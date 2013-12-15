#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetTerrainName(short Index)
{
	if(GenieFile->Terrains.size() <= Index) return "Nonexistent Terrain";
	if(!GenieFile->Terrains[Index].Name.empty())
		return GenieFile->Terrains[Index].Name;
	return "New Terrain";
}

void AGE_Frame::OnTerrainsSearch(wxCommandEvent &Event)
{
	ListTerrains(false);
}

void AGE_Frame::ListTerrainNumbers()
{
	Terrains_UsedCount->ChangeValue(lexical_cast<string>(GenieFile->NumberOfTerrainsUsed));
	Terrains_UsedCount->resize(2);
	Terrains_UsedCount->container[0] = &GenieFile->NumberOfTerrainsUsed;
	Terrains_UsedCount->container[1] = &GenieFile->NumberOfTerrainsUsed2;
}

void AGE_Frame::OnTerrainCountChange(wxFocusEvent &Event)
{
	if(!((AGETextCtrl*)Event.GetEventObject())->SaveEdits()) return;
	uint16_t UsedTerrains = lexical_cast<uint16_t>(((wxTextCtrl*)Event.GetEventObject())->GetValue());
	// Resize terrain restrictions
	for(short loop = 0; loop < GenieFile->TerrainRestrictions.size(); ++loop)
	{
		GenieFile->TerrainRestrictions[loop].TerrainAccessible.resize(UsedTerrains);
		if(GenieVersion >= genie::GV_AoK)
		GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.resize(UsedTerrains);
	}

	wxCommandEvent E;
	OnTerrainRestrictionsSelect(E);
	Event.Skip();
}

void AGE_Frame::ListTerrains(bool all)
{
	searchText = Terrains_Terrains_Search->GetValue().Lower();
	excludeText = Terrains_Terrains_Search_R->GetValue().Lower();

	auto selections = Terrains_Terrains_List->GetSelections(Items);
	Terrains_Terrains_List->Clear();

	list<short> savedSelections;
	wxArrayString names;
	if(all)
	{
		PrepareLists(TerrainComboBoxList, savedSelections);
		names.Alloc(GenieFile->Terrains.size());
	}

	for(short loop = 0; loop < GenieFile->Terrains.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetTerrainName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Terrains_Terrains_List->Append(Name, (void*)&GenieFile->Terrains[loop]);
		}
		if(all) names.Add(Name);
	}

	ListingFix(selections, Terrains_Terrains_List);
	if(all) FillLists(TerrainComboBoxList, savedSelections, names);

	wxCommandEvent E;
	OnTerrainsSelect(E);

	searchText = TerRestrict_Terrains_Search->GetValue().Lower();
	excludeText = TerRestrict_Terrains_Search_R->GetValue().Lower();

	short Selections2 = TerRestrict_Terrains_List->GetSelections(Items);
	TerRestrict_Terrains_List->Clear();

	for(short loop = 0; loop < GenieFile->NumberOfTerrainsUsed; ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - A"+lexical_cast<string>((bool)GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible[loop]);
		if(GenieVersion >= genie::GV_AoK)
		Name += " B"+lexical_cast<string>((bool)GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainPassGraphics[loop].Buildable);
		Name += " - "+GetTerrainName(loop);
		if(SearchMatches(Name.Lower()))
		{
			TerRestrict_Terrains_List->Append(Name, (void*)&GenieFile->Terrains[loop]);
		}
	}
	TerRestrict_Terrains_List->SetSelection(Items.Item(0));

	OnTerrainRestrictionsTerrainSelect(E);
}

