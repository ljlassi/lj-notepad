#include "databaseconnection.h"

    void DatabaseConnection::connectToDB() {
      m_rc = sqlite3_open(DB_NAME, &m_db);
      if (m_rc) {
        std::cout << "Failed to open database connection" << sqlite3_errmsg(m_db) << std::endl;
      }
      else {
        std::cout << "Opened database connection succesfully" << std::endl;
      }
    }

    void DatabaseConnection::closeDBConnection() {
      m_rc = sqlite3_close(m_db);
      if (m_rc) {
        std::cout << "Possibly failed to close database connection." << std::endl;
      }
      else {
        std::cout << "Closed database connection succesfully." << std::endl;
      }
    }

    int DatabaseConnection::callBack(void *NotUsed, int argc, char **argv, char **azColName) {
      for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
      }
      return 0;
    }


    void DatabaseConnection::runSQL(const std::string& sql) {
      m_rc = sqlite3_exec(m_db, sql.c_str(), &DatabaseConnection::callBack, 0, &m_zErrMsg);
      if (m_rc) {
        std::cout << "Failed to do the operation. Error message: " << sqlite3_errmsg(m_db) << std::endl;
      }
      else {
        std::cout << "Operation successful." << std::endl;
      }
    }

    void DatabaseConnection::selectQuery(const std::string& sql) {
      m_rc = sqlite3_exec(m_db, sql.c_str(), &DatabaseConnection::callBack, 0, &m_zErrMsg);
      if (m_rc) {
        std::cout << "Failed to do the operation. Error message: " << sqlite3_errmsg(m_db) << std::endl;
      }
      else {
        std::cout << "Operation successful." << std::endl;
      }
    }
