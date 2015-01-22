#include "AGE_FramePieces.h"
#include "AGE_OpenDialog.h"
#include "AGE_SaveDialog.h"
#include "AGE_AboutDialog.h"
#include "AGE_Copies.hpp"

class AGE_Frame: public wxFrame
{
public:
	AGE_Frame(const wxString &title, wxString &aP, Copies &c, short window = 1);

//	Stuff related to editing multiple files at once

	//AGE_Frame *secondWindow;
	Copies *copies;
	wxString *argPath;

//	Constructions Methods

	void CreateGeneralControls();
	void CreateResearchControls();
	void CreateTechControls();
	void CreateTechTreeControls();
	void CreateCivControls();
	void CreateUnitControls();
	void CreateUnitLineControls();
	void CreateGraphicsControls();
	void CreateTerrainControls();
	void CreateTerrainBorderControls();
	void CreateTerrainRestrictionControls();
	void CreateSoundControls();
	void CreatePlayerColorControls();
	void CreateUnknownControls();

//	void CreateDRSControls();

//	Other Events

	bool DataOpened;
	void LoadLists();
	void OnGameVersionChange();
	void OnSave(wxCommandEvent &Event);
	void OnOpen(wxCommandEvent &Event);
	void OnExit(wxCloseEvent &Event);
	void OnMenuOption(wxCommandEvent &Event);
	void OnAutoCopy(wxCommandEvent &Event);

//	Updates user interface after changing data name.

	void OnSelection_SearchFilters(wxCommandEvent &Event);
	void OnKillFocus_LangDLL(wxFocusEvent &Event);

	void OnKillFocus_Research(wxFocusEvent &Event);
	void OnKillFocus_Techs(wxFocusEvent &Event);
	void OnKillFocus_TechTrees(wxFocusEvent &Event);
	void OnKillFocus_Civs(wxFocusEvent &Event);
	void OnKillFocus_Units(wxFocusEvent &Event);
	void OnKillFocus_UnitLines(wxFocusEvent &Event);
	void OnKillFocus_Graphics(wxFocusEvent &Event);
	void OnKillFocus_Terrains(wxFocusEvent &Event);
	void OnKillFocus_Borders(wxFocusEvent &Event);
	void OnKillFocus_TerRestrict(wxFocusEvent &Event);
	void OnKillFocus_Sounds(wxFocusEvent &Event);
	void OnKillFocus_Colors(wxFocusEvent &Event);
	void OnKillFocus_Unknown(wxFocusEvent &Event);

	void OnUpdateCheck_Techs(wxCommandEvent &Event);
	void OnUpdateCheck_Graphics(wxCommandEvent &Event);
	void OnUpdateCheck_TerRestrict(wxCommandEvent &Event);
	void OnUpdateCheck_UnitAttribute(wxCommandEvent &Event);
	void OnUpdateCheck_UnitGarrisonType(wxCommandEvent &Event);

	void OnUpdateCombo_Techs(wxCommandEvent &Event);
	void OnUpdateCombo_TechTrees(wxCommandEvent &Event);
	void OnUpdateCombo_Units(wxCommandEvent &Event);
	void OnUpdateCombo_UnitLines(wxCommandEvent &Event);
	void OnUpdateCombo_Graphics(wxCommandEvent &Event);
	void OnUpdateCombo_Terrains(wxCommandEvent &Event);

//	Other Methods

//	bool FileExists(const char *value);
	wxString searchText, excludeText;
	wxString FormatFloat(float);
	wxString FormatInt(int);
	wxString CurrentTime();
	wxArrayString Type20, Type30, Type40, Type50, Type60, Type70, Type80;
	void SaveBackup();
	bool SearchMatches(wxString itemText);
	void Listing(wxListBox* &List, wxArrayString &names, list<void*> &data);
	void FillLists(list<ComboBox_Plus1*> &boxlist, wxArrayString &names);
	void UnitLangDLLConverter(wxCommandEvent &Event);
	void ResearchLangDLLConverter(wxCommandEvent &Event);
	void SearchAllSubVectors(wxListBox* &List, wxTextCtrl* &TopSearch, wxTextCtrl* &SubSearch);
	void LoadAllTechEffects(wxCommandEvent &Event);
	void ClearAllTechEffects(wxCommandEvent &Event);
	void OnAllTechEffectSelect(wxCommandEvent &Event);
	void LoadAllSoundFiles(wxCommandEvent &Event);
	void ClearAllSoundFiles(wxCommandEvent &Event);
	void OnAllSoundFileSelect(wxCommandEvent &Event);

//	General Events

	void InitTTAges();
	void InitTTBuildings();
	void InitTTUnits();
	void InitTTResearches();
	void InitCivs(bool all);
	void InitUnits(short civ, bool all);
	void InitUnitLines();
	void InitResearches(bool all);
	void InitTechs(bool all);
	void InitGraphics(bool all);
	void InitSounds(bool all);
	void InitTerrainRestrictions(bool all);
	void InitTerrains1(bool all);
	void InitTerrains2();
	void InitPlayerColors();
	void InitTerrainBorders(bool all);
	void InitRandomMaps();

	void ListGeneral();
	void OnGeneralSelect(wxCommandEvent &Event);
	void OnVariableCalc(wxFocusEvent &Event);
	void OnVariableCalcReverse(wxFocusEvent &Event);

	void ListRandomMaps();
	void OnUnknownsSearch(wxCommandEvent &Event);
	void OnUnknownsSelect(wxCommandEvent &Event);
	void OnUnknownsAdd(wxCommandEvent &Event);
	void OnUnknownsInsert(wxCommandEvent &Event);
	void OnUnknownsDelete(wxCommandEvent &Event);
	void OnUnknownsCopy(wxCommandEvent &Event);
	void OnUnknownsPaste(wxCommandEvent &Event);
	void OnUnknownsPasteInsert(wxCommandEvent &Event);
	string GetUnknownName(short);

	void ListRMSBaseZones();
	void DisableRMSBaseZones();
	void OnRMSBaseZoneSearch(wxCommandEvent &Event);
	void OnRMSBaseZoneSelect(wxCommandEvent &Event);
	void OnRMSBaseZoneAdd(wxCommandEvent &Event);
	void OnRMSBaseZoneInsert(wxCommandEvent &Event);
	void OnRMSBaseZoneDelete(wxCommandEvent &Event);
	void OnRMSBaseZoneCopy(wxCommandEvent &Event);
	void OnRMSBaseZonePaste(wxCommandEvent &Event);
	void OnRMSBaseZonePasteInsert(wxCommandEvent &Event);
	void OnRMSBaseZoneCopyToMaps(wxCommandEvent &Event);
	string GetRMSBaseZonesName(short);

	void ListRMSTerrains();
	void DisableRMSTerrains();
	void OnRMSTerrainSearch(wxCommandEvent &Event);
	void OnRMSTerrainSelect(wxCommandEvent &Event);
	void OnRMSTerrainAdd(wxCommandEvent &Event);
	void OnRMSTerrainInsert(wxCommandEvent &Event);
	void OnRMSTerrainDelete(wxCommandEvent &Event);
	void OnRMSTerrainCopy(wxCommandEvent &Event);
	void OnRMSTerrainPaste(wxCommandEvent &Event);
	void OnRMSTerrainPasteInsert(wxCommandEvent &Event);
	void OnRMSTerrainCopyToMaps(wxCommandEvent &Event);
	string GetRMSTerrainName(short);

	void ListRMSUnits();
	void DisableRMSUnits();
	void OnRMSUnitSearch(wxCommandEvent &Event);
	void OnRMSUnitSelect(wxCommandEvent &Event);
	void OnRMSUnitAdd(wxCommandEvent &Event);
	void OnRMSUnitInsert(wxCommandEvent &Event);
	void OnRMSUnitDelete(wxCommandEvent &Event);
	void OnRMSUnitCopy(wxCommandEvent &Event);
	void OnRMSUnitPaste(wxCommandEvent &Event);
	void OnRMSUnitPasteInsert(wxCommandEvent &Event);
	void OnRMSUnitCopyToMaps(wxCommandEvent &Event);
	string GetRMSUnitName(short);

	void ListRMSUnknowns();
	void DisableRMSUnknowns();
	void OnRMSUnknownSearch(wxCommandEvent &Event);
	void OnRMSUnknownSelect(wxCommandEvent &Event);
	void OnRMSUnknownAdd(wxCommandEvent &Event);
	void OnRMSUnknownInsert(wxCommandEvent &Event);
	void OnRMSUnknownDelete(wxCommandEvent &Event);
	void OnRMSUnknownCopy(wxCommandEvent &Event);
	void OnRMSUnknownPaste(wxCommandEvent &Event);
	void OnRMSUnknownPasteInsert(wxCommandEvent &Event);
	void OnRMSUnknownCopyToMaps(wxCommandEvent &Event);
	string GetRMSUnknownName(short);

//	Research Events

	void ListResearches(bool all = true);
	void OnResearchSearch(wxCommandEvent &Event);
	void OnResearchSelect(wxCommandEvent &Event);
	void OnResearchAdd(wxCommandEvent &Event);
	void OnResearchInsert(wxCommandEvent &Event);
	void OnResearchDelete(wxCommandEvent &Event);
	void OnResearchCopy(wxCommandEvent &Event);
	void OnResearchPaste(wxCommandEvent &Event);
	void OnResearchPasteInsert(wxCommandEvent &Event);
	string GetResearchName(short, bool = false);

//	Tech Events

	void ListTechs(bool all = true);
	void OnTechSearch(wxCommandEvent &Event);
	void OnTechSelect(wxCommandEvent &Event);
	void OnTechAdd(wxCommandEvent &Event);
	void OnTechInsert(wxCommandEvent &Event);
	void OnTechDelete(wxCommandEvent &Event);
	void OnTechCopy(wxCommandEvent &Event);
	void OnTechPaste(wxCommandEvent &Event);
	void OnTechPasteInsert(wxCommandEvent &Event);
	void OnTechRename(wxCommandEvent &Event);
	void OnTechRenameGE2(wxCommandEvent &Event);
	string GetTechName(short);

	void ListEffects();
	void OnEffectsSearch(wxCommandEvent &Event);
	void OnEffectsSelect(wxCommandEvent &Event);
	void OnEffectsAdd(wxCommandEvent &Event);
	void OnEffectsInsert(wxCommandEvent &Event);
	void OnEffectsDelete(wxCommandEvent &Event);
	void OnEffectsCopy(wxCommandEvent &Event);
	void OnEffectsPaste(wxCommandEvent &Event);
	void OnEffectsPasteInsert(wxCommandEvent &Event);
	void OnEffectsCopyToTechs(wxCommandEvent &Event);
	string GetEffectName(short);

//	Tech Tree Events

	void ListTTAges();
	void OnTTAgesSearch(wxCommandEvent &Event);
	void OnTTAgesSelect(wxCommandEvent &Event);
	void OnTTAgesAdd(wxCommandEvent &Event);
	void OnTTAgesInsert(wxCommandEvent &Event);
	void OnTTAgesDelete(wxCommandEvent &Event);
	void OnTTAgesCopy(wxCommandEvent &Event);
	void OnTTAgesPaste(wxCommandEvent &Event);
	void OnTTAgesPasteInsert(wxCommandEvent &Event);
	string GetTTAgesName(short);

	void ListTTAgeBuildings();
	void OnTTAgesBuildingSearch(wxCommandEvent &Event);
	void OnTTAgesBuildingSelect(wxCommandEvent &Event);
	void OnTTAgesBuildingAdd(wxCommandEvent &Event);
	void OnTTAgesBuildingInsert(wxCommandEvent &Event);
	void OnTTAgesBuildingDelete(wxCommandEvent &Event);
	void OnTTAgesBuildingCopy(wxCommandEvent &Event);
	void OnTTAgesBuildingPaste(wxCommandEvent &Event);
	void OnTTAgesBuildingPasteInsert(wxCommandEvent &Event);
	void OnTTAgesBuildingCopyToAges(wxCommandEvent &Event);
	string GetBuildingName(short);

	void ListTTAgeUnits();
	void OnTTAgesUnitSearch(wxCommandEvent &Event);
	void OnTTAgesUnitSelect(wxCommandEvent &Event);
	void OnTTAgesUnitAdd(wxCommandEvent &Event);
	void OnTTAgesUnitInsert(wxCommandEvent &Event);
	void OnTTAgesUnitDelete(wxCommandEvent &Event);
	void OnTTAgesUnitCopy(wxCommandEvent &Event);
	void OnTTAgesUnitPaste(wxCommandEvent &Event);
	void OnTTAgesUnitPasteInsert(wxCommandEvent &Event);
	void OnTTAgesUnitCopyToAges(wxCommandEvent &Event);

	void ListTTAgeResearches();
	void OnTTAgesResearchSearch(wxCommandEvent &Event);
	void OnTTAgesResearchSelect(wxCommandEvent &Event);
	void OnTTAgesResearchAdd(wxCommandEvent &Event);
	void OnTTAgesResearchInsert(wxCommandEvent &Event);
	void OnTTAgesResearchDelete(wxCommandEvent &Event);
	void OnTTAgesResearchCopy(wxCommandEvent &Event);
	void OnTTAgesResearchPaste(wxCommandEvent &Event);
	void OnTTAgesResearchPasteInsert(wxCommandEvent &Event);
	void OnTTAgesResearchCopyToAges(wxCommandEvent &Event);
	string GetSimpleResearchName(short);

	void ListTTAgeItems();
	void OnTTAgeItemSearch(wxCommandEvent &Event);
	void OnTTAgeItemSelect(wxCommandEvent &Event);
	void OnTTAgeItemCopy(wxCommandEvent &Event);
	void OnTTAgeItemPaste(wxCommandEvent &Event);
	void OnTTAgeItemCopyToAges(wxCommandEvent &Event);

	void ListTTAgeUnknownItems();
	void OnTTAgeUnknownItemSearch(wxCommandEvent &Event);
	void OnTTAgeUnknownItemSelect(wxCommandEvent &Event);
	void OnTTAgeUnknownItemCopy(wxCommandEvent &Event);
	void OnTTAgeUnknownItemPaste(wxCommandEvent &Event);
	void OnTTAgeUnknownItemCopyToAges(wxCommandEvent &Event);

	void ListTTBuildings();
	void OnTTBuildingSearch(wxCommandEvent &Event);
	void OnTTBuildingSelect(wxCommandEvent &Event);
	void OnTTBuildingAdd(wxCommandEvent &Event);
	void OnTTBuildingInsert(wxCommandEvent &Event);
	void OnTTBuildingDelete(wxCommandEvent &Event);
	void OnTTBuildingCopy(wxCommandEvent &Event);
	void OnTTBuildingPaste(wxCommandEvent &Event);
	void OnTTBuildingPasteInsert(wxCommandEvent &Event);
	string GetTTBuildingName(short);

	void ListTTBuildingBuildings();
	void OnTTBuildingBuildingSearch(wxCommandEvent &Event);
	void OnTTBuildingBuildingSelect(wxCommandEvent &Event);
	void OnTTBuildingBuildingAdd(wxCommandEvent &Event);
	void OnTTBuildingBuildingInsert(wxCommandEvent &Event);
	void OnTTBuildingBuildingDelete(wxCommandEvent &Event);
	void OnTTBuildingBuildingCopy(wxCommandEvent &Event);
	void OnTTBuildingBuildingPaste(wxCommandEvent &Event);
	void OnTTBuildingBuildingPasteInsert(wxCommandEvent &Event);
	void OnTTBuildingBuildingCopyToBuildings(wxCommandEvent &Event);

	void ListTTBuildingUnits();
	void OnTTBuildingUnitSearch(wxCommandEvent &Event);
	void OnTTBuildingUnitSelect(wxCommandEvent &Event);
	void OnTTBuildingUnitAdd(wxCommandEvent &Event);
	void OnTTBuildingUnitInsert(wxCommandEvent &Event);
	void OnTTBuildingUnitDelete(wxCommandEvent &Event);
	void OnTTBuildingUnitCopy(wxCommandEvent &Event);
	void OnTTBuildingUnitPaste(wxCommandEvent &Event);
	void OnTTBuildingUnitPasteInsert(wxCommandEvent &Event);
	void OnTTBuildingUnitCopyToBuildings(wxCommandEvent &Event);

	void ListTTBuildingResearches();
	void OnTTBuildingResearchSearch(wxCommandEvent &Event);
	void OnTTBuildingResearchSelect(wxCommandEvent &Event);
	void OnTTBuildingResearchAdd(wxCommandEvent &Event);
	void OnTTBuildingResearchInsert(wxCommandEvent &Event);
	void OnTTBuildingResearchDelete(wxCommandEvent &Event);
	void OnTTBuildingResearchCopy(wxCommandEvent &Event);
	void OnTTBuildingResearchPaste(wxCommandEvent &Event);
	void OnTTBuildingResearchPasteInsert(wxCommandEvent &Event);
	void OnTTBuildingResearchCopyToBuildings(wxCommandEvent &Event);

	void ListTTBuildingItems();
	void OnTTBuildingItemSearch(wxCommandEvent &Event);
	void OnTTBuildingItemSelect(wxCommandEvent &Event);
	void OnTTBuildingItemCopy(wxCommandEvent &Event);
	void OnTTBuildingItemPaste(wxCommandEvent &Event);
	void OnTTBuildingItemCopyToBuildings(wxCommandEvent &Event);

	void ListTTUnits();
	void OnTTUnitSearch(wxCommandEvent &Event);
	void OnTTUnitSelect(wxCommandEvent &Event);
	void OnTTUnitAdd(wxCommandEvent &Event);
	void OnTTUnitInsert(wxCommandEvent &Event);
	void OnTTUnitDelete(wxCommandEvent &Event);
	void OnTTUnitCopy(wxCommandEvent &Event);
	void OnTTUnitPaste(wxCommandEvent &Event);
	void OnTTUnitPasteInsert(wxCommandEvent &Event);
	string GetTTUnitName(short);

	void ListTTUnitUnits();
	void OnTTUnitUnitSearch(wxCommandEvent &Event);
	void OnTTUnitUnitSelect(wxCommandEvent &Event);
	void OnTTUnitUnitAdd(wxCommandEvent &Event);
	void OnTTUnitUnitInsert(wxCommandEvent &Event);
	void OnTTUnitUnitDelete(wxCommandEvent &Event);
	void OnTTUnitUnitCopy(wxCommandEvent &Event);
	void OnTTUnitUnitPaste(wxCommandEvent &Event);
	void OnTTUnitUnitPasteInsert(wxCommandEvent &Event);
	void OnTTUnitUnitCopyToUnits(wxCommandEvent &Event);

	void ListTTCommonItems(AGE_AreaTT84 &area, genie::techtree::Common* dataPointer);
	void SelectTTCommonItems(AGE_AreaTT84 &area, genie::techtree::Common* dataPointer);
	void ListTTUnitItems();
	void OnTTUnitItemSearch(wxCommandEvent &Event);
	void OnTTUnitItemSelect(wxCommandEvent &Event);
	void OnTTUnitItemCopy(wxCommandEvent &Event);
	void OnTTUnitItemPaste(wxCommandEvent &Event);
	void OnTTUnitItemCopyToUnits(wxCommandEvent &Event);

	void ListTTResearches();
	void OnTTResearchSearch(wxCommandEvent &Event);
	void OnTTResearchSelect(wxCommandEvent &Event);
	void OnTTResearchAdd(wxCommandEvent &Event);
	void OnTTResearchInsert(wxCommandEvent &Event);
	void OnTTResearchDelete(wxCommandEvent &Event);
	void OnTTResearchCopy(wxCommandEvent &Event);
	void OnTTResearchPaste(wxCommandEvent &Event);
	void OnTTResearchPasteInsert(wxCommandEvent &Event);
	string GetTTResearchName(short);

	void ListTTResearchBuildings();
	void OnTTResearchBuildingSearch(wxCommandEvent &Event);
	void OnTTResearchBuildingSelect(wxCommandEvent &Event);
	void OnTTResearchBuildingAdd(wxCommandEvent &Event);
	void OnTTResearchBuildingInsert(wxCommandEvent &Event);
	void OnTTResearchBuildingDelete(wxCommandEvent &Event);
	void OnTTResearchBuildingCopy(wxCommandEvent &Event);
	void OnTTResearchBuildingPaste(wxCommandEvent &Event);
	void OnTTResearchBuildingPasteInsert(wxCommandEvent &Event);
	void OnTTResearchBuildingCopyToResearches(wxCommandEvent &Event);

	void ListTTResearchUnits();
	void OnTTResearchUnitSearch(wxCommandEvent &Event);
	void OnTTResearchUnitSelect(wxCommandEvent &Event);
	void OnTTResearchUnitAdd(wxCommandEvent &Event);
	void OnTTResearchUnitInsert(wxCommandEvent &Event);
	void OnTTResearchUnitDelete(wxCommandEvent &Event);
	void OnTTResearchUnitCopy(wxCommandEvent &Event);
	void OnTTResearchUnitPaste(wxCommandEvent &Event);
	void OnTTResearchUnitPasteInsert(wxCommandEvent &Event);
	void OnTTResearchUnitCopyToResearches(wxCommandEvent &Event);