void AGE_Frame::OnTerrainsSelect(wxCommandEvent &Event)
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	TerrainIDs.resize(selections);
	Terrains_Unknown1->resize(selections);
	Terrains_Unknown2->resize(selections);
	Terrains_Name->resize(selections);
	Terrains_Name2->resize(selections);
	Terrains_SLP->resize(selections);
	Terrains_Unknown3->resize(selections);
	Terrains_SoundID->resize(selections);
	if(GenieVersion >= genie::GV_AoK)
	{
		Terrains_BlendPriority->resize(selections);
		Terrains_BlendType->resize(selections);
		if(GenieVersion >= genie::GV_SWGB)
		for(short loop = 0; loop < genie::Terrain::SWGBUNKNOWN1_SIZE; ++loop)
		{
			Terrains_SUnknown1[loop]->resize(selections);
		}
	}
	for(short loop = 0; loop < 3; ++loop)
	{
		Terrains_Colors[loop]->resize(selections);
	}
	for(short loop = 0; loop < Terrains_Unknown5.size(); ++loop)
	Terrains_Unknown5[loop]->resize(selections);
	Terrains_Unknown6->resize(selections);
	for(short loop = 0; loop < genie::Terrain::UNKNOWN7_SIZE; ++loop)
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
	for(short loop = 0; loop < GenieFile->Terrains[0].getTerrainBorderSize(); ++loop)
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
		TerrainIDs[sel] = (TerrainPointer - (&GenieFile->Terrains[0]));

		Terrains_Unknown1->container[sel] = &TerrainPointer->Unknown1;
		Terrains_Unknown2->container[sel] = &TerrainPointer->Enabled;
		Terrains_Name->container[sel] = &TerrainPointer->Name;
		Terrains_Name2->container[sel] = &TerrainPointer->Name2;
		Terrains_SLP->container[sel] = &TerrainPointer->SLP;
		Terrains_Unknown3->container[sel] = &TerrainPointer->Unknown3;
		Terrains_SoundID->container[sel] = &TerrainPointer->SoundID;
		if(GenieVersion >= genie::GV_AoK)
		{
			Terrains_BlendPriority->container[sel] = &TerrainPointer->BlendPriority;
			Terrains_BlendType->container[sel] = &TerrainPointer->BlendType;
			if(GenieVersion >= genie::GV_SWGB)
			for(short loop = 0; loop < TerrainPointer->SWGBUNKNOWN1_SIZE; ++loop)
			{
				Terrains_SUnknown1[loop]->container[sel] = &TerrainPointer->SWGBUnknown1[loop];
			}
		}
		for(short loop = 0; loop < 3; ++loop)
		{
			Terrains_Colors[loop]->container[sel] = &TerrainPointer->Colors[loop];
		}
		for(short loop = 0; loop < Terrains_Unknown5.size(); ++loop)
		Terrains_Unknown5[loop]->container[sel] = &TerrainPointer->Unknown5[loop];
		Terrains_Unknown6->container[sel] = &TerrainPointer->Unknown6;
		for(short loop = 0; loop < TerrainPointer->UNKNOWN7_SIZE; ++loop)
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
		for(short loop = 0; loop < TerrainPointer->getTerrainBorderSize(); ++loop)
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

	Terrains_Unknown1->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown1));
	Terrains_Unknown2->ChangeValue(lexical_cast<string>(TerrainPointer->Enabled));
	Terrains_Name->ChangeValue(TerrainPointer->Name);
	Terrains_Name2->ChangeValue(TerrainPointer->Name2);
	Terrains_SLP->ChangeValue(lexical_cast<string>(TerrainPointer->SLP));
	Terrains_Unknown3->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown3));
	Terrains_SoundID->ChangeValue(lexical_cast<string>(TerrainPointer->SoundID));
	Terrains_ComboBox_SoundID->SetSelection(TerrainPointer->SoundID + 1);
	if(GenieVersion >= genie::GV_AoK)
	{
		Terrains_BlendPriority->ChangeValue(lexical_cast<string>(TerrainPointer->BlendPriority));
		Terrains_BlendType->ChangeValue(lexical_cast<string>(TerrainPointer->BlendType));
		if(GenieVersion >= genie::GV_SWGB)
		for(short loop = 0; loop < TerrainPointer->SWGBUNKNOWN1_SIZE; ++loop)
		{
			Terrains_SUnknown1[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->SWGBUnknown1[loop]));
		}
	}
	for(short loop = 0; loop < 3; ++loop)
	{
		Terrains_Colors[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->Colors[loop]));
	}
	for(short loop = 0; loop < Terrains_Unknown5.size(); ++loop)
	Terrains_Unknown5[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->Unknown5[loop]));
	Terrains_Unknown6->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown6));
	for(short loop = 0; loop < TerrainPointer->UNKNOWN7_SIZE; ++loop)
	{
		Terrains_Unknown7[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->Unknown7[loop]));
	}
	Terrains_FrameCount->ChangeValue(lexical_cast<string>(TerrainPointer->FrameCount));
	Terrains_AngleCount->ChangeValue(lexical_cast<string>(TerrainPointer->AngleCount));
	Terrains_TerrainID->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainID));
	for(short loop = 0; loop < TerrainPointer->ELEVATION_GRAPHICS_SIZE; ++loop)
	{
		Terrains_ElevationGraphics[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->ElevationGraphics[loop]));
	}
	Terrains_TerrainReplacementID->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainReplacementID));
	Terrains_ComboBox_TerrainReplacementID->SetSelection(TerrainPointer->TerrainReplacementID + 1);
	Terrains_TerrainDimensions[0]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainDimensions.first));
	Terrains_TerrainDimensions[1]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainDimensions.second));
	for(short loop = 0; loop < TerrainPointer->getTerrainBorderSize(); ++loop)
	{
		Terrains_TerrainBorderID[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainBorderIDs[loop]));
		Terrains_ComboBox_TerrainBorderID[loop]->SetSelection(TerrainPointer->TerrainBorderIDs[loop] + 1);
	}
	for(short loop = 0; loop < TerrainPointer->TERRAIN_UNITS_SIZE; ++loop)
	{
		Terrains_TerrainUnitID[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainUnitID[loop]));
		Terrains_ComboBox_TerrainUnitID[loop]->SetSelection(TerrainPointer->TerrainUnitID[loop] + 1);
		Terrains_TerrainUnitDensity[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainUnitDensity[loop]));
		Terrains_TerrainUnitPriority[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->TerrainUnitPriority[loop]));
	}
	Terrains_NumberOfTerrainUnitsUsed->ChangeValue(lexical_cast<string>(TerrainPointer->NumberOfTerrainUnitsUsed));
}

