#!/bin/sh
#
#builds a source package of Agender
#

VERSION="2.0"
AgROOT=`pwd`
DISTROOT="Agender-$VERSION"

cd ..
mkdir "$DISTROOT"
cp -r -T "$AgROOT" "$DISTROOT/"
cd "$DISTROOT"

./update_revision.sh
bakefile -I"$WXWIN/build/bakefiles/wxpresets" -f autoconf Agender.bkl
bakefilize
aclocal
autoconf

find . -depth -name "*.svn" -exec rm -fr {} \;
find . -depth -name "obj" -exec rm -fr {} \;
find . -depth -name "bin" -exec rm -fr {} \;
find . -depth -name "*.exe" -exec rm -fr {} \;
find . -depth -name "*.bz2" -exec rm -fr {} \;
cd ..

tar -cjf "$AgROOT/$DISTROOT.tar.bz2" "$DISTROOT"
#rm -rf "$DISTROOT"

cd "$AgROOT"
