#ifndef BOT_H
#define BOT_H
#include <tgbot/tgbot.h>
#include <string>

typedef enum activestate_t {
    EXIT,
    ACTIVE,
} ActiveBot;

typedef enum botstate_t {
    DEFAULT,
    BOTREVIEW,
    BOTFRIEND
} StateBot;

class BotClass {
    private:
        StateBot Type;
        ActiveBot ActiveType;
        TgBot::Bot BotTg;
    public:
        BotClass(TgBot::Bot Bot, ActiveBot ActiveType, StateBot Type);
        ActiveBot GetActive(std::string State);
        StateBot GetState(std::string State);
        bool InitCommandsBotMain(BotClass bot);

        

};

#endif