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
		General_BorderName[0]->ChangeValue(BorderPointer->Name);
		General_BorderName[0]->Container = &BorderPointer->Name;
		General_BorderName[1]->ChangeValue(BorderPointer->Name2);
		General_BorderName[1]->Container = &BorderPointer->Name2;
		General_BorderEnabled->ChangeValue(lexical_cast<string>(BorderPointer->Enabled));
		General_BorderEnabled->Container = &BorderPointer->Enabled;
		General_CheckBox_BorderEnabled->SetValue((bool)BorderPointer->Enabled);
		General_BorderRessourceID->ChangeValue(lexical_cast<string>(BorderPointer->RessourceID));
		General_BorderRessourceID->Container = &BorderPointer->RessourceID;
		General_BorderUnknown3->ChangeValue(lexical_cast<string>(BorderPointer->Unknown3));
		General_BorderUnknown3->Container = &BorderPointer->Unknown3;
		General_BorderUnknown4->ChangeValue(lexical_cast<string>(BorderPointer->Unknown4));
		General_BorderUnknown4->Container = &BorderPointer->Unknown4;
		for(short loop = 0;loop < 3;loop++)
		{
			General_BorderColors[loop]->ChangeValue(lexical_cast<string>((short)BorderPointer->Colors[loop]));
			General_BorderColors[loop]->Container = &BorderPointer->Colors[loop];
		}
		General_BorderUnknown5->ChangeValue(lexical_cast<string>((short)BorderPointer->Unknown5));
		General_BorderUnknown5->Container = &BorderPointer->Unknown5;
		General_BorderUnknown6->ChangeValue(lexical_cast<string>(BorderPointer->Unknown6));
		General_BorderUnknown6->Container = &BorderPointer->Unknown6;
		General_BorderUnknown7->ChangeValue(lexical_cast<string>(BorderPointer->Unknown7));
		General_BorderUnknown7->Container = &BorderPointer->Unknown7;
		General_BorderFrameCount->ChangeValue(lexical_cast<string>(BorderPointer->FrameCount));
		General_BorderFrameCount->Container = &BorderPointer->FrameCount;
		General_BorderUnknown8->ChangeValue(lexical_cast<string>(BorderPointer->Unknown8));
		General_BorderUnknown8->Container = &BorderPointer->Unknown8;
		General_BorderUnknown9->ChangeValue(lexical_cast<string>(BorderPointer->Unknown9));
		General_BorderUnknown9->Container = &BorderPointer->Unknown9;
		General_BorderUnknown10->ChangeValue(lexical_cast<string>(BorderPointer->Unknown10));
		General_BorderUnknown10->Container = &BorderPointer->Unknown10;
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
		General_BorderFrameID->ChangeValue(lexical_cast<string>(FramePointer->FrameID));
		General_BorderFrameID->Container = &FramePointer->FrameID;
		General_BorderFlag1->ChangeValue(lexical_cast<string>(FramePointer->Flag1));
		General_BorderFlag1->Container = &FramePointer->Flag1;
		General_BorderFlag2->ChangeValue(lexical_cast<string>(FramePointer->Flag2));
		General_BorderFlag2->Container = &FramePointer->Flag2;
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
	Tab_TerrainBorders = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	Borders_Main = new wxBoxSizer(wxHORIZONTAL);
	Borders_ListArea = new wxBoxSizer(wxVERTICAL);
	Borders_Borders_Buttons = new wxGridSizer(2, 0, 0);
	Borders_Borders = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Terrain Border slot");
	Borders_Borders_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Borders_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Borders_List = new wxListBox(Tab_TerrainBorders, wxID_ANY, wxDefaultPosition, wxSize(-1, 220));
	Borders_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Borders_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));
	Borders_DataArea = new wxBoxSizer(wxVERTICAL);
	General_DataTopRow = new wxGridSizer(3, 5, 5);
	Borders_Data1 = new wxGridSizer(4, 5, 5);

	Borders_FrameData = new wxBoxSizer(wxHORIZONTAL);
	Borders_Frames = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Frame slot");
	Borders_Frames_Buttons = new wxGridSizer(2, 0, 0);
	Borders_Frames_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Frames_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Frames_List = new wxListBox(Tab_TerrainBorders, wxID_ANY, wxDefaultPosition, wxSize(-1, 220));
	Frames_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Frames_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));

	Borders_Holder_FrameArea = new wxBoxSizer(wxVERTICAL);
	General_Holder_BorderFrameID = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderFrameID = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderFrameID = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	General_Holder_BorderFlag1 = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderFlag1 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Flag 1", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderFlag1 = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	General_Holder_BorderFlag2 = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderFlag2 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Flag 2", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderFlag2 = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	
	Borders_Unknonws = new wxGridSizer(4, 5, 5);
	General_Holder_BorderEnabled = new wxBoxSizer(wxVERTICAL);
	General_Holder_BorderEnabled1 = new wxBoxSizer(wxHORIZONTAL);
	General_Text_BorderEnabled = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Enabled", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderEnabled = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	General_CheckBox_BorderEnabled = new CheckBox_Short(Tab_TerrainBorders, " Yes", General_BorderEnabled);
	for(short loop = 0;loop < 2;loop++)
	{
		General_Holder_BorderName[loop] = new wxBoxSizer(wxVERTICAL);
		General_BorderName[loop] = new TextCtrl_String(Tab_TerrainBorders, "0", NULL);
	}
	General_Text_BorderName[0] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Name", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Text_BorderName[1] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " SLP Name ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Holder_BorderRessourceID = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderRessourceID = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Ressource", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderRessourceID = new TextCtrl_Long(Tab_TerrainBorders, "0", NULL);
	General_Holder_BorderUnknown3 = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderUnknown3 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 3", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderUnknown3 = new TextCtrl_Long(Tab_TerrainBorders, "0", NULL);
	General_Holder_BorderUnknown4 = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderUnknown4 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 4", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderUnknown4 = new TextCtrl_Long(Tab_TerrainBorders, "0", NULL);
	General_Holder_BorderColors = new wxBoxSizer(wxVERTICAL);
	General_Grid_BorderColors = new wxGridSizer(3, 0, 0);
	General_Text_BorderColors = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Colors", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 3;loop++)
	General_BorderColors[loop] = new TextCtrl_Byte(Tab_TerrainBorders, "0", NULL);
	General_Holder_BorderUnknown5 = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderUnknown5 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 5", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderUnknown5 = new TextCtrl_Byte(Tab_TerrainBorders, "0", NULL);
	General_Holder_BorderUnknown6 = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderUnknown6 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 6", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderUnknown6 = new TextCtrl_Long(Tab_TerrainBorders, "0", NULL);
	General_Holder_BorderUnknown7 = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderUnknown7 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 7", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderUnknown7 = new TextCtrl_Long(Tab_TerrainBorders, "0", NULL);
	General_Holder_BorderFrameCount = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderFrameCount = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame Count", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderFrameCount = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	General_Holder_BorderUnknown8 = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderUnknown8 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 8", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderUnknown8 = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	General_Holder_BorderUnknown9 = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderUnknown9 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 9", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderUnknown9 = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);
	General_Holder_BorderUnknown10 = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderUnknown10 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 10", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderUnknown10 = new TextCtrl_Short(Tab_TerrainBorders, "0", NULL);

	for(short loop = 0;loop < 2;loop++)
	{
		General_Holder_BorderName[loop]->Add(General_Text_BorderName[loop], 0, wxEXPAND);
		General_Holder_BorderName[loop]->Add(-1, 2);
		General_Holder_BorderName[loop]->Add(General_BorderName[loop], 0, wxEXPAND);
	}
	General_Holder_BorderEnabled1->Add(General_BorderEnabled, 1, wxEXPAND);
	General_Holder_BorderEnabled1->Add(2, -1);
	General_Holder_BorderEnabled1->Add(General_CheckBox_BorderEnabled, 2, wxEXPAND);
	General_Holder_BorderEnabled->Add(General_Text_BorderEnabled, 0, wxEXPAND);
	General_Holder_BorderEnabled->Add(-1, 2);
	General_Holder_BorderEnabled->Add(General_Holder_BorderEnabled1, 1, wxEXPAND);

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
	
	for(short loop = 0;loop < 2;loop++)
	General_DataTopRow->Add(General_Holder_BorderName[loop], 1, wxEXPAND);
	Borders_Data1->Add(General_Holder_BorderEnabled, 1, wxEXPAND);
	
	General_Holder_BorderRessourceID->Add(General_Text_BorderRessourceID, 0, wxEXPAND);
	General_Holder_BorderRessourceID->Add(-1, 2);
	General_Holder_BorderRessourceID->Add(General_BorderRessourceID, 1, wxEXPAND);
	General_Holder_BorderUnknown3->Add(General_Text_BorderUnknown3, 0, wxEXPAND);
	General_Holder_BorderUnknown3->Add(-1, 2);
	General_Holder_BorderUnknown3->Add(General_BorderUnknown3, 1, wxEXPAND);
	General_Holder_BorderUnknown4->Add(General_Text_BorderUnknown4, 0, wxEXPAND);
	General_Holder_BorderUnknown4->Add(-1, 2);
	General_Holder_BorderUnknown4->Add(General_BorderUnknown4, 1, wxEXPAND);
	for(short loop = 0;loop < 3;loop++)
	General_Grid_BorderColors->Add(General_BorderColors[loop], 1, wxEXPAND);
	General_Holder_BorderColors->Add(General_Text_BorderColors, 0, wxEXPAND);
	General_Holder_BorderColors->Add(-1, 2);
	General_Holder_BorderColors->Add(General_Grid_BorderColors, 1, wxEXPAND);
	General_Holder_BorderUnknown5->Add(General_Text_BorderUnknown5, 0, wxEXPAND);
	General_Holder_BorderUnknown5->Add(-1, 2);
	General_Holder_BorderUnknown5->Add(General_BorderUnknown5, 1, wxEXPAND);
	General_Holder_BorderUnknown6->Add(General_Text_BorderUnknown6, 0, wxEXPAND);
	General_Holder_BorderUnknown6->Add(-1, 2);
	General_Holder_BorderUnknown6->Add(General_BorderUnknown6, 1, wxEXPAND);
	General_Holder_BorderUnknown7->Add(General_Text_BorderUnknown7, 0, wxEXPAND);
	General_Holder_BorderUnknown7->Add(-1, 2);
	General_Holder_BorderUnknown7->Add(General_BorderUnknown7, 1, wxEXPAND);
	General_Holder_BorderFrameCount->Add(General_Text_BorderFrameCount, 0, wxEXPAND);
	General_Holder_BorderFrameCount->Add(-1, 2);
	General_Holder_BorderFrameCount->Add(General_BorderFrameCount, 1, wxEXPAND);
	General_Holder_BorderUnknown8->Add(General_Text_BorderUnknown8, 0, wxEXPAND);
	General_Holder_BorderUnknown8->Add(-1, 2);
	General_Holder_BorderUnknown8->Add(General_BorderUnknown8, 1, wxEXPAND);
	General_Holder_BorderUnknown9->Add(General_Text_BorderUnknown9, 0, wxEXPAND);
	General_Holder_BorderUnknown9->Add(-1, 2);
	General_Holder_BorderUnknown9->Add(General_BorderUnknown9, 1, wxEXPAND);
	General_Holder_BorderUnknown10->Add(General_Text_BorderUnknown10, 0, wxEXPAND);
	General_Holder_BorderUnknown10->Add(-1, 2);
	General_Holder_BorderUnknown10->Add(General_BorderUnknown10, 1, wxEXPAND);

	Borders_Data1->Add(General_Holder_BorderRessourceID, 1, wxEXPAND);
	Borders_Data1->Add(General_Holder_BorderColors, 1, wxEXPAND);
	Borders_Data1->Add(General_Holder_BorderFrameCount, 1, wxEXPAND);

	Borders_Frames_Buttons->Add(Frames_Copy, 1, wxEXPAND);
	Borders_Frames_Buttons->Add(Frames_Paste, 1, wxEXPAND);

	Borders_Frames->Add(Borders_Frames_Search, 0, wxEXPAND);
	Borders_Frames->Add(Borders_Frames_Search_R, 0, wxEXPAND);
	Borders_Frames->Add(-1, 2);
	Borders_Frames->Add(Borders_Frames_List, 1, wxEXPAND);
	Borders_Frames->Add(-1, 2);
	Borders_Frames->Add(Borders_Frames_Buttons, 0, wxEXPAND);

	General_Holder_BorderFrameID->Add(General_Text_BorderFrameID, 0, wxEXPAND);
	General_Holder_BorderFrameID->Add(-1, 2);
	General_Holder_BorderFrameID->Add(General_BorderFrameID, 1, wxEXPAND);
	General_Holder_BorderFlag1->Add(General_Text_BorderFlag1, 0, wxEXPAND);
	General_Holder_BorderFlag1->Add(-1, 2);
	General_Holder_BorderFlag1->Add(General_BorderFlag1, 1, wxEXPAND);
	General_Holder_BorderFlag2->Add(General_Text_BorderFlag2, 0, wxEXPAND);
	General_Holder_BorderFlag2->Add(-1, 2);
	General_Holder_BorderFlag2->Add(General_BorderFlag2, 1, wxEXPAND);

	Borders_Holder_FrameArea->Add(General_Holder_BorderFrameID, 0, wxEXPAND);
	Borders_Holder_FrameArea->Add(-1, 5);
	Borders_Holder_FrameArea->Add(General_Holder_BorderFlag1, 0, wxEXPAND);
	Borders_Holder_FrameArea->Add(-1, 5);
	Borders_Holder_FrameArea->Add(General_Holder_BorderFlag2, 0, wxEXPAND);
	
	Borders_FrameData->Add(Borders_Frames, 3, wxEXPAND);
	Borders_FrameData->Add(5, -1);
	Borders_FrameData->Add(Borders_Holder_FrameArea, 2, wxEXPAND);
	Borders_FrameData->AddStretchSpacer(3);
	
	Borders_Unknonws->Add(General_Holder_BorderUnknown3, 1, wxEXPAND);
	Borders_Unknonws->Add(General_Holder_BorderUnknown4, 1, wxEXPAND);
	Borders_Unknonws->Add(General_Holder_BorderUnknown5, 1, wxEXPAND);
	Borders_Unknonws->Add(General_Holder_BorderUnknown6, 1, wxEXPAND);
	Borders_Unknonws->Add(General_Holder_BorderUnknown7, 1, wxEXPAND);
	Borders_Unknonws->Add(General_Holder_BorderUnknown8, 1, wxEXPAND);
	Borders_Unknonws->Add(General_Holder_BorderUnknown9, 1, wxEXPAND);
	Borders_Unknonws->Add(General_Holder_BorderUnknown10, 1, wxEXPAND);
	
	Borders_DataArea->Add(-1, 10);
	Borders_DataArea->Add(General_DataTopRow, 0, wxEXPAND);
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
	General_BorderName[loop]->Connect(General_BorderName[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	General_BorderFrameID->Connect(General_BorderFrameID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);
	General_BorderFlag1->Connect(General_BorderFlag1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);
	General_BorderFlag2->Connect(General_BorderFlag2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);

}