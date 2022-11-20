THEME = queue
THEME2 = singly_linked_list
THEME2PATH = ../$(THEME2)/

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
TARGET = ../../bin/$(THEME).out
VPATH = ../../test/ ../../include/ ../../obj/ ../../bin/ ../$(THEME2)/

INCLUDE = -I../../include/
OBJ = ../../obj/
TEST = ../../test/

.PHONY: clean
.PHONY: debug
.PHONY: release
.PHONY: all
.PHONY: open
.PHONY: run

all : $(THEME).out
objects = $(THEME)_test.o $(THEME).o $(THEME2).o

$(THEME).out: $(objects)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ)$(THEME).o $(OBJ)$(THEME)_test.o $(OBJ)$(THEME2).o -o $(TARGET)
	
$(THEME)_test.o: $(THEME)_test.c $(THEME).h $(THEME2).h
	$(CC) $(CFLAGS) $(INCLUDE) -c $(TEST)$(THEME)_test.c  -o$(OBJ)$@
	
$(THEME).o: $(THEME).c $(THEME).h $(THEME2).h 
	$(CC) $(CFLAGS) $(INCLUDE) -c $(THEME).c -o$(OBJ)$@

$(THEME2).o: $(THEME2).c $(THEME2).h
	$(CC) $(CFLAGS) $(INCLUDE) -c $(THEME2PATH)$(THEME2).c  -o$(OBJ)$@

debug: CFLAGS += -DEBUG
debug: all

release: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -o3
release: all
	
run: $(TARGET)
	$(TARGET)
		
cgdb:
	cgdb $(TARGET)	

valgrind: 
	valgrind ../../bin/$(THEME).out		
		
clean :
	rm $(TARGET) $(OBJ)$(THEME)_test.o $(OBJ)$(THEME).o
	
open:	$(THEME)_test.c $(THEME).c $(THEME).h
	gopen $(TEST)$(THEME)_test.c $(THEME).c ../../include/$(THEME).h
	
	
	
	
	
	
	

