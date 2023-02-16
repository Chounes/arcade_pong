CC=gcc
CFLAGS = -Wall -lncurses -std=c99 -o2 -g
LDFLAGS_LINUX = -g -lncurses -ltinfo
LDFLAGS=$(LDFLAGS_LINUX)
TARGET=pong

all: $(TARGET) liblogger.so libmenu.so

$(TARGET): $(TARGET).o
	$(CC) $^ -o $@ $(LDFLAGS)

liblogger.so: src_logger/logger.o
	$(CC) -shared $^ -o $@ $(LDFLAGS)

libmenu.so: src_menu/menu.o
	$(CC) -shared $^ -o $@ $(LDFLAGS)

# lib
logger.o: src_logger/$logger.c src_logger/logger.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

menu.o: src_menu/menu.c src_menu/menu.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(TARGET).o: $(TARGET).c $(TARGET).h
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)

mrproper: clean
	rm -f $(TARGET)

