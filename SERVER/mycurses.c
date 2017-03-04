
/*

Urbinelli Federico

federico.urbinelli@gmail.com

*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "mycurses.h"

/**
 * This function initialize the main menu choices (assigns the relative strings)
 * and does other primary and necessary tasks before starting ncurses
 */
void ncurses_init(void ){

	choices[0] = lang.s46;
	choices[1] = lang.s47;
	choices[2] = lang.s43;
	choices[3] = lang.s58;
	choices[4] = lang.s45;

	n_choices = sizeof(choices) / sizeof(char *);

	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	ncurses_initColors();
}

/**
 * This function starts color mode and define our enumerated colors
 * (see mycurses.h)
 */
void ncurses_initColors(void ){

	start_color();
	init_pair(RED_BLUE, COLOR_RED, COLOR_BLUE);
	init_pair(YELLOW_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(WHITE_WHITE, COLOR_WHITE, COLOR_WHITE);
	init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
	init_pair(GREEN_AZURE, COLOR_GREEN, COLOR_CYAN);
	init_pair(GREEN_GREEN, COLOR_GREEN, COLOR_GREEN);
	init_pair(YELLOW_RED, COLOR_YELLOW, COLOR_RED);	
	init_pair(MAGENTA_AZURE, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(YELLOW_AZURE, COLOR_YELLOW, COLOR_CYAN);
	init_pair(RED_RED, COLOR_RED, COLOR_RED);
	init_pair(AZURE_AZURE, COLOR_CYAN, COLOR_CYAN);
	init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN_BLUE, COLOR_GREEN, COLOR_BLUE);
	init_pair(BLUE_BLUE, COLOR_BLUE, COLOR_BLUE);
	init_pair(YELLOW_BLUE, COLOR_YELLOW, COLOR_BLUE);
	init_pair(RED_YELLOW, COLOR_RED, COLOR_YELLOW);
	init_pair(BLACK_GREEN, COLOR_BLACK, COLOR_GREEN);
	init_pair(BLACK_YELLOW, COLOR_BLACK, COLOR_YELLOW);
	init_pair(WHITE_BLUE, COLOR_WHITE, COLOR_BLUE);
	init_pair(BLACK_AZURE, COLOR_BLACK, COLOR_CYAN);
	init_pair(BLACK_BLACK, COLOR_BLACK, COLOR_BLACK);
	init_pair(RED_WHITE, COLOR_RED, COLOR_WHITE);
}


/**
 * This function checks if the console size is ok, then applies current
 * size to x and y which are passed as arguments
 * @param y screen rows
 * @param x screen columns
 */
void ncurses_initConsole(int *y, int *x){

	int min_x = 120, min_y = 40;
	char input;

	getmaxyx(stdscr, *y, *x);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(3));
	while (*y<min_y || *x<min_x){
		mvprintw(1,0, "[!] %s [!]", lang.s3);
		mvprintw(2,0, "[!] %s [!]", lang.s4);
		mvprintw(3,0, "[!] %s [!]", lang.s5);
		do
			input = getch();
		while (input != ' ');
		getmaxyx(stdscr, *y, *x);
	}

	/* initialize the x and y for the main windows created by the functions */
	mainwin_y = *y-2;		// max height - 2 rows
	mainwin_x = 90;			// just the default width
}

/**
 * This function creates a full-size window (our background window) and returns it
 * @param  y screen rows
 * @param  x screen columns
 * @return   local_win
 */
WINDOW *ncurses_background(int y, int x){

	WINDOW *local_win;

	local_win = newwin(y, x, 0, 0);
	ncurses_initColors();
	wbkgd(local_win, COLOR_PAIR(GREEN_GREEN));
	wattron(local_win, COLOR_PAIR(BLACK_GREEN));
	mvwprintw(local_win, 0, 0, "%s", lang.s59);
	int xstr = COLS/2 - ( ( (int) strlen(lang.s6) ) / 2);
	mvwprintw(local_win, LINES-1, xstr, "%s", lang.s6);  
	wrefresh(local_win);

	return local_win;
}

