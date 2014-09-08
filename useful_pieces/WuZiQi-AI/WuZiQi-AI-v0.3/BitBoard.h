#pragma once

// �ײ�� Pattern9��Pattern13 �ֱ�ʵ���˶��޽����н���֧��
// �� BitBoard �п�ͳһ���� 9�� bits �� 13�� bits�����طֳ�������
// 

// ��������� Board ��ʱ�����ݹ���ͬ���ע�Ľ�������Ҳ��ͬ
// ��� ���� + 43 �ĵ㣬�޽�����ֱ�ӹ�ע�������ɣ���ȷ5 ������Ҫ��ע 43�����н���������Ҫ
// ��ע����������б�Ҫ�� Board ���ݹ���ֳ� 3 ���࣬�����书���໥Ӱ��
// 
// BoardNoFoul��BoardNoFoulEx5��BoardFoul �ֱ��Ӧ�޽����޽���ȷ5���Լ��н�����
// ���� BoardNoFoul �� BoardNoFoulEx5 �������������ֺڰף��ò��� const COLOR �����֣�
// BoardFoul ��Ϊ���н����޽���������������ֿ���д
// 





/********************************************************

���̳ߴ�Ϊ int BitBoard::boardSize
��������Ϊ (x, y), ���� x, y �ķ�Χ�� [0, boardSize - 1]
ֻ�������������̡������ȵ��������� v0.1 ����롣
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

    // �� PC ��������������������ʾ����
    std::vector<Line> blackBits456, whiteBits456;   // =
    std::vector<Line> blackBits852, whiteBits852;   // ||
    std::vector<Line> blackBits159, whiteBits159;   // //
    std::vector<Line> blackBits753, whiteBits753;   // \\

    // ��� (x, y) ���� 159 ��б��������ڼ���
    unsigned lineRow159(const unsigned x, const unsigned y) const {
        return x + y;
    }
    // ��� (x, y) ���� 753 ��б��������ڼ���
    unsigned lineRow753(const unsigned x, const unsigned y) const {
        return boardSize + x - y - 1;
    }
    // ��� (x, y) ���� 159 б���е�λ��
    unsigned lineOffset159(const unsigned x, const unsigned y) const {
        return (x + y > boardSize - 1)?
            (boardSize - x - 1): y;
    }
    // ��� (x, y) ���� 753 б���е�λ��
    unsigned lineOffset753(const unsigned x, const unsigned y) const {
        return (x > y)? y: x;
    }

    // ��� (x, y) ���ڵ� 159 б�еĳ���
    unsigned lineSize159(const unsigned x, const unsigned y) const {
        if(x + y <= boardSize - 1) {
            return x + y + 1;
        }
        else {
            return boardSize * 2 - x - y - 1;
        }
    }
    // ��� (x, y) ���ڵ� 753 б�еĳ���
    unsigned lineSize753(const unsigned x, const unsigned y) const {
        if(x >= y) {
            return boardSize - x + y;
        }
        else {
            return boardSize + x - y;
        }
    }

    // ��ϳ� (x, y) ���ں��еĺ���� Line bits
    Line blackLineBits456(const unsigned x, const unsigned y) const {
        return blackBits456[x] | whiteBits456[x] | whiteBits456[x] << 1;
    }
    // ��ϳ� (x, y) �������еĺ���� Line bits
    Line blackLineBits852(const unsigned x, const unsigned y) const {
        return blackBits852[y] | whiteBits852[y] | whiteBits852[y] << 1;
    }
    // ��ϳ� (x, y) ���� 159 ����ĺ���� Line bits
    Line blackLineBits159(const unsigned x, const unsigned y) const {
        unsigned r = lineRow159(x, y);
        return blackBits159[r] | whiteBits159[r] | whiteBits159[r] << 1;
    }
    // ��ϳ� (x, y) ���� 753 ����ĺ���� Line bits
    Line blackLineBits753(const unsigned x, const unsigned y) const {
        unsigned r = lineRow753(x, y);
        return blackBits753[r] | whiteBits753[r] | whiteBits753[r] << 1;
    }

    // ��ϳ� (x, y) ���ں��еİ���� Line bits
    Line whiteLineBits456(const unsigned x, const unsigned y) const {
        return whiteBits456[x] | blackBits456[x] | blackBits456[x] << 1;
    }
    // ��ϳ� (x, y) �������еİ���� Line bits
    Line whiteLineBits852(const unsigned x, const unsigned y) const {
        return whiteBits852[y] | blackBits852[y] | blackBits852[y] << 1;
    }
    // ��ϳ� (x, y) ���� 159 ����İ���� Line bits
    Line whiteLineBits159(const unsigned x, const unsigned y) const {
        unsigned r = lineRow159(x, y);
        return whiteBits159[r] | blackBits159[r] | blackBits159[r] << 1;
    }
    // ��ϳ� (x, y) ���� 753 ����İ���� Line bits
    Line whiteLineBits753(const unsigned x, const unsigned y) const {
        unsigned r = lineRow753(x, y);
        return whiteBits753[r] | blackBits753[r] | blackBits753[r] << 1;
    }

public:
    // �� BoardSize ����λ���̲���ʼ��Ϊ������
    BitBoard(unsigned BoardSize = 15): boardSize(BoardSize) {
        resetBoard();
    }

    // �������̳ߴ硣����ǰ�ߴ粻ͬ���ʼ��Ϊ�����̡�
    void setBoardSize(unsigned Size) {
        if(Size == boardSize) return;
        boardSize = Size;
        resetBoard();
    }

    // ��ʼ��Ϊ������
    void resetBoard() {
        // ÿ�������������� 12 bits ��ǽ������ 11 bits ��Ϊ 1
        blackBits456.assign(boardSize, ~0ull << (boardSize * 2 + 12) | 0x7FF);
        whiteBits456.assign(boardSize, ~0ull << (boardSize * 2 + 12) | 0x7FF);
        blackBits852.assign(boardSize, ~0ull << (boardSize * 2 + 12) | 0x7FF);
        whiteBits852.assign(boardSize, ~0ull << (boardSize * 2 + 12) | 0x7FF);

        // б���ȿ��ٿռ��ٸ�ֵ
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
        // ֻ��Ե�һ�С����һ�к͵�һ�в������ɸ�������б��
        for(int i = 0; i < (int)boardSize; ++i) {
            fillBoardBits(i, 0);
        }
        for(int j = 0; j < (int)boardSize; ++j) {
            fillBoardBits(0, j);
            fillBoardBits(boardSize - 1, j);
        }
    }

    // ������ (x, y) Ϊ���ĵ� 456 ����� 9 �� bits����ֱ������ Pattern9 �Ĳ���
    unsigned blackVici9Bits456(const short x, const short y) const {
        return blackLineBits456(x, y) >> (y * 2 + 4) & 0x3FFFF;
    }

};









