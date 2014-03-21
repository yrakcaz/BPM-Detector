#include "../include/detector.hh"
#include "../include/args.hh"

int main(int argc, char** argv)
{
    Args args(argc, argv);
    args.push_arg("--display");
    args.compute();
    int pos;
    if ((pos = args.map_get()["--display"]) != 0 && argc >= pos)
    {
        SoundSystem system;
        system.load(argv[pos + 1]);
        system.start();
        system.pause();
        Detector detect(system);
        std::cout << detect.bpm_get() << std::endl;
    }
    else
        return 1;
    return 0;
}
