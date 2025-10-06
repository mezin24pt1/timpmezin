#include "routeCipher.h"
#include <vector>
#include <stdexcept>
#include <cmath>

RouteCipher::RouteCipher(int columns) {
    if (columns <= 0)
        throw route_error("Number of columns must be positive");
    cols = columns;
}

std::string RouteCipher::encrypt(const std::string& text) {
    if (text.empty()) return "";

    int len = static_cast<int>(text.length());
    int rows = (len + cols - 1) / cols; // ceil(len / cols)
    std::vector<std::vector<char>> table(rows, std::vector<char>(cols, 0));

    int k = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (k < len) {
                table[i][j] = text[k++];
            }
        }
    }

   
    std::string result;
    for (int j = cols - 1; j >= 0; --j) {
        for (int i = 0; i < rows; ++i) {
            if (table[i][j] != 0) {
                result += table[i][j];
            }
        }
    }
    return result;
}

std::string RouteCipher::decrypt(const std::string& cipher) {
    if (cipher.empty()) return "";

    int len = static_cast<int>(cipher.length());
    int rows = (len + cols - 1) / cols;

    std::vector<std::vector<char>> table(rows, std::vector<char>(cols, 0));

   
    int k = 0;
    for (int j = cols - 1; j >= 0; --j) {
        for (int i = 0; i < rows; ++i) {
            if (k < len) {
                table[i][j] = cipher[k++];
            }
        }
    }

 
    std::string result;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (table[i][j] != 0) {
                result += table[i][j];
            }
        }
    }
    return result;
}
