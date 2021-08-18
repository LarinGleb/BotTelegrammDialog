#include "SaveFile.h"
#include <locale>
#include <cctype>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <wctype.h>

//====================
//Erros Check

std::wstring SaveFile::ConvertToWstring(const std::string string, const char * locate) {
    setlocale(LC_CTYPE, locate);
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
    std::wstring ws = converter.from_bytes(string);
    return ws;

}
std::string SaveFile::ConvertTostring(const std::wstring string, const char * locate) {
    setlocale(LC_CTYPE, locate);
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.to_bytes(string);

}

bool SaveFile::IsPropertyExists(const std::wstring& Property, const char * locate) {
    setlocale(LC_CTYPE, locate);
    if (_Map.find(Property) == _Map.end()) {
        std::cerr << "The given key does not exist! Key: " << ConvertTostring(Property, locate) << std::endl;
        return false;
    }
    return true;
}
// "ru_RU.UTF-8"

bool SaveFile::IsAcceptable(wchar_t wchar, const char * locate)
{
    setlocale(LC_CTYPE, locate);
    return (iswalnum(wchar) != 0 && wchar == L':' && wchar == L'-' && wchar == L'_' && wchar == L'.' && wchar == L' ' && wchar == L'!' && wchar == L'?');
    
}


bool SaveFile::IsWordCorrect(const std::wstring Word, const char * locate) {


    setlocale(LC_CTYPE, locate);

    for (const auto& wchar : Word) {
        if (!IsAcceptable(wchar, locate)) {
            std::cerr << "Error name! Uncorect char is: <" << (char)wchar << ">. Full string: <" << ConvertTostring(Word, locate) << ">" << std::endl;
            return false;
        }
    }
    return true;
}


//=================
// Working with Properties


bool SaveFile::DeleteProperty(std::string Property, const char * locale) {
    setlocale(LC_CTYPE, locale);
    if (!SaveFile::IsPropertyExists(ConvertToWstring(Property, locale), locale)) {
        return false;
    }
    _Map.erase(ConvertToWstring(Property, locale));
    return true;
}
bool SaveFile::AddProperty(const std::string& Property, const char * locale)
{
    setlocale(LC_CTYPE, locale);
    if (!SaveFile::IsWordCorrect(ConvertToWstring(Property, locale), locale)) {
        return false;
    }

    _Map[ConvertToWstring(Property, locale)] = std::wstring(L"");
    
    return true;
}

bool SaveFile::SetProperty(const std::string& Property,const std::string& Value, const char * locate_second, const char * locate_first)
{
    if (!SaveFile::IsPropertyExists(ConvertToWstring(Property, locate_first), locate_first)) {
        return false;
    }
    _Map[ConvertToWstring(Property, locate_first)] = ConvertToWstring(Value, locate_second);
    return true;
}

bool SaveFile::MakeSave(const std::string& FilePath, const char * locate_first, const char * locate_second) 
{
    
    std::ofstream fout(FilePath);
    for (auto const& info : _Map) {
        fout << '\'' << ConvertTostring(info.first, locate_first) << "':'" << ConvertTostring(info.second, locate_second) << "'\n";
    }
    fout.close();
    return true;
}
// -> bool

std::wstring SaveFile::Word(const std::wstring& string, size_t *position, const char * locate)
{
    setlocale(LC_CTYPE, locate);

    if (string[*position] == L'\'') {
        (*position)++;
    } else {
        std::cout << "Error in file format. Missing leading <'> in " << ConvertTostring(string, locate) << " at position " << *position << ", string[*position] = <" << string[*position] << ">" <<  std::endl; return L"";
    }

    size_t indexFirst = *position;


    while (SaveFile::IsAcceptable(string[*position], locate))  {
        (*position)++;
    }

    if (string[*position] == L'\'') {
        (*position)++;
    } else if (string[*position] == L':') {
        std::cout << "Error in file format. Missing terminating <'> in " << ConvertTostring(string, locate) << std::endl; return L"";
    } else {
        std::cout << "Error in file format. Illegal symbol in word " << ConvertTostring(string, locate) <<", Symbol: <" << (char)string[*position] << "> at position " << *position << std::endl; return L"";
    }

    return string.substr(indexFirst, *position - indexFirst - 1);
}

bool SaveFile::ReadSave(const std::string& FilePath, const char * locate_second, const char * locate_first)
{
    std::string string;

    std::ifstream file(FilePath);

    if (file.fail()) {
        std::cerr << "Cant opent file" << FilePath << '\n';
        return false;
    }

    int index = 0;
    while (std::getline(file, string)) {
        //std::cout << "Line: " << index;
        index += 1;
        size_t indexSeparator = 0;
        std::string Propetry = ConvertTostring(Word(ConvertToWstring(string, locate_first), &indexSeparator, locate_first), locate_first);

        if (Propetry == "")
            return false;

        if (string[indexSeparator] == ':') {
            indexSeparator++;
        } else {
            std::cerr << "Error separator! indexSeparator = " << indexSeparator << ", string[indexSeparator + 1] = <" << string[indexSeparator + 1] << ">" << std::endl;
            std::cerr << "Full line: <" << string << ">" << std::endl; 
            return false;
        }

        SaveFile::AddProperty(Propetry);
        //std::cout << FilePath << " " << Propetry << std::endl;
        std::string Value = ConvertTostring(Word(ConvertToWstring(string, locate_second), &indexSeparator, locate_second), locate_second);

        if (Value == "") return false;
        SaveFile::SetProperty(Propetry, Value, locate_second);


    }
    return true;
}

std::string SaveFile::ReadProperty(const std::string& Property, const char * locate_second, const char * locate_first)
{
    if (!SaveFile::IsPropertyExists(ConvertToWstring(Property, locate_first), locate_first)) {
        return "";
    }
    return ConvertTostring(_Map[ConvertToWstring(Property, locate_first)], locate_second);
}
