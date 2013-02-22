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
}

void AGE_Frame::OnGeneralSelect(wxCommandEvent &Event)
{
	for(short loop=0; loop < General_TerrainHeader.size(); loop++)
	{
		General_TerrainHeader[loop]->ChangeValue(lexical_cast<string>(GenieFile->GraphicsRendering[loop]));
		General_TerrainHeader[loop]->resize(1);
		General_TerrainHeader[loop]->container[0] = &GenieFile->GraphicsRendering[loop];
	}
	General_BeforeBorders->ChangeValue(lexical_cast<string>(GenieFile->Unknown2));
	General_BeforeBorders->resize(1);
	General_BeforeBorders->container[0] = &GenieFile->Unknown2;
	General_AfterBorders[0]->ChangeValue(lexical_cast<string>(GenieFile->ZeroSpace[0]));
	General_AfterBorders[0]->resize(1);
	General_AfterBorders[0]->container[0] = &GenieFile->ZeroSpace[0];
	for(short loop=0; loop < General_TerrainRendering.size(); loop++)
	{
		General_TerrainRendering[loop]->ChangeValue(lexical_cast<string>(GenieFile->Rendering[loop]));
		General_TerrainRendering[loop]->resize(1);
		General_TerrainRendering[loop]->container[0] = &GenieFile->Rendering[loop];
	}
	for(short loop=0; loop < 6; loop++)
	{
		General_Something[loop]->ChangeValue(lexical_cast<string>(GenieFile->Something[loop]));
		General_Something[loop]->resize(1);
		General_Something[loop]->container[0] = &GenieFile->Something[loop];
	}
	Unknown_UnknownPointer->ChangeValue(lexical_cast<string>(GenieFile->Unknown.Pointer));
	Unknown_UnknownPointer->resize(1);
	Unknown_UnknownPointer->container[0] = &GenieFile->Unknown.Pointer;
	if(GameVersion < 2) return;
	for(short loop=1; loop < General_AfterBorders.size(); loop++)
	{
		General_AfterBorders[loop]->ChangeValue(lexical_cast<string>(GenieFile->ZeroSpace[loop]));
		General_AfterBorders[loop]->resize(1);
		General_AfterBorders[loop]->container[0] = &GenieFile->ZeroSpace[loop];
	}
	for(short loop=6; loop < 162; loop++)
	{
		General_Something[loop]->ChangeValue(lexical_cast<string>(GenieFile->Something[loop]));
		General_Something[loop]->resize(1);
		General_Something[loop]->container[0] = &GenieFile->Something[loop];
	}
	for(long loop = 0;loop < General_TTUnknown.size(); loop++)
	{
		General_TTUnknown[loop]->ChangeValue(lexical_cast<string>(GenieFile->UnknownPreTechTree[loop]));
		General_TTUnknown[loop]->resize(1);
		General_TTUnknown[loop]->container[0] = &GenieFile->UnknownPreTechTree[loop];
	}
	General_TTUnknown[7]->ChangeValue(lexical_cast<string>(GenieFile->TechTree.Unknown2));
	General_TTUnknown[7]->resize(1);
	General_TTUnknown[7]->container[0] = &GenieFile->TechTree.Unknown2;
	if(GameVersion < 4) return;
	General_Something[162]->ChangeValue(lexical_cast<string>(GenieFile->Something[162]));
	General_Something[162]->resize(1);
	General_Something[162]->container[0] = &GenieFile->Something[162];
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
	for(short loop=0; loop < 5; loop++)
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
	for(short loop=0; loop < General_TerrainHeader.size(); loop++)
	General_TerrainHeader[loop] = new TextCtrl_Short(General_Scroller);
	General_BeforeBorders = new TextCtrl_Short(General_Scroller);
	General_BeforeBorders->SetToolTip("In the file this is\nright after terrains and\nbefore terrain borders");
	for(short loop=0; loop < General_AfterBorders.size(); loop++)
	{
		General_AfterBorders[loop] = new TextCtrl_Long(General_Scroller);
		General_AfterBorders[loop]->SetToolTip("In the file these are\nright after terrain borders and\nbefore the second terrain count");
	}
	for(short loop=0; loop < General_TerrainRendering.size(); loop++)
	General_TerrainRendering[loop] = new TextCtrl_Short(General_Scroller);
	for(short loop=0; loop < General_Something.size(); loop++)
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
	for(short loop=0; loop < 4; loop++)
	General_TopRow->Add(General_CalcBoxes[loop], 1, wxEXPAND);
	General_TopRow->Add(General_Text_CalcBoxesMiddle, 0, wxEXPAND);
	General_TopRow->Add(General_CalcBoxes[4], 1, wxEXPAND);
	General_TopRow->Add(General_Text_CalcBoxes, 0, wxEXPAND);
	General_TopRow->AddStretchSpacer(1);

	for(short loop=0; loop < General_TerrainHeader.size(); loop++)
	General_Grid_TerrainHeader->Add(General_TerrainHeader[loop], 1, wxEXPAND);
	General_Holder_TerrainHeader->Add(General_Text_TerrainHeader, 0, wxEXPAND);
	General_Holder_TerrainHeader->Add(General_Grid_TerrainHeader, 0, wxEXPAND);

	General_Grid_BorderRelated->Add(General_BeforeBorders, 1, wxEXPAND);
	for(short loop=0; loop < General_AfterBorders.size(); loop++)
	General_Grid_BorderRelated->Add(General_AfterBorders[loop], 1, wxEXPAND);
	General_Holder_BorderRelated->Add(General_Text_BorderRelated, 0, wxEXPAND);
	General_Holder_BorderRelated->Add(General_Grid_BorderRelated, 0, wxEXPAND);

	for(short loop=0; loop < General_TerrainRendering.size(); loop++)
	General_Grid_TerrainRendering->Add(General_TerrainRendering[loop], 1, wxEXPAND);
	for(short loop=0; loop < General_Something.size(); loop++)
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
	for(short loop=0; loop < 4; loop++)
	General_CalcBoxes[loop]->Connect(General_CalcBoxes[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnVariableCalc), NULL, this);
	General_CalcBoxes[4]->Connect(General_CalcBoxes[4]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnVariableCalcReverse), NULL, this);
}

