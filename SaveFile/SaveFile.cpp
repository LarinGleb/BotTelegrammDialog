#include "SaveFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>

#define CHARACTERS "1234567890qwertyuioplkjhgfdesazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM"

enum statesParce {PROPERTY, PROPERTY_VALUE};

// -> bool
void SaveFile::AddProperty(std::string Property) {
    for (char CharValue: Property) {
        if (isalnum(CharValue) == 0) {
            std::cerr << "Error name! Uncorect char is: " << CharValue << std::endl;
            return;
        }
    }
    _Map.insert(std::pair<std::string, std::string>(Property, ""));
}

// -> set
// -> bool
void SaveFile::SaveProperty(std::string Property, std::string Value) {
    if (_Map.find(Property) == _Map.end()) {
        std::cerr << "The given key does not exist!" << std::endl;
        return;
    }
    _Map[Property] = Value;
}

// -> bool
void SaveFile::MakeSave(std::string FilePath) {
    std::ofstream fout(FilePath);
    if (fout.fail()) {
        std::cerr << "Cant opent file!";
        return;
    }
    for (auto const& info : _Map) {
        fout << '\'' << info.first << "':'" << info.second << "'\n";
    }
    fout.close();
}

bool IsCharCorrect(char Char) {
    for (char CharValue : CHARACTERS) {
        if (Char != CharValue) return false;
    }
    return true;
}

// -> bool
void SaveFile::ReadSave(std::string FilePath) {
    std::string string;

    std::ifstream file(FilePath);
    if (file.fail()) {
        std::cerr << "Cant opent file!";
        return;
    }

    while (std::getline(file, string)) {
        int indexSeparator = 0;
        statesParce state(PROPERTY);
        std::string Property;
        std::string PropertyValue;
        for (int i = 0; i < string.length(); i ++) {
            if (string[i] == ':') {
                int indexFirst =  string.find("'", indexSeparator);
                int indexSecond = string.find("'", indexFirst);
                if (indexFirst == std::string::npos || indexSecond == std::string::npos) {
                    std::cerr << "Error format file!" << std::endl;
                }
                else {
                    std::string Value = string.substr(indexFirst + 1, indexSecond);
                    for (char CharInValue: Value) {
                        if (isalnum(CharInValue) == 0) {
                            std::cerr << "Error name! Uncorect char is: " << CharInValue << std::endl;
                            return;
                        }
                    }
                    switch (state) {
                        
                        case PROPERTY: Property = Value; state = PROPERTY_VALUE; break;
                        case PROPERTY_VALUE: PropertyValue = Value; break;
                    }               
                }
            }
        }
        SaveFile::AddProperty(Property);
        SaveFile::SaveProperty(Property, PropertyValue);        
    }
}


std::string SaveFile::ReadProperty(std::string Property) {
    if (_Map.find(Property) == _Map.end()) {
        std::cerr << "The given key does not exist!";
        return "";
    }
    return _Map[Property];
}

int main() {
    SaveFile Save;

    Save.AddProperty("something");
    Save.AddProperty("somethinig");
    Save.SaveProperty("something", "5");
    Save.SaveProperty("somethinig", "6");
    Save.MakeSave("map.txt");

    Save.ReadSave("map.txt");

    std::cout << Save.ReadProperty("something") << std::endl;
    std::cout << Save.ReadProperty("somethinig") << std::endl;
    std::cout << Save.ReadProperty("somdsdsdsething") << std::endl;
}