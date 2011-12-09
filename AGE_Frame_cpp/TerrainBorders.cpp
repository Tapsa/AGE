/* AGEFrame_cpp/TerrainBorders.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetTerrainBorderName(short Index)
{
	string Name = "";
	if(GenieFile->TerrainBorders[Index].Name == "" && GenieFile->TerrainBorders[Index].Name2 == "")
	{
		Name = "Border "+lexical_cast<string>(Index);
	}
	else
	{
		Name = GenieFile->TerrainBorders[Index].Name;
		Name += " - ";
		Name += GenieFile->TerrainBorders[Index].Name2;
	}
	return Name;
}

void AGE_Frame::ListTerrainBorders()
{
	string Name;
	SearchText = wxString(General_Borders_Search->GetValue()).Lower();
	ExcludeText = wxString(General_Borders_Search_R->GetValue()).Lower();
	string CompareText;

	short Selection = General_Borders_List->GetSelection();

	if(General_Borders_List->GetCount() > 0)
	{
		General_Borders_List->Clear();
	}
	
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	
	for(short loop = 0;loop < GenieFile->TerrainBorders.size();loop++)
	{
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetTerrainBorderName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTerrainBorderName(loop)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			General_Borders_List->Append(Name, (void*)&GenieFile->TerrainBorders[loop]);
		}
	}
	
	General_Borders_List->SetSelection(0);
	General_Borders_List->SetFirstItem(Selection - 3);
	General_Borders_List->SetSelection(Selection);
	
	wxCommandEvent E;
	OnTerrainBordersSelect(E);
}

void AGE_Frame::OnTerrainBordersSearch(wxCommandEvent& Event)
{
	ListTerrainBorders();
}

void AGE_Frame::OnTerrainBordersSelect(wxCommandEvent& Event)
{
	short Selection = General_Borders_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		gdat::TerrainBorder * BorderPointer = (gdat::TerrainBorder*)General_Borders_List->GetClientData(Selection);
		BorderID = BorderPointer - (&GenieFile->TerrainBorders[0]);
		General_BorderName[0]->ChangeValue(BorderPointer->Name);
		General_BorderName[0]->Container = &BorderPointer->Name;
		General_BorderName[1]->ChangeValue(BorderPointer->Name2);
		General_BorderName[1]->Container = &BorderPointer->Name2;
		General_BorderEnabled->ChangeValue(lexical_cast<string>(BorderPointer->Enabled));
		General_BorderEnabled->Container = &BorderPointer->Enabled;
	}
}

void AGE_Frame::OnTerrainBordersCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTerrainBordersPaste(wxCommandEvent& Event)
{

}


string AGE_Frame::GetTerrainBorderFrameName(short Index, short BorderID)
{

}

void AGE_Frame::ListTerrainBorderFrames(short Index)
{

}

void AGE_Frame::OnTerrainBorderFramesSearch(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTerrainBorderFramesSelect(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTerrainBorderFramesCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTerrainBorderFramesPaste(wxCommandEvent& Event)
{

}

void AGE_Frame::CreateTerrainBorderControls()
{
	Tab_TerrainBorders = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	Borders_Main = new wxBoxSizer(wxHORIZONTAL);
	General_Borders_Buttons = new wxGridSizer(2, 0, 0);
	General_Borders = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Terrain Border slot");
	General_Borders_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	General_Borders_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	General_Borders_List = new wxListBox(Tab_TerrainBorders, wxID_ANY, wxDefaultPosition, wxSize(-1, 220));
	Borders_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Borders_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));
	General_DataArea = new wxBoxSizer(wxVERTICAL);
	General_DataTopRow = new wxBoxSizer(wxHORIZONTAL);
	General_Holder_BorderEnabled = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderEnabled = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Enabled", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderEnabled = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	for(short loop = 0;loop < 2;loop++)
	{
		General_Holder_BorderName[loop] = new wxBoxSizer(wxVERTICAL);
		General_BorderName[loop] = new TextCtrl_String(Tab_TerrainBorders, "0", NULL);
	}
	General_Text_BorderName[0] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Name", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Text_BorderName[1] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " SLP Name ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Connect(General_Borders_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSearch));
	Connect(General_Borders_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSearch));
	Connect(General_Borders_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSelect));
	Connect(Borders_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersCopy));
	Connect(Borders_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersPaste));
	
	for(short loop = 0;loop < 2;loop++)
	{
		General_Holder_BorderName[loop]->Add(General_Text_BorderName[loop], 0, wxEXPAND);
		General_Holder_BorderName[loop]->Add(General_BorderName[loop], 0, wxEXPAND);
	}
	General_Holder_BorderEnabled->Add(General_Text_BorderEnabled, 0, wxEXPAND);
	General_Holder_BorderEnabled->Add(General_BorderEnabled, 0, wxEXPAND);

	General_Borders_Buttons->Add(Borders_Copy, 1, wxEXPAND);
	General_Borders_Buttons->Add(Borders_Paste, 1, wxEXPAND);

	General_Borders->Add(-1, 10);
	General_Borders->Add(General_Borders_Search, 0, wxEXPAND);
	General_Borders->Add(General_Borders_Search_R, 0, wxEXPAND);
	General_Borders->Add(-1, 2);
	General_Borders->Add(General_Borders_List, 1, wxEXPAND);
	General_Borders->Add(-1, 2);
	General_Borders->Add(General_Borders_Buttons, 0, wxEXPAND);
	General_Borders->Add(-1, 10);
	
	General_DataTopRow->Add(General_Holder_BorderName[0], 1, wxEXPAND);
	General_DataTopRow->Add(5, -1);
	General_DataTopRow->Add(General_Holder_BorderName[1], 1, wxEXPAND);
	General_DataTopRow->Add(5, -1);
	General_DataTopRow->Add(General_Holder_BorderEnabled, 1, wxEXPAND);

	General_DataArea->Add(-1, 10);
	General_DataArea->Add(General_DataTopRow, 0, wxEXPAND);
	General_DataArea->Add(-1, 5);
	General_DataArea->Add(-1, 10);
	
	Borders_Main->Add(10, -1);
	Borders_Main->Add(General_Borders, 1, wxEXPAND);
	Borders_Main->Add(10, -1);
	Borders_Main->Add(General_DataArea, 3, wxEXPAND);
	Borders_Main->Add(10, -1);
	
	Tab_TerrainBorders->SetSizer(Borders_Main);

	for(short loop = 0;loop < 2;loop++)
	General_BorderName[loop]->Connect(General_BorderName[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);

}