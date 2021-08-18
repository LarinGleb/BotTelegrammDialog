#include "Event.h"

#include <iostream>

bool Event::Rename(std::string Name) {
    
    m_Name = Name;
    return true;
}

bool Event::ReadFromFile(std::string Path) {
    Save.ReadSave(Path, RUSSION);
    m_CountReviews = Save.GetMap().size();
    ///for (int i = 0; i < m_CountReviews; i ++) {
      //  std::cout << Path << ": " << Save._Properties[i] << " ";
    //}
    return true;
}

bool Event::SaveEvent(std::string Name) {
    return Save.MakeSave("../BotReview/Events/" + Name + ".txt", RUSSION);
}
bool Event::AddReview(std::string Review) {
    m_CountReviews += 1;
    if(!Save.AddProperty("Review " + std::to_string(m_CountReviews))) {
        return false;
    }
    
    Save.SetProperty("Review " + std::to_string(m_CountReviews), Review, RUSSION);
    
    return true;
}

bool Event::RemoveReview(std::string ID) {
    return Save.DeleteProperty("Review " + ID + ":");
}