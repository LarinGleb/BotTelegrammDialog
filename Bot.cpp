#include <stdio.h>
#include <tgbot/tgbot.h>

int main()
{
    // ====================
    // SAVE FILE CONFIG

    // save file workflow

    // ====================
    // BOT BODY

    TgBot::Bot bot("1940339152:AAH8fohu8_cETEVz-LNOBEAKT2a5VEJ0Q-8");
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
