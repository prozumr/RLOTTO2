 /*t_add.c | RLotto | gcc | v0.0.3.0
 * Console program for storing and evaluating lottery ticket results.
 * ----------------------------------------------------------------------------
 *
 * Objective:	Create and store new ticket as ASCII file to file system.
 *
 * Author: 		Reinhard Rozumek
 * Email: 		reinhard@rozumek.de
 * Created: 	10/08/17
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

int t_initialize(void);
void get_ticket_No(void);
void get_Player_Name(void);
void get_Start_Date(void);
void get_T_Runtime(void);
void get_T_D_Day(void);
void get_T_G77(void); 
void get_T_SU6(void);
void get_T_GSP(void);
void get_T_Rows(void);
void display_Ticket(void);
void write_Ticket(void);
void map_t_attributes(int choice);
bool isCorrectTicketNo(char *n);
bool isCorrectDateFormat(int m, int d, int y);
bool isLeapYear(const int iYear);


// GLOBAL VARIABLES

struct tm ts;											// standard date type

 
/******************************************************************************
 * ADD TICKET - CALL INPUT SUBMENUS
 *****************************************************************************/
 
int addTicket(void) {
	
	bool is_ok = false;
	bool first_input = true;	
	bool confirm_ticket = true;
	char sConfirm[2], sWrite[2];
	
	// CONFIRM TO CREATE NEW TICKET
	do {
		
		if(first_input == true)
    		printf("\n\nAdd new lottery ticket? (y/n): ");
    	else
    		printf("Invalid input! Please correct: ");	   
    	scanf("%s", &sConfirm);
    	fflush(stdin);
		
		if(*sConfirm=='y' || *sConfirm=='n') {
			is_ok = true;
		}
		
		first_input = false;
		
	} while(is_ok == false);
	
	// INPUT SUBMENUS - EACH INPUT QUERY ENCAPSULATED IN ITS OWN FUNCTION
	if(*sConfirm=='y') {
		
		t_initialize();
		get_ticket_No();
		get_Player_Name();
		get_Start_Date();
		get_T_Runtime();
		get_T_D_Day();
		get_T_G77();
		get_T_SU6();
		get_T_GSP();
		get_T_Rows();
		display_Ticket();
		
		// CONFIRM TO WRITE TICKET
		is_ok = false;
		first_input = true;
		
		do {
		
			if(first_input == true)
				printf("\nWrite ticket to file sytem? (y/n): ");
			else
				printf("Invalid input! Please correct: ");	   
			scanf("%s", &sWrite);
			fflush(stdin);
			
			if(*sWrite=='y' || *sWrite=='n') {
				is_ok = true;
			}
			
			first_input = false;
		
		} while(is_ok == false);
	
		// WRITE TICKET TO FILE SYSTEM
		if(*sWrite=='y') {
			
			write_Ticket();
			
		} else {
			
			printf("\nCreation of new ticket canceled.\n");
		}
		
	} else {
		
		printf("\nCreation of new ticket canceled.\n");
	}
	
}
	
/******************************************************************************
 * GET TICKET NUMBER
 *****************************************************************************/
 
 /*  Gets Ticket Number by user input from stdin. */
 	
 
 void get_ticket_No(void) {
	
	 bool is_ok = false;			// correctness of input format
	 bool confirm = false;			// User confirms entered input
	 bool first_input = true;		// indicates first attempt for input
	 char ticket_No[8];				// Ticket No to return to calling function
	 
	 do
    {
    	if(first_input == true)
    		printf("Enter 7-digit Ticket Number: ");
    	else
    		printf("Invalid input! Please correct: ");	   
    	scanf("%8s", &ticket_No);							//Input limited to 7 characters
    	fflush(stdin);
    	is_ok = (isCorrectTicketNo(ticket_No));
    	first_input = false;
    	 
    } while(is_ok == false);
	
	/* Remove trailing newline, if there and add 0 terminator. */
    if ((strlen(ticket_No)>0) && (ticket_No[strlen (ticket_No) - 1] == '\n'))
		ticket_No[strlen (ticket_No) - 1] = '\0';
	
	strcpy(current.T_No , ticket_No);						// Assign ticket number to structure
	
 }
 
 /******************************************************************************
 * GET PLAYER NAME(S) 
 *****************************************************************************/
 
 /*  Gets Player Name by user input from stdin. */
 
 void get_Player_Name(void) {
	
	char cPlayers[MAX_T_PLAYER_SZ];
	
	printf("Enter Player Name: ");
	fgets (cPlayers, MAX_T_PLAYER_SZ, stdin);
	
	/* Remove trailing newline, if there and add 0 terminator. */
    if ((strlen(cPlayers)>0) && (cPlayers[strlen (cPlayers) - 1] == '\n'))
		cPlayers[strlen (cPlayers) - 1] = '\0';
	
	strcpy(current.T_Player, cPlayers);					// Assign ticket number to structure
	
 }
 
 /******************************************************************************
 * GET TICKET START DATE
 ******************************************************************************/
 
