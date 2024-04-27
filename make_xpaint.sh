#!/bin/bash
final="xpaint.ho"
temp="full.hh"

htemp="xpaint.hh"
ctemp="xpaint.cc"

hfile="xpaint.h"
cfile="xpaint.c"

mdpp Readme.md

cd src/xpaint
echo "#ifndef XPAINT_H" > $temp
echo "#define XPAINT_H" >> $temp

echo "#ifdef __cplusplus" >> $temp
echo "extern \"C\" {"  >> $temp
echo "#endif" >> $temp

cat aintro.h color.h base.h draw.h text.h xmath.h modules.h >> $temp

echo "#ifdef __cplusplus" >> $temp
echo "}"  >> $temp
echo "#endif" >> $temp

echo "#endif /* XPAINT_H */" >> $temp

cp $temp $htemp

echo "#ifdef XPAINT /* inicio da implementacao */" >> $temp

# echo "#ifdef __cplusplus" >> $temp
# echo "extern \"C\" {"  >> $temp
# echo "#endif" >> $temp


cat lodepng.h lodepng.c >> $temp

echo "#include \"xpaint.h\"" >> $ctemp
cat lodepng.h lodepng.c >> $ctemp

cat color.c base.c draw.c text.c xmath.c modules.c >> $temp
cat color.c base.c draw.c text.c xmath.c modules.c >> $ctemp

# echo "#ifdef __cplusplus" >> $temp
# echo "}"  >> $temp
# echo "#endif" >> $temp


echo "#endif /* XPAINT */" >> $temp
sed '/XDDDX/d' $temp  > $final
sed '/XDDDX/d' $htemp > $hfile
sed '/XDDDX/d' $ctemp > $cfile

cp $final ../../mode_easy/xpaint.h
cp $hfile ../../mode_fast/$hfile
cp $cfile ../../mode_fast/$cfile

rm $temp
rm $htemp
rm $ctemp
rm $final
rm $hfile
rm $cfile

cd ../..
