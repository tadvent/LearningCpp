#pragma once

// 本文件定义3个 Pattern 类： Pattern5、Pattern9 和 Pattern13
// 其中 Pattern9 用于自由规则(大于5连也算赢)和无禁规则
//     Pattern13 用于精确五连和/或有禁规则
// 程序其它部分只使用 Pattern9 和 Pattern13
// Pattern5 仅作为辅助类，帮助 Pattern9 和 Pattern13 实现其功能。
// 

#include <cstdlib>
#include <cstring>
#include <cassert>


// 取出 num 从最低位数第 idx 开始的 len 位作为整数返回。
inline unsigned get_bits(const unsigned num, const int idx, const int len) {
    return num >> idx & ~(~0x0u << len);
}
inline unsigned long long get_bits(const unsigned long long num, const int idx, const int len) {
    return num >> idx & ~(~0x0ull << len);
}

// 将 num 从最低位数第 idx 开始的 len 位设为 val
inline void set_bits(unsigned &num, const int idx, const int len, const unsigned val) {
    unsigned mask = ~(~0x0u << len) << idx;
    num &= ~mask;
    num |= (val << idx) & mask;
}
inline void set_bits(unsigned long long &num, const int idx, const int len, const unsigned val) {
    unsigned long long mask = ~(~0x0ull << len) << idx;
    num &= ~mask;
    num |= (unsigned long long(val) << idx) & mask;
}

// Pattern 中用到的表示法
enum {
    BLANK = 0,  // 00
    STONE = 1,  // 01
    BLOCK = 3   // 11
};

/////////////////////////////////////////////////////////////////////////////
// 由 WuZiQi-AI-v0.1 的经验，只需判断 Pattern9 中间格的状态即可
// 相应的 Pattern5 的实现需稍作调整，以使 Pattern9 的实现更加高效

// 对每个 pat5 用 1 byte 存储，格式如下
// | jump | nStone+1 |
// jump 表示要跳过最高格的墙需右移的位数 (0, 2, 4, 6, 8, 10)
//     jump = 0 表示 pat5 中没有墙
// 当 jump = 0 时，低 4 位是 nStone + 1；否则低 4 位为 1
// nStone 表示棋子数，+1 表示在空格处填入棋子后会成几颗棋子。

class Pattern5 {
public:
    Pattern5() {
        // 如果第一次建立 Pattern5 对象，初始化 buf 数组
        if(objCount++ == 0) {
            // 申请空间
            const int MEM_SIZE = 1 << 10;
            buf = (unsigned char *)malloc(MEM_SIZE);
            if(buf == NULL) {
                throw "ERROR: Not Enough Memory!\n";
            }

            // 初始化 buf 数组
            memset(buf, 0, MEM_SIZE);
            for(unsigned pat5 = 0; pat5 < 1024u; ++pat5) {
                buf[pat5] = calcPattern(pat5);
            }
        } // if(objCount++ == 0)
    }

    ~Pattern5() {
        // 如果销毁最后一个 Pattern5 对象，释放 buf
        if(--objCount == 0) {
            free(buf);
        }
    }

    // 返回 | jump:4b | nStone+1:4b |
    // jump 表示要跳过最高格的墙需右移的位数 (0, 2, 4, 6, 8, 10)
    //     jump = 0 表示 pat5 中没有墙
    // 当 jump = 0 时，低 4 位是 nStone + 1；否则低 4 位为 1
    // nStone 表示棋子数，+1 表示在空格处填入棋子后会成几颗棋子。
    unsigned char getState(const unsigned pat5) const {
        // 越界检查
        assert(pat5 < (1 << 10));

        return buf[pat5];
    }

private:

    // buf数组存储每个 pat5 对应的状态，具体格式见前描述。
    static unsigned char *buf;

    // 记录 Pattern5 对象的数目，只有第一次建立对象时初始化 buf 数组。
    static int objCount;

    // 返回 | jump:4b | nStone+1:4b |
    static unsigned char calcPattern(const unsigned pat5) {
        // 越界检查
        assert(pat5 < 1024u);

        // nStone 记录棋子数
        unsigned nStone = 0;

        // 位置从 4 到 0 依次判断，遇到墙可直接返回
        for(int i = 8; i >= 0; i-=2) {
            switch(get_bits(pat5, i, 2)) {
            case BLANK:     // 空格
                break;
            case STONE:     // 棋子
                ++nStone;
                break;
            case BLOCK:     // 墙
                return ((i + 2) << 4) | 1;
                break;
            default:
                return 0;
                // throw "ERROR: Illegal Stone\n";
                break;
            } // switch
        } // for

        return nStone + 1;
    }
};


