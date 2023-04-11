CC=gcc
CFLAGS= -Wall -std=c99
LDFLAGS= -lm -lSDL2 -lSDL2_ttf
TARGET=pong

all: $(TARGET) liblogger.so libball.so libsound.so

$(TARGET): $(TARGET).o
	$(CC) $^ -o $@ $(LDFLAGS)

liblogger.so: src_logger/logger.o
	$(CC) -shared $^ -o $@

libball.so: src_ball/ball.o
	$(CC) -shared $^ -o $@

libsound.so: src_sound/sound.o
	$(CC) -shared $^ -o $@

# lib
logger.o: src_logger/logger.c src_logger/logger.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

ball.o: src_ball/ball.c src_ball/ball.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

sound.o: src_sound/sound.c src_sound/sound.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@


$(TARGET).o: $(TARGET).c $(TARGET).h
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

install:
	# install SDL2
	sudo apt-get install libsdl2-dev
	# install SDL2_ttf
	sudo apt-get install libsdl2-ttf-dev


runDebug:
	./$(TARGET) --debug --dir "./services_log/pong.log"

run:
	./$(TARGET)

help:
	@echo "---------------HELP-----------------"
	@echo "make all: compile all"
	@echo "make clean: clean all"
	@echo "make mrproper: clean all and remove executable"
	@echo "make install: install SDL2 and SDL2_ttf"
	@echo "Options:"
	@echo "--debug: enable debug mode"
	@echo "--dir: set the directory of the log file"
	@echo "------------------------------------"
clean:
	rm -f *.o $(TARGET)

mrproper: clean
	rm -f $(TARGET)

