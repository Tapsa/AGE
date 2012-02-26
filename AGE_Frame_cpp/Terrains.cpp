/* AGEFrame_cpp/Terrains.cpp */

#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetTerrainName(short &Index)
{
	string Name = "";
	if(GenieFile->Terrains[Index].Name != "")
	{
		Name = GenieFile->Terrains[Index].Name;
	}
	else
	{
		Name = "New Terrain";
	}
	return Name;
}

void AGE_Frame::OnTerrainsSearch(wxCommandEvent& Event)
{
	ListTerrains(false);
}

void AGE_Frame::ListTerrains(bool Sized)
{
	string Name;
	string CompareText;

	SearchText = wxString(Terrains_Terrains_Search->GetValue()).Lower();
	ExcludeText = wxString(Terrains_Terrains_Search_R->GetValue()).Lower();
	short Selection = Terrains_Terrains_List->GetSelection();
	if(Terrains_Terrains_List->GetCount() > 0)
	{
		Terrains_Terrains_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}

	short IDsCount = 7, TerrainIDs[IDsCount];
	if(Sized)
	{
		for(short loop = 0;loop < 2;loop++)
		{
			TerrainIDs[loop] = Units_ComboBox_PlacementBypassTerrain[loop]->GetSelection();
			TerrainIDs[loop+2] = Units_ComboBox_PlacementTerrain[loop]->GetSelection();
		}
		TerrainIDs[4] = Units_ComboBox_TerrainID->GetSelection();
		TerrainIDs[5] = Terrains_ComboBox_TerrainReplacementID->GetSelection();
		TerrainIDs[6] = Borders_ComboBox_BorderTerrain->GetSelection();

		for(short loop = 0;loop < 2;loop++)
		{
			if(Units_ComboBox_PlacementBypassTerrain[loop]->GetCount() > 0)
			{
				Units_ComboBox_PlacementBypassTerrain[loop]->Clear();
			}
			if(Units_ComboBox_PlacementTerrain[loop]->GetCount() > 0)
			{
				Units_ComboBox_PlacementTerrain[loop]->Clear();
			}
		}
		if(Units_ComboBox_TerrainID->GetCount() > 0)
		{
			Units_ComboBox_TerrainID->Clear();
		}
		if(Terrains_ComboBox_TerrainReplacementID->GetCount() > 0)
		{
			Terrains_ComboBox_TerrainReplacementID->Clear();
		}
		if(Borders_ComboBox_BorderTerrain->GetCount() > 0)
		{
			Borders_ComboBox_BorderTerrain->Clear();
		}

		for(short loop = 0;loop < IDsCount;loop++)
		{
			if(TerrainIDs[loop] == wxNOT_FOUND)
			{
				TerrainIDs[loop] = 0;
			}
		}

		for(short loop = 0;loop < 2;loop++)
		{
			Units_ComboBox_PlacementBypassTerrain[loop]->Append("-1 - None");
			Units_ComboBox_PlacementTerrain[loop]->Append("-1 - None");
		}
		Units_ComboBox_TerrainID->Append("-1 - None");
		Terrains_ComboBox_TerrainReplacementID->Append("-1 - None");
		Borders_ComboBox_BorderTerrain->Append("-1 - None");
	}

	for(short loop = 0;loop < GenieFile->Terrains.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTerrainName(loop);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText))
		{
			Terrains_Terrains_List->Append(Name, (void*)&GenieFile->Terrains[loop]);
		}
		if(Sized)
		{
			for(short loop = 0;loop < 2;loop++)
			{
				Units_ComboBox_PlacementBypassTerrain[loop]->Append(Name);
				Units_ComboBox_PlacementTerrain[loop]->Append(Name);
			}
			Units_ComboBox_TerrainID->Append(Name);
			Terrains_ComboBox_TerrainReplacementID->Append(Name);
			Borders_ComboBox_BorderTerrain->Append(Name);
		}
	}

	Terrains_Terrains_List->SetSelection(0);
	Terrains_Terrains_List->SetFirstItem(Selection - 3);
	Terrains_Terrains_List->SetSelection(Selection);
	if(Sized)
	{
		for(short loop = 0;loop < 2;loop++)
		{
			Units_ComboBox_PlacementBypassTerrain[loop]->SetSelection(TerrainIDs[loop]);
			Units_ComboBox_PlacementTerrain[loop]->SetSelection(TerrainIDs[loop+2]);
		}
		Units_ComboBox_TerrainID->SetSelection(TerrainIDs[4]);
		Terrains_ComboBox_TerrainReplacementID->SetSelection(TerrainIDs[5]);
		Borders_ComboBox_BorderTerrain->SetSelection(TerrainIDs[6]);
	}

	wxCommandEvent E;
	OnTerrainsSelect(E);

	SearchText = wxString(TerRestrict_Terrains_Search->GetValue()).Lower();
	ExcludeText = wxString(TerRestrict_Terrains_Search_R->GetValue()).Lower();
	short Selection2 = TerRestrict_Terrains_List->GetSelection();
	if(TerRestrict_Terrains_List->GetCount() > 0)
	{
		TerRestrict_Terrains_List->Clear();
	}
	if(Selection2 == wxNOT_FOUND)
	{
		Selection2 = 0;
	}
	for(short loop = 0;loop < GenieFile->TerrainRestrictions[0].TerrainAccessible.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - A"+lexical_cast<string>((bool)GenieFile->TerrainRestrictions[TerRestrictID].TerrainAccessible[loop]);
		if(GameVersion >= 2)
		Name += " B"+lexical_cast<string>((bool)GenieFile->TerrainRestrictions[TerRestrictID].TerrainPassGraphics[loop].Buildable);
		Name += " - "+GetTerrainName(loop);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText))
		{
			TerRestrict_Terrains_List->Append(Name, (void*)&GenieFile->Terrains[loop]);
		}
	}
	TerRestrict_Terrains_List->SetSelection(Selection2);

	OnTerrainRestrictionsTerrainSelect(E);
}

