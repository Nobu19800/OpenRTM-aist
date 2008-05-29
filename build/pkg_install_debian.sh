#!/bin/sh
#
# @file pkg_install_debianSarge.sh
# @brief OpenRTM-aist dependent packages install script for Debian-sarge
# @author Noriaki Ando <n-ando@aist.go.jp> and Shinji Kurihara
#

#---------------------------------------
# �p�b�P�[�W���X�g
#---------------------------------------
omni="libomniorb4 libomniorb4-de omniidl4 omniorb4-nameserver"
ace="libace libace-dev"
openrtm="python-yaml"
devel="gcc g++ make"
packages="$devel $omni $ace $openrtm"

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
	echo "Now installing: " $p
	apt-get install $p
	echo "done."
	echo ""
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
	aptitude remove $p
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
    install_packages $packages
fi

