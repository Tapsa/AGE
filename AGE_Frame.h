#pragma once

// External headers
#include <array>
#include <chrono>
#include <functional>
#include <string>
#include <wx/clrpicker.h>
#include <wx/dcbuffer.h>
#include <wx/frame.h>
#include <wx/msgdlg.h>
#include <wx/notebook.h>
#include <wx/radiobox.h>
#include <wx/wrapsizer.h>

// Project headers
#include "BaseMainFrame.h"
#include "CustomComboBoxes.h"
#include "CustomTextControls.h"
#include "CustomWidgets.h"
#include "DataCopies.hpp"
#include "DelayedMessageRelay.h"
#include "LinkedCheckBox.h"
#include "Sprites.h"

// Subproject headers
#include "genie/lang/LangFile.h"
#include "genie/resource/DrsFile.h"
#include "genie/resource/SlpFile.h"
#include "genie/resource/SmpFile.h"
#include "genie/resource/SmxFile.h"

#ifndef WIN32
#define HINSTANCE ssize_t
#endif

const unsigned short maxStringlength = 0x7FFF;

class AGE_Frame;
class AGE_List32Box
{
private:
    wxGridSizer *Buttons;

public:
    wxStaticBoxSizer *ItemList;
    wxTextCtrl *Search, *SearchRecursive;
    ProperList *List;
    AGETextCtrl *Item;
    LinkedComboBox *ItemCombo;
    wxButton *Add, *Insert, *Delete, *Copy, *Paste, *PasteInsert, *CopyAllToSelected;

    void CreateControls(AGE_Frame *frame, DelayedMessageRelay *popUp, AScrolled *scroller, const wxString &itemName,
        const wxString &listName, wxArrayString *choices);
};

class AGE_AreaTT84
{
private:
    wxGridSizer *Buttons;
    wxBoxSizer *ItemList, *UsedItems_H, *Item_H;
    SolidText *UsedItems_T;

public:
    wxStaticBoxSizer *Area;
    wxTextCtrl *Search, *SearchRecursive;
    ProperList *List;
    AGETextCtrl *Item, *Mode, *UsedItems;
    LinkedComboBox *ItemCombo;
    AGEComboBox *ModeCombo;
    wxButton *Copy, *Paste, *CopyAllToSelected;

    void CreateControls(AGE_Frame *frame, DelayedMessageRelay *popUp, AScrolled *scroller, const wxString &itemName,
        wxArrayString *choices);
};

class AGE_AreaTT31020
{
private:
    wxGridSizer *Buttons;
    wxBoxSizer *ItemList, *UsedItems_H, *Unknowns_H, *Unknown_H, *Top;
    SolidText *UsedItems_T, *Unknown_T;

public:
    wxStaticBoxSizer *Area;
    wxTextCtrl *Search, *SearchRecursive;
    ProperList *List;
    AGETextCtrl *Unknown1, *Unknown2, *UsedItems, *Unknown;
    wxButton *Copy, *Paste, *CopyAllToSelected;

    void CreateControls(AGE_Frame *frame, DelayedMessageRelay *popUp, AScrolled *scroller);
};

class Loader : public wxThread
{
public:
    Loader(AGE_Frame *frame, genie::Terrain *tp) :
        wxThread()
    {
        HostFrame = frame;
        TerrainPointer = tp;
    }
    ~Loader();

private:
    genie::Terrain *TerrainPointer;

protected:
    virtual ExitCode Entry();
    AGE_Frame *HostFrame;
};

class AGE_Frame : public BaseMainFrame
{
public:
    AGE_Frame(const wxString &title, short window, wxString aP = wxEmptyString);

    void FixSize(float scale);
    inline wxSize ASize(int x, int y) const
    {
        return wxSize(x * displayScaling, y * displayScaling);
    }

    struct Pixels
    {
        float x1, y1, x2, y2, x3, y3, x4, y4;
    };

    std::ofstream log_out;

    void OnOpen(wxCommandEvent &event) override;
    void OnExit(wxCloseEvent &event) override;

private:
//  Constructions Methods

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

//  Other Events

    bool DataOpened = false;
    bool SaveLang();
    bool SaveLangX1();
    bool SaveLangX1P1();
    void FillListsBasedOnGameVersion();
    void LoadLists();
    void OnGameVersionChange();
    void OnSave(wxCommandEvent &event);
    void OnMenuOption(wxCommandEvent &event);
    void OnAnimationMenuOption(wxCommandEvent &event);
    void OnAutoCopy(wxCommandEvent &event);
    void OnExitSLP(wxCloseEvent &event);
    void OnFrameButton(wxCommandEvent &event);
    void OnFrameMouse(wxMouseEvent &event);
    void LoadTerrainFromSLPs(genie::Terrain *TerrainPointer)
    {
        TerrainLoader = new Loader(this, TerrainPointer);
        TerrainLoader->Create(); // Not needed in wxWidgets 3+
        if(TerrainLoader->Run() != wxTHREAD_NO_ERROR)
        {
            delete TerrainLoader;
            TerrainLoader = 0;
        }
    }
    void OnFrameKey(wxKeyEvent &event);

//  Updates user interface after changing data name.

    void OnSelection_SearchFilters(wxCommandEvent &event);
    void OnKillFocus_LangDLL(wxFocusEvent &event);

    void OnKillFocus_Research(wxFocusEvent &event);
    void OnKillFocus_Techs(wxFocusEvent &event);
    void OnKillFocus_Effects89(wxFocusEvent &event);
    void OnKillFocus_Graphics(wxFocusEvent &event);
    void OnKillFocus_Borders(wxFocusEvent &event);
    void OnKillFocus_TerRestrict(wxFocusEvent &event);
    void OnKillFocus_Sounds(wxFocusEvent &event);
    void OnKillFocus_Colors(wxFocusEvent &event);

    void OnEnter_Research(wxCommandEvent &event);
    void OnEnter_Techs(wxCommandEvent &event);
    void OnEnter_Effects89(wxCommandEvent &event);
    void OnEnter_Graphics(wxCommandEvent &event);
    void OnEnter_Borders(wxCommandEvent &event);
    void OnEnter_TerRestrict(wxCommandEvent &event);
    void OnEnter_Sounds(wxCommandEvent &event);
    void OnEnter_Colors(wxCommandEvent &event);

    void UpdateEffects89(bool forced);
    int32_t CombineEffects89(uint16_t type, int16_t amount);
    void UpdateGraphicsView(void);

    void OnUpdateCheck_Techs(wxCommandEvent &event);
    void OnUpdateCombo_Techs(wxCommandEvent &event);
    void OnUpdateCombo_Units(wxCommandEvent &event);
    void OnUpdateCombo_UnitLines(wxCommandEvent &event);
    void OnUpdateCombo_Graphics(wxCommandEvent &event);
    void OnUpdateCombo_Terrains(wxCommandEvent &event);

//  Other Methods

    void InitSearch(const wxString &yes, const wxString &no);
    bool initArt(AGE_SLP&, unsigned);
    void initSounds(AGE_SLP&, unsigned, size_t);
    void ReloadAngles();
    void ResizeAngles();
    wxTimer animater;
    wxArrayString SearchYes, SearchNo, soundfolders;
    wxString FormatFloat(float);
    wxString FormatInt(int);
    wxString FormatUnsigned(unsigned);
    wxString CurrentTime();
    wxArrayString TerrainRestrictionNames;
    wxArrayString CivilizationResourceNames;
    void SaveBackup();
    bool SearchMatches(const wxString &hay);
    void getSelectedItems(const size_t selections, const ProperList *list, std::vector<int> &indexes);
    void RefreshList(ProperList *list, std::vector<int> *oldies = 0);
    void UnitLangDLLConverter(wxCommandEvent &event);
    void ResearchLangDLLConverter(wxCommandEvent &event);
    void SearchAllSubVectors(ProperList *list, wxTextCtrl *topSearch, wxTextCtrl *subSearch);
    void LoadAllEffects(wxCommandEvent &event);
    void ClearAllEffects(wxCommandEvent &event);
    void OnAllEffectSelect(wxCommandEvent &event);
    void LoadAllSoundFiles(wxCommandEvent &event);
    void ClearAllSoundFiles(wxCommandEvent &event);
    void OnAllSoundFileSelect(wxCommandEvent &event);
    bool Paste11Check(size_t numPastes, size_t numCopies);
    void OnDrawIconSLP(wxPaintEvent &event);
    void OnDrawGraphicSLP(wxPaintEvent &event);
    void CalcDrawCenter(wxWindowBase*, int&, int&);
    void CalcAngle(AGE_SLP&);
    void SetDisplayBearings(AGE_SLP&, const genie::GraphicDelta&);
    void OnDrawTechSLP(wxPaintEvent &event);
    void OnDrawBorderSLP(wxPaintEvent &event);
    void OnDrawPalette(wxPaintEvent &event);
    void OnGraphicAnim(wxTimerEvent &event);
    int ShouldAnimate(AGE_SLP&, bool&);
    void Listen(AGE_SLP&);
    void ChooseNextFrame(AGE_SLP&, bool&);
    void ChoosePreviousFrame(AGE_SLP&, bool&);
    void HandleLastFrame(const uint16_t, bool, unsigned);
    int loadChosenGraphic(unsigned int unitID);
    void AddAnnexAndStackGraphics(unsigned int unitID, int offsetX = 0, int offsetY = 0, int apply = 0);
    void CalcAnnexCoords(const genie::unit::BuildingAnnex *annex);
    void DrawGraphics(wxBufferedPaintDC&, AGE_SLPs&, int, int);
    void DrawAngle(wxBufferedPaintDC&, int, int, int, int);
    bool loadPalette(const wxString &folder);
    void addFilesToRead(const wxArrayString &files, const wxString &folder);
    void addDRSFolders4SLPs(wxArrayString &folders, const wxString &folder);
    void addSLPFolders4SLPs(wxArrayString &folders, wxString folder);
    void setForeAndBackColors(AGETextCtrl *box, wxColour color);
    void OnChooseGraphic(wxCommandEvent&);
    void playWAV(wxCommandEvent &event);
    AGE_SLPs* getCurrentGraphics();
    int produceRecentValues(wxArrayString&, std::vector<wxArrayString>&);
    void autoOdds(wxCommandEvent &event);
    void autoDrsIncrement(wxCommandEvent &event);
    void copySoundsFromCivToCiv(wxCommandEvent &event);
    void tileToPixels(float sizeX, float sizeY, Pixels &p, int centerX, int centerY);

//  General Events

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
    void InitTerrainBlends();
    void InitRandomMaps();

    void ListMapData();
    void OnMapsRefresh(wxCommandEvent &event);
    void OnVariableCalc(wxFocusEvent &event);
    void OnVariableCalcReverse(wxFocusEvent &event);

    void ListRandomMaps();
    void OnRandomMapSearch(wxCommandEvent &event);
    void OnRandomMapSelect(wxCommandEvent &event);
    void OnRandomMapAdd(wxCommandEvent &event);
    void OnRandomMapInsert(wxCommandEvent &event);
    void OnRandomMapDelete(wxCommandEvent &event);
    void OnRandomMapCopy(wxCommandEvent &event);
    void OnRandomMapPaste(wxCommandEvent &event);
    void OnRandomMapPasteInsert(wxCommandEvent &event);
    wxString GetRandomMapName(int);

    void ListMapLands();
    void OnMapLandSearch(wxCommandEvent &event);
    void OnMapLandSelect(wxCommandEvent &event);
    void OnMapLandAdd(wxCommandEvent &event);
    void OnMapLandInsert(wxCommandEvent &event);
    void OnMapLandDelete(wxCommandEvent &event);
    void OnMapLandCopy(wxCommandEvent &event);
    void OnMapLandPaste(wxCommandEvent &event);
    void OnMapLandPasteInsert(wxCommandEvent &event);
    void OnMapLandCopyToMaps(wxCommandEvent &event);
    wxString GetMapLandName(int);

    void ListMapTerrains();
    void OnMapTerrainSearch(wxCommandEvent &event);
    void OnMapTerrainSelect(wxCommandEvent &event);
    void OnMapTerrainAdd(wxCommandEvent &event);
    void OnMapTerrainInsert(wxCommandEvent &event);
    void OnMapTerrainDelete(wxCommandEvent &event);
    void OnMapTerrainCopy(wxCommandEvent &event);
    void OnMapTerrainPaste(wxCommandEvent &event);
    void OnMapTerrainPasteInsert(wxCommandEvent &event);
    void OnMapTerrainCopyToMaps(wxCommandEvent &event);
    wxString GetMapTerrainName(int);

    void ListMapUnits();
    void OnMapUnitSearch(wxCommandEvent &event);
    void OnMapUnitSelect(wxCommandEvent &event);
    void OnMapUnitAdd(wxCommandEvent &event);
    void OnMapUnitInsert(wxCommandEvent &event);
    void OnMapUnitDelete(wxCommandEvent &event);
    void OnMapUnitCopy(wxCommandEvent &event);
    void OnMapUnitPaste(wxCommandEvent &event);
    void OnMapUnitPasteInsert(wxCommandEvent &event);
    void OnMapUnitCopyToMaps(wxCommandEvent &event);

    void ListMapElevations();
    void OnMapElevationSearch(wxCommandEvent &event);
    void OnMapElevationSelect(wxCommandEvent &event);
    void OnMapElevationAdd(wxCommandEvent &event);
    void OnMapElevationInsert(wxCommandEvent &event);
    void OnMapElevationDelete(wxCommandEvent &event);
    void OnMapElevationCopy(wxCommandEvent &event);
    void OnMapElevationPaste(wxCommandEvent &event);
    void OnMapElevationPasteInsert(wxCommandEvent &event);
    void OnMapElevationCopyToMaps(wxCommandEvent &event);

//  Research Events

    void ListResearches(bool all = true);
    void OnResearchSearch(wxCommandEvent &event);
    void OnResearchSelect(wxCommandEvent &event);
    void OnResearchAdd(wxCommandEvent &event);
    void OnResearchInsert(wxCommandEvent &event);
    void OnResearchDelete(wxCommandEvent &event);
    void OnResearchCopy(wxCommandEvent &event);
    void OnResearchPaste(wxCommandEvent &event);
    void OnResearchPasteInsert(wxCommandEvent &event);
    wxString GetResearchName(int, bool = false);
    void PrepTechSearch();

//  Tech Events

    void ListEffects(bool all = true);
    void OnEffectSearch(wxCommandEvent &event);
    void OnEffectSelect(wxCommandEvent &event);
    void OnEffectAdd(wxCommandEvent &event);
    void OnEffectInsert(wxCommandEvent &event);
    void OnEffectDelete(wxCommandEvent &event);
    void OnEffectCopy(wxCommandEvent &event);
    void OnEffectPaste(wxCommandEvent &event);
    void OnEffectPasteInsert(wxCommandEvent &event);
    void OnEffectRename(wxCommandEvent &event);
    void OnEffectRenameGE2(wxCommandEvent &event);
    wxString GetEffectName(int);

    void ListEffectCmds();
    void OnEffectCmdSearch(wxCommandEvent &event);
    void OnEffectCmdSelect(wxCommandEvent &event);
    void OnEffectCmdAdd(wxCommandEvent &event);
    void OnEffectCmdInsert(wxCommandEvent &event);
    void OnEffectCmdDelete(wxCommandEvent &event);
    void OnEffectCmdCopy(wxCommandEvent &event);
    void OnEffectCmdPaste(wxCommandEvent &event);
    void OnEffectCmdPasteInsert(wxCommandEvent &event);
    void OnEffectCmdCopyToTechs(wxCommandEvent &event);
    inline wxString Tester(genie::EffectCommand, wxString);
    wxString GetEffectCmdName(int, int);

    void (*SetEffectTypeChoice)(LinkedComboBox *, short) = [](LinkedComboBox *, short) {};
    void (*SetEffectAttributeChoice)(LinkedComboBox *, short) = [](LinkedComboBox *, short) {};
    void (*OnChooseEffectType)(AGETextCtrl *, unsigned) = [](AGETextCtrl *, unsigned) {};
    void (*OnChooseEffectAttribute)(AGETextCtrl *, unsigned) = [](AGETextCtrl *, unsigned) {};

//  Tech Tree Events

    void ListTTAges();
    void OnTTAgesSearch(wxCommandEvent &event);
    void OnTTAgeSelect(wxCommandEvent &event);
    void OnTTAgesAdd(wxCommandEvent &event);
    void OnTTAgesInsert(wxCommandEvent &event);
    void OnTTAgesDelete(wxCommandEvent &event);
    void OnTTAgesCopy(wxCommandEvent &event);
    void OnTTAgesPaste(wxCommandEvent &event);
    void OnTTAgesPasteInsert(wxCommandEvent &event);
    wxString GetTTAgesName(int);

    void ListTTAgeBuildings();
    void OnTTAgesBuildingSearch(wxCommandEvent &event);
    void OnTTAgesBuildingSelect(wxCommandEvent &event);
    void OnTTAgesBuildingAdd(wxCommandEvent &event);
    void OnTTAgesBuildingInsert(wxCommandEvent &event);
    void OnTTAgesBuildingDelete(wxCommandEvent &event);
    void OnTTAgesBuildingCopy(wxCommandEvent &event);
    void OnTTAgesBuildingPaste(wxCommandEvent &event);
    void OnTTAgesBuildingPasteInsert(wxCommandEvent &event);
    void OnTTAgesBuildingCopyToAges(wxCommandEvent &event);
    wxString GetBuildingName(int);

    void ListTTAgeUnits();
    void OnTTAgesUnitSearch(wxCommandEvent &event);
    void OnTTAgesUnitSelect(wxCommandEvent &event);
    void OnTTAgesUnitAdd(wxCommandEvent &event);
    void OnTTAgesUnitInsert(wxCommandEvent &event);
    void OnTTAgesUnitDelete(wxCommandEvent &event);
    void OnTTAgesUnitCopy(wxCommandEvent &event);
    void OnTTAgesUnitPaste(wxCommandEvent &event);
    void OnTTAgesUnitPasteInsert(wxCommandEvent &event);
    void OnTTAgesUnitCopyToAges(wxCommandEvent &event);

    void ListTTAgeResearches();
    void OnTTAgesResearchSearch(wxCommandEvent &event);
    void OnTTAgesResearchSelect(wxCommandEvent &event);
    void OnTTAgesResearchAdd(wxCommandEvent &event);
    void OnTTAgesResearchInsert(wxCommandEvent &event);
    void OnTTAgesResearchDelete(wxCommandEvent &event);
    void OnTTAgesResearchCopy(wxCommandEvent &event);
    void OnTTAgesResearchPaste(wxCommandEvent &event);
    void OnTTAgesResearchPasteInsert(wxCommandEvent &event);
    void OnTTAgesResearchCopyToAges(wxCommandEvent &event);
    wxString GetSimpleResearchName(int);

    void ListTTAgeItems();
    void OnTTAgeItemSearch(wxCommandEvent &event);
    void OnTTAgeItemSelect(wxCommandEvent &event);
    void OnTTAgeItemCopy(wxCommandEvent &event);
    void OnTTAgeItemPaste(wxCommandEvent &event);
    void OnTTAgeItemCopyToAges(wxCommandEvent &event);

    void ListTTAgeUnknownItems();
    void OnTTAgeUnknownItemSearch(wxCommandEvent &event);
    void OnTTAgeUnknownItemSelect(wxCommandEvent &event);
    void OnTTAgeUnknownItemCopy(wxCommandEvent &event);
    void OnTTAgeUnknownItemPaste(wxCommandEvent &event);
    void OnTTAgeUnknownItemCopyToAges(wxCommandEvent &event);

    void ListTTBuildings();
    void OnTTBuildingSearch(wxCommandEvent &event);
    void OnTTBuildingSelect(wxCommandEvent &event);
    void OnTTBuildingAdd(wxCommandEvent &event);
    void OnTTBuildingInsert(wxCommandEvent &event);
    void OnTTBuildingDelete(wxCommandEvent &event);
    void OnTTBuildingCopy(wxCommandEvent &event);
    void OnTTBuildingPaste(wxCommandEvent &event);
    void OnTTBuildingPasteInsert(wxCommandEvent &event);
    wxString GetTTBuildingName(int, bool = false);
    void PrepTTBuildingSearch();

    void ListTTBuildingBuildings();
    void OnTTBuildingBuildingSearch(wxCommandEvent &event);
    void OnTTBuildingBuildingSelect(wxCommandEvent &event);
    void OnTTBuildingBuildingAdd(wxCommandEvent &event);
    void OnTTBuildingBuildingInsert(wxCommandEvent &event);
    void OnTTBuildingBuildingDelete(wxCommandEvent &event);
    void OnTTBuildingBuildingCopy(wxCommandEvent &event);
    void OnTTBuildingBuildingPaste(wxCommandEvent &event);
    void OnTTBuildingBuildingPasteInsert(wxCommandEvent &event);
    void OnTTBuildingBuildingCopyToBuildings(wxCommandEvent &event);

    void ListTTBuildingUnits();
    void OnTTBuildingUnitSearch(wxCommandEvent &event);
    void OnTTBuildingUnitSelect(wxCommandEvent &event);
    void OnTTBuildingUnitAdd(wxCommandEvent &event);
    void OnTTBuildingUnitInsert(wxCommandEvent &event);
    void OnTTBuildingUnitDelete(wxCommandEvent &event);
    void OnTTBuildingUnitCopy(wxCommandEvent &event);
    void OnTTBuildingUnitPaste(wxCommandEvent &event);
    void OnTTBuildingUnitPasteInsert(wxCommandEvent &event);
    void OnTTBuildingUnitCopyToBuildings(wxCommandEvent &event);

    void ListTTBuildingResearches();
    void OnTTBuildingResearchSearch(wxCommandEvent &event);
    void OnTTBuildingResearchSelect(wxCommandEvent &event);
    void OnTTBuildingResearchAdd(wxCommandEvent &event);
    void OnTTBuildingResearchInsert(wxCommandEvent &event);
    void OnTTBuildingResearchDelete(wxCommandEvent &event);
    void OnTTBuildingResearchCopy(wxCommandEvent &event);
    void OnTTBuildingResearchPaste(wxCommandEvent &event);
    void OnTTBuildingResearchPasteInsert(wxCommandEvent &event);
    void OnTTBuildingResearchCopyToBuildings(wxCommandEvent &event);

