#include "../AGE_Frame.h"

string AGE_Frame::GetTerrainRestrictionName(int index)
{
	switch(GenieVersion)
	{
		case genie::GV_SWGB:
		{
			switch(index)
			{
				case 30: return "Lava";
				case 31: return "Water2";
				case 32: return "Rock4";
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
		case genie::GV_Cysion:
		{
			switch(index)
			{
				case 20: return "All - water";
				case 21: return "Shallow water";
			}
		}
		case genie::GV_AoK:
		case genie::GV_AoKB:
		case genie::GV_AoKA:
		{
			switch(index)
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
		case genie::GV_AoE:
		case genie::GV_AoEB:
		case genie::GV_MATT:
		case genie::GV_DAVE:
		case genie::GV_TEST:
		{
			switch(index)
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

void AGE_Frame::OnTerrainRestrictionsSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTerrainRestrictions(false);
}

void AGE_Frame::ListTerrainRestrictions(bool all)
{
	InitTerrainRestrictions(all);
	wxTimerEvent E;
	OnTerrainRestrictionsTimer(E);
}

void AGE_Frame::InitTerrainRestrictions(bool all)
{
	searchText = TerRestrict_TerRestrict_Search->GetValue().Lower();
	excludeText = TerRestrict_TerRestrict_Search_R->GetValue().Lower();

	TerRestrict_TerRestrict_ListV->names.clear();
	TerRestrict_TerRestrict_ListV->indexes.clear();
	wxArrayString names;
	if(all) names.Alloc(dataset->TerrainRestrictions.size());

	for(short loop = 0; loop < dataset->TerrainRestrictions.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTerrainRestrictionName(loop);
		if(SearchMatches(Name.Lower()))
		{
			TerRestrict_TerRestrict_ListV->names.Add(Name);
			TerRestrict_TerRestrict_ListV->indexes.push_back(loop);
		}
		if(all) names.Add(Name);
	}

	virtualListing(TerRestrict_TerRestrict_ListV);
	if(all) FillLists(TerrainRestrictionComboBoxList, names);
}

void AGE_Frame::OnTerrainRestrictionsSelect(wxCommandEvent &event)
{
    if(!restrictionTimer.IsRunning())
        restrictionTimer.Start(150);
}

void AGE_Frame::OnTerrainRestrictionsTimer(wxTimerEvent &event)
{
    restrictionTimer.Stop();
	auto selections = TerRestrict_TerRestrict_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, TerRestrict_TerRestrict_ListV, TerRestrictIDs);

	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected restriction: "+lexical_cast<string>(TerRestrictIDs[0]), 0);
	ListTerrains2();
}

void AGE_Frame::OnTerrainRestrictionsTerrainSelect(wxCommandEvent &event)
{
    if(!restrictionTerrainTimer.IsRunning())
        restrictionTerrainTimer.Start(150);
}

void AGE_Frame::OnTerrainRestrictionsTerrainTimer(wxTimerEvent &event)
{
    restrictionTerrainTimer.Stop();
	auto selections = TerRestrict_Terrains_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, TerRestrict_Terrains_ListV, TerRestrictTerIDs);

    for(auto &box: uiGroupRestriction) box->clear();

    genie::TerrainRestriction * TerRestPointer;
	for(short rest = TerRestrictIDs.size(); rest--> 0;)
    {
        TerRestPointer = &dataset->TerrainRestrictions[TerRestrictIDs[rest]];
        for(short loop = selections; loop--> 0;)
        {
            TerRestrict_Accessible->prepend(&TerRestPointer->TerrainAccessible[TerRestrictTerIDs[loop]]);
            if(GenieVersion >= genie::GV_AoKA)	//	Above AoE and RoR
            {
                TerRestrict_Unknown1->prepend(&TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].Buildable);
                TerRestrict_Graphics[0]->prepend(&TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].GraphicIDs.first);
                TerRestrict_Graphics[1]->prepend(&TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].GraphicIDs.second);
                TerRestrict_Amount->prepend(&TerRestPointer->TerrainPassGraphics[TerRestrictTerIDs[loop]].ReplicationAmount);
            }
        }
	}

    for(auto &box: uiGroupRestriction) box->update();
}

