/************************************************************************
目前进度：完成了 black_vc4(int a) 函数，并加入了棋盘哈希，可快速搜索黑棋的 VC4 路线

下一步：
(1) 根据 black_vc4(int a) 函数改写 black_vc4_and_defense(int a) 函数，使其具备棋盘哈希，快速找到黑棋 VC4 的所有防点。(已完成)
(2) 写出 black_vc3(int a) 函数，测试速度
(3) 补全对应的 white 方函数
(4) 写出黑白双方的 a-b 搜索函数，同时根据 board_hash.occupy_ratio() 考虑何时清空棋盘 hash_table
(5) 考虑如何加入时间限定
(6) 放入 piskvork 的 AI 框架，测试效果

长远：
根据 v0.1 的经验写出 v0.2 等后续版本。
/************************************************************************/

#pragma once

#include <random>
#include <vector>

#include "Board.h"

extern std::default_random_engine random_generator;

// BoardHash class 后面再补充完善
template<class DataType>
class BoardHash
{
private:
    int stone_num;
    int saved_hash_num;
    unsigned current_hash_index;
    unsigned long long current_hash_check;

    struct hash_table_node
    {
        unsigned long long hash_check;
        int stone_num:  16;
        DataType d;
        hash_table_node()
            : hash_check(0), stone_num(-1) {}
    };

    std::vector<unsigned> index_matrix;
    unsigned index_color_hash[2];
    std::vector<unsigned long long> check_matrix;
    unsigned long long check_color_hash[2];

    std::vector<hash_table_node> hash_table;
    std::vector<COLOR> board;

    int pos2idx(const short x, const short y, const COLOR c) const
    {
        return ((c-BLACK) * MAX_BOARD_SIZE + x) * MAX_BOARD_SIZE + y;
    }
public:
    BoardHash(unsigned HashSize = 16)    // MB
        : stone_num(0), saved_hash_num(0),
        current_hash_index(0u), current_hash_check(0ull),
        index_matrix(2 * MAX_BOARD_SIZE * MAX_BOARD_SIZE),
        check_matrix(2 * MAX_BOARD_SIZE * MAX_BOARD_SIZE)
    {
        std::uniform_int_distribution<unsigned> urand(1); // 1 ~ 2^32-1
        std::uniform_int_distribution<unsigned long long> u64rand(1); // 1 ~ 2^64 - 1
        board.assign(MAX_BOARD_SIZE * MAX_BOARD_SIZE, EMPTY);
        index_color_hash[0] = urand(random_generator);
        index_color_hash[1] = urand(random_generator);
        check_color_hash[0] = u64rand(random_generator);
        check_color_hash[1] = u64rand(random_generator);
        for(int i=0; i<MAX_BOARD_SIZE; ++i)
        {
            for(int j=0; j<MAX_BOARD_SIZE; ++j)
            {
                index_matrix[pos2idx(i, j, BLACK)] = urand(random_generator);
                index_matrix[pos2idx(i, j, WHITE)] = urand(random_generator);
                check_matrix[pos2idx(i, j, BLACK)] = u64rand(random_generator);
                check_matrix[pos2idx(i, j, WHITE)] = u64rand(random_generator);
            }
        }
        hash_table.resize(HashSize * 1024 * 1024 / sizeof(hash_table_node));
    }
    void move(const short x, const short y, const COLOR c)
    {
        ++stone_num;
        board[x * MAX_BOARD_SIZE + y] = c;
        current_hash_index ^= index_matrix[pos2idx(x, y, c)];
        current_hash_check ^= check_matrix[pos2idx(x, y, c)];
    }
    void move(const unsigned pos, const COLOR c)
    {
        move(pos >> 8 & 0xFF, pos & 0xFF, c);
    }
    void remove(const short x, const short y)
    {
        --stone_num;
        COLOR c = board[x * MAX_BOARD_SIZE + y];
        board[x * MAX_BOARD_SIZE + y] = EMPTY;
        current_hash_index ^= index_matrix[pos2idx(x, y, c)];
        current_hash_check ^= check_matrix[pos2idx(x, y, c)];
    }
    void remove(const unsigned pos)
    {
        remove(pos >> 8 & 0xFF, pos & 0xFF);
    }
    void clear_board()
    {
        current_hash_index = 0u;
        current_hash_check = 0ull;
        stone_num = 0;
        board.assign(MAX_BOARD_SIZE * MAX_BOARD_SIZE, EMPTY);
        clear_hash_table();
    }
    // 以后添加 删除小于 stone_num 结点的功能；要删除结点只能使用每个 index 链表存储
    // 可以用 hash_table 头 + 自己管理的内存池构成的静态链表实现
    void clear_hash_table()
    {
        saved_hash_num = 0;
        for(auto i = hash_table.begin(); i != hash_table.end(); ++i)
        {
            i->stone_num = -1;
        }
    }
    void set_hash_table_size(unsigned size_in_MB)
    {
        hash_table.resize(size_in_MB * 1024 * 1024 / sizeof(hash_table_node));
        clear_hash_table();
    }
    DataType& get_data(const COLOR c, bool &isFound)
    {
        unsigned idx = (current_hash_index ^ index_color_hash[c - BLACK]) % hash_table.size();
        unsigned long long check = current_hash_check ^ check_color_hash[c - BLACK];

        if(hash_table[idx].hash_check == check && hash_table[idx].stone_num == stone_num)
        {
            isFound = true;
            return hash_table[idx].d;
        }
        else if(hash_table[idx].stone_num == -1)
        {
            isFound = false;
            ++saved_hash_num;
            hash_table[idx].stone_num = stone_num;
            hash_table[idx].hash_check = check;
            return hash_table[idx].d;
        }
        for(int i = 1; i < 50; ++i)
        {
            unsigned pos = (idx + i*i) % hash_table.size();
            if(hash_table[pos].hash_check == check && hash_table[pos].stone_num == stone_num)
            {
                isFound = true;
                return hash_table[idx].d;
            }
            else if(hash_table[pos].stone_num == -1)
            {
                isFound = false;
                ++saved_hash_num;
                hash_table[pos].stone_num = stone_num;
                hash_table[pos].hash_check = check;
                return hash_table[pos].d;
            }

            pos = (idx - i*i) % hash_table.size();
            if(hash_table[pos].hash_check == check && hash_table[pos].stone_num == stone_num)
            {
                isFound = true;
                return hash_table[idx].d;
            }
            else if(hash_table[pos].stone_num == -1)
            {
                isFound = false;
                ++saved_hash_num;
                hash_table[pos].stone_num = stone_num;
                hash_table[pos].hash_check = check;
                return hash_table[pos].d;
            }
        }
        throw "Not Enough HashTable Size.\n";
        return hash_table[0].d;
    }
    double occupy_ratio() const
    {
        return (double)saved_hash_num / hash_table.size();
    }
};


