#include <cstring>
#include "../include/detector.hh"
#include "../include/extractor.hh"

int main(int argc, char** argv)
{
    if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")))
        std::cout << "Help have to be done soon!" << std::endl;
    else if (argc == 3)
    {
        if (!strcmp(argv[1], "-b") || !strcmp(argv[1], "--bpm"))
        {
            SoundSystem system;
            system.load(argv[2]);
            system.start();
            system.pause();
            Detector detect(system);
            std::cout << detect.bpm_get() << std::endl;
        }
        else if (!strcmp(argv[1], "-c") || !strcmp(argv[1], "--centroid"))
        {
            SoundSystem system;
            system.load(argv[2]);
            system.start();
            system.pause();
            Extractor extract(system);
            std::cout << extract.centroid_get() << std::endl;
        }
        else
        {
            std::cerr << argv[0] << ": use " << argv[0] << " --help" << std::endl;
            return 1;
        }
    }
    else
    {
        std::cerr << argv[0] << ": use " << argv[0] << " --help" << std::endl;
        return 1;
    }
    return 0;
}