    void ListTTBuildingItems();
    void OnTTBuildingItemSearch(wxCommandEvent &event);
    void OnTTBuildingItemSelect(wxCommandEvent &event);
    void OnTTBuildingItemCopy(wxCommandEvent &event);
    void OnTTBuildingItemPaste(wxCommandEvent &event);
    void OnTTBuildingItemCopyToBuildings(wxCommandEvent &event);

    void ListTTUnits();
    void OnTTUnitSearch(wxCommandEvent &event);
    void OnTTUnitSelect(wxCommandEvent &event);
    void OnTTUnitAdd(wxCommandEvent &event);
    void OnTTUnitInsert(wxCommandEvent &event);
    void OnTTUnitDelete(wxCommandEvent &event);
    void OnTTUnitCopy(wxCommandEvent &event);
    void OnTTUnitPaste(wxCommandEvent &event);
    void OnTTUnitPasteInsert(wxCommandEvent &event);
    wxString GetTTUnitName(int, bool = false);
    void PrepTTUnitSearch();

    void ListTTUnitUnits();
    void OnTTUnitUnitSearch(wxCommandEvent &event);
    void OnTTUnitUnitSelect(wxCommandEvent &event);
    void OnTTUnitUnitAdd(wxCommandEvent &event);
    void OnTTUnitUnitInsert(wxCommandEvent &event);
    void OnTTUnitUnitDelete(wxCommandEvent &event);
    void OnTTUnitUnitCopy(wxCommandEvent &event);
    void OnTTUnitUnitPaste(wxCommandEvent &event);
    void OnTTUnitUnitPasteInsert(wxCommandEvent &event);
    void OnTTUnitUnitCopyToUnits(wxCommandEvent &event);

    void ListTTCommonItems(AGE_AreaTT84 &area, genie::techtree::Common *tt_cmn_ptr);
    void SelectTTCommonItems(AGE_AreaTT84 &area, genie::techtree::Common *tt_cmn_ptr);
    void ListTTUnitItems();
    void OnTTUnitItemSearch(wxCommandEvent &event);
    void OnTTUnitItemSelect(wxCommandEvent &event);
    void OnTTUnitItemCopy(wxCommandEvent &event);
    void OnTTUnitItemPaste(wxCommandEvent &event);
    void OnTTUnitItemCopyToUnits(wxCommandEvent &event);

    void ListTTResearches();
    void OnTTResearchSearch(wxCommandEvent &event);
    void OnTTResearchSelect(wxCommandEvent &event);
    void OnTTResearchAdd(wxCommandEvent &event);
    void OnTTResearchInsert(wxCommandEvent &event);
    void OnTTResearchDelete(wxCommandEvent &event);
    void OnTTResearchCopy(wxCommandEvent &event);
    void OnTTResearchPaste(wxCommandEvent &event);
    void OnTTResearchPasteInsert(wxCommandEvent &event);
    wxString GetTTResearchName(int, bool = false);
    void PrepTTResearchSearch();

    void ListTTResearchBuildings();
    void OnTTResearchBuildingSearch(wxCommandEvent &event);
    void OnTTResearchBuildingSelect(wxCommandEvent &event);
    void OnTTResearchBuildingAdd(wxCommandEvent &event);
    void OnTTResearchBuildingInsert(wxCommandEvent &event);
    void OnTTResearchBuildingDelete(wxCommandEvent &event);
    void OnTTResearchBuildingCopy(wxCommandEvent &event);
    void OnTTResearchBuildingPaste(wxCommandEvent &event);
    void OnTTResearchBuildingPasteInsert(wxCommandEvent &event);
    void OnTTResearchBuildingCopyToResearches(wxCommandEvent &event);

    void ListTTResearchUnits();
    void OnTTResearchUnitSearch(wxCommandEvent &event);
    void OnTTResearchUnitSelect(wxCommandEvent &event);
    void OnTTResearchUnitAdd(wxCommandEvent &event);
    void OnTTResearchUnitInsert(wxCommandEvent &event);
    void OnTTResearchUnitDelete(wxCommandEvent &event);
    void OnTTResearchUnitCopy(wxCommandEvent &event);
    void OnTTResearchUnitPaste(wxCommandEvent &event);
    void OnTTResearchUnitPasteInsert(wxCommandEvent &event);
    void OnTTResearchUnitCopyToResearches(wxCommandEvent &event);

    void ListTTResearchResearches();
    void OnTTResearchResearchSearch(wxCommandEvent &event);
    void OnTTResearchResearchSelect(wxCommandEvent &event);
    void OnTTResearchResearchAdd(wxCommandEvent &event);
    void OnTTResearchResearchInsert(wxCommandEvent &event);
    void OnTTResearchResearchDelete(wxCommandEvent &event);
    void OnTTResearchResearchCopy(wxCommandEvent &event);
    void OnTTResearchResearchPaste(wxCommandEvent &event);
    void OnTTResearchResearchPasteInsert(wxCommandEvent &event);
    void OnTTResearchResearchCopyToResearches(wxCommandEvent &event);

    void ListTTResearchItems();
    void OnTTResearchItemSearch(wxCommandEvent &event);
    void OnTTResearchItemSelect(wxCommandEvent &event);
    void OnTTResearchItemCopy(wxCommandEvent &event);
    void OnTTResearchItemPaste(wxCommandEvent &event);
    void OnTTResearchItemCopyToResearches(wxCommandEvent &event);

//  Civilization Events

    void ListCivs(bool all = true);
    void OnCivsSearch(wxCommandEvent &event);
    void OnCivSelect(wxCommandEvent &event);
    void OnCivsAdd(wxCommandEvent &event);
    void OnCivsInsert(wxCommandEvent &event);
    void OnCivsDelete(wxCommandEvent &event);
    void OnCivsCopy(wxCommandEvent &event);
    void OnCivsPaste(wxCommandEvent &event);
    void OnCivsPasteInsert(wxCommandEvent &event);
    wxString GetCivName(int);
    void OnCivCountChange();

    void ListResources(bool all = true);
    void OnResourcesSearch(wxCommandEvent &event);
    void OnResourceSelect(wxCommandEvent &event);
    void OnResourcesAdd(wxCommandEvent &event);
    void OnResourcesInsert(wxCommandEvent &event);
    void OnResourcesDelete(wxCommandEvent &event);
    void OnResourcesCopy(wxCommandEvent &event);
    void OnResourcesPaste(wxCommandEvent &event);
    void OnResourcesPasteInsert(wxCommandEvent &event);
    void OnResourcesCopyToAll(wxCommandEvent &event);
    wxString GetResourceName(size_t);

    void ListUnits(short civ, bool all = true);
    void OnUnitsSearch(wxCommandEvent&); // Convert to local lambda
    void OnUnitSelect(wxCommandEvent &event); // Convert to local lambda
    void UnitsGraphicsCopy(GraphicCopies &store, short civ, short unit);
    void PasteUnits(bool OneOnOne = false);
    short CorrectID(bool OneOnOne, size_t loop);
    void UnitsGraphicsPaste(GraphicCopies &store, short civ, short unit);
    wxString GetUnitName(int, short, bool = false);
    void PrepUnitSearch();

    void ListUnitDamageGraphics();
    void OnUnitDamageGraphicsSearch(wxCommandEvent &event);
    void OnUnitDamageGraphicSelect(wxCommandEvent &event);
    void OnUnitDamageGraphicsAdd(wxCommandEvent &event);
    void OnUnitDamageGraphicsInsert(wxCommandEvent &event);
    void OnUnitDamageGraphicsDelete(wxCommandEvent &event);
    void OnUnitDamageGraphicsCopy(wxCommandEvent &event);
    void OnUnitDamageGraphicsPaste(wxCommandEvent &event);
    void OnUnitDamageGraphicsPasteInsert(wxCommandEvent &event);
    void OnUnitDamageGraphicsCopyToUnits(wxCommandEvent &event);
    wxString GetUnitDamageGraphicName(int);

    void ListUnitDropSites();
    void OnUnitDropSitesSearch(wxCommandEvent &event);
    void OnUnitDropSiteSelect(wxCommandEvent &event);

    void ListUnitAttacks();
    void OnUnitAttacksSearch(wxCommandEvent &event);
    void OnUnitAttackSelect(wxCommandEvent &event);
    void OnUnitAttacksAdd(wxCommandEvent &event);
    void OnUnitAttacksInsert(wxCommandEvent &event);
    void OnUnitAttacksDelete(wxCommandEvent &event);
    void OnUnitAttacksCopy(wxCommandEvent &event);
    void OnUnitAttacksPaste(wxCommandEvent &event);
    void OnUnitAttacksPasteInsert(wxCommandEvent &event);
    void OnUnitAttacksCopyToUnits(wxCommandEvent &event);
    wxString GetUnitAttackName(int);

    void ListUnitArmors();
    void OnUnitArmorsSearch(wxCommandEvent &event);
    void OnUnitArmorSelect(wxCommandEvent &event);
    void OnUnitArmorsAdd(wxCommandEvent &event);
    void OnUnitArmorsInsert(wxCommandEvent &event);
    void OnUnitArmorsDelete(wxCommandEvent &event);
    void OnUnitArmorsCopy(wxCommandEvent &event);
    void OnUnitArmorsPaste(wxCommandEvent &event);
    void OnUnitArmorsPasteInsert(wxCommandEvent &event);
    void OnUnitArmorsCopyToUnits(wxCommandEvent &event);
    wxString GetUnitArmorName(int);

//  Unit Events

    void ListUnitCommands();
    void OnUnitCommandsSearch(wxCommandEvent &event);
    void OnUnitCommandSelect(wxCommandEvent &event);
    void OnUnitCommandsAdd(wxCommandEvent &event);
    void OnUnitCommandsInsert(wxCommandEvent &event);
    void OnUnitCommandsDelete(wxCommandEvent &event);
    void OnUnitCommandsCopy(wxCommandEvent &event);
    void OnUnitCommandsPaste(wxCommandEvent &event);
    void OnUnitCommandsPasteInsert(wxCommandEvent &event);
    void OnUnitCommandsCopyToUnits(wxCommandEvent &event);
    wxString GetUnitCommandName(int);

//  Unitline Events

    void ListUnitLines();
    void OnUnitLinesSearch(wxCommandEvent &event);
    void OnUnitLineSelect(wxCommandEvent &event);
    void OnUnitLinesAdd(wxCommandEvent &event);
    void OnUnitLinesInsert(wxCommandEvent &event);
    void OnUnitLinesDelete(wxCommandEvent &event);
    void OnUnitLinesCopy(wxCommandEvent &event);
    void OnUnitLinesPaste(wxCommandEvent &event);
    void OnUnitLinesPasteInsert(wxCommandEvent &event);
    wxString GetUnitLineName(int);

    void ListUnitLineUnits();
    void OnUnitLineUnitsSearch(wxCommandEvent &event);
    void OnUnitLineUnitSelect(wxCommandEvent &event);
    void OnUnitLineUnitsAdd(wxCommandEvent &event);
    void OnUnitLineUnitsInsert(wxCommandEvent &event);
    void OnUnitLineUnitsDelete(wxCommandEvent &event);
    void OnUnitLineUnitsCopy(wxCommandEvent &event);
    void OnUnitLineUnitsPaste(wxCommandEvent &event);
    void OnUnitLineUnitsPasteInsert(wxCommandEvent &event);
    void OnUnitLineUnitsCopyToUnitLines(wxCommandEvent &event);
    wxString GetUnitLineUnitName(int);

//  Graphic Events

    void ListGraphics(bool all = true);
    void OnGraphicsSearch(wxCommandEvent &event);
    void OnGraphicSelect(wxCommandEvent &event);
    void OnGraphicsAdd(wxCommandEvent &event);
    void OnGraphicsInsert(wxCommandEvent &event);
    void OnGraphicsDelete(wxCommandEvent &event);
    void OnGraphicsCopy(wxCommandEvent &event);
    void OnGraphicsPaste(wxCommandEvent &event);
    void OnGraphicsPasteInsert(wxCommandEvent &event);
    void OnGraphicsEnable(wxCommandEvent &event);
    void OnGraphicsDisable(wxCommandEvent &event);
    wxString GetGraphicName(int, bool = false);
    void PrepGraphicSearch();

    void ListGraphicDeltas();
    void OnGraphicDeltasSearch(wxCommandEvent &event);
    void OnGraphicDeltaSelect(wxCommandEvent &event);
    void OnGraphicDeltasAdd(wxCommandEvent &event);
    void OnGraphicDeltasInsert(wxCommandEvent &event);
    void OnGraphicDeltasDelete(wxCommandEvent &event);
    void OnGraphicDeltasCopy(wxCommandEvent &event);
    void OnGraphicDeltasPaste(wxCommandEvent &event);
    void OnGraphicDeltasPasteInsert(wxCommandEvent &event);
    void OnGraphicDeltasCopyToGraphics(wxCommandEvent &event);
    wxString GetGraphicDeltaName(int);

    void ListGraphicAngleSounds();
    void OnGraphicAngleSoundsSearch(wxCommandEvent &event);
    void OnGraphicAngleSoundSelect(wxCommandEvent &event);
    void OnGraphicAngleSoundsCopy(wxCommandEvent &event);
    void OnGraphicAngleSoundsCopyToGraphics(wxCommandEvent &event);
    wxString GetGraphicAngleSoundName(int);

//  Terrain Events

    void ListTerrainNumbers();
    void OnTerrainCountChange(wxFocusEvent &event);

    void ListTerrains1(bool all = true);
    void ListTerrains2();
    void OnTerrainsSearch(wxCommandEvent &event);
    void OnTerrainSelect(wxCommandEvent &event);
    void OnTerrainsAdd(wxCommandEvent &event);
    void OnTerrainsDelete(wxCommandEvent &event);
    void OnTerrainsCopy(wxCommandEvent &event);
    void OnTerrainsPaste(wxCommandEvent &event);
    wxString GetTerrainName(int, bool = false);
    void PrepTerrainSearch();

    void OnTerrainsBorderSearch(wxCommandEvent &event);
    void ListTerrainsBorders();
    void OnTerrainsBorderSelect(wxCommandEvent &event);
    void OnTerrainsBorderCopy(wxCommandEvent &event);
    void OnTerrainsBorderPaste(wxCommandEvent &event);
    void OnTerrainsBorderCopyToBuildings(wxCommandEvent &event);

//  Terrain Border Events

    void ListTerrainBorders(bool all = true);
    void OnTerrainBordersSearch(wxCommandEvent &event);
    void OnTerrainBorderSelect(wxCommandEvent &event);
    void OnTerrainBordersCopy(wxCommandEvent &event);
    void OnTerrainBordersPaste(wxCommandEvent &event);
    void OnTerrainBordersMoveUp(wxCommandEvent &event);
    void OnTerrainBordersMoveDown(wxCommandEvent &event);
    wxString GetTerrainBorderName(int);

    void ListTerrainBorderTileTypes();
    void OnTerrainBorderTileTypeSearch(wxCommandEvent &event);
    void OnTerrainBorderTileTypeSelect(wxCommandEvent &event);
    void OnTerrainBorderTileTypeCopy(wxCommandEvent &event);
    void OnTerrainBorderTileTypePaste(wxCommandEvent &event);
    void OnTerrainBorderTileTypeCopyToBorders(wxCommandEvent &event);
    wxString GetTerrainBorderTileTypeName(int);

    void ListTerrainBorderBorderShapes();
    void OnTerrainBorderBorderShapeSearch(wxCommandEvent &event);
    void OnTerrainBorderBorderShapeSelect(wxCommandEvent &event);
    void OnTerrainBorderBorderShapeCopy(wxCommandEvent &event);
    void OnTerrainBorderBorderShapePaste(wxCommandEvent &event);
    void OnTerrainBorderBorderShapeCopyToBorders(wxCommandEvent &event);
    wxString GetTerrainBorderBorderShapeName(int);

//  Terrain Restriction Events

    void ListTerrainRestrictions(bool all = true);
    void OnTerrainRestrictionsSearch(wxCommandEvent &event);
    void OnTerrainRestrictionSelect(wxCommandEvent &event);
    void OnTerrainRestrictionsTerrainSelect(wxCommandEvent &event);
    void OnTerrainRestrictionsAdd(wxCommandEvent &event);
    void OnTerrainRestrictionsInsert(wxCommandEvent &event);
    void OnTerrainRestrictionsDelete(wxCommandEvent &event);
    void OnTerrainRestrictionsCopy(wxCommandEvent &event);
    void OnTerrainRestrictionsPaste(wxCommandEvent &event);
    void OnTerrainRestrictionsPasteInsert(wxCommandEvent &event);
    void OnTerrainRestrictionsTerrainCopy(wxCommandEvent &event);
    void OnTerrainRestrictionsTerrainPaste(wxCommandEvent &event);
    wxString GetTerrainRestrictionName(int);

//  Sound Events

    void ListSounds(bool all = true);
    void OnSoundsSearch(wxCommandEvent &event);
    void OnSoundSelect(wxCommandEvent &event);
    void OnSoundsAdd(wxCommandEvent &event);
    void OnSoundsInsert(wxCommandEvent &event);
    void OnSoundsDelete(wxCommandEvent &event);
    void OnSoundsCopy(wxCommandEvent &event);
    void OnSoundsPaste(wxCommandEvent &event);
    void OnSoundsPasteInsert(wxCommandEvent &event);
    wxString GetSoundName(int);

    void ListSoundItems();
    void OnSoundItemsSearch(wxCommandEvent &event);
    void OnSoundItemSelect(wxCommandEvent &event);
    void OnSoundItemsAdd(wxCommandEvent &event);
    void OnSoundItemsInsert(wxCommandEvent &event);
    void OnSoundItemsDelete(wxCommandEvent &event);
    void OnSoundItemsCopy(wxCommandEvent &event);
    void OnSoundItemsPaste(wxCommandEvent &event);
    void OnSoundItemsPasteInsert(wxCommandEvent &event);
    void OnSoundItemsCopyToSounds(wxCommandEvent &event);
    wxString GetSoundItemName(int, int, bool = false);
    void PrepSoundItemSearch();

//  Player Color Events

    void ListPlayerColors();
    void OnPlayerColorsSearch(wxCommandEvent &event);
    void OnPlayerColorSelect(wxCommandEvent &event);
    void OnPlayerColorsAdd(wxCommandEvent &event);
    void OnPlayerColorsInsert(wxCommandEvent &event);
    void OnPlayerColorsDelete(wxCommandEvent &event);
    void OnPlayerColorsCopy(wxCommandEvent &event);
    void OnPlayerColorsPaste(wxCommandEvent &event);
    void OnPlayerColorsPasteInsert(wxCommandEvent &event);
    wxString GetPlayerColorName(int);

//  Application Variables

    float slp_zoom = 1, boxWidthMultiplier, displayScaling;
    wxString EditorVersionString, slp_extra_info;
    bool PromptForFilesOnOpen, AutoCopy, CopyGraphics, AllCivs, AutoBackups, StayOnTop, KeepViewOnTop,
        NeverHideAttributes;
    std::vector<short> SelectedCivs;
    bool SearchAnd = false, ExcludeAnd = false, ShowUnknowns, ResizeTerrains, SkipOpenDialog, Paste11, Reselection;
    bool ShowSLP, AnimSLP, ShowShadows, ShowOutline, ShowDeltas, ShowStack, ShowAnnexes, ShowIcons, DrawHot = false;
    bool DrawTerrain, RotateAngles, FillMissingFrames;
    bool DrawCollisionShape, DrawClearanceShape, DrawOutline, DrawAngles, PlaySounds, AutoCopyAngles;
    std::vector<genie::DrsFile*> datafiles;
    std::vector<std::vector<genie::Color>> palettes, pc_palettes;
    genie::DatFile *dataset = 0;
    genie::LangFile *Lang = 0, *LangX = 0, *LangXP = 0;
    int CustomTerrains, paletteView = 0, ViewBackR, ViewBackG, ViewBackB, ViewPosX, ViewPosY;
    bool slp_tool_on = false;
    wxBrush slp_background_brush;
    wxFrame *slp_window = nullptr;
    APanel *slp_view;
    wxSizer *slp_sizer;
    wxButton *slp_next, *slp_frame_export, *slp_frame_import, *slp_save, *slp_prev, *slp_first,
        *slp_tool, *slp_merge_shadow, *slp_zoom_btn;
    wxFilePickerCtrl *slp_source1, *slp_source2, *slp_target1;
    wxFlexGridSizer *slp_tool_layout;
    wxRadioBox *slp_radio, *slp_unit_actions;
    wxCheckBox *slp_dmg_unit, *slp_snow, *slp_garrison, *slp_hotspot, *slp_collision, *slp_clearance, *slp_selection;
    wxCheckBox *slp_animate, *slp_shadow, *slp_outline, *slp_delta, *slp_stack, *slp_annex, *slp_terrain;
    wxCheckBox *slp_angles, *slp_show_angles, *slp_sounds;
    wxColourPickerCtrl *slp_background;
    int times_listed = 0;

    std::vector<AGEComboBox*> ResearchComboBoxList, TechComboBoxList, CivComboBoxList, ResourceComboBoxList,
        UnitComboBoxList, GraphicComboBoxList, TerrainComboBoxList, TerrainBorderComboBoxList,
        TerrainRestrictionComboBoxList, SoundComboBoxList;

