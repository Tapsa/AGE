#include "../AGE_Frame.h"

string AGE_Frame::GetTerrainName(short Index, bool Filter)
{
	if(GenieFile->TerrainBlock.Terrains.size() <= Index) return "Nonexistent Terrain";
	string Name = "";
	if(Filter)
	{
		short Selection[2];
		for(short loop = 0; loop < 2; ++loop)
		Selection[loop] = Terrains_SearchFilters[loop]->GetSelection();

		if(Selection[0] > 1) // Internal name prevents
		for(short loop = 0; loop < 2; ++loop)
		{
			switch(Selection[loop])
			{
				case 2: // SLP
					Name += "SLP "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].SLP);
					break;
				case 3: // Enabled
					Name += "E "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].Enabled);
					break;
				case 4: // Random
					Name += "R "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].Random);
					break;
				case 5: // Unknown3
					Name += "U3 "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].Unknown3);
					break;
				case 6: // SoundID
					Name += "S "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].SoundID);
					break;
				case 7: // BlendPriority
					Name += "BP "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].BlendPriority);
					break;
				case 8: // BlendType
					Name += "BT "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].BlendType);
					break;
				case 9: // Colors
					{
						Name += "H"+FormatInt(GenieFile->TerrainBlock.Terrains[Index].Colors[0]);
						Name += " M"+FormatInt(GenieFile->TerrainBlock.Terrains[Index].Colors[1]);
						Name += " L"+FormatInt(GenieFile->TerrainBlock.Terrains[Index].Colors[2]);
					}
					break;
				case 10: // CliffColors
					{
						Name += "LT"+FormatInt(GenieFile->TerrainBlock.Terrains[Index].CliffColors.first);
						Name += " RT"+FormatInt(GenieFile->TerrainBlock.Terrains[Index].CliffColors.second);
					}
					break;
				case 11: // PassableTerrain
					Name += "PT "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].PassableTerrain);
					break;
				case 12: // ImpassableTerrain
					Name += "IT "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].ImpassableTerrain);
					break;
				case 13: // Frame Count
					Name += "FC "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].ElevationGraphics[0].FrameCount);
					break;
				case 14: // Angle Count
					Name += "AC "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].ElevationGraphics[0].AngleCount);
					break;
				case 15: // TerrainToDraw
					Name += "TD "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].TerrainToDraw);
					break;
				case 16: // TerrainDimensions
					Name += "R"+FormatInt(GenieFile->TerrainBlock.Terrains[Index].TerrainDimensions.first);
					Name += " C"+FormatInt(GenieFile->TerrainBlock.Terrains[Index].TerrainDimensions.second);
					break;
				case 17: // NumberOfTerrainUnitsUsed
					Name += "TU "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].NumberOfTerrainUnitsUsed);
					break;
				case 18: // Unknown1
					Name += "U1 "+FormatInt(GenieFile->TerrainBlock.Terrains[Index].Unknown1);
					break;
			}
			Name += ", ";
			if(Selection[loop+1] < 1) break; // Internal name breaks
		}
		if(Selection[0] == 1) goto InternalName;
	}

	if(!GenieFile->TerrainBlock.Terrains[Index].Name.empty())
	{
		return Name + GenieFile->TerrainBlock.Terrains[Index].Name;
	}
InternalName:
	if(!GenieFile->TerrainBlock.Terrains[Index].Name2.empty())
	{
		return Name + GenieFile->TerrainBlock.Terrains[Index].Name2;
	}
	return Name + "New Terrain";
}

void AGE_Frame::OnTerrainsSearch(wxCommandEvent &Event)
{
	How2List = SEARCH;
	ListTerrains1(false);
}

void AGE_Frame::ListTerrainNumbers()
{
	Terrains_UsedCount->resize(2);
	Terrains_UsedCount->container[0] = &GenieFile->TerrainBlock.TerrainsUsed2;
	Terrains_UsedCount->container[1] = &GenieFile->TerrainsUsed1;
	Terrains_UsedCount->Update();
	Borders_UsedCount->resize(1);
	Borders_UsedCount->container[0] = &GenieFile->TerrainBlock.BordersUsed;
	Borders_UsedCount->Update();
}

void AGE_Frame::OnTerrainCountChange(wxFocusEvent &Event)
{
	Event.Skip();
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
}

void AGE_Frame::ListTerrains1(bool all)
{
	FirstVisible = How2List == SEARCH ? 0 : Terrains_Terrains_List->HitTest(wxPoint(0, 0));
	InitTerrains1(all);
	wxCommandEvent E;
	OnTerrainsSelect(E);
	if(all) OnTerrainRestrictionsTerrainSelect(E);
}

void AGE_Frame::ListTerrains2()
{
	FirstVisible = How2List == SEARCH ? 0 : TerRestrict_Terrains_List->HitTest(wxPoint(0, 0));
	InitTerrains2();
	wxCommandEvent E;
	OnTerrainRestrictionsTerrainSelect(E);
}

