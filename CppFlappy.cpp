#include "CppFlappy.h"
#include "Bird.h"
#include "World.h"
#include "Pipe.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

CppFlappy::CppFlappy()
    :   m_Init(false),
        m_Window(NULL),
        m_StartScreen(NULL),
        m_Renderer(NULL),
        m_Bird(NULL),
        m_World(NULL),
        m_score(0)
{

}

void CppFlappy::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Error: Could not init SDL\n" << SDL_GetError();
        m_Init = false;
        return;
    }

    if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ))
        std::cout << "Warning: Linear Texture filtering is not enabled" << std::endl;

    m_Window = SDL_CreateWindow("CppFlappy - Written by ManhNTSE04004", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!m_Window)
    {
        std::cout << "Error: Could not create SDL Window" << std::endl;
        m_Init = false;
        return;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    if (!m_Renderer)
    {
        std::cout << "Could not create renderer\n" << SDL_GetError();
        return;
    }

    SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "Error: Could not init SDLImage\n" << IMG_GetError();
        m_Init = false;
        return;
    }

    SDL_Surface* surface = NULL;

    surface = IMG_Load("img//startscreen.png");

    if (!surface)
    {
        std::cout << " Could not load Start Screen\n" << IMG_GetError();
        return;
    }

    m_StartScreen = SDL_CreateTextureFromSurface(m_Renderer, surface);

    if(!m_StartScreen)
    {
        std::cout << "Could not draw Start Screen\n" << SDL_GetError();
        return;
    }
    else
        std::cout << "Loaded StartScreen" << std::endl;

    SDL_FreeSurface(surface);

    m_Init = true;
}

void CppFlappy::DrawStartScreen()
{
    bool stop = false;
    while (!stop)
    {
        while(SDL_PollEvent(&m_Event) != 0)
        {
            if( m_Event.type == SDL_KEYDOWN )
            {
                stop = true;
            }
        }

        SDL_RenderCopy(m_Renderer, m_StartScreen, NULL, NULL);
        SDL_RenderPresent(m_Renderer);
    }

    SDL_RenderClear(m_Renderer);
}

int CppFlappy::Run()
{
    if (!m_Init)
    {
        Init();
        TTF_Init();
        

        if (!m_Init)
        {
            std::cout << "Fatal Error" << std::endl;
            return -1;
        }
    }

    DrawStartScreen();

    m_Bird = new Bird;
    m_Bird->Spawn(m_Window, m_Renderer);

    m_World = new World(m_Window, m_Renderer);

    unsigned int lastTime = 0, currentTime;
    float dt;
    TTF_Font* Sans = TTF_OpenFont("font//font_score.ttf",24);

    float time = 0.0f;
    float mapMoveTime = 0.0f;
    float mapLevel = 0.01f;

    bool quit = false;
    bool up = false;
    while (!quit)
    {
        currentTime = SDL_GetTicks();

        dt = (currentTime - lastTime) / 1000.f;

        lastTime = currentTime;

        while (SDL_PollEvent(&m_Event) != 0)
        {
            if (m_Event.type == SDL_KEYDOWN)
            {

                switch (m_Event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    {
                        up = true;
                    }
                    break;

                case SDLK_ESCAPE:
                    {
                        quit = true;
                        std::cout << "User pressed Escape, exiting" << std::endl;
                    }
                    break;
                }

            }
        }

        time += dt;
        mapMoveTime += dt;

        if (mapMoveTime > mapLevel)
        {
            m_World->MoveLeft();
            mapMoveTime = 0.0f;
        }

        if (time > 0.01f)
        {
            if (up)
            {
                m_Bird->Update(-10);
                up = false;
            }
            else
                m_Bird->Update(0.5f);

            time = 0.0f;
        }

        //SDL_RenderClear(m_Renderer);

        m_World->RenderBackground(m_Renderer);
        m_World->RenderFloor(m_Renderer);

        m_World->RenderPipes(m_Window, m_Renderer);

        m_Bird->Render(m_Renderer);
        m_World->RenderScore(m_Window,Sans,m_Renderer,m_Bird->m_CurrentScore);

        SDL_RenderPresent(m_Renderer);

        if (m_Bird->IsHit(m_World->GetPipes()))
        {
            std::cout << "Die" << std::endl;

            while (!quit)
            {
                while (SDL_PollEvent(&m_Event) != 0)
                {
                    if (m_Event.type == SDL_KEYDOWN)
                    quit = true;
                }

                m_World->RenderBackground(m_Renderer);
                m_World->RenderFloor(m_Renderer);

                m_World->RenderPipes(m_Window, m_Renderer);

                m_Bird->Render(m_Renderer);
                m_World->RenderScore(m_Window,Sans,m_Renderer,m_Bird->m_CurrentScore);
                SDL_RenderPresent(m_Renderer);
            }
        }

        m_World->RenderScore(m_Window,Sans,m_Renderer,m_Bird->m_CurrentScore);
    }

    return m_Bird->m_CurrentScore;
}

void CppFlappy::EndGame(int score)
{
    if (m_Bird)
    {
        delete m_Bird;
        m_Bird = NULL;
    }

}

void CppFlappy::Quit()
{
    if (m_Renderer)
        SDL_RenderClear(m_Renderer);

    if (m_Bird)
        delete m_Bird;

    if (m_StartScreen)
        SDL_DestroyTexture(m_StartScreen);

	if (m_Window)
        SDL_DestroyWindow(m_Window);

    if (m_Renderer)
        SDL_DestroyRenderer(m_Renderer);

	IMG_Quit();
	SDL_Quit();
}

CppFlappy::~CppFlappy()
{

}
