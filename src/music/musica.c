#include "musica.h"

static Music musicaStarWars;
static Music musicaCantina;
static bool tocando_jogo = false;

void InitMusica(void)
{
    InitAudioDevice();

    musicaStarWars = LoadMusicStream("src/music/StarWarsMainTheme.mp3");
    musicaStarWars.looping = false;
    SetMusicVolume(musicaStarWars, 0.8f);

    musicaCantina = LoadMusicStream("src/music/Cantina Band - John Williams (youtube).mp3");
    musicaCantina.looping = true;
    SetMusicVolume(musicaCantina, 0.8f);

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
        UpdateMusicStream(musicaCantina);
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
        SeekMusicStream(musicaCantina, 0.0f);
        PlayMusicStream(musicaCantina);
    }

    else
    {
        StopMusicStream(musicaCantina);
        SeekMusicStream(musicaStarWars, 0.0f);
        PlayMusicStream(musicaStarWars);
    }
}

void UnloadMusica(void)
{
    UnloadMusicStream(musicaStarWars);
    UnloadMusicStream(musicaCantina);
    CloseAudioDevice();
}