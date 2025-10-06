#include <iostream>
#include <locale>
#include <codecvt>
#include "modAlphaCipher.h"
using namespace std;
bool isRussianLetter(wchar_t c) {
    return (c >= L'А' && c <= L'Я') || c == L'Ё' ||
           (c >= L'а' && c <= L'я') || c == L'ё';
}

wchar_t toUpperRussian(wchar_t c) {
    if (c >= L'а' && c <= L'я') {
        return c - (L'а' - L'А');
    }
    if (c == L'ё') return L'Ё';
    return c;
}

wstring cleanRussianText(const wstring& s) {
    wstring result;
    for (wchar_t c : s) {
        if (isRussianLetter(c)) {
            result += toUpperRussian(c);
        }
    }
    return result;
}

wstring stringToWstring(const string& str) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

string wstringToString(const wstring& wstr) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    string key_input;
    cout << "Шифр готов. Введите ключ: ";
    getline(cin, key_input);
    wstring key = cleanRussianText(stringToWstring(key_input));

    if (key.empty()) {
        cerr << "Ошибка: ключ не содержит русских букв." << endl;
        return 1;
    }
    cout << "Ключ загружен: " << wstringToString(key) << endl;

    modAlphaCipher cipher(key);

    unsigned op;
    do {
        cout << "Шифр готов. Выберите операцию (0-выход, 1-шифрование, 2-расшифрование): ";
        cin >> op;
        cin.ignore();

        if (op > 2) {
            cout << "Неверная операция" << endl;
        } else if (op > 0) {
            string text_input;
            cout << "Введите текст: ";
            getline(cin, text_input);
            wstring text = cleanRussianText(stringToWstring(text_input));

            if (text.empty()) {
                cout << "Операция отменена: текст не содержит русских букв." << endl;
                continue;
            }

            if (op == 1) {
                wstring encrypted = cipher.encrypt(text);
                cout << "Зашифрованный текст: " << wstringToString(encrypted) << endl;
            } else {
                wstring decrypted = cipher.decrypt(text);
                cout << "Расшифрованный текст: " << wstringToString(decrypted) << endl;
            }
        }
    } while (op != 0);

    return 0;
}
