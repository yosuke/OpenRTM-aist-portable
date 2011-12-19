## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/rtm/idl
##
## $Id: Makefile.am 2108 2011-05-23 03:00:57Z n-ando $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -f *~ *.idl *.cpp *.h *.cc *.hh
	rm -f *.sln *.suo *.ncb *.user *.vcproj *.vcxproj

src:
	cp -p $(top_srcdir)/src/lib/rtm/idl/*.idl .
	qkc -ms *.idl


dist-hook: src
