#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetTerrainRestrictionName(short Index)
{
	switch(GenieVersion)
	{
		case genie::GV_CC:
		{
			switch(Index)
			{
				case 30: return "Lava";
				case 31: return "Water2";
				case 32: return "Rock4";
			}
		}
		case genie::GV_SWGB:
		{
			switch(Index)
			{
				case 0: return "All";
				case 1: return "Land + unbuildable";
				case 2: return "Shore";
				case 3: return "Water";
				case 4: return "Land";
				case 5: return "Land + shore, impassable water";
				case 6: return "Water + ice2 - swamp";
				case 7: return "Land - water, lava";
				case 8: return "Land - water, lava, farm";
				case 9: return "Only water";
				case 10: return "Land - shore";
				case 11: return "Land - water, lava, farm";
				case 12: return "All - lava";
				case 13: return "Water";
				case 14: return "All - lava";
				case 15: return "Land + shore, impassable water";
				case 16: return "Grass + shore";
				case 17: return "Water - shore + impassable water";
				case 18: return "All - impassable water, lava";
				case 19: return "Land + shore, impassable water";
				case 20: return "Land + shore, impassable water";
				case 21: return "Water - deep water";
				case 22: return "All - impassable water, lava";
				case 23: return "No restriction";
				case 24: return "Only water";
				case 25: return "Land + shore, impassable water";
				case 26: return "Land + shore, impassable water";
				case 27: return "Deep water";
				case 28: return "Wasteland";
				case 29: return "Ice";
				default: return "Restriction";
			}
		}
		case genie::GV_TC:
		{
			switch(Index)
			{
				case 20: return "All - water";
				case 21: return "Shallow water";
			}
		}
		case genie::GV_AoK:
		case genie::GV_AoKA:
		{
			switch(Index)
			{
				case 0: return "All";
				case 1: return "Land + shallows";
				case 2: return "Beach";
				case 3: return "Water";
				case 4: return "Land";
				case 5: return "Nothing";
				case 6: return "Water";
				case 7: return "All - water";
				case 8: return "Land - farm";
				case 9: return "Nothing";
				case 10: return "Land + beach";
				case 11: return "Land - farm";
				case 12: return "All - water bridge";
				case 13: return "Water";
				case 14: return "All - water bridge";
				case 15: return "Water";
				case 16: return "Grass + beach";
				case 17: return "Water (+bridge) - beach";
				case 18: return "All - water bridge";
				case 19: return "Only water + ice";
				default: return "Restriction";
			}
		}
		case genie::GV_RoR:
		case genie::GV_AoE:
		{
			switch(Index)
			{
				case 0: return "Land + water";
				case 1: return "Land";
				case 2: return "Beach";
				case 3: return "Water";
				case 4: return "Land";
				case 5: return "Nothing";
				case 6: return "Water + beach";
				case 7: return "Land + shallows";
				case 8: return "Plain";
				case 9: return "Land - dirt";
				case 10: return "Land + beach";
				default: return "Restriction";
			}
		}
		// Unknown game version
		default: return "Restriction";
	}
}

void AGE_Frame::OnTerrainRestrictionsSearch(wxCommandEvent &Event)
{
	ListTerrainRestrictions(false);
}

void AGE_Frame::ListTerrainRestrictions(bool all)
{
	searchText = TerRestrict_TerRestrict_Search->GetValue().Lower();
	excludeText = TerRestrict_TerRestrict_Search_R->GetValue().Lower();

	auto selections = TerRestrict_TerRestrict_List->GetSelections(Items);
	TerRestrict_TerRestrict_List->Clear();

	wxArrayString names;
	if(all) names.Alloc(GenieFile->TerrainRestrictions.size());

	for(short loop = 0; loop < GenieFile->TerrainRestrictions.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetTerrainRestrictionName(loop);
		if(SearchMatches(Name.Lower()))
		{
			TerRestrict_TerRestrict_List->Append(Name, (void*)&GenieFile->TerrainRestrictions[loop]);
		}
		if(all) names.Add(Name);
	}

	ListingFix(selections, TerRestrict_TerRestrict_List);
	if(all) FillLists(TerrainRestrictionComboBoxList, names);

	wxCommandEvent E;
	OnTerrainRestrictionsSelect(E);
}

