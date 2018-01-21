 /*t_evaluate.c | RLotto | gcc | v0.0.3.0
 * Console program for storing and evaluating lottery ticket resultt.
 * ----------------------------------------------------------------------------
 *
 * Objective:	Evaluate selected ticket based on corresponding draw results
 *
 * Author: 		Reinhard Rozumek
 * Email: 		reinhard@rozumek.de
 * Created: 	10/08/17
 * Last mod:	01/19/18
 *
 * ----------------------------------------------------------------------------
 * This file is part of RLotto.                                               */


 // HEADER SECTION

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "rlotto.h"
#include "version.h"


/* GLOABL VARIABLES ***********************************************************/

struct tm dd;			                            // date type used for d_rawing d_ate

/* FUCTION DECLARATION *******************************************************/

int enterInput(void);								            // enter drawing results
int checkLotto(void);								            // evaluate lottery result
int checkGame77(void);								            // evaluate Game 77 result
int checkSuper6(void);								            // evaluate Super 6 result
int checkGSP(void);									            // evaluate Glueckspirale result
int isCorrectDateFormat(int m, int d, int y);		            // validating date format
bool isValidDrawingDate(int dd_month, int dd_day, int dd_year); // validating date range
bool isCorrectLotteryRow(int *LotteryNo);			            // checks valid range & duplicates
bool isCorrectBonusNo(int BN, int *LoNo);			            // check if bonus number already exists
int convertToDigit( char c );						            // converts single char in range of '1' to '9' to number.
char *getWinClass(int matches, bool bonus_super );	            // returns win class based on lottery matches

 /*	*****************************************************************************
	EVALUATE TICKET
	*****************************************************************************/

/*  Enter actuals drawings results and evaluate against selected ticket. This
	function create the output/result file and calls all sub functions for ticket
	evaluation. */


	// FIXME: (camelo#1#01/20/18): Adjust for new rules - remove Bonus number adjust win classed by Superzahl
	// TODO: (camelo#2#01/03/18): Implement condition to evaluate only enabled options (e.g. G77)

int evaluateTicket(void) {

	int sConfirm;						        // yes or no to confirm user input
	char sPath[45];                             // Full pathname for result file
	char sPrefix[14] = "Lotto-Result-";         // File prefix
	char sPostfix[5] = ".txt";                  // File extension
	char sDrwDate[25];                          // Drawing Date formatted as part of filename

	printf("\n\nEnter actual drawing result.\n");

	// Call function to enter drawing results
	enterInput();

	// Final confirmation for starting evaluation
	printf("\nEvaluate results now? [y/n]: ");

	do {
		sConfirm = tolower(getchar());
	} while(sConfirm != 'y' && sConfirm != 'n');

	if(sConfirm == 'y') {

		// Create Filename
		strftime(sDrwDate, N, "%Y-%m-%d", &dd); strcpy(sPath, ResultFolder);
		strcat(sPath, sPrefix); strcat(sPath, sDrwDate); strcat(sPath, sPostfix);

		// Open result file for output
		pFile = fopen(sPath, "w");
		if(pFile == NULL) {
			printf("\nResult folder missing. Try to create now...\n");
			system("mkdir results");
			pFile = fopen(sPath, "w");
			if(pFile == NULL) {
				printf("Error opening %s for writing. Program terminated.", sPath);
				abort();
			} else {
				printf("Folder \"%s\" has been created.\n", ResultFolder);
			}
		}

		// Output to result file first part (header information)
		fprintf(pFile, "%s v%ld.%ld.%ld.%ld\n", THISPROG,MAJOR,MINOR,BUILD,REVISION);
		fprintf(pFile, "Evaluating lottery results\n");
		fprintf(pFile, "Lottery Ticket No: %s\n", current.T_No);

		fprintf(pFile, "\nPlayers: %s\n", current.T_Player);

		strftime(sDrwDate, N, "%A, %d-%b-%Y", &dd);

		fprintf(pFile, "\nDrawing Date: %s\n", sDrwDate);
		fprintf(pFile, "Lottery numbers: %i %i %i %i %i %i\n",ALN[0],ALN[1],ALN[2],ALN[3],ALN[4],ALN[5]);
		fprintf(pFile, "Bonus number: %i\n", ABN);
		fprintf(pFile, "Super number: %i\n", ASN);
		fprintf(pFile, "Game 77: %s\n", cG77);
		fprintf(pFile, "Super 6: %s\n", cSU6);

		fprintf(pFile, "\nLottery Matches on %s\n\n", sDrwDate);

		// Evaluate results
		checkLotto(); checkGame77(); checkSuper6();
		printf("\nWithout any warranty.\n");

		// Final output for result file
		fprintf(pFile, "\nWithout any warranty.\n");

		 // Close result file
		fclose(pFile);
		printf("\nResults written to %s.\n", sPath);

	}

	return 0;
}


