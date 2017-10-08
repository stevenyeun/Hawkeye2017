// Hawkeye_HWDecodingWithFFmpeg.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Hawkeye_HWDecodingWithFFmpeg.h"


int g_nInit = -1;
bool g_bDestroy = false;
enum AVHWDeviceType g_hwDeviceType;
std::string g_strURL;
fnCallBackFunc g_callBackFunc;

#if 1
static AVBufferRef *hw_device_ctx = NULL;
static enum AVPixelFormat hw_pix_fmt;
//static FILE *output_file = NULL;

static enum AVPixelFormat get_hw_format(AVCodecContext *ctx,
	const enum AVPixelFormat *pix_fmts)
{
	const enum AVPixelFormat *p;

	for (p = pix_fmts; *p != -1; p++) {
		if (*p == hw_pix_fmt)
			return *p;
	}

	fprintf(stderr, "Failed to get HW surface format.\n");
	return AV_PIX_FMT_NONE;
}
static int hw_decoder_init(AVCodecContext *ctx, const enum AVHWDeviceType type)
{
	int err = 0;

	if ((err = av_hwdevice_ctx_create(&hw_device_ctx, type,
		NULL, NULL, 0)) < 0) {
		fprintf(stderr, "Failed to create specified HW device.\n");
		return err;
	}
	ctx->hw_device_ctx = av_buffer_ref(hw_device_ctx);

	return err;
}
static enum AVPixelFormat find_fmt_by_hw_type(const enum AVHWDeviceType type)
{
	enum AVPixelFormat fmt;

	switch (type) {
	case AV_HWDEVICE_TYPE_VAAPI:
		fmt = AV_PIX_FMT_VAAPI;
		break;
	case AV_HWDEVICE_TYPE_DXVA2:
		fmt = AV_PIX_FMT_DXVA2_VLD;
		break;
	case AV_HWDEVICE_TYPE_D3D11VA:
		fmt = AV_PIX_FMT_D3D11;
		break;
	case AV_HWDEVICE_TYPE_VDPAU:
		fmt = AV_PIX_FMT_VDPAU;
		break;
	case AV_HWDEVICE_TYPE_VIDEOTOOLBOX:
		fmt = AV_PIX_FMT_VIDEOTOOLBOX;
		break;
	default:
		fmt = AV_PIX_FMT_NONE;
		break;
	}

	return fmt;
}
int decode_write(AVCodecContext *avctx, AVPacket *packet, AVFrame **dstFrame)
{
	AVFrame *frame = NULL, *sw_frame = NULL;
	AVFrame *tmp_frame = NULL;
	uint8_t *buffer = NULL;
	int size;
	int ret = 0;

	ret = avcodec_send_packet(avctx, packet);
	if (ret < 0) {
		fprintf(stderr, "Error during decoding\n");
		return ret;
	}

	while (ret >= 0) {
		if (!(frame = av_frame_alloc()) || !(sw_frame = av_frame_alloc())) {
			fprintf(stderr, "Can not alloc frame\n");
			ret = AVERROR(ENOMEM);
			goto fail;
		}

		ret = avcodec_receive_frame(avctx, frame);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
			av_frame_free(&frame);
			av_frame_free(&sw_frame);
			return 0;
		}
		else if (ret < 0) {
			fprintf(stderr, "Error while decoding\n");
			goto fail;
		}

		g_callBackFunc(frame, "ok");

	fail:
		av_frame_free(&frame);
		av_frame_free(&sw_frame);
		if (buffer)
			av_freep(&buffer);
		if (ret < 0)
			return ret;
	}

	return 0;
}
#endif

#if 0
UINT ReadFrameThread(void * pParam)
{
	fnCallBackFunc func = (fnCallBackFunc)pParam;

	/* actual decoding and dump the raw data */
#if 1

	while (1)
	{

#if 1
		while (g_nInit >= 0) {
			if ((g_nInit = av_read_frame(g_input_ctx, &g_packet)) < 0)
				break;

			if (g_nVideo_stream == g_packet.stream_index)
			{
				AVFrame * dstFrame;
				g_nInit = decode_write(g_decoder_ctx, &g_packet, &dstFrame);

				func(dstFrame);
			}
			av_packet_unref(&g_packet);
		}
#endif


		Sleep(1000);
		func(NULL);
	}

#endif
}
#endif

