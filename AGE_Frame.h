/* AGE_Frame.h */

#include "wx/wx.h"
#include "wx/fileconf.h"
#include "wx/notebook.h"
#include "wx/aboutdlg.h"
#include "wx/hyperlink.h"
#include "wx/tooltip.h"
#include "geniedat/File.h"	// New dat system
#include "AGE_TextControls.h"
#include "AGE_ComboBoxes.h"
#include "AGE_CheckBoxes.h"
//#include "AGE_ScrolledWindow.h"

#ifndef AGEFrame_h
#define AGEFrame_h

class AGE_Frame : public wxFrame
{
	public:

	AGE_Frame(const wxString& title);
	~AGE_Frame();

//	Constructions Methods

	void CreateGeneralControls();
	void CreateResearchControls();
	void CreateTechageControls();
	void CreateCivControls();
	void CreateUnitControls();
	void CreateUnitLineControls();
	void CreateGraphicsControls();
	void CreateTerrainControls();
	void CreateTerrainBorderControls();
	void CreateTerrainRestrictionControls();
	void CreateSoundControls();
	void CreatePlayerColorControls();

//	Other Events

	bool DataOpened;
	void OnGameVersionChange();
//	void OnTempBackup();
//	void OnUndoing(wxCommandEvent& Event);
//	void OnReload(wxCommandEvent& Event);
//	void OnSectionChange(wxCommandEvent& Event);
	void OnSave(wxCommandEvent& Event);
//	void OnReset(wxCommandEvent& Event);
//	void OnExecute(wxCommandEvent& Event);
//	void OnQuickExecute(wxCommandEvent& Event);
	void OnOpen(wxCommandEvent& Event);
	void OnExit(wxCloseEvent& Event);
	void OnMenuOption(wxCommandEvent& Event);

//	Updates user interface after changing data name.
	
	void OnKillFocus_TextControls(wxFocusEvent& Event);
	void OnSelection_ComboBoxes(wxCommandEvent& Event);
	void OnSelection_CheckBoxes(wxCommandEvent& Event);
	
	void OnKillFocus_Byte(wxFocusEvent& Event);
	void OnKillFocus_Short(wxFocusEvent& Event);
	void OnKillFocus_UnShort(wxFocusEvent& Event);
	void OnKillFocus_Long(wxFocusEvent& Event);
	void OnKillFocus_Float(wxFocusEvent& Event);
	void OnKillFocus_String(wxFocusEvent& Event);
	
	void OnKillFocus_ComboBoxByteEffectType(wxFocusEvent& Event); // for effects' name update
	void OnKillFocus_CheckBoxByte(wxFocusEvent& Event);
	void OnKillFocus_ComboBoxShort(wxFocusEvent& Event);
	
	void OnKillFocus_AutoCopy_Byte(wxFocusEvent& Event);
	void OnKillFocus_AutoCopy_ComboBoxByte(wxFocusEvent& Event);
	void OnKillFocus_AutoCopy_ComboBoxByteUnitType(wxFocusEvent& Event);
	void OnKillFocus_AutoCopy_CheckBoxByte(wxFocusEvent& Event);
	void OnKillFocus_AutoCopy_Short(wxFocusEvent& Event);
	void OnKillFocus_AutoCopy_ComboBoxShort(wxFocusEvent& Event);
	void OnKillFocus_AutoCopy_ComboBoxShortAttackType(wxFocusEvent& Event);
	void OnKillFocus_AutoCopy_CheckBoxShort(wxFocusEvent& Event);
	void OnKillFocus_AutoCopy_CheckBoxShortUnitSheepConversion(wxFocusEvent& Event);
	void OnKillFocus_AutoCopy_Float(wxFocusEvent& Event);
	void OnKillFocus_AutoCopy_Long(wxFocusEvent& Event);
	void OnKillFocus_AutoCopy_ComboBoxLong(wxFocusEvent& Event);
	void OnKillFocus_AutoCopy_String(wxFocusEvent& Event);
	
	void OnUpdate_ComboBoxByteEffectType(wxCommandEvent& Event); // for effects' name update
	void OnUpdate_CheckBoxByte(wxCommandEvent& Event);
	void OnUpdate_ComboBoxShort(wxCommandEvent& Event);
	void OnUpdate_CheckBoxShort(wxCommandEvent& Event);

	void OnUpdate_AutoCopy_ComboBoxByte(wxCommandEvent& Event);
	void OnUpdate_AutoCopy_ComboBoxByteUnitType(wxCommandEvent& Event);
	void OnUpdate_AutoCopy_ComboBoxShort(wxCommandEvent& Event);
	void OnUpdate_AutoCopy_ComboBoxShortAttackType(wxCommandEvent& Event);
	void OnUpdate_AutoCopy_ComboBoxLong(wxCommandEvent& Event);
	void OnUpdate_AutoCopy_CheckBoxByte(wxCommandEvent& Event);
	void OnUpdate_AutoCopy_CheckBoxShort(wxCommandEvent& Event);
	void OnUpdate_AutoCopy_CheckBoxShortUnitSheepConversion(wxCommandEvent& Event);

//	Other Methods

//	bool FileExists(const char * value);
	wxString SearchText, ExcludeText;
	bool SearchMatches(string CompareText);

//	General Events

	void ListGeneral();
	void OnGeneralSelect(wxCommandEvent& Event);
	void OnDataGridPage(wxCommandEvent& Event);
	void OnDataGridNext(wxCommandEvent& Event);
	void OnDataGridPrev(wxCommandEvent& Event);
	void OnVariableCalc(wxFocusEvent& Event);

	void ListBorders();
	void OnBordersSearch(wxCommandEvent& Event);
	void OnBordersSelect(wxCommandEvent& Event);
	void OnBordersCopy(wxCommandEvent& Event);
	void OnBordersPaste(wxCommandEvent& Event);
	string GetBorderName(short Index);

//	Research Events

	void ListResearchs();
	void OnResearchSearch(wxCommandEvent& Event);
	void OnResearchSelect(wxCommandEvent& Event);
	void OnResearchAdd(wxCommandEvent& Event);
	void OnResearchDelete(wxCommandEvent& Event);
	void OnResearchCopy(wxCommandEvent& Event);
	void OnResearchPaste(wxCommandEvent& Event);
	string GetResearchName(short Index);

//	Techage Events

	void ListTechages();
	void OnTechageSearch(wxCommandEvent& Event);
	void OnTechageSelect(wxCommandEvent& Event);
	void OnTechageAdd(wxCommandEvent& Event);
	void OnTechageDelete(wxCommandEvent& Event);
	void OnTechageCopy(wxCommandEvent& Event);
	void OnTechagePaste(wxCommandEvent& Event);
	void OnTechageRename(wxCommandEvent& Event);
	void OnTechageRenameGE2(wxCommandEvent& Event);
	string GetTechageName(short Index);

	void ListEffects(short Index);
	void OnEffectsSearch(wxCommandEvent& Event);
	void OnEffectsSelect(wxCommandEvent& Event);
	void OnEffectsAdd(wxCommandEvent& Event);
	void OnEffectsDelete(wxCommandEvent& Event);
	void OnEffectsCopy(wxCommandEvent& Event);
	void OnEffectsPaste(wxCommandEvent& Event);
	string GetEffectName(short Index, short TechID);

//	Civilization Events

	void ListCivs();
	void OnCivsSearch(wxCommandEvent& Event);
	void OnCivsSelect(wxCommandEvent& Event);
	void OnCivsAdd(wxCommandEvent& Event);
	void OnCivsDelete(wxCommandEvent& Event);
	void OnCivsCopy(wxCommandEvent& Event);
	void OnCivsPaste(wxCommandEvent& Event);
	string GetCivName(short Index);

	void ListResources(short Index);
	void OnResourcesSearch(wxCommandEvent& Event);
	void OnResourcesSelect(wxCommandEvent& Event);
	void OnResourcesAdd(wxCommandEvent& Event);
	void OnResourcesDelete(wxCommandEvent& Event);
	void OnResourcesCopy(wxCommandEvent& Event);
	void OnResourcesPaste(wxCommandEvent& Event);
	string GetResourceName(short Index, short CivID);

	void ListUnits(short CivID = -1);
	void OnUnitsSearch(wxCommandEvent& Event);
	void OnUnitsSelect(wxCommandEvent& Event);
	void OnUnitsAdd(wxCommandEvent& Event);
	void OnUnitsDelete(wxCommandEvent& Event);
	void OnUnitsCopy(wxCommandEvent& Event);
	void OnUnitsPaste(wxCommandEvent& Event);
	void OnUnitSubList(wxCommandEvent& Event);
	string GetUnitName(short Index, short CivID, bool Filter);
	
	void ListUnitDamageGraphics(short Index, short CivID);
	void OnUnitDamageGraphicsSearch(wxCommandEvent& Event);
	void OnUnitDamageGraphicsSelect(wxCommandEvent& Event);
	void OnUnitDamageGraphicsAdd(wxCommandEvent& Event);
	void OnUnitDamageGraphicsDelete(wxCommandEvent& Event);
	void OnUnitDamageGraphicsCopy(wxCommandEvent& Event);
	void OnUnitDamageGraphicsPaste(wxCommandEvent& Event);
	string GetUnitDamageGraphicName(short Index, short CivID, short UnitID);

	void ListUnitAttacks(short Index, short CivID);
	void OnUnitAttacksSearch(wxCommandEvent& Event);
	void OnUnitAttacksSelect(wxCommandEvent& Event);
	void OnUnitAttacksAdd(wxCommandEvent& Event);
	void OnUnitAttacksDelete(wxCommandEvent& Event);
	void OnUnitAttacksCopy(wxCommandEvent& Event);
	void OnUnitAttacksPaste(wxCommandEvent& Event);
	string GetUnitAttackName(short Index, short CivID, short UnitID);
	
	void ListUnitArmors(short Index, short CivID);
	void OnUnitArmorsSearch(wxCommandEvent& Event);
	void OnUnitArmorsSelect(wxCommandEvent& Event);
	void OnUnitArmorsAdd(wxCommandEvent& Event);
	void OnUnitArmorsDelete(wxCommandEvent& Event);
	void OnUnitArmorsCopy(wxCommandEvent& Event);
	void OnUnitArmorsPaste(wxCommandEvent& Event);
	string GetUnitArmorName(short Index, short CivID, short UnitID);
	
//	Unit Events
	
	void ListUnitHeads();
	void OnUnitHeadsSelect(wxCommandEvent& Event);

	void ListUnitCommands(short Index, short CivID);
	void OnUnitCommandsSearch(wxCommandEvent& Event);
	void OnUnitCommandsSelect(wxCommandEvent& Event);
	void OnUnitCommandsAdd(wxCommandEvent& Event);
	void OnUnitCommandsDelete(wxCommandEvent& Event);
	void OnUnitCommandsCopy(wxCommandEvent& Event);
	void OnUnitCommandsPaste(wxCommandEvent& Event);
	string GetUnitCommandName(short Index, short CivID, short UnitID);

//	Unitline Events

	void ListUnitLines();
	void OnUnitLinesSearch(wxCommandEvent& Event);
	void OnUnitLinesSelect(wxCommandEvent& Event);
	void OnUnitLinesAdd(wxCommandEvent& Event);
	void OnUnitLinesDelete(wxCommandEvent& Event);
	void OnUnitLinesCopy(wxCommandEvent& Event);
	void OnUnitLinesPaste(wxCommandEvent& Event);
	string GetUnitLineName(short Index);

	void ListUnitLineUnits(short Index);
	void OnUnitLineUnitsSearch(wxCommandEvent& Event);
	void OnUnitLineUnitsSelect(wxCommandEvent& Event);
	void OnUnitLineUnitsAdd(wxCommandEvent& Event);
	void OnUnitLineUnitsDelete(wxCommandEvent& Event);
	void OnUnitLineUnitsCopy(wxCommandEvent& Event);
	void OnUnitLineUnitsPaste(wxCommandEvent& Event);
	string GetUnitLineUnitName(short Index, short UnitLinesID);

//	Graphic Events

	void ListGraphics();
	void OnGraphicsSearch(wxCommandEvent& Event);
	void OnGraphicsSelect(wxCommandEvent& Event);
	void OnGraphicsAdd(wxCommandEvent& Event);
	void OnGraphicsDelete(wxCommandEvent& Event);
	void OnGraphicsCopy(wxCommandEvent& Event);
	void OnGraphicsPaste(wxCommandEvent& Event);
	string GetGraphicName(short Index);

	void ListGraphicDeltas(short Index);
	void OnGraphicDeltasSearch(wxCommandEvent& Event);
	void OnGraphicDeltasSelect(wxCommandEvent& Event);
	void OnGraphicDeltasAdd(wxCommandEvent& Event);
	void OnGraphicDeltasDelete(wxCommandEvent& Event);
	void OnGraphicDeltasCopy(wxCommandEvent& Event);
	void OnGraphicDeltasPaste(wxCommandEvent& Event);
	string GetGraphicDeltaName(short Index, short GraphicID);

	void ListGraphicAttackSounds(short Index);
	void OnGraphicAttackSoundsSearch(wxCommandEvent& Event);
	void OnGraphicAttackSoundsSelect(wxCommandEvent& Event);
	void OnGraphicAttackSoundsAdd(wxCommandEvent& Event);
	void OnGraphicAttackSoundsDelete(wxCommandEvent& Event);
	void OnGraphicAttackSoundsCopy(wxCommandEvent& Event);
	void OnGraphicAttackSoundsPaste(wxCommandEvent& Event);
	string GetGraphicAttackSoundName(short Index, short GraphicID);

//	Terrain Events

	void ListTerrains();
	void OnTerrainsSearch(wxCommandEvent& Event);
	void OnTerrainsSelect(wxCommandEvent& Event);
	void OnTerrainsAdd(wxCommandEvent& Event);
	void OnTerrainsDelete(wxCommandEvent& Event);
	void OnTerrainsCopy(wxCommandEvent& Event);
	void OnTerrainsPaste(wxCommandEvent& Event);
	string GetTerrainName(short Index);

//	Terrain Border Events
	
