#ifndef VERSION_H
#define VERSION_H

namespace Agender{
	
	//Software Status
	static const char STATUS[] = "Release";
	static const char STATUS_SHORT[] = "r";
	
	//Standard Version Type
    static const int MAJOR = 1;
    static const int MINOR = 2;
    static const int BUILD = 0;
    static const int REVISION = 0;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 11;
	#define RC_FILEVERSION 1,2,0,0
	#define RC_FILEVERSION_STRING "1, 2, 0, 0\0"
	static const char FULLVERSION_STRING[] = "1.2.0.0";
	
	//SVN Version
	static const char SVN_REVISION[] = "307";
	static const char SVN_DATE[] = "2011-05-01T01:21:01.081440Z";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 1;
	

}
#endif //VERSION_H
