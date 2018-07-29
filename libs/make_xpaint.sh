#!/bin/bash
final="xpaint.h"
temp="xpaint.hh"
echo "#ifndef XPAINT_H" > $temp
echo "#define XPAINT_H" >> $temp
cat ximage.h xdraw.h xy.h xmath.h >> $temp
echo "#endif /* XPAINT_H */" >> $temp
echo "#ifdef X_FULL" >> $temp
cat xpng.h xpng.c xttf.h xfont.h >> $temp
cat ximage.c xdraw.c xy.c xmath.c >> $temp
echo "#endif /* X_FULL */" >> $temp
sed '/XDDDX/d' $temp > ../$final
rm $temp
cd ..

