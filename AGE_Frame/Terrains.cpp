#include "../AGE_Frame.h"

string AGE_Frame::GetTerrainName(int index, bool Filter)
{
	if(dataset->TerrainBlock.Terrains.size() <= index) return "Nonexistent Terrain";
	string Name = "";
	if(Filter)
	{
		short Selection[2];
		for(size_t loop = 0; loop < 2; ++loop)
		Selection[loop] = Terrains_SearchFilters[loop]->GetSelection();

		if(Selection[0] > 1) // Internal name prevents
		for(size_t loop = 0; loop < 2; ++loop)
		{
			switch(Selection[loop])
			{
				case 2: // SLP
					Name += "SLP "+FormatInt(dataset->TerrainBlock.Terrains[index].SLP);
					break;
				case 3: // Enabled
					Name += "E "+FormatInt(dataset->TerrainBlock.Terrains[index].Enabled);
					break;
				case 4: // Random
					Name += "R "+FormatInt(dataset->TerrainBlock.Terrains[index].Random);
					break;
				case 5: // Unknown3
					Name += "U3 "+FormatInt(dataset->TerrainBlock.Terrains[index].Unknown3);
					break;
				case 6: // SoundID
					Name += "S "+FormatInt(dataset->TerrainBlock.Terrains[index].SoundID);
					break;
				case 7: // BlendPriority
					Name += "BP "+FormatInt(dataset->TerrainBlock.Terrains[index].BlendPriority);
					break;
				case 8: // BlendType
					Name += "BT "+FormatInt(dataset->TerrainBlock.Terrains[index].BlendType);
					break;
				case 9: // Colors
					{
						Name += "H"+FormatInt(dataset->TerrainBlock.Terrains[index].Colors[0]);
						Name += " M"+FormatInt(dataset->TerrainBlock.Terrains[index].Colors[1]);
						Name += " L"+FormatInt(dataset->TerrainBlock.Terrains[index].Colors[2]);
					}
					break;
				case 10: // CliffColors
					{
						Name += "LT"+FormatInt(dataset->TerrainBlock.Terrains[index].CliffColors.first);
						Name += " RT"+FormatInt(dataset->TerrainBlock.Terrains[index].CliffColors.second);
					}
					break;
				case 11: // PassableTerrain
					Name += "PT "+FormatInt(dataset->TerrainBlock.Terrains[index].PassableTerrain);
					break;
				case 12: // ImpassableTerrain
					Name += "IT "+FormatInt(dataset->TerrainBlock.Terrains[index].ImpassableTerrain);
					break;
				case 13: // Frame Count
					Name += "FC "+FormatInt(dataset->TerrainBlock.Terrains[index].ElevationGraphics[0].FrameCount);
					break;
				case 14: // Angle Count
					Name += "AC "+FormatInt(dataset->TerrainBlock.Terrains[index].ElevationGraphics[0].AngleCount);
					break;
				case 15: // TerrainToDraw
					Name += "TD "+FormatInt(dataset->TerrainBlock.Terrains[index].TerrainToDraw);
					break;
				case 16: // TerrainDimensions
					Name += "R"+FormatInt(dataset->TerrainBlock.Terrains[index].TerrainDimensions.first);
					Name += " C"+FormatInt(dataset->TerrainBlock.Terrains[index].TerrainDimensions.second);
					break;
				case 17: // NumberOfTerrainUnitsUsed
					Name += "TU "+FormatInt(dataset->TerrainBlock.Terrains[index].NumberOfTerrainUnitsUsed);
					break;
				case 18: // Unknown1
					Name += "U1 "+FormatInt(dataset->TerrainBlock.Terrains[index].Unknown1);
					break;
			}
			Name += ", ";
			if(Selection[loop+1] < 1) break; // Internal name breaks
		}
		if(Selection[0] == 1) goto InternalName;
	}

	if(!dataset->TerrainBlock.Terrains[index].Name.empty())
	{
		return Name + dataset->TerrainBlock.Terrains[index].Name;
	}
InternalName:
	if(!dataset->TerrainBlock.Terrains[index].Name2.empty())
	{
		return Name + dataset->TerrainBlock.Terrains[index].Name2;
	}
	return Name + "New Terrain";
}

void AGE_Frame::OnTerrainsSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTerrains1(false);
}

void AGE_Frame::ListTerrainNumbers()
{
	Terrains_UsedCount->clear();
	Terrains_UsedCount->prepend(&dataset->TerrainBlock.TerrainsUsed2);
	Terrains_UsedCount->prepend(&dataset->TerrainsUsed1);
	Terrains_UsedCount->update();
	Borders_UsedCount->clear();
	Borders_UsedCount->prepend(&dataset->TerrainBlock.BordersUsed);
	Borders_UsedCount->update();
}

void AGE_Frame::OnTerrainCountChange(wxFocusEvent &event)
{
	//event.Skip();
	if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
	uint16_t UsedTerrains = lexical_cast<uint16_t>(((wxTextCtrl*)event.GetEventObject())->GetValue());
	// Resize terrain restrictions
	for(size_t loop = 0; loop < dataset->TerrainRestrictions.size(); ++loop)
	{
		dataset->TerrainRestrictions[loop].PassableBuildableDmgMultiplier.resize(UsedTerrains);
		if(GenieVersion >= genie::GV_AoKA)
		dataset->TerrainRestrictions[loop].TerrainPassGraphics.resize(UsedTerrains);
	}

	wxTimerEvent E;
	OnTerrainRestrictionsTimer(E);
}

