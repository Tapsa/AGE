#include "../AGE_Frame.h"

string AGE_Frame::GetGraphicName(int index, bool Filter)
{
	string Name = "";
	if(GenieVersion >= genie::GV_AoE && dataset->GraphicPointers[index] == 0)
	{
		return "*Disabled*";
	}
	if(Filter)
	{
		short Selection[2];
		for(short loop = 0; loop < 2; ++loop)
		Selection[loop] = Graphics_SearchFilters[loop]->GetSelection();

		if(Selection[0] > 1) // Internal name prevents
		for(short loop = 0; loop < 2; ++loop)
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
					Name += "U2 "+FormatInt(dataset->Graphics[index].Unknown2);
					break;
				case 5: // Layer
					Name += "L "+FormatInt(dataset->Graphics[index].Layer);
					break;
				case 6: // Player Color Forcer
					Name += "PC "+FormatInt(dataset->Graphics[index].PlayerColor);
					break;
				case 7: // Replay
					Name += "R "+FormatInt(dataset->Graphics[index].Replay);
					break;
				case 8: // Sound
					Name += "So "+FormatInt(dataset->Graphics[index].SoundID);
					break;
				case 9: // Coordinates
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
					Name += "Sp "+FormatFloat(dataset->Graphics[index].NewSpeed);
					break;
				case 15: // Frame Rate
					Name += "FR "+FormatFloat(dataset->Graphics[index].FrameRate);
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
					Name += "U3 "+FormatInt(dataset->Graphics[index].Unknown3);
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
	searchText = Graphics_Graphics_Search->GetValue().Lower();
	excludeText = Graphics_Graphics_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = Graphics_Graphics_UseAnd[loop]->GetValue();

    Graphics_Graphics_ListV->names.clear();
    Graphics_Graphics_ListV->indexes.clear();
	wxArrayString names;
	if(all) names.Alloc(dataset->Graphics.size());

	for(short loop = 0; loop < dataset->Graphics.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetGraphicName(loop, true);
		if(SearchMatches(Name.Lower()))
		{
			Graphics_Graphics_ListV->names.Add(Name);
            Graphics_Graphics_ListV->indexes.push_back(loop);
		}
		if(all) names.Add(" "+FormatInt(loop)+" - "+GetGraphicName(loop));
	}

    virtualListing(Graphics_Graphics_ListV);
	if(all) FillLists(GraphicComboBoxList, names);

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;
}

void AGE_Frame::OnGraphicsSelect(wxCommandEvent &event)
{
    if(!graphicTimer.IsRunning())
        graphicTimer.Start(150);
}

void AGE_Frame::OnGraphicsTimer(wxTimerEvent &event)
{
    graphicTimer.Stop();
	auto selections = Graphics_Graphics_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    for(auto &box: uiGroupGraphic) box->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, Graphics_Graphics_ListV, GraphicIDs);

		genie::Graphic * GraphicPointer = NULL;
		for(auto sel = selections; sel--> 0;)
		{
			GraphicPointer = &dataset->Graphics[GraphicIDs[sel]];

			Graphics_Name->prepend(&GraphicPointer->Name);
			Graphics_Name2->prepend(&GraphicPointer->Name2);
			Graphics_SLP->prepend(&GraphicPointer->SLP);
			Graphics_Unknown1->prepend(&GraphicPointer->Unknown1);
			Graphics_Unknown2->prepend(&GraphicPointer->Unknown2);
			Graphics_FrameType->prepend(&GraphicPointer->Layer);
			Graphics_PlayerColor->prepend(&GraphicPointer->PlayerColor);
			Graphics_Rainbow->prepend(&GraphicPointer->Rainbow);
			Graphics_Replay->prepend(&GraphicPointer->Replay);
			for(short loop = 0; loop < 4; ++loop)
			{
				Graphics_Coordinates[loop]->prepend(&GraphicPointer->Coordinates[loop]);
			}
			Graphics_SoundID->prepend(&GraphicPointer->SoundID);
			Graphics_AttackSoundUsed->prepend(&GraphicPointer->AttackSoundUsed);
			Graphics_FrameCount->prepend(&GraphicPointer->FrameCount);
			Graphics_AngleCount->prepend(&GraphicPointer->AngleCount);
			Graphics_NewSpeed->prepend(&GraphicPointer->NewSpeed);
			Graphics_FrameRate->prepend(&GraphicPointer->FrameRate);
			Graphics_ReplayDelay->prepend(&GraphicPointer->ReplayDelay);
			Graphics_SequenceType->prepend(&GraphicPointer->SequenceType);
			Graphics_ID->prepend(&GraphicPointer->ID);
			Graphics_MirroringMode->prepend(&GraphicPointer->MirroringMode);
			if(GenieVersion >= genie::GV_AoKB)
			Graphics_Unknown3->prepend(&GraphicPointer->Unknown3);
		}
		SetStatusText("Selections: "+lexical_cast<string>(GraphicIDs.size())+"    Selected graphic: "+lexical_cast<string>(GraphicIDs[0]), 0);

		selections = GenieVersion < genie::GV_AoE ? 1 : dataset->GraphicPointers[GraphicIDs[0]];

        if(NULL != GraphicPointer)
        {
            graphicSLP.datID = GraphicIDs[0];
            graphicSLP.slpID = -2; // Force reloading delta graphics.
        }
	}
    for(auto &box: uiGroupGraphic) box->update();

    Graphics_ID->Enable(false);
	Deltas_Add->Enable(selections);
	ListGraphicDeltas();
	ListGraphicAttackSounds();
    if(NULL != slp_window) slp_view->Refresh();
}

