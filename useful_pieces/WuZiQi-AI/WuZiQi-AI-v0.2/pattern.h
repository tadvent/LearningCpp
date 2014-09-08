/*
 * Pattern9 �����ǳ������������ж�
 * Pattern9 ֻ�洢���м�� ���塢˫�ġ����� ���ж�
 * �� ˫�ĺͳ��� �������λ��
 * 1 ~ 9 �ֱ��ʾ������ -4 ~ +4 ���ƫ�ƴ�
 * 0xA ��ʾ������
 * 0 ��ʾ�ǳ��Ļ�������
 */

#pragma once

#include <cstdlib>
#include <cstring>
#include <vector>


// ȡ�� num �����λ���� idx ��ʼ�� len λ��Ϊ�������ء�
inline unsigned get_bits(const unsigned num, const int idx, const int len)
{
    return num >> idx & ~(~0x0u << len);
}
inline unsigned long long get_bits(const unsigned long long num, const int idx, const int len)
{
    return num >> idx & ~(~0x0u << len);
}

// �� num �����λ���� idx ��ʼ�� len λ��Ϊ val
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
    // state �ĸ�ʽ���� 4 λ����Ϊ 8 ����λ
    // ��λ�� | ... | ... | ����2 | ����1 | ��־ | �÷� | ��λ��
    // ���� ����2 > ����1�������� 1 ~ 9 ��ʾ -4 ~ +4 ��ƫ��
    // ���� ��־Ϊ�� 0x5 �����
    //             0x4 ���ĵ�  ����Ӧһ�����㣩
    //             0x3 ������  ����Ӧ�������㣩
    //             0x0 �������
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
        {   // �÷�
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
 * ÿ�� Pattern �� 4 �ֽ� (32 bits) �洢
 * ���� 6 bits ���� score
 *     8 bits ��4λ�͸�4λ�ֱ𱣴��������㣨˫��ʱ����
 *      �����4λ������㣨����ʱ����
 *      ���4λ��־λ
 *          0xA��������
 *          0xB��������
 *          0xC�����壩
 *      0x00 ��ʾ�������
 *      ������ 1 ~ 9 ��ʾ -4 ~ +4 ��ƫ��
 */
class Pattern9
{
    const static unsigned HASH_SIZE = 59999;    // ���� 3^9 * 3 ������
    const static unsigned INVALID_PATTERN = 0x2AAAA;    // 0b 10 10101010 10101010 ��18λ

public:
    enum
    {
        LIAN5 = 0xC,
        HUO3  = 0xB,
        MIAN3 = 0xA,
        INVMK = 0x0
    };

    // State::mark �ĸ�ʽ��
    // 0b 0000 1010     0xA (������MIAN3)
    //    0000 1011     0xB (������HUO3)
    //    0000 1100     0xC (���壬LIAN5)
    //    0000 0000     0x0 (������㣬INVMK)
    //    0000  def     ���� (����)
    //    def2 def1     ����2 ����1 (˫��)
    // ���з���������ƫ�Ʊ�ʾ��1 ~ 9 �ֱ��ʾƫ�� -4 ~ +4
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

        unsigned mark[5] = {0}; // ����(5/4/3) ���������(1/2/3) ������1 ������2 ������3
        for(int idx = 0; idx < 5; ++idx)
        {
            unsigned pat5_s = pat5(get_bits(pat9, idx*2, 10), 4 - idx);
            s.score += pat5_s & 0xF;
            unsigned def;
            switch(pat5_s >> 4 & 0xF)
            {
            case 0x5:   // �����
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
            case 0x4:   // ���ĵ�
                def = pat5_s >> 8 & 0xF;
                if(mark[0] < 4)
                {
                    mark[0] = 4;
                    mark[1] = 1;
                    mark[2] = def;
                }
                else if(mark[0] == 4)
                {   // �Ѿ��ǳ���
                    if(mark[1] == 1 && mark[2] != def)
                    {   // ���㲻ͬ������˫�ĵ�
                        mark[1] = 2;
                        mark[3] = def;
                    }
                }
                break;
            case 0x3:   // ������
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
                    {   // �Ѿ���������
                        if(mark[2] != def)
                        {   // ���㲻ͬ��������������
                            mark[1] = 2;
                            mark[3] = def;
                        }
                    }
                    else if(mark[1] == 2)
                    {   // �Ѿ�������������
                        if(mark[2] != def && mark[3] != def)
                        {
                            mark[1] = 3;
                            mark[4] = def;
                        }
                    }
                }
                break;
            default:    // �������
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
            {   // ������
                s.mark = mark[2];
            }
            else if(mark[1] == 2)
            {   // ˫��
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
                {   // ������������������������
                    s.mark = HUO3;
                }
                else
                {   // �����������̫Զ��ʵ��ֻ�ֱܷ��γ�����
                    s.mark = MIAN3;
                }
            }
            else if(mark[1] == 3)
            {   // ���������������
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

