#include "musica.h"

static Music musicaStarWars;

void InitMusica(void)
{
    InitAudioDevice();
    musicaStarWars = LoadMusicStream("src/music/starwars.wav");
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

void StopMusica(void)
{
    StopMusicStream(musicaStarWars);
}

void UnloadMusica(void)
{
    UnloadMusicStream(musicaStarWars);
    CloseAudioDevice();
}