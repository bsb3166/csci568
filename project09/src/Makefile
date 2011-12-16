CC = g++

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGETS = kdd

CFLAGS = -g -Wall

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)
	rm -f *.o

clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY: all clean