void AGE_Frame::OnDrawGraphicSLP(wxPaintEvent &event)
{
    wxPanel *canvas = (wxPanel*)event.GetEventObject();
    wxBufferedPaintDC dc(canvas);
    dc.Clear();
    int centerX, centerY;
    canvas->GetClientSize(&centerX, &centerY);
    centerX *= 0.5f;
    centerY *= 0.6f;
    if(6 == TabBar_Main->GetSelection()) AGE_SLP::currentDisplay = 6;
    else if(4 == TabBar_Main->GetSelection()) AGE_SLP::currentDisplay = 4;
    if(AGE_SLP::currentDisplay == 6)
    {
        if(GraphicIDs.size() == 0 || dataset->Graphics[graphicSLP.datID].FrameCount == 0)
        {
            dc.DrawLabel("No frames", wxNullBitmap, wxRect(15, 15, 100, 40));
            return;
        }
        if(graphicSLP.slpID != dataset->Graphics[graphicSLP.datID].SLP) // SLP changed
        {
            graphicSLP.frameID = 0;
            graphicSLP.filename = dataset->Graphics[graphicSLP.datID].Name2;
            graphicSLP.slpID = dataset->Graphics[graphicSLP.datID].SLP;
            graphicSLP.deltas.clear();
            // Load possible delta graphics.
            if(ShowDeltas)
            for(auto const &delta: dataset->Graphics[graphicSLP.datID].Deltas)
            {
                AGE_SLP deltaSLP;
                if(delta.GraphicID < dataset->Graphics.size())
                {
                    deltaSLP.datID = delta.GraphicID;
                    deltaSLP.filename = dataset->Graphics[delta.GraphicID].Name2;
                    deltaSLP.slpID = dataset->Graphics[delta.GraphicID].SLP;
                }
                else
                {
                    deltaSLP = graphicSLP;
                }
                deltaSLP.xdelta = delta.DirectionX;
                deltaSLP.ydelta = delta.DirectionY;
                graphicSLP.deltas.insert(make_pair(0, deltaSLP));
            }
        }
        if(graphicSLP.deltas.size())
        {
            int fpms = 0x7FFF;
            for(auto &delta: graphicSLP.deltas)
            {
                SLPtoBitMap(&delta.second);
                if(delta.second.bitmap.IsOk())
                {
                    dc.DrawBitmap(delta.second.bitmap, centerX + delta.second.xpos + delta.second.xdelta, centerY + delta.second.ypos + delta.second.ydelta, true);
                    if(AnimSLP || nextFrame)
                    {
                        fpms = min(fpms, ShouldAnimate(&delta.second));
                    }
                }
            }
            nextFrame = false;
            if(AnimSLP)
            {
                graphicAnimTimer.Start(fpms);
            }
        }
        else
        {
            if(graphicSLP.slpID == -1)
            {
                dc.DrawLabel("No SLP", wxNullBitmap, wxRect(15, 15, 100, 40));
                return;
            }
            SLPtoBitMap(&graphicSLP);
            if(graphicSLP.bitmap.IsOk())
            {
                assert(graphicSLP.slp);
                dc.DrawBitmap(graphicSLP.bitmap, graphicSLP.xpos + centerX, graphicSLP.ypos + centerY, true);
                if(AnimSLP)
                {
                    graphicAnimTimer.Start(ShouldAnimate(&graphicSLP));
                }
                else if(nextFrame)
                {
                    ShouldAnimate(&graphicSLP);
                    nextFrame = false;
                }
            }
            else dc.DrawLabel("!SLP " + FormatInt(graphicSLP.slpID) + "\n" + graphicSLP.filename, wxNullBitmap, wxRect(15, 15, 100, 40));
        }
    }
    else if(AGE_SLP::currentDisplay == 4)
    {
        if(UnitIDs.size() == 0 || unitSLP.datID >= dataset->Graphics.size())
        {
            dc.DrawLabel("!Graphic " + FormatInt(unitSLP.datID), wxNullBitmap, wxRect(15, 15, 100, 40));
            return;
        }
        if(unitSLP.slpID != dataset->Graphics[unitSLP.datID].SLP) // SLP changed
        {
            unitSLP.frameID = 0;
            unitSLP.filename = dataset->Graphics[unitSLP.datID].Name2;
            unitSLP.slpID = dataset->Graphics[unitSLP.datID].SLP;
            unitSLP.deltas.clear();
            unsigned int unitID = UnitIDs[0];
            // Load possible delta and annex graphics.
            if(dataset->Civs[UnitCivID].Units[unitID].Type == 80)
            {
                // Start drawing from head unit instead.
                if(dataset->Civs[UnitCivID].Units[unitID].Building.HeadUnit < dataset->Civs[UnitCivID].Units.size())
                    unitID = dataset->Civs[UnitCivID].Units[unitID].Building.HeadUnit;
                // Draw this building only if it will stay up after built.
                if(dataset->Civs[UnitCivID].Units[unitID].Building.DisappearsWhenBuilt == 0)
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
        if(unitSLP.deltas.size())
        {
            int fpms = 0x7FFF;
            uint32_t hasSLP = -1;
            for(auto &delta: unitSLP.deltas)
            {
                SLPtoBitMap(&delta.second);
                if(delta.second.bitmap.IsOk())
                {
                    dc.DrawBitmap(delta.second.bitmap, centerX + delta.second.xpos + delta.second.xdelta, centerY + delta.second.ypos + delta.second.ydelta, true);
                    if(AnimSLP || nextFrame)
                    {
                        fpms = min(fpms, ShouldAnimate(&delta.second));
                    }
                }
                hasSLP = min(hasSLP, delta.second.slpID);
            }
            nextFrame = false;
            if(AnimSLP)
            {
                unitAnimTimer.Start(fpms);
            }
            if(hasSLP == -1)
            {
                dc.DrawLabel("No SLP", wxNullBitmap, wxRect(15, 15, 100, 40));
                return;
            }
        }
        else
        {
            if(unitSLP.slpID == -1)
            {
                dc.DrawLabel("No SLP", wxNullBitmap, wxRect(15, 15, 100, 40));
                return;
            }
            SLPtoBitMap(&unitSLP);
            if(unitSLP.bitmap.IsOk())
            {
                assert(unitSLP.slp);
                dc.DrawBitmap(unitSLP.bitmap, unitSLP.xpos + centerX, unitSLP.ypos + centerY, true);
                if(AnimSLP)
                {
                    unitAnimTimer.Start(ShouldAnimate(&unitSLP));
                }
                else if(nextFrame)
                {
                    ShouldAnimate(&unitSLP);
                    nextFrame = false;
                }
            }
            else dc.DrawLabel("!SLP " + FormatInt(unitSLP.slpID) + "\n" + unitSLP.filename, wxNullBitmap, wxRect(15, 15, 100, 40));
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

int AGE_Frame::ShouldAnimate(AGE_SLP *graphic)
{
    unsigned int frames = graphic->slp.get()->getFrameCount();
    int fpms = dataset->Graphics[graphic->datID].FrameRate * 1000;
    if((frames > 1 && fpms == 0) || dataset->Graphics[graphic->datID].FrameCount == 1) fpms = 500;
    if(fpms)
    {
        graphic->frameID = (graphic->frameID + 1) % frames; // Rotate through frames.
    }
    return fpms;
}

void AGE_Frame::OnGraphicAnim(wxTimerEvent &event)
{
    graphicAnimTimer.Stop();
    if(NULL != slp_window)
    {
        if(slp_view->IsShownOnScreen())
        slp_view->Refresh();
        else graphicAnimTimer.Start(1000);
    }
}

void AGE_Frame::OnGraphicErase(wxEraseEvent &event)
{
}

void AGE_Frame::OnGraphicsAdd(wxCommandEvent &event)
{
	if(NULL == dataset) return;

	wxBusyCursor WaitCursor;
	genie::Graphic Temp;
	Temp.setGameVersion(GenieVersion);
	dataset->Graphics.push_back(Temp);
	dataset->GraphicPointers.push_back(1);
	if(EnableIDFix)
	dataset->Graphics[dataset->Graphics.size()-1].ID = (dataset->Graphics.size()-1); // ID Fix
	How2List = ADD;
	ListGraphics();
}

void AGE_Frame::OnGraphicsInsert(wxCommandEvent &event)
{
	auto selections = Graphics_Graphics_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::Graphic Temp;
	Temp.setGameVersion(GenieVersion);
	dataset->Graphics.insert(dataset->Graphics.begin() + GraphicIDs[0], Temp);
	dataset->GraphicPointers.insert(dataset->GraphicPointers.begin() + GraphicIDs[0], 1);
	if(EnableIDFix)
	for(short loop = GraphicIDs[0];loop < dataset->Graphics.size(); ++loop) // ID Fix
	dataset->Graphics[loop].ID = loop;
	How2List = INSNEW;
	ListGraphics();
}

void AGE_Frame::OnGraphicsDelete(wxCommandEvent &event)
{
	auto selections = Graphics_Graphics_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(auto loop = selections; loop--> 0;)
	{
		dataset->Graphics.erase(dataset->Graphics.begin() + GraphicIDs[loop]);
		dataset->GraphicPointers.erase(dataset->GraphicPointers.begin() + GraphicIDs[loop]);
	}
	if(EnableIDFix)
	for(short loop = GraphicIDs[0];loop < dataset->Graphics.size(); ++loop) // ID Fix
	dataset->Graphics[loop].ID = loop;
	How2List = DEL;
	ListGraphics();
}

void AGE_Frame::OnGraphicsCopy(wxCommandEvent &event)
{
	auto selections = Graphics_Graphics_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	copies.GraphicPointer.resize(selections);
	copies.Graphic.resize(selections);
	for(short loop = 0; loop < selections; ++loop)
	{
		copies.GraphicPointer[loop] = dataset->GraphicPointers[GraphicIDs[loop]];
		copies.Graphic[loop] = dataset->Graphics[GraphicIDs[loop]];
		//copies.Graphic[loop].Deltas = dataset->Graphics[GraphicIDs[loop]].Deltas; Needs its own button!
	}
	Graphics_Graphics_ListV->SetFocus();
}

void AGE_Frame::OnGraphicsPaste(wxCommandEvent &event)
{
	auto selections = Graphics_Graphics_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(GraphicIDs.size(), copies.Graphic.size()))
		{
			for(short loop = 0; loop < copies.Graphic.size(); ++loop)
			{
				dataset->GraphicPointers[GraphicIDs[loop]] = copies.GraphicPointer[loop];
				copies.Graphic[loop].setGameVersion(GenieVersion);
				dataset->Graphics[GraphicIDs[loop]] = copies.Graphic[loop];
				//dataset->Graphics[GraphicIDs[loop]].Deltas = copies.Graphic[loop].Deltas; Needs its own button!
				if(EnableIDFix)
				dataset->Graphics[GraphicIDs[loop]].ID = GraphicIDs[loop]; // ID Fix
			}
		}
	}
	else
	{
		if(copies.Graphic.size()+GraphicIDs[0] > dataset->Graphics.size())
		{
			dataset->GraphicPointers.resize(copies.GraphicPointer.size()+GraphicIDs[0]);
			dataset->Graphics.resize(copies.Graphic.size()+GraphicIDs[0]);
		}
		for(short loop = 0; loop < copies.Graphic.size(); ++loop)
		{
			dataset->GraphicPointers[GraphicIDs[0]+loop] = copies.GraphicPointer[loop];
			copies.Graphic[loop].setGameVersion(GenieVersion);
			dataset->Graphics[GraphicIDs[0]+loop] = copies.Graphic[loop];
			if(EnableIDFix)
			dataset->Graphics[GraphicIDs[0]+loop].ID = (GraphicIDs[0]+loop); // ID Fix
		}
	}
	How2List = PASTE;
	ListGraphics();
}

void AGE_Frame::OnGraphicsPasteInsert(wxCommandEvent &event)
{
	auto selections = Graphics_Graphics_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::Graphic Temp;
	dataset->GraphicPointers.insert(dataset->GraphicPointers.begin() + GraphicIDs[0], copies.GraphicPointer.size(), 0);
	dataset->Graphics.insert(dataset->Graphics.begin() + GraphicIDs[0], copies.Graphic.size(), Temp);
	for(short loop = 0; loop < copies.Graphic.size(); ++loop)
	{
		dataset->GraphicPointers[GraphicIDs[0]+loop] = copies.GraphicPointer[loop];
		copies.Graphic[loop].setGameVersion(GenieVersion);
		dataset->Graphics[GraphicIDs[0]+loop] = copies.Graphic[loop];
	}
	if(EnableIDFix)
	for(short loop = GraphicIDs[0];loop < dataset->Graphics.size(); ++loop) // ID Fix
	dataset->Graphics[loop].ID = loop;
	How2List = INSPASTE;
	ListGraphics();
}

void AGE_Frame::OnGraphicsEnable(wxCommandEvent &event)
{
	auto selections = Graphics_Graphics_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short loop = 0; loop < selections; ++loop)
	{
		dataset->GraphicPointers[GraphicIDs[loop]] = 1;
		dataset->Graphics[GraphicIDs[loop]].ID = GraphicIDs[loop]; // ID Fix
	}
	How2List = ENABLE;
	ListGraphics();
}

void AGE_Frame::OnGraphicsDisable(wxCommandEvent &event)
{
	auto selections = Graphics_Graphics_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short loop = 0; loop < selections; ++loop)
	dataset->GraphicPointers[GraphicIDs[loop]] = 0;
	How2List = ENABLE;
	ListGraphics();
}

string AGE_Frame::GetGraphicDeltaName(int index)
{
    int deltaID = dataset->Graphics[GraphicIDs[0]].Deltas[index].GraphicID;
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
	searchText = Graphics_Deltas_Search->GetValue().Lower();
	excludeText = Graphics_Deltas_Search_R->GetValue().Lower();

    Graphics_Deltas_ListV->names.clear();
    Graphics_Deltas_ListV->indexes.clear();

    if(Graphics_Graphics_ListV->GetSelectedItemCount())
	for(short loop = 0; loop < dataset->Graphics[GraphicIDs[0]].Deltas.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetGraphicDeltaName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Graphics_Deltas_ListV->names.Add(Name);
            Graphics_Deltas_ListV->indexes.push_back(loop);
		}
	}
	virtualListing(Graphics_Deltas_ListV);

	wxTimerEvent E;
	OnGraphicDeltasTimer(E);
}

