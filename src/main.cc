#include <cstring>
#include "../include/detector.hh"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << argv[0] << ": use " << argv[0] << " -h or --help." << std::endl;
        return 1;
    }
    else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
        std::cout << argv[0] << ": usage: " << argv[0] << " <SONG FILE>." << std::endl;
    else
    {
        SoundSystem system;
        system.load(argv[1]);
        system.start();
        system.pause();
        Detector detect(system);
        std::cout << detect.bpm_get() << std::endl;
    }
    return 0;
}
