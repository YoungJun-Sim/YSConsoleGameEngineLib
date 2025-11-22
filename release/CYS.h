#pragma once


#include<iostream>
#include<vector>
#include<string>
#include <tchar.h>
#include <conio.h>
#include <strsafe.h>
#include<windows.h>
#include<errhandlingapi.h>
#include <io.h>
#include <fcntl.h> 
#include <fstream> // 파일 입출력
#include <locale>  // 로케일 설정
#include <codecvt> // UTF-8 <-> wstring 변환
class Screen {
private: 
	short width;
	short height;
	std::vector<std::wstring> buffer;
	HANDLE hScreen[2];
	int screenIndex;
	int k = 0;
public:
	Screen();
	~Screen();
	void setFont(int sizeX, int sizeY, const wchar_t* fontName);
	short getWindowX();
	short getWindowY();
	void release();
	void resetBuffer();
	void Display();
	void Draw(int x, int y, const std::vector<std::wstring>& sprite);
	void setTitle(std::string title);
	void setWindowSize(short Width, short Height);
	void disableResize();
	void enableResize();
	void printMaxallowed();
	short getMaxY();
	short getMaxX();
	void gotoxy(int x, int y);
	void write(int x, int y, std::wstring str);
};

class Asset {
private:
	int x = 0, y = 0;
	//Screen mScreen;
public:
	std::vector<std::wstring> sprite;
	Asset();
	Asset(int X,int Y);
	void Load(std::string link);
	void SetSprite(const std::vector<std::wstring>& temp);
	void Draw(Screen* screen);
	void setX(int n);
	void setY(int n);
	short getX(int n);
	short getY(int n);
};


class CYS
{
public:
	void CYScon() { std::wcout << "CYS.h is connected"; }
};

