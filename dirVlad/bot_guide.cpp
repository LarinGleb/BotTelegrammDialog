#include "tgbot/tgbot.h"
#include <stdio.h>
#include "bot_guide.h"

using namespace std;
using namespace TgBot;

void ButtonTOWN(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr query)
{

    InlineKeyboardMarkup::Ptr keyboard2(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> rowCHOICE2;
    InlineKeyboardButton::Ptr checkButtonEND(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr checkButtonOtherTown(new InlineKeyboardButton);
    checkButtonEND->text = "Перейтинаначало";
    checkButtonEND->callbackData = "DEFAULT";
    checkButtonOtherTown->text = "Другойгород";
    checkButtonOtherTown->callbackData = "OtherTown";
    rowCHOICE2.push_back(checkButtonEND);
    rowCHOICE2.push_back(checkButtonOtherTown);
    keyboard2->inlineKeyboard.push_back(rowCHOICE2);
    bot.getApi().sendMessage(query->message->chat->id, "Перейти в начало, либо назвать другой город", false, 0, keyboard2);
    

}



void ButtonEND(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr query)
{
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> rowCHOICE;
    InlineKeyboardButton::Ptr checkButtonTOWN(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr checkButtonMAINSIGHTS(new InlineKeyboardButton);
    checkButtonTOWN->text = "1";
    checkButtonTOWN->callbackData = "Choice...TOwn";
    checkButtonMAINSIGHTS->text = "2";
    checkButtonMAINSIGHTS->callbackData = "mainsights";
    rowCHOICE.push_back(checkButtonTOWN);
    rowCHOICE.push_back(checkButtonMAINSIGHTS);
    keyboard->inlineKeyboard.push_back(rowCHOICE);

    
    bot.getApi().sendMessage(query->message->chat->id, "Привет, я бот-гид. Я могу показать тебе разные достопримечательности России. Чтобы узнать о главных достопримечательностей какого-то города, нажми 1, а если ты турист и не знаешь что посетить, то нажми 2", false, 0, keyboard);
}





void ButtonMAINSIGHTS(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr query) 
{
    InlineKeyboardMarkup::Ptr keyboard3(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> rowCHOICE3;
    InlineKeyboardButton::Ptr checkButtonEND(new InlineKeyboardButton);
    checkButtonEND->text = "Перейтинаначало";
    checkButtonEND->callbackData = "DEFAULT";
    rowCHOICE3.push_back(checkButtonEND);
    keyboard3->inlineKeyboard.push_back(rowCHOICE3);
    bot.getApi().sendMessage(query->message->chat->id, "Ха-ха затролил тебя, скоро все основные достопримечательности будут");

    //Вывод главных достопримечательностей

    bot.getApi().sendMessage(query->message->chat->id, "перейти в начало", false, 0, keyboard3);
}





void ButtonOtherTown(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr query)
{
    InlineKeyboardMarkup::Ptr keyboard2(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> rowCHOICE2;
    InlineKeyboardButton::Ptr checkButtonEND(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr checkButtonOtherTown(new InlineKeyboardButton);
    checkButtonEND->text = "Перейтинаначало";
    checkButtonEND->callbackData = "DEFAULT";
    checkButtonOtherTown->text = "Другойгород";
    checkButtonOtherTown->callbackData = "OtherTown";
    rowCHOICE2.push_back(checkButtonEND);
    rowCHOICE2.push_back(checkButtonOtherTown);
    keyboard2->inlineKeyboard.push_back(rowCHOICE2);
        //обратиться к базе данных
    bot.getApi().sendMessage(query->message->chat->id, "Перейти в начало, либо назвать другой город", false, 0, keyboard2);
}