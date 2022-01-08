CC=gcc
CFLAGS=-Wall -Werror -I. -fPIC

DEPS=scanner.h token.h

ODIR=obj
_OBJ=scanner.o 
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

TARGET=libkujira.so
TARGETFLAGS=-shared

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(TARGETFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(TARGET)