#include "Common.h"
#include "../AGE_Frame.h"
#include "../Loaders.h"

const wxString MirrorHelp = "Angle count clockwise from east after mirroring starts.\n"
    "Angles before south are mirrored too.\nFrom the graphics scanner, if the graphic mirror is > 0,\n"
    "mirror = (angle_count >> 1) + (angle_count >> 2)";

std::vector<std::function<wxString(genie::Graphic*)>> GraphicFilterFunctions;
bool UseGraphicName;

wxString AGE_Frame::GetGraphicName(int index, bool filter)
{
    if (GenieVersion >= genie::GV_AoE && dataset->GraphicPointers[index] == 0)
    {
        return "Nonexistent";
    }
    wxString name;
    if (filter)
    {
        for (auto &f : GraphicFilterFunctions)
        {
            name += f(&dataset->Graphics[index]) + ", ";
        }
    }
    if (UseGraphicName && !dataset->Graphics[index].Name.empty())
    {
        return name + dataset->Graphics[index].Name;
    }
    if (!dataset->Graphics[index].FileName.empty())
    {
        return name + dataset->Graphics[index].FileName;
    }
    return name + "New Graphic";
}

void AGE_Frame::PrepGraphicSearch()
{
    UseGraphicName = true;
    GraphicFilterFunctions.clear();
    for (size_t loop = 0; loop < 2; ++loop)
    {
        int selection = Graphics_SearchFilters[loop]->GetSelection();
        if (selection < 1) continue;
        wxString label = graphic_filters[selection];

        if (label.compare("Sprite Name") == 0)
        {
            UseGraphicName = false;
            continue;
        }
        else if (label.compare("Particle Effect Name") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "PE " + graphic_ptr->ParticleEffectName;
        });
        else if (label.compare("Sprite") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "SLP " + FormatInt(graphic_ptr->SLP);
        });
        else if (label.compare("Disabler") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "IL " + FormatInt(graphic_ptr->IsLoaded);
        });
        else if (label.compare("Old Color Flag") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "CF " + FormatInt(graphic_ptr->OldColorFlag);
        });
        else if (label.compare("Layer") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "L " + FormatInt(graphic_ptr->Layer);
        });
        else if (label.compare("Player Color Forcer") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "PC " + FormatInt(graphic_ptr->PlayerColor);
        });
        else if (label.compare("Transparent Picking") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "TP " + FormatInt(graphic_ptr->TransparentSelection);
        });
        else if (label.compare("Sound") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "S " + FormatInt(graphic_ptr->SoundID);
        });
        else if (label.compare("Wave Works Sound") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "WS " + FormatInt(graphic_ptr->WwiseSoundID);
        });
        else if (label.compare("Coordinates") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "xy " + FormatInt(graphic_ptr->Coordinates[0])
                + " " + FormatInt(graphic_ptr->Coordinates[1])
                + " " + FormatInt(graphic_ptr->Coordinates[2])
                + " " + FormatInt(graphic_ptr->Coordinates[3]);
        });
        else if (label.compare("Delta Count") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "DC " + FormatInt(graphic_ptr->Deltas.size());
        });
        else if (label.compare("Angle Sounds Used") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "U " + FormatInt(graphic_ptr->AngleSoundsUsed);
        });
        else if (label.compare("Angle Sounds") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            wxString name;
            if (graphic_ptr->AngleSoundsUsed)
            {
                name = "AS " + FormatInt(graphic_ptr->AngleSounds[0].SoundID)
                    + ", AS " + FormatInt(graphic_ptr->AngleSounds[0].SoundID2)
                    + ", AS " + FormatInt(graphic_ptr->AngleSounds[0].SoundID3);
            }
            else
            {
                name = "None";
            }
            return name;
        });
        else if (label.compare("Angle Wave Works Sounds") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            wxString name;
            if (graphic_ptr->AngleSoundsUsed)
            {
                name = "AWS " + FormatInt(graphic_ptr->AngleSounds[0].WwiseSoundID)
                    + ", AWS " + FormatInt(graphic_ptr->AngleSounds[0].WwiseSoundID2)
                    + ", AWS " + FormatInt(graphic_ptr->AngleSounds[0].WwiseSoundID3);
            }
            else
            {
                name = "None";
            }
            return name;
        });
        else if (label.compare("Frames per Angle") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "FC " + FormatInt(graphic_ptr->FrameCount);
        });
        else if (label.compare("Angle Count") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "AC " + FormatInt(graphic_ptr->AngleCount);
        });
        else if (label.compare("New Speed") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "SM " + FormatFloat(graphic_ptr->SpeedMultiplier);
        });
        else if (label.compare("Animation Duration") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "AD " + FormatFloat(graphic_ptr->AnimationDuration);
        });
        else if (label.compare("Replay Delay") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "RD " + FormatFloat(graphic_ptr->ReplayDelay);
        });
        else if (label.compare("Sequence Type") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "ST " + FormatInt(graphic_ptr->SequenceType);
        });
        else if (label.compare("Mirroring Mode") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "M " + FormatInt(graphic_ptr->MirroringMode);
        });
        else if (label.compare("Old Editor Flag") == 0)
            GraphicFilterFunctions.push_back([this](genie::Graphic *graphic_ptr)
        {
            return "EF " + FormatInt(graphic_ptr->EditorFlag);
        });
    }
}

void AGE_Frame::OnGraphicsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListGraphics(false);
}

void AGE_Frame::ListGraphics(bool all)
{
    InitGraphics(all);
    wxCommandEvent e;
    OnGraphicSelect(e);
}

void AGE_Frame::InitGraphics(bool all)
{
    InitSearch(Graphics_Graphics_Search->GetValue().MakeLower(), Graphics_Graphics_Search_R->GetValue().MakeLower());
    SearchAnd = Graphics_Graphics_UseAnd[0]->GetValue();
    ExcludeAnd = Graphics_Graphics_UseAnd[1]->GetValue();
    PrepGraphicSearch();

    Graphics_Graphics_ListV->Sweep();
    if(all)
    {
        graphic_names.Clear();
        graphic_names.Alloc(1 + dataset->Graphics.size());
        graphic_names.Add("-1 - None");
    }

    for(size_t loop = 0; loop < dataset->Graphics.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetGraphicName(loop, true);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Graphics_Graphics_ListV->names.Add(Name);
            Graphics_Graphics_ListV->indexes.push_back(loop);
        }
        if(all) graphic_names.Add(FormatInt(loop)+" - "+GetGraphicName(loop));
    }

    RefreshList(Graphics_Graphics_ListV, &GraphicIDs);
    if (all)
    {
        for (AGEComboBox *list : GraphicComboBoxList)
        {
            list->Flash();
        }
    }

    SearchAnd = ExcludeAnd = false;
}

void AGE_Frame::OnGraphicSelect(wxCommandEvent &event)
{
    size_t selections = Graphics_Graphics_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    for (AGETextCtrl *box : uiGroupGraphic) box->clear();
    Graphics_ID->clear();
    getSelectedItems(selections, Graphics_Graphics_ListV, GraphicIDs);

    genie::Graphic *GraphicPointer = 0;
    for (size_t sel = selections; sel-- > 0;)
    {
        if (GenieVersion >= genie::GV_AoE && !dataset->GraphicPointers[GraphicIDs[sel]]) continue;
        GraphicPointer = &dataset->Graphics[GraphicIDs[sel]];

        Graphics_Name->prepend(&GraphicPointer->Name);
        Graphics_FileName->prepend(&GraphicPointer->FileName);
        if (GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap)
        {
            Graphics_FirstFrame->prepend(&GraphicPointer->FirstFrame);
        }
        Graphics_SLP->prepend(&GraphicPointer->SLP);
        Graphics_Loaded->prepend(&GraphicPointer->IsLoaded);
        Graphics_ColorFlag->prepend(&GraphicPointer->OldColorFlag);
        Graphics_DrawLevel->prepend(&GraphicPointer->Layer);
        Graphics_PlayerColor->prepend(&GraphicPointer->PlayerColor);
        Graphics_TransparentPicking->prepend(&GraphicPointer->TransparentSelection);
        for (size_t loop = 0; loop < 4; ++loop)
        {
            Graphics_Coordinates[loop]->prepend(&GraphicPointer->Coordinates[loop]);
        }
        Graphics_SoundID->prepend(&GraphicPointer->SoundID);
        if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
        {
            Graphics_ParticleEffectName->prepend(&GraphicPointer->ParticleEffectName);
            Graphics_WwiseSoundID->prepend(&GraphicPointer->WwiseSoundID);
        }
        Graphics_AngleSoundsUsed->prepend(&GraphicPointer->AngleSoundsUsed);
        Graphics_FrameCount->prepend(&GraphicPointer->FrameCount);
        Graphics_AngleCount->prepend(&GraphicPointer->AngleCount);
        Graphics_SpeedMultiplier->prepend(&GraphicPointer->SpeedMultiplier);
        Graphics_FrameDuration->prepend(&GraphicPointer->AnimationDuration);
        Graphics_ReplayDelay->prepend(&GraphicPointer->ReplayDelay);
        Graphics_SequenceType->prepend(&GraphicPointer->SequenceType);
        Graphics_ID->prepend(&GraphicPointer->ID);
        Graphics_MirroringMode->prepend(&GraphicPointer->MirroringMode);
        if (GenieVersion >= genie::GV_AoKB)
            Graphics_EditorFlag->prepend(&GraphicPointer->EditorFlag);
    }
    SetStatusText(wxString::Format("Selections: %zu    Selected graphic: %d",
        selections, selections > 0 ? GraphicIDs.front() : -1), 0);

    if (selections > 0)
    {
        selections = GenieVersion < genie::GV_AoE ? 1 : dataset->GraphicPointers[GraphicIDs.front()];
    }
    if (GraphicPointer)
    {
        int goodMirrorMode = (GraphicPointer->AngleCount >> 1) + (GraphicPointer->AngleCount >> 2);
        Graphics_MirroringMode->SetToolTip("If used, should be " +
            lexical_cast<std::string>(goodMirrorMode) + " for this sprite.\n" + MirrorHelp);
        gallery.datID = GraphicIDs.front();
        gallery.reload(); // Force reloading delta graphics.
    }
    setbearing = 1u;
    for (AGETextCtrl *box : uiGroupGraphic) box->update();

    Graphics_ID->refill();
    Deltas_Add->Enable(selections);
    ListGraphicDeltas();
    ListGraphicAngleSounds();
    if (slp_window) slp_view->Refresh();
}

void AGE_Frame::CalcDrawCenter(wxWindowBase *canvas, int &centerX, int &centerY)
{
    canvas->GetClientSize(&centerX, &centerY);
    centerX *= 0.5f / slp_zoom;
    centerY *= 0.6f / slp_zoom;
}

