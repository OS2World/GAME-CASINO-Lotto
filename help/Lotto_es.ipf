.* Ayuda de Lotto
:userdoc.

:h1 res=001.Ayuda general
:font facename=Helv size=8x12.
:p.
Lotto genera selecciones de numeros al azar para loterias. Admite juegos desde 1 de 1 hasta 99 de 99 y crea hasta 999 combinaciones a la vez. Se pueden fijar hasta cinco numeros, que aparecen en todas las combinaciones. El resultado se puede guardar en un archivo. Elija un tema&colon.
:p.
:ul compact.
:li.:link reftype=hd res=002.Numeros y combinaciones:elink.
:li.:link reftype=hd res=003.Numeros fijos:elink.
:li.:link reftype=hd res=004.Resultado y guardado:elink.
:li.:link reftype=hd res=005.Menus y teclas:elink.
:li.:link reftype=hd res=006.Acerca de Lotto y licencia:elink.
:eul.
:p.

:h1 res=002.Numeros y combinaciones
:font facename=Helv size=8x12.
:p.
En el campo :hp2.Juego:ehp2. escriba cuantos numeros tiene una combinacion y, despues de :hp2.de:ehp2., entre cuantos numeros se elige (por ejemplo 7 de 39). Una combinacion no puede tener mas numeros que entre los que se elige; el total maximo es 99.
:p.
En :hp2.Combinaciones:ehp2. escriba cuantas combinaciones crear (1 a 999). Pulse :hp2.Adelante!:ehp2. (Ctrl+N) para generarlas. Cada combinacion tiene numeros distintos, ordenados de menor a mayor. :hp2.Borrar:ehp2. (Ctrl+L) vacia la lista y pone los campos en 7 de 39 con 8 combinaciones y sin numeros fijos.
:p.
Un campo que se deja con una entrada incorrecta vuelve a su valor por defecto.

:h1 res=003.Numeros fijos
:font facename=Helv size=8x12.
:p.
Los cinco campos tras :hp2.Fijos:ehp2. contienen numeros que deben estar en todas las combinaciones. Un 0 significa que no hay numero fijo. Los numeros deben estar entre 1 y el total, y no se puede repetir un numero.
:p.
Si hay mas numeros fijos de los que cabe en una combinacion, se usan los primeros.

:h1 res=004.Resultado y guardado
:font facename=Helv size=8x12.
:p.
Las combinaciones generadas aparecen en la lista, una por linea. :hp2.Archivo:ehp2. (Ctrl+S) guarda la lista en el archivo LOTTO.TXT del directorio de trabajo del programa; el archivo empieza con una linea que indica los numeros del juego y los numeros fijos, y cada combinacion va numerada. Tras guardar puede abrir el archivo con el editor del sistema OS/2.
:p.
La lista no se guarda con la configuracion; guardela antes de generar otra.

:h1 res=005.Menus y teclas
:font facename=Helv size=8x12.
:p.
Juego&colon. Generar (Ctrl+N), Borrar (Ctrl+L), Guardar en archivo (Ctrl+S), Salir (Ctrl+X). Opciones&colon. Idioma elige ingles, espanol, neerlandes, aleman, frances o italiano, y menus, dialogos y esta ayuda cambian al instante; Controles de marco (Ctrl+F) oculta o muestra la barra de titulo y el menu; Guardar al salir guarda la configuracion y los numeros del juego en Lotto.cfg.

:h1 res=006.Acerca de Lotto y licencia
:font facename=Helv size=8x12.
:p.
Lotto fue escrito por Goran Ivankovic en 1999 como programa VX-REXX (version 1.02). El programa fue reescrito en C para Open Watcom por la comunidad OS2World en 2026, a partir del codigo fuente conservado en el archivo de recursos original.
:p.
Lotto es software libre&colon. puede redistribuirlo y/o modificarlo bajo los terminos de la Licencia Publica General GNU publicada por la Free Software Foundation, ya sea la version 3 de la Licencia o (a su eleccion) cualquier version posterior. Se distribuye con la esperanza de que sea util, pero SIN NINGUNA GARANTIA. Vea el archivo LICENSE.txt.

:euserdoc.