    std::vector<int> RandomMapIDs, UnknownFSIDs, UnknownSSIDs, UnknownTSIDs, Unknown4SIDs,
        ResearchIDs, TechIDs, EffectIDs,
        TTAgeIDs, TTAgeBuildIDs, TTAgeUnitIDs, TTAgeResIDs, TTAgeUnknownIDs, TTItemIDs, TTUnknownItemIDs,
        TTBuildConIDs, TTBuildBuildIDs, TTBuildUnitIDs, TTBuildResIDs,
        TTUnitConIDs, TTUnitUnitIDs,
        TTResConIDs, TTResBuildIDs, TTResUnitIDs, TTResResIDs,
        CivIDs, ResourceIDs,
        UnitIDs, DamageGraphicIDs, DropSiteIDs, AttackIDs, ArmorIDs, CommandIDs,
        UnitLineIDs, UnitLineUnitIDs,
        GraphicIDs, DeltaIDs, AttackSoundIDs,
        TerrainIDs, TerBorderIDs, TerRestrictIDs, TerRestrictTerIDs,
        SoundIDs, SoundItemIDs, ColorIDs,
        BorderIDs, BorderTileTypeIDs, BorderShapeIDs;
    int UnitCivID;

    bool SaveDat, SaveApf, WriteLangs, SaveLangs, LangWriteToLatest, SyncSaveWithOpen,
        UseTXT = false, UseDRS, UseMod, UseExtra, FilterAllSubs, UseLooseSLP, UseLooseModSLP, LooseHD;
    enum class ListMode { SEARCH, ADD, DEL, PASTE, INSNEW, INSPASTE, ENABLE } How2List = ListMode::SEARCH;
    short techAttributeNameId, techResearchNameId;
    int TimesOpened, GameVersion, DatUsed, SaveGameVersion;
    int maxWindowWidthV2, minWindowWidth, lastWindowPosX, lastWindowPosY;
    std::chrono::time_point<std::chrono::system_clock> endTime;
    genie::GameVersion GenieVersion = genie::GV_None;
    wxString DriveLetter, Language, CustomFolder;
    wxString DatFileName, SaveDatFileName, FolderDRS, FolderDRS2, Path1stDRS, PathSLP, PathModSLP;
    wxString PathPalettes, PathPlayerColorPalette, PathCustomNames;
    int LangsUsed; // 0x01 Lang.dll, 0x02, LangX1.dll, 0x04 LangX1P1.dll
    wxString LangCharset, AlexZoom;
    wxString LangFileName, LangX1FileName, LangX1P1FileName;
    wxString SaveLangFileName, SaveLangX1FileName, SaveLangX1P1FileName;

    std::map<size_t, std::string> LangTxt;
    HINSTANCE LanguageDLL[3];
    wxString TranslatedText(int ID, int Letters = 0);
    //void WriteTranslatedText(int ID, wxString Name);
    bool exportFrame = false;
    void LoadTXT(const wxString &filename);
    bool LoadSLP(AGE_SLP*);
    void FrameToBitmap(AGE_SLP*, bool = false);
    void BitmapToSLP(AGE_SLP*);
    AGE_SLP iconSLP, techSLP, tileSLP, borderSLP;
    AGE_SLPs gallery, museum;
    enum class SHOW { NONE, UNIT, GRAPHIC } currentDisplay = SHOW::NONE;
    uint8_t playerColorStart = 0, playerColorID = 0;
    unsigned setbearing;
    float bearing;

public:
//  Constants, remove unneeded entries.

    enum
    {
        // menus and tool bar
        ePrompt = wxID_HIGHEST + 1, eVasili,
        eButtons, eNeverHide, eTips, eStayOnTop, eAbout,
        eBackup, eUnknown, eHelp, eDRS, eHex, eFloat, ePaste,
        eReselection, eAddWindow, eCompileList, eBoxWidth, eScrollRate,

        // animation menu
        eShowSLP, eShowIcons, eSlpPals, eSlpPCPal, eStayOnTopSLP, eCacheDepth, eSlpZoom,

        // open and save
        eOpen,
        eSave,

        // tab change
        eTabBar,

        // buttons
        eNextFrame, ePrevFrame, eFirstFrame, eExportFrame, eImportFrame, eSaveSLP, eSLPTool,
        eSLPMergeShadow, eZoom,

        // check boxes
        eShowHotspot, eAnimSLP, eShowShadows, eShowOutline, eShowDeltas, eShowStack, eShowAnnexes,
        eShowTerrain, eCollisionShape, eClearanceShape, eOutline, eShowAngles, eRotateAngles,
        ePlaySounds,

        // color picker
        ePickBgColor,

        // invisible
        hotWin1, hotWin2, hotWin3, hotWin4, closeAll
    };

//  User Interface
private:

    //  Data combo box strings
    wxArrayString sound_names, graphic_names, resource_names, terrain_names,
        unit_names, class_names, action_names, research_names, restriction_names,
        unitline_names, civ_names, armor_names, border_names, tech_names, color_names,
        age_names, effect_type_names, effect_attribute_names,

    //  Search filter strings
        unit_filters, terrain_filters, tt_research_filters, tt_unit_filters,
        tt_building_filters, soundfile_filters, research_filters, graphic_filters,

    //  Miscellaneous combo box strings
        task_names, unit_type_names, graphicset_names, specialcopy_names,
        unit_filter_options, civ_names_only, mode_names, modify_research_names;

    wxMenuBar *MenuBar_Main;
    wxMenu *SubMenu_Options, *SubMenu_Help, *SubMenu_SLP;

    wxNotebook *TabBar_Main, *TabBar_TechTree;

    ATabPage *Tab_General = nullptr, *Tab_Research = nullptr, *Tab_Techs = nullptr,
        *Tab_TechTrees = nullptr, *Tab_Civs = nullptr, *Tab_Units = nullptr, *Tab_UnitLine = nullptr,
        *Tab_Graphics = nullptr, *Tab_Terrains = nullptr, *Tab_TerrainBorders = nullptr,
        *Tab_TerrainRestrictions = nullptr, *Tab_Sounds = nullptr, *Tab_PlayerColors = nullptr,
        *Tab_Unknown = nullptr, *Tab_TechTreeAges = nullptr, *Tab_TechTreeBuildings = nullptr,
        *Tab_TechTreeUnits = nullptr, *Tab_TechTreeResearches = nullptr;

//  General user interface

    wxBoxSizer *General_Main;
    wxBoxSizer *General_TopRow;
    wxButton *General_Refresh;
    SolidText *General_CalcBoxes_Text;
    SolidText *General_CalcBoxesMiddle_Text;
    wxTextCtrl *General_CalcBoxes[5];
    AScrolled *General_Scroller;
    wxBoxSizer *General_ScrollSpace;
    SolidText *General_TileSizes_Text;
    wxGridSizer *General_TileSizes_Grid;
    std::array<wxBoxSizer*, 19> General_TileSizes_Sizers;
    std::array<AGETextCtrl*, 57> General_TileSizes;

    wxBoxSizer *MapRowOffset_Sizer;
    SolidText *MapRowOffset_Text;
    AGETextCtrl *MapRowOffset;
    wxBoxSizer *MapMinX_Sizer;
    SolidText *MapMinX_Text;
    AGETextCtrl *MapMinX;
    wxBoxSizer *MapMinY_Sizer;
    SolidText *MapMinY_Text;
    AGETextCtrl *MapMinY;
    wxBoxSizer *MapMaxX_Sizer;
    SolidText *MapMaxX_Text;
    AGETextCtrl *MapMaxX;
    wxBoxSizer *MapMaxY_Sizer;
    SolidText *MapMaxY_Text;
    AGETextCtrl *MapMaxY;
    wxBoxSizer *MapMaxXplus1_Sizer;
    SolidText *MapMaxXplus1_Text;
    AGETextCtrl *MapMaxXplus1;
    wxBoxSizer *MapMaxYplus1_Sizer;
    SolidText *MapMaxYplus1_Text;
    AGETextCtrl *MapMaxYplus1;

    wxBoxSizer *MaxTerrain_Sizer;
    SolidText *MaxTerrain_Text;
    AGETextCtrl *MaxTerrain;
    wxBoxSizer *TileWidth_Sizer;
    SolidText *TileWidth_Text;
    AGETextCtrl *TileWidth;
    wxBoxSizer *TileHeight_Sizer;
    SolidText *TileHeight_Text;
    AGETextCtrl *TileHeight;
    wxBoxSizer *TileHalfHeight_Sizer;
    SolidText *TileHalfHeight_Text;
    AGETextCtrl *TileHalfHeight;
    wxBoxSizer *TileHalfWidth_Sizer;
    SolidText *TileHalfWidth_Text;
    AGETextCtrl *TileHalfWidth;
    wxBoxSizer *ElevHeight_Sizer;
    SolidText *ElevHeight_Text;
    AGETextCtrl *ElevHeight;
    wxBoxSizer *CurRow_Sizer;
    SolidText *CurRow_Text;
    AGETextCtrl *CurRow;
    wxBoxSizer *CurCol_Sizer;
    SolidText *CurCol_Text;
    AGETextCtrl *CurCol;
    wxBoxSizer *BlockBegRow_Sizer;
    SolidText *BlockBegRow_Text;
    AGETextCtrl *BlockBegRow;
    wxBoxSizer *BlockEndRow_Sizer;
    SolidText *BlockEndRow_Text;
    AGETextCtrl *BlockEndRow;
    wxBoxSizer *BlockBegCol_Sizer;
    SolidText *BlockBegCol_Text;
    AGETextCtrl *BlockBegCol;
    wxBoxSizer *BlockEndCol_Sizer;
    SolidText *BlockEndCol_Text;
    AGETextCtrl *BlockEndCol;

    wxBoxSizer *SearchMapPtr_Sizer;
    SolidText *SearchMapPtr_Text;
    AGETextCtrl *SearchMapPtr;
    wxBoxSizer *SearchMapRowsPtr_Sizer;
    SolidText *SearchMapRowsPtr_Text;
    AGETextCtrl *SearchMapRowsPtr;
    wxBoxSizer *AnyFrameChange_Sizer;
    SolidText *AnyFrameChange_Text;
    AGETextCtrl *AnyFrameChange;

    wxBoxSizer *MapVisibleFlag_Sizer;
    SolidText *MapVisibleFlag_Text;
    AGETextCtrl *MapVisibleFlag;
    wxBoxSizer *FogFlag_Sizer;
    SolidText *FogFlag_Text;
    AGETextCtrl *FogFlag;

    SolidText *General_TerrainRendering_Text;
    wxGridSizer *General_TerrainRendering_Grid;
    std::array<AGETextCtrl*, 25> General_SomeBytes;
    wxGridSizer *General_Something_Grid1, *General_Something_Grid2;
    std::array<AGETextCtrl*, 157> General_Something;

    wxBoxSizer *Borders_Main;
    wxStaticBoxSizer *Borders_Borders;
    wxGridSizer *Borders_Buttons;
    wxTextCtrl *Borders_Search;
    wxTextCtrl *Borders_Search_R;
    ProperList *Borders_ListV;
    wxButton *Borders_Copy;
    wxButton *Borders_Paste;
    wxButton *Borders_MoveUp;
    wxButton *Borders_MoveDown;
    wxBoxSizer *Borders_DataArea;
    wxBoxSizer *Borders_DataTopRow;
    wxBoxSizer *Borders_Data1;
    wxBoxSizer *Borders_Data2;
    wxBoxSizer *Borders_FrameData;
    wxStaticBoxSizer *Borders_Borders_Holder;

    wxStaticBoxSizer *Borders_TileTypes;
    wxGridSizer *Borders_TileTypes_Buttons;
    wxTextCtrl *Borders_TileTypes_Search;
    wxTextCtrl *Borders_TileTypes_Search_R;
    ProperList *Borders_TileTypes_ListV;
    wxButton *TileTypes_Copy;
    wxButton *TileTypes_Paste;
    wxButton *TileTypes_CopyToBorders;

    wxStaticBoxSizer *Borders_BorderShapes;
    wxGridSizer *Borders_BorderShapes_Buttons;
    wxTextCtrl *Borders_BorderShapes_Search;
    wxTextCtrl *Borders_BorderShapes_Search_R;
    ProperList *Borders_BorderShapes_ListV;
    wxButton *BorderShapes_Copy;
    wxButton *BorderShapes_Paste;
    wxButton *BorderShapes_CopyToBorders;

    wxBoxSizer *Borders_FrameArea_Holder;
    wxBoxSizer *Borders_Enabled_Holder;
    wxBoxSizer *Borders_Enabled1_Holder;
    SolidText *Borders_Enabled_Text;
    AGETextCtrl *Borders_Enabled;
    LinkedCheckBox *Borders_Enabled_CheckBox;
    wxBoxSizer *Borders_Random_Holder;
    SolidText *Borders_Random_Text;
    AGETextCtrl *Borders_Random;
    wxBoxSizer *Borders_Name_Holder[2];
    SolidText *Borders_Name_Text[2];
    StringControl *Borders_Name[2];
    wxBoxSizer *Borders_SLP_Holder;
    SolidText *Borders_SLP_Text;
    AGETextCtrl *Borders_SLP;
    wxBoxSizer *Borders_ShapePtr_Holder;
    SolidText *Borders_ShapePtr_Text;
    AGETextCtrl *Borders_ShapePtr;
    wxBoxSizer *Borders_Sound_Holder;
    SolidText *Borders_Sound_Text;
    AGETextCtrl *Borders_Sound;
    wxBoxSizer *Borders_Colors_Holder;
    wxGridSizer *Borders_Colors_Grid;
    SolidText *Borders_Colors_Text;
    std::array<AGETextCtrl*, 3> Borders_Colors;
    wxBoxSizer *Borders_Animation_Grid1;
    wxBoxSizer *Borders_Animation_Grid2;
    wxBoxSizer *Borders_IsAnimated_Holder;
    SolidText *Borders_IsAnimated_Text;
    AGETextCtrl *Borders_IsAnimated;
    wxBoxSizer *Borders_AnimationFrames_Holder;
    SolidText *Borders_AnimationFrames_Text;
    AGETextCtrl *Borders_AnimationFrames;
    wxBoxSizer *Borders_PauseFames_Holder;
    SolidText *Borders_PauseFames_Text;
    AGETextCtrl *Borders_PauseFames;
    wxBoxSizer *Borders_Interval_Holder;
    SolidText *Borders_Interval_Text;
    AGETextCtrl *Borders_Interval;
    wxBoxSizer *Borders_PauseBetweenLoops_Holder;
    SolidText *Borders_PauseBetweenLoops_Text;
    AGETextCtrl *Borders_PauseBetweenLoops;
    wxBoxSizer *Borders_Frame_Holder;
    SolidText *Borders_Frame_Text;
    AGETextCtrl *Borders_Frame;
    wxBoxSizer *Borders_DrawFrame_Holder;
    SolidText *Borders_DrawFrame_Text;
    AGETextCtrl *Borders_DrawFrame;
    wxBoxSizer *Borders_AnimateLast_Holder;
    SolidText *Borders_AnimateLast_Text;
    AGETextCtrl *Borders_AnimateLast;
    wxBoxSizer *Borders_FrameChanged_Holder;
    SolidText *Borders_FrameChanged_Text;
    AGETextCtrl *Borders_FrameChanged;
    wxBoxSizer *Borders_Drawn_Holder;
    SolidText *Borders_Drawn_Text;
    AGETextCtrl *Borders_Drawn;
    wxBoxSizer *Borders_FrameID_Holder;
    SolidText *Borders_FrameID_Text;
    AGETextCtrl *Borders_FrameID;
    wxBoxSizer *Borders_Flag1_Holder;
    SolidText *Borders_Flag1_Text;
    AGETextCtrl *Borders_Flag1;
    wxBoxSizer *Borders_Flag2_Holder;
    SolidText *Borders_Flag2_Text;
    AGETextCtrl *Borders_Flag2;
    APanel *Border_Shape_SLP;
    wxBoxSizer *Borders_DrawTerrain_Holder;
    SolidText *Borders_DrawTerrain_Text;
    AGETextCtrl *Borders_DrawTerrain;
    wxBoxSizer *Borders_Terrain_Holder;
    SolidText *Borders_Terrain_Text;
    AGETextCtrl *Borders_Terrain;
    LinkedComboBox *Borders_Terrain_ComboBox;
    wxBoxSizer *Borders_BorderStyle_Holder;
    SolidText *Borders_BorderStyle_Text;
    AGETextCtrl *Borders_BorderStyle;

    std::vector<AGETextCtrl*> uiGroupMaps, uiGroupTT, uiGroupTTAge, uiGroupTTBuilding, uiGroupTTUnit, uiGroupTTResearch;
    wxBoxSizer *General_Variables2_Grid;
    wxStaticBoxSizer *General_Variables1_Holder;
    wxStaticBoxSizer *General_Variables2_Holder;
    wxBoxSizer *General_SUnknown7_Holder;
    SolidText *General_SUnknown7_Text;
    AGETextCtrl *General_SUnknown7;
    wxBoxSizer *General_SUnknown8_Holder;
    SolidText *General_SUnknown8_Text;
    AGETextCtrl *General_SUnknown8;
    wxBoxSizer *General_SUnknown2_Holder;
    SolidText *General_SUnknown2_Text;
    AGETextCtrl *General_SUnknown2;
    wxBoxSizer *General_SUnknown3_Holder;
    SolidText *General_SUnknown3_Text;
    AGETextCtrl *General_SUnknown3;
    wxBoxSizer *General_SUnknown4_Holder;
    SolidText *General_SUnknown4_Text;
    AGETextCtrl *General_SUnknown4;
    wxBoxSizer *General_SUnknown5_Holder;
    SolidText *General_SUnknown5_Text;
    AGETextCtrl *General_SUnknown5;
    std::array<wxBoxSizer*, 8> General_TTKnown_Holder;
    std::array<SolidText*, 8> General_TTKnown_Text;
    std::array<AGETextCtrl*, 8> General_TTKnown;

    wxBoxSizer *General_MapPointer_Holder;
    SolidText *General_MapPointer_Text;
    AGETextCtrl *General_MapPointer;
    wxBoxSizer *General_VFP_Holder;
    SolidText *General_VFP_Text;
    AGETextCtrl *General_VFP;
    wxBoxSizer *General_MapWidth_Holder;
    SolidText *General_MapWidth_Text;
    AGETextCtrl *General_MapWidth;
    wxBoxSizer *General_MapHeight_Holder;
    SolidText *General_MapHeight_Text;
    AGETextCtrl *General_MapHeight;
    wxBoxSizer *General_WorldWidth_Holder;
    SolidText *General_WorldWidth_Text;
    AGETextCtrl *General_WorldWidth;
    wxBoxSizer *General_WorldHeight_Holder;
    SolidText *General_WorldHeight_Text;
    AGETextCtrl *General_WorldHeight;
    wxBoxSizer *General_TileSizesPadding_Holder;
    SolidText *General_TileSizesPadding_Text;
    AGETextCtrl *General_TileSizesPadding;

    wxBoxSizer *Unknown_Main;
    AScrolled *RMS_Scroller;
    wxBoxSizer *Unknown_ScrollSpace;

    std::vector<AGETextCtrl*> uiGroupRandomMap, uiGroupRMBase, uiGroupRMTerrain, uiGroupRMUnit, uiGroupRMUnknown;
    SolidText *RMS_MapsPtr_Text;
    AGETextCtrl *RMS_MapsPtr;

    wxStaticBoxSizer *Unknowns;
    wxBoxSizer *Unknowns_ListArea;
    wxTextCtrl *Unknowns_Search;
    wxTextCtrl *Unknowns_Search_R;
    ProperList *Unknowns_ListV;
    wxGridSizer *Unknowns_Buttons;
    wxButton *Unknowns_Add;
    wxButton *Unknowns_Insert;
    wxButton *Unknowns_Delete;
    wxButton *Unknowns_Copy;
    wxButton *Unknowns_Paste;
    wxButton *Unknowns_PasteInsert;

    SolidText *RMS_MapID_Text;
    AGETextCtrl *RMS_MapID;
    wxGridSizer *RMS_LandData_Grid;
    wxBoxSizer *RMS_MapID_Holder;
    std::array<wxBoxSizer*, 9> RMS_LandData_Holder;
    std::array<SolidText*, 9> RMS_LandData_Text;
    std::array<AGETextCtrl*, 9> RMS_LandData;
    SolidText *RMS_LandsPtr_Text;
    AGETextCtrl *RMS_LandsPtr;
    SolidText *RMS_TerrainsPtr_Text;
    AGETextCtrl *RMS_TerrainsPtr;
    SolidText *RMS_UnitsPtr_Text;
    AGETextCtrl *RMS_UnitsPtr;
    SolidText *RMS_ElevationsPtr_Text;
    AGETextCtrl *RMS_ElevationsPtr;

    wxStaticBoxSizer *RMSMapLands;
    wxBoxSizer *RMS_Land_ListArea;
    wxTextCtrl *RMS_Land_Search;
    wxTextCtrl *RMS_Land_Search_R;
    ProperList *RMS_Land_ListV;
    wxGridSizer *RMS_Land_Buttons;
    wxButton *RMS_Land_Add;
    wxButton *RMS_Land_Insert;
    wxButton *RMS_Land_Delete;
    wxButton *RMS_Land_Copy;
    wxButton *RMS_Land_Paste;
    wxButton *RMS_Land_PasteInsert;
    wxButton *RMS_Land_CopyToMaps;

    wxGridSizer *RMS_Land_LandID_Grid;

    wxBoxSizer *RMS_Land_LandID_Holder;
    SolidText *RMS_Land_LandID_Text;
    AGETextCtrl *RMS_Land_LandID;
    wxBoxSizer *RMS_Land_BaseTerrain_Holder;
    SolidText *RMS_Land_BaseTerrain_Text;
    AGETextCtrl *RMS_Land_BaseTerrain;
    wxBoxSizer *RMS_Land_PlayerSpacing_Holder;
    SolidText *RMS_Land_PlayerSpacing_Text;
    AGETextCtrl *RMS_Land_PlayerSpacing;
    wxBoxSizer *RMS_Land_BaseSize_Holder;
    SolidText *RMS_Land_BaseSize_Text;
    AGETextCtrl *RMS_Land_BaseSize;

