SUBDIRS = console typeset c3ga p3ga e3ga i2ga c5ga

bin_PROGRAMS = gaviewer

AM_CPPFLAGS = $(GL_CFLAGS) $(AQSIS_FLTK_GL_CFLAGS) -I/opt/local/include 
	
gaviewer_LDADD = \
        console/libconsole.a typeset/libtypeset.a \
        c5ga/libc5ga.a c3ga/libc3ga.a i2ga/libi2ga.a p3ga/libp3ga.a e3ga/libe3ga.a \
        $(AQSIS_FLTK_GL_LIBS) \
	     $(ANTLR_LIBS) -lpng -lz

        
gaviewer_SOURCES = \
	main.cpp draw.cpp gafile.cpp glwindow.cpp osdep.cpp \
        mainwindow.cpp mvintc3ga.cpp mvintc5ga.cpp netserver.cpp polygonobject.cpp \
        softpic.cpp dynamicstatementwindow.cpp mvinte3ga.cpp ui.cpp \
        mvinti2ga.cpp object.cpp screenshot.cpp state.cpp \
        i2gaobject.cpp meshobject.cpp mvintp3ga.cpp \
        p3gaobject.cpp screenshotdialog.cpp util.cpp c3gaobject.cpp c5gaobject.cpp \
        geosphere.cpp textobject.cpp conformalobject.cpp \
        e3gaobject.cpp mvint.cpp netclient.cpp \
        pngwrapper.cpp selectwindow.cpp tubedraw.cpp writestate.cpp \
        mt19937-2.cpp
 
noinst_HEADERS = \
	draw.h mvint.h netclient.h pngwrapper.h selectwindow.h  tubedraw.h \
        gafile.h glwindow.h osdep.h gaincludes.h mainwindow.h netserver.h \
        resource.h softpic.h dynamicstatementwindow.h uistate.h object.h \
        state.h models.h mypng.h screenshotdialog.h util.h geosphere.h \
        openglfont.h gl_includes.h mt19937-2.h c3gadraw.h
        

EXTRA_DIST = c5ga.gas c3ga.gas e3ga.gas p3ga.gas i2ga.gas gaviewer.rc gaviewer.xbm icon1.ico
        
