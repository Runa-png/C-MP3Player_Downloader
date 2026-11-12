CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -I.
QTFLAGS = $(shell pkg-config --cflags Qt6Widgets)
QTLIBS = $(shell pkg-config --libs Qt6Widgets)

TARGET = app
SOURCES = $(shell find . -name '*.cpp')

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(QTFLAGS) $(SOURCES) -o $(TARGET) $(QTLIBS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	QT_LOGGING_RULES="qt.qpa.wayland.textinput=false" ./$(TARGET)
