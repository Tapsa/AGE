#pragma once
#include "AGE_FramePieces.h"
#include "AGE_OpenDialog.h"
#include "AGE_SaveDialog.h"
#include "AGE_AboutDialog.h"
#include "AGE_Copies.hpp"

class AGE_SLP
{
public:
    int32_t slpID = -1, frameID, datID = -1, lastSlpID = -1, startframe;
    uint16_t angles, fpa, frames, mirror;
    string filename = "";
    genie::SlpFilePtr slp;
    wxBitmap bitmap;
    int16_t xpos = 0, ypos = 0, xdelta = 0, ydelta = 0;
    bool flip = false;
    float beginbearing = 0, endbearing = 6.28319f;

    set<uint16_t> angleset;
    multimap<int, AGE_SLP> deltas;
    enum SHOW {NONE, UNIT, GRAPHIC};
    static SHOW currentDisplay;
    static unsigned setbearing;
    static float bearing;
    static uint8_t playerColorStart, playerColorID;
    bool initStats(unsigned int graphicID, genie::DatFile &dataset);
};

class AGE_Frame;

class Loader: public wxThread
{
public:
    Loader(AGE_Frame *frame, genie::Terrain *tp):
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

class AGE_Frame: public wxFrame
{
public:
    AGE_Frame(const wxString &title, short window, wxString aP = wxEmptyString);
    static void FixSize(AGE_Frame*);

    struct Pixels
    {
        float x1, y1, x2, y2, x3, y3, x4, y4;
    };

//  Stuff related to editing multiple files at once

    static std::ofstream log_out;
    static wxWindow* openEditors[];
    static Copies copies;
    wxString argPath;
    wxFont font;

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

//  void CreateDRSControls();

//  Other Events

    bool DataOpened = false;
    bool SaveLang();
    bool SaveLangX1();
    bool SaveLangX1P1();
    void LoadLists();
    void OnGameVersionChange();
    void OnSave(wxCommandEvent &event);
    void OnOpen(wxCommandEvent &event);
    void OnExit(wxCloseEvent &event);
    void OnMenuOption(wxCommandEvent &event);
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
    void OnKillFocus_TechTrees(wxFocusEvent &event);
    void OnKillFocus_Civs(wxFocusEvent &event);
    void OnKillFocus_Units(wxFocusEvent &event);
    void OnKillFocus_UnitLines(wxFocusEvent &event);
    void OnKillFocus_Graphics(wxFocusEvent &event);
    void OnKillFocus_Terrains(wxFocusEvent &event);
    void OnKillFocus_Borders(wxFocusEvent &event);
    void OnKillFocus_TerRestrict(wxFocusEvent &event);
    void OnKillFocus_Sounds(wxFocusEvent &event);
    void OnKillFocus_Colors(wxFocusEvent &event);
    void OnKillFocus_Unknown(wxFocusEvent &event);

    void OnUpdateCheck_Techs(wxCommandEvent &event);
    void OnUpdateCheck_Graphics(wxCommandEvent &event);
    void OnUpdateCheck_UnitAttribute(wxCommandEvent &event);
    void OnUpdateCheck_UnitGarrisonType(wxCommandEvent &event);

    void OnUpdateCombo_Techs(wxCommandEvent &event);
    void OnUpdateCombo_TechTrees(wxCommandEvent &event);
    void OnUpdateCombo_TechTreeMode(wxCommandEvent &event);
    void OnUpdateCombo_Units(wxCommandEvent &event);
    void OnUpdateCombo_UnitLines(wxCommandEvent &event);
    void OnUpdateCombo_Graphics(wxCommandEvent &event);
    void OnUpdateCombo_Terrains(wxCommandEvent &event);

//  Timers to consume overlapping virtual list events.

    wxTimer researchTimer, techTimer, effectTimer, allEffectsTimer;
    wxTimer ttAgeTimer, ttAgeBuildingTimer, ttAgeUnitTimer, ttAgeResearchTimer, ttAgeItemTimer, ttAgeUnknownTimer;
    wxTimer ttBuildingTimer, ttBuildingBuildingTimer, ttBuildingUnitTimer, ttBuildingResearchTimer, ttBuildingItemTimer;
    wxTimer ttUnitTimer, ttUnitUnitTimer, ttUnitItemTimer;
    wxTimer ttResearchTimer, ttResearchBuildingTimer, ttResearchUnitTimer, ttResearchResearchTimer, ttResearchItemTimer;
    wxTimer civTimer, resourceTimer;
    wxTimer unitTimer, dmgGraphicTimer, attackTimer, armorTimer, actionTimer;
    wxTimer unitLineTimer, unitLineUnitTimer;
    wxTimer graphicTimer, deltaTimer, graphicSoundTimer, graphicAnimTimer;
    wxTimer terrainTimer, terrainBorderTimer;
    wxTimer borderTimer, borderTileTypeTimer, borderBorderShapeTimer;
    wxTimer restrictionTimer, restrictionTerrainTimer;
    wxTimer soundTimer, soundFileTimer, allSoundFilesTimer;
    wxTimer colorTimer, randomMapTimer, rmBaseTimer, rmTerrainTimer, rmUnitTimer, rmUnknownTimer;

//  Other Methods

    void InitSearch(const wxString &yes, const wxString &no);
    wxArrayString SearchYes, SearchNo;
    wxString FormatFloat(float);
    wxString FormatInt(int);
    wxString CurrentTime();
    wxArrayString Type20, Type30, Type40, Type50, Type60, Type70, Type80;
    wxArrayString AoE1TerrainRestrictions, AoE2TerrainRestrictions, SWGBTerrainRestrictions;
    wxArrayString RoRCivResources, AoKCivResources, SWGBCivResources;
    AGE_SaveDialog *SaveDialog;
    //int FindItem(wxArrayInt &selections, int find, int min, int max);
    //void SwapSelection(int last, wxArrayInt &selections);
    void SaveBackup();
    bool SearchMatches(const wxString &hay);
    void getSelectedItems(const int selections, const AGEListView* list, vector<int> &indexes);
    //void Listing(wxListBox *List, wxArrayString &names, list<void*> &data);
    void RefreshList(AGEListView *list, vector<int> *oldies = 0);
    void UnitLangDLLConverter(wxCommandEvent &event);
    void ResearchLangDLLConverter(wxCommandEvent &event);
    void SearchAllSubVectors(AGEListView *list, wxTextCtrl *topSearch, wxTextCtrl *subSearch);
    void LoadAllTechEffects(wxCommandEvent &event);
    void ClearAllTechEffects(wxCommandEvent &event);
    void OnAllTechEffectTimer(wxTimerEvent&);
    void OnAllTechEffectSelect(wxCommandEvent &event);
    void LoadAllSoundFiles(wxCommandEvent &event);
    void ClearAllSoundFiles(wxCommandEvent &event);
    void OnAllSoundFileTimer(wxTimerEvent&);
    void OnAllSoundFileSelect(wxCommandEvent &event);
    bool Paste11Check(size_t pastes, size_t copies);
    void OnDrawIconSLP(wxPaintEvent &event);
    void OnDrawGraphicSLP(wxPaintEvent &event);
    void CalcDrawCenter(APanel*, int&, int&);
    void CalcAngle(AGE_SLP&);
    void SetDisplayBearings(AGE_SLP&, const genie::GraphicDelta&);
    void OnDrawTechSLP(wxPaintEvent &event);
    void OnDrawBorderSLP(wxPaintEvent &event);
    void OnDrawPalette(wxPaintEvent &event);
    void OnGraphicAnim(wxTimerEvent &event);
    int ShouldAnimate(AGE_SLP&, bool&);
    void ChooseNextFrame(AGE_SLP&, bool&);
    void ChoosePreviousFrame(AGE_SLP&, bool&);
    void HandleLastFrame(const AGE_SLP&, bool, unsigned);
    int loadChosenGraphic(unsigned int unitID);
    void AddAnnexAndStackGraphics(unsigned int unitID, int offsetX = 0, int offsetY = 0, int apply = 0);
    void CalcAnnexCoords(const genie::unit::BuildingAnnex *annex);
    void DrawGraphics(wxBufferedPaintDC &dc, AGE_SLP &graphic, int centerX, int centerY);
    void loadPalette(const wxString &folder);
    void addFilesToRead(const wxArrayString &files, const wxString &folder);
    void addDRSFolders4SLPs(wxArrayString &folders, const wxString &folder);
    void addSLPFolders4SLPs(wxArrayString &folders, wxString folder);
    void setForeAndBackColors(AGETextCtrl* box, wxColour color);
    void OnChooseGraphic(wxCommandEvent&);
    void playWAV(wxCommandEvent &event);
    AGE_SLP* getCurrentGraphics();
    int produceRecentValues(wxArrayString&, vector<wxArrayString>&);
    void autoOdds(wxCommandEvent &event);
    void autoDrsIncrement(wxCommandEvent &event);
    void copySoundsFromCivToCiv(wxCommandEvent &event);
    void tileToPixels(float sizeX, float sizeY, Pixels &p, int centerX, int centerY);
    void OnSyncSaveWithOpen(wxCommandEvent &event);

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
    void InitRandomMaps();

    void ListMapData();
    void OnMapsRefresh(wxCommandEvent &event);
    void OnVariableCalc(wxFocusEvent &event);
    void OnVariableCalcReverse(wxFocusEvent &event);

    void ListRandomMaps();
    void OnRandomMapSearch(wxCommandEvent &event);
    void OnRandomMapTimer(wxTimerEvent&);
    void OnRandomMapSelect(wxCommandEvent &event);
    void OnRandomMapAdd(wxCommandEvent &event);
    void OnRandomMapInsert(wxCommandEvent &event);
    void OnRandomMapDelete(wxCommandEvent &event);
    void OnRandomMapCopy(wxCommandEvent &event);
    void OnRandomMapPaste(wxCommandEvent &event);
    void OnRandomMapPasteInsert(wxCommandEvent &event);
    string GetRandomMapName(int);

    void ListRMSBaseZones();
    void OnRMSBaseZoneSearch(wxCommandEvent &event);
    void OnRMSBaseZoneTimer(wxTimerEvent&);
    void OnRMSBaseZoneSelect(wxCommandEvent &event);
    void OnRMSBaseZoneAdd(wxCommandEvent &event);
    void OnRMSBaseZoneInsert(wxCommandEvent &event);
    void OnRMSBaseZoneDelete(wxCommandEvent &event);
    void OnRMSBaseZoneCopy(wxCommandEvent &event);
    void OnRMSBaseZonePaste(wxCommandEvent &event);
    void OnRMSBaseZonePasteInsert(wxCommandEvent &event);
    void OnRMSBaseZoneCopyToMaps(wxCommandEvent &event);
    string GetRMSBaseZonesName(int);

    void ListRMSTerrains();
    void OnRMSTerrainSearch(wxCommandEvent &event);
    void OnRMSTerrainTimer(wxTimerEvent&);
    void OnRMSTerrainSelect(wxCommandEvent &event);
    void OnRMSTerrainAdd(wxCommandEvent &event);
    void OnRMSTerrainInsert(wxCommandEvent &event);
    void OnRMSTerrainDelete(wxCommandEvent &event);
    void OnRMSTerrainCopy(wxCommandEvent &event);
    void OnRMSTerrainPaste(wxCommandEvent &event);
    void OnRMSTerrainPasteInsert(wxCommandEvent &event);
    void OnRMSTerrainCopyToMaps(wxCommandEvent &event);
    string GetRMSTerrainName(int);

    void ListRMSUnits();
    void OnRMSUnitSearch(wxCommandEvent &event);
    void OnRMSUnitTimer(wxTimerEvent&);
    void OnRMSUnitSelect(wxCommandEvent &event);
    void OnRMSUnitAdd(wxCommandEvent &event);
    void OnRMSUnitInsert(wxCommandEvent &event);
    void OnRMSUnitDelete(wxCommandEvent &event);
    void OnRMSUnitCopy(wxCommandEvent &event);
    void OnRMSUnitPaste(wxCommandEvent &event);
    void OnRMSUnitPasteInsert(wxCommandEvent &event);
    void OnRMSUnitCopyToMaps(wxCommandEvent &event);
    string GetRMSUnitName(int);

    void ListRMSUnknowns();
    void OnRMSUnknownSearch(wxCommandEvent &event);
    void OnRMSUnknownTimer(wxTimerEvent&);
    void OnRMSUnknownSelect(wxCommandEvent &event);
    void OnRMSUnknownAdd(wxCommandEvent &event);
    void OnRMSUnknownInsert(wxCommandEvent &event);
    void OnRMSUnknownDelete(wxCommandEvent &event);
    void OnRMSUnknownCopy(wxCommandEvent &event);
    void OnRMSUnknownPaste(wxCommandEvent &event);
    void OnRMSUnknownPasteInsert(wxCommandEvent &event);
    void OnRMSUnknownCopyToMaps(wxCommandEvent &event);
    string GetRMSUnknownName(int);

//  Research Events

    void ListResearches(bool all = true);
    void OnResearchSearch(wxCommandEvent &event);
    void OnResearchTimer(wxTimerEvent&);
    void OnResearchSelect(wxCommandEvent &event);
    void OnResearchAdd(wxCommandEvent &event);
    void OnResearchInsert(wxCommandEvent &event);
    void OnResearchDelete(wxCommandEvent &event);
    void OnResearchCopy(wxCommandEvent &event);
    void OnResearchPaste(wxCommandEvent &event);
    void OnResearchPasteInsert(wxCommandEvent &event);
    string GetResearchName(int, bool = false);

//  Tech Events

    void ListTechs(bool all = true);
    void OnTechSearch(wxCommandEvent &event);
    void OnTechTimer(wxTimerEvent&);
    void OnTechSelect(wxCommandEvent &event);
    void OnTechAdd(wxCommandEvent &event);
    void OnTechInsert(wxCommandEvent &event);
    void OnTechDelete(wxCommandEvent &event);
    void OnTechCopy(wxCommandEvent &event);
    void OnTechPaste(wxCommandEvent &event);
    void OnTechPasteInsert(wxCommandEvent &event);
    void OnTechRename(wxCommandEvent &event);
    void OnTechRenameGE2(wxCommandEvent &event);
    string GetTechName(int);

    void ListEffects();
    void OnEffectsSearch(wxCommandEvent &event);
    void OnEffectsTimer(wxTimerEvent&);
    void OnEffectsSelect(wxCommandEvent &event);
    void OnEffectsAdd(wxCommandEvent &event);
    void OnEffectsInsert(wxCommandEvent &event);
    void OnEffectsDelete(wxCommandEvent &event);
    void OnEffectsCopy(wxCommandEvent &event);
    void OnEffectsPaste(wxCommandEvent &event);
    void OnEffectsPasteInsert(wxCommandEvent &event);
    void OnEffectsCopyToTechs(wxCommandEvent &event);
    string GetEffectName(int, int);

//  Tech Tree Events

    void ListTTAges();
    void OnTTAgesSearch(wxCommandEvent &event);
    void OnTTAgesTimer(wxTimerEvent&);
    void OnTTAgesSelect(wxCommandEvent &event);
    void OnTTAgesAdd(wxCommandEvent &event);
    void OnTTAgesInsert(wxCommandEvent &event);
    void OnTTAgesDelete(wxCommandEvent &event);
    void OnTTAgesCopy(wxCommandEvent &event);
    void OnTTAgesPaste(wxCommandEvent &event);
    void OnTTAgesPasteInsert(wxCommandEvent &event);
    string GetTTAgesName(int);

    void ListTTAgeBuildings();
    void OnTTAgesBuildingSearch(wxCommandEvent &event);
    void OnTTAgesBuildingTimer(wxTimerEvent&);
    void OnTTAgesBuildingSelect(wxCommandEvent &event);
    void OnTTAgesBuildingAdd(wxCommandEvent &event);
    void OnTTAgesBuildingInsert(wxCommandEvent &event);
    void OnTTAgesBuildingDelete(wxCommandEvent &event);
    void OnTTAgesBuildingCopy(wxCommandEvent &event);
    void OnTTAgesBuildingPaste(wxCommandEvent &event);
    void OnTTAgesBuildingPasteInsert(wxCommandEvent &event);
    void OnTTAgesBuildingCopyToAges(wxCommandEvent &event);
    string GetBuildingName(int);

    void ListTTAgeUnits();
    void OnTTAgesUnitSearch(wxCommandEvent &event);
    void OnTTAgesUnitTimer(wxTimerEvent&);
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
    void OnTTAgesResearchTimer(wxTimerEvent&);
    void OnTTAgesResearchSelect(wxCommandEvent &event);
    void OnTTAgesResearchAdd(wxCommandEvent &event);
    void OnTTAgesResearchInsert(wxCommandEvent &event);
    void OnTTAgesResearchDelete(wxCommandEvent &event);
    void OnTTAgesResearchCopy(wxCommandEvent &event);
    void OnTTAgesResearchPaste(wxCommandEvent &event);
    void OnTTAgesResearchPasteInsert(wxCommandEvent &event);
    void OnTTAgesResearchCopyToAges(wxCommandEvent &event);
    string GetSimpleResearchName(int);

