/* AGEFrame_cpp/General.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;
/*
string AGE_Frame::GetTerrainName(short Index)
{
	string Name = "";
	if(GenieFile->Terrains[Index].Name != "")
	{
		Name = GenieFile->Terrains[Index].Name;
	}
	else
	{
		Name = "New Terrain";
	}
	return Name;
}
*/
void AGE_Frame::ListGeneral()
{
/*	string Name;
	SearchText = wxString(Terrains_Terrains_Search->GetValue()).Lower();
	ExcludeText = wxString(Terrains_Terrains_Search_R->GetValue()).Lower();
	string CompareText;
	
	short Selection = Terrains_Terrains_List->GetSelection();
	short TerrainID1 = TerRestrict_Terrains_List->GetSelection();
	short TerrainID2 = Units_ComboBox_PlacementBypassTerrain[0]->GetSelection();
	short TerrainID3 = Units_ComboBox_PlacementBypassTerrain[1]->GetSelection();
	short TerrainID4 = Units_ComboBox_PlacementTerrain[0]->GetSelection();
	short TerrainID5 = Units_ComboBox_PlacementTerrain[1]->GetSelection();
	short TerrainID6 = Units_ComboBox_TerrainID->GetSelection();
	short TerrainID7 = Terrains_ComboBox_TerrainReplacementID->GetSelection();

	if(!Terrains_Terrains_List->IsEmpty())
	{
		Terrains_Terrains_List->Clear();
	}
	if(!TerRestrict_Terrains_List->IsEmpty())
	{
		TerRestrict_Terrains_List->Clear();
	}
	if(!Units_ComboBox_PlacementBypassTerrain[0]->IsEmpty())
	{
		Units_ComboBox_PlacementBypassTerrain[0]->Clear();
	}
	if(!Units_ComboBox_PlacementBypassTerrain[1]->IsEmpty())
	{
		Units_ComboBox_PlacementBypassTerrain[1]->Clear();
	}
	if(!Units_ComboBox_PlacementTerrain[0]->IsEmpty())
	{
		Units_ComboBox_PlacementTerrain[0]->Clear();
	}
	if(!Units_ComboBox_PlacementTerrain[1]->IsEmpty())
	{
		Units_ComboBox_PlacementTerrain[1]->Clear();
	}
	if(!Units_ComboBox_TerrainID->IsEmpty())
	{
		Units_ComboBox_TerrainID->Clear();
	}
	if(!Terrains_ComboBox_TerrainReplacementID->IsEmpty())
	{
		Terrains_ComboBox_TerrainReplacementID->Clear();
	}
	
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	if(TerrainID1 == wxNOT_FOUND)
	{
		TerrainID1 = 0;
	}
	if(TerrainID2 == wxNOT_FOUND)
	{
		TerrainID2 = 0;
	}
	if(TerrainID3 == wxNOT_FOUND)
	{
		TerrainID3 = 0;
	}
	if(TerrainID4 == wxNOT_FOUND)
	{
		TerrainID4 = 0;
	}
	if(TerrainID5 == wxNOT_FOUND)
	{
		TerrainID5 = 0;
	}
	if(TerrainID6 == wxNOT_FOUND)
	{
		TerrainID6 = 0;
	}
	if(TerrainID7 == wxNOT_FOUND)
	{
		TerrainID7 = 0;
	}
	
	Units_ComboBox_PlacementBypassTerrain[0]->Append("-1 - None");
	Units_ComboBox_PlacementBypassTerrain[1]->Append("-1 - None");
	Units_ComboBox_PlacementTerrain[0]->Append("-1 - None");
	Units_ComboBox_PlacementTerrain[1]->Append("-1 - None");
	Units_ComboBox_TerrainID->Append("-1 - None");
	Terrains_ComboBox_TerrainReplacementID->Append("-1 - None");
	
	for(short loop = 0;loop < GenieFile->Terrains.size();loop++)
	{
		Name = lexical_cast<string>(loop)+" - "+GetTerrainName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTerrainName(loop)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Terrains_Terrains_List->Append(Name, (void*)&GenieFile->Terrains[loop]);
		}
		Units_ComboBox_PlacementBypassTerrain[0]->Append(Name);
		Units_ComboBox_PlacementBypassTerrain[1]->Append(Name);
		Units_ComboBox_PlacementTerrain[0]->Append(Name);
		Units_ComboBox_PlacementTerrain[1]->Append(Name);
		Units_ComboBox_TerrainID->Append(Name);
		Terrains_ComboBox_TerrainReplacementID->Append(Name);
	}
	SearchText = wxString(TerRestrict_Terrains_Search->GetValue()).Lower();
	ExcludeText = wxString(TerRestrict_Terrains_Search_R->GetValue()).Lower();
	for(short loop = 0;loop < GenieFile->TerrainRestrictions[0].TerrainAccessible.size();loop++)
	{
		Name = lexical_cast<string>(loop)+" - "+GetTerrainName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTerrainName(loop)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TerRestrict_Terrains_List->Append(Name, (void*)&GenieFile->Terrains[loop]);
		}
	}
	
	Terrains_Terrains_List->SetSelection(0);
	Terrains_Terrains_List->SetFirstItem(Selection - 3);
	Terrains_Terrains_List->SetSelection(Selection);
	TerRestrict_Terrains_List->SetSelection(TerrainID1);
	Units_ComboBox_PlacementBypassTerrain[0]->SetSelection(TerrainID2);
	Units_ComboBox_PlacementBypassTerrain[1]->SetSelection(TerrainID3);
	Units_ComboBox_PlacementTerrain[0]->SetSelection(TerrainID4);
	Units_ComboBox_PlacementTerrain[1]->SetSelection(TerrainID5);
	Units_ComboBox_TerrainID->SetSelection(TerrainID6);
	Terrains_ComboBox_TerrainReplacementID->SetSelection(TerrainID7);
*/
	General_TechTreeSize->SetLabel(" Tech Tree Size");
	TechTreeSize = lexical_cast<long>(0);
	TechTreePage = lexical_cast<long>(0);
	General_TechTreePicker->ChangeValue(lexical_cast<string>(TechTreePage));
	
	wxCommandEvent E;
	OnGeneralSelect(E);
}
/*
void AGE_Frame::OnTerrainsSearch(wxCommandEvent& Event)
{
	ListTerrains();
}
*/

