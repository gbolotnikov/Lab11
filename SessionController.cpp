#include <sstream>
#include <iomanip>
#include "Include/SessionController.hpp"

std::string SessionController::process(std::string_view str) {
    auto token = parcer(str);
    auto command = _cmdMap.find(token[Commnad]);
    if (command != _cmdMap.end()) {
        return command->second(token);
    } else {
        return "Wrong command" + token[Commnad] + "\n";
    }
}

// переведи на строки хрень со string_view
SessionController::Token SessionController::parcer(std::string_view str) {
    size_t endPos = 0;
    size_t startPos = 0;
    Token token;
    while (true) {
        endPos = str.find(Delimetr, startPos); 
        if (endPos == std::string_view::npos) {
            std::string s = std::string(str.substr(startPos));
            token.push_back(std::move(s));
            break;
        } 
        std::string s = std::string(str.substr(startPos, endPos - startPos));
        token.push_back(std::move(s));
        startPos = endPos + 1;
    }
    return token;
}

std::string SessionController::insert(const Token& token) const {
    if (token.size() != 4) {
        return "Wrong arg for \"INSERT\" command\n";
    }
    auto id = std::stoi(token[SessionController::Id]);
    try {
        _dataBase.insert(std::move(token[Table]), id, std::move(token[Value]));
    }
    catch (const DataBaseController::InvalidOperation& err) {
        return "ERR " + std::string(err.what()) + '\n';
    }
    return "OK\n";
}

std::string SessionController::truncate(const Token& token) const {
    try {
        _dataBase.truncate(std::move(token[Table]));

    }
    catch (const DataBaseController::InvalidOperation& err) {
        return "ERR " + std::string(err.what()) + '\n';
    }
    return "OK\n";
}

std::string SessionController::intersection(const Token& token) const {
    try {
        auto result = std::move(_dataBase.insertion());
        return toString(result);
    }
    catch (const DataBaseController::InvalidOperation& err) {
        return "ERR " + std::string(err.what()) + '\n';
    }
    return "OK\n";
}



std::string SessionController::symmetricDifference(const Token& token) const {
    try {
        auto result = std::move(_dataBase.symmetricDifference());
        return toString(result);
    }
    catch (const DataBaseController::InvalidOperation& err) {
        return "ERR " + std::string(err.what()) + '\n';
    }
    return "OK\n";
}

std::string SessionController::toString(DataBaseController::ResultType& result) const {
    std::stringstream out{};
    for (const auto& [id, val1, val2]: result) {
        out << std::to_string(id) << ',';
        out << val1  << ',';
        out << val2  << '\n';
    }
    out << "OK\n";
    return out.str();
}