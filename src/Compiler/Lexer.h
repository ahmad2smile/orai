//
// Created by ahmad on 8/27/23.
//

#ifndef ORAI_LEXER_H
#define ORAI_LEXER_H

#include <vector>
#include <string>
#include <map>

enum class Keyword {
    _and,
    _get
};

struct Token {
    explicit Token(Keyword keyword, const std::vector<std::string> &values);

    Keyword keyword;
    
    std::vector<std::string> values;
};

class Lexer {

public:
    static std::vector<Token> GetTokens(const char *raw);

private:
    static std::map<Keyword, std::vector<std::string>> TokenMap;

    static std::string GetWord(const char *raw, int wordStartIndex);

    static std::string GetToken(std::string word);
};


#endif //ORAI_LEXER_H