void AGE_Frame::OnTerrainsSelect(wxCommandEvent& Event)
{
	short Selection = Terrains_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Terrains_Terrains_List->GetCount() - 1;
			Terrains_Terrains_List->SetSelection(Selection);
		}
		gdat::Terrain * TerrainPointer = (gdat::Terrain*)Terrains_Terrains_List->GetClientData(Selection);
		TerrainID = TerrainPointer - (&GenieFile->Terrains[0]);
		Terrains_Unknown1->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown1));
		Terrains_Unknown1->Container = &TerrainPointer->Unknown1;
		Terrains_Unknown2->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown2));
		Terrains_Unknown2->Container = &TerrainPointer->Unknown2;
		Terrains_Name->ChangeValue(TerrainPointer->Name);
		Terrains_Name->Container = &TerrainPointer->Name;
		Terrains_Name2->ChangeValue(TerrainPointer->Name2);
		Terrains_Name2->Container = &TerrainPointer->Name2;
		Terrains_SLP->ChangeValue(lexical_cast<string>(TerrainPointer->SLP));
		Terrains_SLP->Container = &TerrainPointer->SLP;
		Terrains_Unknown3->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown3));
		Terrains_Unknown3->Container = &TerrainPointer->Unknown3;
		Terrains_SoundID->ChangeValue(lexical_cast<string>(TerrainPointer->SoundID));
		Terrains_SoundID->Container = &TerrainPointer->SoundID;
		Terrains_ComboBox_SoundID->SetSelection(TerrainPointer->SoundID + 1);
		if(GameVersion >= 2)
		{
			Terrains_BlendPriority->ChangeValue(lexical_cast<string>(TerrainPointer->BlendPriority));
			Terrains_BlendPriority->Container = &TerrainPointer->BlendPriority;
			Terrains_BlendType->ChangeValue(lexical_cast<string>(TerrainPointer->BlendType));
			Terrains_BlendType->Container = &TerrainPointer->BlendType;
		}
		for(short loop = 0;loop < 3;loop++)
		{
			Terrains_Colours[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->Colours[loop]));
			Terrains_Colours[loop]->Container = &TerrainPointer->Colours[loop];
		}
		Terrains_Unknown5->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown5));
		Terrains_Unknown5->Container = &TerrainPointer->Unknown5;
		Terrains_Unknown6->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown6));
		Terrains_Unknown6->Container = &TerrainPointer->Unknown6;
		for(short loop = 0;loop < 23;loop++)
		{
			Terrains_Unknown7[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->Unknown7[loop]));
			Terrains_Unknown7[loop]->Container = &TerrainPointer->Unknown7[loop];
		}
		Terrains_FrameCount->ChangeValue(lexical_cast<string>(TerrainPointer->FrameCount));
		Terrains_FrameCount->Container = &TerrainPointer->FrameCount;
		Terrains_Unknown8[0]->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown8[0]));
		Terrains_Unknown8[0]->Container = &TerrainPointer->Unknown8[0];
		Terrains_Unknown8[1]->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown8[1]));
		Terrains_Unknown8[1]->Container = &TerrainPointer->Unknown8[1];
		for(short loop = 0;loop < 54;loop++)
		{
			Terrains_Unknown9[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown9[loop]));
			Terrains_Unknown9[loop]->Container = &TerrainPointer->Unknown9[loop];
		}
		Terrains_TerrainReplacementID->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainReplacementID));
		Terrains_TerrainReplacementID->Container = &TerrainPointer->TerrainReplacementID;
		Terrains_ComboBox_TerrainReplacementID->SetSelection(TerrainPointer->TerrainReplacementID + 1);
		Terrains_TerrainDimensions[0]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainDimensions.first));
		Terrains_TerrainDimensions[0]->Container = &TerrainPointer->TerrainDimensions.first;
		Terrains_TerrainDimensions[1]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainDimensions.second));
		Terrains_TerrainDimensions[1]->Container = &TerrainPointer->TerrainDimensions.second;
		short Unknown10;
		for(short loop = 64;loop < 84;loop++)
		{
			if(GameVersion >= 3)
			{
				Unknown10 = 84;
			}
			else
			{
				Unknown10 = 64;
			}
		}
		for(short loop = 0;loop < Unknown10;loop++)
		{
			Terrains_Unknown10[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->Unknown10[loop]));
			Terrains_Unknown10[loop]->Container = &TerrainPointer->Unknown10[loop];
		}
		for(short loop = 0;loop < 30;loop++)
		{
			Terrains_TerrainUnitID[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainUnitID[loop]));
			Terrains_TerrainUnitID[loop]->Container = &TerrainPointer->TerrainUnitID[loop];
			Terrains_ComboBox_TerrainUnitID[loop]->SetSelection(TerrainPointer->TerrainUnitID[loop] + 1);
			Terrains_TerrainUnitDensity[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainUnitDensity[loop]));
			Terrains_TerrainUnitDensity[loop]->Container = &TerrainPointer->TerrainUnitDensity[loop];
		}
		for(short loop = 0;loop < 30;loop++)
		{
			Terrains_Unknown11[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->Unknown11[loop]));
			Terrains_Unknown11[loop]->Container = &TerrainPointer->Unknown11[loop];
		}
		Terrains_NumberOfTerrainUnitsUsed->ChangeValue(lexical_cast<string>(TerrainPointer->NumberOfTerrainUnitsUsed));
		Terrains_NumberOfTerrainUnitsUsed->Container = &TerrainPointer->NumberOfTerrainUnitsUsed;
		if(GameVersion >= 4)
		{
			for(short loop = 0;loop < 24;loop++)
			{
				Terrains_SUnknown1[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->SWGBUnknown1[loop]));
				Terrains_SUnknown1[loop]->Container = &TerrainPointer->SWGBUnknown1[loop];
			}
		}
		Added = false;
	}
}

