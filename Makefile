CC=gcc
BIN=app

OBJ=main.o Student_main.o Student_func.o Master_main.o Master_func.o tools.o Teacher_main.o Teacher_func.o
FLAG=-Wall -Werror
STD=-std=gnu99

all :$(OBJ)
	$(CC) -o $(BIN) $(OBJ) && ./$(BIN)

main.o:main.c tools.h Student_main.h Master_main.h Teacher_main.h main.h
	$(CC) $(STD) $(FLAG) -c main.c

tools.o:tools.c tools.h main.h
	$(CC) $(STD) $(FLAG) -c tools.c

Student_func:Student_func.c Student_func.h Student_main.h tools.h main.h
	$(CC) $(STD) $(FLAG) -c Student_func.c

Student_main:Student_main.c tools.h Student_func.h main.h Student_main.h
	$(CC) $(STD) $(FLAG) -c Student_main.c

Teacher_func:Teacher_func.c Teacher_func.h tools.h Teacher_main.h main.h
	$(CC) $(STD) $(FLAG) -c Teacher_func.c	

Teacher_main:Teacher_main.c tools.h Teacher_func.h Teacher_main.h
	$(CC) $(STD) $(FLAG) -c Teacher_main.c

Master_func:Master_func.c Master_func.h tools.h Master_main.h	
	$(CC) $(STD) $(FLAG) -c Master_func.c

Master_main:Master_main.c Master_func.h tools.h Master_main.h main.h
	$(CC) $(STD) $(FLAG) -c Master_main.c
	
clean:
	rm -rf $(BIN) $(OBJ)
	
