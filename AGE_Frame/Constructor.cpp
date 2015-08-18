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
//#include "genie/util/Logger.h"

std::ofstream AGE_Frame::log_out;

AGE_Frame::AGE_Frame(const wxString &title, short window, wxString aP)
: wxFrame(NULL, wxID_ANY, title)
{
	SetIcon(wxIcon(AppIcon_xpm));
	wxBusyCursor WaitCursor;
	TabBar_Main = new wxNotebook(this, wxID_ANY);
	argPath = aP;
	AGEwindow = window;
    slp_window = NULL;
    paletteView = 0;

    if(window < AGE_Frame::openEditors.size())
    {
        AGE_Frame::openEditors[window] = true;
    }
    else
    {
        AGE_Frame::openEditors.push_back(true);
        AGETextCtrl::hexMode.push_back(false);
        AGETextCtrl::accurateFloats.push_back(false);
        AGETextCtrl::unSaved.push_back(0);
        AGETextCtrl::fileLoaded.push_back(0);
    }

	Config = new wxFileConfig(wxEmptyString, "Tapsa", "age2configw"+lexical_cast<string>(AGEwindow + 1)+".ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	Config->Read("/EditorVersion", &EditorVersionString, AGE_AboutDialog::AGE_VER);
	sscanf(EditorVersionString, "%f", &EditorVersion);
	Config->Read("/TimesOpened", &TimesOpened, 0);
	if(EditorVersionString != AGE_AboutDialog::AGE_VER) TimesOpened = 0;
	Config->Read("Interaction/PromptForFilesOnOpen", &PromptForFilesOnOpen, true);
	Config->Read("Interaction/AutoCopy", &AutoCopy, true);
	Config->Read("Interaction/CopyGraphics", &CopyGraphics, false);
	Config->Read("Interaction/AllCivs", &AllCivs, true);
	Config->Read("Interaction/EnableIDFix", &EnableIDFix, true);
	Config->Read("Interaction/ShowSLP", &ShowSLP, true);
	Config->Read("Interaction/AnimSLP", &AnimSLP, true);
	Config->Read("Interaction/ShowShadows", &ShowShadows, true);
	Config->Read("Interaction/ShowOutline", &ShowOutline, true);
	Config->Read("Interaction/ShowDeltas", &ShowDeltas, true);
	Config->Read("Interaction/ShowStack", &ShowStack, true);
	Config->Read("Interaction/ShowAnnexes", &ShowAnnexes, true);
	Config->Read("Interface/ShowUnknowns", &ShowUnknowns, true);
	Config->Read("Interface/ShowButtons", &ShowButtons, false);
	Config->Read("Interface/Paste11", &Paste11, true);
	Config->Read("Interface/MaxWindowWidth", &MaxWindowWidth, 900);
	Config->Read("Interface/SLPareaPerCent", &SLPareaPerCent, 100);
	Config->Read("DefaultFiles/DriveLetter", &DriveLetter, "C");
	Config->Read("DefaultFiles/UseCustomPath", &UseCustomPath, false);
	Config->Read("DefaultFiles/CustomFolder", &CustomFolder, wxEmptyString);
	Config->Read("DefaultFiles/Version", &GameVersion, genie::GV_TC);
	Config->Read("DefaultFiles/SaveVersion", &SaveGameVersion, 3);
	Config->Read("DefaultFiles/DatUsed", &DatUsed, 0);
	Config->Read("DefaultFiles/DatFilename", &DatFileName, wxEmptyString);
	Config->Read("DefaultFiles/SaveDatFilename", &SaveDatFileName, wxEmptyString);
	Config->Read("DefaultFiles/FolderDRS", &FolderDRS, wxEmptyString);
	Config->Read("DefaultFiles/FolderDRS2", &FolderDRS2, wxEmptyString);
	Config->Read("DefaultFiles/UseDRS", &UseDRS, false);
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
	Config->Read("Misc/CustomTerrains", &CustomTerrains, 42);

	Config->Write("/EditorVersion", AGE_AboutDialog::AGE_VER);
	Config->Write("/TimesOpened", ++TimesOpened);
	delete Config;

	if(TimesOpened < 2) AnimSLP = ShowSLP = true; // For people that had these initialized to false in previous release.

	CreateToolBar(wxTB_HORIZONTAL | wxTB_TEXT);
	int bars[5] = {295, 145, 145, 145, -1};
	CreateStatusBar(5)->SetStatusWidths(5, bars);

	GetToolBar()->AddTool(ToolBar_AddWindow, "+++", wxBitmap(AppIcon24_xpm), "Open multiple editors to easily copy between files and game versions\nUse the normal copy and paste buttons\n4 windows seem to be the maximum");
	GetToolBar()->AddTool(ToolBar_Open, "Open", wxBitmap(GateOpen_xpm), "Open files");
	GetToolBar()->AddTool(ToolBar_Save, "Save", wxBitmap(GateClosed_xpm), "Save files");
	GetToolBar()->AddTool(ToolBar_Show, "Show", wxBitmap(Question_xpm), "Show unknowns", wxITEM_CHECK);
	GetToolBar()->AddTool(ToolBar_Hex, "Hex", wxBitmap(Ox_xpm), "Toggle hex mode (data not editable)", wxITEM_CHECK);
	GetToolBar()->AddTool(ToolBar_Float, "0001", wxBitmap(float_xpm), "Toggle float display mode", wxITEM_CHECK);
	GetToolBar()->AddTool(ToolBar_Paste, "Paste", wxBitmap(Paste_xpm), "Toggle pasting between 1:1 and sequentially", wxITEM_CHECK);
	GetToolBar()->AddTool(ToolBar_DRS, "SLP", wxBitmap(DRS_unlock_xpm), "Unload DRS files", wxITEM_CHECK);
	GetToolBar()->AddTool(ToolBar_Help, "Help", wxBitmap(Question_xpm), "Show help");
	GetToolBar()->ToggleTool(ToolBar_Show, ShowUnknowns);
	GetToolBar()->ToggleTool(ToolBar_Paste, Paste11);
	GetToolBar()->Realize();

	MenuBar_Main = new wxMenuBar();

	SubMenu_Options = new wxMenu();
	SubMenu_Options->AppendCheckItem(MenuOption_Prompt, "&Prompt for files on open");
	SubMenu_Options->Check(MenuOption_Prompt, PromptForFilesOnOpen);
	SubMenu_Options->AppendCheckItem(MenuOption_Buttons, "Allow adding &terrains");
	SubMenu_Options->Check(MenuOption_Buttons, ShowButtons);

	SubMenu_Options->AppendCheckItem(MenuOption_IDFix, "Enable &index fixes");
	SubMenu_Options->Check(MenuOption_IDFix, EnableIDFix);
	SubMenu_Options->Enable(MenuOption_IDFix, false);

	SubMenu_SLP = new wxMenu();
	SubMenu_SLP->AppendCheckItem(MenuOption_ShowSLP, "Show SLP &graphics");
	SubMenu_SLP->Check(MenuOption_ShowSLP, ShowSLP);
	SubMenu_SLP->AppendCheckItem(MenuOption_AnimSLP, "&Animate SLP graphics");
	SubMenu_SLP->Check(MenuOption_AnimSLP, AnimSLP);
	SubMenu_SLP->AppendCheckItem(MenuOption_ShowShadows, "Show SLP &shadows");
	SubMenu_SLP->Check(MenuOption_ShowShadows, ShowShadows);
	SubMenu_SLP->AppendCheckItem(MenuOption_ShowOutline, "Show SLP &outline");
	SubMenu_SLP->Check(MenuOption_ShowOutline, ShowOutline);
	SubMenu_SLP->AppendCheckItem(MenuOption_ShowDeltas, "Show SLP &deltas");
	SubMenu_SLP->Check(MenuOption_ShowDeltas, ShowDeltas);
	SubMenu_SLP->AppendCheckItem(MenuOption_ShowStack, "Show SLP graphics of stack &unit");
	SubMenu_SLP->Check(MenuOption_ShowStack, ShowStack);
	SubMenu_SLP->AppendCheckItem(MenuOption_ShowAnnexes, "Show SLP graphics of annex &units");
	SubMenu_SLP->Check(MenuOption_ShowAnnexes, ShowAnnexes);

	SubMenu_Help = new wxMenu();
	SubMenu_Help->Append(MenuOption_Tips, "&Tips");
	SubMenu_Help->Append(MenuOption_About, "&About...");

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

//	CreateDRSControls();

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
	Connect(ToolBar_Open, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnOpen));
	Connect(ToolBar_Save, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnSave));
	Connect(ToolBar_Show, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(ToolBar_Help, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(ToolBar_DRS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(ToolBar_Hex, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(ToolBar_Float, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(ToolBar_Paste, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(ToolBar_AddWindow, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_Prompt, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_IDFix, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_Buttons, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_ShowSLP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_AnimSLP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_ShowShadows, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_ShowOutline, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_ShowDeltas, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_ShowStack, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_ShowAnnexes, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(Units_AutoCopy->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_CopyTo->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::UnitsAutoCopy));
	Connect(Units_SelectAll->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_SelectClear->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_CopyGraphics->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_GraphicSet->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(MenuOption_Tips, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_About, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));

	DataOpened = UseTXT = false;
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;

	wxCommandEvent ShowUnknownsCmd(wxEVT_COMMAND_MENU_SELECTED, ToolBar_Show);
	ShowUnknownsCmd.SetInt(ShowUnknowns);
	ProcessEvent(ShowUnknownsCmd);

	wxCommandEvent ShowButtonsCmd(wxEVT_COMMAND_MENU_SELECTED, MenuOption_Buttons);
	ShowButtonsCmd.SetInt(ShowButtons);
	ProcessEvent(ShowButtonsCmd);

	wxCommandEvent Paste11Cmd(wxEVT_COMMAND_MENU_SELECTED, ToolBar_Paste);
	Paste11Cmd.SetInt(Paste11);
	ProcessEvent(Paste11Cmd);

	if(TimesOpened < 2)
	{
		wxCommandEvent ShowHelpCmd(wxEVT_COMMAND_MENU_SELECTED, ToolBar_Help);
		ProcessEvent(ShowHelpCmd);
	}

	wxCommandEvent ShowSLPCmd(wxEVT_COMMAND_MENU_SELECTED, MenuOption_ShowSLP);
	ShowSLPCmd.SetInt(ShowSLP);
	ProcessEvent(ShowSLPCmd);

	SkipOpenDialog = !PromptForFilesOnOpen;

#ifndef NDEBUG
	genie::Logger::setLogLevel(genie::Logger::L_DEBUG);
	log_out.open("gulog.ini");
	genie::Logger::setGlobalOutputStream(log_out);
#endif

	dataset = NULL;
	Lang = NULL;
	LangX = NULL;
	LangXP = NULL;
	wxToolTip::SetDelay(200);
	wxToolTip::SetAutoPop(32700);
	wxToolTip::SetReshow(1);
}

void AGE_Frame::FixSizes()
{
	SetMinSize(wxSize(MinWindowWidth, 480));
	if(MaxWindowWidth < GetMinSize().GetWidth()) MaxWindowWidth = GetMinSize().GetWidth();
	SetMaxSize(wxSize(MaxWindowWidth, 4096));
}
