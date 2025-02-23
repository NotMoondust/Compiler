//this was easier to make a second time. many backups later and I can say it is just fine. it can only bring out an exit code but its a start. but I will add a TODO anyway.
//TODO add a parsing tree/finish debugging a parsing tree if I ever get it started.
#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

#include "./tokenization.hpp"

std::string tokens_to_asm(const std::vector<Token>& tokens) {
	std::stringstream output;
	output << "global _start\n_start:\n";
	for (int i = 0; i < tokens.size(); i++) 
	{
		const Token& token = tokens.at(i);
		if (token.type == TokenType::_exit) 
		{
			if (i+ 1 < tokens.size() && tokens.at(i + 1).type == TokenType::int_lit) 
			{
				if (i + 2 < tokens.size() && tokens.at(i + 2).type == TokenType::semi) 
				{
					output << "   mov rax, 60\n";
					output << "   mov rdi, " << tokens.at(i + 1).value.value() << "\n";
					output << "   syscall";
				}
			}
		}
	}
	return output.str();
} 	

int main(int argc, char* argv[]) {
	if (argc != 2){
		std::cerr << "The Emperor is displeased with your failures, the correct usage is below" << std::endl;
		std::cerr << "40k <input.40k>" << std::endl;
		return EXIT_FAILURE;
		}
	std::string contents;
	{
		std::fstream input(argv[1], std::ios::in);
		std::stringstream contents_stream;
		contents_stream << input.rdbuf();
		contents = contents_stream.str();
	}
	Tokenizer tokenizer (std::move(contents));
	std::vector<Tokens> tokens = tokenizer.tokenize();
	{
		std::fstream file("out.asm", std::ios::out);
		file << tokens_to_asm(tokens);
	}

	system("nasm -felf64 out.asm");
	system("ld -o out out.o");
	return EXIT_SUCCESS;
}
