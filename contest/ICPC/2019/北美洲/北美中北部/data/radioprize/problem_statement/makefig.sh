!#/bin/bash


fig2dev -L pdftex_t f1.fig > f1.pdf_t
fig2dev -L pdftex -p dummy f1.fig > f1.pdf
pdflatex f1tex
pdfcrop f1tex.pdf 1.pdf
rm -f dummy.create f1.eps f1.pdf f1.pdf_t f1tex.aux f1tex.log f1tex.pdf 1.pdf.orig *~

