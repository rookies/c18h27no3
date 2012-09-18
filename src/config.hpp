#ifndef _config_h_
#	define _config_h_
	
#	ifdef _WIN32
#		include "config_windows.hpp"
#	endif
#	ifdef __linux__
#		include "config_linux.hpp"
#	endif
#endif // _config_h_
