#include "../AGE_Frame.h"

string AGE_Frame::GetTerrainBorderName(short Index)
{
	if(GenieFile->TerrainBlock.TerrainBorders[Index].Name.empty() && GenieFile->TerrainBlock.TerrainBorders[Index].Name2.empty())
		return "Border "+lexical_cast<string>(Index);
	return GenieFile->TerrainBlock.TerrainBorders[Index].Name+" - "+GenieFile->TerrainBlock.TerrainBorders[Index].Name2;
}

void AGE_Frame::OnTerrainBordersSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTerrainBorders(false);
}

void AGE_Frame::ListTerrainBorders(bool all)
{
	FirstVisible = How2List == SEARCH ? 0 : Borders_List->HitTest(wxPoint(0, 0));
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
		wxString Name = " "+FormatInt(loop)+" - "+GetTerrainBorderName(loop);
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

void AGE_Frame::OnTerrainBordersSelect(wxCommandEvent &event)
{
	auto selections = Borders_List->GetSelections(Items);
	if(selections < 1) return;

	SwapSelection(event.GetSelection(), Items);
	BorderIDs.resize(selections);
	Borders_Enabled->resize(selections);
	Borders_Random->resize(selections);
	Borders_Name[0]->resize(selections);
	Borders_Name[1]->resize(selections);
	if(GenieVersion >= genie::GV_AoEB)
	Borders_SLP->resize(selections);
	Borders_Unknown3->resize(selections);
	Borders_Sound->resize(selections);
	for(short loop = 0; loop < 3; ++loop)
	{
		Borders_Colors[loop]->resize(selections);
	}
	Borders_IsAnimated->resize(selections);
	Borders_AnimationFrames->resize(selections);
	Borders_PauseFames->resize(selections);
	Borders_Interval->resize(selections);
	Borders_PauseBetweenLoops->resize(selections);
	Borders_Frame->resize(selections);
	Borders_DrawFrame->resize(selections);
	Borders_AnimateLast->resize(selections);
	Borders_FrameChanged->resize(selections);
	Borders_Drawn->resize(selections);
	Borders_DrawTile->resize(selections);
	Borders_Terrain->resize(selections);
	Borders_BorderStyle->resize(selections);

	genie::TerrainBorder * BorderPointer;
	for(auto sel = selections; sel--> 0;)
	{
		BorderPointer = (genie::TerrainBorder*)Borders_List->GetClientData(Items.Item(sel));
		BorderIDs[sel] = (BorderPointer - (&GenieFile->TerrainBlock.TerrainBorders[0]));

		Borders_Enabled->prepend(&BorderPointer->Enabled);
		Borders_Random->prepend(&BorderPointer->Random);
		Borders_Name[0]->prepend(&BorderPointer->Name);
		Borders_Name[1]->prepend(&BorderPointer->Name2);
		if(GenieVersion >= genie::GV_AoEB)
		Borders_SLP->prepend(&BorderPointer->SLP);
		Borders_Unknown3->prepend(&BorderPointer->Unknown3);
		Borders_Sound->prepend(&BorderPointer->SoundID);
		for(short loop = 0; loop < 3; ++loop)
		{
			Borders_Colors[loop]->prepend(&BorderPointer->Colors[loop]);
		}
		Borders_IsAnimated->prepend(&BorderPointer->IsAnimated);
		Borders_AnimationFrames->prepend(&BorderPointer->AnimationFrames);
		Borders_PauseFames->prepend(&BorderPointer->PauseFames);
		Borders_Interval->prepend(&BorderPointer->Interval);
		Borders_PauseBetweenLoops->prepend(&BorderPointer->PauseBetweenLoops);
		Borders_Frame->prepend(&BorderPointer->Frame);
		Borders_DrawFrame->prepend(&BorderPointer->DrawFrame);
		Borders_AnimateLast->prepend(&BorderPointer->AnimateLast);
		Borders_FrameChanged->prepend(&BorderPointer->FrameChanged);
		Borders_Drawn->prepend(&BorderPointer->Drawn);
		Borders_DrawTile->prepend(&BorderPointer->DrawTile);
		Borders_Terrain->prepend(&BorderPointer->UnderlayTerrain);
		Borders_BorderStyle->prepend(&BorderPointer->BorderStyle);
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected border: "+lexical_cast<string>(BorderIDs[0]), 0);

	Borders_Enabled->Update();
	Borders_Random->Update();
	Borders_Name[0]->Update();
	Borders_Name[1]->Update();
	if(GenieVersion >= genie::GV_AoEB)
	Borders_SLP->Update();
	Borders_Unknown3->Update();
	Borders_Sound->Update();
	for(short loop = 0; loop < 3; ++loop)
	{
		Borders_Colors[loop]->Update();
	}
	Borders_IsAnimated->Update();
	Borders_AnimationFrames->Update();
	Borders_PauseFames->Update();
	Borders_Interval->Update();
	Borders_PauseBetweenLoops->Update();
	Borders_Frame->Update();
	Borders_DrawFrame->Update();
	Borders_AnimateLast->Update();
	Borders_FrameChanged->Update();
	Borders_Drawn->Update();
	Borders_DrawTile->Update();
	Borders_Terrain->Update();
	Borders_BorderStyle->Update();
	ListTerrainBorderFrames();
}

void AGE_Frame::OnTerrainBordersCopy(wxCommandEvent &event)
{
	auto selections = Borders_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TerrainBlock.TerrainBorders, BorderIDs, copies.TerrainBorder);
	Borders_List->SetFocus();
}

void AGE_Frame::OnTerrainBordersPaste(wxCommandEvent &event)
{
	auto selections = Borders_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(BorderIDs.size(), copies.TerrainBorder.size()))
		{
			PasteToList(GenieFile->TerrainBlock.TerrainBorders, BorderIDs, copies.TerrainBorder);
		}
	}
	else
	{
		PasteToListNoResize(GenieFile->TerrainBlock.TerrainBorders, BorderIDs[0], copies.TerrainBorder);
	}
	ListTerrainBorders();
}

