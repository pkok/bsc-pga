dnl Process this file with autoconf to produce a configure script.
AC_INIT()
AM_INIT_AUTOMAKE(GAViewer, 0.86)
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB
AQSIS_CHECK_FLTK

AC_CHECK_FILE(/usr/lib64/libantlr.a, ANTLR_LIBS="/usr/lib64/libantlr.a", )
AC_CHECK_FILE(/usr/local/lib64/libantlr.a, ANTLR_LIBS="/usr/local64/lib/libantlr.a", )
AC_CHECK_FILE(/usr/lib/libantlr.a, ANTLR_LIBS="/usr/lib/libantlr.a", )
AC_CHECK_FILE(/usr/local/lib/libantlr.a, ANTLR_LIBS="/usr/local/lib/libantlr.a", )
AC_SUBST([ANTLR_LIBS])

dnl 
dnl AC_CHECK_FILE(/usr/lib64/libantlr.a, ANTLR_LIBS="/usr/lib64/libantlr.a", 
dnl AC_CHECK_FILE(/usr/local/lib/libantlr.a, ANTLR_LIBS="/usr/local/lib/libantlr.a", 
dnl AC_CHECK_FILE(/usr/lib/libantlr.a, ANTLR_LIBS="/usr/lib/libantlr.a", 
dnl AC_CHECK_FILE(/opt/local/lib/libantlr.a, ANTLR_LIBS="/opt/local/lib/libantlr.a", -lantlr))))
dnl AC_CHECK_FILE(/usr/local/lib/libpng.a, PNG_LIBS="/usr/local/lib/libpng.a", AC_CHECK_FILE(/usr/lib/libpng.a, PNG_LIBS="/usr/lib/libpng.a", AC_CHECK_FILE(/opt/local/lib/libpng.a, PNG_LIBS="/opt/local/lib/libpng.a", -lpng)))
dnl AC_CHECK_FILE(/usr/local/lib/libz.a, Z_LIBS="/usr/local/lib/libz.a", AC_CHECK_FILE(/usr/lib/libz.a, Z_LIBS="/usr/lib/libz.a", AC_CHECK_FILE(/opt/local/lib/libz.a, Z_LIBS="/opt/local/lib/libz.a", -lz)))
AC_OUTPUT(Makefile \
 src/console/Makefile src/console/codegen/Makefile src/typeset/Makefile \
 src/c3ga/Makefile src/c5ga/Makefile src/p3ga/Makefile src/e3ga/Makefile src/i2ga/Makefile \
 src/Makefile vs.net/Makefile vs.2005/Makefile vs2008/Makefile txtfiles/Makefile)
