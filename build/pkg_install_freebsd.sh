#!/bin/sh
#
# @file pkg_install_freebsd6.sh
# @brief OpenRTM-aist dependent packages install script for FreeBSD-6
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: pkg_install_freebsd6.sh 726 2008-05-14 03:05:42Z n-ando $
#

PACKAGEROOT='ftp://ftp.jp.freebsd.org'
export PACKAGEROOT

omni="omniORB"
omniorbpy="py24-omniorb py24-tkinter"
ace="ace+tao"
autotools="autoconf259 automake19 libtool"
packages="$omni $ace"

#----------------------------------------
# root ���ǂ������`�F�b�N
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

#----------------------------------------
# �p�b�P�[�W�C���X�g�[���֐�
#----------------------------------------
install_packages () {
    for p in $*; do
	ins=`rpm -qa $p`
	if test "x$ins" = "x"; then
	    echo "Now installing: " $p
	    pkg_add -r install $p
	    echo "done."
	    echo ""
	else
	    echo $p "is already installed."
	    echo ""
	fi
    done
}

#------------------------------------------------------------
# ���X�g���t���ɂ���
#------------------------------------------------------------
reverse () {
    for i in $*; do
	echo $i
    done | sed '1!G;h;$!d'
}

#----------------------------------------
# �p�b�P�[�W���A���C���X�g�[������
#----------------------------------------
uninstall_packages () {
    for p in $*; do
	echo "Now uninstalling: " $p
	pkg_delete $p
	echo "done."
	echo ""
    done
}

#---------------------------------------
# ���C��
#---------------------------------------
check_root
if test "x$1" = "x-u" ; then
    uninstall_packages `reverse $packages`
else
    create_repo
    install_packages $packages
fi
