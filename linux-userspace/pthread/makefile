TARGET = pthread_demo

C = gcc
G = g++
CFLAGS = -Wall -O -g
LDFLAGS = -lpthread

#%.o:%.c
#	$(C) $(CFLAGS) $(LDFLAGS) -c $< -o $@
 
#%.o:%.cpp
#	$(G) $(CFLAGS) $(LDFLAGS) -c $< -o $@
 
SOURCES = $(wildcard *.c *.cpp)
 
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))
 
$(TARGET):$(OBJS)
	$(G) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET)
#	chmod a+x $(TARGET)
 
clean:
	rm -rf *.o $(TARGET)
