#include "../AGE_Frame.h"

string AGE_Frame::GetTerrainName(short Index)
{
	if(GenieFile->TerrainBlock.Terrains.size() <= Index) return "Nonexistent Terrain";
	if(!GenieFile->TerrainBlock.Terrains[Index].Name.empty())
		return GenieFile->TerrainBlock.Terrains[Index].Name;
	return "New Terrain";
}

void AGE_Frame::OnTerrainsSearch(wxCommandEvent &Event)
{
	ListTerrains1(false);
}

void AGE_Frame::ListTerrainNumbers()
{
	Terrains_UsedCount->resize(2);
	Terrains_UsedCount->container[0] = &GenieFile->NumberOfTerrainsUsed;
	Terrains_UsedCount->container[1] = &GenieFile->TerrainBlock.NumberOfTerrainsUsed2;
	Terrains_UsedCount->Update();
}

void AGE_Frame::OnTerrainCountChange(wxFocusEvent &Event)
{
	if(((AGETextCtrl*)Event.GetEventObject())->SaveEdits() != 0) return;
	uint16_t UsedTerrains = lexical_cast<uint16_t>(((wxTextCtrl*)Event.GetEventObject())->GetValue());
	// Resize terrain restrictions
	for(short loop = 0; loop < GenieFile->TerrainRestrictions.size(); ++loop)
	{
		GenieFile->TerrainRestrictions[loop].TerrainAccessible.resize(UsedTerrains);
		if(GenieVersion >= genie::GV_AoKA)
		GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.resize(UsedTerrains);
	}

	wxCommandEvent E;
	OnTerrainRestrictionsSelect(E);
	Event.Skip();
}

void AGE_Frame::ListTerrains1(bool all)
{
	InitTerrains1(all);
	wxCommandEvent E;
	OnTerrainsSelect(E);
	if(all) OnTerrainRestrictionsTerrainSelect(E);
}

void AGE_Frame::ListTerrains2()
{
	InitTerrains2();
	wxCommandEvent E;
	OnTerrainRestrictionsTerrainSelect(E);
}

void AGE_Frame::InitTerrains1(bool all)
{
	searchText = Terrains_Terrains_Search->GetValue().Lower();
	excludeText = Terrains_Terrains_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString names, filteredNames;
	if(all) names.Alloc(GenieFile->TerrainBlock.Terrains.size());

	for(short loop = 0; loop < GenieFile->TerrainBlock.Terrains.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetTerrainName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TerrainBlock.Terrains[loop]);
		}
		if(all) names.Add(Name);
	}

	Listing(Terrains_Terrains_List, filteredNames, dataPointers);
	if(all) FillLists(TerrainComboBoxList, names);
	InitTerrains2();
}

void AGE_Frame::InitTerrains2()
{
	searchText = TerRestrict_Terrains_Search->GetValue().Lower();
	excludeText = TerRestrict_Terrains_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->NumberOfTerrainsUsed; ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - A"+lexical_cast<string>((bool)GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible[loop]);
		if(GenieVersion >= genie::GV_AoKA)
		Name += " B"+lexical_cast<string>((bool)GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainPassGraphics[loop].Buildable);
		Name += " - "+GetTerrainName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TerrainBlock.Terrains[loop]);
		}
	}
	Listing(TerRestrict_Terrains_List, filteredNames, dataPointers);
}

