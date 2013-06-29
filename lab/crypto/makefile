CXX		= g++
LINK		= g++
CXXFLAGS	= -c -funsigned-char
LINKFLAGS	= -s
REMOVE		= rm -f
INCLUDE		= -I./ -I./../../include
TARGET		= crc32.exe







all: $(TARGET)

$(TARGET): crc32.o
	$(LINK) $(LINKFLAGS) -o $@ $^

crc32.o: crc32.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^

clean:
	$(REMOVE) $(TARGET) crc32.o
