/* Lotto - language table. ASCII only (no accents).
   Order of the strings must match the enum in lottolang.h. */

#include <os2.h>
#include "lottolang.h"

int current_lang = LANG_EN;

const char *lang_strings[LANG_COUNT][S_COUNT] = {

/* ======================= LANG_EN ======================= */
{
    "~Game", "~Generate\tCtrl+N", "~Clear\tCtrl+L", "~Save to file\tCtrl+S", "E~xit\tCtrl+X",
    "~Options", "~Language", "~Frame Controls\tCtrl+F", "S~ave settings on exit",
    "~Help", "~General Help", "Help ~Index", "~Help on Help", "~About...",
    "Do it!", "Clear", "File", "About", "Exit",
    "Game:", "of", "Combinations:", "Fixed:", "%d combinations",
    "1st", "2nd", "3rd", "4th", "5th",
    "Here can be max %d numbers in a combination.",
    "Valid number for the %s fixed number is between 0 and %d.",
    "Nothing to do. The list is empty.",
    "Result saved to:",
    "%s\nTo view the file with the OS/2 System editor press OK. To return to the program press Cancel.",
    "Cannot write the file %s.",
    "%d of %d - %d combinations", "Fixed numbers:",
    "Lotto Help", "The help file %s was not found.\nPlease put it in the help folder next to Lotto.exe."
},

/* ======================= LANG_ES ======================= */
{
    "~Juego", "~Generar\tCtrl+N", "~Borrar\tCtrl+L", "~Guardar en archivo\tCtrl+S", "~Salir\tCtrl+X",
    "~Opciones", "~Idioma", "~Controles de marco\tCtrl+F", "~Guardar al salir",
    "A~yuda", "~Ayuda general", "~Indice de ayuda", "Ayuda so~bre la ayuda", "~Acerca de...",
    "Adelante!", "Borrar", "Archivo", "Acerca de", "Salir",
    "Juego:", "de", "Combinaciones:", "Fijos:", "%d combinaciones",
    "primer", "segundo", "tercer", "cuarto", "quinto",
    "En una combinacion puede haber como maximo %d numeros.",
    "El %s numero fijo debe estar entre 0 y %d.",
    "Nada que hacer. La lista esta vacia.",
    "Resultado guardado en:",
    "%s\nPara ver el archivo con el editor del sistema OS/2 pulse Aceptar. Para volver al programa pulse Cancelar.",
    "No se puede escribir el archivo %s.",
    "%d de %d - %d combinaciones", "Numeros fijos:",
    "Ayuda de Lotto", "No se encontro el archivo de ayuda %s.\nPongalo en la carpeta help junto a Lotto.exe."
},

/* ======================= LANG_NL ======================= */
{
    "~Spel", "~Genereren\tCtrl+N", "~Wissen\tCtrl+L", "~Opslaan in bestand\tCtrl+S", "~Afsluiten\tCtrl+X",
    "~Opties", "~Taal", "~Kaderbediening\tCtrl+F", "Instellingen op~slaan bij afsluiten",
    "~Help", "~Algemene help", "Help~index", "~Help bij help", "~Info...",
    "Doen!", "Wissen", "Bestand", "Info", "Einde",
    "Spel:", "uit", "Combinaties:", "Vast:", "%d combinaties",
    "eerste", "tweede", "derde", "vierde", "vijfde",
    "In een combinatie mogen hooguit %d getallen staan.",
    "Het %s vaste getal moet tussen 0 en %d liggen.",
    "Niets te doen. De lijst is leeg.",
    "Resultaat opgeslagen in:",
    "%s\nOm het bestand met de OS/2-systeemeditor te bekijken drukt u op OK. Om terug te keren naar het programma drukt u op Annuleren.",
    "Het bestand %s kan niet worden geschreven.",
    "%d uit %d - %d combinaties", "Vaste getallen:",
    "Lotto Help", "Het helpbestand %s is niet gevonden.\nPlaats het in de map help naast Lotto.exe."
},

/* ======================= LANG_DE ======================= */
{
    "~Spiel", "~Erzeugen\tCtrl+N", "~Loeschen\tCtrl+L", "~In Datei speichern\tCtrl+S", "~Beenden\tCtrl+X",
    "~Optionen", "~Sprache", "~Rahmenelemente\tCtrl+F", "Beim Beenden Einstellungen ~sichern",
    "~Hilfe", "~Allgemeine Hilfe", "Hilfe~index", "~Hilfe zur Hilfe", "~Ueber...",
    "Los!", "Loeschen", "Datei", "Ueber", "Ende",
    "Spiel:", "aus", "Kombinationen:", "Fest:", "%d Kombinationen",
    "erste", "zweite", "dritte", "vierte", "fuenfte",
    "In einer Kombination koennen hoechstens %d Zahlen stehen.",
    "Die %s feste Zahl muss zwischen 0 und %d liegen.",
    "Nichts zu tun. Die Liste ist leer.",
    "Ergebnis gespeichert in:",
    "%s\nUm die Datei mit dem OS/2-Systemeditor anzusehen, druecken Sie OK. Um zum Programm zurueckzukehren, druecken Sie Abbrechen.",
    "Die Datei %s kann nicht geschrieben werden.",
    "%d aus %d - %d Kombinationen", "Feste Zahlen:",
    "Lotto Hilfe", "Die Hilfedatei %s wurde nicht gefunden.\nBitte in den Ordner help neben Lotto.exe legen."
},

/* ======================= LANG_FR ======================= */
{
    "~Jeu", "~Generer\tCtrl+N", "~Effacer\tCtrl+L", "~Enregistrer dans un fichier\tCtrl+S", "~Sortir\tCtrl+X",
    "~Options", "~Langue", "~Controles du cadre\tCtrl+F", "Enregistrer en ~quittant",
    "~Aide", "Aide ~generale", "~Index de l'aide", "Aide sur l'~aide", "A ~propos...",
    "Allez!", "Effacer", "Fichier", "A propos", "Sortir",
    "Jeu:", "sur", "Combinaisons:", "Fixes:", "%d combinaisons",
    "premier", "deuxieme", "troisieme", "quatrieme", "cinquieme",
    "Une combinaison peut contenir au plus %d numeros.",
    "Le %s numero fixe doit etre compris entre 0 et %d.",
    "Rien a faire. La liste est vide.",
    "Resultat enregistre dans:",
    "%s\nPour voir le fichier avec l'editeur systeme OS/2, appuyez sur OK. Pour revenir au programme, appuyez sur Annuler.",
    "Impossible d'ecrire le fichier %s.",
    "%d sur %d - %d combinaisons", "Numeros fixes:",
    "Aide de Lotto", "Le fichier d'aide %s est introuvable.\nPlacez-le dans le dossier help a cote de Lotto.exe."
},

/* ======================= LANG_IT ======================= */
{
    "~Gioco", "~Genera\tCtrl+N", "~Cancella\tCtrl+L", "~Salva su file\tCtrl+S", "~Esci\tCtrl+X",
    "~Opzioni", "~Lingua", "~Controlli cornice\tCtrl+F", "Salva impostazioni all'~uscita",
    "~Aiuto", "Aiuto ~generale", "~Indice dell'aiuto", "Aiuto sull'~aiuto", "~Informazioni...",
    "Via!", "Cancella", "File", "Informazioni", "Esci",
    "Gioco:", "su", "Combinazioni:", "Fissi:", "%d combinazioni",
    "primo", "secondo", "terzo", "quarto", "quinto",
    "In una combinazione possono esserci al massimo %d numeri.",
    "Il %s numero fisso deve essere compreso tra 0 e %d.",
    "Niente da fare. L'elenco e vuoto.",
    "Risultato salvato in:",
    "%s\nPer vedere il file con l'editor di sistema OS/2 premere OK. Per tornare al programma premere Annulla.",
    "Impossibile scrivere il file %s.",
    "%d su %d - %d combinazioni", "Numeri fissi:",
    "Aiuto di Lotto", "Il file di aiuto %s non e stato trovato.\nMetterlo nella cartella help accanto a Lotto.exe."
}
};
