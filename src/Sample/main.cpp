#include "GameManager.h"
#include "SampleScene.h"

int main()
{
    GameManager* game = GameManager::Get();

    game->LaunchScene<SampleScene>(720, 720, "SampleScene", Color{ 25, 25, 35 });

    return 0;
}