void AGE_Frame::OnGraphicDeltasSelect(wxCommandEvent &event)
{
    if(!deltaTimer.IsRunning())
        deltaTimer.Start(150);
}

void AGE_Frame::OnGraphicDeltasTimer(wxTimerEvent &event)
{
    deltaTimer.Stop();
	auto selections = Graphics_Deltas_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    for(auto &box: uiGroupGraphicDelta) box->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, Graphics_Deltas_ListV, DeltaIDs);

		genie::GraphicDelta * DeltaPointer;
		for(auto sel = selections; sel--> 0;)
		{
            DeltaPointer = &dataset->Graphics[GraphicIDs[0]].Deltas[DeltaIDs[sel]];

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
	auto selections = Graphics_Graphics_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->Graphics[GraphicIDs[0]].Deltas);
	ListGraphicDeltas();
}

void AGE_Frame::OnGraphicDeltasInsert(wxCommandEvent &event)
{
	auto selections = Graphics_Deltas_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->Graphics[GraphicIDs[0]].Deltas, DeltaIDs[0]);
	ListGraphicDeltas();
}

void AGE_Frame::OnGraphicDeltasDelete(wxCommandEvent &event)
{
	auto selections = Graphics_Deltas_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->Graphics[GraphicIDs[0]].Deltas, DeltaIDs);
	ListGraphicDeltas();
}

