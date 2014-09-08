#pragma once

// 底层的 Pattern9、Pattern13 分别实现了对无禁、有禁的支持
// 在 BitBoard 中可统一返回 9格 bits 和 13格 bits，不必分成两个类
// 

// 后面在完成 Board 类时，根据规则不同需关注的进攻类型也不同
// 如对 长连 + 43 的点，无禁规则直接关注长连即可；精确5 规则需要关注 43；而有禁规则又需要
// 关注长连。因此有必要将 Board 根据规则分成 3 个类，以免其功能相互影响
// 
// BoardNoFoul、BoardNoFoulEx5、BoardFoul 分别对应无禁、无禁精确5连以及有禁规则
// 其中 BoardNoFoul 和 BoardNoFoulEx5 的搜索函数不分黑白，用参数 const COLOR 来区分；
// BoardFoul 因为黑有禁白无禁，因此搜索函数分开来写
// 





/********************************************************

棋盘尺寸为 int BitBoard::boardSize
棋子坐标为 (x, y), 其中 x, y 的范围是 [0, boardSize - 1]
只允许正方形棋盘。长宽不等的情况处理见 v0.1 版代码。
------------------------------------------
    0   1   2   --->    y   size
0
1
2

|
|
V

x
size
------------------------------------------
*********************************************************/


#include <vector>
#include "Pattern.h"

enum COLOR {
    C_BLACK = 0,
    C_WHITE = 1,
    C_EMPTY = 2,
    C_BLOCK = 3
};


class BitBoard {
public:
    typedef unsigned long long Line;
private:
    unsigned boardSize; // 0 <= x, y < boardSize

    // 以 PC 键盘数字区的数字来表示方向
    std::vector<Line> blackBits456, whiteBits456;   // =
    std::vector<Line> blackBits852, whiteBits852;   // ||
    std::vector<Line> blackBits159, whiteBits159;   // //
    std::vector<Line> blackBits753, whiteBits753;   // \\

    // 求得 (x, y) 点以 159 的斜行来数算第几行
    unsigned lineRow159(const unsigned x, const unsigned y) const {
        return x + y;
    }
    // 求得 (x, y) 点以 753 的斜行来数算第几行
    unsigned lineRow753(const unsigned x, const unsigned y) const {
        return boardSize + x - y - 1;
    }
    // 求得 (x, y) 点在 159 斜行中的位置
    unsigned lineOffset159(const unsigned x, const unsigned y) const {
        return (x + y > boardSize - 1)?
            (boardSize - x - 1): y;
    }
    // 求得 (x, y) 点在 753 斜行中的位置
    unsigned lineOffset753(const unsigned x, const unsigned y) const {
        return (x > y)? y: x;
    }

    // 求得 (x, y) 所在的 159 斜行的长度
    unsigned lineSize159(const unsigned x, const unsigned y) const {
        if(x + y <= boardSize - 1) {
            return x + y + 1;
        }
        else {
            return boardSize * 2 - x - y - 1;
        }
    }
    // 求得 (x, y) 所在的 753 斜行的长度
    unsigned lineSize753(const unsigned x, const unsigned y) const {
        if(x >= y) {
            return boardSize - x + y;
        }
        else {
            return boardSize + x - y;
        }
    }

    // 组合出 (x, y) 所在横行的黑棋的 Line bits
    Line blackLineBits456(const unsigned x, const unsigned y) const {
        return blackBits456[x] | whiteBits456[x] | whiteBits456[x] << 1;
    }
    // 组合出 (x, y) 所在竖行的黑棋的 Line bits
    Line blackLineBits852(const unsigned x, const unsigned y) const {
        return blackBits852[y] | whiteBits852[y] | whiteBits852[y] << 1;
    }
    // 组合出 (x, y) 所在 159 方向的黑棋的 Line bits
    Line blackLineBits159(const unsigned x, const unsigned y) const {
        unsigned r = lineRow159(x, y);
        return blackBits159[r] | whiteBits159[r] | whiteBits159[r] << 1;
    }
    // 组合出 (x, y) 所在 753 方向的黑棋的 Line bits
    Line blackLineBits753(const unsigned x, const unsigned y) const {
        unsigned r = lineRow753(x, y);
        return blackBits753[r] | whiteBits753[r] | whiteBits753[r] << 1;
    }

