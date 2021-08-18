#include <tgbot/tgbot.h>
#include<string>

bool InitBotTD(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message);
std::string TDAddOrKnow(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr& query);
std::string TDSex(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr& query);
std::string TDPrice(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr& query);
bool TDEatOrNo(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr& query);
bool TDAddPodsk(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr& query);