void AGE_Frame::OnTerrainRestrictionsSelect(wxCommandEvent &Event)
{
	auto selections = TerRestrict_TerRestrict_List->GetSelections(Items);
	if(selections < 1) return;

	TerRestrictIDs.resize(selections);
	genie::TerrainRestriction * TerRestPointer;
	for(auto loop = selections; loop--> 0;)
	{
		TerRestPointer = (genie::TerrainRestriction*)TerRestrict_TerRestrict_List->GetClientData(Items.Item(loop));
		TerRestrictIDs[loop] = (TerRestPointer - (&GenieFile->TerrainRestrictions[0]));
	}
	ListTerrains(false);
}

void AGE_Frame::OnTerrainRestrictionsTerrainSelect(wxCommandEvent &Event)
{
	wxArrayInt Items2;
	auto selections = TerRestrict_TerRestrict_List->GetSelections(Items);
	auto Selections2 = TerRestrict_Terrains_List->GetSelections(Items2);
	if(Selections2 < 1) return;

	genie::TerrainRestriction * TerRestPointer = (genie::TerrainRestriction*)TerRestrict_TerRestrict_List->GetClientData(Items.Item(0));

	TerRestrictTerIDs.resize(Selections2);
	TerRestrict_Accessible->resize(Selections2);
	if(GenieVersion >= genie::GV_AoKA)	//	Above AoE and RoR
	{
		TerRestrict_Unknown1->resize(Selections2);
		TerRestrict_Graphics[0]->resize(Selections2);
		TerRestrict_Graphics[1]->resize(Selections2);
		TerRestrict_Amount->resize(Selections2);
	}

	genie::Terrain * TerrainPointer;
	for(short loop = Selections2; loop--> 0;)
	{
		TerrainPointer = (genie::Terrain*)TerRestrict_Terrains_List->GetClientData(Items2.Item(loop));
		TerRestrictTerIDs[loop] = (TerrainPointer - (&GenieFile->Terrains[0]));

		TerRestrict_Accessible->container[loop] = &TerRestPointer->TerrainAccessible[TerRestrictTerIDs[loop]];
		if(GenieVersion >= genie::GV_AoKA)	//	Above AoE and RoR
		{
			TerRestrict_Unknown1->container[loop] = &TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].Buildable;
			TerRestrict_Graphics[0]->container[loop] = &TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].GraphicIDs.first;
			TerRestrict_Graphics[1]->container[loop] = &TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].GraphicIDs.second;
			TerRestrict_Amount->container[loop] = &TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].ReplicationAmount;
		}
	}

	TerRestrict_Accessible->ChangeValue(lexical_cast<string>(TerRestPointer->TerrainAccessible[TerRestrictTerIDs[0]]));
	TerRestrict_CheckBox_Accessible->SetValue((bool)TerRestPointer->TerrainAccessible[TerRestrictTerIDs[0]]);

	if(GenieVersion <= genie::GV_RoR) return; // Above AoE and RoR
	TerRestrict_Unknown1->ChangeValue(lexical_cast<string>(TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[0]].Buildable));
	switch(TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[0]].Buildable)
	{
		case 0:
			TerRestrict_CheckBox_Unknown1->SetValue(true);
			break;
		default:
			TerRestrict_CheckBox_Unknown1->SetValue(false);
			break;
	}
	TerRestrict_Graphics[0]->ChangeValue(lexical_cast<string>(TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[0]].GraphicIDs.first));
	TerRestrict_Graphics[1]->ChangeValue(lexical_cast<string>(TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[0]].GraphicIDs.second));
	TerRestrict_ComboBox_Graphics[0]->SetSelection(TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[0]].GraphicIDs.first + 1);
	TerRestrict_ComboBox_Graphics[1]->SetSelection(TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[0]].GraphicIDs.second + 1);
	TerRestrict_Amount->ChangeValue(lexical_cast<string>(TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[0]].ReplicationAmount));
}

