
#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetTerrainName(short &Index)
{
	if(GenieFile->Terrains[Index].Name != "")
		return GenieFile->Terrains[Index].Name;
	return "New Terrain";
}

void AGE_Frame::OnTerrainsSearch(wxCommandEvent& Event)
{
	ListTerrains(false);
}

void AGE_Frame::ListTerrains(bool Sized)
{
	wxString Name, CompareText;
	SearchText = Terrains_Terrains_Search->GetValue().Lower();
	ExcludeText = Terrains_Terrains_Search_R->GetValue().Lower();

	auto Selections = Terrains_Terrains_List->GetSelections(Items);
	if(Terrains_Terrains_List->GetCount() > 0) Terrains_Terrains_List->Clear();

	short IDCount = 7, TerrainIDs[IDCount];
	if(Sized)
	{
		for(short loop=0; loop < 2; loop++)
		{
			TerrainIDs[loop] = Units_ComboBox_PlacementBypassTerrain[loop]->GetSelection();
			TerrainIDs[loop+2] = Units_ComboBox_PlacementTerrain[loop]->GetSelection();
		}
		TerrainIDs[4] = Units_ComboBox_TerrainID->GetSelection();
		TerrainIDs[5] = Terrains_ComboBox_TerrainReplacementID->GetSelection();
		TerrainIDs[6] = Borders_ComboBox_BorderTerrain->GetSelection();

		for(short loop=0; loop < 2; loop++)
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

		for(short loop=0; loop < IDCount; loop++)
		{
			if(TerrainIDs[loop] == wxNOT_FOUND)
			{
				TerrainIDs[loop] = 0;
			}
		}

		for(short loop=0; loop < 2; loop++)
		{
			Units_ComboBox_PlacementBypassTerrain[loop]->Append("-1 - None");
			Units_ComboBox_PlacementTerrain[loop]->Append("-1 - None");
		}
		Units_ComboBox_TerrainID->Append("-1 - None");
		Terrains_ComboBox_TerrainReplacementID->Append("-1 - None");
		Borders_ComboBox_BorderTerrain->Append("-1 - None");
	}

	for(short loop=0; loop < GenieFile->Terrains.size(); loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTerrainName(loop);
		CompareText = Name.Lower();
		if(SearchMatches(CompareText))
		{
			Terrains_Terrains_List->Append(Name, (void*)&GenieFile->Terrains[loop]);
		}
		if(Sized)
		{
			for(short loop=0; loop < 2; loop++)
			{
				Units_ComboBox_PlacementBypassTerrain[loop]->Append(Name);
				Units_ComboBox_PlacementTerrain[loop]->Append(Name);
			}
			Units_ComboBox_TerrainID->Append(Name);
			Terrains_ComboBox_TerrainReplacementID->Append(Name);
			Borders_ComboBox_BorderTerrain->Append(Name);
		}
	}

	ListingFix(Selections, Terrains_Terrains_List);
	if(Sized)
	{
		for(short loop=0; loop < 2; loop++)
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

	SearchText = TerRestrict_Terrains_Search->GetValue().Lower();
	ExcludeText = TerRestrict_Terrains_Search_R->GetValue().Lower();

	short Selections2 = TerRestrict_Terrains_List->GetSelections(Items);
	if(TerRestrict_Terrains_List->GetCount() > 0) TerRestrict_Terrains_List->Clear();

	for(short loop=0; loop < GenieFile->TerrainRestrictions[0].TerrainAccessible.size(); loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - A"+lexical_cast<string>((bool)GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible[loop]);
		if(GameVersion >= 2)
		Name += " B"+lexical_cast<string>((bool)GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainPassGraphics[loop].Buildable);
		Name += " - "+GetTerrainName(loop);
		CompareText = Name.Lower();
		if(SearchMatches(CompareText))
		{
			TerRestrict_Terrains_List->Append(Name, (void*)&GenieFile->Terrains[loop]);
		}
	}
	TerRestrict_Terrains_List->SetSelection(Items.Item(0));

	OnTerrainRestrictionsTerrainSelect(E);
}

void AGE_Frame::OnTerrainsSelect(wxCommandEvent& Event)
{
	auto Selections = Terrains_Terrains_List->GetSelections(Items);
	if(Selections != 0)
	{
		TerrainIDs.resize(Selections);
		genie::Terrain * TerrainPointer;
		for(short loop = Selections; loop--> 0;)
		{
			TerrainPointer = (genie::Terrain*)Terrains_Terrains_List->GetClientData(Items.Item(loop));
			TerrainIDs[loop] = (TerrainPointer - (&GenieFile->Terrains[0]));
		}
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
		for(short loop=0; loop < 3; loop++)
		{
			Terrains_Colors[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->Colors[loop]));
			Terrains_Colors[loop]->Container = &TerrainPointer->Colors[loop];
		}
		Terrains_Unknown5->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown5));
		Terrains_Unknown5->Container = &TerrainPointer->Unknown5;
		Terrains_Unknown6->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown6));
		Terrains_Unknown6->Container = &TerrainPointer->Unknown6;
		for(short loop=0; loop < 23; loop++)
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
		for(short loop=0; loop < 54; loop++)
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
		short Borders;
		if(GameVersion >= 3) Borders = TERRAINBORDERSMAX;
		else Borders = 32;
		for(short loop=0; loop < Borders; loop++)
		{
			Terrains_TerrainBorderID[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainBorderID[loop]));
			Terrains_TerrainBorderID[loop]->Container = &TerrainPointer->TerrainBorderID[loop];
			Terrains_ComboBox_TerrainBorderID[loop]->SetSelection(TerrainPointer->TerrainBorderID[loop] + 1);
		}
		for(short loop=0; loop < TERRAINUNITS; loop++)
		{
			Terrains_TerrainUnitID[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainUnitID[loop]));
			Terrains_TerrainUnitID[loop]->Container = &TerrainPointer->TerrainUnitID[loop];
			Terrains_ComboBox_TerrainUnitID[loop]->SetSelection(TerrainPointer->TerrainUnitID[loop] + 1);
			Terrains_TerrainUnitDensity[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainUnitDensity[loop]));
			Terrains_TerrainUnitDensity[loop]->Container = &TerrainPointer->TerrainUnitDensity[loop];
			Terrains_TerrainUnitPriority[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->TerrainUnitPriority[loop]));
			Terrains_TerrainUnitPriority[loop]->Container = &TerrainPointer->TerrainUnitPriority[loop];
		}
		Terrains_NumberOfTerrainUnitsUsed->ChangeValue(lexical_cast<string>(TerrainPointer->NumberOfTerrainUnitsUsed));
		Terrains_NumberOfTerrainUnitsUsed->Container = &TerrainPointer->NumberOfTerrainUnitsUsed;
		if(GameVersion >= 4)
		{
			for(short loop=0; loop < 24; loop++)
			{
				Terrains_SUnknown1[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->SWGBUnknown1[loop]));
				Terrains_SUnknown1[loop]->Container = &TerrainPointer->SWGBUnknown1[loop];
			}
		}
	}
}

