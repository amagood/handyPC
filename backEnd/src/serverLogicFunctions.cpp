#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <iostream>
#include "json.hpp"

std::vector<std::vector<std::string>> output;
std::vector<std::string> colName;
std::vector<std::string> tmp;

using json = nlohmann::json;

static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    //fprintf(stderr, "%s: ", (const char*)data);
    for(i=0; i<argc; i++){
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        tmp.emplace_back(argv[i] ? argv[i] : "NULL");
        colName.emplace_back(azColName[i]);
    }
    output.emplace_back(tmp);
    tmp.clear();
    //printf("\n");
    return 0;
}

bool isAllDigit(std::string in)
{
    for(int i = 0;i < in.size();i ++)
    {
        if(!isdigit(in[i])) return false;
    }
    return true;
}

json vector_to_json(std::vector<std::vector<std::string>> in, std::vector<std::string> col)
{
    json out;
    if(in.size() == 0) return out;
    for(int i = 0;i < in[0].size();i ++)
    {
        if(in.size() == 1)
        {
            if(isAllDigit(in[0][i])) out[col[i]] = std::stoi(in[0][i]);
            else
            {
                if(in[0][i] != "NULL") out[col[i]] = in[0][i];
                else out[col[i]] = nullptr;
            }
        }
        else
        {
            std::vector<int> js;
            for(int j = 0;j < in.size();j ++)
            {
                int a = 0;
                if(isdigit(in[j][i].c_str()[0]))
                {
                    js.emplace_back(std::stoi(in[j][i]));
                }
            }
            out[col[i]] = js;
        }
    }
    return out;
}

void vector_output(std::vector<std::vector<std::string>> in, std::vector<std::string> col)
{
    if(in.size() != 0)
    {
        for(int j = 0; j < in[0].size(); j ++)
        {
            std::cout << col[j] << " ";
        }
        printf("\n");
        for(int i = 0; i < in.size(); i ++)
        {
            for(int j = 0; j < in[0].size(); j ++)
            {
                std::cout << in[i][j] << " ";
            }
            printf("\n");
        }
    }
}

