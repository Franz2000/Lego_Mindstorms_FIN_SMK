#Target
output: roboter.o initializer.o movements.o mode_management.o framebuffer.o
		gcc roboter.o initializer.o  movements.o mode_management.o framebuffer.o -lev3dev-c -lm -o start

roboter.o:	roboter.c
			gcc -c roboter.c

initializer.o:	initializer.c initializer.h
				gcc -c initializer.c

movements.o:	movements.c movements.h
				gcc -c movements.c

mode_management.o:	mode_management.c mode_management.h
					gcc -c mode_management.c

framebuffer.o:		framebuffer.c framebuffer.h
					gcc -c framebuffer.c
clean:
		rm *.o start
