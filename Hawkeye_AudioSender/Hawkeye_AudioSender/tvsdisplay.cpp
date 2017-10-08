// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "tvsdisplay.h"


/////////////////////////////////////////////////////////////////////////////
// CTVSDisplay properties

/////////////////////////////////////////////////////////////////////////////
// CTVSDisplay operations

short CTVSDisplay::GetMonitorCount()
{
	short result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

long CTVSDisplay::GetLayoutMode(short nMonitor)
{
	long result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		nMonitor);
	return result;
}

void CTVSDisplay::SetLayoutMode(short nMonitor, long nNewValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_I4;
	InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nMonitor, nNewValue);
}

long CTVSDisplay::GetDUCount(short nMonitor)
{
	long result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		nMonitor);
	return result;
}

void CTVSDisplay::SetDUCount(short nMonitor, long nNewValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nMonitor, nNewValue);
}

long CTVSDisplay::GetMapChannel(short nMonitor, long nDU)
{
	long result;
	static BYTE parms[] =
		VTS_I2 VTS_I4;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		nMonitor, nDU);
	return result;
}

void CTVSDisplay::SetMapChannel(short nMonitor, long nDU, long nNewValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_I4 VTS_I4;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nMonitor, nDU, nNewValue);
}

BOOL CTVSDisplay::SetDURect(short nMonitor, long nDU, short nLeft, short nTop, short nRight, short nBottom)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_I4 VTS_I2 VTS_I2 VTS_I2 VTS_I2;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nMonitor, nDU, nLeft, nTop, nRight, nBottom);
	return result;
}

BOOL CTVSDisplay::GetDURect(short nMonitor, long nDU, short* pnLeft, short* pnTop, short* pnRight, short* pnBottom)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_I4 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nMonitor, nDU, pnLeft, pnTop, pnRight, pnBottom);
	return result;
}

BOOL CTVSDisplay::GetShowToolbar(long lChID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		lChID);
	return result;
}

void CTVSDisplay::SetShowToolbar(long lChID, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lChID, bNewValue);
}

long CTVSDisplay::GetToolbarConfig(long lChID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		lChID);
	return result;
}

void CTVSDisplay::SetToolbarConfig(long lChID, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lChID, nNewValue);
}

long CTVSDisplay::AddOsdArea(long lChID, short nLeft, short nTop, short nRight, short nBottom, short nType)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2;
	InvokeHelper(0x79, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		lChID, nLeft, nTop, nRight, nBottom, nType);
	return result;
}

void CTVSDisplay::RemoveOsdArea(long lOSDID)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lOSDID);
}

void CTVSDisplay::UpdateOsdArea(long lOSDID, const VARIANT& vData)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x7b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lOSDID, &vData);
}

short CTVSDisplay::GetOsdType(long lOSDID)
{
	short result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms,
		lOSDID);
	return result;
}

long CTVSDisplay::GetOsdForeColor(long lOSDID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		lOSDID);
	return result;
}

void CTVSDisplay::SetOsdForeColor(long lOSDID, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lOSDID, nNewValue);
}

long CTVSDisplay::GetOsdBackColor(long lOSDID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		lOSDID);
	return result;
}

void CTVSDisplay::SetOsdBackColor(long lOSDID, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lOSDID, nNewValue);
}

BOOL CTVSDisplay::GetOsdTransparency(long lOSDID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		lOSDID);
	return result;
}

void CTVSDisplay::SetOsdTransparency(long lOSDID, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lOSDID, bNewValue);
}

CString CTVSDisplay::GetOsdFontName(long lOSDID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		lOSDID);
	return result;
}

void CTVSDisplay::SetOsdFontName(long lOSDID, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lOSDID, lpszNewValue);
}

short CTVSDisplay::GetOsdFontSize(long lOSDID)
{
	short result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms,
		lOSDID);
	return result;
}

void CTVSDisplay::SetOsdFontSize(long lOSDID, short nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I2;
	InvokeHelper(0x81, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lOSDID, nNewValue);
}

void CTVSDisplay::SetDigitalZoom(long lChID, long lZoom, long xStart, long yStart)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x82, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lChID, lZoom, xStart, yStart);
}

void CTVSDisplay::GetDigitalZoom(long lChID, long* lZoom, long* xStart, long* yStart)
{
	static BYTE parms[] =
		VTS_I4 VTS_PI4 VTS_PI4 VTS_PI4;
	InvokeHelper(0x83, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lChID, lZoom, xStart, yStart);
}

//asvzzz
HRESULT CTVSDisplay::GetChannelFlip(long lChID, long* lMode)
{
//	HRESULT result;
//	static BYTE parms[] = VTS_I4 VTS_PI4;
//	InvokeHelper(0x8C, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, lChID, lMode);
//	return result;

	long result;
	static BYTE parms[] = VTS_I4;
	InvokeHelper(0x8C, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,lChID);
	*lMode=result;
	return S_OK;


}

HRESULT CTVSDisplay::SetChannelFlip(long lChID, long lMode)
{
	HRESULT result;
	static BYTE parms[] = VTS_I4 VTS_I4;
	InvokeHelper(0x8C, DISPATCH_PROPERTYPUT, VT_I4, (void*)&result, parms, lChID, lMode);
	return result;
}