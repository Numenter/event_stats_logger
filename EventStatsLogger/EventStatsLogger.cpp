#include "pch.h"
#include "EventStatsLogger.h"
#include <fstream>
#include <chrono>


BAKKESMOD_PLUGIN(EventStatsLogger, "EventStatsLogger", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void EventStatsLogger::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("Plugin Loaded!");
	std::filesystem::path bakkesModPath = gameWrapper->GetBakkesModPath();

	// Update all ranks (with delay)
	gameWrapper->SetTimeout([this](GameWrapper* gw) {
		updateAllRankFiles();
		}, 5.0f);

	//LOG("Plugin loaded!");
	// !! Enable debug logging by setting DEBUG_LOG = true in logging.h !!
	//DEBUGLOG("EventStatsLogger debug mode enabled");

	// LOG and DEBUGLOG use fmt format strings https://fmt.dev/latest/index.html
	//DEBUGLOG("1 = {}, 2 = {}, pi = {}, false != {}", "one", 2, 3.14, true);

	//cvarManager->registerNotifier("my_aweseome_notifier", [&](std::vector<std::string> args) {
	//	LOG("Hello notifier!");
	//}, "", 0);

	//auto cvar = cvarManager->registerCvar("template_cvar", "hello-cvar", "just a example of a cvar");
	//auto cvar2 = cvarManager->registerCvar("template_cvar2", "0", "just a example of a cvar with more settings", true, true, -10, true, 10 );

	//cvar.addOnValueChanged([this](std::string cvarName, CVarWrapper newCvar) {
	//	LOG("the cvar with name: {} changed", cvarName);
	//	LOG("the new value is: {}", newCvar.getStringValue());
	//});

	//cvar2.addOnValueChanged(std::bind(&EventStatsLogger::YourPluginMethod, this, _1, _2));

	// enabled decleared in the header
	//enabled = std::make_shared<bool>(false);
	//cvarManager->registerCvar("TEMPLATE_Enabled", "0", "Enable the TEMPLATE plugin", true, true, 0, true, 1).bindTo(enabled);

	//cvarManager->registerNotifier("NOTIFIER", [this](std::vector<std::string> params){FUNCTION();}, "DESCRIPTION", PERMISSION_ALL);
	//cvarManager->registerCvar("CVAR", "DEFAULTVALUE", "DESCRIPTION", true, true, MINVAL, true, MAXVAL);//.bindTo(CVARVARIABLE);
	//gameWrapper->HookEvent("FUNCTIONNAME", std::bind(&TEMPLATE::FUNCTION, this));
	//gameWrapper->HookEventWithCallerPost<ActorWrapper>("FUNCTIONNAME", std::bind(&EventStatsLogger::FUNCTION, this, _1, _2, _3));
	//gameWrapper->RegisterDrawable(bind(&TEMPLATE::Render, this, std::placeholders::_1));

	gameWrapper->HookEvent("Function TAGame.Team_TA.PostBeginPlay", [this](std::string eventName) {
		saveEventToFile("PostBeginPlay");
		});

	gameWrapper->HookEvent("Function GameEvent_Soccar_TA.Active.StartRound", [this](std::string eventName) {
		saveEventToFile("Active.StartRound");
	});

	gameWrapper->HookEvent("Function GameEvent_Soccar_TA.Countdown.BeginState", [this](std::string eventName) {
		saveEventToFile("Countdown.BeginState");
		});

	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.EventMatchEnded", [this](std::string eventName) {
		MMRWrapper mmrWrapper = gameWrapper->GetMMRWrapper();
		int gameModeId = mmrWrapper.GetCurrentPlaylist();
		//cvarManager->log("gameModeId: " + std::to_string(gameModeId));
		GameMode::Type gameMode = static_cast<GameMode::Type>(gameModeId);
		saveRankToFile(gameMode);
		saveEventToFile("EventMatchEnded");
		});

	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.Destroyed", [this](std::string eventName) {
		saveEventToFile("Destroyed");
		});

	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", [this](std::string eventName) {
	//	LOG("Your hook got called and the ball went POOF");
	//});
	// You could also use std::bind here
	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", std::bind(&EventStatsLogger::YourPluginMethod, this);
}


void EventStatsLogger::saveDataToFile(const std::string& filename, const std::string& data) {
	_globalCvarManager = cvarManager;

	// Working folder path
	std::filesystem::path bakkesModPath = gameWrapper->GetBakkesModPath();
	std::filesystem::path pluginFolderPath = bakkesModPath / "data" / "EventStatsLogger";
	std::filesystem::path filePath = pluginFolderPath / filename;
	std::filesystem::path dirPath = filePath.parent_path();

	// Create directory if it doesn't exist
	std::error_code ec;
	std::filesystem::create_directories(dirPath, ec);
	if (ec) {
		cvarManager->log("Failed to create directory: " + dirPath.string());
		return;
	}

	// Overwrite or create the file
	std::ofstream outFile(filePath);
	if (outFile.is_open()) {
		outFile << data;
		outFile.close();
	}
	else {
		cvarManager->log("Failed to open file for writing: " + filePath.string());
	}
}

void EventStatsLogger::saveEventToFile(const std::string& eventName)
{
	ServerWrapper sw = gameWrapper->GetCurrentGameState();
	if (!sw) return;
	GameSettingPlaylistWrapper playlist = sw.GetPlaylist();
	if (!playlist) return;
	int playlistID = playlist.GetPlaylistId();
	std::string playlistName = GameMode::GetGameModeName(playlistID);
	saveDataToFile("event\\"+eventName+".txt", playlistName +"\n" + std::to_string(playlistID));
}

void EventStatsLogger::saveRankToFile(GameMode::Type gameMode)
{
	MMRWrapper mmrWrapper = gameWrapper->GetMMRWrapper();
	int gameModeId = static_cast<int>(gameMode);
	float mmrValue = mmrWrapper.GetPlayerMMR(gameWrapper->GetUniqueID(), gameModeId);
	SkillRank skillRank = mmrWrapper.GetPlayerRank(gameWrapper->GetUniqueID(), gameModeId);

	std::string gameModeName = GameMode::GetGameModeName(gameModeId);
	std::string mmr = std::to_string(mmrValue);
	std::string tier = std::to_string(skillRank.Tier);
	std::string division = std::to_string(skillRank.Division);
	std::string matchesPlayed = std::to_string(skillRank.MatchesPlayed);

	std::string data = gameModeName + "\n" + mmr + "\n" + tier + "\n" + division + "\n" + matchesPlayed;
	saveDataToFile("rank\\" + GameMode::GetEnumName(gameMode) + ".txt", data);
}

void EventStatsLogger::updateAllRankFiles()
{
	saveRankToFile(GameMode::Type::Casual);
	saveRankToFile(GameMode::Type::DuelRanked);
	saveRankToFile(GameMode::Type::DoublesRanked);
	saveRankToFile(GameMode::Type::StandardRanked);
	saveRankToFile(GameMode::Type::RumbleRanked);
	saveRankToFile(GameMode::Type::HoopsRanked);
	saveRankToFile(GameMode::Type::SnowDayRanked);
}