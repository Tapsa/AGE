#include "Common.h"
#include "../AboutDialog.h"
#include "../AGE_Frame.h"
#include "../EditableVersion.h"
#include "../Loaders.h"

// Icons
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

BaseMainFrame::BaseMainFrame(const wxString &title) :
    wxFrame(nullptr, wxID_ANY, title)
{
}

BaseMainFrame *BaseMainFrame::Create(wxString commands)
{
    return new AGE_Frame("Advanced Genie Editor " + AboutDialog::AGE_VER, 0, commands);
}

AGE_Frame::AGE_Frame(const wxString &title, short window, wxString aP) :
    BaseMainFrame(title), window_num(window), argPath(aP), font(GetFont())
    //font(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Tahoma")
{
    wxBusyCursor WaitCursor;
    {
        wxPanel model;
        //SetBackgroundStyle(wxBG_STYLE_SYSTEM);
        SetBackgroundColour(*wxYELLOW);// Hack to force the color.
        SetBackgroundColour(model.GetBackgroundColour());// Fixes most of the GUI drawing lag.
    }
    font.SetPointSize(8);
    SetIcon(wxIcon(AppIcon32_xpm));
    SetFont(font);
    displayScaling = FromDIP(1000) / 1000.f;
    TabBar_Main = new wxNotebook(this, eTabBar);
    openEditors[window] = this;
    {
        std::string windowNumText = lexical_cast<std::string>(window + 1);
        int temp;

        wxConfig Config("", "", "AGE2\\ConfigWindow" + windowNumText, "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        Config.Read("/EditorVersion", &EditorVersionString, AboutDialog::AGE_VER);
        if (EditorVersionString >= AboutDialog::AGE_VER)
        {
            Config.Read("/TimesOpened", &TimesOpened, 0);
        }
        else
        {
            TimesOpened = 0;
        }
        Config.Read("Interaction/PromptForFilesOnOpen", &PromptForFilesOnOpen, true);
        Config.Read("Interaction/AutoCopy", &AutoCopy, true);
        Config.Read("Interaction/AutoCopyAngles", &AutoCopyAngles, true);
        Config.Read("Interaction/CopyGraphics", &CopyGraphics, false);
        Config.Read("Interaction/AllCivs", &AllCivs, true);
        Config.Read("Interaction/ShowSLP", &ShowSLP, true);
        Config.Read("Interaction/ShowIcons", &ShowIcons, true);
        Config.Read("Interaction/AnimSLP", &AnimSLP, true);
        Config.Read("Interaction/ShowShadows", &ShowShadows, true);
        Config.Read("Interaction/ShowOutline", &ShowOutline, true);
        Config.Read("Interaction/ShowDeltas", &ShowDeltas, true);
        Config.Read("Interaction/ShowStack", &ShowStack, true);
        Config.Read("Interaction/ShowAnnexes", &ShowAnnexes, true);
        Config.Read("Interaction/RotateAngles", &RotateAngles, true);
        Config.Read("Interaction/DrawTerrain", &DrawTerrain, true);
        Config.Read("Interaction/FilterAllSubs", &FilterAllSubs, true);
        Config.Read("Interaction/PlaySounds", &PlaySounds, true);
        Config.Read("Interaction/NeverHideAttributes", &NeverHideAttributes, false);
        Config.Read("Interface/ShowUnknowns", &ShowUnknowns, true);
        Config.Read("Interface/ResizeTerrains", &ResizeTerrains, false);
        Config.Read("Interface/StayOnTop", &StayOnTop, false);
        Config.Read("Interface/KeepViewOnTop", &KeepViewOnTop, false);
        Config.Read("Interface/Paste11", &Paste11, false);
        Config.Read("Interface/Reselection", &Reselection, true);
        Config.Read("Interface/MaxWindowWidthV2", &maxWindowWidthV2, 0x4000);
        Config.Read("Interface/WindowPosX", &lastWindowPosX, 0);
        Config.Read("Interface/WindowPosY", &lastWindowPosY, 0);
        Config.Read("Interface/Zooming", &slp_zoom, 1);
        Config.Read("Interface/ViewBackgroundR", &ViewBackR, 255);
        Config.Read("Interface/ViewBackgroundG", &ViewBackG, 255);
        Config.Read("Interface/ViewBackgroundB", &ViewBackB, 255);
        Config.Read("Interface/DrawAngles", &DrawAngles, false);
        Config.Read("Interface/DrawCollisionShape", &DrawCollisionShape, true);
        Config.Read("Interface/DrawClearanceShape", &DrawClearanceShape, true);
        Config.Read("Interface/DrawSelectionShape", &DrawOutline, true);
        Config.Read("Interface/CacheSizeMB", &temp, 1000);
        Config.Read("Interface/AlexZoom", &AlexZoom, "x1");
        Config.Read("Interface/ViewPosX", &ViewPosX, -1);
        Config.Read("Interface/ViewPosY", &ViewPosY, -1);
        Config.Read("Interface/BoxWidthMultiplier", &boxWidthMultiplier, 1.f);
        // Global settings
        if (window == 0)
        {
            int rate;
            Config.Read("Interface/ScrollRate", &rate, 60);
            AScrolled::rate = rate / 120.f;
        }
        Config.Read("DefaultFiles/DriveLetter", &DriveLetter, "C");
        Config.Read("DefaultFiles/CustomFolder", &CustomFolder, wxEmptyString);
        Config.Read("DefaultFiles/SyncSaveWithOpen", &SyncSaveWithOpen, true);
        Config.Read("DefaultFiles/Version", &GameVersion, EV_TC);
        Config.Read("DefaultFiles/SaveVersion", &SaveGameVersion, EV_TC);
        Config.Read("DefaultFiles/DatUsed", &DatUsed, 0);
        Config.Read("DefaultFiles/DatFilename", &DatFileName, wxEmptyString);
        Config.Read("DefaultFiles/SaveDatFilename", &SaveDatFileName, wxEmptyString);
        Config.Read("DefaultFiles/FolderDRS", &FolderDRS, wxEmptyString);
        Config.Read("DefaultFiles/FolderDRS2", &FolderDRS2, wxEmptyString);
        Config.Read("DefaultFiles/Path1stDRS", &Path1stDRS, wxEmptyString);
        Config.Read("DefaultFiles/PathLooseSprites", &PathSLP, wxEmptyString);
        Config.Read("DefaultFiles/PathLooseModSprites", &PathModSLP, wxEmptyString);
        Config.Read("DefaultFiles/PathPalettes", &PathPalettes, wxEmptyString);
        Config.Read("DefaultFiles/PathPlayerPalette", &PathPlayerColorPalette, wxEmptyString);
        Config.Read("DefaultFiles/UseDRS", &UseDRS, true);
        Config.Read("DefaultFiles/UseMod", &UseMod, false);
        Config.Read("DefaultFiles/UseExtra", &UseExtra, false);
        Config.Read("DefaultFiles/UseLooseSprites", &UseLooseSLP, false);
        Config.Read("DefaultFiles/UseLooseModSprites", &UseLooseModSLP, false);
        Config.Read("DefaultFiles/LangsUsed", &LangsUsed, 7);
        Config.Read("DefaultFiles/WriteLangs", &WriteLangs, false);
        Config.Read("DefaultFiles/SaveLangs", &SaveLangs, false);
        Config.Read("DefaultFiles/LangWriteToLatest", &LangWriteToLatest, false);
        Config.Read("DefaultFiles/Language", &Language, "en");
        Config.Read("DefaultFiles/LangCharset", &LangCharset, "Windows-1252");
        Config.Read("DefaultFiles/LangFilename", &LangFileName, wxEmptyString);
        Config.Read("DefaultFiles/LangX1Filename", &LangX1FileName, wxEmptyString);
        Config.Read("DefaultFiles/LangX1P1Filename", &LangX1P1FileName, wxEmptyString);
        Config.Read("DefaultFiles/SaveLangFilename", &SaveLangFileName, wxEmptyString);
        Config.Read("DefaultFiles/SaveLangX1Filename", &SaveLangX1FileName, wxEmptyString);
        Config.Read("DefaultFiles/SaveLangX1P1Filename", &SaveLangX1P1FileName, wxEmptyString);
        Config.Read("DefaultFiles/SaveDat", &SaveDat, true);
        Config.Read("DefaultFiles/AutoBackups", &AutoBackups, false);
        Config.Read("Misc/CustomTerrains", &CustomTerrains, 42);

        Config.Write("/EditorVersion", AboutDialog::AGE_VER);
        Config.Write("/TimesOpened", ++TimesOpened);

        GG::cache_size = std::min(std::max(temp, 100), 3000) * 1000000u;
    }

    float boxWidthScaling = boxWidthMultiplier * displayScaling;
    if (boxWidthScaling > 1.f)
    {
        AGETextCtrl::SMALL = 50 * boxWidthScaling;
        AGETextCtrl::MEDIUM = 70 * boxWidthScaling;
        AGETextCtrl::NORMAL = 100 * boxWidthScaling;
        AGETextCtrl::LARGE = 150 * boxWidthScaling;
        AGETextCtrl::GIANT = 200 * boxWidthScaling;
    }

    wxColour back(ViewBackR, ViewBackG, ViewBackB);
    slp_background_brush = wxBrush(back);
    if (TimesOpened < 2) AnimSLP = ShowSLP = ShowIcons = true; // For people that had these initialized to false in previous release.

    CreateToolBar(wxTB_HORIZONTAL | wxTB_TEXT);
    int bars[5] = { 295, 145, 145, 145, -1 };
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
    GetToolBar()->AddTool(eDRS, "Sprite", wxBitmap(DRS_unlock_xpm), "Unload DRS files", wxITEM_CHECK);
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
    SubMenu_Options->Append(eScrollRate, "Set scroll &rate");
    SubMenu_Options->AppendCheckItem(eNeverHide, "Never hide &attributes");
    SubMenu_Options->Check(eNeverHide, NeverHideAttributes);

    SubMenu_SLP = new wxMenu();
    SubMenu_SLP->AppendCheckItem(eShowSLP, "Show &graphics");
    SubMenu_SLP->Check(eShowSLP, ShowSLP);
    SubMenu_SLP->AppendCheckItem(eShowIcons, "Show &icons");
    SubMenu_SLP->Check(eShowIcons, ShowIcons);
    SubMenu_SLP->AppendCheckItem(eStayOnTopSLP, "Keep view on &top");
    SubMenu_SLP->Check(eStayOnTopSLP, KeepViewOnTop);
    SubMenu_SLP->Append(eSlpPals, "Set &palettes");
    SubMenu_SLP->Append(eSlpPCPal, "Set &player color palette");
    SubMenu_SLP->Append(eCacheDepth, "Set &cache size");
    SubMenu_SLP->Append(eSlpZoom, "Set &zoom level");
    SubMenu_SLP->Append(eCompileList, "Compile SLP &list");

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

    FixSize(displayScaling);

    Bind(wxEVT_CLOSE_WINDOW, &AGE_Frame::OnExit, this);
    Bind(wxEVT_IDLE, [this](wxIdleEvent &)
    {
        if (popUp.hasMessage)
        {
            wxMessageBox(popUp.popUpMessage, popUp.popUpTitle);
            popUp.hasMessage = false;
            if (popUp.focusTarget)
            {
                if (popUp.focusTarget->IsEnabled() && popUp.focusTarget->IsShownOnScreen())
                    popUp.focusTarget->SetFocus();
                popUp.focusTarget = 0;
            }
        }
    });
    Bind(wxEVT_MENU, &AGE_Frame::OnOpen, this, eOpen);
    Bind(wxEVT_MENU, &AGE_Frame::OnSave, this, eSave);
    Bind(wxEVT_MENU, &AGE_Frame::OnMenuOption, this, ePrompt, eScrollRate);
    Bind(wxEVT_MENU, &AGE_Frame::OnMenuOption, this, hotWin1, closeAll);
    Bind(wxEVT_MENU, &AGE_Frame::OnAnimationMenuOption, this, eShowSLP, eSlpZoom);

    Units_AutoCopy->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnAutoCopy, this);
    Units_CopyTo->Bind(wxEVT_BUTTON, [this](wxCommandEvent &)
    {
        size_t selections = Units_ListV->GetSelectedCount();
        if (selections < 1) return;

        size_t edits = 0;
        GraphicCopies graphics;
        for (size_t civ = 0; civ < dataset->Civs.size(); ++civ)
        {
            if (Units_CivBoxes[civ]->IsChecked() && civ != UnitCivID)
            {
                for (size_t loop = 0; loop < selections; ++loop)
                {
                    if (!CopyGraphics)// Let's copy graphics separately.
                        UnitsGraphicsCopy(graphics, civ, UnitIDs[loop]);
                    dataset->Civs[civ].Units[UnitIDs[loop]] = dataset->Civs[UnitCivID].Units[UnitIDs[loop]];
                    if (!CopyGraphics)// Let's paste graphics separately.
                        UnitsGraphicsPaste(graphics, civ, UnitIDs[loop]);
                }
                ++edits;
            }
        }

        SetStatusText("Manual unit copy", 2);
        SetStatusText(wxString::Format("Edits: %zu + %zu", popUp.unSaved, edits), 3);
        popUp.unSaved += edits;
    });
    Units_SelectAll->Bind(wxEVT_BUTTON, &AGE_Frame::OnAutoCopy, this);
    Units_SelectClear->Bind(wxEVT_BUTTON, &AGE_Frame::OnAutoCopy, this);
    Units_CopyGraphics->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnAutoCopy, this);
    Units_GraphicSet->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnAutoCopy, this);
    TabBar_Main->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &AGE_Frame::OnMenuOption, this, eTabBar);

    wxCommandEvent event(wxEVT_MENU);
    if (!window && TimesOpened < 2)
    {
        event.SetId(eHelp);
        OnMenuOption(event);
    }

    event.SetId(eVasili);
    OnMenuOption(event);

    event.SetId(eButtons);
    event.SetInt(ResizeTerrains);
    OnMenuOption(event);

    event.SetId(eNeverHide);
    event.SetInt(NeverHideAttributes);
    OnMenuOption(event);

    if (StayOnTop)
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
    OnAnimationMenuOption(event);

    event.SetId(eShowIcons);
    event.SetInt(ShowIcons);
    OnAnimationMenuOption(event);

    SkipOpenDialog = !PromptForFilesOnOpen;

