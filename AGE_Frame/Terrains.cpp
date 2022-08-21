#include "Common.h"
#include "../AGE_Frame.h"
#include "../Loaders.h"

std::vector<std::function<wxString(genie::Terrain*)>> TerrainFilterFunctions;
bool UseTerrainName;

wxString AGE_Frame::GetTerrainName(int index, bool filter)
{
    wxString name;
    if (filter)
    {
        for (auto &f : TerrainFilterFunctions)
        {
            name += f(&dataset->TerrainBlock.Terrains[index]) + ", ";
        }
    }
    if (UseTerrainName)
    {
        wxString DynamicName = TranslatedText(dataset->TerrainBlock.Terrains[index].StringID, 64);
        if (!DynamicName.empty())
        {
            return name + DynamicName;
        }
    }
    if (!dataset->TerrainBlock.Terrains[index].Name.empty())
    {
        return name + dataset->TerrainBlock.Terrains[index].Name;
    }
    return name + "New Terrain";
}

void AGE_Frame::PrepTerrainSearch()
{
    UseTerrainName = true;
    TerrainFilterFunctions.clear();
    for (size_t loop = 0; loop < 2; ++loop)
    {
        int selection = Terrains_SearchFilters[loop]->GetSelection();
        if (selection < 1) continue;
        wxString label = terrain_filters[selection];

        if (label.compare("Internal Name") == 0)
        {
            UseTerrainName = false;
            continue;
        }
        else if (label.compare("Sprite Name") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "FN " + terrain_ptr->Name2;
        });
        else if (label.compare("Sprite") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "SLP " + FormatInt(terrain_ptr->SLP);
        });
        else if (label.compare("Enabled") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "E " + FormatInt(terrain_ptr->Enabled);
        });
        else if (label.compare("Random") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "R " + FormatInt(terrain_ptr->Random);
        });
        else if (label.compare("Shape Pointer") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "SP " + FormatInt(terrain_ptr->ShapePtr);
        });
        else if (label.compare("Sound") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "S " + FormatInt(terrain_ptr->SoundID);
        });
        else if (label.compare("Blend Priority") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "BP " + FormatInt(terrain_ptr->BlendPriority);
        });
        else if (label.compare("Blend Type") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "BT " + FormatInt(terrain_ptr->BlendType);
        });
        else if (label.compare("Colors") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "H" + FormatInt(terrain_ptr->Colors[0])
                + " M" + FormatInt(terrain_ptr->Colors[1])
                + " L" + FormatInt(terrain_ptr->Colors[2]);
        });
        else if (label.compare("Cliff Colors") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "LT" + FormatInt(terrain_ptr->CliffColors.first)
                + " RT" + FormatInt(terrain_ptr->CliffColors.second);
        });
        else if (label.compare("Passable Terrain") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "PT " + FormatInt(terrain_ptr->PassableTerrain);
        });
        else if (label.compare("Impassable Terrain") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "IT " + FormatInt(terrain_ptr->ImpassableTerrain);
        });
        else if (label.compare("Frame Count") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "FC " + FormatInt(terrain_ptr->ElevationGraphics.front().FrameCount);
        });
        else if (label.compare("Angle Count") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "AC " + FormatInt(terrain_ptr->ElevationGraphics.front().AngleCount);
        });
        else if (label.compare("Terrain to Draw") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "TD " + FormatInt(terrain_ptr->TerrainToDraw);
        });
        else if (label.compare("Terrain Dimensions") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "R" + FormatInt(terrain_ptr->TerrainDimensions.first)
                + " C" + FormatInt(terrain_ptr->TerrainDimensions.second);
        });
        else if (label.compare("Terrain Units Used") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "TU " + FormatInt(terrain_ptr->NumberOfTerrainUnitsUsed);
        });
        else if (label.compare("Phantom Variable") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "U1 " + FormatInt(terrain_ptr->Phantom);
        });
        else if (label.compare("Water") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "IW " + FormatInt(terrain_ptr->IsWater);
        });
        else if (label.compare("Hide in Editor") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "HE " + FormatInt(terrain_ptr->HideInEditor);
        });
        else if (label.compare("Name String") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "NS " + FormatInt(terrain_ptr->StringID);
        });
        else if (label.compare("Overlay Mask") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "OM " + terrain_ptr->OverlayMaskName;
        });
        else if (label.compare("Wave Works Stop Sound") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "WSS " + FormatInt(terrain_ptr->WwiseSoundStopID);
        });
        else if (label.compare("Wave Works Sound") == 0)
            TerrainFilterFunctions.push_back([this](genie::Terrain *terrain_ptr)
        {
            return "WS " + FormatInt(terrain_ptr->WwiseSoundID);
        });
    }
}

void AGE_Frame::OnTerrainsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
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
    if(static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() != 0) return;
    uint16_t UsedTerrains = lexical_cast<uint16_t>(static_cast<wxTextCtrl*>(event.GetEventObject())->GetValue());
    // Resize terrain restrictions
    for(size_t loop = 0; loop < dataset->TerrainRestrictions.size(); ++loop)
    {
        dataset->TerrainRestrictions[loop].PassableBuildableDmgMultiplier.resize(UsedTerrains);
        if(GenieVersion >= genie::GV_AoKA)
        dataset->TerrainRestrictions[loop].TerrainPassGraphics.resize(UsedTerrains);
    }

    wxCommandEvent e;
    OnTerrainRestrictionSelect(e);
}

void AGE_Frame::ListTerrains1(bool all)
{
    InitTerrains1(all);
    wxCommandEvent e;
    OnTerrainSelect(e);
    if(all) OnTerrainRestrictionsTerrainSelect(e);
}

void AGE_Frame::ListTerrains2()
{
    InitTerrains2();
    wxCommandEvent e;
    OnTerrainRestrictionsTerrainSelect(e);
}

