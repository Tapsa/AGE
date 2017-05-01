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
                    Name += "FC "+FormatInt(dataset->TerrainBlock.Terrains[index].ElevationGraphics.front().FrameCount);
                    break;
                case 14: // Angle Count
                    Name += "AC "+FormatInt(dataset->TerrainBlock.Terrains[index].ElevationGraphics.front().AngleCount);
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
    event.Skip();
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
    InitSearch(Terrains_Terrains_Search->GetValue().MakeLower(), Terrains_Terrains_Search_R->GetValue().MakeLower());
    SearchAnd = Terrains_Terrains_UseAnd[0]->GetValue();
    ExcludeAnd = Terrains_Terrains_UseAnd[1]->GetValue();

    Terrains_Terrains_ListV->names.clear();
    Terrains_Terrains_ListV->indexes.clear();
    if(all)
    {
        terrain_names.Clear();
        terrain_names.Alloc(1 + dataset->TerrainBlock.Terrains.size());
        terrain_names.Add("-1 - None");
    }

    for(size_t loop = 0; loop < dataset->TerrainBlock.Terrains.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetTerrainName(loop, true);
        if(SearchMatches(Name.Lower()))
        {
            Terrains_Terrains_ListV->names.Add(Name);
            Terrains_Terrains_ListV->indexes.push_back(loop);
        }
        if(all) terrain_names.Add(" "+FormatInt(loop)+" - "+GetTerrainName(loop));
    }

    SearchAnd = ExcludeAnd = false;

    virtualListing(Terrains_Terrains_ListV, &TerrainIDs);
    if(all) FillLists(TerrainComboBoxList, terrain_names);
    InitTerrains2();
}

void AGE_Frame::InitTerrains2()
{
    InitSearch(TerRestrict_Terrains_Search->GetValue().MakeLower(), TerRestrict_Terrains_Search_R->GetValue().MakeLower());

    TerRestrict_Terrains_ListV->names.clear();
    TerRestrict_Terrains_ListV->indexes.clear();

    for(size_t loop = 0; loop < dataset->TerrainRestrictions.front().PassableBuildableDmgMultiplier.size(); ++loop)
    {
        float val = dataset->TerrainRestrictions[TerRestrictIDs.front()].PassableBuildableDmgMultiplier[loop];
        wxString Name = " "+FormatInt(loop)+" - P"+(val > 0 ? "1" : "0")+" B"+(val > 0.05 ? "1" : "0")+" - "+GetTerrainName(loop);
        if(SearchMatches(Name.Lower()))
        {
            TerRestrict_Terrains_ListV->names.Add(Name);
            TerRestrict_Terrains_ListV->indexes.push_back(loop);
        }
    }
    virtualListing(TerRestrict_Terrains_ListV, &TerRestrictTerIDs);
}

void AGE_Frame::OnTerrainsSelect(wxCommandEvent &event)
{
    if(!terrainTimer.IsRunning())
        terrainTimer.Start(150);
}

void AGE_Frame::OnTerrainsTimer(wxTimerEvent&)
{
    terrainTimer.Stop();
    auto selections = Terrains_Terrains_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Terrains_Terrains_ListV, TerrainIDs);

    for(auto &box: uiGroupTerrain) box->clear();

    genie::Terrain * TerrainPointer = 0;
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
    SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected terrain: "+lexical_cast<string>(TerrainIDs.front()), 0);

    for(auto &box: uiGroupTerrain) box->update();
    if(TerrainPointer && !palettes.empty() && !palettes.front().empty())
    {
        genie::Color high = palettes.front()[(uint8_t)TerrainPointer->Colors[0]];
        genie::Color med = palettes.front()[(uint8_t)TerrainPointer->Colors[1]];
        genie::Color low = palettes.front()[(uint8_t)TerrainPointer->Colors[2]];
        genie::Color left = palettes.front()[(uint8_t)TerrainPointer->CliffColors.first];
        genie::Color right = palettes.front()[(uint8_t)TerrainPointer->CliffColors.second];
        setForeAndBackColors(Terrains_Colors[0], wxColour(high.r, high.g, high.b));
        setForeAndBackColors(Terrains_Colors[1], wxColour(med.r, med.g, med.b));
        setForeAndBackColors(Terrains_Colors[2], wxColour(low.r, low.g, low.b));
        setForeAndBackColors(Terrains_CliffColors[0], wxColour(left.r, left.g, left.b));
        setForeAndBackColors(Terrains_CliffColors[1], wxColour(right.r, right.g, right.b));

        if(DrawTerrain && slp_window)
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
            else // Build the image from tile frames
            {
                LoadTerrainFromSLPs(TerrainPointer);
            }
        }
    }

    ListTerrainsBorders();
}

