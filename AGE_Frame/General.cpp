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
	if(Selections > 0)
	{
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
		ListRMSTerrains();
		ListRMSUnits();
	}
	else
	{
		Unknowns_UnknownLevel->ChangeValue("0");
		for(short loop=0; loop < Unknowns_Unknown1.size(); loop++)
		Unknowns_Unknown1[loop]->ChangeValue("0");
		Unknowns_Pointer1->ChangeValue("0");
		Unknowns_Pointer2->ChangeValue("0");
		Unknowns_Pointer3->ChangeValue("0");
		for(short loop=0; loop < Unknowns_Unknown2.size(); loop++)
		Unknowns_Unknown2[loop]->ChangeValue("0");

		UnknownFirstSubData_List->Clear();
		DisableUnknownFirstSubData();
		RMSTerrain_List->Clear();
		DisableRMSTerrains();
		RMSUnit_List->Clear();
		DisableRMSUnits();
	}
	Unknowns_UnknownLevel->Enable(Selections);
	for(short loop=0; loop < Unknowns_Unknown1.size(); loop++)
	Unknowns_Unknown1[loop]->Enable(Selections);
	Unknowns_Pointer1->Enable(Selections);
	Unknowns_Pointer2->Enable(Selections);
	Unknowns_Pointer3->Enable(Selections);
	for(short loop=0; loop < Unknowns_Unknown2.size(); loop++)
	Unknowns_Unknown2[loop]->Enable(Selections);

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
	if(Selections < 1)
	{
		DisableUnknownFirstSubData();
		return;
	}

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
	{
		UnknownFirstSubData_Unknown1[loop]->Enable(true);
		UnknownFirstSubData_Unknown1[loop]->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown1[loop]));
	}
}

void AGE_Frame::DisableUnknownFirstSubData()
{
	for(short loop=0; loop < UnknownFirstSubData_Unknown1.size(); loop++)
	{
		UnknownFirstSubData_Unknown1[loop]->Enable(false);
		UnknownFirstSubData_Unknown1[loop]->ChangeValue("0");
	}
}

void AGE_Frame::OnUnknownFirstSubDataAdd(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count1 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas.size();
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownFirstSubDataInsert(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas, UnknownFSIDs[0]);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count1 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas.size();
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownFirstSubDataDelete(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas, UnknownFSIDs);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count1 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas.size();
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
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count1 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas.size();
	ListUnknownFirstSubData();
}

void AGE_Frame::OnUnknownFirstSubDataPasteInsert(wxCommandEvent &Event)
{
	auto Selections = UnknownFirstSubData_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas, UnknownFSIDs[0], copies->FirstSubData);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count1 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].FirstSubDatas.size();
	ListUnknownFirstSubData();
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

	for(short loop=0; loop < GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas.size(); loop++)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetRMSTerrainName(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas[loop].Unknown1[1]);
		if(SearchMatches(Name.Lower()))
		{
			RMSTerrain_List->Append(Name, (void*)&GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas[loop]);
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
	for(short loop=0; loop < RMSTerrain_Unknown1.size(); loop++)
	RMSTerrain_Unknown1[loop]->resize(Selections);

	genie::SecondSubData * UnknownPointer;
	for(auto sel = Selections; sel--> 0;)
	{
		UnknownPointer = (genie::SecondSubData*)RMSTerrain_List->GetClientData(Items.Item(sel));
		UnknownSSIDs[sel] = (UnknownPointer - (&GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas[0]));

		for(short loop=0; loop < genie::SecondSubData::UNKNOWN1_LEN; loop++)
		RMSTerrain_Unknown1[loop]->container[sel] = &UnknownPointer->Unknown1[loop];
	}

	for(short loop=0; loop < RMSTerrain_Unknown1.size(); loop++)
	{
		RMSTerrain_Unknown1[loop]->Enable(true);
		RMSTerrain_Unknown1[loop]->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown1[loop]));
	}
}