void AGE_Frame::OnTerrainsAdd(wxCommandEvent& Event) // Their count is hardcoded.
{
	if(GenieFile != NULL)
	{
		wxBusyCursor WaitCursor;
		genie::Terrain Temp1;
		GenieFile->Terrains.push_back(Temp1);
		genie::TerrainPassGraphic Temp2;
		for(int loop = 0;loop < GenieFile->TerrainRestrictions.size(); loop++)
		{
			GenieFile->TerrainRestrictions[loop].TerrainAccessible.push_back(0);
			GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.push_back(Temp2);
		}
		Added = true;
		ListTerrains();
	}
}

void AGE_Frame::OnTerrainsInsert(wxCommandEvent& Event) // Their count is hardcoded.
{
	auto Selections = Terrains_Terrains_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::Terrain Temp1;
		GenieFile->Terrains.insert(GenieFile->Terrains.begin() + TerrainIDs[0], Temp1);
		genie::TerrainPassGraphic Temp2;
		for(int loop = 0;loop < GenieFile->TerrainRestrictions.size(); loop++)
		{
			GenieFile->TerrainRestrictions[loop].TerrainAccessible.insert(GenieFile->TerrainRestrictions[loop].TerrainAccessible.begin() + TerrainIDs[0], 0);
			GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.insert(GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.begin() + TerrainIDs[0], Temp2);
		}
		ListTerrains();
	}
}

void AGE_Frame::OnTerrainsDelete(wxCommandEvent& Event) // Their count is hardcoded.
{
	auto Selections = Terrains_Terrains_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop = Selections; loop--> 0;)
		{
			GenieFile->Terrains.erase(GenieFile->Terrains.begin() + TerrainIDs[loop]);
			for(int loop2 = 0;loop2 < GenieFile->TerrainRestrictions.size(); loop2++)
			{
				GenieFile->TerrainRestrictions[loop2].TerrainAccessible.erase(GenieFile->TerrainRestrictions[loop2].TerrainAccessible.begin() + TerrainIDs[loop]);
				GenieFile->TerrainRestrictions[loop2].TerrainPassGraphics.erase(GenieFile->TerrainRestrictions[loop2].TerrainPassGraphics.begin() + TerrainIDs[loop]);
			}
		}
		ListTerrains();
	}
}

