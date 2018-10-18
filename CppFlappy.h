#ifndef CPPFLAPPY_H
#define CPPFLAPPY_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include <SDL2/SDL_events.h>

class SDL_Texture;
class SDL_Window;
class SDL_Renderer;

class Bird;
class World;

class CppFlappy
{
public:
                                CppFlappy();
    virtual                     ~CppFlappy();

    int                         Run();
    void                        EndGame(int score);

    void                        Quit();

private:
    void                        Init();
    void                        DrawStartScreen();
  
    bool                        m_Init;

    SDL_Window*                 m_Window;
    SDL_Texture*                m_StartScreen;

    SDL_Event                   m_Event;

    SDL_Renderer*               m_Renderer;
private:
    Bird*                       m_Bird;
    World*                      m_World;

    int                         m_score;
};

#endif // CPPFLAPPY_H
