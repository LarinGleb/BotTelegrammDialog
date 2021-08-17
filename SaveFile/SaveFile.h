#ifndef __SAVEFILE_H__
#define __SAVEFILE_H__

#include <map>
#include <ctype.h>
#include <string>


class SaveFile {

    public:
        SaveFile() = default;
        ~SaveFile() = default;

        typedef std::map<std::string, std::string> StringMap;

        // Добавляет в локальный словарь поле. Если не получилось создать - вернёт false, в противном случае true
        bool AddProperty(const std::string& Property);

        // Устанавливает в данный property значение value. Если не получилось добавить (отсуствие поля) вернёт false, в противном случае true
        bool SetProperty(const std::string& Property, const std::string& Value);

        //Читает сохрвнённый словарь в FilePath и записывает его в локальную map. В случае ошибки вернёт false, в противном случае true
        bool ReadSave(const std::string& FilePath);

        //Записывает в FilePath все поля и значение текущих данных. Формат: 'property':'value'. В случае ошибки вернёт false,  в противном случае true
        bool MakeSave(const std::string& FilePath) ;

        //Вернёт значение по данному Property. Если достать не получилось, то вернёт пустую строку
        std::string ReadProperty(const std::string& Property)  ;

        StringMap GetMap() { return _Map;}
        bool DeleteProperty(std::string Key);

        void PrintAllProperties();
    
    private:

        std::string Word(const std::string& string, size_t * positon);
        bool IsExeptable(char Char);
        bool IsPropertyExists(const std::string& Property);
        bool IsWordCorrect(const std::string& Word);
        
        // StringMap _Map{};
        std::map<std::string, std::string> _Map{};

};
#endif