/******************************************************************************
 * Enter Input
 *****************************************************************************/

int enterInput() {

 	// Actual Play Date (drawing date) ''''''''''''''''''''''''''''''''''''''''

    int year, month, day;		    // year, month, day as enterd by user
    bool is_ok = false;             //
    bool date_format_ok = false;    // correctness of drawing date format
    bool date_range_ok = false;     // validity of drawing date related to ticket
    char sPlayDate[40];			    // Actual Drawing Date
    int i;						    // Actual Lottery Number Index
    bool first_input = true;	    // indicates first attempt for input
    char sDrwDate[N];			    // Drawing date formated


    while(date_format_ok == false || date_range_ok == false)
    {

    	if(first_input == true)
    		printf("\nEnter drawing date (mm/dd/yyyy): ");
    	else
    		printf("Invalid input for drawing date! Please correct: ");
    	scanf("%d/%d/%d", &month, &day, &year);
    	fflush(stdin);

    	dd.tm_year = year - 1900;
        dd.tm_mon  = month - 1;
        dd.tm_mday = day;

        dd.tm_hour = 0;
        dd.tm_min  = 0;
        dd.tm_sec  = 1;
        dd.tm_isdst = -1;       // Change for Summer Time !?

        if (mktime(&dd) == -1 )
          dd.tm_wday = 7;

        strftime(sPlayDate, 40, "%A, %d-%b-%Y", &dd);

    	date_format_ok = isCorrectDateFormat(month, day, year);
    	date_range_ok = isValidDrawingDate(month, day, year);



    	first_input = false;

    	// printf("DEBUG: date_format_ok = %d | date_range_ok = %d\n", date_format_ok, date_range_ok);

    }


    first_input = true;	// reset to true for next evaluation

 	// Actual Lottery Numbers '''''''''''''''''''''''''''''''''''''''''''''''''

 	do {
    	// Initialize ALN
    	for(i = 0; i < 6; ++i) {
            ALN[i] = 0;
    	}


 		if(first_input == true)
 			printf("Enter actual lottory numbers seperated by commas: ");
 		else
 			printf("Invalid input! /Lottery Numbers) Please correct: ");
 		scanf("%i,%i,%i,%i,%i,%i", &ALN[0], &ALN[1], &ALN[2], &ALN[3], &ALN[4], &ALN[5]);
 		fflush(stdin);
 		is_ok = (isCorrectLotteryRow(ALN));
 		first_input = false;

 	} while(is_ok == false);

 	first_input = true;	// reset to true for next evaluation

 	// Actual Lottery Bonus Number ''''''''''''''''''''''''''''''''''''''''''''

 	do {
 		if(first_input == true)
 			printf("Enter actual bonus number: ");
 		else
 			printf("Invalid input! Please correct: ");
 		scanf("%i", &ABN);
 		fflush(stdin);
 		first_input = false;

 	} while((isCorrectBonusNo(ABN, ALN)) == false);

 	first_input = true;	// reset to true for next evaluation

 	// Actual Lottery Super Number ''''''''''''''''''''''''''''''''''''''''''''

 	do {
 		if(first_input == true)
 			printf("Enter actual super number: ");
 		else
 			printf("Invalid input! Please correct: ");
 		scanf("%i", &ASN);
 		fflush(stdin);
 		first_input = false;

 	} while(ASN < 0 || ASN > 9);

 	first_input = true;	// reset to true for next evaluation

 	// Actual Game 77 '''''''''''''''''''''''''''''''''''''''''''''''''''''''''

 	do {
 		if(first_input == true)
 			printf("Enter actual Game 77 number: ");
 		else
 			printf("Invalid input! Please correct: ");
 		scanf("%7[0123456789]", cG77);
 		fflush(stdin);
 		first_input = false;

 	} while((strlen(cG77)) < 7);

 	first_input = true;	// reset to true for next evaluation

 	// Actual Super 6 '''''''''''''''''''''''''''''''''''''''''''''''''''''''''

 	do {
 		if(first_input == true)
 			printf("Enter actual Super 6 number: ");
 		else
 			printf("Invalid input! Please correct: ");
 		scanf("%6[0123456789]", cSU6);
 		fflush(stdin);
 		first_input = false;

 	} while((strlen(cSU6)) < 6);

 	first_input = true;	// reset to true for next evaluation

 	// Actual Glueckspirale '''''''''''''''''''''''''''''''''''''''''''''''''''




 	// Console Output

    strftime(sDrwDate, N, "%A, %d-%b-%Y", &dd);

    printf("\nCheck your input:\n");
    printf("\nDrawing Date: %s\n", sDrwDate);
 	printf("Actual lottery numbers: %i %i %i %i %i %i\n",ALN[0],ALN[1],ALN[2],ALN[3],ALN[4],ALN[5]);
 	printf("Actual bonus number: %i\n", ABN);
 	printf("Actual super number: %i\n", ASN);
 	printf("Actual Game 77: %s\n", cG77);
 	printf("Actual Super 6: %s\n", cSU6);

 	return 0;

}

