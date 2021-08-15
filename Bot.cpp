#include <stdio.h>
#include "SaveFile/SaveFile.h"
#include "tgbot/tgbot.h"

typedef enum activestate_t {
    EXIT,
    ACTIVE
} ActiveBot;

typedef enum botstate_t {
    DEFAULT,
    BOTREVIEW,
    BOTFRIEND,
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
    SaveFile Save;
    ActiveBot MyState = ACTIVE;
    StateBot BotState = DEFAULT;
    Save.ReadSave("../BotSettings.txt");
    TgBot::Bot bot(Save.ReadProperty("Token"));

    InitCommandsBotMain(bot, &MyState);

    bot.getEvents().onAnyMessage([&bot, BotState, MyState](TgBot::Message::Ptr message)    {
        switch (MyState)
        {
        case ACTIVE:
            switch(BotState) {
                case BOTFRIEND: //  для Пети
                break;

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

    TgBot::TgLongPoll longPoll(bot);
    while (true)
    {
        printf("Long poll started\n");
        longPoll.start();
    }
    
    return 0;
}
