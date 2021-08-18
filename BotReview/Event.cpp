#include "Event.h"

#include <iostream>

bool Event::Rename(std::string Name) {
    
    m_Name = Name;
    return true;
}

bool Event::ReadFromFile(std::string Path) {
    Save.ReadSave(Path);
    m_CountReviews = Save.GetMap().size();
    ///for (int i = 0; i < m_CountReviews; i ++) {
      //  std::cout << Path << ": " << Save._Properties[i] << " ";
    //}
    return true;
}

int Event::SaveEvent(std::string Name) {
    return Save.MakeSave("../BotReview/Events/" + Name + ".txt");
}
int Event::AddReview(std::string Review) {
    m_CountReviews += 1;
    if(Save.AddProperty("Review " + std::to_string(m_CountReviews)) == ERROR_NAME) {
        m_CountReviews -= 1;
        return ERROR_NAME;
    }
    
    if (!Save.IsWordCorrect(Review)) {
        m_CountReviews -= 1;
        return ERROR_NAME;
    }
    Save.SetProperty("Review " + std::to_string(m_CountReviews), Review);
    
    return OK;
}

bool Event::RemoveReview(std::string ID) {
    return Save.DeleteProperty("Review " + ID + ":");
}