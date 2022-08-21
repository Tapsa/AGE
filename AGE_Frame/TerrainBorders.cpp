#include "Common.h"
#include "../AGE_Frame.h"
#include "genie/resource/Color.h"

wxString AGE_Frame::GetTerrainBorderName(int index)
{
    if(dataset->TerrainBlock.TerrainBorders[index].Name.empty() && dataset->TerrainBlock.TerrainBorders[index].Name2.empty())
        return "Border "+lexical_cast<std::string>(index);
    return dataset->TerrainBlock.TerrainBorders[index].Name+" - "+dataset->TerrainBlock.TerrainBorders[index].Name2;
}

void AGE_Frame::OnTerrainBordersSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListTerrainBorders(false);
}

void AGE_Frame::ListTerrainBorders(bool all)
{
    if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
    {
       InitTerrainBlends();
    }
    else
    {
        InitTerrainBorders(all);
        wxCommandEvent e;
        OnTerrainBorderSelect(e);
    }
}

void AGE_Frame::InitTerrainBlends()
{
    InitSearch(Borders_Search->GetValue().MakeLower(), Borders_Search_R->GetValue().MakeLower());

    Borders_ListV->Sweep();

    // Just do dirty work here.
    std::multimap<unsigned, unsigned> blendMap;
    for(size_t loop = 0; loop < dataset->TerrainBlock.Terrains.size(); ++loop)
    {
        blendMap.emplace(dataset->TerrainBlock.Terrains[loop].BlendPriority, loop);
    }

    // Patch up the blend levels every time we sort them.
    size_t level = 0;
    for(auto &entry: blendMap)
    {
        wxString Name = FormatInt(entry.second)+" - "+GetTerrainName(entry.second);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Borders_ListV->names.Add(Name);
            Borders_ListV->indexes.push_back(entry.second);
        }
        dataset->TerrainBlock.Terrains[entry.second].BlendPriority = level++;
    }

    unsigned long cookie;
    size_t first_visible = Borders_ListV->GetVisibleRowsBegin();
    int first_selected = Borders_ListV->GetFirstSelected(cookie);
    size_t name_count = Borders_ListV->names.size();

    Borders_ListV->SetItemCount(name_count);
    if(name_count)
    {
        // Set selections and first visible item.
        if(first_selected == wxNOT_FOUND)
        {
            first_selected = 0;
        }
        Borders_ListV->DeselectAll();
        if(first_selected >= name_count)
        {
            first_selected = name_count - 1;
        }
        Borders_ListV->ScrollToRow(first_visible);
        if(Reselection && BorderIDs.size())
        {
            // Select old indexes again.
            // As the items are not sorted by
            std::map<unsigned, unsigned> listMap;
            for(size_t loop = 0; loop < name_count; ++loop)
            {
                listMap.emplace(Borders_ListV->indexes[loop], loop);
            }
            first_selected = 0;
            for(size_t loop = BorderIDs.size(); loop--> 0;)
            {
                auto it = listMap.find(BorderIDs[loop]);
                if(it != listMap.end())
                {
                    Borders_ListV->Select(it->second, true);
                    first_selected = it->second;
                }
            }
        }
        if(!Borders_ListV->GetSelectedCount())
        {
            Borders_ListV->Select(first_selected, true);
        }
        Borders_ListV->EnsureVisible(first_selected);
        if(How2List != ListMode::SEARCH)
        {
            Borders_ListV->SetFocus();
        }
    }

    How2List = ListMode::SEARCH;
    Borders_ListV->Refresh();
}

void AGE_Frame::InitTerrainBorders(bool all)
{
    InitSearch(Borders_Search->GetValue().MakeLower(), Borders_Search_R->GetValue().MakeLower());

    Borders_ListV->Sweep();
    if(all)
    {
        border_names.Clear();
        border_names.Alloc(1 + dataset->TerrainBlock.TerrainBorders.size());
        border_names.Add("-1 - None");
    }

    for(size_t loop = 0; loop < dataset->TerrainBlock.TerrainBorders.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetTerrainBorderName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Borders_ListV->names.Add(Name);
            Borders_ListV->indexes.push_back(loop);
        }
        if (all)
        {
            border_names.Add(Name);
        }
    }

    RefreshList(Borders_ListV, &BorderIDs);
    if (all)
    {
        for (AGEComboBox *list : TerrainBorderComboBoxList)
        {
            list->Flash();
        }
    }
}

