#!/bin/bash

convert "originals/1024px-American_bison_k5680-1.jpg" -resize 400x400 bison.jpg
convert "originals/Miniature_schnauzer.jpg"           -resize 400x400 schnauzer.jpg
convert "originals/Water_Vole_(6038169781).jpg"       -resize 400x400 vole.jpg

montage -tile 1x3 -geometry +0+0 bison.jpg vole.jpg schnauzer.jpg animals.jpg

