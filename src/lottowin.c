/************************************************************************
 *
 * File: LottoWin.C
 *
 * Main window and logic of Lotto.
 *
 * The client window holds the entry fields, the list of combinations and
 * the buttons as child windows.
 *
 ************************************************************************/
#define INCL_WIN
#define INCL_GPI
#define INCL_DOS

#include    "lotto.h"
#include    "lottolang.h"
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <time.h>
#include    <direct.h>

    /* Functions contained in this file */

MRESULT EXPENTRY MainWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY AboutDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

static void    CreateControls(LOTTO *L);
static void    Layout(LOTTO *L, LONG cx, LONG cy);
static void    ApplyLanguage(LOTTO *L, int lang);
static void    SetTexts(LOTTO *L);
static void    SyncMenus(LOTTO *L);
static void    ShowFields(LOTTO *L);
static void    ShowStatus(LOTTO *L);
static void    ReadFields(LOTTO *L);
static void    FieldLostFocus(LOTTO *L, int id);
static void    Generate(LOTTO *L);
static void    ClearAll(LOTTO *L, BOOL fDefaults);
static void    SaveResult(LOTTO *L);
static void    CenterInOwner(HWND hwnd);
static BOOL    ErrorBox(LOTTO *L, const char *text);

static const CG_MENUTEXT mtAll[] = {
    { MainGame,           S_MENU_GAME },     { MainGameGenerate,  S_MENU_GENERATE },
    { MainGameClear,      S_MENU_CLEAR },    { MainGameSave,      S_MENU_SAVE },
    { MainGameExit,       S_MENU_EXIT },     { MainOptions,       S_MENU_OPTIONS },
    { MainOptionsLang,    S_MENU_LANGUAGE }, { MainOptionsFrame,  S_MENU_FRAME },
    { MainOptionsSave,    S_MENU_SAVEONEXIT },{ MainHelp,         S_MENU_HELP },
    { MainHelpGeneral,    S_MENU_GENHELP },  { MainHelpIndex,     S_MENU_HELPINDEX },
    { MainHelpOnHelp,     S_MENU_HELPONHELP },{ MainHelpAbout,    S_MENU_ABOUT }
};

static const USHORT usSubs[]   = { MainGame, MainOptions, MainHelp };
static const USHORT usNested[] = { MainOptionsLang };

static const char *szHelpFiles[LANG_COUNT] = {
    "Lotto_en.hlp", "Lotto_es.hlp", "Lotto_nl.hlp",
    "Lotto_de.hlp", "Lotto_fr.hlp", "Lotto_it.hlp"
};

static const USHORT FixedIds[NUMFIXED]={CtlFixed1, CtlFixed2, CtlFixed3, CtlFixed4, CtlFixed5};

/************************************************************************
 *
 * Small helpers
 *
 ************************************************************************/
static void CenterInOwner(HWND hwnd)
{
    SWP     swpChild, swpOwner;
    HWND    hwndOwner=WinQueryWindow(hwnd, QW_OWNER);

    if(!hwndOwner) hwndOwner=HWND_DESKTOP;
    if(!WinQueryWindowPos(hwndOwner, &swpOwner)) return;
    if(!WinQueryWindowPos(hwnd, &swpChild)) return;

    WinSetWindowPos(hwnd, HWND_TOP, swpOwner.x+(swpOwner.cx-swpChild.cx)/2,
        swpOwner.y+(swpOwner.cy-swpChild.cy)/2, 0, 0, SWP_MOVE | SWP_SHOW);
}

static BOOL ErrorBox(LOTTO *L, const char *text)
{
    DosBeep(400, 50);
    WinMessageBox(HWND_DESKTOP, L->hwndFrame, (PSZ)text, (PSZ)"Lotto", 0,
        MB_OK | MB_ERROR | MB_MOVEABLE);
    return FALSE;
}

/* The text of an entry field as a number; bad text gives -1 */
static int FieldValue(LOTTO *L, USHORT id)
{
    char    Text[16];
    char    *End;
    long    Value;

    WinQueryWindowText(WinWindowFromID(L->hwndClient, id), sizeof(Text), (PSZ)Text);
    if(!Text[0]) return -1;
    Value=strtol(Text, &End, 10);
    while(*End==' ') End++;
    if(*End || Value<0 || Value>999) return -1;
    return (int)Value;
}

