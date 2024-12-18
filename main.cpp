#include <iostream>
#include <string>
using namespace std;

/*
Autor: Elias Eder
Startdatum: 30.10.2023
Abgabedatum: 21.11.2023
Version: 1.0
OS: Windows
*/



//Klassendeklaration

class BENUTZERKONTO {

private:

	//Attribute eines Mitarbeiters
	string Nachname;
	string Vorname;
	string Geburtsdatum;
	int Behinderungsgrad;
	int Urlaub_genommen;
	int Resturlaub;

public:

	//Methode zur Anlage eines neuen Mitarbeiters
	void mitarbeiteranlage() {
		
		system("cls");

		//Eingabe der neuen Mitarbeiterdaten:
		cout << "Mitarbeiteranlage\nBitte Nachname eingeben:\t";
		cin >> Nachname;
		cout << "Bitte Vorname eingaben:\t\t";
		cin >> Vorname;
		cout << "Bitte Geburtsdatum (TT.MM.JJJJ) eingeben:\t";
		cin >> Geburtsdatum;
		cout << "Bitte Behinderungsgrad (Ganzzahl ohne %) eingeben:\t";
		cin >> Behinderungsgrad;

		//Berechnung des gesamten Urlaubs des Mitarbeiters
		int Urlaub = urlaubsberechnung();
		
		//Ueberpruefung, ob der genommene Urlaub den gesamten Urlaub uebersteigt
		do {
			cout << "Bitte bereits genommenen Urlaub in Tagen eingeben:\t";
			cin >> Urlaub_genommen;
			if (Urlaub_genommen > Urlaub) {
				cout << "\nEs stehen insgesamt nur " << Urlaub << " Urlaubstage zur verfuegung!\n";
			}
		} while (Urlaub_genommen > Urlaub);
		Resturlaub = Urlaub - Urlaub_genommen;

		system("cls");
		cout << "\n\nMitarbeiter erfolgreich angelegt!\n\n";
	};
	
	//Methode zur Urlaubsbuchung
	void urlaubsbuchung() {
		int Urlaub = urlaubsberechnung();
		int newUrlaub;

		//Validierung, dass der neu gebuchte Urlaub den Gesamturlaub nicht uebersteigt
		do {
			cout << "Bitte eintragen, wie viele Tage Urlaub genommen wird:\t";
			cin >> newUrlaub;
			if (newUrlaub > Resturlaub) {
				cout << "\nEs stehen nur noch " << Resturlaub << " Urlaubstage zur verfuegung!\n";
			}
		} while (newUrlaub > Resturlaub);

		Urlaub_genommen = Urlaub_genommen + newUrlaub;
		Resturlaub = Urlaub - Urlaub_genommen;

		cout << "\nDer Mitarbeiter hat sich schon " << Urlaub_genommen << " Tage Urlaub genommen.\n";
	}

	//Methode zur Anzeige des gesamten Urlaubs bzw. des Resturlaubs
	void urlaubsanzeige() {	
		cout << "\nInsgesamt stehen " << Urlaub_genommen + Resturlaub << " Urlaubstage zur Verfuegung\n";
		cout << "Der Restliche Urlaub betraegt " << Resturlaub << " Tage\n\n";
	}

	//Gibt gespeicherten Mitarbeiterinfos aus
	void anzeige_daten_ma(int a, bool sensible_Daten) {	
		if (!Nachname.empty() && !Vorname.empty() && !Geburtsdatum.empty()) {
			cout << "\nMitarbeiter " << 1 + a << endl;
			cout << "\nNachname:\t\t" << Nachname << endl;
			cout << "Vorname:\t\t" << Vorname << endl;

			//Gibt die sensiblen Daten aus
			if (sensible_Daten) {
				cout << "Geburtsdatum:\t\t" << Geburtsdatum << endl;
				cout << "Behinderungsgrad:\t" << Behinderungsgrad << endl << endl;
			}
		}
	}


