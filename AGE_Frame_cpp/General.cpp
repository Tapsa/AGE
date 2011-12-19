/* AGEFrame_cpp/General.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

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
			LastUnknownsSize = lexical_cast<long>(21642);
			break;
		case 3:
			TechTreeSize = lexical_cast<long>(12722);
			LastUnknownsSize = lexical_cast<long>(27062);
			break;
		case 4:
			TechTreeSize = lexical_cast<long>(698);
			LastUnknownsSize = lexical_cast<long>(89340);
			break;
		case 5:
			TechTreeSize = lexical_cast<long>(698);
			LastUnknownsSize = lexical_cast<long>(116819);
			break;
		default: break;
	}
	General_TechTreeSize->SetLabel("Size: "+lexical_cast<string>(TechTreeSize));
	TechTreePage = lexical_cast<long>(0);
	General_TechTreePicker->ChangeValue(lexical_cast<string>(TechTreePage));
	if(GameVersion >= 2)
	{
		General_LastUnknownsSize->SetLabel("Size: "+lexical_cast<string>(LastUnknownsSize));
		LastUnknownsPage = lexical_cast<long>(0);
		General_LastUnknownsPicker->ChangeValue(lexical_cast<string>(LastUnknownsPage));
	}
	
	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnDataGridPage(wxCommandEvent& Event)
{
	if(Event.GetId() == General_TechTreePicker->GetId())
	{
		TechTreePage = lexical_cast<long>(0);
		if(General_TechTreePicker->IsEmpty())
		TechTreePage = lexical_cast<long>(General_TechTreePicker->GetValue());
		if(TechTreePage >= (TechTreeSize - 256))
		TechTreePage = lexical_cast<long>(TechTreeSize - 256);
		if(TechTreePage < 0)
		TechTreePage = lexical_cast<long>(0);
	}
	if(Event.GetId() == General_LastUnknownsPicker->GetId())
	{
		LastUnknownsPage = lexical_cast<long>(0);
		if(General_LastUnknownsPicker->IsEmpty())
		LastUnknownsPage = lexical_cast<long>(General_LastUnknownsPicker->GetValue());
		if(LastUnknownsPage >= (LastUnknownsSize - 256))
		LastUnknownsPage = lexical_cast<long>(LastUnknownsSize - 256);
		if(LastUnknownsPage < 0)
		LastUnknownsPage = lexical_cast<long>(0);
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
	if(Event.GetId() == General_LastUnknownsNext->GetId())
	{
		LastUnknownsPage += lexical_cast<long>(256);
		if(LastUnknownsPage >= (LastUnknownsSize - 256))
		LastUnknownsPage = lexical_cast<long>(LastUnknownsSize - 256);
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
	if(Event.GetId() == General_LastUnknownsPrev->GetId())
	{
		LastUnknownsPage -= lexical_cast<long>(256);
		if(LastUnknownsPage < 0)
		LastUnknownsPage = lexical_cast<long>(0);
	}

	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnGeneralSelect(wxCommandEvent& Event)
{
//	
	{
		for(short loop = 0;loop < 138;loop++)
		{
			General_TerrainHeader[loop]->ChangeValue(lexical_cast<string>((short)GenieFile->TerrainHeader[loop]));
			General_TerrainHeader[loop]->Container = &GenieFile->TerrainHeader[loop];
		}
		General_TechTreePicker->ChangeValue(lexical_cast<string>(TechTreePage));
		for(long loop = 0;loop < 256;loop++)
		{
			General_TechTree[loop]->ChangeValue(lexical_cast<string>((short)GenieFile->TechTree[loop+TechTreePage]));
			General_TechTree[loop]->Container = &GenieFile->TechTree[loop+TechTreePage];
		}
		if(GameVersion >= 2)
		{
			General_LastUnknownsPicker->ChangeValue(lexical_cast<string>(LastUnknownsPage));
			for(long loop = 0;loop < 256;loop++)
			{
				General_LastUnknowns[loop]->ChangeValue(lexical_cast<string>((short)GenieFile->Unknown1[loop+LastUnknownsPage]));
				General_LastUnknowns[loop]->Container = &GenieFile->Unknown1[loop+LastUnknownsPage];
			}
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
}

void AGE_Frame::CreateGeneralControls()
{
	Tab_General = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	General_Main = new wxBoxSizer(wxVERTICAL);
	General_TopRow = new wxBoxSizer(wxHORIZONTAL);
	General_Refresh = new wxButton(Tab_General, wxID_ANY, "Refresh", wxDefaultPosition, wxSize(-1, 20));
	General_Scroller = new AGE_ScrolledWindow(Tab_General, wxVSCROLL | wxTAB_TRAVERSAL);
	General_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	General_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	General_Holder_TerrainHeader = new wxBoxSizer(wxVERTICAL);
	General_Grid_TerrainHeader = new wxGridSizer(18, 0, 0);
	General_Text_TerrainHeader = new wxStaticText(General_Scroller, wxID_ANY, " Unknown Data, Terrain Header?", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 138;loop++)
	General_TerrainHeader[loop] = new TextCtrl_Byte(General_Scroller, "0", NULL);
	
	General_Grid_Variables = new wxGridSizer(6, 5, 5);
	General_Holder_SUnknown7 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown7 = new wxStaticText(General_Scroller, wxID_ANY, " SW Unkown 7", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown7 = new TextCtrl_Byte(General_Scroller, "0", NULL);
	General_Holder_SUnknown8 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown8 = new wxStaticText(General_Scroller, wxID_ANY, " SW Unkown 8", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown8 = new TextCtrl_Byte(General_Scroller, "0", NULL);
	General_Holder_SUnknown2 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown2 = new wxStaticText(General_Scroller, wxID_ANY, " SW Unkown 2", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown2 = new TextCtrl_Long(General_Scroller, "0", NULL);
	General_Holder_SUnknown3 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown3 = new wxStaticText(General_Scroller, wxID_ANY, " SW Unkown 3", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown3 = new TextCtrl_Long(General_Scroller, "0", NULL);
	General_Holder_SUnknown4 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown4 = new wxStaticText(General_Scroller, wxID_ANY, " SW Unkown 4", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown4 = new TextCtrl_Long(General_Scroller, "0", NULL);
	General_Holder_SUnknown5 = new wxBoxSizer(wxVERTICAL);
	General_Text_SUnknown5 = new wxStaticText(General_Scroller, wxID_ANY, " SW Unkown 5", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_SUnknown5 = new TextCtrl_Long(General_Scroller, "0", NULL);
	
	General_Holder_TechTree = new wxBoxSizer(wxVERTICAL);
	General_Holder_TechTreeTop = new wxBoxSizer(wxHORIZONTAL);
	General_TechTreePicker = new wxTextCtrl(General_Scroller, wxID_ANY);
	General_TechTreeNext = new wxButton(General_Scroller, wxID_ANY, "Next", wxDefaultPosition, wxSize(-1, 20));
	General_TechTreePrev = new wxButton(General_Scroller, wxID_ANY, "Previous", wxDefaultPosition, wxSize(-1, 20));
	General_TechTreeSize = new wxStaticText(General_Scroller, wxID_ANY, " Tech Tree Size", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Grid_TechTree = new wxGridSizer(16, 0, 0);
	General_Text_TechTree = new wxStaticText(General_Scroller, wxID_ANY, " Unknown Data, Tech Tree?", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 256;loop++)
	General_TechTree[loop] = new TextCtrl_Byte(General_Scroller, "0", NULL);

	General_Holder_LastUnknowns = new wxBoxSizer(wxVERTICAL);
	General_Holder_LastUnknownsTop = new wxBoxSizer(wxHORIZONTAL);
	General_LastUnknownsPicker = new wxTextCtrl(General_Scroller, wxID_ANY);
	General_LastUnknownsNext = new wxButton(General_Scroller, wxID_ANY, "Next", wxDefaultPosition, wxSize(-1, 20));
	General_LastUnknownsPrev = new wxButton(General_Scroller, wxID_ANY, "Previous", wxDefaultPosition, wxSize(-1, 20));
	General_LastUnknownsSize = new wxStaticText(General_Scroller, wxID_ANY, " Data Block Size", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Grid_LastUnknowns = new wxGridSizer(16, 0, 0);
	General_Text_LastUnknowns = new wxStaticText(General_Scroller, wxID_ANY, " Unknown Data Block", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 256;loop++)
	General_LastUnknowns[loop] = new TextCtrl_Byte(General_Scroller, "0", NULL);

	General_TopRow->Add(10, -1);
	General_TopRow->Add(General_Refresh, 1, wxEXPAND);
	General_TopRow->AddStretchSpacer(4);
	
	for(short loop = 0;loop < 138;loop++)
	General_Grid_TerrainHeader->Add(General_TerrainHeader[loop], 1, wxEXPAND);
	General_Holder_TerrainHeader->Add(General_Text_TerrainHeader, 0, wxEXPAND);
	General_Holder_TerrainHeader->Add(General_Grid_TerrainHeader, 0, wxEXPAND);

	General_Holder_SUnknown7->Add(General_Text_SUnknown7, 0, wxEXPAND);
	General_Holder_SUnknown7->Add(-1, 2);
	General_Holder_SUnknown7->Add(General_SUnknown7, 1, wxEXPAND);
	General_Holder_SUnknown8->Add(General_Text_SUnknown8, 0, wxEXPAND);
	General_Holder_SUnknown8->Add(-1, 2);
	General_Holder_SUnknown8->Add(General_SUnknown8, 1, wxEXPAND);
	General_Holder_SUnknown2->Add(General_Text_SUnknown2, 0, wxEXPAND);
	General_Holder_SUnknown2->Add(-1, 2);
	General_Holder_SUnknown2->Add(General_SUnknown2, 1, wxEXPAND);
	General_Holder_SUnknown3->Add(General_Text_SUnknown3, 0, wxEXPAND);
	General_Holder_SUnknown3->Add(-1, 2);
	General_Holder_SUnknown3->Add(General_SUnknown3, 1, wxEXPAND);
	General_Holder_SUnknown4->Add(General_Text_SUnknown4, 0, wxEXPAND);
	General_Holder_SUnknown4->Add(-1, 2);
	General_Holder_SUnknown4->Add(General_SUnknown4, 1, wxEXPAND);
	General_Holder_SUnknown5->Add(General_Text_SUnknown5, 0, wxEXPAND);
	General_Holder_SUnknown5->Add(-1, 2);
	General_Holder_SUnknown5->Add(General_SUnknown5, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown2, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown3, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown4, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown5, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown7, 1, wxEXPAND);
	General_Grid_Variables->Add(General_Holder_SUnknown8, 1, wxEXPAND);
	
	General_Holder_TechTreeTop->Add(General_Text_TechTree, 0, wxEXPAND);
	General_Holder_TechTreeTop->Add(5, -1);
	General_Holder_TechTreeTop->Add(General_TechTreePicker, 1, wxEXPAND);
	General_Holder_TechTreeTop->Add(5, -1);
	General_Holder_TechTreeTop->Add(General_TechTreeNext, 1, wxEXPAND);
	General_Holder_TechTreeTop->Add(5, -1);
	General_Holder_TechTreeTop->Add(General_TechTreePrev, 1, wxEXPAND);
	General_Holder_TechTreeTop->Add(5, -1);
	General_Holder_TechTreeTop->Add(General_TechTreeSize, 1, wxEXPAND);
	General_Holder_TechTreeTop->AddStretchSpacer(2);
	for(short loop = 0;loop < 256;loop++)
	General_Grid_TechTree->Add(General_TechTree[loop], 1, wxEXPAND);
	General_Holder_TechTree->Add(General_Holder_TechTreeTop, 0, wxEXPAND);
	General_Holder_TechTree->Add(-1, 5);
	General_Holder_TechTree->Add(General_Grid_TechTree, 0, wxEXPAND);

	General_Holder_LastUnknownsTop->Add(General_Text_LastUnknowns, 0, wxEXPAND);
	General_Holder_LastUnknownsTop->Add(5, -1);
	General_Holder_LastUnknownsTop->Add(General_LastUnknownsPicker, 1, wxEXPAND);
	General_Holder_LastUnknownsTop->Add(5, -1);
	General_Holder_LastUnknownsTop->Add(General_LastUnknownsNext, 1, wxEXPAND);
	General_Holder_LastUnknownsTop->Add(5, -1);
	General_Holder_LastUnknownsTop->Add(General_LastUnknownsPrev, 1, wxEXPAND);
	General_Holder_LastUnknownsTop->Add(5, -1);
	General_Holder_LastUnknownsTop->Add(General_LastUnknownsSize, 1, wxEXPAND);
	General_Holder_LastUnknownsTop->AddStretchSpacer(2);
	for(short loop = 0;loop < 256;loop++)
	General_Grid_LastUnknowns->Add(General_LastUnknowns[loop], 1, wxEXPAND);
	General_Holder_LastUnknowns->Add(General_Holder_LastUnknownsTop, 0, wxEXPAND);
	General_Holder_LastUnknowns->Add(-1, 5);
	General_Holder_LastUnknowns->Add(General_Grid_LastUnknowns, 0, wxEXPAND);

	General_ScrollerWindowsSpace->Add(General_Grid_Variables, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_TerrainHeader, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_TechTree, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_LastUnknowns, 0, wxEXPAND);
	General_ScrollerWindowsSpace->AddStretchSpacer(1);
	
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
	Connect(General_LastUnknownsPicker->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnDataGridPage));
	Connect(General_TechTreeNext->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnDataGridNext));
	Connect(General_LastUnknownsNext->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnDataGridNext));
	Connect(General_TechTreePrev->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnDataGridPrev));
	Connect(General_LastUnknownsPrev->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnDataGridPrev));

}
