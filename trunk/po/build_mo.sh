#!/bin/sh
#builds message catalogs
#found in the current dir
#

CATALOGS=`ls *.po`
for ll in $CATALOGS;do
	echo "$ll: "
	msgfmt -v -o `echo $ll | sed s/.po/.mo/` $ll
done
