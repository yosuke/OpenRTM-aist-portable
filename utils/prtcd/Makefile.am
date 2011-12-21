## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile for prtcd: Portable RT-Component Manager
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

ORB = @ORB@
IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@

bin_SCRIPTS = prtcc

prtcc: prtcc.in
	echo '#!/bin/sh' > $@
	echo '' >> $@
	echo 'rtm_cflags="'${CXXFLAGS}' -I'${prefix}'/include -I'${coil_includedir}' -I'${rtm_includedir}' -I'${rtm_includedir}'/rtm/idl"' >> $@
	echo 'rtm_libs="'${LDFLAGS}' -L'${prefix}'/lib '${LIBS}' -lRTC -lcoil"' >> $@
	cat prtcc.in >> $@
	chmod 755 $@

EXTRA_DIST = \
	prtcc.in

clean-local:
	rm -f prtcc
	rm -rf *~ *core
