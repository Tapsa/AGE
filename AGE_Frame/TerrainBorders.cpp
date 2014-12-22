#include "../AGE_Frame.h"

string AGE_Frame::GetTerrainBorderName(short Index)
{
	if(GenieFile->TerrainBlock.TerrainBorders[Index].Name.empty() && GenieFile->TerrainBlock.TerrainBorders[Index].Name2.empty())
		return "Border "+lexical_cast<string>(Index);
	return GenieFile->TerrainBlock.TerrainBorders[Index].Name+" - "+GenieFile->TerrainBlock.TerrainBorders[Index].Name2;
}

void AGE_Frame::OnTerrainBordersSearch(wxCommandEvent &Event)
{
	ListTerrainBorders(false);
}

void AGE_Frame::ListTerrainBorders(bool all)
{
	InitTerrainBorders(all);
	wxCommandEvent E;
	OnTerrainBordersSelect(E);
}

void AGE_Frame::InitTerrainBorders(bool all)
{
	searchText = Borders_Search->GetValue().Lower();
	excludeText = Borders_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString names, filteredNames;
	if(all) names.Alloc(GenieFile->TerrainBlock.TerrainBorders.size());

	for(short loop = 0; loop < GenieFile->TerrainBlock.TerrainBorders.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetTerrainBorderName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TerrainBlock.TerrainBorders[loop]);
		}
		if(all) names.Add(Name);
	}

	Listing(Borders_List, filteredNames, dataPointers);
	if(all) FillLists(TerrainBorderComboBoxList, names);
}

void AGE_Frame::OnTerrainBordersSelect(wxCommandEvent &Event)
{
	auto selections = Borders_List->GetSelections(Items);
	if(selections < 1) return;

	BorderIDs.resize(selections);
	Borders_Unknown1->resize(selections);
	Borders_Enabled->resize(selections);
	Borders_Name[0]->resize(selections);
	Borders_Name[1]->resize(selections);
	Borders_RessourceID->resize(selections);
	Borders_Unknown3->resize(selections);
	Borders_Unknown4->resize(selections);
	for(short loop = 0; loop < 3; ++loop)
	{
		Borders_Colors[loop]->resize(selections);
	}
	for(short loop = 0; loop < Borders_Unknown5.size(); ++loop)
	Borders_Unknown5[loop]->resize(selections);
	Borders_Unknown6->resize(selections);
	Borders_FrameCount->resize(selections);
	Borders_Unknown8->resize(selections);
	Borders_Terrain->resize(selections);

	genie::TerrainBorder * BorderPointer;
	for(auto sel = selections; sel--> 0;)
	{
		BorderPointer = (genie::TerrainBorder*)Borders_List->GetClientData(Items.Item(sel));
		BorderIDs[sel] = (BorderPointer - (&GenieFile->TerrainBlock.TerrainBorders[0]));

		Borders_Unknown1->container[sel] = &BorderPointer->Unknown1;
		Borders_Enabled->container[sel] = &BorderPointer->Enabled;
		Borders_Name[0]->container[sel] = &BorderPointer->Name;
		Borders_Name[1]->container[sel] = &BorderPointer->Name2;
		Borders_RessourceID->container[sel] = &BorderPointer->SLP;
		Borders_Unknown3->container[sel] = &BorderPointer->Unknown3;
		Borders_Unknown4->container[sel] = &BorderPointer->SoundID;
		for(short loop = 0; loop < 3; ++loop)
		{
			Borders_Colors[loop]->container[sel] = &BorderPointer->Colors[loop];
		}
		for(short loop = 0; loop < Borders_Unknown5.size(); ++loop)
		Borders_Unknown5[loop]->container[sel] = &BorderPointer->Unknown5[loop];
		Borders_Unknown6->container[sel] = &BorderPointer->Unknown6;
		Borders_FrameCount->container[sel] = &BorderPointer->FrameCount;
		Borders_Unknown8->container[sel] = &BorderPointer->AngleCount;
		Borders_Terrain->container[sel] = &BorderPointer->TerrainID;
	}

	Borders_Unknown1->Update();
	Borders_Enabled->Update();
	Borders_Name[0]->Update();
	Borders_Name[1]->Update();
	Borders_RessourceID->Update();
	Borders_Unknown3->Update();
	Borders_Unknown4->Update();
	for(short loop = 0; loop < 3; ++loop)
	{
		Borders_Colors[loop]->Update();
	}
	for(short loop = 0; loop < Borders_Unknown5.size(); ++loop)
	Borders_Unknown5[loop]->Update();
	Borders_Unknown6->Update();
	Borders_FrameCount->Update();
	Borders_Unknown8->Update();
	Borders_Terrain->Update();
	ListTerrainBorderFrames();
}

