/************************************************************************
 *
 * File: Lotto.C
 *
 * This is the main source file for Lotto, a lottery combination
 * generator for OS/2.
 *
 * Original program (VX-REXX): Goran Ivankovic, 1999.
 * 2026: rewritten in C for Open Watcom by the OS2World community
 *       (settings in Lotto.cfg, six languages, help, About dialog,
 *       frame controls).
 *
 ************************************************************************/
#define INCL_WINWINDOWMGR
#define INCL_WINMESSAGEMGR
#define INCL_WINDIALOGS
#define INCL_WINFRAMEMGR

#include    "lotto.h"
#include    "lottolang.h"
#include    <string.h>
#include    <stdlib.h>
#include    <stdio.h>

#pragma off(unreferenced)
static const char bldlevel[] =
    "@#Goran Ivankovic:1.10#@##1## 06 Oct 2026 20:00:00      "
    "ARCAOS:::0::::@@Lotto - lottery combination generator for OS/2\r\n\x1a";
#pragma on(unreferenced)

    /* Functions contained in LottoWin.C */

MRESULT EXPENTRY MainWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    /* Functions contained in this file */

static void Initialize(LOTTO *Lotto);
static BOOL SaveProfile(LOTTO *Lotto);

    /* Settings file: the first three fields are the same in every program */

typedef struct {
    ULONG   saveonexit, detaillevel, current_lang;
    ULONG   comb, total, numcomb;
    ULONG   fixed[NUMFIXED];
} LOTTOCFG;

#define CFGFILE "Lotto.cfg"

int main(int argc, char *argv[])
{
    LOTTO   Lotto;
    HMQ     hmq;
    QMSG    qmsg;
    ULONG   ulFlags=FCF_STANDARD;

    if(bldlevel[0] != '@')      /* keeps the BLDLEVEL string in the executable */
        return 1;

    CG_InitExeDir();

    if(!(Lotto.hab=WinInitialize(0))) return 1;
    if(!(hmq=WinCreateMsgQueue(Lotto.hab, 0))) return 1;

    Initialize(&Lotto);

    Lotto.hwndFrame=WinCreateStdWindow(HWND_DESKTOP, FS_SIZEBORDER, &ulFlags,
        "LottoClient", "Lotto", WS_VISIBLE,
        (HMODULE)0, MainFrame, &Lotto.hwndClient);

    CG_FrameInit(&Lotto.Frame, Lotto.hwndFrame);

    if(WinSendMsg(Lotto.hwndClient, MESS_CREATE, MPFROMP(&Lotto), NULL))
    {
        while(WinGetMsg(Lotto.hab, &qmsg, 0, 0, 0))
            WinDispatchMsg(Lotto.hab, &qmsg);
    }

    if(Lotto.SaveOnExit)
        SaveProfile(&Lotto);

    CG_FrameDone(&Lotto.Frame);

    if(Lotto.hwndHelpInstance)
        WinDestroyHelpInstance(Lotto.hwndHelpInstance);
    WinDestroyWindow(Lotto.hwndFrame);

    WinDestroyMsgQueue(hmq);
    WinTerminate(Lotto.hab);
    return 0;
}

/************************************************************************
 *
 * void Initialize(LOTTO *Lotto)
 *
 * Initializes the program: defaults first, then the settings file.
 *
 ************************************************************************/
static void Initialize(LOTTO *Lotto)
{
    HAB         habTemp=Lotto->hab;
    LOTTOCFG    cfg;
    int         Temp;

    memset(Lotto, 0, sizeof(*Lotto));
    Lotto->hab=habTemp;

    Lotto->SaveOnExit=TRUE;
    Lotto->Lang=LANG_EN;
    Lotto->Comb=DEF_COMB;
    Lotto->Total=DEF_TOTAL;
    Lotto->NumComb=DEF_NUMCOMB;

    memset(&cfg, 0, sizeof(cfg));
    cfg.comb=DEF_COMB;
    cfg.total=DEF_TOTAL;
    cfg.numcomb=DEF_NUMCOMB;
    if(CG_LoadBlob(CFGFILE, &cfg, sizeof(cfg)))
    {
        Lotto->SaveOnExit=cfg.saveonexit?TRUE:FALSE;
        if(cfg.current_lang<LANG_COUNT) Lotto->Lang=(int)cfg.current_lang;
        if(cfg.total>=1 && cfg.total<=MAX_TOTAL) Lotto->Total=(int)cfg.total;
        if(cfg.comb>=1 && cfg.comb<=(ULONG)Lotto->Total) Lotto->Comb=(int)cfg.comb;
        if(cfg.numcomb>=1 && cfg.numcomb<=MAX_COMBS) Lotto->NumComb=(int)cfg.numcomb;
        for(Temp=0;Temp<NUMFIXED;Temp++)
            if(cfg.fixed[Temp]<=(ULONG)Lotto->Total) Lotto->Fixed[Temp]=(int)cfg.fixed[Temp];
    }
    current_lang=Lotto->Lang;

    WinRegisterClass(Lotto->hab, "LottoClient", (PFNWP)MainWindowProc,
        CS_SIZEREDRAW | CS_CLIPCHILDREN, sizeof(PVOID));
}

/************************************************************************
 *
 * BOOL SaveProfile(LOTTO *Lotto)
 *
 * Saves the settings and the last parameters.
 *
 ************************************************************************/
static BOOL SaveProfile(LOTTO *Lotto)
{
    LOTTOCFG    cfg;
    int         Temp;

    memset(&cfg, 0, sizeof(cfg));
    cfg.saveonexit=Lotto->SaveOnExit?1:0;
    cfg.detaillevel=1;
    cfg.current_lang=(ULONG)Lotto->Lang;
    cfg.comb=(ULONG)Lotto->Comb;
    cfg.total=(ULONG)Lotto->Total;
    cfg.numcomb=(ULONG)Lotto->NumComb;
    for(Temp=0;Temp<NUMFIXED;Temp++)
        cfg.fixed[Temp]=(ULONG)Lotto->Fixed[Temp];

    return CG_SaveBlob(CFGFILE, &cfg, sizeof(cfg));
}
