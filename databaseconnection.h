#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <iostream>
#include <string>
#include <sqlite3.h>
#include <QString>
#define DB_NAME "ljnotepad.db"

class DatabaseConnection {
private:
    int m_rc; // Stores SQLite3 error status
    char *m_zErrMsg; // Stores the error message.
    sqlite3 *m_db; // SQLite3 database connection object
    void errorCheck(bool bind_operation = false);

public:
  static QString m_displayable_result;
  void connectToDB();
  void closeDBConnection();
  static int callBack(void*, int, char**, char**);
  void runSQL(const std::string& sql);
  void selectQuery(const std::string& sql);
  void saveNote(const char* sql_stmt, const char* title, const char* content);
};

#endif // DATABASECONNECTION_H