string AGE_Frame::GetTerrainBorderFrameName(short Index)
{
	return "Frame "+lexical_cast<string>(GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames[Index].FrameCount)
	+" - Flags "+lexical_cast<string>(GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames[Index].AngleCount)
	+" "+lexical_cast<string>(GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames[Index].ShapeID)+" ";
}

void AGE_Frame::OnTerrainBorderFramesSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTerrainBorderFrames();
}

void AGE_Frame::ListTerrainBorderFrames()
{
	FirstVisible = How2List == SEARCH ? 0 : Borders_Frames_List->HitTest(wxPoint(0, 0));
	searchText = Borders_Frames_Search->GetValue().Lower();
	excludeText = Borders_Frames_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTerrainBorderFrameName(loop);
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

void AGE_Frame::OnTerrainBorderFramesSelect(wxCommandEvent &event)
{
	auto selections = Borders_Frames_List->GetSelections(Items);
	if(selections < 1) return;

	SwapSelection(event.GetSelection(), Items);
	FrameIDs.resize(selections);
	Borders_FrameID->resize(selections);
	Borders_Flag1->resize(selections);
	Borders_Flag2->resize(selections);

	genie::FrameData * FramePointer;
	for(auto loop = selections; loop--> 0;)
	{
		FramePointer = (genie::FrameData*)Borders_Frames_List->GetClientData(Items.Item(loop));
		FrameIDs[loop] = (FramePointer - (&GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames[0]));

		Borders_FrameID->prepend(&FramePointer->FrameCount);
		Borders_Flag1->prepend(&FramePointer->AngleCount);
		Borders_Flag2->prepend(&FramePointer->ShapeID);
	}

	Borders_FrameID->Update();
	Borders_Flag1->Update();
	Borders_Flag2->Update();
}

void AGE_Frame::OnTerrainBorderFramesCopy(wxCommandEvent &event)
{
	auto selections = Borders_Frames_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames, FrameIDs, copies.FrameData);
	Borders_Frames_List->SetFocus();
}

void AGE_Frame::OnTerrainBorderFramesPaste(wxCommandEvent &event)
{
	auto selections = Borders_Frames_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(FrameIDs.size(), copies.FrameData.size()))
		{
			PasteToList(GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames, FrameIDs, copies.FrameData);
		}
	}
	else
	{
		PasteToListNoResize(GenieFile->TerrainBlock.TerrainBorders[BorderIDs[0]].Frames, FrameIDs[0], copies.FrameData);
	}
	ListTerrainBorderFrames();
}

