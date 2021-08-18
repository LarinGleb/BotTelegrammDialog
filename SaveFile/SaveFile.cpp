#include "SaveFile.h"
#include <algorithm>
#include <cctype>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <wctype.h>

//====================
//Erros Check

int SaveFile::IsPropertyExists(const std::string& Property)
{
    if (_Map.find(Property) == _Map.end()) {
        std::cerr << "The given key does not exist! Key: " << Property << std::endl;
        return ERROR_FIND;
    }
    return OK;
}

bool SaveFile::IsAcceptable(const std::string string, size_t positon)
{
    setlocale(LC_CTYPE, "ru_RU.UTF-8");
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
    std::wstring ws = converter.from_bytes(string);
    const auto wchar = ws[positon];

    bool isalnum = iswalnum(wchar) != 0;

    return !(!isalnum && wchar != L':' && wchar != L'-' && wchar != L',' && wchar != L'_' && wchar != L'.' && wchar != L' ' && wchar != L'!' && wchar != L'?');
}

bool SaveFile::IsWordCorrect(const std::string Word)
{
    setlocale(LC_CTYPE, "ru_RU.UTF-8");
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
    std::wstring ws = converter.from_bytes(Word);

    for (wchar_t wchar: ws) {
        bool isalnum = iswalnum(wchar) != 0;
        if (!isalnum && wchar != L':' && wchar != L'-' && wchar != L',' && wchar != L'_' && wchar != L'.' && wchar != L' ' && wchar != L'!' && wchar != L'?') {
            return false;
        }
    }

    return true;
}

//=================
// Working with Properties

int SaveFile::DeleteProperty(std::string Property)
{
    if (SaveFile::IsPropertyExists(Property) == ERROR_NAME) {
        std::cerr << "The given key does not exist! Key: " << Property << std::endl;
        return ERROR_FIND;
    }
    _Map.erase(Property);
    return OK;
}
int SaveFile::AddProperty(const std::string& Property)
{
    if (!SaveFile::IsWordCorrect(Property)) {
        return ERROR_NAME;
    }

    _Map[Property] = std::string("");

    return OK;
}

int SaveFile::SetProperty(const std::string& Property, const std::string& Value)
{
    if (SaveFile::IsPropertyExists(Property) == ERROR_NAME) {
        return ERROR_FIND;
    }
    _Map[Property] = Value;
    return OK;
}

int SaveFile::MakeSave(const std::string& FilePath)
{
    
    std::ofstream fout(FilePath);
    for (auto const& info : _Map) {
        fout << '\'' << info.first << "':'" << info.second << "'\n";
    }
    fout.close();
    return OK;
}
// -> bool

std::string SaveFile::Word(const std::string& string, size_t* position)
{
    setlocale(LC_CTYPE, "ru_RU.UTF-8");
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
    std::wstring ws = converter.from_bytes(string);
    bool is_char = string[*position] == '\'';
    bool is_wchar = ws[*position] == L'\'';

    if (is_wchar || is_char) {
        (*position)++;
    } else {
        std::cout << "Error in file format. Missing leading <'> in " << string << " at position " << *position << ", string[*position] = <" << string[*position] << ">" << std::endl;
        return "";
    }

    size_t indexFirst = *position;

    while (SaveFile::IsAcceptable(string, *position)) {
        (*position)++;
    }

    is_char = string[*position] == '\'';
    is_wchar = ws[*position] == L'\'';

    if (is_wchar || is_char) {
        (*position)++;
    } else if (string[*position] == ':' || ws[*position] == L':') {
        std::cout << "Error in file format. Missing terminating <'> in " << string << std::endl;
        return "";
    } else {
        std::cout << "Error in file format. Illegal symbol in word " << string << ", Symbol: <" << string[*position] << "> at position " << *position << std::endl;
        return "";
    }

    if (is_char) {
        return string.substr(indexFirst, *position - indexFirst - 1);
    } else {
        const auto kkk = ws.substr(indexFirst, *position - indexFirst - 1);
        return converter.to_bytes(kkk);
    }
}
void SaveFile::PrintAllProperties()
{
    for (const auto& property : _Map) {
        std::cout << property.first << std::endl;
    }
}
int SaveFile::ReadSave(const std::string& FilePath)
{
    std::string string;

    std::ifstream file(FilePath);

    if (file.fail()) {
        std::cerr << "Cant opent file" << FilePath << '\n';
        return ERROR_FILE;
    }

    int index = 0;
    while (std::getline(file, string)) {
        index += 1;
        size_t indexSeparator = 0;
        std::string Propetry = Word(string, &indexSeparator);

        if (Propetry == "")
            return ERROR_NAME;

        setlocale(LC_CTYPE, "ru_RU.UTF-8");
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
        std::wstring ws = converter.from_bytes(string);

        if (string[indexSeparator] == ':' || ws[indexSeparator] == L':') {
            indexSeparator++;
        } else {
            std::cerr << "Error separator! indexSeparator = " << indexSeparator << ", string[indexSeparator + 1] = <" << string[indexSeparator + 1] << ">" << std::endl;
            std::cerr << "Full line: <" << string << ">" << std::endl;
            return ERROR_SEPARATOR;
        }

        std::string Value = Word(string, &indexSeparator);

        if (Value == "") {
            return false;
        }

        SaveFile::AddProperty(Propetry);
        SaveFile::SetProperty(Propetry, Value);
    }
    return true;
}

std::string SaveFile::ReadProperty(const std::string& Property)
{
    if (SaveFile::IsPropertyExists(Property) == ERROR_NAME) {
        return "";
    }
    return _Map[Property];
}
