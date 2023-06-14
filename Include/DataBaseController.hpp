#ifndef DATA_BASE_CONTROLLER_HPP
#define DATA_BASE_CONTROLLER_HPP

#include <map>
#include <string>
#include <vector>
#include "DataBase.hpp"
#include <string_view>
#include <stdexcept>

class DataBaseController {
public:
    using ResultType = std::vector<std::tuple<int, std::string, std::string>>;

    class InvalidOperation: public std::runtime_error {
    public:
        InvalidOperation(std::string const &message):
        std::runtime_error(message) { }
    };

    void insert(std::string tableName, size_t id, std::string value);
    void truncate(std::string tableName);
    ResultType insertion();
    ResultType symmetricDifference();

private:
    std::mutex _mutex{};
    std::map<std::string, DataBase> _tables {
        {std::make_pair("A", DataBase())}, 
        {std::make_pair("B", DataBase())}
    };
};

#endif