/* AGEFrame_cpp/General.cpp */

#include "../AGE_Frame.h"
using boost::lexical_cast;

void AGE_Frame::ListGeneral()
{
	switch(GameVersion)
	{
		case 0:
			TechTreeSize = lexical_cast<long>(6946);
			break;
		case 1:
			TechTreeSize = lexical_cast<long>(15118);
			break;
		case 2:
			TechTreeSize = lexical_cast<long>(12722);
			break;
		case 3:
			TechTreeSize = lexical_cast<long>(12722);
			break;
		case 4:
			TechTreeSize = lexical_cast<long>(698);
			break;
		case 5:
			TechTreeSize = lexical_cast<long>(698);
			break;
		default: break;
	}
	General_TechTreeSize->SetLabel("Size: "+lexical_cast<string>(TechTreeSize));
	TechTreePage = lexical_cast<long>(0);
	General_TechTreePicker->ChangeValue(lexical_cast<string>(TechTreePage));

	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnDataGridPage(wxCommandEvent& Event)
{
	if(Event.GetId() == General_TechTreePicker->GetId())
	{
		TechTreePage = lexical_cast<long>(0);
		if(!General_TechTreePicker->IsEmpty())
		TechTreePage = lexical_cast<long>(General_TechTreePicker->GetValue());
		if(TechTreePage >= (TechTreeSize - 256))
		TechTreePage = lexical_cast<long>(TechTreeSize - 256);
		if(TechTreePage < 0)
		TechTreePage = lexical_cast<long>(0);
	}

	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnDataGridNext(wxCommandEvent& Event)
{
	if(Event.GetId() == General_TechTreeNext->GetId())
	{
		TechTreePage += lexical_cast<long>(256);
		if(TechTreePage >= (TechTreeSize - 256))
		TechTreePage = lexical_cast<long>(TechTreeSize - 256);
	}

	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnDataGridPrev(wxCommandEvent& Event)
{
	if(Event.GetId() == General_TechTreePrev->GetId())
	{
		TechTreePage -= lexical_cast<long>(256);
		if(TechTreePage < 0)
		TechTreePage = lexical_cast<long>(0);

	}

	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnVariableCalc(wxFocusEvent& Event)
{
	long Result, Temp;

	if(!General_CalcBoxes[0]->IsEmpty())
	Result = lexical_cast<short>(General_CalcBoxes[0]->GetValue());
	else Result = 0;
	if(Result < 0)
	Result = (unsigned char)Result;

	if(!General_CalcBoxes[1]->IsEmpty())
	Temp = lexical_cast<short>(General_CalcBoxes[1]->GetValue());
	else Temp = 0;
	if(Temp < 0)
	Temp = (unsigned char)Temp;
	Result = Result + 256 * Temp;

	if(!General_CalcBoxes[2]->IsEmpty())
	Temp = lexical_cast<short>(General_CalcBoxes[2]->GetValue());
	else Temp = 0;
	if(Temp < 0)
	Temp = (unsigned char)Temp;
	Result = Result + 65536 * Temp;

	if(!General_CalcBoxes[3]->IsEmpty())
	Temp = lexical_cast<short>(General_CalcBoxes[3]->GetValue());
	else Temp = 0;
	if(Temp < 0)
	Temp = (unsigned char)Temp;
	Result = Result + 16777216 * Temp;

	General_CalcBoxes[4]->ChangeValue("= "+lexical_cast<string>(Result));
}

void AGE_Frame::OnGeneralSelect(wxCommandEvent& Event)
{
//
	{
		for(short loop = 0;loop < 138;loop++)
		{
			General_TerrainHeader[loop]->ChangeValue(lexical_cast<string>((short)GenieFile->GraphicsRendering[loop]));
			General_TerrainHeader[loop]->Container = &GenieFile->GraphicsRendering[loop];
		}
		General_TechTreePicker->ChangeValue(lexical_cast<string>(TechTreePage));
		for(long loop = 0;loop < 256;loop++)
		{
			General_TechTree[loop]->ChangeValue(lexical_cast<string>((short)GenieFile->RenderingPlusSomething[loop+TechTreePage]));
			General_TechTree[loop]->Container = &GenieFile->RenderingPlusSomething[loop+TechTreePage];
		}
		if(GameVersion >= 2)
		{
			for(long loop = 0;loop < 7;loop++)
			{
				General_TTUnknown[loop]->ChangeValue(lexical_cast<string>(GenieFile->UnknownPreTechTree[loop]));
				General_TTUnknown[loop]->Container = &GenieFile->UnknownPreTechTree[loop];
			}
			General_TTUnknown[7]->ChangeValue(lexical_cast<string>(GenieFile->TechTree.Unknown2));
			General_TTUnknown[7]->Container = &GenieFile->TechTree.Unknown2;
			if(GameVersion >= 4)
			{
				General_SUnknown2->ChangeValue(lexical_cast<string>(GenieFile->SUnknown2));
				General_SUnknown2->Container = &GenieFile->SUnknown2;
				General_SUnknown3->ChangeValue(lexical_cast<string>(GenieFile->SUnknown3));
				General_SUnknown3->Container = &GenieFile->SUnknown3;
				General_SUnknown4->ChangeValue(lexical_cast<string>(GenieFile->SUnknown4));
				General_SUnknown4->Container = &GenieFile->SUnknown4;
				General_SUnknown5->ChangeValue(lexical_cast<string>(GenieFile->SUnknown5));
				General_SUnknown5->Container = &GenieFile->SUnknown5;
				General_SUnknown7->ChangeValue(lexical_cast<string>((short)GenieFile->SUnknown7));
				General_SUnknown7->Container = &GenieFile->SUnknown7;
				General_SUnknown8->ChangeValue(lexical_cast<string>((short)GenieFile->SUnknown8));
				General_SUnknown8->Container = &GenieFile->SUnknown8;
			}
		}
	}
//	for(long loop = 0;loop < LastUnknownsSize;loop++)
//	GenieFile->TechTrees[loop] = 0;
}

void AGE_Frame::CreateGeneralControls()
{
	Tab_General = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	General_Main = new wxBoxSizer(wxVERTICAL);
	General_TopRow = new wxBoxSizer(wxHORIZONTAL);
	General_Refresh = new wxButton(Tab_General, wxID_ANY, "Refresh", wxDefaultPosition, wxSize(0, 20));
	General_Text_CalcBoxes = new wxStaticText(Tab_General, wxID_ANY, " Variable Converter", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 5;loop++)
	General_CalcBoxes[loop] = new wxTextCtrl(Tab_General, wxID_ANY);
	General_Scroller = new wxScrolledWindow(Tab_General, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	General_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	General_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);

	General_Grid_Variables = new wxGridSizer(6, 5, 5);
	General_Grid_Variables2 = new wxGridSizer(8, 5, 5);
	General_Holder_Variables1 = new wxStaticBoxSizer(wxVERTICAL, General_Scroller, "Star Wars Unknowns");
	General_Holder_SUnknown2 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown2 = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown2 = new TextCtrl_Long(General_Scroller, "0", NULL);
	General_Holder_SUnknown3 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown3 = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown3 = new TextCtrl_Long(General_Scroller, "0", NULL);
	General_Holder_SUnknown4 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown4 = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown4 = new TextCtrl_Long(General_Scroller, "0", NULL);
	General_Holder_SUnknown5 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown5 = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown5 = new TextCtrl_Long(General_Scroller, "0", NULL);
	General_Holder_SUnknown7 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown7 = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown7 = new TextCtrl_Byte(General_Scroller, "0", NULL);
	General_Holder_SUnknown8 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown8 = new wxStaticText(General_Scroller, wxID_ANY, " Unkown 8", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown8 = new TextCtrl_Byte(General_Scroller, "0", NULL);
	General_Holder_TerrainHeader = new wxBoxSizer(wxVERTICAL);
	General_Grid_TerrainHeader = new wxGridSizer(18, 0, 0);
	General_Text_TerrainHeader = new wxStaticText(General_Scroller, wxID_ANY, " Graphics-related", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 138;loop++)
	General_TerrainHeader[loop] = new TextCtrl_Byte(General_Scroller, "0", NULL);
	General_Holder_RenderPlusUnknown = new wxBoxSizer(wxVERTICAL);
	General_Holder_RenderPlusUnknownTop = new wxBoxSizer(wxHORIZONTAL);
	General_TechTreePicker = new wxTextCtrl(General_Scroller, wxID_ANY);
	General_TechTreeNext = new wxButton(General_Scroller, wxID_ANY, "Next", wxDefaultPosition, wxSize(0, 20));
	General_TechTreePrev = new wxButton(General_Scroller, wxID_ANY, "Previous", wxDefaultPosition, wxSize(0, 20));
	General_TechTreeSize = new wxStaticText(General_Scroller, wxID_ANY, " Data Size", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Grid_TechTree = new wxGridSizer(16, 0, 0);
	General_Text_TechTree = new wxStaticText(General_Scroller, wxID_ANY, " Graphics-related + Unknown Data", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 256;loop++)
	General_TechTree[loop] = new TextCtrl_Byte(General_Scroller, "0", NULL);

	General_Holder_Variables2 = new wxStaticBoxSizer(wxVERTICAL, General_Scroller, "Technology Tree Related?");
	for(short loop = 0;loop < 8;loop++)
	{
		General_Holder_TTUnknown[loop] = new wxBoxSizer(wxVERTICAL);
		General_TTUnknown[loop] = new TextCtrl_Long(General_Scroller, "0", NULL);
		General_Text_TTUnknown[loop] = new wxStaticText(General_Scroller, wxID_ANY, " Unkown "+lexical_cast<string>(loop+1), wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	}

	General_TopRow->Add(10, -1);
	General_TopRow->Add(General_Refresh, 2, wxEXPAND);
	General_TopRow->AddStretchSpacer(3);
	for(short loop = 0;loop < 5;loop++)
	General_TopRow->Add(General_CalcBoxes[loop], 1, wxEXPAND);
	General_TopRow->Add(General_Text_CalcBoxes, 0, wxEXPAND);
	General_TopRow->AddStretchSpacer(1);

	for(short loop = 0;loop < 138;loop++)
	General_Grid_TerrainHeader->Add(General_TerrainHeader[loop], 1, wxEXPAND);
	General_Holder_TerrainHeader->Add(General_Text_TerrainHeader, 0, wxEXPAND);
	General_Holder_TerrainHeader->Add(General_Grid_TerrainHeader, 0, wxEXPAND);

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
	for(short loop = 0;loop < 8;loop++)
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
	for(short loop = 0;loop < 8;loop++)
	General_Grid_Variables2->Add(General_Holder_TTUnknown[loop], 1, wxEXPAND);
	General_Holder_Variables2->Add(General_Grid_Variables2, 0, wxEXPAND);

	General_Holder_RenderPlusUnknownTop->Add(General_Text_TechTree, 0, wxEXPAND);
	General_Holder_RenderPlusUnknownTop->Add(5, -1);
	General_Holder_RenderPlusUnknownTop->Add(General_TechTreePicker, 1, wxEXPAND);
	General_Holder_RenderPlusUnknownTop->Add(5, -1);
	General_Holder_RenderPlusUnknownTop->Add(General_TechTreeNext, 1, wxEXPAND);
	General_Holder_RenderPlusUnknownTop->Add(5, -1);
	General_Holder_RenderPlusUnknownTop->Add(General_TechTreePrev, 1, wxEXPAND);
	General_Holder_RenderPlusUnknownTop->Add(5, -1);
	General_Holder_RenderPlusUnknownTop->Add(General_TechTreeSize, 1, wxEXPAND);
	General_Holder_RenderPlusUnknownTop->AddStretchSpacer(2);
	for(short loop = 0;loop < 256;loop++)
	General_Grid_TechTree->Add(General_TechTree[loop], 1, wxEXPAND);
	General_Holder_RenderPlusUnknown->Add(General_Holder_RenderPlusUnknownTop, 0, wxEXPAND);
	General_Holder_RenderPlusUnknown->Add(-1, 5);
	General_Holder_RenderPlusUnknown->Add(General_Grid_TechTree, 0, wxEXPAND);

	General_ScrollerWindowsSpace->Add(General_Holder_Variables1, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_TerrainHeader, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_RenderPlusUnknown, 0, wxEXPAND);
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
	Connect(General_TechTreePicker->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnDataGridPage));
	Connect(General_TechTreeNext->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnDataGridNext));
	Connect(General_TechTreePrev->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnDataGridPrev));
	for(short loop = 0;loop < 4;loop++)
	General_CalcBoxes[loop]->Connect(General_CalcBoxes[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnVariableCalc), NULL, this);

}
