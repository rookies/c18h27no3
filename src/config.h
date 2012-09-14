#ifndef _config_h_
#	define _config_h_
	
#	ifdef _WIN32
#		include "config_windows.h"
#	endif
#	ifdef __linux__
#		include "config_linux.h"
#	endif
#endif // _config_h_
