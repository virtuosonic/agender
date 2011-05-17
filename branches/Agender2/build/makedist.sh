#!/bin/sh
#
#builds a source package of Agender
#

#error reporting
function check_error() {
	if [ $1 != 0 ];then
		echo $2
		exit 1
	fi
}
#clean the especified wildcards
function clean_dist() {
	for wc in $1;do
		find . -depth -name $wc -exec rm -fr {} \;
	done
}
#constants
VERSION="2.0"
cd ..
AgROOT=`pwd`
DISTROOT="Agender-$VERSION"
#make a copy
cd ..
mkdir "$DISTROOT"
check_error $? "error creating dir"

cp -r -T "$AgROOT" "$DISTROOT/"
check_error $? "error copying dir"
cd "$DISTROOT"
check_error $? "error changing dir"

#buid makefiles
cd "build"
bakefile_gen
check_error $? "error generating bakefile"
cd ..
#cleanup the copy
clean_dist "*.svn
	obj
	bin
	*.exe
	*.bz2
	*.layout
	*.depend
	*.bak
	*.idb
	*.pdb
	.bakefile_gen.state
	Thumbs.db
	*.o
	*.obj"
cd ..
#compress
tar -cjf "$AgROOT/$DISTROOT.tar.bz2" "$DISTROOT"
7z a "$AgROOT/$DISTROOT.7z" "$DISTROOT"
#delete
rm -rf "$DISTROOT"
#back
cd `dirname $0`
