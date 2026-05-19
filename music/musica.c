#include "musica.h"

#define MUSICA_DURACAO_MAX 50.0f

static Music musicaStarWars;

void InitMusica(void)
{
    InitAudioDevice();
    musicaStarWars = LoadMusicStream("music/starwars.wav");
    musicaStarWars.looping = false;
    SetMusicVolume(musicaStarWars, 0.5f);
    PlayMusicStream(musicaStarWars);
}

void UpdateMusica(void)
{
    UpdateMusicStream(musicaStarWars);
    if (GetMusicTimePlayed(musicaStarWars) >= MUSICA_DURACAO_MAX) 
    {
        PlayMusicStream(musicaStarWars);
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