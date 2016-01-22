#include "../AGE_Frame.h"

string AGE_Frame::GetTerrainBorderName(int index)
{
	if(dataset->TerrainBlock.TerrainBorders[index].Name.empty() && dataset->TerrainBlock.TerrainBorders[index].Name2.empty())
		return "Border "+lexical_cast<string>(index);
	return dataset->TerrainBlock.TerrainBorders[index].Name+" - "+dataset->TerrainBlock.TerrainBorders[index].Name2;
}

void AGE_Frame::OnTerrainBordersSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTerrainBorders(false);
}

void AGE_Frame::ListTerrainBorders(bool all)
{
	InitTerrainBorders(all);
	wxTimerEvent E;
	OnTerrainBordersTimer(E);
}

void AGE_Frame::InitTerrainBorders(bool all)
{
	searchText = Borders_Search->GetValue().MakeLower();
	excludeText = Borders_Search_R->GetValue().MakeLower();

	Borders_ListV->names.clear();
	Borders_ListV->indexes.clear();
	wxArrayString names;
	if(all) names.Alloc(dataset->TerrainBlock.TerrainBorders.size());

	for(size_t loop = 0; loop < dataset->TerrainBlock.TerrainBorders.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTerrainBorderName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Borders_ListV->names.Add(Name);
			Borders_ListV->indexes.push_back(loop);
		}
		if(all) names.Add(Name);
	}

	virtualListing(Borders_ListV);
	if(all) FillLists(TerrainBorderComboBoxList, names);
}

void AGE_Frame::OnTerrainBordersSelect(wxCommandEvent &event)
{
    if(!borderTimer.IsRunning())
        borderTimer.Start(150);
}

void AGE_Frame::OnTerrainBordersTimer(wxTimerEvent &event)
{
    borderTimer.Stop();
	auto selections = Borders_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Borders_ListV, BorderIDs);

	for(auto &box: uiGroupBorder) box->clear();

	genie::TerrainBorder * BorderPointer = NULL;
	for(auto sel = selections; sel--> 0;)
	{
		BorderPointer = &dataset->TerrainBlock.TerrainBorders[BorderIDs[sel]];

		Borders_Enabled->prepend(&BorderPointer->Enabled);
		Borders_Random->prepend(&BorderPointer->Random);
		Borders_Name[0]->prepend(&BorderPointer->Name);
		Borders_Name[1]->prepend(&BorderPointer->Name2);
		if(GenieVersion >= genie::GV_AoEB)
		Borders_SLP->prepend(&BorderPointer->SLP);
		Borders_Unknown3->prepend(&BorderPointer->Unknown3);
		Borders_Sound->prepend(&BorderPointer->SoundID);
		for(size_t loop = 0; loop < 3; ++loop)
		{
			Borders_Colors[loop]->prepend(&BorderPointer->Colors[loop]);
		}
		Borders_IsAnimated->prepend(&BorderPointer->IsAnimated);
		Borders_AnimationFrames->prepend(&BorderPointer->AnimationFrames);
		Borders_PauseFames->prepend(&BorderPointer->PauseFames);
		Borders_Interval->prepend(&BorderPointer->Interval);
		Borders_PauseBetweenLoops->prepend(&BorderPointer->PauseBetweenLoops);
		Borders_Frame->prepend(&BorderPointer->Frame);
		Borders_DrawFrame->prepend(&BorderPointer->DrawFrame);
		Borders_AnimateLast->prepend(&BorderPointer->AnimateLast);
		Borders_FrameChanged->prepend(&BorderPointer->FrameChanged);
		Borders_Drawn->prepend(&BorderPointer->Drawn);
		Borders_DrawTile->prepend(&BorderPointer->DrawTile);
		Borders_Terrain->prepend(&BorderPointer->UnderlayTerrain);
		Borders_BorderStyle->prepend(&BorderPointer->BorderStyle);
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected border: "+lexical_cast<string>(BorderIDs[0]), 0);

	for(auto &box: uiGroupBorder) box->update();
    if(NULL != BorderPointer && !palettes.empty() && !palettes[0].empty())
    {
        genie::Color high = palettes[0][(uint8_t)BorderPointer->Colors[0]];
        genie::Color med = palettes[0][(uint8_t)BorderPointer->Colors[1]];
        genie::Color low = palettes[0][(uint8_t)BorderPointer->Colors[2]];
        setForeAndBackColors(Borders_Colors[0], wxColour(high.r, high.g, high.b));
        setForeAndBackColors(Borders_Colors[1], wxColour(med.r, med.g, med.b));
        setForeAndBackColors(Borders_Colors[2], wxColour(low.r, low.g, low.b));
        borderSLP.slpID = BorderPointer->SLP;
    }
    else borderSLP.slpID = -1;
	ListTerrainBorderTileTypes();
}