    wxBoxSizer *RMS_Land_Zone_Holder;
    SolidText *RMS_Land_Zone_Text;
    AGETextCtrl *RMS_Land_Zone;
    wxBoxSizer *RMS_Land_PlacementType_Holder;
    SolidText *RMS_Land_PlacementType_Text;
    AGETextCtrl *RMS_Land_PlacementType;
    wxBoxSizer *RMS_Land_Padding1_Holder;
    SolidText *RMS_Land_Padding1_Text;
    AGETextCtrl *RMS_Land_Padding1;

    wxBoxSizer *RMS_Land_X_Holder;
    SolidText *RMS_Land_X_Text;
    AGETextCtrl *RMS_Land_X;
    wxBoxSizer *RMS_Land_Y_Holder;
    SolidText *RMS_Land_Y_Text;
    AGETextCtrl *RMS_Land_Y;

    wxBoxSizer *RMS_Land_LandProportion_Holder;
    SolidText *RMS_Land_LandProportion_Text;
    AGETextCtrl *RMS_Land_LandProportion;
    wxBoxSizer *RMS_Land_ByPlayerFlag_Holder;
    SolidText *RMS_Land_ByPlayerFlag_Text;
    AGETextCtrl *RMS_Land_ByPlayerFlag;
    wxBoxSizer *RMS_Land_Padding2_Holder;
    SolidText *RMS_Land_Padding2_Text;
    AGETextCtrl *RMS_Land_Padding2;

    wxBoxSizer *RMS_Land_StartAreaRadius_Holder;
    SolidText *RMS_Land_StartAreaRadius_Text;
    AGETextCtrl *RMS_Land_StartAreaRadius;
    wxBoxSizer *RMS_Land_TerrainEdgeFade_Holder;
    SolidText *RMS_Land_TerrainEdgeFade_Text;
    AGETextCtrl *RMS_Land_TerrainEdgeFade;
    wxBoxSizer *RMS_Land_Clumpiness_Holder;
    SolidText *RMS_Land_Clumpiness_Text;
    AGETextCtrl *RMS_Land_Clumpiness;

    wxStaticBoxSizer *RMSTerrain;
    wxBoxSizer *RMS_Terrain_ListArea;
    wxTextCtrl *RMS_Terrain_Search;
    wxTextCtrl *RMS_Terrain_Search_R;
    ProperList *RMS_Terrain_ListV;
    wxGridSizer *RMS_Terrain_Buttons;
    wxButton *RMS_Terrain_Add;
    wxButton *RMS_Terrain_Insert;
    wxButton *RMS_Terrain_Delete;
    wxButton *RMS_Terrain_Copy;
    wxButton *RMS_Terrain_Paste;
    wxButton *RMS_Terrain_PasteInsert;
    wxButton *RMS_Terrain_CopyToMaps;

    wxGridSizer *RMS_TerrainData_Grid;
    std::array<wxBoxSizer*, 6> RMS_TerrainData_Holder;
    std::array<SolidText*, 6> RMS_TerrainData_Text;
    std::array<AGETextCtrl*, 6> RMS_TerrainData;

    wxStaticBoxSizer *RMSUnit;
    wxBoxSizer *RMS_Unit_ListArea;
    wxTextCtrl *RMS_Unit_Search;
    wxTextCtrl *RMS_Unit_Search_R;
    ProperList *RMS_Unit_ListV;
    wxGridSizer *RMS_Unit_Buttons;
    wxButton *RMS_Unit_Add;
    wxButton *RMS_Unit_Insert;
    wxButton *RMS_Unit_Delete;
    wxButton *RMS_Unit_Copy;
    wxButton *RMS_Unit_Paste;
    wxButton *RMS_Unit_PasteInsert;
    wxButton *RMS_Unit_CopyToMaps;

    wxGridSizer *RMS_Unit_Unknown1_Grid;
    wxBoxSizer *RMS_Unit_Unit_Holder;
    SolidText *RMS_Unit_Unit_Text;
    AGETextCtrl *RMS_Unit_Unit;
    wxBoxSizer *RMS_Unit_HostTerrain_Holder;
    SolidText *RMS_Unit_HostTerrain_Text;
    AGETextCtrl *RMS_Unit_HostTerrain;
    wxBoxSizer *RMS_Unit_GroupPlacing_Holder;
    SolidText *RMS_Unit_GroupPlacing_Text;
    AGETextCtrl *RMS_Unit_GroupPlacing;
    wxBoxSizer *RMS_Unit_ScaleFlag_Holder;
    SolidText *RMS_Unit_ScaleFlag_Text;
    AGETextCtrl *RMS_Unit_ScaleFlag;
    wxBoxSizer *RMS_Unit_Padding1_Holder;
    SolidText *RMS_Unit_Padding1_Text;
    AGETextCtrl *RMS_Unit_Padding1;
    wxBoxSizer *RMS_Unit_ObjectsPerPlayer_Holder;
    SolidText *RMS_Unit_ObjectsPerPlayer_Text;
    AGETextCtrl *RMS_Unit_ObjectsPerPlayer;
    wxBoxSizer *RMS_Unit_Fluctuation_Holder;
    SolidText *RMS_Unit_Fluctuation_Text;
    AGETextCtrl *RMS_Unit_Fluctuation;
    wxBoxSizer *RMS_Unit_GroupsPerPlayer_Holder;
    SolidText *RMS_Unit_GroupsPerPlayer_Text;
    AGETextCtrl *RMS_Unit_GroupsPerPlayer;
    wxBoxSizer *RMS_Unit_GroupArea_Holder;
    SolidText *RMS_Unit_GroupArea_Text;
    AGETextCtrl *RMS_Unit_GroupArea;
    wxBoxSizer *RMS_Unit_PlayerID_Holder;
    SolidText *RMS_Unit_PlayerID_Text;
    AGETextCtrl *RMS_Unit_PlayerID;
    wxBoxSizer *RMS_Unit_SetPlaceForAllPlayers_Holder;
    SolidText *RMS_Unit_SetPlaceForAllPlayers_Text;
    AGETextCtrl *RMS_Unit_SetPlaceForAllPlayers;
    wxBoxSizer *RMS_Unit_MinDistanceToPlayers_Holder;
    SolidText *RMS_Unit_MinDistanceToPlayers_Text;
    AGETextCtrl *RMS_Unit_MinDistanceToPlayers;
    wxBoxSizer *RMS_Unit_MaxDistanceToPlayers_Holder;
    SolidText *RMS_Unit_MaxDistanceToPlayers_Text;
    AGETextCtrl *RMS_Unit_MaxDistanceToPlayers;

    wxStaticBoxSizer *RMSUnknown;
    wxBoxSizer *RMS_Elevation_ListArea;
    wxTextCtrl *RMS_Elevation_Search;
    wxTextCtrl *RMS_Elevation_Search_R;
    ProperList *RMS_Elevation_ListV;
    wxGridSizer *RMS_Elevation_Buttons;
    wxButton *RMS_Elevation_Add;
    wxButton *RMS_Elevation_Insert;
    wxButton *RMS_Elevation_Delete;
    wxButton *RMS_Elevation_Copy;
    wxButton *RMS_Elevation_Paste;
    wxButton *RMS_Elevation_PasteInsert;
    wxButton *RMS_Elevation_CopyToMaps;

    wxGridSizer *RMS_ElevationData_Grid;
    std::array<wxBoxSizer*, 6> RMS_ElevationData_Holder;
    std::array<SolidText*, 6> RMS_ElevationData_Text;
    std::array<AGETextCtrl*, 6> RMS_ElevationData;

//  Techs user interface

    wxBoxSizer *Research_Main;
    wxGridSizer *Research_Research_Buttons;
    AScrolled *Research_Scroller;
    wxBoxSizer *Research_ScrollSpace;
    wxBoxSizer *Research_LangDLLArea_Holder;
    wxBoxSizer *Research_Misc2_Holder;
    wxBoxSizer *Research_Misc3_Holder;
    wxBoxSizer *Research_PointerArea_Holder;
    wxBoxSizer *Research_Names_Holder;

    wxStaticBoxSizer *Research_Research;
    wxBoxSizer *Research_Research_Searches[2];
    wxTextCtrl *Research_Research_Search;
    wxTextCtrl *Research_Research_Search_R;
    AGEComboBox *Research_SearchFilters[2];
    wxCheckBox *Research_Research_UseAnd[2];
    ProperList *Research_Research_ListV;
    wxButton *Research_Add;
    wxButton *Research_Insert;
    wxButton *Research_Delete;
    wxButton *Research_Copy;
    wxButton *Research_Paste;
    wxButton *Research_PasteInsert;

    std::vector<AGETextCtrl*> uiGroupResearch;
    wxBoxSizer *Research_RequiredTechArea_Holder;
    wxGridSizer *Research_RequiredTechs_Holder;
    SolidText *Research_RequiredTechArea_Text;
    AGETextCtrl *Research_RequiredTechs[6];
    LinkedComboBox *Research_RequiredTechs_ComboBox[6];
    wxBoxSizer *Research_RequiredTechCount_Holder;
    SolidText *Research_RequiredTechCount_Text;
    AGETextCtrl *Research_RequiredTechCount;

    wxStaticBoxSizer *Research_CostHeader_Holder;
    wxBoxSizer *Research_Cost_Texts;
    std::array<wxBoxSizer*, 3> Research_Cost_Sizers;
    SolidText *Research_Resources_Text;
    AGETextCtrl *Research_Resources[3];
    LinkedComboBox *Research_Resources_ComboBox[3];
    SolidText *Research_Amount_Text;
    AGETextCtrl *Research_Amount[3];
    SolidText *Research_Used_Text;
    AGETextCtrl *Research_Used[3];
    LinkedCheckBox *Research_Used_CheckBox[3];

    wxBoxSizer *Research_Civ_Holder;
    SolidText *Research_Civ_Text;
    AGETextCtrl *Research_Civ;
    LinkedComboBox *Research_Civ_ComboBox;

    wxBoxSizer *Research_FullTechMode_Holder;
    SolidText *Research_FullTechMode_Text;
    AGETextCtrl *Research_FullTechMode;
    LinkedCheckBox *Research_FullTechMode_CheckBox;

    wxBoxSizer *Research_ResearchLocation_Holder;
    SolidText *Research_ResearchLocation_Text;
    AGETextCtrl *Research_ResearchLocation;
    LinkedComboBox *Research_ResearchLocation_ComboBox;

    wxBoxSizer *Research_LangDLLName_Holder;
    SolidText *Research_LangDLLName_Text;
    NumberControl *Research_LangDLLName;
    TextIndexControl *Research_DLL_LangDLLName;

    wxBoxSizer *Research_LangDLLDescription_Holder;
    SolidText *Research_LangDLLDescription_Text;
    NumberControl *Research_LangDLLDescription;
    TextIndexControl *Research_DLL_LangDLLDescription;

    wxBoxSizer *Research_ResearchTime_Holder;
    SolidText *Research_ResearchTime_Text;
    AGETextCtrl *Research_ResearchTime;

    wxBoxSizer *Research_TechID_Holder;
    SolidText *Research_TechID_Text;
    AGETextCtrl *Research_TechID;
    LinkedComboBox *Research_TechID_ComboBox;

    wxBoxSizer *Research_Type_Holder;
    SolidText *Research_Type_Text;
    AGETextCtrl *Research_Type;

    wxBoxSizer *Research_IconID_Holder;
    SolidText *Research_IconID_Text;
    AGETextCtrl *Research_IconID;
    APanel *Research_IconID_SLP;

    wxBoxSizer *Research_ButtonID_Holder;
    SolidText *Research_ButtonID_Text;
    AGETextCtrl *Research_ButtonID;

    wxBoxSizer *Techs_Repeatable_Holder;
    SolidText *Techs_Repeatable_Text;
    AGETextCtrl *Techs_Repeatable;

    wxBoxSizer *Research_LanguageDLLHelp_Holder;
    SolidText *Research_LanguageDLLHelp_Text;
    AGETextCtrl *Research_LanguageDLLHelp;
    wxBoxSizer *Research_LanguageDLLName2_Holder;
    SolidText *Research_LanguageDLLName2_Text;
    AGETextCtrl *Research_LanguageDLLName2;
    wxBoxSizer *Research_HotKey_Holder;
    SolidText *Research_HotKey_Text;
    AGETextCtrl *Research_HotKey;
    TextIndexControl *Research_DLL_HotKey;
    TextIndexControl *Research_DLL_LanguageDLLHelp;
    TextIndexControl *Research_DLL_LanguageDLLName2;
    wxBoxSizer *Research_LanguageDLLConverter_Holder[2];
    SolidText *Research_LanguageDLLConverter_Text[2];
    wxTextCtrl *Research_LanguageDLLConverter[2];

    wxBoxSizer *Research_Name_Holder[2];
    SolidText *Research_Name_Text[2];
    StringControl *Research_Name[2];

//  Techs user interface

    wxBoxSizer *Techs_Main;
    wxGridSizer *Techs_Buttons;
    wxBoxSizer *Effects_ListArea;
    wxGridSizer *Techs_Effects_Buttons;
    wxBoxSizer *Effects_DataAreaProperties;
    wxCheckBox *Effects_NeverHide;
    wxBoxSizer *Effects_DataA_Holder;
    wxBoxSizer *Effects_DataB_Holder;
    wxBoxSizer *Effects_DataC_Holder;
    wxBoxSizer *Effects_DataD_Holder;
    wxBoxSizer *Effects_DataF_Holder;   // for attack/armor class
    wxBoxSizer *Effects_A_Holder;
    wxBoxSizer *Effects_B_Holder;
    wxBoxSizer *Effects_C_Holder;
    wxBoxSizer *Effects_D_Holder;
    wxBoxSizer *Effects_89_Type_Holder;   // for attack/armor class

    wxTextCtrl *Effects_89_Amount;  // amount
    SolidText *Effects_89_Type_Text;
    AGETextCtrl *Effects_89_Type; // class
    LinkedComboBox *Effects_89_Type_CB1;

    wxStaticBoxSizer *Techs_Techs;
    wxBoxSizer *Techs_Searches[2];
    wxTextCtrl *Techs_Search;
    wxTextCtrl *Techs_Search_R;
    wxCheckBox *Techs_UseAnd[2];
    ProperList *Techs_ListV;
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
    ProperList *Techs_AllEffects_ListV;
    wxBoxSizer *Techs_AllEffects_Buttons;
    wxButton *Techs_AllEffects_Load;
    wxButton *Techs_AllEffects_Clear;

    SolidText *Techs_Name_Text;
    StringControl *Techs_Name;

    wxStaticBoxSizer *Techs_Effects;
    wxBoxSizer *Techs_Effects_Searches[2];
    wxTextCtrl *Techs_Effects_Search;
    wxTextCtrl *Techs_Effects_Search_R;
    wxCheckBox *Techs_Effects_UseAnd[2];
    ProperList *Techs_Effects_ListV;
    wxButton *Techs_Effects_Add;
    wxButton *Techs_Effects_Insert;
    wxButton *Techs_Effects_Delete;
    wxButton *Techs_Effects_Copy;
    wxButton *Techs_Effects_Paste;
    wxButton *Techs_Effects_PasteInsert;
    wxButton *Techs_Effects_CopyToTechs;

    wxBoxSizer *Effects_DataArea;
    std::vector<AGETextCtrl*> uiGroupTechEffect;
    wxBoxSizer *Effects_Type_Holder;
    wxBoxSizer *Effects_Type2_Holder;
    SolidText *Effects_Type_Text;
    LinkedComboBox *Effects_Type_ComboBox;
    AGETextCtrl *Effects_Type;
    wxStaticBoxSizer *Effects_Data_Holder;
    SolidText *Effects_A_Text;
    AGETextCtrl *Effects_A;
    LinkedComboBox *Effects_A_ComboBox;
    SolidText *Effects_Info_A;
    SolidText *Effects_B_Text;
    AGETextCtrl *Effects_B;
    wxBoxSizer *Effects_B_Boxes;
    LinkedCheckBox *Effects_B_CheckBox;
    LinkedComboBox *Effects_B_ComboBox;
    SolidText *Effects_Info_B;
    SolidText *Effects_C_Text;
    AGETextCtrl *Effects_C;
    wxBoxSizer *Effects_C_Boxes;
    LinkedCheckBox *Effects_C_CheckBox;
    LinkedComboBox *Effects_C_ComboBox;
    SolidText *Effects_Info_C;
    SolidText *Effects_D_Text;
    AGETextCtrl *Effects_D;
    wxBoxSizer *Effects_D_Boxes;
    LinkedComboBox *Effects_D_ComboBox;
    SolidText *Effects_Info_D;

//  Civs user interface

    wxBoxSizer *Civs_Main;
    wxGridSizer *Civs_Civs_Buttons;
    wxStaticBoxSizer *Civs_Civs;
    wxTextCtrl *Civs_Civs_Search;
    wxTextCtrl *Civs_Civs_Search_R;
    ProperList *Civs_Civs_ListV;
    wxButton *Civs_Add;
    wxButton *Civs_Insert;
    wxButton *Civs_Delete;
    wxButton *Civs_Copy;
    wxButton *Civs_Paste;
    wxButton *Civs_PasteInsert;

    std::vector<AGETextCtrl*> uiGroupCiv;
    wxBoxSizer *Civs_DataArea;
    wxBoxSizer *Civs_DataGrid1;
    wxBoxSizer *Civs_DataGrid2;
    wxGridSizer *Civs_DataGrid3;
    SolidText *Civs_One_Text;
    wxBoxSizer *Civs_One_Holder;
    AGETextCtrl *Civs_One;
    wxBoxSizer *Civs_Name_Holder[2];
    SolidText *Civs_Name_Text[2];
    StringControl *Civs_Name[2];
    wxBoxSizer *Civs_SUnknown1_Holder;
    SolidText *Civs_SUnknown1_Text;
    AGETextCtrl *Civs_SUnknown1[4];
    wxBoxSizer *Civs_TechTree_Holder;
    SolidText *Civs_TechTree_Text;
    AGETextCtrl *Civs_TechTree;
    LinkedComboBox *Civs_TechTree_ComboBox;
    wxBoxSizer *Civs_TeamBonus_Holder;
    SolidText *Civs_TeamBonus_Text;
    AGETextCtrl *Civs_TeamBonus;
    LinkedComboBox *Civs_TeamBonus_ComboBox;
    wxBoxSizer *Civs_GraphicSet_Holder;
    SolidText *Civs_GraphicSet_Text;
    AGETextCtrl *Civs_GraphicSet;
    wxStaticBoxSizer *Civs_Resources;
    wxTextCtrl *Civs_Resources_Search;
    wxTextCtrl *Civs_Resources_Search_R;
    ProperList *Civs_Resources_ListV;
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
    SolidText *Civs_ResourceValue_Text;
    AGETextCtrl *Civs_ResourceValue;

//  Units user interface

//  Type 10+

    AScrolled *Units_Scroller;    // Scrollable unit section

    SolidText *visibleUnitCiv;
    AGETextCtrl *Units_Type;
    AGEComboBox *Units_Type_ComboBox;
    AGETextCtrl *Units_ID1;
    NumberControl *Units_LanguageDLLName;
    TextIndexControl *Units_DLL_LanguageName;
    NumberControl *Units_LanguageDLLCreation;
    TextIndexControl *Units_DLL_LanguageCreation;
    AGETextCtrl *Units_Class;
    LinkedComboBox *Units_Class_ComboBox[2];
    AGETextCtrl *Units_StandingGraphic[2];
    LinkedComboBox *Units_StandingGraphic_ComboBox[2];
    AGETextCtrl *Units_DyingGraphic[2];
    LinkedComboBox *Units_DyingGraphic_ComboBox[2];
    AGETextCtrl *Units_UndeadMode;
    LinkedCheckBox *Units_UndeadMode_CheckBox;
    AGETextCtrl *Units_HitPoints;
    AGETextCtrl *Units_LineOfSight;
    AGETextCtrl *Units_GarrisonCapacity;
    AGETextCtrl *Units_SizeRadius[3];
    AGETextCtrl *Units_MinCollisionSizeMultiplier;
    AGETextCtrl *Units_TrainSound;
    AGETextCtrl *Units_DamageSound;
    AGETextCtrl *Units_WwiseTrainSound;
    AGETextCtrl *Units_WwiseDamageSound;
    LinkedComboBox *Units_TrainSound_ComboBox;
    LinkedComboBox *Units_DamageSound_ComboBox;
    AGETextCtrl *Units_DeadUnitID;
    AGETextCtrl *Units_BloodUnitID;
    LinkedComboBox *Units_DeadUnitID_ComboBox;
    LinkedComboBox *Units_BloodUnitID_ComboBox;
    AGETextCtrl *Units_SortNumber;
    AGETextCtrl *Units_CanBeBuiltOn;
    LinkedCheckBox *Units_CanBeBuiltOn_CheckBox;
    AGETextCtrl *Units_IconID;
    AGETextCtrl *Units_HideInEditor;
    LinkedCheckBox *Units_HideInEditor_CheckBox;
    AGETextCtrl *Units_Portrait;
    AGETextCtrl *Units_Enabled;
    LinkedCheckBox *Units_Enabled_CheckBox;
    AGETextCtrl *Units_Disabled;
    LinkedCheckBox *Units_Disabled_CheckBox;
    AGETextCtrl *Units_PlacementSideTerrain[2];
    LinkedComboBox *Units_PlacementSideTerrain_ComboBox[2];
    AGETextCtrl *Units_PlacementTerrain[2];
    LinkedComboBox *Units_PlacementTerrain_ComboBox[2];
    AGETextCtrl *Units_ClearanceSize[2];
    AGETextCtrl *Units_HillMode;
    AGETextCtrl *Units_FogVisibility;
    SolidText *Units_FogVisibility_Text;
    AGETextCtrl *Units_TerrainRestriction;
    LinkedComboBox *Units_TerrainRestriction_ComboBox;
    AGETextCtrl *Units_FlyMode;
    LinkedCheckBox *Units_FlyMode_CheckBox;
    AGETextCtrl *Units_ResourceCapacity;
    AGETextCtrl *Units_ResourceDecay;
    AGETextCtrl *Units_BlastDefenseLevel;
    AGETextCtrl *Units_CombatLevel;
    AGETextCtrl *Units_InteractionMode;
    AGETextCtrl *Units_MinimapMode;
    AGETextCtrl *Units_InterfaceKind;
    AGETextCtrl *Units_MultipleAttributeMode;
    AGETextCtrl *Units_MinimapColor;
    AGETextCtrl *Units_LanguageDLLHelp;
    TextIndexControl *Units_DLL_LanguageHelp;
    wxTextCtrl *Units_LanguageDLLConverter[2];
    AGETextCtrl *Units_LanguageDLLHotKeyText;
    TextIndexControl *Units_DLL_LanguageHKText;
    AGETextCtrl *Units_HotKey;
    TextIndexControl *Units_DLL_HotKey4;
    AGETextCtrl *Units_Recyclable;
    LinkedCheckBox *Units_Recyclable_CheckBox;
    AGETextCtrl *Units_TrackAsResource;
    AGETextCtrl *Units_CreateDoppelgangerOnDeath;
    AGETextCtrl *Units_ResourceGroup;
    AGETextCtrl *Units_OcclusionMode;
    AGETextCtrl *Units_ObstructionType;
    AGETextCtrl *Units_ObstructionClass;
    AGETextCtrl *Units_Trait;
    wxBoxSizer *Units_Trait_Grid;
    wxCheckBox *Units_Trait_CheckBox[8];
    AGETextCtrl *Units_Civ;
    LinkedComboBox *Units_Civ_ComboBox;
    AGETextCtrl *Units_Nothing;
    AGETextCtrl *Units_SelectionEffect;
    AGETextCtrl *Units_EditorSelectionColour;
    wxBoxSizer *Units_SelectionRadiusBox;
    AGETextCtrl *Units_SelectionRadius[3];
    AGETextCtrl *ResourceStorage_Type[3];
    LinkedComboBox *ResourceStorage_Type_ComboBox[3];
    AGETextCtrl *ResourceStorage_Amount[3];
    AGETextCtrl *ResourceStorage_Mode[3];
    AGETextCtrl *Units_SelectionSound;
    AGETextCtrl *Units_WwiseSelectionSound;
    LinkedComboBox *Units_SelectionSound_ComboBox;
    AGETextCtrl *Units_DyingSound;
    AGETextCtrl *Units_WwiseDyingSound;
    LinkedComboBox *Units_DyingSound_ComboBox;
    AGETextCtrl *Units_AttackReaction;
    AGETextCtrl *Units_ConvertTerrain;
    StringControl *Units_Name;
    StringControl *Units_Name2;
    AGETextCtrl *Units_Unitline;
    LinkedComboBox *Units_Unitline_ComboBox;
    AGETextCtrl *Units_MinTechLevel;
    LinkedComboBox *Units_MinTechLevel_ComboBox;
    AGETextCtrl *Units_CopyID;
    AGETextCtrl *Units_BaseID;
    AGETextCtrl *Units_TelemetryID;

//  Type 20+

