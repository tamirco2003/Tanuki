CC=gcc
CFLAGS=-Wall -Werror -I.

DEPS=kujira/scanner.h kujira/token.h

ODIR=obj
_OBJ=main.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

LIBS=kujira/libkujira.so

TARGET=tanuki
TARGETFLAGS=-Lkujira -lkujira -Wl,-rpath=/home/amiu/tanuki/kujira

$(TARGET): $(OBJ) $(LIBS)
	$(CC) -o $@ $(OBJ) $(TARGETFLAGS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Use phony target to force running make on subdirs.
$(LIBS): makelibs
	$(MAKE) -C kujira

makelibs: ;

.PHONY: clean makelibs

clean:
	rm -f $(ODIR)/*.o $(TARGET)
	$(MAKE) clean -C kujira