void AGE_Frame::OnTerrainBordersCopy(wxCommandEvent &event)
{
	auto selections = Borders_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TerrainBlock.TerrainBorders, BorderIDs, copies.TerrainBorder);
	Borders_ListV->SetFocus();
}

void AGE_Frame::OnTerrainBordersPaste(wxCommandEvent &event)
{
	auto selections = Borders_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(BorderIDs.size(), copies.TerrainBorder.size()))
		{
			PasteToList(dataset->TerrainBlock.TerrainBorders, BorderIDs, copies.TerrainBorder);
		}
	}
	else
	{
		PasteToListNoResize(dataset->TerrainBlock.TerrainBorders, BorderIDs[0], copies.TerrainBorder);
	}
	ListTerrainBorders();
}

string AGE_Frame::GetTerrainBorderTileTypeName(int index)
{
    switch(index)
    {
        case 0: return "Flat Tile ";
        case 1: return "Hillside Tile N ";
        case 2: return "Hillside Tile S ";
        case 3: return "Hillside Tile E ";
        case 4: return "Hillside Tile W ";
        case 5: return "Hillside Tile NE ";
        case 6: return "Hillside Tile SE ";
        case 7: return "Hillside Tile NW ";
        case 8: return "Hillside Tile SW ";
        case 9: return "Pit Pair Tile N ";
        case 10: return "Pit Pair Tile S ";
        case 11: return "Pit Pair Tile E ";
        case 12: return "Pit Pair Tile W ";
        case 13: return "Pit Tile N ";
        case 14: return "Pit Tile S ";
        case 15: return "Pit Tile W ";
        case 16: return "Pit Tile E ";
        case 17: return "1:1 Tile A ";
        case 18: return "1:1 Tile B ";
        default: return "Tile Type "+lexical_cast<string>(index)+" ";
    }
}

void AGE_Frame::OnTerrainBorderTileTypeSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTerrainBorderTileTypes();
}

void AGE_Frame::ListTerrainBorderTileTypes()
{
	searchText = Borders_TileTypes_Search->GetValue().MakeLower();
	excludeText = Borders_TileTypes_Search_R->GetValue().MakeLower();

	Borders_TileTypes_ListV->names.clear();
	Borders_TileTypes_ListV->indexes.clear();

	for(size_t loop = 0; loop < dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTerrainBorderTileTypeName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Borders_TileTypes_ListV->names.Add(Name);
			Borders_TileTypes_ListV->indexes.push_back(loop);
		}
	}

	virtualListing(Borders_TileTypes_ListV);

	wxTimerEvent E;
	OnTerrainBorderTileTypeTimer(E);
}

void AGE_Frame::OnTerrainBorderTileTypeSelect(wxCommandEvent &event)
{
    if(!borderTileTypeTimer.IsRunning())
        borderTileTypeTimer.Start(150);
}

void AGE_Frame::OnTerrainBorderTileTypeTimer(wxTimerEvent &event)
{
    borderTileTypeTimer.Stop();
	auto selections = Borders_TileTypes_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Borders_TileTypes_ListV, BorderTileTypeIDs);

    ListTerrainBorderBorderShapes();
}

void AGE_Frame::OnTerrainBorderTileTypeCopy(wxCommandEvent &event)
{
	auto selections = Borders_TileTypes_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders, BorderTileTypeIDs, copies.BorderBorder);
	Borders_TileTypes_ListV->SetFocus();
}

void AGE_Frame::OnTerrainBorderTileTypePaste(wxCommandEvent &event)
{
	auto selections = Borders_TileTypes_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(BorderTileTypeIDs.size(), copies.BorderBorder.size()))
		{
			PasteToListNoGV(dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders, BorderTileTypeIDs, copies.BorderBorder);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders, BorderTileTypeIDs[0], copies.BorderBorder);
	}
	ListTerrainBorderTileTypes();
}

