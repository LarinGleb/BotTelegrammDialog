#include <stdio.h>
#include <string>
#include "SaveFile/SaveFile.h"
#include "tgbot/tgbot.h"
#include "ForTD/PPForTD.h"
#include "LibDB/DB.h"


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

ActiveBot GetActive(std::string State) {
    if (State == "active") {return EXIT;}
    else {return EXIT;}
}

bool InitCommandsBotMain(TgBot::Bot &bot, ActiveBot *ActiveType) {

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
    Save.ReadSave("../BotSettings.txt");
    TgBot::Bot bot(Save.ReadProperty("Token"));

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

    });


    bot.getEvents().onAnyMessage([&bot, &BotState, &MyState, &AddPodsk, &Sex, &Price, &EatOrNo, &conn](TgBot::Message::Ptr message)    {
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
