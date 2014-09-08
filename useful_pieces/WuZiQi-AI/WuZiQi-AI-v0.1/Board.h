/********************************************************

棋盘尺寸为 int BitBoard::board_size
棋子坐标为 (x, y), 其中 x, y 的范围是 [0, board_size - 1]
------------------------------------------
    0   1   2   --->    y   width
0
1
2

|
|
V

x
height
------------------------------------------
*********************************************************/

#pragma once

#include <vector>
#include "PatternMatch.h"

enum COLOR {EMPTY = 0, BLACK = 1, WHITE = 2, BLOCK = 3};

class BitBoard
{
public:
    typedef unsigned long long Line;
private:
    unsigned board_height;  // 0 <= x < height
    unsigned board_width;   // 0 <= y < width

    std::vector<Line> blackbits_456, whitebits_456;    // =
    std::vector<Line> blackbits_852, whitebits_852;    // ||
    std::vector<Line> blackbits_159, whitebits_159;    // //
    std::vector<Line> blackbits_753, whitebits_753;    // \\\

    unsigned line_row_159(const unsigned x, const unsigned y) const
    {   // 求得 (x, y) 点以 159 的斜行数算第几行
        return x + y;
    }
    unsigned line_row_753(const unsigned x, const unsigned y) const
    {   // 求得 (x, y) 点以 753 的斜行数算第几行
        return board_width + x - y - 1;
    }
    unsigned line_offset_159(const unsigned x, const unsigned y) const
    {   // 求得 (x, y) 点在 159 的斜行中位置
        return (x + y > board_height - 1)?
            (board_height - x - 1): y;
    }
    unsigned line_offset_753(const unsigned x, const unsigned y) const
    {   // 求得 (x, y) 点在 753 的斜行中的位置
        return (x > y)? y: x;
    }

public:
    BitBoard(unsigned Width = 15, unsigned Height = 15)
        : board_width(Width), board_height(Height)
    {
        reset_board();
    }
    void set_size(unsigned Width, unsigned Height)
    {
        if(Width == board_width && Height == board_height) return;
        board_width = Width;
        board_height = Height;
        reset_board();
    }

    void reset_board()
    {
        blackbits_456.assign(board_height, ~0ull << (board_width * 2 + 8) | 0x7F);
        blackbits_852.assign(board_width, ~0ull << (board_height * 2 + 8) | 0x7F);
        whitebits_456.assign(board_height, ~0ull << (board_width * 2 + 8) | 0x7F);
        whitebits_852.assign(board_width, ~0ull << (board_height * 2 + 8) | 0x7F);

        blackbits_159.resize(board_width + board_height - 1);
        blackbits_753.resize(board_width + board_height - 1);
        whitebits_159.resize(board_width + board_height - 1);
        whitebits_753.resize(board_width + board_height - 1);

        for(int i=0; i<(int)board_height; ++i)
        {
            for(int j=0; j<(int)board_width; ++j)
            {
                blackbits_159[line_row_159(i, j)] = ~0ull << (line_size_159(i, j) * 2 + 8) | 0x7F;
                whitebits_159[line_row_159(i, j)] = ~0ull << (line_size_159(i, j) * 2 + 8) | 0x7F;
                blackbits_753[line_row_753(i, j)] = ~0ull << (line_size_753(i, j) * 2 + 8) | 0x7F;
                whitebits_753[line_row_753(i, j)] = ~0ull << (line_size_753(i, j) * 2 + 8) | 0x7F;
            }
        }
    }
    unsigned line_size_159(const unsigned x, const unsigned y) const
    {   // 取得 (x, y) 所在的 159 斜线的长度
        if(board_width >= board_height)
        {
            if(x + y <= board_height - 1)
            {
                return x + y + 1;
            }
            else if(x + y >= board_width - 1)
            {
                return board_width + board_height - x - y - 1;
            }
            else
            {
                return board_height;
            }
        }
        else
        {
            if(x + y <= board_width - 1)
            {
                return x + y + 1;
            }
            else if(x + y >= board_height - 1)
            {
                return board_width + board_height - x - y - 1;
            }
            else
            {
                return board_width;
            }
        }
    }
    unsigned line_size_753(const unsigned x, const unsigned y) const
    {   // 取得 (x, y) 所在的 753 斜线的长度
        if(board_width >= board_height)
        {
            if(x >= y)
            {
                return board_height - x + y;
            }
            else if(x + board_width - board_height <= y)
            {
                return board_width + x - y;
            }
            else
            {
                return board_height;
            }
        }
        else
        {
            if(x <= y)
            {
                return board_width + x - y;
            }
            else if(x >= y + board_height - board_width)
            {
                return board_height - x + y;
            }
            else
            {
                return board_width;
            }
        }
    }

    Line black_linebits_456(const unsigned x, const unsigned y) const
    {   // 组合出 (x, y) 所在横行的黑棋的 Line bits
        return blackbits_456[x] | whitebits_456[x] | whitebits_456[x] << 1;
    }
    Line black_linebits_852(const unsigned x, const unsigned y) const
    {   // 组合出 (x, y) 所在竖行的黑棋的 Line bits
        return blackbits_852[y] | whitebits_852[y] | whitebits_852[y] << 1;
    }
    Line black_linebits_159(const unsigned x, const unsigned y) const
    {   // 组合出 (x, y) 所在 159 方向斜行的黑棋的 Line bits
        unsigned row = line_row_159(x, y);
        return blackbits_159[row] | whitebits_159[row] | whitebits_159[row] << 1;
    }
    Line black_linebits_753(const unsigned x, const unsigned y) const
    {   // 组合出 (x, y) 所在 753 方向斜行的黑棋的 Line bits
        unsigned row = line_row_753(x, y);
        return blackbits_753[row] | whitebits_753[row] | whitebits_753[row] << 1;
    }

