#ifndef TABLE_HPP
#define TABLE_HPP

#include <mutex>
#include <functional>
#include <unordered_map>

class DataBase {
public:
    using RowType = std::pair<size_t, std::string>;
    using Table = std::map<size_t, std::string>;

    bool insert(RowType row) {
        const auto [it_hinata, success] = _table.insert(row);
        return success;
    }

    void trancate() {
        _table.clear();
    }

    const Table& data() const {
        return _table;
    }

private:
    Table _table{};
    
};

#endif