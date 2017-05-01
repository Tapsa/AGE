#include "../AGE_Frame.h"

const wxString AGE_Frame::MirrorHelp = "Angle count clockwise from east after mirroring starts?\nSeems to ignore angles before south.\nFrom the graphics scanner, if the graphic mirror is > 0,\nGraphic->Mirror = (Graphic_Angles_Count >> 1) + (Graphic_Angles_Count >> 2)";

string AGE_Frame::GetGraphicName(int index, bool Filter)
{
    string Name = "";
    if(GenieVersion >= genie::GV_AoE && dataset->GraphicPointers[index] == 0)
    {
        return "Nonexistent";
    }
    if(Filter)
    {
        short Selection[2];
        for(size_t loop = 0; loop < 2; ++loop)
        Selection[loop] = Graphics_SearchFilters[loop]->GetSelection();

        if(Selection[0] > 1) // Internal name prevents
        for(size_t loop = 0; loop < 2; ++loop)
        {
            switch(Selection[loop])
            {
                case 2: // SLP
                    Name += "SLP "+FormatInt(dataset->Graphics[index].SLP);
                    break;
                case 3: // Unknown 1
                    Name += "U1 "+FormatInt(dataset->Graphics[index].Unknown1);
                    break;
                case 4: // Unknown 2
                    Name += "CF "+FormatInt(dataset->Graphics[index].Unknown2);
                    break;
                case 5: // Layer
                    Name += "L "+FormatInt(dataset->Graphics[index].Layer);
                    break;
                case 6: // Player Color Forcer
                    Name += "PC "+FormatInt(dataset->Graphics[index].PlayerColor);
                    break;
                case 7: // Transparent Picking
                    Name += "TP "+FormatInt(dataset->Graphics[index].Replay);
                    break;
                case 8: // Sound
                    Name += "S "+FormatInt(dataset->Graphics[index].SoundID);
                    break;
                case 9: // Coordinates
                    Name += "xy "+FormatInt(dataset->Graphics[index].Coordinates[0]);
                    Name += " "+FormatInt(dataset->Graphics[index].Coordinates[1]);
                    Name += " "+FormatInt(dataset->Graphics[index].Coordinates[2]);
                    Name += " "+FormatInt(dataset->Graphics[index].Coordinates[3]);
                    break;
                case 10: // Deltas
                    Name += "DC "+FormatInt(dataset->Graphics[index].Deltas.size());
                    break;
                case 11: // Attack Sound Used
                    Name += "U "+FormatInt(dataset->Graphics[index].AttackSoundUsed);
                    break;
                case 12: // Frames
                    Name += "FC "+FormatInt(dataset->Graphics[index].FrameCount);
                    break;
                case 13: // Angles
                    Name += "AC "+FormatInt(dataset->Graphics[index].AngleCount);
                    break;
                case 14: // Speed
                    Name += "SM "+FormatFloat(dataset->Graphics[index].NewSpeed);
                    break;
                case 15: // Frame Duration
                    Name += "FD "+FormatFloat(dataset->Graphics[index].FrameRate);
                    break;
                case 16: // Replay Delay
                    Name += "RD "+FormatFloat(dataset->Graphics[index].ReplayDelay);
                    break;
                case 17: // Sequence Type
                    Name += "ST "+FormatInt(dataset->Graphics[index].SequenceType);
                    break;
                case 18: // Mirroring Mode
                    Name += "M "+FormatInt(dataset->Graphics[index].MirroringMode);
                    break;
                case 19: // Unknown 3
                    Name += "EF "+FormatInt(dataset->Graphics[index].Unknown3);
                    break;
                case 20: // Pointer
                    Name = FormatInt(dataset->GraphicPointers[index]);
                    break;
            }
            Name += ", ";
            if(Selection[loop+1] < 1) break; // Internal name breaks
        }
        if(Selection[0] == 1) goto InternalName;
    }

    if(!dataset->Graphics[index].Name.empty())
    {
        return Name + dataset->Graphics[index].Name;
    }
InternalName:
    if(!dataset->Graphics[index].Name2.empty())
    {
        return Name + dataset->Graphics[index].Name2;
    }
    return Name + "New Graphic";
}

void AGE_Frame::OnGraphicsSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListGraphics(false);
}

void AGE_Frame::ListGraphics(bool all)
{
    InitGraphics(all);
    wxTimerEvent E;
    OnGraphicsTimer(E);
}

void AGE_Frame::InitGraphics(bool all)
{
    InitSearch(Graphics_Graphics_Search->GetValue().MakeLower(), Graphics_Graphics_Search_R->GetValue().MakeLower());
    SearchAnd = Graphics_Graphics_UseAnd[0]->GetValue();
    ExcludeAnd = Graphics_Graphics_UseAnd[1]->GetValue();

    Graphics_Graphics_ListV->names.clear();
    Graphics_Graphics_ListV->indexes.clear();
    if(all)
    {
        graphic_names.Clear();
        graphic_names.Alloc(1 + dataset->Graphics.size());
        graphic_names.Add("-1 - None");
    }

    for(size_t loop = 0; loop < dataset->Graphics.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetGraphicName(loop, true);
        if(SearchMatches(Name.Lower()))
        {
            Graphics_Graphics_ListV->names.Add(Name);
            Graphics_Graphics_ListV->indexes.push_back(loop);
        }
        if(all) graphic_names.Add(" "+FormatInt(loop)+" - "+GetGraphicName(loop));
    }

    RefreshList(Graphics_Graphics_ListV, &GraphicIDs);
    if(all) for(auto &list: GraphicComboBoxList) list->Flash();

    SearchAnd = ExcludeAnd = false;
}

void AGE_Frame::OnGraphicsSelect(wxCommandEvent &event)
{
    if(!graphicTimer.IsRunning())
        graphicTimer.Start(150);
}

void AGE_Frame::OnGraphicsTimer(wxTimerEvent&)
{
    graphicTimer.Stop();
    auto selections = Graphics_Graphics_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    for(auto &box: uiGroupGraphic) box->clear();
    Graphics_ID->clear();
    if(selections > 0)
    {
        getSelectedItems(selections, Graphics_Graphics_ListV, GraphicIDs);

        genie::Graphic * GraphicPointer = 0;
        for(auto sel = selections; sel--> 0;)
        {
            GraphicPointer = &dataset->Graphics[GraphicIDs[sel]];

            Graphics_Name->prepend(&GraphicPointer->Name);
            Graphics_Name2->prepend(&GraphicPointer->Name2);
            Graphics_SLP->prepend(&GraphicPointer->SLP);
            Graphics_Loaded->prepend(&GraphicPointer->Unknown1);
            Graphics_ColorFlag->prepend(&GraphicPointer->Unknown2);
            Graphics_FrameType->prepend(&GraphicPointer->Layer);
            Graphics_PlayerColor->prepend(&GraphicPointer->PlayerColor);
            Graphics_Rainbow->prepend(&GraphicPointer->Rainbow);
            Graphics_TransparentPicking->prepend(&GraphicPointer->Replay);
            for(size_t loop = 0; loop < 4; ++loop)
            {
                Graphics_Coordinates[loop]->prepend(&GraphicPointer->Coordinates[loop]);
            }
            Graphics_SoundID->prepend(&GraphicPointer->SoundID);
            Graphics_AttackSoundUsed->prepend(&GraphicPointer->AttackSoundUsed);
            Graphics_FrameCount->prepend(&GraphicPointer->FrameCount);
            Graphics_AngleCount->prepend(&GraphicPointer->AngleCount);
            Graphics_NewSpeed->prepend(&GraphicPointer->NewSpeed);
            Graphics_FrameDuration->prepend(&GraphicPointer->FrameRate);
            Graphics_ReplayDelay->prepend(&GraphicPointer->ReplayDelay);
            Graphics_SequenceType->prepend(&GraphicPointer->SequenceType);
            Graphics_ID->prepend(&GraphicPointer->ID);
            Graphics_MirroringMode->prepend(&GraphicPointer->MirroringMode);
            if(GenieVersion >= genie::GV_AoKB)
            Graphics_EditorFlag->prepend(&GraphicPointer->Unknown3);
        }
        SetStatusText("Selections: "+lexical_cast<string>(GraphicIDs.size())+"    Selected graphic: "+lexical_cast<string>(GraphicIDs.front()), 0);

        selections = GenieVersion < genie::GV_AoE ? 1 : dataset->GraphicPointers[GraphicIDs.front()];

        if(GraphicPointer)
        {
            Graphics_MirroringMode->SetToolTip("Should be " + lexical_cast<string>((GraphicPointer->AngleCount >> 1) + (GraphicPointer->AngleCount >> 2)) + " for this sprite.\n" + MirrorHelp);
            graphicSLP.datID = GraphicIDs.front();
            graphicSLP.slpID = -2; // Force reloading delta graphics.
        }
    }
    AGE_SLP::setbearing = 1u;
    for(auto &box: uiGroupGraphic) box->update();

    Graphics_ID->refill();
    Deltas_Add->Enable(selections);
    ListGraphicDeltas();
    ListGraphicAttackSounds();
    if(slp_window) slp_view->Refresh();
}

