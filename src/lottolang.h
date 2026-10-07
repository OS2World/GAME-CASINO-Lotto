/* Lotto - run time language support */

#ifndef LOTTOLANG_H
#define LOTTOLANG_H

#include "common/common.h"

enum {
    S_MENU_GAME = 0, S_MENU_GENERATE, S_MENU_CLEAR, S_MENU_SAVE, S_MENU_EXIT,
    S_MENU_OPTIONS, S_MENU_LANGUAGE, S_MENU_FRAME, S_MENU_SAVEONEXIT,
    S_MENU_HELP, S_MENU_GENHELP, S_MENU_HELPINDEX, S_MENU_HELPONHELP, S_MENU_ABOUT,
    /* buttons */
    S_B_DOIT, S_B_CLEAR, S_B_FILE, S_B_ABOUT, S_B_EXIT,
    /* labels */
    S_L_GAME, S_L_OF, S_L_COMBS, S_L_FIXED, S_ST_COUNT,
    S_ORD1, S_ORD2, S_ORD3, S_ORD4, S_ORD5,
    /* messages */
    S_M_MAXNUM, S_M_FIXEDRANGE, S_M_EMPTY, S_M_SAVED_TITLE, S_M_SAVED, S_M_SAVEFAIL,
    S_F_COMBS, S_F_FIXED, S_HELP_TITLE, S_HELP_MISSING,
    S_COUNT
};

extern int current_lang;
extern const char *lang_strings[LANG_COUNT][S_COUNT];
#define tr(id) ((char *)lang_strings[current_lang][(id)])

#endif /* LOTTOLANG_H */
