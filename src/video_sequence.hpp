/*
 * video_sequence.hpp
 * 
 * Copyright 2012 Robert Knauer <robert@privatdemail.net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#ifndef _video_sequence_h_
#	define _video_sequence_h_
	
#	include <iostream>
extern "C" {
#	if __WORDSIZE == 64
#		define INT64_C(c)	c ## L
#		define UINT64_C(c)	c ## UL
#	else
#		define INT64_C(c)	c ## LL
#		define UINT64_C(c)	c ## ULL
#	endif
#	include <libavcodec/avcodec.h>
#	include <libavformat/avformat.h>
#	include <libswscale/swscale.h>
}
	
	class VideoSequence {
		public:
			VideoSequence();
			~VideoSequence();
			
			/*
			 * Set videofile:
			*/
			void set_videofile(char *file);
			/*
			 * Initialize player and start playing:
			*/
			int play(void);
			/*
			 * Stop playing and uninitialize player:
			 * INFO: To resume playing, you need to call play()
			*/
			int stop(void);
			/*
			 * Stop playing, but don't uninitialize player:
			 * INFO: To resume playing, you need to call resume()
			*/
			int pause(void);
			/*
			 * Resume playing (after pausing it):
			*/
			int resume(void);
			/*
			 * Check if playing is done:
			*/
			int done(void);
		private:
			/*
			 * Internal variables:
			*/
			char *m_videofile;
			int m_done;
	};
#endif // _video_sequence_h_
