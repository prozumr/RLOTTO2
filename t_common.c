 /*t_common.c | RLotto | gcc | v0.8.355.1720
 * Console program for storing and evaluating lottery ticket results.
 * ----------------------------------------------------------------------------
 *
 * Objective:	Common functions used in various parts of this program.
 *
 * Author: 		Reinhard Rozumek
 * Email: 		reinhard@rozumek.de
 * Created: 	11/17/17
 * Last mod:	03/26/18
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

/* GLOABL VARIABLES ***********************************************************/

struct tm dd;			                            // date type used for d_rawing d_ate


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
 Function gets number of lottery matches per row and result from check of super
 super number per ticket. The fuction returns the lottery win class.          */

 char *getWinClass(int matches, bool super ) {

     if(super == false) {

         switch(matches) {
			 
			 case 0: return "no win"; break;
			 case 1: return "no win"; break;
			 case 2: return "no win"; break;
             case 3: return "class VIII"; break;
             case 4: return "class VI"; break;
             case 5: return "class IV"; break;
             case 6: return "class II"; break;
             default: return "no win";
         }

     } else {

         switch(matches) {

             case 0: return "no win"; break;
			 case 1: return "no win"; break;
			 case 2: return "class IX"; break;
             case 3: return "class VII"; break;
             case 4: return "class V"; break;
             case 5: return "class III"; break;
             case 6: return "class I"; break;
             default: return "no win";
         }
     }
}


 /******************************************************************************
 * IsValidDrawingDate
 ******************************************************************************
 Check for ticket validity against drawing date. Gets Drawing Date and returns
 true or false by checking Ticket Start Date, Ticket Runtime and Ticket day of
 week - all stored in the global ticket structure. In order to accomplish this,
 the functions first needs to calculate the ticket end date. */