    Line white_linebits_456(const unsigned x, const unsigned y) const
    {   // 组合出 (x, y) 所在横行的白棋的 Line bits
        return whitebits_456[x] | blackbits_456[x] | blackbits_456[x] << 1;
    }
    Line white_linebits_852(const unsigned x, const unsigned y) const
    {   // 组合出 (x, y) 所在竖行的白棋的 Line bits
        return whitebits_852[y] | blackbits_852[y] | blackbits_852[y] << 1;
    }
    Line white_linebits_159(const unsigned x, const unsigned y) const
    {   // 组合出 (x, y) 所在 159 方向斜行的白棋的 Line bits
        unsigned row = line_row_159(x, y);
        return whitebits_159[row] | blackbits_159[row] | blackbits_159[row] << 1;
    }
    Line white_linebits_753(const unsigned x, const unsigned y) const
    {   // 组合出 (x, y) 所在 753 方向斜行的白棋的 Line bits
        unsigned row = line_row_753(x, y);
        return whitebits_753[row] | blackbits_753[row] | blackbits_753[row] << 1;
    }

    unsigned black_vici9bits_456(const short x, const short y/*, const short offset = 0*/) const
    {   // 返回以 (x, y) 为中心的 456 方向的 9 格 bits，可直接用作 Pattern9 的 pattern
        return black_linebits_456(x, y) >> ((y /*+ offset*/) * 2) & 0x3FFFF;
    }
    unsigned black_vici9bits_852(const short x, const short y/*, const short offset = 0*/) const
    {
        return black_linebits_852(x, y) >> ((x /*+ offset*/) * 2) & 0x3FFFF;
    }
    unsigned black_vici9bits_159(const short x, const short y/*, const short offset = 0*/) const
    {
        return black_linebits_159(x, y) >> ((line_offset_159(x, y) /*+ offset*/) * 2) & 0x3FFFF;
    }
    unsigned black_vici9bits_753(const short x, const short y/*, const short offset = 0*/) const
    {
        return black_linebits_753(x, y) >> ((line_offset_753(x, y) /*+ offset*/) * 2) & 0x3FFFF;
    }
    unsigned white_vici9bits_456(const short x, const short y/*, const short offset = 0*/) const
    {   // 返回以 (x, y) 为中心的 456 方向的 9 格 bits，可直接用作 Pattern9 的 pattern
        return white_linebits_456(x, y) >> ((y /*+ offset*/) * 2) & 0x3FFFF;
    }
    unsigned white_vici9bits_852(const short x, const short y/*, const short offset = 0*/) const
    {
        return white_linebits_852(x, y) >> ((x /*+ offset*/) * 2) & 0x3FFFF;
    }
    unsigned white_vici9bits_159(const short x, const short y/*, const short offset = 0*/) const
    {
        return white_linebits_159(x, y) >> ((line_offset_159(x, y) /*+ offset*/) * 2) & 0x3FFFF;
    }
    unsigned white_vici9bits_753(const short x, const short y/*, const short offset = 0*/) const
    {
        return white_linebits_753(x, y) >> ((line_offset_753(x, y) /*+ offset*/) * 2) & 0x3FFFF;
    }

    void add_stone(const short x, const short y, const COLOR c)
    {   // 增加 4 格偏移
        switch(c)
        {
        case BLACK:
            blackbits_456[x] |= 0x1ull << (y * 2 + 8);
            blackbits_852[y] |= 0x1ull << (x * 2 + 8);
            blackbits_159[line_row_159(x, y)] |= 0x1ull << (line_offset_159(x, y) * 2 + 8);
            blackbits_753[line_row_753(x, y)] |= 0x1ull << (line_offset_753(x, y) * 2 + 8);
            break;
        case WHITE:
            whitebits_456[x] |= 0x1ull << (y * 2 + 8);
            whitebits_852[y] |= 0x1ull << (x * 2 + 8);
            whitebits_159[line_row_159(x, y)] |= 0x1ull << (line_offset_159(x, y) * 2 + 8);
            whitebits_753[line_row_753(x, y)] |= 0x1ull << (line_offset_753(x, y) * 2 + 8);
            break;
        case BLOCK:
            // Nothing to do...
            break;
        default:
            break;
        }
    }

    void remove_stone(const short x, const short y, const COLOR c)
    {   // 增加 4 格偏移
        switch(c)
        {
        case BLACK:
            blackbits_456[x] &= ~(0x3ull << (y * 2 + 8));
            blackbits_852[y] &= ~(0x3ull << (x * 2 + 8));
            blackbits_159[line_row_159(x, y)] &= ~(0x3ull << (line_offset_159(x, y) * 2 + 8));
            blackbits_753[line_row_753(x, y)] &= ~(0x3ull << (line_offset_753(x, y) * 2 + 8));
            break;
        case WHITE:
            whitebits_456[x] &= ~(0x3ull << (y * 2 + 8));
            whitebits_852[y] &= ~(0x3ull << (x * 2 + 8));
            whitebits_159[line_row_159(x, y)] &= ~(0x3ull << (line_offset_159(x, y) * 2 + 8));
            whitebits_753[line_row_753(x, y)] &= ~(0x3ull << (line_offset_753(x, y) * 2 + 8));
            break;
        case BLOCK:
            // Nothing to do...
            break;
        default:
            break;
        }
    }
};

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//*
const int MAX_BOARD_SIZE = 25;

