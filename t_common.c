 /*t_common.c | RLotto | gcc | v0.0.3.0
 * Console program for storing and evaluating lottery ticket results.
 * ----------------------------------------------------------------------------
 *
 * Objective:	Common functions used in various parts of this program.
 *
 * Author: 		Reinhard Rozumek
 * Email: 		reinhard@rozumek.de
 * Created: 	11/17/17
 * Last mod:	11/18/17
 *
 * ----------------------------------------------------------------------------
 * This file is part of RLotto.                                               */


 // HEADER SECTION

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <time.h>
#include "rlotto.h"


// FUNCTION DECLARATION


bool isCorrectTicketNo(char *n);
bool isCorrectDateFormat(int m, int d, int y);
bool isLeapYear(const int iYear);
void map_t_attributes(int choice);
void display_Ticket(void);


/******************************************************************************
 * IsCorrectTicketNo
 *****************************************************************************/
// Checks length and character (only '0' to '9' are allowed)

 bool isCorrectTicketNo(char *n) {

	 bool result = false;
	 int x;
	 int y = 0;

	 // check for characters - only 0-9 are allowed
	 for(int i = 0; i < 7; i++) {
		 x = n[i] - 0;
		 if(x > 47 && x < 58)
			y++;
		 else
			break;
	 }

	 if(y == 7)
		 result = true;
	 return result;
 }

 /******************************************************************************
 * IsCorrectDateFormat
 *****************************************************************************/

bool isCorrectDateFormat(int m, int d, int y) {

	int ii = 0;		// incremented by 1 for each positive validation
	int febdays;	// used for number of days depending on year

	/* Checking month '''''''''''''''''''''''''''''''''''''''''''''''''''''' */
	if(m > 0 && m < 13)
		ii++;
	else
		printf("\nInvalid value for month!\n");

	/* Checking day depending on month ''''''''''''''''''''''''''''''''''''' */

	// Jan, Mar, May, Jul, Aug, Oct, Dec
	if(m==1|| m==3 || m==5 || m==7 || m==8 || m==10 || m==12) {
		if(d > 0 && d < 32)
			ii++;
		else
			printf("\nInvalid value for day!\n");
	}

	// Feb (validating leap years)

	if((isLeapYear(y)) == true)
		febdays = 29;
	else
		febdays = 28;

	if(m==2) {
		if(d > 0 && d < (febdays + 1))
			ii++;
		else
			printf("\nInvalid value for day!\n");
	}

	// Apr, Jun, Sep, Nov
	if(m==4|| m==6 || m==9 || m==11) {
		if(d > 0 && d < 31)
			ii++;
		else
			printf("\nInvalid value for day!\n");
	}

	/* Checking year ''''''''''''''''''''''''''''''''''''''''''''''''''''''' */
	if(y > 999 && y < 9999)								// to ensure 4 digits
		ii++;
	else
		printf("\nInvalid value for year!\n");

	/* Evaluating complete result '''''''''''''''''''''''''''''''''''''''''' */

	if(ii == 3)
		return true;
	else
		return false;

}

/******************************************************************************
 * IsLeapYear
 *****************************************************************************/

bool isLeapYear(const int iYear)
{
  // Each year that could be devided by 4 without rest is a leap year.
  // Exception: year could be devided by 100 without rest but not by 400.

  if ((iYear % 400) == 0)
    return true;
  else if ((iYear % 100) == 0)
    return false;
  else if ((iYear % 4) == 0)
    return true;

  return false;
}

