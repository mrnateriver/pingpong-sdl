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

#include "Bat.h"
#include "Settings.h"

void Bat::ProcessInput(const SDL_Event* ev)
{
	if (ev->type == SDL_KEYDOWN)
	{
		if (ev->key.keysym.sym == SDLK_LEFT)
		{
			coordX -= BAT_MOVEMENT_STEP;
		}
		else if (ev->key.keysym.sym == SDLK_RIGHT)
		{
			coordX += BAT_MOVEMENT_STEP;
		}
	}
	else if (ev->type == SDL_MOUSEMOTION)
	{
		// handle mouse movement - cursor is aligned with the middle of the racket
		// motion.x is relative to the window, so we can use it here
		coordX = ev->motion.x - BAT_WIDTH / 2;
	}

	if (coordX < 0)
	{
		coordX = 0;
	}
	else if (coordX + BAT_WIDTH > WINDOW_WIDTH)
	{
		coordX = WINDOW_WIDTH - BAT_WIDTH;
	}
}

void Bat::Render(SDL_Renderer* renderer)
{
	SDL_Rect outer = { coordX, coordY, BAT_WIDTH, BAT_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 255, 165, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &outer);

	outer.x += BAT_BORDER_WIDTH;
	outer.y += BAT_BORDER_WIDTH;
	outer.w -= BAT_BORDER_WIDTH * 2;
	outer.h -= BAT_BORDER_WIDTH * 2;
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &outer);
}
