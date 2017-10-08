// Hawkeye_HWDecodingWithFFmpeg.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Hawkeye_HWDecodingWithFFmpeg.h"


int g_nInit = -1;
int g_nVideo_stream;
AVFormatContext * g_input_ctx = NULL;
AVCodecContext * g_decoder_ctx = NULL;
AVPacket g_packet;

#if 1
static AVBufferRef *hw_device_ctx = NULL;
static enum AVPixelFormat hw_pix_fmt;
static FILE *output_file = NULL;

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

// This is an example of an exported function.
CALLBACKPROC_API void Register_Callback(fnCallBackFunc func)
{

	/* actual decoding and dump the raw data */
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
	AVFrame *frame;


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

__declspec(dllexport) bool Init()
{
	avcodec_register_all();
	return false;
}

__declspec(dllexport) bool DeInit()
{
	return false;
}


