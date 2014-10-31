#include "../include/extractor.hh"

#define ABS(X) \
    X >= 0 ? X : -X

Extractor::Extractor()
{
}

Extractor::Extractor(SoundSystem& system)
    : system_(system)
{
}

Extractor::~Extractor()
{
}

//DEBUG THIS:
double Extractor::centroid_get()
{
    double nbin = 0;
    double num = 0;
    double denom = 0;
    float *spectrum = system_.spectrum_get();

    for (int i = 0; i < SPECTRUM_SIZE; i++)
    {
        double f = (44100 / 2) / SPECTRUM_SIZE;
        f *= nbin;
        num += (f * ABS(spectrum[i]));
        denom += ABS(spectrum[i]);
        nbin++;
    }

    return ((num / denom);
}
