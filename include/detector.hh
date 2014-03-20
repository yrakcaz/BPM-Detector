#ifndef DETECTOR_HH
# define DETECTOR_HH

# include "sound-system.hh"

class Detector
{
    public:
        Detector();
        Detector(SoundSystem& system);
        ~Detector();

        SoundSystem& system_get();

    private:
        SoundSystem system_;
};

#endif /* !DETECTOR_HH */