void AGE_Frame::OnUnknownsSearch(wxCommandEvent &Event)
{
	ListUnknowns();
}

string AGE_Frame::GetUnknownName(short Index)
{
	return "Unknown "+lexical_cast<string>(GenieFile->Unknown.Unknown1stBlocks[Index].UnknownLevel)+" ";
}

void AGE_Frame::ListUnknowns()
{
	searchText = Unknowns_Search->GetValue().Lower();
	excludeText = Unknowns_Search_R->GetValue().Lower();

	auto Selections = Unknowns_List->GetSelections(Items);
	Unknowns_List->Clear();

	for(short loop=0; loop < GenieFile->Unknown.Unknown1stBlocks.size(); loop++)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnknownName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Unknowns_List->Append(Name, (void*)&GenieFile->Unknown.Unknown2ndBlocks[loop]);
		}
	}

	ListingFix(Selections, Unknowns_List);

	wxCommandEvent E;
	OnUnknownsSelect(E);
}

void AGE_Frame::OnUnknownsSelect(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	UnknownIDs.resize(Selections);
	Unknowns_UnknownLevel->resize(Selections);
	int PointerCount = Selections * 2;
	for(short loop=0; loop < Unknowns_Unknown1.size(); loop++)
	Unknowns_Unknown1[loop]->resize(PointerCount);
	Unknowns_Pointer1->resize(PointerCount);
	Unknowns_Pointer2->resize(PointerCount);
	Unknowns_Pointer3->resize(PointerCount);
	for(short loop=0; loop < Unknowns_Unknown2.size(); loop++)
	Unknowns_Unknown2[loop]->resize(PointerCount);

	genie::Unknown1stBlock * UnknownPointer1;
	genie::Unknown2ndBlock * UnknownPointer2;
	for(auto sel = Selections; sel--> 0;)
	{
		UnknownPointer2 = (genie::Unknown2ndBlock*)Unknowns_List->GetClientData(Items.Item(sel));
		UnknownIDs[sel] = (UnknownPointer2 - (&GenieFile->Unknown.Unknown2ndBlocks[0]));
		UnknownPointer1 = &GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[sel]];

		Unknowns_UnknownLevel->container[sel] = &UnknownPointer1->UnknownLevel;
		int sel2 = sel + Selections;
		for(short loop=0; loop < genie::Unknown1stBlock::UNKNOWN1_LEN; loop++)
		{
			Unknowns_Unknown1[loop]->container[sel] = &UnknownPointer1->Unknown1[loop];
			Unknowns_Unknown1[loop]->container[sel2] = &UnknownPointer2->Unknown1[loop];
		}
		Unknowns_Pointer1->container[sel] = &UnknownPointer1->Pointer1;
		Unknowns_Pointer1->container[sel2] = &UnknownPointer2->Pointer1;
		Unknowns_Pointer2->container[sel] = &UnknownPointer1->Pointer2;
		Unknowns_Pointer2->container[sel2] = &UnknownPointer2->Pointer2;
		Unknowns_Pointer3->container[sel] = &UnknownPointer1->Pointer3;
		Unknowns_Pointer3->container[sel2] = &UnknownPointer2->Pointer3;
		for(short loop=0; loop < genie::Unknown1stBlock::UNKNOWN2_LEN; loop++)
		{
			Unknowns_Unknown2[loop]->container[sel] = &UnknownPointer1->Unknown2[loop];
			Unknowns_Unknown2[loop]->container[sel2] = &UnknownPointer2->Unknown2[loop];
		}
	}

	Unknowns_UnknownLevel->ChangeValue(lexical_cast<string>(UnknownPointer1->UnknownLevel));
	for(short loop=0; loop < Unknowns_Unknown1.size(); loop++)
	Unknowns_Unknown1[loop]->ChangeValue(lexical_cast<string>(UnknownPointer1->Unknown1[loop]));
	Unknowns_Pointer1->ChangeValue(lexical_cast<string>(UnknownPointer1->Pointer1));
	Unknowns_Pointer2->ChangeValue(lexical_cast<string>(UnknownPointer1->Pointer2));
	Unknowns_Pointer3->ChangeValue(lexical_cast<string>(UnknownPointer1->Pointer3));
	for(short loop=0; loop < Unknowns_Unknown2.size(); loop++)
	Unknowns_Unknown2[loop]->ChangeValue(lexical_cast<string>(UnknownPointer1->Unknown2[loop]));

	ListUnknownFirstSubData();
	ListUnknownSecondSubData();
	ListUnknownThirdSubData();
}

