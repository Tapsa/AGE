#include "../AGE_Frame.h"

string AGE_Frame::GetGraphicName(short Index, bool Filter)
{
	string Name = "";
	if(GenieVersion >= genie::GV_AoE && GenieFile->GraphicPointers[Index] == 0)
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
					Name += "SLP "+FormatInt(GenieFile->Graphics[Index].SLP);
					break;
				case 3: // Unknown 1
					Name += "U1 "+FormatInt(GenieFile->Graphics[Index].Unknown1);
					break;
				case 4: // Unknown 2
					Name += "U2 "+FormatInt(GenieFile->Graphics[Index].Unknown2);
					break;
				case 5: // Layer
					Name += "L "+FormatInt(GenieFile->Graphics[Index].Layer);
					break;
				case 6: // Player Color Forcer
					Name += "PC "+FormatInt(GenieFile->Graphics[Index].PlayerColor);
					break;
				case 7: // Replay
					Name += "R "+FormatInt(GenieFile->Graphics[Index].Replay);
					break;
				case 8: // Sound
					Name += "So "+FormatInt(GenieFile->Graphics[Index].SoundID);
					break;
				case 9: // Coordinates
					break;
				case 10: // Deltas
					Name += "DC "+FormatInt(GenieFile->Graphics[Index].Deltas.size());
					break;
				case 11: // Attack Sound Used
					Name += "U "+FormatInt(GenieFile->Graphics[Index].AttackSoundUsed);
					break;
				case 12: // Frames
					Name += "FC "+FormatInt(GenieFile->Graphics[Index].FrameCount);
					break;
				case 13: // Angles
					Name += "AC "+FormatInt(GenieFile->Graphics[Index].AngleCount);
					break;
				case 14: // Speed
					Name += "Sp "+FormatFloat(GenieFile->Graphics[Index].NewSpeed);
					break;
				case 15: // Frame Rate
					Name += "FR "+FormatFloat(GenieFile->Graphics[Index].FrameRate);
					break;
				case 16: // Replay Delay
					Name += "RD "+FormatFloat(GenieFile->Graphics[Index].ReplayDelay);
					break;
				case 17: // Sequence Type
					Name += "ST "+FormatInt(GenieFile->Graphics[Index].SequenceType);
					break;
				case 18: // Mirroring Mode
					Name += "M "+FormatInt(GenieFile->Graphics[Index].MirroringMode);
					break;
				case 19: // Unknown 3
					Name += "U3 "+FormatInt(GenieFile->Graphics[Index].Unknown3);
					break;
				case 20: // Pointer
					Name = FormatInt(GenieFile->GraphicPointers[Index]);
					break;
			}
			Name += ", ";
			if(Selection[loop+1] < 1) break; // Internal name breaks
		}
		if(Selection[0] == 1) goto InternalName;
	}

	if(!GenieFile->Graphics[Index].Name.empty())
	{
		return Name + GenieFile->Graphics[Index].Name;
	}
InternalName:
	if(!GenieFile->Graphics[Index].Name2.empty())
	{
		return Name + GenieFile->Graphics[Index].Name2;
	}
	return Name + "New Graphic";
}

void AGE_Frame::OnGraphicsSearch(wxCommandEvent &Event)
{
	ListGraphics(false);
}

void AGE_Frame::ListGraphics(bool all)
{
	InitGraphics(all);
	wxCommandEvent E;
	OnGraphicsSelect(E);
}

void AGE_Frame::InitGraphics(bool all)
{
	searchText = Graphics_Graphics_Search->GetValue().Lower();
	excludeText = Graphics_Graphics_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = Graphics_Graphics_UseAnd[loop]->GetValue();

	list<void*> dataPointers;
	wxArrayString names, filteredNames;
	if(all) names.Alloc(GenieFile->Graphics.size());

	for(short loop = 0; loop < GenieFile->Graphics.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetGraphicName(loop, true);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->Graphics[loop]);
		}
		if(all) names.Add(" "+FormatInt(loop)+" - "+GetGraphicName(loop));
	}

	Listing(Graphics_Graphics_List, filteredNames, dataPointers);
	if(all) FillLists(GraphicComboBoxList, names);

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;
}