void AGE_Frame::OnTerrainsCopy(wxCommandEvent& Event)
{
	auto Selections = Terrains_Terrains_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		TerrainCopies.resize(Selections);
		for(short loop=0; loop < Selections; loop++)
		TerrainCopies[loop] = GenieFile->Terrains[TerrainIDs[loop]];
	}
}

void AGE_Frame::OnTerrainsPaste(wxCommandEvent& Event)
{
	auto Selections = Terrains_Terrains_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		if(TerrainCopies.size()+TerrainIDs[0] > GenieFile->Terrains.size())
		{
			GenieFile->Terrains.resize(TerrainCopies.size()+TerrainIDs[0]);
			for(int loop2 = 0;loop2 < GenieFile->TerrainRestrictions.size(); loop2++)
			{
				GenieFile->TerrainRestrictions[loop2].TerrainAccessible.resize(TerrainCopies.size()+TerrainIDs[0]);
				GenieFile->TerrainRestrictions[loop2].TerrainPassGraphics.resize(TerrainCopies.size()+TerrainIDs[0]);
			}
		}
		for(short loop=0; loop < TerrainCopies.size(); loop++)
		GenieFile->Terrains[TerrainIDs[0]+loop] = TerrainCopies[loop];
		ListTerrains();
	}
}

void AGE_Frame::OnTerrainsPasteInsert(wxCommandEvent& Event)
{
	auto Selections = Terrains_Terrains_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::Terrain Temp1;
		genie::TerrainPassGraphic Temp2;
		GenieFile->Terrains.insert(GenieFile->Terrains.begin() + TerrainIDs[0], TerrainCopies.size(), Temp1);
		for(int loop2 = 0;loop2 < GenieFile->TerrainRestrictions.size(); loop2++)
		{
			GenieFile->TerrainRestrictions[loop2].TerrainAccessible.insert(GenieFile->TerrainRestrictions[loop2].TerrainAccessible.begin() + TerrainIDs[0], TerrainCopies.size(), 0);
			GenieFile->TerrainRestrictions[loop2].TerrainPassGraphics.insert(GenieFile->TerrainRestrictions[loop2].TerrainPassGraphics.begin() + TerrainIDs[0], TerrainCopies.size(), Temp2);
		}
		for(short loop=0; loop < TerrainCopies.size(); loop++)
		GenieFile->Terrains[TerrainIDs[0]+loop] = TerrainCopies[loop];
		ListTerrains();
	}
}