class UniquePosStack
{
private:
    std::vector<unsigned> check;
    std::vector<unsigned> pos_stack;

    unsigned pos2idx(const unsigned Pos) const
    {
        return (Pos >> 8) * MAX_BOARD_SIZE + (Pos & 0xF);
    }
public:
    UniquePosStack()
    {
        clear();
    }
    void clear()
    {
        check.assign(MAX_BOARD_SIZE * MAX_BOARD_SIZE, 0u);
        pos_stack.clear();
        pos_stack.reserve(MAX_BOARD_SIZE * MAX_BOARD_SIZE);
    }
    bool push(const unsigned &Pos)
    {   // 入栈成功返回 true，元素已存在返回 false
        // Pos = x << 8 | y
        unsigned idx = pos2idx(Pos);
        if(check[idx] == 0)
        {
            ++check[idx];
            pos_stack.push_back(Pos);
            return true;
        }
        return false;
    }
    const unsigned& top() const
    {
        return pos_stack.back();
    }
    void pop()
    {
        check[pos2idx(pos_stack.back())] = 0u;
        pos_stack.pop_back();
    }
    int size()
    {
        return pos_stack.size();
    }
    const unsigned& operator[](const int idx) const
    {
        return pos_stack[idx];
    }
};

class Board
{
public:
    //static const unsigned MAX_STACK_DEPTH = 100;
    static const unsigned INVPOS = ~0x0;
    enum {
        LIAN5_BIT = 0x1 << 12,  // 4 bits
        SHUA4_BIT = 0x1 << 8,   // 4 bits
        CHON4_BIT = 0x1 << 7,   // 1 bit
        SHUA3_BIT = 0x1 << 4,   // 3 bits
        HUO3_BIT  = 0x1 << 3,   // 1 bit
        MIAN3_BIT = 0x1,        // 3 bits
    };
private:
    struct Pos_Color_State{
        unsigned prev;      // 指向同状态链表的上一个元素 (x, y) -->  x << 8 | y
        unsigned next;      // 指向同状态链表的下一个元素 (x, y) -->  x << 8 | y

        unsigned state;     // = state_456 + 852 + 159 + 753，区分五连/双四/冲四/双三/活三/眠三

        // 防点用相应方向上的偏移表示，0 ~ 8 分别表示 -4 ~ +4 偏移
        // 每2字节表示一个方向的攻击方式及防点: 高位| 753 | 159 | 852 | 456 |低位
        // 2字节内：0000 防3 防2 防1/标志(Pattern9::LIAN5 / SHUA4 / CHON4 / MIAN3 / 活三<MAXMK / INVMK)
        // 相当于 Pattern9::State 中 move0~4 >> 4 的结果
        unsigned long long defend;

        Pos_Color_State(): prev(INVPOS), next(INVPOS), state(0), 
            defend(unsigned long long(Pattern9::INVMK) << 16*3
                | unsigned long long(Pattern9::INVMK) << 16*2
                | unsigned long long(Pattern9::INVMK) << 16
                | unsigned long long(Pattern9::INVMK)){}
    };

    struct Pos_State
    {
        Pos_Color_State black;
        Pos_Color_State white;
    };

    unsigned board_width, board_height;
    std::vector<Pos_State> board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

    struct Board_State
    {
        struct Color_Point_List
        {
            struct Point_List
            {
                unsigned root;
                unsigned num;
                Point_List()
                    :root(INVPOS), num(0) {}
            };
            Point_List lian5;
            Point_List shua4;
            Point_List chn43;
            Point_List chon4;
            Point_List shua3;
            Point_List huo3;
            Point_List mian3;
        };
        int black_score, white_score;
        Color_Point_List black, white;
        Board_State(): black_score(0), white_score(0){}
    };
    std::vector<Board_State> state; // board state stack

    // 记录状态有变化的点，这些点会 push Pos_State
    // 每一层首先 push 放入棋子的点 (x, y)
    // 出栈时判断 .top() == (x, y) 即出栈结束。
    std::vector<unsigned> log_points;
    // 每个位置只允许在栈中存储一次，存多次时后几次无效
    UniquePosStack ups;

    BitBoard bitboard;
    static Pattern9 pat9;

    void vici_score(const short x, const short y, int &black_score, int &white_score)
    {
        Pattern9::State vici_state;
        vici_state = pat9(bitboard.black_vici9bits_456(x, y));
        black_score += vici_state.score;
        vici_state = pat9(bitboard.black_vici9bits_852(x, y));
        black_score += vici_state.score;
        vici_state = pat9(bitboard.black_vici9bits_159(x, y));
        black_score += vici_state.score;
        vici_state = pat9(bitboard.black_vici9bits_753(x, y));
        black_score += vici_state.score;
        vici_state = pat9(bitboard.white_vici9bits_456(x, y));
        white_score += vici_state.score;
        vici_state = pat9(bitboard.white_vici9bits_852(x, y));
        white_score += vici_state.score;
        vici_state = pat9(bitboard.white_vici9bits_159(x, y));
        white_score += vici_state.score;
        vici_state = pat9(bitboard.white_vici9bits_753(x, y));
        white_score += vici_state.score;
    }
    //void push_ups(const unsigned Pos)
    //{
    //    std::vector<Pos_State> &s = board[Pos >> 8][Pos & 0xFF];
    //    if(ups.push(Pos))
    //    {
    //        s.push_back(s.back());
    //    }
    //}
    //void push_ups(const short x, const short y)
    //{
    //    std::vector<Pos_State> &s = board[x][y];
    //    if(ups.push(x << 8 | y))
    //    {
    //        s.push_back(s.back());
    //    }
    //}

