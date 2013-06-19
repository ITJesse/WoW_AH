// WoW_AH.cpp : 定义控制台应用程
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "./json/json.h"


using namespace std;
using namespace Json;    //json的命名空间



int main()
{
    /*JSON DATA as following:            //一个json类型的数据    
    {
        "test : 5
    }*/

    string test = "{\"test\" : 5}";        //保存上文的json类型的数据
                  
    //以下涉及json的操作，将在后文中涉及，此处为简单应用，不解释，你懂的
    Reader reader;
    Value value;

    if (reader.parse(test, value))
    {
        int i = 0;

        if (!value["test"].isNull())
        {
            i = value["test"].asInt();
            cout << i << endl;
        }
    }
    return 0;
}