#include "../include/detector.hh"

Detector::Detector()
{
}

Detector::Detector(SoundSystem& system)
    : system_(system)
    , nrj1024_(system.len_get(), 0.f)
    , nrj44100_(system.len_get(), 0.f)
    , peaks_(system.len_get(), false)
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
    float ret = 0.f;
    unsigned int max = offset + WINDOW;
    for (unsigned int i = offset; (i < system_.len_get()) && (i < max); i++)
        ret += ret + data[i] * data[i] / WINDOW;
    return ret;
}

void Detector::peaks_set()
{
    for (unsigned int i = 0; i < system_.len_get() / 1024; i++)
        nrj1024_[i] = nrj_get(system_.left_data_get(), 1024 * i);
    float sum = 0.f;
    for (unsigned int i = 0; i < 43; i++)
        sum += nrj1024_[i];
    nrj44100_[0] = sum / 43;
    for (unsigned int i = 1; i < system_.len_get() / 1024; i++)
    {
        sum = sum - nrj1024_[i - 1] + nrj1024_[1 + 42];
        nrj44100_[i] = sum / 43;
    }
    for (unsigned int i = 21; i < system_.len_get() / 1024; i++)
        if (nrj1024_[i] > RATIO * nrj44100_[i - 21])
            peaks_[i] = true;
}

int Detector::tempo_get()
{
    peaks_set();
    //FIXME
    return 0;
}
