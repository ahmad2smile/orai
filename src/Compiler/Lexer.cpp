//
// Created by ahmad on 8/27/23.
//

#include <algorithm>
#include "Lexer.h"

Token::Token(Keyword keyword, const std::vector<std::string> &values) {}

// TODO: Inefficient structure for lookup with word for Keyword
std::map<Keyword, std::vector<std::string>> Lexer::TokenMap = {
        {Keyword::_and, {"and", "&&"}},
        {Keyword::_get, {"get", "fetch", "show"}}
};

std::vector<Token> Lexer::GetTokens(const char *raw) {
    std::vector<Token> tokens;

    for (int i = 0; raw[i] != '\0'; ++i) {
        auto c = raw[i];

        if (std::isalpha(c)) {
            auto word = GetWord(raw, i);


            for (const auto &pair: TokenMap) {
                auto vec = pair.second;

                if (!(std::find(vec.begin(), vec.end(), word) != vec.end())) {
                    continue;
                }

                tokens.push_back(Token{pair.first, {}});
                break;
            }
        }
    }

    return tokens;
}

std::string Lexer::GetWord(const char *raw, int wordStartIndex) {
    auto index = wordStartIndex;
    std::string word;

    while (true) {
        auto c = raw[index];

        if (c == ' ') {
            break;
        }

        word.push_back(c);
        index++;
    }

    return word;
}

std::string Lexer::GetToken(std::string word) {


    return std::string();
}
