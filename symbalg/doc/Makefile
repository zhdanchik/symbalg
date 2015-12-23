pres: symbalg.tex AST.tex Statements.tex images/If.pdf images/Hier.pdf
	pdflatex symbalg.tex   
	pdflatex symbalg.tex
	rm symbalg.aux
	rm symbalg.log
	rm symbalg.out
	rm symbalg.toc
images/If.pdf: images/If.dot
	dot -Tpdf -o images/If.pdf images/If.dot
images/Hier.pdf: images/Hier.dot
	dot -Tpdf -o images/Hier.pdf images/Hier.dot