/**
 * The main menu
 * @param  local_win menu window
 * @param  logged    user login status
 * @param  highlight which choice to highlight when this function is called
 * @param  timeout   if timeout is reached or not
 * @return           choice made, ERR otherwise
 */
int ncurses_menu(WINDOW *local_win, int logged, int highlight, int *timeout){

	// choose in in run-time from where to start the window,
	// according to the width of the console (COLS)
	int startx = (COLS / 2) - mainwin_x/2;
	int choice = 0;
	int c;

	if(logged)
		// "change user"
		choices[0] = lang.s57;

	else if(isServerProgram())
		// "add user"
		choices[0] = lang.s46;
	
	else
		// "login"
		choices[0] = lang.s42; 

	delwin(local_win);
	local_win = newwin(mainwin_y, mainwin_x, 1, startx);
	keypad(local_win, TRUE);
	wbkgd(local_win, COLOR_PAIR(YELLOW_YELLOW));
	wattron(local_win, COLOR_PAIR(BLACK_YELLOW));
	wrefresh(local_win);
	cbreak();
	ncurses_printMenu(local_win, 10, 30, 4, mainwin_y, choices, n_choices, highlight);
	while(1){

		// wait just for 0.5 second for user's input 
		wtimeout(local_win, 500);

		c = wgetch(local_win);
		switch(c){

			case KEY_UP:
				if(highlight == 1)			// if you're at the top
					highlight = n_choices;	// highlight the last one
				else
					--highlight;
				break;

			case KEY_DOWN:
				if(highlight == n_choices)	// if you're at the bottom
					highlight = 1;			// highlight the first one
				else
					++highlight;
				break;

			case 10:	// enter
				choice = highlight;
				break;

			// timeout reached
			case ERR:
				*timeout = 1;
				choice = highlight;
				break;

			default:
				break;
		}
		ncurses_printMenu(local_win, 10, 30, 4, mainwin_y, choices, n_choices, highlight);
		if(choice != 0) // user made a choice, exit from loop
			break;
	}

	return choice;
}

/**
 * @param menu the host window
 * @param starty from which row print the first choice
 * @param startx from which column print the first choice
 * @param padding vertical space between each choice
 * @param height the height of the window
 * @param strings string array of the choices
 * @param n_str number of the choices
 * @param highlight which choice to highlight
 */
void ncurses_printMenu(WINDOW *menu, int starty, int startx, int padding, int height, char *strings[], int n_str, int highlight){

	int x, y, i;
	int increment;

	x = startx;
	y = starty;
	increment = padding;

	for(i = 0; i < n_str; ++i){
		if(highlight == i + 1){
			wattron(menu, A_REVERSE);
			mvwprintw(menu, y, x, "%s", strings[i]);
			wattroff(menu, A_REVERSE);
		}else{
			mvwprintw(menu, y, x, "%s", strings[i]);
		}
		y += increment;
	}
	wrefresh(menu);
}

/**
 * @param pf file pointer to the indexbook (to find usernames and passwords)
 * @param user pointer to user who may login
 * @param local_win pointer to main window
 * @return TRUE: user has succesfully logged in, FALSE otherwise
 */
