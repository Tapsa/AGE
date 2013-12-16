#include "Common.h"
#include "AGE_TextControls.h"
#include "AGE_ComboBoxes.h"
#include "AGE_CheckBoxes.h"
#include "AGE_OpenDialog.h"
#include "AGE_SaveDialog.h"
#include "AGE_AboutDialog.h"
#include "AGE_Copies.hpp"
//#include <wx/dynarray.h>
using std::array;
using std::list;
using std::vector;

/*class MyCanvas: public wxSFMLCanvas
{
public :

    ////////////////////////////////////////////////////////////
    /// Construct the canvas
    ///
    ////////////////////////////////////////////////////////////
    MyCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style = 0) :
    wxSFMLCanvas(Parent, Id, Position, Size, Style)
    {
        // Change background color
        SetBackgroundColor(sfColor(0, 128, 128));

        // Load an image and assign it to our sprite
        myImage.LoadFromFile("sprite.png");
        mySprite.SetImage(myImage);
    }

private :

    ////////////////////////////////////////////////////////////
    /// /see wxSFMLCanvas::OnUpdate
    ///
    ////////////////////////////////////////////////////////////
    virtual void OnUpdate()
    {
        Draw(mySprite);
    }

    ////////////////////////////////////////////////////////////
    /// Member data
    ////////////////////////////////////////////////////////////
    sf::Image  myImage;  ///< Some image to load...
    sf::Sprite mySprite; ///< Something to draw...
};*/

//Working stuff if you need custom wxArrays. I'll just use standard vectors instead.
//WX_DECLARE_OBJARRAY(float, wxArrayFloat);
//WX_DECLARE_OBJARRAY(genie::Civ, ArrayCivCopy);
//WX_DECLARE_OBJARRAY(genie::PlayerColour, ArrayPlayerColour);

class AGE_Frame: public wxFrame
{
public:
	AGE_Frame(const wxString &title, Copies &c, short window = 1);

//	Stuff related to editing multiple files at once

	//AGE_Frame *secondWindow;
	Copies *copies;

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
	void OnGameVersionChange();
//	void OnTempBackup();
//	void OnUndoing(wxCommandEvent &Event);
//	void OnReload(wxCommandEvent &Event);
//	void OnSectionChange(wxCommandEvent &Event);
	void OnSave(wxCommandEvent &Event);
//	void OnReset(wxCommandEvent &Event);
//	void OnExecute(wxCommandEvent &Event);
//	void OnQuickExecute(wxCommandEvent &Event);
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

	void OnUpdateCombo_Techs(wxCommandEvent &Event);
	void OnUpdateCombo_TechTrees(wxCommandEvent &Event);
	void OnUpdateCombo_Units(wxCommandEvent &Event);
	void OnUpdateCombo_UnitLines(wxCommandEvent &Event);
	void OnUpdateCombo_Graphics(wxCommandEvent &Event);

//	Other Methods

//	bool FileExists(const char *value);
	wxString searchText, excludeText;
	bool SearchMatches(wxString itemText);
	void Listing(wxListBox* &List, wxArrayString &names, list<void*> &data);
	void ListingFix(int selections, wxListBox* &List);
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

//	Exporting and importing common functions.
	//bool CorrectVersion(int &Version);
	//void ExpError(wxFileConfig &Extract);
	//void ImpError();

//	General Events

	void ListGeneral();
	void OnGeneralSelect(wxCommandEvent &Event);
//	void OnDataGridPage(wxCommandEvent &Event);
//	void OnDataGridNext(wxCommandEvent &Event);
//	void OnDataGridPrev(wxCommandEvent &Event);
	void OnVariableCalc(wxFocusEvent &Event);
	void OnVariableCalcReverse(wxFocusEvent &Event);

	void ListUnknowns();
	void OnUnknownsSearch(wxCommandEvent &Event);
	void OnUnknownsSelect(wxCommandEvent &Event);
	void OnUnknownsAdd(wxCommandEvent &Event);
	void OnUnknownsInsert(wxCommandEvent &Event);
	void OnUnknownsDelete(wxCommandEvent &Event);
	void OnUnknownsCopy(wxCommandEvent &Event);
	void OnUnknownsPaste(wxCommandEvent &Event);
	void OnUnknownsPasteInsert(wxCommandEvent &Event);
	string GetUnknownName(short);

	void ListUnknownFirstSubData();
	void DisableUnknownFirstSubData();
	void OnUnknownFirstSubDataSearch(wxCommandEvent &Event);
	void OnUnknownFirstSubDataSelect(wxCommandEvent &Event);
	void OnUnknownFirstSubDataAdd(wxCommandEvent &Event);
	void OnUnknownFirstSubDataInsert(wxCommandEvent &Event);
	void OnUnknownFirstSubDataDelete(wxCommandEvent &Event);
	void OnUnknownFirstSubDataCopy(wxCommandEvent &Event);
	void OnUnknownFirstSubDataPaste(wxCommandEvent &Event);
	void OnUnknownFirstSubDataPasteInsert(wxCommandEvent &Event);
	void OnUnknownFirstSubDataCopyToMaps(wxCommandEvent &Event);
	string GetUnknownFirstSubDataName(short);

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

	void ListTTAgess();
	void OnTTAgesSearch(wxCommandEvent &Event);
	void OnTTAgesSelect(wxCommandEvent &Event);
	void OnTTAgesAdd(wxCommandEvent &Event);
	void OnTTAgesInsert(wxCommandEvent &Event);
	void OnTTAgesDelete(wxCommandEvent &Event);
	void OnTTAgesCopy(wxCommandEvent &Event);
	void OnTTAgesPaste(wxCommandEvent &Event);
	void OnTTAgesPasteInsert(wxCommandEvent &Event);
	string GetTTAgesName(short);

	void ListTTAgesBuildings();
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

	void ListTTAgesUnits();
	void OnTTAgesUnitSearch(wxCommandEvent &Event);
	void OnTTAgesUnitSelect(wxCommandEvent &Event);
	void OnTTAgesUnitAdd(wxCommandEvent &Event);
	void OnTTAgesUnitInsert(wxCommandEvent &Event);
	void OnTTAgesUnitDelete(wxCommandEvent &Event);
	void OnTTAgesUnitCopy(wxCommandEvent &Event);
	void OnTTAgesUnitPaste(wxCommandEvent &Event);
	void OnTTAgesUnitPasteInsert(wxCommandEvent &Event);
	void OnTTAgesUnitCopyToAges(wxCommandEvent &Event);

	void ListTTAgesResearches();
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

	void ListTerrains(bool all = true);
	void OnTerrainsSearch(wxCommandEvent &Event);
//	void OnTerRestTerrainsSearch(wxCommandEvent &Event);
	void OnTerrainsSelect(wxCommandEvent &Event);
	void OnTerrainsAdd(wxCommandEvent &Event);
	void OnTerrainsInsert(wxCommandEvent &Event);
	void OnTerrainsDelete(wxCommandEvent &Event);
	void OnTerrainsCopy(wxCommandEvent &Event);
	void OnTerrainsPaste(wxCommandEvent &Event);
	void OnTerrainsPasteInsert(wxCommandEvent &Event);
	string GetTerrainName(short);

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

	bool PromptForFilesOnOpen;
	bool AutoCopy;
	bool CopyGraphics;
	bool AllCivs;
	vector<short> SelectedCivs;
//	static const wxString CIVCOUNTWARNING;
//	int SearchFilters;
	bool useAnd[2];
	bool EnableIDFix;
	bool ShowUnknowns;
	bool ShowButtons;
	bool ShowHelpOnStart;
//	bool UseUndo;
	bool NeedDat;
	bool SkipOpenDialog;
	wxFileConfig *Config;
	wxFileConfig *Customs;
	genie::DatFile *GenieFile;
	genie::LangFile *Lang;
	genie::LangFile *LangX;
	genie::LangFile *LangXP;
//	wxSound SoundFile;

	list<ComboBox_Plus1*> ResearchComboBoxList;
	list<ComboBox_Plus1*> TechComboBoxList;
	list<ComboBox_Plus1*> CivComboBoxList;
	list<ComboBox_Plus1*> ResourceComboBoxList;
	list<ComboBox_Plus1*> UnitComboBoxList;
	list<ComboBox_Plus1*> GraphicComboBoxList;
	list<ComboBox_Plus1*> TerrainComboBoxList;
	list<ComboBox_Plus1*> TerrainBorderComboBoxList;
	list<ComboBox_Plus1*> TerrainRestrictionComboBoxList;
	list<ComboBox_Plus1*> SoundComboBoxList;

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
	vector<short> ResearchIDs;
	vector<short> TechIDs;
	vector<short> EffectIDs;
	vector<short> TTAgeIDs;
	vector<short> TTAgeBuildIDs;
	vector<short> TTAgeUnitIDs;
	vector<short> TTAgeResIDs;
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
	int SimultaneousFiles, GameVersion, DatUsed, SaveGameVersion;
	genie::GameVersion GenieVersion;
	wxString DriveLetter, Language, CustomFolder;
	wxString DatFileName;
	wxString ApfFileName;
	wxString SaveDatFileName;
	wxString SaveApfFileName;
	int LangsUsed; // 0x01 Lang.dll, 0x02, LangX1.dll, 0x04 LangX1P1.dll
	wxString LangCharset;
	wxString LangFileName;
	wxString LangX1FileName;
	wxString LangX1P1FileName;
	wxString SaveLangFileName;
	wxString SaveLangX1FileName;
	wxString SaveLangX1P1FileName;

	HINSTANCE LanguageDLL[3];
	string LangDLLstring(int ID, int Letters = 0);
	//void WriteLangDLLstring(int ID, wxString Name);

//	Constants, remove unneeded entries.

	enum
	{
		MenuOption_Prompt,
		MenuOption_IDFix,
		MenuOption_Buttons,
		MenuOption_Tips,
		MenuOption_About,
		ToolBar_Open,
		ToolBar_Save,
		ToolBar_Show,
		ToolBar_Help
	};

//	User Interface

	wxMenuBar *MenuBar_Main;
	wxMenu *SubMenu_Options;
	wxMenu *SubMenu_Help;

	wxNotebook *TabBar_Main;
//	wxNotebook *TabBar_Data;
//	wxNotebook *TabBar_Test;

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

//	wxPanel *Tab_DRS;

//	General user interface

	wxBoxSizer *General_Main;
	wxBoxSizer *General_TopRow;
	wxButton *General_Refresh;
	wxStaticText *General_Text_CalcBoxes;
	wxStaticText *General_Text_CalcBoxesMiddle;
	wxTextCtrl *General_CalcBoxes[5];
	wxScrolledWindow *General_Scroller;
	wxBoxSizer *General_ScrollerWindows;
	wxBoxSizer *General_ScrollerWindowsSpace;
	wxBoxSizer *General_Holder_TerrainHeader;
	wxStaticText *General_Text_TerrainHeader;
	wxGridSizer *General_Grid_TerrainHeader;
	array<TextCtrl_Short*, 69> General_TerrainHeader;

	wxBoxSizer *General_Holder_BorderRelated;
	wxStaticText *General_Text_BorderRelated;
	wxGridSizer *General_Grid_BorderRelated;
	array<TextCtrl_Short*, 15> General_AfterBorders;

	wxBoxSizer *General_Holder_TerrainRendering;
	wxStaticText *General_Text_TerrainRendering;
	wxGridSizer *General_Grid_TerrainRendering;
	array<TextCtrl_Short*, 31> General_TerrainRendering;
	wxGridSizer *General_Grid_Something;
	array<TextCtrl_Long*, 157> General_Something;

	wxBoxSizer *Borders_Main;
	wxBoxSizer *Borders_ListArea;
	wxStaticBoxSizer *Borders_Borders;
	wxGridSizer *Borders_Borders_Buttons;
	wxTextCtrl *Borders_Borders_Search;
	wxTextCtrl *Borders_Borders_Search_R;
	wxListBox *Borders_Borders_List;
	wxButton *Borders_Copy;
	wxButton *Borders_Paste;
	wxBoxSizer *Borders_DataArea;
	wxBoxSizer *Borders_DataTopRow;
	wxGridSizer *Borders_Data1;
	wxBoxSizer *Borders_FrameData;
	wxStaticBoxSizer *Borders_Holder_Frames;
	wxBoxSizer *Borders_Frames;
	wxGridSizer *Borders_Frames_Buttons;
	wxTextCtrl *Borders_Frames_Search;
	wxTextCtrl *Borders_Frames_Search_R;
	wxListBox *Borders_Frames_List;
	wxButton *Frames_Copy;
	wxButton *Frames_Paste;
	wxButton *Frames_CopyToBorders;
	wxBoxSizer *Borders_Holder_FrameArea;
	wxGridSizer *Borders_Unknonws;
	wxBoxSizer *Borders_Holder_BorderEnabled;
	wxBoxSizer *Borders_Holder_BorderEnabled1;
	wxStaticText *Borders_Text_BorderEnabled;
	TextCtrl_Short *Borders_BorderEnabled;
	CheckBox_2State *Borders_CheckBox_BorderEnabled;
	wxBoxSizer *Borders_Holder_BorderName[2];
	wxStaticText *Borders_Text_BorderName[2];
	TextCtrl_String *Borders_BorderName[2];
	wxBoxSizer *Borders_Holder_BorderRessourceID;
	wxStaticText *Borders_Text_BorderRessourceID;
	TextCtrl_Long *Borders_BorderRessourceID;
	wxBoxSizer *Borders_Holder_BorderUnknown3;
	wxStaticText *Borders_Text_BorderUnknown3;
	TextCtrl_Float *Borders_BorderUnknown3;
	wxBoxSizer *Borders_Holder_BorderUnknown4;
	wxStaticText *Borders_Text_BorderUnknown4;
	TextCtrl_Long *Borders_BorderUnknown4;
	wxBoxSizer *Borders_Holder_BorderColors;
	wxGridSizer *Borders_Grid_BorderColors;
	wxStaticText *Borders_Text_BorderColors;
	array<TextCtrl_UByte*, 3> Borders_BorderColors;
	wxBoxSizer *Borders_Holder_BorderUnknown5;
	wxGridSizer *Borders_Grid_BorderUnknown5;
	wxStaticText *Borders_Text_BorderUnknown5;
	array<TextCtrl_Byte*, 5> Borders_BorderUnknown5;
	wxBoxSizer *Borders_Holder_BorderUnknown6;
	wxStaticText *Borders_Text_BorderUnknown6;
	TextCtrl_Float *Borders_BorderUnknown6;
	wxBoxSizer *Borders_Holder_BorderFrameID;
	wxStaticText *Borders_Text_BorderFrameID;
	TextCtrl_Short *Borders_BorderFrameID;
	wxBoxSizer *Borders_Holder_BorderFlag1;
	wxStaticText *Borders_Text_BorderFlag1;
	TextCtrl_Short *Borders_BorderFlag1;
	wxBoxSizer *Borders_Holder_BorderFlag2;
	wxStaticText *Borders_Text_BorderFlag2;
	TextCtrl_Short *Borders_BorderFlag2;
	wxBoxSizer *Borders_Holder_BorderFrameCount;
	wxStaticText *Borders_Text_BorderFrameCount;
	TextCtrl_Short *Borders_BorderFrameCount;
	wxBoxSizer *Borders_Holder_BorderUnknown8;
	wxStaticText *Borders_Text_BorderUnknown8;
	TextCtrl_Short *Borders_BorderUnknown8;
	wxBoxSizer *Borders_Holder_BorderTerrain;
	wxStaticText *Borders_Text_BorderTerrain;
	TextCtrl_Short *Borders_BorderTerrain;
	ComboBox_Plus1 *Borders_ComboBox_BorderTerrain;
	wxBoxSizer *Borders_Holder_BorderUnknown1;
	wxStaticText *Borders_Text_BorderUnknown1;
	TextCtrl_Short *Borders_BorderUnknown1;

