APP=sterowanie-lazikiem


__start__: obj dat  pliki_do_rysowania ./${APP}
	rm -f core.* core; ./${APP}

# Tworzy katalog "obj" gdy go nie ma
# 
obj:
	mkdir obj

dat:
	mkdir dat

pliki_do_rysowania:
	mkdir pliki_do_rysowania


./${APP}: obj/main.o obj/lacze_do_gnuplota.o obj/PowierzchniaMarsa.o obj/ObrysXY.o \
		  obj/ObiektGeom.o obj/Lazik.o obj/MacierzRotacji.o obj/Scena.o obj/Menu.o\
		  obj/ProbkaRegolitu.o inc/TypKolizji.hh obj/LazikSFR.o
	g++ -o ./${APP} obj/main.o obj/lacze_do_gnuplota.o obj/PowierzchniaMarsa.o\
                     obj/ObrysXY.o obj/ObiektGeom.o obj/Lazik.o obj/MacierzRotacji.o obj/Scena.o\
					 obj/Menu.o obj/ProbkaRegolitu.o obj/LazikSFR.o


obj/main.o: src/main.cpp inc/lacze_do_gnuplota.hh inc/ObrysXY.hh inc/ObiektGeom.hh inc/PowierzchniaMarsa.hh\
            inc/Kolory.hh inc/rozmiar.hh inc/Wektor2D.hh inc/Wektor3D.hh inc/Macierz3D.hh inc/Lazik.hh\
			inc/Scena.hh inc/MacierzRotacji.hh inc/Menu.hh inc/ProbkaRegolitu.hh inc/TypKolizji.hh inc/LazikSFR.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/main.o src/main.cpp

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/PowierzchniaMarsa.o: src/PowierzchniaMarsa.cpp inc/PowierzchniaMarsa.hh inc/lacze_do_gnuplota.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/PowierzchniaMarsa.o src/PowierzchniaMarsa.cpp

obj/ObiektGeom.o: src/ObiektGeom.cpp inc/ObiektGeom.hh inc/lacze_do_gnuplota.hh inc/ObrysXY.hh inc/TypKolizji.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/ObiektGeom.o src/ObiektGeom.cpp

obj/Lazik.o: src/Lazik.cpp inc/Lazik.hh inc/ObiektGeom.hh inc/lacze_do_gnuplota.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Lazik.o src/Lazik.cpp

obj/MacierzRotacji.o: src/MacierzRotacji.cpp inc/MacierzRotacji.hh inc/Macierz3D.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/MacierzRotacji.o src/MacierzRotacji.cpp

obj/ObrysXY.o: src/ObrysXY.cpp inc/ObrysXY.hh inc/Wektor2D.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/ObrysXY.o src/ObrysXY.cpp

obj/Scena.o: src/Scena.cpp inc/Scena.hh inc/ObiektGeom.hh inc/Lazik.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Scena.o src/Scena.cpp

obj/Menu.o: src/Menu.cpp inc/Menu.hh inc/Scena.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Menu.o src/Menu.cpp

obj/ProbkaRegolitu.o: src/ProbkaRegolitu.cpp inc/ProbkaRegolitu.hh inc/ObiektGeom.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/ProbkaRegolitu.o src/ProbkaRegolitu.cpp

obj/LazikSFR.o: src/LazikSFR.cpp inc/LazikSFR.hh inc/ObiektGeom.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/LazikSFR.o src/LazikSFR.cpp

clean:
	rm -f obj/* ./${APP} core.* core liki_do_rysowania/*



help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo " make help   - wyswietla niniejsza informacje"
	@echo