void AGE_Frame::InitTerrains1(bool all)
{
	searchText = Terrains_Terrains_Search->GetValue().Lower();
	excludeText = Terrains_Terrains_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = Terrains_Terrains_UseAnd[loop]->GetValue();

	list<void*> dataPointers;
	wxArrayString names, filteredNames;
	if(all) names.Alloc(GenieFile->TerrainBlock.Terrains.size());

	for(short loop = 0; loop < GenieFile->TerrainBlock.Terrains.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTerrainName(loop, true);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TerrainBlock.Terrains[loop]);
		}
		if(all) names.Add(" "+FormatInt(loop)+" - "+GetTerrainName(loop));
	}

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;

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

	for(short loop = 0; loop < GenieFile->TerrainsUsed1; ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - A"+lexical_cast<string>((bool)GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible[loop]);
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

	SwapSelection(Event.GetSelection(), Items);
	TerrainIDs.resize(selections);
	if(GenieVersion < genie::GV_SWGB)
	Terrains_Unknown1->resize(selections);
	Terrains_Enabled->resize(selections);
	Terrains_Random->resize(selections);
	Terrains_Name->resize(selections);
	Terrains_Name2->resize(selections);
	if(GenieVersion >= genie::GV_AoEB)
	Terrains_SLP->resize(selections);
	Terrains_Unknown3->resize(selections);
	Terrains_SoundID->resize(selections);
	if(GenieVersion >= genie::GV_AoKB)
	{
		Terrains_BlendPriority->resize(selections);
		Terrains_BlendType->resize(selections);
	}
	for(short loop = 0; loop < 3; ++loop)
	{
		Terrains_Colors[loop]->resize(selections);
	}
	for(short loop = 0; loop < Terrains_CliffColors.size(); ++loop)
	Terrains_CliffColors[loop]->resize(selections);
	Terrains_PassableTerrain->resize(selections);
	Terrains_ImpassableTerrain->resize(selections);
	Terrains_IsAnimated->resize(selections);
	Terrains_AnimationFrames->resize(selections);
	Terrains_PauseFames->resize(selections);
	Terrains_Interval->resize(selections);
	Terrains_PauseBetweenLoops->resize(selections);
	Terrains_Frame->resize(selections);
	Terrains_DrawFrame->resize(selections);
	Terrains_AnimateLast->resize(selections);
	Terrains_FrameChanged->resize(selections);
	Terrains_Drawn->resize(selections);
	for(short loop = 0; loop < genie::SharedTerrain::TILE_TYPE_COUNT * 3; ++loop)
	{
		Terrains_ElevationGraphics[loop]->resize(selections);
	}
	Terrains_TerrainReplacementID->resize(selections);
	Terrains_TerrainDimensions[0]->resize(selections);
	Terrains_TerrainDimensions[1]->resize(selections);
	for(short loop = 0; loop < genie::Terrain::TERRAIN_UNITS_SIZE; ++loop)
	{
		Terrains_TerrainUnitID[loop]->resize(selections);
		Terrains_TerrainUnitDensity[loop]->resize(selections);
		Terrains_TerrainUnitPriority[loop]->resize(selections);
	}
	Terrains_UsedTerrainUnits->resize(selections);

	genie::Terrain * TerrainPointer;
	for(auto sel = selections; sel--> 0;)
	{
		TerrainPointer = (genie::Terrain*)Terrains_Terrains_List->GetClientData(Items.Item(sel));
		TerrainIDs[sel] = (TerrainPointer - (&GenieFile->TerrainBlock.Terrains[0]));

		if(GenieVersion < genie::GV_SWGB)
		Terrains_Unknown1->container[sel] = &TerrainPointer->Unknown1;
		Terrains_Enabled->container[sel] = &TerrainPointer->Enabled;
		Terrains_Random->container[sel] = &TerrainPointer->Random;
		Terrains_Name->container[sel] = &TerrainPointer->Name;
		Terrains_Name2->container[sel] = &TerrainPointer->Name2;
		if(GenieVersion >= genie::GV_AoEB)
		Terrains_SLP->container[sel] = &TerrainPointer->SLP;
		Terrains_Unknown3->container[sel] = &TerrainPointer->Unknown3;
		Terrains_SoundID->container[sel] = &TerrainPointer->SoundID;
		if(GenieVersion >= genie::GV_AoKB)
		{
			Terrains_BlendPriority->container[sel] = &TerrainPointer->BlendPriority;
			Terrains_BlendType->container[sel] = &TerrainPointer->BlendType;
		}
		for(short loop = 0; loop < 3; ++loop)
		{
			Terrains_Colors[loop]->container[sel] = &TerrainPointer->Colors[loop];
		}
		for(short loop = 0; loop < Terrains_CliffColors.size(); ++loop)
		Terrains_CliffColors[0]->container[sel] = &TerrainPointer->CliffColors.first;
		Terrains_CliffColors[1]->container[sel] = &TerrainPointer->CliffColors.second;
		Terrains_PassableTerrain->container[sel] = &TerrainPointer->PassableTerrain;
		Terrains_ImpassableTerrain->container[sel] = &TerrainPointer->ImpassableTerrain;
		Terrains_IsAnimated->container[sel] = &TerrainPointer->IsAnimated;
		Terrains_AnimationFrames->container[sel] = &TerrainPointer->AnimationFrames;
		Terrains_PauseFames->container[sel] = &TerrainPointer->PauseFames;
		Terrains_Interval->container[sel] = &TerrainPointer->Interval;
		Terrains_PauseBetweenLoops->container[sel] = &TerrainPointer->PauseBetweenLoops;
		Terrains_Frame->container[sel] = &TerrainPointer->Frame;
		Terrains_DrawFrame->container[sel] = &TerrainPointer->DrawFrame;
		Terrains_AnimateLast->container[sel] = &TerrainPointer->AnimateLast;
		Terrains_FrameChanged->container[sel] = &TerrainPointer->FrameChanged;
		Terrains_Drawn->container[sel] = &TerrainPointer->Drawn;
		for(short loop = 0, slot = 0; loop < genie::SharedTerrain::TILE_TYPE_COUNT; ++loop)
		{
			Terrains_ElevationGraphics[slot++]->container[sel] = &TerrainPointer->ElevationGraphics[loop].FrameCount;
			Terrains_ElevationGraphics[slot++]->container[sel] = &TerrainPointer->ElevationGraphics[loop].AngleCount;
			Terrains_ElevationGraphics[slot++]->container[sel] = &TerrainPointer->ElevationGraphics[loop].ShapeID;
		}
		Terrains_TerrainReplacementID->container[sel] = &TerrainPointer->TerrainToDraw;
		Terrains_TerrainDimensions[0]->container[sel] = &TerrainPointer->TerrainDimensions.first;
		Terrains_TerrainDimensions[1]->container[sel] = &TerrainPointer->TerrainDimensions.second;
		for(short loop = 0; loop < TerrainPointer->TERRAIN_UNITS_SIZE; ++loop)
		{
			Terrains_TerrainUnitID[loop]->container[sel] = &TerrainPointer->TerrainUnitID[loop];
			Terrains_TerrainUnitDensity[loop]->container[sel] = &TerrainPointer->TerrainUnitDensity[loop];
			Terrains_TerrainUnitPriority[loop]->container[sel] = &TerrainPointer->TerrainUnitPriority[loop];
		}
		Terrains_UsedTerrainUnits->container[sel] = &TerrainPointer->NumberOfTerrainUnitsUsed;
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected terrain: "+lexical_cast<string>(TerrainIDs[0]), 0);

	if(GenieVersion < genie::GV_SWGB)
	Terrains_Unknown1->Update();
	Terrains_Enabled->Update();
	Terrains_Random->Update();
	Terrains_Name->Update();
	Terrains_Name2->Update();
	if(GenieVersion >= genie::GV_AoEB)
	Terrains_SLP->Update();
	Terrains_Unknown3->Update();
	Terrains_SoundID->Update();
	if(GenieVersion >= genie::GV_AoKB)
	{
		Terrains_BlendPriority->Update();
		Terrains_BlendType->Update();
	}
	for(short loop = 0; loop < 3; ++loop)
	{
		Terrains_Colors[loop]->Update();
	}
	for(short loop = 0; loop < Terrains_CliffColors.size(); ++loop)
	Terrains_CliffColors[loop]->Update();
	Terrains_PassableTerrain->Update();
	Terrains_ImpassableTerrain->Update();
	Terrains_IsAnimated->Update();
	Terrains_AnimationFrames->Update();
	Terrains_PauseFames->Update();
	Terrains_Interval->Update();
	Terrains_PauseBetweenLoops->Update();
	Terrains_Frame->Update();
	Terrains_DrawFrame->Update();
	Terrains_AnimateLast->Update();
	Terrains_FrameChanged->Update();
	Terrains_Drawn->Update();
	for(short loop = 0; loop < genie::SharedTerrain::TILE_TYPE_COUNT * 3; ++loop)
	{
		Terrains_ElevationGraphics[loop]->Update();
	}
	Terrains_TerrainReplacementID->Update();
	Terrains_TerrainDimensions[0]->Update();
	Terrains_TerrainDimensions[1]->Update();
	for(short loop = 0; loop < TerrainPointer->TERRAIN_UNITS_SIZE; ++loop)
	{
		Terrains_TerrainUnitID[loop]->Update();
		Terrains_TerrainUnitDensity[loop]->Update();
		Terrains_TerrainUnitPriority[loop]->Update();
	}
	Terrains_UsedTerrainUnits->Update();

	ListTerrainsBorders();
}

void AGE_Frame::OnTerrainsAdd(wxCommandEvent &Event) // Their count is hardcoded.
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	genie::Terrain::customTerrainAmount = ++CustomTerrains;
	for(short loop = 0; loop < GenieFile->TerrainBlock.Terrains.size(); ++loop)
	GenieFile->TerrainBlock.Terrains[loop].setGameVersion(GenieVersion);
	AddToList(GenieFile->TerrainBlock.Terrains);
	ListTerrains1();
}

