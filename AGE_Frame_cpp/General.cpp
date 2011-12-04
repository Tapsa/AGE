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

string AGE_Frame::GetBorderName(short Index)
{
	string Name = "";
	if(GenieFile->TerrainBorders[Index].Name == "" && GenieFile->TerrainBorders[Index].Name2 == "")
	{
		Name = "Border "+lexical_cast<string>(Index);
	}
	else
	{
		Name = GenieFile->TerrainBorders[Index].Name;
		Name += " - ";
		Name += GenieFile->TerrainBorders[Index].Name2;
	}
	return Name;
}

void AGE_Frame::ListBorders()
{
	string Name;
	SearchText = wxString(General_Borders_Search->GetValue()).Lower();
	ExcludeText = wxString(General_Borders_Search_R->GetValue()).Lower();
	string CompareText;

	short Selection = General_Borders_List->GetSelection();

	if(!General_Borders_List->IsEmpty())
	{
		General_Borders_List->Clear();
	}
	
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	
	for(short loop = 0;loop < GenieFile->TerrainBorders.size();loop++)
	{
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetBorderName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetBorderName(loop)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			General_Borders_List->Append(Name, (void*)&GenieFile->TerrainBorders[loop]);
		}
	}
	
	General_Borders_List->SetSelection(0);
	General_Borders_List->SetFirstItem(Selection - 3);
	General_Borders_List->SetSelection(Selection);
	
	wxCommandEvent E;
	OnBordersSelect(E);
}

void AGE_Frame::OnBordersSearch(wxCommandEvent& Event)
{
	ListBorders();
}

void AGE_Frame::OnBordersSelect(wxCommandEvent& Event)
{
	short Selection = General_Borders_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		gdat::TerrainBorder * BorderPointer = (gdat::TerrainBorder*)General_Borders_List->GetClientData(Selection);
		BorderID = BorderPointer - (&GenieFile->TerrainBorders[0]);
		General_BorderName[0]->ChangeValue(BorderPointer->Name);
		General_BorderName[0]->Container = &BorderPointer->Name;
		General_BorderName[1]->ChangeValue(BorderPointer->Name2);
		General_BorderName[1]->Container = &BorderPointer->Name2;
		General_BorderEnabled->ChangeValue(lexical_cast<string>(BorderPointer->Enabled));
		General_BorderEnabled->Container = &BorderPointer->Enabled;
	}
}

void AGE_Frame::OnBordersCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnBordersPaste(wxCommandEvent& Event)
{

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
	
	General_Holder_TerrainBorders = new wxStaticBoxSizer(wxHORIZONTAL, General_Scroller, "Terrain Borders (Used in AoE and RoR)");
	General_Borders_Buttons = new wxGridSizer(2, 0, 0);
	General_Borders = new wxStaticBoxSizer(wxVERTICAL, General_Scroller, "Terrain Border slot");
	General_Borders_Search = new wxTextCtrl(General_Scroller, wxID_ANY);
	General_Borders_Search_R = new wxTextCtrl(General_Scroller, wxID_ANY);
	General_Borders_List = new wxListBox(General_Scroller, wxID_ANY, wxDefaultPosition, wxSize(-1, 220));
	Borders_Copy = new wxButton(General_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Borders_Paste = new wxButton(General_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));
	General_DataArea = new wxBoxSizer(wxVERTICAL);
	General_DataTopRow = new wxBoxSizer(wxHORIZONTAL);
	General_Holder_BorderEnabled = new wxBoxSizer(wxVERTICAL);
	General_Text_BorderEnabled = new wxStaticText(General_Scroller, wxID_ANY, " Enabled", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_BorderEnabled = new TextCtrl_Short(General_Scroller, "0", NULL);
	for(short loop = 0;loop < 2;loop++)
	{
		General_Holder_BorderName[loop] = new wxBoxSizer(wxVERTICAL);
		General_BorderName[loop] = new TextCtrl_String(General_Scroller, "0", NULL);
	}
	General_Text_BorderName[0] = new wxStaticText(General_Scroller, wxID_ANY, " Name", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Text_BorderName[1] = new wxStaticText(General_Scroller, wxID_ANY, " SLP Name ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	
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

/*
  static const unsigned short TERRAIN_HEADER_SIZE = 138;
  char *TerrainHeader;
        
  char *TechTree; // joka peliversiolle oma lukunsa
  switch (getGameVersion()) // is this really the techtree?
  {
    case gdat::GV_AoE: serialize<char>(&TechTree, 33666); break;
    case gdat::GV_RoR: serialize<char>(&TechTree, 41838); break;
    case gdat::GV_AoK: serialize<char>(&TechTree, 35794); break;
    case gdat::GV_TC: serialize<char>(&TechTree, 36230); break;
    case gdat::GV_SWGB: serialize<char>(&TechTree, 0x642A); break; //0x1030a5
    case gdat::GV_CC: serialize<char>(&TechTree, 0x6082); break;
    default: break;
  }

  char *Unknown1; //[27063]; //89341 // aokista ylöspäin oma lukunsa
  switch (getGameVersion())
  {
    case gdat::GV_AoK:
      serialize<char>(&Unknown1, 21642); //TODO: maybe team bonus
      break;
  
    case gdat::GV_TC: serialize<char>(&Unknown1,27062); break;
    case gdat::GV_SWGB: serialize<char>(&Unknown1, 89341); break;
    case gdat::GV_CC: serialize<char>(&Unknown1, 116820); break;
    
    default: break;
  }

   //SWGB Unknowns:
  /// Seems to be the CivCount
  if (getGameVersion() >= gdat::GV_SWGB)
  short SUnknown1;     
  long SUnknown2;
  long SUnknown3;
  long SUnknown4;
  long SUnknown5;
  
  char *SUnknown6; // 1382 // eri määrä kloonisodissa
  
  char SUnknown7;
*/

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
	
	Connect(General_Borders_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnBordersSearch));
	Connect(General_Borders_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnBordersSearch));
	Connect(General_Borders_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnBordersSelect));
	Connect(General_TechTreePicker->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTechTreePage));
	Connect(General_Refresh->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGeneralSelect));
	Connect(General_TechTreeNext->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechTreeNext));
	Connect(General_TechTreePrev->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechTreePrev));
	Connect(Borders_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnBordersCopy));
	Connect(Borders_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnBordersPaste));

	for(short loop = 0;loop < 2;loop++)
	General_BorderName[loop]->Connect(General_BorderName[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);

}
