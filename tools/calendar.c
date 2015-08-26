/* $Id$ */
/* Copyright (c) 2012-2015 Pierre Pronchery <khorben@defora.org> */
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
#include <Desktop/Mailer/plugin.h>
#include "../src/calendar.h"

#include "../src/calendar.c"
#include "../src/event.c"


/* Mailing-lists */
/* private */
/* types */
typedef struct _MailerPlugin CalendarPlugin;

struct _MailerPlugin
{
	MailerPluginHelper * helper;

	Calendar * calendar;

	/* widgets */
	GtkWidget * widget;
	GtkWidget * view;
};


/* protected */
/* prototypes */
/* plug-in */
static MailerPlugin * _calendar_init(MailerPluginHelper * helper);
static void _calendar_destroy(CalendarPlugin * calendar);
static GtkWidget * _calendar_get_widget(CalendarPlugin * calendar);


/* public */
/* variables */
/* plug-in */
MailerPluginDefinition plugin =
{
	"Calendar",
	"stock_calendar",
	NULL,
	_calendar_init,
	_calendar_destroy,
	_calendar_get_widget,
	NULL
};


/* protected */
/* functions */
/* plug-in */
/* calendar_init */
static MailerPlugin * _calendar_init(MailerPluginHelper * helper)
{
	CalendarPlugin * calendar;
	GtkWidget * widget;

	if((calendar = malloc(sizeof(*calendar))) == NULL)
		return NULL;
	if((calendar->calendar = calendar_new()) == NULL)
	{
		_calendar_destroy(calendar);
		return NULL;
	}
	calendar->helper = helper;
#if GTK_CHECK_VERSION(3, 0, 0)
	calendar->widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
#else
	calendar->widget = gtk_vbox_new(FALSE, 4);
#endif
	widget = calendar_get_widget(calendar->calendar);
	gtk_box_pack_start(GTK_BOX(calendar->widget), widget, FALSE, TRUE, 0);
	widget = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(widget),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	calendar->view = gtk_tree_view_new();
	gtk_container_add(GTK_CONTAINER(widget), calendar->view);
	gtk_box_pack_start(GTK_BOX(calendar->widget), widget, TRUE, TRUE, 0);
	gtk_widget_show_all(calendar->widget);
	return calendar;
}


/* calendar_destroy */
static void _calendar_destroy(CalendarPlugin * calendar)
{
	if(calendar->calendar != NULL)
		calendar_delete(calendar->calendar);
	free(calendar);
}


/* calendar_get_widget */
static GtkWidget * _calendar_get_widget(CalendarPlugin * calendar)
{
	return calendar->widget;
}
