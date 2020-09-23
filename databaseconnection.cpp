#include "databaseconnection.h"
#include <string.h>

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
      sqlite3_close(m_db);
      std::cout << "Closed database connection" << std::endl;
    }

    int DatabaseConnection::callBack(void *NotUsed, int argc, char **argv, char **azColName) {
      for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
      }
      return 0;
    }


    void DatabaseConnection::runSQL(const std::string& sql) {
      m_rc = sqlite3_exec(m_db, sql.c_str(), &DatabaseConnection::callBack, 0, &m_zErrMsg);
      errorCheck();
    }

    void DatabaseConnection::selectQuery(const std::string& sql) {
      m_rc = sqlite3_exec(m_db, sql.c_str(), &DatabaseConnection::callBack, 0, &m_zErrMsg);
      errorCheck();
    }



    void DatabaseConnection::saveNote(const char* sql_stmt, const char* title, const char* content) {
        sqlite3_stmt *stmt;
        sqlite3_prepare(m_db, sql_stmt, -1, &stmt, 0);
        m_rc = sqlite3_bind_text(stmt, 1, title, strlen(title), SQLITE_STATIC);
        errorCheck(true);
        m_rc = sqlite3_bind_text(stmt, 2, content, strlen(content), SQLITE_STATIC);
        errorCheck(true);
        sqlite3_step(stmt);
        m_rc = sqlite3_reset(stmt);
        errorCheck();
    }

    void DatabaseConnection::errorCheck(bool bind_operation) {
        if (bind_operation == true) {
            if (m_rc) {
              std::cout << "Failed to do the bind operation. Error message: " << sqlite3_errmsg(m_db) << std::endl;
            }
            else {
              std::cout << "Operation successful." << std::endl;
            }
        }
        else {
            if (m_rc) {
              std::cout << "Failed to do the operation. Error message: " << sqlite3_errmsg(m_db) << std::endl;
            }
            else {
              std::cout << "Operation successful." << std::endl;
            }
        }
    }
