#include "musica.h"

static Music musicaStarWars;

void InitMusica(void) 
{
    InitAudioDevice();
    musicaStarWars = LoadMusicStream("music/starwars.wav");
    musicaStarWars.looping = true;
    SetMusicVolume(musicaStarWars, 0.5f);
    PlayMusicStream(musicaStarWars);
}

void UpdateMusica(void) 
{
    UpdateMusicStream(musicaStarWars);
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