	wxGridSizer *General_Grid_Variables;
	wxGridSizer *General_Grid_Variables2;
	wxStaticBoxSizer *General_Holder_Variables1;
	wxStaticBoxSizer *General_Holder_Variables2;
	wxBoxSizer *General_Holder_SUnknown7;
	wxStaticText *General_Text_SUnknown7;
	TextCtrl_Byte *General_SUnknown7;
	wxBoxSizer *General_Holder_SUnknown8;
	wxStaticText *General_Text_SUnknown8;
	TextCtrl_Byte *General_SUnknown8;
	wxBoxSizer *General_Holder_SUnknown2;
	wxStaticText *General_Text_SUnknown2;
	TextCtrl_Long *General_SUnknown2;
	wxBoxSizer *General_Holder_SUnknown3;
	wxStaticText *General_Text_SUnknown3;
	TextCtrl_Long *General_SUnknown3;
	wxBoxSizer *General_Holder_SUnknown4;
	wxStaticText *General_Text_SUnknown4;
	TextCtrl_Long *General_SUnknown4;
	wxBoxSizer *General_Holder_SUnknown5;
	wxStaticText *General_Text_SUnknown5;
	TextCtrl_Long *General_SUnknown5;
	array<wxBoxSizer*, 8> General_Holder_TTUnknown;
	array<wxStaticText*, 8> General_Text_TTUnknown;
	array<TextCtrl_Long*, 8> General_TTUnknown;

	//wxBoxSizer *General_Holder_RenderPlusUnknown;
	//wxBoxSizer *General_Holder_RenderPlusUnknownTop;
	//wxStaticText *General_Text_TechTree;
	//wxTextCtrl *General_SomethingPicker;
	//wxButton *General_SomethingNext;
	//wxButton *General_SomethingPrev;
	//wxStaticText *General_SomethingSize;
	//wxGridSizer *General_Grid_TechTree;
	//array<TextCtrl_Long*, 128> General_Something;

	wxBoxSizer *Unknown_Main;
	wxBoxSizer *Unknown_Area;
	wxScrolledWindow *Unknown_Scroller;
	wxBoxSizer *Unknown_ScrollerWindows;
	wxBoxSizer *Unknown_ScrollerWindowsSpace;

	wxGridSizer *Unknown_Grid_UnknownPointer;
	wxBoxSizer *Unknown_Holder_UnknownPointer;
	wxStaticText *Unknown_Text_UnknownPointer;
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
	wxBoxSizer *Unknowns_Holder_UnknownLevel;
	wxStaticText *Unknowns_Text_UnknownLevel;
	TextCtrl_Long *Unknowns_UnknownLevel;
	wxGridSizer *Unknowns_Grid_Unknown1;
	array<wxBoxSizer*, 9> Unknowns_Holder_Unknown1;
	array<wxStaticText*, 9> Unknowns_Text_Unknown1;
	array<TextCtrl_Long*, 9> Unknowns_Unknown1;
	wxBoxSizer *Unknowns_Space_Pointer1;
	wxBoxSizer *Unknowns_Holder_Pointer1;
	wxStaticText *Unknowns_Text_Pointer1;
	TextCtrl_Long *Unknowns_Pointer1;
	wxBoxSizer *Unknowns_Space_Pointer2;
	wxBoxSizer *Unknowns_Holder_Pointer2;
	wxStaticText *Unknowns_Text_Pointer2;
	TextCtrl_Long *Unknowns_Pointer2;
	wxBoxSizer *Unknowns_Space_Pointer3;
	wxBoxSizer *Unknowns_Holder_Pointer3;
	wxStaticText *Unknowns_Text_Pointer3;
	TextCtrl_Long *Unknowns_Pointer3;
	wxGridSizer *Unknowns_Grid_Unknown2;
	array<wxBoxSizer*, 2> Unknowns_Holder_Unknown2;
	array<wxStaticText*, 2> Unknowns_Text_Unknown2;
	array<TextCtrl_Long*, 2> Unknowns_Unknown2;

	wxStaticBoxSizer *UnknownFirstSubData;
	wxBoxSizer *UnknownFirstSubData_ListArea;
	wxBoxSizer *UnknownFirstSubData_DataArea;
	wxTextCtrl *UnknownFirstSubData_Search;
	wxTextCtrl *UnknownFirstSubData_Search_R;
	wxListBox *UnknownFirstSubData_List;
	wxGridSizer *UnknownFirstSubData_Buttons;
	wxButton *UnknownFirstSubData_Add;
	wxButton *UnknownFirstSubData_Insert;
	wxButton *UnknownFirstSubData_Delete;
	wxButton *UnknownFirstSubData_Copy;
	wxButton *UnknownFirstSubData_Paste;
	wxButton *UnknownFirstSubData_PasteInsert;
	wxButton *UnknownFirstSubData_CopyToMaps;

	wxGridSizer *UnknownFirstSubData_Grid_Unknown1;

	wxBoxSizer *UnknownFirstSubData_Holder_Unknown1;
	wxStaticText *UnknownFirstSubData_Text_Unknown1;
	TextCtrl_Long *UnknownFirstSubData_Unknown1;
	wxBoxSizer *UnknownFirstSubData_Holder_BaseTerrain;
	wxStaticText *UnknownFirstSubData_Text_BaseTerrain;
	TextCtrl_Long *UnknownFirstSubData_BaseTerrain;
	wxBoxSizer *UnknownFirstSubData_Holder_SpacingBetweenPlayers;
	wxStaticText *UnknownFirstSubData_Text_SpacingBetweenPlayers;
	TextCtrl_Long *UnknownFirstSubData_SpacingBetweenPlayers;
	wxBoxSizer *UnknownFirstSubData_Holder_Unknown4;
	wxStaticText *UnknownFirstSubData_Text_Unknown4;
	TextCtrl_Long *UnknownFirstSubData_Unknown4;

	wxBoxSizer *UnknownFirstSubData_Holder_Unknown5;
	wxGridSizer *UnknownFirstSubData_Grid_Unknown5;
	wxStaticText *UnknownFirstSubData_Text_Unknown5;
	array<TextCtrl_Byte*, 4> UnknownFirstSubData_Unknown5;

	wxBoxSizer *UnknownFirstSubData_Holder_Unknown6;
	wxStaticText *UnknownFirstSubData_Text_Unknown6;
	TextCtrl_Long *UnknownFirstSubData_Unknown6;
	wxBoxSizer *UnknownFirstSubData_Holder_Unknown7;
	wxStaticText *UnknownFirstSubData_Text_Unknown7;
	TextCtrl_Long *UnknownFirstSubData_Unknown7;

	wxBoxSizer *UnknownFirstSubData_Holder_Unknown8;
	wxGridSizer *UnknownFirstSubData_Grid_Unknown8;
	wxStaticText *UnknownFirstSubData_Text_Unknown8;
	array<TextCtrl_Byte*, 4> UnknownFirstSubData_Unknown8;

	wxBoxSizer *UnknownFirstSubData_Holder_StartAreaRadius;
	wxStaticText *UnknownFirstSubData_Text_StartAreaRadius;
	TextCtrl_Long *UnknownFirstSubData_StartAreaRadius;
	wxBoxSizer *UnknownFirstSubData_Holder_Unknown10;
	wxStaticText *UnknownFirstSubData_Text_Unknown10;
	TextCtrl_Long *UnknownFirstSubData_Unknown10;
	wxBoxSizer *UnknownFirstSubData_Holder_Unknown11;
	wxStaticText *UnknownFirstSubData_Text_Unknown11;
	TextCtrl_Long *UnknownFirstSubData_Unknown11;

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

	wxGridSizer *RMSTerrain_Grid_Unknown1;
	array<wxBoxSizer*, 6> RMSTerrain_Holder_Unknown1;
	array<wxStaticText*, 6> RMSTerrain_Text_Unknown1;
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

	wxGridSizer *RMSUnit_Grid_Unknown1;
	wxBoxSizer *RMSUnit_Holder_Unit;
	wxStaticText *RMSUnit_Text_Unit;
	TextCtrl_Long *RMSUnit_Unit;
	wxBoxSizer *RMSUnit_Holder_HostTerrain;
	wxStaticText *RMSUnit_Text_HostTerrain;
	TextCtrl_Long *RMSUnit_HostTerrain;
	wxBoxSizer *RMSUnit_Holder_Unknown3;
	wxGridSizer *RMSUnit_Grid_Unknown3;
	wxStaticText *RMSUnit_Text_Unknown3;
	array<TextCtrl_Byte*, 4> RMSUnit_Unknown3;
	wxBoxSizer *RMSUnit_Holder_ObjectsPerPlayer;
	wxStaticText *RMSUnit_Text_ObjectsPerPlayer;
	TextCtrl_Long *RMSUnit_ObjectsPerPlayer;
	wxBoxSizer *RMSUnit_Holder_Unknown5;
	wxStaticText *RMSUnit_Text_Unknown5;
	TextCtrl_Long *RMSUnit_Unknown5;
	wxBoxSizer *RMSUnit_Holder_GroupsPerPlayer;
	wxStaticText *RMSUnit_Text_GroupsPerPlayer;
	TextCtrl_Long *RMSUnit_GroupsPerPlayer;
	wxBoxSizer *RMSUnit_Holder_Unknown7;
	wxStaticText *RMSUnit_Text_Unknown7;
	TextCtrl_Long *RMSUnit_Unknown7;
	wxBoxSizer *RMSUnit_Holder_OwnAtStart;
	wxStaticText *RMSUnit_Text_OwnAtStart;
	TextCtrl_Long *RMSUnit_OwnAtStart;
	wxBoxSizer *RMSUnit_Holder_SetPlaceForAllPlayers;
	wxStaticText *RMSUnit_Text_SetPlaceForAllPlayers;
	TextCtrl_Long *RMSUnit_SetPlaceForAllPlayers;
	wxBoxSizer *RMSUnit_Holder_MinDistanceToPlayers;
	wxStaticText *RMSUnit_Text_MinDistanceToPlayers;
	TextCtrl_Long *RMSUnit_MinDistanceToPlayers;
	wxBoxSizer *RMSUnit_Holder_MaxDistanceToPlayers;
	wxStaticText *RMSUnit_Text_MaxDistanceToPlayers;
	TextCtrl_Long *RMSUnit_MaxDistanceToPlayers;

//	Researchs user interface

	wxBoxSizer *Research_Main;
	wxBoxSizer *Research_ListArea;
	wxGridSizer *Research_Research_Buttons;
	wxBoxSizer *Research_DataArea;
	wxScrolledWindow *Research_Scroller;
	wxBoxSizer *Research_ScrollerWindows;
	wxBoxSizer *Research_ScrollerWindowsSpace;
	wxGridSizer *Research_Grid_MiscArea1;
	wxBoxSizer *Research_Holder_LangDLLArea;
	wxBoxSizer *Research_Holder_Misc2;
	wxBoxSizer *Research_Holder_PointerArea;
	wxBoxSizer *Research_Holder_Names;

	wxStaticBoxSizer *Research_Research;
	wxBoxSizer *Research_Research_Searches[2];
	wxTextCtrl *Research_Research_Search;
	wxTextCtrl *Research_Research_Search_R;
	wxOwnerDrawnComboBox *Research_Research_SearchFilters[2];
	wxCheckBox *Research_Research_UseAnd[2];
	wxListBox *Research_Research_List;
	wxButton *Research_Add;
	wxButton *Research_Insert;
	wxButton *Research_Delete;
	wxButton *Research_Copy;
	wxButton *Research_Paste;
	wxButton *Research_PasteInsert;

	wxBoxSizer *Research_Holder_RequiredTechArea;
	wxGridSizer *Research_Holder_RequiredTechs;
	wxStaticText *Research_Text_RequiredTechArea;
	TextCtrl_Short *Research_RequiredTechs[6];
	ComboBox_Plus1 *Research_ComboBox_RequiredTechs[6];
	wxBoxSizer *Research_Holder_RequiredTechCount;
	wxStaticText *Research_Text_RequiredTechCount;
	TextCtrl_Short *Research_RequiredTechCount;

	wxStaticBoxSizer *Research_Holder_CostHeader;
	wxBoxSizer *Research_Holder_CostType;
	wxBoxSizer *Research_Holder_CostAmount;
	wxBoxSizer *Research_Holder_CostUsed;
	wxStaticText *Research_Text_Resources;
	wxGridSizer *Research_ResourceGrid;
	TextCtrl_Short *Research_Resources[3];
	ComboBox_Plus1 *Research_ComboBox_Resources[3];
	wxStaticText *Research_Text_Amount;
	TextCtrl_Short *Research_Amount[3];
	wxStaticText *Research_Text_Used;
	TextCtrl_Byte *Research_Used[3];
	CheckBox_2State *Research_CheckBox_Used[3];

	wxBoxSizer *Research_Holder_Civ;
	wxStaticText *Research_Text_Civ;
	TextCtrl_Short *Research_Civ;
	ComboBox_Plus1 *Research_ComboBox_Civ;

	wxBoxSizer *Research_Holder_FullTechMode;
	wxStaticText *Research_Text_FullTechMode;
	TextCtrl_Short *Research_FullTechMode;
	CheckBox_2State *Research_CheckBox_FullTechMode;

	wxBoxSizer *Research_Holder_ResearchLocation;
	wxStaticText *Research_Text_ResearchLocation;
	TextCtrl_Short *Research_ResearchLocation;
	ComboBox_Plus1 *Research_ComboBox_ResearchLocation;

	wxBoxSizer *Research_Holder_LangDLLName;
	wxStaticText *Research_Text_LangDLLName;
	TextCtrl_UShort *Research_LangDLLName;
	TextCtrl_DLL *Research_DLL_LangDLLName;

	wxBoxSizer *Research_Holder_LangDLLDescription;
	wxStaticText *Research_Text_LangDLLDescription;
	TextCtrl_UShort *Research_LangDLLDescription;
	TextCtrl_DLL *Research_DLL_LangDLLDescription;

	wxBoxSizer *Research_Holder_ResearchTime;
	wxStaticText *Research_Text_ResearchTime;
	TextCtrl_Short *Research_ResearchTime;

	wxBoxSizer *Research_Holder_TechID;
	wxStaticText *Research_Text_TechID;
	TextCtrl_Short *Research_TechID;
	ComboBox_Plus1 *Research_ComboBox_TechID;

	wxBoxSizer *Research_Holder_Type;
	wxStaticText *Research_Text_Type;
	TextCtrl_Short *Research_Type;

	wxBoxSizer *Research_Holder_IconID;
	wxStaticText *Research_Text_IconID;
	TextCtrl_Short *Research_IconID;

	wxBoxSizer *Research_Holder_ButtonID;
	wxStaticText *Research_Text_ButtonID;
	TextCtrl_Byte *Research_ButtonID;

