#pragma once

#include <string>

class GameMode
{
public:
    enum class Type {
        Intermission = -2,
        Casual = 0,
        Duel = 1,
        Doubles = 2,
        Standard = 3,
        Chaos = 4,
        PrivateMatch = 6,
        Season = 7,
        Exhibition = 8,
        Training = 9,
        DuelRanked = 10,
        DoublesRanked = 11,
        StandardRanked = 13,
        SnowDay = 15,
        RocketLabs = 16,
        Hoops = 17,
        Rumble = 18,
        Workshop = 19,
        CustomTrainingEditor = 20,
        CustomTraining = 21,
        TournamentMatchCustom = 22,
        Dropshot = 23,
        LocalMatch = 24,
        ExternalMatchRanked = 26,
        HoopsRanked = 27,
        RumbleRanked = 28,
        DropshotRanked = 29,
        SnowDayRanked = 30,
        GhostHunt = 31,
        BeachBall = 32,
        SpikeRush = 33,
        TournamentMatchAutomatic = 34,
        RocketLabs2 = 35,
        DropshotRumble = 37,
        Heatseeker = 38,
        BoomerBall = 41,
        HeatseekerDoubles = 43,
        WinterBreakaway = 44,
        Gridiron = 46,
        SuperCube = 47,
        TacticalRumble = 48,
        SpringLoaded = 49,
        SpeedDemon = 50,
        GothamCityRumble = 52,
        Knockout = 54,
        ConfidentialThirdWheelTest = 55
    };

    static std::string GetGameModeName(int gameModeId)
    {
        switch (static_cast<Type>(gameModeId))
        {
        case Type::Intermission: return "Intermission";
        case Type::Casual: return "Casual";
        case Type::Duel: return "Duel";
        case Type::Doubles: return "Doubles";
        case Type::Standard: return "Standard";
        case Type::Chaos: return "Chaos";
        case Type::PrivateMatch: return "Private Match";
        case Type::Season: return "Season";
        case Type::Exhibition: return "Exhibition";
        case Type::Training: return "Training";
        case Type::DuelRanked: return "Duel (Ranked)";
        case Type::DoublesRanked: return "Doubles (Ranked)";
        case Type::StandardRanked: return "Standard (Ranked)";
        case Type::SnowDay: return "Snow Day";
        case Type::RocketLabs: return "Rocket Labs";
        case Type::Hoops: return "Hoops";
        case Type::Rumble: return "Rumble";
        case Type::Workshop: return "Workshop";
        case Type::CustomTrainingEditor: return "Custom Training Editor";
        case Type::CustomTraining: return "Custom Training";
        case Type::TournamentMatchCustom: return "Tournament Match (Custom)";
        case Type::Dropshot: return "Dropshot";
        case Type::LocalMatch: return "Local Match";
        case Type::ExternalMatchRanked: return "External Match (Ranked)";
        case Type::HoopsRanked: return "Hoops (Ranked)";
        case Type::RumbleRanked: return "Rumble (Ranked)";
        case Type::DropshotRanked: return "Dropshot (Ranked)";
        case Type::SnowDayRanked: return "Snow Day (Ranked)";
        case Type::GhostHunt: return "Ghost Hunt";
        case Type::BeachBall: return "Beach Ball";
        case Type::SpikeRush: return "Spike Rush";
        case Type::TournamentMatchAutomatic: return "Tournament Match (Automatic)";
        case Type::RocketLabs2: return "Rocket Labs";
        case Type::DropshotRumble: return "Dropshot Rumble";
        case Type::Heatseeker: return "Heatseeker";
        case Type::BoomerBall: return "Boomer Ball";
        case Type::HeatseekerDoubles: return "Heatseeker Doubles";
        case Type::WinterBreakaway: return "Winter Breakaway";
        case Type::Gridiron: return "Gridiron";
        case Type::SuperCube: return "Super Cube";
        case Type::TacticalRumble: return "Tactical Rumble";
        case Type::SpringLoaded: return "Spring Loaded";
        case Type::SpeedDemon: return "Speed Demon";
        case Type::GothamCityRumble: return "Gotham City Rumble";
        case Type::Knockout: return "Knockout";
        case Type::ConfidentialThirdWheelTest: return "confidential_thirdwheel_test";
        default: return "Unknown";
        }
    }

    static std::string GetEnumName(Type gameMode)
    {
        int gameModeId = static_cast<int>(gameMode);
        std::string gameModeName = GetGameModeName(gameModeId);

        std::string result = gameModeName;
        result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
        result.erase(std::remove(result.begin(), result.end(), '('), result.end());
        result.erase(std::remove(result.begin(), result.end(), ')'), result.end());
        return result;
    }
};