	void ListTerrainBorders();
	void OnTerrainBordersSearch(wxCommandEvent& Event);
	void OnTerrainBordersSelect(wxCommandEvent& Event);
	void OnTerrainBordersCopy(wxCommandEvent& Event);
	void OnTerrainBordersPaste(wxCommandEvent& Event);
	string GetTerrainBorderName(short Index);

	void ListTerrainBorderFrames(short Index);
	void OnTerrainBorderFramesSearch(wxCommandEvent& Event);
	void OnTerrainBorderFramesSelect(wxCommandEvent& Event);
	void OnTerrainBorderFramesCopy(wxCommandEvent& Event);
	void OnTerrainBorderFramesPaste(wxCommandEvent& Event);
	string GetTerrainBorderFrameName(short Index, short BorderID);

//	Terrain Restriction Events

	void ListTerrainRestrictions();
	void OnTerrainRestrictionsSearch(wxCommandEvent& Event);
//	void OnTerrainRestrictionsSelect(wxCommandEvent& Event);
	void OnTerrainRestrictionsTerrainSelect(wxCommandEvent& Event);
	void OnTerrainRestrictionsAdd(wxCommandEvent& Event);
	void OnTerrainRestrictionsDelete(wxCommandEvent& Event);
	void OnTerrainRestrictionsCopy(wxCommandEvent& Event);
	void OnTerrainRestrictionsPaste(wxCommandEvent& Event);
	void OnTerrainRestrictionsTerrainCopy(wxCommandEvent& Event);
	void OnTerrainRestrictionsTerrainPaste(wxCommandEvent& Event);
	string GetTerrainRestrictionName(short Index);

//	Sound Events

	void ListSounds();
	void OnSoundsSearch(wxCommandEvent& Event);
	void OnSoundsSelect(wxCommandEvent& Event);
	void OnSoundsAdd(wxCommandEvent& Event);
	void OnSoundsDelete(wxCommandEvent& Event);
	void OnSoundsCopy(wxCommandEvent& Event);
	void OnSoundsPaste(wxCommandEvent& Event);
	string GetSoundName(short Index);

	void ListSoundItems(short Index);
	void OnSoundItemsSearch(wxCommandEvent& Event);
	void OnSoundItemsSelect(wxCommandEvent& Event);
	void OnSoundItemsAdd(wxCommandEvent& Event);
	void OnSoundItemsDelete(wxCommandEvent& Event);
	void OnSoundItemsCopy(wxCommandEvent& Event);
	void OnSoundItemsPaste(wxCommandEvent& Event);
	string GetSoundItemName(short Index, short SoundID);
	
//	Player Color Events

	void ListPlayerColors();
	void OnPlayerColorsSearch(wxCommandEvent& Event);
	void OnPlayerColorsSelect(wxCommandEvent& Event);
	void OnPlayerColorsAdd(wxCommandEvent& Event);
	void OnPlayerColorsDelete(wxCommandEvent& Event);
	void OnPlayerColorsCopy(wxCommandEvent& Event);
	void OnPlayerColorsPaste(wxCommandEvent& Event);
	string GetPlayerColorName(short Index);

//	Application Variables

	bool PromptForFilesOnOpen;
	int AutoCopy;	// Complete.
	int SearchFilters;
	bool UseAnd[2];
	bool ShowUnknowns;
	bool ShowButtons;
//	bool UseUndo;
	bool NeedDat;
	bool SkipOpenDialog;
	wxFileConfig * Config;
//	wxFileConfig * Extraction;
	gdat::File * GenieFile;

/*	gdat::File FileBackup; // Can't copy the whole file?
	long EditCount;
	gdat::Unit UnitBackup[100][20];
	short IDtoRestore[100];
	gdat::Civ CivBackup[20];	// Only temporary solution!*/
	
	long TechTreePage;
	long TechTreeSize;
	long LastUnknownsPage;
	long LastUnknownsSize;
	gdat::Research ResearchCopy;
	short ResearchID;
	gdat::Techage TechageCopy;
	short TechID;
	gdat::TechageEffect EffectCopy;
	short EffectID;
	gdat::Civ CivCopy;
	short CivID;
	float ResourceCopy;
	short ResourceID;
	gdat::Unit UnitCopy;
	short UnitID;
	short UnitCivID;
	int RefreshLists;
	gdat::Unit UnitGraphics[20];	// This should be a vector equal to Civs.
	gdat::unit::DamageGraphic DamageGraphicCopy;
	short DamageGraphicID;
	gdat::unit::AttackOrArmor AttackCopy;
	short AttackID;
	gdat::unit::AttackOrArmor ArmorCopy;
	short ArmorID;
	gdat::UnitHeader UnitHeaderCopy;
	gdat::UnitCommand UnitCommandCopy;
	short CommandID;
	gdat::UnitLine UnitLineCopy;
	short UnitLineID;
	short UnitLineUnitCopy;
	short UnitLineUnitID;
	gdat::Graphic GraphicCopy;
	short GraphicID;
	gdat::GraphicDelta GraphicDeltaCopy;
	short DeltaID;
	gdat::GraphicAttackSound GraphicAttackSoundCopy;
	short AttackSoundID;
	gdat::Terrain TerrainCopy;
	short TerrainID;
	gdat::TerrainRestriction TerrainRestrictionCopy;
	short TerRestrictID;
	gdat::TerrainPassGraphic TerrainRestrictionSubCopy;
	short TerRestrictTerID;
	float TerrainRestrictionSubCopyAccess;
	gdat::Sound SoundCopy;
	short SoundID;
	gdat::SoundItem SoundItemCopy;
	short SoundItemID;
	gdat::PlayerColour PlayerColorCopy;
	short ColorID;
	gdat::TerrainBorder TerrainBorderCopy;
	short BorderID;
	gdat::TBFrameData TBFrameDataCopy;
	short FrameID;

	bool Added;
	int GameVersion;
	int DatUsed;
	int SaveGameVersion;
	bool SaveDat;
	bool SaveApf;
	wxString DriveLetter;
	wxString DatFileName;
	wxString ApfFileName;
	wxString SaveDatFileName;
	wxString SaveApfFileName;
	int LangsUsed; // 0x01 Lang.dll, 0x02, LangX1.dll, 0x04 LangX1P1.dll
	wxString LangFileName;
	wxString LangX1FileName;
	wxString LangX1P1FileName;

	HINSTANCE LanguageDll[3];
	string LanguageDllString(int ID);

//	Constants, remove unneeded entries.

	enum
	{
		MenuOption_Prompt,
		MenuOption_Unknowns,
		MenuOption_Buttons,
//		MenuOption_Undo,
		MenuOption_NoAuto,
		MenuOption_Include,
		MenuOption_Exclude,
		MenuOption_Tips,
		MenuOption_About,
		MenuOption_NoExtra,
		MenuOption_1stFilters,
		MenuOption_2ndFilters,
		ToolBar_Open,
		ToolBar_Save,
	};

//	User Interface	
	
	wxMenuBar * MenuBar_Main;
	wxMenu * SubMenu_Options;
	wxMenu * SubMenu_CivAutoCopy;
	wxMenu * SubMenu_SearchFilters;
	wxMenu * SubMenu_Help;

	wxNotebook * TabBar_Main;

	wxPanel * Tab_General;
	wxPanel * Tab_Research;
	wxPanel * Tab_Techage;
	wxPanel * Tab_Civs;
	wxPanel * Tab_Units;	// Unit tab
	wxPanel * Tab_UnitLine;
	wxPanel * Tab_Graphics;
	wxPanel * Tab_Terrains;
	wxPanel * Tab_TerrainBorders;
	wxPanel * Tab_TerrainRestrictions;
	wxPanel * Tab_Sounds;
	wxPanel * Tab_PlayerColors;

//	General user interface
	
	wxBoxSizer * General_Main;
	wxBoxSizer * General_TopRow;
	wxButton * General_Refresh;
	wxStaticText * General_Text_CalcBoxes;
	wxTextCtrl * General_CalcBoxes[5];
	wxScrolledWindow * General_Scroller;
	wxBoxSizer * General_ScrollerWindows;
	wxBoxSizer * General_ScrollerWindowsSpace;
	wxBoxSizer * General_Holder_TerrainHeader;
	wxGridSizer * General_Grid_TerrainHeader;
	wxStaticText * General_Text_TerrainHeader;
	TextCtrl_Byte * General_TerrainHeader[138];
	
	wxBoxSizer * Borders_Main;
	wxBoxSizer * Borders_ListArea;
	wxStaticBoxSizer * Borders_Borders;
	wxGridSizer * Borders_Borders_Buttons;
	wxTextCtrl * Borders_Borders_Search;
	wxTextCtrl * Borders_Borders_Search_R;
	wxListBox * Borders_Borders_List;
	wxButton * Borders_Copy;
	wxButton * Borders_Paste;
	wxBoxSizer * Borders_DataArea;
	wxBoxSizer * Borders_DataTopRow;
	wxGridSizer * Borders_Data1;
	wxBoxSizer * Borders_FrameData;
	wxStaticBoxSizer * Borders_Frames;
	wxGridSizer * Borders_Frames_Buttons;
	wxTextCtrl * Borders_Frames_Search;
	wxTextCtrl * Borders_Frames_Search_R;
	wxListBox * Borders_Frames_List;
	wxButton * Frames_Copy;
	wxButton * Frames_Paste;
	wxBoxSizer * Borders_Holder_FrameArea;
	wxGridSizer * Borders_Unknonws;
	wxBoxSizer * Borders_Holder_BorderEnabled;
	wxBoxSizer * Borders_Holder_BorderEnabled1;
	wxStaticText * Borders_Text_BorderEnabled;
	TextCtrl_Short * Borders_BorderEnabled;
	CheckBox_Short * Borders_CheckBox_BorderEnabled;
	wxBoxSizer * Borders_Holder_BorderName[2];
	wxStaticText * Borders_Text_BorderName[2];
	TextCtrl_String * Borders_BorderName[2];
	wxBoxSizer * Borders_Holder_BorderRessourceID;
	wxStaticText * Borders_Text_BorderRessourceID;
	TextCtrl_Long * Borders_BorderRessourceID;
	wxBoxSizer * Borders_Holder_BorderUnknown3;
	wxStaticText * Borders_Text_BorderUnknown3;
	TextCtrl_Long * Borders_BorderUnknown3;
	wxBoxSizer * Borders_Holder_BorderUnknown4;
	wxStaticText * Borders_Text_BorderUnknown4;
	TextCtrl_Long * Borders_BorderUnknown4;
	wxBoxSizer * Borders_Holder_BorderColors;
	wxGridSizer * Borders_Grid_BorderColors;
	wxStaticText * Borders_Text_BorderColors;
	TextCtrl_Byte * Borders_BorderColors[3];
	wxBoxSizer * Borders_Holder_BorderUnknown5;
	wxStaticText * Borders_Text_BorderUnknown5;
	TextCtrl_Byte * Borders_BorderUnknown5;
	wxBoxSizer * Borders_Holder_BorderUnknown6;
	wxStaticText * Borders_Text_BorderUnknown6;
	TextCtrl_Long * Borders_BorderUnknown6;
	wxBoxSizer * Borders_Holder_BorderUnknown7;
	wxStaticText * Borders_Text_BorderUnknown7;
	TextCtrl_Long * Borders_BorderUnknown7;
	wxBoxSizer * Borders_Holder_BorderFrameID;
	wxStaticText * Borders_Text_BorderFrameID;
	TextCtrl_Short * Borders_BorderFrameID;
	wxBoxSizer * Borders_Holder_BorderFlag1;
	wxStaticText * Borders_Text_BorderFlag1;
	TextCtrl_Short * Borders_BorderFlag1;
	wxBoxSizer * Borders_Holder_BorderFlag2;
	wxStaticText * Borders_Text_BorderFlag2;
	TextCtrl_Short * Borders_BorderFlag2;
	wxBoxSizer * Borders_Holder_BorderFrameCount;
	wxStaticText * Borders_Text_BorderFrameCount;
	TextCtrl_Short * Borders_BorderFrameCount;
	wxBoxSizer * Borders_Holder_BorderUnknown8;
	wxStaticText * Borders_Text_BorderUnknown8;
	TextCtrl_Short * Borders_BorderUnknown8;
	wxBoxSizer * Borders_Holder_BorderTerrain;
	wxStaticText * Borders_Text_BorderTerrain;
	TextCtrl_Short * Borders_BorderTerrain;
	ComboBox_Short * Borders_ComboBox_BorderTerrain;
	wxBoxSizer * Borders_Holder_BorderUnknown10;
	wxStaticText * Borders_Text_BorderUnknown10;
	TextCtrl_Short * Borders_BorderUnknown10;
	
	wxGridSizer * General_Grid_Variables;
	wxBoxSizer * General_Holder_SUnknown7;
	wxStaticText * General_Text_SUnknown7;
	TextCtrl_Byte * General_SUnknown7;
	wxBoxSizer * General_Holder_SUnknown8;
	wxStaticText * General_Text_SUnknown8;
	TextCtrl_Byte * General_SUnknown8;
	wxBoxSizer * General_Holder_SUnknown2;
	wxStaticText * General_Text_SUnknown2;
	TextCtrl_Long * General_SUnknown2;
	wxBoxSizer * General_Holder_SUnknown3;
	wxStaticText * General_Text_SUnknown3;
	TextCtrl_Long * General_SUnknown3;
	wxBoxSizer * General_Holder_SUnknown4;
	wxStaticText * General_Text_SUnknown4;
	TextCtrl_Long * General_SUnknown4;
	wxBoxSizer * General_Holder_SUnknown5;
	wxStaticText * General_Text_SUnknown5;
	TextCtrl_Long * General_SUnknown5;
	
	wxBoxSizer * General_Holder_TechTree;
	wxBoxSizer * General_Holder_TechTreeTop;
	wxStaticText * General_Text_TechTree;
	wxTextCtrl * General_TechTreePicker;
	wxButton * General_TechTreeNext;
	wxButton * General_TechTreePrev;
	wxStaticText * General_TechTreeSize;
	wxGridSizer * General_Grid_TechTree;
	TextCtrl_Byte * General_TechTree[256];