void AGE_Frame::OnGraphicsSelect(wxCommandEvent &Event)
{
	auto selections = Graphics_Graphics_List->GetSelections(Items);
	if(selections > 0)
	{
		GraphicIDs.resize(selections);
		Graphics_Name->resize(selections);
		Graphics_Name2->resize(selections);
		Graphics_SLP->resize(selections);
		Graphics_Unknown1->resize(selections);
		Graphics_Unknown2->resize(selections);
		Graphics_FrameType->resize(selections);
		Graphics_PlayerColor->resize(selections);
		Graphics_Rainbow->resize(selections);
		Graphics_Replay->resize(selections);
		for(short loop = 0; loop < 4; ++loop)
		{
			Graphics_Coordinates[loop]->resize(selections);
		}
		Graphics_SoundID->resize(selections);
		Graphics_AttackSoundUsed->resize(selections);
		Graphics_FrameCount->resize(selections);
		Graphics_AngleCount->resize(selections);
		Graphics_NewSpeed->resize(selections);
		Graphics_FrameRate->resize(selections);
		Graphics_ReplayDelay->resize(selections);
		Graphics_SequenceType->resize(selections);
		Graphics_ID->resize(selections);
		Graphics_MirroringMode->resize(selections);
		if(GenieVersion >= genie::GV_AoKB)
		Graphics_Unknown3->resize(selections);

		genie::Graphic * GraphicPointer;
		for(auto sel = selections; sel--> 0;)
		{
			GraphicPointer = (genie::Graphic*)Graphics_Graphics_List->GetClientData(Items.Item(sel));
			GraphicIDs[sel] = (GraphicPointer - (&GenieFile->Graphics[0]));

			Graphics_Name->container[sel] = &GraphicPointer->Name;
			Graphics_Name2->container[sel] = &GraphicPointer->Name2;
			Graphics_SLP->container[sel] = &GraphicPointer->SLP;
			Graphics_Unknown1->container[sel] = &GraphicPointer->Unknown1;
			Graphics_Unknown2->container[sel] = &GraphicPointer->Unknown2;
			Graphics_FrameType->container[sel] = &GraphicPointer->Layer;
			Graphics_PlayerColor->container[sel] = &GraphicPointer->PlayerColor;
			Graphics_Rainbow->container[sel] = &GraphicPointer->Rainbow;
			Graphics_Replay->container[sel] = &GraphicPointer->Replay;
			for(short loop = 0; loop < 4; ++loop)
			{
				Graphics_Coordinates[loop]->container[sel] = &GraphicPointer->Coordinates[loop];
			}
			Graphics_SoundID->container[sel] = &GraphicPointer->SoundID;
			Graphics_AttackSoundUsed->container[sel] = &GraphicPointer->AttackSoundUsed;
			Graphics_FrameCount->container[sel] = &GraphicPointer->FrameCount;
			Graphics_AngleCount->container[sel] = &GraphicPointer->AngleCount;
			Graphics_NewSpeed->container[sel] = &GraphicPointer->NewSpeed;
			Graphics_FrameRate->container[sel] = &GraphicPointer->FrameRate;
			Graphics_ReplayDelay->container[sel] = &GraphicPointer->ReplayDelay;
			Graphics_SequenceType->container[sel] = &GraphicPointer->SequenceType;
			Graphics_ID->container[sel] = &GraphicPointer->ID;
			Graphics_MirroringMode->container[sel] = &GraphicPointer->MirroringMode;
			if(GenieVersion >= genie::GV_AoKB)
			Graphics_Unknown3->container[sel] = &GraphicPointer->Unknown3;
		}

		Graphics_Name->Update();
		Graphics_Name2->Update();
		Graphics_SLP->Update();
		Graphics_Unknown1->Update();
		Graphics_Unknown2->Update();
		Graphics_FrameType->Update();
		Graphics_PlayerColor->Update();
		Graphics_Rainbow->Update();
		Graphics_Replay->Update();
		for(short loop = 0; loop < 4; ++loop)
		{
			Graphics_Coordinates[loop]->Update();
		}
		Graphics_SoundID->Update();
		Graphics_AttackSoundUsed->Update();
		Graphics_FrameCount->Update();
		Graphics_AngleCount->Update();
		Graphics_NewSpeed->Update();
		Graphics_FrameRate->Update();
		Graphics_ReplayDelay->Update();
		Graphics_SequenceType->Update();
		Graphics_ID->Update();
		Graphics_MirroringMode->Update();
		if(GenieVersion >= genie::GV_AoKB)
		Graphics_Unknown3->Update();

		selections = GenieVersion < genie::GV_AoE ? 1 : GenieFile->GraphicPointers[GraphicIDs[0]];
	}
	if(!selections)
	{
		Graphics_Name->Clear();
		Graphics_Name2->Clear();
		Graphics_SLP->Clear();
		Graphics_Unknown1->Clear();
		Graphics_Unknown2->Clear();
		Graphics_FrameType->Clear();
		Graphics_PlayerColor->Clear();
		Graphics_PlayerColor_ComboBox->SetSelection(0);
		Graphics_Rainbow->Clear();
		Graphics_Replay->Clear();
		for(short loop = 0; loop < 4; ++loop)
		Graphics_Coordinates[loop]->Clear();
		Graphics_SoundID->Clear();
		Graphics_SoundID_ComboBox->SetSelection(0);
		Graphics_AttackSoundUsed->Clear();
		Graphics_AttackSoundUsed_CheckBox->SetValue(0);
		Graphics_FrameCount->Clear();
		Graphics_AngleCount->Clear();
		Graphics_NewSpeed->Clear();
		Graphics_FrameRate->Clear();
		Graphics_ReplayDelay->Clear();
		Graphics_SequenceType->Clear();
		Graphics_ID->Clear();
		Graphics_MirroringMode->Clear();
		if(GenieVersion >= genie::GV_AoKB)
		Graphics_Unknown3->Clear();
	}
	Graphics_Name->Enable(selections);
	Graphics_Name2->Enable(selections);
	Graphics_SLP->Enable(selections);
	Graphics_Unknown1->Enable(selections);
	Graphics_Unknown2->Enable(selections);
	Graphics_FrameType->Enable(selections);
	Graphics_PlayerColor->Enable(selections);
	Graphics_PlayerColor_ComboBox->Enable(selections);
	Graphics_Rainbow->Enable(selections);
	Graphics_Replay->Enable(selections);
	for(short loop = 0; loop < 4; ++loop)
	Graphics_Coordinates[loop]->Enable(selections);
	Graphics_SoundID->Enable(selections);
	Graphics_SoundID_ComboBox->Enable(selections);
	Graphics_AttackSoundUsed->Enable(selections);
	Graphics_AttackSoundUsed_CheckBox->Enable(selections);
	Graphics_FrameCount->Enable(selections);
	Graphics_AngleCount->Enable(selections);
	Graphics_NewSpeed->Enable(selections);
	Graphics_FrameRate->Enable(selections);
	Graphics_ReplayDelay->Enable(selections);
	Graphics_SequenceType->Enable(selections);
	Graphics_MirroringMode->Enable(selections);
	if(GenieVersion >= genie::GV_AoKB)
	Graphics_Unknown3->Enable(selections);

	Deltas_Add->Enable(selections);
	ListGraphicDeltas();
	ListGraphicAttackSounds();
}

void AGE_Frame::OnGraphicsAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	genie::Graphic Temp;
	Temp.setGameVersion(GenieVersion);
	GenieFile->Graphics.push_back(Temp);
	GenieFile->GraphicPointers.push_back(1);
	if(EnableIDFix)
	GenieFile->Graphics[GenieFile->Graphics.size()-1].ID = (GenieFile->Graphics.size()-1); // ID Fix
	Added = true;
	ListGraphics();
}