	wxBoxSizer *Research_Holder_LanguageDLLHelp;
	wxStaticText *Research_Text_LanguageDLLHelp;
	TextCtrl_Long *Research_LanguageDLLHelp;
	wxBoxSizer *Research_Holder_LanguageDLLName2;
	wxStaticText *Research_Text_LanguageDLLName2;
	TextCtrl_Long *Research_LanguageDLLName2;
	wxBoxSizer *Research_Holder_Unknown1;
	wxStaticText *Research_Text_Unknown1;
	TextCtrl_Long *Research_Unknown1;
	TextCtrl_DLL *Research_DLL_LanguageDLLHelp;
	TextCtrl_DLL *Research_DLL_LanguageDLLName2;
	wxBoxSizer *Research_Holder_LanguageDLLConverter[2];
	wxStaticText *Research_Text_LanguageDLLConverter[2];
	wxTextCtrl *Research_LanguageDLLConverter[2];

	wxBoxSizer *Research_Holder_Name[2];
	wxStaticText *Research_Text_Name[2];
	TextCtrl_String *Research_Name[2];

//	Techs user interface

	wxBoxSizer *Techs_Main;
	wxBoxSizer *Techs_ListArea;
	wxGridSizer *Techs_Techs_Buttons;
	wxBoxSizer *Effects_ListArea;
	wxGridSizer *Techs_Effects_Buttons;
	wxBoxSizer *Effects_DataAreaProperties;
	wxCheckBox *Effects_NeverHide;
	wxBoxSizer *Effects_Holder_DataA;
	wxBoxSizer *Effects_Holder_DataB;
	wxBoxSizer *Effects_Holder_DataC;
	wxBoxSizer *Effects_Holder_DataD;
	wxBoxSizer *Effects_Holder_DataE;	// for attack/armor amount
	wxBoxSizer *Effects_Holder_DataF;	// for attack/armor class
	wxBoxSizer *Effects_Holder_A;
	wxBoxSizer *Effects_Holder_B;
	wxBoxSizer *Effects_Holder_C;
	wxBoxSizer *Effects_Holder_D;
	wxBoxSizer *Effects_Holder_E;	// for attack/armor amount
	wxBoxSizer *Effects_Holder_F;	// for attack/armor class

	wxStaticText *Effects_Text_E;
	wxTextCtrl *Effects_E;	// amount
	wxStaticText *Effects_Info_E;
	wxStaticText *Effects_Text_F;
	TextCtrl_Short *Effects_F;	// class
	wxStaticText *Effects_Info_F;

	wxStaticBoxSizer *Techs_Techs;
	wxTextCtrl *Techs_Techs_Search;
	wxTextCtrl *Techs_Techs_Search_R;
	wxListBox *Techs_Techs_List;
	wxButton *Techs_Techs_Rename;
	wxButton *Techs_Techs_Restore;
	wxButton *Techs_Techs_Add;
	wxButton *Techs_Techs_Insert;
	wxButton *Techs_Techs_Delete;
	wxButton *Techs_Techs_Copy;
	wxButton *Techs_Techs_Paste;
	wxButton *Techs_Techs_PasteInsert;

	wxStaticBoxSizer *Techs_AllEffects;
	wxBoxSizer *Techs_AllEffects_Searches[2];
	wxTextCtrl *Techs_AllEffects_Search;
	wxTextCtrl *Techs_AllEffects_Search_R;
	wxCheckBox *Techs_AllEffects_UseAnd[2];
	wxListBox *Techs_AllEffects_List;
	wxBoxSizer *Techs_AllEffects_Buttons;
	wxButton *Techs_AllEffects_Load;
	wxButton *Techs_AllEffects_Clear;

	wxBoxSizer *Techs_Holder_Name;
	wxStaticText *Techs_Text_Name;
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

	wxBoxSizer *Effects_Holder_Type;
	wxBoxSizer *Effects_Holder_Type2;
	wxStaticText *Effects_Text_Type;
	ComboBox_EffectType *Effects_ComboBox_Type;
	TextCtrl_Byte *Effects_Type;
	wxStaticBoxSizer *Effects_Holder_Data;
	wxStaticText *Effects_Text_A;
	TextCtrl_Short *Effects_A;
	wxBoxSizer *Effects_ComboBox_A;	// Space reserver, never used.
	ComboBox_Plus1 *Effects_ComboBox_UnitsA;	// for Effects 0, 2, 3, 4, 5
	ComboBox_Plus1 *Effects_ComboBox_ResourcesA;	// for Effects 1, 6
	ComboBox_Plus1 *Effects_ComboBox_ResearchsA;	// for Effects 101, 103
	wxStaticText *Effects_Info_A;
	wxStaticText *Effects_Text_B;
	TextCtrl_Short *Effects_B;
	wxBoxSizer *Effects_ComboBox_B;	// Space reserver, never used.
	CheckBox_2State *Effects_CheckBox_ModeB;	// for Effects 1, 2
	//ComboBox_Plus1 *Units_ComboBox_Class[2];	// for Effects 0, 4, 5
	ComboBox_Plus1 *Effects_ComboBox_UnitsB;	// for Effects 3
	ComboBox_Plus1 *Effects_ComboBox_ResourcesB;	// for Effects 101
	wxStaticText *Effects_Info_B;
	wxStaticText *Effects_Text_C;
	TextCtrl_Short *Effects_C;
	wxBoxSizer *Effects_ComboBox_C;	// Space reserver, never used.
	CheckBox_2State *Effects_CheckBox_ModeC;	// for Effects 101, 103
	ComboBox_Plus1 *Effects_ComboBox_AttributesC;	// for Effects 0, 4, 5
	wxStaticText *Effects_Info_C;
	wxStaticText *Effects_Text_D;
	TextCtrl_Float *Effects_D;
	wxBoxSizer *Effects_ComboBox_D;	// Space reserver, never used.
	ComboBox_Plus1 *Effects_ComboBox_ResearchsD;	// for Effects 102
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
	wxStaticText *Civs_Text_One;
	wxBoxSizer *Civs_Holder_One;
	TextCtrl_Byte *Civs_One;
	wxBoxSizer *Civs_Holder_Name[2];
	wxStaticText *Civs_Text_Name[2];
	TextCtrl_String *Civs_Name[2];
	wxBoxSizer *Civs_Holder_SUnknown1;
	wxStaticText *Civs_Text_SUnknown1;
	TextCtrl_Short *Civs_SUnknown1[4];
	wxBoxSizer *Civs_Holder_TechTree;
	wxStaticText *Civs_Text_TechTree;
	TextCtrl_Short *Civs_TechTree;
	ComboBox_Plus1 *Civs_ComboBox_TechTree;
	wxBoxSizer *Civs_Holder_TeamBonus;
	wxStaticText *Civs_Text_TeamBonus;
	TextCtrl_Short *Civs_TeamBonus;
	ComboBox_Plus1 *Civs_ComboBox_TeamBonus;
	wxBoxSizer *Civs_Holder_GraphicSet;
	wxStaticText *Civs_Text_GraphicSet;
	TextCtrl_Byte *Civs_GraphicSet;
	wxBoxSizer *Civs_Holder_Resources;
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
	wxBoxSizer *Civs_Holder_ResourceValue;
	wxStaticText *Civs_Text_ResourceValue;
	TextCtrl_Float *Civs_ResourceValue;
	wxHyperlinkCtrl *Civs_Holder_Resources_Link;

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
	wxOwnerDrawnComboBox *Units_ComboBox_Type;
	TextCtrl_Short *Units_ID1;
	TextCtrl_UShort *Units_LanguageDLLName;
	TextCtrl_DLL *Units_DLL_LanguageName;
	TextCtrl_UShort *Units_LanguageDLLCreation;
	TextCtrl_DLL *Units_DLL_LanguageCreation;
	TextCtrl_Short *Units_Class;
	ComboBox_Plus1 *Units_ComboBox_Class[3];
	TextCtrl_Short *Units_StandingGraphic[2];
	ComboBox_Plus1 *Units_ComboBox_StandingGraphic[2];
	TextCtrl_Short *Units_DyingGraphic[2];
	ComboBox_Plus1 *Units_ComboBox_DyingGraphic[2];
	TextCtrl_Byte *Units_DeathMode;
	CheckBox_2State *Units_CheckBox_DeathMode;
	TextCtrl_Short *Units_HitPoints;
	TextCtrl_Float *Units_LineOfSight;
	TextCtrl_Byte *Units_GarrisonCapacity;
	TextCtrl_Float *Units_SizeRadius[2];
	TextCtrl_Float *Units_HPBarHeight1;
	TextCtrl_Short *Units_TrainSound[2];
	ComboBox_Plus1 *Units_ComboBox_TrainSound[2];
	TextCtrl_Short *Units_DeadUnitID;
	ComboBox_Plus1 *Units_ComboBox_DeadUnitID;
	TextCtrl_Byte *Units_PlacementMode;
	TextCtrl_Byte *Units_AirMode;
	CheckBox_2State *Units_CheckBox_AirMode;
	TextCtrl_Short *Units_IconID;
	TextCtrl_Byte *Units_HideInEditor;
	CheckBox_2State *Units_CheckBox_HideInEditor;
	TextCtrl_Short *Units_Unknown1;
	TextCtrl_Short *Units_Enabled;
	CheckBox_2State *Units_CheckBox_Enabled;
	TextCtrl_Short *Units_PlacementBypassTerrain[2];
	ComboBox_Plus1 *Units_ComboBox_PlacementBypassTerrain[2];
	TextCtrl_Short *Units_PlacementTerrain[2];
	ComboBox_Plus1 *Units_ComboBox_PlacementTerrain[2];
	TextCtrl_Float *Units_EditorRadius[2];
	TextCtrl_Byte *Units_BuildingMode;
	TextCtrl_Byte *Units_VisibleInFog;
	wxStaticText *Units_Text_VisibleInFog;
	TextCtrl_Short *Units_TerrainRestriction;
	ComboBox_Plus1 *Units_ComboBox_TerrainRestriction;
	TextCtrl_Byte *Units_FlyMode;
	CheckBox_2State *Units_CheckBox_FlyMode;
	TextCtrl_Short *Units_ResourceCapacity;
	TextCtrl_Float *Units_ResourceDecay;
	TextCtrl_Byte *Units_BlastType;
	TextCtrl_Byte *Units_Unknown2;
	TextCtrl_Byte *Units_InteractionMode;
	TextCtrl_Byte *Units_MinimapMode;
	TextCtrl_Short *Units_CommandAttribute;
	array<TextCtrl_Byte*, 4> Units_Unknown3;
	TextCtrl_Long *Units_LanguageDLLHelp;
	TextCtrl_DLL *Units_DLL_LanguageHelp;
	wxTextCtrl *Units_LanguageDLLConverter[2];
	TextCtrl_Long *Units_LanguageDLLHotKeyText;
	TextCtrl_DLL *Units_DLL_LanguageHKText;
	TextCtrl_Long *Units_HotKey;
	TextCtrl_DLL *Units_DLL_HotKey4;
	TextCtrl_Byte *Units_Unselectable;
	CheckBox_2State *Units_CheckBox_Unselectable;
	TextCtrl_Byte *Units_Unknown6;
	TextCtrl_Byte *Units_Unknown7;
	TextCtrl_Byte *Units_Unknown8;
	TextCtrl_Byte *Units_SelectionMask;
	TextCtrl_Byte *Units_SelectionShapeType;
	TextCtrl_Byte *Units_SelectionShape;
	TextCtrl_Byte *Units_Attribute;
	TextCtrl_Byte *Units_Civ;
	ComboBox_Plus1 *Units_ComboBox_Civ;
	TextCtrl_Short *Units_Unknown9;
	TextCtrl_Byte *Units_SelectionEffect;
	TextCtrl_Byte *Units_EditorSelectionColour;
	wxBoxSizer *Units_SelectionRadiusBox;
	TextCtrl_Float *Units_SelectionRadius[2];
	TextCtrl_Float *Units_HPBarHeight2;
	TextCtrl_Short *ResourceStorage_Type[3];
	ComboBox_Plus1 *ResourceStorage_ComboBox_Type[3];
	TextCtrl_Float *ResourceStorage_Amount[3];
	TextCtrl_Byte *ResourceStorage_Enabled[3];
	TextCtrl_Short *Units_SelectionSound;
	ComboBox_Plus1 *Units_ComboBox_SelectionSound;
	TextCtrl_Short *Units_DyingSound;
	ComboBox_Plus1 *Units_ComboBox_DyingSound;
	TextCtrl_Short *Units_AttackMode;
	TextCtrl_String *Units_Name;
	TextCtrl_String *Units_Name2;
	TextCtrl_Short *Units_Unitline;
	ComboBox_Plus1 *Units_ComboBox_Unitline;
	TextCtrl_Byte *Units_MinTechLevel;
	TextCtrl_Short *Units_ID2;
	TextCtrl_Short *Units_ID3;

//	Type 20+

	TextCtrl_Float *Units_Speed;

//	Type 30+

	TextCtrl_Short *Units_WalkingGraphic[2];
	ComboBox_Plus1 *Units_ComboBox_WalkingGraphic[2];
	TextCtrl_Float *Units_RotationSpeed;
	TextCtrl_Byte *Units_Unknown11;
	TextCtrl_Short *Units_TrackingUnit;
	ComboBox_Plus1 *Units_ComboBox_TrackingUnit;
	TextCtrl_Byte *Units_TrackingUnitUsed;
	TextCtrl_Float *Units_TrackingUnitDensity;
	TextCtrl_Float *Units_Unknown12;
	TextCtrl_Byte *Units_Unknown16;
	array<TextCtrl_Byte*, 16> Units_Unknown16B;

//	Type 40+

	TextCtrl_Short *Units_SheepConversion;
	CheckBox_ZeroIsYes *Units_CheckBox_SheepConversion;
	TextCtrl_Float *Units_SearchRadius;
	TextCtrl_Float *Units_WorkRate;
	TextCtrl_Short *Units_DropSite[2];
	ComboBox_Plus1 *Units_ComboBox_DropSite[2];
	TextCtrl_Byte *Units_VillagerMode;
	TextCtrl_Short *Units_AttackSound;
	ComboBox_Plus1 *Units_ComboBox_AttackSound;
	TextCtrl_Short *Units_MoveSound;
	ComboBox_Plus1 *Units_ComboBox_MoveSound;
	TextCtrl_Byte *Units_AnimalMode;
	CheckBox_2State *Units_CheckBox_AnimalMode;
	TextCtrl_Byte *Units_Exists;

//	Type 60+

	TextCtrl_Byte *Units_Unknown20[2];
	TextCtrl_Short *Units_Unknown21;
	TextCtrl_Float *Units_MaxRange;
	TextCtrl_Float *Units_BlastRadius;
	TextCtrl_Float *Units_ReloadTime1;
	TextCtrl_Short *Units_ProjectileUnitID;
	ComboBox_Plus1 *Units_ComboBox_ProjectileUnitID;
	TextCtrl_Short *Units_AccuracyPercent;
	TextCtrl_Byte *Units_TowerMode;
	CheckBox_2State *Units_CheckBox_TowerMode;
	TextCtrl_Short *Units_Delay;
	TextCtrl_Float *Units_GraphicDisplacement[3];
	TextCtrl_Byte *Units_BlastLevel;
	TextCtrl_Float *Units_MinRange;
	TextCtrl_Float *Units_GarrisonRecoveryRate;
	TextCtrl_Short *Units_AttackGraphic;
	ComboBox_Plus1 *Units_ComboBox_AttackGraphic;
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
	ComboBox_Plus1 *Units_ComboBox_CostType[3];
	TextCtrl_Short *Units_CostAmount[3];
	TextCtrl_Short *Units_CostUsed[3];
	CheckBox_2State *Units_CheckBox_CostUsed[3];
	TextCtrl_Short *Units_TrainTime;
	TextCtrl_Short *Units_TrainLocationID;
	ComboBox_Plus1 *Units_ComboBox_TrainLocationID;
	TextCtrl_Byte *Units_ButtonID;
	TextCtrl_Long *Units_Unknown26;
	TextCtrl_Long *Units_Unknown27;
	TextCtrl_Byte *Units_MissileGraphicDelay;
	TextCtrl_Byte *Units_HeroMode;
	CheckBox_2State *Units_CheckBox_HeroMode;
	TextCtrl_Short *Units_GarrisonGraphic[2];
	ComboBox_Plus1 *Units_ComboBox_GarrisonGraphic[2];
	TextCtrl_Float *Units_AttackMissileDuplicationAmount1;
	TextCtrl_Byte *Units_AttackMissileDuplicationAmount2;
	TextCtrl_Float *Units_AttackMissileDuplicationSpawning[3];
	TextCtrl_Long *Units_AttackMissileDuplicationUnit;
	ComboBox_Plus1 *Units_ComboBox_AttackMissileDuplicationUnit;
	TextCtrl_Long *Units_AttackMissileDuplicationGraphic;
	ComboBox_Plus1 *Units_ComboBox_AttackMissileDuplicationGraphic;
	TextCtrl_Byte *Units_Unknown29;
	TextCtrl_Short *Units_DisplayedPierceArmour;

//	Type 80