    void try_update_vici_state(const short x, const short y)
    {   // 四方向分别更新 x,y 临近的空格状态，有变化则入栈 board_state，并加入 ups

        unsigned vici9bits;
        Pattern9::State vs;
        unsigned cdef;

        {   // 更新棋子点
            std::vector<Pos_State> &ccs = board[x][y];
            ups.push(x << 8 | y);
            ccs.push_back(ccs.back());
            ccs.back().black.defend = ccs.back().white.defend
                = unsigned long long(Pattern9::INVMK) << 16*3
                | unsigned long long(Pattern9::INVMK) << 16*2
                | unsigned long long(Pattern9::INVMK) << 16
                | unsigned long long(Pattern9::INVMK);
        }

        // black 四方向判断
        vici9bits = bitboard.black_vici9bits_456(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // 非空格，直接跳过
            if(vici9bits >> (i * 2) & 0x3) continue;

            int cx = x;
            int cy = y + i - 4;
            std::vector<Pos_State> &cs = board[cx][cy];
            vs = pat9(bitboard.black_vici9bits_456(cx, cy));
            cdef = cs.back().black.defend & 0xFFFF; // 456
            if((vs.move0 & 0xF) != 4 && cdef != Pattern9::INVMK)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().black.defend, 0, 16, Pattern9::INVMK);
            }
            else if((vs.move0 & 0xF) == 4 && cdef != vs.move0 >> 4)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().black.defend, 0, 16, vs.move0 >> 4);
            }
        }
        vici9bits = bitboard.black_vici9bits_852(x, y);             //
        for(int i = 0; i < 9; ++i)
        {
            // 非空格，直接跳过
            if(vici9bits >> (i * 2) & 0x3) continue;

            int cx = x + i - 4; //
            int cy = y;         //
            std::vector<Pos_State> &cs = board[cx][cy];
            vs = pat9(bitboard.black_vici9bits_852(cx, cy));        //
            cdef = cs.back().black.defend >> 16 & 0xFFFF;  // 852
            if((vs.move0 & 0xF) != 4 && cdef != Pattern9::INVMK)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().black.defend, 16, 16, Pattern9::INVMK);  //
            }
            else if((vs.move0 & 0xF) == 4 && cdef != vs.move0 >> 4)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().black.defend, 16, 16, vs.move0 >> 4);    //
            }
        }
        vici9bits = bitboard.black_vici9bits_159(x, y);             //
        for(int i = 0; i < 9; ++i)
        {
            // 非空格，直接跳过
            if(vici9bits >> (i * 2) & 0x3) continue;

            int cx = x + 4 - i; //
            int cy = y + i - 4; //
            std::vector<Pos_State> &cs = board[cx][cy];
            vs = pat9(bitboard.black_vici9bits_159(cx, cy));        //
            cdef = cs.back().black.defend >> 32 & 0xFFFF;  // 159
            if((vs.move0 & 0xF) != 4 && cdef != Pattern9::INVMK)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().black.defend, 32, 16, Pattern9::INVMK);  //
            }
            else if((vs.move0 & 0xF) == 4 && cdef != vs.move0 >> 4)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().black.defend, 32, 16, vs.move0 >> 4);    //
            }
        }
        vici9bits = bitboard.black_vici9bits_753(x, y);             //
        for(int i = 0; i < 9; ++i)
        {
            // 非空格，直接跳过
            if(vici9bits >> (i * 2) & 0x3) continue;

            int cx = x + i - 4; //
            int cy = y + i - 4; //
            std::vector<Pos_State> &cs = board[cx][cy];
            vs = pat9(bitboard.black_vici9bits_753(cx, cy));        //
            cdef = cs.back().black.defend >> 48 & 0xFFFF;  // 753
            if((vs.move0 & 0xF) != 4 && cdef != Pattern9::INVMK)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().black.defend, 48, 16, Pattern9::INVMK);  //
            }
            else if((vs.move0 & 0xF) == 4 && cdef != vs.move0 >> 4)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().black.defend, 48, 16, vs.move0 >> 4);    //
            }
        }

        // white 四方向判断
        vici9bits = bitboard.white_vici9bits_456(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // 非空格，直接跳过
            if(vici9bits >> (i * 2) & 0x3) continue;

            int cx = x;
            int cy = y + i - 4;
            std::vector<Pos_State> &cs = board[cx][cy];
            vs = pat9(bitboard.white_vici9bits_456(cx, cy));
            cdef = cs.back().white.defend & 0xFFFF; // 456
            if((vs.move0 & 0xF) != 4 && cdef != Pattern9::INVMK)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().white.defend, 0, 16, Pattern9::INVMK);
            }
            else if((vs.move0 & 0xF) == 4 && cdef != vs.move0 >> 4)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().white.defend, 0, 16, vs.move0 >> 4);
            }
        }
        vici9bits = bitboard.white_vici9bits_852(x, y);             //
        for(int i = 0; i < 9; ++i)
        {
            // 非空格，直接跳过
            if(vici9bits >> (i * 2) & 0x3) continue;

            int cx = x + i - 4; //
            int cy = y;         //
            std::vector<Pos_State> &cs = board[cx][cy];
            vs = pat9(bitboard.white_vici9bits_852(cx, cy));        //
            cdef = cs.back().white.defend >> 16 & 0xFFFF;  // 852
            if((vs.move0 & 0xF) != 4 && cdef != Pattern9::INVMK)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().white.defend, 16, 16, Pattern9::INVMK);  //
            }
            else if((vs.move0 & 0xF) == 4 && cdef != vs.move0 >> 4)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().white.defend, 16, 16, vs.move0 >> 4);    //
            }
        }
        vici9bits = bitboard.white_vici9bits_159(x, y);             //
        for(int i = 0; i < 9; ++i)
        {
            // 非空格，直接跳过
            if(vici9bits >> (i * 2) & 0x3) continue;

            int cx = x + 4 - i; //
            int cy = y + i - 4; //
            std::vector<Pos_State> &cs = board[cx][cy];
            vs = pat9(bitboard.white_vici9bits_159(cx, cy));        //
            cdef = cs.back().white.defend >> 32 & 0xFFFF;  // 159
            if((vs.move0 & 0xF) != 4 && cdef != Pattern9::INVMK)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().white.defend, 32, 16, Pattern9::INVMK);  //
            }
            else if((vs.move0 & 0xF) == 4 && cdef != vs.move0 >> 4)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().white.defend, 32, 16, vs.move0 >> 4);    //
            }
        }
        vici9bits = bitboard.white_vici9bits_753(x, y);             //
        for(int i = 0; i < 9; ++i)
        {
            // 非空格，直接跳过
            if(vici9bits >> (i * 2) & 0x3) continue;

            int cx = x + i - 4; //
            int cy = y + i - 4; //
            std::vector<Pos_State> &cs = board[cx][cy];
            vs = pat9(bitboard.white_vici9bits_753(cx, cy));        //
            cdef = cs.back().white.defend >> 48 & 0xFFFF;  // 753
            if((vs.move0 & 0xF) != 4 && cdef != Pattern9::INVMK)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().white.defend, 48, 16, Pattern9::INVMK);  //
            }
            else if((vs.move0 & 0xF) == 4 && cdef != vs.move0 >> 4)
            {
                if(ups.push(cx << 8 | cy))
                {cs.push_back(cs.back());}
                set_bits(cs.back().white.defend, 48, 16, vs.move0 >> 4);    //
            }
        }
    }
    void try_update_pos_state(const short x, const short y)
    {   // 根据各方向状态更新 x,y 的总状态，更新前后指针，并更新相应前后结点入栈 ups
        unsigned state_sum;

        ////////////////////// black //////////////////////////
        state_sum = 0;
        Pos_Color_State &bs = board[x][y].back().black;
        Pos_Color_State &lbs = (board[x][y].rbegin() + 1)->black;
        for(int offset = 0; offset <= 48; offset += 16)
        {
            unsigned s = bs.defend >> offset & 0xFFFF;
            switch(s & 0xF)
            {
            case Pattern9::LIAN5:
                state_sum += LIAN5_BIT;
                break;
            case Pattern9::SHUA4:
                state_sum += SHUA4_BIT;
                break;
            case Pattern9::CHON4:
                state_sum += CHON4_BIT;
                break;
            case Pattern9::MIAN3:
                state_sum += MIAN3_BIT;
                break;
            case Pattern9::INVMK:
                break;
            default:    // HUO3
                state_sum += HUO3_BIT;
                break;
            }
        }

        // 归一化 state_sum
        if(state_sum < MIAN3_BIT){/*无效点*/}
        else if(state_sum < HUO3_BIT)
        {   // 眠三
            state_sum = MIAN3_BIT;
        }
        else if(state_sum < SHUA3_BIT)
        {   // 活三
            state_sum = HUO3_BIT;
        }
        else if(state_sum < CHON4_BIT)
        {   // 双三
            state_sum = SHUA3_BIT;
        }
        else if(state_sum < (CHON4_BIT | HUO3_BIT))
        {   // 冲四
            state_sum = CHON4_BIT;
        }
        else if(state_sum < SHUA4_BIT)
        {   // 冲四活三
            state_sum = CHON4_BIT | HUO3_BIT;
        }
        else if(state_sum < LIAN5_BIT)
        {   // 双四/四连
            state_sum = SHUA4_BIT;
        }
        else
        {   // 五连
            state_sum = LIAN5_BIT;
        }
        bs.state = state_sum;

        // 判断与上层状态是否相同
        if(state_sum != lbs.state)
        {   // 状态不同，出上层队列，入本层队列。更新队列中元素数
            switch(lbs.state)
            {   // 更新上层元素数，头元素时更新 root 指标
            case LIAN5_BIT:
                --state.back().black.lian5.num;
                if(bs.prev == INVPOS)
                {
                    state.back().black.lian5.root = bs.next;
                }
                break;
            case SHUA4_BIT:
                --state.back().black.shua4.num;
                if(bs.prev == INVPOS)
                {
                    state.back().black.shua4.root = bs.next;
                }
                break;
            case (CHON4_BIT | HUO3_BIT):
                --state.back().black.chn43.num;
                if(bs.prev == INVPOS)
                {
                    state.back().black.chn43.root = bs.next;
                }
                break;
            case CHON4_BIT:
                --state.back().black.chon4.num;
                if(bs.prev == INVPOS)
                {
                    state.back().black.chon4.root = bs.next;
                }
                break;
            case SHUA3_BIT:
                --state.back().black.shua3.num;
                if(bs.prev == INVPOS)
                {
                    state.back().black.shua3.root = bs.next;
                }
                break;
            case HUO3_BIT:
                --state.back().black.huo3.num;
                if(bs.prev == INVPOS)
                {
                    state.back().black.huo3.root = bs.next;
                }
                break;
            case MIAN3_BIT:
                --state.back().black.mian3.num;
                if(bs.prev == INVPOS)
                {
                    state.back().black.mian3.root = bs.next;
                }
                break;
            default:
                break;
            }
            // 出上层队列
            if(bs.prev != INVPOS)
            {
                std::vector<Pos_State> &s = board[bs.prev >> 8][bs.prev & 0xFF];
                if(ups.push(bs.prev))
                {s.push_back(s.back());}
                s.back().black.next = bs.next;
            }
            if(bs.next != INVPOS)
            {
                std::vector<Pos_State> &s = board[bs.next >> 8][bs.next & 0xFF];
                if(ups.push(bs.next))
                {s.push_back(s.back());}
                s.back().black.prev = bs.prev;
            }
            // 入本层队列
            bs.prev = INVPOS;
            switch(bs.state)
            {
            case LIAN5_BIT:
                {
                    ++state.back().black.lian5.num;
                    unsigned first = state.back().black.lian5.root;
                    bs.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().black.prev = x << 8 | y;
                    }
                    state.back().black.lian5.root = x << 8 | y;
                }
                break;
            case SHUA4_BIT:
                {
                    ++state.back().black.shua4.num;
                    unsigned first = state.back().black.shua4.root;
                    bs.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().black.prev = x << 8 | y;
                    }
                    state.back().black.shua4.root = x << 8 | y;
                }
                break;
            case CHON4_BIT | HUO3_BIT:
                {
                    ++state.back().black.chn43.num;
                    unsigned first = state.back().black.chn43.root;
                    bs.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().black.prev = x << 8 | y;
                    }
                    state.back().black.chn43.root = x << 8 | y;
                }
                break;
            case CHON4_BIT:
                {
                    ++state.back().black.chon4.num;
                    unsigned first = state.back().black.chon4.root;
                    bs.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().black.prev = x << 8 | y;
                    }
                    state.back().black.chon4.root = x << 8 | y;
                }
                break;
            case SHUA3_BIT:
                {
                    ++state.back().black.shua3.num;
                    unsigned first = state.back().black.shua3.root;
                    bs.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().black.prev = x << 8 | y;
                    }
                    state.back().black.shua3.root = x << 8 | y;
                }
                break;
            case HUO3_BIT:
                {
                    ++state.back().black.huo3.num;
                    unsigned first = state.back().black.huo3.root;
                    bs.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().black.prev = x << 8 | y;
                    }
                    state.back().black.huo3.root = x << 8 | y;
                }
                break;
            case MIAN3_BIT:
                {
                    ++state.back().black.mian3.num;
                    unsigned first = state.back().black.mian3.root;
                    bs.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().black.prev = x << 8 | y;
                    }
                    state.back().black.mian3.root = x << 8 | y;
                }
                break;
            default:
                bs.next = INVPOS;
                break;
            }
        }

        ////////////////////// white //////////////////////////
        state_sum = 0;
        Pos_Color_State &ws = board[x][y].back().white;
        Pos_Color_State &lws = (board[x][y].rbegin() + 1)->white;
        for(int offset = 0; offset <= 48; offset += 16)
        {
            unsigned s = ws.defend >> offset & 0xFFFF;
            switch(s & 0xF)
            {
            case Pattern9::LIAN5:
                state_sum += LIAN5_BIT;
                break;
            case Pattern9::SHUA4:
                state_sum += SHUA4_BIT;
                break;
            case Pattern9::CHON4:
                state_sum += CHON4_BIT;
                break;
            case Pattern9::MIAN3:
                state_sum += MIAN3_BIT;
                break;
            case Pattern9::INVMK:
                break;
            default:    // HUO3
                state_sum += HUO3_BIT;
                break;
            }
        }

        // 归一化 state_sum
        if(state_sum < MIAN3_BIT){/*无效点*/}
        else if(state_sum < HUO3_BIT)
        {   // 眠三
            state_sum = MIAN3_BIT;
        }
        else if(state_sum < SHUA3_BIT)
        {   // 活三
            state_sum = HUO3_BIT;
        }
        else if(state_sum < CHON4_BIT)
        {   // 双三
            state_sum = SHUA3_BIT;
        }
        else if(state_sum < (CHON4_BIT | HUO3_BIT))
        {   // 冲四
            state_sum = CHON4_BIT;
        }
        else if(state_sum < SHUA4_BIT)
        {   // 冲四活三
            state_sum = CHON4_BIT | HUO3_BIT;
        }
        else if(state_sum < LIAN5_BIT)
        {   // 双四/四连
            state_sum = SHUA4_BIT;
        }
        else
        {   // 五连
            state_sum = LIAN5_BIT;
        }
        ws.state = state_sum;

        // 判断与上层状态是否相同
        if(state_sum != lws.state)
        {   // 状态不同，出上层队列，入本层队列。更新队列中元素数
            switch(lws.state)
            {   // 更新上层元素数，头元素时更新 root 指标
            case LIAN5_BIT:
                --state.back().white.lian5.num;
                if(ws.prev == INVPOS)
                {
                    state.back().white.lian5.root = ws.next;
                }
                break;
            case SHUA4_BIT:
                --state.back().white.shua4.num;
                if(ws.prev == INVPOS)
                {
                    state.back().white.shua4.root = ws.next;
                }
                break;
            case (CHON4_BIT | HUO3_BIT):
                --state.back().white.chn43.num;
                if(ws.prev == INVPOS)
                {
                    state.back().white.chn43.root = ws.next;
                }
                break;
            case CHON4_BIT:
                --state.back().white.chon4.num;
                if(ws.prev == INVPOS)
                {
                    state.back().white.chon4.root = ws.next;
                }
                break;
            case SHUA3_BIT:
                --state.back().white.shua3.num;
                if(ws.prev == INVPOS)
                {
                    state.back().white.shua3.root = ws.next;
                }
                break;
            case HUO3_BIT:
                --state.back().white.huo3.num;
                if(ws.prev == INVPOS)
                {
                    state.back().white.huo3.root = ws.next;
                }
                break;
            case MIAN3_BIT:
                --state.back().white.mian3.num;
                if(ws.prev == INVPOS)
                {
                    state.back().white.mian3.root = ws.next;
                }
                break;
            default:
                break;
            }
            // 出上层队列
            if(ws.prev != INVPOS)
            {
                std::vector<Pos_State> &s = board[ws.prev >> 8][ws.prev & 0xFF];
                if(ups.push(ws.prev))
                {s.push_back(s.back());}
                s.back().white.next = ws.next;
            }
            if(ws.next != INVPOS)
            {
                std::vector<Pos_State> &s = board[ws.next >> 8][ws.next & 0xFF];
                if(ups.push(ws.next))
                {s.push_back(s.back());}
                s.back().white.prev = ws.prev;
            }
            // 入本层队列
            ws.prev = INVPOS;
            switch(ws.state)
            {
            case LIAN5_BIT:
                {
                    ++state.back().white.lian5.num;
                    unsigned first = state.back().white.lian5.root;
                    ws.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().white.prev = x << 8 | y;
                    }
                    state.back().white.lian5.root = x << 8 | y;
                }
                break;
            case SHUA4_BIT:
                {
                    ++state.back().white.shua4.num;
                    unsigned first = state.back().white.shua4.root;
                    ws.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().white.prev = x << 8 | y;
                    }
                    state.back().white.shua4.root = x << 8 | y;
                }
                break;
            case CHON4_BIT | HUO3_BIT:
                {
                    ++state.back().white.chn43.num;
                    unsigned first = state.back().white.chn43.root;
                    ws.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().white.prev = x << 8 | y;
                    }
                    state.back().white.chn43.root = x << 8 | y;
                }
                break;
            case CHON4_BIT:
                {
                    ++state.back().white.chon4.num;
                    unsigned first = state.back().white.chon4.root;
                    ws.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().white.prev = x << 8 | y;
                    }
                    state.back().white.chon4.root = x << 8 | y;
                }
                break;
            case SHUA3_BIT:
                {
                    ++state.back().white.shua3.num;
                    unsigned first = state.back().white.shua3.root;
                    ws.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().white.prev = x << 8 | y;
                    }
                    state.back().white.shua3.root = x << 8 | y;
                }
                break;
            case HUO3_BIT:
                {
                    ++state.back().white.huo3.num;
                    unsigned first = state.back().white.huo3.root;
                    ws.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().white.prev = x << 8 | y;
                    }
                    state.back().white.huo3.root = x << 8 | y;
                }
                break;
            case MIAN3_BIT:
                {
                    ++state.back().white.mian3.num;
                    unsigned first = state.back().white.mian3.root;
                    ws.next = first;
                    if(first != INVPOS)
                    {
                        std::vector<Pos_State> &s = board[first >> 8][first & 0xFF];
                        if(ups.push(first))
                        {s.push_back(s.back());}
                        s.back().white.prev = x << 8 | y;
                    }
                    state.back().white.mian3.root = x << 8 | y;
                }
                break;
            default:
                ws.next = INVPOS;
                break;
            }
        }
    }

    //void clear_try()
    //{
    //    state.resize(1);
    //    for(unsigned x = 0; x < board_height; ++x)
    //    {
    //        for(unsigned y = 0; y < board_width; ++y)
    //        {
    //            board[x][y].resize(1);
    //        }
    //    }
    //    while(!log_points.empty())
    //    {
    //        unsigned pos = log_points.back();
    //        log_points.pop_back();
    //        if(pos > 0xFFFF)
    //        {
    //            bitboard.remove_stone(pos >> 8 & 0xFF, pos & 0xFF, COLOR(pos >> 16));
    //        }
    //    }
    //}