	void ListTTResearchResearches();
	void OnTTResearchResearchSearch(wxCommandEvent &Event);
	void OnTTResearchResearchSelect(wxCommandEvent &Event);
	void OnTTResearchResearchAdd(wxCommandEvent &Event);
	void OnTTResearchResearchInsert(wxCommandEvent &Event);
	void OnTTResearchResearchDelete(wxCommandEvent &Event);
	void OnTTResearchResearchCopy(wxCommandEvent &Event);
	void OnTTResearchResearchPaste(wxCommandEvent &Event);
	void OnTTResearchResearchPasteInsert(wxCommandEvent &Event);
	void OnTTResearchResearchCopyToResearches(wxCommandEvent &Event);

	void ListTTResearchItems();
	void OnTTResearchItemSearch(wxCommandEvent &Event);
	void OnTTResearchItemSelect(wxCommandEvent &Event);
	void OnTTResearchItemCopy(wxCommandEvent &Event);
	void OnTTResearchItemPaste(wxCommandEvent &Event);
	void OnTTResearchItemCopyToResearches(wxCommandEvent &Event);

//	Civilization Events

	void ListCivs(bool all = true);
	void OnCivsSearch(wxCommandEvent &Event);
	void OnCivsSelect(wxCommandEvent &Event);
	void OnCivsAdd(wxCommandEvent &Event);
	void OnCivsInsert(wxCommandEvent &Event);
	void OnCivsDelete(wxCommandEvent &Event);
	void OnCivsCopy(wxCommandEvent &Event);
	void OnCivsPaste(wxCommandEvent &Event);
	void OnCivsPasteInsert(wxCommandEvent &Event);
	string GetCivName(short);
	void OnCivCountChange();

	void ListResources(bool all = true);
	void OnResourcesSearch(wxCommandEvent &Event);
	void OnResourcesSelect(wxCommandEvent &Event);
	void OnResourcesAdd(wxCommandEvent &Event);
	void OnResourcesInsert(wxCommandEvent &Event);
	void OnResourcesDelete(wxCommandEvent &Event);
	void OnResourcesCopy(wxCommandEvent &Event);
	void OnResourcesPaste(wxCommandEvent &Event);
	void OnResourcesPasteInsert(wxCommandEvent &Event);
	void OnResourcesCopyToAll(wxCommandEvent &Event);
	string GetResourceName(short);

	void ListUnits(short civ, bool all = true);
	void OnUnitsSearch(wxCommandEvent &Event);
	void OnUnitsSelect(wxCommandEvent &Event);
	void OnUnitsAdd(wxCommandEvent &Event);
	void OnUnitsInsert(wxCommandEvent &Event);
	void OnUnitsDelete(wxCommandEvent &Event);
	void OnUnitsCopy(wxCommandEvent &Event);
	void UnitsAutoCopy(wxCommandEvent &Event);
	void OnUnitsSpecialCopy(wxCommandEvent &Event);
	void UnitsGraphicsCopy(GraphicCopies &store, short civ, short unit);
	void OnUnitsPaste(wxCommandEvent &Event);
	void OnUnitsPasteInsert(wxCommandEvent &Event);
	void PasteUnits();
	void OnUnitsSpecialPaste(wxCommandEvent &Event);
	void OnUnitsSpecialPasteInsert(wxCommandEvent &Event);
	void UnitsGraphicsPaste(GraphicCopies &store, short civ, short unit);
	void OnUnitsEnable(wxCommandEvent &Event);
	void OnUnitsDisable(wxCommandEvent &Event);
	//void OnExtractUnit(wxCommandEvent &Event);
	//void OnImportUnit(wxCommandEvent &Event);
	void OnUnitSubList(wxCommandEvent &Event);
	string GetUnitName(short, short, bool = false);

	void ListUnitDamageGraphics();
	void OnUnitDamageGraphicsSearch(wxCommandEvent &Event);
	void OnUnitDamageGraphicsSelect(wxCommandEvent &Event);
	void OnUnitDamageGraphicsAdd(wxCommandEvent &Event);
	void OnUnitDamageGraphicsInsert(wxCommandEvent &Event);
	void OnUnitDamageGraphicsDelete(wxCommandEvent &Event);
	void OnUnitDamageGraphicsCopy(wxCommandEvent &Event);
	void OnUnitDamageGraphicsPaste(wxCommandEvent &Event);
	void OnUnitDamageGraphicsPasteInsert(wxCommandEvent &Event);
	void OnUnitDamageGraphicsCopyToUnits(wxCommandEvent &Event);
	string GetUnitDamageGraphicName(short);

	void ListUnitAttacks();
	void OnUnitAttacksSearch(wxCommandEvent &Event);
	void OnUnitAttacksSelect(wxCommandEvent &Event);
	void OnUnitAttacksAdd(wxCommandEvent &Event);
	void OnUnitAttacksInsert(wxCommandEvent &Event);
	void OnUnitAttacksDelete(wxCommandEvent &Event);
	void OnUnitAttacksCopy(wxCommandEvent &Event);
	void OnUnitAttacksPaste(wxCommandEvent &Event);
	void OnUnitAttacksPasteInsert(wxCommandEvent &Event);
	void OnUnitAttacksCopyToUnits(wxCommandEvent &Event);
	string GetUnitAttackName(short);

	void ListUnitArmors();
	void OnUnitArmorsSearch(wxCommandEvent &Event);
	void OnUnitArmorsSelect(wxCommandEvent &Event);
	void OnUnitArmorsAdd(wxCommandEvent &Event);
	void OnUnitArmorsInsert(wxCommandEvent &Event);
	void OnUnitArmorsDelete(wxCommandEvent &Event);
	void OnUnitArmorsCopy(wxCommandEvent &Event);
	void OnUnitArmorsPaste(wxCommandEvent &Event);
	void OnUnitArmorsPasteInsert(wxCommandEvent &Event);
	void OnUnitArmorsCopyToUnits(wxCommandEvent &Event);
	string GetUnitArmorName(short);

//	Unit Events

	//void ListUnitHeads(short);
	//void OnUnitHeadsSelect();

	void ListUnitCommands();
	void OnUnitCommandsSearch(wxCommandEvent &Event);
	void OnUnitCommandsSelect(wxCommandEvent &Event);
	void OnUnitCommandsAdd(wxCommandEvent &Event);
	void OnUnitCommandsInsert(wxCommandEvent &Event);
	void OnUnitCommandsDelete(wxCommandEvent &Event);
	void OnUnitCommandsCopy(wxCommandEvent &Event);
	void OnUnitCommandsPaste(wxCommandEvent &Event);
	void OnUnitCommandsPasteInsert(wxCommandEvent &Event);
	void OnUnitCommandsCopyToUnits(wxCommandEvent &Event);
	wxString GetUnitCommandName(short);

//	Unitline Events

	void ListUnitLines();
	void OnUnitLinesSearch(wxCommandEvent &Event);
	void OnUnitLinesSelect(wxCommandEvent &Event);
	void OnUnitLinesAdd(wxCommandEvent &Event);
	void OnUnitLinesInsert(wxCommandEvent &Event);
	void OnUnitLinesDelete(wxCommandEvent &Event);
	void OnUnitLinesCopy(wxCommandEvent &Event);
	void OnUnitLinesPaste(wxCommandEvent &Event);
	void OnUnitLinesPasteInsert(wxCommandEvent &Event);
	string GetUnitLineName(short);

	void ListUnitLineUnits();
	void OnUnitLineUnitsSearch(wxCommandEvent &Event);
	void OnUnitLineUnitsSelect(wxCommandEvent &Event);
	void OnUnitLineUnitsAdd(wxCommandEvent &Event);
	void OnUnitLineUnitsInsert(wxCommandEvent &Event);
	void OnUnitLineUnitsDelete(wxCommandEvent &Event);
	void OnUnitLineUnitsCopy(wxCommandEvent &Event);
	void OnUnitLineUnitsPaste(wxCommandEvent &Event);
	void OnUnitLineUnitsPasteInsert(wxCommandEvent &Event);
	void OnUnitLineUnitsCopyToUnitLines(wxCommandEvent &Event);
	string GetUnitLineUnitName(short);

//	Graphic Events

	void ListGraphics(bool all = true);
	void OnGraphicsSearch(wxCommandEvent &Event);
	void OnGraphicsSelect(wxCommandEvent &Event);
	void OnGraphicsAdd(wxCommandEvent &Event);
	void OnGraphicsInsert(wxCommandEvent &Event);
	void OnGraphicsDelete(wxCommandEvent &Event);
	void OnGraphicsCopy(wxCommandEvent &Event);
	void OnGraphicsPaste(wxCommandEvent &Event);
	void OnGraphicsPasteInsert(wxCommandEvent &Event);
	void OnGraphicsEnable(wxCommandEvent &Event);
	void OnGraphicsDisable(wxCommandEvent &Event);
	//void OnExtractGraphic(wxCommandEvent &Event);
	//void OnImportGraphic(wxCommandEvent &Event);
	string GetGraphicName(short, bool = false);

	void ListGraphicDeltas();
	void OnGraphicDeltasSearch(wxCommandEvent &Event);
	void OnGraphicDeltasSelect(wxCommandEvent &Event);
	void OnGraphicDeltasAdd(wxCommandEvent &Event);
	void OnGraphicDeltasInsert(wxCommandEvent &Event);
	void OnGraphicDeltasDelete(wxCommandEvent &Event);
	void OnGraphicDeltasCopy(wxCommandEvent &Event);
	void OnGraphicDeltasPaste(wxCommandEvent &Event);
	void OnGraphicDeltasPasteInsert(wxCommandEvent &Event);
	void OnGraphicDeltasCopyToGraphics(wxCommandEvent &Event);
	string GetGraphicDeltaName(short);

	void ListGraphicAttackSounds();
	void OnGraphicAttackSoundsSearch(wxCommandEvent &Event);
	void OnGraphicAttackSoundsSelect(wxCommandEvent &Event);
	void OnGraphicAttackSoundsCopy(wxCommandEvent &Event);
	void OnGraphicAttackSoundsCopyToGraphics(wxCommandEvent &Event);
	string GetGraphicAttackSoundName(short);

//	Terrain Events

	void ListTerrainNumbers();
	void OnTerrainCountChange(wxFocusEvent &Event);

	void ListTerrains1(bool all = true);
	void ListTerrains2();
	void OnTerrainsSearch(wxCommandEvent &Event);
	void OnTerrainsSelect(wxCommandEvent &Event);
	void OnTerrainsAdd(wxCommandEvent &Event);
	void OnTerrainsInsert(wxCommandEvent &Event);
	void OnTerrainsDelete(wxCommandEvent &Event);
	void OnTerrainsCopy(wxCommandEvent &Event);
	void OnTerrainsPaste(wxCommandEvent &Event);
	void OnTerrainsPasteInsert(wxCommandEvent &Event);
	string GetTerrainName(short);

	void OnTerrainsBorderSearch(wxCommandEvent &Event);
	void ListTerrainsBorders();
	void OnTerrainsBorderSelect(wxCommandEvent &Event);
	void OnTerrainsBorderCopy(wxCommandEvent &Event);
	void OnTerrainsBorderPaste(wxCommandEvent &Event);
	void OnTerrainsBorderCopyToBuildings(wxCommandEvent &Event);

//	Terrain Border Events

	void ListTerrainBorders(bool all = true);
	void OnTerrainBordersSearch(wxCommandEvent &Event);
	void OnTerrainBordersSelect(wxCommandEvent &Event);
	void OnTerrainBordersCopy(wxCommandEvent &Event);
	void OnTerrainBordersPaste(wxCommandEvent &Event);
	string GetTerrainBorderName(short);

	void ListTerrainBorderFrames();
	void OnTerrainBorderFramesSearch(wxCommandEvent &Event);
	void OnTerrainBorderFramesSelect(wxCommandEvent &Event);
	void OnTerrainBorderFramesCopy(wxCommandEvent &Event);
	void OnTerrainBorderFramesPaste(wxCommandEvent &Event);
	void OnTerrainBorderFramesCopyToBorders(wxCommandEvent &Event);
	string GetTerrainBorderFrameName(short);

//	Terrain Restriction Events

	void ListTerrainRestrictions(bool all = true);
	void OnTerrainRestrictionsSearch(wxCommandEvent &Event);
	void OnTerrainRestrictionsSelect(wxCommandEvent &Event);
	void OnTerrainRestrictionsTerrainSelect(wxCommandEvent &Event);
	void OnTerrainRestrictionsAdd(wxCommandEvent &Event);
	void OnTerrainRestrictionsInsert(wxCommandEvent &Event);
	void OnTerrainRestrictionsDelete(wxCommandEvent &Event);
	void OnTerrainRestrictionsCopy(wxCommandEvent &Event);
	void OnTerrainRestrictionsPaste(wxCommandEvent &Event);
	void OnTerrainRestrictionsPasteInsert(wxCommandEvent &Event);
	void OnTerrainRestrictionsTerrainCopy(wxCommandEvent &Event);
	void OnTerrainRestrictionsTerrainPaste(wxCommandEvent &Event);
	string GetTerrainRestrictionName(short);

//	Sound Events

	void ListSounds(bool all = true);
	void OnSoundsSearch(wxCommandEvent &Event);
	void OnSoundsSelect(wxCommandEvent &Event);
	void OnSoundsAdd(wxCommandEvent &Event);
	void OnSoundsInsert(wxCommandEvent &Event);
	void OnSoundsDelete(wxCommandEvent &Event);
	void OnSoundsCopy(wxCommandEvent &Event);
	void OnSoundsPaste(wxCommandEvent &Event);
	void OnSoundsPasteInsert(wxCommandEvent &Event);
	string GetSoundName(short);

	void ListSoundItems();
	void OnSoundItemsSearch(wxCommandEvent &Event);
	void OnSoundItemsSelect(wxCommandEvent &Event);
	void OnSoundItemsAdd(wxCommandEvent &Event);
	void OnSoundItemsInsert(wxCommandEvent &Event);
	void OnSoundItemsDelete(wxCommandEvent &Event);
	void OnSoundItemsCopy(wxCommandEvent &Event);
	void OnSoundItemsPaste(wxCommandEvent &Event);
	void OnSoundItemsPasteInsert(wxCommandEvent &Event);
	void OnSoundItemsCopyToSounds(wxCommandEvent &Event);
	string GetSoundItemName(short);

//	Player Color Events

	void ListPlayerColors();
	void OnPlayerColorsSearch(wxCommandEvent &Event);
	void OnPlayerColorsSelect(wxCommandEvent &Event);
	void OnPlayerColorsAdd(wxCommandEvent &Event);
	void OnPlayerColorsInsert(wxCommandEvent &Event);
	void OnPlayerColorsDelete(wxCommandEvent &Event);
	void OnPlayerColorsCopy(wxCommandEvent &Event);
	void OnPlayerColorsPaste(wxCommandEvent &Event);
	void OnPlayerColorsPasteInsert(wxCommandEvent &Event);
	string GetPlayerColorName(short);

//	Application Variables

	float EditorVersion;
	wxString EditorVersionString;
	bool PromptForFilesOnOpen, AutoCopy, CopyGraphics, AllCivs, AutoBackups;
	vector<short> SelectedCivs;
	bool useAnd[2], EnableIDFix, ShowUnknowns, ShowButtons, NeedDat, SkipOpenDialog;
	wxFileConfig *Config, *Customs;
	genie::DatFile *GenieFile;
	genie::LangFile *Lang, *LangX, *LangXP;
//	wxSound SoundFile;

	list<ComboBox_Plus1*> ResearchComboBoxList, TechComboBoxList, CivComboBoxList, ResourceComboBoxList,
	UnitComboBoxList, GraphicComboBoxList, TerrainComboBoxList, TerrainBorderComboBoxList,
	TerrainRestrictionComboBoxList, SoundComboBoxList;

/*	genie::DatFile FileBackup; // Can't copy the whole file?
	long EditCount;
	genie::Unit UnitBackup[100][20];
	short IDtoRestore[100];
	genie::Civ CivBackup[20];	// Only temporary solution!*/

	wxArrayInt Items;
	long SomethingPage;
	long SomethingSize;
	vector<short> RandomMapIDs;
	vector<short> UnknownFSIDs;
	vector<short> UnknownSSIDs;
	vector<short> UnknownTSIDs;
	vector<short> Unknown4SIDs;
	vector<short> ResearchIDs;
	vector<short> TechIDs;
	vector<short> EffectIDs;
	vector<short> TTAgeIDs;
	vector<short> TTAgeBuildIDs;
	vector<short> TTAgeUnitIDs;
	vector<short> TTAgeResIDs;
	vector<short> TTAgeUnknownIDs;
	vector<short> TTItemIDs;
	vector<short> TTUnknownItemIDs;
	vector<short> TTBuildConIDs;
	vector<short> TTBuildBuildIDs;
	vector<short> TTBuildUnitIDs;
	vector<short> TTBuildResIDs;
	vector<short> TTUnitConIDs;
	vector<short> TTUnitUnitIDs;
	vector<short> TTResConIDs;
	vector<short> TTResBuildIDs;
	vector<short> TTResUnitIDs;
	vector<short> TTResResIDs;

	vector<short> CivIDs;
	vector<short> ResourceIDs;
	short UnitCivID;
	vector<short> UnitIDs;
	vector<short> DamageGraphicIDs;
	vector<short> AttackIDs;
	vector<short> ArmorIDs;
	vector<short> CommandIDs;
	vector<short> UnitLineIDs;
	vector<short> UnitLineUnitIDs;
	vector<short> GraphicIDs;
	vector<short> DeltaIDs;
	vector<short> AttackSoundIDs;
	vector<short> TerrainIDs;
	vector<short> TerBorderIDs;
	vector<short> TerRestrictIDs;
	vector<short> TerRestrictTerIDs;
	vector<float> TerrainRestrictionSubCopyAccess;
	vector<short> SoundIDs;
	vector<short> SoundItemIDs;
	vector<short> ColorIDs;
	vector<short> BorderIDs;
	vector<short> FrameIDs;

	bool Added, SaveDat, SaveApf, WriteLangs, SaveLangs, LangWriteToLatest, UseCustomPath;
	short AGEwindow;
	int TimesOpened, SimultaneousFiles, GameVersion, DatUsed, SaveGameVersion;
	chrono::time_point<chrono::system_clock> endTime;
	genie::GameVersion GenieVersion;
	wxString DriveLetter, Language, CustomFolder;
	wxString DatFileName, ApfFileName;
	wxString SaveDatFileName, SaveApfFileName;
	int LangsUsed; // 0x01 Lang.dll, 0x02, LangX1.dll, 0x04 LangX1P1.dll
	wxString LangCharset;
	wxString LangFileName, LangX1FileName, LangX1P1FileName;
	wxString SaveLangFileName, SaveLangX1FileName, SaveLangX1P1FileName;

	HINSTANCE LanguageDLL[3];
	string LangDLLstring(int ID, int Letters = 0);
	//void WriteLangDLLstring(int ID, wxString Name);

//	Constants, remove unneeded entries.

	enum
	{
		MenuOption_Prompt = wxID_HIGHEST + 1,
		MenuOption_IDFix,
		MenuOption_Buttons,
		MenuOption_Tips,
		MenuOption_About,
		ToolBar_Open,
		ToolBar_Save,
		ToolBar_Show,
		ToolBar_Help,
		ToolBar_Hex,
		ToolBar_Float
	};

//	User Interface

	wxMenuBar *MenuBar_Main;
	wxMenu *SubMenu_Options;
	wxMenu *SubMenu_Help;

	wxNotebook *TabBar_Main;
	wxNotebook *TabBar_TechTree;

	wxPanel *Tab_General;
	wxPanel *Tab_Research;
	wxPanel *Tab_Techs;
	wxPanel *Tab_TechTrees;
	wxPanel *Tab_Civs;
	wxPanel *Tab_Units;	// Unit tab
	wxPanel *Tab_UnitLine;
	wxPanel *Tab_Graphics;
	wxPanel *Tab_Terrains;
	wxPanel *Tab_TerrainBorders;
	wxPanel *Tab_TerrainRestrictions;
	wxPanel *Tab_Sounds;
	wxPanel *Tab_PlayerColors;
	wxPanel *Tab_Unknown;

	wxPanel *Tab_TechTreeAges;
	wxPanel *Tab_TechTreeBuildings;
	wxPanel *Tab_TechTreeUnits;
	wxPanel *Tab_TechTreeResearches;

//	wxPanel *Tab_DRS;

//	General user interface

