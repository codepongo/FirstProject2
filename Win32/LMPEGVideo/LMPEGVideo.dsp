# Microsoft Developer Studio Project File - Name="LMPEGVideo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LMPEGVideo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LMPEGVideo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LMPEGVideo.mak" CFG="LMPEGVideo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LMPEGVideo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LMPEGVideo - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LMPEGVideo - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "../../Intermediate/Win32/LMPEGVideo/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /GR /GX /Z7 /Od /I "../../include/LMPEGVideo" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x414 /d "_DEBUG"
# ADD RSC /l 0x414 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /map /debug /machine:I386 /out:"../../bin/Win32/Debug/LMPEGVideo.dll"
# Begin Custom Build
IntDir=.\../../Intermediate/Win32/LMPEGVideo/Debug
InputPath=\MMStudio\bin\Win32\Debug\LMPEGVideo.dll
SOURCE="$(InputPath)"

"../../bin/Win32/Debug/LMPEGVideo.ad" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ParseMap $(IntDir)/LMPEGVideo.map "../../bin/Win32/Debug/LMPEGVideo.typeinfo"

# End Custom Build

!ELSEIF  "$(CFG)" == "LMPEGVideo - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "LMPEGVideo___Win32_Release"
# PROP BASE Intermediate_Dir "LMPEGVideo___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "../../Intermediate/Win32/LMPEGVideo/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GR /GX /Zd /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GR /GX /Zd /O2 /I "../../include/LMPEGVideo" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x414 /d "NDEBUG"
# ADD RSC /l 0x414 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /debug /machine:I386 /out:"../bin/Release/LMPEGVideo.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /map /debug /machine:I386 /out:"../../bin/Win32/Release/LMPEGVideo.dll"
# Begin Custom Build
IntDir=.\../../Intermediate/Win32/LMPEGVideo/Release
InputPath=\MMStudio\bin\Win32\Release\LMPEGVideo.dll
SOURCE="$(InputPath)"

"../../bin/Win32/Release/LMPEGVideo.ad" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ParseMap $(IntDir)/LMPEGVideo.map "../../bin/Win32/Debug/LMPEGVideo.typeinfo" "../../bin/Win32/Release/LMPEGVideo.ad"

# End Custom Build

!ENDIF 

# Begin Target

# Name "LMPEGVideo - Win32 Debug"
# Name "LMPEGVideo - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\LMPEGVideo\LMPEGVideo.cpp
# End Source File
# Begin Source File

SOURCE=.\LMPEGVideo.def
# End Source File
# Begin Source File

SOURCE=..\..\src\LMPEGVideo\LMPEGVideo.h

!IF  "$(CFG)" == "LMPEGVideo - Win32 Debug"

# Begin Custom Build
InputPath=..\..\src\LMPEGVideo\LMPEGVideo.h

"../../bin/Win32/Debug/LMPEGVideo.typeinfo" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	Test_gc $(InputPath) "../../bin/Win32/Debug/LMPEGVideo.typeinfo"

# End Custom Build

!ELSEIF  "$(CFG)" == "LMPEGVideo - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LMPEGVideo.rc
# End Source File
# Begin Source File

SOURCE=..\..\src\LMPEGVideo\MPEGVideoDecoder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LMPEGVideo\MPEGVideoDecoder.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LMPEGVideo\Picture.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LMPEGVideo\Picture.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LMPEGVideo\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\src\LMPEGVideo\stdafx.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LMPEGVideo\VideoSequence.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\LMPEGVideo\VideoSequence.h
# End Source File
# Begin Source File

SOURCE=..\..\src\LMPEGVideo\vlctables.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
