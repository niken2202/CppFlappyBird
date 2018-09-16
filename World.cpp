#include "World.h"
#include "Pipe.h"

#include <iostream>
#include <stdlib.h>
#include <ctime>

#include <SDL.h>
#include <SDL_Image.h>

World::World(SDL_Window* window, SDL_Renderer* renderer)
    :   m_Background(NULL),
        m_Floor(NULL)
{
    SDL_Surface* surface = NULL;

    surface = IMG_Load("img\\background.png");

    if (!surface)
    {
        std::cout << " Could not load Start Screen\n" << IMG_GetError();
        return;
    }

    m_Background = SDL_CreateTextureFromSurface(renderer, surface);

    if(!m_Background)
    {
        std::cout << "Could not load background image\n" << SDL_GetError();
        return;
    }
    else
        std::cout << "Loaded Background" << std::endl;

    SDL_FreeSurface(surface);
    surface = NULL;

    surface = IMG_Load("img\\floor.png");

    if (!surface)
    {
        std::cout << " Could not load floor texture\n" << IMG_GetError();
        return;
    }

    m_Floor = SDL_CreateTextureFromSurface(renderer, surface);

    if(!m_Floor)
    {
        std::cout << "Could not create floor\n" << SDL_GetError();
        return;
    }
    else
        std::cout << "Loaded floor" << std::endl;

    SDL_FreeSurface(surface);

    m_PipeDistance = 350;

    srand(time(0));
    int randomType = rand() % 3 + 1;

    Pipe* pipe = new Pipe(window, renderer, randomType);
    pipe->MoveTo(800);
    m_Pipes.push_back(pipe);
}

void World::MoveLeft()
{
    for (unsigned int i = 0; i < m_Pipes.size(); ++i)
    {
        Pipe* pipe = m_Pipes[i];
        pipe->MoveLeft();
    }
}

void World::RenderPipes(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_Rect rect;
    rect.x = 800;
    rect.y = 0;
    rect.h = 20;
    rect.w = m_PipeDistance;

    SDL_Rect lastPipe = m_Pipes.back()->GetTopRect();

    if (SDL_HasIntersection(&rect, &lastPipe) == SDL_TRUE)
    {
        srand(time(0));
        int randomType = rand() % 3 + 1;

        Pipe* pipe = new Pipe(window, renderer, randomType);
        pipe->MoveTo(lastPipe.x + m_PipeDistance);
        m_Pipes.push_back(pipe);
    }

    for (unsigned int i = 0; i < m_Pipes.size(); ++i)
    {
        Pipe* pipe = m_Pipes[i];
        pipe->Render(renderer);
    }
}

void World::RenderBackground(SDL_Renderer* renderer)
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = 600;
    rect.w = 800;

    SDL_RenderCopy(renderer, m_Background, NULL, &rect);
}

void World::RenderFloor(SDL_Renderer* renderer)
{
    SDL_Rect rect;

    rect.x = 0;
    rect.y = 500;
    rect.h = 216;
    rect.w = 800;
    SDL_RenderCopy(renderer, m_Floor, NULL, &rect);
}

World::~World()
{
    if (m_Background)
        SDL_DestroyTexture(m_Background);
}
