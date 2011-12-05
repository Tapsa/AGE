/* AGEFrame_cpp/General.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

void AGE_Frame::ListGeneral()
{
	switch(GameVersion) // is this really the techtree?
	{
		case 0: TechTreeSize = lexical_cast<long>(6952); break;
		case 1: TechTreeSize = lexical_cast<long>(15124); break;
		case 2: TechTreeSize = lexical_cast<long>(12752); break;
		case 3: TechTreeSize = lexical_cast<long>(12752); break;
		case 4: TechTreeSize = lexical_cast<long>(728); break;
		case 5: TechTreeSize = lexical_cast<long>(728); break;
		default: break;
	}
	General_TechTreeSize->SetLabel("Size: "+lexical_cast<string>(TechTreeSize));
	TechTreePage = lexical_cast<long>(0);
	General_TechTreePicker->ChangeValue(lexical_cast<string>(TechTreePage));
	
	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnTechTreePage(wxCommandEvent& Event)
{
	if(General_TechTreePicker->IsEmpty())
	TechTreePage = lexical_cast<long>(0);
	TechTreePage = lexical_cast<long>(General_TechTreePicker->GetValue());
	if(TechTreePage >= (TechTreeSize - 324))
	TechTreePage = lexical_cast<long>(TechTreeSize - 324);
	if(TechTreePage < 0)
	TechTreePage = lexical_cast<long>(0);
	
	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnTechTreeNext(wxCommandEvent& Event)
{
	TechTreePage += lexical_cast<long>(324);
	if(TechTreePage >= (TechTreeSize - 324))
	TechTreePage = lexical_cast<long>(TechTreeSize - 324);
	
	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnTechTreePrev(wxCommandEvent& Event)
{
	TechTreePage -= lexical_cast<long>(324);
	if(TechTreePage < 0)
	TechTreePage = lexical_cast<long>(0);
	
	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnGeneralSelect(wxCommandEvent& Event)
{
/*	short Selection = Terrains_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Terrains_Terrains_List->GetCount() - 1;
			Terrains_Terrains_List->SetSelection(Selection);
		}
		gdat::File * FilePointer = (gdat::File*)Terrains_Terrains_List->GetClientData(Selection);
		TerrainID = TerrainPointer - (&GenieFile->Terrains[0]);*/
		for(short loop = 0;loop < 138;loop++)
		{
			General_TerrainHeader[loop]->ChangeValue(lexical_cast<string>((short)GenieFile->TerrainHeader[loop]));
			General_TerrainHeader[loop]->Container = &GenieFile->TerrainHeader[loop];
		}
		General_TechTreePicker->ChangeValue(lexical_cast<string>(TechTreePage));
		for(long loop = 0;loop < 324;loop++)
		{
		//	wxMessageBox(lexical_cast<string>(loop+TechTreePage));
			General_TechTree[loop]->ChangeValue(lexical_cast<string>((short)GenieFile->TechTree[loop+TechTreePage]));
			General_TechTree[loop]->Container = &GenieFile->TechTree[loop+TechTreePage];
		}
/*		Terrains_Unknown2->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown2));
		Terrains_Unknown2->Container = &TerrainPointer->Unknown2;
		if(GameVersion >= 2)
		{
			Terrains_Holder_BlendPriority->Show(true);
			Terrains_Holder_BlendType->Show(true);
			
			Terrains_BlendPriority->ChangeValue(lexical_cast<string>(TerrainPointer->BlendPriority));
			Terrains_BlendPriority->Container = &TerrainPointer->BlendPriority;
			Terrains_BlendType->ChangeValue(lexical_cast<string>(TerrainPointer->BlendType));
			Terrains_BlendType->Container = &TerrainPointer->BlendType;
		}
		else
		{
			Terrains_Holder_BlendPriority->Show(false);
			Terrains_Holder_BlendType->Show(false);
		}

	}*/
}

