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



#ifndef CALENDAR_H
# define CALENDAR_H


/* Calendar */
/* public */
/* types */
typedef struct _Calendar Calendar;


/* functions */
Calendar * calendar_new(void);
void calendar_delete(Calendar * calendar);

/* accessors */
/* details */
char const * calendar_get_detail(Calendar * calendar, unsigned int year,
		unsigned int month, unsigned int day);
int calendar_set_detail(Calendar * calendar, unsigned int year,
		unsigned int month, unsigned int day, char const * detail);

GtkWidget * calendar_get_widget(Calendar * calendar);

#endif /* !CALENDAR_H */
