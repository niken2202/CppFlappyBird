#ifndef BIRD_H
#define BIRD_H

#include <SDL_rect.h>
#include <vector>

class Pipe;
class SDL_Texture;
class SDL_Window;
class SDL_Renderer;

class Bird
{
public:
                                Bird();
    virtual                     ~Bird();

    void                        Spawn(SDL_Window* window, SDL_Renderer* renderer);

    void                        Update(float val);

    void                        Up();

    void                        Render(SDL_Renderer* renderer);

    SDL_Rect                    GetRect();

    int                         m_CurrentScore;

    bool                        IsHit(std::vector<Pipe*>* pipes);

private:
    SDL_Texture*                m_Texture;

    float                       m_CurrentY;
    int                         m_NewY;

    bool                        m_Up;
    const float                 m_UpTime;
    float                       m_Time;
};

#endif // BIRD_H