void AGE_Frame::CreateGeneralControls()
{
	Tab_General = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(-1, 350));

	General_Main = new wxBoxSizer(wxVERTICAL);
	General_TopRow = new wxBoxSizer(wxHORIZONTAL);
	General_Refresh = new wxButton(Tab_General, wxID_ANY, "Refresh", wxDefaultPosition, wxSize(-1, 20));
	General_Scroller = new AGE_ScrolledWindow(Tab_General, wxVSCROLL | wxTAB_TRAVERSAL);
	General_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	General_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	General_Holder_TerrainHeader = new wxBoxSizer(wxVERTICAL);
	General_Grid_TerrainHeader = new wxGridSizer(12, 0, 0);
	General_Text_TerrainHeader = new wxStaticText(General_Scroller, wxID_ANY, " Unknown Data, Terrain Header?", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 138;loop++)
	General_TerrainHeader[loop] = new TextCtrl_Byte(General_Scroller, "0", NULL);
	
	General_Holder_TechTree = new wxBoxSizer(wxVERTICAL);
	General_Holder_TechTreeTop = new wxBoxSizer(wxHORIZONTAL);
	General_TechTreePicker = new wxTextCtrl(General_Scroller, wxID_ANY);
	General_TechTreeNext = new wxButton(General_Scroller, wxID_ANY, "Next", wxDefaultPosition, wxSize(-1, 20));
	General_TechTreePrev = new wxButton(General_Scroller, wxID_ANY, "Previous", wxDefaultPosition, wxSize(-1, 20));
	General_TechTreeSize = new wxStaticText(General_Scroller, wxID_ANY, " Tech Tree Size", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Grid_TechTree = new wxGridSizer(18, 0, 0);
	General_Text_TechTree = new wxStaticText(General_Scroller, wxID_ANY, " Unknown Data, Tech Tree?", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 324;loop++)
	General_TechTree[loop] = new TextCtrl_Byte(General_Scroller, "0", NULL);

	General_TopRow->Add(10, -1);
	General_TopRow->Add(General_Refresh, 1, wxEXPAND);
	General_TopRow->AddStretchSpacer(4);
	
	for(short loop = 0;loop < 138;loop++)
	General_Grid_TerrainHeader->Add(General_TerrainHeader[loop], 1, wxEXPAND);
	General_Holder_TerrainHeader->Add(General_Text_TerrainHeader, 0, wxEXPAND);
	General_Holder_TerrainHeader->Add(General_Grid_TerrainHeader, 0, wxEXPAND);
	
	for(short loop = 0;loop < 2;loop++)
	{
		General_Holder_BorderName[loop]->Add(General_Text_BorderName[loop], 0, wxEXPAND);
		General_Holder_BorderName[loop]->Add(General_BorderName[loop], 0, wxEXPAND);
	}
	General_Holder_BorderEnabled->Add(General_Text_BorderEnabled, 0, wxEXPAND);
	General_Holder_BorderEnabled->Add(General_BorderEnabled, 0, wxEXPAND);

	General_Borders_Buttons->Add(Borders_Copy, 1, wxEXPAND);
	General_Borders_Buttons->Add(Borders_Paste, 1, wxEXPAND);

	General_Borders->Add(General_Borders_Search, 0, wxEXPAND);
	General_Borders->Add(General_Borders_Search_R, 0, wxEXPAND);
	General_Borders->Add(-1, 2);
	General_Borders->Add(General_Borders_List, 1, wxEXPAND);
	General_Borders->Add(-1, 2);
	General_Borders->Add(General_Borders_Buttons, 0, wxEXPAND);
	
	General_DataTopRow->Add(General_Holder_BorderName[0], 1, wxEXPAND);
	General_DataTopRow->Add(5, -1);
	General_DataTopRow->Add(General_Holder_BorderName[1], 1, wxEXPAND);
	General_DataTopRow->Add(5, -1);
	General_DataTopRow->Add(General_Holder_BorderEnabled, 1, wxEXPAND);

	General_DataArea->Add(General_DataTopRow, 0, wxEXPAND);
	General_DataArea->Add(-1, 5);
	
	General_Holder_TerrainBorders->Add(General_Borders, 1, wxEXPAND);
	General_Holder_TerrainBorders->Add(10, -1);
	General_Holder_TerrainBorders->Add(General_DataArea, 3, wxEXPAND);

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
	for(short loop = 0;loop < 324;loop++)
	General_Grid_TechTree->Add(General_TechTree[loop], 1, wxEXPAND);
	General_Holder_TechTree->Add(General_Holder_TechTreeTop, 0, wxEXPAND);
	General_Holder_TechTree->Add(-1, 5);
	General_Holder_TechTree->Add(General_Grid_TechTree, 0, wxEXPAND);

	General_ScrollerWindowsSpace->Add(General_Holder_TerrainHeader, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_TerrainBorders, 0, wxEXPAND);
	General_ScrollerWindowsSpace->Add(-1, 10);
	General_ScrollerWindowsSpace->Add(General_Holder_TechTree, 0, wxEXPAND);
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
	
	Connect(General_TechTreePicker->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTechTreePage));
	Connect(General_Refresh->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGeneralSelect));
	Connect(General_TechTreeNext->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechTreeNext));
	Connect(General_TechTreePrev->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechTreePrev));

}
