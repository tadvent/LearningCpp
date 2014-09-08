/*
 * 注： 这一版 AI 受 Pattern9 所限，暂不考虑对长连判断的支持
 * 因此无法支持禁手规则以及精确五连取胜的规则
 * 留待下一版再做改进
 * 
 * 有了 Pattern9 的经验，再写 Pattern11 时不用保留太多信息占空间
 * 只需正确保存中间点的判断结果以及 pattern 得分即可
 * (防点也只用保存冲四和双四的即可，活三的防点用不到)
 * 再加上 pattern 本身，一共 2 个 unsigned 足够
 * 
 * 到时使用自由规则可用 Pattern9，使用标准规则或有禁规则可用 Pattern11
 */

#pragma once

#include <cstdlib>
#include <cstring>


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
    enum {
        STONE_IDX = 28,
        BLANK_IDX = 24,
        JUMP_IDX = 20
    };
private:
    // state 的格式：按 4 位划分为 8 个单位
    // 高位侧 <-- | 棋子数 | 空位数 | 下一跳 | .. 棋子坐标 .. | .. 空位坐标 .. | --> 低位侧
    // 其中棋子和空位坐标用格数表示： 0、1、2、3、4
    // 棋子和空位坐标从低位到高位依次递增
    // 棋子数 即为 外势得分
    unsigned pat_state[1024];

    void calc_pat(unsigned pat, unsigned &states)
    {
        int blank = 0;
        unsigned blanks = 0;
        int stone = 0;
        unsigned stones = 0;
        states = 0u;

        for(int i=4; i>=0; --i)
        {
            switch((pat & (0x3 << (i*2))) >> (i*2))
            {
            case 0x0:
                blanks <<= 4;
                blanks |= i;
                ++blank;
                break;
            case 0x1:
                stones <<= 4;
                stones |= i;
                ++stone;
                break;
            case 0x2:
                return;
                //break;
            case 0x3:
                set_bits(states, JUMP_IDX, 4, i + 1);   // 匹配不成功时可直接跳到 i+1 格之后进行下次比较
                return;
                //break;
            default:
                throw "BitBoard.h: Pattern5::calc_pat()\n    Never here!\n";
                break;
            }
        }
        states = blanks | stones << blank * 4;
        set_bits(states, JUMP_IDX, 4, 1);
        set_bits(states, BLANK_IDX, 4, blank);
        set_bits(states, STONE_IDX, 4, stone);
    }
public:
    Pattern5()
    {
        for(unsigned pat = 0; pat < 1024; ++pat)
        {
            calc_pat(pat, pat_state[pat]);
        }
    }

    unsigned operator()(const unsigned pattn) const
    {
        return pat_state[pattn];
    }
};

/////////////////////////////////////////////////////////
class Pattern9
{
public:
    enum {
        LIAN6 = 0xF,    // 长连点
        LIAN5 = 0xE,    // 五连点
        SHUA4 = 0xD,    // 双四点
        CHON4 = 0xC,    // 冲四点
        MIAN3 = 0xB,    // 眠三点
        INVMK = 0xA,    // 无效点
        MAXMK = 0x9     // 小于此值为活三点
    };
    struct State
    {
        // 防点用偏移表示，0 ~ 8 分别表示防点在 -4 ~ +4 的偏移处
        // 连六点                  ---- ---- 1111 xxxx    / --  --   标志(LIAN6)      长连点
        // 五连点                  ---- ---- 1110 xxxx    / --  --   标志(LIAN5)      五连点
        // 四连/双四点 及其两个防点   xxxx xxxx 1101 xxxx    / 防2 防1  标志(SHUA4)  四连/双四点
        // 单冲四点 及其一个防点      ---- xxxx 1100 xxxx    / --  防   标志(CHON4)      冲四点
        // 眠三点                  ---- ---- 1011 xxxx    / --  --   标志(MIAN3)      眠三点
        // 无效点                  ---- ---- 1010 ----     / --  --  标志(INVMK)        --
        // 活三点 及其三个防点       xxxx xxxx xxxx xxxx    / 防3 防2  防1(< MAXMK)      活三点
        // move0 ~ move3: 中间格(2字节) 低4格 高4格
        unsigned move0:    16;
        unsigned move1:    16;
        unsigned move2:    16;
        unsigned move3:    16;

        // 记录除中间格以外的眠三点
        // ---- xxxx xxxx xxxx xxxx xxxx numh numl
        // 眠三点(最多五个，低位到高位从小到大) 高4格中数量 低4格中数量
        unsigned mian3;

