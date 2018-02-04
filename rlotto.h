 /*rlotto.h | RLotto | gcc | v0.7.348.1701
 * Console program for storing and evaluating lottery ticket results.
 * ----------------------------------------------------------------------------
 *
 * Objective:	Providing global variables and functions for RLotto
 *
 * Author: 		Reinhard Rozumek
 * Email: 		reinhard@rozumek.de
 * Created: 	10/08/17
 * Last mod:	01/26/18
 *
 * ----------------------------------------------------------------------------
 * This file is part of RLotto.
 * 
 * c is free software; you can redistribute it and/or
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
 * along with Tyche I. If not, see <http://www.gnu.org/licenses/>.
 */


 
#ifndef RLOTTO_H
#define RLOTTO_H
#define N 80
#define NOLR 12															// N_umber O_f L_ottery R_ows -1 (First Row with index 0)

 /* GLOBAL VARIABLES */
bool go_Exit;
struct date { short month, day, year; };								// not used !? => check

extern int ALN[6];														// Actual Lottery Numbers
extern int ASN;															// Actual Super Number
extern char cG77[8];													// Actual Game 77 Number
extern char cSU6[7];													// Actual Super 6 Number
extern char TicketFolder[13];                             				// Folder to store results
extern char ResultFolder[13];                             				// Folder to store results
extern FILE *pFile;                                                 	// Pointer to result file

/* GLOBAL DEFINITIONS */
#define MAX_T_PLAYER_SZ 64							// Max characters for player name
#define MAX_LINE_LENGTH 80							// Max characters for length of a ticket row
#define T_EXT ".tck"								// File extension for lottery tickets



 
 /* FUNCTION DECLARATIONS */
 
	int getche(void);
	int terminateProgram(void);
	int welcome(void); 													
	int selectTicket(void);												
	int addTicket(void);												
	int evaluateTicket(void);												
	int deleteTicket(void);											
	int configureSettings(void);											
	int terminateProgram(void);
	int t_initialize(void);								// Initialize ticket data structure											

	
/* STRUCTURE TICKET */

struct ticket {
	
	char T_No[8];									// Ticket Number - 7 digits + NULL terminator
	char T_Player[MAX_T_PLAYER_SZ];					// Player Name(s). Site limited by MAX_T_PLAYER_SZ
	char T_Start[11];								// Ticket Start Date 
	char T_Runtime[2];								// Runtime for ticket
	char T_D_Day[2];								// Drawing Day: s_saturday, w_ednesday, or b_oth
	char T_G77[2];									// Game 77 yes or no
	char T_SU6[2];									// Super 6 yes or no
	char T_GSP[2];									// Glueckspirale yes or no
	int T_Max_Row;									// Max Number of active rows
	int T_Row[12] [6];								// Lottery numbers per row
	   
} current;


/* MAPPING ATTRIBUTES*/

	char display_runtime[10];						// range: 1,2,3,4,5,month,permananet
	char display_weekday[10];						// range: Wed,Sat,Wed + Sat
	char display_G77[4];							// range: yes,no
	char display_SU6[4];							// range: yes,no
	char display_GSP[4];							// range: yes,no


#endif // TICKET_H_INCLUDED