void AGE_Frame::InitTerrains1(bool all)
{
    InitSearch(Terrains_Terrains_Search->GetValue().MakeLower(), Terrains_Terrains_Search_R->GetValue().MakeLower());
    SearchAnd = Terrains_Terrains_UseAnd[0]->GetValue();
    ExcludeAnd = Terrains_Terrains_UseAnd[1]->GetValue();
    PrepTerrainSearch();

    Terrains_Terrains_ListV->Sweep();
    if(all)
    {
        terrain_names.Clear();
        terrain_names.Alloc(1 + dataset->TerrainBlock.Terrains.size());
        terrain_names.Add("-1 - None");
    }

    for(size_t loop = 0; loop < dataset->TerrainBlock.Terrains.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetTerrainName(loop, true);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Terrains_Terrains_ListV->names.Add(Name);
            Terrains_Terrains_ListV->indexes.push_back(loop);
        }
        if (all)
        {
            terrain_names.Add(FormatInt(loop) + " - " + GetTerrainName(loop));
        }
    }

    SearchAnd = ExcludeAnd = false;

    RefreshList(Terrains_Terrains_ListV, &TerrainIDs);
    if (all)
    {
        for (AGEComboBox *list : TerrainComboBoxList)
        {
            list->Flash();
        }
    }
    InitTerrains2();
}

