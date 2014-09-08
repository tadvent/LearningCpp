#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include "board.h"


unsigned str2pat(char *s)
{
    printf("\n%s\t", s);
    unsigned ret = 0u;
    for(int i=0; *s; ++s, i+=2)
    {
        switch(*s)
        {
        case 'X':
            set_bits(ret, i, 2, 0x3);
            break;
        case 'O':
            set_bits(ret, i, 2, 0x1);
            break;
        case '_':
            break;
        default:
            throw "main.h: str2pat()\n    Invalid char!\n";
            break;
        }
    }
    return ret;
}

void printstate(const Pattern9::State s)
{
    printf("\ns.PATTERN: ");
    for(int i=0; i<9; ++i)printf("%u ", get_bits(s.pattern, i*2, 2));

    printf("\nScore: %d\n", s.score);
    switch(s.mark)
    {
    case Pattern9::LIAN5:
        printf("连五点\n");
        break;
    case Pattern9::HUO3:
        printf("活三点\n");
        break;
    case Pattern9::MIAN3:
        printf("眠三点\n");
        break;
    case Pattern9::INVMK:
        printf("非特殊点\n");
        break;
    default:
        if(s.mark > 0xF)
        {
            printf("双四点. 防点为： %d %d\n", s.mark & 0xF, s.mark >> 4);
        }
        else
        {
            printf("冲四点. 防点为： %d\n", s.mark);
        }
        break;
    }
}

void print_board_points(const Board &b)
{
    printf("\n\n得分： 黑 %d, 白 %d", b.get_black_score(), b.get_white_score());
    printf("\n黑棋：");
    //if(b.black_lian5_num() > 0)
    {
        printf("\n连五：%d 个\n\t", b.black_lian5_num());
        for(unsigned pos = b.black_lian5_begin(); pos != Board::INVPOS; pos = b.black_next(pos))
        {
            printf(" (%d,%d)", pos >> 5, pos & 0x1F);
        }
    }
    //if(b.black_shua4_num() > 0)
    {
        printf("\n双四：%d 个\n\t", b.black_shua4_num());
        for(unsigned pos = b.black_shua4_begin(); pos != Board::INVPOS; pos = b.black_next(pos))
        {
            unsigned def = b.black_defense(pos);
            printf(" (%d,%d)-(%d,%d)-(%d,%d)", pos >> 5, pos & 0x1F,
                def >> 5 & 0x1F, def & 0x1F, def >> 15 & 0x1F, def >> 10 & 0x1F);
        }
    }
    //if(b.black_chon4_num() > 0)
    {
        printf("\n冲四：%d 个\n\t", b.black_chon4_num());
        for(unsigned pos = b.black_chon4_begin(); pos != Board::INVPOS; pos = b.black_next(pos))
        {
            unsigned def = b.black_defense(pos);
            printf(" (%d,%d)-(%d,%d)", pos >> 5, pos & 0x1F, def >> 5 & 0x1F, def & 0x1F);
        }
    }
    //if(b.black_huo3_num() > 0)
    {
        printf("\n活三：%d 个\n\t", b.black_huo3_num());
        for(unsigned pos = b.black_huo3_begin(); pos != Board::INVPOS; pos = b.black_next(pos))
        {
            printf(" (%d,%d)", pos >> 5, pos & 0x1F);
        }
    }
    //if(b.black_mian3_num() > 0)
    {
        printf("\n眠三：%d 个\n\t", b.black_mian3_num());
        for(unsigned pos = b.black_mian3_begin(); pos != Board::INVPOS; pos = b.black_next(pos))
        {
            printf(" (%d,%d)", pos >> 5, pos & 0x1F);
        }
    }

    printf("\n白棋：");
        //if(b.white_lian5_num() > 0)
    {
        printf("\n连五：%d 个\n\t", b.white_lian5_num());
        for(unsigned pos = b.white_lian5_begin(); pos != Board::INVPOS; pos = b.white_next(pos))
        {
            printf(" (%d,%d)", pos >> 5, pos & 0x1F);
        }
    }
    //if(b.white_shua4_num() > 0)
    {
        printf("\n双四：%d 个\n\t", b.white_shua4_num());
        for(unsigned pos = b.white_shua4_begin(); pos != Board::INVPOS; pos = b.white_next(pos))
        {
            unsigned def = b.white_defense(pos);
            printf(" (%d,%d)-(%d,%d)-(%d,%d)", pos >> 5, pos & 0x1F,
                def >> 5 & 0x1F, def & 0x1F, def >> 15 & 0x1F, def >> 10 & 0x1F);
        }
    }
    //if(b.white_chon4_num() > 0)
    {
        printf("\n冲四：%d 个\n\t", b.white_chon4_num());
        for(unsigned pos = b.white_chon4_begin(); pos != Board::INVPOS; pos = b.white_next(pos))
        {
            unsigned def = b.white_defense(pos);
            printf(" (%d,%d)-(%d,%d)", pos >> 5, pos & 0x1F, def >> 5 & 0x1F, def & 0x1F);
        }
    }
    //if(b.white_huo3_num() > 0)
    {
        printf("\n活三：%d 个\n\t", b.white_huo3_num());
        for(unsigned pos = b.white_huo3_begin(); pos != Board::INVPOS; pos = b.white_next(pos))
        {
            printf(" (%d,%d)", pos >> 5, pos & 0x1F);
        }
    }
    //if(b.white_mian3_num() > 0)
    {
        printf("\n眠三：%d 个\n\t", b.white_mian3_num());
        for(unsigned pos = b.white_mian3_begin(); pos != Board::INVPOS; pos = b.white_next(pos))
        {
            printf(" (%d,%d)", pos >> 5, pos & 0x1F);
        }
    }
}