    void ListTTAgeItems();
    void OnTTAgeItemSearch(wxCommandEvent &event);
    void OnTTAgeItemTimer(wxTimerEvent&);
    void OnTTAgeItemSelect(wxCommandEvent &event);
    void OnTTAgeItemCopy(wxCommandEvent &event);
    void OnTTAgeItemPaste(wxCommandEvent &event);
    void OnTTAgeItemCopyToAges(wxCommandEvent &event);

    void ListTTAgeUnknownItems();
    void OnTTAgeUnknownItemSearch(wxCommandEvent &event);
    void OnTTAgeUnknownItemTimer(wxTimerEvent&);
    void OnTTAgeUnknownItemSelect(wxCommandEvent &event);
    void OnTTAgeUnknownItemCopy(wxCommandEvent &event);
    void OnTTAgeUnknownItemPaste(wxCommandEvent &event);
    void OnTTAgeUnknownItemCopyToAges(wxCommandEvent &event);

    void ListTTBuildings();
    void OnTTBuildingSearch(wxCommandEvent &event);
    void OnTTBuildingTimer(wxTimerEvent&);
    void OnTTBuildingSelect(wxCommandEvent &event);
    void OnTTBuildingAdd(wxCommandEvent &event);
    void OnTTBuildingInsert(wxCommandEvent &event);
    void OnTTBuildingDelete(wxCommandEvent &event);
    void OnTTBuildingCopy(wxCommandEvent &event);
    void OnTTBuildingPaste(wxCommandEvent &event);
    void OnTTBuildingPasteInsert(wxCommandEvent &event);
    string GetTTBuildingName(int);

    void ListTTBuildingBuildings();
    void OnTTBuildingBuildingSearch(wxCommandEvent &event);
    void OnTTBuildingBuildingTimer(wxTimerEvent&);
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
    void OnTTBuildingUnitTimer(wxTimerEvent&);
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
    void OnTTBuildingResearchTimer(wxTimerEvent&);
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
    void OnTTBuildingItemTimer(wxTimerEvent&);
    void OnTTBuildingItemSelect(wxCommandEvent &event);
    void OnTTBuildingItemCopy(wxCommandEvent &event);
    void OnTTBuildingItemPaste(wxCommandEvent &event);
    void OnTTBuildingItemCopyToBuildings(wxCommandEvent &event);

    void ListTTUnits();
    void OnTTUnitSearch(wxCommandEvent &event);
    void OnTTUnitTimer(wxTimerEvent&);
    void OnTTUnitSelect(wxCommandEvent &event);
    void OnTTUnitAdd(wxCommandEvent &event);
    void OnTTUnitInsert(wxCommandEvent &event);
    void OnTTUnitDelete(wxCommandEvent &event);
    void OnTTUnitCopy(wxCommandEvent &event);
    void OnTTUnitPaste(wxCommandEvent &event);
    void OnTTUnitPasteInsert(wxCommandEvent &event);
    string GetTTUnitName(int);

    void ListTTUnitUnits();
    void OnTTUnitUnitSearch(wxCommandEvent &event);
    void OnTTUnitUnitTimer(wxTimerEvent&);
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
    void OnTTUnitItemTimer(wxTimerEvent&);
    void OnTTUnitItemSelect(wxCommandEvent &event);
    void OnTTUnitItemCopy(wxCommandEvent &event);
    void OnTTUnitItemPaste(wxCommandEvent &event);
    void OnTTUnitItemCopyToUnits(wxCommandEvent &event);

    void ListTTResearches();
    void OnTTResearchSearch(wxCommandEvent &event);
    void OnTTResearchTimer(wxTimerEvent&);
    void OnTTResearchSelect(wxCommandEvent &event);
    void OnTTResearchAdd(wxCommandEvent &event);
    void OnTTResearchInsert(wxCommandEvent &event);
    void OnTTResearchDelete(wxCommandEvent &event);
    void OnTTResearchCopy(wxCommandEvent &event);
    void OnTTResearchPaste(wxCommandEvent &event);
    void OnTTResearchPasteInsert(wxCommandEvent &event);
    string GetTTResearchName(int);

    void ListTTResearchBuildings();
    void OnTTResearchBuildingSearch(wxCommandEvent &event);
    void OnTTResearchBuildingTimer(wxTimerEvent&);
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
    void OnTTResearchUnitTimer(wxTimerEvent&);
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
    void OnTTResearchResearchTimer(wxTimerEvent&);
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
    void OnTTResearchItemTimer(wxTimerEvent&);
    void OnTTResearchItemSelect(wxCommandEvent &event);
    void OnTTResearchItemCopy(wxCommandEvent &event);
    void OnTTResearchItemPaste(wxCommandEvent &event);
    void OnTTResearchItemCopyToResearches(wxCommandEvent &event);

//  Civilization Events

    void ListCivs(bool all = true);
    void OnCivsSearch(wxCommandEvent &event);
    void OnCivsTimer(wxTimerEvent&);
    void OnCivsSelect(wxCommandEvent &event);
    void OnCivsAdd(wxCommandEvent &event);
    void OnCivsInsert(wxCommandEvent &event);
    void OnCivsDelete(wxCommandEvent &event);
    void OnCivsCopy(wxCommandEvent &event);
    void OnCivsPaste(wxCommandEvent &event);
    void OnCivsPasteInsert(wxCommandEvent &event);
    string GetCivName(int);
    void OnCivCountChange();

    void ListResources(bool all = true);
    void OnResourcesSearch(wxCommandEvent &event);
    void OnResourcesTimer(wxTimerEvent&);
    void OnResourcesSelect(wxCommandEvent &event);
    void OnResourcesAdd(wxCommandEvent &event);
    void OnResourcesInsert(wxCommandEvent &event);
    void OnResourcesDelete(wxCommandEvent &event);
    void OnResourcesCopy(wxCommandEvent &event);
    void OnResourcesPaste(wxCommandEvent &event);
    void OnResourcesPasteInsert(wxCommandEvent &event);
    void OnResourcesCopyToAll(wxCommandEvent &event);
    wxString GetResourceName(int);

    void ListUnits(short civ, bool all = true);
    void OnUnitsSearch(wxCommandEvent&); // Convert to local lambda
    void OnUnitsTimer(wxTimerEvent&);
    void OnUnitsSelect(wxCommandEvent&); // Convert to local lambda
    void UnitsGraphicsCopy(GraphicCopies &store, short civ, short unit);
    void PasteUnits(bool OneOnOne = false);
    short CorrectID(bool OneOnOne, size_t loop);
    void UnitsGraphicsPaste(GraphicCopies &store, short civ, short unit);
    wxString GetUnitName(int, short, bool = false);
    void PrepUnitSearch();
    vector<function<wxString(genie::Unit*)>> UnitFilterFunctions;

    void ListUnitDamageGraphics();
    void OnUnitDamageGraphicsSearch(wxCommandEvent &event);
    void OnUnitDamageGraphicsTimer(wxTimerEvent&);
    void OnUnitDamageGraphicsSelect(wxCommandEvent &event);
    void OnUnitDamageGraphicsAdd(wxCommandEvent &event);
    void OnUnitDamageGraphicsInsert(wxCommandEvent &event);
    void OnUnitDamageGraphicsDelete(wxCommandEvent &event);
    void OnUnitDamageGraphicsCopy(wxCommandEvent &event);
    void OnUnitDamageGraphicsPaste(wxCommandEvent &event);
    void OnUnitDamageGraphicsPasteInsert(wxCommandEvent &event);
    void OnUnitDamageGraphicsCopyToUnits(wxCommandEvent &event);
    string GetUnitDamageGraphicName(int);

    void ListUnitAttacks();
    void OnUnitAttacksSearch(wxCommandEvent &event);
    void OnUnitAttacksTimer(wxTimerEvent&);
    void OnUnitAttacksSelect(wxCommandEvent &event);
    void OnUnitAttacksAdd(wxCommandEvent &event);
    void OnUnitAttacksInsert(wxCommandEvent &event);
    void OnUnitAttacksDelete(wxCommandEvent &event);
    void OnUnitAttacksCopy(wxCommandEvent &event);
    void OnUnitAttacksPaste(wxCommandEvent &event);
    void OnUnitAttacksPasteInsert(wxCommandEvent &event);
    void OnUnitAttacksCopyToUnits(wxCommandEvent &event);
    string GetUnitAttackName(int);

    void ListUnitArmors();
    void OnUnitArmorsSearch(wxCommandEvent &event);
    void OnUnitArmorsTimer(wxTimerEvent&);
    void OnUnitArmorsSelect(wxCommandEvent &event);
    void OnUnitArmorsAdd(wxCommandEvent &event);
    void OnUnitArmorsInsert(wxCommandEvent &event);
    void OnUnitArmorsDelete(wxCommandEvent &event);
    void OnUnitArmorsCopy(wxCommandEvent &event);
    void OnUnitArmorsPaste(wxCommandEvent &event);
    void OnUnitArmorsPasteInsert(wxCommandEvent &event);
    void OnUnitArmorsCopyToUnits(wxCommandEvent &event);
    string GetUnitArmorName(int);

//  Unit Events

    void ListUnitCommands();
    void OnUnitCommandsSearch(wxCommandEvent &event);
    void OnUnitCommandsTimer(wxTimerEvent&);
    void OnUnitCommandsSelect(wxCommandEvent &event);
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
    void OnUnitLinesTimer(wxTimerEvent&);
    void OnUnitLinesSelect(wxCommandEvent &event);
    void OnUnitLinesAdd(wxCommandEvent &event);
    void OnUnitLinesInsert(wxCommandEvent &event);
    void OnUnitLinesDelete(wxCommandEvent &event);
    void OnUnitLinesCopy(wxCommandEvent &event);
    void OnUnitLinesPaste(wxCommandEvent &event);
    void OnUnitLinesPasteInsert(wxCommandEvent &event);
    string GetUnitLineName(int);

    void ListUnitLineUnits();
    void OnUnitLineUnitsSearch(wxCommandEvent &event);
    void OnUnitLineUnitsTimer(wxTimerEvent&);
    void OnUnitLineUnitsSelect(wxCommandEvent &event);
    void OnUnitLineUnitsAdd(wxCommandEvent &event);
    void OnUnitLineUnitsInsert(wxCommandEvent &event);
    void OnUnitLineUnitsDelete(wxCommandEvent &event);
    void OnUnitLineUnitsCopy(wxCommandEvent &event);
    void OnUnitLineUnitsPaste(wxCommandEvent &event);
    void OnUnitLineUnitsPasteInsert(wxCommandEvent &event);
    void OnUnitLineUnitsCopyToUnitLines(wxCommandEvent &event);
    string GetUnitLineUnitName(int);

//  Graphic Events

    void ListGraphics(bool all = true);
    void OnGraphicsSearch(wxCommandEvent &event);
    void OnGraphicsTimer(wxTimerEvent&);
    void OnGraphicsSelect(wxCommandEvent &event);
    void OnGraphicsAdd(wxCommandEvent &event);
    void OnGraphicsInsert(wxCommandEvent &event);
    void OnGraphicsDelete(wxCommandEvent &event);
    void OnGraphicsCopy(wxCommandEvent &event);
    void OnGraphicsPaste(wxCommandEvent &event);
    void OnGraphicsPasteInsert(wxCommandEvent &event);
    void OnGraphicsEnable(wxCommandEvent &event);
    void OnGraphicsDisable(wxCommandEvent &event);
    string GetGraphicName(int, bool = false);

    void ListGraphicDeltas();
    void OnGraphicDeltasSearch(wxCommandEvent &event);
    void OnGraphicDeltasTimer(wxTimerEvent&);
    void OnGraphicDeltasSelect(wxCommandEvent &event);
    void OnGraphicDeltasAdd(wxCommandEvent &event);
    void OnGraphicDeltasInsert(wxCommandEvent &event);
    void OnGraphicDeltasDelete(wxCommandEvent &event);
    void OnGraphicDeltasCopy(wxCommandEvent &event);
    void OnGraphicDeltasPaste(wxCommandEvent &event);
    void OnGraphicDeltasPasteInsert(wxCommandEvent &event);
    void OnGraphicDeltasCopyToGraphics(wxCommandEvent &event);
    string GetGraphicDeltaName(int);

    void ListGraphicAttackSounds();
    void OnGraphicAttackSoundsSearch(wxCommandEvent &event);
    void OnGraphicAttackSoundsTimer(wxTimerEvent&);
    void OnGraphicAttackSoundsSelect(wxCommandEvent &event);
    void OnGraphicAttackSoundsCopy(wxCommandEvent &event);
    void OnGraphicAttackSoundsCopyToGraphics(wxCommandEvent &event);
    string GetGraphicAttackSoundName(int);

//  Terrain Events

    void ListTerrainNumbers();
    void OnTerrainCountChange(wxFocusEvent &event);

    void ListTerrains1(bool all = true);
    void ListTerrains2();
    void OnTerrainsSearch(wxCommandEvent &event);
    void OnTerrainsTimer(wxTimerEvent&);
    void OnTerrainsSelect(wxCommandEvent &event);
    void OnTerrainsAdd(wxCommandEvent &event);
    void OnTerrainsDelete(wxCommandEvent &event);
    void OnTerrainsCopy(wxCommandEvent &event);
    void OnTerrainsPaste(wxCommandEvent &event);
    string GetTerrainName(int, bool = false);

    void OnTerrainsBorderSearch(wxCommandEvent &event);
    void ListTerrainsBorders();
    void OnTerrainsBorderTimer(wxTimerEvent&);
    void OnTerrainsBorderSelect(wxCommandEvent &event);
    void OnTerrainsBorderCopy(wxCommandEvent &event);
    void OnTerrainsBorderPaste(wxCommandEvent &event);
    void OnTerrainsBorderCopyToBuildings(wxCommandEvent &event);

//  Terrain Border Events

    void ListTerrainBorders(bool all = true);
    void OnTerrainBordersSearch(wxCommandEvent &event);
    void OnTerrainBordersTimer(wxTimerEvent&);
    void OnTerrainBordersSelect(wxCommandEvent &event);
    void OnTerrainBordersCopy(wxCommandEvent &event);
    void OnTerrainBordersPaste(wxCommandEvent &event);
    string GetTerrainBorderName(int);

    void ListTerrainBorderTileTypes();
    void OnTerrainBorderTileTypeSearch(wxCommandEvent &event);
    void OnTerrainBorderTileTypeTimer(wxTimerEvent&);
    void OnTerrainBorderTileTypeSelect(wxCommandEvent &event);
    void OnTerrainBorderTileTypeCopy(wxCommandEvent &event);
    void OnTerrainBorderTileTypePaste(wxCommandEvent &event);
    void OnTerrainBorderTileTypeCopyToBorders(wxCommandEvent &event);
    string GetTerrainBorderTileTypeName(int);

    void ListTerrainBorderBorderShapes();
    void OnTerrainBorderBorderShapeSearch(wxCommandEvent &event);
    void OnTerrainBorderBorderShapeTimer(wxTimerEvent&);
    void OnTerrainBorderBorderShapeSelect(wxCommandEvent &event);
    void OnTerrainBorderBorderShapeCopy(wxCommandEvent &event);
    void OnTerrainBorderBorderShapePaste(wxCommandEvent &event);
    void OnTerrainBorderBorderShapeCopyToBorders(wxCommandEvent &event);
    string GetTerrainBorderBorderShapeName(int);

//  Terrain Restriction Events

    void ListTerrainRestrictions(bool all = true);
    void OnTerrainRestrictionsSearch(wxCommandEvent &event);
    void OnTerrainRestrictionsTimer(wxTimerEvent&);
    void OnTerrainRestrictionsSelect(wxCommandEvent &event);
    void OnTerrainRestrictionsTerrainTimer(wxTimerEvent&);
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
    void OnSoundsTimer(wxTimerEvent&);
    void OnSoundsSelect(wxCommandEvent &event);
    void OnSoundsAdd(wxCommandEvent &event);
    void OnSoundsInsert(wxCommandEvent &event);
    void OnSoundsDelete(wxCommandEvent &event);
    void OnSoundsCopy(wxCommandEvent &event);
    void OnSoundsPaste(wxCommandEvent &event);
    void OnSoundsPasteInsert(wxCommandEvent &event);
    string GetSoundName(int);