void AGE_Frame::OnTerrainsSelect(wxCommandEvent &Event)
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	TerrainIDs.resize(selections);
	if(GenieVersion < genie::GV_SWGB)
	Terrains_Unknown1->resize(selections);
	Terrains_Enabled->resize(selections);
	Terrains_Name->resize(selections);
	Terrains_Name2->resize(selections);
	Terrains_SLP->resize(selections);
	Terrains_Unknown3->resize(selections);
	Terrains_SoundID->resize(selections);
	if(GenieVersion >= genie::GV_AoK)
	{
		Terrains_BlendPriority->resize(selections);
		Terrains_BlendType->resize(selections);
	}
	for(short loop = 0; loop < 3; ++loop)
	{
		Terrains_Colors[loop]->resize(selections);
	}
	for(short loop = 0; loop < Terrains_Unknown5.size(); ++loop)
	Terrains_Unknown5[loop]->resize(selections);
	Terrains_Terrain1->resize(selections);
	Terrains_Terrain2->resize(selections);
	for(short loop = 0; loop < genie::Terrain::TERRAINS_USED_AOE; ++loop)
	{
		Terrains_Unknown7[loop]->resize(selections);
	}
	Terrains_FrameCount->resize(selections);
	Terrains_AngleCount->resize(selections);
	Terrains_TerrainID->resize(selections);
	for(short loop = 0; loop < genie::Terrain::ELEVATION_GRAPHICS_SIZE; ++loop)
	{
		Terrains_ElevationGraphics[loop]->resize(selections);
	}
	Terrains_TerrainReplacementID->resize(selections);
	Terrains_TerrainDimensions[0]->resize(selections);
	Terrains_TerrainDimensions[1]->resize(selections);
	for(short loop = 0; loop < GenieFile->TerrainBlock.Terrains.size(); ++loop)
	{
		Terrains_TerrainBorderID[loop]->resize(selections);
	}
	for(short loop = 0; loop < genie::Terrain::TERRAIN_UNITS_SIZE; ++loop)
	{
		Terrains_TerrainUnitID[loop]->resize(selections);
		Terrains_TerrainUnitDensity[loop]->resize(selections);
		Terrains_TerrainUnitPriority[loop]->resize(selections);
	}
	Terrains_NumberOfTerrainUnitsUsed->resize(selections);

	genie::Terrain * TerrainPointer;
	for(auto sel = selections; sel--> 0;)
	{
		TerrainPointer = (genie::Terrain*)Terrains_Terrains_List->GetClientData(Items.Item(sel));
		TerrainIDs[sel] = (TerrainPointer - (&GenieFile->TerrainBlock.Terrains[0]));

		if(GenieVersion < genie::GV_SWGB)
		Terrains_Unknown1->container[sel] = &TerrainPointer->Unknown1;
		Terrains_Enabled->container[sel] = &TerrainPointer->Enabled;
		Terrains_Name->container[sel] = &TerrainPointer->Name;
		Terrains_Name2->container[sel] = &TerrainPointer->Name2;
		Terrains_SLP->container[sel] = &TerrainPointer->SLP;
		Terrains_Unknown3->container[sel] = &TerrainPointer->Unknown3;
		Terrains_SoundID->container[sel] = &TerrainPointer->SoundID;
		if(GenieVersion >= genie::GV_AoK)
		{
			Terrains_BlendPriority->container[sel] = &TerrainPointer->BlendPriority;
			Terrains_BlendType->container[sel] = &TerrainPointer->BlendType;
		}
		for(short loop = 0; loop < 3; ++loop)
		{
			Terrains_Colors[loop]->container[sel] = &TerrainPointer->Colors[loop];
		}
		for(short loop = 0; loop < Terrains_Unknown5.size(); ++loop)
		Terrains_Unknown5[loop]->container[sel] = &TerrainPointer->Unknown5[loop];
		Terrains_Terrain1->container[sel] = &TerrainPointer->Terrain1;
		Terrains_Terrain2->container[sel] = &TerrainPointer->Terrain2;
		for(short loop = 0; loop < TerrainPointer->TERRAINS_USED_AOE; ++loop)
		{
			Terrains_Unknown7[loop]->container[sel] = &TerrainPointer->Unknown7[loop];
		}
		Terrains_FrameCount->container[sel] = &TerrainPointer->FrameCount;
		Terrains_AngleCount->container[sel] = &TerrainPointer->AngleCount;
		Terrains_TerrainID->container[sel] = &TerrainPointer->TerrainID;
		for(short loop = 0; loop < TerrainPointer->ELEVATION_GRAPHICS_SIZE; ++loop)
		{
			Terrains_ElevationGraphics[loop]->container[sel] = &TerrainPointer->ElevationGraphics[loop];
		}
		Terrains_TerrainReplacementID->container[sel] = &TerrainPointer->TerrainReplacementID;
		Terrains_TerrainDimensions[0]->container[sel] = &TerrainPointer->TerrainDimensions.first;
		Terrains_TerrainDimensions[1]->container[sel] = &TerrainPointer->TerrainDimensions.second;
		for(short loop = 0; loop < GenieFile->TerrainBlock.Terrains.size(); ++loop)
		{
			Terrains_TerrainBorderID[loop]->container[sel] = &TerrainPointer->TerrainBorderIDs[loop];
		}
		for(short loop = 0; loop < TerrainPointer->TERRAIN_UNITS_SIZE; ++loop)
		{
			Terrains_TerrainUnitID[loop]->container[sel] = &TerrainPointer->TerrainUnitID[loop];
			Terrains_TerrainUnitDensity[loop]->container[sel] = &TerrainPointer->TerrainUnitDensity[loop];
			Terrains_TerrainUnitPriority[loop]->container[sel] = &TerrainPointer->TerrainUnitPriority[loop];
		}
		Terrains_NumberOfTerrainUnitsUsed->container[sel] = &TerrainPointer->NumberOfTerrainUnitsUsed;
	}

	if(GenieVersion < genie::GV_SWGB)
	Terrains_Unknown1->Update();
	Terrains_Enabled->Update();
	Terrains_Name->Update();
	Terrains_Name2->Update();
	Terrains_SLP->Update();
	Terrains_Unknown3->Update();
	Terrains_SoundID->Update();
	if(GenieVersion >= genie::GV_AoK)
	{
		Terrains_BlendPriority->Update();
		Terrains_BlendType->Update();
	}
	for(short loop = 0; loop < 3; ++loop)
	{
		Terrains_Colors[loop]->Update();
	}
	for(short loop = 0; loop < Terrains_Unknown5.size(); ++loop)
	Terrains_Unknown5[loop]->Update();
	Terrains_Terrain1->Update();
	Terrains_Terrain2->Update();
	for(short loop = 0; loop < TerrainPointer->TERRAINS_USED_AOE; ++loop)
	{
		Terrains_Unknown7[loop]->Update();
	}
	Terrains_FrameCount->Update();
	Terrains_AngleCount->Update();
	Terrains_TerrainID->Update();
	for(short loop = 0; loop < TerrainPointer->ELEVATION_GRAPHICS_SIZE; ++loop)
	{
		Terrains_ElevationGraphics[loop]->Update();
	}
	Terrains_TerrainReplacementID->Update();
	Terrains_TerrainDimensions[0]->Update();
	Terrains_TerrainDimensions[1]->Update();
	for(short loop = 0; loop < GenieFile->TerrainBlock.Terrains.size(); ++loop)
	{
		Terrains_TerrainBorderID[loop]->Update();
	}
	for(short loop = 0; loop < TerrainPointer->TERRAIN_UNITS_SIZE; ++loop)
	{
		Terrains_TerrainUnitID[loop]->Update();
		Terrains_TerrainUnitDensity[loop]->Update();
		Terrains_TerrainUnitPriority[loop]->Update();
	}
	Terrains_NumberOfTerrainUnitsUsed->Update();
}

