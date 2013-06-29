CXX		= g++ -std=c++0x -c -funsigned-char
LINK		= g++ -std=c++0x -s -static-libgcc
INCLUDE		=
REMOVE		= rm -f
TARGET		= cppox.exe

all: $(TARGET)

$(TARGET): main.o
	$(LINK) $(INCLUDE) -o $@ $^

main.o: main.cpp
	$(CXX) $(INCLUDE) -o $@ $^

clean:
	$(REMOVE) $(TARGET) main.o
