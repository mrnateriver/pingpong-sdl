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

#include "Game.h"
#include "Bat.h"
#include "Ball.h"
#include "Settings.h"

Game::Game()
{
	running = false;
	window = nullptr;
	renderer = nullptr;
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	window = SDL_CreateWindow("Ping-pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	entities.push_back(new Ball(renderer));
	entities.push_back(new Bat(BAT_VERTICAL_OFFSET));
	entities.push_back(new Bat(WINDOW_HEIGHT - BAT_HEIGHT - BAT_VERTICAL_OFFSET));

	running = true;
	return true;
}

void Game::Cleanup()
{
	for (Entity* entity : entities)
	{
		delete entity;
	}
	entities.clear();

	if (renderer != nullptr) SDL_DestroyRenderer(renderer);
	if (window != nullptr) SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::Update()
{
	for (Entity* entity : entities)
	{
		entity->Update(entities);
	}
}

void Game::HandleInput(const SDL_Event* ev)
{
	if (ev->type == SDL_QUIT || (ev->type == SDL_KEYDOWN && ev->key.keysym.sym == SDLK_ESCAPE))
	{
		running = false;
		return;
	}
	
	for (Entity* entity : entities)
	{
		entity->ProcessInput(ev);
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	for (Entity* entity : entities)
	{
		entity->Render(renderer);
	}

	SDL_RenderPresent(renderer);
}

int Game::Start()
{
	if (!Initialize())
	{
		return -1;
	}

	SDL_Event input_event;
	while (running)
	{
		while (SDL_PollEvent(&input_event))
		{
			HandleInput(&input_event);
		}

		Update();
		Render();
	}

	Cleanup();
	return 0;
}
