#include <tgbot/tgbot.h>

void HandleAnswerCity(TgBot::Bot &bot);
//void ButtonTOWN(TgBot::Bot &bot, TgBot::Message::Ptr message);
void ButtonTOWN(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr query);
void ButtonEND(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr query);
void ButtonMAINSIGHTS(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr query);
void ButtonOtherTown(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr query);