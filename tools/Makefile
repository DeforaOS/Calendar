TARGETS	= $(OBJDIR)calendar.so
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF=
CPPFLAGS=
CFLAGSF	= -W -fPIC `pkg-config --cflags libDesktop Mailer`
CFLAGS	= -Wall -g -O2 -pedantic
LDFLAGSF= `pkg-config --libs libDesktop`
AR	= ar
RANLIB	= ranlib
CCSHARED= $(CC) -shared
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

calendar_OBJS = $(OBJDIR)calendar.o
calendar_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
calendar_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) ../src/calendar.o ../src/event.o

$(OBJDIR)calendar.so: $(calendar_OBJS)
	$(CCSHARED) -o $(OBJDIR)calendar.so $(calendar_OBJS) $(calendar_LDFLAGS)

$(OBJDIR)calendar.o: calendar.c
	$(CC) $(calendar_CFLAGS) -o $(OBJDIR)calendar.o -c calendar.c

clean:
	$(RM) -- $(calendar_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(LIBDIR)/Mailer/plugins
	$(INSTALL) -m 0755 $(OBJDIR)calendar.so $(DESTDIR)$(LIBDIR)/Mailer/plugins/calendar.so

uninstall:
	$(RM) -- $(DESTDIR)$(LIBDIR)/Mailer/plugins/calendar.so

.PHONY: all clean distclean install uninstall