void AGE_Frame::OnDrawGraphicSLP(wxPaintEvent &event)
{
    APanel *canvas = static_cast<APanel*>(event.GetEventObject());
    wxBufferedPaintDC dc(canvas);
    dc.SetBackground(slp_background_brush);
    dc.Clear();
    if (!dataset)
    {
        // Nothing to draw.
        return;
    }
    dc.SetUserScale(slp_zoom, slp_zoom);
    int centerX, centerY, text_pos = 5 / slp_zoom;
    CalcDrawCenter(canvas, centerX, centerY);
    if(DrawTerrain && tileSLP.bitmap.IsOk())
    {
        dc.DrawBitmap(tileSLP.bitmap, centerX - tileSLP.xpos, centerY - tileSLP.ypos, true);
    }
    unsigned c8 = unsigned((bearing + 0.392699f) * 1.27324f) % 8u;
    unsigned c16 = unsigned((bearing + 0.19635f) * 2.54648f) % 16u;
    dc.DrawLabel("Angle "+FormatInt(c8)+"/8 "+FormatInt(c16)+"/16", wxRect((centerX << 1) - 80, text_pos, 80, 20));
    if(slp_extra_info.size())
    {
        dc.DrawLabel(slp_extra_info, wxRect(text_pos, text_pos * 6, 100, 40));
        slp_extra_info = "";
    }
    if(6 == TabBar_Main->GetSelection())
    {
        if(currentDisplay != SHOW::GRAPHIC)
        {
            currentDisplay = SHOW::GRAPHIC;
            gallery.reload();

            slp_stack->Enable(false);
            slp_annex->Enable(false);
            slp_collision->Enable(false);
            slp_clearance->Enable(false);
            slp_selection->Enable(false);
        }
    }
    else if(4 == TabBar_Main->GetSelection())
    {
        if(currentDisplay != SHOW::UNIT)
        {
            currentDisplay = SHOW::UNIT;
            museum.reload();

            slp_stack->Enable(true);
            slp_annex->Enable(true);
            slp_collision->Enable(true);
            slp_clearance->Enable(true);
            slp_selection->Enable(true);
        }
    }
    size_t spriteMemoryInUse = 0u;
    if(currentDisplay == SHOW::GRAPHIC)
    {
        if (gallery.datID >= dataset->Graphics.size() || dataset->Graphics[gallery.datID].FrameCount == 0)
        {
            dc.DrawLabel("No frames", wxRect(text_pos, text_pos, 100, 40));
            return;
        }
        if(gallery.slpID != dataset->Graphics[gallery.datID].SLP) // SLP changed
        {
            setbearing = 1u;
            bool has_base = initArt(gallery, gallery.datID);
            // SLP cache reduces reloading times.
            gallery.deltas.clear();
            // Load possible delta graphics.
            if(ShowDeltas)
            for(const genie::GraphicDelta &delta: dataset->Graphics[gallery.datID].Deltas)
            {
                AGE_SLP art;
                if(delta.GraphicID < dataset->Graphics.size())
                {
                    if(initArt(art, delta.GraphicID))
                    {
                        gallery.angles = std::max(gallery.angles, art.angles);
                    }
                    else continue;
                }
                else if(has_base)
                {
                    initArt(art, gallery.datID);
                }
                else continue;
                art.xdelta = delta.OffsetX;
                art.ydelta = delta.OffsetY;
                SetDisplayBearings(art, delta);
                gallery.deltas.emplace(std::move(std::make_pair(0, std::move(art))));
            }
        }
        DrawGraphics(dc, gallery, centerX, centerY);
        spriteMemoryInUse = gallery.getMemoryInUse();
    }
    else if(currentDisplay == SHOW::UNIT)
    {
        if (UnitCivID >= dataset->Civs.size())
        {
            return;
        }
        Pixels collision, clearance, selection;
        if(UnitIDs.size())
        {
            wxPen pen = wxPen(wxColour(255 - ViewBackR, 255 - ViewBackG, 255 - ViewBackB));
            dc.SetPen(pen);
            genie::Unit *unit = &dataset->Civs[UnitCivID].Units[UnitIDs.front()];
            if(DrawCollisionShape)
            {
                tileToPixels(unit->CollisionSize.x, unit->CollisionSize.y, collision, centerX, centerY);
                dc.DrawLine(collision.x1, collision.y1, collision.x4, collision.y4);
                dc.DrawLine(collision.x3, collision.y3, collision.x4, collision.y4);
            }
            if(DrawClearanceShape)
            {
                tileToPixels(unit->ClearanceSize.first, unit->ClearanceSize.second, clearance, centerX, centerY);
                dc.DrawLine(clearance.x1, clearance.y1, clearance.x4, clearance.y4);
                dc.DrawLine(clearance.x3, clearance.y3, clearance.x4, clearance.y4);
            }
            if(DrawOutline)
            {
                tileToPixels(unit->OutlineSize.x, unit->OutlineSize.y, selection, centerX, centerY);
                dc.DrawLine(selection.x1, selection.y1, selection.x4, selection.y4);
                dc.DrawLine(selection.x3, selection.y3, selection.x4, selection.y4);
            }
        }
        if(UnitIDs.size() == 0 || museum.datID >= dataset->Graphics.size())
        {
            dc.DrawLabel("No graphic " + FormatInt(museum.datID), wxRect(text_pos, text_pos, 100, 40));
            return;
        }
        if(museum.slpID != dataset->Graphics[museum.datID].SLP) // SLP changed
        {
            setbearing = 1u;
            initArt(museum, museum.datID);
            museum.deltas.clear();
            if(ShowDeltas)
            {
                unsigned int unitID = UnitIDs.front();
                // Load possible delta and annex graphics.
                if(dataset->Civs[UnitCivID].Units[unitID].Type == 80)
                {
                    // Start drawing from head unit instead.
                    if(ShowStack && dataset->Civs[UnitCivID].Units[unitID].Building.HeadUnit < dataset->Civs[UnitCivID].Units.size())
                        unitID = dataset->Civs[UnitCivID].Units[unitID].Building.HeadUnit;
                    // Draw this building only if it will stay up after built.
                    if(dataset->Civs[UnitCivID].Units[unitID].Building.DisappearsWhenBuilt == 0 || !ShowStack)
                    {
                        AddAnnexAndStackGraphics(unitID);
                        if(ShowAnnexes)
                        for(int i=0; i < 4; ++i)
                        CalcAnnexCoords(&dataset->Civs[UnitCivID].Units[unitID].Building.Annexes[i]);
                    }
                    if(ShowStack && dataset->Civs[UnitCivID].Units[unitID].Building.StackUnitID < dataset->Civs[UnitCivID].Units.size())
                    {
                        unitID = dataset->Civs[UnitCivID].Units[unitID].Building.StackUnitID;
                        AddAnnexAndStackGraphics(unitID);
                        if(ShowAnnexes)
                        for(int i=0; i < 4; ++i)
                        CalcAnnexCoords(&dataset->Civs[UnitCivID].Units[unitID].Building.Annexes[i]);
                    }
                }
                else AddAnnexAndStackGraphics(unitID);
                if(slp_garrison->GetValue()) // Garrison
                {
                    AddAnnexAndStackGraphics(unitID, 0, 0, 3);
                }
                if(slp_snow->GetValue()) // Snow
                {
                    AddAnnexAndStackGraphics(unitID, 0, 0, 2);
                }
                if(slp_dmg_unit->GetValue()) // Damage
                {
                    AddAnnexAndStackGraphics(unitID, 0, 0, 1);
                }
            }
        }
        DrawGraphics(dc, museum, centerX, centerY);
        spriteMemoryInUse = museum.getMemoryInUse();
        if(UnitIDs.size())
        {
            if(DrawCollisionShape)
            {
                dc.DrawLine(collision.x1, collision.y1, collision.x2, collision.y2);
                dc.DrawLine(collision.x3, collision.y3, collision.x2, collision.y2);
            }
            if(DrawClearanceShape)
            {
                dc.DrawLine(clearance.x1, clearance.y1, clearance.x2, clearance.y2);
                dc.DrawLine(clearance.x3, clearance.y3, clearance.x2, clearance.y2);
            }
            if(DrawOutline)
            {
                dc.DrawLine(selection.x1, selection.y1, selection.x2, selection.y2);
                dc.DrawLine(selection.x3, selection.y3, selection.x2, selection.y2);
            }
        }
    }
    if(DrawHot)
    {
        wxPen pen = wxPen(wxColour(255, 242, 0));
        dc.SetPen(pen);
        dc.DrawLine(centerX - 24, centerY - 12, centerX, centerY);
        dc.DrawLine(centerX + 24, centerY - 12, centerX, centerY);
        dc.DrawLine(centerX - 1, centerY + 1, centerX - 25, centerY + 13);
        dc.DrawLine(centerX + 1, centerY + 1, centerX + 25, centerY + 13);
    }
    if (GG::cache_size < spriteMemoryInUse)
    {
        // Have to delay the message.
        popUp.post(wxString::Format("Increasing cache size from %zu to %zu megabytes in order to display current sprites.",
            GG::cache_size / 1000000u, spriteMemoryInUse / 1000000u), "Warning");
        GG::cache_size = spriteMemoryInUse;
    }
}

bool AGE_Frame::initArt(AGE_SLP &art, unsigned graphicID)
{
    genie::Graphic &graphic = dataset->Graphics[graphicID];
    art.datID = graphicID;
    art.angles = graphic.AngleCount;
    art.fpa = graphic.FrameCount;
    art.mirror = graphic.MirroringMode;
    bool valid = art.angles && art.fpa;
    art.filename = valid ? graphic.FileName : "";
    art.slpID = valid ? graphic.SLP : -1;

    // Might wanna make this into another thread.
    if(PlaySounds)
    {
        initSounds(art, graphic.SoundID, 0);
        if(graphic.AngleSoundsUsed && graphic.AngleSounds.size())
        {
            // Is it worth to figure out sounds for each angle? I think not.
            art.delays[1] = graphic.AngleSounds[0].FrameNum;
            art.delays[2] = graphic.AngleSounds[0].FrameNum2;
            art.delays[3] = graphic.AngleSounds[0].FrameNum3;
            initSounds(art, graphic.AngleSounds[0].SoundID, 1);
            initSounds(art, graphic.AngleSounds[0].SoundID2, 2);
            initSounds(art, graphic.AngleSounds[0].SoundID3, 3);
        }
        else
        {
            art.buffers[1] = sf::SoundBuffer();
            art.buffers[2] = sf::SoundBuffer();
            art.buffers[3] = sf::SoundBuffer();
        }
    }

    return valid;
}

void AGE_Frame::initSounds(AGE_SLP &art, unsigned sound_num, size_t slot)
{
    if(sound_num < dataset->Sounds.size() && dataset->Sounds[sound_num].Items.size())
    {
        // TODO: Handle randomization, civ sounds.
        genie::SoundItem &sound_item = dataset->Sounds[sound_num].Items[0];
        if(LooseHD)
        {
            std::string soundname = GG::LoadSound(soundfolders, sound_item.FileName, sound_item.ResourceID);
            if("" != soundname)
            {
                if(art.buffers[slot].loadFromFile(soundname)) return;
            }
        }
        else
        {
            const unsigned char* sounddata = GG::LoadSound(datafiles, sound_item.ResourceID);
            if(0 != sounddata)
            {
                size_t size = *((uint32_t*)sounddata + 1) + 8;
                if(art.buffers[slot].loadFromMemory(sounddata, size)) return;
            }
            else // Terrain sounds may be loose files.
            {
                std::string soundname = GG::LoadSound(soundfolders, sound_item.FileName, sound_item.ResourceID);
                if("" != soundname)
                {
                    if(art.buffers[slot].loadFromFile(soundname)) return;
                }
            }
        }
    }
    // Clear the sound buffer.
    art.buffers[slot] = sf::SoundBuffer();
}

