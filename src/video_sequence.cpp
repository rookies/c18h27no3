#include "video_sequence.hpp"

using namespace std;

VideoSequence::VideoSequence()
{
	m_done = 1;
}
VideoSequence::~VideoSequence()
{
	
}
void VideoSequence::set_videofile(char *file)
{
	m_videofile = file;
}
int VideoSequence::play(void)
{
	AVFormatContext *videofile_format_context = NULL;
	AVCodecContext *videofile_codec_context_video = NULL;
	AVCodec *videofile_codec_video = NULL;
	AVFrame *videofile_video_frame = NULL;
	AVDictionary *options_dict = NULL;
	int video_stream = -1;
	int i;
	
	cout << "Start playing the video sequence '" << m_videofile << "'... ";
	/*
	 * Register formats and codecs:
	*/
	av_register_all();
	/*
	 * Open video file:
	*/
	if (avformat_open_input(&videofile_format_context, m_videofile, NULL, NULL) !=0)
	{
		cout << "[FAIL]" << endl;
		cout << "Error: avformat_open_input() failed! Maybe the file doesn't exist?" << endl;
		return 1;
	};
	/*
	 * Get stream information:
	*/
	if (avformat_find_stream_info(videofile_format_context, NULL) < 0)
	{
		cout << "[FAIL]" << endl;
		cout << "Error: avformat_find_stream_info() failed!" << endl;
		return 1;
	};
	/*
	 * Dump file information:
	*/
	//av_dump_format(videofile_format_context, 0, m_videofile, 0);
	/*
	 * Find first video stream:
	*/
	for (i=0; i < videofile_format_context->nb_streams; i++)
	{
		if (videofile_format_context->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			video_stream = i;
			break;
		};
	}
	if (video_stream == -1)
	{
		cout << "[FAIL]" << endl;
		cout << "Error: Couldn't find a video stream!" << endl;
		return 1;
	};
	videofile_codec_context_video = videofile_format_context->streams[video_stream]->codec;
	/*
	 * Find a decoder:
	*/
	videofile_codec_video = avcodec_find_decoder(videofile_codec_context_video->codec_id);
	if (videofile_codec_video == NULL)
	{
		cout << "[FAIL]" << endl;
		cout << "Error: Unsupported video codec!" << endl;
		return 1;
	};
	/*
	 * Open codec:
	*/
	if (avcodec_open2(videofile_codec_context_video, videofile_codec_video, &options_dict) < 0)
	{
		cout << "[FAIL]" << endl;
		cout << "Error: Couldn't open video codec!" << endl;
		return 1;
	};
	/*
	 * Allocate video frame:
	*/
	videofile_video_frame = avcodec_alloc_frame();
}
int VideoSequence::stop(void)
{
	/* ... */
}
int VideoSequence::pause(void)
{
	/* ... */
}
int VideoSequence::resume(void)
{
	/* ... */
}
int VideoSequence::done(void)
{
	return m_done;
}
