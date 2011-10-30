/* AGEFrame_cpp/Graphics.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetGraphicName(int Index)
{
	string Name = "";
	Name = GenieFile->Graphics[Index].Name;
	return Name;
}

void AGE_Frame::ListGraphics()
{
	string Name;
	wxString SearchText = wxString(Graphics_Graphics_Search->GetValue()).Lower();
	string CompareText;
	
	short Selection = Graphics_Graphics_List->GetSelection();
	short GraphicIDs[21];
	GraphicIDs[0] = Units_ComboBox_ConstructionGraphicID->GetSelection();
	GraphicIDs[1] = Units_ComboBox_SnowGraphicID->GetSelection();
	GraphicIDs[2] = Units_ComboBox_AttackGraphic->GetSelection();
	GraphicIDs[3] = Units_ComboBox_StandingGraphic[0]->GetSelection();
	GraphicIDs[4] = Units_ComboBox_StandingGraphic[1]->GetSelection();
	GraphicIDs[5] = Units_ComboBox_GarrisonGraphic[0]->GetSelection();
	GraphicIDs[6] = Units_ComboBox_GarrisonGraphic[1]->GetSelection();
	GraphicIDs[7] = Units_ComboBox_WalkingGraphic[0]->GetSelection();
	GraphicIDs[8] = Units_ComboBox_WalkingGraphic[1]->GetSelection();
	GraphicIDs[9] = Units_ComboBox_DyingGraphic[0]->GetSelection();
	GraphicIDs[10] = Units_ComboBox_DyingGraphic[1]->GetSelection();
	GraphicIDs[11] = Units_ComboBox_AttackMissileDuplicationGraphic->GetSelection();
	GraphicIDs[12] = UnitCommands_ComboBox_Graphics[0]->GetSelection();
	GraphicIDs[13] = UnitCommands_ComboBox_Graphics[1]->GetSelection();
	GraphicIDs[14] = UnitCommands_ComboBox_Graphics[2]->GetSelection();
	GraphicIDs[15] = UnitCommands_ComboBox_Graphics[3]->GetSelection();
	GraphicIDs[16] = UnitCommands_ComboBox_Graphics[4]->GetSelection();
	GraphicIDs[17] = UnitCommands_ComboBox_Graphics[5]->GetSelection();
	GraphicIDs[18] = DamageGraphics_ComboBox_GraphicID->GetSelection();
	GraphicIDs[19] = TerRestrict_ComboBox_Graphics[0]->GetSelection();
	GraphicIDs[20] = TerRestrict_ComboBox_Graphics[1]->GetSelection();

	if(!Graphics_Graphics_List->IsEmpty())
	{
		Graphics_Graphics_List->Clear();
	}
	if(!Units_ComboBox_ConstructionGraphicID->IsEmpty())
	{
		Units_ComboBox_ConstructionGraphicID->Clear();
	}
	if(!Units_ComboBox_SnowGraphicID->IsEmpty())
	{
		Units_ComboBox_SnowGraphicID->Clear();
	}
	if(!Units_ComboBox_AttackGraphic->IsEmpty())
	{
		Units_ComboBox_AttackGraphic->Clear();
	}
	if(!Units_ComboBox_StandingGraphic[0]->IsEmpty())
	{
		Units_ComboBox_StandingGraphic[0]->Clear();
	}
	if(!Units_ComboBox_StandingGraphic[1]->IsEmpty())
	{
		Units_ComboBox_StandingGraphic[1]->Clear();
	}
	if(!Units_ComboBox_GarrisonGraphic[0]->IsEmpty())
	{
		Units_ComboBox_GarrisonGraphic[0]->Clear();
	}
	if(!Units_ComboBox_GarrisonGraphic[1]->IsEmpty())
	{
		Units_ComboBox_GarrisonGraphic[1]->Clear();
	}
	if(!Units_ComboBox_WalkingGraphic[0]->IsEmpty())
	{
		Units_ComboBox_WalkingGraphic[0]->Clear();
	}
	if(!Units_ComboBox_WalkingGraphic[1]->IsEmpty())
	{
		Units_ComboBox_WalkingGraphic[1]->Clear();
	}
	if(!Units_ComboBox_DyingGraphic[0]->IsEmpty())
	{
		Units_ComboBox_DyingGraphic[0]->Clear();
	}
	if(!Units_ComboBox_DyingGraphic[1]->IsEmpty())
	{
		Units_ComboBox_DyingGraphic[1]->Clear();
	}
	if(!Units_ComboBox_AttackMissileDuplicationGraphic->IsEmpty())
	{
		Units_ComboBox_AttackMissileDuplicationGraphic->Clear();
	}
	if(!UnitCommands_ComboBox_Graphics[0]->IsEmpty())
	{
		UnitCommands_ComboBox_Graphics[0]->Clear();
	}
	if(!UnitCommands_ComboBox_Graphics[1]->IsEmpty())
	{
		UnitCommands_ComboBox_Graphics[1]->Clear();
	}
	if(!UnitCommands_ComboBox_Graphics[2]->IsEmpty())
	{
		UnitCommands_ComboBox_Graphics[2]->Clear();
	}
	if(!UnitCommands_ComboBox_Graphics[3]->IsEmpty())
	{
		UnitCommands_ComboBox_Graphics[3]->Clear();
	}
	if(!UnitCommands_ComboBox_Graphics[4]->IsEmpty())
	{
		UnitCommands_ComboBox_Graphics[4]->Clear();
	}
	if(!UnitCommands_ComboBox_Graphics[5]->IsEmpty())
	{
		UnitCommands_ComboBox_Graphics[5]->Clear();
	}
	if(!DamageGraphics_ComboBox_GraphicID->IsEmpty())
	{
		DamageGraphics_ComboBox_GraphicID->Clear();
	}
	if(!TerRestrict_ComboBox_Graphics[0]->IsEmpty())
	{
		TerRestrict_ComboBox_Graphics[0]->Clear();
	}
	if(!TerRestrict_ComboBox_Graphics[1]->IsEmpty())
	{
		TerRestrict_ComboBox_Graphics[1]->Clear();
	}
	
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < 21;loop++)
	{
		if(GraphicIDs[loop] == wxNOT_FOUND)
		{
			GraphicIDs[loop] = 0;
		}
	}
	
	Units_ComboBox_ConstructionGraphicID->Append("-1 - None");
	Units_ComboBox_SnowGraphicID->Append("-1 - None");
	Units_ComboBox_AttackGraphic->Append("-1 - None");
	Units_ComboBox_StandingGraphic[0]->Append("-1 - None");
	Units_ComboBox_StandingGraphic[1]->Append("-1 - None");
	Units_ComboBox_GarrisonGraphic[0]->Append("-1 - None");
	Units_ComboBox_GarrisonGraphic[1]->Append("-1 - None");
	Units_ComboBox_WalkingGraphic[0]->Append("-1 - None");
	Units_ComboBox_WalkingGraphic[1]->Append("-1 - None");
	Units_ComboBox_DyingGraphic[0]->Append("-1 - None");
	Units_ComboBox_DyingGraphic[1]->Append("-1 - None");
	Units_ComboBox_AttackMissileDuplicationGraphic->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[0]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[1]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[2]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[3]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[4]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[5]->Append("-1 - None");
	DamageGraphics_ComboBox_GraphicID->Append("-1 - None");
	TerRestrict_ComboBox_Graphics[0]->Append("-1 - None");
	TerRestrict_ComboBox_Graphics[1]->Append("-1 - None");
	
	for(short loop = 0;loop < GenieFile->Graphics.size();loop++)
	{
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetGraphicName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetGraphicName(loop)).Lower();
		if(SearchText.IsEmpty() || CompareText.find(SearchText) != string::npos)
		{
			Graphics_Graphics_List->Append(Name, (void*)&GenieFile->Graphics[loop]);
		}
		Units_ComboBox_ConstructionGraphicID->Append(Name);
		Units_ComboBox_SnowGraphicID->Append(Name);
		Units_ComboBox_AttackGraphic->Append(Name);
		Units_ComboBox_StandingGraphic[0]->Append(Name);
		Units_ComboBox_StandingGraphic[1]->Append(Name);
		Units_ComboBox_GarrisonGraphic[0]->Append(Name);
		Units_ComboBox_GarrisonGraphic[1]->Append(Name);
		Units_ComboBox_WalkingGraphic[0]->Append(Name);
		Units_ComboBox_WalkingGraphic[1]->Append(Name);
		Units_ComboBox_DyingGraphic[0]->Append(Name);
		Units_ComboBox_DyingGraphic[1]->Append(Name);
		Units_ComboBox_AttackMissileDuplicationGraphic->Append(Name);
		UnitCommands_ComboBox_Graphics[0]->Append(Name);
		UnitCommands_ComboBox_Graphics[1]->Append(Name);
		UnitCommands_ComboBox_Graphics[2]->Append(Name);
		UnitCommands_ComboBox_Graphics[3]->Append(Name);
		UnitCommands_ComboBox_Graphics[4]->Append(Name);
		UnitCommands_ComboBox_Graphics[5]->Append(Name);
		DamageGraphics_ComboBox_GraphicID->Append(Name);
		TerRestrict_ComboBox_Graphics[0]->Append(Name);
		TerRestrict_ComboBox_Graphics[1]->Append(Name);
	}
	
	Graphics_Graphics_List->SetFirstItem(Selection - 3);
	Graphics_Graphics_List->SetSelection(Selection);
	Units_ComboBox_ConstructionGraphicID->SetSelection(GraphicIDs[0]);
	Units_ComboBox_SnowGraphicID->SetSelection(GraphicIDs[1]);
	Units_ComboBox_AttackGraphic->SetSelection(GraphicIDs[2]);
	Units_ComboBox_StandingGraphic[0]->SetSelection(GraphicIDs[3]);
	Units_ComboBox_StandingGraphic[1]->SetSelection(GraphicIDs[4]);
	Units_ComboBox_GarrisonGraphic[0]->SetSelection(GraphicIDs[5]);
	Units_ComboBox_GarrisonGraphic[1]->SetSelection(GraphicIDs[6]);
	Units_ComboBox_WalkingGraphic[0]->SetSelection(GraphicIDs[7]);
	Units_ComboBox_WalkingGraphic[1]->SetSelection(GraphicIDs[8]);
	Units_ComboBox_DyingGraphic[0]->SetSelection(GraphicIDs[9]);
	Units_ComboBox_DyingGraphic[1]->SetSelection(GraphicIDs[10]);
	Units_ComboBox_AttackMissileDuplicationGraphic->SetSelection(GraphicIDs[11]);
	UnitCommands_ComboBox_Graphics[0]->SetSelection(GraphicIDs[12]);
	UnitCommands_ComboBox_Graphics[1]->SetSelection(GraphicIDs[13]);
	UnitCommands_ComboBox_Graphics[2]->SetSelection(GraphicIDs[14]);
	UnitCommands_ComboBox_Graphics[3]->SetSelection(GraphicIDs[15]);
	UnitCommands_ComboBox_Graphics[4]->SetSelection(GraphicIDs[16]);
	UnitCommands_ComboBox_Graphics[5]->SetSelection(GraphicIDs[17]);
	DamageGraphics_ComboBox_GraphicID->SetSelection(GraphicIDs[18]);
	TerRestrict_ComboBox_Graphics[0]->SetSelection(GraphicIDs[19]);
	TerRestrict_ComboBox_Graphics[1]->SetSelection(GraphicIDs[20]);
	
	wxCommandEvent E;
	OnGraphicsSelect(E);
}

void AGE_Frame::OnGraphicsSearch(wxCommandEvent& Event)
{
	short Selection = Graphics_Graphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		ListGraphics();
	}
}

void AGE_Frame::OnGraphicsSelect(wxCommandEvent& Event)
{
	short Selection = Graphics_Graphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Graphics_Graphics_List->GetCount() - 1;
			Graphics_Graphics_List->SetSelection(Selection);
		}
		gdat::Graphic * GraphicPointer = (gdat::Graphic*)Graphics_Graphics_List->GetClientData(Selection);
		GraphicID = GraphicPointer - (&GenieFile->Graphics[0]);
		Graphics_Name->ChangeValue(GraphicPointer->Name);
		Graphics_Name->Container = &GraphicPointer->Name;
		Graphics_Name2->ChangeValue(GraphicPointer->Name2);
		Graphics_Name2->Container = &GraphicPointer->Name2;
		Graphics_SLP->ChangeValue(lexical_cast<string>(GraphicPointer->SLP));
		Graphics_SLP->Container = &GraphicPointer->SLP;
		Graphics_Unknown1->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown1));
		Graphics_Unknown1->Container = &GraphicPointer->Unknown1;
		Graphics_Unknown2->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown2));
		Graphics_Unknown2->Container = &GraphicPointer->Unknown2;
		Graphics_FrameType->ChangeValue(lexical_cast<string>((short)GraphicPointer->FrameType));
		Graphics_FrameType->Container = &GraphicPointer->FrameType;
		Graphics_Unknown3->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown3));
		Graphics_Unknown3->Container = &GraphicPointer->Unknown3;
		Graphics_Unknown4->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown4));
		Graphics_Unknown4->Container = &GraphicPointer->Unknown4;
		Graphics_Replay->ChangeValue(lexical_cast<string>((short)GraphicPointer->Replay));
		Graphics_Replay->Container = &GraphicPointer->Replay;
		Graphics_Unknown5->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown5));
		Graphics_Unknown5->Container = &GraphicPointer->Unknown5;
		Graphics_Unknown6->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown6));
		Graphics_Unknown6->Container = &GraphicPointer->Unknown6;
		Graphics_Unknown7->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown7));
		Graphics_Unknown7->Container = &GraphicPointer->Unknown7;
		Graphics_Unknown8->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown8));
		Graphics_Unknown8->Container = &GraphicPointer->Unknown8;
		Graphics_Unknown9->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown9));
		Graphics_Unknown9->Container = &GraphicPointer->Unknown9;
		Graphics_Unknown10->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown10));
		Graphics_Unknown10->Container = &GraphicPointer->Unknown10;
		Graphics_Unknown11->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown11));
		Graphics_Unknown11->Container = &GraphicPointer->Unknown11;
		Graphics_Unknown12->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown12));
		Graphics_Unknown12->Container = &GraphicPointer->Unknown12;
		Graphics_SoundID->ChangeValue(lexical_cast<string>(GraphicPointer->SoundID));
		Graphics_SoundID->Container = &GraphicPointer->SoundID;
		Graphics_ComboBox_SoundID->SetSelection(GraphicPointer->SoundID + 1);
		Graphics_AttackSoundUsed->ChangeValue(lexical_cast<string>((short)GraphicPointer->AttackSoundUsed));
		Graphics_AttackSoundUsed->Container = &GraphicPointer->AttackSoundUsed;
		Graphics_CheckBox_AttackSoundUsed->SetValue((bool)GraphicPointer->AttackSoundUsed);
		Graphics_FrameCount->ChangeValue(lexical_cast<string>(GraphicPointer->FrameCount));
		Graphics_FrameCount->Container = &GraphicPointer->FrameCount;
		Graphics_AngleCount->ChangeValue(lexical_cast<string>(GraphicPointer->AngleCount));
		Graphics_AngleCount->Container = &GraphicPointer->AngleCount;
		Graphics_Unknown13->ChangeValue(lexical_cast<string>(GraphicPointer->Unknown13));
		Graphics_Unknown13->Container = &GraphicPointer->Unknown13;
		Graphics_FrameRate->ChangeValue(lexical_cast<string>(GraphicPointer->FrameRate));
		Graphics_FrameRate->Container = &GraphicPointer->FrameRate;
		Graphics_ReplayDelay->ChangeValue(lexical_cast<string>(GraphicPointer->ReplayDelay));
		Graphics_ReplayDelay->Container = &GraphicPointer->ReplayDelay;
		Graphics_SequenceType->ChangeValue(lexical_cast<string>((short)GraphicPointer->SequenceType));
		Graphics_SequenceType->Container = &GraphicPointer->SequenceType;
		Graphics_ID->ChangeValue(lexical_cast<string>(GraphicPointer->ID));
		Graphics_ID->Container = &GraphicPointer->ID;
		if(GameVersion >= 2)
		{
			Graphics_TypeS->SetBackgroundColour(wxColour(210, 230, 255));
			Graphics_TypeS->ChangeValue(lexical_cast<string>(GraphicPointer->Type));
		}
		else
		{
			Graphics_TypeS->SetBackgroundColour(wxColour(255, 235, 215));
			Graphics_TypeS->ChangeValue(lexical_cast<string>((short)GraphicPointer->Type));
		}
		Graphics_TypeS->Container = &GraphicPointer->Type;
		Added = false;
	}
}

void AGE_Frame::OnGraphicsAdd(wxCommandEvent& Event)
{
	gdat::Graphic Temp;
	GenieFile->Graphics.push_back(Temp);
	for(short loop = 0;loop < GenieFile->Graphics.size();loop++)	//	ID fix
	{
		GenieFile->Graphics[loop].ID = lexical_cast<short>(loop);
	}
	Added = true;
	ListGraphics();
}

void AGE_Frame::OnGraphicsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Graphics_Graphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->Graphics.erase(GenieFile->Graphics.begin() + GraphicID);
		for(short loop = 0;loop < GenieFile->Graphics.size();loop++)	//	ID fix
		{
			GenieFile->Graphics[loop].ID = lexical_cast<short>(loop);
		}
		if(Selection == Graphics_Graphics_List->GetCount() - 1)
		Graphics_Graphics_List->SetSelection(Selection - 1);
		ListGraphics();
	}
}

void AGE_Frame::OnGraphicsCopy(wxCommandEvent& Event)
{
	short Selection = Graphics_Graphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GraphicCopy = *(gdat::Graphic*)Graphics_Graphics_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnGraphicsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Graphics_Graphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::Graphic*)Graphics_Graphics_List->GetClientData(Selection) = GraphicCopy;
		for(short loop = 0;loop < GenieFile->Graphics.size();loop++)	//	ID fix
		{
			GenieFile->Graphics[loop].ID = lexical_cast<short>(loop);
		}
		ListGraphics();
	}
}

void AGE_Frame::CreateGraphicsControls()
{

	Tab_Graphics = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(-1, 350));
	Graphics_Main = new wxBoxSizer(wxHORIZONTAL);
	Graphics_ListArea = new wxBoxSizer(wxVERTICAL);
	Graphics_Graphics_Buttons = new wxGridSizer(2, 0, 0);

	Graphics_Graphics = new wxStaticBoxSizer(wxVERTICAL, Tab_Graphics, "Graphic Slot");
	Graphics_Graphics_Search = new wxTextCtrl(Tab_Graphics, wxID_ANY);
	Graphics_Graphics_List = new wxListBox(Tab_Graphics, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	Graphics_Add = new wxButton(Tab_Graphics, wxID_ANY, "Add", wxDefaultPosition, wxSize(-1, 20));
	Graphics_Delete = new wxButton(Tab_Graphics, wxID_ANY, "Delete", wxDefaultPosition, wxSize(-1, 20));
	Graphics_Copy = new wxButton(Tab_Graphics, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Graphics_Paste = new wxButton(Tab_Graphics, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));

	Graphics_DataArea = new wxBoxSizer(wxVERTICAL);
	Graphics_Scroller = new AGE_ScrolledWindow(Tab_Graphics, wxVSCROLL | wxTAB_TRAVERSAL);
	Graphics_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	Graphics_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_NameArea = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Holder_Name = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Name = new wxStaticText(Graphics_Scroller, wxID_ANY, " Name", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Name = new TextCtrl_String(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Name2 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Name2 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Name 2", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Name2 = new TextCtrl_String(Graphics_Scroller, "0", NULL);
	Graphics_Holder_SLP = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_SLP = new wxStaticText(Graphics_Scroller, wxID_ANY, " SLP", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SLP = new TextCtrl_Long(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknowns = new wxGridSizer(4, 5, 5);
	Graphics_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown1 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown1 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown2 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown2 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_FrameType = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_FrameType = new wxStaticText(Graphics_Scroller, wxID_ANY, " Frame Type", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameType = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown3 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown3 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown4 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown4 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown4 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Replay = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_2 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Text_Replay = new wxStaticText(Graphics_Scroller, wxID_ANY, " Replay", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Replay = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown5 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown5 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown6 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown6 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown6 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown7 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown7 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown7 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown8 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown8 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 8", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown8 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown9 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown9 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 9", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown9 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown10 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown10 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 10", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown10 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown11 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown11 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown11 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown12 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown12 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 12", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown12 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_SoundID = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_SoundID = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SoundID = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	Graphics_ComboBox_SoundID = new ComboBox_Short(Graphics_Scroller, Graphics_SoundID);
	Graphics_Holder_AttackSoundUsed = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_AttackSoundUsed1 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Text_AttackSoundUsed = new wxStaticText(Graphics_Scroller, wxID_ANY, " Attack Sound Used", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_AttackSoundUsed = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_CheckBox_AttackSoundUsed = new CheckBox_Byte(Graphics_Scroller, "Used", Graphics_AttackSoundUsed);
	Graphics_Holder_FrameCount = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_3 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Text_FrameCount = new wxStaticText(Graphics_Scroller, wxID_ANY, " Frame Count", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameCount = new TextCtrl_UnShort(Graphics_Scroller, "0", NULL);
	Graphics_Holder_AngleCount = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_AngleCount = new wxStaticText(Graphics_Scroller, wxID_ANY, " Angle Count", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_AngleCount = new TextCtrl_UnShort(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown13 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown13 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 13", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown13 = new TextCtrl_Float(Graphics_Scroller, "0", NULL);
	Graphics_Holder_FrameRate = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_FrameRate = new wxStaticText(Graphics_Scroller, wxID_ANY, " Frame Rate", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameRate = new TextCtrl_Float(Graphics_Scroller, "0", NULL);
	Graphics_Holder_ReplayDelay = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_ReplayDelay = new wxStaticText(Graphics_Scroller, wxID_ANY, " Replay Delay", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_ReplayDelay = new TextCtrl_Float(Graphics_Scroller, "0", NULL);
	Graphics_Holder_SequenceType = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_SequenceType = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sequence Type", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SequenceType = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_ID = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_ID = new wxStaticText(Graphics_Scroller, wxID_ANY, " ID", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_ID = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Type = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_1 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Text_Type = new wxStaticText(Graphics_Scroller, wxID_ANY, " Type", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_TypeS = new TextCtrl_Short(Graphics_Scroller, "0", NULL);

	Graphics_Graphics_Buttons->Add(Graphics_Add, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Delete, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Copy, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Paste, 1, wxEXPAND);

	Graphics_Graphics->Add(Graphics_Graphics_Search, 0, wxEXPAND);
	Graphics_Graphics->Add(-1, 2);
	Graphics_Graphics->Add(Graphics_Graphics_List, 1, wxEXPAND);
	Graphics_Graphics->Add(-1, 2);
	Graphics_Graphics->Add(Graphics_Graphics_Buttons, 0, wxEXPAND);

	Graphics_ListArea->Add(-1, 10);
	Graphics_ListArea->Add(Graphics_Graphics, 1, wxEXPAND);
	Graphics_ListArea->Add(-1, 10);
	
	Graphics_Holder_Name->Add(Graphics_Text_Name, 0, wxEXPAND);
	Graphics_Holder_Name->Add(-1, 2);
	Graphics_Holder_Name->Add(Graphics_Name, 1, wxEXPAND);
	Graphics_Holder_Name2->Add(Graphics_Text_Name2, 0, wxEXPAND);
	Graphics_Holder_Name2->Add(-1, 2);
	Graphics_Holder_Name2->Add(Graphics_Name2, 1, wxEXPAND);
	Graphics_Holder_ID->Add(Graphics_Text_ID, 0, wxEXPAND);
	Graphics_Holder_ID->Add(-1, 2);
	Graphics_Holder_ID->Add(Graphics_ID, 1, wxEXPAND);
	Graphics_Holder_Unknown1->Add(Graphics_Text_Unknown1, 0, wxEXPAND);
	Graphics_Holder_Unknown1->Add(-1, 2);
	Graphics_Holder_Unknown1->Add(Graphics_Unknown1, 1, wxEXPAND);
	Graphics_Holder_Unknown2->Add(Graphics_Text_Unknown2, 0, wxEXPAND);
	Graphics_Holder_Unknown2->Add(-1, 2);
	Graphics_Holder_Unknown2->Add(Graphics_Unknown2, 1, wxEXPAND);
	Graphics_Holder_Unknown3->Add(Graphics_Text_Unknown3, 0, wxEXPAND);
	Graphics_Holder_Unknown3->Add(-1, 2);
	Graphics_Holder_Unknown3->Add(Graphics_Unknown3, 1, wxEXPAND);
	Graphics_Holder_Unknown4->Add(Graphics_Text_Unknown4, 0, wxEXPAND);
	Graphics_Holder_Unknown4->Add(-1, 2);
	Graphics_Holder_Unknown4->Add(Graphics_Unknown4, 1, wxEXPAND);
	Graphics_Holder_Unknown5->Add(Graphics_Text_Unknown5, 0, wxEXPAND);
	Graphics_Holder_Unknown5->Add(-1, 2);
	Graphics_Holder_Unknown5->Add(Graphics_Unknown5, 1, wxEXPAND);
	Graphics_Holder_Unknown6->Add(Graphics_Text_Unknown6, 0, wxEXPAND);
	Graphics_Holder_Unknown6->Add(-1, 2);
	Graphics_Holder_Unknown6->Add(Graphics_Unknown6, 1, wxEXPAND);
	Graphics_Holder_Unknown7->Add(Graphics_Text_Unknown7, 0, wxEXPAND);
	Graphics_Holder_Unknown7->Add(-1, 2);
	Graphics_Holder_Unknown7->Add(Graphics_Unknown7, 1, wxEXPAND);
	Graphics_Holder_Unknown8->Add(Graphics_Text_Unknown8, 0, wxEXPAND);
	Graphics_Holder_Unknown8->Add(-1, 2);
	Graphics_Holder_Unknown8->Add(Graphics_Unknown8, 1, wxEXPAND);
	Graphics_Holder_Unknown9->Add(Graphics_Text_Unknown9, 0, wxEXPAND);
	Graphics_Holder_Unknown9->Add(-1, 2);
	Graphics_Holder_Unknown9->Add(Graphics_Unknown9, 1, wxEXPAND);
	Graphics_Holder_Unknown10->Add(Graphics_Text_Unknown10, 0, wxEXPAND);
	Graphics_Holder_Unknown10->Add(-1, 2);
	Graphics_Holder_Unknown10->Add(Graphics_Unknown10, 1, wxEXPAND);
	Graphics_Holder_Unknown11->Add(Graphics_Text_Unknown11, 0, wxEXPAND);
	Graphics_Holder_Unknown11->Add(-1, 2);
	Graphics_Holder_Unknown11->Add(Graphics_Unknown11, 1, wxEXPAND);
	Graphics_Holder_Unknown12->Add(Graphics_Text_Unknown12, 0, wxEXPAND);
	Graphics_Holder_Unknown12->Add(-1, 2);
	Graphics_Holder_Unknown12->Add(Graphics_Unknown12, 1, wxEXPAND);
	Graphics_Holder_Unknown13->Add(Graphics_Text_Unknown13, 0, wxEXPAND);
	Graphics_Holder_Unknown13->Add(-1, 2);
	Graphics_Holder_Unknown13->Add(Graphics_Unknown13, 1, wxEXPAND);
	Graphics_Holder_SLP->Add(Graphics_Text_SLP, 0, wxEXPAND);
	Graphics_Holder_SLP->Add(-1, 2);
	Graphics_Holder_SLP->Add(Graphics_SLP, 1, wxEXPAND);
	Graphics_Holder_FrameType->Add(Graphics_Text_FrameType, 0, wxEXPAND);
	Graphics_Holder_FrameType->Add(-1, 2);
	Graphics_Holder_FrameType->Add(Graphics_FrameType, 1, wxEXPAND);
	Graphics_Holder_Replay->Add(Graphics_Text_Replay, 0, wxEXPAND);
	Graphics_Holder_Replay->Add(-1, 2);
	Graphics_Holder_Replay->Add(Graphics_Replay, 1, wxEXPAND);
	Graphics_Holder_Replay->AddStretchSpacer(1);
	Graphics_Holder_SoundID->Add(Graphics_Text_SoundID, 0, wxEXPAND);
	Graphics_Holder_SoundID->Add(-1, 2);
	Graphics_Holder_SoundID->Add(Graphics_SoundID, 1, wxEXPAND);
	Graphics_Holder_SoundID->Add(Graphics_ComboBox_SoundID, 1, wxEXPAND);
	Graphics_Holder_AttackSoundUsed1->Add(Graphics_AttackSoundUsed, 2, wxEXPAND);
	Graphics_Holder_AttackSoundUsed1->Add(2, -1);
	Graphics_Holder_AttackSoundUsed1->Add(Graphics_CheckBox_AttackSoundUsed, 1, wxEXPAND);
	Graphics_Holder_AttackSoundUsed->Add(Graphics_Text_AttackSoundUsed, 0, wxEXPAND);
	Graphics_Holder_AttackSoundUsed->Add(-1, 2);
	Graphics_Holder_AttackSoundUsed->Add(Graphics_Holder_AttackSoundUsed1, 1, wxEXPAND);
	Graphics_Holder_AttackSoundUsed->AddStretchSpacer(1);
	Graphics_Holder_FrameCount->Add(Graphics_Text_FrameCount, 0, wxEXPAND);
	Graphics_Holder_FrameCount->Add(-1, 2);
	Graphics_Holder_FrameCount->Add(Graphics_FrameCount, 1, wxEXPAND);
	Graphics_Holder_AngleCount->Add(Graphics_Text_AngleCount, 0, wxEXPAND);
	Graphics_Holder_AngleCount->Add(-1, 2);
	Graphics_Holder_AngleCount->Add(Graphics_AngleCount, 1, wxEXPAND);
	Graphics_Holder_FrameRate->Add(Graphics_Text_FrameRate, 0, wxEXPAND);
	Graphics_Holder_FrameRate->Add(-1, 2);
	Graphics_Holder_FrameRate->Add(Graphics_FrameRate, 1, wxEXPAND);
	Graphics_Holder_ReplayDelay->Add(Graphics_Text_ReplayDelay, 0, wxEXPAND);
	Graphics_Holder_ReplayDelay->Add(-1, 2);
	Graphics_Holder_ReplayDelay->Add(Graphics_ReplayDelay, 1, wxEXPAND);
	Graphics_Holder_ReplayDelay->AddStretchSpacer(1);
	Graphics_Holder_SequenceType->Add(Graphics_Text_SequenceType, 0, wxEXPAND);
	Graphics_Holder_SequenceType->Add(-1, 2);
	Graphics_Holder_SequenceType->Add(Graphics_SequenceType, 1, wxEXPAND);
	Graphics_Holder_Type->Add(Graphics_Text_Type, 0, wxEXPAND);
	Graphics_Holder_Type->Add(-1, 2);
	Graphics_Holder_Type->Add(Graphics_TypeS, 1, wxEXPAND);
	
	Graphics_Holder_NameArea->Add(Graphics_Holder_Name, 2, wxEXPAND);
	Graphics_Holder_NameArea->Add(5, -1);
	Graphics_Holder_NameArea->Add(Graphics_Holder_Name2, 2, wxEXPAND);
	Graphics_Holder_NameArea->Add(5, -1);
	Graphics_Holder_NameArea->Add(Graphics_Holder_ID, 1, wxEXPAND);
	
	Graphics_Holder_1->Add(Graphics_Holder_Type, 1, wxEXPAND);
	Graphics_Holder_1->Add(5, -1);
	Graphics_Holder_1->Add(Graphics_Holder_SequenceType, 1, wxEXPAND);
	Graphics_Holder_1->Add(5, -1);
	Graphics_Holder_1->Add(Graphics_Holder_SLP, 1, wxEXPAND);
	Graphics_Holder_1->Add(5, -1);
	Graphics_Holder_1->Add(Graphics_Holder_FrameType, 1, wxEXPAND);
	
	Graphics_Holder_2->Add(Graphics_Holder_Replay, 1, wxEXPAND);
	Graphics_Holder_2->Add(5, -1);
	Graphics_Holder_2->Add(Graphics_Holder_ReplayDelay, 1, wxEXPAND);
	Graphics_Holder_2->Add(5, -1);
	Graphics_Holder_2->Add(Graphics_Holder_SoundID, 1, wxEXPAND);
	Graphics_Holder_2->Add(5, -1);
	Graphics_Holder_2->Add(Graphics_Holder_AttackSoundUsed, 1, wxEXPAND);
	
	Graphics_Holder_3->Add(Graphics_Holder_FrameCount, 1, wxEXPAND);
	Graphics_Holder_3->Add(5, -1);
	Graphics_Holder_3->Add(Graphics_Holder_AngleCount, 1, wxEXPAND);
	Graphics_Holder_3->Add(5, -1);
	Graphics_Holder_3->Add(Graphics_Holder_FrameRate, 1, wxEXPAND);
	
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown1, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown2, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown3, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown4, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown5, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown6, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown7, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown8, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown9, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown10, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown11, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown12, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown13, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_NameArea, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_1, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_2, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_3, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_Unknowns, 0, wxEXPAND);
	
	Graphics_ScrollerWindows->Add(Graphics_ScrollerWindowsSpace, 1, wxEXPAND);
	Graphics_ScrollerWindows->Add(5, -1);

	Graphics_Scroller->SetSizer(Graphics_ScrollerWindows);
	Graphics_Scroller->SetScrollRate(0, 15);

	Graphics_DataArea->Add(-1, 10);
	Graphics_DataArea->Add(Graphics_Scroller, 1, wxEXPAND);
	Graphics_DataArea->Add(-1, 10);

	Graphics_Main->Add(10, -1);
	Graphics_Main->Add(Graphics_ListArea, 1, wxEXPAND);
	Graphics_Main->Add(10, -1);
	Graphics_Main->Add(Graphics_DataArea, 3, wxEXPAND);
	Graphics_Main->Add(10, -1);
	
	Graphics_ID->Enable(false);

	Tab_Graphics->SetSizer(Graphics_Main);
	
	Connect(Graphics_Graphics_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
	Connect(Graphics_Graphics_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicsSelect));
	Connect(Graphics_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsAdd));
	Connect(Graphics_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsDelete));
	Connect(Graphics_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsCopy));
	Connect(Graphics_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsPaste));

	Graphics_Name->Connect(Graphics_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Graphics_Name2->Connect(Graphics_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);

}
