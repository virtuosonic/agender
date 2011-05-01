#ifndef VERSION_H
#define VERSION_H

namespace Agender {

//Software Status
static const char STATUS[] = "Release";
static const char STATUS_SHORT[] = "r";

//Standard Version Type
static const long MAJOR = 2;
static const long MINOR = 0;
static const long BUILD = 0;
static const long REVISION = 0;

//Miscellaneous Version Types
static const long BUILDS_COUNT = 10;
#define RC_FILEVERSION 2,0,0,0
#define RC_FILEVERSION_STRING "2, 0, 0, 0\0"
static const char FULLVERSION_STRING[] = "2.0.0.0";

//SVN Version
static const char SVN_REVISION[] = "293";
static const char SVN_DATE[] = "2011-04-24T08:39:35.340746Z";

//These values are to keep track of your versioning state, don't modify them.
static const long BUILD_HISTORY = 1;


}
#endif //VERSION_H
