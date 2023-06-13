#include "Include/SessionController.hpp"

std::string SessionController::process(std::string_view str) {
    auto token = parcer(str);
    auto command = _cmdMap.find(token[Commnad]);
    if (command != _cmdMap.end()) {
       return insert(token);
    } else {
        return "Wrong command" + token[Commnad] + "\n";
    }
}

SessionController::Token SessionController::parcer(std::string_view str) {
    size_t pos = 0;
    Token token;
    while ((pos = str.find(pos + token.size(), Delimetr)) != std::string::npos) {
        std::string s = std::string(str.substr(0, pos));
        token.push_back(std::move(s));
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
    std::string str;
    return str;
}

std::string SessionController::insertion(const Token& token) const {
    std::string str;
    return str;
}

std::string SessionController::symmetricDifference(const Token& token) const {
    std::string str;
    return str;
}