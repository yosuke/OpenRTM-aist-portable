## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/SimpleService
##
## $Id: Makefile.am 2107 2011-05-23 02:54:49Z n-ando $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.hh *.cc *.idl rtc.conf
	rm -rf *.vcproj *vcxproj *.user *.ncb *.suo
	rm -rf MyServiceProvider MyServiceProviderComp
	rm -rf MyServiceConsumer MyServiceConsumerComp

src:
	cp -p $(top_srcdir)/examples/SimpleService/*.cpp .
	cp -p $(top_srcdir)/examples/SimpleService/*.h .
	cp -p $(top_srcdir)/examples/SimpleService/*.idl .
	cp -p $(top_srcdir)/examples/SimpleService/rtc.conf .
	qkc -ms *.cpp
	qkc -ms *.h
	qkc -ms *.idl

dist-hook: src
