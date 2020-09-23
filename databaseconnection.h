#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <iostream>
#include <string>
#include <sqlite3.h>
#define DB_NAME "ljnotepad.db"

class DatabaseConnection {
private:
  int m_rc;
  char *m_zErrMsg;
  sqlite3 *m_db;

public:
  void connectToDB();
  void closeDBConnection();
  static int callBack(void*, int, char**, char**);
  void runSQL(const std::string& sql);
  void selectQuery(const std::string& sql);
  void saveNote(const char* sql_stmt, const char* title, const char* content);
};

#endif // DATABASECONNECTION_H
