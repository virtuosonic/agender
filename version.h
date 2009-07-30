#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "27";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2009";
	static const double UBUNTU_VERSION_STYLE = 9.07;
	
	//Software Status
	static const char STATUS[] = "Release";
	static const char STATUS_SHORT[] = "r";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 0;
	static const long BUILD = 6;
	static const long REVISION = 34;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 64;
	#define RC_FILEVERSION 1,0,6,34
	#define RC_FILEVERSION_STRING "1, 0, 6, 34\0"
	static const char FULLVERSION_STRING[] = "1.0.6.34";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 6;
	

}
#endif //VERSION_h
