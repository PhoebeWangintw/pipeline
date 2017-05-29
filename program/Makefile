all:
	gcc -o exec *.c
test:
	gcc -o exec *.c
	./exec < ../input/Datahazard.txt > output.txt
	# diff -b output.txt ../output/dataResult.txt
compare:
	diff -b output.txt ../output/dataResult.txt
clear:
		rm *.o exec
