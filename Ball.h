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

#ifndef _BALL_H_
#define _BALL_H_

#include "Entity.h"

class Ball: public Entity
{
private:
	SDL_Texture* sprite;
	float directionVector[2];
	int speed;

	void ResetPosition();

public:
	// Renderer is required for creating a sprite, which will later be drawn on the screen
	Ball(SDL_Renderer* renderer);

	void Update(const std::vector<Entity*> &entities);
	void Render(SDL_Renderer* renderer);
};

#endif