//////////////////////////////////////////////////////////////////////////

class WzqAI
{
public:
    static const int INTINFINITY = 10000;
    enum {VC4_EXACT = 1, VC4_ALPHA = 2, VC4_BETA = 3};
    struct Board_Status_Save
    {
        unsigned val_type:  8;  // EXACT / ALPHA / BETA
        int value:         24;
    };

    Board board;
    std::vector<unsigned> vc4_defense;
    unsigned vc4_move;
    BoardHash<Board_Status_Save> board_hash;

private:
    // 将白棋所有冲四加入到 vc4_defense 中
    void add_white_rev4()
    {
        for(unsigned pos = board.white_lian5_begin(); pos != Board::INVPOS; pos = board.white_next(pos))
        {
            vc4_defense.push_back(pos);
        }
        for(unsigned pos = board.white_shua4_begin(); pos != Board::INVPOS; pos = board.white_next(pos))
        {
            vc4_defense.push_back(pos);
        }
        for(unsigned pos = board.white_chn43_begin(); pos != Board::INVPOS; pos = board.white_next(pos))
        {
            vc4_defense.push_back(pos);
        }
        for(unsigned pos = board.white_chon4_begin(); pos != Board::INVPOS; pos = board.white_next(pos))
        {
            vc4_defense.push_back(pos);
        }
    }
public:
    //int black_direct_eval()
    //{   // 不考虑 VC4，返回当前局面黑先走的直接得分
    //    if(board.black_lian5_num() > 0)
    //    {
    //        return 9999;
    //    }
    //    if(board.white_lian5_num() > 1)
    //    {
    //        return -9998;
    //    }
    //    if(board.black_shua4_num() > 0)
    //    {
    //        return 9997;
    //    }
    //    int val;
    //    if(board.white_lian5_num() == 1)
    //    {
    //        unsigned pos = board.white_lian5_begin();
    //        board.move(pos >> 8, pos & 0xFF, BLACK);
    //        val = -white_direct_eval();
    //        board.backtrace();
    //    }
    //    else if(board.black_huo3_num() > 0 || board.black_shua3_num() > 0)
    //    {
    //        val = 100 + 40 * (board.black_chon4_num() + board.black_chn43_num())
    //            + 25 * (board.black_huo3_num() + board.black_huo3_num())
    //            + 10 * board.black_mian3_num()
    //            + board.get_black_score() - board.get_white_score();
    //    }
    //    else if(board.white_huo3_num() > 0 || board.white_shua3_num() > 0)
    //    {
    //        val = -100 - 80 * board.white_shua4_num()
    //            - 40 * (board.white_chon4_num() + board.white_chn43_num())
    //            - 25 * (board.white_huo3_num() + board.white_shua3_num())
    //            - 10 * board.white_mian3_num()
    //            + board.get_black_score() - board.get_white_score();
    //    }

