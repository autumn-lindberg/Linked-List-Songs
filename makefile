CC  = g++
CPPFLAGS = -Wall -g -std=c++11 
OBJECT_FILES = main.o song.o songList.o
APP_NAME = app

# use these object files to create app
# must be same name as entry point
# main: $(OBJECT_FILES)	

# run is an example of not the same name
# you have to explicitly say "compile this with this name (-o)"
run: $(OBJECT_FILES) 
	$(CC) $(CPPFLAGS) $(OBJECT_FILES) -o $(APP_NAME)

# app.o needs songList.h to run
# songList.h includes the rest of the .h files
main.o:	songList.h

# song.o needs song.h to run
song.o: song.h

# songList.o needs songList.h to run
songList.o: songList.h

# valgrind command!
leak:
	valgrind --leak-check=full ./$(APP_NAME)

# "make clean" is not associated with any files (.PHONY:)
# $(info output_text_here) gives a message when command is run
.PHONY: clean
clean:
	$(info -- cleaning the directory --)
	rm -f *.o 
	rm -f $(APP_NAME)