void AGE_Frame::OnTerrainBorderTileTypeCopyToBorders(wxCommandEvent &event)
{
	for(size_t loop=1; loop < BorderIDs.size(); ++loop)
	{
		dataset->TerrainBlock.TerrainBorders[BorderIDs[loop]].Borders = dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders;
	}
}

string AGE_Frame::GetTerrainBorderBorderShapeName(int index)
{
	return "FC "+lexical_cast<string>(dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders[BorderTileTypeIDs[0]][index].FrameCount)
	+", A "+lexical_cast<string>(dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders[BorderTileTypeIDs[0]][index].AngleCount)
	+", SI "+lexical_cast<string>(dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders[BorderTileTypeIDs[0]][index].ShapeID)+" ";
}

void AGE_Frame::OnTerrainBorderBorderShapeSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTerrainBorderBorderShapes();
}

void AGE_Frame::ListTerrainBorderBorderShapes()
{
	searchText = Borders_BorderShapes_Search->GetValue().MakeLower();
	excludeText = Borders_BorderShapes_Search_R->GetValue().MakeLower();

	Borders_BorderShapes_ListV->names.clear();
	Borders_BorderShapes_ListV->indexes.clear();

	for(size_t loop = 0; loop < dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders[BorderTileTypeIDs[0]].size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTerrainBorderBorderShapeName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Borders_BorderShapes_ListV->names.Add(Name);
			Borders_BorderShapes_ListV->indexes.push_back(loop);
		}
	}

	virtualListing(Borders_BorderShapes_ListV);

	wxTimerEvent E;
	OnTerrainBorderBorderShapeTimer(E);
}

void AGE_Frame::OnTerrainBorderBorderShapeSelect(wxCommandEvent &event)
{
    if(!borderBorderShapeTimer.IsRunning())
        borderBorderShapeTimer.Start(150);
}

void AGE_Frame::OnTerrainBorderBorderShapeTimer(wxTimerEvent &event)
{
    borderBorderShapeTimer.Stop();
	auto selections = Borders_BorderShapes_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Borders_BorderShapes_ListV, BorderShapeIDs);

	for(auto &box: uiGroupBorderFrame) box->clear();

	genie::FrameData * FramePointer = NULL;
	for(auto loop = selections; loop--> 0;)
	{
		FramePointer = &dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders[BorderTileTypeIDs[0]][BorderShapeIDs[loop]];

		Borders_FrameID->prepend(&FramePointer->FrameCount);
		Borders_Flag1->prepend(&FramePointer->AngleCount);
		Borders_Flag2->prepend(&FramePointer->ShapeID);
	}
    if(NULL != FramePointer)
        borderSLP.frameID = FramePointer->ShapeID;
    Border_Shape_SLP->Refresh();

	for(auto &box: uiGroupBorderFrame) box->update();
}

void AGE_Frame::OnDrawBorderSLP(wxPaintEvent &event)
{
    wxBufferedPaintDC dc(Border_Shape_SLP);
    dc.Clear();
    if(borderSLP.slpID == -1)
    {
        dc.DrawLabel("No SLP", wxNullBitmap, wxRect(0, 0, 100, 40));
        return;
    }
    if(borderSLP.frameID == -1)
    {
        dc.DrawLabel("U w0t m8", wxNullBitmap, wxRect(0, 0, 100, 40));
        return;
    }
    SLPtoBitMap(&borderSLP);
    if(borderSLP.bitmap.IsOk())
    dc.DrawBitmap(borderSLP.bitmap, 0, 0, true);
}

void AGE_Frame::OnTerrainBorderBorderShapeCopy(wxCommandEvent &event)
{
	auto selections = Borders_BorderShapes_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders[BorderTileTypeIDs[0]], BorderShapeIDs, copies.FrameData);
	Borders_BorderShapes_ListV->SetFocus();
}

