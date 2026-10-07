/* Lotto 1.02 - REXX code recovered from Lotto.RES (VX-REXX project file).
   Original author: Goran Ivankovic, 1999.  Objects are named as in VX-REXX:
   loto = main window (100); C102 Do it!; C103 Clear; C104 File (save); C105 About;
   C106 Exit; C108 progress text; C109 result list; C110 numbers per combination;
   C112 total numbers; C115 number of combinations; C122..C126 fixed numbers;
   C127 fixed numbers display; C114 hidden work list. */

/* ---- procedure showfixed ---- */
showfixed:
myfixed = C122.Text()||' '||C123.Text()||' '||C124.Text()||' '||C125.Text()||' '||C126.Text()
oldText = C127.Text(myfixed)
RETURN

/* ---- procedure defnumber ---- */
defnumber:
oldText = C110.Text('7')
oldText = C112.Text('39')
oldText = C115.Text('8')
oldText = C122.Text('0')
oldText = C123.Text('0')
oldText = C124.Text('0')
oldText = C125.Text('0')
oldText = C126.Text('0')
CALL showfixed
RETURN

/* ---- procedure writeme ---- */
writeme:
myfile = 'LOTTO.TXT'
'del '||myfile
mytxt = loto.Text()||', (c)Goran Ivankovic, '||DATE()||'; '||TIME()
CALL LINEOUT myfile, mytxt
mytxt = C110.Text()||' of '||C112.Text()||' - '||C115.Text()||' combinations'
IF numfixed > 0 THEN DO
    DO i = 1 TO WORDS(myfixed)
	IF STRIP(WORD(myfixed,i)) > 0 THEN DO
	    CALL C114.Add FORMAT(WORD(myfixed,i),2,0),'A'
	END
    END
    fixstr = ''
    DO i = 1 TO loto.C114.Item()
	fixstr = fixstr||' '||loto.C114.Item(i)
    END
    CALL C114.Delete
    mytxt = mytxt||'     Fixed numbers:'||fixstr
END
CALL LINEOUT myfile, mytxt
mytxt = ' '
CALL LINEOUT myfile,mytxt
DO i = 1 TO allcomb
    CALL LINEOUT myfile,FORMAT(i,3,0)||'.'||C109.Item(i)
    IF RIGHT(i,1) = 0 THEN DO
	oldText = C108.Text(i)
    END
END
oldText = loto.C108.Text('')
CALL LINEOUT myfile
rc = STREAM(myfile,"c","CLOSE")
CALL C109.Select 1
CALL C110.Focus
CALL BEEP 500,100
IF RxMessageBox(DIRECTORY()||'\LOTTO.TXT'||'0D0A'x||'To view file with OS/2 System editor press OK. To return to program press Cancel.','Result saved to:','OKCANCEL','INFORMATION') = 1 THEN DO
    'START /F E.exe '||DIRECTORY()||'\LOTTO.TXT'
END
RETURN

/* ---- procedure randomize ---- */
randomize:
numfixed = 0
DO i = 1 TO WORDS(myfixed)
    IF WORD(myfixed,i) > 0 THEN DO
	numfixed = numfixed + 1
    END
END
IF numfixed > comb THEN DO
    numfixed = comb
END
DO j = 1 TO sumkomb
    lotoline =''
    DO i = 1 TO WORDS(myfixed)
	IF WORD(myfixed,i) > 0 THEN DO
	    CALL C114.Add FORMAT(WORD(myfixed,i),2,0),'A'
	END
    END
    IF numfixed < comb THEN DO
	DO k = 1 TO comb - numfixed
	    mynum = FORMAT(RANDOM(1,total),2,0)
	    mynumis = 0
	    DO l = 1 TO C114.Item()
		IF mynum = C114.Item(l) THEN DO
		    mynumis = 1
		END
	    END
	    IF mynumis = 0 THEN DO
		CALL C114.Add mynum,'A'
	    END
	    IF mynumis = 1 THEN DO
		k = k - 1
	    END
	END
    END
    DO m = 1 TO comb
	lotonum = C114.Item(m)
	lotoline = lotoline||FORMAT(lotonum,3,0)
    END
    CALL C114.Delete
    CALL C109.Add lotoline
    oldText = C108.Text(j)
END
CALL BEEP 500,100
oldText = C108.Text('')
RETURN

/* ---- procedure iserror ---- */
iserror:
PARSE ARG chknum, errtxt
IF chknum > total THEN DO
    myerror = 1
    IF RxMessageBox('Valid number for '||errtxt||' fixed number is between 0 and '||total,,,'ERROR') = 1 THEN DO
    END
END
RETURN