void AGE_Frame::CalcDrawCenter(APanel *canvas, int &centerX, int &centerY)
{
    canvas->GetClientSize(&centerX, &centerY);
    centerX *= 0.5f;
    centerY *= 0.6f;
}

void AGE_Frame::OnDrawGraphicSLP(wxPaintEvent &event)
{
    APanel *canvas = static_cast<APanel*>(event.GetEventObject());
    wxBufferedPaintDC dc(canvas);
    dc.SetBackground(slp_background_brush);
    dc.Clear();
    int centerX, centerY;
    CalcDrawCenter(canvas, centerX, centerY);
    if(DrawTerrain && tileSLP.bitmap.IsOk())
    {
        dc.DrawBitmap(tileSLP.bitmap, centerX - tileSLP.xpos, centerY - tileSLP.ypos, true);
    }
    unsigned c8 = unsigned((AGE_SLP::bearing + 0.392699f) * 1.27324f) % 8u;
    unsigned c16 = unsigned((AGE_SLP::bearing + 0.19635f) * 2.54648f) % 16u;
    if(DrawAngles)
    {
        dc.SetPen(*wxRED_PEN);
        float x = 0.894427f, y = 0.447214f;
        //float x = 0.707107f, y = 0.707107f;
        float xh = (1 + x) / 2 * 345, yh = (1 + y) / 2 * 250;
        float xm = x / 2 * 250, ym = y / 2 * 345;
        dc.DrawLine(-xh + centerX, -ym + centerY, xh + centerX, ym + centerY);
        dc.DrawLine(-xh + centerX, ym + centerY, xh + centerX, -ym + centerY);
        dc.DrawLine(-xm + centerX, -yh + centerY, xm + centerX, yh + centerY);
        dc.DrawLine(-xm + centerX, yh + centerY, xm + centerX, -yh + centerY);
    }
    dc.DrawLabel("Angle "+FormatInt(c8)+"/8 "+FormatInt(c16)+"/16", wxRect(360, 5, 100, 40));
    if(slp_extra_info.size())
    {
        dc.DrawLabel(slp_extra_info, wxRect(15, 35, 100, 40));
        slp_extra_info = "";
    }
    if(6 == TabBar_Main->GetSelection())
    {
        if(AGE_SLP::currentDisplay != AGE_SLP::SHOW::GRAPHIC)
        {
            AGE_SLP::currentDisplay = AGE_SLP::SHOW::GRAPHIC;
            graphicSLP.slpID = -2;
        }
    }
    else if(4 == TabBar_Main->GetSelection())
    {
        if(AGE_SLP::currentDisplay != AGE_SLP::SHOW::UNIT)
        {
            AGE_SLP::currentDisplay = AGE_SLP::SHOW::UNIT;
            unitSLP.slpID = -2;
        }
    }
    if(AGE_SLP::currentDisplay == AGE_SLP::SHOW::GRAPHIC)
    {
        if(GraphicIDs.size() == 0 || dataset->Graphics[graphicSLP.datID].FrameCount == 0)
        {
            dc.DrawLabel("No frames", wxRect(15, 15, 100, 40));
            return;
        }
        if(graphicSLP.slpID != dataset->Graphics[graphicSLP.datID].SLP) // SLP changed
        {
            AGE_SLP::setbearing = 1u;
            graphicSLP.angleset.clear();
            bool has_base = graphicSLP.initStats(graphicSLP.datID, *dataset);
            if(has_base) graphicSLP.angleset.insert(graphicSLP.angles);
            graphicSLP.deltas.clear();
            // Load possible delta graphics.
            if(ShowDeltas)
            for(auto const &delta: dataset->Graphics[graphicSLP.datID].Deltas)
            {
                AGE_SLP deltaSLP;
                if(delta.GraphicID < dataset->Graphics.size())
                {
                    if(deltaSLP.initStats(delta.GraphicID, *dataset))
                    {
                        graphicSLP.angleset.insert(deltaSLP.angles);
                    }
                    else continue;
                }
                else if(has_base)
                {
                    deltaSLP = graphicSLP;
                }
                else continue;
                deltaSLP.xdelta = delta.DirectionX;
                deltaSLP.ydelta = delta.DirectionY;
                SetDisplayBearings(deltaSLP, delta);
                graphicSLP.deltas.insert(make_pair(0, deltaSLP));
            }
        }
        DrawGraphics(dc, graphicSLP, centerX, centerY);
    }
    else if(AGE_SLP::currentDisplay == AGE_SLP::SHOW::UNIT)
    {
        Pixels collision, clearance, selection;
        if(UnitIDs.size())
        {
            wxPen pen = wxPen(wxColour(255 - SLPbackR, 255 - SLPbackG, 255 - SLPbackB));
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
            if(DrawSelectionShape)
            {
                tileToPixels(unit->SelectionShapeSize.x, unit->SelectionShapeSize.y, selection, centerX, centerY);
                dc.DrawLine(selection.x1, selection.y1, selection.x4, selection.y4);
                dc.DrawLine(selection.x3, selection.y3, selection.x4, selection.y4);
            }
        }
        if(UnitIDs.size() == 0 || unitSLP.datID >= dataset->Graphics.size())
        {
            dc.DrawLabel("!Graphic " + FormatInt(unitSLP.datID), wxRect(15, 15, 100, 40));
            return;
        }
        if(unitSLP.slpID != dataset->Graphics[unitSLP.datID].SLP) // SLP changed
        {
            AGE_SLP::setbearing = 1u;
            unitSLP.angleset.clear();
            if(unitSLP.initStats(unitSLP.datID, *dataset))
            {
                unitSLP.angleset.insert(unitSLP.angles);
            }
            unitSLP.deltas.clear();
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
        DrawGraphics(dc, unitSLP, centerX, centerY);
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
            if(DrawSelectionShape)
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
}

bool AGE_SLP::initStats(unsigned int graphicID, genie::DatFile &dataset)
{
    datID = graphicID;
    filename = dataset.Graphics[graphicID].Name2;
    angles = dataset.Graphics[graphicID].AngleCount;
    fpa = dataset.Graphics[graphicID].FrameCount;
    slpID = angles * fpa ? dataset.Graphics[graphicID].SLP : -1;
    mirror = dataset.Graphics[graphicID].MirroringMode;
    return angles * fpa;
}

void AGE_Frame::SetDisplayBearings(AGE_SLP &graphic, const genie::GraphicDelta &delta)
{
    if(delta.DisplayAngle != -1)
    {
        float anglesize = 6.28319f / graphic.angles, properangle = anglesize * delta.DisplayAngle - 1.5708f;
        graphic.beginbearing = properangle < 0 ? properangle + 6.28319f : properangle;
        graphic.endbearing = graphic.beginbearing + anglesize;
    }
}

void AGE_Frame::CalcAngle(AGE_SLP &graphic)
{
    float correction = 3.14159f / graphic.angles, result = AGE_SLP::bearing + correction;
    float bearing = result > 6.28319f ? result - 6.28319f : result;
    if(graphic.beginbearing > bearing || bearing > graphic.endbearing)
    {
        graphic.startframe = graphic.frameID = -0xC000;
        return;
    }
    uint16_t angle = bearing * 0.159154f * graphic.angles;
    if(graphic.mirror && angle > graphic.angles >> 1)
    {
        angle = graphic.angles - angle;
        graphic.flip = true;
    }
    else graphic.flip = false;
    graphic.startframe = angle * graphic.fpa;
    graphic.frameID = AGE_SLP::setbearing == 2u ? graphic.fpa - 1 + graphic.startframe : graphic.startframe;
}

void AGE_Frame::DrawGraphics(wxBufferedPaintDC &dc, AGE_SLP &graphic, int centerX, int centerY)
{
    bool framesleft = false;
    if(graphic.deltas.size())
    {
        int fpms = 0x7FFF;
        set<uint32_t> slpIDs;
        for(auto &delta: graphic.deltas)
        {
            if(AGE_SLP::setbearing)
            {
                CalcAngle(delta.second);
            }
            SLPtoBitMap(&delta.second);
            if(delta.second.bitmap.IsOk())
            {
                dc.DrawBitmap(delta.second.bitmap, centerX + delta.second.xpos + delta.second.xdelta, centerY + delta.second.ypos + delta.second.ydelta, true);
                if(AnimSLP)
                {
                    fpms = min(fpms, ShouldAnimate(delta.second, framesleft));
                }
                slpIDs.insert(delta.second.slpID);
            }
        }
        if(AnimSLP)
        {
            graphicAnimTimer.Start(fpms);
        }
        if(slpIDs.count(-1) == slpIDs.size())
        {
            dc.DrawLabel("No SLP", wxRect(15, 15, 100, 40));
            return;
        }
        else
        {
            wxString slps = "SLPs";
            for(auto const &ID: slpIDs)
            slps += " " + FormatInt(ID);
            dc.DrawLabel(slps, wxRect(15, 15, 100, 40));
        }
    }
    else
    {
        if(graphic.slpID == -1)
        {
            dc.DrawLabel("No SLP", wxRect(15, 15, 100, 40));
            return;
        }
        if(AGE_SLP::setbearing)
        {
            CalcAngle(graphic);
        }
        SLPtoBitMap(&graphic);
        if(graphic.bitmap.IsOk())
        {
            assert(graphic.slp);
            dc.DrawBitmap(graphic.bitmap, graphic.xpos + centerX, graphic.ypos + centerY, true);
            if(AnimSLP)
            {
                graphicAnimTimer.Start(ShouldAnimate(graphic, framesleft));
            }
            dc.DrawLabel("SLP " + FormatInt(graphic.slpID) + "\n" + graphic.filename, wxRect(15, 15, 100, 40));
        }
        else dc.DrawLabel("!SLP " + FormatInt(graphic.slpID) + "\n" + graphic.filename, wxRect(15, 15, 100, 40));
    }
    if(AnimSLP)
    {
        HandleLastFrame(graphic, framesleft, 1u);
    }
}

void AGE_Frame::HandleLastFrame(const AGE_SLP &graphic, bool framesleft, unsigned clockwise)
{
    if(framesleft)
    {
        AGE_SLP::setbearing = 0u;
    }
    else // Switch graphics to next angle or loop this angle
    {
        if(slp_angles->GetValue())
        {
            float rotationrate = 6.2832f;
            if(!graphic.angleset.empty() && graphic.angleset.count(0) != graphic.angleset.size())
                rotationrate = 6.2832f / *graphic.angleset.rbegin();
            AGE_SLP::bearing = clockwise == 1u ? AGE_SLP::bearing > 6.28319f ? rotationrate : AGE_SLP::bearing + rotationrate : AGE_SLP::bearing < 0.f ? 6.28319f - rotationrate : AGE_SLP::bearing - rotationrate;
        }
        AGE_SLP::setbearing = clockwise;
    }
}

int AGE_Frame::ShouldAnimate(AGE_SLP &graphic, bool &framesleft)
{
    int fpms = dataset->Graphics[graphic.datID].FrameRate * 1000;
    if((graphic.frames > 1 && fpms == 0) || graphic.fpa == 1) fpms = 700;
    if(fpms) ChooseNextFrame(graphic, framesleft);
    return fpms;
}

void AGE_Frame::ChooseNextFrame(AGE_SLP &graphic, bool &framesleft)
{
    int32_t nextframe = graphic.frameID + 1; // Rotate through frames.
    if(nextframe < graphic.startframe + graphic.fpa)
    {
        // TODO: Mirror missing angles.
        graphic.frameID = nextframe;
        framesleft = true;
    }
}

void AGE_Frame::ChoosePreviousFrame(AGE_SLP &graphic, bool &framesleft)
{
    int32_t prevframe = graphic.frameID - 1;
    if(prevframe >= graphic.startframe)
    {
        // TODO: Mirror missing angles.
        graphic.frameID = prevframe;
        framesleft = true;
    }
}

void AGE_Frame::OnGraphicAnim(wxTimerEvent &event)
{
    graphicAnimTimer.Stop();
    if(slp_window)
    {
        if(slp_view->IsShownOnScreen())
        slp_view->Refresh();
        else graphicAnimTimer.Start(1000);
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
    auto selections = Graphics_Graphics_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    for(size_t loop = 0; loop < selections; ++loop)
    {
        dataset->GraphicPointers[GraphicIDs[loop]] = 1;
        dataset->Graphics[GraphicIDs[loop]].ID = GraphicIDs[loop]; // ID Fix
    }
    How2List = ENABLE;
    ListGraphics();
}

void AGE_Frame::OnGraphicsDisable(wxCommandEvent &event)
{
    auto selections = Graphics_Graphics_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    for(size_t loop = 0; loop < selections; ++loop)
    dataset->GraphicPointers[GraphicIDs[loop]] = 0;
    How2List = ENABLE;
    ListGraphics();
}

string AGE_Frame::GetGraphicDeltaName(int index)
{
    int deltaID = dataset->Graphics[GraphicIDs.front()].Deltas[index].GraphicID;
    if(deltaID < dataset->Graphics.size())
    return lexical_cast<string>(deltaID) + ": " + GetGraphicName(deltaID, false) + " ";
    return "Re-drawer "+lexical_cast<string>(deltaID)+" ";
}

void AGE_Frame::OnGraphicDeltasSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListGraphicDeltas();
}

void AGE_Frame::ListGraphicDeltas()
{
    InitSearch(Graphics_Deltas_Search->GetValue().MakeLower(), Graphics_Deltas_Search_R->GetValue().MakeLower());

    Graphics_Deltas_ListV->names.clear();
    Graphics_Deltas_ListV->indexes.clear();

    if(Graphics_Graphics_ListV->GetSelectedCount())
    for(size_t loop = 0; loop < dataset->Graphics[GraphicIDs.front()].Deltas.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetGraphicDeltaName(loop);
        if(SearchMatches(Name.Lower()))
        {
            Graphics_Deltas_ListV->names.Add(Name);
            Graphics_Deltas_ListV->indexes.push_back(loop);
        }
    }
    RefreshList(Graphics_Deltas_ListV, &DeltaIDs);

    wxTimerEvent E;
    OnGraphicDeltasTimer(E);
}

void AGE_Frame::OnGraphicDeltasSelect(wxCommandEvent &event)
{
    if(!deltaTimer.IsRunning())
        deltaTimer.Start(150);
}

void AGE_Frame::OnGraphicDeltasTimer(wxTimerEvent&)
{
    deltaTimer.Stop();
    auto selections = Graphics_Deltas_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    for(auto &box: uiGroupGraphicDelta) box->clear();
    if(selections > 0)
    {
        getSelectedItems(selections, Graphics_Deltas_ListV, DeltaIDs);

        genie::GraphicDelta * DeltaPointer;
        for(auto sel = selections; sel--> 0;)
        {
            DeltaPointer = &dataset->Graphics[GraphicIDs.front()].Deltas[DeltaIDs[sel]];

            GraphicDeltas_GraphicID->prepend(&DeltaPointer->GraphicID);
            GraphicDeltas_Unknown1->prepend(&DeltaPointer->Unknown1);
            GraphicDeltas_Unknown2->prepend(&DeltaPointer->Unknown2);
            GraphicDeltas_Unknown3->prepend(&DeltaPointer->Unknown3);
            GraphicDeltas_DirectionX->prepend(&DeltaPointer->DirectionX);
            GraphicDeltas_DirectionY->prepend(&DeltaPointer->DirectionY);
            GraphicDeltas_DisplayAngle->prepend(&DeltaPointer->DisplayAngle);
            GraphicDeltas_Unknown5->prepend(&DeltaPointer->Unknown5);
        }
    }
    for(auto &box: uiGroupGraphicDelta) box->update();
}

void AGE_Frame::OnGraphicDeltasAdd(wxCommandEvent &event)
{
    auto selections = Graphics_Graphics_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->Graphics[GraphicIDs.front()].Deltas);
    graphicSLP.slpID = -2;
    ListGraphicDeltas();
    if(slp_window && ShowDeltas) slp_view->Refresh();
}

void AGE_Frame::OnGraphicDeltasInsert(wxCommandEvent &event)
{
    auto selections = Graphics_Deltas_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->Graphics[GraphicIDs.front()].Deltas, DeltaIDs.front());
    graphicSLP.slpID = -2;
    ListGraphicDeltas();
    if(slp_window && ShowDeltas) slp_view->Refresh();
}