void AGE_Frame::SetDisplayBearings(AGE_SLP &graphic, const genie::GraphicDelta &delta)
{
    if(delta.DisplayAngle != -1 && graphic.angles)
    {
        float quarter = FillMissingFrames ? 1.5708f : 0.f;
        float anglesize = PI2A / graphic.angles,
            properangle = anglesize * delta.DisplayAngle - quarter;// -anglesize / 2;
        graphic.beginbearing = properangle < 0.f ? properangle + PI2A : properangle;
            properangle += anglesize;
        graphic.endbearing = properangle < 0.f ? properangle + PI2A : properangle;
    }
    else
    {
        assert(graphic.beginbearing == 0.f && graphic.endbearing == PI2A);
    }
}

void AGE_Frame::CalcAngle(AGE_SLP &graphic)
{
    float result = bearing + 3.14159f / graphic.angles;
    float bearing = result > PI2A ? result - PI2A : result;
    if(graphic.beginbearing < graphic.endbearing)
    {
        if(graphic.beginbearing > bearing || bearing > graphic.endbearing)
        {
            graphic.startframe = graphic.frameID = -0xC000;
            return;
        }
    }
    else
    {
        if(graphic.beginbearing > bearing && bearing > graphic.endbearing)
        {
            graphic.startframe = graphic.frameID = -0xC000;
            return;
        }
    }
    uint16_t angle = bearing * 0.159154f * graphic.angles;
    graphic.flip = false;
    if (FillMissingFrames && graphic.mirror)
    {
        if(angle > graphic.angles >> 1)
        {
            angle = graphic.angles - angle;
            graphic.flip = true;
        }
        else if(graphic.angles == 2)
        {
            graphic.flip = angle == 1;
            angle = 0;
        }
    }
    graphic.startframe = angle * graphic.fpa;
    graphic.frameID = setbearing == 2u ? graphic.fpa - 1 + graphic.startframe : graphic.startframe;
}

void AGE_Frame::DrawAngle(wxBufferedPaintDC &dc, int x, int y, int centerX, int centerY)
{
    dc.DrawLine(-x + centerX, -y + centerY, x + centerX, y + centerY);
    dc.DrawLine(-x + centerX, y + centerY, x + centerX, -y + centerY);
}

void AGE_Frame::DrawGraphics(wxBufferedPaintDC &dc, AGE_SLPs &spritemap, int centerX, int centerY)
{
    if(DrawAngles)
    {
        if(spritemap.angles)
        {
            uint16_t angles = spritemap.angles;
            float anglesize = PI2A / angles;
            float direction = PI2A - anglesize / 2;
            int x = sin(direction) * 512.f;
            int y = cos(direction) * 256.f;
            dc.DrawLine(-x + centerX, y + centerY, centerX, centerY);
            while(--angles > 0)
            {
                direction += anglesize;
                x = sin(direction) * 512.f;
                y = cos(direction) * 256.f;
                dc.DrawLine(-x + centerX, y + centerY, centerX, centerY);
            }
        }
    }
    bool framesleft = false;
    int text_pos = 5 / slp_zoom;
    wxRect banner(text_pos, text_pos, 100, 40);
    if(spritemap.deltas.size())
    {
        int fpms = 0x7FFF;
        wxString text = "Sprites";
        for(std::pair<const int, AGE_SLP> &delta: spritemap.deltas)
        {
            if(setbearing)
            {
                CalcAngle(delta.second);
            }
            if (LoadSLP(&delta.second))
            {
                FrameToBitmap(&delta.second);
            }
            if(delta.second.bitmap.IsOk())
            {
                int xdelta = delta.second.xdelta;
                int ydelta = delta.second.ydelta;
                if (AlexZoom[1] == '2')
                {
                    xdelta *= 2;
                    ydelta *= 2;
                }
                dc.DrawBitmap(delta.second.bitmap, centerX + delta.second.xpos + xdelta, centerY + delta.second.ypos + ydelta, true);
                if(PlaySounds)
                {
                    Listen(delta.second);
                }
                if(AnimSLP)
                {
                    fpms = std::min(fpms, ShouldAnimate(delta.second, framesleft));
                }
                text += "\n" + FormatInt(delta.second.slpID) + " " + delta.second.filename;
            }
        }
        if(AnimSLP)
        {
            animater.Start(fpms);
        }
        if (text.size() > 7)
        {
            dc.DrawLabel(text, banner);
        }
        else dc.DrawLabel("No sprites associated with " + FormatInt(spritemap.slpID) + " " + spritemap.filename, banner);
    }
    else
    {
        if(setbearing)
        {
            CalcAngle(spritemap);
        }
        if (LoadSLP(&spritemap))
        {
            FrameToBitmap(&spritemap);
        }
        if(spritemap.bitmap.IsOk())
        {
            dc.DrawBitmap(spritemap.bitmap, spritemap.xpos + centerX, spritemap.ypos + centerY, true);
            // Ideally sound starts playing after timer is running.
            if(PlaySounds)
            {
                Listen(spritemap);
            }
            if(AnimSLP)
            {
                animater.Start(ShouldAnimate(spritemap, framesleft));
            }
            dc.DrawLabel("Sprite " + FormatInt(spritemap.slpID) + " " + spritemap.filename, banner);
        }
        else dc.DrawLabel("No sprite " + FormatInt(spritemap.slpID) + " " + spritemap.filename, banner);
    }
    if(AnimSLP)
    {
        if(!framesleft && !spritemap.pause)
        {
            int rdms = dataset->Graphics[spritemap.datID].ReplayDelay * 1000;
            if(rdms)
            {
                animater.Start(rdms);
                spritemap.pause = true;
                return;
            }
        }
        HandleLastFrame(spritemap.angles, framesleft, 1u);
        spritemap.pause = false;
    }
}

void AGE_Frame::HandleLastFrame(const uint16_t angles, bool framesleft, unsigned clockwise)
{
    if (framesleft)
    {
        setbearing = 0u;
    }
    else // Switch graphics to next angle or loop this angle
    {
        if (RotateAngles)
        {
            float rotationrate = PI2;
            if (angles)
            {
                rotationrate = PI2 / angles;
            }
            if (clockwise == 1u)
            {
                bearing += rotationrate;
                if (bearing >= PI2A)
                {
                    bearing -= PI2A;
                }
            }
            else
            {
                bearing -= rotationrate;
                if (bearing < 0.f)
                {
                    bearing += PI2A;
                }
            }
        }
        setbearing = clockwise;
    }
}

int AGE_Frame::ShouldAnimate(AGE_SLP &graphic, bool &framesleft)
{
    int fpms = graphic.fpa ? dataset->Graphics[graphic.datID].AnimationDuration / graphic.fpa * 1000 : 0;
    if((graphic.frames > 1 && fpms == 0) || graphic.fpa == 1) fpms = 700;
    if(fpms) ChooseNextFrame(graphic, framesleft);
    return fpms;
}

void AGE_Frame::Listen(AGE_SLP &art)
{
    if(art.fpa) for(size_t i = 0; i < 4; ++i)
    if(art.delays[i] == art.frameID % art.fpa)
    {
        //if valid sound data?
        if(art.buffers[i].getSampleCount() > 0)
        {
            art.sounds[i].setBuffer(art.buffers[i]);
            art.sounds[i].play();
        }
    }
}

void AGE_Frame::ChooseNextFrame(AGE_SLP &graphic, bool &framesleft)
{
    int32_t nextframe = graphic.frameID + 1; // Rotate through frames.
    if(nextframe < graphic.startframe + graphic.fpa)
    {
        graphic.frameID = nextframe;
        framesleft = true;
    }
}

void AGE_Frame::ChoosePreviousFrame(AGE_SLP &graphic, bool &framesleft)
{
    int32_t prevframe = graphic.frameID - 1;
    if(prevframe >= graphic.startframe)
    {
        graphic.frameID = prevframe;
        framesleft = true;
    }
}

void AGE_Frame::OnGraphicAnim(wxTimerEvent &event)
{
    animater.Stop();
    if(slp_window)
    {
        if(slp_view->IsShownOnScreen())
        slp_view->Refresh();
        else animater.Start(1000);
    }
}

void AGE_Frame::tileToPixels(float sizeX, float sizeY, Pixels &p, int centerX, int centerY)
{
    p.x1 = centerX + dataset->TerrainBlock.TileHalfWidth * (sizeX + sizeY);
    p.y2 = centerY + dataset->TerrainBlock.TileHalfHeight * (sizeX + sizeY);
    p.x2 = centerX + dataset->TerrainBlock.TileHalfWidth * (-sizeX + sizeY);
    p.y1 = centerY + dataset->TerrainBlock.TileHalfHeight * (-sizeX + sizeY);
    p.x4 = centerX + dataset->TerrainBlock.TileHalfWidth * (sizeX - sizeY);
    p.y3 = centerY + dataset->TerrainBlock.TileHalfHeight * (sizeX - sizeY);
    p.x3 = centerX + dataset->TerrainBlock.TileHalfWidth * (-sizeX - sizeY);
    p.y4 = centerY + dataset->TerrainBlock.TileHalfHeight * (-sizeX - sizeY);
}

void AGE_Frame::OnGraphicsAdd(wxCommandEvent &event)
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    dataset->GraphicPointers.push_back(1);
    AddToListIDFix(dataset->Graphics);
    ListGraphics();
}

void AGE_Frame::OnGraphicsInsert(wxCommandEvent &event)
{
    if(!Graphics_Graphics_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    dataset->GraphicPointers.insert(dataset->GraphicPointers.begin() + GraphicIDs.front(), 1);
    InsertToListIDFix(dataset->Graphics, GraphicIDs.front());
    ListGraphics();
}

void AGE_Frame::OnGraphicsDelete(wxCommandEvent &event)
{
    if(!Graphics_Graphics_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->GraphicPointers, GraphicIDs);
    DeleteFromListIDFix(dataset->Graphics, GraphicIDs);
    ListGraphics();
}

void AGE_Frame::OnGraphicsCopy(wxCommandEvent &event)
{
    if(!Graphics_Graphics_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->GraphicPointers, GraphicIDs, copies.GraphicPointer);
    CopyFromList(dataset->Graphics, GraphicIDs, copies.Graphic);
    Graphics_Graphics_ListV->SetFocus();
}

void AGE_Frame::OnGraphicsPaste(wxCommandEvent &event)
{
    if(!Graphics_Graphics_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->GraphicPointers, GraphicIDs, copies.GraphicPointer);
    PasteToListIDFix(dataset->Graphics, GraphicIDs, copies.Graphic);
    ListGraphics();
}

void AGE_Frame::OnGraphicsPasteInsert(wxCommandEvent &event)
{
    if(!Graphics_Graphics_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->GraphicPointers, GraphicIDs.front(), copies.GraphicPointer);
    PasteInsertToListIDFix(dataset->Graphics, GraphicIDs.front(), copies.Graphic);
    ListGraphics();
}

void AGE_Frame::OnGraphicsEnable(wxCommandEvent &event)
{
    size_t selections = Graphics_Graphics_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    for(size_t loop = 0; loop < selections; ++loop)
    {
        dataset->GraphicPointers[GraphicIDs[loop]] = 1;
        dataset->Graphics[GraphicIDs[loop]].ID = GraphicIDs[loop]; // ID Fix
    }
    How2List = ListMode::ENABLE;
    ListGraphics();
}

void AGE_Frame::OnGraphicsDisable(wxCommandEvent &event)
{
    size_t selections = Graphics_Graphics_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    for(size_t loop = 0; loop < selections; ++loop)
    dataset->GraphicPointers[GraphicIDs[loop]] = 0;
    How2List = ListMode::ENABLE;
    ListGraphics();
}

wxString AGE_Frame::GetGraphicDeltaName(int index)
{
    int deltaID = dataset->Graphics[GraphicIDs.front()].Deltas[index].GraphicID;
    if(deltaID < dataset->Graphics.size())
    return lexical_cast<std::string>(deltaID) + ": " + GetGraphicName(deltaID, false);
    return "Re-drawer "+lexical_cast<std::string>(deltaID);
}

void AGE_Frame::OnGraphicDeltasSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListGraphicDeltas();
}

