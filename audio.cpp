#include <stdio.h>
#include "audio.h"
#pragma comment(lib, "winmm.lib")

#define NOMINMAX
#include <Windows.h>


void weaponSound(std::string weapon, std::string state) {

	if (state == "start") {
		if (weapon == "Fists") {
			mciSendString(TEXT("open \"audio\\fist.mp3\" type mpegvideo alias fistAttack"), NULL, 0, NULL);
			mciSendString(TEXT("play fistAttack"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio fistAttack volume to 100"), NULL, 0, NULL);
		}
		else if (weapon == "Sword") {

		}
		else if (weapon == "Axe") {

		}
		else if (weapon == "Crowwbow") {

		}
	}
	else if (state == "close") {
		if (weapon == "Fists") {
			mciSendString(TEXT("close fistAttack"), NULL, 0, NULL);
		}
		else if (weapon == "Sword") {

		}
		else if (weapon == "Axe") {

		}
		else if (weapon == "Crowwbow") {

		}
	}
	
}