void AGE_Frame::OnTerrainBordersCopy(wxCommandEvent &Event)
{
	auto selections = Borders_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TerrainBlock.TerrainBorders, BorderIDs, copies->TerrainBorder);
}

void AGE_Frame::OnTerrainBordersPaste(wxCommandEvent &Event)
{
	auto selections = Borders_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoResize(GenieFile->TerrainBlock.TerrainBorders, BorderIDs[0], copies->TerrainBorder);
	ListTerrainBorders();
}

string AGE_Frame::GetTerrainBorderFrameName(short Index)
{
	return "Frame "+lexical_cast<string>(GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames[Index].FrameID)
	+" - Flags "+lexical_cast<string>(GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames[Index].Flag1)
	+" "+lexical_cast<string>(GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames[Index].Flag2)+" ";
}

void AGE_Frame::OnTerrainBorderFramesSearch(wxCommandEvent &Event)
{
	ListTerrainBorderFrames();
}

void AGE_Frame::ListTerrainBorderFrames()
{
	searchText = Borders_Frames_Search->GetValue().Lower();
	excludeText = Borders_Frames_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetTerrainBorderFrameName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames[loop]);
		}
	}

	Listing(Borders_Frames_List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTerrainBorderFramesSelect(E);
}

void AGE_Frame::OnTerrainBorderFramesSelect(wxCommandEvent &Event)
{
	auto selections = Borders_Frames_List->GetSelections(Items);
	if(selections < 1) return;

	FrameIDs.resize(selections);
	Borders_FrameID->resize(selections);
	Borders_Flag1->resize(selections);
	Borders_Flag2->resize(selections);

	genie::TBFrameData * FramePointer;
	for(auto loop = selections; loop--> 0;)
	{
		FramePointer = (genie::TBFrameData*)Borders_Frames_List->GetClientData(Items.Item(loop));
		FrameIDs[loop] = (FramePointer - (&GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames[0]));

		Borders_FrameID->container[loop] = &FramePointer->FrameID;
		Borders_Flag1->container[loop] = &FramePointer->Flag1;
		Borders_Flag2->container[loop] = &FramePointer->Flag2;
	}

	Borders_FrameID->Update();
	Borders_Flag1->Update();
	Borders_Flag2->Update();
}

void AGE_Frame::OnTerrainBorderFramesCopy(wxCommandEvent &Event)
{
	auto selections = Borders_Frames_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames, FrameIDs, copies->TBFrameData);
}

void AGE_Frame::OnTerrainBorderFramesPaste(wxCommandEvent &Event)
{
	auto selections = Borders_Frames_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoResize(GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames, FrameIDs[0], copies->TBFrameData);
	ListTerrainBorderFrames();
}

void AGE_Frame::OnTerrainBorderFramesCopyToBorders(wxCommandEvent &Event)
{
	for(short loop=1; loop < BorderIDs.size(); ++loop)
	{
		GenieFile->TerrainBlock.TerrainBorders[BorderIDs[loop]].Frames = GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames;
	}
}

