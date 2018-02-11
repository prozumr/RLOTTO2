 /*t_select.c | RLotto | gcc | v0.8.353.1712
 * Console program for storing and evaluating lottery ticket results.
 * ----------------------------------------------------------------------------
 *
 * Objective:	Select stored ticket for evaluation
 *
 * Author: 		Reinhard Rozumek
 * Email: 		reinhard@rozumek.de
 * Created: 	10/08/17
 * Last mod:	12/28/17
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
#include "rlotto.h"


/* FUCTION DECLARATION *******************************************************/

void read_Ticket(char *ticket_no);
void display_Ticket(void);


/*	SELECT TICKET ****************************************************************
	Search path of executable binary for lottery tickets and displays a sub menu
	to select which ticket to open. Afterwards read_Ticket function is called to
	read the ticket data from file into global variables. Finally and after user
	confirms selected ticket the function for ticket evaluation is called.
	*****************************************************************************/


int selectTicket(void) {

	char ticket_no[7];

	printf("\nTICKET SELECTION\n\n");

	// Find all files in path of binary executable file. Requires dirent.h

	int i = 0;
	int i_min = 1, i_max;
	int i_input = 0;
	DIR *d;
    struct dirent *dir;
	char fn_array[100] [12];								// Array filename with extension (str length + 1)

    // First run just to count number of tickets
	d = opendir(TicketFolder);

    if (d)
    {
		while ((dir = readdir(d)) != NULL)
        {
			char *fn = dir->d_name;							// fn: file name
			char * ext = strrchr(fn, '.');					// ext: file extension
			if(strcmp(ext, T_EXT) == 0) 					// File extension for lottery tickets
			{
				i++;
			}
        }

        closedir(d);
		i_max = i;
    }



	// Second run to read ticket file names in array for all files matching file extension
	d = opendir(TicketFolder);

    if (d)
	{
		i = 0;												// Reset counter i
		while ((dir = readdir(d)) != NULL)
        {
			char *fn = dir->d_name;							// fn: file name
			char * ext = strrchr(fn, '.');					// ext: file extension
			if(strcmp(ext, T_EXT) == 0) 					// File extension for lottery tickets
			{
				i++;
				strcpy(fn_array[i-1],fn);
				printf("%3i --> Ticket Number: %.*s File Name: %s\n", i, 7, fn + 0, fn_array[i-1]);
			}
        }
        closedir(d);
    }


	// i equals null --> no ticket found
	if(i == 0)
	{
		 // no ticket found
		 printf("\nNo ticket found in selected directory.\n");
	}
	else
	{
		printf("\n%i ticket(s) found in selected directory.\n", i_max);
		do {
			printf("\nEnter number between %i and %i: ",i_min, i_max);
			scanf("%d", &i_input);
			if(i_input < 1 || i_input > i_max)
			if(i_input < 1 || i_input > i_max)
			{
				printf("\n \"%d\" is not between %i and %i !\n",i_input, i_min, i_max);
				printf("\n \"%d\" is not between %i and %i !\n",i_input, i_min, i_max);
			}
		}while(i_input < 1 || i_input > i_max);

		strncpy(ticket_no, fn_array[i_input - 1] + 0,7);
		ticket_no[7] = '\0';
		printf("\nTicket No %s has been selected.\n", ticket_no);
	}



	// Call function for reading selected ticket

	read_Ticket(ticket_no);

	return 0;
}