void AGE_Frame::OnGraphicDeltasDelete(wxCommandEvent &event)
{
    auto selections = Graphics_Deltas_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->Graphics[GraphicIDs.front()].Deltas, DeltaIDs);
    graphicSLP.slpID = -2;
    ListGraphicDeltas();
    if(slp_window && ShowDeltas) slp_view->Refresh();
}

void AGE_Frame::OnGraphicDeltasCopy(wxCommandEvent &event)
{
    auto selections = Graphics_Deltas_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->Graphics[GraphicIDs.front()].Deltas, DeltaIDs, copies.GraphicDelta);
    Graphics_Deltas_ListV->SetFocus();
}

void AGE_Frame::OnGraphicDeltasPaste(wxCommandEvent &event)
{
    auto selections = Graphics_Deltas_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Graphics[GraphicIDs.front()].Deltas, DeltaIDs, copies.GraphicDelta);
    graphicSLP.slpID = -2;
    ListGraphicDeltas();
    if(slp_window && ShowDeltas) slp_view->Refresh();
}

void AGE_Frame::OnGraphicDeltasPasteInsert(wxCommandEvent &event)
{
    auto selections = Graphics_Deltas_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->Graphics[GraphicIDs.front()].Deltas, DeltaIDs.front(), copies.GraphicDelta);
    graphicSLP.slpID = -2;
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