	TextCtrl_Short *Units_ConstructionGraphicID;
	ComboBox_Plus1 *Units_ComboBox_ConstructionGraphicID;
	TextCtrl_Short *Units_SnowGraphicID;
	ComboBox_Plus1 *Units_ComboBox_SnowGraphicID;
	TextCtrl_Short *Units_AdjacentMode;
	CheckBox_2State *Units_CheckBox_AdjacentMode;
	TextCtrl_Byte *Units_Unknown31;
	TextCtrl_Byte *Units_Unknown31b;
	CheckBox_2State *Units_CheckBox_Unknown31b;
	TextCtrl_Short *Units_StackUnitID;
	ComboBox_Plus1 *Units_ComboBox_StackUnitID;
	TextCtrl_Short *Units_TerrainID;
	ComboBox_Plus1 *Units_ComboBox_TerrainID;
	TextCtrl_Short *Units_Unknown32;
	TextCtrl_Short *Units_ResearchID;
	ComboBox_Plus1 *Units_ComboBox_ResearchID;
	TextCtrl_Byte *Units_Unknown33;
	TextCtrl_Short *Units_AnnexUnit[4];
	ComboBox_Plus1 *Units_ComboBox_AnnexUnit[4];
	TextCtrl_Float *Units_AnnexUnitMisplacement[4][2];
	TextCtrl_Short *Units_HeadUnit;
	ComboBox_Plus1 *Units_ComboBox_HeadUnit;
	TextCtrl_Short *Units_TransformUnit;
	ComboBox_Plus1 *Units_ComboBox_TransformUnit;
	TextCtrl_Short *Units_Unknown34;
	TextCtrl_Short *Units_ConstructionSound;
	ComboBox_Plus1 *Units_ComboBox_ConstructionSound;
	TextCtrl_Byte *Units_GarrisonType;
	ComboBox_Plus1 *Units_ComboBox_GarrisonType;
	TextCtrl_Float *Units_GarrisonHealRate;
	TextCtrl_Long *Units_Unknown35;
	array<TextCtrl_Byte*, 8> Units_AlfaThingy;

//	Data Container Names
//	Type 10+

	wxStaticText *Units_Text_Type;
	wxStaticText *Units_Text_ID1;
	wxStaticText *Units_Text_LanguageDLLName;
	wxStaticText *Units_Text_LanguageDLLCreation;
	wxStaticText *Units_Text_Class;
	wxStaticText *Units_Text_StandingGraphic;
	wxStaticText *Units_Text_DyingGraphic;
	wxStaticText *Units_Text_HitPoints;
	wxStaticText *Units_Text_LineOfSight;
	wxStaticText *Units_Text_GarrisonCapacity;
	wxStaticText *Units_Text_SizeRadius;
	wxStaticText *Units_Text_HPBarHeight1;
	wxStaticText *Units_Text_TrainSound;
	wxStaticText *Units_Text_DeadUnitID;
	wxStaticText *Units_Text_PlacementMode;
	wxStaticText *Units_Text_IconID;
	wxStaticText *Units_Text_Unknown1;
	wxStaticText *Units_Text_PlacementBypassTerrain;
	wxStaticText *Units_Text_PlacementTerrain;
	wxStaticText *Units_Text_EditorRadius;
	wxStaticText *Units_Text_BuildingMode;
	wxStaticText *Units_Text_TerrainRestriction;
	wxStaticText *Units_Text_ResourceCapacity;
	wxStaticText *Units_Text_ResourceDecay;
	wxStaticText *Units_Text_BlastType;
	wxStaticText *Units_Text_Unknown2;
	wxStaticText *Units_Text_InteractionMode;
	wxStaticText *Units_Text_MinimapMode;
	wxStaticText *Units_Text_CommandAttribute;
	wxStaticText *Units_Text_Unknown3;
	wxStaticText *Units_Text_LanguageDLLHelp;
	wxStaticText *Units_Text_LanguageDLLConverter[2];
	wxStaticText *Units_Text_LanguageDLLHotKeyText;
	wxStaticText *Units_Text_HotKey;
	wxStaticText *Units_Text_Unknown6;
	wxStaticText *Units_Text_Unknown7;
	wxStaticText *Units_Text_Unknown8;
	wxStaticText *Units_Text_SelectionMask;
	wxStaticText *Units_Text_SelectionShapeType;
	wxStaticText *Units_Text_SelectionShape;
	wxStaticText *Units_Text_Attribute;
	wxStaticText *Units_Text_Civ;
	wxStaticText *Units_Text_Unknown9;
	wxStaticText *Units_Text_SelectionEffect;
	wxStaticText *Units_Text_EditorSelectionColour;
	wxStaticText *Units_Text_SelectionRadius;
	wxStaticText *Units_Text_HPBarHeight2;
	wxStaticText *ResourceStorage_Text_Type;
	wxStaticText *ResourceStorage_Text_Amount;
	wxStaticText *ResourceStorage_Text_Enabled;
	wxStaticText *Units_Text_SelectionSound;
	wxStaticText *Units_Text_DyingSound;
	wxStaticText *Units_Text_AttackMode;
	wxStaticText *Units_Text_Name;
	wxStaticText *Units_Text_Name2;
	wxStaticText *Units_Text_Unitline;
	wxStaticText *Units_Text_MinTechLevel;
	wxStaticText *Units_Text_ID2;
	wxStaticText *Units_Text_ID3;

//	Type 20+

	wxStaticText *Units_Text_Speed;

//	Type 30+

	wxStaticText *Units_Text_WalkingGraphic;
	wxStaticText *Units_Text_RotationSpeed;
	wxStaticText *Units_Text_Unknown11;
	wxStaticText *Units_Text_TrackingUnit;
	wxStaticText *Units_Text_TrackingUnitUsed;
	wxStaticText *Units_Text_TrackingUnitDensity;
	wxStaticText *Units_Text_Unknown12;
	wxStaticText *Units_Text_Unknown16;
	wxStaticText *Units_Text_Unknown16B;

//	Type 40+

	wxStaticText *Units_Text_SearchRadius;
	wxStaticText *Units_Text_WorkRate;
	wxStaticText *Units_Text_DropSite;
	wxStaticText *Units_Text_VillagerMode;
	wxStaticText *Units_Text_AttackSound;
	wxStaticText *Units_Text_MoveSound;
	wxStaticText *Units_Text_Exists;

//	Type 60+

	wxStaticText *Units_Text_Unknown20;
	wxStaticText *Units_Text_Unknown21;
	wxStaticText *Units_Text_MaxRange;
	wxStaticText *Units_Text_BlastRadius;
	wxStaticText *Units_Text_ReloadTime1;
	wxStaticText *Units_Text_ProjectileUnitID;
	wxStaticText *Units_Text_AccuracyPercent;
	wxStaticText *Units_Text_Delay;
	wxStaticText *Units_Text_GraphicDisplacement;
	wxStaticText *Units_Text_BlastLevel;
	wxStaticText *Units_Text_MinRange;
	wxStaticText *Units_Text_GarrisonRecoveryRate;
	wxStaticText *Units_Text_AttackGraphic;
	wxStaticText *Units_Text_DisplayedMeleeArmour;
	wxStaticText *Units_Text_DisplayedAttack;
	wxStaticText *Units_Text_DisplayedRange;
	wxStaticText *Units_Text_ReloadTime2;

//	Type 60 only

	wxStaticText *Units_Text_StretchMode;
	wxStaticText *Units_Text_CompensationMode;
	wxStaticText *Units_Text_DropAnimationMode;
	wxStaticText *Units_Text_PenetrationMode;
	wxStaticText *Units_Text_Unknown24;
	wxStaticText *Units_Text_ProjectileArc;

//	Type 70+

	wxStaticText *Units_Text_CostType;
	wxStaticText *Units_Text_CostAmount;
	wxStaticText *Units_Text_CostUsed;
	wxStaticText *Units_Text_TrainTime;
	wxStaticText *Units_Text_TrainLocationID;
	wxStaticText *Units_Text_ButtonID;
	wxStaticText *Units_Text_Unknown26;
	wxStaticText *Units_Text_Unknown27;
	wxStaticText *Units_Text_MissileGraphicDelay;
	wxStaticText *Units_Text_GarrisonGraphic;
	wxStaticText *Units_Text_AttackMissileDuplicationAmount1;
	wxStaticText *Units_Text_AttackMissileDuplicationAmount2;
	wxStaticText *Units_Text_AttackMissileDuplicationSpawning;
	wxStaticText *Units_Text_AttackMissileDuplicationUnit;
	wxStaticText *Units_Text_AttackMissileDuplicationGraphic;
	wxStaticText *Units_Text_Unknown29;
	wxStaticText *Units_Text_DisplayedPierceArmour;

//	Type 80

	wxStaticText *Units_Text_ConstructionGraphicID;
	wxStaticText *Units_Text_SnowGraphicID;
	wxStaticText *Units_Text_Unknown31;
	wxStaticText *Units_Text_Unknown31b;
	wxStaticText *Units_Text_StackUnitID;
	wxStaticText *Units_Text_TerrainID;
	wxStaticText *Units_Text_Unknown32;
	wxStaticText *Units_Text_ResearchID;
	wxStaticText *Units_Text_Unknown33;
	wxStaticText *Units_Text_AnnexUnit;
	wxStaticText *Units_Text_AnnexUnitMisplacement;
	wxStaticText *Units_Text_HeadUnit;
	wxStaticText *Units_Text_TransformUnit;
	wxStaticText *Units_Text_Unknown34;
	wxStaticText *Units_Text_ConstructionSound;
	wxStaticText *Units_Text_GarrisonType;
	wxStaticText *Units_Text_GarrisonHealRate;
	wxStaticText *Units_Text_Unknown35;
	wxStaticText *Units_Text_AlfaThingy;

//	Invisible Holder Windows
//	Type 10+

	wxStaticBoxSizer *Units_Holder_Type;
	wxBoxSizer *Units_Holder_ID1;
	wxBoxSizer *Units_Holder_LanguageDLLName;
	wxBoxSizer *Units_Holder_LanguageDLLCreation;
	wxBoxSizer *Units_Holder_Class;
	wxBoxSizer *Units_Holder_StandingGraphic;
	wxGridSizer *Units_Grid_StandingGraphic;
	wxBoxSizer *Units_Holder_DyingGraphic;
	wxGridSizer *Units_Grid_DyingGraphic;
	wxBoxSizer *Units_Holder_DeathMode;
	wxBoxSizer *Units_Holder_HitPoints;
	wxBoxSizer *Units_Holder_LineOfSight;
	wxBoxSizer *Units_Holder_GarrisonCapacity;
	wxBoxSizer *Units_Holder_SizeRadius;
	wxGridSizer *Units_Grid_SizeRadius;
	wxBoxSizer *Units_Holder_HPBarHeight1;
	wxBoxSizer *Units_Holder_TrainSound;
	wxBoxSizer *Units_Holder_TrainSound1;
	wxBoxSizer *Units_Holder_TrainSound2;
	wxBoxSizer *Units_Holder_TrainSound3;
	wxBoxSizer *Units_Holder_DeadUnitID;
	wxBoxSizer *Units_Holder_PlacementMode;
	wxBoxSizer *Units_Holder_AirMode;
	wxBoxSizer *Units_Holder_IconID;
	wxBoxSizer *Units_Holder_HideInEditor;
	wxBoxSizer *Units_Holder_Unknown1;
	wxBoxSizer *Units_Holder_Enabled;
	wxBoxSizer *Units_Holder_PlacementBypassTerrain;
	wxGridSizer *Units_Holder_PlacementBypassTerrainGrid;
	wxBoxSizer *Units_Holder_PlacementTerrain;
	wxGridSizer *Units_Holder_PlacementTerrainGrid;
	wxBoxSizer *Units_Holder_EditorRadius;
	wxGridSizer *Units_Grid_EditorRadius;
	wxBoxSizer *Units_Holder_BuildingMode;
	wxBoxSizer *Units_Holder_VisibleInFog;
	wxBoxSizer *Units_Holder_TerrainRestriction;
	wxBoxSizer *Units_Holder_FlyMode;
	wxBoxSizer *Units_Holder_ResourceCapacity;
	wxBoxSizer *Units_Holder_ResourceDecay;
	wxBoxSizer *Units_Holder_BlastType;
	wxBoxSizer *Units_Holder_Unknown2;
	wxBoxSizer *Units_Holder_InteractionMode;
	wxBoxSizer *Units_Holder_MinimapMode;
	wxBoxSizer *Units_Holder_CommandAttribute;
	wxBoxSizer *Units_Holder_Unknown3;
	wxGridSizer *Units_Grid_Unknown3;
	wxBoxSizer *Units_Holder_LanguageDLLHelp;
	wxBoxSizer *Units_Holder_LanguageDLLConverter[2];
	wxBoxSizer *Units_Holder_LanguageDLLHotKeyText;
	wxBoxSizer *Units_Holder_HotKey;
	wxBoxSizer *Units_Holder_Unselectable;
	wxBoxSizer *Units_Holder_Unknown6;
	wxBoxSizer *Units_Holder_Unknown7;
	wxBoxSizer *Units_Holder_Unknown8;
	wxBoxSizer *Units_Holder_SelectionMask;
	wxBoxSizer *Units_Holder_SelectionShapeType;
	wxBoxSizer *Units_Holder_SelectionShape;
	wxBoxSizer *Units_Holder_Attribute;
	wxBoxSizer *Units_Holder_Civ;
	wxBoxSizer *Units_Holder_Unknown9;
	wxBoxSizer *Units_Holder_SelectionEffect;
	wxBoxSizer *Units_Holder_EditorSelectionColour;
	wxBoxSizer *Units_Holder_SelectionRadius;
	wxBoxSizer *Units_Holder_HPBarHeight2;
	wxStaticBoxSizer *Units_Holder_ResourceStorageHeader;
	wxGridSizer *Units_Grid_ResourceStorage;
	wxBoxSizer *Units_Holder_ResourceStorage[3];
	wxBoxSizer *Units_Holder_SelectionSound;
	wxBoxSizer *Units_Holder_DyingSound;
	wxBoxSizer *Units_Holder_AttackMode;
	wxBoxSizer *Units_Holder_Name;
	wxBoxSizer *Units_Holder_Name2;
	wxBoxSizer *Units_Holder_Unitline;
	wxBoxSizer *Units_Holder_MinTechLevel;
	wxBoxSizer *Units_Holder_ID2;
	wxBoxSizer *Units_Holder_ID3;

//	Type 20+

