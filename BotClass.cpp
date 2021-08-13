
#include "BotClass.h"

StateBot BotClass::GetState(std::string State) {
    if (State == "default") return DEFAULT;
    if (State == "botreview") return BOTREVIEW;
    if (State == "botfriend") return BOTFRIEND;
}

ActiveBot BotClass::GetActive(std::string State) {
    if (State == "exit") return EXIT;
    if (State == "active") return ACTIVE;
}

bool BotClass::InitCommandsBotMain(BotClass bot) {
    TgBot::Bot BotTg = bot.BotTg;

    Bot.getEvents().onCommand("start", [&Bot](TgBot::Message::Ptr message) { 
        Thisbot.Bot.getApi().sendMessage(message->chat->id, "Hi!");
        Thisbot.ActiveType = ACTIVE;
    });
}