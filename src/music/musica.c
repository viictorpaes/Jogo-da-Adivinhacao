#include "musica.h"

static Music musicaStarWars;

void InitMusica(void)
{
    InitAudioDevice();
    musicaStarWars = LoadMusicStream("src/music/StarWarsMainTheme.mp3");
    musicaStarWars.looping = false;
    SetMusicVolume(musicaStarWars, 0.8f);
    PlayMusicStream(musicaStarWars);
}

void UpdateMusica(void)
{
    UpdateMusicStream(musicaStarWars);
    if (GetMusicTimePlayed(musicaStarWars) >= 70.0f) 
    {
        SeekMusicStream(musicaStarWars, 0.0f);
    }
}

void UnloadMusica(void)
{
    UnloadMusicStream(musicaStarWars);
    CloseAudioDevice();
}