void AGE_Frame::OnTerrainsAdd(wxCommandEvent& Event) // Their count is hardcoded.
{
	gdat::Terrain Temp1;
	GenieFile->Terrains.push_back(Temp1);
	gdat::TerrainPassGraphic Temp2;
	for(int loop = 0;loop < GenieFile->TerrainRestrictions.size();loop++)
	{
		GenieFile->TerrainRestrictions[loop].TerrainAccessible.push_back(0);
		GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.push_back(Temp2);
	}
	Added = true;
	ListTerrains();
}

void AGE_Frame::OnTerrainsInsert(wxCommandEvent& Event) // Their count is hardcoded.
{
	short Selection = Terrains_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		gdat::Terrain Temp1;
		GenieFile->Terrains.insert(GenieFile->Terrains.begin() + TerrainID, Temp1);
		gdat::TerrainPassGraphic Temp2;
		for(int loop = 0;loop < GenieFile->TerrainRestrictions.size();loop++)
		{
			GenieFile->TerrainRestrictions[loop].TerrainAccessible.insert(GenieFile->TerrainRestrictions[loop].TerrainAccessible.begin() + TerrainID, 0);
			GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.insert(GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.begin() + TerrainID, Temp2);
		}
		ListTerrains();
	}
}

void AGE_Frame::OnTerrainsDelete(wxCommandEvent& Event) // Their count is hardcoded.
{
	short Selection = Terrains_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		wxBusyCursor WaitCursor;
		GenieFile->Terrains.erase(GenieFile->Terrains.begin() + TerrainID);
		for(int loop = 0;loop < GenieFile->TerrainRestrictions.size();loop++)
		{
			GenieFile->TerrainRestrictions[loop].TerrainAccessible.erase(GenieFile->TerrainRestrictions[loop].TerrainAccessible.begin() + TerrainID);
			GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.erase(GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.begin() + TerrainID);
		}
		if(Selection == Terrains_Terrains_List->GetCount() - 1)
		Terrains_Terrains_List->SetSelection(Selection - 1);
		ListTerrains();
	}
}