void AGE_Frame::ListGraphicDeltas()
{
    InitSearch(Graphics_Deltas_Search->GetValue().MakeLower(), Graphics_Deltas_Search_R->GetValue().MakeLower());

    Graphics_Deltas_ListV->Sweep();

    if(Graphics_Graphics_ListV->GetSelectedCount())
    for(size_t loop = 0; loop < dataset->Graphics[GraphicIDs.front()].Deltas.size(); ++loop)
    {
        wxString Name = FormatInt(loop)+" - "+GetGraphicDeltaName(loop);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Graphics_Deltas_ListV->names.Add(Name);
            Graphics_Deltas_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(Graphics_Deltas_ListV, &DeltaIDs);

    wxCommandEvent e;
    OnGraphicDeltaSelect(e);
}

void AGE_Frame::OnGraphicDeltaSelect(wxCommandEvent &event)
{
    size_t selections = Graphics_Deltas_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    for (AGETextCtrl *box : uiGroupGraphicDelta) box->clear();
    if(selections > 0)
    {
        getSelectedItems(selections, Graphics_Deltas_ListV, DeltaIDs);

        genie::GraphicDelta * DeltaPointer;
        for(size_t sel = selections; sel--> 0;)
        {
            DeltaPointer = &dataset->Graphics[GraphicIDs.front()].Deltas[DeltaIDs[sel]];

            GraphicDeltas_GraphicID->prepend(&DeltaPointer->GraphicID);
            GraphicDeltas_Padding1->prepend(&DeltaPointer->Padding1);
            GraphicDeltas_SpritePtr->prepend(&DeltaPointer->SpritePtr);
            GraphicDeltas_OffsetX->prepend(&DeltaPointer->OffsetX);
            GraphicDeltas_OffsetY->prepend(&DeltaPointer->OffsetY);
            GraphicDeltas_DisplayAngle->prepend(&DeltaPointer->DisplayAngle);
            GraphicDeltas_Padding2->prepend(&DeltaPointer->Padding2);
        }
    }
    for (AGETextCtrl *box : uiGroupGraphicDelta) box->update();
}

void AGE_Frame::OnGraphicDeltasAdd(wxCommandEvent &event)
{
    size_t selections = Graphics_Graphics_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->Graphics[GraphicIDs.front()].Deltas);
    gallery.reload();
    ListGraphicDeltas();
    if(slp_window && ShowDeltas) slp_view->Refresh();
}

void AGE_Frame::OnGraphicDeltasInsert(wxCommandEvent &event)
{
    size_t selections = Graphics_Deltas_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->Graphics[GraphicIDs.front()].Deltas, DeltaIDs.front());
    gallery.reload();
    ListGraphicDeltas();
    if(slp_window && ShowDeltas) slp_view->Refresh();
}

void AGE_Frame::OnGraphicDeltasDelete(wxCommandEvent &event)
{
    size_t selections = Graphics_Deltas_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->Graphics[GraphicIDs.front()].Deltas, DeltaIDs);
    gallery.reload();
    ListGraphicDeltas();
    if(slp_window && ShowDeltas) slp_view->Refresh();
}

void AGE_Frame::OnGraphicDeltasCopy(wxCommandEvent &event)
{
    size_t selections = Graphics_Deltas_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->Graphics[GraphicIDs.front()].Deltas, DeltaIDs, copies.GraphicDelta);
    Graphics_Deltas_ListV->SetFocus();
}

void AGE_Frame::OnGraphicDeltasPaste(wxCommandEvent &event)
{
    size_t selections = Graphics_Deltas_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Graphics[GraphicIDs.front()].Deltas, DeltaIDs, copies.GraphicDelta);
    gallery.reload();
    ListGraphicDeltas();
    if(slp_window && ShowDeltas) slp_view->Refresh();
}

void AGE_Frame::OnGraphicDeltasPasteInsert(wxCommandEvent &event)
{
    size_t selections = Graphics_Deltas_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->Graphics[GraphicIDs.front()].Deltas, DeltaIDs.front(), copies.GraphicDelta);
    gallery.reload();
    ListGraphicDeltas();
    if(slp_window && ShowDeltas) slp_view->Refresh();
}

void AGE_Frame::OnGraphicDeltasCopyToGraphics(wxCommandEvent &event)
{
    for(size_t loop=1; loop < GraphicIDs.size(); ++loop)
    {
        dataset->Graphics[GraphicIDs[loop]].Deltas = dataset->Graphics[GraphicIDs.front()].Deltas;
    }
}

wxString AGE_Frame::GetGraphicAngleSoundName(int index)
{
    // Sounds 1, 2, 3 - Delays 1, 2, 3
    genie::GraphicAngleSound &angle = dataset->Graphics[GraphicIDs.front()].AngleSounds[index];
    return "Sounds: "+FormatInt(angle.SoundID)+", "+FormatInt(angle.SoundID2)+", "+FormatInt(angle.SoundID3)
        +", Delays: "+FormatInt(angle.FrameNum)+", "+FormatInt(angle.FrameNum2)+", "+FormatInt(angle.FrameNum3);
}

void AGE_Frame::OnGraphicAngleSoundsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListGraphicAngleSounds();
}

void AGE_Frame::ListGraphicAngleSounds()
{
    Graphics_AngleSounds_ListV->Sweep();

    if(Graphics_Graphics_ListV->GetSelectedCount())
    for(size_t loop = 0; loop < dataset->Graphics[GraphicIDs.front()].AngleSounds.size(); ++loop)
    {
        Graphics_AngleSounds_ListV->names.Add(FormatInt(loop)+" - "+GetGraphicAngleSoundName(loop));
        Graphics_AngleSounds_ListV->indexes.push_back(loop);
    }

    RefreshList(Graphics_AngleSounds_ListV, &AttackSoundIDs);

    wxCommandEvent e;
    OnGraphicAngleSoundSelect(e);
}

void AGE_Frame::OnGraphicAngleSoundSelect(wxCommandEvent &event)
{
    size_t selections = Graphics_AngleSounds_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    for (AGETextCtrl *box : uiGroupGraphicSound) box->clear();
    if(selections > 0)
    {
        getSelectedItems(selections, Graphics_AngleSounds_ListV, AttackSoundIDs);

        genie::GraphicAngleSound * angle_ptr;
        if(AutoCopyAngles)
        for(size_t loop = dataset->Graphics[GraphicIDs.front()].AngleSounds.size(); loop--> 0;)
        {
            angle_ptr = &dataset->Graphics[GraphicIDs.front()].AngleSounds[loop];

            Graphics_AngleSoundID[0]->prepend(&angle_ptr->SoundID);
            Graphics_AngleSoundID[1]->prepend(&angle_ptr->SoundID2);
            Graphics_AngleSoundID[2]->prepend(&angle_ptr->SoundID3);
            Graphics_AngleFrameNum[0]->prepend(&angle_ptr->FrameNum);
            Graphics_AngleFrameNum[1]->prepend(&angle_ptr->FrameNum2);
            Graphics_AngleFrameNum[2]->prepend(&angle_ptr->FrameNum3);
            if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
            {
                Graphics_WwiseAngleSoundID[0]->prepend(&angle_ptr->WwiseSoundID);
                Graphics_WwiseAngleSoundID[1]->prepend(&angle_ptr->WwiseSoundID2);
                Graphics_WwiseAngleSoundID[2]->prepend(&angle_ptr->WwiseSoundID3);
            }
        }
        else for(size_t sel = selections; sel--> 0;)
        {
            angle_ptr = &dataset->Graphics[GraphicIDs.front()].AngleSounds[AttackSoundIDs[sel]];

            Graphics_AngleSoundID[0]->prepend(&angle_ptr->SoundID);
            Graphics_AngleSoundID[1]->prepend(&angle_ptr->SoundID2);
            Graphics_AngleSoundID[2]->prepend(&angle_ptr->SoundID3);
            Graphics_AngleFrameNum[0]->prepend(&angle_ptr->FrameNum);
            Graphics_AngleFrameNum[1]->prepend(&angle_ptr->FrameNum2);
            Graphics_AngleFrameNum[2]->prepend(&angle_ptr->FrameNum3);
            if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
            {
                Graphics_WwiseAngleSoundID[0]->prepend(&angle_ptr->WwiseSoundID);
                Graphics_WwiseAngleSoundID[1]->prepend(&angle_ptr->WwiseSoundID2);
                Graphics_WwiseAngleSoundID[2]->prepend(&angle_ptr->WwiseSoundID3);
            }
        }
    }
    for (AGETextCtrl *box : uiGroupGraphicSound) box->update();
}

void AGE_Frame::OnGraphicAngleSoundsCopy(wxCommandEvent &event)
{
    size_t selections = Graphics_AngleSounds_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    genie::GraphicAngleSound Copy = dataset->Graphics[GraphicIDs.front()].AngleSounds[AttackSoundIDs.front()];
    for(size_t loop2 = 0; loop2 < dataset->Graphics[GraphicIDs.front()].AngleSounds.size(); ++loop2)
    dataset->Graphics[GraphicIDs.front()].AngleSounds[loop2] = Copy;
    ListGraphicAngleSounds();
    Graphics_AngleSounds_ListV->SetFocus();
}

void AGE_Frame::OnGraphicAngleSoundsCopyToGraphics(wxCommandEvent &event)
{
    for(size_t loop=1; loop < GraphicIDs.size(); ++loop)
    {
        dataset->Graphics[GraphicIDs[loop]].AngleSounds = dataset->Graphics[GraphicIDs.front()].AngleSounds;
    }
}

