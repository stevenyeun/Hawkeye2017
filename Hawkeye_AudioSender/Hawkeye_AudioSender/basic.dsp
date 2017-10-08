# Microsoft Developer Studio Project File - Name="basic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=basic - Win32 Debug_Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "basic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "basic.mak" CFG="basic - Win32 Debug_Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "basic - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "basic - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "basic - Win32 Debug_Unicode" (based on "Win32 (x86) Application")
!MESSAGE "basic - Win32 Release_Unicode" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "basic - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\..\bin\basic.exe"

!ELSEIF  "$(CFG)" == "basic - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "basic - Win32 Debug_Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "basic___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "basic___Win32_Debug_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "basic___Win32_Debug_Unicode"
# PROP Intermediate_Dir "basic___Win32_Debug_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"../../../bin/basicu.exe" /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "basic - Win32 Release_Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "basic___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "basic___Win32_Release_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "basic___Win32_Release_Unicode"
# PROP Intermediate_Dir "basic___Win32_Release_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /FR /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"..\..\..\bin\basicu.exe"

!ENDIF 

# Begin Target

# Name "basic - Win32 Release"
# Name "basic - Win32 Debug"
# Name "basic - Win32 Debug_Unicode"
# Name "basic - Win32 Release_Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\basic.cpp
# End Source File
# Begin Source File

SOURCE=.\basic.rc
# End Source File
# Begin Source File

SOURCE=.\basicDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\clrspace.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DecodeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PicturePreview.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\tvs.cpp
# End Source File
# Begin Source File

SOURCE=.\tvsdecodecontrol.cpp
# End Source File
# Begin Source File

SOURCE=.\tvsdisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\tvslivecontrol.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\basic.h
# End Source File
# Begin Source File

SOURCE=.\basicDlg.h
# End Source File
# Begin Source File

SOURCE=.\ConnectDlg.h
# End Source File
# Begin Source File

SOURCE=.\DecodeDialog.h
# End Source File
# Begin Source File

SOURCE=.\PicturePreview.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\tvs.h
# End Source File
# Begin Source File

SOURCE=.\tvsdecodecontrol.h
# End Source File
# Begin Source File

SOURCE=.\tvsdisplay.h
# End Source File
# Begin Source File

SOURCE=.\tvslivecontrol.h
# End Source File
# Begin Source File

SOURCE=.\VideoDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\basic.ico
# End Source File
# Begin Source File

SOURCE=.\res\basic.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section basic : {7154F7B1-FD89-43A5-850F-6731A1CE93F3}
# 	2:5:Class:CTVSDecodeControl
# 	2:10:HeaderFile:tvsdecodecontrol.h
# 	2:8:ImplFile:tvsdecodecontrol.cpp
# End Section
# Section basic : {CA1B836A-156F-40BD-A2F5-F7AABEFAD692}
# 	2:21:DefaultSinkHeaderFile:tvsdecodecontrol.h
# 	2:16:DefaultSinkClass:CTVSDecodeControl
# End Section
# Section basic : {EC99D4D7-15E4-49DB-97C2-80EB35FDB3EC}
# 	2:5:Class:CTVSLiveControl
# 	2:10:HeaderFile:tvslivecontrol.h
# 	2:8:ImplFile:tvslivecontrol.cpp
# End Section
# Section basic : {575A6BF1-1460-4907-9157-BECB7DCAC655}
# 	2:21:DefaultSinkHeaderFile:tvslivecontrol.h
# 	2:16:DefaultSinkClass:CTVSLiveControl
# End Section
# Section basic : {234BDCD3-2720-4876-A2F0-DE9A715BF21A}
# 	2:5:Class:CTVSDisplay
# 	2:10:HeaderFile:tvsdisplay.h
# 	2:8:ImplFile:tvsdisplay.cpp
# End Section
