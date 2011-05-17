#!/bin/sh
#install message catalogs
#found in the current dir
#

CATALOGS=`ls *.mo`
PREFIX="/usr"
CATALOG_NAME="Agender"
for ll in $CATALOGS;do
	echo " installing $ll"
	cat_locale=`echo $ll | sed s/.mo//`
	cp $ll "$PREFIX/share/locale/$cat_locale/LC_MESSAGES/$CATALOG_NAME.mo"
done
