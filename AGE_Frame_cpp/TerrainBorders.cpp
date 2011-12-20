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

void AGE_Frame::OnTerrainBordersSearch(wxCommandEvent& Event)
{
	ListTerrainBorders();
}

void AGE_Frame::ListTerrainBorders()
{
	string Name;
	SearchText = wxString(Borders_Borders_Search->GetValue()).Lower();
	ExcludeText = wxString(Borders_Borders_Search_R->GetValue()).Lower();
	string CompareText;

	short Selection = Borders_Borders_List->GetSelection();

	if(Borders_Borders_List->GetCount() > 0)
	{
		Borders_Borders_List->Clear();
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
			Borders_Borders_List->Append(Name, (void*)&GenieFile->TerrainBorders[loop]);
		}
	}
	
	Borders_Borders_List->SetSelection(0);
	Borders_Borders_List->SetFirstItem(Selection - 3);
	Borders_Borders_List->SetSelection(Selection);
	
	wxCommandEvent E;
	OnTerrainBordersSelect(E);
}

void AGE_Frame::OnTerrainBordersSelect(wxCommandEvent& Event)
{
	short Selection = Borders_Borders_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		gdat::TerrainBorder * BorderPointer = (gdat::TerrainBorder*)Borders_Borders_List->GetClientData(Selection);
		BorderID = BorderPointer - (&GenieFile->TerrainBorders[0]);
		Borders_BorderName[0]->ChangeValue(BorderPointer->Name);
		Borders_BorderName[0]->Container = &BorderPointer->Name;
		Borders_BorderName[1]->ChangeValue(BorderPointer->Name2);
		Borders_BorderName[1]->Container = &BorderPointer->Name2;
		Borders_BorderEnabled->ChangeValue(lexical_cast<string>(BorderPointer->Enabled));
		Borders_BorderEnabled->Container = &BorderPointer->Enabled;
		Borders_CheckBox_BorderEnabled->SetValue((bool)BorderPointer->Enabled);
		Borders_BorderRessourceID->ChangeValue(lexical_cast<string>(BorderPointer->RessourceID));
		Borders_BorderRessourceID->Container = &BorderPointer->RessourceID;
		Borders_BorderUnknown3->ChangeValue(lexical_cast<string>(BorderPointer->Unknown3));
		Borders_BorderUnknown3->Container = &BorderPointer->Unknown3;
		Borders_BorderUnknown4->ChangeValue(lexical_cast<string>(BorderPointer->Unknown4));
		Borders_BorderUnknown4->Container = &BorderPointer->Unknown4;
		for(short loop = 0;loop < 3;loop++)
		{
			Borders_BorderColors[loop]->ChangeValue(lexical_cast<string>((short)BorderPointer->Colors[loop]));
			Borders_BorderColors[loop]->Container = &BorderPointer->Colors[loop];
		}
		Borders_BorderUnknown5->ChangeValue(lexical_cast<string>((short)BorderPointer->Unknown5));
		Borders_BorderUnknown5->Container = &BorderPointer->Unknown5;
		Borders_BorderUnknown6->ChangeValue(lexical_cast<string>(BorderPointer->Unknown6));
		Borders_BorderUnknown6->Container = &BorderPointer->Unknown6;
		Borders_BorderUnknown7->ChangeValue(lexical_cast<string>(BorderPointer->Unknown7));
		Borders_BorderUnknown7->Container = &BorderPointer->Unknown7;
		Borders_BorderFrameCount->ChangeValue(lexical_cast<string>(BorderPointer->FrameCount));
		Borders_BorderFrameCount->Container = &BorderPointer->FrameCount;
		Borders_BorderUnknown8->ChangeValue(lexical_cast<string>(BorderPointer->Unknown8));
		Borders_BorderUnknown8->Container = &BorderPointer->Unknown8;
		Borders_BorderTerrain->ChangeValue(lexical_cast<string>(BorderPointer->Unknown9));
		Borders_BorderTerrain->Container = &BorderPointer->Unknown9;
		Borders_ComboBox_BorderTerrain->SetSelection(BorderPointer->Unknown9 + 1);
		Borders_BorderUnknown10->ChangeValue(lexical_cast<string>(BorderPointer->Unknown10));
		Borders_BorderUnknown10->Container = &BorderPointer->Unknown10;
		ListTerrainBorderFrames(BorderID);
	}
}

