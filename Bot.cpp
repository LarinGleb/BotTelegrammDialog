#include <stdio.h>
#include <string>
#include "SaveFile/SaveFile.h"
#include "LibDB/DB.h"
#include "BotReview/BotReview.cpp"
#include <iostream>
#include <experimental/filesystem>
#include "dirVlad/bot_guide.h"
#include "tgbot/tgbot.h"


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

enum BotGuideState {
    BOTGUIDE_DEFAULT,
    BOTGUIDE_AWAITING_FOR_AN_ANSWER_CITY,
    BOTGUIDE_D
};

bool CheckIsCommnad(std::string Message) {
    return StringTools::startsWith(Message, "/list") | StringTools::startsWith(Message, "/start");
}

StateBot GetState(std::string State) {
    if (State == "botfriend") {
        return BOTFRIEND;
    }
    else if (State == "botreview") {
        return BOTREVIEW;
    }
    else { 
        return DEFAULT;
    }
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
    BotGuideState BotStateGuide = BOTGUIDE_DEFAULT;
    ReviewState BotReviewState = WAITING_COMMAND;
    Event *current_event = new Event();

    Save.ReadSave("../BotSettings.txt");
    TgBot::Bot bot(Save.ReadProperty("Token"));
    const std::string username = "psny";
    const std::string hostname = "192.168.88.240";
    const std::string password = "12345678";
    

    db_api::Connector conn(hostname.c_str(), username.c_str(), password.c_str(), "rpnac5");

    InitCommandsBotMain(bot, &MyState, &BotState, &BotReviewState);

    

    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> rowCHOICE;
    TgBot::InlineKeyboardButton::Ptr checkButtonTOWN(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr checkButtonMAINSIGHTS(new TgBot::InlineKeyboardButton);
    checkButtonTOWN->text = "1";
    checkButtonTOWN->callbackData = "Choice...TOwn";
    checkButtonMAINSIGHTS->text = "2";
    checkButtonMAINSIGHTS->callbackData = "mainsights";
    rowCHOICE.push_back(checkButtonTOWN);
    rowCHOICE.push_back(checkButtonMAINSIGHTS);
    keyboard->inlineKeyboard.push_back(rowCHOICE);

    bot.getEvents().onCommand("sights", [&bot, &keyboard, &BotState](TgBot::Message::Ptr message) { 
        BotState = BOTGUIDE;
        bot.getApi().sendMessage(message->chat->id, "Привет, я бот-гид. Я могу показать тебе разные достопримечательности России. Чтобы узнать о главных достопримечательностей какого-то города, нажми 1, а если ты турист и не знаешь что посетить, то нажми 2", false, 0, keyboard);
        
    });

    InitCommandsBotMain(bot, &MyState, &BotState, &BotReviewState);

    bot.getEvents().onCallbackQuery([&bot, &AddOrKnow, &Sex, &Price, &EatOrNo, &AddPodsk, &BotState, &conn, &BotStateGuide, &keyboard](TgBot::CallbackQuery::Ptr query) {
        if ((StringTools::startsWith(query->data, "AddNew")) || (StringTools::startsWith(query->data, "ToKnow"))){
            AddOrKnow = TDAddOrKnow(bot, query);
        } 
        else if (StringTools::startsWith(query->data, "Choice...TOwn")) {
            std::string response = "Напиши город, о котором ты хочешь узнать...";
            bot.getApi().sendMessage(query->message->chat->id, response);
            if (BotStateGuide == BOTGUIDE_D) {
                ButtonTOWN(bot, query);
            }  
            BotStateGuide = BOTGUIDE_AWAITING_FOR_AN_ANSWER_CITY;
                      
        }
        else if (StringTools::startsWith(query->data, "mainsights")) 
        {
            ButtonMAINSIGHTS(bot, query);
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
        else if (StringTools::startsWith(query->data, "DEFAULT"))
        {
            ButtonEND(bot, query);
            BotStateGuide = BOTGUIDE_DEFAULT;
        }
        else if (StringTools::startsWith(query->data, "OtherTown"))
        {
            std::string response = "Напиши город, о котором ты хочешь узнать...";
            bot.getApi().sendMessage(query->message->chat->id, response);
            BotStateGuide = BOTGUIDE_AWAITING_FOR_AN_ANSWER_CITY;
            if (BotStateGuide == BOTGUIDE_D) {
                ButtonTOWN(bot, query);
            } 
        }
    });


    bot.getEvents().onAnyMessage([&bot, &BotState, &MyState, &AddPodsk, &Sex, &Price, &EatOrNo, &conn, &BotReviewState, current_event, &BotStateGuide, &keyboard2](TgBot::Message::Ptr message)    {
        switch (MyState)
        {
        case ACTIVE:
            switch(BotState) {
                case BOTFRIEND: 
                break;

                case BOTFRIENDADD: {
                    AddPodsk = message->text;

                    conn.AddPo(AddPodsk, Sex, Price, EatOrNo, message, bot);

                    BotState = DEFAULT;
                }
                break;

                case BOTGUIDE: { // for vlad
                    switch(BotStateGuide) {
                        case BOTGUIDE_AWAITING_FOR_AN_ANSWER_CITY: {
                            conn.SearchDescriptions(message->text.c_str(), message, bot);
                            BotStateGuide = BOTGUIDE_D;
                            break;
                        }
                    }
                }
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
                        BotReviewState = WAITING_COMMAND;
                        if(current_event->AddReview(message->text.c_str()) == ERROR_NAME) {
                            bot.getApi().sendMessage(message->chat->id, "Неверный формат отзыва!");
                            return;     
                        }
                        
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
                        ReadReviews.ReadSave("../BotReview/Events/" + current_event->GetName() + ".txt");
                        for (auto const & event: ReadReviews.GetMap()) {
                            bot.getApi().sendMessage(message->chat->id, event.first + ": \n" + event.second); 
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
                        if(AddEvent(event) == ERROR_NAME) {
                            bot.getApi().sendMessage(message->chat->id, "Ошибка в названии!");
                            return;    
                        };
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

                case BOTPARCE:
                break;

                case BOTTIME:
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

    TgBot::TgLongPoll longPoll(bot);
    while (true)
    {
        printf("Long poll started\n");
        longPoll.start();
    }
    
    return 0;
}
