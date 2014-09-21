# Dan LaManna
# dl954588
# dlamanna@albany.edu

.SUFFIXES: .c .o

CC=gcc
CFLAGS=-g3 -Wall
SOURCES=main.c config.c parser.c sort.c select.c project.c utils.c count.c output.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=p3

%.o : %.c
	$(CC) $(CFLAGS) -c $<

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

sort.o: constants.h struct_def.h prototypes.h
config.o: constants.h struct_def.h prototypes.h
select.o: constants.h struct_def.h prototypes.h
output.o: constants.h struct_def.h prototypes.h
utils.o: constants.h struct_def.h prototypes.h
main.o: constants.h struct_def.h prototypes.h
parser.o: constants.h struct_def.h prototypes.h
project.o: constants.h struct_def.h prototypes.h
count.o: constants.h struct_def.h prototypes.h

clean:
	rm -f *.o core