void AGE_Frame::OnGraphicDeltasCopy(wxCommandEvent &event)
{
	auto selections = Graphics_Deltas_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->Graphics[GraphicIDs[0]].Deltas, DeltaIDs, copies.GraphicDelta);
	Graphics_Deltas_ListV->SetFocus();
}

void AGE_Frame::OnGraphicDeltasPaste(wxCommandEvent &event)
{
	auto selections = Graphics_Deltas_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(DeltaIDs.size(), copies.GraphicDelta.size()))
		{
			PasteToList(dataset->Graphics[GraphicIDs[0]].Deltas, DeltaIDs, copies.GraphicDelta);
		}
	}
	else
	{
		PasteToList(dataset->Graphics[GraphicIDs[0]].Deltas, DeltaIDs[0], copies.GraphicDelta);
	}
	ListGraphicDeltas();
}

void AGE_Frame::OnGraphicDeltasPasteInsert(wxCommandEvent &event)
{
	auto selections = Graphics_Deltas_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->Graphics[GraphicIDs[0]].Deltas, DeltaIDs[0], copies.GraphicDelta);
	ListGraphicDeltas();
}

void AGE_Frame::OnGraphicDeltasCopyToGraphics(wxCommandEvent &event)
{
	for(short loop=1; loop < GraphicIDs.size(); ++loop)
	{
		dataset->Graphics[GraphicIDs[loop]].Deltas = dataset->Graphics[GraphicIDs[0]].Deltas;
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

    if(Graphics_Graphics_ListV->GetSelectedItemCount())
	for(short loop = 0; loop < dataset->Graphics[GraphicIDs[0]].AttackSounds.size(); ++loop)
	{
        Graphics_AttackSounds_ListV->names.Add(" "+FormatInt(loop)+" - "+GetGraphicAttackSoundName(loop));
        Graphics_AttackSounds_ListV->indexes.push_back(loop);
	}

	virtualListing(Graphics_AttackSounds_ListV);

	wxTimerEvent E;
	OnGraphicAttackSoundsTimer(E);
}

void AGE_Frame::OnGraphicAttackSoundsSelect(wxCommandEvent &event)
{
    if(!graphicSoundTimer.IsRunning())
        graphicSoundTimer.Start(150);
}

void AGE_Frame::OnGraphicAttackSoundsTimer(wxTimerEvent &event)
{
    graphicSoundTimer.Stop();
	auto selections = Graphics_AttackSounds_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    for(auto &box: uiGroupGraphicSound) box->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, Graphics_AttackSounds_ListV, AttackSoundIDs);

		genie::GraphicAttackSound * AttackSoundPointer;
		for(auto sel = selections; sel--> 0;)
		{
            AttackSoundPointer = &dataset->Graphics[GraphicIDs[0]].AttackSounds[AttackSoundIDs[sel]];

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
	auto selections = Graphics_AttackSounds_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::GraphicAttackSound Copy = dataset->Graphics[GraphicIDs[0]].AttackSounds[AttackSoundIDs[0]];
	for(short loop2 = 0; loop2 < dataset->Graphics[GraphicIDs[0]].AttackSounds.size(); ++loop2)
	dataset->Graphics[GraphicIDs[0]].AttackSounds[loop2] = Copy;
	Graphics_AttackSounds_ListV->SetFocus();
}

void AGE_Frame::OnGraphicAttackSoundsCopyToGraphics(wxCommandEvent &event)
{
	for(short loop=1; loop < GraphicIDs.size(); ++loop)
	{
		dataset->Graphics[GraphicIDs[loop]].AttackSounds = dataset->Graphics[GraphicIDs[0]].AttackSounds;
	}
}

void AGE_Frame::CreateGraphicsControls()
{
	Tab_Graphics = new wxPanel(TabBar_Main);
	Graphics_Main = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Graphics = new wxStaticBoxSizer(wxVERTICAL, Tab_Graphics, "Graphics  (Search by enter)");

	Graphics_Graphics_Search = new wxTextCtrl(Tab_Graphics, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Graphics_Graphics_UseAnd[0] = new wxCheckBox(Tab_Graphics, wxID_ANY, "And");
	Graphics_Graphics_Search_R = new wxTextCtrl(Tab_Graphics, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Graphics_Graphics_UseAnd[1] = new wxCheckBox(Tab_Graphics, wxID_ANY, "And");
	for(short loop = 0; loop < 2; ++loop)
	{
		Graphics_Graphics_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Graphics_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_Graphics, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	Graphics_Graphics_ListV = new AGEListView(Tab_Graphics, wxSize(200, 100));
	Graphics_Graphics_Buttons = new wxGridSizer(3, 0, 0);
	Graphics_Add = new wxButton(Tab_Graphics, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Graphics_Insert = new wxButton(Tab_Graphics, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Graphics_Delete = new wxButton(Tab_Graphics, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Graphics_Copy = new wxButton(Tab_Graphics, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Graphics_Paste = new wxButton(Tab_Graphics, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Graphics_PasteInsert = new wxButton(Tab_Graphics, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	Graphics_Enable = new wxButton(Tab_Graphics, wxID_ANY, "Enable", wxDefaultPosition, wxSize(5, 20));
	Graphics_Disable = new wxButton(Tab_Graphics, wxID_ANY, "Disable", wxDefaultPosition, wxSize(5, 20));

	Graphics_Scroller = new wxScrolledWindow(Tab_Graphics, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
	Graphics_ScrollSpace = new wxBoxSizer(wxVERTICAL);
	Graphics_NameArea_Holder = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Name_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Name_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Name = AGETextCtrl::init(CString, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_Name2_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Name2_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " SLP Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Name2 = AGETextCtrl::init(CString, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_ID_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_ID_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " ID", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_ID = AGETextCtrl::init(CShort, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);

	Graphics_SLP_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_SLP_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SLP = AGETextCtrl::init(CLong, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_FrameType_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_FrameType_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Layer *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameType = AGETextCtrl::init(CByte, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_FrameType->SetToolTip("0 - Cliffs\n5 - Shadows, Farms\n6 - Rubble\n10 - Construction sequences, some shadows, corpses, stumps, flowers, paths, ruins, crack\n11 - Fish\n19 - Rugs, crater\n20 - Buildings, damage flames, mill animation, units\n21 - Blacksmith piece (no slp), blacksmith smoke\n22 - Hawk\n30 - Explosions, projectiles ");
	Graphics_Replay_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Replay_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Replay *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Replay = AGETextCtrl::init(CByte, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_Replay->SetToolTip("Will the graphic be looped?");
	Graphics_ReplayDelay_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_ReplayDelay_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Replay Delay *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_ReplayDelay = AGETextCtrl::init(CFloat, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_ReplayDelay->SetToolTip("Waiting time in seconds before animation restarts again");

	Graphics_FrameCount_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_FrameCount_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Frame Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameCount = AGETextCtrl::init(CUShort, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_FrameRate_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_FrameRate_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Frame Rate *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameRate = AGETextCtrl::init(CFloat, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_FrameRate->SetToolTip("How long each frame is displayed in seconds");
	Graphics_SequenceType_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_SequenceType_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sequence Type *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SequenceType = AGETextCtrl::init(CByte, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_SequenceType->SetToolTip("Animation type?\n6 Changes frames when placed in the scenario editor");
	Graphics_Type_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Type_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Mirroring Mode", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_MirroringMode = AGETextCtrl::init(CByte, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);

	Graphics_Coordinates_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_CoordinateGrid_Holder = new wxGridSizer(4, 0, 5);
	Graphics_Coordinates_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Coordinates", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 4; ++loop)
	Graphics_Coordinates[loop] = AGETextCtrl::init(CShort, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller, true);

	Graphics_SoundID_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_SoundID_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SoundID = AGETextCtrl::init(CShort, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_SoundID_ComboBox = new ComboBox_Plus1(Graphics_Scroller, Graphics_SoundID);
	SoundComboBoxList.push_front(Graphics_SoundID_ComboBox);
	Graphics_PlayerColor_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_PlayerColor_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Forced Player Color *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_PlayerColor = AGETextCtrl::init(CByte, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_PlayerColor->SetToolTip("The player color to be forced on the graphic");
	Graphics_PlayerColor_ComboBox = new ComboBox_Plus1(Graphics_Scroller, Graphics_PlayerColor);
	Graphics_Rainbow_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Rainbow_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Rainbow *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Rainbow = AGETextCtrl::init(CByte, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_Rainbow->SetToolTip("Makes the graphic change its player color according to nearby units");
	Graphics_NewSpeed_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_NewSpeed_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unit Speed Multiplier *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_NewSpeed = AGETextCtrl::init(CFloat, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_NewSpeed->SetToolTip("Multiplies the speed of the unit this graphic is applied to");

	Graphics_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Unknown1_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown1 = AGETextCtrl::init(CByte, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Unknown2_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown2 = AGETextCtrl::init(CByte, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Unknown3_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 3 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown3 = AGETextCtrl::init(CByte, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_Unknown3->SetToolTip("Related to sprite editor?");
	Graphics_4_Holder = new wxBoxSizer(wxHORIZONTAL);
	Graphics_5_Holder = new wxBoxSizer(wxHORIZONTAL);
	Graphics_1_Grid = new wxGridSizer(4, 5, 5);
	Graphics_2_Grid = new wxGridSizer(4, 5, 5);
	Graphics_3_Grid = new wxGridSizer(4, 5, 5);

	Graphics_Deltas = new wxBoxSizer(wxVERTICAL);
	Graphics_Deltas_Search = new wxTextCtrl(Graphics_Scroller, wxID_ANY);
	Graphics_Deltas_Search_R = new wxTextCtrl(Graphics_Scroller, wxID_ANY);
	Graphics_Deltas_ListV = new AGEListView(Graphics_Scroller, wxSize(140, 140));
	Graphics_Deltas_Buttons = new wxGridSizer(3, 0, 0);
	Deltas_Add = new wxButton(Graphics_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Deltas_Insert = new wxButton(Graphics_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Deltas_Delete = new wxButton(Graphics_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Deltas_Copy = new wxButton(Graphics_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Deltas_Paste = new wxButton(Graphics_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Deltas_PasteInsert = new wxButton(Graphics_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	Deltas_CopyToGraphics = new wxButton(Graphics_Scroller, wxID_ANY, "Copy all to selected graphics", wxDefaultPosition, wxSize(5, 20));
	GraphicDeltas_GraphicID_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_GraphicID_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Graphic", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_GraphicID = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, AGEwindow, Graphics_Scroller);
	GraphicDeltas_GraphicID_ComboBox = new ComboBox_Plus1(Graphics_Scroller, GraphicDeltas_GraphicID);
	GraphicComboBoxList.push_front(GraphicDeltas_GraphicID_ComboBox);
	GraphicDeltas_DirectionX_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_DirectionX_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Direction X", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_DirectionX = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, AGEwindow, Graphics_Scroller);
	GraphicDeltas_DirectionY_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_DirectionY_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Direction Y", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_DirectionY = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, AGEwindow, Graphics_Scroller);
	GraphicDeltas_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Unknown1_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown1 = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, AGEwindow, Graphics_Scroller);
	GraphicDeltas_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Unknown2_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown2 = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, AGEwindow, Graphics_Scroller);
	GraphicDeltas_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Unknown3_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown3 = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, AGEwindow, Graphics_Scroller);
	GraphicDeltas_DisplayAngle_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_DisplayAngle_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Display Angle *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_DisplayAngle = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, AGEwindow, Graphics_Scroller);
	GraphicDeltas_DisplayAngle->SetToolTip("The angle where this delta will be displayed\nIn a unit with 8 angles, 0 would mean east, 1 south-east, 2 south,\n3 south-west, 4 west, 5 north-west, 6 north, 7 north-east");
	GraphicDeltas_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Unknown5_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown5 = AGETextCtrl::init(CShort, &uiGroupGraphicDelta, this, AGEwindow, Graphics_Scroller);

	Graphics_AngleCount_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_AngleCount_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Angle Count *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_AngleCount = AGETextCtrl::init(CUShort, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_AngleCount->SetToolTip("The number of directions that a unit/ship faces");
	Graphics_AttackSoundUsed_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_AttackSoundUsed1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Graphics_AttackSoundUsed_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Attack Sound Used", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_AttackSoundUsed = AGETextCtrl::init(CByte, &uiGroupGraphic, this, AGEwindow, Graphics_Scroller);
	Graphics_AttackSoundUsed_CheckBox = new CheckBox_2State(Graphics_Scroller, "Used", Graphics_AttackSoundUsed);
	Graphics_AttackSounds = new wxBoxSizer(wxVERTICAL);
	Graphics_AttackSounds_ListV = new AGEListView(Graphics_Scroller, wxSize(140, 140));
	AttackSounds_Copy = new wxButton(Graphics_Scroller, wxID_ANY, "Copy to all", wxDefaultPosition, wxSize(10, 20));
	AttackSounds_CopyToGraphics = new wxButton(Graphics_Scroller, wxID_ANY, "Copy all to selected graphics", wxDefaultPosition, wxSize(10, 20));
	Graphics_AttackSounds_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_AttackSounds_Grid = new wxGridSizer(2, 0, 0);
	Graphics_AttackSounds_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_AttackSoundDelays_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_AttackSoundDelays_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound Delay", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 3; ++loop)
	{
		Graphics_AttackSoundID[loop] = AGETextCtrl::init(CShort, &uiGroupGraphicSound, this, AGEwindow, Graphics_Scroller);
		Graphics_AttackSoundID_ComboBox[loop] = new ComboBox_Plus1(Graphics_Scroller, Graphics_AttackSoundID[loop]);
		SoundComboBoxList.push_front(Graphics_AttackSoundID_ComboBox[loop]);
		Graphics_AttackSoundDelay[loop] = AGETextCtrl::init(CShort, &uiGroupGraphicSound, this, AGEwindow, Graphics_Scroller);
	}

	Graphics_Deltas_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Graphics_Scroller, "Deltas");
	Graphics_Deltas_Holder_Data = new wxBoxSizer(wxVERTICAL);
	Graphics_Deltas_Holder_Data1 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Deltas_Grid_Data2 = new wxGridSizer(3, 5, 5);
	Graphics_AttackSoundArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Graphics_Scroller, "Attack Sounds");

	for(short loop = 0; loop < 2; ++loop)
	{
		Graphics_SearchFilters[loop]->Append("Internal Name");	// 0
		Graphics_SearchFilters[loop]->Append("SLP Name");
		Graphics_SearchFilters[loop]->Append("SLP");
		Graphics_SearchFilters[loop]->Append("Unknown 1");
		Graphics_SearchFilters[loop]->Append("Unknown 2");
		Graphics_SearchFilters[loop]->Append("Layer");
		Graphics_SearchFilters[loop]->Append("Player Color Forcer");
		Graphics_SearchFilters[loop]->Append("Replay");
		Graphics_SearchFilters[loop]->Append("Sound");
		Graphics_SearchFilters[loop]->Append("Coordinates");
		Graphics_SearchFilters[loop]->Append("Delta Count");
		Graphics_SearchFilters[loop]->Append("Attack Sound Used");
		Graphics_SearchFilters[loop]->Append("Frame Count");
		Graphics_SearchFilters[loop]->Append("Angle Count");
		Graphics_SearchFilters[loop]->Append("New Speed");
		Graphics_SearchFilters[loop]->Append("Frame Rate");
		Graphics_SearchFilters[loop]->Append("Replay Delay");
		Graphics_SearchFilters[loop]->Append("Sequence Type");
		Graphics_SearchFilters[loop]->Append("Mirroring Mode");
		Graphics_SearchFilters[loop]->Append("Unknown 3");
		Graphics_SearchFilters[loop]->Append("Pointer");
		Graphics_SearchFilters[loop]->SetSelection(0);
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
	for(short loop = 0; loop < 2; ++loop)
	Graphics_Graphics->Add(Graphics_Graphics_Searches[loop], 0, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Graphics_Graphics->Add(Graphics_SearchFilters[loop], 0, wxEXPAND);
	Graphics_Graphics->Add(Graphics_Graphics_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Graphics_Graphics->Add(Graphics_Graphics_Buttons, 0, wxEXPAND);

	Graphics_Name_Holder->Add(Graphics_Name_Text, 0, wxEXPAND);
	Graphics_Name_Holder->Add(Graphics_Name, 1, wxEXPAND);
	Graphics_Name2_Holder->Add(Graphics_Name2_Text, 0, wxEXPAND);
	Graphics_Name2_Holder->Add(Graphics_Name2, 1, wxEXPAND);
	Graphics_ID_Holder->Add(Graphics_ID_Text, 0, wxEXPAND);
	Graphics_ID_Holder->Add(Graphics_ID, 1, wxEXPAND);
	Graphics_Unknown1_Holder->Add(Graphics_Unknown1_Text, 0, wxEXPAND);
	Graphics_Unknown1_Holder->Add(Graphics_Unknown1, 0, wxEXPAND);
	Graphics_Unknown2_Holder->Add(Graphics_Unknown2_Text, 0, wxEXPAND);
	Graphics_Unknown2_Holder->Add(Graphics_Unknown2, 0, wxEXPAND);
	Graphics_PlayerColor_Holder->Add(Graphics_PlayerColor_Text, 0, wxEXPAND);
	Graphics_PlayerColor_Holder->Add(Graphics_PlayerColor, 1, wxEXPAND);
	Graphics_PlayerColor_Holder->Add(Graphics_PlayerColor_ComboBox, 1, wxEXPAND);
	Graphics_Rainbow_Holder->Add(Graphics_Rainbow_Text, 0, wxEXPAND);
	Graphics_Rainbow_Holder->Add(Graphics_Rainbow, 0, wxEXPAND);
	for(short loop = 0; loop < 4; ++loop)
	Graphics_CoordinateGrid_Holder->Add(Graphics_Coordinates[loop], 1, wxEXPAND);
	Graphics_Coordinates_Holder->Add(Graphics_Coordinates_Text, 0, wxEXPAND);
	Graphics_Coordinates_Holder->Add(Graphics_CoordinateGrid_Holder, 0, wxEXPAND);
	Graphics_NewSpeed_Holder->Add(Graphics_NewSpeed_Text, 0, wxEXPAND);
	Graphics_NewSpeed_Holder->Add(Graphics_NewSpeed, 0, wxEXPAND);
	Graphics_SLP_Holder->Add(Graphics_SLP_Text, 0, wxEXPAND);
	Graphics_SLP_Holder->Add(Graphics_SLP, 1, wxEXPAND);
	Graphics_FrameType_Holder->Add(Graphics_FrameType_Text, 0, wxEXPAND);
	Graphics_FrameType_Holder->Add(Graphics_FrameType, 1, wxEXPAND);
	Graphics_Replay_Holder->Add(Graphics_Replay_Text, 0, wxEXPAND);
	Graphics_Replay_Holder->Add(Graphics_Replay, 0, wxEXPAND);
	Graphics_SoundID_Holder->Add(Graphics_SoundID_Text, 0, wxEXPAND);
	Graphics_SoundID_Holder->Add(Graphics_SoundID, 1, wxEXPAND);
	Graphics_SoundID_Holder->Add(Graphics_SoundID_ComboBox, 1, wxEXPAND);
	Graphics_AttackSoundUsed1_Holder->Add(Graphics_AttackSoundUsed, 2, wxEXPAND);
	Graphics_AttackSoundUsed1_Holder->Add(Graphics_AttackSoundUsed_CheckBox, 1, wxEXPAND | wxLEFT, 2);
	Graphics_AttackSoundUsed_Holder->Add(Graphics_AttackSoundUsed_Text, 0, wxEXPAND);
	Graphics_AttackSoundUsed_Holder->Add(Graphics_AttackSoundUsed1_Holder, 1, wxEXPAND);
	Graphics_FrameCount_Holder->Add(Graphics_FrameCount_Text, 0, wxEXPAND);
	Graphics_FrameCount_Holder->Add(Graphics_FrameCount, 1, wxEXPAND);
	Graphics_AngleCount_Holder->Add(Graphics_AngleCount_Text, 0, wxEXPAND);
	Graphics_AngleCount_Holder->Add(Graphics_AngleCount, 1, wxEXPAND);
	Graphics_FrameRate_Holder->Add(Graphics_FrameRate_Text, 0, wxEXPAND);
	Graphics_FrameRate_Holder->Add(Graphics_FrameRate, 1, wxEXPAND);
	Graphics_ReplayDelay_Holder->Add(Graphics_ReplayDelay_Text, 0, wxEXPAND);
	Graphics_ReplayDelay_Holder->Add(Graphics_ReplayDelay, 0, wxEXPAND);
	Graphics_SequenceType_Holder->Add(Graphics_SequenceType_Text, 0, wxEXPAND);
	Graphics_SequenceType_Holder->Add(Graphics_SequenceType, 1, wxEXPAND);
	Graphics_Type_Holder->Add(Graphics_Type_Text, 0, wxEXPAND);
	Graphics_Type_Holder->Add(Graphics_MirroringMode, 1, wxEXPAND);
	Graphics_Unknown3_Holder->Add(Graphics_Unknown3_Text, 0, wxEXPAND);
	Graphics_Unknown3_Holder->Add(Graphics_Unknown3, 1, wxEXPAND);

	Graphics_NameArea_Holder->Add(Graphics_Name_Holder, 2, wxEXPAND);
	Graphics_NameArea_Holder->Add(Graphics_Name2_Holder, 2, wxEXPAND | wxLEFT, 5);
	Graphics_NameArea_Holder->Add(Graphics_ID_Holder, 1, wxEXPAND | wxLEFT, 5);

	Graphics_1_Grid->Add(Graphics_SLP_Holder, 1, wxEXPAND);
	Graphics_1_Grid->Add(Graphics_FrameType_Holder, 1, wxEXPAND);
	Graphics_1_Grid->Add(Graphics_Replay_Holder, 1, wxEXPAND);
	Graphics_1_Grid->Add(Graphics_ReplayDelay_Holder, 1, wxEXPAND);
	Graphics_1_Grid->Add(Graphics_FrameCount_Holder, 1, wxEXPAND);
	Graphics_1_Grid->Add(Graphics_FrameRate_Holder, 1, wxEXPAND);
	Graphics_1_Grid->Add(Graphics_SequenceType_Holder, 1, wxEXPAND);
	Graphics_1_Grid->Add(Graphics_Type_Holder, 1, wxEXPAND);

	Graphics_2_Grid->Add(Graphics_SoundID_Holder, 1, wxEXPAND);
	Graphics_2_Grid->Add(Graphics_PlayerColor_Holder, 0, wxEXPAND);
	Graphics_2_Grid->Add(Graphics_Rainbow_Holder, 0, wxEXPAND);
	Graphics_2_Grid->Add(Graphics_NewSpeed_Holder, 1, wxEXPAND);

	Graphics_3_Grid->Add(Graphics_Unknown1_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_3_Grid->Add(Graphics_Unknown2_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_3_Grid->Add(Graphics_Unknown3_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

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

	GraphicDeltas_GraphicID_Holder->Add(GraphicDeltas_GraphicID_Text, 0, wxEXPAND);
	GraphicDeltas_GraphicID_Holder->Add(GraphicDeltas_GraphicID, 1, wxEXPAND);
	GraphicDeltas_GraphicID_Holder->Add(GraphicDeltas_GraphicID_ComboBox, 1, wxEXPAND);
	GraphicDeltas_Unknown1_Holder->Add(GraphicDeltas_Unknown1_Text, 0, wxEXPAND);
	GraphicDeltas_Unknown1_Holder->Add(GraphicDeltas_Unknown1, 1, wxEXPAND);
	GraphicDeltas_Unknown2_Holder->Add(GraphicDeltas_Unknown2_Text, 0, wxEXPAND);
	GraphicDeltas_Unknown2_Holder->Add(GraphicDeltas_Unknown2, 1, wxEXPAND);
	GraphicDeltas_Unknown3_Holder->Add(GraphicDeltas_Unknown3_Text, 0, wxEXPAND);
	GraphicDeltas_Unknown3_Holder->Add(GraphicDeltas_Unknown3, 1, wxEXPAND);
	GraphicDeltas_DirectionX_Holder->Add(GraphicDeltas_DirectionX_Text, 0, wxEXPAND);
	GraphicDeltas_DirectionX_Holder->Add(GraphicDeltas_DirectionX, 0, wxEXPAND);
	GraphicDeltas_DirectionY_Holder->Add(GraphicDeltas_DirectionY_Text, 0, wxEXPAND);
	GraphicDeltas_DirectionY_Holder->Add(GraphicDeltas_DirectionY, 0, wxEXPAND);
	GraphicDeltas_DisplayAngle_Holder->Add(GraphicDeltas_DisplayAngle_Text, 0, wxEXPAND);
	GraphicDeltas_DisplayAngle_Holder->Add(GraphicDeltas_DisplayAngle, 1, wxEXPAND);
	GraphicDeltas_Unknown5_Holder->Add(GraphicDeltas_Unknown5_Text, 0, wxEXPAND);
	GraphicDeltas_Unknown5_Holder->Add(GraphicDeltas_Unknown5, 1, wxEXPAND);

	Graphics_Deltas_Holder_Data1->Add(GraphicDeltas_GraphicID_Holder, 1, wxEXPAND);
	Graphics_Deltas_Holder_Data1->Add(GraphicDeltas_DirectionX_Holder, 1, wxEXPAND | wxLEFT, 5);
	Graphics_Deltas_Holder_Data1->Add(GraphicDeltas_DirectionY_Holder, 1, wxEXPAND | wxLEFT, 5);
	Graphics_Deltas_Grid_Data2->Add(GraphicDeltas_Unknown1_Holder, 1, wxEXPAND);
	Graphics_Deltas_Grid_Data2->Add(GraphicDeltas_Unknown2_Holder, 1, wxEXPAND);
	Graphics_Deltas_Grid_Data2->Add(GraphicDeltas_Unknown3_Holder, 1, wxEXPAND);
	Graphics_Deltas_Grid_Data2->Add(GraphicDeltas_DisplayAngle_Holder, 1, wxEXPAND);
	Graphics_Deltas_Grid_Data2->Add(GraphicDeltas_Unknown5_Holder, 1, wxEXPAND);
	Graphics_Deltas_Holder_Data->Add(Graphics_Deltas_Holder_Data1, 0, wxEXPAND);
	Graphics_Deltas_Holder_Data->Add(Graphics_Deltas_Grid_Data2, 0, wxEXPAND | wxTOP, 5);

	Graphics_Deltas_Holder->Add(Graphics_Deltas, 1, wxEXPAND);
	Graphics_Deltas_Holder->Add(Graphics_Deltas_Holder_Data, 3, wxEXPAND | wxLEFT, 5);

	Graphics_AttackSounds->Add(Graphics_AttackSounds_ListV, 1, wxEXPAND | wxBOTTOM, 2);
	Graphics_AttackSounds->Add(AttackSounds_Copy, 0, wxEXPAND);
	Graphics_AttackSounds->Add(AttackSounds_CopyToGraphics, 0, wxEXPAND | wxTOP, 2);

	Graphics_AttackSounds_Holder->Add(Graphics_AttackSounds_Text, 0, wxEXPAND);
	Graphics_AttackSounds_Holder->Add(Graphics_AttackSounds_Grid, 0, wxEXPAND);
	Graphics_AttackSoundDelays_Holder->Add(Graphics_AttackSoundDelays_Text, 0, wxEXPAND);
	for(short loop = 0; loop < 3; ++loop)
	{
		Graphics_AttackSounds_Grid->Add(Graphics_AttackSoundID[loop], 0, wxEXPAND);
		Graphics_AttackSounds_Grid->Add(Graphics_AttackSoundID_ComboBox[loop], 0, wxEXPAND);
		Graphics_AttackSoundDelays_Holder->Add(Graphics_AttackSoundDelay[loop], 0, wxEXPAND);
	}
	Graphics_5_Holder->Add(Graphics_AttackSounds_Holder, 2, wxEXPAND);
	Graphics_5_Holder->Add(Graphics_AttackSoundDelays_Holder, 1, wxEXPAND | wxLEFT, 5);

	Graphics_4_Holder->Add(Graphics_AngleCount_Holder, 1, wxEXPAND);
	Graphics_4_Holder->Add(Graphics_AttackSoundUsed_Holder, 1, wxEXPAND | wxLEFT, 5);
	Graphics_4_Holder->AddStretchSpacer(2);

	Graphics_AttackSoundArea_Holder->Add(Graphics_AttackSounds, 1, wxEXPAND);
	Graphics_AttackSoundArea_Holder->Add(Graphics_5_Holder, 3, wxEXPAND | wxLEFT, 5);

	Graphics_ScrollSpace->Add(Graphics_NameArea_Holder, 0, wxEXPAND);
	Graphics_ScrollSpace->Add(Graphics_1_Grid, 0, wxEXPAND | wxTOP, 5);
	Graphics_ScrollSpace->Add(Graphics_Coordinates_Holder, 0, wxEXPAND | wxTOP, 5);
	Graphics_ScrollSpace->Add(Graphics_2_Grid, 0, wxEXPAND | wxTOP, 5);
	Graphics_ScrollSpace->Add(Graphics_3_Grid, 0, wxEXPAND | wxTOP, 5);
	Graphics_ScrollSpace->Add(Graphics_Deltas_Holder, 0, wxEXPAND | wxTOP, 5);
	Graphics_ScrollSpace->Add(Graphics_4_Holder, 0, wxEXPAND | wxTOP, 5);
	Graphics_ScrollSpace->Add(Graphics_AttackSoundArea_Holder, 0, wxEXPAND | wxTOP, 5);

	Graphics_Scroller->SetSizer(Graphics_ScrollSpace);
	Graphics_Scroller->SetScrollRate(0, 15);

	Graphics_Main->Add(Graphics_Graphics, 21, wxEXPAND | wxALL, 5);
	Graphics_Main->Add(Graphics_Scroller, 65, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

	if(EnableIDFix)
	Graphics_ID->Enable(false);

	Tab_Graphics->SetSizer(Graphics_Main);

	Connect(Graphics_Graphics_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
	Connect(Graphics_Graphics_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
	for(short loop = 0; loop < 2; ++loop)
	{
		Connect(Graphics_Graphics_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
		Connect(Graphics_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
	}
	Connect(Graphics_Graphics_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicsSelect)); // LMB
	Connect(Graphics_Graphics_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicsSelect)); // CTRL
	Connect(Graphics_Graphics_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnGraphicsSelect)); // SHIFT
	Connect(Graphics_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsAdd));
	Connect(Graphics_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsInsert));
	Connect(Graphics_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsDelete));
	Connect(Graphics_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsCopy));
	Connect(Graphics_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsPaste));
	Connect(Graphics_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsPasteInsert));
	Connect(Graphics_Enable->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsEnable));
	Connect(Graphics_Disable->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsDisable));
	Connect(Graphics_Deltas_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSearch));
	Connect(Graphics_Deltas_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSearch));
	Connect(Graphics_Deltas_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSelect));
	Connect(Graphics_Deltas_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSelect));
	Connect(Graphics_Deltas_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSelect));
	Connect(Deltas_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasAdd));
	Connect(Deltas_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasInsert));
	Connect(Deltas_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasDelete));
	Connect(Deltas_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasCopy));
	Connect(Deltas_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasPaste));
	Connect(Deltas_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasPasteInsert));
	Connect(Deltas_CopyToGraphics->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasCopyToGraphics));
	Connect(Graphics_AttackSounds_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicAttackSoundsSelect));
	Connect(Graphics_AttackSounds_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicAttackSoundsSelect));
	Connect(Graphics_AttackSounds_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnGraphicAttackSoundsSelect));
	Connect(AttackSounds_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicAttackSoundsCopy));
	Connect(AttackSounds_CopyToGraphics->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicAttackSoundsCopyToGraphics));

    graphicTimer.Connect(graphicTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnGraphicsTimer), NULL, this);
    deltaTimer.Connect(deltaTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnGraphicDeltasTimer), NULL, this);
    graphicSoundTimer.Connect(graphicSoundTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnGraphicAttackSoundsTimer), NULL, this);
	Graphics_Name->Connect(Graphics_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Graphics), NULL, this);
	Graphics_Name2->Connect(Graphics_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Graphics), NULL, this);
	GraphicDeltas_GraphicID->Connect(GraphicDeltas_GraphicID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Graphics), NULL, this);
	GraphicDeltas_GraphicID_ComboBox->Connect(GraphicDeltas_GraphicID_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Graphics), NULL, this);
	Graphics_AngleCount->Connect(Graphics_AngleCount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Graphics), NULL, this);
	Graphics_AttackSoundUsed->Connect(Graphics_AttackSoundUsed->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Graphics), NULL, this);
	Graphics_AttackSoundUsed_CheckBox->Connect(Graphics_AttackSoundUsed_CheckBox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_Graphics), NULL, this);
    graphicAnimTimer.Connect(graphicAnimTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnGraphicAnim), NULL, this);
}