    void ListSoundItems();
    void OnSoundItemsSearch(wxCommandEvent &event);
    void OnSoundItemsTimer(wxTimerEvent&);
    void OnSoundItemsSelect(wxCommandEvent &event);
    void OnSoundItemsAdd(wxCommandEvent &event);
    void OnSoundItemsInsert(wxCommandEvent &event);
    void OnSoundItemsDelete(wxCommandEvent &event);
    void OnSoundItemsCopy(wxCommandEvent &event);
    void OnSoundItemsPaste(wxCommandEvent &event);
    void OnSoundItemsPasteInsert(wxCommandEvent &event);
    void OnSoundItemsCopyToSounds(wxCommandEvent &event);
    string GetSoundItemName(int, int);

//  Player Color Events

    void ListPlayerColors();
    void OnPlayerColorsSearch(wxCommandEvent &event);
    void OnPlayerColorsTimer(wxTimerEvent&);
    void OnPlayerColorsSelect(wxCommandEvent &event);
    void OnPlayerColorsAdd(wxCommandEvent &event);
    void OnPlayerColorsInsert(wxCommandEvent &event);
    void OnPlayerColorsDelete(wxCommandEvent &event);
    void OnPlayerColorsCopy(wxCommandEvent &event);
    void OnPlayerColorsPaste(wxCommandEvent &event);
    void OnPlayerColorsPasteInsert(wxCommandEvent &event);
    string GetPlayerColorName(int);

//  Application Variables

    float EditorVersion;
    wxString EditorVersionString, slp_extra_info;
    bool PromptForFilesOnOpen, AutoCopy, CopyGraphics, AllCivs, AutoBackups, StayOnTop, StayOnTopSLP;
    vector<short> SelectedCivs;
    bool SearchAnd = false, ExcludeAnd = false, EnableIDFix, ShowUnknowns, ResizeTerrains, SkipOpenDialog, Paste11, Reselection;
    bool ShowSLP, AnimSLP, ShowShadows, ShowOutline, ShowDeltas, ShowStack, ShowAnnexes, ShowIcons, DrawHot = false, DrawTerrain;
    bool DrawCollisionShape, DrawClearanceShape, DrawSelectionShape, DrawAngles = false;
    vector<genie::DrsFile*> datafiles;
    vector<vector<genie::Color>> palettes;
    genie::DatFile *dataset = 0;
    genie::LangFile *Lang = 0, *LangX = 0, *LangXP = 0;
    int CustomTerrains, SLPareaPerCent, paletteView = 0, SLPbackR, SLPbackG, SLPbackB;
    wxBrush slp_background_brush;
    wxFrame *slp_window = 0;
    APanel *slp_view;
    wxSizer *slp_sizer;
    wxButton *slp_next, *slp_frame_export, *slp_frame_import, *slp_save, *slp_prev, *slp_first, *slp_tool, *slp_merge_shadow;
    wxFilePickerCtrl *slp_source1, *slp_source2, *slp_target1;
    wxFlexGridSizer *slp_tool_layout;
    wxRadioBox *slp_radio, *slp_unit_actions;
    wxCheckBox *slp_dmg_unit, *slp_snow, *slp_garrison, *slp_hotspot, *slp_collision, *slp_clearance, *slp_selection;
    wxCheckBox *slp_animate, *slp_shadow, *slp_outline, *slp_delta, *slp_stack, *slp_annex, *slp_terrain, *slp_angles, *slp_show_angles;
    wxColourPickerCtrl *slp_background;
    DelayedPopUp popUp;
    int randomi = 0;

    vector<AGEComboBox*> ResearchComboBoxList, TechComboBoxList, CivComboBoxList, ResourceComboBoxList,
        UnitComboBoxList, GraphicComboBoxList, TerrainComboBoxList, TerrainBorderComboBoxList,
        TerrainRestrictionComboBoxList, SoundComboBoxList;

    vector<int> RandomMapIDs, UnknownFSIDs, UnknownSSIDs, UnknownTSIDs, Unknown4SIDs,
        ResearchIDs, TechIDs, EffectIDs,
        TTAgeIDs, TTAgeBuildIDs, TTAgeUnitIDs, TTAgeResIDs, TTAgeUnknownIDs, TTItemIDs, TTUnknownItemIDs,
        TTBuildConIDs, TTBuildBuildIDs, TTBuildUnitIDs, TTBuildResIDs,
        TTUnitConIDs, TTUnitUnitIDs,
        TTResConIDs, TTResBuildIDs, TTResUnitIDs, TTResResIDs,
        CivIDs, ResourceIDs,
        UnitIDs, DamageGraphicIDs, AttackIDs, ArmorIDs, CommandIDs,
        UnitLineIDs, UnitLineUnitIDs,
        GraphicIDs, DeltaIDs, AttackSoundIDs,
        TerrainIDs, TerBorderIDs, TerRestrictIDs, TerRestrictTerIDs,
        SoundIDs, SoundItemIDs, ColorIDs,
        BorderIDs, BorderTileTypeIDs, BorderShapeIDs;
    int UnitCivID;
    vector<float> TerrainRestrictionSubCopyAccess;

    bool SaveDat, SaveApf, WriteLangs, SaveLangs, LangWriteToLatest, SyncSaveWithOpen,
        UseCustomPath, UseTXT = false, UseDRS, UseMod, UseExtra, FilterAllSubs;
    enum ListMode {SEARCH, ADD, DEL, PASTE, INSNEW, INSPASTE, ENABLE};
    short How2List;
    int TimesOpened, GameVersion, DatUsed, SaveGameVersion, MaxWindowWidthV2, MinWindowWidth;
    void FixSizes();
    chrono::time_point<chrono::system_clock> endTime;
    genie::GameVersion GenieVersion = genie::GV_None;
    wxString DriveLetter, Language, CustomFolder;
    wxString DatFileName, SaveDatFileName, FolderDRS, FolderDRS2, Path1stDRS;
    int LangsUsed; // 0x01 Lang.dll, 0x02, LangX1.dll, 0x04 LangX1P1.dll
    wxString LangCharset;
    wxString LangFileName, LangX1FileName, LangX1P1FileName;
    wxString SaveLangFileName, SaveLangX1FileName, SaveLangX1P1FileName;

    map<int, string> LangTxt;
    HINSTANCE LanguageDLL[3];
    wxString LangDLLstring(int ID, int Letters = 0);
    //void WriteLangDLLstring(int ID, wxString Name);
    bool exportFrame = false;
    void LoadTXT(const wxString &filename);
    void LoadSLPFrame(AGE_SLP*);
    void SLPtoBitMap(AGE_SLP*);
    void BitMaptoSLP(AGE_SLP*);
    AGE_SLP iconSLP, graphicSLP, unitSLP, techSLP, tileSLP, borderSLP;

public:
//  Constants, remove unneeded entries.

    enum
    {
        // menus and tool bar
        ePrompt = wxID_HIGHEST + 1,
        eIdFix, eButtons, eShowSLP, eShowIcons, eTips, eStayOnTop, eStayOnTopSLP, eAbout,
        eBackup, eUnknown, eHelp, eDRS, eHex, eFloat, ePaste, eReselection, eAddWindow,

        // open and save
        eOpen,
        eSave,

        // tab change
        eTabBar,

        // buttons
        eNextFrame, ePrevFrame, eFirstFrame, eExportFrame, eImportFrame, eSaveSLP, eSLPTool, eSLPMergeShadow,

        // check boxes
        eShowHotspot, eAnimSLP, eShowShadows, eShowOutline, eShowDeltas, eShowStack, eShowAnnexes, eShowTerrain,
        eCollisionShape, eClearanceShape, eSelectionShape, eShowAngles,

        // color picker
        ePickBgColor,

        // invisible
        hotWin1, hotWin2, hotWin3, hotWin4, closeAll
    };

    static const wxString MirrorHelp;

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
        action_type_names, unit_type_names, graphicset_names, specialcopy_names,
        unit_filter_options, civ_names_only, mode_names;

    wxMenuBar *MenuBar_Main;
    wxMenu *SubMenu_Options, *SubMenu_Help, *SubMenu_SLP;

    wxNotebook *TabBar_Main, *TabBar_TechTree;

    APanel *Tab_General, *Tab_Research, *Tab_Techs, *Tab_TechTrees, *Tab_Civs,
        *Tab_Units, *Tab_UnitLine, *Tab_Graphics, *Tab_Terrains, *Tab_TerrainBorders,
        *Tab_TerrainRestrictions, *Tab_Sounds, *Tab_PlayerColors, *Tab_Unknown,
        *Tab_TechTreeAges, *Tab_TechTreeBuildings, *Tab_TechTreeUnits, *Tab_TechTreeResearches;

//  General user interface

    wxBoxSizer *General_Main;
    wxBoxSizer *General_TopRow;
    wxButton *General_Refresh;
    SolidText *General_CalcBoxes_Text;
    SolidText *General_CalcBoxesMiddle_Text;
    wxTextCtrl *General_CalcBoxes[5];
    wxScrolled<APanel> *General_Scroller;
    wxBoxSizer *General_ScrollSpace;
    SolidText *General_TileSizes_Text;
    wxGridSizer *General_TileSizes_Grid;
    array<wxBoxSizer*, 19> General_TileSizes_Sizers;
    array<AGETextCtrl*, 57> General_TileSizes;

    wxBoxSizer *UnknownPointer1_Sizer;
    SolidText *UnknownPointer1_Text;
    AGETextCtrl *UnknownPointer1;
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

    wxBoxSizer *UnknownPointer2_Sizer;
    SolidText *UnknownPointer2_Text;
    AGETextCtrl *UnknownPointer2;
    wxBoxSizer *UnknownPointer3_Sizer;
    SolidText *UnknownPointer3_Text;
    AGETextCtrl *UnknownPointer3;
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
    array<AGETextCtrl*, 25> General_SomeBytes;
    wxGridSizer *General_Something_Grid1, *General_Something_Grid2;
    array<AGETextCtrl*, 157> General_Something;

    wxBoxSizer *Borders_Main;
    wxStaticBoxSizer *Borders_Borders;
    wxGridSizer *Borders_Buttons;
    wxTextCtrl *Borders_Search;
    wxTextCtrl *Borders_Search_R;
    AGEListView *Borders_ListV;
    wxButton *Borders_Copy;
    wxButton *Borders_Paste;
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
    AGEListView *Borders_TileTypes_ListV;
    wxButton *TileTypes_Copy;
    wxButton *TileTypes_Paste;
    wxButton *TileTypes_CopyToBorders;

    wxStaticBoxSizer *Borders_BorderShapes;
    wxGridSizer *Borders_BorderShapes_Buttons;
    wxTextCtrl *Borders_BorderShapes_Search;
    wxTextCtrl *Borders_BorderShapes_Search_R;
    AGEListView *Borders_BorderShapes_ListV;
    wxButton *BorderShapes_Copy;
    wxButton *BorderShapes_Paste;
    wxButton *BorderShapes_CopyToBorders;

    wxBoxSizer *Borders_FrameArea_Holder;
    wxBoxSizer *Borders_Enabled_Holder;
    wxBoxSizer *Borders_Enabled1_Holder;
    SolidText *Borders_Enabled_Text;
    AGETextCtrl *Borders_Enabled;
    CheckBox_2State *Borders_Enabled_CheckBox;
    wxBoxSizer *Borders_Random_Holder;
    SolidText *Borders_Random_Text;
    AGETextCtrl *Borders_Random;
    wxBoxSizer *Borders_Name_Holder[2];
    SolidText *Borders_Name_Text[2];
    AGETextCtrl *Borders_Name[2];
    wxBoxSizer *Borders_SLP_Holder;
    SolidText *Borders_SLP_Text;
    AGETextCtrl *Borders_SLP;
    wxBoxSizer *Borders_Unknown3_Holder;
    SolidText *Borders_Unknown3_Text;
    AGETextCtrl *Borders_Unknown3;
    wxBoxSizer *Borders_Sound_Holder;
    SolidText *Borders_Sound_Text;
    AGETextCtrl *Borders_Sound;
    wxBoxSizer *Borders_Colors_Holder;
    wxGridSizer *Borders_Colors_Grid;
    SolidText *Borders_Colors_Text;
    array<AGETextCtrl*, 3> Borders_Colors;
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
    wxBoxSizer *Borders_DrawTile_Holder;
    SolidText *Borders_DrawTile_Text;
    AGETextCtrl *Borders_DrawTile;
    wxBoxSizer *Borders_Terrain_Holder;
    SolidText *Borders_Terrain_Text;
    AGETextCtrl *Borders_Terrain;
    ComboBox_Plus1 *Borders_Terrain_ComboBox;
    wxBoxSizer *Borders_BorderStyle_Holder;
    SolidText *Borders_BorderStyle_Text;
    AGETextCtrl *Borders_BorderStyle;

    vector<AGETextCtrl*> uiGroupMaps, uiGroupTT, uiGroupTTAge, uiGroupTTBuilding, uiGroupTTUnit, uiGroupTTResearch;
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
    array<wxBoxSizer*, 8> General_TTUnknown_Holder;
    array<SolidText*, 8> General_TTUnknown_Text;
    array<AGETextCtrl*, 8> General_TTUnknown;

    wxBoxSizer *General_MapPointer_Holder;
    SolidText *General_MapPointer_Text;
    AGETextCtrl *General_MapPointer;
    wxBoxSizer *General_Unknown1_Holder;
    SolidText *General_Unknown1_Text;
    AGETextCtrl *General_Unknown1;
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
    wxBoxSizer *General_Unknown2_Holder;
    SolidText *General_Unknown2_Text;
    AGETextCtrl *General_Unknown2;

    wxBoxSizer *Unknown_Main;
    wxScrolled<APanel> *Unknown_Scroller;
    wxBoxSizer *Unknown_ScrollSpace;

    vector<AGETextCtrl*> uiGroupRandomMap, uiGroupRMBase, uiGroupRMTerrain, uiGroupRMUnit, uiGroupRMUnknown;
    SolidText *Unknown_UnknownPointer_Text;
    AGETextCtrl *Unknown_UnknownPointer;

    wxStaticBoxSizer *Unknowns;
    wxBoxSizer *Unknowns_ListArea;
    wxTextCtrl *Unknowns_Search;
    wxTextCtrl *Unknowns_Search_R;
    AGEListView *Unknowns_ListV;
    wxGridSizer *Unknowns_Buttons;
    wxButton *Unknowns_Add;
    wxButton *Unknowns_Insert;
    wxButton *Unknowns_Delete;
    wxButton *Unknowns_Copy;
    wxButton *Unknowns_Paste;
    wxButton *Unknowns_PasteInsert;

    SolidText *Unknowns_UnknownLevel_Text;
    AGETextCtrl *Unknowns_UnknownLevel;
    wxGridSizer *Unknowns_Unknown1_Grid;
    array<wxBoxSizer*, 9> Unknowns_Unknown1_Holder;
    array<SolidText*, 9> Unknowns_Unknown1_Text;
    array<AGETextCtrl*, 9> Unknowns_Unknown1;
    SolidText *Unknowns_Pointer1_Text;
    AGETextCtrl *Unknowns_Pointer1;
    SolidText *Unknowns_Pointer2_Text;
    AGETextCtrl *Unknowns_Pointer2;
    SolidText *Unknowns_Pointer3_Text;
    AGETextCtrl *Unknowns_Pointer3;
    SolidText *Unknowns_Pointer4_Text;
    AGETextCtrl *Unknowns_Pointer4;

    wxStaticBoxSizer *RMSBaseZones;
    wxBoxSizer *RMSBaseZones_ListArea;
    wxTextCtrl *RMSBaseZones_Search;
    wxTextCtrl *RMSBaseZones_Search_R;
    AGEListView *RMSBaseZones_ListV;
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
    SolidText *RMSBaseZones_Unknown1_Text;
    AGETextCtrl *RMSBaseZones_Unknown1;
    wxBoxSizer *RMSBaseZones_BaseTerrain_Holder;
    SolidText *RMSBaseZones_BaseTerrain_Text;
    AGETextCtrl *RMSBaseZones_BaseTerrain;
    wxBoxSizer *RMSBaseZones_SpacingBetweenPlayers_Holder;
    SolidText *RMSBaseZones_SpacingBetweenPlayers_Text;
    AGETextCtrl *RMSBaseZones_SpacingBetweenPlayers;
    wxBoxSizer *RMSBaseZones_Unknown4_Holder;
    SolidText *RMSBaseZones_Unknown4_Text;
    AGETextCtrl *RMSBaseZones_Unknown4;

    wxBoxSizer *RMSBaseZones_Unknown5_Holder;
    wxGridSizer *RMSBaseZones_Unknown5_Grid;
    SolidText *RMSBaseZones_Unknown5_Text;
    array<AGETextCtrl*, 4> RMSBaseZones_Unknown5;

    wxBoxSizer *RMSBaseZones_Unknown6_Holder;
    SolidText *RMSBaseZones_Unknown6_Text;
    AGETextCtrl *RMSBaseZones_Unknown6;
    wxBoxSizer *RMSBaseZones_Unknown7_Holder;
    SolidText *RMSBaseZones_Unknown7_Text;
    AGETextCtrl *RMSBaseZones_Unknown7;

