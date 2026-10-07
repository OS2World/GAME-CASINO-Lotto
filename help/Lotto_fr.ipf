.* Aide de Lotto
:userdoc.

:h1 res=001.Aide generale
:font facename=Helv size=8x12.
:p.
Lotto genere des selections de numeros au hasard pour les loteries. Il permet des jeux de 1 sur 1 a 99 sur 99 et fait jusqu'a 999 combinaisons a la fois. Jusqu'a cinq numeros peuvent etre fixes, pour figurer dans toutes les combinaisons. Le resultat peut etre enregistre dans un fichier. Choisissez un sujet&colon.
:p.
:ul compact.
:li.:link reftype=hd res=002.Numeros et combinaisons:elink.
:li.:link reftype=hd res=003.Numeros fixes:elink.
:li.:link reftype=hd res=004.Resultat et enregistrement:elink.
:li.:link reftype=hd res=005.Menus et touches:elink.
:li.:link reftype=hd res=006.A propos de Lotto et licence:elink.
:eul.
:p.

:h1 res=002.Numeros et combinaisons
:font facename=Helv size=8x12.
:p.
Dans le champ :hp2.Jeu:ehp2. entrez combien de numeros contient une combinaison et, apres :hp2.sur:ehp2., parmi combien de numeros on choisit (par exemple 7 sur 39). Une combinaison ne peut pas contenir plus de numeros qu'il n'y en a a choisir; le total maximal est 99.
:p.
Dans :hp2.Combinaisons:ehp2. entrez combien de combinaisons faire (1 a 999). Appuyez sur :hp2.Allez!:ehp2. (Ctrl+N) pour les generer. Chaque combinaison contient des numeros differents, du plus petit au plus grand. :hp2.Effacer:ehp2. (Ctrl+L) vide la liste et remet les champs a 7 sur 39 avec 8 combinaisons et sans numeros fixes.
:p.
Un champ laisse avec une entree erronee est remis a sa valeur par defaut.

:h1 res=003.Numeros fixes
:font facename=Helv size=8x12.
:p.
Les cinq champs apres :hp2.Fixes:ehp2. contiennent des numeros qui doivent figurer dans toutes les combinaisons. Un 0 signifie pas de numero fixe. Les numeros doivent etre compris entre 1 et le total et ne peuvent pas etre repetes.
:p.
S'il y a plus de numeros fixes qu'une combinaison n'en contient, les premiers sont utilises.

:h1 res=004.Resultat et enregistrement
:font facename=Helv size=8x12.
:p.
Les combinaisons generees apparaissent dans la liste, une par ligne. :hp2.Fichier:ehp2. (Ctrl+S) enregistre la liste dans le fichier LOTTO.TXT du repertoire de travail du programme; le fichier commence par une ligne indiquant les numeros du jeu et les numeros fixes, et chaque combinaison est numerotee. Apres l'enregistrement vous pouvez ouvrir le fichier avec l'editeur systeme OS/2.
:p.
La liste n'est pas conservee avec les parametres; enregistrez-la avant d'en generer une nouvelle.

:h1 res=005.Menus et touches
:font facename=Helv size=8x12.
:p.
Jeu&colon. Generer (Ctrl+N), Effacer (Ctrl+L), Enregistrer dans un fichier (Ctrl+S), Sortir (Ctrl+X). Options&colon. Langue choisit l'anglais, l'espagnol, le neerlandais, l'allemand, le francais ou l'italien, et menus, dialogues et cette aide changent immediatement; Controles du cadre (Ctrl+F) masque ou affiche la barre de titre et le menu; Enregistrer en quittant stocke les parametres et les numeros du jeu dans Lotto.cfg.

:h1 res=006.A propos de Lotto et licence
:font facename=Helv size=8x12.
:p.
Lotto a ete ecrit par Goran Ivankovic en 1999 comme programme VX-REXX (version 1.02). Le programme a ete reecrit en C pour Open Watcom par la communaute OS2World en 2026, d'apres le code source conserve dans le fichier de ressources d'origine.
:p.
Lotto est un logiciel libre&colon. vous pouvez le redistribuer et/ou le modifier selon les termes de la Licence Publique Generale GNU telle que publiee par la Free Software Foundation, soit la version 3 de la Licence, soit (a votre gre) toute version ulterieure. Il est distribue dans l'espoir qu'il sera utile, mais SANS AUCUNE GARANTIE. Consultez le fichier LICENSE.txt.

:euserdoc.
