#ifndef SOUND_SYSTEM_HH
# define SOUND_SYSTEM_HH

# include "FMOD/fmod.h"

class SoundSystem
{
    public:
        SoundSystem();
        ~SoundSystem();

        void load(const char* path);
        void play();
        void pause();

        int* left_data_get();
        int* right_data_get();
        float* spectrum_get();
        unsigned int len_get() const;

        float speed_get() const;
        void speed_set(float speed);

        int position_get() const;
        void position_set(int position);

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