void AGE_Frame::OnUnknownsAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->Unknown.Unknown1stBlocks);
	AddToListNoGV(GenieFile->Unknown.Unknown2ndBlocks);
	ListUnknowns();
}

void AGE_Frame::OnUnknownsInsert(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->Unknown.Unknown1stBlocks, UnknownIDs[0]);
	InsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks, UnknownIDs[0]);
	ListUnknowns();
}

void AGE_Frame::OnUnknownsDelete(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Unknown.Unknown1stBlocks, UnknownIDs);
	DeleteFromList(GenieFile->Unknown.Unknown2ndBlocks, UnknownIDs);
	ListUnknowns();
}

void AGE_Frame::OnUnknownsCopy(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Unknown.Unknown1stBlocks, UnknownIDs, copies->Unknown1stBlock);
	CopyFromList(GenieFile->Unknown.Unknown2ndBlocks, UnknownIDs, copies->Unknown2ndBlock);
}

void AGE_Frame::OnUnknownsPaste(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->Unknown.Unknown1stBlocks, UnknownIDs, copies->Unknown1stBlock);
	PasteToListNoGV(GenieFile->Unknown.Unknown2ndBlocks, UnknownIDs, copies->Unknown2ndBlock);
	ListUnknowns();
}

void AGE_Frame::OnUnknownsPasteInsert(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->Unknown.Unknown1stBlocks, UnknownIDs[0], copies->Unknown1stBlock);
	PasteInsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks, UnknownIDs[0], copies->Unknown2ndBlock);
	ListUnknowns();
}

void AGE_Frame::OnUnknownFirstSubDataSearch(wxCommandEvent &Event)
{
	ListUnknownFirstSubData();
}

string AGE_Frame::GetUnknownFirstSubDataName(short Index)
{
	return "Unknown "+lexical_cast<string>(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas[Index].Unknown1[0])+" ";
}

void AGE_Frame::ListUnknownFirstSubData()
{
	searchText = UnknownFirstSubData_Search->GetValue().Lower();
	excludeText = UnknownFirstSubData_Search_R->GetValue().Lower();
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	UnknownFirstSubData_List->Clear();

	for(short loop=0; loop < GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas.size(); loop++)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnknownFirstSubDataName(loop);
		if(SearchMatches(Name.Lower()))
		{
			UnknownFirstSubData_List->Append(Name, (void*)&GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas[loop]);
		}
	}
	ListingFix(Selections, UnknownFirstSubData_List);

	wxCommandEvent E;
	OnUnknownFirstSubDataSelect(E);
}

void AGE_Frame::OnUnknownFirstSubDataSelect(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	UnknownFSIDs.resize(Selections);
	for(short loop=0; loop < UnknownFirstSubData_Unknown1.size(); loop++)
	UnknownFirstSubData_Unknown1[loop]->resize(Selections);

	genie::FirstSubData * UnknownPointer;
	for(auto sel = Selections; sel--> 0;)
	{
		UnknownPointer = (genie::FirstSubData*)UnknownFirstSubData_List->GetClientData(Items.Item(sel));
		UnknownFSIDs[sel] = (UnknownPointer - (&GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas[0]));

		for(short loop=0; loop < genie::FirstSubData::UNKNOWN1_LEN; loop++)
		UnknownFirstSubData_Unknown1[loop]->container[sel] = &UnknownPointer->Unknown1[loop];
	}

	for(short loop=0; loop < UnknownFirstSubData_Unknown1.size(); loop++)
	UnknownFirstSubData_Unknown1[loop]->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown1[loop]));
}

