SUBDIRS = codegen

noinst_LIBRARIES = libconsole.a

EXTRA_DIST = \
        ConsoleLexer.g extratokentypes.txt consolecodetemplates.txt  \
        consolelexertokentypes.txt console.txt consoleparsertokentypes.txt \
        ConsoleParser.g

libconsole_a_SOURCES = \
        ConsoleLexer.cpp consoleautocolor.cpp   consolestatement.cpp  consolewindow.cpp \
        consolefunctions.cpp console.cpp consolecontrol.cpp consolegafile.cpp \
        consoleoperators.cpp consolescope.cpp consoletest.cpp ConsoleParser.cpp \
        consolevariable.cpp fl_console.cpp consoledynstmt.cpp consolegeneratedfunctions.cpp \
        consolesourcefileread.cpp
	

noinst_HEADERS = ConsoleParser.hpp consolefunction.h ConsoleLexerTokenTypes.hpp \
        consoleparserwrapper.h ConsoleLexer.hpp consolestatement.h consolewindow.h \
        console.h consolecontrol.h consolegafile.h consoleoperators.h consolescope.h \
        ConsoleParserTokenTypes.hpp consolevariable.h fl_console.h
