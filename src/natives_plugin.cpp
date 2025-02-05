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

#include "textdraw_data.hpp"
#include "natives.hpp"
#include "service.hpp"

bool Plugin_Settings::logMode = true;
std::string Plugin_Settings::file = "unknown";
int Plugin_Settings::line;

bool gCancelTextDraw = false;

cell AMX_NATIVE_CALL Natives::TDLogger(AMX* amx, cell* params)
{
	CHECK_PARAMS(2);
	Plugin_Settings::file = service::getString(amx, params[1]);
	Plugin_Settings::line = static_cast<int>(params[2]);
	return 1;
}

cell AMX_NATIVE_CALL Natives::CancelSelectDynTextDraw(AMX* amx, cell* params)
{
	CancelSelectTextDraw(params[1]);

	gCancelTextDraw = true;

	return 1;
}

void Plugin_Settings::ILogger(ErrorID type, std::string funcs, int playerid, int textid)
{
	if (Plugin_Settings::logMode == true)
	{
		if (type == ErrorID::CreatePlayerTextdraw)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: First use the CreatePlayerTextDraw function. (playerid: %d, textId: %d) (%s:%d)"
			,
				funcs.c_str(),
				playerid,
				textid,
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
		else if (type == ErrorID::FindPlayerText)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: No such id was found. (playerid: %d, textId: %d) (%s:%d)"
			,
				funcs.c_str(),
				playerid,
				textid,
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
		else if (type == ErrorID::ShowLimitPlayer)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: A maximum of %d textdraws can be displayed on a player. (playerid: %d, textId: %d) (%s:%d)"
			,
				funcs.c_str(),
				MAX_PLAYER_TEXT_DRAWS,
				playerid,
				textid,
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
		else if (type == ErrorID::FindGlobalText)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: No such id was found. (textId: %d) (%s:%d)"
			,
				funcs.c_str(),
				textid,
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
		else if (type == ErrorID::InvalidType)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: Type format is invalid. (%s:%d)"
			,
				funcs.c_str(),
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
		else if (type == ErrorID::FunctionNotFound)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: function not found. (%s:%d)"
			,
				funcs.c_str(),
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
		else if (type == ErrorID::UnknownSpecifier)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: unknown specifier. (%s:%d)"
			,
				funcs.c_str(),
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
		else if (type == ErrorID::InvalidSpecifierUse)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: invalid specifier use. (%s:%d)"
			,
				funcs.c_str(),
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
		else if (type == ErrorID::SpecifierCountMismatchArgs)
		{
			sampgdk::logprintf("[textdraw.streamer] %s: specifiers count does not match the arguments. (%s:%d)"
			,
				funcs.c_str(),
				Plugin_Settings::file.c_str(),
				Plugin_Settings::line
			);
		}
	}
}
