#pragma comment(lib, "urlmon.lib")
#include <bits/stdc++.h>>
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <tlhelp32.h>
#include <thread>
#include <chrono>

std::string generateRandomString(size_t length);
std::string generateRandomPass(size_t length);
std::string generateRandomNumber(size_t length);
long long random_number(int min, int max);
//std::wstring string_to_wstring(std::string text);
//LPCWSTR ToLPCWSTR(std::string s);
void SetTitle(std::string s);
void srand_set();
char* to_charstar(std::string str);
void Colorcout(const char* s, int color);
bool replace(std::string& str, const std::string& from, const std::string& to);
bool del(std::string& str, const std::string& from);
void eraseLines(int count); // Not Very efficient
bool getProcess(const char *procressName);
void Runinbackground();


std::string generateRandomString(size_t length)
{
  const char *charmap = "ABCDEFGHIJKLMNOPQRSTUVWXYZqwertyuiopasdfghjklzxcvbnm1234567890";
  const size_t charmapLength = strlen(charmap);
  auto generator = [&]()
  { return charmap[rand() % charmapLength]; };
  std::string result;
  result.reserve(length);
  generate_n(back_inserter(result), length, generator);
  return result;
}
std::string generateRandomPass(size_t length){
  const char *charmap = "ABCDEFGHIJKLMNOPQRSTUVWXYZqwertyuiopasdfghjklzxcvbnm1234567890$*&#!";
  const size_t charmapLength = strlen(charmap);
  auto generator = [&]()
  { return charmap[rand() % charmapLength]; };
  std::string result;
  result.reserve(length);
  generate_n(back_inserter(result), length, generator);
  return result;
}

std::string generateRandomNumber(size_t length){
  const char *charmap = "1234567890";
  const size_t charmapLength = strlen(charmap);
  auto generator = [&]()
  { return charmap[rand() % charmapLength]; };
  std::string result;
  result.reserve(length);
  generate_n(back_inserter(result), length, generator);
  return result;
}

long long random_number(int min, int max){
  int num;
  while (true)
  {
    num = rand();
    if (num >= min && num <= max)
      return num;
  }
}

 /* std::wstring string_to_wstring(std::string text) {
  std::wstring temp = std::wstring(text.begin(), text.end());
  return temp;
}

LPCWSTR ToLPCWSTR(std::string s){
  return string_to_wstring(s).c_str();
} */  

void SetTitle(std::string s)
{
  SetConsoleTitleA(to_charstar(s));
}

void srand_set()
{
  srand((unsigned int)time(NULL));
}

char* to_charstar(std::string str)
{
  char* p = (char *)str.c_str();
  return p;
}

void Colorcout(const char* s, int color)
{
    
 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
 printf(s);
 SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}
// 0 = 黑色 8 = 灰色
//1 = 蓝色 9 = 淡蓝色
//2 = 绿色 10 = 淡绿色
//3 = 浅绿色 11 = 淡浅绿色
//4 = 红色 12 = 淡红色
//5 = 紫色 13 = 淡紫色
//6 = 黄色 14 = 淡黄色
//7 = 白色 15 = 亮白色

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

bool del(std::string& str, const std::string& from) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.erase(start_pos, from.length());
    return true;
}

void eraseLines(int count) {
    if (count > 0) {
        std::cout << "\x1b[2K"; // Delete current line
        // i=1 because we included the first line
        for (int i = 1; i < count; i++) {
            std::cout
            << "\x1b[1A" // Move cursor up one
            << "\x1b[2K"; // Delete the entire line
        }
        std::cout << "\r"; // Resume the cursor at beginning of line
    }
}

bool getProcess(const char *procressName)                //此函数进程名不区分大小写
{
    char pName[MAX_PATH];                                //和PROCESSENTRY32结构体中的szExeFile字符数组保持一致，便于比较
    strcpy(pName,procressName);                            //拷贝数组
    CharLowerBuff(pName,MAX_PATH);                        //将名称转换为小写
    PROCESSENTRY32 currentProcess;                        //存放快照进程信息的一个结构体
    currentProcess.dwSize = sizeof(currentProcess);        //在使用这个结构之前，先设置它的大小
    HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//给系统内的所有进程拍一个快照

    if (hProcess == INVALID_HANDLE_VALUE)
    {
        printf("CreateToolhelp32Snapshot()调用失败!\n");
        return false;
    }

    bool bMore=Process32First(hProcess,&currentProcess);        //获取第一个进程信息
    while(bMore)
    {
        CharLowerBuff(currentProcess.szExeFile,MAX_PATH);        //将进程名转换为小写
        if (strcmp(currentProcess.szExeFile,pName)==0)            //比较是否存在此进程
        {
            CloseHandle(hProcess);                                //清除hProcess句柄
            return true;
        }
        bMore=Process32Next(hProcess,&currentProcess);            //遍历下一个
    }

    CloseHandle(hProcess);    //清除hProcess句柄
    return false;
}

void Runinbackground() {
  HWND window;
  AllocConsole();
  window = FindWindowA("ConsoleWindowClass", NULL);
  ShowWindow(window, 0);
}

/*

void DownloadFile(char* DownloadURL, char* SavePath){
  URLDownloadToFile
}

*/