	wxBoxSizer *Units_Holder_Speed;

//	Type 30+

	wxBoxSizer *Units_Holder_WalkingGraphic;
	wxGridSizer *Units_Grid_WalkingGraphic;
	wxBoxSizer *Units_Holder_RotationSpeed;
	wxBoxSizer *Units_Holder_Unknown11;
	wxBoxSizer *Units_Holder_TrackingUnit;
	wxBoxSizer *Units_Holder_TrackingUnitUsed;
	wxBoxSizer *Units_Holder_TrackingUnitUsedBox;
	wxBoxSizer *Units_Holder_TrackingUnitDensity;
	wxBoxSizer *Units_Holder_Unknown12;
	wxBoxSizer *Units_Holder_Unknown16;
	wxBoxSizer *Units_Holder_Unknown16B;
	wxGridSizer *Units_Grid_Unknown16B;

//	Type 40+

	wxBoxSizer *Units_Holder_SheepConversion;
	wxBoxSizer *Units_Holder_SearchRadius;
	wxBoxSizer *Units_Holder_WorkRate;
	wxGridSizer *Units_Grid_DropSite;
	wxBoxSizer *Units_Holder_VillagerMode;
	wxBoxSizer *Units_Holder_AttackSound;
	wxBoxSizer *Units_Holder_MoveSound;
	wxBoxSizer *Units_Holder_AnimalMode;
	wxBoxSizer *Units_Holder_Exists;

//	Type 60+

	wxBoxSizer *Units_Holder_Unknown20;
	wxGridSizer *Units_Grid_Unknown20;
	wxBoxSizer *Units_Holder_Unknown21;
	wxBoxSizer *Units_Holder_MaxRange;
	wxBoxSizer *Units_Holder_BlastRadius;
	wxBoxSizer *Units_Holder_ReloadTime1;
	wxBoxSizer *Units_Holder_ProjectileUnitID;
	wxBoxSizer *Units_Holder_AccuracyPercent;
	wxBoxSizer *Units_Holder_TowerMode;
	wxBoxSizer *Units_Holder_Delay;
	wxBoxSizer *Units_Holder_GraphicDisplacement;
	wxGridSizer *Units_Grid_GraphicDisplacement;
	wxBoxSizer *Units_Holder_BlastLevel;
	wxBoxSizer *Units_Holder_MinRange;
	wxBoxSizer *Units_Holder_GarrisonRecoveryRate;
	wxBoxSizer *Units_Holder_AttackGraphic;
	wxBoxSizer *Units_Holder_DisplayedMeleeArmour;
	wxBoxSizer *Units_Holder_DisplayedAttack;
	wxBoxSizer *Units_Holder_DisplayedRange;
	wxBoxSizer *Units_Holder_ReloadTime2;

//	Type 60 only

	wxBoxSizer *Units_Holder_StretchMode;
	wxBoxSizer *Units_Holder_CompensationMode;
	wxBoxSizer *Units_Holder_DropAnimationMode;
	wxBoxSizer *Units_Holder_PenetrationMode;
	wxBoxSizer *Units_Holder_Unknown24;
	wxBoxSizer *Units_Holder_ProjectileArc;

//	Type 70+

	wxStaticBoxSizer *Units_Holder_CostHeader;
	wxBoxSizer *Units_Holder_CostType;
	wxGridSizer *Units_Grid_CostType;
	wxBoxSizer *Units_Holder_CostAmount;
	wxBoxSizer *Units_Holder_CostUsed;
	wxBoxSizer *Units_Holder_TrainTime;
	wxBoxSizer *Units_Holder_TrainLocationID;
	wxBoxSizer *Units_Holder_ButtonID;
	wxBoxSizer *Units_Holder_Unknown26;
	wxBoxSizer *Units_Holder_Unknown27;
	wxBoxSizer *Units_Holder_MissileGraphicDelay;
	wxBoxSizer *Units_Holder_HeroMode;
	wxBoxSizer *Units_Holder_GarrisonGraphic;
	wxGridSizer *Units_Grid_GarrisonGraphic;
	wxBoxSizer *Units_Holder_AttackMissileDuplicationAmount1;
	wxBoxSizer *Units_Holder_AttackMissileDuplicationAmount2;
	wxBoxSizer *Units_Holder_AttackMissileDuplicationSpawning;
	wxGridSizer *Units_Grid_AttackMissileDuplicationSpawning;
	wxBoxSizer *Units_Holder_AttackMissileDuplicationUnit;
	wxBoxSizer *Units_Holder_AttackMissileDuplicationGraphic;
	wxBoxSizer *Units_Holder_Unknown29;
	wxBoxSizer *Units_Holder_DisplayedPierceArmour;

//	Type 80

	wxBoxSizer *Units_Holder_ConstructionGraphicID;
	wxBoxSizer *Units_Holder_SnowGraphicID;
	wxBoxSizer *Units_Holder_AdjacentMode;
	wxBoxSizer *Units_Holder_Unknown31;
	wxBoxSizer *Units_Holder_Unknown31b;
	wxBoxSizer *Units_Holder_Unknown31bsub;
	wxBoxSizer *Units_Holder_StackUnitID;
	wxBoxSizer *Units_Holder_TerrainID;
	wxBoxSizer *Units_Holder_Unknown32;
	wxBoxSizer *Units_Holder_ResearchID;
	wxBoxSizer *Units_Holder_Unknown33;
	wxGridSizer *Units_Grid_AnnexUnit;
	wxBoxSizer *Units_Holder_AnnexUnit1;
	wxGridSizer *Units_Grid_AnnexUnitMisplacement;
	wxBoxSizer *Units_Holder_AnnexUnitMisplacement1;
	wxBoxSizer *Units_Holder_HeadUnit;
	wxBoxSizer *Units_Holder_TransformUnit;
	wxBoxSizer *Units_Holder_Unknown34;
	wxBoxSizer *Units_Holder_ConstructionSound;
	wxBoxSizer *Units_Holder_GarrisonType;
	wxBoxSizer *Units_Holder_GarrisonHealRate;
	wxBoxSizer *Units_Holder_Unknown35;
	wxBoxSizer *Units_Holder_AlfaThingy;
	wxGridSizer *Units_Grid_AlfaThingy;

//	Unit Controls SubControls

	wxGridSizer *Units_Holder_DamageGraphics;
	wxBoxSizer *Units_Holder_DamageGraphics_Data;
	TextCtrl_Short *DamageGraphics_GraphicID;
	ComboBox_Plus1 *DamageGraphics_ComboBox_GraphicID;
	TextCtrl_Byte *DamageGraphics_DamagePercent;
	TextCtrl_Byte *DamageGraphics_Unknown1;
	TextCtrl_Byte *DamageGraphics_Unknown2;
	wxStaticText *DamageGraphics_Text_GraphicID;
	wxStaticText *DamageGraphics_Text_DamagePercent;
	wxStaticText *DamageGraphics_Text_Unknown1;
	wxStaticText *DamageGraphics_Text_Unknown2;
	wxBoxSizer *DamageGraphics_Holder_GraphicID;
	wxBoxSizer *DamageGraphics_Holder_DamagePercent;
	wxBoxSizer *DamageGraphics_Holder_Unknown1;
	wxBoxSizer *DamageGraphics_Holder_Unknown2;
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

	wxBoxSizer *Units_Holder_Attacks;
	wxBoxSizer *Units_Holder_Attacks_Data;
	wxGridSizer *Units_Grid_Attacks_Data2;
	TextCtrl_Short *Attacks_Class;
	ComboBox_Plus1 *Attacks_ComboBox_Class[3];
	TextCtrl_Short *Attacks_Amount;
	wxStaticText *Attacks_Text_Class;
	wxStaticText *Attacks_Text_Amount;
	wxBoxSizer *Attacks_Holder_Class;
	wxBoxSizer *Attacks_Holder_Amount;
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

	wxBoxSizer *Units_Holder_Armors;
	wxBoxSizer *Units_Holder_Armors_Data3;
	TextCtrl_Short *Armors_Class;
	TextCtrl_Short *Armors_Amount;
	wxStaticText *Armors_Text_Class;
	wxStaticText *Armors_Text_Amount;
	wxBoxSizer *Armors_Holder_Class;
	wxBoxSizer *Armors_Holder_Amount;
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
	wxGridSizer *Units_Units_Buttons[2];	// Unit list section buttons

	wxStaticBoxSizer *Units_Units;	// Unit list section vertical division excluding window borders
	//wxStaticLine *Units_Units_Line;
	wxBoxSizer *Units_Units_Special;
	wxComboBox *Units_Civs_List;	// Civ list combo box
	wxBoxSizer *Units_Units_Searches[2];
	wxTextCtrl *Units_Units_Search;	// Unit search
	wxTextCtrl *Units_Units_Search_R;	// Unit reverse search
	wxOwnerDrawnComboBox *Units_Units_SearchFilters[2];	// Unit search
	wxCheckBox *Units_Units_UseAnd[2];
	wxListBox *Units_Units_List;	// List of units
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

	wxBoxSizer *Units_ScrollerWindows;	// Scrollable section division
	wxBoxSizer *Units_ScrollerWindowsSpace;
	wxStaticBoxSizer *Units_Holder_TypeArea;
	wxBoxSizer *Units_Holder_TypeArea1;
	wxBoxSizer *Units_Holder_TypeArea2;
	wxStaticBoxSizer *Units_Holder_LangDLLArea;
	wxStaticBoxSizer *Units_Holder_GraphicsArea;
	wxBoxSizer *Units_Holder_GraphicsArea1;
	wxBoxSizer *Units_Holder_GraphicsArea4;
	wxBoxSizer *Units_Holder_GraphicsArea5;
	wxStaticBoxSizer *Units_Holder_StatsArea;
	wxGridSizer *Units_Grid_StatsArea1;
	wxGridSizer *Units_Grid_StatsAreaGarrison;
	wxGridSizer *Units_Grid_StatsArea2;
	wxStaticBoxSizer *Units_Holder_ProjectilesArea;
	wxGridSizer *Units_Grid_ProjectilesArea1;
	wxGridSizer *Units_Grid_ProjectilesArea2;
	wxGridSizer *Units_Grid_ProjectilesArea3;
	wxStaticBoxSizer *Units_Holder_Attributes;
	wxGridSizer *Units_Grid_AttributesBoxes1;
	wxGridSizer *Units_Grid_Attributes1;
	wxBoxSizer *Units_Holder_AttributesTerrain;
	wxGridSizer *Units_Grid_AttributesTerrain;
	wxGridSizer *Units_Grid_AttributesModes1;
	wxBoxSizer *Units_Holder_AttributesDropSite;
	wxBoxSizer *Units_Holder_AttributesSizes;
	wxGridSizer *Units_Grid_AttributesSelection1;
	wxBoxSizer *Units_Holder_LangRegular;
	wxBoxSizer *Units_Holder_LangHotKey;
	wxGridSizer *Units_Grid_AttributesTracking;
	wxGridSizer *Units_Grid_AttributesTrain1;
	wxGridSizer *Units_Grid_Attributes3;
	wxStaticBoxSizer *Units_Holder_SoundsArea;
	wxBoxSizer *Units_Holder_SoundsArea1;
	wxGridSizer *Units_Grid_SoundsArea2;
	wxStaticBoxSizer *Units_Holder_MiscArea;
	wxGridSizer *Units_Grid_HPBars;
	wxBoxSizer *Units_Holder_UnknownArea;
	wxStaticBoxSizer *Units_Holder_Type10plusUnknownArea;
	wxGridSizer *Units_Grid_Type10plusUnknowns;
	wxStaticBoxSizer *Units_Holder_Type30plusUnknownArea;
	wxGridSizer *Units_Grid_Type30plusUnknownArea;
	wxStaticBoxSizer *Units_Holder_Type60plusUnknownArea;
	wxStaticBoxSizer *Units_Holder_Type70plusUnknownArea;
	wxGridSizer *Units_Grid_Type70plusUnknownArea;
	wxStaticBoxSizer *Units_Holder_Type80plusUnknownArea;
	wxGridSizer *Units_Grid_Type80plusUnknownArea;
	wxStaticBoxSizer *Units_Holder_CommandsArea;
	wxBoxSizer *Units_Holder_Top;
	wxGridSizer *Units_Holder_TopGrid;
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
	wxBoxSizer *UnitCommands_Holder_One;
	wxBoxSizer *UnitCommands_Holder_ID;
	wxBoxSizer *UnitCommands_Holder_1;
	wxBoxSizer *UnitCommands_Holder_Unknown1;
	wxBoxSizer *UnitCommands_Holder_Type;
	wxBoxSizer *UnitCommands_Holder_SubType;
	wxBoxSizer *UnitCommands_Holder_ClassID;
	wxBoxSizer *UnitCommands_Holder_UnitID;
	wxBoxSizer *UnitCommands_Holder_Unknown2;
	wxBoxSizer *UnitCommands_Holder_ResourceIn;
	wxBoxSizer *UnitCommands_Holder_ResourceOut;
	wxBoxSizer *UnitCommands_Holder_Unknown3;
	wxBoxSizer *UnitCommands_Holder_WorkRateMultiplier;
	wxBoxSizer *UnitCommands_Holder_ExecutionRadius;
	wxBoxSizer *UnitCommands_Holder_ExtraRange;
	wxBoxSizer *UnitCommands_Holder_Unknown4;
	wxBoxSizer *UnitCommands_Holder_Unknown5;
	wxBoxSizer *UnitCommands_Holder_Unknown6;
	wxBoxSizer *UnitCommands_Holder_Unknown7;
	wxBoxSizer *UnitCommands_Holder_Unknown8;
	wxBoxSizer *UnitCommands_Holder_Unknown9;
	wxBoxSizer *UnitCommands_Holder_Unknown10;
	wxBoxSizer *UnitCommands_Holder_Unknown11;
	array<wxBoxSizer*, 6> UnitCommands_Holder_Graphics;
	wxGridSizer *UnitCommands_Grid_Graphics;

	wxStaticText *UnitCommands_Text_One;
	wxStaticText *UnitCommands_Text_ID;
	wxStaticText *UnitCommands_Text_Unknown1;
	wxStaticText *UnitCommands_Text_Type;
	wxStaticText *UnitCommands_Text_ClassID;
	wxStaticText *UnitCommands_Text_UnitID;
	wxStaticText *UnitCommands_Text_Unknown2;
	wxStaticText *UnitCommands_Text_ResourceIn;
	wxStaticText *UnitCommands_Text_SubType;
	wxStaticText *UnitCommands_Text_ResourceOut;
	wxStaticText *UnitCommands_Text_Unknown3;
	wxStaticText *UnitCommands_Text_WorkRateMultiplier;
	wxStaticText *UnitCommands_Text_ExecutionRadius;
	wxStaticText *UnitCommands_Text_ExtraRange;
	wxStaticText *UnitCommands_Text_Unknown4;
	wxStaticText *UnitCommands_Text_Unknown5;
	wxStaticText *UnitCommands_Text_Unknown6;
	wxStaticText *UnitCommands_Text_Unknown7;
	wxStaticText *UnitCommands_Text_Unknown8;
	wxStaticText *UnitCommands_Text_Unknown9;
	wxStaticText *UnitCommands_Text_Unknown10;
	wxStaticText *UnitCommands_Text_Unknown11;
	array<wxStaticText*, 6> UnitCommands_Text_Graphics;