void AGE_Frame::OnTerrainsInsert(wxCommandEvent &Event) // Their count is hardcoded.
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	ListTerrains1();
}

void AGE_Frame::OnTerrainsDelete(wxCommandEvent &Event) // Their count is hardcoded.
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::Terrain::customTerrainAmount = CustomTerrains -= TerrainIDs.size();
	DeleteFromList(GenieFile->TerrainBlock.Terrains, TerrainIDs);
	for(short loop = GenieFile->TerrainBlock.Terrains.size(); loop--> 0;)
	DeleteFromList(GenieFile->TerrainBlock.Terrains[loop].Borders, TerrainIDs);
	ListTerrains1();
}

void AGE_Frame::OnTerrainsCopy(wxCommandEvent &Event)
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TerrainBlock.Terrains, TerrainIDs, copies->Terrain);
	Terrains_Terrains_List->SetFocus();
}

void AGE_Frame::OnTerrainsPaste(wxCommandEvent &Event)
{
	auto selections = Terrains_Terrains_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TerrainIDs.size(), copies->Terrain.size()))
		{
			PasteToList(GenieFile->TerrainBlock.Terrains, TerrainIDs, copies->Terrain);
		}
	}
	else
	{
		PasteToListNoResize(GenieFile->TerrainBlock.Terrains, TerrainIDs[0], copies->Terrain);
	}
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

void AGE_Frame::OnTerrainsBorderSearch(wxCommandEvent &Event)
{
	How2List = SEARCH;
	ListTerrainsBorders();
}

void AGE_Frame::ListTerrainsBorders()
{
	FirstVisible = How2List == SEARCH ? 0 : Terrains_Borders_List->HitTest(wxPoint(0, 0));
	searchText = Terrains_Borders_Search->GetValue().Lower();
	excludeText = Terrains_Borders_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TerrainBlock.Terrains.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" "+GetTerrainName(loop)+" - ";
		Name += lexical_cast<string>(GenieFile->TerrainBlock.Terrains[TerrainIDs[0]].Borders[loop])+" ";
		Name += GetTerrainBorderName(GenieFile->TerrainBlock.Terrains[TerrainIDs[0]].Borders[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TerrainBlock.Terrains[TerrainIDs[0]].Borders[loop]);
		}
	}
	Listing(Terrains_Borders_List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTerrainsBorderSelect(E);
}

void AGE_Frame::OnTerrainsBorderSelect(wxCommandEvent &Event)
{
	auto selections = Terrains_Borders_List->GetSelections(Items);
	SwapSelection(Event.GetSelection(), Items);
	TerBorderIDs.resize(selections);
	Terrains_Border->resize(selections);

	int16_t * BorderPointer;
	for(auto loop = selections; loop--> 0;)
	{
		BorderPointer = (int16_t*)Terrains_Borders_List->GetClientData(Items.Item(loop));
		TerBorderIDs[loop] = (BorderPointer - (&GenieFile->TerrainBlock.Terrains[TerrainIDs[0]].Borders[0]));
		Terrains_Border->container[loop] = BorderPointer;
	}

	Terrains_Border->Update();
	Terrains_Border->Enable(selections);
	Terrains_Border_ComboBox->Enable(selections);
}

