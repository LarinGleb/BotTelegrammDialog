#include <stdio.h>
#include <tgbot/tgbot.h>
#include "SaveFile/SaveFile.h"
int main()
{
    // ====================
    // SAVE FILE CONFIG

    // save file workflow
    SaveFile Save;

    Save.ReadSave("../BotSettings.txt");
    Save.AddProperty("Status");
    Save.SetProperty("Status", "Calm");
    Save.AddProperty("Token");
    Save.SetProperty("Token", "1940339152:AAH8fohu8_cETEVz-LNOBEAKT2a5VEJ0Q-8");
    Save.AddProperty("Config");
    Save.SetProperty("Config", "0");
    Save.MakeSave("../BotSettings.txt");
    return 0;

    // ====================
    // BOT BODY

    TgBot::Bot bot(Save.ReadProperty("Token"));
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) { 
        bot.getApi().sendMessage(message->chat->id, "Hi!"); 
    });

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message)    {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start"))
        {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });
    
    printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
    TgBot::TgLongPoll longPoll(bot);
    while (true)
    {
        printf("Long poll started\n");
        longPoll.start();
    }


    
    return 0;
}