void AGE_Frame::OnGraphicsInsert(wxCommandEvent &Event)
{
	auto selections = Graphics_Graphics_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::Graphic Temp;
	Temp.setGameVersion(GenieVersion);
	GenieFile->Graphics.insert(GenieFile->Graphics.begin() + GraphicIDs[0], Temp);
	GenieFile->GraphicPointers.insert(GenieFile->GraphicPointers.begin() + GraphicIDs[0], 1);
	if(EnableIDFix)
	for(short loop = GraphicIDs[0];loop < GenieFile->Graphics.size(); ++loop) // ID Fix
	GenieFile->Graphics[loop].ID = loop;
	ListGraphics();
}

void AGE_Frame::OnGraphicsDelete(wxCommandEvent &Event)
{
	auto selections = Graphics_Graphics_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(auto loop = selections; loop--> 0;)
	{
		GenieFile->Graphics.erase(GenieFile->Graphics.begin() + GraphicIDs[loop]);
		GenieFile->GraphicPointers.erase(GenieFile->GraphicPointers.begin() + GraphicIDs[loop]);
	}
	if(EnableIDFix)
	for(short loop = GraphicIDs[0];loop < GenieFile->Graphics.size(); ++loop) // ID Fix
	GenieFile->Graphics[loop].ID = loop;
	ListGraphics();
}

void AGE_Frame::OnGraphicsCopy(wxCommandEvent &Event)
{
	auto selections = Graphics_Graphics_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	copies->GraphicPointer.resize(selections);
	copies->Graphic.resize(selections);
	for(short loop = 0; loop < selections; ++loop)
	{
		copies->GraphicPointer[loop] = GenieFile->GraphicPointers[GraphicIDs[loop]];
		copies->Graphic[loop] = GenieFile->Graphics[GraphicIDs[loop]];
	}
}

void AGE_Frame::OnGraphicsPaste(wxCommandEvent &Event)
{
	auto selections = Graphics_Graphics_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(copies->Graphic.size()+GraphicIDs[0] > GenieFile->Graphics.size())
	{
		GenieFile->GraphicPointers.resize(copies->GraphicPointer.size()+GraphicIDs[0]);
		GenieFile->Graphics.resize(copies->Graphic.size()+GraphicIDs[0]);
	}
	for(short loop = 0; loop < copies->Graphic.size(); ++loop)
	{
		GenieFile->GraphicPointers[GraphicIDs[0]+loop] = copies->GraphicPointer[loop];
		copies->Graphic[loop].setGameVersion(GenieVersion);
		GenieFile->Graphics[GraphicIDs[0]+loop] = copies->Graphic[loop];
		if(EnableIDFix)
		GenieFile->Graphics[GraphicIDs[0]+loop].ID = (GraphicIDs[0]+loop); // ID Fix
	}
	ListGraphics();
}

void AGE_Frame::OnGraphicsPasteInsert(wxCommandEvent &Event)
{
	auto selections = Graphics_Graphics_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::Graphic Temp;
	GenieFile->GraphicPointers.insert(GenieFile->GraphicPointers.begin() + GraphicIDs[0], copies->GraphicPointer.size(), 0);
	GenieFile->Graphics.insert(GenieFile->Graphics.begin() + GraphicIDs[0], copies->Graphic.size(), Temp);
	for(short loop = 0; loop < copies->Graphic.size(); ++loop)
	{
		GenieFile->GraphicPointers[GraphicIDs[0]+loop] = copies->GraphicPointer[loop];
		copies->Graphic[loop].setGameVersion(GenieVersion);
		GenieFile->Graphics[GraphicIDs[0]+loop] = copies->Graphic[loop];
	}
	if(EnableIDFix)
	for(short loop = GraphicIDs[0];loop < GenieFile->Graphics.size(); ++loop) // ID Fix
	GenieFile->Graphics[loop].ID = loop;
	ListGraphics();
}

void AGE_Frame::OnGraphicsEnable(wxCommandEvent &Event)
{
	auto selections = Graphics_Graphics_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short loop = 0; loop < selections; ++loop)
	{
		GenieFile->GraphicPointers[GraphicIDs[loop]] = 1;
		GenieFile->Graphics[GraphicIDs[loop]].ID = GraphicIDs[loop]; // ID Fix
	}
	ListGraphics();
}

void AGE_Frame::OnGraphicsDisable(wxCommandEvent &Event)
{
	auto selections = Graphics_Graphics_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short loop = 0; loop < selections; ++loop)
	GenieFile->GraphicPointers[GraphicIDs[loop]] = 0;
	ListGraphics();
}

string AGE_Frame::GetGraphicDeltaName(short Index)
{
	if(GenieFile->Graphics[GraphicIDs[0]].Deltas[Index].GraphicID < GenieFile->Graphics.size())
	return GetGraphicName(GenieFile->Graphics[GraphicIDs[0]].Deltas[Index].GraphicID, false);
	return "Re-drawer "+lexical_cast<string>(GenieFile->Graphics[GraphicIDs[0]].Deltas[Index].GraphicID)+" ";
}

void AGE_Frame::OnGraphicDeltasSearch(wxCommandEvent &Event)
{
	ListGraphicDeltas();
}

void AGE_Frame::ListGraphicDeltas()
{
	searchText = Graphics_Deltas_Search->GetValue().Lower();
	excludeText = Graphics_Deltas_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->Graphics[GraphicIDs[0]].Deltas.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetGraphicDeltaName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->Graphics[GraphicIDs[0]].Deltas[loop]);
		}
	}
	Listing(Graphics_Deltas_List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnGraphicDeltasSelect(E);
}

