#ifndef __MAPNIK_BENCH_FRAMEWORK_HPP__
#define __MAPNIK_BENCH_FRAMEWORK_HPP__ 

// mapnik
#include <mapnik/params.hpp>
#include <mapnik/value_types.hpp>

// boost
#define BOOST_CHRONO_HEADER_ONLY
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/chrono.hpp>

// stl
#include <iostream>
#include <thread>
#include <vector>
#include <set>

namespace benchmark {

class test_case
{
protected:
    mapnik::parameters params_;
    std::size_t threads_;
    std::size_t iterations_;
public:
    test_case(mapnik::parameters const& params)
       : params_(params),
         threads_(*params.get<mapnik::value_integer>("threads",0)),
         iterations_(*params.get<mapnik::value_integer>("iterations",0))
         {}
    std::size_t threads() const
    {
        return threads_;
    }
    std::size_t iterations() const
    {
        return iterations_;
    }
    virtual bool validate() const = 0;
    virtual void operator()() const = 0;
    virtual ~test_case() {}
};

void handle_args(int argc, char** argv, mapnik::parameters & params)
{
    if (argc > 0) {
        for (int i=1;i<argc;++i) {
            std::string opt(argv[i]);
            // parse --foo bar / -foo bar syntax
            if (!opt.empty() && opt[0] != '-') {
                std::string key = std::string(argv[i-1]);
                if (!key.empty() && key[0] == '-') {
                    key = key.substr(key.find_first_not_of("-"));
                    params[key] = opt;
                }
            }
        }
    }
}

#define BENCHMARK(test_class,name) \
    int main(int argc, char** argv)      \
    {                                    \
        mapnik::parameters params;       \
        benchmark::handle_args(argc,argv,params);   \
        test_class test_runner(params);        \
        return run(test_runner,name);    \
    }                                    \

template <typename T>
int run(T const& test_runner, std::string const& name)
{
    try
    {
        if (!test_runner.validate())
        {
            std::clog << "test did not validate: " << name << "\n";
            return -1;
        }
        boost::chrono::process_cpu_clock::time_point start;
        boost::chrono::process_cpu_clock::duration elapsed;
        std::clog << name << ": ";
        if (test_runner.threads() > 0)
        {
            typedef std::vector<std::unique_ptr<std::thread> > thread_group;
            typedef thread_group::value_type value_type;
            thread_group tg;
            for (std::size_t i=0;i<test_runner.threads();++i)
            {
                tg.emplace_back(new std::thread(test_runner));
            }
            start = boost::chrono::process_cpu_clock::now();
            std::for_each(tg.begin(), tg.end(), [](value_type & t) {if (t->joinable()) t->join();});
            elapsed = boost::chrono::process_cpu_clock::now() - start;
        }
        else
        {
            start = boost::chrono::process_cpu_clock::now();
            test_runner();
            elapsed = boost::chrono::process_cpu_clock::now() - start;
        }
        std::clog << boost::chrono::duration_cast<boost::chrono::milliseconds>(elapsed)
            << " t:" << test_runner.threads()
            << " i:" << test_runner.iterations() << "\n";
        return 0;
    }
    catch (std::exception const& ex)
    {
        std::clog << "test runner did not complete: " << ex.what() << "\n";
        return -1;
    }
    return 0;
}

}

#endif // __MAPNIK_BENCH_FRAMEWORK_HPP__