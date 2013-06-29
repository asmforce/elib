CXX		= g++ -c -funsigned-char
LINK		= g++ -s -static-libgcc
REMOVE		= rm -f
INCLUDE		= -I./ -I./include
LIBS		= -L./
TARGET		= mkhex.exe





all: $(TARGET)

$(TARGET): main.o
	$(LINK) $(INCLUDE) -o $@ $^

main.o: main.cpp
	$(CXX) $(LIBS) -o $@ $^

clean:
	$(REMOVE) $(TARGET) main.o