void AGE_Frame::OnGraphicDeltasSelect(wxCommandEvent &Event)
{
	auto selections = Graphics_Deltas_List->GetSelections(Items);
	if(selections > 0)
	{
		DeltaIDs.resize(selections);
		GraphicDeltas_GraphicID->resize(selections);
		GraphicDeltas_Unknown1->resize(selections);
		GraphicDeltas_Unknown2->resize(selections);
		GraphicDeltas_Unknown3->resize(selections);
		GraphicDeltas_DirectionX->resize(selections);
		GraphicDeltas_DirectionY->resize(selections);
		GraphicDeltas_Unknown4->resize(selections);
		GraphicDeltas_Unknown5->resize(selections);

		genie::GraphicDelta * DeltaPointer;
		for(auto loop = selections; loop--> 0;)
		{
			DeltaPointer = (genie::GraphicDelta*)Graphics_Deltas_List->GetClientData(Items.Item(loop));
			DeltaIDs[loop] = (DeltaPointer - (&GenieFile->Graphics[GraphicIDs[0]].Deltas[0]));

			GraphicDeltas_GraphicID->container[loop] = &DeltaPointer->GraphicID;
			GraphicDeltas_Unknown1->container[loop] = &DeltaPointer->Unknown1;
			GraphicDeltas_Unknown2->container[loop] = &DeltaPointer->Unknown2;
			GraphicDeltas_Unknown3->container[loop] = &DeltaPointer->Unknown3;
			GraphicDeltas_DirectionX->container[loop] = &DeltaPointer->DirectionX;
			GraphicDeltas_DirectionY->container[loop] = &DeltaPointer->DirectionY;
			GraphicDeltas_Unknown4->container[loop] = &DeltaPointer->Unknown4;
			GraphicDeltas_Unknown5->container[loop] = &DeltaPointer->Unknown5;
		}

		GraphicDeltas_GraphicID->Update();
		GraphicDeltas_Unknown1->Update();
		GraphicDeltas_Unknown2->Update();
		GraphicDeltas_Unknown3->Update();
		GraphicDeltas_DirectionX->Update();
		GraphicDeltas_DirectionY->Update();
		GraphicDeltas_Unknown4->Update();
		GraphicDeltas_Unknown5->Update();
	}
	else
	{
		GraphicDeltas_GraphicID->Clear();
		GraphicDeltas_GraphicID_ComboBox->SetSelection(0);
		GraphicDeltas_Unknown1->Clear();
		GraphicDeltas_Unknown2->Clear();
		GraphicDeltas_Unknown3->Clear();
		GraphicDeltas_Unknown4->Clear();
		GraphicDeltas_Unknown5->Clear();
		GraphicDeltas_DirectionX->Clear();
		GraphicDeltas_DirectionY->Clear();
	}
	GraphicDeltas_GraphicID->Enable(selections);
	GraphicDeltas_GraphicID_ComboBox->Enable(selections);
	GraphicDeltas_Unknown1->Enable(selections);
	GraphicDeltas_Unknown2->Enable(selections);
	GraphicDeltas_Unknown3->Enable(selections);
	GraphicDeltas_Unknown4->Enable(selections);
	GraphicDeltas_Unknown5->Enable(selections);
	GraphicDeltas_DirectionX->Enable(selections);
	GraphicDeltas_DirectionY->Enable(selections);
}

void AGE_Frame::OnGraphicDeltasAdd(wxCommandEvent &Event)
{
	auto selections = Graphics_Graphics_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->Graphics[GraphicIDs[0]].Deltas);
	ListGraphicDeltas();
}

void AGE_Frame::OnGraphicDeltasInsert(wxCommandEvent &Event)
{
	auto selections = Graphics_Deltas_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->Graphics[GraphicIDs[0]].Deltas, DeltaIDs[0]);
	ListGraphicDeltas();
}

void AGE_Frame::OnGraphicDeltasDelete(wxCommandEvent &Event)
{
	auto selections = Graphics_Deltas_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Graphics[GraphicIDs[0]].Deltas, DeltaIDs);
	ListGraphicDeltas();
}

void AGE_Frame::OnGraphicDeltasCopy(wxCommandEvent &Event)
{
	auto selections = Graphics_Deltas_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Graphics[GraphicIDs[0]].Deltas, DeltaIDs, copies->GraphicDelta);
}

void AGE_Frame::OnGraphicDeltasPaste(wxCommandEvent &Event)
{
	auto selections = Graphics_Deltas_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->Graphics[GraphicIDs[0]].Deltas, DeltaIDs[0], copies->GraphicDelta);
	ListGraphicDeltas();
}

void AGE_Frame::OnGraphicDeltasPasteInsert(wxCommandEvent &Event)
{
	auto selections = Graphics_Deltas_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->Graphics[GraphicIDs[0]].Deltas, DeltaIDs[0], copies->GraphicDelta);
	ListGraphicDeltas();
}

void AGE_Frame::OnGraphicDeltasCopyToGraphics(wxCommandEvent &Event)
{
	for(short loop=1; loop < GraphicIDs.size(); ++loop)
	{
		GenieFile->Graphics[GraphicIDs[loop]].Deltas = GenieFile->Graphics[GraphicIDs[0]].Deltas;
	}
}

string AGE_Frame::GetGraphicAttackSoundName(short Index)
{
	return "Attack sound "+lexical_cast<string>(Index);
}

void AGE_Frame::OnGraphicAttackSoundsSearch(wxCommandEvent &Event)
{
	ListGraphicAttackSounds();
}

void AGE_Frame::ListGraphicAttackSounds()
{
	list<void*> dataPointers;
	wxArrayString names;

	for(short loop = 0; loop < GenieFile->Graphics[GraphicIDs[0]].AttackSounds.size(); ++loop)
	{
		names.Add(" "+FormatInt(loop)+" - "+GetGraphicAttackSoundName(loop));
		dataPointers.push_back((void*)&GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop]);
	}

	Listing(Graphics_AttackSounds_List, names, dataPointers);

	wxCommandEvent E;
	OnGraphicAttackSoundsSelect(E);
}

