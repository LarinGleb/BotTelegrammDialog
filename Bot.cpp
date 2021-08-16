#include <stdio.h>
#include <string>
#include "SaveFile/SaveFile.h"
#include "tgbot/tgbot.h"
#include "ForTD/PPForTD.h"

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
    std::string Prise;
    std::string EatOrNo;
    std::string AddPodsk;
    
    SaveFile Save;
    ActiveBot MyState = ACTIVE;
    StateBot BotState = DEFAULT;
    Save.ReadSave("../BotSettings.txt");
    TgBot::Bot bot(Save.ReadProperty("Token"));

    InitCommandsBotMain(bot, &MyState);

     bot.getEvents().onCallbackQuery([&bot, &AddOrKnow, &Sex, &Prise, &EatOrNo, &AddPodsk, &BotState](TgBot::CallbackQuery::Ptr query) {
        if ((StringTools::startsWith(query->data, "AddNew")) || (StringTools::startsWith(query->data, "ToKnow"))){
            AddOrKnow = TDAddOrKnow(bot, query);
        }
        else if((StringTools::startsWith(query->data, "ForBoy")) || (StringTools::startsWith(query->data, "ForGirl")) || (StringTools::startsWith(query->data, "ForAll"))){ 
            Sex = TDSex(bot, query);
        }
        else if((StringTools::startsWith(query->data, "Free")) || (StringTools::startsWith(query->data, "NoMuch")) || (StringTools::startsWith(query->data, "Average"))){
            Prise = TDPrise(bot, query);
        }
        else if((StringTools::startsWith(query->data, "Eat")) || (StringTools::startsWith(query->data, "NoEat"))){
            EatOrNo = TDEatOrNo(bot, query);
            if(AddOrKnow == "AddNew"){
                BotState = BOTFRIENDADD;
                TDAddPodsk(bot, query);
            }
            else{
                //выдать что-то из бд
                BotState = DEFAULT;
            }
        }

    });


    bot.getEvents().onAnyMessage([&bot, &BotState, &MyState, &AddPodsk, &Sex, &Prise, &EatOrNo](TgBot::Message::Ptr message)    {
        switch (MyState)
        {
        case ACTIVE:
            switch(BotState) {
                case BOTFRIEND: 
                    InitBotTD(bot, message);
                break;

                case BOTFRIENDADD:
                    AddPodsk = message->text;
                    //добавить в бд
                    BotState = DEFAULT;


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