DWORD WINAPI ReadFrameThread(__in LPVOID lpParameter)
{
	//MessageBox(NULL, "Hello", "Testing", NULL); ­
	//fnCallBackFunc func = (fnCallBackFunc)lpParameter;

	AVFormatContext *input_ctx = NULL;
	int video_stream, ret;
	AVStream *video = NULL;
	AVCodecContext *decoder_ctx = NULL;
	AVCodec *decoder = NULL;
	AVPacket packet;
	

	if (g_hwDeviceType == 0) {
		string hwDevice = av_hwdevice_get_type_name(g_hwDeviceType);		
		fprintf(stderr, "Usage: %s <vaapi|vdpau|dxva2|d3d11va> <input file> <output file>\n", hwDevice.c_str());

		string str;	
		g_callBackFunc(NULL, "Usage: " + hwDevice + " <vaapi|vdpau|dxva2|d3d11va>");

		// prints "writing toto,  x=40.230 : 50-th try"

		return -1;
	}

	av_register_all();
	avformat_network_init();

	
	hw_pix_fmt = find_fmt_by_hw_type(g_hwDeviceType);
	if (hw_pix_fmt == -1) {
		//fprintf(stderr, "Cannot support '%s' in this example.\n", g_hwDeviceType);
		string hwDevice = av_hwdevice_get_type_name(g_hwDeviceType);		
		g_callBackFunc(NULL, "Cannot support " + hwDevice + " in this example.\n");
		return -1;
	}

	/* open the input file */
	AVDictionary *stream_opts = 0;
	av_dict_set(&stream_opts, "rtsp_transport", "tcp", 0);//한프로그램에서 스레드 여러개 돌리면 속도가 느려짐?
														  //av_dict_set(&stream_opts, "rtsp_transport", "http", 0);
														  //av_dict_set(&stream_opts, "rtsp_flags", "prefer_tcp", 0);
														  //av_dict_set(&stream_opts, "rtsp_flags", "listen", 0);
														  //av_dict_set(&stream_opts, "reorder_queue_size", "tcp", 0);

	av_dict_set(&stream_opts, "stimeout", "10000000", 0); // in microseconds.
														  //av_dict_set(&stream_opts, "max_alloc ", "10000", 0);

	if (avformat_open_input(&input_ctx, g_strURL.c_str(), NULL, &stream_opts) != 0) {
		fprintf(stderr, "Cannot open input file '%s'\n", g_strURL.c_str());

	
		g_callBackFunc(NULL, "Cannot open input file " + g_strURL + "\n");

		return -1;
	}

	if (avformat_find_stream_info(input_ctx, NULL) < 0) {
		fprintf(stderr, "Cannot find input stream information.\n");

		g_callBackFunc(NULL, "Cannot find input stream information.\n");
		return -1;
	}

	/* find the video stream information */
	ret = av_find_best_stream(input_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, &decoder, 0);
	if (ret < 0) {
		fprintf(stderr, "Cannot find a video stream in the input file\n");

		g_callBackFunc(NULL, "Cannot find a video stream in the input file\n");
		return -1;
	}
	video_stream = ret;

	if (!(decoder_ctx = avcodec_alloc_context3(decoder)))
	{
		g_callBackFunc(NULL, "if (!(decoder_ctx = avcodec_alloc_context3(decoder))) \n");

		return AVERROR(ENOMEM);
	}

	video = input_ctx->streams[video_stream];
	if (avcodec_parameters_to_context(decoder_ctx, video->codecpar) < 0)
	{
		g_callBackFunc(NULL, "avcodec_parameters_to_context(decoder_ctx, video->codecpar) < 0 \n");
		return -1;
	}

	decoder_ctx->get_format = get_hw_format;
	av_opt_set_int(decoder_ctx, "refcounted_frames", 1, 0);

	if (hw_decoder_init(decoder_ctx, g_hwDeviceType) < 0)
	{
		g_callBackFunc(NULL, "if (hw_decoder_init(decoder_ctx, g_hwDeviceType) < 0) \n");
		return -1;
	}

	if ((ret = avcodec_open2(decoder_ctx, decoder, NULL)) < 0) {
		fprintf(stderr, "Failed to open codec for stream #%u\n", video_stream);
		
		stringstream ss;
		ss << video_stream;		
		g_callBackFunc(NULL, "Failed to open codec for stream " + ss.str() + "\n");

		return -1;
	}

	/* open the file to dump raw data */
	//output_file = fopen(argv[3], "w+");

	/* actual decoding and dump the raw data */
	while (ret >= 0) {

		if (g_bDestroy == true)
		{
			break;
		}

		if ((ret = av_read_frame(input_ctx, &packet)) < 0)
			break;

		if (video_stream == packet.stream_index)
		{
			AVFrame * dstFrame;
			ret = decode_write(decoder_ctx, &packet, &dstFrame);

		}
		av_packet_unref(&packet);
	}

	/* flush the decoder */
	packet.data = NULL;
	packet.size = 0;
	ret = decode_write(decoder_ctx, &packet, NULL);
	av_packet_unref(&packet);

	//if (output_file)
	//	fclose(output_file);
	avcodec_free_context(&decoder_ctx);
	avformat_close_input(&input_ctx);
	av_buffer_unref(&hw_device_ctx);

	g_callBackFunc(NULL, "Finish ReadFrameThread \n");
	return 1;
}

// This is an example of an exported function.
CALLBACKPROC_API void Register_Callback(fnCallBackFunc func)
{
	//g_readFrameThread = AfxBeginThread(ReadFrameThread, &func, THREAD_PRIORITY_NORMAL);

	g_callBackFunc = func;

	CreateThread(NULL, NULL, ReadFrameThread, NULL, NULL, NULL);
	
	g_callBackFunc(NULL, "Register_Callback \n");

#if 0
	int count = 0;

	// let's send 10 messages to the subscriber
	while (count < 10)
	{
		// format the message
		std::stringstream msg;
		msg << "Message #" << count;

		// call the callback function
		func(msg.str());

		count++;

		// Sleep for 2 seconds
		Sleep(2000);
	}
#endif

}

#if 1
__declspec(dllexport) bool Init(string strURL, enum AVHWDeviceType type)
{
	g_hwDeviceType = type;
	g_strURL = strURL;

	return false;
}
#endif

__declspec(dllexport) bool DeInit()
{
	g_bDestroy = true;

	return false;
}