/* ---- loto Init ---- */
lotox = 320
lotoy = 310
step = 20
PARSE VALUE ScreenSize() WITH cx cy
CALL loto.Position (cx-lotox)%2, (cy-lotoy)%2, lotox, lotoy
PARSE VALUE loto.Frame() WITH fll flb flr flt
CALL C114.Position fll, flb, lotox-fll-flr, step
CALL C199.Position fll, flb, lotox-fll-flr, step
x198 = fll
y198 = flb+step
xs198 = lotox-fll-flr
ys198 = lotoy-flb-flt-step
CALL C198.Position x198, y198, xs198, ys198
CALL C109.Position x198+fll*2, y198+flb*2, xs198-fll*2-flr*2, step*8
minixs198 = (xs198-fll*8)%5
CALL C102.Position x198+fll*2, y198+flb*4+step*8, minixs198, step+flb
CALL C103.Position x198+minixs198+fll*3, y198+flb*4+step*8, minixs198, step+flb
CALL C104.Position x198+minixs198*2+fll*4, y198+flb*4+step*8, minixs198, step+flb
CALL C105.Position x198+minixs198*3+fll*5, y198+flb*4+step*8, minixs198, step+flb
CALL C106.Position x198+minixs198*4+fll*6, y198+flb*4+step*8, minixs198, step+flb
CALL C107.Position x198+fll*2-1, y198+flb*4+step*8-1, xs198-fll-flr, step+flb+2
CALL C197.Position x198+fll, y198+flb*6+step*9, xs198-fll-flr, step+flb*2
CALL C120.Position x198+fll*2-1, y198+flb*7+step*9-1, xs198-fll-flr, step+2
CALL C121.Position x198+fll*2, y198+flb*7+step*9, lotox%6, step
CALL C122.Position x198+(lotox*2)%12+fll*3, y198+flb*7+step*9, lotox%12, step
CALL C123.Position x198+(lotox*3)%12+fll*4, y198+flb*7+step*9, lotox%12, step
CALL C124.Position x198+(lotox*4)%12+fll*5, y198+flb*7+step*9, lotox%12, step
CALL C125.Position x198+(lotox*5)%12+fll*6, y198+flb*7+step*9, lotox%12, step
CALL C126.Position x198+(lotox*6)%12+fll*7, y198+flb*7+step*9, lotox%12, step
CALL C127.Position x198+(lotox*7)%12+fll*8, y198+flb*7+step*9, lotox%4, step
CALL C101.Position x198+fll*2, y198+flb*9+step*10, lotox%6, step
CALL C110.Position x198+(lotox*2)%12+fll*3, y198+flb*9+step*10, lotox%12, step
CALL C111.Position x198+(lotox*3)%12+fll*4, y198+flb*9+step*10, lotox%12, step
CALL C112.Position x198+(lotox*4)%12+fll*5, y198+flb*9+step*10, lotox%12, step
CALL C113.Position x198+(lotox*5)%12+fll*6, y198+flb*9+step*10, lotox%4, step
CALL C115.Position x198+minixs198*4+fll*6, y198+flb*9+step*10, lotox%12, step
CALL C108.Position x198+minixs198*4+lotox%12+fll*7, y198+flb*9+step*10, lotox%12, step

oldFont = loto.Font('9.WarpSans')
oldFont = C109.Font('10.Courier')
oldHint = C104.Hint('Save result to: '||DIRECTORY()||'\LOTTO.TXT')
oldHint = C105.Hint('About '||loto.Text())
CALL loto.C199.IsDefault 'C'
CALL showfixed
CALL loto.Show
CALL C110.Focus

/* ---- C102 Click ---- */
myerror = 0
CALL C109.Delete
CALL C114.Delete
comb = C110.Text()
total = C112.Text()
IF comb > total THEN DO
    myerror = 1
    IF RxMessageBox('Here can be max '||total||' numbers in combination.',,,'ERROR') = 1 THEN DO
    END
END
sumkomb = C115.Text()
fixed1 = C122.Text()
fixed2 = C123.Text()
fixed3 = C124.Text()
fixed4 = C125.Text()
fixed5 = C126.Text()
CALL iserror fixed1, '1st'
CALL iserror fixed2, '2nd'
CALL iserror fixed3, '3rd'
CALL iserror fixed4, '4th'
CALL iserror fixed5, '5th'

IF myerror = 0 THEN DO
    CALL loto.Disable
    CALL randomize
    CALL loto.Enable
END
IF myerror = 1 THEN DO
    CALL defnumber
END

/* ---- C103 Click ---- */
CALL C109.Delete
CALL C114.Delete
CALL defnumber

/* ---- C104 Click ---- */
allcomb = C109.Item()
IF allcomb = 0 THEN DO
    IF RxMessageBox('Nothing to do. List is empty.',,,'ERROR') = 1 THEN DO
    END
END
IF allcomb > 0 THEN DO
    CALL writeme
END