void AGE_Frame::OnTerrainRestrictionsAdd(wxCommandEvent &event)
{
	if(NULL == dataset) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->TerrainRestrictions);
	dataset->TerrainRestrictionPointers1.push_back(1);
	if(GenieVersion >= genie::GV_AoKA)
	dataset->TerrainRestrictionPointers2.push_back(1);
	ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsInsert(wxCommandEvent &event)
{
	auto selections = TerRestrict_TerRestrict_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->TerrainRestrictions, TerRestrictIDs[0]);
	dataset->TerrainRestrictionPointers1.insert(dataset->TerrainRestrictionPointers1.begin() + TerRestrictIDs[0], 1);
	if(GenieVersion >= genie::GV_AoKA)
	dataset->TerrainRestrictionPointers2.insert(dataset->TerrainRestrictionPointers2.begin() + TerRestrictIDs[0], 1);
	How2List = INSNEW;
	ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsDelete(wxCommandEvent &event)
{
	auto selections = TerRestrict_TerRestrict_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(auto loop = selections; loop--> 0;)
	{
		dataset->TerrainRestrictions.erase(dataset->TerrainRestrictions.begin() + TerRestrictIDs[loop]);
		dataset->TerrainRestrictionPointers1.erase(dataset->TerrainRestrictionPointers1.begin() + TerRestrictIDs[loop]);
		if(GenieVersion >= genie::GV_AoKA)
		dataset->TerrainRestrictionPointers2.erase(dataset->TerrainRestrictionPointers2.begin() + TerRestrictIDs[loop]);
	}
	How2List = DEL;
	ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsCopy(wxCommandEvent &event)
{
	auto selections = TerRestrict_TerRestrict_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TerrainRestrictions, TerRestrictIDs, copies.TerrainRestriction);
	TerRestrict_TerRestrict_ListV->SetFocus();
}

void AGE_Frame::OnTerrainRestrictionsPaste(wxCommandEvent &event)
{
	auto selections = TerRestrict_TerRestrict_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TerRestrictIDs.size(), copies.TerrainRestriction.size()))
		{
			PasteToList(dataset->TerrainRestrictions, TerRestrictIDs, copies.TerrainRestriction);
		}
	}
	else
	{
		// If copies would go beyond the end of these vectors.
		if(copies.TerrainRestriction.size()+TerRestrictIDs[0] > dataset->TerrainRestrictions.size())
		{
			dataset->TerrainRestrictions.resize(copies.TerrainRestriction.size()+TerRestrictIDs[0]);
			dataset->TerrainRestrictionPointers1.resize(copies.TerrainRestriction.size()+TerRestrictIDs[0]);
			if(GenieVersion >= genie::GV_AoKA)
			dataset->TerrainRestrictionPointers2.resize(copies.TerrainRestriction.size()+TerRestrictIDs[0]);
		}
		// Actually pasting the copies.
		PasteToList(dataset->TerrainRestrictions, TerRestrictIDs[0], copies.TerrainRestriction);
	}
	ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsPasteInsert(wxCommandEvent &event)
{
	auto selections = TerRestrict_TerRestrict_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->TerrainRestrictions, TerRestrictIDs[0], copies.TerrainRestriction);
	dataset->TerrainRestrictionPointers1.insert(dataset->TerrainRestrictionPointers1.begin() + TerRestrictIDs[0], copies.TerrainRestriction.size(), 1);
	if(GenieVersion >= genie::GV_AoKA)
	dataset->TerrainRestrictionPointers2.insert(dataset->TerrainRestrictionPointers2.begin() + TerRestrictIDs[0], copies.TerrainRestriction.size(), 1);
	How2List = INSPASTE;
	ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsTerrainCopy(wxCommandEvent &event)
{
	auto selections = TerRestrict_TerRestrict_ListV->GetSelectedItemCount();
	auto Selections2 = TerRestrict_Terrains_ListV->GetSelectedItemCount();
	if(selections < 1 || Selections2 < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible, TerRestrictTerIDs, copies.TerrainRestrictionSubAccess);
	if(GenieVersion >= genie::GV_AoKA)	// not AoE nor RoR
	CopyFromList(dataset->TerrainRestrictions[TerRestrictIDs[0]].TerrainPassGraphics, TerRestrictTerIDs, copies.TerrainRestrictionSubGraphics);
	TerRestrict_Terrains_ListV->SetFocus();
}