void AGE_Frame::OnGraphicAttackSoundsSelect(wxCommandEvent &Event)
{
	auto selections = Graphics_AttackSounds_List->GetSelections(Items);
	if(selections > 0)
	{
		AttackSoundIDs.resize(selections);
		Graphics_AttackSoundID[0]->resize(selections);
		Graphics_AttackSoundID[1]->resize(selections);
		Graphics_AttackSoundID[2]->resize(selections);
		Graphics_AttackSoundDelay[0]->resize(selections);
		Graphics_AttackSoundDelay[1]->resize(selections);
		Graphics_AttackSoundDelay[2]->resize(selections);

		genie::GraphicAttackSound * AttackSoundPointer;
		for(auto sel = selections; sel--> 0;)
		{
			AttackSoundPointer = (genie::GraphicAttackSound*)Graphics_AttackSounds_List->GetClientData(Items.Item(sel));
			AttackSoundIDs[sel] = (AttackSoundPointer - (&GenieFile->Graphics[GraphicIDs[0]].AttackSounds[0]));

			Graphics_AttackSoundID[0]->container[sel] = &AttackSoundPointer->SoundID;
			Graphics_AttackSoundID[1]->container[sel] = &AttackSoundPointer->SoundID2;
			Graphics_AttackSoundID[2]->container[sel] = &AttackSoundPointer->SoundID3;
			Graphics_AttackSoundDelay[0]->container[sel] = &AttackSoundPointer->SoundDelay;
			Graphics_AttackSoundDelay[1]->container[sel] = &AttackSoundPointer->SoundDelay2;
			Graphics_AttackSoundDelay[2]->container[sel] = &AttackSoundPointer->SoundDelay3;
		}

		Graphics_AttackSoundID[0]->Update();
		Graphics_AttackSoundID[1]->Update();
		Graphics_AttackSoundID[2]->Update();
		Graphics_AttackSoundDelay[0]->Update();
		Graphics_AttackSoundDelay[1]->Update();
		Graphics_AttackSoundDelay[2]->Update();
	}
	else
	{
		for(short loop = 0; loop < 3; ++loop)
		{
			Graphics_AttackSoundID[loop]->Clear();
			Graphics_AttackSoundID_ComboBox[loop]->SetSelection(0);
			Graphics_AttackSoundDelay[loop]->Clear();
		}
	}
	for(short loop = 0; loop < 3; ++loop)
	{
		Graphics_AttackSoundID[loop]->Enable(selections);
		Graphics_AttackSoundID_ComboBox[loop]->Enable(selections);
		Graphics_AttackSoundDelay[loop]->Enable(selections);
	}
}

void AGE_Frame::OnGraphicAttackSoundsCopy(wxCommandEvent &Event)
{
	auto selections = Graphics_AttackSounds_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::GraphicAttackSound Copy = GenieFile->Graphics[GraphicIDs[0]].AttackSounds[AttackSoundIDs[0]];
	for(short loop2 = 0; loop2 < GenieFile->Graphics[GraphicIDs[0]].AttackSounds.size(); ++loop2)
	GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop2] = Copy;
}

void AGE_Frame::OnGraphicAttackSoundsCopyToGraphics(wxCommandEvent &Event)
{
	for(short loop=1; loop < GraphicIDs.size(); ++loop)
	{
		GenieFile->Graphics[GraphicIDs[loop]].AttackSounds = GenieFile->Graphics[GraphicIDs[0]].AttackSounds;
	}
}