	//Überprüfung auf leere Objekte (Falls ein Mitarbeiter geloescht wurde)
	bool mitarbeiternummer_checking() {
		if (!Nachname.empty() && !Vorname.empty() && !Geburtsdatum.empty()) {
			return 1;
		}
		else {
			return 0;
		}

	}

	//Berechnung des zur verfuegung stehenden Urlaubs
	int urlaubsberechnung() {

		const int aktuellesJahr = 2023;
		const int alterZusatzurlaub = 50;

		string Geburtsjahr = Geburtsdatum.substr(6, 4);

		int Geburtsjahr_Int = stoi(Geburtsjahr);
		
		int Urlaub = 30;
		if (Geburtsjahr_Int <= aktuellesJahr - alterZusatzurlaub) {
			Urlaub = 32;
		}

		if (Behinderungsgrad >= 50) {
			Urlaub += 5;
		}

		return Urlaub;
	
	}

};


//Funktion zum Aufruf jedes Mitarbeiters, der nicht geloescht wurde
int mitarbeiteraufruf(BENUTZERKONTO ma[], int i, bool whole) {
	system("cls");

	//Check, ob Bereits Mitarbeiter angelegt wurden (oder alle geloescht wurden)
	for (int c = 0; c < 500; c++) {
		bool angelegt = ma[c].mitarbeiternummer_checking();

		if (angelegt) {
			int a;
				for (a = 0; a < i; a++) {
					ma[a].anzeige_daten_ma(a, whole);
				}
			//Rueckgabewert, damit nur bei vorhandenen Mitarbeitern, die aufrufende Funktion weiter ausgef�hrt wird
			return 1;
			break;
		}
		else if (!angelegt && c == 499) {
			cout << "\n\nKeine Eintraege Vorhanden!\n\n";
			return 0;
		}
	}
	
	

}


//Check ob die Auswahl des Mitarbeiters bei loeschung, Urlaubsbuchung, ..., auf einen existierenden Mitarbeiter verweist
int eingabecheck(BENUTZERKONTO ma[]) {
	int validierendeZahl;
	do {
		cin >> validierendeZahl;
		if (validierendeZahl <= 0) {
			cout << "\nUngueltige Zahl! Bitte gueltige Zahl eingeben:\t";
		}
		else {
			bool checkNum = ma[validierendeZahl - 1].mitarbeiternummer_checking();
			if (checkNum == 0) {
				cout << "\nMitarbeiter nicht gefunden! Bitte gueltige Zahl eingeben:\t";
			}
			else {
				break;
			}
		}
	} while (true);

	return validierendeZahl;
}