static void SetField(LOTTO *L, USHORT id, int Value)
{
    char Text[16];

    sprintf(Text, "%d", Value);
    WinSetWindowText(WinWindowFromID(L->hwndClient, id), (PSZ)Text);
}

/* Puts the numbers of the program into the entry fields */
static void ShowFields(LOTTO *L)
{
    int Temp;

    SetField(L, CtlComb, L->Comb);
    SetField(L, CtlTotal, L->Total);
    SetField(L, CtlNumComb, L->NumComb);
    for(Temp=0;Temp<NUMFIXED;Temp++)
        SetField(L, FixedIds[Temp], L->Fixed[Temp]);
}

/* Takes the numbers from the entry fields (bad entries keep their value) */
static void ReadFields(LOTTO *L)
{
    int Value, Temp;

    if((Value=FieldValue(L, CtlTotal))>=1 && Value<=MAX_TOTAL) L->Total=Value;
    if((Value=FieldValue(L, CtlComb))>=1) L->Comb=Value;
    if((Value=FieldValue(L, CtlNumComb))>=1 && Value<=MAX_COMBS) L->NumComb=Value;
    for(Temp=0;Temp<NUMFIXED;Temp++)
        if((Value=FieldValue(L, FixedIds[Temp]))>=0) L->Fixed[Temp]=Value;
}

static void ShowStatus(LOTTO *L)
{
    if(L->Count>0)
        sprintf(L->StatusText, tr(S_ST_COUNT), L->Count);
    else
        L->StatusText[0]='\0';
    WinSetWindowText(WinWindowFromID(L->hwndClient, CtlStatus), (PSZ)L->StatusText);
}

/************************************************************************
 *
 * Checking the entry fields when they lose the focus
 *
 ************************************************************************/
static void FieldLostFocus(LOTTO *L, int id)
{
    int Value=FieldValue(L, (USHORT)id), Temp, Other;

    switch(id) {
    case CtlComb:
        if(Value<1) { DosBeep(400, 50); SetField(L, id, DEF_COMB); }
        break;
    case CtlTotal:
        if(Value<1 || Value>MAX_TOTAL) { DosBeep(400, 50); SetField(L, id, DEF_TOTAL); }
        break;
    case CtlNumComb:
        if(Value<1 || Value>MAX_COMBS) { DosBeep(400, 50); SetField(L, id, DEF_NUMCOMB); }
        break;
    default:
        /* A fixed number: 0 means none, and no number may appear twice */
        if(Value<0) { DosBeep(400, 50); SetField(L, id, 0); break; }
        if(Value>0)
            for(Temp=0;Temp<NUMFIXED;Temp++)
            {
                if(FixedIds[Temp]==id) continue;
                Other=FieldValue(L, FixedIds[Temp]);
                if(Other==Value) { SetField(L, id, 0); break; }
            }
        break;
    }
    ReadFields(L);
}

/************************************************************************
 *
 * Generating the combinations
 *
 ************************************************************************/
