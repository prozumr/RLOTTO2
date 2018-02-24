 /*version.h | RLotto | gcc | v0.8.354.1715
 * Console program for storing and evaluating lottery ticket results.
 * ----------------------------------------------------------------------------
 *
 * Objective:	maintain version information for source code
 *
 * Author: 		Reinhard Rozumek
 * Email: 		reinhard@rozumek.de
 * Created: 	10/08/17
 * Last mod:	02/11/18
 *
 * ----------------------------------------------------------------------------
 * This file is part of RLotto.                                               */


#ifndef VERSION_H
#define VERSION_H

	// TODO (camelo#3#01/03/18): Improve handling of version number

	//Program Name
	static const char THISPROG[] = "RLOTTO";

	//Software Status
	static const char STATUS[] = "v0.8 beta";
	static const char STATUS_SHORT[] = "v0.8b";

	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 8;
	static const long BUILD = 354;
	static const long REVISION = 1715;

	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 354;
	#define RC_FILEVERSION 0,8,353,1715
	#define RC_FILEVERSION_STRING "0, 8, 354, 1715\0"
	static const char FULLVERSION_STRING[] = "0.8.354.1715";

	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 29;


#endif //VERSION_h



/*

ABSTRACT

Originally generated by a Code::Blocks plugin. RLOTTO continues to use version.h
for central maintenance of versioning. However and since RLOTTO is developed with
no real IDE but just an editor (VIM/GVIM/Notepad++), FAR and the GNU Compiler this
file is maintained manually.


VERSION VALUES

Major - Increments by 1 when the minor version reaches its maximum
Minor - Increments by 1 when the build number pass the barrier of build times, the value is reset to 0 when it reach its maximum value.
Build number (also equivalent to Release) - Increments by 1 every time that the revision number is incremented.
Revision - Increments randomly when the project has been modified and then compiled.

STATUS

Some fields to keep track of your software status with a list of predefined values for convenience.

Software Status - The typical example should be v1.0 Alpha
Abbreviation - Same as software status but like this: v1.0a

SCHEME

Minor maximum - The maximum number that the Minor value can reach, after this value is reached the Major is incremented by 1 and next time project is compiled the Minor is set to 0.
Build Number maximum - When the value is reached, the next time the project is compiled is set to 0. Put a 0 for unlimited.
Revision maximum - Same as Build Number maximum. Put a 0 for unlimited
Revision random maximum - The revision increments by random numbers that you decide, if you put here 1, the revision obviously will increment by 1.
Build times before incrementing Minor - After successful changes to code and compilation the build history will increment, and when it reaches this value the Minor will increment.
 */