int ncurses_login(FILE *pf, recUser *user, WINDOW *local_win){

	int startx = (COLS / 2) - mainwin_x/2;
	char s[25], pw[25];
	int f, attempts, j, k;
	int c;
	int x_star;

	delwin(local_win);
	local_win = newwin(mainwin_y, mainwin_x, 1, startx);
	wrefresh(local_win);
	wbkgd(local_win, COLOR_PAIR(AZURE_AZURE));
	wattron(local_win, COLOR_PAIR(BLACK_AZURE));
	mvwprintw(local_win, 0, 0, "%s", lang.s7);
	wrefresh(local_win);
	echo();	// display characters entered
	f = 0;
	attempts = 0;
	do{
		mvwscanw(local_win, 0, 23, "%s", s);
		f = findUsername(pf, s);
		if(f == FALSE){

			/* INCORRECT USERNAME */

			wclear(local_win);
			mvwprintw(local_win, 5, 0, "%s", lang.s8);
			mvwprintw(local_win, 0, 0, "%s", lang.s7);
			rewind(pf);
			wrefresh(local_win);
			attempts++;
			if(attempts == 5){

				/* INCORRECT USERNAME ENTERED FOR 5 TIMES CONSECUTIVELY */

				wbkgd(local_win, COLOR_PAIR(BLACK_BLACK));
				wattron(local_win, COLOR_PAIR(RED_BLACK));
				mvwprintw(local_win, 10, 20, "%s", lang.s9);
				mvwprintw(local_win, 11, 20, "%s", lang.s10);
				wrefresh(local_win);
				noecho();
				c = wgetch(local_win);
				if(c == 27){
					// ESC is pressed
					delwin(local_win);
					return FALSE;
				}
				attempts = 0;	// reset attempts
				wbkgd(local_win, COLOR_PAIR(AZURE_AZURE));
				wattron(local_win, COLOR_PAIR(BLACK_AZURE));
				mvwprintw(local_win, 0, 0, "%s", lang.s7);
				wrefresh(local_win);
			}
		}
	}while(f == FALSE);

	// store the username
	strcpy(getUsername(user), s);

	// now we need to find the password
	getc(pf);	// advance 1 char
	fscanf(pf,"%[^ ]",pw); // here is the password

	wclear(local_win);
	wattron(local_win, COLOR_PAIR(BLACK_AZURE));
	mvwprintw(local_win, 0, 0, "%s", lang.s11);
	wrefresh(local_win);
	noecho();	// don't echo characters typed
	attempts = 0;
	do{
		// clear string
		for(k = 0; k < 25; k++) memset(&s[k], 0, sizeof(s[k]));
		j = 0;
		x_star = 23;

		// until user press enter
		while((c = wgetch(local_win)) != 10){
			if(c == 8 || c == 127){	// backspace

				// clear previous '*' with one ' '
				if(x_star > 23) mvwprintw(local_win, 0, --x_star, " ");

				// delete previous character typed
				if(j > 0) s[--j] = (char) 0;

			}else{
				s[j] = c;
				j++;
				// display a '*' instead of what user types
				mvwprintw(local_win, 0, x_star, "*");
				x_star++;
			}
		}
		if(strcmp(pw, s) != 0){

			/* INCORRECT PASSWORD */

			wclear(local_win);
			mvwprintw(local_win, 5, 0, "%s", lang.s12);
			mvwprintw(local_win, 0, 0, "%s", lang.s11);
			wrefresh(local_win);
			attempts++;
			if(attempts == 5){

				/* INCORRECT PASSWORD ENTERED FOR 5 TIMES CONSECUTIVELY */

				wbkgd(local_win, COLOR_PAIR(BLACK_BLACK));
				wattron(local_win, COLOR_PAIR(RED_BLACK));
				mvwprintw(local_win, 10, 20, "%s", lang.s9);
				mvwprintw(local_win, 11, 20, "%s", lang.s10);
				wrefresh(local_win);
				noecho();
				c = wgetch(local_win);
				if(c == 27){
					// ESC is pressed
					delwin(local_win);
					return FALSE;
				}
				attempts = 0;	// reset attempts
				wbkgd(local_win, COLOR_PAIR(AZURE_AZURE));
				wattron(local_win, COLOR_PAIR(BLACK_AZURE));
				mvwprintw(local_win, 0, 0, "%s", lang.s11);
				wrefresh(local_win);
			}
		}
	}while(strcmp(pw, s) != 0);

	// store the password
	setPassword(user, pw);

	// store name and surname
	getc(pf);
	fscanf(pf,"%[^ ]",s);
	setName(user, s);
	getc(pf);
	fscanf(pf,"%[^\n]",s);
	setSurname(user, s);
	rewind(pf);
	delwin(local_win);

	return TRUE;
}