	wxBoxSizer * General_Holder_LastUnknowns;
	wxBoxSizer * General_Holder_LastUnknownsTop;
	wxStaticText * General_Text_LastUnknowns;
	wxTextCtrl * General_LastUnknownsPicker;
	wxButton * General_LastUnknownsNext;
	wxButton * General_LastUnknownsPrev;
	wxStaticText * General_LastUnknownsSize;
	wxGridSizer * General_Grid_LastUnknowns;
	TextCtrl_Byte * General_LastUnknowns[256];
	
//	Researchs user interface

	wxBoxSizer * Research_Main;
	wxBoxSizer * Research_ListArea;
	wxGridSizer * Research_Research_Buttons;
	wxBoxSizer * Research_DataArea;
	wxScrolledWindow * Research_Scroller;
	wxBoxSizer * Research_ScrollerWindows;
	wxBoxSizer * Research_ScrollerWindowsSpace;
	wxGridSizer * Research_Grid_MiscArea1;
	wxBoxSizer * Research_Holder_LangDLLArea;
	wxBoxSizer * Research_Holder_Misc2;
	wxBoxSizer * Research_Holder_PointerArea;
	wxBoxSizer * Research_Holder_Names;

	wxStaticBoxSizer * Research_Research;
	wxTextCtrl * Research_Research_Search;
	wxTextCtrl * Research_Research_Search_R;
	wxCheckBox * Research_Research_UseAnd;
	wxListBox * Research_Research_List;
	wxButton * Research_Add;
	wxButton * Research_Delete;
	wxButton * Research_Copy;
	wxButton * Research_Paste;

	wxBoxSizer * Research_Holder_RequiredTechArea;
	wxGridSizer * Research_Holder_RequiredTechs;
	wxStaticText * Research_Text_RequiredTechArea;
	TextCtrl_Short * Research_RequiredTechs[6];
	ComboBox_Short * Research_ComboBox_RequiredTechs[6];
	wxBoxSizer * Research_Holder_RequiredTechCount;
	wxStaticText * Research_Text_RequiredTechCount;
	TextCtrl_Short * Research_RequiredTechCount;
	
	wxStaticBoxSizer * Research_Holder_CostHeader;
	wxBoxSizer * Research_Holder_CostType;
	wxBoxSizer * Research_Holder_CostAmount;
	wxBoxSizer * Research_Holder_CostUsed;
	wxStaticText * Research_Text_Resources;
	wxGridSizer * Research_ResourceGrid;
	TextCtrl_Short * Research_Resources[3];
	ComboBox_Short * Research_ComboBox_Resources[3];
	wxStaticText * Research_Text_Amount;
	TextCtrl_Short * Research_Amount[3];
	wxStaticText * Research_Text_Used;
	TextCtrl_Byte * Research_Used[3];
	CheckBox_Byte * Research_CheckBox_Used[3];

	wxBoxSizer * Research_Holder_Civ;
	wxStaticText * Research_Text_Civ;
	TextCtrl_Short * Research_Civ;
	ComboBox_Short * Research_ComboBox_Civ;

	wxBoxSizer * Research_Holder_FullTechMode;
	wxStaticText * Research_Text_FullTechMode;
	TextCtrl_Short * Research_FullTechMode;
	CheckBox_Short * Research_CheckBox_FullTechMode;

	wxBoxSizer * Research_Holder_ResearchLocation;
	wxStaticText * Research_Text_ResearchLocation;
	TextCtrl_Short * Research_ResearchLocation;
	ComboBox_Short * Research_ComboBox_ResearchLocation;

	wxBoxSizer * Research_Holder_LangDllName;
	wxStaticText * Research_Text_LangDllName;
	TextCtrl_Short * Research_LangDllName;
	wxStaticText * Research_DLL_LangDllName;

	wxBoxSizer * Research_Holder_LangDllDescription;
	wxStaticText * Research_Text_LangDllDescription;
	TextCtrl_Short * Research_LangDllDescription;
	wxStaticText * Research_DLL_LangDllDescription;

	wxBoxSizer * Research_Holder_ResearchTime;
	wxStaticText * Research_Text_ResearchTime;
	TextCtrl_Short * Research_ResearchTime;

	wxBoxSizer * Research_Holder_TechID;
	wxStaticText * Research_Text_TechID;
	TextCtrl_Short * Research_TechID;
	ComboBox_Short * Research_ComboBox_TechID;

	wxBoxSizer * Research_Holder_Type;
	wxStaticText * Research_Text_Type;
	TextCtrl_Short * Research_Type;

	wxBoxSizer * Research_Holder_IconID;
	wxStaticText * Research_Text_IconID;
	TextCtrl_Short * Research_IconID;

	wxBoxSizer * Research_Holder_ButtonID;
	wxStaticText * Research_Text_ButtonID;
	TextCtrl_Byte * Research_ButtonID;

	wxBoxSizer * Research_Holder_Pointers[3];
	wxStaticText * Research_Text_Pointers[3];
	TextCtrl_Long * Research_Pointers[3];	// long text = TextCtrl_Long

	wxBoxSizer * Research_Holder_Name[2];
	wxStaticText * Research_Text_Name[2];
	TextCtrl_String * Research_Name[2];

//	Techs user interface

	wxBoxSizer * Techs_Main;
	wxBoxSizer * Techs_ListArea;
	wxGridSizer * Techs_Techs_Buttons;
	wxBoxSizer * Effects_ListArea;
	wxGridSizer * Techs_Effects_Buttons;
	wxBoxSizer * Effects_DataAreaProperties;
	wxBoxSizer * Effects_Holder_DataA;
	wxBoxSizer * Effects_Holder_DataB;
	wxBoxSizer * Effects_Holder_DataC;
	wxBoxSizer * Effects_Holder_DataD;
	wxBoxSizer * Effects_Holder_DataE;	// for attack/armor amount
	wxBoxSizer * Effects_Holder_DataF;	// for attack/armor class
	wxBoxSizer * Effects_Holder_A;
	wxBoxSizer * Effects_Holder_B;
	wxBoxSizer * Effects_Holder_C;
	wxBoxSizer * Effects_Holder_D;
	wxBoxSizer * Effects_Holder_E;	// for attack/armor amount
	wxBoxSizer * Effects_Holder_F;	// for attack/armor class
	
	wxStaticText * Effects_Text_E;
	wxTextCtrl * Effects_E;	// amount
	wxStaticText * Effects_Info_E;
	wxStaticText * Effects_Text_F;
	TextCtrl_Short * Effects_F;	// class
//	wxOwnerDrawnComboBox * Attacks_ComboBox_Class[2];	// class
	wxStaticText * Effects_Info_F;
	
	wxStaticBoxSizer * Techs_Techs;
	wxTextCtrl * Techs_Techs_Search;
	wxTextCtrl * Techs_Techs_Search_R;
//	wxCheckBox * Techs_Techs_UseAnd;
	wxListBox * Techs_Techs_List;
	wxButton * Techs_Techs_Rename;
	wxButton * Techs_Techs_Restore;
	wxButton * Techs_Techs_Add;
	wxButton * Techs_Techs_Delete;
	wxButton * Techs_Techs_Copy;
	wxButton * Techs_Techs_Paste;

	wxBoxSizer * Techs_Holder_Name;
	wxStaticText * Techs_Text_Name;
	TextCtrl_String * Techs_Name;

	wxStaticBoxSizer * Techs_Effects;
	wxTextCtrl * Techs_Effects_Search;
	wxTextCtrl * Techs_Effects_Search_R;
	wxCheckBox * Techs_Effects_UseAnd;
	wxListBox * Techs_Effects_List;
	wxButton * Techs_Effects_Add;
	wxButton * Techs_Effects_Delete;
	wxButton * Techs_Effects_Copy;
	wxButton * Techs_Effects_Paste;

	wxBoxSizer * Effects_DataArea;

	wxBoxSizer * Effects_Holder_Type;
	wxBoxSizer * Effects_Holder_Type2;
	wxStaticText * Effects_Text_Type;
	ComboBox_Byte_EffectType * Effects_ComboBox_Type;
	TextCtrl_Byte * Effects_Type;
	wxStaticBoxSizer * Effects_Holder_Data;
	wxStaticText * Effects_Text_A;
	TextCtrl_Short * Effects_A;
	wxBoxSizer * Effects_ComboBox_A;	// Space reserver, never used.
	ComboBox_Short * Effects_ComboBox_UnitsA;	// for Effects 0, 2, 3, 4, 5
	ComboBox_Short * Effects_ComboBox_ResourcesA;	// for Effects 1, 6
	ComboBox_Short * Effects_ComboBox_ResearchsA;	// for Effects 101, 103
	wxStaticText * Effects_Info_A;
	wxStaticText * Effects_Text_B;
	TextCtrl_Short * Effects_B;
	wxBoxSizer * Effects_ComboBox_B;	// Space reserver, never used.
	CheckBox_Short * Effects_CheckBox_ModeB;	// for Effects 1, 2
	ComboBox_Short * Effects_ComboBox_UnitsB;	// for Effects 3
	ComboBox_Short * Effects_ComboBox_ResourcesB;	// for Effects 101
	wxStaticText * Effects_Info_B;
	wxStaticText * Effects_Text_C;
	TextCtrl_Short * Effects_C;
	wxBoxSizer * Effects_ComboBox_C;	// Space reserver, never used.
	CheckBox_Short * Effects_CheckBox_ModeC;	// for Effects 101, 103
	ComboBox_Short * Effects_ComboBox_AttributesC;	// for Effects 0, 4, 5
	wxStaticText * Effects_Info_C;
	wxStaticText * Effects_Text_D;
	TextCtrl_Float * Effects_D;
	wxBoxSizer * Effects_ComboBox_D;	// Space reserver, never used.
	ComboBox_Float * Effects_ComboBox_ResearchsD;	// for Effects 102
	wxStaticText * Effects_Info_D;
	wxHyperlinkCtrl * Effects_Link;
	
//	Civs user interface

	wxBoxSizer * Civs_Main;
	wxBoxSizer * Civs_ListArea;
	wxGridSizer * Civs_Civs_Buttons;
	wxStaticBoxSizer * Civs_Civs;
	wxTextCtrl * Civs_Civs_Search;
	wxTextCtrl * Civs_Civs_Search_R;
//	wxCheckBox * Civs_Civs_UseAnd;
	wxListBox * Civs_Civs_List;
	wxButton * Civs_Add;
	wxButton * Civs_Delete;
	wxButton * Civs_Copy;
	wxButton * Civs_Paste;

	wxBoxSizer * Civs_DataArea;
	wxGridSizer * Civs_DataGrid1;
	wxGridSizer * Civs_DataGrid2;
	wxGridSizer * Civs_DataGrid3;
	wxStaticText * Civs_Text_One;
	wxBoxSizer * Civs_Holder_One;
	TextCtrl_Byte * Civs_One;
	wxBoxSizer * Civs_Holder_Name[2];
	wxStaticText * Civs_Text_Name[2];
	TextCtrl_String * Civs_Name[2];
	wxBoxSizer * Civs_Holder_SUnknown1;
	wxStaticText * Civs_Text_SUnknown1;
	TextCtrl_Short * Civs_SUnknown1[4];
	wxBoxSizer * Civs_Holder_TechTree;
	wxStaticText * Civs_Text_TechTree;
	TextCtrl_Short * Civs_TechTree;
	ComboBox_Short * Civs_ComboBox_TechTree;
	wxBoxSizer * Civs_Holder_TeamBonus;
	wxStaticText * Civs_Text_TeamBonus;
	TextCtrl_Short * Civs_TeamBonus;
	ComboBox_Short * Civs_ComboBox_TeamBonus;
	wxBoxSizer * Civs_Holder_GraphicSet;
	wxStaticText * Civs_Text_GraphicSet;
	TextCtrl_Byte * Civs_GraphicSet;
	wxBoxSizer * Civs_Holder_Resources;
	wxStaticBoxSizer * Civs_Resources;
	wxTextCtrl * Civs_Resources_Search;
	wxTextCtrl * Civs_Resources_Search_R;
//	wxCheckBox * Civs_Resources_UseAnd;
	wxListBox * Civs_Resources_List;
	wxGridSizer * Civs_Resources_Buttons;
	wxButton * Resources_Add;
	wxButton * Resources_Delete;
	wxButton * Resources_Copy;
	wxButton * Resources_Paste;
	wxBoxSizer * Civs_Resources_Data;
	wxBoxSizer * Civs_Holder_ResourceValue;
	wxStaticText * Civs_Text_ResourceValue;
	TextCtrl_Float * Civs_ResourceValue;
	wxHyperlinkCtrl * Civs_Holder_Resources_Link;

//	Units user interface

//	Data container types:
/*
	wxBoxSizer * invisible_borders_window;
	wxStaticBoxSizer * visible_borders_window;
	wxCollapsiblePane * hide_button_window;	// Doesn't work!
	wxScrollBar * window_scroller;
	wxTextCtrl * editable_text;
	wxComboBox * drop_down_list;
	wxCheckBoc * check_box;
	wxStaticText * uneditable_text;
	wxHyperlinkCtrl * web_link;
	
//	Own text controls
	
	VBoolTextCtrl * text 0 or 1;	DOES NOT EXIST, CREATE? DON'T!
	TextCtrl_Byte * text -128 to 127;
	TextCtrl_Float * text +/- 3.4e +/- 38 (~7 digits);
	TextCtrl_Long * text -2147483648 to 2147483647;
	TextCtrl_Short * text -32768 to 32767;
	TextCtrl_String * text pure text;
*/
//	Data Containers
//	Type 10+

	wxScrolledWindow * Units_Scroller;	// Scrollable unit section
	
