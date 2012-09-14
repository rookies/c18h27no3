#ifndef _config_common_h_
#	define _config_common_h_

	/*
	 * Configuration types:
	*/
#	define CONFIG_TYPE_STRING 1
#	define CONFIG_TYPE_INTEGER 2
	/*
	 * Configuration indexes:
	*/
	// [...]
	
	typedef union {
		int type;
		char *string;
		int integer;
	} ConfigVariable;
#endif // _config_common_h_