    AGETextCtrl *Units_Speed;

//  Type 30+

    AGETextCtrl *Units_WalkingGraphic[2];
    LinkedComboBox *Units_WalkingGraphic_ComboBox[2];
    AGETextCtrl *Units_RotationSpeed;
    AGETextCtrl *Units_SizeClass;
    AGETextCtrl *Units_TrackingUnit;
    LinkedComboBox *Units_TrackingUnit_ComboBox;
    AGETextCtrl *Units_TrackingUnitMode;
    AGETextCtrl *Units_TrackingUnitDensity;
    AGETextCtrl *Units_MoveAlgorithm;
    std::array<AGETextCtrl*, 5> Units_RotationAngles;

//  Type 40+

    SolidText *Units_DefaultTaskID_Text;
    AGETextCtrl *Units_DefaultTaskID;
    LinkedComboBox *Units_DefaultTaskID_ComboBox;
    AGETextCtrl *Units_SearchRadius;
    AGETextCtrl *Units_WorkRate;
    AGETextCtrl *Units_TaskSwapGroup;
    AGETextCtrl *Units_AttackSound;
    AGETextCtrl *Units_WwiseAttackSound;
    LinkedComboBox *Units_AttackSound_ComboBox;
    AGETextCtrl *Units_MoveSound;
    AGETextCtrl *Units_WwiseMoveSound;
    LinkedComboBox *Units_MoveSound_ComboBox;
    AGETextCtrl *Units_RunPattern;
    SolidText *Units_RunPattern_Text;
    AGETextCtrl *Units_Exists;

//  Type 50+

    NumberControl *Units_BaseArmor;
    AGETextCtrl *Units_DefenseTerrainBonus;
    LinkedComboBox *Units_DefenseTerrainBonus_ComboBox;
    AGETextCtrl *Units_BonusDamageResistance;
    AGETextCtrl *Units_MaxRange;
    AGETextCtrl *Units_BlastWidth;
    AGETextCtrl *Units_ReloadTime;
    AGETextCtrl *Units_ProjectileUnitID;
    LinkedComboBox *Units_ProjectileUnitID_ComboBox;
    AGETextCtrl *Units_AccuracyPercent;
    AGETextCtrl *Units_TowerMode;
    SolidText *Units_TowerMode_Text;
    AGETextCtrl *Units_Delay;
    AGETextCtrl *Units_GraphicDisplacement[3];
    AGETextCtrl *Units_BlastAttackLevel;
    AGETextCtrl *Units_BlastDamage;
    AGETextCtrl *Units_MinRange;
    AGETextCtrl *Units_AccuracyDispersion;
    AGETextCtrl *Units_AttackGraphic;
    LinkedComboBox *Units_AttackGraphic_ComboBox;
    AGETextCtrl *Units_DisplayedMeleeArmour;
    AGETextCtrl *Units_DisplayedAttack;
    AGETextCtrl *Units_DisplayedRange;
    AGETextCtrl *Units_DisplayedReloadTime;

//  Type 60 only

    AGETextCtrl *Units_ProjectileType;
    AGETextCtrl *Units_SmartMode;
    AGETextCtrl *Units_HitMode;
    AGETextCtrl *Units_VanishMode;
    AGETextCtrl *Units_AreaEffectSpecials;
    AGETextCtrl *Units_ProjectileArc;

//  Type 70+

    AGETextCtrl *Units_CostType[3];
    LinkedComboBox *Units_CostType_ComboBox[3];
    AGETextCtrl *Units_CostAmount[3];
    AGETextCtrl *Units_CostUsed[3];
    LinkedCheckBox *Units_CostUsed_CheckBox[3];
    AGETextCtrl *Units_TrainTime;
    AGETextCtrl *Units_TrainLocationID;
    LinkedComboBox *Units_TrainLocationID_ComboBox;
    AGETextCtrl *Units_ButtonID;
    AGETextCtrl *Units_RearAttackModifier;
    AGETextCtrl *Units_FlankAttackModifier;
    AGETextCtrl *Units_CreatableType;
    AGETextCtrl *Units_HeroMode;
    LinkedCheckBox *Units_HeroMode_CheckBox;
    AGETextCtrl *Units_GarrisonGraphic;
    LinkedComboBox *Units_GarrisonGraphic_ComboBox;
    AGETextCtrl *Units_MissileCount;
    AGETextCtrl *Units_MissileDuplicationCount;
    AGETextCtrl *Units_AttackMissileDuplicationSpawning[3];
    AGETextCtrl *Units_AttackMissileDuplicationUnit;
    LinkedComboBox *Units_AttackMissileDuplicationUnit_ComboBox;
    AGETextCtrl *Units_ChargingGraphic;
    LinkedComboBox *Units_ChargingGraphic_ComboBox;
    AGETextCtrl *Units_ChargingMode;
    AGETextCtrl *Units_DisplayedPierceArmour;
    AGETextCtrl *Units_SpawningGraphic;
    AGETextCtrl *Units_UpgradeGraphic;
    AGETextCtrl *Units_HeroGlowGraphic;
    LinkedComboBox *Units_SpawningGraphic_ComboBox;
    LinkedComboBox *Units_UpgradeGraphic_ComboBox;
    LinkedComboBox *Units_HeroGlowGraphic_ComboBox;
    AGETextCtrl *Units_MaxCharge;
    AGETextCtrl *Units_RechargeRate;
    AGETextCtrl *Units_ChargeEvent;
    AGETextCtrl *Units_ChargeType;
    AGETextCtrl *Units_MinConversionTimeMod;
    AGETextCtrl *Units_MaxConversionTimeMod;
    AGETextCtrl *Units_ConversionChanceMod;

//  Type 80

    AGETextCtrl *Units_ConstructionGraphicID;
    AGETextCtrl *Units_SnowGraphicID;
    AGETextCtrl *Units_DestructionGraphicID;
    AGETextCtrl *Units_DestructionRubbleGraphicID;
    AGETextCtrl *Units_ResearchingGraphic;
    AGETextCtrl *Units_ResearchCompletedGraphic;
    LinkedComboBox *Units_ConstructionGraphicID_ComboBox;
    LinkedComboBox *Units_SnowGraphicID_ComboBox;
    LinkedComboBox *Units_DestructionGraphicID_ComboBox;
    LinkedComboBox *Units_DestructionRubbleGraphicID_ComboBox;
    LinkedComboBox *Units_ResearchingGraphic_ComboBox;
    LinkedComboBox *Units_ResearchCompletedGraphic_ComboBox;
    AGETextCtrl *Units_AdjacentMode;
    LinkedCheckBox *Units_AdjacentMode_CheckBox;
    AGETextCtrl *Units_IconAngle;
    AGETextCtrl *Units_DisappearsWhenBuilt;
    LinkedCheckBox *Units_BuildAndVanish_CheckBox;
    AGETextCtrl *Units_StackUnitID;
    LinkedComboBox *Units_StackUnitID_ComboBox;
    AGETextCtrl *Units_TerrainID;
    LinkedComboBox *Units_TerrainID_ComboBox;
    AGETextCtrl *Units_OldOverlayID;
    AGETextCtrl *Units_ResearchID;
    LinkedComboBox *Units_ResearchID_ComboBox;
    AGETextCtrl *Units_CanBurn;
    AGETextCtrl *Units_AnnexUnit[4];
    LinkedComboBox *Units_AnnexUnit_ComboBox[4];
    AGETextCtrl *Units_AnnexUnitMisplacement[4][2];
    AGETextCtrl *Units_HeadUnit;
    LinkedComboBox *Units_HeadUnit_ComboBox;
    AGETextCtrl *Units_TransformUnit;
    LinkedComboBox *Units_TransformUnit_ComboBox;
    AGETextCtrl *Units_TransformSound;
    AGETextCtrl *Units_WwiseTransformSound;
    LinkedComboBox *Units_TransformSound_ComboBox;
    AGETextCtrl *Units_ConstructionSound;
    AGETextCtrl *Units_WwiseConstructionSound;
    LinkedComboBox *Units_ConstructionSound_ComboBox;
    AGETextCtrl *Units_GarrisonType;
    wxBoxSizer *Units_GarrisonType_Grid;
    wxCheckBox *Units_GarrisonType_CheckBox[8];
    AGETextCtrl *Units_GarrisonHealRate;
    AGETextCtrl *Units_GarrisonRepairRate;
    AGETextCtrl *Units_PileUnit;
    LinkedComboBox *Units_PileUnit_ComboBox;
    std::array<AGETextCtrl*, 6> Units_LootSwitch;

//  Data Container Names
//  Type 10+

    SolidText *Units_Type_Text;
    SolidText *Units_ID1_Text;
    SolidText *Units_LanguageDLLName_Text;
    SolidText *Units_LanguageDLLCreation_Text;
    SolidText *Units_Class_Text;
    SolidText *Units_StandingGraphic_Text;
    SolidText *Units_DyingGraphic_Text;
    SolidText *Units_HitPoints_Text;
    SolidText *Units_LineOfSight_Text;
    SolidText *Units_GarrisonCapacity_Text;
    SolidText *Units_SizeRadius_Text;
    SolidText *Units_MinCollisionSizeMultiplier_Text;
    SolidText *Units_TrainSound_Text;
    SolidText *Units_DamageSound_Text;
    SolidText *Units_DeadUnitID_Text;
    SolidText *Units_BloodUnitID_Text;
    SolidText *Units_SortNumber_Text;
    SolidText *Units_IconID_Text;
    SolidText *Units_Portrait_Text;
    SolidText *Units_PlacementSideTerrain_Text;
    SolidText *Units_PlacementTerrain_Text;
    SolidText *Units_ClearanceSize_Text;
    SolidText *Units_HillMode_Text;
    SolidText *Units_TerrainRestriction_Text;
    SolidText *Units_ResourceCapacity_Text;
    SolidText *Units_ResourceDecay_Text;
    SolidText *Units_BlastDefenseLevel_Text;
    SolidText *Units_CombatLevel_Text;
    SolidText *Units_InteractionMode_Text;
    SolidText *Units_MinimapMode_Text;
    SolidText *Units_InterfaceKind_Text;
    SolidText *Units_MultipleAttributeMode_Text;
    SolidText *Units_MinimapColor_Text;
    SolidText *Units_LanguageDLLHelp_Text;
    SolidText *Units_LanguageDLLConverter_Text[2];
    SolidText *Units_LanguageDLLHotKeyText_Text;
    SolidText *Units_HotKey_Text;
    LinkedCheckBox *Units_TrackAsResource_CheckBox;
    SolidText *Units_CreateDoppelgangerOnDeath_Text;
    SolidText *Units_ResourceGroup_Text;
    SolidText *Units_OcclusionMode_Text;
    SolidText *Units_ObstructionType_Text;
    SolidText *Units_ObstructionClass_Text;
    SolidText *Units_Trait_Text;
    SolidText *Units_Civ_Text;
    SolidText *Units_Nothing_Text;
    SolidText *Units_SelectionEffect_Text;
    SolidText *Units_EditorSelectionColour_Text;
    SolidText *Units_SelectionRadius_Text;
    SolidText *ResourceStorage_Type_Text;
    SolidText *ResourceStorage_Amount_Text;
    SolidText *ResourceStorage_Mode_Text;
    SolidText *Units_SelectionSound_Text;
    SolidText *Units_DyingSound_Text;
    SolidText *Units_AttackReaction_Text;
    SolidText *Units_ConvertTerrain_Text;
    SolidText *Units_Name_Text;
    SolidText *Units_Name2_Text;
    SolidText *Units_Unitline_Text;
    SolidText *Units_MinTechLevel_Text;
    SolidText *Units_CopyID_Text;
    SolidText *Units_BaseID_Text;
    SolidText *Units_TelemetryID_Text;

//  Type 20+

    SolidText *Units_Speed_Text;

//  Type 30+

    SolidText *Units_WalkingGraphic_Text;
    SolidText *Units_RotationSpeed_Text;
    SolidText *Units_SizeClass_Text;
    SolidText *Units_TrackingUnit_Text;
    SolidText *Units_TrackingUnitMode_Text;
    SolidText *Units_TrackingUnitDensity_Text;
    SolidText *Units_MoveAlgorithm_Text;
    SolidText *Units_RotationAngles_Text;
    wxString Units_RotationAngles_Label;
    std::array<SolidText*, 5> Units_TurnStats_Text;

//  Type 40+

    SolidText *Units_SearchRadius_Text;
    SolidText *Units_WorkRate_Text;
    SolidText *Units_TaskSwapGroup_Text;
    SolidText *Units_AttackSound_Text;
    SolidText *Units_MoveSound_Text;
    SolidText *Units_Exists_Text;

//  Type 50+

    SolidText *Units_BaseArmor_Text;
    SolidText *Units_DefenseTerrainBonus_Text;
    SolidText *Units_BonusDamageResistance_Text;
    SolidText *Units_MaxRange_Text;
    SolidText *Units_BlastWidth_Text;
    SolidText *Units_ReloadTime_Text;
    SolidText *Units_ProjectileUnitID_Text;
    SolidText *Units_AccuracyPercent_Text;
    SolidText *Units_Delay_Text;
    SolidText *Units_GraphicDisplacement_Text;
    SolidText *Units_BlastAttackLevel_Text;
    SolidText *Units_BlastDamage_Text;
    SolidText *Units_MinRange_Text;
    SolidText *Units_AccuracyDispersion_Text;
    SolidText *Units_AttackGraphic_Text;
    SolidText *Units_DisplayedMeleeArmour_Text;
    SolidText *Units_DisplayedAttack_Text;
    SolidText *Units_DisplayedRange_Text;
    SolidText *Units_DisplayedReloadTime_Text;

//  Type 60 only

    SolidText *Units_ProjectileType_Text;
    SolidText *Units_SmartMode_Text;
    SolidText *Units_HitMode_Text;
    SolidText *Units_VanishMode_Text;
    SolidText *Units_AreaEffectSpecials_Text;
    SolidText *Units_ProjectileArc_Text;

//  Type 70+

    SolidText *Units_CostType_Text;
    SolidText *Units_CostAmount_Text;
    SolidText *Units_CostUsed_Text;
    SolidText *Units_TrainTime_Text;
    SolidText *Units_TrainLocationID_Text;
    SolidText *Units_ButtonID_Text;
    SolidText *Units_RearAttackModifier_Text;
    SolidText *Units_FlankAttackModifier_Text;
    SolidText *Units_CreatableType_Text;
    SolidText *Units_GarrisonGraphic_Text;
    SolidText *Units_MissileCount_Text;
    SolidText *Units_MissileDuplicationCount_Text;
    SolidText *Units_AttackMissileDuplicationSpawning_Text;
    SolidText *Units_AttackMissileDuplicationUnit_Text;
    SolidText *Units_ChargingGraphic_Text;
    SolidText *Units_ChargingMode_Text;
    SolidText *Units_DisplayedPierceArmour_Text;
    SolidText *Units_SpawningGraphic_Text;
    SolidText *Units_UpgradeGraphic_Text;
    SolidText *Units_HeroGlowGraphic_Text;
    SolidText *Units_MaxCharge_Text;
    SolidText *Units_RechargeRate_Text;
    SolidText *Units_ChargeEvent_Text;
    SolidText *Units_ChargeType_Text;
    SolidText *Units_MinConversionTimeMod_Text;
    SolidText *Units_MaxConversionTimeMod_Text;
    SolidText *Units_ConversionChanceMod_Text;

//  Type 80

    SolidText *Units_ConstructionGraphicID_Text;
    SolidText *Units_SnowGraphicID_Text;
    SolidText *Units_DestructionGraphicID_Text;
    SolidText *Units_DestructionRubbleGraphicID_Text;
    SolidText *Units_ResearchingGraphic_Text;
    SolidText *Units_ResearchCompletedGraphic_Text;
    SolidText *Units_IconAngle_Text;
    SolidText *Units_StackUnitID_Text;
    SolidText *Units_TerrainID_Text;
    SolidText *Units_OldOverlayID_Text;
    SolidText *Units_ResearchID_Text;
    SolidText *Units_CanBurn_Text;
    SolidText *Units_AnnexUnit_Text;
    SolidText *Units_AnnexUnitMisplacement_Text;
    SolidText *Units_HeadUnit_Text;
    SolidText *Units_TransformUnit_Text;
    SolidText *Units_TransformSound_Text;
    SolidText *Units_ConstructionSound_Text;
    SolidText *Units_GarrisonType_Text;
    SolidText *Units_GarrisonHealRate_Text;
    SolidText *Units_GarrisonRepairRate_Text;
    SolidText *Units_PileUnit_Text;
    SolidText *Units_LootSwitch_Text;

//  Invisible Holder Windows
//  Type 10+

    wxBoxSizer *Units_Type_Holder;
    wxBoxSizer *Units_ID1_Holder;
    wxBoxSizer *Units_LanguageDLLName_Holder;
    wxBoxSizer *Units_LanguageDLLCreation_Holder;
    wxBoxSizer *Units_StandingGraphic_Holder;
    wxGridSizer *Units_StandingGraphic_Grid;
    wxBoxSizer *Units_DyingGraphic_Holder;
    wxGridSizer *Units_DyingGraphic_Grid;
    wxBoxSizer *Units_UndeadMode_Holder;
    wxBoxSizer *Units_HitPoints_Holder;
    wxBoxSizer *Units_LineOfSight_Holder;
    wxBoxSizer *Units_SizeRadius_Holder;
    wxBoxSizer *Units_SizeRadius_Grid;
    wxBoxSizer *Units_MinCollisionSizeMultiplier_Holder;
    wxBoxSizer *Units_TrainSound_Holder;
    wxBoxSizer *Units_DamageSound_Holder;
    wxBoxSizer *Units_DeadUnitID_Holder;
    wxBoxSizer *Units_BloodUnitID_Holder;
    wxBoxSizer *Units_SortNumber_Holder;
    wxBoxSizer *Units_CanBeBuiltOn_Holder;
    wxBoxSizer *Units_IconID_Holder;
    APanel *Units_IconID_SLP;
    wxBoxSizer *Units_HideInEditor_Holder;
    wxBoxSizer *Units_Portrait_Holder;
    wxBoxSizer *Units_Enabled_Holder;
    wxBoxSizer *Units_Disabled_Holder;
    wxBoxSizer *Units_PlacementSideTerrain_Holder;
    wxGridSizer *Units_PlacementSideTerrainGrid_Holder;
    wxBoxSizer *Units_PlacementTerrain_Holder;
    wxGridSizer *Units_PlacementTerrainGrid_Holder;
    wxBoxSizer *Units_ClearanceSize_Holder;
    wxBoxSizer *Units_ClearanceSize_Grid;
    wxBoxSizer *Units_HillMode_Holder;
    wxBoxSizer *Units_FogVisibility_Holder;
    wxBoxSizer *Units_TerrainRestriction_Holder;
    wxBoxSizer *Units_FlyMode_Holder;
    wxBoxSizer *Units_BlastDefenseLevel_Holder;
    wxBoxSizer *Units_CombatLevel_Holder;
    wxBoxSizer *Units_InteractionMode_Holder;
    wxBoxSizer *Units_MinimapMode_Holder;
    wxBoxSizer *Units_InterfaceKind_Holder;
    wxBoxSizer *Units_MultipleAttributeMode_Holder;
    wxBoxSizer *Units_MinimapColor_Holder;
    wxBoxSizer *Units_LanguageDLLHelp_Holder;
    wxBoxSizer *Units_LanguageDLLConverter_Holder[2];
    wxBoxSizer *Units_LanguageDLLHotKeyText_Holder;
    wxBoxSizer *Units_HotKey_Holder;
    wxBoxSizer *Units_Recyclable_Holder;
    wxBoxSizer *Units_TrackAsResource_Holder;
    wxBoxSizer *Units_CreateDoppelgangerOnDeath_Holder;
    wxBoxSizer *Units_ResourceGroup_Holder;
    wxBoxSizer *Units_OcclusionMode_Holder;
    wxBoxSizer *Units_ObstructionType_Holder;
    wxBoxSizer *Units_ObstructionClass_Holder;
    wxBoxSizer *Units_Trait_Holder;
    wxBoxSizer *Units_Civ_Holder;
    wxBoxSizer *Units_Nothing_Holder;
    wxBoxSizer *Units_SelectionEffect_Holder;
    wxBoxSizer *Units_EditorSelectionColour_Holder;
    wxBoxSizer *Units_SelectionRadius_Holder;
    wxStaticBoxSizer *Units_ResourceStorageHeader_Holder;
    wxBoxSizer *Units_ResourceStorage_Texts;
    std::array<wxBoxSizer*, 3> Units_ResourceStorage_Holder;
    wxBoxSizer *Units_SelectionSound_Holder;
    wxBoxSizer *Units_DyingSound_Holder;
    wxBoxSizer *Units_AttackReaction_Holder;
    wxBoxSizer *Units_ConvertTerrain_Holder;
    wxBoxSizer *Units_Name_Holder;
    wxBoxSizer *Units_Name2_Holder;
    wxBoxSizer *Units_Unitline_Holder;
    wxBoxSizer *Units_MinTechLevel_Holder;
    wxBoxSizer *Units_CopyID_Holder;
    wxBoxSizer *Units_BaseID_Holder;
    wxBoxSizer *Units_TelemetryID_Holder;

//  Type 20+

