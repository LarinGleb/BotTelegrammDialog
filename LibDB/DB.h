#ifndef __DIALOGUE_DB_API_H_INCLUDED__
#define __DIALOGUE_DB_API_H_INCLUDED__

// #include <cppconn/driver.h>
// #include <cppconn/prepared_statement.h>

#include <sstream>
#include <iostream>

#include <jdbc.h>
#include <xdevapi.h>
#include "tgbot/tgbot.h"

namespace db_api {
struct Task {
    std::string text;
    std::string pic_name;
};

class Connector {
  public:
    Connector() = delete;
    Connector(const char* hostname, const char* username, const char* password,
              const char* db_name) {
        try {
            driver_ = get_driver_instance();

            con_ = driver_->connect(hostname, username, password);

            con_->setSchema(db_name);

            stmt_ = con_->createStatement();

        } catch (sql::SQLException& e) {
            std::cerr << "# ERR: SQLException in " << __FILE__;
            std::cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
            std::cerr << "# ERR: " << e.what();
            std::cerr << " (MySQL error code: " << e.getErrorCode();
            std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        } catch (std::exception& ex) {
            std::cerr << "STD EXCEPTION: " << ex.what() << std::endl;
        } catch (const char* ex) {
            std::cerr << "EXCEPTION: " << ex << std::endl;
        }
    }

    ~Connector() {
        delete stmt_;
        delete con_;
    }

    void AddPo(const std::string& AddPodsk, const std::string Sex,const std::string Price, const bool EatOrNo, const TgBot::Message::Ptr& message, TgBot::Bot& bot);
    void KnowPo(const std::string Sex, const std::string Price, const bool EatOrNo, const TgBot::Message::Ptr& message, const TgBot::Bot& bot);

    void AddTown(const std::string CITY);
    void TownDescriptions(const std::string Descr, const std::string CITY);
    void SearchDescriptions(const std::string CITY_, const TgBot::Message::Ptr& message, const TgBot::Bot& bot);
  private:
    sql::Driver*     driver_;
    sql::Connection* con_;
    sql::Statement*  stmt_;
};
}; // namespace db_api

#endif