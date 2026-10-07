Lotto for OS/2 - Version 1.10
=============================

OVERVIEW
--------
Lotto generates random number selections for lotteries. It allows games from
1 of 1 to 99 of 99 and makes up to 999 combinations at a time. Up to five
numbers can be fixed so that they appear in every combination. The result can
be saved to a file.

Originally written by Goran Ivankovic in 1999 as a VX-REXX program (version
1.02). Rewritten in C for Open Watcom (ArcaOS / OS/2 Warp 4) by the OS2World
community, 2026, from the source code kept in the original resource file.

The program speaks English, Spanish, Dutch, German, French and Italian.
Choose Options - Language to switch; menus, dialogs and the online help change
at once.

HOW TO USE
----------
Game       how many numbers a combination holds, and out of how many numbers
           they are chosen (for example 7 of 39). A combination cannot hold
           more numbers than there are to choose from. The largest total is 99.
Combinations   how many combinations to make, 1 to 999.
Fixed      up to five numbers that appear in every combination; 0 means none.
           The same number cannot be entered twice.

Press Do it! (Ctrl+N) to generate. The combinations are listed one per line,
each in ascending order. Clear (Ctrl+L) empties the list and puts the fields
back to 7 of 39, 8 combinations and no fixed numbers. File (Ctrl+S) saves the
list into LOTTO.TXT in the working directory and offers to open it with the
OS/2 system editor.

MENUS AND KEYS
--------------
Ctrl+N Generate, Ctrl+L Clear, Ctrl+S Save to file, Ctrl+X Exit,
Ctrl+F Frame Controls (hide the title bar and the menu), F1 Help.

FILE LIST
---------
Lotto.exe            the program
help\Lotto_xx.hlp    online help, one file per language
Lotto.cfg            settings, created on exit if enabled
LOTTO.TXT            the saved result
doc\                 Readme.txt, Changelog.txt, LICENSE.txt

BUILDING
--------
Install Open Watcom 2.0 and run compile-wat.cmd. The result is in bin\.

DISCLAIMER
----------
Lotto only draws random numbers. The author makes no representations about the
accuracy or suitability of this program for any purpose. It is provided "as
is", without any express or implied warranties. You may not distribute Lotto
in any way which leads to your making a profit from it.

LICENSE
-------
GNU General Public License, version 3 or later. See LICENSE.txt.

AUTHORS
-------
Goran Ivankovic (original, 1999); OS2World community (port, 2026).
