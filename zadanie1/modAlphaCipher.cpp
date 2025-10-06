#include "modAlphaCipher.h"
#include <vector>
#include <map>
#include <string>

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    for (size_t i = 0; i < numAlpha.size(); ++i) {
        alphaNum[numAlpha[i]] = static_cast<int>(i);
    }
    key = convert(skey);
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s) {
        result.push_back(alphaNum.at(c)); // 
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(open_text);
    size_t alpha_size = numAlpha.size();
    for (size_t i = 0; i < work.size(); ++i) {
        work[i] = (work[i] + key[i % key.size()]) % static_cast<int>(alpha_size);
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(cipher_text);
    size_t alpha_size = numAlpha.size();
    for (size_t i = 0; i < work.size(); ++i) {
        work[i] = (work[i] + static_cast<int>(alpha_size) - key[i % key.size()]) % static_cast<int>(alpha_size);
    }
    return convert(work);
}
