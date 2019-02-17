#include "../AGE_Frame.h"
#include "../AppIcon32.xpm"
#include "../GateOpen.xpm"
#include "../GateClosed.xpm"
#include "../Question.xpm"
#include "../Ox.xpm"
#include "../float.xpm"
#include "../Paste.xpm"
#include "../AppIcon24.xpm"
#include "../DRSunlock.xpm"
#include "../AutoBackup.xpm"
#include "../Reselection.xpm"
//#include "genie/util/Logger.h"

std::ofstream AGE_Frame::log_out;

AGE_Frame::AGE_Frame(const wxString &title, short window, wxString aP)
: wxFrame(NULL, wxID_ANY, title), window_num(window), argPath(aP), font(GetFont())
//font(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Tahoma")
{
    {
        wxPanel model;
        //SetBackgroundStyle(wxBG_STYLE_SYSTEM);
        SetBackgroundColour(*wxYELLOW);// Hack to force the color.
        SetBackgroundColour(model.GetBackgroundColour());// Fixes most of the GUI drawing lag.
    }
    font.SetPointSize(8);
    SetIcon(wxIcon(AppIcon32_xpm));
    SetFont(font);
    wxBusyCursor WaitCursor;
    TabBar_Main = new wxNotebook(this, eTabBar);
    AGE_Frame::openEditors[window] = this;

    {
        int temp;

        ConfigPtr Config = getConfig("AGE2\\ConfigWindow"+std::to_string(window + 1));

        Config->Read("/EditorVersion", &EditorVersionString, AGE_AboutDialog::AGE_VER);
        sscanf(EditorVersionString, "%f", &EditorVersion);
        Config->Read("/TimesOpened", &TimesOpened, 0);
        if(EditorVersionString != AGE_AboutDialog::AGE_VER) TimesOpened = 0;
        Config->Read("Interaction/PromptForFilesOnOpen", &PromptForFilesOnOpen, true);
        Config->Read("Interaction/AutoCopy", &AutoCopy, true);
        Config->Read("Interaction/AutoCopyAngles", &AutoCopyAngles, true);
        Config->Read("Interaction/CopyGraphics", &CopyGraphics, false);
        Config->Read("Interaction/AllCivs", &AllCivs, true);
        Config->Read("Interaction/ShowSLP", &ShowSLP, true);
        Config->Read("Interaction/ShowIcons", &ShowIcons, true);
        Config->Read("Interaction/AnimSLP", &AnimSLP, true);
        Config->Read("Interaction/ShowShadows", &ShowShadows, true);
        Config->Read("Interaction/ShowOutline", &ShowOutline, true);
        Config->Read("Interaction/ShowDeltas", &ShowDeltas, true);
        Config->Read("Interaction/ShowStack", &ShowStack, true);
        Config->Read("Interaction/ShowAnnexes", &ShowAnnexes, true);
        Config->Read("Interaction/RotateAngles", &RotateAngles, true);
        Config->Read("Interaction/DrawTerrain", &DrawTerrain, true);
        Config->Read("Interaction/FilterAllSubs", &FilterAllSubs, true);
        Config->Read("Interaction/PlaySounds", &PlaySounds, true);
        Config->Read("Interface/ShowUnknowns", &ShowUnknowns, true);
        Config->Read("Interface/ResizeTerrains", &ResizeTerrains, false);
        Config->Read("Interface/StayOnTop", &StayOnTop, false);
        Config->Read("Interface/KeepViewOnTop", &KeepViewOnTop, false);
        Config->Read("Interface/Paste11", &Paste11, false);
        Config->Read("Interface/Reselection", &Reselection, true);
        Config->Read("Interface/MaxWindowWidthV2", &MaxWindowWidthV2, 0x4000);
        Move(Config->ReadLong("Interface/WindowPosX", -1), Config->ReadLong("Interface/WindowPosY", -1));
        Config->Read("Interface/Zooming", &slp_zoom, 1);
        Config->Read("Interface/ViewBackgroundR", &ViewBackR, 255);
        Config->Read("Interface/ViewBackgroundG", &ViewBackG, 255);
        Config->Read("Interface/ViewBackgroundB", &ViewBackB, 255);
        Config->Read("Interface/DrawAngles", &DrawAngles, false);
        Config->Read("Interface/DrawCollisionShape", &DrawCollisionShape, true);
        Config->Read("Interface/DrawClearanceShape", &DrawClearanceShape, true);
        Config->Read("Interface/DrawSelectionShape", &DrawOutline, true);
        Config->Read("Interface/CacheDepth", &temp, 32);
        Config->Read("Interface/AlexZoom", &AlexZoom, "x1");
        Config->Read("Interface/ViewPosX", &ViewPosX, -1);
        Config->Read("Interface/ViewPosY", &ViewPosY, -1);
        Config->Read("Interface/BoxWidthMultiplier", &boxWidthMultiplier, 1.f);
        Config->Read("DefaultFiles/DriveLetter", &DriveLetter, "C");
        Config->Read("DefaultFiles/CustomFolder", &CustomFolder, wxEmptyString);
        Config->Read("DefaultFiles/SyncSaveWithOpen", &SyncSaveWithOpen, true);
        Config->Read("DefaultFiles/Version", &GameVersion, EV_TC);
        Config->Read("DefaultFiles/SaveVersion", &SaveGameVersion, EV_TC);
        Config->Read("DefaultFiles/DatUsed", &DatUsed, 0);
        Config->Read("DefaultFiles/DatFilename", &DatFileName, wxEmptyString);
        Config->Read("DefaultFiles/SaveDatFilename", &SaveDatFileName, wxEmptyString);
        Config->Read("DefaultFiles/FolderDRS", &FolderDRS, wxEmptyString);
        Config->Read("DefaultFiles/FolderDRS2", &FolderDRS2, wxEmptyString);
        Config->Read("DefaultFiles/Path1stDRS", &Path1stDRS, wxEmptyString);
        Config->Read("DefaultFiles/PathLooseSprites", &PathSLP, wxEmptyString);
        Config->Read("DefaultFiles/UseDRS", &UseDRS, true);
        Config->Read("DefaultFiles/UseMod", &UseMod, false);
        Config->Read("DefaultFiles/UseExtra", &UseExtra, false);
        Config->Read("DefaultFiles/UseLooseSprites", &UseLooseSLP, false);
        Config->Read("DefaultFiles/LangsUsed", &LangsUsed, 7);
        Config->Read("DefaultFiles/WriteLangs", &WriteLangs, false);
        Config->Read("DefaultFiles/SaveLangs", &SaveLangs, false);
        Config->Read("DefaultFiles/LangWriteToLatest", &LangWriteToLatest, false);
        Config->Read("DefaultFiles/Language", &Language, "en");
        Config->Read("DefaultFiles/LangCharset", &LangCharset, "Windows-1252");
        Config->Read("DefaultFiles/LangFilename", &LangFileName, wxEmptyString);
        Config->Read("DefaultFiles/LangX1Filename", &LangX1FileName, wxEmptyString);
        Config->Read("DefaultFiles/LangX1P1Filename", &LangX1P1FileName, wxEmptyString);
        Config->Read("DefaultFiles/SaveLangFilename", &SaveLangFileName, wxEmptyString);
        Config->Read("DefaultFiles/SaveLangX1Filename", &SaveLangX1FileName, wxEmptyString);
        Config->Read("DefaultFiles/SaveLangX1P1Filename", &SaveLangX1P1FileName, wxEmptyString);
        Config->Read("DefaultFiles/SaveDat", &SaveDat, true);
        Config->Read("DefaultFiles/AutoBackups", &AutoBackups, false);
        Config->Read("DefaultFiles/PalettesPath", &PalettesPath, wxEmptyString);
        Config->Read("Misc/CustomTerrains", &CustomTerrains, 42);

        Config->Write("/EditorVersion", AGE_AboutDialog::AGE_VER);
        Config->Write("/TimesOpened", ++TimesOpened);

        GG::cache_depth = temp;
    }

    if(boxWidthMultiplier > 1.f)
    {
        AGETextCtrl::SMALL *= boxWidthMultiplier;
        AGETextCtrl::MEDIUM *= boxWidthMultiplier;
        AGETextCtrl::NORMAL *= boxWidthMultiplier;
        AGETextCtrl::LARGE *= boxWidthMultiplier;
        AGETextCtrl::GIANT *= boxWidthMultiplier;
    }

    wxColour back(ViewBackR, ViewBackG, ViewBackB);
    slp_background_brush = wxBrush(back);
    if(TimesOpened < 2) AnimSLP = ShowSLP = ShowIcons = true; // For people that had these initialized to false in previous release.

    CreateToolBar(wxTB_HORIZONTAL | wxTB_TEXT);
    int bars[5] = {295, 145, 145, 145, -1};
    CreateStatusBar(5)->SetStatusWidths(5, bars);

    GetToolBar()->AddTool(eAddWindow, "+++", wxBitmap(AppIcon24_xpm), "Open multiple editors to easily copy between files and game versions\nUse the normal copy and paste buttons\n4 windows seem to be the maximum");
    GetToolBar()->AddTool(eOpen, "Open", wxBitmap(GateOpen_xpm), "Open files");
    GetToolBar()->AddTool(eSave, "Save", wxBitmap(GateClosed_xpm), "Save files");
    GetToolBar()->AddTool(eBackup, "Auto", wxBitmap(AutoBackup_xpm), "Automatically backup files", wxITEM_CHECK);
    GetToolBar()->AddTool(eUnknown, "Show", wxBitmap(Question_xpm), "Show unknowns", wxITEM_CHECK);
    GetToolBar()->AddTool(eHex, "Hex", wxBitmap(Ox_xpm), "Toggle hex mode (data not editable)", wxITEM_CHECK);
    GetToolBar()->AddTool(eFloat, "0001", wxBitmap(float_xpm), "Toggle float display mode", wxITEM_CHECK);
    GetToolBar()->AddTool(eReselection, "List", wxBitmap(Reselection_xpm), "Toggle reselection when relisting", wxITEM_CHECK);
    GetToolBar()->AddTool(ePaste, "Paste", wxBitmap(Paste_xpm), "Toggle pasting between 1:1 and sequentially", wxITEM_CHECK);
    GetToolBar()->AddTool(eDRS, "SLP", wxBitmap(DRS_unlock_xpm), "Unload DRS files", wxITEM_CHECK);
    GetToolBar()->AddTool(eHelp, "Help", wxBitmap(Question_xpm), "Show help");
    GetToolBar()->ToggleTool(eBackup, AutoBackups);
    GetToolBar()->ToggleTool(eUnknown, ShowUnknowns);
    GetToolBar()->ToggleTool(ePaste, Paste11);
    GetToolBar()->ToggleTool(eReselection, Reselection);
    GetToolBar()->Realize();

    MenuBar_Main = new wxMenuBar();

    SubMenu_Options = new wxMenu();
    SubMenu_Options->AppendCheckItem(ePrompt, "&Prompt for files on open");
    SubMenu_Options->Check(ePrompt, PromptForFilesOnOpen);
    SubMenu_Options->AppendCheckItem(eButtons, "Allow adding &terrains");
    SubMenu_Options->Check(eButtons, ResizeTerrains);
    SubMenu_Options->AppendCheckItem(eStayOnTop, "&Stay on top");
    SubMenu_Options->Check(eStayOnTop, StayOnTop);
    SubMenu_Options->Append(eBoxWidth, "Set &width of the boxes");

    SubMenu_SLP = new wxMenu();
    SubMenu_SLP->AppendCheckItem(eShowSLP, "Show &graphics");
    SubMenu_SLP->Check(eShowSLP, ShowSLP);
    SubMenu_SLP->AppendCheckItem(eShowIcons, "Show &icons");
    SubMenu_SLP->Check(eShowIcons, ShowIcons);
    SubMenu_SLP->AppendCheckItem(eStayOnTopSLP, "Keep view on &top");
    SubMenu_SLP->Check(eStayOnTopSLP, KeepViewOnTop);
    SubMenu_SLP->Append(eSlpPals, "Set &palettes");
    SubMenu_SLP->Append(eSlpPCPal, "Set &player color palette");
    SubMenu_SLP->Append(eCacheDepth, "Set &cache depth");
    SubMenu_SLP->Append(eSlpZoom, "Set &zoom level");
#ifndef NDEBUG
    SubMenu_SLP->Append(eCompileList, "Compile SLP &list");
#endif

    SubMenu_Help = new wxMenu();
    SubMenu_Help->Append(eTips, "&Tips");
    SubMenu_Help->Append(eVasili, "Free some &memory");
    SubMenu_Help->Append(eAbout, "&About...");

    MenuBar_Main->Append(SubMenu_Options, "&Options");
    MenuBar_Main->Append(SubMenu_SLP, "&SLP");
    MenuBar_Main->Append(SubMenu_Help, "&Help");

    this->SetMenuBar(MenuBar_Main);

    CreateCivControls();
    CreateUnitControls();
    CreateResearchControls();
    CreateTechControls();
    CreateTechTreeControls();
    CreateGraphicsControls();
    CreateTerrainControls();
    CreateTerrainRestrictionControls();
    CreateSoundControls();
    CreatePlayerColorControls();
    CreateUnitLineControls();
    CreateTerrainBorderControls();
    CreateGeneralControls();
    CreateUnknownControls();

    // Freeing some memory
    ResearchComboBoxList.shrink_to_fit();
    TechComboBoxList.shrink_to_fit();
    CivComboBoxList.shrink_to_fit();
    ResourceComboBoxList.shrink_to_fit();
    uiGroupMaps.shrink_to_fit();
    uiGroupTT.shrink_to_fit();
    uiGroupTTAge.shrink_to_fit();
    uiGroupTTBuilding.shrink_to_fit();
    uiGroupTTUnit.shrink_to_fit();
    uiGroupTTResearch.shrink_to_fit();
    uiGroupRandomMap.shrink_to_fit();
    uiGroupRMBase.shrink_to_fit();
    uiGroupRMTerrain.shrink_to_fit();
    uiGroupRMUnit.shrink_to_fit();
    uiGroupRMUnknown.shrink_to_fit();
    uiGroupResearch.shrink_to_fit();
    uiGroupTechEffect.shrink_to_fit();
    uiGroupCiv.shrink_to_fit();
    uiGroupUnit.shrink_to_fit();
    uiGroupUnitDmgGraphic.shrink_to_fit();
    uiGroupUnitTask.shrink_to_fit();
    uiGroupGraphic.shrink_to_fit();
    uiGroupGraphicDelta.shrink_to_fit();
    uiGroupGraphicSound.shrink_to_fit();
    uiGroupTerrain.shrink_to_fit();
    uiGroupBorder.shrink_to_fit();
    uiGroupBorderFrame.shrink_to_fit();
    uiGroupRestriction.shrink_to_fit();
    uiGroupSound.shrink_to_fit();
    uiGroupSoundFile.shrink_to_fit();
    uiGroupColor.shrink_to_fit();

    Units_AutoCopy->SetValue(AutoCopy);
    Units_CopyGraphics->SetValue(CopyGraphics);
    Units_CopyTo->Enable(!AutoCopy);
    Units_SpecialCopy_Civs->SetValue(AllCivs);
    AngleSounds_AutoCopy->SetValue(AutoCopyAngles);
    AngleSounds_Copy->Enable(!AutoCopyAngles);

    TabBar_Main->AddPage(Tab_Research, "Techs");
    TabBar_Main->AddPage(Tab_Techs, "Effects");
    TabBar_Main->AddPage(Tab_TechTrees, "Tech Trees");
    TabBar_Main->AddPage(Tab_Civs, "Civilizations");
    TabBar_Main->AddPage(Tab_Units, "Units");
    TabBar_Main->AddPage(Tab_UnitLine, "Unitlines");
    TabBar_Main->AddPage(Tab_Graphics, "Graphics");
    TabBar_Main->AddPage(Tab_General, "Map");
    TabBar_Main->AddPage(Tab_Terrains, "Terrains");
    TabBar_Main->AddPage(Tab_TerrainBorders, "Borders");
    TabBar_Main->AddPage(Tab_TerrainRestrictions, "Terrain Tables");
    TabBar_Main->AddPage(Tab_Sounds, "Sounds");
    TabBar_Main->AddPage(Tab_PlayerColors, "Colors");
    TabBar_Main->AddPage(Tab_Unknown, "Maps");
    TabBar_Main->ChangeSelection(4);

    AGE_Frame::FixSize(this);

    Bind(wxEVT_CLOSE_WINDOW, &AGE_Frame::OnExit, this);
    Bind(wxEVT_IDLE, [this](wxIdleEvent&)
    {
        if(popUp.hasMessage)
        {
            wxMessageBox(popUp.popUpMessage, popUp.popUpTitle);
            popUp.hasMessage = false;
            if(popUp.focusTarget)
            {
                if(popUp.focusTarget->IsEnabled() && popUp.focusTarget->IsShownOnScreen())
                popUp.focusTarget->SetFocus();
                popUp.focusTarget = 0;
            }
        }
    });
    Bind(wxEVT_MENU, &AGE_Frame::OnOpen, this, eOpen);
    Bind(wxEVT_MENU, &AGE_Frame::OnSave, this, eSave);
    Bind(wxEVT_MENU, &AGE_Frame::OnMenuOption, this, ePrompt, eBoxWidth);
    Bind(wxEVT_MENU, &AGE_Frame::OnMenuOption, this, hotWin1, closeAll);

    Units_AutoCopy->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnAutoCopy, this);
    Units_CopyTo->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        auto selections = Units_ListV->GetSelectedCount();
        if(selections < 1) return;

        int edits = 0;
        GraphicCopies graphics;
        for(short civ = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(Units_CivBoxes[civ]->IsChecked() && civ != UnitCivID)
            {
                for(size_t loop = 0; loop < selections; ++loop)
                {
                    if(!CopyGraphics)// Let's copy graphics separately.
                    UnitsGraphicsCopy(graphics, civ, UnitIDs[loop]);
                    dataset->Civs[civ].Units[UnitIDs[loop]] = dataset->Civs[UnitCivID].Units[UnitIDs[loop]];
                    if(!CopyGraphics)// Let's paste graphics separately.
                    UnitsGraphicsPaste(graphics, civ, UnitIDs[loop]);
                }
                ++edits;
            }
        }

        SetStatusText("Manual unit copy", 2);
        SetStatusText("Edits: "+std::to_string(popUp.unSaved)+" + "+std::to_string(edits), 3);
        popUp.unSaved += edits;
    });
    Units_SelectAll->Bind(wxEVT_BUTTON, &AGE_Frame::OnAutoCopy, this);
    Units_SelectClear->Bind(wxEVT_BUTTON, &AGE_Frame::OnAutoCopy, this);
    Units_CopyGraphics->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnAutoCopy, this);
    Units_GraphicSet->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnAutoCopy, this);
    TabBar_Main->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &AGE_Frame::OnMenuOption, this, eTabBar);

    wxCommandEvent event(wxEVT_MENU);
    if(!window && TimesOpened < 2)
    {
        event.SetId(eHelp);
        OnMenuOption(event);
    }

    event.SetId(eVasili);
    OnMenuOption(event);

    event.SetId(eButtons);
    event.SetInt(ResizeTerrains);
    OnMenuOption(event);

    if(StayOnTop)
    {
        event.SetId(eStayOnTop);
        event.SetInt(true);
        OnMenuOption(event);
    }

    event.SetId(ePaste);
    event.SetInt(Paste11);
    OnMenuOption(event);

    event.SetId(eReselection);
    event.SetInt(Reselection);
    OnMenuOption(event);

    event.SetId(eShowSLP);
    event.SetInt(ShowSLP);
    OnMenuOption(event);

    event.SetId(eShowIcons);
    event.SetInt(ShowIcons);
    OnMenuOption(event);

    SkipOpenDialog = !PromptForFilesOnOpen;