void AGE_Frame::OnTerrainsAdd(wxCommandEvent &Event) // Their count is hardcoded.
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->TerrainBlock.Terrains);
	ListTerrains1();
}

void AGE_Frame::OnTerrainsInsert(wxCommandEvent &Event) // Their count is hardcoded.
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->TerrainBlock.Terrains, TerrainIDs[0]);
	ListTerrains1();
}

void AGE_Frame::OnTerrainsDelete(wxCommandEvent &Event) // Their count is hardcoded.
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TerrainBlock.Terrains, TerrainIDs);
	ListTerrains1();
}

void AGE_Frame::OnTerrainsCopy(wxCommandEvent &Event)
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TerrainBlock.Terrains, TerrainIDs, copies->Terrain);
}

void AGE_Frame::OnTerrainsPaste(wxCommandEvent &Event)
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoResize(GenieFile->TerrainBlock.Terrains, TerrainIDs[0], copies->Terrain);
	ListTerrains1();
}

void AGE_Frame::OnTerrainsPasteInsert(wxCommandEvent &Event)
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->TerrainBlock.Terrains, TerrainIDs[0], copies->Terrain);
	ListTerrains1();
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
	Terrains_Terrains_List = new wxListBox(Tab_Terrains, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	Terrains_UsedCountHolder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_UsedCountText = new wxStaticText(Tab_Terrains, wxID_ANY, " Terrains Used *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_UsedCount = new TextCtrl_UShort(Tab_Terrains);
	Terrains_UsedCount->SetToolTip("How many terrains are used\nstarting from the first terrain without gaps");
	Terrains_Add = new wxButton(Tab_Terrains, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Terrains_Insert = new wxButton(Tab_Terrains, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Terrains_Delete = new wxButton(Tab_Terrains, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Terrains_Copy = new wxButton(Tab_Terrains, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Terrains_Paste = new wxButton(Tab_Terrains, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Terrains_PasteInsert = new wxButton(Tab_Terrains, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	Terrains_DataArea = new wxBoxSizer(wxVERTICAL);
	Terrains_Scroller = new wxScrolledWindow(Tab_Terrains, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Terrains_ScrollArea = new wxBoxSizer(wxHORIZONTAL);
	Terrains_ScrollSpace = new wxBoxSizer(wxVERTICAL);
	Terrains_NameArea_Holder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Area1_Grid = new wxGridSizer(4, 5, 5);
	Terrains_Enabled_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Enabled1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Enabled_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Enabled", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Enabled = new TextCtrl_Short(Terrains_Scroller);
	Terrains_Enabled_CheckBox = new CheckBox_2State(Terrains_Scroller, " Yes", Terrains_Enabled);
	Terrains_Name_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Name_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name = new TextCtrl_String(Terrains_Scroller);
	Terrains_Name2_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Name2_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " SLP Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name2 = new TextCtrl_String(Terrains_Scroller);
	Terrains_SLP_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_SLP_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SLP = new TextCtrl_Long(Terrains_Scroller);
	Terrains_SoundID_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_SoundID_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SoundID = new TextCtrl_Long(Terrains_Scroller);
	Terrains_SoundID_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_SoundID);
	SoundComboBoxList.push_back(Terrains_SoundID_ComboBox);
	Terrains_BlendPriority_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_BlendPriority_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Blend Priority", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_BlendPriority = new TextCtrl_Long(Terrains_Scroller);
	Terrains_BlendType_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_BlendType_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Blend Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_BlendType = new TextCtrl_Long(Terrains_Scroller);
	Terrains_Colors_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Colors_Grid = new wxGridSizer(3, 0, 0);
	Terrains_Colors_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 3; ++loop)
	Terrains_Colors[loop] = new TextCtrl_UByte(Terrains_Scroller);
	Terrains_FrameCount_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_FrameCount_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Frame Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_FrameCount = new TextCtrl_Short(Terrains_Scroller);
	Terrains_AngleCount_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_AngleCount_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Angle Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_AngleCount = new TextCtrl_Short(Terrains_Scroller);
	Terrains_TerrainDimensions_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainDimensions_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Dimensions", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainDimensions[0] = new TextCtrl_Short(Terrains_Scroller);
	Terrains_TerrainDimensions[1] = new TextCtrl_Short(Terrains_Scroller);
	Terrains_Terrain1_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Terrain1_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Terrain1 = new TextCtrl_Byte(Terrains_Scroller);
	Terrains_Terrain1_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_Terrain1);
	TerrainComboBoxList.push_back(Terrains_Terrain1_ComboBox);
	Terrains_Terrain2_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Terrain2_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Terrain2 = new TextCtrl_Byte(Terrains_Scroller);
	Terrains_Terrain2_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_Terrain2);
	TerrainComboBoxList.push_back(Terrains_Terrain2_ComboBox);
	Terrains_TerrainID_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainID_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainID = new TextCtrl_Short(Terrains_Scroller);
	Terrains_TerrainID_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainID);
	TerrainComboBoxList.push_back(Terrains_TerrainID_ComboBox);
	Terrains_TerrainReplacementID_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainReplacementID_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Replacement", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainReplacementID = new TextCtrl_Short(Terrains_Scroller);
	Terrains_TerrainReplacementID_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainReplacementID);
	TerrainComboBoxList.push_back(Terrains_TerrainReplacementID_ComboBox);
	Terrains_NumberOfTerrainUnitsUsed_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_NumberOfTerrainUnitsUsed1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_NumberOfTerrainUnitsUsed_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Number of Terrain Units Used", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_NumberOfTerrainUnitsUsed = new TextCtrl_Short(Terrains_Scroller);
	Terrains_TerrainUnits_Holder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_TerrainUnitID_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainUnitID_Grid = new wxGridSizer(2, 0, 0);
	Terrains_TerrainUnitDensity_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainUnitPriority_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainUnitID_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainUnitDensity_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit Density", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainUnitPriority_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit Priority *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < TERRAINUNITS; ++loop)
	{
		Terrains_TerrainUnitID[loop] = new TextCtrl_Short(Terrains_Scroller);
		Terrains_TerrainUnitID_ComboBox[loop] = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainUnitID[loop]);
		UnitComboBoxList.push_back(Terrains_TerrainUnitID_ComboBox[loop]);
		Terrains_TerrainUnitDensity[loop] = new TextCtrl_Short(Terrains_Scroller);
		Terrains_TerrainUnitPriority[loop] = new TextCtrl_Byte(Terrains_Scroller);
		Terrains_TerrainUnitPriority[loop]->SetToolTip("1 prevails, others don't");
	}
	Terrains_TerrainBorders_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainBorders_Grid = new wxGridSizer(6, 0, 0);
	Terrains_TerrainBorderID_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Borders", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < TERRAINBORDERSMAX; ++loop)
	{
		Terrains_TerrainBorderID[loop] = new TextCtrl_Short(Terrains_Scroller);
		Terrains_TerrainBorderID_ComboBox[loop] = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainBorderID[loop]);
		TerrainBorderComboBoxList.push_back(Terrains_TerrainBorderID_ComboBox[loop]);
	}
	Terrains_ElevationGraphics_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Unknown9_Grid = new wxGridSizer(6, 0, 0);
	Terrains_ElevationGraphics_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Elevation Graphics", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < Terrains_ElevationGraphics.size(); ++loop)
	{
		Terrains_ElevationGraphics[loop] = new TextCtrl_Short(Terrains_Scroller);
	}
	Terrains_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Unknown3_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown3 = new TextCtrl_Float(Terrains_Scroller);
	Terrains_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Unknown5_Grid = new wxGridSizer(2, 0, 0);
	Terrains_Unknown5_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Colors?", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < Terrains_Unknown5.size(); ++loop)
	Terrains_Unknown5[loop] = new TextCtrl_UByte(Terrains_Scroller);
	Terrains_Unknowns1_Grid = new wxGridSizer(4, 5, 5);
	Terrains_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Unknown1_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown1 = new TextCtrl_Short(Terrains_Scroller);
	Terrains_Unknown7_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Unknown7_Grid = new wxGridSizer(12, 0, 0);
	Terrains_Unknown7_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Useless garbage for used terrains (23 in AoE)", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < Terrains_Unknown7.size(); ++loop)
	Terrains_Unknown7[loop] = new TextCtrl_Byte(Terrains_Scroller);

	Terrains_UsedCountHolder->Add(Terrains_UsedCountText, 0, wxEXPAND);
	Terrains_UsedCountHolder->Add(2, -1);
	Terrains_UsedCountHolder->Add(Terrains_UsedCount, 1, wxEXPAND);

	Terrains_Terrains_Buttons->Add(Terrains_Add, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Delete, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Insert, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Copy, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Paste, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_PasteInsert, 1, wxEXPAND);

	Terrains_Terrains->Add(Terrains_Terrains_Search, 0, wxEXPAND);
	Terrains_Terrains->Add(Terrains_Terrains_Search_R, 0, wxEXPAND);
//	Terrains_Terrains->Add(Terrains_Terrains_UseAnd, 0, wxEXPAND);
	Terrains_Terrains->Add(-1, 2);
	Terrains_Terrains->Add(Terrains_Terrains_List, 1, wxEXPAND);
	Terrains_Terrains->Add(-1, 2);
	Terrains_Terrains->Add(Terrains_UsedCountHolder, 0, wxEXPAND);
	Terrains_Terrains->Add(-1, 2);
	Terrains_Terrains->Add(Terrains_Terrains_Buttons, 0, wxEXPAND);

	Terrains_ListArea->Add(-1, 10);
	Terrains_ListArea->Add(Terrains_Terrains, 1, wxEXPAND);
	Terrains_ListArea->Add(-1, 10);

	Terrains_Unknown1_Holder->Add(Terrains_Unknown1_Text, 0, wxEXPAND);
	Terrains_Unknown1_Holder->Add(Terrains_Unknown1, 1, wxEXPAND);
	Terrains_Enabled1_Holder->Add(Terrains_Enabled, 1, wxEXPAND);
	Terrains_Enabled1_Holder->Add(2, -1);
	Terrains_Enabled1_Holder->Add(Terrains_Enabled_CheckBox, 1, wxEXPAND);
	Terrains_Enabled_Holder->Add(Terrains_Enabled_Text, 0, wxEXPAND);
	Terrains_Enabled_Holder->Add(Terrains_Enabled1_Holder, 1, wxEXPAND);
	Terrains_Name_Holder->Add(Terrains_Name_Text, 0, wxEXPAND);
	Terrains_Name_Holder->Add(Terrains_Name, 1, wxEXPAND);
	Terrains_Name2_Holder->Add(Terrains_Name2_Text, 0, wxEXPAND);
	Terrains_Name2_Holder->Add(Terrains_Name2, 1, wxEXPAND);
	Terrains_SLP_Holder->Add(Terrains_SLP_Text, 0, wxEXPAND);
	Terrains_SLP_Holder->Add(Terrains_SLP, 0, wxEXPAND);
	Terrains_Unknown3_Holder->Add(Terrains_Unknown3_Text, 0, wxEXPAND);
	Terrains_Unknown3_Holder->Add(Terrains_Unknown3, 1, wxEXPAND);
	Terrains_SoundID_Holder->Add(Terrains_SoundID_Text, 0, wxEXPAND);
	Terrains_SoundID_Holder->Add(Terrains_SoundID, 1, wxEXPAND);
	Terrains_SoundID_Holder->Add(Terrains_SoundID_ComboBox, 1, wxEXPAND);
	Terrains_BlendPriority_Holder->Add(Terrains_BlendPriority_Text, 0, wxEXPAND);
	Terrains_BlendPriority_Holder->Add(Terrains_BlendPriority, 0, wxEXPAND);
	Terrains_BlendType_Holder->Add(Terrains_BlendType_Text, 0, wxEXPAND);
	Terrains_BlendType_Holder->Add(Terrains_BlendType, 0, wxEXPAND);
	for(short loop = 0; loop < 3; ++loop)
	Terrains_Colors_Grid->Add(Terrains_Colors[loop], 1, wxEXPAND);
	Terrains_Colors_Holder->Add(Terrains_Colors_Text, 0, wxEXPAND);
	Terrains_Colors_Holder->Add(Terrains_Colors_Grid, 0, wxEXPAND);
	Terrains_Unknown5_Holder->Add(Terrains_Unknown5_Text, 0, wxEXPAND);
	for(short loop = 0; loop < Terrains_Unknown5.size(); ++loop)
	Terrains_Unknown5_Grid->Add(Terrains_Unknown5[loop], 1, wxEXPAND);
	Terrains_Unknown5_Holder->Add(Terrains_Unknown5_Grid, 1, wxEXPAND);
	Terrains_Terrain1_Holder->Add(Terrains_Terrain1_Text, 0, wxEXPAND);
	Terrains_Terrain1_Holder->Add(Terrains_Terrain1, 0, wxEXPAND);
	Terrains_Terrain1_Holder->Add(Terrains_Terrain1_ComboBox, 0, wxEXPAND);
	Terrains_Terrain2_Holder->Add(Terrains_Terrain2_Text, 0, wxEXPAND);
	Terrains_Terrain2_Holder->Add(Terrains_Terrain2, 0, wxEXPAND);
	Terrains_Terrain2_Holder->Add(Terrains_Terrain2_ComboBox, 0, wxEXPAND);
	for(short loop = 0; loop < Terrains_Unknown7.size(); ++loop)
	Terrains_Unknown7_Grid->Add(Terrains_Unknown7[loop], 1, wxEXPAND);
	Terrains_Unknown7_Holder->Add(Terrains_Unknown7_Text, 0, wxEXPAND);
	Terrains_Unknown7_Holder->Add(Terrains_Unknown7_Grid, 0, wxEXPAND);
	Terrains_FrameCount_Holder->Add(Terrains_FrameCount_Text, 0, wxEXPAND);
	Terrains_FrameCount_Holder->Add(Terrains_FrameCount, 0, wxEXPAND);
	Terrains_AngleCount_Holder->Add(Terrains_AngleCount_Text, 0, wxEXPAND);
	Terrains_AngleCount_Holder->Add(Terrains_AngleCount, 0, wxEXPAND);
	Terrains_TerrainID_Holder->Add(Terrains_TerrainID_Text, 0, wxEXPAND);
	Terrains_TerrainID_Holder->Add(Terrains_TerrainID, 0, wxEXPAND);
	Terrains_TerrainID_Holder->Add(Terrains_TerrainID_ComboBox, 0, wxEXPAND);
	Terrains_ElevationGraphics_Holder->Add(Terrains_ElevationGraphics_Text, 0, wxEXPAND);
	Terrains_ElevationGraphics_Holder->Add(Terrains_Unknown9_Grid, 0, wxEXPAND);
	for(short loop = 0; loop < Terrains_ElevationGraphics.size(); ++loop)
	{
		Terrains_Unknown9_Grid->Add(Terrains_ElevationGraphics[loop], 1, wxEXPAND);
	}
	Terrains_TerrainReplacementID_Holder->Add(Terrains_TerrainReplacementID_Text, 0, wxEXPAND);
	Terrains_TerrainReplacementID_Holder->Add(Terrains_TerrainReplacementID, 1, wxEXPAND);
	Terrains_TerrainReplacementID_Holder->Add(Terrains_TerrainReplacementID_ComboBox, 1, wxEXPAND);
	Terrains_TerrainDimensions_Holder->Add(Terrains_TerrainDimensions_Text, 0, wxEXPAND);
	Terrains_TerrainDimensions_Holder->Add(Terrains_TerrainDimensions[0], 1, wxEXPAND);
	Terrains_TerrainDimensions_Holder->Add(Terrains_TerrainDimensions[1], 1, wxEXPAND);
	for(short loop = 0; loop < TERRAINBORDERSMAX; ++loop)
	{
		Terrains_TerrainBorders_Grid->Add(Terrains_TerrainBorderID[loop], 1, wxEXPAND);
		Terrains_TerrainBorders_Grid->Add(Terrains_TerrainBorderID_ComboBox[loop], 1, wxEXPAND);
	}
	Terrains_TerrainBorders_Holder->Add(Terrains_TerrainBorderID_Text, 0, wxEXPAND);
	Terrains_TerrainBorders_Holder->Add(Terrains_TerrainBorders_Grid, 0, wxEXPAND);
	Terrains_TerrainUnitDensity_Holder->Add(Terrains_TerrainUnitDensity_Text, 0, wxEXPAND);
	Terrains_TerrainUnitPriority_Holder->Add(Terrains_TerrainUnitPriority_Text, 0, wxEXPAND);
	for(short loop = 0; loop < TERRAINUNITS; ++loop)
	{
		Terrains_TerrainUnitID_Grid->Add(Terrains_TerrainUnitID[loop], 1, wxEXPAND);
		Terrains_TerrainUnitID_Grid->Add(Terrains_TerrainUnitID_ComboBox[loop], 1, wxEXPAND);
		Terrains_TerrainUnitDensity_Holder->Add(Terrains_TerrainUnitDensity[loop], 1, wxEXPAND);
		Terrains_TerrainUnitPriority_Holder->Add(Terrains_TerrainUnitPriority[loop], 1, wxEXPAND);
	}
	Terrains_TerrainUnitID_Holder->Add(Terrains_TerrainUnitID_Text, 0, wxEXPAND);
	Terrains_TerrainUnitID_Holder->Add(Terrains_TerrainUnitID_Grid, 0, wxEXPAND);
	Terrains_NumberOfTerrainUnitsUsed_Holder->Add(Terrains_NumberOfTerrainUnitsUsed_Text, 0, wxEXPAND);
	Terrains_NumberOfTerrainUnitsUsed_Holder->Add(Terrains_NumberOfTerrainUnitsUsed, 1, wxEXPAND);

	Terrains_NameArea_Holder->Add(Terrains_Enabled_Holder, 1, wxEXPAND);
	Terrains_NameArea_Holder->Add(5, -1);
	Terrains_NameArea_Holder->Add(Terrains_Name_Holder, 2, wxEXPAND);
	Terrains_NameArea_Holder->Add(5, -1);
	Terrains_NameArea_Holder->Add(Terrains_Name2_Holder, 2, wxEXPAND);
	Terrains_NameArea_Holder->AddStretchSpacer(1);

	Terrains_Area1_Grid->Add(Terrains_SLP_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_SoundID_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_BlendPriority_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_Area1_Grid->Add(Terrains_BlendType_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_Area1_Grid->Add(Terrains_Colors_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_FrameCount_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_AngleCount_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_TerrainDimensions_Holder, 1, wxEXPAND);

	Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitID_Holder, 2, wxEXPAND);
	Terrains_TerrainUnits_Holder->Add(5, -1);
	Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitDensity_Holder, 1, wxEXPAND);
	Terrains_TerrainUnits_Holder->Add(5, -1);
	Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitPriority_Holder, 1, wxEXPAND);

	Terrains_Unknowns1_Grid->Add(Terrains_Unknown3_Holder, 1, wxEXPAND);
	Terrains_Unknowns1_Grid->Add(Terrains_Unknown5_Holder, 1, wxEXPAND);
	Terrains_Unknowns1_Grid->Add(Terrains_Unknown1_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_Terrain1_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_Terrain2_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_TerrainID_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_TerrainReplacementID_Holder, 1, wxEXPAND);

	Terrains_NumberOfTerrainUnitsUsed1_Holder->Add(Terrains_NumberOfTerrainUnitsUsed_Holder, 1, wxEXPAND);
	Terrains_NumberOfTerrainUnitsUsed1_Holder->AddStretchSpacer(3);

	Terrains_ScrollSpace->Add(Terrains_NameArea_Holder, 0, wxEXPAND);
	Terrains_ScrollSpace->Add(-1, 5);
	Terrains_ScrollSpace->Add(Terrains_Area1_Grid, 0, wxEXPAND);
	Terrains_ScrollSpace->Add(-1, 5);
	Terrains_ScrollSpace->Add(Terrains_NumberOfTerrainUnitsUsed1_Holder, 0, wxEXPAND);
	Terrains_ScrollSpace->Add(-1, 5);
	Terrains_ScrollSpace->Add(Terrains_TerrainUnits_Holder, 0, wxEXPAND);
	Terrains_ScrollSpace->Add(-1, 5);
	Terrains_ScrollSpace->Add(Terrains_TerrainBorders_Holder, 0, wxEXPAND);
	Terrains_ScrollSpace->Add(-1, 5);
	Terrains_ScrollSpace->Add(Terrains_ElevationGraphics_Holder, 0, wxEXPAND);
	Terrains_ScrollSpace->Add(-1, 5);
	Terrains_ScrollSpace->Add(Terrains_Unknowns1_Grid, 0, wxEXPAND);
	Terrains_ScrollSpace->Add(-1, 5);
	Terrains_ScrollSpace->Add(Terrains_Unknown7_Holder, 0, wxEXPAND);

	Terrains_ScrollArea->Add(Terrains_ScrollSpace, 1, wxEXPAND);
	Terrains_ScrollArea->Add(5, -1);

	Terrains_Scroller->SetSizer(Terrains_ScrollArea);
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

	Terrains_Name->Connect(Terrains_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Terrains), NULL, this);
	Terrains_Name2->Connect(Terrains_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Terrains), NULL, this);
	Terrains_UsedCount->Connect(Terrains_UsedCount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnTerrainCountChange), NULL, this);
}

void AGE_Frame::OnKillFocus_Terrains(wxFocusEvent &Event)
{
	if(((AGETextCtrl*)Event.GetEventObject())->SaveEdits() != 0) return;
	if(Event.GetId() == Terrains_Name->GetId())
	{
		ListTerrains1();
	}
	else if(Event.GetId() == Terrains_Name2->GetId())
	{
		wxCommandEvent E;
		OnTerrainsSelect(E);
	}
	Event.Skip();
}
