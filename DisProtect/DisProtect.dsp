# Microsoft Developer Studio Project File - Name="DisProtect" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DisProtect - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DisProtect.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DisProtect.mak" CFG="DisProtect - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DisProtect - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DisProtect - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DisProtect - Win32 Release"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "__TRANS_KOR__" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"../Bin/Release/DisProtect.dll"

!ELSEIF  "$(CFG)" == "DisProtect - Win32 Debug"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../Bin/Debug/DisProtect.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DisProtect - Win32 Release"
# Name "DisProtect - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\51SRyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DisProtect.cpp
# End Source File
# Begin Source File

SOURCE=.\DisProtect.def
# End Source File
# Begin Source File

SOURCE=.\DisProtect.rc
# End Source File
# Begin Source File

SOURCE=.\DLRyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EquipAlgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Label.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PcaPcaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PcaRcDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PcaSelectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RcAssDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RcFuseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RcPcaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RcRcDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RcSeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RcSettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RyCRyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RyPCADlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RyRcDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetRelayDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SortClass.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TCCurve2.cpp
# End Source File
# Begin Source File

SOURCE=.\TCCurveDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TCFuseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TCRcRegDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TCRelayRegDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\51SRyDlg.h
# End Source File
# Begin Source File

SOURCE=.\CustomerDlg.h
# End Source File
# Begin Source File

SOURCE=.\DLRyDlg.h
# End Source File
# Begin Source File

SOURCE=.\EquipAlgDlg.h
# End Source File
# Begin Source File

SOURCE=.\Label.h
# End Source File
# Begin Source File

SOURCE=.\MsgDlg.h
# End Source File
# Begin Source File

SOURCE=.\PcaPcaDlg.h
# End Source File
# Begin Source File

SOURCE=.\PcaRcDlg.h
# End Source File
# Begin Source File

SOURCE=.\PcaSelectDlg.h
# End Source File
# Begin Source File

SOURCE=.\RcAssDlg.h
# End Source File
# Begin Source File

SOURCE=.\RcFuseDlg.h
# End Source File
# Begin Source File

SOURCE=.\RcPcaDlg.h
# End Source File
# Begin Source File

SOURCE=.\RcRcDlg.h
# End Source File
# Begin Source File

SOURCE=.\RcSeDlg.h
# End Source File
# Begin Source File

SOURCE=.\RcSettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RyCRyDlg.h
# End Source File
# Begin Source File

SOURCE=.\RyPCADlg.h
# End Source File
# Begin Source File

SOURCE=.\RyRcDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetRelayDlg.h
# End Source File
# Begin Source File

SOURCE=.\SortClass.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TCCurve2.h
# End Source File
# Begin Source File

SOURCE=.\TCCurveDlg.h
# End Source File
# Begin Source File

SOURCE=.\TCFuseDlg.h
# End Source File
# Begin Source File

SOURCE=.\TCRcRegDlg.h
# End Source File
# Begin Source File

SOURCE=.\TCRelayRegDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DisProtect.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
