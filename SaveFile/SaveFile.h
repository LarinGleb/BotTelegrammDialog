
#ifndef SAVEFILE_H
#define SAVEFILE_H
#include <map>


enum statesParce {PROPERTY, PROPERTY_VALUE};

class SaveFile {

    public:
        typedef std::map<std::string, std::string> StringMap;
        void AddProperty(std::string Property);
        void SaveProperty(std::string Property, std::string Value);
        void ReadSave(std::string FilePath);
        void MakeSave(std::string FilePath);
        std::string ReadProperty(std::string Property);
    private:
        StringMap _Map = StringMap();

};
#endif

