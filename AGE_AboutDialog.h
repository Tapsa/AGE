#include "Common.hpp"
using namespace std;

#ifndef AGE_AboutDialog_h
#define AGE_AboutDialog_h

class AGE_AboutDialog : public wxDialog
{
	public:

	AGE_AboutDialog(wxWindow *parent);

//	Member Variables

	wxStaticText * Title;
	wxStaticBitmap * Image;
	wxStaticText * Credits;
	wxHyperlinkCtrl * AoKHThread; //http://aok.heavengames.com/cgi-bin/aokcgi/display.cgi?action=ct&f=4,38606,0,365
	wxStaticText * UPXInfo;
	wxHyperlinkCtrl * UPXLink; //http://upx.sourceforge.net/

	wxBoxSizer * MainLeft;
	wxBoxSizer * MainRight;
	wxBoxSizer * MainAbout;
};

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

class Copies // Used to copy units with various settings.
{
	public:

	bool AllCivs;
	int8_t CopyType; // 1 = normal, 2 = special, 3 = auto
	vector<SubCopies> Civs;

	Copies()
	{
		Civs.resize(1);
		Civs[0].UnitGraphics.resize(1);
	}
	~Copies(){}
};

#endif