	TextCtrl_Byte * Units_Type;
	wxOwnerDrawnComboBox * Units_ComboBox_Type;
	TextCtrl_Short * Units_ID1;
	TextCtrl_Short * Units_LanguageDllName;
	wxStaticText * Units_DLL_LanguageDllName;
	TextCtrl_Short * Units_LanguageDllCreation;
	wxStaticText * Units_DLL_LanguageDllCreation;
	TextCtrl_Short * Units_Class;
	ComboBox_Short * Units_ComboBox_Class[3];
	TextCtrl_Short * Units_StandingGraphic[2];
	ComboBox_Short * Units_ComboBox_StandingGraphic[2];
	TextCtrl_Short * Units_DyingGraphic[2];
	ComboBox_Short * Units_ComboBox_DyingGraphic[2];
	TextCtrl_Byte * Units_DeathMode;
	CheckBox_Byte * Units_CheckBox_DeathMode;
	TextCtrl_Short * Units_HitPoints;
	TextCtrl_Float * Units_LineOfSight;
	TextCtrl_Byte * Units_GarrisonCapacity;
	TextCtrl_Float * Units_SizeRadius[2];
	TextCtrl_Float * Units_HPBarHeight1;
	TextCtrl_Short * Units_TrainSound[2];
	ComboBox_Short * Units_ComboBox_TrainSound[2];
	TextCtrl_Short * Units_DeadUnitID;
	ComboBox_Short * Units_ComboBox_DeadUnitID;
	TextCtrl_Byte * Units_PlacementMode;
	TextCtrl_Byte * Units_AirMode;
	CheckBox_Byte * Units_CheckBox_AirMode;
	TextCtrl_Short * Units_IconID;
	TextCtrl_Byte * Units_HideInEditor;
	CheckBox_Byte * Units_CheckBox_HideInEditor;
	TextCtrl_Short * Units_Unknown1;
	TextCtrl_Short * Units_Enabled;
	CheckBox_Short * Units_CheckBox_Enabled;
	TextCtrl_Short * Units_PlacementBypassTerrain[2];
	ComboBox_Short * Units_ComboBox_PlacementBypassTerrain[2];
	TextCtrl_Short * Units_PlacementTerrain[2];
	ComboBox_Short * Units_ComboBox_PlacementTerrain[2];
	TextCtrl_Float * Units_EditorRadius[2];
	TextCtrl_Byte * Units_BuildingMode;
	TextCtrl_Byte * Units_VisibleInFog;
	CheckBox_Byte * Units_CheckBox_VisibleInFog;
	TextCtrl_Short * Units_TerrainRestriction;
	ComboBox_Short * Units_ComboBox_TerrainRestriction;
	TextCtrl_Byte * Units_FlyMode;
	CheckBox_Byte * Units_CheckBox_FlyMode;
	TextCtrl_Short * Units_ResourceCapacity;
	TextCtrl_Float * Units_ResourceDecay;
	TextCtrl_Byte * Units_BlastType;
	TextCtrl_Byte * Units_Unknown2;
	TextCtrl_Byte * Units_InteractionMode;
	TextCtrl_Byte * Units_MinimapMode;
	TextCtrl_Short * Units_CommandAttribute;
	TextCtrl_Short * Units_Unknown3;
	TextCtrl_Short * Units_Unknown3B;
	TextCtrl_Byte * Units_Unknown3a;
	TextCtrl_Short * Units_LanguageDllHelp;
	wxStaticText * Units_DLL_LanguageDllHelp;
	TextCtrl_Short * Units_HotKey[4];
	wxStaticText * Units_DLL_HotKey4;
	TextCtrl_Byte * Units_Unknown4;
	TextCtrl_Byte * Units_Unknown5;
	TextCtrl_Byte * Units_Unselectable;
	CheckBox_Byte * Units_CheckBox_Unselectable;
	TextCtrl_Byte * Units_Unknown6;
	TextCtrl_Byte * Units_Unknown7;
	TextCtrl_Byte * Units_Unknown8;
	TextCtrl_Byte * Units_SelectionMask;
	TextCtrl_Byte * Units_SelectionShapeType;
	TextCtrl_Byte * Units_SelectionShape;
	TextCtrl_Byte * Units_Attribute;
	TextCtrl_Byte * Units_Civ;
	ComboBox_Byte * Units_ComboBox_Civ;
	TextCtrl_Byte * Units_Unknown9[2];
	TextCtrl_Byte * Units_SelectionEffect;
	TextCtrl_Byte * Units_EditorSelectionColour;
	wxBoxSizer * Units_SelectionRadiusBox;
	TextCtrl_Float * Units_SelectionRadius[2];
	TextCtrl_Float * Units_HPBarHeight2;
	TextCtrl_Short * ResourceStorage_Type[3];
	ComboBox_Short * ResourceStorage_ComboBox_Type[3];
	TextCtrl_Float * ResourceStorage_Amount[3];
	TextCtrl_Byte * ResourceStorage_Enabled[3];
	TextCtrl_Byte * Units_DamageGraphicCount;
	TextCtrl_Short * Units_SelectionSound;
	ComboBox_Short * Units_ComboBox_SelectionSound;
	TextCtrl_Short * Units_DyingSound;
	ComboBox_Short * Units_ComboBox_DyingSound;
	TextCtrl_Short * Units_AttackSound;
	ComboBox_Short * Units_ComboBox_AttackSound;
	TextCtrl_String * Units_Name;
	TextCtrl_String * Units_Name2;
	TextCtrl_Short * Units_Unitline;
	ComboBox_Short * Units_ComboBox_Unitline;
	TextCtrl_Byte * Units_MinTechLevel;
	TextCtrl_Short * Units_ID2;
	TextCtrl_Short * Units_ID3;

//	Type 20+

	TextCtrl_Float * Units_Speed;

//	Type 30+

	TextCtrl_Short * Units_WalkingGraphic[2];
	ComboBox_Short * Units_ComboBox_WalkingGraphic[2];
	TextCtrl_Float * Units_RotationSpeed;
	TextCtrl_Byte * Units_Unknown11;
	TextCtrl_Short * Units_TrackingUnit;
	ComboBox_Short * Units_ComboBox_TrackingUnit;
	TextCtrl_Byte * Units_TrackingUnitUsed;
	TextCtrl_Float * Units_TrackingUnitDensity;
	TextCtrl_Float * Units_Unknown12;
	TextCtrl_Byte * Units_Unknown16[17];

//	Type 40+

	TextCtrl_Short * Units_SheepConversion;
	CheckBox_Short_ZeroIsYes * Units_CheckBox_SheepConversion;
	TextCtrl_Float * Units_SearchRadius;
	TextCtrl_Float * Units_WorkRate;
	TextCtrl_Short * Units_DropSite[2];
	ComboBox_Short * Units_ComboBox_DropSite[2];
	TextCtrl_Byte * Units_VillagerMode;
	TextCtrl_Short * Units_MoveSound;
	ComboBox_Short * Units_ComboBox_MoveSound;
	TextCtrl_Short * Units_StopSound;
	ComboBox_Short * Units_ComboBox_StopSound;
	TextCtrl_Byte * Units_AnimalMode;
	CheckBox_Byte * Units_CheckBox_AnimalMode;
	TextCtrl_Byte * Units_Exists;
	TextCtrl_Short * Units_CommandCount;

//	Type 60+

	TextCtrl_Byte * Units_Unknown20[2];
	TextCtrl_Short * Units_AttackCount;
	TextCtrl_Short * Units_ArmourCount;
	TextCtrl_Short * Units_Unknown21;
	TextCtrl_Float * Units_MaxRange;
	TextCtrl_Float * Units_BlastRadius;
	TextCtrl_Float * Units_ReloadTime1;
	TextCtrl_Short * Units_ProjectileUnitID;
	ComboBox_Short * Units_ComboBox_ProjectileUnitID;
	TextCtrl_Short * Units_AccuracyPercent;
	TextCtrl_Byte * Units_TowerMode;
	CheckBox_Byte * Units_CheckBox_TowerMode;
	TextCtrl_Short * Units_Delay;
	TextCtrl_Float * Units_GraphicDisplacement[3];
	TextCtrl_Byte * Units_BlastLevel;
	TextCtrl_Float * Units_MinRange;
	TextCtrl_Float * Units_GarrisonRecoveryRate;
	TextCtrl_Short * Units_AttackGraphic;
	ComboBox_Short * Units_ComboBox_AttackGraphic;
	TextCtrl_Short * Units_DisplayedMeleeArmour;
	TextCtrl_Short * Units_DisplayedAttack;
	TextCtrl_Float * Units_DisplayedRange;
	TextCtrl_Float * Units_ReloadTime2;

//	Type 60 only

	TextCtrl_Byte * Units_StretchMode;
	TextCtrl_Byte * Units_CompensationMode;
	TextCtrl_Byte * Units_DropAnimationMode;
	TextCtrl_Byte * Units_PenetrationMode;
	TextCtrl_Byte * Units_Unknown24;
	TextCtrl_Float * Units_ProjectileArc;

//	Type 70+

	TextCtrl_Short * Units_CostType[3];
	ComboBox_Short * Units_ComboBox_CostType[3];
	TextCtrl_Short * Units_CostAmount[3];
	TextCtrl_Short * Units_CostUsed[3];
	CheckBox_Short * Units_CheckBox_CostUsed[3];
	TextCtrl_Short * Units_TrainTime;
	TextCtrl_Short * Units_TrainLocationID;
	ComboBox_Short * Units_ComboBox_TrainLocationID;
	TextCtrl_Byte * Units_ButtonID;
	TextCtrl_Byte * Units_Unknown26;
	TextCtrl_Short * Units_Unknown27[3];
	TextCtrl_Byte * Units_Unknown28;
	TextCtrl_Byte * Units_MissileGraphicDelay;
	TextCtrl_Byte * Units_HeroMode;
	CheckBox_Byte * Units_CheckBox_HeroMode;
	TextCtrl_Short * Units_GarrisonGraphic[2];
	ComboBox_Short * Units_ComboBox_GarrisonGraphic[2];
	TextCtrl_Float * Units_AttackMissileDuplicationAmount1;
	TextCtrl_Byte * Units_AttackMissileDuplicationAmount2;
	TextCtrl_Float * Units_AttackMissileDuplicationSpawning[3];
	TextCtrl_Long * Units_AttackMissileDuplicationUnit;
	ComboBox_Long * Units_ComboBox_AttackMissileDuplicationUnit;
	TextCtrl_Long * Units_AttackMissileDuplicationGraphic;
	ComboBox_Long * Units_ComboBox_AttackMissileDuplicationGraphic;
	TextCtrl_Byte * Units_Unknown29;
	TextCtrl_Short * Units_DisplayedPierceArmour;

//	Type 80

	TextCtrl_Short * Units_ConstructionGraphicID;
	ComboBox_Short * Units_ComboBox_ConstructionGraphicID;
	TextCtrl_Short * Units_SnowGraphicID;
	ComboBox_Short * Units_ComboBox_SnowGraphicID;
	TextCtrl_Short * Units_AdjacentMode;
	CheckBox_Short * Units_CheckBox_AdjacentMode;
	TextCtrl_Byte * Units_Unknown31;
	TextCtrl_Byte * Units_Unknown31b;
	CheckBox_Byte * Units_CheckBox_Unknown31b;
	TextCtrl_Short * Units_StackUnitID;
	ComboBox_Short * Units_ComboBox_StackUnitID;
	TextCtrl_Short * Units_TerrainID;
	ComboBox_Short * Units_ComboBox_TerrainID;
	TextCtrl_Short * Units_Unknown32;
	TextCtrl_Short * Units_ResearchID;
	ComboBox_Short * Units_ComboBox_ResearchID;
	TextCtrl_Byte * Units_Unknown33;
	TextCtrl_Short * Units_AnnexUnit[4];
	ComboBox_Short * Units_ComboBox_AnnexUnit[4];
	TextCtrl_Float * Units_AnnexUnitMisplacement[4][2];
	TextCtrl_Short * Units_HeadUnit;
	ComboBox_Short * Units_ComboBox_HeadUnit;
	TextCtrl_Short * Units_TransformUnit;
	ComboBox_Short * Units_ComboBox_TransformUnit;
	TextCtrl_Short * Units_Unknown34;
	TextCtrl_Short * Units_ConstructionSound;
	ComboBox_Short * Units_ComboBox_ConstructionSound;
	TextCtrl_Byte * Units_GarrisonType;
	ComboBox_Byte * Units_ComboBox_GarrisonType;
	TextCtrl_Float * Units_GarrisonHealRate;
	TextCtrl_Long * Units_Unknown35;
	TextCtrl_Short * Units_Unknown36;
	TextCtrl_Byte * Units_Unknown37[6];
	
//	Data Container Names
//	Type 10+

