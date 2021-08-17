#include "SaveFile.h"

#include <fstream>
#include <iostream>
//====================
//Erros Check

bool SaveFile::IsPropertyExists(const std::string& Property) {
    if (_Map.find(Property) == _Map.end()) {
        std::cerr << "The given key does not exist! Key: " << Property << std::endl;
        return false;
    }
    return true;
}

bool SaveFile::IsExeptable(char Char)
{
    return (isalnum(Char) != 0 || Char == ':' || Char == '-' || Char == '_' || Char == ' ' || Char == '.');
}

bool SaveFile::IsWordCorrect(const std::string& Word) {
    for (char CharValue : Word) {
        if (!IsExeptable(CharValue)) {
            std::cerr << "Error name! Uncorect char is: <" << CharValue << ">. Full string: <" << Word << ">" << std::endl;
            return false;
        }
    }
    return true;
}


//=================
// Working with Properties


bool SaveFile::DeleteProperty(std::string Property) {
    if (!SaveFile::IsPropertyExists(Property)) {
        return false;
    }
    _Map.erase(Property);
    return true;
}
bool SaveFile::AddProperty(const std::string& Property)
{
    if (!SaveFile::IsWordCorrect(Property)) {
        return false;
    }

    _Map[Property] = std::string("");
    
    return true;
}

bool SaveFile::SetProperty(const std::string& Property, const std::string& Value)
{
    if (!SaveFile::IsPropertyExists(Property)) {
        return false;
    }
    _Map[Property] = Value;
    return true;
}

bool SaveFile::MakeSave(const std::string& FilePath) 
{
    std::ofstream fout(FilePath);
    for (auto const& info : _Map) {
        fout << '\'' << info.first << "':'" << info.second << "'\n";
    }
    fout.close();
    return true;
}
// -> bool

std::string SaveFile::Word(const std::string& string, size_t *position)
{
    if (string[*position] == '\'') {
        (*position)++;
    } else {std::cout << "Error in file format. Missing leading <'> in " << string << " at position " << *position << ", string[*position] = <" << string[*position] << ">" <<  std::endl; return "";}

    size_t indexFirst = *position;


    while (SaveFile::IsExeptable(string[*position]))  {
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
void SaveFile::PrintAllProperties() {
    for (const auto& property: _Map) {
        std::cout << property.first << std::endl;
    }
}
bool SaveFile::ReadSave(const std::string& FilePath)
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
        //std::cout << FilePath << " " << Propetry << std::endl;
        std::string Value = Word(string, &indexSeparator);

        if (Value == "") return false;
        SaveFile::SetProperty(Propetry, Value);


    }
    return true;
}

std::string SaveFile::ReadProperty(const std::string& Property)
{
    if (!SaveFile::IsPropertyExists(Property)) {
        return "";
    }
    return _Map[Property];
}
