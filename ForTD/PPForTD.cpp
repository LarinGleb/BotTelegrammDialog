#include <tgbot/tgbot.h>
#include "PPForTD.h"
#include <string>


bool InitBotTD(TgBot::Bot& bot, std::shared_ptr<TgBot::Message> message) {

    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> row0;

    TgBot::InlineKeyboardButton::Ptr WriteNew(new TgBot::InlineKeyboardButton);
    WriteNew->text = "Добавить";
    WriteNew->callbackData = "AddNew";
    row0.push_back(WriteNew);

    TgBot::InlineKeyboardButton::Ptr ReadOld(new TgBot::InlineKeyboardButton);
    ReadOld->text = "Узнать";
    ReadOld->callbackData = "ToKnow";
    row0.push_back(ReadOld);

    keyboard->inlineKeyboard.push_back(row0);

    bot.getApi().sendMessage(message->chat->id, "Привет! Это модуль для тех, кто не знает, "
    "что можно подарить тайному другу, и для тех, кто хочет помочь справиться с этим другим." 
    "Итак, ты хочешь узнать подсказку или помочь другим, добавив свой вариант?", false, 0, keyboard);

    return true;
}


std::string TDAddOrKnow(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr& query){

    TgBot::InlineKeyboardMarkup::Ptr keyboardSex(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> row1;

    TgBot::InlineKeyboardButton::Ptr ForBoy(new TgBot::InlineKeyboardButton);
    ForBoy->text = "Для мальчика";
    ForBoy->callbackData = "ForBoy";
    row1.push_back(ForBoy);

    TgBot::InlineKeyboardButton::Ptr ForGirl(new TgBot::InlineKeyboardButton);
    ForGirl->text = "Для девочки";
    ForGirl->callbackData = "ForGirl";
    row1.push_back(ForGirl);

    TgBot::InlineKeyboardButton::Ptr ForAll(new TgBot::InlineKeyboardButton);
    ForAll->text = "Универсальная";
    ForAll->callbackData = "ForAll";
    row1.push_back(ForAll);

    keyboardSex->inlineKeyboard.push_back(row1);

    if (StringTools::startsWith(query->data, "AddNew")) {
        bot.getApi().sendMessage(query->message->chat->id, "Отлтчно! Для кого будет подсказка?" ,false, 0, keyboardSex, "Markdown");
        return"AddNew";
    }

    if(StringTools::startsWith(query->data, "ToKnow")) {
        bot.getApi().sendMessage(query->message->chat->id, "Отлтчно! Для кого будет подсказка?" ,false, 0, keyboardSex, "Markdown");
        return "ToKnow";
    }
    
    return "error";
}


std::string TDSex(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr& query){

    TgBot::InlineKeyboardMarkup::Ptr keyboardPrise(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> row2;

    TgBot::InlineKeyboardButton::Ptr Free(new TgBot::InlineKeyboardButton);
    Free->text = "Бесплатная";
    Free->callbackData = "Free";
    row2.push_back(Free);

    TgBot::InlineKeyboardButton::Ptr NoMuch(new TgBot::InlineKeyboardButton);
    NoMuch->text = "0-100 рублей";
    NoMuch->callbackData = "NoMuch";
    row2.push_back(NoMuch);

    TgBot::InlineKeyboardButton::Ptr Average(new TgBot::InlineKeyboardButton);
    Average->text = "100+ рублей";
    Average->callbackData = "Average";
    row2.push_back(Average);

    keyboardPrise->inlineKeyboard.push_back(row2);
    
    if(StringTools::startsWith(query->data, "ForBoy")){ 
        bot.getApi().sendMessage(query->message->chat->id, "А сколько будет стоить?" ,false, 0, keyboardPrise, "Markdown");
        return "Boy";
    }

    else if(StringTools::startsWith(query->data, "ForGirl")){ 
        bot.getApi().sendMessage(query->message->chat->id, "А сколько будет стоить?" ,false, 0, keyboardPrise, "Markdown");
        return "Girl";
    }

    else if(StringTools::startsWith(query->data, "ForAll")){ 
        bot.getApi().sendMessage(query->message->chat->id, "А сколько будет стоить?" ,false, 0, keyboardPrise, "Markdown");
        return "All";
    }

    return "error";
}


std::string TDPrise(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr& query){

    TgBot::InlineKeyboardMarkup::Ptr keyboardEat(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> row3;

    TgBot::InlineKeyboardButton::Ptr Eat(new TgBot::InlineKeyboardButton);
    Eat->text = "Съедобно";
    Eat->callbackData = "Eat";
    row3.push_back(Eat);

    TgBot::InlineKeyboardButton::Ptr NoEat(new TgBot::InlineKeyboardButton);
    NoEat->text = "Не съедобно";
    NoEat->callbackData = "NoEat";
    row3.push_back(NoEat);

    keyboardEat->inlineKeyboard.push_back(row3);

    if(StringTools::startsWith(query->data, "Free")) {
        bot.getApi().sendMessage(query->message->chat->id, "И последний вопрос, это съедобно или нет?" ,false, 0, keyboardEat, "Markdown");
        return "Free";
    }
    else if(StringTools::startsWith(query->data, "NoMuch")) {
        bot.getApi().sendMessage(query->message->chat->id, "И последний вопрос, это съедобно или нет?" ,false, 0, keyboardEat, "Markdown");
        return "NoMuch";
    }
    else if(StringTools::startsWith(query->data, "Average")) {
        bot.getApi().sendMessage(query->message->chat->id, "И последний вопрос, это съедобно или нет?" ,false, 0, keyboardEat, "Markdown");
        return "Average";
    }

    return "error";
}


std::string TDEatOrNo(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr& query){

    TgBot::InlineKeyboardMarkup::Ptr keyboardEat(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> row3;

    TgBot::InlineKeyboardButton::Ptr Eat(new TgBot::InlineKeyboardButton);
    Eat->text = "Eat";
    Eat->callbackData = "Eat";
    row3.push_back(Eat);
    keyboardEat->inlineKeyboard.push_back(row3);

    TgBot::InlineKeyboardButton::Ptr NoEat(new TgBot::InlineKeyboardButton);
    NoEat->text = "No Eat";
    NoEat->callbackData = "NoEat";
    row3.push_back(NoEat);
    keyboardEat->inlineKeyboard.push_back(row3);

    if(StringTools::startsWith(query->data, "Eat")) {
        return "Eat";
    }
    else if(StringTools::startsWith(query->data, "NoEat")) {
        return "NoEat";
    }

    return "error";
}


bool TDAddPodsk(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr& query){
    bot.getApi().sendMessage(query->message->chat->id, "Теперь напишите текст подсказки");
    return true;
}