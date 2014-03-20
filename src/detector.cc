#include "../include/detector.hh"

Detector::Detector()
{
}

Detector::Detector(SoundSystem& system)
    : system_(system)
{
}

Detector::~Detector()
{
}

SoundSystem& Detector::system_get()
{
    return system_;
}
