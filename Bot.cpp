#include <stdio.h>
#include <string>
#include "SaveFile/SaveFile.h"
#include "tgbot/tgbot.h"
#include "ForTD/PPForTD.h"
#include "LibDB/DB.h"
#include "BotReview/BotReview.cpp"
#include <iostream>
#include <experimental/filesystem>

typedef enum activestate_t {
    EXIT,
    ACTIVE
} ActiveBot;

typedef enum botstate_t {
    DEFAULT,
    BOTREVIEW,
    BOTFRIEND,
    BOTFRIENDADD,
    BOTGUIDE,
    BOTTIME,
    BOTPARCE
} StateBot;

bool CheckIsCommnad(std::string Message) {
    return StringTools::startsWith(Message, "/list") | StringTools::startsWith(Message, "/start");
}

bool InitCommandsBotMain(TgBot::Bot &bot, ActiveBot *ActiveType, StateBot *State, ReviewState * Review) {
    bot.getEvents().onCommand("start", [&bot, ActiveType](TgBot::Message::Ptr message) { 
        bot.getApi().sendMessage(message->chat->id, "Hi!");
        *ActiveType = ACTIVE;
    });
    bot.getEvents().onCommand("exit", [&bot, ActiveType](TgBot::Message::Ptr message) { 
        bot.getApi().sendMessage(message->chat->id, "Good!");
        *ActiveType = EXIT;
    });
    bot.getEvents().onCommand("help", [&bot](TgBot::Message::Ptr message) { 
        bot.getApi().sendMessage(message->chat->id, "Writing help");
    });
    

    bot.getEvents().onCommand("review", [&bot, Review, State](TgBot::Message::Ptr message) {
        *State = BOTREVIEW;
        InitCommandsBotReview(bot, Review, message);
    });

    return true;
}

