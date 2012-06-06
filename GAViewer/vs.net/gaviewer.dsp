# Microsoft Developer Studio Project File - Name="gaviewer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=gaviewer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gaviewer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gaviewer.mak" CFG="gaviewer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gaviewer - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "gaviewer - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "gaviewer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /Zm200 /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib wsock32.lib fltk.lib glu32.lib fltkgl.lib comctl32.lib libpng.lib zlib.lib antlr.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "gaviewer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /Zm200 /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib ws2_32.lib fltkd.lib glu32.lib fltkgld.lib comctl32.lib libpngd.lib zlibd.lib antlrd.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "gaviewer - Win32 Release"
# Name "gaviewer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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

SOURCE=.\draw.cpp
# End Source File
# Begin Source File

SOURCE=.\dynamicstatementwindow.cpp
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

SOURCE=.\gafile.cpp
# End Source File
# Begin Source File

SOURCE=.\geosphere.cpp
# End Source File
# Begin Source File

SOURCE=.\glwindow.cpp
# End Source File
# Begin Source File

SOURCE=..\algebras\i2ga_gaviewer\i2ga.cpp
# End Source File
# Begin Source File

SOURCE=..\algebras\i2ga_gaviewer\i2ga_optc2.cpp
# End Source File
# Begin Source File

SOURCE=.\i2gaobject.cpp
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

SOURCE=.\mvinti2ga.cpp
# End Source File
# Begin Source File

SOURCE=.\mvintp3ga.cpp
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

SOURCE=.\p3gaobject.cpp
# End Source File
# Begin Source File

SOURCE=.\pngwrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\polygonobject.cpp
# End Source File
# Begin Source File

SOURCE=.\screenshot.cpp
# End Source File
# Begin Source File

SOURCE=.\screenshotdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\selectwindow.cpp
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
# Begin Source File

SOURCE=.\writestate.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\algebras\c3ga_gaviewer\c3ga.h
# End Source File
# Begin Source File

SOURCE=.\draw.h
# End Source File
# Begin Source File

SOURCE=.\dynamicstatementwindow.h
# End Source File
# Begin Source File

SOURCE=..\algebras\e3ga_gaviewer\e3ga.h
# End Source File
# Begin Source File

SOURCE=.\gafile.h
# End Source File
# Begin Source File

SOURCE=.\gaincludes.h
# End Source File
# Begin Source File

SOURCE=.\geosphere.h
# End Source File
# Begin Source File

SOURCE=.\glwindow.h
# End Source File
# Begin Source File

SOURCE=..\algebras\i2ga_gaviewer\i2ga.h
# End Source File
# Begin Source File

SOURCE=.\mainwindow.h
# End Source File
# Begin Source File

SOURCE=.\models.h
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

SOURCE=.\pngwrapper.h
# End Source File
# Begin Source File

SOURCE=.\screenshotdialog.h
# End Source File
# Begin Source File

SOURCE=.\selectwindow.h
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
# Begin Group "typeset"

# PROP Default_Filter ""
# Begin Group "h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\typeset\fontdata.h
# End Source File
# Begin Source File

SOURCE=.\typeset\fontparse.h
# End Source File
# Begin Source File

SOURCE=.\typeset\fontyacc.h
# End Source File
# Begin Source File

SOURCE=.\typeset\liststack.h
# End Source File
# Begin Source File

SOURCE=.\typeset\openglfont.h
# End Source File
# Begin Source File

SOURCE=.\typeset\typeset.h
# End Source File
# Begin Source File

SOURCE=.\typeset\typesetbox.h
# End Source File
# End Group
# Begin Group "cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\typeset\fontdata.cpp
# End Source File
# Begin Source File

SOURCE=.\typeset\fontlex.c
# End Source File
# Begin Source File

SOURCE=.\typeset\fontparse.cpp
# End Source File
# Begin Source File

SOURCE=.\typeset\fontyacc.c
# End Source File
# Begin Source File

SOURCE=.\typeset\openglfont.cpp
# End Source File
# Begin Source File

SOURCE=.\typeset\typeset.cpp
# End Source File
# Begin Source File

SOURCE=.\typeset\typesetbox.cpp
# End Source File
# End Group
# Begin Group "yacc files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\typeset\fontparse.l
# End Source File
# Begin Source File

SOURCE=.\typeset\fontparse.y
# End Source File
# End Group
# End Group
# Begin Group "geo files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\txt_files\2tims_smit2.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\asciifile.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\bivector.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\e3gaobjects.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\font_samples.geo
# End Source File
# Begin Source File

SOURCE=".\txt_files\ga-ogl-tmp1.geo"
# End Source File
# Begin Source File

