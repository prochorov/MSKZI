CC = g++
CFLAGS = -std=c++11 -Wall
TARGET = lfsr

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp

run: $(TARGET)
	./$(TARGET)

clean: #
	rm -f $(TARGET)
