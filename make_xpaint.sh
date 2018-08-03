#!/bin/bash
final="xpaint.h"
temp="xpaint.hh"
cd libs
echo "#ifndef XPAINT_H" > $temp
echo "#define XPAINT_H" >> $temp
cat aintro.h ximage.h xdraw.h xy.h xmath.h >> $temp
echo "#endif /* XPAINT_H */" >> $temp
echo "#ifndef H_ONLY /* inicio da implementacao */" >> $temp
cat xpng.h xpng.c xttf.h xfont.h >> $temp
cat ximage.c xdraw.c xy.c xmath.c >> $temp
echo "#endif /* H_ONLY */" >> $temp
echo "#undef H_ONLY /* Para evitar a propagação da Flag ela deve ser apagada */" >> $temp
sed '/XDDDX/d' $temp > ../$final
rm $temp
cd ..