void AGE_Frame::OnUnknownFirstSubDataAdd(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas);
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownFirstSubDataInsert(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas, UnknownFSIDs[0]);
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownFirstSubDataDelete(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas, UnknownFSIDs);
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownFirstSubDataCopy(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas, UnknownFSIDs, copies->FirstSubData);
}

void AGE_Frame::OnUnknownFirstSubDataPaste(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas, UnknownFSIDs, copies->FirstSubData);
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownFirstSubDataPasteInsert(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas, UnknownFSIDs[0], copies->FirstSubData);
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownSecondSubDataSearch(wxCommandEvent &Event)
{
	ListUnknownSecondSubData();
}

string AGE_Frame::GetSimpleTerrainName(short Terrain)
{
	string Name = lexical_cast<string>(Terrain)+" ";
	if(GenieFile->Terrains.size() <= Terrain) return Name + "Nonexistent Terrain";
	if(!GenieFile->Terrains[Terrain].Name.empty())
	{
		return Name + GenieFile->Terrains[Terrain].Name;
	}
	return Name + "New Terrain";
}

void AGE_Frame::ListUnknownSecondSubData()
{
	searchText = UnknownSecondSubData_Search->GetValue().Lower();
	excludeText = UnknownSecondSubData_Search_R->GetValue().Lower();
	auto Selections = UnknownSecondSubData_List->GetSelections(Items);
	UnknownSecondSubData_List->Clear();

	for(short loop=0; loop < GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas.size(); loop++)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetSimpleTerrainName(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas[loop].Unknown1[1]);
		if(SearchMatches(Name.Lower()))
		{
			UnknownSecondSubData_List->Append(Name, (void*)&GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas[loop]);
		}
	}
	ListingFix(Selections, UnknownSecondSubData_List);

	wxCommandEvent E;
	OnUnknownSecondSubDataSelect(E);
}

void AGE_Frame::OnUnknownSecondSubDataSelect(wxCommandEvent &Event)
{
	auto Selections = UnknownSecondSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	UnknownSSIDs.resize(Selections);
	for(short loop=0; loop < UnknownSecondSubData_Unknown1.size(); loop++)
	UnknownSecondSubData_Unknown1[loop]->resize(Selections);

	genie::SecondSubData * UnknownPointer;
	for(auto sel = Selections; sel--> 0;)
	{
		UnknownPointer = (genie::SecondSubData*)UnknownSecondSubData_List->GetClientData(Items.Item(sel));
		UnknownSSIDs[sel] = (UnknownPointer - (&GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas[0]));

		for(short loop=0; loop < genie::SecondSubData::UNKNOWN1_LEN; loop++)
		UnknownSecondSubData_Unknown1[loop]->container[sel] = &UnknownPointer->Unknown1[loop];
	}

	for(short loop=0; loop < UnknownSecondSubData_Unknown1.size(); loop++)
	UnknownSecondSubData_Unknown1[loop]->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown1[loop]));
}

void AGE_Frame::OnUnknownSecondSubDataAdd(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas);
	ListUnknownSecondSubData();
}

void AGE_Frame::OnUnknownSecondSubDataInsert(wxCommandEvent &Event)
{
	auto Selections = UnknownSecondSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas, UnknownSSIDs[0]);
	ListUnknownSecondSubData();
}

void AGE_Frame::OnUnknownSecondSubDataDelete(wxCommandEvent &Event)
{
	auto Selections = UnknownSecondSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas, UnknownSSIDs);
	ListUnknownSecondSubData();
}

void AGE_Frame::OnUnknownSecondSubDataCopy(wxCommandEvent &Event)
{
	auto Selections = UnknownSecondSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas, UnknownSSIDs, copies->SecondSubData);
}

void AGE_Frame::OnUnknownSecondSubDataPaste(wxCommandEvent &Event)
{
	auto Selections = UnknownSecondSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas, UnknownSSIDs, copies->SecondSubData);
	ListUnknownSecondSubData();
}

void AGE_Frame::OnUnknownSecondSubDataPasteInsert(wxCommandEvent &Event)
{
	auto Selections = UnknownSecondSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas, UnknownSSIDs[0], copies->SecondSubData);
	ListUnknownSecondSubData();
}

void AGE_Frame::OnUnknownThirdSubDataSearch(wxCommandEvent &Event)
{
	ListUnknownThirdSubData();
}

string AGE_Frame::GetUnknownThirdSubDataName(short Index)
{
	return "Unknown "+lexical_cast<string>(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas[Index].Unknown1[0])+" ";
}