string AGE_Frame::GetGraphicAttackSoundName(int index)
{
    return "Attack sound "+lexical_cast<string>(index);
}

void AGE_Frame::OnGraphicAttackSoundsSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListGraphicAttackSounds();
}

void AGE_Frame::ListGraphicAttackSounds()
{
    Graphics_AttackSounds_ListV->names.clear();
    Graphics_AttackSounds_ListV->indexes.clear();

    if(Graphics_Graphics_ListV->GetSelectedCount())
    for(size_t loop = 0; loop < dataset->Graphics[GraphicIDs.front()].AttackSounds.size(); ++loop)
    {
        Graphics_AttackSounds_ListV->names.Add(" "+FormatInt(loop)+" - "+GetGraphicAttackSoundName(loop));
        Graphics_AttackSounds_ListV->indexes.push_back(loop);
    }

    RefreshList(Graphics_AttackSounds_ListV, &AttackSoundIDs);

    wxTimerEvent E;
    OnGraphicAttackSoundsTimer(E);
}

void AGE_Frame::OnGraphicAttackSoundsSelect(wxCommandEvent &event)
{
    if(!graphicSoundTimer.IsRunning())
        graphicSoundTimer.Start(150);
}

void AGE_Frame::OnGraphicAttackSoundsTimer(wxTimerEvent&)
{
    graphicSoundTimer.Stop();
    auto selections = Graphics_AttackSounds_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    for(auto &box: uiGroupGraphicSound) box->clear();
    if(selections > 0)
    {
        getSelectedItems(selections, Graphics_AttackSounds_ListV, AttackSoundIDs);

        genie::GraphicAttackSound * AttackSoundPointer;
        for(auto sel = selections; sel--> 0;)
        {
            AttackSoundPointer = &dataset->Graphics[GraphicIDs.front()].AttackSounds[AttackSoundIDs[sel]];

            Graphics_AttackSoundID[0]->prepend(&AttackSoundPointer->SoundID);
            Graphics_AttackSoundID[1]->prepend(&AttackSoundPointer->SoundID2);
            Graphics_AttackSoundID[2]->prepend(&AttackSoundPointer->SoundID3);
            Graphics_AttackSoundDelay[0]->prepend(&AttackSoundPointer->SoundDelay);
            Graphics_AttackSoundDelay[1]->prepend(&AttackSoundPointer->SoundDelay2);
            Graphics_AttackSoundDelay[2]->prepend(&AttackSoundPointer->SoundDelay3);
        }
    }
    for(auto &box: uiGroupGraphicSound) box->update();
}

void AGE_Frame::OnGraphicAttackSoundsCopy(wxCommandEvent &event)
{
    auto selections = Graphics_AttackSounds_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    genie::GraphicAttackSound Copy = dataset->Graphics[GraphicIDs.front()].AttackSounds[AttackSoundIDs.front()];
    for(size_t loop2 = 0; loop2 < dataset->Graphics[GraphicIDs.front()].AttackSounds.size(); ++loop2)
    dataset->Graphics[GraphicIDs.front()].AttackSounds[loop2] = Copy;
    Graphics_AttackSounds_ListV->SetFocus();
}

void AGE_Frame::OnGraphicAttackSoundsCopyToGraphics(wxCommandEvent &event)
{
    for(size_t loop=1; loop < GraphicIDs.size(); ++loop)
    {
        dataset->Graphics[GraphicIDs[loop]].AttackSounds = dataset->Graphics[GraphicIDs.front()].AttackSounds;
    }
}