int main()
{
    std::string AddOrKnow;
    std::string Sex;
    std::string Price;
    bool EatOrNo;
    std::string AddPodsk;
    const std::string username = "psny";
    const std::string hostname = "192.168.88.240";
    const std::string password = "12345678";
    
    SaveFile Save;
    ActiveBot MyState = ACTIVE;
    StateBot BotState = DEFAULT;
    ReviewState BotReviewState = WAITING_COMMAND;
    Event *current_event = new Event();

    Save.ReadSave("../BotSettings.txt", ENGLISH);
    TgBot::Bot bot(Save.ReadProperty("Token", ENGLISH));

    db_api::Connector conn(hostname.c_str(), username.c_str(), password.c_str(), "rpnac5");

    InitCommandsBotMain(bot, &MyState);

    TgBot::InlineKeyboardMarkup::Ptr keyboardBot(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> row0;

    TgBot::InlineKeyboardButton::Ptr ButtonBOTGUIDE(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr ButtonBOTTIME(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr ButtonBOTREVIEW(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr ButtonBOTPARCE(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr ButtonBOTFRIEND(new TgBot::InlineKeyboardButton);

    
    bot.getEvents().onCommand("moduls", [&bot, &BotState, &keyboardBot](TgBot::Message::Ptr message) { 
        bot.getApi().sendMessage(message->chat->id, "Выберите бота: ", false, 0, keyboardBot);
    });

    InitCommandsBotMain(bot, &MyState, &BotState, &BotReviewState);

    bot.getEvents().onCallbackQuery([&bot, &AddOrKnow, &Sex, &Prise, &EatOrNo, &AddPodsk, &BotState, &conn](TgBot::CallbackQuery::Ptr query) {
        if ((StringTools::startsWith(query->data, "AddNew")) || (StringTools::startsWith(query->data, "ToKnow"))){
            AddOrKnow = TDAddOrKnow(bot, query);
        }
        else if((StringTools::startsWith(query->data, "ForBoy")) || (StringTools::startsWith(query->data, "ForGirl")) || (StringTools::startsWith(query->data, "ForAll"))){ 
            Sex = TDSex(bot, query);
        }
        else if((StringTools::startsWith(query->data, "Free")) || (StringTools::startsWith(query->data, "NoMuch")) || (StringTools::startsWith(query->data, "Average"))){
            Price = TDPrice(bot, query);
        }
        else if((StringTools::startsWith(query->data, "Eat")) || (StringTools::startsWith(query->data, "NoEat"))){
            EatOrNo = TDEatOrNo(bot, query);
            if(AddOrKnow == "AddNew"){
                BotState = BOTFRIENDADD;
                TDAddPodsk(bot, query);
            }
            else{
                conn.KnowPo(Sex, Price, EatOrNo, query->message, bot);

                BotState = DEFAULT;
            }
        }

    });


    bot.getEvents().onAnyMessage([&bot, &BotState, &MyState, &AddPodsk, &Sex, &Price, &EatOrNo, &connm, &BotReviewState, current_event](TgBot::Message::Ptr message)    {
        switch (MyState)
        {
        case ACTIVE:
            switch(BotState) {
                case BOTFRIEND: 
                    InitBotTD(bot, message);
                break;

                case BOTFRIENDADD: {
                    AddPodsk = message->text;

                    conn.AddPo(AddPodsk, Sex, Price, EatOrNo, message, bot);

                    BotState = DEFAULT;

                    break;
                }

                case BOTGUIDE: // for vlad
                break;

                case BOTREVIEW:
                    switch (BotReviewState)
                    {
                    
                    case WAITING_COMMAND:
                        break;
                    case WAITING_NAME_EVENT: {
                        if(!GetEventByName(current_event, message->text.c_str())) {
                            if (CheckIsCommnad(message->text.c_str())) {
                               return;
                            }
                            else {
                                bot.getApi().sendMessage(message->chat->id, "Такого мероприятия не существует!"); 
                            }
                           return;
                        }
                        BotReviewState = WAITING_REVIE;
                        bot.getApi().sendMessage(message->chat->id, "Введите отзыв: "); 
                        break;
                    }
                    case WAITING_REVIE: {
                        
                        current_event->AddReview(message->text.c_str());
                        BotReviewState = WAITING_COMMAND;
                        current_event->SaveEvent(current_event->GetName());
                        bot.getApi().sendMessage(message->chat->id, "Спасибо за отзыв!"); 
                        break;
                    }

                    case WAITING_NAME_EVENT_READING: {
                        if(!GetEventByName(current_event, message->text.c_str())) {
                            if (CheckIsCommnad(message->text.c_str())) {
                               return;
                            }
                            else {
                                bot.getApi().sendMessage(message->chat->id, "Такого мероприятия не существует!"); 
                            }
                           return;
                        }
                        SaveFile ReadReviews;
                        ReadReviews.ReadSave("../BotReview/Events/" + current_event->GetName() + ".txt", RUSSION, ENGLISH);
                        for (auto const & event: ReadReviews.GetMap()) {
                            bot.getApi().sendMessage(message->chat->id, ReadReviews.ConvertTostring(event.first, ENGLISH) + ": \n" + ReadReviews.ConvertTostring(event.second, RUSSION)); 
                        }
                        BotReviewState = WAITING_COMMAND;
                        break;
                    }
                    case WAITING_PASSOWRD: {
                        std::string Password = message->text.c_str();
                        if (Password == "123") {
                            BotReviewState = WAITING_NAME_EVENT_ADDED;
                            bot.getApi().sendMessage(message->chat->id, "Введите название мероприятия"); 
                        }
                        else {
                            bot.getApi().sendMessage(message->chat->id, "Вы не препод! Не пытайтесь даже!");
                            BotReviewState = WAITING_COMMAND;
                            return;
                        }
                        break;
                    }
                    case WAITING_NAME_EVENT_ADDED: {
                        Event *event = new Event(message->text.c_str());
                        event->SaveEvent(event->GetName());
                        AddEvent(event);
                        BotReviewState = WAITING_COMMAND;
                        bot.getApi().sendMessage(message->chat->id, "Успешно созданно!"); 
                        break;
                    }
                    case WAITING_PASSOWRD_FOR_DELETE: {
                        std::string Password = message->text.c_str();
                        if (Password == "123") {
                            BotReviewState = WAITING_NAME_EVENT_DELETE;
                            bot.getApi().sendMessage(message->chat->id, "Введите название мероприятия"); 
                        }
                        else {
                            bot.getApi().sendMessage(message->chat->id, "Вы не препод! Не пытайтесь даже!");
                            BotReviewState = WAITING_COMMAND;
                            return;
                        }
                        break;
                    }
                    case WAITING_NAME_EVENT_DELETE: {
                        std::string Event = message->text;
                        if(!GetEventByName(current_event, message->text.c_str())) {
                            if (CheckIsCommnad(message->text.c_str())) {
                               return;
                            }
                            else {
                                bot.getApi().sendMessage(message->chat->id, "Такого мероприятия не существует!"); 
                            }
                           return;
                        }
                        std::cout << "deleting event...\n";
                        DeleteEvent(*current_event);
                        BotReviewState = WAITING_COMMAND;
                    }
                }
                break;

                case BOTPARCE: // for sasha
                break;

                case BOTTIME: // for valya
                break;

                case DEFAULT:
                break;
            }
            break;
        case EXIT:
            return;
        default:
            break;
        }
        
    });

    bot.getEvents().onCommand("friend", [&bot, &BotState](TgBot::Message::Ptr message) { 
        BotState = BOTFRIEND;
        InitBotTD(bot, message);
    });

    TgBot::TgLongPoll longPoll(bot);
    while (true)
    {
        printf("Long poll started\n");
        longPoll.start();
    }
    
    return 0;
}
