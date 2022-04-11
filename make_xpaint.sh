#!/bin/bash
final="xpaint.h"
temp="xpaint.hh"
cd lib
echo "#ifndef XPAINT_H" > $temp
echo "#define XPAINT_H" >> $temp

# echo "#ifdef __cplusplus" >> $temp
# echo "extern \"C\" {"  >> $temp
# echo "#endif" >> $temp

cat aintro.h color.h base.h draw.h text.h xmath.h modules.h >> $temp

# echo "#ifdef __cplusplus" >> $temp
# echo "}"  >> $temp
# echo "#endif" >> $temp


echo "#endif /* XPAINT_H */" >> $temp
echo "#ifdef XPAINT /* inicio da implementacao */" >> $temp

# echo "#ifdef __cplusplus" >> $temp
# echo "extern \"C\" {"  >> $temp
# echo "#endif" >> $temp


cat lodepng.h lodepng.c >> $temp
cat color.c base.c draw.c text.c xmath.c modules.c >> $temp

# echo "#ifdef __cplusplus" >> $temp
# echo "}"  >> $temp
# echo "#endif" >> $temp


echo "#endif /* XPAINT */" >> $temp
#echo "#undef H_ONLY /* Para evitar a propagação da Flag ela deve ser apagada */" >> $temp
sed '/XDDDX/d' $temp > ~/Dropbox/gits/0_tools/xpaint/$final
rm $temp
cd ..