	wxBoxSizer *General_Main;
	wxBoxSizer *General_TopRow;
	wxButton *General_Refresh;
	wxStaticText *General_CalcBoxes_Text;
	wxStaticText *General_CalcBoxesMiddle_Text;
	wxTextCtrl *General_CalcBoxes[5];
	wxScrolledWindow *General_Scroller;
	wxBoxSizer *General_ScrollArea;
	wxBoxSizer *General_ScrollSpace;
	wxBoxSizer *General_TerrainHeader_Holder;
	wxStaticText *General_TerrainHeader_Text;
	wxGridSizer *General_TerrainHeader_Grid;
	array<TextCtrl_Short*, 70> General_TerrainHeader;

	wxBoxSizer *General_BorderRelated_Holder;
	wxStaticText *General_BorderRelated_Text;
	wxGridSizer *General_BorderRelated_Grid;
	array<TextCtrl_Short*, 14> General_AfterBorders;

	wxBoxSizer *General_TerrainRendering_Holder;
	wxStaticText *General_TerrainRendering_Text;
	wxGridSizer *General_TerrainRendering_Grid;
	array<TextCtrl_Short*, 24> General_TerrainRendering;
	wxGridSizer *General_Something_Grid;
	array<TextCtrl_Long*, 157> General_Something;

	wxBoxSizer *Borders_Main;
	wxBoxSizer *Borders_ListArea;
	wxStaticBoxSizer *Borders_Borders;
	wxGridSizer *Borders_Buttons;
	wxTextCtrl *Borders_Search;
	wxTextCtrl *Borders_Search_R;
	wxListBox *Borders_List;
	wxButton *Borders_Copy;
	wxButton *Borders_Paste;
	wxBoxSizer *Borders_DataArea;
	wxBoxSizer *Borders_DataTopRow;
	wxGridSizer *Borders_Data1;
	wxBoxSizer *Borders_FrameData;
	wxStaticBoxSizer *Borders_Frames_Holder;
	wxBoxSizer *Borders_Frames;
	wxGridSizer *Borders_Frames_Buttons;
	wxTextCtrl *Borders_Frames_Search;
	wxTextCtrl *Borders_Frames_Search_R;
	wxListBox *Borders_Frames_List;
	wxButton *Frames_Copy;
	wxButton *Frames_Paste;
	wxButton *Frames_CopyToBorders;
	wxBoxSizer *Borders_FrameArea_Holder;
	wxGridSizer *Borders_Unknonws;
	wxBoxSizer *Borders_Enabled_Holder;
	wxBoxSizer *Borders_Enabled1_Holder;
	wxStaticText *Borders_Enabled_Text;
	TextCtrl_Short *Borders_Enabled;
	CheckBox_2State *Borders_Enabled_CheckBox;
	wxBoxSizer *Borders_Name_Holder[2];
	wxStaticText *Borders_Name_Text[2];
	TextCtrl_String *Borders_Name[2];
	wxBoxSizer *Borders_SLP_Holder;
	wxStaticText *Borders_SLP_Text;
	TextCtrl_Long *Borders_SLP;
	wxBoxSizer *Borders_Unknown3_Holder;
	wxStaticText *Borders_Unknown3_Text;
	TextCtrl_Float *Borders_Unknown3;
	wxBoxSizer *Borders_Unknown4_Holder;
	wxStaticText *Borders_Unknown4_Text;
	TextCtrl_Long *Borders_Unknown4;
	wxBoxSizer *Borders_Colors_Holder;
	wxGridSizer *Borders_Colors_Grid;
	wxStaticText *Borders_Colors_Text;
	array<TextCtrl_UByte*, 3> Borders_Colors;
	wxBoxSizer *Borders_Unknown5_Holder;
	wxGridSizer *Borders_Unknown5_Grid;
	wxStaticText *Borders_Unknown5_Text;
	array<TextCtrl_Byte*, 5> Borders_Unknown5;
	wxBoxSizer *Borders_Unknown6_Holder;
	wxStaticText *Borders_Unknown6_Text;
	TextCtrl_Float *Borders_Unknown6;
	wxBoxSizer *Borders_FrameID_Holder;
	wxStaticText *Borders_FrameID_Text;
	TextCtrl_Short *Borders_FrameID;
	wxBoxSizer *Borders_Flag1_Holder;
	wxStaticText *Borders_Flag1_Text;
	TextCtrl_Short *Borders_Flag1;
	wxBoxSizer *Borders_Flag2_Holder;
	wxStaticText *Borders_Flag2_Text;
	TextCtrl_Short *Borders_Flag2;
	wxBoxSizer *Borders_FrameCount_Holder;
	wxStaticText *Borders_FrameCount_Text;
	TextCtrl_Short *Borders_FrameCount;
	wxBoxSizer *Borders_Unknown8_Holder;
	wxStaticText *Borders_Unknown8_Text;
	TextCtrl_Short *Borders_Unknown8;
	wxBoxSizer *Borders_Terrain_Holder;
	wxStaticText *Borders_Terrain_Text;
	TextCtrl_Short *Borders_Terrain;
	ComboBox_Plus1 *Borders_Terrain_ComboBox;
	wxBoxSizer *Borders_Unknown1_Holder;
	wxStaticText *Borders_Unknown1_Text;
	TextCtrl_Short *Borders_Unknown1;

	wxGridSizer *General_Variables_Grid;
	wxGridSizer *General_Variables2_Grid;
	wxStaticBoxSizer *General_Variables1_Holder;
	wxStaticBoxSizer *General_Variables2_Holder;
	wxBoxSizer *General_SUnknown7_Holder;
	wxStaticText *General_SUnknown7_Text;
	TextCtrl_Byte *General_SUnknown7;
	wxBoxSizer *General_SUnknown8_Holder;
	wxStaticText *General_SUnknown8_Text;
	TextCtrl_Byte *General_SUnknown8;
	wxBoxSizer *General_SUnknown2_Holder;
	wxStaticText *General_SUnknown2_Text;
	TextCtrl_Long *General_SUnknown2;
	wxBoxSizer *General_SUnknown3_Holder;
	wxStaticText *General_SUnknown3_Text;
	TextCtrl_Long *General_SUnknown3;
	wxBoxSizer *General_SUnknown4_Holder;
	wxStaticText *General_SUnknown4_Text;
	TextCtrl_Long *General_SUnknown4;
	wxBoxSizer *General_SUnknown5_Holder;
	wxStaticText *General_SUnknown5_Text;
	TextCtrl_Long *General_SUnknown5;
	array<wxBoxSizer*, 8> General_TTUnknown_Holder;
	array<wxStaticText*, 8> General_TTUnknown_Text;
	array<TextCtrl_Long*, 8> General_TTUnknown;

	//wxBoxSizer *General_RenderPlusUnknown_Holder;
	//wxBoxSizer *General_RenderPlusUnknownTop_Holder;
	//wxStaticText *General_TechTree_Text;
	//wxTextCtrl *General_SomethingPicker;
	//wxButton *General_SomethingNext;
	//wxButton *General_SomethingPrev;
	//wxStaticText *General_SomethingSize;
	//wxGridSizer *General_TechTree_Grid;
	//array<TextCtrl_Long*, 128> General_Something;

	wxBoxSizer *Unknown_Main;
	wxBoxSizer *Unknown_Area;
	wxScrolledWindow *Unknown_Scroller;
	wxBoxSizer *Unknown_ScrollArea;
	wxBoxSizer *Unknown_ScrollSpace;

	wxGridSizer *Unknown_UnknownPointer_Grid;
	wxBoxSizer *Unknown_UnknownPointer_Holder;
	wxStaticText *Unknown_UnknownPointer_Text;
	TextCtrl_Long *Unknown_UnknownPointer;

	wxStaticBoxSizer *Unknowns;
	wxBoxSizer *Unknowns_ListArea;
	wxTextCtrl *Unknowns_Search;
	wxTextCtrl *Unknowns_Search_R;
	wxListBox *Unknowns_List;
	wxGridSizer *Unknowns_Buttons;
	wxButton *Unknowns_Add;
	wxButton *Unknowns_Insert;
	wxButton *Unknowns_Delete;
	wxButton *Unknowns_Copy;
	wxButton *Unknowns_Paste;
	wxButton *Unknowns_PasteInsert;

	wxBoxSizer *Unknowns_Space_UnknownLevel;
	wxBoxSizer *Unknowns_UnknownLevel_Holder;
	wxStaticText *Unknowns_UnknownLevel_Text;
	TextCtrl_Long *Unknowns_UnknownLevel;
	wxGridSizer *Unknowns_Unknown1_Grid;
	array<wxBoxSizer*, 9> Unknowns_Unknown1_Holder;
	array<wxStaticText*, 9> Unknowns_Unknown1_Text;
	array<TextCtrl_Long*, 9> Unknowns_Unknown1;
	wxBoxSizer *Unknowns_Space_Pointer1;
	wxBoxSizer *Unknowns_Pointer1_Holder;
	wxStaticText *Unknowns_Pointer1_Text;
	TextCtrl_Long *Unknowns_Pointer1;
	wxBoxSizer *Unknowns_Space_Pointer2;
	wxBoxSizer *Unknowns_Pointer2_Holder;
	wxStaticText *Unknowns_Pointer2_Text;
	TextCtrl_Long *Unknowns_Pointer2;
	wxBoxSizer *Unknowns_Space_Pointer3;
	wxBoxSizer *Unknowns_Pointer3_Holder;
	wxStaticText *Unknowns_Pointer3_Text;
	TextCtrl_Long *Unknowns_Pointer3;
	wxBoxSizer *Unknowns_Space_Pointer4;
	wxBoxSizer *Unknowns_Pointer4_Holder;
	wxStaticText *Unknowns_Pointer4_Text;
	TextCtrl_Long *Unknowns_Pointer4;

	wxStaticBoxSizer *RMSBaseZones;
	wxBoxSizer *RMSBaseZones_ListArea;
	wxBoxSizer *RMSBaseZones_DataArea;
	wxTextCtrl *RMSBaseZones_Search;
	wxTextCtrl *RMSBaseZones_Search_R;
	wxListBox *RMSBaseZones_List;
	wxGridSizer *RMSBaseZones_Buttons;
	wxButton *RMSBaseZones_Add;
	wxButton *RMSBaseZones_Insert;
	wxButton *RMSBaseZones_Delete;
	wxButton *RMSBaseZones_Copy;
	wxButton *RMSBaseZones_Paste;
	wxButton *RMSBaseZones_PasteInsert;
	wxButton *RMSBaseZones_CopyToMaps;

	wxGridSizer *RMSBaseZones_Unknown1_Grid;

	wxBoxSizer *RMSBaseZones_Unknown1_Holder;
	wxStaticText *RMSBaseZones_Unknown1_Text;
	TextCtrl_Long *RMSBaseZones_Unknown1;
	wxBoxSizer *RMSBaseZones_BaseTerrain_Holder;
	wxStaticText *RMSBaseZones_BaseTerrain_Text;
	TextCtrl_Long *RMSBaseZones_BaseTerrain;
	wxBoxSizer *RMSBaseZones_SpacingBetweenPlayers_Holder;
	wxStaticText *RMSBaseZones_SpacingBetweenPlayers_Text;
	TextCtrl_Long *RMSBaseZones_SpacingBetweenPlayers;
	wxBoxSizer *RMSBaseZones_Unknown4_Holder;
	wxStaticText *RMSBaseZones_Unknown4_Text;
	TextCtrl_Long *RMSBaseZones_Unknown4;

	wxBoxSizer *RMSBaseZones_Unknown5_Holder;
	wxGridSizer *RMSBaseZones_Unknown5_Grid;
	wxStaticText *RMSBaseZones_Unknown5_Text;
	array<TextCtrl_Byte*, 4> RMSBaseZones_Unknown5;

	wxBoxSizer *RMSBaseZones_Unknown6_Holder;
	wxStaticText *RMSBaseZones_Unknown6_Text;
	TextCtrl_Long *RMSBaseZones_Unknown6;
	wxBoxSizer *RMSBaseZones_Unknown7_Holder;
	wxStaticText *RMSBaseZones_Unknown7_Text;
	TextCtrl_Long *RMSBaseZones_Unknown7;

	wxBoxSizer *RMSBaseZones_Unknown8_Holder;
	wxGridSizer *RMSBaseZones_Unknown8_Grid;
	wxStaticText *RMSBaseZones_Unknown8_Text;
	array<TextCtrl_Byte*, 4> RMSBaseZones_Unknown8;

	wxBoxSizer *RMSBaseZones_StartAreaRadius_Holder;
	wxStaticText *RMSBaseZones_StartAreaRadius_Text;
	TextCtrl_Long *RMSBaseZones_StartAreaRadius;
	wxBoxSizer *RMSBaseZones_Unknown10_Holder;
	wxStaticText *RMSBaseZones_Unknown10_Text;
	TextCtrl_Long *RMSBaseZones_Unknown10;
	wxBoxSizer *RMSBaseZones_Unknown11_Holder;
	wxStaticText *RMSBaseZones_Unknown11_Text;
	TextCtrl_Long *RMSBaseZones_Unknown11;

	wxStaticBoxSizer *RMSTerrain;
	wxBoxSizer *RMSTerrain_ListArea;
	wxBoxSizer *RMSTerrain_DataArea;
	wxTextCtrl *RMSTerrain_Search;
	wxTextCtrl *RMSTerrain_Search_R;
	wxListBox *RMSTerrain_List;
	wxGridSizer *RMSTerrain_Buttons;
	wxButton *RMSTerrain_Add;
	wxButton *RMSTerrain_Insert;
	wxButton *RMSTerrain_Delete;
	wxButton *RMSTerrain_Copy;
	wxButton *RMSTerrain_Paste;
	wxButton *RMSTerrain_PasteInsert;
	wxButton *RMSTerrain_CopyToMaps;

	wxGridSizer *RMSTerrain_Unknown1_Grid;
	array<wxBoxSizer*, 6> RMSTerrain_Unknown1_Holder;
	array<wxStaticText*, 6> RMSTerrain_Unknown1_Text;
	array<TextCtrl_Long*, 6> RMSTerrain_Unknown1;

	wxStaticBoxSizer *RMSUnit;
	wxBoxSizer *RMSUnit_ListArea;
	wxBoxSizer *RMSUnit_DataArea;
	wxTextCtrl *RMSUnit_Search;
	wxTextCtrl *RMSUnit_Search_R;
	wxListBox *RMSUnit_List;
	wxGridSizer *RMSUnit_Buttons;
	wxButton *RMSUnit_Add;
	wxButton *RMSUnit_Insert;
	wxButton *RMSUnit_Delete;
	wxButton *RMSUnit_Copy;
	wxButton *RMSUnit_Paste;
	wxButton *RMSUnit_PasteInsert;
	wxButton *RMSUnit_CopyToMaps;

	wxGridSizer *RMSUnit_Unknown1_Grid;
	wxBoxSizer *RMSUnit_Unit_Holder;
	wxStaticText *RMSUnit_Unit_Text;
	TextCtrl_Long *RMSUnit_Unit;
	wxBoxSizer *RMSUnit_HostTerrain_Holder;
	wxStaticText *RMSUnit_HostTerrain_Text;
	TextCtrl_Long *RMSUnit_HostTerrain;
	wxBoxSizer *RMSUnit_Unknown3_Holder;
	wxGridSizer *RMSUnit_Unknown3_Grid;
	wxStaticText *RMSUnit_Unknown3_Text;
	array<TextCtrl_Byte*, 4> RMSUnit_Unknown3;
	wxBoxSizer *RMSUnit_ObjectsPerPlayer_Holder;
	wxStaticText *RMSUnit_ObjectsPerPlayer_Text;
	TextCtrl_Long *RMSUnit_ObjectsPerPlayer;
	wxBoxSizer *RMSUnit_Unknown5_Holder;
	wxStaticText *RMSUnit_Unknown5_Text;
	TextCtrl_Long *RMSUnit_Unknown5;
	wxBoxSizer *RMSUnit_GroupsPerPlayer_Holder;
	wxStaticText *RMSUnit_GroupsPerPlayer_Text;
	TextCtrl_Long *RMSUnit_GroupsPerPlayer;
	wxBoxSizer *RMSUnit_Unknown7_Holder;
	wxStaticText *RMSUnit_Unknown7_Text;
	TextCtrl_Long *RMSUnit_Unknown7;
	wxBoxSizer *RMSUnit_OwnAtStart_Holder;
	wxStaticText *RMSUnit_OwnAtStart_Text;
	TextCtrl_Long *RMSUnit_OwnAtStart;
	wxBoxSizer *RMSUnit_SetPlaceForAllPlayers_Holder;
	wxStaticText *RMSUnit_SetPlaceForAllPlayers_Text;
	TextCtrl_Long *RMSUnit_SetPlaceForAllPlayers;
	wxBoxSizer *RMSUnit_MinDistanceToPlayers_Holder;
	wxStaticText *RMSUnit_MinDistanceToPlayers_Text;
	TextCtrl_Long *RMSUnit_MinDistanceToPlayers;
	wxBoxSizer *RMSUnit_MaxDistanceToPlayers_Holder;
	wxStaticText *RMSUnit_MaxDistanceToPlayers_Text;
	TextCtrl_Long *RMSUnit_MaxDistanceToPlayers;

	wxStaticBoxSizer *RMSUnknown;
	wxBoxSizer *RMSUnknown_ListArea;
	wxBoxSizer *RMSUnknown_DataArea;
	wxTextCtrl *RMSUnknown_Search;
	wxTextCtrl *RMSUnknown_Search_R;
	wxListBox *RMSUnknown_List;
	wxGridSizer *RMSUnknown_Buttons;
	wxButton *RMSUnknown_Add;
	wxButton *RMSUnknown_Insert;
	wxButton *RMSUnknown_Delete;
	wxButton *RMSUnknown_Copy;
	wxButton *RMSUnknown_Paste;
	wxButton *RMSUnknown_PasteInsert;
	wxButton *RMSUnknown_CopyToMaps;

	wxGridSizer *RMSUnknown_Unknown1_Grid;
	array<wxBoxSizer*, 6> RMSUnknown_Unknown1_Holder;
	array<wxStaticText*, 6> RMSUnknown_Unknown1_Text;
	array<TextCtrl_Long*, 6> RMSUnknown_Unknown1;

//	Researchs user interface

	wxBoxSizer *Research_Main;
	wxBoxSizer *Research_ListArea;
	wxGridSizer *Research_Research_Buttons;
	wxBoxSizer *Research_DataArea;
	wxScrolledWindow *Research_Scroller;
	wxBoxSizer *Research_ScrollArea;
	wxBoxSizer *Research_ScrollSpace;
	wxGridSizer *Research_MiscArea1_Grid;
	wxBoxSizer *Research_LangDLLArea_Holder;
	wxBoxSizer *Research_Misc2_Holder;
	wxBoxSizer *Research_PointerArea_Holder;
	wxBoxSizer *Research_Names_Holder;

	wxStaticBoxSizer *Research_Research;
	wxBoxSizer *Research_Research_Searches[2];
	wxTextCtrl *Research_Research_Search;
	wxTextCtrl *Research_Research_Search_R;
	wxOwnerDrawnComboBox *Research_SearchFilters[2];
	wxCheckBox *Research_Research_UseAnd[2];
	wxListBox *Research_Research_List;
	wxButton *Research_Add;
	wxButton *Research_Insert;
	wxButton *Research_Delete;
	wxButton *Research_Copy;
	wxButton *Research_Paste;
	wxButton *Research_PasteInsert;

	wxBoxSizer *Research_RequiredTechArea_Holder;
	wxGridSizer *Research_RequiredTechs_Holder;
	wxStaticText *Research_RequiredTechArea_Text;
	TextCtrl_Short *Research_RequiredTechs[6];
	ComboBox_Plus1 *Research_RequiredTechs_ComboBox[6];
	wxBoxSizer *Research_RequiredTechCount_Holder;
	wxStaticText *Research_RequiredTechCount_Text;
	TextCtrl_Short *Research_RequiredTechCount;

	wxStaticBoxSizer *Research_CostHeader_Holder;
	wxBoxSizer *Research_CostType_Holder;
	wxBoxSizer *Research_CostAmount_Holder;
	wxBoxSizer *Research_CostUsed_Holder;
	wxStaticText *Research_Resources_Text;
	wxGridSizer *Research_ResourceGrid;
	TextCtrl_Short *Research_Resources[3];
	ComboBox_Plus1 *Research_Resources_ComboBox[3];
	wxStaticText *Research_Amount_Text;
	TextCtrl_Short *Research_Amount[3];
	wxStaticText *Research_Used_Text;
	TextCtrl_Byte *Research_Used[3];
	CheckBox_2State *Research_Used_CheckBox[3];

	wxBoxSizer *Research_Civ_Holder;
	wxStaticText *Research_Civ_Text;
	TextCtrl_Short *Research_Civ;
	ComboBox_Plus1 *Research_Civ_ComboBox;

	wxBoxSizer *Research_FullTechMode_Holder;
	wxStaticText *Research_FullTechMode_Text;
	TextCtrl_Short *Research_FullTechMode;
	CheckBox_2State *Research_FullTechMode_CheckBox;

