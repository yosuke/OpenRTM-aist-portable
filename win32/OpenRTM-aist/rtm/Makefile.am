## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/rtm
##
## $Id: Makefile.am 2151 2011-05-31 00:23:51Z n-ando $
##---------------------------------------------------------------------------
SUBDIRS = idl .

RTM_VERSION = @RTM_VERSION@
RTM_SHORT_VERSION = @RTM_SHORT_VERSION@

clean-local:
	rm -rf Debug Release
	rm -f *~ *.cpp *.h *.cc *.hh version.txt
	rm -f *.sln *.suo *.ncb *.user *.vcproj *.vcxproj *.def

src:
	cp -p $(top_srcdir)/src/lib/rtm/*.cpp .
	cp -p $(top_srcdir)/src/lib/rtm/*.h .
	cp -p $(top_srcdir)/src/lib/rtm/version.txt .
	cp -p config_rtc.h.in config_rtc.h
	qkc -ms *.cpp
	qkc -ms *.h

dist-hook: src

EXTRA_DIST = config_rtc.h.in