#ifndef DETECTOR_HH
# define DETECTOR_HH

# include "sound-system.hh"
# include <vector>

/**
** @def WINDOW
** @brief Size of a song sample.
*/
# define WINDOW 4096

/**
** @def RATIO
** @brief Ratio for the peak detection.
*/
# define RATIO 1.3

/**
** @class Detector
** @brief Class which has to detect the BPM of the song.
*/
class Detector
{
    public:
        /**
        ** @fn Detector();
        ** @brief Default constructor.
        */
        Detector();
        /**
        ** @fn Detector(SoundSystem& system);
        ** @brief Principal constructor.
        ** @param system SoundSystem containing initialized song.
        */
        Detector(SoundSystem& system);
        /**
        ** @fn ~Detector();
        ** @brief Default destructor.
        */
        ~Detector();

        /**
        ** @fn SoundSystem& system_get();
        ** @brief Getter on the SoundSystem attribute.
        ** @return Returns the system_ attribute.
        */
        SoundSystem& system_get();
        /**
        ** @fn double bpm_get();
        ** @brief Final method which returns the bpm.
        ** @return Returns a double which is the bpm of the song.
        */
        double bpm_get();

    private:
        /**
        ** @fn int nrj_get(int* data, int offset);
        ** @brief Function which calculate the energy of a song sample.
        ** @param data Datas of the song.
        ** @param offset Offset of the sample into data.
        ** @return Returns an integer which represent the energy of the sample.
        */
        int nrj_get(int* data, int offset);
        /**
        ** @fn void peaks_set();
        ** @briefs Fill the energy peaks array.
        */
        void peaks_set();
        /**
        ** @fn void laps_set();
        ** Fills the laps array.
        */
        void laps_set();
        /**
        ** @fn double normalize(double bpm);
        ** @brief Divide or multiply per 2 the bpm while it isn't between 70 and 200.
        ** @param bpm Unnormalized bpm.
        ** @return Normalized bpm.
        */
        double normalize(double bpm);

    private:
        /**
        ** @var system_
        ** @brief SoundSystem containing the initialized song.
        */
        SoundSystem system_;
        /*
        ** @var nrj1024_
        ** @brief Vector representing energy.
        */
        std::vector<double> nrj1024_;
        /*
        ** @var nrj44100_
        ** @brief Vector representing energy 44100Hz.
        */
        std::vector<double> nrj44100_;
        /*
        ** @var peaks_
        ** @brief Vector representing energy peaks.
        */
        std::vector<bool> peaks_;
        /*
        ** @var laps_
        ** @brief Vector representing laps_ between energy peaks.
        */
        std::vector<int> laps_;
};

#endif /* !DETECTOR_HH */