    wxBoxSizer *Units_Speed_Holder;

//  Type 30+

    wxBoxSizer *Units_WalkingGraphic_Holder;
    wxGridSizer *Units_WalkingGraphic_Grid;
    wxBoxSizer *Units_RotationSpeed_Holder;
    wxBoxSizer *Units_SizeClass_Holder;
    wxBoxSizer *Units_TrackingUnit_Holder;
    wxBoxSizer *Units_TrackingUnitMode_Holder;
    wxBoxSizer *Units_TrackingUnitDensity_Holder;
    wxBoxSizer *Units_MoveAlgorithm_Holder;
    wxBoxSizer *Units_RotationAngles_Holder;
    wxGridSizer *Units_RotationAngles_Grid;

//  Type 40+

    wxBoxSizer *Units_DefaultTaskID_Holder;
    wxBoxSizer *Units_SearchRadius_Holder;
    wxBoxSizer *Units_TaskSwapGroup_Holder;
    wxBoxSizer *Units_AttackSound_Holder;
    wxBoxSizer *Units_MoveSound_Holder;
    wxBoxSizer *Units_RunPattern_Holder;
    wxBoxSizer *Units_Exists_Holder;

//  Type 50+

    wxBoxSizer *Units_BaseArmor_Holder;
    wxBoxSizer *Units_DefenseTerrainBonus_Holder;
    wxBoxSizer *Units_BonusDamageResistance_Holder;
    wxBoxSizer *Units_MaxRange_Holder;
    wxBoxSizer *Units_BlastWidth_Holder;
    wxBoxSizer *Units_ReloadTime_Holder;
    wxBoxSizer *Units_ProjectileUnitID_Holder;
    wxBoxSizer *Units_AccuracyPercent_Holder;
    wxBoxSizer *Units_TowerMode_Holder;
    wxBoxSizer *Units_Delay_Holder;
    wxBoxSizer *Units_GraphicDisplacement_Holder;
    wxBoxSizer *Units_GraphicDisplacement_Grid;
    wxBoxSizer *Units_BlastAttackLevel_Holder;
    wxBoxSizer *Units_BlastDamage_Holder;
    wxBoxSizer *Units_MinRange_Holder;
    wxBoxSizer *Units_AccuracyDispersion_Holder;
    wxBoxSizer *Units_AttackGraphic_Holder;
    wxBoxSizer *Units_DisplayedMeleeArmour_Holder;
    wxBoxSizer *Units_DisplayedAttack_Holder;
    wxBoxSizer *Units_DisplayedRange_Holder;
    wxBoxSizer *Units_DisplayedReloadTime_Holder;

//  Type 60 only

    wxBoxSizer *Units_ProjectileType_Holder;
    wxBoxSizer *Units_SmartMode_Holder;
    wxBoxSizer *Units_HitMode_Holder;
    wxBoxSizer *Units_VanishMode_Holder;
    wxBoxSizer *Units_AreaEffectSpecials_Holder;
    wxBoxSizer *Units_ProjectileArc_Holder;

//  Type 70+

    wxStaticBoxSizer *Units_CostHeader_Holder;
    wxBoxSizer *Unit_Cost_Texts;
    std::array<wxBoxSizer*, 3> Unit_Cost_Sizers;
    wxBoxSizer *Units_TrainTime_Holder;
    wxBoxSizer *Units_TrainLocationID_Holder;
    wxBoxSizer *Units_ButtonID_Holder;
    wxBoxSizer *Units_RearAttackModifier_Holder;
    wxBoxSizer *Units_FlankAttackModifier_Holder;
    wxBoxSizer *Units_CreatableType_Holder;
    wxBoxSizer *Units_HeroMode_Holder;
    wxBoxSizer *Units_GarrisonGraphic_Holder;
    wxBoxSizer *Units_MissileCount_Holder;
    wxBoxSizer *Units_MissileDuplicationCount_Holder;
    wxBoxSizer *Units_AttackMissileDuplicationSpawning_Holder;
    wxBoxSizer *Units_AttackMissileDuplicationSpawning_Grid;
    wxBoxSizer *Units_AttackMissileDuplicationUnit_Holder;
    wxBoxSizer *Units_ChargingGraphic_Holder;
    wxBoxSizer *Units_ChargingMode_Holder;
    wxBoxSizer *Units_DisplayedPierceArmour_Holder;
    wxBoxSizer *Units_SpawningGraphic_Holder;
    wxBoxSizer *Units_UpgradeGraphic_Holder;
    wxBoxSizer *Units_HeroGlowGraphic_Holder;

//  Type 80

    wxBoxSizer *Units_ConstructionGraphicID_Holder;
    wxBoxSizer *Units_SnowGraphicID_Holder;
    wxBoxSizer *Units_DestructionGraphicID_Holder;
    wxBoxSizer *Units_DestructionRubbleGraphicID_Holder;
    wxBoxSizer *Units_ResearchingGraphic_Holder;
    wxBoxSizer *Units_ResearchCompletedGraphic_Holder;
    wxBoxSizer *Units_AdjacentMode_Holder;
    wxBoxSizer *Units_IconAngle_Holder;
    wxBoxSizer *Units_BuildAndVanish_Holder;
    wxBoxSizer *Units_StackUnitID_Holder;
    wxBoxSizer *Units_TerrainID_Holder;
    wxBoxSizer *Units_OldOverlayID_Holder;
    wxBoxSizer *Units_ResearchID_Holder;
    wxBoxSizer *Units_CanBurn_Holder;
    wxGridSizer *Units_AnnexUnit_Grid;
    wxBoxSizer *Units_AnnexUnit1_Holder;
    wxGridSizer *Units_AnnexUnitMisplacement_Grid;
    wxBoxSizer *Units_AnnexUnitMisplacement1_Holder;
    wxBoxSizer *Units_HeadUnit_Holder;
    wxBoxSizer *Units_TransformUnit_Holder;
    wxBoxSizer *Units_TransformSound_Holder;
    wxBoxSizer *Units_ConstructionSound_Holder;
    wxBoxSizer *Units_GarrisonType_Holder;
    wxBoxSizer *Units_GarrisonRepairRate_Holder;
    wxBoxSizer *Units_PileUnit_Holder;
    wxBoxSizer *Units_LootSwitch_Holder;
    wxGridSizer *Units_LootSwitch_Grid;

//  Unit Controls SubControls

    wxBoxSizer *Units_DamageGraphics_Holder_Data;
    AGETextCtrl *DamageGraphics_GraphicID;
    LinkedComboBox *DamageGraphics_GraphicID_ComboBox;
    AGETextCtrl *DamageGraphics_DamagePercent;
    AGETextCtrl *DamageGraphics_ApplyMode;
    SolidText *DamageGraphics_GraphicID_Text;
    SolidText *DamageGraphics_DamagePercent_Text;
    SolidText *DamageGraphics_ApplyMode_Text;
    wxBoxSizer *DamageGraphics_GraphicID_Holder;
    wxBoxSizer *DamageGraphics_DamagePercent_Holder;
    wxBoxSizer *DamageGraphics_ApplyMode_Holder;
    wxStaticBoxSizer *Units_DamageGraphics;
    wxBoxSizer *Units_DamageGraphics_ListArea;
    wxTextCtrl *Units_DamageGraphics_Search;
    wxTextCtrl *Units_DamageGraphics_Search_R;
    ProperList *Units_DamageGraphics_ListV;
    wxGridSizer *Units_DamageGraphics_Buttons;
    wxButton *Units_DamageGraphics_Add;
    wxButton *Units_DamageGraphics_Insert;
    wxButton *Units_DamageGraphics_Delete;
    wxButton *Units_DamageGraphics_Copy;
    wxButton *Units_DamageGraphics_Paste;
    wxButton *Units_DamageGraphics_PasteInsert;
    wxButton *Units_DamageGraphics_CopyToUnits;

    AGETextCtrl *DropSites_UnitID;
    LinkedComboBox *DropSites_UnitID_ComboBox;
    SolidText *DropSites_UnitID_Text;
    wxBoxSizer *DropSites_UnitID_Holder;
    wxStaticBoxSizer *Units_DropSites;
    wxBoxSizer *Units_DropSites_ListArea;
    wxTextCtrl *Units_DropSites_Search;
    wxTextCtrl *Units_DropSites_Search_R;
    ProperList *Units_DropSites_ListV;
    wxBoxSizer *Units_DropSites_Buttons_Upper;
    wxBoxSizer *Units_DropSites_Buttons_Lower;
    wxButton *Units_DropSites_Add;
    wxButton *Units_DropSites_Insert;
    wxButton *Units_DropSites_Delete;
    wxButton *Units_DropSites_Copy;
    wxButton *Units_DropSites_Paste;
    wxButton *Units_DropSites_PasteInsert;
    wxButton *Units_DropSites_CopyToUnits;

    wxBoxSizer *Units_Attacks_Holder;
    wxGridSizer *Units_Attacks_Holder_Data;
    AGETextCtrl *Attacks_Class;
    LinkedComboBox *Attacks_Class_ComboBox[2];
    AGETextCtrl *Attacks_Amount;
    SolidText *Attacks_Class_Text;
    SolidText *Attacks_Amount_Text;
    wxBoxSizer *Attacks_Class_Holder;
    wxBoxSizer *Attacks_Amount_Holder;
    wxStaticBoxSizer *Units_Attacks;
    wxBoxSizer *Units_Attacks_ListArea;
    wxBoxSizer *Units_Attacks_DataArea;
    wxTextCtrl *Units_Attacks_Search;
    wxTextCtrl *Units_Attacks_Search_R;
    ProperList *Units_Attacks_ListV;
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
    wxGridSizer *Units_Defense_Holder;
    AGETextCtrl *Armors_Class;
    AGETextCtrl *Armors_Amount;
    SolidText *Armors_Class_Text;
    SolidText *Armors_Amount_Text;
    wxBoxSizer *Armors_Class_Holder;
    wxBoxSizer *Armors_Amount_Holder;
    wxStaticBoxSizer *Units_Armors;
    wxBoxSizer *Units_Armors_ListArea;
    wxBoxSizer *Units_Armors_DataArea;
    wxTextCtrl *Units_Armors_Search;
    wxTextCtrl *Units_Armors_Search_R;
    ProperList *Units_Armors_ListV;
    wxGridSizer *Units_Armors_Buttons;
    wxButton *Units_Armors_Add;
    wxButton *Units_Armors_Insert;
    wxButton *Units_Armors_Delete;
    wxButton *Units_Armors_Copy;
    wxButton *Units_Armors_Paste;
    wxButton *Units_Armors_PasteInsert;
    wxButton *Units_Armors_CopyToUnits;

//  End of Unit Controls

    wxBoxSizer *Units_Main; // Unit window

    wxStaticBoxSizer *Units_Units;  // Unit list section vertical division excluding window borders
    //wxStaticLine *Units_Line;
    wxBoxSizer *Units_Special;
    AGEComboBox *Units_Civs_List;  // Civ list combo box
    wxBoxSizer *Units_Searches[2];
    wxTextCtrl *Units_Search;   // Unit search
    wxTextCtrl *Units_Search_R; // Unit reverse search
    AGEComboBox *Units_FilterSelector;
    AGEComboBox *Units_SearchFilters[2];   // Unit search
    wxCheckBox *Units_UseAnd[2];
    ProperList *Units_ListV;
    wxButton *Units_Add;    // Buttons
    wxButton *Units_Insert;
    wxButton *Units_Delete;
    wxButton *Units_Copy;
    wxButton *Units_Paste;
    wxButton *Units_PasteInsert;
    SolidText *Units_Info;
    //wxButton *Units_Extract;
    //wxButton *Units_Import;
    wxButton *Units_Enable;
    wxButton *Units_Disable;
    wxButton *Units_SpecialCopy;
    wxButton *Units_SpecialPaste;
    wxButton *Units_SpecialPasteInsert;
    AGEComboBox *Units_SpecialCopy_Options;
    wxCheckBox *Units_SpecialCopy_Civs;
//  wxButton *Units_Undo;

    wxBoxSizer *Units_DataArea; // Unit window other-than unit-list-section

    std::vector<AGETextCtrl*> uiGroupUnit, uiGroupUnitDmgGraphic, uiGroupUnitTask;
    wxBoxSizer *Units_ScrollSpace;
    wxStaticBoxSizer *Units_Identity_Holder;
    wxBoxSizer *Units_TypeArea_Holder;
    wxStaticBoxSizer *Units_LangDLLArea_Holder;
    wxStaticBoxSizer *Units_GraphicsArea_Holder;
    wxBoxSizer *Units_GraphicsArea1_Holder;
    wxBoxSizer *Units_GraphicsArea4_Holder;
    wxGridSizer *Units_GraphicsArea5_Holder;
    wxStaticBoxSizer *Units_StatsArea_Holder;
    wxBoxSizer *Units_StatsArea1A_Sizer;
    wxBoxSizer *Units_StatsArea1B_Sizer;
    wxSizer *Units_Garrison_Grid;
    wxSizer *Units_Resource_Grid;
    wxSizer *Units_Charge_Grid;
    wxStaticBoxSizer *Units_ProjectileArea_Holder;
    wxBoxSizer *Units_P1, *Units_P2, *Units_P3, *Units_AS2_Holder;
    wxStaticBoxSizer *Units_Attributes_Holder;
    wxBoxSizer *Units_A1_Grid, *Units_A2_Grid, *Units_A3_Grid, *Units_A4_Grid, *Units_AS_Holder, *Units_AS1_Grid;
    wxGridSizer *Units_A5_Grid, *Units_AM1_Grid, *Units_AB1_Grid;
    wxBoxSizer *Units_LangRegular_Holder;
    wxBoxSizer *Units_LangHotKey_Holder;
    wxBoxSizer *Units_Tracking_Grid;
    wxBoxSizer *Units_Training_Grid;
    wxStaticBoxSizer *Units_SoundsArea_Holder;
    wxBoxSizer *Units_SoundsArea1_Holder;
    wxBoxSizer *Units_SoundsArea2_Grid;
    wxGridSizer *Units_Obsoletes_Holder;
    wxStaticBoxSizer *Units_Obsoletes_Area;
    wxStaticBoxSizer *TasksArea_Holder;
    wxBoxSizer *Units_Top_Holder;
    wxWrapSizer *Units_TopGrid_Holder;
    std::vector<wxCheckBox*> Units_CivBoxes;
    //std::vector<SolidText*> Units_CivLabels;
    wxButton *Units_CopyTo;
    wxCheckBox *Units_CopyGraphics;
    wxCheckBox *Units_AutoCopy;
    SolidText *Units_CopyToText;
    SolidText *Units_GraphicSetText;
    AGEComboBox *Units_GraphicSet;
    wxButton *Units_SelectAll;
    wxButton *Units_SelectClear;

//  Unit Attributes section

    wxBoxSizer *TaskHolder_Lists;
    SolidText *Units_UnitHeads_Name;

    wxTextCtrl *Units_Tasks_Search;
    wxTextCtrl *Units_Tasks_Search_R;
    ProperList *Units_Tasks_ListV;
    wxGridSizer *Units_Tasks_Buttons;
    wxButton *Units_Tasks_Add;
    wxButton *Units_Tasks_Insert;
    wxButton *Units_Tasks_Delete;
    wxButton *Units_Tasks_Copy;
    wxButton *Units_Tasks_Paste;
    wxButton *Units_Tasks_PasteInsert;
    wxButton *Units_Tasks_CopyToUnits;

    wxBoxSizer *TaskHolder_Data;
    wxBoxSizer *Tasks_Known1, *Tasks_Known3;
    wxGridSizer *Tasks_Known2, *Tasks_Known4, *Tasks_Known5;
    wxBoxSizer *Tasks_Type_Holder;
    wxBoxSizer *Tasks_ID_Holder;
    wxBoxSizer *Tasks_IsDefault_Holder;
    wxBoxSizer *Tasks_ActionType_Holder;
    wxBoxSizer *Tasks_ProdResource_Holder;
    wxBoxSizer *Tasks_ClassID_Holder;
    wxBoxSizer *Tasks_UnitID_Holder;
    wxBoxSizer *Tasks_TerrainID_Holder;
    wxBoxSizer *Tasks_ResourceIn_Holder;
    wxBoxSizer *Tasks_ResourceOut_Holder;
    wxBoxSizer *Tasks_Resource_Holder;
    wxBoxSizer *Tasks_WorkValue1_Holder;
    wxBoxSizer *Tasks_WorkValue2_Holder;
    wxBoxSizer *Tasks_WorkRange_Holder;
    wxBoxSizer *Tasks_AutoSearchTargets_Holder;
    wxBoxSizer *Tasks_SearchWaitTime_Holder;
    wxBoxSizer *Tasks_EnableTargeting_Holder;
    wxBoxSizer *Tasks_CombatLevelFlag_Holder;
    wxBoxSizer *Tasks_GatherType_Holder;
    wxBoxSizer *Tasks_WorkFlag2_Holder;
    wxBoxSizer *Tasks_TargetDiplomacy_Holder;
    wxBoxSizer *Tasks_CarryCheck_Holder;
    wxBoxSizer *Tasks_PickForConstruction_Holder;
    std::array<wxBoxSizer*, 6> Tasks_Graphics_Holder;

    SolidText *Tasks_Type_Text;
    SolidText *Tasks_ID_Text;
    LinkedCheckBox *Tasks_IsDefault_Text;
    SolidText *Tasks_ActionType_Text;
    SolidText *Tasks_ClassID_Text;
    SolidText *Tasks_UnitID_Text;
    SolidText *Tasks_TerrainID_Text;
    SolidText *Tasks_ResourceIn_Text;
    SolidText *Tasks_ProdResource_Text;
    SolidText *Tasks_ResourceOut_Text;
    SolidText *Tasks_Resource_Text;
    SolidText *Tasks_WorkValue1_Text;
    SolidText *Tasks_WorkValue2_Text;
    SolidText *Tasks_WorkRange_Text;
    SolidText *Tasks_AutoSearchTargets_Text;
    SolidText *Tasks_SearchWaitTime_Text;
    SolidText *Tasks_EnableTargeting_Text;
    LinkedCheckBox *Tasks_CombatLevelFlag_Text;
    SolidText *Tasks_GatherType_Text;
    SolidText *Tasks_WorkFlag2_Text;
    SolidText *Tasks_TargetDiplomacy_Text;
    LinkedCheckBox *Tasks_CarryCheck_Text;
    LinkedCheckBox *Tasks_PickForConstruction_Text;
    std::array<SolidText*, 6> Tasks_Graphics_Text;

    AGETextCtrl *Tasks_Type;
    AGETextCtrl *Tasks_ID;
    AGETextCtrl *Tasks_IsDefault;
    AGETextCtrl *Tasks_ActionType;
    LinkedComboBox *Tasks_ActionType_ComboBox;
    AGETextCtrl *Tasks_ClassID;
    AGETextCtrl *Tasks_UnitID;
    LinkedComboBox *Tasks_UnitID_ComboBox;
    AGETextCtrl *Tasks_TerrainID;
    LinkedComboBox *Tasks_TerrainID_ComboBox;
    AGETextCtrl *Tasks_ResourceIn;
    LinkedComboBox *Tasks_ResourceIn_ComboBox;
    AGETextCtrl *Tasks_ProdResource;
    LinkedComboBox *Tasks_ProdResource_ComboBox;
    AGETextCtrl *Tasks_ResourceOut;
    LinkedComboBox *Tasks_ResourceOut_ComboBox;
    AGETextCtrl *Tasks_Resource;
    LinkedComboBox *Tasks_Resource_ComboBox;
    AGETextCtrl *Tasks_WorkValue1;
    AGETextCtrl *Tasks_WorkValue2;
    AGETextCtrl *Tasks_WorkRange;
    AGETextCtrl *Tasks_AutoSearchTargets;
    AGETextCtrl *Tasks_SearchWaitTime;
    AGETextCtrl *Tasks_EnableTargeting;
    AGETextCtrl *Tasks_CombatLevelFlag;
    AGETextCtrl *Tasks_GatherType;
    AGETextCtrl *Tasks_WorkFlag2;
    AGETextCtrl *Tasks_TargetDiplomacy;
    AGETextCtrl *Tasks_CarryCheck;
    AGETextCtrl *Tasks_PickForConstruction;
    AGETextCtrl *Tasks_WwiseResourceGatheringSound;
    AGETextCtrl *Tasks_WwiseResourceDepositSound;
    std::array<AGETextCtrl*, 6> Tasks_Graphics;
    std::array<LinkedComboBox*, 6> Tasks_Graphics_ComboBox;

//  Graphics user interface

