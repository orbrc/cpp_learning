#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// enumeration token types
enum class TokenType {
    Number,
    Operator,
    LeftBracket,
    RightBracket
};

// string value = "1234" or "*" or "+" etc, TokenType::Number and etc 
struct Token {
    std::string value;
    TokenType type;

    Token(std::string value, TokenType type):
    value(value),
    type(type){}
};
unsigned int getOperatorWeight(char op); 

std::unordered_map<std::string, TokenType> acceptedValues();

std::vector<Token> tokenize(std::string expression);
std::vector<Token> shuntingYard(std::vector<Token> tokens);

double result(std::vector<Token> shuntingYardVec);

int main() {
    std::string expression;

    std::cout << "Welcome to c++ calculator!" << std::endl;
    std::cout << "Operations: [+], [-], [*], [/], [Brackets]" << std::endl;

    std::cout << "Expression: ";
    std::getline(std::cin, expression);

    std::cout << expression << std::endl;

    try {
        std::vector<Token> tokens = tokenize(expression);
        std::vector<Token> shuntingYardVec = shuntingYard(tokens);

        std::cout << "Result: " << result(shuntingYardVec) << std::endl;
        
        return 0;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}

std::vector<Token> shuntingYard(std::vector<Token> tokens) {
    
    std::vector<Token> result;
    std::vector<Token> stack;
//  +- - 1; */ - 2; () - 0;
    for (Token t: tokens) {

        // (2 + 2) / 2
        // ( +
        // 22
        switch (t.type) {
            case TokenType::Number:
                result.push_back(t);
                break;

            case TokenType::Operator:
                while (!stack.empty()
                    && getOperatorWeight(stack.back().value[0]) >= getOperatorWeight(t.value[0])) {
                
                    result.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(t);
                break;
                
            case TokenType::LeftBracket:
                stack.push_back(t);
                break;

            case TokenType::RightBracket:
                while (stack.back().type != TokenType::LeftBracket) {
                    result.push_back(stack.back());
                    stack.pop_back();
                }
                stack.pop_back(); // pop left bracket
                break;
        }
    }

    while (!stack.empty()) {
        result.push_back(stack.back());
        stack.pop_back();
    }

    return result;
}

unsigned int getOperatorWeight(char op) {
    if (op == '+' || op == '-') return 1;
    else if (op == '/' || op == '*') return 2;

    return 0;
}

std::vector<Token> tokenize(std::string expression) {
    
    if (expression.empty()) throw std::runtime_error("Expression is empty!");
    
    const std::string operations = "+-*/";
    std::vector<Token> tokens;

    int i = 0;
    int current = 0;
    bool isNumber = false;
    
    while (i < std::size(expression)) {
        char c = expression[i];
        
        if (std::isspace(c)) { i++; continue; }
        
        if (std::isdigit(c)) {
            current = current * 10 + (c - '0');
            i++;

            if (i == expression.size() || !(std::isdigit(expression[i]))) {
                tokens.push_back(Token(std::to_string(current), TokenType::Number));
                current = 0;
            }
            continue;
        }

        if (operations.find(expression[i]) != std::string::npos) {
            
            if (current != 0) {
                tokens.push_back(Token(std::to_string(current), TokenType::Number));
                current = 0;
            }
            
            tokens.push_back(Token(std::string(1, c), TokenType::Operator));
            i++;
            continue;
        }

        if (c == '(') {
            tokens.push_back(Token(std::string(1, c), TokenType::LeftBracket));
            i++;
            continue;
        }
        if (c == ')') {
            tokens.push_back(Token(std::string(1, c), TokenType::RightBracket));
            i++;
            continue;
        }
        i++;
    }

    return tokens;
}

double result(std::vector<Token> shuntingYardVec) {

    if (shuntingYardVec.empty()) throw std::runtime_error("Invalide expression! Empty shunting yard result!");

    std::stack<double> result;

    for (int i = 0; i < std::size(shuntingYardVec); i++) {

        if (shuntingYardVec[i].type == TokenType::Number) {
            result.push(std::stoi(shuntingYardVec[i].value));
            continue;
        }

        if (shuntingYardVec[i].type == TokenType::Operator) {
            if (result.size() < 1) {
                throw std::runtime_error("Invalide expression!");
                break;
            }

            double right = result.top();
            result.pop();
            
            double left = result.top();
            result.pop();
            
            if (shuntingYardVec[i].value == "+") {
                result.push(left + right);
            } else if (shuntingYardVec[i].value == "-") {
                result.push(left - right);
            } else if (shuntingYardVec[i].value == "/") {
                result.push(left / right);
            } else if (shuntingYardVec[i].value == "*") {
                result.push(left * right);
            }
        }
    }

    if (result.size() != 1 or result.empty()) throw std::runtime_error("Invalide expression!");
    return result.top();
}