void AGE_Frame::OnTerrainBordersCopy(wxCommandEvent& Event)
{
	short Selection = Borders_Borders_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TerrainBorderCopy = *(gdat::TerrainBorder*)Borders_Borders_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnTerrainBordersPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Borders_Borders_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::TerrainBorder*)Borders_Borders_List->GetClientData(Selection) = TerrainBorderCopy;
		ListTerrainBorders();
	}
}

string AGE_Frame::GetTerrainBorderFrameName(short Index, short BorderID)
{
	string Name = "";
	Name = "Frame ";
	Name += lexical_cast<string>(GenieFile->TerrainBorders[BorderID].Frames[Index].FrameID);
	Name += " - Flags ";
	Name += lexical_cast<string>(GenieFile->TerrainBorders[BorderID].Frames[Index].Flag1);
	Name += " ";
	Name += lexical_cast<string>(GenieFile->TerrainBorders[BorderID].Frames[Index].Flag2);
	return Name;
}

void AGE_Frame::OnTerrainBorderFramesSearch(wxCommandEvent& Event)
{
	ListTerrainBorderFrames(BorderID);
}

void AGE_Frame::ListTerrainBorderFrames(short Index)
{
	string Name;
	SearchText = wxString(Borders_Frames_Search->GetValue()).Lower();
	ExcludeText = wxString(Borders_Frames_Search_R->GetValue()).Lower();
	string CompareText;

	short Selection = Borders_Frames_List->GetSelection();

	if(Borders_Frames_List->GetCount() > 0)
	{
		Borders_Frames_List->Clear();
	}
	
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	
	for(short loop = 0;loop < GenieFile->TerrainBorders[Index].Frames.size();loop++)
	{
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetTerrainBorderFrameName(loop, Index);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTerrainBorderFrameName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Borders_Frames_List->Append(Name, (void*)&GenieFile->TerrainBorders[Index].Frames[loop]);
		}
	}
	
	Borders_Frames_List->SetSelection(0);
	Borders_Frames_List->SetFirstItem(Selection - 3);
	Borders_Frames_List->SetSelection(Selection);
	
	wxCommandEvent E;
	OnTerrainBorderFramesSelect(E);
}

void AGE_Frame::OnTerrainBorderFramesSelect(wxCommandEvent& Event)
{
	short Selection = Borders_Frames_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		gdat::TBFrameData * FramePointer = (gdat::TBFrameData*)Borders_Frames_List->GetClientData(Selection);
		FrameID = FramePointer - (&GenieFile->TerrainBorders[BorderID].Frames[0]);
		Borders_BorderFrameID->ChangeValue(lexical_cast<string>(FramePointer->FrameID));
		Borders_BorderFrameID->Container = &FramePointer->FrameID;
		Borders_BorderFlag1->ChangeValue(lexical_cast<string>(FramePointer->Flag1));
		Borders_BorderFlag1->Container = &FramePointer->Flag1;
		Borders_BorderFlag2->ChangeValue(lexical_cast<string>(FramePointer->Flag2));
		Borders_BorderFlag2->Container = &FramePointer->Flag2;
	}
}

void AGE_Frame::OnTerrainBorderFramesCopy(wxCommandEvent& Event)
{
	short Selection = Borders_Frames_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TBFrameDataCopy = *(gdat::TBFrameData*)Borders_Frames_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnTerrainBorderFramesPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Borders_Frames_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::TBFrameData*)Borders_Frames_List->GetClientData(Selection) = TBFrameDataCopy;
		ListTerrainBorderFrames(BorderID);
	}
}