void AGE_Frame::OnTerrainRestrictionsAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->TerrainRestrictions);
	GenieFile->TerrainRestrictionPointers1.push_back(1);
	if(GenieVersion >= genie::GV_AoKA)
	GenieFile->TerrainRestrictionPointers2.push_back(1);
	ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsInsert(wxCommandEvent &Event)
{
	auto selections = TerRestrict_TerRestrict_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->TerrainRestrictions, TerRestrictIDs[0]);
	GenieFile->TerrainRestrictionPointers1.insert(GenieFile->TerrainRestrictionPointers1.begin() + TerRestrictIDs[0], 1);
	if(GenieVersion >= genie::GV_AoKA)
	GenieFile->TerrainRestrictionPointers2.insert(GenieFile->TerrainRestrictionPointers2.begin() + TerRestrictIDs[0], 1);
	ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsDelete(wxCommandEvent &Event)
{
	auto selections = TerRestrict_TerRestrict_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(auto loop = selections; loop--> 0;)
	{
		GenieFile->TerrainRestrictions.erase(GenieFile->TerrainRestrictions.begin() + TerRestrictIDs[loop]);
		GenieFile->TerrainRestrictionPointers1.erase(GenieFile->TerrainRestrictionPointers1.begin() + TerRestrictIDs[loop]);
		if(GenieVersion >= genie::GV_AoKA)
		GenieFile->TerrainRestrictionPointers2.erase(GenieFile->TerrainRestrictionPointers2.begin() + TerRestrictIDs[loop]);
	}
	ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsCopy(wxCommandEvent &Event)
{
	auto selections = TerRestrict_TerRestrict_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TerrainRestrictions, TerRestrictIDs, copies->TerrainRestriction);
}

