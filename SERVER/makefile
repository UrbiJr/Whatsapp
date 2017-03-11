# Urbinelli Federico federico.urbinelli@gmail.com
# Whatsapp 1.0.0

IDIR = include
CC = gcc
CFLAGS = -I$(IDIR)

ODIR = obj
LDIR = lib

LIBS = -lncurses

# Keep the alphabetical order!
_DEPS = \
connected_user.h\
constants.h\
date.h\
in_out.h\
languages.h\
message.h\
mycurses.h\
mysignal.h\
mytime.h\
socket.h\
text.h\
user.h\

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Keep the alphabetical order!
_OBJ = \
connected_user.o\
date.o\
in_out.o\
languages.o\
main.o\
message.o\
mycurses.o\
mysignal.o\
mytime.o\
socket.o\
text.o\
user.o\

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Whatsapp:	$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:	clean

clean:
	rm -f Whatsapp message_for_user.txt message.txt temp.txt $(ODIR)/*.o *~ core $(INCDIR)/*~ 
