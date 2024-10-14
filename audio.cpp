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
			mciSendString(TEXT("open \"audio\\sword.mp3\" type mpegvideo alias swordAttack"), NULL, 0, NULL);
			mciSendString(TEXT("play swordAttack"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio swordAttack volume to 100"), NULL, 0, NULL);
		}
		else if (weapon == "Axe") {
			mciSendString(TEXT("open \"audio\\axe.mp3\" type mpegvideo alias axeAttack"), NULL, 0, NULL);
			mciSendString(TEXT("play axeAttack"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio axeAttack volume to 100"), NULL, 0, NULL);
		}
		else if (weapon == "Crossbow") {
			mciSendString(TEXT("open \"audio\\crossbow.mp3\" type mpegvideo alias crossbowAttack"), NULL, 0, NULL);
			mciSendString(TEXT("play crossbowAttack"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio crossbowAttack volume to 100"), NULL, 0, NULL);
		}
	}
	else if (state == "close") {
		if (weapon == "Fists") {
			mciSendString(TEXT("close fistAttack"), NULL, 0, NULL);
		}
		else if (weapon == "Sword") {
			mciSendString(TEXT("close swordAttack"), NULL, 0, NULL);
		}
		else if (weapon == "Axe") {
			mciSendString(TEXT("close axeAttack"), NULL, 0, NULL);
		}
		else if (weapon == "Crossbow") {
			mciSendString(TEXT("close crossbowAttack"), NULL, 0, NULL);
		}
	}
	
}

void magicSound(std::string magic, std::string state) {

	if (state == "start") {
		if (magic == "Fireball") {
			mciSendString(TEXT("open \"audio\\fireSpell.mp3\" type mpegvideo alias fireAttack"), NULL, 0, NULL);
			mciSendString(TEXT("play fireAttack"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio fireAttack volume to 100"), NULL, 0, NULL);
		}
		else if (magic == "Lightning") {
			mciSendString(TEXT("open \"audio\\lightningSpell.mp3\" type mpegvideo alias lightningAttack"), NULL, 0, NULL);
			mciSendString(TEXT("play lightningAttack"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio lightningAttack volume to 100"), NULL, 0, NULL);
		}
		else if (magic == "IceStorm") {
			mciSendString(TEXT("open \"audio\\iceSpell.mp3\" type mpegvideo alias iceAttack"), NULL, 0, NULL);
			mciSendString(TEXT("play iceAttack"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio iceAttack volume to 100"), NULL, 0, NULL);
		}
	}
	else if (state == "close") {
		if (magic == "Fireball") {
			mciSendString(TEXT("close fireAttack"), NULL, 0, NULL);
		}
		else if (magic == "Lightning") {
			mciSendString(TEXT("close lightningAttack"), NULL, 0, NULL);
		}
		else if (magic == "IceStorm") {
			mciSendString(TEXT("close iceAttack"), NULL, 0, NULL);
		}
	}

}

void itemSound(std::string item, std::string state) {

	if (state == "start") {
		if (item == "Vitality-Potion") {
			mciSendString(TEXT("open \"audio\\potionUse.mp3\" type mpegvideo alias healthPotion"), NULL, 0, NULL);
			mciSendString(TEXT("play healthPotion"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio healthPotion volume to 500"), NULL, 0, NULL);
		}
		else if (item == "Throwing-Knives") {
			mciSendString(TEXT("open \"audio\\knifeUse.mp3\" type mpegvideo alias knife"), NULL, 0, NULL);
			mciSendString(TEXT("play knife"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio knife volume to 500"), NULL, 0, NULL);
		}
		else if (item == "Smokebomb") {
			mciSendString(TEXT("open \"audio\\smokebombUse.mp3\" type mpegvideo alias smoke"), NULL, 0, NULL);
			mciSendString(TEXT("play smoke"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio smoke volume to 350"), NULL, 0, NULL);
		}
	}
	else if (state == "close") {
		if (item == "Vitality-Potion") {
			mciSendString(TEXT("close healthPotion"), NULL, 0, NULL);
		}
		else if (item == "Throwing-Knives") {
			mciSendString(TEXT("close knife"), NULL, 0, NULL);
		}
		else if (item == "Smokebomb") {
			mciSendString(TEXT("close smoke"), NULL, 0, NULL);
		}
	}
}

void enemySound(std::string enemy, std::string state) {
	if (state == "start") {
		if (enemy == "Goblin") {
			mciSendString(TEXT("open \"audio\\goblinAttack.mp3\" type mpegvideo alias goblin"), NULL, 0, NULL);
			mciSendString(TEXT("play goblin"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio goblin volume to 250"), NULL, 0, NULL);
		}
		else if (enemy == "Merman") {
			mciSendString(TEXT("open \"audio\\mermanAttack.mp3\" type mpegvideo alias merman"), NULL, 0, NULL);
			mciSendString(TEXT("play merman"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio merman volume to 100"), NULL, 0, NULL);
		}
		else if (enemy == "Kobold") {
			mciSendString(TEXT("open \"audio\\koboldAttack.mp3\" type mpegvideo alias kobold"), NULL, 0, NULL);
			mciSendString(TEXT("play kobold"), NULL, 0, NULL);
			mciSendString(TEXT("setaudio kobold volume to 350"), NULL, 0, NULL);
		}
	}

	else if (state == "close") {
		if (enemy == "Goblin") {
			mciSendString(TEXT("close goblin"), NULL, 0, NULL);
		}
		else if (enemy == "Merman") {
			mciSendString(TEXT("close merman"), NULL, 0, NULL);
		}
		else if (enemy == "Kobold") {
			mciSendString(TEXT("close kobold"), NULL, 0, NULL);
		}
	}
}