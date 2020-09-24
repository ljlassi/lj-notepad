#include "databaseconnection.h"
#include <string.h>

    /**
     * @brief DatabaseConnection::connectToDB
     * Connect to SQLite3 database.
     *
     */

    QString DatabaseConnection::m_displayable_result = "Previous Notes: \n";

    void DatabaseConnection::connectToDB() {
      m_rc = sqlite3_open(DB_NAME, &m_db);
      if (m_rc) {
        std::cout << "Failed to open database connection" << sqlite3_errmsg(m_db) << std::endl;
      }
      else {
        std::cout << "Opened database connection succesfully" << std::endl;
      }
    }

    /**
     * @brief DatabaseConnection::closeDBConnection
     * Close SQLite3 database connection.
     */

    void DatabaseConnection::closeDBConnection() {
      sqlite3_close(m_db);
      std::cout << "Closed database connection" << std::endl;
    }

    /**
     * @brief DatabaseConnection::callBack
     * Acts as a callback function for SQLite3 C++ interface SQL queries.
     * @param NotUsed
     * @param argc
     * @param argv
     * @param azColName
     * @return
     */

    int DatabaseConnection::callBack(void *NotUsed, int argc, char **argv, char **azColName) {
      for (int i = 0; i < argc; i++) {
        DatabaseConnection::m_displayable_result = DatabaseConnection::m_displayable_result + azColName[i] + ": " + argv[i] + "\n";
      }
      return 0;
    }

    /**
     * @brief DatabaseConnection::runSQL
     * Run a generic SQL query. Used for e.g. table creation.
     * @param sql
     */

    void DatabaseConnection::runSQL(const std::string& sql) {
      m_rc = sqlite3_exec(m_db, sql.c_str(), &DatabaseConnection::callBack, 0, &m_zErrMsg);
      errorCheck();
    }

    /**
     * @brief DatabaseConnection::selectQuery
     * Run a SELECT query. To be expanded.
     * @param sql
     */

    void DatabaseConnection::selectQuery(const std::string& sql) {
      m_rc = sqlite3_exec(m_db, sql.c_str(), &DatabaseConnection::callBack, 0, &m_zErrMsg);
      errorCheck();
    }


    /**
     * @brief DatabaseConnection::saveNote
     * Save a LJNotepad note to the database.
     * @param sql_stmt
     * @param title
     * @param content
     */

    void DatabaseConnection::saveNote(const char* sql_stmt, const char* title, const char* content) {
        sqlite3_stmt *stmt;
        sqlite3_prepare(m_db, sql_stmt, -1, &stmt, 0);
        m_rc = sqlite3_bind_text(stmt, 1, title, strlen(title), SQLITE_TRANSIENT);
        errorCheck(true);
        m_rc = sqlite3_bind_text(stmt, 2, content, strlen(content), SQLITE_TRANSIENT);
        errorCheck(true);
        sqlite3_step(stmt);
        m_rc = sqlite3_reset(stmt);
        errorCheck();
    }

    /**
     * @brief DatabaseConnection::errorCheck
     * Check for errors, this is called after a sqlite3 operation that returns the value to m_rc class member variable.
     * Set true as the argument if this is a bind operation, for customized error and success messages.
     * @param bind_operation
     */

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
