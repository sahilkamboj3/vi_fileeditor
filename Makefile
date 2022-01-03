CC=g++
CFLAGS=-Wall -std=c++11
TARGET=main
all=$(TARGET)

$(TARGET): src/*.cpp src/currencyconverter/*.cpp src/window/*.cpp src/util/*.cpp
			$(CC) $(CFLAGS) -o $(TARGET) -I include -L lib -l SDL2-2.0.0 src/*.cpp src/currencyconverter/*.cpp src/window/*.cpp src/util/*.cpp

clean: $(TARGET)
		$(RM) $(TARGET)
