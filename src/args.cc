#include "../include/args.hh"

Args::Args()
{
}

Args::Args(int argc, char** argv)
    : argc_(argc)
    , argv_(argv)
{
}

Args::~Args()
{
}

void Args::push_arg(const char* arg)
{
    args_.push_front(arg);
}

void Args::compute()
{
    std::list<const char*>::iterator it = args_.begin();
    while (it != args_.end())
    {
        for (int i = 1; i < argc_; i++)
        {
            if (argv_[i] == std::string(*it))
            {
                map_[*it] = i;
                break;
            }
            else
                map_[*it] = 0;
        }
        it++;
    }
}

std::map<const char*, int> Args::map_get() const
{
    return map_;
}
