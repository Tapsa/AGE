#include "../AGE_Frame.h"
using boost::lexical_cast;

void AGE_Frame::ListGeneral()
{
	//General_SomethingSize->SetLabel("Size: "+lexical_cast<string>(SomethingSize));
	//General_SomethingPicker->ChangeValue(lexical_cast<string>(SomethingPage));

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
		General_TerrainHeader[loop]->ChangeValue(lexical_cast<string>(GenieFile->GraphicsRendering[loop]));
		General_TerrainHeader[loop]->resize(1);
		General_TerrainHeader[loop]->container[0] = &GenieFile->GraphicsRendering[loop];
	}
	for(short loop = 0; loop < GenieFile->ZeroSpace.size(); ++loop)
	{
		General_AfterBorders[loop]->ChangeValue(lexical_cast<string>(GenieFile->ZeroSpace[loop]));
		General_AfterBorders[loop]->resize(1);
		General_AfterBorders[loop]->container[0] = &GenieFile->ZeroSpace[loop];
	}
	for(short loop = 0; loop < GenieFile->Rendering.size(); ++loop)
	{
		General_TerrainRendering[loop]->ChangeValue(lexical_cast<string>(GenieFile->Rendering[loop]));
		General_TerrainRendering[loop]->resize(1);
		General_TerrainRendering[loop]->container[0] = &GenieFile->Rendering[loop];
	}
	for(short loop = 0; loop < GenieFile->Something.size(); ++loop)
	{
		General_Something[loop]->ChangeValue(lexical_cast<string>(GenieFile->Something[loop]));
		General_Something[loop]->resize(1);
		General_Something[loop]->container[0] = &GenieFile->Something[loop];
	}
	Unknown_UnknownPointer->ChangeValue(lexical_cast<string>(GenieFile->RandomMaps.RandomMapPointer));
	Unknown_UnknownPointer->resize(1);
	Unknown_UnknownPointer->container[0] = &GenieFile->RandomMaps.RandomMapPointer;
	if(GenieVersion <= genie::GV_RoR) return;
	for(long loop = 0;loop < General_TTUnknown.size(); ++loop)
	{
		General_TTUnknown[loop]->ChangeValue(lexical_cast<string>(GenieFile->UnknownPreTechTree[loop]));
		General_TTUnknown[loop]->resize(1);
		General_TTUnknown[loop]->container[0] = &GenieFile->UnknownPreTechTree[loop];
	}
	General_TTUnknown[7]->ChangeValue(lexical_cast<string>(GenieFile->TechTree.Unknown2));
	General_TTUnknown[7]->resize(1);
	General_TTUnknown[7]->container[0] = &GenieFile->TechTree.Unknown2;
	if(GenieVersion <= genie::GV_TC) return;
	General_SUnknown2->ChangeValue(lexical_cast<string>(GenieFile->SUnknown2));
	General_SUnknown2->resize(1);
	General_SUnknown2->container[0] = &GenieFile->SUnknown2;
	General_SUnknown3->ChangeValue(lexical_cast<string>(GenieFile->SUnknown3));
	General_SUnknown3->resize(1);
	General_SUnknown3->container[0] = &GenieFile->SUnknown3;
	General_SUnknown4->ChangeValue(lexical_cast<string>(GenieFile->SUnknown4));
	General_SUnknown4->resize(1);
	General_SUnknown4->container[0] = &GenieFile->SUnknown4;
	General_SUnknown5->ChangeValue(lexical_cast<string>(GenieFile->SUnknown5));
	General_SUnknown5->resize(1);
	General_SUnknown5->container[0] = &GenieFile->SUnknown5;
	General_SUnknown7->ChangeValue(lexical_cast<string>((short)GenieFile->SUnknown7));
	General_SUnknown7->resize(1);
	General_SUnknown7->container[0] = &GenieFile->SUnknown7;
	General_SUnknown8->ChangeValue(lexical_cast<string>((short)GenieFile->SUnknown8));
	General_SUnknown8->resize(1);
	General_SUnknown8->container[0] = &GenieFile->SUnknown8;
}

