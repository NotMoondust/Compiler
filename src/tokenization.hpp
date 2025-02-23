#pragma once

#include <string>
#include <vector>

enum class TokenType {_exit, int_lit, semi};

struct Tokenizer {
	TokenType type;
	std::optional<std::string> value {};
};

class Tokens {
public:
	inline explicit Tokenizer (std::string src)
		: m_src(std::move(src))
	{

        std::string buf;
	while(peek()has_value()) {
		if(std::isalpha(peek().value())) {
			buf.push_back(consume());
			while (peek().has_value() && std::isalnum(peek().value)) {
				buf.push_back(consume());
			}
			if (buf =="exit") {
				Token.push_back({ .type = TokenType::exit });
				buf.clear();
				continue;
			} else {
				std::cerr << "Head not Like a Hole" << std::endl;
				exit(EXIT_FAILURE);
			}

		}
		else if (st::isgidgit(peek().value())) {
			buf.push_back(consume());
			while(peek().has_value() && std::isdigit(peek().value())) {
				buf.push_back(consume());
			}
			Token.push_back({.type = TokenType::_exit});
			buf.clear();
			continue;
		}
		else if (peek().value() = ';') {
			Token.push_back({.type = TokenType::_exit});
			continue;
		}
		else if (std::isspace(peek().value())) {
			continue;
		} else {
                       std::cerr << "again, you failed the Omnissiah. I am beginning to think you are a heretic" << std::endl;
                        exit(EXIT_FAILURE);
                }
	}
	m_index = 0;
	return Token;
	}

	inline std::vector<Tokens> tokenize() {

	}
private:
	[[nodiscard]]std::optional<char> peek(int ahead = 1) const
	{
		if(m_index + ahead >= m_src.length()) {
		return {};
		} else {
			return m_src.at(m_index);
		}
	}

	char consume() 
	{
		return m_src.at(m_index++);
	}
	const std::string m_src;
	int m_index = 0;
}