/******************************************************************************
 * check Lotto
 ******************************************************************************

 Evaluates actual lottery numbers against lottery ticket
 in order to determine matches and win classes                               */



 int checkLotto() {

 	int RowNo, i, j;							// row number, indizees
 	int MPR[NOLR];								// matches per lottery row
 	int WinRows = 0;                            // number of lottery rows with win
 	bool CBN[NOLR];                             // correct bonus number
 	bool CSN[NOLR];                             // correct super number
 	char sDrwDate[N];			                // Drawing date formated
 	int iNOLR = NOLR;                           // Number of lottery rows (hard coded)
 	char WinMsg[12];                            // literal to show win class for ouput

 	// Initialize MPR, CBN and CSN
 	for(i = 0; i < NOLR; i++) {
        MPR[i] = 0; CBN[i] = false; CSN[i] = false;
 	}

// check for matches with actual lottery numbers ''''''''''''''''''''''''''''''

    for(RowNo = 0;RowNo < NOLR; RowNo++)
        for(i = 0; i < 6; i++)
            for(j = 0; j < 6; j++)
                if(current.T_Row[RowNo][i] == ALN[j])
                    MPR[RowNo]++ ;

    // check for correct Super and Bonus Number '''''''''''''''''''''''''''''''

    for(RowNo = 0; RowNo < NOLR; RowNo++) {

        // check for correct Super Number
        if(MPR[RowNo] > 2) {
            WinRows++;
            if(MPR[RowNo] > 5) {
                if(ASN == convertToDigit(current.T_No[6]))
                    CSN[RowNo] = true;
            } else {
                    for(i = 0; i < 6; i++)
                        if(current.T_Row[RowNo][i] == ABN)
                            CBN[RowNo] = true;

                    }
        }
    }

    // Generate output ''''''''''''''''''''''''''''''''''''''''''''''''''''''''

    // Console Output

    strftime(sDrwDate, N, "%A, %d-%b-%Y", &dd);
    printf("\nLottery Matches on %s\n\n", sDrwDate);

    for(RowNo = 0; RowNo < NOLR; RowNo++) {

        if(MPR[RowNo] < 6)
            strcpy(WinMsg, getWinClass(MPR[RowNo], CBN[RowNo]));
        else
            strcpy(WinMsg, getWinClass(MPR[RowNo], CSN[RowNo]));

        switch(MPR[RowNo]) {
            case 0: {   printf("Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / no match)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg);
                        fprintf(pFile, "Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / no match)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg);
                    }
                    break;
            case 1: {   printf("Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / %i match)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg,MPR[RowNo]);
                        fprintf(pFile, "Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / %i match)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg,MPR[RowNo]);
                    }
                    break;
            case 2: {   printf("Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / %i matches)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg,MPR[RowNo]);
                        fprintf(pFile, "Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / %i matches)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg,MPR[RowNo]);
                    }
                    break;
            case 6: {   if(CSN[RowNo] == true) {
                            printf("Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / %i matches + correct super number)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg,MPR[RowNo]);
                            fprintf(pFile, "Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / %i matches + correct super number)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg,MPR[RowNo]);
                        } else {
                            printf("Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / %i matches)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg,MPR[RowNo]);
                            fprintf(pFile, "Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / %i matches)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg,MPR[RowNo]);
                        }
                    }
                    break;
            default: {  if(CBN[RowNo] == true) {
                            printf("Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / %i matches + correct bonus number)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg,MPR[RowNo]);
                            fprintf(pFile, "Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / %i matches + correct bonus number)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg,MPR[RowNo]);
                        } else {
                            printf("Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / %i Matches)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg,MPR[RowNo]);
                            fprintf(pFile, "Row No %2i: %2i %2i %2i %2i %2i %2i\t(%s / %i Matches)\n",RowNo + 1,current.T_Row[RowNo][0], current.T_Row[RowNo][1],current.T_Row[RowNo][2],current.T_Row[RowNo][3],current.T_Row[RowNo][4],current.T_Row[RowNo][5],WinMsg,MPR[RowNo]);
                        }
                    }
        }

    }

    switch(WinRows) {

        // FIXME (camelo#3#01/20/18): %row in total not matching count of rows actually played - Needs to be corrected.

        case 0: {
            printf("\nThere is no win for any of %i rows played in total.\n",iNOLR);
            fprintf(pFile, "\nThere is no win for any of %i rows played in total.\n",iNOLR);
            break;
        }
        case 1: {
            printf("\nThere is %i row with win of %i rows played in total.\n",WinRows,iNOLR);
            fprintf(pFile, "\nThere is %i row with win of %i rows played in total.\n",WinRows,iNOLR);
            break;
        }
        default: {
            printf("\nThere are %i rows with wins of %i rows played in total.\n",WinRows,iNOLR);
            fprintf(pFile, "\nThere are %i rows with wins of %i rows played in total.\n",WinRows,iNOLR);
        }
    }

    // File Output
    // printf("\nPlayers: %s\n", &current.T_Player);
    // printf("%i %i %i %i %i %i\n");

 	return 0;
}

/******************************************************************************
 * check Game 77
 ******************************************************************************

 Evaluates actual lottery numbers against lottery ticket
 in order to determine matches and win classes                               */

 int checkGame77() {

 	int ii;									    // index of ticket number array
 	int MatchG77 = 0;							// matches Game 77
 	char WinClassG77[4];                        // Game 77 win class

    for(ii = 6; ii >= 0; ii--) {
        if(current.T_No[ii] == cG77[ii])
            MatchG77++;
        else
            break;
    }

    if(MatchG77 > 0) {
        switch(MatchG77) {

            case 1: strcpy(WinClassG77, "VII"); break;
            case 2: strcpy(WinClassG77, "VI"); break;
            case 3: strcpy(WinClassG77, "V"); break;
            case 4: strcpy(WinClassG77, "IV"); break;
            case 5: strcpy(WinClassG77, "III"); break;
            case 6: strcpy(WinClassG77, "II"); break;
            case 7: strcpy(WinClassG77, "I"); break;
            default: strcpy(WinClassG77, "---");
        }

        if(MatchG77 == 1) {
            printf("You have won Game 77 according winning class %s (%i digit matching).\n",WinClassG77,MatchG77);
            fprintf(pFile, "You have won Game 77 according winning class %s (%i digit matching).\n",WinClassG77,MatchG77);
        }

        if(MatchG77 > 1) {
            printf("You have won Game 77 according winning class %s (%i digits matching).\n",WinClassG77,MatchG77);
            fprintf(pFile, "You have won Game 77 according winning class %s (%i digits matching).\n",WinClassG77,MatchG77);
        }

    } else {
        printf("There is no win for Game 77.\n");
        fprintf(pFile, "There is no win for Game 77.\n");

    }

 	return 0;
}

/******************************************************************************
 * check Super 6
 ******************************************************************************

 Evaluates actual lottery numbers against lottery ticket
 in order to determine matches and win classes                               */

 int checkSuper6() {


 	int ii;									    // index of ticket number array
 	int MatchSU6 = 0;							// matches Super 6
 	char WinClassSU6[4];                        // Game 77 win class

    for(ii = 6; ii >= 0; ii--) {
        if(current.T_No[ii] == cSU6[ii -1])
            MatchSU6++;
        else
            break;
    }

    if(MatchSU6 > 0) {
        switch(MatchSU6) {

            case 1: strcpy(WinClassSU6, "VI"); break;
            case 2: strcpy(WinClassSU6, "V"); break;
            case 3: strcpy(WinClassSU6, "IV"); break;
            case 4: strcpy(WinClassSU6, "III"); break;
            case 5: strcpy(WinClassSU6, "II"); break;
            case 6: strcpy(WinClassSU6, "I"); break;
            default: strcpy(WinClassSU6, "---");
        }


        if(MatchSU6 == 1) {
            printf("You have won Super 6 according winning class %s (%i digit matching).\n",WinClassSU6,MatchSU6);
            fprintf(pFile, "You have won Super 6 according winning class %s (%i digit matching).\n",WinClassSU6,MatchSU6);
        }

        if(MatchSU6 > 1) {
            printf("You have won Super 6 according winning class %s (%i digits matching).\n",WinClassSU6,MatchSU6);
            fprintf(pFile, "You have won Super 6 according winning class %s (%i digits matching).\n",WinClassSU6,MatchSU6);

        }

    } else {
        printf("There is no win for Super 6.\n");
        fprintf(pFile, "There is no win for Super 6.\n");

    }

 	return 0;
}

/******************************************************************************
 * check GLUCKSPIRALE
 ******************************************************************************

 Evaluates ticket against actual result for 'Glueckspirale'. */

 // TODO (camelo#1#01/03/18): Implement evaluation for Glueckspirale

 int checkGSP() {


	 return 0;
 }