	wxStaticText * Units_Text_Type;
	wxStaticText * Units_Text_ID1;
	wxStaticText * Units_Text_LanguageDllName;
	wxStaticText * Units_Text_LanguageDllCreation;
	wxStaticText * Units_Text_Class;
	wxStaticText * Units_Text_StandingGraphic;
	wxStaticText * Units_Text_DyingGraphic;
	wxStaticText * Units_Text_HitPoints;
	wxStaticText * Units_Text_LineOfSight;
	wxStaticText * Units_Text_GarrisonCapacity;
	wxStaticText * Units_Text_SizeRadius;
	wxStaticText * Units_Text_HPBarHeight1;
	wxStaticText * Units_Text_TrainSound;
	wxStaticText * Units_Text_DeadUnitID;
	wxStaticText * Units_Text_PlacementMode;
	wxStaticText * Units_Text_IconID;
	wxStaticText * Units_Text_Unknown1;
	wxStaticText * Units_Text_PlacementBypassTerrain;
	wxStaticText * Units_Text_PlacementTerrain;
	wxStaticText * Units_Text_EditorRadius;
	wxStaticText * Units_Text_BuildingMode;
	wxStaticText * Units_Text_TerrainRestriction;
	wxStaticText * Units_Text_ResourceCapacity;
	wxStaticText * Units_Text_ResourceDecay;
	wxStaticText * Units_Text_BlastType;
	wxStaticText * Units_Text_Unknown2;
	wxStaticText * Units_Text_InteractionMode;
	wxStaticText * Units_Text_MinimapMode;
	wxStaticText * Units_Text_CommandAttribute;
	wxStaticText * Units_Text_Unknown3;
	wxStaticText * Units_Text_Unknown3B;
	wxStaticText * Units_Text_Unknown3a;
	wxStaticText * Units_Text_LanguageDllHelp;
	wxStaticText * Units_Text_HotKey;
	wxStaticText * Units_Text_Unknown4;
	wxStaticText * Units_Text_Unknown5;
	wxStaticText * Units_Text_Unknown6;
	wxStaticText * Units_Text_Unknown7;
	wxStaticText * Units_Text_Unknown8;
	wxStaticText * Units_Text_SelectionMask;
	wxStaticText * Units_Text_SelectionShapeType;
	wxStaticText * Units_Text_SelectionShape;
	wxStaticText * Units_Text_Attribute;
	wxStaticText * Units_Text_Civ;
	wxStaticText * Units_Text_Unknown9;
	wxStaticText * Units_Text_SelectionEffect;
	wxStaticText * Units_Text_EditorSelectionColour;
	wxStaticText * Units_Text_SelectionRadius;
	wxStaticText * Units_Text_HPBarHeight2;
	wxStaticText * ResourceStorage_Text_Type;
	wxStaticText * ResourceStorage_Text_Amount;
	wxStaticText * ResourceStorage_Text_Enabled;
	wxStaticText * Units_Text_DamageGraphicCount;
	wxStaticText * Units_Text_SelectionSound;
	wxStaticText * Units_Text_DyingSound;
	wxStaticText * Units_Text_AttackSound;
	wxStaticText * Units_Text_Name;
	wxStaticText * Units_Text_Name2;
	wxStaticText * Units_Text_Unitline;
	wxStaticText * Units_Text_MinTechLevel;
	wxStaticText * Units_Text_ID2;
	wxStaticText * Units_Text_ID3;

//	Type 20+

	wxStaticText * Units_Text_Speed;

//	Type 30+

	wxStaticText * Units_Text_WalkingGraphic;
	wxStaticText * Units_Text_RotationSpeed;
	wxStaticText * Units_Text_Unknown11;
	wxStaticText * Units_Text_TrackingUnit;
	wxStaticText * Units_Text_TrackingUnitUsed;
	wxStaticText * Units_Text_TrackingUnitDensity;
	wxStaticText * Units_Text_Unknown12;
	wxStaticText * Units_Text_Unknown16;

//	Type 40+

	wxStaticText * Units_Text_SearchRadius;
	wxStaticText * Units_Text_WorkRate;
	wxStaticText * Units_Text_DropSite;
	wxStaticText * Units_Text_VillagerMode;
	wxStaticText * Units_Text_MoveSound;
	wxStaticText * Units_Text_StopSound;
	wxStaticText * Units_Text_Exists;
	wxStaticText * Units_Text_CommandCount;

//	Type 60+

	wxStaticText * Units_Text_Unknown20;
	wxStaticText * Units_Text_AttackCount;
	wxStaticText * Units_Text_ArmourCount;
	wxStaticText * Units_Text_Unknown21;
	wxStaticText * Units_Text_MaxRange;
	wxStaticText * Units_Text_BlastRadius;
	wxStaticText * Units_Text_ReloadTime1;
	wxStaticText * Units_Text_ProjectileUnitID;
	wxStaticText * Units_Text_AccuracyPercent;
	wxStaticText * Units_Text_Delay;
	wxStaticText * Units_Text_GraphicDisplacement;
	wxStaticText * Units_Text_BlastLevel;
	wxStaticText * Units_Text_MinRange;
	wxStaticText * Units_Text_GarrisonRecoveryRate;
	wxStaticText * Units_Text_AttackGraphic;
	wxStaticText * Units_Text_DisplayedMeleeArmour;
	wxStaticText * Units_Text_DisplayedAttack;
	wxStaticText * Units_Text_DisplayedRange;
	wxStaticText * Units_Text_ReloadTime2;

//	Type 60 only

	wxStaticText * Units_Text_StretchMode;
	wxStaticText * Units_Text_CompensationMode;
	wxStaticText * Units_Text_DropAnimationMode;
	wxStaticText * Units_Text_PenetrationMode;
	wxStaticText * Units_Text_Unknown24;
	wxStaticText * Units_Text_ProjectileArc;

//	Type 70+

	wxStaticText * Units_Text_CostType;
	wxStaticText * Units_Text_CostAmount;
	wxStaticText * Units_Text_CostUsed;
	wxStaticText * Units_Text_TrainTime;
	wxStaticText * Units_Text_TrainLocationID;
	wxStaticText * Units_Text_ButtonID;
	wxStaticText * Units_Text_Unknown26;
	wxStaticText * Units_Text_Unknown27;
	wxStaticText * Units_Text_Unknown28;
	wxStaticText * Units_Text_MissileGraphicDelay;
	wxStaticText * Units_Text_GarrisonGraphic;
	wxStaticText * Units_Text_AttackMissileDuplicationAmount1;
	wxStaticText * Units_Text_AttackMissileDuplicationAmount2;
	wxStaticText * Units_Text_AttackMissileDuplicationSpawning;
	wxStaticText * Units_Text_AttackMissileDuplicationUnit;
	wxStaticText * Units_Text_AttackMissileDuplicationGraphic;
	wxStaticText * Units_Text_Unknown29;
	wxStaticText * Units_Text_DisplayedPierceArmour;

//	Type 80

	wxStaticText * Units_Text_ConstructionGraphicID;
	wxStaticText * Units_Text_SnowGraphicID;
	wxStaticText * Units_Text_Unknown31;
	wxStaticText * Units_Text_Unknown31b;
	wxStaticText * Units_Text_StackUnitID;
	wxStaticText * Units_Text_TerrainID;
	wxStaticText * Units_Text_Unknown32;
	wxStaticText * Units_Text_ResearchID;
	wxStaticText * Units_Text_Unknown33;
	wxStaticText * Units_Text_AnnexUnit;
	wxStaticText * Units_Text_AnnexUnitMisplacement;
	wxStaticText * Units_Text_HeadUnit;
	wxStaticText * Units_Text_TransformUnit;
	wxStaticText * Units_Text_Unknown34;
	wxStaticText * Units_Text_ConstructionSound;
	wxStaticText * Units_Text_GarrisonType;
	wxStaticText * Units_Text_GarrisonHealRate;
	wxStaticText * Units_Text_Unknown35;
	wxStaticText * Units_Text_Unknown36;
	wxStaticText * Units_Text_Unknown37;

//	Invisible Holder Windows
//	Type 10+

	wxBoxSizer * Units_Holder_Type;
	wxBoxSizer * Units_Holder_ID1;
	wxBoxSizer * Units_Holder_LanguageDllName;
	wxBoxSizer * Units_Holder_LanguageDllCreation;
	wxBoxSizer * Units_Holder_Class;
	wxBoxSizer * Units_Holder_StandingGraphic;
	wxBoxSizer * Units_Holder_DyingGraphic;
	wxBoxSizer * Units_Holder_DeathMode;
	wxBoxSizer * Units_Holder_HitPoints;
	wxBoxSizer * Units_Holder_LineOfSight;
	wxBoxSizer * Units_Holder_GarrisonCapacity;
	wxBoxSizer * Units_Holder_SizeRadius;
	wxGridSizer * Units_Grid_SizeRadius;
	wxBoxSizer * Units_Holder_HPBarHeight1;
	wxBoxSizer * Units_Holder_TrainSound;
	wxBoxSizer * Units_Holder_TrainSound1;
	wxBoxSizer * Units_Holder_TrainSound2;
	wxBoxSizer * Units_Holder_TrainSound3;
	wxBoxSizer * Units_Holder_DeadUnitID;
	wxBoxSizer * Units_Holder_PlacementMode;
	wxBoxSizer * Units_Holder_AirMode;
	wxBoxSizer * Units_Holder_IconID;
	wxBoxSizer * Units_Holder_HideInEditor;
	wxBoxSizer * Units_Holder_Unknown1;
	wxBoxSizer * Units_Holder_Enabled;
	wxBoxSizer * Units_Holder_PlacementBypassTerrain;
	wxGridSizer * Units_Holder_PlacementBypassTerrainGrid;
	wxBoxSizer * Units_Holder_PlacementTerrain;
	wxGridSizer * Units_Holder_PlacementTerrainGrid;
	wxBoxSizer * Units_Holder_EditorRadius;
	wxGridSizer * Units_Grid_EditorRadius;
	wxBoxSizer * Units_Holder_BuildingMode;
	wxBoxSizer * Units_Holder_VisibleInFog;
	wxBoxSizer * Units_Holder_TerrainRestriction;
	wxBoxSizer * Units_Holder_FlyMode;
	wxBoxSizer * Units_Holder_ResourceCapacity;
	wxBoxSizer * Units_Holder_ResourceDecay;
	wxBoxSizer * Units_Holder_BlastType;
	wxBoxSizer * Units_Holder_Unknown2;
	wxBoxSizer * Units_Holder_InteractionMode;
	wxBoxSizer * Units_Holder_MinimapMode;
	wxBoxSizer * Units_Holder_CommandAttribute;
	wxBoxSizer * Units_Holder_Unknown3;
	wxBoxSizer * Units_Holder_Unknown3B;
	wxBoxSizer * Units_Holder_Unknown3a;
	wxBoxSizer * Units_Holder_LanguageDllHelp;
	wxGridSizer * Units_Grid_HotKey;
	wxBoxSizer * Units_Holder_Unknown4;
	wxBoxSizer * Units_Holder_Unknown5;
	wxBoxSizer * Units_Holder_Unselectable;
	wxBoxSizer * Units_Holder_Unknown6;
	wxBoxSizer * Units_Holder_Unknown7;
	wxBoxSizer * Units_Holder_Unknown8;
	wxBoxSizer * Units_Holder_SelectionMask;
	wxBoxSizer * Units_Holder_SelectionShapeType;
	wxBoxSizer * Units_Holder_SelectionShape;
	wxBoxSizer * Units_Holder_Attribute;
	wxBoxSizer * Units_Holder_Civ;
	wxBoxSizer * Units_Holder_Unknown9;
	wxGridSizer * Units_Grid_Unknown9;
	wxBoxSizer * Units_Holder_SelectionEffect;
	wxBoxSizer * Units_Holder_EditorSelectionColour;
	wxBoxSizer * Units_Holder_SelectionRadius;
	wxBoxSizer * Units_Holder_HPBarHeight2;
	wxStaticBoxSizer * Units_Holder_ResourceStorageHeader;
	wxGridSizer * Units_Grid_ResourceStorage;
	wxBoxSizer * Units_Holder_ResourceStorage[3];
	wxBoxSizer * Units_Holder_SelectionSound;
	wxBoxSizer * Units_Holder_DyingSound;
	wxBoxSizer * Units_Holder_AttackSound;
	wxBoxSizer * Units_Holder_Name;
	wxBoxSizer * Units_Holder_Name2;
	wxBoxSizer * Units_Holder_Unitline;
	wxBoxSizer * Units_Holder_MinTechLevel;
	wxBoxSizer * Units_Holder_ID2;
	wxBoxSizer * Units_Holder_ID3;

//	Type 20+

	wxBoxSizer * Units_Holder_Speed;

//	Type 30+

	wxBoxSizer * Units_Holder_WalkingGraphic;
	wxBoxSizer * Units_Holder_RotationSpeed;
	wxBoxSizer * Units_Holder_Unknown11;
	wxBoxSizer * Units_Holder_TrackingUnit;
	wxBoxSizer * Units_Holder_TrackingUnitUsed;
	wxBoxSizer * Units_Holder_TrackingUnitUsedBox;
	wxBoxSizer * Units_Holder_TrackingUnitDensity;
	wxBoxSizer * Units_Holder_Unknown12;
	wxBoxSizer * Units_Holder_Unknown16;
	wxGridSizer * Units_Grid_Unknown16;

//	Type 40+

	wxBoxSizer * Units_Holder_SheepConversion;
	wxBoxSizer * Units_Holder_SearchRadius;
	wxBoxSizer * Units_Holder_WorkRate;
	wxGridSizer * Units_Grid_DropSite;
	wxBoxSizer * Units_Holder_VillagerMode;
	wxBoxSizer * Units_Holder_MoveSound;
	wxBoxSizer * Units_Holder_StopSound;
	wxBoxSizer * Units_Holder_AnimalMode;
	wxBoxSizer * Units_Holder_Exists;

//	Type 60+

	wxBoxSizer * Units_Holder_Unknown20;
	wxGridSizer * Units_Grid_Unknown20;
	wxBoxSizer * Units_Holder_Unknown21;
	wxBoxSizer * Units_Holder_MaxRange;
	wxBoxSizer * Units_Holder_BlastRadius;
	wxBoxSizer * Units_Holder_ReloadTime1;
	wxBoxSizer * Units_Holder_ProjectileUnitID;
	wxBoxSizer * Units_Holder_AccuracyPercent;
	wxBoxSizer * Units_Holder_TowerMode;
	wxBoxSizer * Units_Holder_Delay;
	wxBoxSizer * Units_Holder_GraphicDisplacement;
	wxGridSizer * Units_Grid_GraphicDisplacement;
	wxBoxSizer * Units_Holder_BlastLevel;
	wxBoxSizer * Units_Holder_MinRange;
	wxBoxSizer * Units_Holder_GarrisonRecoveryRate;
	wxBoxSizer * Units_Holder_AttackGraphic;
	wxBoxSizer * Units_Holder_DisplayedMeleeArmour;
	wxBoxSizer * Units_Holder_DisplayedAttack;
	wxBoxSizer * Units_Holder_DisplayedRange;
	wxBoxSizer * Units_Holder_ReloadTime2;

//	Type 60 only

	wxBoxSizer * Units_Holder_StretchMode;
	wxBoxSizer * Units_Holder_CompensationMode;
	wxBoxSizer * Units_Holder_DropAnimationMode;
	wxBoxSizer * Units_Holder_PenetrationMode;
	wxBoxSizer * Units_Holder_Unknown24;
	wxBoxSizer * Units_Holder_ProjectileArc;

//	Type 70+