/////////////////////////////////////////////////////////////////////////////
// Pattern MARK

enum {
    // 长连
    PT_LIAN6 = 11,
    // 连5
    PT_LIAN5 = 10,
    // 活4
    PT_LIAN4 = 9,
    // 双4
    PT_SHUA4 = 8,
    // 冲4
    PT_CHON4 = 7,
    // 活3
    PT_LIAN3 = 6,
    // 双3 - 同条线上的双3表示再下一步可形成双4，攻击强度与活3相同，但不算作活3
    PT_SHUA3 = 5,
    // 眠3
    PT_MIAN3 = 4,
    // 活2
    PT_LIAN2 = 3,
    // 眠2
    PT_MIAN2 = 2,
    // 无效进攻
    PT_INVMV = 1
};


// Pattern9 为了方便判断空格放入棋子时的攻击类型，并方便计算外势得分
// 要判断中间空格的攻击类型，只需考虑两侧各 4 格的状态，因此共有
// 3 ^ 8 = 6561 个需保存，开三倍空间约为 19001 (取质数) 个。

class Pattern9 {
public:
    struct State {
        // 为了使构造函数中对 pat9 的赋初值 0x2AAAA 正确生效
        // pat9 位域必须偶数位对齐
        unsigned atkLevel:  4;  // 中间格的进攻种类
        unsigned midScore:  4;  // 中间空格放入棋子的得分增量 (范围 [0, 5])
        unsigned allScore:  6;  // 中间空格放入墙时需扣掉的分 (范围 [0, 20])
        unsigned pat9:     18;  // 对应的 Pattern9
        State(const unsigned Pat9)
            : midScore(0), allScore(0), atkLevel(PT_INVMV), pat9(Pat9) {}
    };

    Pattern9() {
        if(objCount++ == 0) {
            buf = (State *)malloc(HASH_SIZE * sizeof(State));
            if(buf == NULL) {
                throw "ERROR: Not Enough Memory!\n";
            }
            // 将所有 buf[i].pat9 都初始化为 0x2AAAA (0b 10 1010 1010 ...) 的无效值
            memset(buf, 0xAA, HASH_SIZE * sizeof(State));
        }
    }
    ~Pattern9() {
        if(--objCount == 0) {
            free(buf);
        }
    }

    // 参数 pat9 中间格必须是空格
    State getState(const unsigned pat9) {
        // 越界检查
        assert(pat9 < (1 << 18));
        // 中间格必须是空格
        assert(get_bits(pat9, 8, 2) == BLANK);

        unsigned pos = pat9 % HASH_SIZE;
        if(buf[pos].pat9 == pat9) {
            return buf[pos];
        }
        else if(buf[pos].pat9 == INVALID_PATTERN) {
            return buf[pos] = calcPattern(pat9);
        }

        unsigned offsetpos, i = 0;
        for(;;) {
            ++i;
            offsetpos = (pos + i*i) % HASH_SIZE;
            if(buf[offsetpos].pat9 == pat9) {
                return buf[offsetpos];
            }
            else if(buf[offsetpos].pat9 == INVALID_PATTERN) {
                return buf[offsetpos] = calcPattern(pat9);
            }

            ++i;
            offsetpos = (pos - i*i) % HASH_SIZE;
            if(buf[offsetpos].pat9 == pat9) {
                return buf[offsetpos];
            }
            else if(buf[offsetpos].pat9 == INVALID_PATTERN) {
                return buf[offsetpos] = calcPattern(pat9);
            }
        }
        throw "ERROR: Hash Table is FULL!\n";
    }

private:
    // 大于 3^9 * 3 的质数
    static const unsigned HASH_SIZE = 19001u;
    // 0b 10 10101010 10101010 共18位
    static const unsigned INVALID_PATTERN = 0x2AAAA;

    // hash 表的存储空间
    static State *buf;

    // 记录 Pattern9 对象的数量，只在初次构建对象时初始化 buf
    static int objCount;