void AGE_Frame::CreateGeneralControls()
{
	Tab_General = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	General_Main = new wxBoxSizer(wxVERTICAL);
	General_TopRow = new wxBoxSizer(wxHORIZONTAL);
	General_Refresh = new wxButton(Tab_General, wxID_ANY, "Refresh", wxDefaultPosition, wxSize(0, 20));
	General_Text_CalcBoxes = new wxStaticText(Tab_General, wxID_ANY, " Variable Converter *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Text_CalcBoxes->SetToolTip("From four 8 bit integers to one 32 bit integer or vice versa");
	General_Text_CalcBoxesMiddle = new wxStaticText(Tab_General, wxID_ANY, " = ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 5; ++loop)
	General_CalcBoxes[loop] = new wxTextCtrl(Tab_General, wxID_ANY);
	General_Scroller = new wxScrolledWindow(Tab_General, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	General_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	General_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);

	const wxString SWUNKNOWNSINFO = "Unknowns 2 to 5 are in the beginning of the file,\nright after civilization count (first of the two) and\nbefore terrain restrictions";
	General_Grid_Variables = new wxGridSizer(6, 5, 5);
	General_Holder_Variables1 = new wxStaticBoxSizer(wxVERTICAL, General_Scroller, "Star Wars Unknowns");
	General_Holder_SUnknown2 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown2 = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 2 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown2 = new TextCtrl_Long(General_Scroller);
	General_SUnknown2->SetToolTip(SWUNKNOWNSINFO);
	General_Holder_SUnknown3 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown3 = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 3 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown3 = new TextCtrl_Long(General_Scroller);
	General_SUnknown3->SetToolTip(SWUNKNOWNSINFO);
	General_Holder_SUnknown4 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown4 = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 4 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown4 = new TextCtrl_Long(General_Scroller);
	General_SUnknown4->SetToolTip(SWUNKNOWNSINFO);
	General_Holder_SUnknown5 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown5 = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 5 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown5 = new TextCtrl_Long(General_Scroller);
	General_SUnknown5->SetToolTip(SWUNKNOWNSINFO);
	General_Holder_SUnknown7 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown7 = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 7 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown7 = new TextCtrl_Byte(General_Scroller);
	General_SUnknown7->SetToolTip("In the file this is\nright after civilizations and\nbefore researches");
	General_Holder_SUnknown8 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown8 = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 8 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown8 = new TextCtrl_Byte(General_Scroller);
	General_SUnknown8->SetToolTip("In the file this is\nright after researches and\nbefore technology trees");
	General_Holder_TerrainHeader = new wxBoxSizer(wxVERTICAL);
	General_Text_TerrainHeader = new wxStaticText(General_Scroller, wxID_ANY, " Graphics-related", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Grid_TerrainHeader = new wxGridSizer(16, 0, 0);
	General_Holder_BorderRelated = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderRelated = new wxStaticText(General_Scroller, wxID_ANY, " Borders-related", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Grid_BorderRelated = new wxGridSizer(8, 0, 0);
	General_Holder_TerrainRendering = new wxBoxSizer(wxVERTICAL);
	General_Text_TerrainRendering = new wxStaticText(General_Scroller, wxID_ANY, " Graphics-related", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Grid_TerrainRendering = new wxGridSizer(16, 0, 0);
	General_Grid_Something = new wxGridSizer(8, 0, 0);
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
/*	General_Holder_RenderPlusUnknown = new wxBoxSizer(wxVERTICAL);
	General_Holder_RenderPlusUnknownTop = new wxBoxSizer(wxHORIZONTAL);
	General_SomethingPicker = new wxTextCtrl(General_Scroller, wxID_ANY);
	General_SomethingNext = new wxButton(General_Scroller, wxID_ANY, "Next", wxDefaultPosition, wxSize(0, 20));
	General_SomethingPrev = new wxButton(General_Scroller, wxID_ANY, "Previous", wxDefaultPosition, wxSize(0, 20));
	General_SomethingSize = new wxStaticText(General_Scroller, wxID_ANY, " Data Size", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Text_TechTree = new wxStaticText(General_Scroller, wxID_ANY, " Unknown Data with 32 Bit Pointers", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
*/
	General_TopRow->Add(10, -1);
	General_TopRow->Add(General_Refresh, 2, wxEXPAND);
	General_TopRow->AddStretchSpacer(3);
	for(short loop = 0; loop < 4; ++loop)
	General_TopRow->Add(General_CalcBoxes[loop], 1, wxEXPAND);
	General_TopRow->Add(General_Text_CalcBoxesMiddle, 0, wxEXPAND);
	General_TopRow->Add(General_CalcBoxes[4], 1, wxEXPAND);
	General_TopRow->Add(General_Text_CalcBoxes, 0, wxEXPAND);
	General_TopRow->AddStretchSpacer(1);

	for(short loop = 0; loop < General_TerrainHeader.size(); ++loop)
	General_Grid_TerrainHeader->Add(General_TerrainHeader[loop], 1, wxEXPAND);
	General_Holder_TerrainHeader->Add(General_Text_TerrainHeader, 0, wxEXPAND);
	General_Holder_TerrainHeader->Add(General_Grid_TerrainHeader, 0, wxEXPAND);

	for(short loop = 0; loop < General_AfterBorders.size(); ++loop)
	General_Grid_BorderRelated->Add(General_AfterBorders[loop], 1, wxEXPAND);
	General_Holder_BorderRelated->Add(General_Text_BorderRelated, 0, wxEXPAND);
	General_Holder_BorderRelated->Add(General_Grid_BorderRelated, 0, wxEXPAND);

	for(short loop = 0; loop < General_TerrainRendering.size(); ++loop)
	General_Grid_TerrainRendering->Add(General_TerrainRendering[loop], 1, wxEXPAND);
	for(short loop = 0; loop < General_Something.size(); ++loop)
	General_Grid_Something->Add(General_Something[loop], 1, wxEXPAND);
	General_Holder_TerrainRendering->Add(General_Text_TerrainRendering, 0, wxEXPAND);
	General_Holder_TerrainRendering->Add(General_Grid_TerrainRendering, 0, wxEXPAND);
	General_Holder_TerrainRendering->Add(General_Grid_Something, 0, wxEXPAND);

	General_Holder_SUnknown7->Add(General_Text_SUnknown7, 0, wxEXPAND);
	General_Holder_SUnknown7->Add(General_SUnknown7, 1, wxEXPAND);
	General_Holder_SUnknown8->Add(General_Text_SUnknown8, 0, wxEXPAND);
	General_Holder_SUnknown8->Add(General_SUnknown8, 1, wxEXPAND);
	General_Holder_SUnknown2->Add(General_Text_SUnknown2, 0, wxEXPAND);
	General_Holder_SUnknown2->Add(General_SUnknown2, 1, wxEXPAND);
	General_Holder_SUnknown3->Add(General_Text_SUnknown3, 0, wxEXPAND);
	General_Holder_SUnknown3->Add(General_SUnknown3, 1, wxEXPAND);
	General_Holder_SUnknown4->Add(General_Text_SUnknown4, 0, wxEXPAND);
	General_Holder_SUnknown4->Add(General_SUnknown4, 1, wxEXPAND);
	General_Holder_SUnknown5->Add(General_Text_SUnknown5, 0, wxEXPAND);
	General_Holder_SUnknown5->Add(General_SUnknown5, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown2, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown3, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown4, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown5, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown7, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown8, 1, wxEXPAND);
	General_Holder_Variables1->Add(General_Grid_Variables, 0, wxEXPAND);
/*
	General_Holder_RenderPlusUnknownTop->Add(General_Text_TechTree, 0, wxEXPAND);
	General_Holder_RenderPlusUnknownTop->Add(5, -1);
	General_Holder_RenderPlusUnknownTop->Add(General_SomethingPicker, 1, wxEXPAND);
	General_Holder_RenderPlusUnknownTop->Add(5, -1);
	General_Holder_RenderPlusUnknownTop->Add(General_SomethingNext, 1, wxEXPAND);
	General_Holder_RenderPlusUnknownTop->Add(5, -1);
	General_Holder_RenderPlusUnknownTop->Add(General_SomethingPrev, 1, wxEXPAND);
	General_Holder_RenderPlusUnknownTop->Add(5, -1);
	General_Holder_RenderPlusUnknownTop->Add(General_SomethingSize, 1, wxEXPAND);
	General_Holder_RenderPlusUnknownTop->AddStretchSpacer(2);
	General_Holder_RenderPlusUnknown->Add(General_Holder_RenderPlusUnknownTop, 0, wxEXPAND);
*/
	General_ScrollerWindowsSpace->Add(General_Holder_Variables1, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_TerrainHeader, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_BorderRelated, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_TerrainRendering, 0, wxEXPAND);
	//General_ScrollerWindowsSpace->Add(-1, 10);
	//General_ScrollerWindowsSpace->Add(General_Holder_RenderPlusUnknown, 0, wxEXPAND);

	General_ScrollerWindows->Add(10, -1);
	General_ScrollerWindows->Add(General_ScrollerWindowsSpace, 1, wxEXPAND);
	General_ScrollerWindows->Add(5, -1);

	General_Scroller->SetSizer(General_ScrollerWindows);
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
	ListUnknowns();
}

string AGE_Frame::GetUnknownName(short Index)
{
	if(GenieVersion >= genie::GV_AoK)
	{
		return "Unknown "+lexical_cast<string>(GenieFile->RandomMaps.MapHeaders[Index].ScriptNumber)+" ";
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
		default: Name += "Unknown (";
	}
	return Name += lexical_cast<string>(GenieFile->RandomMaps.MapHeaders[Index].ScriptNumber)+")";
}

void AGE_Frame::ListUnknowns()
{
	searchText = Unknowns_Search->GetValue().Lower();
	excludeText = Unknowns_Search_R->GetValue().Lower();

	auto Selections = Unknowns_List->GetSelections(Items);
	Unknowns_List->Clear();

	for(short loop = 0; loop < GenieFile->RandomMaps.MapHeaders.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnknownName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Unknowns_List->Append(Name, (void*)&GenieFile->RandomMaps.Maps[loop]);
		}
	}

	ListingFix(Selections, Unknowns_List);

	wxCommandEvent E;
	OnUnknownsSelect(E);
}

void AGE_Frame::OnUnknownsSelect(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections > 0)
	{
		RandomMapIDs.resize(Selections);
		Unknowns_UnknownLevel->resize(Selections);
		int PointerCount = Selections * 2;
		for(short loop = 0; loop < Unknowns_Unknown1.size(); ++loop)
		Unknowns_Unknown1[loop]->resize(PointerCount);
		Unknowns_Pointer1->resize(PointerCount);
		Unknowns_Pointer2->resize(PointerCount);
		Unknowns_Pointer3->resize(PointerCount);
		for(short loop = 0; loop < Unknowns_Unknown2.size(); ++loop)
		Unknowns_Unknown2[loop]->resize(PointerCount);

		genie::MapHeader * MapPointer1;
		genie::Map * MapPointer2;
		for(auto sel = Selections; sel--> 0;)
		{
			MapPointer2 = (genie::Map*)Unknowns_List->GetClientData(Items.Item(sel));
			RandomMapIDs[sel] = (MapPointer2 - (&GenieFile->RandomMaps.Maps[0]));
			MapPointer1 = &GenieFile->RandomMaps.MapHeaders[RandomMapIDs[sel]];

			Unknowns_UnknownLevel->container[sel] = &MapPointer1->ScriptNumber;
			int sel2 = sel + Selections;
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
			for(short loop = 0; loop < genie::MapHeader::UNKNOWN2_SIZE; ++loop)
			{
				Unknowns_Unknown2[loop]->container[sel] = &MapPointer1->Unknown2[loop];
				Unknowns_Unknown2[loop]->container[sel2] = &MapPointer2->Unknown2[loop];
			}
		}

		Unknowns_UnknownLevel->ChangeValue(lexical_cast<string>(MapPointer1->ScriptNumber));
		Unknowns_Unknown1[0]->ChangeValue(lexical_cast<string>(MapPointer1->BorderSouthWest));
		Unknowns_Unknown1[1]->ChangeValue(lexical_cast<string>(MapPointer1->BorderNorthWest));
		Unknowns_Unknown1[2]->ChangeValue(lexical_cast<string>(MapPointer1->BorderNorthEast));
		Unknowns_Unknown1[3]->ChangeValue(lexical_cast<string>(MapPointer1->BorderSouthEast));
		Unknowns_Unknown1[4]->ChangeValue(lexical_cast<string>(MapPointer1->BorderUsage));
		Unknowns_Unknown1[5]->ChangeValue(lexical_cast<string>(MapPointer1->WaterShape));
		Unknowns_Unknown1[6]->ChangeValue(lexical_cast<string>(MapPointer1->NonBaseTerrain));
		Unknowns_Unknown1[7]->ChangeValue(lexical_cast<string>(MapPointer1->BaseZoneCoverage));
		Unknowns_Unknown1[8]->ChangeValue(lexical_cast<string>(MapPointer1->Unknown9));
		Unknowns_Pointer1->ChangeValue(lexical_cast<string>(MapPointer1->BaseZonePointer));
		Unknowns_Pointer2->ChangeValue(lexical_cast<string>(MapPointer1->MapTerrainPointer));
		Unknowns_Pointer3->ChangeValue(lexical_cast<string>(MapPointer1->MapUnitPointer));
		for(short loop = 0; loop < Unknowns_Unknown2.size(); ++loop)
		Unknowns_Unknown2[loop]->ChangeValue(lexical_cast<string>(MapPointer1->Unknown2[loop]));

		ListUnknownFirstSubData();
		ListRMSTerrains();
		ListRMSUnits();
	}
	else
	{
		Unknowns_UnknownLevel->ChangeValue("0");
		for(short loop = 0; loop < Unknowns_Unknown1.size(); ++loop)
		Unknowns_Unknown1[loop]->ChangeValue("0");
		Unknowns_Pointer1->ChangeValue("0");
		Unknowns_Pointer2->ChangeValue("0");
		Unknowns_Pointer3->ChangeValue("0");
		for(short loop = 0; loop < Unknowns_Unknown2.size(); ++loop)
		Unknowns_Unknown2[loop]->ChangeValue("0");

		UnknownFirstSubData_List->Clear();
		DisableUnknownFirstSubData();
		RMSTerrain_List->Clear();
		DisableRMSTerrains();
		RMSUnit_List->Clear();
		DisableRMSUnits();
	}
	Unknowns_UnknownLevel->Enable(Selections);
	for(short loop = 0; loop < Unknowns_Unknown1.size(); ++loop)
	Unknowns_Unknown1[loop]->Enable(Selections);
	Unknowns_Pointer1->Enable(Selections);
	Unknowns_Pointer2->Enable(Selections);
	Unknowns_Pointer3->Enable(Selections);
	for(short loop = 0; loop < Unknowns_Unknown2.size(); ++loop)
	Unknowns_Unknown2[loop]->Enable(Selections);

}

void AGE_Frame::OnUnknownsAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->RandomMaps.MapHeaders);
	AddToList(GenieFile->RandomMaps.Maps);
	ListUnknowns();
}

void AGE_Frame::OnUnknownsInsert(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->RandomMaps.MapHeaders, RandomMapIDs[0]);
	InsertToList(GenieFile->RandomMaps.Maps, RandomMapIDs[0]);
	ListUnknowns();
}

