# Lotto

A lottery combination generator for OS/2 and ArcaOS. Version **1.10**.

Lotto draws random number selections for games from 1 of 1 to 99 of 99, makes up
to 999 combinations at a time and can keep up to five fixed numbers in every
combination. The result can be saved to a file (`LOTTO.TXT`).

![Goran's Lotto ScreenShot](/doc/GoransLotto.png)

The original program (version 1.02, 1999) was written by Goran Ivankovic in
VX-REXX. The source code was recovered from its resource file (`Lotto.RES`, kept
in `legacy/`) and the program was rewritten in C for Open Watcom by the
OS2World community in 2026.

## Features

* Six languages, switched at run time: English, Spanish, Dutch, German, French, Italian (menus, dialogs, messages and online help)
* Online help in `help\` (one `.hlp` file per language)
* Settings are saved in `Lotto.cfg`
* Shortcuts: Ctrl+N generate, Ctrl+L clear, Ctrl+S save, Ctrl+X exit, Ctrl+F frame controls

## Layout

```
src/        source code (src/common holds the shared helper code)
bin/        build output
doc/        Readme.txt, Changelog.txt, LICENSE.txt
help/       IPF help sources (en, es, nl, de, fr, it)
legacy/     the original files and the recovered REXX code
```

## Build

Open Watcom 2.0 and the OS/2 Toolkit 4.5 are required. On ArcaOS run:

```
compile-wat.cmd
```

The result is in `bin\`. The script writes `compile-wat.log` and prints `BUILD OK` or `BUILD FAILED`.

## License

GNU General Public License, version 3 or (at your option) any later version.
See [doc/LICENSE.txt](doc/LICENSE.txt).

## Authors

* Goran Ivankovic (original, 1999)
* OS2World community (Open Watcom port, 2026)