void AGE_Frame::ListTerrains1(bool all)
{
	InitTerrains1(all);
	wxTimerEvent E;
	OnTerrainsTimer(E);
	if(all) OnTerrainRestrictionsTerrainTimer(E);
}

void AGE_Frame::ListTerrains2()
{
	InitTerrains2();
	wxTimerEvent E;
	OnTerrainRestrictionsTerrainTimer(E);
}

void AGE_Frame::InitTerrains1(bool all)
{
	searchText = Terrains_Terrains_Search->GetValue().MakeLower();
	excludeText = Terrains_Terrains_Search_R->GetValue().MakeLower();
	for(size_t loop = 0; loop < 2; ++loop)
	useAnd[loop] = Terrains_Terrains_UseAnd[loop]->GetValue();

	Terrains_Terrains_ListV->names.clear();
	Terrains_Terrains_ListV->indexes.clear();
	wxArrayString names;
	if(all) names.Alloc(dataset->TerrainBlock.Terrains.size());

	for(size_t loop = 0; loop < dataset->TerrainBlock.Terrains.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTerrainName(loop, true);
		if(SearchMatches(Name.Lower()))
		{
			Terrains_Terrains_ListV->names.Add(Name);
			Terrains_Terrains_ListV->indexes.push_back(loop);
		}
		if(all) names.Add(" "+FormatInt(loop)+" - "+GetTerrainName(loop));
	}

	for(size_t loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;

	virtualListing(Terrains_Terrains_ListV);
	if(all) FillLists(TerrainComboBoxList, names);
	InitTerrains2();
}

void AGE_Frame::InitTerrains2()
{
	searchText = TerRestrict_Terrains_Search->GetValue().MakeLower();
	excludeText = TerRestrict_Terrains_Search_R->GetValue().MakeLower();

	TerRestrict_Terrains_ListV->names.clear();
	TerRestrict_Terrains_ListV->indexes.clear();

	for(size_t loop = 0; loop < dataset->TerrainRestrictions[0].PassableBuildableDmgMultiplier.size(); ++loop)
	{
        float val = dataset->TerrainRestrictions[TerRestrictIDs[0]].PassableBuildableDmgMultiplier[loop];
		wxString Name = " "+FormatInt(loop)+" - P"+(val > 0 ? "1" : "0")+" B"+(val > 0.05 ? "1" : "0")+" - "+GetTerrainName(loop);
		if(SearchMatches(Name.Lower()))
		{
			TerRestrict_Terrains_ListV->names.Add(Name);
			TerRestrict_Terrains_ListV->indexes.push_back(loop);
		}
	}
	virtualListing(TerRestrict_Terrains_ListV);
}

void AGE_Frame::OnTerrainsSelect(wxCommandEvent &event)
{
    if(!terrainTimer.IsRunning())
        terrainTimer.Start(150);
}

void AGE_Frame::OnTerrainsTimer(wxTimerEvent &event)
{
    terrainTimer.Stop();
	auto selections = Terrains_Terrains_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Terrains_Terrains_ListV, TerrainIDs);

    for(auto &box: uiGroupTerrain) box->clear();

	genie::Terrain * TerrainPointer = NULL;
	for(auto sel = selections; sel--> 0;)
	{
		TerrainPointer = &dataset->TerrainBlock.Terrains[TerrainIDs[sel]];

		if(GenieVersion < genie::GV_SWGB)
		Terrains_Unknown1->prepend(&TerrainPointer->Unknown1);
		Terrains_Enabled->prepend(&TerrainPointer->Enabled);
		Terrains_Random->prepend(&TerrainPointer->Random);
		Terrains_Name->prepend(&TerrainPointer->Name);
		Terrains_Name2->prepend(&TerrainPointer->Name2);
		if(GenieVersion >= genie::GV_AoEB)
		Terrains_SLP->prepend(&TerrainPointer->SLP);
		Terrains_Unknown3->prepend(&TerrainPointer->Unknown3);
		Terrains_SoundID->prepend(&TerrainPointer->SoundID);
		if(GenieVersion >= genie::GV_AoKB)
		{
			Terrains_BlendPriority->prepend(&TerrainPointer->BlendPriority);
			Terrains_BlendType->prepend(&TerrainPointer->BlendType);
		}
		for(size_t loop = 0; loop < 3; ++loop)
		{
			Terrains_Colors[loop]->prepend(&TerrainPointer->Colors[loop]);
		}
		for(size_t loop = 0; loop < Terrains_CliffColors.size(); ++loop)
		Terrains_CliffColors[0]->prepend(&TerrainPointer->CliffColors.first);
		Terrains_CliffColors[1]->prepend(&TerrainPointer->CliffColors.second);
		Terrains_PassableTerrain->prepend(&TerrainPointer->PassableTerrain);
		Terrains_ImpassableTerrain->prepend(&TerrainPointer->ImpassableTerrain);
		Terrains_IsAnimated->prepend(&TerrainPointer->IsAnimated);
		Terrains_AnimationFrames->prepend(&TerrainPointer->AnimationFrames);
		Terrains_PauseFames->prepend(&TerrainPointer->PauseFames);
		Terrains_Interval->prepend(&TerrainPointer->Interval);
		Terrains_PauseBetweenLoops->prepend(&TerrainPointer->PauseBetweenLoops);
		Terrains_Frame->prepend(&TerrainPointer->Frame);
		Terrains_DrawFrame->prepend(&TerrainPointer->DrawFrame);
		Terrains_AnimateLast->prepend(&TerrainPointer->AnimateLast);
		Terrains_FrameChanged->prepend(&TerrainPointer->FrameChanged);
		Terrains_Drawn->prepend(&TerrainPointer->Drawn);
		for(size_t loop = 0, slot = 0; loop < genie::SharedTerrain::TILE_TYPE_COUNT; ++loop)
		{
			Terrains_ElevationGraphics[slot++]->prepend(&TerrainPointer->ElevationGraphics[loop].FrameCount);
			Terrains_ElevationGraphics[slot++]->prepend(&TerrainPointer->ElevationGraphics[loop].AngleCount);
			Terrains_ElevationGraphics[slot++]->prepend(&TerrainPointer->ElevationGraphics[loop].ShapeID);
		}
		Terrains_TerrainReplacementID->prepend(&TerrainPointer->TerrainToDraw);
		Terrains_TerrainDimensions[0]->prepend(&TerrainPointer->TerrainDimensions.first);
		Terrains_TerrainDimensions[1]->prepend(&TerrainPointer->TerrainDimensions.second);
		for(size_t loop = 0; loop < TerrainPointer->TERRAIN_UNITS_SIZE; ++loop)
		{
			Terrains_TerrainUnitID[loop]->prepend(&TerrainPointer->TerrainUnitID[loop]);
			Terrains_TerrainUnitDensity[loop]->prepend(&TerrainPointer->TerrainUnitDensity[loop]);
			Terrains_TerrainUnitPriority[loop]->prepend(&TerrainPointer->TerrainUnitPriority[loop]);
		}
		Terrains_UsedTerrainUnits->prepend(&TerrainPointer->NumberOfTerrainUnitsUsed);
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected terrain: "+lexical_cast<string>(TerrainIDs[0]), 0);

    for(auto &box: uiGroupTerrain) box->update();
    if(NULL != TerrainPointer && !palettes.empty() && !palettes[0].empty())
    {
        genie::Color high = palettes[0][(uint8_t)TerrainPointer->Colors[0]];
        genie::Color med = palettes[0][(uint8_t)TerrainPointer->Colors[1]];
        genie::Color low = palettes[0][(uint8_t)TerrainPointer->Colors[2]];
        genie::Color left = palettes[0][(uint8_t)TerrainPointer->CliffColors.first];
        genie::Color right = palettes[0][(uint8_t)TerrainPointer->CliffColors.second];
        setForeAndBackColors(Terrains_Colors[0], wxColour(high.r, high.g, high.b));
        setForeAndBackColors(Terrains_Colors[1], wxColour(med.r, med.g, med.b));
        setForeAndBackColors(Terrains_Colors[2], wxColour(low.r, low.g, low.b));
        setForeAndBackColors(Terrains_CliffColors[0], wxColour(left.r, left.g, left.b));
        setForeAndBackColors(Terrains_CliffColors[1], wxColour(right.r, right.g, right.b));

        if(DrawTerrain && NULL != slp_window)
        {
            wxString folder = FolderDRS;
            if(UseTXT)
            {
                wxString resname;
                folder.Replace("drs", "terrain\\textures", false);
                if(!wxFileName(resname).FileExists())
                {
                    resname = folder + "\\" + TerrainPointer->Name2 + "_00_color.png";
                }
                if(wxFileName(resname).FileExists())
                {
                    wxImage img(resname, wxBITMAP_TYPE_PNG);
                    if(img.IsOk())
                    {
                        if(!img.HasAlpha()) img.InitAlpha();
                        int half_width = img.GetWidth() / 2;
                        int half_height = img.GetHeight() / 2;
                        wxPoint center(half_width, half_height);
                        wxImage rotated = img.Rotate(0.785398163, center);
                        half_width = rotated.GetWidth() / 2;
                        half_height = rotated.GetHeight() / 2;
                        tileSLP.bitmap = wxBitmap(rotated.Scale(rotated.GetWidth(), half_height));
                        tileSLP.xpos = half_width;
                        tileSLP.ypos = half_height / 2;
                    }
                }
                slp_view->Refresh();
            }
        }
    }

	ListTerrainsBorders();
}

void AGE_Frame::OnTerrainsAdd(wxCommandEvent &event) // Their count is hardcoded.
{
	if(NULL == dataset) return;

	wxBusyCursor WaitCursor;
    if(GameVersion == EV_EF)
	genie::Terrain::setTerrainsSize(++CustomTerrains);
	for(size_t loop = 0; loop < dataset->TerrainBlock.Terrains.size(); ++loop)
	dataset->TerrainBlock.Terrains[loop].setGameVersion(GenieVersion);
	AddToList(dataset->TerrainBlock.Terrains);
	ListTerrains1();
}

void AGE_Frame::OnTerrainsInsert(wxCommandEvent &event) // Their count is hardcoded.
{
	auto selections = Terrains_Terrains_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	ListTerrains1();
}

void AGE_Frame::OnTerrainsDelete(wxCommandEvent &event) // Their count is hardcoded.
{
	auto selections = Terrains_Terrains_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
    if(GameVersion == EV_EF)
	genie::Terrain::setTerrainsSize(CustomTerrains -= TerrainIDs.size());
	DeleteFromList(dataset->TerrainBlock.Terrains, TerrainIDs);
	for(size_t loop = dataset->TerrainBlock.Terrains.size(); loop--> 0;)
	DeleteFromList(dataset->TerrainBlock.Terrains[loop].Borders, TerrainIDs);
	ListTerrains1();
}

void AGE_Frame::OnTerrainsCopy(wxCommandEvent &event)
{
	auto selections = Terrains_Terrains_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TerrainBlock.Terrains, TerrainIDs, copies.Terrain);
	Terrains_Terrains_ListV->SetFocus();
}