bool isValidDrawingDate(int dd_month, int dd_day, int dd_year) {

    bool result;                    // true if w_day_OK AND period_OK true. Otherwise false.
    bool w_day_OK;                  // true if drawing day of the week matches with ticket. Otherwise false.
    bool period_OK;                 // true if with ticket validity period. Otherwise false.
    struct tm add;                  // date type used for a_ctual d_rawing d_ate
    struct tm tsd;                  // date type used for t_icket s_tart d_ate
    struct tm ted;                  // date type used for t_icket e_nd d_ate
    int ts_day, ts_month, ts_year;  // representing year, month, day from ticket start date as integer values
    char *str_day;                  // Token of Ticket start date for day
    char *str_month;                // Token of Ticket start date for month
    char *str_year;                 // Token of Ticket start date for year
    char str_runtime;               // runtime range: 1,2,3,4,5,m_onth, p_ermanent
    /* char str_d_day;              drawing day range: s_saturday, w_ednesday or b_oth*/
    double diff_seconds1;           // time difference in seconds
    double diff_seconds2;           // time difference in seconds
    int dw_day;                     // drawing weekday (0,1,2,3,4,5,6)
    char tw_day;                    // ticket week day (s, w or b)
	char sbuffer[11];				// buffer to hold string for T_Start date

    result = false;


    // build actual drawing date structure ------------------------------------

    add.tm_year = dd_year - 1900;
    add.tm_mon  = dd_month - 1;
    add.tm_mday = dd_day;

    add.tm_hour = 0;
    add.tm_min  = 0;
    add.tm_sec  = 1;
    add.tm_isdst = -1;       // Change for Summer Time !?

    if (mktime(&add) == -1 )
        add.tm_wday = 7;

    // build ticket start date structure --------------------------------------

	str_runtime = current.T_Runtime[0];
	strcpy(sbuffer, current.T_Start);

    str_day = strtok(sbuffer, ".");
    str_month = strtok(NULL, ".");
    str_year = strtok(NULL, ".");

	// calculating ticket start date in case ticket runtime is 'month'
	if(str_runtime == 'm'){

		ts_day = 1;

		if(atoi(str_month) == 12){
			ts_month = 1;
			ts_year = atoi(str_year) + 1;
		} else {
			
			ts_month = atoi(str_month) +1;
			ts_year = atoi(str_year);
		}

	// calculating ticket start date in case ticket runtime is not 'month'
	} else {

		ts_day = atoi(str_day);
		ts_month = atoi(str_month);
		ts_year = atoi(str_year);
	}

    tsd.tm_year = ts_year - 1900;
    tsd.tm_mon  = ts_month - 1;
	tsd.tm_mday = ts_day;

    tsd.tm_hour = 0;
    tsd.tm_min  = 0;
    tsd.tm_sec  = 1;
    tsd.tm_isdst = -1;       // Change for Summer Time !?

    if (mktime(&tsd) == -1 )
        tsd.tm_wday = 7;

    // build ticket end date structure ----------------------------------------

	ted.tm_year = ts_year - 1900;
	ted.tm_mon  = ts_month - 1;
	ted.tm_mday = ts_day;

	ted.tm_hour = 0;
	ted.tm_min  = 0;
	ted.tm_sec  = 1;
	ted.tm_isdst = -1;       // Change for Summer Time !?

	switch (str_runtime) {

		case '1': ted.tm_mday +=7; mktime(&ted); break;     			// 1 week = 7 days
		case '2': ted.tm_mday +=14; mktime(&ted); break;    			// 2 weeks = 14 days
		case '3': ted.tm_mday +=21; mktime(&ted); break;    			// 3 weeks = 21 days
		case '4': ted.tm_mday +=28; mktime(&ted); break;    			// 4 weeks = 28 days
		case '5': ted.tm_mday +=35; mktime(&ted); break;    			// 5 weeks = 35 days
		case 'm': ted.tm_mon +=1; ted.tm_mday -=1; mktime(&ted); break;	// 1st until last day of next month
		case 'p': ted.tm_year +=25; mktime(&ted); break;    			// permanent = 25 years
		default: break;
	}

    // Check validity ---------------------------------------------------------
    // Condition 1: weekday 0=Sun, 1=Mon, 2=Tue, 3=Wed, 4=Thu, 5=Fri, 6=Sat
    // Condition 2: Ticket end date is greater or equals actual drawing date
    // Condition 3: Actual drawing date is grater or equals ticket start date
    // Ticket has been validated against drawing date once all conditions above are evaluated true

    diff_seconds1 = difftime(mktime(&add), mktime(&tsd));       // difference between actual drawing date and ticket start date 
    diff_seconds2 = difftime(mktime(&ted), mktime(&add));       // difference between ticket end date and actual drawing date

    dw_day = add.tm_wday;                                       // day of the week for actual drawing date from console input
    tw_day = current.T_D_Day[0];                                // day of the week read from ticket (w, s or b)

    // Check for correct weekday (condition 1)

    w_day_OK = false;
    period_OK = false;


    switch (tw_day) {

        case 's':

            if(dw_day == 6) w_day_OK = true;
            else printf("\nDrawing date is not a Saturday. Please enter correct drawing date.\n");
            break;

        case 'w':

            if(dw_day == 3) w_day_OK = true;
            else printf("\nDrawing date is not a Wednesday. Please enter correct drawing date.\n");
            break;

        case 'b':

            if(dw_day == 3 || dw_day == 6) w_day_OK = true;
            else printf("\nDrawing date is neither Wednesday nor Saturday. Please enter correct drawing date.\n");
            break;

        default:

            printf("\nDay of Week from ticket not available. \n");
            break;
    }



    // Check for correct validity period (condition 2 & 3)

    if((diff_seconds1 >= 0) && (diff_seconds2 >= 0)) period_OK = true;
    else printf("\nActual drawing date not in rage of valid ticket period. Please enter correct drawing date.\n");

    // Total result for check of validity

    if(w_day_OK == true && period_OK == true) result = true;
    else result = 0;
    
    /*printf("DEBUG add: %s\n", asctime(&add));
    printf("DEBUG tsd: %s\n", asctime(&tsd));
    printf("DEBUG ted: %s\n", asctime(&ted));
    printf("DEBUG diff_seconds1: %f\n", diff_seconds1);
    printf("DEBUG diff_seconds2: %f\n", diff_seconds2);
    printf("DEBUG dw_day: %d\n", dw_day);
    printf("DEBUG tw_day: %c\n", tw_day);*/  

    return result;

}