    //    if(val > 0)
    //    {
    //        return val - 1;
    //    }
    //    else if(val < 0)
    //    {
    //        return val + 1;
    //    }
    //    return val;
    //}
    //int white_direct_eval()
    //{
    //    if(board.white_lian5_num() > 0)
    //    {
    //        return 9999;
    //    }
    //    if(board.black_lian5_num() > 1)
    //    {
    //        return -9998;
    //    }
    //    if(board.white_shua4_num() > 0)
    //    {
    //        return 9997;
    //    }
    //    int val;
    //    if(board.black_lian5_num() == 1)
    //    {
    //        unsigned pos = board.black_lian5_begin();
    //        board.move(pos >> 8, pos & 0xFF, WHITE);
    //        val = -black_direct_eval();
    //        board.backtrace();
    //    }
    //    else if(board.white_huo3_num() > 0 || board.white_shua3_num() > 0)
    //    {
    //        val = 100 + 40 * (board.white_chon4_num() + board.white_chn43_num())
    //            + 25 * (board.white_huo3_num() + board.white_shua3_num())
    //            + 10 * board.white_mian3_num()
    //            + board.get_white_score() - board.get_black_score();
    //    }
    //    else if(board.black_huo3_num() > 0 || board.black_shua3_num() > 0)
    //    {
    //        val = -100 - 80 * board.black_shua4_num()
    //            - 40 * (board.black_chon4_num() + board.black_chn43_num())
    //            - 25 * (board.black_huo3_num() + board.black_shua3_num())
    //            - 10 * board.black_mian3_num()
    //            + board.get_white_score() - board.get_black_score();
    //    }

    //    if(val > 0)
    //    {
    //        return val - 1;
    //    }
    //    else if(val < 0)
    //    {
    //        return val + 1;
    //    }
    //    return val;
    //}
    
    void move(const unsigned short x, const unsigned short y, const COLOR c)
    {
        board_hash.move(x, y, c);
        board.move(x, y, c);
    }
    void move(const unsigned pos, const COLOR c)
    {
        move(pos >> 8 & 0xFF, pos & 0xFF, c);
    }
    void backtrace()
    {
        unsigned x, y;
        board.backtrace(x, y);
        board_hash.remove(x, y);
    }

    //int black_vc4()
    //{
    //    if(board_hash.occupy_ratio() > 0.35)
    //    {
    //        board_hash.clear_hash_table();
    //    }
    //    return black_vc4(-10000);
    //}


