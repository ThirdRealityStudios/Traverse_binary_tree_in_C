#include <stdio.h>
#include <stdlib.h>

struct Knoten
{
    // Wert des Knotens.
    int key;

    // Nachfolge-Knoten.
    struct Knoten *next;
};

// "z" ist das Ende vom Stack (der Trick bei "z" ist,
// dass man später beim Runternehmen keine Sonderfälle beachten muss,
// da es auf sich selber zeigt).
// "t" ist nur ein temporärer Knoten, wenn ein neuer erzeugt werden soll.
// "Kopf" ist der Anfang vom Stack.
struct Knoten *z, *t, *Kopf;

/**
  * Den Stapel initialisieren mit den Standardelementen
  * "Kopf" (Anfangselement ganz oben auf'm Stapel) und
  * "z" (Endelement ganz unten, das lediglich das Ende markiert).
  */
void stackinit()
{
    // Hier wird ein Kopf-Element erstellt,
    // das jedoch nicht für die Datenhaltung gedacht ist.
    // Es soll nur den Anfang des Stacks markieren.
	Kopf = (struct Knoten *) malloc (sizeof *Kopf);

    // Hier ein weiterer Knoten erzeugt,
    // der ebenfalls nicht für die Datenhaltung gedacht ist.
    // Er dient lediglich der Markierung des Endes vom Stack.
	z = (struct Knoten *) malloc (sizeof *z);

    // Das Kopf zeigt jetzt direkt auf das Ende vom Stack.
    // Der Stack soll also leer sein.
	Kopf->next = z;

    // Der Anfang des Stacks soll keinen spezifischen Wert beinhalten,
    // da er ja nicht zur Datenhaltung gedacht ist.
    // Er bekommt daher einfach den Wert "0" (das neutrale Element der Mathematik in vielen Fällen).
    Kopf->key = 0;

    // Das Ende zeigt auf sich selber.
	z->next = z;
}

void push (int v)
{
    // Den neuen Knoten erzegen als "t" für "temporär".
	t = (struct Knoten *) malloc (sizeof *t);

    // Den Knoten mit dem entsprechenden Wert initialisieren.
	t->key = v;

    /*
     * Der Kopf ist beim Stack in dieser Implementierung
     * bildlich gesehen oben auf dem Stapel.
     * Das Ende ist somit immer unten.
     *
     * Was hier also geschieht ist Folgendes:
     *
     * Das neue Stapel-Element zeigt im ersten Schritt
     * hier auf das vorherige oberste Element des Stapels (Kopf -> next).
     */
    t -> next = Kopf -> next;

    /*
     * Der vorherige Schritt bringt aber noch nicht viel,
     * da der Anfang vom Stapel ("oben" also in der Implementierung bildlich gesehen)
     * dieses neue Stapel-Element noch nicht kennt.
     * Es ist bisher so,
     * dass das neue Stapel-Element
     * nur schon seinen Nachfolger "unten drunter" (vorheriges oberstes Stapel-Element).
     *
     * Daher passiert in der Wertzuweisung hierunter nun Folgendes:
     * der Stapel-Anfang (Kopf -> next) soll jetzt auf das neue
     * oberste Stapel-Element zeigen (t also).
     */
	Kopf -> next = t;

    // Somit wurde bis hier nun ein neues Stapel-Element auf den Stack gelegt..
}

int pop()
{
	int x;

    // Das oberste Stapel-Element (oben drauf also) als temporären
    // Knoten t merken,
    // damit dieser runtergenommen wird.
	t = Kopf -> next;

    // Der Stapel-Anfang soll jetzt einfach auf den Nachfolger
    // vom obersten Stapel-Element zeigen (das Element unter dem obersten Element also).
    // Zur Erinnerung: der Kopf bzw. Anfang ist in dieser Implmentierung ja ganz oben.
    Kopf -> next = t -> next;

    // Den Wert merken vom runtergenommenen Stapel-Element,
    // bevor dieses mit free(..) vom Arbeitsspeicher gelöscht wird (da ja nicht mehr benötigt).
	x = t -> key;

    // Das runtergenommene Stapel-Element aus dem Arbeitsspeicher löschen.
	free(t);

    // Den Wert vom runtergenommenen Stapel-Element zurückgeben.
	return x;
}

void main (void)
{
	char c; int x;
	
    // Den Stack initialisieren,
    // dann ein Zeichen einlesen als Bedingung und dieses Zeichen muss dann != '.' sein,
    // da sonst das Programm abgebrochen wird.
    // Ansonsten passiert nichts.
	for (stackinit(); (c = getchar()) != '.'; )
	{
		x = 0;

		if (c == '+') x = pop() + pop(); // Direkt zwei Operanden vom Stapel nehmen und addieren.
		if (c == '*') x = pop() * pop(); // Gleiches hier, aber mit Multiplikation

        // Nachtrag zu den zwei if-Statements: man geht halt davon aus, dass bei Angabe einer
        // Rechenoperation bereits zwei Operanden angegeben worden sind (gemäß Postorder),
        // da die Rechenoperation bei Postorder erst dann angegeben wird,
        // wenn man diese zwei Operanden bereits angegeben hat.
        // Daher kann man ruhigen Gewissens auch hier direkt zwei Operanden per pop()
        // vom Stapel nehmen und diese gleichzeitig addieren.
        // Falls der Nutzer hier eine ungültige Angabe macht, dann wird die Rechenoperation
        // entsprechend nicht erkannt.

        // Einen eingelesenen Wert (s. Anweisung in for-Bedingung, Latin1-Zeichen) in einen Integer umwandeln.
		while (c >= '0' && c <= '9')
		{
			x = 10 * x + (c - '0'); // Das eingelesene Zeichen in den entsprechenden Integer umwandeln.
			c = getchar(); // Neuen Operanden einlesen.
		}

        // Das Ergebnis x auf dem Stack pushen.
		if (x != 0) push (x);
	}

    // Das Ergebnis auf der Konsole ausgeben, indem man es vom Stack holt.
	printf ("%d\n", pop());
}
