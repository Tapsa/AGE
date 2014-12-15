#include "../AGE_Frame.h"

void AGE_Frame::ListGeneral()
{
	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnVariableCalc(wxFocusEvent &Event)
{
	int32_t Result, Temp;

	if(!General_CalcBoxes[0]->IsEmpty())
	{
		try{Result = lexical_cast<int32_t>(General_CalcBoxes[0]->GetValue());}
		catch(bad_lexical_cast e){return;}
	}
	else Result = 0;
	Result = (uint8_t)Result;

	if(!General_CalcBoxes[1]->IsEmpty())
	{
		try{Temp = lexical_cast<int32_t>(General_CalcBoxes[1]->GetValue());}
		catch(bad_lexical_cast e){return;}
	}
	else Temp = 0;
	Result += (uint8_t)Temp << 8;

	if(!General_CalcBoxes[2]->IsEmpty())
	{
		try{Temp = lexical_cast<int32_t>(General_CalcBoxes[2]->GetValue());}
		catch(bad_lexical_cast e){return;}
	}
	else Temp = 0;
	Result += (uint8_t)Temp << 16;

	if(!General_CalcBoxes[3]->IsEmpty())
	{
		try{Temp = lexical_cast<int32_t>(General_CalcBoxes[3]->GetValue());}
		catch(bad_lexical_cast e){return;}
	}
	else Temp = 0;
	Result += (uint8_t)Temp << 24;

	General_CalcBoxes[4]->ChangeValue(lexical_cast<string>(Result));

	Event.Skip();
}

void AGE_Frame::OnVariableCalcReverse(wxFocusEvent &Event)
{
	if(General_CalcBoxes[4]->IsEmpty()) return;

	int32_t Result;
	try{Result = lexical_cast<int32_t>(General_CalcBoxes[4]->GetValue());}
	catch(bad_lexical_cast e){return;}

	General_CalcBoxes[0]->ChangeValue(lexical_cast<string>((short)(int8_t)Result));
	Result >>= 8;
	General_CalcBoxes[1]->ChangeValue(lexical_cast<string>((short)(int8_t)Result));
	Result >>= 8;
	General_CalcBoxes[2]->ChangeValue(lexical_cast<string>((short)(int8_t)Result));
	Result >>= 8;
	General_CalcBoxes[3]->ChangeValue(lexical_cast<string>((short)(int8_t)Result));

	Event.Skip();
}

void AGE_Frame::OnGeneralSelect(wxCommandEvent &Event)
{
	for(short loop = 0; loop < General_TerrainHeader.size(); ++loop)
	{
		General_TerrainHeader[loop]->resize(1);
		General_TerrainHeader[loop]->container[0] = &GenieFile->TerrainBlock.GraphicsRendering[loop];
		General_TerrainHeader[loop]->Update();
	}
	for(short loop = 0; loop < GenieFile->TerrainBlock.ZeroSpace.size(); ++loop)
	{
		General_AfterBorders[loop]->resize(1);
		General_AfterBorders[loop]->container[0] = &GenieFile->TerrainBlock.ZeroSpace[loop];
		General_AfterBorders[loop]->Update();
	}
	for(short loop = 0; loop < GenieFile->TerrainBlock.Rendering.size(); ++loop)
	{
		General_TerrainRendering[loop]->resize(1);
		General_TerrainRendering[loop]->container[0] = &GenieFile->TerrainBlock.Rendering[loop];
		General_TerrainRendering[loop]->Update();
	}
	for(short loop = 0; loop < GenieFile->TerrainBlock.Something.size(); ++loop)
	{
		General_Something[loop]->resize(1);
		General_Something[loop]->container[0] = &GenieFile->TerrainBlock.Something[loop];
		General_Something[loop]->Update();
	}
	Unknown_UnknownPointer->resize(1);
	Unknown_UnknownPointer->container[0] = &GenieFile->RandomMaps.RandomMapPointer;
	Unknown_UnknownPointer->Update();
	if(GenieVersion <= genie::GV_RoR) return;
	for(long loop = 0;loop < General_TTUnknown.size(); ++loop)
	{
		General_TTUnknown[loop]->resize(1);
		General_TTUnknown[loop]->container[0] = &GenieFile->UnknownPreTechTree[loop];
		General_TTUnknown[loop]->Update();
	}
	General_TTUnknown[7]->resize(1);
	General_TTUnknown[7]->container[0] = &GenieFile->TechTree.Unknown2;
	General_TTUnknown[7]->Update();
	if(GenieVersion <= genie::GV_TC) return;
	General_SUnknown2->resize(1);
	General_SUnknown2->container[0] = &GenieFile->SUnknown2;
	General_SUnknown2->Update();
	General_SUnknown3->resize(1);
	General_SUnknown3->container[0] = &GenieFile->SUnknown3;
	General_SUnknown3->Update();
	General_SUnknown4->resize(1);
	General_SUnknown4->container[0] = &GenieFile->SUnknown4;
	General_SUnknown4->Update();
	General_SUnknown5->resize(1);
	General_SUnknown5->container[0] = &GenieFile->SUnknown5;
	General_SUnknown5->Update();
	General_SUnknown7->resize(1);
	General_SUnknown7->container[0] = &GenieFile->SUnknown7;
	General_SUnknown7->Update();
	General_SUnknown8->resize(1);
	General_SUnknown8->container[0] = &GenieFile->SUnknown8;
	General_SUnknown8->Update();
}

void AGE_Frame::CreateGeneralControls()
{
	Tab_General = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	General_Main = new wxBoxSizer(wxVERTICAL);
	General_TopRow = new wxBoxSizer(wxHORIZONTAL);
	General_Refresh = new wxButton(Tab_General, wxID_ANY, "Refresh", wxDefaultPosition, wxSize(0, 20));
	General_CalcBoxes_Text = new wxStaticText(Tab_General, wxID_ANY, " Variable Converter *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_CalcBoxes_Text->SetToolTip("From four 8 bit integers to one 32 bit integer or vice versa");
	General_CalcBoxesMiddle_Text = new wxStaticText(Tab_General, wxID_ANY, " = ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 5; ++loop)
	General_CalcBoxes[loop] = new wxTextCtrl(Tab_General, wxID_ANY);
	General_Scroller = new wxScrolledWindow(Tab_General, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	General_ScrollArea = new wxBoxSizer(wxHORIZONTAL);
	General_ScrollSpace = new wxBoxSizer(wxVERTICAL);

	const wxString SWUNKNOWNSINFO = "Unknowns 2 to 5 are in the beginning of the file,\nright after civilization count (first of the two) and\nbefore terrain restrictions";
	General_Variables_Grid = new wxGridSizer(6, 5, 5);
	General_Variables1_Holder = new wxStaticBoxSizer(wxVERTICAL, General_Scroller, "Star Wars Unknowns");
	General_SUnknown2_Holder = new wxBoxSizer(wxVERTICAL);
	General_SUnknown2_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 2 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown2 = new TextCtrl_Long(General_Scroller);
	General_SUnknown2->SetToolTip(SWUNKNOWNSINFO);
	General_SUnknown3_Holder = new wxBoxSizer(wxVERTICAL);
	General_SUnknown3_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 3 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown3 = new TextCtrl_Long(General_Scroller);
	General_SUnknown3->SetToolTip(SWUNKNOWNSINFO);
	General_SUnknown4_Holder = new wxBoxSizer(wxVERTICAL);
	General_SUnknown4_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 4 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown4 = new TextCtrl_Long(General_Scroller);
	General_SUnknown4->SetToolTip(SWUNKNOWNSINFO);
	General_SUnknown5_Holder = new wxBoxSizer(wxVERTICAL);
	General_SUnknown5_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 5 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown5 = new TextCtrl_Long(General_Scroller);
	General_SUnknown5->SetToolTip(SWUNKNOWNSINFO);
	General_SUnknown7_Holder = new wxBoxSizer(wxVERTICAL);
	General_SUnknown7_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 7 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown7 = new TextCtrl_Byte(General_Scroller);
	General_SUnknown7->SetToolTip("In the file this is\nright after civilizations and\nbefore researches");
	General_SUnknown8_Holder = new wxBoxSizer(wxVERTICAL);
	General_SUnknown8_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 8 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown8 = new TextCtrl_Byte(General_Scroller);
	General_SUnknown8->SetToolTip("In the file this is\nright after researches and\nbefore technology trees");
	General_TerrainHeader_Holder = new wxBoxSizer(wxVERTICAL);
	General_TerrainHeader_Text = new wxStaticText(General_Scroller, wxID_ANY, " Graphics-related", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_TerrainHeader_Grid = new wxGridSizer(16, 0, 0);
	General_BorderRelated_Holder = new wxBoxSizer(wxVERTICAL);
	General_BorderRelated_Text = new wxStaticText(General_Scroller, wxID_ANY, " Borders-related", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderRelated_Grid = new wxGridSizer(8, 0, 0);
	General_TerrainRendering_Holder = new wxBoxSizer(wxVERTICAL);
	General_TerrainRendering_Text = new wxStaticText(General_Scroller, wxID_ANY, " Graphics-related", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_TerrainRendering_Grid = new wxGridSizer(16, 0, 0);
	General_Something_Grid = new wxGridSizer(8, 0, 0);
	for(short loop = 0; loop < General_TerrainHeader.size(); ++loop)
	General_TerrainHeader[loop] = new TextCtrl_Short(General_Scroller);
	for(short loop = 0; loop < General_AfterBorders.size(); ++loop)
	{
		General_AfterBorders[loop] = new TextCtrl_Short(General_Scroller);
		General_AfterBorders[loop]->SetToolTip("In the file these are\nright after terrain borders and\nbefore the second terrain count");
	}
	for(short loop = 0; loop < General_TerrainRendering.size(); ++loop)
	General_TerrainRendering[loop] = new TextCtrl_Short(General_Scroller);
	for(short loop = 0; loop < General_Something.size(); ++loop)
	General_Something[loop] = new TextCtrl_Long(General_Scroller);
/*	General_RenderPlusUnknown_Holder = new wxBoxSizer(wxVERTICAL);
	General_RenderPlusUnknownTop_Holder = new wxBoxSizer(wxHORIZONTAL);
	General_SomethingPicker = new wxTextCtrl(General_Scroller, wxID_ANY);
	General_SomethingNext = new wxButton(General_Scroller, wxID_ANY, "Next", wxDefaultPosition, wxSize(0, 20));
	General_SomethingPrev = new wxButton(General_Scroller, wxID_ANY, "Previous", wxDefaultPosition, wxSize(0, 20));
	General_SomethingSize = new wxStaticText(General_Scroller, wxID_ANY, " Data Size", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_TechTree_Text = new wxStaticText(General_Scroller, wxID_ANY, " Unknown Data with 32 Bit Pointers", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
*/
	General_TopRow->Add(10, -1);
	General_TopRow->Add(General_Refresh, 2, wxEXPAND);
	General_TopRow->AddStretchSpacer(3);
	for(short loop = 0; loop < 4; ++loop)
	General_TopRow->Add(General_CalcBoxes[loop], 1, wxEXPAND);
	General_TopRow->Add(General_CalcBoxesMiddle_Text, 0, wxEXPAND);
	General_TopRow->Add(General_CalcBoxes[4], 1, wxEXPAND);
	General_TopRow->Add(General_CalcBoxes_Text, 0, wxEXPAND);
	General_TopRow->AddStretchSpacer(1);

	for(short loop = 0; loop < General_TerrainHeader.size(); ++loop)
	General_TerrainHeader_Grid->Add(General_TerrainHeader[loop], 1, wxEXPAND);
	General_TerrainHeader_Holder->Add(General_TerrainHeader_Text, 0, wxEXPAND);
	General_TerrainHeader_Holder->Add(General_TerrainHeader_Grid, 0, wxEXPAND);

	for(short loop = 0; loop < General_AfterBorders.size(); ++loop)
	General_BorderRelated_Grid->Add(General_AfterBorders[loop], 1, wxEXPAND);
	General_BorderRelated_Holder->Add(General_BorderRelated_Text, 0, wxEXPAND);
	General_BorderRelated_Holder->Add(General_BorderRelated_Grid, 0, wxEXPAND);

	for(short loop = 0; loop < General_TerrainRendering.size(); ++loop)
	General_TerrainRendering_Grid->Add(General_TerrainRendering[loop], 1, wxEXPAND);
	for(short loop = 0; loop < General_Something.size(); ++loop)
	General_Something_Grid->Add(General_Something[loop], 1, wxEXPAND);
	General_TerrainRendering_Holder->Add(General_TerrainRendering_Text, 0, wxEXPAND);
	General_TerrainRendering_Holder->Add(General_TerrainRendering_Grid, 0, wxEXPAND);
	General_TerrainRendering_Holder->Add(General_Something_Grid, 0, wxEXPAND);

	General_SUnknown7_Holder->Add(General_SUnknown7_Text, 0, wxEXPAND);
	General_SUnknown7_Holder->Add(General_SUnknown7, 1, wxEXPAND);
	General_SUnknown8_Holder->Add(General_SUnknown8_Text, 0, wxEXPAND);
	General_SUnknown8_Holder->Add(General_SUnknown8, 1, wxEXPAND);
	General_SUnknown2_Holder->Add(General_SUnknown2_Text, 0, wxEXPAND);
	General_SUnknown2_Holder->Add(General_SUnknown2, 1, wxEXPAND);
	General_SUnknown3_Holder->Add(General_SUnknown3_Text, 0, wxEXPAND);
	General_SUnknown3_Holder->Add(General_SUnknown3, 1, wxEXPAND);
	General_SUnknown4_Holder->Add(General_SUnknown4_Text, 0, wxEXPAND);
	General_SUnknown4_Holder->Add(General_SUnknown4, 1, wxEXPAND);
	General_SUnknown5_Holder->Add(General_SUnknown5_Text, 0, wxEXPAND);
	General_SUnknown5_Holder->Add(General_SUnknown5, 1, wxEXPAND);
	General_Variables_Grid->Add(General_SUnknown2_Holder, 1, wxEXPAND);
	General_Variables_Grid->Add(General_SUnknown3_Holder, 1, wxEXPAND);
	General_Variables_Grid->Add(General_SUnknown4_Holder, 1, wxEXPAND);
	General_Variables_Grid->Add(General_SUnknown5_Holder, 1, wxEXPAND);
	General_Variables_Grid->Add(General_SUnknown7_Holder, 1, wxEXPAND);
	General_Variables_Grid->Add(General_SUnknown8_Holder, 1, wxEXPAND);
	General_Variables1_Holder->Add(General_Variables_Grid, 0, wxEXPAND);
/*
	General_RenderPlusUnknownTop_Holder->Add(General_TechTree_Text, 0, wxEXPAND);
	General_RenderPlusUnknownTop_Holder->Add(5, -1);
	General_RenderPlusUnknownTop_Holder->Add(General_SomethingPicker, 1, wxEXPAND);
	General_RenderPlusUnknownTop_Holder->Add(5, -1);
	General_RenderPlusUnknownTop_Holder->Add(General_SomethingNext, 1, wxEXPAND);
	General_RenderPlusUnknownTop_Holder->Add(5, -1);
	General_RenderPlusUnknownTop_Holder->Add(General_SomethingPrev, 1, wxEXPAND);
	General_RenderPlusUnknownTop_Holder->Add(5, -1);
	General_RenderPlusUnknownTop_Holder->Add(General_SomethingSize, 1, wxEXPAND);
	General_RenderPlusUnknownTop_Holder->AddStretchSpacer(2);
	General_RenderPlusUnknown_Holder->Add(General_RenderPlusUnknownTop_Holder, 0, wxEXPAND);
*/
	General_ScrollSpace->Add(General_Variables1_Holder, 0, wxEXPAND);
	General_ScrollSpace->Add(-1, 10);
	General_ScrollSpace->Add(General_TerrainHeader_Holder, 0, wxEXPAND);
	General_ScrollSpace->Add(-1, 10);
	General_ScrollSpace->Add(General_BorderRelated_Holder, 0, wxEXPAND);
	General_ScrollSpace->Add(-1, 10);
	General_ScrollSpace->Add(General_TerrainRendering_Holder, 0, wxEXPAND);
	//General_ScrollSpace->Add(-1, 10);
	//General_ScrollSpace->Add(General_RenderPlusUnknown_Holder, 0, wxEXPAND);

	General_ScrollArea->Add(10, -1);
	General_ScrollArea->Add(General_ScrollSpace, 1, wxEXPAND);
	General_ScrollArea->Add(5, -1);

	General_Scroller->SetSizer(General_ScrollArea);
	General_Scroller->SetScrollRate(0, 15);

	General_Main->Add(-1, 10);
	General_Main->Add(General_TopRow, 0, wxEXPAND);
	General_Main->Add(-1, 5);
	General_Main->Add(General_Scroller, 1, wxEXPAND);
	General_Main->Add(-1, 10);

	Tab_General->SetSizer(General_Main);

	Connect(General_Refresh->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGeneralSelect));
	//Connect(General_SomethingPicker->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnDataGridPage));
	//Connect(General_SomethingNext->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnDataGridNext));
	//Connect(General_SomethingPrev->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnDataGridPrev));
	for(short loop = 0; loop < 4; ++loop)
	General_CalcBoxes[loop]->Connect(General_CalcBoxes[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnVariableCalc), NULL, this);
	General_CalcBoxes[4]->Connect(General_CalcBoxes[4]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnVariableCalcReverse), NULL, this);
}

void AGE_Frame::OnUnknownsSearch(wxCommandEvent &Event)
{
	ListRandomMaps();
}

string AGE_Frame::GetUnknownName(short Index)
{
	if(GenieVersion >= genie::GV_AoK)
	{
		return "Map "+lexical_cast<string>(GenieFile->RandomMaps.MapHeaders[Index].ScriptNumber)+" ";
	}
	string Name = "";
	switch(Index)
	{
		case 0: Name += "Small Islands ("; break;
		case 1: Name += "Large Islands ("; break;
		case 2: Name += "Coastal ("; break;
		case 3: Name += "Inland ("; break;
		case 4: Name += "Highland ("; break;
		case 5: Name += "Continental ("; break;
		case 6: Name += "Mediterranean ("; break;
		case 7: Name += "Hill Country ("; break;
		case 8: Name += "Narrows ("; break;
		case 9: Name += "Gigantic ("; break;
		default: Name += "Map (";
	}
	return Name += lexical_cast<string>(GenieFile->RandomMaps.MapHeaders[Index].ScriptNumber)+")";
}

void AGE_Frame::ListRandomMaps()
{
	InitRandomMaps();
	wxCommandEvent E;
	OnUnknownsSelect(E);
}

void AGE_Frame::InitRandomMaps()
{
	searchText = Unknowns_Search->GetValue().Lower();
	excludeText = Unknowns_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->RandomMaps.MapHeaders.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnknownName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->RandomMaps.Maps[loop]);
		}
	}
	Listing(Unknowns_List, filteredNames, dataPointers);
}

void AGE_Frame::OnUnknownsSelect(wxCommandEvent &Event)
{
	auto selections = Unknowns_List->GetSelections(Items);
	if(selections > 0)
	{
		RandomMapIDs.resize(selections);
		Unknowns_UnknownLevel->resize(selections);
		int PointerCount = selections * 2;
		for(short loop = 0; loop < Unknowns_Unknown1.size(); ++loop)
		Unknowns_Unknown1[loop]->resize(PointerCount);
		Unknowns_Pointer1->resize(PointerCount);
		Unknowns_Pointer2->resize(PointerCount);
		Unknowns_Pointer3->resize(PointerCount);
		Unknowns_Pointer4->resize(PointerCount);

		genie::MapHeader * MapPointer1;
		genie::Map * MapPointer2;
		for(auto sel = selections; sel--> 0;)
		{
			MapPointer2 = (genie::Map*)Unknowns_List->GetClientData(Items.Item(sel));
			RandomMapIDs[sel] = (MapPointer2 - (&GenieFile->RandomMaps.Maps[0]));
			MapPointer1 = &GenieFile->RandomMaps.MapHeaders[RandomMapIDs[sel]];

			Unknowns_UnknownLevel->container[sel] = &MapPointer1->ScriptNumber;
			int sel2 = sel + selections;
			Unknowns_Unknown1[0]->container[sel] = &MapPointer1->BorderSouthWest;
			Unknowns_Unknown1[0]->container[sel2] = &MapPointer2->BorderSouthWest;
			Unknowns_Unknown1[1]->container[sel] = &MapPointer1->BorderNorthWest;
			Unknowns_Unknown1[1]->container[sel2] = &MapPointer2->BorderNorthWest;
			Unknowns_Unknown1[2]->container[sel] = &MapPointer1->BorderNorthEast;
			Unknowns_Unknown1[2]->container[sel2] = &MapPointer2->BorderNorthEast;
			Unknowns_Unknown1[3]->container[sel] = &MapPointer1->BorderSouthEast;
			Unknowns_Unknown1[3]->container[sel2] = &MapPointer2->BorderSouthEast;
			Unknowns_Unknown1[4]->container[sel] = &MapPointer1->BorderUsage;
			Unknowns_Unknown1[4]->container[sel2] = &MapPointer2->BorderUsage;
			Unknowns_Unknown1[5]->container[sel] = &MapPointer1->WaterShape;
			Unknowns_Unknown1[5]->container[sel2] = &MapPointer2->WaterShape;
			Unknowns_Unknown1[6]->container[sel] = &MapPointer1->NonBaseTerrain;
			Unknowns_Unknown1[6]->container[sel2] = &MapPointer2->NonBaseTerrain;
			Unknowns_Unknown1[7]->container[sel] = &MapPointer1->BaseZoneCoverage;
			Unknowns_Unknown1[7]->container[sel2] = &MapPointer2->BaseZoneCoverage;
			Unknowns_Unknown1[8]->container[sel] = &MapPointer1->Unknown9;
			Unknowns_Unknown1[8]->container[sel2] = &MapPointer2->Unknown9;
			Unknowns_Pointer1->container[sel] = &MapPointer1->BaseZonePointer;
			Unknowns_Pointer1->container[sel2] = &MapPointer2->BaseZonePointer;
			Unknowns_Pointer2->container[sel] = &MapPointer1->MapTerrainPointer;
			Unknowns_Pointer2->container[sel2] = &MapPointer2->MapTerrainPointer;
			Unknowns_Pointer3->container[sel] = &MapPointer1->MapUnitPointer;
			Unknowns_Pointer3->container[sel2] = &MapPointer2->MapUnitPointer;
			Unknowns_Pointer4->container[sel] = &MapPointer1->MapUnknownPointer;
			Unknowns_Pointer4->container[sel2] = &MapPointer2->MapUnknownPointer;
		}

		Unknowns_UnknownLevel->Update();
		Unknowns_Unknown1[0]->Update();
		Unknowns_Unknown1[1]->Update();
		Unknowns_Unknown1[2]->Update();
		Unknowns_Unknown1[3]->Update();
		Unknowns_Unknown1[4]->Update();
		Unknowns_Unknown1[5]->Update();
		Unknowns_Unknown1[6]->Update();
		Unknowns_Unknown1[7]->Update();
		Unknowns_Unknown1[8]->Update();
		Unknowns_Pointer1->Update();
		Unknowns_Pointer2->Update();
		Unknowns_Pointer3->Update();
		Unknowns_Pointer4->Update();

		ListRMSBaseZones();
		ListRMSTerrains();
		ListRMSUnits();
		ListRMSUnknowns();
	}
	else
	{
		Unknowns_UnknownLevel->ChangeValue("0");
		for(short loop = 0; loop < Unknowns_Unknown1.size(); ++loop)
		Unknowns_Unknown1[loop]->ChangeValue("0");
		Unknowns_Pointer1->ChangeValue("0");
		Unknowns_Pointer2->ChangeValue("0");
		Unknowns_Pointer3->ChangeValue("0");
		Unknowns_Pointer4->ChangeValue("0");

		RMSBaseZones_List->Clear();
		DisableRMSBaseZones();
		RMSTerrain_List->Clear();
		DisableRMSTerrains();
		RMSUnit_List->Clear();
		DisableRMSUnits();
		RMSUnknown_List->Clear();
		DisableRMSUnknowns();
	}
	Unknowns_UnknownLevel->Enable(selections);
	for(short loop = 0; loop < Unknowns_Unknown1.size(); ++loop)
	Unknowns_Unknown1[loop]->Enable(selections);
	Unknowns_Pointer1->Enable(selections);
	Unknowns_Pointer2->Enable(selections);
	Unknowns_Pointer3->Enable(selections);
	Unknowns_Pointer4->Enable(selections);
}

void AGE_Frame::OnUnknownsAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->RandomMaps.MapHeaders);
	AddToList(GenieFile->RandomMaps.Maps);
	ListRandomMaps();
}