    // 寻找黑棋的 vc4，找到则返回 > 9000 的得分，否则返回 <= 0 的值
    // 当前局面下一步 vc4 的走法存入 vc4_move 变量
    int black_vc4(int a)
    {
        if(a >= INTINFINITY - 1){
            return 0;
        }
        bool isHashSaved;
        Board_Status_Save &current_status = board_hash.get_data(BLACK, isHashSaved);

        if(isHashSaved)
        {
            if(current_status.val_type == VC4_EXACT)
            {
                if(current_status.value > a)
                {
                    return current_status.value;
                }
                return 0;
            }
            if(current_status.val_type == VC4_ALPHA && current_status.value <= a)
            {
                return 0;
            }
        }

        if(board.black_lian5_num() > 0)
        {
            current_status.val_type = VC4_EXACT;
            current_status.value = INTINFINITY - 1;
            vc4_move = board.black_lian5_begin();   // 将来考虑将 best_move 放入 board_hash 中
            return INTINFINITY - 1;
        }
        if(board.white_lian5_num() > 1)
        {
            current_status.val_type = VC4_EXACT;
            current_status.value = -INTINFINITY + 2;
            return -INTINFINITY + 2;
        }
        if(board.white_lian5_num() == 1)
        {
            unsigned pos = board.white_lian5_begin();
            move(pos, BLACK);   // move 1
            if(board.black_lian5_num() > 0)
            {
                move(board.black_lian5_begin(), WHITE);  // move 2
                int val = black_vc4(a + 2) - 2;
                backtrace();    // move 2
                if(val > a)
                {
                    current_status.val_type = VC4_EXACT;
                    current_status.value = val;
                    vc4_move = pos;
                }
                backtrace();    // move 1
                return val;
            }
            else
            {
                current_status.val_type = VC4_EXACT;
                current_status.value = 0;
                backtrace();    // move 1
                return 0;   // 当前白棋冲四，黑棋无反四
            }
        }
        if(board.black_shua4_num() > 0)
        {
            current_status.val_type = VC4_EXACT;
            current_status.value = INTINFINITY - 3;
            if(a < INTINFINITY - 3)
            {
                vc4_move = board.black_shua4_begin();
            }
            return INTINFINITY - 3;
        }

        current_status.val_type = VC4_ALPHA;
        for(unsigned pos = board.black_chn43_begin(); pos != Board::INVPOS; pos = board.black_next(pos))
        {
            move(pos, BLACK);
            move(board.black_lian5_begin(), WHITE);
            int val = black_vc4(a + 2) - 2;
            backtrace();
            backtrace();
            if(val > a)
            {
                current_status.val_type = VC4_EXACT;
                vc4_move = pos;
                a = val;
            }
        }

        for(unsigned pos = board.black_chon4_begin(); pos != Board::INVPOS; pos = board.black_next(pos))
        {
            move(pos, BLACK);
            move(board.black_lian5_begin(), WHITE);
            int val = black_vc4(a + 2) - 2;
            backtrace();
            backtrace();
            if(val > a)
            {
                current_status.val_type = VC4_EXACT;
                vc4_move = pos;
                a = val;
            }
        }

        current_status.value = a;
        return a;
    }


