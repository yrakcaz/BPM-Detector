#ifndef EXTRACTOR_HH
# define EXTRACTOR_HH

# include "sound-system.hh"

class Extractor
{
    public:
        Extractor();
        Extractor(SoundSystem& system);
        ~Extractor();

        double centroid_get();

    private:
        SoundSystem system_;
};

#endif /* !EXTRACTOR_HH */