wxThread::ExitCode Loader::Entry()
{
    const vector<genie::Color> *pal = &HostFrame->palettes.front();
    if(pal->empty()) return (wxThread::ExitCode)0;
    size_t TileHalfWidth = HostFrame->dataset->TerrainBlock.TileHalfWidth;
    size_t TileHalfHeight = HostFrame->dataset->TerrainBlock.TileHalfHeight;
    AGE_SLP tileSLP;
    if(0 < TerrainPointer->SLP)
    for(auto &file: HostFrame->datafiles)
    {
        tileSLP.slp = file->getSlpFile(TerrainPointer->SLP);
        if(tileSLP.slp)
        {
            tileSLP.frames = tileSLP.slp->getFrameCount();
            int rows = TerrainPointer->TerrainDimensions.first;
            int cols = TerrainPointer->TerrainDimensions.second;
            size_t wwidth = (rows + cols) * TileHalfWidth;
            size_t wheight = (rows + cols) * TileHalfHeight;
            size_t warea = wwidth * wheight;
            vector<uint8_t> wrgbdata(warea * 4, 0);

            pair<size_t, size_t> corners[rows * cols];
            for(int c = 0; c < cols; ++c)
            for(int r = 0; r < rows; ++r)
            {
                int i = rows * c + r;
                corners[i].first = (r + c) * TileHalfWidth;
                corners[i].second = (rows - r + c - 1) * TileHalfHeight;
            }

            for(size_t f = 0; f < tileSLP.frames && f < rows * cols; ++f)
            {
                genie::SlpFramePtr frame;
                try
                {
                    frame = tileSLP.slp->getFrame(f);
                }
                catch(out_of_range){}
                if(frame)
                {
                    int width = frame->getWidth();
                    int height = frame->getHeight();
                    uint8_t *val = wrgbdata.data() + (3 * (wwidth * corners[f].second + corners[f].first));
                    uint8_t *alpha = wrgbdata.data() + (3 * warea) + (wwidth * corners[f].second + corners[f].first);
                    const genie::SlpFrameData *imgdata = &frame->img_data;
                    for(int h = 0; h < height; ++h)
                    {
                        for(int w = 0; w < width; ++w)
                        {
                            int i = width * h + w;
                            genie::Color rgba = (*pal)[imgdata->pixel_indexes[i]];
                            if(*alpha == 0)
                            {
                                *val++ = rgba.r;
                                *val++ = rgba.g;
                                *val++ = rgba.b;
                                *alpha++ = imgdata->alpha_channel[i];
                            }
                            else
                            {
                                val += 3;
                                ++alpha;
                            }
                        }
                        val += 3 * (wwidth - width);
                        alpha += wwidth - width;
                    }
                }
            }
            tileSLP.xpos = wwidth / 2;
            tileSLP.ypos = wheight / 2;
            unsigned char *pic = (unsigned char*)wrgbdata.data();
            unsigned char *trans = pic + warea * 3;
            tileSLP.bitmap = wxBitmap(wxImage(wwidth, wheight, pic, trans, true), 24);
            break;
        }
    }
    HostFrame->tileSLP = tileSLP;
    return (wxThread::ExitCode)0;
}

Loader::~Loader()
{
    wxCriticalSectionLocker enter(HostFrame->TerrainLoaderCS);
    HostFrame->TerrainLoader = 0;
    if(HostFrame->slp_window) HostFrame->slp_view->Refresh();
}

void AGE_Frame::OnTerrainsAdd(wxCommandEvent &event) // Their count is hardcoded.
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    genie::Terrain::setTerrainCount(++CustomTerrains);
    for(size_t loop = 0; loop < dataset->TerrainBlock.Terrains.size(); ++loop)
    dataset->TerrainBlock.Terrains[loop].setGameVersion(GenieVersion);
    AddToList(dataset->TerrainBlock.Terrains);
    ListTerrains1();
}

void AGE_Frame::OnTerrainsDelete(wxCommandEvent &event) // Their count is hardcoded.
{
    if(!Terrains_Terrains_ListV->GetSelectedItemCount()) return;

    wxBusyCursor WaitCursor;
    genie::Terrain::setTerrainCount(CustomTerrains -= TerrainIDs.size());
    DeleteFromList(dataset->TerrainBlock.Terrains, TerrainIDs);
    for(size_t loop = dataset->TerrainBlock.Terrains.size(); loop--> 0;)
    DeleteFromList(dataset->TerrainBlock.Terrains[loop].Borders, TerrainIDs);
    ListTerrains1();
}

void AGE_Frame::OnTerrainsCopy(wxCommandEvent &event)
{
    if(!Terrains_Terrains_ListV->GetSelectedItemCount()) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TerrainBlock.Terrains, TerrainIDs, copies.Terrain);
    Terrains_Terrains_ListV->SetFocus();
}

void AGE_Frame::OnTerrainsPaste(wxCommandEvent &event)
{
    if(!Terrains_Terrains_ListV->GetSelectedItemCount()) return;

    wxBusyCursor WaitCursor;
    genie::Terrain::setTerrainCount(ResizeTerrains ? CustomTerrains : 0); // Since it is static variable.
    PasteToList(dataset->TerrainBlock.Terrains, TerrainIDs, copies.Terrain, false);
    ListTerrains1();
}

void AGE_Frame::OnTerrainsBorderSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTerrainsBorders();
}

