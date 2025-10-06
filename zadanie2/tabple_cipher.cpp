#include "table_cipher.h"
#include <vector>
#include <stdexcept>
#include <string>

TableCipher::TableCipher(int key)
{
    if (key <= 0) {
        throw std::invalid_argument("Ключ должен быть положительным числом");
    }
    columns = key;
}

std::wstring TableCipher::encrypt(const std::wstring& plain_text)
{
    if (plain_text.empty()) {
        throw std::invalid_argument("Текст не может быть пустым");
    }

    int text_length = static_cast<int>(plain_text.length());
    int rows = (text_length + columns - 1) / columns; // ceil
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(columns, L' '));
    int index = 0;

  
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            if (index < text_length) {
                table[row][col] = plain_text[index++];
            } else {
                table[row][col] = L'Я'; 
            }
        }
    }

    std::wstring result;
    for (int col = columns - 1; col >= 0; --col) {
        for (int row = 0; row < rows; ++row) {
            result += table[row][col];
        }
    }
    return result;
}

std::wstring TableCipher::decrypt(const std::wstring& cipher_text)
{
    if (cipher_text.empty()) {
        throw std::invalid_argument("Текст не может быть пустым");
    }

    int total_chars = static_cast<int>(cipher_text.length());
    if (total_chars % columns != 0) {
        throw std::invalid_argument("Длина зашифрованного текста не кратна числу столбцов");
    }

    int rows = total_chars / columns;
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(columns, L' '));
    int index = 0;

 
    for (int col = columns - 1; col >= 0; --col) {
        for (int row = 0; row < rows; ++row) {
            wchar_t c = cipher_text[index++];
       
            if (!((c >= L'А' && c <= L'Я') || c == L'Ё')) {
                throw std::invalid_argument("Шифротекст содержит недопустимые символы");
            }
            table[row][col] = c;
        }
    }

   
    std::wstring result;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            result += table[row][col];
        }
    }

  
    while (!result.empty() && result.back() == L'Я') {
        result.pop_back();
    }

    return result;
}
