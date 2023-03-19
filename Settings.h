/*
 * Copyright (c) 2016 Evgenii Dobrovidov
 * This file is part of "Ping-pong".
 *
 * "Ping-pong" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * "Ping-pong" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with "Ping-pong".  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _SETTINGS_H_
#define _SETTINGS_H_

//game window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

//the length and height of the racket in pixels
const int BAT_WIDTH = 100;
const int BAT_HEIGHT = 30;

//the speed of the racket with the arrows
const int BAT_MOVEMENT_STEP = 20;

//racquet edge thickness
const int BAT_BORDER_WIDTH = 5;

//indentation of rackets from the top and bottom edges
const int BAT_VERTICAL_OFFSET = 10;

//ball radius
const int BALL_RADIUS = 15;

//initial speed of the ball
const int BALL_SPEED = 5;

#endif
