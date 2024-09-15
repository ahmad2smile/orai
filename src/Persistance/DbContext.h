//
// Created by ahmad on 8/24/24.
//

#ifndef ORAI_DBCONTEXT_H
#define ORAI_DBCONTEXT_H

#include <sqlite3.h>
#include <string>
#include <vector>

class DbContext {
public:
    DbContext();
    ~DbContext();

    void initTables() const;

    void addSuggestion(const std::wstring& value) const;
    void addSuggestion(const std::string& value) const;
    [[nodiscard]] std::vector<std::wstring> getSuggestions(const std::wstring& search) const;
    [[nodiscard]] std::vector<std::wstring> getSuggestions(const std::string& search) const;

private:
    sqlite3* _db{};
    const std::string _suggestionTable = "suggestions";
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>* _wideConverter;

    void commandExecute(const char* query) const;
    std::vector<std::vector<std::optional<std::string>>> queryExecute(const char* query) const;
};


#endif //ORAI_DBCONTEXT_H
