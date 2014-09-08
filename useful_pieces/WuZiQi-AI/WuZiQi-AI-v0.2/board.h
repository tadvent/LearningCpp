/********************************************************

���̳ߴ�Ϊ int BitBoard::board_size
��������Ϊ (x, y), ���� x, y �ķ�Χ�� [0, board_size - 1]
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

��ʱ�� Board ����Ȼά�� ���������� ������
�Ժ���� AI ����Ҫ���ɿ��ǲ���ά������ֻ����������Ϣ��

*********************************************************/

#pragma once

#include <vector>
#include "pattern.h"

enum COLOR {BLACK = 1, WHITE = 2, BLANK = 0, BLOCK = 3};

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
    {   // ��� (x, y) ���� 159 ��б������ڼ���
        return x + y;
    }
    unsigned line_row_753(const unsigned x, const unsigned y) const
    {   // ��� (x, y) ���� 753 ��б������ڼ���
        return board_width + x - y - 1;
    }
    unsigned line_offset_159(const unsigned x, const unsigned y) const
    {   // ��� (x, y) ���� 159 ��б����λ��
        return (x + y > board_height - 1)?
            (board_height - x - 1): y;
    }
    unsigned line_offset_753(const unsigned x, const unsigned y) const
    {   // ��� (x, y) ���� 753 ��б���е�λ��
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
    {   // ȡ�� (x, y) ���ڵ� 159 б�ߵĳ���
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
    {   // ȡ�� (x, y) ���ڵ� 753 б�ߵĳ���
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
    {   // ��ϳ� (x, y) ���ں��еĺ���� Line bits
        return blackbits_456[x] | whitebits_456[x] | whitebits_456[x] << 1;
    }
    Line black_linebits_852(const unsigned x, const unsigned y) const
    {   // ��ϳ� (x, y) �������еĺ���� Line bits
        return blackbits_852[y] | whitebits_852[y] | whitebits_852[y] << 1;
    }
    Line black_linebits_159(const unsigned x, const unsigned y) const
    {   // ��ϳ� (x, y) ���� 159 ����б�еĺ���� Line bits
        unsigned row = line_row_159(x, y);
        return blackbits_159[row] | whitebits_159[row] | whitebits_159[row] << 1;
    }
    Line black_linebits_753(const unsigned x, const unsigned y) const
    {   // ��ϳ� (x, y) ���� 753 ����б�еĺ���� Line bits
        unsigned row = line_row_753(x, y);
        return blackbits_753[row] | whitebits_753[row] | whitebits_753[row] << 1;
    }

    Line white_linebits_456(const unsigned x, const unsigned y) const
    {   // ��ϳ� (x, y) ���ں��еİ���� Line bits
        return whitebits_456[x] | blackbits_456[x] | blackbits_456[x] << 1;
    }
    Line white_linebits_852(const unsigned x, const unsigned y) const
    {   // ��ϳ� (x, y) �������еİ���� Line bits
        return whitebits_852[y] | blackbits_852[y] | blackbits_852[y] << 1;
    }
    Line white_linebits_159(const unsigned x, const unsigned y) const
    {   // ��ϳ� (x, y) ���� 159 ����б�еİ���� Line bits
        unsigned row = line_row_159(x, y);
        return whitebits_159[row] | blackbits_159[row] | blackbits_159[row] << 1;
    }
    Line white_linebits_753(const unsigned x, const unsigned y) const
    {   // ��ϳ� (x, y) ���� 753 ����б�еİ���� Line bits
        unsigned row = line_row_753(x, y);
        return whitebits_753[row] | blackbits_753[row] | blackbits_753[row] << 1;
    }

    unsigned black_vici9bits_456(const short x, const short y) const
    {   // ������ (x, y) Ϊ���ĵ� 456 ����� 9 �� bits����ֱ������ Pattern9 �� pattern
        return black_linebits_456(x, y) >> (y * 2) & 0x3FFFF;
    }
    unsigned black_vici9bits_852(const short x, const short y) const
    {
        return black_linebits_852(x, y) >> (x * 2) & 0x3FFFF;
    }
    unsigned black_vici9bits_159(const short x, const short y) const
    {
        return black_linebits_159(x, y) >> (line_offset_159(x, y) * 2) & 0x3FFFF;
    }
    unsigned black_vici9bits_753(const short x, const short y) const
    {
        return black_linebits_753(x, y) >> (line_offset_753(x, y) * 2) & 0x3FFFF;
    }
    unsigned white_vici9bits_456(const short x, const short y) const
    {   // ������ (x, y) Ϊ���ĵ� 456 ����� 9 �� bits����ֱ������ Pattern9 �� pattern
        return white_linebits_456(x, y) >> ((y /*+ offset*/) * 2) & 0x3FFFF;
    }
    unsigned white_vici9bits_852(const short x, const short y) const
    {
        return white_linebits_852(x, y) >> (x * 2) & 0x3FFFF;
    }
    unsigned white_vici9bits_159(const short x, const short y) const
    {
        return white_linebits_159(x, y) >> (line_offset_159(x, y) * 2) & 0x3FFFF;
    }
    unsigned white_vici9bits_753(const short x, const short y) const
    {
        return white_linebits_753(x, y) >> (line_offset_753(x, y) * 2) & 0x3FFFF;
    }

    void add_black(const short x, const short y)
    {   // ���� 4 ��ƫ��
        blackbits_456[x] |= 0x1ull << (y * 2 + 8);
        blackbits_852[y] |= 0x1ull << (x * 2 + 8);
        blackbits_159[line_row_159(x, y)] |= 0x1ull << (line_offset_159(x, y) * 2 + 8);
        blackbits_753[line_row_753(x, y)] |= 0x1ull << (line_offset_753(x, y) * 2 + 8);
    }
    void add_white(const short x, const short y)
    {
        whitebits_456[x] |= 0x1ull << (y * 2 + 8);
        whitebits_852[y] |= 0x1ull << (x * 2 + 8);
        whitebits_159[line_row_159(x, y)] |= 0x1ull << (line_offset_159(x, y) * 2 + 8);
        whitebits_753[line_row_753(x, y)] |= 0x1ull << (line_offset_753(x, y) * 2 + 8);
    }
    //void add_stone(const short x, const short y, const COLOR c)
    //{   // ���� 4 ��ƫ��
    //    switch(c)
    //    {
    //    case BLACK:
    //        blackbits_456[x] |= 0x1ull << (y * 2 + 8);
    //        blackbits_852[y] |= 0x1ull << (x * 2 + 8);
    //        blackbits_159[line_row_159(x, y)] |= 0x1ull << (line_offset_159(x, y) * 2 + 8);
    //        blackbits_753[line_row_753(x, y)] |= 0x1ull << (line_offset_753(x, y) * 2 + 8);
    //        break;
    //    case WHITE:
    //        whitebits_456[x] |= 0x1ull << (y * 2 + 8);
    //        whitebits_852[y] |= 0x1ull << (x * 2 + 8);
    //        whitebits_159[line_row_159(x, y)] |= 0x1ull << (line_offset_159(x, y) * 2 + 8);
    //        whitebits_753[line_row_753(x, y)] |= 0x1ull << (line_offset_753(x, y) * 2 + 8);
    //        break;
    //    case BLOCK:
    //        // Nothing to do...
    //        break;
    //    default:
    //        break;
    //    }
    //}
    void remove_black(const short x, const short y)
    {
        blackbits_456[x] &= ~(0x3ull << (y * 2 + 8));
        blackbits_852[y] &= ~(0x3ull << (x * 2 + 8));
        blackbits_159[line_row_159(x, y)] &= ~(0x3ull << (line_offset_159(x, y) * 2 + 8));
        blackbits_753[line_row_753(x, y)] &= ~(0x3ull << (line_offset_753(x, y) * 2 + 8));
    }
    void remove_white(const short x, const short y)
    {
        whitebits_456[x] &= ~(0x3ull << (y * 2 + 8));
        whitebits_852[y] &= ~(0x3ull << (x * 2 + 8));
        whitebits_159[line_row_159(x, y)] &= ~(0x3ull << (line_offset_159(x, y) * 2 + 8));
        whitebits_753[line_row_753(x, y)] &= ~(0x3ull << (line_offset_753(x, y) * 2 + 8));
    }
    //void remove_stone(const short x, const short y, const COLOR c)
    //{   // ���� 4 ��ƫ��
    //    switch(c)
    //    {
    //    case BLACK:
    //        blackbits_456[x] &= ~(0x3ull << (y * 2 + 8));
    //        blackbits_852[y] &= ~(0x3ull << (x * 2 + 8));
    //        blackbits_159[line_row_159(x, y)] &= ~(0x3ull << (line_offset_159(x, y) * 2 + 8));
    //        blackbits_753[line_row_753(x, y)] &= ~(0x3ull << (line_offset_753(x, y) * 2 + 8));
    //        break;
    //    case WHITE:
    //        whitebits_456[x] &= ~(0x3ull << (y * 2 + 8));
    //        whitebits_852[y] &= ~(0x3ull << (x * 2 + 8));
    //        whitebits_159[line_row_159(x, y)] &= ~(0x3ull << (line_offset_159(x, y) * 2 + 8));
    //        whitebits_753[line_row_753(x, y)] &= ~(0x3ull << (line_offset_753(x, y) * 2 + 8));
    //        break;
    //    case BLOCK:
    //        // Nothing to do...
    //        break;
    //    default:
    //        break;
    //    }
    //}
};

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

const int MAX_BOARD_SIZE = 22;

class Board
{
public:
    enum
    {
        LIAN5 = 5,
        SHUA4 = 4,
        CHON4 = 3,
        HUO3 =  2,
        MIAN3 = 1,
        INVMK = 0
    };
    typedef unsigned short Position;    // 0000 00XX XXXY YYYY��ÿ������ 5 + 5 = 10 bits
    static const Position INVPOS = 0x3FF;

private:
    static Pattern9 pat9;
    BitBoard bitboard;
    int board_width, board_height;
    int black_score, white_score;

public: // ----------------- Debug -----------------------
    enum
    {   // Color_Pos_State::mark[5] ��������Ӧ���±�
        DIR_456 = 1,
        DIR_852 = 2,
        DIR_159 = 3,
        DIR_753 = 4
    };
    union Color_Pos_Mark
    {
        struct Data
        {
            unsigned mark:   4; // LIAN5, SHUA4, CHON4, HUO3, MIAN3, INVMK
            unsigned def1:  10;
            unsigned def2:  10;
        };
        Data d;
        unsigned u;
    };
    struct Color_Pos_State
    {
        Color_Pos_Mark mark[5]; // all, 456, 852, 159, 753 direction
        unsigned prev:      10;
        unsigned next:      10;
        unsigned color:      4;
        Color_Pos_State(): prev(INVPOS), next(INVPOS), color(BLANK) {
            memset(mark, 0, sizeof(mark));
        }
    };
    // ���һ�����ڴ�� lian5, shua4, chon4, huo3, mian3 �����ͷ���
    Color_Pos_State black_board[MAX_BOARD_SIZE + 1][MAX_BOARD_SIZE];
    Color_Pos_State white_board[MAX_BOARD_SIZE + 1][MAX_BOARD_SIZE];


    //struct Color_Point_Num
    //{
    //    int lian5_num;
    //    int shua4_num;
    //    int chon4_num;
    //    int huo3_num;
    //    int mian3_num;
    //    Color_Point_Num()
    //        :lian5_num(0),
    //         shua4_num(0),
    //         chon4_num(0),
    //         huo3_num(0),
    //         mian3_num(0) {}
    //};
    int black_num[6], white_num[6];

    //enum
    //{   // ������ͷ����� board[MAX_BOARD_SIZE] �е�λ��
    //    LIAN5_IDX = 0,
    //    SHUA4_IDX = 1,
    //    CHON4_IDX = 2,
    //     HUO3_IDX = 3,
    //    MIAN3_IDX = 4
    //};

    void vici_score(const short x, const short y, int &_black_score, int &_white_score) const
    {
        Pattern9::State vici_state;
        _black_score = _white_score = 0;
        vici_state = pat9(bitboard.black_vici9bits_456(x, y));
        _black_score += vici_state.score;
        vici_state = pat9(bitboard.black_vici9bits_852(x, y));
        _black_score += vici_state.score;
        vici_state = pat9(bitboard.black_vici9bits_159(x, y));
        _black_score += vici_state.score;
        vici_state = pat9(bitboard.black_vici9bits_753(x, y));
        _black_score += vici_state.score;
        vici_state = pat9(bitboard.white_vici9bits_456(x, y));
        _white_score += vici_state.score;
        vici_state = pat9(bitboard.white_vici9bits_852(x, y));
        _white_score += vici_state.score;
        vici_state = pat9(bitboard.white_vici9bits_159(x, y));
        _white_score += vici_state.score;
        vici_state = pat9(bitboard.white_vici9bits_753(x, y));
        _white_score += vici_state.score;
    }

public:
    Board(const unsigned Witdh = 15, const unsigned Height = 15)
        :bitboard(Witdh, Height), board_width(Witdh), board_height(Height),
         black_score(0), white_score(0)
    {
        memset(black_num, 0, sizeof(black_num));
        memset(white_num, 0, sizeof(white_num));
    }

    void set_size(const unsigned Width, const unsigned Height)
    {
        if(Width == board_width && Height == board_height) return;
        board_width = Width;
        board_height = Height;
        bitboard.set_size(Width, Height);
        reset();
    }

    void reset()
    {
        bitboard.reset_board();
        memset(black_num, 0, sizeof(black_num));
        memset(white_num, 0, sizeof(white_num));
        black_score = white_score = 0;
        for(int i = 0; i <= MAX_BOARD_SIZE; ++i)
        {
            for(int j = 0; j < MAX_BOARD_SIZE; ++j)
            {
                black_board[i][j] = Color_Pos_State();
                white_board[i][j] = Color_Pos_State();
            }
        }
    }

    int get_black_score() const
    {
        return black_score;
    }
    int get_white_score() const
    {
        return white_score;
    }

    Position black_lian5_begin() const
    {
        return black_board[MAX_BOARD_SIZE][LIAN5].next;
    }
    Position black_shua4_begin() const
    {
        return black_board[MAX_BOARD_SIZE][SHUA4].next;
    }
    Position black_chon4_begin() const
    {
        return black_board[MAX_BOARD_SIZE][CHON4].next;
    }
    Position black_huo3_begin() const
    {
        return black_board[MAX_BOARD_SIZE][HUO3].next;
    }
    Position black_mian3_begin() const
    {
        return black_board[MAX_BOARD_SIZE][MIAN3].next;
    }

    Position white_lian5_begin() const
    {
        return white_board[MAX_BOARD_SIZE][LIAN5].next;
    }
    Position white_shua4_begin() const
    {
        return white_board[MAX_BOARD_SIZE][SHUA4].next;
    }
    Position white_chon4_begin() const
    {
        return white_board[MAX_BOARD_SIZE][CHON4].next;
    }
    Position white_huo3_begin() const
    {
        return white_board[MAX_BOARD_SIZE][HUO3].next;
    }
    Position white_mian3_begin() const
    {
        return white_board[MAX_BOARD_SIZE][MIAN3].next;
    }

    int black_lian5_num() const
    {
        return black_num[LIAN5];
    }
    int black_shua4_num() const
    {
        return black_num[SHUA4];
    }
    int black_chon4_num() const
    {
        return black_num[CHON4];
    }
    int black_huo3_num() const
    {
        return black_num[HUO3];
    }
    int black_mian3_num() const
    {
        return black_num[MIAN3];
    }
    int white_lian5_num() const
    {
        return white_num[LIAN5];
    }
    int white_shua4_num() const
    {
        return white_num[SHUA4];
    }
    int white_chon4_num() const
    {
        return white_num[CHON4];
    }
    int white_huo3_num() const
    {
        return white_num[HUO3];
    }
    int white_mian3_num() const
    {
        return white_num[MIAN3];
    }

    unsigned black_defense(const Position pos) const
    {
        const Color_Pos_Mark::Data &d = black_board[pos >> 5][pos & 0x1F].mark[0].d;
        return d.def2 << 10 | d.def1;
    }
    unsigned white_defense(const Position pos) const
    {
        const Color_Pos_Mark::Data &d = white_board[pos >> 5][pos & 0x1F].mark[0].d;
        return d.def2 << 10 | d.def1;
    }

    Position black_next(const Position pos) const
    {
        return black_board[pos >> 5][pos & 0x1F].next;
    }
    Position white_next(const Position pos) const
    {
        return white_board[pos >> 5][pos & 0x1F].next;
    }
    //*
    // ���� new_mark ���� black_board[pos] �� prev next ָ��
    // ���ô˺���ǰȷ�� black_board[pos].mark[0] != new_mark
    void pos_update_black_list(const short x, const short y, const Color_Pos_Mark new_mark)
    {
        Color_Pos_State &ps = black_board[x][y];
        // ��ǰ���Ƴ�����
        if(ps.prev != INVPOS)
        {
            black_board[ps.prev >> 5][ps.prev & 0x1F].next = ps.next;
        }
        if(ps.next != INVPOS)
        {
            black_board[ps.next >> 5][ps.next & 0x1F].prev = ps.prev;
        }
        --black_num[ps.mark[0].d.mark];

        if(new_mark.d.mark == INVMK)
        {   // ��� new_mark ������㣬��ǰ��ָ����Ϊ INVPOS
            ps.prev = ps.next = INVPOS;
        }
        else
        {   // ���򣬵�ǰ�����������
            ++black_num[new_mark.d.mark];
            ps.prev = MAX_BOARD_SIZE << 5 | new_mark.d.mark;
            ps.next = black_board[MAX_BOARD_SIZE][new_mark.d.mark].next;
            black_board[MAX_BOARD_SIZE][new_mark.d.mark].next = x << 5 | y;
            if(ps.next != INVPOS)
            {
                black_board[ps.next >> 5][ps.next & 0x1F].prev = x << 5 | y;
            }
        }
    }
    // ���� new_mark ���� white_board[pos] �� prev next ָ��
    // ���ô˺���ǰȷ�� white_board[pos].mark[0] != new_mark
    void pos_update_white_list(const short x, const short y, const Color_Pos_Mark new_mark)
    {
        Color_Pos_State &ps = white_board[x][y];
        // ��ǰ���Ƴ�����
        if(ps.prev != INVPOS)
        {
            white_board[ps.prev >> 5][ps.prev & 0x1F].next = ps.next;
        }
        if(ps.next != INVPOS)
        {
            white_board[ps.next >> 5][ps.next & 0x1F].prev = ps.prev;
        }
        --white_num[ps.mark[0].d.mark];

        if(new_mark.d.mark == INVMK)
        {   // ��� new_mark ������㣬��ǰ��ָ����Ϊ INVPOS
            ps.prev = ps.next = INVPOS;
        }
        else
        {   // ���򣬵�ǰ�����������
            ++white_num[new_mark.d.mark];
            ps.prev = MAX_BOARD_SIZE << 5 | new_mark.d.mark;
            ps.next = white_board[MAX_BOARD_SIZE][new_mark.d.mark].next;
            white_board[MAX_BOARD_SIZE][new_mark.d.mark].next = x << 5 | y;
            if(ps.next != INVPOS)
            {
                white_board[ps.next >> 5][ps.next & 0x1F].prev = x << 5 | y;
            }
        }
    }
    void move(const unsigned x, const unsigned y, const COLOR c)
    {
        // ����ķ���ԭ���Ƶ÷�
        int original_black_score, new_black_score;
        int original_white_score, new_white_score;
        vici_score(x, y, original_black_score, original_white_score);
        // bitboard �������
        black_board[x][y].color = c;
        if(c == BLACK)
        {
            bitboard.add_black(x, y);
        }
        else if(c == WHITE)
        {
            bitboard.add_white(x, y);
        }
        // ����ķ��������Ƶ÷֣������·���
        vici_score(x, y, new_black_score, new_white_score);
        black_score += new_black_score - original_black_score;
        white_score += new_white_score - original_white_score;

        // ����ǰλ�ô��������Ƴ��������� num ����
        // black
        Color_Pos_State &curBPS = black_board[x][y];
        if(curBPS.prev != INVPOS)
        {
            black_board[curBPS.prev >> 5][curBPS.prev & 0x1F].next = curBPS.next;
        }
        if(curBPS.next != INVPOS)
        {
            black_board[curBPS.next >> 5][curBPS.next & 0x1F].prev = curBPS.prev;
        }
        curBPS.prev = curBPS.next = INVPOS;
        --black_num[curBPS.mark[0].d.mark];
        memset(curBPS.mark, 0, sizeof(curBPS.mark));
        // white
        Color_Pos_State &curWPS = white_board[x][y];
        if(curWPS.prev != INVPOS)
        {
            white_board[curWPS.prev >> 5][curWPS.prev & 0x1F].next = curWPS.next;
        }
        if(curWPS.next != INVPOS)
        {
            white_board[curWPS.next >> 5][curWPS.next & 0x1F].prev = curWPS.prev;
        }
        curWPS.prev = curWPS.next = INVPOS;
        --white_num[curWPS.mark[0].d.mark];
        memset(curWPS.mark, 0, sizeof(curWPS.mark));

        // ������Χ +-4 ���ڿո��״̬
        unsigned vici9bits;
        unsigned char pat_mark;
        Color_Pos_Mark new_dir_mark;

        // ----------------------------- black -------------------------------
        // Direction 456
        vici9bits = bitboard.black_vici9bits_456(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x;
            int cy = y + i - 4;
            Color_Pos_State &cs = black_board[cx][cy];
            pat_mark = pat9(bitboard.black_vici9bits_456(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = cx << 5 | cy + (pat_mark & 0xF) - 5;
                    new_dir_mark.d.def2 = cx << 5 | cy + (pat_mark >> 4 & 0xF) - 5;
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = cx << 5 | cy + (pat_mark & 0xF) - 5;
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_456].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_456].u = new_dir_mark.u;
                    pos_update_black_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_456].u)
                {
                    cs.mark[DIR_456].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_456].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_black_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
        // Direction 852
        vici9bits = bitboard.black_vici9bits_852(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x + i - 4;
            int cy = y;
            Color_Pos_State &cs = black_board[cx][cy];
            pat_mark = pat9(bitboard.black_vici9bits_852(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | cy;
                    new_dir_mark.d.def2 = (cx + (pat_mark >> 4 & 0xF) - 5) << 5 | cy;
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | cy;
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_852].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_852].u = new_dir_mark.u;
                    pos_update_black_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_852].u)
                {
                    cs.mark[DIR_852].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_852].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_black_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
        // Direction 159
        vici9bits = bitboard.black_vici9bits_159(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x + 4 - i;
            int cy = y + i - 4;
            Color_Pos_State &cs = black_board[cx][cy];
            pat_mark = pat9(bitboard.black_vici9bits_159(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = (cx + 5 - (pat_mark & 0xF)) << 5 | (cy + (pat_mark & 0xF) - 5);
                    new_dir_mark.d.def2 = (cx + 5 - (pat_mark >> 4 & 0xF)) << 5 | (cy + (pat_mark >> 4 & 0xF) - 5);
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = (cx + 5 - (pat_mark & 0xF)) << 5 | (cy + (pat_mark & 0xF) - 5);
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_159].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_159].u = new_dir_mark.u;
                    pos_update_black_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_159].u)
                {
                    cs.mark[DIR_159].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_159].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_black_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
        // Direction 753
        vici9bits = bitboard.black_vici9bits_753(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x + i - 4;
            int cy = y + i - 4;
            Color_Pos_State &cs = black_board[cx][cy];
            pat_mark = pat9(bitboard.black_vici9bits_753(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | (cy + (pat_mark & 0xF) - 5);
                    new_dir_mark.d.def2 = (cx + (pat_mark >> 4 & 0xF) - 5) << 5 | (cy + (pat_mark >> 4 & 0xF) - 5);
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | (cy + (pat_mark & 0xF) - 5);
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_753].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_753].u = new_dir_mark.u;
                    pos_update_black_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_753].u)
                {
                    cs.mark[DIR_753].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_753].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_black_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }

        // ----------------------------- white -------------------------------
        // Direction 456
        vici9bits = bitboard.white_vici9bits_456(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x;
            int cy = y + i - 4;
            Color_Pos_State &cs = white_board[cx][cy];
            pat_mark = pat9(bitboard.white_vici9bits_456(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = cx << 5 | cy + (pat_mark & 0xF) - 5;
                    new_dir_mark.d.def2 = cx << 5 | cy + (pat_mark >> 4 & 0xF) - 5;
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = cx << 5 | cy + (pat_mark & 0xF) - 5;
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_456].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_456].u = new_dir_mark.u;
                    pos_update_white_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_456].u)
                {
                    cs.mark[DIR_456].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_456].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_white_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
        // Direction 852
        vici9bits = bitboard.white_vici9bits_852(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x + i - 4;
            int cy = y;
            Color_Pos_State &cs = white_board[cx][cy];
            pat_mark = pat9(bitboard.white_vici9bits_852(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | cy;
                    new_dir_mark.d.def2 = (cx + (pat_mark >> 4 & 0xF) - 5) << 5 | cy;
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | cy;
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_852].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_852].u = new_dir_mark.u;
                    pos_update_white_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_852].u)
                {
                    cs.mark[DIR_852].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_852].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_white_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
        // Direction 159
        vici9bits = bitboard.white_vici9bits_159(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x + 4 - i;
            int cy = y + i - 4;
            Color_Pos_State &cs = white_board[cx][cy];
            pat_mark = pat9(bitboard.white_vici9bits_159(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = (cx + 5 - (pat_mark & 0xF)) << 5 | (cy + (pat_mark & 0xF) - 5);
                    new_dir_mark.d.def2 = (cx + 5 - (pat_mark >> 4 & 0xF)) << 5 | (cy + (pat_mark >> 4 & 0xF) - 5);
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = (cx + 5 - (pat_mark & 0xF)) << 5 | (cy + (pat_mark & 0xF) - 5);
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_159].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_159].u = new_dir_mark.u;
                    pos_update_white_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_159].u)
                {
                    cs.mark[DIR_159].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_159].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_white_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
        // Direction 753
        vici9bits = bitboard.white_vici9bits_753(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x + i - 4;
            int cy = y + i - 4;
            Color_Pos_State &cs = white_board[cx][cy];
            pat_mark = pat9(bitboard.white_vici9bits_753(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | (cy + (pat_mark & 0xF) - 5);
                    new_dir_mark.d.def2 = (cx + (pat_mark >> 4 & 0xF) - 5) << 5 | (cy + (pat_mark >> 4 & 0xF) - 5);
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | (cy + (pat_mark & 0xF) - 5);
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_753].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_753].u = new_dir_mark.u;
                    pos_update_white_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_753].u)
                {
                    cs.mark[DIR_753].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_753].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_white_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
    }
    void move(const Position pos, const COLOR c)
    {
        move(pos >> 5, pos & 0x1F, c);
    }

    void remove(const short x, const short y)
    {
        // ����ķ���ԭ���Ƶ÷�
        int original_black_score, new_black_score;
        int original_white_score, new_white_score;
        vici_score(x, y, original_black_score, original_white_score);
        // bitboard ȥ������
        if(black_board[x][y].color == BLACK)
        {
            bitboard.remove_black(x, y);
        }
        else if(black_board[x][y].color == WHITE)
        {
            bitboard.remove_white(x, y);
        }
        else
        {
            throw "Remove Stone at EMPTY point!\n";
        }
        // ����ķ��������Ƶ÷֣������·���
        vici_score(x, y, new_black_score, new_white_score);
        black_score += new_black_score - original_black_score;
        white_score += new_white_score - original_white_score;

        // ������Χ +-4 ���ڿո��״̬
        unsigned vici9bits;
        unsigned char pat_mark;
        Color_Pos_Mark new_dir_mark;

        // ----------------------------- black -------------------------------
        // Direction 456
        vici9bits = bitboard.black_vici9bits_456(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x;
            int cy = y + i - 4;
            Color_Pos_State &cs = black_board[cx][cy];
            pat_mark = pat9(bitboard.black_vici9bits_456(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = cx << 5 | cy + (pat_mark & 0xF) - 5;
                    new_dir_mark.d.def2 = cx << 5 | cy + (pat_mark >> 4 & 0xF) - 5;
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = cx << 5 | cy + (pat_mark & 0xF) - 5;
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_456].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_456].u = new_dir_mark.u;
                    pos_update_black_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_456].u)
                {
                    cs.mark[DIR_456].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_456].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_black_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
        // Direction 852
        vici9bits = bitboard.black_vici9bits_852(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x + i - 4;
            int cy = y;
            Color_Pos_State &cs = black_board[cx][cy];
            pat_mark = pat9(bitboard.black_vici9bits_852(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | cy;
                    new_dir_mark.d.def2 = (cx + (pat_mark >> 4 & 0xF) - 5) << 5 | cy;
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | cy;
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_852].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_852].u = new_dir_mark.u;
                    pos_update_black_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_852].u)
                {
                    cs.mark[DIR_852].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_852].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_black_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
        // Direction 159
        vici9bits = bitboard.black_vici9bits_159(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x + 4 - i;
            int cy = y + i - 4;
            Color_Pos_State &cs = black_board[cx][cy];
            pat_mark = pat9(bitboard.black_vici9bits_159(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = (cx + 5 - (pat_mark & 0xF)) << 5 | (cy + (pat_mark & 0xF) - 5);
                    new_dir_mark.d.def2 = (cx + 5 - (pat_mark >> 4 & 0xF)) << 5 | (cy + (pat_mark >> 4 & 0xF) - 5);
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = (cx + 5 - (pat_mark & 0xF)) << 5 | (cy + (pat_mark & 0xF) - 5);
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_159].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_159].u = new_dir_mark.u;
                    pos_update_black_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_159].u)
                {
                    cs.mark[DIR_159].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_159].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_black_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
        // Direction 753
        vici9bits = bitboard.black_vici9bits_753(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x + i - 4;
            int cy = y + i - 4;
            Color_Pos_State &cs = black_board[cx][cy];
            pat_mark = pat9(bitboard.black_vici9bits_753(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | (cy + (pat_mark & 0xF) - 5);
                    new_dir_mark.d.def2 = (cx + (pat_mark >> 4 & 0xF) - 5) << 5 | (cy + (pat_mark >> 4 & 0xF) - 5);
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | (cy + (pat_mark & 0xF) - 5);
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_753].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_753].u = new_dir_mark.u;
                    pos_update_black_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_753].u)
                {
                    cs.mark[DIR_753].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_753].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_black_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }

        // ----------------------------- white -------------------------------
        // Direction 456
        vici9bits = bitboard.white_vici9bits_456(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x;
            int cy = y + i - 4;
            Color_Pos_State &cs = white_board[cx][cy];
            pat_mark = pat9(bitboard.white_vici9bits_456(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = cx << 5 | cy + (pat_mark & 0xF) - 5;
                    new_dir_mark.d.def2 = cx << 5 | cy + (pat_mark >> 4 & 0xF) - 5;
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = cx << 5 | cy + (pat_mark & 0xF) - 5;
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_456].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_456].u = new_dir_mark.u;
                    pos_update_white_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_456].u)
                {
                    cs.mark[DIR_456].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_456].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_white_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
        // Direction 852
        vici9bits = bitboard.white_vici9bits_852(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x + i - 4;
            int cy = y;
            Color_Pos_State &cs = white_board[cx][cy];
            pat_mark = pat9(bitboard.white_vici9bits_852(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | cy;
                    new_dir_mark.d.def2 = (cx + (pat_mark >> 4 & 0xF) - 5) << 5 | cy;
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | cy;
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_852].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_852].u = new_dir_mark.u;
                    pos_update_white_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_852].u)
                {
                    cs.mark[DIR_852].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_852].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_white_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
        // Direction 159
        vici9bits = bitboard.white_vici9bits_159(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x + 4 - i;
            int cy = y + i - 4;
            Color_Pos_State &cs = white_board[cx][cy];
            pat_mark = pat9(bitboard.white_vici9bits_159(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = (cx + 5 - (pat_mark & 0xF)) << 5 | (cy + (pat_mark & 0xF) - 5);
                    new_dir_mark.d.def2 = (cx + 5 - (pat_mark >> 4 & 0xF)) << 5 | (cy + (pat_mark >> 4 & 0xF) - 5);
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = (cx + 5 - (pat_mark & 0xF)) << 5 | (cy + (pat_mark & 0xF) - 5);
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_159].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_159].u = new_dir_mark.u;
                    pos_update_white_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_159].u)
                {
                    cs.mark[DIR_159].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_159].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_white_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }
        // Direction 753
        vici9bits = bitboard.white_vici9bits_753(x, y);
        for(int i = 0; i < 9; ++i)
        {
            // �ǿո�ֱ������
            if(vici9bits >> i*2 & 0x3) continue;

            int cx = x + i - 4;
            int cy = y + i - 4;
            Color_Pos_State &cs = white_board[cx][cy];
            pat_mark = pat9(bitboard.white_vici9bits_753(cx, cy)).mark;
            // ����÷������״̬
            new_dir_mark.u = 0;
            switch(pat_mark & 0xF)
            {
            case Pattern9::LIAN5:
                new_dir_mark.d.mark = LIAN5;
                break;
            case Pattern9::HUO3:
                new_dir_mark.d.mark = HUO3;
                break;
            case Pattern9::MIAN3:
                new_dir_mark.d.mark = MIAN3;
                break;
            case Pattern9::INVMK:
                new_dir_mark.d.mark = INVMK;
                break;
            default:
                if(pat_mark > 0xF)
                {   // ˫��
                    new_dir_mark.d.mark = SHUA4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | (cy + (pat_mark & 0xF) - 5);
                    new_dir_mark.d.def2 = (cx + (pat_mark >> 4 & 0xF) - 5) << 5 | (cy + (pat_mark >> 4 & 0xF) - 5);
                }
                else
                {   // ����
                    new_dir_mark.d.mark = CHON4;
                    new_dir_mark.d.def1 = (cx + (pat_mark & 0xF) - 5) << 5 | (cy + (pat_mark & 0xF) - 5);
                }
            }
            // ����״̬��ԭ״̬��ͬ�������
            if(new_dir_mark.u != cs.mark[DIR_753].u)
            {
                if(new_dir_mark.d.mark > cs.mark[0].d.mark)
                {
                    cs.mark[DIR_753].u = new_dir_mark.u;
                    pos_update_white_list(cx, cy, new_dir_mark);
                    cs.mark[0].u = new_dir_mark.u;
                }
                else if(cs.mark[0].u != cs.mark[DIR_753].u)
                {
                    cs.mark[DIR_753].u = new_dir_mark.u;
                }
                else
                {
                    cs.mark[DIR_753].u = new_dir_mark.u;
                    if(cs.mark[1].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[1].u;
                    if(cs.mark[2].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[2].u;
                    if(cs.mark[3].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[3].u;
                    if(cs.mark[4].d.mark > new_dir_mark.d.mark) new_dir_mark.u = cs.mark[4].u;
                    if(cs.mark[0].u != new_dir_mark.u)
                    {
                        pos_update_white_list(cx, cy, new_dir_mark);
                        cs.mark[0].u = new_dir_mark.u;
                    }
                }
            }
        }


    }
};

