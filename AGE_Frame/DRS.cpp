
#include "../AGE_Frame.h"
using boost::lexical_cast;

wxTextCtrl * DRS_SLP;

void AGE_Frame::LoadDRSFile(wxCommandEvent &Event)
{
	ResourceFile = new genie::DrsFile();
	try
	{
		ResourceFile->setGameVersion(GenieFile->getGameVersion());
		ResourceFile->load(DRS_Path_FileLocation->GetPath().c_str());
		DRS_StatusText->SetLabel("DRS file loaded.");
	}
	catch(std::ios_base::failure e)
	{
		delete ResourceFile;
		wxMessageBox("Unable to load the file!");
		DRS_StatusText->SetLabel("Loading failed.");
		return;
	}
}

void AGE_Frame::UnLoadDRSFile(wxCommandEvent &Event)
{
	delete ResourceFile;
	ResourceFile = 0;
	DRS_StatusText->SetLabel("DRS file unloaded.");
}

void AGE_Frame::LoadSLP(wxCommandEvent &Event)
{
	genie::DrsFile Interface, GameData;

	Interface.setGameVersion(GenieFile->getGameVersion());
	GameData.setGameVersion(GenieFile->getGameVersion());
	try
	{
		Interface.load("C:/Program Files (x86)/Microsoft Games/Age of Empires II/DATA/interfac.drs");
		GameData.load("C:/Program Files (x86)/Microsoft Games/Age of Empires II/DATA/gamedata_x1_p1.drs");
	}
	catch(...)
	{
		wxMessageBox("An error happened.");
	}

	genie::PalFilePtr Palette = Interface.getPalFile(50500);

	DRS_SLP->ChangeValue("5220");
	int32_t SLP = lexical_cast<int32_t>(DRS_SLP->GetValue());
	genie::SlpFilePtr SLP_Pointer = GameData.getSlpFile(SLP);
	/*sf::Texture SLP_Texture;
	SLP_Texture.loadFromImage(createSfImage(SLP_Pointer->getFrame(1), Palette));
	sf::Sprite SLP_Sprite(SLP_Texture);*/

	DRS_StatusText->SetLabel("SLP "+SLP+" loaded.");
}

void AGE_Frame::CreateDRSControls()
{
	Tab_DRS = new wxPanel(TabBar_Test, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	DRS_Main = new wxBoxSizer(wxVERTICAL);
	DRS_TopRow = new wxBoxSizer(wxHORIZONTAL);
	DRS_MidArea = new wxBoxSizer(wxHORIZONTAL);

	DRS_Text_FileLocation = new wxStaticText(Tab_DRS, wxID_ANY, "      DRS File (*.drs):");
	DRS_Path_FileLocation = new wxFilePickerCtrl(Tab_DRS, wxID_ANY, "", "Select a file", "DRS File (*.drs)|*.drs", wxDefaultPosition, wxSize(300, 20), wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	DRS_LoadButton = new wxButton(Tab_DRS, wxID_ANY, "Load DRS File");
	DRS_UnLoadButton = new wxButton(Tab_DRS, wxID_ANY, "Unload DRS File");
	DRS_StatusText = new wxStaticText(Tab_DRS, wxID_ANY, "Awaiting user...");
	DRS_SLP = new wxTextCtrl(Tab_DRS, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20));
	DRS_SLPLoadButton = new wxButton(Tab_DRS, wxID_ANY, "Load SLP");

	DRS_TopRow->Add(10, -1);
	DRS_TopRow->Add(DRS_Text_FileLocation, 0, wxEXPAND);
	DRS_TopRow->Add(5, -1);
	DRS_TopRow->Add(DRS_Path_FileLocation, 1, wxEXPAND);
	DRS_TopRow->Add(5, -1);
	DRS_TopRow->Add(DRS_LoadButton, 0, wxEXPAND);
	DRS_TopRow->Add(5, -1);
	DRS_TopRow->Add(DRS_UnLoadButton, 0, wxEXPAND);
	DRS_TopRow->Add(10, -1);

	DRS_MidArea->Add(10, -1);
	DRS_MidArea->Add(DRS_SLP, 0, wxEXPAND);
	DRS_MidArea->Add(5, -1);
	DRS_MidArea->Add(DRS_SLPLoadButton, 0, wxEXPAND);
	DRS_MidArea->Add(5, -1);
	DRS_MidArea->Add(DRS_StatusText, 1, wxEXPAND);
	DRS_MidArea->Add(10, -1);

	DRS_Main->Add(-1, 10);
	DRS_Main->Add(DRS_TopRow, 0, wxEXPAND);
	DRS_Main->Add(-1, 5);
	DRS_Main->Add(DRS_MidArea, 0, wxEXPAND);
	DRS_Main->Add(-1, 10);

	Tab_DRS->SetSizer(DRS_Main);

	Connect(DRS_LoadButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::LoadDRSFile));
	Connect(DRS_UnLoadButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::UnLoadDRSFile));
	Connect(DRS_SLPLoadButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::LoadSLP));
}
