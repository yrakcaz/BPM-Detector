#ifndef DETECTOR_HH
# define DETECTOR_HH

# include "sound-system.hh"
# include <vector>

# define WINDOW 4096
# define RATIO 1.3

class Detector
{
    public:
        Detector();
        Detector(SoundSystem& system);
        ~Detector();

        SoundSystem& system_get();
        int tempo_get();

    private:
        int nrj_get(int* data, int offset);
        void peaks_set();

    private:
        SoundSystem system_;
        std::vector<float> nrj1024_;
        std::vector<float> nrj44100_;
        std::vector<bool> peaks_;
};

#endif /* !DETECTOR_HH */
