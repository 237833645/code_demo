#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

#define DATABASE "sqlite.db"

#if 0
SQLITE_API int sqlite3_open(                                                                                                                                                  │ICY Info: StreamTitle='';
  const char *filename,   /* Database filename (UTF-8) */                                                                                                                     │
  sqlite3 **ppDb          /* OUT: SQLite db handle */                                                                                                                         │
); 

SQLITE_API const char *sqlite3_errmsg(sqlite3*);

SQLITE_API int sqlite3_close(sqlite3*);

typedef int (*sqlite3_callback)(void*,int,char**, char**);

SQLITE_API int sqlite3_exec(                                                                                                                                                  │Playing http://lhttp.qingting.fm/live/386/64k.mp3.
  sqlite3*,                                  /* An open database */                                                                                                           │Resolving lhttp.qingting.fm for AF_INET6...
  const char *sql,                           /* SQL to be evaluated */                                                                                                        │
  int (*callback)(void*,int,char**,char**),  /* Callback function */
  void *,                                    /* 1st argument to callback */                                                                                                   │Resolving lhttp.qingting.fm for AF_INET...
  char **errmsg                              /* Error msg written here */                                                                                                     │Connecting to server lhttp.qingting.fm[114.67.126.170]: 80...
); 

SQLITE_API void sqlite3_free(void*);
#endif

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;

   for(i=0; i<argc; i++)
   {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");

   return 0;
}

int main()
{
    int ret = 0;
    sqlite3 *db = NULL;
    char *sql;
    char *zErrMsg = 0;
    const char *data = "Callback function called\n";

/*打开数据库*/
    ret = sqlite3_open(DATABASE, &db);
    if (ret) {
        fprintf(stderr,"--->[Open Database] failed Can't open database:%s\n",sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(0);
    } else {
        printf("--->[Open Database]: success\n");
        //sqlite3_close(db);
    }

/* 创建一个表*/
    sql = "CREATE TABLE COMPANY("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SALARY         REAL );";

    ret = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "--->[Create Sheet] failed SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;                      //错误，返回
    } else {
        fprintf(stdout, "--->[Create Sheet]: success\n");
    }

/*表中插入数据*/
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

    ret = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "--->[Insert]: failed SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;                      //错误，返回
    } else {
       fprintf(stdout, "--->[Insert]: success\n");
    }

/*读取数据*/
    sql = "SELECT * from COMPANY";
    ret  = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "--->[Read]: failed SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    } else {
        fprintf(stdout, "--->[Read]: success\n");
        fprintf(stdout, data);
    }

/*修改数据*/
    sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
            "SELECT * from COMPANY";

    ret = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "--->[Modify]: failed! SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    } else {
        fprintf(stdout, "--->[Modify]: success\n");
    }

#if 1
/*删除数据*/
    sql = "DELETE from COMPANY where ID=2; " \
            "SELECT * from COMPANY";

    ret = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if (ret != SQLITE_OK) {
        fprintf(stderr, "--->[Delete]: failed! SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    } else {
        fprintf(stdout, "--->[Delete]: success\n");
    }
#endif

/*关闭数据库*/    
    sqlite3_close(db);
    fprintf(stdout, "--->[sqlite3_close]: success\n");

    return 0;
}