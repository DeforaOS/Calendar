TARGETS	= $(OBJDIR)calendar
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
BINDIR	= $(PREFIX)/bin
SBINDIR	= $(PREFIX)/sbin
CC	= cc
CPPFLAGSF=
CPPFLAGS=
CFLAGSF	= -W `pkg-config --cflags libSystem gtk+-2.0`
CFLAGS	= -Wall -g -O2 -pedantic
LDFLAGSF= `pkg-config --libs libSystem gtk+-2.0`
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

calendar_OBJS = $(OBJDIR)calendar.o $(OBJDIR)event.o $(OBJDIR)window.o $(OBJDIR)main.o
calendar_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
calendar_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)calendar: $(calendar_OBJS)
	$(CC) -o $(OBJDIR)calendar $(calendar_OBJS) $(calendar_LDFLAGS)

$(OBJDIR)calendar.o: calendar.c calendar.h event.h ../config.h
	$(CC) $(calendar_CFLAGS) -fPIC -o $(OBJDIR)calendar.o -c calendar.c

$(OBJDIR)event.o: event.c event.h
	$(CC) $(calendar_CFLAGS) -fPIC -o $(OBJDIR)event.o -c event.c

$(OBJDIR)window.o: window.c calendar.h window.h
	$(CC) $(calendar_CFLAGS) -o $(OBJDIR)window.o -c window.c

$(OBJDIR)main.o: main.c calendar.h window.h
	$(CC) $(calendar_CFLAGS) -o $(OBJDIR)main.o -c main.c

clean:
	$(RM) -- $(calendar_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(BINDIR)
	$(INSTALL) -m 0755 $(OBJDIR)calendar $(DESTDIR)$(BINDIR)/calendar

uninstall:
	$(RM) -- $(DESTDIR)$(BINDIR)/calendar

.PHONY: all clean distclean install uninstall