/**
 * This function simply displays the indexbook
 * @param pf file pointer to indexbook 
 * @param local_win pointer to main window 
 * @param users pointer to existing users 
 */
void ncurses_indexBook(FILE *pf, WINDOW *local_win, recUser *users){

	int startx = (COLS / 2) - mainwin_x/2;
	int iLine = 4, iUtenti = 0;
	char s[52];

	delwin(local_win);		
	local_win = newwin(mainwin_y, mainwin_x, 1, startx);
	wrefresh(local_win);
	wbkgd(local_win, COLOR_PAIR(AZURE_AZURE));
	wattron(local_win, COLOR_PAIR(BLACK_AZURE));
	int xstr = mainwin_x - ((int)strlen(lang.s13));
	mvwprintw(local_win, 0, xstr, "%s", lang.s13);
	mvwprintw(local_win, 2, 4, "%s", lang.s14);
	mvwprintw(local_win, 2, 30, "%s", lang.s15);
	mvwprintw(local_win, 2, 58, "Username");
	iUtenti = storeUsers(pf, users);

	int j;
	for(j = 0; j < iUtenti; j++){
		mvwprintw(local_win, iLine, 1, "%d. %s", iLine-3, getName(&users[j]));
		mvwprintw(local_win, iLine, 30, "%s", getSurname(&users[j]));
		mvwprintw(local_win, iLine, 58, "%s", getUsername(&users[j]));
		iLine++;
	}

	// as long as user doesn't press ESC
	while(wgetch(local_win) != 27);
}

/**
 * @param pf file pointer to indexbook
 * @param local_win pointer to main window
 * @param sender pointer to sender
 * @param msg pointer to message sended
 * @return TRUE: user has succesfully sended a message, FALSE otherwise
 */
