#Target
output: roboter.o initializer.o movements.o mode_management.o
		gcc roboter.o initializer.o  movements.o mode_management.o -lev3dev-c -o start

roboter.o:	roboter.c
			gcc -c roboter.c

initializer.o:	initializer.c initializer.h
				gcc -c initializer.c

movements.o:	movements.c movements.h
				gcc -c movements.c

mode_management.o:	mode_management.c mode_management.h
					gcc -c mode_management.c

clean:
		rm *.o start
