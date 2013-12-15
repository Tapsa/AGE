#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetTerrainBorderName(short Index)
{
	if(GenieFile->TerrainBorders[Index].Name.empty() && GenieFile->TerrainBorders[Index].Name2.empty())
		return "Border "+lexical_cast<string>(Index);
	return GenieFile->TerrainBorders[Index].Name+" - "+GenieFile->TerrainBorders[Index].Name2;
}

void AGE_Frame::OnTerrainBordersSearch(wxCommandEvent &Event)
{
	ListTerrainBorders(false);
}

void AGE_Frame::ListTerrainBorders(bool all)
{
	searchText = Borders_Borders_Search->GetValue().Lower();
	excludeText = Borders_Borders_Search_R->GetValue().Lower();

	auto selections = Borders_Borders_List->GetSelections(Items);
	Borders_Borders_List->Clear();

	list<short> savedSelections;
	wxArrayString names;
	if(all)
	{
		PrepareLists(TerrainBorderComboBoxList, savedSelections);
		names.Alloc(GenieFile->TerrainBorders.size());
	}

	for(short loop = 0; loop < GenieFile->TerrainBorders.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetTerrainBorderName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Borders_Borders_List->Append(Name, (void*)&GenieFile->TerrainBorders[loop]);
		}
		if(all) names.Add(Name);
	}

	ListingFix(selections, Borders_Borders_List);
	if(all) FillLists(TerrainBorderComboBoxList, savedSelections, names);

	wxCommandEvent E;
	OnTerrainBordersSelect(E);
}

void AGE_Frame::OnTerrainBordersSelect(wxCommandEvent &Event)
{
	auto selections = Borders_Borders_List->GetSelections(Items);
	if(selections < 1) return;

	BorderIDs.resize(selections);
	Borders_BorderUnknown1->resize(selections);
	Borders_BorderEnabled->resize(selections);
	Borders_BorderName[0]->resize(selections);
	Borders_BorderName[1]->resize(selections);
	Borders_BorderRessourceID->resize(selections);
	Borders_BorderUnknown3->resize(selections);
	Borders_BorderUnknown4->resize(selections);
	for(short loop = 0; loop < 3; ++loop)
	{
		Borders_BorderColors[loop]->resize(selections);
	}
	for(short loop = 0; loop < Borders_BorderUnknown5.size(); ++loop)
	Borders_BorderUnknown5[loop]->resize(selections);
	Borders_BorderUnknown6->resize(selections);
	Borders_BorderFrameCount->resize(selections);
	Borders_BorderUnknown8->resize(selections);
	Borders_BorderTerrain->resize(selections);

	genie::TerrainBorder * BorderPointer;
	for(auto sel = selections; sel--> 0;)
	{
		BorderPointer = (genie::TerrainBorder*)Borders_Borders_List->GetClientData(Items.Item(sel));
		BorderIDs[sel] = (BorderPointer - (&GenieFile->TerrainBorders[0]));

		Borders_BorderUnknown1->container[sel] = &BorderPointer->Unknown1;
		Borders_BorderEnabled->container[sel] = &BorderPointer->Enabled;
		Borders_BorderName[0]->container[sel] = &BorderPointer->Name;
		Borders_BorderName[1]->container[sel] = &BorderPointer->Name2;
		Borders_BorderRessourceID->container[sel] = &BorderPointer->SLP;
		Borders_BorderUnknown3->container[sel] = &BorderPointer->Unknown3;
		Borders_BorderUnknown4->container[sel] = &BorderPointer->SoundID;
		for(short loop = 0; loop < 3; ++loop)
		{
			Borders_BorderColors[loop]->container[sel] = &BorderPointer->Colors[loop];
		}
		for(short loop = 0; loop < Borders_BorderUnknown5.size(); ++loop)
		Borders_BorderUnknown5[loop]->container[sel] = &BorderPointer->Unknown5[loop];
		Borders_BorderUnknown6->container[sel] = &BorderPointer->Unknown6;
		Borders_BorderFrameCount->container[sel] = &BorderPointer->FrameCount;
		Borders_BorderUnknown8->container[sel] = &BorderPointer->AngleCount;
		Borders_BorderTerrain->container[sel] = &BorderPointer->TerrainID;
	}

	Borders_BorderUnknown1->ChangeValue(lexical_cast<string>(BorderPointer->Unknown1));
	Borders_BorderEnabled->ChangeValue(lexical_cast<string>(BorderPointer->Enabled));
	Borders_CheckBox_BorderEnabled->SetValue((bool)BorderPointer->Enabled);
	Borders_BorderName[0]->ChangeValue(BorderPointer->Name);
	Borders_BorderName[1]->ChangeValue(BorderPointer->Name2);
	Borders_BorderRessourceID->ChangeValue(lexical_cast<string>(BorderPointer->SLP));
	Borders_BorderUnknown3->ChangeValue(lexical_cast<string>(BorderPointer->Unknown3));
	Borders_BorderUnknown4->ChangeValue(lexical_cast<string>(BorderPointer->SoundID));
	for(short loop = 0; loop < 3; ++loop)
	{
		Borders_BorderColors[loop]->ChangeValue(lexical_cast<string>((short)BorderPointer->Colors[loop]));
	}
	for(short loop = 0; loop < Borders_BorderUnknown5.size(); ++loop)
	Borders_BorderUnknown5[loop]->ChangeValue(lexical_cast<string>((short)BorderPointer->Unknown5[loop]));
	Borders_BorderUnknown6->ChangeValue(lexical_cast<string>(BorderPointer->Unknown6));
	Borders_BorderFrameCount->ChangeValue(lexical_cast<string>(BorderPointer->FrameCount));
	Borders_BorderUnknown8->ChangeValue(lexical_cast<string>(BorderPointer->AngleCount));
	Borders_BorderTerrain->ChangeValue(lexical_cast<string>(BorderPointer->TerrainID));
	Borders_ComboBox_BorderTerrain->SetSelection(BorderPointer->TerrainID + 1);
	ListTerrainBorderFrames();
}

