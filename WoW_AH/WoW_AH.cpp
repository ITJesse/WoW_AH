// WoW_AH.cpp : 定义控制台应用程
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <winsock.h>
#include <windows.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib");
#include "./json/json.h"

#define MAXBLOCKSIZE 1024

using namespace std;
using namespace Json;    //json的命名空间


//下载文件并保存为新文件名
void DownloadSaveFiles(const char *Url,const char *save_as)/*将Url指向的地址的文件下载到save_as指向的本地文件*/
{
  byte Temp[MAXBLOCKSIZE];
   ULONG Number = 1;

   FILE *stream;
   HINTERNET hSession = InternetOpen((LPCWSTR)"RookIE/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
 if (hSession != NULL)
 {
  HINTERNET handle2 = InternetOpenUrl(hSession, (LPCWSTR)Url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
  if (handle2 != NULL)
  {
  
  
   if( (stream = fopen( save_as, "wb" )) != NULL )
   {
    while (Number > 0)
    {
     InternetReadFile(handle2, Temp, MAXBLOCKSIZE - 1, &Number);
     
     fwrite(Temp, sizeof (char), Number , stream);
    }
    fclose( stream );
   }
   
   InternetCloseHandle(handle2);
   handle2 = NULL;
  }
  InternetCloseHandle(hSession);
  hSession = NULL;
 }
}

int main()
{
    /*JSON DATA as following:            //一个json类型的数据    
    {
        "test : 5
    }*/
	DownloadSaveFiles("http://www.battlenet.com.cn/api/wow/auction/data/%E5%86%AC%E6%8B%A5%E6%B9%96","./tmp.json");
    string test;
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