void AGE_Frame::OnKillFocus_Graphics(wxFocusEvent &event)
{
	event.Skip();
	if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
	if(event.GetId() == Graphics_Name->GetId())
	{
		ListGraphics();
	}
	else if(event.GetId() == GraphicDeltas_GraphicID->GetId())
	{
		ListGraphicDeltas();
	}
	else if(event.GetId() == Graphics_Name2->GetId())
	{
		wxTimerEvent E;
		OnGraphicsTimer(E);
	}
	else if(event.GetId() == Graphics_AngleCount->GetId() || event.GetId() == Graphics_AttackSoundUsed->GetId())
	{
		if(dataset->Graphics[GraphicIDs[0]].AttackSoundUsed == 0) return;

		for(short loop = 0; loop < GraphicIDs.size(); ++loop)
		dataset->Graphics[GraphicIDs[loop]].AttackSounds.resize(dataset->Graphics[GraphicIDs[loop]].AngleCount);

		wxTimerEvent E;
		OnGraphicsTimer(E);
	}
}

void AGE_Frame::OnUpdateCheck_Graphics(wxCommandEvent &event)
{
	((AGECheckBox*)event.GetEventObject())->OnUpdate(event);
	if(dataset->Graphics[GraphicIDs[0]].AttackSoundUsed == 0) return;

	for(short loop = 0; loop < GraphicIDs.size(); ++loop)
	dataset->Graphics[GraphicIDs[loop]].AttackSounds.resize(dataset->Graphics[GraphicIDs[loop]].AngleCount);

	wxTimerEvent E;
	OnGraphicsTimer(E);
}

void AGE_Frame::OnUpdateCombo_Graphics(wxCommandEvent &event)
{
	((AGEComboBox*)event.GetEventObject())->OnUpdate(event);
	ListGraphicDeltas();
}