void AGE_Frame::OnTerrainBordersCopy(wxCommandEvent &Event)
{
	auto selections = Borders_Borders_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TerrainBorders, BorderIDs, copies->TerrainBorder);
}

void AGE_Frame::OnTerrainBordersPaste(wxCommandEvent &Event)
{
	auto selections = Borders_Borders_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoResize(GenieFile->TerrainBorders, BorderIDs[0], copies->TerrainBorder);
	ListTerrainBorders();
}

string AGE_Frame::GetTerrainBorderFrameName(short Index)
{
	return "Frame "+lexical_cast<string>(GenieFile->TerrainBorders[BorderIDs[0]].Frames[Index].FrameID)
	+" - Flags "+lexical_cast<string>(GenieFile->TerrainBorders[BorderIDs[0]].Frames[Index].Flag1)
	+" "+lexical_cast<string>(GenieFile->TerrainBorders[BorderIDs[0]].Frames[Index].Flag2)+" ";
}

void AGE_Frame::OnTerrainBorderFramesSearch(wxCommandEvent &Event)
{
	ListTerrainBorderFrames();
}

void AGE_Frame::ListTerrainBorderFrames()
{
	searchText = Borders_Frames_Search->GetValue().Lower();
	excludeText = Borders_Frames_Search_R->GetValue().Lower();

	auto selections = Borders_Frames_List->GetSelections(Items);
	Borders_Frames_List->Clear();

	for(short loop = 0; loop < GenieFile->TerrainBorders[BorderIDs[0]].Frames.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetTerrainBorderFrameName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Borders_Frames_List->Append(Name, (void*)&GenieFile->TerrainBorders[BorderIDs[0]].Frames[loop]);
		}
	}

	ListingFix(selections, Borders_Frames_List);

	wxCommandEvent E;
	OnTerrainBorderFramesSelect(E);
}

