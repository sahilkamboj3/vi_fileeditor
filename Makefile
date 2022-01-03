CC=g++
CFLAGS=-Wall -std=c++11
TARGET=main
all=$(TARGET)

$(TARGET): src/*.cpp src/window/*.cpp
			$(CC) $(CFLAGS) -o $(TARGET) -I include -L lib -l SDL2-2.0.0 src/*.cpp src/window/*.cpp 

clean: $(TARGET)
		$(RM) $(TARGET)
