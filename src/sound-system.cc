#include "../include/sound-system.hh"

SoundSystem::SoundSystem()
    : chan_(0)
    , speed_(1.0)
{
    FMOD_System_Create(&sys_);
    FMOD_System_Init(sys_, 1, FMOD_INIT_NORMAL, 0);
}

SoundSystem::~SoundSystem()
{
    FMOD_System_Release(sys_);
}

void SoundSystem::load(const char* path)
{
    FMOD_System_CreateSound(sys_, path, FMOD_SOFTWARE | FMOD_2D, 0, &sound_);
    FMOD_Sound_SetLoopCount(sound_, -1);
    FMOD_Sound_GetLength(sound_, &len_, FMOD_TIMEUNIT_PCM);
    left_data_ = new int[len_];
    right_data_ = new int[len_];
    void* addr1;
    void* addr2;
    unsigned int len1;
    unsigned int len2;
    FMOD_Sound_Lock(sound_, 0, len_, &addr1, &addr2, &len1, &len2);
    unsigned int i = 0;
    while (i < len_)
    {
        left_data_[i] = ((int*)addr1)[i] >> 16;
        right_data_[i] = (((int*)addr1)[i] << 16) >> 16;
        i++;
    }
    FMOD_Sound_Unlock(sound_, addr1, addr2, len1, len2);
}

void SoundSystem::play()
{
    FMOD_System_PlaySound(sys_, FMOD_CHANNEL_FREE, sound_, 0, 0);
    FMOD_System_GetChannel(sys_, 0, &chan_);
}
