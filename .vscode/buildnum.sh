#!/bin/sh
FILE=./source/pdxinfo
VERSION=$(cat $FILE | grep buildNumber | tr -dc '0-9')
NEW=$((VERSION+1))

sed -i .inplace "s/buildNumber=[0-9]*/buildNumber=$NEW/g" $FILE
if [ $? -eq 0 ]; then
   rm $FILE.inplace
   echo "Updating pdxinfo buildNumber: $VERSION -> $NEW"
else
   echo "Error updating build number."
   rm $FILE
   mv $FILE.inplace $FILE
   return 1
fi