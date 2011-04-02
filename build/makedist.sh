#!/bin/sh
#
#builds a source package of Agender
#

VERSION="2.0"
cd ..
AgROOT=`pwd`
DISTROOT="Agender-$VERSION"

cd ..
mkdir "$DISTROOT"
cp -r -T "$AgROOT" "$DISTROOT/"
cd "$DISTROOT"
if [ $? != 0];then
	echo "error creating dir"
	exit
fi

./build/update_revision.sh
bakefile -o "./Makefile.in" -I"$WXWIN/build/bakefiles/wxpresets" -f autoconf "build/Agender.bkl"
bakefilize
aclocal
autoconf -o "./configure" "build/configure.in"

find . -depth -name "*.svn" -exec rm -fr {} \;
find . -depth -name "obj" -exec rm -fr {} \;
find . -depth -name "bin" -exec rm -fr {} \;
find . -depth -name "*.exe" -exec rm -fr {} \;
find . -depth -name "*.bz2" -exec rm -fr {} \;
find . -depth -name "*.layout" -exec rm -fr {} \;
find . -depth -name "*.depend" -exec rm -fr {} \;
find . -depth -name "*.bak" -exec rm -fr {} \;
find . -depth -name "*.idb" -exec rm -fr {} \;
find . -depth -name "*.pdb" -exec rm -fr {} \;
cd ..

tar -cjf "$AgROOT/$DISTROOT.tar.bz2" "$DISTROOT"
rm -rf "$DISTROOT"

cd "$AgROOT"
cd build
