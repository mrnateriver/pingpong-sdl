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

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SDL.h>
#include <vector>

class Entity
{
protected:
	int coordX;
	int coordY;

public:
	virtual void ProcessInput(const SDL_Event* ev) {}
	virtual void Update(const std::vector<Entity*> &entities) {}
	virtual void Render(SDL_Renderer* renderer) {}
};

#endif