void AGE_Frame::OnTerrainsPaste(wxCommandEvent &event)
{
	auto selections = Terrains_Terrains_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TerrainIDs.size(), copies.Terrain.size()))
		{
			PasteToList(dataset->TerrainBlock.Terrains, TerrainIDs, copies.Terrain);
		}
	}
	else
	{
		PasteToListNoResize(dataset->TerrainBlock.Terrains, TerrainIDs[0], copies.Terrain);
	}
	ListTerrains1();
}

void AGE_Frame::OnTerrainsPasteInsert(wxCommandEvent &event)
{
	auto selections = Terrains_Terrains_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->TerrainBlock.Terrains, TerrainIDs[0], copies.Terrain);
	ListTerrains1();
}

void AGE_Frame::OnTerrainsBorderSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTerrainsBorders();
}

void AGE_Frame::ListTerrainsBorders()
{
	searchText = Terrains_Borders_Search->GetValue().MakeLower();
	excludeText = Terrains_Borders_Search_R->GetValue().MakeLower();

	Terrains_Borders_ListV->names.clear();
	Terrains_Borders_ListV->indexes.clear();

	for(size_t loop = 0; loop < dataset->TerrainBlock.Terrains.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" "+GetTerrainName(loop)+" - ";
		Name += lexical_cast<string>(dataset->TerrainBlock.Terrains[TerrainIDs[0]].Borders[loop])+" ";
		Name += GetTerrainBorderName(dataset->TerrainBlock.Terrains[TerrainIDs[0]].Borders[loop]);
		if(SearchMatches(Name.Lower()))
		{
			Terrains_Borders_ListV->names.Add(Name);
			Terrains_Borders_ListV->indexes.push_back(loop);
		}
	}
	virtualListing(Terrains_Borders_ListV);

	wxTimerEvent E;
	OnTerrainsBorderTimer(E);
}

