#include "../AGE_Frame.h"
#include "genie/util/Logger.h"

//#include <wx/arrimpl.cpp>
using boost::lexical_cast;

AGE_Frame::AGE_Frame(const wxString &title, Copies &c, short window)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(0, 20))
{
	SetIcon(wxIcon(AppIcon_xpm));
	wxBusyCursor WaitCursor;
	TabBar_Main = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
//	TabBar_Data = new wxNotebook(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
//	TabBar_Test = new wxNotebook(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	copies = &c;
	AGEwindow = window;

	Config = new wxFileConfig(wxEmptyString, "Tapsa", "age2configw"+lexical_cast<string>(AGEwindow)+".ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	Config->Read("Interaction/PromptForFilesOnOpen", &PromptForFilesOnOpen, true);
	//Config->Read("Interaction/AutoCopyToAllCivs", (long*)&AutoCopy, MenuOption_Exclude);
	Config->Read("Interaction/AutoCopy", &AutoCopy, true);
	Config->Read("Interaction/CopyGraphics", &CopyGraphics, false);
	Config->Read("Interaction/AllCivs", &AllCivs, true);
	Config->Read("Interaction/EnableIDFix", &EnableIDFix, true);
	Config->Read("Interface/ShowUnknowns", &ShowUnknowns, true);
	Config->Read("Interface/ShowButtons", &ShowButtons, false);
	if(AGEwindow == 1) Config->Read("DefaultFiles/SimultaneousFiles", &SimultaneousFiles, 2); // 2 to showcase this feature.
	Config->Read("DefaultFiles/DriveLetter", &DriveLetter, wxT("C"));
	Config->Read("DefaultFiles/Version", &GameVersion, 3);
	Config->Read("DefaultFiles/SaveVersion", &SaveGameVersion, 3);
	Config->Read("DefaultFiles/DatUsed", &DatUsed, 0);
	Config->Read("DefaultFiles/DatFilename", &DatFileName, wxT(""));
	Config->Read("DefaultFiles/ApfFilename", &ApfFileName, wxT(""));
	Config->Read("DefaultFiles/SaveDatFilename", &SaveDatFileName, wxT(""));
	Config->Read("DefaultFiles/SaveApfFilename", &SaveApfFileName, wxT(""));
	Config->Read("DefaultFiles/LangsUsed", &LangsUsed, 7);
	Config->Read("DefaultFiles/WriteLangs", &WriteLangs, false);
	Config->Read("DefaultFiles/LangWriteMode", &LangWriteMode, 1);
	Config->Read("DefaultFiles/LangFilename", &LangFileName, wxT(""));
	Config->Read("DefaultFiles/LangX1Filename", &LangX1FileName, wxT(""));
	Config->Read("DefaultFiles/LangX1P1Filename", &LangX1P1FileName, wxT(""));
	Config->Read("DefaultFiles/SaveDat", &SaveDat, true);
	Config->Read("DefaultFiles/SaveApf", &SaveApf, false);
	delete Config;

	CreateToolBar(wxTB_HORIZONTAL | wxTB_TEXT);
	CreateStatusBar();

	GetToolBar()->AddTool(ToolBar_Open, "Open", wxBitmap(GateOpen_xpm), "Opens the open dialog");
	GetToolBar()->AddTool(ToolBar_Save, "Save", wxBitmap(GateClosed_xpm), "Opens the save dialog");
	GetToolBar()->AddTool(ToolBar_Show, "Show", wxBitmap(Question_xpm), "Show unknowns", wxITEM_CHECK);
	GetToolBar()->AddTool(ToolBar_CustomNames, "Lists", wxNullBitmap, "Extract a setting file for custom names in some lists\nRestart this program after editing the file");
	GetToolBar()->ToggleTool(ToolBar_Show, ShowUnknowns);
	GetToolBar()->Realize();
	
	MenuBar_Main = new wxMenuBar();

	SubMenu_Options = new wxMenu();
	SubMenu_Options->AppendCheckItem(MenuOption_Prompt, "&Prompt for files on open");
	SubMenu_Options->Check(MenuOption_Prompt, PromptForFilesOnOpen);
	SubMenu_Options->AppendCheckItem(MenuOption_Buttons, "Enable forbidden &buttons");
	SubMenu_Options->Check(MenuOption_Buttons, ShowButtons);
	/*SubMenu_Options->AppendCheckItem(MenuOption_Undo, "Use &undo function");
	SubMenu_Options->Check(MenuOption_Undo, UseUndo);

	SubMenu_SearchFilters = new wxMenu();
	SubMenu_SearchFilters->AppendRadioItem(MenuOption_NoExtra, "&Default");
	SubMenu_SearchFilters->AppendRadioItem(MenuOption_1stFilters, "&1st filters");
	SubMenu_SearchFilters->AppendRadioItem(MenuOption_2ndFilters, "&2nd filters");
	SubMenu_SearchFilters->Check(SearchFilters, true);

	SubMenu_Options->AppendSubMenu(SubMenu_SearchFilters, "Additional &filters [| to separate]");*/

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
	CreateTechageControls();
	CreateTechTreeControls();
	CreateGraphicsControls();
	CreateTerrainControls();
	CreateTerrainRestrictionControls();
	CreateSoundControls();
	CreatePlayerColorControls();
	CreateUnitLineControls();
	CreateTerrainBorderControls();
	CreateGeneralControls();
	
//	CreateDRSControls();
	
	Units_AutoCopy->SetValue(AutoCopy);
	Units_CopyGraphics->SetValue(CopyGraphics);
	Units_CopyTo->Enable(!AutoCopy);
	Units_SpecialCopy_Civs->SetValue(AllCivs);

//	TabBar_Main->AddPage(TabBar_Data, "Data");
//	TabBar_Main->AddPage(TabBar_Test, "Test");

	TabBar_Main->AddPage(Tab_General, "General");
	TabBar_Main->AddPage(Tab_Research, "Researches");
	TabBar_Main->AddPage(Tab_Techs, "Technologies");
	TabBar_Main->AddPage(Tab_TechTrees, "Tech. Trees");
	TabBar_Main->AddPage(Tab_Civs, "Civilizations");
	TabBar_Main->AddPage(Tab_Units, "Units");
	TabBar_Main->AddPage(Tab_UnitLine, "Unitline");
	TabBar_Main->AddPage(Tab_Graphics, "Graphics");
	TabBar_Main->AddPage(Tab_Terrains, "Terrains");
	TabBar_Main->AddPage(Tab_TerrainBorders, "Terrain Borders");
	TabBar_Main->AddPage(Tab_TerrainRestrictions, "Terrain Restrictions");
	TabBar_Main->AddPage(Tab_Sounds, "Sounds");
	TabBar_Main->AddPage(Tab_PlayerColors, "Player Colors");
	TabBar_Main->SetSelection(5);
	
//	TabBar_Test->AddPage(Tab_DRS, "DRS Files");
//	TabBar_Test->SetSelection(0);

	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(AGE_Frame::OnExit));
	Connect(ToolBar_Open, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnOpen));
	Connect(ToolBar_Save, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnSave));
	Connect(ToolBar_Show, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(ToolBar_CustomNames, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_Prompt, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_IDFix, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_Buttons, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(Units_AutoCopy->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_CopyTo->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_SelectAll->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_SelectClear->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_CopyGraphics->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(Units_GraphicSet->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
	Connect(MenuOption_Tips, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_About, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));

	DataOpened = false;
	PopupCivWarning = true;
	for(short loop=0; loop < 2; loop++)
	UseAnd[loop] = false;
	
	wxCommandEvent ShowButtonsCommand(wxEVT_COMMAND_MENU_SELECTED, MenuOption_Buttons);
	ShowButtonsCommand.SetId(MenuOption_Buttons);
	ShowButtonsCommand.SetInt(ShowButtons);
	ProcessEvent(ShowButtonsCommand);

	/*wxCommandEvent UseUndoCommand(wxEVT_COMMAND_MENU_SELECTED, MenuOption_Undo);
	UseUndoCommand.SetId(MenuOption_Undo);
	UseUndoCommand.SetInt(UseUndo);
	ProcessEvent(UseUndoCommand);*/

	NeedDat = true;
	if(!PromptForFilesOnOpen)
	{
		SkipOpenDialog = true;
	}
	else SkipOpenDialog = false;

	genie::Logger::setLogLevel(genie::Logger::L_INFO);
	static std::ofstream log_out;
	log_out.open("gulog.txt");
	genie::Logger::setGlobalOutputStream(log_out);
	GenieFile = NULL;
	Lang = NULL;
	LangX = NULL;
	LangXP = NULL;
	wxToolTip::SetDelay(200);
	wxToolTip::SetAutoPop(32700);
	wxToolTip::SetReshow(1);

	// Let's create our SFML view
    // new MyCanvas(this, wxID_ANY, wxPoint(50, 50), wxSize(700, 500));
}

//Working stuff if you need custom wxArrays. I'll just use standard vectors instead.
//WX_DEFINE_OBJARRAY(wxArrayFloat);
//WX_DEFINE_OBJARRAY(ArrayCivCopy);
//WX_DEFINE_OBJARRAY(ArrayPlayerColour);
