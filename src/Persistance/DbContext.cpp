//
// Created by ahmad on 8/24/24.
//

#include <stdexcept>
#include <algorithm>
#include <optional>
#include <locale>
#include <codecvt>
#include "DbContext.h"


DbContext::DbContext() : _wideConverter(new std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>()) {
    if (sqlite3_open("orai_db", &_db)) {
        throw std::runtime_error("Can't open database: " + std::string(sqlite3_errmsg(_db)));
    }
}

DbContext::~DbContext() {
    if (_db) {
        sqlite3_close(_db);
    }

    delete _wideConverter;
}

void DbContext::initTables() const {
    const auto suggestionsQuery =
            "CREATE TABLE IF NOT EXISTS " + _suggestionTable +
            " (id INTEGER PRIMARY KEY, value TEXT, timestamp DATETIME DEFAULT CURRENT_TIMESTAMP);";

    commandExecute(suggestionsQuery.c_str());
}

void DbContext::commandExecute(const char* query) const {
    char* errMsg = nullptr;

    if (sqlite3_exec(_db, query, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        const std::string error_message = errMsg ? errMsg : "Unknown error during Sqlite queryExecute execution";

        sqlite3_free(errMsg);

        throw std::runtime_error("SQL error: " + error_message);
    }
}

std::vector<std::vector<std::optional<std::string>>> DbContext::queryExecute(const char* query) const {
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(_db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(_db)));
    }

    std::vector<std::vector<std::optional<std::string>>> results;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const int cols = sqlite3_column_count(stmt);
        std::vector<std::optional<std::string>> row;

        for (int i = 0; i < cols; ++i) {
            auto text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));

            row.push_back(text ? std::make_optional<std::string>(text) : std::nullopt);
        }

        results.push_back(std::move(row));
    }

    sqlite3_finalize(stmt);

    return results;
}

void DbContext::addSuggestion(const std::wstring& value) const {
    addSuggestion(_wideConverter->to_bytes(value));
}

void DbContext::addSuggestion(const std::string& value) const {
    const std::string query = "INSERT INTO " + _suggestionTable + " (value) VALUES (\"" + value + "\");";

    commandExecute(query.c_str());
}


std::vector<std::wstring> DbContext::getSuggestions(const std::wstring& search) const {
    return getSuggestions(_wideConverter->to_bytes(search));
}

std::vector<std::wstring> DbContext::getSuggestions(const std::string& search) const {
    auto query = "SELECT value FROM " + _suggestionTable;

    if (!search.empty()) {
       query += " WHERE value LIKE '%" + search + "%'"; 
    }

    query += ";";

    std::vector<std::wstring> result;

    for (const auto& item: queryExecute(query.c_str())) {
        if (auto col = item.at(0); col && col.has_value()) {
            result.emplace_back(_wideConverter->from_bytes(col.value()));
        }
    }

    return result;
}
