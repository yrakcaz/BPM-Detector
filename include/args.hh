#ifndef ARGS_HH
# define ARGS_HH

# include <list>
# include <map>
# include <string>

class Args
{
    public:
        Args();
        Args(int argc, char** argv);
        ~Args();

        void push_arg(const char* arg);
        void compute();
        std::map<const char*, int> map_get() const;

    private:
        int argc_;
        char** argv_;
        std::list<const char*> args_;
        //map_[arg] = position, position = 0 if arg doesn't exist.
        std::map<const char*, int> map_;
};

#endif /* !ARGS_HH */
