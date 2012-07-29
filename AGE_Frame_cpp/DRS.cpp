/* AGEFrame_cpp/DRS.cpp */

#include "../AGE_Frame.h"
using boost::lexical_cast;

void AGE_Frame::LoadDRSFile(wxCommandEvent& Event)
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

void AGE_Frame::UnLoadDRSFile(wxCommandEvent& Event)
{
	delete ResourceFile;
	ResourceFile = 0;
	DRS_StatusText->SetLabel("DRS file unloaded.");
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
}
