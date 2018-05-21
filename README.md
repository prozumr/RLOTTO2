# RLOTTO2

## WHAT IS RLOTTO?

RLOTTO is most and foremost a beginner's exersise for learning and training of the C Programming language. Furthermore RLOTTO is a little console program to evaluate German lottery results. The program evaluates lottery matches along with win classes for lottery, Game 77 and Super 6. The actual effiency for the evaluation of a single drawing ticket is disputable since both ticket and drawing data have to be entered manually. The Program however becomes more beneficial for weekly, monthly or permanent tickets with re-occuring drawings. 

Current version of RLOTTO uses plain text files to store tickets in order to train text based I/O operations. For the future a binary  file is planned as database to store all ticket data either just a new version of RLOTTO or as a fork to the current version.


## SUPPORTED PLATFORMS

Currently Windows and Linux are supported. For platform specific compile instructions see next section. 


## SOURCE DOWNLOAD AND COMPILE INSTRUCTIONS

For download the source code please files refer to the lastest stable release on github: 

https://github.com/prozumr/RLOTTO2/releases

Required source code files are:

rlotto.c, t_select.c, t_add.c, t_evaluate.c, t_delete.c, settings.c, t_common.c, rlotto.h, version.h 

You can compile RLOTTO with the GNU C Compiler by using the following command:

```
gcc -Wall rlotto.c t_select.c t_add.c t_evaluate.c t_delete.c settings.c t_common.c -o rlotto.exe
```

For compiling for Linux use the provided make file.


## INSTALLATION

RLOTTO does not come with a installer. Just start the executable from your desired location. Please note that subfolders for ticket and result files are created in the same path. You might want to create a shortcut and place it in the start menu or on the desktop for your concenience.

## USAGE

Usage of RLOTTO is most simple. RLOTTO is dialog based. So once you select a feature from the main menu RLOTTO leads you through all further steps. In addition RLOTTO checks all data entered by users for plausibilty and formal correctness. 


Choose "Add Ticket" form the main menu to create a new ticket. A dialog is leading through all queries required to add a new ticket. You have the option to create the ticket with or without "Game 77" or "Super 6". Once confirmed at the end of the dialog the program safes all ticket information to a text file which is stored in a subfolder in the path of the program executable called "tickets".

Choose "Evaluate Ticket" from the main menu to evaluate the ticket against drawing results. Select the ticket by ticket number and enter the results from the drawing. Once confirmed at the end of the dialog the program evaluates lottery matches, any wins for Spiel 77 or Super 6 (if played) and evaluates the win class. The results are displayed in the terminal window and stored as text file in a subfolder in the path of the program executable called "results".

Choose "Delete Ticket" from main menu in order to delete a ticket from the repository at ./results.

## PLANNED FEATURES

Future version of RLOTTO will feature "settings" such as configuration of path to ticket or result file folder. Also some statistics functions are planned. In more distant future it is planned to store all ticket data in a single binary file instead using ascii files. This however require redisign of some fundamental I/O functions of RLOTTO. Do no expect this coming soon.


## AUTHORS

All code writtenby prozumr except some small adoptions for linux written by mabod.

Make file provided by mabod.

## CONTRIBUTORS

Thanks for strong contribution by mabod.

## LICENSE

RLOTTO is puplished and distrubted by the terms of the GNU GPL 3 license.