static void Generate(LOTTO *L)
{
    HWND    hwndList=WinWindowFromID(L->hwndClient, CtlList);
    char    Text[64], Line[MAX_TOTAL*3+4];
    int     Pick[MAX_TOTAL+1], Used[MAX_TOTAL+1];
    int     Temp, Temp2, Number, NumFixed, Comb, Combs, Index;

    ReadFields(L);

    /* There cannot be more numbers in a combination than numbers to choose from */
    if(L->Comb>L->Total)
    {
        sprintf(Text, tr(S_M_MAXNUM), L->Total);
        ErrorBox(L, Text);
        return;
    }

    for(Temp=0;Temp<NUMFIXED;Temp++)
        if(L->Fixed[Temp]>L->Total)
        {
            sprintf(Text, tr(S_M_FIXEDRANGE), tr(S_ORD1+Temp), L->Total);
            ErrorBox(L, Text);
            return;
        }

    WinSendMsg(hwndList, LM_DELETEALL, 0, 0);
    L->Count=0;

    /* The fixed numbers; if there are more than the combination holds, the first ones count */
    NumFixed=0;
    memset(Used, 0, sizeof(Used));
    for(Temp=0;Temp<NUMFIXED && NumFixed<L->Comb;Temp++)
        if(L->Fixed[Temp]>0 && !Used[L->Fixed[Temp]])
        {
            Used[L->Fixed[Temp]]=1;
            NumFixed++;
        }

    Comb=L->Comb;
    Combs=L->NumComb;

    for(Index=0;Index<Combs;Index++)
    {
        int Chosen[MAX_TOTAL+1];

        memcpy(Chosen, Used, sizeof(Chosen));

        /* The rest of the numbers are drawn at random, without repeating */
        for(Temp=NumFixed;Temp<Comb;)
        {
            Number=rand()%L->Total+1;
            if(!Chosen[Number])
            {
                Chosen[Number]=1;
                Temp++;
            }
        }

        /* In ascending order */
        for(Temp=1, Temp2=0;Temp<=L->Total;Temp++)
            if(Chosen[Temp]) Pick[Temp2++]=Temp;

        Line[0]='\0';
        for(Temp=0;Temp<Comb;Temp++)
        {
            char Item[8];

            sprintf(Item, "%3d", Pick[Temp]);
            strcat(Line, Item);
        }
        WinSendMsg(hwndList, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP(Line));
        L->Count++;
    }

    DosBeep(500, 100);
    if(L->Count>0) WinSendMsg(hwndList, LM_SELECTITEM, MPFROMSHORT(0), MPFROMSHORT(TRUE));
    ShowStatus(L);
    WinSetFocus(HWND_DESKTOP, WinWindowFromID(L->hwndClient, CtlComb));
}

static void ClearAll(LOTTO *L, BOOL fDefaults)
{
    WinSendMsg(WinWindowFromID(L->hwndClient, CtlList), LM_DELETEALL, 0, 0);
    L->Count=0;

    if(fDefaults)
    {
        int Temp;

        L->Comb=DEF_COMB;
        L->Total=DEF_TOTAL;
        L->NumComb=DEF_NUMCOMB;
        for(Temp=0;Temp<NUMFIXED;Temp++) L->Fixed[Temp]=0;
        ShowFields(L);
    }
    ShowStatus(L);
}

/************************************************************************
 *
 * Saving the result into LOTTO.TXT in the working directory
 *
 ************************************************************************/
