#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <SDL_rect.h>

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
