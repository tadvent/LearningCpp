#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include "PatternMatch.h"
#include "AI.h"

void printbits(unsigned num)
{
    for(int i=7; i>=0; --i)
    {
        printf("%u ", get_bits(num, i*4, 4));
    }
    putchar('\n');
}

void printmark(unsigned mark)
{
    unsigned pos = get_bits(mark, 0, 4);
    switch(get_bits(mark, 4, 4))
    {
    case Pattern9::LIAN5:
        printf("五连：%u\n", pos);
        break;
    case Pattern9::SHUA4:
        printf("双四/四连：%u\t防一 %u\t防二 %u\n", pos, pos + get_bits(mark, 8, 4) - 4, pos + get_bits(mark, 12, 4) - 4);
        break;
    case Pattern9::CHON4:
        printf("冲四：%u\t防 %u\n", pos, pos + get_bits(mark, 8, 4) - 4);
        break;
    case Pattern9::MIAN3:
        printf("眠三：%u\n", pos);
        break;
    case Pattern9::INVMK & 0xF:
        break;
    default:
        printf("活三：%u\t防一 %u\t防二 %u",
            pos, pos + get_bits(mark, 4, 4) - 4, pos + get_bits(mark, 8, 4) - 4);
        if(get_bits(mark, 12, 4) != Pattern9::INVMK)
        {
            printf("\t防三 %u", pos + get_bits(mark, 12, 4) - 4);
        }
        putchar('\n');
    }
}
void printstate(const Pattern9::State s)
{
    printf("\ns.PATTERN: ");
    for(int i=0; i<9; ++i)printf("%u ", get_bits(s.pattn, i*2, 2));
    printf("\ns.JUMP:\t%u\n", s.jump);
    printf("最高有效格：\t%u\n", s.max_valid);
    printf("下一次低4位有效：\t%s\n", s.next_low_valid? "Yes":"No");
    printf("s.SCORE:\t%u\n", s.score);
    printmark(s.move0);
    printmark(s.move1);
    printmark(s.move2);
    printmark(s.move3);
    int mian3l = get_bits(s.mian3, 0, 4);
    printf("低4格眠三数：%u\n", mian3l);
    for(int i=0; i<mian3l; ++i)printf("%u ", get_bits(s.mian3, 8+4*i, 4));
    if(mian3l > 0)putchar('\n');
    int mian3h = get_bits(s.mian3, 4, 4);
    printf("高4格眠三数：%u\n", mian3h);
    for(int i=0; i<mian3h; ++i)printf("%u ", get_bits(s.mian3, 8+4*(mian3l+i), 4));
    if(mian3h > 0)putchar('\n');
}

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