	wxStaticBoxSizer * Units_Holder_CostHeader;
	wxBoxSizer * Units_Holder_CostType;
	wxGridSizer * Units_Grid_CostType;
	wxBoxSizer * Units_Holder_CostAmount;
	wxBoxSizer * Units_Holder_CostUsed;
	wxBoxSizer * Units_Holder_TrainTime;
	wxBoxSizer * Units_Holder_TrainLocationID;
	wxBoxSizer * Units_Holder_ButtonID;
	wxBoxSizer * Units_Holder_Unknown26;
	wxBoxSizer * Units_Holder_Unknown27;
	wxBoxSizer * Units_Holder_Unknown28;
	wxBoxSizer * Units_Holder_MissileGraphicDelay;
	wxBoxSizer * Units_Holder_HeroMode;
	wxBoxSizer * Units_Holder_GarrisonGraphic;
	wxBoxSizer * Units_Holder_AttackMissileDuplicationAmount1;
	wxBoxSizer * Units_Holder_AttackMissileDuplicationAmount2;
	wxBoxSizer * Units_Holder_AttackMissileDuplicationSpawning;
	wxGridSizer * Units_Grid_AttackMissileDuplicationSpawning;
	wxBoxSizer * Units_Holder_AttackMissileDuplicationUnit;
	wxBoxSizer * Units_Holder_AttackMissileDuplicationGraphic;
	wxBoxSizer * Units_Holder_Unknown29;
	wxBoxSizer * Units_Holder_DisplayedPierceArmour;

//	Type 80

	wxBoxSizer * Units_Holder_ConstructionGraphicID;
	wxBoxSizer * Units_Holder_SnowGraphicID;
	wxBoxSizer * Units_Holder_AdjacentMode;
	wxBoxSizer * Units_Holder_Unknown31;
	wxBoxSizer * Units_Holder_Unknown31b;
	wxBoxSizer * Units_Holder_Unknown31bsub;
	wxBoxSizer * Units_Holder_StackUnitID;
	wxBoxSizer * Units_Holder_TerrainID;
	wxBoxSizer * Units_Holder_Unknown32;
	wxBoxSizer * Units_Holder_ResearchID;
	wxBoxSizer * Units_Holder_Unknown33;
	wxGridSizer * Units_Grid_AnnexUnit;
	wxBoxSizer * Units_Holder_AnnexUnit1;
	wxGridSizer * Units_Grid_AnnexUnitMisplacement;
	wxBoxSizer * Units_Holder_AnnexUnitMisplacement1;
	wxBoxSizer * Units_Holder_HeadUnit;
	wxBoxSizer * Units_Holder_TransformUnit;
	wxBoxSizer * Units_Holder_Unknown34;
	wxBoxSizer * Units_Holder_ConstructionSound;
	wxBoxSizer * Units_Holder_GarrisonType;
	wxBoxSizer * Units_Holder_GarrisonHealRate;
	wxBoxSizer * Units_Holder_Unknown35;
	wxBoxSizer * Units_Holder_Unknown36;
	wxBoxSizer * Units_Holder_Unknown37;
	
//	Unit Controls SubControls
	
	wxGridSizer * Units_Holder_DamageGraphics;
	wxBoxSizer * Units_Holder_DamageGraphics_Data;
	TextCtrl_Short * DamageGraphics_GraphicID;
	ComboBox_Short * DamageGraphics_ComboBox_GraphicID;
	TextCtrl_Byte * DamageGraphics_DamagePercent;
	TextCtrl_Byte * DamageGraphics_Unknown1;
	TextCtrl_Byte * DamageGraphics_Unknown2;
	wxStaticText * DamageGraphics_Text_GraphicID;
	wxStaticText * DamageGraphics_Text_DamagePercent;
	wxStaticText * DamageGraphics_Text_Unknown1;
	wxStaticText * DamageGraphics_Text_Unknown2;
	wxBoxSizer * DamageGraphics_Holder_GraphicID;
	wxBoxSizer * DamageGraphics_Holder_DamagePercent;
	wxBoxSizer * DamageGraphics_Holder_Unknown1;
	wxBoxSizer * DamageGraphics_Holder_Unknown2;
	wxStaticBoxSizer * Units_DamageGraphics;
	wxTextCtrl * Units_DamageGraphics_Search;
	wxTextCtrl * Units_DamageGraphics_Search_R;
//	wxCheckBox * Units_DamageGraphics_UseAnd;
	wxListBox * Units_DamageGraphics_List;
	wxGridSizer * Units_DamageGraphics_Buttons;
	wxButton * Units_DamageGraphics_Add;
	wxButton * Units_DamageGraphics_Delete;
	wxButton * Units_DamageGraphics_Copy;
	wxButton * Units_DamageGraphics_Paste;
	
	wxBoxSizer * Units_Holder_Attacks;
	wxBoxSizer * Units_Holder_Attacks_Data;
	wxBoxSizer * Units_Holder_Attacks_Data1;
	wxGridSizer * Units_Grid_Attacks_Data2;
	TextCtrl_Short * Attacks_Class;
	ComboBox_Short_AttackType * Attacks_ComboBox_Class[3];
	TextCtrl_Short * Attacks_Amount;
	wxStaticText * Attacks_Text_Class;
	wxStaticText * Attacks_Text_Amount;
	wxBoxSizer * Attacks_Holder_Class;
	wxBoxSizer * Attacks_Holder_Class1;
	wxBoxSizer * Attacks_Holder_Amount;
	wxStaticBoxSizer * Units_Attacks;
	wxTextCtrl * Units_Attacks_Search;
	wxTextCtrl * Units_Attacks_Search_R;
//	wxCheckBox * Units_Attacks_UseAnd;
	wxListBox * Units_Attacks_List;
	wxGridSizer * Units_Attacks_Buttons;
	wxButton * Units_Attacks_Add;
	wxButton * Units_Attacks_Delete;
	wxButton * Units_Attacks_Copy;
	wxButton * Units_Attacks_Paste;
	
	wxBoxSizer * Units_Holder_Armors;
	wxBoxSizer * Units_Holder_Armors_Data;
	wxBoxSizer * Units_Holder_Armors_Data1;
	wxBoxSizer * Units_Holder_Armors_Data2;
	wxBoxSizer * Units_Holder_Armors_Data3;
	TextCtrl_Short * Armors_Class;
	TextCtrl_Short * Armors_Amount;
	wxStaticText * Armors_Text_Class;
	wxStaticText * Armors_Text_Amount;
	wxBoxSizer * Armors_Holder_Class;
	wxBoxSizer * Armors_Holder_Class1;
	wxBoxSizer * Armors_Holder_Amount;
	wxStaticBoxSizer * Units_Armors;
	wxTextCtrl * Units_Armors_Search;
	wxTextCtrl * Units_Armors_Search_R;
//	wxCheckBox * Units_Armors_UseAnd;
	wxListBox * Units_Armors_List;
	wxGridSizer * Units_Armors_Buttons;
	wxButton * Units_Armors_Add;
	wxButton * Units_Armors_Delete;
	wxButton * Units_Armors_Copy;
	wxButton * Units_Armors_Paste;

//	End of Unit Controls

	wxBoxSizer * Units_Main;	// Unit window
	wxBoxSizer * Units_ListArea;	// Unit list section vertical division
	wxGridSizer * Units_Units_Buttons;	// Unit list section buttons

	wxStaticBoxSizer * Units_Units;	// Unit list section vertical division excluding window borders
	wxComboBox * Units_Civs_List;	// Civ list combo box
	wxBoxSizer * Units_Units_Searches[2];
	wxTextCtrl * Units_Units_Search;	// Unit search
	wxTextCtrl * Units_Units_Search_R;	// Unit reverse search
	wxOwnerDrawnComboBox * Units_Units_SearchFilters[2];	// Unit search
	wxCheckBox * Units_Units_UseAnd[2];
	wxListBox * Units_Units_List;	// List of units
	wxButton * Units_Add;	// Buttons
	wxButton * Units_Delete;
	wxButton * Units_Copy;
	wxButton * Units_Paste;
//	wxButton * Units_Undo;

	wxBoxSizer * Units_DataArea;	// Unit window other-than unit-list-section
	wxBoxSizer * Units_MainRow1;	// Unscrollable top section
	
	wxBoxSizer * Units_ScrollerWindows;	// Scrollable section division
	wxBoxSizer * Units_ScrollerWindowsSpace;
	wxStaticBoxSizer * Units_Holder_TypeArea;
	wxBoxSizer * Units_Holder_TypeArea1;
	wxBoxSizer * Units_Holder_TypeArea2;
	wxStaticBoxSizer * Units_Holder_LangDLLArea;
	wxStaticBoxSizer * Units_Holder_GraphicsArea;
	wxBoxSizer * Units_Holder_GraphicsArea1;
	wxGridSizer * Units_Holder_GraphicsArea2;
	wxGridSizer * Units_Holder_GraphicsArea3;
	wxBoxSizer * Units_Holder_GraphicsArea4;
	wxBoxSizer * Units_Holder_GraphicsArea5;
	wxBoxSizer * Units_Holder_GraphicsArea6;
	wxBoxSizer * Units_Holder_GraphicsArea7;
	wxStaticBoxSizer * Units_Holder_StatsArea;
	wxGridSizer * Units_Grid_StatsArea1;
	wxGridSizer * Units_Grid_StatsAreaGarrison;
	wxGridSizer * Units_Grid_StatsArea2;
	wxStaticBoxSizer * Units_Holder_ProjectilesArea;
	wxGridSizer * Units_Grid_ProjectilesArea1;
	wxGridSizer * Units_Grid_ProjectilesArea2;
	wxGridSizer * Units_Grid_ProjectilesArea3;
	wxStaticBoxSizer * Units_Holder_Attributes;
	wxGridSizer * Units_Grid_AttributesBoxes1;
	wxGridSizer * Units_Grid_Attributes1;
	wxBoxSizer * Units_Holder_AttributesTerrain;
	wxGridSizer * Units_Grid_AttributesTerrain;
	wxGridSizer * Units_Grid_AttributesModes1;
	wxBoxSizer * Units_Holder_AttributesDropSite;
	wxBoxSizer * Units_Holder_AttributesSizes;
	wxGridSizer * Units_Grid_AttributesSelection1;
	wxBoxSizer * Units_Holder_AttributesHotKey;
	wxGridSizer * Units_Grid_AttributesTracking;
	wxGridSizer * Units_Grid_AttributesTrain1;
	wxGridSizer * Units_Grid_Attributes3;
	wxBoxSizer * Units_Holder_AttributesAnnexUnit;
	wxBoxSizer * Units_Holder_AttributesAnnexUnit2;
	wxBoxSizer * Units_Holder_Attributes4;
	wxStaticBoxSizer * Units_Holder_SoundsArea;
	wxBoxSizer * Units_Holder_SoundsArea1;
	wxGridSizer * Units_Grid_SoundsArea2;
	wxStaticBoxSizer * Units_Holder_MiscArea;
	wxGridSizer * Units_Grid_HPBars;
	wxBoxSizer * Units_Holder_UnknownArea;
	wxStaticBoxSizer * Units_Holder_Type10plusUnknownArea;
	wxBoxSizer * Units_Holder_Type10plusUnknowns1;
	wxGridSizer * Units_Grid_Type10plusUnknowns;
	wxStaticBoxSizer * Units_Holder_Type30plusUnknownArea;
	wxGridSizer * Units_Grid_Type30plusUnknownArea;
	wxStaticBoxSizer * Units_Holder_Type60plusUnknownArea;
	wxStaticBoxSizer * Units_Holder_Type70plusUnknownArea;
	wxGridSizer * Units_Grid_Type70plusUnknownArea;
	wxStaticBoxSizer * Units_Holder_Type80plusUnknownArea;
	wxGridSizer * Units_Grid_Type80plusUnknownArea;
	wxStaticBoxSizer * Units_Holder_CommandsArea;
	wxStaticBoxSizer * Units_Holder_TopRow;
	wxStaticText * Units_AutoCopyState;
	
//	Unit Attributes section

	wxBoxSizer * Units_CommandHolder_Lists;
	wxStaticBoxSizer * Units_UnitHeads;
	wxStaticText * Units_UnitHeads_Name;
	wxListBox * Units_UnitHeads_List;
	
	wxStaticBoxSizer * Units_UnitCommands;
	wxTextCtrl * Units_UnitCommands_Search;
	wxTextCtrl * Units_UnitCommands_Search_R;
//	wxCheckBox * Units_UnitCommands_UseAnd;
	wxListBox * Units_UnitCommands_List;
	wxGridSizer * Units_UnitCommands_Buttons;
	wxButton * Units_UnitCommands_Add;
	wxButton * Units_UnitCommands_Delete;
	wxButton * Units_UnitCommands_Copy;
	wxButton * Units_UnitCommands_Paste;

	wxBoxSizer * Units_CommandHolder_Data;
	wxBoxSizer * Units_CommandHolder_Data1;
	wxBoxSizer * Units_CommandHolder_Data2;
	wxBoxSizer * UnitCommands_Holder_One;
	wxBoxSizer * UnitCommands_Holder_ID;
	wxBoxSizer * UnitCommands_Holder_1;
	wxBoxSizer * UnitCommands_Holder_Unknown1;
	wxBoxSizer * UnitCommands_Holder_Type;
	wxBoxSizer * UnitCommands_Holder_SubType;
	wxBoxSizer * UnitCommands_Holder_Types;
	wxBoxSizer * UnitCommands_Holder_2;
	wxBoxSizer * UnitCommands_Holder_Resources;
	wxBoxSizer * UnitCommands_Holder_ClassID;
	wxBoxSizer * UnitCommands_Holder_UnitID;
	wxBoxSizer * UnitCommands_Holder_Unknown2;
	wxBoxSizer * UnitCommands_Holder_ResourceIn;
	wxBoxSizer * UnitCommands_Holder_ResourceOut;
	wxBoxSizer * UnitCommands_Holder_Unknown3;
	wxBoxSizer * UnitCommands_Holder_Unknown4;
	wxBoxSizer * UnitCommands_Holder_ExecutionRadius;
	wxBoxSizer * UnitCommands_Holder_Unknown5;
	wxBoxSizer * UnitCommands_Holder_Unknown6;
	wxBoxSizer * UnitCommands_Holder_Unknown7;
	wxBoxSizer * UnitCommands_Holder_Unknown8;
	wxBoxSizer * UnitCommands_Holder_Unknown9;
	wxBoxSizer * UnitCommands_Holder_Unknown10;
	wxBoxSizer * UnitCommands_Holder_Unknown11;
	wxBoxSizer * UnitCommands_Holder_Unknown12;
	wxBoxSizer * UnitCommands_Holder_Unknown13;
	wxBoxSizer * UnitCommands_Holder_Unknown14;
	wxBoxSizer * UnitCommands_Holder_Graphics;
	wxGridSizer * UnitCommands_Holder_GraphicsGrid;
	
