#include "Bird.h"
#include "Pipe.h"

#include <iostream>
#include <SDL.h>
#include <SDL_Image.h>

Bird::Bird()
    :   m_CurrentScore(0),
        m_Texture(NULL),
        m_CurrentY(600/2),
        m_NewY(0),
        m_Up(false),
        m_UpTime(1.5f),
        m_Time(0.0f)
{

}

bool Bird::IsHit(std::vector<Pipe*>* pipes)
{
    SDL_Rect birdRect = GetRect();

    if (birdRect.y < 0 || (birdRect.y + birdRect.h) > 500)
        return true;

    Pipe* pipe = (*pipes).at(m_CurrentScore+1);

    SDL_Rect topPipeRect = pipe->GetTopRect();
    SDL_Rect botPipeRect = pipe->GetBotRect();

    if (SDL_HasIntersection(&birdRect, &topPipeRect) == SDL_TRUE)
        return true;

    if (SDL_HasIntersection(&birdRect, &botPipeRect) == SDL_TRUE)
        return true;

    if ((pipe->GetTopRect().x + pipe->GetTopRect().w)  < birdRect.x)
    {
        ++m_CurrentScore;
        std::cout << "Score: " << m_CurrentScore << std::endl;
    }

    return false;
}

void Bird::Update(float val)
{
    m_CurrentY += val;
}

void Bird::Up()
{
    if(m_Up)
        return;

    m_Up = true;
    m_Time = SDL_GetTicks();
}

void Bird::Spawn(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load("img\\bird.png");

    if (!surface)
    {
        std::cout << " Could not spawn the bird\n" << IMG_GetError();
        return;
    }

    m_Texture = SDL_CreateTextureFromSurface(renderer, surface);

    if(!m_Texture)
    {
        std::cout << "Could not load bird texture\n" << SDL_GetError();
        return;
    }
    else
        std::cout << "Bird Spawned" << std::endl;

    SDL_FreeSurface(surface);
}

void Bird::Render(SDL_Renderer* renderer)
{
    SDL_Rect rect;

    rect.x = 800/2 - 64-2;
    rect.y = m_CurrentY;
    rect.h = 48;
    rect.w = 64;

    SDL_RenderCopy(renderer, m_Texture, NULL, &rect);
}


SDL_Rect Bird::GetRect()
{
    SDL_Rect rect;

    rect.x = 800/2 - 64-2;
    rect.y = m_CurrentY;
    rect.h = 42;
    rect.w = 58;

    return rect;
}

Bird::~Bird()
{
    SDL_DestroyTexture(m_Texture);
}
