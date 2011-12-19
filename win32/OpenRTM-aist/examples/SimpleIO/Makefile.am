## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/SimpleIO
##
## $Id: Makefile.am 2107 2011-05-23 02:54:49Z n-ando $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.idl rtc.conf
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo
	rm -rf ConsoleIn ConsoleInComp ConsoleOut ConsoleOutComp

src:
	cp -p $(top_srcdir)/examples/SimpleIO/*.cpp .
	cp -p $(top_srcdir)/examples/SimpleIO/*.h .
	cp -p $(top_srcdir)/examples/SimpleIO/rtc.conf .
	qkc -ms *.cpp
	qkc -ms *.h

dist-hook: src
