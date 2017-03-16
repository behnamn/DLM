#!/bin/sh

for i in *.gv; do
	j="$(echo $i | sed -e 's/\(.gv\)*$//g')"
	#neato -Tpng ${j}.gv -o ${j}.png
	neato -Tpdf ${j}.gv -o ${j}.pdf
	#neato -Gstart=5 -Gepsilon=.0000000000001 -Tpdf ${j}.gv -o ${j}.pdf
	#fdp -Tbmp ${j}.gv -o ${j}_fdp.bmp
	#patchwork -Tbmp ${j}.gv -o ${j}_patchwork.bmp
	#dot -Tbmp ${j}.gv -o ${j}_dot.bmp
	#sfdp -Tbmp ${j}.gv -o ${j}_sfdp.bmp
	#circo -Tbmp ${j}.gv -o ${j}_circo.bmp
	#osage -Tbmp ${j}.gv -o ${j}_osage.bmp
	#twopi -Tbmp ${j}.gv -o ${j}_twopi.bmp
done
