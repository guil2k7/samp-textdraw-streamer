/*
 * Copyright (C) 2023 Burak (Nexor)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <set>
#include "sampgdk.hpp"
#include "compilation_date.hpp"
#include "plugin_version.hpp"
#include "slot_manager.hpp"
#include "natives.hpp"
#include "textdraw_data.hpp"

bool load = false;
extern void *pAMXFunctions;
std::set<AMX*> gAmx;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return sampgdk::Supports() | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	load = sampgdk::Load(ppData);
	if (load)
	{
		sampgdk::logprintf("");
		sampgdk::logprintf(" =================================");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |    textdraw-streamer v%d.%d.%d   |", MINOR, MAJOR, PATCH);
		sampgdk::logprintf(" |            Loaded             |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Coding:                      |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Burak (Nexor)                |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Compiled:                    |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  %02d.%02d.%04d, %02d:%02d:%02d         |", BUILD_DAY, BUILD_MONTH, BUILD_YEAR, BUILD_HOUR, BUILD_MIN, BUILD_SEC);
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Github:                      |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  github.com/nexquery          |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Discord:                     |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  benburakya - Nexor#4730      |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" =================================");
		sampgdk::logprintf("");
	}
	return load;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	if (load)
	{
		GlobalText::Destroy();
		PlayerText::Destroy(-1);

		sampgdk::logprintf("");
		sampgdk::logprintf(" =================================");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |    textdraw-streamer v%d.%d.%d   |", MINOR, MAJOR, PATCH);
		sampgdk::logprintf(" |           Unloaded            |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Coding:                      |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Burak (Nexor)                |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Compiled:                    |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  %02d.%02d.%04d, %02d:%02d:%02d         |", BUILD_DAY, BUILD_MONTH, BUILD_YEAR, BUILD_HOUR, BUILD_MIN, BUILD_SEC);
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Github:                      |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  github.com/nexquery          |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  Discord:                     |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" |  benburakya - Nexor#4730      |");
		sampgdk::logprintf(" |                               |");
		sampgdk::logprintf(" =================================");
		sampgdk::logprintf("");
	}
}

extern "C" const AMX_NATIVE_INFO NativeList[] =
{
	// Global
	{"CreateDynamicTextDraw",							Natives::CreateDynamicTextDraw},
	{"DestroyDynamicTextDraw",							Natives::DestroyDynamicTextDraw},
	{"DynamicTextDrawLetterSize",						Natives::DynamicTextDrawLetterSize},
	{"DynamicTextDrawTextSize",							Natives::DynamicTextDrawTextSize},
	{"DynamicTextDrawAlignment",						Natives::DynamicTextDrawAlignment},
	{"DynamicTextDrawColour",							Natives::DynamicTextDrawColour},
	{"DynamicTextDrawUseBox",							Natives::DynamicTextDrawUseBox},
	{"DynamicTextDrawBoxColour",						Natives::DynamicTextDrawBoxColour},
	{"DynamicTextDrawSetShadow",						Natives::DynamicTextDrawSetShadow},
	{"DynamicTextDrawSetOutline",						Natives::DynamicTextDrawSetOutline},
	{"DynamicTextDrawBackgroundColour",					Natives::DynamicTextDrawBackgroundColour},
	{"DynamicTextDrawFont",								Natives::DynamicTextDrawFont},
	{"DynamicTextDrawSetProportional",					Natives::DynamicTextDrawSetProportional},
	{"DynamicTextDrawSetSelectable",					Natives::DynamicTextDrawSetSelectable},
	{"DynamicTextDrawShowForPlayer",					Natives::DynamicTextDrawShowForPlayer},
	{"DynamicTextDrawHideForPlayer",					Natives::DynamicTextDrawHideForPlayer},
	{"DynamicTextDrawShowForAll",						Natives::DynamicTextDrawShowForAll},
	{"DynamicTextDrawHideForAll",						Natives::DynamicTextDrawHideForAll},
	{"DynamicTextDrawSetString",						Natives::DynamicTextDrawSetString},
	{"DynamicTextDrawSetPreviewModel",					Natives::DynamicTextDrawSetPreviewModel},
	{"DynamicTextDrawSetPreviewRot",					Natives::DynamicTextDrawSetPreviewRot},
	{"DynamicTextDrawSetPreviewVehCol",					Natives::DynamicTextDrawSetPreviewVehicleColours},
	{"DynamicTextDrawSetClick",							Natives::DynamicTextDrawSetClickCallback},

	{"IsValidDynamicTextDraw",							Natives::IsValidDynamicTextDraw},
	{"IsDynTextDrawVisibleForPlayer",					Natives::IsDynamicTextDrawVisibleForPlayer},
	{"DynamicTextDrawGetString",						Natives::DynamicTextDrawGetString},
	{"DynamicTextDrawSetPos",							Natives::DynamicTextDrawSetPos},
	{"DynamicTextDrawGetLetterSize",					Natives::DynamicTextDrawGetLetterSize},
	{"DynamicTextDrawGetTextSize",						Natives::DynamicTextDrawGetTextSize},
	{"DynamicTextDrawGetPos",							Natives::DynamicTextDrawGetPos},
	{"DynamicTextDrawGetColour",						Natives::DynamicTextDrawGetColour},
	{"DynamicTextDrawGetBoxColour",						Natives::DynamicTextDrawGetBoxColour},
	{"DynamicTextDrawGetBackgroundCo",					Natives::DynamicTextDrawGetBackgroundColour},
	{"DynamicTextDrawGetShadow",						Natives::DynamicTextDrawGetShadow},
	{"DynamicTextDrawGetOutline",						Natives::DynamicTextDrawGetOutline},
	{"DynamicTextDrawGetFont",							Natives::DynamicTextDrawGetFont},
	{"DynamicTextDrawIsBox",							Natives::DynamicTextDrawIsBox},
	{"DynamicTextDrawIsProportional",					Natives::DynamicTextDrawIsProportional},
	{"DynamicTextDrawIsSelectable",						Natives::DynamicTextDrawIsSelectable},
	{"DynamicTextDrawGetAlignment",						Natives::DynamicTextDrawGetAlignment},
	{"DynamicTextDrawGetPreviewModel",					Natives::DynamicTextDrawGetPreviewModel},
	{"DynamicTextDrawGetPreviewRot",					Natives::DynamicTextDrawGetPreviewRot},
	{"DynamicTextDrawGetPreviewVehCo",					Natives::DynamicTextDrawGetPreviewVehicleColours},
	{"DynamicTextDrawGetRealID",						Natives::DynamicTextDrawGetRealID},
	{"DynamicTextDrawGetSize",							Natives::DynamicTextDrawGetSize},

	// Player
	{"CreateDynamicPlayerTextDraw",						Natives::CreateDynamicPlayerTextDraw},
	{"DestroyDynamicPlayerTextDraw",					Natives::DestroyDynamicPlayerTextDraw},
	{"DynamicPlayerTextDrawLetterSize",					Natives::DynamicPlayerTextDrawLetterSize},
	{"DynamicPlayerTextDrawTextSize",					Natives::DynamicPlayerTextDrawTextSize},
	{"DynamicPlayerTextDrawAlignment",					Natives::DynamicPlayerTextDrawAlignment},
	{"DynamicPlayerTextDrawColour",						Natives::DynamicPlayerTextDrawColour},
	{"DynamicPlayerTextDrawUseBox",						Natives::DynamicPlayerTextDrawUseBox},
	{"DynamicPlayerTextDrawBoxColor",					Natives::DynamicPlayerTextDrawBoxColor},
	{"DynamicPlayerTextDrawSetShadow",					Natives::DynamicPlayerTextDrawSetShadow},
	{"DynamicPlayerTextDrawSetOutline",					Natives::DynamicPlayerTextDrawSetOutline},
	{"DynamicPlayerTextDrawBGColour",					Natives::DynamicPlayerTextDrawBackgroundColour},
	{"DynamicPlayerTextDrawFont",						Natives::DynamicPlayerTextDrawFont},
	{"DynPlayerTextSetProportional",					Natives::DynamicPlayerTextDrawSetProportional},
	{"DynamicPlayerTextDrawSelectable",					Natives::DynamicPlayerTextDrawSetSelectable},
	{"DynamicPlayerTextDrawShow",						Natives::DynamicPlayerTextDrawShow},
	{"DynamicPlayerTextDrawHide",						Natives::DynamicPlayerTextDrawHide},
	{"DynamicPlayerTextDrawSetString",					Natives::DynamicPlayerTextDrawSetString},
	{"DynamicPlayerTextDrawSetPrevMdl",					Natives::DynamicPlayerTextDrawSetPreviewModel},
	{"DynamicPlayerTextDrawSetPrevRot",					Natives::DynamicPlayerTextDrawSetPreviewRot},
	{"DynamicPlayerTextDrawPrevVehCol",					Natives::DynamicPlayerTextDrawSetPreviewVehicleColours},
	{"DynamicPlayerTextDrawSetClick",					Natives::DynamicPlayerTextDrawSetClickCallback},

	{"IsValidDynamicPlayerTextDraw",					Natives::IsValidDynamicPlayerTextDraw},
	{"IsDynamicPlayerTextDrawVisible",					Natives::IsDynamicPlayerTextDrawVisible},
	{"DynamicPlayerTextDrawGetString",					Natives::DynamicPlayerTextDrawGetString},
	{"DynamicPlayerTextDrawSetPos",						Natives::DynamicPlayerTextDrawSetPos},
	{"DynPlayerTextDrawGetLetterSize",					Natives::DynamicPlayerTextDrawGetLetterSize},
	{"DynPlayerTextDrawGetTextSize",					Natives::DynamicPlayerTextDrawGetTextSize},
	{"DynamicPlayerTextDrawGetPos",						Natives::DynamicPlayerTextDrawGetPos},
	{"DynamicPlayerTextDrawGetColour",					Natives::DynamicPlayerTextDrawGetColour},
	{"DynamicPlayerTextDrawGetBoxCol",					Natives::DynamicPlayerTextDrawGetBoxColour},
	{"DynPlayerTextDrawGetBGColour",					Natives::DynamicPlayerTextDrawGetBackgroundColour},
	{"DynamicPlayerTextDrawGetShadow",					Natives::DynamicPlayerTextDrawGetShadow},
	{"DynamicPlayerTextDrawGetOutline",					Natives::DynamicPlayerTextDrawGetOutline},
	{"DynamicPlayerTextDrawGetFont",					Natives::DynamicPlayerTextDrawGetFont},
	{"DynamicPlayerTextDrawIsBox",						Natives::DynamicPlayerTextDrawIsBox},
	{"DynPlayerTextDrawIsProportional",					Natives::DynamicPlayerTextDrawIsProportional},
	{"DynPlayerTextDrawIsSelectable",					Natives::DynamicPlayerTextDrawIsSelectable},
	{"DynPlayerTextDrawGetAlignment",					Natives::DynamicPlayerTextDrawGetAlignment},
	{"DynPlayerTextDrawGetPreviewMdl",					Natives::DynamicPlayerTextDrawGetPreviewModel},
	{"DynPlayerTextDrawGetPreviewRot",					Natives::DynamicPlayerTextDrawGetPreviewRot},
	{"DynPlayerTextDrawGetPrevVehCol",					Natives::DynamicPlayerTextDrawGetPreviewVehicleColours},
	{"PlayerTextDrawGetRealID",							Natives::PlayerTextDrawGetRealID},
	{"PlayerTextDrawGetSize",							Natives::PlayerTextDrawGetSize},

	// Logger
	{ "TDLogger__",										Natives::TDLogger },

	// NULL
	{NULL, NULL}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	cell address = 0;
	if (!amx_FindPubVar(amx, "TDS_Enable_Log", &address))
	{
		cell* amxPhysAddr = NULL;
		if (!amx_GetAddr(amx, address, &amxPhysAddr))
		{
			Plugin_Settings::logMode = static_cast<bool>(*amxPhysAddr);
		}
	}
	gAmx.insert(amx);
	return amx_Register(amx, NativeList, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	gAmx.erase(amx);
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	sampgdk::ProcessTick();
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	// Ba�lanan oyuncuyu listeye ekle
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		GlobalText::PlayerList.insert(playerid);
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	// Ba�lanan oyuncuda textdraw g�z�k�yor mu?
	for (auto textList = GlobalText::gTextVisible.begin(); textList != GlobalText::gTextVisible.end(); textList++)
	{
		// T�m textdrawlarda bu oyuncuyu ara
		auto p = GlobalText::gTextVisible[textList->first].find(playerid);
		if (p != GlobalText::gTextVisible[textList->first].end())
		{
			// Textdraw da g�steriliyorsa oyuncuyu kald�r
			GlobalText::gTextVisible[textList->first].erase(p);
		}

		// G�sterilen textdraw da oyuncu kalmad�ysa
		if (GlobalText::gTextVisible[textList->first].empty())
		{
			// Textdraw� sunucudan sil
			auto t = GlobalText::gText->find(textList->first);
			if (t != GlobalText::gText->end())
			{
				if (t->second->real_id != INVALID_DYNAMIC_PLAYER_TEXTDRAW)
				{
					TextDrawDestroy(t->second->real_id);
					t->second->real_id = INVALID_DYNAMIC_PLAYER_TEXTDRAW;
				}
			}
		}
	}

	// Ba�lanan oyuncuyu listeden kald�r
	GlobalText::PlayerList.erase(playerid);

	// PlayerTextdraw havuzunu ve slot manageri temizle
	PlayerText::Destroy(playerid);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickTextDraw(int playerid, int clickedid)
{
	// ESC bast�ysa
	if (clickedid == INVALID_TEXT_DRAW)
	{
		int idx;
		for (std::set<AMX*>::iterator p = gAmx.begin(); p != gAmx.end(); p++)
		{
			if (!amx_FindPublic(*p, "OnCancelDynamicTextDraw", &idx))
			{
				amx_Push(*p, static_cast<cell>(playerid));
				amx_Exec(*p, NULL, idx);
			}

			if (!amx_FindPublic(*p, "OnClickDynamicTextDraw", &idx))
			{
				amx_Push(*p, static_cast<cell>(INVALID_TEXT_DRAW));
				amx_Push(*p, static_cast<cell>(playerid));
				amx_Exec(*p, NULL, idx);
			}
		}

		return false;
	}

	if (gAmx.empty() || GlobalText::gText->empty())
		return false;

	for (std::unordered_map<int, Text_Data*>::iterator it = GlobalText::gText->begin(); it != GlobalText::gText->end(); it++)
	{
		if (it->second->real_id != clickedid)
			continue;

		AMX* amx = it->second->amx;
		int idx = it->second->clickCallback;

		if (idx == 0)
		{
			if (amx_FindPublic(amx, "OnClickDynamicTextDraw", &idx) != AMX_ERR_NONE)
				break;

			amx_Push(amx, static_cast<cell>(it->first));
			amx_Push(amx, static_cast<cell>(playerid));
			amx_Exec(amx, NULL, idx);

			break;
		}

		cell allocations[10];
		size_t allocationsCount = 0;

		auto argsIt = it->second->userData.rbegin();
		auto argsItEnd = it->second->userData.rend();

		for (; argsIt != argsItEnd; ++argsIt) {
			cell xAddr = argsIt->push(amx);

			if (xAddr != 0)
				allocations[allocationsCount++] = xAddr;
		}

		amx_Push(amx, static_cast<cell>(playerid));
		amx_Exec(amx, NULL, idx);

		for (size_t i = 0; i < allocationsCount; ++i)
			amx_Release(amx, allocations[i]);

		break;
	}

	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayerTextDraw(int playerid, int playertextid)
{
	if (gAmx.empty() || !PlayerText::pText[playerid] || PlayerText::pText[playerid]->empty())
		return false;

	for (auto it = PlayerText::pText[playerid]->begin(); it != PlayerText::pText[playerid]->end(); it++)
	{
		if (it->second->real_id != playertextid)
			continue;

		AMX* amx = it->second->amx;
		int idx = it->second->clickCallback;

		if (idx == 0)
		{
			if (amx_FindPublic(amx, "OnClickDynamicPlayerTextDraw", &idx) != AMX_ERR_NONE)
				break;

			amx_Push(amx, static_cast<cell>(it->first));
			amx_Push(amx, static_cast<cell>(playerid));
			amx_Exec(amx, NULL, idx);

			break;
		}

		cell allocations[10];
		size_t allocationsCount = 0;

		auto argsIt = it->second->userData.rbegin();
		auto argsItEnd = it->second->userData.rend();

		for (; argsIt != argsItEnd; ++argsIt) {
			cell xAddr = argsIt->push(amx);

			if (xAddr != 0)
				allocations[allocationsCount++] = xAddr;
		}

		amx_Push(amx, static_cast<cell>(playerid));
		amx_Exec(amx, NULL, idx);

		for (size_t i = 0; i < allocationsCount; ++i)
			amx_Release(amx, allocations[i]);

		break;
	}

	return false;
}