    wxBoxSizer *RMSBaseZones_Unknown8_Holder;
    wxGridSizer *RMSBaseZones_Unknown8_Grid;
    SolidText *RMSBaseZones_Unknown8_Text;
    array<AGETextCtrl*, 4> RMSBaseZones_Unknown8;

    wxBoxSizer *RMSBaseZones_StartAreaRadius_Holder;
    SolidText *RMSBaseZones_StartAreaRadius_Text;
    AGETextCtrl *RMSBaseZones_StartAreaRadius;
    wxBoxSizer *RMSBaseZones_Unknown10_Holder;
    SolidText *RMSBaseZones_Unknown10_Text;
    AGETextCtrl *RMSBaseZones_Unknown10;
    wxBoxSizer *RMSBaseZones_Unknown11_Holder;
    SolidText *RMSBaseZones_Unknown11_Text;
    AGETextCtrl *RMSBaseZones_Unknown11;

    wxStaticBoxSizer *RMSTerrain;
    wxBoxSizer *RMSTerrain_ListArea;
    wxTextCtrl *RMSTerrain_Search;
    wxTextCtrl *RMSTerrain_Search_R;
    AGEListView *RMSTerrain_ListV;
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
    array<SolidText*, 6> RMSTerrain_Unknown1_Text;
    array<AGETextCtrl*, 6> RMSTerrain_Unknown1;

    wxStaticBoxSizer *RMSUnit;
    wxBoxSizer *RMSUnit_ListArea;
    wxTextCtrl *RMSUnit_Search;
    wxTextCtrl *RMSUnit_Search_R;
    AGEListView *RMSUnit_ListV;
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
    SolidText *RMSUnit_Unit_Text;
    AGETextCtrl *RMSUnit_Unit;
    wxBoxSizer *RMSUnit_HostTerrain_Holder;
    SolidText *RMSUnit_HostTerrain_Text;
    AGETextCtrl *RMSUnit_HostTerrain;
    wxBoxSizer *RMSUnit_Unknown3_Holder;
    wxGridSizer *RMSUnit_Unknown3_Grid;
    SolidText *RMSUnit_Unknown3_Text;
    array<AGETextCtrl*, 4> RMSUnit_Unknown3;
    wxBoxSizer *RMSUnit_ObjectsPerPlayer_Holder;
    SolidText *RMSUnit_ObjectsPerPlayer_Text;
    AGETextCtrl *RMSUnit_ObjectsPerPlayer;
    wxBoxSizer *RMSUnit_Unknown5_Holder;
    SolidText *RMSUnit_Unknown5_Text;
    AGETextCtrl *RMSUnit_Unknown5;
    wxBoxSizer *RMSUnit_GroupsPerPlayer_Holder;
    SolidText *RMSUnit_GroupsPerPlayer_Text;
    AGETextCtrl *RMSUnit_GroupsPerPlayer;
    wxBoxSizer *RMSUnit_Unknown7_Holder;
    SolidText *RMSUnit_Unknown7_Text;
    AGETextCtrl *RMSUnit_Unknown7;
    wxBoxSizer *RMSUnit_OwnAtStart_Holder;
    SolidText *RMSUnit_OwnAtStart_Text;
    AGETextCtrl *RMSUnit_OwnAtStart;
    wxBoxSizer *RMSUnit_SetPlaceForAllPlayers_Holder;
    SolidText *RMSUnit_SetPlaceForAllPlayers_Text;
    AGETextCtrl *RMSUnit_SetPlaceForAllPlayers;
    wxBoxSizer *RMSUnit_MinDistanceToPlayers_Holder;
    SolidText *RMSUnit_MinDistanceToPlayers_Text;
    AGETextCtrl *RMSUnit_MinDistanceToPlayers;
    wxBoxSizer *RMSUnit_MaxDistanceToPlayers_Holder;
    SolidText *RMSUnit_MaxDistanceToPlayers_Text;
    AGETextCtrl *RMSUnit_MaxDistanceToPlayers;

    wxStaticBoxSizer *RMSUnknown;
    wxBoxSizer *RMSUnknown_ListArea;
    wxTextCtrl *RMSUnknown_Search;
    wxTextCtrl *RMSUnknown_Search_R;
    AGEListView *RMSUnknown_ListV;
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
    array<SolidText*, 6> RMSUnknown_Unknown1_Text;
    array<AGETextCtrl*, 6> RMSUnknown_Unknown1;

//  Researchs user interface

    wxBoxSizer *Research_Main;
    wxGridSizer *Research_Research_Buttons;
    wxScrolled<APanel> *Research_Scroller;
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
    AGEListView *Research_Research_ListV;
    wxButton *Research_Add;
    wxButton *Research_Insert;
    wxButton *Research_Delete;
    wxButton *Research_Copy;
    wxButton *Research_Paste;
    wxButton *Research_PasteInsert;

    vector<AGETextCtrl*> uiGroupResearch;
    wxBoxSizer *Research_RequiredTechArea_Holder;
    wxGridSizer *Research_RequiredTechs_Holder;
    SolidText *Research_RequiredTechArea_Text;
    AGETextCtrl *Research_RequiredTechs[6];
    ComboBox_Plus1 *Research_RequiredTechs_ComboBox[6];
    wxBoxSizer *Research_RequiredTechCount_Holder;
    SolidText *Research_RequiredTechCount_Text;
    AGETextCtrl *Research_RequiredTechCount;

    wxStaticBoxSizer *Research_CostHeader_Holder;
    wxBoxSizer *Research_Cost_Texts;
    array<wxBoxSizer*, 3> Research_Cost_Sizers;
    SolidText *Research_Resources_Text;
    AGETextCtrl *Research_Resources[3];
    ComboBox_Plus1 *Research_Resources_ComboBox[3];
    SolidText *Research_Amount_Text;
    AGETextCtrl *Research_Amount[3];
    SolidText *Research_Used_Text;
    AGETextCtrl *Research_Used[3];
    CheckBox_2State *Research_Used_CheckBox[3];

    wxBoxSizer *Research_Civ_Holder;
    SolidText *Research_Civ_Text;
    AGETextCtrl *Research_Civ;
    ComboBox_Plus1 *Research_Civ_ComboBox;

    wxBoxSizer *Research_FullTechMode_Holder;
    SolidText *Research_FullTechMode_Text;
    AGETextCtrl *Research_FullTechMode;
    CheckBox_2State *Research_FullTechMode_CheckBox;

    wxBoxSizer *Research_ResearchLocation_Holder;
    SolidText *Research_ResearchLocation_Text;
    AGETextCtrl *Research_ResearchLocation;
    ComboBox_Plus1 *Research_ResearchLocation_ComboBox;

    wxBoxSizer *Research_LangDLLName_Holder;
    SolidText *Research_LangDLLName_Text;
    AGETextCtrl *Research_LangDLLName;
    TextCtrl_DLL *Research_DLL_LangDLLName;

    wxBoxSizer *Research_LangDLLDescription_Holder;
    SolidText *Research_LangDLLDescription_Text;
    AGETextCtrl *Research_LangDLLDescription;
    TextCtrl_DLL *Research_DLL_LangDLLDescription;

    wxBoxSizer *Research_ResearchTime_Holder;
    SolidText *Research_ResearchTime_Text;
    AGETextCtrl *Research_ResearchTime;

    wxBoxSizer *Research_TechID_Holder;
    SolidText *Research_TechID_Text;
    AGETextCtrl *Research_TechID;
    ComboBox_Plus1 *Research_TechID_ComboBox;

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

    wxBoxSizer *Research_LanguageDLLHelp_Holder;
    SolidText *Research_LanguageDLLHelp_Text;
    AGETextCtrl *Research_LanguageDLLHelp;
    wxBoxSizer *Research_LanguageDLLName2_Holder;
    SolidText *Research_LanguageDLLName2_Text;
    AGETextCtrl *Research_LanguageDLLName2;
    wxBoxSizer *Research_HotKey_Holder;
    SolidText *Research_HotKey_Text;
    AGETextCtrl *Research_HotKey;
    TextCtrl_DLL *Research_DLL_HotKey;
    TextCtrl_DLL *Research_DLL_LanguageDLLHelp;
    TextCtrl_DLL *Research_DLL_LanguageDLLName2;
    wxBoxSizer *Research_LanguageDLLConverter_Holder[2];
    SolidText *Research_LanguageDLLConverter_Text[2];
    wxTextCtrl *Research_LanguageDLLConverter[2];

    wxBoxSizer *Research_Name_Holder[2];
    SolidText *Research_Name_Text[2];
    AGETextCtrl *Research_Name[2];

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
    ComboBox_Plus1 *Effects_89_Type_CB1;

    wxStaticBoxSizer *Techs_Techs;
    wxBoxSizer *Techs_Searches[2];
    wxTextCtrl *Techs_Search;
    wxTextCtrl *Techs_Search_R;
    wxCheckBox *Techs_UseAnd[2];
    AGEListView *Techs_ListV;
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
    AGEListView *Techs_AllEffects_ListV;
    wxBoxSizer *Techs_AllEffects_Buttons;
    wxButton *Techs_AllEffects_Load;
    wxButton *Techs_AllEffects_Clear;

    SolidText *Techs_Name_Text;
    AGETextCtrl *Techs_Name;

    wxStaticBoxSizer *Techs_Effects;
    wxBoxSizer *Techs_Effects_Searches[2];
    wxTextCtrl *Techs_Effects_Search;
    wxTextCtrl *Techs_Effects_Search_R;
    wxCheckBox *Techs_Effects_UseAnd[2];
    AGEListView *Techs_Effects_ListV;
    wxButton *Techs_Effects_Add;
    wxButton *Techs_Effects_Insert;
    wxButton *Techs_Effects_Delete;
    wxButton *Techs_Effects_Copy;
    wxButton *Techs_Effects_Paste;
    wxButton *Techs_Effects_PasteInsert;
    wxButton *Techs_Effects_CopyToTechs;

    wxBoxSizer *Effects_DataArea;
    vector<AGETextCtrl*> uiGroupTechEffect;
    wxBoxSizer *Effects_Type_Holder;
    wxBoxSizer *Effects_Type2_Holder;
    SolidText *Effects_Type_Text;
    ComboBox_EffectType *Effects_Type_ComboBox;
    AGETextCtrl *Effects_Type;
    wxStaticBoxSizer *Effects_Data_Holder;
    SolidText *Effects_A_Text;
    AGETextCtrl *Effects_A;
    ComboBox_Plus1 *Effects_A_ComboBox; // for effects 0 - 6, 101, 103
    SolidText *Effects_Info_A;
    SolidText *Effects_B_Text;
    AGETextCtrl *Effects_B;
    wxBoxSizer *Effects_B_Boxes;
    CheckBox_2State *Effects_B_CheckBox;    // for effects 1, 2
    ComboBox_Plus1 *Effects_B_ComboBox;    // for effects 0, 3, 4, 5, 101
    SolidText *Effects_Info_B;
    SolidText *Effects_C_Text;
    AGETextCtrl *Effects_C;
    wxBoxSizer *Effects_C_Boxes;
    CheckBox_2State *Effects_C_CheckBox;    // for effects 101, 103
    ComboBox_EffectAttribute *Effects_C_ComboBox; // for effects 0, 4, 5
    SolidText *Effects_Info_C;
    SolidText *Effects_D_Text;
    AGETextCtrl *Effects_D;
    wxBoxSizer *Effects_D_Boxes;
    ComboBox_Plus1 *Effects_D_ComboBox;    // for effect 102
    SolidText *Effects_Info_D;

//  Civs user interface

    wxBoxSizer *Civs_Main;
    wxGridSizer *Civs_Civs_Buttons;
    wxStaticBoxSizer *Civs_Civs;
    wxTextCtrl *Civs_Civs_Search;
    wxTextCtrl *Civs_Civs_Search_R;
    AGEListView *Civs_Civs_ListV;
    wxButton *Civs_Add;
    wxButton *Civs_Insert;
    wxButton *Civs_Delete;
    wxButton *Civs_Copy;
    wxButton *Civs_Paste;
    wxButton *Civs_PasteInsert;

    vector<AGETextCtrl*> uiGroupCiv;
    wxBoxSizer *Civs_DataArea;
    wxBoxSizer *Civs_DataGrid1;
    wxBoxSizer *Civs_DataGrid2;
    wxGridSizer *Civs_DataGrid3;
    SolidText *Civs_One_Text;
    wxBoxSizer *Civs_One_Holder;
    AGETextCtrl *Civs_One;
    wxBoxSizer *Civs_Name_Holder[2];
    SolidText *Civs_Name_Text[2];
    AGETextCtrl *Civs_Name[2];
    wxBoxSizer *Civs_SUnknown1_Holder;
    SolidText *Civs_SUnknown1_Text;
    AGETextCtrl *Civs_SUnknown1[4];
    wxBoxSizer *Civs_TechTree_Holder;
    SolidText *Civs_TechTree_Text;
    AGETextCtrl *Civs_TechTree;
    ComboBox_Plus1 *Civs_TechTree_ComboBox;
    wxBoxSizer *Civs_TeamBonus_Holder;
    SolidText *Civs_TeamBonus_Text;
    AGETextCtrl *Civs_TeamBonus;
    ComboBox_Plus1 *Civs_TeamBonus_ComboBox;
    wxBoxSizer *Civs_GraphicSet_Holder;
    SolidText *Civs_GraphicSet_Text;
    AGETextCtrl *Civs_GraphicSet;
    wxStaticBoxSizer *Civs_Resources;
    wxTextCtrl *Civs_Resources_Search;
    wxTextCtrl *Civs_Resources_Search_R;
    AGEListView *Civs_Resources_ListV;
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

    wxScrolled<APanel> *Units_Scroller;    // Scrollable unit section

    SolidText *visibleUnitCiv;
    AGETextCtrl *Units_Type;
    AGEComboBox *Units_Type_ComboBox;
    AGETextCtrl *Units_ID1;
    AGETextCtrl *Units_LanguageDLLName;
    TextCtrl_DLL *Units_DLL_LanguageName;
    AGETextCtrl *Units_LanguageDLLCreation;
    TextCtrl_DLL *Units_DLL_LanguageCreation;
    AGETextCtrl *Units_Class;
    ComboBox_Plus1 *Units_Class_ComboBox[2];
    AGETextCtrl *Units_StandingGraphic[2];
    ComboBox_Plus1 *Units_StandingGraphic_ComboBox[2];
    AGETextCtrl *Units_DyingGraphic[2];
    ComboBox_Plus1 *Units_DyingGraphic_ComboBox[2];
    AGETextCtrl *Units_DeathMode;
    CheckBox_2State *Units_DeathMode_CheckBox;
    AGETextCtrl *Units_HitPoints;
    AGETextCtrl *Units_LineOfSight;
    AGETextCtrl *Units_GarrisonCapacity;
    AGETextCtrl *Units_SizeRadius[2];
    AGETextCtrl *Units_HPBarHeight1;
    AGETextCtrl *Units_TrainSound[2];
    ComboBox_Plus1 *Units_TrainSound_ComboBox[2];
    AGETextCtrl *Units_DeadUnitID;
    ComboBox_Plus1 *Units_DeadUnitID_ComboBox;
    AGETextCtrl *Units_PlacementMode;
    AGETextCtrl *Units_AirMode;
    CheckBox_2State *Units_AirMode_CheckBox;
    AGETextCtrl *Units_IconID;
    AGETextCtrl *Units_HideInEditor;
    CheckBox_2State *Units_HideInEditor_CheckBox;
    AGETextCtrl *Units_Unknown1;
    AGETextCtrl *Units_Enabled;
    CheckBox_2State *Units_Enabled_CheckBox;
    AGETextCtrl *Units_Disabled;
    CheckBox_2State *Units_Disabled_CheckBox;
    AGETextCtrl *Units_PlacementSideTerrain[2];
    ComboBox_Plus1 *Units_PlacementSideTerrain_ComboBox[2];
    AGETextCtrl *Units_PlacementTerrain[2];
    ComboBox_Plus1 *Units_PlacementTerrain_ComboBox[2];
    AGETextCtrl *Units_ClearanceSize[2];
    AGETextCtrl *Units_HillMode;
    AGETextCtrl *Units_VisibleInFog;
    SolidText *Units_VisibleInFog_Text;
    AGETextCtrl *Units_TerrainRestriction;
    ComboBox_Plus1 *Units_TerrainRestriction_ComboBox;
    AGETextCtrl *Units_FlyMode;
    CheckBox_2State *Units_FlyMode_CheckBox;
    AGETextCtrl *Units_ResourceCapacity;
    AGETextCtrl *Units_ResourceDecay;
    AGETextCtrl *Units_BlastDefenseLevel;
    AGETextCtrl *Units_SubType;
    AGETextCtrl *Units_InteractionMode;
    AGETextCtrl *Units_MinimapMode;
    AGETextCtrl *Units_CommandID;
    AGETextCtrl *Units_Unknown3A;
    AGETextCtrl *Units_MinimapColor;
    AGETextCtrl *Units_LanguageDLLHelp;
    TextCtrl_DLL *Units_DLL_LanguageHelp;
    wxTextCtrl *Units_LanguageDLLConverter[2];
    AGETextCtrl *Units_LanguageDLLHotKeyText;
    TextCtrl_DLL *Units_DLL_LanguageHKText;
    AGETextCtrl *Units_HotKey;
    TextCtrl_DLL *Units_DLL_HotKey4;
    AGETextCtrl *Units_Unselectable;
    CheckBox_2State *Units_Unselectable_CheckBox;
    AGETextCtrl *Units_Unknown6;
    AGETextCtrl *Units_Unknown7;
    AGETextCtrl *Units_Unknown8;
    AGETextCtrl *Units_SelectionMask;
    AGETextCtrl *Units_SelectionShapeType;
    AGETextCtrl *Units_SelectionShape;
    AGETextCtrl *Units_Attribute;
    wxBoxSizer *Units_Attribute_Grid;
    wxCheckBox *Units_Attribute_CheckBox[8];
    AGETextCtrl *Units_Civ;
    ComboBox_Plus1 *Units_Civ_ComboBox;
    AGETextCtrl *Units_Nothing;
    AGETextCtrl *Units_SelectionEffect;
    AGETextCtrl *Units_EditorSelectionColour;
    wxBoxSizer *Units_SelectionRadiusBox;
    AGETextCtrl *Units_SelectionRadius[2];
    AGETextCtrl *Units_HPBarHeight2;
    AGETextCtrl *ResourceStorage_Type[3];
    ComboBox_Plus1 *ResourceStorage_Type_ComboBox[3];
    AGETextCtrl *ResourceStorage_Amount[3];
    AGETextCtrl *ResourceStorage_Enabled[3];
    AGETextCtrl *Units_SelectionSound;
    ComboBox_Plus1 *Units_SelectionSound_ComboBox;
    AGETextCtrl *Units_DyingSound;
    ComboBox_Plus1 *Units_DyingSound_ComboBox;
    AGETextCtrl *Units_AttackMode;
    AGETextCtrl *Units_Unknown10;
    AGETextCtrl *Units_Name;
    AGETextCtrl *Units_Name2;
    AGETextCtrl *Units_Unitline;
    ComboBox_Plus1 *Units_Unitline_ComboBox;
    AGETextCtrl *Units_MinTechLevel;
    ComboBox_Plus1 *Units_MinTechLevel_ComboBox;
    AGETextCtrl *Units_ID2;
    AGETextCtrl *Units_ID3;

//  Type 20+

