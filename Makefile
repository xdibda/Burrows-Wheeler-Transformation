PROGRAM=bwted

LIB=bwted

PROJECT=kko.proj2.xdibda00

SOURCE=bwted.cpp main.cpp MTF.cpp BWT.cpp RLE.cpp
HEADER=bwted.h MTF.h RLE.h BWT.h
OTHER=input-auto.txt output-compress-auto.txt output-decompress-auto.txt log.txt

COMPILER=g++
FLAGS=-std=c++11 -Wall -pedantic -Wextra

${PROGRAM}: main.cpp
	$(COMPILER) $(FLAGS) $(SOURCE) -o $@

compress:
	./${PROGRAM} -c -l log.txt -i input-auto.txt -o output-compress-auto.txt

decompress:
	./${PROGRAM} -x -l log.txt -i output-compress-auto.txt -o output-decompress-auto.txt

clean:
	rm -f *.o ${PROGRAM}

zip:
	zip ${PROJECT}.zip ${SOURCE} ${HEADER} ${OTHER} Makefile ${PROGRAM}.pdf
