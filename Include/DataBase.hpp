#ifndef TABLE_HPP
#define TABLE_HPP

#include <mutex>
#include <unordered_map>

class DataBase {
public:
    using RowType = std::pair<size_t, std::string>;
    using Table = std::unordered_map<size_t, std::string>;

    // const TypeRow& getData() const {
    //     std::lock_guard(mutex);
    //     return table;
    // }

    // TypeRow& getData() {
    //     mutex.lock();
    //     return table;
    // }

    void unlock() {
        // mutex.unlock();
    }

    bool insert(RowType row) {
        std::lock_guard lock(_mutex);
        const auto [it_hinata, success] = _table.insert(row);
        return success;
    }

private:
    Table _table{};
    std::mutex _mutex{};
};

#endif