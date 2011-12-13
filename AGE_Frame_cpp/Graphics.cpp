/* AGEFrame_cpp/Graphics.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetGraphicName(short Index)
{
	string Name = "";
	if(GenieFile->GraphicPointers[Index] == 0)
	{
		Name += "*Disabled*";
	}
	else if(GenieFile->Graphics[Index].Name != "")
	{
		Name += GenieFile->Graphics[Index].Name;
	}
	else
	{
		Name += "New Graphic";
	}
	return Name;
}

void AGE_Frame::OnGraphicsSearch(wxCommandEvent& Event)
{
	ListGraphics();
}

void AGE_Frame::ListGraphics()
{
	string Name;
	SearchText = wxString(Graphics_Graphics_Search->GetValue()).Lower();
	ExcludeText = wxString(Graphics_Graphics_Search_R->GetValue()).Lower();
	string CompareText;
	
	short Selection = Graphics_Graphics_List->GetSelection();
	short GraphicIDs[22];
	GraphicIDs[0] = Units_ComboBox_ConstructionGraphicID->GetSelection();
	GraphicIDs[1] = Units_ComboBox_SnowGraphicID->GetSelection();
	GraphicIDs[2] = Units_ComboBox_AttackGraphic->GetSelection();
	GraphicIDs[3] = Units_ComboBox_StandingGraphic[0]->GetSelection();
	GraphicIDs[4] = Units_ComboBox_StandingGraphic[1]->GetSelection();
	GraphicIDs[5] = Units_ComboBox_GarrisonGraphic[0]->GetSelection();
	GraphicIDs[6] = Units_ComboBox_GarrisonGraphic[1]->GetSelection();
	GraphicIDs[7] = Units_ComboBox_WalkingGraphic[0]->GetSelection();
	GraphicIDs[8] = Units_ComboBox_WalkingGraphic[1]->GetSelection();
	GraphicIDs[9] = Units_ComboBox_DyingGraphic[0]->GetSelection();
	GraphicIDs[10] = Units_ComboBox_DyingGraphic[1]->GetSelection();
	GraphicIDs[11] = Units_ComboBox_AttackMissileDuplicationGraphic->GetSelection();
	GraphicIDs[12] = UnitCommands_ComboBox_Graphics[0]->GetSelection();
	GraphicIDs[13] = UnitCommands_ComboBox_Graphics[1]->GetSelection();
	GraphicIDs[14] = UnitCommands_ComboBox_Graphics[2]->GetSelection();
	GraphicIDs[15] = UnitCommands_ComboBox_Graphics[3]->GetSelection();
	GraphicIDs[16] = UnitCommands_ComboBox_Graphics[4]->GetSelection();
	GraphicIDs[17] = UnitCommands_ComboBox_Graphics[5]->GetSelection();
	GraphicIDs[18] = DamageGraphics_ComboBox_GraphicID->GetSelection();
	GraphicIDs[19] = TerRestrict_ComboBox_Graphics[0]->GetSelection();
	GraphicIDs[20] = TerRestrict_ComboBox_Graphics[1]->GetSelection();
	GraphicIDs[21] = GraphicDeltas_ComboBox_GraphicID->GetSelection();

	if(Graphics_Graphics_List->GetCount() > 0)
	{
		Graphics_Graphics_List->Clear();
	}
	if(Units_ComboBox_ConstructionGraphicID->GetCount() > 0)
	{
		Units_ComboBox_ConstructionGraphicID->Clear();
	}
	if(Units_ComboBox_SnowGraphicID->GetCount() > 0)
	{
		Units_ComboBox_SnowGraphicID->Clear();
	}
	if(Units_ComboBox_AttackGraphic->GetCount() > 0)
	{
		Units_ComboBox_AttackGraphic->Clear();
	}
	if(Units_ComboBox_StandingGraphic[0]->GetCount() > 0)
	{
		Units_ComboBox_StandingGraphic[0]->Clear();
	}
	if(Units_ComboBox_StandingGraphic[1]->GetCount() > 0)
	{
		Units_ComboBox_StandingGraphic[1]->Clear();
	}
	if(Units_ComboBox_GarrisonGraphic[0]->GetCount() > 0)
	{
		Units_ComboBox_GarrisonGraphic[0]->Clear();
	}
	if(Units_ComboBox_GarrisonGraphic[1]->GetCount() > 0)
	{
		Units_ComboBox_GarrisonGraphic[1]->Clear();
	}
	if(Units_ComboBox_WalkingGraphic[0]->GetCount() > 0)
	{
		Units_ComboBox_WalkingGraphic[0]->Clear();
	}
	if(Units_ComboBox_WalkingGraphic[1]->GetCount() > 0)
	{
		Units_ComboBox_WalkingGraphic[1]->Clear();
	}
	if(Units_ComboBox_DyingGraphic[0]->GetCount() > 0)
	{
		Units_ComboBox_DyingGraphic[0]->Clear();
	}
	if(Units_ComboBox_DyingGraphic[1]->GetCount() > 0)
	{
		Units_ComboBox_DyingGraphic[1]->Clear();
	}
	if(Units_ComboBox_AttackMissileDuplicationGraphic->GetCount() > 0)
	{
		Units_ComboBox_AttackMissileDuplicationGraphic->Clear();
	}
	if(UnitCommands_ComboBox_Graphics[0]->GetCount() > 0)
	{
		UnitCommands_ComboBox_Graphics[0]->Clear();
	}
	if(UnitCommands_ComboBox_Graphics[1]->GetCount() > 0)
	{
		UnitCommands_ComboBox_Graphics[1]->Clear();
	}
	if(UnitCommands_ComboBox_Graphics[2]->GetCount() > 0)
	{
		UnitCommands_ComboBox_Graphics[2]->Clear();
	}
	if(UnitCommands_ComboBox_Graphics[3]->GetCount() > 0)
	{
		UnitCommands_ComboBox_Graphics[3]->Clear();
	}
	if(UnitCommands_ComboBox_Graphics[4]->GetCount() > 0)
	{
		UnitCommands_ComboBox_Graphics[4]->Clear();
	}
	if(UnitCommands_ComboBox_Graphics[5]->GetCount() > 0)
	{
		UnitCommands_ComboBox_Graphics[5]->Clear();
	}
	if(DamageGraphics_ComboBox_GraphicID->GetCount() > 0)
	{
		DamageGraphics_ComboBox_GraphicID->Clear();
	}
	if(TerRestrict_ComboBox_Graphics[0]->GetCount() > 0)
	{
		TerRestrict_ComboBox_Graphics[0]->Clear();
	}
	if(TerRestrict_ComboBox_Graphics[1]->GetCount() > 0)
	{
		TerRestrict_ComboBox_Graphics[1]->Clear();
	}
	if(GraphicDeltas_ComboBox_GraphicID->GetCount() > 0)
	{
		GraphicDeltas_ComboBox_GraphicID->Clear();
	}
	
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < 22;loop++)
	{
		if(GraphicIDs[loop] == wxNOT_FOUND)
		{
			GraphicIDs[loop] = 0;
		}
	}
	
	Units_ComboBox_ConstructionGraphicID->Append("-1 - None");
	Units_ComboBox_SnowGraphicID->Append("-1 - None");
	Units_ComboBox_AttackGraphic->Append("-1 - None");
	Units_ComboBox_StandingGraphic[0]->Append("-1 - None");
	Units_ComboBox_StandingGraphic[1]->Append("-1 - None");
	Units_ComboBox_GarrisonGraphic[0]->Append("-1 - None");
	Units_ComboBox_GarrisonGraphic[1]->Append("-1 - None");
	Units_ComboBox_WalkingGraphic[0]->Append("-1 - None");
	Units_ComboBox_WalkingGraphic[1]->Append("-1 - None");
	Units_ComboBox_DyingGraphic[0]->Append("-1 - None");
	Units_ComboBox_DyingGraphic[1]->Append("-1 - None");
	Units_ComboBox_AttackMissileDuplicationGraphic->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[0]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[1]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[2]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[3]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[4]->Append("-1 - None");
	UnitCommands_ComboBox_Graphics[5]->Append("-1 - None");
	DamageGraphics_ComboBox_GraphicID->Append("-1 - None");
	TerRestrict_ComboBox_Graphics[0]->Append("-1 - None");
	TerRestrict_ComboBox_Graphics[1]->Append("-1 - None");
	GraphicDeltas_ComboBox_GraphicID->Append("-1 - None");
	
	for(short loop = 0;loop < GenieFile->Graphics.size();loop++)
	{
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetGraphicName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetGraphicName(loop)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Graphics_Graphics_List->Append(Name, (void*)&GenieFile->Graphics[loop]);
		}
		Units_ComboBox_ConstructionGraphicID->Append(Name);
		Units_ComboBox_SnowGraphicID->Append(Name);
		Units_ComboBox_AttackGraphic->Append(Name);
		Units_ComboBox_StandingGraphic[0]->Append(Name);
		Units_ComboBox_StandingGraphic[1]->Append(Name);
		Units_ComboBox_GarrisonGraphic[0]->Append(Name);
		Units_ComboBox_GarrisonGraphic[1]->Append(Name);
		Units_ComboBox_WalkingGraphic[0]->Append(Name);
		Units_ComboBox_WalkingGraphic[1]->Append(Name);
		Units_ComboBox_DyingGraphic[0]->Append(Name);
		Units_ComboBox_DyingGraphic[1]->Append(Name);
		Units_ComboBox_AttackMissileDuplicationGraphic->Append(Name);
		UnitCommands_ComboBox_Graphics[0]->Append(Name);
		UnitCommands_ComboBox_Graphics[1]->Append(Name);
		UnitCommands_ComboBox_Graphics[2]->Append(Name);
		UnitCommands_ComboBox_Graphics[3]->Append(Name);
		UnitCommands_ComboBox_Graphics[4]->Append(Name);
		UnitCommands_ComboBox_Graphics[5]->Append(Name);
		DamageGraphics_ComboBox_GraphicID->Append(Name);
		TerRestrict_ComboBox_Graphics[0]->Append(Name);
		TerRestrict_ComboBox_Graphics[1]->Append(Name);
		GraphicDeltas_ComboBox_GraphicID->Append(Name);
	}
	
	Graphics_Graphics_List->SetSelection(0);
	Graphics_Graphics_List->SetFirstItem(Selection - 3);
	Graphics_Graphics_List->SetSelection(Selection);
	Units_ComboBox_ConstructionGraphicID->SetSelection(GraphicIDs[0]);
	Units_ComboBox_SnowGraphicID->SetSelection(GraphicIDs[1]);
	Units_ComboBox_AttackGraphic->SetSelection(GraphicIDs[2]);
	Units_ComboBox_StandingGraphic[0]->SetSelection(GraphicIDs[3]);
	Units_ComboBox_StandingGraphic[1]->SetSelection(GraphicIDs[4]);
	Units_ComboBox_GarrisonGraphic[0]->SetSelection(GraphicIDs[5]);
	Units_ComboBox_GarrisonGraphic[1]->SetSelection(GraphicIDs[6]);
	Units_ComboBox_WalkingGraphic[0]->SetSelection(GraphicIDs[7]);
	Units_ComboBox_WalkingGraphic[1]->SetSelection(GraphicIDs[8]);
	Units_ComboBox_DyingGraphic[0]->SetSelection(GraphicIDs[9]);
	Units_ComboBox_DyingGraphic[1]->SetSelection(GraphicIDs[10]);
	Units_ComboBox_AttackMissileDuplicationGraphic->SetSelection(GraphicIDs[11]);
	UnitCommands_ComboBox_Graphics[0]->SetSelection(GraphicIDs[12]);
	UnitCommands_ComboBox_Graphics[1]->SetSelection(GraphicIDs[13]);
	UnitCommands_ComboBox_Graphics[2]->SetSelection(GraphicIDs[14]);
	UnitCommands_ComboBox_Graphics[3]->SetSelection(GraphicIDs[15]);
	UnitCommands_ComboBox_Graphics[4]->SetSelection(GraphicIDs[16]);
	UnitCommands_ComboBox_Graphics[5]->SetSelection(GraphicIDs[17]);
	DamageGraphics_ComboBox_GraphicID->SetSelection(GraphicIDs[18]);
	TerRestrict_ComboBox_Graphics[0]->SetSelection(GraphicIDs[19]);
	TerRestrict_ComboBox_Graphics[1]->SetSelection(GraphicIDs[20]);
	GraphicDeltas_ComboBox_GraphicID->SetSelection(GraphicIDs[21]);
	
	wxCommandEvent E;
	OnGraphicsSelect(E);
}

void AGE_Frame::OnGraphicsSelect(wxCommandEvent& Event)
{
	short Selection = Graphics_Graphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Graphics_Graphics_List->GetCount() - 1;
			Graphics_Graphics_List->SetSelection(Selection);
		}
		gdat::Graphic * GraphicPointer = (gdat::Graphic*)Graphics_Graphics_List->GetClientData(Selection);
		GraphicID = GraphicPointer - (&GenieFile->Graphics[0]);
//		wxMessageBox("Graphic Pointer: "+lexical_cast<string>(GenieFile->GraphicPointers[GraphicID]));
		Graphics_Name->ChangeValue(GraphicPointer->Name);
		Graphics_Name->Container = &GraphicPointer->Name;
		Graphics_Name2->ChangeValue(GraphicPointer->Name2);
		Graphics_Name2->Container = &GraphicPointer->Name2;
		Graphics_SLP->ChangeValue(lexical_cast<string>(GraphicPointer->SLP));
		Graphics_SLP->Container = &GraphicPointer->SLP;
		Graphics_Unknown1->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown1));
		Graphics_Unknown1->Container = &GraphicPointer->Unknown1;
		Graphics_Unknown2->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown2));
		Graphics_Unknown2->Container = &GraphicPointer->Unknown2;
		Graphics_FrameType->ChangeValue(lexical_cast<string>((short)GraphicPointer->FrameType));
		Graphics_FrameType->Container = &GraphicPointer->FrameType;
		Graphics_Unknown3->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown3));
		Graphics_Unknown3->Container = &GraphicPointer->Unknown3;
		Graphics_Unknown4->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown4));
		Graphics_Unknown4->Container = &GraphicPointer->Unknown4;
		Graphics_Replay->ChangeValue(lexical_cast<string>((short)GraphicPointer->Replay));
		Graphics_Replay->Container = &GraphicPointer->Replay;
		for(short loop = 0;loop < 4;loop++)
		{
			Graphics_Coordinates[loop]->ChangeValue(lexical_cast<string>(GraphicPointer->Coordinates[loop]));
			Graphics_Coordinates[loop]->Container = &GraphicPointer->Coordinates[loop];
		}
		Graphics_SoundID->ChangeValue(lexical_cast<string>(GraphicPointer->SoundID));
		Graphics_SoundID->Container = &GraphicPointer->SoundID;
		Graphics_ComboBox_SoundID->SetSelection(GraphicPointer->SoundID + 1);
		Graphics_AttackSoundUsed->ChangeValue(lexical_cast<string>((short)GraphicPointer->AttackSoundUsed));
		Graphics_AttackSoundUsed->Container = &GraphicPointer->AttackSoundUsed;
		Graphics_CheckBox_AttackSoundUsed->SetValue((bool)GraphicPointer->AttackSoundUsed);
		Graphics_FrameCount->ChangeValue(lexical_cast<string>(GraphicPointer->FrameCount));
		Graphics_FrameCount->Container = &GraphicPointer->FrameCount;
		Graphics_AngleCount->ChangeValue(lexical_cast<string>(GraphicPointer->AngleCount));
		Graphics_AngleCount->Container = &GraphicPointer->AngleCount;
		Graphics_Unknown13->ChangeValue(lexical_cast<string>(GraphicPointer->Unknown13));
		Graphics_Unknown13->Container = &GraphicPointer->Unknown13;
		Graphics_FrameRate->ChangeValue(lexical_cast<string>(GraphicPointer->FrameRate));
		Graphics_FrameRate->Container = &GraphicPointer->FrameRate;
		Graphics_ReplayDelay->ChangeValue(lexical_cast<string>(GraphicPointer->ReplayDelay));
		Graphics_ReplayDelay->Container = &GraphicPointer->ReplayDelay;
		Graphics_SequenceType->ChangeValue(lexical_cast<string>((short)GraphicPointer->SequenceType));
		Graphics_SequenceType->Container = &GraphicPointer->SequenceType;
		Graphics_ID->ChangeValue(lexical_cast<string>(GraphicPointer->ID));
		Graphics_ID->Container = &GraphicPointer->ID;
		if(GameVersion >= 2)
		{
			Graphics_TypeS->SetBackgroundColour(wxColour(210, 230, 255));
			Graphics_TypeS->ChangeValue(lexical_cast<string>(GraphicPointer->Type));
		}
		else
		{
			Graphics_TypeS->SetBackgroundColour(wxColour(255, 235, 215));
			Graphics_TypeS->ChangeValue(lexical_cast<string>((short)GraphicPointer->Type));
		}
		Graphics_TypeS->Container = &GraphicPointer->Type;
		Added = false;
		ListGraphicDeltas(GraphicID);
		ListGraphicAttackSounds(GraphicID);
	}
}

void AGE_Frame::OnGraphicsAdd(wxCommandEvent& Event)
{
	gdat::Graphic Temp;
	GenieFile->Graphics.push_back(Temp);
	GenieFile->GraphicPointers.push_back(1);
	GenieFile->Graphics[GenieFile->Graphics.size() - 1].ID = lexical_cast<short>(GenieFile->Graphics.size() - 1);	//	ID Fix
	Added = true;
	ListGraphics();
}

void AGE_Frame::OnGraphicsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Graphics_Graphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->Graphics.erase(GenieFile->Graphics.begin() + GraphicID);
		GenieFile->GraphicPointers.erase(GenieFile->GraphicPointers.begin() + GraphicID);
		for(short loop = GraphicID;loop < GenieFile->Graphics.size();loop++)	//	ID Fix
		{
			GenieFile->Graphics[loop].ID = lexical_cast<short>(loop);
		}
		if(Selection == Graphics_Graphics_List->GetCount() - 1)
		Graphics_Graphics_List->SetSelection(Selection - 1);
		ListGraphics();
	}
}

void AGE_Frame::OnGraphicsCopy(wxCommandEvent& Event)
{
	short Selection = Graphics_Graphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GraphicCopy = *(gdat::Graphic*)Graphics_Graphics_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnGraphicsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Graphics_Graphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::Graphic*)Graphics_Graphics_List->GetClientData(Selection) = GraphicCopy;
		GenieFile->Graphics[GraphicID].ID = lexical_cast<short>(GraphicID);	//	ID Fix
		ListGraphics();
	}
}

string AGE_Frame::GetGraphicDeltaName(short Index, short GraphicID)
{
	string Name = "";
	Name = "Graphic ID: ";
	Name += lexical_cast<string>(GenieFile->Graphics[GraphicID].Deltas[Index].GraphicID);
	return Name;
}

void AGE_Frame::OnGraphicDeltasSearch(wxCommandEvent& Event)
{
	ListGraphicDeltas(GraphicID);
}

void AGE_Frame::ListGraphicDeltas(short Index)
{
	string Name;
	SearchText = wxString(Graphics_Deltas_Search->GetValue()).Lower();
	ExcludeText = wxString(Graphics_Deltas_Search_R->GetValue()).Lower();
	string CompareText;
	short Selection = Graphics_Deltas_List->GetSelection();

	if(Graphics_Deltas_List->GetCount() > 0)
	{
		Graphics_Deltas_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->Graphics[Index].Deltas.size();loop++)
	{
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetGraphicDeltaName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Name = lexical_cast<string>(loop);
			Name += " - ";
			Name += GetGraphicDeltaName(loop, Index);
			Graphics_Deltas_List->Append(Name, (void*)&GenieFile->Graphics[Index].Deltas[loop]);
		}
	}
	Graphics_Deltas_List->SetSelection(0);
	Graphics_Deltas_List->SetFirstItem(Selection - 3);
	Graphics_Deltas_List->SetSelection(Selection);

	wxCommandEvent E;
	OnGraphicDeltasSelect(E);
}

void AGE_Frame::OnGraphicDeltasSelect(wxCommandEvent& Event)
{
	short Selection = Graphics_Deltas_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Graphics_Deltas_List->GetCount() - 1;
			Graphics_Deltas_List->SetSelection(Selection);
		}
		gdat::GraphicDelta * DeltaPointer = (gdat::GraphicDelta*)Graphics_Deltas_List->GetClientData(Selection);
		DeltaID = DeltaPointer - (&GenieFile->Graphics[GraphicID].Deltas[0]);
		GraphicDeltas_GraphicID->ChangeValue(lexical_cast<string>(DeltaPointer->GraphicID));
		GraphicDeltas_GraphicID->Container = &DeltaPointer->GraphicID;
		GraphicDeltas_ComboBox_GraphicID->SetSelection(DeltaPointer->GraphicID + 1);
		GraphicDeltas_Unknown1->ChangeValue(lexical_cast<string>(DeltaPointer->Unknown1));
		GraphicDeltas_Unknown1->Container = &DeltaPointer->Unknown1;
		GraphicDeltas_Unknown2->ChangeValue(lexical_cast<string>(DeltaPointer->Unknown2));
		GraphicDeltas_Unknown2->Container = &DeltaPointer->Unknown2;
		GraphicDeltas_Unknown3->ChangeValue(lexical_cast<string>(DeltaPointer->Unknown3));
		GraphicDeltas_Unknown3->Container = &DeltaPointer->Unknown3;
		GraphicDeltas_DirectionX->ChangeValue(lexical_cast<string>(DeltaPointer->DirectionX));
		GraphicDeltas_DirectionX->Container = &DeltaPointer->DirectionX;
		GraphicDeltas_DirectionY->ChangeValue(lexical_cast<string>(DeltaPointer->DirectionY));
		GraphicDeltas_DirectionY->Container = &DeltaPointer->DirectionY;
		GraphicDeltas_Unknown4->ChangeValue(lexical_cast<string>(DeltaPointer->Unknown4));
		GraphicDeltas_Unknown4->Container = &DeltaPointer->Unknown4;
		GraphicDeltas_Unknown5->ChangeValue(lexical_cast<string>(DeltaPointer->Unknown5));
		GraphicDeltas_Unknown5->Container = &DeltaPointer->Unknown5;
		Added = false;
	}
	else
	{
		GraphicDeltas_GraphicID->ChangeValue("0");
		GraphicDeltas_ComboBox_GraphicID->SetSelection(0);
		GraphicDeltas_Unknown1->ChangeValue("0");
		GraphicDeltas_Unknown2->ChangeValue("0");
		GraphicDeltas_Unknown3->ChangeValue("0");
		GraphicDeltas_Unknown4->ChangeValue("0");
		GraphicDeltas_Unknown5->ChangeValue("0");
		GraphicDeltas_DirectionX->ChangeValue("0");
		GraphicDeltas_DirectionY->ChangeValue("0");
	}
}

void AGE_Frame::OnGraphicDeltasAdd(wxCommandEvent& Event)
{
	short Selection = Graphics_Graphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		gdat::GraphicDelta Temp;
		GenieFile->Graphics[GraphicID].Deltas.push_back(Temp);
		Added = true;
		ListGraphicDeltas(GraphicID);
	}
}

void AGE_Frame::OnGraphicDeltasDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Graphics_Deltas_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->Graphics[GraphicID].Deltas.erase(GenieFile->Graphics[GraphicID].Deltas.begin() + DeltaID);
		if(Selection == Graphics_Deltas_List->GetCount() - 1)
		Graphics_Deltas_List->SetSelection(Selection - 1);
		ListGraphicDeltas(GraphicID);
	}
}

void AGE_Frame::OnGraphicDeltasCopy(wxCommandEvent& Event)
{
	short Selection = Graphics_Deltas_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GraphicDeltaCopy = *(gdat::GraphicDelta*)Graphics_Deltas_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnGraphicDeltasPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Graphics_Deltas_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::GraphicDelta*)Graphics_Deltas_List->GetClientData(Selection) = GraphicDeltaCopy;
		ListGraphicDeltas(GraphicID);
	}
}

string AGE_Frame::GetGraphicAttackSoundName(short Index, short GraphicID)
{
	string Name = "";
	Name = "Attack Sound "+lexical_cast<string>(Index);
	return Name;
}

void AGE_Frame::OnGraphicAttackSoundsSearch(wxCommandEvent& Event)
{
	ListGraphicAttackSounds(GraphicID);
}

void AGE_Frame::ListGraphicAttackSounds(short Index)
{
	string Name;
//	SearchText = wxString(Graphics_AttackSounds_Search->GetValue()).Lower();
//	ExcludeText = wxString(Graphics_AttackSounds_Search_R->GetValue()).Lower();
//	string CompareText;
	short Selection = Graphics_AttackSounds_List->GetSelection();

	if(Graphics_AttackSounds_List->GetCount() > 0)
	{
		Graphics_AttackSounds_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->Graphics[Index].AttackSounds.size();loop++)
	{
//		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetGraphicAttackSoundName(loop, Index)).Lower();
//		if(SearchMatches(CompareText) == true)
//		{
			Name = lexical_cast<string>(loop);
			Name += " - ";
			Name += GetGraphicAttackSoundName(loop, Index);
			Graphics_AttackSounds_List->Append(Name, (void*)&GenieFile->Graphics[Index].AttackSounds[loop]);
//		}
	}
	Graphics_AttackSounds_List->SetSelection(0);
	Graphics_AttackSounds_List->SetFirstItem(Selection - 3);
	Graphics_AttackSounds_List->SetSelection(Selection);

	wxCommandEvent E;
	OnGraphicAttackSoundsSelect(E);
}

void AGE_Frame::OnGraphicAttackSoundsSelect(wxCommandEvent& Event)
{
	short Selection = Graphics_AttackSounds_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Graphics_AttackSounds_List->GetCount() - 1;
			Graphics_AttackSounds_List->SetSelection(Selection);
		}
		gdat::GraphicAttackSound * AttackSoundPointer = (gdat::GraphicAttackSound*)Graphics_AttackSounds_List->GetClientData(Selection);
		AttackSoundID = AttackSoundPointer - (&GenieFile->Graphics[GraphicID].AttackSounds[0]);
		Graphics_AttackSoundID[0]->ChangeValue(lexical_cast<string>(AttackSoundPointer->SoundID));
		Graphics_AttackSoundID[0]->Container = &AttackSoundPointer->SoundID;
		Graphics_AttackSoundID[1]->ChangeValue(lexical_cast<string>(AttackSoundPointer->SoundID2));
		Graphics_AttackSoundID[1]->Container = &AttackSoundPointer->SoundID2;
		Graphics_AttackSoundID[2]->ChangeValue(lexical_cast<string>(AttackSoundPointer->SoundID3));
		Graphics_AttackSoundID[2]->Container = &AttackSoundPointer->SoundID3;
		Graphics_ComboBox_AttackSoundID[0]->SetSelection(AttackSoundPointer->SoundID + 1);
		Graphics_ComboBox_AttackSoundID[1]->SetSelection(AttackSoundPointer->SoundID2 + 1);
		Graphics_ComboBox_AttackSoundID[2]->SetSelection(AttackSoundPointer->SoundID3 + 1);
		Graphics_AttackSoundDelay[0]->ChangeValue(lexical_cast<string>(AttackSoundPointer->SoundDelay));
		Graphics_AttackSoundDelay[0]->Container = &AttackSoundPointer->SoundDelay;
		Graphics_AttackSoundDelay[1]->ChangeValue(lexical_cast<string>(AttackSoundPointer->SoundDelay2));
		Graphics_AttackSoundDelay[1]->Container = &AttackSoundPointer->SoundDelay2;
		Graphics_AttackSoundDelay[2]->ChangeValue(lexical_cast<string>(AttackSoundPointer->SoundDelay3));
		Graphics_AttackSoundDelay[2]->Container = &AttackSoundPointer->SoundDelay3;
		Added = false;
	}
	else
	{
		for(short loop = 0;loop < 3;loop++)
		{
			Graphics_AttackSoundID[loop]->ChangeValue("0");
			Graphics_ComboBox_AttackSoundID[loop]->SetSelection(0);
			Graphics_AttackSoundDelay[loop]->ChangeValue("0");
		}
	}
}

void AGE_Frame::OnGraphicAttackSoundsCopy(wxCommandEvent& Event)
{
	short Selection = Graphics_AttackSounds_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GraphicAttackSoundCopy = GenieFile->Graphics[GraphicID].AttackSounds[AttackSoundID];
		for(short loop = 0;loop < GenieFile->Graphics[GraphicID].AttackSounds.size();loop++)
		GenieFile->Graphics[GraphicID].AttackSounds[loop] = GraphicAttackSoundCopy;
	}
}

void AGE_Frame::CreateGraphicsControls()
{

	Tab_Graphics = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	Graphics_Main = new wxBoxSizer(wxHORIZONTAL);
	Graphics_ListArea = new wxBoxSizer(wxVERTICAL);
	Graphics_Graphics = new wxStaticBoxSizer(wxVERTICAL, Tab_Graphics, "Graphic slot");

	Graphics_Graphics_Search = new wxTextCtrl(Tab_Graphics, wxID_ANY);
	Graphics_Graphics_Search_R = new wxTextCtrl(Tab_Graphics, wxID_ANY);
	Graphics_Graphics_UseAnd = new wxCheckBox(Tab_Graphics, wxID_ANY, "Use AND instead of OR", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator);
	Graphics_Graphics_List = new wxListBox(Tab_Graphics, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	Graphics_Graphics_Buttons = new wxGridSizer(2, 0, 0);
	Graphics_Add = new wxButton(Tab_Graphics, wxID_ANY, "Add", wxDefaultPosition, wxSize(-1, 20));
	Graphics_Delete = new wxButton(Tab_Graphics, wxID_ANY, "Delete", wxDefaultPosition, wxSize(-1, 20));
	Graphics_Copy = new wxButton(Tab_Graphics, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Graphics_Paste = new wxButton(Tab_Graphics, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));

	Graphics_DataArea = new wxBoxSizer(wxVERTICAL);
	Graphics_Scroller = new AGE_ScrolledWindow(Tab_Graphics, wxVSCROLL | wxTAB_TRAVERSAL);
	Graphics_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	Graphics_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_NameArea = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Holder_Name = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Name = new wxStaticText(Graphics_Scroller, wxID_ANY, " Name", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Name = new TextCtrl_String(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Name2 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Name2 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Name 2", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Name2 = new TextCtrl_String(Graphics_Scroller, "0", NULL);
	Graphics_Holder_SLP = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_SLP = new wxStaticText(Graphics_Scroller, wxID_ANY, " SLP", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SLP = new TextCtrl_Long(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknowns = new wxGridSizer(5, 0, 5);
	Graphics_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown1 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown1 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown2 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown2 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_FrameType = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_FrameType = new wxStaticText(Graphics_Scroller, wxID_ANY, " Frame Type", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameType = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown3 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown3 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown4 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown4 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown4 = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Replay = new wxBoxSizer(wxVERTICAL);
//	Graphics_Holder_2 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Text_Replay = new wxStaticText(Graphics_Scroller, wxID_ANY, " Replay", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Replay = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Coordinates = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_CoordinateGrid = new wxGridSizer(4, 0, 5);
	Graphics_Text_Coordinates = new wxStaticText(Graphics_Scroller, wxID_ANY, " Coordinates", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 4;loop++)
	Graphics_Coordinates[loop] = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	Graphics_Holder_SoundID = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_SoundID = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SoundID = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	Graphics_ComboBox_SoundID = new ComboBox_Short(Graphics_Scroller, Graphics_SoundID);
	Graphics_Holder_AttackSoundUsed = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_AttackSoundUsed1 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Text_AttackSoundUsed = new wxStaticText(Graphics_Scroller, wxID_ANY, " Attack Sound Used", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_AttackSoundUsed = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_CheckBox_AttackSoundUsed = new CheckBox_Byte(Graphics_Scroller, "Used", Graphics_AttackSoundUsed);
	Graphics_Holder_FrameCount = new wxBoxSizer(wxVERTICAL);
//	Graphics_Holder_3 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Holder_4 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Holder_5 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Text_FrameCount = new wxStaticText(Graphics_Scroller, wxID_ANY, " Frame Count", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameCount = new TextCtrl_UnShort(Graphics_Scroller, "0", NULL);
	Graphics_Holder_AngleCount = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_AngleCount = new wxStaticText(Graphics_Scroller, wxID_ANY, " Angle Count", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_AngleCount = new TextCtrl_UnShort(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Unknown13 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown13 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 13", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown13 = new TextCtrl_Float(Graphics_Scroller, "0", NULL);
	Graphics_Holder_FrameRate = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_FrameRate = new wxStaticText(Graphics_Scroller, wxID_ANY, " Frame Rate", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameRate = new TextCtrl_Float(Graphics_Scroller, "0", NULL);
	Graphics_Holder_ReplayDelay = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_ReplayDelay = new wxStaticText(Graphics_Scroller, wxID_ANY, " Replay Delay", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_ReplayDelay = new TextCtrl_Float(Graphics_Scroller, "0", NULL);
	Graphics_Holder_SequenceType = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_SequenceType = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sequence Type", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SequenceType = new TextCtrl_Byte(Graphics_Scroller, "0", NULL);
	Graphics_Holder_ID = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_ID = new wxStaticText(Graphics_Scroller, wxID_ANY, " ID", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_ID = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	Graphics_Holder_Type = new wxBoxSizer(wxVERTICAL);
	Graphics_Grid_1 = new wxGridSizer(4, 5, 5);
	Graphics_Grid_2 = new wxGridSizer(4, 5, 5);
	Graphics_Text_Type = new wxStaticText(Graphics_Scroller, wxID_ANY, " Type", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_TypeS = new TextCtrl_Short(Graphics_Scroller, "0", NULL);

	Graphics_Deltas = new wxStaticBoxSizer(wxVERTICAL, Graphics_Scroller, "Graphic Deltas slot");
	Graphics_Deltas_Search = new wxTextCtrl(Graphics_Scroller, wxID_ANY);
	Graphics_Deltas_Search_R = new wxTextCtrl(Graphics_Scroller, wxID_ANY);
	Graphics_Deltas_List = new wxListBox(Graphics_Scroller, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	Graphics_Deltas_Buttons = new wxGridSizer(2, 0, 0);
	Deltas_Add = new wxButton(Graphics_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(-1, 20));
	Deltas_Delete = new wxButton(Graphics_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(-1, 20));
	Deltas_Copy = new wxButton(Graphics_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Deltas_Paste = new wxButton(Graphics_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));
	Graphics_AttackSounds = new wxStaticBoxSizer(wxVERTICAL, Graphics_Scroller, "Graphic Attack Sounds slot");
	Graphics_AttackSounds_List = new wxListBox(Graphics_Scroller, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	AttackSounds_Copy = new wxButton(Graphics_Scroller, wxID_ANY, "Copy To All", wxDefaultPosition, wxSize(-1, 20));
	
	GraphicDeltas_Holder_GraphicID = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_GraphicID = new wxStaticText(Graphics_Scroller, wxID_ANY, " Graphic", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_GraphicID = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	GraphicDeltas_ComboBox_GraphicID = new ComboBox_Short(Graphics_Scroller, GraphicDeltas_GraphicID);
	GraphicDeltas_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_Unknown1 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown1 = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	GraphicDeltas_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_Unknown2 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown2 = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	GraphicDeltas_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_Unknown3 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown3 = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	GraphicDeltas_Holder_DirectionX = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_DirectionX = new wxStaticText(Graphics_Scroller, wxID_ANY, " Direction X", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_DirectionX = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	GraphicDeltas_Holder_DirectionY = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_DirectionY = new wxStaticText(Graphics_Scroller, wxID_ANY, " Direction Y", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_DirectionY = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	GraphicDeltas_Holder_Unknown4 = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_Unknown4 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown4 = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	GraphicDeltas_Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_Unknown5 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown5 = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
	Graphics_Holder_AttackSounds = new wxBoxSizer(wxVERTICAL);
	Graphics_Grid_AttackSounds = new wxGridSizer(2, 0, 0);
	Graphics_Text_AttackSounds = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Holder_AttackSoundDelays = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_AttackSoundDelays = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound Delay", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 3;loop++)
	{
		Graphics_AttackSoundDelay[loop] = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
		Graphics_AttackSoundID[loop] = new TextCtrl_Short(Graphics_Scroller, "0", NULL);
		Graphics_ComboBox_AttackSoundID[loop] = new ComboBox_Short(Graphics_Scroller, Graphics_AttackSoundID[loop]);
	}
	
	Graphics_Holder_Deltas = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Holder_Deltas_Data = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_Deltas_Space = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_Deltas_Data1 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Grid_Deltas_Data2 = new wxGridSizer(3, 5, 5);
	Graphics_Holder_AttackSoundArea = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Holder_AttackSounds_Data = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_AttackSounds_Space = new wxBoxSizer(wxVERTICAL);

	Graphics_Graphics_Buttons->Add(Graphics_Add, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Delete, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Copy, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Paste, 1, wxEXPAND);

	Graphics_Graphics->Add(Graphics_Graphics_Search, 0, wxEXPAND);
	Graphics_Graphics->Add(Graphics_Graphics_Search_R, 0, wxEXPAND);
	Graphics_Graphics->Add(Graphics_Graphics_UseAnd, 0, wxEXPAND);
	Graphics_Graphics->Add(-1, 2);
	Graphics_Graphics->Add(Graphics_Graphics_List, 1, wxEXPAND);
	Graphics_Graphics->Add(-1, 2);
	Graphics_Graphics->Add(Graphics_Graphics_Buttons, 0, wxEXPAND);

	Graphics_ListArea->Add(-1, 10);
	Graphics_ListArea->Add(Graphics_Graphics, 1, wxEXPAND);
	Graphics_ListArea->Add(-1, 10);
	
	Graphics_Holder_Name->Add(Graphics_Text_Name, 0, wxEXPAND);
	Graphics_Holder_Name->Add(-1, 2);
	Graphics_Holder_Name->Add(Graphics_Name, 1, wxEXPAND);
	Graphics_Holder_Name2->Add(Graphics_Text_Name2, 0, wxEXPAND);
	Graphics_Holder_Name2->Add(-1, 2);
	Graphics_Holder_Name2->Add(Graphics_Name2, 1, wxEXPAND);
	Graphics_Holder_ID->Add(Graphics_Text_ID, 0, wxEXPAND);
	Graphics_Holder_ID->Add(-1, 2);
	Graphics_Holder_ID->Add(Graphics_ID, 1, wxEXPAND);
	Graphics_Holder_Unknown1->Add(Graphics_Text_Unknown1, 0, wxEXPAND);
	Graphics_Holder_Unknown1->Add(-1, 2);
	Graphics_Holder_Unknown1->Add(Graphics_Unknown1, 1, wxEXPAND);
	Graphics_Holder_Unknown2->Add(Graphics_Text_Unknown2, 0, wxEXPAND);
	Graphics_Holder_Unknown2->Add(-1, 2);
	Graphics_Holder_Unknown2->Add(Graphics_Unknown2, 1, wxEXPAND);
	Graphics_Holder_Unknown3->Add(Graphics_Text_Unknown3, 0, wxEXPAND);
	Graphics_Holder_Unknown3->Add(-1, 2);
	Graphics_Holder_Unknown3->Add(Graphics_Unknown3, 1, wxEXPAND);
	Graphics_Holder_Unknown4->Add(Graphics_Text_Unknown4, 0, wxEXPAND);
	Graphics_Holder_Unknown4->Add(-1, 2);
	Graphics_Holder_Unknown4->Add(Graphics_Unknown4, 1, wxEXPAND);
	for(short loop = 0;loop < 4;loop++)
	Graphics_Holder_CoordinateGrid->Add(Graphics_Coordinates[loop], 1, wxEXPAND);
	Graphics_Holder_Coordinates->Add(Graphics_Text_Coordinates, 0, wxEXPAND);
	Graphics_Holder_Coordinates->Add(-1, 2);
	Graphics_Holder_Coordinates->Add(Graphics_Holder_CoordinateGrid, 1, wxEXPAND);
	Graphics_Holder_Unknown13->Add(Graphics_Text_Unknown13, 0, wxEXPAND);
	Graphics_Holder_Unknown13->Add(-1, 2);
	Graphics_Holder_Unknown13->Add(Graphics_Unknown13, 1, wxEXPAND);
	Graphics_Holder_SLP->Add(Graphics_Text_SLP, 0, wxEXPAND);
	Graphics_Holder_SLP->Add(-1, 2);
	Graphics_Holder_SLP->Add(Graphics_SLP, 1, wxEXPAND);
	Graphics_Holder_FrameType->Add(Graphics_Text_FrameType, 0, wxEXPAND);
	Graphics_Holder_FrameType->Add(-1, 2);
	Graphics_Holder_FrameType->Add(Graphics_FrameType, 1, wxEXPAND);
	Graphics_Holder_Replay->Add(Graphics_Text_Replay, 0, wxEXPAND);
	Graphics_Holder_Replay->Add(-1, 2);
	Graphics_Holder_Replay->Add(Graphics_Replay, 1, wxEXPAND);
	Graphics_Holder_Replay->AddStretchSpacer(1);
	Graphics_Holder_SoundID->Add(Graphics_Text_SoundID, 0, wxEXPAND);
	Graphics_Holder_SoundID->Add(-1, 2);
	Graphics_Holder_SoundID->Add(Graphics_SoundID, 1, wxEXPAND);
	Graphics_Holder_SoundID->Add(Graphics_ComboBox_SoundID, 1, wxEXPAND);
	Graphics_Holder_AttackSoundUsed1->Add(Graphics_AttackSoundUsed, 2, wxEXPAND);
	Graphics_Holder_AttackSoundUsed1->Add(2, -1);
	Graphics_Holder_AttackSoundUsed1->Add(Graphics_CheckBox_AttackSoundUsed, 1, wxEXPAND);
	Graphics_Holder_AttackSoundUsed->Add(Graphics_Text_AttackSoundUsed, 0, wxEXPAND);
	Graphics_Holder_AttackSoundUsed->Add(-1, 2);
	Graphics_Holder_AttackSoundUsed->Add(Graphics_Holder_AttackSoundUsed1, 1, wxEXPAND);
	Graphics_Holder_FrameCount->Add(Graphics_Text_FrameCount, 0, wxEXPAND);
	Graphics_Holder_FrameCount->Add(-1, 2);
	Graphics_Holder_FrameCount->Add(Graphics_FrameCount, 1, wxEXPAND);
	Graphics_Holder_AngleCount->Add(Graphics_Text_AngleCount, 0, wxEXPAND);
	Graphics_Holder_AngleCount->Add(-1, 2);
	Graphics_Holder_AngleCount->Add(Graphics_AngleCount, 1, wxEXPAND);
	Graphics_Holder_FrameRate->Add(Graphics_Text_FrameRate, 0, wxEXPAND);
	Graphics_Holder_FrameRate->Add(-1, 2);
	Graphics_Holder_FrameRate->Add(Graphics_FrameRate, 1, wxEXPAND);
	Graphics_Holder_ReplayDelay->Add(Graphics_Text_ReplayDelay, 0, wxEXPAND);
	Graphics_Holder_ReplayDelay->Add(-1, 2);
	Graphics_Holder_ReplayDelay->Add(Graphics_ReplayDelay, 1, wxEXPAND);
	Graphics_Holder_ReplayDelay->AddStretchSpacer(1);
	Graphics_Holder_SequenceType->Add(Graphics_Text_SequenceType, 0, wxEXPAND);
	Graphics_Holder_SequenceType->Add(-1, 2);
	Graphics_Holder_SequenceType->Add(Graphics_SequenceType, 1, wxEXPAND);
	Graphics_Holder_Type->Add(Graphics_Text_Type, 0, wxEXPAND);
	Graphics_Holder_Type->Add(-1, 2);
	Graphics_Holder_Type->Add(Graphics_TypeS, 1, wxEXPAND);
	
	Graphics_Holder_NameArea->Add(Graphics_Holder_Name, 2, wxEXPAND);
	Graphics_Holder_NameArea->Add(5, -1);
	Graphics_Holder_NameArea->Add(Graphics_Holder_Name2, 2, wxEXPAND);
	Graphics_Holder_NameArea->Add(5, -1);
	Graphics_Holder_NameArea->Add(Graphics_Holder_ID, 1, wxEXPAND);
	
	Graphics_Grid_1->Add(Graphics_Holder_Type, 1, wxEXPAND);
	Graphics_Grid_1->Add(Graphics_Holder_SequenceType, 1, wxEXPAND);
	Graphics_Grid_1->Add(Graphics_Holder_SLP, 1, wxEXPAND);
	Graphics_Grid_1->AddStretchSpacer(1);
	Graphics_Grid_1->Add(Graphics_Holder_FrameType, 1, wxEXPAND);
	Graphics_Grid_1->Add(Graphics_Holder_FrameCount, 1, wxEXPAND);
	Graphics_Grid_1->Add(Graphics_Holder_FrameRate, 1, wxEXPAND);
	Graphics_Grid_2->Add(Graphics_Holder_SoundID, 1, wxEXPAND);
	Graphics_Grid_2->Add(Graphics_Holder_Replay, 1, wxEXPAND);
	Graphics_Grid_2->Add(Graphics_Holder_ReplayDelay, 1, wxEXPAND);

	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown1, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown2, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown3, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown4, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown13, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Graphics_Deltas_Buttons->Add(Deltas_Add, 1, wxEXPAND);
	Graphics_Deltas_Buttons->Add(Deltas_Delete, 1, wxEXPAND);
	Graphics_Deltas_Buttons->Add(Deltas_Copy, 1, wxEXPAND);
	Graphics_Deltas_Buttons->Add(Deltas_Paste, 1, wxEXPAND);

	Graphics_Deltas->Add(Graphics_Deltas_Search, 0, wxEXPAND);
	Graphics_Deltas->Add(Graphics_Deltas_Search_R, 0, wxEXPAND);
	Graphics_Deltas->Add(-1, 2);
	Graphics_Deltas->Add(Graphics_Deltas_List, 1, wxEXPAND);
	Graphics_Deltas->Add(-1, 2);
	Graphics_Deltas->Add(Graphics_Deltas_Buttons, 0, wxEXPAND);

	GraphicDeltas_Holder_GraphicID->Add(GraphicDeltas_Text_GraphicID, 0, wxEXPAND);
	GraphicDeltas_Holder_GraphicID->Add(GraphicDeltas_GraphicID, 1, wxEXPAND);
	GraphicDeltas_Holder_GraphicID->Add(GraphicDeltas_ComboBox_GraphicID, 1, wxEXPAND);
	GraphicDeltas_Holder_Unknown1->Add(GraphicDeltas_Text_Unknown1, 0, wxEXPAND);
	GraphicDeltas_Holder_Unknown1->Add(GraphicDeltas_Unknown1, 1, wxEXPAND);
	GraphicDeltas_Holder_Unknown2->Add(GraphicDeltas_Text_Unknown2, 0, wxEXPAND);
	GraphicDeltas_Holder_Unknown2->Add(GraphicDeltas_Unknown2, 1, wxEXPAND);
	GraphicDeltas_Holder_Unknown3->Add(GraphicDeltas_Text_Unknown3, 0, wxEXPAND);
	GraphicDeltas_Holder_Unknown3->Add(GraphicDeltas_Unknown3, 1, wxEXPAND);
	GraphicDeltas_Holder_DirectionX->Add(GraphicDeltas_Text_DirectionX, 0, wxEXPAND);
	GraphicDeltas_Holder_DirectionX->Add(GraphicDeltas_DirectionX, 1, wxEXPAND);
	GraphicDeltas_Holder_DirectionX->AddStretchSpacer(1);
	GraphicDeltas_Holder_DirectionY->Add(GraphicDeltas_Text_DirectionY, 0, wxEXPAND);
	GraphicDeltas_Holder_DirectionY->Add(GraphicDeltas_DirectionY, 1, wxEXPAND);
	GraphicDeltas_Holder_DirectionY->AddStretchSpacer(1);
	GraphicDeltas_Holder_Unknown4->Add(GraphicDeltas_Text_Unknown4, 0, wxEXPAND);
	GraphicDeltas_Holder_Unknown4->Add(GraphicDeltas_Unknown4, 1, wxEXPAND);
	GraphicDeltas_Holder_Unknown5->Add(GraphicDeltas_Text_Unknown5, 0, wxEXPAND);
	GraphicDeltas_Holder_Unknown5->Add(GraphicDeltas_Unknown5, 1, wxEXPAND);
	
	Graphics_Holder_Deltas_Data1->Add(GraphicDeltas_Holder_GraphicID, 1, wxEXPAND);
	Graphics_Holder_Deltas_Data1->Add(5, -1);
	Graphics_Holder_Deltas_Data1->Add(GraphicDeltas_Holder_DirectionX, 1, wxEXPAND);
	Graphics_Holder_Deltas_Data1->Add(5, -1);
	Graphics_Holder_Deltas_Data1->Add(GraphicDeltas_Holder_DirectionY, 1, wxEXPAND);
	Graphics_Grid_Deltas_Data2->Add(GraphicDeltas_Holder_Unknown1, 1, wxEXPAND);
	Graphics_Grid_Deltas_Data2->Add(GraphicDeltas_Holder_Unknown2, 1, wxEXPAND);
	Graphics_Grid_Deltas_Data2->Add(GraphicDeltas_Holder_Unknown3, 1, wxEXPAND);
	Graphics_Grid_Deltas_Data2->Add(GraphicDeltas_Holder_Unknown4, 1, wxEXPAND);
	Graphics_Grid_Deltas_Data2->Add(GraphicDeltas_Holder_Unknown5, 1, wxEXPAND);
	Graphics_Holder_Deltas_Data->Add(Graphics_Holder_Deltas_Data1, 0, wxEXPAND);
	Graphics_Holder_Deltas_Data->Add(-1, 5);
	Graphics_Holder_Deltas_Data->Add(Graphics_Grid_Deltas_Data2, 0, wxEXPAND);
	
	Graphics_Holder_Deltas_Space->Add(-1, 200);
	Graphics_Holder_Deltas->Add(Graphics_Deltas, 1, wxEXPAND);
	Graphics_Holder_Deltas->Add(5, -1);
	Graphics_Holder_Deltas->Add(Graphics_Holder_Deltas_Data, 3, wxEXPAND);
	Graphics_Holder_Deltas->Add(Graphics_Holder_Deltas_Space, 0, wxEXPAND);

	Graphics_AttackSounds->Add(Graphics_AttackSounds_List, 1, wxEXPAND);
	Graphics_AttackSounds->Add(-1, 2);
	Graphics_AttackSounds->Add(AttackSounds_Copy, 0, wxEXPAND);
	
	Graphics_Holder_AttackSounds->Add(Graphics_Text_AttackSounds, 0, wxEXPAND);
	Graphics_Holder_AttackSounds->Add(-1, 2);
	Graphics_Holder_AttackSounds->Add(Graphics_Grid_AttackSounds, 0, wxEXPAND);
	Graphics_Holder_AttackSoundDelays->Add(Graphics_Text_AttackSoundDelays, 0, wxEXPAND);
	Graphics_Holder_AttackSoundDelays->Add(-1, 2);
	for(short loop = 0;loop < 3;loop++)
	{
		Graphics_Grid_AttackSounds->Add(Graphics_AttackSoundID[loop], 0, wxEXPAND);
		Graphics_Grid_AttackSounds->Add(Graphics_ComboBox_AttackSoundID[loop], 0, wxEXPAND);
		Graphics_Holder_AttackSoundDelays->Add(Graphics_AttackSoundDelay[loop], 0, wxEXPAND);
	}
	Graphics_Holder_5->Add(Graphics_Holder_AttackSounds, 2, wxEXPAND);
	Graphics_Holder_5->Add(5, -1);
	Graphics_Holder_5->Add(Graphics_Holder_AttackSoundDelays, 1, wxEXPAND);

	Graphics_Holder_4->Add(Graphics_Holder_AngleCount, 1, wxEXPAND);
	Graphics_Holder_4->Add(5, -1);
	Graphics_Holder_4->Add(Graphics_Holder_AttackSoundUsed, 1, wxEXPAND);
	Graphics_Holder_4->AddStretchSpacer(1);
	
	Graphics_Holder_AttackSounds_Data->Add(Graphics_Holder_4, 0, wxEXPAND);
	Graphics_Holder_AttackSounds_Data->Add(-1, 5);
	Graphics_Holder_AttackSounds_Data->Add(Graphics_Holder_5, 0, wxEXPAND);
	
	Graphics_Holder_AttackSounds_Space->Add(-1, 160);
	Graphics_Holder_AttackSoundArea->Add(Graphics_AttackSounds, 1, wxEXPAND);
	Graphics_Holder_AttackSoundArea->Add(5, -1);
	Graphics_Holder_AttackSoundArea->Add(Graphics_Holder_AttackSounds_Data, 3, wxEXPAND);
	Graphics_Holder_AttackSoundArea->Add(Graphics_Holder_AttackSounds_Space, 0, wxEXPAND);
	
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_NameArea, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Grid_1, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Grid_2, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_Deltas, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_AttackSoundArea, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_Coordinates, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_Unknowns, 0, wxEXPAND);
	
	Graphics_ScrollerWindows->Add(Graphics_ScrollerWindowsSpace, 1, wxEXPAND);
	Graphics_ScrollerWindows->Add(5, -1);

	Graphics_Scroller->SetSizer(Graphics_ScrollerWindows);
	Graphics_Scroller->SetScrollRate(0, 15);

	Graphics_DataArea->Add(-1, 10);
	Graphics_DataArea->Add(Graphics_Scroller, 1, wxEXPAND);
	Graphics_DataArea->Add(-1, 10);

	Graphics_Main->Add(10, -1);
	Graphics_Main->Add(Graphics_ListArea, 1, wxEXPAND);
	Graphics_Main->Add(10, -1);
	Graphics_Main->Add(Graphics_DataArea, 3, wxEXPAND);
	Graphics_Main->Add(10, -1);
	
	Graphics_ID->Enable(false);
	Graphics_Graphics_UseAnd->Show(false);

	Tab_Graphics->SetSizer(Graphics_Main);
	
	Connect(Graphics_Graphics_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
	Connect(Graphics_Graphics_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
	Connect(Graphics_Graphics_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicsSelect));
	Connect(Graphics_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsAdd));
	Connect(Graphics_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsDelete));
	Connect(Graphics_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsCopy));
	Connect(Graphics_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsPaste));
	Connect(Graphics_Deltas_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSearch));
	Connect(Graphics_Deltas_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSearch));
	Connect(Graphics_Deltas_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSelect));
	Connect(Deltas_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasAdd));
	Connect(Deltas_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasDelete));
	Connect(Deltas_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasCopy));
	Connect(Deltas_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasPaste));
	Connect(Graphics_AttackSounds_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicAttackSoundsSelect));
	Connect(AttackSounds_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicAttackSoundsCopy));

	Graphics_Name->Connect(Graphics_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Graphics_Name2->Connect(Graphics_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	GraphicDeltas_GraphicID->Connect(GraphicDeltas_GraphicID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxShort), NULL, this);
	GraphicDeltas_ComboBox_GraphicID->Connect(GraphicDeltas_ComboBox_GraphicID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxShort), NULL, this);
	Graphics_AngleCount->Connect(Graphics_AngleCount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_UnShort), NULL, this);
	Graphics_AttackSoundUsed->Connect(Graphics_AttackSoundUsed->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_CheckBoxByte), NULL, this);
	Graphics_CheckBox_AttackSoundUsed->Connect(Graphics_CheckBox_AttackSoundUsed->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_CheckBoxByte), NULL, this);

}
