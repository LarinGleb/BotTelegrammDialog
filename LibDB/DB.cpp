#include "DB.h"
#include "tgbot/tgbot.h"

namespace db_api {

    void Connector::AddPo(const std::string& AddPodsk, const std::string Sex,const std::string Price, const bool EatOrNo, const TgBot::Message::Ptr& message, TgBot::Bot& bot){
        std::stringstream sql_request;
        sql_request.str("");
        sql_request << "INSERT INTO rpnac5.ForTD (podsk, sex, price, eat) VALUES (\"" << AddPodsk.c_str()
                    << "\", \"" << Sex.c_str() << "\", \""  << Price.c_str() << "\", " << EatOrNo << ')';

        std::cout << sql_request.str() << "\n";
        stmt_->execute(sql_request.str().c_str());

        bot.getApi().sendMessage(message->chat->id, "Спасибо! подсказка добавленна.");

    }

    void Connector::KnowPo(const std::string Sex, const std::string Price, const bool EatOrNo, const TgBot::Message::Ptr& message, const TgBot::Bot& bot){
        std::stringstream sql_request;
        bool flag = true;

        //SELECT podsk FROM rpnac5.ForTD WHERE sex = "All" AND price = "Free" AND eat = 0;


        sql_request << "SELECT podsk FROM rpnac5.ForTD WHERE sex = \""
                    << Sex.c_str() << "\" AND price = \"" << Price.c_str() << "\" AND eat = " << EatOrNo; 

        sql::ResultSet* res = stmt_->executeQuery(sql_request.str().c_str());

        std::string count;
        while (res->next()) {
            flag = false;
            count = res->getString(1);
            bot.getApi().sendMessage(message->chat->id, count);
        }
        if (flag){
            bot.getApi().sendMessage(message->chat->id, "Извините, но по данным параметрам подсказок пока нет. "
            "Вы можете посмотреть другие или зайти позже, "
            "бот постоянно обновляется и добавляются новые подсказкию");
        }

        delete (res);

        }

    }