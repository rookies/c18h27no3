#ifndef _config_linux_h_
#	define _config_linux_h_
	
#	include "config_common.h"
	
	class Config
	{
		public:
			Config();
			~Config();
			
			/*
			 * Load config:
			*/
			int load(void);
			/*
			 * Write config:
			*/
			int write(void);
			/*
			 * Get / set variable:
			*/
			ConfigVariable get(int index);
			void set(int index, ConfigVariable value);
		private:
			
	};
#endif // _config_linux_h_