void AGE_Frame::OnTerrainsCopy(wxCommandEvent& Event)
{
	short Selection = Terrains_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TerrainCopy = *(gdat::Terrain*)Terrains_Terrains_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnTerrainsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Terrains_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::Terrain*)Terrains_Terrains_List->GetClientData(Selection) = TerrainCopy;
		ListTerrains();
	}
}

void AGE_Frame::CreateTerrainControls()
{

	Terrains_Main = new wxBoxSizer(wxHORIZONTAL);
	Terrains_ListArea = new wxBoxSizer(wxVERTICAL);
	Terrains_Terrains_Buttons = new wxGridSizer(3, 0, 0);
	Tab_Terrains = new wxPanel(TabBar_Data, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	Terrains_Terrains = new wxStaticBoxSizer(wxVERTICAL, Tab_Terrains, "Terrains");
	Terrains_Terrains_Search = new wxTextCtrl(Tab_Terrains, wxID_ANY);
	Terrains_Terrains_Search_R = new wxTextCtrl(Tab_Terrains, wxID_ANY);
//	Terrains_Terrains_UseAnd = new wxCheckBox(Tab_Terrains, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20), 0, wxDefaultValidator);
	Terrains_Terrains_List = new wxListBox(Tab_Terrains, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	Terrains_Add = new wxButton(Tab_Terrains, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Terrains_Insert = new wxButton(Tab_Terrains, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Terrains_Delete = new wxButton(Tab_Terrains, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Terrains_Copy = new wxButton(Tab_Terrains, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Terrains_Paste = new wxButton(Tab_Terrains, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));

	Terrains_DataArea = new wxBoxSizer(wxVERTICAL);
	Terrains_Scroller = new wxScrolledWindow(Tab_Terrains, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Terrains_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	Terrains_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	Terrains_Holder_NameArea = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Grid_Area1 = new wxGridSizer(4, 5, 5);
	Terrains_Holder_UnknownArea = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknowns1 = new wxGridSizer(5, 5, 5);
	Terrains_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown1 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown1 = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown2 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown2 = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Name = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Name = new wxStaticText(Terrains_Scroller, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name = new TextCtrl_String(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Name2 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Name2 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Name 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name2 = new TextCtrl_String(Terrains_Scroller, "0", NULL);
	Terrains_Holder_SLP = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_SLP = new wxStaticText(Terrains_Scroller, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SLP = new TextCtrl_Long(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown3 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown3 = new TextCtrl_Long(Terrains_Scroller, "0", NULL);
	Terrains_Holder_SoundID = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_SoundID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SoundID = new TextCtrl_Long(Terrains_Scroller, "0", NULL);
	Terrains_ComboBox_SoundID = new ComboBox_Long(Terrains_Scroller, Terrains_SoundID);
	Terrains_Holder_BlendPriority = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_BlendPriority = new wxStaticText(Terrains_Scroller, wxID_ANY, " Blend Priority", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_BlendPriority = new TextCtrl_Long(Terrains_Scroller, "0", NULL);
	Terrains_Holder_BlendType = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_BlendType = new wxStaticText(Terrains_Scroller, wxID_ANY, " Blend Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_BlendType = new TextCtrl_Long(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Colours = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Colours = new wxGridSizer(3, 0, 0);
	Terrains_Text_Colours = new wxStaticText(Terrains_Scroller, wxID_ANY, " Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 3;loop++)
	Terrains_Colours[loop] = new TextCtrl_Byte(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown5 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown5 = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown6 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown6 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown6 = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown7 = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknown7 = new wxGridSizer(12, 0, 0);
	Terrains_Text_Unknown7 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 23;loop++)
	Terrains_Unknown7[loop] = new TextCtrl_Byte(Terrains_Scroller, "0", NULL);
	Terrains_Holder_FrameCount = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_FrameCount = new wxStaticText(Terrains_Scroller, wxID_ANY, " Frame Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_FrameCount = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown8 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown8 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 8", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown8[0] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Unknown8[1] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown9 = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknown9 = new wxGridSizer(6, 0, 0);
	Terrains_Text_Unknown9 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 9", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 54;loop++)
	{
		Terrains_Unknown9[loop] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	}
	Terrains_Holder_TerrainReplacementID = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainReplacementID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Replacement", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainReplacementID = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_ComboBox_TerrainReplacementID = new ComboBox_Short(Terrains_Scroller, Terrains_TerrainReplacementID);
	Terrains_Holder_TerrainDimensions = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainDimensions = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Dimensions", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainDimensions[0] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_TerrainDimensions[1] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown10 = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknown10 = new wxGridSizer(12, 0, 0);
	Terrains_Text_Unknown10 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 10", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 84;loop++)
	Terrains_Unknown10[loop] = new TextCtrl_Byte(Terrains_Scroller, "0", NULL);
	Terrains_Holder_TerrainUnits = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Holder_TerrainUnitID = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_TerrainUnitID = new wxGridSizer(2, 0, 0);
	Terrains_Holder_TerrainUnitDensity = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainUnitID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Text_TerrainUnitDensity = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit Density", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 30;loop++)
	{
		Terrains_TerrainUnitID[loop] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
		Terrains_ComboBox_TerrainUnitID[loop] = new ComboBox_Short(Terrains_Scroller, Terrains_TerrainUnitID[loop]);
		Terrains_TerrainUnitDensity[loop] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	}
	Terrains_Holder_Unknown11 = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknown11 = new wxGridSizer(12, 0, 0);
	Terrains_Text_Unknown11 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 30;loop++)
	Terrains_Unknown11[loop] = new TextCtrl_Byte(Terrains_Scroller, "0", NULL);
	Terrains_Holder_NumberOfTerrainUnitsUsed = new wxBoxSizer(wxVERTICAL);
	Terrains_Holder_NumberOfTerrainUnitsUsed1 = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Text_NumberOfTerrainUnitsUsed = new wxStaticText(Terrains_Scroller, wxID_ANY, " Number Of Terrain Units Used", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_NumberOfTerrainUnitsUsed = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_SUnknown1 = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_SUnknown1 = new wxGridSizer(12, 0, 0);
	Terrains_Text_SUnknown1 = new wxStaticText(Terrains_Scroller, wxID_ANY, " SW Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 24;loop++)
	Terrains_SUnknown1[loop] = new TextCtrl_Byte(Terrains_Scroller, "0", NULL);

	Terrains_Terrains_Buttons->Add(Terrains_Add, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Insert, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Delete, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Copy, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Paste, 1, wxEXPAND);

	Terrains_Terrains->Add(Terrains_Terrains_Search, 0, wxEXPAND);
	Terrains_Terrains->Add(Terrains_Terrains_Search_R, 0, wxEXPAND);
//	Terrains_Terrains->Add(Terrains_Terrains_UseAnd, 0, wxEXPAND);
	Terrains_Terrains->Add(-1, 2);
	Terrains_Terrains->Add(Terrains_Terrains_List, 1, wxEXPAND);
	Terrains_Terrains->Add(-1, 2);
	Terrains_Terrains->Add(Terrains_Terrains_Buttons, 0, wxEXPAND);

	Terrains_ListArea->Add(-1, 10);
	Terrains_ListArea->Add(Terrains_Terrains, 1, wxEXPAND);
	Terrains_ListArea->Add(-1, 10);

	Terrains_Holder_Unknown1->Add(Terrains_Text_Unknown1, 0, wxEXPAND);
	Terrains_Holder_Unknown1->Add(Terrains_Unknown1, 1, wxEXPAND);
	Terrains_Holder_Unknown2->Add(Terrains_Text_Unknown2, 0, wxEXPAND);
	Terrains_Holder_Unknown2->Add(Terrains_Unknown2, 1, wxEXPAND);
	Terrains_Holder_Name->Add(Terrains_Text_Name, 0, wxEXPAND);
	Terrains_Holder_Name->Add(Terrains_Name, 1, wxEXPAND);
	Terrains_Holder_Name2->Add(Terrains_Text_Name2, 0, wxEXPAND);
	Terrains_Holder_Name2->Add(Terrains_Name2, 1, wxEXPAND);
	Terrains_Holder_SLP->Add(Terrains_Text_SLP, 0, wxEXPAND);
	Terrains_Holder_SLP->Add(Terrains_SLP, 0, wxEXPAND);
	Terrains_Holder_Unknown3->Add(Terrains_Text_Unknown3, 0, wxEXPAND);
	Terrains_Holder_Unknown3->Add(Terrains_Unknown3, 1, wxEXPAND);
	Terrains_Holder_SoundID->Add(Terrains_Text_SoundID, 0, wxEXPAND);
	Terrains_Holder_SoundID->Add(Terrains_SoundID, 1, wxEXPAND);
	Terrains_Holder_SoundID->Add(Terrains_ComboBox_SoundID, 1, wxEXPAND);
	Terrains_Holder_BlendPriority->Add(Terrains_Text_BlendPriority, 0, wxEXPAND);
	Terrains_Holder_BlendPriority->Add(Terrains_BlendPriority, 0, wxEXPAND);
	Terrains_Holder_BlendType->Add(Terrains_Text_BlendType, 0, wxEXPAND);
	Terrains_Holder_BlendType->Add(Terrains_BlendType, 0, wxEXPAND);
	for(short loop = 0;loop < 3;loop++)
	Terrains_Grid_Colours->Add(Terrains_Colours[loop], 1, wxEXPAND);
	Terrains_Holder_Colours->Add(Terrains_Text_Colours, 0, wxEXPAND);
	Terrains_Holder_Colours->Add(Terrains_Grid_Colours, 0, wxEXPAND);
	Terrains_Holder_Unknown5->Add(Terrains_Text_Unknown5, 0, wxEXPAND);
	Terrains_Holder_Unknown5->Add(Terrains_Unknown5, 1, wxEXPAND);
	Terrains_Holder_Unknown6->Add(Terrains_Text_Unknown6, 0, wxEXPAND);
	Terrains_Holder_Unknown6->Add(Terrains_Unknown6, 1, wxEXPAND);
	for(short loop = 0;loop < 23;loop++)
	Terrains_Grid_Unknown7->Add(Terrains_Unknown7[loop], 1, wxEXPAND);
	Terrains_Holder_Unknown7->Add(Terrains_Text_Unknown7, 0, wxEXPAND);
	Terrains_Holder_Unknown7->Add(Terrains_Grid_Unknown7, 0, wxEXPAND);
	Terrains_Holder_FrameCount->Add(Terrains_Text_FrameCount, 0, wxEXPAND);
	Terrains_Holder_FrameCount->Add(Terrains_FrameCount, 0, wxEXPAND);
	Terrains_Holder_Unknown8->Add(Terrains_Text_Unknown8, 0, wxEXPAND);
	Terrains_Holder_Unknown8->Add(Terrains_Unknown8[0], 1, wxEXPAND);
	Terrains_Holder_Unknown8->Add(Terrains_Unknown8[1], 1, wxEXPAND);
	Terrains_Holder_Unknown9->Add(Terrains_Text_Unknown9, 0, wxEXPAND);
	Terrains_Holder_Unknown9->Add(Terrains_Grid_Unknown9, 0, wxEXPAND);
	for(short loop = 0;loop < 54;loop++)
	{
		Terrains_Grid_Unknown9->Add(Terrains_Unknown9[loop], 1, wxEXPAND);
	}
	Terrains_Holder_TerrainReplacementID->Add(Terrains_Text_TerrainReplacementID, 0, wxEXPAND);
	Terrains_Holder_TerrainReplacementID->Add(Terrains_TerrainReplacementID, 1, wxEXPAND);
	Terrains_Holder_TerrainReplacementID->Add(Terrains_ComboBox_TerrainReplacementID, 1, wxEXPAND);
	Terrains_Holder_TerrainDimensions->Add(Terrains_Text_TerrainDimensions, 0, wxEXPAND);
	Terrains_Holder_TerrainDimensions->Add(Terrains_TerrainDimensions[0], 1, wxEXPAND);
	Terrains_Holder_TerrainDimensions->Add(Terrains_TerrainDimensions[1], 1, wxEXPAND);
	for(short loop = 0;loop < 84;loop++)
	Terrains_Grid_Unknown10->Add(Terrains_Unknown10[loop], 1, wxEXPAND);
	Terrains_Holder_Unknown10->Add(Terrains_Text_Unknown10, 0, wxEXPAND);
	Terrains_Holder_Unknown10->Add(Terrains_Grid_Unknown10, 0, wxEXPAND);
	Terrains_Holder_TerrainUnitDensity->Add(Terrains_Text_TerrainUnitDensity, 0, wxEXPAND);
	for(short loop = 0;loop < 30;loop++)
	{
		Terrains_Grid_TerrainUnitID->Add(Terrains_TerrainUnitID[loop], 1, wxEXPAND);
		Terrains_Grid_TerrainUnitID->Add(Terrains_ComboBox_TerrainUnitID[loop], 1, wxEXPAND);
		Terrains_Holder_TerrainUnitDensity->Add(Terrains_TerrainUnitDensity[loop], 1, wxEXPAND);
	}
	Terrains_Holder_TerrainUnitID->Add(Terrains_Text_TerrainUnitID, 0, wxEXPAND);
	Terrains_Holder_TerrainUnitID->Add(Terrains_Grid_TerrainUnitID, 0, wxEXPAND);
	for(short loop = 0;loop < 30;loop++)
	Terrains_Grid_Unknown11->Add(Terrains_Unknown11[loop], 1, wxEXPAND);
	Terrains_Holder_Unknown11->Add(Terrains_Text_Unknown11, 0, wxEXPAND);
	Terrains_Holder_Unknown11->Add(Terrains_Grid_Unknown11, 1, wxEXPAND);
	Terrains_Holder_NumberOfTerrainUnitsUsed->Add(Terrains_Text_NumberOfTerrainUnitsUsed, 0, wxEXPAND);
	Terrains_Holder_NumberOfTerrainUnitsUsed->Add(Terrains_NumberOfTerrainUnitsUsed, 1, wxEXPAND);
	for(short loop = 0;loop < 24;loop++)
	Terrains_Grid_SUnknown1->Add(Terrains_SUnknown1[loop], 1, wxEXPAND);
	Terrains_Holder_SUnknown1->Add(Terrains_Text_SUnknown1, 0, wxEXPAND);
	Terrains_Holder_SUnknown1->Add(Terrains_Grid_SUnknown1, 0, wxEXPAND);

	Terrains_Holder_NameArea->Add(Terrains_Holder_Name, 1, wxEXPAND);
	Terrains_Holder_NameArea->Add(5, -1);
	Terrains_Holder_NameArea->Add(Terrains_Holder_Name2, 1, wxEXPAND);

	Terrains_Grid_Area1->Add(Terrains_Holder_SLP, 1, wxEXPAND);
	Terrains_Grid_Area1->Add(Terrains_Holder_SoundID, 1, wxEXPAND);
	Terrains_Grid_Area1->Add(Terrains_Holder_BlendPriority, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_Grid_Area1->Add(Terrains_Holder_BlendType, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_Grid_Area1->Add(Terrains_Holder_Colours, 1, wxEXPAND);
	Terrains_Grid_Area1->Add(Terrains_Holder_FrameCount, 1, wxEXPAND);
	Terrains_Grid_Area1->Add(Terrains_Holder_TerrainReplacementID, 1, wxEXPAND);
	Terrains_Grid_Area1->Add(Terrains_Holder_TerrainDimensions, 1, wxEXPAND);

	Terrains_Holder_TerrainUnits->Add(Terrains_Holder_TerrainUnitID, 2, wxEXPAND);
	Terrains_Holder_TerrainUnits->Add(5, -1);
	Terrains_Holder_TerrainUnits->Add(Terrains_Holder_TerrainUnitDensity, 1, wxEXPAND);
	Terrains_Holder_TerrainUnits->AddStretchSpacer(1);

	Terrains_Grid_Unknowns1->Add(Terrains_Holder_Unknown1, 1, wxEXPAND);
	Terrains_Grid_Unknowns1->Add(Terrains_Holder_Unknown2, 1, wxEXPAND);
	Terrains_Grid_Unknowns1->Add(Terrains_Holder_Unknown3, 1, wxEXPAND);
	Terrains_Grid_Unknowns1->Add(Terrains_Holder_Unknown5, 1, wxEXPAND);
	Terrains_Grid_Unknowns1->Add(Terrains_Holder_Unknown6, 1, wxEXPAND);
	Terrains_Holder_UnknownArea->Add(Terrains_Grid_Unknowns1, 0, wxEXPAND);
	Terrains_Holder_UnknownArea->Add(-1, 5);
	Terrains_Holder_UnknownArea->Add(Terrains_Holder_Unknown8, 0, wxEXPAND);
	Terrains_Holder_UnknownArea->Add(-1, 5);
	Terrains_Holder_UnknownArea->Add(Terrains_Holder_Unknown9, 0, wxEXPAND);
	Terrains_Holder_UnknownArea->Add(-1, 5);
	Terrains_Holder_UnknownArea->Add(Terrains_Holder_Unknown7, 0, wxEXPAND);
	Terrains_Holder_UnknownArea->Add(-1, 5);
	Terrains_Holder_UnknownArea->Add(Terrains_Holder_Unknown10, 0, wxEXPAND);
	Terrains_Holder_UnknownArea->Add(-1, 5);
	Terrains_Holder_UnknownArea->Add(Terrains_Holder_Unknown11, 0, wxEXPAND);
	Terrains_Holder_UnknownArea->Add(-1, 5);
	Terrains_Holder_UnknownArea->Add(Terrains_Holder_SUnknown1, 0, wxEXPAND);

	Terrains_Holder_NumberOfTerrainUnitsUsed1->Add(Terrains_Holder_NumberOfTerrainUnitsUsed, 1, wxEXPAND);
	Terrains_Holder_NumberOfTerrainUnitsUsed1->AddStretchSpacer(3);

	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_NameArea, 0, wxEXPAND);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Grid_Area1, 0, wxEXPAND);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_NumberOfTerrainUnitsUsed1, 0, wxEXPAND);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_TerrainUnits, 0, wxEXPAND);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_UnknownArea, 0, wxEXPAND);

	Terrains_ScrollerWindows->Add(Terrains_ScrollerWindowsSpace, 1, wxEXPAND);
	Terrains_ScrollerWindows->Add(5, -1);

	Terrains_Scroller->SetSizer(Terrains_ScrollerWindows);
	Terrains_Scroller->SetScrollRate(0, 15);

	Terrains_DataArea->Add(-1, 10);
	Terrains_DataArea->Add(Terrains_Scroller, 1, wxEXPAND);
	Terrains_DataArea->Add(-1, 10);

	Terrains_Main->Add(10, -1);
	Terrains_Main->Add(Terrains_ListArea, 1, wxEXPAND);
	Terrains_Main->Add(10, -1);
	Terrains_Main->Add(Terrains_DataArea, 3, wxEXPAND);
	Terrains_Main->Add(10, -1);

//	Terrains_Terrains_UseAnd->Show(false);

	Tab_Terrains->SetSizer(Terrains_Main);

	Connect(Terrains_Terrains_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	Connect(Terrains_Terrains_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	Connect(Terrains_Terrains_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainsSelect));
	Connect(Terrains_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsAdd));
	Connect(Terrains_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsInsert));
	Connect(Terrains_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsDelete));
	Connect(Terrains_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsCopy));
	Connect(Terrains_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsPaste));

	Terrains_Name->Connect(Terrains_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Terrains_Name2->Connect(Terrains_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);

}