void AGE_Frame::OnTerrainBorderFramesSelect(wxCommandEvent &Event)
{
	auto selections = Borders_Frames_List->GetSelections(Items);
	if(selections < 1) return;

	FrameIDs.resize(selections);
	Borders_BorderFrameID->resize(selections);
	Borders_BorderFlag1->resize(selections);
	Borders_BorderFlag2->resize(selections);

	genie::TBFrameData * FramePointer;
	for(auto loop = selections; loop--> 0;)
	{
		FramePointer = (genie::TBFrameData*)Borders_Frames_List->GetClientData(Items.Item(loop));
		FrameIDs[loop] = (FramePointer - (&GenieFile->TerrainBorders[BorderIDs[0]].Frames[0]));

		Borders_BorderFrameID->container[loop] = &FramePointer->FrameID;
		Borders_BorderFlag1->container[loop] = &FramePointer->Flag1;
		Borders_BorderFlag2->container[loop] = &FramePointer->Flag2;
	}

	Borders_BorderFrameID->ChangeValue(lexical_cast<string>(FramePointer->FrameID));
	Borders_BorderFlag1->ChangeValue(lexical_cast<string>(FramePointer->Flag1));
	Borders_BorderFlag2->ChangeValue(lexical_cast<string>(FramePointer->Flag2));
}

void AGE_Frame::OnTerrainBorderFramesCopy(wxCommandEvent &Event)
{
	auto selections = Borders_Frames_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TerrainBorders[BorderIDs[0]].Frames, FrameIDs, copies->TBFrameData);
}

void AGE_Frame::OnTerrainBorderFramesPaste(wxCommandEvent &Event)
{
	auto selections = Borders_Frames_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoResize(GenieFile->TerrainBorders[BorderIDs[0]].Frames, FrameIDs[0], copies->TBFrameData);
	ListTerrainBorderFrames();
}

void AGE_Frame::OnTerrainBorderFramesCopyToBorders(wxCommandEvent &Event)
{
	for(short loop=1; loop < BorderIDs.size(); ++loop)
	{
		GenieFile->TerrainBorders[BorderIDs[loop]].Frames = GenieFile->TerrainBorders[BorderIDs[0]].Frames;
	}
}