int ncurses_sendMessage(FILE *pf, WINDOW *local_win, recUser *sender, recMessage *msg){

	int c;
	int startx = (COLS / 2) - mainwin_x/2;
	int highlight = 1, choice = 0;
	recTime msgtime;
	recDate msgdate;
	recUser receiver;

	
	setSender(msg, sender);	// set message sender

	delwin(local_win);		
	local_win = newwin(mainwin_y, mainwin_x, 1, startx);
	wrefresh(local_win);
	wbkgd(local_win, COLOR_PAIR(AZURE_AZURE));
	wattron(local_win, COLOR_PAIR(BLACK_AZURE));
	int xstr = mainwin_x - ((int)strlen(lang.s13));
	mvwprintw(local_win, 0, xstr, "%s", lang.s13);
	
	char *strings[] = {
		lang.s16,
		lang.s17,
	};

	keypad(local_win, TRUE);

	ncurses_interMenu(local_win, 10, 30, 5, mainwin_y, BLACK_AZURE, strings, 2);

	wclear(local_win);
	wrefresh(local_win);
	echo();
	
	if(choice == 1){

		/* READ DATE FROM USER INPUT */

		mvwprintw(local_win, 1, 1, "%s", lang.s18);
		wrefresh(local_win);
		wscanw(local_win, "%d", &msgdate.day);
		mvwprintw(local_win, 3, 1, "%s", lang.s19);
		wrefresh(local_win);
		wscanw(local_win, "%d", &msgdate.month);
		mvwprintw(local_win, 5, 1, "%s", lang.s20);
		wrefresh(local_win);
		wscanw(local_win, "%d", &msgdate.year);
		mvwprintw(local_win, 7, 1, "%s", lang.s21);
		wrefresh(local_win);
		wscanw(local_win, "%d", &msgtime.hours);
		mvwprintw(local_win, 9, 1, "%s", lang.s22);
		wrefresh(local_win);
		wscanw(local_win, "%d", &msgtime.minutes);
	}else{

		/* FILL IN CURRENT TIME (READ FROM MACHINE) */ 

		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		msgdate.day = tm.tm_mday;
		msgdate.month = tm.tm_mon + 1;
		msgdate.year = tm.tm_year + 1900;
		msgtime.hours = tm.tm_hour;
		msgtime.minutes = tm.tm_min;
	}

	/* set message date and time */
	setDate(msg, &msgdate);
	setTime(msg, &msgtime);

	/* USER ENTERS MESSAGE */
	char text[250];
	wclear(local_win);
	mvwprintw(local_win, 1, 1, "%s", lang.s23);
	wscanw(local_win, "%[^\n]", text); 
	setText(msg, text);
	wclear(local_win);

	/* USER ENTERS RECEIVER */
	int found = FALSE;
	do{
		mvwprintw(local_win, 1, 1, "%s", lang.s24);
		wrefresh(local_win);
		wscanw(local_win, "%s", receiver.username);
		found = findUsername(pf, getUsername(&receiver));
		if(!found){
			wclear(local_win);
			mvwprintw(local_win, 5, 1, "%s", lang.s25);
			rewind(pf);
		}
	}while(!found);

	/* READ RECEIVER INFO FROM INDEXBOOK */
	wclear(local_win);
	getc(pf);
	fscanf(pf, "%[^ ]", receiver.password);
	getc(pf);
	fscanf(pf, "%[^ ]", receiver.name);
	getc(pf);
	fscanf(pf, "%[^\n]", receiver.surname);
	rewind(pf);
	setReceiver(msg, &receiver);	// set message receiver

	/* PRINT MESSAGE SENDED */
	mvwprintw(local_win, 0, xstr, "%s", lang.s13);
	mvwprintw(local_win, 5, 1, "%s %02d/%02d/%d", lang.s26, getDay(&msg->date), getMonth(&msg->date), getYear(&msg->date));
	mvwprintw(local_win, 6, 1, "%s %02d.%02d", lang.s27, getHours(&msg->time), getMinutes(&msg->time));
	mvwprintw(local_win, 9, 1, "%s \"%s\"", lang.s28, getTxt(&msg->text));
	mvwprintw(local_win, 12, 1, "%s %s %s", lang.s29, getName(&msg->sender), getSurname(&msg->sender));
	mvwprintw(local_win, 13, 1, "%s %s %s", lang.s30, getName(&msg->receiver), getSurname(&msg->receiver));
	wrefresh(local_win);

	// as long as user doesn't press ESC
	noecho();
	while(wgetch(local_win) != 27);

	return TRUE;

}

/**
 * This function adds a user to indexbook and updates nUsers
 * @param pf file pointer to indexbook
 * @param local_win pointer to main window
 * @param nUsers current number of users
 */
void ncurses_addUser(FILE *pf, WINDOW *local_win, int *nUsers){

	char username[25], password[25], name[25], surname[25];
	int startx = (COLS / 2) - mainwin_x/2;

	closeFile(pf);
	pf = openFile("indexbook.txt", "a");

	delwin(local_win);		
	local_win = newwin(mainwin_y, mainwin_x, 1, startx);
	wrefresh(local_win);
	wbkgd(local_win, COLOR_PAIR(AZURE_AZURE));
	wattron(local_win, COLOR_PAIR(BLACK_AZURE));
	int xstr = mainwin_x - ((int)strlen(lang.s13));
	mvwprintw(local_win, 0, xstr, lang.s13);
	echo();
	mvwprintw(local_win, 1, 1, lang.s7);
	wscanw(local_win, "%s", username);
	mvwprintw(local_win, 3, 1, lang.s11);
	wscanw(local_win, "%s", password);
	mvwprintw(local_win, 5, 1, lang.s31);
	wscanw(local_win, "%s", name);
	mvwprintw(local_win, 7, 1, lang.s32);
	wscanw(local_win, "%s", surname);
	fprintf(pf, "%s %s %s %s\n", username, password, name, surname);
	mvwprintw(local_win, 12, 1, lang.s33);

	(*nUsers)++;

	closeFile(pf);
	pf = openFile("indexbook.txt", "r");

	// as long as user doesn't press ESC
	noecho();
	while(wgetch(local_win) != 27);

}

