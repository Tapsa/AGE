#include "Common.h"
using namespace std;

#ifndef Copies_h
#define Copies_h

class GraphicCopies
{
	public:

	int16_t IconID;
	pair<int16_t, int16_t> StandingGraphic;
	pair<int16_t, int16_t> DyingGraphic;
	uint8_t DamageGraphicCount;
	vector<genie::unit::DamageGraphic> DamageGraphics;

	int16_t ConstructionGraphicID;
	int16_t SnowGraphicID;
	pair<int16_t, int16_t> GarrisonGraphic;
	int16_t AttackGraphic;
	pair<int16_t, int16_t> WalkingGraphic;

	GraphicCopies()
	{
		IconID = -1;
		StandingGraphic.first = -1;
		StandingGraphic.second = -1;
		DyingGraphic.first = -1;
		DyingGraphic.second = -1;
		DamageGraphicCount = 0;
		ConstructionGraphicID = -1;
		SnowGraphicID = -1;
		GarrisonGraphic.first = -1;
		GarrisonGraphic.second = -1;
		AttackGraphic = -1;
		WalkingGraphic.first = -1;
		WalkingGraphic.second = -1;
	}
	~GraphicCopies(){}
};

class SubCopies
{
	public:

	vector<bool> UnitExists;
	vector<genie::Unit> UnitCopies;
	vector<GraphicCopies> UnitGraphics;

	SubCopies(){}
	~SubCopies(){}
};

class AdvCopies // Used to copy units with various settings.
{
	public:

	bool AllCivs;
	int8_t CopyType; // 1 = normal, 2 = special, 3 = auto
	vector<SubCopies> Civs;

	AdvCopies()
	{
		Civs.resize(1);
		Civs[0].UnitGraphics.resize(1);
	}
	~AdvCopies(){}
};

class Copies
{
	public:

	Copies(){}
	~Copies(){}
	
	vector<genie::Research> Research;
	vector<genie::Techage> Tech;
	vector<genie::TechageEffect> Effect;
	vector<genie::TechTreeAge> TTAge;
	vector<long> TTAgeBuild;
	vector<long> TTAgeUnit;
	vector<long> TTAgeRes;
	vector<genie::BuildingConnection> TTBuildCon;
	vector<long> TTBuildBuild;
	vector<long> TTBuildUnit;
	vector<long> TTBuildRes;
	vector<genie::UnitConnection> TTUnitCon;
	vector<long> TTUnitUnit;
	vector<genie::ResearchConnection> TTResCon;
	vector<long> TTResBuild;
	vector<long> TTResUnit;
	vector<long> TTResRes;
	vector<genie::Civ> Civ;
	vector<float> Resource;
	AdvCopies Dat; // Advanced unit copying.
	vector<genie::unit::DamageGraphic> DamageGraphic;
	vector<genie::unit::AttackOrArmor> Attack;
	vector<genie::unit::AttackOrArmor> Armor;
	vector<genie::UnitHeader> UnitHeader;
	vector<genie::UnitCommand> UnitCommand;
	vector<genie::UnitLine> UnitLine;
	vector<int16_t> UnitLineUnit;
	vector<genie::Graphic> Graphic;
	vector<int32_t> GraphicPointer;
	vector<genie::GraphicDelta> GraphicDelta;
	vector<genie::Terrain> Terrain;
	vector<genie::TerrainRestriction> TerrainRestriction;
	vector<genie::TerrainPassGraphic> TerrainRestrictionSub;
	vector<genie::Sound> Sound;
	vector<genie::SoundItem> SoundItem;
	vector<genie::PlayerColour> PlayerColor;
	vector<genie::TerrainBorder> TerrainBorder;
	vector<genie::TBFrameData> TBFrameData;
};

#endif
