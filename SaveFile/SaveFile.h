#ifndef __SAVEFILE_H__
#define __SAVEFILE_H__

#include <ctype.h>
#include <map>
#include <string>

#define OK 1
#define ERROR_FORMAT 2
#define ERROR_SEPARATOR 3
#define ERROR_FIND 4
#define ERROR_NAME 5
#define ERROR_FILE 6
class SaveFile {

public:
    SaveFile() = default;
    ~SaveFile() = default;

    typedef std::map<std::string, std::string> StringMap;

    // Добавляет в локальный словарь поле. Если не получилось создать - вернёт false, в противном случае true
    int AddProperty(const std::string& Property);

    // Устанавливает в данный property значение value. Если не получилось добавить (отсуствие поля) вернёт false, в противном случае true
    int SetProperty(const std::string& Property, const std::string& Value);

    //Читает сохрвнённый словарь в FilePath и записывает его в локальную map. В случае ошибки вернёт false, в противном случае true
    int ReadSave(const std::string& FilePath);

    //Записывает в FilePath все поля и значение текущих данных. Формат: 'property':'value'. В случае ошибки вернёт false,  в противном случае true
    int MakeSave(const std::string& FilePath);

    //Вернёт значение по данному Property. Если достать не получилось, то вернёт пустую строку
    std::string ReadProperty(const std::string& Property);

    StringMap GetMap() { return _Map; }
    int DeleteProperty(std::string Key);

    void PrintAllProperties();
    bool IsWordCorrect(const std::string Word);

private:
    // std::string ToLowerNoSpaces(const std::string& str);
    bool IsRu(wchar_t Char);
    std::string Word(const std::string& string, size_t* positon);
    bool IsAcceptable(const std::string string, size_t positon);
    int IsPropertyExists(const std::string& Property);

    // StringMap _Map{};
    std::map<std::string, std::string> _Map{};
};
#endif
