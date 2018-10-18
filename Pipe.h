#ifndef PIPE_H
#define PIPE_H

#include <SDL2/SDL_rect.h>

class SDL_Texture;
class SDL_Window;
class SDL_Renderer;

class Pipe
{
public:
                                Pipe(SDL_Window* window, SDL_Renderer* renderer, int type);
    virtual                     ~Pipe();

    void                        MoveLeft();
    void                        Render(SDL_Renderer* renderer);

    void                        MoveTo(int x);

    SDL_Rect                    GetTopRect();
    SDL_Rect                    GetBotRect();

private:
    int                         m_Type;

    SDL_Texture*                m_PipeTop;
    SDL_Texture*                m_PipeBot;

    SDL_Rect                    m_TopRect;
    SDL_Rect                    m_BotRect;

};

inline void Pipe::MoveTo(int x)
{
    m_TopRect.x = x;
    m_BotRect.x = x;
}
inline SDL_Rect Pipe::GetTopRect()
{
    return m_TopRect;
}

inline SDL_Rect Pipe::GetBotRect()
{
    return m_BotRect;
}

inline void Pipe::MoveLeft()
{
    --m_TopRect.x;
    --m_BotRect.x;
}

#endif // PIPE_H
