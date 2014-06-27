/* $Id$ */
/* Copyright (c) 2012 Pierre Pronchery <khorben@defora.org> */
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



#include <stdlib.h>
#include <gtk/gtk.h>
#include "calendar.h"
#include "window.h"


/* CalendarWindow */
/* private */
/* types */
struct _CalendarWindow
{
	Calendar * calendar;

	/* widgets */
	GtkWidget * window;
};


/* prototypes */
/* callbacks */
static gboolean _calendarwindow_on_closex(gpointer data);


/* public */
/* functions */
/* calendarwindow_new */
CalendarWindow * calendarwindow_new(void)
{
	CalendarWindow * calendar;
	GtkWidget * widget;

	if((calendar = malloc(sizeof(*calendar))) == NULL)
		return NULL;
	calendar->calendar = calendar_new();
	calendar->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	/* check for errors */
	if(calendar->calendar == NULL)
	{
		calendarwindow_delete(calendar);
		return NULL;
	}
#if GTK_CHECK_VERSION(2, 6, 0)
	gtk_window_set_icon_name(GTK_WINDOW(calendar->window),
			"stock_calendar");
#endif
	gtk_window_set_title(GTK_WINDOW(calendar->window), "Calendar");
	g_signal_connect_swapped(calendar->window, "delete-event", G_CALLBACK(
				_calendarwindow_on_closex), calendar);
	widget = calendar_get_widget(calendar->calendar);
	gtk_container_add(GTK_CONTAINER(calendar->window), widget);
	gtk_widget_show(calendar->window);
	return calendar;
}


/* calendarwindow_delete */
void calendarwindow_delete(CalendarWindow * calendar)
{
	if(calendar->calendar != NULL)
		calendar_delete(calendar->calendar);
	gtk_widget_destroy(calendar->window);
	free(calendar);
}


/* private */
/* functions */
/* calendarwindow_on_closex */
static gboolean _calendarwindow_on_closex(gpointer data)
{
	CalendarWindow * calendar = data;

	gtk_widget_hide(calendar->window);
	gtk_main_quit();
	return TRUE;
}
