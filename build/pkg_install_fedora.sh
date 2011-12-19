#!/bin/sh
#
# @file pkg_install_fedora.sh
# @brief OpenRTM-aist dependent packages install script for Fedora
# @author Noriaki Ando <n-ando@aist.go.jp>
#         Shinji Kurihara
#         Tetsuo Ando
#
# ���Υ����륹����ץȤϡ�ace�����omniORB�Υѥå������򥤥󥹥ȡ��뤷��
# fedora�γ�ȯ�Ķ����ۤ��ޤ���
#
# $Id$
#

#---------------------------------------
# �ѥå������ꥹ��
#---------------------------------------
omni="omniORB omniORB-devel omniORB-doc omniORB-servers omniORB-utils omniORB-bootscripts"
openrtm="OpenRTM-aist OpenRTM-aist-devel OpenRTM-aist-doc OpenRTM-aist-example PyYAML"
packages="gcc-c++ $omni $openrtm"


#----------------------------------------
# root ���ɤ���������å�
#----------------------------------------
check_root () {
    if test ! `id -u` = 0 ; then
	echo ""
	echo "This script should be run by root user."
	echo "Abort."
	echo ""
	exit 1
    fi
}

#---------------------------------------
# ���󥹥ȡ���ѥѥå������ꥹ��
#---------------------------------------
rpm_qa="/tmp/yum_list.txt"
get_pkg_list () {
    rpm -qa > $rpm_qa
}
clean_pkg_list () {
    rm -f $rpm_qa
}

#---------------------------------------
# ��ݥ��ȥꥵ��������ե����������
#---------------------------------------
openrtm_repo () {
cat <<EOF
[openrtm]
name=Fedora \$releasever - \$basearch
failovermethod=priority
baseurl=http://www.openrtm.org/pub/Linux/Fedora/releases/\$releasever/Fedora/\$basearch/os/Packages
enabled=1
gpgcheck=0
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-fedora file:///etc/pki/rpm-gpg/RPM-GPG-KEY
EOF
} 
create_repo() {
    repo="/etc/yum.repos.d/openrtm.repo"
    if test ! -f $repo ; then
	echo "OpenRTM-aist �Υ�ݥ��ȥ꤬��Ͽ����Ƥ��ޤ���"
	echo "OpenRTM-aist �Υ�ݥ��ȥ�: "
	echo "  http://www.openrtm.org/pub/Linux/Fedora/"
	read -p "���ɲä��ޤ���������Ǥ����� (y/n) [y] " kick_shell

	if test "x$kick_shell" = "xn" ; then
	    echo "���Ǥ��ޤ���"
	    exit 0
	else
	    openrtm_repo > /etc/yum.repos.d/openrtm.repo
	fi
    fi
}

#----------------------------------------
# �ѥå��������󥹥ȡ���ؿ�
#----------------------------------------
install_packages () {
    for p in $*; do
	if test "x$p" = "x0.4.2" || test "x$p" = "x0.4.2" ; then
	    :
	else
	    if echo "$p" | grep -q '=0.4.2' ; then
		str=`echo "$p" |sed 's/=0.4.2//'`
	    else 
		str="$p"
	    fi

	    ins=`rpm -qa $str`

	    if test "x$ins" = "x"; then
		echo "Now installing: " $p
		yum install $p
		echo "done."
		echo ""
	    else  
		if echo "$ins" |grep -q '0.4.2-0' ; then
			yum install $p
			echo "done." 
			echo ""
	       else 
 		    echo $ins
		    echo $str "is already installed."
		    echo ""
		fi
	    fi
	fi
    done
}


#------------------------------------------------------------
# �ꥹ�Ȥ�ս�ˤ���
#------------------------------------------------------------
reverse () {
    for i in $*; do
	echo $i
    done | sed '1!G;h;$!d'
}

#----------------------------------------
# �ѥå������򥢥󥤥󥹥ȡ��뤹��
#----------------------------------------
uninstall_packages () {
    for p in $*; do
	echo "Now uninstalling: " $p
	yum erase $p
	echo "done."
	echo ""
    done
}

#---------------------------------------
# �ᥤ��
#---------------------------------------
check_root
if test "x$1" = "x-u" ; then
    uninstall_packages `reverse $packages`
else
    create_repo
    install_packages $packages
fi