    AGETextCtrl *Units_Speed;

//  Type 30+

    AGETextCtrl *Units_WalkingGraphic[2];
    ComboBox_Plus1 *Units_WalkingGraphic_ComboBox[2];
    AGETextCtrl *Units_RotationSpeed;
    AGETextCtrl *Units_Unknown11;
    AGETextCtrl *Units_TrackingUnit;
    ComboBox_Plus1 *Units_TrackingUnit_ComboBox;
    AGETextCtrl *Units_TrackingUnitUsed;
    AGETextCtrl *Units_TrackingUnitDensity;
    AGETextCtrl *Units_Unknown16;
    array<AGETextCtrl*, 5> Units_RotationAngles;

//  Type 40+

    SolidText *Units_ActionWhenDiscoveredID_Text;
    AGETextCtrl *Units_ActionWhenDiscoveredID;
    ComboBox_Plus1 *Units_ActionWhenDiscoveredID_ComboBox;
    AGETextCtrl *Units_SearchRadius;
    AGETextCtrl *Units_WorkRate;
    AGETextCtrl *Units_DropSite[2];
    ComboBox_Plus1 *Units_DropSite_ComboBox[2];
    AGETextCtrl *Units_TaskSwapID;
    AGETextCtrl *Units_AttackSound;
    ComboBox_Plus1 *Units_AttackSound_ComboBox;
    AGETextCtrl *Units_MoveSound;
    ComboBox_Plus1 *Units_MoveSound_ComboBox;
    AGETextCtrl *Units_AnimalMode;
    CheckBox_2State *Units_AnimalMode_CheckBox;
    AGETextCtrl *Units_Exists;

//  Type 50+

    AGETextCtrl *Units_DefaultArmor;
    AGETextCtrl *Units_TerRestrictionForDmgMultiply;
    ComboBox_Plus1 *Units_TerRestrictionForDmgMultiply_ComboBox;
    AGETextCtrl *Units_MaxRange;
    AGETextCtrl *Units_BlastWidth;
    AGETextCtrl *Units_ReloadTime1;
    AGETextCtrl *Units_ProjectileUnitID;
    ComboBox_Plus1 *Units_ProjectileUnitID_ComboBox;
    AGETextCtrl *Units_AccuracyPercent;
    AGETextCtrl *Units_TowerMode;
    CheckBox_2State *Units_TowerMode_CheckBox;
    AGETextCtrl *Units_Delay;
    AGETextCtrl *Units_GraphicDisplacement[3];
    AGETextCtrl *Units_BlastAttackLevel;
    AGETextCtrl *Units_MinRange;
    AGETextCtrl *Units_AccuracyDispersion;
    AGETextCtrl *Units_AttackGraphic;
    ComboBox_Plus1 *Units_AttackGraphic_ComboBox;
    AGETextCtrl *Units_DisplayedMeleeArmour;
    AGETextCtrl *Units_DisplayedAttack;
    AGETextCtrl *Units_DisplayedRange;
    AGETextCtrl *Units_ReloadTime2;

//  Type 60 only

    AGETextCtrl *Units_StretchMode;
    AGETextCtrl *Units_SmartMode;
    AGETextCtrl *Units_DropAnimationMode;
    AGETextCtrl *Units_PenetrationMode;
    AGETextCtrl *Units_Unknown24;
    AGETextCtrl *Units_ProjectileArc;

//  Type 70+

    AGETextCtrl *Units_CostType[3];
    ComboBox_Plus1 *Units_CostType_ComboBox[3];
    AGETextCtrl *Units_CostAmount[3];
    AGETextCtrl *Units_CostUsed[3];
    CheckBox_2State *Units_CostUsed_CheckBox[3];
    AGETextCtrl *Units_TrainTime;
    AGETextCtrl *Units_TrainLocationID;
    ComboBox_Plus1 *Units_TrainLocationID_ComboBox;
    AGETextCtrl *Units_ButtonID;
    AGETextCtrl *Units_Unknown26;
    AGETextCtrl *Units_Unknown27;
    AGETextCtrl *Units_UnknownType;
    AGETextCtrl *Units_HeroMode;
    CheckBox_2State *Units_HeroMode_CheckBox;
    AGETextCtrl *Units_GarrisonGraphic;
    ComboBox_Plus1 *Units_GarrisonGraphic_ComboBox;
    AGETextCtrl *Units_MissileCount;
    AGETextCtrl *Units_MissileDuplicationCount;
    AGETextCtrl *Units_AttackMissileDuplicationSpawning[3];
    AGETextCtrl *Units_AttackMissileDuplicationUnit;
    ComboBox_Plus1 *Units_AttackMissileDuplicationUnit_ComboBox;
    AGETextCtrl *Units_ChargingGraphic;
    ComboBox_Plus1 *Units_ChargingGraphic_ComboBox;
    AGETextCtrl *Units_ChargingMode;
    AGETextCtrl *Units_DisplayedPierceArmour;

//  Type 80

    AGETextCtrl *Units_ConstructionGraphicID;
    ComboBox_Plus1 *Units_ConstructionGraphicID_ComboBox;
    AGETextCtrl *Units_SnowGraphicID;
    ComboBox_Plus1 *Units_SnowGraphicID_ComboBox;
    AGETextCtrl *Units_AdjacentMode;
    CheckBox_2State *Units_AdjacentMode_CheckBox;
    AGETextCtrl *Units_IconAngle;
    AGETextCtrl *Units_DisappearsWhenBuilt;
    CheckBox_2State *Units_Unknown31b_CheckBox;
    AGETextCtrl *Units_StackUnitID;
    ComboBox_Plus1 *Units_StackUnitID_ComboBox;
    AGETextCtrl *Units_TerrainID;
    ComboBox_Plus1 *Units_TerrainID_ComboBox;
    AGETextCtrl *Units_OldTerrainLikeID;
    AGETextCtrl *Units_ResearchID;
    ComboBox_Plus1 *Units_ResearchID_ComboBox;
    AGETextCtrl *Units_Unknown33;
    AGETextCtrl *Units_AnnexUnit[4];
    ComboBox_Plus1 *Units_AnnexUnit_ComboBox[4];
    AGETextCtrl *Units_AnnexUnitMisplacement[4][2];
    AGETextCtrl *Units_HeadUnit;
    ComboBox_Plus1 *Units_HeadUnit_ComboBox;
    AGETextCtrl *Units_TransformUnit;
    ComboBox_Plus1 *Units_TransformUnit_ComboBox;
    AGETextCtrl *Units_UnknownSound;
    ComboBox_Plus1 *Units_UnknownSound_ComboBox;
    AGETextCtrl *Units_ConstructionSound;
    ComboBox_Plus1 *Units_ConstructionSound_ComboBox;
    AGETextCtrl *Units_GarrisonType;
    wxBoxSizer *Units_GarrisonType_Grid;
    wxCheckBox *Units_GarrisonType_CheckBox[8];
    AGETextCtrl *Units_GarrisonHealRate;
    AGETextCtrl *Units_Unknown35;
    AGETextCtrl *Units_PileUnit;
    ComboBox_Plus1 *Units_PileUnit_ComboBox;
    array<AGETextCtrl*, 6> Units_LootSwitch;

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
    SolidText *Units_TrainSound_Text;
    SolidText *Units_DeadUnitID_Text;
    SolidText *Units_PlacementMode_Text;
    SolidText *Units_IconID_Text;
    SolidText *Units_Unknown1_Text;
    SolidText *Units_PlacementSideTerrain_Text;
    SolidText *Units_PlacementTerrain_Text;
    SolidText *Units_ClearanceSize_Text;
    SolidText *Units_HillMode_Text;
    SolidText *Units_TerrainRestriction_Text;
    SolidText *Units_ResourceCapacity_Text;
    SolidText *Units_ResourceDecay_Text;
    SolidText *Units_BlastDefenseLevel_Text;
    SolidText *Units_SubType_Text;
    SolidText *Units_InteractionMode_Text;
    SolidText *Units_MinimapMode_Text;
    SolidText *Units_CommandID_Text;
    SolidText *Units_Unknown3A_Text;
    SolidText *Units_MinimapColor_Text;
    SolidText *Units_LanguageDLLHelp_Text;
    SolidText *Units_LanguageDLLConverter_Text[2];
    SolidText *Units_LanguageDLLHotKeyText_Text;
    SolidText *Units_HotKey_Text;
    SolidText *Units_Unknown6_Text;
    SolidText *Units_Unknown7_Text;
    SolidText *Units_Unknown8_Text;
    SolidText *Units_SelectionMask_Text;
    SolidText *Units_SelectionShapeType_Text;
    SolidText *Units_SelectionShape_Text;
    SolidText *Units_Attribute_Text;
    SolidText *Units_Civ_Text;
    SolidText *Units_Nothing_Text;
    SolidText *Units_SelectionEffect_Text;
    SolidText *Units_EditorSelectionColour_Text;
    SolidText *Units_SelectionRadius_Text;
    SolidText *ResourceStorage_Type_Text;
    SolidText *ResourceStorage_Amount_Text;
    SolidText *ResourceStorage_Enabled_Text;
    SolidText *Units_SelectionSound_Text;
    SolidText *Units_DyingSound_Text;
    SolidText *Units_AttackMode_Text;
    SolidText *Units_Unknown10_Text;
    SolidText *Units_Name_Text;
    SolidText *Units_Name2_Text;
    SolidText *Units_Unitline_Text;
    SolidText *Units_MinTechLevel_Text;
    SolidText *Units_ID2_Text;
    SolidText *Units_ID3_Text;

//  Type 20+

    SolidText *Units_Speed_Text;

//  Type 30+

    SolidText *Units_WalkingGraphic_Text;
    SolidText *Units_RotationSpeed_Text;
    SolidText *Units_Unknown11_Text;
    SolidText *Units_TrackingUnit_Text;
    SolidText *Units_TrackingUnitUsed_Text;
    SolidText *Units_TrackingUnitDensity_Text;
    SolidText *Units_Unknown16_Text;
    SolidText *Units_RotationAngles_Text;
    wxString Units_RotationAngles_Label;

//  Type 40+

    SolidText *Units_SearchRadius_Text;
    SolidText *Units_WorkRate_Text;
    SolidText *Units_DropSite_Text;
    SolidText *Units_TaskSwapID_Text;
    SolidText *Units_AttackSound_Text;
    SolidText *Units_MoveSound_Text;
    SolidText *Units_Exists_Text;

//  Type 50+

    SolidText *Units_DefaultArmor_Text;
    SolidText *Units_TerRestrictionForDmgMultiply_Text;
    SolidText *Units_MaxRange_Text;
    SolidText *Units_BlastWidth_Text;
    SolidText *Units_ReloadTime1_Text;
    SolidText *Units_ProjectileUnitID_Text;
    SolidText *Units_AccuracyPercent_Text;
    SolidText *Units_Delay_Text;
    SolidText *Units_GraphicDisplacement_Text;
    SolidText *Units_BlastAttackLevel_Text;
    SolidText *Units_MinRange_Text;
    SolidText *Units_AccuracyDispersion_Text;
    SolidText *Units_AttackGraphic_Text;
    SolidText *Units_DisplayedMeleeArmour_Text;
    SolidText *Units_DisplayedAttack_Text;
    SolidText *Units_DisplayedRange_Text;
    SolidText *Units_ReloadTime2_Text;

//  Type 60 only

    SolidText *Units_StretchMode_Text;
    SolidText *Units_SmartMode_Text;
    SolidText *Units_DropAnimationMode_Text;
    SolidText *Units_PenetrationMode_Text;
    SolidText *Units_Unknown24_Text;
    SolidText *Units_ProjectileArc_Text;

//  Type 70+

    SolidText *Units_CostType_Text;
    SolidText *Units_CostAmount_Text;
    SolidText *Units_CostUsed_Text;
    SolidText *Units_TrainTime_Text;
    SolidText *Units_TrainLocationID_Text;
    SolidText *Units_ButtonID_Text;
    SolidText *Units_Unknown26_Text;
    SolidText *Units_Unknown27_Text;
    SolidText *Units_UnknownType_Text;
    SolidText *Units_GarrisonGraphic_Text;
    SolidText *Units_MissileCount_Text;
    SolidText *Units_MissileDuplicationCount_Text;
    SolidText *Units_AttackMissileDuplicationSpawning_Text;
    SolidText *Units_AttackMissileDuplicationUnit_Text;
    SolidText *Units_ChargingGraphic_Text;
    SolidText *Units_ChargingMode_Text;
    SolidText *Units_DisplayedPierceArmour_Text;

//  Type 80

