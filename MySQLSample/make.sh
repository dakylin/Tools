#!/bin/bash
ROOTPATH=/daniel/src

STKPATH=$ROOTPATH/MySQLSample/stk

filelist=`ls $STKPATH`
for file in $filelist
do
	CURRENTPATH=${STKPATH}/$file
	if [ ! -f $CURRENTPATH ]
	then
		cd ${CURRENTPATH}
		make clean
		make
	fi
done

APPPATH=$ROOTPATH/MySQLSample/app
appfilelist=`ls $APPPATH`
for file in $appfilelist
do
	CURRENTPATH=${APPPATH}/$file
	if [ ! -f $CURRENTPATH ]
	then
		cd ${CURRENTPATH}
		make clean
		make
	fi
done
