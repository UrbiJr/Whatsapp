# Urbinelli Federico
# federico.urbinelli@gmail.com

IDIR = include
CC = gcc
CFLAGS = -I$(IDIR)

ODIR = obj
LDIR = lib

LIBS = -lncurses

# Keep the alphabetical order!
_DEPS = \
connecteduser.h\
constants.h\
date.h\
inOut.h\
languages.h\
message.h\
mycurses.h\
mysignal.h\
mysocket.h\
mytime.h\
text.h\
user.h\

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Keep the alphabetical order!
_OBJ = \
connecteduser.o\
date.o\
inOut.o\
languages.o\
main.o\
message.o\
mycurses.o\
mysignal.o\
mysocket.o\
mytime.o\
text.o\
user.o\

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Whatsapp:	$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:	clean

clean:
	rm -f Whatsapp $(ODIR)/*.o *~ core $(INCDIR)/*~ 