	wxStaticText * UnitCommands_Text_One;
	wxStaticText * UnitCommands_Text_ID;
	wxStaticText * UnitCommands_Text_Unknown1;
	wxStaticText * UnitCommands_Text_Type;
	wxStaticText * UnitCommands_Text_ClassID;
	wxStaticText * UnitCommands_Text_UnitID;
	wxStaticText * UnitCommands_Text_Unknown2;
	wxStaticText * UnitCommands_Text_ResourceIn;
	wxStaticText * UnitCommands_Text_SubType;
	wxStaticText * UnitCommands_Text_ResourceOut;
	wxStaticText * UnitCommands_Text_Unknown3;
	wxStaticText * UnitCommands_Text_Unknown4;
	wxStaticText * UnitCommands_Text_ExecutionRadius;
	wxStaticText * UnitCommands_Text_Unknown5;
	wxStaticText * UnitCommands_Text_Unknown6;
	wxStaticText * UnitCommands_Text_Unknown7;
	wxStaticText * UnitCommands_Text_Unknown8;
	wxStaticText * UnitCommands_Text_Unknown9;
	wxStaticText * UnitCommands_Text_Unknown10;
	wxStaticText * UnitCommands_Text_Unknown11;
	wxStaticText * UnitCommands_Text_Unknown12;
	wxStaticText * UnitCommands_Text_Unknown13;
	wxStaticText * UnitCommands_Text_Unknown14;
	wxStaticText * UnitCommands_Text_Graphics;

	TextCtrl_Short * UnitCommands_One;
	TextCtrl_Short * UnitCommands_ID;
	TextCtrl_Byte * UnitCommands_Unknown1;
	TextCtrl_Short * UnitCommands_Type;
	TextCtrl_Short * UnitCommands_SubType;
	wxOwnerDrawnComboBox * UnitCommands_ComboBox_Types;
	TextCtrl_Short * UnitCommands_ClassID;
	TextCtrl_Short * UnitCommands_UnitID;
	ComboBox_Short * UnitCommands_ComboBox_UnitID;
	TextCtrl_Short * UnitCommands_Unknown2;
	TextCtrl_Short * UnitCommands_ResourceIn;
	ComboBox_Short * UnitCommands_ComboBox_ResourceIn;
	TextCtrl_Short * UnitCommands_ResourceOut;
	ComboBox_Short * UnitCommands_ComboBox_ResourceOut;
	TextCtrl_Short * UnitCommands_Unknown3;
	TextCtrl_Float * UnitCommands_Unknown4;
	TextCtrl_Float * UnitCommands_ExecutionRadius;
	TextCtrl_Float * UnitCommands_Unknown5;
	TextCtrl_Byte * UnitCommands_Unknown6;
	TextCtrl_Float * UnitCommands_Unknown7;
	TextCtrl_Byte * UnitCommands_Unknown8;
	TextCtrl_Byte * UnitCommands_Unknown9;
	TextCtrl_Byte * UnitCommands_Unknown10;
	TextCtrl_Byte * UnitCommands_Unknown11;
	TextCtrl_Short * UnitCommands_Unknown12;
	TextCtrl_Short * UnitCommands_Unknown13;
	TextCtrl_Byte * UnitCommands_Unknown14;
	TextCtrl_Short * UnitCommands_Graphics[6];
	ComboBox_Short * UnitCommands_ComboBox_Graphics[6];

//	Graphics user interface

	wxBoxSizer * Graphics_Main;
	wxBoxSizer * Graphics_ListArea;
	wxGridSizer * Graphics_Graphics_Buttons;
	wxStaticBoxSizer * Graphics_Graphics;
	wxTextCtrl * Graphics_Graphics_Search;
	wxTextCtrl * Graphics_Graphics_Search_R;
	wxCheckBox * Graphics_Graphics_UseAnd;
	wxListBox * Graphics_Graphics_List;
	wxButton * Graphics_Add;
	wxButton * Graphics_Delete;
	wxButton * Graphics_Copy;
	wxButton * Graphics_Paste;
	
	wxBoxSizer * Graphics_DataArea;
	wxScrolledWindow * Graphics_Scroller;
	wxBoxSizer * Graphics_ScrollerWindows;
	wxBoxSizer * Graphics_ScrollerWindowsSpace;
	
	wxBoxSizer * Graphics_Holder_NameArea;
	wxBoxSizer * Graphics_Holder_Name;
	wxBoxSizer * Graphics_Holder_Name2;
	wxBoxSizer * Graphics_Holder_SLP;
	wxGridSizer * Graphics_Holder_Unknowns;
	wxBoxSizer * Graphics_Holder_Unknown1;
	wxBoxSizer * Graphics_Holder_Unknown2;
	wxBoxSizer * Graphics_Holder_FrameType;
	wxBoxSizer * Graphics_Holder_Unknown3;
	wxBoxSizer * Graphics_Holder_Unknown4;
	wxBoxSizer * Graphics_Holder_Replay;
	wxBoxSizer * Graphics_Holder_Coordinates;
	wxGridSizer * Graphics_Holder_CoordinateGrid;
	wxBoxSizer * Graphics_Holder_SoundID;
	wxBoxSizer * Graphics_Holder_AttackSoundUsed;
	wxBoxSizer * Graphics_Holder_AttackSoundUsed1;
	wxBoxSizer * Graphics_Holder_4;
	wxBoxSizer * Graphics_Holder_5;
	wxBoxSizer * Graphics_Holder_FrameCount;
	wxBoxSizer * Graphics_Holder_AngleCount;
	wxBoxSizer * Graphics_Holder_Unknown13;
	wxBoxSizer * Graphics_Holder_FrameRate;
	wxBoxSizer * Graphics_Holder_ReplayDelay;
	wxBoxSizer * Graphics_Holder_SequenceType;
	wxBoxSizer * Graphics_Holder_ID;
	wxBoxSizer * Graphics_Holder_Type;
	wxGridSizer * Graphics_Grid_1;
	wxGridSizer * Graphics_Grid_2;
	
	wxStaticText * Graphics_Text_Name;
	wxStaticText * Graphics_Text_Name2;
	wxStaticText * Graphics_Text_SLP;
	wxStaticText * Graphics_Text_Unknown1;
	wxStaticText * Graphics_Text_Unknown2;
	wxStaticText * Graphics_Text_FrameType;
	wxStaticText * Graphics_Text_Unknown3;
	wxStaticText * Graphics_Text_Unknown4;
	wxStaticText * Graphics_Text_Replay;
	wxStaticText * Graphics_Text_Coordinates;
	wxStaticText * Graphics_Text_SoundID;
	wxStaticText * Graphics_Text_AttackSoundUsed;
	wxStaticText * Graphics_Text_FrameCount;
	wxStaticText * Graphics_Text_AngleCount;
	wxStaticText * Graphics_Text_Unknown13;
	wxStaticText * Graphics_Text_FrameRate;
	wxStaticText * Graphics_Text_ReplayDelay;
	wxStaticText * Graphics_Text_SequenceType;
	wxStaticText * Graphics_Text_ID;
	wxStaticText * Graphics_Text_Type;
	
	TextCtrl_String * Graphics_Name;
	TextCtrl_String * Graphics_Name2;
	TextCtrl_Long * Graphics_SLP;
	TextCtrl_Byte * Graphics_Unknown1;
	TextCtrl_Byte * Graphics_Unknown2;
	TextCtrl_Byte * Graphics_FrameType;
	TextCtrl_Byte * Graphics_Unknown3;
	TextCtrl_Byte * Graphics_Unknown4;
	TextCtrl_Byte * Graphics_Replay;
	TextCtrl_Short * Graphics_Coordinates[4];
	TextCtrl_Short * Graphics_SoundID;
	ComboBox_Short * Graphics_ComboBox_SoundID;
	TextCtrl_Byte * Graphics_AttackSoundUsed;
	CheckBox_Byte * Graphics_CheckBox_AttackSoundUsed;
	TextCtrl_UnShort * Graphics_FrameCount;
	TextCtrl_UnShort * Graphics_AngleCount;
	TextCtrl_Float * Graphics_Unknown13;
	TextCtrl_Float * Graphics_FrameRate;
	TextCtrl_Float * Graphics_ReplayDelay;
	TextCtrl_Byte * Graphics_SequenceType;
	TextCtrl_Short * Graphics_ID;
	TextCtrl_Short * Graphics_TypeS;

	wxStaticBoxSizer * Graphics_Deltas;
	wxTextCtrl * Graphics_Deltas_Search;
	wxTextCtrl * Graphics_Deltas_Search_R;
//	wxCheckBox * Graphics_Deltas_UseAnd;
	wxListBox * Graphics_Deltas_List;
	wxGridSizer * Graphics_Deltas_Buttons;
	wxButton * Deltas_Add;
	wxButton * Deltas_Delete;
	wxButton * Deltas_Copy;
	wxButton * Deltas_Paste;
	wxStaticBoxSizer * Graphics_AttackSounds;
	wxListBox * Graphics_AttackSounds_List;
	wxButton * AttackSounds_Copy;
	
	wxBoxSizer * Graphics_Holder_Deltas;
	wxBoxSizer * Graphics_Holder_Deltas_Data;
	wxBoxSizer * Graphics_Holder_Deltas_Data1;
	wxGridSizer * Graphics_Grid_Deltas_Data2;
	wxBoxSizer * Graphics_Holder_AttackSoundArea;
	wxBoxSizer * Graphics_Holder_AttackSounds_Data;
	
	wxBoxSizer * GraphicDeltas_Holder_GraphicID;
	wxStaticText * GraphicDeltas_Text_GraphicID;
	TextCtrl_Short * GraphicDeltas_GraphicID;
	ComboBox_Short * GraphicDeltas_ComboBox_GraphicID;
	wxBoxSizer * GraphicDeltas_Holder_Unknown1;
	wxStaticText * GraphicDeltas_Text_Unknown1;
	TextCtrl_Short * GraphicDeltas_Unknown1;
	wxBoxSizer * GraphicDeltas_Holder_Unknown2;
	wxStaticText * GraphicDeltas_Text_Unknown2;
	TextCtrl_Short * GraphicDeltas_Unknown2;
	wxBoxSizer * GraphicDeltas_Holder_Unknown3;
	wxStaticText * GraphicDeltas_Text_Unknown3;
	TextCtrl_Short * GraphicDeltas_Unknown3;
	wxBoxSizer * GraphicDeltas_Holder_DirectionX;
	wxStaticText * GraphicDeltas_Text_DirectionX;
	TextCtrl_Short * GraphicDeltas_DirectionX;
	wxBoxSizer * GraphicDeltas_Holder_DirectionY;
	wxStaticText * GraphicDeltas_Text_DirectionY;
	TextCtrl_Short * GraphicDeltas_DirectionY;
	wxBoxSizer * GraphicDeltas_Holder_Unknown4;
	wxStaticText * GraphicDeltas_Text_Unknown4;
	TextCtrl_Short * GraphicDeltas_Unknown4;
	wxBoxSizer * GraphicDeltas_Holder_Unknown5;
	wxStaticText * GraphicDeltas_Text_Unknown5;
	TextCtrl_Short * GraphicDeltas_Unknown5;
	wxBoxSizer * Graphics_Holder_AttackSounds;
	wxGridSizer * Graphics_Grid_AttackSounds;
	wxStaticText * Graphics_Text_AttackSounds;
	wxBoxSizer * Graphics_Holder_AttackSoundDelays;
	wxStaticText * Graphics_Text_AttackSoundDelays;
	TextCtrl_Short * Graphics_AttackSoundDelay[3];
	TextCtrl_Short * Graphics_AttackSoundID[3];
	ComboBox_Short * Graphics_ComboBox_AttackSoundID[3];

//	Terrains user interface
	
	wxBoxSizer * Terrains_Main;
	wxBoxSizer * Terrains_ListArea;
	wxStaticBoxSizer * Terrains_Terrains;
	wxTextCtrl * Terrains_Terrains_Search;
	wxTextCtrl * Terrains_Terrains_Search_R;
	wxCheckBox * Terrains_Terrains_UseAnd;
	wxListBox * Terrains_Terrains_List;
	wxGridSizer * Terrains_Terrains_Buttons;
	wxButton * Terrains_Add;
	wxButton * Terrains_Delete;
	wxButton * Terrains_Copy;
	wxButton * Terrains_Paste;
	