void AGE_Frame::OnTerrainBorderSelect(wxCommandEvent &event)
{
    size_t selections = Borders_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Borders_ListV, BorderIDs);

    if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
        return;

    for (AGETextCtrl *box : uiGroupBorder) box->clear();

    genie::TerrainBorder * BorderPointer = 0;
    for(size_t sel = selections; sel--> 0;)
    {
        BorderPointer = &dataset->TerrainBlock.TerrainBorders[BorderIDs[sel]];

        Borders_Enabled->prepend(&BorderPointer->Enabled);
        Borders_Random->prepend(&BorderPointer->Random);
        Borders_Name[0]->prepend(&BorderPointer->Name);
        Borders_Name[1]->prepend(&BorderPointer->Name2);
        if(GenieVersion >= genie::GV_AoEB)
        Borders_SLP->prepend(&BorderPointer->SLP);
        Borders_ShapePtr->prepend(&BorderPointer->ShapePtr);
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
        Borders_DrawTerrain->prepend(&BorderPointer->DrawTerrain);
        Borders_Terrain->prepend(&BorderPointer->UnderlayTerrain);
        Borders_BorderStyle->prepend(&BorderPointer->BorderStyle);
    }
    SetStatusText(wxString::Format("Selections: %zu    Selected border: %d",
        selections, selections > 0 ? BorderIDs.front() : -1), 0);

    for (AGETextCtrl *box : uiGroupBorder) box->update();
    if(BorderPointer && !palettes.empty() && !palettes.front().empty())
    {
        genie::Color high = palettes.front()[(uint8_t)BorderPointer->Colors[0]];
        genie::Color med = palettes.front()[(uint8_t)BorderPointer->Colors[1]];
        genie::Color low = palettes.front()[(uint8_t)BorderPointer->Colors[2]];
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
    if(!Borders_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TerrainBlock.TerrainBorders, BorderIDs, copies.TerrainBorder);
    Borders_ListV->SetFocus();
}

void AGE_Frame::OnTerrainBordersPaste(wxCommandEvent &event)
{
    if(!Borders_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->TerrainBlock.TerrainBorders, BorderIDs, copies.TerrainBorder, false);
    ListTerrainBorders();
}

void AGE_Frame::OnTerrainBordersMoveUp(wxCommandEvent &event)
{
    size_t selections = Borders_ListV->GetSelectedCount();
    if(!selections) return;

    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Borders_ListV, BorderIDs);
    int32_t lowest = 70000;
    for(size_t sel = 0; sel < selections; ++sel)
    {
        lowest = std::min(lowest, dataset->TerrainBlock.Terrains[BorderIDs[sel]].BlendPriority);
    }
    int32_t newLow = lowest - 1;
    // Patch any terrain found to have same blend level.
    for(size_t loop = 0; loop < dataset->TerrainBlock.Terrains.size(); ++loop)
    {
        if(dataset->TerrainBlock.Terrains[loop].BlendPriority == newLow)
        {
            dataset->TerrainBlock.Terrains[loop].BlendPriority = lowest;
        }
    }
    // Loop through terrains and patch their blend level.
    for(size_t sel = 0; sel < selections; ++sel)
    {
        dataset->TerrainBlock.Terrains[BorderIDs[sel]].BlendPriority = newLow;
    }
    ListTerrainBorders();
}

void AGE_Frame::OnTerrainBordersMoveDown(wxCommandEvent &event)
{
    size_t selections = Borders_ListV->GetSelectedCount();
    if(!selections) return;

    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Borders_ListV, BorderIDs);
    int32_t highest = 0;
    for(size_t sel = 0; sel < selections; ++sel)
    {
        highest = std::max(highest, dataset->TerrainBlock.Terrains[BorderIDs[sel]].BlendPriority);
    }
    int32_t newHigh = highest + 1;
    // Patch any terrain found to have same blend level.
    for(size_t loop = 0; loop < dataset->TerrainBlock.Terrains.size(); ++loop)
    {
        if(dataset->TerrainBlock.Terrains[loop].BlendPriority == newHigh)
        {
            dataset->TerrainBlock.Terrains[loop].BlendPriority = highest;
        }
    }
    // Loop through terrains and patch their blend level.
    for(size_t sel = 0; sel < selections; ++sel)
    {
        dataset->TerrainBlock.Terrains[BorderIDs[sel]].BlendPriority = newHigh;
    }
    ListTerrainBorders();
}