/*  Gets Date of purchase by user input from stdin. */
 
 void get_Start_Date(void) {
	 
	

    int year, month, day;		// year, month, day as enterd by user
    bool is_ok = false;			// correctness of date format
    char sPlayDate[11];			// Actual Drawing Date
    int i;						// Actual Lottery Number Index 
    bool first_input = true;	// indicates first attempt for input
    
    do
    {
    	if(first_input == true)
    		printf("Enter playing date (mm/dd/yyyy): ");
    	else
    		printf("Invalid input! Please correct: ");	   
    	scanf("%d/%d/%d", &month, &day, &year);
    	fflush(stdin);
    	is_ok = (isCorrectDateFormat(month, day, year));
    	first_input = false;
    	
    } while(is_ok == false);

    ts.tm_year = year - 1900;
    ts.tm_mon  = month - 1;
    ts.tm_mday = day;

    ts.tm_hour = 0;
    ts.tm_min  = 0;
    ts.tm_sec  = 1;
    ts.tm_isdst = -1;

    if ( mktime(&ts) == -1 )
      ts.tm_wday = 7;
	
	// strftime(sPlayDate, 40, "%A, %d-%B-%Y", &ts); <---- 
	
	strftime(sPlayDate, 11, "%d.%m.%Y", &ts);
	
	
	strcpy(current.T_Start , sPlayDate);						// Assign ticket Start Date to structure

    is_ok = false;		// reset to false for next evaluation
    first_input = true;	// reset to true for next evaluation
	 
 }
 
 /******************************************************************************
 * GET TICKET RUNTIME
 ******************************************************************************/
 
 /* Gets ticket runtime in weeks by user input from stdin.
	Allowed ranged is 1-5 (weeks),'m' (month) or 'p' (permanent) */
 
 
 void get_T_Runtime(void) {
	 
	char rt[2];					// Ticket runtimet in weeks . 
    bool is_ok = false;			// correctness of date format
    bool first_input = true;	// indicates first attempt for input
	
	do
    {
    	if(first_input == true)
    		printf("Enter ticket runtime (1-5,m,p): ");
    	else
    		printf("Invalid input! Please correct: ");	   
    	scanf("%s", &rt);
    	fflush(stdin);
		if(*rt=='1' || *rt=='2' || *rt=='3' || *rt=='4' || *rt=='5' || *rt=='m' || *rt=='p' ) {
			
			is_ok = true;
			
			/* Remove trailing newline, if there and add 0 terminator. */
			if ((strlen(rt)>0) && (rt[strlen (rt) - 1] == '\n'))
				rt[strlen (rt) - 1] = '\0';
			
			strcpy(current.T_Runtime, rt);						// Assign ticket runtime to structure
		}
		
    	first_input = false;
    	
    } while(is_ok == false);
 }

/******************************************************************************
 * GET TICKET DRAWING DATE OF THE WEEK
 ******************************************************************************/
 
 /* Gets ticket drawing day of the week by user input from stdin.
	Allowed ranged is s (Saturday), w (Wednesday) or b (Both - Saturday and 
	Wednesday) */ 
	
void get_T_D_Day(void){
	
	char T_D_Day[2];			// Ticket runtimet in weeks . 
    bool is_ok = false;			// correctness of date format
    bool first_input = true;	// indicates first attempt for input
	
	do
    {
    	if(first_input == true)
    		printf("Enter ticket drawing day (s,w,b): ");
    	else
    		printf("Invalid input! Please correct: ");	   
    	scanf("%s", &T_D_Day);
    	fflush(stdin);
		if(*T_D_Day=='s' || *T_D_Day=='w' || *T_D_Day=='b') {
			
			is_ok = true;
			
			/* Remove trailing newline, if there and add 0 terminator. */
			if ((strlen(T_D_Day)>0) && (T_D_Day[strlen (T_D_Day) - 1] == '\n'))
				T_D_Day[strlen (T_D_Day) - 1] = '\0';
			
			strcpy(current.T_D_Day, T_D_Day);					// Assign ticket drawing day to structure
		}
		
    	first_input = false;
    	
    } while(is_ok == false);
}
 
