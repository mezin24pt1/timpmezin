#pragma once
#include <string>
#include <stdexcept>

class cipher_error : public std::runtime_error {
public:
    explicit cipher_error(const std::string& message) : std::runtime_error(message) {}
};

class TableCipher {
private:
    int columns;
public:
    TableCipher(int key);
    std::wstring encrypt(const std::wstring& plain_text);
    std::wstring decrypt(const std::wstring& cipher_text);
};
