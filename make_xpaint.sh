#!/bin/bash
final="xpaint.h"
temp="full.hh"
htemp="xpaint.hh"
ctemp="xpaint.cc"
hfile="xlite.h"
cfile="xlite.c"

cd src
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

echo "#include \"xlite.h\"" >> $ctemp
cat lodepng.h lodepng.c >> $ctemp

cat color.c base.c draw.c text.c xmath.c modules.c >> $temp
cat color.c base.c draw.c text.c xmath.c modules.c >> $ctemp

# echo "#ifdef __cplusplus" >> $temp
# echo "}"  >> $temp
# echo "#endif" >> $temp


echo "#endif /* XPAINT */" >> $temp
sed '/XDDDX/d' $temp > ~/Dropbox/gits/0_tools/xpaint/$final
sed '/XDDDX/d' $htemp > ~/Dropbox/gits/0_tools/xpaint/lite/$hfile
sed '/XDDDX/d' $ctemp > ~/Dropbox/gits/0_tools/xpaint/lite/$cfile
rm $temp
rm $htemp
rm $ctemp
cd ..
