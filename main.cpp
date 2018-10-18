#include "CppFlappy.h"

int main()
{
    CppFlappy* game = new CppFlappy;

    int score = game->Run();

    game->EndGame(score);

    game->Quit();

    delete game;

    return 0;
}