    SolidText *Units_ConstructionGraphicID_Text;
    SolidText *Units_SnowGraphicID_Text;
    SolidText *Units_IconAngle_Text;
    SolidText *Units_StackUnitID_Text;
    SolidText *Units_TerrainID_Text;
    SolidText *Units_OldTerrainLikeID_Text;
    SolidText *Units_ResearchID_Text;
    SolidText *Units_Unknown33_Text;
    SolidText *Units_AnnexUnit_Text;
    SolidText *Units_AnnexUnitMisplacement_Text;
    SolidText *Units_HeadUnit_Text;
    SolidText *Units_TransformUnit_Text;
    SolidText *Units_UnknownSound_Text;
    SolidText *Units_ConstructionSound_Text;
    SolidText *Units_GarrisonType_Text;
    SolidText *Units_GarrisonHealRate_Text;
    SolidText *Units_Unknown35_Text;
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
    wxBoxSizer *Units_DeathMode_Holder;
    wxBoxSizer *Units_HitPoints_Holder;
    wxBoxSizer *Units_LineOfSight_Holder;
    wxBoxSizer *Units_GarrisonCapacity_Holder;
    wxBoxSizer *Units_SizeRadius_Holder;
    wxBoxSizer *Units_SizeRadius_Grid;
    wxBoxSizer *Units_TrainSound_Holder;
    wxBoxSizer *Units_TrainSound1_Holder;
    wxBoxSizer *Units_TrainSound2_Holder;
    wxBoxSizer *Units_TrainSound3_Holder;
    wxBoxSizer *Units_DeadUnitID_Holder;
    wxBoxSizer *Units_PlacementMode_Holder;
    wxBoxSizer *Units_AirMode_Holder;
    wxBoxSizer *Units_IconID_Holder;
    APanel *Units_IconID_SLP;
    wxBoxSizer *Units_HideInEditor_Holder;
    wxBoxSizer *Units_Unknown1_Holder;
    wxBoxSizer *Units_Enabled_Holder;
    wxBoxSizer *Units_Disabled_Holder;
    wxBoxSizer *Units_PlacementSideTerrain_Holder;
    wxGridSizer *Units_PlacementSideTerrainGrid_Holder;
    wxBoxSizer *Units_PlacementTerrain_Holder;
    wxGridSizer *Units_PlacementTerrainGrid_Holder;
    wxBoxSizer *Units_ClearanceSize_Holder;
    wxBoxSizer *Units_ClearanceSize_Grid;
    wxBoxSizer *Units_HillMode_Holder;
    wxBoxSizer *Units_VisibleInFog_Holder;
    wxBoxSizer *Units_TerrainRestriction_Holder;
    wxBoxSizer *Units_FlyMode_Holder;
    wxBoxSizer *Units_ResourceCapacity_Holder;
    wxBoxSizer *Units_ResourceDecay_Holder;
    wxBoxSizer *Units_BlastDefenseLevel_Holder;
    wxBoxSizer *Units_SubType_Holder;
    wxBoxSizer *Units_InteractionMode_Holder;
    wxBoxSizer *Units_MinimapMode_Holder;
    wxBoxSizer *Units_CommandID_Holder;
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
    wxBoxSizer *Units_Nothing_Holder;
    wxBoxSizer *Units_SelectionEffect_Holder;
    wxBoxSizer *Units_EditorSelectionColour_Holder;
    wxBoxSizer *Units_SelectionRadius_Holder;
    wxStaticBoxSizer *Units_ResourceStorageHeader_Holder;
    wxBoxSizer* Units_ResourceStorage_Texts;
    array<wxBoxSizer*, 3> Units_ResourceStorage_Holder;
    wxBoxSizer *Units_SelectionSound_Holder;
    wxBoxSizer *Units_DyingSound_Holder;
    wxBoxSizer *Units_AttackMode_Holder;
    wxBoxSizer *Units_Unknown10_Holder;
    wxBoxSizer *Units_Name_Holder;
    wxBoxSizer *Units_Name2_Holder;
    wxBoxSizer *Units_Unitline_Holder;
    wxBoxSizer *Units_MinTechLevel_Holder;
    wxBoxSizer *Units_ID2_Holder;
    wxBoxSizer *Units_ID3_Holder;

//  Type 20+

    wxBoxSizer *Units_Speed_Holder;

//  Type 30+

    wxBoxSizer *Units_WalkingGraphic_Holder;
    wxGridSizer *Units_WalkingGraphic_Grid;
    wxBoxSizer *Units_RotationSpeed_Holder;
    wxBoxSizer *Units_Unknown11_Holder;
    wxBoxSizer *Units_TrackingUnit_Holder;
    wxBoxSizer *Units_TrackingUnitUsed_Holder;
    wxBoxSizer *Units_TrackingUnitUsedBox_Holder;
    wxBoxSizer *Units_TrackingUnitDensity_Holder;
    wxBoxSizer *Units_Unknown16_Holder;
    wxBoxSizer *Units_RotationAngles_Holder;
    wxBoxSizer *Units_RotationAngles_Grid;

//  Type 40+

    wxBoxSizer *Units_ActionWhenDiscoveredID_Holder;
    wxBoxSizer *Units_SearchRadius_Holder;
    wxBoxSizer *Units_WorkRate_Holder;
    wxGridSizer *Units_DropSite_Grid;
    wxBoxSizer *Units_TaskSwapID_Holder;
    wxBoxSizer *Units_AttackSound_Holder;
    wxBoxSizer *Units_MoveSound_Holder;
    wxBoxSizer *Units_AnimalMode_Holder;
    wxBoxSizer *Units_Exists_Holder;

//  Type 50+

    wxBoxSizer *Units_DefaultArmor_Holder;
    wxBoxSizer *Units_TerRestrictionForDmgMultiply_Holder;
    wxBoxSizer *Units_MaxRange_Holder;
    wxBoxSizer *Units_BlastWidth_Holder;
    wxBoxSizer *Units_ReloadTime1_Holder;
    wxBoxSizer *Units_ProjectileUnitID_Holder;
    wxBoxSizer *Units_AccuracyPercent_Holder;
    wxBoxSizer *Units_TowerMode_Holder;
    wxBoxSizer *Units_Delay_Holder;
    wxBoxSizer *Units_GraphicDisplacement_Holder;
    wxBoxSizer *Units_GraphicDisplacement_Grid;
    wxBoxSizer *Units_BlastAttackLevel_Holder;
    wxBoxSizer *Units_MinRange_Holder;
    wxBoxSizer *Units_AccuracyDispersion_Holder;
    wxBoxSizer *Units_AttackGraphic_Holder;
    wxBoxSizer *Units_DisplayedMeleeArmour_Holder;
    wxBoxSizer *Units_DisplayedAttack_Holder;
    wxBoxSizer *Units_DisplayedRange_Holder;
    wxBoxSizer *Units_ReloadTime2_Holder;

//  Type 60 only

    wxBoxSizer *Units_StretchMode_Holder;
    wxBoxSizer *Units_SmartMode_Holder;
    wxBoxSizer *Units_DropAnimationMode_Holder;
    wxBoxSizer *Units_PenetrationMode_Holder;
    wxBoxSizer *Units_Unknown24_Holder;
    wxBoxSizer *Units_ProjectileArc_Holder;

//  Type 70+

    wxStaticBoxSizer *Units_CostHeader_Holder;
    wxBoxSizer *Unit_Cost_Texts;
    array<wxBoxSizer*, 3> Unit_Cost_Sizers;
    wxBoxSizer *Units_TrainTime_Holder;
    wxBoxSizer *Units_TrainLocationID_Holder;
    wxBoxSizer *Units_ButtonID_Holder;
    wxBoxSizer *Units_Unknown26_Holder;
    wxBoxSizer *Units_Unknown27_Holder;
    wxBoxSizer *Units_UnknownType_Holder;
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

//  Type 80

    wxBoxSizer *Units_ConstructionGraphicID_Holder;
    wxBoxSizer *Units_SnowGraphicID_Holder;
    wxBoxSizer *Units_AdjacentMode_Holder;
    wxBoxSizer *Units_IconAngle_Holder;
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

//  Unit Controls SubControls

    wxBoxSizer *Units_DamageGraphics_Holder_Data;
    AGETextCtrl *DamageGraphics_GraphicID;
    ComboBox_Plus1 *DamageGraphics_GraphicID_ComboBox;
    AGETextCtrl *DamageGraphics_DamagePercent;
    AGETextCtrl *DamageGraphics_ApplyMode;
    AGETextCtrl *DamageGraphics_Unknown2;
    SolidText *DamageGraphics_GraphicID_Text;
    SolidText *DamageGraphics_DamagePercent_Text;
    SolidText *DamageGraphics_ApplyMode_Text;
    SolidText *DamageGraphics_Unknown2_Text;
    wxBoxSizer *DamageGraphics_GraphicID_Holder;
    wxBoxSizer *DamageGraphics_DamagePercent_Holder;
    wxBoxSizer *DamageGraphics_ApplyMode_Holder;
    wxBoxSizer *DamageGraphics_Unknown2_Holder;
    wxStaticBoxSizer *Units_DamageGraphics;
    wxBoxSizer *Units_DamageGraphics_ListArea;
    wxTextCtrl *Units_DamageGraphics_Search;
    wxTextCtrl *Units_DamageGraphics_Search_R;
    AGEListView *Units_DamageGraphics_ListV;
    wxGridSizer *Units_DamageGraphics_Buttons;
    wxButton *Units_DamageGraphics_Add;
    wxButton *Units_DamageGraphics_Insert;
    wxButton *Units_DamageGraphics_Delete;
    wxButton *Units_DamageGraphics_Copy;
    wxButton *Units_DamageGraphics_Paste;
    wxButton *Units_DamageGraphics_PasteInsert;
    wxButton *Units_DamageGraphics_CopyToUnits;

    wxBoxSizer *Units_Attacks_Holder;
    wxGridSizer *Units_Attacks_Holder_Data;
    AGETextCtrl *Attacks_Class;
    ComboBox_Plus1 *Attacks_Class_ComboBox[2];
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
    AGEListView *Units_Attacks_ListV;
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
    AGEListView *Units_Armors_ListV;
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
    AGEListView *Units_ListV;
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

    vector<AGETextCtrl*> uiGroupUnit, uiGroupUnitDmgGraphic, uiGroupUnitCommand;
    wxBoxSizer *Units_ScrollSpace;
    wxStaticBoxSizer *Units_Identity_Holder;
    wxBoxSizer *Units_TypeArea_Holder;
    wxStaticBoxSizer *Units_LangDLLArea_Holder;
    wxStaticBoxSizer *Units_GraphicsArea_Holder;
    wxBoxSizer *Units_GraphicsArea1_Holder;
    wxBoxSizer *Units_GraphicsArea4_Holder;
    wxBoxSizer *Units_GraphicsArea5_Holder;
    wxStaticBoxSizer *Units_StatsArea_Holder;
    wxBoxSizer *Units_StatsArea1A_Sizer;
    wxBoxSizer *Units_StatsArea1B_Sizer;
    wxBoxSizer *Units_StatsAreaGarrison_Grid;
    wxBoxSizer *Units_StatsArea2_Grid;
    wxStaticBoxSizer *Units_ProjectileArea_Holder;
    wxBoxSizer *Units_P1, *Units_P2, *Units_P3;
    wxStaticBoxSizer *Units_Attributes_Holder;
    wxBoxSizer *Units_A1_Grid, *Units_A2_Grid, *Units_A3_Grid, *Units_A4_Grid, *Units_A6_Grid, *Units_AS_Holder, *Units_AS1_Grid;
    wxGridSizer *Units_A5_Grid, *Units_AM1_Grid, *Units_AB1_Grid;
    wxBoxSizer *Units_LangRegular_Holder;
    wxBoxSizer *Units_LangHotKey_Holder;
    wxBoxSizer *Units_AttributesTracking_Grid;
    wxBoxSizer *Units_AttributesTrain1_Grid;
    wxStaticBoxSizer *Units_SoundsArea_Holder;
    wxBoxSizer *Units_SoundsArea1_Holder;
    wxBoxSizer *Units_SoundsArea2_Grid;
    wxGridSizer *Units_UnknownArea_Holder;
    wxStaticBoxSizer *Units_Type10plusUnknownArea_Holder;
    wxStaticBoxSizer *Units_Type30plusUnknownArea_Holder;
    wxStaticBoxSizer *Units_Type70plusUnknownArea_Holder;
    wxStaticBoxSizer *Units_Type80plusUnknownArea_Holder;
    wxStaticBoxSizer *Units_CommandsArea_Holder;
    wxBoxSizer *Units_Top_Holder;
    wxWrapSizer *Units_TopGrid_Holder;
    vector<wxCheckBox*> Units_CivBoxes;
    //vector<SolidText*> Units_CivLabels;
    wxButton *Units_CopyTo;
    wxCheckBox *Units_CopyGraphics;
    wxCheckBox *Units_AutoCopy;
    SolidText *Units_CopyToText;
    SolidText *Units_GraphicSetText;
    AGEComboBox *Units_GraphicSet;
    wxButton *Units_SelectAll;
    wxButton *Units_SelectClear;

//  Unit Attributes section

    wxBoxSizer *Units_CommandHolder_Lists;
    SolidText *Units_UnitHeads_Name;

    wxTextCtrl *Units_UnitCommands_Search;
    wxTextCtrl *Units_UnitCommands_Search_R;
    AGEListView *Units_UnitCommands_ListV;
    wxGridSizer *Units_UnitCommands_Buttons;
    wxButton *Units_UnitCommands_Add;
    wxButton *Units_UnitCommands_Insert;
    wxButton *Units_UnitCommands_Delete;
    wxButton *Units_UnitCommands_Copy;
    wxButton *Units_UnitCommands_Paste;
    wxButton *Units_UnitCommands_PasteInsert;
    wxButton *Units_UnitCommands_CopyToUnits;

    wxBoxSizer *Units_CommandHolder_Data;
    wxBoxSizer *Unit_Command_Known1, *Unit_Command_Known3;
    wxGridSizer *Unit_Command_Known2, *Unit_Command_Known4, *Unit_Command_Unknowns;
    wxBoxSizer *UnitCommands_One_Holder;
    wxBoxSizer *UnitCommands_ID_Holder;
    wxBoxSizer *UnitCommands_Unknown1_Holder;
    wxBoxSizer *UnitCommands_Type_Holder;
    wxBoxSizer *UnitCommands_ProductivityResource_Holder;
    wxBoxSizer *UnitCommands_ClassID_Holder;
    wxBoxSizer *UnitCommands_UnitID_Holder;
    wxBoxSizer *UnitCommands_TerrainID_Holder;
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
    wxBoxSizer *UnitCommands_RightClickMode_Holder;
    wxBoxSizer *UnitCommands_Unknown12_Holder;
    array<wxBoxSizer*, 6> UnitCommands_Graphics_Holder;

    SolidText *UnitCommands_One_Text;
    SolidText *UnitCommands_ID_Text;
    SolidText *UnitCommands_Unknown1_Text;
    SolidText *UnitCommands_Type_Text;
    SolidText *UnitCommands_ClassID_Text;
    SolidText *UnitCommands_UnitID_Text;
    SolidText *UnitCommands_TerrainID_Text;
    SolidText *UnitCommands_ResourceIn_Text;
    SolidText *UnitCommands_ProductivityResource_Text;
    SolidText *UnitCommands_ResourceOut_Text;
    SolidText *UnitCommands_Resource_Text;
    SolidText *UnitCommands_WorkRateMultiplier_Text;
    SolidText *UnitCommands_ExecutionRadius_Text;
    SolidText *UnitCommands_ExtraRange_Text;
    SolidText *UnitCommands_Unknown4_Text;
    SolidText *UnitCommands_Unknown5_Text;
    SolidText *UnitCommands_SelectionEnabler_Text;
    SolidText *UnitCommands_Unknown7_Text;
    SolidText *UnitCommands_Unknown8_Text;
    SolidText *UnitCommands_Unknown9_Text;
    SolidText *UnitCommands_SelectionMode_Text;
    SolidText *UnitCommands_RightClickMode_Text;
    SolidText *UnitCommands_Unknown12_Text;
    array<SolidText*, 6> UnitCommands_Graphics_Text;

    AGETextCtrl *UnitCommands_One;
    AGETextCtrl *UnitCommands_ID;
    AGETextCtrl *UnitCommands_Unknown1;
    AGETextCtrl *UnitCommands_Type;
    AGEComboBox *UnitCommands_Type_ComboBox;
    AGETextCtrl *UnitCommands_ClassID;
    AGETextCtrl *UnitCommands_UnitID;
    ComboBox_Plus1 *UnitCommands_UnitID_ComboBox;
    AGETextCtrl *UnitCommands_TerrainID;
    ComboBox_Plus1 *UnitCommands_TerrainID_ComboBox;
    AGETextCtrl *UnitCommands_ResourceIn;
    ComboBox_Plus1 *UnitCommands_ResourceIn_ComboBox;
    AGETextCtrl *UnitCommands_ProductivityResource;
    ComboBox_Plus1 *UnitCommands_ProductivityResource_ComboBox;
    AGETextCtrl *UnitCommands_ResourceOut;
    ComboBox_Plus1 *UnitCommands_ResourceOut_ComboBox;
    AGETextCtrl *UnitCommands_Resource;
    ComboBox_Plus1 *UnitCommands_Resource_ComboBox;
    AGETextCtrl *UnitCommands_WorkRateMultiplier;
    AGETextCtrl *UnitCommands_ExecutionRadius;
    AGETextCtrl *UnitCommands_ExtraRange;
    AGETextCtrl *UnitCommands_Unknown4;
    AGETextCtrl *UnitCommands_Unknown5;
    AGETextCtrl *UnitCommands_SelectionEnabler;
    AGETextCtrl *UnitCommands_Unknown7;
    AGETextCtrl *UnitCommands_Unknown8;
    AGETextCtrl *UnitCommands_Unknown9;
    AGETextCtrl *UnitCommands_SelectionMode;
    AGETextCtrl *UnitCommands_RightClickMode;
    AGETextCtrl *UnitCommands_Unknown12;
    array<AGETextCtrl*, 6> UnitCommands_Graphics;
    array<ComboBox_Plus1*, 6> UnitCommands_Graphics_ComboBox;

//  Graphics user interface