void AGE_Frame::ListTerrainsBorders()
{
    InitSearch(Terrains_Borders_Search->GetValue().MakeLower(), Terrains_Borders_Search_R->GetValue().MakeLower());

    Terrains_Borders_ListV->names.clear();
    Terrains_Borders_ListV->indexes.clear();

    for(size_t loop = 0; loop < dataset->TerrainBlock.Terrains.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" "+GetTerrainName(loop)+" - ";
        Name += lexical_cast<string>(dataset->TerrainBlock.Terrains[TerrainIDs.front()].Borders[loop])+" ";
        Name += GetTerrainBorderName(dataset->TerrainBlock.Terrains[TerrainIDs.front()].Borders[loop]);
        if(SearchMatches(Name.Lower()))
        {
            Terrains_Borders_ListV->names.Add(Name);
            Terrains_Borders_ListV->indexes.push_back(loop);
        }
    }
    virtualListing(Terrains_Borders_ListV, &TerBorderIDs);

    wxTimerEvent E;
    OnTerrainsBorderTimer(E);
}

void AGE_Frame::OnTerrainsBorderSelect(wxCommandEvent &event)
{
    if(!terrainBorderTimer.IsRunning())
        terrainBorderTimer.Start(150);
}

void AGE_Frame::OnTerrainsBorderTimer(wxTimerEvent&)
{
    terrainBorderTimer.Stop();
    auto selections = Terrains_Borders_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Terrains_Borders_ListV, TerBorderIDs);
    Terrains_Border->clear();

    int16_t * BorderPointer;
    for(auto loop = selections; loop--> 0;)
    {
        BorderPointer = &dataset->TerrainBlock.Terrains[TerrainIDs.front()].Borders[TerBorderIDs[loop]];
        Terrains_Border->prepend(BorderPointer);
    }

    Terrains_Border->update();
}

void AGE_Frame::OnTerrainsBorderCopy(wxCommandEvent &event)
{
    auto selections = Terrains_Borders_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TerrainBlock.Terrains[TerrainIDs.front()].Borders, TerBorderIDs, copies.TerBorder);
    Terrains_Borders_ListV->SetFocus();
}

void AGE_Frame::OnTerrainsBorderPaste(wxCommandEvent &event)
{
    auto selections = Terrains_Borders_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TerrainBlock.Terrains[TerrainIDs.front()].Borders, TerBorderIDs, copies.TerBorder);
    ListTerrainsBorders();
}

