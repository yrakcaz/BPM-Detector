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
        //std::cout << "Left: " << left_data_[i] << std::endl;
        //std::cout << "Right: " << right_data_[i] << std::endl;
        i++;
    }
    FMOD_Sound_Unlock(sound_, addr1, addr2, len1, len2);
}

void SoundSystem::start()
{
    FMOD_System_PlaySound(sys_, FMOD_CHANNEL_FREE, sound_, 0, 0);
    FMOD_System_GetChannel(sys_, 0, &chan_);
}

void SoundSystem::play()
{
    FMOD_BOOL state;
    FMOD_Channel_GetPaused(chan_, &state);
    FMOD_Channel_SetFrequency(chan_, 44100.f * speed_);
    if (state)
        FMOD_Channel_SetPaused(chan_, 0);
}

void SoundSystem::pause()
{
    FMOD_BOOL state;
    FMOD_Channel_GetPaused(chan_, &state);
    FMOD_Channel_SetFrequency(chan_, 44100.f * speed_);
    if (!state)
        FMOD_Channel_SetPaused(chan_, 1);
}

int* SoundSystem::left_data_get()
{
    return left_data_;
}

int* SoundSystem::right_data_get()
{
    return right_data_;
}

float* SoundSystem::spectrum_get()
{
    FMOD_System_Update(sys_);
    float* spectrum = new float[SPECTRUM_SIZE + 1];
    FMOD_Channel_GetSpectrum(chan_, spectrum, SPECTRUM_SIZE,
                             position_get(), FMOD_DSP_FFT_WINDOW_TRIANGLE);
    return spectrum;
}

unsigned int SoundSystem::len_get() const
{
    return len_;
}

float SoundSystem::speed_get() const
{
    return speed_;
}

void SoundSystem::speed_set(float speed)
{
    pause();
    speed_ = speed;
    play();
}

unsigned int SoundSystem::position_get() const
{
    unsigned int ret = 0;
    FMOD_Channel_GetPosition(chan_, &ret, FMOD_TIMEUNIT_PCM);
    return ret;
}

void SoundSystem::position_set(unsigned int position)
{
    FMOD_Channel_SetPosition(chan_, position, FMOD_TIMEUNIT_PCM);
}