void AGE_Frame::CreateGraphicsControls()
{
    Tab_Graphics = new ATabPage(TabBar_Main);
    Graphics_Main = new wxBoxSizer(wxHORIZONTAL);
    Graphics_Graphics = new wxStaticBoxSizer(wxVERTICAL, Tab_Graphics, "Sprites");

    Graphics_Graphics_Search = new wxTextCtrl(Tab_Graphics, wxID_ANY);
    Graphics_Graphics_UseAnd[0] = new wxCheckBox(Tab_Graphics, wxID_ANY, "And");
    Graphics_Graphics_Search_R = new wxTextCtrl(Tab_Graphics, wxID_ANY);
    Graphics_Graphics_UseAnd[1] = new wxCheckBox(Tab_Graphics, wxID_ANY, "And");
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Graphics_Graphics_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
        Graphics_SearchFilters[loop] = new AGEComboBox(Tab_Graphics, &graphic_filters);
    }
    Graphics_Graphics_ListV = new ProperList(Tab_Graphics, ASize(200, 100));
    Graphics_Graphics_Buttons = new wxGridSizer(3, 0, 0);
    Graphics_Add = new wxButton(Tab_Graphics, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Graphics_Insert = new wxButton(Tab_Graphics, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Graphics_Delete = new wxButton(Tab_Graphics, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Graphics_Copy = new wxButton(Tab_Graphics, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Graphics_Paste = new wxButton(Tab_Graphics, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Graphics_PasteInsert = new wxButton(Tab_Graphics, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Graphics_NoMirror = new wxButton(Tab_Graphics, wxID_ANY, "Shatter *", wxDefaultPosition, wxSize(10, -1));
    Graphics_NoMirror->SetToolTip("Export SLP file with mirrored angles saved in it.\n"
        "Remember to set mirroring mode to 0 on the graphic.");
    Graphics_Enable = new wxButton(Tab_Graphics, wxID_ANY, "Exist", wxDefaultPosition, wxSize(10, -1));
    Graphics_Disable = new wxButton(Tab_Graphics, wxID_ANY, "Wipe Out", wxDefaultPosition, wxSize(10, -1));
    Graphics_CopyToEnd = new wxButton(Tab_Graphics, wxID_ANY, "Double *", wxDefaultPosition, wxSize(10, -1));
    Graphics_CopyToEnd->SetToolTip("Duplicate selected to the end");
    Graphics_MakeLast = new wxButton(Tab_Graphics, wxID_ANY, "Relay *", wxDefaultPosition, wxSize(10, -1));
    Graphics_MakeLast->SetToolTip("Move re-drawer on deltas to the end");
    Graphics_Rename = new wxButton(Tab_Graphics, wxID_ANY, "Rename *", wxDefaultPosition, wxSize(10, -1));
    Graphics_Rename->SetToolTip("Special handy renaming button that can be customized by Tapsa");

    Graphics_Scroller = new AScrolled(Tab_Graphics);
    Graphics_ScrollSpace = new wxBoxSizer(wxVERTICAL);
    Graphics_NameArea_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_Name_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_Name_Text = new SolidText(Graphics_Scroller, " Internal Name");
    Graphics_Name = new StringControl(Graphics_Scroller, this, &uiGroupGraphic, false);
    Graphics_FileName_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_FileName_Text = new SolidText(Graphics_Scroller, " Sprite Name");
    Graphics_FileName = new StringControl(Graphics_Scroller,  this, &uiGroupGraphic, false);
    Graphics_ParticleEffectName_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_ParticleEffectName_Text = new SolidText(Graphics_Scroller, " Particle Effect Name");
    Graphics_ParticleEffectName = new StringControl(Graphics_Scroller,  this, &uiGroupGraphic);
    Graphics_ParticleEffectName_Browse = new wxButton(Graphics_Scroller, wxID_ANY, "Browse");
    Graphics_ID_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_ID_Text = new SolidText(Graphics_Scroller, " ID");
    Graphics_ID = new NumberControl(CShort, Graphics_Scroller, this, nullptr);

    Graphics_SLP_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_SLP_Text = new SolidText(Graphics_Scroller, " Sprite");
    Graphics_SLP = new NumberControl(CLong, Graphics_Scroller, this, &uiGroupGraphic, false);
    Graphics_DrawLevel_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_DrawLevel_Text = new SolidText(Graphics_Scroller, " Layer *");
    Graphics_DrawLevel = new NumberControl(CUByte, Graphics_Scroller, this, &uiGroupGraphic);
    Graphics_DrawLevel->SetToolTip("Draw Level\n0   Terrain\n5   Shadows, farms\n6   Rubble\n10   Constructions, corpses, shadows, flowers, ruins\n11   Fish\n19   Rugs, craters\n20   Buildings, units, damage flames, mill animation\n21   Blacksmith smoke\n22   Hawk\n30   Projectiles, explosions");
    Graphics_TransparentPicking_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_TransparentPicking_Text = new SolidText(Graphics_Scroller, " Transparent Pick *");
    Graphics_TransparentPicking = new NumberControl(CUByte, Graphics_Scroller, this, &uiGroupGraphic);
    Graphics_TransparentPicking->SetToolTip("0   Never select\n1   Select only on pixels\n2   Select in box");
    Graphics_ReplayDelay_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_ReplayDelay_Text = new SolidText(Graphics_Scroller, " Replay Delay *");
    Graphics_ReplayDelay = new NumberControl(CFloat, Graphics_Scroller, this, &uiGroupGraphic, false);
    Graphics_ReplayDelay->SetToolTip("Waiting time in seconds before animation restarts again");

    Graphics_FrameCount_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_FrameCount_Text = new SolidText(Graphics_Scroller, " Frames per Angle");
    Graphics_FrameCount = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphic, false);
    Graphics_FrameDuration_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_FrameDuration_Text = new SolidText(Graphics_Scroller, " Anim Duration *");
    Graphics_FrameDuration = new NumberControl(CFloat, Graphics_Scroller, this, &uiGroupGraphic, false);
    Graphics_FrameDuration->SetToolTip("How long the frames are displayed in seconds");
    Graphics_SequenceType_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_SequenceType_Text = new SolidText(Graphics_Scroller, " Sequence Type *");
    Graphics_SequenceType = new NumberControl(CUByte, Graphics_Scroller, this, &uiGroupGraphic);
    Graphics_SequenceType->SetToolTip("Combinable bit field\n0x1   Animated\n0x2   Directional\n0x4   Sprite randomized\n0x8   Loop once");
    Graphics_Type_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_Type_Text = new SolidText(Graphics_Scroller, " Mirroring Mode *");
    Graphics_MirroringMode = new NumberControl(CUByte, Graphics_Scroller, this, &uiGroupGraphic, false);
    Graphics_MirroringMode->SetToolTip(MirrorHelp);

    Graphics_SoundID_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_SoundID_Text = new SolidText(Graphics_Scroller, " Sound");
    Graphics_WwiseSoundID = new NumberControl(CULong, Graphics_Scroller, this, &uiGroupGraphic, false);
    Graphics_SoundID = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphic, false, AGETextCtrl::SMALL);
    Graphics_SoundID_ComboBox = new LinkedComboBox(Graphics_Scroller, Graphics_SoundID, &sound_names, false);
    SoundComboBoxList.push_back(Graphics_SoundID_ComboBox);
    Graphics_PlayerColor_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_PlayerColor_Text = new SolidText(Graphics_Scroller, " Forced Player Color *");
    Graphics_PlayerColor = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphic);
    Graphics_PlayerColor->SetToolTip("The player color to be forced on the graphic");
    Graphics_PlayerColor_ComboBox = new LinkedComboBox(Graphics_Scroller, Graphics_PlayerColor, &color_names);
    Graphics_SpeedMultiplier_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_SpeedMultiplier_Text = new SolidText(Graphics_Scroller, " Unit Speed Multiplier *");
    Graphics_SpeedMultiplier = new NumberControl(CFloat, Graphics_Scroller, this, &uiGroupGraphic);
    Graphics_SpeedMultiplier->SetToolTip("Multiplies the speed of the unit this graphic is applied to");

    Graphics_Coordinates_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_CoordinateGrid_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_Coordinates_Text = new SolidText(Graphics_Scroller, " Bounding Box Coordinates (X1, Y1, X2, Y2)");
    for(size_t loop = 0; loop < 4; ++loop)
    Graphics_Coordinates[loop] = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphic, true, AGETextCtrl::MEDIUM);

    Graphics_Loaded_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_Loaded_Text = new SolidText(Graphics_Scroller, " Is Loaded *");
    Graphics_Loaded = new NumberControl(CUByte, Graphics_Scroller, this, &uiGroupGraphic);
    Graphics_Loaded->SetToolTip("This variable is used, but should probably be set to 0");
    Graphics_ColorFlag_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_ColorFlag_Text = new SolidText(Graphics_Scroller, " Old Color Flag *");
    Graphics_ColorFlag = new NumberControl(CUByte, Graphics_Scroller, this, &uiGroupGraphic);
    Graphics_ColorFlag->SetToolTip("Unused");
    Graphics_EditorFlag_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_EditorFlag_Text = new SolidText(Graphics_Scroller, " Editor Flag *");
    Graphics_EditorFlag = new NumberControl(CUByte, Graphics_Scroller, this, &uiGroupGraphic);
    Graphics_EditorFlag->SetToolTip("Used for sprite editor");
    Graphics_4_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_5_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_1_Grid = new wxBoxSizer(wxHORIZONTAL);
    Graphics_2_Grid = new wxBoxSizer(wxHORIZONTAL);
    Graphics_3_Grid = new wxBoxSizer(wxHORIZONTAL);
    Graphics_Unknowns_Grid = new wxBoxSizer(wxHORIZONTAL);

    Graphics_Deltas = new wxBoxSizer(wxVERTICAL);
    Graphics_Deltas_Search = new wxTextCtrl(Graphics_Scroller, wxID_ANY);
    Graphics_Deltas_Search_R = new wxTextCtrl(Graphics_Scroller, wxID_ANY);
    Graphics_Deltas_ListV = new ProperList(Graphics_Scroller, ASize(140, 140));
    Graphics_Deltas_Buttons = new wxGridSizer(3, 0, 0);
    Deltas_Add = new wxButton(Graphics_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Deltas_Insert = new wxButton(Graphics_Scroller, wxID_ANY, "Ins New", wxDefaultPosition, wxSize(10, -1));
    Deltas_Delete = new wxButton(Graphics_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Deltas_Copy = new wxButton(Graphics_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Deltas_Paste = new wxButton(Graphics_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Deltas_PasteInsert = new wxButton(Graphics_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Deltas_CopyToGraphics = new wxButton(Graphics_Scroller, wxID_ANY, "Copy all to selected graphics", wxDefaultPosition, wxSize(10, -1));
    GraphicDeltas_GraphicID_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_GraphicID_Text = new SolidText(Graphics_Scroller, " Graphic");
    GraphicDeltas_GraphicID = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphicDelta, false);
    GraphicDeltas_GraphicID_ComboBox = new LinkedComboBox(Graphics_Scroller, GraphicDeltas_GraphicID, &graphic_names, false);
    GraphicComboBoxList.push_back(GraphicDeltas_GraphicID_ComboBox);
    wxString OffsetTip = "You can click on SLP view and use WASD to change these";
    GraphicDeltas_OffsetX_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_OffsetX_Text = new SolidText(Graphics_Scroller, " Offset X *");
    GraphicDeltas_OffsetX = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphicDelta, false);
    GraphicDeltas_OffsetX->SetToolTip(OffsetTip);
    GraphicDeltas_OffsetY_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_OffsetY_Text = new SolidText(Graphics_Scroller, " Offset Y *");
    GraphicDeltas_OffsetY = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphicDelta, false);
    GraphicDeltas_OffsetY->SetToolTip(OffsetTip);
    GraphicDeltas_DisplayAngle_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_DisplayAngle_Text = new SolidText(Graphics_Scroller, " Display Angle *");
    GraphicDeltas_DisplayAngle = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphicDelta, false);
    GraphicDeltas_DisplayAngle->SetToolTip("The angle where this delta will be displayed.\n"
        "Angle 0 is always east. Angles increase clocwise.\nIn a graphic with 8 angles would be,\n"
        "0 east, 1 south-east, 2 south, 3 south-west,\n4 west, 5 north-west, 6 north, 7 north-east.");
    GraphicDeltas_SpritePtr_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_SpritePtr_Text = new SolidText(Graphics_Scroller, " Sprite Pointer *");
    GraphicDeltas_SpritePtr = new NumberControl(CLong, Graphics_Scroller, this, &uiGroupGraphicDelta);
    GraphicDeltas_SpritePtr->SetToolTip("Is overwritten");
    GraphicDeltas_Padding1_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_Padding1_Text = new SolidText(Graphics_Scroller, " Padding 1 *");
    GraphicDeltas_Padding1 = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphicDelta);
    GraphicDeltas_Padding1->SetToolTip("Completely useless");
    GraphicDeltas_Padding2_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_Padding2_Text = new SolidText(Graphics_Scroller, " Padding 2 *");
    GraphicDeltas_Padding2 = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphicDelta);
    GraphicDeltas_Padding2->SetToolTip("Completely useless");
    Deltas_Import = new wxButton(Graphics_Scroller, wxID_ANY, "Import delta change list");

    Graphics_FirstFrame_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_FirstFrame_Text = new SolidText(Graphics_Scroller, " First Frame");
    Graphics_FirstFrame = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphic);
    Graphics_AngleCount_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_AngleCount_Text = new SolidText(Graphics_Scroller, " Angle Count *");
    Graphics_AngleCount = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphic, false);
    Graphics_AngleCount->SetToolTip("The number of directions that a unit/ship faces");
    Graphics_AngleSoundsUsed_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_AngleSoundsUsed1_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_AngleSoundsUsed_Text = new SolidText(Graphics_Scroller, " Angle Sounds Used");
    Graphics_AngleSoundsUsed = new NumberControl(CUByte, Graphics_Scroller, this, &uiGroupGraphic, false);
    Graphics_AngleSoundsUsed_CheckBox = new LinkedCheckBox(Graphics_Scroller, "Used", Graphics_AngleSoundsUsed, false);
    Graphics_AngleSounds = new wxBoxSizer(wxVERTICAL);
    Graphics_AngleSounds_ListV = new ProperList(Graphics_Scroller, ASize(240, 140));
    wxBoxSizer *AngleSounds_CopySizer = new wxBoxSizer(wxHORIZONTAL);
    AngleSounds_AutoCopy = new wxCheckBox(Graphics_Scroller, wxID_ANY, "Automatically");
    AngleSounds_Copy = new wxButton(Graphics_Scroller, wxID_ANY, "Copy to all", wxDefaultPosition, wxSize(10, -1));
    AngleSounds_CopyToGraphics = new wxButton(Graphics_Scroller, wxID_ANY, "Copy all to selected graphics", wxDefaultPosition, wxSize(10, -1));
    Graphics_AngleSounds_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_AngleSounds_Text = new SolidText(Graphics_Scroller, " Sound");
    Graphics_AngleFrameNums_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_AngleFrameNums_Text = new SolidText(Graphics_Scroller, " Frame Delay");
    for(size_t loop = 0; loop < 3; ++loop)
    {
        Graphics_WwiseAngleSoundID[loop] = new NumberControl(CULong, Graphics_Scroller, this, &uiGroupGraphicSound, false);
        Graphics_AngleSoundID[loop] = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphicSound, false, AGETextCtrl::SMALL);
        Graphics_AngleSoundID_ComboBox[loop] = new LinkedComboBox(Graphics_Scroller, Graphics_AngleSoundID[loop], &sound_names, false);
        SoundComboBoxList.push_back(Graphics_AngleSoundID_ComboBox[loop]);
        Graphics_AngleFrameNum[loop] = new NumberControl(CShort, Graphics_Scroller, this, &uiGroupGraphicSound, false);
    }

    Graphics_Deltas_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Graphics_Scroller, "Deltas");
    Graphics_Deltas_Holder_Data = new wxBoxSizer(wxVERTICAL);
    Deltas_Holder = new wxBoxSizer(wxHORIZONTAL);
    Deltas_Unknowns_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_AngleSoundArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Graphics_Scroller, "Angle Sounds");

    Graphics_Graphics_Buttons->Add(Graphics_Add, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Delete, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Insert, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Copy, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Paste, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_PasteInsert, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_NoMirror, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Enable, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Disable, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_CopyToEnd, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_MakeLast, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Rename, 1, wxEXPAND);

    Graphics_Graphics_Searches[0]->Add(Graphics_Graphics_Search, 1, wxEXPAND);
    Graphics_Graphics_Searches[0]->Add(Graphics_Graphics_UseAnd[0], 0, wxLEFT, 2);
    Graphics_Graphics_Searches[1]->Add(Graphics_Graphics_Search_R, 1, wxEXPAND);
    Graphics_Graphics_Searches[1]->Add(Graphics_Graphics_UseAnd[1], 0, wxLEFT, 2);
    for(size_t loop = 0; loop < 2; ++loop)
    Graphics_Graphics->Add(Graphics_Graphics_Searches[loop], 0, wxEXPAND);
    for(size_t loop = 0; loop < 2; ++loop)
    Graphics_Graphics->Add(Graphics_SearchFilters[loop], 0, wxEXPAND);
    Graphics_Graphics->Add(Graphics_Graphics_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Graphics_Graphics->Add(Graphics_Graphics_Buttons, 0, wxEXPAND);

    Graphics_Name_Holder->Add(Graphics_Name_Text);
    Graphics_Name_Holder->Add(Graphics_Name);
    Graphics_FileName_Holder->Add(Graphics_FileName_Text);
    Graphics_FileName_Holder->Add(Graphics_FileName);
    Graphics_ParticleEffectName_Holder->Add(Graphics_ParticleEffectName);
    Graphics_ParticleEffectName_Holder->Add(Graphics_ParticleEffectName_Browse);
    Graphics_ID_Holder->Add(Graphics_ID_Text);
    Graphics_ID_Holder->Add(Graphics_ID);
    Graphics_Loaded_Holder->Add(Graphics_Loaded_Text);
    Graphics_Loaded_Holder->Add(Graphics_Loaded);
    Graphics_ColorFlag_Holder->Add(Graphics_ColorFlag_Text);
    Graphics_ColorFlag_Holder->Add(Graphics_ColorFlag);
    Graphics_PlayerColor_Holder->Add(Graphics_PlayerColor_Text);
    Graphics_PlayerColor_Holder->Add(Graphics_PlayerColor, 0, wxEXPAND);
    Graphics_PlayerColor_Holder->Add(Graphics_PlayerColor_ComboBox);
    for(size_t loop = 0; loop < 4; ++loop)
    Graphics_CoordinateGrid_Holder->Add(Graphics_Coordinates[loop]);
    Graphics_Coordinates_Holder->Add(Graphics_Coordinates_Text);
    Graphics_Coordinates_Holder->Add(Graphics_CoordinateGrid_Holder);
    Graphics_SpeedMultiplier_Holder->Add(Graphics_SpeedMultiplier_Text);
    Graphics_SpeedMultiplier_Holder->Add(Graphics_SpeedMultiplier, 0, wxEXPAND);
    Graphics_SLP_Holder->Add(Graphics_SLP_Text);
    Graphics_SLP_Holder->Add(Graphics_SLP);
    Graphics_DrawLevel_Holder->Add(Graphics_DrawLevel_Text);
    Graphics_DrawLevel_Holder->Add(Graphics_DrawLevel);
    Graphics_TransparentPicking_Holder->Add(Graphics_TransparentPicking_Text);
    Graphics_TransparentPicking_Holder->Add(Graphics_TransparentPicking);
    Graphics_SoundID_Holder->Add(Graphics_SoundID_Text);
    wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(Graphics_SoundID, 1, wxEXPAND);
    sizer->Add(Graphics_WwiseSoundID, 2, wxEXPAND);
    Graphics_SoundID_Holder->Add(sizer, 0, wxEXPAND);
    Graphics_SoundID_Holder->Add(Graphics_SoundID_ComboBox);
    Graphics_AngleSoundsUsed1_Holder->Add(Graphics_AngleSoundsUsed);
    Graphics_AngleSoundsUsed1_Holder->Add(Graphics_AngleSoundsUsed_CheckBox, 0, wxLEFT, 2);
    Graphics_AngleSoundsUsed_Holder->Add(Graphics_AngleSoundsUsed_Text);
    Graphics_AngleSoundsUsed_Holder->Add(Graphics_AngleSoundsUsed1_Holder);
    Graphics_FrameCount_Holder->Add(Graphics_FrameCount_Text);
    Graphics_FrameCount_Holder->Add(Graphics_FrameCount);
    Graphics_AngleCount_Holder->Add(Graphics_AngleCount_Text);
    Graphics_AngleCount_Holder->Add(Graphics_AngleCount);
    Graphics_FirstFrame_Holder->Add(Graphics_FirstFrame_Text);
    Graphics_FirstFrame_Holder->Add(Graphics_FirstFrame);
    Graphics_FrameDuration_Holder->Add(Graphics_FrameDuration_Text);
    Graphics_FrameDuration_Holder->Add(Graphics_FrameDuration);
    Graphics_ReplayDelay_Holder->Add(Graphics_ReplayDelay_Text);
    Graphics_ReplayDelay_Holder->Add(Graphics_ReplayDelay);
    Graphics_SequenceType_Holder->Add(Graphics_SequenceType_Text);
    Graphics_SequenceType_Holder->Add(Graphics_SequenceType);
    Graphics_Type_Holder->Add(Graphics_Type_Text);
    Graphics_Type_Holder->Add(Graphics_MirroringMode);
    Graphics_EditorFlag_Holder->Add(Graphics_EditorFlag_Text);
    Graphics_EditorFlag_Holder->Add(Graphics_EditorFlag);

    Graphics_NameArea_Holder->Add(Graphics_Name_Holder);
    Graphics_NameArea_Holder->Add(Graphics_FileName_Holder, 0, wxLEFT, 5);
    Graphics_NameArea_Holder->Add(Graphics_ID_Holder, 0, wxLEFT, 5);

    Graphics_1_Grid->Add(Graphics_SLP_Holder);
    Graphics_1_Grid->Add(Graphics_DrawLevel_Holder, 0, wxLEFT, 5);
    Graphics_1_Grid->Add(Graphics_TransparentPicking_Holder, 0, wxLEFT, 5);
    Graphics_1_Grid->Add(Graphics_ReplayDelay_Holder, 0, wxLEFT, 5);
    Graphics_2_Grid->Add(Graphics_FrameCount_Holder);
    Graphics_2_Grid->Add(Graphics_FrameDuration_Holder, 0, wxLEFT, 5);
    Graphics_2_Grid->Add(Graphics_SequenceType_Holder, 0, wxLEFT, 5);
    Graphics_2_Grid->Add(Graphics_Type_Holder, 0, wxLEFT, 5);

    Graphics_3_Grid->Add(Graphics_SoundID_Holder);
    Graphics_3_Grid->Add(Graphics_PlayerColor_Holder, 0, wxLEFT, 5);
    Graphics_3_Grid->Add(Graphics_SpeedMultiplier_Holder, 0, wxLEFT, 5);

    Graphics_Unknowns_Grid->Add(Graphics_Loaded_Holder);
    Graphics_Unknowns_Grid->Add(Graphics_ColorFlag_Holder, 0, wxLEFT, 5);
    Graphics_Unknowns_Grid->Add(Graphics_EditorFlag_Holder, 0, wxLEFT, 5);

    Graphics_Deltas_Buttons->Add(Deltas_Add, 1, wxEXPAND);
    Graphics_Deltas_Buttons->Add(Deltas_Delete, 1, wxEXPAND);
    Graphics_Deltas_Buttons->Add(Deltas_Insert, 1, wxEXPAND);
    Graphics_Deltas_Buttons->Add(Deltas_Copy, 1, wxEXPAND);
    Graphics_Deltas_Buttons->Add(Deltas_Paste, 1, wxEXPAND);
    Graphics_Deltas_Buttons->Add(Deltas_PasteInsert, 1, wxEXPAND);

    Graphics_Deltas->Add(Graphics_Deltas_Search, 0, wxEXPAND);
    Graphics_Deltas->Add(Graphics_Deltas_Search_R, 0, wxEXPAND);
    Graphics_Deltas->Add(Graphics_Deltas_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Graphics_Deltas->Add(Graphics_Deltas_Buttons, 0, wxEXPAND);
    Graphics_Deltas->Add(Deltas_CopyToGraphics, 0, wxEXPAND | wxTOP, 2);

    GraphicDeltas_GraphicID_Holder->Add(GraphicDeltas_GraphicID_Text);
    GraphicDeltas_GraphicID_Holder->Add(GraphicDeltas_GraphicID, 0, wxEXPAND);
    GraphicDeltas_GraphicID_Holder->Add(GraphicDeltas_GraphicID_ComboBox);
    GraphicDeltas_Padding1_Holder->Add(GraphicDeltas_Padding1_Text);
    GraphicDeltas_Padding1_Holder->Add(GraphicDeltas_Padding1);
    GraphicDeltas_SpritePtr_Holder->Add(GraphicDeltas_SpritePtr_Text);
    GraphicDeltas_SpritePtr_Holder->Add(GraphicDeltas_SpritePtr);
    GraphicDeltas_OffsetX_Holder->Add(GraphicDeltas_OffsetX_Text);
    GraphicDeltas_OffsetX_Holder->Add(GraphicDeltas_OffsetX);
    GraphicDeltas_OffsetY_Holder->Add(GraphicDeltas_OffsetY_Text);
    GraphicDeltas_OffsetY_Holder->Add(GraphicDeltas_OffsetY);
    GraphicDeltas_DisplayAngle_Holder->Add(GraphicDeltas_DisplayAngle_Text);
    GraphicDeltas_DisplayAngle_Holder->Add(GraphicDeltas_DisplayAngle);
    GraphicDeltas_Padding2_Holder->Add(GraphicDeltas_Padding2_Text);
    GraphicDeltas_Padding2_Holder->Add(GraphicDeltas_Padding2);

    Deltas_Holder->Add(GraphicDeltas_GraphicID_Holder);
    Deltas_Holder->Add(GraphicDeltas_OffsetX_Holder, 0, wxLEFT, 5);
    Deltas_Holder->Add(GraphicDeltas_OffsetY_Holder, 0, wxLEFT, 5);
    Deltas_Holder->Add(GraphicDeltas_DisplayAngle_Holder, 0, wxLEFT, 5);
    Deltas_Unknowns_Holder->Add(GraphicDeltas_SpritePtr_Holder);
    Deltas_Unknowns_Holder->Add(GraphicDeltas_Padding1_Holder, 0, wxLEFT, 5);
    Deltas_Unknowns_Holder->Add(GraphicDeltas_Padding2_Holder, 0, wxLEFT, 5);
    Graphics_Deltas_Holder_Data->Add(Deltas_Holder);
    Graphics_Deltas_Holder_Data->Add(Deltas_Unknowns_Holder, 0, wxTOP, 5);
    Graphics_Deltas_Holder_Data->Add(Deltas_Import, 0, wxTOP, 5);

    Graphics_Deltas_Holder->Add(Graphics_Deltas, 1, wxEXPAND);
    Graphics_Deltas_Holder->Add(Graphics_Deltas_Holder_Data, 3, wxEXPAND | wxLEFT, 5);

    Graphics_AngleSounds->Add(Graphics_AngleSounds_ListV, 1, wxEXPAND | wxBOTTOM, 2);
    AngleSounds_CopySizer->Add(AngleSounds_AutoCopy);
    AngleSounds_CopySizer->Add(AngleSounds_Copy, 1, wxEXPAND);
    Graphics_AngleSounds->Add(AngleSounds_CopySizer, 0, wxEXPAND);
    Graphics_AngleSounds->Add(AngleSounds_CopyToGraphics, 0, wxEXPAND | wxTOP, 2);

    Graphics_AngleSounds_Holder->Add(Graphics_AngleSounds_Text);
    Graphics_AngleFrameNums_Holder->Add(Graphics_AngleFrameNums_Text);
    for(size_t loop = 0; loop < 3; ++loop)
    {
        sizer = new wxBoxSizer(wxHORIZONTAL);
        sizer->Add(Graphics_AngleSoundID[loop], 1, wxEXPAND);
        sizer->Add(Graphics_WwiseAngleSoundID[loop], 2, wxEXPAND);
        Graphics_AngleSounds_Holder->Add(sizer, 0, wxEXPAND);
        Graphics_AngleSounds_Holder->Add(Graphics_AngleSoundID_ComboBox[loop], 0, wxBOTTOM, 4);
        Graphics_AngleFrameNums_Holder->Add(Graphics_AngleFrameNum[loop], 1, wxBOTTOM, 2);
        Graphics_AngleFrameNums_Holder->Add(1, 1, 1);
    }
    Graphics_5_Holder->Add(Graphics_AngleSounds_Holder);
    Graphics_5_Holder->Add(Graphics_AngleFrameNums_Holder, 0, wxLEFT, 5);

    Graphics_4_Holder->Add(Graphics_FirstFrame_Holder, 0, wxRIGHT, 5);
    Graphics_4_Holder->Add(Graphics_AngleCount_Holder);
    Graphics_4_Holder->Add(Graphics_AngleSoundsUsed_Holder, 0, wxLEFT, 5);

    Graphics_AngleSoundArea_Holder->Add(Graphics_AngleSounds, 8, wxEXPAND);
    Graphics_AngleSoundArea_Holder->Add(Graphics_5_Holder, 13, wxEXPAND | wxLEFT, 5);

    Graphics_ScrollSpace->Add(Graphics_NameArea_Holder);
    Graphics_ScrollSpace->Add(Graphics_ParticleEffectName_Text, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_ParticleEffectName_Holder);
    Graphics_ScrollSpace->Add(Graphics_1_Grid, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_2_Grid, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_3_Grid, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_Coordinates_Holder, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_Unknowns_Grid, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_Deltas_Holder, 0, wxEXPAND | wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_4_Holder, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_AngleSoundArea_Holder, 0, wxEXPAND | wxTOP, 5);

    Graphics_Scroller->SetSizer(Graphics_ScrollSpace);

    Graphics_Main->Add(Graphics_Graphics, 21, wxEXPAND | wxALL, 5);
    Graphics_Main->Add(Graphics_Scroller, 65, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

    Graphics_ID->Enable(false);
    Graphics_FirstFrame_Holder->Show(false);

    Tab_Graphics->SetSizer(Graphics_Main);

    Graphics_Graphics_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnGraphicsSearch, this);
    Graphics_Graphics_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnGraphicsSearch, this);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Graphics_Graphics_UseAnd[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnGraphicsSearch, this);
        Graphics_SearchFilters[loop]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnSelection_SearchFilters, this);
    }
    Graphics_Graphics_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnGraphicSelect, this); // LMB
    Graphics_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsAdd, this);
    Graphics_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsInsert, this);
    Graphics_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsDelete, this);
    Graphics_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsCopy, this);
    Graphics_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsPaste, this);
    Graphics_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsPasteInsert, this);
    Graphics_NoMirror->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        if(!dataset) return;
        wxBusyCursor WaitCursor;
        // Choose folder where to save.
        wxDirDialog dd(this, wxDirSelectorPromptStr, wxGetCwd());
        if(dd.ShowModal() != wxID_OK) return;
        wxString path = dd.GetPath() + "\\";

        // Export SLP file from each selected graphic.
        for (int i : GraphicIDs)
        {
            if(dataset->Graphics[i].SLP != -1)
            {
                AGE_SLP source;
                source.slpID = dataset->Graphics[i].SLP;
                source.filename = dataset->Graphics[i].FileName;
                if (!LoadSLP(&source) || !source.slp->isSLP()) continue;
                genie::SlpFile *slp = static_cast<genie::SlpFile *>(source.slp.get());
                size_t north = dataset->Graphics[i].MirroringMode;
                wxString name = path + source.filename + ".slp";

                if(north)
                {
                    size_t south = dataset->Graphics[i].AngleCount >> 2;
                    size_t angles = dataset->Graphics[i].AngleCount;
                    size_t frames = dataset->Graphics[i].FrameCount;

                    genie::SlpFile target;
                    target.setFrameCount(angles * frames);

                    for(size_t a = 0; a < angles; ++a)
                    {
                        // Calculate the angles that need to be mirrored.
                        if(south > a || a > north)
                        {
                            source.flip = true;
                            source.frameID = (south + angles - a) % angles * frames;
                        }
                        else if(angles == 2)
                        {
                            source.flip = a == 1;
                            source.frameID = 0;
                        }
                        else
                        {
                            source.flip = false;
                            source.frameID = (a - south) * frames;
                        }
                        for(size_t f = 0; f < frames; ++f)
                        {
                            size_t frame_pos = a * frames + f;
                            try
                            {
                                genie::SlpFramePtr src_frame = slp->getFrame(source.frameID);
                                if(source.flip)
                                {
                                    target.setFrame(frame_pos, src_frame->mirrorX());
                                }
                                else
                                {
                                    target.setFrame(frame_pos, src_frame);
                                }
                            }
                            catch(const std::out_of_range&)
                            {
                                // Less frames than is displayed.
                                frames = f;
                                break;
                            }
                            ++source.frameID;
                        }
                    }

                    // Save only sprites that have content in them.
                    if(angles && frames)
                    {
                        // Set correct total frame count.
                        target.setFrameCount(angles * frames);
                        target.version = slp->version;
                        target.comment = slp->comment;
                        target.saveAs(name.c_str());
                    }
                }
                else // Nothing to mirror, save as is.
                {
                    slp->saveAs(name.c_str());
                }
            }
        }
    });
    Graphics_Enable->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsEnable, this);
    Graphics_Disable->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsDisable, this);
    Graphics_CopyToEnd->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        if(!dataset) return;
        wxBusyCursor WaitCursor;
        OnGraphicsCopy(event);
        wxString search = Graphics_Graphics_Search->GetValue();
        wxString exclude = Graphics_Graphics_Search_R->GetValue();
        Graphics_Graphics_Search->Clear();
        Graphics_Graphics_Search_R->Clear();
        OnGraphicsAdd(event);
        OnGraphicsPaste(event);
        Graphics_Graphics_Search->SetValue(search);
        Graphics_Graphics_Search_R->SetValue(exclude);
    });
    Graphics_MakeLast->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        if(!dataset) return;
        wxBusyCursor WaitCursor;
        for(size_t lg = 0; lg < GraphicIDs.size(); ++lg)
        {
            size_t d_cnt = dataset->Graphics[GraphicIDs[lg]].Deltas.size();
            // Save delta #s
            std::set<uint16_t> d_nums;
            for(size_t ld = 0; ld < d_cnt; ++ld)
            {
                d_nums.emplace(dataset->Graphics[GraphicIDs[lg]].Deltas[ld].GraphicID);
            }
            // Give back sorted
            std::vector<uint16_t> d_snums(d_nums.begin(), d_nums.end());
            for(size_t ld = 0; ld < d_cnt; ++ld)
            {
                dataset->Graphics[GraphicIDs[lg]].Deltas[ld].GraphicID = d_snums[ld];
            }
        }
    });
    Graphics_Rename->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        if(!dataset) return;
        wxString replacement;
        wxTextEntryDialog ted(this, "Enter a letter to replace the last one with", "Rename");
        if(ted.ShowModal() == wxID_OK)
        {
            replacement = ted.GetValue();
        }
        wxBusyCursor WaitCursor;
        for(size_t lg = 0; lg < GraphicIDs.size(); ++lg)
        {
            genie::Graphic &sprite = dataset->Graphics[GraphicIDs[lg]];
            sprite.Name = sprite.Name.substr(0, sprite.Name.length() - 1) + replacement;
            sprite.FileName = sprite.FileName.substr(0, sprite.FileName.length() - 1) + replacement;
        }
        ListGraphics();
    });
    Graphics_Deltas_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnGraphicDeltasSearch, this);
    Graphics_Deltas_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnGraphicDeltasSearch, this);
    Graphics_Deltas_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnGraphicDeltaSelect, this);
    Deltas_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasAdd, this);
    Deltas_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasInsert, this);
    Deltas_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasDelete, this);
    Deltas_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasCopy, this);
    Deltas_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasPaste, this);
    Deltas_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasPasteInsert, this);
    Deltas_CopyToGraphics->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasCopyToGraphics, this);
    Deltas_Import->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        wxFileDialog dd(this, "Open sprite change list", "", "tr_spred.txt",
        "Sprite editor files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if(dd.ShowModal() == wxID_OK && dataset)
        {
            wxBusyCursor WaitCursor;
            std::string line(dd.GetPath());
            std::ifstream infile(line);
            while(getline(infile, line))
            {
                wxArrayString pieces(wxStringTokenize(line, "\t"));
                for(size_t loop = 1, spriteID = static_cast<size_t>(-1), deltaID = static_cast<size_t>(-1); loop < pieces.GetCount(); ++loop)
                {
                    switch(loop)
                    {
                        case 1: // ID
                        {
                            try
                            {
                                spriteID = lexical_cast<uint32_t>(pieces[1]);
                            }
                            catch(const bad_lexical_cast&)
                            {
                                wxMessageBox(pieces[1], "Invalid sprite index");
                            }
                            if(spriteID < dataset->Graphics.size()) break;
                            else goto LINE_PARSED;
                        }
                        case 2: // Either index of the delta or the sprite number of the delta.
                        {
                            try
                            {
                                deltaID = lexical_cast<uint32_t>(pieces[2]);
                            }
                            catch(const bad_lexical_cast&)
                            {
                                wxMessageBox(pieces[2], "Invalid delta number");
                            }
                            break;
                        }
                        case 3: // Add, Delete, Change
                        {
                            switch(static_cast<char>(pieces[3][0]))
                            {
                                case 'A':
                                {
                                    if(deltaID < dataset->Graphics.size())
                                    {
                                        genie::GraphicDelta newDelta;
                                        newDelta.setGameVersion(GenieVersion);
                                        newDelta.GraphicID = deltaID;
                                        // Fixup the index of the delta for offset setting.
                                        deltaID = dataset->Graphics[spriteID].Deltas.size();
                                        dataset->Graphics[spriteID].Deltas.push_back(newDelta);
                                        break;
                                    }
                                    else
                                    {
                                        wxMessageBox(pieces[2], "Trying to add reference to nonexistent sprite!");
                                        goto LINE_PARSED;
                                    }
                                }
                                case 'D': // Delete immediately and proceed to next line.
                                {
                                    auto &deltas = dataset->Graphics[spriteID].Deltas;
                                    if(deltaID < deltas.size())
                                    {
                                        deltas.erase(deltas.begin() + deltaID);
                                    }
                                    goto LINE_PARSED;
                                }
                            }
                            break;
                        }
                        case 4: // Offset X
                        {
                            if(deltaID >= dataset->Graphics[spriteID].Deltas.size())
                            {
                                wxMessageBox(line, "Skipping nonexistent delta "+pieces[2]+"!");
                                goto LINE_PARSED;
                            }
                            try
                            {
                                dataset->Graphics[spriteID].Deltas[deltaID].OffsetX = lexical_cast<int16_t>(pieces[4]);
                            }
                            catch(const bad_lexical_cast&)
                            {
                                wxMessageBox(pieces[4], "Invalid X offset");
                            }
                            break;
                        }
                        case 5: // Offset Y
                        {
                            try // In case of missing new line.
                            {
                                dataset->Graphics[spriteID].Deltas[deltaID].OffsetY = lexical_cast<int16_t>(pieces[5]);
                            }
                            catch(const bad_lexical_cast&)
                            {
                                wxMessageBox(pieces[5], "Invalid Y offset");
                            }
                            break;
                        }
                    }
                }
                LINE_PARSED:;
            }
            // In case the currently viewed graphics was changed.
            gallery.reload();
            ListGraphicDeltas();
            if(slp_window)
            {
                slp_view->Refresh();
            }
        }
    });
    Graphics_AngleSounds_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnGraphicAngleSoundSelect, this);
    AngleSounds_AutoCopy->Bind(wxEVT_CHECKBOX, [this](wxCommandEvent &event)
    {
        AutoCopyAngles = event.IsChecked();
        AngleSounds_Copy->Enable(!AutoCopyAngles);

        wxCommandEvent e;
        OnGraphicAngleSoundSelect(e);
    });
    AngleSounds_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicAngleSoundsCopy, this);
    AngleSounds_CopyToGraphics->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicAngleSoundsCopyToGraphics, this);
    animater.Bind(wxEVT_TIMER, &AGE_Frame::OnGraphicAnim, this);

    GraphicDeltas_GraphicID_ComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent& event)
    {
        static_cast<LinkedComboBox*>(event.GetEventObject())->OnChoose(event);
        gallery.reload();
        ListGraphicDeltas();
        if (slp_window && ShowDeltas)
        {
            slp_view->Refresh();
        }
    });
    Graphics_SoundID_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Graphics, this);
    Graphics_AngleSoundsUsed_CheckBox->Bind(wxEVT_CHECKBOX, [this](wxCommandEvent& event)
    {
        static_cast<LinkedCheckBox*>(event.GetEventObject())->OnChoose(event);
        ResizeAngles();
    });

    // Need handling for both kill focus and enter events.
    Graphics_Name->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListGraphics();
        }
    });
    Graphics_Name->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListGraphics();
    });
    Graphics_FileName->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            wxCommandEvent e;
            OnGraphicSelect(e);
        }
    });
    Graphics_FileName->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        wxCommandEvent e;
        OnGraphicSelect(e);
    });
    GraphicDeltas_GraphicID->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            gallery.reload();
            ListGraphicDeltas();
            if (slp_window && ShowDeltas)
            {
                slp_view->Refresh();
            }
        }
    });
    GraphicDeltas_GraphicID->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        gallery.reload();
        ListGraphicDeltas();
        if (slp_window && ShowDeltas)
        {
            slp_view->Refresh();
        }
    });
    auto TrySaveThenResizeAngles = [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ResizeAngles();
        }
    };
    auto SaveThenResizeAngles = [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ResizeAngles();
    };
    Graphics_AngleCount->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_AngleCount->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Graphics, this);
    Graphics_AngleSoundsUsed->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_AngleSoundsUsed->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Graphics, this);
    Graphics_SLP->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_SLP->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Graphics, this);
    Graphics_FrameDuration->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_FrameDuration->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Graphics, this);
    Graphics_FrameCount->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_FrameCount->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Graphics, this);
    Graphics_ReplayDelay->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_ReplayDelay->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Graphics, this);
    Graphics_MirroringMode->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_MirroringMode->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Graphics, this);
    GraphicDeltas_OffsetX->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    GraphicDeltas_OffsetX->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Graphics, this);
    GraphicDeltas_OffsetY->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    GraphicDeltas_OffsetY->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Graphics, this);
    GraphicDeltas_DisplayAngle->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    GraphicDeltas_DisplayAngle->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Graphics, this);
    Graphics_SoundID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_SoundID->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Graphics, this);
    Graphics_WwiseSoundID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_WwiseSoundID->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Graphics, this);

    auto TrySaveThenReloadAngles = [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ReloadAngles();
        }
    };
    auto SaveThenReloadAngles = [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ReloadAngles();
    };
    for(size_t loop = 0; loop < 3; ++loop)
    {
        Graphics_AngleSoundID[loop]->Bind(wxEVT_KILL_FOCUS, TrySaveThenReloadAngles);
        Graphics_WwiseAngleSoundID[loop]->Bind(wxEVT_KILL_FOCUS, TrySaveThenReloadAngles);
        Graphics_AngleFrameNum[loop]->Bind(wxEVT_KILL_FOCUS, TrySaveThenReloadAngles);
        Graphics_AngleSoundID[loop]->Bind(wxEVT_TEXT_ENTER, SaveThenReloadAngles);
        Graphics_WwiseAngleSoundID[loop]->Bind(wxEVT_TEXT_ENTER, SaveThenReloadAngles);
        Graphics_AngleFrameNum[loop]->Bind(wxEVT_TEXT_ENTER, SaveThenReloadAngles);
        Graphics_AngleSoundID_ComboBox[loop]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Graphics, this);
    }

    Graphics_ParticleEffectName_Browse->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        wxFileDialog md(this, "Select particle effect file", "", "",
        "Particle effect files (*.json)|*.json", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if(md.ShowModal() == wxID_OK)
        {
            Graphics_ParticleEffectName->ChangeValue(md.GetFilename().BeforeLast('.'));
            Graphics_ParticleEffectName->SaveEdits(true);
        }
    });
}

