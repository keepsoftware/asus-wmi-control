#!/bin/sh
VERSION=`uname -r | grep -o '^[0-9]\+\.[0-9]\+'`
VERSION="6.0"

wget "https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/plain/drivers/platform/x86/asus-wmi.c?h=linux-$VERSION.y" -O './orig/asus-wmi.c'
wget "https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/plain/drivers/platform/x86/asus-wmi.h?h=linux-$VERSION.y" -O './orig/asus-wmi.h'
wget "https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/plain/drivers/platform/x86/asus-nb-wmi.c?h=linux-$VERSION.y" -O './orig/asus-nb-wmi.c'
#wget "https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/plain/drivers/platform/x86/asus-wireless.c?h=linux-$VERSION.y" -O './orig/asus-wireless.c'

cd new
cp -a ../orig/* .
cd ..

if { echo $VERSION ; echo "5.7" ; } | sort -V -c 2>/dev/null
then
  PATCHFILE="patch"
elif { echo $VERSION ; echo "5.18" ; } | sort -V -c 2>/dev/null
  PATCHFILE="patch5.18"
elif { echo $VERSION ; echo "6.0" ; } | sort -V -c 2>/dev/null
  PATCHFILE="patch6.0"
fi

echo "Using: $PATCHFILE"



#wget "https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/plain/drivers/platform/x86/asus-wmi.c" -O 'asus-wmi.c'
#wget "https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/plain/drivers/platform/x86/asus-wmi.h" -O 'asus-wmi.h'
#wget "https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/plain/drivers/platform/x86/asus-nb-wmi.c" -O 'asus-nb-wmi.c'
patch -p1 < $PATCHFILE
rm *.orig
