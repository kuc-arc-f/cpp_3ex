CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LIBS     = -lsqlite3 -lcurl -lm
TARGET   = server
SRC = ./src
.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(SRC)/server.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

install: $(TARGET)
	install -m 755 $(TARGET) $(HOME)/.local/bin/

clean:
	rm -f $(TARGET)
rm:
	rm -f $(TARGET)