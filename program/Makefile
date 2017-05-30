all:
	gcc -o exec *.c
check_all:
	./exec < ../input/General.txt > output.txt
	diff -b output.txt ../output/genResult.txt
	./exec < ../input/Datahazard.txt > output.txt
	diff -b output.txt ../output/dataResult.txt
	./exec < ../input/Lwhazard.txt > output.txt
	diff -b output.txt ../output/loadResult.txt
test:
	gcc -o exec *.c
	./exec < ../input/Lwhazard.txt > output.txt
	# diff -b output.txt ../output/loadResult.txt
compare:
	diff -b output.txt ../output/loadResult.txt
clear:
	rm *.o exec output.txt
