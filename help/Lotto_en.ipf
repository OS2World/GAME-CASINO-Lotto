.* Lotto Help
:userdoc.

:h1 res=001.General Help
:font facename=Helv size=8x12.
:p.
Lotto generates random number selections for lotteries. It allows games from 1 of 1 to 99 of 99 and makes up to 999 combinations at a time. Up to five numbers can be fixed, so that they appear in every combination. The result can be saved to a file. Choose a topic&colon.
:p.
:ul compact.
:li.:link reftype=hd res=002.Numbers and combinations:elink.
:li.:link reftype=hd res=003.Fixed numbers:elink.
:li.:link reftype=hd res=004.Result and saving:elink.
:li.:link reftype=hd res=005.Menus and keys:elink.
:li.:link reftype=hd res=006.About Lotto and license:elink.
:eul.
:p.

:h1 res=002.Numbers and combinations
:font facename=Helv size=8x12.
:p.
In the field :hp2.Game:ehp2. enter how many numbers a combination holds, and after :hp2.of:ehp2. how many numbers there are to choose from (for example 7 of 39). A combination cannot hold more numbers than there are to choose from; the largest total is 99.
:p.
In :hp2.Combinations:ehp2. enter how many combinations to make (1 to 999). Press :hp2.Do it!:ehp2. (Ctrl+N) to generate them. Each combination holds different numbers, listed from the smallest to the largest. :hp2.Clear:ehp2. (Ctrl+L) empties the list and sets the entry fields to 7 of 39 with 8 combinations and no fixed numbers.
:p.
A field that is left with a wrong entry is reset to its default value.

:h1 res=003.Fixed numbers
:font facename=Helv size=8x12.
:p.
The five fields after :hp2.Fixed:ehp2. hold numbers which must be in every combination. A 0 means no fixed number. The numbers must lie between 1 and the total, and the same number cannot be entered twice.
:p.
If there are more fixed numbers than a combination holds, the first ones are used.

:h1 res=004.Result and saving
:font facename=Helv size=8x12.
:p.
The generated combinations appear in the list, one per line. :hp2.File:ehp2. (Ctrl+S) saves the list into the file LOTTO.TXT in the working directory of the program; the file begins with a line giving the numbers of the game and the fixed numbers, and each combination is numbered. After saving you may open the file with the OS/2 system editor.
:p.
The list is not saved in the settings; save it before you generate a new one.

:h1 res=005.Menus and keys
:font facename=Helv size=8x12.
:p.
Game&colon. Generate (Ctrl+N), Clear (Ctrl+L), Save to file (Ctrl+S), Exit (Ctrl+X). Options&colon. Language selects English, Spanish, Dutch, German, French or Italian, and menus, dialogs and this help change at once; Frame Controls (Ctrl+F) hides or shows the title bar and menu; Save settings on exit stores the settings and the numbers of the game in Lotto.cfg.

:h1 res=006.About Lotto and license
:font facename=Helv size=8x12.
:p.
Lotto was written by Goran Ivankovic in 1999 as a VX-REXX program (version 1.02). The program was rewritten in C for Open Watcom by the OS2World community in 2026, working from the source code kept in the original resource file.
:p.
Lotto is free software&colon. you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License or (at your option) any later version. It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY. See the file LICENSE.txt.

:euserdoc.
