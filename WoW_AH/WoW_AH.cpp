// WoW_AH.cpp : 定义控制台应用程
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <wchar.h>
#include <Windows.h>
#include <comdef.h>
#include "./json/json.h"



using namespace std;
using namespace Json;    //json的命名空间

std::string UTF8_to_ANSI (const char* szUTF8)
{
    if (szUTF8 == NULL)
        return "" ;
    
    int     nLen = ::MultiByteToWideChar (CP_UTF8, 0, szUTF8, -1, NULL, 0) ;
    WCHAR   * pWstr = new WCHAR[nLen+1] ;
    ZeroMemory (pWstr, sizeof(WCHAR) * (nLen+1)) ;
    ::MultiByteToWideChar (CP_UTF8, 0, szUTF8, -1, pWstr, nLen) ;
    std::string     strAnsi (_bstr_t((wchar_t*)pWstr)) ;
    delete[] pWstr ;
    return strAnsi ;
}

int decode_json_url(const char* filename)
{
	ifstream ifs;
	ifs.open(filename,ios::binary|ios::in);
    Reader reader;
    Value value;
    if (reader.parse(ifs, value))
	{
		Value files = value["files"]; 
		for(unsigned int i = 0;i < files.size(); i++)
		{
			if(!files[i].isMember("url"))  
			continue; 
			std::string out= files[i]["url"].asString();
			cout << out; 
			if(i != (files.size() - 1)) 
				cout << endl;  
		}
    }
	return 0;
}

int decode_json_data(const char* filename)
{
	ifstream ifs;
	ifs.open(filename);
    Reader reader;
    Value value;
    if (reader.parse(ifs, value))
	{
		Value data = value["horde"]["auctions"]; 
		for(unsigned int i = 0;i < data.size(); i++)
		{
			if(!data[i].isMember("owner"))  
			continue; 
			if(UTF8_to_ANSI(data[i]["owner"].asCString())=="光明铭文专卖")
			{
				std::string out= UTF8_to_ANSI(data[i]["owner"].asCString());
				cout << out;
			}
			if(i != (data.size() - 1)) 
				cout << endl;  
		}
    }
	return 0;
}

int get_url()
{
		system("curl.exe -o tmp.json http://www.battlenet.com.cn/api/wow/auction/data/%E5%86%AC%E6%8B%A5%E6%B9%96");
		decode_json_url("tmp.json");
		system("cls");
		decode_json_data("auctions.json");
		return 0;
}

int main()
{
    /*JSON DATA as following:            //一个json类型的数据    
    {
        "test : 5
    }*/
	if(!get_url())
	{
		system("pause");
	}

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