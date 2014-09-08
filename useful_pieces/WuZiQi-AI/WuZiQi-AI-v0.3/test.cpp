

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <ctime>

#include "Pattern.h"

#include "test.h"

// print s
// "OO____OOX" -> 0x35005
unsigned str2pat(char *s) {
    printf("%s\t", s);
    unsigned ret = 0u;
    for(int i=0; *s; ++s, i+=2) {
        switch(*s) {
        case 'X':
            set_bits(ret, i, 2, BLOCK);
            break;
        case 'O':
            set_bits(ret, i, 2, STONE);
            break;
        case '_':
            set_bits(ret, i, 2, BLANK);
            break;
        default:
            throw "test.cpp: str2pat()\n    Invalid char!\n";
            break;
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////
// Pattern5 TEST

Pattern5 objPat5;
bool singlePattern5Test( unsigned pat5, unsigned jump, unsigned attLevel ) {
    unsigned state = objPat5.getState(pat5);
    if(state != (jump << 4 | attLevel)) {
        printf("Error!\n");
        throw "TEST FAILED!\n";
        return false;
    }
    else {
        printf("PASS\n");
        return true;
    }
    return false;
}


bool testPattern5() {
    printf("Start test Pattern5:\n");
    singlePattern5Test(str2pat("_OOO_"), 0, 4);
    singlePattern5Test(str2pat("_O_O_"), 0, 3);
    singlePattern5Test(str2pat("_OO__"), 0, 3);
    singlePattern5Test(str2pat("O___O"), 0, 3);
    singlePattern5Test(str2pat("_____"), 0, 1);
    singlePattern5Test(str2pat("OOOOO"), 0, 6);
    putchar('\n');

    singlePattern5Test(str2pat("_XOO_"), 4, 1);
    singlePattern5Test(str2pat("_O_OX"), 10, 1);
    singlePattern5Test(str2pat("_XO_X"), 10, 1);
    singlePattern5Test(str2pat("O__XO"), 8, 1);
    singlePattern5Test(str2pat("XXXXX"), 10, 1);
    putchar('\n');

    return true;
}


/////////////////////////////////////////////////////////
// Pattern9 TEST

Pattern9 objPat9;
bool singlePattern9Test( unsigned pat9, unsigned midscore, unsigned allscore, unsigned attMark) {
    Pattern9::State st = objPat9.getState(pat9);
    if(st.midScore != midscore || st.allScore != allscore || st.atkLevel != attMark){
        printf("Error!\n");
        printf("    Pat9 midScore: %d, allScore: %d, mark: %d\n", st.midScore, st.allScore, st.atkLevel);
        printf("    Expect midscore: %d, allscore: %d, mark: %d\n", midscore, allscore, attMark);
        throw "TEST FAILED!\n";
        return false;
    }
    else {
        printf("PASS\n");
        return true;
    }
    return false;
}

bool testPattern9() {
    printf("Start test Pattern9:\n");
    printf("\nSizeof(Pattern9::State)\t%d\n", sizeof(Pattern9::State));

    singlePattern9Test(str2pat("OOOO_XXXX"), 1,  4, PT_LIAN5);
    singlePattern9Test(str2pat("OOOO_OXXX"), 2,  8, PT_LIAN5);
    singlePattern9Test(str2pat("XOOO_OXXX"), 1,  4, PT_LIAN5);
    singlePattern9Test(str2pat("XOOO_OOXX"), 2,  8, PT_LIAN5);
    singlePattern9Test(str2pat("__OO_OO__"), 5, 14, PT_LIAN5);
    putchar('\n');

    singlePattern9Test(str2pat("_OOO__XXX"), 2,  6, PT_LIAN4);
    singlePattern9Test(str2pat("XX_O_OO_X"), 2,  6, PT_LIAN4);
    singlePattern9Test(str2pat("__OO_O___"), 5, 11, PT_LIAN4);
    singlePattern9Test(str2pat("OOO___OOO"), 5, 12, PT_SHUA4);
    singlePattern9Test(str2pat("XO_O_O_OX"), 3,  8, PT_SHUA4);
    singlePattern9Test(str2pat("XXO__OO_O"), 3,  8, PT_SHUA4);
    singlePattern9Test(str2pat("O_OO__OXX"), 3,  8, PT_SHUA4);
    singlePattern9Test(str2pat("XOO__O_OO"), 4, 10, PT_SHUA4);
    singlePattern9Test(str2pat("OO_O__OOX"), 4, 10, PT_SHUA4);
    singlePattern9Test(str2pat("XXO__OOOX"), 2,  6, PT_CHON4);
    singlePattern9Test(str2pat("OOO__XXXX"), 1,  3, PT_CHON4);
    singlePattern9Test(str2pat("XOOO__XXX"), 1,  3, PT_CHON4);
    singlePattern9Test(str2pat("XO_O_OXXX"), 1,  3, PT_CHON4);
    singlePattern9Test(str2pat("XXO__OOXX"), 1,  3, PT_CHON4);
    singlePattern9Test(str2pat("OOO______"), 5,  6, PT_CHON4);
    singlePattern9Test(str2pat("_OOO_X___"), 1,  3, PT_CHON4);
    putchar('\n');

    singlePattern9Test(str2pat("OO____OO_"), 5,  8, PT_LIAN3);
    singlePattern9Test(str2pat("X_OO___XX"), 2,  4, PT_LIAN3);
    singlePattern9Test(str2pat("_OO___XXX"), 2,  4, PT_LIAN3);
    singlePattern9Test(str2pat("XX_O_O__X"), 2,  4, PT_LIAN3);
    singlePattern9Test(str2pat("XX_O__O_X"), 2,  4, PT_LIAN3);
    singlePattern9Test(str2pat("XXX__O_O_"), 2,  4, PT_LIAN3);
    singlePattern9Test(str2pat("OO___OO__"), 5, 10, PT_LIAN3);
    singlePattern9Test(str2pat("_O_O___O_"), 5,  8, PT_LIAN3);
    singlePattern9Test(str2pat("OO____OOX"), 4,  6, PT_SHUA3);
    singlePattern9Test(str2pat("O_O___O__"), 5,  7, PT_SHUA3);
    singlePattern9Test(str2pat("O_O___OXX"), 3,  5, PT_SHUA3);
    singlePattern9Test(str2pat("X_O___O_O"), 4,  6, PT_SHUA3);
    singlePattern9Test(str2pat("O_O___O_O"), 5,  8, PT_SHUA3);
    singlePattern9Test(str2pat("O__O___OX"), 4,  6, PT_MIAN3);
    singlePattern9Test(str2pat("XX_O_O_XX"), 1,  2, PT_MIAN3);
    singlePattern9Test(str2pat("XXX__OO_X"), 1,  2, PT_MIAN3);
    singlePattern9Test(str2pat("OO___O__O"), 5,  8, PT_MIAN3);
    singlePattern9Test(str2pat("XXXX__OO_"), 1,  2, PT_MIAN3);
    singlePattern9Test(str2pat("OO_______"), 5,  3, PT_MIAN3);
    singlePattern9Test(str2pat("OO___XXXX"), 1,  2, PT_MIAN3);
    singlePattern9Test(str2pat("OO_____OO"), 5,  6, PT_MIAN3);
    putchar('\n');

    singlePattern9Test(str2pat("_O____XXX"), 2,  2, PT_LIAN2);
    singlePattern9Test(str2pat("X____O_XX"), 2,  2, PT_LIAN2);
    singlePattern9Test(str2pat("X_O____XX"), 2,  2, PT_LIAN2);
    singlePattern9Test(str2pat("O____OXXX"), 2,  2, PT_MIAN2);
    singlePattern9Test(str2pat("_O___XXXX"), 1,  1, PT_MIAN2);
    putchar('\n');

    singlePattern9Test(str2pat("_X_____X_"), 1,  0, PT_INVMV);
    singlePattern9Test(str2pat("__X____X_"), 0,  0, PT_INVMV);
    singlePattern9Test(str2pat("__XO__OX_"), 0,  0, PT_INVMV);
    singlePattern9Test(str2pat("__X__O_X_"), 0,  0, PT_INVMV);
#if 0
    //singlePattern9Test(str2pat("__X_O__X_"),  0, PT_INVMV);
    //singlePattern9Test(str2pat("O_O_O___O"), 10, PT_INVMV);
    //singlePattern9Test(str2pat("O_O_O_O_O"), 13, PT_INVMV);
    //singlePattern9Test(str2pat("____O____"),  5, PT_INVMV);
    //singlePattern9Test(str2pat("OOOOOOOOO"), 25, PT_INVMV);
    //singlePattern9Test(str2pat("__XOOOOOX"),  5, PT_INVMV);
#endif
    putchar('\n');

    return true;
}

/////////////////////////////////////////////////////////
// Pattern13 TEST

Pattern13 objPat13;
bool singlePattern13Test(unsigned pat13, int midscore, int allscore, unsigned atkLevel) {
    Pattern13::State st = objPat13.getState(pat13);
    if(st.midScore != midscore || st.allScore != allscore || st.atkLevel != atkLevel){
        printf("Error!\n");
        printf("    Pat13 midscore: %d, allscore: %d, attack: %d\n", st.midScore, st.allScore, st.atkLevel);
        printf("    Expect midscore: %d, allscore: %d, attack: %d\n", midscore, allscore, atkLevel);
        throw "TEST FAILED!\n";
        return false;
    }
    else {
        printf("PASS\n");
        return true;
    }
    return false;
}

bool testPattern13() {
    printf("Start test Pattern13:\n");
    //printf("\nSizeof(Pattern13::P11State)\t%d\n", sizeof(Pattern13::P11State));
    printf("Sizeof(Pattern13::State)\t%d\n", sizeof(Pattern13::State));

    singlePattern13Test(str2pat("XOOOOO_XXXXXO"),  -5, 0, PT_LIAN6);
    singlePattern13Test(str2pat("OOOOOO_XOOXXO"),   0, 0, PT_LIAN6);
    singlePattern13Test(str2pat("_XOOOO_OXXXX_"),   0, 0, PT_LIAN6);
    singlePattern13Test(str2pat("_OOOOO_OOOOOX"), -10, 0, PT_LIAN6);
    singlePattern13Test(str2pat("XOOOOO_OOOOOO"),  -5, 0, PT_LIAN6);
    singlePattern13Test(str2pat("OOXOOO_OOXXO_"),   0, 0, PT_LIAN6);
    singlePattern13Test(str2pat("_O__OO_OOO_OO"),  -3, 0, PT_LIAN6);
    singlePattern13Test(str2pat("XO__OO_OOO_O_"),  -7, 0, PT_LIAN6);
    singlePattern13Test(str2pat("OXXXXX_OOOOO_"),  -5, 0, PT_LIAN6);
    singlePattern13Test(str2pat("_XXXXX_OOOOOO"),   0, 0, PT_LIAN6);
    //singlePattern13Test(str2pat("OOOOOOOOOOO"), 0, PT_INVMV);
    //singlePattern13Test(str2pat("XXXXXXXXXXX"), 0, PT_INVMV);
    putchar('\n');

    singlePattern13Test(str2pat("OXOOOO_XXXXOO"),   1,  4, PT_LIAN5);
    singlePattern13Test(str2pat("_OXOOO_OXXXO_"),   1,  4, PT_LIAN5);
    singlePattern13Test(str2pat("OOX_OO_OOXXOX"),   1,  4, PT_LIAN5);
    singlePattern13Test(str2pat("X___OO_OO____"),  -3,  4, PT_LIAN5);
    singlePattern13Test(str2pat("X___OO_OO___O"),  -1,  4, PT_LIAN5);
    singlePattern13Test(str2pat("O___OO_OO___O"),   1,  4, PT_LIAN5);
    singlePattern13Test(str2pat("_____O_OOO__X"),  -3,  4, PT_LIAN5);
    singlePattern13Test(str2pat("O____O_OOO___"),  -2,  4, PT_LIAN5);
    singlePattern13Test(str2pat("X____O_OOO__O"),   0,  4, PT_LIAN5);
    singlePattern13Test(str2pat("O____O_OOO__O"),   1,  4, PT_LIAN5);
    singlePattern13Test(str2pat("_O_OOO_O_OOO_"),  -7,  4, PT_LIAN5);
    singlePattern13Test(str2pat("OO_OOO_O_OOOX"),  -3,  4, PT_LIAN5);
    singlePattern13Test(str2pat("_O_OOO_O_OOOO"),  -3,  4, PT_LIAN5);
    singlePattern13Test(str2pat("OO_OOO_O_OOOO"),   1,  4, PT_LIAN5);
    singlePattern13Test(str2pat("X_OOOO__OOOOX"),  -7,  4, PT_LIAN5);
    singlePattern13Test(str2pat("O_OOOO__OOOOX"),  -3,  4, PT_LIAN5);
    singlePattern13Test(str2pat("__OOOO_XOOOOX"),  -3,  4, PT_LIAN5);
    putchar('\n');

    singlePattern13Test(str2pat("XX_OOO__XXXO_"),   2,  6, PT_LIAN4);
    singlePattern13Test(str2pat("_O_OOO__XXXOX"),  -3,  3, PT_CHON4);
    singlePattern13Test(str2pat("OO_OOO__XXXOO"),   1,  3, PT_CHON4);
    singlePattern13Test(str2pat("XOXX_O_OO_XOO"),   2,  6, PT_LIAN4);
    singlePattern13Test(str2pat("____OO_O____X"),  -1,  6, PT_LIAN4);
    singlePattern13Test(str2pat("XO__OO_O___O_"),  -3,  6, PT_LIAN4);
    singlePattern13Test(str2pat("OO__OO_O___O_"),   0,  6, PT_LIAN4);
    singlePattern13Test(str2pat("X_O_OO_O__O_X"),  -4,  3, PT_CHON4);
    singlePattern13Test(str2pat("__O_OO_O__O_O"),  -2,  3, PT_CHON4);
    singlePattern13Test(str2pat("_O__OO_O_O___"),  -4,  3, PT_CHON4);
    singlePattern13Test(str2pat("XO__OO_O_O__O"),  -2,  3, PT_CHON4);
    singlePattern13Test(str2pat("X_O_OO_O_O___"),  -5,  0, PT_INVMV);
    singlePattern13Test(str2pat("_XOOO___OOOXX"),   2,  6, PT_SHUA4);
    singlePattern13Test(str2pat("_XOOO___OOOO_"),  -3,  3, PT_CHON4);
    singlePattern13Test(str2pat("_XOOO___OOOOO"),   1,  3, PT_CHON4);
    singlePattern13Test(str2pat("OXXO_O_O_OXX_"),   2,  6, PT_SHUA4);
    singlePattern13Test(str2pat("_XXO_O_O_O_X_"),   2,  6, PT_SHUA4);
    singlePattern13Test(str2pat("_XXO_O_O_O_O_"),  -1,  6, PT_SHUA4);
    singlePattern13Test(str2pat("OXXO_O_O_O_OO"),   2,  6, PT_SHUA4);
    singlePattern13Test(str2pat("XXXO_O_O_OOXO"),   1,  3, PT_CHON4);
    singlePattern13Test(str2pat("OOXXO__OO_OX_"),   2,  6, PT_SHUA4);
    singlePattern13Test(str2pat("_OXXO__OO_OO_"),  -3,  3, PT_CHON4);
    singlePattern13Test(str2pat("OOXXO__OO_OOO"),   1,  3, PT_CHON4);
    singlePattern13Test(str2pat("XOX_O__OO_OOX"),  -3,  3, PT_CHON4);
    singlePattern13Test(str2pat("XOX_O__OO_OOO"),   1,  3, PT_CHON4);
    singlePattern13Test(str2pat("_XO_OO__OXXO_"),   2,  6, PT_SHUA4);
    singlePattern13Test(str2pat("XOXOO__O_OOX_"),   2,  6, PT_SHUA4);
    singlePattern13Test(str2pat("X_OOO__O_OOXO"),  -2,  3, PT_CHON4);
    singlePattern13Test(str2pat("O_OOO__O_OOXO"),   1,  3, PT_CHON4);
    singlePattern13Test(str2pat("X_OO_O__OOX_X"),  -1,  6, PT_SHUA4);
    singlePattern13Test(str2pat("O_OO_O__OOX_X"),   2,  6, PT_SHUA4);
    singlePattern13Test(str2pat("XOXXO__OOOXOO"),   0,  0, PT_INVMV);
    singlePattern13Test(str2pat("_XOOO__XXXXOO"),   1,  3, PT_CHON4);
    singlePattern13Test(str2pat("XOOOO__XXXXO_"),  -4,  0, PT_INVMV);
    singlePattern13Test(str2pat("OOOOO__XXXXO_"),   0,  0, PT_INVMV);
    singlePattern13Test(str2pat("X_XOOO__XXX_X"),   1,  3, PT_CHON4);
    singlePattern13Test(str2pat("O_XO_O_OXXXXO"),   1,  3, PT_CHON4);
    singlePattern13Test(str2pat("_XXXO__OOXXOX"),   1,  3, PT_CHON4);
    singlePattern13Test(str2pat("X_OOO_______X"),  -1,  3, PT_CHON4);
    singlePattern13Test(str2pat("O_OOO________"),   2,  3, PT_CHON4);
    singlePattern13Test(str2pat("_OOOO________"),  -3,  0, PT_INVMV);
    singlePattern13Test(str2pat("OOOOO_______O"),   1,  0, PT_INVMV);
    singlePattern13Test(str2pat("X_OOO__O____X"),  -3,  1, PT_MIAN2);
    singlePattern13Test(str2pat("__OOO__O____O"),  -2,  1, PT_MIAN2);
    singlePattern13Test(str2pat("_X_OOO_X___X_"),   1,  3, PT_CHON4);
    singlePattern13Test(str2pat("___OOO_X___O_"),  -2,  3, PT_CHON4);
    singlePattern13Test(str2pat("O__OOO_X___OO"),   1,  3, PT_CHON4);
    putchar('\n');

    singlePattern13Test(str2pat("X_OO____OO__X"),  -1,  6, PT_LIAN3);
    singlePattern13Test(str2pat("__OO____OO__O"),   1,  6, PT_LIAN3);
    singlePattern13Test(str2pat("O_OO____OO__O"),   3,  6, PT_LIAN3);
    singlePattern13Test(str2pat("O_X_OO___XXOO"),   2,  4, PT_LIAN3);
    singlePattern13Test(str2pat("__X_OO___OXO_"),   1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("_X_OO___XXXXO"),   2,  4, PT_LIAN3);
    singlePattern13Test(str2pat("OXXX_O_O__XX_"),   2,  4, PT_LIAN3);
    singlePattern13Test(str2pat("__XX_O__O_X_O"),   2,  4, PT_LIAN3);
    singlePattern13Test(str2pat("OOXXX__O_O_XO"),   2,  4, PT_LIAN3);
    singlePattern13Test(str2pat("_OXXX__O_O_OX"),  -2,  2, PT_MIAN3);
    singlePattern13Test(str2pat("_OXXX__O_O_OO"),   1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("_XOO___OO____"),   0,  4, PT_LIAN3);
    singlePattern13Test(str2pat("_XOO___OO___O"),   2,  4, PT_LIAN3);
    singlePattern13Test(str2pat("_XOO___OO__O_"),  -2,  2, PT_MIAN3);
    singlePattern13Test(str2pat("_XOO___OO__OO"),   1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("_X_O_O___O_X_"),   3,  6, PT_LIAN3);
    singlePattern13Test(str2pat("_XXO_O___O_XO"),   2,  4, PT_SHUA3);
    singlePattern13Test(str2pat("XXOO____OOXXO"),   2,  4, PT_SHUA3);
    singlePattern13Test(str2pat("_XO_O___O__XX"),   3,  5, PT_SHUA3);
    singlePattern13Test(str2pat("XXO_O___OXXX_"),   2,  4, PT_SHUA3);
    singlePattern13Test(str2pat("OXX_O___O_OXO"),   2,  4, PT_SHUA3);
    singlePattern13Test(str2pat("_XX_O___O_O__"),   0,  4, PT_SHUA3);
    singlePattern13Test(str2pat("_XX_O___O_O_O"),   2,  4, PT_SHUA3);
    singlePattern13Test(str2pat("OXX_O___O_OOX"),  -2,  2, PT_MIAN3);
    singlePattern13Test(str2pat("OXX_O___O_OOO"),   1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("_XO_O___O_OXX"),   3,  6, PT_SHUA3);
    singlePattern13Test(str2pat("XXO__O___OXX_"),   2,  4, PT_MIAN3);
    singlePattern13Test(str2pat("_OO__O___OXOX"),  -2,  2, PT_MIAN3);
    singlePattern13Test(str2pat("OOO__O___OXOO"),   1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("XXXX_O_O_XXXX"),   1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("__XXX__OO_XO_"),   1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("XXOO___O__OXX"),   1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("X_OO___O__O_X"),  -3,  2, PT_MIAN3);
    singlePattern13Test(str2pat("X_OO___O__O_O"),  -1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("O_OO___O__O_X"),  -1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("O_OO___O__O_O"),   1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("_XOO___O__OO_"),  -3,  0, PT_INVMV);
    singlePattern13Test(str2pat("_XOO___O__OOO"),   0,  0, PT_INVMV);
    singlePattern13Test(str2pat("XXXXXX__OO_XX"),   1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("OOO_OX__OO_O_"),  -3,  0, PT_INVMV);
    singlePattern13Test(str2pat("OOO_OX__OO_OO"),   0,  0, PT_INVMV);
    singlePattern13Test(str2pat("_XOO_______X_"),   3,  2, PT_MIAN3);
    singlePattern13Test(str2pat("OXOO___X___OX"),   1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("XXOO_____OOXX"),   2,  4, PT_MIAN3);
    singlePattern13Test(str2pat("X_OO_____OOOX"),  -4,  2, PT_MIAN3);
    singlePattern13Test(str2pat("O_OO_____OOOX"),  -2,  2, PT_MIAN3);
    singlePattern13Test(str2pat("X_OO_____OOOO"),  -1,  2, PT_MIAN3);
    singlePattern13Test(str2pat("O_OO_____OOOO"),   1,  2, PT_MIAN3);
    putchar('\n');

    singlePattern13Test(str2pat("_XO____OXXXX_"),   0,  0, PT_INVMV);
    singlePattern13Test(str2pat("_X_O___XXXXXX"),   1,  1, PT_MIAN2);
    singlePattern13Test(str2pat("X__O___XXXXXO"),   0,  1, PT_MIAN2);
    singlePattern13Test(str2pat("O__O___XXXXXO"),   1,  1, PT_MIAN2);
    singlePattern13Test(str2pat("_O_O___XOX___"),  -2,  0, PT_INVMV);
    singlePattern13Test(str2pat("OO_O___XOX___"),   0,  0, PT_INVMV);
    singlePattern13Test(str2pat("_X_O____XXXX_"),   2,  2, PT_LIAN2);
    singlePattern13Test(str2pat("XO_O____XXXXX"),  -1,  1, PT_MIAN2);
    singlePattern13Test(str2pat("OO_O____XXXXX"),   1,  1, PT_MIAN2);
    singlePattern13Test(str2pat("XOX____O_XXO_"),   2,  2, PT_LIAN2);
    singlePattern13Test(str2pat("O_X_O____XX_O"),   2,  2, PT_LIAN2);
    putchar('\n');

    singlePattern13Test(str2pat("XX_X_____X_OX"),   1,  0, PT_INVMV);
    singlePattern13Test(str2pat("____X____X_X_"),   0,  0, PT_INVMV);
    singlePattern13Test(str2pat("OO__XO__OX_OO"),   0,  0, PT_INVMV);
    singlePattern13Test(str2pat("_O__X__O_X_XX"),   0,  0, PT_INVMV);
    //singlePattern13Test(str2pat("O__X_O__X__"),  0, PT_INVMV);
    //singlePattern13Test(str2pat("_O_O_O___O_"),  7, PT_INVMV);
    //singlePattern13Test(str2pat("_O_O_O_O_O_"),  9, PT_INVMV);
    //singlePattern13Test(str2pat("_____O_____"),  5, PT_INVMV);
    //singlePattern13Test(str2pat("_OOOOOOOOO_"),  0, PT_INVMV);
    //singlePattern13Test(str2pat("O__XOOOOOX_"),  5, PT_INVMV);
    putchar('\n');

    return true;
}

#if 0



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
#endif



bool runtests() {
    testPattern5();
    testPattern9();
    testPattern13();

    return true;
}
