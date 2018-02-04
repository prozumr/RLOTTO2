 /*rlotto.c | RLotto | gcc | v0.7.348.1701
 * Console program for storing and evaluating lottery ticket results.
 * ----------------------------------------------------------------------------
 *
 * Objective:	Main Menu and core program loop
 *
 * Author: 		Reinhard Rozumek
 * Email: 		reinhard@rozumek.de
 * Created: 	09/23/17
 * Last mod:	12/31/17
 *
 * ----------------------------------------------------------------------------
 * This file is part of RLotto.
 *
 * RLotto is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * RLotto is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RLotto. If not, see <http://www.gnu.org/licenses/>.
 */



/* Header Section ************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include "rlotto.h"
#include "version.h"

/* GLOBAL VARIABLES **********************************************************/

int ALN[6];											// Actual Lottery Numbers
int ASN = -1;										// Actual Super Number
char cG77[8];										// Actual Game 77 Number
char cSU6[7];										// Actual Super 6 Number
char TicketFolder[13] = ".\\tickets\\";				// Folder to store results
char ResultFolder[13] = ".\\results\\";				// Folder to store results
FILE *pFile = NULL;									// Pointer to result file


/******************************************************************************
 * MAIN
 *****************************************************************************/

/* Function main just displays the main user menu and generates the main
	program loop. Program can only be terminated by the option from the main
	menu. All submenus are coded in other functions. */

int main() {

	int iSelect;												// Selection from Main Menu

	welcome();													// Welcome Message
	t_initialize();												// Initialize ticket data structure

	// TODO (camelo#3#01/03/18): Implement Console attribute (Title, Color etc.) ...

	/* Main Loop starts here */

	do {

		printf("\nMain Menu Options\n");
		printf("------------------------------------\n");
		printf("\t1 - Add Lottery Ticket\n");
		printf("\t2 - Delete Lottery Ticket\n");
		printf("\t3 - Evaluate Lottery Ticket\n");
		printf("\t4 - RLotto settings\n");
		printf("\t5 - Terminate Program\n");

		do {

			printf("\nPlease select (1-5): ");
			iSelect =(getche());
			fflush(stdin);

         } while(iSelect < 49 || iSelect > 53);

		iSelect = iSelect - 48;

		switch(iSelect) {

			case 1: addTicket(); break;
			case 2: deleteTicket(); break;
			case 3: selectTicket(); break;
			case 4: configureSettings(); break;
			case 5: terminateProgram();

		}

		} while(go_Exit == false);

}

/******************************************************************************
 * WELCOME
 *****************************************************************************/

 /* Welcome message and check for default RLotto file to open. */

int welcome(void) {

	printf("\n%s v%ld.%ld.%ld.%ld\n",THISPROG,MAJOR,MINOR,BUILD,REVISION);
	printf("Evaluating lottery results\n") ;

	return 0;
}

/******************************************************************************
 * INITIALIZE TICKET STRUCTURE
 *****************************************************************************/

/* Initializing all members of the ticket data structure.*/

int t_initialize(void) {

	// Initialize ticket structure
	strcpy(current.T_No, "0000000");
	strcpy(current.T_Player, "0000000000000000000000000000000000000000000000000000000000000000");
	strcpy(current.T_Start, "00/00/0000");
	strcpy(current.T_Runtime, "0");
	strcpy(current.T_D_Day, "u");
	strcpy(current.T_G77, "u");
	strcpy(current.T_SU6, "u");
	strcpy(current.T_GSP, "u");
	current.T_Max_Row = 0;

	for(int j = 0; j < 12; j++) {
		for(int k = 0; k < 6; k++) {
			current.T_Row[j][k] = 0;
		}
	}

	strcpy(display_runtime, "000000000");
	strcpy(display_weekday, "000000000");
	strcpy(display_G77, "000");
	strcpy(display_SU6, "000");
	strcpy(display_GSP, "000");

	return 0;

}


/******************************************************************************
 * TERMINATE PROGRAM
 *****************************************************************************/

/* terminateProgram displays a message for the program termination. Other
	functions like closing any open files, reset variables and write a history
 	message to the ini file still needs to be defined. */

int terminateProgram(void) {

	printf("\n");
 	printf("\n\nProgram terminated by user.\n");
 	go_Exit = true; // remove after Main Menu is completed
 	return 0;
}