/**
 * This function deletes a user and updates nUsers in case of success
 * @param pfin file pointer to indexbook
 * @param local_win pointer to main window
 * @param nUsers current number of users
 * @return TRUE: user succesfully deleted, FALSE otherwise
 */
int ncurses_deleteUser(FILE *pfin, WINDOW *local_win, int *nUsers){

	FILE *pfout;
	int startx = (COLS / 2) - mainwin_x/2;
	int n;
	
	pfout = openFile("temp.txt", "w");
	delwin(local_win);		
	local_win = newwin(mainwin_y, mainwin_x, 1, startx);
	wrefresh(local_win);
	wbkgd(local_win, COLOR_PAIR(AZURE_AZURE));
	wattron(local_win, COLOR_PAIR(BLACK_AZURE));
	mvwprintw(local_win, 2, 1, lang.s34);
	mvwprintw(local_win, 3, 1, lang.s35);
	mvwprintw(local_win, 4, 1, "--> ");
	echo();	// echo input
	// read input
	wscanw(local_win, "%d", &n);
	while(n > *nUsers || n < 0){
		mvwprintw(local_win, 6, 1, lang.s36);
		wrefresh(local_win);
		mvwscanw(local_win, 4, 5, "%d", &n);
	}

	noecho();	// stop echo
	if(n == 0){	// user doesn't want to delete a user, return
		closeFile(pfout);
		return FALSE;
	}

	int i = 1;
	char username[25], password[25], name[25], surname[25];

	// read indexbook
	while(fscanf(pfin,"%s %s %s %s\n",username, password, name, surname) == 4){
		if(i != n)	// copy all except of index line entered by user
			fprintf(pfout,"%s %s %s %s\n",username, password, name, surname);
		i++;
	}

	// now rewrite updated indexbook
	closeFile(pfin);
	closeFile(pfout);
	pfout = openFile("indexbook.txt", "w");
	pfin = openFile("temp.txt", "r");
	int c;
	while((c = getc(pfin)) != EOF)
	   	putc(c, pfout);
	(*nUsers)--;
	closeFile(pfin);

	wclear(local_win);
	mvwprintw(local_win, 4, COLS/2 - 20, lang.s37);
	mvwprintw(local_win, 5, COLS/2 - 8, lang.s38);
	wrefresh(local_win);
	while(wgetch(local_win) != 27);

	return TRUE;
}

/**
 * This generic function simply display a message (it creates a new window).
 * The window size is dynamic, in relation with str[] size
 * @param str message to display
 */
void ncurses_alert(char str[]){

	WINDOW *local_win;

	/* dynamic window size */
	int maxWidth = 60;
	int size = 0;
	for(size; str[size] != '\0'; size++);
	int x = size;
	int y = 3;	// minimum lines: 3
	while(x >= maxWidth){
		x--;
		if(x%maxWidth == 0) y++;
	}

	local_win = newwin(y, x, 3, COLS/2 - maxWidth/2);
	wbkgd(local_win, COLOR_PAIR(WHITE_WHITE));
	wattron(local_win, COLOR_PAIR(RED_WHITE));
	mvwprintw(local_win, 0, 0, "%s", lang.s38);
	mvwprintw(local_win, 2, 0, "%s", str);

	// as long as user doesn't press ESC
	noecho();
	while(wgetch(local_win) != 27);
	delwin(local_win);

}