	wxBoxSizer * Terrains_DataArea;
	wxScrolledWindow * Terrains_Scroller;
	wxBoxSizer * Terrains_ScrollerWindows;
	wxBoxSizer * Terrains_ScrollerWindowsSpace;
	wxBoxSizer * Terrains_Holder_NameArea;
	wxGridSizer * Terrains_Grid_Area1;
	wxBoxSizer * Terrains_Holder_UnknownArea;
	wxGridSizer * Terrains_Grid_Unknowns1;
	wxBoxSizer * Terrains_Holder_Unknown1;
	wxStaticText * Terrains_Text_Unknown1;
	TextCtrl_Short * Terrains_Unknown1;
	wxBoxSizer * Terrains_Holder_Unknown2;
	wxStaticText * Terrains_Text_Unknown2;
	TextCtrl_Short * Terrains_Unknown2;
	wxBoxSizer * Terrains_Holder_Name;
	wxStaticText * Terrains_Text_Name;
	TextCtrl_String * Terrains_Name;
	wxBoxSizer * Terrains_Holder_Name2;
	wxStaticText * Terrains_Text_Name2;
	TextCtrl_String * Terrains_Name2;
	wxBoxSizer * Terrains_Holder_SLP;
	wxStaticText * Terrains_Text_SLP;
	TextCtrl_Long * Terrains_SLP;
	wxBoxSizer * Terrains_Holder_Unknown3;
	wxStaticText * Terrains_Text_Unknown3;
	TextCtrl_Long * Terrains_Unknown3;
	wxBoxSizer * Terrains_Holder_SoundID;
	wxStaticText * Terrains_Text_SoundID;
	TextCtrl_Long * Terrains_SoundID;
	ComboBox_Long * Terrains_ComboBox_SoundID;
	wxBoxSizer * Terrains_Holder_BlendPriority;
	wxStaticText * Terrains_Text_BlendPriority;
	TextCtrl_Long * Terrains_BlendPriority;
	wxBoxSizer * Terrains_Holder_BlendType;
	wxStaticText * Terrains_Text_BlendType;
	TextCtrl_Long * Terrains_BlendType;
	wxBoxSizer * Terrains_Holder_Colours;
	wxGridSizer * Terrains_Grid_Colours;
	wxStaticText * Terrains_Text_Colours;
	TextCtrl_Byte * Terrains_Colours[3];
	wxBoxSizer * Terrains_Holder_Unknown5;
	wxStaticText * Terrains_Text_Unknown5;
	TextCtrl_Short * Terrains_Unknown5;
	wxBoxSizer * Terrains_Holder_Unknown6;
	wxStaticText * Terrains_Text_Unknown6;
	TextCtrl_Short * Terrains_Unknown6;
	wxBoxSizer * Terrains_Holder_Unknown7;
	wxGridSizer * Terrains_Grid_Unknown7;
	wxStaticText * Terrains_Text_Unknown7;
	TextCtrl_Byte * Terrains_Unknown7[23];
	wxBoxSizer * Terrains_Holder_FrameCount;
	wxStaticText * Terrains_Text_FrameCount;
	TextCtrl_Short * Terrains_FrameCount;
	wxBoxSizer * Terrains_Holder_Unknown8;
	wxStaticText * Terrains_Text_Unknown8;
	TextCtrl_Short * Terrains_Unknown8[2];
	wxBoxSizer * Terrains_Holder_Unknown9;
	wxGridSizer * Terrains_Grid_Unknown9;
	wxStaticText * Terrains_Text_Unknown9;
	TextCtrl_Short * Terrains_Unknown9[54];
	wxBoxSizer * Terrains_Holder_TerrainReplacementID;
	wxStaticText * Terrains_Text_TerrainReplacementID;
	TextCtrl_Short * Terrains_TerrainReplacementID;
	ComboBox_Short * Terrains_ComboBox_TerrainReplacementID;
	wxBoxSizer * Terrains_Holder_TerrainDimensions;
	wxStaticText * Terrains_Text_TerrainDimensions;
	TextCtrl_Short * Terrains_TerrainDimensions[2];
	wxBoxSizer * Terrains_Holder_Unknown10;
	wxGridSizer * Terrains_Grid_Unknown10;
	wxStaticText * Terrains_Text_Unknown10;
	TextCtrl_Byte * Terrains_Unknown10[84];
	wxBoxSizer * Terrains_Holder_TerrainUnits;
	wxBoxSizer * Terrains_Holder_TerrainUnitID;
	wxGridSizer * Terrains_Grid_TerrainUnitID;
	wxStaticText * Terrains_Text_TerrainUnitID;
	TextCtrl_Short * Terrains_TerrainUnitID[30];
	ComboBox_Short * Terrains_ComboBox_TerrainUnitID[30];
	wxBoxSizer * Terrains_Holder_TerrainUnitDensity;
	wxStaticText * Terrains_Text_TerrainUnitDensity;
	TextCtrl_Short * Terrains_TerrainUnitDensity[30];
	wxBoxSizer * Terrains_Holder_Unknown11;
	wxGridSizer * Terrains_Grid_Unknown11;
	wxStaticText * Terrains_Text_Unknown11;
	TextCtrl_Byte * Terrains_Unknown11[30];
	wxBoxSizer * Terrains_Holder_NumberOfTerrainUnitsUsed;
	wxBoxSizer * Terrains_Holder_NumberOfTerrainUnitsUsed1;
	wxStaticText * Terrains_Text_NumberOfTerrainUnitsUsed;
	TextCtrl_Short * Terrains_NumberOfTerrainUnitsUsed;
	wxBoxSizer * Terrains_Holder_SUnknown1;
	wxGridSizer * Terrains_Grid_SUnknown1;
	wxStaticText * Terrains_Text_SUnknown1;
	TextCtrl_Byte * Terrains_SUnknown1[24];
	
//	Terrain restrictions user interface

	wxBoxSizer * TerRestrict_Main;
	wxBoxSizer * TerRestrict_ListArea;
	wxGridSizer * TerRestrict_TerRestrict_Buttons;
	wxStaticBoxSizer * TerRestrict_TerRestrict;
	wxTextCtrl * TerRestrict_TerRestrict_Search;
	wxTextCtrl * TerRestrict_TerRestrict_Search_R;
//	wxCheckBox * TerRestrict_TerRestrict_UseAnd;
	wxListBox * TerRestrict_TerRestrict_List;
	wxButton * TerRestrict_Add;
	wxButton * TerRestrict_Delete;
	wxButton * TerRestrict_Copy;
	wxButton * TerRestrict_Paste;

	wxBoxSizer * TerRestrict_Terrains;
	wxBoxSizer * TerRestrict_DataArea;
	wxTextCtrl * TerRestrict_Terrains_Search;
	wxTextCtrl * TerRestrict_Terrains_Search_R;
//	wxCheckBox * TerRestrict_Terrains_UseAnd;
	wxListBox * TerRestrict_Terrains_List;
	wxGridSizer * TerRestrict_Terrains_Buttons;
	wxButton * TerRestrict_Terrains_Copy;
	wxButton * TerRestrict_Terrains_Paste;
	wxBoxSizer * TerRestrict_Holder_Accessible;
	wxBoxSizer * TerRestrict_Holder_Accessible2;
	wxStaticText * TerRestrict_Text_Accessible;
	TextCtrl_Float * TerRestrict_Accessible;
	CheckBox_Float * TerRestrict_CheckBox_Accessible;
	wxBoxSizer * TerRestrict_Holder_Unknown1;
	wxBoxSizer * TerRestrict_Holder_Unknown1Sub;
	wxStaticText * TerRestrict_Text_Unknown1;
	TextCtrl_Long * TerRestrict_Unknown1;
	CheckBox_Long_ZeroIsYes * TerRestrict_CheckBox_Unknown1;
	wxBoxSizer * TerRestrict_Holder_Graphics;
	wxStaticText * TerRestrict_Text_Graphics;
	TextCtrl_Long * TerRestrict_Graphics[2];
	ComboBox_Long * TerRestrict_ComboBox_Graphics[2];
	wxBoxSizer * TerRestrict_Holder_Amount;
	wxStaticText * TerRestrict_Text_Amount;
	TextCtrl_Long * TerRestrict_Amount;

//	Sound user interface
	
	wxBoxSizer * Sounds_Main;
	wxBoxSizer * Sounds_ListArea;
	wxGridSizer * Sounds_Sounds_Buttons;
	wxBoxSizer * SoundItems_ListArea;
	wxGridSizer * Sounds_SoundItems_Buttons;
	wxBoxSizer * Sounds_DataArea;

	wxStaticBoxSizer * Sounds_Sounds;
	wxTextCtrl * Sounds_Sounds_Search;
	wxTextCtrl * Sounds_Sounds_Search_R;
//	wxCheckBox * Sounds_Sounds_UseAnd;
	wxListBox * Sounds_Sounds_List;
	wxButton * Sounds_Add;
	wxButton * Sounds_Delete;
	wxButton * Sounds_Copy;
	wxButton * Sounds_Paste;

	wxStaticBoxSizer * Sounds_SoundItems;
	wxTextCtrl * Sounds_SoundItems_Search;
	wxTextCtrl * Sounds_SoundItems_Search_R;
//	wxCheckBox * Sounds_SoundItems_UseAnd;
	wxListBox * Sounds_SoundItems_List;
	wxButton * SoundItems_Add;
	wxButton * SoundItems_Delete;
	wxButton * SoundItems_Copy;
	wxButton * SoundItems_Paste;

	wxBoxSizer * Sounds_Holder_ID;
	wxStaticText * Sounds_Text_ID;
	TextCtrl_Long * Sounds_ID;
	wxBoxSizer * Sounds_Holder_Unknown;
	wxStaticText * Sounds_Text_Unknown;
	TextCtrl_Long * Sounds_Unknown;
	wxBoxSizer * SoundItems_Holder_Name;
	wxStaticText * SoundItems_Text_Name;
	TextCtrl_String * SoundItems_Name;
	wxBoxSizer * SoundItems_Holder_Resource;
	wxStaticText * SoundItems_Text_Resource;
	TextCtrl_Long * SoundItems_Resource;
	wxBoxSizer * SoundItems_Holder_Probability;
	wxStaticText * SoundItems_Text_Probability;
	TextCtrl_Short * SoundItems_Probability;
	wxBoxSizer * SoundItems_Holder_Civ;
	wxStaticText * SoundItems_Text_Civ;
	TextCtrl_Short * SoundItems_Civ;
	ComboBox_Short * SoundItems_ComboBox_Civ;
	wxBoxSizer * SoundItems_Holder_Unknown;
	wxStaticText * SoundItems_Text_Unknown;
	TextCtrl_Short * SoundItems_Unknown;

//	Player Color user interface

	wxBoxSizer * Colors_Main;
	wxBoxSizer * Colors_ListArea;
	wxGridSizer * Colors_Colors_Buttons;
	wxStaticBoxSizer * Colors_Colors;
	wxTextCtrl * Colors_Colors_Search;
	wxTextCtrl * Colors_Colors_Search_R;
//	wxCheckBox * Colors_Colors_UseAnd;
	wxListBox * Colors_Colors_List;
	wxButton * Colors_Add;
	wxButton * Colors_Delete;
	wxButton * Colors_Copy;
	wxButton * Colors_Paste;
	
	wxBoxSizer * Colors_DataArea;
	wxBoxSizer * Colors_Holder_Name;
	wxBoxSizer * Colors_Holder_ID;
	wxBoxSizer * Colors_Holder_Palette;
	wxBoxSizer * Colors_Holder_Color;
	wxBoxSizer * Colors_Holder_MinimapColor;
	wxBoxSizer * Colors_Holder_UnknownArea;
	wxBoxSizer * Colors_Holder_Unknown1;
	wxBoxSizer * Colors_Holder_Unknown2;
	wxBoxSizer * Colors_Holder_Unknown3;
	wxBoxSizer * Colors_Holder_Unknown4;
	wxBoxSizer * Colors_Holder_Unknown5;
	wxStaticText * Colors_Text_Name;
	wxStaticText * Colors_Text_ID;
	wxStaticText * Colors_Text_Palette;
	wxStaticText * Colors_Text_Color;
	wxStaticText * Colors_Text_MinimapColor;
	wxStaticText * Colors_Text_Unknown1;
	wxStaticText * Colors_Text_Unknown2;
	wxStaticText * Colors_Text_Unknown3;
	wxStaticText * Colors_Text_Unknown4;
	wxStaticText * Colors_Text_Unknown5;
	TextCtrl_String * Colors_Name;
	TextCtrl_Long * Colors_ID;
	TextCtrl_Long * Colors_Palette;
	TextCtrl_Long * Colors_ColorL;
	TextCtrl_Long * Colors_MinimapColor;
	TextCtrl_Long * Colors_Unknown1;
	TextCtrl_Long * Colors_Unknown2;
	TextCtrl_Long * Colors_Unknown3;
	TextCtrl_Long * Colors_Unknown4;
	TextCtrl_Long * Colors_Unknown5;

//	Unitline user interface

	wxBoxSizer * UnitLines_Main;
	wxBoxSizer * UnitLines_ListArea;
	wxGridSizer * UnitLines_UnitLines_Buttons;
	wxBoxSizer * UnitLineUnits_ListArea;
	wxGridSizer * UnitLines_UnitLineUnits_Buttons;
	wxBoxSizer * UnitLines_DataArea;
	
	wxStaticBoxSizer * UnitLines_UnitLines;
	wxTextCtrl * UnitLines_UnitLines_Search;
	wxTextCtrl * UnitLines_UnitLines_Search_R;
	wxListBox * UnitLines_UnitLines_List;
	wxButton * UnitLines_Add;
	wxButton * UnitLines_Delete;
	wxButton * UnitLines_Copy;
	wxButton * UnitLines_Paste;

	wxBoxSizer * UnitLines_Holder_ID;
	wxStaticText * UnitLines_Text_ID;
	TextCtrl_Short * UnitLines_ID;
	wxBoxSizer * UnitLines_Holder_Name;
	wxStaticText * UnitLines_Text_Name;
	TextCtrl_String * UnitLines_Name;

	wxStaticBoxSizer * UnitLines_UnitLineUnits;
	wxTextCtrl * UnitLines_UnitLineUnits_Search;
	wxTextCtrl * UnitLines_UnitLineUnits_Search_R;
	wxListBox * UnitLines_UnitLineUnits_List;
	wxButton * UnitLineUnits_Add;
	wxButton * UnitLineUnits_Delete;
	wxButton * UnitLineUnits_Copy;
	wxButton * UnitLineUnits_Paste;

	wxBoxSizer * UnitLineUnits_Holder_Units;
	wxStaticText * UnitLineUnits_Text_Units;
	TextCtrl_Short * UnitLineUnits_Units;
	ComboBox_Short * UnitLineUnits_ComboBox_Units;

};

#endif