void AGE_Frame::OnTechTreePage(wxCommandEvent& Event)
{
	TechTreePage = lexical_cast<long>(General_TechTreePicker->GetValue());
	
	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnTechTreeNext(wxCommandEvent& Event)
{
	TechTreePage += lexical_cast<long>(324);
	
	wxCommandEvent E;
	OnGeneralSelect(E);
}

void AGE_Frame::OnTechTreePrev(wxCommandEvent& Event)
{
	TechTreePage -= lexical_cast<long>(324);
	
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
		Terrains_Name->ChangeValue(TerrainPointer->Name);
		Terrains_Name->Container = &TerrainPointer->Name;
		Terrains_Name2->ChangeValue(TerrainPointer->Name2);
		Terrains_Name2->Container = &TerrainPointer->Name2;
		Terrains_SLP->ChangeValue(lexical_cast<string>(TerrainPointer->SLP));
		Terrains_SLP->Container = &TerrainPointer->SLP;
		Terrains_Unknown3->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown3));
		Terrains_Unknown3->Container = &TerrainPointer->Unknown3;
		Terrains_SoundID->ChangeValue(lexical_cast<string>(TerrainPointer->SoundID));
		Terrains_SoundID->Container = &TerrainPointer->SoundID;
		Terrains_ComboBox_SoundID->SetSelection(TerrainPointer->SoundID + 1);
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
		for(short loop = 0;loop < 3;loop++)
		{
			Terrains_Colours[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->Colours[loop]));
			Terrains_Colours[loop]->Container = &TerrainPointer->Colours[loop];
		}
		Terrains_Unknown5->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown5));
		Terrains_Unknown5->Container = &TerrainPointer->Unknown5;
		Terrains_Unknown6->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown6));
		Terrains_Unknown6->Container = &TerrainPointer->Unknown6;
		for(short loop = 0;loop < 23;loop++)
		{
			Terrains_Unknown7[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->Unknown7[loop]));
			Terrains_Unknown7[loop]->Container = &TerrainPointer->Unknown7[loop];
		}
		Terrains_FrameCount->ChangeValue(lexical_cast<string>(TerrainPointer->FrameCount));
		Terrains_FrameCount->Container = &TerrainPointer->FrameCount;
		Terrains_Unknown8[0]->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown8[0]));
		Terrains_Unknown8[0]->Container = &TerrainPointer->Unknown8[0];
		Terrains_Unknown8[1]->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown8[1]));
		Terrains_Unknown8[1]->Container = &TerrainPointer->Unknown8[1];
		for(short loop = 0;loop < 54;loop++)
		{
			Terrains_Unknown9[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown9[loop]));
			Terrains_Unknown9[loop]->Container = &TerrainPointer->Unknown9[loop];
		}
		Terrains_TerrainReplacementID->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainReplacementID));
		Terrains_TerrainReplacementID->Container = &TerrainPointer->TerrainReplacementID;
		Terrains_ComboBox_TerrainReplacementID->SetSelection(TerrainPointer->TerrainReplacementID + 1);
		Terrains_TerrainDimensions[0]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainDimensions.first));
		Terrains_TerrainDimensions[0]->Container = &TerrainPointer->TerrainDimensions.first;
		Terrains_TerrainDimensions[1]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainDimensions.second));
		Terrains_TerrainDimensions[1]->Container = &TerrainPointer->TerrainDimensions.second;
		short Unknown10;
		for(short loop = 64;loop < 84;loop++)
		{
			if(GameVersion >= 3)
			{
				Unknown10 = 84;
				if(ShowUnknowns) Terrains_Unknown10[loop]->Show(true);
			}
			else
			{
				Unknown10 = 64;
				Terrains_Unknown10[loop]->Show(false);
			}
		}
		for(short loop = 0;loop < Unknown10;loop++)
		{
			Terrains_Unknown10[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->Unknown10[loop]));
			Terrains_Unknown10[loop]->Container = &TerrainPointer->Unknown10[loop];
		}
		for(short loop = 0;loop < 30;loop++)
		{
			Terrains_TerrainUnitID[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainUnitID[loop]));
			Terrains_TerrainUnitID[loop]->Container = &TerrainPointer->TerrainUnitID[loop];
			Terrains_ComboBox_TerrainUnitID[loop]->SetSelection(TerrainPointer->TerrainUnitID[loop] + 1);
			Terrains_TerrainUnitDensity[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainUnitDensity[loop]));
			Terrains_TerrainUnitDensity[loop]->Container = &TerrainPointer->TerrainUnitDensity[loop];
		}
		for(short loop = 0;loop < 30;loop++)
		{
			Terrains_Unknown11[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->Unknown11[loop]));
			Terrains_Unknown11[loop]->Container = &TerrainPointer->Unknown11[loop];
		}
		Terrains_NumberOfTerrainUnitsUsed->ChangeValue(lexical_cast<string>(TerrainPointer->NumberOfTerrainUnitsUsed));
		Terrains_NumberOfTerrainUnitsUsed->Container = &TerrainPointer->NumberOfTerrainUnitsUsed;
		if(GameVersion >= 4)
		{
			if(ShowUnknowns) Terrains_Holder_SUnknown1->Show(true);
			
			for(short loop = 0;loop < 24;loop++)
			{
				Terrains_SUnknown1[loop]->ChangeValue(lexical_cast<string>((short)TerrainPointer->SWGBUnknown1[loop]));
				Terrains_SUnknown1[loop]->Container = &TerrainPointer->SWGBUnknown1[loop];
			}
		}
		else
		{
			Terrains_Holder_SUnknown1->Show(false);
		}
		Added = false;
	}*/
}
/*
void AGE_Frame::OnTerrainsAdd(wxCommandEvent& Event) // Their count is hardcoded.
{
	gdat::Terrain Temp1;
	GenieFile->Terrains.push_back(Temp1);
	gdat::TerrainPassGraphic Temp2;
	for(int loop = 0;loop < GenieFile->TerrainRestrictions.size();loop++)
	{
		GenieFile->TerrainRestrictions[loop].TerrainAccessible.push_back(0);
		GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.push_back(Temp2);
	}
	Added = true;
	ListTerrains();
}

void AGE_Frame::OnTerrainsDelete(wxCommandEvent& Event) // Their count is hardcoded.
{
	wxBusyCursor WaitCursor;
	short Selection = Terrains_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->Terrains.erase(GenieFile->Terrains.begin() + TerrainID);
		for(int loop = 0;loop < GenieFile->TerrainRestrictions.size();loop++)
		{
			GenieFile->TerrainRestrictions[loop].TerrainAccessible.erase(GenieFile->TerrainRestrictions[loop].TerrainAccessible.begin() + TerrainID);
			GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.erase(GenieFile->TerrainRestrictions[loop].TerrainPassGraphics.begin() + TerrainID);
		}
		if(Selection == Terrains_Terrains_List->GetCount() - 1)
		Terrains_Terrains_List->SetSelection(Selection - 1);
		ListTerrains();
	}
}

void AGE_Frame::OnTerrainsCopy(wxCommandEvent& Event)
{
	short Selection = Terrains_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TerrainCopy = *(gdat::Terrain*)Terrains_Terrains_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnTerrainsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Terrains_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::Terrain*)Terrains_Terrains_List->GetClientData(Selection) = TerrainCopy;
		ListTerrains();
	}
}
*/
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
	General_Text_TerrainHeader = new wxStaticText(General_Scroller, wxID_ANY, " Terrain Header", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 138;loop++)
	General_TerrainHeader[loop] = new TextCtrl_Byte(General_Scroller, "0", NULL);
	General_Holder_TechTree = new wxBoxSizer(wxVERTICAL);
	General_Holder_TechTreeTop = new wxBoxSizer(wxHORIZONTAL);
	General_TechTreePicker = new wxTextCtrl(General_Scroller, wxID_ANY);
	General_TechTreeNext = new wxButton(General_Scroller, wxID_ANY, "Next", wxDefaultPosition, wxSize(-1, 20));
	General_TechTreePrev = new wxButton(General_Scroller, wxID_ANY, "Previous", wxDefaultPosition, wxSize(-1, 20));
	General_TechTreeSize = new wxStaticText(General_Scroller, wxID_ANY, " Tech Tree Size", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	General_Grid_TechTree = new wxGridSizer(18, 0, 0);
	General_Text_TechTree = new wxStaticText(General_Scroller, wxID_ANY, " Tech Tree", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
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
	General_ScrollerWindowsSpace->Add(-1, 5);
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
	
//	Terrains_Terrains_UseAnd->Show(false);

	Tab_General->SetSizer(General_Main);
/*	
	Connect(Terrains_Terrains_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	Connect(Terrains_Terrains_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainsSelect));*/
	Connect(General_TechTreePicker->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTechTreePage));
	Connect(General_Refresh->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGeneralSelect));
	Connect(General_TechTreeNext->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechTreeNext));
	Connect(General_TechTreePrev->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechTreePrev));
/*	Connect(Terrains_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsDelete));
	Connect(Terrains_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsCopy));
	Connect(Terrains_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsPaste));

	Terrains_Name->Connect(Terrains_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Terrains_Name2->Connect(Terrains_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
*/
}