/******************************************************************************
 * MAP TICKET ATTRIBUTES
 *****************************************************************************/

 /* Map some structure data first to some more human readable values for display on stdout.
	This is required since the input data for some ticket attributes differs from the output
	format. E.g. y => yes

	1: maps 	current.T_Runtime	=> display_runtime
	2: maps 	current.T_D_Day		=> display_weekday
	3: maps 	current.T_G77		=> display_G77
	4: maps 	current.T_SU6		=> display_SU6
	5: maps 	current.T_GSP		=> display_GSP

 */

 void map_t_attributes(int choice) {


	// range of allowed values
	char runtime_o1[2] = "1", runtime_o2[2] = "2", runtime_o3[2] = "3",
	runtime_o4[2] = "4", runtime_o5[2] = "5", runtime_o6[2] = "m", runtime_o7[2] = "p";
	char weekday_o1 [2] = "s", weekday_o2 [2] = "w", weekday_o3 [2] = "b";
	char T_G77_o1[2] = "y", T_G77_o2[2] = "n";
	char T_SU6_o1[2] = "y", T_SU6_o2[2] = "n";
	char T_GSP_o1[2] = "y", T_GSP_o2[2] = "n";

	 switch(choice) {

		 // Runtime
		 case 1:

			if(strcmp(current.T_Runtime, runtime_o1) == 0) strcpy(display_runtime, "1 week");
			else if(strcmp(current.T_Runtime, runtime_o2) == 0) strcpy(display_runtime, "2 weeks");
			else if(strcmp(current.T_Runtime, runtime_o3) == 0) strcpy(display_runtime, "3 weeks");
			else if(strcmp(current.T_Runtime, runtime_o4) == 0) strcpy(display_runtime, "4 weeks");
			else if(strcmp(current.T_Runtime, runtime_o5) == 0) strcpy(display_runtime, "5 weeks");
			else if(strcmp(current.T_Runtime, runtime_o6) == 0) strcpy(display_runtime, "month");
			else if(strcmp(current.T_Runtime, runtime_o7) == 0) strcpy(display_runtime, "permanent");
			else strcpy(display_runtime, "");

		 break;

		 // Weekday
		 case 2:
			if(strcmp(current.T_D_Day, weekday_o1) == 0) strcpy(display_weekday, "Sat");
			else if(strcmp(current.T_D_Day, weekday_o2) == 0) strcpy(display_weekday, "Wed");
			else if(strcmp(current.T_D_Day, weekday_o3) == 0) strcpy(display_weekday, "Wed + Sat");
			else strcpy(display_weekday, "");
		 break;

		 // Game 77
		 case 3:

			if(strcmp(current.T_G77, T_G77_o1) == 0) strcpy(display_G77, "yes");
			else if(strcmp(current.T_G77, T_G77_o2) == 0) strcpy(display_G77, "no");
			else strcpy(display_G77, "");

		 break;

		 // Super 6
		 case 4:

			if(strcmp(current.T_SU6, T_SU6_o1) == 0) strcpy(display_SU6, "yes");
			else if(strcmp(current.T_SU6, T_SU6_o2) == 0) strcpy(display_SU6, "no");
			else strcpy(display_SU6, "");

		 break;

		 // Glueckspirale
		 case 5:

			if(strcmp(current.T_GSP, T_GSP_o1) == 0) strcpy(display_GSP, "yes");
			else if(strcmp(current.T_GSP, T_GSP_o2) == 0) strcpy(display_GSP, "no");
			else strcpy(display_GSP, "");

		 break;

		 default: ;

	 }
 }


 /******************************************************************************
 * Display Ticket
 *****************************************************************************/
/* Displays ticket on terminal to confirm selection. This function can be used
for new tickets before writing ticket to file system or for existing tickets.
A loop for cofirming the selection is NOT part of the function itself. Note
that this function requires that the actual ticket data to display are already
expected to be in the current global ticket structure. */