void AGE_Frame::OnUnknownsInsert(wxCommandEvent &Event)
{
	auto selections = Unknowns_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->RandomMaps.MapHeaders, RandomMapIDs[0]);
	InsertToList(GenieFile->RandomMaps.Maps, RandomMapIDs[0]);
	ListRandomMaps();
}

void AGE_Frame::OnUnknownsDelete(wxCommandEvent &Event)
{
	auto selections = Unknowns_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->RandomMaps.MapHeaders, RandomMapIDs);
	DeleteFromList(GenieFile->RandomMaps.Maps, RandomMapIDs);
	ListRandomMaps();
}

void AGE_Frame::OnUnknownsCopy(wxCommandEvent &Event)
{
	auto selections = Unknowns_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->RandomMaps.MapHeaders, RandomMapIDs, copies->MapHeader);
	CopyFromList(GenieFile->RandomMaps.Maps, RandomMapIDs, copies->Map);
	Unknowns_Paste->Enable(true);
	Unknowns_PasteInsert->Enable(true);
}

void AGE_Frame::OnUnknownsPaste(wxCommandEvent &Event)
{
	auto selections = Unknowns_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->RandomMaps.MapHeaders, RandomMapIDs, copies->MapHeader);
	PasteToList(GenieFile->RandomMaps.Maps, RandomMapIDs, copies->Map);
	ListRandomMaps();
}

