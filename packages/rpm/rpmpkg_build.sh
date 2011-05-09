#!/bin/sh 

export PATH=/usr/local/bin:/usr/bin:/bin:/usr/X11R6/bin:/usr/local/X11R6/bin:/usr/local/sbin:/usr/sbin:/sbin
export LANG=C
export LC_ALL=C

version="1.1.0"
packagename="OpenRTM-aist$version"
tarballname=$packagename-RELEASE

# system information
hostname=`hostname`
os=`uname -s`
release=`uname -r`-`uname -p`

dist_name=""
dist_key=""
# Check the lsb distribution name
if test -f /etc/lsb-release ; then
    . /etc/lsb-release
    if test "x$DISTRIB_DESCRIPTION" != "x" ; then
	dist_name=$DISTRIB_DESCRIPTION-`uname -m`
    fi
fi
# Check the Fedora version
if test "x$dist_name" = "x" && test -f /etc/fedora-release ; then
    dist_name=`cat /etc/fedora-release`-`uname -m`
    dist_key=`sed -e 's/.[^0-9]*\([0-9]\+\).*/fc\1/' /etc/fedora-release`
fi
#Check the Debian version
if test "x$dist_name" = "x" && test -f /etc/debian_version ; then
    dist_name="Debian"`cat /etc/debian_version`-`uname -m`
    dist_key=""
fi
# Check the Vine version
if test "x$dist_name" = "x" && test -f /etc/vine-release ; then
    dist_name=`cat /etc/vine-release`-`uname -m`
    dist_key=`sed -e 's/.*\([0-9]\)\.\([0-9]\).*/vl\1\2/' /etc/vine-release`
fi
# Check the TuboLinux version
if test "x$dist_name" = "x" && test -f /etc/turbolinux-release ; then
    dist_name=`cat /etc/tubolinux-release`-`uname -m`
    dist_key=""
fi

if test "x$dist_name" = "x" ; then
    dist_name=$os$release
fi
# Check the RedHat/Fedora version
if test "x$dist_name" = "x" && test -f /etc/redhat-release ; then
    dist_name=`cat /etc/redhat-release`-`uname -m`
fi

# only fedora and vine
if test "x$dist_key" = "x" ; then
    echo "This is not Feodra/Vine/Scientific/RedHat distribution"
    exit 0
fi

distname=`echo $dist_name | sed 's/[ |\(|\)]//g'`
# system dependent build directory and log file name

echo "distribution: " $dist_name

#------------------------------------------------------------
# package build process
#------------------------------------------------------------
mkdir {BUILD,RPMS,SOURCES,SPECS,SRPMS}
mkdir RPMS/{i386,i586,i686,x86_64,noarch}

# fake tar-ball is created under SOURCES dir
ln -s ../../../ $packagename
tar cvzf $tarballname $packagename
cp $tarballname SOURCES

#------------------------------------------------------------
# Selecting and adding dist key to the spec file
#
# Fedora12/13's omniORB package names are odd.
#------------------------------------------------------------
if test "x$dist_key" = "xfc12" || test "x$dist_key" = "xfc13" ; then
    cp OpenRTM-aist_libomniORB41.spec OpenRTM-aist.spec.tmp
    echo $dist_key
else
    cp OpenRTM-aist_omniORB.spec OpenRTM-aist.spec.tmp
    echo $dist_key
fi
sed "s/__DISTNAME__/$dist_key/g" OpenRTM-aist.spec.tmp > OpenRTM-aist.spec

#------------------------------------------------------------
# Copying spec file to SPEC and goto SPEC dir to build rpm
#------------------------------------------------------------
builddir=`pwd`
cp OpenRTM-aist.spec SPECS
cd SPECS
echo "%_topdir $builddir" > .rpmrc

# We have already extracted source under BUILD directory.
# %prep process can be skiped. = --short-circuit -bc
rpm_def="_topdir $builddir"
rpmbuild --define "$rpm_def" --short-circuit -bc OpenRTM-aist.spec