public:
    //Board(void)
    //{
    //    // TODO
    //}
    Board(unsigned Width = 15u, unsigned Height = 15u)
        :bitboard(Width, Height), board_width(Width), board_height(Height)
    {
        // TODO
        state.reserve(50);
        state.assign(1, Board_State());
        log_points.reserve(1000);
        for(unsigned x = 0; x < Height; ++x)
        {
            for(unsigned y = 0; y < Width; ++y)
            {
                board[x][y].reserve(50);
                board[x][y].assign(1, Pos_State());
            }
        }
    }
    void set_size(unsigned Width, unsigned Height)
    {
        board_width = Width;
        board_height = Height;
        reset();
    }
    void reset()
    {
        bitboard.set_size(board_width, board_height);
        state.assign(1, Board_State());
        log_points.clear();
        for(unsigned x = 0; x < board_height; ++x)
        {
            for(unsigned y = 0; y < board_width; ++y)
            {
                board[x][y].assign(1, Pos_State());
            }
        }
    }

    int get_black_score() const
    {
        return state.back().black_score;
    }
    int get_white_score() const
    {
        return state.back().white_score;
    }

    void move(const short x, const short y, const COLOR c)
    {   // 当前状态入栈，根据新棋子更新状态增加栈深度

        // 将新棋子及颜色入栈，作为回退时的终止标志（判断大值）
        log_points.push_back(c << 16 | x << 8 | y);

        state.push_back(state.back());

        // 求得四方向原外势得分
        int original_black_score = 0;
        int original_white_score = 0;
        vici_score(x, y, original_black_score, original_white_score);

        // bitboard 添加棋子
        bitboard.add_stone(x, y, c);

        // 求得四方向新外势得分，并更新 state 的分数
        int new_black_score = 0;
        int new_white_score = 0;
        vici_score(x, y, new_black_score, new_white_score);
        state.back().black_score += new_black_score - original_black_score;
        state.back().white_score += new_white_score - original_white_score;

        ups.clear();
        // 按四个方向分黑白分别更新棋子及临近点状态，若状态变化则入栈对应格 pos_state，并将该点记录在 ups 中
        try_update_vici_state(x, y);

        // 依次更新 ups 中对应位置的综合状态，并修改特殊点链表指针
        // 修改前后结点指针的时候需要将改变的结点也加入 ups 中。
        for(int i = ups.size() - 1; i >= 0; --i)
        {
            try_update_pos_state(ups[i] >> 8, ups[i] & 0xFF);
        }
        
        // 将 ups 中的点入栈 log_points
        for(int i = 0; i < ups.size(); ++i)
        {
            log_points.push_back(ups[i]);
        }

    }
    void move(const unsigned pos, const COLOR c)
    {
        move(pos >> 8, pos & 0xFF, c);
    }
    void backtrace()
    {   // 按照 move 回退一步
        state.pop_back();
        for(;;)
        {
            unsigned pos = log_points.back();
            log_points.pop_back();
            if(pos <= 0xFFFF)
            {
                board[pos >> 8][pos & 0xFF].pop_back();
            }
            else
            {
                bitboard.remove_stone(pos >> 8 & 0xFF, pos & 0xFF, COLOR(pos >> 16));
                break;
            }
        }
    }
    void backtrace(unsigned int &x, unsigned int &y)
    {   // 按照 move 回退一步
        state.pop_back();
        for(;;)
        {
            unsigned pos = log_points.back();
            log_points.pop_back();
            if(pos <= 0xFFFF)
            {
                board[pos >> 8][pos & 0xFF].pop_back();
            }
            else
            {
                x = pos >> 8 & 0xFF;
                y = pos & 0xFF;
                bitboard.remove_stone(pos >> 8 & 0xFF, pos & 0xFF, COLOR(pos >> 16));
                break;
            }
        }
    }

    int black_lian5_num() const
    {
        return state.back().black.lian5.num;
    }
    int black_shua4_num() const
    {
        return state.back().black.shua4.num;
    }
    int black_chn43_num() const
    {
        return state.back().black.chn43.num;
    }
    int black_chon4_num() const
    {
        return state.back().black.chon4.num;
    }
    int black_shua3_num() const
    {
        return state.back().black.shua3.num;
    }
    int black_huo3_num() const
    {
        return state.back().black.huo3.num;
    }
    int black_mian3_num() const
    {
        return state.back().black.mian3.num;
    }
    //
    int white_lian5_num() const
    {
        return state.back().white.lian5.num;
    }
    int white_shua4_num() const
    {
        return state.back().white.shua4.num;
    }
    int white_chn43_num() const
    {
        return state.back().white.chn43.num;
    }
    int white_chon4_num() const
    {
        return state.back().white.chon4.num;
    }
    int white_shua3_num() const
    {
        return state.back().white.shua3.num;
    }
    int white_huo3_num() const
    {
        return state.back().white.huo3.num;
    }
    int white_mian3_num() const
    {
        return state.back().white.mian3.num;
    }

    unsigned black_lian5_begin() const
    {
        return state.back().black.lian5.root;
    }
    unsigned black_shua4_begin() const
    {
        return state.back().black.shua4.root;
    }
    unsigned black_chn43_begin() const
    {
        return state.back().black.chn43.root;
    }
    unsigned black_chon4_begin() const
    {
        return state.back().black.chon4.root;
    }
    unsigned black_shua3_begin() const
    {
        return state.back().black.shua3.root;
    }
    unsigned black_huo3_begin() const
    {
        return state.back().black.huo3.root;
    }
    unsigned black_mian3_begin() const
    {
        return state.back().black.mian3.root;
    }
    unsigned black_next(const unsigned pos) const
    {
        return board[pos >> 8][pos & 0xFF].back().black.next;
    }
    //
    unsigned white_lian5_begin() const
    {
        return state.back().white.lian5.root;
    }
    unsigned white_shua4_begin() const
    {
        return state.back().white.shua4.root;
    }
    unsigned white_chn43_begin() const
    {
        return state.back().white.chn43.root;
    }
    unsigned white_chon4_begin() const
    {
        return state.back().white.chon4.root;
    }
    unsigned white_shua3_begin() const
    {
        return state.back().white.shua3.root;
    }
    unsigned white_huo3_begin() const
    {
        return state.back().white.huo3.root;
    }
    unsigned white_mian3_begin() const
    {
        return state.back().white.mian3.root;
    }
    unsigned white_next(const unsigned pos) const
    {
        return board[pos >> 8][pos & 0xFF].back().white.next;
    }

    void move_at_top(const short x, const short y, COLOR c)
    {   // 在栈顶添加 x, y, c 棋子，并更新棋盘状态。直接更新栈顶值，不入栈
        log_points.push_back(x << 8 | y);
        Pattern9::State s_456 = pat9(bitboard.black_vici9bits_456(x, y));
        // 计算并保存原始 9 pat 得分
        //
        // 

        // 添加棋子 bb.add_stone
        // 计算新 9 pat 得分，根据差值计算新黑白 score
    }

};

/**/