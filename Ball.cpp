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

#include "Ball.h"
#include "Bat.h"
#include "Settings.h"

#include <random>

void Ball::ResetPosition()
{
	//put the ball in the center of the screen
	coordX = WINDOW_WIDTH / 2 - BALL_RADIUS;
	coordY = WINDOW_HEIGHT / 2 - BALL_RADIUS;

	//generate a random angle, which we use to set the direction vector of the ball
	//for this we use C++11 tools, because C rand() on MS compiler produces incremental values when run sequentially
	auto rnd = std::default_random_engine(std::random_device{}());
	std::uniform_real_distribution<> distribution(0, 1);

	float angle = static_cast<float>(distribution(rnd) * M_PI * 2);

	directionVector[0] = cosf(angle);
	directionVector[1] = sinf(angle);

	speed = BALL_SPEED;
}

Ball::Ball(SDL_Renderer* renderer)
{
	ResetPosition();

	sprite = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, BALL_RADIUS * 2 + 1, BALL_RADIUS * 2 + 1);
	if (sprite != nullptr)
	{
		SDL_SetRenderTarget(renderer, sprite);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 165, 0, SDL_ALPHA_OPAQUE);

		//drawing a circle
		for (int y = -BALL_RADIUS; y <= BALL_RADIUS; y++)
		{
			for (int x = -BALL_RADIUS; x <= BALL_RADIUS; x++)
			{
				if (x * x + y * y <= BALL_RADIUS * BALL_RADIUS)
				{
					SDL_RenderDrawPoint(renderer, BALL_RADIUS + x, BALL_RADIUS + y);
				}
			}
		}

		SDL_SetRenderTarget(renderer, nullptr);
	}
}

void Ball::Update(const std::vector<Entity*>& entities)
{
	coordX += static_cast<int>(directionVector[0] * speed);
	coordY += static_cast<int>(directionVector[1] * speed);

	//now we check the collisions, first with the walls, then with the rackets
	if ((coordX + BALL_RADIUS) >= WINDOW_WIDTH || (coordX - BALL_RADIUS) <= 0)
	{
		//just flip along the abscissa
		directionVector[0] = -directionVector[0];
	}
	for (Entity* entity : entities)
	{
		Bat* bat;
		if (bat = dynamic_cast<Bat*>(entity))
		{
			int batX = bat->GetX();
			int batY = bat->GetY();
			//if the racket is higher than the middle of the window, then we take into account the lower edge, otherwise the upper
			if ((batY < (WINDOW_HEIGHT / 2) && (coordY - BALL_RADIUS) <= (batY + BAT_HEIGHT)) || 
				(batY > (WINDOW_HEIGHT / 2) && (coordY + BALL_RADIUS) >= batY))
			{
				if (coordX > batX && coordX < batX + BAT_WIDTH)
				{
					directionVector[1] = -directionVector[1]; //flip along the ordinate
					directionVector[0] = (directionVector[0] > 0 ? directionVector[0] + 0.1f : directionVector[0] - 0.1f); //factor of surprise

					//move the ball to the edge of the racket to help it fly away
					coordY = (batY < (WINDOW_HEIGHT / 2) ? batY + BAT_HEIGHT + BALL_RADIUS + 1 : batY - BALL_RADIUS * 2 - 1);

					//and for fun, speed it up after each collision with the racket
					speed++;

					//the ball cannot collide with both paddles at the same time, so exit immediately after a collision is detected
					break;
				}
			}
		}
	}

	//check if the ball has gone out of bounds
	if ((coordY - BALL_RADIUS) <= 0 || (coordY + BALL_RADIUS) >= WINDOW_HEIGHT)
	{
		ResetPosition();
	}
}

void Ball::Render(SDL_Renderer * renderer)
{
	if (sprite != nullptr)
	{
		SDL_Rect destination = { coordX - BALL_RADIUS, coordY - BALL_RADIUS, BALL_RADIUS * 2, BALL_RADIUS * 2 };
		SDL_RenderCopy(renderer, sprite, NULL, &destination);
	}
}
