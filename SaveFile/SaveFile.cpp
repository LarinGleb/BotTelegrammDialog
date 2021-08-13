#include "SaveFile.h"
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <string>

bool SaveFile::AddProperty(std::string Property)
{
    for (char CharValue : Property) {
        if (isalnum(CharValue) == 0) {
            std::cerr << "Error name! Uncorect char is: <" << CharValue << ">. Full string: <" << Property << ">" << std::endl;
            return false;
        }
    }
    _Map.insert(std::pair<std::string, std::string>(Property, ""));
    return true;
}

bool SaveFile::SetProperty(std::string Property, std::string Value)
{
    if (_Map.find(Property) == _Map.end()) {
        std::cerr << "The given key does not exist! Key: " << Property << std::endl;
        return false;
    }
    _Map[Property] = Value;
    return true;
}

bool SaveFile::MakeSave(std::string FilePath)
{
    std::ofstream fout(FilePath);
    if (fout.fail()) {
        std::cerr << "Cant opent file!" << '\n';
        return false;
    }
    for (auto const& info : _Map) {
        fout << '\'' << info.first << "':'" << info.second << "'\n";
    }
    fout.close();
    return true;
}
// -> bool

bool SaveFile::IsExeptable(char Char)
{
    return (isalnum(Char) != 0 || Char == ':' || Char == '-' || Char == '_');
}
std::string SaveFile::Word(std::string string, size_t *position)
{
    if (string[*position] == '\'') {
        (*position)++;
    } else {std::cout << "Error in file format. Missing leading <'> in " << string << " at position " << *position << ", string[*position] = <" << string[*position] << ">" <<  std::endl; return "";}

    size_t indexFirst = *position;


    while (IsExeptable(string[*position])) {
        (*position)++;
    }

    if (string[*position] == '\'') {
        (*position)++;
    } else if (string[*position] == ':') {
        std::cout << "Error in file format. Missing terminating <'> in " << string << std::endl; return "";
    } else {
        std::cout << "Error in file format. Illegal symbol in word " << string << std::endl; return "";
    }
    
    std::string word = string.substr(indexFirst, *position - indexFirst - 1);
    
    return word;
}

bool SaveFile::ReadSave(std::string FilePath)
{
    std::string string;

    std::ifstream file(FilePath);

    if (file.fail()) {
        std::cerr << "Cant opent file!" << '\n';
        return false;
    }

    while (std::getline(file, string)) {
        size_t indexSeparator = 0;
        std::string Propetry = Word(string, &indexSeparator);

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
        std::string Value = Word(string, &indexSeparator);

        if (Value == "") return false;
        SaveFile::SetProperty(Propetry, Value);


    }
    return true;
}

std::string SaveFile::ReadProperty(std::string Property)
{
    if (_Map.find(Property) == _Map.end()) {
        std::cerr << "The given key does not exist! Key: " << Property << std::endl;
        return "";
    }
    return _Map[Property];
}
