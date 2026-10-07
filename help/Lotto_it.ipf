.* Aiuto di Lotto
:userdoc.

:h1 res=001.Guida generale
:font facename=Helv size=8x12.
:p.
Lotto genera selezioni casuali di numeri per le lotterie. Permette giochi da 1 su 1 a 99 su 99 e crea fino a 999 combinazioni alla volta. Si possono fissare fino a cinque numeri, che compaiono in ogni combinazione. Il risultato si puo salvare in un file. Scegliere un argomento&colon.
:p.
:ul compact.
:li.:link reftype=hd res=002.Numeri e combinazioni:elink.
:li.:link reftype=hd res=003.Numeri fissi:elink.
:li.:link reftype=hd res=004.Risultato e salvataggio:elink.
:li.:link reftype=hd res=005.Menu e tasti:elink.
:li.:link reftype=hd res=006.Informazioni su Lotto e licenza:elink.
:eul.
:p.

:h1 res=002.Numeri e combinazioni
:font facename=Helv size=8x12.
:p.
Nel campo :hp2.Gioco:ehp2. inserire quanti numeri contiene una combinazione e, dopo :hp2.su:ehp2., tra quanti numeri si sceglie (ad esempio 7 su 39). Una combinazione non puo contenere piu numeri di quelli tra cui si sceglie; il totale massimo e 99.
:p.
In :hp2.Combinazioni:ehp2. inserire quante combinazioni creare (da 1 a 999). Premere :hp2.Via!:ehp2. (Ctrl+N) per generarle. Ogni combinazione contiene numeri diversi, dal piu piccolo al piu grande. :hp2.Cancella:ehp2. (Ctrl+L) svuota l'elenco e riporta i campi a 7 su 39 con 8 combinazioni e senza numeri fissi.
:p.
Un campo lasciato con un valore errato torna al valore predefinito.

:h1 res=003.Numeri fissi
:font facename=Helv size=8x12.
:p.
I cinque campi dopo :hp2.Fissi:ehp2. contengono numeri che devono comparire in ogni combinazione. Uno 0 significa nessun numero fisso. I numeri devono essere compresi tra 1 e il totale e non possono ripetersi.
:p.
Se i numeri fissi sono piu di quelli che una combinazione contiene, si usano i primi.

:h1 res=004.Risultato e salvataggio
:font facename=Helv size=8x12.
:p.
Le combinazioni generate compaiono nell'elenco, una per riga. :hp2.File:ehp2. (Ctrl+S) salva l'elenco nel file LOTTO.TXT nella directory di lavoro del programma; il file inizia con una riga che indica i numeri del gioco e i numeri fissi, e ogni combinazione e numerata. Dopo il salvataggio si puo aprire il file con l'editor di sistema OS/2.
:p.
L'elenco non viene salvato con le impostazioni; salvarlo prima di generarne uno nuovo.

:h1 res=005.Menu e tasti
:font facename=Helv size=8x12.
:p.
Gioco&colon. Genera (Ctrl+N), Cancella (Ctrl+L), Salva su file (Ctrl+S), Esci (Ctrl+X). Opzioni&colon. Lingua sceglie inglese, spagnolo, olandese, tedesco, francese o italiano, e menu, dialoghi e questo aiuto cambiano subito; Controlli cornice (Ctrl+F) nasconde o mostra la barra del titolo e il menu; Salva impostazioni all'uscita memorizza le impostazioni e i numeri del gioco in Lotto.cfg.

:h1 res=006.Informazioni su Lotto e licenza
:font facename=Helv size=8x12.
:p.
Lotto e stato scritto da Goran Ivankovic nel 1999 come programma VX-REXX (versione 1.02). Il programma e stato riscritto in C per Open Watcom dalla comunita OS2World nel 2026, a partire dal codice sorgente conservato nel file di risorse originale.
:p.
Lotto e software libero&colon. potete ridistribuirlo e/o modificarlo secondo i termini della GNU General Public License pubblicata dalla Free Software Foundation, nella versione 3 della Licenza o (a vostra scelta) in qualsiasi versione successiva. E distribuito nella speranza che sia utile, ma SENZA ALCUNA GARANZIA. Consultate il file LICENSE.txt.

:euserdoc.
