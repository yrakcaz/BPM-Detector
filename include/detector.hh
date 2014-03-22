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
        double bpm_get();

    private:
        int nrj_get(int* data, int offset);
        void peaks_set();
        void laps_set();

    private:
        SoundSystem system_;
        std::vector<double> nrj1024_;
        std::vector<double> nrj44100_;
        std::vector<bool> peaks_;
        std::vector<int> laps_;
};

#endif /* !DETECTOR_HH */