/* ---- C105 Click ---- */
about = "Lotto generates random number selections for lotteries. It allows selections between 1/1 to 99/99 with 999 calculated combinations. " ||,
	"5 numbers can be fixed, to be in every combination. Result can be saved to file "||DIRECTORY()||"\LOTTO.TXT"||'0D0A'x ||,
	"Copyright: Goran Ivankovic     goran_ivankovic@excite.com     http://members.tripod.com/~Goran_Ivankovic/"||'0D0A'x ||,
	"This program is provided free under the terms of the GPL. You can use it, modify it and distribute it.  "||,
	"If you do modify or distribute it the new source must accompany the distribution. I would appreciate a copy of any changes."||'0D'x ||,
	"You may not distribute Lotto in any way which leads to your making a profit from it."||'0D0A'x ||,
	"The author makes no representations about the accuracy or suitability of this material for any purpose. " ||,
	"It is provided "as is", without any express or implied warranties."

IF RxMessageBox(about,'About '||loto.Text()) = 1 THEN DO
END

/* ---- C106 Click ---- */
EXIT

/* ---- C110 LoseFocus ---- */
IF DATATYPE(C110.Text()) <> 'NUM' | C110.Text() < 1 THEN DO
    CALL BEEP 400,50
    CALL C110.Text '7'
    CALL C110.Focus
END

/* ---- C112 LoseFocus ---- */
IF DATATYPE(C112.Text()) <> 'NUM' | C112.Text() < 1 THEN DO
    CALL BEEP 400,50
    CALL C112.Text '39'
    CALL C112.Focus
END

/* ---- C115 LoseFocus ---- */
IF DATATYPE(C115.Text()) <> 'NUM' | C115.Text() < 1 THEN DO
    CALL BEEP 400,50
    CALL C115.Text '8'
    CALL C115.Focus
END

/* ---- C122 LoseFocus ---- */
IF DATATYPE(C122.Text()) <> 'NUM' | C122.Text() < 0 THEN DO
    CALL BEEP 400,50
    CALL C122.Text '0'
    CALL C122.Focus
END
SELECT
    WHEN C122.Text() = C123.Text() THEN oldText = C122.Text('0')
    WHEN C122.Text() = C124.Text() THEN oldText = C122.Text('0')
    WHEN C122.Text() = C125.Text() THEN oldText = C122.Text('0')
    WHEN C122.Text() = C126.Text() THEN oldText = C122.Text('0')
    OTHERWISE NOP
END
CALL showfixed

/* ---- C123 LoseFocus ---- */
IF DATATYPE(C123.Text()) <> 'NUM' | C123.Text() < 0 THEN DO
    CALL BEEP 400,50
    CALL C123.Text '0'
    CALL C123.Focus
END
SELECT
    WHEN C123.Text() = C122.Text() THEN oldText = C123.Text('0')
    WHEN C123.Text() = C124.Text() THEN oldText = C123.Text('0')
    WHEN C123.Text() = C125.Text() THEN oldText = C123.Text('0')
    WHEN C123.Text() = C126.Text() THEN oldText = C123.Text('0')
    OTHERWISE NOP
END
CALL showfixed

/* ---- C124 LoseFocus ---- */
IF DATATYPE(C124.Text()) <> 'NUM' | C124.Text() < 0 THEN DO
    CALL BEEP 400,50
    CALL C124.Text '0'
    CALL C124.Focus
END
SELECT
    WHEN C124.Text() = C122.Text() THEN oldText = C124.Text('0')
    WHEN C124.Text() = C123.Text() THEN oldText = C124.Text('0')
    WHEN C124.Text() = C125.Text() THEN oldText = C124.Text('0')
    WHEN C124.Text() = C126.Text() THEN oldText = C124.Text('0')
    OTHERWISE NOP
END
CALL showfixed

/* ---- C125 LoseFocus ---- */
IF DATATYPE(C125.Text()) <> 'NUM' | C125.Text() < 0 THEN DO
    CALL BEEP 400,50
    CALL C125.Text '0'
    CALL C125.Focus
END
SELECT
    WHEN C125.Text() = C122.Text() THEN oldText = C125.Text('0')
    WHEN C125.Text() = C123.Text() THEN oldText = C125.Text('0')
    WHEN C125.Text() = C124.Text() THEN oldText = C125.Text('0')
    WHEN C125.Text() = C126.Text() THEN oldText = C125.Text('0')
    OTHERWISE NOP
END
CALL showfixed

/* ---- C126 LoseFocus ---- */
IF DATATYPE(C126.Text()) <> 'NUM' | C126.Text() < 0 THEN DO
    CALL BEEP 400,50
    CALL C126.Text '0'
    CALL C126.Focus
END
SELECT
    WHEN C126.Text() = C122.Text() THEN oldText = C126.Text('0')
    WHEN C126.Text() = C123.Text() THEN oldText = C126.Text('0')
    WHEN C126.Text() = C124.Text() THEN oldText = C126.Text('0')
    WHEN C126.Text() = C125.Text() THEN oldText = C126.Text('0')
    OTHERWISE NOP
END
CALL showfixed
