#pragma once
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/pixdesc.h>
#include <libavutil/hwcontext.h>
#include <libavutil/opt.h>
#include <libavutil/avassert.h>
#include <libavutil/imgutils.h>

#pragma comment ( lib, "avformat.lib")
#pragma comment ( lib, "swscale.lib" )
#pragma comment ( lib, "avcodec.lib" )
#pragma comment ( lib, "avutil.lib" )
#pragma comment ( lib, "avdevice.lib" )
}

#ifdef HAWKEYE_HWDECODINGWITHFFMPEG_EXPORTS
#define CALLBACKPROC_API __declspec(dllexport)
#else
#define CALLBACKPROC_API __declspec(dllimport)
#endif

// our sample callback will only take 1 string parameter
//typedef void (CALLBACK * fnCallBackFunc)(std::string value);

typedef void (CALLBACK * fnCallBackFunc)(AVFrame *frame);




// marked as extern "C" to avoid name mangling issue
extern "C"
{
	//this is the export function for subscriber to register the callback function
	CALLBACKPROC_API void Register_Callback(fnCallBackFunc func);
	__declspec(dllexport) bool Init();
	__declspec(dllexport) bool DeInit();
}