void AGE_Frame::CreateGraphicsControls()
{
    Tab_Graphics = new APanel(TabBar_Main);
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
    Graphics_Graphics_ListV = new ProperList(Tab_Graphics, wxSize(200, 100));
    Graphics_Graphics_Buttons = new wxGridSizer(3, 0, 0);
    Graphics_Add = new wxButton(Tab_Graphics, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Graphics_Insert = new wxButton(Tab_Graphics, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Graphics_Delete = new wxButton(Tab_Graphics, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Graphics_Copy = new wxButton(Tab_Graphics, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Graphics_Paste = new wxButton(Tab_Graphics, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Graphics_PasteInsert = new wxButton(Tab_Graphics, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Graphics_Enable = new wxButton(Tab_Graphics, wxID_ANY, "Exist", wxDefaultPosition, wxSize(10, -1));
    Graphics_Disable = new wxButton(Tab_Graphics, wxID_ANY, "Wipe Out", wxDefaultPosition, wxSize(10, -1));

    Graphics_Scroller = new wxScrolled<APanel>(Tab_Graphics, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
    Graphics_ScrollSpace = new wxBoxSizer(wxVERTICAL);
    Graphics_NameArea_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_Name_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_Name_Text = new SolidText(Graphics_Scroller, " Name");
    Graphics_Name = AGETextCtrl::init(CString, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_Name2_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_Name2_Text = new SolidText(Graphics_Scroller, " SLP Name");
    Graphics_Name2 = AGETextCtrl::init(CString, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_ID_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_ID_Text = new SolidText(Graphics_Scroller, " ID");
    Graphics_ID = AGETextCtrl::init(CShort, 0, this, &popUp, Graphics_Scroller);

    Graphics_SLP_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_SLP_Text = new SolidText(Graphics_Scroller, " SLP");
    Graphics_SLP = AGETextCtrl::init(CLong, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_FrameType_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_FrameType_Text = new SolidText(Graphics_Scroller, " Layer *");
    Graphics_FrameType = AGETextCtrl::init(CByte, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_FrameType->SetToolTip("0 - Cliffs\n5 - Shadows, Farms\n6 - Rubble\n10 - Construction sequences, some shadows, corpses, stumps, flowers, paths, ruins, crack\n11 - Fish\n19 - Rugs, crater\n20 - Buildings, damage flames, mill animation, units\n21 - Blacksmith piece (no slp), blacksmith smoke\n22 - Hawk\n30 - Explosions, projectiles ");
    Graphics_TransparentPicking_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_TransparentPicking_Text = new SolidText(Graphics_Scroller, " Transparent Pick *");
    Graphics_TransparentPicking = AGETextCtrl::init(CByte, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_TransparentPicking->SetToolTip("0, 1, 2");
    Graphics_ReplayDelay_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_ReplayDelay_Text = new SolidText(Graphics_Scroller, " Replay Delay *");
    Graphics_ReplayDelay = AGETextCtrl::init(CFloat, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_ReplayDelay->SetToolTip("Waiting time in seconds before animation restarts again");

    Graphics_FrameCount_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_FrameCount_Text = new SolidText(Graphics_Scroller, " Frames per Angle");
    Graphics_FrameCount = AGETextCtrl::init(CUShort, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_FrameDuration_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_FrameDuration_Text = new SolidText(Graphics_Scroller, " Frame Duration *");
    Graphics_FrameDuration = AGETextCtrl::init(CFloat, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_FrameDuration->SetToolTip("How long each frame is displayed in seconds");
    Graphics_SequenceType_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_SequenceType_Text = new SolidText(Graphics_Scroller, " Sequence Type *");
    Graphics_SequenceType = AGETextCtrl::init(CByte, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_SequenceType->SetToolTip("Combinable bit field\n1 animated\n2 directional\n4 sprite randomized\n8 loop once");
    Graphics_Type_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_Type_Text = new SolidText(Graphics_Scroller, " Mirroring Mode *");
    Graphics_MirroringMode = AGETextCtrl::init(CByte, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_MirroringMode->SetToolTip(MirrorHelp);

    Graphics_SoundID_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_SoundID_Text = new SolidText(Graphics_Scroller, " Sound");
    Graphics_SoundID = AGETextCtrl::init(CShort, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_SoundID_ComboBox = new ComboBox_Plus1(Graphics_Scroller, Graphics_SoundID, &sound_names);
    SoundComboBoxList.push_back(Graphics_SoundID_ComboBox);
    Graphics_PlayerColor_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_PlayerColor_Text = new SolidText(Graphics_Scroller, " Forced Player Color *");
    Graphics_PlayerColor = AGETextCtrl::init(CByte, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_PlayerColor->SetToolTip("The player color to be forced on the graphic");
    Graphics_PlayerColor_ComboBox = new ComboBox_Plus1(Graphics_Scroller, Graphics_PlayerColor, &color_names);
    Graphics_Rainbow_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_Rainbow_Text = new SolidText(Graphics_Scroller, " Rainbow *");
    Graphics_Rainbow = AGETextCtrl::init(CByte, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_Rainbow->SetToolTip("Makes the graphic change its player color according to nearby units");
    Graphics_NewSpeed_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_NewSpeed_Text = new SolidText(Graphics_Scroller, " Unit Speed Multiplier *");
    Graphics_NewSpeed = AGETextCtrl::init(CFloat, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_NewSpeed->SetToolTip("Multiplies the speed of the unit this graphic is applied to");

    Graphics_Coordinates_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_CoordinateGrid_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_Coordinates_Text = new SolidText(Graphics_Scroller, " Coordinates");
    for(size_t loop = 0; loop < 4; ++loop)
    Graphics_Coordinates[loop] = AGETextCtrl::init(CShort, &uiGroupGraphic, this, &popUp, Graphics_Scroller, AGETextCtrl::MEDIUM);

    Graphics_Loaded_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_Loaded_Text = new SolidText(Graphics_Scroller, " Disabler");
    Graphics_Loaded = AGETextCtrl::init(CByte, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_ColorFlag_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_ColorFlag_Text = new SolidText(Graphics_Scroller, " Old Color Flag");
    Graphics_ColorFlag = AGETextCtrl::init(CByte, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_EditorFlag_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_EditorFlag_Text = new SolidText(Graphics_Scroller, " Old Editor Flag *");
    Graphics_EditorFlag = AGETextCtrl::init(CByte, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_EditorFlag->SetToolTip("Was related to sprite editor?");
    Graphics_4_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_5_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_1_Grid = new wxBoxSizer(wxHORIZONTAL);
    Graphics_2_Grid = new wxBoxSizer(wxHORIZONTAL);
    Graphics_3_Grid = new wxBoxSizer(wxHORIZONTAL);
    Graphics_Unknowns_Grid = new wxBoxSizer(wxHORIZONTAL);

    Graphics_Deltas = new wxBoxSizer(wxVERTICAL);
    Graphics_Deltas_Search = new wxTextCtrl(Graphics_Scroller, wxID_ANY);
    Graphics_Deltas_Search_R = new wxTextCtrl(Graphics_Scroller, wxID_ANY);
    Graphics_Deltas_ListV = new ProperList(Graphics_Scroller, wxSize(140, 140));
    Graphics_Deltas_Buttons = new wxGridSizer(3, 0, 0);
    Deltas_Add = new wxButton(Graphics_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Deltas_Insert = new wxButton(Graphics_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Deltas_Delete = new wxButton(Graphics_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Deltas_Copy = new wxButton(Graphics_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    Deltas_Paste = new wxButton(Graphics_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Deltas_PasteInsert = new wxButton(Graphics_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Deltas_CopyToGraphics = new wxButton(Graphics_Scroller, wxID_ANY, "Copy all to selected graphics", wxDefaultPosition, wxSize(10, -1));
    GraphicDeltas_GraphicID_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_GraphicID_Text = new SolidText(Graphics_Scroller, " Graphic");
    GraphicDeltas_GraphicID = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, &popUp, Graphics_Scroller);
    GraphicDeltas_GraphicID_ComboBox = new ComboBox_Plus1(Graphics_Scroller, GraphicDeltas_GraphicID, &graphic_names);
    GraphicComboBoxList.push_back(GraphicDeltas_GraphicID_ComboBox);
    GraphicDeltas_DirectionX_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_DirectionX_Text = new SolidText(Graphics_Scroller, " Direction X");
    GraphicDeltas_DirectionX = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, &popUp, Graphics_Scroller);
    GraphicDeltas_DirectionY_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_DirectionY_Text = new SolidText(Graphics_Scroller, " Direction Y");
    GraphicDeltas_DirectionY = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, &popUp, Graphics_Scroller);
    GraphicDeltas_DisplayAngle_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_DisplayAngle_Text = new SolidText(Graphics_Scroller, " Display Angle *");
    GraphicDeltas_DisplayAngle = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, &popUp, Graphics_Scroller);
    GraphicDeltas_DisplayAngle->SetToolTip("The angle where this delta will be displayed.\nAngle 0 is always east. Angles increase clocwise."
    "In a graphic with 8 angles, 0 would mean east, 1 south-east, 2 south,\n3 south-west, 4 west, 5 north-west, 6 north, 7 north-east.\n");
    GraphicDeltas_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_Unknown1_Text = new SolidText(Graphics_Scroller, " Unknown 1");
    GraphicDeltas_Unknown1 = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, &popUp, Graphics_Scroller);
    GraphicDeltas_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_Unknown2_Text = new SolidText(Graphics_Scroller, " Sprite Pointer");
    GraphicDeltas_Unknown2 = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, &popUp, Graphics_Scroller);
    GraphicDeltas_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_Unknown3_Text = new SolidText(Graphics_Scroller, " (Sprite Pointer)");
    GraphicDeltas_Unknown3 = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, &popUp, Graphics_Scroller);
    GraphicDeltas_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
    GraphicDeltas_Unknown5_Text = new SolidText(Graphics_Scroller, " Unknown 5");
    GraphicDeltas_Unknown5 = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, &popUp, Graphics_Scroller);

    Graphics_AngleCount_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_AngleCount_Text = new SolidText(Graphics_Scroller, " Angle Count *");
    Graphics_AngleCount = AGETextCtrl::init(CUShort, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_AngleCount->SetToolTip("The number of directions that a unit/ship faces");
    Graphics_AttackSoundUsed_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_AttackSoundUsed1_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_AttackSoundUsed_Text = new SolidText(Graphics_Scroller, " Attack Sound Used");
    Graphics_AttackSoundUsed = AGETextCtrl::init(CByte, &uiGroupGraphic, this, &popUp, Graphics_Scroller);
    Graphics_AttackSoundUsed_CheckBox = new CheckBox_2State(Graphics_Scroller, "Used", Graphics_AttackSoundUsed);
    Graphics_AttackSounds = new wxBoxSizer(wxVERTICAL);
    Graphics_AttackSounds_ListV = new ProperList(Graphics_Scroller, wxSize(140, 140));
    AttackSounds_Copy = new wxButton(Graphics_Scroller, wxID_ANY, "Copy to all", wxDefaultPosition, wxSize(10, -1));
    AttackSounds_CopyToGraphics = new wxButton(Graphics_Scroller, wxID_ANY, "Copy all to selected graphics", wxDefaultPosition, wxSize(10, -1));
    Graphics_AttackSounds_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_AttackSounds_Text = new SolidText(Graphics_Scroller, " Sound");
    Graphics_AttackSoundDelays_Holder = new wxBoxSizer(wxVERTICAL);
    Graphics_AttackSoundDelays_Text = new SolidText(Graphics_Scroller, " Sound Delay");
    for(size_t loop = 0; loop < 3; ++loop)
    {
        Graphics_AttackSoundID[loop] = AGETextCtrl::init(CShort, &uiGroupGraphicSound, this, &popUp, Graphics_Scroller);
        Graphics_AttackSoundID_ComboBox[loop] = new ComboBox_Plus1(Graphics_Scroller, Graphics_AttackSoundID[loop], &sound_names);
        SoundComboBoxList.push_back(Graphics_AttackSoundID_ComboBox[loop]);
        Graphics_AttackSoundDelay[loop] = AGETextCtrl::init(CShort, &uiGroupGraphicSound, this, &popUp, Graphics_Scroller);
    }

    Graphics_Deltas_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Graphics_Scroller, "Deltas");
    Graphics_Deltas_Holder_Data = new wxBoxSizer(wxVERTICAL);
    Deltas_Holder = new wxBoxSizer(wxHORIZONTAL);
    Deltas_Unknowns_Holder = new wxBoxSizer(wxHORIZONTAL);
    Graphics_AttackSoundArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Graphics_Scroller, "Attack Sounds");

    graphic_filters.Add("Internal Name");  // 0
    graphic_filters.Add("SLP Name");
    graphic_filters.Add("SLP");
    graphic_filters.Add("Disabler");
    graphic_filters.Add("Old Color Flag");
    graphic_filters.Add("Layer");
    graphic_filters.Add("Player Color Forcer");
    graphic_filters.Add("Transparent Picking");
    graphic_filters.Add("Sound");
    graphic_filters.Add("Coordinates");
    graphic_filters.Add("Delta Count");
    graphic_filters.Add("Attack Sound Used");
    graphic_filters.Add("Frames per Angle");
    graphic_filters.Add("Angle Count");
    graphic_filters.Add("New Speed");
    graphic_filters.Add("Frame Duration");
    graphic_filters.Add("Replay Delay");
    graphic_filters.Add("Sequence Type");
    graphic_filters.Add("Mirroring Mode");
    graphic_filters.Add("Old Editor Flag");
    graphic_filters.Add("Pointer");
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Graphics_SearchFilters[loop]->Flash();
    }

    Graphics_Graphics_Buttons->Add(Graphics_Add, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Delete, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Insert, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Copy, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Paste, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_PasteInsert, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Enable, 1, wxEXPAND);
    Graphics_Graphics_Buttons->Add(Graphics_Disable, 1, wxEXPAND);

    Graphics_Graphics_Searches[0]->Add(Graphics_Graphics_Search, 1, wxEXPAND);
    Graphics_Graphics_Searches[0]->Add(Graphics_Graphics_UseAnd[0], 0, wxEXPAND | wxLEFT, 2);
    Graphics_Graphics_Searches[1]->Add(Graphics_Graphics_Search_R, 1, wxEXPAND);
    Graphics_Graphics_Searches[1]->Add(Graphics_Graphics_UseAnd[1], 0, wxEXPAND | wxLEFT, 2);
    for(size_t loop = 0; loop < 2; ++loop)
    Graphics_Graphics->Add(Graphics_Graphics_Searches[loop], 0, wxEXPAND);
    for(size_t loop = 0; loop < 2; ++loop)
    Graphics_Graphics->Add(Graphics_SearchFilters[loop], 0, wxEXPAND);
    Graphics_Graphics->Add(Graphics_Graphics_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Graphics_Graphics->Add(Graphics_Graphics_Buttons, 0, wxEXPAND);

    Graphics_Name_Holder->Add(Graphics_Name_Text);
    Graphics_Name_Holder->Add(Graphics_Name, 0, wxEXPAND);
    Graphics_Name2_Holder->Add(Graphics_Name2_Text);
    Graphics_Name2_Holder->Add(Graphics_Name2, 0, wxEXPAND);
    Graphics_ID_Holder->Add(Graphics_ID_Text);
    Graphics_ID_Holder->Add(Graphics_ID, 0, wxEXPAND);
    Graphics_Loaded_Holder->Add(Graphics_Loaded_Text);
    Graphics_Loaded_Holder->Add(Graphics_Loaded, 0, wxEXPAND);
    Graphics_ColorFlag_Holder->Add(Graphics_ColorFlag_Text);
    Graphics_ColorFlag_Holder->Add(Graphics_ColorFlag, 0, wxEXPAND);
    Graphics_PlayerColor_Holder->Add(Graphics_PlayerColor_Text);
    Graphics_PlayerColor_Holder->Add(Graphics_PlayerColor, 0, wxEXPAND);
    Graphics_PlayerColor_Holder->Add(Graphics_PlayerColor_ComboBox);
    Graphics_Rainbow_Holder->Add(Graphics_Rainbow_Text);
    Graphics_Rainbow_Holder->Add(Graphics_Rainbow, 0, wxEXPAND);
    for(size_t loop = 0; loop < 4; ++loop)
    Graphics_CoordinateGrid_Holder->Add(Graphics_Coordinates[loop]);
    Graphics_Coordinates_Holder->Add(Graphics_Coordinates_Text);
    Graphics_Coordinates_Holder->Add(Graphics_CoordinateGrid_Holder);
    Graphics_NewSpeed_Holder->Add(Graphics_NewSpeed_Text);
    Graphics_NewSpeed_Holder->Add(Graphics_NewSpeed, 0, wxEXPAND);
    Graphics_SLP_Holder->Add(Graphics_SLP_Text);
    Graphics_SLP_Holder->Add(Graphics_SLP, 0, wxEXPAND);
    Graphics_FrameType_Holder->Add(Graphics_FrameType_Text);
    Graphics_FrameType_Holder->Add(Graphics_FrameType, 0, wxEXPAND);
    Graphics_TransparentPicking_Holder->Add(Graphics_TransparentPicking_Text);
    Graphics_TransparentPicking_Holder->Add(Graphics_TransparentPicking, 0, wxEXPAND);
    Graphics_SoundID_Holder->Add(Graphics_SoundID_Text);
    Graphics_SoundID_Holder->Add(Graphics_SoundID, 0, wxEXPAND);
    Graphics_SoundID_Holder->Add(Graphics_SoundID_ComboBox);
    Graphics_AttackSoundUsed1_Holder->Add(Graphics_AttackSoundUsed, 0, wxEXPAND);
    Graphics_AttackSoundUsed1_Holder->Add(Graphics_AttackSoundUsed_CheckBox, 0, wxLEFT, 2);
    Graphics_AttackSoundUsed_Holder->Add(Graphics_AttackSoundUsed_Text);
    Graphics_AttackSoundUsed_Holder->Add(Graphics_AttackSoundUsed1_Holder, 0, wxEXPAND);
    Graphics_FrameCount_Holder->Add(Graphics_FrameCount_Text);
    Graphics_FrameCount_Holder->Add(Graphics_FrameCount, 0, wxEXPAND);
    Graphics_AngleCount_Holder->Add(Graphics_AngleCount_Text);
    Graphics_AngleCount_Holder->Add(Graphics_AngleCount, 0, wxEXPAND);
    Graphics_FrameDuration_Holder->Add(Graphics_FrameDuration_Text);
    Graphics_FrameDuration_Holder->Add(Graphics_FrameDuration, 0, wxEXPAND);
    Graphics_ReplayDelay_Holder->Add(Graphics_ReplayDelay_Text);
    Graphics_ReplayDelay_Holder->Add(Graphics_ReplayDelay, 0, wxEXPAND);
    Graphics_SequenceType_Holder->Add(Graphics_SequenceType_Text);
    Graphics_SequenceType_Holder->Add(Graphics_SequenceType, 0, wxEXPAND);
    Graphics_Type_Holder->Add(Graphics_Type_Text);
    Graphics_Type_Holder->Add(Graphics_MirroringMode, 0, wxEXPAND);
    Graphics_EditorFlag_Holder->Add(Graphics_EditorFlag_Text);
    Graphics_EditorFlag_Holder->Add(Graphics_EditorFlag, 0, wxEXPAND);

    Graphics_NameArea_Holder->Add(Graphics_Name_Holder);
    Graphics_NameArea_Holder->Add(Graphics_Name2_Holder, 0, wxLEFT, 5);
    Graphics_NameArea_Holder->Add(Graphics_ID_Holder, 0, wxLEFT, 5);

    Graphics_1_Grid->Add(Graphics_SLP_Holder);
    Graphics_1_Grid->Add(Graphics_FrameType_Holder, 0, wxLEFT, 5);
    Graphics_1_Grid->Add(Graphics_TransparentPicking_Holder, 0, wxLEFT, 5);
    Graphics_1_Grid->Add(Graphics_ReplayDelay_Holder, 0, wxLEFT, 5);
    Graphics_2_Grid->Add(Graphics_FrameCount_Holder);
    Graphics_2_Grid->Add(Graphics_FrameDuration_Holder, 0, wxLEFT, 5);
    Graphics_2_Grid->Add(Graphics_SequenceType_Holder, 0, wxLEFT, 5);
    Graphics_2_Grid->Add(Graphics_Type_Holder, 0, wxLEFT, 5);

    Graphics_3_Grid->Add(Graphics_SoundID_Holder);
    Graphics_3_Grid->Add(Graphics_PlayerColor_Holder, 0, wxLEFT, 5);
    Graphics_3_Grid->Add(Graphics_Rainbow_Holder, 0, wxLEFT, 5);
    Graphics_3_Grid->Add(Graphics_NewSpeed_Holder, 0, wxLEFT, 5);

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
    GraphicDeltas_Unknown1_Holder->Add(GraphicDeltas_Unknown1_Text);
    GraphicDeltas_Unknown1_Holder->Add(GraphicDeltas_Unknown1, 0, wxEXPAND);
    GraphicDeltas_Unknown2_Holder->Add(GraphicDeltas_Unknown2_Text);
    GraphicDeltas_Unknown2_Holder->Add(GraphicDeltas_Unknown2, 0, wxEXPAND);
    GraphicDeltas_Unknown3_Holder->Add(GraphicDeltas_Unknown3_Text);
    GraphicDeltas_Unknown3_Holder->Add(GraphicDeltas_Unknown3, 0, wxEXPAND);
    GraphicDeltas_DirectionX_Holder->Add(GraphicDeltas_DirectionX_Text);
    GraphicDeltas_DirectionX_Holder->Add(GraphicDeltas_DirectionX, 0, wxEXPAND);
    GraphicDeltas_DirectionY_Holder->Add(GraphicDeltas_DirectionY_Text);
    GraphicDeltas_DirectionY_Holder->Add(GraphicDeltas_DirectionY, 0, wxEXPAND);
    GraphicDeltas_DisplayAngle_Holder->Add(GraphicDeltas_DisplayAngle_Text);
    GraphicDeltas_DisplayAngle_Holder->Add(GraphicDeltas_DisplayAngle, 0, wxEXPAND);
    GraphicDeltas_Unknown5_Holder->Add(GraphicDeltas_Unknown5_Text);
    GraphicDeltas_Unknown5_Holder->Add(GraphicDeltas_Unknown5, 0, wxEXPAND);

    Deltas_Holder->Add(GraphicDeltas_GraphicID_Holder);
    Deltas_Holder->Add(GraphicDeltas_DirectionX_Holder, 0, wxLEFT, 5);
    Deltas_Holder->Add(GraphicDeltas_DirectionY_Holder, 0, wxLEFT, 5);
    Deltas_Holder->Add(GraphicDeltas_DisplayAngle_Holder, 0, wxLEFT, 5);
    Deltas_Unknowns_Holder->Add(GraphicDeltas_Unknown1_Holder);
    Deltas_Unknowns_Holder->Add(GraphicDeltas_Unknown2_Holder, 0, wxLEFT, 5);
    Deltas_Unknowns_Holder->Add(GraphicDeltas_Unknown3_Holder, 0, wxLEFT, 5);
    Deltas_Unknowns_Holder->Add(GraphicDeltas_Unknown5_Holder, 0, wxLEFT, 5);
    Graphics_Deltas_Holder_Data->Add(Deltas_Holder);
    Graphics_Deltas_Holder_Data->Add(Deltas_Unknowns_Holder, 0, wxTOP, 5);

    Graphics_Deltas_Holder->Add(Graphics_Deltas, 1, wxEXPAND);
    Graphics_Deltas_Holder->Add(Graphics_Deltas_Holder_Data, 3, wxEXPAND | wxLEFT, 5);

    Graphics_AttackSounds->Add(Graphics_AttackSounds_ListV, 1, wxEXPAND | wxBOTTOM, 2);
    Graphics_AttackSounds->Add(AttackSounds_Copy, 0, wxEXPAND);
    Graphics_AttackSounds->Add(AttackSounds_CopyToGraphics, 0, wxEXPAND | wxTOP, 2);

    Graphics_AttackSounds_Holder->Add(Graphics_AttackSounds_Text);
    Graphics_AttackSoundDelays_Holder->Add(Graphics_AttackSoundDelays_Text);
    for(size_t loop = 0; loop < 3; ++loop)
    {
        Graphics_AttackSounds_Holder->Add(Graphics_AttackSoundID[loop], 0, wxEXPAND);
        Graphics_AttackSounds_Holder->Add(Graphics_AttackSoundID_ComboBox[loop], 0, wxBOTTOM, 4);
        Graphics_AttackSoundDelays_Holder->Add(Graphics_AttackSoundDelay[loop], 1, wxBOTTOM, 2);
        Graphics_AttackSoundDelays_Holder->Add(1, 1, 1);
    }
    Graphics_5_Holder->Add(Graphics_AttackSounds_Holder);
    Graphics_5_Holder->Add(Graphics_AttackSoundDelays_Holder, 0, wxLEFT, 5);

    Graphics_4_Holder->Add(Graphics_AngleCount_Holder);
    Graphics_4_Holder->Add(Graphics_AttackSoundUsed_Holder, 0, wxLEFT, 5);

    Graphics_AttackSoundArea_Holder->Add(Graphics_AttackSounds, 1, wxEXPAND);
    Graphics_AttackSoundArea_Holder->Add(Graphics_5_Holder, 3, wxEXPAND | wxLEFT, 5);

    Graphics_ScrollSpace->Add(Graphics_NameArea_Holder);
    Graphics_ScrollSpace->Add(Graphics_1_Grid, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_2_Grid, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_3_Grid, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_Coordinates_Holder, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_Unknowns_Grid, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_Deltas_Holder, 0, wxEXPAND | wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_4_Holder, 0, wxTOP, 5);
    Graphics_ScrollSpace->Add(Graphics_AttackSoundArea_Holder, 0, wxEXPAND | wxTOP, 5);

    Graphics_Scroller->SetSizer(Graphics_ScrollSpace);
    Graphics_Scroller->SetScrollRate(0, 15);

    Graphics_Main->Add(Graphics_Graphics, 21, wxEXPAND | wxALL, 5);
    Graphics_Main->Add(Graphics_Scroller, 65, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

    if(EnableIDFix)
    Graphics_ID->Enable(false);

    Tab_Graphics->SetSizer(Graphics_Main);

    Graphics_Graphics_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnGraphicsSearch, this);
    Graphics_Graphics_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnGraphicsSearch, this);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Graphics_Graphics_UseAnd[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnGraphicsSearch, this);
        Graphics_SearchFilters[loop]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnSelection_SearchFilters, this);
    }
    Graphics_Graphics_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnGraphicsSelect, this); // LMB
    Graphics_Graphics_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnGraphicsSelect, this); // CTRL
    Graphics_Graphics_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnGraphicsSelect, this); // SHIFT
    Graphics_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsAdd, this);
    Graphics_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsInsert, this);
    Graphics_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsDelete, this);
    Graphics_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsCopy, this);
    Graphics_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsPaste, this);
    Graphics_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsPasteInsert, this);
    Graphics_Enable->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsEnable, this);
    Graphics_Disable->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicsDisable, this);
    Graphics_Deltas_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnGraphicDeltasSearch, this);
    Graphics_Deltas_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnGraphicDeltasSearch, this);
    Graphics_Deltas_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnGraphicDeltasSelect, this);
    Graphics_Deltas_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnGraphicDeltasSelect, this);
    Graphics_Deltas_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnGraphicDeltasSelect, this);
    Deltas_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasAdd, this);
    Deltas_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasInsert, this);
    Deltas_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasDelete, this);
    Deltas_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasCopy, this);
    Deltas_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasPaste, this);
    Deltas_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasPasteInsert, this);
    Deltas_CopyToGraphics->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicDeltasCopyToGraphics, this);
    Graphics_AttackSounds_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnGraphicAttackSoundsSelect, this);
    Graphics_AttackSounds_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnGraphicAttackSoundsSelect, this);
    Graphics_AttackSounds_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnGraphicAttackSoundsSelect, this);
    AttackSounds_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicAttackSoundsCopy, this);
    AttackSounds_CopyToGraphics->Bind(wxEVT_BUTTON, &AGE_Frame::OnGraphicAttackSoundsCopyToGraphics, this);

    graphicTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnGraphicsTimer, this);
    deltaTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnGraphicDeltasTimer, this);
    graphicSoundTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnGraphicAttackSoundsTimer, this);
    Graphics_Name->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_Name2->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    GraphicDeltas_GraphicID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    GraphicDeltas_GraphicID_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Graphics, this);
    Graphics_AngleCount->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_AttackSoundUsed->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_AttackSoundUsed_CheckBox->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnUpdateCheck_Graphics, this);

    graphicAnimTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnGraphicAnim, this);
    Graphics_SLP->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_FrameDuration->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_FrameCount->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_ReplayDelay->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    Graphics_MirroringMode->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    GraphicDeltas_DirectionX->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    GraphicDeltas_DirectionY->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
    GraphicDeltas_DisplayAngle->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Graphics, this);
}

