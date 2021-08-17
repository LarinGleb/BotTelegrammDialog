
#ifndef SAVEFILE_H
#define SAVEFILE_H
#include <map>
#include <string>


class SaveFile {

    public:
        typedef std::map<std::string, std::string> StringMap;

        // Добавляет в локальный словарь поле. Если не получилось создать - вернёт false, в противном случае true
        bool AddProperty(std::string Property);

        // Устанавливает в данный property значение value. Если не получилось добавить (отсуствие поля) вернёт false, в противном случае true
        bool SetProperty(std::string Property, std::string Value);

        //Читает сохрвнённый словарь в FilePath и записывает его в локальную map. В случае ошибки вернёт false, в противном случае true
        bool ReadSave(std::string FilePath);

        //Записывает в FilePath все поля и значение текущих данных. Формат: 'property':'value'. В случае ошибки вернёт false,  в противном случае true
        bool MakeSave(std::string FilePath);

        //Вернёт значение по данному Property. Если достать не получилось, то вернёт пустую строку
        std::string ReadProperty(std::string Property);

        bool DeleteProperty(std::string Key);
        StringMap GetMap() { return _Map;}
    private:

        std::string Word(std::string string, size_t * positon);
        bool IsExeptable(char Char);
        bool IsPropertyExists(std::string Property);
        bool IsWordCorrect(std::string Word);
        
        StringMap _Map = StringMap();

};
#endif