	wxBoxSizer *Research_ResearchLocation_Holder;
	wxStaticText *Research_ResearchLocation_Text;
	TextCtrl_Short *Research_ResearchLocation;
	ComboBox_Plus1 *Research_ResearchLocation_ComboBox;

	wxBoxSizer *Research_LangDLLName_Holder;
	wxStaticText *Research_LangDLLName_Text;
	TextCtrl_UShort *Research_LangDLLName;
	TextCtrl_DLL *Research_DLL_LangDLLName;

	wxBoxSizer *Research_LangDLLDescription_Holder;
	wxStaticText *Research_LangDLLDescription_Text;
	TextCtrl_UShort *Research_LangDLLDescription;
	TextCtrl_DLL *Research_DLL_LangDLLDescription;

	wxBoxSizer *Research_ResearchTime_Holder;
	wxStaticText *Research_ResearchTime_Text;
	TextCtrl_Short *Research_ResearchTime;

	wxBoxSizer *Research_TechID_Holder;
	wxStaticText *Research_TechID_Text;
	TextCtrl_Short *Research_TechID;
	ComboBox_Plus1 *Research_TechID_ComboBox;

	wxBoxSizer *Research_Type_Holder;
	wxStaticText *Research_Type_Text;
	TextCtrl_Short *Research_Type;

	wxBoxSizer *Research_IconID_Holder;
	wxStaticText *Research_IconID_Text;
	TextCtrl_Short *Research_IconID;

	wxBoxSizer *Research_ButtonID_Holder;
	wxStaticText *Research_ButtonID_Text;
	TextCtrl_Byte *Research_ButtonID;

	wxBoxSizer *Research_LanguageDLLHelp_Holder;
	wxStaticText *Research_LanguageDLLHelp_Text;
	TextCtrl_Long *Research_LanguageDLLHelp;
	wxBoxSizer *Research_LanguageDLLName2_Holder;
	wxStaticText *Research_LanguageDLLName2_Text;
	TextCtrl_Long *Research_LanguageDLLName2;
	wxBoxSizer *Research_Unknown1_Holder;
	wxStaticText *Research_Unknown1_Text;
	TextCtrl_Long *Research_Unknown1;
	TextCtrl_DLL *Research_DLL_LanguageDLLHelp;
	TextCtrl_DLL *Research_DLL_LanguageDLLName2;
	wxBoxSizer *Research_LanguageDLLConverter_Holder[2];
	wxStaticText *Research_LanguageDLLConverter_Text[2];
	wxTextCtrl *Research_LanguageDLLConverter[2];

	wxBoxSizer *Research_Name_Holder[2];
	wxStaticText *Research_Name_Text[2];
	TextCtrl_String *Research_Name[2];

//	Techs user interface

	wxBoxSizer *Techs_Main;
	wxBoxSizer *Techs_ListArea;
	wxGridSizer *Techs_Buttons;
	wxBoxSizer *Effects_ListArea;
	wxGridSizer *Techs_Effects_Buttons;
	wxBoxSizer *Effects_DataAreaProperties;
	wxCheckBox *Effects_NeverHide;
	wxBoxSizer *Effects_DataA_Holder;
	wxBoxSizer *Effects_DataB_Holder;
	wxBoxSizer *Effects_DataC_Holder;
	wxBoxSizer *Effects_DataD_Holder;
	wxBoxSizer *Effects_DataE_Holder;	// for attack/armor amount
	wxBoxSizer *Effects_DataF_Holder;	// for attack/armor class
	wxBoxSizer *Effects_A_Holder;
	wxBoxSizer *Effects_B_Holder;
	wxBoxSizer *Effects_C_Holder;
	wxBoxSizer *Effects_D_Holder;
	wxBoxSizer *Effects_E_Holder;	// for attack/armor amount
	wxBoxSizer *Effects_F_Holder;	// for attack/armor class

	wxStaticText *Effects_E_Text;
	wxTextCtrl *Effects_E;	// amount
	wxStaticText *Effects_Info_E;
	wxStaticText *Effects_F_Text;
	TextCtrl_Short *Effects_F;	// class
	wxStaticText *Effects_Info_F;

	wxStaticBoxSizer *Techs_Techs;
	wxBoxSizer *Techs_Searches[2];
	wxTextCtrl *Techs_Search;
	wxTextCtrl *Techs_Search_R;
	wxCheckBox *Techs_UseAnd[2];
	wxListBox *Techs_List;
	wxButton *Techs_Rename;
	wxButton *Techs_Restore;
	wxButton *Techs_Add;
	wxButton *Techs_Insert;
	wxButton *Techs_Delete;
	wxButton *Techs_Copy;
	wxButton *Techs_Paste;
	wxButton *Techs_PasteInsert;

	wxStaticBoxSizer *Techs_AllEffects;
	wxBoxSizer *Techs_AllEffects_Searches[2];
	wxTextCtrl *Techs_AllEffects_Search;
	wxTextCtrl *Techs_AllEffects_Search_R;
	wxCheckBox *Techs_AllEffects_UseAnd[2];
	wxListBox *Techs_AllEffects_List;
	wxBoxSizer *Techs_AllEffects_Buttons;
	wxButton *Techs_AllEffects_Load;
	wxButton *Techs_AllEffects_Clear;

	wxBoxSizer *Techs_Name_Holder;
	wxStaticText *Techs_Name_Text;
	TextCtrl_String *Techs_Name;

	wxStaticBoxSizer *Techs_Effects;
	wxBoxSizer *Techs_Effects_Searches[2];
	wxTextCtrl *Techs_Effects_Search;
	wxTextCtrl *Techs_Effects_Search_R;
	wxCheckBox *Techs_Effects_UseAnd[2];
	wxListBox *Techs_Effects_List;
	wxButton *Techs_Effects_Add;
	wxButton *Techs_Effects_Insert;
	wxButton *Techs_Effects_Delete;
	wxButton *Techs_Effects_Copy;
	wxButton *Techs_Effects_Paste;
	wxButton *Techs_Effects_PasteInsert;
	wxButton *Techs_Effects_CopyToTechs;

	wxBoxSizer *Effects_DataArea;

	wxBoxSizer *Effects_Type_Holder;
	wxBoxSizer *Effects_Type2_Holder;
	wxStaticText *Effects_Type_Text;
	ComboBox_EffectType *Effects_Type_ComboBox;
	TextCtrl_Byte *Effects_Type;
	wxStaticBoxSizer *Effects_Data_Holder;
	wxStaticText *Effects_A_Text;
	TextCtrl_Short *Effects_A;
	wxBoxSizer *Effects_A_ComboBox;	// Space reserver, never used.
	ComboBox_Plus1 *Effects_UnitsA_ComboBox;	// for Effects 0, 2, 3, 4, 5
	ComboBox_Plus1 *Effects_ResourcesA_ComboBox;	// for Effects 1, 6
	ComboBox_Plus1 *Effects_ResearchsA_ComboBox;	// for Effects 101, 103
	wxStaticText *Effects_Info_A;
	wxStaticText *Effects_B_Text;
	TextCtrl_Short *Effects_B;
	wxBoxSizer *Effects_B_ComboBox;	// Space reserver, never used.
	CheckBox_2State *Effects_ModeB_CheckBox;	// for Effects 1, 2
	ComboBox_Plus1 *Effects_UnitsB_ComboBox;	// for Effects 3
	ComboBox_Plus1 *Effects_ResourcesB_ComboBox;	// for Effects 101
	wxStaticText *Effects_Info_B;
	wxStaticText *Effects_C_Text;
	TextCtrl_Short *Effects_C;
	wxBoxSizer *Effects_C_ComboBox;	// Space reserver, never used.
	CheckBox_2State *Effects_ModeC_CheckBox;	// for Effects 101, 103
	ComboBox_EffectAttribute *Effects_AttributesC_ComboBox;	// for Effects 0, 4, 5
	wxStaticText *Effects_Info_C;
	wxStaticText *Effects_D_Text;
	TextCtrl_Float *Effects_D;
	wxBoxSizer *Effects_D_ComboBox;	// Space reserver, never used.
	ComboBox_Plus1 *Effects_ResearchsD_ComboBox;	// for Effects 102
	wxStaticText *Effects_Info_D;
	wxHyperlinkCtrl *Effects_Link;

//	Civs user interface

	wxBoxSizer *Civs_Main;
	wxBoxSizer *Civs_ListArea;
	wxGridSizer *Civs_Civs_Buttons;
	wxStaticBoxSizer *Civs_Civs;
	wxTextCtrl *Civs_Civs_Search;
	wxTextCtrl *Civs_Civs_Search_R;
	wxListBox *Civs_Civs_List;
	wxButton *Civs_Add;
	wxButton *Civs_Insert;
	wxButton *Civs_Delete;
	wxButton *Civs_Copy;
	wxButton *Civs_Paste;
	wxButton *Civs_PasteInsert;

	wxBoxSizer *Civs_DataArea;
	wxGridSizer *Civs_DataGrid1;
	wxGridSizer *Civs_DataGrid2;
	wxGridSizer *Civs_DataGrid3;
	wxStaticText *Civs_One_Text;
	wxBoxSizer *Civs_One_Holder;
	TextCtrl_Byte *Civs_One;
	wxBoxSizer *Civs_Name_Holder[2];
	wxStaticText *Civs_Name_Text[2];
	TextCtrl_String *Civs_Name[2];
	wxBoxSizer *Civs_SUnknown1_Holder;
	wxStaticText *Civs_SUnknown1_Text;
	TextCtrl_Short *Civs_SUnknown1[4];
	wxBoxSizer *Civs_TechTree_Holder;
	wxStaticText *Civs_TechTree_Text;
	TextCtrl_Short *Civs_TechTree;
	ComboBox_Plus1 *Civs_TechTree_ComboBox;
	wxBoxSizer *Civs_TeamBonus_Holder;
	wxStaticText *Civs_TeamBonus_Text;
	TextCtrl_Short *Civs_TeamBonus;
	ComboBox_Plus1 *Civs_TeamBonus_ComboBox;
	wxBoxSizer *Civs_GraphicSet_Holder;
	wxStaticText *Civs_GraphicSet_Text;
	TextCtrl_Byte *Civs_GraphicSet;
	wxBoxSizer *Civs_Resources_Holder;
	wxStaticBoxSizer *Civs_Resources;
	wxTextCtrl *Civs_Resources_Search;
	wxTextCtrl *Civs_Resources_Search_R;
	wxListBox *Civs_Resources_List;
	wxGridSizer *Civs_Resources_Buttons;
	wxButton *Resources_Add;
	wxButton *Resources_Insert;
	wxButton *Resources_Delete;
	wxButton *Resources_Copy;
	wxButton *Resources_Paste;
	wxButton *Resources_PasteInsert;
	wxButton *Resources_CopyToAll;
	wxBoxSizer *Civs_Resources_Data;
	wxBoxSizer *Civs_ResourceValue_Holder;
	wxStaticText *Civs_ResourceValue_Text;
	TextCtrl_Float *Civs_ResourceValue;
	wxHyperlinkCtrl *Civs_Resources_Holder_Link;

//	Units user interface

//	Data container types:
/*
	wxBoxSizer *invisible_borders_window;
	wxStaticBoxSizer *visible_borders_window;
	wxCollapsiblePane *hide_button_window;	// Doesn't work!
	wxScrollBar *window_scroller;
	wxTextCtrl *editable_text;
	wxComboBox *drop_down_list;
	wxCheckBoc *check_box;
	wxStaticText *uneditable_text;
	wxHyperlinkCtrl *web_link;

//	Own text controls

	VBoolTextCtrl *text 0 or 1;	DOES NOT EXIST, CREATE? DON'T!
	TextCtrl_Byte *text -128 to 127;
	TextCtrl_Float *text +/- 3.4e +/- 38 (~7 digits);
	TextCtrl_Long *text -2147483648 to 2147483647;
	TextCtrl_Short *text -32768 to 32767;
	TextCtrl_String *text pure text;
*/
//	Data Containers
//	Type 10+

	wxScrolledWindow *Units_Scroller;	// Scrollable unit section

	TextCtrl_Byte *Units_Type;
	wxOwnerDrawnComboBox *Units_Type_ComboBox;
	TextCtrl_Short *Units_ID1;
	TextCtrl_UShort *Units_LanguageDLLName;
	TextCtrl_DLL *Units_DLL_LanguageName;
	TextCtrl_UShort *Units_LanguageDLLCreation;
	TextCtrl_DLL *Units_DLL_LanguageCreation;
	TextCtrl_Short *Units_Class;
	ComboBox_Plus1 *Units_Class_ComboBox[3];
	TextCtrl_Short *Units_StandingGraphic[2];
	ComboBox_Plus1 *Units_StandingGraphic_ComboBox[2];
	TextCtrl_Short *Units_DyingGraphic[2];
	ComboBox_Plus1 *Units_DyingGraphic_ComboBox[2];
	TextCtrl_Byte *Units_DeathMode;
	CheckBox_2State *Units_DeathMode_CheckBox;
	TextCtrl_Short *Units_HitPoints;
	TextCtrl_Float *Units_LineOfSight;
	TextCtrl_Byte *Units_GarrisonCapacity;
	TextCtrl_Float *Units_SizeRadius[2];
	TextCtrl_Float *Units_HPBarHeight1;
	TextCtrl_Short *Units_TrainSound[2];
	ComboBox_Plus1 *Units_TrainSound_ComboBox[2];
	TextCtrl_Short *Units_DeadUnitID;
	ComboBox_Plus1 *Units_DeadUnitID_ComboBox;
	TextCtrl_Byte *Units_PlacementMode;
	TextCtrl_Byte *Units_AirMode;
	CheckBox_2State *Units_AirMode_CheckBox;
	TextCtrl_Short *Units_IconID;
	TextCtrl_Byte *Units_HideInEditor;
	CheckBox_2State *Units_HideInEditor_CheckBox;
	TextCtrl_Short *Units_Unknown1;
	TextCtrl_Byte *Units_Enabled;
	CheckBox_2State *Units_Enabled_CheckBox;
	TextCtrl_Byte *Units_Disabled;
	CheckBox_2State *Units_Disabled_CheckBox;
	TextCtrl_Short *Units_PlacementBypassTerrain[2];
	ComboBox_Plus1 *Units_PlacementBypassTerrain_ComboBox[2];
	TextCtrl_Short *Units_PlacementTerrain[2];
	ComboBox_Plus1 *Units_PlacementTerrain_ComboBox[2];
	TextCtrl_Float *Units_EditorRadius[2];
	TextCtrl_Byte *Units_HillMode;
	TextCtrl_Byte *Units_VisibleInFog;
	wxStaticText *Units_VisibleInFog_Text;
	TextCtrl_Short *Units_TerrainRestriction;
	ComboBox_Plus1 *Units_TerrainRestriction_ComboBox;
	TextCtrl_Byte *Units_FlyMode;
	CheckBox_2State *Units_FlyMode_CheckBox;
	TextCtrl_Short *Units_ResourceCapacity;
	TextCtrl_Float *Units_ResourceDecay;
	TextCtrl_Byte *Units_BlastType;
	TextCtrl_Byte *Units_Unknown2;
	TextCtrl_Byte *Units_InteractionMode;
	TextCtrl_Byte *Units_MinimapMode;
	TextCtrl_Byte *Units_CommandAttribute;
	TextCtrl_Float *Units_Unknown3A;
	TextCtrl_UByte *Units_MinimapColor;
	TextCtrl_Long *Units_LanguageDLLHelp;
	TextCtrl_DLL *Units_DLL_LanguageHelp;
	wxTextCtrl *Units_LanguageDLLConverter[2];
	TextCtrl_Long *Units_LanguageDLLHotKeyText;
	TextCtrl_DLL *Units_DLL_LanguageHKText;
	TextCtrl_Long *Units_HotKey;
	TextCtrl_DLL *Units_DLL_HotKey4;
	TextCtrl_Byte *Units_Unselectable;
	CheckBox_2State *Units_Unselectable_CheckBox;
	TextCtrl_Byte *Units_Unknown6;
	TextCtrl_Byte *Units_Unknown7;
	TextCtrl_Byte *Units_Unknown8;
	TextCtrl_Byte *Units_SelectionMask;
	TextCtrl_Byte *Units_SelectionShapeType;
	TextCtrl_Byte *Units_SelectionShape;
	TextCtrl_UByte *Units_Attribute;
	wxGridSizer *Units_Attribute_Grid;
	wxCheckBox *Units_Attribute_CheckBox[8];
	TextCtrl_Byte *Units_Civ;
	ComboBox_Plus1 *Units_Civ_ComboBox;
	TextCtrl_Short *Units_Unknown9;
	TextCtrl_Byte *Units_SelectionEffect;
	TextCtrl_UByte *Units_EditorSelectionColour;
	wxBoxSizer *Units_SelectionRadiusBox;
	TextCtrl_Float *Units_SelectionRadius[2];
	TextCtrl_Float *Units_HPBarHeight2;
	TextCtrl_Short *ResourceStorage_Type[3];
	ComboBox_Plus1 *ResourceStorage_Type_ComboBox[3];
	TextCtrl_Float *ResourceStorage_Amount[3];
	TextCtrl_Byte *ResourceStorage_Enabled[3];
	TextCtrl_Short *Units_SelectionSound;
	ComboBox_Plus1 *Units_SelectionSound_ComboBox;
	TextCtrl_Short *Units_DyingSound;
	ComboBox_Plus1 *Units_DyingSound_ComboBox;
	TextCtrl_Byte *Units_AttackMode;
	TextCtrl_Byte *Units_EdibleMeat;
	TextCtrl_String *Units_Name;
	TextCtrl_String *Units_Name2;
	TextCtrl_Short *Units_Unitline;
	ComboBox_Plus1 *Units_Unitline_ComboBox;
	TextCtrl_Byte *Units_MinTechLevel;
	ComboBox_Plus1 *Units_MinTechLevel_ComboBox;
	TextCtrl_Short *Units_ID2;
	TextCtrl_Short *Units_ID3;

//	Type 20+

	TextCtrl_Float *Units_Speed;

//	Type 30+

	TextCtrl_Short *Units_WalkingGraphic[2];
	ComboBox_Plus1 *Units_WalkingGraphic_ComboBox[2];
	TextCtrl_Float *Units_RotationSpeed;
	TextCtrl_Byte *Units_Unknown11;
	TextCtrl_Short *Units_TrackingUnit;
	ComboBox_Plus1 *Units_TrackingUnit_ComboBox;
	TextCtrl_Byte *Units_TrackingUnitUsed;
	TextCtrl_Float *Units_TrackingUnitDensity;
	TextCtrl_Byte *Units_Unknown16;
	array<TextCtrl_Float*, 5> Units_Unknown16B;

//	Type 40+

	TextCtrl_Short *Units_SheepConversion;
	CheckBox_ZeroIsYes *Units_SheepConversion_CheckBox;
	TextCtrl_Float *Units_SearchRadius;
	TextCtrl_Float *Units_WorkRate;
	TextCtrl_Short *Units_DropSite[2];
	ComboBox_Plus1 *Units_DropSite_ComboBox[2];
	TextCtrl_Byte *Units_VillagerMode;
	TextCtrl_Short *Units_AttackSound;
	ComboBox_Plus1 *Units_AttackSound_ComboBox;
	TextCtrl_Short *Units_MoveSound;
	ComboBox_Plus1 *Units_MoveSound_ComboBox;
	TextCtrl_Byte *Units_AnimalMode;
	CheckBox_2State *Units_AnimalMode_CheckBox;
	TextCtrl_Byte *Units_Exists;

//	Type 50+

	TextCtrl_Short *Units_DefaultArmor;
	TextCtrl_Short *Units_TerRestrictionForDmgMultiply;
	ComboBox_Plus1 *Units_TerRestrictionForDmgMultiply_ComboBox;
	TextCtrl_Float *Units_MaxRange;
	TextCtrl_Float *Units_BlastRadius;
	TextCtrl_Float *Units_ReloadTime1;
	TextCtrl_Short *Units_ProjectileUnitID;
	ComboBox_Plus1 *Units_ProjectileUnitID_ComboBox;
	TextCtrl_Short *Units_AccuracyPercent;
	TextCtrl_Byte *Units_TowerMode;
	CheckBox_2State *Units_TowerMode_CheckBox;
	TextCtrl_Short *Units_Delay;
	TextCtrl_Float *Units_GraphicDisplacement[3];
	TextCtrl_Byte *Units_BlastLevel;
	TextCtrl_Float *Units_MinRange;
	TextCtrl_Float *Units_AccuracyErrorRadius;
	TextCtrl_Short *Units_AttackGraphic;
	ComboBox_Plus1 *Units_AttackGraphic_ComboBox;
	TextCtrl_Short *Units_DisplayedMeleeArmour;
	TextCtrl_Short *Units_DisplayedAttack;
	TextCtrl_Float *Units_DisplayedRange;
	TextCtrl_Float *Units_ReloadTime2;

//	Type 60 only

