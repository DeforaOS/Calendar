/* $Id$ */
/* Copyright (c) 2012 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS Desktop Mailer */
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


/* Mailing-lists */
/* private */
/* types */
typedef struct _MailerPlugin Calendar;

struct _MailerPlugin
{
	MailerPluginHelper * helper;

	/* widgets */
	GtkWidget * widget;
	GtkWidget * calendar;
	GtkWidget * view;
};


/* protected */
/* prototypes */
/* plug-in */
static MailerPlugin * _calendar_init(MailerPluginHelper * helper);
static void _calendar_destroy(Calendar * calendar);
static GtkWidget * _calendar_get_widget(Calendar * calendar);


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
	Calendar * calendar;
	GtkWidget * widget;

	if((calendar = malloc(sizeof(*calendar))) == NULL)
		return NULL;
	calendar->helper = helper;
	calendar->widget = gtk_vbox_new(FALSE, 4);
	/* XXX code duplicated from the Calendar class */
	calendar->calendar = gtk_calendar_new();
	gtk_calendar_set_display_options(GTK_CALENDAR(calendar->calendar),
			GTK_CALENDAR_SHOW_HEADING
			| GTK_CALENDAR_SHOW_DAY_NAMES
			| GTK_CALENDAR_SHOW_WEEK_NUMBERS);
#if GTK_CHECK_VERSION(2, 14, 0)
	gtk_calendar_set_detail_height_rows(GTK_CALENDAR(calendar->calendar),
			1);
# if 0 /* XXX allow callbacks to be re-used from the Calendar class */
	gtk_calendar_set_detail_func(GTK_CALENDAR(calendar->calendar),
			(GtkCalendarDetailFunc)_calendar_on_detail, calendar,
			NULL);
# endif
#endif
	gtk_box_pack_start(GTK_BOX(calendar->widget), calendar->calendar, FALSE,
			TRUE, 0);
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
static void _calendar_destroy(Calendar * calendar)
{
	free(calendar);
}


/* calendar_get_widget */
static GtkWidget * _calendar_get_widget(Calendar * calendar)
{
	return calendar->widget;
}
