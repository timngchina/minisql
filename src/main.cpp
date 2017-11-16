#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "minisql.h"

#include <iostream>
#include <time.h>
#include <string.h>

extern "C"{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

using namespace std;
using namespace rapidjson;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("\tMiniSQL tableName [-i key] [(-nq|-eq) compre key value] [-order key]\n");
        printf("\t-i\tadd index\n");
        printf("\t-nq\tadd a number query compare [=|<|>|<=|>=|!=|in|bt] key value\n");
        printf("\t-sq\tadd a string query compare [=|!=|in] key value\n");
        printf("\t-order\torder by key asc\n");
        return 0;
    }
    RE::MiniSQL* sql;
    bool needOrder = false;
    for (int i = 1; i < argc; ++i)
    {
        if (i == 1)
        {
            char jsonFile[256];
            int n = snprintf(jsonFile, 100, "../../test/t_s_%s.json", argv[1]);
            if (n >= sizeof(jsonFile)) {
                printf("it is to long\n");
            }
            sql = new RE::MiniSQL(jsonFile);
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            sql->genIndex(argv[i + 1]);
            i++;
        }
        else if (strcmp(argv[i], "-nq") == 0)
        {
            char* comp = argv[i + 2];
            char* value = argv[i + 3];
            if (strcmp(comp, "in") == 0)
            {
                double num[10];
                int count = 0;
                char* tempStr = strtok(value, ",");
                while(tempStr != NULL)
                {
                    num[count++] = atof(tempStr);
                    tempStr = strtok(NULL, ",");
                }
                sql->addIn(argv[i + 1], num, count);
            }
            else if (strcmp(comp, "bt") == 0)
            {
                double a = atof(strtok(value, ","));
                double b = atof(strtok(NULL, ","));
                sql->addBetween(argv[i + 1], a, b);
            }
            else
            {
                sql->add(argv[i + 1], comp, atof(value));
            }
            i += 3;
        }
        else if (strcmp(argv[i], "-sq") == 0)
        {
            char* comp = argv[i + 2];
            char* value = argv[i + 3];
            if (strcmp(comp, "in") == 0)
            {
                char* str[10];
                int count = 0;
                char* tempStr = strtok(value, ",");
                while(tempStr != NULL)
                {
                    str[count++] = tempStr;
                    tempStr = strtok(NULL, ",");
                }
                sql->addIn(argv[i + 1], (const char**)str, count);
            }
            else
            {
                sql->add(argv[i + 1], comp, value);
            }
            i += 3;
        }
        else if (strcmp(argv[i], "-order") == 0)
        {
            needOrder = true;
        }

        if (sql != nullptr && sql->checkError())
        {
            printf("error: %s\n", sql->getErrorMessage());
        }
    }
    auto beg = clock();
    int count = sql->query();
    if (needOrder)
    {
        sql->orderByResult("templateId");
    }
    double deltaTime = (clock() - beg) * 1.0 / CLOCKS_PER_SEC;
    if (sql != nullptr && sql->checkError())
    {
        printf("error: %s\n", sql->getErrorMessage());
    }
    printf("result count is %d\n", count);
    printf("use time %f\n", deltaTime);
    auto result = sql->getResult();
    printf("result %lu\n", result.size());
    for (auto it = result.begin(); it != result.end(); ++it)
    {
        printf("%d ", *it);
    }
    return 0;
}