	TextCtrl_Short *UnitCommands_One;
	TextCtrl_Short *UnitCommands_ID;
	TextCtrl_Byte *UnitCommands_Unknown1;
	TextCtrl_Short *UnitCommands_Type;
	wxOwnerDrawnComboBox *UnitCommands_ComboBox_Type;
	TextCtrl_Short *UnitCommands_ClassID;
	TextCtrl_Short *UnitCommands_UnitID;
	ComboBox_Plus1 *UnitCommands_ComboBox_UnitID;
	TextCtrl_Short *UnitCommands_Unknown2;
	TextCtrl_Short *UnitCommands_ResourceIn;
	ComboBox_Plus1 *UnitCommands_ComboBox_ResourceIn;
	TextCtrl_Short *UnitCommands_SubType;
	ComboBox_Plus1 *UnitCommands_ComboBox_SubType;
	TextCtrl_Short *UnitCommands_ResourceOut;
	ComboBox_Plus1 *UnitCommands_ComboBox_ResourceOut;
	TextCtrl_Short *UnitCommands_Unknown3;
	ComboBox_Plus1 *UnitCommands_ComboBox_Unknown3;
	TextCtrl_Float *UnitCommands_WorkRateMultiplier;
	TextCtrl_Float *UnitCommands_ExecutionRadius;
	TextCtrl_Float *UnitCommands_ExtraRange;
	TextCtrl_Byte *UnitCommands_Unknown4;
	TextCtrl_Float *UnitCommands_Unknown5;
	TextCtrl_Byte *UnitCommands_Unknown6;
	TextCtrl_Byte *UnitCommands_Unknown7;
	TextCtrl_Long *UnitCommands_Unknown8;
	TextCtrl_Byte *UnitCommands_Unknown9;
	TextCtrl_Byte *UnitCommands_Unknown10;
	TextCtrl_Byte *UnitCommands_Unknown11;
	array<TextCtrl_Short*, 6> UnitCommands_Graphics;
	array<ComboBox_Plus1*, 6> UnitCommands_ComboBox_Graphics;

//	Graphics user interface

	wxBoxSizer *Graphics_Main;
	wxBoxSizer *Graphics_ListArea;
	wxGridSizer *Graphics_Graphics_Buttons;
	wxStaticBoxSizer *Graphics_Graphics;
	wxBoxSizer *Graphics_Graphics_Searches[2];
	wxTextCtrl *Graphics_Graphics_Search;
	wxTextCtrl *Graphics_Graphics_Search_R;
	wxOwnerDrawnComboBox *Graphics_Graphics_SearchFilters[2];
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
	wxBoxSizer *Graphics_ScrollerWindows;
	wxBoxSizer *Graphics_ScrollerWindowsSpace;

	wxBoxSizer *Graphics_Holder_NameArea;
	wxBoxSizer *Graphics_Holder_Name;
	wxBoxSizer *Graphics_Holder_Name2;
	wxBoxSizer *Graphics_Holder_SLP;
	wxGridSizer *Graphics_Holder_Unknowns;
	wxBoxSizer *Graphics_Holder_Unknown1;
	wxBoxSizer *Graphics_Holder_Unknown2;
	wxBoxSizer *Graphics_Holder_FrameType;
	wxBoxSizer *Graphics_Holder_PlayerColor;
	wxBoxSizer *Graphics_Holder_Unknown4;
	wxBoxSizer *Graphics_Holder_Replay;
	wxBoxSizer *Graphics_Holder_Coordinates;
	wxGridSizer *Graphics_Holder_CoordinateGrid;
	wxBoxSizer *Graphics_Holder_SoundID;
	wxBoxSizer *Graphics_Holder_AttackSoundUsed;
	wxBoxSizer *Graphics_Holder_AttackSoundUsed1;
	wxBoxSizer *Graphics_Holder_4;
	wxBoxSizer *Graphics_Holder_5;
	wxBoxSizer *Graphics_Holder_FrameCount;
	wxBoxSizer *Graphics_Holder_AngleCount;
	wxBoxSizer *Graphics_Holder_NewSpeed;
	wxBoxSizer *Graphics_Holder_FrameRate;
	wxBoxSizer *Graphics_Holder_ReplayDelay;
	wxBoxSizer *Graphics_Holder_SequenceType;
	wxBoxSizer *Graphics_Holder_ID;
	wxBoxSizer *Graphics_Holder_Type;
	wxGridSizer *Graphics_Grid_1;
	wxGridSizer *Graphics_Grid_2;

	wxStaticText *Graphics_Text_Name;
	wxStaticText *Graphics_Text_Name2;
	wxStaticText *Graphics_Text_SLP;
	wxStaticText *Graphics_Text_Unknown1;
	wxStaticText *Graphics_Text_Unknown2;
	wxStaticText *Graphics_Text_FrameType;
	wxStaticText *Graphics_Text_PlayerColor;
	wxStaticText *Graphics_Text_Unknown4;
	wxStaticText *Graphics_Text_Replay;
	wxStaticText *Graphics_Text_Coordinates;
	wxStaticText *Graphics_Text_SoundID;
	wxStaticText *Graphics_Text_AttackSoundUsed;
	wxStaticText *Graphics_Text_FrameCount;
	wxStaticText *Graphics_Text_AngleCount;
	wxStaticText *Graphics_Text_NewSpeed;
	wxStaticText *Graphics_Text_FrameRate;
	wxStaticText *Graphics_Text_ReplayDelay;
	wxStaticText *Graphics_Text_SequenceType;
	wxStaticText *Graphics_Text_ID;
	wxStaticText *Graphics_Text_Type;

	TextCtrl_String *Graphics_Name;
	TextCtrl_String *Graphics_Name2;
	TextCtrl_Long *Graphics_SLP;
	TextCtrl_Byte *Graphics_Unknown1;
	TextCtrl_Byte *Graphics_Unknown2;
	TextCtrl_Byte *Graphics_FrameType;
	TextCtrl_Short *Graphics_PlayerColor;
	ComboBox_Plus1 *Graphics_ComboBox_PlayerColor;
	TextCtrl_Byte *Graphics_Replay;
	TextCtrl_Short *Graphics_Coordinates[4];
	TextCtrl_Short *Graphics_SoundID;
	ComboBox_Plus1 *Graphics_ComboBox_SoundID;
	TextCtrl_Byte *Graphics_AttackSoundUsed;
	CheckBox_2State *Graphics_CheckBox_AttackSoundUsed;
	TextCtrl_UShort *Graphics_FrameCount;
	TextCtrl_UShort *Graphics_AngleCount;
	TextCtrl_Float *Graphics_NewSpeed;
	TextCtrl_Float *Graphics_FrameRate;
	TextCtrl_Float *Graphics_ReplayDelay;
	TextCtrl_Byte *Graphics_SequenceType;
	TextCtrl_Short *Graphics_ID;
	TextCtrl_Short *Graphics_TypeS;

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

	wxStaticBoxSizer *Graphics_Holder_Deltas;
	wxBoxSizer *Graphics_Holder_Deltas_Data;
	wxBoxSizer *Graphics_Holder_Deltas_Data1;
	wxGridSizer *Graphics_Grid_Deltas_Data2;
	wxStaticBoxSizer *Graphics_Holder_AttackSoundArea;

	wxBoxSizer *GraphicDeltas_Holder_GraphicID;
	wxStaticText *GraphicDeltas_Text_GraphicID;
	TextCtrl_Short *GraphicDeltas_GraphicID;
	ComboBox_Plus1 *GraphicDeltas_ComboBox_GraphicID;
	wxBoxSizer *GraphicDeltas_Holder_Unknown1;
	wxStaticText *GraphicDeltas_Text_Unknown1;
	TextCtrl_Short *GraphicDeltas_Unknown1;
	wxBoxSizer *GraphicDeltas_Holder_Unknown2;
	wxStaticText *GraphicDeltas_Text_Unknown2;
	TextCtrl_Short *GraphicDeltas_Unknown2;
	wxBoxSizer *GraphicDeltas_Holder_Unknown3;
	wxStaticText *GraphicDeltas_Text_Unknown3;
	TextCtrl_Short *GraphicDeltas_Unknown3;
	wxBoxSizer *GraphicDeltas_Holder_DirectionX;
	wxStaticText *GraphicDeltas_Text_DirectionX;
	TextCtrl_Short *GraphicDeltas_DirectionX;
	wxBoxSizer *GraphicDeltas_Holder_DirectionY;
	wxStaticText *GraphicDeltas_Text_DirectionY;
	TextCtrl_Short *GraphicDeltas_DirectionY;
	wxBoxSizer *GraphicDeltas_Holder_Unknown4;
	wxStaticText *GraphicDeltas_Text_Unknown4;
	TextCtrl_Short *GraphicDeltas_Unknown4;
	wxBoxSizer *GraphicDeltas_Holder_Unknown5;
	wxStaticText *GraphicDeltas_Text_Unknown5;
	TextCtrl_Short *GraphicDeltas_Unknown5;
	wxBoxSizer *Graphics_Holder_AttackSounds;
	wxGridSizer *Graphics_Grid_AttackSounds;
	wxStaticText *Graphics_Text_AttackSounds;
	wxBoxSizer *Graphics_Holder_AttackSoundDelays;
	wxStaticText *Graphics_Text_AttackSoundDelays;
	TextCtrl_Short *Graphics_AttackSoundDelay[3];
	TextCtrl_Short *Graphics_AttackSoundID[3];
	ComboBox_Plus1 *Graphics_ComboBox_AttackSoundID[3];

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
	wxGridSizer *Terrains_Terrains_Buttons;
	wxButton *Terrains_Add;
	wxButton *Terrains_Insert;
	wxButton *Terrains_Delete;
	wxButton *Terrains_Copy;
	wxButton *Terrains_Paste;
	wxButton *Terrains_PasteInsert;

	wxBoxSizer *Terrains_DataArea;
	wxScrolledWindow *Terrains_Scroller;
	wxBoxSizer *Terrains_ScrollerWindows;
	wxBoxSizer *Terrains_ScrollerWindowsSpace;
	wxBoxSizer *Terrains_Holder_NameArea;
	wxGridSizer *Terrains_Grid_Area1;
	wxBoxSizer *Terrains_Holder_UnknownArea;
	wxGridSizer *Terrains_Grid_Unknowns1;
	wxBoxSizer *Terrains_Holder_Unknown1;
	wxStaticText *Terrains_Text_Unknown1;
	TextCtrl_Short *Terrains_Unknown1;
	wxBoxSizer *Terrains_Holder_Unknown2;
	wxStaticText *Terrains_Text_Unknown2;
	TextCtrl_Short *Terrains_Unknown2;
	wxBoxSizer *Terrains_Holder_Name;
	wxStaticText *Terrains_Text_Name;
	TextCtrl_String *Terrains_Name;
	wxBoxSizer *Terrains_Holder_Name2;
	wxStaticText *Terrains_Text_Name2;
	TextCtrl_String *Terrains_Name2;
	wxBoxSizer *Terrains_Holder_SLP;
	wxStaticText *Terrains_Text_SLP;
	TextCtrl_Long *Terrains_SLP;
	wxBoxSizer *Terrains_Holder_Unknown3;
	wxStaticText *Terrains_Text_Unknown3;
	TextCtrl_Float *Terrains_Unknown3;
	wxBoxSizer *Terrains_Holder_SoundID;
	wxStaticText *Terrains_Text_SoundID;
	TextCtrl_Long *Terrains_SoundID;
	ComboBox_Plus1 *Terrains_ComboBox_SoundID;
	wxBoxSizer *Terrains_Holder_BlendPriority;
	wxStaticText *Terrains_Text_BlendPriority;
	TextCtrl_Long *Terrains_BlendPriority;
	wxBoxSizer *Terrains_Holder_BlendType;
	wxStaticText *Terrains_Text_BlendType;
	TextCtrl_Long *Terrains_BlendType;
	wxBoxSizer *Terrains_Holder_Colors;
	wxGridSizer *Terrains_Grid_Colors;
	wxStaticText *Terrains_Text_Colors;
	array<TextCtrl_UByte*, 3> Terrains_Colors;
	wxBoxSizer *Terrains_Holder_Unknown5;
	wxGridSizer *Terrains_Grid_Unknown5;
	wxStaticText *Terrains_Text_Unknown5;
	array<TextCtrl_Byte*, 5> Terrains_Unknown5;
	wxBoxSizer *Terrains_Holder_Unknown6;
	wxStaticText *Terrains_Text_Unknown6;
	TextCtrl_Float *Terrains_Unknown6;
	wxBoxSizer *Terrains_Holder_Unknown7;
	wxGridSizer *Terrains_Grid_Unknown7;
	wxStaticText *Terrains_Text_Unknown7;
	array<TextCtrl_Byte*, 18> Terrains_Unknown7;
	wxBoxSizer *Terrains_Holder_FrameCount;
	wxStaticText *Terrains_Text_FrameCount;
	TextCtrl_Short *Terrains_FrameCount;
	wxBoxSizer *Terrains_Holder_AngleCount;
	wxStaticText *Terrains_Text_AngleCount;
	TextCtrl_Short *Terrains_AngleCount;
	wxBoxSizer *Terrains_Holder_TerrainID;
	wxStaticText *Terrains_Text_TerrainID;
	TextCtrl_Short *Terrains_TerrainID;
	wxBoxSizer *Terrains_Holder_ElevationGraphics;
	wxGridSizer *Terrains_Grid_Unknown9;
	wxStaticText *Terrains_Text_ElevationGraphics;
	array<TextCtrl_Short*, 54>Terrains_ElevationGraphics;
	wxBoxSizer *Terrains_Holder_TerrainReplacementID;
	wxStaticText *Terrains_Text_TerrainReplacementID;
	TextCtrl_Short *Terrains_TerrainReplacementID;
	ComboBox_Plus1 *Terrains_ComboBox_TerrainReplacementID;
	wxBoxSizer *Terrains_Holder_TerrainDimensions;
	wxStaticText *Terrains_Text_TerrainDimensions;
	array<TextCtrl_Short*, 2>Terrains_TerrainDimensions;
	wxBoxSizer *Terrains_Holder_TerrainBorders;
	wxGridSizer *Terrains_Grid_TerrainBorders;
	wxStaticText *Terrains_Text_TerrainBorderID;
	auto static const TERRAINBORDERSMAX = 42;
	array<TextCtrl_Short*, TERRAINBORDERSMAX>Terrains_TerrainBorderID;
	array<ComboBox_Plus1*, TERRAINBORDERSMAX>Terrains_ComboBox_TerrainBorderID;
	auto static const TERRAINUNITS = 30;
	wxBoxSizer *Terrains_Holder_TerrainUnits;
	wxBoxSizer *Terrains_Holder_TerrainUnitID;
	wxGridSizer *Terrains_Grid_TerrainUnitID;
	wxStaticText *Terrains_Text_TerrainUnitID;
	array<TextCtrl_Short*, TERRAINUNITS>Terrains_TerrainUnitID;
	array<ComboBox_Plus1*, TERRAINUNITS>Terrains_ComboBox_TerrainUnitID;
	wxBoxSizer *Terrains_Holder_TerrainUnitDensity;
	wxStaticText *Terrains_Text_TerrainUnitDensity;
	array<TextCtrl_Short*, TERRAINUNITS>Terrains_TerrainUnitDensity;
	wxBoxSizer *Terrains_Holder_TerrainUnitPriority;
	wxStaticText *Terrains_Text_TerrainUnitPriority;
	array<TextCtrl_Byte*, TERRAINUNITS>Terrains_TerrainUnitPriority;
	wxBoxSizer *Terrains_Holder_NumberOfTerrainUnitsUsed;
	wxBoxSizer *Terrains_Holder_NumberOfTerrainUnitsUsed1;
	wxStaticText *Terrains_Text_NumberOfTerrainUnitsUsed;
	TextCtrl_Short *Terrains_NumberOfTerrainUnitsUsed;
	wxBoxSizer *Terrains_Holder_SUnknown1;
	wxGridSizer *Terrains_Grid_SUnknown1;
	wxStaticText *Terrains_Text_SUnknown1;
	array<TextCtrl_Byte*, 24>Terrains_SUnknown1;

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
	wxBoxSizer *TerRestrict_Holder_Accessible;
	wxBoxSizer *TerRestrict_Holder_Accessible2;
	wxStaticText *TerRestrict_Text_Accessible;
	TextCtrl_Float *TerRestrict_Accessible;
	CheckBox_2State *TerRestrict_CheckBox_Accessible;
	wxBoxSizer *TerRestrict_Holder_Unknown1;
	wxBoxSizer *TerRestrict_Holder_Unknown1Sub;
	wxStaticText *TerRestrict_Text_Unknown1;
	TextCtrl_Long *TerRestrict_Unknown1;
	CheckBox_ZeroIsYes *TerRestrict_CheckBox_Unknown1;
	wxBoxSizer *TerRestrict_Holder_Graphics;
	wxStaticText *TerRestrict_Text_Graphics;
	TextCtrl_Long *TerRestrict_Graphics[2];
	ComboBox_Plus1 *TerRestrict_ComboBox_Graphics[2];
	wxBoxSizer *TerRestrict_Holder_Amount;
	wxStaticText *TerRestrict_Text_Amount;
	TextCtrl_Long *TerRestrict_Amount;

//	Sound user interface

