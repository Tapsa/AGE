#include "../AGE_Frame.h"
#include "../AppIcon.xpm"
#include "../GateOpen.xpm"
#include "../GateClosed.xpm"
#include "../Question.xpm"
#include "../Ox.xpm"
#include "../float.xpm"
//#include "genie/util/Logger.h"

AGE_Frame::AGE_Frame(const wxString &title, wxString &aP, Copies &c, short window)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(0, 20))
{
	SetIcon(wxIcon(AppIcon_xpm));
	wxBusyCursor WaitCursor;
	TabBar_Main = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	copies = &c;
	argPath = &aP;
	AGEwindow = window;

	Config = new wxFileConfig(wxEmptyString, "Tapsa", "age2configw"+lexical_cast<string>(AGEwindow)+".ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	Config->Read("/EditorVersion", &EditorVersionString, AGE_AboutDialog::AGE_VER);
	sscanf(EditorVersionString, "%f", &EditorVersion);
	Config->Read("/TimesOpened", &TimesOpened, 0);
	if(EditorVersionString != AGE_AboutDialog::AGE_VER) TimesOpened = 0;
	Config->Read("Interaction/PromptForFilesOnOpen", &PromptForFilesOnOpen, true);
	Config->Read("Interaction/AutoCopy", &AutoCopy, true);
	Config->Read("Interaction/CopyGraphics", &CopyGraphics, false);
	Config->Read("Interaction/AllCivs", &AllCivs, true);
	Config->Read("Interaction/EnableIDFix", &EnableIDFix, true);
	Config->Read("Interface/ShowUnknowns", &ShowUnknowns, true);
	Config->Read("Interface/ShowButtons", &ShowButtons, false);
	Config->Read("Interface/MaxWindowWidth", &MaxWindowWidth, 900);
	if(AGEwindow == 1) Config->Read("DefaultFiles/SimultaneousFiles", &SimultaneousFiles, 2); // 2 to showcase this feature.
	Config->Read("DefaultFiles/DriveLetter", &DriveLetter, wxT("C"));
	Config->Read("DefaultFiles/UseCustomPath", &UseCustomPath, false);
	Config->Read("DefaultFiles/CustomFolder", &CustomFolder, wxT(""));
	Config->Read("DefaultFiles/Version", &GameVersion, genie::GV_TC);
	Config->Read("DefaultFiles/SaveVersion", &SaveGameVersion, 3);
	Config->Read("DefaultFiles/DatUsed", &DatUsed, 0);
	Config->Read("DefaultFiles/DatFilename", &DatFileName, wxT(""));
	Config->Read("DefaultFiles/SaveDatFilename", &SaveDatFileName, wxT(""));
	Config->Read("DefaultFiles/LangsUsed", &LangsUsed, 7);
	Config->Read("DefaultFiles/WriteLangs", &WriteLangs, false);
	Config->Read("DefaultFiles/SaveLangs", &SaveLangs, false);
	Config->Read("DefaultFiles/LangWriteToLatest", &LangWriteToLatest, false);
	Config->Read("DefaultFiles/Language", &Language, wxT("en"));
	Config->Read("DefaultFiles/LangCharset", &LangCharset, wxT("Windows-1252"));
	Config->Read("DefaultFiles/LangFilename", &LangFileName, wxT(""));
	Config->Read("DefaultFiles/LangX1Filename", &LangX1FileName, wxT(""));
	Config->Read("DefaultFiles/LangX1P1Filename", &LangX1P1FileName, wxT(""));
	Config->Read("DefaultFiles/SaveLangFilename", &SaveLangFileName, wxT(""));
	Config->Read("DefaultFiles/SaveLangX1Filename", &SaveLangX1FileName, wxT(""));
	Config->Read("DefaultFiles/SaveLangX1P1Filename", &SaveLangX1P1FileName, wxT(""));
	Config->Read("DefaultFiles/SaveDat", &SaveDat, true);
	Config->Read("DefaultFiles/AutoBackups", &AutoBackups, false);

	Config->Write("/EditorVersion", AGE_AboutDialog::AGE_VER);
	Config->Write("/TimesOpened", ++TimesOpened);
	delete Config;

	SetMinSize(wxSize(900, 480));
	SetMaxSize(wxSize(MaxWindowWidth, 4096));
	CreateToolBar(wxTB_HORIZONTAL | wxTB_TEXT);
	CreateStatusBar()->SetFieldsCount(3);

	GetToolBar()->AddTool(ToolBar_Open, "Open", wxBitmap(GateOpen_xpm), "Opens the open dialog");
	GetToolBar()->AddTool(ToolBar_Save, "Save", wxBitmap(GateClosed_xpm), "Opens the save dialog");
	GetToolBar()->AddTool(ToolBar_Show, "Show", wxBitmap(Question_xpm), "Show unknowns", wxITEM_CHECK);
	GetToolBar()->AddTool(ToolBar_Hex, "Hex", wxBitmap(Ox_xpm), "Toggle hex mode (data not editable)", wxITEM_CHECK);
	GetToolBar()->AddTool(ToolBar_Float, "0001", wxBitmap(float_xpm), "Toggle float display mode", wxITEM_CHECK);
	GetToolBar()->AddTool(ToolBar_Help, "Help", wxBitmap(Question_xpm), "Show help");
	GetToolBar()->ToggleTool(ToolBar_Show, ShowUnknowns);
	GetToolBar()->Realize();

	MenuBar_Main = new wxMenuBar();

	SubMenu_Options = new wxMenu();
	SubMenu_Options->AppendCheckItem(MenuOption_Prompt, "&Prompt for files on open");
	SubMenu_Options->Check(MenuOption_Prompt, PromptForFilesOnOpen);
	SubMenu_Options->AppendCheckItem(MenuOption_Buttons, "Enable forbidden &buttons");
	SubMenu_Options->Check(MenuOption_Buttons, ShowButtons);

	SubMenu_Options->AppendCheckItem(MenuOption_IDFix, "Enable &index fixes");
	SubMenu_Options->Check(MenuOption_IDFix, EnableIDFix);
	SubMenu_Options->Enable(MenuOption_IDFix, false);

	SubMenu_Help = new wxMenu();
	SubMenu_Help->Append(MenuOption_Tips, "&Tips");
	SubMenu_Help->Append(MenuOption_About, "&About...");

	MenuBar_Main->Append(SubMenu_Options, "&Options");
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
	TabBar_Main->AddPage(Tab_General, "General");
	TabBar_Main->AddPage(Tab_Terrains, "Terrains");
	TabBar_Main->AddPage(Tab_TerrainBorders, "T. Borders");
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
	Connect(ToolBar_Hex, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(ToolBar_Float, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_Prompt, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_IDFix, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_Buttons, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(Units_AutoCopy->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_CopyTo->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::UnitsAutoCopy));
	Connect(Units_SelectAll->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_SelectClear->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_CopyGraphics->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_GraphicSet->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(MenuOption_Tips, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_About, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));

	DataOpened = false;
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;

	wxCommandEvent ShowUnknownsCmd(wxEVT_COMMAND_MENU_SELECTED, ToolBar_Show);
	ShowUnknownsCmd.SetInt(ShowUnknowns);
	ProcessEvent(ShowUnknownsCmd);

	wxCommandEvent ShowButtonsCmd(wxEVT_COMMAND_MENU_SELECTED, MenuOption_Buttons);
	ShowButtonsCmd.SetInt(ShowButtons);
	ProcessEvent(ShowButtonsCmd);

	if(TimesOpened < 2)
	{
		wxCommandEvent ShowHelpCmd(wxEVT_COMMAND_MENU_SELECTED, ToolBar_Help);
		ProcessEvent(ShowHelpCmd);
	}

	NeedDat = true;
	SkipOpenDialog = !PromptForFilesOnOpen;

	//genie::Logger::setLogLevel(genie::Logger::L_INFO);
	//static std::ofstream log_out;
	//log_out.open("gulog.ini");
	//genie::Logger::setGlobalOutputStream(log_out);
	GenieFile = NULL;
	Lang = NULL;
	LangX = NULL;
	LangXP = NULL;
	wxToolTip::SetDelay(200);
	wxToolTip::SetAutoPop(32700);
	wxToolTip::SetReshow(1);
	AGETextCtrl::editable = false;
	AGETextCtrl::hexMode = false;
	AGETextCtrl::accurateFloats = false;
	AGETextCtrl::unSaved = 0;
}