void AGE_Frame::OnUnknownsDelete(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->RandomMaps.MapHeaders, RandomMapIDs);
	DeleteFromList(GenieFile->RandomMaps.Maps, RandomMapIDs);
	ListUnknowns();
}

void AGE_Frame::OnUnknownsCopy(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->RandomMaps.MapHeaders, RandomMapIDs, copies->MapHeader);
	CopyFromList(GenieFile->RandomMaps.Maps, RandomMapIDs, copies->Map);
}

void AGE_Frame::OnUnknownsPaste(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->RandomMaps.MapHeaders, RandomMapIDs, copies->MapHeader);
	PasteToList(GenieFile->RandomMaps.Maps, RandomMapIDs, copies->Map);
	ListUnknowns();
}

void AGE_Frame::OnUnknownsPasteInsert(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->RandomMaps.MapHeaders, RandomMapIDs[0], copies->MapHeader);
	PasteInsertToList(GenieFile->RandomMaps.Maps, RandomMapIDs[0], copies->Map);
	ListUnknowns();
}

void AGE_Frame::OnUnknownFirstSubDataSearch(wxCommandEvent &Event)
{
	ListUnknownFirstSubData();
}

string AGE_Frame::GetUnknownFirstSubDataName(short Index)
{
	return "Unknown "+lexical_cast<string>(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones[Index].Unknown1)+" ";
}

void AGE_Frame::ListUnknownFirstSubData()
{
	searchText = UnknownFirstSubData_Search->GetValue().Lower();
	excludeText = UnknownFirstSubData_Search_R->GetValue().Lower();
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	UnknownFirstSubData_List->Clear();

	for(short loop = 0; loop < GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnknownFirstSubDataName(loop);
		if(SearchMatches(Name.Lower()))
		{
			UnknownFirstSubData_List->Append(Name, (void*)&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones[loop]);
		}
	}
	ListingFix(Selections, UnknownFirstSubData_List);

	wxCommandEvent E;
	OnUnknownFirstSubDataSelect(E);
}

void AGE_Frame::OnUnknownFirstSubDataSelect(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1)
	{
		DisableUnknownFirstSubData();
		return;
	}

	UnknownFSIDs.resize(Selections);
	UnknownFirstSubData_Unknown1->resize(Selections);
	UnknownFirstSubData_BaseTerrain->resize(Selections);
	UnknownFirstSubData_SpacingBetweenPlayers->resize(Selections);
	UnknownFirstSubData_Unknown4->resize(Selections);
	for(short loop = 0; loop < UnknownFirstSubData_Unknown5.size(); ++loop)
	UnknownFirstSubData_Unknown5[loop]->resize(Selections);
	UnknownFirstSubData_Unknown6->resize(Selections);
	UnknownFirstSubData_Unknown7->resize(Selections);
	for(short loop = 0; loop < UnknownFirstSubData_Unknown8.size(); ++loop)
	UnknownFirstSubData_Unknown8[loop]->resize(Selections);
	UnknownFirstSubData_StartAreaRadius->resize(Selections);
	UnknownFirstSubData_Unknown10->resize(Selections);
	UnknownFirstSubData_Unknown11->resize(Selections);

	genie::BaseZone * UnknownPointer;
	for(auto sel = Selections; sel--> 0;)
	{
		UnknownPointer = (genie::BaseZone*)UnknownFirstSubData_List->GetClientData(Items.Item(sel));
		UnknownFSIDs[sel] = (UnknownPointer - (&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones[0]));

		UnknownFirstSubData_Unknown1->container[sel] = &UnknownPointer->Unknown1;
		UnknownFirstSubData_BaseTerrain->container[sel] = &UnknownPointer->BaseTerrain;
		UnknownFirstSubData_SpacingBetweenPlayers->container[sel] = &UnknownPointer->SpacingBetweenPlayers;
		UnknownFirstSubData_Unknown4->container[sel] = &UnknownPointer->Unknown4;
		for(short loop = 0; loop < UnknownFirstSubData_Unknown5.size(); ++loop)
		UnknownFirstSubData_Unknown5[loop]->container[sel] = &UnknownPointer->Unknown5[loop];
		UnknownFirstSubData_Unknown6->container[sel] = &UnknownPointer->Unknown6;
		UnknownFirstSubData_Unknown7->container[sel] = &UnknownPointer->Unknown7;
		for(short loop = 0; loop < UnknownFirstSubData_Unknown8.size(); ++loop)
		UnknownFirstSubData_Unknown8[loop]->container[sel] = &UnknownPointer->Unknown8[loop];
		UnknownFirstSubData_StartAreaRadius->container[sel] = &UnknownPointer->StartAreaRadius;
		UnknownFirstSubData_Unknown10->container[sel] = &UnknownPointer->Unknown10;
		UnknownFirstSubData_Unknown11->container[sel] = &UnknownPointer->Unknown11;
	}

	UnknownFirstSubData_Unknown1->Enable(true);
	UnknownFirstSubData_Unknown1->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown1));
	UnknownFirstSubData_BaseTerrain->Enable(true);
	UnknownFirstSubData_BaseTerrain->ChangeValue(lexical_cast<string>(UnknownPointer->BaseTerrain));
	UnknownFirstSubData_SpacingBetweenPlayers->Enable(true);
	UnknownFirstSubData_SpacingBetweenPlayers->ChangeValue(lexical_cast<string>(UnknownPointer->SpacingBetweenPlayers));
	UnknownFirstSubData_Unknown4->Enable(true);
	UnknownFirstSubData_Unknown4->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown4));
	for(short loop = 0; loop < UnknownFirstSubData_Unknown5.size(); ++loop)
	{
		UnknownFirstSubData_Unknown5[loop]->Enable(true);
		UnknownFirstSubData_Unknown5[loop]->ChangeValue(lexical_cast<string>((short)UnknownPointer->Unknown5[loop]));
	}
	UnknownFirstSubData_Unknown6->Enable(true);
	UnknownFirstSubData_Unknown6->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown6));
	UnknownFirstSubData_Unknown7->Enable(true);
	UnknownFirstSubData_Unknown7->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown7));
	for(short loop = 0; loop < UnknownFirstSubData_Unknown8.size(); ++loop)
	{
		UnknownFirstSubData_Unknown8[loop]->Enable(true);
		UnknownFirstSubData_Unknown8[loop]->ChangeValue(lexical_cast<string>((short)UnknownPointer->Unknown8[loop]));
	}
	UnknownFirstSubData_StartAreaRadius->Enable(true);
	UnknownFirstSubData_StartAreaRadius->ChangeValue(lexical_cast<string>(UnknownPointer->StartAreaRadius));
	UnknownFirstSubData_Unknown10->Enable(true);
	UnknownFirstSubData_Unknown10->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown10));
	UnknownFirstSubData_Unknown11->Enable(true);
	UnknownFirstSubData_Unknown11->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown11));
}