	wxBoxSizer *Sounds_Main;
	wxBoxSizer *Sounds_ListArea;
	wxGridSizer *Sounds_Sounds_Buttons;
	wxBoxSizer *SoundItems_ListArea;
	wxGridSizer *Sounds_Items_Buttons;
	wxBoxSizer *Sounds_DataArea;

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

	wxBoxSizer *Sounds_Holder_ID;
	wxStaticText *Sounds_Text_ID;
	TextCtrl_Long *Sounds_ID;
	wxBoxSizer *Sounds_Holder_Unknown;
	wxStaticText *Sounds_Text_Unknown;
	TextCtrl_Long *Sounds_Unknown;
	wxBoxSizer *SoundItems_Holder_Name;
	wxStaticText *SoundItems_Text_Name;
	TextCtrl_String *SoundItems_Name;
	wxBoxSizer *SoundItems_Holder_Resource;
	wxStaticText *SoundItems_Text_Resource;
	TextCtrl_Long *SoundItems_Resource;
	wxBoxSizer *SoundItems_Holder_Probability;
	wxStaticText *SoundItems_Text_Probability;
	TextCtrl_Short *SoundItems_Probability;
	wxBoxSizer *SoundItems_Holder_Civ;
	wxStaticText *SoundItems_Text_Civ;
	TextCtrl_Short *SoundItems_Civ;
	ComboBox_Plus1 *SoundItems_ComboBox_Civ;
	wxBoxSizer *SoundItems_Holder_Unknown;
	wxStaticText *SoundItems_Text_Unknown;
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
	wxBoxSizer *Colors_Holder_Name;
	wxBoxSizer *Colors_Holder_ID;
	wxBoxSizer *Colors_Holder_Palette;
	wxBoxSizer *Colors_Holder_Color;
	wxBoxSizer *Colors_Holder_MinimapColor;
	wxBoxSizer *Colors_Holder_UnknownArea;
	wxBoxSizer *Colors_Holder_Unknown1;
	wxBoxSizer *Colors_Holder_Unknown2;
	wxBoxSizer *Colors_Holder_Unknown3;
	wxBoxSizer *Colors_Holder_Unknown4;
	wxBoxSizer *Colors_Holder_Unknown5;
	wxStaticText *Colors_Text_Name;
	wxStaticText *Colors_Text_ID;
	wxStaticText *Colors_Text_Palette;
	wxStaticText *Colors_Text_Color;
	wxStaticText *Colors_Text_MinimapColor;
	wxStaticText *Colors_Text_Unknown1;
	wxStaticText *Colors_Text_Unknown2;
	wxStaticText *Colors_Text_Unknown3;
	wxStaticText *Colors_Text_Unknown4;
	wxStaticText *Colors_Text_Unknown5;
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

	wxBoxSizer *UnitLines_Holder_ID;
	wxStaticText *UnitLines_Text_ID;
	TextCtrl_Short *UnitLines_ID;
	wxBoxSizer *UnitLines_Holder_Name;
	wxStaticText *UnitLines_Text_Name;
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

	wxBoxSizer *UnitLineUnits_Holder_Units;
	wxStaticText *UnitLineUnits_Text_Units;
	TextCtrl_Short *UnitLineUnits_Units;
	ComboBox_Plus1 *UnitLineUnits_ComboBox_Units;

//	Tech Tree user interface

	wxBoxSizer *TechTrees_Main;
	wxBoxSizer *TechTrees_All;
	wxScrolledWindow *TechTrees_Scroller;
	wxBoxSizer *TechTrees_ScrollerWindows;
	wxBoxSizer *TechTrees_ScrollerWindowsSpace;
	wxStaticBoxSizer *TechTrees_Ages;
	wxStaticBoxSizer *TechTrees_Buildings;
	wxStaticBoxSizer *TechTrees_Units;
	wxStaticBoxSizer *TechTrees_Researches;
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

	wxBoxSizer *TechTrees_Data_Ages;
	wxGridSizer *TechTrees_Data_Ages1;
	wxBoxSizer *TechTrees_Data_Buildings;
	wxGridSizer *TechTrees_Data_Buildings1;
	wxBoxSizer *TechTrees_Data_Units;
	wxGridSizer *TechTrees_Data_Units1;
	wxBoxSizer *TechTrees_Data_Researches;
	wxGridSizer *TechTrees_Data_Researches1;
	wxBoxSizer *TechTrees_DataListHolder_Ages;
	wxBoxSizer *TechTrees_DataListHolder_Buildings;
	wxBoxSizer *TechTrees_DataListHolder_Units;
	wxBoxSizer *TechTrees_DataListHolder_Researches;
	wxStaticBoxSizer *TechTrees_DataList_Ages_Buildings;
	wxStaticBoxSizer *TechTrees_DataList_Ages_Units;
	wxStaticBoxSizer *TechTrees_DataList_Ages_Researches;
	wxStaticBoxSizer *TechTrees_DataList_Buildings_Buildings;
	wxStaticBoxSizer *TechTrees_DataList_Buildings_Units;
	wxStaticBoxSizer *TechTrees_DataList_Buildings_Researches;
	wxStaticBoxSizer *TechTrees_DataList_Units_Units;
	wxStaticBoxSizer *TechTrees_DataList_Researches_Buildings;
	wxStaticBoxSizer *TechTrees_DataList_Researches_Units;
	wxStaticBoxSizer *TechTrees_DataList_Researches_Researches;
	wxTextCtrl *TechTrees_DataList_Ages_Search_Buildings;
	wxTextCtrl *TechTrees_DataList_Ages_Search_Units;
	wxTextCtrl *TechTrees_DataList_Ages_Search_Researches;
	wxTextCtrl *TechTrees_DataList_Buildings_Search_Buildings;
	wxTextCtrl *TechTrees_DataList_Buildings_Search_Units;
	wxTextCtrl *TechTrees_DataList_Buildings_Search_Researches;
	wxTextCtrl *TechTrees_DataList_Units_Search_Units;
	wxTextCtrl *TechTrees_DataList_Researches_Search_Buildings;
	wxTextCtrl *TechTrees_DataList_Researches_Search_Units;
	wxTextCtrl *TechTrees_DataList_Researches_Search_Researches;
	wxTextCtrl *TechTrees_DataList_Ages_Search_R_Buildings;
	wxTextCtrl *TechTrees_DataList_Ages_Search_R_Units;
	wxTextCtrl *TechTrees_DataList_Ages_Search_R_Researches;
	wxTextCtrl *TechTrees_DataList_Buildings_Search_R_Buildings;
	wxTextCtrl *TechTrees_DataList_Buildings_Search_R_Units;
	wxTextCtrl *TechTrees_DataList_Buildings_Search_R_Researches;
	wxTextCtrl *TechTrees_DataList_Units_Search_R_Units;
	wxTextCtrl *TechTrees_DataList_Researches_Search_R_Buildings;
	wxTextCtrl *TechTrees_DataList_Researches_Search_R_Units;
	wxTextCtrl *TechTrees_DataList_Researches_Search_R_Researches;
	wxListBox *TechTrees_DataList_Ages_List_Buildings;
	wxListBox *TechTrees_DataList_Ages_List_Units;
	wxListBox *TechTrees_DataList_Ages_List_Researches;
	wxListBox *TechTrees_DataList_Buildings_List_Buildings;
	wxListBox *TechTrees_DataList_Buildings_List_Units;
	wxListBox *TechTrees_DataList_Buildings_List_Researches;
	wxListBox *TechTrees_DataList_Units_List_Units;
	wxListBox *TechTrees_DataList_Researches_List_Buildings;
	wxListBox *TechTrees_DataList_Researches_List_Units;
	wxListBox *TechTrees_DataList_Researches_List_Researches;
	wxGridSizer *TechTrees_DataList_Ages_Buttons_Buildings;
	wxGridSizer *TechTrees_DataList_Ages_Buttons_Units;
	wxGridSizer *TechTrees_DataList_Ages_Buttons_Researches;
	wxGridSizer *TechTrees_DataList_Buildings_Buttons_Buildings;
	wxGridSizer *TechTrees_DataList_Buildings_Buttons_Units;
	wxGridSizer *TechTrees_DataList_Buildings_Buttons_Researches;
	wxGridSizer *TechTrees_DataList_Units_Buttons_Units;
	wxGridSizer *TechTrees_DataList_Researches_Buttons_Buildings;
	wxGridSizer *TechTrees_DataList_Researches_Buttons_Units;
	wxGridSizer *TechTrees_DataList_Researches_Buttons_Researches;
	wxButton *TechTrees_DataList_Ages_Add_Buildings;
	wxButton *TechTrees_DataList_Ages_Add_Units;
	wxButton *TechTrees_DataList_Ages_Add_Researches;
	wxButton *TechTrees_DataList_Buildings_Add_Buildings;
	wxButton *TechTrees_DataList_Buildings_Add_Units;
	wxButton *TechTrees_DataList_Buildings_Add_Researches;
	wxButton *TechTrees_DataList_Units_Add_Units;
	wxButton *TechTrees_DataList_Researches_Add_Buildings;
	wxButton *TechTrees_DataList_Researches_Add_Units;
	wxButton *TechTrees_DataList_Researches_Add_Researches;
	wxButton *TechTrees_DataList_Ages_Insert_Buildings;
	wxButton *TechTrees_DataList_Ages_Insert_Units;
	wxButton *TechTrees_DataList_Ages_Insert_Researches;
	wxButton *TechTrees_DataList_Buildings_Insert_Buildings;
	wxButton *TechTrees_DataList_Buildings_Insert_Units;
	wxButton *TechTrees_DataList_Buildings_Insert_Researches;
	wxButton *TechTrees_DataList_Units_Insert_Units;
	wxButton *TechTrees_DataList_Researches_Insert_Buildings;
	wxButton *TechTrees_DataList_Researches_Insert_Units;
	wxButton *TechTrees_DataList_Researches_Insert_Researches;
	wxButton *TechTrees_DataList_Ages_Delete_Buildings;
	wxButton *TechTrees_DataList_Ages_Delete_Units;
	wxButton *TechTrees_DataList_Ages_Delete_Researches;
	wxButton *TechTrees_DataList_Buildings_Delete_Buildings;
	wxButton *TechTrees_DataList_Buildings_Delete_Units;
	wxButton *TechTrees_DataList_Buildings_Delete_Researches;
	wxButton *TechTrees_DataList_Units_Delete_Units;
	wxButton *TechTrees_DataList_Researches_Delete_Buildings;
	wxButton *TechTrees_DataList_Researches_Delete_Units;
	wxButton *TechTrees_DataList_Researches_Delete_Researches;
	wxButton *TechTrees_DataList_Ages_Copy_Buildings;
	wxButton *TechTrees_DataList_Ages_Copy_Units;
	wxButton *TechTrees_DataList_Ages_Copy_Researches;
	wxButton *TechTrees_DataList_Buildings_Copy_Buildings;
	wxButton *TechTrees_DataList_Buildings_Copy_Units;
	wxButton *TechTrees_DataList_Buildings_Copy_Researches;
	wxButton *TechTrees_DataList_Units_Copy_Units;
	wxButton *TechTrees_DataList_Researches_Copy_Buildings;
	wxButton *TechTrees_DataList_Researches_Copy_Units;
	wxButton *TechTrees_DataList_Researches_Copy_Researches;
	wxButton *TechTrees_DataList_Ages_Paste_Buildings;
	wxButton *TechTrees_DataList_Ages_Paste_Units;
	wxButton *TechTrees_DataList_Ages_Paste_Researches;
	wxButton *TechTrees_DataList_Buildings_Paste_Buildings;
	wxButton *TechTrees_DataList_Buildings_Paste_Units;
	wxButton *TechTrees_DataList_Buildings_Paste_Researches;
	wxButton *TechTrees_DataList_Units_Paste_Units;
	wxButton *TechTrees_DataList_Researches_Paste_Buildings;
	wxButton *TechTrees_DataList_Researches_Paste_Units;
	wxButton *TechTrees_DataList_Researches_Paste_Researches;
	wxButton *TechTrees_DataList_Ages_PasteInsert_Buildings;
	wxButton *TechTrees_DataList_Ages_PasteInsert_Units;
	wxButton *TechTrees_DataList_Ages_PasteInsert_Researches;
	wxButton *TechTrees_DataList_Buildings_PasteInsert_Buildings;
	wxButton *TechTrees_DataList_Buildings_PasteInsert_Units;
	wxButton *TechTrees_DataList_Buildings_PasteInsert_Researches;
	wxButton *TechTrees_DataList_Units_PasteInsert_Units;
	wxButton *TechTrees_DataList_Researches_PasteInsert_Buildings;
	wxButton *TechTrees_DataList_Researches_PasteInsert_Units;
	wxButton *TechTrees_DataList_Researches_PasteInsert_Researches;
	wxButton *TechTrees_DataList_Ages_CopyToAges_Buildings;
	wxButton *TechTrees_DataList_Ages_CopyToAges_Units;
	wxButton *TechTrees_DataList_Ages_CopyToAges_Researches;
	wxButton *TechTrees_DataList_Buildings_CopyToBuildings_Buildings;
	wxButton *TechTrees_DataList_Buildings_CopyToBuildings_Units;
	wxButton *TechTrees_DataList_Buildings_CopyToBuildings_Researches;
	wxButton *TechTrees_DataList_Units_CopyToUnits_Units;
	wxButton *TechTrees_DataList_Researches_CopyToResearches_Buildings;
	wxButton *TechTrees_DataList_Researches_CopyToResearches_Units;
	wxButton *TechTrees_DataList_Researches_CopyToResearches_Researches;