        unsigned score:             5;  // 外势得分
        unsigned max_valid:         3;  // 最高有效格(如墙在 8 格，最高有效格即为 7)
        unsigned jump:              4;  // 下一跳距离
        unsigned next_low_valid:    2;  // 表示下一次判断时低 4 格是否有效
        unsigned pattn:             18;  // 9格 pattern

        State(): move0(INVMK << 4), move1(INVMK << 4), move2(INVMK << 4), move3(INVMK << 4),
            mian3(0), score(0), jump(1), max_valid(4), next_low_valid(0) {}
    };

private:
    const static unsigned HASH_SIZE = 59999;    // 大于 3^9 * 3 的质数
    const static unsigned INVALID_PATTERN = 0x2AAAA;    // 0b 10 10101010 10101010 共18位

    static Pattern5 pat5;
    State *hash_table;

    // 防点用偏移表示，0 ~ 8 分别表示防点在 -4 ~ +4 的偏移处
    // 连六点                  ---- ---- 1111 xxxx    / --  --   标志(LIAN6)      长连点
    // 五连点                  ---- ---- 1110 xxxx    / --  --   标志(LIAN5)      五连点
    // 四连/双四点 及其两个防点   xxxx xxxx 1101 xxxx    / 防2 防1  标志(SHUA4)  四连/双四点
    // 单冲四点 及其一个防点      ---- xxxx 1100 xxxx    / --  防   标志(CHON4)      冲四点
    // 眠三点                  ---- ---- 1011 xxxx    / --  --   标志(MIAN3)      眠三点
    // 无效点                  ---- ---- 1010 ----     / --  --  标志(INVMK)        --
    // 活三点 及其三个防点       xxxx xxxx xxxx xxxx    / 防3 防2  防1(< MAXMK)      活三点
    unsigned mark2bits(const unsigned pos, const unsigned mark[5]) const
    {
        switch(mark[0])
        {
        case 5:
            if(mark[1] == 1)
            {   // 五连点
                return (LIAN5 << 4) | pos;
            }
            else if(mark[1] > 1)
            {   // 长连点 无法判断 xOOOOO 的情况
                // 注：Pattern9 无法精确判断长连点，必须要 Pattern11 以上，因此这里不加区分，仍返回五连
                return (LIAN5 << 4) | pos;
            }
            else
            {
                throw "BitBoard.h: Pattern9::mark2bits()\n    case 5: Never here!\n";
            }
            break;
        case 4:
            if(mark[1] == 1)
            {   // 单冲四点
                return (mark[2] << 8) | (CHON4 << 4) | pos;
            }
            else if(mark[1] == 2)
            {   // 双四点
                return (mark[3] << 12) | (mark[2] << 8) | (SHUA4 << 4) | pos;
            }
            else
            {
                throw "BitBoard.h: Pattern9::mark2bits()\n    case 4: Never here!\n";
            }
            break;
        case 3:
            if(mark[1] == 1)
            {   // 眠三点
                return (MIAN3 << 4) | pos;
            }
            else if(mark[1] == 2)
            {
                if((mark[2] >> 4) == (mark[3] & 0xF))
                {   // 亚连活三或跳三，三个挡点
                    return mark[3] << 8 | mark[2] << 4 | pos;
                }
                else
                {   // 两个活三相距太远，实际只能分别形成眠三
                    return (MIAN3 << 4) | pos;
                }
            }
            else if(mark[1] == 3)
            {   // 真活三点，两个挡点
                return INVMK << 12 | mark[3] << 4 | pos;
            }
            else
            {
                throw "BitBoard.h: Pattern9::mark2bits()\n    case 3: Never here!\n";
            }
            break;
        default:
            return INVMK << 4;    // 无效点
            break;
        }
    }
    State calc_state(const unsigned pat9)
    {
        State s;
        s.pattn = pat9;

        unsigned mark[9][5] = {0};  // 棋形(5/4/3) 防点组个数(1/2/3) 防点组1 防点组2 防点组3
        unsigned max_stone_idx = 0;
        unsigned max_wall_idx = 0;
        for(int idx = 0; idx < 5;)
        {
            unsigned pat5_s = pat5(get_bits(pat9, idx*2, 10));
            int n_blank = get_bits(pat5_s, Pattern5::BLANK_IDX, 4);
            int n_stone = get_bits(pat5_s, Pattern5::STONE_IDX, 4);
            int jump = get_bits(pat5_s, Pattern5::JUMP_IDX, 4);

            if(n_stone > 0)
            {   // 有棋子，更新最高棋子位置
                max_stone_idx = idx + get_bits(pat5_s, 16, 4);
            }
            else
            {   // 全空格 或 有墙
                if(jump > 1)
                {   // 有墙，更新最高墙的位置
                    max_wall_idx = idx + jump - 1;
                }
                idx += jump;
                continue;
            }

            s.score += n_stone;

            int pos0, pos1, pos2;       // pos 为 0, 2, 4, 6, 8, 10, 12, 14, 16
            unsigned def0, def1, def2;  // 与 pos0~2 相对应的防点组，用偏移表示
            switch(n_blank)
            {
            case 1: // 单空格，四棋子
                pos0 = idx + get_bits(pat5_s, 0, 4);

                if(mark[pos0][0] < 5)
                {
                    mark[pos0][0] = 5;  // pos0 是五连点
                    mark[pos0][1] = 1;
                }
                else
                {   // 已经是五连点
                    ++mark[pos0][1];
                }
                break;

            case 2: // 双空格，三棋子
                pos0 = idx + get_bits(pat5_s, 0, 4);
                pos1 = idx + get_bits(pat5_s, 4, 4);
                def0 = pos1 + 4 - pos0;
                def1 = pos0 + 4 - pos1;

                if(mark[pos0][0] < 4)   // 处理 pos0
                {   // pos0 至少是冲四点
                    mark[pos0][0] = 4;
                    mark[pos0][1] = 1;
                    mark[pos0][2] = def0;
                }
                else if(mark[pos0][0] == 4)
                {   // 已经是冲四
                    if(mark[pos0][1] == 1 && mark[pos0][2] != def0)
                    {   // 防点不同，则是双四点
                        mark[pos0][1] = 2;
                        mark[pos0][3] = def0;
                    }
                }
                if(mark[pos1][0] < 4)   // 处理 pos1
                {
                    mark[pos1][0] = 4;
                    mark[pos1][1] = 1;
                    mark[pos1][2] = def1;
                }
                else if(mark[pos1][0] == 4)
                {
                    if(mark[pos1][1] == 1 && mark[pos1][2] != def1)
                    {
                        mark[pos1][1] = 2;
                        mark[pos1][3] = def1;
                    }
                }
                break;

            case 3: // 三空格，双棋子
                pos0 = idx + get_bits(pat5_s, 0, 4);
                pos1 = idx + get_bits(pat5_s, 4, 4);
                pos2 = idx + get_bits(pat5_s, 8, 4);
                def0 = (pos1 + 4 - pos0) | ((pos2 + 4 - pos0) << 4);
                def1 = (pos0 + 4 - pos1) | ((pos2 + 4 - pos1) << 4);
                def2 = (pos0 + 4 - pos2) | ((pos1 + 4 - pos2) << 4);

                // pos0
                if(mark[pos0][0] < 3)
                {   // pos0 至少是眠三点
                    mark[pos0][0] = 3;
                    mark[pos0][1] = 1;
                    mark[pos0][2] = def0;
                }
                else if(mark[pos0][0] == 3)
                {
                    if(mark[pos0][1] == 1)
                    {   // 已经是眠三点
                        if(mark[pos0][2] != def0)
                        {   // 防点不同，则是（亚连）活三点
                            mark[pos0][1] = 2;
                            mark[pos0][3] = def0;
                        }
                    }
                    else if(mark[pos0][1] == 2)
                    {   // 已经是（亚连）活三点
                        if(mark[pos0][2] != def0 && mark[pos0][3] != def0)
                        {   // 防点不同，则是真活三点
                            mark[pos0][1] = 3;
                            mark[pos0][4] = def0;
                        }
                    }
                }
                // pos1
                if(mark[pos1][0] < 3)
                {
                    mark[pos1][0] = 3;
                    mark[pos1][1] = 1;
                    mark[pos1][2] = def1;
                }
                else if(mark[pos1][0] == 3)
                {
                    if(mark[pos1][1] == 1)
                    {
                        if(mark[pos1][2] != def1)
                        {
                            mark[pos1][1] = 2;
                            mark[pos1][3] = def1;
                        }
                    }
                    else if(mark[pos1][1] == 2)
                    {
                        if(mark[pos1][2] != def1 && mark[pos1][3] != def1)
                        {
                            mark[pos1][1] = 3;
                            mark[pos1][4] = def1;
                        }
                    }
                }
                // pos2
                if(mark[pos2][0] < 3)
                {
                    mark[pos2][0] = 3;
                    mark[pos2][1] = 1;
                    mark[pos2][2] = def2;
                }
                else if(mark[pos2][0] == 3)
                {
                    if(mark[pos2][1] == 1)
                    {
                        if(mark[pos2][2] != def2)
                        {
                            mark[pos2][1] = 2;
                            mark[pos2][3] = def2;
                        }
                    }
                    else if(mark[pos2][1] == 2)
                    {
                        if(mark[pos2][2] != def2 && mark[pos2][3] != def2)
                        {
                            mark[pos2][1] = 3;
                            mark[pos2][4] = def2;
                        }
                    }
                }
                break;

            default:
                break;
            }

            idx += jump;
        }

        // 填充返回值 s
        int move_i = 0;
        int mian3_low = 0;
        int mian3_high = 0;
        unsigned bits = mark2bits(4, mark[4]);
        if(bits != INVMK << 4)
        {
            s.move0 = bits;
            ++move_i;
        }
        for(int i=0; i<4; ++i)
        {
            bits = mark2bits(i, mark[i]);
            if(bits == INVMK << 4) continue;
            if((bits & 0xF0) == MIAN3 << 4)
            {
                s.mian3 |= (bits & 0xF) << (mian3_low * 4 + 8);
                ++mian3_low;
            }
            else
            {
                switch(move_i)
                {
                case 0:
                    s.move0 = bits;
                    break;
                case 1:
                    s.move1 = bits;
                    break;
                case 2:
                    s.move2 = bits;
                    break;
                case 3:
                    s.move3 = bits;
                    break;
                default:
                    throw "BitBoard.h: Pattern9::calc_state()\n    Too many special points! 1";
                    break;
                }
                ++move_i;
            }
        }   // for(int i=0; i<4; ++i)
        for(int i=5; i<9; ++i)
        {
            bits = mark2bits(i, mark[i]);
            if(bits == INVMK << 4) continue;
            if((bits & 0xF0) == MIAN3 << 4)
            {
                s.mian3 |= (bits & 0xF) << ((mian3_low + mian3_high) * 4 + 8);
                ++mian3_high;
            }
            else
            {
                switch(move_i)
                {
                case 0:
                    s.move0 = bits;
                    break;
                case 1:
                    s.move1 = bits;
                    break;
                case 2:
                    s.move2 = bits;
                    break;
                case 3:
                    s.move3 = bits;
                    break;
                default:
                    throw "BitBoard.h: Pattern9::calc_state()\n    Too many special points! 2";
                    break;
                }
                ++move_i;
            }
        }   // for(int i=5; i<9; ++i)
        s.mian3 |= mian3_high << 4 | mian3_low;

        if(max_wall_idx > 5)
        {   // 墙出现在最高3格中
            s.max_valid = max_wall_idx - 1;
            s.jump = max_wall_idx + 1;
            s.next_low_valid = 1;
        }
        else
        {
            if(max_stone_idx < 6)
            {
                s.max_valid = 5;
                if(max_stone_idx < 3)
                {
                    s.jump = 6;
                    s.next_low_valid = 1;
                }
            }
        }

        return s;
    }
public:
    Pattern9()
    {
        hash_table = (State*)malloc(HASH_SIZE * sizeof(State));
        if(hash_table == NULL) throw "BitBoard.h: Pattern9::Pattern()\n    Not Enough Memory!\n";
        memset(hash_table, 0xAA, HASH_SIZE * sizeof(State));
    }

    const State& operator()(unsigned pat)
    {
        unsigned pos = pat % HASH_SIZE;
        if(hash_table[pos].pattn == pat)
        {
            return hash_table[pos];
        }
        else if(hash_table[pos].pattn == INVALID_PATTERN)
        {
            return hash_table[pos] = calc_state(pat);
        }

        unsigned offsetpos, i = 0;
        for(;;)
        {
            ++i;
            offsetpos = (pos + i*i) % HASH_SIZE;
            if(hash_table[offsetpos].pattn == pat)
            {
                return hash_table[offsetpos];
            }
            else if(hash_table[offsetpos].pattn == INVALID_PATTERN)
            {
                return hash_table[offsetpos] = calc_state(pat);
            }

            ++i;
            offsetpos = (pos - i*i) % HASH_SIZE;
            if(hash_table[offsetpos].pattn == pat)
            {
                return hash_table[offsetpos];
            }
            else if(hash_table[offsetpos].pattn == INVALID_PATTERN)
            {
                return hash_table[offsetpos] = calc_state(pat);
            }
        }
        throw "BitBoard.h: Pattern9::operator()\n    Hash Table is FULL!\n";
    }
};