int main() {	
	//Generierung der maximal fuenfhundert Benutzerkonten als Objekt-Array
	const int Anzahl_Benutzerkonten = 500;
	BENUTZERKONTO ma[Anzahl_Benutzerkonten];

	//Initialisierung
	for (int INI = 0; INI < 500; INI++) {
		ma[INI] = BENUTZERKONTO();
	}

	//Variable um das Hochzaehlen der Mitarbeiter zu ermoeglichen
	int Mitarbeiternummer = 0;
	
	//Variable um festzustellen, ob "Mitarbeiternummer" 500 erreicht hat
	bool ueberfuellt = 0;

	//Erstellen des Auswahlmenues
	enum Menue_t {anlage = 1, loeschung = 2, buchung = 3, urlaubanzeige = 4, anzeige_daten_ma = 5, ende = 6};


	//Erstellung eines ewigen Loopes, um die Menueauswahl fortzusetzen, bis "ende" ausgewaehlt wird
	while (true) {
		int menueauswahl;

		cout << "Personalverwaltungsprogamm\nBitte waehlen Sie aus folgenden Punkten:" << endl;
		cout << "1. Mitarbeiter anlegen\n2. Mitarbeiter loeschen\n3. Urlaub buchen\n4. Resturlaub anzeigen\n5. Alle Mitarbeiterdaten anzeigen\n6. Programm Beenden\n\n";
		
		//Eingabe des gewuenschten Modus
		cin >> menueauswahl;

		//Abbruchbedingung
		if (menueauswahl == ende) {
			return 0;
		}

		//Anlage eines Mitarbeiters
		else if (menueauswahl == anlage) {

			//Sonderfall: Es wurden bereits 500 Mitarbeiter angelegt
			bool exit_weil_Ueberfuellt = 0;
			if (ueberfuellt || Mitarbeiternummer == 500) {

				ueberfuellt = 1;
				
				//Check, ob es noch freie Objekte gibt
				for (int i = 0; i < 500; i++) {
					bool leerObjekt = ma[i].mitarbeiternummer_checking();

					//Fall 1: Zuweisung des Wertes eines leeren Objekts fuer "Mitarbeiternummer" 
					if (leerObjekt) {
						Mitarbeiternummer = i;
						break;
					}

					//Fall 2: Alle Objekte sind bef�llt
					if (i == 499 && Mitarbeiternummer != i) {
						cout << "\n\nSpeicher voll!\nEs koennen keine Mitarbeiter mehr angelegt werden!\n";
						exit_weil_Ueberfuellt = true;
					}
				}
			}
			//Wenn Speicher nicht voll ist, wird die Mitarbeiteranlage aufgerufen
			if (!exit_weil_Ueberfuellt) {
				ma[Mitarbeiternummer].mitarbeiteranlage();
				Mitarbeiternummer++;
			}
		}

		//Aufruf aller eingetragenen Mitarbeiter mit sensiblen Informationen
		else if (menueauswahl == anzeige_daten_ma) {	
			mitarbeiteraufruf(ma, Mitarbeiternummer, 1);
		}

		//Mitarbeiterloeschung
		else if (menueauswahl == loeschung) {
			//Aufruf aller eingetragenen Mitarbeiter
			bool check = mitarbeiteraufruf(ma, Mitarbeiternummer, 0);

			if (check) {
				//Auswahl des zu loeschenden Mitarbeiters
				cout << "\nWelcher Mitarbeiter soll geloescht werden?\nBitte Zahl eingeben:\t";

				int deletingNum = eingabecheck(ma);

				cout << "\n Mitarbeiter " << deletingNum << " wird geloescht. Fortfahren? (j)";
				string deletingCheck;
				cin >> deletingCheck;
				if (deletingCheck == "j") {

					ma[deletingNum - 1] = BENUTZERKONTO();
					cout << "\nMitarbeiter wurde geloescht!\n\n";
				}
			}

		}

		//Urlaubsbuchung
		else if (menueauswahl == buchung) {
			//Aufruf aller eingetragenen Mitarbeiter
			bool check = mitarbeiteraufruf(ma, Mitarbeiternummer, 0);

			if (check) {
				//Auswahl des Mitarbeiters, bei dem Urlaub gebucht werden soll
				cout << "\nWelcher Mitarbeiter moechte Urlaub buchen?\nBitte Zahl eingeben:\t";

				int holidayNum = eingabecheck(ma);

				ma[holidayNum-1].urlaubsbuchung();
			}
		}
		
		//Anzeige Resturlaub
		else if (menueauswahl == urlaubanzeige) {
			bool check = mitarbeiteraufruf(ma, Mitarbeiternummer, 0);
			
			if (check) {
				cout << "\nWelcher Mitarbeiter moechte seinen Resturlaub anzeigen?\nBitte Zahl eingeben:\t";

				int holidayNum = eingabecheck(ma);
				
				ma[holidayNum-1].urlaubsanzeige();
			}
		}

		//Ungueltige Eingabe
		else {	
			system("cls");
			cout << "\n\nUngueltige Auswahl!\n\n";
		}

		
	}

	return 0;
}