	wxBoxSizer *TechTrees_Ages_Holder_Unknown1;
	wxStaticText *TechTrees_Ages_Text_Unknown1;
	TextCtrl_Long *TechTrees_Ages_Unknown1;
	wxBoxSizer *TechTrees_Ages_Holder_ID;
	wxStaticText *TechTrees_Ages_Text_ID;
	TextCtrl_Long *TechTrees_Ages_ID;
	wxBoxSizer *TechTrees_Ages_Holder_Unknown2;
	wxStaticText *TechTrees_Ages_Text_Unknown2;
	TextCtrl_Byte *TechTrees_Ages_Unknown2;
	wxBoxSizer *TechTrees_Ages_Holder_Building;
	TextCtrl_Long *TechTrees_Ages_Building;
	ComboBox_Plus1 *TechTrees_Ages_ComboBox_Building;
	wxBoxSizer *TechTrees_Ages_Holder_Unit;
	TextCtrl_Long *TechTrees_Ages_Unit;
	ComboBox_Plus1 *TechTrees_Ages_ComboBox_Unit;
	wxBoxSizer *TechTrees_Ages_Holder_Research;
	TextCtrl_Long *TechTrees_Ages_Research;
	ComboBox_Plus1 *TechTrees_Ages_ComboBox_Research;
	wxBoxSizer *TechTrees_Ages_Holder_Unknown3;
	wxStaticText *TechTrees_Ages_Text_Unknown3;
	TextCtrl_Long *TechTrees_Ages_Unknown3;
	wxBoxSizer *TechTrees_Ages_Holder_Unknown4;
	wxStaticText *TechTrees_Ages_Text_Unknown4;
	TextCtrl_Long *TechTrees_Ages_Unknown4;
	wxBoxSizer *TechTrees_Ages_Holder_Zeroes;
	wxGridSizer *TechTrees_Ages_Grid_Zeroes1;
	wxGridSizer *TechTrees_Ages_Grid_Zeroes2;
	wxStaticText *TechTrees_Ages_Text_Zeroes;
	TextCtrl_Short *TechTrees_Ages_Zeroes1[49];
	TextCtrl_Short *TechTrees_Ages_Zeroes2[50];

	wxBoxSizer *TechTrees_Buildings_Holder_ID;
	wxStaticText *TechTrees_Buildings_Text_ID;
	TextCtrl_Long *TechTrees_Buildings_ID;
	ComboBox_Plus1 *TechTrees_Buildings_ComboBox_ID;
	wxBoxSizer *TechTrees_Buildings_Holder_Always2;
	wxStaticText *TechTrees_Buildings_Text_Always2;
	TextCtrl_Byte *TechTrees_Buildings_Always2;
	wxBoxSizer *TechTrees_Buildings_Holder_Building;
	TextCtrl_Long *TechTrees_Buildings_Building;
	ComboBox_Plus1 *TechTrees_Buildings_ComboBox_Building;
	wxBoxSizer *TechTrees_Buildings_Holder_Unit;
	TextCtrl_Long *TechTrees_Buildings_Unit;
	ComboBox_Plus1 *TechTrees_Buildings_ComboBox_Unit;
	wxBoxSizer *TechTrees_Buildings_Holder_Research;
	TextCtrl_Long *TechTrees_Buildings_Research;
	ComboBox_Plus1 *TechTrees_Buildings_ComboBox_Research;

	wxBoxSizer *TechTrees_Buildings_Holder_RequiredResearches;
	wxStaticText *TechTrees_Buildings_Text_RequiredResearches;
	TextCtrl_Long *TechTrees_Buildings_RequiredResearches;
	wxBoxSizer *TechTrees_Buildings_Holder_Age;
	wxStaticText *TechTrees_Buildings_Text_Age;
	TextCtrl_Long *TechTrees_Buildings_Age;
	wxBoxSizer *TechTrees_Buildings_Holder_UnitOrResearch1;
	wxStaticText *TechTrees_Buildings_Text_UnitOrResearch1;
	TextCtrl_Long *TechTrees_Buildings_UnitOrResearch1;
	wxBoxSizer *TechTrees_Buildings_Holder_UnitOrResearch2;
	wxStaticText *TechTrees_Buildings_Text_UnitOrResearch2;
	TextCtrl_Long *TechTrees_Buildings_UnitOrResearch2;
	wxBoxSizer *TechTrees_Buildings_Holder_Unknown2a;
	wxGridSizer *TechTrees_Buildings_Grid_Unknown2a1;
	wxGridSizer *TechTrees_Buildings_Grid_Unknown2a2;
	wxStaticText *TechTrees_Buildings_Text_Unknown2a;
	TextCtrl_Long *TechTrees_Buildings_Unknown2a1[8];
	TextCtrl_Long *TechTrees_Buildings_Unknown2a2[10];
	wxBoxSizer *TechTrees_Holder_UnitAndResearch1;
	wxBoxSizer *TechTrees_Holder_UnitAndResearch2;
	wxBoxSizer *TechTrees_Holder_UnitAndResearch3;
	wxBoxSizer *TechTrees_Holder_UnitAndResearch4;
	wxOwnerDrawnComboBox *TechTrees_ComboBox_Modes[4];
	ComboBox_Plus1 *TechTrees_ComboBox_Unit[4];
	ComboBox_Plus1 *TechTrees_ComboBox_Research[4];
	wxBoxSizer *TechTrees_Buildings_Holder_Mode1;
	wxStaticText *TechTrees_Buildings_Text_Mode1;
	TextCtrl_Long *TechTrees_Buildings_Mode1;
	wxBoxSizer *TechTrees_Buildings_Holder_Mode2;
	wxStaticText *TechTrees_Buildings_Text_Mode2;
	TextCtrl_Long *TechTrees_Buildings_Mode2;
	wxBoxSizer *TechTrees_Buildings_Holder_Unknown2b;
	wxGridSizer *TechTrees_Buildings_Grid_Unknown2b1;
	wxGridSizer *TechTrees_Buildings_Grid_Unknown2b2;
	wxStaticText *TechTrees_Buildings_Text_Unknown2b;
	TextCtrl_Long *TechTrees_Buildings_Unknown2b1[7];
	TextCtrl_Long *TechTrees_Buildings_Unknown2b2[10];

	wxBoxSizer *TechTrees_Buildings_Holder_Unknown3;
	wxGridSizer *TechTrees_Buildings_Grid_Unknown3;
	wxStaticText *TechTrees_Buildings_Text_Unknown3;
	TextCtrl_Byte *TechTrees_Buildings_Unknown3[11];
	wxBoxSizer *TechTrees_Buildings_Holder_Connections;
	wxStaticText *TechTrees_Buildings_Text_Connections;
	TextCtrl_Long *TechTrees_Buildings_Connections;
	wxBoxSizer *TechTrees_Buildings_Holder_EnablingResearch;
	wxStaticText *TechTrees_Buildings_Text_EnablingResearch;
	TextCtrl_Long *TechTrees_Buildings_EnablingResearch;
	ComboBox_Plus1 *TechTrees_Buildings_ComboBox_EnablingResearch;

	wxBoxSizer *TechTrees_Units_Holder_ID;
	wxStaticText *TechTrees_Units_Text_ID;
	TextCtrl_Long *TechTrees_Units_ID;
	ComboBox_Plus1 *TechTrees_Units_ComboBox_ID;
	wxBoxSizer *TechTrees_Units_Holder_Always2;
	wxStaticText *TechTrees_Units_Text_Always2;
	TextCtrl_Byte *TechTrees_Units_Always2;
	wxBoxSizer *TechTrees_Units_Holder_UpperBuilding;
	wxStaticText *TechTrees_Units_Text_UpperBuilding;
	TextCtrl_Long *TechTrees_Units_UpperBuilding;
	ComboBox_Plus1 *TechTrees_Units_ComboBox_UpperBuilding;

	wxBoxSizer *TechTrees_Units_Holder_RequiredResearches;
	wxStaticText *TechTrees_Units_Text_RequiredResearches;
	TextCtrl_Long *TechTrees_Units_RequiredResearches;
	wxBoxSizer *TechTrees_Units_Holder_Age;
	wxStaticText *TechTrees_Units_Text_Age;
	TextCtrl_Long *TechTrees_Units_Age;
	wxBoxSizer *TechTrees_Units_Holder_UnitOrResearch1;
	wxStaticText *TechTrees_Units_Text_UnitOrResearch1;
	TextCtrl_Long *TechTrees_Units_UnitOrResearch1;
	wxBoxSizer *TechTrees_Units_Holder_UnitOrResearch2;
	wxStaticText *TechTrees_Units_Text_UnitOrResearch2;
	TextCtrl_Long *TechTrees_Units_UnitOrResearch2;
	wxBoxSizer *TechTrees_Units_Holder_Unknown2a;
	wxGridSizer *TechTrees_Units_Grid_Unknown2a1;
	wxGridSizer *TechTrees_Units_Grid_Unknown2a2;
	wxStaticText *TechTrees_Units_Text_Unknown2a;
	TextCtrl_Long *TechTrees_Units_Unknown2a1[8];
	TextCtrl_Long *TechTrees_Units_Unknown2a2[10];
	wxBoxSizer *TechTrees_Units_Holder_Mode1;
	wxStaticText *TechTrees_Units_Text_Mode1;
	TextCtrl_Long *TechTrees_Units_Mode1;
	wxBoxSizer *TechTrees_Units_Holder_Mode2;
	wxStaticText *TechTrees_Units_Text_Mode2;
	TextCtrl_Long *TechTrees_Units_Mode2;
	wxBoxSizer *TechTrees_Units_Holder_Unknown2b;
	wxGridSizer *TechTrees_Units_Grid_Unknown2b1;
	wxGridSizer *TechTrees_Units_Grid_Unknown2b2;
	wxStaticText *TechTrees_Units_Text_Unknown2b;
	TextCtrl_Long *TechTrees_Units_Unknown2b1[7];
	TextCtrl_Long *TechTrees_Units_Unknown2b2[10];
	wxBoxSizer *TechTrees_Units_Holder_VerticalLine;
	wxStaticText *TechTrees_Units_Text_VerticalLine;
	TextCtrl_Long *TechTrees_Units_VerticalLine;

	wxBoxSizer *TechTrees_Units_Holder_Unit;
	TextCtrl_Long *TechTrees_Units_Unit;
	ComboBox_Plus1 *TechTrees_Units_ComboBox_Unit;
	wxBoxSizer *TechTrees_Units_Holder_LocationInAge;
	wxStaticText *TechTrees_Units_Text_LocationInAge;
	TextCtrl_Long *TechTrees_Units_LocationInAge;
	wxBoxSizer *TechTrees_Units_Holder_RequiredResearch;
	wxStaticText *TechTrees_Units_Text_RequiredResearch;
	TextCtrl_Long *TechTrees_Units_RequiredResearch;
	ComboBox_Plus1 *TechTrees_Units_ComboBox_RequiredResearch;
	wxBoxSizer *TechTrees_Units_Holder_LineMode;
	wxStaticText *TechTrees_Units_Text_LineMode;
	TextCtrl_Long *TechTrees_Units_LineMode;
	wxBoxSizer *TechTrees_Units_Holder_EnablingResearch;
	wxStaticText *TechTrees_Units_Text_EnablingResearch;
	TextCtrl_Long *TechTrees_Units_EnablingResearch;
	ComboBox_Plus1 *TechTrees_Units_ComboBox_EnablingResearch;

	wxBoxSizer *TechTrees_Researches_Holder_ID;
	wxStaticText *TechTrees_Researches_Text_ID;
	TextCtrl_Long *TechTrees_Researches_ID;
	ComboBox_Plus1 *TechTrees_Researches_ComboBox_ID;
	wxBoxSizer *TechTrees_Researches_Holder_Always2;
	wxStaticText *TechTrees_Researches_Text_Always2;
	TextCtrl_Byte *TechTrees_Researches_Always2;
	wxBoxSizer *TechTrees_Researches_Holder_UpperBuilding;
	wxStaticText *TechTrees_Researches_Text_UpperBuilding;
	TextCtrl_Long *TechTrees_Researches_UpperBuilding;
	ComboBox_Plus1 *TechTrees_Researches_ComboBox_UpperBuilding;
	wxBoxSizer *TechTrees_Researches_Holder_Building;
	TextCtrl_Long *TechTrees_Researches_Building;
	ComboBox_Plus1 *TechTrees_Researches_ComboBox_Building;
	wxBoxSizer *TechTrees_Researches_Holder_Unit;
	TextCtrl_Long *TechTrees_Researches_Unit;
	ComboBox_Plus1 *TechTrees_Researches_ComboBox_Unit;
	wxBoxSizer *TechTrees_Researches_Holder_Research;
	TextCtrl_Long *TechTrees_Researches_Research;
	ComboBox_Plus1 *TechTrees_Researches_ComboBox_Research;

	wxBoxSizer *TechTrees_Researches_Holder_RequiredResearches;
	wxStaticText *TechTrees_Researches_Text_RequiredResearches;
	TextCtrl_Long *TechTrees_Researches_RequiredResearches;
	wxBoxSizer *TechTrees_Researches_Holder_Age;
	wxStaticText *TechTrees_Researches_Text_Age;
	TextCtrl_Long *TechTrees_Researches_Age;
	wxBoxSizer *TechTrees_Researches_Holder_UpperResearch;
	wxStaticText *TechTrees_Researches_Text_UpperResearch;
	TextCtrl_Long *TechTrees_Researches_UpperResearch;
	ComboBox_Plus1 *TechTrees_Researches_ComboBox_UpperResearch;
	wxBoxSizer *TechTrees_Researches_Holder_Unknown2a;
	wxGridSizer *TechTrees_Researches_Grid_Unknown2a1;
	wxGridSizer *TechTrees_Researches_Grid_Unknown2a2;
	wxStaticText *TechTrees_Researches_Text_Unknown2a;
	TextCtrl_Long *TechTrees_Researches_Unknown2a1[9];
	TextCtrl_Long *TechTrees_Researches_Unknown2a2[10];
	wxBoxSizer *TechTrees_Researches_Holder_LineMode;
	wxStaticText *TechTrees_Researches_Text_LineMode;
	TextCtrl_Long *TechTrees_Researches_LineMode;
	wxBoxSizer *TechTrees_Researches_Holder_Unknown2b;
	wxGridSizer *TechTrees_Researches_Grid_Unknown2b1;
	wxGridSizer *TechTrees_Researches_Grid_Unknown2b2;
	wxStaticText *TechTrees_Researches_Text_Unknown2b;
	TextCtrl_Long *TechTrees_Researches_Unknown2b1[8];
	TextCtrl_Long *TechTrees_Researches_Unknown2b2[10];
	wxBoxSizer *TechTrees_Researches_Holder_VerticalLine;
	wxStaticText *TechTrees_Researches_Text_VerticalLine;
	TextCtrl_Long *TechTrees_Researches_VerticalLine;
	wxBoxSizer *TechTrees_Researches_Holder_LocationInAge;
	wxStaticText *TechTrees_Researches_Text_LocationInAge;
	TextCtrl_Long *TechTrees_Researches_LocationInAge;
	wxBoxSizer *TechTrees_Researches_Holder_Unknown9;
	wxStaticText *TechTrees_Researches_Text_Unknown9;
	TextCtrl_Long *TechTrees_Researches_Unknown9;

//	DRS user interface

	/*genie::DrsFile *ResourceFile;

	void LoadDRSFile(wxCommandEvent &Event);
	void UnLoadDRSFile(wxCommandEvent &Event);
	void LoadSLP(wxCommandEvent &Event);

	wxBoxSizer *DRS_Main;
	wxBoxSizer *DRS_TopRow;
	wxBoxSizer *DRS_MidArea;

	wxStaticText *DRS_Text_FileLocation;
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