    // 共用的 Pattern5 成员
    static Pattern5 objPat5;

    // 根据 pat9 求得对应的 State。
    // pat9 的中间格必须是空格
    State calcPattern(const unsigned pat9) const {
        // 越界检查 (< 0b 100 0000 0000 0000 0000)
        assert(pat9 < 0x40000);
        // 中间格必须是空格
        assert(get_bits(pat9, 8, 2) == BLANK);

        State s(pat9);

        // 前 5 格的攻击类型
        unsigned attackLevel = objPat5.getState(get_bits(pat9, 0, 10));
        // 前 5 格偏移的位置
        unsigned pos = attackLevel >> 4;

#if 0
        // 取得后 5 格中墙的位置
        unsigned state2 = objPat5.getState(get_bits(pat9, 8, 10));
        unsigned pos2 = (state2 > 0xF)? (state2 & 0xF) : 10;
        // 中间格放入棋子的得分
        s.midScore = (pos2 - pos) / 2;
#endif

        // 如果 pos > 0，说明前 5 格中有墙，跳过后重新判断
        if(pos > 0) {
            attackLevel = objPat5.getState(get_bits(pat9, pos, 10));

            // 如果 attLevel.jump > 0，说明 pat9 中有间隔刚好为 5 的墙，直接返回无效 s
            if(attackLevel > 0xF) {
                return s;
            }
        }

        // 记录上次棋子迁移的形态
        // 0x000    空格 -> 空格
        // 0x001    棋子 -> 空格
        // 0x400    空格 -> 棋子
        // 0x401    棋子 -> 棋子
        // 初始化为任一无效值
        unsigned transMark = 0x111;

#if 0
        // 如果 pat9 的中间格不是空格，只计算得分即可
        if(get_bits(pat9, 8, 2) != BLANK) {
            // 从 pos 处开始依次加和
            for(; pos < 10; pos += 2) {
                s.score += attackLevel - 1;

                // 读取下一格，更新 transMask
                transMark = pat9 >> pos & 0xC03;
                switch(transMark) {
                case 0x000: // 空格 -> 空格
                    break;
                case 0x001: // 棋子 -> 空格
                    --attackLevel;
                    break;
                case 0x400: // 空格 -> 棋子
                    ++attackLevel;
                    break;
                case 0x401: // 棋子 -> 棋子
                    break;
                default:    // 有墙，跳过
                    pos += 10;
                    break;
                } // switch
            } // for

            return s;
        } // if
#endif

        // 上次成 i 子的位置
        unsigned last[5];
        // 初始化为很大的数
        memset(last, 0x40, sizeof(last));

        // 从 pos 处开始依次判断
        for(; pos < 10; pos += 2) {
            // 棋子数计入 score
            s.allScore += attackLevel - 1;
            ++s.midScore;

            // 根据 attLevel 区分攻击类型
            switch(attackLevel) {
            case 5: // 成5
                // 不区分长连，都按五连算
                s.atkLevel = PT_LIAN5;
                break;
            case 4: // 成4
                // last[4] 初始化为很大的数，以 > 10 判断是否第一次成4
                if(pos - last[4] > 20) {
                    if(PT_CHON4 > s.atkLevel) {
                        s.atkLevel = PT_CHON4;
                    }
                }
                // 连续两个 4
                else if(pos - last[4] == 2) {
                    // 空格 -> 空格迁移，则为活4
                    if(transMark == 0x000) {
                        if(PT_LIAN4 > s.atkLevel) {
                            s.atkLevel = PT_LIAN4;
                        }
                    }
                }
                // 非连续的两个 4 即为双四
                else {
                    if(PT_SHUA4 > s.atkLevel) {
                        s.atkLevel = PT_SHUA4;
                    }
                }
                last[4] = pos;
                break;
            case 3: // 成3
                // 第一次成3
                if(pos - last[3] > 20) {
                    if(PT_MIAN3 > s.atkLevel) {
                        s.atkLevel = PT_MIAN3;
                    }
                }
                // 连续两个 3
                else if(pos - last[3] == 2) {
                    // 空格 -> 空格
                    if(transMark == 0x000) {
                        if(PT_LIAN3 > s.atkLevel) {
                            s.atkLevel = PT_LIAN3;
                        }
                    }
                }
                // 3 2 3
                // XO_O___OX
                // XO__O__OX
                else if(pos - last[3] == 4) {
                    if(PT_SHUA3 > s.atkLevel) {
                        s.atkLevel = PT_SHUA3;
                    }
                }
                // 3 2 2 3
                // 也可能是 3 4 4 3，这种情况会被 4 覆盖，所以不用单独判断。
                else if(pos - last[3] == 6) {
                    // 区分 XOO____OOX    (双3)
                    //   和 XO__O___OX    (眠3)
                    if((pat9 >> (pos - 4) & 0xC03) == 0x401) {
                        if(PT_SHUA3 > s.atkLevel) {
                            s.atkLevel = PT_SHUA3;
                        }
                    }
                }
                last[3] = pos;
                break;
            case 2: // 成2
                // 第一次成2
                if(pos - last[2] > 20) {
                    if(PT_MIAN2 > s.atkLevel) {
                        s.atkLevel = PT_MIAN2;
                    }
                }
                // 连续两个 2
                else if(pos - last[2] == 2) {
                    // 空格 -> 空格
                    if(transMark == 0x000) {
                        if(PT_LIAN2 > s.atkLevel) {
                            s.atkLevel = PT_LIAN2;
                        }
                    }
                }
                last[2] = pos;
                break;
            case 1: // 成1
                break;
            default:
                throw "ERROR: never here!";
                break;
            } // switch

            // 读取下一格，更新 transMask
            transMark = pat9 >> pos & 0xC03;
            switch(transMark) {
            case 0x000: // 空格 -> 空格
                break;
            case 0x001: // 棋子 -> 空格
                --attackLevel;
                break;
            case 0x400: // 空格 -> 棋子
                ++attackLevel;
                break;
            case 0x401: // 棋子 -> 棋子
                break;
            default:    // 有墙，跳过
                pos += 10;
                break;
            } // switch
        } // for

        return s;
    }
};


