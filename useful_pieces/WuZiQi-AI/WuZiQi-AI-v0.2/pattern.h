/*
 * Pattern9 不考虑长连、连六的判断
 * Pattern9 只存储对中间格 连五、双四、冲四 的判断
 * 对 双四和冲四 保存防点位置
 * 1 ~ 9 分别表示防点在 -4 ~ +4 格的偏移处
 * 0xA 表示五连点
 * 0 表示非冲四或五连点
 */

#pragma once

#include <cstdlib>
#include <cstring>
#include <vector>


// 取出 num 从最低位数第 idx 开始的 len 位作为整数返回。
inline unsigned get_bits(const unsigned num, const int idx, const int len)
{
    return num >> idx & ~(~0x0u << len);
}
inline unsigned long long get_bits(const unsigned long long num, const int idx, const int len)
{
    return num >> idx & ~(~0x0u << len);
}

// 将 num 从最低位数第 idx 开始的 len 位设为 val
inline void set_bits(unsigned &num, const int idx, const int len, const unsigned val)
{
    unsigned mask = ~(~0x0u << len) << idx;
    num &= ~mask;
    num |= (val << idx) & mask;
}
inline void set_bits(unsigned long long &num, const int idx, const int len, const unsigned val)
{
    unsigned long long mask = ~(~0x0ull << len) << idx;
    num &= ~mask;
    num |= (unsigned long long(val) << idx) & mask;
}

/////////////////////////////////////////////////////////
class Pattern5{
public:
    enum
    {
        STN5 = 5,
        STN4 = 4,
        STN3 = 3,
        INVP = 0
    };
private:
    // state 的格式：按 4 位划分为 8 个单位
    // 高位侧 | ... | ... | 防点2 | 防点1 | 标志 | 得分 | 低位侧
    // 其中 防点2 > 防点1，防点用 1 ~ 9 表示 -4 ~ +4 的偏移
    // 其中 标志为： 0x5 成五点
    //             0x4 成四点  （对应一个防点）
    //             0x3 成三点  （对应两个防点）
    //             0x0 非特殊点
    std::vector<unsigned> pat_state;

    void calc_pat(unsigned pat)
    {
        int nStone = 0;
        //unsigned stoneBits = 0u;
        //int nBlank = 0;
        unsigned blankBits = 0u;

        for(int i=4; i>=0; --i)
        {
            switch(pat >> i*2 & 0x3)
            {
            case 0x0:
                blankBits = blankBits << 4 | i;
                //++nBlank;
                break;
            case 0x1:
                //stoneBits = stoneBits << 4 | i;
                ++nStone;
                break;
            case 0x2:
                return;
                //break;
            case 0x3:
                return;
                //break;
            default:
                throw "BitBoard.h: Pattern5::calc_pat()\n    Never here!\n";
                break;
            }
        }

        for(int i = 0; i < 5; ++i)
        {   // 得分
            pat_state[pat * 5 + i] = nStone;
        }
        unsigned pos1, pos2, pos3;
        switch(nStone)
        {
        case 2:
            // pos1 < pos2 < pos3
            pos1 = blankBits & 0xF;
            pos2 = blankBits >> 4 & 0xF;
            pos3 = blankBits >> 8 & 0xF;
            pat_state[pat * 5 + pos1] |= (pos3 + 5 - pos1) << 12 | (pos2 + 5 - pos1) << 8 | STN3 << 4;
            pat_state[pat * 5 + pos2] |= (pos3 + 5 - pos2) << 12 | (pos1 + 5 - pos2) << 8 | STN3 << 4;
            pat_state[pat * 5 + pos3] |= (pos2 + 5 - pos3) << 12 | (pos1 + 5 - pos3) << 8 | STN3 << 4;
            break;
        case 3:
            // pos1 < pos2
            pos1 = blankBits & 0xF;
            pos2 = blankBits >> 4 & 0xF;
            pat_state[pat * 5 + pos1] |= (pos2 + 5 - pos1) << 8 | STN4 << 4;
            pat_state[pat * 5 + pos2] |= (pos1 + 5 - pos2) << 8 | STN4 << 4;
            break;
        case 4:
            pat_state[pat * 5 + blankBits] |= STN5 << 4;
            break;
        default:
            break;
        }
    }
public:
    Pattern5()
    {
        pat_state.resize(1024 * 5);
        for(unsigned pat = 0; pat < 1024; ++pat)
        {
            for(int i = 0; i < 5; ++i)
            {
                pat_state[pat * 5 + i] = 0;
            }
            calc_pat(pat);
        }
    }

    unsigned operator()(const unsigned pattern, const int idx) const
    {
        return pat_state[pattern * 5 + idx];
    }
};


//////////////////////////////////////////////////////////////////////////

/*
 * 每个 Pattern 用 4 字节 (32 bits) 存储
 * 其中 6 bits 保存 score
 *     8 bits 低4位和高4位分别保存两个防点（双四时），
 *      或仅低4位保存防点（冲四时），
 *      或低4位标志位
 *          0xA（眠三）
 *          0xB（活三）
 *          0xC（连五）
 *      0x00 表示非特殊点
 *      防点用 1 ~ 9 表示 -4 ~ +4 的偏移
 */
