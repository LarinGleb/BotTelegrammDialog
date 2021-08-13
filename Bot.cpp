#include <stdio.h>
#include "SaveFile/SaveFile.h"
#include "BotClass.h"
// bool InitCommandsBotMain(bot) {
//     bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) { 
//         bot.getApi().sendMessage(message->chat->id, "Hi!"); 
//     });
// }

int main()
{
    SaveFile Save;

    TgBot::Bot bot(Save.ReadProperty("Token"));
    

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message)    {

        switch (state) {
            case DEFAULT:

            break;

            deafult:

                break;

        }
        // printf("User wrote %s\n", message->text.c_str());
        // if (StringTools::startsWith(message->text, "/start"))
        // {
        //     return;
        // }
        // bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
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