void AGE_Frame::OnTerrainsBorderSelect(wxCommandEvent &event)
{
    if(!terrainBorderTimer.IsRunning())
        terrainBorderTimer.Start(150);
}

void AGE_Frame::OnTerrainsBorderTimer(wxTimerEvent &event)
{
    terrainBorderTimer.Stop();
	auto selections = Terrains_Borders_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Terrains_Borders_ListV, TerBorderIDs);
	Terrains_Border->clear();

	int16_t * BorderPointer;
	for(auto loop = selections; loop--> 0;)
	{
		BorderPointer = &dataset->TerrainBlock.Terrains[TerrainIDs[0]].Borders[TerBorderIDs[loop]];
		Terrains_Border->prepend(BorderPointer);
	}

	Terrains_Border->update();
}

void AGE_Frame::OnTerrainsBorderCopy(wxCommandEvent &event)
{
	auto selections = Terrains_Borders_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TerrainBlock.Terrains[TerrainIDs[0]].Borders, TerBorderIDs, copies.TerBorder);
	Terrains_Borders_ListV->SetFocus();
}

void AGE_Frame::OnTerrainsBorderPaste(wxCommandEvent &event)
{
	auto selections = Terrains_Borders_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TerBorderIDs.size(), copies.TerBorder.size()))
		{
			PasteToListNoGV(dataset->TerrainBlock.Terrains[TerrainIDs[0]].Borders, TerBorderIDs, copies.TerBorder);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TerrainBlock.Terrains[TerrainIDs[0]].Borders, TerBorderIDs[0], copies.TerBorder);
	}
	ListTerrainsBorders();
}

void AGE_Frame::OnTerrainsBorderCopyToBuildings(wxCommandEvent &event)
{
	for(size_t loop=1; loop < TerrainIDs.size(); ++loop)
	{
		dataset->TerrainBlock.Terrains[TerrainIDs[loop]].Borders = dataset->TerrainBlock.Terrains[TerrainIDs[0]].Borders;
	}
}

