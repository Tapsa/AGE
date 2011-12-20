/* AGEFrame_cpp/Constructor.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include "../AppIcon.xpm"
#include "../Villie.xpm"
#include "../Tech.xpm"
#include "../TC.xpm"
#include "../AoK.xpm"
#include "../GateOpen.xpm"
#include "../GateClosed.xpm"

AGE_Frame::AGE_Frame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(0, 20))
{
	SetIcon(wxIcon(AppIcon_xpm));
	wxBusyCursor WaitCursor;
	TabBar_Main = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Config = new wxFileConfig("AdvancedGenieEditor", wxEmptyString, "age2config.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	Config->Read("Interaction/PromptForFilesOnOpen", &PromptForFilesOnOpen, true);
	Config->Read("Interaction/AutoCopyToAllCivs", (long*)&AutoCopy, MenuOption_Exclude);
	Config->Read("Interaction/ExtraSearchFilters", (long*)&SearchFilters, MenuOption_2ndFilters);
	Config->Read("Interface/ShowUnknowns", &ShowUnknowns, true);
	Config->Read("Interface/ShowButtons", &ShowButtons, false);
	Config->Read("DefaultFiles/DriveLetter", &DriveLetter, wxT("C"));
	Config->Read("DefaultFiles/Version", &GameVersion, 3);
	Config->Read("DefaultFiles/SaveVersion", &SaveGameVersion, 3);
	Config->Read("DefaultFiles/DatUsed", &DatUsed, 0);
	Config->Read("DefaultFiles/DatFilename", &DatFileName, wxT(""));
	Config->Read("DefaultFiles/ApfFilename", &ApfFileName, wxT(""));
	Config->Read("DefaultFiles/SaveDatFilename", &SaveDatFileName, wxT(""));
	Config->Read("DefaultFiles/SaveApfFilename", &SaveApfFileName, wxT(""));
	Config->Read("DefaultFiles/LangsUsed", &LangsUsed, 7);
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

	GetToolBar()->Realize();

	MenuBar_Main = new wxMenuBar();

	SubMenu_Options = new wxMenu();
	SubMenu_Options->AppendCheckItem(MenuOption_Prompt, "&Prompt for files on open");
	SubMenu_Options->Check(MenuOption_Prompt, PromptForFilesOnOpen);
	SubMenu_Options->AppendCheckItem(MenuOption_Unknowns, "Show &unknowns");
	SubMenu_Options->Check(MenuOption_Unknowns, ShowUnknowns);
	SubMenu_Options->AppendCheckItem(MenuOption_Buttons, "Enable forbidden &buttons");
	SubMenu_Options->Check(MenuOption_Buttons, ShowButtons);

	SubMenu_SearchFilters = new wxMenu();
	SubMenu_SearchFilters->AppendRadioItem(MenuOption_NoExtra, "&Default");
	SubMenu_SearchFilters->AppendRadioItem(MenuOption_1stFilters, "&1st filters");
	SubMenu_SearchFilters->AppendRadioItem(MenuOption_2ndFilters, "&2nd filters");
	SubMenu_SearchFilters->Check(SearchFilters, true);

	SubMenu_Options->AppendSubMenu(SubMenu_SearchFilters, "Additional &filters [| to separate]");

	SubMenu_CivAutoCopy = new wxMenu();
	SubMenu_CivAutoCopy->AppendRadioItem(MenuOption_NoAuto, "&Disabled");
	SubMenu_CivAutoCopy->AppendRadioItem(MenuOption_Include, "&Include graphics");
	SubMenu_CivAutoCopy->AppendRadioItem(MenuOption_Exclude, "&Exclude graphics");
	SubMenu_CivAutoCopy->Check(AutoCopy, true);

	SubMenu_Options->AppendSubMenu(SubMenu_CivAutoCopy, "&Auto-copy to all civilizations");

	SubMenu_Help = new wxMenu();
	SubMenu_Help->Append(MenuOption_Tips, "&Tips");
	SubMenu_Help->Append(MenuOption_About, "&About...");

	MenuBar_Main->Append(SubMenu_Options, "&Options");
	MenuBar_Main->Append(SubMenu_Help, "&Help");

	this->SetMenuBar(MenuBar_Main);

	CreateUnitControls();
	CreateResearchControls();
	CreateTechageControls();
	CreateCivControls();
	CreateGraphicsControls();
	CreateTerrainControls();
	CreateTerrainRestrictionControls();
	CreateSoundControls();
	CreatePlayerColorControls();
	CreateUnitLineControls();
	CreateTerrainBorderControls();
	CreateGeneralControls();

	TabBar_Main->AddPage(Tab_General, "General");
	TabBar_Main->AddPage(Tab_Research, "Researches");
	TabBar_Main->AddPage(Tab_Techage, "Technologies");
	TabBar_Main->AddPage(Tab_Civs, "Civilizations");
	TabBar_Main->AddPage(Tab_Units, "Units");
	TabBar_Main->AddPage(Tab_UnitLine, "Unitline");
	TabBar_Main->AddPage(Tab_Graphics, "Graphics");
	TabBar_Main->AddPage(Tab_Terrains, "Terrains");
	TabBar_Main->AddPage(Tab_TerrainBorders, "Terrain Borders");
	TabBar_Main->AddPage(Tab_TerrainRestrictions, "Terrain Restrictions");
	TabBar_Main->AddPage(Tab_Sounds, "Sounds");
	TabBar_Main->AddPage(Tab_PlayerColors, "Player Colors");
	TabBar_Main->SetSelection(4);

	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(AGE_Frame::OnExit));
	Connect(ToolBar_Open, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnOpen));
	Connect(ToolBar_Save, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnSave));
	Connect(MenuOption_Prompt, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_Unknowns, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_Buttons, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_NoAuto, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_Include, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_Exclude, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_Tips, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_About, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_NoExtra, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_1stFilters, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));
	Connect(MenuOption_2ndFilters, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AGE_Frame::OnMenuOption));

	DataOpened = false;
	wxCommandEvent ShowUnknownsCommand(wxEVT_COMMAND_MENU_SELECTED, MenuOption_Unknowns);
	ShowUnknownsCommand.SetId(MenuOption_Unknowns);
	ShowUnknownsCommand.SetInt(ShowUnknowns);
	ProcessEvent(ShowUnknownsCommand);
	
	wxCommandEvent ShowButtonsCommand(wxEVT_COMMAND_MENU_SELECTED, MenuOption_Buttons);
	ShowButtonsCommand.SetId(MenuOption_Buttons);
	ShowButtonsCommand.SetInt(ShowButtons);
	ProcessEvent(ShowButtonsCommand);

	NeedDat = true;
	if(!PromptForFilesOnOpen)
	{
		SkipOpenDialog = true;
	}

	GenieFile = NULL;
//	wxToolTip::SetAutoPop(300000);
}