/////////////////////////////////////////////////////////////////////////////
// Pattern13 直接使用 Pattern5，部分代码与 Pattern9 类似，但多出了对 pat5 两边
// 棋子的判断部分。
// 
// 其中攻击判断部分按 Pattern11 来进行，只考虑中间 11 格的情况，只有在算分的时候才考虑 13 格
// 当 Pattern5 的 attackLevel == 5 时判断 pat5 两边是否有棋子来确定长连
// 除此以外的情况当 pat5 两边有棋子时 score 置 0，且 state.atkLevel 置为 PT_INVMV
// 

// hash 只保存 Pattern11 的情况。
// Pattern11 只保存中间格是空格的情况，有效数量为 3^10 = 59049 个，用 hash 保存。
// 开辟三倍空间即为 170003 (取质数) 个。（占据空间为 664 kB）
// 

class Pattern13 {
public:
    struct State {
        char midScore;  // 中间格放入棋子后得分的增量（有可能为负）
        char allScore;  // 中间格放入墙后会失掉的得分
        unsigned char atkLevel;  // 中间格的进攻种类
    };

    Pattern13() {
        if(objCount++ == 0) {
            buf = (P11State *)malloc(HASH_SIZE * sizeof(P11State));
            if(buf == NULL) {
                throw "ERROR: Not Enough Memory!\n";
            }
            // 将所有 buf[i].pat11 都初始化为 0x2AAAAA (0b 10 1010 1010 ...) 的无效值
            memset(buf, 0xAA, HASH_SIZE * sizeof(P11State));
        }
    }
    ~Pattern13() {
        if(--objCount == 0) {
            free(buf);
        }
    }