void AGE_Frame::OnTerrainsAdd(wxCommandEvent &Event) // Their count is hardcoded.
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->Terrains);
	ListTerrains();
}

void AGE_Frame::OnTerrainsInsert(wxCommandEvent &Event) // Their count is hardcoded.
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->Terrains, TerrainIDs[0]);
	ListTerrains();
}

void AGE_Frame::OnTerrainsDelete(wxCommandEvent &Event) // Their count is hardcoded.
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Terrains, TerrainIDs);
	ListTerrains();
}

void AGE_Frame::OnTerrainsCopy(wxCommandEvent &Event)
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Terrains, TerrainIDs, copies->Terrain);
}

void AGE_Frame::OnTerrainsPaste(wxCommandEvent &Event)
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoResize(GenieFile->Terrains, TerrainIDs[0], copies->Terrain);
	ListTerrains();
}

void AGE_Frame::OnTerrainsPasteInsert(wxCommandEvent &Event)
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->Terrains, TerrainIDs[0], copies->Terrain);
	ListTerrains();
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
	Terrains_Name = new TextCtrl_String(Terrains_Scroller);
	Terrains_Holder_Name2 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Name2 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Name 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name2 = new TextCtrl_String(Terrains_Scroller);
	Terrains_Holder_SLP = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_SLP = new wxStaticText(Terrains_Scroller, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SLP = new TextCtrl_Long(Terrains_Scroller);
	Terrains_Holder_SoundID = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_SoundID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SoundID = new TextCtrl_Long(Terrains_Scroller);
	Terrains_ComboBox_SoundID = new ComboBox_Plus1(Terrains_Scroller, Terrains_SoundID);
	SoundComboBoxList.push_back(Terrains_ComboBox_SoundID);
	Terrains_Holder_BlendPriority = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_BlendPriority = new wxStaticText(Terrains_Scroller, wxID_ANY, " Blend Priority", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_BlendPriority = new TextCtrl_Long(Terrains_Scroller);
	Terrains_Holder_BlendType = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_BlendType = new wxStaticText(Terrains_Scroller, wxID_ANY, " Blend Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_BlendType = new TextCtrl_Long(Terrains_Scroller);
	Terrains_Holder_Colors = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Colors = new wxGridSizer(3, 0, 0);
	Terrains_Text_Colors = new wxStaticText(Terrains_Scroller, wxID_ANY, " Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 3; ++loop)
	Terrains_Colors[loop] = new TextCtrl_UByte(Terrains_Scroller);
	Terrains_Holder_FrameCount = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_FrameCount = new wxStaticText(Terrains_Scroller, wxID_ANY, " Frame Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_FrameCount = new TextCtrl_Short(Terrains_Scroller);
	Terrains_Holder_TerrainReplacementID = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainReplacementID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Replacement", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainReplacementID = new TextCtrl_Short(Terrains_Scroller);
	Terrains_ComboBox_TerrainReplacementID = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainReplacementID);
	TerrainComboBoxList.push_back(Terrains_ComboBox_TerrainReplacementID);
	Terrains_Holder_TerrainDimensions = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainDimensions = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Dimensions", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainDimensions[0] = new TextCtrl_Short(Terrains_Scroller);
	Terrains_TerrainDimensions[1] = new TextCtrl_Short(Terrains_Scroller);
	Terrains_Holder_NumberOfTerrainUnitsUsed = new wxBoxSizer(wxVERTICAL);
	Terrains_Holder_NumberOfTerrainUnitsUsed1 = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Text_NumberOfTerrainUnitsUsed = new wxStaticText(Terrains_Scroller, wxID_ANY, " Number of Terrain Units Used", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_NumberOfTerrainUnitsUsed = new TextCtrl_Short(Terrains_Scroller);
	Terrains_Holder_TerrainUnits = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Holder_TerrainUnitID = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_TerrainUnitID = new wxGridSizer(2, 0, 0);
	Terrains_Holder_TerrainUnitDensity = new wxBoxSizer(wxVERTICAL);
	Terrains_Holder_TerrainUnitPriority = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainUnitID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Text_TerrainUnitDensity = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit Density", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Text_TerrainUnitPriority = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit Priority *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < TERRAINUNITS; ++loop)
	{
		Terrains_TerrainUnitID[loop] = new TextCtrl_Short(Terrains_Scroller);
		Terrains_ComboBox_TerrainUnitID[loop] = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainUnitID[loop]);
		UnitComboBoxList.push_back(Terrains_ComboBox_TerrainUnitID[loop]);
		Terrains_TerrainUnitDensity[loop] = new TextCtrl_Short(Terrains_Scroller);
		Terrains_TerrainUnitPriority[loop] = new TextCtrl_Byte(Terrains_Scroller);
		Terrains_TerrainUnitPriority[loop]->SetToolTip("1 prevails, others don't");
	}
	Terrains_Holder_TerrainBorders = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_TerrainBorders = new wxGridSizer(6, 0, 0);
	Terrains_Text_TerrainBorderID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Borders", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < TERRAINBORDERSMAX; ++loop)
	{
		Terrains_TerrainBorderID[loop] = new TextCtrl_Short(Terrains_Scroller);
		Terrains_ComboBox_TerrainBorderID[loop] = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainBorderID[loop]);
		TerrainBorderComboBoxList.push_back(Terrains_ComboBox_TerrainBorderID[loop]);
	}
	Terrains_Holder_UnknownArea = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknowns1 = new wxGridSizer(4, 5, 5);
	Terrains_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown1 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown1 = new TextCtrl_Short(Terrains_Scroller);
	Terrains_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown2 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Enabled", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown2 = new TextCtrl_Short(Terrains_Scroller);
	Terrains_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown3 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown3 = new TextCtrl_Float(Terrains_Scroller);
	Terrains_Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknown5 = new wxGridSizer(5, 0, 0);
	Terrains_Text_Unknown5 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < Terrains_Unknown5.size(); ++loop)
	Terrains_Unknown5[loop] = new TextCtrl_Byte(Terrains_Scroller);
	Terrains_Holder_Unknown6 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown6 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown6 = new TextCtrl_Float(Terrains_Scroller);
	Terrains_Holder_AngleCount = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_AngleCount = new wxStaticText(Terrains_Scroller, wxID_ANY, " Angle Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_AngleCount = new TextCtrl_Short(Terrains_Scroller);
	Terrains_Holder_TerrainID = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainID = new TextCtrl_Short(Terrains_Scroller);
	Terrains_Holder_ElevationGraphics = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknown9 = new wxGridSizer(6, 0, 0);
	Terrains_Text_ElevationGraphics = new wxStaticText(Terrains_Scroller, wxID_ANY, " Elevation Graphics *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 54; ++loop)
	{
		Terrains_ElevationGraphics[loop] = new TextCtrl_Short(Terrains_Scroller);
	}
	Terrains_Holder_Unknown7 = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknown7 = new wxGridSizer(12, 0, 0);
	Terrains_Text_Unknown7 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < Terrains_Unknown7.size(); ++loop)
	Terrains_Unknown7[loop] = new TextCtrl_Byte(Terrains_Scroller);
	Terrains_Holder_SUnknown1 = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_SUnknown1 = new wxGridSizer(12, 0, 0);
	Terrains_Text_SUnknown1 = new wxStaticText(Terrains_Scroller, wxID_ANY, " SW Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 24; ++loop)
	Terrains_SUnknown1[loop] = new TextCtrl_Byte(Terrains_Scroller);

	Terrains_UsedCountHolder->Add(Terrains_UsedCountText, 0, wxEXPAND);
	Terrains_UsedCountHolder->Add(2, -1);
	Terrains_UsedCountHolder->Add(Terrains_UsedCount, 1, wxEXPAND);

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
	Terrains_Terrains->Add(Terrains_UsedCountHolder, 0, wxEXPAND);
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
	for(short loop = 0; loop < 3; ++loop)
	Terrains_Grid_Colors->Add(Terrains_Colors[loop], 1, wxEXPAND);
	Terrains_Holder_Colors->Add(Terrains_Text_Colors, 0, wxEXPAND);
	Terrains_Holder_Colors->Add(Terrains_Grid_Colors, 0, wxEXPAND);
	Terrains_Holder_Unknown5->Add(Terrains_Text_Unknown5, 0, wxEXPAND);
	for(short loop = 0; loop < Terrains_Unknown5.size(); ++loop)
	Terrains_Grid_Unknown5->Add(Terrains_Unknown5[loop], 1, wxEXPAND);
	Terrains_Holder_Unknown5->Add(Terrains_Grid_Unknown5, 0, wxEXPAND);
	Terrains_Holder_Unknown6->Add(Terrains_Text_Unknown6, 0, wxEXPAND);
	Terrains_Holder_Unknown6->Add(Terrains_Unknown6, 1, wxEXPAND);
	for(short loop = 0; loop < Terrains_Unknown7.size(); ++loop)
	Terrains_Grid_Unknown7->Add(Terrains_Unknown7[loop], 1, wxEXPAND);
	Terrains_Holder_Unknown7->Add(Terrains_Text_Unknown7, 0, wxEXPAND);
	Terrains_Holder_Unknown7->Add(Terrains_Grid_Unknown7, 0, wxEXPAND);
	Terrains_Holder_FrameCount->Add(Terrains_Text_FrameCount, 0, wxEXPAND);
	Terrains_Holder_FrameCount->Add(Terrains_FrameCount, 0, wxEXPAND);
	Terrains_Holder_AngleCount->Add(Terrains_Text_AngleCount, 0, wxEXPAND);
	Terrains_Holder_AngleCount->Add(Terrains_AngleCount, 0, wxEXPAND);
	Terrains_Holder_TerrainID->Add(Terrains_Text_TerrainID, 0, wxEXPAND);
	Terrains_Holder_TerrainID->Add(Terrains_TerrainID, 0, wxEXPAND);
	Terrains_Holder_ElevationGraphics->Add(Terrains_Text_ElevationGraphics, 0, wxEXPAND);
	Terrains_Holder_ElevationGraphics->Add(Terrains_Grid_Unknown9, 0, wxEXPAND);
	for(short loop = 0; loop < 54; ++loop)
	{
		Terrains_Grid_Unknown9->Add(Terrains_ElevationGraphics[loop], 1, wxEXPAND);
	}
	Terrains_Holder_TerrainReplacementID->Add(Terrains_Text_TerrainReplacementID, 0, wxEXPAND);
	Terrains_Holder_TerrainReplacementID->Add(Terrains_TerrainReplacementID, 1, wxEXPAND);
	Terrains_Holder_TerrainReplacementID->Add(Terrains_ComboBox_TerrainReplacementID, 1, wxEXPAND);
	Terrains_Holder_TerrainDimensions->Add(Terrains_Text_TerrainDimensions, 0, wxEXPAND);
	Terrains_Holder_TerrainDimensions->Add(Terrains_TerrainDimensions[0], 1, wxEXPAND);
	Terrains_Holder_TerrainDimensions->Add(Terrains_TerrainDimensions[1], 1, wxEXPAND);
	for(short loop = 0; loop < TERRAINBORDERSMAX; ++loop)
	{
		Terrains_Grid_TerrainBorders->Add(Terrains_TerrainBorderID[loop], 1, wxEXPAND);
		Terrains_Grid_TerrainBorders->Add(Terrains_ComboBox_TerrainBorderID[loop], 1, wxEXPAND);
	}
	Terrains_Holder_TerrainBorders->Add(Terrains_Text_TerrainBorderID, 0, wxEXPAND);
	Terrains_Holder_TerrainBorders->Add(Terrains_Grid_TerrainBorders, 0, wxEXPAND);
	Terrains_Holder_TerrainUnitDensity->Add(Terrains_Text_TerrainUnitDensity, 0, wxEXPAND);
	Terrains_Holder_TerrainUnitPriority->Add(Terrains_Text_TerrainUnitPriority, 0, wxEXPAND);
	for(short loop = 0; loop < TERRAINUNITS; ++loop)
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
	for(short loop = 0; loop < 24; ++loop)
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
	Terrains_Grid_Unknowns1->Add(Terrains_Holder_Unknown6, 1, wxEXPAND);
	Terrains_Grid_Unknowns1->Add(Terrains_Holder_AngleCount, 1, wxEXPAND);
	Terrains_Grid_Unknowns1->Add(Terrains_Holder_TerrainID, 1, wxEXPAND);
	Terrains_Holder_UnknownArea->Add(Terrains_Grid_Unknowns1, 0, wxEXPAND);
	Terrains_Holder_UnknownArea->Add(-1, 5);
	Terrains_Holder_UnknownArea->Add(Terrains_Holder_Unknown5, 0, wxEXPAND);
	Terrains_Holder_UnknownArea->Add(-1, 5);
	Terrains_Holder_UnknownArea->Add(Terrains_Holder_ElevationGraphics, 0, wxEXPAND);
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

	Terrains_Name->Connect(Terrains_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Terrains), NULL, this);
	Terrains_Name2->Connect(Terrains_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Terrains), NULL, this);
	Terrains_UsedCount->Connect(Terrains_UsedCount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnTerrainCountChange), NULL, this);
}

void AGE_Frame::OnKillFocus_Terrains(wxFocusEvent &Event)
{
	if(!((AGETextCtrl*)Event.GetEventObject())->SaveEdits()) return;
	if(Event.GetId() == Terrains_Name->GetId())
	{
		ListTerrains();
	}
	else if(Event.GetId() == Terrains_Name2->GetId())
	{
		wxCommandEvent E;
		OnTerrainsSelect(E);
	}
	Event.Skip();
}
