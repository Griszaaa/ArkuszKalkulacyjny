main: *.cpp *.h
	g++ main.cpp tablica.cpp tablica_wysw.cpp menu.cpp operacje_na_plikach.cpp -g -o main
	doxygen config
	make -C latex -iks
	cp latex/refman.pdf Dokumentacja.pdf

clean:
	rm -f main
	rm -r html latex

