#ifndef __SAVEFILE_H__
#define __SAVEFILE_H__

#include <map>
#include <ctype.h>
#include <string>
#define ENGLISH "en_US.UTF-8"
#define RUSSION "ru_RU.UTF-8"
#define STANDART ENGLISH


class SaveFile {

    public:
        SaveFile() = default;
        ~SaveFile() = default;

        typedef std::map<std::wstring, std::wstring> StringMap;

        // Добавляет в локальный словарь поле. Если не получилось создать - вернёт false, в противном случае true
        bool AddProperty(const std::string& Property, const char * locale = STANDART);

        // Устанавливает в данный property значение value. Если не получилось добавить (отсуствие поля) вернёт false, в противном случае true
        bool SetProperty(const std::string& Property,const std::string& Value, const char * locate_second, const char * locate_first = STANDART);

        //Читает сохрвнённый словарь в FilePath и записывает его в локальную map. В случае ошибки вернёт false, в противном случае true
        bool ReadSave(const std::string& FilePath, const char * locate_second, const char * locate_first = STANDART);

        //Записывает в FilePath все поля и значение текущих данных. Формат: 'property':'value'. В случае ошибки вернёт false,  в противном случае true
        bool MakeSave(const std::string& FilePath, const char * locate_second, const char * locate_first = STANDART) ;

        //Вернёт значение по данному Property. Если достать не получилось, то вернёт пустую строку
        std::string ReadProperty(const std::string& Property, const char * locate_second, const char * locate_first = STANDART);

        StringMap GetMap() { return _Map;}
        bool DeleteProperty(std::string Key, const char * locale = STANDART);

        std::wstring ConvertToWstring(const std::string string, const char * locate);
        std::string ConvertTostring(const std::wstring string, const char * locate);
    
    private:
    
        std::wstring Word(const std::wstring& string, size_t *position, const char * locate = STANDART);

        bool IsAcceptable(wchar_t wchar, const char * locate);
        bool IsPropertyExists(const std::wstring& Property, const char * locate);
        bool IsWordCorrect(const std::wstring Word, const char * locate);
        
        // StringMap _Map{};
        std::map<std::wstring, std::wstring> _Map{};

};
#endif

