#include "../include/detector.hh"

Detector::Detector()
{
}

Detector::Detector(SoundSystem& system)
    : system_(system)
    , nrj1024_(system.len_get(), 0.f)
    , nrj44100_(system.len_get(), 0.f)
    , peaks_(system.len_get(), false)
    , laps_(system.len_get(), 0)
{
}

Detector::~Detector()
{
}

SoundSystem& Detector::system_get()
{
    return system_;
}

int Detector::nrj_get(int* data, int offset)
{
    double ret = 0.f;
    unsigned int max = offset + WINDOW;
    for (unsigned int i = offset; (i < system_.len_get()) && (i < max); i++)
        ret = ret + data[i] * data[i] / WINDOW;
    return (int)ret;
}

void Detector::peaks_set()
{
    int* data = system_.left_data_get();
    for (unsigned int i = 0; i < system_.len_get() / 1024; i++)
        nrj1024_[i] = nrj_get(data, 1024 * i);
    double sum = 0.f;
    for (unsigned int i = 0; i < 43; i++)
        sum += nrj1024_[i];
    nrj44100_[0] = sum / 43;
    for (unsigned int i = 1; i < system_.len_get() / 1024; i++)
    {
        sum = sum - nrj1024_[i - 1] + nrj1024_[i + 42];
        nrj44100_[i] = sum / 43;
    }
    for (unsigned int i = 21; i < system_.len_get() / 1024; i++)
        if (nrj1024_[i] > RATIO * nrj44100_[i - 21])
            peaks_[i] = true;
}

void Detector::laps_set()
{
    peaks_set();
    int prec = 0;
    for (unsigned int i = 1; i < system_.len_get() / 1024; i++)
    {
        if (peaks_[i] && !peaks_[i - 1])
        {
            int d = i - prec;
            if (d > 5)
            {
                laps_.push_back(d);
                prec = i;
            }
        }
    }
}

double Detector::normalize(double bpm)
{
    if (bpm < 70)
        while (bpm < 70)
            bpm *= 2;
    else if (bpm > 200)
        while (bpm > 200)
            bpm /= 2;
    return bpm;
}

double Detector::bpm_get()
{
    laps_set();
    int occ[86];
    for (int i = 0; i < 86; i++)
        occ[i] = 0;
    for (unsigned int i = 1; i < laps_.size(); i++)
        if (laps_[i] <= 86)
            occ[laps_[i]]++;
    int tmax = 0;
    int max = 0;
    double moy = 0.f;
    for (int i = 1; i < 86; i++)
    {
        if (occ[i] > max)
        {
            tmax = i;
            max = occ[i];
        }
    }
    int prec = tmax - 1;
    if (occ[tmax + 1] > occ[prec])
        prec = tmax + 1;
    double div = occ[tmax] + occ[prec];
    moy = !div ? 0 : (double)((tmax * occ[tmax]) + (prec * occ[prec])) / div;
    return normalize(60.f / (moy * (1024.f / 44100.f)));
}