wxString AGE_Frame::GetTerrainBorderTileTypeName(int index)
{
    switch(index)
    {
        case 0: return "Flat Tile";
        case 1: return "Hillside Tile N";
        case 2: return "Hillside Tile S";
        case 3: return "Hillside Tile E";
        case 4: return "Hillside Tile W";
        case 5: return "Hillside Tile NE";
        case 6: return "Hillside Tile SE";
        case 7: return "Hillside Tile NW";
        case 8: return "Hillside Tile SW";
        case 9: return "Pit Pair Tile N";
        case 10: return "Pit Pair Tile S";
        case 11: return "Pit Pair Tile E";
        case 12: return "Pit Pair Tile W";
        case 13: return "Pit Tile N";
        case 14: return "Pit Tile S";
        case 15: return "Pit Tile W";
        case 16: return "Pit Tile E";
        case 17: return "1:1 Tile A";
        case 18: return "1:1 Tile B";
        default: return "Tile Type "+lexical_cast<std::string>(index);
    }
}

void AGE_Frame::OnTerrainBorderTileTypeSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListTerrainBorderTileTypes();
}

void AGE_Frame::ListTerrainBorderTileTypes()
{
    InitSearch(Borders_TileTypes_Search->GetValue().MakeLower(), Borders_TileTypes_Search_R->GetValue().MakeLower());

    Borders_TileTypes_ListV->Sweep();

    if (BorderIDs.size())
    for(size_t loop = 0; loop < dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetTerrainBorderTileTypeName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Borders_TileTypes_ListV->names.Add(Name);
            Borders_TileTypes_ListV->indexes.push_back(loop);
        }
    }

    RefreshList(Borders_TileTypes_ListV, &BorderTileTypeIDs);

    wxCommandEvent e;
    OnTerrainBorderTileTypeSelect(e);
}

void AGE_Frame::OnTerrainBorderTileTypeSelect(wxCommandEvent &event)
{
    size_t selections = Borders_TileTypes_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Borders_TileTypes_ListV, BorderTileTypeIDs);

    ListTerrainBorderBorderShapes();
}

void AGE_Frame::OnTerrainBorderTileTypeCopy(wxCommandEvent &event)
{
    if(!Borders_TileTypes_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders, BorderTileTypeIDs, copies.BorderBorder);
    Borders_TileTypes_ListV->SetFocus();
}

void AGE_Frame::OnTerrainBorderTileTypePaste(wxCommandEvent &event)
{
    if(!Borders_TileTypes_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders, BorderTileTypeIDs, copies.BorderBorder, false);
    ListTerrainBorderTileTypes();
}

void AGE_Frame::OnTerrainBorderTileTypeCopyToBorders(wxCommandEvent &event)
{
    for(size_t loop=1; loop < BorderIDs.size(); ++loop)
    {
        dataset->TerrainBlock.TerrainBorders[BorderIDs[loop]].Borders = dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders;
    }
}

wxString AGE_Frame::GetTerrainBorderBorderShapeName(int index)
{
    return "FC "+lexical_cast<std::string>(dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders[BorderTileTypeIDs.front()][index].FrameCount)
    +", A "+lexical_cast<std::string>(dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders[BorderTileTypeIDs.front()][index].AngleCount)
    +", SI "+lexical_cast<std::string>(dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders[BorderTileTypeIDs.front()][index].ShapeID);
}

void AGE_Frame::OnTerrainBorderBorderShapeSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListTerrainBorderBorderShapes();
}

void AGE_Frame::ListTerrainBorderBorderShapes()
{
    InitSearch(Borders_BorderShapes_Search->GetValue().MakeLower(), Borders_BorderShapes_Search_R->GetValue().MakeLower());

    Borders_BorderShapes_ListV->Sweep();

    if (BorderTileTypeIDs.size())
    for(size_t loop = 0; loop < dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders[BorderTileTypeIDs.front()].size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetTerrainBorderBorderShapeName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Borders_BorderShapes_ListV->names.Add(Name);
            Borders_BorderShapes_ListV->indexes.push_back(loop);
        }
    }

    RefreshList(Borders_BorderShapes_ListV, &BorderShapeIDs);

    wxCommandEvent e;
    OnTerrainBorderBorderShapeSelect(e);
}