    wxBoxSizer *Graphics_Main;
    wxGridSizer *Graphics_Graphics_Buttons;
    wxStaticBoxSizer *Graphics_Graphics;
    wxBoxSizer *Graphics_Graphics_Searches[2];
    wxTextCtrl *Graphics_Graphics_Search;
    wxTextCtrl *Graphics_Graphics_Search_R;
    AGEComboBox *Graphics_SearchFilters[2];
    wxCheckBox *Graphics_Graphics_UseAnd[2];
    AGEListView *Graphics_Graphics_ListV;
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

    wxScrolled<APanel> *Graphics_Scroller;
    wxBoxSizer *Graphics_ScrollSpace;

    vector<AGETextCtrl*> uiGroupGraphic, uiGroupGraphicDelta, uiGroupGraphicSound;
    wxBoxSizer *Graphics_NameArea_Holder;
    wxBoxSizer *Graphics_Name_Holder;
    wxBoxSizer *Graphics_Name2_Holder;
    wxBoxSizer *Graphics_SLP_Holder;
    wxBoxSizer *Graphics_Loaded_Holder;
    wxBoxSizer *Graphics_ColorFlag_Holder;
    wxBoxSizer *Graphics_FrameType_Holder;
    wxBoxSizer *Graphics_PlayerColor_Holder;
    wxBoxSizer *Graphics_Rainbow_Holder;
    wxBoxSizer *Graphics_TransparentPicking_Holder;
    wxBoxSizer *Graphics_Coordinates_Holder;
    wxBoxSizer *Graphics_CoordinateGrid_Holder;
    wxBoxSizer *Graphics_SoundID_Holder;
    wxBoxSizer *Graphics_AttackSoundUsed_Holder;
    wxBoxSizer *Graphics_AttackSoundUsed1_Holder;
    wxBoxSizer *Graphics_4_Holder;
    wxBoxSizer *Graphics_5_Holder;
    wxBoxSizer *Graphics_FrameCount_Holder;
    wxBoxSizer *Graphics_AngleCount_Holder;
    wxBoxSizer *Graphics_NewSpeed_Holder;
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
    SolidText *Graphics_Name2_Text;
    SolidText *Graphics_SLP_Text;
    SolidText *Graphics_Loaded_Text;
    SolidText *Graphics_ColorFlag_Text;
    SolidText *Graphics_FrameType_Text;
    SolidText *Graphics_PlayerColor_Text;
    SolidText *Graphics_Rainbow_Text;
    SolidText *Graphics_TransparentPicking_Text;
    SolidText *Graphics_Coordinates_Text;
    SolidText *Graphics_SoundID_Text;
    SolidText *Graphics_AttackSoundUsed_Text;
    SolidText *Graphics_FrameCount_Text;
    SolidText *Graphics_AngleCount_Text;
    SolidText *Graphics_NewSpeed_Text;
    SolidText *Graphics_FrameDuration_Text;
    SolidText *Graphics_ReplayDelay_Text;
    SolidText *Graphics_SequenceType_Text;
    SolidText *Graphics_ID_Text;
    SolidText *Graphics_Type_Text;
    SolidText *Graphics_EditorFlag_Text;

    AGETextCtrl *Graphics_Name;
    AGETextCtrl *Graphics_Name2;
    AGETextCtrl *Graphics_SLP;
    AGETextCtrl *Graphics_Loaded;
    AGETextCtrl *Graphics_ColorFlag;
    AGETextCtrl *Graphics_FrameType;
    AGETextCtrl *Graphics_PlayerColor;
    ComboBox_Plus1 *Graphics_PlayerColor_ComboBox;
    AGETextCtrl *Graphics_Rainbow;
    AGETextCtrl *Graphics_TransparentPicking;
    AGETextCtrl *Graphics_Coordinates[4];
    AGETextCtrl *Graphics_SoundID;
    ComboBox_Plus1 *Graphics_SoundID_ComboBox;
    AGETextCtrl *Graphics_AttackSoundUsed;
    CheckBox_2State *Graphics_AttackSoundUsed_CheckBox;
    AGETextCtrl *Graphics_FrameCount;
    AGETextCtrl *Graphics_AngleCount;
    AGETextCtrl *Graphics_NewSpeed;
    AGETextCtrl *Graphics_FrameDuration;
    AGETextCtrl *Graphics_ReplayDelay;
    AGETextCtrl *Graphics_SequenceType;
    AGETextCtrl *Graphics_ID;
    AGETextCtrl *Graphics_MirroringMode;
    AGETextCtrl *Graphics_EditorFlag;

    wxBoxSizer *Graphics_Deltas;
    wxTextCtrl *Graphics_Deltas_Search;
    wxTextCtrl *Graphics_Deltas_Search_R;
    AGEListView *Graphics_Deltas_ListV;
    wxGridSizer *Graphics_Deltas_Buttons;
    wxButton *Deltas_Add;
    wxButton *Deltas_Insert;
    wxButton *Deltas_Delete;
    wxButton *Deltas_Copy;
    wxButton *Deltas_Paste;
    wxButton *Deltas_PasteInsert;
    wxButton *Deltas_CopyToGraphics;
    wxBoxSizer *Graphics_AttackSounds;
    AGEListView *Graphics_AttackSounds_ListV;
    wxButton *AttackSounds_Copy;
    wxButton *AttackSounds_CopyToGraphics;

    wxStaticBoxSizer *Graphics_Deltas_Holder;
    wxBoxSizer *Graphics_Deltas_Holder_Data;
    wxBoxSizer *Deltas_Holder;
    wxBoxSizer *Deltas_Unknowns_Holder;
    wxStaticBoxSizer *Graphics_AttackSoundArea_Holder;

    wxBoxSizer *GraphicDeltas_GraphicID_Holder;
    SolidText *GraphicDeltas_GraphicID_Text;
    AGETextCtrl *GraphicDeltas_GraphicID;
    ComboBox_Plus1 *GraphicDeltas_GraphicID_ComboBox;
    wxBoxSizer *GraphicDeltas_Unknown1_Holder;
    SolidText *GraphicDeltas_Unknown1_Text;
    AGETextCtrl *GraphicDeltas_Unknown1;
    wxBoxSizer *GraphicDeltas_Unknown2_Holder;
    SolidText *GraphicDeltas_Unknown2_Text;
    AGETextCtrl *GraphicDeltas_Unknown2;
    wxBoxSizer *GraphicDeltas_Unknown3_Holder;
    SolidText *GraphicDeltas_Unknown3_Text;
    AGETextCtrl *GraphicDeltas_Unknown3;
    wxBoxSizer *GraphicDeltas_DirectionX_Holder;
    SolidText *GraphicDeltas_DirectionX_Text;
    AGETextCtrl *GraphicDeltas_DirectionX;
    wxBoxSizer *GraphicDeltas_DirectionY_Holder;
    SolidText *GraphicDeltas_DirectionY_Text;
    AGETextCtrl *GraphicDeltas_DirectionY;
    wxBoxSizer *GraphicDeltas_DisplayAngle_Holder;
    SolidText *GraphicDeltas_DisplayAngle_Text;
    AGETextCtrl *GraphicDeltas_DisplayAngle;
    wxBoxSizer *GraphicDeltas_Unknown5_Holder;
    SolidText *GraphicDeltas_Unknown5_Text;
    AGETextCtrl *GraphicDeltas_Unknown5;
    wxBoxSizer *Graphics_AttackSounds_Holder;
    SolidText *Graphics_AttackSounds_Text;
    wxBoxSizer *Graphics_AttackSoundDelays_Holder;
    SolidText *Graphics_AttackSoundDelays_Text;
    AGETextCtrl *Graphics_AttackSoundDelay[3];
    AGETextCtrl *Graphics_AttackSoundID[3];
    ComboBox_Plus1 *Graphics_AttackSoundID_ComboBox[3];

//  Terrains user interface

    vector<AGETextCtrl*> uiGroupTerrain, uiGroupBorder, uiGroupBorderFrame;
    wxBoxSizer *Terrains_Main;
    wxStaticBoxSizer *Terrains_Terrains;
    wxBoxSizer *Terrains_Terrains_Searches[2];
    wxTextCtrl *Terrains_Terrains_Search;
    wxTextCtrl *Terrains_Terrains_Search_R;
    AGEComboBox *Terrains_SearchFilters[2];
    wxCheckBox *Terrains_Terrains_UseAnd[2];
    AGEListView *Terrains_Terrains_ListV;
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
    ComboBox_Plus1 *Terrains_Border_ComboBox;
    wxStaticBoxSizer *Terrains_Borders;
    wxTextCtrl *Terrains_Borders_Search;
    wxTextCtrl *Terrains_Borders_Search_R;
    AGEListView *Terrains_Borders_ListV;
    wxGridSizer *Terrains_Borders_Buttons;
    wxButton *Terrains_Borders_Copy;
    wxButton *Terrains_Borders_Paste;
    wxButton *Terrains_Borders_CopyToTerrains;

    wxScrolled<APanel> *Terrains_Scroller;
    wxBoxSizer *Terrains_ScrollSpace;
    wxBoxSizer *Terrains_NameArea_Holder;
    wxBoxSizer *Terrains_Area1_Grid;
    wxBoxSizer *Terrains_Area2_Grid;
    wxBoxSizer *Terrains_GridX1;
    wxBoxSizer *Terrains_GridX2;
    wxBoxSizer *Terrains_Unknown1_Holder;
    SolidText *Terrains_Unknown1_Text;
    AGETextCtrl *Terrains_Unknown1;
    wxBoxSizer *Terrains_Enabled_Holder;
    wxBoxSizer *Terrains_Enabled1_Holder;
    SolidText *Terrains_Enabled_Text;
    AGETextCtrl *Terrains_Enabled;
    CheckBox_2State *Terrains_Enabled_CheckBox;
    wxBoxSizer *Terrains_Random_Holder;
    SolidText *Terrains_Random_Text;
    AGETextCtrl *Terrains_Random;
    wxBoxSizer *Terrains_Name_Holder;
    SolidText *Terrains_Name_Text;
    AGETextCtrl *Terrains_Name;
    wxBoxSizer *Terrains_Name2_Holder;
    SolidText *Terrains_Name2_Text;
    AGETextCtrl *Terrains_Name2;
    wxBoxSizer *Terrains_SLP_Holder;
    SolidText *Terrains_SLP_Text;
    AGETextCtrl *Terrains_SLP;
    wxBoxSizer *Terrains_Unknown3_Holder;
    SolidText *Terrains_Unknown3_Text;
    AGETextCtrl *Terrains_Unknown3;
    wxBoxSizer *Terrains_SoundID_Holder;
    SolidText *Terrains_SoundID_Text;
    AGETextCtrl *Terrains_SoundID;
    ComboBox_Plus1 *Terrains_SoundID_ComboBox;
    wxBoxSizer *Terrains_BlendPriority_Holder;
    SolidText *Terrains_BlendPriority_Text;
    AGETextCtrl *Terrains_BlendPriority;
    wxBoxSizer *Terrains_BlendType_Holder;
    SolidText *Terrains_BlendType_Text;
    AGETextCtrl *Terrains_BlendType;
    wxBoxSizer *Terrains_Colors_Holder;
    wxGridSizer *Terrains_Colors_Grid;
    SolidText *Terrains_Colors_Text;
    array<AGETextCtrl*, 3> Terrains_Colors;
    wxBoxSizer *Terrains_CliffColors_Holder;
    wxGridSizer *Terrains_CliffColors_Grid;
    SolidText *Terrains_CliffColors_Text;
    array<AGETextCtrl*, 2> Terrains_CliffColors;
    wxBoxSizer *Terrains_PassableTerrain_Holder;
    wxBoxSizer *Terrains_ImpassableTerrain_Holder;
    SolidText *Terrains_PassableTerrain_Text;
    SolidText *Terrains_ImpassableTerrain_Text;
    AGETextCtrl *Terrains_PassableTerrain;
    AGETextCtrl *Terrains_ImpassableTerrain;
    ComboBox_Plus1 *Terrains_PassableTerrain_ComboBox;
    ComboBox_Plus1 *Terrains_ImpassableTerrain_ComboBox;

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
    array<wxBoxSizer*, 19>Terrain_TileGraphics_Sizers;
    array<AGETextCtrl*, 57>Terrains_ElevationGraphics;
    wxBoxSizer *Terrains_TerrainReplacementID_Holder;
    SolidText *Terrains_TerrainReplacementID_Text;
    AGETextCtrl *Terrains_TerrainReplacementID;
    ComboBox_Plus1 *Terrains_TerrainReplacementID_ComboBox;
    wxBoxSizer *Terrains_TerrainDimensions_Holder;
    SolidText *Terrains_TerrainDimensions_Text;
    array<AGETextCtrl*, 2>Terrains_TerrainDimensions;
    auto static const TERRAINUNITS = 30;
    wxBoxSizer *Terrains_TerrainUnits_Holder;
    wxBoxSizer *Terrains_TerrainUnitID_Holder;
    wxBoxSizer *Terrains_TerrainUnitID_Holder1;
    SolidText *Terrains_TerrainUnitID_Text;
    array<AGETextCtrl*, TERRAINUNITS>Terrains_TerrainUnitID;
    array<ComboBox_Plus1*, TERRAINUNITS>Terrains_TerrainUnitID_ComboBox;
    wxBoxSizer *Terrains_TerrainUnitDensity_Holder;
    SolidText *Terrains_TerrainUnitDensity_Text;
    array<AGETextCtrl*, TERRAINUNITS>Terrains_TerrainUnitDensity;
    wxBoxSizer *Terrains_TerrainUnitPriority_Holder;
    SolidText *Terrains_TerrainUnitPriority_Text;
    array<AGETextCtrl*, TERRAINUNITS>Terrains_TerrainUnitPriority;
    wxBoxSizer *Terrains_UsedTerrainUnits_Holder;
    SolidText *Terrains_UsedTerrainUnits_Text;
    AGETextCtrl *Terrains_UsedTerrainUnits;

//  Terrain restrictions user interface

    wxBoxSizer *TerRestrict_Main;
    wxGridSizer *TerRestrict_TerRestrict_Buttons;
    wxStaticBoxSizer *TerRestrict_TerRestrict;
    wxTextCtrl *TerRestrict_TerRestrict_Search;
    wxTextCtrl *TerRestrict_TerRestrict_Search_R;
    AGEListView *TerRestrict_TerRestrict_ListV;
    wxButton *TerRestrict_Add;
    wxButton *TerRestrict_Insert;
    wxButton *TerRestrict_Delete;
    wxButton *TerRestrict_Copy;
    wxButton *TerRestrict_Paste;
    wxButton *TerRestrict_PasteInsert;

    vector<AGETextCtrl*> uiGroupRestriction;
    wxBoxSizer *TerRestrict_Terrains;
    wxBoxSizer *TerRestrict_DataArea;
    wxTextCtrl *TerRestrict_Terrains_Search;
    wxTextCtrl *TerRestrict_Terrains_Search_R;
//  wxCheckBox *TerRestrict_Terrains_UseAnd;
    AGEListView *TerRestrict_Terrains_ListV;
    wxGridSizer *TerRestrict_Terrains_Buttons;
    wxButton *TerRestrict_Terrains_Copy;
    wxButton *TerRestrict_Terrains_Paste;
    wxButton *TerRestrict_Terrains_PasteInsert;
    SolidText *TerRestrict_Accessible_Text;
    AGETextCtrl *TerRestrict_Accessible;
    wxBoxSizer *TerRestrict_Graphics_Holder;
    SolidText *TerRestrict_Graphics_Text[3];
    AGETextCtrl *TerRestrict_Graphics[3];
    ComboBox_Plus1 *TerRestrict_Graphics_ComboBox[3];
    SolidText *TerRestrict_Amount_Text;
    AGETextCtrl *TerRestrict_Amount;

//  Sound user interface

    wxBoxSizer *Sounds_Main;
    wxGridSizer *Sounds_Sounds_Buttons;
    wxGridSizer *Sounds_Items_Buttons;
    wxBoxSizer *Sounds_DataArea;

    wxStaticBoxSizer *Sounds_Sounds;
    wxTextCtrl *Sounds_Sounds_Search;
    wxTextCtrl *Sounds_Sounds_Search_R;
    AGEListView *Sounds_Sounds_ListV;
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
    AGEListView *Sounds_Items_ListV;
    wxButton *SoundItems_Add;
    wxButton *SoundItems_Insert;
    wxButton *SoundItems_Delete;
    wxButton *SoundItems_Copy;
    wxButton *SoundItems_Paste;
    wxButton *SoundItems_PasteInsert;
    wxButton *SoundItems_CopyToSounds;

