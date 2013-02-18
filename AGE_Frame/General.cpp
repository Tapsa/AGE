#include "../AGE_Frame.h"
using boost::lexical_cast;

void AGE_Frame::ListGeneral()
{
	General_SomethingSize->SetLabel("Size: "+lexical_cast<string>(SomethingSize));
	General_SomethingPicker->ChangeValue(lexical_cast<string>(SomethingPage));

	wxCommandEvent E;
	OnGeneralSelect(E);
	
	ListUnknowns();
}

/*void AGE_Frame::OnDataGridPage(wxCommandEvent &Event)
{
	SomethingPage = 0;
	if(!General_SomethingPicker->IsEmpty())
	SomethingPage = lexical_cast<long>(General_SomethingPicker->GetValue());
	if(SomethingPage >= (SomethingSize - 128))
	SomethingPage = SomethingSize - 128;
	if(SomethingPage < 0)
	SomethingPage = 0;

	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnDataGridNext(wxCommandEvent &Event)
{
	SomethingPage += 128;
	if(SomethingPage >= (SomethingSize - 128))
	SomethingPage = SomethingSize - 128;

	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnDataGridPrev(wxCommandEvent &Event)
{
	SomethingPage -= 128;
	if(SomethingPage < 0)
	SomethingPage = 0;

	wxCommandEvent E;
	OnGeneralSelect(E);
}*/

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
	General_SomethingPicker->ChangeValue(lexical_cast<string>(SomethingPage));
	/*wxString Info = lexical_cast<string>(GenieFile->Unknown.Pointer)+", size: ";
	for(int loop = 0; loop < GenieFile->Unknown.Unknown1stBlocks.size(); loop++)
	{
		Info.Append("\n\nItem: "+lexical_cast<string>(loop)+"\n");
		for(int loop2 = 0; loop2 < genie::Unknown1stBlock::UNKNOWN1_LEN; loop2++)
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown1stBlocks[loop].Unknown1[loop2])+" ");
		Info.Append("\n"+lexical_cast<string>(GenieFile->Unknown.Unknown1stBlocks[loop].Pointer1)+", size: ");
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown1stBlocks[loop].Count1)+", ");
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown1stBlocks[loop].Pointer2)+", size: ");
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown1stBlocks[loop].Count2)+", ");
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown1stBlocks[loop].Pointer3)+", size: ");
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown1stBlocks[loop].Count3)+"    ");
		for(int loop2 = 0; loop2 < genie::Unknown1stBlock::UNKNOWN2_LEN; loop2++)
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown1stBlocks[loop].Unknown2[loop2])+" ");

		Info.Append("\n");
		for(int loop2 = 0; loop2 < genie::Unknown2ndBlock::UNKNOWN3_LEN; loop2++)
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown2ndBlocks[loop].Unknown3[loop2])+" ");
		Info.Append("\n"+lexical_cast<string>(GenieFile->Unknown.Unknown2ndBlocks[loop].Pointer1)+", size: ");
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown2ndBlocks[loop].FirstSubDatas.size())+", ");
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown2ndBlocks[loop].Pointer2)+", size: ");
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown2ndBlocks[loop].SecondSubDatas.size())+", ");
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown2ndBlocks[loop].Pointer3)+", size: ");
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown2ndBlocks[loop].ThirdSubDatas.size())+"    ");
		for(int loop2 = 0; loop2 < genie::Unknown2ndBlock::UNKNOWN4_LEN; loop2++)
		Info.Append(lexical_cast<string>(GenieFile->Unknown.Unknown2ndBlocks[loop].Unknown4[loop2])+" ");
	}
	wxMessageBox(Info);*/
	if(GameVersion < 2) return;
	for(short loop=1; loop < General_AfterBorders.size(); loop++)
	{
		General_AfterBorders[loop]->ChangeValue(lexical_cast<string>(GenieFile->ZeroSpace[loop]));
		General_AfterBorders[loop]->resize(1);
		General_AfterBorders[loop]->container[0] = &GenieFile->ZeroSpace[loop];
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

string AGE_Frame::GetUnknownName(short Index)
{
	return "Unknown "+lexical_cast<string>(GenieFile->Unknown.Unknown1stBlocks[Index].Unknown1[0])+" ";
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

	//wxCommandEvent E;
	//OnPlayerColorsSelect(E);
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
	General_Grid_Variables2 = new wxGridSizer(8, 5, 5);
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
	General_Holder_RenderPlusUnknown = new wxBoxSizer(wxVERTICAL);
	General_Holder_RenderPlusUnknownTop = new wxBoxSizer(wxHORIZONTAL);
	General_SomethingPicker = new wxTextCtrl(General_Scroller, wxID_ANY);
	General_SomethingNext = new wxButton(General_Scroller, wxID_ANY, "Next", wxDefaultPosition, wxSize(0, 20));
	General_SomethingPrev = new wxButton(General_Scroller, wxID_ANY, "Previous", wxDefaultPosition, wxSize(0, 20));
	General_SomethingSize = new wxStaticText(General_Scroller, wxID_ANY, " Data Size", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	//General_Grid_TechTree = new wxGridSizer(8, 0, 0);
	General_Text_TechTree = new wxStaticText(General_Scroller, wxID_ANY, " Unknown Data with 32 Bit Pointers", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	//for(short loop=0; loop < General_Something.size(); loop++)
	//General_Something[loop] = new TextCtrl_Long(General_Scroller);

	Unknowns = new wxStaticBoxSizer(wxHORIZONTAL, General_Scroller, "Unknown Removable Data Only Required in AoE 1");
	Unknowns_ListArea = new wxBoxSizer(wxVERTICAL);
	Unknowns_DataArea = new wxBoxSizer(wxVERTICAL);
	Unknowns_Search = new wxTextCtrl(General_Scroller, wxID_ANY);
	Unknowns_Search_R = new wxTextCtrl(General_Scroller, wxID_ANY);
	Unknowns_List = new wxListBox(General_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 220), 0, NULL, wxLB_EXTENDED);
	Unknowns_Buttons = new wxGridSizer(3, 0, 0);
	Unknowns_Add = new wxButton(General_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Insert = new wxButton(General_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Delete = new wxButton(General_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Copy = new wxButton(General_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Unknowns_Paste = new wxButton(General_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Unknowns_PasteInsert = new wxButton(General_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	UnknownFirstSubData = new wxStaticBoxSizer(wxHORIZONTAL, General_Scroller, "First Subdata");
	UnknownFirstSubData_ListArea = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_DataArea = new wxBoxSizer(wxVERTICAL);
	UnknownFirstSubData_Search = new wxTextCtrl(General_Scroller, wxID_ANY);
	UnknownFirstSubData_Search_R = new wxTextCtrl(General_Scroller, wxID_ANY);
	UnknownFirstSubData_List = new wxListBox(General_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	UnknownFirstSubData_Buttons = new wxGridSizer(3, 0, 0);
	UnknownFirstSubData_Add = new wxButton(General_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnknownFirstSubData_Insert = new wxButton(General_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	UnknownFirstSubData_Delete = new wxButton(General_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnknownFirstSubData_Copy = new wxButton(General_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnknownFirstSubData_Paste = new wxButton(General_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	UnknownFirstSubData_PasteInsert = new wxButton(General_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	UnknownSecondSubData = new wxStaticBoxSizer(wxHORIZONTAL, General_Scroller, "Second Subdata");
	UnknownSecondSubData_ListArea = new wxBoxSizer(wxVERTICAL);
	UnknownSecondSubData_DataArea = new wxBoxSizer(wxVERTICAL);
	UnknownSecondSubData_Search = new wxTextCtrl(General_Scroller, wxID_ANY);
	UnknownSecondSubData_Search_R = new wxTextCtrl(General_Scroller, wxID_ANY);
	UnknownSecondSubData_List = new wxListBox(General_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	UnknownSecondSubData_Buttons = new wxGridSizer(3, 0, 0);
	UnknownSecondSubData_Add = new wxButton(General_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnknownSecondSubData_Insert = new wxButton(General_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	UnknownSecondSubData_Delete = new wxButton(General_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnknownSecondSubData_Copy = new wxButton(General_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnknownSecondSubData_Paste = new wxButton(General_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	UnknownSecondSubData_PasteInsert = new wxButton(General_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	UnknownThirdSubData = new wxStaticBoxSizer(wxHORIZONTAL, General_Scroller, "Third Subdata");
	UnknownThirdSubData_ListArea = new wxBoxSizer(wxVERTICAL);
	UnknownThirdSubData_DataArea = new wxBoxSizer(wxVERTICAL);
	UnknownThirdSubData_Search = new wxTextCtrl(General_Scroller, wxID_ANY);
	UnknownThirdSubData_Search_R = new wxTextCtrl(General_Scroller, wxID_ANY);
	UnknownThirdSubData_List = new wxListBox(General_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	UnknownThirdSubData_Buttons = new wxGridSizer(3, 0, 0);
	UnknownThirdSubData_Add = new wxButton(General_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnknownThirdSubData_Insert = new wxButton(General_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	UnknownThirdSubData_Delete = new wxButton(General_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnknownThirdSubData_Copy = new wxButton(General_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnknownThirdSubData_Paste = new wxButton(General_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	UnknownThirdSubData_PasteInsert = new wxButton(General_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	General_Holder_Variables2 = new wxStaticBoxSizer(wxVERTICAL, General_Scroller, "Technology Tree Related?");
	for(short loop=0; loop < General_TTUnknown.size(); loop++)
	{
		General_Holder_TTUnknown[loop] = new wxBoxSizer(wxVERTICAL);
		General_Text_TTUnknown[loop] = new wxStaticText(General_Scroller, wxID_ANY, " Unkown "+lexical_cast<string>(loop+1), wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		General_TTUnknown[loop] = new TextCtrl_Long(General_Scroller);
	}
	General_TTUnknown[7]->SetToolTip("In the file this is\nright after technology tree ages and\nbefore rest of the tech tree data");

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
	General_Holder_TerrainRendering->Add(General_Text_TerrainRendering, 0, wxEXPAND);
	General_Holder_TerrainRendering->Add(General_Grid_TerrainRendering, 0, wxEXPAND);

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
	for(short loop=0; loop < General_TTUnknown.size(); loop++)
	{
		General_Holder_TTUnknown[loop]->Add(General_Text_TTUnknown[loop], 0, wxEXPAND);
		General_Holder_TTUnknown[loop]->Add(General_TTUnknown[loop], 0, wxEXPAND);
	}
	General_Grid_Variables->Add(General_Holder_SUnknown2, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown3, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown4, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown5, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown7, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown8, 1, wxEXPAND);
	General_Holder_Variables1->Add(General_Grid_Variables, 0, wxEXPAND);
	for(short loop=0; loop < General_TTUnknown.size(); loop++)
	General_Grid_Variables2->Add(General_Holder_TTUnknown[loop], 1, wxEXPAND);
	General_Holder_Variables2->Add(General_Grid_Variables2, 0, wxEXPAND);

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
	//for(short loop=0; loop < General_Something.size(); loop++)
	//General_Grid_TechTree->Add(General_Something[loop], 1, wxEXPAND);
	General_Holder_RenderPlusUnknown->Add(General_Holder_RenderPlusUnknownTop, 0, wxEXPAND);
	//General_Holder_RenderPlusUnknown->Add(General_Grid_TechTree, 0, wxEXPAND);

	Unknowns_Buttons->Add(Unknowns_Add, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Insert, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Delete, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Copy, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_Paste, 1, wxEXPAND);
	Unknowns_Buttons->Add(Unknowns_PasteInsert, 1, wxEXPAND);

	Unknowns_ListArea->Add(Unknowns_Search, 0, wxEXPAND);
	Unknowns_ListArea->Add(Unknowns_Search_R, 0, wxEXPAND);
	Unknowns_ListArea->Add(-1, 2);
	Unknowns_ListArea->Add(Unknowns_List, 0, wxEXPAND);
	Unknowns_ListArea->Add(-1, 2);
	Unknowns_ListArea->Add(Unknowns_Buttons, 0, wxEXPAND);

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

	UnknownFirstSubData->Add(UnknownFirstSubData_ListArea, 1, wxEXPAND);
	UnknownFirstSubData->Add(10, -1);
	UnknownFirstSubData->Add(UnknownFirstSubData_DataArea, 2, wxEXPAND);

	UnknownSecondSubData->Add(UnknownSecondSubData_ListArea, 1, wxEXPAND);
	UnknownSecondSubData->Add(10, -1);
	UnknownSecondSubData->Add(UnknownSecondSubData_DataArea, 2, wxEXPAND);

	UnknownThirdSubData->Add(UnknownThirdSubData_ListArea, 1, wxEXPAND);
	UnknownThirdSubData->Add(10, -1);
	UnknownThirdSubData->Add(UnknownThirdSubData_DataArea, 2, wxEXPAND);

	Unknowns_DataArea->Add(UnknownFirstSubData, 1, wxEXPAND);
	Unknowns_DataArea->Add(10, -1);
	Unknowns_DataArea->Add(UnknownSecondSubData, 1, wxEXPAND);
	Unknowns_DataArea->Add(10, -1);
	Unknowns_DataArea->Add(UnknownThirdSubData, 1, wxEXPAND);

	Unknowns->Add(Unknowns_ListArea, 1, wxEXPAND);
	Unknowns->Add(10, -1);
	Unknowns->Add(Unknowns_DataArea, 3, wxEXPAND);

	General_ScrollerWindowsSpace->Add(General_Holder_Variables1, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_TerrainHeader, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_BorderRelated, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_TerrainRendering, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_RenderPlusUnknown, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(Unknowns, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_Variables2, 0, wxEXPAND);

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
