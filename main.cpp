#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include "Include/Server.hpp"
#include <iostream>
#include <stdexcept>

namespace po = boost::program_options;
uint32_t parse_command_options(int argc, char* argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help",                                                      "Print this message")
        ("port", po::value<uint32_t>()->required(),                   "Server port");

    po::variables_map vm;
    try {
        po::store(parse_command_line(argc, argv, desc), vm);
        if (vm.count("help") != 0) {
            std::cout << desc << "\n";
            throw;
        }
        po::notify(vm);
    }
    catch (const po::error& error) {
        std::cerr << "Error while parsing command-line arguments: "
                << error.what() << "\nPlease use --help to see help message\n";
        throw;
    }
    return vm["port"].as<uint32_t>();
}

enum class ECmd { one, two, three };

class C
{
public:

    void Command(ECmd e)
    {
        auto pos = m_fnCmd.find(e);

        if (pos != m_fnCmd.end())
        {
            // call the function
            (pos->second)(this);
         }
        else
        {
            printf("no command!\n");
        }
    }

protected:
    using fnCmd = std::function<void(C*)>;
    using fnCmdMap = std::map<ECmd, fnCmd>;

    static const fnCmdMap m_fnCmd;

    // the command functions
    void One() { printf("one.\n"); }
    void Two() { printf("Two.\n"); }
    void Three() { printf("Three.\n"); }
};

const C::fnCmdMap C::m_fnCmd =
{
    {std::make_pair(ECmd::one, &C::One)},
    {std::make_pair(ECmd::two, &C::Two)},
    {std::make_pair(ECmd::three, &C::Three)},
};

int main(int argc, char* argv[]) {
    try {
        uint32_t port;
        try {
            port = parse_command_options(argc, argv);
        }
        catch (...) {
            return 0;
        }
        boost::asio::io_service io_context;
        Server server(io_context, port);
        io_context.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