void AGE_Frame::OnTerrainRestrictionsTerrainPaste(wxCommandEvent &event)
{
	auto selections = TerRestrict_TerRestrict_ListV->GetSelectedItemCount();
	auto Selections2 = TerRestrict_Terrains_ListV->GetSelectedItemCount();
	if(selections < 1 || Selections2 < 1) return;

	wxBusyCursor WaitCursor;
	short CopyCount = TerrainRestrictionSubCopyAccess.size();
	if(Paste11)
	{
		if(Paste11Check(TerRestrictTerIDs.size(), copies.TerrainRestrictionSubGraphics.size()))
		{
			for(short loop = 0; loop < CopyCount; ++loop)
			dataset->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible[TerRestrictTerIDs[loop]] = TerrainRestrictionSubCopyAccess[loop];
			if(GenieVersion >= genie::GV_AoKA)	// not AoE nor RoR
			{
				for(short loop = 0; loop < CopyCount; ++loop)
				{
					copies.TerrainRestrictionSubGraphics[loop].setGameVersion(GenieVersion);
					dataset->TerrainRestrictions[TerRestrictIDs[0]].TerrainPassGraphics[TerRestrictTerIDs[loop]] = copies.TerrainRestrictionSubGraphics[loop];
				}
			}
		}
	}
	else
	{
		if(CopyCount+TerRestrictTerIDs[0] > dataset->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible.size())
		CopyCount -= CopyCount+TerRestrictTerIDs[0] - dataset->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible.size();
		for(short loop = 0; loop < CopyCount; ++loop)
		dataset->TerrainRestrictions[TerRestrictIDs[0]].TerrainAccessible[TerRestrictTerIDs[0]+loop] = TerrainRestrictionSubCopyAccess[loop];
		if(GenieVersion >= genie::GV_AoKA)	// not AoE nor RoR
		{
			for(short loop = 0; loop < CopyCount; ++loop)
			{
				copies.TerrainRestrictionSubGraphics[loop].setGameVersion(GenieVersion);
				dataset->TerrainRestrictions[TerRestrictIDs[0]].TerrainPassGraphics[TerRestrictTerIDs[0]+loop] = copies.TerrainRestrictionSubGraphics[loop];
			}
		}
	}
	wxTimerEvent E;
	OnTerrainRestrictionsTerrainTimer(E);
}