    State getState(const unsigned pat13) {
        // 越界检查
        assert(pat13 < (1 << 26));
        // 中间格是空格
        assert(get_bits(pat13, 12, 2) == BLANK);

        unsigned pat11 = (pat13 >> 2) & 0x3FFFFF;
        unsigned p11hash = calcP11Hash(pat11);
        P11State p11s;

        unsigned pos = p11hash % HASH_SIZE;
        if(buf[pos].p11hash == p11hash) {
            p11s = buf[pos];
        }
        else if(buf[pos].p11hash == INVALID_HASH) {
            p11s = buf[pos] = calcPattern11(pat11);
        }
        else {
            unsigned offsetpos, i = 0;
            for(;;) {
                ++i;
                offsetpos = (pos + i*i) % HASH_SIZE;
                if(buf[offsetpos].p11hash == p11hash) {
                    p11s = buf[offsetpos];
                    break;
                }
                else if(buf[offsetpos].p11hash == INVALID_HASH) {
                    p11s = buf[offsetpos] = calcPattern11(pat11);
                    break;
                }

                ++i;
                offsetpos = (pos - i*i) % HASH_SIZE;
                if(buf[offsetpos].p11hash == p11hash) {
                    p11s = buf[offsetpos];
                    break;
                }
                else if(buf[offsetpos].p11hash == INVALID_HASH) {
                    p11s = buf[offsetpos] = calcPattern11(pat11);
                    break;
                }
            }
            //throw "ERROR: Hash Table is FULL!\n";
        } // else

        State p13s;
        p13s.midScore = static_cast<char>(p11s.midScore);
        p13s.allScore = static_cast<char>(p11s.allScore);
        p13s.atkLevel = p11s.atkLevel;
        if((pat13 & 0x3) != STONE){
            p13s.midScore -= static_cast<char>((objPat5.getState((pat13 >> 2) & 0x3FF) & 0xF) - 1);
        }
        if(((pat13 >> 24) & 0x3) != STONE){
            p13s.midScore -= static_cast<char>((objPat5.getState((pat13 >> 14) & 0x3FF) & 0xF) - 1);
        }

        return p13s;
    }

private:
    struct P11State {
        // 为了使构造函数中对 pat11 的赋初值 0x2AAAAA 正确生效
        // 以下位域必须偶数位对齐
        unsigned midScore:  3;  // 中间格放入棋子的得分增量
        unsigned allScore:  5;  // 只算中间 9 格的外势得分
        unsigned atkLevel:  4;  // 中间格的进攻种类
        unsigned p11hash:  20;  // 排除中间空格后的 Pattern11
        P11State()
            : midScore(0), allScore(0), atkLevel(PT_INVMV),
            p11hash(INVALID_HASH) {}
        P11State(const unsigned Pat11)
            : midScore(0), allScore(0), atkLevel(PT_INVMV),
            p11hash(calcP11Hash(Pat11)) {}
    };

private:
    // 大于 3^11 * 3 的质数
    static const unsigned HASH_SIZE = 170003u;
    // 0b 101010 10101010 10101010 共20位
    static const unsigned INVALID_HASH = 0xAAAAA;

    // hash 表的存储空间
    static P11State *buf;

    // 记录 Pattern11 对象的数量，只在初次构建对象时初始化 buf
    static int objCount;

    // 共用的 Pattern5 成员
    static Pattern5 objPat5;

    static unsigned calcP11Hash(unsigned pat11) {
        return ((pat11 >> 2) & 0xFFC00) | (pat11 & 0x3FF);
    }