/******************************************************************************
 * GET GAME 77 
 ******************************************************************************/
 
 /* Gets info by user if ticket is enabled for "Game 77" (German "Spiel 77").
	Allowed ranged is y (yes) or n (no) */ 

void get_T_G77(void){
	
	char T_G77[2];				// Indicates if Game 77 is active (y/n). 
    bool is_ok = false;			// Indicates correctness of date format
    bool first_input = true;	// indicates first attempt for input
	
	do
    {
    	if(first_input == true)
    		printf("Enter if Game 77 is active (y,n): ");
    	else
    		printf("Invalid input! Please correct: ");	   
    	scanf("%s", &T_G77);
    	fflush(stdin);
		if(*T_G77=='y' || *T_G77=='n') {
			
			is_ok = true;
			
			/* Remove trailing newline, if there and add 0 terminator. */
			if ((strlen(T_G77)>0) && (T_G77[strlen (T_G77) - 1] == '\n'))
				T_G77[strlen (T_G77) - 1] = '\0';
			
			strcpy(current.T_G77, T_G77);						// Assign Game 77 (yes or no) to structure
		}
		
    	first_input = false;
    	
    } while(is_ok == false);	
}
	
/******************************************************************************
 * GET SUPER 6
 ******************************************************************************/
 
/* Gets info by user if ticket is enabled for "Super 6".
	Allowed ranged is y (yes) or n (no) */ 

void get_T_SU6(void){
	
	char T_SU6[2];				// Indicates if Super 6 is active (y/n).  
    bool is_ok = false;			// Indicates correctness of user input
    bool first_input = true;	// indicates first attempt for input
	
	do
    {
    	if(first_input == true)
    		printf("Enter if Super 6 is active (y,n): ");
    	else
    		printf("Invalid input! Please correct: ");	   
    	scanf("%s", &T_SU6);
    	fflush(stdin);
		if(*T_SU6=='y' || *T_SU6=='n') {
			
			is_ok = true;
			
			/* Remove trailing newline, if there and add 0 terminator. */
			if ((strlen(T_SU6)>0) && (T_SU6[strlen (T_SU6) - 1] == '\n'))
				T_SU6[strlen (T_SU6) - 1] = '\0';
			
			strcpy(current.T_SU6, T_SU6);						// Assign Super 6 (yes or no) to structure
		}
		
    	first_input = false;
    	
    } while(is_ok == false);
}	
	
/******************************************************************************
 * GET GLUECKSPIRALE
 ******************************************************************************/
 
/* Gets info by user if ticket is enabled for "Glueckspirale".
	Allowed ranged is y (yes) or n (no) */ 	

void get_T_GSP(void){
	
	char T_GSP[2];				// Indicates if Glueckspirale is active (y/n).  
    bool is_ok = false;			// Indicates correctness of user input
    bool first_input = true;	// indicates first attempt for input
	
	do
    {
    	if(first_input == true)
    		printf("Enter if Glueckspirale is active (y,n): ");
    	else
    		printf("Invalid input! Please correct: ");	   
    	scanf("%s", &T_GSP);
    	fflush(stdin);
		if(*T_GSP=='y' || *T_GSP=='n') {
			
			is_ok = true;
			
			/* Remove trailing newline, if there and add 0 terminator. */
			if ((strlen(T_GSP)>0) && (T_GSP[strlen (T_GSP) - 1] == '\n'))
				T_GSP[strlen (T_GSP) - 1] = '\0';
			
			strcpy(current.T_GSP, T_GSP);						// Assign Glueckspirale (yes or no) to structure
		}
		
    	first_input = false;
    	
    } while(is_ok == false);
	
}
	
/******************************************************************************
 * GET LOTTERY NUMBERS
 ******************************************************************************/
 
/* Get lottery numbers per row. 12 rows defined. Range of number is 1-49.*/ 
	