    wxBoxSizer *Graphics_Main;
    wxGridSizer *Graphics_Graphics_Buttons;
    wxStaticBoxSizer *Graphics_Graphics;
    wxBoxSizer *Graphics_Graphics_Searches[2];
    wxTextCtrl *Graphics_Graphics_Search;
    wxTextCtrl *Graphics_Graphics_Search_R;
    AGEComboBox *Graphics_SearchFilters[2];
    wxCheckBox *Graphics_Graphics_UseAnd[2];
    ProperList *Graphics_Graphics_ListV;
    wxButton *Graphics_Add;
    wxButton *Graphics_Insert;
    wxButton *Graphics_Delete;
    wxButton *Graphics_Copy;
    wxButton *Graphics_Paste;
    wxButton *Graphics_PasteInsert;
    //wxButton *Graphics_Extract;
    //wxButton *Graphics_Import;
    wxButton *Graphics_NoMirror;
    wxButton *Graphics_Enable;
    wxButton *Graphics_Disable;
    wxButton *Graphics_CopyToEnd;
    wxButton *Graphics_MakeLast;
    wxButton *Graphics_Rename;

    AScrolled *Graphics_Scroller;
    wxBoxSizer *Graphics_ScrollSpace;

    std::vector<AGETextCtrl*> uiGroupGraphic, uiGroupGraphicDelta, uiGroupGraphicSound;
    wxBoxSizer *Graphics_NameArea_Holder;
    wxBoxSizer *Graphics_Name_Holder;
    wxBoxSizer *Graphics_FileName_Holder;
    wxBoxSizer *Graphics_ParticleEffectName_Holder;
    wxBoxSizer *Graphics_SLP_Holder;
    wxBoxSizer *Graphics_Loaded_Holder;
    wxBoxSizer *Graphics_ColorFlag_Holder;
    wxBoxSizer *Graphics_DrawLevel_Holder;
    wxBoxSizer *Graphics_PlayerColor_Holder;
    wxBoxSizer *Graphics_TransparentPicking_Holder;
    wxBoxSizer *Graphics_Coordinates_Holder;
    wxBoxSizer *Graphics_CoordinateGrid_Holder;
    wxBoxSizer *Graphics_SoundID_Holder;
    wxBoxSizer *Graphics_AngleSoundsUsed_Holder;
    wxBoxSizer *Graphics_AngleSoundsUsed1_Holder;
    wxBoxSizer *Graphics_4_Holder;
    wxBoxSizer *Graphics_5_Holder;
    wxBoxSizer *Graphics_FrameCount_Holder;
    wxBoxSizer *Graphics_AngleCount_Holder;
    wxBoxSizer *Graphics_FirstFrame_Holder;
    wxBoxSizer *Graphics_SpeedMultiplier_Holder;
    wxBoxSizer *Graphics_FrameDuration_Holder;
    wxBoxSizer *Graphics_ReplayDelay_Holder;
    wxBoxSizer *Graphics_SequenceType_Holder;
    wxBoxSizer *Graphics_ID_Holder;
    wxBoxSizer *Graphics_Type_Holder;
    wxBoxSizer *Graphics_EditorFlag_Holder;
    wxBoxSizer *Graphics_1_Grid;
    wxBoxSizer *Graphics_2_Grid;
    wxBoxSizer *Graphics_3_Grid;
    wxBoxSizer *Graphics_Unknowns_Grid;

    SolidText *Graphics_Name_Text;
    SolidText *Graphics_FileName_Text;
    SolidText *Graphics_ParticleEffectName_Text;
    SolidText *Graphics_SLP_Text;
    SolidText *Graphics_Loaded_Text;
    SolidText *Graphics_ColorFlag_Text;
    SolidText *Graphics_DrawLevel_Text;
    SolidText *Graphics_PlayerColor_Text;
    SolidText *Graphics_TransparentPicking_Text;
    SolidText *Graphics_Coordinates_Text;
    SolidText *Graphics_SoundID_Text;
    SolidText *Graphics_AngleSoundsUsed_Text;
    SolidText *Graphics_FrameCount_Text;
    SolidText *Graphics_AngleCount_Text;
    SolidText *Graphics_FirstFrame_Text;
    SolidText *Graphics_SpeedMultiplier_Text;
    SolidText *Graphics_FrameDuration_Text;
    SolidText *Graphics_ReplayDelay_Text;
    SolidText *Graphics_SequenceType_Text;
    SolidText *Graphics_ID_Text;
    SolidText *Graphics_Type_Text;
    SolidText *Graphics_EditorFlag_Text;

    StringControl *Graphics_Name;
    StringControl *Graphics_FileName;
    StringControl *Graphics_ParticleEffectName;
    wxButton *Graphics_ParticleEffectName_Browse;
    NumberControl *Graphics_SLP;
    AGETextCtrl *Graphics_Loaded;
    AGETextCtrl *Graphics_ColorFlag;
    AGETextCtrl *Graphics_DrawLevel;
    AGETextCtrl *Graphics_PlayerColor;
    LinkedComboBox *Graphics_PlayerColor_ComboBox;
    AGETextCtrl *Graphics_TransparentPicking;
    AGETextCtrl *Graphics_Coordinates[4];
    AGETextCtrl *Graphics_SoundID;
    AGETextCtrl *Graphics_WwiseSoundID;
    LinkedComboBox *Graphics_SoundID_ComboBox;
    AGETextCtrl *Graphics_AngleSoundsUsed;
    LinkedCheckBox *Graphics_AngleSoundsUsed_CheckBox;
    AGETextCtrl *Graphics_FrameCount;
    AGETextCtrl *Graphics_AngleCount;
    AGETextCtrl *Graphics_FirstFrame;
    AGETextCtrl *Graphics_SpeedMultiplier;
    AGETextCtrl *Graphics_FrameDuration;
    AGETextCtrl *Graphics_ReplayDelay;
    AGETextCtrl *Graphics_SequenceType;
    AGETextCtrl *Graphics_ID;
    AGETextCtrl *Graphics_MirroringMode;
    AGETextCtrl *Graphics_EditorFlag;

    wxBoxSizer *Graphics_Deltas;
    wxTextCtrl *Graphics_Deltas_Search;
    wxTextCtrl *Graphics_Deltas_Search_R;
    ProperList *Graphics_Deltas_ListV;
    wxGridSizer *Graphics_Deltas_Buttons;
    wxButton *Deltas_Add;
    wxButton *Deltas_Insert;
    wxButton *Deltas_Delete;
    wxButton *Deltas_Copy;
    wxButton *Deltas_Paste;
    wxButton *Deltas_PasteInsert;
    wxButton *Deltas_CopyToGraphics;
    wxBoxSizer *Graphics_AngleSounds;
    ProperList *Graphics_AngleSounds_ListV;
    wxCheckBox *AngleSounds_AutoCopy;
    wxButton *AngleSounds_Copy;
    wxButton *AngleSounds_CopyToGraphics;

    wxStaticBoxSizer *Graphics_Deltas_Holder;
    wxBoxSizer *Graphics_Deltas_Holder_Data;
    wxBoxSizer *Deltas_Holder;
    wxBoxSizer *Deltas_Unknowns_Holder;
    wxStaticBoxSizer *Graphics_AngleSoundArea_Holder;

    wxBoxSizer *GraphicDeltas_GraphicID_Holder;
    SolidText *GraphicDeltas_GraphicID_Text;
    AGETextCtrl *GraphicDeltas_GraphicID;
    LinkedComboBox *GraphicDeltas_GraphicID_ComboBox;
    wxBoxSizer *GraphicDeltas_Padding1_Holder;
    SolidText *GraphicDeltas_Padding1_Text;
    AGETextCtrl *GraphicDeltas_Padding1;
    wxBoxSizer *GraphicDeltas_SpritePtr_Holder;
    SolidText *GraphicDeltas_SpritePtr_Text;
    AGETextCtrl *GraphicDeltas_SpritePtr;
    wxBoxSizer *GraphicDeltas_OffsetX_Holder;
    SolidText *GraphicDeltas_OffsetX_Text;
    AGETextCtrl *GraphicDeltas_OffsetX;
    wxBoxSizer *GraphicDeltas_OffsetY_Holder;
    SolidText *GraphicDeltas_OffsetY_Text;
    AGETextCtrl *GraphicDeltas_OffsetY;
    wxBoxSizer *GraphicDeltas_DisplayAngle_Holder;
    SolidText *GraphicDeltas_DisplayAngle_Text;
    AGETextCtrl *GraphicDeltas_DisplayAngle;
    wxBoxSizer *GraphicDeltas_Padding2_Holder;
    SolidText *GraphicDeltas_Padding2_Text;
    AGETextCtrl *GraphicDeltas_Padding2;
    wxBoxSizer *Graphics_AngleSounds_Holder;
    SolidText *Graphics_AngleSounds_Text;
    wxBoxSizer *Graphics_AngleFrameNums_Holder;
    SolidText *Graphics_AngleFrameNums_Text;
    AGETextCtrl *Graphics_AngleFrameNum[3];
    AGETextCtrl *Graphics_AngleSoundID[3];
    AGETextCtrl *Graphics_WwiseAngleSoundID[3];
    LinkedComboBox *Graphics_AngleSoundID_ComboBox[3];
    wxButton *Deltas_Import;

//  Terrains user interface

    std::vector<AGETextCtrl*> uiGroupTerrain, uiGroupBorder, uiGroupBorderFrame;
    wxBoxSizer *Terrains_Main;
    wxStaticBoxSizer *Terrains_Terrains;
    wxBoxSizer *Terrains_Terrains_Searches[2];
    wxTextCtrl *Terrains_Terrains_Search;
    wxTextCtrl *Terrains_Terrains_Search_R;
    AGEComboBox *Terrains_SearchFilters[2];
    wxCheckBox *Terrains_Terrains_UseAnd[2];
    ProperList *Terrains_Terrains_ListV;
    wxBoxSizer *Terrains_UsedCountHolder;
    SolidText *Terrains_UsedCountText;
    AGETextCtrl *Terrains_UsedCount;
    wxBoxSizer *Borders_UsedCountHolder;
    SolidText *Borders_UsedCountText;
    AGETextCtrl *Borders_UsedCount;
    wxGridSizer *Terrains_Terrains_Buttons;
    wxButton *Terrains_Add;
    wxButton *Terrains_Delete;
    wxButton *Terrains_Copy;
    wxButton *Terrains_Paste;

    wxBoxSizer *Terrains_GreatSpace;
    wxBoxSizer *Terrains_SpaceLeft;
    wxBoxSizer *Terrains_SpaceRight;
    AGETextCtrl *Terrains_Border;
    LinkedComboBox *Terrains_Border_ComboBox;
    wxStaticBoxSizer *Terrains_Borders;
    wxTextCtrl *Terrains_Borders_Search;
    wxTextCtrl *Terrains_Borders_Search_R;
    ProperList *Terrains_Borders_ListV;
    wxGridSizer *Terrains_Borders_Buttons;
    wxButton *Terrains_Borders_Copy;
    wxButton *Terrains_Borders_Paste;
    wxButton *Terrains_Borders_CopyToTerrains;

    AScrolled *Terrains_Scroller;
    wxBoxSizer *Terrains_ScrollSpace;
    wxBoxSizer *Terrains_NameArea_Holder;
    wxBoxSizer *Terrains_Area1_Grid;
    wxBoxSizer *Terrains_Area2_Grid;
    wxBoxSizer *Terrains_GridX1;
    wxGridSizer *Terrains_GridX2;
    wxBoxSizer *Terrains_Phantom_Holder;
    SolidText *Terrains_Phantom_Text;
    AGETextCtrl *Terrains_Phantom;
    wxBoxSizer *Terrains_Enabled_Holder;
    wxBoxSizer *Terrains_Enabled1_Holder;
    SolidText *Terrains_Enabled_Text;
    AGETextCtrl *Terrains_Enabled;
    LinkedCheckBox *Terrains_Enabled_CheckBox;
    wxBoxSizer *Terrains_Random_Holder;
    SolidText *Terrains_Random_Text;
    AGETextCtrl *Terrains_Random;
    wxBoxSizer *Terrains_Name_Holder;
    SolidText *Terrains_Name_Text;
    StringControl *Terrains_Name;
    wxBoxSizer *Terrains_FileName_Holder;
    SolidText *Terrains_FileName_Text;
    StringControl *Terrains_FileName;
    wxBoxSizer *Terrains_SLP_Holder;
    SolidText *Terrains_SLP_Text;
    AGETextCtrl *Terrains_SLP;
    wxBoxSizer *Terrains_ShapePtr_Holder;
    SolidText *Terrains_ShapePtr_Text;
    AGETextCtrl *Terrains_ShapePtr;
    wxBoxSizer *Terrains_SoundID_Holder;
    SolidText *Terrains_SoundID_Text;
    AGETextCtrl *Terrains_SoundID;
    AGETextCtrl *Terrains_WwiseSoundID;
    LinkedComboBox *Terrains_SoundID_ComboBox;
    wxBoxSizer *Terrains_SoundStopID_Holder;
    SolidText *Terrains_SoundStopID_Text;
    AGETextCtrl *Terrains_SoundStopID;
    wxBoxSizer *Terrains_BlendPriority_Holder;
    SolidText *Terrains_BlendPriority_Text;
    NumberControl *Terrains_BlendPriority;
    wxBoxSizer *Terrains_BlendType_Holder;
    SolidText *Terrains_BlendType_Text;
    NumberControl *Terrains_BlendType;
    wxBoxSizer *Terrains_OverlayMaskName_Holder;
    SolidText *Terrains_OverlayMaskName_Text;
    StringControl *Terrains_OverlayMaskName;
    wxButton *Terrains_OverlayMaskName_Browse;
    wxBoxSizer *Terrains_IsWater_Holder;
    SolidText *Terrains_IsWater_Text;
    AGETextCtrl *Terrains_IsWater;
    wxBoxSizer *Terrains_HideInEditor_Holder;
    SolidText *Terrains_HideInEditor_Text;
    AGETextCtrl *Terrains_HideInEditor;
    wxBoxSizer *Terrains_StringID_Holder;
    SolidText *Terrains_StringID_Text;
    AGETextCtrl *Terrains_StringID;
    wxBoxSizer *Terrains_Colors_Holder;
    wxGridSizer *Terrains_Colors_Grid;
    SolidText *Terrains_Colors_Text;
    std::array<AGETextCtrl*, 3> Terrains_Colors;
    wxBoxSizer *Terrains_CliffColors_Holder;
    wxGridSizer *Terrains_CliffColors_Grid;
    SolidText *Terrains_CliffColors_Text;
    std::array<AGETextCtrl*, 2> Terrains_CliffColors;
    wxBoxSizer *Terrains_PassableTerrain_Holder;
    wxBoxSizer *Terrains_ImpassableTerrain_Holder;
    SolidText *Terrains_PassableTerrain_Text;
    SolidText *Terrains_ImpassableTerrain_Text;
    AGETextCtrl *Terrains_PassableTerrain;
    AGETextCtrl *Terrains_ImpassableTerrain;
    LinkedComboBox *Terrains_PassableTerrain_ComboBox;
    LinkedComboBox *Terrains_ImpassableTerrain_ComboBox;

    wxBoxSizer *Terrains_Animation_Grid1;
    wxBoxSizer *Terrains_Animation_Grid2;
    wxBoxSizer *Terrains_IsAnimated_Holder;
    SolidText *Terrains_IsAnimated_Text;
    AGETextCtrl *Terrains_IsAnimated;
    wxBoxSizer *Terrains_AnimationFrames_Holder;
    SolidText *Terrains_AnimationFrames_Text;
    AGETextCtrl *Terrains_AnimationFrames;
    wxBoxSizer *Terrains_PauseFames_Holder;
    SolidText *Terrains_PauseFames_Text;
    AGETextCtrl *Terrains_PauseFames;
    wxBoxSizer *Terrains_Interval_Holder;
    SolidText *Terrains_Interval_Text;
    AGETextCtrl *Terrains_Interval;
    wxBoxSizer *Terrains_PauseBetweenLoops_Holder;
    SolidText *Terrains_PauseBetweenLoops_Text;
    AGETextCtrl *Terrains_PauseBetweenLoops;
    wxBoxSizer *Terrains_Frame_Holder;
    SolidText *Terrains_Frame_Text;
    AGETextCtrl *Terrains_Frame;
    wxBoxSizer *Terrains_DrawFrame_Holder;
    SolidText *Terrains_DrawFrame_Text;
    AGETextCtrl *Terrains_DrawFrame;
    wxBoxSizer *Terrains_AnimateLast_Holder;
    SolidText *Terrains_AnimateLast_Text;
    AGETextCtrl *Terrains_AnimateLast;
    wxBoxSizer *Terrains_FrameChanged_Holder;
    SolidText *Terrains_FrameChanged_Text;
    AGETextCtrl *Terrains_FrameChanged;
    wxBoxSizer *Terrains_Drawn_Holder;
    SolidText *Terrains_Drawn_Text;
    AGETextCtrl *Terrains_Drawn;

    wxBoxSizer *Terrains_ElevationGraphics_Holder;
    wxBoxSizer *Terrain_TileGraphics_Sizer;
    SolidText *Terrains_ElevationGraphics_Text;
    std::array<wxBoxSizer*, 19>Terrain_TileGraphics_Sizers;
    std::array<AGETextCtrl*, 57>Terrains_ElevationGraphics;
    wxBoxSizer *Terrains_TerrainReplacementID_Holder;
    SolidText *Terrains_TerrainReplacementID_Text;
    AGETextCtrl *Terrains_TerrainReplacementID;
    LinkedComboBox *Terrains_TerrainReplacementID_ComboBox;
    wxBoxSizer *Terrains_TerrainDimensions_Holder;
    SolidText *Terrains_TerrainDimensions_Text;
    std::array<AGETextCtrl*, 2>Terrains_TerrainDimensions;
    size_t static const TERRAINUNITS = 30;
    wxBoxSizer *Terrains_TerrainUnits_Holder;
    wxBoxSizer *Terrains_TerrainUnitID_Holder;
    wxBoxSizer *Terrains_TerrainUnitID_Holder1;
    SolidText *Terrains_TerrainUnitID_Text;
    std::array<AGETextCtrl*, TERRAINUNITS>Terrains_TerrainUnitID;
    std::array<LinkedComboBox*, TERRAINUNITS>Terrains_TerrainUnitID_ComboBox;
    wxBoxSizer *Terrains_TerrainUnitDensity_Holder;
    wxBoxSizer *Terrains_TerrainUnitMaskedDensity_Holder;
    wxBoxSizer *Terrains_TerrainUnitPriority_Holder;
    SolidText *Terrains_TerrainUnitDensity_Text;
    SolidText *Terrains_TerrainUnitPriority_Text;
    std::array<AGETextCtrl*, TERRAINUNITS>Terrains_TerrainUnitDensity;
    std::array<AGETextCtrl*, TERRAINUNITS>Terrains_TerrainUnitMaskedDensity;
    std::array<AGETextCtrl*, TERRAINUNITS>Terrains_TerrainUnitPriority;
    wxBoxSizer *Terrains_UsedTerrainUnits_Holder;
    SolidText *Terrains_UsedTerrainUnits_Text;
    AGETextCtrl *Terrains_UsedTerrainUnits;

//  Terrain restrictions user interface

    wxBoxSizer *TerRestrict_Main;
    wxGridSizer *TerRestrict_TerRestrict_Buttons;
    wxStaticBoxSizer *TerRestrict_TerRestrict;
    wxTextCtrl *TerRestrict_TerRestrict_Search;
    wxTextCtrl *TerRestrict_TerRestrict_Search_R;
    ProperList *TerRestrict_TerRestrict_ListV;
    wxButton *TerRestrict_Add;
    wxButton *TerRestrict_Insert;
    wxButton *TerRestrict_Delete;
    wxButton *TerRestrict_Copy;
    wxButton *TerRestrict_Paste;
    wxButton *TerRestrict_PasteInsert;

    std::vector<AGETextCtrl*> uiGroupRestriction;
    wxBoxSizer *TerRestrict_Terrains;
    wxBoxSizer *TerRestrict_DataArea;
    wxTextCtrl *TerRestrict_Terrains_Search;
    wxTextCtrl *TerRestrict_Terrains_Search_R;
//  wxCheckBox *TerRestrict_Terrains_UseAnd;
    ProperList *TerRestrict_Terrains_ListV;
    wxGridSizer *TerRestrict_Terrains_Buttons;
    wxButton *TerRestrict_Terrains_Copy;
    wxButton *TerRestrict_Terrains_Paste;
    wxButton *TerRestrict_Terrains_PasteInsert;
    SolidText *TerRestrict_Accessible_Text;
    AGETextCtrl *TerRestrict_Accessible;
    wxBoxSizer *TerRestrict_Graphics_Holder;
    SolidText *TerRestrict_Graphics_Text[3];
    AGETextCtrl *TerRestrict_Graphics[3];
    LinkedComboBox *TerRestrict_Graphics_ComboBox[3];
    SolidText *TerRestrict_Amount_Text;
    NumberControl *TerRestrict_Amount;

//  Sound user interface

    wxBoxSizer *Sounds_Main;
    wxGridSizer *Sounds_Sounds_Buttons;
    wxGridSizer *Sounds_Items_Buttons;
    wxBoxSizer *Sounds_DataArea;