void AGE_Frame::ListUnknownThirdSubData()
{
	searchText = UnknownThirdSubData_Search->GetValue().Lower();
	excludeText = UnknownThirdSubData_Search_R->GetValue().Lower();
	auto Selections = UnknownThirdSubData_List->GetSelections(Items);
	UnknownThirdSubData_List->Clear();

	for(short loop=0; loop < GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas.size(); loop++)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineUnitName(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas[loop].Unknown1[0]);
		if(SearchMatches(Name.Lower()))
		{
			UnknownThirdSubData_List->Append(Name, (void*)&GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas[loop]);
		}
	}
	ListingFix(Selections, UnknownThirdSubData_List);

	wxCommandEvent E;
	OnUnknownThirdSubDataSelect(E);
}

void AGE_Frame::OnUnknownThirdSubDataSelect(wxCommandEvent &Event)
{
	auto Selections = UnknownThirdSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	UnknownTSIDs.resize(Selections);
	for(short loop=0; loop < UnknownThirdSubData_Unknown1.size(); loop++)
	UnknownThirdSubData_Unknown1[loop]->resize(Selections);

	genie::ThirdSubData * UnknownPointer;
	for(auto sel = Selections; sel--> 0;)
	{
		UnknownPointer = (genie::ThirdSubData*)UnknownThirdSubData_List->GetClientData(Items.Item(sel));
		UnknownTSIDs[sel] = (UnknownPointer - (&GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas[0]));

		for(short loop=0; loop < genie::ThirdSubData::UNKNOWN1_LEN; loop++)
		UnknownThirdSubData_Unknown1[loop]->container[sel] = &UnknownPointer->Unknown1[loop];
	}

	for(short loop=0; loop < UnknownThirdSubData_Unknown1.size(); loop++)
	UnknownThirdSubData_Unknown1[loop]->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown1[loop]));
}

void AGE_Frame::OnUnknownThirdSubDataAdd(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas);
	ListUnknownThirdSubData();
}

void AGE_Frame::OnUnknownThirdSubDataInsert(wxCommandEvent &Event)
{
	auto Selections = UnknownThirdSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas, UnknownTSIDs[0]);
	ListUnknownThirdSubData();
}

void AGE_Frame::OnUnknownThirdSubDataDelete(wxCommandEvent &Event)
{
	auto Selections = UnknownThirdSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas, UnknownTSIDs);
	ListUnknownThirdSubData();
}

void AGE_Frame::OnUnknownThirdSubDataCopy(wxCommandEvent &Event)
{
	auto Selections = UnknownThirdSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas, UnknownTSIDs, copies->ThirdSubData);
}

void AGE_Frame::OnUnknownThirdSubDataPaste(wxCommandEvent &Event)
{
	auto Selections = UnknownThirdSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas, UnknownTSIDs, copies->ThirdSubData);
	ListUnknownThirdSubData();
}

