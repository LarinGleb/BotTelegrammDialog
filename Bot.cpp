
#include <string>
#include "SaveFile/SaveFile.h"
#include "tgbot/tgbot.h"
#include "ForTD/PPForTD.h"
#include "LibDB/DB.h"
#include "BotReview/BotReview.cpp"
#include <iostream>
#include <experimental/filesystem>
#include "bottimelib/BotTime.h"
#include <ctime>
timedifference diff;
std::map <std::string,timedifference> timetable = {
                            {"Lunch", {14,0}},
                            {"Dinner", {19,0}},
                            {"Breakfast", {9,0}},
                            {"Event1", {17,0}},
                            {"Event2", {20,0}}
                            };
                            
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

    Save.ReadSave("../BotSettings.txt");
    TgBot::Bot bot(Save.ReadProperty("Token"));

    db_api::Connector conn(hostname.c_str(), username.c_str(), password.c_str(), "rpnac5");

    InitCommandsBotMain(bot, &MyState, &BotState, &BotReviewState);

    TgBot::InlineKeyboardMarkup::Ptr keyboardBot(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> row0;

    TgBot::InlineKeyboardButton::Ptr ButtonBOTGUIDE(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr ButtonBOTTIME(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr ButtonBOTREVIEW(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr ButtonBOTPARCE(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr ButtonBOTFRIEND(new TgBot::InlineKeyboardButton);

    TgBot::InlineKeyboardMarkup::Ptr timekeyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardMarkup::Ptr deathkeyboard(new TgBot::InlineKeyboardMarkup);

    std::vector<TgBot::InlineKeyboardButton::Ptr> row0;
    std::vector<TgBot::InlineKeyboardButton::Ptr> row1;
    std::vector<TgBot::InlineKeyboardButton::Ptr> deathrow;

    TgBot::InlineKeyboardButton::Ptr death(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr breakfast(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr lunch(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr dinner(new TgBot::InlineKeyboardButton);

    TgBot::InlineKeyboardButton::Ptr event1(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr event2(new TgBot::InlineKeyboardButton);

    death->text = "с̶̪̈́̓̀̕ͅм̸̨̛̟̦̞͙̫̳͋̆͐̓̃̏̋̈́е̴̣̼̭̰̠̪̼̭͇͉̿̅р̷̼̤͍̳̔͌̄͋̈́̓́́̀̈̿͂̿̚͜т̷̛͍̭̣͎̋͒̽͂͒̔̓͆̌͌̾̈́͝ь̸̡̩̲̟̠͔͍̜̲̬̼̮̍̂͐͑͋̎̑͐́̆͋̚̚̕ͅ";
    death->callbackData = "death";

    breakfast->text = "завтрак";
    breakfast->callbackData = "breakfast";

    lunch->text = "обед";
    lunch->callbackData = "lunch";

    dinner->text = "ужин";
    dinner->callbackData = "dinner";

    event1->text = "мероприятие 1";
    event1->callbackData = "event1";

    event2->text = "мероприятие 2";
    event2->callbackData = "event2";

    row0.push_back(breakfast);
    row0.push_back(lunch);
    row0.push_back(dinner);
    row1.push_back(event1);
    row1.push_back(event2);

    deathrow.push_back(death);

    timekeyboard->inlineKeyboard.push_back(row0);
    timekeyboard->inlineKeyboard.push_back(row1);

    deathkeyboard->inlineKeyboard.push_back(deathrow);
    
    InitCommandsBotMain(bot, &MyState);



    bot.getEvents().onCommand("time", [&bot, &timekeyboard](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Выберите событие, время до которого вы хотите узнать:", false, 0, timekeyboard, "Markdown");
    });
    
    bot.getEvents().onCommand("moduls", [&bot, &BotState, &keyboardBot](TgBot::Message::Ptr message) { 
        bot.getApi().sendMessage(message->chat->id, "Выберите бота: ", false, 0, keyboardBot);
    });

    InitCommandsBotMain(bot, &MyState, &BotState, &BotReviewState);

    bot.getEvents().onCallbackQuery([&bot, &AddOrKnow, &Sex, &Price, &EatOrNo, &AddPodsk, &BotState, &conn](TgBot::CallbackQuery::Ptr query) {
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
        if (StringTools::startsWith(query->data, "death"))
        {
            std::string response = "0̸͙̰̫͓͉͍͔̹̘̤̗̐̄̓̑̍̇̽̓̏̔͋̋̈͌̕̚̚͠ ӵ̸̢̧̯͈͔̘̩͙̺͙̌͂̈́̈́̑̌. 0̸͙̰̫͓͉͍͔̹̘̤̗̐̄̓̑̍̇̽̓̏̔͋̋̈͌̕̚̚͠ м̶̨͔̺̮̯̮̾͒̂͒̍̓̏͛͌̕и̵̬̗̞͖̻̤̫̩̼͕͍̰͕̩͙̾̅͝н̶̡̥͍̫̬̬̺̺͇̪̗̘͚͎̥͙͖̑̒̆͗͊̈́̀̅̈́̚.";
            bot.getApi().sendMessage(query->message->chat->id, response , false, 0, deathkeyboard, "Markdown");    
        }  

        if (StringTools::startsWith(query->data, "breakfast"))
        {
            diff = HandleTime(timetable["Breakfast"]);
            std::string response = "Времени до завтрака: \n" + std::to_string(diff.hoursdiff) + " ч. " + std::to_string(diff.minutesdiff) + " мин.";
            bot.getApi().sendMessage(query->message->chat->id, response , false, 0, timekeyboard, "Markdown");      
        }
        if (StringTools::startsWith(query->data, "lunch"))
        {
            diff = HandleTime(timetable["Lunch"]);
            std::string response = "Времени до обеда: \n" + std::to_string(diff.hoursdiff) + " ч. " + std::to_string(diff.minutesdiff) + " мин.";
            bot.getApi().sendMessage(query->message->chat->id, response , false, 0, timekeyboard, "Markdown");        
        }
        if (StringTools::startsWith(query->data, "event1"))
        {
            diff = HandleTime(timetable["Event1"]);
            std::string response = "Времени до мероприятия 1: \n" + std::to_string(diff.hoursdiff) + " ч. " + std::to_string(diff.minutesdiff) + " мин.";
            bot.getApi().sendMessage(query->message->chat->id, response , false, 0, timekeyboard, "Markdown");        
        }
        if (StringTools::startsWith(query->data, "event2"))
        {
            diff = HandleTime(timetable["Event2"]);
            std::string response = "Времени до мероприятия 2: \n" + std::to_string(diff.hoursdiff) + " ч. " + std::to_string(diff.minutesdiff) + " мин.";
            bot.getApi().sendMessage(query->message->chat->id, response , false, 0, timekeyboard, "Markdown");        
        }
        if (StringTools::startsWith(query->data, "dinner"))
        {
            diff = HandleTime(timetable["Dinner"]);
            std::string response = "Времени до ужина: \n" + std::to_string(diff.hoursdiff) + " ч. " + std::to_string(diff.minutesdiff) + " мин.";
            bot.getApi().sendMessage(query->message->chat->id, response , false, 0, timekeyboard, "Markdown");  
        }

    });
    bot.getEvents().onCommand("death", [&bot, &deathkeyboard](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Ӧ̵̧̲͖͉̫̻̥̺͈͚̣̪́Б̵̡̙̦̤̏̊́̎̓̀̊̉͆͋̀̀Р̴̧̨̺͙̮͙̩̰̭̥̙͚̜̝̐̾̈́̅̊̿̈́̓̔̆̅̍̈́͛̕͠Е̷̲̺̖̼̩̹͓̐̐̐͂̂̂Ч̶̡̼̣̣̟͖̭̣̯̦͐͊́͌͐̓̉̏̍̃͗̆̄̓̄̚ͅЁ̴̛̣̬̳͍͓̳͎̺̩͌̀̈̃̅̌̓͜ͅН̵̲̘̳̟̖̱͛͌̉͑́͑͆͒̀̄̿̕͝͠", false, 0, deathkeyboard, "Markdown");
    });

    bot.getEvents().onAnyMessage([&bot, &BotState, &MyState, &AddPodsk, &Sex, &Price, &EatOrNo, &conn, &BotReviewState, current_event](TgBot::Message::Ptr message)    {
        switch (MyState)
    

    bot.getEvents().onCallbackQuery([&bot, &deathkeyboard, &timekeyboard](TgBot::CallbackQuery::Ptr query) {
        
     });

    bot.getEvents().onAnyMessage([&bot, BotState, MyState](TgBot::Message::Ptr message) {
        switch (MyState) {
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
    while (true) {
        printf("Long poll started\n");
        longPoll.start();
    }

    return 0;
}
