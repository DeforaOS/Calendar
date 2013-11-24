/* $Id$ */
/* Copyright (c) 2012-2013 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS Desktop Calendar */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#include <unistd.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <System.h>
#include "calendar.h"
#include "window.h"
#include "../config.h"

/* constants */
#ifndef PROGNAME
# define PROGNAME	"calendar"
#endif


/* calendar */
/* private */
/* prototypes */
static int _calendar(int embedded);

static int _usage(void);


/* functions */
/* calendar */
static int _calendar_embedded(void);
static void _embedded_on_embedded(gpointer data);

static int _calendar(int embedded)
{
	CalendarWindow * calendar;

	if(embedded != 0)
		return _calendar_embedded();
	if((calendar = calendarwindow_new()) == NULL)
		return error_print(PACKAGE);
	gtk_main();
	calendarwindow_delete(calendar);
	return 0;
}

static int _calendar_embedded(void)
{
	GtkWidget * window;
	GtkWidget * widget;
	Calendar * calendar;
	unsigned long id;

	window = gtk_plug_new(0);
	gtk_widget_realize(window);
	g_signal_connect_swapped(window, "embedded", G_CALLBACK(
				_embedded_on_embedded), window);
	if((calendar = calendar_new()) == NULL)
	{
		gtk_widget_destroy(window);
		return -1;
	}
	widget = calendar_get_widget(calendar);
	gtk_container_add(GTK_CONTAINER(window), widget);
	id = gtk_plug_get_id(GTK_PLUG(window));
	printf("%lu\n", id);
	fclose(stdout);
	gtk_main();
	calendar_delete(calendar);
	gtk_widget_destroy(window);
	return 0;
}

static void _embedded_on_embedded(gpointer data)
{
	GtkWidget * widget = data;

	gtk_widget_show(widget);
}


/* usage */
static int _usage(void)
{
	fprintf(stderr, "Usage: %s -x\n", PROGNAME);
	return 1;
}


/* public */
/* functions */
/* main */
int main(int argc, char * argv[])
{
	int o;
	int embedded = 0;

	gtk_init(&argc, &argv);
	while((o = getopt(argc, argv, "x")) != -1)
		switch(o)
		{
			case 'x':
				embedded = 1;
				break;
			default:
				return _usage();
		}
	return (_calendar(embedded) == 0) ? 0 : 2;
}