void AGE_Frame::DisableRMSTerrains()
{
	for(short loop=0; loop < RMSTerrain_Unknown1.size(); loop++)
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
	AddToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count2 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainInsert(wxCommandEvent &Event)
{
	auto Selections = RMSTerrain_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas, UnknownSSIDs[0]);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count2 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainDelete(wxCommandEvent &Event)
{
	auto Selections = RMSTerrain_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas, UnknownSSIDs);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count2 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainCopy(wxCommandEvent &Event)
{
	auto Selections = RMSTerrain_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas, UnknownSSIDs, copies->SecondSubData);
}

void AGE_Frame::OnRMSTerrainPaste(wxCommandEvent &Event)
{
	auto Selections = RMSTerrain_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas, UnknownSSIDs, copies->SecondSubData);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count2 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSTerrainPasteInsert(wxCommandEvent &Event)
{
	auto Selections = RMSTerrain_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas, UnknownSSIDs[0], copies->SecondSubData);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count2 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].SecondSubDatas.size();
	ListRMSTerrains();
}

void AGE_Frame::OnRMSUnitSearch(wxCommandEvent &Event)
{
	ListRMSUnits();
}

string AGE_Frame::GetRMSUnitName(short Unit)
{
	return "Unknown "+lexical_cast<string>(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas[Unit].Unknown1[0])+" ";
}

void AGE_Frame::ListRMSUnits()
{
	searchText = RMSUnit_Search->GetValue().Lower();
	excludeText = RMSUnit_Search_R->GetValue().Lower();
	auto Selections = RMSUnit_List->GetSelections(Items);
	RMSUnit_List->Clear();

	for(short loop=0; loop < GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas.size(); loop++)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineUnitName(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas[loop].Unknown1[0]);
		if(SearchMatches(Name.Lower()))
		{
			RMSUnit_List->Append(Name, (void*)&GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas[loop]);
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
	for(short loop=0; loop < RMSUnit_Unknown1.size(); loop++)
	RMSUnit_Unknown1[loop]->resize(Selections);

	genie::ThirdSubData * UnknownPointer;
	for(auto sel = Selections; sel--> 0;)
	{
		UnknownPointer = (genie::ThirdSubData*)RMSUnit_List->GetClientData(Items.Item(sel));
		UnknownTSIDs[sel] = (UnknownPointer - (&GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas[0]));

		for(short loop=0; loop < genie::ThirdSubData::UNKNOWN1_LEN; loop++)
		RMSUnit_Unknown1[loop]->container[sel] = &UnknownPointer->Unknown1[loop];
	}

	for(short loop=0; loop < RMSUnit_Unknown1.size(); loop++)
	{
		RMSUnit_Unknown1[loop]->Enable(true);
		RMSUnit_Unknown1[loop]->ChangeValue(lexical_cast<string>(UnknownPointer->Unknown1[loop]));
	}
}

void AGE_Frame::DisableRMSUnits()
{
	for(short loop=0; loop < RMSUnit_Unknown1.size(); loop++)
	{
		RMSUnit_Unknown1[loop]->Enable(false);
		RMSUnit_Unknown1[loop]->ChangeValue("0");
	}
}

void AGE_Frame::OnRMSUnitAdd(wxCommandEvent &Event)
{
	auto Selections = Unknowns_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count3 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitInsert(wxCommandEvent &Event)
{
	auto Selections = RMSUnit_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas, UnknownTSIDs[0]);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count3 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitDelete(wxCommandEvent &Event)
{
	auto Selections = RMSUnit_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas, UnknownTSIDs);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count3 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitCopy(wxCommandEvent &Event)
{
	auto Selections = RMSUnit_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas, UnknownTSIDs, copies->ThirdSubData);
}

void AGE_Frame::OnRMSUnitPaste(wxCommandEvent &Event)
{
	auto Selections = RMSUnit_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas, UnknownTSIDs, copies->ThirdSubData);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count3 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas.size();
	ListRMSUnits();
}