	TextCtrl_Byte *Units_StretchMode;
	TextCtrl_Byte *Units_CompensationMode;
	TextCtrl_Byte *Units_DropAnimationMode;
	TextCtrl_Byte *Units_PenetrationMode;
	TextCtrl_Byte *Units_Unknown24;
	TextCtrl_Float *Units_ProjectileArc;

//	Type 70+

	TextCtrl_Short *Units_CostType[3];
	ComboBox_Plus1 *Units_CostType_ComboBox[3];
	TextCtrl_Short *Units_CostAmount[3];
	TextCtrl_Short *Units_CostUsed[3];
	CheckBox_2State *Units_CostUsed_CheckBox[3];
	TextCtrl_Short *Units_TrainTime;
	TextCtrl_Short *Units_TrainLocationID;
	ComboBox_Plus1 *Units_TrainLocationID_ComboBox;
	TextCtrl_Byte *Units_ButtonID;
	TextCtrl_Long *Units_Unknown26;
	TextCtrl_Long *Units_Unknown27;
	TextCtrl_Byte *Units_Unknown28;
	TextCtrl_Byte *Units_HeroMode;
	CheckBox_2State *Units_HeroMode_CheckBox;
	TextCtrl_Long *Units_GarrisonGraphic;
	ComboBox_Plus1 *Units_GarrisonGraphic_ComboBox;
	TextCtrl_Float *Units_AttackMissileDuplicationAmount1;
	TextCtrl_Byte *Units_AttackMissileDuplicationAmount2;
	TextCtrl_Float *Units_AttackMissileDuplicationSpawning[3];
	TextCtrl_Long *Units_AttackMissileDuplicationUnit;
	ComboBox_Plus1 *Units_AttackMissileDuplicationUnit_ComboBox;
	TextCtrl_Long *Units_ChargingGraphic;
	ComboBox_Plus1 *Units_ChargingGraphic_ComboBox;
	TextCtrl_Byte *Units_ChargingMode;
	TextCtrl_Short *Units_DisplayedPierceArmour;

//	Type 80

	TextCtrl_Short *Units_ConstructionGraphicID;
	ComboBox_Plus1 *Units_ConstructionGraphicID_ComboBox;
	TextCtrl_Short *Units_SnowGraphicID;
	ComboBox_Plus1 *Units_SnowGraphicID_ComboBox;
	TextCtrl_Byte *Units_AdjacentMode;
	CheckBox_2State *Units_AdjacentMode_CheckBox;
	TextCtrl_Short *Units_IconDisabler;
	TextCtrl_Byte *Units_DisappearsWhenBuilt;
	CheckBox_2State *Units_Unknown31b_CheckBox;
	TextCtrl_Short *Units_StackUnitID;
	ComboBox_Plus1 *Units_StackUnitID_ComboBox;
	TextCtrl_Short *Units_TerrainID;
	ComboBox_Plus1 *Units_TerrainID_ComboBox;
	TextCtrl_Short *Units_OldTerrainLikeID;
	TextCtrl_Short *Units_ResearchID;
	ComboBox_Plus1 *Units_ResearchID_ComboBox;
	TextCtrl_Byte *Units_Unknown33;
	TextCtrl_Short *Units_AnnexUnit[4];
	ComboBox_Plus1 *Units_AnnexUnit_ComboBox[4];
	TextCtrl_Float *Units_AnnexUnitMisplacement[4][2];
	TextCtrl_Short *Units_HeadUnit;
	ComboBox_Plus1 *Units_HeadUnit_ComboBox;
	TextCtrl_Short *Units_TransformUnit;
	ComboBox_Plus1 *Units_TransformUnit_ComboBox;
	TextCtrl_Short *Units_UnknownSound;
	ComboBox_Plus1 *Units_UnknownSound_ComboBox;
	TextCtrl_Short *Units_ConstructionSound;
	ComboBox_Plus1 *Units_ConstructionSound_ComboBox;
	TextCtrl_UByte *Units_GarrisonType;
	wxGridSizer *Units_GarrisonType_Grid;
	wxCheckBox *Units_GarrisonType_CheckBox[8];
	TextCtrl_Float *Units_GarrisonHealRate;
	TextCtrl_Float *Units_Unknown35;
	TextCtrl_Short *Units_PileUnit;
	ComboBox_Plus1 *Units_PileUnit_ComboBox;
	array<TextCtrl_Byte*, 6> Units_LootSwitch;

//	Data Container Names
//	Type 10+

	wxStaticText *Units_Type_Text;
	wxStaticText *Units_ID1_Text;
	wxStaticText *Units_LanguageDLLName_Text;
	wxStaticText *Units_LanguageDLLCreation_Text;
	wxStaticText *Units_Class_Text;
	wxStaticText *Units_StandingGraphic_Text;
	wxStaticText *Units_DyingGraphic_Text;
	wxStaticText *Units_HitPoints_Text;
	wxStaticText *Units_LineOfSight_Text;
	wxStaticText *Units_GarrisonCapacity_Text;
	wxStaticText *Units_SizeRadius_Text;
	wxStaticText *Units_HPBarHeight1_Text;
	wxStaticText *Units_TrainSound_Text;
	wxStaticText *Units_DeadUnitID_Text;
	wxStaticText *Units_PlacementMode_Text;
	wxStaticText *Units_IconID_Text;
	wxStaticText *Units_Unknown1_Text;
	wxStaticText *Units_PlacementBypassTerrain_Text;
	wxStaticText *Units_PlacementTerrain_Text;
	wxStaticText *Units_EditorRadius_Text;
	wxStaticText *Units_HillMode_Text;
	wxStaticText *Units_TerrainRestriction_Text;
	wxStaticText *Units_ResourceCapacity_Text;
	wxStaticText *Units_ResourceDecay_Text;
	wxStaticText *Units_BlastType_Text;
	wxStaticText *Units_Unknown2_Text;
	wxStaticText *Units_InteractionMode_Text;
	wxStaticText *Units_MinimapMode_Text;
	wxStaticText *Units_CommandAttribute_Text;
	wxStaticText *Units_Unknown3A_Text;
	wxStaticText *Units_MinimapColor_Text;
	wxStaticText *Units_LanguageDLLHelp_Text;
	wxStaticText *Units_LanguageDLLConverter_Text[2];
	wxStaticText *Units_LanguageDLLHotKeyText_Text;
	wxStaticText *Units_HotKey_Text;
	wxStaticText *Units_Unknown6_Text;
	wxStaticText *Units_Unknown7_Text;
	wxStaticText *Units_Unknown8_Text;
	wxStaticText *Units_SelectionMask_Text;
	wxStaticText *Units_SelectionShapeType_Text;
	wxStaticText *Units_SelectionShape_Text;
	wxStaticText *Units_Attribute_Text;
	wxStaticText *Units_Civ_Text;
	wxStaticText *Units_Unknown9_Text;
	wxStaticText *Units_SelectionEffect_Text;
	wxStaticText *Units_EditorSelectionColour_Text;
	wxStaticText *Units_SelectionRadius_Text;
	wxStaticText *Units_HPBarHeight2_Text;
	wxStaticText *ResourceStorage_Type_Text;
	wxStaticText *ResourceStorage_Amount_Text;
	wxStaticText *ResourceStorage_Enabled_Text;
	wxStaticText *Units_SelectionSound_Text;
	wxStaticText *Units_DyingSound_Text;
	wxStaticText *Units_AttackMode_Text;
	wxStaticText *Units_EdibleMeat_Text;
	wxStaticText *Units_Name_Text;
	wxStaticText *Units_Name2_Text;
	wxStaticText *Units_Unitline_Text;
	wxStaticText *Units_MinTechLevel_Text;
	wxStaticText *Units_ID2_Text;
	wxStaticText *Units_ID3_Text;

//	Type 20+

	wxStaticText *Units_Speed_Text;

//	Type 30+

	wxStaticText *Units_WalkingGraphic_Text;
	wxStaticText *Units_RotationSpeed_Text;
	wxStaticText *Units_Unknown11_Text;
	wxStaticText *Units_TrackingUnit_Text;
	wxStaticText *Units_TrackingUnitUsed_Text;
	wxStaticText *Units_TrackingUnitDensity_Text;
	wxStaticText *Units_Unknown16_Text;
	wxStaticText *Units_Unknown16B_Text;

//	Type 40+

	wxStaticText *Units_SearchRadius_Text;
	wxStaticText *Units_WorkRate_Text;
	wxStaticText *Units_DropSite_Text;
	wxStaticText *Units_VillagerMode_Text;
	wxStaticText *Units_AttackSound_Text;
	wxStaticText *Units_MoveSound_Text;
	wxStaticText *Units_Exists_Text;

//	Type 50+

	wxStaticText *Units_DefaultArmor_Text;
	wxStaticText *Units_TerRestrictionForDmgMultiply_Text;
	wxStaticText *Units_MaxRange_Text;
	wxStaticText *Units_BlastRadius_Text;
	wxStaticText *Units_ReloadTime1_Text;
	wxStaticText *Units_ProjectileUnitID_Text;
	wxStaticText *Units_AccuracyPercent_Text;
	wxStaticText *Units_Delay_Text;
	wxStaticText *Units_GraphicDisplacement_Text;
	wxStaticText *Units_BlastLevel_Text;
	wxStaticText *Units_MinRange_Text;
	wxStaticText *Units_AccuracyErrorRadius_Text;
	wxStaticText *Units_AttackGraphic_Text;
	wxStaticText *Units_DisplayedMeleeArmour_Text;
	wxStaticText *Units_DisplayedAttack_Text;
	wxStaticText *Units_DisplayedRange_Text;
	wxStaticText *Units_ReloadTime2_Text;

//	Type 60 only

	wxStaticText *Units_StretchMode_Text;
	wxStaticText *Units_CompensationMode_Text;
	wxStaticText *Units_DropAnimationMode_Text;
	wxStaticText *Units_PenetrationMode_Text;
	wxStaticText *Units_Unknown24_Text;
	wxStaticText *Units_ProjectileArc_Text;

//	Type 70+

	wxStaticText *Units_CostType_Text;
	wxStaticText *Units_CostAmount_Text;
	wxStaticText *Units_CostUsed_Text;
	wxStaticText *Units_TrainTime_Text;
	wxStaticText *Units_TrainLocationID_Text;
	wxStaticText *Units_ButtonID_Text;
	wxStaticText *Units_Unknown26_Text;
	wxStaticText *Units_Unknown27_Text;
	wxStaticText *Units_Unknown28_Text;
	wxStaticText *Units_GarrisonGraphic_Text;
	wxStaticText *Units_AttackMissileDuplicationAmount1_Text;
	wxStaticText *Units_AttackMissileDuplicationAmount2_Text;
	wxStaticText *Units_AttackMissileDuplicationSpawning_Text;
	wxStaticText *Units_AttackMissileDuplicationUnit_Text;
	wxStaticText *Units_ChargingGraphic_Text;
	wxStaticText *Units_ChargingMode_Text;
	wxStaticText *Units_DisplayedPierceArmour_Text;

//	Type 80

	wxStaticText *Units_ConstructionGraphicID_Text;
	wxStaticText *Units_SnowGraphicID_Text;
	wxStaticText *Units_IconDisabler_Text;
	wxStaticText *Units_StackUnitID_Text;
	wxStaticText *Units_TerrainID_Text;
	wxStaticText *Units_OldTerrainLikeID_Text;
	wxStaticText *Units_ResearchID_Text;
	wxStaticText *Units_Unknown33_Text;
	wxStaticText *Units_AnnexUnit_Text;
	wxStaticText *Units_AnnexUnitMisplacement_Text;
	wxStaticText *Units_HeadUnit_Text;
	wxStaticText *Units_TransformUnit_Text;
	wxStaticText *Units_UnknownSound_Text;
	wxStaticText *Units_ConstructionSound_Text;
	wxStaticText *Units_GarrisonType_Text;
	wxStaticText *Units_GarrisonHealRate_Text;
	wxStaticText *Units_Unknown35_Text;
	wxStaticText *Units_PileUnit_Text;
	wxStaticText *Units_LootSwitch_Text;

//	Invisible Holder Windows
//	Type 10+

	wxStaticBoxSizer *Units_Type_Holder;
	wxBoxSizer *Units_ID1_Holder;
	wxBoxSizer *Units_LanguageDLLName_Holder;
	wxBoxSizer *Units_LanguageDLLCreation_Holder;
	wxBoxSizer *Units_StandingGraphic_Holder;
	wxGridSizer *Units_StandingGraphic_Grid;
	wxBoxSizer *Units_DyingGraphic_Holder;
	wxGridSizer *Units_DyingGraphic_Grid;
	wxBoxSizer *Units_DeathMode_Holder;
	wxBoxSizer *Units_HitPoints_Holder;
	wxBoxSizer *Units_LineOfSight_Holder;
	wxBoxSizer *Units_GarrisonCapacity_Holder;
	wxBoxSizer *Units_SizeRadius_Holder;
	wxGridSizer *Units_SizeRadius_Grid;
	wxBoxSizer *Units_HPBarHeight1_Holder;
	wxBoxSizer *Units_TrainSound_Holder;
	wxBoxSizer *Units_TrainSound1_Holder;
	wxBoxSizer *Units_TrainSound2_Holder;
	wxBoxSizer *Units_TrainSound3_Holder;
	wxBoxSizer *Units_DeadUnitID_Holder;
	wxBoxSizer *Units_PlacementMode_Holder;
	wxBoxSizer *Units_AirMode_Holder;
	wxBoxSizer *Units_IconID_Holder;
	wxGridSizer *Units_IconID_Grid;
	wxBoxSizer *Units_HideInEditor_Holder;
	wxBoxSizer *Units_Unknown1_Holder;
	wxBoxSizer *Units_Enabled_Holder;
	wxBoxSizer *Units_Disabled_Holder;
	wxBoxSizer *Units_PlacementBypassTerrain_Holder;
	wxGridSizer *Units_PlacementBypassTerrainGrid_Holder;
	wxBoxSizer *Units_PlacementTerrain_Holder;
	wxGridSizer *Units_PlacementTerrainGrid_Holder;
	wxBoxSizer *Units_EditorRadius_Holder;
	wxGridSizer *Units_EditorRadius_Grid;
	wxBoxSizer *Units_HillMode_Holder;
	wxBoxSizer *Units_VisibleInFog_Holder;
	wxBoxSizer *Units_TerrainRestriction_Holder;
	wxBoxSizer *Units_FlyMode_Holder;
	wxBoxSizer *Units_ResourceCapacity_Holder;
	wxBoxSizer *Units_ResourceDecay_Holder;
	wxBoxSizer *Units_BlastType_Holder;
	wxBoxSizer *Units_Unknown2_Holder;
	wxBoxSizer *Units_InteractionMode_Holder;
	wxBoxSizer *Units_MinimapMode_Holder;
	wxBoxSizer *Units_CommandAttribute_Holder;
	wxBoxSizer *Units_Unknown3A_Holder;
	wxBoxSizer *Units_MinimapColor_Holder;
	wxBoxSizer *Units_LanguageDLLHelp_Holder;
	wxBoxSizer *Units_LanguageDLLConverter_Holder[2];
	wxBoxSizer *Units_LanguageDLLHotKeyText_Holder;
	wxBoxSizer *Units_HotKey_Holder;
	wxBoxSizer *Units_Unselectable_Holder;
	wxBoxSizer *Units_Unknown6_Holder;
	wxBoxSizer *Units_Unknown7_Holder;
	wxBoxSizer *Units_Unknown8_Holder;
	wxBoxSizer *Units_SelectionMask_Holder;
	wxBoxSizer *Units_SelectionShapeType_Holder;
	wxBoxSizer *Units_SelectionShape_Holder;
	wxBoxSizer *Units_Attribute_Holder;
	wxBoxSizer *Units_Civ_Holder;
	wxBoxSizer *Units_Unknown9_Holder;
	wxBoxSizer *Units_SelectionEffect_Holder;
	wxBoxSizer *Units_EditorSelectionColour_Holder;
	wxBoxSizer *Units_SelectionRadius_Holder;
	wxBoxSizer *Units_HPBarHeight2_Holder;
	wxStaticBoxSizer *Units_ResourceStorageHeader_Holder;
	wxGridSizer *Units_ResourceStorage_Grid;
	wxBoxSizer *Units_ResourceStorage_Holder[3];
	wxBoxSizer *Units_SelectionSound_Holder;
	wxBoxSizer *Units_DyingSound_Holder;
	wxBoxSizer *Units_AttackMode_Holder;
	wxBoxSizer *Units_EdibleMeat_Holder;
	wxBoxSizer *Units_Name_Holder;
	wxBoxSizer *Units_Name2_Holder;
	wxBoxSizer *Units_Unitline_Holder;
	wxBoxSizer *Units_MinTechLevel_Holder;
	wxBoxSizer *Units_ID2_Holder;
	wxBoxSizer *Units_ID3_Holder;

//	Type 20+

	wxBoxSizer *Units_Speed_Holder;

//	Type 30+

	wxBoxSizer *Units_WalkingGraphic_Holder;
	wxGridSizer *Units_WalkingGraphic_Grid;
	wxBoxSizer *Units_RotationSpeed_Holder;
	wxBoxSizer *Units_Unknown11_Holder;
	wxBoxSizer *Units_TrackingUnit_Holder;
	wxBoxSizer *Units_TrackingUnitUsed_Holder;
	wxBoxSizer *Units_TrackingUnitUsedBox_Holder;
	wxBoxSizer *Units_TrackingUnitDensity_Holder;
	wxBoxSizer *Units_Unknown16_Holder;
	wxBoxSizer *Units_Unknown16B_Holder;
	wxGridSizer *Units_Unknown16B_Grid;

//	Type 40+

	wxBoxSizer *Units_SheepConversion_Holder;
	wxBoxSizer *Units_SearchRadius_Holder;
	wxBoxSizer *Units_WorkRate_Holder;
	wxGridSizer *Units_DropSite_Grid;
	wxBoxSizer *Units_VillagerMode_Holder;
	wxBoxSizer *Units_AttackSound_Holder;
	wxBoxSizer *Units_MoveSound_Holder;
	wxBoxSizer *Units_AnimalMode_Holder;
	wxBoxSizer *Units_Exists_Holder;

//	Type 50+

	wxBoxSizer *Units_DefaultArmor_Holder;
	wxBoxSizer *Units_TerRestrictionForDmgMultiply_Holder;
	wxBoxSizer *Units_MaxRange_Holder;
	wxBoxSizer *Units_BlastRadius_Holder;
	wxBoxSizer *Units_ReloadTime1_Holder;
	wxBoxSizer *Units_ProjectileUnitID_Holder;
	wxBoxSizer *Units_AccuracyPercent_Holder;
	wxBoxSizer *Units_TowerMode_Holder;
	wxBoxSizer *Units_Delay_Holder;
	wxBoxSizer *Units_GraphicDisplacement_Holder;
	wxGridSizer *Units_GraphicDisplacement_Grid;
	wxBoxSizer *Units_BlastLevel_Holder;
	wxBoxSizer *Units_MinRange_Holder;
	wxBoxSizer *Units_AccuracyErrorRadius_Holder;
	wxBoxSizer *Units_AttackGraphic_Holder;
	wxBoxSizer *Units_DisplayedMeleeArmour_Holder;
	wxBoxSizer *Units_DisplayedAttack_Holder;
	wxBoxSizer *Units_DisplayedRange_Holder;
	wxBoxSizer *Units_ReloadTime2_Holder;

//	Type 60 only

	wxBoxSizer *Units_StretchMode_Holder;
	wxBoxSizer *Units_CompensationMode_Holder;
	wxBoxSizer *Units_DropAnimationMode_Holder;
	wxBoxSizer *Units_PenetrationMode_Holder;
	wxBoxSizer *Units_Unknown24_Holder;
	wxBoxSizer *Units_ProjectileArc_Holder;

//	Type 70+

	wxStaticBoxSizer *Units_CostHeader_Holder;
	wxBoxSizer *Units_CostType_Holder;
	wxGridSizer *Units_CostType_Grid;
	wxBoxSizer *Units_CostAmount_Holder;
	wxBoxSizer *Units_CostUsed_Holder;
	wxBoxSizer *Units_TrainTime_Holder;
	wxBoxSizer *Units_TrainLocationID_Holder;
	wxBoxSizer *Units_ButtonID_Holder;
	wxBoxSizer *Units_Unknown26_Holder;
	wxBoxSizer *Units_Unknown27_Holder;
	wxBoxSizer *Units_Unknown28_Holder;
	wxBoxSizer *Units_HeroMode_Holder;
	wxBoxSizer *Units_GarrisonGraphic_Holder;
	wxGridSizer *Units_GarrisonGraphic_Grid;
	wxBoxSizer *Units_AttackMissileDuplicationAmount1_Holder;
	wxBoxSizer *Units_AttackMissileDuplicationAmount2_Holder;
	wxBoxSizer *Units_AttackMissileDuplicationSpawning_Holder;
	wxGridSizer *Units_AttackMissileDuplicationSpawning_Grid;
	wxBoxSizer *Units_AttackMissileDuplicationUnit_Holder;
	wxBoxSizer *Units_ChargingGraphic_Holder;
	wxBoxSizer *Units_ChargingMode_Holder;
	wxBoxSizer *Units_DisplayedPierceArmour_Holder;

//	Type 80

