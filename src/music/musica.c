#include "musica.h"

static Music musicaStarWars;
static Music musicaCantinaToyStory;
static bool tocando_jogo = false;

void InitMusica(void)
{
    InitAudioDevice();

    musicaStarWars = LoadMusicStream("src/music/StarWarsMainTheme.mp3");
    musicaStarWars.looping = false;
    SetMusicVolume(musicaStarWars, 0.8f);

    musicaCantinaToyStory = LoadMusicStream("src/music/Cantina Band - John Williams (youtube).mp3");
    musicaCantinaToyStory.looping = true;
    SetMusicVolume(musicaCantinaToyStory, 0.8f);

    PlayMusicStream(musicaStarWars);
}

void UpdateMusica(void)
{
    if (!tocando_jogo)
    {
        UpdateMusicStream(musicaStarWars);

        if (GetMusicTimePlayed(musicaStarWars) >= 70.0f) 
        {
            SeekMusicStream(musicaStarWars, 0.0f);
        }
    }

    else
    {
        UpdateMusicStream(musicaCantinaToyStory);
    }
}

void TrocarMusica(bool para_jogo)
{
    if (para_jogo == tocando_jogo) 
    {
        return;
    }
    
    tocando_jogo = para_jogo;

    if (para_jogo)
    {
        StopMusicStream(musicaStarWars);
        SeekMusicStream(musicaCantinaToyStory, 0.0f);
        PlayMusicStream(musicaCantinaToyStory);
    }

    else
    {
        StopMusicStream(musicaCantinaToyStory);
        SeekMusicStream(musicaStarWars, 0.0f);
        PlayMusicStream(musicaStarWars);
    }
}

void UnloadMusica(void)
{
    UnloadMusicStream(musicaStarWars);
    UnloadMusicStream(musicaCantinaToyStory);
    CloseAudioDevice();
}