void AGE_Frame::CreateTerrainBorderControls()
{
	Tab_TerrainBorders = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Borders_Main = new wxBoxSizer(wxHORIZONTAL);
	Borders_ListArea = new wxBoxSizer(wxVERTICAL);
	Borders_Borders_Buttons = new wxGridSizer(2, 0, 0);
	Borders_Borders = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Terrain Borders");
	Borders_Borders_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Borders_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Borders_List = new wxListBox(Tab_TerrainBorders, wxID_ANY, wxDefaultPosition, wxSize(10, 220));
	Borders_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Borders_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Borders_DataArea = new wxBoxSizer(wxVERTICAL);
	Borders_DataTopRow = new wxBoxSizer(wxHORIZONTAL);
	Borders_Data1 = new wxGridSizer(4, 5, 5);

	Borders_FrameData = new wxBoxSizer(wxHORIZONTAL);
	Borders_Frames = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Frames");
	Borders_Frames_Buttons = new wxGridSizer(2, 0, 0);
	Borders_Frames_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Frames_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Frames_List = new wxListBox(Tab_TerrainBorders, wxID_ANY, wxDefaultPosition, wxSize(10, 220));
	Frames_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Frames_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));

	Borders_Holder_FrameArea = new wxBoxSizer(wxVERTICAL);
	Borders_Holder_BorderFrameID = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderFrameID = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderFrameID = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	Borders_Holder_BorderFlag1 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderFlag1 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Flag 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderFlag1 = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	Borders_Holder_BorderFlag2 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderFlag2 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Flag 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderFlag2 = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	
	Borders_Unknonws = new wxGridSizer(4, 5, 5);
	Borders_Holder_BorderEnabled = new wxBoxSizer(wxVERTICAL);
	Borders_Holder_BorderEnabled1 = new wxBoxSizer(wxHORIZONTAL);
	Borders_Text_BorderEnabled = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Enabled", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderEnabled = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	Borders_CheckBox_BorderEnabled = new CheckBox_Short(Tab_TerrainBorders, " Yes", Borders_BorderEnabled);
	for(short loop = 0;loop < 2;loop++)
	{
		Borders_Holder_BorderName[loop] = new wxBoxSizer(wxVERTICAL);
		Borders_BorderName[loop] = new TextCtrl_String(Tab_TerrainBorders, "0", NULL);
	}
	Borders_Text_BorderName[0] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Text_BorderName[1] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " SLP Name ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Holder_BorderRessourceID = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderRessourceID = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderRessourceID = new TextCtrl_Long(Tab_TerrainBorders, "0", NULL);
	Borders_Holder_BorderUnknown3 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderUnknown3 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderUnknown3 = new TextCtrl_Long(Tab_TerrainBorders, "0", NULL);
	Borders_Holder_BorderUnknown4 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderUnknown4 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderUnknown4 = new TextCtrl_Long(Tab_TerrainBorders, "0", NULL);
	Borders_Holder_BorderColors = new wxBoxSizer(wxVERTICAL);
	Borders_Grid_BorderColors = new wxGridSizer(3, 0, 0);
	Borders_Text_BorderColors = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 3;loop++)
	Borders_BorderColors[loop] = new TextCtrl_Byte(Tab_TerrainBorders, "0", NULL);
	Borders_Holder_BorderUnknown5 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderUnknown5 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderUnknown5 = new TextCtrl_Byte(Tab_TerrainBorders, "0", NULL);
	Borders_Holder_BorderUnknown6 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderUnknown6 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderUnknown6 = new TextCtrl_Long(Tab_TerrainBorders, "0", NULL);
	Borders_Holder_BorderUnknown7 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderUnknown7 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderUnknown7 = new TextCtrl_Long(Tab_TerrainBorders, "0", NULL);
	Borders_Holder_BorderFrameCount = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderFrameCount = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderFrameCount = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	Borders_Holder_BorderUnknown8 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderUnknown8 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 8", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderUnknown8 = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	Borders_Holder_BorderTerrain = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderTerrain = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderTerrain = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	Borders_ComboBox_BorderTerrain = new ComboBox_Short(Tab_TerrainBorders, Borders_BorderTerrain);
	Borders_Holder_BorderUnknown10 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderUnknown10 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 10", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderUnknown10 = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);

	for(short loop = 0;loop < 2;loop++)
	{
		Borders_Holder_BorderName[loop]->Add(Borders_Text_BorderName[loop], 0, wxEXPAND);
		Borders_Holder_BorderName[loop]->Add(Borders_BorderName[loop], 0, wxEXPAND);
	}
	Borders_Holder_BorderEnabled1->Add(Borders_BorderEnabled, 1, wxEXPAND);
	Borders_Holder_BorderEnabled1->Add(2, -1);
	Borders_Holder_BorderEnabled1->Add(Borders_CheckBox_BorderEnabled, 1, wxEXPAND);
	Borders_Holder_BorderEnabled->Add(Borders_Text_BorderEnabled, 0, wxEXPAND);
	Borders_Holder_BorderEnabled->Add(Borders_Holder_BorderEnabled1, 1, wxEXPAND);

	Borders_Borders_Buttons->Add(Borders_Copy, 1, wxEXPAND);
	Borders_Borders_Buttons->Add(Borders_Paste, 1, wxEXPAND);

	Borders_Borders->Add(Borders_Borders_Search, 0, wxEXPAND);
	Borders_Borders->Add(Borders_Borders_Search_R, 0, wxEXPAND);
	Borders_Borders->Add(-1, 2);
	Borders_Borders->Add(Borders_Borders_List, 1, wxEXPAND);
	Borders_Borders->Add(-1, 2);
	Borders_Borders->Add(Borders_Borders_Buttons, 0, wxEXPAND);
	
	Borders_ListArea->Add(-1, 10);
	Borders_ListArea->Add(Borders_Borders, 1, wxEXPAND);
	Borders_ListArea->Add(-1, 10);
	
	Borders_DataTopRow->Add(Borders_Holder_BorderEnabled, 1, wxEXPAND);
	Borders_DataTopRow->Add(5, -1);
	Borders_DataTopRow->Add(Borders_Holder_BorderName[0], 2, wxEXPAND);
	Borders_DataTopRow->Add(5, -1);
	Borders_DataTopRow->Add(Borders_Holder_BorderName[1], 2, wxEXPAND);
	Borders_DataTopRow->AddStretchSpacer(1);
	
	Borders_Holder_BorderRessourceID->Add(Borders_Text_BorderRessourceID, 0, wxEXPAND);
	Borders_Holder_BorderRessourceID->Add(Borders_BorderRessourceID, 1, wxEXPAND);
	Borders_Holder_BorderRessourceID->AddStretchSpacer(1);
	Borders_Holder_BorderUnknown3->Add(Borders_Text_BorderUnknown3, 0, wxEXPAND);
	Borders_Holder_BorderUnknown3->Add(Borders_BorderUnknown3, 1, wxEXPAND);
	Borders_Holder_BorderUnknown4->Add(Borders_Text_BorderUnknown4, 0, wxEXPAND);
	Borders_Holder_BorderUnknown4->Add(Borders_BorderUnknown4, 1, wxEXPAND);
	for(short loop = 0;loop < 3;loop++)
	Borders_Grid_BorderColors->Add(Borders_BorderColors[loop], 1, wxEXPAND);
	Borders_Holder_BorderColors->Add(Borders_Text_BorderColors, 0, wxEXPAND);
	Borders_Holder_BorderColors->Add(Borders_Grid_BorderColors, 1, wxEXPAND);
	Borders_Holder_BorderColors->AddStretchSpacer(1);
	Borders_Holder_BorderUnknown5->Add(Borders_Text_BorderUnknown5, 0, wxEXPAND);
	Borders_Holder_BorderUnknown5->Add(Borders_BorderUnknown5, 1, wxEXPAND);
	Borders_Holder_BorderUnknown6->Add(Borders_Text_BorderUnknown6, 0, wxEXPAND);
	Borders_Holder_BorderUnknown6->Add(Borders_BorderUnknown6, 1, wxEXPAND);
	Borders_Holder_BorderUnknown7->Add(Borders_Text_BorderUnknown7, 0, wxEXPAND);
	Borders_Holder_BorderUnknown7->Add(Borders_BorderUnknown7, 1, wxEXPAND);
	Borders_Holder_BorderFrameCount->Add(Borders_Text_BorderFrameCount, 0, wxEXPAND);
	Borders_Holder_BorderFrameCount->Add(Borders_BorderFrameCount, 1, wxEXPAND);
	Borders_Holder_BorderFrameCount->AddStretchSpacer(1);
	Borders_Holder_BorderUnknown8->Add(Borders_Text_BorderUnknown8, 0, wxEXPAND);
	Borders_Holder_BorderUnknown8->Add(Borders_BorderUnknown8, 1, wxEXPAND);
	Borders_Holder_BorderTerrain->Add(Borders_Text_BorderTerrain, 0, wxEXPAND);
	Borders_Holder_BorderTerrain->Add(Borders_BorderTerrain, 1, wxEXPAND);
	Borders_Holder_BorderTerrain->Add(Borders_ComboBox_BorderTerrain, 1, wxEXPAND);
	Borders_Holder_BorderUnknown10->Add(Borders_Text_BorderUnknown10, 0, wxEXPAND);
	Borders_Holder_BorderUnknown10->Add(Borders_BorderUnknown10, 1, wxEXPAND);

	Borders_Data1->Add(Borders_Holder_BorderRessourceID, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Holder_BorderColors, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Holder_BorderFrameCount, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Holder_BorderTerrain, 1, wxEXPAND);

	Borders_Frames_Buttons->Add(Frames_Copy, 1, wxEXPAND);
	Borders_Frames_Buttons->Add(Frames_Paste, 1, wxEXPAND);

	Borders_Frames->Add(Borders_Frames_Search, 0, wxEXPAND);
	Borders_Frames->Add(Borders_Frames_Search_R, 0, wxEXPAND);
	Borders_Frames->Add(-1, 2);
	Borders_Frames->Add(Borders_Frames_List, 1, wxEXPAND);
	Borders_Frames->Add(-1, 2);
	Borders_Frames->Add(Borders_Frames_Buttons, 0, wxEXPAND);

	Borders_Holder_BorderFrameID->Add(Borders_Text_BorderFrameID, 0, wxEXPAND);
	Borders_Holder_BorderFrameID->Add(Borders_BorderFrameID, 1, wxEXPAND);
	Borders_Holder_BorderFlag1->Add(Borders_Text_BorderFlag1, 0, wxEXPAND);
	Borders_Holder_BorderFlag1->Add(Borders_BorderFlag1, 1, wxEXPAND);
	Borders_Holder_BorderFlag2->Add(Borders_Text_BorderFlag2, 0, wxEXPAND);
	Borders_Holder_BorderFlag2->Add(Borders_BorderFlag2, 1, wxEXPAND);

	Borders_Holder_FrameArea->Add(Borders_Holder_BorderFrameID, 0, wxEXPAND);
	Borders_Holder_FrameArea->Add(-1, 5);
	Borders_Holder_FrameArea->Add(Borders_Holder_BorderFlag1, 0, wxEXPAND);
	Borders_Holder_FrameArea->Add(-1, 5);
	Borders_Holder_FrameArea->Add(Borders_Holder_BorderFlag2, 0, wxEXPAND);
	
	Borders_FrameData->Add(Borders_Frames, 3, wxEXPAND);
	Borders_FrameData->Add(5, -1);
	Borders_FrameData->Add(Borders_Holder_FrameArea, 2, wxEXPAND);
	Borders_FrameData->AddStretchSpacer(3);
	
	Borders_Unknonws->Add(Borders_Holder_BorderUnknown3, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Holder_BorderUnknown4, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Holder_BorderUnknown5, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Holder_BorderUnknown6, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Holder_BorderUnknown7, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Holder_BorderUnknown8, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Holder_BorderUnknown10, 1, wxEXPAND);
	
	Borders_DataArea->Add(-1, 10);
	Borders_DataArea->Add(Borders_DataTopRow, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 5);
	Borders_DataArea->Add(Borders_Data1, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 5);
	Borders_DataArea->Add(Borders_FrameData, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 5);
	Borders_DataArea->Add(Borders_Unknonws, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 10);
	
	Borders_Main->Add(10, -1);
	Borders_Main->Add(Borders_ListArea, 1, wxEXPAND);
	Borders_Main->Add(10, -1);
	Borders_Main->Add(Borders_DataArea, 3, wxEXPAND);
	Borders_Main->Add(10, -1);
	
	Tab_TerrainBorders->SetSizer(Borders_Main);

	Connect(Borders_Borders_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSearch));
	Connect(Borders_Borders_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSearch));
	Connect(Borders_Borders_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSelect));
	Connect(Borders_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersCopy));
	Connect(Borders_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersPaste));
	Connect(Borders_Frames_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesSearch));
	Connect(Borders_Frames_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesSearch));
	Connect(Borders_Frames_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesSelect));
	Connect(Frames_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesCopy));
	Connect(Frames_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesPaste));
	
	for(short loop = 0;loop < 2;loop++)
	Borders_BorderName[loop]->Connect(Borders_BorderName[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Borders_BorderFrameID->Connect(Borders_BorderFrameID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);
	Borders_BorderFlag1->Connect(Borders_BorderFlag1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);
	Borders_BorderFlag2->Connect(Borders_BorderFlag2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);

}