void display_Ticket(void) {

	int i;

	char runtime_o1[2] = "1", runtime_o2[2] = "2", runtime_o3[2] = "3",
	runtime_o4[2] = "4", runtime_o5[2] = "5", runtime_o6[2] = "m", runtime_o7[2] = "p";
	char weekday_o1 [2] = "s", weekday_o2 [2] = "w", weekday_o3 [2] = "b";
	char T_G77_o1[2] = "y", T_G77_o2[2] = "n";
	char T_SU6_o1[2] = "y", T_SU6_o2[2] = "n";
	char T_GSP_o1[2] = "y", T_GSP_o2[2] = "n";

	/* Map some structure data first to some more human readable values for display on stdout */

	map_t_attributes(1);	// Runtime
	map_t_attributes(2);	// Weekday
	map_t_attributes(3);	// Game 77
	map_t_attributes(4);	// Super 6
	map_t_attributes(5);	// Glueckspirale

	// Display ticket -----------------------------------------

	printf("\n===============================================================================\n\n");
	printf("  Ticket No: %-11sPlayer: %-26s Active Rows: %-10d\n", current.T_No, current.T_Player, current.T_Max_Row);
	printf("  Date: %-16sTicket Runtime: %-19sWeekday: %-10s\n", current.T_Start, display_runtime, display_weekday);
	printf("  Game 77: %-13sSuper 6: %-26sGlueckspirale: %-10s\n", display_G77, display_SU6, display_GSP);
	printf("\n===============================================================================\n\n");

	for(i = 0; i < 12; i++) {

		printf("  Row %3d: %3d %3d %3d %3d %3d %3d\n",i+1, current.T_Row[i][0],current.T_Row[i][1],current.T_Row[i][2],current.T_Row[i][3],current.T_Row[i][4],current.T_Row[i][5]);
	}

	printf("\n===============================================================================\n\n");

}

 /******************************************************************************
 * IsCorrectLotteryRow
 ******************************************************************************
 checks for valid range and duplicates                                       */

bool isCorrectLotteryRow(int *LotteryNo) {

	int i, j; int v = 0; bool bDuplicate = false;

	// checks for duplicates
	for(i = 0; i < 6; i++) {
		for(j = 0; j < 6; j++) {
			if(i != j)
				if(LotteryNo[i] == LotteryNo[j])
					bDuplicate = true;
		}
	}


	// checks for valid range
	for(i = 0; i < 6; i++) {
		if(LotteryNo[i] > 0 &&  LotteryNo[i] < 50)
			v++;
	}

	if((v == 6) && (bDuplicate == false))
		return true;

	return false;
}

 /******************************************************************************
 * IsCorrectBonusNo
 ******************************************************************************
 prevent bonus number already exists as actual lottery number                */

 bool isCorrectBonusNo(int BN, int *LoNo) {

 	int i;
 	bool bDuplicate = false;
 	bool bValidRange = false;

 	// checks valid range ff
 	if(BN > 0 && BN < 50)
 		bValidRange = true;

 	// checks if BN already exists as acual lottery number

 	for(i = 0; i < 6; i++) {

		if(LoNo[i] == BN)
			bDuplicate = true;
	}

 	if((bValidRange == true) && (bDuplicate == false))
 		return true;

 	return false;
 }

 /******************************************************************************
 * Convert To Digit
 ******************************************************************************
 converts single char in range of '1' to '9' to number.                       */

 /* returns int value if in range '0'..'9' else returns -1 if not a number */

int convertToDigit( char c )
{
    if ( c < '0' || c > '9' ) return -1;
    return c - '0';
}

 /******************************************************************************
 * Get Lottery Win Class
 ******************************************************************************
 Function gets number of lottery matches and bonus or super number and
 returns lottery win class.                                                  */

 char *getWinClass(int matches, bool bonus_super ) {

     if(bonus_super == false) {

         switch(matches) {

             case 3: return "class VIII"; break;
             case 4: return "class VI"; break;
             case 5: return "class IV"; break;
             case 6: return "class II"; break;
             default: return "no win";
         }

     } else {

         switch(matches) {

             case 3: return "class VII"; break;
             case 4: return "class V"; break;
             case 5: return "class III"; break;
             case 6: return "class I"; break;
             default: return "no win";
         }
     }
}

