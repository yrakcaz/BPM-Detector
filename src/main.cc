#include "../include/detector.hh"

int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;
    SoundSystem system;
    system.load(argv[1]);
    system.start();
    system.pause();
    Detector detect(system);
    float* spectrum = detect.system_get().spectrum_get();
    for (int i = 0; i < SPECTRUM_SIZE; i++)
        std::cout << spectrum[i] << std::endl;
    return 0;
}
