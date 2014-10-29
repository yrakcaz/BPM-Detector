#ifndef SOUND_SYSTEM_HH
# define SOUND_SYSTEM_HH

# include <iostream>
# include "fmod.h"

/**
** @def SPECTRUM_SIZE
** @brief Maximum size of the song's spectrum.
*/
# define SPECTRUM_SIZE 8192

/**
** @class SoundSystem
** @brief Interface between FMOD API and and detector class.
*/
class SoundSystem
{
    public:
        /**
        ** @fn SoundSystem();
        ** @brief Default and principal constructor.
        */
        SoundSystem();
        /**
        ** @fn ~SoundSystem();
        ** @brief Default and principal destructor.
        */
        ~SoundSystem();

        /**
        ** @fn void load(const char* path);
        ** @brief Function which loads the song.
        ** @param path Path for the song file.
        */
        void load(const char* path);
        /**
        ** @fn void start();
        ** @brief Starts the song.
        */
        void start();
        /**
        ** @fn void play();
        ** @brief Plays the song.
        */
        void play();
        /**
        ** @fn void pause();
        ** @brief Pauses the song.
        */
        void pause();

        /**
        ** @fn int* left_data_get();
        ** @brief Gets the left_data of the song.
        ** @return Integer array with the left_data of the song.
        */
        int* left_data_get();
        /**
        ** @fn int* right_data_get();
        ** @brief Gets the right_data of the song.
        ** @return Integer array with the right_data of the song.
        */
        int* right_data_get();
        /**
        ** @fn float* spectrum_get();
        ** @brief Gets the spectrum of the song.
        ** @return Returns a float array containing the spectrum of the song.
        */
        float* spectrum_get();
        /**
        ** @fn unsigned int len_get() const;
        ** @brief Getter on the song length.
        ** @return Returns the length of the song.
        */
        unsigned int len_get() const;
        
        /**
        ** @fn float speed_get() const;
        ** @brief Getter on the speed of the song.
        ** @return Returns the speed of the song.
        */
        float speed_get() const;
        /**
        ** @fn void speed_set(float speed);
        ** @brief Setter on the speed of the song.
        ** @param speed Song speed to set.
        */
        void speed_set(float speed);

        /**
        ** @fn unsigned int position_get() const;
        ** @brief Getter on the current position.
        ** @return Returns the current position on the song.
        */
        unsigned int position_get() const;
        /**
        ** @fn void position_set(unsigned int position);
        ** @brief Setter on the current position.
        ** @param position Song position to set.
        */
        void position_set(unsigned int position);

    private:
        /**
        ** @var sys_
        ** @brief Pointer on FMOD_SYSTEM attribute.
        */
        FMOD_SYSTEM* sys_;
        /**
        ** @var chan_
        ** @brief Pointer on FMOD_CHANNEl attribute.
        */
        FMOD_CHANNEL* chan_;
        /**
        ** @var sound_
        ** @brief Pointer on FMOD_SOUND attribute containing the song.
        */
        FMOD_SOUND* sound_;
        /**
        ** @var left_fata_
        ** @brief Array containing left data of the song.
        */
        int* left_data_;
        /**
        ** @var right_data_
        ** @brief Array containing right data of the song.
        */
        int* right_data_;
        /**
        ** @var spectrum_
        ** @brief Array containing the spectrum of the song.
        */
        float* spectrum_;
        /**
        ** @var len_
        ** @brief Song length.
        */
        unsigned int len_;
        /**
        ** @var speed_
        ** @brief Song speed.
        */
        float speed_;
};

#endif /* !SOUND_SYSTEM_HH */
