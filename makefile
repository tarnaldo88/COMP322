ALL:
	gcc -c ArnaldoTorres.c -Wall -Wextra
	gcc -o ArnaldoTorres ArnaldoTorres.o -lm

REM:
	rm ArnaldoTorres ArnaldoTorres.o
