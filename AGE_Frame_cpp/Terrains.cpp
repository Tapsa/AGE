/* AGEFrame_cpp/Terrains.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetTerrainName(int Index)
{
	string Name = "";
	Name = GenieFile->Terrains[Index].Name;
	return Name;
}

void AGE_Frame::ListTerrains()
{
	string Name;
	wxString SearchText = wxString(Terrains_Terrains_Search->GetValue()).Lower();
	wxString SearchText2 = wxString(TerRestrict_Terrains_Search->GetValue()).Lower();
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
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetTerrainName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTerrainName(loop)).Lower();
		if(SearchText.IsEmpty() || CompareText.find(SearchText) != string::npos)
		{
			Terrains_Terrains_List->Append(Name, (void*)&GenieFile->Terrains[loop]);
		}
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTerrainName(loop)).Lower();
		if(SearchText2.IsEmpty() || CompareText.find(SearchText2) != string::npos)
		{
			TerRestrict_Terrains_List->Append(Name, (void*)&GenieFile->Terrains[loop]);
		}
		Units_ComboBox_PlacementBypassTerrain[0]->Append(Name);
		Units_ComboBox_PlacementBypassTerrain[1]->Append(Name);
		Units_ComboBox_PlacementTerrain[0]->Append(Name);
		Units_ComboBox_PlacementTerrain[1]->Append(Name);
		Units_ComboBox_TerrainID->Append(Name);
		Terrains_ComboBox_TerrainReplacementID->Append(Name);
	}
	
	Terrains_Terrains_List->SetFirstItem(Selection - 3);
	Terrains_Terrains_List->SetSelection(Selection);
	TerRestrict_Terrains_List->SetSelection(TerrainID1);
	Units_ComboBox_PlacementBypassTerrain[0]->SetSelection(TerrainID2);
	Units_ComboBox_PlacementBypassTerrain[1]->SetSelection(TerrainID3);
	Units_ComboBox_PlacementTerrain[0]->SetSelection(TerrainID4);
	Units_ComboBox_PlacementTerrain[1]->SetSelection(TerrainID5);
	Units_ComboBox_TerrainID->SetSelection(TerrainID6);
	Terrains_ComboBox_TerrainReplacementID->SetSelection(TerrainID7);

	wxCommandEvent E;
	OnTerrainsSelect(E);
}

void AGE_Frame::OnTerrainsSearch(wxCommandEvent& Event)
{
	if(TerRestrict_Terrains_List->GetSelection() != wxNOT_FOUND || Terrains_Terrains_List->GetSelection() != wxNOT_FOUND)
	{
		ListTerrains();
	}
}

void AGE_Frame::OnTerrainsSelect(wxCommandEvent& Event)
{
	short Selection = Terrains_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Terrains_Terrains_List->GetCount() - 1;
			Terrains_Terrains_List->SetSelection(Selection);
		}
		gdat::Terrain * TerrainPointer = (gdat::Terrain*)Terrains_Terrains_List->GetClientData(Selection);
		TerrainID = TerrainPointer - (&GenieFile->Terrains[0]);
		Terrains_Unknown1->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown1));
		Terrains_Unknown1->Container = &TerrainPointer->Unknown1;
		Terrains_Unknown2->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown2));
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
		Terrains_BlendPriority->ChangeValue(lexical_cast<string>(TerrainPointer->BlendPriority));
		Terrains_BlendPriority->Container = &TerrainPointer->BlendPriority;
		Terrains_BlendType->ChangeValue(lexical_cast<string>(TerrainPointer->BlendType));
		Terrains_BlendType->Container = &TerrainPointer->BlendType;
//		Terrains_Colours->ChangeValue(TerrainPointer->Colours);
//		Terrains_Colours->Container = TerrainPointer->Colours;
		Terrains_Unknown5->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown5));
		Terrains_Unknown5->Container = &TerrainPointer->Unknown5;
		Terrains_Unknown6->ChangeValue(lexical_cast<string>(TerrainPointer->Unknown6));
		Terrains_Unknown6->Container = &TerrainPointer->Unknown6;
//		Terrains_Unknown7->ChangeValue(TerrainPointer->Unknown7);
//		Terrains_Unknown7->Container = TerrainPointer->Unknown7;
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
//		Terrains_Unknown10->ChangeValue(TerrainPointer->Unknown10);
//		Terrains_Unknown10->Container = TerrainPointer->Unknown10;
		for(short loop = 0;loop < 30;loop++)
		{
			Terrains_TerrainUnitID[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainUnitID[loop]));
			Terrains_TerrainUnitID[loop]->Container = &TerrainPointer->TerrainUnitID[loop];
			Terrains_ComboBox_TerrainUnitID[loop]->SetSelection(TerrainPointer->TerrainUnitID[loop] + 1);
			Terrains_TerrainUnitDensity[loop]->ChangeValue(lexical_cast<string>(TerrainPointer->TerrainUnitDensity[loop]));
			Terrains_TerrainUnitDensity[loop]->Container = &TerrainPointer->TerrainUnitDensity[loop];
		}
//		Terrains_Unknown11->ChangeValue(TerrainPointer->Unknown11);
//		Terrains_Unknown11->Container = TerrainPointer->Unknown11;
		Terrains_NumberOfTerrainUnitsUsed->ChangeValue(lexical_cast<string>(TerrainPointer->NumberOfTerrainUnitsUsed));
		Terrains_NumberOfTerrainUnitsUsed->Container = &TerrainPointer->NumberOfTerrainUnitsUsed;
		Added = false;
	}
}

void AGE_Frame::OnTerrainsAdd(wxCommandEvent& Event) // Their count is hardcoded.
{
	gdat::Terrain Temp;
	GenieFile->Terrains.push_back(Temp);
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

void AGE_Frame::CreateTerrainControls()
{

	Terrains_Main = new wxBoxSizer(wxHORIZONTAL);
	Terrains_ListArea = new wxBoxSizer(wxVERTICAL);
	Terrains_Terrains_Buttons = new wxGridSizer(2, 0, 0);
	Tab_Terrains = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(-1, 350));
	Terrains_Terrains = new wxStaticBoxSizer(wxVERTICAL, Tab_Terrains, "Terrain Slot");
	Terrains_Terrains_Search = new wxTextCtrl(Tab_Terrains, wxID_ANY);
	Terrains_Terrains_List = new wxListBox(Tab_Terrains, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	Terrains_Add = new wxButton(Tab_Terrains, wxID_ANY, "Add", wxDefaultPosition, wxSize(-1, 20));
	Terrains_Delete = new wxButton(Tab_Terrains, wxID_ANY, "Delete", wxDefaultPosition, wxSize(-1, 20));
	Terrains_Copy = new wxButton(Tab_Terrains, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Terrains_Paste = new wxButton(Tab_Terrains, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));
	
	Terrains_DataArea = new wxBoxSizer(wxVERTICAL);
	Terrains_Scroller = new AGE_ScrolledWindow(Tab_Terrains, wxVSCROLL | wxTAB_TRAVERSAL);
	Terrains_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	Terrains_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	Terrains_Holder_NameArea = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Holder_LongArea = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Holder_ShortArea = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown1 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown1 = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown2 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown2 = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Name = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Name = new wxStaticText(Terrains_Scroller, wxID_ANY, " Name", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name = new TextCtrl_String(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Name2 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Name2 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Name 2", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Name2 = new TextCtrl_String(Terrains_Scroller, "0", NULL);
	Terrains_Holder_SLP = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_SLP = new wxStaticText(Terrains_Scroller, wxID_ANY, " SLP", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SLP = new TextCtrl_Long(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown3 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown3 = new TextCtrl_Long(Terrains_Scroller, "0", NULL);
	Terrains_Holder_SoundID = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_SoundID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_SoundID = new TextCtrl_Long(Terrains_Scroller, "0", NULL);
	Terrains_ComboBox_SoundID = new ComboBox_Long(Terrains_Scroller, Terrains_SoundID);
	Terrains_Holder_BlendPriority = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_BlendPriority = new wxStaticText(Terrains_Scroller, wxID_ANY, " Blend Priority", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_BlendPriority = new TextCtrl_Long(Terrains_Scroller, "0", NULL);
	Terrains_Holder_BlendType = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_BlendType = new wxStaticText(Terrains_Scroller, wxID_ANY, " Blend Type", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_BlendType = new TextCtrl_Long(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Colours = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Colours = new wxStaticText(Terrains_Scroller, wxID_ANY, " Colors", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Colours = new TextCtrl_String(Terrains_Scroller, "0", NULL, 3);
	Terrains_Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown5 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown5 = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown6 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown6 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown6 = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown7 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown7 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown7 = new TextCtrl_String(Terrains_Scroller, "0", NULL, 23);
	Terrains_Holder_FrameCount = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_FrameCount = new wxStaticText(Terrains_Scroller, wxID_ANY, " Frame Count", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_FrameCount = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown8 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown8 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 8", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown8[0] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Unknown8[1] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown9 = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_Unknown9 = new wxGridSizer(6, 0, 0);
	Terrains_Text_Unknown9 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 9", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 54;loop++)
	{
		Terrains_Unknown9[loop] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	}
	Terrains_Holder_TerrainReplacementID = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainReplacementID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Replacement", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainReplacementID = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_ComboBox_TerrainReplacementID = new ComboBox_Short(Terrains_Scroller, Terrains_TerrainReplacementID);
	Terrains_Holder_TerrainDimensions = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainDimensions = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Dimensions", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_TerrainDimensions[0] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_TerrainDimensions[1] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	Terrains_Holder_Unknown10 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown10 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 10", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	// The size of Unknown10 is 84 in TC and above, 64 in others.
	Terrains_Unknown10 = new TextCtrl_String(Terrains_Scroller, "0", NULL, 84);
	Terrains_Holder_TerrainUnits = new wxBoxSizer(wxHORIZONTAL);
	Terrains_Holder_TerrainUnitID = new wxBoxSizer(wxVERTICAL);
	Terrains_Grid_TerrainUnitID = new wxGridSizer(2, 0, 5);
	Terrains_Holder_TerrainUnitDensity = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_TerrainUnitID = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Text_TerrainUnitDensity = new wxStaticText(Terrains_Scroller, wxID_ANY, " Terrain Unit Density", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 30;loop++)
	{
		Terrains_TerrainUnitID[loop] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
		Terrains_ComboBox_TerrainUnitID[loop] = new ComboBox_Short(Terrains_Scroller, Terrains_TerrainUnitID[loop]);
		Terrains_TerrainUnitDensity[loop] = new TextCtrl_Short(Terrains_Scroller, "0", NULL);
	}
	Terrains_Holder_Unknown11 = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_Unknown11 = new wxStaticText(Terrains_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_Unknown11 = new TextCtrl_String(Terrains_Scroller, "0", NULL, 30);
	Terrains_Holder_NumberOfTerrainUnitsUsed = new wxBoxSizer(wxVERTICAL);
	Terrains_Text_NumberOfTerrainUnitsUsed = new wxStaticText(Terrains_Scroller, wxID_ANY, " Number Of Terrain Units Used", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Terrains_NumberOfTerrainUnitsUsed = new TextCtrl_Short(Terrains_Scroller, "0", NULL);

	Terrains_Terrains_Buttons->Add(Terrains_Add, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Delete, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Copy, 1, wxEXPAND);
	Terrains_Terrains_Buttons->Add(Terrains_Paste, 1, wxEXPAND);

	Terrains_Terrains->Add(Terrains_Terrains_Search, 0, wxEXPAND);
	Terrains_Terrains->Add(-1, 2);
	Terrains_Terrains->Add(Terrains_Terrains_List, 1, wxEXPAND);
	Terrains_Terrains->Add(-1, 2);
	Terrains_Terrains->Add(Terrains_Terrains_Buttons, 0, wxEXPAND);

	Terrains_ListArea->Add(-1, 10);
	Terrains_ListArea->Add(Terrains_Terrains, 1, wxEXPAND);
	Terrains_ListArea->Add(-1, 10);
	
	Terrains_Holder_Unknown1->Add(Terrains_Text_Unknown1, 0, wxEXPAND);
	Terrains_Holder_Unknown1->Add(-1, 2);
	Terrains_Holder_Unknown1->Add(Terrains_Unknown1, 1, wxEXPAND);
	Terrains_Holder_Unknown2->Add(Terrains_Text_Unknown2, 0, wxEXPAND);
	Terrains_Holder_Unknown2->Add(-1, 2);
	Terrains_Holder_Unknown2->Add(Terrains_Unknown2, 1, wxEXPAND);
	Terrains_Holder_Name->Add(Terrains_Text_Name, 0, wxEXPAND);
	Terrains_Holder_Name->Add(-1, 2);
	Terrains_Holder_Name->Add(Terrains_Name, 1, wxEXPAND);
	Terrains_Holder_Name2->Add(Terrains_Text_Name2, 0, wxEXPAND);
	Terrains_Holder_Name2->Add(-1, 2);
	Terrains_Holder_Name2->Add(Terrains_Name2, 1, wxEXPAND);
	Terrains_Holder_SLP->Add(Terrains_Text_SLP, 0, wxEXPAND);
	Terrains_Holder_SLP->Add(-1, 2);
	Terrains_Holder_SLP->Add(Terrains_SLP, 1, wxEXPAND);
	Terrains_Holder_SLP->AddStretchSpacer(1);
	Terrains_Holder_Unknown3->Add(Terrains_Text_Unknown3, 0, wxEXPAND);
	Terrains_Holder_Unknown3->Add(-1, 2);
	Terrains_Holder_Unknown3->Add(Terrains_Unknown3, 1, wxEXPAND);
	Terrains_Holder_SoundID->Add(Terrains_Text_SoundID, 0, wxEXPAND);
	Terrains_Holder_SoundID->Add(-1, 2);
	Terrains_Holder_SoundID->Add(Terrains_SoundID, 1, wxEXPAND);
	Terrains_Holder_SoundID->Add(Terrains_ComboBox_SoundID, 1, wxEXPAND);
	Terrains_Holder_BlendPriority->Add(Terrains_Text_BlendPriority, 0, wxEXPAND);
	Terrains_Holder_BlendPriority->Add(-1, 2);
	Terrains_Holder_BlendPriority->Add(Terrains_BlendPriority, 1, wxEXPAND);
	Terrains_Holder_BlendPriority->AddStretchSpacer(1);
	Terrains_Holder_BlendType->Add(Terrains_Text_BlendType, 0, wxEXPAND);
	Terrains_Holder_BlendType->Add(-1, 2);
	Terrains_Holder_BlendType->Add(Terrains_BlendType, 1, wxEXPAND);
	Terrains_Holder_BlendType->AddStretchSpacer(1);
	Terrains_Holder_Colours->Add(Terrains_Text_Colours, 0, wxEXPAND);
	Terrains_Holder_Colours->Add(-1, 2);
	Terrains_Holder_Colours->Add(Terrains_Colours, 1, wxEXPAND);
	Terrains_Holder_Colours->AddStretchSpacer(1);
	Terrains_Holder_Unknown5->Add(Terrains_Text_Unknown5, 0, wxEXPAND);
	Terrains_Holder_Unknown5->Add(-1, 2);
	Terrains_Holder_Unknown5->Add(Terrains_Unknown5, 1, wxEXPAND);
	Terrains_Holder_Unknown6->Add(Terrains_Text_Unknown6, 0, wxEXPAND);
	Terrains_Holder_Unknown6->Add(-1, 2);
	Terrains_Holder_Unknown6->Add(Terrains_Unknown6, 1, wxEXPAND);
	Terrains_Holder_Unknown7->Add(Terrains_Text_Unknown7, 0, wxEXPAND);
	Terrains_Holder_Unknown7->Add(-1, 2);
	Terrains_Holder_Unknown7->Add(Terrains_Unknown7, 1, wxEXPAND);
	Terrains_Holder_FrameCount->Add(Terrains_Text_FrameCount, 0, wxEXPAND);
	Terrains_Holder_FrameCount->Add(-1, 2);
	Terrains_Holder_FrameCount->Add(Terrains_FrameCount, 1, wxEXPAND);
	Terrains_Holder_FrameCount->AddStretchSpacer(1);
	Terrains_Holder_Unknown8->Add(Terrains_Text_Unknown8, 0, wxEXPAND);
	Terrains_Holder_Unknown8->Add(-1, 2);
	Terrains_Holder_Unknown8->Add(Terrains_Unknown8[0], 1, wxEXPAND);
	Terrains_Holder_Unknown8->Add(Terrains_Unknown8[1], 1, wxEXPAND);
	Terrains_Holder_Unknown9->Add(Terrains_Text_Unknown9, 0, wxEXPAND);
	Terrains_Holder_Unknown9->Add(-1, 2);
	Terrains_Holder_Unknown9->Add(Terrains_Grid_Unknown9, 0, wxEXPAND);
	for(short loop = 0;loop < 54;loop++)
	{
		Terrains_Grid_Unknown9->Add(Terrains_Unknown9[loop], 1, wxEXPAND);
	}
	Terrains_Holder_TerrainReplacementID->Add(Terrains_Text_TerrainReplacementID, 0, wxEXPAND);
	Terrains_Holder_TerrainReplacementID->Add(-1, 2);
	Terrains_Holder_TerrainReplacementID->Add(Terrains_TerrainReplacementID, 1, wxEXPAND);
	Terrains_Holder_TerrainReplacementID->Add(Terrains_ComboBox_TerrainReplacementID, 1, wxEXPAND);
	Terrains_Holder_TerrainDimensions->Add(Terrains_Text_TerrainDimensions, 0, wxEXPAND);
	Terrains_Holder_TerrainDimensions->Add(-1, 2);
	Terrains_Holder_TerrainDimensions->Add(Terrains_TerrainDimensions[0], 1, wxEXPAND);
	Terrains_Holder_TerrainDimensions->Add(Terrains_TerrainDimensions[1], 1, wxEXPAND);
	Terrains_Holder_Unknown10->Add(Terrains_Text_Unknown10, 0, wxEXPAND);
	Terrains_Holder_Unknown10->Add(-1, 2);
	Terrains_Holder_Unknown10->Add(Terrains_Unknown10, 1, wxEXPAND);
	Terrains_Holder_TerrainUnitID->Add(Terrains_Text_TerrainUnitID, 0, wxEXPAND);
	Terrains_Holder_TerrainUnitID->Add(-1, 2);
	Terrains_Holder_TerrainUnitID->Add(Terrains_Grid_TerrainUnitID, 0, wxEXPAND);
	Terrains_Holder_TerrainUnitDensity->Add(Terrains_Text_TerrainUnitDensity, 0, wxEXPAND);
	Terrains_Holder_TerrainUnitDensity->Add(-1, 2);
	for(short loop = 0;loop < 30;loop++)
	{
		Terrains_Grid_TerrainUnitID->Add(Terrains_TerrainUnitID[loop], 1, wxEXPAND);
		Terrains_Grid_TerrainUnitID->Add(Terrains_ComboBox_TerrainUnitID[loop], 1, wxEXPAND);
		Terrains_Holder_TerrainUnitDensity->Add(Terrains_TerrainUnitDensity[loop], 1, wxEXPAND);
	}
	Terrains_Holder_Unknown11->Add(Terrains_Text_Unknown11, 0, wxEXPAND);
	Terrains_Holder_Unknown11->Add(-1, 2);
	Terrains_Holder_Unknown11->Add(Terrains_Unknown11, 1, wxEXPAND);
	Terrains_Holder_NumberOfTerrainUnitsUsed->Add(Terrains_Text_NumberOfTerrainUnitsUsed, 0, wxEXPAND);
	Terrains_Holder_NumberOfTerrainUnitsUsed->Add(-1, 2);
	Terrains_Holder_NumberOfTerrainUnitsUsed->Add(Terrains_NumberOfTerrainUnitsUsed, 1, wxEXPAND);
	
	Terrains_Holder_NameArea->Add(Terrains_Holder_Name, 1, wxEXPAND);
	Terrains_Holder_NameArea->Add(5, -1);
	Terrains_Holder_NameArea->Add(Terrains_Holder_Name2, 1, wxEXPAND);
	
	Terrains_Holder_LongArea->Add(Terrains_Holder_SLP, 1, wxEXPAND);
	Terrains_Holder_LongArea->Add(5, -1);
	Terrains_Holder_LongArea->Add(Terrains_Holder_SoundID, 1, wxEXPAND);
	Terrains_Holder_LongArea->Add(5, -1);
	Terrains_Holder_LongArea->Add(Terrains_Holder_BlendPriority, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_Holder_LongArea->Add(5, -1);
	Terrains_Holder_LongArea->Add(Terrains_Holder_BlendType, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Terrains_Holder_ShortArea->Add(Terrains_Holder_Colours, 1, wxEXPAND);
	Terrains_Holder_ShortArea->Add(5, -1);
	Terrains_Holder_ShortArea->Add(Terrains_Holder_FrameCount, 1, wxEXPAND);
	Terrains_Holder_ShortArea->Add(5, -1);
	Terrains_Holder_ShortArea->Add(Terrains_Holder_TerrainReplacementID, 1, wxEXPAND);
	Terrains_Holder_ShortArea->Add(5, -1);
	Terrains_Holder_ShortArea->Add(Terrains_Holder_TerrainDimensions, 1, wxEXPAND);
	
	Terrains_Holder_TerrainUnits->Add(Terrains_Holder_TerrainUnitID, 2, wxEXPAND);
	Terrains_Holder_TerrainUnits->Add(5, -1);
	Terrains_Holder_TerrainUnits->Add(Terrains_Holder_TerrainUnitDensity, 1, wxEXPAND);
	
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_NameArea, 0, wxEXPAND);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_LongArea, 0, wxEXPAND);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_ShortArea, 0, wxEXPAND);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_NumberOfTerrainUnitsUsed, 0, wxEXPAND);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_TerrainUnits, 0, wxEXPAND);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_Unknown1, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_Unknown2, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_Unknown3, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_Unknown5, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_Unknown6, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_Unknown8, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_Unknown9, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_Unknown7, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_Unknown10, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Terrains_ScrollerWindowsSpace->Add(-1, 5);
	Terrains_ScrollerWindowsSpace->Add(Terrains_Holder_Unknown11, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Terrains_ScrollerWindows->Add(Terrains_ScrollerWindowsSpace, 1, wxEXPAND);
	Terrains_ScrollerWindows->Add(5, -1);

	Terrains_Scroller->SetSizer(Terrains_ScrollerWindows);
	Terrains_Scroller->SetScrollRate(0, 15);

	Terrains_DataArea->Add(-1, 10);
	Terrains_DataArea->Add(Terrains_Scroller, 1, wxEXPAND);
	Terrains_DataArea->Add(-1, 10);

	Terrains_Main->Add(10, -1);
	Terrains_Main->Add(Terrains_ListArea, 1, wxEXPAND);
	Terrains_Main->Add(10, -1);
	Terrains_Main->Add(Terrains_DataArea, 3, wxEXPAND);
	Terrains_Main->Add(10, -1);
	
	Terrains_Colours->Enable(false);
	Terrains_Unknown7->Enable(false);
	Terrains_Unknown10->Enable(false);
	Terrains_Unknown11->Enable(false);

	Tab_Terrains->SetSizer(Terrains_Main);
	
	Connect(Terrains_Terrains_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	Connect(Terrains_Terrains_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainsSelect));
	Connect(Terrains_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsAdd));
	Connect(Terrains_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsDelete));
	Connect(Terrains_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsCopy));
	Connect(Terrains_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainsPaste));

	Terrains_Name->Connect(Terrains_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Terrains_Name2->Connect(Terrains_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);

}