json getProductById(int id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[100];
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("HandyPC.db", &db);
    if( rc )
    {
        //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else
    {
        //fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    //sql = "SELECT * from Product WHERE ID = %d";
    sprintf(sql,"SELECT * FROM Product WHERE ID = %d;",id);

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        //fprintf(stdout, "Operation done successfully\n");
    }
    json result;
    result = vector_to_json(output,colName);
    //vector_output(output,colName)
    sqlite3_close(db);
    output.clear();
    colName.clear();
    tmp.clear();

    return result;
}

json getProductDetailsById(int id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[100];
    const char* data = "Callback function called";
    std::vector<std::string> subclass;
    subclass.emplace_back("ProductCPU");
    subclass.emplace_back("ProductGPU");
    subclass.emplace_back("ProductRAM");

    /* Open database */
    rc = sqlite3_open("HandyPC.db", &db);
    if( rc )
    {
        //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else
    {
        //fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    //sql = "SELECT * from Product WHERE ID = %d";
    for(int i = 0; i < subclass.size(); i ++)
    {
        sprintf(sql,"SELECT * FROM %s WHERE Product_ID = %d;",subclass[i].c_str(),id);
        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
        if(output.size() != 0) break;
        output.clear();
        colName.clear();
        tmp.clear();
    }


    if( rc != SQLITE_OK )
    {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        //fprintf(stdout, "Operation done successfully\n");
    }
    json result;
    result = vector_to_json(output,colName);
    //vector_output(output,colName);
    sqlite3_close(db);
    output.clear();
    colName.clear();
    tmp.clear();

    return result;
}

json getCategoryById(int id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[500];
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("HandyPC.db", &db);
    if( rc )
    {
        //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else
    {
        //fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    //sql = "SELECT * from Product WHERE ID = %d";
    sprintf(sql,"SELECT * FROM Category WHERE ID = %d;",id);

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        //fprintf(stdout, "Operation done successfully\n");
    }
    json result;
    result = vector_to_json(output,colName);
    output.clear();
    colName.clear();
    tmp.clear();

    sprintf(sql,"SELECT Product_ID FROM Include WHERE EXISTS(SELECT Name FROM Model WHERE Name = Model_Name AND Category_ID = %d);",id);
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        //fprintf(stdout, "Operation done successfully\n");
    }
    std::vector<int> ids;
    for(int i = 0;i < output.size();i ++)
    {
        int a = 0;
        if(isdigit(output[i][0].c_str()[0]))
        {
            a = std::stoi(output[i][0]);
        }
        ids.emplace_back(a);
    }
    result["AllProductID"] = ids;
    //vector_output(output,colName);
    sqlite3_close(db);
    output.clear();
    colName.clear();
    tmp.clear();

    return result;
}

json getEvaluationById(int id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[100];
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("HandyPC.db", &db);
    if( rc )
    {
        //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else
    {
        //fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sprintf(sql,"SELECT * FROM ProductList WHERE ID = %d;",id);
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK )
    {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    if(!output.empty())
    {
        output.clear();
        colName.clear();
        tmp.clear();
        sprintf(sql,"SELECT Product_ID FROM Contain WHERE ProductList_ID = %d;",id);

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

        if( rc != SQLITE_OK )
        {
            //fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        else
        {
            //fprintf(stdout, "Operation done successfully\n");
        }
    }
    //sql = "SELECT * from Product WHERE ID = %d";

    json result;
    result = vector_to_json(output,colName);
    //vector_output(output,colName);
    sqlite3_close(db);
    output.clear();
    colName.clear();
    tmp.clear();

    return result;
}

int createEvaluationByIds(std::vector<int> productIds)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[500];
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("HandyPC.db", &db);
    if( rc )
    {
        //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else
    {
        //fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sprintf(sql,"INSERT INTO ProductList(Total_Price, Product_Count) VALUES(0,0);");
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if(rc != SQLITE_OK) return -1;

    int id = sqlite3_last_insert_rowid(db);

    //int id = 0;
    //sprintf(sql,"SELECT last_insert_rowid();");
    //rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    printf("%d\n",id);
    for(int i = 0;i < productIds.size();i ++)
    {
        sprintf(sql,"INSERT INTO Contain(Product_ID,ProductList_ID) VALUES(%d, %d)",productIds[i],id);
        rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
        if(rc != SQLITE_OK) return -1;
    }
    if( rc != SQLITE_OK )
    {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        //fprintf(stdout, "Operation done successfully\n");
    }
    //json result;
    //result = vector_to_json(output,colName);
    //vector_output(output,colName);
    sqlite3_close(db);
    output.clear();
    colName.clear();
    tmp.clear();

    return id;
}  //returns id of the new evaluation (< 0 if anything went wrong)

bool deleteEvaluationById(int id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[500];
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("HandyPC.db", &db);
    if( rc )
    {
        //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else
    {
        //fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sprintf(sql,"DELETE FROM ProductList WHERE ID = %d;",id);
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK )
    {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }

    sprintf(sql,"DELETE FROM Contain WHERE ProductList_ID = %d;",id);
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK )
    {
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }
    //json result;
    //result = vector_to_json(output,colName);
    //vector_output(output,colName);
    sqlite3_close(db);
    output.clear();
    colName.clear();
    tmp.clear();

    return true;
}  //false if failed

json getAllCategories()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[100];
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("HandyPC.db", &db);
    if( rc )
    {
        //fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else
    {
        //fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    //sql = "SELECT * from Product WHERE ID = %d";
    sprintf(sql,"SELECT ID FROM Category;");

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        //fprintf(stdout, "Operation done successfully\n");
    }
    json result;
    result = vector_to_json(output,colName);
    //vector_output(output,colName)
    sqlite3_close(db);
    output.clear();
    colName.clear();
    tmp.clear();

    return result;
}