void AGE_Frame::CreateTerrainControls()
{

	Terrains_Main = new wxBoxSizer(wxHORIZONTAL);
	Terrains_ListArea = new wxBoxSizer(wxVERTICAL);
	Terrains_Terrains_Buttons = new wxGridSizer(3, 0, 0);
	Tab_Terrains = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	Terrains_Terrains = new wxStaticBoxSizer(wxVERTICAL, Tab_Terrains, "Terrains");
	Terrains_Terrains_Search = new wxTextCtrl(Tab_Terrains, wxID_ANY);
	Terrains_Terrains_Search_R = new wxTextCtrl(Tab_Terrains, wxID_ANY);
//	Terrains_Terrains_UseAnd = new wxCheckBox(Tab_Terrains, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Terrains_Terrains_List = new wxListBox(Tab_Terrains, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, wxLB_EXTENDED);
	Terrains_Add = new wxButton(Tab_Terrains, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Terrains_Insert = new wxButton(Tab_Terrains, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Terrains_Delete = new wxButton(Tab_Terrains, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Terrains_Copy = new wxButton(Tab_Terrains, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Terrains_Paste = new wxButton(Tab_Terrains, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Terrains_PasteInsert = new wxButton(Tab_Terrains, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	Terrains_DataArea = new wxBoxSizer(wxVERTICAL);
	Terrains_Scroller = new wxScrolledWindow(Tab_Terrains, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Terrains_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	Terrains_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	Terrains_Holder_NameArea = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Grid_Area1 = new wxGridSizer(4, 5, 5);
	Terrains_Holder_Name = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Name = new wxStaticText(Terrains_Scroller, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name = new TextCtrl_String(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Name2 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Name2 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Name 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name2 = new TextCtrl_String(Terrains_Scroller, "0", NULL);
	Terrains_Holder_SLP = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_SLP = new wxStaticText(Terrains_Scroller, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SLP = new TextCtrl_Long(Terrains_Scroller, "0", NULL);
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
	Terrains_Holder_Colors = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Colors = new wxGridSizer(3, 0, 0);
	Terrains_Text_Colors = new wxStaticText(Terrains_Scroller, wxID_ANY, " Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop=0; loop < 3; loop++)
	Terrains_Colors[loop] = new TextCtrl_UByte(Terrains_Scroller, "0", NULL);
	Terrains_Holder_FrameCount = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_FrameCount = new wxStaticText(Terrains_Scroller, wxID_ANY, " Frame Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_FrameCount = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_TerrainReplacementID = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainReplacementID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Replacement", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainReplacementID = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_ComboBox_TerrainReplacementID = new ComboBox_Short(Terrains_Scroller, Terrains_TerrainReplacementID);
	Terrains_Holder_TerrainDimensions = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainDimensions = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Dimensions", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainDimensions[0] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_TerrainDimensions[1] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_NumberOfTerrainUnitsUsed = new wxBoxSizer(wxVERTICAL);
	Terrains_Holder_NumberOfTerrainUnitsUsed1 = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Text_NumberOfTerrainUnitsUsed = new wxStaticText(Terrains_Scroller, wxID_ANY, " Number of Terrain Units Used", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_NumberOfTerrainUnitsUsed = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_TerrainUnits = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Holder_TerrainUnitID = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_TerrainUnitID = new wxGridSizer(2, 0, 0);
	Terrains_Holder_TerrainUnitDensity = new wxBoxSizer(wxVERTICAL);
	Terrains_Holder_TerrainUnitPriority = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainUnitID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Text_TerrainUnitDensity = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit Density", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Text_TerrainUnitPriority = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit Priority *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop=0; loop < TERRAINUNITS; loop++)
	{
		Terrains_TerrainUnitID[loop] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
		Terrains_ComboBox_TerrainUnitID[loop] = new ComboBox_Short(Terrains_Scroller, Terrains_TerrainUnitID[loop]);
		Terrains_TerrainUnitDensity[loop] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
		Terrains_TerrainUnitPriority[loop] = new TextCtrl_Byte(Terrains_Scroller, "0", NULL);
		Terrains_TerrainUnitPriority[loop]->SetToolTip("1 prevails, others don't");
	}
	Terrains_Holder_TerrainBorders = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_TerrainBorders = new wxGridSizer(6, 0, 0);
	Terrains_Text_TerrainBorderID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Borders", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop=0; loop < TERRAINBORDERSMAX; loop++)
	{
		Terrains_TerrainBorderID[loop] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
		Terrains_ComboBox_TerrainBorderID[loop] = new ComboBox_Short(Terrains_Scroller, Terrains_TerrainBorderID[loop]);
	}
	Terrains_Holder_UnknownArea = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknowns1 = new wxGridSizer(5, 5, 5);
	Terrains_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown1 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown1 = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown2 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown2 = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown3 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown3 = new TextCtrl_Long(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown5 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown5 = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown6 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown6 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown6 = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown8 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown8 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Angles + unknown", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown8[0] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Unknown8[1] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown9 = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknown9 = new wxGridSizer(6, 0, 0);
	Terrains_Text_Unknown9 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 9", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop=0; loop < 54; loop++)
	{
		Terrains_Unknown9[loop] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	}
	Terrains_Holder_Unknown7 = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknown7 = new wxGridSizer(12, 0, 0);
	Terrains_Text_Unknown7 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop=0; loop < 23; loop++)
	Terrains_Unknown7[loop] = new TextCtrl_Byte(Terrains_Scroller, "0", NULL);
	Terrains_Holder_SUnknown1 = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_SUnknown1 = new wxGridSizer(12, 0, 0);
	Terrains_Text_SUnknown1 = new wxStaticText(Terrains_Scroller, wxID_ANY, " SW Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop=0; loop < 24; loop++)
	Terrains_SUnknown1[loop] = new TextCtrl_Byte(Terrains_Scroller, "0", NULL);

	Terrains_Terrains_Buttons->Add(Terrains_Add, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Insert, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Delete, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Copy, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Paste, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_PasteInsert, 1, wxEXPAND);

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
	for(short loop=0; loop < 3; loop++)
	Terrains_Grid_Colors->Add(Terrains_Colors[loop], 1, wxEXPAND);
	Terrains_Holder_Colors->Add(Terrains_Text_Colors, 0, wxEXPAND);
	Terrains_Holder_Colors->Add(Terrains_Grid_Colors, 0, wxEXPAND);
	Terrains_Holder_Unknown5->Add(Terrains_Text_Unknown5, 0, wxEXPAND);
	Terrains_Holder_Unknown5->Add(Terrains_Unknown5, 1, wxEXPAND);
	Terrains_Holder_Unknown6->Add(Terrains_Text_Unknown6, 0, wxEXPAND);
	Terrains_Holder_Unknown6->Add(Terrains_Unknown6, 1, wxEXPAND);
	for(short loop=0; loop < 23; loop++)
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
	for(short loop=0; loop < 54; loop++)
	{
		Terrains_Grid_Unknown9->Add(Terrains_Unknown9[loop], 1, wxEXPAND);
	}
	Terrains_Holder_TerrainReplacementID->Add(Terrains_Text_TerrainReplacementID, 0, wxEXPAND);
	Terrains_Holder_TerrainReplacementID->Add(Terrains_TerrainReplacementID, 1, wxEXPAND);
	Terrains_Holder_TerrainReplacementID->Add(Terrains_ComboBox_TerrainReplacementID, 1, wxEXPAND);
	Terrains_Holder_TerrainDimensions->Add(Terrains_Text_TerrainDimensions, 0, wxEXPAND);
	Terrains_Holder_TerrainDimensions->Add(Terrains_TerrainDimensions[0], 1, wxEXPAND);
	Terrains_Holder_TerrainDimensions->Add(Terrains_TerrainDimensions[1], 1, wxEXPAND);
	for(short loop=0; loop < TERRAINBORDERSMAX; loop++)
	{
		Terrains_Grid_TerrainBorders->Add(Terrains_TerrainBorderID[loop], 1, wxEXPAND);
		Terrains_Grid_TerrainBorders->Add(Terrains_ComboBox_TerrainBorderID[loop], 1, wxEXPAND);
	}
	Terrains_Holder_TerrainBorders->Add(Terrains_Text_TerrainBorderID, 0, wxEXPAND);
	Terrains_Holder_TerrainBorders->Add(Terrains_Grid_TerrainBorders, 0, wxEXPAND);
	Terrains_Holder_TerrainUnitDensity->Add(Terrains_Text_TerrainUnitDensity, 0, wxEXPAND);
	Terrains_Holder_TerrainUnitPriority->Add(Terrains_Text_TerrainUnitPriority, 0, wxEXPAND);
	for(short loop=0; loop < TERRAINUNITS; loop++)
	{
		Terrains_Grid_TerrainUnitID->Add(Terrains_TerrainUnitID[loop], 1, wxEXPAND);
		Terrains_Grid_TerrainUnitID->Add(Terrains_ComboBox_TerrainUnitID[loop], 1, wxEXPAND);
		Terrains_Holder_TerrainUnitDensity->Add(Terrains_TerrainUnitDensity[loop], 1, wxEXPAND);
		Terrains_Holder_TerrainUnitPriority->Add(Terrains_TerrainUnitPriority[loop], 1, wxEXPAND);
	}
	Terrains_Holder_TerrainUnitID->Add(Terrains_Text_TerrainUnitID, 0, wxEXPAND);
	Terrains_Holder_TerrainUnitID->Add(Terrains_Grid_TerrainUnitID, 0, wxEXPAND);
	Terrains_Holder_NumberOfTerrainUnitsUsed->Add(Terrains_Text_NumberOfTerrainUnitsUsed, 0, wxEXPAND);
	Terrains_Holder_NumberOfTerrainUnitsUsed->Add(Terrains_NumberOfTerrainUnitsUsed, 1, wxEXPAND);
	for(short loop=0; loop < 24; loop++)
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
	Terrains_Grid_Area1->Add(Terrains_Holder_Colors, 1, wxEXPAND);
	Terrains_Grid_Area1->Add(Terrains_Holder_FrameCount, 1, wxEXPAND);
	Terrains_Grid_Area1->Add(Terrains_Holder_TerrainReplacementID, 1, wxEXPAND);
	Terrains_Grid_Area1->Add(Terrains_Holder_TerrainDimensions, 1, wxEXPAND);

	Terrains_Holder_TerrainUnits->Add(Terrains_Holder_TerrainUnitID, 2, wxEXPAND);
	Terrains_Holder_TerrainUnits->Add(5, -1);
	Terrains_Holder_TerrainUnits->Add(Terrains_Holder_TerrainUnitDensity, 1, wxEXPAND);
	Terrains_Holder_TerrainUnits->Add(5, -1);
	Terrains_Holder_TerrainUnits->Add(Terrains_Holder_TerrainUnitPriority, 1, wxEXPAND);

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
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_TerrainBorders, 0, wxEXPAND);
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
	Connect(Terrains_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsPasteInsert));

	Terrains_Name->Connect(Terrains_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Terrains_Name2->Connect(Terrains_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);

}
