BUTLER_LOC=${PREFIX}/bin/

all: build/networking.o

${BUTLER_LOC}/butler.guile:
	if [ -n ${BUTLER_LOC} ]; then
		mkdir -p ${BUTLER_LOC}
	fi
	cp source/butler.guile ${BUTLER_LOC}/butler.guile

build/networking.o: source/networking.c source/networking.h
	gcc -c source/networking.c -o build/networking.o -I source

install: ${BUTLER_LOC}/butler.guile
