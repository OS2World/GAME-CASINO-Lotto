/* LOTTOWPS - Install Lotto */

IF RxFuncQuery('SysLoadFuncs') THEN DO
  	CALL RxFuncAdd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs'
  	CALL SysLoadFuncs
END
CALL SysCls
SAY ' '
SAY 'This program will create Program Object for Lotto.exe on your Desktop,'
SAY 'Press 'Y' (and Enter) to start Installation, any other key to exit...'
PULL answer
IF answer <> "Y" THEN DO
	Exit
END
SAY ' '
ProgramTitle = 'Lotto 1.02'
EXE = 'Lotto.exe'
ICO = 'Lotto.ico'
InstallDir = DIRECTORY()
WorkDir = DIRECTORY()
Setup = 'EXENAME='InstallDir'\'EXE';ICONFILE='InstallDir'\'ICO';STARTUPDIR='WorkDir''
Action = 'U'
SAY 'Creating Program object - LOTTO'
CALL SysCreateObject 'WPProgram',ProgramTitle,'<WP_DESKTOP>',Setup,Action
SAY ' '
SAY 'Program object created!'
SAY ' '
SAY 'Installation complete. You can start LOTTO now.'
SAY 'Press any key to exit...'
PULL answer
Exit

/* End */
