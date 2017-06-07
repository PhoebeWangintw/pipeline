all:
	gcc -o exec *.c
check_all:
	./exec < ../input/General.txt > genResult.txt
	diff -b genResult.txt ../output/genResult.txt
	./exec < ../input/Datahazard.txt > dataResult.txt
	diff -b dataResult.txt ../output/dataResult.txt
	./exec < ../input/Lwhazard.txt > loadResult.txt
	diff -b loadResult.txt ../output/loadResult.txt
	./exec < ../input/Branchhazard.txt > branchResult.txt
	diff -b branchResult.txt ../output/branchResult.txt
test:
	gcc -o exec *.c
	./exec < ../input/Branchhazard.txt > branchResult.txt
	# diff -b output.txt ../output/loadResult.txt
compare:
	diff -b branchResult.txt ../output/branchResult.txt
clear:
	rm *.o exec branchResult.txt genResult.txt dataResult.txt loadResult.txt