	wxBoxSizer *Units_ConstructionGraphicID_Holder;
	wxBoxSizer *Units_SnowGraphicID_Holder;
	wxBoxSizer *Units_AdjacentMode_Holder;
	wxBoxSizer *Units_IconDisabler_Holder;
	wxBoxSizer *Units_Unknown31b_Holder;
	wxBoxSizer *Units_StackUnitID_Holder;
	wxBoxSizer *Units_TerrainID_Holder;
	wxBoxSizer *Units_OldTerrainLikeID_Holder;
	wxBoxSizer *Units_ResearchID_Holder;
	wxBoxSizer *Units_Unknown33_Holder;
	wxGridSizer *Units_AnnexUnit_Grid;
	wxBoxSizer *Units_AnnexUnit1_Holder;
	wxGridSizer *Units_AnnexUnitMisplacement_Grid;
	wxBoxSizer *Units_AnnexUnitMisplacement1_Holder;
	wxBoxSizer *Units_HeadUnit_Holder;
	wxBoxSizer *Units_TransformUnit_Holder;
	wxBoxSizer *Units_UnknownSound_Holder;
	wxBoxSizer *Units_ConstructionSound_Holder;
	wxBoxSizer *Units_GarrisonType_Holder;
	wxBoxSizer *Units_GarrisonHealRate_Holder;
	wxBoxSizer *Units_Unknown35_Holder;
	wxBoxSizer *Units_PileUnit_Holder;
	wxBoxSizer *Units_LootSwitch_Holder;
	wxGridSizer *Units_LootSwitch_Grid;

//	Unit Controls SubControls

	wxBoxSizer *Units_DamageGraphics_Holder_Data;
	TextCtrl_Short *DamageGraphics_GraphicID;
	ComboBox_Plus1 *DamageGraphics_GraphicID_ComboBox;
	TextCtrl_Byte *DamageGraphics_DamagePercent;
	TextCtrl_Byte *DamageGraphics_Unknown1;
	TextCtrl_Byte *DamageGraphics_Unknown2;
	wxStaticText *DamageGraphics_GraphicID_Text;
	wxStaticText *DamageGraphics_DamagePercent_Text;
	wxStaticText *DamageGraphics_Unknown1_Text;
	wxStaticText *DamageGraphics_Unknown2_Text;
	wxBoxSizer *DamageGraphics_GraphicID_Holder;
	wxBoxSizer *DamageGraphics_DamagePercent_Holder;
	wxBoxSizer *DamageGraphics_Unknown1_Holder;
	wxBoxSizer *DamageGraphics_Unknown2_Holder;
	wxStaticBoxSizer *Units_DamageGraphics;
	wxBoxSizer *Units_DamageGraphics_ListArea;
	wxTextCtrl *Units_DamageGraphics_Search;
	wxTextCtrl *Units_DamageGraphics_Search_R;
	wxListBox *Units_DamageGraphics_List;
	wxGridSizer *Units_DamageGraphics_Buttons;
	wxButton *Units_DamageGraphics_Add;
	wxButton *Units_DamageGraphics_Insert;
	wxButton *Units_DamageGraphics_Delete;
	wxButton *Units_DamageGraphics_Copy;
	wxButton *Units_DamageGraphics_Paste;
	wxButton *Units_DamageGraphics_PasteInsert;
	wxButton *Units_DamageGraphics_CopyToUnits;

	wxBoxSizer *Units_Attacks_Holder;
	wxBoxSizer *Units_Attacks_Holder_Data;
	wxGridSizer *Units_Attacks_Grid_Data2;
	TextCtrl_Short *Attacks_Class;
	ComboBox_Plus1 *Attacks_Class_ComboBox[3];
	TextCtrl_Short *Attacks_Amount;
	wxStaticText *Attacks_Class_Text;
	wxStaticText *Attacks_Amount_Text;
	wxBoxSizer *Attacks_Class_Holder;
	wxBoxSizer *Attacks_Amount_Holder;
	wxStaticBoxSizer *Units_Attacks;
	wxBoxSizer *Units_Attacks_ListArea;
	wxBoxSizer *Units_Attacks_DataArea;
	wxTextCtrl *Units_Attacks_Search;
	wxTextCtrl *Units_Attacks_Search_R;
	wxListBox *Units_Attacks_List;
	wxGridSizer *Units_Attacks_Buttons;
	wxButton *Units_Attacks_Add;
	wxButton *Units_Attacks_Insert;
	wxButton *Units_Attacks_Delete;
	wxButton *Units_Attacks_Copy;
	wxButton *Units_Attacks_Paste;
	wxButton *Units_Attacks_PasteInsert;
	wxButton *Units_Attacks_CopyToUnits;

	wxBoxSizer *Units_Armors_Holder;
	wxBoxSizer *Units_Armors_Holder_Data3;
	TextCtrl_Short *Armors_Class;
	TextCtrl_Short *Armors_Amount;
	wxStaticText *Armors_Class_Text;
	wxStaticText *Armors_Amount_Text;
	wxBoxSizer *Armors_Class_Holder;
	wxBoxSizer *Armors_Amount_Holder;
	wxStaticBoxSizer *Units_Armors;
	wxBoxSizer *Units_Armors_ListArea;
	wxBoxSizer *Units_Armors_DataArea;
	wxTextCtrl *Units_Armors_Search;
	wxTextCtrl *Units_Armors_Search_R;
	wxListBox *Units_Armors_List;
	wxGridSizer *Units_Armors_Buttons;
	wxButton *Units_Armors_Add;
	wxButton *Units_Armors_Insert;
	wxButton *Units_Armors_Delete;
	wxButton *Units_Armors_Copy;
	wxButton *Units_Armors_Paste;
	wxButton *Units_Armors_PasteInsert;
	wxButton *Units_Armors_CopyToUnits;

//	End of Unit Controls

	wxBoxSizer *Units_Main;	// Unit window
	wxBoxSizer *Units_ListArea;	// Unit list section vertical division
	wxGridSizer *Units_Buttons[2];	// Unit list section buttons

	wxStaticBoxSizer *Units_Units;	// Unit list section vertical division excluding window borders
	//wxStaticLine *Units_Line;
	wxBoxSizer *Units_Special;
	wxComboBox *Units_Civs_List;	// Civ list combo box
	wxBoxSizer *Units_Searches[2];
	wxTextCtrl *Units_Search;	// Unit search
	wxTextCtrl *Units_Search_R;	// Unit reverse search
	wxOwnerDrawnComboBox *Units_FilterSelector;
	wxOwnerDrawnComboBox *Units_SearchFilters[2];	// Unit search
	wxCheckBox *Units_UseAnd[2];
	wxListBox *Units_List;	// List of units
	wxButton *Units_Add;	// Buttons
	wxButton *Units_Insert;
	wxButton *Units_Delete;
	wxButton *Units_Copy;
	wxButton *Units_Paste;
	wxButton *Units_PasteInsert;
	wxStaticText *Units_Info;
	//wxButton *Units_Extract;
	//wxButton *Units_Import;
	wxButton *Units_Enable;
	wxButton *Units_Disable;
	wxButton *Units_SpecialCopy;
	wxButton *Units_SpecialPaste;
	wxButton *Units_SpecialPasteInsert;
	wxOwnerDrawnComboBox *Units_SpecialCopy_Options;
	wxCheckBox *Units_SpecialCopy_Civs;
//	wxButton *Units_Undo;

	wxBoxSizer *Units_DataArea;	// Unit window other-than unit-list-section

	wxBoxSizer *Units_ScrollArea;	// Scrollable section division
	wxBoxSizer *Units_ScrollSpace;
	wxStaticBoxSizer *Units_TypeArea_Holder;
	wxStaticBoxSizer *Units_LangDLLArea_Holder;
	wxStaticBoxSizer *Units_GraphicsArea_Holder;
	wxBoxSizer *Units_GraphicsArea1_Holder;
	wxGridSizer *Units_GraphicsArea4_Holder;
	wxGridSizer *Units_GraphicsArea5_Holder;
	wxStaticBoxSizer *Units_StatsArea_Holder;
	wxGridSizer *Units_StatsArea1_Grid;
	wxGridSizer *Units_StatsAreaGarrison_Grid;
	wxGridSizer *Units_StatsArea2_Grid;
	wxStaticBoxSizer *Units_ProjectilesArea_Holder;
	wxGridSizer *Units_ProjectilesArea1_Grid;
	wxGridSizer *Units_ProjectilesArea2_Grid;
	wxGridSizer *Units_ProjectilesArea3_Grid;
	wxStaticBoxSizer *Units_Attributes_Holder;
	wxGridSizer *Units_AttributesBoxes1_Grid;
	wxGridSizer *Units_Attributes1_Grid;
	wxGridSizer *Units_Attributes2_Grid;
	wxBoxSizer *Units_AttributesTerrain_Holder;
	wxGridSizer *Units_AttributesTerrain_Grid;
	wxGridSizer *Units_AttributesModes1_Grid;
	wxBoxSizer *Units_AttributesDropSite_Holder;
	wxGridSizer *Units_AttributesSizes_Holder;
	wxGridSizer *Units_AttributesSelection1_Grid;
	wxBoxSizer *Units_LangRegular_Holder;
	wxBoxSizer *Units_LangHotKey_Holder;
	wxGridSizer *Units_AttributesTracking_Grid;
	wxGridSizer *Units_AttributesTrain1_Grid;
	wxGridSizer *Units_Attributes3_Grid;
	wxStaticBoxSizer *Units_SoundsArea_Holder;
	wxBoxSizer *Units_SoundsArea1_Holder;
	wxGridSizer *Units_SoundsArea2_Grid;
	wxStaticBoxSizer *Units_MiscArea_Holder;
	wxGridSizer *Units_HPBars_Grid;
	wxBoxSizer *Units_UnknownArea_Holder;
	wxStaticBoxSizer *Units_Type10plusUnknownArea_Holder;
	wxGridSizer *Units_Type10plusUnknowns_Grid;
	wxStaticBoxSizer *Units_Type30plusUnknownArea_Holder;
	wxGridSizer *Units_Type30plusUnknownArea_Grid;
	wxStaticBoxSizer *Units_Type70plusUnknownArea_Holder;
	wxGridSizer *Units_Type70plusUnknownArea_Grid;
	wxStaticBoxSizer *Units_Type80plusUnknownArea_Holder;
	wxGridSizer *Units_Type80plusUnknownArea_Grid;
	wxStaticBoxSizer *Units_CommandsArea_Holder;
	wxBoxSizer *Units_Top_Holder;
	wxGridSizer *Units_TopGrid_Holder;
	vector<wxCheckBox*> Units_CivBoxes;
	//vector<wxStaticText*> Units_CivLabels;
	wxButton *Units_CopyTo;
	wxCheckBox *Units_CopyGraphics;
	wxCheckBox *Units_AutoCopy;
	wxStaticText *Units_CopyToText;
	wxStaticText *Units_GraphicSetText;
	wxOwnerDrawnComboBox *Units_GraphicSet;
	wxButton *Units_SelectAll;
	wxButton *Units_SelectClear;

//	Unit Attributes section

	wxBoxSizer *Units_CommandHolder_Lists;
	wxStaticText *Units_UnitHeads_Name;

	wxStaticBoxSizer *Units_UnitCommands;
	wxTextCtrl *Units_UnitCommands_Search;
	wxTextCtrl *Units_UnitCommands_Search_R;
	wxListBox *Units_UnitCommands_List;
	wxGridSizer *Units_UnitCommands_Buttons;
	wxButton *Units_UnitCommands_Add;
	wxButton *Units_UnitCommands_Insert;
	wxButton *Units_UnitCommands_Delete;
	wxButton *Units_UnitCommands_Copy;
	wxButton *Units_UnitCommands_Paste;
	wxButton *Units_UnitCommands_PasteInsert;
	wxButton *Units_UnitCommands_CopyToUnits;

	wxBoxSizer *Units_CommandHolder_Data;
	wxBoxSizer *Units_CommandHolder_Data1;
	wxBoxSizer *Units_CommandHolder_Data2;
	wxGridSizer *Units_CommandHolder_Grid1;
	wxGridSizer *Units_CommandHolder_Grid2;
	wxGridSizer *Units_CommandHolder_Grid3;
	wxBoxSizer *UnitCommands_One_Holder;
	wxBoxSizer *UnitCommands_ID_Holder;
	wxBoxSizer *UnitCommands_1_Holder;
	wxBoxSizer *UnitCommands_Unknown1_Holder;
	wxBoxSizer *UnitCommands_Type_Holder;
	wxBoxSizer *UnitCommands_ProductivityResource_Holder;
	wxBoxSizer *UnitCommands_ClassID_Holder;
	wxBoxSizer *UnitCommands_UnitID_Holder;
	wxBoxSizer *UnitCommands_Unknown2_Holder;
	wxBoxSizer *UnitCommands_ResourceIn_Holder;
	wxBoxSizer *UnitCommands_ResourceOut_Holder;
	wxBoxSizer *UnitCommands_Resource_Holder;
	wxBoxSizer *UnitCommands_WorkRateMultiplier_Holder;
	wxBoxSizer *UnitCommands_ExecutionRadius_Holder;
	wxBoxSizer *UnitCommands_ExtraRange_Holder;
	wxBoxSizer *UnitCommands_Unknown4_Holder;
	wxBoxSizer *UnitCommands_Unknown5_Holder;
	wxBoxSizer *UnitCommands_SelectionEnabler_Holder;
	wxBoxSizer *UnitCommands_Unknown7_Holder;
	wxBoxSizer *UnitCommands_Unknown8_Holder;
	wxBoxSizer *UnitCommands_Unknown9_Holder;
	wxBoxSizer *UnitCommands_SelectionMode_Holder;
	wxBoxSizer *UnitCommands_Unknown11_Holder;
	wxBoxSizer *UnitCommands_Unknown12_Holder;
	array<wxBoxSizer*, 6> UnitCommands_Graphics_Holder;
	wxGridSizer *UnitCommands_Graphics_Grid;

	wxStaticText *UnitCommands_One_Text;
	wxStaticText *UnitCommands_ID_Text;
	wxStaticText *UnitCommands_Unknown1_Text;
	wxStaticText *UnitCommands_Type_Text;
	wxStaticText *UnitCommands_ClassID_Text;
	wxStaticText *UnitCommands_UnitID_Text;
	wxStaticText *UnitCommands_Unknown2_Text;
	wxStaticText *UnitCommands_ResourceIn_Text;
	wxStaticText *UnitCommands_ProductivityResource_Text;
	wxStaticText *UnitCommands_ResourceOut_Text;
	wxStaticText *UnitCommands_Resource_Text;
	wxStaticText *UnitCommands_WorkRateMultiplier_Text;
	wxStaticText *UnitCommands_ExecutionRadius_Text;
	wxStaticText *UnitCommands_ExtraRange_Text;
	wxStaticText *UnitCommands_Unknown4_Text;
	wxStaticText *UnitCommands_Unknown5_Text;
	wxStaticText *UnitCommands_SelectionEnabler_Text;
	wxStaticText *UnitCommands_Unknown7_Text;
	wxStaticText *UnitCommands_Unknown8_Text;
	wxStaticText *UnitCommands_Unknown9_Text;
	wxStaticText *UnitCommands_SelectionMode_Text;
	wxStaticText *UnitCommands_Unknown11_Text;
	wxStaticText *UnitCommands_Unknown12_Text;
	array<wxStaticText*, 6> UnitCommands_Graphics_Text;

	TextCtrl_Short *UnitCommands_One;
	TextCtrl_Short *UnitCommands_ID;
	TextCtrl_Byte *UnitCommands_Unknown1;
	TextCtrl_Short *UnitCommands_Type;
	wxOwnerDrawnComboBox *UnitCommands_Type_ComboBox;
	TextCtrl_Short *UnitCommands_ClassID;
	TextCtrl_Short *UnitCommands_UnitID;
	ComboBox_Plus1 *UnitCommands_UnitID_ComboBox;
	TextCtrl_Short *UnitCommands_Unknown2;
	TextCtrl_Short *UnitCommands_ResourceIn;
	ComboBox_Plus1 *UnitCommands_ResourceIn_ComboBox;
	TextCtrl_Short *UnitCommands_ProductivityResource;
	ComboBox_Plus1 *UnitCommands_ProductivityResource_ComboBox;
	TextCtrl_Short *UnitCommands_ResourceOut;
	ComboBox_Plus1 *UnitCommands_ResourceOut_ComboBox;
	TextCtrl_Short *UnitCommands_Resource;
	ComboBox_Plus1 *UnitCommands_Resource_ComboBox;
	TextCtrl_Float *UnitCommands_WorkRateMultiplier;
	TextCtrl_Float *UnitCommands_ExecutionRadius;
	TextCtrl_Float *UnitCommands_ExtraRange;
	TextCtrl_Byte *UnitCommands_Unknown4;
	TextCtrl_Float *UnitCommands_Unknown5;
	TextCtrl_Byte *UnitCommands_SelectionEnabler;
	TextCtrl_Byte *UnitCommands_Unknown7;
	TextCtrl_Short *UnitCommands_Unknown8;
	TextCtrl_Short *UnitCommands_Unknown9;
	TextCtrl_Byte *UnitCommands_SelectionMode;
	TextCtrl_Byte *UnitCommands_Unknown11;
	TextCtrl_Byte *UnitCommands_Unknown12;
	array<TextCtrl_Short*, 6> UnitCommands_Graphics;
	array<ComboBox_Plus1*, 6> UnitCommands_Graphics_ComboBox;

//	Graphics user interface

	wxBoxSizer *Graphics_Main;
	wxBoxSizer *Graphics_ListArea;
	wxGridSizer *Graphics_Graphics_Buttons;
	wxStaticBoxSizer *Graphics_Graphics;
	wxBoxSizer *Graphics_Graphics_Searches[2];
	wxTextCtrl *Graphics_Graphics_Search;
	wxTextCtrl *Graphics_Graphics_Search_R;
	wxOwnerDrawnComboBox *Graphics_SearchFilters[2];
	wxCheckBox *Graphics_Graphics_UseAnd[2];
	wxListBox *Graphics_Graphics_List;
	//AGEListCtrl *Graphics_Graphics_ListV;
	wxButton *Graphics_Add;
	wxButton *Graphics_Insert;
	wxButton *Graphics_Delete;
	wxButton *Graphics_Copy;
	wxButton *Graphics_Paste;
	wxButton *Graphics_PasteInsert;
	//wxButton *Graphics_Extract;
	//wxButton *Graphics_Import;
	wxButton *Graphics_Enable;
	wxButton *Graphics_Disable;

	wxBoxSizer *Graphics_DataArea;
	wxScrolledWindow *Graphics_Scroller;
	wxBoxSizer *Graphics_ScrollArea;
	wxBoxSizer *Graphics_ScrollSpace;

	wxBoxSizer *Graphics_NameArea_Holder;
	wxBoxSizer *Graphics_Name_Holder;
	wxBoxSizer *Graphics_Name2_Holder;
	wxBoxSizer *Graphics_SLP_Holder;
	wxBoxSizer *Graphics_Unknown1_Holder;
	wxBoxSizer *Graphics_Unknown2_Holder;
	wxBoxSizer *Graphics_FrameType_Holder;
	wxBoxSizer *Graphics_PlayerColor_Holder;
	wxBoxSizer *Graphics_Rainbow_Holder;
	wxBoxSizer *Graphics_Replay_Holder;
	wxBoxSizer *Graphics_Coordinates_Holder;
	wxGridSizer *Graphics_CoordinateGrid_Holder;
	wxBoxSizer *Graphics_SoundID_Holder;
	wxBoxSizer *Graphics_AttackSoundUsed_Holder;
	wxBoxSizer *Graphics_AttackSoundUsed1_Holder;
	wxBoxSizer *Graphics_4_Holder;
	wxBoxSizer *Graphics_5_Holder;
	wxBoxSizer *Graphics_FrameCount_Holder;
	wxBoxSizer *Graphics_AngleCount_Holder;
	wxBoxSizer *Graphics_NewSpeed_Holder;
	wxBoxSizer *Graphics_FrameRate_Holder;
	wxBoxSizer *Graphics_ReplayDelay_Holder;
	wxBoxSizer *Graphics_SequenceType_Holder;
	wxBoxSizer *Graphics_ID_Holder;
	wxBoxSizer *Graphics_Type_Holder;
	wxBoxSizer *Graphics_Unknown3_Holder;
	wxGridSizer *Graphics_1_Grid;
	wxGridSizer *Graphics_2_Grid;
	wxGridSizer *Graphics_3_Grid;

