PACKAGE_PREFIX=
SERVICE_PREFIX=

PACKAGE_BIN=${PACKAGE_PREFIX}/bin
SERVICE_BIN=${SERVICE_PREFIX}/bin

PROJECT_COMP_FLAGS="-Wall -Wextra -Werror"
PROJECT_SOURCE_DIR=source

BUTLER_SOURCE_DIR=${PROJECT_SOURCE_DIR}/butler
BUTLER_COMP_FLAGS="${PROJECT_COMP_FLAGS} -I source/butler"

build: build/networking.o

install: ${PACKAGE_BIN}/butler.guile ${SERVICE_BIN}/butler.guile

${PACKAGE_BIN}/butler.guile:
	mkdir --parents ${PACKAGE_BIN}
	install ${BUTLER_SOURCE_DIR}/butler.guile ${PACKAGE_BIN}/butler.guile

${SERVICE_BIN}/butler.guile: ${PACKAGE_BIN}/butler.guile
	mkdir --parents ${SERVICE_BIN}
	if [ -e $@ ]; then rm $@; fi
	ln -s ${PACKAGE_BIN}/butler.guile $@

build/networking.o: ${BUTLER_SOURCE_DIR}/networking.c ${BUTLER_SOURCE_DIR}/networking.h
	gcc -c ${BUTLER_SOURCE_DIR}/networking.c -o $@ ${BUTLER_COMP_FLAGS}