void get_T_Rows(void){
	
	int T_Row[12] [6];			// Lottery numbers with row.
	int T_Max_Row;				// Max number of rows used in this ticket
	int i, j;					// Loop counter
	int checksum;				// Checksum to validate numbers are in range of 1-49
	int countInput;				// Used as count for input arguments of scanf per iteration
	int n[12][6];				// Lottery number array
    bool is_ok = false;			// Indicates correctness of user input
    bool first_input = true;	// indicates first attempt for input
	
	// Query number of active rows (T_Max_Row)
	
	do
    {
    	if(first_input == true)
    		printf("Enter number of active rows (1-12): ");
    	else
    		printf("Invalid input! Please correct: ");	   
    	scanf("%d", &T_Max_Row);
    	fflush(stdin);
		if(T_Max_Row > 0 && T_Max_Row < 13) {
			
			is_ok = true;
			current.T_Max_Row = T_Max_Row;						// Assign Glueckspirale (yes or no) to structure
		}
		
    	first_input = false;
    	
    } while(is_ok == false);
	
	// Query Lottery Numbers (T_Row[][])
	
	is_ok = false;												// reset loop control variables
	first_input = true;											// reset loop control variables
	
	do
    {
		// Initialzing variables required to reset for each loop;
		checksum = 0;
		
		for(i = 0; i < 12; i++){
			for(j = 0; j < 6; j++){	
				n[j][j]=0;
			}
		}
		
		if(first_input == true)
			printf("Enter Lottery numbers per row separated by commas.\n");
    	else
    		printf("Invalid input! Please correct!\n\n");
	
		for(i = 0; i <= T_Max_Row - 1; i++) {
			
			countInput = 0;
			
			printf("Row %d: ", i + 1);
			countInput = scanf("%d,%d,%d,%d,%d,%d", &n[i][0],&n[i][1],&n[i][2],&n[i][3],&n[i][4],&n[i][5]);
			fflush(stdin);
			
			if(countInput == 6){
				
				// Checks range of each mumber in the row
				for(j = 0; j < 6; j++){
				
					if(n[i][j] > 0 && n[i][j] < 50){
						
						checksum++;
						current.T_Row[i][j] = n[i][j];
					}
				}
				
			}else {
				printf("\nInvalid number of arguments in input\n");
				checksum = 0;
				t_initialize();										//re-initialie to ensure structure is clean
				break;
			}
			
			if(countInput == 6 && checksum != (i+1) * 6){
				printf("\nInvalid value - All lottery numbers have to be in range from 1 to 49 \n");
				checksum = 0;
				t_initialize();										//re-initialie to ensure structure is clean
				break;
			}
		}
		
		if(checksum == 6 * T_Max_Row){
			is_ok = true;
		} 
			
		first_input = false;
    	
    } while(is_ok == false);
}
	
	
/******************************************************************************
 * WRITE INPUT TO TICKET FILE
 *****************************************************************************/

void write_Ticket(void){
	
	// construct filename
	char *t_filename;
	strcpy(t_filename, current.T_No);
	strcat(t_filename, T_EXT);
	
	
	// Open file and write
	FILE *fp;
	fp = fopen(t_filename, "w");
	
	if(fp == NULL) {
		
		printf("Error creating file!\n");
		
	} else {
		
		fprintf(fp, "Ticket No:%s\n", current.T_No);
		fprintf(fp, "Player:%s\n", current.T_Player);
		fprintf(fp, "Play Date:%s\n", current.T_Start);
		fprintf(fp, "Runtime:%s\n", current.T_Runtime);
		fprintf(fp, "Weekday:%s\n", current.T_D_Day);
		fprintf(fp, "Game 77:%s\n", current.T_G77);
		fprintf(fp, "Super 6:%s\n", current.T_SU6);
		fprintf(fp, "Glueckspirale:%s\n", current.T_GSP);
		fprintf(fp, "Active Rows:%d\n", current.T_Max_Row);
		
		for(int j = 0; j < 12; j++) {
			
			fprintf(fp, "Row %2d:%d,%d,%d,%d,%d,%d\n",j+1, current.T_Row[j][0],current.T_Row[j][1],current.T_Row[j][2],current.T_Row[j][3],current.T_Row[j][4],current.T_Row[j][5]);
		}
		
		fclose(fp);
		
		printf("\nTicket %s written.\n", t_filename);
	}

}