void AGE_Frame::CreateTerrainControls()
{
	Terrains_Main = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Terrains_Buttons = new wxGridSizer(2, 0, 0);
	Tab_Terrains = new wxPanel(TabBar_Main);
	Terrains_Terrains = new wxStaticBoxSizer(wxVERTICAL, Tab_Terrains, "Terrains");
	Terrains_Terrains_Search = new wxTextCtrl(Tab_Terrains, wxID_ANY);
	Terrains_Terrains_UseAnd[0] = new wxCheckBox(Tab_Terrains, wxID_ANY, "And");
	Terrains_Terrains_Search_R = new wxTextCtrl(Tab_Terrains, wxID_ANY);
	Terrains_Terrains_UseAnd[1] = new wxCheckBox(Tab_Terrains, wxID_ANY, "And");
	for(size_t loop = 0; loop < 2; ++loop)
	{
		Terrains_Terrains_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Terrains_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_Terrains, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	Terrains_Terrains_ListV = new AGEListView(Tab_Terrains, wxSize(200, 100));
	Terrains_UsedCountHolder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_UsedCountText = new wxStaticText(Tab_Terrains, wxID_ANY, " Terrains Used *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_UsedCount = AGETextCtrl::init(CUShort, NULL, this, AGEwindow, Tab_Terrains);
	Terrains_UsedCount->SetToolTip("How many terrains are used\nstarting from the first terrain without gaps");
	Terrains_Add = new wxButton(Tab_Terrains, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Terrains_Delete = new wxButton(Tab_Terrains, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Terrains_Copy = new wxButton(Tab_Terrains, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Terrains_Paste = new wxButton(Tab_Terrains, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));

	Terrains_Scroller = new wxScrolledWindow(Tab_Terrains, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
	Terrains_ScrollSpace = new wxBoxSizer(wxVERTICAL);
	Terrains_NameArea_Holder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Area1_Grid = new wxGridSizer(4, 5, 5);
	Terrains_Enabled_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Enabled1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Enabled_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Enabled", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Enabled = AGETextCtrl::init(CByte, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller, true);
	Terrains_Enabled_CheckBox = new CheckBox_2State(Terrains_Scroller, " Yes", Terrains_Enabled);
	Terrains_Random_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Random_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Random", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Random = AGETextCtrl::init(CByte, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller, true);
	Terrains_Name_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Name_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name = AGETextCtrl::init(CString, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_Name2_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Name2_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " SLP Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name2 = AGETextCtrl::init(CString, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_SLP_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_SLP_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SLP = AGETextCtrl::init(CLong, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_SoundID_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_SoundID_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SoundID = AGETextCtrl::init(CLong, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_SoundID_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_SoundID);
	SoundComboBoxList.push_back(Terrains_SoundID_ComboBox);
	Terrains_BlendPriority_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_BlendPriority_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Blend Priority", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_BlendPriority = AGETextCtrl::init(CLong, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_BlendType_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_BlendType_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Blend Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_BlendType = AGETextCtrl::init(CLong, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_Colors_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Colors_Grid = new wxGridSizer(3, 0, 0);
	Terrains_Colors_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(size_t loop = 0; loop < 3; ++loop)
	Terrains_Colors[loop] = AGETextCtrl::init(CUByte, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_CliffColors_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_CliffColors_Grid = new wxGridSizer(2, 0, 0);
	Terrains_CliffColors_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Cliff Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(size_t loop = 0; loop < Terrains_CliffColors.size(); ++loop)
	Terrains_CliffColors[loop] = AGETextCtrl::init(CUByte, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);

	Terrains_PassableTerrain_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_PassableTerrain_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Passable Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_PassableTerrain = AGETextCtrl::init(CByte, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_PassableTerrain_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_PassableTerrain);
	TerrainComboBoxList.push_back(Terrains_PassableTerrain_ComboBox);
	Terrains_ImpassableTerrain_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_ImpassableTerrain_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Impassable Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_ImpassableTerrain = AGETextCtrl::init(CByte, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_ImpassableTerrain_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_ImpassableTerrain);
	TerrainComboBoxList.push_back(Terrains_ImpassableTerrain_ComboBox);
	Terrains_TerrainReplacementID_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainReplacementID_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain to Draw", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainReplacementID = AGETextCtrl::init(CShort, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_TerrainReplacementID_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainReplacementID);
	TerrainComboBoxList.push_back(Terrains_TerrainReplacementID_ComboBox);
	Terrains_TerrainDimensions_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainDimensions_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Dimensions", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainDimensions[0] = AGETextCtrl::init(CShort, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_TerrainDimensions[1] = AGETextCtrl::init(CShort, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_TerrainDimensions[0]->SetToolTip("Rows");
	Terrains_TerrainDimensions[1]->SetToolTip("Columns");
	Terrains_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Unknown3_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown3 = AGETextCtrl::init(CLong, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_GridX = new wxFlexGridSizer(3, 0, 5);
	Terrains_GridX->AddGrowableCol(0, 1);
	Terrains_GridX->AddGrowableCol(1, 1);
	Terrains_GridX->AddGrowableCol(2, 1);
	Terrains_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Unknown1_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown1 = AGETextCtrl::init(CShort, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);

	Terrains_GreatSpace = new wxBoxSizer(wxHORIZONTAL);
	Terrains_SpaceLeft = new wxBoxSizer(wxVERTICAL);
	Terrains_SpaceRight = new wxBoxSizer(wxVERTICAL);
	Terrains_Borders = new wxStaticBoxSizer(wxVERTICAL, Terrains_Scroller, "Borders");
	Terrains_Borders_Search = new wxTextCtrl(Terrains_Scroller, wxID_ANY);
	Terrains_Borders_Search_R = new wxTextCtrl(Terrains_Scroller, wxID_ANY);
	Terrains_Borders_ListV = new AGEListView(Terrains_Scroller, wxSize(200, 250));
	Terrains_Border = AGETextCtrl::init(CShort, NULL, this, AGEwindow, Terrains_Scroller);
	Terrains_Border_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_Border);
	TerrainBorderComboBoxList.push_back(Terrains_Border_ComboBox);
	Terrains_Borders_Buttons = new wxGridSizer(2, 0, 0);
	Terrains_Borders_Copy = new wxButton(Terrains_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Terrains_Borders_Paste = new wxButton(Terrains_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Terrains_Borders_CopyToTerrains = new wxButton(Terrains_Scroller, wxID_ANY, "Copy all to selected terrains", wxDefaultPosition, wxSize(5, 20));

	Terrains_UsedTerrainUnits_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_UsedTerrainUnits_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Units Used", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_UsedTerrainUnits = AGETextCtrl::init(CShort, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_TerrainUnits_Holder = new wxBoxSizer(wxHORIZONTAL);
	Terrains_TerrainUnitID_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainUnitID_Holder1 = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainUnitDensity_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainUnitPriority_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_TerrainUnitID_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainUnitDensity_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unit Density", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainUnitPriority_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unit Priority *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(size_t loop = 0; loop < TERRAINUNITS; ++loop)
	{
		Terrains_TerrainUnitID[loop] = AGETextCtrl::init(CShort, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller, true);
		Terrains_TerrainUnitID_ComboBox[loop] = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainUnitID[loop]);
		UnitComboBoxList.push_back(Terrains_TerrainUnitID_ComboBox[loop]);
		Terrains_TerrainUnitDensity[loop] = AGETextCtrl::init(CShort, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller, true);
		Terrains_TerrainUnitPriority[loop] = AGETextCtrl::init(CByte, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
		Terrains_TerrainUnitPriority[loop]->SetToolTip("1 prevails, others don't");
	}
	Terrains_ElevationGraphics_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Unknown9_Grid = new wxGridSizer(3, 0, 0);
	Terrains_ElevationGraphics_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Elevation Graphics\n Frames, Animations, Shape index", wxDefaultPosition, wxSize(-1, 30), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(size_t loop = 0; loop < Terrains_ElevationGraphics.size(); ++loop)
	{
		Terrains_ElevationGraphics[loop] = AGETextCtrl::init(CShort, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller, 2);
	}

	Terrains_Animation_Grid = new wxGridSizer(5, 5, 5);
	Terrains_IsAnimated_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_IsAnimated_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Is Animated", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_IsAnimated = AGETextCtrl::init(CByte, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_AnimationFrames_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_AnimationFrames_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Animation Frames *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_AnimationFrames = AGETextCtrl::init(CShort, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_AnimationFrames->SetToolTip("Number of frames to animate through");
	Terrains_PauseFames_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_PauseFames_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Pause Fames *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_PauseFames = AGETextCtrl::init(CShort, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_PauseFames->SetToolTip("Number of frames to pause animation after last frame is drawn");
	Terrains_Interval_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Interval_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Interval *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Interval = AGETextCtrl::init(CFloat, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_Interval->SetToolTip("Time between frames");
	Terrains_PauseBetweenLoops_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_PauseBetweenLoops_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Pause Between Loops *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_PauseBetweenLoops = AGETextCtrl::init(CFloat, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_PauseBetweenLoops->SetToolTip("Time to pause after last frame");
	Terrains_Frame_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Frame_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Frame *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Frame = AGETextCtrl::init(CShort, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_Frame->SetToolTip("The current frame (includes animation and pause frames)");
	Terrains_DrawFrame_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_DrawFrame_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Draw Frame *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_DrawFrame = AGETextCtrl::init(CShort, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_DrawFrame->SetToolTip("The current frame to draw");
	Terrains_AnimateLast_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_AnimateLast_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Animate Last *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_AnimateLast = AGETextCtrl::init(CFloat, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_AnimateLast->SetToolTip("Last time animation frame was changed");
	Terrains_FrameChanged_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_FrameChanged_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Frame Changed *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_FrameChanged = AGETextCtrl::init(CByte, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);
	Terrains_FrameChanged->SetToolTip("Has the Draw Frame changed since terrain was drawn?");
	Terrains_Drawn_Holder = new wxBoxSizer(wxVERTICAL);
	Terrains_Drawn_Text = new wxStaticText(Terrains_Scroller, wxID_ANY, " Drawn", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Drawn = AGETextCtrl::init(CByte, &uiGroupTerrain, this, AGEwindow, Terrains_Scroller);

	for(size_t loop = 0; loop < 2; ++loop)
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
	Terrains_UsedCountHolder->Add(Terrains_UsedCount, 1, wxEXPAND | wxLEFT, 2);

	Terrains_Terrains_Buttons->Add(Terrains_Add, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Delete, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Copy, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Paste, 1, wxEXPAND);

	Terrains_Terrains_Searches[0]->Add(Terrains_Terrains_Search, 1, wxEXPAND);
	Terrains_Terrains_Searches[0]->Add(Terrains_Terrains_UseAnd[0], 0, wxEXPAND | wxLEFT, 2);
	Terrains_Terrains_Searches[1]->Add(Terrains_Terrains_Search_R, 1, wxEXPAND);
	Terrains_Terrains_Searches[1]->Add(Terrains_Terrains_UseAnd[1], 0, wxEXPAND | wxLEFT, 2);
	for(size_t loop = 0; loop < 2; ++loop)
	Terrains_Terrains->Add(Terrains_Terrains_Searches[loop], 0, wxEXPAND);
	for(size_t loop = 0; loop < 2; ++loop)
	Terrains_Terrains->Add(Terrains_SearchFilters[loop], 0, wxEXPAND);
	Terrains_Terrains->Add(Terrains_Terrains_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Terrains_Terrains->Add(Terrains_UsedCountHolder, 0, wxEXPAND);
	Terrains_Terrains->Add(Terrains_Terrains_Buttons, 0, wxEXPAND | wxTOP, 2);

	Terrains_Unknown1_Holder->Add(Terrains_Unknown1_Text, 0, wxEXPAND);
	Terrains_Unknown1_Holder->Add(Terrains_Unknown1, 0, wxEXPAND);
	Terrains_Enabled1_Holder->Add(Terrains_Enabled, 1, wxEXPAND);
	Terrains_Enabled1_Holder->Add(Terrains_Enabled_CheckBox, 1, wxEXPAND | wxLEFT, 2);
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
	for(size_t loop = 0; loop < 3; ++loop)
	Terrains_Colors_Grid->Add(Terrains_Colors[loop], 1, wxEXPAND);
	Terrains_Colors_Holder->Add(Terrains_Colors_Text, 0, wxEXPAND);
	Terrains_Colors_Holder->Add(Terrains_Colors_Grid, 0, wxEXPAND);
	Terrains_CliffColors_Holder->Add(Terrains_CliffColors_Text, 0, wxEXPAND);
	for(size_t loop = 0; loop < Terrains_CliffColors.size(); ++loop)
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
	for(size_t loop = 0; loop < Terrains_ElevationGraphics.size(); ++loop)
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
	for(size_t loop = 0; loop < TERRAINUNITS; ++loop)
	{
		Terrains_TerrainUnitID_Holder->Add(Terrains_TerrainUnitID[loop], 1, wxEXPAND);
		Terrains_TerrainUnitID_Holder1->Add(Terrains_TerrainUnitID_ComboBox[loop], 1, wxEXPAND);
		Terrains_TerrainUnitDensity_Holder->Add(Terrains_TerrainUnitDensity[loop], 1, wxEXPAND);
		Terrains_TerrainUnitPriority_Holder->Add(Terrains_TerrainUnitPriority[loop], 1, wxEXPAND);
	}
	Terrains_UsedTerrainUnits_Holder->Add(Terrains_UsedTerrainUnits_Text, 0, wxEXPAND);
	Terrains_UsedTerrainUnits_Holder->Add(Terrains_UsedTerrainUnits, 0, wxEXPAND);

	Terrains_NameArea_Holder->Add(Terrains_Enabled_Holder, 3, wxEXPAND);
	Terrains_NameArea_Holder->Add(Terrains_Random_Holder, 2, wxEXPAND | wxLEFT, 5);
	Terrains_NameArea_Holder->Add(Terrains_Name_Holder, 8, wxEXPAND | wxLEFT, 5);
	Terrains_NameArea_Holder->Add(Terrains_Name2_Holder, 8, wxEXPAND | wxLEFT, 5);

	Terrains_Area1_Grid->Add(Terrains_SLP_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_SoundID_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_BlendPriority_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_Area1_Grid->Add(Terrains_BlendType_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_Area1_Grid->Add(Terrains_Colors_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_CliffColors_Holder, 1, wxEXPAND);

	Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitID_Holder, 1, wxEXPAND);
	Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitID_Holder1, 2, wxEXPAND);
	Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitDensity_Holder, 1, wxEXPAND | wxLEFT, 5);
	Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitPriority_Holder, 1, wxEXPAND | wxLEFT, 5);

	Terrains_GridX->Add(Terrains_TerrainReplacementID_Holder, 1, wxEXPAND);
	Terrains_GridX->Add(Terrains_TerrainDimensions_Holder, 1, wxEXPAND);
	Terrains_GridX->Add(0, 0);
	Terrains_GridX->Add(Terrains_Unknown3_Holder, 1, wxEXPAND);
	Terrains_GridX->Add(Terrains_Unknown1_Holder, 1, wxEXPAND);
	Terrains_GridX->Add(0, 0);
	Terrains_GridX->Add(Terrains_UsedTerrainUnits_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_PassableTerrain_Holder, 1, wxEXPAND);
	Terrains_Area1_Grid->Add(Terrains_ImpassableTerrain_Holder, 1, wxEXPAND);

	Terrains_SpaceRight->Add(Terrains_GridX, 0, wxEXPAND);
	Terrains_SpaceRight->Add(Terrains_TerrainUnits_Holder, 0, wxEXPAND | wxTOP, 5);

	Terrains_Borders_Buttons->Add(Terrains_Borders_Copy, 1, wxEXPAND);
	Terrains_Borders_Buttons->Add(Terrains_Borders_Paste, 1, wxEXPAND);
	Terrains_Borders->Add(Terrains_Borders_Search, 0, wxEXPAND);
	Terrains_Borders->Add(Terrains_Borders_Search_R, 0, wxEXPAND);
	Terrains_Borders->Add(Terrains_Borders_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Terrains_Borders->Add(Terrains_Border, 0, wxEXPAND);
	Terrains_Borders->Add(Terrains_Border_ComboBox, 0, wxEXPAND | wxBOTTOM, 2);
	Terrains_Borders->Add(Terrains_Borders_Buttons, 0, wxEXPAND);
	Terrains_Borders->Add(Terrains_Borders_CopyToTerrains, 0, wxEXPAND | wxTOP, 2);
	Terrains_SpaceLeft->Add(Terrains_Borders, 0, wxEXPAND);
	Terrains_SpaceLeft->Add(Terrains_ElevationGraphics_Holder, 0, wxEXPAND | wxTOP, 5);
	Terrains_GreatSpace->Add(Terrains_SpaceLeft, 3, wxEXPAND);
	Terrains_GreatSpace->Add(Terrains_SpaceRight, 5, wxEXPAND | wxLEFT, 5);

	Terrains_ScrollSpace->Add(Terrains_NameArea_Holder, 0, wxEXPAND);
	Terrains_ScrollSpace->Add(Terrains_Area1_Grid, 0, wxEXPAND | wxTOP, 5);
	Terrains_ScrollSpace->Add(Terrains_GreatSpace, 0, wxEXPAND | wxTOP, 5);
	Terrains_ScrollSpace->Add(Terrains_Animation_Grid, 0, wxEXPAND | wxTOP, 5);

	Terrains_Scroller->SetSizer(Terrains_ScrollSpace);
	Terrains_Scroller->SetScrollRate(0, 15);

	Terrains_Main->Add(Terrains_Terrains, 21, wxEXPAND | wxALL, 5);
	Terrains_Main->Add(Terrains_Scroller, 65, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

	Tab_Terrains->SetSizer(Terrains_Main);

	Connect(Terrains_Terrains_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	Connect(Terrains_Terrains_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	for(size_t loop = 0; loop < 2; ++loop)
	{
		Connect(Terrains_Terrains_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
		Connect(Terrains_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
	}
	Connect(Terrains_Terrains_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainsSelect));
	Connect(Terrains_Terrains_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainsSelect));
	Connect(Terrains_Terrains_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTerrainsSelect));
	Connect(Terrains_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsAdd));
	Connect(Terrains_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsDelete));
	Connect(Terrains_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsCopy));
	Connect(Terrains_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsPaste));

	Terrains_Name->Connect(Terrains_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Terrains), NULL, this);
	Terrains_Name2->Connect(Terrains_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Terrains), NULL, this);
	Terrains_UsedCount->Connect(Terrains_UsedCount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnTerrainCountChange), NULL, this);

	Connect(Terrains_Borders_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderSearch));
	Connect(Terrains_Borders_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderSearch));
	Connect(Terrains_Borders_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderSelect));
	Connect(Terrains_Borders_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderSelect));
	Connect(Terrains_Borders_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderSelect));
	Connect(Terrains_Borders_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderCopy));
	Connect(Terrains_Borders_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderPaste));
	Connect(Terrains_Borders_CopyToTerrains->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsBorderCopyToBuildings));
	Terrains_Border->Connect(Terrains_Border->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Terrains), NULL, this);
	Terrains_Border_ComboBox->Connect(Terrains_Border_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Terrains), NULL, this);

    terrainTimer.Connect(terrainTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTerrainsTimer), NULL, this);
    terrainBorderTimer.Connect(terrainBorderTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTerrainsBorderTimer), NULL, this);
}

void AGE_Frame::OnKillFocus_Terrains(wxFocusEvent &event)
{
	//event.Skip();
	if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
	if(event.GetId() == Terrains_Name->GetId())
	{
		ListTerrains1();
	}
	else if(event.GetId() == Terrains_Name2->GetId())
	{
		wxTimerEvent E;
		OnTerrainsTimer(E);
	}
	else if(event.GetId() == Terrains_Border->GetId())
	{
		ListTerrainsBorders();
	}
}

void AGE_Frame::OnUpdateCombo_Terrains(wxCommandEvent &event)
{
	((AGEComboBox*)event.GetEventObject())->OnUpdate(event);
	ListTerrainsBorders();
}