void AGE_Frame::OnTerrainRestrictionsPaste(wxCommandEvent &Event)
{
	auto selections = TerRestrict_TerRestrict_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	// If copies would go beyond the end of these vectors.
	if(copies->TerrainRestriction.size()+TerRestrictIDs[0] > GenieFile->TerrainRestrictions.size())
	{
		GenieFile->TerrainRestrictions.resize(copies->TerrainRestriction.size()+TerRestrictIDs[0]);
		GenieFile->TerrainRestrictionPointers1.resize(copies->TerrainRestriction.size()+TerRestrictIDs[0]);
		if(GenieVersion >= genie::GV_AoKA)
		GenieFile->TerrainRestrictionPointers2.resize(copies->TerrainRestriction.size()+TerRestrictIDs[0]);
	}
	// Actually pasting the copies.
	for(short loop = 0; loop < copies->TerrainRestriction.size(); ++loop)
	{
		copies->TerrainRestriction[loop].setGameVersion(GenieVersion);
		GenieFile->TerrainRestrictions[TerRestrictIDs[0]+loop] = copies->TerrainRestriction[loop];
	}
	ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsPasteInsert(wxCommandEvent &Event)
{
	auto selections = TerRestrict_TerRestrict_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->TerrainRestrictions, TerRestrictIDs[0], copies->TerrainRestriction);
	GenieFile->TerrainRestrictionPointers1.insert(GenieFile->TerrainRestrictionPointers1.begin() + TerRestrictIDs[0], copies->TerrainRestriction.size(), 1);
	if(GenieVersion >= genie::GV_AoKA)
	GenieFile->TerrainRestrictionPointers2.insert(GenieFile->TerrainRestrictionPointers2.begin() + TerRestrictIDs[0], copies->TerrainRestriction.size(), 1);
	ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsTerrainCopy(wxCommandEvent &Event)
{
	auto selections = TerRestrict_TerRestrict_List->GetSelections(Items);
	auto Selections2 = TerRestrict_Terrains_List->GetSelections(Items);
	if(selections < 1 || Selections2 < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible, TerRestrictTerIDs, copies->TerrainRestrictionSubAccess);
	if(GenieVersion >= genie::GV_AoKA)	// not AoE nor RoR
	CopyFromList(GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainPassGraphics, TerRestrictTerIDs, copies->TerrainRestrictionSubGraphics);
}

void AGE_Frame::OnTerrainRestrictionsTerrainPaste(wxCommandEvent &Event)
{
	auto selections = TerRestrict_TerRestrict_List->GetSelections(Items);
	auto Selections2 = TerRestrict_Terrains_List->GetSelections(Items);
	if(selections < 1 || Selections2 < 1) return;

	wxBusyCursor WaitCursor;
	short CopyCount = TerrainRestrictionSubCopyAccess.size();
	if(CopyCount+TerRestrictTerIDs[0] > GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible.size())
	CopyCount -= CopyCount+TerRestrictTerIDs[0] - GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible.size();
	for(short loop = 0; loop < CopyCount; ++loop)
	GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible[TerRestrictTerIDs[0]+loop] = TerrainRestrictionSubCopyAccess[loop];
	if(GenieVersion >= genie::GV_AoKA)	// not AoE nor RoR
	{
		for(short loop = 0; loop < CopyCount; ++loop)
		{
			copies->TerrainRestrictionSubGraphics[loop].setGameVersion(GenieVersion);
			GenieFile->TerrainRestrictions[TerRestrictIDs[0]].TerrainPassGraphics[TerRestrictTerIDs[0]+loop] = copies->TerrainRestrictionSubGraphics[loop];
		}
	}
	wxCommandEvent E;
	OnTerrainRestrictionsTerrainSelect(E);
}

void AGE_Frame::CreateTerrainRestrictionControls()
{
	Tab_TerrainRestrictions = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	TerRestrict_Main = new wxBoxSizer(wxHORIZONTAL);
	TerRestrict_ListArea = new wxBoxSizer(wxVERTICAL);
	TerRestrict_TerRestrict_Buttons = new wxGridSizer(3, 0, 0);
	TerRestrict_TerRestrict = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainRestrictions, "Terrain Restrictions");
	TerRestrict_TerRestrict_Search = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
	TerRestrict_TerRestrict_Search_R = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
	TerRestrict_TerRestrict_List = new wxListBox(Tab_TerrainRestrictions, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TerRestrict_Add = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_Insert = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_Delete = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_Copy = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_Paste = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_PasteInsert = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	TerRestrict_Terrains = new wxBoxSizer(wxVERTICAL);
	TerRestrict_DataArea = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Terrains_Search = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
	TerRestrict_Terrains_Search_R = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
	TerRestrict_Terrains_List = new wxListBox(Tab_TerrainRestrictions, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TerRestrict_Terrains_Buttons = new wxGridSizer(2, 0, 0);
	TerRestrict_Terrains_Copy = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_Terrains_Paste = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_Holder_Accessible = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Holder_Accessible2 = new wxBoxSizer(wxHORIZONTAL);
	TerRestrict_Text_Accessible = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Accessible", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerRestrict_Accessible = new TextCtrl_Float(Tab_TerrainRestrictions);
	TerRestrict_CheckBox_Accessible = new CheckBox_2State(Tab_TerrainRestrictions, "Terrain Is Accessible", TerRestrict_Accessible);
	TerRestrict_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Holder_Unknown1Sub = new wxBoxSizer(wxHORIZONTAL);
	TerRestrict_Text_Unknown1 = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Can Be Built On", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerRestrict_Unknown1 = new TextCtrl_Long(Tab_TerrainRestrictions);
	TerRestrict_CheckBox_Unknown1 = new CheckBox_ZeroIsYes(Tab_TerrainRestrictions, "No", TerRestrict_Unknown1);
	TerRestrict_Holder_Graphics = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Text_Graphics = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Graphics", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerRestrict_Graphics[0] = new TextCtrl_Long(Tab_TerrainRestrictions);
	TerRestrict_ComboBox_Graphics[0] = new ComboBox_Plus1(Tab_TerrainRestrictions, TerRestrict_Graphics[0]);
	GraphicComboBoxList.push_back(TerRestrict_ComboBox_Graphics[0]);
	TerRestrict_Graphics[1] = new TextCtrl_Long(Tab_TerrainRestrictions);
	TerRestrict_ComboBox_Graphics[1] = new ComboBox_Plus1(Tab_TerrainRestrictions, TerRestrict_Graphics[1]);
	GraphicComboBoxList.push_back(TerRestrict_ComboBox_Graphics[1]);
	TerRestrict_Holder_Amount = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Text_Amount = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Replication Amount", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerRestrict_Amount = new TextCtrl_Long(Tab_TerrainRestrictions);

	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Add, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Insert, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Delete, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Copy, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Paste, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_PasteInsert, 1, wxEXPAND);

	TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_Search, 0, wxEXPAND);
	TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_Search_R, 0, wxEXPAND);
	TerRestrict_TerRestrict->Add(-1, 2);
	TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_List, 1, wxEXPAND);
	TerRestrict_TerRestrict->Add(-1, 2);
	TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_Buttons, 0, wxEXPAND);

	TerRestrict_ListArea->Add(-1, 10);
	TerRestrict_ListArea->Add(TerRestrict_TerRestrict, 1, wxEXPAND);
	TerRestrict_ListArea->Add(-1, 10);

	TerRestrict_Terrains_Buttons->Add(TerRestrict_Terrains_Copy, 1, wxEXPAND);
	TerRestrict_Terrains_Buttons->Add(TerRestrict_Terrains_Paste, 1, wxEXPAND);

	TerRestrict_Terrains->Add(-1, 10);
	TerRestrict_Terrains->Add(TerRestrict_Terrains_Search, 0, wxEXPAND);
	TerRestrict_Terrains->Add(TerRestrict_Terrains_Search_R, 0, wxEXPAND);
	TerRestrict_Terrains->Add(-1, 2);
	TerRestrict_Terrains->Add(TerRestrict_Terrains_List, 1, wxEXPAND);
	TerRestrict_Terrains->Add(-1, 2);
	TerRestrict_Terrains->Add(TerRestrict_Terrains_Buttons, 0, wxEXPAND);
	TerRestrict_Terrains->Add(-1, 10);

	TerRestrict_Holder_Accessible2->Add(TerRestrict_Accessible, 1, wxEXPAND);
	TerRestrict_Holder_Accessible2->Add(2, -1);
	TerRestrict_Holder_Accessible2->Add(TerRestrict_CheckBox_Accessible, 2, wxEXPAND);
	TerRestrict_Holder_Accessible->Add(TerRestrict_Text_Accessible, 0, wxEXPAND);
	TerRestrict_Holder_Accessible->Add(TerRestrict_Holder_Accessible2, 1, wxEXPAND);

	TerRestrict_Holder_Unknown1Sub->Add(TerRestrict_Unknown1, 1, wxEXPAND);
	TerRestrict_Holder_Unknown1Sub->Add(2, -1);
	TerRestrict_Holder_Unknown1Sub->Add(TerRestrict_CheckBox_Unknown1, 1, wxEXPAND);
	TerRestrict_Holder_Unknown1->Add(TerRestrict_Text_Unknown1, 0, wxEXPAND);
	TerRestrict_Holder_Unknown1->Add(TerRestrict_Holder_Unknown1Sub, 1, wxEXPAND);
	TerRestrict_Holder_Graphics->Add(TerRestrict_Text_Graphics, 0, wxEXPAND);
	TerRestrict_Holder_Graphics->Add(TerRestrict_Graphics[0], 1, wxEXPAND);
	TerRestrict_Holder_Graphics->Add(TerRestrict_ComboBox_Graphics[0], 1, wxEXPAND);
	TerRestrict_Holder_Graphics->Add(TerRestrict_Graphics[1], 1, wxEXPAND);
	TerRestrict_Holder_Graphics->Add(TerRestrict_ComboBox_Graphics[1], 1, wxEXPAND);
	TerRestrict_Holder_Amount->Add(TerRestrict_Text_Amount, 0, wxEXPAND);
	TerRestrict_Holder_Amount->Add(TerRestrict_Amount, 1, wxEXPAND);

	TerRestrict_DataArea->Add(-1, 10);
	TerRestrict_DataArea->Add(TerRestrict_Holder_Accessible, 0, wxEXPAND);
	TerRestrict_DataArea->Add(-1, 5);
	TerRestrict_DataArea->Add(TerRestrict_Holder_Unknown1, 0, wxEXPAND);
	TerRestrict_DataArea->Add(-1, 5);
	TerRestrict_DataArea->Add(TerRestrict_Holder_Graphics, 0, wxEXPAND);
	TerRestrict_DataArea->Add(-1, 5);
	TerRestrict_DataArea->Add(TerRestrict_Holder_Amount, 0, wxEXPAND);
	TerRestrict_DataArea->Add(-1, 10);

	TerRestrict_Main->Add(10, -1);
	TerRestrict_Main->Add(TerRestrict_ListArea, 1, wxEXPAND);
	TerRestrict_Main->Add(10, -1);
	TerRestrict_Main->Add(TerRestrict_Terrains, 1, wxEXPAND);
	TerRestrict_Main->Add(10, -1);
	TerRestrict_Main->Add(TerRestrict_DataArea, 1, wxEXPAND);
	TerRestrict_Main->AddStretchSpacer(1);

	Tab_TerrainRestrictions->SetSizer(TerRestrict_Main);

	Connect(TerRestrict_TerRestrict_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsSearch));
	Connect(TerRestrict_TerRestrict_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsSearch));
	Connect(TerRestrict_TerRestrict_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsSelect));
	Connect(TerRestrict_Terrains_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	Connect(TerRestrict_Terrains_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	Connect(TerRestrict_Terrains_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainSelect));
	Connect(TerRestrict_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsAdd));
	Connect(TerRestrict_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsInsert));
	Connect(TerRestrict_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsDelete));
	Connect(TerRestrict_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsCopy));
	Connect(TerRestrict_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsPaste));
	Connect(TerRestrict_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsPasteInsert));
	Connect(TerRestrict_Terrains_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainCopy));
	Connect(TerRestrict_Terrains_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainPaste));

	TerRestrict_Accessible->Connect(TerRestrict_Accessible->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TerRestrict), NULL, this);
	TerRestrict_Unknown1->Connect(TerRestrict_Unknown1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TerRestrict), NULL, this);
	TerRestrict_CheckBox_Accessible->Connect(TerRestrict_CheckBox_Accessible->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_TerRestrict), NULL, this);
	TerRestrict_CheckBox_Unknown1->Connect(TerRestrict_CheckBox_Unknown1->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_TerRestrict), NULL, this);
}

void AGE_Frame::OnKillFocus_TerRestrict(wxFocusEvent &Event)
{
	if(!((AGETextCtrl*)Event.GetEventObject())->SaveEdits()) return;
	ListTerrains(false);
	Event.Skip();
}

void AGE_Frame::OnUpdateCheck_TerRestrict(wxCommandEvent &Event)
{
	((AGECheckBox*)Event.GetEventObject())->OnUpdate(Event);
	ListTerrains(false);
}