/**
 * This function says that a new message has arrived
 * @param local_win pointer to main window
 * @return wheter user read the message or not
 */
int ncurses_message_received(WINDOW *local_win){

	int startx = (COLS / 2) - mainwin_x/2;
	int choice;
	int xstr;

	char *strings[] = {
		lang.s51,
		lang.s52,
	};

	delwin(local_win);
	local_win = newwin((mainwin_y), mainwin_x, 1, startx);
	wbkgd(local_win, COLOR_PAIR(WHITE_WHITE));
	wattron(local_win, COLOR_PAIR(RED_WHITE));

	/*  putting the strings in the centre of this window */
	xstr = mainwin_x/2 - (((int)strlen(lang.s49))/2);
	mvwprintw(local_win, 5, xstr, lang.s49);
	xstr = mainwin_x/2 - (((int)strlen(lang.s50))/2);
	mvwprintw(local_win, 6, xstr, lang.s50);
	choice = ncurses_interMenu(local_win, 13, 30, 6, (mainwin_y)-10, RED_WHITE, strings, 2);

	return choice;

}

/**
 * This function DOES NOT delete previous window, instead it creates
 * a sub-menu inside of it.
 * @param local_win pointer to main window
 * @param starty from which row print the first choice
 * @param startx from which column print the first choice
 * @param padding vertical space between each choice
 * @param height the height of the window
 * @param color which color to use from our enum list
 * @param strings string array of the choices
 * @param n_str number of the choices
 * @return user choice
 */
int ncurses_interMenu(WINDOW *local_win, int starty, int startx, int padding, int height, int color, char *strings[], int n_str){

	int c;
	int i;
	int choice = 0;
	int highlight = 1;

	keypad(local_win, TRUE);
	wattron(local_win, COLOR_PAIR(color));
	int xstr = mainwin_x - ((int)strlen(lang.s13));
	mvwprintw(local_win, 0, xstr, lang.s13);
	cbreak();
	ncurses_printMenu(local_win, starty, startx, padding, height, strings, n_str, highlight);
	while(1){
		c = wgetch(local_win);
		switch(c){

			case KEY_UP:
				if(highlight == 1)
					highlight = n_str;
				else
					--highlight;
				break;

			case KEY_DOWN:
				if(highlight == n_str)
					highlight = 1;
				else
					++highlight;
				break;

			case 10:
				choice = highlight;
				break;

			case 27:
				choice = c;

			default:
				break;
		}
		ncurses_printMenu(local_win, starty, startx, padding, height, strings, n_str, highlight);
		if(choice != 0) break;	// user made a choice, exit from loop
	}

	if(choice == 27) return 0;
	else if(!n_str) return -1;
	else return choice;

}

/**
 * This function creates a new window that displays a list of all the unread messages.
 * @param local_win pointer to main window
 * @param msg pointer to unread messages
 * @param curent number of unread messages
 * @return -1 on error or 0 if user wants to exit
 */