void AGE_Frame::ReloadAngles()
{
    ListGraphicAngleSounds();
    if(PlaySounds)// Need to reload displaying graphic sounds.
    {
        UpdateGraphicsView();
    }
}

void AGE_Frame::ResizeAngles()
{
    if(dataset->Graphics[GraphicIDs.front()].AngleSoundsUsed != 0)
    {
        for(size_t loop = 0; loop < GraphicIDs.size(); ++loop)
        {
            genie::Graphic &graphic = dataset->Graphics[GraphicIDs[loop]];
            if(graphic.AngleSounds.size())
            {
                graphic.AngleSounds.resize(graphic.AngleCount, graphic.AngleSounds.front());
            }
            else
            {
                graphic.AngleSounds.resize(graphic.AngleCount);
            }
        }

        wxCommandEvent e;
        OnGraphicSelect(e);
    }
}

void AGE_Frame::UpdateGraphicsView(void)
{
    gallery.reload();
    if (slp_window)
    {
        slp_view->Refresh();
    }
}

void AGE_Frame::OnEnter_Graphics(wxCommandEvent &event)
{
    static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
    UpdateGraphicsView();
}

void AGE_Frame::OnKillFocus_Graphics(wxFocusEvent &event)
{
    event.Skip();
    if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
    {
        UpdateGraphicsView();
    }
}

void AGE_Frame::OnUpdateCombo_Graphics(wxCommandEvent &event)
{
    static_cast<LinkedComboBox*>(event.GetEventObject())->OnChoose(event);
    ReloadAngles();
}
