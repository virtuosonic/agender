#!/bin/sh
#
#this script builds a bundle and creates
#a dmg disk image (i hope)
#

cd ../
#locales
cd po/
linguas=`ls *.po|sed s/.po//`
cd ..
#version
APPNAME="Agender"
VERSION="2.0"

bakefile -f autoconf Agender.bkl
bakefilize
aclocal
autoconf

#./configure --with-wx-config=wx-config
./configure $@
make

#copy exe
mkdir -p "$APPNAME.app/Contents/MacOS"
cp "$APPNAME" "$APPNAME.app/Contents/MacOS/"

#
cp "Info.plist" "$APPNAME.app/Contents/"

# ico
mkdir -p "$APPNAME.app/Resources/"
cp "share/$APPNAME.icns" "$APPNAME.app/Resources/"

#
function cp_catalog {
	mkdir -p "$APPNAME.app/Resources/$1.lproj/"
	cp "po/$1.mo" "$APPNAME.app/Resources/$1.lproj/$APPNAME.mo"
}

#copy message catalogs
for l in linguas;do
	cp_catalog $l;
done;

/Developer/Tools/SetFile -a B "$APPNAME.app/"


#disk image
echo "creating disk image..."
hdiutil create $APPNAME-$VERSION.dmg -volname $APPNAME-$VERSION \
	-type UDIF -megabytes 20 -fs HFS+
echo "mounting disk image..."
MYDEV=`hdiutil attach $APPNAME-$VERSION.dmg|tail -n 1|awk '{print $1}'`
echo "Device is $MYDEV"
echo "Copying to disk image..."
ditto --rsrc $APPNAME.app /Volumes/$APPNAME-$VERSION
echo "unmounting disk image..."
hdiutil convert $APPNAME-$VERSION.dmg -format UDZO -o $APPNAME-$VERSION-compresed.dmg
echo "Internet enabling the disk image..."
hdiutil internet-enable $APPNAME-$VERSION-compresed.dmg
echo "Renaming..."
rm -f $APPNAME-$VERSION.dmg
mv  $APPNAME-$VERSION-compresed.dmg $APPNAME-$VERSION.dmg
