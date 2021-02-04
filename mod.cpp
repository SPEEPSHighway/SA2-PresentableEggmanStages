#include "SA2ModLoader.h"
#include "SA2Functions.h"
#include "MemAccess.h"

extern "C"
{
	void IGflashlight();
	void LCflashlight();
	void floors();
	void enemyFlash();
	void IGRed1();
	void IGRed2();
	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
	__declspec(dllexport) void _cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
	}

	void floors() {
		FunctionPointer(void, sub_42A950, (int, float, float, float), 0x42A950);
		sub_42A950(0, 0.0f, 0.0f, 0.0f);
	}

	void IGRed1(){
		FunctionPointer(void, sub_42A950, (int, float, float, float), 0x42A950);
		sub_42A950(2, 0.5f, 0.05f, 0.15000001f);
	}

	void IGRed2() {
		FunctionPointer(void, sub_42A950, (int, float, float, float), 0x42A950);
		sub_42A950(3, 0.5f, 0.15000001f, 0.05f);
	}

	void IGflashlight() {
		FunctionPointer(void, sub_42A950, (int, float, float, float), 0x42A950);
		sub_42A950(1, 0.4f, 0.4f, 0.3f);
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