    // 寻找黑棋的 vc4 路径，结果存入 vc4_route 中
    // vc4_route.back() 为当前局面需走的棋
    // 参数 a 表示寻找比 a 得分更高的棋
    // 若找到则返回 > 9000 的得分，否则返回 0 附近的值
    int black_vc4_and_defense(int a)
    {
        if(a >= INTINFINITY - 1){
            return 0;
        }
        bool isHashSaved;
        Board_Status_Save &current_status = board_hash.get_data(BLACK, isHashSaved);

        if(isHashSaved)
        {
            if(current_status.val_type == VC4_EXACT)
            {
                if(current_status.value > a)
                {
                    return current_status.value;
                }
                return 0;
            }
            if(current_status.val_type == VC4_ALPHA && current_status.value <= a)
            {
                return 0;
            }
        }

        if(board.black_lian5_num() > 0)
        {
            current_status.val_type = VC4_EXACT;
            current_status.value = INTINFINITY - 1;
            vc4_defense.clear();
            add_white_rev4();
            for(unsigned pos = board.black_lian5_begin(); pos != Board::INVPOS; pos = board.black_next(pos))
            {
                vc4_defense.push_back(pos);
            }
            return INTINFINITY - 1;
        }
        if(board.white_lian5_num() > 1)
        {
            current_status.val_type = VC4_EXACT;
            current_status.value = -INTINFINITY + 2;
            return -INTINFINITY + 2;
        }
        if(board.white_lian5_num() == 1)    // 白棋有一个冲四
        {
            unsigned pos = board.white_lian5_begin();
            move(pos, BLACK); // move 1
            if(board.black_lian5_num() > 0) // 黑棋反冲四
            {
                move(board.black_lian5_begin(), WHITE);   // move 2
                int val = black_vc4_and_defense(a + 2) - 2;
                backtrace();  // move 2
                if(val > a)
                {
                    current_status.val_type = VC4_EXACT;
                    current_status.value = val;
                    vc4_defense.push_back(board.black_lian5_begin());
                    vc4_defense.push_back(pos);
                }
                backtrace();  // move 1
                return val;
            }
            else    // 黑棋无反四
            {
                current_status.val_type = VC4_EXACT;
                current_status.value = 0;
                backtrace();  // move 1
                return 0;
            }
        }
        if(board.black_shua4_num() > 0)
        {
            current_status.val_type = VC4_EXACT;
            current_status.value = INTINFINITY - 3;
            if(a < INTINFINITY - 3){
                vc4_defense.clear();
                add_white_rev4();
                if(board.black_shua4_num() > 1)
                {
                    for(unsigned pos = board.black_shua4_begin(); pos != Board::INVPOS; pos = board.black_next(pos))
                    {
                        board.move(pos, WHITE);
                        if(board.black_shua4_num() == 0)
                        {
                            vc4_defense.push_back(pos);
                        }
                        board.backtrace();
                    }
                }
                else    // black_shua4_num == 1
                {
                    vc4_defense.push_back(board.black_shua4_begin());
                    board.move(board.black_shua4_begin(), BLACK);
                    for(unsigned pos = board.black_lian5_begin(); pos != Board::INVPOS; pos = board.black_next(pos))
                    {
                        vc4_defense.push_back(pos);
                    }
                    board.backtrace();
                }
            }
            return INTINFINITY - 3;
        }

        current_status.val_type = VC4_ALPHA;
        for(unsigned pos = board.black_chn43_begin(); pos != Board::INVPOS;
            pos = board.black_next(pos))
        {
            move(pos, BLACK);
            move(board.black_lian5_begin(), WHITE);
            int val = black_vc4_and_defense(a + 2) - 2;
            backtrace();
            if(val > a)
            {
                current_status.val_type = VC4_EXACT;
                vc4_defense.push_back(board.black_lian5_begin());
                vc4_defense.push_back(pos);
                a = val;
            }
            backtrace();
        }

        for(unsigned pos = board.black_chon4_begin(); pos != Board::INVPOS;
            pos = board.black_next(pos))
        {
            move(pos, BLACK);
            move(board.black_lian5_begin(), WHITE);
            int val = black_vc4_and_defense(a + 2) - 2;
            backtrace();
            if(val > a)
            {
                current_status.val_type = VC4_EXACT;
                vc4_defense.push_back(board.black_lian5_begin());
                vc4_defense.push_back(pos);
                a = val;
            }
            backtrace();
        }
        current_status.value = a;
        return a;
    }

    //int black_vc4_eval(int a, int b)
    //{
    //    int val;
    //    val = black_direct_eval();
    //    if(val >= b)
    //    {
    //        return b;
    //    }
    //    if(val > a)
    //    {
    //        a = val;
    //    }

    //    for(unsigned pos = board.black_chon4_begin(); pos != Board::INVPOS;
    //        pos = board.black_next(pos))
    //    {
    //        board.move(pos >> 8, pos & 0xFF, BLACK);
    //        val = -white_vc4_eval(-b, -a);
    //        board.backtrace();
    //        val += val >= 0? -1: 1;
    //        if(val >= b)
    //        {
    //            return b;
    //        }
    //        if(val > a)
    //        {
    //            a = val;
    //        }
    //    }
    //    return a;
    //}
    //int white_vc4_eval(int a, int b)
    //{
    //    int val;
    //    val = white_direct_eval();
    //    if(val >= b)
    //    {
    //        return b;
    //    }
    //    if(val > a)
    //    {
    //        a = val;
    //    }

    //    for(unsigned pos = board.white_chon4_begin(); pos != Board::INVPOS;
    //        pos = board.white_next(pos))
    //    {
    //        board.move(pos >> 8, pos & 0xFF, WHITE);
    //        val = -black_vc4_eval(-b, -a);
    //        board.backtrace();
    //        val += val >= 0? -1: 1;
    //        if(val >= b)
    //        {
    //            return b;
    //        }
    //        if(val > a)
    //        {
    //            a = val;
    //        }
    //    }
    //    return a;
    //}
};