void AGE_Frame::CreateGraphicsControls()
{

	Tab_Graphics = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	Graphics_Main = new wxBoxSizer(wxHORIZONTAL);
	Graphics_ListArea = new wxBoxSizer(wxVERTICAL);
	Graphics_Graphics = new wxStaticBoxSizer(wxVERTICAL, Tab_Graphics, "Graphics  (Search by enter)");

	Graphics_Graphics_Search = new wxTextCtrl(Tab_Graphics, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Graphics_Graphics_UseAnd[0] = new wxCheckBox(Tab_Graphics, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Graphics_Graphics_Search_R = new wxTextCtrl(Tab_Graphics, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Graphics_Graphics_UseAnd[1] = new wxCheckBox(Tab_Graphics, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	for(short loop = 0; loop < 2; ++loop)
	{
		Graphics_Graphics_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Graphics_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_Graphics, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	Graphics_Graphics_List = new wxListBox(Tab_Graphics, wxID_ANY, wxDefaultPosition, wxSize(200, 100), 0, NULL, wxLB_EXTENDED);
	//Graphics_Graphics_ListV = new AGEListCtrl(Tab_Graphics, wxSize(10, 100));
	Graphics_Graphics_Buttons = new wxGridSizer(3, 0, 0);
	Graphics_Add = new wxButton(Tab_Graphics, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Graphics_Insert = new wxButton(Tab_Graphics, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Graphics_Delete = new wxButton(Tab_Graphics, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Graphics_Copy = new wxButton(Tab_Graphics, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Graphics_Paste = new wxButton(Tab_Graphics, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Graphics_PasteInsert = new wxButton(Tab_Graphics, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	Graphics_Enable = new wxButton(Tab_Graphics, wxID_ANY, "Enable", wxDefaultPosition, wxSize(5, 20));
	Graphics_Disable = new wxButton(Tab_Graphics, wxID_ANY, "Disable", wxDefaultPosition, wxSize(5, 20));

	Graphics_DataArea = new wxBoxSizer(wxVERTICAL);
	Graphics_Scroller = new wxScrolledWindow(Tab_Graphics, wxID_ANY, wxDefaultPosition, wxSize(600, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Graphics_ScrollArea = new wxBoxSizer(wxHORIZONTAL);
	Graphics_ScrollSpace = new wxBoxSizer(wxVERTICAL);
	Graphics_NameArea_Holder = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Name_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Name_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Name = new TextCtrl_String(Graphics_Scroller);
	Graphics_Name2_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Name2_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " SLP Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Name2 = new TextCtrl_String(Graphics_Scroller);
	Graphics_ID_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_ID_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " ID", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_ID = new TextCtrl_Short(Graphics_Scroller);

	Graphics_SLP_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_SLP_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SLP = new TextCtrl_Long(Graphics_Scroller);
	Graphics_FrameType_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_FrameType_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Layer *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameType = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_FrameType->SetToolTip("0 - Cliffs\n5 - Shadows, Farms\n6 - Rubble\n10 - Construction sequences, some shadows, corpses, stumps, flowers, paths, ruins, crack\n11 - Fish\n19 - Rugs, crater\n20 - Buildings, damage flames, mill animation, units\n21 - Blacksmith piece (no slp), blacksmith smoke\n22 - Hawk\n30 - Explosions, projectiles ");
	Graphics_Replay_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Replay_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Replay *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Replay = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_Replay->SetToolTip("Will the graphic be looped?");
	Graphics_ReplayDelay_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_ReplayDelay_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Replay Delay *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_ReplayDelay = new TextCtrl_Float(Graphics_Scroller);
	Graphics_ReplayDelay->SetToolTip("Waiting time in seconds before animation restarts again");

	Graphics_FrameCount_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_FrameCount_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Frame Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameCount = new TextCtrl_UShort(Graphics_Scroller);
	Graphics_FrameRate_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_FrameRate_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Frame Rate *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameRate = new TextCtrl_Float(Graphics_Scroller);
	Graphics_FrameRate->SetToolTip("How long each frame is displayed in seconds");
	Graphics_SequenceType_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_SequenceType_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sequence Type *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SequenceType = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_SequenceType->SetToolTip("Animation type?\n6 Changes frames when placed in the scenario editor");
	Graphics_Type_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Type_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Mirroring Mode", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_MirroringMode = new TextCtrl_Byte(Graphics_Scroller);

	Graphics_Coordinates_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_CoordinateGrid_Holder = new wxGridSizer(4, 0, 5);
	Graphics_Coordinates_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Coordinates", wxDefaultPosition, wxSize(630, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 4; ++loop)
	Graphics_Coordinates[loop] = new TextCtrl_Short(Graphics_Scroller);

	Graphics_SoundID_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_SoundID_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SoundID = new TextCtrl_Short(Graphics_Scroller);
	Graphics_SoundID_ComboBox = new ComboBox_Plus1(Graphics_Scroller, Graphics_SoundID);
	SoundComboBoxList.push_back(Graphics_SoundID_ComboBox);
	Graphics_PlayerColor_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_PlayerColor_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Forced Player Color *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_PlayerColor = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_PlayerColor->SetToolTip("The player color to be forced on the graphic");
	Graphics_PlayerColor_ComboBox = new ComboBox_Plus1(Graphics_Scroller, Graphics_PlayerColor);
	Graphics_Rainbow_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Rainbow_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Rainbow *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Rainbow = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_Rainbow->SetToolTip("Makes the graphic change its player color according to nearby units");
	Graphics_NewSpeed_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_NewSpeed_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unit Speed Multiplier *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_NewSpeed = new TextCtrl_Float(Graphics_Scroller);
	Graphics_NewSpeed->SetToolTip("Multiplies the speed of the unit this graphic is applied to");

	Graphics_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Unknown1_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown1 = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Unknown2_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown2 = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_Unknown3_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 3 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown3 = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_Unknown3->SetToolTip("Related to sprite editor?");
	Graphics_4_Holder = new wxBoxSizer(wxHORIZONTAL);
	Graphics_5_Holder = new wxBoxSizer(wxHORIZONTAL);
	Graphics_1_Grid = new wxGridSizer(4, 5, 5);
	Graphics_2_Grid = new wxGridSizer(4, 5, 5);
	Graphics_3_Grid = new wxGridSizer(4, 5, 5);

	Graphics_Deltas = new wxBoxSizer(wxVERTICAL);
	Graphics_Deltas_Search = new wxTextCtrl(Graphics_Scroller, wxID_ANY);
	Graphics_Deltas_Search_R = new wxTextCtrl(Graphics_Scroller, wxID_ANY);
	Graphics_Deltas_List = new wxListBox(Graphics_Scroller, wxID_ANY, wxDefaultPosition, wxSize(140, 140), 0, NULL, wxLB_EXTENDED);
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
	GraphicDeltas_GraphicID = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_GraphicID_ComboBox = new ComboBox_Plus1(Graphics_Scroller, GraphicDeltas_GraphicID);
	GraphicComboBoxList.push_back(GraphicDeltas_GraphicID_ComboBox);
	GraphicDeltas_DirectionX_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_DirectionX_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Direction X", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_DirectionX = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_DirectionY_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_DirectionY_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Direction Y", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_DirectionY = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Unknown1_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown1 = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Unknown2_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown2 = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Unknown3_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown3 = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_Unknown4_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Unknown4_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown4 = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Unknown5_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown5 = new TextCtrl_Short(Graphics_Scroller);

	Graphics_AngleCount_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_AngleCount_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Angle Count *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_AngleCount = new TextCtrl_UShort(Graphics_Scroller);
	Graphics_AngleCount->SetToolTip("The number of directions that a unit/ship faces");
	Graphics_AttackSoundUsed_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_AttackSoundUsed1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Graphics_AttackSoundUsed_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Attack Sound Used", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_AttackSoundUsed = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_AttackSoundUsed_CheckBox = new CheckBox_2State(Graphics_Scroller, "Used", Graphics_AttackSoundUsed);
	Graphics_AttackSounds = new wxBoxSizer(wxVERTICAL);
	Graphics_AttackSounds_List = new wxListBox(Graphics_Scroller, wxID_ANY, wxDefaultPosition, wxSize(140, 140), 0, NULL, wxLB_EXTENDED);
	AttackSounds_Copy = new wxButton(Graphics_Scroller, wxID_ANY, "Copy to all", wxDefaultPosition, wxSize(10, 20));
	AttackSounds_CopyToGraphics = new wxButton(Graphics_Scroller, wxID_ANY, "Copy all to selected graphics", wxDefaultPosition, wxSize(10, 20));
	Graphics_AttackSounds_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_AttackSounds_Grid = new wxGridSizer(2, 0, 0);
	Graphics_AttackSounds_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_AttackSoundDelays_Holder = new wxBoxSizer(wxVERTICAL);
	Graphics_AttackSoundDelays_Text = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound Delay", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 3; ++loop)
	{
		Graphics_AttackSoundID[loop] = new TextCtrl_Short(Graphics_Scroller);
		Graphics_AttackSoundID_ComboBox[loop] = new ComboBox_Plus1(Graphics_Scroller, Graphics_AttackSoundID[loop]);
		SoundComboBoxList.push_back(Graphics_AttackSoundID_ComboBox[loop]);
		Graphics_AttackSoundDelay[loop] = new TextCtrl_Short(Graphics_Scroller);
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
	Graphics_Graphics_Searches[0]->AddSpacer(2);
	Graphics_Graphics_Searches[0]->Add(Graphics_Graphics_UseAnd[0], 0, wxEXPAND);
	Graphics_Graphics_Searches[1]->Add(Graphics_Graphics_Search_R, 1, wxEXPAND);
	Graphics_Graphics_Searches[1]->AddSpacer(2);
	Graphics_Graphics_Searches[1]->Add(Graphics_Graphics_UseAnd[1], 0, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Graphics_Graphics->Add(Graphics_Graphics_Searches[loop], 0, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Graphics_Graphics->Add(Graphics_SearchFilters[loop], 0, wxEXPAND);
	Graphics_Graphics->AddSpacer(2);
	Graphics_Graphics->Add(Graphics_Graphics_List, 1, wxEXPAND);
	//Graphics_Graphics->Add(Graphics_Graphics_ListV, 2, wxEXPAND);
	Graphics_Graphics->AddSpacer(2);
	Graphics_Graphics->Add(Graphics_Graphics_Buttons, 0, wxEXPAND);

	Graphics_ListArea->AddSpacer(5);
	Graphics_ListArea->Add(Graphics_Graphics, 1, wxEXPAND);
	Graphics_ListArea->AddSpacer(5);

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
	Graphics_Coordinates_Holder->Add(Graphics_CoordinateGrid_Holder, 1, wxEXPAND);
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
	Graphics_AttackSoundUsed1_Holder->AddSpacer(2);
	Graphics_AttackSoundUsed1_Holder->Add(Graphics_AttackSoundUsed_CheckBox, 1, wxEXPAND);
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
	Graphics_NameArea_Holder->AddSpacer(5);
	Graphics_NameArea_Holder->Add(Graphics_Name2_Holder, 2, wxEXPAND);
	Graphics_NameArea_Holder->AddSpacer(5);
	Graphics_NameArea_Holder->Add(Graphics_ID_Holder, 1, wxEXPAND);

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
	Graphics_Deltas->AddSpacer(2);
	Graphics_Deltas->Add(Graphics_Deltas_List, 1, wxEXPAND);
	Graphics_Deltas->AddSpacer(2);
	Graphics_Deltas->Add(Graphics_Deltas_Buttons, 0, wxEXPAND);
	Graphics_Deltas->AddSpacer(2);
	Graphics_Deltas->Add(Deltas_CopyToGraphics, 0, wxEXPAND);

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
	GraphicDeltas_Unknown4_Holder->Add(GraphicDeltas_Unknown4_Text, 0, wxEXPAND);
	GraphicDeltas_Unknown4_Holder->Add(GraphicDeltas_Unknown4, 1, wxEXPAND);
	GraphicDeltas_Unknown5_Holder->Add(GraphicDeltas_Unknown5_Text, 0, wxEXPAND);
	GraphicDeltas_Unknown5_Holder->Add(GraphicDeltas_Unknown5, 1, wxEXPAND);

	Graphics_Deltas_Holder_Data1->Add(GraphicDeltas_GraphicID_Holder, 1, wxEXPAND);
	Graphics_Deltas_Holder_Data1->AddSpacer(5);
	Graphics_Deltas_Holder_Data1->Add(GraphicDeltas_DirectionX_Holder, 1, wxEXPAND);
	Graphics_Deltas_Holder_Data1->AddSpacer(5);
	Graphics_Deltas_Holder_Data1->Add(GraphicDeltas_DirectionY_Holder, 1, wxEXPAND);
	Graphics_Deltas_Grid_Data2->Add(GraphicDeltas_Unknown1_Holder, 1, wxEXPAND);
	Graphics_Deltas_Grid_Data2->Add(GraphicDeltas_Unknown2_Holder, 1, wxEXPAND);
	Graphics_Deltas_Grid_Data2->Add(GraphicDeltas_Unknown3_Holder, 1, wxEXPAND);
	Graphics_Deltas_Grid_Data2->Add(GraphicDeltas_Unknown4_Holder, 1, wxEXPAND);
	Graphics_Deltas_Grid_Data2->Add(GraphicDeltas_Unknown5_Holder, 1, wxEXPAND);
	Graphics_Deltas_Holder_Data->Add(Graphics_Deltas_Holder_Data1, 0, wxEXPAND);
	Graphics_Deltas_Holder_Data->AddSpacer(5);
	Graphics_Deltas_Holder_Data->Add(Graphics_Deltas_Grid_Data2, 0, wxEXPAND);

	Graphics_Deltas_Holder->Add(Graphics_Deltas, 1, wxEXPAND);
	Graphics_Deltas_Holder->AddSpacer(5);
	Graphics_Deltas_Holder->Add(Graphics_Deltas_Holder_Data, 3, wxEXPAND);

	Graphics_AttackSounds->Add(Graphics_AttackSounds_List, 1, wxEXPAND);
	Graphics_AttackSounds->AddSpacer(2);
	Graphics_AttackSounds->Add(AttackSounds_Copy, 0, wxEXPAND);
	Graphics_AttackSounds->AddSpacer(2);
	Graphics_AttackSounds->Add(AttackSounds_CopyToGraphics, 0, wxEXPAND);

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
	Graphics_5_Holder->AddSpacer(5);
	Graphics_5_Holder->Add(Graphics_AttackSoundDelays_Holder, 1, wxEXPAND);

	Graphics_4_Holder->Add(Graphics_AngleCount_Holder, 1, wxEXPAND);
	Graphics_4_Holder->AddSpacer(5);
	Graphics_4_Holder->Add(Graphics_AttackSoundUsed_Holder, 1, wxEXPAND);
	Graphics_4_Holder->AddStretchSpacer(2);

	Graphics_AttackSoundArea_Holder->Add(Graphics_AttackSounds, 1, wxEXPAND);
	Graphics_AttackSoundArea_Holder->AddSpacer(5);
	Graphics_AttackSoundArea_Holder->Add(Graphics_5_Holder, 3, wxEXPAND);

	Graphics_ScrollSpace->Add(Graphics_NameArea_Holder, 0, wxEXPAND);
	Graphics_ScrollSpace->AddSpacer(5);
	Graphics_ScrollSpace->Add(Graphics_1_Grid, 0, wxEXPAND);
	Graphics_ScrollSpace->AddSpacer(5);
	Graphics_ScrollSpace->Add(Graphics_Coordinates_Holder, 0, wxEXPAND);
	Graphics_ScrollSpace->AddSpacer(5);
	Graphics_ScrollSpace->Add(Graphics_2_Grid, 0, wxEXPAND);
	Graphics_ScrollSpace->AddSpacer(5);
	Graphics_ScrollSpace->Add(Graphics_3_Grid, 0, wxEXPAND);
	Graphics_ScrollSpace->AddSpacer(5);
	Graphics_ScrollSpace->Add(Graphics_Deltas_Holder, 0, wxEXPAND);
	Graphics_ScrollSpace->AddSpacer(5);
	Graphics_ScrollSpace->Add(Graphics_4_Holder, 0, wxEXPAND);
	Graphics_ScrollSpace->AddSpacer(5);
	Graphics_ScrollSpace->Add(Graphics_AttackSoundArea_Holder, 0, wxEXPAND);

	Graphics_ScrollArea->Add(Graphics_ScrollSpace, 1, wxEXPAND);
	Graphics_ScrollArea->AddSpacer(5);

	Graphics_Scroller->SetSizer(Graphics_ScrollArea);
	Graphics_Scroller->SetScrollRate(0, 15);

	Graphics_DataArea->AddSpacer(5);
	Graphics_DataArea->Add(Graphics_Scroller, 1, wxEXPAND);
	Graphics_DataArea->AddSpacer(5);

	Graphics_Main->AddSpacer(5);
	Graphics_Main->Add(Graphics_ListArea, 21, wxEXPAND);
	Graphics_Main->AddSpacer(5);
	Graphics_Main->Add(Graphics_DataArea, 65, wxEXPAND);
	Graphics_Main->AddSpacer(5);

	if(EnableIDFix)
	Graphics_ID->Enable(false);

	Tab_Graphics->SetSizer(Graphics_Main);

	Connect(Graphics_Graphics_Search->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
	Connect(Graphics_Graphics_Search_R->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
	for(short loop = 0; loop < 2; ++loop)
	{
		Connect(Graphics_Graphics_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
		Connect(Graphics_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
	}
	Connect(Graphics_Graphics_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicsSelect));
	Connect(Graphics_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsAdd));
	Connect(Graphics_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsInsert));
	Connect(Graphics_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsDelete));
	Connect(Graphics_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsCopy));
	Connect(Graphics_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsPaste));
	Connect(Graphics_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsPasteInsert));
	//Connect(Graphics_Extract->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnExtractGraphic));
	//Connect(Graphics_Import->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnImportGraphic));
	Connect(Graphics_Enable->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsEnable));
	Connect(Graphics_Disable->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsDisable));
	Connect(Graphics_Deltas_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSearch));
	Connect(Graphics_Deltas_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSearch));
	Connect(Graphics_Deltas_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSelect));
	Connect(Deltas_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasAdd));
	Connect(Deltas_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasInsert));
	Connect(Deltas_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasDelete));
	Connect(Deltas_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasCopy));
	Connect(Deltas_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasPaste));
	Connect(Deltas_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasPasteInsert));
	Connect(Deltas_CopyToGraphics->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasCopyToGraphics));
	Connect(Graphics_AttackSounds_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicAttackSoundsSelect));
	Connect(AttackSounds_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicAttackSoundsCopy));
	Connect(AttackSounds_CopyToGraphics->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicAttackSoundsCopyToGraphics));

	Graphics_Name->Connect(Graphics_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Graphics), NULL, this);
	Graphics_Name2->Connect(Graphics_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Graphics), NULL, this);
	GraphicDeltas_GraphicID->Connect(GraphicDeltas_GraphicID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Graphics), NULL, this);
	GraphicDeltas_GraphicID_ComboBox->Connect(GraphicDeltas_GraphicID_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Graphics), NULL, this);
	Graphics_AngleCount->Connect(Graphics_AngleCount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Graphics), NULL, this);
	Graphics_AttackSoundUsed->Connect(Graphics_AttackSoundUsed->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Graphics), NULL, this);
	Graphics_AttackSoundUsed_CheckBox->Connect(Graphics_AttackSoundUsed_CheckBox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_Graphics), NULL, this);
}

