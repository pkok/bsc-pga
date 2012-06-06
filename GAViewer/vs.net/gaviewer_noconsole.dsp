# Microsoft Developer Studio Project File - Name="gaviewer_noconsole" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=gaviewer_noconsole - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gaviewer_noconsole.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gaviewer_noconsole.mak" CFG="gaviewer_noconsole - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gaviewer_noconsole - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "gaviewer_noconsole - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gaviewer_noconsole - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "gaviewer_noconsole___Win32_Release"
# PROP BASE Intermediate_Dir "gaviewer_noconsole___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "gaviewer_noconsole___Win32_Release"
# PROP Intermediate_Dir "gaviewer_noconsole___Win32_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "WIN32_NO_CONSOLE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  opengl32.lib wsock32.lib fltk.lib glu32.lib fltkgl.lib comctl32.lib libpng.lib zlib.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "gaviewer_noconsole - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "gaviewer_noconsole___Win32_Debug"
# PROP BASE Intermediate_Dir "gaviewer_noconsole___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "gaviewer_noconsole___Win32_Debug"
# PROP Intermediate_Dir "gaviewer_noconsole___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "WIN32_NO_CONSOLE" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  opengl32.lib wsock32.lib fltkd.lib glu32.lib fltkgld.lib comctl32.lib libpngd.lib zlibd.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "gaviewer_noconsole - Win32 Release"
# Name "gaviewer_noconsole - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\basisvectors.cpp
# End Source File
# Begin Source File

SOURCE=..\algebras\c3ga_gaviewer\c3ga.cpp
# End Source File
# Begin Source File

SOURCE=..\algebras\c3ga_gaviewer\c3ga_optc.cpp
# End Source File
# Begin Source File

SOURCE=.\c3gaobject.cpp
# End Source File
# Begin Source File

SOURCE=.\consolewindow.cpp
# End Source File
# Begin Source File

SOURCE=.\draw.cpp
# End Source File
# Begin Source File

SOURCE=..\algebras\e3ga_gaviewer\e3ga.cpp
# End Source File
# Begin Source File

SOURCE=..\algebras\e3ga_gaviewer\e3ga_optc.cpp
# End Source File
# Begin Source File

SOURCE=.\e3gaobject.cpp
# End Source File
# Begin Source File

SOURCE=.\fl_console.cpp
# End Source File
# Begin Source File

SOURCE=.\gafile.cpp
# End Source File
# Begin Source File

SOURCE=.\geosphere.cpp
# End Source File
# Begin Source File

SOURCE=.\glwindow.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\mainwindow.cpp
# End Source File
# Begin Source File

SOURCE=.\meshobject.cpp
# End Source File
# Begin Source File

SOURCE=.\mvint.cpp
# End Source File
# Begin Source File

SOURCE=.\mvintc3ga.cpp
# End Source File
# Begin Source File

SOURCE=.\mvinte3ga.cpp
# End Source File
# Begin Source File

SOURCE=.\object.cpp
# End Source File
# Begin Source File

SOURCE=.\osdep.cpp
# End Source File
# Begin Source File

SOURCE=..\algebras\p3ga_gaviewer\p3ga.cpp
# End Source File
# Begin Source File

SOURCE=..\algebras\p3ga_gaviewer\p3ga_optc.cpp
# End Source File
# Begin Source File

SOURCE=.\pngwrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\polygonobject.cpp
# End Source File
# Begin Source File

SOURCE=.\selectwindow.cpp
# End Source File
# Begin Source File

SOURCE=.\softpic.cpp
# End Source File
# Begin Source File

SOURCE=.\state.cpp
# End Source File
# Begin Source File

SOURCE=.\textobject.cpp
# End Source File
# Begin Source File

SOURCE=.\ui.cpp
# End Source File
# Begin Source File

SOURCE=.\util.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\basisvectors.h
# End Source File
# Begin Source File

SOURCE=..\algebras\c3ga_gaviewer\c3ga.h
# End Source File
# Begin Source File

SOURCE=.\consolewindow.h
# End Source File
# Begin Source File

SOURCE=.\draw.h
# End Source File
# Begin Source File

SOURCE=..\algebras\e3ga_gaviewer\e3ga.h
# End Source File
# Begin Source File

SOURCE=.\gafile.h
# End Source File
# Begin Source File

SOURCE=.\geosphere.h
# End Source File
# Begin Source File

SOURCE=.\glwindow.h
# End Source File
# Begin Source File

SOURCE=.\mainwindow.h
# End Source File
# Begin Source File

SOURCE=.\mvint.h
# End Source File
# Begin Source File

SOURCE=.\object.h
# End Source File
# Begin Source File

SOURCE=.\osdep.h
# End Source File
# Begin Source File

SOURCE=..\algebras\p3ga_gaviewer\p3ga.h
# End Source File
# Begin Source File

SOURCE=.\selectwindow.h
# End Source File
# Begin Source File

SOURCE=.\softpic.h
# End Source File
# Begin Source File

SOURCE=.\state.h
# End Source File
# Begin Source File

SOURCE=.\uistate.h
# End Source File
# Begin Source File

SOURCE=.\util.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "typeset files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\typeset\fontdata.cpp
# End Source File
# Begin Source File

SOURCE=.\typeset\fontdata.h
# End Source File
# Begin Source File

SOURCE=.\typeset\fontlex.c
# End Source File
# Begin Source File

SOURCE=.\typeset\fontparse.cpp
# End Source File
# Begin Source File

SOURCE=.\typeset\fontparse.h
# End Source File
# Begin Source File

SOURCE=.\typeset\fontyacc.c
# End Source File
# Begin Source File

SOURCE=.\typeset\fontyacc.h
# End Source File
# Begin Source File

SOURCE=.\typeset\liststack.h
# End Source File
# Begin Source File

SOURCE=.\typeset\openglfont.cpp
# End Source File
# Begin Source File

SOURCE=.\typeset\openglfont.h
# End Source File
# Begin Source File

SOURCE=.\typeset\typeset.cpp
# End Source File
# Begin Source File

SOURCE=.\typeset\typeset.h
# End Source File
# Begin Source File

SOURCE=.\typeset\typesetbox.cpp
# End Source File
# Begin Source File

SOURCE=.\typeset\typesetbox.h
# End Source File
# End Group
# End Target
# End Project