void AGE_Frame::OnUnknownsPasteInsert(wxCommandEvent &Event)
{
	auto selections = Unknowns_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->RandomMaps.MapHeaders, RandomMapIDs[0], copies->MapHeader);
	PasteInsertToList(GenieFile->RandomMaps.Maps, RandomMapIDs[0], copies->Map);
	ListRandomMaps();
}

void AGE_Frame::OnRMSBaseZoneSearch(wxCommandEvent &Event)
{
	ListRMSBaseZones();
}

string AGE_Frame::GetRMSBaseZonesName(short Index)
{
	return "Base Zone "+lexical_cast<string>(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones[Index].Unknown1)+" ";
}

void AGE_Frame::ListRMSBaseZones()
{
	searchText = RMSBaseZones_Search->GetValue().Lower();
	excludeText = RMSBaseZones_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetRMSBaseZonesName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones[loop]);
		}
	}
	Listing(RMSBaseZones_List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnRMSBaseZoneSelect(E);
}

void AGE_Frame::OnRMSBaseZoneSelect(wxCommandEvent &Event)
{
	auto selections = RMSBaseZones_List->GetSelections(Items);
	if(selections < 1)
	{
		DisableRMSBaseZones();
		return;
	}

	UnknownFSIDs.resize(selections);
	RMSBaseZones_Unknown1->resize(selections);
	RMSBaseZones_BaseTerrain->resize(selections);
	RMSBaseZones_SpacingBetweenPlayers->resize(selections);
	RMSBaseZones_Unknown4->resize(selections);
	for(short loop = 0; loop < RMSBaseZones_Unknown5.size(); ++loop)
	RMSBaseZones_Unknown5[loop]->resize(selections);
	RMSBaseZones_Unknown6->resize(selections);
	RMSBaseZones_Unknown7->resize(selections);
	for(short loop = 0; loop < RMSBaseZones_Unknown8.size(); ++loop)
	RMSBaseZones_Unknown8[loop]->resize(selections);
	RMSBaseZones_StartAreaRadius->resize(selections);
	RMSBaseZones_Unknown10->resize(selections);
	RMSBaseZones_Unknown11->resize(selections);

	genie::BaseZone * UnknownPointer;
	for(auto sel = selections; sel--> 0;)
	{
		UnknownPointer = (genie::BaseZone*)RMSBaseZones_List->GetClientData(Items.Item(sel));
		UnknownFSIDs[sel] = (UnknownPointer - (&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones[0]));

		RMSBaseZones_Unknown1->container[sel] = &UnknownPointer->Unknown1;
		RMSBaseZones_BaseTerrain->container[sel] = &UnknownPointer->BaseTerrain;
		RMSBaseZones_SpacingBetweenPlayers->container[sel] = &UnknownPointer->SpacingBetweenPlayers;
		RMSBaseZones_Unknown4->container[sel] = &UnknownPointer->Unknown4;
		for(short loop = 0; loop < RMSBaseZones_Unknown5.size(); ++loop)
		RMSBaseZones_Unknown5[loop]->container[sel] = &UnknownPointer->Unknown5[loop];
		RMSBaseZones_Unknown6->container[sel] = &UnknownPointer->Unknown6;
		RMSBaseZones_Unknown7->container[sel] = &UnknownPointer->Unknown7;
		for(short loop = 0; loop < RMSBaseZones_Unknown8.size(); ++loop)
		RMSBaseZones_Unknown8[loop]->container[sel] = &UnknownPointer->Unknown8[loop];
		RMSBaseZones_StartAreaRadius->container[sel] = &UnknownPointer->StartAreaRadius;
		RMSBaseZones_Unknown10->container[sel] = &UnknownPointer->Unknown10;
		RMSBaseZones_Unknown11->container[sel] = &UnknownPointer->Unknown11;
	}

	RMSBaseZones_Unknown1->Enable(true);
	RMSBaseZones_Unknown1->Update();
	RMSBaseZones_BaseTerrain->Enable(true);
	RMSBaseZones_BaseTerrain->Update();
	RMSBaseZones_SpacingBetweenPlayers->Enable(true);
	RMSBaseZones_SpacingBetweenPlayers->Update();
	RMSBaseZones_Unknown4->Enable(true);
	RMSBaseZones_Unknown4->Update();
	for(short loop = 0; loop < RMSBaseZones_Unknown5.size(); ++loop)
	{
		RMSBaseZones_Unknown5[loop]->Enable(true);
		RMSBaseZones_Unknown5[loop]->Update();
	}
	RMSBaseZones_Unknown6->Enable(true);
	RMSBaseZones_Unknown6->Update();
	RMSBaseZones_Unknown7->Enable(true);
	RMSBaseZones_Unknown7->Update();
	for(short loop = 0; loop < RMSBaseZones_Unknown8.size(); ++loop)
	{
		RMSBaseZones_Unknown8[loop]->Enable(true);
		RMSBaseZones_Unknown8[loop]->Update();
	}
	RMSBaseZones_StartAreaRadius->Enable(true);
	RMSBaseZones_StartAreaRadius->Update();
	RMSBaseZones_Unknown10->Enable(true);
	RMSBaseZones_Unknown10->Update();
	RMSBaseZones_Unknown11->Enable(true);
	RMSBaseZones_Unknown11->Update();
}

void AGE_Frame::DisableRMSBaseZones()
{
	RMSBaseZones_Unknown1->Enable(false);
	RMSBaseZones_Unknown1->ChangeValue("0");
	RMSBaseZones_BaseTerrain->Enable(false);
	RMSBaseZones_BaseTerrain->ChangeValue("0");
	RMSBaseZones_SpacingBetweenPlayers->Enable(false);
	RMSBaseZones_SpacingBetweenPlayers->ChangeValue("0");
	RMSBaseZones_Unknown4->Enable(false);
	RMSBaseZones_Unknown4->ChangeValue("0");
	for(short loop = 0; loop < RMSBaseZones_Unknown5.size(); ++loop)
	{
		RMSBaseZones_Unknown5[loop]->Enable(false);
		RMSBaseZones_Unknown5[loop]->ChangeValue("0");
	}
	RMSBaseZones_Unknown6->Enable(false);
	RMSBaseZones_Unknown6->ChangeValue("0");
	RMSBaseZones_Unknown7->Enable(false);
	RMSBaseZones_Unknown7->ChangeValue("0");
	for(short loop = 0; loop < RMSBaseZones_Unknown8.size(); ++loop)
	{
		RMSBaseZones_Unknown8[loop]->Enable(false);
		RMSBaseZones_Unknown8[loop]->ChangeValue("0");
	}
	RMSBaseZones_StartAreaRadius->Enable(false);
	RMSBaseZones_StartAreaRadius->ChangeValue("0");
	RMSBaseZones_Unknown10->Enable(false);
	RMSBaseZones_Unknown10->ChangeValue("0");
	RMSBaseZones_Unknown11->Enable(false);
	RMSBaseZones_Unknown11->ChangeValue("0");
}

void AGE_Frame::OnRMSBaseZoneAdd(wxCommandEvent &Event)
{
	auto selections = Unknowns_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].BaseZoneCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones.size();
	ListRMSBaseZones();
}

void AGE_Frame::OnRMSBaseZoneInsert(wxCommandEvent &Event)
{
	auto selections = RMSBaseZones_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones, UnknownFSIDs[0]);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].BaseZoneCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones.size();
	ListRMSBaseZones();
}

