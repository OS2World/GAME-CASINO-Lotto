/************************************************************************
 *
 * File: Lotto.H
 *
 * Main include file for Lotto, a lottery combination generator for OS/2.
 *
 ************************************************************************/
#define INCL_WINHELP
#include    <os2.h>
#include    "common/common.h"
#include    "lottorc.h"

#ifndef LOTTO_H_INCLUDED
#define LOTTO_H_INCLUDED

#define NUMFIXED        5
#define MAX_TOTAL       99      /* numbers 1..99 */
#define MAX_COMBS       999     /* combinations in the list */
#define DEF_COMB        7
#define DEF_TOTAL       39
#define DEF_NUMCOMB     8
#define RESULTFILE      "LOTTO.TXT"

typedef struct {
    HAB     hab;
    HWND    hwndFrame, hwndClient, hwndHelpInstance;
    CG_FRAMECTL Frame;
    int     Lang;
    BOOL    SaveOnExit;
    int     Comb, Total, NumComb;           /* numbers per combination, numbers to choose from, combinations */
    int     Fixed[NUMFIXED];                /* fixed numbers, 0 for none */
    int     Count;                          /* combinations in the list */
    char    StatusText[64];
} LOTTO;

#define MESS_CREATE     (WM_USER+1)

#endif
