#include <stdio.h>
#include "../SaveFile/SaveFile.h"
#include "tgbot/tgbot.h"
#include "Event.h"
#include <list>
#include <sstream>

typedef enum botreview_t {
    WAITING_REVIE,
    WAITING_COMMAND,
    WAITING_NAME_EVENT,
    WAITING_NAME_EVENT_READING,
    WAITING_NAME_EVENT_ADDED,
    WAITING_PASSOWRD,
    WAITING_PASSOWRD_FOR_DELETE,
    WAITING_NAME_EVENT_DELETE
} ReviewState;
std::list<Event *> ListEvents;

bool AddEvent(Event *event) {
    ListEvents.push_back(event);
    SaveFile AddSave;
    AddSave.ReadSave("../BotReview/Events/Events.txt");

    AddSave.AddProperty(event->GetName());
    AddSave.SetProperty(event->GetName(), event->GetName() + ".txt");
    AddSave.MakeSave("../BotReview/Events/Events.txt");
    return true;
}

bool GetEventByName(Event * NullEvent, std::string name) {
    for (Event *event: ListEvents) {
        if  (event->GetName() == name) {
            event->ReadFromFile("../BotReview/Events/" + event->GetName() + ".txt");
            *NullEvent = *event;
            return true;
        }
    }
    return false;
}
bool DeleteEvent(Event eventDelete) {
    SaveFile DeleteEvent;
    DeleteEvent.ReadSave("../BotReview/Events/Events.txt");

    for (const auto& event: ListEvents) {
        if (event->GetName() == eventDelete.GetName()) {
            ListEvents.remove(event);
            break;
        }
    }

    DeleteEvent.DeleteProperty(eventDelete.GetName());
    DeleteEvent.MakeSave("../BotReview/Events/Events.txt");

    std::stringstream Path ("../BotReview/Events/" + eventDelete.GetName() + ".txt");
    std::remove(Path.str().c_str());
    return true;
}

bool InitCommandsBotReview(TgBot::Bot &bot, ReviewState *BotState, TgBot::Message::Ptr message) {

    SaveFile Save{};
    *BotState = WAITING_COMMAND;
    Save.ReadSave("../BotReview/Events/Events.txt");
        for (auto const & eventpair: Save.GetMap()) {
        Event *event = new Event(eventpair.first);
        event->ReadFromFile("../BotReview/Events/" + eventpair.second);
        ListEvents.push_back(event);
    }
    
    bot.getApi().sendMessage(message->chat->id, "Привет! Я бот для добавленния отзывов к мероприятиям. Команды: \n /addReview - добавит отзыв к мероприятию \n /readReviews - посмотреть отзывы об мероприятиях \n /list - выведет все мероприятия  \n (ТОЛЬКО ДЛЯ ПРЕПОДОВ) \n /addEvent - добавит мероприятие с  нужным названием \n /removeEvent - удалит мероприятие по имени. ВНИМАНИЕ. Навсегда. Со всеми отзывами.");
    bot.getEvents().onCommand("list", [&bot](TgBot::Message::Ptr message) {
        
        SaveFile Save{};
        std::string Message = "Мероприятия: \n";
        int lineMessage = 1;
        Save.ReadSave("../BotReview/Events/Events.txt");
        for(const auto& eventpair : Save.GetMap()) {
            Message += std::to_string(lineMessage) + ". " + eventpair.first + '\n';
            lineMessage += 1;
        }
        bot.getApi().sendMessage(message->chat->id, Message);
    });
    bot.getEvents().onCommand("addReview", [&bot, BotState](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Выберите мероприятие");
        *BotState = WAITING_NAME_EVENT;
    });
    bot.getEvents().onCommand("addEvent", [&bot, BotState](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Напишите пароль: ");
        *BotState = WAITING_PASSOWRD;
    });
    bot.getEvents().onCommand("removeEvent", [&bot, BotState](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Напишите пароль: ");
        *BotState = WAITING_PASSOWRD_FOR_DELETE;
    });
    bot.getEvents().onCommand("readReviews", [&bot, BotState](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Выберите мероприятие");
        *BotState = WAITING_NAME_EVENT_READING;
    });
    return true;
}

