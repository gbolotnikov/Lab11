#include "Include/DataBaseController.hpp"

void DataBaseController::insert(std::string tableName, size_t id, std::string value) {
    bool result = false;
    auto table = _tables.find(tableName);
    if (table != _tables.end()) {
        {
            std::lock_guard lock(_mutex);
            result = table->second.insert(std::make_pair(id, value));
        }
        if (!result) {
            throw InvalidOperation("duplicate " + std::to_string(id));
        }
    } else {
        throw InvalidOperation("unknown table \"" + tableName + '"');
    }
}

void DataBaseController::truncate(std::string tableName) {
    auto table = _tables.find(tableName);
    if (table != _tables.end()) {
        std::lock_guard lock(_mutex);
        table->second.trancate();
    } else {
        throw InvalidOperation("unknown table \"" + tableName + '"');
    }
}

DataBaseController::ResultType DataBaseController::insertion() {
    ResultType out;
    std::lock_guard lock(_mutex);
    const auto& tableA = _tables["A"].data();
    const auto& tableB = _tables["B"].data();
    for (auto const &[id, value]: tableA) {
        auto res = tableB.find(id);
        if (res != tableB.end()) {
            out.push_back({std::make_tuple(id, value, res->second)});
        }
    }
    return out;
}

DataBaseController::ResultType DataBaseController::symmetricDifference() {
    ResultType out;
    std::lock_guard lock(_mutex);
    const auto& tableA = _tables["A"].data();
    const auto& tableB = _tables["B"].data();
    for (auto const &[id, value]: tableA) {
        if (tableB.find(id) == tableB.end())  {
            out.push_back({std::make_tuple(id, value, "")});
        }
    }
    for (auto const &[id, value]: tableB) {
        if (tableA.find(id) == tableA.end())  {
            out.push_back({std::make_tuple(id, "", value)});
        }
    }
    return out;
}