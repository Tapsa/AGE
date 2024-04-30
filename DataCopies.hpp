#pragma once
#include <cstdint>
#include <utility>
#include <vector>
#include "genie/dat/DatFile.h"

class GraphicCopies
{
public:

    int16_t IconID = -1;
    std::pair<int16_t, int16_t> StandingGraphic = { -1, -1 };
    int16_t DyingGraphic = -1;
    int16_t UndeadGraphic = -1;
    uint8_t DamageGraphicCount = 0;
    std::vector<genie::unit::DamageGraphic> DamageGraphics;

    int16_t ConstructionGraphicID = -1;
    int16_t SnowGraphicID = -1;
    int16_t DestructionGraphicID = -1;
    int16_t DestructionRubbleGraphicID = -1;
    int16_t ResearchingGraphic = -1;
    int16_t ResearchCompletedGraphic = -1;
    int16_t SpawningGraphic = -1;
    int16_t UpgradeGraphic = -1;
    int16_t HeroGlowGraphic = -1;
    int32_t GarrisonGraphic = -1;
    int32_t SpecialGraphic = -1;
    int16_t AttackGraphic = -1;
    int16_t WalkingGraphic = -1;
    int16_t RunningGraphic = -1;

    GraphicCopies() {}
    ~GraphicCopies() {}
};

class AdvCopies // Used to copy units with various settings.
{
public:

    // AllCivs is used as follows
    // 0x01 = normal copy
    // 0x02 = special copy
    // 0x04 =
    // 0x08 = from AoE 1
    // 0x10 = damage graphics
    // 0x20 = attacks
    // 0x40 = armors
    // 0x80 = commands
    // 0x100 = drop sites
    int16_t AllCivs;
    std::vector<std::vector<bool>> UnitExists;
    std::vector<std::vector<genie::Unit>> UnitCopies;
    std::vector<std::vector<GraphicCopies>> UnitGraphics;
    std::vector<short> UnitDamageGraphicExists;
    std::vector<std::vector<genie::unit::DamageGraphic>> UnitDamageGraphics;
    std::vector<short> UnitDropSiteExists;
    std::vector<std::vector<int16_t>> UnitDropSites;
    std::vector<short> UnitAttackExists;
    std::vector<std::vector<genie::unit::AttackOrArmor>> UnitAttacks;
    std::vector<short> UnitArmorExists;
    std::vector<std::vector<genie::unit::AttackOrArmor>> UnitArmors;
    std::vector<short> UnitCommandExists;
    std::vector<std::vector<genie::Task>> UnitCommands;

    AdvCopies()
    {
        UnitCopies.resize(1); // Civs
        UnitGraphics.resize(1); // Civs
        UnitDamageGraphics.resize(1); // Civs
        UnitDropSites.resize(1); // Civs
        UnitAttacks.resize(1); // Civs
        UnitArmors.resize(1); // Civs
        UnitCommands.resize(1); // Civs
        UnitGraphics[0].resize(1);
    }
    ~AdvCopies() {}
};

class Copies
{
public:

    Copies() {}
    ~Copies() {}

    std::vector<genie::Tech> Tech;
    std::vector<genie::Effect> Effect;
    std::vector<genie::EffectCommand> EffectCmd;
    std::vector<genie::TechTreeAge> TTAge;
    std::vector<long> TTAgeBuild;
    std::vector<long> TTAgeUnit;
    std::vector<long> TTAgeRes;
    std::vector<long> TTMode;
    std::vector<long> TTItem;
    std::vector<char> TTUnknown4;
    std::vector<char> TTUnknown5;
    std::vector<genie::BuildingConnection> TTBuildCon;
    std::vector<long> TTBuildBuild;
    std::vector<long> TTBuildUnit;
    std::vector<long> TTBuildRes;
    std::vector<genie::UnitConnection> TTUnitCon;
    std::vector<long> TTUnitUnit;
    std::vector<genie::ResearchConnection> TTResCon;
    std::vector<long> TTResBuild;
    std::vector<long> TTResUnit;
    std::vector<long> TTResRes;
    std::vector<genie::Civ> Civ;
    std::vector<float> Resource;
    AdvCopies Dat; // Advanced unit copying.
    std::vector<genie::UnitHeader> UnitHeader;
    std::vector<genie::UnitLine> UnitLine;
    std::vector<int16_t> UnitLineUnit;
    std::vector<genie::Graphic> Graphic;
    std::vector<uint32_t> GraphicPointer, TRptr1, TRptr2;
    std::vector<genie::GraphicDelta> GraphicDelta;
    std::vector<genie::Terrain> Terrain;
    std::vector<short> TerBorder;
    std::vector<genie::TerrainRestriction> TerrainRestriction;
    std::vector<float> TerrainRestrictionSubAccess;
    std::vector<genie::TerrainPassGraphic> TerrainRestrictionSubGraphics;
    std::vector<genie::Sound> Sound;
    std::vector<genie::SoundItem> SoundItem;
    std::vector<genie::PlayerColour> PlayerColor;
    std::vector<genie::TerrainBorder> TerrainBorder;
    std::vector<std::vector<genie::FrameData>> BorderBorder;
    std::vector<genie::FrameData> FrameData;
    std::vector<genie::MapInfo> Map;
    std::vector<genie::MapLand> MapLand;
    std::vector<genie::MapTerrain> MapTerrain;
    std::vector<genie::MapUnit> MapUnit;
    std::vector<genie::MapElevation> MapElevation;
};