int main()
{
    printf("Pattern::State: %d bytes\n", sizeof(Pattern9::State));

    ////////////////////////////////////////////////////////////
    // Pattern9 TEST
    //Pattern9 pat9;
    //printstate(pat9(str2pat("OOO___OOO")));
    //printstate(pat9(str2pat("OO____OO_")));
    //printstate(pat9(str2pat("OO____OO_")));
    //printstate(pat9(str2pat("OO____OOX")));

    //printstate(pat9(str2pat("OOO______")));
    //printstate(pat9(str2pat("OO___OO__")));
    //printstate(pat9(str2pat("_________")));

    //printstate(pat9(str2pat("OO___O__O")));
    //printstate(pat9(str2pat("O_O_O_O_O")));
    //printstate(pat9(str2pat("O_O___O_O")));
    //printstate(pat9(str2pat("O_O_O___O")));
    //printstate(pat9(str2pat("_O_O___O_")));
    //printstate(pat9(str2pat("O_O___O_X")));

    //////////////////////////////////////////////////////////////////////////
    printf("Board::Color_Pos_State: %d bytes\n", sizeof(Board::Color_Pos_State));
    printf("Board: %d bytes\n", sizeof(Board));

    //////////////////////////////////////////////////////////////////////////
    // Board TEST
    //Board bd;

    //bd.move(2, 1, BLACK);
    //bd.move(2, 4, BLACK);
    //bd.move(2, 5, BLACK);
    //bd.move(2, 7, BLACK);


    //bd.move(4, 4, BLACK);
    //print_board_points(bd);
    //bd.move(3, 2, WHITE);
    //print_board_points(bd);
    //bd.move(1, 7, BLACK);
    //print_board_points(bd);
    //bd.move(4, 6, BLACK);

    //bd.remove(4, 6);
    //print_board_points(bd);
    //bd.remove(1, 7);
    //print_board_points(bd);
    //bd.remove(3, 2);
    //print_board_points(bd);

    //bd.move(2, 1, WHITE);
    //bd.move(2, 4, WHITE);
    //bd.move(2, 5, WHITE);
    //bd.move(2, 7, WHITE);
    //bd.move(4, 4, WHITE);
    //bd.move(3, 2, WHITE);
    //bd.move(1, 7, WHITE);
    //bd.move(4, 6, WHITE);
    //print_board_points(bd);

    //////////////////////////////////////////////////////////////////////////
    // bd.move() bd.remove() 有 ver0.1 版, ver0.2版 以及 fast_move() 版，测试三者的速度差别
    
    // ver0.1
    Board b;
    clock_t start, finish;

    start = clock();
    for(int i = 0; i < 6800; ++i)
    {
        b.move(7, 7, BLACK);
        b.move(6, 8, WHITE);
        b.move(7, 9, BLACK);
        b.move(7, 8, WHITE);
        b.move(8, 8, BLACK);
        b.move(9, 7, WHITE);
        b.move(9, 9, BLACK);
        b.move(10, 10, WHITE);
        b.move(8, 9, BLACK);
        b.move(6, 9, WHITE);
        b.move(8, 7, BLACK);
        b.move(8, 6, WHITE);
        b.move(8, 10, BLACK);
        b.move(8, 11, WHITE);
        b.move(10, 8, BLACK);
        b.move(11, 7, WHITE);
        b.move(6, 10, BLACK);
        b.move(5, 10, WHITE);
        b.move(4, 8, BLACK);
        b.move(7, 11, WHITE);
        b.move(4, 7, BLACK);
        b.move(5, 7, WHITE);
        b.move(4, 6, BLACK);
        b.move(4, 11, WHITE);
        b.move(3, 12, BLACK);
        b.move(4, 5, WHITE);
        b.move(5, 6, BLACK);
        b.move(6, 6, WHITE);
        b.move(6, 5, BLACK);
        b.move(3, 8, WHITE);
        b.move(3, 7, BLACK);
        b.move(4, 4, WHITE);

        b.remove(4, 4);
        b.remove(3, 7);
        b.remove(3, 8);
        b.remove(6, 5);
        b.remove(6, 6);
        b.remove(5, 6);
        b.remove(4, 5);
        b.remove(3, 12);
        b.remove(4, 11);
        b.remove(4, 6);
        b.remove(5, 7);
        b.remove(4, 7);
        b.remove(7, 11);
        b.remove(4, 8);
        b.remove(5, 10);
        b.remove(6, 10);
        b.remove(11, 7);
        b.remove(10, 8);
        b.remove(8, 11);
        b.remove(8, 10);
        b.remove(8, 6);
        b.remove(8, 7);
        b.remove(6, 9);
        b.remove(8, 9);
        b.remove(10, 10);
        b.remove(9, 9);
        b.remove(9, 7);
        b.remove(8, 8);
        b.remove(7, 8);
        b.remove(7, 9);
        b.remove(6, 8);
        b.remove(7, 7);
    }
    finish = clock();
    printf("Time: %.3f secs.\n", double(finish - start)/ CLOCKS_PER_SEC);

    putchar('\n');
    system("pause");
}

