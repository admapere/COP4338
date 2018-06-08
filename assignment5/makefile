# Adrian M. Perez
# COP 4338 U01 Programming III
# William Feild
# Assignment 5

all: validate display
all-debug: validate-debug display-debug

validate: validateMain.c validate.c
	gcc -o validateMain.out validateMain.c validate.c
validate-debug: validateMain.c validate.c
	gcc -g -o validateMain.out validateMain.c validate.c

display: displayMain.c display.c
	gcc -o displayMain.out displayMain.c display.c
display-debug: displayMain.c display.c
	gcc -g -o displayMain.out displayMain.c display.c