void AGE_Frame::CreateTerrainBorderControls()
{
	Tab_TerrainBorders = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Borders_Main = new wxBoxSizer(wxHORIZONTAL);
	Borders_ListArea = new wxBoxSizer(wxVERTICAL);
	Borders_Borders_Buttons = new wxGridSizer(2, 0, 0);
	Borders_Borders = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainBorders, "Terrain Borders");
	Borders_Borders_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Borders_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Borders_List = new wxListBox(Tab_TerrainBorders, wxID_ANY, wxDefaultPosition, wxSize(10, 220), 0, NULL, wxLB_EXTENDED);
	Borders_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Borders_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Borders_DataArea = new wxBoxSizer(wxVERTICAL);
	Borders_DataTopRow = new wxBoxSizer(wxHORIZONTAL);
	Borders_Data1 = new wxGridSizer(4, 5, 5);

	Borders_Holder_BorderEnabled = new wxBoxSizer(wxVERTICAL);
	Borders_Holder_BorderEnabled1 = new wxBoxSizer(wxHORIZONTAL);
	Borders_Text_BorderEnabled = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Enabled", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderEnabled = new TextCtrl_Short(Tab_TerrainBorders);
	Borders_CheckBox_BorderEnabled = new CheckBox_2State(Tab_TerrainBorders, " Yes", Borders_BorderEnabled);
	for(short loop = 0; loop < 2; ++loop)
	{
		Borders_Holder_BorderName[loop] = new wxBoxSizer(wxVERTICAL);
		Borders_BorderName[loop] = new TextCtrl_String(Tab_TerrainBorders, 13);
	}
	Borders_Text_BorderName[0] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Text_BorderName[1] = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " SLP Name ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_Holder_BorderRessourceID = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderRessourceID = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderRessourceID = new TextCtrl_Long(Tab_TerrainBorders);
	Borders_Holder_BorderColors = new wxBoxSizer(wxVERTICAL);
	Borders_Grid_BorderColors = new wxGridSizer(3, 0, 0);
	Borders_Text_BorderColors = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Colors", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 3; ++loop)
	Borders_BorderColors[loop] = new TextCtrl_UByte(Tab_TerrainBorders);
	Borders_Holder_BorderFrameCount = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderFrameCount = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderFrameCount = new TextCtrl_Short(Tab_TerrainBorders);
	Borders_Holder_BorderTerrain = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderTerrain = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderTerrain = new TextCtrl_Short(Tab_TerrainBorders);
	Borders_ComboBox_BorderTerrain = new ComboBox_Plus1(Tab_TerrainBorders, Borders_BorderTerrain);
	TerrainComboBoxList.push_back(Borders_ComboBox_BorderTerrain);

	Borders_FrameData = new wxBoxSizer(wxHORIZONTAL);
	Borders_Holder_Frames = new wxStaticBoxSizer(wxHORIZONTAL, Tab_TerrainBorders, "Frames");
	Borders_Frames = new wxBoxSizer(wxVERTICAL);
	Borders_Frames_Buttons = new wxGridSizer(2, 0, 0);
	Borders_Frames_Search = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Frames_Search_R = new wxTextCtrl(Tab_TerrainBorders, wxID_ANY);
	Borders_Frames_List = new wxListBox(Tab_TerrainBorders, wxID_ANY, wxDefaultPosition, wxSize(10, 220), 0, NULL, wxLB_EXTENDED);
	Frames_Copy = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Frames_Paste = new wxButton(Tab_TerrainBorders, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Frames_CopyToBorders = new wxButton(Tab_TerrainBorders, wxID_ANY, "Copy all to selected borders", wxDefaultPosition, wxSize(5, 20));

	Borders_Holder_FrameArea = new wxBoxSizer(wxVERTICAL);
	Borders_Holder_BorderFrameID = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderFrameID = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Frame", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderFrameID = new TextCtrl_Short(Tab_TerrainBorders);
	Borders_Holder_BorderFlag1 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderFlag1 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Flag 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderFlag1 = new TextCtrl_Short(Tab_TerrainBorders);
	Borders_Holder_BorderFlag2 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderFlag2 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Flag 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderFlag2 = new TextCtrl_Short(Tab_TerrainBorders);

	Borders_Unknonws = new wxGridSizer(5, 5, 5);
	Borders_Holder_BorderUnknown1 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderUnknown1 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderUnknown1 = new TextCtrl_Short(Tab_TerrainBorders);
	Borders_Holder_BorderUnknown3 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderUnknown3 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderUnknown3 = new TextCtrl_Float(Tab_TerrainBorders);
	Borders_Holder_BorderUnknown4 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderUnknown4 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderUnknown4 = new TextCtrl_Long(Tab_TerrainBorders);
	Borders_Holder_BorderUnknown5 = new wxBoxSizer(wxVERTICAL);
	Borders_Grid_BorderUnknown5 = new wxGridSizer(5, 0, 0);
	Borders_Text_BorderUnknown5 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < Borders_BorderUnknown5.size(); ++loop)
	Borders_BorderUnknown5[loop] = new TextCtrl_Byte(Tab_TerrainBorders);
	Borders_Holder_BorderUnknown6 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderUnknown6 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderUnknown6 = new TextCtrl_Float(Tab_TerrainBorders);
	Borders_Holder_BorderUnknown8 = new wxBoxSizer(wxVERTICAL);
	Borders_Text_BorderUnknown8 = new wxStaticText(Tab_TerrainBorders, wxID_ANY, " Angle Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Borders_BorderUnknown8 = new TextCtrl_Short(Tab_TerrainBorders);

	for(short loop = 0; loop < 2; ++loop)
	{
		Borders_Holder_BorderName[loop]->Add(Borders_Text_BorderName[loop], 0, wxEXPAND);
		Borders_Holder_BorderName[loop]->Add(Borders_BorderName[loop], 0, wxEXPAND);
	}
	Borders_Holder_BorderEnabled1->Add(Borders_BorderEnabled, 1, wxEXPAND);
	Borders_Holder_BorderEnabled1->Add(2, -1);
	Borders_Holder_BorderEnabled1->Add(Borders_CheckBox_BorderEnabled, 1, wxEXPAND);
	Borders_Holder_BorderEnabled->Add(Borders_Text_BorderEnabled, 0, wxEXPAND);
	Borders_Holder_BorderEnabled->Add(Borders_Holder_BorderEnabled1, 1, wxEXPAND);

	Borders_Borders_Buttons->Add(Borders_Copy, 1, wxEXPAND);
	Borders_Borders_Buttons->Add(Borders_Paste, 1, wxEXPAND);

	Borders_Borders->Add(Borders_Borders_Search, 0, wxEXPAND);
	Borders_Borders->Add(Borders_Borders_Search_R, 0, wxEXPAND);
	Borders_Borders->Add(-1, 2);
	Borders_Borders->Add(Borders_Borders_List, 1, wxEXPAND);
	Borders_Borders->Add(-1, 2);
	Borders_Borders->Add(Borders_Borders_Buttons, 0, wxEXPAND);

	Borders_ListArea->Add(-1, 10);
	Borders_ListArea->Add(Borders_Borders, 1, wxEXPAND);
	Borders_ListArea->Add(-1, 10);

	Borders_DataTopRow->Add(Borders_Holder_BorderEnabled, 1, wxEXPAND);
	Borders_DataTopRow->Add(5, -1);
	Borders_DataTopRow->Add(Borders_Holder_BorderName[0], 2, wxEXPAND);
	Borders_DataTopRow->Add(5, -1);
	Borders_DataTopRow->Add(Borders_Holder_BorderName[1], 2, wxEXPAND);
	Borders_DataTopRow->AddStretchSpacer(1);

	Borders_Holder_BorderRessourceID->Add(Borders_Text_BorderRessourceID, 0, wxEXPAND);
	Borders_Holder_BorderRessourceID->Add(Borders_BorderRessourceID, 0, wxEXPAND);
	Borders_Holder_BorderUnknown3->Add(Borders_Text_BorderUnknown3, 0, wxEXPAND);
	Borders_Holder_BorderUnknown3->Add(Borders_BorderUnknown3, 1, wxEXPAND);
	Borders_Holder_BorderUnknown4->Add(Borders_Text_BorderUnknown4, 0, wxEXPAND);
	Borders_Holder_BorderUnknown4->Add(Borders_BorderUnknown4, 1, wxEXPAND);
	for(short loop = 0; loop < 3; ++loop)
	Borders_Grid_BorderColors->Add(Borders_BorderColors[loop], 1, wxEXPAND);
	Borders_Holder_BorderColors->Add(Borders_Text_BorderColors, 0, wxEXPAND);
	Borders_Holder_BorderColors->Add(Borders_Grid_BorderColors, 0, wxEXPAND);
	Borders_Holder_BorderUnknown5->Add(Borders_Text_BorderUnknown5, 0, wxEXPAND);
	for(short loop = 0; loop < Borders_BorderUnknown5.size(); ++loop)
	Borders_Grid_BorderUnknown5->Add(Borders_BorderUnknown5[loop], 1, wxEXPAND);
	Borders_Holder_BorderUnknown5->Add(Borders_Grid_BorderUnknown5, 0, wxEXPAND);
	Borders_Holder_BorderUnknown6->Add(Borders_Text_BorderUnknown6, 0, wxEXPAND);
	Borders_Holder_BorderUnknown6->Add(Borders_BorderUnknown6, 1, wxEXPAND);
	Borders_Holder_BorderFrameCount->Add(Borders_Text_BorderFrameCount, 0, wxEXPAND);
	Borders_Holder_BorderFrameCount->Add(Borders_BorderFrameCount, 0, wxEXPAND);
	Borders_Holder_BorderUnknown8->Add(Borders_Text_BorderUnknown8, 0, wxEXPAND);
	Borders_Holder_BorderUnknown8->Add(Borders_BorderUnknown8, 1, wxEXPAND);
	Borders_Holder_BorderTerrain->Add(Borders_Text_BorderTerrain, 0, wxEXPAND);
	Borders_Holder_BorderTerrain->Add(Borders_BorderTerrain, 1, wxEXPAND);
	Borders_Holder_BorderTerrain->Add(Borders_ComboBox_BorderTerrain, 1, wxEXPAND);
	Borders_Holder_BorderUnknown1->Add(Borders_Text_BorderUnknown1, 0, wxEXPAND);
	Borders_Holder_BorderUnknown1->Add(Borders_BorderUnknown1, 1, wxEXPAND);

	Borders_Data1->Add(Borders_Holder_BorderRessourceID, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Holder_BorderColors, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Holder_BorderFrameCount, 1, wxEXPAND);
	Borders_Data1->Add(Borders_Holder_BorderTerrain, 1, wxEXPAND);

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

	Borders_Holder_BorderFrameID->Add(Borders_Text_BorderFrameID, 0, wxEXPAND);
	Borders_Holder_BorderFrameID->Add(Borders_BorderFrameID, 1, wxEXPAND);
	Borders_Holder_BorderFlag1->Add(Borders_Text_BorderFlag1, 0, wxEXPAND);
	Borders_Holder_BorderFlag1->Add(Borders_BorderFlag1, 1, wxEXPAND);
	Borders_Holder_BorderFlag2->Add(Borders_Text_BorderFlag2, 0, wxEXPAND);
	Borders_Holder_BorderFlag2->Add(Borders_BorderFlag2, 1, wxEXPAND);

	Borders_Holder_FrameArea->Add(Borders_Holder_BorderFrameID, 0, wxEXPAND);
	Borders_Holder_FrameArea->Add(-1, 5);
	Borders_Holder_FrameArea->Add(Borders_Holder_BorderFlag1, 0, wxEXPAND);
	Borders_Holder_FrameArea->Add(-1, 5);
	Borders_Holder_FrameArea->Add(Borders_Holder_BorderFlag2, 0, wxEXPAND);

	Borders_Holder_Frames->Add(Borders_Frames, 3, wxEXPAND);
	Borders_Holder_Frames->Add(5, -1);
	Borders_Holder_Frames->Add(Borders_Holder_FrameArea, 2, wxEXPAND);
	Borders_FrameData->Add(Borders_Holder_Frames, 5, wxEXPAND);
	Borders_FrameData->AddStretchSpacer(3);

	Borders_Unknonws->Add(Borders_Holder_BorderUnknown1, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Holder_BorderUnknown3, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Holder_BorderUnknown4, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Holder_BorderUnknown6, 1, wxEXPAND);
	Borders_Unknonws->Add(Borders_Holder_BorderUnknown8, 1, wxEXPAND);

	Borders_DataArea->Add(-1, 10);
	Borders_DataArea->Add(Borders_DataTopRow, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 5);
	Borders_DataArea->Add(Borders_Data1, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 5);
	Borders_DataArea->Add(Borders_FrameData, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 5);
	Borders_DataArea->Add(Borders_Unknonws, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 5);
	Borders_DataArea->Add(Borders_Holder_BorderUnknown5, 0, wxEXPAND);
	Borders_DataArea->Add(-1, 10);

	Borders_Main->Add(10, -1);
	Borders_Main->Add(Borders_ListArea, 1, wxEXPAND);
	Borders_Main->Add(10, -1);
	Borders_Main->Add(Borders_DataArea, 3, wxEXPAND);
	Borders_Main->Add(10, -1);

	Tab_TerrainBorders->SetSizer(Borders_Main);

	Connect(Borders_Borders_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSearch));
	Connect(Borders_Borders_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSearch));
	Connect(Borders_Borders_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersSelect));
	Connect(Borders_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersCopy));
	Connect(Borders_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBordersPaste));
	Connect(Borders_Frames_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesSearch));
	Connect(Borders_Frames_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesSearch));
	Connect(Borders_Frames_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesSelect));
	Connect(Frames_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesCopy));
	Connect(Frames_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesPaste));
	Connect(Frames_CopyToBorders->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainBorderFramesCopyToBorders));

	for(short loop = 0; loop < 2; ++loop)
	Borders_BorderName[loop]->Connect(Borders_BorderName[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Borders), NULL, this);
	Borders_BorderFrameID->Connect(Borders_BorderFrameID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Borders), NULL, this);
	Borders_BorderFlag1->Connect(Borders_BorderFlag1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Borders), NULL, this);
	Borders_BorderFlag2->Connect(Borders_BorderFlag2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Borders), NULL, this);
}

void AGE_Frame::OnKillFocus_Borders(wxFocusEvent &Event)
{
	if(!((AGETextCtrl*)Event.GetEventObject())->SaveEdits()) return;
	if(Event.GetId() == Borders_BorderName[0]->GetId() || Event.GetId() == Borders_BorderName[1]->GetId())
	{
		ListTerrainBorders();
	}
	else if(Event.GetId() == Borders_BorderFrameID->GetId() || Event.GetId() == Borders_BorderFlag1->GetId() || Event.GetId() == Borders_BorderFlag2->GetId())
	{
		ListTerrainBorderFrames();
	}
	Event.Skip();
}
