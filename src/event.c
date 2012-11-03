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
#include <string.h>
#include <System.h>
#include "event.h"


/* CalendarEvent */
/* private */
/* types */
struct _CalendarEvent
{
	char * name;
	char * location;
	time_t start;
	time_t end;
	char * description;
};


/* public */
/* functions */
/* calendar_event_new */
CalendarEvent * calendarevent_new(void)
{
	CalendarEvent * event;

	if((event = object_new(sizeof(*event))) == NULL)
		return NULL;
	memset(event, 0, sizeof(*event));
	event->start = -1;
	event->end = -1;
	return event;
}


/* calendar_event_delete */
void calendarevent_delete(CalendarEvent * event)
{
	free(event->name);
	free(event->location);
	free(event->description);
	object_delete(event);
}


/* accessors */
/* calendarevent_get_end */
time_t calendarevent_get_end(CalendarEvent * event)
{
	return event->end;
}


/* calendarevent_get_name */
char const * calendarevent_get_name(CalendarEvent * event)
{
	return event->name;
}


/* calendarevent_get_start */
time_t calendarevent_get_start(CalendarEvent * event)
{
	return event->start;
}


/* calendar_event_set_description */
int calendarevent_set_description(CalendarEvent * event,
		char const * description)
{
	char * p;

	if((p = strdup(description)) == NULL)
		return -1;
	free(event->description);
	event->description = p;
	return 0;
}


/* calendar_event_set_end */
int calendarevent_set_end(CalendarEvent * event, time_t end)
{
	event->end = end;
	if(event->start > end)
		event->start = end;
	return 0;
}


/* calendar_event_set_location */
int calendarevent_set_location(CalendarEvent * event,
		char const * location)
{
	char * p;

	if((p = strdup(location)) == NULL)
		return -1;
	free(event->location);
	event->location = p;
	return 0;
}


/* calendar_event_set_name */
int calendarevent_set_name(CalendarEvent * event, char const * name)
{
	char * p;

	if((p = strdup(name)) == NULL)
		return -1;
	free(event->name);
	event->name = p;
	return 0;
}


/* calendar_event_set_start */
int calendarevent_set_start(CalendarEvent * event, time_t start)
{
	event->start = start;
	if(event->end < start)
		event->end = start;
	return 0;
}
