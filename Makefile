CFLAGS = -c -Wall -g
LDFLAGS = 
 
SOURCES = si2cce.c
OBJECTS = $(SOURCES:.c=.o)
 
EXECUTABLE = si2cce 
 
all: $(SOURCES) $(EXECUTABLE)
 
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.o:
	$(CC) $(CFLAGS) $< -o $@

install: $(EXECUTABLE)
	install $(EXECUTABLE) /usr/bin

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

