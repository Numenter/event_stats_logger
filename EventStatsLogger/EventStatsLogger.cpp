#include "pch.h"
#include "EventStatsLogger.h"
#include <fstream>


BAKKESMOD_PLUGIN(EventStatsLogger, "write a plugin description here", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void EventStatsLogger::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("Plugin Loaded!");
	std::filesystem::path bakkesModPath = gameWrapper->GetBakkesModPath();
	// Register a console command to trigger saving
	cvarManager->registerNotifier("save_test", [this](std::vector<std::string> args) {
		// Example data to save, you can replace this with your actual data
		std::string data = "Sample data to save.";
		SaveDataToFile("my_saved_data.txt", data);
	}, "Save sample data to a file", 0);

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


	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", [this](std::string eventName) {
	//	LOG("Your hook got called and the ball went POOF");
	//});
	// You could also use std::bind here
	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", std::bind(&EventStatsLogger::YourPluginMethod, this);
}


void EventStatsLogger::SaveDataToFile(const std::string& filename, const std::string& data) {
	_globalCvarManager = cvarManager;

	// Working folder path
	std::filesystem::path bakkesModPath = gameWrapper->GetBakkesModPath();
	std::filesystem::path pluginFolderPath = bakkesModPath / "data" / "EventStatsLogger";

	// Create directory if it doesn't exist
	std::error_code ec;
	std::filesystem::create_directories(pluginFolderPath, ec);
	if (ec) {
		cvarManager->log("Failed to create directory: " + pluginFolderPath.string());
		return;
	}

	// Overwrite or create the file
	std::filesystem::path filePath = pluginFolderPath / filename;
	std::ofstream outFile(filePath);
	if (outFile.is_open()) {
		outFile << data;
		outFile.close();
		cvarManager->log("Data saved to: " + filePath.string());
	}
	else {
		cvarManager->log("Failed to open file for writing: " + filePath.string());
	}
}