void AGE_Frame::InitTerrains2()
{
    InitSearch(TerRestrict_Terrains_Search->GetValue().MakeLower(), TerRestrict_Terrains_Search_R->GetValue().MakeLower());

    TerRestrict_Terrains_ListV->Sweep();

    if (TerRestrictIDs.size())
    for(size_t loop = 0; loop < dataset->TerrainRestrictions.front().PassableBuildableDmgMultiplier.size(); ++loop)
    {
        float val = dataset->TerrainRestrictions[TerRestrictIDs.front()].PassableBuildableDmgMultiplier[loop];
        wxString Name = FormatInt(loop)+" - M"+FormatFloat(val)+" P"+(val > 0.f ? "1" : "0")+" B"+(val > 0.05f ? "1" : "0")+" - "+GetTerrainName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            TerRestrict_Terrains_ListV->names.Add(Name);
            TerRestrict_Terrains_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(TerRestrict_Terrains_ListV, &TerRestrictTerIDs);
}

void AGE_Frame::OnTerrainSelect(wxCommandEvent &event)
{
    size_t selections = Terrains_Terrains_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Terrains_Terrains_ListV, TerrainIDs);

    for (AGETextCtrl *box : uiGroupTerrain) box->clear();

    genie::Terrain * TerrainPointer = 0;
    for(size_t sel = selections; sel--> 0;)
    {
        TerrainPointer = &dataset->TerrainBlock.Terrains[TerrainIDs[sel]];

        if(GenieVersion < genie::GV_SWGB)
        Terrains_Phantom->prepend(&TerrainPointer->Phantom);
        Terrains_Enabled->prepend(&TerrainPointer->Enabled);
        Terrains_Random->prepend(&TerrainPointer->Random);
        Terrains_Name->prepend(&TerrainPointer->Name);
        Terrains_FileName->prepend(&TerrainPointer->Name2);
        if(GenieVersion >= genie::GV_AoEB)
        Terrains_SLP->prepend(&TerrainPointer->SLP);
        Terrains_ShapePtr->prepend(&TerrainPointer->ShapePtr);
        Terrains_SoundID->prepend(&TerrainPointer->SoundID);
        if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
        {
            Terrains_WwiseSoundID->prepend(&TerrainPointer->WwiseSoundID);
            Terrains_SoundStopID->prepend(&TerrainPointer->WwiseSoundStopID);
            Terrains_OverlayMaskName->prepend(&TerrainPointer->OverlayMaskName);
            Terrains_IsWater->prepend(&TerrainPointer->IsWater);
            Terrains_HideInEditor->prepend(&TerrainPointer->HideInEditor);
            Terrains_StringID->prepend(&TerrainPointer->StringID);
        }
        if(GenieVersion >= genie::GV_AoKB)
        {
            BLENDS:
            Terrains_BlendPriority->prepend(&TerrainPointer->BlendPriority);
            Terrains_BlendType->prepend(&TerrainPointer->BlendType);
        }
        else if(GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap)
        {
            Terrains_IsWater->prepend(&TerrainPointer->IsWater);
            Terrains_HideInEditor->prepend(&TerrainPointer->HideInEditor);
            Terrains_StringID->prepend(&TerrainPointer->StringID);
            goto BLENDS;
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
            Terrains_TerrainUnitMaskedDensity[loop]->prepend(&TerrainPointer->TerrainUnitMaskedDensity[loop]);
            Terrains_TerrainUnitPriority[loop]->prepend(&TerrainPointer->TerrainUnitCentering[loop]);
        }
        Terrains_UsedTerrainUnits->prepend(&TerrainPointer->NumberOfTerrainUnitsUsed);
    }
    SetStatusText(wxString::Format("Selections: %zu    Selected terrain: %d",
        selections, selections > 0 ? TerrainIDs.front() : -1), 0);

    for (AGETextCtrl *box : uiGroupTerrain) box->update();
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
            if (TerrainPointer->TerrainToDraw < dataset->TerrainBlock.Terrains.size())
            {
                TerrainPointer = &dataset->TerrainBlock.Terrains[TerrainPointer->TerrainToDraw];
            }
            if(LooseHD)
            {
                wxString resname;
                folder.Replace("drs", "terrain\\textures", false);
                if(!wxFileName(resname).FileExists())
                {
                    resname = folder + "\\" + TerrainPointer->Name2 + "_00_color.png";
                }
                if(wxFileName(resname).FileExists())
                {
                    wxLogNull suppresser;
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

    if(GenieVersion < genie::GV_C2 || GenieVersion > genie::GV_LatestDE2)
    {
        ListTerrainsBorders();
    }
}

wxThread::ExitCode Loader::Entry()
{
    const std::vector<genie::Color> *pal = &HostFrame->palettes.front();
    if(pal->empty()) return (wxThread::ExitCode)0;
    size_t TileHalfWidth = HostFrame->dataset->TerrainBlock.TileHalfWidth;
    size_t TileHalfHeight = HostFrame->dataset->TerrainBlock.TileHalfHeight;
    AGE_SLP tileSLP;
    if (TerrainPointer->SLP != -1)
    for (genie::DrsFile *file : HostFrame->datafiles)
    {
        tileSLP.slp = GG::LoadSLP(*file, TerrainPointer->SLP);
        if (tileSLP.slp && tileSLP.slp->isSLP())
        {
            tileSLP.frames = tileSLP.slp->getFrameCount();
            int rows = TerrainPointer->TerrainDimensions.first;
            int cols = TerrainPointer->TerrainDimensions.second;
            size_t wwidth = (rows + cols) * TileHalfWidth;
            size_t wheight = (rows + cols) * TileHalfHeight;
            size_t warea = wwidth * wheight + 1;
            std::vector<uint8_t> wrgbdata(warea * 4, 0);

            std::vector<std::pair<size_t, size_t>> corners(rows * cols);
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
                    genie::SlpFile *slp = static_cast<genie::SlpFile *>(tileSLP.slp.get());
                    frame = slp->getFrame(f);
                }
                catch (const std::out_of_range &) {}
                if (frame)
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
            tileSLP.bitmap = wxBitmap(wxImage(wwidth, wheight, pic, trans, true), 32);
            break;
        }
    }
    HostFrame->tileSLP = std::move(tileSLP);
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
    if(!Terrains_Terrains_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::Terrain::setTerrainCount(CustomTerrains -= TerrainIDs.size());
    DeleteFromList(dataset->TerrainBlock.Terrains, TerrainIDs);
    for(size_t loop = dataset->TerrainBlock.Terrains.size(); loop--> 0;)
    DeleteFromList(dataset->TerrainBlock.Terrains[loop].Borders, TerrainIDs);
    ListTerrains1();
}

void AGE_Frame::OnTerrainsCopy(wxCommandEvent &event)
{
    if(!Terrains_Terrains_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TerrainBlock.Terrains, TerrainIDs, copies.Terrain);
    Terrains_Terrains_ListV->SetFocus();
}

void AGE_Frame::OnTerrainsPaste(wxCommandEvent &event)
{
    if(!Terrains_Terrains_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::Terrain::setTerrainCount(ResizeTerrains ? CustomTerrains : 0); // Since it is static variable.
    PasteToList(dataset->TerrainBlock.Terrains, TerrainIDs, copies.Terrain, false);
    ListTerrains1();
}

void AGE_Frame::OnTerrainsBorderSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListTerrainsBorders();
}

void AGE_Frame::ListTerrainsBorders()
{
    if (GenieVersion == genie::GV_TCV || GenieVersion == genie::GV_CCV || GenieVersion == genie::GV_CCV2)
        return;

    InitSearch(Terrains_Borders_Search->GetValue().MakeLower(), Terrains_Borders_Search_R->GetValue().MakeLower());

    Terrains_Borders_ListV->Sweep();

    if (TerrainIDs.size())
    for(size_t loop = 0; loop < dataset->TerrainBlock.Terrains.size(); ++loop)
    {
        wxString Name = FormatInt(loop) + " " + GetTerrainName(loop) + " - "
        + FormatInt(dataset->TerrainBlock.Terrains[TerrainIDs.front()].Borders[loop]) + " "
        + GetTerrainBorderName(dataset->TerrainBlock.Terrains[TerrainIDs.front()].Borders[loop]);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Terrains_Borders_ListV->names.Add(Name);
            Terrains_Borders_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(Terrains_Borders_ListV, &TerBorderIDs);

    wxCommandEvent e;
    OnTerrainsBorderSelect(e);
}

void AGE_Frame::OnTerrainsBorderSelect(wxCommandEvent &event)
{
    size_t selections = Terrains_Borders_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Terrains_Borders_ListV, TerBorderIDs);
    Terrains_Border->clear();

    int16_t * BorderPointer;
    for(size_t loop = selections; loop--> 0;)
    {
        BorderPointer = &dataset->TerrainBlock.Terrains[TerrainIDs.front()].Borders[TerBorderIDs[loop]];
        Terrains_Border->prepend(BorderPointer);
    }

    Terrains_Border->update();
}

void AGE_Frame::OnTerrainsBorderCopy(wxCommandEvent &event)
{
    size_t selections = Terrains_Borders_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TerrainBlock.Terrains[TerrainIDs.front()].Borders, TerBorderIDs, copies.TerBorder);
    Terrains_Borders_ListV->SetFocus();
}

void AGE_Frame::OnTerrainsBorderPaste(wxCommandEvent &event)
{
    size_t selections = Terrains_Borders_ListV->GetSelectedCount();
    if (!selections) return;

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
    Tab_Terrains = new ATabPage(TabBar_Main);
    Terrains_Terrains = new wxStaticBoxSizer(wxVERTICAL, Tab_Terrains, "Terrains");
    Terrains_Terrains_Search = new wxTextCtrl(Tab_Terrains, wxID_ANY);
    Terrains_Terrains_UseAnd[0] = new wxCheckBox(Tab_Terrains, wxID_ANY, "And");
    Terrains_Terrains_Search_R = new wxTextCtrl(Tab_Terrains, wxID_ANY);
    Terrains_Terrains_UseAnd[1] = new wxCheckBox(Tab_Terrains, wxID_ANY, "And");
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Terrains_Terrains_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
        Terrains_SearchFilters[loop] = new AGEComboBox(Tab_Terrains, &terrain_filters);
    }
    Terrains_Terrains_ListV = new ProperList(Tab_Terrains, ASize(200, 100));
    Terrains_UsedCountHolder = new wxBoxSizer(wxHORIZONTAL);
    Terrains_UsedCountText = new SolidText(Tab_Terrains, " Terrains Used *");
    Terrains_UsedCount = new NumberControl(CShort, Tab_Terrains, this, nullptr, false);
    Terrains_UsedCount->SetToolTip("How many terrains are used\nstarting from the first terrain without gaps");
    Terrains_Add = new wxButton(Tab_Terrains, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Terrains_Delete = new wxButton(Tab_Terrains, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Terrains_Copy = new wxButton(Tab_Terrains, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Terrains_Paste = new wxButton(Tab_Terrains, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));

    Terrains_Scroller = new AScrolled(Tab_Terrains);
    Terrains_ScrollSpace = new wxBoxSizer(wxVERTICAL);
    Terrains_NameArea_Holder = new wxBoxSizer(wxHORIZONTAL);
    Terrains_Area1_Grid = new wxBoxSizer(wxHORIZONTAL);
    Terrains_Area2_Grid = new wxBoxSizer(wxHORIZONTAL);
    Terrains_Enabled_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Enabled1_Holder = new wxBoxSizer(wxHORIZONTAL);
    Terrains_Enabled_Text = new SolidText(Terrains_Scroller, " Enabled");
    Terrains_Enabled = new NumberControl(CUByte, Terrains_Scroller, this, &uiGroupTerrain, true, AGETextCtrl::SMALL);
    Terrains_Enabled_CheckBox = new LinkedCheckBox(Terrains_Scroller, " Yes", Terrains_Enabled);
    Terrains_Random_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Random_Text = new SolidText(Terrains_Scroller, " Random");
    Terrains_Random = new NumberControl(CUByte, Terrains_Scroller, this, &uiGroupTerrain, true, AGETextCtrl::SMALL);
    Terrains_Name_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Name_Text = new SolidText(Terrains_Scroller, " Internal Name");
    Terrains_Name = new StringControl(Terrains_Scroller,  this, &uiGroupTerrain, false);
    Terrains_FileName_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_FileName_Text = new SolidText(Terrains_Scroller, " Texture Filename");
    Terrains_FileName = new StringControl(Terrains_Scroller,  this, &uiGroupTerrain, false);
    Terrains_SLP_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_SLP_Text = new SolidText(Terrains_Scroller, " SLP");
    Terrains_SLP = new NumberControl(CLong, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_SoundID_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_SoundID_Text = new SolidText(Terrains_Scroller, " Sound");
    Terrains_WwiseSoundID = new NumberControl(CULong, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_SoundID = new NumberControl(CLong, Terrains_Scroller, this, &uiGroupTerrain, true, AGETextCtrl::SMALL);
    Terrains_SoundID_ComboBox = new LinkedComboBox(Terrains_Scroller, Terrains_SoundID, &sound_names);
    SoundComboBoxList.push_back(Terrains_SoundID_ComboBox);
    Terrains_SoundStopID_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_SoundStopID_Text = new SolidText(Terrains_Scroller, " Sound Stop Event");
    Terrains_SoundStopID = new NumberControl(CULong, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_BlendPriority_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_BlendPriority_Text = new SolidText(Terrains_Scroller, " Blend Level");
    Terrains_BlendPriority = new NumberControl(CLong, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_BlendType_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_BlendType_Text = new SolidText(Terrains_Scroller, " Blend Class");
    Terrains_BlendType = new NumberControl(CLong, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_OverlayMaskName_Holder = new wxBoxSizer(wxHORIZONTAL);
    Terrains_OverlayMaskName_Text = new SolidText(Terrains_Scroller, " Overlay Mask Name");
    Terrains_OverlayMaskName = new StringControl(Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_OverlayMaskName_Browse = new wxButton(Terrains_Scroller, wxID_ANY, "Browse");
    Terrains_Colors_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Colors_Grid = new wxGridSizer(3, 0, 0);
    Terrains_Colors_Text = new SolidText(Terrains_Scroller, " Minimap Colors");
    for(size_t loop = 0; loop < 3; ++loop)
    Terrains_Colors[loop] = new NumberControl(CUByte, Terrains_Scroller, this, &uiGroupTerrain, true, AGETextCtrl::SMALL);
    Terrains_CliffColors_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_CliffColors_Grid = new wxGridSizer(2, 0, 0);
    Terrains_CliffColors_Text = new SolidText(Terrains_Scroller, " Minimap Cliff Colors");
    for(size_t loop = 0; loop < Terrains_CliffColors.size(); ++loop)
    Terrains_CliffColors[loop] = new NumberControl(CUByte, Terrains_Scroller, this, &uiGroupTerrain, true, AGETextCtrl::SMALL);

    Terrains_PassableTerrain_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_PassableTerrain_Text = new SolidText(Terrains_Scroller, " Passable Terrain");
    Terrains_PassableTerrain = new NumberControl(CUByte, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_PassableTerrain_ComboBox = new LinkedComboBox(Terrains_Scroller, Terrains_PassableTerrain, &terrain_names);
    TerrainComboBoxList.push_back(Terrains_PassableTerrain_ComboBox);
    Terrains_ImpassableTerrain_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_ImpassableTerrain_Text = new SolidText(Terrains_Scroller, " Impassable Terrain");
    Terrains_ImpassableTerrain = new NumberControl(CUByte, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_ImpassableTerrain_ComboBox = new LinkedComboBox(Terrains_Scroller, Terrains_ImpassableTerrain, &terrain_names);
    TerrainComboBoxList.push_back(Terrains_ImpassableTerrain_ComboBox);
    Terrains_TerrainReplacementID_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainReplacementID_Text = new SolidText(Terrains_Scroller, " Terrain to Draw");
    Terrains_TerrainReplacementID = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_TerrainReplacementID_ComboBox = new LinkedComboBox(Terrains_Scroller, Terrains_TerrainReplacementID, &terrain_names);
    TerrainComboBoxList.push_back(Terrains_TerrainReplacementID_ComboBox);
    Terrains_TerrainDimensions_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainDimensions_Text = new SolidText(Terrains_Scroller, " Terrain Dimensions");
    Terrains_TerrainDimensions[0] = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_TerrainDimensions[1] = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_TerrainDimensions[0]->SetToolTip("Rows");
    Terrains_TerrainDimensions[1]->SetToolTip("Columns");
    Terrains_StringID_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_StringID_Text = new SolidText(Terrains_Scroller, " String ID");
    Terrains_StringID = new NumberControl(CLong, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_IsWater_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_IsWater_Text = new SolidText(Terrains_Scroller, " Type *");
    Terrains_IsWater = new NumberControl(CUByte, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_IsWater->SetToolTip("0   None\n1   Water\n2   Deep water\n4   Shallow water\n8   Walkable shallow\n16   Beach\n32   Land\n64   Ice\n128   Snow");
    Terrains_HideInEditor_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_HideInEditor_Text = new SolidText(Terrains_Scroller, " Hide in Editor");
    Terrains_HideInEditor = new NumberControl(CUByte, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_ShapePtr_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_ShapePtr_Text = new SolidText(Terrains_Scroller, " Shape Pointer *");
    Terrains_ShapePtr = new NumberControl(CLong, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_ShapePtr->SetToolTip("Assigned using SHP Filename");
    Terrains_GridX1 = new wxBoxSizer(wxHORIZONTAL);
    Terrains_GridX2 = new wxFlexGridSizer(3, 5, 5);

    Terrains_GreatSpace = new wxBoxSizer(wxHORIZONTAL);
    Terrains_SpaceLeft = new wxBoxSizer(wxVERTICAL);
    Terrains_SpaceRight = new wxBoxSizer(wxVERTICAL);
    Terrains_Borders = new wxStaticBoxSizer(wxVERTICAL, Terrains_Scroller, "Borders");
    Terrains_Borders_Search = new wxTextCtrl(Terrains_Scroller, wxID_ANY);
    Terrains_Borders_Search_R = new wxTextCtrl(Terrains_Scroller, wxID_ANY);
    Terrains_Borders_ListV = new ProperList(Terrains_Scroller, ASize(200, 250));
    Terrains_Border = new NumberControl(CShort, Terrains_Scroller, this, nullptr, false);
    Terrains_Border_ComboBox = new LinkedComboBox(Terrains_Scroller, Terrains_Border, &border_names, false);
    TerrainBorderComboBoxList.push_back(Terrains_Border_ComboBox);
    Terrains_Borders_Buttons = new wxGridSizer(2, 0, 0);
    Terrains_Borders_Copy = new wxButton(Terrains_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Terrains_Borders_Paste = new wxButton(Terrains_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Terrains_Borders_CopyToTerrains = new wxButton(Terrains_Scroller, wxID_ANY, "Copy all to selected terrains", wxDefaultPosition, wxSize(10, -1));

    Terrains_UsedTerrainUnits_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_UsedTerrainUnits_Text = new SolidText(Terrains_Scroller, " Terrain Units Used");
    Terrains_UsedTerrainUnits = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_Phantom_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Phantom_Text = new SolidText(Terrains_Scroller, " Phantom Var");
    Terrains_Phantom = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_TerrainUnits_Holder = new wxBoxSizer(wxHORIZONTAL);
    Terrains_TerrainUnitID_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainUnitID_Holder1 = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainUnitDensity_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainUnitMaskedDensity_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainUnitPriority_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_TerrainUnitID_Text = new SolidText(Terrains_Scroller, " Terrain Unit");
    Terrains_TerrainUnitDensity_Text = new SolidText(Terrains_Scroller, " Unit Density");
    Terrains_TerrainUnitPriority_Text = new SolidText(Terrains_Scroller, " Centralize *");
    for(size_t loop = 0; loop < TERRAINUNITS; ++loop)
    {
        Terrains_TerrainUnitID[loop] = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain, true, AGETextCtrl::SMALL);
        Terrains_TerrainUnitID_ComboBox[loop] = new LinkedComboBox(Terrains_Scroller, Terrains_TerrainUnitID[loop], &unit_names);
        UnitComboBoxList.push_back(Terrains_TerrainUnitID_ComboBox[loop]);
        Terrains_TerrainUnitDensity[loop] = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain, true, AGETextCtrl::SMALL);
        Terrains_TerrainUnitMaskedDensity[loop] = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain, true, AGETextCtrl::SMALL);
        Terrains_TerrainUnitPriority[loop] = new NumberControl(CUByte, Terrains_Scroller, this, &uiGroupTerrain, true, AGETextCtrl::SMALL);
        Terrains_TerrainUnitPriority[loop]->SetToolTip("0   Place randomly on the tile\n1   Place in middle of the tile");
    }
    Terrains_ElevationGraphics_Holder = new wxBoxSizer(wxVERTICAL);
    Terrain_TileGraphics_Sizer = new wxBoxSizer(wxVERTICAL);
    Terrains_ElevationGraphics_Text = new SolidText(Terrains_Scroller, " Tile Graphics: flat, 2 x 8 elevation, 2 x 1:1\n Frame Count, Animations, Frame Index");
    for (wxBoxSizer *&sizer : Terrain_TileGraphics_Sizers)
    sizer = new wxBoxSizer(wxHORIZONTAL);
    for (AGETextCtrl *&box : Terrains_ElevationGraphics)
    box = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain, true, AGETextCtrl::MEDIUM);

    Terrains_Animation_Grid1 = new wxBoxSizer(wxHORIZONTAL);
    Terrains_Animation_Grid2 = new wxBoxSizer(wxHORIZONTAL);
    Terrains_IsAnimated_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_IsAnimated_Text = new SolidText(Terrains_Scroller, " Is Animated");
    Terrains_IsAnimated = new NumberControl(CUByte, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_AnimationFrames_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_AnimationFrames_Text = new SolidText(Terrains_Scroller, " Anim Frames *");
    Terrains_AnimationFrames = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_AnimationFrames->SetToolTip("Number of frames to animate through");
    Terrains_PauseFames_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_PauseFames_Text = new SolidText(Terrains_Scroller, " Pause Fames *");
    Terrains_PauseFames = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_PauseFames->SetToolTip("Number of frames to pause animation after last frame is drawn");
    Terrains_Interval_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Interval_Text = new SolidText(Terrains_Scroller, " Interval *");
    Terrains_Interval = new NumberControl(CFloat, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_Interval->SetToolTip("Time between frames");
    Terrains_PauseBetweenLoops_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_PauseBetweenLoops_Text = new SolidText(Terrains_Scroller, " Replay Delay *");
    Terrains_PauseBetweenLoops = new NumberControl(CFloat, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_PauseBetweenLoops->SetToolTip("Time to pause after last frame");
    Terrains_Frame_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Frame_Text = new SolidText(Terrains_Scroller, " Frame *");
    Terrains_Frame = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_Frame->SetToolTip("The current frame (includes animation and pause frames)");
    Terrains_DrawFrame_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_DrawFrame_Text = new SolidText(Terrains_Scroller, " Draw Frame *");
    Terrains_DrawFrame = new NumberControl(CShort, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_DrawFrame->SetToolTip("The current frame to draw");
    Terrains_AnimateLast_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_AnimateLast_Text = new SolidText(Terrains_Scroller, " Animate Last *");
    Terrains_AnimateLast = new NumberControl(CFloat, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_AnimateLast->SetToolTip("Last time animation frame was changed");
    Terrains_FrameChanged_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_FrameChanged_Text = new SolidText(Terrains_Scroller, " Frame Changed *");
    Terrains_FrameChanged = new NumberControl(CUByte, Terrains_Scroller, this, &uiGroupTerrain);
    Terrains_FrameChanged->SetToolTip("Has the Draw Frame changed since terrain was drawn?");
    Terrains_Drawn_Holder = new wxBoxSizer(wxVERTICAL);
    Terrains_Drawn_Text = new SolidText(Terrains_Scroller, " Drawn");
    Terrains_Drawn = new NumberControl(CUByte, Terrains_Scroller, this, &uiGroupTerrain);

    Terrains_UsedCountHolder->Add(Terrains_UsedCountText);
    Terrains_UsedCountHolder->Add(Terrains_UsedCount, 1, wxEXPAND | wxLEFT, 2);

    Terrains_Terrains_Buttons->Add(Terrains_Add, 1, wxEXPAND);
    Terrains_Terrains_Buttons->Add(Terrains_Delete, 1, wxEXPAND);
    Terrains_Terrains_Buttons->Add(Terrains_Copy, 1, wxEXPAND);
    Terrains_Terrains_Buttons->Add(Terrains_Paste, 1, wxEXPAND);

    Terrains_Terrains_Searches[0]->Add(Terrains_Terrains_Search, 1, wxEXPAND);
    Terrains_Terrains_Searches[0]->Add(Terrains_Terrains_UseAnd[0], 0, wxLEFT, 2);
    Terrains_Terrains_Searches[1]->Add(Terrains_Terrains_Search_R, 1, wxEXPAND);
    Terrains_Terrains_Searches[1]->Add(Terrains_Terrains_UseAnd[1], 0, wxLEFT, 2);
    for(size_t loop = 0; loop < 2; ++loop)
    Terrains_Terrains->Add(Terrains_Terrains_Searches[loop], 0, wxEXPAND);
    for(size_t loop = 0; loop < 2; ++loop)
    Terrains_Terrains->Add(Terrains_SearchFilters[loop], 0, wxEXPAND);
    Terrains_Terrains->Add(Terrains_Terrains_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Terrains_Terrains->Add(Terrains_UsedCountHolder, 0, wxEXPAND);
    Terrains_Terrains->Add(Terrains_Terrains_Buttons, 0, wxEXPAND | wxTOP, 2);

    Terrains_Phantom_Holder->Add(Terrains_Phantom_Text);
    Terrains_Phantom_Holder->Add(Terrains_Phantom);
    Terrains_Enabled1_Holder->Add(Terrains_Enabled);
    Terrains_Enabled1_Holder->Add(Terrains_Enabled_CheckBox, 0, wxLEFT, 2);
    Terrains_Enabled_Holder->Add(Terrains_Enabled_Text);
    Terrains_Enabled_Holder->Add(Terrains_Enabled1_Holder);
    Terrains_Random_Holder->Add(Terrains_Random_Text);
    Terrains_Random_Holder->Add(Terrains_Random);
    Terrains_Name_Holder->Add(Terrains_Name_Text);
    Terrains_Name_Holder->Add(Terrains_Name);
    Terrains_FileName_Holder->Add(Terrains_FileName_Text);
    Terrains_FileName_Holder->Add(Terrains_FileName);
    Terrains_SLP_Holder->Add(Terrains_SLP_Text);
    Terrains_SLP_Holder->Add(Terrains_SLP);
    Terrains_ShapePtr_Holder->Add(Terrains_ShapePtr_Text);
    Terrains_ShapePtr_Holder->Add(Terrains_ShapePtr);
    Terrains_SoundID_Holder->Add(Terrains_SoundID_Text);
    wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(Terrains_SoundID, 1, wxEXPAND);
    sizer->Add(Terrains_WwiseSoundID, 2, wxEXPAND);
    Terrains_SoundID_Holder->Add(sizer, 0, wxEXPAND);
    Terrains_SoundID_Holder->Add(Terrains_SoundID_ComboBox);
    Terrains_SoundStopID_Holder->Add(Terrains_SoundStopID_Text);
    Terrains_SoundStopID_Holder->Add(Terrains_SoundStopID);
    Terrains_BlendPriority_Holder->Add(Terrains_BlendPriority_Text);
    Terrains_BlendPriority_Holder->Add(Terrains_BlendPriority);
    Terrains_BlendType_Holder->Add(Terrains_BlendType_Text);
    Terrains_BlendType_Holder->Add(Terrains_BlendType);
    Terrains_OverlayMaskName_Holder->Add(Terrains_OverlayMaskName);
    Terrains_OverlayMaskName_Holder->Add(Terrains_OverlayMaskName_Browse);
    Terrains_IsWater_Holder->Add(Terrains_IsWater_Text);
    Terrains_IsWater_Holder->Add(Terrains_IsWater);
    Terrains_HideInEditor_Holder->Add(Terrains_HideInEditor_Text);
    Terrains_HideInEditor_Holder->Add(Terrains_HideInEditor);
    Terrains_StringID_Holder->Add(Terrains_StringID_Text);
    Terrains_StringID_Holder->Add(Terrains_StringID);
    for(size_t loop = 0; loop < 3; ++loop)
    Terrains_Colors_Grid->Add(Terrains_Colors[loop]);
    Terrains_Colors_Holder->Add(Terrains_Colors_Text);
    Terrains_Colors_Holder->Add(Terrains_Colors_Grid);
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
    Terrains_IsAnimated_Holder->Add(Terrains_IsAnimated);
    Terrains_AnimationFrames_Holder->Add(Terrains_AnimationFrames);
    Terrains_PauseFames_Holder->Add(Terrains_PauseFames);
    Terrains_Interval_Holder->Add(Terrains_Interval);
    Terrains_PauseBetweenLoops_Holder->Add(Terrains_PauseBetweenLoops);
    Terrains_Frame_Holder->Add(Terrains_Frame);
    Terrains_DrawFrame_Holder->Add(Terrains_DrawFrame);
    Terrains_AnimateLast_Holder->Add(Terrains_AnimateLast);
    Terrains_FrameChanged_Holder->Add(Terrains_FrameChanged);
    Terrains_Drawn_Holder->Add(Terrains_Drawn);
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
    Terrains_ElevationGraphics_Holder->Add(Terrain_TileGraphics_Sizer);
    for(size_t loop = 0, tile = 0; loop < Terrains_ElevationGraphics.size();)
    {
        Terrain_TileGraphics_Sizers[tile]->Add(Terrains_ElevationGraphics[loop++]);
        Terrain_TileGraphics_Sizers[tile]->Add(Terrains_ElevationGraphics[loop++]);
        Terrain_TileGraphics_Sizers[tile++]->Add(Terrains_ElevationGraphics[loop++]);
    }
    for (wxBoxSizer *&innerSizer : Terrain_TileGraphics_Sizers)
    Terrain_TileGraphics_Sizer->Add(innerSizer);
    Terrains_TerrainReplacementID_Holder->Add(Terrains_TerrainReplacementID_Text);
    Terrains_TerrainReplacementID_Holder->Add(Terrains_TerrainReplacementID, 0, wxEXPAND);
    Terrains_TerrainReplacementID_Holder->Add(Terrains_TerrainReplacementID_ComboBox);
    Terrains_TerrainDimensions_Holder->Add(Terrains_TerrainDimensions_Text);
    Terrains_TerrainDimensions_Holder->Add(Terrains_TerrainDimensions[0]);
    Terrains_TerrainDimensions_Holder->Add(Terrains_TerrainDimensions[1]);

    Terrains_TerrainUnitID_Holder->Add(Terrains_TerrainUnitID_Text);
    Terrains_TerrainUnitID_Holder1->Add(new SolidText(Terrains_Scroller, " "));
    Terrains_TerrainUnitDensity_Holder->Add(Terrains_TerrainUnitDensity_Text);
    Terrains_TerrainUnitMaskedDensity_Holder->Add(new SolidText(Terrains_Scroller, " Masked"));
    Terrains_TerrainUnitPriority_Holder->Add(Terrains_TerrainUnitPriority_Text);
    for(size_t loop = 0; loop < TERRAINUNITS; ++loop)
    {
        Terrains_TerrainUnitID_Holder->Add(Terrains_TerrainUnitID[loop], 0, wxEXPAND);
        Terrains_TerrainUnitID_Holder1->Add(Terrains_TerrainUnitID_ComboBox[loop]);
        Terrains_TerrainUnitDensity_Holder->Add(Terrains_TerrainUnitDensity[loop], 0, wxEXPAND);
        Terrains_TerrainUnitMaskedDensity_Holder->Add(Terrains_TerrainUnitMaskedDensity[loop], 0, wxEXPAND);
        Terrains_TerrainUnitPriority_Holder->Add(Terrains_TerrainUnitPriority[loop], 0, wxEXPAND);
    }
    Terrains_UsedTerrainUnits_Holder->Add(Terrains_UsedTerrainUnits_Text);
    Terrains_UsedTerrainUnits_Holder->Add(Terrains_UsedTerrainUnits);

    Terrains_NameArea_Holder->Add(Terrains_Enabled_Holder);
    Terrains_NameArea_Holder->Add(Terrains_Random_Holder, 0, wxLEFT, 5);
    Terrains_NameArea_Holder->Add(Terrains_Name_Holder, 0, wxLEFT, 5);
    Terrains_NameArea_Holder->Add(Terrains_FileName_Holder, 0, wxLEFT, 5);

    Terrains_Area1_Grid->Add(Terrains_SLP_Holder);
    Terrains_Area1_Grid->Add(Terrains_SoundID_Holder, 0, wxLEFT, 5);
    Terrains_Area1_Grid->Add(Terrains_SoundStopID_Holder, 0, wxLEFT, 5);
    Terrains_Area1_Grid->Add(Terrains_BlendPriority_Holder, 0, wxLEFT, 5);
    Terrains_Area1_Grid->Add(Terrains_BlendType_Holder, 0, wxLEFT, 5);
    Terrains_Area2_Grid->Add(Terrains_Colors_Holder);
    Terrains_Area2_Grid->Add(Terrains_CliffColors_Holder, 0, wxLEFT, 5);

    Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitID_Holder);
    Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitID_Holder1);
    Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitDensity_Holder, 0, wxLEFT, 5);
    Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitMaskedDensity_Holder);
    Terrains_TerrainUnits_Holder->Add(Terrains_TerrainUnitPriority_Holder, 0, wxLEFT, 5);

    Terrains_GridX1->Add(Terrains_TerrainReplacementID_Holder);
    Terrains_GridX1->Add(Terrains_TerrainDimensions_Holder, 0, wxLEFT, 5);
    Terrains_GridX2->Add(Terrains_StringID_Holder);
    Terrains_GridX2->Add(Terrains_IsWater_Holder);
    Terrains_GridX2->Add(Terrains_HideInEditor_Holder);
    Terrains_GridX2->Add(Terrains_ShapePtr_Holder);
    Terrains_GridX2->Add(Terrains_UsedTerrainUnits_Holder);
    Terrains_GridX2->Add(Terrains_Phantom_Holder);
    Terrains_Area2_Grid->Add(Terrains_PassableTerrain_Holder, 0, wxLEFT, 5);
    Terrains_Area2_Grid->Add(Terrains_ImpassableTerrain_Holder, 0, wxLEFT, 5);

    Terrains_SpaceRight->Add(Terrains_GridX1, 0, wxBOTTOM | wxLEFT, 5);
    Terrains_SpaceRight->Add(Terrains_GridX2, 0, wxBOTTOM | wxLEFT, 5);
    Terrains_SpaceRight->Add(Terrains_TerrainUnits_Holder, 0, wxLEFT, 5);

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
    Terrains_ScrollSpace->Add(Terrains_OverlayMaskName_Text, 0, wxTOP, 5);
    Terrains_ScrollSpace->Add(Terrains_OverlayMaskName_Holder);
    Terrains_ScrollSpace->Add(Terrains_Area1_Grid, 0, wxTOP, 5);
    Terrains_ScrollSpace->Add(Terrains_Area2_Grid, 0, wxTOP, 5);
    Terrains_ScrollSpace->Add(Terrains_GreatSpace, 0, wxEXPAND | wxTOP, 5);
    Terrains_ScrollSpace->Add(Terrains_Animation_Grid1, 0, wxTOP, 5);
    Terrains_ScrollSpace->Add(Terrains_Animation_Grid2, 0, wxTOP, 5);

    Terrains_Scroller->SetSizer(Terrains_ScrollSpace);

    Terrains_Main->Add(Terrains_Terrains, 21, wxEXPAND | wxALL, 5);
    Terrains_Main->Add(Terrains_Scroller, 65, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

    Terrains_IsWater_Holder->Show(false);
    Terrains_HideInEditor_Holder->Show(false);
    Terrains_StringID_Holder->Show(false);
    Terrains_TerrainUnitMaskedDensity_Holder->Show(false);

    Tab_Terrains->SetSizer(Terrains_Main);

    Terrains_Terrains_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainsSearch, this);
    Terrains_Terrains_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainsSearch, this);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Terrains_Terrains_UseAnd[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnTerrainsSearch, this);
        Terrains_SearchFilters[loop]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnSelection_SearchFilters, this);
    }
    Terrains_Terrains_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnTerrainSelect, this);
    Terrains_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainsAdd, this);
    Terrains_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainsDelete, this);
    Terrains_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainsCopy, this);
    Terrains_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainsPaste, this);

    Terrains_Name->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListTerrains1();
        }
    });
    Terrains_Name->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListTerrains1();
    });
    Terrains_FileName->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            wxCommandEvent e;
            OnTerrainSelect(e);
        }
    });
    Terrains_FileName->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        wxCommandEvent e;
        OnTerrainSelect(e);
    });
    Terrains_UsedCount->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnTerrainCountChange, this);
    Terrains_UsedCount->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent&)
    {
        TabBar_Main->ChangeSelection(10);
        TerRestrict_Terrains_Search->SetFocus();
    });
    Terrains_OverlayMaskName_Browse->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        wxFileDialog md(this, "Select overlay mask file", "", "", "", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if(md.ShowModal() == wxID_OK)
        {
            Terrains_OverlayMaskName->ChangeValue(md.GetFilename());
            Terrains_OverlayMaskName->SaveEdits(true);
        }
    });

    Terrains_Borders_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainsBorderSearch, this);
    Terrains_Borders_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnTerrainsBorderSearch, this);
    Terrains_Borders_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnTerrainsBorderSelect, this);
    Terrains_Borders_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainsBorderCopy, this);
    Terrains_Borders_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainsBorderPaste, this);
    Terrains_Borders_CopyToTerrains->Bind(wxEVT_BUTTON, &AGE_Frame::OnTerrainsBorderCopyToBuildings, this);
    Terrains_Border->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListTerrainsBorders();
        }
    });
    Terrains_Border->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListTerrainsBorders();
    });
    Terrains_Border_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Terrains, this);
}

void AGE_Frame::OnUpdateCombo_Terrains(wxCommandEvent &event)
{
    static_cast<LinkedComboBox*>(event.GetEventObject())->OnChoose(event);
    ListTerrainsBorders();
}