void AGE_Frame::OnKillFocus_Graphics(wxFocusEvent &event)
{
    event.Skip();
    if(static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() != 0) return;
    if(event.GetId() == Graphics_Name->GetId())
    {
        ListGraphics();
    }
    else if(event.GetId() == GraphicDeltas_GraphicID->GetId())
    {
        graphicSLP.slpID = -2;
        ListGraphicDeltas();
        if(slp_window && ShowDeltas) slp_view->Refresh();
    }
    else if(event.GetId() == Graphics_Name2->GetId())
    {
        wxTimerEvent E;
        OnGraphicsTimer(E);
    }
    else if(event.GetId() == Graphics_AngleCount->GetId() || event.GetId() == Graphics_AttackSoundUsed->GetId())
    {
        if(dataset->Graphics[GraphicIDs.front()].AttackSoundUsed == 0) return;

        for(size_t loop = 0; loop < GraphicIDs.size(); ++loop)
        dataset->Graphics[GraphicIDs[loop]].AttackSounds.resize(dataset->Graphics[GraphicIDs[loop]].AngleCount);

        wxTimerEvent E;
        OnGraphicsTimer(E);
    }
    else
    {
        graphicSLP.slpID = -2;
        if(slp_window) slp_view->Refresh();
    }
}

void AGE_Frame::OnUpdateCheck_Graphics(wxCommandEvent &event)
{
    static_cast<CheckBox_2State*>(event.GetEventObject())->OnChoose(event);
    if(dataset->Graphics[GraphicIDs.front()].AttackSoundUsed == 0) return;

    for(size_t loop = 0; loop < GraphicIDs.size(); ++loop)
    dataset->Graphics[GraphicIDs[loop]].AttackSounds.resize(dataset->Graphics[GraphicIDs[loop]].AngleCount);

    wxTimerEvent E;
    OnGraphicsTimer(E);
}

void AGE_Frame::OnUpdateCombo_Graphics(wxCommandEvent &event)
{
    static_cast<ComboBox_Plus1*>(event.GetEventObject())->OnChoose(event);
    graphicSLP.slpID = -2;
    ListGraphicDeltas();
    if(slp_window && ShowDeltas) slp_view->Refresh();
}