class Pattern9
{
    const static unsigned HASH_SIZE = 59999;    // 大于 3^9 * 3 的质数
    const static unsigned INVALID_PATTERN = 0x2AAAA;    // 0b 10 10101010 10101010 共18位

public:
    enum
    {
        LIAN5 = 0xC,
        HUO3  = 0xB,
        MIAN3 = 0xA,
        INVMK = 0x0
    };

    // State::mark 的格式：
    // 0b 0000 1010     0xA (眠三，MIAN3)
    //    0000 1011     0xB (活三，HUO3)
    //    0000 1100     0xC (连五，LIAN5)
    //    0000 0000     0x0 (非特殊点，INVMK)
    //    0000  def     防点 (冲四)
    //    def2 def1     防点2 防点1 (双四)
    // 其中防点均以相对偏移表示，1 ~ 9 分别表示偏移 -4 ~ +4
    struct State
    {
        unsigned mark:      8;
        unsigned score:     6;
        unsigned pattern:  18;
        State(): score(0), mark(0), pattern(INVALID_PATTERN) {}
    };

private:
    static Pattern5 pat5;
    std::vector<State> hash_table;


    State calc_state(const unsigned pat9) const
    {
        State s;
        s.pattern = pat9;

        unsigned mark[5] = {0}; // 棋形(5/4/3) 防点组个数(1/2/3) 防点组1 防点组2 防点组3
        for(int idx = 0; idx < 5; ++idx)
        {
            unsigned pat5_s = pat5(get_bits(pat9, idx*2, 10), 4 - idx);
            s.score += pat5_s & 0xF;
            unsigned def;
            switch(pat5_s >> 4 & 0xF)
            {
            case 0x5:   // 成五点
                if(mark[0] < 5)
                {
                    mark[0] = 5;
                    mark[1] = 1;
                }
                else
                {
                    ++mark[1];
                }
                break;
            case 0x4:   // 成四点
                def = pat5_s >> 8 & 0xF;
                if(mark[0] < 4)
                {
                    mark[0] = 4;
                    mark[1] = 1;
                    mark[2] = def;
                }
                else if(mark[0] == 4)
                {   // 已经是冲四
                    if(mark[1] == 1 && mark[2] != def)
                    {   // 防点不同，则是双四点
                        mark[1] = 2;
                        mark[3] = def;
                    }
                }
                break;
            case 0x3:   // 成三点
                def = pat5_s >> 8 & 0xFF;
                if(mark[0] < 3)
                {
                    mark[0] = 3;
                    mark[1] = 1;
                    mark[2] = def;
                }
                else if(mark[0] == 3)
                {
                    if(mark[1] == 1)
                    {   // 已经是眠三点
                        if(mark[2] != def)
                        {   // 防点不同，则是亚连活三
                            mark[1] = 2;
                            mark[3] = def;
                        }
                    }
                    else if(mark[1] == 2)
                    {   // 已经是亚连活三点
                        if(mark[2] != def && mark[3] != def)
                        {
                            mark[1] = 3;
                            mark[4] = def;
                        }
                    }
                }
                break;
            default:    // 非特殊点
                break;
            }
        }

        switch(mark[0])
        {
        case 5:
            s.mark = LIAN5;
            break;
        case 4:
            if(mark[1] == 1)
            {   // 单冲四
                s.mark = mark[2];
            }
            else if(mark[1] == 2)
            {   // 双四
                s.mark = mark[3] << 4 | mark[2];
            }
            break;
        case 3:
            if(mark[1] == 1)
            {
                s.mark = MIAN3;
            }
            else if(mark[1] == 2)
            {
                if((mark[2] >> 4) == (mark[3] & 0xF))
                {   // 亚连活三或跳三，三个挡点
                    s.mark = HUO3;
                }
                else
                {   // 两个活三相距太远，实际只能分别形成眠三
                    s.mark = MIAN3;
                }
            }
            else if(mark[1] == 3)
            {   // 真活三，两个挡点
                s.mark = HUO3;
            }
            break;
        default:
            s.mark = INVMK;
            break;
        }
        return s;
    }
public:
    Pattern9(): hash_table(HASH_SIZE){}

    State operator()(const unsigned pat)
    {
        unsigned pos = pat % HASH_SIZE;
        if(hash_table[pos].pattern == pat)
        {
            return hash_table[pos];
        }
        else if(hash_table[pos].pattern == INVALID_PATTERN)
        {
            return hash_table[pos] = calc_state(pat);
        }

        unsigned offsetpos, i = 0;
        for(;;)
        {
            ++i;
            offsetpos = (pos + i*i) % HASH_SIZE;
            if(hash_table[offsetpos].pattern == pat)
            {
                return hash_table[offsetpos];
            }
            else if(hash_table[offsetpos].pattern == INVALID_PATTERN)
            {
                return hash_table[offsetpos] = calc_state(pat);
            }

            //++i;
            offsetpos = (pos - i*i) % HASH_SIZE;
            if(hash_table[offsetpos].pattern == pat)
            {
                return hash_table[offsetpos];
            }
            else if(hash_table[offsetpos].pattern == INVALID_PATTERN)
            {
                return hash_table[offsetpos] = calc_state(pat);
            }
        }
        throw "BitBoard.h: Pattern9::operator()\n    Hash Table is FULL!\n";
    }
};