    // 组合出 (x, y) 所在横行的白棋的 Line bits
    Line whiteLineBits456(const unsigned x, const unsigned y) const {
        return whiteBits456[x] | blackBits456[x] | blackBits456[x] << 1;
    }
    // 组合出 (x, y) 所在竖行的白棋的 Line bits
    Line whiteLineBits852(const unsigned x, const unsigned y) const {
        return whiteBits852[y] | blackBits852[y] | blackBits852[y] << 1;
    }
    // 组合出 (x, y) 所在 159 方向的白棋的 Line bits
    Line whiteLineBits159(const unsigned x, const unsigned y) const {
        unsigned r = lineRow159(x, y);
        return whiteBits159[r] | blackBits159[r] | blackBits159[r] << 1;
    }
    // 组合出 (x, y) 所在 753 方向的白棋的 Line bits
    Line whiteLineBits753(const unsigned x, const unsigned y) const {
        unsigned r = lineRow753(x, y);
        return whiteBits753[r] | blackBits753[r] | blackBits753[r] << 1;
    }

public:
    // 按 BoardSize 创建位棋盘并初始化为空棋盘
    BitBoard(unsigned BoardSize = 15): boardSize(BoardSize) {
        resetBoard();
    }

    // 重设棋盘尺寸。与先前尺寸不同则初始化为空棋盘。
    void setBoardSize(unsigned Size) {
        if(Size == boardSize) return;
        boardSize = Size;
        resetBoard();
    }

    // 初始化为空棋盘
    void resetBoard() {
        // 每行两侧留出至少 12 bits 的墙，其中 11 bits 置为 1
        blackBits456.assign(boardSize, ~0ull << (boardSize * 2 + 12) | 0x7FF);
        whiteBits456.assign(boardSize, ~0ull << (boardSize * 2 + 12) | 0x7FF);
        blackBits852.assign(boardSize, ~0ull << (boardSize * 2 + 12) | 0x7FF);
        whiteBits852.assign(boardSize, ~0ull << (boardSize * 2 + 12) | 0x7FF);

        // 斜向先开辟空间再赋值
        blackBits159.resize(boardSize * 2 - 1);
        whiteBits159.resize(boardSize * 2 - 1);
        blackBits753.resize(boardSize * 2 - 1);
        whiteBits753.resize(boardSize * 2 - 1);

        auto fillBoardBits = [&] (int i, int j) {
            blackBits159[lineRow159(i,j)] = ~0ull << (lineSize159(i, j) * 2 + 12) | 0x7FF;
            whiteBits159[lineRow159(i,j)] = ~0ull << (lineSize159(i, j) * 2 + 12) | 0x7FF;
            blackBits753[lineRow753(i,j)] = ~0ull << (lineSize753(i, j) * 2 + 12) | 0x7FF;
            whiteBits753[lineRow753(i,j)] = ~0ull << (lineSize753(i, j) * 2 + 12) | 0x7FF;
        };
        // 只需对第一行、最后一行和第一列操作即可覆盖所有斜行
        for(int i = 0; i < (int)boardSize; ++i) {
            fillBoardBits(i, 0);
        }
        for(int j = 0; j < (int)boardSize; ++j) {
            fillBoardBits(0, j);
            fillBoardBits(boardSize - 1, j);
        }
    }

    // 返回以 (x, y) 为中心的 456 方向的 9 格 bits，可直接用作 Pattern9 的参数
    unsigned blackVici9Bits456(const short x, const short y) const {
        return blackLineBits456(x, y) >> (y * 2 + 4) & 0x3FFFF;
    }

};