/*	READ TICKET ****************************************************************
	Reads selected ticket into ticket structure
	*****************************************************************************/

	void read_Ticket(char *ticket_no) {

		FILE *fp;						// file pointer
		char line[MAX_LINE_LENGTH];		// array for line string
		int lnr;  						// line number of input file
		char *description;				// left token of separated input line contains line description
		char *value;					// right token of separated input line contains line value
		char *token1, *token2, *token3;	// token 1-3 for lottery numbers
		char *token4, *token5, *token6;	// token 4-6 for lottery numbers
		int sConfirm;					// yes or no to confirm ticket for further evaluation


		// construct filename
		char t_filename[45];
		strcpy(t_filename, TicketFolder);
		strcat(t_filename, ticket_no);
		strcat(t_filename, T_EXT);

		// Open file for reading ----------------------------------

		lnr = 0;
		fp = fopen(t_filename, "r");

		if(fp == NULL) {

			printf("Error opening file!\n");

		} else {

			while(fgets(line, MAX_LINE_LENGTH, fp) != NULL){

				strtok(line, "\n");			// Remove trailing new line character

				lnr++;

				// Parsing input and copy into current ticket structure ----------------------------------

				// separate input line

				description = strtok(line, ":");
				value = strtok(0, ":");

				// reading values into ticket structure

				switch(lnr){

					case 1:
						strcpy(current.T_No, value); break;
					case 2:
						strcpy(current.T_Player, value); break;
					case 3:
						strcpy(current.T_Start, value); break;
					case 4:
						strcpy(current.T_Runtime, value); break;
					case 5:
						strcpy(current.T_D_Day, value); break;
					case 6:
						strcpy(current.T_G77, value); break;
					case 7:
						strcpy(current.T_SU6, value); break;
					case 8:
						strcpy(current.T_GSP, value); break;
					case 9:
						current.T_Max_Row = atoi(value); break;
					case 10:

						token1 = strtok(value, ","); current.T_Row[lnr -10][0] = atoi(token1);
						token2 = strtok(0, ","); current.T_Row[lnr -10][1] = atoi(token2);
						token3 = strtok(0, ","); current.T_Row[lnr -10][2] = atoi(token3);
						token4 = strtok(0, ","); current.T_Row[lnr -10][3] = atoi(token4);
						token5 = strtok(0, ","); current.T_Row[lnr -10][4] = atoi(token5);
						token6 = strtok(0, ","); current.T_Row[lnr -10][5] = atoi(token6);
						break;

					case 11:

						token1 = strtok(value, ","); current.T_Row[lnr -10][0] = atoi(token1);
						token2 = strtok(0, ","); current.T_Row[lnr -10][1] = atoi(token2);
						token3 = strtok(0, ","); current.T_Row[lnr -10][2] = atoi(token3);
						token4 = strtok(0, ","); current.T_Row[lnr -10][3] = atoi(token4);
						token5 = strtok(0, ","); current.T_Row[lnr -10][4] = atoi(token5);
						token6 = strtok(0, ","); current.T_Row[lnr -10][5] = atoi(token6);
						break;

					case 12:

						token1 = strtok(value, ","); current.T_Row[lnr -10][0] = atoi(token1);
						token2 = strtok(0, ","); current.T_Row[lnr -10][1] = atoi(token2);
						token3 = strtok(0, ","); current.T_Row[lnr -10][2] = atoi(token3);
						token4 = strtok(0, ","); current.T_Row[lnr -10][3] = atoi(token4);
						token5 = strtok(0, ","); current.T_Row[lnr -10][4] = atoi(token5);
						token6 = strtok(0, ","); current.T_Row[lnr -10][5] = atoi(token6);
						break;

					case 13:

						token1 = strtok(value, ","); current.T_Row[lnr -10][0] = atoi(token1);
						token2 = strtok(0, ","); current.T_Row[lnr -10][1] = atoi(token2);
						token3 = strtok(0, ","); current.T_Row[lnr -10][2] = atoi(token3);
						token4 = strtok(0, ","); current.T_Row[lnr -10][3] = atoi(token4);
						token5 = strtok(0, ","); current.T_Row[lnr -10][4] = atoi(token5);
						token6 = strtok(0, ","); current.T_Row[lnr -10][5] = atoi(token6);
						break;

					case 14:

						token1 = strtok(value, ","); current.T_Row[lnr -10][0] = atoi(token1);
						token2 = strtok(0, ","); current.T_Row[lnr -10][1] = atoi(token2);
						token3 = strtok(0, ","); current.T_Row[lnr -10][2] = atoi(token3);
						token4 = strtok(0, ","); current.T_Row[lnr -10][3] = atoi(token4);
						token5 = strtok(0, ","); current.T_Row[lnr -10][4] = atoi(token5);
						token6 = strtok(0, ","); current.T_Row[lnr -10][5] = atoi(token6);
						break;

					case 15:

						token1 = strtok(value, ","); current.T_Row[lnr -10][0] = atoi(token1);
						token2 = strtok(0, ","); current.T_Row[lnr -10][1] = atoi(token2);
						token3 = strtok(0, ","); current.T_Row[lnr -10][2] = atoi(token3);
						token4 = strtok(0, ","); current.T_Row[lnr -10][3] = atoi(token4);
						token5 = strtok(0, ","); current.T_Row[lnr -10][4] = atoi(token5);
						token6 = strtok(0, ","); current.T_Row[lnr -10][5] = atoi(token6);
						break;

					case 16:

						token1 = strtok(value, ","); current.T_Row[lnr -10][0] = atoi(token1);
						token2 = strtok(0, ","); current.T_Row[lnr -10][1] = atoi(token2);
						token3 = strtok(0, ","); current.T_Row[lnr -10][2] = atoi(token3);
						token4 = strtok(0, ","); current.T_Row[lnr -10][3] = atoi(token4);
						token5 = strtok(0, ","); current.T_Row[lnr -10][4] = atoi(token5);
						token6 = strtok(0, ","); current.T_Row[lnr -10][5] = atoi(token6);
						break;

					case 17:

						token1 = strtok(value, ","); current.T_Row[lnr -10][0] = atoi(token1);
						token2 = strtok(0, ","); current.T_Row[lnr -10][1] = atoi(token2);
						token3 = strtok(0, ","); current.T_Row[lnr -10][2] = atoi(token3);
						token4 = strtok(0, ","); current.T_Row[lnr -10][3] = atoi(token4);
						token5 = strtok(0, ","); current.T_Row[lnr -10][4] = atoi(token5);
						token6 = strtok(0, ","); current.T_Row[lnr -10][5] = atoi(token6);
						break;

					case 18:

						token1 = strtok(value, ","); current.T_Row[lnr -10][0] = atoi(token1);
						token2 = strtok(0, ","); current.T_Row[lnr -10][1] = atoi(token2);
						token3 = strtok(0, ","); current.T_Row[lnr -10][2] = atoi(token3);
						token4 = strtok(0, ","); current.T_Row[lnr -10][3] = atoi(token4);
						token5 = strtok(0, ","); current.T_Row[lnr -10][4] = atoi(token5);
						token6 = strtok(0, ","); current.T_Row[lnr -10][5] = atoi(token6);
						break;

					case 19:

						token1 = strtok(value, ","); current.T_Row[lnr -10][0] = atoi(token1);
						token2 = strtok(0, ","); current.T_Row[lnr -10][1] = atoi(token2);
						token3 = strtok(0, ","); current.T_Row[lnr -10][2] = atoi(token3);
						token4 = strtok(0, ","); current.T_Row[lnr -10][3] = atoi(token4);
						token5 = strtok(0, ","); current.T_Row[lnr -10][4] = atoi(token5);
						token6 = strtok(0, ","); current.T_Row[lnr -10][5] = atoi(token6);
						break;

					case 20:

						token1 = strtok(value, ","); current.T_Row[lnr -10][0] = atoi(token1);
						token2 = strtok(0, ","); current.T_Row[lnr -10][1] = atoi(token2);
						token3 = strtok(0, ","); current.T_Row[lnr -10][2] = atoi(token3);
						token4 = strtok(0, ","); current.T_Row[lnr -10][3] = atoi(token4);
						token5 = strtok(0, ","); current.T_Row[lnr -10][4] = atoi(token5);
						token6 = strtok(0, ","); current.T_Row[lnr -10][5] = atoi(token6);
						break;

					case 21:

						token1 = strtok(value, ","); current.T_Row[lnr -10][0] = atoi(token1);
						token2 = strtok(0, ","); current.T_Row[lnr -10][1] = atoi(token2);
						token3 = strtok(0, ","); current.T_Row[lnr -10][2] = atoi(token3);
						token4 = strtok(0, ","); current.T_Row[lnr -10][3] = atoi(token4);
						token5 = strtok(0, ","); current.T_Row[lnr -10][4] = atoi(token5);
						token6 = strtok(0, ","); current.T_Row[lnr -10][5] = atoi(token6);
						break;

					default:
					printf("\n Error parsing ticket file.\n");

				}

		}


		fclose(fp);

	}

		// Display selected Ticket ----------------------------------

		display_Ticket();

		// confirm for evaluation ----------------------------------

		printf("Evaluate this ticket now? [y/n]: ");

		do {
			sConfirm = tolower(mygetc());
			if(sConfirm != 'y' && sConfirm != 'n')
				printf("\nEnter \"y\" or \"n\"\n");
			if(sConfirm == 'y')
				evaluateTicket();
			if(sConfirm == 'n') {
				printf("\nReturning to main menu.\n");
				t_initialize();
				// exit statement removed due to compiler warning (
			}

		} while(sConfirm != 'y' && sConfirm != 'n');

	}
