#include "SA2ModLoader.h"
#include "IniFile.hpp"

extern "C"
{
	void IGflashlight();
	void LCflashlight();
	void floors();
	void enemyFlash();
	void IGRed1();
	void IGRed2();
	bool lostColonyFog = false;
	bool ironGateFog = false;
	bool ironGateTint = false;
	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
	__declspec(dllexport) void _cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		lostColonyFog = config->getBool("Options", "LostColonyFog", false);
		ironGateFog = config->getBool("Options", "IronGateFog", false);
		ironGateTint = config->getBool("Options", "IronGateTint", false);

		if (lostColonyFog) {
			helperFunctions.ReplaceFile("resource\\gd_PC\\stg27_fog.bin", "resource\\gd_PC\\stg27_fog_DC.bin");
			helperFunctions.ReplaceFile("resource\\gd_PC\\stg27_fogB.bin", "resource\\gd_PC\\stg27_fogB_DC.bin");
		}

		if (ironGateFog) {
			helperFunctions.ReplaceFile("resource\\gd_PC\\stg11_fog.bin", "resource\\gd_PC\\stg11_fog_DC.bin");
			helperFunctions.ReplaceFile("resource\\gd_PC\\stg11_fogB.bin", "resource\\gd_PC\\stg11_fogB_DC.bin");
			
		}
	}

	void floors() {
		FunctionPointer(void, sub_42A950, (int, float, float, float), 0x42A950);
		sub_42A950(0, 0.0f, 0.0f, 0.0f);
	}

	void IGRed1(){
		FunctionPointer(void, sub_42A950, (int, float, float, float), 0x42A950);
		sub_42A950(2, 0.5f, 0.05f, 0.15000001f);
		if (LevelIDs_IronGate && ironGateFog) {
			DataPointer(FogData, ironGateFogPtrB, 0x1A508B0);
			FogDataPtr = &ironGateFogPtrB;
		}

		if (CurrentLevel == LevelIDs_IronGate && ironGateTint && ScreenFadeARGB.color == 0x00000000 &&
			(GameState == GameStates_Ingame || GameState == GameStates_Pause)) ScreenFadeARGB.color = 0x40FF0000;
	}

	void IGRed2() {
		FunctionPointer(void, sub_42A950, (int, float, float, float), 0x42A950);
		sub_42A950(3, 0.5f, 0.15000001f, 0.05f);

		if (CurrentLevel == LevelIDs_IronGate && ironGateFog) {
			DataPointer(FogData, ironGateFogPtrB, 0x1A508B0);
			FogDataPtr = &ironGateFogPtrB;
		}
		if (CurrentLevel == LevelIDs_IronGate && ironGateTint && ScreenFadeARGB.color == 0x00000000 &&
			(GameState == GameStates_Ingame || GameState == GameStates_Pause)) ScreenFadeARGB.color = 0x40FF0000;
	}

	void IGflashlight() {
		FunctionPointer(void, sub_42A950, (int, float, float, float), 0x42A950);
		sub_42A950(1, 0.4f, 0.4f, 0.3f);

		if (CurrentLevel == LevelIDs_IronGate && ironGateFog) {
			DataPointer(FogData, ironGateFogPtr, 0x1A50620);
			FogDataPtr = &ironGateFogPtr;
			
		}

		if (CurrentLevel == LevelIDs_IronGate && ironGateTint && ScreenFadeARGB.color == 0x40FF0000) ScreenFadeARGB.color = 0x00000000;
	}

	void LCflashlight() {
		FunctionPointer(void, sub_42A950, (int, float, float, float), 0x42A950);
		sub_42A950(2, 0.1f, 0.1f, 0.1f);
	}

	void enemyFlash() {
		FunctionPointer(void, sub_42A950, (int, float, float, float), 0x42A950);
		if (CurrentLevel == LevelIDs_IronGate) {
			sub_42A950(3, 0.1f, 0.1f, 0.08f);
		}
		if (CurrentLevel == LevelIDs_LostColony) {
			sub_42A950(3, 0.0f, 0.0f, 0.0f);
		}

	}

	__declspec(dllexport) void __cdecl OnFrame() {
		if (CurrentLevel == LevelIDs_IronGate || CurrentLevel == LevelIDs_LostColony) {
			WriteCall((void*)0x486F47, floors);
			WriteCall((void*)0x48714D, floors);
			WriteCall((void*)0x68EDD2, enemyFlash);
			WriteCall((void*)0x699DBB, IGflashlight);
			WriteCall((void*)0x76407B, LCflashlight);
			WriteCall((void*)0x699F31, IGRed1);
			WriteCall((void*)0x69A075, IGRed2);
			WriteData((BYTE*)0x699D1E, (BYTE)0xA8);
		}
		else {
			WriteCall((void*)0x699DBB, (int*)0x42A950);
			WriteCall((void*)0x76407B, (int*)0x42A950);
			WriteCall((void*)0x699F31, (int*)0x42A950);
			WriteCall((void*)0x69A075, (int*)0x42A950);
			WriteCall((int*)0x486F47, (int*)0x42A950);
			WriteCall((int*)0x48714D, (int*)0x42A950);
			WriteCall((void*)0x68EDD2, (int*)0x42A950);
			WriteData((BYTE*)0x699D1E, (BYTE)0x08);
		}
	}
}