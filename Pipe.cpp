#include "Pipe.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Pipe::Pipe(SDL_Window* window, SDL_Renderer* renderer, int type)
    :   m_Type(type),
        m_PipeTop(NULL),
        m_PipeBot(NULL)
{
    SDL_Surface* surface = NULL;

    surface = IMG_Load("img//pipe_top.png");

    if (!surface)
    {
        std::cout << " Could not load pipe texture\n" << IMG_GetError();
        return;
    }

    m_PipeTop = SDL_CreateTextureFromSurface(renderer, surface);

    if(!m_PipeTop)
    {
        std::cout << "Could not load create pipe\n" << SDL_GetError();
        return;
    }

    SDL_FreeSurface(surface);
    surface = NULL;

    surface = IMG_Load("img//pipe_bot.png");

    if (!surface)
    {
        std::cout << " Could not load pipe texture\n" << IMG_GetError();
        return;
    }

    m_PipeBot = SDL_CreateTextureFromSurface(renderer, surface);

    if(!m_PipeBot)
    {
        std::cout << "Could not load create pipe\n" << SDL_GetError();
        return;
    }

    SDL_FreeSurface(surface);
    surface = NULL;

    switch (type)
    {
    case 1:
        {
            m_TopRect.x = 800;
            m_TopRect.y = 200 - 1136;
            m_TopRect.h = 1136;
            m_TopRect.w = 104;

            m_BotRect.x = 0;
            m_BotRect.y = 300;
            m_BotRect.h = 500 - 300;
            m_BotRect.w = 104;
        }
        break;

    case 2:
        {
            m_TopRect.x = 800;
            m_TopRect.y = 300 - 1136;
            m_TopRect.h = 1136;
            m_TopRect.w = 104;

            m_BotRect.x = 0;
            m_BotRect.y = 390;
            m_BotRect.h = 500 - 390;
            m_BotRect.w = 104;
        }
        break;

    case 3:
        {
            m_TopRect.x = 800;
            m_TopRect.y = 100 - 1136;
            m_TopRect.h = 1136;
            m_TopRect.w = 104;

            m_BotRect.x = 800;
            m_BotRect.y = 200;
            m_BotRect.h = 500 - 200;
            m_BotRect.w = 104;
        }
        break;
    }
}


void Pipe::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, m_PipeTop, NULL, &m_TopRect);
    SDL_RenderCopy(renderer, m_PipeBot, NULL, &m_BotRect);
}

Pipe::~Pipe()
{

}