	wxStaticText *Graphics_Name_Text;
	wxStaticText *Graphics_Name2_Text;
	wxStaticText *Graphics_SLP_Text;
	wxStaticText *Graphics_Unknown1_Text;
	wxStaticText *Graphics_Unknown2_Text;
	wxStaticText *Graphics_FrameType_Text;
	wxStaticText *Graphics_PlayerColor_Text;
	wxStaticText *Graphics_Rainbow_Text;
	wxStaticText *Graphics_Replay_Text;
	wxStaticText *Graphics_Coordinates_Text;
	wxStaticText *Graphics_SoundID_Text;
	wxStaticText *Graphics_AttackSoundUsed_Text;
	wxStaticText *Graphics_FrameCount_Text;
	wxStaticText *Graphics_AngleCount_Text;
	wxStaticText *Graphics_NewSpeed_Text;
	wxStaticText *Graphics_FrameRate_Text;
	wxStaticText *Graphics_ReplayDelay_Text;
	wxStaticText *Graphics_SequenceType_Text;
	wxStaticText *Graphics_ID_Text;
	wxStaticText *Graphics_Type_Text;
	wxStaticText *Graphics_Unknown3_Text;

	TextCtrl_String *Graphics_Name;
	TextCtrl_String *Graphics_Name2;
	TextCtrl_Long *Graphics_SLP;
	TextCtrl_Byte *Graphics_Unknown1;
	TextCtrl_Byte *Graphics_Unknown2;
	TextCtrl_Byte *Graphics_FrameType;
	TextCtrl_Byte *Graphics_PlayerColor;
	ComboBox_Plus1 *Graphics_PlayerColor_ComboBox;
	TextCtrl_Byte *Graphics_Rainbow;
	TextCtrl_Byte *Graphics_Replay;
	TextCtrl_Short *Graphics_Coordinates[4];
	TextCtrl_Short *Graphics_SoundID;
	ComboBox_Plus1 *Graphics_SoundID_ComboBox;
	TextCtrl_Byte *Graphics_AttackSoundUsed;
	CheckBox_2State *Graphics_AttackSoundUsed_CheckBox;
	TextCtrl_UShort *Graphics_FrameCount;
	TextCtrl_UShort *Graphics_AngleCount;
	TextCtrl_Float *Graphics_NewSpeed;
	TextCtrl_Float *Graphics_FrameRate;
	TextCtrl_Float *Graphics_ReplayDelay;
	TextCtrl_Byte *Graphics_SequenceType;
	TextCtrl_Short *Graphics_ID;
	TextCtrl_Byte *Graphics_MirroringMode;
	TextCtrl_Byte *Graphics_Unknown3;

	wxBoxSizer *Graphics_Deltas;
	wxTextCtrl *Graphics_Deltas_Search;
	wxTextCtrl *Graphics_Deltas_Search_R;
	wxListBox *Graphics_Deltas_List;
	wxGridSizer *Graphics_Deltas_Buttons;
	wxButton *Deltas_Add;
	wxButton *Deltas_Insert;
	wxButton *Deltas_Delete;
	wxButton *Deltas_Copy;
	wxButton *Deltas_Paste;
	wxButton *Deltas_PasteInsert;
	wxButton *Deltas_CopyToGraphics;
	wxBoxSizer *Graphics_AttackSounds;
	wxListBox *Graphics_AttackSounds_List;
	wxButton *AttackSounds_Copy;
	wxButton *AttackSounds_CopyToGraphics;

	wxStaticBoxSizer *Graphics_Deltas_Holder;
	wxBoxSizer *Graphics_Deltas_Holder_Data;
	wxBoxSizer *Graphics_Deltas_Holder_Data1;
	wxGridSizer *Graphics_Deltas_Grid_Data2;
	wxStaticBoxSizer *Graphics_AttackSoundArea_Holder;

	wxBoxSizer *GraphicDeltas_GraphicID_Holder;
	wxStaticText *GraphicDeltas_GraphicID_Text;
	TextCtrl_Short *GraphicDeltas_GraphicID;
	ComboBox_Plus1 *GraphicDeltas_GraphicID_ComboBox;
	wxBoxSizer *GraphicDeltas_Unknown1_Holder;
	wxStaticText *GraphicDeltas_Unknown1_Text;
	TextCtrl_Short *GraphicDeltas_Unknown1;
	wxBoxSizer *GraphicDeltas_Unknown2_Holder;
	wxStaticText *GraphicDeltas_Unknown2_Text;
	TextCtrl_Short *GraphicDeltas_Unknown2;
	wxBoxSizer *GraphicDeltas_Unknown3_Holder;
	wxStaticText *GraphicDeltas_Unknown3_Text;
	TextCtrl_Short *GraphicDeltas_Unknown3;
	wxBoxSizer *GraphicDeltas_DirectionX_Holder;
	wxStaticText *GraphicDeltas_DirectionX_Text;
	TextCtrl_Short *GraphicDeltas_DirectionX;
	wxBoxSizer *GraphicDeltas_DirectionY_Holder;
	wxStaticText *GraphicDeltas_DirectionY_Text;
	TextCtrl_Short *GraphicDeltas_DirectionY;
	wxBoxSizer *GraphicDeltas_Unknown4_Holder;
	wxStaticText *GraphicDeltas_Unknown4_Text;
	TextCtrl_Short *GraphicDeltas_Unknown4;
	wxBoxSizer *GraphicDeltas_Unknown5_Holder;
	wxStaticText *GraphicDeltas_Unknown5_Text;
	TextCtrl_Short *GraphicDeltas_Unknown5;
	wxBoxSizer *Graphics_AttackSounds_Holder;
	wxGridSizer *Graphics_AttackSounds_Grid;
	wxStaticText *Graphics_AttackSounds_Text;
	wxBoxSizer *Graphics_AttackSoundDelays_Holder;
	wxStaticText *Graphics_AttackSoundDelays_Text;
	TextCtrl_Short *Graphics_AttackSoundDelay[3];
	TextCtrl_Short *Graphics_AttackSoundID[3];
	ComboBox_Plus1 *Graphics_AttackSoundID_ComboBox[3];

//	Terrains user interface

	wxBoxSizer *Terrains_Main;
	wxBoxSizer *Terrains_ListArea;
	wxStaticBoxSizer *Terrains_Terrains;
	wxTextCtrl *Terrains_Terrains_Search;
	wxTextCtrl *Terrains_Terrains_Search_R;
//	wxCheckBox *Terrains_Terrains_UseAnd;
	wxListBox *Terrains_Terrains_List;
	wxBoxSizer *Terrains_UsedCountHolder;
	wxStaticText *Terrains_UsedCountText;
	TextCtrl_UShort *Terrains_UsedCount;
	wxBoxSizer *Borders_UsedCountHolder;
	wxStaticText *Borders_UsedCountText;
	TextCtrl_UShort *Borders_UsedCount;
	wxGridSizer *Terrains_Terrains_Buttons;
	wxButton *Terrains_Add;
	wxButton *Terrains_Insert;
	wxButton *Terrains_Delete;
	wxButton *Terrains_Copy;
	wxButton *Terrains_Paste;
	wxButton *Terrains_PasteInsert;

	wxBoxSizer *Terrains_GreatSpace;
	wxBoxSizer *Terrains_SpaceLeft;
	wxBoxSizer *Terrains_SpaceRight;
	TextCtrl_Short *Terrains_Border;
	ComboBox_Plus1 *Terrains_Border_ComboBox;
	wxStaticBoxSizer *Terrains_Borders;
	wxTextCtrl *Terrains_Borders_Search;
	wxTextCtrl *Terrains_Borders_Search_R;
	wxListBox *Terrains_Borders_List;
	wxGridSizer *Terrains_Borders_Buttons;
	wxButton *Terrains_Borders_Copy;
	wxButton *Terrains_Borders_Paste;
	wxButton *Terrains_Borders_CopyToTerrains;

	wxBoxSizer *Terrains_DataArea;
	wxScrolledWindow *Terrains_Scroller;
	wxBoxSizer *Terrains_ScrollArea;
	wxBoxSizer *Terrains_ScrollSpace;
	wxBoxSizer *Terrains_NameArea_Holder;
	wxGridSizer *Terrains_Area1_Grid;
	wxGridSizer *Terrains_Unknowns1_Grid;
	wxBoxSizer *Terrains_Unknown1_Holder;
	wxStaticText *Terrains_Unknown1_Text;
	TextCtrl_Short *Terrains_Unknown1;
	wxBoxSizer *Terrains_Enabled_Holder;
	wxBoxSizer *Terrains_Enabled1_Holder;
	wxStaticText *Terrains_Enabled_Text;
	TextCtrl_Short *Terrains_Enabled;
	CheckBox_2State *Terrains_Enabled_CheckBox;
	wxBoxSizer *Terrains_Name_Holder;
	wxStaticText *Terrains_Name_Text;
	TextCtrl_String *Terrains_Name;
	wxBoxSizer *Terrains_Name2_Holder;
	wxStaticText *Terrains_Name2_Text;
	TextCtrl_String *Terrains_Name2;
	wxBoxSizer *Terrains_SLP_Holder;
	wxStaticText *Terrains_SLP_Text;
	TextCtrl_Long *Terrains_SLP;
	wxBoxSizer *Terrains_Unknown3_Holder;
	wxStaticText *Terrains_Unknown3_Text;
	TextCtrl_Float *Terrains_Unknown3;
	wxBoxSizer *Terrains_SoundID_Holder;
	wxStaticText *Terrains_SoundID_Text;
	TextCtrl_Long *Terrains_SoundID;
	ComboBox_Plus1 *Terrains_SoundID_ComboBox;
	wxBoxSizer *Terrains_BlendPriority_Holder;
	wxStaticText *Terrains_BlendPriority_Text;
	TextCtrl_Long *Terrains_BlendPriority;
	wxBoxSizer *Terrains_BlendType_Holder;
	wxStaticText *Terrains_BlendType_Text;
	TextCtrl_Long *Terrains_BlendType;
	wxBoxSizer *Terrains_Colors_Holder;
	wxGridSizer *Terrains_Colors_Grid;
	wxStaticText *Terrains_Colors_Text;
	array<TextCtrl_UByte*, 3> Terrains_Colors;
	wxBoxSizer *Terrains_Unknown5_Holder;
	wxGridSizer *Terrains_Unknown5_Grid;
	wxStaticText *Terrains_Unknown5_Text;
	array<TextCtrl_UByte*, 2> Terrains_Unknown5;
	wxBoxSizer *Terrains_Terrain1_Holder;
	wxBoxSizer *Terrains_Terrain2_Holder;
	wxStaticText *Terrains_Terrain1_Text;
	wxStaticText *Terrains_Terrain2_Text;
	TextCtrl_Byte *Terrains_Terrain1;
	TextCtrl_Byte *Terrains_Terrain2;
	ComboBox_Plus1 *Terrains_Terrain1_ComboBox;
	ComboBox_Plus1 *Terrains_Terrain2_ComboBox;
	wxBoxSizer *Terrains_Unknown7_Holder;
	wxGridSizer *Terrains_Unknown7_Grid;
	wxStaticText *Terrains_Unknown7_Text;
	array<TextCtrl_Byte*, 23> Terrains_Unknown7;
	wxBoxSizer *Terrains_FrameCount_Holder;
	wxStaticText *Terrains_FrameCount_Text;
	TextCtrl_Short *Terrains_FrameCount;
	wxBoxSizer *Terrains_AngleCount_Holder;
	wxStaticText *Terrains_AngleCount_Text;
	TextCtrl_Short *Terrains_AngleCount;
	wxBoxSizer *Terrains_TerrainID_Holder;
	wxStaticText *Terrains_TerrainID_Text;
	TextCtrl_Short *Terrains_TerrainID;
	ComboBox_Plus1 *Terrains_TerrainID_ComboBox;
	wxBoxSizer *Terrains_ElevationGraphics_Holder;
	wxGridSizer *Terrains_Unknown9_Grid;
	wxStaticText *Terrains_ElevationGraphics_Text;
	array<TextCtrl_Short*, 54>Terrains_ElevationGraphics;
	wxBoxSizer *Terrains_TerrainReplacementID_Holder;
	wxStaticText *Terrains_TerrainReplacementID_Text;
	TextCtrl_Short *Terrains_TerrainReplacementID;
	ComboBox_Plus1 *Terrains_TerrainReplacementID_ComboBox;
	wxBoxSizer *Terrains_TerrainDimensions_Holder;
	wxStaticText *Terrains_TerrainDimensions_Text;
	array<TextCtrl_Short*, 2>Terrains_TerrainDimensions;
	auto static const TERRAINUNITS = 30;
	wxBoxSizer *Terrains_TerrainUnits_Holder;
	wxBoxSizer *Terrains_TerrainUnitID_Holder;
	wxBoxSizer *Terrains_TerrainUnitID_Holder1;
	wxStaticText *Terrains_TerrainUnitID_Text;
	array<TextCtrl_Short*, TERRAINUNITS>Terrains_TerrainUnitID;
	array<ComboBox_Plus1*, TERRAINUNITS>Terrains_TerrainUnitID_ComboBox;
	wxBoxSizer *Terrains_TerrainUnitDensity_Holder;
	wxStaticText *Terrains_TerrainUnitDensity_Text;
	array<TextCtrl_Short*, TERRAINUNITS>Terrains_TerrainUnitDensity;
	wxBoxSizer *Terrains_TerrainUnitPriority_Holder;
	wxStaticText *Terrains_TerrainUnitPriority_Text;
	array<TextCtrl_Byte*, TERRAINUNITS>Terrains_TerrainUnitPriority;
	wxBoxSizer *Terrains_UsedTerrainUnits_Holder;
	wxGridSizer *Terrains_UsedTerrainUnits_Grid;
	wxStaticText *Terrains_UsedTerrainUnits_Text;
	TextCtrl_Short *Terrains_UsedTerrainUnits;

//	Terrain restrictions user interface

	wxBoxSizer *TerRestrict_Main;
	wxBoxSizer *TerRestrict_ListArea;
	wxGridSizer *TerRestrict_TerRestrict_Buttons;
	wxStaticBoxSizer *TerRestrict_TerRestrict;
	wxTextCtrl *TerRestrict_TerRestrict_Search;
	wxTextCtrl *TerRestrict_TerRestrict_Search_R;
	wxListBox *TerRestrict_TerRestrict_List;
	wxButton *TerRestrict_Add;
	wxButton *TerRestrict_Insert;
	wxButton *TerRestrict_Delete;
	wxButton *TerRestrict_Copy;
	wxButton *TerRestrict_Paste;
	wxButton *TerRestrict_PasteInsert;

	wxBoxSizer *TerRestrict_Terrains;
	wxBoxSizer *TerRestrict_DataArea;
	wxTextCtrl *TerRestrict_Terrains_Search;
	wxTextCtrl *TerRestrict_Terrains_Search_R;
//	wxCheckBox *TerRestrict_Terrains_UseAnd;
	wxListBox *TerRestrict_Terrains_List;
	wxGridSizer *TerRestrict_Terrains_Buttons;
	wxButton *TerRestrict_Terrains_Copy;
	wxButton *TerRestrict_Terrains_Paste;
	wxButton *TerRestrict_Terrains_PasteInsert;
	wxBoxSizer *TerRestrict_Accessible_Holder;
	wxBoxSizer *TerRestrict_Accessible2_Holder;
	wxStaticText *TerRestrict_Accessible_Text;
	TextCtrl_Float *TerRestrict_Accessible;
	CheckBox_2State *TerRestrict_Accessible_CheckBox;
	wxBoxSizer *TerRestrict_Unknown1_Holder;
	wxBoxSizer *TerRestrict_Unknown1Sub_Holder;
	wxStaticText *TerRestrict_Unknown1_Text;
	TextCtrl_Long *TerRestrict_Unknown1;
	CheckBox_ZeroIsYes *TerRestrict_Unknown1_CheckBox;
	wxBoxSizer *TerRestrict_Graphics_Holder;
	wxStaticText *TerRestrict_Graphics_Text;
	TextCtrl_Long *TerRestrict_Graphics[2];
	ComboBox_Plus1 *TerRestrict_Graphics_ComboBox[2];
	wxBoxSizer *TerRestrict_Amount_Holder;
	wxStaticText *TerRestrict_Amount_Text;
	TextCtrl_Float *TerRestrict_Amount;

//	Sound user interface

	wxBoxSizer *Sounds_Main;
	wxBoxSizer *Sounds_ListArea;
	wxGridSizer *Sounds_Sounds_Buttons;
	wxBoxSizer *SoundItems_ListArea;
	wxGridSizer *Sounds_Items_Buttons;
	wxBoxSizer *Sounds_DataArea;
	wxBoxSizer *Sounds_AllArea;

	wxStaticBoxSizer *Sounds_Sounds;
	wxTextCtrl *Sounds_Sounds_Search;
	wxTextCtrl *Sounds_Sounds_Search_R;
	wxListBox *Sounds_Sounds_List;
	wxButton *Sounds_Add;
	wxButton *Sounds_Insert;
	wxButton *Sounds_Delete;
	wxButton *Sounds_Copy;
	wxButton *Sounds_Paste;
	wxButton *Sounds_PasteInsert;

	wxStaticBoxSizer *Sounds_Items;
	wxBoxSizer *Sounds_Items_Searches[2];
	wxTextCtrl *Sounds_Items_Search;
	wxTextCtrl *Sounds_Items_Search_R;
	wxOwnerDrawnComboBox *Sounds_Items_SearchFilters[2];
	wxCheckBox *Sounds_Items_UseAnd[2];
	wxListBox *Sounds_Items_List;
	wxButton *SoundItems_Add;
	wxButton *SoundItems_Insert;
	wxButton *SoundItems_Delete;
	wxButton *SoundItems_Copy;
	wxButton *SoundItems_Paste;
	wxButton *SoundItems_PasteInsert;
	wxButton *SoundItems_CopyToSounds;

	wxBoxSizer *Sounds_ID_Holder;
	wxStaticText *Sounds_ID_Text;
	TextCtrl_Short *Sounds_ID;
	wxBoxSizer *Sounds_Unknown1_Holder;
	wxStaticText *Sounds_Unknown1_Text;
	TextCtrl_Short *Sounds_Unknown1;
	wxBoxSizer *Sounds_Unknown2_Holder;
	wxStaticText *Sounds_Unknown2_Text;
	TextCtrl_Long *Sounds_Unknown2;
	wxBoxSizer *SoundItems_Name_Holder;
	wxStaticText *SoundItems_Name_Text;
	TextCtrl_String *SoundItems_Name;
	wxBoxSizer *SoundItems_Resource_Holder;
	wxStaticText *SoundItems_Resource_Text;
	TextCtrl_Long *SoundItems_Resource;
	wxBoxSizer *SoundItems_Probability_Holder;
	wxStaticText *SoundItems_Probability_Text;
	TextCtrl_Short *SoundItems_Probability;
	wxBoxSizer *SoundItems_Civ_Holder;
	wxStaticText *SoundItems_Civ_Text;
	TextCtrl_Short *SoundItems_Civ;
	ComboBox_Plus1 *SoundItems_Civ_ComboBox;
	wxBoxSizer *SoundItems_Unknown_Holder;
	wxStaticText *SoundItems_Unknown_Text;
	TextCtrl_Short *SoundItems_Unknown;

	wxStaticBoxSizer *Sounds_AllItems;
	wxBoxSizer *Sounds_AllItems_Searches[2];
	wxTextCtrl *Sounds_AllItems_Search;
	wxTextCtrl *Sounds_AllItems_Search_R;
	wxCheckBox *Sounds_AllItems_UseAnd[2];
	wxListBox *Sounds_AllItems_List;
	wxBoxSizer *Sounds_AllItems_Buttons;
	wxButton *Sounds_AllItems_Load;
	wxButton *Sounds_AllItems_Clear;

//	Player Color user interface

	wxBoxSizer *Colors_Main;
	wxBoxSizer *Colors_ListArea;
	wxGridSizer *Colors_Colors_Buttons;
	wxStaticBoxSizer *Colors_Colors;
	wxTextCtrl *Colors_Colors_Search;
	wxTextCtrl *Colors_Colors_Search_R;
	wxListBox *Colors_Colors_List;
	wxButton *Colors_Add;
	wxButton *Colors_Insert;
	wxButton *Colors_Delete;
	wxButton *Colors_Copy;
	wxButton *Colors_Paste;
	wxButton *Colors_PasteInsert;