void AGE_Frame::OnTerrainBorderBorderShapeSelect(wxCommandEvent &event)
{
    size_t selections = Borders_BorderShapes_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Borders_BorderShapes_ListV, BorderShapeIDs);

    for (AGETextCtrl *box : uiGroupBorderFrame) box->clear();

    genie::FrameData * FramePointer = 0;
    for(size_t loop = selections; loop--> 0;)
    {
        FramePointer = &dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders[BorderTileTypeIDs.front()][BorderShapeIDs[loop]];

        Borders_FrameID->prepend(&FramePointer->FrameCount);
        Borders_Flag1->prepend(&FramePointer->AngleCount);
        Borders_Flag2->prepend(&FramePointer->ShapeID);
    }
    if(FramePointer)
        borderSLP.frameID = FramePointer->ShapeID;
    Border_Shape_SLP->Refresh();

    for (AGETextCtrl *box : uiGroupBorderFrame) box->update();
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
    if(UseDRS && LoadSLP(&borderSLP)) FrameToBitmap(&borderSLP);
    if(borderSLP.bitmap.IsOk())
    dc.DrawBitmap(borderSLP.bitmap, 0, 0, true);
}

void AGE_Frame::OnTerrainBorderBorderShapeCopy(wxCommandEvent &event)
{
    if(!Borders_BorderShapes_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders[BorderTileTypeIDs.front()], BorderShapeIDs, copies.FrameData);
    Borders_BorderShapes_ListV->SetFocus();
}

void AGE_Frame::OnTerrainBorderBorderShapePaste(wxCommandEvent &event)
{
    if(!Borders_BorderShapes_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders[BorderTileTypeIDs.front()], BorderShapeIDs, copies.FrameData, false);
    ListTerrainBorderBorderShapes();
}

void AGE_Frame::OnTerrainBorderBorderShapeCopyToBorders(wxCommandEvent &event)
{
    for(size_t loop=1; loop < BorderTileTypeIDs.size(); ++loop)
    {
        dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders[BorderTileTypeIDs[loop]] = dataset->TerrainBlock.TerrainBorders[BorderIDs.front()].Borders[BorderTileTypeIDs.front()];
    }
}

