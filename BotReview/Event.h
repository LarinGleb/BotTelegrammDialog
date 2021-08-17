#ifndef __REVIEW_H___
#define __REVIEW_H___

#include <string>
#include <map>
#include "../SaveFile/SaveFile.h"
#include <fstream>
#include <iostream>
class Event {

private:
    int m_CountReviews;
    std::string m_Name;
   
public:
    SaveFile Save;

    Event(std::string Name) {
        m_Name = Name;
        m_CountReviews = 0;
    }
    Event() {
        m_Name = "NullEvent";
    }
    ~Event() = default;


    void PrintAllRevies();
    bool Rename(std::string Mame);
    bool AddReview(std::string Review);
    bool RemoveReview(std::string ID);
    bool SaveEvent(std::string Name);
    bool ReadFromFile(std::string Path);
    int GetCount() {return m_CountReviews;}
    std::string GetName() {return m_Name;}
};

#endif