void AGE_Frame::OnTerrainBorderFramesCopyToBorders(wxCommandEvent &event)
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
	Borders_List = new wxListBox(Tab_TerrainBorders, wxID_ANY, wxDefaultPosition, wxSize(200, 220), 0, NULL, wxLB_EXTENDED);
	Borders_UsedCountHolder = new wxBoxSizer(wxHORIZONTAL);
	Borders_UsedCountText = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Borders Used *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_UsedCount = new TextCtrl_UShort(this, AGEwindow, Tab_TerrainBorders);
	Borders_UsedCount->SetToolTip("How many terrain borders are used\nstarting from the first border without gaps");
	Borders_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Borders_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Borders_DataArea = new wxBoxSizer(wxVERTICAL);
	Borders_DataTopRow = new wxBoxSizer(wxHORIZONTAL);
	Borders_Data1 = new wxGridSizer(4, 5, 5);

	Borders_Enabled_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Enabled1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Borders_Enabled_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Enabled", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Enabled = new TextCtrl_Byte(this, AGEwindow, Tab_TerrainBorders, true);
	Borders_Enabled_CheckBox = new CheckBox_2State(Tab_TerrainBorders, " Yes", Borders_Enabled);
	Borders_Random_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Random_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Random", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Random = new TextCtrl_Byte(this, AGEwindow, Tab_TerrainBorders, true);
	for(short loop = 0; loop < 2; ++loop)
	{
		Borders_Name_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		Borders_Name[loop] = new TextCtrl_String(this, AGEwindow, Tab_TerrainBorders, 13);
	}
	Borders_Name_Text[0] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Name_Text[1] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " SLP Name ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_SLP_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_SLP_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_SLP = new TextCtrl_Long(this, AGEwindow, Tab_TerrainBorders);
	Borders_Data2 = new wxGridSizer(4, 5, 5);
	Borders_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Unknown3_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Unknown3 = new TextCtrl_Long(this, AGEwindow, Tab_TerrainBorders);
	Borders_Sound_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Sound_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Sound = new TextCtrl_Long(this, AGEwindow, Tab_TerrainBorders);
	Borders_Colors_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Colors_Grid = new wxGridSizer(3, 0, 0);
	Borders_Colors_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 3; ++loop)
	Borders_Colors[loop] = new TextCtrl_UByte(this, AGEwindow, Tab_TerrainBorders);
	Borders_DrawTile_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_DrawTile_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Draw Tile", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_DrawTile = new TextCtrl_Short(this, AGEwindow, Tab_TerrainBorders);
	Borders_Terrain_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Terrain_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Underlay Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Terrain = new TextCtrl_Short(this, AGEwindow, Tab_TerrainBorders);
	Borders_Terrain_ComboBox = new ComboBox_Plus1(Tab_TerrainBorders, Borders_Terrain);
	TerrainComboBoxList.push_back(Borders_Terrain_ComboBox);
	Borders_BorderStyle_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_BorderStyle_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Border Style", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderStyle = new TextCtrl_Short(this, AGEwindow, Tab_TerrainBorders);

	Borders_FrameData = new wxBoxSizer(wxHORIZONTAL);
	Borders_Frames_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Tab_TerrainBorders, "Frames");
	Borders_Frames = new wxBoxSizer(wxVERTICAL);
	Borders_Frames_Buttons = new wxGridSizer(2, 0, 0);
	Borders_Frames_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Frames_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Frames_List = new wxListBox(Tab_TerrainBorders, wxID_ANY, wxDefaultPosition, wxSize(200, 220), 0, NULL, wxLB_EXTENDED);
	Frames_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Frames_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Frames_CopyToBorders = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy all to selected borders", wxDefaultPosition, wxSize(5, 20));

	Borders_FrameArea_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_FrameID_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_FrameID_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frames", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_FrameID = new TextCtrl_Short(this, AGEwindow, Tab_TerrainBorders);
	Borders_Flag1_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Flag1_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Animations", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Flag1 = new TextCtrl_Short(this, AGEwindow, Tab_TerrainBorders);
	Borders_Flag2_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Flag2_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Shape index", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Flag2 = new TextCtrl_Short(this, AGEwindow, Tab_TerrainBorders);

	Borders_Animation_Grid = new wxGridSizer(5, 5, 5);
	Borders_IsAnimated_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_IsAnimated_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Is Animated", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_IsAnimated = new TextCtrl_Byte(this, AGEwindow, Tab_TerrainBorders);
	Borders_AnimationFrames_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_AnimationFrames_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Animation Frames *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_AnimationFrames = new TextCtrl_Short(this, AGEwindow, Tab_TerrainBorders);
	Borders_AnimationFrames->SetToolTip("Number of frames to animate through");
	Borders_PauseFames_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_PauseFames_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Pause Fames *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_PauseFames = new TextCtrl_Short(this, AGEwindow, Tab_TerrainBorders);
	Borders_PauseFames->SetToolTip("Number of frames to pause animation after last frame is drawn");
	Borders_Interval_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Interval_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Interval *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Interval = new TextCtrl_Float(this, AGEwindow, Tab_TerrainBorders);
	Borders_Interval->SetToolTip("Time between frames");
	Borders_PauseBetweenLoops_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_PauseBetweenLoops_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Pause Between Loops *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_PauseBetweenLoops = new TextCtrl_Float(this, AGEwindow, Tab_TerrainBorders);
	Borders_PauseBetweenLoops->SetToolTip("Time to pause after last frame");
	Borders_Frame_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Frame_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Frame = new TextCtrl_Short(this, AGEwindow, Tab_TerrainBorders);
	Borders_Frame->SetToolTip("The current frame (includes animation and pause frames)");
	Borders_DrawFrame_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_DrawFrame_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Draw Frame *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_DrawFrame = new TextCtrl_Short(this, AGEwindow, Tab_TerrainBorders);
	Borders_DrawFrame->SetToolTip("The current frame to draw");
	Borders_AnimateLast_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_AnimateLast_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Animate Last *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_AnimateLast = new TextCtrl_Float(this, AGEwindow, Tab_TerrainBorders);
	Borders_AnimateLast->SetToolTip("Last time animation frame was changed");
	Borders_FrameChanged_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_FrameChanged_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame Changed *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_FrameChanged = new TextCtrl_Byte(this, AGEwindow, Tab_TerrainBorders);
	Borders_FrameChanged->SetToolTip("Has the Draw Frame changed since terrain was drawn?");
	Borders_Drawn_Holder = new wxBoxSizer(wxVERTICAL);
	Borders_Drawn_Text = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Drawn", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Drawn = new TextCtrl_Byte(this, AGEwindow, Tab_TerrainBorders);

	for(short loop = 0; loop < 2; ++loop)
	{
		Borders_Name_Holder[loop]->Add(Borders_Name_Text[loop], 0, wxEXPAND);
		Borders_Name_Holder[loop]->Add(Borders_Name[loop], 0, wxEXPAND);
	}
	Borders_Enabled1_Holder->Add(Borders_Enabled, 1, wxEXPAND);
	Borders_Enabled1_Holder->AddSpacer(2);
	Borders_Enabled1_Holder->Add(Borders_Enabled_CheckBox, 1, wxEXPAND);
	Borders_Enabled_Holder->Add(Borders_Enabled_Text, 0, wxEXPAND);
	Borders_Enabled_Holder->Add(Borders_Enabled1_Holder, 1, wxEXPAND);
	Borders_Random_Holder->Add(Borders_Random_Text, 0, wxEXPAND);
	Borders_Random_Holder->Add(Borders_Random, 0, wxEXPAND);

	Borders_UsedCountHolder->Add(Borders_UsedCountText, 0, wxEXPAND);
	Borders_UsedCountHolder->AddSpacer(2);
	Borders_UsedCountHolder->Add(Borders_UsedCount, 1, wxEXPAND);

	Borders_Buttons->Add(Borders_Copy, 1, wxEXPAND);
	Borders_Buttons->Add(Borders_Paste, 1, wxEXPAND);

	Borders_Borders->Add(Borders_Search, 0, wxEXPAND);
	Borders_Borders->Add(Borders_Search_R, 0, wxEXPAND);
	Borders_Borders->AddSpacer(2);
	Borders_Borders->Add(Borders_List, 1, wxEXPAND);
	Borders_Borders->AddSpacer(2);
	Borders_Borders->Add(Borders_UsedCountHolder, 0, wxEXPAND);
	Borders_Borders->AddSpacer(2);
	Borders_Borders->Add(Borders_Buttons, 0, wxEXPAND);

	Borders_ListArea->AddSpacer(5);
	Borders_ListArea->Add(Borders_Borders, 1, wxEXPAND);
	Borders_ListArea->AddSpacer(5);

	Borders_DataTopRow->Add(Borders_Enabled_Holder, 3, wxEXPAND);
	Borders_DataTopRow->AddSpacer(5);
	Borders_DataTopRow->Add(Borders_Random_Holder, 2, wxEXPAND);
	Borders_DataTopRow->AddSpacer(5);
	Borders_DataTopRow->Add(Borders_Name_Holder[0], 8, wxEXPAND);
	Borders_DataTopRow->AddSpacer(5);
	Borders_DataTopRow->Add(Borders_Name_Holder[1], 8, wxEXPAND);

	Borders_SLP_Holder->Add(Borders_SLP_Text, 0, wxEXPAND);
	Borders_SLP_Holder->Add(Borders_SLP, 0, wxEXPAND);
	Borders_Unknown3_Holder->Add(Borders_Unknown3_Text, 0, wxEXPAND);
	Borders_Unknown3_Holder->Add(Borders_Unknown3, 0, wxEXPAND);
	Borders_Sound_Holder->Add(Borders_Sound_Text, 0, wxEXPAND);
	Borders_Sound_Holder->Add(Borders_Sound, 0, wxEXPAND);
	for(short loop = 0; loop < 3; ++loop)
	Borders_Colors_Grid->Add(Borders_Colors[loop], 1, wxEXPAND);
	Borders_Colors_Holder->Add(Borders_Colors_Text, 0, wxEXPAND);
	Borders_Colors_Holder->Add(Borders_Colors_Grid, 0, wxEXPAND);
	Borders_DrawTile_Holder->Add(Borders_DrawTile_Text, 0, wxEXPAND);
	Borders_DrawTile_Holder->Add(Borders_DrawTile, 0, wxEXPAND);
	Borders_Terrain_Holder->Add(Borders_Terrain_Text, 0, wxEXPAND);
	Borders_Terrain_Holder->Add(Borders_Terrain, 0, wxEXPAND);
	Borders_Terrain_Holder->Add(Borders_Terrain_ComboBox, 0, wxEXPAND);
	Borders_BorderStyle_Holder->Add(Borders_BorderStyle_Text, 0, wxEXPAND);
	Borders_BorderStyle_Holder->Add(Borders_BorderStyle, 0, wxEXPAND);

	Borders_Data1->Add(Borders_SLP_Holder, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Unknown3_Holder, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Sound_Holder, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Colors_Holder, 1, wxEXPAND);

	Borders_IsAnimated_Holder->Add(Borders_IsAnimated_Text, 0, wxEXPAND);
	Borders_AnimationFrames_Holder->Add(Borders_AnimationFrames_Text, 0, wxEXPAND);
	Borders_PauseFames_Holder->Add(Borders_PauseFames_Text, 0, wxEXPAND);
	Borders_Interval_Holder->Add(Borders_Interval_Text, 0, wxEXPAND);
	Borders_PauseBetweenLoops_Holder->Add(Borders_PauseBetweenLoops_Text, 0, wxEXPAND);
	Borders_Frame_Holder->Add(Borders_Frame_Text, 0, wxEXPAND);
	Borders_DrawFrame_Holder->Add(Borders_DrawFrame_Text, 0, wxEXPAND);
	Borders_AnimateLast_Holder->Add(Borders_AnimateLast_Text, 0, wxEXPAND);
	Borders_FrameChanged_Holder->Add(Borders_FrameChanged_Text, 0, wxEXPAND);
	Borders_Drawn_Holder->Add(Borders_Drawn_Text, 0, wxEXPAND);
	Borders_IsAnimated_Holder->Add(Borders_IsAnimated, 1, wxEXPAND);
	Borders_AnimationFrames_Holder->Add(Borders_AnimationFrames, 1, wxEXPAND);
	Borders_PauseFames_Holder->Add(Borders_PauseFames, 1, wxEXPAND);
	Borders_Interval_Holder->Add(Borders_Interval, 1, wxEXPAND);
	Borders_PauseBetweenLoops_Holder->Add(Borders_PauseBetweenLoops, 1, wxEXPAND);
	Borders_Frame_Holder->Add(Borders_Frame, 1, wxEXPAND);
	Borders_DrawFrame_Holder->Add(Borders_DrawFrame, 1, wxEXPAND);
	Borders_AnimateLast_Holder->Add(Borders_AnimateLast, 1, wxEXPAND);
	Borders_FrameChanged_Holder->Add(Borders_FrameChanged, 1, wxEXPAND);
	Borders_Drawn_Holder->Add(Borders_Drawn, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_IsAnimated_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_AnimationFrames_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_PauseFames_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_Interval_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_PauseBetweenLoops_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_Frame_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_DrawFrame_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_AnimateLast_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_FrameChanged_Holder, 1, wxEXPAND);
	Borders_Animation_Grid->Add(Borders_Drawn_Holder, 1, wxEXPAND);

	Borders_Frames_Buttons->Add(Frames_Copy, 1, wxEXPAND);
	Borders_Frames_Buttons->Add(Frames_Paste, 1, wxEXPAND);

	Borders_Frames->Add(Borders_Frames_Search, 0, wxEXPAND);
	Borders_Frames->Add(Borders_Frames_Search_R, 0, wxEXPAND);
	Borders_Frames->AddSpacer(2);
	Borders_Frames->Add(Borders_Frames_List, 1, wxEXPAND);
	Borders_Frames->AddSpacer(2);
	Borders_Frames->Add(Borders_Frames_Buttons, 0, wxEXPAND);
	Borders_Frames->AddSpacer(2);
	Borders_Frames->Add(Frames_CopyToBorders, 0, wxEXPAND);

	Borders_FrameID_Holder->Add(Borders_FrameID_Text, 0, wxEXPAND);
	Borders_FrameID_Holder->Add(Borders_FrameID, 1, wxEXPAND);
	Borders_Flag1_Holder->Add(Borders_Flag1_Text, 0, wxEXPAND);
	Borders_Flag1_Holder->Add(Borders_Flag1, 1, wxEXPAND);
	Borders_Flag2_Holder->Add(Borders_Flag2_Text, 0, wxEXPAND);
	Borders_Flag2_Holder->Add(Borders_Flag2, 1, wxEXPAND);

	Borders_FrameArea_Holder->Add(Borders_FrameID_Holder, 0, wxEXPAND);
	Borders_FrameArea_Holder->AddSpacer(5);
	Borders_FrameArea_Holder->Add(Borders_Flag1_Holder, 0, wxEXPAND);
	Borders_FrameArea_Holder->AddSpacer(5);
	Borders_FrameArea_Holder->Add(Borders_Flag2_Holder, 0, wxEXPAND);

	Borders_Frames_Holder->Add(Borders_Frames, 3, wxEXPAND);
	Borders_Frames_Holder->AddSpacer(5);
	Borders_Frames_Holder->Add(Borders_FrameArea_Holder, 2, wxEXPAND);
	Borders_FrameData->Add(Borders_Frames_Holder, 5, wxEXPAND);
	Borders_FrameData->AddStretchSpacer(3);

	Borders_Data2->Add(Borders_DrawTile_Holder, 1, wxEXPAND);
	Borders_Data2->Add(Borders_Terrain_Holder, 1, wxEXPAND);
	Borders_Data2->Add(Borders_BorderStyle_Holder, 1, wxEXPAND);

	Borders_DataArea->AddSpacer(5);
	Borders_DataArea->Add(Borders_DataTopRow, 0, wxEXPAND);
	Borders_DataArea->AddSpacer(5);
	Borders_DataArea->Add(Borders_Data1, 0, wxEXPAND);
	Borders_DataArea->AddSpacer(5);
	Borders_DataArea->Add(Borders_Data2, 0, wxEXPAND);
	Borders_DataArea->AddSpacer(5);
	Borders_DataArea->Add(Borders_FrameData, 0, wxEXPAND);
	Borders_DataArea->AddSpacer(5);
	Borders_DataArea->Add(Borders_Animation_Grid, 0, wxEXPAND);
	Borders_DataArea->AddSpacer(5);

	Borders_Main->AddSpacer(5);
	Borders_Main->Add(Borders_ListArea, 21, wxEXPAND);
	Borders_Main->AddSpacer(5);
	Borders_Main->Add(Borders_DataArea, 65, wxEXPAND);
	Borders_Main->AddSpacer(5);

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

void AGE_Frame::OnKillFocus_Borders(wxFocusEvent &event)
{
	event.Skip();
	if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
	if(event.GetId() == Borders_Name[0]->GetId() || event.GetId() == Borders_Name[1]->GetId())
	{
		ListTerrainBorders();
	}
	else if(event.GetId() == Borders_FrameID->GetId() || event.GetId() == Borders_Flag1->GetId() || event.GetId() == Borders_Flag2->GetId())
	{
		ListTerrainBorderFrames();
	}
}
