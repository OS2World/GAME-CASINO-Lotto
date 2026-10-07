# Makefile for Lotto (Open Watcom C on OS/2 / ArcaOS)
# wmake 2.0.1 on ArcaOS - explicit per-file rules, prerequisites on ONE line.

BINDIR  = bin
SRCDIR  = src

!ifndef WATCOM
WATCOM  = C:\WATCOM
!endif

!ifndef OS2TK
OS2TK   = C:\OS2TK45
!endif

CC      = wcc386
LINK    = wlink
RC      = wrc
WIPFC   = wipfc

CFLAGS  = -bt=os2 -mf -5 -fpi -Oaxt -W3 -ze -d0
CFLAGS  = $(CFLAGS) -i=$(OS2TK)\h -i=$(SRCDIR) -i=$(SRCDIR)\common

RCFLAGS = -r -bt=os2 -i=$(OS2TK)\h -i=$(SRCDIR)

LFLAGS  = system os2v2_pm option stack=65536

HLPS    = $(BINDIR)\help\Lotto_en.hlp $(BINDIR)\help\Lotto_es.hlp $(BINDIR)\help\Lotto_nl.hlp $(BINDIR)\help\Lotto_de.hlp $(BINDIR)\help\Lotto_fr.hlp $(BINDIR)\help\Lotto_it.hlp

HDR     = $(SRCDIR)\lotto.h $(SRCDIR)\lottorc.h $(SRCDIR)\lottolang.h $(SRCDIR)\common\common.h
OBJS    = $(BINDIR)\lotto.obj $(BINDIR)\lottowin.obj $(BINDIR)\lottolang.obj $(BINDIR)\common.obj

all : $(BINDIR)\Lotto.exe $(HLPS) .SYMBOLIC

$(BINDIR) :
	@if not exist $(BINDIR) mkdir $(BINDIR)

$(BINDIR)\help : $(BINDIR)
	@if not exist $(BINDIR)\help mkdir $(BINDIR)\help

$(BINDIR)\Lotto.exe : $(OBJS) $(BINDIR)\lotto.res $(SRCDIR)\lotto.def
	@echo Linking Lotto.exe...
	@$(LINK) $(LFLAGS) name $(BINDIR)\Lotto.exe file $(BINDIR)\lotto.obj, $(BINDIR)\lottowin.obj, $(BINDIR)\lottolang.obj, $(BINDIR)\common.obj library os2386.lib
	@echo Binding resources...
	@$(RC) -q -bt=os2 $(BINDIR)\lotto.res $(BINDIR)\Lotto.exe
	@if exist $(BINDIR)\Lotto.exe echo BUILD OK Lotto

$(BINDIR)\common.obj : $(SRCDIR)\common\common.c $(SRCDIR)\common\common.h $(BINDIR)
	@echo Compiling src\common\common.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\common\common.c

$(BINDIR)\lotto.obj : $(SRCDIR)\lotto.c $(HDR) $(BINDIR)
	@echo Compiling src\lotto.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\lotto.c

$(BINDIR)\lottowin.obj : $(SRCDIR)\lottowin.c $(HDR) $(BINDIR)
	@echo Compiling src\lottowin.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\lottowin.c

$(BINDIR)\lottolang.obj : $(SRCDIR)\lottolang.c $(SRCDIR)\lottolang.h $(BINDIR)
	@echo Compiling src\lottolang.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\lottolang.c

$(BINDIR)\lotto.res : $(SRCDIR)\lotto.rc $(SRCDIR)\lottorc.h $(SRCDIR)\lotto.ico $(BINDIR)
	@echo Compiling src\lotto.rc
	@$(RC) $(RCFLAGS) -fo=$@ $(SRCDIR)\lotto.rc

$(BINDIR)\help\Lotto_en.hlp : help\Lotto_en.ipf $(BINDIR)\help
	@echo Compiling help\Lotto_en.ipf
	@$(WIPFC) -o $@ help\Lotto_en.ipf

$(BINDIR)\help\Lotto_es.hlp : help\Lotto_es.ipf $(BINDIR)\help
	@echo Compiling help\Lotto_es.ipf
	@$(WIPFC) -o $@ help\Lotto_es.ipf

$(BINDIR)\help\Lotto_nl.hlp : help\Lotto_nl.ipf $(BINDIR)\help
	@echo Compiling help\Lotto_nl.ipf
	@$(WIPFC) -o $@ help\Lotto_nl.ipf

$(BINDIR)\help\Lotto_de.hlp : help\Lotto_de.ipf $(BINDIR)\help
	@echo Compiling help\Lotto_de.ipf
	@$(WIPFC) -l de_DE -o $@ help\Lotto_de.ipf

$(BINDIR)\help\Lotto_fr.hlp : help\Lotto_fr.ipf $(BINDIR)\help
	@echo Compiling help\Lotto_fr.ipf
	@$(WIPFC) -l fr_FR -o $@ help\Lotto_fr.ipf

$(BINDIR)\help\Lotto_it.hlp : help\Lotto_it.ipf $(BINDIR)\help
	@echo Compiling help\Lotto_it.ipf
	@$(WIPFC) -o $@ help\Lotto_it.ipf

clean : .SYMBOLIC
	@if exist $(BINDIR)\*.obj del $(BINDIR)\*.obj >nul
	@if exist $(BINDIR)\*.res del $(BINDIR)\*.res >nul
	@if exist $(BINDIR)\*.exe del $(BINDIR)\*.exe >nul
	@if exist $(BINDIR)\*.map del $(BINDIR)\*.map >nul
	@if exist $(BINDIR)\help\*.hlp del $(BINDIR)\help\*.hlp >nul
	@echo Clean complete