    wxStaticBoxSizer *Sounds_Sounds;
    wxTextCtrl *Sounds_Sounds_Search;
    wxTextCtrl *Sounds_Sounds_Search_R;
    ProperList *Sounds_Sounds_ListV;
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
    AGEComboBox *Sounds_Items_SearchFilters[2];
    wxCheckBox *Sounds_Items_UseAnd[2];
    ProperList *Sounds_Items_ListV;
    wxButton *SoundItems_Add;
    wxButton *SoundItems_Insert;
    wxButton *SoundItems_Delete;
    wxButton *SoundItems_Copy;
    wxButton *SoundItems_Paste;
    wxButton *SoundItems_PasteInsert;
    wxButton *SoundItems_CopyToSounds;

    std::vector<AGETextCtrl*> uiGroupSound, uiGroupSoundFile;
    wxBoxSizer *Sounds_ID_Holder;
    SolidText *Sounds_ID_Text;
    AGETextCtrl *Sounds_ID;
    wxBoxSizer *Sounds_PlayDelay_Holder;
    SolidText *Sounds_PlayDelay_Text;
    AGETextCtrl *Sounds_PlayDelay;
    wxBoxSizer *Sounds_CacheTime_Holder;
    SolidText *Sounds_CacheTime_Text;
    AGETextCtrl *Sounds_CacheTime;
    wxBoxSizer *Sounds_TotalProbability_Holder;
    SolidText *Sounds_TotalProbability_Text;
    SolidText *Sounds_TotalProbability_Info;
    AGETextCtrl *Sounds_TotalProbability;
    wxBoxSizer *SoundItems_Name_Holder;
    SolidText *SoundItems_Name_Text;
    StringControl *SoundItems_Name;
    wxBoxSizer *SoundItems_Resource_Holder;
    SolidText *SoundItems_Resource_Text;
    NumberControl *SoundItems_Resource;
    wxBoxSizer *SoundItems_Probability_Holder;
    SolidText *SoundItems_Probability_Text;
    AGETextCtrl *SoundItems_Probability;
    wxBoxSizer *SoundItems_Civ_Holder;
    SolidText *SoundItems_Civ_Text;
    AGETextCtrl *SoundItems_Civ;
    LinkedComboBox *SoundItems_Civ_ComboBox;
    wxBoxSizer *SoundItems_IconSet_Holder;
    SolidText *SoundItems_IconSet_Text;
    AGETextCtrl *SoundItems_IconSet;
    wxButton *SoundFile_Play;
    wxCheckBox *SoundFile_Loop;
    wxButton *SoundFile_Stop;
    wxButton *SoundFile_AutoProbability;
    wxButton *SoundFile_AutoIncrement;
    wxButton *SoundFile_CopyCivToCiv;
    wxSizer *SourceCiv_Holder;
    wxSizer *TargetCiv_Holder;
    AGEComboBox *SoundFile_Source_Civ;
    AGEComboBox *SoundFile_Target_Civ;

    wxStaticBoxSizer *Sounds_AllItems;
    wxBoxSizer *Sounds_AllItems_Searches[2];
    wxTextCtrl *Sounds_AllItems_Search;
    wxTextCtrl *Sounds_AllItems_Search_R;
    wxCheckBox *Sounds_AllItems_UseAnd[2];
    ProperList *Sounds_AllItems_ListV;
    wxBoxSizer *Sounds_AllItems_Buttons;
    wxButton *Sounds_AllItems_Load;
    wxButton *Sounds_AllItems_Clear;

//  Player Color user interface

    wxBoxSizer *Colors_Main;
    wxGridSizer *Colors_Colors_Buttons;
    wxStaticBoxSizer *Colors_Colors;
    wxTextCtrl *Colors_Colors_Search;
    wxTextCtrl *Colors_Colors_Search_R;
    ProperList *Colors_Colors_ListV;
    wxButton *Colors_Add;
    wxButton *Colors_Insert;
    wxButton *Colors_Delete;
    wxButton *Colors_Copy;
    wxButton *Colors_Paste;
    wxButton *Colors_PasteInsert;

    std::vector<AGETextCtrl*> uiGroupColor;
    wxBoxSizer *Colors_DataArea;
    wxWrapSizer *Colors_WrapArea;
    wxBoxSizer *Colors_Name_Holder;
    wxBoxSizer *Colors_ID_Holder;
    wxBoxSizer *Colors_ResourceID_Holder;
    wxBoxSizer *Colors_PlayerPalette_Holder;
    wxBoxSizer *Colors_OutlineColor_Holder;
    wxBoxSizer *Colors_MinimapColor_Holder;
    wxBoxSizer *Colors_SelectionColor1_Holder;
    wxBoxSizer *Colors_SelectionColor2_Holder;
    wxBoxSizer *Colors_MinimapColor2_Holder;
    wxBoxSizer *Colors_MinimapColor3_Holder;
    wxBoxSizer *Colors_Type_Holder;
    wxBoxSizer *Colors_ReferenceID_Holder;
    SolidText *Colors_Name_Text;
    SolidText *Colors_ID_Text;
    SolidText *Colors_ResourceID_Text;
    SolidText *Colors_PlayerPalette_Text;
    SolidText *Colors_OutlineColor_Text;
    SolidText *Colors_MinimapColor_Text;
    SolidText *Colors_SelectionColor1_Text;
    SolidText *Colors_SelectionColor2_Text;
    SolidText *Colors_MinimapColor2_Text;
    SolidText *Colors_MinimapColor3_Text;
    SolidText *Colors_Type_Text;
    SolidText *Colors_ReferenceID_Text;
    StringControl *Colors_Name;
    NumberControl *Colors_ID;
    AGETextCtrl *Colors_ResourceID;
    AGETextCtrl *Colors_PlayerPalette;
    AGETextCtrl *Colors_OutlineColor;
    NumberControl *Colors_MinimapColor;
    AGETextCtrl *Colors_SelectionColor1;
    AGETextCtrl *Colors_SelectionColor2;
    AGETextCtrl *Colors_MinimapColor2;
    AGETextCtrl *Colors_MinimapColor3;
    AGETextCtrl *Colors_Type;
    AGETextCtrl *Colors_ReferenceID;
    LinkedComboBox *Colors_ReferenceID_ComboBox;
    APanel *Colors_Palette_Display;

//  Unitline user interface

    wxBoxSizer *UnitLines_Main;
    wxGridSizer *UnitLines_UnitLines_Buttons;
    wxGridSizer *UnitLines_UnitLineUnits_Buttons;
    wxBoxSizer *UnitLines_DataArea;

    wxStaticBoxSizer *UnitLines_UnitLines;
    wxTextCtrl *UnitLines_UnitLines_Search;
    wxTextCtrl *UnitLines_UnitLines_Search_R;
    ProperList *UnitLines_UnitLines_ListV;
    wxButton *UnitLines_Add;
    wxButton *UnitLines_Insert;
    wxButton *UnitLines_Delete;
    wxButton *UnitLines_Copy;
    wxButton *UnitLines_Paste;
    wxButton *UnitLines_PasteInsert;

    wxBoxSizer *UnitLines_ID_Holder;
    SolidText *UnitLines_ID_Text;
    AGETextCtrl *UnitLines_ID;
    wxBoxSizer *UnitLines_Name_Holder;
    SolidText *UnitLines_Name_Text;
    StringControl *UnitLines_Name;

    wxStaticBoxSizer *UnitLines_UnitLineUnits;
    wxTextCtrl *UnitLines_UnitLineUnits_Search;
    wxTextCtrl *UnitLines_UnitLineUnits_Search_R;
    ProperList *UnitLines_UnitLineUnits_ListV;
    wxButton *UnitLineUnits_Add;
    wxButton *UnitLineUnits_Insert;
    wxButton *UnitLineUnits_Delete;
    wxButton *UnitLineUnits_Copy;
    wxButton *UnitLineUnits_Paste;
    wxButton *UnitLineUnits_PasteInsert;
    wxButton *UnitLineUnits_CopyToUnitLines;

    wxBoxSizer *UnitLineUnits_Holder;
    SolidText *UnitLineUnits_Text;
    AGETextCtrl *UnitLineUnits_Units;
    LinkedComboBox *UnitLineUnits_ComboBox;

//  Tech Tree user interface

    wxBoxSizer *TechTrees_Main;
    wxBoxSizer *TechTrees_TabAges;
    wxBoxSizer *TechTrees_TabBuildings;
    wxBoxSizer *TechTrees_TabUnits;
    wxBoxSizer *TechTrees_TabResearches;
    AScrolled *TechTrees_ScrollerAges;
    AScrolled *TechTrees_ScrollerBuildings;
    AScrolled *TechTrees_ScrollerUnits;
    AScrolled *TechTrees_ScrollerResearches;
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
    AGEComboBox *TechTrees_MainList_Buildings_SearchFilters[2];
    AGEComboBox *TechTrees_MainList_Units_SearchFilters[2];
    AGEComboBox *TechTrees_MainList_Researches_SearchFilters[2];
    wxCheckBox *TechTrees_MainList_Buildings_UseAnd[2];
    wxCheckBox *TechTrees_MainList_Units_UseAnd[2];
    wxCheckBox *TechTrees_MainList_Researches_UseAnd[2];
    ProperList *TechTrees_MainList_Ages_ListV;
    ProperList *TechTrees_MainList_Buildings_ListV;
    ProperList *TechTrees_MainList_Units_ListV;
    ProperList *TechTrees_MainList_Researches_ListV;
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
    AGE_AreaTT31020 TechTrees_Ages_ZoneData;
    AGE_AreaTT84 TechTrees_Buildings_Items;
    AGE_AreaTT84 TechTrees_Units_Items;
    AGE_AreaTT84 TechTrees_Researches_Items;

    wxBoxSizer *TechTrees_Data_Ages;
    wxBoxSizer *TechTrees_Data_Ages2;
    wxBoxSizer *TechTrees_Data_Ages1;
    wxBoxSizer *TechTrees_Data_Buildings;
    wxBoxSizer *TechTrees_Data_Buildings2;
    wxBoxSizer *TechTrees_Data_Buildings3;
    wxBoxSizer *TechTrees_Data_Buildings1;
    wxBoxSizer *TechTrees_Data_Units;
    wxBoxSizer *TechTrees_Data_Units1;
    wxBoxSizer *TechTrees_Data_Units2;
    wxBoxSizer *TechTrees_Data_Researches;
    wxBoxSizer *TechTrees_Data_Researches2;
    wxBoxSizer *TechTrees_Data_Researches1;
    wxBoxSizer *TechTrees_Data_Researches3;
    wxBoxSizer *TechTrees_Data_Researches4;
    wxBoxSizer *TechTrees_ConnectedHolder_Ages;
    wxBoxSizer *TechTrees_ConnectedHolder_Buildings;
    wxBoxSizer *TechTrees_ConnectedHolder_Units;
    wxBoxSizer *TechTrees_ConnectedHolder_Researches;

    wxBoxSizer *TechTrees_Ages_ID_Holder;
    SolidText *TechTrees_Ages_ID_Text;
    AGETextCtrl *TechTrees_Ages_ID;
    wxBoxSizer *TechTrees_Ages_Status_Holder;
    SolidText *TechTrees_Ages_Status_Text;
    AGETextCtrl *TechTrees_Ages_Status;
    wxBoxSizer *TechTrees_Ages_LineMode_Holder;
    SolidText *TechTrees_Ages_LineMode_Text;
    AGETextCtrl *TechTrees_Ages_LineMode;

    wxBoxSizer *TechTrees_Buildings_ID_Holder;
    SolidText *TechTrees_Buildings_ID_Text;
    AGETextCtrl *TechTrees_Buildings_ID;
    LinkedComboBox *TechTrees_Buildings_ID_ComboBox;
    wxBoxSizer *TechTrees_Buildings_Status_Holder;
    SolidText *TechTrees_Buildings_Status_Text;
    AGETextCtrl *TechTrees_Buildings_Status;

    wxBoxSizer *TechTrees_Buildings_LocationInAge_Holder;
    SolidText *TechTrees_Buildings_LocationInAge_Text;
    AGETextCtrl *TechTrees_Buildings_LocationInAge;
    wxBoxSizer *TechTrees_Buildings_LineMode_Holder;
    SolidText *TechTrees_Buildings_LineMode_Text;
    AGETextCtrl *TechTrees_Buildings_LineMode;
    wxBoxSizer *TechTrees_Buildings_EnablingResearch_Holder;
    SolidText *TechTrees_Buildings_EnablingResearch_Text;
    AGETextCtrl *TechTrees_Buildings_EnablingResearch;
    LinkedComboBox *TechTrees_Buildings_EnablingResearch_ComboBox;
    wxStaticBoxSizer *TechTrees_Buildings_TotalUnitsTechs_Holder[2];
    AGETextCtrl *TechTrees_Buildings_TotalUnitsTechs[10];

    wxBoxSizer *TechTrees_Units_ID_Holder;
    SolidText *TechTrees_Units_ID_Text;
    AGETextCtrl *TechTrees_Units_ID;
    LinkedComboBox *TechTrees_Units_ID_ComboBox;
    wxBoxSizer *TechTrees_Units_Status_Holder;
    SolidText *TechTrees_Units_Status_Text;
    AGETextCtrl *TechTrees_Units_Status;
    wxBoxSizer *TechTrees_Units_UpperBuilding_Holder;
    SolidText *TechTrees_Units_UpperBuilding_Text;
    AGETextCtrl *TechTrees_Units_UpperBuilding;
    LinkedComboBox *TechTrees_Units_UpperBuilding_ComboBox;

    wxBoxSizer *TechTrees_Units_VerticalLine_Holder;
    SolidText *TechTrees_Units_VerticalLine_Text;
    AGETextCtrl *TechTrees_Units_VerticalLine;

    wxBoxSizer *TechTrees_Units_LocationInAge_Holder;
    SolidText *TechTrees_Units_LocationInAge_Text;
    AGETextCtrl *TechTrees_Units_LocationInAge;
    wxBoxSizer *TechTrees_Units_RequiredResearch_Holder;
    SolidText *TechTrees_Units_RequiredResearch_Text;
    AGETextCtrl *TechTrees_Units_RequiredResearch;
    LinkedComboBox *TechTrees_Units_RequiredResearch_ComboBox;
    wxBoxSizer *TechTrees_Units_LineMode_Holder;
    SolidText *TechTrees_Units_LineMode_Text;
    AGETextCtrl *TechTrees_Units_LineMode;
    wxBoxSizer *TechTrees_Units_EnablingResearch_Holder;
    SolidText *TechTrees_Units_EnablingResearch_Text;
    AGETextCtrl *TechTrees_Units_EnablingResearch;
    LinkedComboBox *TechTrees_Units_EnablingResearch_ComboBox;

    wxBoxSizer *TechTrees_Researches_ID_Holder;
    SolidText *TechTrees_Researches_ID_Text;
    AGETextCtrl *TechTrees_Researches_ID;
    LinkedComboBox *TechTrees_Researches_ID_ComboBox;
    wxBoxSizer *TechTrees_Researches_Status_Holder;
    SolidText *TechTrees_Researches_Status_Text;
    AGETextCtrl *TechTrees_Researches_Status;
    wxBoxSizer *TechTrees_Researches_UpperBuilding_Holder;
    SolidText *TechTrees_Researches_UpperBuilding_Text;
    AGETextCtrl *TechTrees_Researches_UpperBuilding;
    LinkedComboBox *TechTrees_Researches_UpperBuilding_ComboBox;

    wxBoxSizer *TechTrees_Researches_VerticalLine_Holder;
    SolidText *TechTrees_Researches_VerticalLine_Text;
    AGETextCtrl *TechTrees_Researches_VerticalLine;
    wxBoxSizer *TechTrees_Researches_LocationInAge_Holder;
    SolidText *TechTrees_Researches_LocationInAge_Text;
    AGETextCtrl *TechTrees_Researches_LocationInAge;
    wxBoxSizer *TechTrees_Researches_LineMode_Holder;
    SolidText *TechTrees_Researches_LineMode_Text;
    AGETextCtrl *TechTrees_Researches_LineMode;

//  Template functions

    template <class P>
    inline void AddToListNoGV(P &path)
    {
        path.emplace_back();
        How2List = ListMode::ADD;
    }
    template <class P>
    inline void AddToList(P &path)
    {
        path.emplace_back();
        path.back().setGameVersion(GenieVersion);
        How2List = ListMode::ADD;
    }
    template <class P>
    inline void AddToListIDFix(P &path)
    {
        path.emplace_back();
        path.back().setGameVersion(GenieVersion);
        path.back().ID = path.size() - 1; // ID Fix
        How2List = ListMode::ADD;
    }

    template <class P>
    inline void InsertToListNoGV(P &path, int place)
    {
        path.emplace(path.begin() + place);
        How2List = ListMode::INSNEW;
    }
    template <class P>
    inline void InsertToList(P &path, int place)
    {
        path.emplace(path.begin() + place);
        path[place].setGameVersion(GenieVersion);
        How2List = ListMode::INSNEW;
    }
    template <class P>
    inline void InsertToListIDFix(P &path, int place)
    {
        path.emplace(path.begin() + place);
        path[place].setGameVersion(GenieVersion);
        for(size_t loop = path.size(); loop--> place;) // ID Fix
        path[loop].ID = loop;
        How2List = ListMode::INSNEW;
    }

    template <class P, class T = int>
    inline void DeleteFromList(P &path, std::vector<T> &places)
    {
        for (size_t loop = places.size(); loop-- > 0;)
        {
            path.erase(path.begin() + places[loop]);
        }
        How2List = ListMode::DEL;
    }
    template <class P, class T = int>
    inline void DeleteFromListIDFix(P &path, std::vector<T> &places)
    {
        for (size_t loop = places.size(); loop-- > 0;)
        {
            path.erase(path.begin() + places[loop]);
        }
        for (size_t loop = path.size(); loop-- > places.front();) // ID Fix
        {
            path[loop].ID = loop;
        }
        How2List = ListMode::DEL;
    }

    template <class P, class C>
    inline void CopyFromList(P &path, std::vector<int> &places, C &copies)
    {
        copies.resize(places.size());
        for(size_t loop = 0; loop < places.size(); ++loop)
        copies[loop] = path[places[loop]];
    }

    // Common paste check
    template <class P, class C>
    inline size_t PasteCheck(P &path, const std::vector<int> &places, const C &copies, bool resize)
    {
        if(Paste11)
        {
            if(places.size() != copies.size())
            {
                wxMessageBox(wxString::Format("%u copies, %u selections.\nClick paste tool to switch to sequential paste.", copies.size(), places.size()), "Selections Mismatch");
                return 0u;
            }
        }
        else
        {
            size_t new_size = places.front() + copies.size();
            if(new_size > path.size())
            {
                if(resize)
                {
                    path.resize(new_size);
                }
                else
                {
                    return copies.size() - (new_size - path.size());
                }
            }
        }
        return copies.size();
    }

    // Combined paste
    template <class P, class C>
    inline void PasteToListNoGV(P &path, std::vector<int> &places, C &copies, bool resize = true)
    {
        size_t copy_cnt = PasteCheck(path, places, copies, resize);
        for(size_t loop = 0; loop < copy_cnt; ++loop)
        {
            path[Paste11 ? places[loop] : places.front() + loop] = copies[loop];
        }
        How2List = ListMode::PASTE;
    }

    // Combined paste with GV
    template <class P, class C>
    inline void PasteToList(P &path, std::vector<int> &places, C &copies, bool resize = true)
    {
        size_t copy_cnt = PasteCheck(path, places, copies, resize);
        for(size_t loop = 0; loop < copy_cnt; ++loop)
        {
            copies[loop].setGameVersion(GenieVersion);
            path[Paste11 ? places[loop] : places.front() + loop] = copies[loop];
        }
        How2List = ListMode::PASTE;
    }

    // Combined paste with ID fix
    template <class P, class C>
    inline void PasteToListIDFix(P &path, std::vector<int> &places, C &copies, bool resize = true)
    {
        size_t copy_cnt = PasteCheck(path, places, copies, resize);
        for(size_t loop = 0; loop < copy_cnt; ++loop)
        {
            size_t loc = Paste11 ? places[loop] : places.front() + loop;
            copies[loop].setGameVersion(GenieVersion);
            path[loc] = copies[loop];
            path[loc].ID = loc;
        }
        How2List = ListMode::PASTE;
    }

    template <class P, class C>
    inline void PasteInsertToListNoGV(P &path, int place, C &copies)
    {
        path.insert(path.begin() + place, copies.begin(), copies.end());
        How2List = ListMode::INSPASTE;
    }
    template <class P, class C>
    inline void PasteInsertToList(P &path, int place, C &copies)
    {
        for(size_t loop = copies.size(); loop--> 0;)
        copies[loop].setGameVersion(GenieVersion);
        path.insert(path.begin() + place, copies.begin(), copies.end());
        How2List = ListMode::INSPASTE;
    }
    template <class P, class C>
    inline void PasteInsertToListIDFix(P &path, int place, C &copies)
    {
        for(size_t loop = copies.size(); loop--> 0;)
        copies[loop].setGameVersion(GenieVersion);
        path.insert(path.begin() + place, copies.begin(), copies.end());
        for(size_t loop = path.size(); loop--> place;) // ID Fix
        path[loop].ID = loop;
        How2List = ListMode::INSPASTE;
    }

    template <class P>
    inline void MoveUpInList(P &path, int place, int number)
    {
        auto beg = path.begin() + place;
        rotate(beg, beg + 1, beg + number);
    }

    template <class P>
    inline void MoveDownInList(P &path, int place, int number)
    {
        auto beg = path.begin() + place;
        rotate(beg, beg - 1 + number, beg + number);
    }

protected:
    Loader *TerrainLoader;
    wxCriticalSection TerrainLoaderCS;
    friend class Loader;
    short window_num;
    wxString argPath;
    wxFont font;
    sf::SoundBuffer waves;
    sf::Sound speaker;
};