#ifndef NDEBUG
    if(!log_out.is_open())
    {
        genie::Logger::setLogLevel(genie::Logger::L_DEBUG);
        log_out.open("gulog.ini");
        genie::Logger::setGlobalOutputStream(log_out);
        cout.rdbuf(log_out.rdbuf());
    }
#endif

    wxAcceleratorEntry shortcuts[] =
    {
        {wxACCEL_RAW_CTRL, int('O'), eOpen},
        {wxACCEL_RAW_CTRL, int('S'), eSave},
        {wxACCEL_RAW_CTRL, int('G'), eShowSLP},
        {wxACCEL_CTRL, int('1'), hotWin1},
        {wxACCEL_CTRL, int('2'), hotWin2},
        {wxACCEL_CTRL, int('3'), hotWin3},
        {wxACCEL_CTRL, int('4'), hotWin4}/*,
        //Broken. Works only as checkers, no button toggling.
        {wxACCEL_CTRL, int('U'), eUnknown},
        {wxACCEL_CTRL, int('H'), eHex},
        {wxACCEL_CTRL, int('F'), eFloat},
        {wxACCEL_CTRL, int('P'), ePaste},
        {wxACCEL_CTRL, int('R'), eReselection},
        {wxACCEL_CTRL, int('D'), eDRS},
        {wxACCEL_CTRL, int('Q'), closeAll}*/
    };
    // Keep count of shortcuts up to date!
    SetAcceleratorTable(wxAcceleratorTable(7, shortcuts));
}

void AGE_Frame::FixSizes()
{
    SetMinSize(wxSize(MinWindowWidth, 480));
    if(MaxWindowWidthV2 < GetMinSize().GetWidth()) MaxWindowWidthV2 = GetMinSize().GetWidth();
    SetMaxSize(wxSize(MaxWindowWidthV2, 0x4000));
}