void AGE_Frame::OnTerrainBorderBorderShapePaste(wxCommandEvent &event)
{
	auto selections = Borders_BorderShapes_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(BorderShapeIDs.size(), copies.FrameData.size()))
		{
			PasteToList(dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders[BorderTileTypeIDs[0]], BorderShapeIDs, copies.FrameData);
		}
	}
	else
	{
		PasteToListNoResize(dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders[BorderTileTypeIDs[0]], BorderShapeIDs[0], copies.FrameData);
	}
	ListTerrainBorderBorderShapes();
}

void AGE_Frame::OnTerrainBorderBorderShapeCopyToBorders(wxCommandEvent &event)
{
	for(size_t loop=1; loop < BorderTileTypeIDs.size(); ++loop)
	{
		dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders[BorderTileTypeIDs[loop]] = dataset->TerrainBlock.TerrainBorders[BorderIDs[0]].Borders[BorderTileTypeIDs[0]];
	}
}

void AGE_Frame::CreateTerrainBorderControls()
{
	Tab_TerrainBorders = new wxPanel(TabBar_Main);

	Borders_Main = new wxBoxSizer(wxHORIZONTAL);
	Borders_Buttons = new wxGridSizer(2, 0, 0);
	Borders_Borders = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Terrain Borders");
	Borders_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_ListV = new AGEListView(Tab_TerrainBorders, wxSize(200, 220));
	Borders_UsedCountHolder = new wxBoxSizer(wxHORIZONTAL);
	Borders_UsedCountText = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Borders Used *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_UsedCount = AGETextCtrl::init(CUShort, NULL, this, AGEwindow, Tab_TerrainBorders);
	Borders_UsedCount->SetToolTip("How many terrain borders are used\nstarting from the first border without gaps");
	Borders_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Borders_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Borders_DataArea = new wxBoxSizer(wxVERTICAL);
	Borders_DataTopRow = new wxBoxSizer(wxHORIZONTAL);
	Borders_Data1 = new wxGridSizer(4, 5, 5);

	Borders_Enabled_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Enabled1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Borders_Enabled_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Enabled", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Enabled = AGETextCtrl::init(CByte, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders, true);
	Borders_Enabled_CheckBox = new CheckBox_2State(Tab_TerrainBorders, " Yes", Borders_Enabled);
	Borders_Random_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Random_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Random", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Random = AGETextCtrl::init(CByte, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders, true);
	for(size_t loop = 0; loop < 2; ++loop)
	{
		Borders_Name_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		Borders_Name[loop] = AGETextCtrl::init(CString, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders, 13);
	}
	Borders_Name_Text[0] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Name");
	Borders_Name_Text[1] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " SLP Name ");
	Borders_SLP_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_SLP_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_SLP = AGETextCtrl::init(CLong, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_Data2 = new wxGridSizer(4, 5, 5);
	Borders_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Unknown3_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Unknown3 = AGETextCtrl::init(CLong, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_Sound_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Sound_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Sound = AGETextCtrl::init(CLong, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_Colors_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Colors_Grid = new wxGridSizer(3, 0, 0);
	Borders_Colors_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Minimap Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(size_t loop = 0; loop < 3; ++loop)
	Borders_Colors[loop] = AGETextCtrl::init(CUByte, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_DrawTile_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_DrawTile_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Draw Tile", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_DrawTile = AGETextCtrl::init(CShort, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_Terrain_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Terrain_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Underlay Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Terrain = AGETextCtrl::init(CShort, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_Terrain_ComboBox = new ComboBox_Plus1(Tab_TerrainBorders, Borders_Terrain);
	TerrainComboBoxList.push_back(Borders_Terrain_ComboBox);
	Borders_BorderStyle_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_BorderStyle_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Border Style *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderStyle = AGETextCtrl::init(CShort, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_BorderStyle->SetToolTip("This has something to do with all 19 tile types\nMickey's DAT had this removed and\ninstead added one border shape to each 19 tile types");

	Borders_FrameData = new wxBoxSizer(wxHORIZONTAL);
	Borders_Borders_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Tab_TerrainBorders, "Borders");
	Borders_TileTypes = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Tile Types");
	Borders_TileTypes_Buttons = new wxGridSizer(2, 0, 0);
	Borders_TileTypes_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_TileTypes_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_TileTypes_ListV = new AGEListView(Tab_TerrainBorders, wxSize(200, 220));
	TileTypes_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TileTypes_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TileTypes_CopyToBorders = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy all to selected terrain borders", wxDefaultPosition, wxSize(5, 20));
	Borders_BorderShapes = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Border Shapes");
	Borders_BorderShapes_Buttons = new wxGridSizer(2, 0, 0);
	Borders_BorderShapes_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_BorderShapes_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_BorderShapes_ListV = new AGEListView(Tab_TerrainBorders, wxSize(200, 220));
	BorderShapes_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	BorderShapes_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	BorderShapes_CopyToBorders = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy all to selected tile types", wxDefaultPosition, wxSize(5, 20));

	Borders_FrameArea_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_FrameID_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_FrameID_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_FrameID = AGETextCtrl::init(CShort, &uiGroupBorderFrame, this, AGEwindow, Tab_TerrainBorders);
	Borders_Flag1_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Flag1_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Animations", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Flag1 = AGETextCtrl::init(CShort, &uiGroupBorderFrame, this, AGEwindow, Tab_TerrainBorders);
	Borders_Flag2_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Flag2_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Shape (Frame) Index", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Flag2 = AGETextCtrl::init(CShort, &uiGroupBorderFrame, this, AGEwindow, Tab_TerrainBorders);
    Border_Shape_SLP = new wxPanel(Tab_TerrainBorders, wxID_ANY, wxDefaultPosition, wxSize(55, 50));

	Borders_Animation_Grid = new wxGridSizer(5, 5, 5);
	Borders_IsAnimated_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_IsAnimated_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Is Animated", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_IsAnimated = AGETextCtrl::init(CByte, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_AnimationFrames_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_AnimationFrames_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Animation Frames *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_AnimationFrames = AGETextCtrl::init(CShort, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_AnimationFrames->SetToolTip("Number of frames to animate through");
	Borders_PauseFames_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_PauseFames_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Pause Fames *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_PauseFames = AGETextCtrl::init(CShort, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_PauseFames->SetToolTip("Number of frames to pause animation after last frame is drawn");
	Borders_Interval_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Interval_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Interval *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Interval = AGETextCtrl::init(CFloat, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_Interval->SetToolTip("Time between frames");
	Borders_PauseBetweenLoops_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_PauseBetweenLoops_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Pause Between Loops *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_PauseBetweenLoops = AGETextCtrl::init(CFloat, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_PauseBetweenLoops->SetToolTip("Time to pause after last frame");
	Borders_Frame_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Frame_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Frame = AGETextCtrl::init(CShort, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_Frame->SetToolTip("The current frame (includes animation and pause frames)");
	Borders_DrawFrame_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_DrawFrame_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Draw Frame *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_DrawFrame = AGETextCtrl::init(CShort, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_DrawFrame->SetToolTip("The current frame to draw");
	Borders_AnimateLast_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_AnimateLast_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Animate Last *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_AnimateLast = AGETextCtrl::init(CFloat, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_AnimateLast->SetToolTip("Last time animation frame was changed");
	Borders_FrameChanged_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_FrameChanged_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame Changed *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_FrameChanged = AGETextCtrl::init(CByte, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);
	Borders_FrameChanged->SetToolTip("Has the Draw Frame changed since terrain was drawn?");
	Borders_Drawn_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Drawn_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Drawn", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Drawn = AGETextCtrl::init(CByte, &uiGroupBorder, this, AGEwindow, Tab_TerrainBorders);

	for(size_t loop = 0; loop < 2; ++loop)
	{
		Borders_Name_Holder[loop]->Add(Borders_Name_Text[loop], 0, wxEXPAND | wxBOTTOM, 2);
		Borders_Name_Holder[loop]->Add(Borders_Name[loop], 0, wxEXPAND);
	}
	Borders_Enabled1_Holder->Add(Borders_Enabled, 1, wxEXPAND);
	Borders_Enabled1_Holder->Add(Borders_Enabled_CheckBox, 1, wxEXPAND | wxLEFT, 2);
	Borders_Enabled_Holder->Add(Borders_Enabled_Text, 0, wxEXPAND);
	Borders_Enabled_Holder->Add(Borders_Enabled1_Holder, 1, wxEXPAND);
	Borders_Random_Holder->Add(Borders_Random_Text, 0, wxEXPAND);
	Borders_Random_Holder->Add(Borders_Random, 0, wxEXPAND);

	Borders_UsedCountHolder->Add(Borders_UsedCountText, 0, wxEXPAND);
	Borders_UsedCountHolder->Add(Borders_UsedCount, 1, wxEXPAND | wxLEFT, 2);

	Borders_Buttons->Add(Borders_Copy, 1, wxEXPAND);
	Borders_Buttons->Add(Borders_Paste, 1, wxEXPAND);

	Borders_Borders->Add(Borders_Search, 0, wxEXPAND);
	Borders_Borders->Add(Borders_Search_R, 0, wxEXPAND);
	Borders_Borders->Add(Borders_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Borders_Borders->Add(Borders_UsedCountHolder, 0, wxEXPAND);
	Borders_Borders->Add(Borders_Buttons, 0, wxEXPAND | wxTOP, 2);

	Borders_DataTopRow->Add(Borders_Enabled_Holder, 3, wxEXPAND);
	Borders_DataTopRow->Add(Borders_Random_Holder, 2, wxEXPAND | wxLEFT, 5);
	Borders_DataTopRow->Add(Borders_Name_Holder[0], 8, wxEXPAND | wxLEFT, 5);
	Borders_DataTopRow->Add(Borders_Name_Holder[1], 8, wxEXPAND | wxLEFT, 5);

	Borders_SLP_Holder->Add(Borders_SLP_Text, 0, wxEXPAND);
	Borders_SLP_Holder->Add(Borders_SLP, 0, wxEXPAND);
	Borders_Unknown3_Holder->Add(Borders_Unknown3_Text, 0, wxEXPAND);
	Borders_Unknown3_Holder->Add(Borders_Unknown3, 0, wxEXPAND);
	Borders_Sound_Holder->Add(Borders_Sound_Text, 0, wxEXPAND);
	Borders_Sound_Holder->Add(Borders_Sound, 0, wxEXPAND);
	for(size_t loop = 0; loop < 3; ++loop)
	Borders_Colors_Grid->Add(Borders_Colors[loop], 1, wxEXPAND);
	Borders_Colors_Holder->Add(Borders_Colors_Text, 0, wxEXPAND);
	Borders_Colors_Holder->Add(Borders_Colors_Grid, 0, wxEXPAND);
	Borders_DrawTile_Holder->Add(Borders_DrawTile_Text, 0, wxEXPAND);
	Borders_DrawTile_Holder->Add(Borders_DrawTile, 0, wxEXPAND);
	Borders_Terrain_Holder->Add(Borders_Terrain_Text, 0, wxEXPAND);
	Borders_Terrain_Holder->Add(Borders_Terrain, 0, wxEXPAND);
	Borders_Terrain_Holder->Add(Borders_Terrain_ComboBox, 0, wxEXPAND);
	Borders_BorderStyle_Holder->Add(Borders_BorderStyle_Text, 0, wxEXPAND);
	Borders_BorderStyle_Holder->Add(Borders_BorderStyle, 0, wxEXPAND);

	Borders_Data1->Add(Borders_SLP_Holder, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Unknown3_Holder, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Sound_Holder, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Colors_Holder, 1, wxEXPAND);

	Borders_IsAnimated_Holder->Add(Borders_IsAnimated_Text, 0, wxEXPAND);
	Borders_AnimationFrames_Holder->Add(Borders_AnimationFrames_Text, 0, wxEXPAND);
	Borders_PauseFames_Holder->Add(Borders_PauseFames_Text, 0, wxEXPAND);
	Borders_Interval_Holder->Add(Borders_Interval_Text, 0, wxEXPAND);
	Borders_PauseBetweenLoops_Holder->Add(Borders_PauseBetweenLoops_Text, 0, wxEXPAND);
	Borders_Frame_Holder->Add(Borders_Frame_Text, 0, wxEXPAND);
	Borders_DrawFrame_Holder->Add(Borders_DrawFrame_Text, 0, wxEXPAND);
	Borders_AnimateLast_Holder->Add(Borders_AnimateLast_Text, 0, wxEXPAND);
	Borders_FrameChanged_Holder->Add(Borders_FrameChanged_Text, 0, wxEXPAND);
	Borders_Drawn_Holder->Add(Borders_Drawn_Text, 0, wxEXPAND);
	Borders_IsAnimated_Holder->Add(Borders_IsAnimated, 1, wxEXPAND);
	Borders_AnimationFrames_Holder->Add(Borders_AnimationFrames, 1, wxEXPAND);
	Borders_PauseFames_Holder->Add(Borders_PauseFames, 1, wxEXPAND);
	Borders_Interval_Holder->Add(Borders_Interval, 1, wxEXPAND);
	Borders_PauseBetweenLoops_Holder->Add(Borders_PauseBetweenLoops, 1, wxEXPAND);
	Borders_Frame_Holder->Add(Borders_Frame, 1, wxEXPAND);
	Borders_DrawFrame_Holder->Add(Borders_DrawFrame, 1, wxEXPAND);
	Borders_AnimateLast_Holder->Add(Borders_AnimateLast, 1, wxEXPAND);
	Borders_FrameChanged_Holder->Add(Borders_FrameChanged, 1, wxEXPAND);
	Borders_Drawn_Holder->Add(Borders_Drawn, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_IsAnimated_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_AnimationFrames_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_PauseFames_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_Interval_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_PauseBetweenLoops_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_Frame_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_DrawFrame_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_AnimateLast_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_FrameChanged_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_Drawn_Holder, 1, wxEXPAND);

	Borders_TileTypes_Buttons->Add(TileTypes_Copy, 1, wxEXPAND);
	Borders_TileTypes_Buttons->Add(TileTypes_Paste, 1, wxEXPAND);

	Borders_TileTypes->Add(Borders_TileTypes_Search, 0, wxEXPAND);
	Borders_TileTypes->Add(Borders_TileTypes_Search_R, 0, wxEXPAND);
	Borders_TileTypes->Add(Borders_TileTypes_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Borders_TileTypes->Add(Borders_TileTypes_Buttons, 0, wxEXPAND);
	Borders_TileTypes->Add(TileTypes_CopyToBorders, 0, wxEXPAND | wxTOP, 2);

	Borders_BorderShapes_Buttons->Add(BorderShapes_Copy, 1, wxEXPAND);
	Borders_BorderShapes_Buttons->Add(BorderShapes_Paste, 1, wxEXPAND);

	Borders_BorderShapes->Add(Borders_BorderShapes_Search, 0, wxEXPAND);
	Borders_BorderShapes->Add(Borders_BorderShapes_Search_R, 0, wxEXPAND);
	Borders_BorderShapes->Add(Borders_BorderShapes_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Borders_BorderShapes->Add(Borders_BorderShapes_Buttons, 0, wxEXPAND);
	Borders_BorderShapes->Add(BorderShapes_CopyToBorders, 0, wxEXPAND | wxTOP, 2);

	Borders_FrameID_Holder->Add(Borders_FrameID_Text, 0, wxEXPAND);
	Borders_FrameID_Holder->Add(Borders_FrameID, 1, wxEXPAND);
	Borders_Flag1_Holder->Add(Borders_Flag1_Text, 0, wxEXPAND);
	Borders_Flag1_Holder->Add(Borders_Flag1, 1, wxEXPAND);
	Borders_Flag2_Holder->Add(Borders_Flag2_Text, 0, wxEXPAND);
	Borders_Flag2_Holder->Add(Borders_Flag2, 1, wxEXPAND);

	Borders_FrameArea_Holder->Add(Borders_FrameID_Holder, 0, wxEXPAND);
	Borders_FrameArea_Holder->Add(Borders_Flag1_Holder, 0, wxEXPAND | wxTOP, 5);
	Borders_FrameArea_Holder->Add(Borders_Flag2_Holder, 0, wxEXPAND | wxTOP, 5);
	Borders_FrameArea_Holder->Add(Border_Shape_SLP, 1, wxEXPAND | wxTOP, 5);

	Borders_Borders_Holder->Add(Borders_TileTypes, 3, wxEXPAND);
	Borders_Borders_Holder->Add(Borders_BorderShapes, 3, wxEXPAND | wxLEFT, 5);
	Borders_Borders_Holder->Add(Borders_FrameArea_Holder, 2, wxEXPAND | wxLEFT, 5);
	Borders_FrameData->Add(Borders_Borders_Holder, 3, wxEXPAND);
	Borders_FrameData->AddStretchSpacer(1);

	Borders_Data2->Add(Borders_DrawTile_Holder, 1, wxEXPAND);
	Borders_Data2->Add(Borders_Terrain_Holder, 1, wxEXPAND);
	Borders_Data2->Add(Borders_BorderStyle_Holder, 1, wxEXPAND);

	Borders_DataArea->Add(Borders_DataTopRow, 0, wxEXPAND);
	Borders_DataArea->Add(Borders_Data1, 0, wxEXPAND | wxTOP, 5);
	Borders_DataArea->Add(Borders_Data2, 0, wxEXPAND | wxTOP, 5);
	Borders_DataArea->Add(Borders_FrameData, 0, wxEXPAND | wxTOP, 5);
	Borders_DataArea->Add(Borders_Animation_Grid, 0, wxEXPAND | wxTOP, 5);

	Borders_Main->Add(Borders_Borders, 21, wxEXPAND | wxALL, 5);
	Borders_Main->Add(Borders_DataArea, 65, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

	Tab_TerrainBorders->SetSizer(Borders_Main);

	Connect(Borders_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSearch));
	Connect(Borders_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSearch));
	Connect(Borders_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSelect));
	Connect(Borders_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSelect));
	Connect(Borders_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSelect));
	Connect(Borders_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersCopy));
	Connect(Borders_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersPaste));
	Connect(Borders_TileTypes_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderTileTypeSearch));
	Connect(Borders_TileTypes_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderTileTypeSearch));
	Connect(Borders_TileTypes_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderTileTypeSelect));
	Connect(Borders_TileTypes_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderTileTypeSelect));
	Connect(Borders_TileTypes_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderTileTypeSelect));
	Connect(TileTypes_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderTileTypeCopy));
	Connect(TileTypes_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderTileTypePaste));
	Connect(TileTypes_CopyToBorders->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderTileTypeCopyToBorders));
	Connect(Borders_BorderShapes_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderBorderShapeSearch));
	Connect(Borders_BorderShapes_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderBorderShapeSearch));
	Connect(Borders_BorderShapes_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderBorderShapeSelect));
	Connect(Borders_BorderShapes_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderBorderShapeSelect));
	Connect(Borders_BorderShapes_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderBorderShapeSelect));
	Connect(BorderShapes_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderBorderShapeCopy));
	Connect(BorderShapes_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderBorderShapePaste));
	Connect(BorderShapes_CopyToBorders->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderBorderShapeCopyToBorders));

    borderTimer.Connect(borderTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTerrainBordersTimer), NULL, this);
    borderTileTypeTimer.Connect(borderTileTypeTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTerrainBorderTileTypeTimer), NULL, this);
    borderBorderShapeTimer.Connect(borderBorderShapeTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTerrainBorderBorderShapeTimer), NULL, this);
	for(size_t loop = 0; loop < 2; ++loop)
	Borders_Name[loop]->Connect(Borders_Name[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Borders), NULL, this);
	Borders_FrameID->Connect(Borders_FrameID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Borders), NULL, this);
	Borders_Flag1->Connect(Borders_Flag1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Borders), NULL, this);
	Borders_Flag2->Connect(Borders_Flag2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Borders), NULL, this);
    Border_Shape_SLP->Connect(Border_Shape_SLP->GetId(), wxEVT_PAINT, wxPaintEventHandler(AGE_Frame::OnDrawBorderSLP), NULL, this);
    Border_Shape_SLP->Connect(Border_Shape_SLP->GetId(), wxEVT_ERASE_BACKGROUND, wxEraseEventHandler(AGE_Frame::OnGraphicErase), NULL, this);
}

void AGE_Frame::OnKillFocus_Borders(wxFocusEvent &event)
{
	//event.Skip();
	if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
	if(event.GetId() == Borders_Name[0]->GetId() || event.GetId() == Borders_Name[1]->GetId())
	{
		ListTerrainBorders();
	}
	else if(event.GetId() == Borders_FrameID->GetId() || event.GetId() == Borders_Flag1->GetId() || event.GetId() == Borders_Flag2->GetId())
	{
		ListTerrainBorderTileTypes();
	}
}