void AGE_Frame::OnRMSBaseZoneDelete(wxCommandEvent &Event)
{
	auto selections = RMSBaseZones_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones, UnknownFSIDs);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].BaseZoneCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones.size();
	ListRMSBaseZones();
}

void AGE_Frame::OnRMSBaseZoneCopy(wxCommandEvent &Event)
{
	auto selections = RMSBaseZones_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones, UnknownFSIDs, copies->BaseZone);
	RMSBaseZones_Paste->Enable(true);
	RMSBaseZones_PasteInsert->Enable(true);
}

void AGE_Frame::OnRMSBaseZonePaste(wxCommandEvent &Event)
{
	auto selections = RMSBaseZones_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones, UnknownFSIDs, copies->BaseZone);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].BaseZoneCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones.size();
	ListRMSBaseZones();
}

void AGE_Frame::OnRMSBaseZonePasteInsert(wxCommandEvent &Event)
{
	auto selections = RMSBaseZones_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones, UnknownFSIDs[0], copies->BaseZone);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].BaseZoneCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones.size();
	ListRMSBaseZones();
}

void AGE_Frame::OnRMSBaseZoneCopyToMaps(wxCommandEvent &Event)
{
	for(short loop=1; loop < RandomMapIDs.size(); ++loop)
	{
		GenieFile->RandomMaps.Maps[RandomMapIDs[loop]].BaseZones = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones;
	}
}

void AGE_Frame::OnRMSTerrainSearch(wxCommandEvent &Event)
{
	ListRMSTerrains();
}

string AGE_Frame::GetRMSTerrainName(short Terrain)
{
	string Name = lexical_cast<string>(Terrain)+" ";
	if(GenieFile->TerrainBlock.Terrains.size() <= Terrain) return Name + "Nonexistent Terrain";
	if(!GenieFile->TerrainBlock.Terrains[Terrain].Name.empty())
	{
		return Name + GenieFile->TerrainBlock.Terrains[Terrain].Name;
	}
	return Name + "New Terrain";
}

void AGE_Frame::ListRMSTerrains()
{
	searchText = RMSTerrain_Search->GetValue().Lower();
	excludeText = RMSTerrain_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetRMSTerrainName(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains[loop].Terrain);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains[loop]);
		}
	}
	Listing(RMSTerrain_List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnRMSTerrainSelect(E);
}

void AGE_Frame::OnRMSTerrainSelect(wxCommandEvent &Event)
{
	auto selections = RMSTerrain_List->GetSelections(Items);
	if(selections < 1)
	{
		DisableRMSTerrains();
		return;
	}

	UnknownSSIDs.resize(selections);
	for(short loop = 0; loop < RMSTerrain_Unknown1.size(); ++loop)
	RMSTerrain_Unknown1[loop]->resize(selections);

	genie::MapTerrain * UnknownPointer;
	for(auto sel = selections; sel--> 0;)
	{
		UnknownPointer = (genie::MapTerrain*)RMSTerrain_List->GetClientData(Items.Item(sel));
		UnknownSSIDs[sel] = (UnknownPointer - (&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains[0]));

		RMSTerrain_Unknown1[0]->container[sel] = &UnknownPointer->Proportion;
		RMSTerrain_Unknown1[1]->container[sel] = &UnknownPointer->Terrain;
		RMSTerrain_Unknown1[2]->container[sel] = &UnknownPointer->NumberOfClumps;
		RMSTerrain_Unknown1[3]->container[sel] = &UnknownPointer->SpacingToOtherTerrains;
		RMSTerrain_Unknown1[4]->container[sel] = &UnknownPointer->PlacementZone;
		RMSTerrain_Unknown1[5]->container[sel] = &UnknownPointer->Unknown6;
	}

	for(short loop = 0; loop < RMSTerrain_Unknown1.size(); ++loop)
	{
		RMSTerrain_Unknown1[loop]->Enable(true);
	}
	RMSTerrain_Unknown1[0]->Update();
	RMSTerrain_Unknown1[1]->Update();
	RMSTerrain_Unknown1[2]->Update();
	RMSTerrain_Unknown1[3]->Update();
	RMSTerrain_Unknown1[4]->Update();
	RMSTerrain_Unknown1[5]->Update();
}

void AGE_Frame::DisableRMSTerrains()
{
	for(short loop = 0; loop < RMSTerrain_Unknown1.size(); ++loop)
	{
		RMSTerrain_Unknown1[loop]->Enable(false);
		RMSTerrain_Unknown1[loop]->ChangeValue("0");
	}
}

void AGE_Frame::OnRMSTerrainAdd(wxCommandEvent &Event)
{
	auto selections = Unknowns_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapTerrainCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainInsert(wxCommandEvent &Event)
{
	auto selections = RMSTerrain_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains, UnknownSSIDs[0]);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapTerrainCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainDelete(wxCommandEvent &Event)
{
	auto selections = RMSTerrain_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains, UnknownSSIDs);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapTerrainCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainCopy(wxCommandEvent &Event)
{
	auto selections = RMSTerrain_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains, UnknownSSIDs, copies->MapTerrain);
	RMSTerrain_Paste->Enable(true);
	RMSTerrain_PasteInsert->Enable(true);
}

void AGE_Frame::OnRMSTerrainPaste(wxCommandEvent &Event)
{
	auto selections = RMSTerrain_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains, UnknownSSIDs, copies->MapTerrain);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapTerrainCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainPasteInsert(wxCommandEvent &Event)
{
	auto selections = RMSTerrain_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains, UnknownSSIDs[0], copies->MapTerrain);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapTerrainCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainCopyToMaps(wxCommandEvent &Event)
{
	for(short loop=1; loop < RandomMapIDs.size(); ++loop)
	{
		GenieFile->RandomMaps.Maps[RandomMapIDs[loop]].MapTerrains = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains;
	}
}

void AGE_Frame::OnRMSUnitSearch(wxCommandEvent &Event)
{
	ListRMSUnits();
}

void AGE_Frame::ListRMSUnits()
{
	searchText = RMSUnit_Search->GetValue().Lower();
	excludeText = RMSUnit_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineUnitName(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits[loop].Unit);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits[loop]);
		}
	}
	Listing(RMSUnit_List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnRMSUnitSelect(E);
}

void AGE_Frame::OnRMSUnitSelect(wxCommandEvent &Event)
{
	auto selections = RMSUnit_List->GetSelections(Items);
	if(selections < 1)
	{
		DisableRMSUnits();
		return;
	}

	UnknownTSIDs.resize(selections);
	RMSUnit_Unit->resize(selections);
	RMSUnit_HostTerrain->resize(selections);
	for(short loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
	RMSUnit_Unknown3[loop]->resize(selections);
	RMSUnit_ObjectsPerPlayer->resize(selections);
	RMSUnit_Unknown5->resize(selections);
	RMSUnit_GroupsPerPlayer->resize(selections);
	RMSUnit_Unknown7->resize(selections);
	RMSUnit_OwnAtStart->resize(selections);
	RMSUnit_SetPlaceForAllPlayers->resize(selections);
	RMSUnit_MinDistanceToPlayers->resize(selections);
	RMSUnit_MaxDistanceToPlayers->resize(selections);

	genie::MapUnit * UnknownPointer;
	for(auto sel = selections; sel--> 0;)
	{
		UnknownPointer = (genie::MapUnit*)RMSUnit_List->GetClientData(Items.Item(sel));
		UnknownTSIDs[sel] = (UnknownPointer - (&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits[0]));

		RMSUnit_Unit->container[sel] = &UnknownPointer->Unit;
		RMSUnit_HostTerrain->container[sel] = &UnknownPointer->HostTerrain;
		for(short loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
		RMSUnit_Unknown3[loop]->container[sel] = &UnknownPointer->Unknown3[loop];
		RMSUnit_ObjectsPerPlayer->container[sel] = &UnknownPointer->ObjectsPerGroup;
		RMSUnit_Unknown5->container[sel] = &UnknownPointer->Fluctuation;
		RMSUnit_GroupsPerPlayer->container[sel] = &UnknownPointer->GroupsPerPlayer;
		RMSUnit_Unknown7->container[sel] = &UnknownPointer->GroupRadius;
		RMSUnit_OwnAtStart->container[sel] = &UnknownPointer->OwnAtStart;
		RMSUnit_SetPlaceForAllPlayers->container[sel] = &UnknownPointer->SetPlaceForAllPlayers;
		RMSUnit_MinDistanceToPlayers->container[sel] = &UnknownPointer->MinDistanceToPlayers;
		RMSUnit_MaxDistanceToPlayers->container[sel] = &UnknownPointer->MaxDistanceToPlayers;
	}

	RMSUnit_Unit->Enable(true);
	RMSUnit_Unit->Update();
	RMSUnit_HostTerrain->Enable(true);
	RMSUnit_HostTerrain->Update();
	for(short loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
	{
		RMSUnit_Unknown3[loop]->Enable(true);
		RMSUnit_Unknown3[loop]->Update();
	}
	RMSUnit_ObjectsPerPlayer->Enable(true);
	RMSUnit_ObjectsPerPlayer->Update();
	RMSUnit_Unknown5->Enable(true);
	RMSUnit_Unknown5->Update();
	RMSUnit_GroupsPerPlayer->Enable(true);
	RMSUnit_GroupsPerPlayer->Update();
	RMSUnit_Unknown7->Enable(true);
	RMSUnit_Unknown7->Update();
	RMSUnit_OwnAtStart->Enable(true);
	RMSUnit_OwnAtStart->Update();
	RMSUnit_SetPlaceForAllPlayers->Enable(true);
	RMSUnit_SetPlaceForAllPlayers->Update();
	RMSUnit_MinDistanceToPlayers->Enable(true);
	RMSUnit_MinDistanceToPlayers->Update();
	RMSUnit_MaxDistanceToPlayers->Enable(true);
	RMSUnit_MaxDistanceToPlayers->Update();
}

void AGE_Frame::DisableRMSUnits()
{
	RMSUnit_Unit->Enable(false);
	RMSUnit_Unit->ChangeValue("0");
	RMSUnit_HostTerrain->Enable(false);
	RMSUnit_HostTerrain->ChangeValue("0");
	for(short loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
	{
		RMSUnit_Unknown3[loop]->Enable(false);
		RMSUnit_Unknown3[loop]->ChangeValue("0");
	}
	RMSUnit_ObjectsPerPlayer->Enable(false);
	RMSUnit_ObjectsPerPlayer->ChangeValue("0");
	RMSUnit_Unknown5->Enable(false);
	RMSUnit_Unknown5->ChangeValue("0");
	RMSUnit_GroupsPerPlayer->Enable(false);
	RMSUnit_GroupsPerPlayer->ChangeValue("0");
	RMSUnit_Unknown7->Enable(false);
	RMSUnit_Unknown7->ChangeValue("0");
	RMSUnit_OwnAtStart->Enable(false);
	RMSUnit_OwnAtStart->ChangeValue("0");
	RMSUnit_SetPlaceForAllPlayers->Enable(false);
	RMSUnit_SetPlaceForAllPlayers->ChangeValue("0");
	RMSUnit_MinDistanceToPlayers->Enable(false);
	RMSUnit_MinDistanceToPlayers->ChangeValue("0");
	RMSUnit_MaxDistanceToPlayers->Enable(false);
	RMSUnit_MaxDistanceToPlayers->ChangeValue("0");
}

void AGE_Frame::OnRMSUnitAdd(wxCommandEvent &Event)
{
	auto selections = Unknowns_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnitCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitInsert(wxCommandEvent &Event)
{
	auto selections = RMSUnit_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits, UnknownTSIDs[0]);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnitCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitDelete(wxCommandEvent &Event)
{
	auto selections = RMSUnit_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits, UnknownTSIDs);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnitCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitCopy(wxCommandEvent &Event)
{
	auto selections = RMSUnit_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits, UnknownTSIDs, copies->MapUnit);
	RMSUnit_Paste->Enable(true);
	RMSUnit_PasteInsert->Enable(true);
}

void AGE_Frame::OnRMSUnitPaste(wxCommandEvent &Event)
{
	auto selections = RMSUnit_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits, UnknownTSIDs, copies->MapUnit);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnitCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitPasteInsert(wxCommandEvent &Event)
{
	auto selections = RMSUnit_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits, UnknownTSIDs[0], copies->MapUnit);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnitCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitCopyToMaps(wxCommandEvent &Event)
{
	for(short loop=1; loop < RandomMapIDs.size(); ++loop)
	{
		GenieFile->RandomMaps.Maps[RandomMapIDs[loop]].MapUnits = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits;
	}
}

void AGE_Frame::OnRMSUnknownSearch(wxCommandEvent &Event)
{
	ListRMSUnknowns();
}

string AGE_Frame::GetRMSUnknownName(short Terrain)
{
	string Name = lexical_cast<string>(Terrain)+" ";
	if(GenieFile->TerrainBlock.Terrains.size() <= Terrain) return Name + "Nonexistent Terrain";
	if(!GenieFile->TerrainBlock.Terrains[Terrain].Name.empty())
	{
		return Name + GenieFile->TerrainBlock.Terrains[Terrain].Name;
	}
	return Name + "New Terrain";
}

void AGE_Frame::ListRMSUnknowns()
{
	searchText = RMSUnknown_Search->GetValue().Lower();
	excludeText = RMSUnknown_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetRMSUnknownName(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns[loop].Unknown2);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns[loop]);
		}
	}
	Listing(RMSUnknown_List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnRMSUnknownSelect(E);
}

void AGE_Frame::OnRMSUnknownSelect(wxCommandEvent &Event)
{
	auto selections = RMSUnknown_List->GetSelections(Items);
	if(selections < 1)
	{
		DisableRMSUnknowns();
		return;
	}

	Unknown4SIDs.resize(selections);
	for(short loop = 0; loop < RMSUnknown_Unknown1.size(); ++loop)
	RMSUnknown_Unknown1[loop]->resize(selections);

	genie::MapUnknown * UnknownPointer;
	for(auto sel = selections; sel--> 0;)
	{
		UnknownPointer = (genie::MapUnknown*)RMSUnknown_List->GetClientData(Items.Item(sel));
		Unknown4SIDs[sel] = (UnknownPointer - (&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns[0]));

		RMSUnknown_Unknown1[0]->container[sel] = &UnknownPointer->Unknown1;
		RMSUnknown_Unknown1[1]->container[sel] = &UnknownPointer->Unknown2;
		RMSUnknown_Unknown1[2]->container[sel] = &UnknownPointer->Unknown3;
		RMSUnknown_Unknown1[3]->container[sel] = &UnknownPointer->Unknown4;
		RMSUnknown_Unknown1[4]->container[sel] = &UnknownPointer->Unknown5;
		RMSUnknown_Unknown1[5]->container[sel] = &UnknownPointer->Unknown6;
	}

	for(short loop = 0; loop < RMSUnknown_Unknown1.size(); ++loop)
	{
		RMSUnknown_Unknown1[loop]->Enable(true);
	}
	RMSUnknown_Unknown1[0]->Update();
	RMSUnknown_Unknown1[1]->Update();
	RMSUnknown_Unknown1[2]->Update();
	RMSUnknown_Unknown1[3]->Update();
	RMSUnknown_Unknown1[4]->Update();
	RMSUnknown_Unknown1[5]->Update();
}

void AGE_Frame::DisableRMSUnknowns()
{
	for(short loop = 0; loop < RMSUnknown_Unknown1.size(); ++loop)
	{
		RMSUnknown_Unknown1[loop]->Enable(false);
		RMSUnknown_Unknown1[loop]->ChangeValue("0");
	}
}

void AGE_Frame::OnRMSUnknownAdd(wxCommandEvent &Event)
{
	auto selections = Unknowns_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnknownCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns.size();
	ListRMSUnknowns();
}

void AGE_Frame::OnRMSUnknownInsert(wxCommandEvent &Event)
{
	auto selections = RMSUnknown_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns, Unknown4SIDs[0]);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnknownCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns.size();
	ListRMSUnknowns();
}

void AGE_Frame::OnRMSUnknownDelete(wxCommandEvent &Event)
{
	auto selections = RMSUnknown_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns, Unknown4SIDs);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnknownCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns.size();
	ListRMSUnknowns();
}