void AGE_Frame::OnTerrainsBorderCopy(wxCommandEvent &Event)
{
	auto selections = Terrains_Borders_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TerrainBlock.Terrains[TerrainIDs[0]].Borders, TerBorderIDs, copies->TerBorder);
	Terrains_Borders_List->SetFocus();
}

void AGE_Frame::OnTerrainsBorderPaste(wxCommandEvent &Event)
{
	auto selections = Terrains_Borders_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TerBorderIDs.size(), copies->TerBorder.size()))
		{
			PasteToListNoGV(GenieFile->TerrainBlock.Terrains[TerrainIDs[0]].Borders, TerBorderIDs, copies->TerBorder);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TerrainBlock.Terrains[TerrainIDs[0]].Borders, TerBorderIDs[0], copies->TerBorder);
	}
	ListTerrainsBorders();
}

void AGE_Frame::OnTerrainsBorderCopyToBuildings(wxCommandEvent &Event)
{
	for(short loop=1; loop < TerrainIDs.size(); ++loop)
	{
		GenieFile->TerrainBlock.Terrains[TerrainIDs[loop]].Borders = GenieFile->TerrainBlock.Terrains[TerrainIDs[0]].Borders;
	}
}

void AGE_Frame::CreateTerrainControls()
{
	Terrains_Main = new wxBoxSizer(wxHORIZONTAL);
	Terrains_ListArea = new wxBoxSizer(wxVERTICAL);
	Terrains_Terrains_Buttons = new wxGridSizer(2, 0, 0);
	Tab_Terrains = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	Terrains_Terrains = new wxStaticBoxSizer(wxVERTICAL, Tab_Terrains, "Terrains");
	Terrains_Terrains_Search = new wxTextCtrl(Tab_Terrains, wxID_ANY);
	Terrains_Terrains_UseAnd[0] = new wxCheckBox(Tab_Terrains, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Terrains_Terrains_Search_R = new wxTextCtrl(Tab_Terrains, wxID_ANY);
	Terrains_Terrains_UseAnd[1] = new wxCheckBox(Tab_Terrains, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	for(short loop = 0; loop < 2; ++loop)
	{
		Terrains_Terrains_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Terrains_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_Terrains, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	Terrains_Terrains_List = new wxListBox(Tab_Terrains, wxID_ANY, wxDefaultPosition, wxSize(200, 100), 0, NULL, wxLB_EXTENDED);
	Terrains_UsedCountHolder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_UsedCountText = new wxStaticText(Tab_Terrains, wxID_ANY, " Terrains Used *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_UsedCount = new TextCtrl_UShort(this, AGEwindow, Tab_Terrains);
	Terrains_UsedCount->SetToolTip("How many terrains are used\nstarting from the first terrain without gaps");
	Terrains_Add = new wxButton(Tab_Terrains, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Terrains_Delete = new wxButton(Tab_Terrains, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Terrains_Copy = new wxButton(Tab_Terrains, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Terrains_Paste = new wxButton(Tab_Terrains, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));

	Terrains_DataArea = new wxBoxSizer(wxVERTICAL);
	Terrains_Scroller = new wxScrolledWindow(Tab_Terrains, wxID_ANY, wxDefaultPosition, wxSize(600, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Terrains_ScrollArea = new wxBoxSizer(wxHORIZONTAL);
	Terrains_ScrollSpace = new wxBoxSizer(wxVERTICAL);
	Terrains_NameArea_Holder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Area1_Grid = new wxGridSizer(4, 5, 5);
	Terrains_Enabled_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Enabled1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Enabled_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Enabled", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Enabled = new TextCtrl_Byte(this, AGEwindow, Terrains_Scroller, true);
	Terrains_Enabled_CheckBox = new CheckBox_2State(Terrains_Scroller, " Yes", Terrains_Enabled);
	Terrains_Random_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Random_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Random", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Random = new TextCtrl_Byte(this, AGEwindow, Terrains_Scroller, true);
	Terrains_Name_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Name_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name = new TextCtrl_String(this, AGEwindow, Terrains_Scroller);
	Terrains_Name2_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Name2_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " SLP Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name2 = new TextCtrl_String(this, AGEwindow, Terrains_Scroller);
	Terrains_SLP_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_SLP_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SLP = new TextCtrl_Long(this, AGEwindow, Terrains_Scroller);
	Terrains_SoundID_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_SoundID_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SoundID = new TextCtrl_Long(this, AGEwindow, Terrains_Scroller);
	Terrains_SoundID_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_SoundID);
	SoundComboBoxList.push_back(Terrains_SoundID_ComboBox);
	Terrains_BlendPriority_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_BlendPriority_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Blend Priority", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_BlendPriority = new TextCtrl_Long(this, AGEwindow, Terrains_Scroller);
	Terrains_BlendType_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_BlendType_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Blend Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_BlendType = new TextCtrl_Long(this, AGEwindow, Terrains_Scroller);
	Terrains_Colors_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Colors_Grid = new wxGridSizer(3, 0, 0);
	Terrains_Colors_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 3; ++loop)
	Terrains_Colors[loop] = new TextCtrl_UByte(this, AGEwindow, Terrains_Scroller);
	Terrains_CliffColors_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_CliffColors_Grid = new wxGridSizer(2, 0, 0);
	Terrains_CliffColors_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Cliff Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < Terrains_CliffColors.size(); ++loop)
	Terrains_CliffColors[loop] = new TextCtrl_UByte(this, AGEwindow, Terrains_Scroller);

	Terrains_PassableTerrain_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_PassableTerrain_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Passable Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_PassableTerrain = new TextCtrl_Byte(this, AGEwindow, Terrains_Scroller);
	Terrains_PassableTerrain_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_PassableTerrain);
	TerrainComboBoxList.push_back(Terrains_PassableTerrain_ComboBox);
	Terrains_ImpassableTerrain_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_ImpassableTerrain_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Impassable Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_ImpassableTerrain = new TextCtrl_Byte(this, AGEwindow, Terrains_Scroller);
	Terrains_ImpassableTerrain_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_ImpassableTerrain);
	TerrainComboBoxList.push_back(Terrains_ImpassableTerrain_ComboBox);
	Terrains_TerrainReplacementID_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainReplacementID_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain to Draw", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainReplacementID = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller);
	Terrains_TerrainReplacementID_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainReplacementID);
	TerrainComboBoxList.push_back(Terrains_TerrainReplacementID_ComboBox);
	Terrains_TerrainDimensions_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainDimensions_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Dimensions", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainDimensions[0] = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller);
	Terrains_TerrainDimensions[1] = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller);
	Terrains_TerrainDimensions[0]->SetToolTip("Rows");
	Terrains_TerrainDimensions[1]->SetToolTip("Columns");
	Terrains_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Unknown3_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown3 = new TextCtrl_Long(this, AGEwindow, Terrains_Scroller);
	Terrains_GridX = new wxGridSizer(3, 0, 5);
	Terrains_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Unknown1_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown1 = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller);

	Terrains_GreatSpace = new wxBoxSizer(wxHORIZONTAL);
	Terrains_SpaceLeft = new wxBoxSizer(wxVERTICAL);
	Terrains_SpaceRight = new wxBoxSizer(wxVERTICAL);
	Terrains_Borders = new wxStaticBoxSizer(wxVERTICAL, Terrains_Scroller, "Borders");
	Terrains_Borders_Search = new wxTextCtrl(Terrains_Scroller, wxID_ANY);
	Terrains_Borders_Search_R = new wxTextCtrl(Terrains_Scroller, wxID_ANY);
	Terrains_Borders_List = new wxListBox(Terrains_Scroller, wxID_ANY, wxDefaultPosition, wxSize(200, 250), 0, NULL, wxLB_EXTENDED);
	Terrains_Border = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller);
	Terrains_Border_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_Border);
	TerrainBorderComboBoxList.push_back(Terrains_Border_ComboBox);
	Terrains_Borders_Buttons = new wxGridSizer(2, 0, 0);
	Terrains_Borders_Copy = new wxButton(Terrains_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Terrains_Borders_Paste = new wxButton(Terrains_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Terrains_Borders_CopyToTerrains = new wxButton(Terrains_Scroller, wxID_ANY, "Copy all to selected terrains", wxDefaultPosition, wxSize(5, 20));

	Terrains_UsedTerrainUnits_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_UsedTerrainUnits_Grid = new wxGridSizer(3, 0, 5);
	Terrains_UsedTerrainUnits_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Units Used", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_UsedTerrainUnits = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller);
	Terrains_TerrainUnits_Holder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_TerrainUnitID_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainUnitID_Holder1 = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainUnitDensity_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainUnitPriority_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainUnitID_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainUnitDensity_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unit Density", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainUnitPriority_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unit Priority *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < TERRAINUNITS; ++loop)
	{
		Terrains_TerrainUnitID[loop] = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller, true);
		Terrains_TerrainUnitID_ComboBox[loop] = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainUnitID[loop]);
		UnitComboBoxList.push_back(Terrains_TerrainUnitID_ComboBox[loop]);
		Terrains_TerrainUnitDensity[loop] = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller, true);
		Terrains_TerrainUnitPriority[loop] = new TextCtrl_Byte(this, AGEwindow, Terrains_Scroller);
		Terrains_TerrainUnitPriority[loop]->SetToolTip("1 prevails, others don't");
	}
	Terrains_ElevationGraphics_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Unknown9_Grid = new wxGridSizer(3, 0, 0);
	Terrains_ElevationGraphics_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Elevation Graphics\n Frames, Animations, Shape index", wxDefaultPosition, wxSize(-1, 30), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < Terrains_ElevationGraphics.size(); ++loop)
	{
		Terrains_ElevationGraphics[loop] = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller, 2);
	}

	Terrains_Animation_Grid = new wxGridSizer(5, 5, 5);
	Terrains_IsAnimated_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_IsAnimated_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Is Animated", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_IsAnimated = new TextCtrl_Byte(this, AGEwindow, Terrains_Scroller);
	Terrains_AnimationFrames_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_AnimationFrames_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Animation Frames *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_AnimationFrames = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller);
	Terrains_AnimationFrames->SetToolTip("Number of frames to animate through");
	Terrains_PauseFames_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_PauseFames_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Pause Fames *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_PauseFames = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller);
	Terrains_PauseFames->SetToolTip("Number of frames to pause animation after last frame is drawn");
	Terrains_Interval_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Interval_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Interval *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Interval = new TextCtrl_Float(this, AGEwindow, Terrains_Scroller);
	Terrains_Interval->SetToolTip("Time between frames");
	Terrains_PauseBetweenLoops_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_PauseBetweenLoops_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Pause Between Loops *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_PauseBetweenLoops = new TextCtrl_Float(this, AGEwindow, Terrains_Scroller);
	Terrains_PauseBetweenLoops->SetToolTip("Time to pause after last frame");
	Terrains_Frame_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Frame_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Frame *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Frame = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller);
	Terrains_Frame->SetToolTip("The current frame (includes animation and pause frames)");
	Terrains_DrawFrame_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_DrawFrame_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Draw Frame *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_DrawFrame = new TextCtrl_Short(this, AGEwindow, Terrains_Scroller);
	Terrains_DrawFrame->SetToolTip("The current frame to draw");
	Terrains_AnimateLast_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_AnimateLast_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Animate Last *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_AnimateLast = new TextCtrl_Float(this, AGEwindow, Terrains_Scroller);
	Terrains_AnimateLast->SetToolTip("Last time animation frame was changed");
	Terrains_FrameChanged_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_FrameChanged_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Frame Changed *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_FrameChanged = new TextCtrl_Byte(this, AGEwindow, Terrains_Scroller);
	Terrains_FrameChanged->SetToolTip("Has the Draw Frame changed since terrain was drawn?");
	Terrains_Drawn_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Drawn_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Drawn", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Drawn = new TextCtrl_Byte(this, AGEwindow, Terrains_Scroller);

	for(short loop = 0; loop < 2; ++loop)
	{
		Terrains_SearchFilters[loop]->Append("Internal Name");	// 0
		Terrains_SearchFilters[loop]->Append("SLP Name");
		Terrains_SearchFilters[loop]->Append("SLP");
		Terrains_SearchFilters[loop]->Append("Enabled");
		Terrains_SearchFilters[loop]->Append("Random");
		Terrains_SearchFilters[loop]->Append("Unknown 3");
		Terrains_SearchFilters[loop]->Append("Sound");
		Terrains_SearchFilters[loop]->Append("Blend Priority");
		Terrains_SearchFilters[loop]->Append("Blend Type");
		Terrains_SearchFilters[loop]->Append("Colors");
		Terrains_SearchFilters[loop]->Append("Cliff Colors");
		Terrains_SearchFilters[loop]->Append("Passable Terrain");
		Terrains_SearchFilters[loop]->Append("Impassable Terrain");
		Terrains_SearchFilters[loop]->Append("Frame Count");
		Terrains_SearchFilters[loop]->Append("Angle Count");
		Terrains_SearchFilters[loop]->Append("Terrain to Draw");
		Terrains_SearchFilters[loop]->Append("Terrain Dimensions");
		Terrains_SearchFilters[loop]->Append("Terrain Units Used");
		Terrains_SearchFilters[loop]->Append("Unknown 1");
		Terrains_SearchFilters[loop]->SetSelection(0);
	}

	Terrains_UsedCountHolder->Add(Terrains_UsedCountText, 0, wxEXPAND);
	Terrains_UsedCountHolder->AddSpacer(2);
	Terrains_UsedCountHolder->Add(Terrains_UsedCount, 1, wxEXPAND);

	Terrains_Terrains_Buttons->Add(Terrains_Add, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Delete, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Copy, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Paste, 1, wxEXPAND);

	Terrains_Terrains_Searches[0]->Add(Terrains_Terrains_Search, 1, wxEXPAND);
	Terrains_Terrains_Searches[0]->AddSpacer(2);
	Terrains_Terrains_Searches[0]->Add(Terrains_Terrains_UseAnd[0], 0, wxEXPAND);
	Terrains_Terrains_Searches[1]->Add(Terrains_Terrains_Search_R, 1, wxEXPAND);
	Terrains_Terrains_Searches[1]->AddSpacer(2);
	Terrains_Terrains_Searches[1]->Add(Terrains_Terrains_UseAnd[1], 0, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Terrains_Terrains->Add(Terrains_Terrains_Searches[loop], 0, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Terrains_Terrains->Add(Terrains_SearchFilters[loop], 0, wxEXPAND);
	Terrains_Terrains->AddSpacer(2);
	Terrains_Terrains->Add(Terrains_Terrains_List, 1, wxEXPAND);
	Terrains_Terrains->AddSpacer(2);
	Terrains_Terrains->Add(Terrains_UsedCountHolder, 0, wxEXPAND);
	Terrains_Terrains->AddSpacer(2);
	Terrains_Terrains->Add(Terrains_Terrains_Buttons, 0, wxEXPAND);

	Terrains_ListArea->AddSpacer(5);
	Terrains_ListArea->Add(Terrains_Terrains, 1, wxEXPAND);
	Terrains_ListArea->AddSpacer(5);

	Terrains_Unknown1_Holder->Add(Terrains_Unknown1_Text, 0, wxEXPAND);
	Terrains_Unknown1_Holder->Add(Terrains_Unknown1, 0, wxEXPAND);
	Terrains_Enabled1_Holder->Add(Terrains_Enabled, 1, wxEXPAND);
	Terrains_Enabled1_Holder->AddSpacer(2);
	Terrains_Enabled1_Holder->Add(Terrains_Enabled_CheckBox, 1, wxEXPAND);
	Terrains_Enabled_Holder->Add(Terrains_Enabled_Text, 0, wxEXPAND);
	Terrains_Enabled_Holder->Add(Terrains_Enabled1_Holder, 1, wxEXPAND);
	Terrains_Random_Holder->Add(Terrains_Random_Text, 0, wxEXPAND);
	Terrains_Random_Holder->Add(Terrains_Random, 0, wxEXPAND);
	Terrains_Name_Holder->Add(Terrains_Name_Text, 0, wxEXPAND);
	Terrains_Name_Holder->Add(Terrains_Name, 1, wxEXPAND);
	Terrains_Name2_Holder->Add(Terrains_Name2_Text, 0, wxEXPAND);
	Terrains_Name2_Holder->Add(Terrains_Name2, 1, wxEXPAND);
	Terrains_SLP_Holder->Add(Terrains_SLP_Text, 0, wxEXPAND);
	Terrains_SLP_Holder->Add(Terrains_SLP, 0, wxEXPAND);
	Terrains_Unknown3_Holder->Add(Terrains_Unknown3_Text, 0, wxEXPAND);
	Terrains_Unknown3_Holder->Add(Terrains_Unknown3, 0, wxEXPAND);
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
	Terrains_CliffColors_Holder->Add(Terrains_CliffColors_Text, 0, wxEXPAND);
	for(short loop = 0; loop < Terrains_CliffColors.size(); ++loop)
	Terrains_CliffColors_Grid->Add(Terrains_CliffColors[loop], 1, wxEXPAND);
	Terrains_CliffColors_Holder->Add(Terrains_CliffColors_Grid, 0, wxEXPAND);
	Terrains_PassableTerrain_Holder->Add(Terrains_PassableTerrain_Text, 0, wxEXPAND);
	Terrains_PassableTerrain_Holder->Add(Terrains_PassableTerrain, 0, wxEXPAND);
	Terrains_PassableTerrain_Holder->Add(Terrains_PassableTerrain_ComboBox, 0, wxEXPAND);
	Terrains_ImpassableTerrain_Holder->Add(Terrains_ImpassableTerrain_Text, 0, wxEXPAND);
	Terrains_ImpassableTerrain_Holder->Add(Terrains_ImpassableTerrain, 0, wxEXPAND);
	Terrains_ImpassableTerrain_Holder->Add(Terrains_ImpassableTerrain_ComboBox, 0, wxEXPAND);

	Terrains_IsAnimated_Holder->Add(Terrains_IsAnimated_Text, 0, wxEXPAND);
	Terrains_AnimationFrames_Holder->Add(Terrains_AnimationFrames_Text, 0, wxEXPAND);
	Terrains_PauseFames_Holder->Add(Terrains_PauseFames_Text, 0, wxEXPAND);
	Terrains_Interval_Holder->Add(Terrains_Interval_Text, 0, wxEXPAND);
	Terrains_PauseBetweenLoops_Holder->Add(Terrains_PauseBetweenLoops_Text, 0, wxEXPAND);
	Terrains_Frame_Holder->Add(Terrains_Frame_Text, 0, wxEXPAND);
	Terrains_DrawFrame_Holder->Add(Terrains_DrawFrame_Text, 0, wxEXPAND);
	Terrains_AnimateLast_Holder->Add(Terrains_AnimateLast_Text, 0, wxEXPAND);
	Terrains_FrameChanged_Holder->Add(Terrains_FrameChanged_Text, 0, wxEXPAND);
	Terrains_Drawn_Holder->Add(Terrains_Drawn_Text, 0, wxEXPAND);
	Terrains_IsAnimated_Holder->Add(Terrains_IsAnimated, 1, wxEXPAND);
	Terrains_AnimationFrames_Holder->Add(Terrains_AnimationFrames, 1, wxEXPAND);
	Terrains_PauseFames_Holder->Add(Terrains_PauseFames, 1, wxEXPAND);
	Terrains_Interval_Holder->Add(Terrains_Interval, 1, wxEXPAND);
	Terrains_PauseBetweenLoops_Holder->Add(Terrains_PauseBetweenLoops, 1, wxEXPAND);
	Terrains_Frame_Holder->Add(Terrains_Frame, 1, wxEXPAND);
	Terrains_DrawFrame_Holder->Add(Terrains_DrawFrame, 1, wxEXPAND);
	Terrains_AnimateLast_Holder->Add(Terrains_AnimateLast, 1, wxEXPAND);
	Terrains_FrameChanged_Holder->Add(Terrains_FrameChanged, 1, wxEXPAND);
	Terrains_Drawn_Holder->Add(Terrains_Drawn, 1, wxEXPAND);
	Terrains_Animation_Grid->Add(Terrains_IsAnimated_Holder, 1, wxEXPAND);
	Terrains_Animation_Grid->Add(Terrains_AnimationFrames_Holder, 1, wxEXPAND);
	Terrains_Animation_Grid->Add(Terrains_PauseFames_Holder, 1, wxEXPAND);
	Terrains_Animation_Grid->Add(Terrains_Interval_Holder, 1, wxEXPAND);
	Terrains_Animation_Grid->Add(Terrains_PauseBetweenLoops_Holder, 1, wxEXPAND);
	Terrains_Animation_Grid->Add(Terrains_Frame_Holder, 1, wxEXPAND);
	Terrains_Animation_Grid->Add(Terrains_DrawFrame_Holder, 1, wxEXPAND);
	Terrains_Animation_Grid->Add(Terrains_AnimateLast_Holder, 1, wxEXPAND);
	Terrains_Animation_Grid->Add(Terrains_FrameChanged_Holder, 1, wxEXPAND);
	Terrains_Animation_Grid->Add(Terrains_Drawn_Holder, 1, wxEXPAND);

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

	Terrains_TerrainUnitID_Holder->Add(Terrains_TerrainUnitID_Text, 0, wxEXPAND);
	Terrains_TerrainUnitID_Holder1->AddSpacer(15);
	Terrains_TerrainUnitDensity_Holder->Add(Terrains_TerrainUnitDensity_Text, 0, wxEXPAND);
	Terrains_TerrainUnitPriority_Holder->Add(Terrains_TerrainUnitPriority_Text, 0, wxEXPAND);
	for(short loop = 0; loop < TERRAINUNITS; ++loop)
	{
		Terrains_TerrainUnitID_Holder->Add(Terrains_TerrainUnitID[loop], 1, wxEXPAND);
		Terrains_TerrainUnitID_Holder1->Add(Terrains_TerrainUnitID_ComboBox[loop], 1, wxEXPAND);
		Terrains_TerrainUnitDensity_Holder->Add(Terrains_TerrainUnitDensity[loop], 1, wxEXPAND);
		Terrains_TerrainUnitPriority_Holder->Add(Terrains_TerrainUnitPriority[loop], 1, wxEXPAND);
	}
	Terrains_UsedTerrainUnits_Holder->Add(Terrains_UsedTerrainUnits_Text, 0, wxEXPAND);
	Terrains_UsedTerrainUnits_Holder->Add(Terrains_UsedTerrainUnits, 1, wxEXPAND);

	Terrains_NameArea_Holder->Add(Terrains_Enabled_Holder, 3, wxEXPAND);
	Terrains_NameArea_Holder->AddSpacer(5);
	Terrains_NameArea_Holder->Add(Terrains_Random_Holder, 2, wxEXPAND);
	Terrains_NameArea_Holder->AddSpacer(5);
	Terrains_NameArea_Holder->Add(Terrains_Name_Holder, 8, wxEXPAND);
	Terrains_NameArea_Holder->AddSpacer(5);
	Terrains_NameArea_Holder->Add(Terrains_Name2_Holder, 8, wxEXPAND);

	Terrains_Area1_Grid->Add(Terrains_SLP_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_SoundID_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_BlendPriority_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_Area1_Grid->Add(Terrains_BlendType_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_Area1_Grid->Add(Terrains_Colors_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_CliffColors_Holder, 1, wxEXPAND);

	Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitID_Holder, 1, wxEXPAND);
	Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitID_Holder1, 2, wxEXPAND);
	Terrains_TerrainUnits_Holder->AddSpacer(5);
	Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitDensity_Holder, 1, wxEXPAND);
	Terrains_TerrainUnits_Holder->AddSpacer(5);
	Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitPriority_Holder, 1, wxEXPAND);

	Terrains_GridX->Add(Terrains_TerrainReplacementID_Holder, 1, wxEXPAND);
	Terrains_GridX->Add(Terrains_TerrainDimensions_Holder, 1, wxEXPAND);
	Terrains_GridX->AddStretchSpacer(1);
	Terrains_GridX->Add(Terrains_Unknown3_Holder, 1, wxEXPAND);
	Terrains_GridX->Add(Terrains_Unknown1_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_PassableTerrain_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_ImpassableTerrain_Holder, 1, wxEXPAND);

	Terrains_UsedTerrainUnits_Grid->Add(Terrains_UsedTerrainUnits_Holder, 1, wxEXPAND);
	Terrains_SpaceRight->Add(Terrains_GridX, 0, wxEXPAND);
	Terrains_SpaceRight->AddSpacer(5);
	Terrains_SpaceRight->Add(Terrains_UsedTerrainUnits_Grid, 0, wxEXPAND);
	Terrains_SpaceRight->AddSpacer(5);
	Terrains_SpaceRight->Add(Terrains_TerrainUnits_Holder, 0, wxEXPAND);

	Terrains_Borders_Buttons->Add(Terrains_Borders_Copy, 1, wxEXPAND);
	Terrains_Borders_Buttons->Add(Terrains_Borders_Paste, 1, wxEXPAND);
	Terrains_Borders->Add(Terrains_Borders_Search, 0, wxEXPAND);
	Terrains_Borders->Add(Terrains_Borders_Search_R, 0, wxEXPAND);
	Terrains_Borders->AddSpacer(2);
	Terrains_Borders->Add(Terrains_Borders_List, 1, wxEXPAND);
	Terrains_Borders->AddSpacer(2);
	Terrains_Borders->Add(Terrains_Border, 0, wxEXPAND);
	Terrains_Borders->Add(Terrains_Border_ComboBox, 0, wxEXPAND);
	Terrains_Borders->AddSpacer(2);
	Terrains_Borders->Add(Terrains_Borders_Buttons, 0, wxEXPAND);
	Terrains_Borders->AddSpacer(2);
	Terrains_Borders->Add(Terrains_Borders_CopyToTerrains, 0, wxEXPAND);
	Terrains_SpaceLeft->Add(Terrains_Borders, 0, wxEXPAND);
	Terrains_SpaceLeft->AddSpacer(5);
	Terrains_SpaceLeft->Add(Terrains_ElevationGraphics_Holder, 0, wxEXPAND);
	Terrains_GreatSpace->Add(Terrains_SpaceLeft, 3, wxEXPAND);
	Terrains_GreatSpace->AddSpacer(5);
	Terrains_GreatSpace->Add(Terrains_SpaceRight, 5, wxEXPAND);

	Terrains_ScrollSpace->Add(Terrains_NameArea_Holder, 0, wxEXPAND);
	Terrains_ScrollSpace->AddSpacer(5);
	Terrains_ScrollSpace->Add(Terrains_Area1_Grid, 0, wxEXPAND);
	Terrains_ScrollSpace->AddSpacer(5);
	Terrains_ScrollSpace->Add(Terrains_GreatSpace, 0, wxEXPAND);
	Terrains_ScrollSpace->AddSpacer(5);
	Terrains_ScrollSpace->Add(Terrains_Animation_Grid, 0, wxEXPAND);

	Terrains_ScrollArea->Add(Terrains_ScrollSpace, 1, wxEXPAND);
	Terrains_ScrollArea->AddSpacer(5);

	Terrains_Scroller->SetSizer(Terrains_ScrollArea);
	Terrains_Scroller->SetScrollRate(0, 15);

	Terrains_DataArea->AddSpacer(5);
	Terrains_DataArea->Add(Terrains_Scroller, 1, wxEXPAND);
	Terrains_DataArea->AddSpacer(5);

	Terrains_Main->AddSpacer(5);
	Terrains_Main->Add(Terrains_ListArea, 21, wxEXPAND);
	Terrains_Main->AddSpacer(5);
	Terrains_Main->Add(Terrains_DataArea, 65, wxEXPAND);
	Terrains_Main->AddSpacer(5);

	Tab_Terrains->SetSizer(Terrains_Main);

	Connect(Terrains_Terrains_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	Connect(Terrains_Terrains_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	for(short loop = 0; loop < 2; ++loop)
	{
		Connect(Terrains_Terrains_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
		Connect(Terrains_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
	}
	Connect(Terrains_Terrains_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainsSelect));
	Connect(Terrains_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsAdd));
	Connect(Terrains_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsDelete));
	Connect(Terrains_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsCopy));
	Connect(Terrains_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsPaste));

	Terrains_Name->Connect(Terrains_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Terrains), NULL, this);
	Terrains_Name2->Connect(Terrains_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Terrains), NULL, this);
	Terrains_UsedCount->Connect(Terrains_UsedCount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnTerrainCountChange), NULL, this);

	Connect(Terrains_Borders_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderSearch));
	Connect(Terrains_Borders_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderSearch));
	Connect(Terrains_Borders_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderSelect));
	Connect(Terrains_Borders_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderCopy));
	Connect(Terrains_Borders_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderPaste));
	Connect(Terrains_Borders_CopyToTerrains->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderCopyToBuildings));
	Terrains_Border->Connect(Terrains_Border->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Terrains), NULL, this);
	Terrains_Border_ComboBox->Connect(Terrains_Border_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Terrains), NULL, this);
}

void AGE_Frame::OnKillFocus_Terrains(wxFocusEvent &Event)
{
	Event.Skip();
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
	else if(Event.GetId() == Terrains_Border->GetId())
	{
		ListTerrainsBorders();
	}
}

void AGE_Frame::OnUpdateCombo_Terrains(wxCommandEvent &Event)
{
	((AGEComboBox*)Event.GetEventObject())->OnUpdate(Event);
	ListTerrainsBorders();
}
