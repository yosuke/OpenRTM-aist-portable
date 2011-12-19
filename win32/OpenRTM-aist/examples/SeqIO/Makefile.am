## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/SeqIO
##
## $Id: Makefile.am 2107 2011-05-23 02:54:49Z n-ando $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.idl rtc.conf
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo
	rm -rf SeqIn SeqInComp SeqOut SeqOutComp

src:
	cp -p $(top_srcdir)/examples/SeqIO/*.cpp .
	cp -p $(top_srcdir)/examples/SeqIO/*.h .
	cp -p $(top_srcdir)/examples/SeqIO/rtc.conf .
	qkc -ms *.cpp
	qkc -ms *.h

dist-hook: src