void AGE_Frame::OnTerrainsBorderCopyToBuildings(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TerrainIDs.size(); ++loop)
    {
        dataset->TerrainBlock.Terrains[TerrainIDs[loop]].Borders = dataset->TerrainBlock.Terrains[TerrainIDs.front()].Borders;
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
        Terrains_SearchFilters[loop] = new AGEODComboBox(Tab_Terrains);
    }
    Terrains_Terrains_ListV = new AGEListView(Tab_Terrains, wxSize(200, 100));
    Terrains_UsedCountHolder = new wxBoxSizer(wxHORIZONTAL);
    Terrains_UsedCountText = new SolidText(Tab_Terrains, " Terrains Used *");
    Terrains_UsedCount = AGETextCtrl::init(CUShort, NULL, this, &popUp, Tab_Terrains);
    Terrains_UsedCount->SetToolTip("How many terrains are used\nstarting from the first terrain without gaps");
    Terrains_Add = new wxButton(Tab_Terrains, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Terrains_Delete = new wxButton(Tab_Terrains, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Terrains_Copy = new wxButton(Tab_Terrains, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Terrains_Paste = new wxButton(Tab_Terrains, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));

    Terrains_Scroller = new wxScrolled<wxPanel>(Tab_Terrains, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
    Terrains_ScrollSpace = new wxBoxSizer(wxVERTICAL);
    Terrains_NameArea_Holder = new wxBoxSizer(wxHORIZONTAL);
    Terrains_Area1_Grid = new wxBoxSizer(wxHORIZONTAL);
    Terrains_Area2_Grid = new wxBoxSizer(wxHORIZONTAL);
    Terrains_Enabled_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Enabled1_Holder = new wxBoxSizer(wxHORIZONTAL);
    Terrains_Enabled_Text = new SolidText(Terrains_Scroller, " Enabled");
    Terrains_Enabled = AGETextCtrl::init(CByte, &uiGroupTerrain, this, &popUp, Terrains_Scroller, AGETextCtrl::SMALL);
    Terrains_Enabled_CheckBox = new CheckBox_2State(Terrains_Scroller, " Yes", Terrains_Enabled);
    Terrains_Random_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Random_Text = new SolidText(Terrains_Scroller, " Random");
    Terrains_Random = AGETextCtrl::init(CByte, &uiGroupTerrain, this, &popUp, Terrains_Scroller, AGETextCtrl::SMALL);
    Terrains_Name_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Name_Text = new SolidText(Terrains_Scroller, " Name");
    Terrains_Name = AGETextCtrl::init(CString, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_Name2_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Name2_Text = new SolidText(Terrains_Scroller, " SLP Name");
    Terrains_Name2 = AGETextCtrl::init(CString, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_SLP_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_SLP_Text = new SolidText(Terrains_Scroller, " SLP");
    Terrains_SLP = AGETextCtrl::init(CLong, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_SoundID_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_SoundID_Text = new SolidText(Terrains_Scroller, " Sound");
    Terrains_SoundID = AGETextCtrl::init(CLong, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_SoundID_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_SoundID, &sound_names);
    SoundComboBoxList.push_back(Terrains_SoundID_ComboBox);
    Terrains_BlendPriority_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_BlendPriority_Text = new SolidText(Terrains_Scroller, " Blend Level");
    Terrains_BlendPriority = AGETextCtrl::init(CLong, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_BlendType_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_BlendType_Text = new SolidText(Terrains_Scroller, " Blend Class");
    Terrains_BlendType = AGETextCtrl::init(CLong, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_Colors_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Colors_Grid = new wxGridSizer(3, 0, 0);
    Terrains_Colors_Text = new SolidText(Terrains_Scroller, " Minimap Colors");
    for(size_t loop = 0; loop < 3; ++loop)
    Terrains_Colors[loop] = AGETextCtrl::init(CUByte, &uiGroupTerrain, this, &popUp, Terrains_Scroller, AGETextCtrl::SMALL);
    Terrains_CliffColors_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_CliffColors_Grid = new wxGridSizer(2, 0, 0);
    Terrains_CliffColors_Text = new SolidText(Terrains_Scroller, " Minimap Cliff Colors");
    for(size_t loop = 0; loop < Terrains_CliffColors.size(); ++loop)
    Terrains_CliffColors[loop] = AGETextCtrl::init(CUByte, &uiGroupTerrain, this, &popUp, Terrains_Scroller, AGETextCtrl::SMALL);

    Terrains_PassableTerrain_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_PassableTerrain_Text = new SolidText(Terrains_Scroller, " Passable Terrain");
    Terrains_PassableTerrain = AGETextCtrl::init(CByte, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_PassableTerrain_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_PassableTerrain, &terrain_names);
    TerrainComboBoxList.push_back(Terrains_PassableTerrain_ComboBox);
    Terrains_ImpassableTerrain_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_ImpassableTerrain_Text = new SolidText(Terrains_Scroller, " Impassable Terrain");
    Terrains_ImpassableTerrain = AGETextCtrl::init(CByte, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_ImpassableTerrain_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_ImpassableTerrain, &terrain_names);
    TerrainComboBoxList.push_back(Terrains_ImpassableTerrain_ComboBox);
    Terrains_TerrainReplacementID_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainReplacementID_Text = new SolidText(Terrains_Scroller, " Terrain to Draw");
    Terrains_TerrainReplacementID = AGETextCtrl::init(CShort, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_TerrainReplacementID_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainReplacementID, &terrain_names);
    TerrainComboBoxList.push_back(Terrains_TerrainReplacementID_ComboBox);
    Terrains_TerrainDimensions_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainDimensions_Text = new SolidText(Terrains_Scroller, " Terrain Dimensions");
    Terrains_TerrainDimensions[0] = AGETextCtrl::init(CShort, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_TerrainDimensions[1] = AGETextCtrl::init(CShort, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_TerrainDimensions[0]->SetToolTip("Rows");
    Terrains_TerrainDimensions[1]->SetToolTip("Columns");
    Terrains_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Unknown3_Text = new SolidText(Terrains_Scroller, " Unknown Pointer");
    Terrains_Unknown3 = AGETextCtrl::init(CLong, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_GridX1 = new wxBoxSizer(wxHORIZONTAL);
    Terrains_GridX2 = new wxBoxSizer(wxHORIZONTAL);
    Terrains_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Unknown1_Text = new SolidText(Terrains_Scroller, " Unknown 1");
    Terrains_Unknown1 = AGETextCtrl::init(CShort, &uiGroupTerrain, this, &popUp, Terrains_Scroller);

    Terrains_GreatSpace = new wxBoxSizer(wxHORIZONTAL);
    Terrains_SpaceLeft = new wxBoxSizer(wxVERTICAL);
    Terrains_SpaceRight = new wxBoxSizer(wxVERTICAL);
    Terrains_Borders = new wxStaticBoxSizer(wxVERTICAL, Terrains_Scroller, "Borders");
    Terrains_Borders_Search = new wxTextCtrl(Terrains_Scroller, wxID_ANY);
    Terrains_Borders_Search_R = new wxTextCtrl(Terrains_Scroller, wxID_ANY);
    Terrains_Borders_ListV = new AGEListView(Terrains_Scroller, wxSize(200, 250));
    Terrains_Border = AGETextCtrl::init(CShort, NULL, this, &popUp, Terrains_Scroller);
    Terrains_Border_ComboBox = new ComboBox_Plus1(Terrains_Scroller, Terrains_Border, &border_names);
    TerrainBorderComboBoxList.push_back(Terrains_Border_ComboBox);
    Terrains_Borders_Buttons = new wxGridSizer(2, 0, 0);
    Terrains_Borders_Copy = new wxButton(Terrains_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Terrains_Borders_Paste = new wxButton(Terrains_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Terrains_Borders_CopyToTerrains = new wxButton(Terrains_Scroller, wxID_ANY, "Copy all to selected terrains", wxDefaultPosition, wxSize(10, -1));

    Terrains_UsedTerrainUnits_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_UsedTerrainUnits_Text = new SolidText(Terrains_Scroller, " Terrain Units Used");
    Terrains_UsedTerrainUnits = AGETextCtrl::init(CShort, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_TerrainUnits_Holder = new wxBoxSizer(wxHORIZONTAL);
    Terrains_TerrainUnitID_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainUnitID_Holder1 = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainUnitDensity_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainUnitPriority_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainUnitID_Text = new SolidText(Terrains_Scroller, " Terrain Unit");
    Terrains_TerrainUnitDensity_Text = new SolidText(Terrains_Scroller, " Unit Density");
    Terrains_TerrainUnitPriority_Text = new SolidText(Terrains_Scroller, " Placement *");
    for(size_t loop = 0; loop < TERRAINUNITS; ++loop)
    {
        Terrains_TerrainUnitID[loop] = AGETextCtrl::init(CShort, &uiGroupTerrain, this, &popUp, Terrains_Scroller, AGETextCtrl::SMALL);
        Terrains_TerrainUnitID_ComboBox[loop] = new ComboBox_Plus1(Terrains_Scroller, Terrains_TerrainUnitID[loop], &unit_names);
        UnitComboBoxList.push_back(Terrains_TerrainUnitID_ComboBox[loop]);
        Terrains_TerrainUnitDensity[loop] = AGETextCtrl::init(CShort, &uiGroupTerrain, this, &popUp, Terrains_Scroller, AGETextCtrl::SMALL);
        Terrains_TerrainUnitPriority[loop] = AGETextCtrl::init(CByte, &uiGroupTerrain, this, &popUp, Terrains_Scroller, AGETextCtrl::SMALL);
        Terrains_TerrainUnitPriority[loop]->SetToolTip("1 prevails, others don't");
    }
    Terrains_ElevationGraphics_Holder = new wxBoxSizer(wxVERTICAL);
    Terrain_TileGraphics_Sizer = new wxBoxSizer(wxVERTICAL);
    Terrains_ElevationGraphics_Text = new SolidText(Terrains_Scroller, " Tile Graphics: flat, 2 x 8 elevation, 2 x 1:1\n Frame Count, Animations, Shape (Frame) Index");
    for(auto &sizer: Terrain_TileGraphics_Sizers)
    sizer = new wxBoxSizer(wxHORIZONTAL);
    for(auto &box: Terrains_ElevationGraphics)
    box = AGETextCtrl::init(CShort, &uiGroupTerrain, this, &popUp, Terrains_Scroller, AGETextCtrl::MEDIUM);

    Terrains_Animation_Grid1 = new wxBoxSizer(wxHORIZONTAL);
    Terrains_Animation_Grid2 = new wxBoxSizer(wxHORIZONTAL);
    Terrains_IsAnimated_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_IsAnimated_Text = new SolidText(Terrains_Scroller, " Is Animated");
    Terrains_IsAnimated = AGETextCtrl::init(CByte, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_AnimationFrames_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_AnimationFrames_Text = new SolidText(Terrains_Scroller, " Animation Frames *");
    Terrains_AnimationFrames = AGETextCtrl::init(CShort, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_AnimationFrames->SetToolTip("Number of frames to animate through");
    Terrains_PauseFames_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_PauseFames_Text = new SolidText(Terrains_Scroller, " Pause Fames *");
    Terrains_PauseFames = AGETextCtrl::init(CShort, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_PauseFames->SetToolTip("Number of frames to pause animation after last frame is drawn");
    Terrains_Interval_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Interval_Text = new SolidText(Terrains_Scroller, " Interval *");
    Terrains_Interval = AGETextCtrl::init(CFloat, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_Interval->SetToolTip("Time between frames");
    Terrains_PauseBetweenLoops_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_PauseBetweenLoops_Text = new SolidText(Terrains_Scroller, " Replay Delay *");
    Terrains_PauseBetweenLoops = AGETextCtrl::init(CFloat, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_PauseBetweenLoops->SetToolTip("Time to pause after last frame");
    Terrains_Frame_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Frame_Text = new SolidText(Terrains_Scroller, " Frame *");
    Terrains_Frame = AGETextCtrl::init(CShort, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_Frame->SetToolTip("The current frame (includes animation and pause frames)");
    Terrains_DrawFrame_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_DrawFrame_Text = new SolidText(Terrains_Scroller, " Draw Frame *");
    Terrains_DrawFrame = AGETextCtrl::init(CShort, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_DrawFrame->SetToolTip("The current frame to draw");
    Terrains_AnimateLast_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_AnimateLast_Text = new SolidText(Terrains_Scroller, " Animate Last *");
    Terrains_AnimateLast = AGETextCtrl::init(CFloat, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_AnimateLast->SetToolTip("Last time animation frame was changed");
    Terrains_FrameChanged_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_FrameChanged_Text = new SolidText(Terrains_Scroller, " Frame Changed *");
    Terrains_FrameChanged = AGETextCtrl::init(CByte, &uiGroupTerrain, this, &popUp, Terrains_Scroller);
    Terrains_FrameChanged->SetToolTip("Has the Draw Frame changed since terrain was drawn?");
    Terrains_Drawn_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Drawn_Text = new SolidText(Terrains_Scroller, " Drawn");
    Terrains_Drawn = AGETextCtrl::init(CByte, &uiGroupTerrain, this, &popUp, Terrains_Scroller);

    for(size_t loop = 0; loop < 2; ++loop)
    {
        Terrains_SearchFilters[loop]->Append("Internal Name");  // 0
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

    Terrains_UsedCountHolder->Add(Terrains_UsedCountText);
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

    Terrains_Unknown1_Holder->Add(Terrains_Unknown1_Text);
    Terrains_Unknown1_Holder->Add(Terrains_Unknown1, 0, wxEXPAND);
    Terrains_Enabled1_Holder->Add(Terrains_Enabled);
    Terrains_Enabled1_Holder->Add(Terrains_Enabled_CheckBox, 0, wxLEFT, 2);
    Terrains_Enabled_Holder->Add(Terrains_Enabled_Text);
    Terrains_Enabled_Holder->Add(Terrains_Enabled1_Holder, 0, wxEXPAND);
    Terrains_Random_Holder->Add(Terrains_Random_Text);
    Terrains_Random_Holder->Add(Terrains_Random, 0, wxEXPAND);
    Terrains_Name_Holder->Add(Terrains_Name_Text);
    Terrains_Name_Holder->Add(Terrains_Name, 0, wxEXPAND);
    Terrains_Name2_Holder->Add(Terrains_Name2_Text);
    Terrains_Name2_Holder->Add(Terrains_Name2, 0, wxEXPAND);
    Terrains_SLP_Holder->Add(Terrains_SLP_Text);
    Terrains_SLP_Holder->Add(Terrains_SLP, 0, wxEXPAND);
    Terrains_Unknown3_Holder->Add(Terrains_Unknown3_Text);
    Terrains_Unknown3_Holder->Add(Terrains_Unknown3, 0, wxEXPAND);
    Terrains_SoundID_Holder->Add(Terrains_SoundID_Text);
    Terrains_SoundID_Holder->Add(Terrains_SoundID, 0, wxEXPAND);
    Terrains_SoundID_Holder->Add(Terrains_SoundID_ComboBox);
    Terrains_BlendPriority_Holder->Add(Terrains_BlendPriority_Text);
    Terrains_BlendPriority_Holder->Add(Terrains_BlendPriority, 0, wxEXPAND);
    Terrains_BlendType_Holder->Add(Terrains_BlendType_Text);
    Terrains_BlendType_Holder->Add(Terrains_BlendType, 0, wxEXPAND);
    for(size_t loop = 0; loop < 3; ++loop)
    Terrains_Colors_Grid->Add(Terrains_Colors[loop], 0, wxEXPAND);
    Terrains_Colors_Holder->Add(Terrains_Colors_Text);
    Terrains_Colors_Holder->Add(Terrains_Colors_Grid, 0, wxEXPAND);
    Terrains_CliffColors_Holder->Add(Terrains_CliffColors_Text);
    for(size_t loop = 0; loop < Terrains_CliffColors.size(); ++loop)
    Terrains_CliffColors_Grid->Add(Terrains_CliffColors[loop], 0, wxEXPAND);
    Terrains_CliffColors_Holder->Add(Terrains_CliffColors_Grid, 0, wxEXPAND);
    Terrains_PassableTerrain_Holder->Add(Terrains_PassableTerrain_Text);
    Terrains_PassableTerrain_Holder->Add(Terrains_PassableTerrain, 0, wxEXPAND);
    Terrains_PassableTerrain_Holder->Add(Terrains_PassableTerrain_ComboBox);
    Terrains_ImpassableTerrain_Holder->Add(Terrains_ImpassableTerrain_Text);
    Terrains_ImpassableTerrain_Holder->Add(Terrains_ImpassableTerrain, 0, wxEXPAND);
    Terrains_ImpassableTerrain_Holder->Add(Terrains_ImpassableTerrain_ComboBox);

    Terrains_IsAnimated_Holder->Add(Terrains_IsAnimated_Text);
    Terrains_AnimationFrames_Holder->Add(Terrains_AnimationFrames_Text);
    Terrains_PauseFames_Holder->Add(Terrains_PauseFames_Text);
    Terrains_Interval_Holder->Add(Terrains_Interval_Text);
    Terrains_PauseBetweenLoops_Holder->Add(Terrains_PauseBetweenLoops_Text);
    Terrains_Frame_Holder->Add(Terrains_Frame_Text);
    Terrains_DrawFrame_Holder->Add(Terrains_DrawFrame_Text);
    Terrains_AnimateLast_Holder->Add(Terrains_AnimateLast_Text);
    Terrains_FrameChanged_Holder->Add(Terrains_FrameChanged_Text);
    Terrains_Drawn_Holder->Add(Terrains_Drawn_Text);
    Terrains_IsAnimated_Holder->Add(Terrains_IsAnimated, 0, wxEXPAND);
    Terrains_AnimationFrames_Holder->Add(Terrains_AnimationFrames, 0, wxEXPAND);
    Terrains_PauseFames_Holder->Add(Terrains_PauseFames, 0, wxEXPAND);
    Terrains_Interval_Holder->Add(Terrains_Interval, 0, wxEXPAND);
    Terrains_PauseBetweenLoops_Holder->Add(Terrains_PauseBetweenLoops, 0, wxEXPAND);
    Terrains_Frame_Holder->Add(Terrains_Frame, 0, wxEXPAND);
    Terrains_DrawFrame_Holder->Add(Terrains_DrawFrame, 0, wxEXPAND);
    Terrains_AnimateLast_Holder->Add(Terrains_AnimateLast, 0, wxEXPAND);
    Terrains_FrameChanged_Holder->Add(Terrains_FrameChanged, 0, wxEXPAND);
    Terrains_Drawn_Holder->Add(Terrains_Drawn, 0, wxEXPAND);
    Terrains_Animation_Grid1->Add(Terrains_IsAnimated_Holder);
    Terrains_Animation_Grid1->Add(Terrains_AnimationFrames_Holder, 0, wxLEFT, 5);
    Terrains_Animation_Grid1->Add(Terrains_PauseFames_Holder, 0, wxLEFT, 5);
    Terrains_Animation_Grid1->Add(Terrains_Interval_Holder, 0, wxLEFT, 5);
    Terrains_Animation_Grid1->Add(Terrains_PauseBetweenLoops_Holder, 0, wxLEFT, 5);
    Terrains_Animation_Grid2->Add(Terrains_Frame_Holder);
    Terrains_Animation_Grid2->Add(Terrains_DrawFrame_Holder, 0, wxLEFT, 5);
    Terrains_Animation_Grid2->Add(Terrains_AnimateLast_Holder, 0, wxLEFT, 5);
    Terrains_Animation_Grid2->Add(Terrains_FrameChanged_Holder, 0, wxLEFT, 5);
    Terrains_Animation_Grid2->Add(Terrains_Drawn_Holder, 0, wxLEFT, 5);

    Terrains_ElevationGraphics_Holder->Add(Terrains_ElevationGraphics_Text);
    Terrains_ElevationGraphics_Holder->Add(Terrain_TileGraphics_Sizer, 0, wxEXPAND);
    for(size_t loop = 0, tile = 0; loop < Terrains_ElevationGraphics.size();)
    {
        Terrain_TileGraphics_Sizers[tile]->Add(Terrains_ElevationGraphics[loop++]);
        Terrain_TileGraphics_Sizers[tile]->Add(Terrains_ElevationGraphics[loop++]);
        Terrain_TileGraphics_Sizers[tile++]->Add(Terrains_ElevationGraphics[loop++]);
    }
    for(auto &sizer: Terrain_TileGraphics_Sizers)
    Terrain_TileGraphics_Sizer->Add(sizer);
    Terrains_TerrainReplacementID_Holder->Add(Terrains_TerrainReplacementID_Text);
    Terrains_TerrainReplacementID_Holder->Add(Terrains_TerrainReplacementID, 0, wxEXPAND);
    Terrains_TerrainReplacementID_Holder->Add(Terrains_TerrainReplacementID_ComboBox);
    Terrains_TerrainDimensions_Holder->Add(Terrains_TerrainDimensions_Text);
    Terrains_TerrainDimensions_Holder->Add(Terrains_TerrainDimensions[0], 0, wxEXPAND);
    Terrains_TerrainDimensions_Holder->Add(Terrains_TerrainDimensions[1], 0, wxEXPAND);

    Terrains_TerrainUnitID_Holder->Add(Terrains_TerrainUnitID_Text);
    Terrains_TerrainUnitID_Holder1->AddSpacer(15);
    Terrains_TerrainUnitDensity_Holder->Add(Terrains_TerrainUnitDensity_Text);
    Terrains_TerrainUnitPriority_Holder->Add(Terrains_TerrainUnitPriority_Text);
    for(size_t loop = 0; loop < TERRAINUNITS; ++loop)
    {
        Terrains_TerrainUnitID_Holder->Add(Terrains_TerrainUnitID[loop], 0, wxEXPAND);
        Terrains_TerrainUnitID_Holder1->Add(Terrains_TerrainUnitID_ComboBox[loop]);
        Terrains_TerrainUnitDensity_Holder->Add(Terrains_TerrainUnitDensity[loop], 0, wxEXPAND);
        Terrains_TerrainUnitPriority_Holder->Add(Terrains_TerrainUnitPriority[loop], 0, wxEXPAND);
    }
    Terrains_UsedTerrainUnits_Holder->Add(Terrains_UsedTerrainUnits_Text);
    Terrains_UsedTerrainUnits_Holder->Add(Terrains_UsedTerrainUnits, 0, wxEXPAND);

    Terrains_NameArea_Holder->Add(Terrains_Enabled_Holder);
    Terrains_NameArea_Holder->Add(Terrains_Random_Holder, 0, wxLEFT, 5);
    Terrains_NameArea_Holder->Add(Terrains_Name_Holder, 0, wxLEFT, 5);
    Terrains_NameArea_Holder->Add(Terrains_Name2_Holder, 0, wxLEFT, 5);

    Terrains_Area1_Grid->Add(Terrains_SLP_Holder);
    Terrains_Area1_Grid->Add(Terrains_SoundID_Holder, 0, wxLEFT, 5);
    Terrains_Area1_Grid->Add(Terrains_BlendPriority_Holder, 0, wxLEFT, 5);
    Terrains_Area1_Grid->Add(Terrains_BlendType_Holder, 0, wxLEFT, 5);
    Terrains_Area2_Grid->Add(Terrains_Colors_Holder);
    Terrains_Area2_Grid->Add(Terrains_CliffColors_Holder, 0, wxLEFT, 5);

    Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitID_Holder);
    Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitID_Holder1);
    Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitDensity_Holder, 0, wxLEFT, 5);
    Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitPriority_Holder, 0, wxLEFT, 5);

    Terrains_GridX1->Add(Terrains_TerrainReplacementID_Holder);
    Terrains_GridX1->Add(Terrains_TerrainDimensions_Holder, 0, wxLEFT, 5);
    Terrains_GridX2->Add(Terrains_Unknown3_Holder);
    Terrains_GridX2->Add(Terrains_Unknown1_Holder, 0, wxLEFT, 5);
    Terrains_GridX2->Add(Terrains_UsedTerrainUnits_Holder, 0, wxLEFT, 5);
    Terrains_Area2_Grid->Add(Terrains_PassableTerrain_Holder, 0, wxLEFT, 5);
    Terrains_Area2_Grid->Add(Terrains_ImpassableTerrain_Holder, 0, wxLEFT, 5);

    Terrains_SpaceRight->Add(Terrains_GridX1, 0, wxBOTTOM, 5);
    Terrains_SpaceRight->Add(Terrains_GridX2, 0, wxBOTTOM, 5);
    Terrains_SpaceRight->Add(Terrains_TerrainUnits_Holder, 0, wxBOTTOM | wxLEFT, 5);

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
    Terrains_GreatSpace->Add(Terrains_SpaceRight, 5, wxEXPAND, 5);

    Terrains_ScrollSpace->Add(Terrains_NameArea_Holder);
    Terrains_ScrollSpace->Add(Terrains_Area1_Grid, 0, wxTOP, 5);
    Terrains_ScrollSpace->Add(Terrains_Area2_Grid, 0, wxTOP, 5);
    Terrains_ScrollSpace->Add(Terrains_GreatSpace, 0, wxEXPAND | wxTOP, 5);
    Terrains_ScrollSpace->Add(Terrains_Animation_Grid1, 0, wxTOP, 5);
    Terrains_ScrollSpace->Add(Terrains_Animation_Grid2, 0, wxTOP, 5);

    Terrains_Scroller->SetSizer(Terrains_ScrollSpace);
    Terrains_Scroller->SetScrollRate(0, 15);

    Terrains_Main->Add(Terrains_Terrains, 21, wxEXPAND | wxALL, 5);
    Terrains_Main->Add(Terrains_Scroller, 65, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

    Tab_Terrains->SetSizer(Terrains_Main);

    Terrains_Terrains_Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTerrainsSearch, this);
    Terrains_Terrains_Search_R->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTerrainsSearch, this);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Terrains_Terrains_UseAnd[loop]->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &AGE_Frame::OnTerrainsSearch, this);
        Terrains_SearchFilters[loop]->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnSelection_SearchFilters, this);
    }
    Terrains_Terrains_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTerrainsSelect, this);
    Terrains_Terrains_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTerrainsSelect, this);
    Terrains_Terrains_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTerrainsSelect, this);
    Terrains_Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainsAdd, this);
    Terrains_Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainsDelete, this);
    Terrains_Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainsCopy, this);
    Terrains_Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainsPaste, this);

    Terrains_Name->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Terrains, this);
    Terrains_Name2->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Terrains, this);
    Terrains_UsedCount->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnTerrainCountChange, this);

    Terrains_Borders_Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTerrainsBorderSearch, this);
    Terrains_Borders_Search_R->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTerrainsBorderSearch, this);
    Terrains_Borders_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTerrainsBorderSelect, this);
    Terrains_Borders_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTerrainsBorderSelect, this);
    Terrains_Borders_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTerrainsBorderSelect, this);
    Terrains_Borders_Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainsBorderCopy, this);
    Terrains_Borders_Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainsBorderPaste, this);
    Terrains_Borders_CopyToTerrains->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTerrainsBorderCopyToBuildings, this);
    Terrains_Border->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Terrains, this);
    Terrains_Border_ComboBox->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_Terrains, this);

    terrainTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTerrainsTimer, this);
    terrainBorderTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTerrainsBorderTimer, this);
}

void AGE_Frame::OnKillFocus_Terrains(wxFocusEvent &event)
{
    event.Skip();
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
    ((AGELinkedBox*)event.GetEventObject())->OnChoose(event);
    ListTerrainsBorders();
}