void AGE_Frame::CreateTerrainBorderControls()
{
    Tab_TerrainBorders = new ATabPage(TabBar_Main);

    Borders_Main = new wxBoxSizer(wxHORIZONTAL);
    Borders_Buttons = new wxGridSizer(2, 0, 0);
    Borders_Borders = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Terrain Borders");
    Borders_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
    Borders_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
    Borders_ListV = new ProperList(Tab_TerrainBorders, ASize(200, 220));
    Borders_UsedCountHolder = new wxBoxSizer(wxHORIZONTAL);
    Borders_UsedCountText = new SolidText(Tab_TerrainBorders, " Borders Used *");
    Borders_UsedCount = new NumberControl(CShort, Tab_TerrainBorders, this, nullptr);
    Borders_UsedCount->SetToolTip("How many terrain borders are used\nstarting from the first border without gaps");
    Borders_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Borders_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Borders_MoveUp = new wxButton(Tab_TerrainBorders, wxID_ANY, "Move Up", wxDefaultPosition, wxSize(10, -1));
    Borders_MoveDown = new wxButton(Tab_TerrainBorders, wxID_ANY, "Move Down", wxDefaultPosition, wxSize(10, -1));
    Borders_DataArea = new wxBoxSizer(wxVERTICAL);
    Borders_DataTopRow = new wxBoxSizer(wxHORIZONTAL);
    Borders_Data1 = new wxBoxSizer(wxHORIZONTAL);
    Borders_Data2 = new wxBoxSizer(wxHORIZONTAL);

    Borders_Enabled_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_Enabled1_Holder = new wxBoxSizer(wxHORIZONTAL);
    Borders_Enabled_Text = new SolidText(Tab_TerrainBorders, " Enabled");
    Borders_Enabled = new NumberControl(CUByte, Tab_TerrainBorders, this, &uiGroupBorder, true, AGETextCtrl::SMALL);
    Borders_Enabled_CheckBox = new LinkedCheckBox(Tab_TerrainBorders, " Yes", Borders_Enabled);
    Borders_Random_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_Random_Text = new SolidText(Tab_TerrainBorders, " Random");
    Borders_Random = new NumberControl(CUByte, Tab_TerrainBorders, this, &uiGroupBorder, true, AGETextCtrl::SMALL);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Borders_Name_Holder[loop] = new wxBoxSizer(wxVERTICAL);
        Borders_Name[loop] = new StringControl(Tab_TerrainBorders, this, &uiGroupBorder, 13, false);
    }
    Borders_Name_Text[0] = new SolidText(Tab_TerrainBorders, " Internal Name");
    Borders_Name_Text[1] = new SolidText(Tab_TerrainBorders, " Texture Filename");
    Borders_SLP_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_SLP_Text = new SolidText(Tab_TerrainBorders, " SLP");
    Borders_SLP = new NumberControl(CLong, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_ShapePtr_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_ShapePtr_Text = new SolidText(Tab_TerrainBorders, " Shape Pointer *");
    Borders_ShapePtr = new NumberControl(CLong, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_ShapePtr->SetToolTip("Assigned using SHP Filename");
    Borders_Sound_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_Sound_Text = new SolidText(Tab_TerrainBorders, " Sound");
    Borders_Sound = new NumberControl(CLong, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_Colors_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_Colors_Grid = new wxGridSizer(3, 0, 0);
    Borders_Colors_Text = new SolidText(Tab_TerrainBorders, " Minimap Colors");
    for(size_t loop = 0; loop < 3; ++loop)
    Borders_Colors[loop] = new NumberControl(CUByte, Tab_TerrainBorders, this, &uiGroupBorder, true, AGETextCtrl::SMALL);
    Borders_DrawTerrain_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_DrawTerrain_Text = new SolidText(Tab_TerrainBorders, " Draw Terrain");
    Borders_DrawTerrain = new NumberControl(CShort, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_Terrain_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_Terrain_Text = new SolidText(Tab_TerrainBorders, " Underlay Terrain *");
    Borders_Terrain = new NumberControl(CShort, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_Terrain->SetToolTip("Used for terrain passability check");
    Borders_Terrain_ComboBox = new LinkedComboBox(Tab_TerrainBorders, Borders_Terrain, &terrain_names);
    TerrainComboBoxList.push_back(Borders_Terrain_ComboBox);
    Borders_BorderStyle_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_BorderStyle_Text = new SolidText(Tab_TerrainBorders, " Border Style *");
    Borders_BorderStyle = new NumberControl(CShort, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_BorderStyle->SetToolTip("This has something to do with all 19 tile types\nMickey's DAT had this removed and\ninstead added one border shape to each 19 tile types");

    Borders_FrameData = new wxBoxSizer(wxHORIZONTAL);
    Borders_Borders_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Tab_TerrainBorders, "Borders");
    Borders_TileTypes = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Tile Types");
    Borders_TileTypes_Buttons = new wxGridSizer(2, 0, 0);
    Borders_TileTypes_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
    Borders_TileTypes_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
    Borders_TileTypes_ListV = new ProperList(Tab_TerrainBorders, ASize(200, 220));
    TileTypes_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    TileTypes_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    TileTypes_CopyToBorders = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy all to selected terrain borders", wxDefaultPosition, wxSize(10, -1));
    Borders_BorderShapes = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Border Shapes");
    Borders_BorderShapes_Buttons = new wxGridSizer(2, 0, 0);
    Borders_BorderShapes_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
    Borders_BorderShapes_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
    Borders_BorderShapes_ListV = new ProperList(Tab_TerrainBorders, ASize(200, 220));
    BorderShapes_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    BorderShapes_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    BorderShapes_CopyToBorders = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy all to selected tile types", wxDefaultPosition, wxSize(10, -1));

    Borders_FrameArea_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_FrameID_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_FrameID_Text = new SolidText(Tab_TerrainBorders, " Frame Count");
    Borders_FrameID = new NumberControl(CShort, Tab_TerrainBorders, this, &uiGroupBorderFrame, false);
    Borders_Flag1_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_Flag1_Text = new SolidText(Tab_TerrainBorders, " Animations");
    Borders_Flag1 = new NumberControl(CShort, Tab_TerrainBorders, this, &uiGroupBorderFrame, false);
    Borders_Flag2_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_Flag2_Text = new SolidText(Tab_TerrainBorders, " Frame Index");
    Borders_Flag2 = new NumberControl(CShort, Tab_TerrainBorders, this, &uiGroupBorderFrame, false);
    Border_Shape_SLP = new APanel(Tab_TerrainBorders, ASize(55, 50));

    Borders_Animation_Grid1 = new wxBoxSizer(wxHORIZONTAL);
    Borders_Animation_Grid2 = new wxBoxSizer(wxHORIZONTAL);
    Borders_IsAnimated_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_IsAnimated_Text = new SolidText(Tab_TerrainBorders, " Is Animated");
    Borders_IsAnimated = new NumberControl(CUByte, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_AnimationFrames_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_AnimationFrames_Text = new SolidText(Tab_TerrainBorders, " Anim Frames *");
    Borders_AnimationFrames = new NumberControl(CShort, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_AnimationFrames->SetToolTip("Number of frames to animate through");
    Borders_PauseFames_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_PauseFames_Text = new SolidText(Tab_TerrainBorders, " Pause Fames *");
    Borders_PauseFames = new NumberControl(CShort, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_PauseFames->SetToolTip("Number of frames to pause animation after last frame is drawn");
    Borders_Interval_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_Interval_Text = new SolidText(Tab_TerrainBorders, " Interval *");
    Borders_Interval = new NumberControl(CFloat, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_Interval->SetToolTip("Time between frames");
    Borders_PauseBetweenLoops_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_PauseBetweenLoops_Text = new SolidText(Tab_TerrainBorders, " Replay Delay *");
    Borders_PauseBetweenLoops = new NumberControl(CFloat, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_PauseBetweenLoops->SetToolTip("Time to pause after last frame");
    Borders_Frame_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_Frame_Text = new SolidText(Tab_TerrainBorders, " Frame *");
    Borders_Frame = new NumberControl(CShort, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_Frame->SetToolTip("The current frame (includes animation and pause frames)");
    Borders_DrawFrame_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_DrawFrame_Text = new SolidText(Tab_TerrainBorders, " Draw Frame *");
    Borders_DrawFrame = new NumberControl(CShort, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_DrawFrame->SetToolTip("The current frame to draw");
    Borders_AnimateLast_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_AnimateLast_Text = new SolidText(Tab_TerrainBorders, " Animate Last *");
    Borders_AnimateLast = new NumberControl(CFloat, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_AnimateLast->SetToolTip("Last time animation frame was changed");
    Borders_FrameChanged_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_FrameChanged_Text = new SolidText(Tab_TerrainBorders, " Frame Changed *");
    Borders_FrameChanged = new NumberControl(CUByte, Tab_TerrainBorders, this, &uiGroupBorder);
    Borders_FrameChanged->SetToolTip("Has the Draw Frame changed since terrain was drawn?");
    Borders_Drawn_Holder = new wxBoxSizer(wxVERTICAL);
    Borders_Drawn_Text = new SolidText(Tab_TerrainBorders, " Drawn");
    Borders_Drawn = new NumberControl(CUByte, Tab_TerrainBorders, this, &uiGroupBorder);

    for(size_t loop = 0; loop < 2; ++loop)
    {
        Borders_Name_Holder[loop]->Add(Borders_Name_Text[loop]);
        Borders_Name_Holder[loop]->Add(Borders_Name[loop]);
    }
    Borders_Enabled1_Holder->Add(Borders_Enabled);
    Borders_Enabled1_Holder->Add(Borders_Enabled_CheckBox, 0, wxLEFT, 2);
    Borders_Enabled_Holder->Add(Borders_Enabled_Text);
    Borders_Enabled_Holder->Add(Borders_Enabled1_Holder);
    Borders_Random_Holder->Add(Borders_Random_Text);
    Borders_Random_Holder->Add(Borders_Random);

    Borders_UsedCountHolder->Add(Borders_UsedCountText);
    Borders_UsedCountHolder->Add(Borders_UsedCount, 1, wxEXPAND | wxLEFT, 2);

    Borders_Buttons->Add(Borders_Copy, 1, wxEXPAND);
    Borders_Buttons->Add(Borders_Paste, 1, wxEXPAND);
    Borders_Buttons->Add(Borders_MoveUp, 1, wxEXPAND);
    Borders_Buttons->Add(Borders_MoveDown, 1, wxEXPAND);

    Borders_Borders->Add(Borders_Search, 0, wxEXPAND);
    Borders_Borders->Add(Borders_Search_R, 0, wxEXPAND);
    Borders_Borders->Add(Borders_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Borders_Borders->Add(Borders_UsedCountHolder, 0, wxEXPAND);
    Borders_Borders->Add(Borders_Buttons, 0, wxEXPAND | wxTOP, 2);

    Borders_DataTopRow->Add(Borders_Enabled_Holder);
    Borders_DataTopRow->Add(Borders_Random_Holder, 0, wxLEFT, 5);
    Borders_DataTopRow->Add(Borders_Name_Holder[0], 0, wxLEFT, 5);
    Borders_DataTopRow->Add(Borders_Name_Holder[1], 0, wxLEFT, 5);

    Borders_SLP_Holder->Add(Borders_SLP_Text);
    Borders_SLP_Holder->Add(Borders_SLP);
    Borders_ShapePtr_Holder->Add(Borders_ShapePtr_Text);
    Borders_ShapePtr_Holder->Add(Borders_ShapePtr);
    Borders_Sound_Holder->Add(Borders_Sound_Text);
    Borders_Sound_Holder->Add(Borders_Sound, 0, wxEXPAND);
    for(size_t loop = 0; loop < 3; ++loop)
    Borders_Colors_Grid->Add(Borders_Colors[loop]);
    Borders_Colors_Holder->Add(Borders_Colors_Text);
    Borders_Colors_Holder->Add(Borders_Colors_Grid);
    Borders_DrawTerrain_Holder->Add(Borders_DrawTerrain_Text);
    Borders_DrawTerrain_Holder->Add(Borders_DrawTerrain);
    Borders_Terrain_Holder->Add(Borders_Terrain_Text);
    Borders_Terrain_Holder->Add(Borders_Terrain, 0, wxEXPAND);
    Borders_Terrain_Holder->Add(Borders_Terrain_ComboBox);
    Borders_BorderStyle_Holder->Add(Borders_BorderStyle_Text);
    Borders_BorderStyle_Holder->Add(Borders_BorderStyle);

    Borders_Data1->Add(Borders_SLP_Holder);
    Borders_Data1->Add(Borders_ShapePtr_Holder, 0, wxLEFT, 5);
    Borders_Data1->Add(Borders_Sound_Holder, 0, wxLEFT, 5);
    Borders_Data1->Add(Borders_Colors_Holder, 0, wxLEFT, 5);

    Borders_IsAnimated_Holder->Add(Borders_IsAnimated_Text);
    Borders_AnimationFrames_Holder->Add(Borders_AnimationFrames_Text);
    Borders_PauseFames_Holder->Add(Borders_PauseFames_Text);
    Borders_Interval_Holder->Add(Borders_Interval_Text);
    Borders_PauseBetweenLoops_Holder->Add(Borders_PauseBetweenLoops_Text);
    Borders_Frame_Holder->Add(Borders_Frame_Text);
    Borders_DrawFrame_Holder->Add(Borders_DrawFrame_Text);
    Borders_AnimateLast_Holder->Add(Borders_AnimateLast_Text);
    Borders_FrameChanged_Holder->Add(Borders_FrameChanged_Text);
    Borders_Drawn_Holder->Add(Borders_Drawn_Text);
    Borders_IsAnimated_Holder->Add(Borders_IsAnimated);
    Borders_AnimationFrames_Holder->Add(Borders_AnimationFrames);
    Borders_PauseFames_Holder->Add(Borders_PauseFames);
    Borders_Interval_Holder->Add(Borders_Interval);
    Borders_PauseBetweenLoops_Holder->Add(Borders_PauseBetweenLoops);
    Borders_Frame_Holder->Add(Borders_Frame);
    Borders_DrawFrame_Holder->Add(Borders_DrawFrame);
    Borders_AnimateLast_Holder->Add(Borders_AnimateLast);
    Borders_FrameChanged_Holder->Add(Borders_FrameChanged);
    Borders_Drawn_Holder->Add(Borders_Drawn);
    Borders_Animation_Grid1->Add(Borders_IsAnimated_Holder);
    Borders_Animation_Grid1->Add(Borders_AnimationFrames_Holder, 0, wxLEFT, 5);
    Borders_Animation_Grid1->Add(Borders_PauseFames_Holder, 0, wxLEFT, 5);
    Borders_Animation_Grid1->Add(Borders_Interval_Holder, 0, wxLEFT, 5);
    Borders_Animation_Grid1->Add(Borders_PauseBetweenLoops_Holder, 0, wxLEFT, 5);
    Borders_Animation_Grid2->Add(Borders_Frame_Holder);
    Borders_Animation_Grid2->Add(Borders_DrawFrame_Holder, 0, wxLEFT, 5);
    Borders_Animation_Grid2->Add(Borders_AnimateLast_Holder, 0, wxLEFT, 5);
    Borders_Animation_Grid2->Add(Borders_FrameChanged_Holder, 0, wxLEFT, 5);
    Borders_Animation_Grid2->Add(Borders_Drawn_Holder, 0, wxLEFT, 5);

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

    Borders_FrameID_Holder->Add(Borders_FrameID_Text);
    Borders_FrameID_Holder->Add(Borders_FrameID);
    Borders_Flag1_Holder->Add(Borders_Flag1_Text);
    Borders_Flag1_Holder->Add(Borders_Flag1);
    Borders_Flag2_Holder->Add(Borders_Flag2_Text);
    Borders_Flag2_Holder->Add(Borders_Flag2);

    Borders_FrameArea_Holder->Add(Borders_FrameID_Holder);
    Borders_FrameArea_Holder->Add(Borders_Flag1_Holder, 0, wxTOP, 5);
    Borders_FrameArea_Holder->Add(Borders_Flag2_Holder, 0, wxTOP, 5);
    Borders_FrameArea_Holder->Add(Border_Shape_SLP, 1, wxEXPAND | wxTOP, 5);

    Borders_Borders_Holder->Add(Borders_TileTypes, 3, wxEXPAND);
    Borders_Borders_Holder->Add(Borders_BorderShapes, 3, wxEXPAND | wxLEFT, 5);
    Borders_Borders_Holder->Add(Borders_FrameArea_Holder, 0, wxLEFT, 5);
    Borders_FrameData->Add(Borders_Borders_Holder, 3, wxEXPAND);
    Borders_FrameData->AddStretchSpacer(1);

    Borders_Data2->Add(Borders_DrawTerrain_Holder);
    Borders_Data2->Add(Borders_Terrain_Holder, 0, wxLEFT, 5);
    Borders_Data2->Add(Borders_BorderStyle_Holder, 0, wxLEFT, 5);

    Borders_DataArea->Add(Borders_DataTopRow);
    Borders_DataArea->Add(Borders_Data1, 0, wxTOP, 5);
    Borders_DataArea->Add(Borders_Data2, 0, wxTOP, 5);
    Borders_DataArea->Add(Borders_FrameData, 0, wxEXPAND | wxTOP, 5);
    Borders_DataArea->Add(Borders_Animation_Grid1, 0, wxTOP, 5);
    Borders_DataArea->Add(Borders_Animation_Grid2, 0, wxTOP, 5);

    Borders_Main->Add(Borders_Borders, 21, wxEXPAND | wxALL, 5);
    Borders_Main->Add(Borders_DataArea, 65, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

    Tab_TerrainBorders->SetSizer(Borders_Main);

    Borders_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainBordersSearch, this);
    Borders_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainBordersSearch, this);
    Borders_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnTerrainBorderSelect, this);
    Borders_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainBordersCopy, this);
    Borders_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainBordersPaste, this);
    Borders_MoveUp->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainBordersMoveUp, this);
    Borders_MoveDown->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainBordersMoveDown, this);
    Borders_TileTypes_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainBorderTileTypeSearch, this);
    Borders_TileTypes_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainBorderTileTypeSearch, this);
    Borders_TileTypes_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnTerrainBorderTileTypeSelect, this);
    TileTypes_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainBorderTileTypeCopy, this);
    TileTypes_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainBorderTileTypePaste, this);
    TileTypes_CopyToBorders->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainBorderTileTypeCopyToBorders, this);
    Borders_BorderShapes_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainBorderBorderShapeSearch, this);
    Borders_BorderShapes_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainBorderBorderShapeSearch, this);
    Borders_BorderShapes_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnTerrainBorderBorderShapeSelect, this);
    BorderShapes_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainBorderBorderShapeCopy, this);
    BorderShapes_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainBorderBorderShapePaste, this);
    BorderShapes_CopyToBorders->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainBorderBorderShapeCopyToBorders, this);

    for(size_t loop = 0; loop < 2; ++loop)
    {
        Borders_Name[loop]->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
        {
            event.Skip();
            if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
            {
                ListTerrainBorders();
            }
        });
        Borders_Name[loop]->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
        {
            static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
            ListTerrainBorders();
        });
    }
    Borders_FrameID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Borders, this);
    Borders_FrameID->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Borders, this);
    Borders_Flag1->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Borders, this);
    Borders_Flag1->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Borders, this);
    Borders_Flag2->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Borders, this);
    Borders_Flag2->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Borders, this);
    Border_Shape_SLP->Bind(wxEVT_PAINT, &AGE_Frame::OnDrawBorderSLP, this);
    Border_Shape_SLP->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&){});
}

void AGE_Frame::OnEnter_Borders(wxCommandEvent &event)
{
    static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
    ListTerrainBorderTileTypes();
}

void AGE_Frame::OnKillFocus_Borders(wxFocusEvent &event)
{
    event.Skip();
    if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
    {
        ListTerrainBorderTileTypes();
    }
}
