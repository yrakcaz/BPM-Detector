#include "../include/sound-system.hh"

int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;
    SoundSystem system;
    system.load(argv[1]);
    system.play();
    return 0;
}
