
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

// you could add your own language here if it doesn't exist yet :-)

#include "languages.h"

CURR_LANG defineLanguage(int n){

	switch(n){
		// ITA
		case 1:
			strcpy(lang.s1, "Numero parametri errato.\n\nCLIENT: riesegui passando, in ordine, l'indirizzo IP e la porta del server.\nSERVER: riesegui passando la porta da bind()are.\n\nChiusura...\n");
			strcpy(lang.s2, "Devi prima effettuare il login!");
			strcpy(lang.s3, "LA CONSOLE E' PIU' PICCOLA DI 120x40");
			strcpy(lang.s4, "RIDIMENSIONALA PRIMA DI COMINCIARE");
			strcpy(lang.s5, "Premi BARRA SPAZIATRICE quando sei pronto");
			strcpy(lang.s6, "Programma realizzato da Federico Urbinelli. Qualsiasi contributo e' apprezzato, sotto i termini della licenza.");
			strcpy(lang.s7, "Inserisci l'username:");
			strcpy(lang.s8, "Username errato. Riprova.");
			strcpy(lang.s9, "Vuoi tornare al menu? Premi ESC.");
			strcpy(lang.s10, "Se invece vuoi riprovare, premi un altro tasto qualsiasi.");
			strcpy(lang.s11, "Inserisci la password:");
			strcpy(lang.s12, "Password errata. Riprova.");
			strcpy(lang.s13, "Premi ESC per tornare al menu");
			strcpy(lang.s14, "Nome");
			strcpy(lang.s15, "Cognome");
			strcpy(lang.s16, "Inserire data e ora manualmente");
			strcpy(lang.s17, "Leggere data e ora dal sistema");
			strcpy(lang.s18, "Inserisci il giorno: ");
			strcpy(lang.s19, "Inserisci il mese: ");
			strcpy(lang.s20, "Inserisci l'anno: ");
			strcpy(lang.s21, "Inserisci le ore: ");
			strcpy(lang.s22, "Inserisci i minuti: ");
			strcpy(lang.s23, "Inserisci il testo (max 250 caratteri): ");
			strcpy(lang.s24, "Inserisci l'username del destinatario: ");
			strcpy(lang.s25, "Username non trovato. Riprova.");
			strcpy(lang.s26, "Data: ");
			strcpy(lang.s27, "Ora: ");
			strcpy(lang.s28, "Testo del messaggio: ");
			strcpy(lang.s29, "Mittente: ");
			strcpy(lang.s30, "Destinatario: ");
			strcpy(lang.s31, "Inserisci il nome: ");
			strcpy(lang.s32, "Inserisci il cognome: ");
			strcpy(lang.s33, "Utente aggiunto con successo al file indexbook.txt");
			strcpy(lang.s34, "Inserisci il numero dell'utente da cancellare.'");
			strcpy(lang.s35, "Digita 0 per tornare al menu.");
			strcpy(lang.s36, "Input non valido. Riprova.");
			strcpy(lang.s37, "Utente cancellato con successo.");
			strcpy(lang.s38, "Premi ESC");
			strcpy(lang.s39, "Leggi archivio");
			strcpy(lang.s40, "Aggiorna archivio");
			strcpy(lang.s41, "Archivio aggiornato con successo.\nPremi ESC");
			strcpy(lang.s42, "Login");
			strcpy(lang.s43, "Rubrica");
			strcpy(lang.s44, "Invia messaggio");
			strcpy(lang.s45, "Esci");
			strcpy(lang.s46, "Aggiunti utente");
			strcpy(lang.s47, "Rimuovi utente");
			strcpy(lang.s48, "Archivio");
			strcpy(lang.s49, "Nuovo messaggio ricevuto!");
			strcpy(lang.s50, "Vuoi visualizzarlo?");
			strcpy(lang.s51, "Apri messaggio");
			strcpy(lang.s52, "Non ora");
			strcpy(lang.s53, "Messaggi non visualizzati");
			strcpy(lang.s54, "Mittente");
			strcpy(lang.s55, "Ora di ricezione");
			strcpy(lang.s56, "Premi ESC per uscire");
			strcpy(lang.s57, "Cambia utente");
			strcpy(lang.s58, "Cambia lingua");
			strcpy(lang.s59, "Whatsapp 1.1");
			break;
		// ENG
		case 2:
			strcpy(lang.s1, "Wrong command-line arguments number.\n\nCLIENT: Execute again, passing, in order, the server IP address and port.\nSERVER: Execute again, passing the port to bind().\n\nClosing...\n");
			strcpy(lang.s2, "You must log-in first!");
			strcpy(lang.s3, "CONSOLE IS SMALLER THAN 120x40");
			strcpy(lang.s4, "EXPAND IT BEFORE STARTING");
			strcpy(lang.s5, "Press SPACE BAR when you're ready");	
			strcpy(lang.s6, "Software developed by Federico Urbinelli. Any contribute is appreciated, under the terms of license.");
			strcpy(lang.s7, "Enter the username: ");
			strcpy(lang.s8, "Wrong username. Try again.");
			strcpy(lang.s9, "Want to return to the main menu? Press ESC.");
			strcpy(lang.s10, "If instead you want to try again, press any other key.");
			strcpy(lang.s11, "Enter the password: ");
			strcpy(lang.s12, "Wrong password. Try again.");
			strcpy(lang.s13, "Press ESC to return to the menu");
			strcpy(lang.s14, "Name");
			strcpy(lang.s15, "Surname");
			strcpy(lang.s16, "Enter date & time manually");
			strcpy(lang.s17, "Read date & time from the system");
			strcpy(lang.s18, "Enter the day: ");
			strcpy(lang.s19, "Enter the month: ");
			strcpy(lang.s20, "Enter the year: ");
			strcpy(lang.s21, "Enter the hours: ");
			strcpy(lang.s22, "Enter the minutes: ");
			strcpy(lang.s23, "Enter the text (max 250 characters): ");
			strcpy(lang.s24, "Enter receiver's username: ");
			strcpy(lang.s25, "Username not found. Try again.");
			strcpy(lang.s26, "Date: ");
			strcpy(lang.s27, "Time: ");
			strcpy(lang.s28, "Message text: ");
			strcpy(lang.s29, "Sended by: ");
			strcpy(lang.s30, "To: ");
			strcpy(lang.s31, "Enter the name: ");
			strcpy(lang.s32, "Enter the surname: ");
			strcpy(lang.s33, "User added with success to the file indexbook.txt");
			strcpy(lang.s34, "Enter the user's number to delete");
			strcpy(lang.s35, "Enter 0 to return to the menu.");
			strcpy(lang.s36, "Input not valid. Try again.");
			strcpy(lang.s37, "User deleted with success.");
			strcpy(lang.s38, "Press ESC");
			strcpy(lang.s39, "Read archive");
			strcpy(lang.s40, "Update archive");
			strcpy(lang.s41, "Archive updated with success.\nPress ESC");
			strcpy(lang.s42, "Login");
			strcpy(lang.s43, "Index book");
			strcpy(lang.s44, "Send message");
			strcpy(lang.s45, "Exit");
			strcpy(lang.s46, "Add user");
			strcpy(lang.s47, "Delete user");
			strcpy(lang.s48, "Archive");
			strcpy(lang.s49, "New message received!");
			strcpy(lang.s50, "Want to read it now?");
			strcpy(lang.s51, "Open message");
			strcpy(lang.s52, "Not now");
			strcpy(lang.s53, "Unread messages");
			strcpy(lang.s54, "Sender");
			strcpy(lang.s55, "Time of receipt");
			strcpy(lang.s56, "Press ESC to exit");
			strcpy(lang.s57, "Change user");
			strcpy(lang.s58, "Change language");
			strcpy(lang.s59, "Whatsapp 1.1");
			break;
	}

	return lang;
}