static void SaveResult(LOTTO *L)
{
    HWND    hwndList=WinWindowFromID(L->hwndClient, CtlList);
    FILE    *fp;
    time_t  Now=time(NULL);
    struct tm *tm=localtime(&Now);
    char    Line[MAX_TOTAL*3+16], Path[CCHMAXPATH+16], Msg[CCHMAXPATH+300], Text[CCHMAXPATH+300];
    int     Temp, Count=(int)(SHORT)SHORT1FROMMR(WinSendMsg(hwndList, LM_QUERYITEMCOUNT, 0, 0));
    BOOL    fFixed=FALSE;

    if(Count<=0)
    {
        ErrorBox(L, tr(S_M_EMPTY));
        return;
    }

    if(!(fp=fopen(RESULTFILE, "w")))
    {
        sprintf(Msg, tr(S_M_SAVEFAIL), RESULTFILE);
        ErrorBox(L, Msg);
        return;
    }

    fprintf(fp, "Lotto, (c)Goran Ivankovic, %04d-%02d-%02d; %02d:%02d:%02d\r\n",
        tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

    fprintf(fp, tr(S_F_COMBS), L->Comb, L->Total, Count);
    for(Temp=0;Temp<NUMFIXED;Temp++)
        if(L->Fixed[Temp]>0)
        {
            if(!fFixed) fprintf(fp, "     %s", tr(S_F_FIXED));
            fprintf(fp, " %2d", L->Fixed[Temp]);
            fFixed=TRUE;
        }
    fprintf(fp, "\r\n\r\n");

    for(Temp=0;Temp<Count;Temp++)
    {
        WinSendMsg(hwndList, LM_QUERYITEMTEXT, MPFROM2SHORT(Temp, sizeof(Line)), MPFROMP(Line));
        fprintf(fp, "%3d.%s\r\n", Temp+1, Line);
    }
    fclose(fp);

    DosBeep(500, 100);

    getcwd(Path, CCHMAXPATH);
    if(Path[0] && Path[strlen(Path)-1]!='\\') strcat(Path, "\\");
    strcat(Path, RESULTFILE);

    sprintf(Text, tr(S_M_SAVED), Path);
    if(WinMessageBox(HWND_DESKTOP, L->hwndFrame, (PSZ)Text, (PSZ)tr(S_M_SAVED_TITLE), 0,
        MB_OKCANCEL | MB_INFORMATION | MB_MOVEABLE)==MBID_OK)
    {
        sprintf(Msg, "start /f e.exe \"%s\"", Path);
        system(Msg);
    }
}

/************************************************************************
 *
 * Controls and layout
 *
 ************************************************************************/
typedef struct {
    USHORT  id;
    ULONG   style;
    int     str;
} CTLBTN;

static const CTLBTN Buttons[] = {
    { MainGameGenerate, BS_PUSHBUTTON | BS_DEFAULT, S_B_DOIT },
    { MainGameClear,    BS_PUSHBUTTON, S_B_CLEAR },
    { MainGameSave,     BS_PUSHBUTTON, S_B_FILE },
    { MainHelpAbout,    BS_PUSHBUTTON, S_B_ABOUT },
    { MainGameExit,     BS_PUSHBUTTON, S_B_EXIT }
};

typedef struct {
    USHORT  id;
    ULONG   align;
    int     str;
} CTLLABEL;

static const CTLLABEL Labels[] = {
    { CtlLblGame,   DT_RIGHT,  S_L_GAME },
    { CtlLblOf,     DT_CENTER, S_L_OF },
    { CtlLblCombs,  DT_RIGHT,  S_L_COMBS },
    { CtlLblFixed,  DT_RIGHT,  S_L_FIXED }
};

static const struct { USHORT id; int limit; } Entries[] = {
    { CtlComb, 2 }, { CtlTotal, 2 }, { CtlNumComb, 3 },
    { CtlFixed1, 2 }, { CtlFixed2, 2 }, { CtlFixed3, 2 }, { CtlFixed4, 2 }, { CtlFixed5, 2 }
};

static void CreateControls(LOTTO *L)
{
    HWND    hwnd=L->hwndClient, hwndCtl;
    LONG    lBack=SYSCLR_DIALOGBACKGROUND;
    int     i;

    for(i=0;i<(int)(sizeof(Labels)/sizeof(Labels[0]));i++)
    {
        hwndCtl=WinCreateWindow(hwnd, WC_STATIC, "", SS_TEXT | DT_VCENTER | Labels[i].align | WS_VISIBLE,
            0, 0, 10, 10, hwnd, HWND_TOP, Labels[i].id, NULL, NULL);
        WinSetPresParam(hwndCtl, PP_BACKGROUNDCOLORINDEX, sizeof(lBack), &lBack);
    }

    for(i=0;i<(int)(sizeof(Entries)/sizeof(Entries[0]));i++)
    {
        hwndCtl=WinCreateWindow(hwnd, WC_ENTRYFIELD, "", ES_MARGIN | ES_CENTER | WS_VISIBLE | WS_TABSTOP,
            0, 0, 10, 10, hwnd, HWND_TOP, Entries[i].id, NULL, NULL);
        WinSendMsg(hwndCtl, EM_SETTEXTLIMIT, MPFROMSHORT(Entries[i].limit), 0);
    }

    hwndCtl=WinCreateWindow(hwnd, WC_LISTBOX, "", LS_NOADJUSTPOS | LS_HORZSCROLL | WS_VISIBLE | WS_TABSTOP,
        0, 0, 10, 10, hwnd, HWND_TOP, CtlList, NULL, NULL);

    /* The list keeps the numbers in columns, so it needs a fixed pitch font,
       of the same size as the font the user has chosen for the system */
    {
        char    Font[64], ListFont[80];
        ULONG   ulSize=9;

        Font[0]='\0';
        WinQueryPresParam(hwnd, PP_FONTNAMESIZE, 0, NULL, sizeof(Font), Font, 0);
        if(Font[0]>='0' && Font[0]<='9') ulSize=(ULONG)atoi(Font);
        if(ulSize<6 || ulSize>40) ulSize=9;
        sprintf(ListFont, "%lu.System Monospaced", ulSize);
        WinSetPresParam(hwndCtl, PP_FONTNAMESIZE, (ULONG)strlen(ListFont)+1, ListFont);
    }

    hwndCtl=WinCreateWindow(hwnd, WC_STATIC, "", SS_TEXT | DT_VCENTER | DT_LEFT | WS_VISIBLE,
        0, 0, 10, 10, hwnd, HWND_TOP, CtlStatus, NULL, NULL);
    WinSetPresParam(hwndCtl, PP_BACKGROUNDCOLORINDEX, sizeof(lBack), &lBack);

    for(i=0;i<(int)(sizeof(Buttons)/sizeof(Buttons[0]));i++)
        WinCreateWindow(hwnd, WC_BUTTON, "", Buttons[i].style | WS_VISIBLE | WS_TABSTOP,
            0, 0, 10, 10, hwnd, HWND_TOP, Buttons[i].id, NULL, NULL);
}

/* The width in pixels of the text of a label, in its own font */
static LONG TextWidth(LOTTO *L, USHORT id)
{
    HWND    hwndCtl=WinWindowFromID(L->hwndClient, id);
    char    Text[80];
    POINTL  aptl[TXTBOX_COUNT];
    HPS     hps;
    LONG    Width=0;

    WinQueryWindowText(hwndCtl, sizeof(Text), (PSZ)Text);
    if(!Text[0]) return 0;

    hps=WinGetPS(hwndCtl);
    if(hps)
    {
        if(GpiQueryTextBox(hps, (LONG)strlen(Text), (PCH)Text, TXTBOX_COUNT, aptl))
            Width=aptl[TXTBOX_TOPRIGHT].x-aptl[TXTBOX_BOTTOMLEFT].x;
        WinReleasePS(hps);
    }
    return Width;
}

#define PLACE(id,x,y,w,h) \
    WinSetWindowPos(WinWindowFromID(L->hwndClient, (id)), 0, (x), (y), (w), (h), SWP_MOVE | SWP_SIZE)

static void Layout(LOTTO *L, LONG cx, LONG cy)
{
    LONG    m=12, rh=28, bh=36, gap=8, x, w;
    LONG    lblW, combW, entW=52, ofW, i;
    LONG    yRow1, yRow2, yStatus, yList, hList;

    if(cx<200 || cy<200) return;

    /* The labels are as wide as their texts, whatever the language and the font */
    lblW=TextWidth(L, CtlLblGame);
    if(TextWidth(L, CtlLblFixed)>lblW) lblW=TextWidth(L, CtlLblFixed);
    lblW+=12;
    if(lblW<60) lblW=60;
    ofW=TextWidth(L, CtlLblOf)+12;
    if(ofW<28) ofW=28;
    combW=TextWidth(L, CtlLblCombs)+12;

    yRow1=cy-m-rh;
    yRow2=yRow1-rh-m;

    /* Row 1: Game: [7] of [39]   Combinations: [8] */
    x=m;
    PLACE(CtlLblGame, x, yRow1, lblW, rh);          x+=lblW+gap;
    PLACE(CtlComb, x, yRow1, entW, rh);             x+=entW+gap;
    PLACE(CtlLblOf, x, yRow1, ofW, rh);             x+=ofW+gap;
    PLACE(CtlTotal, x, yRow1, entW, rh);            x+=entW+gap*3;
    PLACE(CtlLblCombs, x, yRow1, combW, rh);        x+=combW+gap;
    PLACE(CtlNumComb, x, yRow1, entW+8, rh);

    /* Row 2: Fixed: [0] [0] [0] [0] [0] */
    x=m;
    PLACE(CtlLblFixed, x, yRow2, lblW, rh);         x+=lblW+gap;
    for(i=0;i<NUMFIXED;i++)
    {
        PLACE(FixedIds[i], x, yRow2, entW, rh);
        x+=entW+gap;
    }

    /* Bottom: the buttons, above them the status line */
    w=(cx-2*m-4*gap)/5;
    for(i=0;i<5;i++)
        PLACE(Buttons[i].id, m+i*(w+gap), m, w, bh);

    yStatus=m+bh+gap;
    PLACE(CtlStatus, m, yStatus, cx-2*m, rh-4);

    yList=yStatus+rh-4+gap;
    hList=yRow2-m-yList;
    if(hList<40) hList=40;
    PLACE(CtlList, m, yList, cx-2*m, hList);
}

/************************************************************************
 *
 * Language, menus and help
 *
 ************************************************************************/
static void SyncMenus(LOTTO *L)
{
    HWND hMenu=WinWindowFromID(L->hwndFrame, FID_MENU);
    int  i;

    for(i=0;i<LANG_COUNT;i++)
        WinCheckMenuItem(hMenu, (USHORT)(MainLang0+i), i==L->Lang);
    WinCheckMenuItem(hMenu, MainOptionsSave, L->SaveOnExit);
    WinCheckMenuItem(hMenu, MainOptionsFrame, L->Frame.hidden);
}

static void SetTexts(LOTTO *L)
{
    int i;

    for(i=0;i<(int)(sizeof(Buttons)/sizeof(Buttons[0]));i++)
        WinSetWindowText(WinWindowFromID(L->hwndClient, Buttons[i].id), (PSZ)tr(Buttons[i].str));

    for(i=0;i<(int)(sizeof(Labels)/sizeof(Labels[0]));i++)
        WinSetWindowText(WinWindowFromID(L->hwndClient, Labels[i].id), (PSZ)tr(Labels[i].str));

    ShowStatus(L);
}

static void ApplyLanguage(LOTTO *L, int lang)
{
    HWND hMenu=WinWindowFromID(L->hwndFrame, FID_MENU);

    if(lang<0 || lang>=LANG_COUNT) lang=LANG_EN;
    L->Lang=lang;
    current_lang=lang;

    CG_RelabelMenu(hMenu, mtAll, sizeof(mtAll)/sizeof(mtAll[0]), lang_strings[lang],
        usSubs, sizeof(usSubs)/sizeof(usSubs[0]), usNested, sizeof(usNested)/sizeof(usNested[0]));
    SyncMenus(L);
    SetTexts(L);
    {
        RECTL rclClient;

        WinQueryWindowRect(L->hwndClient, &rclClient);
        Layout(L, rclClient.xRight, rclClient.yTop);
    }

    L->hwndHelpInstance=CG_SetHelp(L->hab, L->hwndFrame, L->hwndHelpInstance,
        szHelpFiles[lang], HID_MAIN, tr(S_HELP_TITLE), tr(S_HELP_MISSING));

    WinInvalidateRect(L->hwndClient, NULL, TRUE);
}

/************************************************************************
 *
 * MainWindowProc()
 *
 * Procedure for the client window.
 *
 ************************************************************************/
MRESULT EXPENTRY MainWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    LOTTO   *L;

    if(msg==MESS_CREATE)
    {
        LONG    cxScreen, cyScreen, cxFrame, cyFrame;
        RECTL   rcl;

        L=(LOTTO *)PVOIDFROMMP(mp1);
        WinSetWindowPtr(hwnd, 0, L);

        L->hwndClient=hwnd;
        L->hwndFrame=WinQueryWindow(hwnd, QW_PARENT);

        srand((unsigned)(WinGetCurrentTime(L->hab)^(unsigned)time(NULL)));

        CreateControls(L);
        ShowFields(L);
        ApplyLanguage(L, L->Lang);

        /* The frame that holds a client of 640x520, centered on the screen */
        cxScreen=WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
        cyScreen=WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);
        rcl.xLeft=0; rcl.yBottom=0; rcl.xRight=640; rcl.yTop=520;
        WinCalcFrameRect(L->hwndFrame, &rcl, FALSE);
        cxFrame=rcl.xRight-rcl.xLeft;
        cyFrame=rcl.yTop-rcl.yBottom;
        if(cxFrame>cxScreen) cxFrame=cxScreen;
        if(cyFrame>cyScreen) cyFrame=cyScreen;

        WinSetWindowPos(L->hwndFrame, HWND_TOP, (cxScreen-cxFrame)/2, (cyScreen-cyFrame)/2,
            cxFrame, cyFrame, SWP_SIZE | SWP_MOVE | SWP_ACTIVATE | SWP_SHOW);

        WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd, CtlComb));
        return (MRESULT)TRUE;
    }

    L=(LOTTO *)WinQueryWindowPtr(hwnd, 0);

    switch(msg) {
    case WM_PAINT:
    {
        RECTL   rcl;
        HPS     hps;

        if(!L) return WinDefWindowProc(hwnd, msg, mp1, mp2);
        hps=WinBeginPaint(hwnd, NULLHANDLE, &rcl);
        WinFillRect(hps, &rcl, SYSCLR_DIALOGBACKGROUND);
        WinEndPaint(hps);
    }
        break;
    case WM_ERASEBACKGROUND:
        return (MRESULT)FALSE;
    case WM_SIZE:
        if(L) Layout(L, SHORT1FROMMP(mp2), SHORT2FROMMP(mp2));
        break;
    case WM_CONTROL:
        if(L && SHORT2FROMMP(mp1)==EN_KILLFOCUS)
            FieldLostFocus(L, SHORT1FROMMP(mp1));
        break;
    case WM_COMMAND:
    {
        USHORT  id=SHORT1FROMMP(mp1);

        switch(id) {
        case MainGameGenerate:
            Generate(L);
            break;
        case MainGameClear:
            ClearAll(L, TRUE);
            break;
        case MainGameSave:
            SaveResult(L);
            break;
        case MainGameExit:
            WinSendMsg(hwnd, WM_CLOSE, 0, 0);
            break;
        case MainLang0: case MainLang1: case MainLang2:
        case MainLang3: case MainLang4: case MainLang5:
            ApplyLanguage(L, id-MainLang0);
            break;
        case MainOptionsFrame:
            CG_FrameToggle(&L->Frame, hwnd);
            break;
        case MainOptionsSave:
            L->SaveOnExit=!L->SaveOnExit;
            SyncMenus(L);
            break;
        case MainHelpAbout:
            WinDlgBox(HWND_DESKTOP, L->hwndFrame, (PFNWP)AboutDlgProc, (HMODULE)0,
                AboutDlg, NULL);
            break;
        case MainHelpGeneral:
            if(L->hwndHelpInstance)
                WinSendMsg(L->hwndHelpInstance, HM_DISPLAY_HELP, MPFROMSHORT(HID_GENERAL),
                    MPFROMSHORT(HM_RESOURCEID));
            break;
        case MainHelpIndex:
            if(L->hwndHelpInstance)
                WinSendMsg(L->hwndHelpInstance, HM_HELP_INDEX, 0, 0);
            break;
        case MainHelpOnHelp:
            if(L->hwndHelpInstance)
                WinSendMsg(L->hwndHelpInstance, HM_DISPLAY_HELP, 0, 0);
            break;
        default:
            return WinDefWindowProc(hwnd, msg, mp1, mp2);
        }
    }
        break;
    case WM_CLOSE:
        ReadFields(L);
        WinPostMsg(hwnd, WM_QUIT, 0, 0);
        break;
    default:
        return WinDefWindowProc(hwnd, msg, mp1, mp2);
    }
    return (MRESULT)0;
}

/************************************************************************
 *
 * AboutDlgProc()
 *
 * Standard About dialog: a single Close button.
 *
 ************************************************************************/
MRESULT EXPENTRY AboutDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    if(msg==WM_INITDLG)
    {
        CenterInOwner(hwnd);
        return (MRESULT)FALSE;
    }
    if(msg==WM_COMMAND)
    {
        switch(SHORT1FROMMP(mp1)) {
        case DID_OK:
        case DID_CANCEL:
            WinDismissDlg(hwnd, TRUE);
            return (MRESULT)0;
        }
    }
    return WinDefDlgProc(hwnd, msg, mp1, mp2);
}