void AGE_Frame::CreateTerrainBorderControls()
{
	Tab_TerrainBorders = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Borders_Main = new wxBoxSizer(wxHORIZONTAL);
	Borders_ListArea = new wxBoxSizer(wxVERTICAL);
	Borders_Buttons = new wxGridSizer(2, 0, 0);
	Borders_Borders = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Terrain Borders");
	Borders_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_List = new wxListBox(Tab_TerrainBorders, wxID_ANY, wxDefaultPosition, wxSize(10, 220), 0, NULL, wxLB_EXTENDED);
	Borders_UsedCountHolder = new wxBoxSizer(wxHORIZONTAL);
	Borders_UsedCountText = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Borders Used *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_UsedCount = new TextCtrl_UShort(Tab_TerrainBorders);
	Borders_UsedCount->SetToolTip("How many terrain borders are used\nstarting from the first border without gaps");
	Borders_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Borders_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Borders_DataArea = new wxBoxSizer(wxVERTICAL);
	Borders_DataTopRow = new wxBoxSizer(wxHORIZONTAL);
	Borders_Data1 = new wxGridSizer(4, 5, 5);

	Borders_Enabled_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Enabled1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Borders_Enabled_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Enabled", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Enabled = new TextCtrl_Short(Tab_TerrainBorders);
	Borders_Enabled_CheckBox = new CheckBox_2State(Tab_TerrainBorders, " Yes", Borders_Enabled);
	for(short loop = 0; loop < 2; ++loop)
	{
		Borders_Name_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		Borders_Name[loop] = new TextCtrl_String(Tab_TerrainBorders, 13);
	}
	Borders_Name_Text[0] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Name_Text[1] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " SLP Name ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_RessourceID_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_RessourceID_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_RessourceID = new TextCtrl_Long(Tab_TerrainBorders);
	Borders_Colors_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Colors_Grid = new wxGridSizer(3, 0, 0);
	Borders_Colors_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 3; ++loop)
	Borders_Colors[loop] = new TextCtrl_UByte(Tab_TerrainBorders);
	Borders_FrameCount_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_FrameCount_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_FrameCount = new TextCtrl_Short(Tab_TerrainBorders);
	Borders_Terrain_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Terrain_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Terrain = new TextCtrl_Short(Tab_TerrainBorders);
	Borders_Terrain_ComboBox = new ComboBox_Plus1(Tab_TerrainBorders, Borders_Terrain);
	TerrainComboBoxList.push_back(Borders_Terrain_ComboBox);

	Borders_FrameData = new wxBoxSizer(wxHORIZONTAL);
	Borders_Frames_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Tab_TerrainBorders, "Frames");
	Borders_Frames = new wxBoxSizer(wxVERTICAL);
	Borders_Frames_Buttons = new wxGridSizer(2, 0, 0);
	Borders_Frames_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Frames_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Frames_List = new wxListBox(Tab_TerrainBorders, wxID_ANY, wxDefaultPosition, wxSize(10, 220), 0, NULL, wxLB_EXTENDED);
	Frames_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Frames_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Frames_CopyToBorders = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy all to selected borders", wxDefaultPosition, wxSize(5, 20));

	Borders_FrameArea_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_FrameID_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_FrameID_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_FrameID = new TextCtrl_Short(Tab_TerrainBorders);
	Borders_Flag1_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Flag1_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Flag 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Flag1 = new TextCtrl_Short(Tab_TerrainBorders);
	Borders_Flag2_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Flag2_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Flag 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Flag2 = new TextCtrl_Short(Tab_TerrainBorders);

	Borders_Unknonws = new wxGridSizer(5, 5, 5);
	Borders_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Unknown1_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Unknown1 = new TextCtrl_Short(Tab_TerrainBorders);
	Borders_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Unknown3_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Unknown3 = new TextCtrl_Float(Tab_TerrainBorders);
	Borders_Unknown4_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Unknown4_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Unknown4 = new TextCtrl_Long(Tab_TerrainBorders);
	Borders_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Unknown5_Grid = new wxGridSizer(5, 0, 0);
	Borders_Unknown5_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < Borders_Unknown5.size(); ++loop)
	Borders_Unknown5[loop] = new TextCtrl_Byte(Tab_TerrainBorders);
	Borders_Unknown6_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Unknown6_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Unknown6 = new TextCtrl_Float(Tab_TerrainBorders);
	Borders_Unknown8_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Unknown8_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Angle Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Unknown8 = new TextCtrl_Short(Tab_TerrainBorders);

	for(short loop = 0; loop < 2; ++loop)
	{
		Borders_Name_Holder[loop]->Add(Borders_Name_Text[loop], 0, wxEXPAND);
		Borders_Name_Holder[loop]->Add(Borders_Name[loop], 0, wxEXPAND);
	}
	Borders_Enabled1_Holder->Add(Borders_Enabled, 1, wxEXPAND);
	Borders_Enabled1_Holder->Add(2, -1);
	Borders_Enabled1_Holder->Add(Borders_Enabled_CheckBox, 1, wxEXPAND);
	Borders_Enabled_Holder->Add(Borders_Enabled_Text, 0, wxEXPAND);
	Borders_Enabled_Holder->Add(Borders_Enabled1_Holder, 1, wxEXPAND);

	Borders_UsedCountHolder->Add(Borders_UsedCountText, 0, wxEXPAND);
	Borders_UsedCountHolder->Add(2, -1);
	Borders_UsedCountHolder->Add(Borders_UsedCount, 1, wxEXPAND);

	Borders_Buttons->Add(Borders_Copy, 1, wxEXPAND);
	Borders_Buttons->Add(Borders_Paste, 1, wxEXPAND);

	Borders_Borders->Add(Borders_Search, 0, wxEXPAND);
	Borders_Borders->Add(Borders_Search_R, 0, wxEXPAND);
	Borders_Borders->Add(-1, 2);
	Borders_Borders->Add(Borders_List, 1, wxEXPAND);
	Borders_Borders->Add(-1, 2);
	Borders_Borders->Add(Borders_UsedCountHolder, 0, wxEXPAND);
	Borders_Borders->Add(-1, 2);
	Borders_Borders->Add(Borders_Buttons, 0, wxEXPAND);

	Borders_ListArea->Add(-1, 10);
	Borders_ListArea->Add(Borders_Borders, 1, wxEXPAND);
	Borders_ListArea->Add(-1, 10);

	Borders_DataTopRow->Add(Borders_Enabled_Holder, 1, wxEXPAND);
	Borders_DataTopRow->Add(5, -1);
	Borders_DataTopRow->Add(Borders_Name_Holder[0], 2, wxEXPAND);
	Borders_DataTopRow->Add(5, -1);
	Borders_DataTopRow->Add(Borders_Name_Holder[1], 2, wxEXPAND);
	Borders_DataTopRow->AddStretchSpacer(1);

	Borders_RessourceID_Holder->Add(Borders_RessourceID_Text, 0, wxEXPAND);
	Borders_RessourceID_Holder->Add(Borders_RessourceID, 0, wxEXPAND);
	Borders_Unknown3_Holder->Add(Borders_Unknown3_Text, 0, wxEXPAND);
	Borders_Unknown3_Holder->Add(Borders_Unknown3, 1, wxEXPAND);
	Borders_Unknown4_Holder->Add(Borders_Unknown4_Text, 0, wxEXPAND);
	Borders_Unknown4_Holder->Add(Borders_Unknown4, 1, wxEXPAND);
	for(short loop = 0; loop < 3; ++loop)
	Borders_Colors_Grid->Add(Borders_Colors[loop], 1, wxEXPAND);
	Borders_Colors_Holder->Add(Borders_Colors_Text, 0, wxEXPAND);
	Borders_Colors_Holder->Add(Borders_Colors_Grid, 0, wxEXPAND);
	Borders_Unknown5_Holder->Add(Borders_Unknown5_Text, 0, wxEXPAND);
	for(short loop = 0; loop < Borders_Unknown5.size(); ++loop)
	Borders_Unknown5_Grid->Add(Borders_Unknown5[loop], 1, wxEXPAND);
	Borders_Unknown5_Holder->Add(Borders_Unknown5_Grid, 0, wxEXPAND);
	Borders_Unknown6_Holder->Add(Borders_Unknown6_Text, 0, wxEXPAND);
	Borders_Unknown6_Holder->Add(Borders_Unknown6, 1, wxEXPAND);
	Borders_FrameCount_Holder->Add(Borders_FrameCount_Text, 0, wxEXPAND);
	Borders_FrameCount_Holder->Add(Borders_FrameCount, 0, wxEXPAND);
	Borders_Unknown8_Holder->Add(Borders_Unknown8_Text, 0, wxEXPAND);
	Borders_Unknown8_Holder->Add(Borders_Unknown8, 1, wxEXPAND);
	Borders_Terrain_Holder->Add(Borders_Terrain_Text, 0, wxEXPAND);
	Borders_Terrain_Holder->Add(Borders_Terrain, 1, wxEXPAND);
	Borders_Terrain_Holder->Add(Borders_Terrain_ComboBox, 1, wxEXPAND);
	Borders_Unknown1_Holder->Add(Borders_Unknown1_Text, 0, wxEXPAND);
	Borders_Unknown1_Holder->Add(Borders_Unknown1, 1, wxEXPAND);

	Borders_Data1->Add(Borders_RessourceID_Holder, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Colors_Holder, 1, wxEXPAND);
	Borders_Data1->Add(Borders_FrameCount_Holder, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Terrain_Holder, 1, wxEXPAND);

	Borders_Frames_Buttons->Add(Frames_Copy, 1, wxEXPAND);
	Borders_Frames_Buttons->Add(Frames_Paste, 1, wxEXPAND);

	Borders_Frames->Add(Borders_Frames_Search, 0, wxEXPAND);
	Borders_Frames->Add(Borders_Frames_Search_R, 0, wxEXPAND);
	Borders_Frames->Add(-1, 2);
	Borders_Frames->Add(Borders_Frames_List, 1, wxEXPAND);
	Borders_Frames->Add(-1, 2);
	Borders_Frames->Add(Borders_Frames_Buttons, 0, wxEXPAND);
	Borders_Frames->Add(-1, 2);
	Borders_Frames->Add(Frames_CopyToBorders, 0, wxEXPAND);

	Borders_FrameID_Holder->Add(Borders_FrameID_Text, 0, wxEXPAND);
	Borders_FrameID_Holder->Add(Borders_FrameID, 1, wxEXPAND);
	Borders_Flag1_Holder->Add(Borders_Flag1_Text, 0, wxEXPAND);
	Borders_Flag1_Holder->Add(Borders_Flag1, 1, wxEXPAND);
	Borders_Flag2_Holder->Add(Borders_Flag2_Text, 0, wxEXPAND);
	Borders_Flag2_Holder->Add(Borders_Flag2, 1, wxEXPAND);

	Borders_FrameArea_Holder->Add(Borders_FrameID_Holder, 0, wxEXPAND);
	Borders_FrameArea_Holder->Add(-1, 5);
	Borders_FrameArea_Holder->Add(Borders_Flag1_Holder, 0, wxEXPAND);
	Borders_FrameArea_Holder->Add(-1, 5);
	Borders_FrameArea_Holder->Add(Borders_Flag2_Holder, 0, wxEXPAND);

	Borders_Frames_Holder->Add(Borders_Frames, 3, wxEXPAND);
	Borders_Frames_Holder->Add(5, -1);
	Borders_Frames_Holder->Add(Borders_FrameArea_Holder, 2, wxEXPAND);
	Borders_FrameData->Add(Borders_Frames_Holder, 5, wxEXPAND);
	Borders_FrameData->AddStretchSpacer(3);

	Borders_Unknonws->Add(Borders_Unknown1_Holder, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Unknown3_Holder, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Unknown4_Holder, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Unknown6_Holder, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Unknown8_Holder, 1, wxEXPAND);

	Borders_DataArea->Add(-1, 10);
	Borders_DataArea->Add(Borders_DataTopRow, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 5);
	Borders_DataArea->Add(Borders_Data1, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 5);
	Borders_DataArea->Add(Borders_FrameData, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 5);
	Borders_DataArea->Add(Borders_Unknonws, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 5);
	Borders_DataArea->Add(Borders_Unknown5_Holder, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 10);

	Borders_Main->Add(10, -1);
	Borders_Main->Add(Borders_ListArea, 1, wxEXPAND);
	Borders_Main->Add(10, -1);
	Borders_Main->Add(Borders_DataArea, 3, wxEXPAND);
	Borders_Main->Add(10, -1);

	Tab_TerrainBorders->SetSizer(Borders_Main);

	Connect(Borders_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSearch));
	Connect(Borders_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSearch));
	Connect(Borders_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSelect));
	Connect(Borders_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersCopy));
	Connect(Borders_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersPaste));
	Connect(Borders_Frames_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesSearch));
	Connect(Borders_Frames_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesSearch));
	Connect(Borders_Frames_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesSelect));
	Connect(Frames_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesCopy));
	Connect(Frames_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesPaste));
	Connect(Frames_CopyToBorders->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesCopyToBorders));

	for(short loop = 0; loop < 2; ++loop)
	Borders_Name[loop]->Connect(Borders_Name[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Borders), NULL, this);
	Borders_FrameID->Connect(Borders_FrameID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Borders), NULL, this);
	Borders_Flag1->Connect(Borders_Flag1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Borders), NULL, this);
	Borders_Flag2->Connect(Borders_Flag2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Borders), NULL, this);
}

void AGE_Frame::OnKillFocus_Borders(wxFocusEvent &Event)
{
	if(((AGETextCtrl*)Event.GetEventObject())->SaveEdits() != 0) return;
	if(Event.GetId() == Borders_Name[0]->GetId() || Event.GetId() == Borders_Name[1]->GetId())
	{
		ListTerrainBorders();
	}
	else if(Event.GetId() == Borders_FrameID->GetId() || Event.GetId() == Borders_Flag1->GetId() || Event.GetId() == Borders_Flag2->GetId())
	{
		ListTerrainBorderFrames();
	}
	Event.Skip();
}