void AGE_Frame::OnKillFocus_Graphics(wxFocusEvent &Event)
{
	if(((AGETextCtrl*)Event.GetEventObject())->SaveEdits() != 0) return;
	if(Event.GetId() == Graphics_Name->GetId())
	{
		ListGraphics();
	}
	else if(Event.GetId() == GraphicDeltas_GraphicID->GetId())
	{
		ListGraphicDeltas();
	}
	else if(Event.GetId() == Graphics_Name2->GetId())
	{
		wxCommandEvent E;
		OnGraphicsSelect(E);
	}
	else if(Event.GetId() == Graphics_AngleCount->GetId() || Event.GetId() == Graphics_AttackSoundUsed->GetId())
	{
		if(GenieFile->Graphics[GraphicIDs[0]].AttackSoundUsed == 0) return;

		for(short loop = 0; loop < GraphicIDs.size(); ++loop)
		GenieFile->Graphics[GraphicIDs[loop]].AttackSounds.resize(GenieFile->Graphics[GraphicIDs[loop]].AngleCount);

		wxCommandEvent E;
		OnGraphicsSelect(E);
	}
	Event.Skip();
}

void AGE_Frame::OnUpdateCheck_Graphics(wxCommandEvent &Event)
{
	((AGECheckBox*)Event.GetEventObject())->OnUpdate(Event);
	if(GenieFile->Graphics[GraphicIDs[0]].AttackSoundUsed == 0) return;

	for(short loop = 0; loop < GraphicIDs.size(); ++loop)
	GenieFile->Graphics[GraphicIDs[loop]].AttackSounds.resize(GenieFile->Graphics[GraphicIDs[loop]].AngleCount);

	wxCommandEvent E;
	OnGraphicsSelect(E);
}

void AGE_Frame::OnUpdateCombo_Graphics(wxCommandEvent &Event)
{
	((AGEComboBox*)Event.GetEventObject())->OnUpdate(Event);
	ListGraphicDeltas();
}