	wxBoxSizer *Colors_DataArea;
	wxBoxSizer *Colors_Name_Holder;
	wxBoxSizer *Colors_ID_Holder;
	wxBoxSizer *Colors_Palette_Holder;
	wxBoxSizer *Colors_Color_Holder;
	wxBoxSizer *Colors_MinimapColor_Holder;
	wxBoxSizer *Colors_UnknownArea_Holder;
	wxBoxSizer *Colors_Unknown1_Holder;
	wxBoxSizer *Colors_Unknown2_Holder;
	wxBoxSizer *Colors_Unknown3_Holder;
	wxBoxSizer *Colors_Unknown4_Holder;
	wxBoxSizer *Colors_Unknown5_Holder;
	wxStaticText *Colors_Name_Text;
	wxStaticText *Colors_ID_Text;
	wxStaticText *Colors_Palette_Text;
	wxStaticText *Colors_Color_Text;
	wxStaticText *Colors_MinimapColor_Text;
	wxStaticText *Colors_Unknown1_Text;
	wxStaticText *Colors_Unknown2_Text;
	wxStaticText *Colors_Unknown3_Text;
	wxStaticText *Colors_Unknown4_Text;
	wxStaticText *Colors_Unknown5_Text;
	TextCtrl_String *Colors_Name;
	TextCtrl_Long *Colors_ID;
	TextCtrl_Long *Colors_Palette;
	TextCtrl_Long *Colors_ColorL;
	TextCtrl_Long *Colors_MinimapColor;
	TextCtrl_Long *Colors_Unknown1;
	TextCtrl_Long *Colors_Unknown2;
	TextCtrl_Long *Colors_Unknown3;
	TextCtrl_Long *Colors_Unknown4;
	TextCtrl_Long *Colors_Unknown5;

//	Unitline user interface

	wxBoxSizer *UnitLines_Main;
	wxBoxSizer *UnitLines_ListArea;
	wxGridSizer *UnitLines_UnitLines_Buttons;
	wxBoxSizer *UnitLineUnits_ListArea;
	wxGridSizer *UnitLines_UnitLineUnits_Buttons;
	wxBoxSizer *UnitLines_DataArea;

	wxStaticBoxSizer *UnitLines_UnitLines;
	wxTextCtrl *UnitLines_UnitLines_Search;
	wxTextCtrl *UnitLines_UnitLines_Search_R;
	wxListBox *UnitLines_UnitLines_List;
	wxButton *UnitLines_Add;
	wxButton *UnitLines_Insert;
	wxButton *UnitLines_Delete;
	wxButton *UnitLines_Copy;
	wxButton *UnitLines_Paste;
	wxButton *UnitLines_PasteInsert;

	wxBoxSizer *UnitLines_ID_Holder;
	wxStaticText *UnitLines_ID_Text;
	TextCtrl_Short *UnitLines_ID;
	wxBoxSizer *UnitLines_Name_Holder;
	wxStaticText *UnitLines_Name_Text;
	TextCtrl_String *UnitLines_Name;

	wxStaticBoxSizer *UnitLines_UnitLineUnits;
	wxTextCtrl *UnitLines_UnitLineUnits_Search;
	wxTextCtrl *UnitLines_UnitLineUnits_Search_R;
	wxListBox *UnitLines_UnitLineUnits_List;
	wxButton *UnitLineUnits_Add;
	wxButton *UnitLineUnits_Insert;
	wxButton *UnitLineUnits_Delete;
	wxButton *UnitLineUnits_Copy;
	wxButton *UnitLineUnits_Paste;
	wxButton *UnitLineUnits_PasteInsert;
	wxButton *UnitLineUnits_CopyToUnitLines;

	wxBoxSizer *UnitLineUnits_Holder;
	wxStaticText *UnitLineUnits_Text;
	TextCtrl_Short *UnitLineUnits_Units;
	ComboBox_Plus1 *UnitLineUnits_ComboBox;

//	Tech Tree user interface

	wxBoxSizer *TechTrees_Main;
	wxBoxSizer *TechTrees_All;
	wxBoxSizer *TechTrees_TabAges;
	wxBoxSizer *TechTrees_TabBuildings;
	wxBoxSizer *TechTrees_TabUnits;
	wxBoxSizer *TechTrees_TabResearches;
	wxScrolledWindow *TechTrees_ScrollerAges;
	wxScrolledWindow *TechTrees_ScrollerBuildings;
	wxScrolledWindow *TechTrees_ScrollerUnits;
	wxScrolledWindow *TechTrees_ScrollerResearches;
	wxBoxSizer *TechTrees_ScrollArea1;
	wxBoxSizer *TechTrees_ScrollArea2;
	wxBoxSizer *TechTrees_ScrollArea3;
	wxBoxSizer *TechTrees_ScrollArea4;
	wxBoxSizer *TechTrees_ScrollSpace1;
	wxBoxSizer *TechTrees_ScrollSpace2;
	wxBoxSizer *TechTrees_ScrollSpace3;
	wxBoxSizer *TechTrees_ScrollSpace4;
	wxBoxSizer *TechTrees_MainList_Ages;
	wxBoxSizer *TechTrees_MainList_Buildings;
	wxBoxSizer *TechTrees_MainList_Units;
	wxBoxSizer *TechTrees_MainList_Researches;
	wxBoxSizer *TechTrees_MainList_Buildings_Searches[2];
	wxBoxSizer *TechTrees_MainList_Units_Searches[2];
	wxBoxSizer *TechTrees_MainList_Researches_Searches[2];
	wxTextCtrl *TechTrees_MainList_Ages_Search;
	wxTextCtrl *TechTrees_MainList_Buildings_Search;
	wxTextCtrl *TechTrees_MainList_Units_Search;
	wxTextCtrl *TechTrees_MainList_Researches_Search;
	wxTextCtrl *TechTrees_MainList_Ages_Search_R;
	wxTextCtrl *TechTrees_MainList_Buildings_Search_R;
	wxTextCtrl *TechTrees_MainList_Units_Search_R;
	wxTextCtrl *TechTrees_MainList_Researches_Search_R;
	wxOwnerDrawnComboBox *TechTrees_MainList_Buildings_SearchFilters[2];
	wxOwnerDrawnComboBox *TechTrees_MainList_Units_SearchFilters[2];
	wxOwnerDrawnComboBox *TechTrees_MainList_Researches_SearchFilters[2];
	wxCheckBox *TechTrees_MainList_Buildings_UseAnd[2];
	wxCheckBox *TechTrees_MainList_Units_UseAnd[2];
	wxCheckBox *TechTrees_MainList_Researches_UseAnd[2];
	wxListBox *TechTrees_MainList_Ages_List;
	wxListBox *TechTrees_MainList_Buildings_List;
	wxListBox *TechTrees_MainList_Units_List;
	wxListBox *TechTrees_MainList_Researches_List;
	wxGridSizer *TechTrees_MainList_Ages_Buttons;
	wxGridSizer *TechTrees_MainList_Buildings_Buttons;
	wxGridSizer *TechTrees_MainList_Units_Buttons;
	wxGridSizer *TechTrees_MainList_Researches_Buttons;
	wxButton *TechTrees_MainList_Ages_Add;
	wxButton *TechTrees_MainList_Buildings_Add;
	wxButton *TechTrees_MainList_Units_Add;
	wxButton *TechTrees_MainList_Researches_Add;
	wxButton *TechTrees_MainList_Ages_Insert;
	wxButton *TechTrees_MainList_Buildings_Insert;
	wxButton *TechTrees_MainList_Units_Insert;
	wxButton *TechTrees_MainList_Researches_Insert;
	wxButton *TechTrees_MainList_Ages_Delete;
	wxButton *TechTrees_MainList_Buildings_Delete;
	wxButton *TechTrees_MainList_Units_Delete;
	wxButton *TechTrees_MainList_Researches_Delete;
	wxButton *TechTrees_MainList_Ages_Copy;
	wxButton *TechTrees_MainList_Buildings_Copy;
	wxButton *TechTrees_MainList_Units_Copy;
	wxButton *TechTrees_MainList_Researches_Copy;
	wxButton *TechTrees_MainList_Ages_Paste;
	wxButton *TechTrees_MainList_Buildings_Paste;
	wxButton *TechTrees_MainList_Units_Paste;
	wxButton *TechTrees_MainList_Researches_Paste;
	wxButton *TechTrees_MainList_Ages_PasteInsert;
	wxButton *TechTrees_MainList_Buildings_PasteInsert;
	wxButton *TechTrees_MainList_Units_PasteInsert;
	wxButton *TechTrees_MainList_Researches_PasteInsert;

	AGE_List32Box TechTrees_Ages_Buildings;
	AGE_List32Box TechTrees_Ages_Units;
	AGE_List32Box TechTrees_Ages_Researches;
	AGE_List32Box TechTrees_Buildings_Buildings;
	AGE_List32Box TechTrees_Buildings_Units;
	AGE_List32Box TechTrees_Buildings_Researches;
	AGE_List32Box TechTrees_Units_Units;
	AGE_List32Box TechTrees_Researches_Buildings;
	AGE_List32Box TechTrees_Researches_Units;
	AGE_List32Box TechTrees_Researches_Researches;
	AGE_AreaTT84 TechTrees_Ages_Items;
	AGE_AreaTT31020 TechTrees_Ages_UnknownItems;
	AGE_AreaTT84 TechTrees_Buildings_Items;
	AGE_AreaTT84 TechTrees_Units_Items;
	AGE_AreaTT84 TechTrees_Researches_Items;

	wxBoxSizer *TechTrees_Data_Ages;
	wxBoxSizer *TechTrees_Data_Ages2;
	wxGridSizer *TechTrees_Data_Ages1;
	wxBoxSizer *TechTrees_Data_Buildings;
	wxBoxSizer *TechTrees_Data_Buildings2;
	wxBoxSizer *TechTrees_Data_Buildings3;
	wxGridSizer *TechTrees_Data_Buildings1;
	wxBoxSizer *TechTrees_Data_Units;
	wxGridSizer *TechTrees_Data_Units1;
	wxBoxSizer *TechTrees_Data_Researches;
	wxBoxSizer *TechTrees_Data_Researches2;
	wxGridSizer *TechTrees_Data_Researches1;
	wxBoxSizer *TechTrees_Data_Researches3;
	wxBoxSizer *TechTrees_ConnectedHolder_Ages;
	wxBoxSizer *TechTrees_ConnectedHolder_Buildings;
	wxBoxSizer *TechTrees_ConnectedHolder_Units;
	wxBoxSizer *TechTrees_ConnectedHolder_Researches;

	wxBoxSizer *TechTrees_Ages_ID_Holder;
	wxStaticText *TechTrees_Ages_ID_Text;
	TextCtrl_Long *TechTrees_Ages_ID;
	wxBoxSizer *TechTrees_Ages_Unknown2_Holder;
	wxStaticText *TechTrees_Ages_Unknown2_Text;
	TextCtrl_Byte *TechTrees_Ages_Unknown2;
	wxBoxSizer *TechTrees_Ages_LineMode_Holder;
	wxStaticText *TechTrees_Ages_LineMode_Text;
	TextCtrl_Long *TechTrees_Ages_LineMode;

	wxBoxSizer *TechTrees_Buildings_ID_Holder;
	wxStaticText *TechTrees_Buildings_ID_Text;
	TextCtrl_Long *TechTrees_Buildings_ID;
	ComboBox_Plus1 *TechTrees_Buildings_ID_ComboBox;
	wxBoxSizer *TechTrees_Buildings_Always2_Holder;
	wxStaticText *TechTrees_Buildings_Always2_Text;
	TextCtrl_Byte *TechTrees_Buildings_Always2;

	wxBoxSizer *TechTrees_Buildings_LocationInAge_Holder;
	wxStaticText *TechTrees_Buildings_LocationInAge_Text;
	TextCtrl_Byte *TechTrees_Buildings_LocationInAge;
	wxBoxSizer *TechTrees_Buildings_LineMode_Holder;
	wxStaticText *TechTrees_Buildings_LineMode_Text;
	TextCtrl_Long *TechTrees_Buildings_LineMode;
	wxBoxSizer *TechTrees_Buildings_EnablingResearch_Holder;
	wxStaticText *TechTrees_Buildings_EnablingResearch_Text;
	TextCtrl_Long *TechTrees_Buildings_EnablingResearch;
	ComboBox_Plus1 *TechTrees_Buildings_EnablingResearch_ComboBox;
	wxStaticBoxSizer *TechTrees_Buildings_TotalUnitsTechs_Holder[2];
	wxGridSizer *TechTrees_Buildings_TotalUnitsTechs_Grid[2];
	TextCtrl_Byte *TechTrees_Buildings_TotalUnitsTechs[10];

	wxBoxSizer *TechTrees_Units_ID_Holder;
	wxStaticText *TechTrees_Units_ID_Text;
	TextCtrl_Long *TechTrees_Units_ID;
	ComboBox_Plus1 *TechTrees_Units_ID_ComboBox;
	wxBoxSizer *TechTrees_Units_Always2_Holder;
	wxStaticText *TechTrees_Units_Always2_Text;
	TextCtrl_Byte *TechTrees_Units_Always2;
	wxBoxSizer *TechTrees_Units_UpperBuilding_Holder;
	wxStaticText *TechTrees_Units_UpperBuilding_Text;
	TextCtrl_Long *TechTrees_Units_UpperBuilding;
	ComboBox_Plus1 *TechTrees_Units_UpperBuilding_ComboBox;

	wxBoxSizer *TechTrees_Units_VerticalLine_Holder;
	wxStaticText *TechTrees_Units_VerticalLine_Text;
	TextCtrl_Long *TechTrees_Units_VerticalLine;

	wxBoxSizer *TechTrees_Units_LocationInAge_Holder;
	wxStaticText *TechTrees_Units_LocationInAge_Text;
	TextCtrl_Long *TechTrees_Units_LocationInAge;
	wxBoxSizer *TechTrees_Units_RequiredResearch_Holder;
	wxStaticText *TechTrees_Units_RequiredResearch_Text;
	TextCtrl_Long *TechTrees_Units_RequiredResearch;
	ComboBox_Plus1 *TechTrees_Units_RequiredResearch_ComboBox;
	wxBoxSizer *TechTrees_Units_LineMode_Holder;
	wxStaticText *TechTrees_Units_LineMode_Text;
	TextCtrl_Long *TechTrees_Units_LineMode;
	wxBoxSizer *TechTrees_Units_EnablingResearch_Holder;
	wxStaticText *TechTrees_Units_EnablingResearch_Text;
	TextCtrl_Long *TechTrees_Units_EnablingResearch;
	ComboBox_Plus1 *TechTrees_Units_EnablingResearch_ComboBox;

	wxBoxSizer *TechTrees_Researches_ID_Holder;
	wxStaticText *TechTrees_Researches_ID_Text;
	TextCtrl_Long *TechTrees_Researches_ID;
	ComboBox_Plus1 *TechTrees_Researches_ID_ComboBox;
	wxBoxSizer *TechTrees_Researches_Always2_Holder;
	wxStaticText *TechTrees_Researches_Always2_Text;
	TextCtrl_Byte *TechTrees_Researches_Always2;
	wxBoxSizer *TechTrees_Researches_UpperBuilding_Holder;
	wxStaticText *TechTrees_Researches_UpperBuilding_Text;
	TextCtrl_Long *TechTrees_Researches_UpperBuilding;
	ComboBox_Plus1 *TechTrees_Researches_UpperBuilding_ComboBox;

	wxBoxSizer *TechTrees_Researches_VerticalLine_Holder;
	wxStaticText *TechTrees_Researches_VerticalLine_Text;
	TextCtrl_Long *TechTrees_Researches_VerticalLine;
	wxBoxSizer *TechTrees_Researches_LocationInAge_Holder;
	wxStaticText *TechTrees_Researches_LocationInAge_Text;
	TextCtrl_Long *TechTrees_Researches_LocationInAge;
	wxBoxSizer *TechTrees_Researches_LineMode_Holder;
	wxStaticText *TechTrees_Researches_LineMode_Text;
	TextCtrl_Long *TechTrees_Researches_LineMode;

//	DRS user interface

	/*genie::DrsFile *ResourceFile;

	void LoadDRSFile(wxCommandEvent &Event);
	void UnLoadDRSFile(wxCommandEvent &Event);
	void LoadSLP(wxCommandEvent &Event);

	wxBoxSizer *DRS_Main;
	wxBoxSizer *DRS_TopRow;
	wxBoxSizer *DRS_MidArea;

	wxStaticText *DRS_FileLocation_Text;
	wxFilePickerCtrl *DRS_Path_FileLocation;
	wxButton *DRS_LoadButton;
	wxButton *DRS_UnLoadButton;
	wxButton *DRS_SLPLoadButton;
	wxStaticText *DRS_StatusText;*/

//	Template functions

	template <class P>
	inline void AddToListNoGV(P &path)
	{
		path.emplace_back();
		Added = true;
	}
	template <class P>
	inline void AddToList(P &path)
	{
		path.emplace_back();
		path.back().setGameVersion(GenieVersion);
		Added = true;
	}
	template <class P>
	inline void AddToListIDFix(P &path)
	{
		path.emplace_back();
		path.back().setGameVersion(GenieVersion);
		if(EnableIDFix)
		path.back().ID = path.size() - 1; // ID Fix
		Added = true;
	}

	template <class P>
	inline void InsertToListNoGV(P &path, short place)
	{
		path.emplace(path.begin() + place);
	}
	template <class P>
	inline void InsertToList(P &path, short place)
	{
		path.emplace(path.begin() + place);
		path[place].setGameVersion(GenieVersion);
	}
	template <class P>
	inline void InsertToListIDFix(P &path, short place)
	{
		path.emplace(path.begin() + place);
		path[place].setGameVersion(GenieVersion);
		if(EnableIDFix)
		for(auto loop = path.size(); loop--> place;) // ID Fix
		path[loop].ID = loop;
	}

	template <class P>
	inline void DeleteFromList(P &path, vector<short> &places)
	{
		for(auto loop = places.size(); loop--> 0;)
		path.erase(path.begin() + places[loop]);
	}
	template <class P>
	inline void DeleteFromListIDFix(P &path, vector<short> &places)
	{
		for(auto loop = places.size(); loop--> 0;)
		path.erase(path.begin() + places[loop]);
		if(EnableIDFix)
		for(auto loop = path.size(); loop--> places[0];) // ID Fix
		path[loop].ID = loop;
	}

	template <class P, class C>
	inline void CopyFromList(P &path, vector<short> &places, C &copies)
	{
		copies.resize(places.size());
		for(auto loop = places.size(); loop--> 0;)
		copies[loop] = path[places[loop]];
	}

	template <class P, class C>
	inline void PasteToListNoGV(P &path, short place, C &copies)
	{
		if(copies.size() + place > path.size())
		path.resize(copies.size() + place);
		for(auto loop = copies.size(); loop--> 0;)
		{
			path[place + loop] = copies[loop];
		}
	}
	template <class P, class C>
	inline void PasteToListNoGV(P &path, vector<short> &places, C &copies)
	{
		for(int loop = 0, from = 0; loop < places.size(); ++loop, ++from)
		{
			from %= copies.size();
			path[places[loop]] = copies[from];
		}
	}
	template <class P, class C>
	inline void PasteToList(P &path, short place, C &copies)
	{
		if(copies.size() + place > path.size())
		path.resize(copies.size() + place);
		for(auto loop = copies.size(); loop--> 0;)
		{
			copies[loop].setGameVersion(GenieVersion);
			path[place + loop] = copies[loop];
		}
	}
	template <class P, class C>
	inline void PasteToList(P &path, vector<short> &places, C &copies)
	{
		for(int loop = 0, from = 0; loop < places.size(); ++loop, ++from)
		{
			from %= copies.size();
			path[places[loop]] = copies[from];
			path[places[loop]].setGameVersion(GenieVersion);
		}
	}
	template <class P, class C>
	inline void PasteToListNoResize(P &path, short place, C &copies)
	{
		auto CopyCount = copies.size();
		if(CopyCount + place > path.size())
		CopyCount -= CopyCount + place - path.size();
		for(auto loop = CopyCount; loop--> 0;)
		{
			copies[loop].setGameVersion(GenieVersion);
			path[place + loop] = copies[loop];
		}
	}
	template <class P, class C>
	inline void PasteToListIDFix(P &path, short place, C &copies)
	{
		if(copies.size() + place > path.size())
		path.resize(copies.size() + place);
		for(auto loop = copies.size(); loop--> 0;)
		{
			copies[loop].setGameVersion(GenieVersion);
			path[place + loop] = copies[loop];
			if(EnableIDFix)
			path[place + loop].ID = place + loop; // ID Fix
		}
	}

	template <class P, class C>
	inline void PasteInsertToListNoGV(P &path, short place, C &copies)
	{
		path.insert(path.begin() + place, copies.begin(), copies.end());
	}
	template <class P, class C>
	inline void PasteInsertToList(P &path, short place, C &copies)
	{
		for(auto loop = copies.size(); loop--> 0;)
		copies[loop].setGameVersion(GenieVersion);
		path.insert(path.begin() + place, copies.begin(), copies.end());
	}
	template <class P, class C>
	inline void PasteInsertToListIDFix(P &path, short place, C &copies)
	{
		for(auto loop = copies.size(); loop--> 0;)
		copies[loop].setGameVersion(GenieVersion);
		path.insert(path.begin() + place, copies.begin(), copies.end());
		if(EnableIDFix)
		for(auto loop = path.size(); loop--> place;) // ID Fix
		path[loop].ID = loop;
	}
};
