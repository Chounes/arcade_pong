CC=gcc
CFLAGS = -Wall -lncurses -std=c99 -o2 -g
LDFLAGS= -g -lncurses -ltinfo
TARGET=pong

all: $(TARGET) liblogger.so libball.so

$(TARGET): $(TARGET).o
	$(CC) $^ -o $@ $(LDFLAGS)

liblogger.so: src_logger/logger.o
	$(CC) -shared $^ -o $@

libball.so: src_ball/ball.o
	$(CC) -shared $^ -o $@

# lib
logger.o: src_logger/logger.c src_logger/logger.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

ball.o: src_ball/ball.c src_ball/ball.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@


$(TARGET).o: $(TARGET).c $(TARGET).h
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

run:
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)

mrproper: clean
	rm -f $(TARGET)