void AGE_Frame::OnUnknownThirdSubDataPasteInsert(wxCommandEvent &Event)
{
	auto Selections = UnknownThirdSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas, UnknownTSIDs[0], copies->ThirdSubData);
	ListUnknownThirdSubData();
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
	Unknown_Text_UnknownPointer = new wxStaticText(Tab_Unknown, wxID_ANY, " Unknown Pointer", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
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
	Unknowns_Text_UnknownLevel = new wxStaticText(Unknown_Scroller, wxID_ANY, " Level", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_UnknownLevel = new TextCtrl_Long(Unknown_Scroller);
	Unknowns_Grid_Unknown1 = new wxGridSizer(5, 5, 5);
	for(short loop=0; loop < Unknowns_Unknown1.size(); loop++)
	{
		Unknowns_Holder_Unknown1[loop] = new wxBoxSizer(wxVERTICAL);
		Unknowns_Unknown1[loop] = new TextCtrl_Long(Unknown_Scroller);
	}
	Unknowns_Text_Unknown1[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Southwest Border", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Text_Unknown1[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Northwest Border", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Text_Unknown1[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Northeast Border", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Text_Unknown1[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Southeast Border", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Text_Unknown1[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Border Usage % *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[4]->SetToolTip("% of border area covered with border terrain");
	Unknowns_Text_Unknown1[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Water Shape?", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Text_Unknown1[6] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Default Terrain *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Unknown1[6]->SetToolTip("Used on the borders as well");
	Unknowns_Text_Unknown1[7] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Terrain Coverage", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Text_Unknown1[8] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 9", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Space_Pointer1 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Holder_Pointer1 = new wxBoxSizer(wxVERTICAL);
	Unknowns_Text_Pointer1 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Pointer 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Pointer1 = new TextCtrl_Long(Unknown_Scroller);

	UnknownFirstSubData = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Base Terrain Data");
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

	UnknownFirstSubData_Grid_Unknown1 = new wxGridSizer(3, 5, 5);
	for(short loop=0; loop < UnknownFirstSubData_Unknown1.size(); loop++)
	{
		UnknownFirstSubData_Holder_Unknown1[loop] = new wxBoxSizer(wxVERTICAL);
		UnknownFirstSubData_Unknown1[loop] = new TextCtrl_Long(Unknown_Scroller);
	}
	UnknownFirstSubData_Text_Unknown1[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[6] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[7] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 8", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[8] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Min Open Place %?", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[9] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 10", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[10] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

	Unknowns_Space_Pointer2 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Holder_Pointer2 = new wxBoxSizer(wxVERTICAL);
	Unknowns_Text_Pointer2 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Pointer 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Pointer2 = new TextCtrl_Long(Unknown_Scroller);

	UnknownSecondSubData = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Terrains Placed on the Map");
	UnknownSecondSubData_ListArea = new wxBoxSizer(wxVERTICAL);
	UnknownSecondSubData_DataArea = new wxBoxSizer(wxVERTICAL);
	UnknownSecondSubData_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	UnknownSecondSubData_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	UnknownSecondSubData_List = new wxListBox(Unknown_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	UnknownSecondSubData_Buttons = new wxGridSizer(3, 0, 0);
	UnknownSecondSubData_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnknownSecondSubData_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	UnknownSecondSubData_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnknownSecondSubData_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnknownSecondSubData_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	UnknownSecondSubData_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	UnknownSecondSubData_Grid_Unknown1 = new wxGridSizer(3, 5, 5);
	for(short loop=0; loop < UnknownSecondSubData_Unknown1.size(); loop++)
	{
		UnknownSecondSubData_Holder_Unknown1[loop] = new wxBoxSizer(wxVERTICAL);
		UnknownSecondSubData_Unknown1[loop] = new TextCtrl_Long(Unknown_Scroller);
	}
	UnknownSecondSubData_Text_Unknown1[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Proportion", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownSecondSubData_Text_Unknown1[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownSecondSubData_Text_Unknown1[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Number of Clumps", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownSecondSubData_Text_Unknown1[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Spacing to Other Terrains", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownSecondSubData_Text_Unknown1[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Placement Zone *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownSecondSubData_Unknown1[4]->SetToolTip("0 Base Zone\n1 Default/Border Zone\n6 ?");
	UnknownSecondSubData_Text_Unknown1[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

	Unknowns_Space_Pointer3 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Holder_Pointer3 = new wxBoxSizer(wxVERTICAL);
	Unknowns_Text_Pointer3 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Pointer 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Unknowns_Pointer3 = new TextCtrl_Long(Unknown_Scroller);

	UnknownThirdSubData = new wxStaticBoxSizer(wxHORIZONTAL, Unknown_Scroller, "Units Placed on the Map");
	UnknownThirdSubData_ListArea = new wxBoxSizer(wxVERTICAL);
	UnknownThirdSubData_DataArea = new wxBoxSizer(wxVERTICAL);
	UnknownThirdSubData_Search = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	UnknownThirdSubData_Search_R = new wxTextCtrl(Unknown_Scroller, wxID_ANY);
	UnknownThirdSubData_List = new wxListBox(Unknown_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 250), 0, NULL, wxLB_EXTENDED);
	UnknownThirdSubData_Buttons = new wxGridSizer(3, 0, 0);
	UnknownThirdSubData_Add = new wxButton(Unknown_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnknownThirdSubData_Insert = new wxButton(Unknown_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	UnknownThirdSubData_Delete = new wxButton(Unknown_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnknownThirdSubData_Copy = new wxButton(Unknown_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnknownThirdSubData_Paste = new wxButton(Unknown_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	UnknownThirdSubData_PasteInsert = new wxButton(Unknown_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	UnknownThirdSubData_Grid_Unknown1 = new wxGridSizer(3, 5, 5);
	for(short loop=0; loop < UnknownThirdSubData_Unknown1.size(); loop++)
	{
		UnknownThirdSubData_Holder_Unknown1[loop] = new wxBoxSizer(wxVERTICAL);
		UnknownThirdSubData_Unknown1[loop] = new TextCtrl_Long(Unknown_Scroller);
	}
	UnknownThirdSubData_Text_Unknown1[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownThirdSubData_Text_Unknown1[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Terrain Restriction", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownThirdSubData_Text_Unknown1[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownThirdSubData_Text_Unknown1[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Number of Objects", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownThirdSubData_Text_Unknown1[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownThirdSubData_Text_Unknown1[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Number of Groups", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownThirdSubData_Text_Unknown1[6] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownThirdSubData_Text_Unknown1[7] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Own at Start (-1=Yes)", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownThirdSubData_Text_Unknown1[8] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 9", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownThirdSubData_Text_Unknown1[9] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Min Distance to Players", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownThirdSubData_Text_Unknown1[10] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Max Distance to Players", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

	Unknowns_Grid_Unknown2 = new wxGridSizer(5, 5, 5);
	for(short loop=0; loop < Unknowns_Unknown2.size(); loop++)
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

	for(short loop=0; loop < Unknowns_Unknown1.size(); loop++)
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

	for(short loop=0; loop < UnknownFirstSubData_Unknown1.size(); loop++)
	{
		UnknownFirstSubData_Holder_Unknown1[loop]->Add(UnknownFirstSubData_Text_Unknown1[loop], 0, wxEXPAND);
		UnknownFirstSubData_Holder_Unknown1[loop]->Add(UnknownFirstSubData_Unknown1[loop], 1, wxEXPAND);
		UnknownFirstSubData_Grid_Unknown1->Add(UnknownFirstSubData_Holder_Unknown1[loop], 1, wxEXPAND);
	}
	UnknownFirstSubData_DataArea->Add(UnknownFirstSubData_Grid_Unknown1, 0, wxEXPAND);

	UnknownFirstSubData->Add(UnknownFirstSubData_ListArea, 1, wxEXPAND);
	UnknownFirstSubData->Add(10, -1);
	UnknownFirstSubData->Add(UnknownFirstSubData_DataArea, 2, wxEXPAND);

	Unknowns_Holder_Pointer2->Add(Unknowns_Text_Pointer2, 0, wxEXPAND);
	Unknowns_Holder_Pointer2->Add(Unknowns_Pointer2, 1, wxEXPAND);
	Unknowns_Space_Pointer2->Add(Unknowns_Holder_Pointer2, 1, wxEXPAND);
	Unknowns_Space_Pointer2->AddStretchSpacer(3);

	UnknownSecondSubData_Buttons->Add(UnknownSecondSubData_Add, 1, wxEXPAND);
	UnknownSecondSubData_Buttons->Add(UnknownSecondSubData_Insert, 1, wxEXPAND);
	UnknownSecondSubData_Buttons->Add(UnknownSecondSubData_Delete, 1, wxEXPAND);
	UnknownSecondSubData_Buttons->Add(UnknownSecondSubData_Copy, 1, wxEXPAND);
	UnknownSecondSubData_Buttons->Add(UnknownSecondSubData_Paste, 1, wxEXPAND);
	UnknownSecondSubData_Buttons->Add(UnknownSecondSubData_PasteInsert, 1, wxEXPAND);

	UnknownSecondSubData_ListArea->Add(UnknownSecondSubData_Search, 0, wxEXPAND);
	UnknownSecondSubData_ListArea->Add(UnknownSecondSubData_Search_R, 0, wxEXPAND);
	UnknownSecondSubData_ListArea->Add(-1, 2);
	UnknownSecondSubData_ListArea->Add(UnknownSecondSubData_List, 1, wxEXPAND);
	UnknownSecondSubData_ListArea->Add(-1, 2);
	UnknownSecondSubData_ListArea->Add(UnknownSecondSubData_Buttons, 0, wxEXPAND);

	for(short loop=0; loop < UnknownSecondSubData_Unknown1.size(); loop++)
	{
		UnknownSecondSubData_Holder_Unknown1[loop]->Add(UnknownSecondSubData_Text_Unknown1[loop], 0, wxEXPAND);
		UnknownSecondSubData_Holder_Unknown1[loop]->Add(UnknownSecondSubData_Unknown1[loop], 1, wxEXPAND);
		UnknownSecondSubData_Grid_Unknown1->Add(UnknownSecondSubData_Holder_Unknown1[loop], 1, wxEXPAND);
	}
	UnknownSecondSubData_DataArea->Add(UnknownSecondSubData_Grid_Unknown1, 0, wxEXPAND);

	UnknownSecondSubData->Add(UnknownSecondSubData_ListArea, 1, wxEXPAND);
	UnknownSecondSubData->Add(10, -1);
	UnknownSecondSubData->Add(UnknownSecondSubData_DataArea, 2, wxEXPAND);

	Unknowns_Holder_Pointer3->Add(Unknowns_Text_Pointer3, 0, wxEXPAND);
	Unknowns_Holder_Pointer3->Add(Unknowns_Pointer3, 1, wxEXPAND);
	Unknowns_Space_Pointer3->Add(Unknowns_Holder_Pointer3, 1, wxEXPAND);
	Unknowns_Space_Pointer3->AddStretchSpacer(3);

	UnknownThirdSubData_Buttons->Add(UnknownThirdSubData_Add, 1, wxEXPAND);
	UnknownThirdSubData_Buttons->Add(UnknownThirdSubData_Insert, 1, wxEXPAND);
	UnknownThirdSubData_Buttons->Add(UnknownThirdSubData_Delete, 1, wxEXPAND);
	UnknownThirdSubData_Buttons->Add(UnknownThirdSubData_Copy, 1, wxEXPAND);
	UnknownThirdSubData_Buttons->Add(UnknownThirdSubData_Paste, 1, wxEXPAND);
	UnknownThirdSubData_Buttons->Add(UnknownThirdSubData_PasteInsert, 1, wxEXPAND);

	UnknownThirdSubData_ListArea->Add(UnknownThirdSubData_Search, 0, wxEXPAND);
	UnknownThirdSubData_ListArea->Add(UnknownThirdSubData_Search_R, 0, wxEXPAND);
	UnknownThirdSubData_ListArea->Add(-1, 2);
	UnknownThirdSubData_ListArea->Add(UnknownThirdSubData_List, 1, wxEXPAND);
	UnknownThirdSubData_ListArea->Add(-1, 2);
	UnknownThirdSubData_ListArea->Add(UnknownThirdSubData_Buttons, 0, wxEXPAND);

	for(short loop=0; loop < UnknownThirdSubData_Unknown1.size(); loop++)
	{
		UnknownThirdSubData_Holder_Unknown1[loop]->Add(UnknownThirdSubData_Text_Unknown1[loop], 0, wxEXPAND);
		UnknownThirdSubData_Holder_Unknown1[loop]->Add(UnknownThirdSubData_Unknown1[loop], 1, wxEXPAND);
		UnknownThirdSubData_Grid_Unknown1->Add(UnknownThirdSubData_Holder_Unknown1[loop], 1, wxEXPAND);
	}
	UnknownThirdSubData_DataArea->Add(UnknownThirdSubData_Grid_Unknown1, 0, wxEXPAND);

	UnknownThirdSubData->Add(UnknownThirdSubData_ListArea, 1, wxEXPAND);
	UnknownThirdSubData->Add(10, -1);
	UnknownThirdSubData->Add(UnknownThirdSubData_DataArea, 2, wxEXPAND);

	for(short loop=0; loop < Unknowns_Unknown2.size(); loop++)
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
	Unknown_ScrollerWindowsSpace->Add(UnknownSecondSubData, 0, wxEXPAND);
	Unknown_ScrollerWindowsSpace->Add(-1, 5);
	Unknown_ScrollerWindowsSpace->Add(Unknowns_Space_Pointer3, 0, wxEXPAND);
	Unknown_ScrollerWindowsSpace->Add(-1, 5);
	Unknown_ScrollerWindowsSpace->Add(UnknownThirdSubData, 0, wxEXPAND);
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
	Connect(UnknownSecondSubData_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnknownSecondSubDataSearch));
	Connect(UnknownSecondSubData_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnknownSecondSubDataSearch));
	Connect(UnknownSecondSubData_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnknownSecondSubDataSelect));
	Connect(UnknownSecondSubData_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownSecondSubDataAdd));
	Connect(UnknownSecondSubData_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownSecondSubDataInsert));
	Connect(UnknownSecondSubData_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownSecondSubDataDelete));
	Connect(UnknownSecondSubData_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownSecondSubDataCopy));
	Connect(UnknownSecondSubData_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownSecondSubDataPaste));
	Connect(UnknownSecondSubData_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownSecondSubDataPasteInsert));
	Connect(UnknownThirdSubData_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnknownThirdSubDataSearch));
	Connect(UnknownThirdSubData_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnknownThirdSubDataSearch));
	Connect(UnknownThirdSubData_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnknownThirdSubDataSelect));
	Connect(UnknownThirdSubData_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownThirdSubDataAdd));
	Connect(UnknownThirdSubData_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownThirdSubDataInsert));
	Connect(UnknownThirdSubData_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownThirdSubDataDelete));
	Connect(UnknownThirdSubData_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownThirdSubDataCopy));
	Connect(UnknownThirdSubData_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownThirdSubDataPaste));
	Connect(UnknownThirdSubData_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnknownThirdSubDataPasteInsert));

	Unknowns_UnknownLevel->Connect(Unknowns_UnknownLevel->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	UnknownFirstSubData_Unknown1[0]->Connect(UnknownFirstSubData_Unknown1[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	UnknownSecondSubData_Unknown1[1]->Connect(UnknownSecondSubData_Unknown1[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	UnknownThirdSubData_Unknown1[0]->Connect(UnknownThirdSubData_Unknown1[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
}

void AGE_Frame::OnKillFocus_Unknown(wxFocusEvent &Event)
{
	if(!((AGETextCtrl*)Event.GetEventObject())->SaveEdits()) return;
	if(Event.GetId() == Unknowns_UnknownLevel->GetId())
	{
		ListUnknowns();
	}
	else if(Event.GetId() == UnknownFirstSubData_Unknown1[0]->GetId())
	{
		ListUnknownFirstSubData();
	}
	else if(Event.GetId() == UnknownSecondSubData_Unknown1[1]->GetId())
	{
		ListUnknownSecondSubData();
	}
	else if(Event.GetId() == UnknownThirdSubData_Unknown1[0]->GetId())
	{
		ListUnknownThirdSubData();
	}
}
