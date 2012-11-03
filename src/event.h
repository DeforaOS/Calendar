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



#ifndef CALENDAR_EVENT_H
# define CALENDAR_EVENT_H


/* CalendarEvent */
/* public */
/* types */
typedef struct _CalendarEvent CalendarEvent;


/* functions */
CalendarEvent * calendarevent_new(void);
void calendarevent_delete(CalendarEvent * event);

/* accessors */
time_t calendarevent_get_end(CalendarEvent * event);
char const * calendarevent_get_name(CalendarEvent * event);
time_t calendarevent_get_start(CalendarEvent * event);

int calendarevent_set_description(CalendarEvent * event,
		char const * description);
int calendarevent_set_end(CalendarEvent * event, time_t end);
int calendarevent_set_location(CalendarEvent * event, char const * location);
int calendarevent_set_name(CalendarEvent * event, char const * name);
int calendarevent_set_start(CalendarEvent * event, time_t start);

#endif /* !CALENDAR_EVENT_H */
