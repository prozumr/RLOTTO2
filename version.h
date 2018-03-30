 /*version.h | RLotto | gcc | v0.9.0-beta
 * Console program for storing and evaluating lottery ticket results.
 * ----------------------------------------------------------------------------
 *
 * Objective:	maintain version information for source code
 *
 * Author: 		Reinhard Rozumek
 * Email: 		reinhard@rozumek.de
 * Created: 	10/08/17
 * Last mod:	03/30/18
 *
 * ----------------------------------------------------------------------------
 * This file is part of RLotto.                                               */


#ifndef VERSION_H
#define VERSION_H

	// Program Name
	static const char THISPROG[] = "RLOTTO";

	// Version Number Components
	static const long MAJOR = 0;
	static const long MINOR = 9;
	static const long PATCH = 0;

	// Software Status
	static const char STAGE[] = "beta";

#endif //VERSION_h

/*

GUIDELINE SUMMARY

Increment MAJOR version for breaking changes not backward compatible to earlier releases
Increment MINOR version for adding functionality in a backwards-compatible manner
Increment PATCH version for backwards-compatible bug fixes.

INITIAL AND FIRST PUBLIC RELEASE

Major version zero (0.y.z) is for initial development.
Version 1.0.0 defines the public released version

SOFTWARE STATUS

STAGE cannot be empty nor anything different from "alpha", "beta" or "production". 

PATCH NUMBER

PATCH version MUST be incremented if only backwards compatible bug fixes are introduced.

MINOR NUMBER

MINOR MUST be incremented if new, backwards compatible functionality is introduced that 
is considered as NOT 'big' enough to justify a change of the major version.
MINOR MUST be incremented if any public functionality is marked as deprecated.
MINOR MAY include patch level changes.
Patch version MUST be reset to 0 when minor version is incremented.

MAJOR NUMBER

MAJOR MUST be incremented if any backwards incompatible functional or non-functional
changes are introduced.
MAJOR MUST be incremented if any backwards compatible functional or non functional 
changes are introduced that are considered to be too 'big' to justify just a minor 
version change.
MAJOR MAY include minor and patch level changes.
Patch and minor version MUST be reset to 0 when major version is incremented.

 */