void AGE_Frame::OnRMSUnitPasteInsert(wxCommandEvent &Event)
{
	auto Selections = RMSUnit_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas, UnknownTSIDs[0], copies->ThirdSubData);
	GenieFile->Unknown.Unknown1stBlocks[UnknownIDs[0]].Count3 = GenieFile->Unknown.Unknown2ndBlocks[UnknownIDs[0]].ThirdSubDatas.size();
	ListRMSUnits();
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
	Unknowns_Text_Pointer1 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Pointer 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
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

	UnknownFirstSubData_Grid_Unknown1 = new wxGridSizer(3, 5, 5);
	for(short loop=0; loop < UnknownFirstSubData_Unknown1.size(); loop++)
	{
		UnknownFirstSubData_Holder_Unknown1[loop] = new wxBoxSizer(wxVERTICAL);
		UnknownFirstSubData_Unknown1[loop] = new TextCtrl_Long(Unknown_Scroller);
	}
	UnknownFirstSubData_Text_Unknown1[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Base Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Spacing Between Players *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Unknown1[2]->SetToolTip("Non-base terrain (like rivers) space between players\nIf too large, it won't be created");
	UnknownFirstSubData_Text_Unknown1[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Min Dist. Between Players *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Unknown1[4]->SetToolTip("Minimum distance in tiles between \"player initial zones\"");
	UnknownFirstSubData_Text_Unknown1[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[6] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[7] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 8", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Text_Unknown1[8] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Players' Start Area Radius *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Unknown1[8]->SetToolTip("This area cannot contain different elevations or terrains\nUnknown 10 affects this too");
	UnknownFirstSubData_Text_Unknown1[9] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 10 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnknownFirstSubData_Unknown1[9]->SetToolTip("Has something to do with players' starting area");
	UnknownFirstSubData_Text_Unknown1[10] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

	Unknowns_Space_Pointer2 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Holder_Pointer2 = new wxBoxSizer(wxVERTICAL);
	Unknowns_Text_Pointer2 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Pointer 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
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

	RMSTerrain_Grid_Unknown1 = new wxGridSizer(3, 5, 5);
	for(short loop=0; loop < RMSTerrain_Unknown1.size(); loop++)
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
	RMSTerrain_Text_Unknown1[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Placement Zone *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSTerrain_Unknown1[4]->SetToolTip("0 Base Zone\n1 Non-base Zone\n6 ?");
	RMSTerrain_Text_Unknown1[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

	Unknowns_Space_Pointer3 = new wxBoxSizer(wxHORIZONTAL);
	Unknowns_Holder_Pointer3 = new wxBoxSizer(wxVERTICAL);
	Unknowns_Text_Pointer3 = new wxStaticText(Unknown_Scroller, wxID_ANY, " Pointer 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
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

	RMSUnit_Grid_Unknown1 = new wxGridSizer(3, 5, 5);
	for(short loop=0; loop < RMSUnit_Unknown1.size(); loop++)
	{
		RMSUnit_Holder_Unknown1[loop] = new wxBoxSizer(wxVERTICAL);
		RMSUnit_Unknown1[loop] = new TextCtrl_Long(Unknown_Scroller);
	}
	RMSUnit_Text_Unknown1[0] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Text_Unknown1[1] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Host Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Text_Unknown1[2] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Text_Unknown1[3] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Objects per Group", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Text_Unknown1[4] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Text_Unknown1[5] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Groups per Player", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Text_Unknown1[6] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Text_Unknown1[7] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Own at Start (-1=Yes) *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Unknown1[7]->SetToolTip("Doesn't work if the unit isn't placed for all players");
	RMSUnit_Text_Unknown1[8] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Set Place for All Players *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Unknown1[8]->SetToolTip("1 = Done once per player\n-1 = Done once, whatever the number of players is\n-2 = same as -1 ? Cannot find a difference");
	RMSUnit_Text_Unknown1[9] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Min Distance to Players", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Text_Unknown1[10] = new wxStaticText(Unknown_Scroller, wxID_ANY, " Max Distance to Players *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	RMSUnit_Unknown1[10]->SetToolTip("- Don't use 0 here for units that are own at start\n- 0 is OK for other units (gold/bushes/gazelle/etc)\n- You can use -1 as a wildcard for units that are own at start");

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

	for(short loop=0; loop < RMSTerrain_Unknown1.size(); loop++)
	{
		RMSTerrain_Holder_Unknown1[loop]->Add(RMSTerrain_Text_Unknown1[loop], 0, wxEXPAND);
		RMSTerrain_Holder_Unknown1[loop]->Add(RMSTerrain_Unknown1[loop], 1, wxEXPAND);
		RMSTerrain_Grid_Unknown1->Add(RMSTerrain_Holder_Unknown1[loop], 1, wxEXPAND);
	}
	RMSTerrain_DataArea->Add(RMSTerrain_Grid_Unknown1, 0, wxEXPAND);

	RMSTerrain->Add(RMSTerrain_ListArea, 1, wxEXPAND);
	RMSTerrain->Add(10, -1);
	RMSTerrain->Add(RMSTerrain_DataArea, 2, wxEXPAND);

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

	for(short loop=0; loop < RMSUnit_Unknown1.size(); loop++)
	{
		RMSUnit_Holder_Unknown1[loop]->Add(RMSUnit_Text_Unknown1[loop], 0, wxEXPAND);
		RMSUnit_Holder_Unknown1[loop]->Add(RMSUnit_Unknown1[loop], 1, wxEXPAND);
		RMSUnit_Grid_Unknown1->Add(RMSUnit_Holder_Unknown1[loop], 1, wxEXPAND);
	}
	RMSUnit_DataArea->Add(RMSUnit_Grid_Unknown1, 0, wxEXPAND);

	RMSUnit->Add(RMSUnit_ListArea, 1, wxEXPAND);
	RMSUnit->Add(10, -1);
	RMSUnit->Add(RMSUnit_DataArea, 2, wxEXPAND);

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
	Connect(RMSTerrain_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainSearch));
	Connect(RMSTerrain_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainSearch));
	Connect(RMSTerrain_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainSelect));
	Connect(RMSTerrain_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainAdd));
	Connect(RMSTerrain_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainInsert));
	Connect(RMSTerrain_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainDelete));
	Connect(RMSTerrain_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainCopy));
	Connect(RMSTerrain_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainPaste));
	Connect(RMSTerrain_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSTerrainPasteInsert));
	Connect(RMSUnit_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSUnitSearch));
	Connect(RMSUnit_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnRMSUnitSearch));
	Connect(RMSUnit_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnRMSUnitSelect));
	Connect(RMSUnit_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitAdd));
	Connect(RMSUnit_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitInsert));
	Connect(RMSUnit_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitDelete));
	Connect(RMSUnit_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitCopy));
	Connect(RMSUnit_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitPaste));
	Connect(RMSUnit_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnRMSUnitPasteInsert));

	Unknowns_UnknownLevel->Connect(Unknowns_UnknownLevel->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	UnknownFirstSubData_Unknown1[0]->Connect(UnknownFirstSubData_Unknown1[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	RMSTerrain_Unknown1[1]->Connect(RMSTerrain_Unknown1[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
	RMSUnit_Unknown1[0]->Connect(RMSUnit_Unknown1[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Unknown), NULL, this);
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
	else if(Event.GetId() == RMSTerrain_Unknown1[1]->GetId())
	{
		ListRMSTerrains();
	}
	else if(Event.GetId() == RMSUnit_Unknown1[0]->GetId())
	{
		ListRMSUnits();
	}
}