void AGE_Frame::DisableUnknownFirstSubData()
{
	UnknownFirstSubData_Unknown1->Enable(false);
	UnknownFirstSubData_Unknown1->ChangeValue("0");
	UnknownFirstSubData_BaseTerrain->Enable(false);
	UnknownFirstSubData_BaseTerrain->ChangeValue("0");
	UnknownFirstSubData_SpacingBetweenPlayers->Enable(false);
	UnknownFirstSubData_SpacingBetweenPlayers->ChangeValue("0");
	UnknownFirstSubData_Unknown4->Enable(false);
	UnknownFirstSubData_Unknown4->ChangeValue("0");
	for(short loop = 0; loop < UnknownFirstSubData_Unknown5.size(); ++loop)
	{
		UnknownFirstSubData_Unknown5[loop]->Enable(false);
		UnknownFirstSubData_Unknown5[loop]->ChangeValue("0");
	}
	UnknownFirstSubData_Unknown6->Enable(false);
	UnknownFirstSubData_Unknown6->ChangeValue("0");
	UnknownFirstSubData_Unknown7->Enable(false);
	UnknownFirstSubData_Unknown7->ChangeValue("0");
	for(short loop = 0; loop < UnknownFirstSubData_Unknown8.size(); ++loop)
	{
		UnknownFirstSubData_Unknown8[loop]->Enable(false);
		UnknownFirstSubData_Unknown8[loop]->ChangeValue("0");
	}
	UnknownFirstSubData_StartAreaRadius->Enable(false);
	UnknownFirstSubData_StartAreaRadius->ChangeValue("0");
	UnknownFirstSubData_Unknown10->Enable(false);
	UnknownFirstSubData_Unknown10->ChangeValue("0");
	UnknownFirstSubData_Unknown11->Enable(false);
	UnknownFirstSubData_Unknown11->ChangeValue("0");
}

void AGE_Frame::OnUnknownFirstSubDataAdd(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].BaseZoneCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones.size();
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownFirstSubDataInsert(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones, UnknownFSIDs[0]);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].BaseZoneCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones.size();
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownFirstSubDataDelete(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones, UnknownFSIDs);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].BaseZoneCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones.size();
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownFirstSubDataCopy(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones, UnknownFSIDs, copies->BaseZone);
}

void AGE_Frame::OnUnknownFirstSubDataPaste(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones, UnknownFSIDs, copies->BaseZone);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].BaseZoneCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones.size();
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownFirstSubDataPasteInsert(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones, UnknownFSIDs[0], copies->BaseZone);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].BaseZoneCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].BaseZones.size();
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownFirstSubDataCopyToMaps(wxCommandEvent &Event)
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
	if(GenieFile->Terrains.size() <= Terrain) return Name + "Nonexistent Terrain";
	if(!GenieFile->Terrains[Terrain].Name.empty())
	{
		return Name + GenieFile->Terrains[Terrain].Name;
	}
	return Name + "New Terrain";
}

void AGE_Frame::ListRMSTerrains()
{
	searchText = RMSTerrain_Search->GetValue().Lower();
	excludeText = RMSTerrain_Search_R->GetValue().Lower();
	auto Selections = RMSTerrain_List->GetSelections(Items);
	RMSTerrain_List->Clear();

	for(short loop = 0; loop < GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetRMSTerrainName(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains[loop].Terrain);
		if(SearchMatches(Name.Lower()))
		{
			RMSTerrain_List->Append(Name, (void*)&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains[loop]);
		}
	}
	ListingFix(Selections, RMSTerrain_List);

	wxCommandEvent E;
	OnRMSTerrainSelect(E);
}

void AGE_Frame::OnRMSTerrainSelect(wxCommandEvent &Event)
{
	auto Selections = RMSTerrain_List->GetSelections(Items);
	if(Selections < 1)
	{
		DisableRMSTerrains();
		return;
	}

	UnknownSSIDs.resize(Selections);
	for(short loop = 0; loop < RMSTerrain_Unknown1.size(); ++loop)
	RMSTerrain_Unknown1[loop]->resize(Selections);

	genie::MapTerrain * UnknownPointer;
	for(auto sel = Selections; sel--> 0;)
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
	RMSTerrain_Unknown1[0]->ChangeValue(lexical_cast<string>(UnknownPointer->Proportion));
	RMSTerrain_Unknown1[1]->ChangeValue(lexical_cast<string>(UnknownPointer->Terrain));
	RMSTerrain_Unknown1[2]->ChangeValue(lexical_cast<string>(UnknownPointer->NumberOfClumps));
	RMSTerrain_Unknown1[3]->ChangeValue(lexical_cast<string>(UnknownPointer->SpacingToOtherTerrains));
	RMSTerrain_Unknown1[4]->ChangeValue(lexical_cast<string>(UnknownPointer->PlacementZone));
	RMSTerrain_Unknown1[5]->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown6));
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
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapTerrainCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainInsert(wxCommandEvent &Event)
{
	auto Selections = RMSTerrain_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains, UnknownSSIDs[0]);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapTerrainCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainDelete(wxCommandEvent &Event)
{
	auto Selections = RMSTerrain_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains, UnknownSSIDs);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapTerrainCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainCopy(wxCommandEvent &Event)
{
	auto Selections = RMSTerrain_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains, UnknownSSIDs, copies->MapTerrain);
}

void AGE_Frame::OnRMSTerrainPaste(wxCommandEvent &Event)
{
	auto Selections = RMSTerrain_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains, UnknownSSIDs, copies->MapTerrain);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapTerrainCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapTerrains.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainPasteInsert(wxCommandEvent &Event)
{
	auto Selections = RMSTerrain_List->GetSelections(Items);
	if(Selections < 1) return;

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

string AGE_Frame::GetRMSUnitName(short Unit)
{
	return "Unknown "+lexical_cast<string>(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits[Unit].Unit)+" ";
}

void AGE_Frame::ListRMSUnits()
{
	searchText = RMSUnit_Search->GetValue().Lower();
	excludeText = RMSUnit_Search_R->GetValue().Lower();
	auto Selections = RMSUnit_List->GetSelections(Items);
	RMSUnit_List->Clear();

	for(short loop = 0; loop < GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineUnitName(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits[loop].Unit);
		if(SearchMatches(Name.Lower()))
		{
			RMSUnit_List->Append(Name, (void*)&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits[loop]);
		}
	}
	ListingFix(Selections, RMSUnit_List);

	wxCommandEvent E;
	OnRMSUnitSelect(E);
}

void AGE_Frame::OnRMSUnitSelect(wxCommandEvent &Event)
{
	auto Selections = RMSUnit_List->GetSelections(Items);
	if(Selections < 1)
	{
		DisableRMSUnits();
		return;
	}

	UnknownTSIDs.resize(Selections);
	RMSUnit_Unit->resize(Selections);
	RMSUnit_HostTerrain->resize(Selections);
	for(short loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
	RMSUnit_Unknown3[loop]->resize(Selections);
	RMSUnit_ObjectsPerPlayer->resize(Selections);
	RMSUnit_Unknown5->resize(Selections);
	RMSUnit_GroupsPerPlayer->resize(Selections);
	RMSUnit_Unknown7->resize(Selections);
	RMSUnit_OwnAtStart->resize(Selections);
	RMSUnit_SetPlaceForAllPlayers->resize(Selections);
	RMSUnit_MinDistanceToPlayers->resize(Selections);
	RMSUnit_MaxDistanceToPlayers->resize(Selections);

	genie::MapUnit * UnknownPointer;
	for(auto sel = Selections; sel--> 0;)
	{
		UnknownPointer = (genie::MapUnit*)RMSUnit_List->GetClientData(Items.Item(sel));
		UnknownTSIDs[sel] = (UnknownPointer - (&GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits[0]));

		RMSUnit_Unit->container[sel] = &UnknownPointer->Unit;
		RMSUnit_HostTerrain->container[sel] = &UnknownPointer->HostTerrain;
		for(short loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
		RMSUnit_Unknown3[loop]->container[sel] = &UnknownPointer->Unknown3[loop];
		RMSUnit_ObjectsPerPlayer->container[sel] = &UnknownPointer->ObjectsPerPlayer;
		RMSUnit_Unknown5->container[sel] = &UnknownPointer->Unknown5;
		RMSUnit_GroupsPerPlayer->container[sel] = &UnknownPointer->GroupsPerPlayer;
		RMSUnit_Unknown7->container[sel] = &UnknownPointer->Unknown7;
		RMSUnit_OwnAtStart->container[sel] = &UnknownPointer->OwnAtStart;
		RMSUnit_SetPlaceForAllPlayers->container[sel] = &UnknownPointer->SetPlaceForAllPlayers;
		RMSUnit_MinDistanceToPlayers->container[sel] = &UnknownPointer->MinDistanceToPlayers;
		RMSUnit_MaxDistanceToPlayers->container[sel] = &UnknownPointer->MaxDistanceToPlayers;
	}

	RMSUnit_Unit->Enable(true);
	RMSUnit_Unit->ChangeValue(lexical_cast<string>(UnknownPointer->Unit));
	RMSUnit_HostTerrain->Enable(true);
	RMSUnit_HostTerrain->ChangeValue(lexical_cast<string>(UnknownPointer->HostTerrain));
	for(short loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
	{
		RMSUnit_Unknown3[loop]->Enable(true);
		RMSUnit_Unknown3[loop]->ChangeValue(lexical_cast<string>((short)UnknownPointer->Unknown3[loop]));
	}
	RMSUnit_ObjectsPerPlayer->Enable(true);
	RMSUnit_ObjectsPerPlayer->ChangeValue(lexical_cast<string>(UnknownPointer->ObjectsPerPlayer));
	RMSUnit_Unknown5->Enable(true);
	RMSUnit_Unknown5->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown5));
	RMSUnit_GroupsPerPlayer->Enable(true);
	RMSUnit_GroupsPerPlayer->ChangeValue(lexical_cast<string>(UnknownPointer->GroupsPerPlayer));
	RMSUnit_Unknown7->Enable(true);
	RMSUnit_Unknown7->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown7));
	RMSUnit_OwnAtStart->Enable(true);
	RMSUnit_OwnAtStart->ChangeValue(lexical_cast<string>(UnknownPointer->OwnAtStart));
	RMSUnit_SetPlaceForAllPlayers->Enable(true);
	RMSUnit_SetPlaceForAllPlayers->ChangeValue(lexical_cast<string>(UnknownPointer->SetPlaceForAllPlayers));
	RMSUnit_MinDistanceToPlayers->Enable(true);
	RMSUnit_MinDistanceToPlayers->ChangeValue(lexical_cast<string>(UnknownPointer->MinDistanceToPlayers));
	RMSUnit_MaxDistanceToPlayers->Enable(true);
	RMSUnit_MaxDistanceToPlayers->ChangeValue(lexical_cast<string>(UnknownPointer->MaxDistanceToPlayers));
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
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnitCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitInsert(wxCommandEvent &Event)
{
	auto Selections = RMSUnit_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits, UnknownTSIDs[0]);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnitCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitDelete(wxCommandEvent &Event)
{
	auto Selections = RMSUnit_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits, UnknownTSIDs);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnitCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitCopy(wxCommandEvent &Event)
{
	auto Selections = RMSUnit_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits, UnknownTSIDs, copies->MapUnit);
}

