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
// 0 = ��ɫ 8 = ��ɫ
//1 = ��ɫ 9 = ����ɫ
//2 = ��ɫ 10 = ����ɫ
//3 = ǳ��ɫ 11 = ��ǳ��ɫ
//4 = ��ɫ 12 = ����ɫ
//5 = ��ɫ 13 = ����ɫ
//6 = ��ɫ 14 = ����ɫ
//7 = ��ɫ 15 = ����ɫ

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

bool getProcess(const char *procressName)                //�˺��������������ִ�Сд
{
    char pName[MAX_PATH];                                //��PROCESSENTRY32�ṹ���е�szExeFile�ַ����鱣��һ�£����ڱȽ�
    strcpy(pName,procressName);                            //��������
    CharLowerBuff(pName,MAX_PATH);                        //������ת��ΪСд
    PROCESSENTRY32 currentProcess;                        //��ſ��ս�����Ϣ��һ���ṹ��
    currentProcess.dwSize = sizeof(currentProcess);        //��ʹ������ṹ֮ǰ�����������Ĵ�С
    HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//��ϵͳ�ڵ����н�����һ������

    if (hProcess == INVALID_HANDLE_VALUE)
    {
        printf("CreateToolhelp32Snapshot()����ʧ��!\n");
        return false;
    }

    bool bMore=Process32First(hProcess,&currentProcess);        //��ȡ��һ��������Ϣ
    while(bMore)
    {
        CharLowerBuff(currentProcess.szExeFile,MAX_PATH);        //��������ת��ΪСд
        if (strcmp(currentProcess.szExeFile,pName)==0)            //�Ƚ��Ƿ���ڴ˽���
        {
            CloseHandle(hProcess);                                //���hProcess���
            return true;
        }
        bMore=Process32Next(hProcess,&currentProcess);            //������һ��
    }

    CloseHandle(hProcess);    //���hProcess���
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