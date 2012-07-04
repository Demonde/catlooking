#!/bin/sh

DEST=$1

rm -rf $DEST
mkdir -p $DEST
cp *.h $DEST
cp *.cpp $DEST
cp *.qrc $DEST
cp CHANGES $DEST
cp COPYING $DEST
cp INSTALL $DEST
cp README.md $DEST
cp catlooking.ico $DEST
#cp catlooking.nsis $DEST
cp catlooking.pro $DEST
cp catlooking.rc $DEST
cp -R debian $DEST
cp -R packaging $DEST
cp -R resources $DEST
