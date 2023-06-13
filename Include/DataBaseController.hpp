#ifndef DATA_BASE_CONTROLLER_HPP
#define DATA_BASE_CONTROLLER_HPP

#include <map>
#include <string>
#include "DataBase.hpp"
#include <string_view>
#include <stdexcept>

class DataBaseController {
public:
    DataBaseController() {
        _tables.try_emplace("A");
        _tables.try_emplace("B");
    }

    class InvalidOperation: public std::runtime_error {
    public:
        InvalidOperation(std::string const &message):
        std::runtime_error(message) { }
    };

    void insert(std::string tableName, size_t id, std::string value);
private:

    std::map<std::string, DataBase> _tables;
};

#endif