
// Hawkeye_VideoPlayer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CHawkeye_VideoPlayerApp:
// See Hawkeye_VideoPlayer.cpp for the implementation of this class
//

class CHawkeye_VideoPlayerApp : public CWinApp
{
public:
	CHawkeye_VideoPlayerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CHawkeye_VideoPlayerApp theApp;