SOURCE=.\txt_files\GABLE.gpl
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock1.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock10.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock11.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock12.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock13.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock14.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock15.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock16.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock2.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock3.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock4.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock5.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock6.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock7.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock8.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\GAblock9.geo
# End Source File
# Begin Source File

SOURCE=.\geo_files\labeltest.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\para_leo.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\scroller.geo
# End Source File
# Begin Source File

SOURCE=.\txt_files\steve_circle.geo
# End Source File
# Begin Source File

SOURCE=.\syntax.txt
# End Source File
# Begin Source File

SOURCE=.\txt_files\tims_smit.geo
# End Source File
# End Group
# Begin Group "console"

# PROP Default_Filter ""
# Begin Group "console_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\console\console.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consoleautocolor.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consolecontrol.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consoledynstmt.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consolefunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consolegafile.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consolegeneratedfunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\console\ConsoleLexer.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consoleoperators.cpp
# End Source File
# Begin Source File

SOURCE=.\console\ConsoleParser.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consolescope.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consolesourcefileread.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consolestatement.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consoletest.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consolevariable.cpp
# End Source File
# Begin Source File

SOURCE=.\console\consolewindow.cpp
# End Source File
# Begin Source File

SOURCE=.\console\fl_console.cpp
# End Source File
# End Group
# Begin Group "console_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\console\console.h
# End Source File
# Begin Source File

SOURCE=.\console\consolecontrol.h
# End Source File
# Begin Source File

SOURCE=.\console\consolefunction.h
# End Source File
# Begin Source File

SOURCE=.\console\consolegafile.h
# End Source File
# Begin Source File

SOURCE=.\console\ConsoleLexer.hpp
# End Source File
# Begin Source File

SOURCE=.\console\ConsoleLexerTokenTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\console\consoleoperators.h
# End Source File
# Begin Source File

SOURCE=.\console\consoleparse.h
# End Source File
# Begin Source File

SOURCE=.\console\ConsoleParser.hpp
# End Source File
# Begin Source File

SOURCE=.\console\ConsoleParserTokenTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\console\consoleparserwrapper.h
# End Source File
# Begin Source File

SOURCE=.\console\consolescope.h
# End Source File
# Begin Source File

SOURCE=.\console\consolestatement.h
# End Source File
# Begin Source File

SOURCE=.\console\consolevariable.h
# End Source File
# Begin Source File

SOURCE=.\console\consolewindow.h
# End Source File
# Begin Source File

SOURCE=.\console\fl_console.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\console\consolecodetemplates.txt

!IF  "$(CFG)" == "gaviewer - Win32 Release"

# Begin Custom Build
InputDir=.\console
InputPath=.\console\consolecodetemplates.txt
InputName=consolecodetemplates

"$(InputDir)/consolegeneratedfunctions.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd $(InputDir) 
	codegen $(InputName).txt consolegeneratedfunctions.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "gaviewer - Win32 Debug"

# Begin Custom Build
InputDir=.\console
InputPath=.\console\consolecodetemplates.txt
InputName=consolecodetemplates

"$(InputDir)\consolegeneratedfunctions.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(InputDir)\codegen $(InputDir)\$(InputName).txt $(InputDir)\consolegeneratedfunctions.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\console\ConsoleLexer.g

!IF  "$(CFG)" == "gaviewer - Win32 Release"

!ELSEIF  "$(CFG)" == "gaviewer - Win32 Debug"

# Begin Custom Build
InputDir=.\console
InputPath=.\console\ConsoleLexer.g
InputName=ConsoleLexer

BuildCmds= \
	cd $(InputDir) \
	del $(InputName).cpp \
	del $(InputName).hpp \
	java antlr.Tool  $(InputName).g \
	

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).hpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\console\ConsoleParser.g

!IF  "$(CFG)" == "gaviewer - Win32 Release"

# Begin Custom Build
InputDir=.\console
InputPath=.\console\ConsoleParser.g
InputName=ConsoleParser

BuildCmds= \
	cd $(InputDir) \
	del $(InputName).cpp \
	del $(InputName).hpp \
	java antlr.Tool  $(InputName).g \
	

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).hpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "gaviewer - Win32 Debug"

# Begin Custom Build
InputDir=.\console
InputPath=.\console\ConsoleParser.g
InputName=ConsoleParser

BuildCmds= \
	cd $(InputDir) \
	del $(InputName).cpp \
	del $(InputName).hpp \
	java antlr.Tool  $(InputName).g \
	

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).hpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\how_to_add_algebra.txt
# End Source File
# End Target
# End Project
