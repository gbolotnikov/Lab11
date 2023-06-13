#ifndef SESSION_MANAGER_HPP
#define SESSION_MANAGER_HPP

#include <map>
#include <string>
#include <functional>
#include <string_view>
#include "DataBaseController.hpp"

class SessionController {  
private:
    using Token = std::vector<std::string>;
    using FnCmd = std::function<void(SessionController*, const Token&)>;
    using FnCmdMap = std::map<std::string, FnCmd>;      
public:
    std::string process(std::string_view str);



private:
    enum Cmd { 
        Commnad = 0x0, 
        Table, 
        Id,
        Value
    };

    std::string insert(const Token& token) const;
    std::string truncate(const Token& token) const;
    std::string insertion(const Token& token) const;
    std::string symmetricDifference(const Token& token) const;

    
    mutable DataBaseController _dataBase;
    static constexpr auto Delimetr = ' ';
    Token parcer(std::string_view str);
    const FnCmdMap _cmdMap {
        {std::make_pair("INSERT", &SessionController::insert)}
    };
};

#endif