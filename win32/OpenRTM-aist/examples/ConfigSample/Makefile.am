## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/ConfigSample
##
## $Id: Makefile.am 2107 2011-05-23 02:54:49Z n-ando $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.idl *.conf
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo
	rm -rf ConfigSample ConfigSampleComp

src:
	cp -p $(top_srcdir)/examples/ConfigSample/*.cpp .
	cp -p $(top_srcdir)/examples/ConfigSample/*.h .
	cp -p $(top_srcdir)/examples/ConfigSample/*.conf .
	qkc -ms *.cpp
	qkc -ms *.h
	qkc -ms *.conf

dist-hook: src
