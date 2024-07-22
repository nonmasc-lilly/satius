


ALL: COMPILE RUN

COMPILE: src/*.c
	x86_64-w64-mingw32-gcc -o build/satius.exe src/*.c

RUN:
	wine build/satius.exe build/truth.sat