void print_board_state(const Board &b, short x, short y, COLOR c)
{
    printf("\n\n(%d, %d) %s\n", x, y, c == BLACK? "黑":"白");
    printf("黑： %d\t白： %d\n", b.get_black_score(), b.get_white_score());
    if(b.black_lian5_num() > 0)
    {
        printf("黑五连 %d 个： ", b.black_lian5_num());
        for(unsigned p = b.black_lian5_begin(); p != Board::INVPOS; p = b.black_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    if(b.black_shua4_num() > 0)
    {
        printf("黑双四 %d 个： ", b.black_shua4_num());
        for(unsigned p = b.black_shua4_begin(); p != Board::INVPOS; p = b.black_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    if(b.black_chn43_num() > 0)
    {
        printf("黑四三 %d 个： ", b.black_chn43_num());
        for(unsigned p = b.black_chn43_begin(); p != Board::INVPOS; p = b.black_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    if(b.black_chon4_num() > 0)
    {
        printf("黑冲四 %d 个： ", b.black_chon4_num());
        for(unsigned p = b.black_chon4_begin(); p != Board::INVPOS; p = b.black_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    if(b.black_shua3_num() > 0)
    {
        printf("黑双三 %d 个： ", b.black_shua3_num());
        for(unsigned p = b.black_shua3_begin(); p != Board::INVPOS; p = b.black_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    if(b.black_huo3_num() > 0)
    {
        printf("黑活三 %d 个： ", b.black_huo3_num());
        for(unsigned p = b.black_huo3_begin(); p != Board::INVPOS; p = b.black_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    if(b.black_mian3_num() > 0)
    {
        printf("黑眠三 %d 个： ", b.black_mian3_num());
        for(unsigned p = b.black_mian3_begin(); p != Board::INVPOS; p = b.black_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    //
    if(b.white_lian5_num() > 0)
    {
        printf("白五连 %d 个： ", b.white_lian5_num());
        for(unsigned p = b.white_lian5_begin(); p != Board::INVPOS; p = b.white_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    if(b.white_shua4_num() > 0)
    {
        printf("白双四 %d 个： ", b.white_shua4_num());
        for(unsigned p = b.white_shua4_begin(); p != Board::INVPOS; p = b.white_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    if(b.white_chn43_num() > 0)
    {
        printf("白四三 %d 个： ", b.white_chn43_num());
        for(unsigned p = b.white_chn43_begin(); p != Board::INVPOS; p = b.white_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    if(b.white_chon4_num() > 0)
    {
        printf("白冲四 %d 个： ", b.white_chon4_num());
        for(unsigned p = b.white_chon4_begin(); p != Board::INVPOS; p = b.white_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    if(b.white_shua3_num() > 0)
    {
        printf("白双三 %d 个： ", b.white_shua3_num());
        for(unsigned p = b.white_shua3_begin(); p != Board::INVPOS; p = b.white_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    if(b.white_huo3_num() > 0)
    {
        printf("白活三 %d 个： ", b.white_huo3_num());
        for(unsigned p = b.white_huo3_begin(); p != Board::INVPOS; p = b.white_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    if(b.white_mian3_num() > 0)
    {
        printf("白眠三 %d 个： ", b.white_mian3_num());
        for(unsigned p = b.white_mian3_begin(); p != Board::INVPOS; p = b.white_next(p))
        {
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
}

void print_black_vc4(WzqAI &ai)
{
    int val = ai.black_vc4(-10000);
    if(val > 9000)
    {
        printf("VCF: %d, (%d,%d).\n", val, ai.vc4_move >> 8, ai.vc4_move & 0xFF);
    }
    else
    {
        printf("VCF: 0.\n");
    }
    printf("HashTable Ratio: %.4f%%\n", ai.board_hash.occupy_ratio() * 100);
}

void print_black_vc4_and_defense(WzqAI &ai)
{
    int val = ai.black_vc4_and_defense(-10000);
    if(val > 9000)
    {
        printf("黑棋有 VCF: %d\n可能的防点是：", val);
        for(int i=0; i<(int)ai.vc4_defense.size(); ++i)
        {
            unsigned p = ai.vc4_defense[i];
            printf("(%d,%d) ", p>>8, p&0xFF);
        }
        putchar('\n');
    }
    else
    {
        printf("黑棋无 VCF\n");
    }
    printf("HashTable Ratio: %.4f%%\n", ai.board_hash.occupy_ratio() * 100);
}

int main() try
{
    /////////////////////////////////////////////////////////
    // Pattern5 TEST
    //printf("sizeof(Pattern9::state): %d\n", sizeof(Pattern9::State));

    //Pattern5 pat5;

    //printbits(pat5(str2pat("_OOO_")));
    //printbits(pat5(str2pat("_O_O_")));
    //printbits(pat5(str2pat("_OO__")));
    //printbits(pat5(str2pat("O___O")));
    //printbits(pat5(str2pat("_____")));
    //putchar('\n');

    //printbits(pat5(str2pat("_XOO_")));
    //printbits(pat5(str2pat("_O_OX")));
    //printbits(pat5(str2pat("_XO_X")));
    //printbits(pat5(str2pat("O__XO")));
    //printbits(pat5(str2pat("XXXXX")));

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
    // Pattern9 speed TEST
    //puts("\n");
    //clock_t start, finish;
    //unsigned test_pat = str2pat("OO____OO_");
    //start = clock();
    //Pattern9::State s;
    //s.move0 = 0u;
    //for(int i=0; i<118000000; ++i)
    //{
    //    s.move0 ^= pat9(test_pat).move0;
    //}
    //finish = clock();
    //printf("\nTime: %f secs.\n", double(finish - start)/CLOCKS_PER_SEC);


    //////////////////////////////////////////////////////////////////////////
    // BitBoard TEST
    //BitBoard bb(7, 4);
    //BitBoard::Line l;
    //bb.add_stone(0, 2, BLACK);
    //bb.add_stone(1, 4, WHITE);
    //bb.add_stone(2, 6, BLACK);
    //bb.add_stone(2, 0, WHITE);
    //l = bb.black_linebits_159(0, 0);
    //l = bb.white_linebits_159(2, 0);
    //l = bb.black_linebits_852(1, 4);
    //l = bb.white_linebits_753(0, 3);

    //l = bb.black_vici9bits_456(0, 2);
    //l = bb.black_vici9bits_456(0, 3);
    //l = bb.white_vici9bits_852(2, 0);
    //l = bb.white_vici9bits_753(1, 4);

    //bb.remove_stone(0, 2, BLACK);
    //l = bb.black_linebits_456(0, 4);
    //bb.remove_stone(1, 4, WHITE);
    //l = bb.white_linebits_852(3, 4);
    
    //////////////////////////////////////////////////////////////////////////
    // Board TEST
    //Board bd;
    //bd.move(2, 3, BLACK);
    //print_board_state(bd, 2, 3, BLACK);
    //bd.move(4, 5, WHITE);
    //print_board_state(bd, 4, 5, WHITE);
    //bd.move(5, 3, BLACK);
    //print_board_state(bd, 5, 3, BLACK);
    //bd.move(5, 4, WHITE);
    //print_board_state(bd, 5, 4, WHITE);
    //bd.move(6, 3, BLACK);
    //print_board_state(bd, 6, 3, BLACK);
    //bd.move(6, 5, WHITE);
    //print_board_state(bd, 6, 5, WHITE);

    //bd.move(4, 3, BLACK);
    //print_board_state(bd, 4, 3, BLACK);
    //bd.move(3, 3, WHITE);
    //print_board_state(bd, 3, 3, WHITE);
    //bd.move(7, 5, BLACK);
    //print_board_state(bd, 7, 5, BLACK);
    //bd.move(5, 6, WHITE);
    //print_board_state(bd, 5, 6, WHITE);
    //bd.move(7, 4, BLACK);
    //print_board_state(bd, 7, 4, BLACK);
    //bd.move(7, 6, WHITE);
    //print_board_state(bd, 7, 6, WHITE);
    //bd.move(7, 1, BLACK);
    //print_board_state(bd, 7, 1, BLACK);
    //bd.move(4, 8, WHITE);
    //print_board_state(bd, 4, 8, WHITE);

    //puts("============================");
    //bd.backtrace();
    //print_board_state(bd, 0, 0, BLOCK);
    //bd.backtrace();
    //print_board_state(bd, 0, 0, BLOCK);
    //bd.backtrace();
    //print_board_state(bd, 0, 0, BLOCK);
    //bd.backtrace();
    //print_board_state(bd, 0, 0, BLOCK);
    
    //////////////////////////////////////////////////////////////////////////
    // Board Performance TEST
    //WzqAI ai;

    //clock_t start, finish;
    //start = clock();

    //for(int i = 0; i < 9000; ++i)
    //{
    //    ai.board.move(7, 7, BLACK);
    //    ai.board.move(6, 8, WHITE);
    //    ai.board.move(7, 9, BLACK);
    //    ai.board.move(7, 8, WHITE);
    //    ai.board.move(8, 8, BLACK);
    //    ai.board.move(9, 7, WHITE);
    //    ai.board.move(9, 9, BLACK);
    //    ai.board.move(10, 10, WHITE);
    //    ai.board.move(8, 9, BLACK);
    //    ai.board.move(6, 9, WHITE);
    //    ai.board.move(8, 7, BLACK);
    //    ai.board.move(8, 6, WHITE);
    //    ai.board.move(8, 10, BLACK);
    //    ai.board.move(8, 11, WHITE);
    //    ai.board.move(10, 8, BLACK);
    //    ai.board.move(11, 7, WHITE);
    //    ai.board.move(6, 10, BLACK);
    //    ai.board.move(5, 10, WHITE);
    //    ai.board.move(4, 8, BLACK);
    //    ai.board.move(7, 11, WHITE);
    //    ai.board.move(4, 7, BLACK);
    //    ai.board.move(5, 7, WHITE);
    //    ai.board.move(4, 6, BLACK);
    //    ai.board.move(4, 11, WHITE);
    //    ai.board.move(3, 12, BLACK);
    //    ai.board.move(4, 5, WHITE);
    //    ai.board.move(5, 6, BLACK);
    //    ai.board.move(6, 6, WHITE);
    //    ai.board.move(6, 5, BLACK);
    //    ai.board.move(3, 8, WHITE);
    //    ai.board.move(3, 7, BLACK);
    //    ai.board.move(4, 4, WHITE);

    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //    ai.board.backtrace();
    //}
    //finish = clock();

    //printf("Time: %.3f secs.\n", double(finish - start)/ CLOCKS_PER_SEC);
    
    //////////////////////////////////////////////////////////////////////////
    // AI Board TEST
    WzqAI ai;
    //ai.board.move(7, 7, BLACK);
    //ai.board.move(7, 8, BLACK);
    //ai.board.move(7, 9, BLACK);
    //ai.board.move(8, 7, BLACK);
    //ai.board.move(6, 7, BLACK);
    //ai.board.move(9, 6, BLACK);

    //ai.board.move(6, 8, WHITE);
    //ai.board.move(7, 6, WHITE);
    //ai.board.move(8, 9, WHITE);
    //ai.board.move(9, 7, WHITE);
    //ai.board.move(10, 5, WHITE);
    //print_black_vc4(ai);

    //print_black_vc4_and_defense(ai);
    ///////////////////////////////////////////////
    
    //ai.board.move(7, 7, BLACK);
    //ai.board.move(7, 8, BLACK);
    //ai.board.move(7, 9, BLACK);
    //ai.board.move(7, 6, WHITE);
    //ai.board.move(6, 8, WHITE);
    //ai.board.move(8, 7, BLACK);
    //ai.board.move(9, 7, WHITE);
    //ai.board.move(6, 9, BLACK);
    //ai.board.move(9, 6, WHITE);
    //ai.board.move(6, 7, BLACK);
    //ai.board.move(7, 10, WHITE);
    //ai.board.move(8, 9, BLACK);
    //ai.board.move(9, 9, WHITE);
    //ai.board.move(9, 8, BLACK);
    //ai.board.move(5, 10, WHITE);
    //ai.board.move(4, 8, BLACK);
    //ai.board.move(9, 10, WHITE);
    //print_black_vc4(ai);
    //print_black_vc4_and_defense(ai);
    ///////////////////////////////////////////////
    
    ai.move(7, 7, BLACK);
    ai.move(6, 8, WHITE);
    ai.move(7, 9, BLACK);
    ai.move(7, 8, WHITE);
    ai.move(8, 8, BLACK);
    ai.move(9, 7, WHITE);
    ai.move(9, 9, BLACK);
    ai.move(10, 10, WHITE);
    ai.move(8, 9, BLACK);
    ai.move(6, 9, WHITE);
    ai.move(8, 7, BLACK);
    ai.move(8, 6, WHITE);
    ai.move(8, 10, BLACK);
    ai.move(8, 11, WHITE);
    ai.move(10, 8, BLACK);
    ai.move(11, 7, WHITE);
    ai.move(6, 10, BLACK);
    ai.move(5, 10, WHITE);
    ai.move(4, 8, BLACK);
    //print_black_vc4(ai);
    print_black_vc4_and_defense(ai);
    ai.move(7, 11, WHITE);
    ai.move(4, 7, BLACK);
    //print_black_vc4(ai);
    print_black_vc4_and_defense(ai);
    ai.move(5, 7, WHITE);
    ai.move(4, 6, BLACK);
    ai.move(4, 11, WHITE);
    ai.move(3, 12, BLACK);
    ai.move(4, 5, WHITE);
    ai.move(5, 6, BLACK);
    //print_black_vc4(ai);
    print_black_vc4_and_defense(ai);
    ai.move(6, 6, WHITE);
    ai.move(6, 5, BLACK);
    ai.move(3, 8, WHITE);
    ai.move(6, 12, WHITE);
    ai.move(2, 5, WHITE);
    //ai.move(1, 4, WHITE);
    ai.move(3, 7, BLACK);
    //print_black_vc4(ai);
    print_black_vc4_and_defense(ai);
    ai.move(4, 4, WHITE);
    //print_black_vc4(ai);
    print_black_vc4_and_defense(ai);

    //////////////////////////////////////////////////////////////////////////
    // BoardHash TEST
    //BoardHash<int> bh;
    //bool found;
    //bh.move(7, 7, BLACK);
    //bh.get_data(WHITE, found) = 1;
    //bh.move(8, 8, WHITE);
    //bh.get_data(BLACK, found) = 2;
    //bh.move(9, 9, BLACK);
    //bh.get_data(WHITE, found) = 3;
    //bh.remove(8, 8);
    //bh.remove(9, 9);
    //printf("Status: %d\n", bh.get_data(WHITE, found));

    //bh.remove(7, 7);
    //bh.move(8, 8, WHITE);
    //bh.move(7, 7, BLACK);
    //printf("Status: %d\n", bh.get_data(BLACK, found));


    system("pause");
}
catch(char *e)
{
    printf("\n%s", e);
    system("pause");
}
