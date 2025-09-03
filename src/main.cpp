#include "parser.hpp"
#include "utils.hpp"

std::string tokenTypeToString(TokenType type) {
    switch(type) {
        case TokenType::VAR: return "VAR";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::END: return "END";
        case TokenType::PLUS: return "PLUS";
        default: return "UNKNOWN";
    }
}

// Fonction pour afficher tous les tokens
void printTokens(const std::vector<Token>& tokens) {
    std::cout << "Contenu des tokens (" << tokens.size() << " tokens):\n";
    std::cout << "--------------------------------\n";
    
    for(size_t i = 0; i < tokens.size(); ++i) {
        const Token& token = tokens[i];
        std::cout << "Token " << i + 1 << ":\n";
        std::cout << "  Type: " << tokenTypeToString(token.type) << "\n";
        std::cout << "  Valeur: '" << token.value << "'\n";
        std::cout << "--------------------------------\n";
    }
}

int main() {
    std::string input = utils::readFileToString("syntaxe.txt");

    try {
        Lexer lexer(input);
        while (auto token = lexer.nextToken()) {
            std::cout << "Token: " << token->type << ", Value: " << token->value << "\n";
            if (token->type == TokenType::END) {
                break;
            }
        }
        Parser parser(lexer);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}