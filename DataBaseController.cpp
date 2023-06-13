#include "Include/DataBaseController.hpp"

void DataBaseController::insert(std::string tableName, size_t id, std::string value) {
    auto table = _tables.find(tableName);
    if (table != _tables.end()) {
         if (!table->second.insert(std::make_pair(id, value))) {
            throw InvalidOperation("duplicate " + std::to_string(id));
         }
    } else {
        throw InvalidOperation("unknown table \"" + tableName + '"');
    }
}