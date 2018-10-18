#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>
class SDL_Texture;
class SDL_Window;
class SDL_Renderer;

class Pipe;

class World
{
public:
                                World(SDL_Window* window, SDL_Renderer* renderer);
    virtual                     ~World();

    void                        RenderBackground(SDL_Renderer* renderer);
    void                        RenderFloor(SDL_Renderer* renderer);

    void                        RenderPipes(SDL_Window* window, SDL_Renderer* renderer);

    void                        MoveLeft();

    Pipe*                       GetCurrentPipe();
    std::vector<Pipe*>*         GetPipes();
    void                        RenderScore(SDL_Window* window,TTF_Font* Sans, SDL_Renderer* renderer,int score);
private:
    SDL_Texture*                m_Background;
    SDL_Texture*                m_Floor;

    std::vector<Pipe*>          m_Pipes;
    int                         m_PipeDistance;
};

inline std::vector<Pipe*>* World::GetPipes()
{
    return &m_Pipes;
}

#endif // WORLD_H
