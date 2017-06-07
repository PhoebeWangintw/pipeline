all:
	gcc -o exec *.c
test:
	./exec < ../input/General.txt > genResult.txt
	diff -b genResult.txt ../output/genResult.txt
	./exec < ../input/Datahazard.txt > dataResult.txt
	diff -b dataResult.txt ../output/dataResult.txt
	./exec < ../input/Lwhazard.txt > loadResult.txt
	diff -b loadResult.txt ../output/loadResult.txt
	./exec < ../input/Branchhazard.txt > branchResult.txt
	diff -b branchResult.txt ../output/branchResult.txt
clear:
	rm exec branchResult.txt genResult.txt dataResult.txt loadResult.txt
