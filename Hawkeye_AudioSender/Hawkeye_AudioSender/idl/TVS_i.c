

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Mon Dec 29 15:15:38 2014
 */
/* Compiler settings for .\TVS.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ITVSLiveControl,0xEC99D4D7,0x15E4,0x49DB,0x97,0xC2,0x80,0xEB,0x35,0xFD,0xB3,0xEC);


MIDL_DEFINE_GUID(IID, IID_ITVSDecodeControl,0x7154F7B1,0xFD89,0x43a5,0x85,0x0F,0x67,0x31,0xA1,0xCE,0x93,0xF3);


MIDL_DEFINE_GUID(IID, IID_ITVSDecodeCallback,0xC0967DFC,0xABA0,0x40d5,0x9C,0xBB,0x5E,0x5B,0x12,0x17,0x09,0x37);


MIDL_DEFINE_GUID(IID, IID_ITVSDisplay,0x234BDCD3,0x2720,0x4876,0xA2,0xF0,0xDE,0x9A,0x71,0x5B,0xF2,0x1A);


MIDL_DEFINE_GUID(IID, IID_ITVSPlaybackControl,0x10998A2A,0xE955,0x4931,0xA9,0xE4,0x83,0x25,0x8B,0x6E,0x4B,0xAC);


MIDL_DEFINE_GUID(IID, IID_ITVSIVSControl,0x2F88F0C6,0x1126,0x4b65,0xAB,0xBC,0xA5,0xAE,0x99,0xAC,0x5A,0x43);


MIDL_DEFINE_GUID(IID, LIBID_TVSLib,0xE0AEF027,0x8849,0x4A4F,0xBB,0x93,0x3F,0x6A,0x2B,0xD9,0x82,0x0D);


MIDL_DEFINE_GUID(IID, DIID__ITVSLiveControlEvents,0xC3555312,0xA0C9,0x449C,0xA4,0xCD,0x83,0xC5,0x15,0xF6,0x5D,0xFB);


MIDL_DEFINE_GUID(CLSID, CLSID_TVSLiveControl,0x575A6BF1,0x1460,0x4907,0x91,0x57,0xBE,0xCB,0x7D,0xCA,0xC6,0x55);


MIDL_DEFINE_GUID(IID, DIID__ITVSPlaybackControlEvents,0x0530937B,0x3487,0x4FC1,0x90,0x30,0x9A,0xBB,0x6C,0xFA,0x53,0xBA);


MIDL_DEFINE_GUID(CLSID, CLSID_TVSPlaybackControl,0x6E1B300A,0x119E,0x461D,0x96,0x53,0xD6,0xCB,0xEF,0x00,0xB3,0xE5);


MIDL_DEFINE_GUID(IID, DIID__ITVSDecodeControlEvents,0x770BD7DB,0x5024,0x4c28,0x9B,0xBA,0x52,0x0B,0x28,0x4E,0xF5,0x08);


MIDL_DEFINE_GUID(CLSID, CLSID_TVSDecodeControl,0xCA1B836A,0x156F,0x40bd,0xA2,0xF5,0xF7,0xAA,0xBE,0xFA,0xD6,0x92);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