void AGE_Frame::OnRMSUnknownCopy(wxCommandEvent &Event)
{
	auto selections = RMSUnknown_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns, Unknown4SIDs, copies->MapUnknown);
	RMSUnknown_Paste->Enable(true);
	RMSUnknown_PasteInsert->Enable(true);
}

void AGE_Frame::OnRMSUnknownPaste(wxCommandEvent &Event)
{
	auto selections = RMSUnknown_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns, Unknown4SIDs, copies->MapUnknown);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnknownCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns.size();
	ListRMSUnknowns();
}

void AGE_Frame::OnRMSUnknownPasteInsert(wxCommandEvent &Event)
{
	auto selections = RMSUnknown_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns, Unknown4SIDs[0], copies->MapUnknown);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnknownCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns.size();
	ListRMSUnknowns();
}

void AGE_Frame::OnRMSUnknownCopyToMaps(wxCommandEvent &Event)
{
	for(short loop=1; loop < RandomMapIDs.size(); ++loop)
	{
		GenieFile->RandomMaps.Maps[RandomMapIDs[loop]].MapUnknowns = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnknowns;
	}
}

void AGE_Frame::CreateUnknownControls()
{
	Tab_Unknown = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Unknown_Main = new wxBoxSizer(wxHORIZONTAL);
	Unknown_Area = new wxBoxSizer(wxVERTICAL);
	Unknown_Scroller = new wxScrolledWindow(Tab_Unknown, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Unknown_ScrollArea = new wxBoxSizer(wxHORIZONTAL);
	Unknown_ScrollSpace = new wxBoxSizer(wxVERTICAL);

	Unknown_UnknownPointer_Grid = new wxGridSizer(8, 0, 0);
	Unknown_UnknownPointer_Holder = new wxBoxSizer(wxVERTICAL);
	Unknown_UnknownPointer_Text = new wxStaticText(Tab_Unknown, wxID_ANY, " Random Map Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknown_UnknownPointer = new TextCtrl_Long(Tab_Unknown);

	Unknowns = new wxStaticBoxSizer(wxHORIZONTAL, Tab_Unknown, "Random Map Scripts (Required in AoE/RoR)");
	Unknowns_ListArea = new wxBoxSizer(wxVERTICAL);
	Unknowns_Search = new wxTextCtrl(Tab_Unknown, wxID_ANY);
	Unknowns_Search_R = new wxTextCtrl(Tab_Unknown, wxID_ANY);
	Unknowns_List = new wxListBox(Tab_Unknown, wxID_ANY, wxDefaultPosition, wxSize(10, 220), 0, NULL, wxLB_EXTENDED);
	Unknowns_Buttons = new wxGridSizer(3, 0, 0);
	Unknowns_Add = new wxButton(Tab_Unknown, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Insert = new wxButton(Tab_Unknown, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Delete = new wxButton(Tab_Unknown, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Copy = new wxButton(Tab_Unknown, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Paste = new wxButton(Tab_Unknown, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Unknowns_PasteInsert = new wxButton(Tab_Unknown, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	Unknowns_Space_UnknownLevel = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_UnknownLevel_Holder = new wxBoxSizer(wxVERTICAL);
	Unknowns_UnknownLevel_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Script Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_UnknownLevel = new TextCtrl_Long(Unknown_Scroller);
	Unknowns_Unknown1_Grid = new wxGridSizer(5, 5, 5);
	for(short loop = 0; loop < Unknowns_Unknown1.size(); ++loop)
	{
		Unknowns_Unknown1_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		Unknowns_Unknown1[loop] = new TextCtrl_Long(Unknown_Scroller);
	}
	Unknowns_Unknown1_Text[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Southwest Border *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[0]->SetToolTip("Distance from the map edge allocated for non-base zone");
	Unknowns_Unknown1_Text[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Northwest Border *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[1]->SetToolTip("Distance from the map edge allocated for non-base zone");
	Unknowns_Unknown1_Text[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Northeast Border *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[2]->SetToolTip("Distance from the map edge allocated for non-base zone");
	Unknowns_Unknown1_Text[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Southeast Border *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[3]->SetToolTip("Distance from the map edge allocated for non-base zone");
	Unknowns_Unknown1_Text[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Border Usage % *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[4]->SetToolTip("% of border area covered with non-base terrain");
	Unknowns_Unknown1_Text[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Water Shape?", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1_Text[6] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Non-base Terrain *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[6]->SetToolTip("Used on the borders as well");
	Unknowns_Unknown1_Text[7] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Zone Cover % *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[7]->SetToolTip("Can be over 100");
	Unknowns_Unknown1_Text[8] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 9", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Space_Pointer1 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Pointer1_Holder = new wxBoxSizer(wxVERTICAL);
	Unknowns_Pointer1_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Zone Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Pointer1 = new TextCtrl_Long(Unknown_Scroller);

	RMSBaseZones = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Base Zone Data");
	RMSBaseZones_ListArea = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_DataArea = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSBaseZones_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSBaseZones_List = new wxListBox(Unknown_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	RMSBaseZones_Buttons = new wxGridSizer(3, 0, 0);
	RMSBaseZones_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	RMSBaseZones_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	RMSBaseZones_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	RMSBaseZones_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	RMSBaseZones_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	RMSBaseZones_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	RMSBaseZones_CopyToMaps = new wxButton(Unknown_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(5, 20));

	RMSBaseZones_Unknown1_Grid = new wxGridSizer(3, 5, 5);

	RMSBaseZones_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown1_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSBaseZones_Unknown1 = new TextCtrl_Long(Unknown_Scroller);
	RMSBaseZones_BaseTerrain_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_BaseTerrain_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSBaseZones_BaseTerrain = new TextCtrl_Long(Unknown_Scroller);
	RMSBaseZones_SpacingBetweenPlayers_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_SpacingBetweenPlayers_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Spacing Between Players *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSBaseZones_SpacingBetweenPlayers = new TextCtrl_Long(Unknown_Scroller);
	RMSBaseZones_SpacingBetweenPlayers->SetToolTip("Non-base terrain (like rivers) space between players\nIf too large, they won't be created");
	RMSBaseZones_Unknown4_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown4_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSBaseZones_Unknown4 = new TextCtrl_Long(Unknown_Scroller);

	RMSBaseZones_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown5_Grid = new wxGridSizer(4, 0, 0);
	RMSBaseZones_Unknown5_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Min Dist. Between Players *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < RMSBaseZones_Unknown5.size(); ++loop)
	RMSBaseZones_Unknown5[loop] = new TextCtrl_Byte(Unknown_Scroller);
	RMSBaseZones_Unknown5[1]->SetToolTip("Minimum distance in tiles between \"player initial zones\"");

	RMSBaseZones_Unknown6_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown6_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSBaseZones_Unknown6 = new TextCtrl_Long(Unknown_Scroller);
	RMSBaseZones_Unknown7_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown7_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSBaseZones_Unknown7 = new TextCtrl_Long(Unknown_Scroller);

	RMSBaseZones_Unknown8_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown8_Grid = new wxGridSizer(4, 0, 0);
	RMSBaseZones_Unknown8_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Zone Radius *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < RMSBaseZones_Unknown8.size(); ++loop)
	RMSBaseZones_Unknown8[loop] = new TextCtrl_Byte(Unknown_Scroller);
	RMSBaseZones_Unknown8[1]->SetToolTip("Base zone is created for every player");

	RMSBaseZones_StartAreaRadius_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_StartAreaRadius_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Players' Start Area Radius *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSBaseZones_StartAreaRadius = new TextCtrl_Long(Unknown_Scroller);
	RMSBaseZones_StartAreaRadius->SetToolTip("This area cannot contain different elevations or terrains\nUnknown 10 affects this too");
	RMSBaseZones_Unknown10_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown10_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 10 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSBaseZones_Unknown10 = new TextCtrl_Long(Unknown_Scroller);
	RMSBaseZones_Unknown10->SetToolTip("Has something to do with players' starting area");
	RMSBaseZones_Unknown11_Holder = new wxBoxSizer(wxVERTICAL);
	RMSBaseZones_Unknown11_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSBaseZones_Unknown11 = new TextCtrl_Long(Unknown_Scroller);

	Unknowns_Space_Pointer2 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Pointer2_Holder = new wxBoxSizer(wxVERTICAL);
	Unknowns_Pointer2_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Map Terrain Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Pointer2 = new TextCtrl_Long(Unknown_Scroller);

	RMSTerrain = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Terrains Placed on the Map");
	RMSTerrain_ListArea = new wxBoxSizer(wxVERTICAL);
	RMSTerrain_DataArea = new wxBoxSizer(wxVERTICAL);
	RMSTerrain_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSTerrain_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSTerrain_List = new wxListBox(Unknown_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	RMSTerrain_Buttons = new wxGridSizer(3, 0, 0);
	RMSTerrain_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_CopyToMaps = new wxButton(Unknown_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(5, 20));

	RMSTerrain_Unknown1_Grid = new wxGridSizer(3, 5, 5);
	for(short loop = 0; loop < RMSTerrain_Unknown1.size(); ++loop)
	{
		RMSTerrain_Unknown1_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		RMSTerrain_Unknown1[loop] = new TextCtrl_Long(Unknown_Scroller);
	}
	RMSTerrain_Unknown1_Text[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Proportion *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSTerrain_Unknown1[0]->SetToolTip("% of the total map area");
	RMSTerrain_Unknown1_Text[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSTerrain_Unknown1_Text[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Number of Clumps *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSTerrain_Unknown1[2]->SetToolTip("Clusters in the map");
	RMSTerrain_Unknown1_Text[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Spacing to Other Terrains *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSTerrain_Unknown1[3]->SetToolTip("Minimum distance to base terrain (or non-base terrain)");
	RMSTerrain_Unknown1_Text[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Placement Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSTerrain_Unknown1_Text[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

	Unknowns_Space_Pointer3 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Pointer3_Holder = new wxBoxSizer(wxVERTICAL);
	Unknowns_Pointer3_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Map Unit Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Pointer3 = new TextCtrl_Long(Unknown_Scroller);

	RMSUnit = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Units Placed on the Map (Some may appear anyway)");
	RMSUnit_ListArea = new wxBoxSizer(wxVERTICAL);
	RMSUnit_DataArea = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSUnit_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSUnit_List = new wxListBox(Unknown_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 250), 0, NULL, wxLB_EXTENDED);
	RMSUnit_Buttons = new wxGridSizer(3, 0, 0);
	RMSUnit_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_CopyToMaps = new wxButton(Unknown_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(5, 20));

	RMSUnit_Unknown1_Grid = new wxGridSizer(3, 5, 5);
	RMSUnit_Unit_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Unit_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Unit = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_HostTerrain_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_HostTerrain_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Placement Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_HostTerrain = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Unknown3_Grid = new wxGridSizer(4, 0, 0);
	RMSUnit_Unknown3_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Group Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
	RMSUnit_Unknown3[loop] = new TextCtrl_Byte(Unknown_Scroller);
	RMSUnit_Unknown3[0]->SetToolTip("0 Only 1 unit is placed from group\n1 & 2 All units are placed from group");
	RMSUnit_ObjectsPerPlayer_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_ObjectsPerPlayer_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Objects per Group", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_ObjectsPerPlayer = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Unknown5_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Fluctuation *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Unknown5 = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_Unknown5->SetToolTip("Max random variation in the number of objects in the group");
	RMSUnit_GroupsPerPlayer_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_GroupsPerPlayer_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Groups per Player", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_GroupsPerPlayer = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_Unknown7_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Unknown7_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Group Radius *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Unknown7 = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_Unknown7->SetToolTip("Max distance in tiles, for each object of the group, to the central location of the group");
	RMSUnit_OwnAtStart_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_OwnAtStart_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Own at Start (-1=Yes) *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_OwnAtStart = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_OwnAtStart->SetToolTip("Doesn't work if the unit isn't placed for all players");
	RMSUnit_SetPlaceForAllPlayers_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_SetPlaceForAllPlayers_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Set Place for All Players *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_SetPlaceForAllPlayers = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_SetPlaceForAllPlayers->SetToolTip("1 = Done once per player\n-1 = Done once, whatever the number of players is\n-2 = same as -1 ? Cannot find a difference");
	RMSUnit_MinDistanceToPlayers_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_MinDistanceToPlayers_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Min Distance to Players", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_MinDistanceToPlayers = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_MaxDistanceToPlayers_Holder = new wxBoxSizer(wxVERTICAL);
	RMSUnit_MaxDistanceToPlayers_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Max Distance to Players *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_MaxDistanceToPlayers = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_MaxDistanceToPlayers->SetToolTip("- Don't use 0 here for units that are own at start\n- 0 is OK for other units (gold/bushes/gazelle/etc)\n- You can use -1 as a wildcard for units that are own at start");

	Unknowns_Space_Pointer4 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Pointer4_Holder = new wxBoxSizer(wxVERTICAL);
	Unknowns_Pointer4_Text = new wxStaticText(Unknown_Scroller, wxID_ANY, " Map Unknown Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Pointer4 = new TextCtrl_Long(Unknown_Scroller);

	RMSUnknown = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Unknowns Placed on the Map");
	RMSUnknown_ListArea = new wxBoxSizer(wxVERTICAL);
	RMSUnknown_DataArea = new wxBoxSizer(wxVERTICAL);
	RMSUnknown_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSUnknown_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSUnknown_List = new wxListBox(Unknown_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	RMSUnknown_Buttons = new wxGridSizer(3, 0, 0);
	RMSUnknown_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	RMSUnknown_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	RMSUnknown_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	RMSUnknown_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	RMSUnknown_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	RMSUnknown_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	RMSUnknown_CopyToMaps = new wxButton(Unknown_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(5, 20));

	RMSUnknown_Unknown1_Grid = new wxGridSizer(3, 5, 5);
	for(short loop = 0; loop < RMSUnknown_Unknown1.size(); ++loop)
	{
		RMSUnknown_Unknown1_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		RMSUnknown_Unknown1[loop] = new TextCtrl_Long(Unknown_Scroller);
	}
	RMSUnknown_Unknown1_Text[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Proportion *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnknown_Unknown1[0]->SetToolTip("% of the total map area");
	RMSUnknown_Unknown1_Text[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnknown_Unknown1_Text[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Number of Clumps *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnknown_Unknown1[2]->SetToolTip("Clusters in the map");
	RMSUnknown_Unknown1_Text[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Spacing to Other Terrains *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnknown_Unknown1[3]->SetToolTip("Minimum distance to base terrain (or non-base terrain)");
	RMSUnknown_Unknown1_Text[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Placement Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnknown_Unknown1_Text[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

	Unknowns_Buttons->Add(Unknowns_Add, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Delete, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Insert, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Copy, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Paste, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_PasteInsert, 1, wxEXPAND);

	Unknowns_ListArea->Add(Unknowns_Search, 0, wxEXPAND);
	Unknowns_ListArea->Add(Unknowns_Search_R, 0, wxEXPAND);
	Unknowns_ListArea->Add(-1, 2);
	Unknowns_ListArea->Add(Unknowns_List, 1, wxEXPAND);
	Unknowns_ListArea->Add(-1, 2);
	Unknowns_ListArea->Add(Unknowns_Buttons, 0, wxEXPAND);

	Unknowns_UnknownLevel_Holder->Add(Unknowns_UnknownLevel_Text, 0, wxEXPAND);
	Unknowns_UnknownLevel_Holder->Add(Unknowns_UnknownLevel, 1, wxEXPAND);
	Unknowns_Space_UnknownLevel->Add(Unknowns_UnknownLevel_Holder, 1, wxEXPAND);
	Unknowns_Space_UnknownLevel->AddStretchSpacer(3);

	for(short loop = 0; loop < Unknowns_Unknown1.size(); ++loop)
	{
		Unknowns_Unknown1_Holder[loop]->Add(Unknowns_Unknown1_Text[loop], 0, wxEXPAND);
		Unknowns_Unknown1_Holder[loop]->Add(Unknowns_Unknown1[loop], 1, wxEXPAND);
		Unknowns_Unknown1_Grid->Add(Unknowns_Unknown1_Holder[loop], 1, wxEXPAND);
	}

	Unknowns_Pointer1_Holder->Add(Unknowns_Pointer1_Text, 0, wxEXPAND);
	Unknowns_Pointer1_Holder->Add(Unknowns_Pointer1, 1, wxEXPAND);
	Unknowns_Space_Pointer1->Add(Unknowns_Pointer1_Holder, 1, wxEXPAND);
	Unknowns_Space_Pointer1->AddStretchSpacer(3);

	RMSBaseZones_Buttons->Add(RMSBaseZones_Add, 1, wxEXPAND);
	RMSBaseZones_Buttons->Add(RMSBaseZones_Delete, 1, wxEXPAND);
	RMSBaseZones_Buttons->Add(RMSBaseZones_Insert, 1, wxEXPAND);
	RMSBaseZones_Buttons->Add(RMSBaseZones_Copy, 1, wxEXPAND);
	RMSBaseZones_Buttons->Add(RMSBaseZones_Paste, 1, wxEXPAND);
	RMSBaseZones_Buttons->Add(RMSBaseZones_PasteInsert, 1, wxEXPAND);

	RMSBaseZones_ListArea->Add(RMSBaseZones_Search, 0, wxEXPAND);
	RMSBaseZones_ListArea->Add(RMSBaseZones_Search_R, 0, wxEXPAND);
	RMSBaseZones_ListArea->Add(-1, 2);
	RMSBaseZones_ListArea->Add(RMSBaseZones_List, 1, wxEXPAND);
	RMSBaseZones_ListArea->Add(-1, 2);
	RMSBaseZones_ListArea->Add(RMSBaseZones_Buttons, 0, wxEXPAND);
	RMSBaseZones_ListArea->Add(-1, 2);
	RMSBaseZones_ListArea->Add(RMSBaseZones_CopyToMaps, 0, wxEXPAND);

	RMSBaseZones_Unknown1_Holder->Add(RMSBaseZones_Unknown1_Text, 0, wxEXPAND);
	RMSBaseZones_Unknown1_Holder->Add(RMSBaseZones_Unknown1, 1, wxEXPAND);
	RMSBaseZones_BaseTerrain_Holder->Add(RMSBaseZones_BaseTerrain_Text, 0, wxEXPAND);
	RMSBaseZones_BaseTerrain_Holder->Add(RMSBaseZones_BaseTerrain, 1, wxEXPAND);
	RMSBaseZones_SpacingBetweenPlayers_Holder->Add(RMSBaseZones_SpacingBetweenPlayers_Text, 0, wxEXPAND);
	RMSBaseZones_SpacingBetweenPlayers_Holder->Add(RMSBaseZones_SpacingBetweenPlayers, 1, wxEXPAND);
	RMSBaseZones_Unknown4_Holder->Add(RMSBaseZones_Unknown4_Text, 0, wxEXPAND);
	RMSBaseZones_Unknown4_Holder->Add(RMSBaseZones_Unknown4, 1, wxEXPAND);
	for(short loop = 0; loop < RMSBaseZones_Unknown5.size(); ++loop)
	RMSBaseZones_Unknown5_Grid->Add(RMSBaseZones_Unknown5[loop], 1, wxEXPAND);
	RMSBaseZones_Unknown5_Holder->Add(RMSBaseZones_Unknown5_Text, 0, wxEXPAND);
	RMSBaseZones_Unknown5_Holder->Add(RMSBaseZones_Unknown5_Grid, 1, wxEXPAND);
	RMSBaseZones_Unknown6_Holder->Add(RMSBaseZones_Unknown6_Text, 0, wxEXPAND);
	RMSBaseZones_Unknown6_Holder->Add(RMSBaseZones_Unknown6, 1, wxEXPAND);
	RMSBaseZones_Unknown7_Holder->Add(RMSBaseZones_Unknown7_Text, 0, wxEXPAND);
	RMSBaseZones_Unknown7_Holder->Add(RMSBaseZones_Unknown7, 1, wxEXPAND);
	for(short loop = 0; loop < RMSBaseZones_Unknown8.size(); ++loop)
	RMSBaseZones_Unknown8_Grid->Add(RMSBaseZones_Unknown8[loop], 1, wxEXPAND);
	RMSBaseZones_Unknown8_Holder->Add(RMSBaseZones_Unknown8_Text, 0, wxEXPAND);
	RMSBaseZones_Unknown8_Holder->Add(RMSBaseZones_Unknown8_Grid, 1, wxEXPAND);
	RMSBaseZones_StartAreaRadius_Holder->Add(RMSBaseZones_StartAreaRadius_Text, 0, wxEXPAND);
	RMSBaseZones_StartAreaRadius_Holder->Add(RMSBaseZones_StartAreaRadius, 1, wxEXPAND);
	RMSBaseZones_Unknown10_Holder->Add(RMSBaseZones_Unknown10_Text, 0, wxEXPAND);
	RMSBaseZones_Unknown10_Holder->Add(RMSBaseZones_Unknown10, 1, wxEXPAND);
	RMSBaseZones_Unknown11_Holder->Add(RMSBaseZones_Unknown11_Text, 0, wxEXPAND);
	RMSBaseZones_Unknown11_Holder->Add(RMSBaseZones_Unknown11, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown1_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_BaseTerrain_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_SpacingBetweenPlayers_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown4_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown5_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown6_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown7_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown8_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_StartAreaRadius_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown10_Holder, 1, wxEXPAND);
	RMSBaseZones_Unknown1_Grid->Add(RMSBaseZones_Unknown11_Holder, 1, wxEXPAND);
	RMSBaseZones_DataArea->Add(RMSBaseZones_Unknown1_Grid, 0, wxEXPAND);

	RMSBaseZones->Add(RMSBaseZones_ListArea, 1, wxEXPAND);
	RMSBaseZones->Add(10, -1);
	RMSBaseZones->Add(RMSBaseZones_DataArea, 3, wxEXPAND);

	Unknowns_Pointer2_Holder->Add(Unknowns_Pointer2_Text, 0, wxEXPAND);
	Unknowns_Pointer2_Holder->Add(Unknowns_Pointer2, 1, wxEXPAND);
	Unknowns_Space_Pointer2->Add(Unknowns_Pointer2_Holder, 1, wxEXPAND);
	Unknowns_Space_Pointer2->AddStretchSpacer(3);

	RMSTerrain_Buttons->Add(RMSTerrain_Add, 1, wxEXPAND);
	RMSTerrain_Buttons->Add(RMSTerrain_Delete, 1, wxEXPAND);
	RMSTerrain_Buttons->Add(RMSTerrain_Insert, 1, wxEXPAND);
	RMSTerrain_Buttons->Add(RMSTerrain_Copy, 1, wxEXPAND);
	RMSTerrain_Buttons->Add(RMSTerrain_Paste, 1, wxEXPAND);
	RMSTerrain_Buttons->Add(RMSTerrain_PasteInsert, 1, wxEXPAND);

	RMSTerrain_ListArea->Add(RMSTerrain_Search, 0, wxEXPAND);
	RMSTerrain_ListArea->Add(RMSTerrain_Search_R, 0, wxEXPAND);
	RMSTerrain_ListArea->Add(-1, 2);
	RMSTerrain_ListArea->Add(RMSTerrain_List, 1, wxEXPAND);
	RMSTerrain_ListArea->Add(-1, 2);
	RMSTerrain_ListArea->Add(RMSTerrain_Buttons, 0, wxEXPAND);
	RMSTerrain_ListArea->Add(-1, 2);
	RMSTerrain_ListArea->Add(RMSTerrain_CopyToMaps, 0, wxEXPAND);

	for(short loop = 0; loop < RMSTerrain_Unknown1.size(); ++loop)
	{
		RMSTerrain_Unknown1_Holder[loop]->Add(RMSTerrain_Unknown1_Text[loop], 0, wxEXPAND);
		RMSTerrain_Unknown1_Holder[loop]->Add(RMSTerrain_Unknown1[loop], 1, wxEXPAND);
		RMSTerrain_Unknown1_Grid->Add(RMSTerrain_Unknown1_Holder[loop], 1, wxEXPAND);
	}
	RMSTerrain_DataArea->Add(RMSTerrain_Unknown1_Grid, 0, wxEXPAND);

	RMSTerrain->Add(RMSTerrain_ListArea, 1, wxEXPAND);
	RMSTerrain->Add(10, -1);
	RMSTerrain->Add(RMSTerrain_DataArea, 3, wxEXPAND);

	Unknowns_Pointer3_Holder->Add(Unknowns_Pointer3_Text, 0, wxEXPAND);
	Unknowns_Pointer3_Holder->Add(Unknowns_Pointer3, 1, wxEXPAND);
	Unknowns_Space_Pointer3->Add(Unknowns_Pointer3_Holder, 1, wxEXPAND);
	Unknowns_Space_Pointer3->AddStretchSpacer(3);

	RMSUnit_Buttons->Add(RMSUnit_Add, 1, wxEXPAND);
	RMSUnit_Buttons->Add(RMSUnit_Delete, 1, wxEXPAND);
	RMSUnit_Buttons->Add(RMSUnit_Insert, 1, wxEXPAND);
	RMSUnit_Buttons->Add(RMSUnit_Copy, 1, wxEXPAND);
	RMSUnit_Buttons->Add(RMSUnit_Paste, 1, wxEXPAND);
	RMSUnit_Buttons->Add(RMSUnit_PasteInsert, 1, wxEXPAND);

	RMSUnit_ListArea->Add(RMSUnit_Search, 0, wxEXPAND);
	RMSUnit_ListArea->Add(RMSUnit_Search_R, 0, wxEXPAND);
	RMSUnit_ListArea->Add(-1, 2);
	RMSUnit_ListArea->Add(RMSUnit_List, 1, wxEXPAND);
	RMSUnit_ListArea->Add(-1, 2);
	RMSUnit_ListArea->Add(RMSUnit_Buttons, 0, wxEXPAND);
	RMSUnit_ListArea->Add(-1, 2);
	RMSUnit_ListArea->Add(RMSUnit_CopyToMaps, 0, wxEXPAND);

	RMSUnit_Unit_Holder->Add(RMSUnit_Unit_Text, 0, wxEXPAND);
	RMSUnit_Unit_Holder->Add(RMSUnit_Unit, 1, wxEXPAND);
	RMSUnit_HostTerrain_Holder->Add(RMSUnit_HostTerrain_Text, 0, wxEXPAND);
	RMSUnit_HostTerrain_Holder->Add(RMSUnit_HostTerrain, 1, wxEXPAND);
	for(short loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
	RMSUnit_Unknown3_Grid->Add(RMSUnit_Unknown3[loop], 1, wxEXPAND);
	RMSUnit_Unknown3_Holder->Add(RMSUnit_Unknown3_Text, 0, wxEXPAND);
	RMSUnit_Unknown3_Holder->Add(RMSUnit_Unknown3_Grid, 1, wxEXPAND);
	RMSUnit_ObjectsPerPlayer_Holder->Add(RMSUnit_ObjectsPerPlayer_Text, 0, wxEXPAND);
	RMSUnit_ObjectsPerPlayer_Holder->Add(RMSUnit_ObjectsPerPlayer, 1, wxEXPAND);
	RMSUnit_Unknown5_Holder->Add(RMSUnit_Unknown5_Text, 0, wxEXPAND);
	RMSUnit_Unknown5_Holder->Add(RMSUnit_Unknown5, 1, wxEXPAND);
	RMSUnit_GroupsPerPlayer_Holder->Add(RMSUnit_GroupsPerPlayer_Text, 0, wxEXPAND);
	RMSUnit_GroupsPerPlayer_Holder->Add(RMSUnit_GroupsPerPlayer, 1, wxEXPAND);
	RMSUnit_Unknown7_Holder->Add(RMSUnit_Unknown7_Text, 0, wxEXPAND);
	RMSUnit_Unknown7_Holder->Add(RMSUnit_Unknown7, 1, wxEXPAND);
	RMSUnit_OwnAtStart_Holder->Add(RMSUnit_OwnAtStart_Text, 0, wxEXPAND);
	RMSUnit_OwnAtStart_Holder->Add(RMSUnit_OwnAtStart, 1, wxEXPAND);
	RMSUnit_SetPlaceForAllPlayers_Holder->Add(RMSUnit_SetPlaceForAllPlayers_Text, 0, wxEXPAND);
	RMSUnit_SetPlaceForAllPlayers_Holder->Add(RMSUnit_SetPlaceForAllPlayers, 1, wxEXPAND);
	RMSUnit_MinDistanceToPlayers_Holder->Add(RMSUnit_MinDistanceToPlayers_Text, 0, wxEXPAND);
	RMSUnit_MinDistanceToPlayers_Holder->Add(RMSUnit_MinDistanceToPlayers, 1, wxEXPAND);
	RMSUnit_MaxDistanceToPlayers_Holder->Add(RMSUnit_MaxDistanceToPlayers_Text, 0, wxEXPAND);
	RMSUnit_MaxDistanceToPlayers_Holder->Add(RMSUnit_MaxDistanceToPlayers, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_Unit_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_HostTerrain_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_Unknown3_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_ObjectsPerPlayer_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_Unknown5_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_GroupsPerPlayer_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_Unknown7_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_OwnAtStart_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_SetPlaceForAllPlayers_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_MinDistanceToPlayers_Holder, 1, wxEXPAND);
	RMSUnit_Unknown1_Grid->Add(RMSUnit_MaxDistanceToPlayers_Holder, 1, wxEXPAND);
	RMSUnit_DataArea->Add(RMSUnit_Unknown1_Grid, 0, wxEXPAND);

	RMSUnit->Add(RMSUnit_ListArea, 1, wxEXPAND);
	RMSUnit->Add(10, -1);
	RMSUnit->Add(RMSUnit_DataArea, 3, wxEXPAND);

	Unknowns_Pointer4_Holder->Add(Unknowns_Pointer4_Text, 0, wxEXPAND);
	Unknowns_Pointer4_Holder->Add(Unknowns_Pointer4, 1, wxEXPAND);
	Unknowns_Space_Pointer4->Add(Unknowns_Pointer4_Holder, 1, wxEXPAND);
	Unknowns_Space_Pointer4->AddStretchSpacer(3);

	RMSUnknown_Buttons->Add(RMSUnknown_Add, 1, wxEXPAND);
	RMSUnknown_Buttons->Add(RMSUnknown_Delete, 1, wxEXPAND);
	RMSUnknown_Buttons->Add(RMSUnknown_Insert, 1, wxEXPAND);
	RMSUnknown_Buttons->Add(RMSUnknown_Copy, 1, wxEXPAND);
	RMSUnknown_Buttons->Add(RMSUnknown_Paste, 1, wxEXPAND);
	RMSUnknown_Buttons->Add(RMSUnknown_PasteInsert, 1, wxEXPAND);

	RMSUnknown_ListArea->Add(RMSUnknown_Search, 0, wxEXPAND);
	RMSUnknown_ListArea->Add(RMSUnknown_Search_R, 0, wxEXPAND);
	RMSUnknown_ListArea->Add(-1, 2);
	RMSUnknown_ListArea->Add(RMSUnknown_List, 1, wxEXPAND);
	RMSUnknown_ListArea->Add(-1, 2);
	RMSUnknown_ListArea->Add(RMSUnknown_Buttons, 0, wxEXPAND);
	RMSUnknown_ListArea->Add(-1, 2);
	RMSUnknown_ListArea->Add(RMSUnknown_CopyToMaps, 0, wxEXPAND);

	for(short loop = 0; loop < RMSUnknown_Unknown1.size(); ++loop)
	{
		RMSUnknown_Unknown1_Holder[loop]->Add(RMSUnknown_Unknown1_Text[loop], 0, wxEXPAND);
		RMSUnknown_Unknown1_Holder[loop]->Add(RMSUnknown_Unknown1[loop], 1, wxEXPAND);
		RMSUnknown_Unknown1_Grid->Add(RMSUnknown_Unknown1_Holder[loop], 1, wxEXPAND);
	}
	RMSUnknown_DataArea->Add(RMSUnknown_Unknown1_Grid, 0, wxEXPAND);

	RMSUnknown->Add(RMSUnknown_ListArea, 1, wxEXPAND);
	RMSUnknown->Add(10, -1);
	RMSUnknown->Add(RMSUnknown_DataArea, 3, wxEXPAND);

	Unknown_ScrollSpace->Add(Unknowns_Space_UnknownLevel, 0, wxEXPAND);
	Unknown_ScrollSpace->Add(-1, 5);
	Unknown_ScrollSpace->Add(Unknowns_Unknown1_Grid, 0, wxEXPAND);
	Unknown_ScrollSpace->Add(-1, 5);
	Unknown_ScrollSpace->Add(Unknowns_Space_Pointer1, 0, wxEXPAND);
	Unknown_ScrollSpace->Add(-1, 5);
	Unknown_ScrollSpace->Add(RMSBaseZones, 0, wxEXPAND);
	Unknown_ScrollSpace->Add(-1, 5);
	Unknown_ScrollSpace->Add(Unknowns_Space_Pointer2, 0, wxEXPAND);
	Unknown_ScrollSpace->Add(-1, 5);
	Unknown_ScrollSpace->Add(RMSTerrain, 0, wxEXPAND);
	Unknown_ScrollSpace->Add(-1, 5);
	Unknown_ScrollSpace->Add(Unknowns_Space_Pointer3, 0, wxEXPAND);
	Unknown_ScrollSpace->Add(-1, 5);
	Unknown_ScrollSpace->Add(RMSUnit, 0, wxEXPAND);
	Unknown_ScrollSpace->Add(-1, 5);
	Unknown_ScrollSpace->Add(Unknowns_Space_Pointer4, 0, wxEXPAND);
	Unknown_ScrollSpace->Add(-1, 5);
	Unknown_ScrollSpace->Add(RMSUnknown, 0, wxEXPAND);

	Unknown_ScrollArea->Add(Unknown_ScrollSpace, 1, wxEXPAND);
	Unknown_ScrollArea->Add(5, -1);

	Unknown_Scroller->SetSizer(Unknown_ScrollArea);
	Unknown_Scroller->SetScrollRate(0, 15);

	Unknowns->Add(Unknowns_ListArea, 1, wxEXPAND);
	Unknowns->Add(10, -1);
	Unknowns->Add(Unknown_Scroller, 3, wxEXPAND);

	Unknown_UnknownPointer_Holder->Add(Unknown_UnknownPointer_Text, 0, wxEXPAND);
	Unknown_UnknownPointer_Holder->Add(Unknown_UnknownPointer, 0, wxEXPAND);
	Unknown_UnknownPointer_Grid->Add(Unknown_UnknownPointer_Holder, 1, wxEXPAND);

	Unknown_Area->Add(-1, 10);
	Unknown_Area->Add(Unknown_UnknownPointer_Grid, 0, wxEXPAND);
	Unknown_Area->Add(-1, 10);
	Unknown_Area->Add(Unknowns, 1, wxEXPAND);
	Unknown_Area->Add(-1, 10);

	Unknown_Main->Add(10, -1);
	Unknown_Main->Add(Unknown_Area, 1, wxEXPAND);
	Unknown_Main->Add(10, -1);

	Unknowns_Paste->Enable(false);
	Unknowns_PasteInsert->Enable(false);
	RMSBaseZones_Paste->Enable(false);
	RMSBaseZones_PasteInsert->Enable(false);
	RMSTerrain_Paste->Enable(false);
	RMSTerrain_PasteInsert->Enable(false);
	RMSUnit_Paste->Enable(false);
	RMSUnit_PasteInsert->Enable(false);
	RMSUnknown_Paste->Enable(false);
	RMSUnknown_PasteInsert->Enable(false);

	Tab_Unknown->SetSizer(Unknown_Main);

	Connect(Unknowns_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnknownsSearch));
	Connect(Unknowns_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnknownsSearch));
	Connect(Unknowns_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnknownsSelect));
	Connect(Unknowns_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownsAdd));
	Connect(Unknowns_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownsInsert));
	Connect(Unknowns_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownsDelete));
	Connect(Unknowns_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownsCopy));
	Connect(Unknowns_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownsPaste));
	Connect(Unknowns_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownsPasteInsert));
	Connect(RMSBaseZones_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneSearch));
	Connect(RMSBaseZones_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneSearch));
	Connect(RMSBaseZones_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneSelect));
	Connect(RMSBaseZones_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneAdd));
	Connect(RMSBaseZones_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneInsert));
	Connect(RMSBaseZones_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneDelete));
	Connect(RMSBaseZones_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneCopy));
	Connect(RMSBaseZones_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZonePaste));
	Connect(RMSBaseZones_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZonePasteInsert));
	Connect(RMSBaseZones_CopyToMaps->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSBaseZoneCopyToMaps));
	Connect(RMSTerrain_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainSearch));
	Connect(RMSTerrain_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainSearch));
	Connect(RMSTerrain_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainSelect));
	Connect(RMSTerrain_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainAdd));
	Connect(RMSTerrain_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainInsert));
	Connect(RMSTerrain_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainDelete));
	Connect(RMSTerrain_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainCopy));
	Connect(RMSTerrain_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainPaste));
	Connect(RMSTerrain_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainPasteInsert));
	Connect(RMSTerrain_CopyToMaps->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainCopyToMaps));
	Connect(RMSUnit_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSUnitSearch));
	Connect(RMSUnit_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSUnitSearch));
	Connect(RMSUnit_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnRMSUnitSelect));
	Connect(RMSUnit_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitAdd));
	Connect(RMSUnit_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitInsert));
	Connect(RMSUnit_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitDelete));
	Connect(RMSUnit_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitCopy));
	Connect(RMSUnit_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitPaste));
	Connect(RMSUnit_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitPasteInsert));
	Connect(RMSUnit_CopyToMaps->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitCopyToMaps));
	Connect(RMSUnknown_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownSearch));
	Connect(RMSUnknown_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownSearch));
	Connect(RMSUnknown_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownSelect));
	Connect(RMSUnknown_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownAdd));
	Connect(RMSUnknown_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownInsert));
	Connect(RMSUnknown_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownDelete));
	Connect(RMSUnknown_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownCopy));
	Connect(RMSUnknown_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownPaste));
	Connect(RMSUnknown_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownPasteInsert));
	Connect(RMSUnknown_CopyToMaps->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnknownCopyToMaps));

	Unknowns_UnknownLevel->Connect(Unknowns_UnknownLevel->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	RMSBaseZones_Unknown1->Connect(RMSBaseZones_Unknown1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	RMSTerrain_Unknown1[1]->Connect(RMSTerrain_Unknown1[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	RMSUnknown_Unknown1[1]->Connect(RMSUnknown_Unknown1[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	RMSUnit_Unit->Connect(RMSUnit_Unit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
}

void AGE_Frame::OnKillFocus_Unknown(wxFocusEvent &Event)
{
	if(((AGETextCtrl*)Event.GetEventObject())->SaveEdits() != 0) return;
	if(Event.GetId() == Unknowns_UnknownLevel->GetId())
	{
		ListRandomMaps();
	}
	else if(Event.GetId() == RMSBaseZones_Unknown1->GetId())
	{
		ListRMSBaseZones();
	}
	else if(Event.GetId() == RMSTerrain_Unknown1[1]->GetId())
	{
		ListRMSTerrains();
	}
	else if(Event.GetId() == RMSUnit_Unit->GetId())
	{
		ListRMSUnits();
	}
	else if(Event.GetId() == RMSUnknown_Unknown1[1]->GetId())
	{
		ListRMSUnknowns();
	}
	Event.Skip();
}