void AGE_Frame::CreateTerrainRestrictionControls()
{
	Tab_TerrainRestrictions = new wxPanel(TabBar_Main);

	TerRestrict_Main = new wxBoxSizer(wxHORIZONTAL);
	TerRestrict_TerRestrict_Buttons = new wxGridSizer(3, 0, 0);
	TerRestrict_TerRestrict = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainRestrictions, "Terrain Restrictions");
	TerRestrict_TerRestrict_Search = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
	TerRestrict_TerRestrict_Search_R = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
	TerRestrict_TerRestrict_ListV = new AGEListView(Tab_TerrainRestrictions, wxSize(200, 100));
	TerRestrict_Add = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_Insert = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_Delete = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_Copy = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_Paste = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_PasteInsert = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	TerRestrict_Terrains = new wxBoxSizer(wxVERTICAL);
	TerRestrict_DataArea = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Terrains_Search = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
	TerRestrict_Terrains_Search_R = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
	TerRestrict_Terrains_ListV = new AGEListView(Tab_TerrainRestrictions, wxSize(200, 100));
	TerRestrict_Terrains_Buttons = new wxGridSizer(2, 0, 0);
	TerRestrict_Terrains_Copy = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_Terrains_Paste = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TerRestrict_Accessible_Holder = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Accessible2_Holder = new wxBoxSizer(wxHORIZONTAL);
	TerRestrict_Accessible_Text = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Accessible and Damage Multiplier *", wxDefaultPosition, wxSize(200, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerRestrict_Accessible = AGETextCtrl::init(CFloat, &uiGroupRestriction, this, AGEwindow, Tab_TerrainRestrictions, true);
	TerRestrict_Accessible->SetToolTip("See unit armor terrain restriction");
	TerRestrict_Accessible_CheckBox = new CheckBox_2State(Tab_TerrainRestrictions, "Terrain Is Accessible", TerRestrict_Accessible);
	TerRestrict_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Unknown1Sub_Holder = new wxBoxSizer(wxHORIZONTAL);
	TerRestrict_Unknown1_Text = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Can Be Built On", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerRestrict_Unknown1 = AGETextCtrl::init(CLong, &uiGroupRestriction, this, AGEwindow, Tab_TerrainRestrictions);
	TerRestrict_Unknown1_CheckBox = new CheckBox_ZeroIsYes(Tab_TerrainRestrictions, "No", TerRestrict_Unknown1);
	TerRestrict_Graphics_Holder = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Graphics_Text = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Graphics", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerRestrict_Graphics[0] = AGETextCtrl::init(CLong, &uiGroupRestriction, this, AGEwindow, Tab_TerrainRestrictions);
	TerRestrict_Graphics_ComboBox[0] = new ComboBox_Plus1(Tab_TerrainRestrictions, TerRestrict_Graphics[0]);
	GraphicComboBoxList.push_front(TerRestrict_Graphics_ComboBox[0]);
	TerRestrict_Graphics[1] = AGETextCtrl::init(CLong, &uiGroupRestriction, this, AGEwindow, Tab_TerrainRestrictions);
	TerRestrict_Graphics_ComboBox[1] = new ComboBox_Plus1(Tab_TerrainRestrictions, TerRestrict_Graphics[1]);
	GraphicComboBoxList.push_front(TerRestrict_Graphics_ComboBox[1]);
	TerRestrict_Amount_Holder = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Amount_Text = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Replication Amount", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerRestrict_Amount = AGETextCtrl::init(CFloat, &uiGroupRestriction, this, AGEwindow, Tab_TerrainRestrictions);

	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Add, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Delete, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Insert, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Copy, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Paste, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_PasteInsert, 1, wxEXPAND);

	TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_Search, 0, wxEXPAND);
	TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_Search_R, 0, wxEXPAND);
	TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_Buttons, 0, wxEXPAND);

	TerRestrict_Terrains_Buttons->Add(TerRestrict_Terrains_Copy, 1, wxEXPAND);
	TerRestrict_Terrains_Buttons->Add(TerRestrict_Terrains_Paste, 1, wxEXPAND);

	TerRestrict_Terrains->Add(TerRestrict_Terrains_Search, 0, wxEXPAND);
	TerRestrict_Terrains->Add(TerRestrict_Terrains_Search_R, 0, wxEXPAND);
	TerRestrict_Terrains->Add(TerRestrict_Terrains_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	TerRestrict_Terrains->Add(TerRestrict_Terrains_Buttons, 0, wxEXPAND);

	TerRestrict_Accessible2_Holder->Add(TerRestrict_Accessible, 0, wxEXPAND);
	TerRestrict_Accessible2_Holder->Add(TerRestrict_Accessible_CheckBox, 2, wxEXPAND | wxLEFT, 2);
	TerRestrict_Accessible_Holder->Add(TerRestrict_Accessible_Text, 0, wxEXPAND);
	TerRestrict_Accessible_Holder->Add(TerRestrict_Accessible2_Holder, 1, wxEXPAND);

	TerRestrict_Unknown1Sub_Holder->Add(TerRestrict_Unknown1, 1, wxEXPAND);
	TerRestrict_Unknown1Sub_Holder->Add(TerRestrict_Unknown1_CheckBox, 1, wxEXPAND | wxLEFT, 2);
	TerRestrict_Unknown1_Holder->Add(TerRestrict_Unknown1_Text, 0, wxEXPAND);
	TerRestrict_Unknown1_Holder->Add(TerRestrict_Unknown1Sub_Holder, 1, wxEXPAND);
	TerRestrict_Graphics_Holder->Add(TerRestrict_Graphics_Text, 0, wxEXPAND);
	TerRestrict_Graphics_Holder->Add(TerRestrict_Graphics[0], 1, wxEXPAND);
	TerRestrict_Graphics_Holder->Add(TerRestrict_Graphics_ComboBox[0], 1, wxEXPAND);
	TerRestrict_Graphics_Holder->Add(TerRestrict_Graphics[1], 1, wxEXPAND);
	TerRestrict_Graphics_Holder->Add(TerRestrict_Graphics_ComboBox[1], 1, wxEXPAND);
	TerRestrict_Amount_Holder->Add(TerRestrict_Amount_Text, 0, wxEXPAND);
	TerRestrict_Amount_Holder->Add(TerRestrict_Amount, 1, wxEXPAND);

	TerRestrict_DataArea->Add(TerRestrict_Accessible_Holder, 0, wxEXPAND | wxTOP, 5);
	TerRestrict_DataArea->Add(TerRestrict_Unknown1_Holder, 0, wxEXPAND | wxTOP, 5);
	TerRestrict_DataArea->Add(TerRestrict_Graphics_Holder, 0, wxEXPAND | wxTOP, 5);
	TerRestrict_DataArea->Add(TerRestrict_Amount_Holder, 0, wxEXPAND | wxTOP, 5);

	TerRestrict_Main->Add(TerRestrict_TerRestrict, 1, wxEXPAND | wxALL, 5);
	TerRestrict_Main->Add(TerRestrict_Terrains, 1, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);
	TerRestrict_Main->Add(TerRestrict_DataArea, 1, wxEXPAND);
	TerRestrict_Main->AddStretchSpacer(1);

	Tab_TerrainRestrictions->SetSizer(TerRestrict_Main);

	Connect(TerRestrict_TerRestrict_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsSearch));
	Connect(TerRestrict_TerRestrict_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsSearch));
	Connect(TerRestrict_TerRestrict_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsSelect));
	Connect(TerRestrict_TerRestrict_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsSelect));
	Connect(TerRestrict_TerRestrict_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsSelect));
	Connect(TerRestrict_Terrains_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	Connect(TerRestrict_Terrains_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	Connect(TerRestrict_Terrains_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainSelect));
	Connect(TerRestrict_Terrains_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainSelect));
	Connect(TerRestrict_Terrains_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainSelect));
	Connect(TerRestrict_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsAdd));
	Connect(TerRestrict_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsInsert));
	Connect(TerRestrict_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsDelete));
	Connect(TerRestrict_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsCopy));
	Connect(TerRestrict_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsPaste));
	Connect(TerRestrict_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsPasteInsert));
	Connect(TerRestrict_Terrains_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainCopy));
	Connect(TerRestrict_Terrains_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainPaste));

    restrictionTimer.Connect(restrictionTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTerrainRestrictionsTimer), NULL, this);
    restrictionTerrainTimer.Connect(restrictionTerrainTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainTimer), NULL, this);
	TerRestrict_Accessible->Connect(TerRestrict_Accessible->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TerRestrict), NULL, this);
	TerRestrict_Unknown1->Connect(TerRestrict_Unknown1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TerRestrict), NULL, this);
	TerRestrict_Accessible_CheckBox->Connect(TerRestrict_Accessible_CheckBox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_TerRestrict), NULL, this);
	TerRestrict_Unknown1_CheckBox->Connect(TerRestrict_Unknown1_CheckBox->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_TerRestrict), NULL, this);
}

void AGE_Frame::OnKillFocus_TerRestrict(wxFocusEvent &event)
{
	if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
	ListTerrains2();
	event.Skip();
}

void AGE_Frame::OnUpdateCheck_TerRestrict(wxCommandEvent &event)
{
	((AGECheckBox*)event.GetEventObject())->OnUpdate(event);
	ListTerrains2();
}
