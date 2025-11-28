play.out: general.o chess.o pieces.o
	gcc general.c chess.c pieces.c -o play.out

general.o: general.c general.h
	gcc -Wall -Wextra -c general.c -o general.o

chess.o: chess.c chess.h pieces.h
	gcc -Wall -Wextra -c chess.c -o chess.o

pieces.o: pieces.c pieces.h chess.h
	gcc -Wall -Wextra -c pieces.c -o pieces.o