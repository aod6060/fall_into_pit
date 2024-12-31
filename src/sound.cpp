#include "SDL_mixer.h"
#include "sys.h"

namespace sound {

    std::map<std::string, Mix_Music*> musicStream;
    std::map<std::string, Mix_Chunk*> soundFXStream;

    float masterVolume = 1.0f;

    void init() {
        Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);
        Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
    }

    void release() {
        for(std::map<std::string, Mix_Music*>::iterator it = musicStream.begin(); it != musicStream.end(); it++) {
            Mix_FreeMusic(it->second);
        }
        musicStream.clear();

        for(std::map<std::string, Mix_Chunk*>::iterator it = soundFXStream.begin(); it != soundFXStream.end(); it++) {
            Mix_FreeChunk(it->second);
        }
        soundFXStream.clear();

        Mix_CloseAudio();
        Mix_Quit();
    }

    void addMusicStream(std::string name, std::string path) {
        musicStream[name] = Mix_LoadMUS(path.c_str());
    }

    void addSoundFXStream(std::string name, std::string path) {
        soundFXStream[name] = Mix_LoadWAV(path.c_str());
    }

    void setMasterVolume(float volume) {
        masterVolume = volume;
    }

    void setMusicVolume(float volume) {
        int v = (int)((volume * masterVolume)) * MIX_MAX_VOLUME;
        Mix_VolumeMusic(v);
    }

    void setSoundFXVolume(float volume) {
        int v = (int)((volume * masterVolume)) * MIX_MAX_VOLUME;
        Mix_Volume(-1, v);
    }


    // Music Player
    void MusicPlayer::init(std::string name) {
        this->name = name;
    }

    void MusicPlayer::release() {}
    
    void MusicPlayer::play(int numLoops) {
        Mix_PlayMusic(musicStream.at(this->name), numLoops);
    }

    void MusicPlayer::stop() {
        Mix_HaltMusic();
    }

    void MusicPlayer::resume() {
        Mix_ResumeMusic();
    }

    void MusicPlayer::puase() {
        Mix_PauseMusic();
    }

    bool MusicPlayer::isPlaying() {
        return Mix_PlayingMusic() ? true : false;
    }

    bool MusicPlayer::isPaused() {
        return Mix_PausedMusic() ? true : false;
    }

    void MusicPlayer::rewind() {
        Mix_RewindMusic();
    }

    void MusicPlayer::setPosition(double position) {
        Mix_SetMusicPosition(position);
    }

    double MusicPlayer::getPolision() {
        return Mix_GetMusicPosition(musicStream.at(this->name));
    }




    // SoundFXPlayer
    void SoundFXPlayer::init(std::string name) {
        this->name = name;
    }

    void SoundFXPlayer::release() {}

    void SoundFXPlayer::play(int channel, int loop) {
        this->channel = Mix_PlayChannel(channel, soundFXStream.at(name), loop);
    }

    void SoundFXPlayer::stop() {
        Mix_HaltChannel(this->channel);
    }

    void SoundFXPlayer::resume() {
        Mix_Resume(this->channel);
    }

    void SoundFXPlayer::pause() {
        Mix_Pause(this->channel);
    }

    void SoundFXPlayer::rewind() {
        Mix_Resume(this->channel);
    }

    bool SoundFXPlayer::isPlaying() {
        return Mix_Playing(this->channel);
    }

    bool SoundFXPlayer::isPaused() {
        return Mix_Paused(this->channel);
    }

}