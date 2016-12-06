TEX=pdflatex

make:
	cd ./capa && $(TEX) capa.tex && rm capa.log
	$(TEX) rel.tex
	rm -rf rel.log

clean:
	rm -rf rel.pdf rel.aux capa/capa.pdf capa/capa.aux
