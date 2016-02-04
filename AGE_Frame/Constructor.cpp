#include "../AGE_Frame.h"
#include "../AppIcon.xpm"
#include "../GateOpen.xpm"
#include "../GateClosed.xpm"
#include "../Question.xpm"
#include "../Ox.xpm"
#include "../float.xpm"
#include "../Paste.xpm"
#include "../AppIcon24.xpm"
#include "../DRSunlock.xpm"
#include "../AutoBackup.xpm"
//#include "genie/util/Logger.h"

std::ofstream AGE_Frame::log_out;

AGE_Frame::AGE_Frame(const wxString &title, short window, wxString aP)
: wxFrame(NULL, wxID_ANY, title)
{
    window_num = window;
	argPath = aP;
	SetIcon(wxIcon(AppIcon_xpm));
	wxBusyCursor WaitCursor;
	TabBar_Main = new wxNotebook(this, eTabBar);
    slp_window = NULL;
    paletteView = randomi = 0;
    AGE_Frame::openEditors[window] = this;

    {
        wxFileConfig Config("AGE", "Tapsa", "age2configw"+lexical_cast<string>(window + 1)+".ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        Config.Read("/EditorVersion", &EditorVersionString, AGE_AboutDialog::AGE_VER);
        sscanf(EditorVersionString, "%f", &EditorVersion);
        Config.Read("/TimesOpened", &TimesOpened, 0);
        if(EditorVersionString != AGE_AboutDialog::AGE_VER) TimesOpened = 0;
        Config.Read("Interaction/PromptForFilesOnOpen", &PromptForFilesOnOpen, true);
        Config.Read("Interaction/AutoCopy", &AutoCopy, true);
        Config.Read("Interaction/CopyGraphics", &CopyGraphics, false);
        Config.Read("Interaction/AllCivs", &AllCivs, true);
        Config.Read("Interaction/EnableIDFix", &EnableIDFix, true);
        Config.Read("Interaction/ShowSLP", &ShowSLP, true);
        Config.Read("Interaction/ShowIcons", &ShowIcons, true);
        Config.Read("Interaction/AnimSLP", &AnimSLP, true);
        Config.Read("Interaction/ShowShadows", &ShowShadows, true);
        Config.Read("Interaction/ShowOutline", &ShowOutline, true);
        Config.Read("Interaction/ShowDeltas", &ShowDeltas, true);
        Config.Read("Interaction/ShowStack", &ShowStack, true);
        Config.Read("Interaction/ShowAnnexes", &ShowAnnexes, true);
        Config.Read("Interaction/DrawTerrain", &DrawTerrain, true);
        Config.Read("Interaction/FilterAllSubs", &FilterAllSubs, true);
        Config.Read("Interface/ShowUnknowns", &ShowUnknowns, true);
        Config.Read("Interface/ShowButtons", &ShowButtons, false);
        Config.Read("Interface/StayOnTop", &StayOnTop, false);
        Config.Read("Interface/StayOnTopSLP", &StayOnTopSLP, false);
        Config.Read("Interface/Paste11", &Paste11, true);
        Config.Read("Interface/MaxWindowWidth", &MaxWindowWidth, 900);
        Config.Read("Interface/SLPareaPerCent", &SLPareaPerCent, 100);
        Config.Read("Interface/SLPbackR", &SLPbackR, 255);
        Config.Read("Interface/SLPbackG", &SLPbackG, 255);
        Config.Read("Interface/SLPbackB", &SLPbackB, 255);
        Config.Read("Interface/DrawCollisionShape", &DrawCollisionShape, true);
        Config.Read("Interface/DrawClearanceShape", &DrawClearanceShape, true);
        Config.Read("Interface/DrawSelectionShape", &DrawSelectionShape, true);
        Config.Read("DefaultFiles/DriveLetter", &DriveLetter, "C");
        Config.Read("DefaultFiles/UseCustomPath", &UseCustomPath, false);
        Config.Read("DefaultFiles/CustomFolder", &CustomFolder, wxEmptyString);
        Config.Read("DefaultFiles/Version", &GameVersion, genie::GV_TC);
        Config.Read("DefaultFiles/SaveVersion", &SaveGameVersion, genie::GV_TC);
        Config.Read("DefaultFiles/DatUsed", &DatUsed, 0);
        Config.Read("DefaultFiles/DatFilename", &DatFileName, wxEmptyString);
        Config.Read("DefaultFiles/SaveDatFilename", &SaveDatFileName, wxEmptyString);
        Config.Read("DefaultFiles/FolderDRS", &FolderDRS, wxEmptyString);
        Config.Read("DefaultFiles/FolderDRS2", &FolderDRS2, wxEmptyString);
        Config.Read("DefaultFiles/Path1stDRS", &Path1stDRS, wxEmptyString);
        Config.Read("DefaultFiles/UseDRS", &UseDRS, true);
        Config.Read("DefaultFiles/UseMod", &UseMod, false);
        Config.Read("DefaultFiles/UseExtra", &UseExtra, false);
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

        Config.Write("/EditorVersion", AGE_AboutDialog::AGE_VER);
        Config.Write("/TimesOpened", ++TimesOpened);
    }

    wxColour back(SLPbackR, SLPbackG, SLPbackB);
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
    GetToolBar()->AddTool(ePaste, "Paste", wxBitmap(Paste_xpm), "Toggle pasting between 1:1 and sequentially", wxITEM_CHECK);
    GetToolBar()->AddTool(eDRS, "SLP", wxBitmap(DRS_unlock_xpm), "Unload DRS files", wxITEM_CHECK);
    GetToolBar()->AddTool(eHelp, "Help", wxBitmap(Question_xpm), "Show help");
    GetToolBar()->ToggleTool(eBackup, AutoBackups);
    GetToolBar()->ToggleTool(eUnknown, ShowUnknowns);
    GetToolBar()->ToggleTool(ePaste, Paste11);
    GetToolBar()->Realize();

    MenuBar_Main = new wxMenuBar();

    SubMenu_Options = new wxMenu();
    SubMenu_Options->AppendCheckItem(ePrompt, "&Prompt for files on open");
    SubMenu_Options->Check(ePrompt, PromptForFilesOnOpen);
    SubMenu_Options->AppendCheckItem(eButtons, "Allow adding &terrains");
    SubMenu_Options->Check(eButtons, ShowButtons);

    SubMenu_Options->AppendCheckItem(eIdFix, "Enable &index fixes");
    SubMenu_Options->Check(eIdFix, EnableIDFix);
    SubMenu_Options->Enable(eIdFix, false);
    SubMenu_Options->AppendCheckItem(eStayOnTop, "&Stay on top");
    SubMenu_Options->Check(eStayOnTop, StayOnTop);

    SubMenu_SLP = new wxMenu();
    SubMenu_SLP->AppendCheckItem(eShowSLP, "Show SLP &graphics");
    SubMenu_SLP->Check(eShowSLP, ShowSLP);
    SubMenu_SLP->AppendCheckItem(eShowIcons, "Show SLP &icons");
    SubMenu_SLP->Check(eShowIcons, ShowIcons);
    SubMenu_SLP->AppendCheckItem(eStayOnTopSLP, "Keep SLP view on &top");
    SubMenu_SLP->Check(eStayOnTopSLP, StayOnTopSLP);

    SubMenu_Help = new wxMenu();
    SubMenu_Help->Append(eTips, "&Tips");
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
    uiGroupUnitCommand.shrink_to_fit();
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

//	TabBar_Main->AddPage(TabBar_Data, "Data");
//	TabBar_Main->AddPage(TabBar_Test, "Test");

	GenieVersion = genie::GV_None;
	TabBar_Main->AddPage(Tab_Research, "Research");
	TabBar_Main->AddPage(Tab_Techs, "Techs");
	TabBar_Main->AddPage(Tab_TechTrees, "Tech Trees");
	TabBar_Main->AddPage(Tab_Civs, "Civilizations");
	TabBar_Main->AddPage(Tab_Units, "Units");
	TabBar_Main->AddPage(Tab_UnitLine, "Unitlines");
	TabBar_Main->AddPage(Tab_Graphics, "Graphics");
	TabBar_Main->AddPage(Tab_General, "Map");
	TabBar_Main->AddPage(Tab_Terrains, "Terrains");
	TabBar_Main->AddPage(Tab_TerrainBorders, "Borders");
	TabBar_Main->AddPage(Tab_TerrainRestrictions, "T. Restrictions");
	TabBar_Main->AddPage(Tab_Sounds, "Sounds");
	TabBar_Main->AddPage(Tab_PlayerColors, "Colors");
	TabBar_Main->AddPage(Tab_Unknown, "Maps");
	TabBar_Main->ChangeSelection(0);

//	TabBar_Test->AddPage(Tab_DRS, "DRS Files");
//	TabBar_Test->SetSelection(0);

    Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(AGE_Frame::OnExit));
    Connect(wxEVT_IDLE, wxIdleEventHandler(AGE_Frame::showPopUp));
    Connect(eOpen, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnOpen));
    Connect(eSave, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnSave));
    Connect(ePrompt, eAddWindow, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
    Connect(Units_AutoCopy->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
    Connect(Units_CopyTo->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::UnitsAutoCopy));
    Connect(Units_SelectAll->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
    Connect(Units_SelectClear->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
    Connect(Units_CopyGraphics->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
    Connect(Units_GraphicSet->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
    Connect(eTabBar, wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
    Connect(hotWin1, hotWin4, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));

	DataOpened = UseTXT = DrawHot = exportFrame = false;
	for(size_t loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;

	wxCommandEvent ShowUnknownsCmd(wxEVT_COMMAND_MENU_SELECTED, eUnknown);
	ShowUnknownsCmd.SetInt(ShowUnknowns);
	ProcessEvent(ShowUnknownsCmd);

	wxCommandEvent ShowButtonsCmd(wxEVT_COMMAND_MENU_SELECTED, eButtons);
	ShowButtonsCmd.SetInt(ShowButtons);
	ProcessEvent(ShowButtonsCmd);

    if(StayOnTop)
    {
        wxCommandEvent StayOnTopCmd(wxEVT_COMMAND_MENU_SELECTED, eStayOnTop);
        StayOnTopCmd.SetInt(true);
        ProcessEvent(StayOnTopCmd);
    }

	wxCommandEvent Paste11Cmd(wxEVT_COMMAND_MENU_SELECTED, ePaste);
	Paste11Cmd.SetInt(Paste11);
	ProcessEvent(Paste11Cmd);

	if(TimesOpened < 2)
	{
		wxCommandEvent ShowHelpCmd(wxEVT_COMMAND_MENU_SELECTED, eHelp);
		ProcessEvent(ShowHelpCmd);
	}

	wxCommandEvent ShowSLPCmd(wxEVT_COMMAND_MENU_SELECTED, eShowSLP);
	ShowSLPCmd.SetInt(ShowSLP);
	ProcessEvent(ShowSLPCmd);

	wxCommandEvent ShowIconsCmd(wxEVT_COMMAND_MENU_SELECTED, eShowIcons);
	ShowIconsCmd.SetInt(ShowIcons);
	ProcessEvent(ShowIconsCmd);

	SkipOpenDialog = !PromptForFilesOnOpen;

#ifndef NDEBUG
    if(!log_out.is_open())
    {
        genie::Logger::setLogLevel(genie::Logger::L_DEBUG);
        log_out.open("gulog.ini");
        genie::Logger::setGlobalOutputStream(log_out);
    }
#endif

	dataset = NULL;
	Lang = NULL;
	LangX = NULL;
	LangXP = NULL;
	wxToolTip::SetDelay(200);
	wxToolTip::SetAutoPop(32700);
	wxToolTip::SetReshow(1);

    wxAcceleratorEntry shortcuts[] =
    {
        {wxACCEL_RAW_CTRL, int('O'), eOpen},
        {wxACCEL_RAW_CTRL, int('S'), eSave},
        {wxACCEL_RAW_CTRL, int('G'), eShowSLP},
        {wxACCEL_SHIFT, int('1'), hotWin1},
        {wxACCEL_SHIFT, int('2'), hotWin2},
        {wxACCEL_SHIFT, int('3'), hotWin3},
        {wxACCEL_SHIFT, int('4'), hotWin4},
        {wxACCEL_CTRL , int('U'), eUnknown},
        {wxACCEL_CTRL , int('H'), eHex},
        {wxACCEL_CTRL , int('F'), eFloat},
        {wxACCEL_CTRL , int('P'), ePaste},
        {wxACCEL_CTRL , int('D'), eDRS}
    };
    SetAcceleratorTable(wxAcceleratorTable(8, shortcuts));
}

void AGE_Frame::FixSizes()
{
	SetMinSize(wxSize(MinWindowWidth, 480));
	if(MaxWindowWidth < GetMinSize().GetWidth()) MaxWindowWidth = GetMinSize().GetWidth();
	SetMaxSize(wxSize(MaxWindowWidth, 4096));
}