#ifndef NDEBUG
    if (!log_out.is_open())
    {
        genie::Logger::setLogLevel(genie::Logger::L_DEBUG);
        log_out.open("gulog.txt");
        genie::Logger::setGlobalOutputStream(log_out);
        std::cout.rdbuf(log_out.rdbuf());
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

// Fancy scaling :)
void AGE_Frame::FixSize(float scale)
{
    wxRect maxSize(wxDisplay(this).GetClientArea());
    float minScrollerWidth = 630 * scale;
    int ScrollerWidth = Units_ScrollSpace->GetMinSize().GetWidth();
    if (ScrollerWidth > minScrollerWidth)
    {
        int NewWidth = 270 * scale * (ScrollerWidth / minScrollerWidth) + ScrollerWidth;
        minWindowWidth = std::min<int>(NewWidth, maxSize.width);
    }
    else
    {
        minWindowWidth = std::min<int>(900 * scale, maxSize.width);
    }
    int windowHeight = std::min<int>(870 * scale, maxSize.height);
    SetSize(minWindowWidth, windowHeight);
    SetMinSize(wxSize(minWindowWidth, std::min<int>(480 * scale, maxSize.height)));
    if (maxWindowWidthV2 < GetMinSize().GetWidth())
    {
        maxWindowWidthV2 = GetMinSize().GetWidth();
    }
    SetMaxSize(wxSize(maxWindowWidthV2, 0x4000));
    if (maxSize.width - minWindowWidth < lastWindowPosX)
    {
        lastWindowPosX = maxSize.width - minWindowWidth;
    }
    if (maxSize.height - windowHeight < lastWindowPosY)
    {
        lastWindowPosY = maxSize.height - windowHeight;
    }
    Move(std::max<int>(0, lastWindowPosX), std::max<int>(0, lastWindowPosY));
    Show(true);
}
