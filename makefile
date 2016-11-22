prefix=prefix-new

all: build/networking.o build/butler.guile

build/butler.guile:
	ln -s source/butler.guile build/butler.guile

build/networking.o: source/networking.c source/networking.h
	gcc -c source/networking.c -o build/networking.o -I source

install:
	echo "Install to: " ${prefix}
