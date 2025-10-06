#pragma once
#include <string>

class route_error : public std::invalid_argument {
public:
    explicit route_error(const std::string& what) : std::invalid_argument(what) {}
};

class RouteCipher {
private:
    int cols;

public:
    explicit RouteCipher(int columns);
    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& cipher);
};
