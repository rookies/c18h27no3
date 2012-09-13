#ifndef _video_sequence_h_
	#define _video_sequence_h_
	
	#include <iostream>
	extern "C"
	{
		#if __WORDSIZE == 64
			#define INT64_C(c)	c ## L
			#define UINT64_C(c)	c ## UL
		#else
			#define INT64_C(c)	c ## LL
			#define UINT64_C(c)	c ## ULL
		#endif
		#include <libavcodec/avcodec.h>
		#include <libavformat/avformat.h>
		#include <libswscale/swscale.h>
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
