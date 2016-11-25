PACKAGE_PREFIX=
SERVICE_PREFIX=

PACKAGE_BIN=${PACKAGE_PREFIX}/bin
SERVICE_BIN=${SERVICE_PREFIX}/bin

build: build/networking.o

install: ${PACKAGE_BIN}/butler.guile ${SERVICE_BIN}/butler.guile

${PACKAGE_BIN}/butler.guile:
	mkdir --parents ${PACKAGE_BIN}
	install source/butler.guile ${PACKAGE_BIN}/butler.guile

${SERVICE_BIN}/butler.guile: ${PACKAGE_BIN}/butler.guile
	mkdir --parents ${SERVICE_BIN}
	if [ -e $@ ]; then rm $@; fi
	ln -s ${PACKAGE_BIN}/butler.guile $@

build/networking.o: source/networking.c source/networking.h
	gcc -c source/networking.c -o build/networking.o -I source