    // 根据 pat11 求得对应的 State
    P11State calcPattern11(const unsigned pat11) const {
        // 越界检查 (< 0b 100 0000 0000 0000 0000 0000)
        assert(pat11 < (1<<22));

        P11State s(pat11);

        // 前 5 格 (不包括边界2格) 的攻击类型
        unsigned attackLevel = objPat5.getState(get_bits(pat11, 2, 10));
        // 前 5 格偏移的位置
        unsigned pos = attackLevel >> 4;

        // 如果 pos > 0，说明前 5 格中有墙，跳过后重新判断
        if(pos > 0) {
            attackLevel = objPat5.getState(get_bits(pat11, pos + 2, 10));

            // 如果 attLevel.jump > 0，说明 pat9 中有间隔刚好为 5 的墙，直接返回无效 s
            if(attackLevel > 0xF) {
                return s;
            }
        }

        // 记录上次棋子迁移的形态
        // 0x000    空格 -> 空格
        // 0x001    棋子 -> 空格
        // 0x400    空格 -> 棋子
        // 0x401    棋子 -> 棋子
        // 初始化为任一无效值
        unsigned transMark = 0x111;

        // 记录 pos 位置的边界2格情况
        unsigned sideGrid = pat11 >> pos;
        // 使第 0 格和第 6 格的两位异或，只有是棋子 (01) 的时候结果才是非零
        sideGrid = (sideGrid ^ (sideGrid >> 1)) & 0x1001;


        // 上次成 i 子的位置
        unsigned last[5];
        // 初始化为很大的数
        memset(last, 0x40, sizeof(last));

        // 从 pos 处开始依次判断
        for(; pos < 10; pos += 2) {
            // 边界不是棋子时，棋子数计入 score 并判断攻击类型
            if(sideGrid == 0) {
                s.allScore += attackLevel - 1;
                ++s.midScore;

                // 根据 attLevel 区分攻击类型
                switch(attackLevel) {
                case 5: // 成5
                    // 边界无棋子，一定是五连
                    s.atkLevel = PT_LIAN5;
                    break;
                case 4: // 成4
                    // last[4] 初始化为很大的数，以 > 10 判断是否第一次成4
                    if(pos - last[4] > 20) {
                        if(PT_CHON4 > s.atkLevel) {
                            s.atkLevel = PT_CHON4;
                        }
                    }
                    // 连续两个 4
                    else if(pos - last[4] == 2) {
                        // 空格 -> 空格迁移，则为活4
                        if(transMark == 0x000) {
                            if(PT_LIAN4 > s.atkLevel) {
                                s.atkLevel = PT_LIAN4;
                            }
                        }
                    }
                    // 非连续的两个 4 即为双四
                    else {
                        if(PT_SHUA4 > s.atkLevel) {
                            s.atkLevel = PT_SHUA4;
                        }
                    }
                    last[4] = pos;
                    break;
                case 3: // 成3
                    // 第一次成3
                    if(pos - last[3] > 20) {
                        if(PT_MIAN3 > s.atkLevel) {
                            s.atkLevel = PT_MIAN3;
                        }
                    }
                    // 连续两个 3
                    else if(pos - last[3] == 2) {
                        // 空格 -> 空格
                        if(transMark == 0x000) {
                            if(PT_LIAN3 > s.atkLevel) {
                                s.atkLevel = PT_LIAN3;
                            }
                        }
                    }
                    // 3 2 3
                    // XO_O___OX
                    // XO__O__OX
                    else if(pos - last[3] == 4) {
                        if(PT_SHUA3 > s.atkLevel) {
                            s.atkLevel = PT_SHUA3;
                        }
                    }
                    // 3 2 2 3
                    // 也可能是 3 4 4 3，这种情况会被 4 覆盖，所以不用单独判断。
                    else if(pos - last[3] == 6) {
                        // 区分 OO____OOX    (双3)
                        //   和 O__O___OX    (眠3)
                        if((pat11 >> (pos - 2) & 0xC03) == 0x401) {
                            if(PT_SHUA3 > s.atkLevel) {
                                s.atkLevel = PT_SHUA3;
                            }
                        }
                    }
                    last[3] = pos;
                    break;
                case 2: // 成2
                    // 第一次成2
                    if(pos - last[2] > 20) {
                        if(PT_MIAN2 > s.atkLevel) {
                            s.atkLevel = PT_MIAN2;
                        }
                    }
                    // 连续两个 2
                    else if(pos - last[2] == 2) {
                        // 空格 -> 空格
                        if(transMark == 0x000) {
                            if(PT_LIAN2 > s.atkLevel) {
                                s.atkLevel = PT_LIAN2;
                            }
                        }
                    }
                    last[2] = pos;
                    break;
                case 1: // 成1
                    break;
                default:
                    throw "ERROR: never here!";
                    break;
                } // switch
            } // if(sideGrid == 0)
            // 边界有棋子的话，需判断长连
            else {
                if(attackLevel == 5) {
                    s.atkLevel = PT_LIAN6;
                }
            }


            // 读取下一格，更新 transMask 和 sideGrid
            transMark = pat11 >> (pos + 2) & 0xC03;

            sideGrid = pat11 >> (pos + 2);
            sideGrid = (sideGrid ^ (sideGrid >> 1)) & 0x1001;

            switch(transMark) {
            case 0x000: // 空格 -> 空格
                break;
            case 0x001: // 棋子 -> 空格
                --attackLevel;
                break;
            case 0x400: // 空格 -> 棋子
                ++attackLevel;
                break;
            case 0x401: // 棋子 -> 棋子
                break;
            default:    // 有墙，跳过
                pos += 10;
                break;
            } // switch
        } // for

        return s;
    }
};