void AGE_Frame::OnRMSUnitPaste(wxCommandEvent &Event)
{
	auto Selections = RMSUnit_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits, UnknownTSIDs, copies->MapUnit);
	GenieFile->RandomMaps.MapHeaders[RandomMapIDs[0]].MapUnitCount = GenieFile->RandomMaps.Maps[RandomMapIDs[0]].MapUnits.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitPasteInsert(wxCommandEvent &Event)
{
	auto Selections = RMSUnit_List->GetSelections(Items);
	if(Selections < 1) return;

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

void AGE_Frame::CreateUnknownControls()
{
	Tab_Unknown = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Unknown_Main = new wxBoxSizer(wxHORIZONTAL);
	Unknown_Area = new wxBoxSizer(wxVERTICAL);
	Unknown_Scroller = new wxScrolledWindow(Tab_Unknown, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Unknown_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	Unknown_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);

	Unknown_Grid_UnknownPointer = new wxGridSizer(8, 0, 0);
	Unknown_Holder_UnknownPointer = new wxBoxSizer(wxVERTICAL);
	Unknown_Text_UnknownPointer = new wxStaticText(Tab_Unknown, wxID_ANY, " Random Map Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknown_UnknownPointer = new TextCtrl_Long(Tab_Unknown);

	Unknowns = new wxStaticBoxSizer(wxHORIZONTAL, Tab_Unknown, "Random Map Scripts (Required in AoE/RoR)");
	Unknowns_ListArea = new wxBoxSizer(wxVERTICAL);
	Unknowns_Search = new wxTextCtrl(Tab_Unknown, wxID_ANY);
	Unknowns_Search_R = new wxTextCtrl(Tab_Unknown, wxID_ANY);
	Unknowns_List = new wxListBox(Tab_Unknown, wxID_ANY, wxDefaultPosition, wxSize(10, 220), 0, NULL, wxLB_EXTENDED);
	Unknowns_Buttons = new wxGridSizer(3, 0, 0);
	Unknowns_Add = new wxButton(Tab_Unknown, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Insert = new wxButton(Tab_Unknown, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Delete = new wxButton(Tab_Unknown, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Copy = new wxButton(Tab_Unknown, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Paste = new wxButton(Tab_Unknown, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Unknowns_PasteInsert = new wxButton(Tab_Unknown, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	Unknowns_Space_UnknownLevel = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Holder_UnknownLevel = new wxBoxSizer(wxVERTICAL);
	Unknowns_Text_UnknownLevel = new wxStaticText(Unknown_Scroller, wxID_ANY, " Script Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_UnknownLevel = new TextCtrl_Long(Unknown_Scroller);
	Unknowns_Grid_Unknown1 = new wxGridSizer(5, 5, 5);
	for(short loop = 0; loop < Unknowns_Unknown1.size(); ++loop)
	{
		Unknowns_Holder_Unknown1[loop] = new wxBoxSizer(wxVERTICAL);
		Unknowns_Unknown1[loop] = new TextCtrl_Long(Unknown_Scroller);
	}
	Unknowns_Text_Unknown1[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Southwest Border *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[0]->SetToolTip("Distance from the map edge allocated for non-base zone");
	Unknowns_Text_Unknown1[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Northwest Border *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[1]->SetToolTip("Distance from the map edge allocated for non-base zone");
	Unknowns_Text_Unknown1[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Northeast Border *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[2]->SetToolTip("Distance from the map edge allocated for non-base zone");
	Unknowns_Text_Unknown1[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Southeast Border *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[3]->SetToolTip("Distance from the map edge allocated for non-base zone");
	Unknowns_Text_Unknown1[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Border Usage % *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[4]->SetToolTip("% of border area covered with non-base terrain");
	Unknowns_Text_Unknown1[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Water Shape?", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Text_Unknown1[6] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Non-base Terrain *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[6]->SetToolTip("Used on the borders as well");
	Unknowns_Text_Unknown1[7] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Zone Cover % *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[7]->SetToolTip("Can be over 100");
	Unknowns_Text_Unknown1[8] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 9", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Space_Pointer1 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Holder_Pointer1 = new wxBoxSizer(wxVERTICAL);
	Unknowns_Text_Pointer1 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Zone Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Pointer1 = new TextCtrl_Long(Unknown_Scroller);

	UnknownFirstSubData = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Base Zone Data");
	UnknownFirstSubData_ListArea = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_DataArea = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	UnknownFirstSubData_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	UnknownFirstSubData_List = new wxListBox(Unknown_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	UnknownFirstSubData_Buttons = new wxGridSizer(3, 0, 0);
	UnknownFirstSubData_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnknownFirstSubData_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	UnknownFirstSubData_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnknownFirstSubData_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnknownFirstSubData_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	UnknownFirstSubData_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	UnknownFirstSubData_CopyToMaps = new wxButton(Unknown_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(5, 20));

	UnknownFirstSubData_Grid_Unknown1 = new wxGridSizer(3, 5, 5);

	UnknownFirstSubData_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Text_Unknown1 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Unknown1 = new TextCtrl_Long(Unknown_Scroller);
	UnknownFirstSubData_Holder_BaseTerrain = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Text_BaseTerrain = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_BaseTerrain = new TextCtrl_Long(Unknown_Scroller);
	UnknownFirstSubData_Holder_SpacingBetweenPlayers = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Text_SpacingBetweenPlayers = new wxStaticText(Unknown_Scroller, wxID_ANY, " Spacing Between Players *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_SpacingBetweenPlayers = new TextCtrl_Long(Unknown_Scroller);
	UnknownFirstSubData_SpacingBetweenPlayers->SetToolTip("Non-base terrain (like rivers) space between players\nIf too large, they won't be created");
	UnknownFirstSubData_Holder_Unknown4 = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Text_Unknown4 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Unknown4 = new TextCtrl_Long(Unknown_Scroller);

	UnknownFirstSubData_Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Grid_Unknown5 = new wxGridSizer(4, 0, 0);
	UnknownFirstSubData_Text_Unknown5 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Min Dist. Between Players *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < UnknownFirstSubData_Unknown5.size(); ++loop)
	UnknownFirstSubData_Unknown5[loop] = new TextCtrl_Byte(Unknown_Scroller);
	UnknownFirstSubData_Unknown5[1]->SetToolTip("Minimum distance in tiles between \"player initial zones\"");

	UnknownFirstSubData_Holder_Unknown6 = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Text_Unknown6 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Unknown6 = new TextCtrl_Long(Unknown_Scroller);
	UnknownFirstSubData_Holder_Unknown7 = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Text_Unknown7 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Unknown7 = new TextCtrl_Long(Unknown_Scroller);

	UnknownFirstSubData_Holder_Unknown8 = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Grid_Unknown8 = new wxGridSizer(4, 0, 0);
	UnknownFirstSubData_Text_Unknown8 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Zone Radius *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < UnknownFirstSubData_Unknown8.size(); ++loop)
	UnknownFirstSubData_Unknown8[loop] = new TextCtrl_Byte(Unknown_Scroller);
	UnknownFirstSubData_Unknown8[1]->SetToolTip("Base zone is created for every player");

	UnknownFirstSubData_Holder_StartAreaRadius = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Text_StartAreaRadius = new wxStaticText(Unknown_Scroller, wxID_ANY, " Players' Start Area Radius *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_StartAreaRadius = new TextCtrl_Long(Unknown_Scroller);
	UnknownFirstSubData_StartAreaRadius->SetToolTip("This area cannot contain different elevations or terrains\nUnknown 10 affects this too");
	UnknownFirstSubData_Holder_Unknown10 = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Text_Unknown10 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 10 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Unknown10 = new TextCtrl_Long(Unknown_Scroller);
	UnknownFirstSubData_Unknown10->SetToolTip("Has something to do with players' starting area");
	UnknownFirstSubData_Holder_Unknown11 = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Text_Unknown11 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Unknown11 = new TextCtrl_Long(Unknown_Scroller);

	Unknowns_Space_Pointer2 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Holder_Pointer2 = new wxBoxSizer(wxVERTICAL);
	Unknowns_Text_Pointer2 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Map Terrain Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Pointer2 = new TextCtrl_Long(Unknown_Scroller);

	RMSTerrain = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Terrains Placed on the Map");
	RMSTerrain_ListArea = new wxBoxSizer(wxVERTICAL);
	RMSTerrain_DataArea = new wxBoxSizer(wxVERTICAL);
	RMSTerrain_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSTerrain_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSTerrain_List = new wxListBox(Unknown_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	RMSTerrain_Buttons = new wxGridSizer(3, 0, 0);
	RMSTerrain_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	RMSTerrain_CopyToMaps = new wxButton(Unknown_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(5, 20));

	RMSTerrain_Grid_Unknown1 = new wxGridSizer(3, 5, 5);
	for(short loop = 0; loop < RMSTerrain_Unknown1.size(); ++loop)
	{
		RMSTerrain_Holder_Unknown1[loop] = new wxBoxSizer(wxVERTICAL);
		RMSTerrain_Unknown1[loop] = new TextCtrl_Long(Unknown_Scroller);
	}
	RMSTerrain_Text_Unknown1[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Proportion *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSTerrain_Unknown1[0]->SetToolTip("% of the total map area");
	RMSTerrain_Text_Unknown1[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSTerrain_Text_Unknown1[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Number of Clumps *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSTerrain_Unknown1[2]->SetToolTip("Clusters in the map");
	RMSTerrain_Text_Unknown1[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Spacing to Other Terrains *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSTerrain_Unknown1[3]->SetToolTip("Minimum distance to base terrain (or non-base terrain)");
	RMSTerrain_Text_Unknown1[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Placement Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSTerrain_Text_Unknown1[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

	Unknowns_Space_Pointer3 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Holder_Pointer3 = new wxBoxSizer(wxVERTICAL);
	Unknowns_Text_Pointer3 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Map Unit Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Pointer3 = new TextCtrl_Long(Unknown_Scroller);

	RMSUnit = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Units Placed on the Map (Some may appear anyway)");
	RMSUnit_ListArea = new wxBoxSizer(wxVERTICAL);
	RMSUnit_DataArea = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSUnit_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	RMSUnit_List = new wxListBox(Unknown_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 250), 0, NULL, wxLB_EXTENDED);
	RMSUnit_Buttons = new wxGridSizer(3, 0, 0);
	RMSUnit_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	RMSUnit_CopyToMaps = new wxButton(Unknown_Scroller, wxID_ANY, "Copy all to selected maps", wxDefaultPosition, wxSize(5, 20));

	RMSUnit_Grid_Unknown1 = new wxGridSizer(3, 5, 5);
	RMSUnit_Holder_Unit = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Text_Unit = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Unit = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_Holder_HostTerrain = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Text_HostTerrain = new wxStaticText(Unknown_Scroller, wxID_ANY, " Placement Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_HostTerrain = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Grid_Unknown3 = new wxGridSizer(4, 0, 0);
	RMSUnit_Text_Unknown3 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Group Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
	RMSUnit_Unknown3[loop] = new TextCtrl_Byte(Unknown_Scroller);
	RMSUnit_Unknown3[0]->SetToolTip("0 Only 1 unit is placed from group\n1 & 2 All units are placed from group");
	RMSUnit_Holder_ObjectsPerPlayer = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Text_ObjectsPerPlayer = new wxStaticText(Unknown_Scroller, wxID_ANY, " Objects per Group", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_ObjectsPerPlayer = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Text_Unknown5 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Fluctuation *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Unknown5 = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_Unknown5->SetToolTip("Max random variation in the number of objects in the group");
	RMSUnit_Holder_GroupsPerPlayer = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Text_GroupsPerPlayer = new wxStaticText(Unknown_Scroller, wxID_ANY, " Groups per Player", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_GroupsPerPlayer = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_Holder_Unknown7 = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Text_Unknown7 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Group Radius *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Unknown7 = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_Unknown7->SetToolTip("Max distance in tiles, for each object of the group, to the central location of the group");
	RMSUnit_Holder_OwnAtStart = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Text_OwnAtStart = new wxStaticText(Unknown_Scroller, wxID_ANY, " Own at Start (-1=Yes) *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_OwnAtStart = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_OwnAtStart->SetToolTip("Doesn't work if the unit isn't placed for all players");
	RMSUnit_Holder_SetPlaceForAllPlayers = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Text_SetPlaceForAllPlayers = new wxStaticText(Unknown_Scroller, wxID_ANY, " Set Place for All Players *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_SetPlaceForAllPlayers = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_SetPlaceForAllPlayers->SetToolTip("1 = Done once per player\n-1 = Done once, whatever the number of players is\n-2 = same as -1 ? Cannot find a difference");
	RMSUnit_Holder_MinDistanceToPlayers = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Text_MinDistanceToPlayers = new wxStaticText(Unknown_Scroller, wxID_ANY, " Min Distance to Players", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_MinDistanceToPlayers = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_Holder_MaxDistanceToPlayers = new wxBoxSizer(wxVERTICAL);
	RMSUnit_Text_MaxDistanceToPlayers = new wxStaticText(Unknown_Scroller, wxID_ANY, " Max Distance to Players *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_MaxDistanceToPlayers = new TextCtrl_Long(Unknown_Scroller);
	RMSUnit_MaxDistanceToPlayers->SetToolTip("- Don't use 0 here for units that are own at start\n- 0 is OK for other units (gold/bushes/gazelle/etc)\n- You can use -1 as a wildcard for units that are own at start");

	Unknowns_Grid_Unknown2 = new wxGridSizer(5, 5, 5);
	for(short loop = 0; loop < Unknowns_Unknown2.size(); ++loop)
	{
		Unknowns_Holder_Unknown2[loop] = new wxBoxSizer(wxVERTICAL);
		Unknowns_Unknown2[loop] = new TextCtrl_Long(Unknown_Scroller);
	}
	Unknowns_Text_Unknown2[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 10", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Text_Unknown2[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

	Unknown_Holder_UnknownPointer->Add(Unknown_Text_UnknownPointer, 0, wxEXPAND);
	Unknown_Holder_UnknownPointer->Add(Unknown_UnknownPointer, 1, wxEXPAND);
	Unknown_Grid_UnknownPointer->Add(Unknown_Holder_UnknownPointer, 1, wxEXPAND);

	Unknowns_Buttons->Add(Unknowns_Add, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Insert, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Delete, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Copy, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Paste, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_PasteInsert, 1, wxEXPAND);

	Unknowns_ListArea->Add(Unknowns_Search, 0, wxEXPAND);
	Unknowns_ListArea->Add(Unknowns_Search_R, 0, wxEXPAND);
	Unknowns_ListArea->Add(-1, 2);
	Unknowns_ListArea->Add(Unknowns_List, 1, wxEXPAND);
	Unknowns_ListArea->Add(-1, 2);
	Unknowns_ListArea->Add(Unknowns_Buttons, 0, wxEXPAND);

	Unknowns_Holder_UnknownLevel->Add(Unknowns_Text_UnknownLevel, 0, wxEXPAND);
	Unknowns_Holder_UnknownLevel->Add(Unknowns_UnknownLevel, 1, wxEXPAND);
	Unknowns_Space_UnknownLevel->Add(Unknowns_Holder_UnknownLevel, 1, wxEXPAND);
	Unknowns_Space_UnknownLevel->AddStretchSpacer(3);

	for(short loop = 0; loop < Unknowns_Unknown1.size(); ++loop)
	{
		Unknowns_Holder_Unknown1[loop]->Add(Unknowns_Text_Unknown1[loop], 0, wxEXPAND);
		Unknowns_Holder_Unknown1[loop]->Add(Unknowns_Unknown1[loop], 1, wxEXPAND);
		Unknowns_Grid_Unknown1->Add(Unknowns_Holder_Unknown1[loop], 1, wxEXPAND);
	}

	Unknowns_Holder_Pointer1->Add(Unknowns_Text_Pointer1, 0, wxEXPAND);
	Unknowns_Holder_Pointer1->Add(Unknowns_Pointer1, 1, wxEXPAND);
	Unknowns_Space_Pointer1->Add(Unknowns_Holder_Pointer1, 1, wxEXPAND);
	Unknowns_Space_Pointer1->AddStretchSpacer(3);

	UnknownFirstSubData_Buttons->Add(UnknownFirstSubData_Add, 1, wxEXPAND);
	UnknownFirstSubData_Buttons->Add(UnknownFirstSubData_Insert, 1, wxEXPAND);
	UnknownFirstSubData_Buttons->Add(UnknownFirstSubData_Delete, 1, wxEXPAND);
	UnknownFirstSubData_Buttons->Add(UnknownFirstSubData_Copy, 1, wxEXPAND);
	UnknownFirstSubData_Buttons->Add(UnknownFirstSubData_Paste, 1, wxEXPAND);
	UnknownFirstSubData_Buttons->Add(UnknownFirstSubData_PasteInsert, 1, wxEXPAND);

	UnknownFirstSubData_ListArea->Add(UnknownFirstSubData_Search, 0, wxEXPAND);
	UnknownFirstSubData_ListArea->Add(UnknownFirstSubData_Search_R, 0, wxEXPAND);
	UnknownFirstSubData_ListArea->Add(-1, 2);
	UnknownFirstSubData_ListArea->Add(UnknownFirstSubData_List, 1, wxEXPAND);
	UnknownFirstSubData_ListArea->Add(-1, 2);
	UnknownFirstSubData_ListArea->Add(UnknownFirstSubData_Buttons, 0, wxEXPAND);
	UnknownFirstSubData_ListArea->Add(-1, 2);
	UnknownFirstSubData_ListArea->Add(UnknownFirstSubData_CopyToMaps, 0, wxEXPAND);

	UnknownFirstSubData_Holder_Unknown1->Add(UnknownFirstSubData_Text_Unknown1, 0, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown1->Add(UnknownFirstSubData_Unknown1, 1, wxEXPAND);
	UnknownFirstSubData_Holder_BaseTerrain->Add(UnknownFirstSubData_Text_BaseTerrain, 0, wxEXPAND);
	UnknownFirstSubData_Holder_BaseTerrain->Add(UnknownFirstSubData_BaseTerrain, 1, wxEXPAND);
	UnknownFirstSubData_Holder_SpacingBetweenPlayers->Add(UnknownFirstSubData_Text_SpacingBetweenPlayers, 0, wxEXPAND);
	UnknownFirstSubData_Holder_SpacingBetweenPlayers->Add(UnknownFirstSubData_SpacingBetweenPlayers, 1, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown4->Add(UnknownFirstSubData_Text_Unknown4, 0, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown4->Add(UnknownFirstSubData_Unknown4, 1, wxEXPAND);
	for(short loop = 0; loop < UnknownFirstSubData_Unknown5.size(); ++loop)
	UnknownFirstSubData_Grid_Unknown5->Add(UnknownFirstSubData_Unknown5[loop], 1, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown5->Add(UnknownFirstSubData_Text_Unknown5, 0, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown5->Add(UnknownFirstSubData_Grid_Unknown5, 1, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown6->Add(UnknownFirstSubData_Text_Unknown6, 0, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown6->Add(UnknownFirstSubData_Unknown6, 1, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown7->Add(UnknownFirstSubData_Text_Unknown7, 0, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown7->Add(UnknownFirstSubData_Unknown7, 1, wxEXPAND);
	for(short loop = 0; loop < UnknownFirstSubData_Unknown8.size(); ++loop)
	UnknownFirstSubData_Grid_Unknown8->Add(UnknownFirstSubData_Unknown8[loop], 1, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown8->Add(UnknownFirstSubData_Text_Unknown8, 0, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown8->Add(UnknownFirstSubData_Grid_Unknown8, 1, wxEXPAND);
	UnknownFirstSubData_Holder_StartAreaRadius->Add(UnknownFirstSubData_Text_StartAreaRadius, 0, wxEXPAND);
	UnknownFirstSubData_Holder_StartAreaRadius->Add(UnknownFirstSubData_StartAreaRadius, 1, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown10->Add(UnknownFirstSubData_Text_Unknown10, 0, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown10->Add(UnknownFirstSubData_Unknown10, 1, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown11->Add(UnknownFirstSubData_Text_Unknown11, 0, wxEXPAND);
	UnknownFirstSubData_Holder_Unknown11->Add(UnknownFirstSubData_Unknown11, 1, wxEXPAND);
	UnknownFirstSubData_Grid_Unknown1->Add(UnknownFirstSubData_Holder_Unknown1, 1, wxEXPAND);
	UnknownFirstSubData_Grid_Unknown1->Add(UnknownFirstSubData_Holder_BaseTerrain, 1, wxEXPAND);
	UnknownFirstSubData_Grid_Unknown1->Add(UnknownFirstSubData_Holder_SpacingBetweenPlayers, 1, wxEXPAND);
	UnknownFirstSubData_Grid_Unknown1->Add(UnknownFirstSubData_Holder_Unknown4, 1, wxEXPAND);
	UnknownFirstSubData_Grid_Unknown1->Add(UnknownFirstSubData_Holder_Unknown5, 1, wxEXPAND);
	UnknownFirstSubData_Grid_Unknown1->Add(UnknownFirstSubData_Holder_Unknown6, 1, wxEXPAND);
	UnknownFirstSubData_Grid_Unknown1->Add(UnknownFirstSubData_Holder_Unknown7, 1, wxEXPAND);
	UnknownFirstSubData_Grid_Unknown1->Add(UnknownFirstSubData_Holder_Unknown8, 1, wxEXPAND);
	UnknownFirstSubData_Grid_Unknown1->Add(UnknownFirstSubData_Holder_StartAreaRadius, 1, wxEXPAND);
	UnknownFirstSubData_Grid_Unknown1->Add(UnknownFirstSubData_Holder_Unknown10, 1, wxEXPAND);
	UnknownFirstSubData_Grid_Unknown1->Add(UnknownFirstSubData_Holder_Unknown11, 1, wxEXPAND);
	UnknownFirstSubData_DataArea->Add(UnknownFirstSubData_Grid_Unknown1, 0, wxEXPAND);

	UnknownFirstSubData->Add(UnknownFirstSubData_ListArea, 1, wxEXPAND);
	UnknownFirstSubData->Add(10, -1);
	UnknownFirstSubData->Add(UnknownFirstSubData_DataArea, 3, wxEXPAND);

	Unknowns_Holder_Pointer2->Add(Unknowns_Text_Pointer2, 0, wxEXPAND);
	Unknowns_Holder_Pointer2->Add(Unknowns_Pointer2, 1, wxEXPAND);
	Unknowns_Space_Pointer2->Add(Unknowns_Holder_Pointer2, 1, wxEXPAND);
	Unknowns_Space_Pointer2->AddStretchSpacer(3);

	RMSTerrain_Buttons->Add(RMSTerrain_Add, 1, wxEXPAND);
	RMSTerrain_Buttons->Add(RMSTerrain_Insert, 1, wxEXPAND);
	RMSTerrain_Buttons->Add(RMSTerrain_Delete, 1, wxEXPAND);
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
		RMSTerrain_Holder_Unknown1[loop]->Add(RMSTerrain_Text_Unknown1[loop], 0, wxEXPAND);
		RMSTerrain_Holder_Unknown1[loop]->Add(RMSTerrain_Unknown1[loop], 1, wxEXPAND);
		RMSTerrain_Grid_Unknown1->Add(RMSTerrain_Holder_Unknown1[loop], 1, wxEXPAND);
	}
	RMSTerrain_DataArea->Add(RMSTerrain_Grid_Unknown1, 0, wxEXPAND);

	RMSTerrain->Add(RMSTerrain_ListArea, 1, wxEXPAND);
	RMSTerrain->Add(10, -1);
	RMSTerrain->Add(RMSTerrain_DataArea, 3, wxEXPAND);

	Unknowns_Holder_Pointer3->Add(Unknowns_Text_Pointer3, 0, wxEXPAND);
	Unknowns_Holder_Pointer3->Add(Unknowns_Pointer3, 1, wxEXPAND);
	Unknowns_Space_Pointer3->Add(Unknowns_Holder_Pointer3, 1, wxEXPAND);
	Unknowns_Space_Pointer3->AddStretchSpacer(3);

	RMSUnit_Buttons->Add(RMSUnit_Add, 1, wxEXPAND);
	RMSUnit_Buttons->Add(RMSUnit_Insert, 1, wxEXPAND);
	RMSUnit_Buttons->Add(RMSUnit_Delete, 1, wxEXPAND);
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

	RMSUnit_Holder_Unit->Add(RMSUnit_Text_Unit, 0, wxEXPAND);
	RMSUnit_Holder_Unit->Add(RMSUnit_Unit, 1, wxEXPAND);
	RMSUnit_Holder_HostTerrain->Add(RMSUnit_Text_HostTerrain, 0, wxEXPAND);
	RMSUnit_Holder_HostTerrain->Add(RMSUnit_HostTerrain, 1, wxEXPAND);
	for(short loop = 0; loop < RMSUnit_Unknown3.size(); ++loop)
	RMSUnit_Grid_Unknown3->Add(RMSUnit_Unknown3[loop], 1, wxEXPAND);
	RMSUnit_Holder_Unknown3->Add(RMSUnit_Text_Unknown3, 0, wxEXPAND);
	RMSUnit_Holder_Unknown3->Add(RMSUnit_Grid_Unknown3, 1, wxEXPAND);
	RMSUnit_Holder_ObjectsPerPlayer->Add(RMSUnit_Text_ObjectsPerPlayer, 0, wxEXPAND);
	RMSUnit_Holder_ObjectsPerPlayer->Add(RMSUnit_ObjectsPerPlayer, 1, wxEXPAND);
	RMSUnit_Holder_Unknown5->Add(RMSUnit_Text_Unknown5, 0, wxEXPAND);
	RMSUnit_Holder_Unknown5->Add(RMSUnit_Unknown5, 1, wxEXPAND);
	RMSUnit_Holder_GroupsPerPlayer->Add(RMSUnit_Text_GroupsPerPlayer, 0, wxEXPAND);
	RMSUnit_Holder_GroupsPerPlayer->Add(RMSUnit_GroupsPerPlayer, 1, wxEXPAND);
	RMSUnit_Holder_Unknown7->Add(RMSUnit_Text_Unknown7, 0, wxEXPAND);
	RMSUnit_Holder_Unknown7->Add(RMSUnit_Unknown7, 1, wxEXPAND);
	RMSUnit_Holder_OwnAtStart->Add(RMSUnit_Text_OwnAtStart, 0, wxEXPAND);
	RMSUnit_Holder_OwnAtStart->Add(RMSUnit_OwnAtStart, 1, wxEXPAND);
	RMSUnit_Holder_SetPlaceForAllPlayers->Add(RMSUnit_Text_SetPlaceForAllPlayers, 0, wxEXPAND);
	RMSUnit_Holder_SetPlaceForAllPlayers->Add(RMSUnit_SetPlaceForAllPlayers, 1, wxEXPAND);
	RMSUnit_Holder_MinDistanceToPlayers->Add(RMSUnit_Text_MinDistanceToPlayers, 0, wxEXPAND);
	RMSUnit_Holder_MinDistanceToPlayers->Add(RMSUnit_MinDistanceToPlayers, 1, wxEXPAND);
	RMSUnit_Holder_MaxDistanceToPlayers->Add(RMSUnit_Text_MaxDistanceToPlayers, 0, wxEXPAND);
	RMSUnit_Holder_MaxDistanceToPlayers->Add(RMSUnit_MaxDistanceToPlayers, 1, wxEXPAND);
	RMSUnit_Grid_Unknown1->Add(RMSUnit_Holder_Unit, 1, wxEXPAND);
	RMSUnit_Grid_Unknown1->Add(RMSUnit_Holder_HostTerrain, 1, wxEXPAND);
	RMSUnit_Grid_Unknown1->Add(RMSUnit_Holder_Unknown3, 1, wxEXPAND);
	RMSUnit_Grid_Unknown1->Add(RMSUnit_Holder_ObjectsPerPlayer, 1, wxEXPAND);
	RMSUnit_Grid_Unknown1->Add(RMSUnit_Holder_Unknown5, 1, wxEXPAND);
	RMSUnit_Grid_Unknown1->Add(RMSUnit_Holder_GroupsPerPlayer, 1, wxEXPAND);
	RMSUnit_Grid_Unknown1->Add(RMSUnit_Holder_Unknown7, 1, wxEXPAND);
	RMSUnit_Grid_Unknown1->Add(RMSUnit_Holder_OwnAtStart, 1, wxEXPAND);
	RMSUnit_Grid_Unknown1->Add(RMSUnit_Holder_SetPlaceForAllPlayers, 1, wxEXPAND);
	RMSUnit_Grid_Unknown1->Add(RMSUnit_Holder_MinDistanceToPlayers, 1, wxEXPAND);
	RMSUnit_Grid_Unknown1->Add(RMSUnit_Holder_MaxDistanceToPlayers, 1, wxEXPAND);
	RMSUnit_DataArea->Add(RMSUnit_Grid_Unknown1, 0, wxEXPAND);

	RMSUnit->Add(RMSUnit_ListArea, 1, wxEXPAND);
	RMSUnit->Add(10, -1);
	RMSUnit->Add(RMSUnit_DataArea, 3, wxEXPAND);

	for(short loop = 0; loop < Unknowns_Unknown2.size(); ++loop)
	{
		Unknowns_Holder_Unknown2[loop]->Add(Unknowns_Text_Unknown2[loop], 0, wxEXPAND);
		Unknowns_Holder_Unknown2[loop]->Add(Unknowns_Unknown2[loop], 1, wxEXPAND);
		Unknowns_Grid_Unknown2->Add(Unknowns_Holder_Unknown2[loop], 1, wxEXPAND);
	}

	Unknown_ScrollerWindowsSpace->Add(Unknowns_Space_UnknownLevel, 0, wxEXPAND);
	Unknown_ScrollerWindowsSpace->Add(-1, 5);
	Unknown_ScrollerWindowsSpace->Add(Unknowns_Grid_Unknown1, 0, wxEXPAND);
	Unknown_ScrollerWindowsSpace->Add(-1, 5);
	Unknown_ScrollerWindowsSpace->Add(Unknowns_Space_Pointer1, 0, wxEXPAND);
	Unknown_ScrollerWindowsSpace->Add(-1, 5);
	Unknown_ScrollerWindowsSpace->Add(UnknownFirstSubData, 0, wxEXPAND);
	Unknown_ScrollerWindowsSpace->Add(-1, 5);
	Unknown_ScrollerWindowsSpace->Add(Unknowns_Space_Pointer2, 0, wxEXPAND);
	Unknown_ScrollerWindowsSpace->Add(-1, 5);
	Unknown_ScrollerWindowsSpace->Add(RMSTerrain, 0, wxEXPAND);
	Unknown_ScrollerWindowsSpace->Add(-1, 5);
	Unknown_ScrollerWindowsSpace->Add(Unknowns_Space_Pointer3, 0, wxEXPAND);
	Unknown_ScrollerWindowsSpace->Add(-1, 5);
	Unknown_ScrollerWindowsSpace->Add(RMSUnit, 0, wxEXPAND);
	Unknown_ScrollerWindowsSpace->Add(-1, 5);
	Unknown_ScrollerWindowsSpace->Add(Unknowns_Grid_Unknown2, 0, wxEXPAND);

	Unknown_ScrollerWindows->Add(Unknown_ScrollerWindowsSpace, 1, wxEXPAND);
	Unknown_ScrollerWindows->Add(5, -1);

	Unknown_Scroller->SetSizer(Unknown_ScrollerWindows);
	Unknown_Scroller->SetScrollRate(0, 15);

	Unknowns->Add(Unknowns_ListArea, 1, wxEXPAND);
	Unknowns->Add(10, -1);
	Unknowns->Add(Unknown_Scroller, 3, wxEXPAND);

	Unknown_Area->Add(-1, 10);
	Unknown_Area->Add(Unknown_Grid_UnknownPointer, 0, wxEXPAND);
	Unknown_Area->Add(-1, 10);
	Unknown_Area->Add(Unknowns, 1, wxEXPAND);
	Unknown_Area->Add(-1, 10);

	Unknown_Main->Add(10, -1);
	Unknown_Main->Add(Unknown_Area, 1, wxEXPAND);
	Unknown_Main->Add(10, -1);

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
	Connect(UnknownFirstSubData_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnknownFirstSubDataSearch));
	Connect(UnknownFirstSubData_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnknownFirstSubDataSearch));
	Connect(UnknownFirstSubData_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnknownFirstSubDataSelect));
	Connect(UnknownFirstSubData_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownFirstSubDataAdd));
	Connect(UnknownFirstSubData_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownFirstSubDataInsert));
	Connect(UnknownFirstSubData_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownFirstSubDataDelete));
	Connect(UnknownFirstSubData_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownFirstSubDataCopy));
	Connect(UnknownFirstSubData_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownFirstSubDataPaste));
	Connect(UnknownFirstSubData_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownFirstSubDataPasteInsert));
	Connect(UnknownFirstSubData_CopyToMaps->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownFirstSubDataCopyToMaps));
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

	Unknowns_UnknownLevel->Connect(Unknowns_UnknownLevel->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	UnknownFirstSubData_Unknown1->Connect(UnknownFirstSubData_Unknown1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	RMSTerrain_Unknown1[1]->Connect(RMSTerrain_Unknown1[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	RMSUnit_Unit->Connect(RMSUnit_Unit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
}

void AGE_Frame::OnKillFocus_Unknown(wxFocusEvent &Event)
{
	if(!((AGETextCtrl*)Event.GetEventObject())->SaveEdits()) return;
	if(Event.GetId() == Unknowns_UnknownLevel->GetId())
	{
		ListUnknowns();
	}
	else if(Event.GetId() == UnknownFirstSubData_Unknown1->GetId())
	{
		ListUnknownFirstSubData();
	}
	else if(Event.GetId() == RMSTerrain_Unknown1[1]->GetId())
	{
		ListRMSTerrains();
	}
	else if(Event.GetId() == RMSUnit_Unit->GetId())
	{
		ListRMSUnits();
	}
	Event.Skip();
}