int ncurses_unread_messages(WINDOW *local_win, recMessage *msg, int *n_mes){

	int startx = (COLS / 2) - mainwin_x/2;
	int iLine = 4;
	int choice;

	delwin(local_win);
	local_win = newwin(mainwin_y, mainwin_x, 1, startx);
	wrefresh(local_win);
	wbkgd(local_win, COLOR_PAIR(AZURE_AZURE));
	wattron(local_win, COLOR_PAIR(BLACK_AZURE));
	int xstr = mainwin_x - ((int)strlen(lang.s13));
	mvwprintw(local_win, 0, xstr, "%s", lang.s13);
	mvwprintw(local_win, 2, 6, "%s", lang.s54);
	mvwprintw(local_win, 2, mainwin_x/2, "%s", lang.s55);

	int i;
	for(i = 0; i < *n_mes; i++){
		mvwprintw(local_win, iLine, 1, "%d.", iLine-3);
		mvwprintw(local_win, iLine, 6, "%s %s", getName(&msg[i].sender), getSurname(&msg[i].sender));
		mvwprintw(local_win, iLine, mainwin_x/2, "%02d/%02d/%d %02d:%02d", getDay(&msg[i].date), getMonth(&msg[i].date),
			getYear(&msg[i].date), getHours(&msg[i].time), getMinutes(&msg[i].time));
		iLine++;
	}

	// allocate memory for pointer of strings
	char **strings = (char **)malloc((iLine-4) * sizeof(char *));
	for(i = 0; i < *n_mes; i++){
		// allocate memory for each string
		strings[i] = (char *)malloc(4 * sizeof(char));
		// copy content into string
		strcpy(strings[i], "[#]");
	}

	/**
	 * display a menu of [#] like this 
	 *
	 * ///////////////////////////////
	 * //                       [#] //
	 * //                       [#] //
	 * //                       [#] //
	 * ///////////////////////////////
	 * 
	 */
	choice = ncurses_interMenu(local_win, 4, mainwin_x-5, 1, (mainwin_y)-4, BLACK_AZURE, strings, *n_mes);
	if(choice == -1) return -1;	// error
	if(choice == 0) return 0;	// exit (main() doesn't call this function again)

	ncurses_read_message(msg[choice-1]);
	removeMessageFromArray(msg, msg[choice-1], n_mes);

	free(strings);

	return 1;	// tell the main() that it has to recall this function
}

/**
 * This function simply displays a message
 * @param msg message to read
 */
void ncurses_read_message(recMessage msg){

	WINDOW *local_win;
	int startx = (COLS / 2) - mainwin_x/2;

	local_win = newwin(mainwin_y/2, mainwin_x, mainwin_y/4, startx);
	wbkgd(local_win, COLOR_PAIR(WHITE_WHITE));
	wattron(local_win, COLOR_PAIR(RED_WHITE));
	int xstr = mainwin_x - ((int)strlen(lang.s56));
	mvwprintw(local_win, 0, xstr, "%s", lang.s56);
	mvwprintw(local_win, 5, 1, "%s %02d/%02d/%d", lang.s26, getDay(&msg.date), getMonth(&msg.date), getYear(&msg.date));
	mvwprintw(local_win, 6, 1, "%s %02d.%02d", lang.s27, getHours(&msg.time), getMinutes(&msg.time));
	mvwprintw(local_win, 9, 1, "%s \"%s\"", lang.s28, getTxt(&msg.text));
	mvwprintw(local_win, 12, 1, "%s %s %s", lang.s29, getName(&msg.sender), getSurname(&msg.sender));
	mvwprintw(local_win, 13, 1, "%s %s %s", lang.s30, getName(&msg.receiver), getSurname(&msg.receiver));
	wrefresh(local_win);

	// as long as user doesn't press ESC
	noecho();
	while(wgetch(local_win) != 27);
	delwin(local_win);

}

/**
 * This function displays a window where user is prompted
 * to select a language
 * @param local_win pointer to main window 
 */
void ncurses_select_language(WINDOW *local_win){

	int startx = (COLS / 2) - mainwin_x/2;
	int choice;

	// update these strings if you added any new language !!!
	char *strings[] = {
		"Italiano",
		"English",
	};

	delwin(local_win);
	local_win = newwin(mainwin_y, mainwin_x, 1, startx);
	wrefresh(local_win);
	wbkgd(local_win, COLOR_PAIR(AZURE_AZURE));
	wattron(local_win, COLOR_PAIR(BLACK_AZURE));

	mvwprintw(local_win, 2, 30, "L I N G U A   I N I Z I A L E");
	mvwprintw(local_win, 4, 30, "I N I T I A L   L A N G U A G E");
	choice = ncurses_interMenu(local_win, 10, 30, 5, (mainwin_y)-10, BLACK_AZURE, strings, 2);

	defineLanguage(choice);

}