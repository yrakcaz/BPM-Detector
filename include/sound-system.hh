#ifndef SOUND_SYSTEM_HH
# define SOUND_SYSTEM_HH

# include <iostream>
# include "FMOD/fmod.h"

# define SPECTRUM_SIZE 8192

class SoundSystem
{
    public:
        SoundSystem();
        ~SoundSystem();

        void load(const char* path);
        void start();
        void play();
        void pause();

        int* left_data_get();
        int* right_data_get();
        float* spectrum_get();
        unsigned int len_get() const;

        float speed_get() const;
        void speed_set(float speed);

        unsigned int position_get() const;
        void position_set(unsigned int position);

    private:
        FMOD_SYSTEM* sys_;
        FMOD_CHANNEL* chan_;
        FMOD_SOUND* sound_;
        int* left_data_;
        int* right_data_;
        float* spectrum_;
        unsigned int len_;
        float speed_;
};

#endif /* !SOUND_SYSTEM_HH */