    vector<AGETextCtrl*> uiGroupSound, uiGroupSoundFile;
    wxBoxSizer *Sounds_ID_Holder;
    SolidText *Sounds_ID_Text;
    AGETextCtrl *Sounds_ID;
    wxBoxSizer *Sounds_Unknown1_Holder;
    SolidText *Sounds_Unknown1_Text;
    AGETextCtrl *Sounds_Unknown1;
    wxBoxSizer *Sounds_Unknown2_Holder;
    SolidText *Sounds_Unknown2_Text;
    AGETextCtrl *Sounds_Unknown2;
    wxBoxSizer *SoundItems_Name_Holder;
    SolidText *SoundItems_Name_Text;
    AGETextCtrl *SoundItems_Name;
    wxBoxSizer *SoundItems_Resource_Holder;
    SolidText *SoundItems_Resource_Text;
    AGETextCtrl *SoundItems_Resource;
    wxBoxSizer *SoundItems_Probability_Holder;
    SolidText *SoundItems_Probability_Text;
    AGETextCtrl *SoundItems_Probability;
    wxBoxSizer *SoundItems_Civ_Holder;
    SolidText *SoundItems_Civ_Text;
    AGETextCtrl *SoundItems_Civ;
    ComboBox_Plus1 *SoundItems_Civ_ComboBox;
    wxBoxSizer *SoundItems_Unknown_Holder;
    SolidText *SoundItems_Unknown_Text;
    AGETextCtrl *SoundItems_Unknown;
    wxButton *SoundFile_Play;
    wxCheckBox *SoundFile_Loop;
    wxButton *SoundFile_Stop;
    wxButton *SoundFile_AutoProbability;
    wxButton *SoundFile_AutoIncrement;
    wxButton *SoundFile_CopyCivToCiv;
    AGEComboBox *SoundFile_Source_Civ;
    AGEComboBox *SoundFile_Target_Civ;

    wxStaticBoxSizer *Sounds_AllItems;
    wxBoxSizer *Sounds_AllItems_Searches[2];
    wxTextCtrl *Sounds_AllItems_Search;
    wxTextCtrl *Sounds_AllItems_Search_R;
    wxCheckBox *Sounds_AllItems_UseAnd[2];
    AGEListView *Sounds_AllItems_ListV;
    wxBoxSizer *Sounds_AllItems_Buttons;
    wxButton *Sounds_AllItems_Load;
    wxButton *Sounds_AllItems_Clear;

//  Player Color user interface

    wxBoxSizer *Colors_Main;
    wxGridSizer *Colors_Colors_Buttons;
    wxStaticBoxSizer *Colors_Colors;
    wxTextCtrl *Colors_Colors_Search;
    wxTextCtrl *Colors_Colors_Search_R;
    AGEListView *Colors_Colors_ListV;
    wxButton *Colors_Add;
    wxButton *Colors_Insert;
    wxButton *Colors_Delete;
    wxButton *Colors_Copy;
    wxButton *Colors_Paste;
    wxButton *Colors_PasteInsert;

    vector<AGETextCtrl*> uiGroupColor;
    wxBoxSizer *Colors_DataArea;
    wxWrapSizer *Colors_WrapArea;
    wxBoxSizer *Colors_Name_Holder;
    wxBoxSizer *Colors_ID_Holder;
    wxBoxSizer *Colors_Palette_Holder;
    wxBoxSizer *Colors_Color_Holder;
    wxBoxSizer *Colors_MinimapColor_Holder;
    wxBoxSizer *Colors_Unknown1_Holder;
    wxBoxSizer *Colors_Unknown2_Holder;
    wxBoxSizer *Colors_Unknown3_Holder;
    wxBoxSizer *Colors_Unknown4_Holder;
    wxBoxSizer *Colors_StatisticsText_Holder;
    SolidText *Colors_Name_Text;
    SolidText *Colors_ID_Text;
    SolidText *Colors_Palette_Text;
    SolidText *Colors_Color_Text;
    SolidText *Colors_MinimapColor_Text;
    SolidText *Colors_Unknown1_Text;
    SolidText *Colors_Unknown2_Text;
    SolidText *Colors_Unknown3_Text;
    SolidText *Colors_Unknown4_Text;
    SolidText *Colors_StatisticsText_Text;
    AGETextCtrl *Colors_Name;
    AGETextCtrl *Colors_ID;
    AGETextCtrl *Colors_Palette;
    AGETextCtrl *Colors_ColorL;
    AGETextCtrl *Colors_MinimapColor;
    AGETextCtrl *Colors_Unknown1;
    AGETextCtrl *Colors_Unknown2;
    AGETextCtrl *Colors_Unknown3;
    AGETextCtrl *Colors_Unknown4;
    AGETextCtrl *Colors_StatisticsText;
    APanel *Colors_Palette_Display;

//  Unitline user interface

    wxBoxSizer *UnitLines_Main;
    wxGridSizer *UnitLines_UnitLines_Buttons;
    wxGridSizer *UnitLines_UnitLineUnits_Buttons;
    wxBoxSizer *UnitLines_DataArea;

    wxStaticBoxSizer *UnitLines_UnitLines;
    wxTextCtrl *UnitLines_UnitLines_Search;
    wxTextCtrl *UnitLines_UnitLines_Search_R;
    AGEListView *UnitLines_UnitLines_ListV;
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
    AGETextCtrl *UnitLines_Name;

    wxStaticBoxSizer *UnitLines_UnitLineUnits;
    wxTextCtrl *UnitLines_UnitLineUnits_Search;
    wxTextCtrl *UnitLines_UnitLineUnits_Search_R;
    AGEListView *UnitLines_UnitLineUnits_ListV;
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
    ComboBox_Plus1 *UnitLineUnits_ComboBox;

//  Tech Tree user interface

    wxBoxSizer *TechTrees_Main;
    wxBoxSizer *TechTrees_TabAges;
    wxBoxSizer *TechTrees_TabBuildings;
    wxBoxSizer *TechTrees_TabUnits;
    wxBoxSizer *TechTrees_TabResearches;
    wxScrolled<APanel> *TechTrees_ScrollerAges;
    wxScrolled<APanel> *TechTrees_ScrollerBuildings;
    wxScrolled<APanel> *TechTrees_ScrollerUnits;
    wxScrolled<APanel> *TechTrees_ScrollerResearches;
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
    AGEListView *TechTrees_MainList_Ages_ListV;
    AGEListView *TechTrees_MainList_Buildings_ListV;
    AGEListView *TechTrees_MainList_Units_ListV;
    AGEListView *TechTrees_MainList_Researches_ListV;
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
    wxBoxSizer *TechTrees_Ages_Unknown2_Holder;
    SolidText *TechTrees_Ages_Unknown2_Text;
    AGETextCtrl *TechTrees_Ages_Unknown2;
    wxBoxSizer *TechTrees_Ages_LineMode_Holder;
    SolidText *TechTrees_Ages_LineMode_Text;
    AGETextCtrl *TechTrees_Ages_LineMode;

    wxBoxSizer *TechTrees_Buildings_ID_Holder;
    SolidText *TechTrees_Buildings_ID_Text;
    AGETextCtrl *TechTrees_Buildings_ID;
    ComboBox_Plus1 *TechTrees_Buildings_ID_ComboBox;
    wxBoxSizer *TechTrees_Buildings_Always2_Holder;
    SolidText *TechTrees_Buildings_Always2_Text;
    AGETextCtrl *TechTrees_Buildings_Always2;

    wxBoxSizer *TechTrees_Buildings_LocationInAge_Holder;
    SolidText *TechTrees_Buildings_LocationInAge_Text;
    AGETextCtrl *TechTrees_Buildings_LocationInAge;
    wxBoxSizer *TechTrees_Buildings_LineMode_Holder;
    SolidText *TechTrees_Buildings_LineMode_Text;
    AGETextCtrl *TechTrees_Buildings_LineMode;
    wxBoxSizer *TechTrees_Buildings_EnablingResearch_Holder;
    SolidText *TechTrees_Buildings_EnablingResearch_Text;
    AGETextCtrl *TechTrees_Buildings_EnablingResearch;
    ComboBox_Plus1 *TechTrees_Buildings_EnablingResearch_ComboBox;
    wxStaticBoxSizer *TechTrees_Buildings_TotalUnitsTechs_Holder[2];
    AGETextCtrl *TechTrees_Buildings_TotalUnitsTechs[10];

    wxBoxSizer *TechTrees_Units_ID_Holder;
    SolidText *TechTrees_Units_ID_Text;
    AGETextCtrl *TechTrees_Units_ID;
    ComboBox_Plus1 *TechTrees_Units_ID_ComboBox;
    wxBoxSizer *TechTrees_Units_Always2_Holder;
    SolidText *TechTrees_Units_Always2_Text;
    AGETextCtrl *TechTrees_Units_Always2;
    wxBoxSizer *TechTrees_Units_UpperBuilding_Holder;
    SolidText *TechTrees_Units_UpperBuilding_Text;
    AGETextCtrl *TechTrees_Units_UpperBuilding;
    ComboBox_Plus1 *TechTrees_Units_UpperBuilding_ComboBox;

    wxBoxSizer *TechTrees_Units_VerticalLine_Holder;
    SolidText *TechTrees_Units_VerticalLine_Text;
    AGETextCtrl *TechTrees_Units_VerticalLine;

    wxBoxSizer *TechTrees_Units_LocationInAge_Holder;
    SolidText *TechTrees_Units_LocationInAge_Text;
    AGETextCtrl *TechTrees_Units_LocationInAge;
    wxBoxSizer *TechTrees_Units_RequiredResearch_Holder;
    SolidText *TechTrees_Units_RequiredResearch_Text;
    AGETextCtrl *TechTrees_Units_RequiredResearch;
    ComboBox_Plus1 *TechTrees_Units_RequiredResearch_ComboBox;
    wxBoxSizer *TechTrees_Units_LineMode_Holder;
    SolidText *TechTrees_Units_LineMode_Text;
    AGETextCtrl *TechTrees_Units_LineMode;
    wxBoxSizer *TechTrees_Units_EnablingResearch_Holder;
    SolidText *TechTrees_Units_EnablingResearch_Text;
    AGETextCtrl *TechTrees_Units_EnablingResearch;
    ComboBox_Plus1 *TechTrees_Units_EnablingResearch_ComboBox;

    wxBoxSizer *TechTrees_Researches_ID_Holder;
    SolidText *TechTrees_Researches_ID_Text;
    AGETextCtrl *TechTrees_Researches_ID;
    ComboBox_Plus1 *TechTrees_Researches_ID_ComboBox;
    wxBoxSizer *TechTrees_Researches_Always2_Holder;
    SolidText *TechTrees_Researches_Always2_Text;
    AGETextCtrl *TechTrees_Researches_Always2;
    wxBoxSizer *TechTrees_Researches_UpperBuilding_Holder;
    SolidText *TechTrees_Researches_UpperBuilding_Text;
    AGETextCtrl *TechTrees_Researches_UpperBuilding;
    ComboBox_Plus1 *TechTrees_Researches_UpperBuilding_ComboBox;

    wxBoxSizer *TechTrees_Researches_VerticalLine_Holder;
    SolidText *TechTrees_Researches_VerticalLine_Text;
    AGETextCtrl *TechTrees_Researches_VerticalLine;
    wxBoxSizer *TechTrees_Researches_LocationInAge_Holder;
    SolidText *TechTrees_Researches_LocationInAge_Text;
    AGETextCtrl *TechTrees_Researches_LocationInAge;
    wxBoxSizer *TechTrees_Researches_LineMode_Holder;
    SolidText *TechTrees_Researches_LineMode_Text;
    AGETextCtrl *TechTrees_Researches_LineMode;

//  DRS user interface

    /*genie::DrsFile *ResourceFile;

    void LoadDRSFile(wxCommandEvent &event);
    void UnLoadDRSFile(wxCommandEvent &event);
    void LoadSLP(wxCommandEvent &event);

    wxBoxSizer *DRS_Main;
    wxBoxSizer *DRS_TopRow;
    wxBoxSizer *DRS_MidArea;

    SolidText *DRS_FileLocation_Text;
    wxFilePickerCtrl *DRS_Path_FileLocation;
    wxButton *DRS_LoadButton;
    wxButton *DRS_UnLoadButton;
    wxButton *DRS_SLPLoadButton;
    SolidText *DRS_StatusText;*/

//  Template functions

    template <class P>
    inline void AddToListNoGV(P &path)
    {
        path.emplace_back();
        How2List = ADD;
    }
    template <class P>
    inline void AddToList(P &path)
    {
        path.emplace_back();
        path.back().setGameVersion(GenieVersion);
        How2List = ADD;
    }
    template <class P>
    inline void AddToListIDFix(P &path)
    {
        path.emplace_back();
        path.back().setGameVersion(GenieVersion);
        if(EnableIDFix)
        path.back().ID = path.size() - 1; // ID Fix
        How2List = ADD;
    }

    template <class P>
    inline void InsertToListNoGV(P &path, int place)
    {
        path.emplace(path.begin() + place);
        How2List = INSNEW;
    }
    template <class P>
    inline void InsertToList(P &path, int place)
    {
        path.emplace(path.begin() + place);
        path[place].setGameVersion(GenieVersion);
        How2List = INSNEW;
    }
    template <class P>
    inline void InsertToListIDFix(P &path, int place)
    {
        path.emplace(path.begin() + place);
        path[place].setGameVersion(GenieVersion);
        if(EnableIDFix)
        for(auto loop = path.size(); loop--> place;) // ID Fix
        path[loop].ID = loop;
        How2List = INSNEW;
    }

    template <class P>
    inline void DeleteFromList(P &path, vector<int> &places)
    {
        for(auto loop = places.size(); loop--> 0;)
        path.erase(path.begin() + places[loop]);
        How2List = DEL;
    }
    template <class P>
    inline void DeleteFromListIDFix(P &path, vector<int> &places)
    {
        for(auto loop = places.size(); loop--> 0;)
        path.erase(path.begin() + places[loop]);
        if(EnableIDFix)
        for(auto loop = path.size(); loop--> places.front();) // ID Fix
        path[loop].ID = loop;
        How2List = DEL;
    }

    template <class P, class C>
    inline void CopyFromList(P &path, vector<int> &places, C &copies)
    {
        copies.resize(places.size());
        for(size_t loop = 0; loop < places.size(); ++loop)
        copies[loop] = path[places[loop]];
    }

    // Common paste check
    template <class P, class C>
    inline size_t PasteCheck(P &path, vector<int> &places, C &copies, bool resize)
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
            if(resize)
            {
                if(new_size > path.size()) path.resize(new_size);
            }
            else
            {
                return copies.size() - (new_size - path.size());
            }
        }
        return copies.size();
    }

    // Combined paste
    template <class P, class C>
    inline void PasteToListNoGV(P &path, vector<int> &places, C &copies, bool resize = true)
    {
        size_t copy_cnt = PasteCheck(path, places, copies, resize);
        for(size_t loop = 0; loop < copy_cnt; ++loop)
        {
            path[Paste11 ? places[loop] : places.front() + loop] = copies[loop];
        }
        How2List = PASTE;
    }

    // Combined paste with GV
    template <class P, class C>
    inline void PasteToList(P &path, vector<int> &places, C &copies, bool resize = true)
    {
        size_t copy_cnt = PasteCheck(path, places, copies, resize);
        for(size_t loop = 0; loop < copy_cnt; ++loop)
        {
            copies[loop].setGameVersion(GenieVersion);
            path[Paste11 ? places[loop] : places.front() + loop] = copies[loop];
        }
        How2List = PASTE;
    }

    // Combined paste with ID fix
    template <class P, class C>
    inline void PasteToListIDFix(P &path, vector<int> &places, C &copies, bool resize = true)
    {
        size_t copy_cnt = PasteCheck(path, places, copies, resize);
        for(size_t loop = 0; loop < copy_cnt; ++loop)
        {
            size_t loc = Paste11 ? places[loop] : places.front() + loop;
            copies[loop].setGameVersion(GenieVersion);
            path[loc] = copies[loop];
            if(EnableIDFix)
            path[loc].ID = loc;
        }
        How2List = PASTE;
    }

    template <class P, class C>
    inline void PasteInsertToListNoGV(P &path, int place, C &copies)
    {
        path.insert(path.begin() + place, copies.begin(), copies.end());
        How2List = INSPASTE;
    }
    template <class P, class C>
    inline void PasteInsertToList(P &path, int place, C &copies)
    {
        for(auto loop = copies.size(); loop--> 0;)
        copies[loop].setGameVersion(GenieVersion);
        path.insert(path.begin() + place, copies.begin(), copies.end());
        How2List = INSPASTE;
    }
    template <class P, class C>
    inline void PasteInsertToListIDFix(P &path, int place, C &copies)
    {
        for(auto loop = copies.size(); loop--> 0;)
        copies[loop].setGameVersion(GenieVersion);
        path.insert(path.begin() + place, copies.begin(), copies.end());
        if(EnableIDFix)
        for(auto loop = path.size(); loop--> place;) // ID Fix
        path[loop].ID = loop;
        How2List = INSPASTE;
    }

protected:
    Loader *TerrainLoader;
    wxCriticalSection TerrainLoaderCS;
    friend class Loader;
    short window_num;
};
