/*
 *      TTY-CLOCK headers file.
 *      Copyright © 2008 Martin Duquesnoy <xorg62@gmail.com>
 *      All rights reserved.
 *
 *      Redistribution and use in source and binary forms, with or without
 *      modification, are permitted provided that the following conditions are
 *      met:
 *
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following disclaimer
 *        in the documentation and/or other materials provided with the
 *        distribution.
 *      * Neither the name of the  nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 *      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TTYCLOCK_H_INCLUDED
#define TTYCLOCK_H_INCLUDED

#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <ncurses.h>
#include <unistd.h>
#include <getopt.h>

/* Macro */
#define NORMFRAMEW 35
#define SECFRAMEW  54
#define DATEWINH   3
/* Maximum number of digits in a time string, hh:mm:ss. */
#define N_TIME_DIGITS 6

typedef enum { False, True } Bool;

/* Global ttyclock struct */
typedef struct
{
        /* while() boolean */
        Bool running;

        /* terminal variables */ 
        SCREEN *ttyscr;
        int bg;

        /* Running option */
        struct
        {
                Bool box;
                int color;
                Bool bold;
        } option;

        /* Clock geometry */
        struct
        {
                int x, y, w, h;
                /* For rebound use (see clock_rebound())*/
                int a, b;
        } geo;

        /* Date content ([2] = number by number) */
        int initial_digits[N_TIME_DIGITS];
        struct
        {
                unsigned int hour[2];
                unsigned int minute[2];
                unsigned int second[2];
                char timestr[9];  /* hh:mm:ss */
        } date;

        /* time.h utils */
        struct tm *tm;
        time_t lt;

        /* Clock member */
        WINDOW *framewin;
        WINDOW *datewin;

} ttyclock_t;

/* Prototypes */
void init(void);
void signal_handler(int signal);
void update_hour(void);
void draw_number(int n, int x, int y, unsigned int color);
void draw_clock(void);
void clock_move(int x, int y, int w, int h);
void set_second(void);
void set_center(void);
void set_box(Bool b);
void key_event(void);

/* Global variable */
ttyclock_t *ttyclock;

/* Number matrix */
const Bool number[][15] =
{
        {1,1,1,1,0,1,1,0,1,1,0,1,1,1,1}, /* 0 */
        {0,0,1,0,0,1,0,0,1,0,0,1,0,0,1}, /* 1 */
        {1,1,1,0,0,1,1,1,1,1,0,0,1,1,1}, /* 2 */
        {1,1,1,0,0,1,1,1,1,0,0,1,1,1,1}, /* 3 */
        {1,0,1,1,0,1,1,1,1,0,0,1,0,0,1}, /* 4 */
        {1,1,1,1,0,0,1,1,1,0,0,1,1,1,1}, /* 5 */
        {1,1,1,1,0,0,1,1,1,1,0,1,1,1,1}, /* 6 */
        {1,1,1,0,0,1,0,0,1,0,0,1,0,0,1}, /* 7 */
        {1,1,1,1,0,1,1,1,1,1,0,1,1,1,1}, /* 8 */
        {1,1,1,1,0,1,1,1,1,0,0,1,1,1,1}, /* 9 */
};

#endif /* TTYCLOCK_H_INCLUDED */
