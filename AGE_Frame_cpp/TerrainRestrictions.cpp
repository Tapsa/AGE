/* AGEFrame_cpp/TerrainRestrictions.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetTerrainRestrictionName(int Index)
{
	string Name = "";
	Name = "Restriction " + lexical_cast<string>(Index);
	if(Index == 1)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 2)
	{
		Name = "Shoreline " + lexical_cast<string>(Index);
	}
	else if(Index == 3)
	{
		Name = "Waterborne " + lexical_cast<string>(Index);
	}
	else if(Index == 4)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 5)
	{
		Name = "All Restriction " + lexical_cast<string>(Index);
	}
	else if(Index == 6)
	{
		Name = "Waterborne " + lexical_cast<string>(Index);
	}
	else if(Index == 7)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 8)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 9)
	{
		Name = "All Restriction " + lexical_cast<string>(Index);
	}
	else if(Index == 10)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 11)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 12)
	{
		Name = "No Restriction " + lexical_cast<string>(Index);
	}
	else if(Index == 13)
	{
		Name = "Waterborne " + lexical_cast<string>(Index);
	}
	else if(Index == 14)
	{
		Name = "No Restriction " + lexical_cast<string>(Index);
	}
	else if(Index == 15)
	{
		Name = "Waterborne " + lexical_cast<string>(Index);
	}
	else if(Index == 16)
	{
		Name = "Grass 1 & Shoreline " + lexical_cast<string>(Index);
	}
	else if(Index == 17)
	{
		Name = "No Moving Restriction " + lexical_cast<string>(Index);
	}
	else if(Index == 18)
	{
		Name = "No Restriction " + lexical_cast<string>(Index);
	}
	else if(Index == 19)
	{
		Name = "Waterborne " + lexical_cast<string>(Index);
	}
	else if(Index == 20)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 21)
	{
		Name = "Waterborne " + lexical_cast<string>(Index);
	}
	return Name;
}

void AGE_Frame::ListTerrainRestrictions()
{
	string Name;
	wxString SearchText = wxString(TerrainLimits_TerrainLimits_Search->GetValue()).Lower();
	string CompareText;
	
	short RestrictionID = TerrainLimits_TerrainLimits_List->GetSelection();
	short RestrictionID1 = Units_ComboBox_TerrainRestriction->GetSelection();

	if(!TerrainLimits_TerrainLimits_List->IsEmpty())
	{
		TerrainLimits_TerrainLimits_List->Clear();
	}
	if(!Units_ComboBox_TerrainRestriction->IsEmpty())
	{
		Units_ComboBox_TerrainRestriction->Clear();
	}
	
	if(RestrictionID == wxNOT_FOUND)
	{
		RestrictionID = 0;
	}
	if(RestrictionID1 == wxNOT_FOUND)
	{
		RestrictionID1 = 0;
	}

	Units_ComboBox_TerrainRestriction->Append("-1 - None");
	
	for(short loop = 0;loop < GenieFile->TerrainRestrictions.size();loop++)
	{
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetTerrainRestrictionName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTerrainRestrictionName(loop)).Lower();
		if((SearchText.IsEmpty()) || (CompareText.find(SearchText) != string::npos))
		{
			TerrainLimits_TerrainLimits_List->Append(Name, (void*)&GenieFile->TerrainRestrictions[loop]);
		}
		Units_ComboBox_TerrainRestriction->Append(Name);
	}
	
	TerrainLimits_TerrainLimits_List->SetSelection(0);
	TerrainLimits_TerrainLimits_List->SetSelection(RestrictionID);
	Units_ComboBox_TerrainRestriction->SetSelection(RestrictionID1);
	
	wxCommandEvent E;
//	OnTerrainRestrictionsSelect(E);
	OnTerrainRestrictionsTerrainSelect(E);
}

void AGE_Frame::OnTerrainRestrictionsSearch(wxCommandEvent& Event)
{
	ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsSelect(wxCommandEvent& Event)
{
//	wxCommandEvent E;
//	OnTerrainRestrictionsTerrainSelect(E);
}

void AGE_Frame::OnTerrainRestrictionsTerrainSelect(wxCommandEvent& Event)
{
	gdat::Terrain * TerrainPointer = (gdat::Terrain*)TerrainLimits_Terrains_List->GetClientData(TerrainLimits_Terrains_List->GetSelection());
	short TerrainID = TerrainPointer - (&GenieFile->Terrains[0]);
//	wxMessageBox("Terrain "+lexical_cast<string>(TerrainID));
	short RestrictionID = TerrainLimits_TerrainLimits_List->GetSelection();
	if((RestrictionID != wxNOT_FOUND) && (TerrainID != wxNOT_FOUND))
	{
		gdat::TerrainRestriction * TerrainRestrictionPointer = (gdat::TerrainRestriction*)TerrainLimits_TerrainLimits_List->GetClientData(RestrictionID);
		TerrainLimits_Accessible->SetValue(lexical_cast<string>(TerrainRestrictionPointer->TerrainAccessible[TerrainID]));
		TerrainLimits_Accessible->Container = &TerrainRestrictionPointer->TerrainAccessible[TerrainID];
		TerrainLimits_CheckBox_Accessible->SetValue((bool)TerrainRestrictionPointer->TerrainAccessible[TerrainID]);
		if(GameVersion > 1)	//	Above AoE and RoR
		{
			TerrainLimits_Unknown1->SetValue(lexical_cast<string>(TerrainRestrictionPointer->TerrainPassGraphics[TerrainID].Buildable));
			TerrainLimits_Unknown1->Container = &TerrainRestrictionPointer->TerrainPassGraphics[TerrainID].Buildable;
			switch(TerrainRestrictionPointer->TerrainPassGraphics[TerrainID].Buildable)
			{
				case -1:
				{
					TerrainLimits_CheckBox_Unknown1->SetValue(false);
				}
				break;
				case 0:
				{
					TerrainLimits_CheckBox_Unknown1->SetValue(true);
				}
				break;
				default:
				{
					TerrainLimits_CheckBox_Unknown1->SetValue(false);
				}
				break;
			}
			TerrainLimits_Graphics[0]->SetValue(lexical_cast<string>(TerrainRestrictionPointer->TerrainPassGraphics[TerrainID].GraphicIDs.first));
			TerrainLimits_Graphics[0]->Container = &TerrainRestrictionPointer->TerrainPassGraphics[TerrainID].GraphicIDs.first;
			TerrainLimits_Graphics[1]->SetValue(lexical_cast<string>(TerrainRestrictionPointer->TerrainPassGraphics[TerrainID].GraphicIDs.second));
			TerrainLimits_Graphics[1]->Container = &TerrainRestrictionPointer->TerrainPassGraphics[TerrainID].GraphicIDs.second;
			TerrainLimits_ComboBox_Graphics[0]->SetSelection(TerrainRestrictionPointer->TerrainPassGraphics[TerrainID].GraphicIDs.first + 1);
			TerrainLimits_ComboBox_Graphics[1]->SetSelection(TerrainRestrictionPointer->TerrainPassGraphics[TerrainID].GraphicIDs.second + 1);
			TerrainLimits_Amount->SetValue(lexical_cast<string>(TerrainRestrictionPointer->TerrainPassGraphics[TerrainID].ReplicationAmount));
			TerrainLimits_Amount->Container = &TerrainRestrictionPointer->TerrainPassGraphics[TerrainID].ReplicationAmount;
		}
	}
}

void AGE_Frame::OnTerrainRestrictionsAdd(wxCommandEvent& Event)
{
	gdat::TerrainRestriction Temp;
	Temp.TerrainAccessible.resize(GenieFile->Terrains.size());
	Temp.TerrainPassGraphics.resize(GenieFile->Terrains.size());
	GenieFile->TerrainRestrictions.push_back(Temp);
	ListTerrainRestrictions();
	TerrainLimits_TerrainLimits_List->SetSelection(TerrainLimits_TerrainLimits_List->GetCount() - 1);
	wxCommandEvent E;
//	OnTerrainRestrictionsSelect(E);
	OnTerrainRestrictionsTerrainSelect(E);
}

void AGE_Frame::OnTerrainRestrictionsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short RestrictionID = TerrainLimits_TerrainLimits_List->GetSelection();
	if(RestrictionID != wxNOT_FOUND)
	{
		gdat::TerrainRestriction * TerrainRestrictionPointer = (gdat::TerrainRestriction*)TerrainLimits_TerrainLimits_List->GetClientData(RestrictionID);
		GenieFile->TerrainRestrictions.erase(GenieFile->TerrainRestrictions.begin() + (TerrainRestrictionPointer - (&GenieFile->TerrainRestrictions[0])));
		ListTerrainRestrictions();
		TerrainLimits_TerrainLimits_List->SetSelection(TerrainLimits_TerrainLimits_List->GetCount() - 1);
		TerrainLimits_TerrainLimits_List->SetSelection(RestrictionID - 1);
		TerrainLimits_TerrainLimits_List->SetSelection(RestrictionID);
	}
}

void AGE_Frame::OnTerrainRestrictionsCopy(wxCommandEvent& Event)
{
	short RestrictionID = TerrainLimits_TerrainLimits_List->GetSelection();
	if(RestrictionID != wxNOT_FOUND)
	{
		TerrainRestrictionCopy = *(gdat::TerrainRestriction*)TerrainLimits_TerrainLimits_List->GetClientData(RestrictionID);
	}
}

void AGE_Frame::OnTerrainRestrictionsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short RestrictionID = TerrainLimits_TerrainLimits_List->GetSelection();
	if(RestrictionID != wxNOT_FOUND)
	{
		*(gdat::TerrainRestriction*)TerrainLimits_TerrainLimits_List->GetClientData(RestrictionID) = TerrainRestrictionCopy;
		ListTerrainRestrictions();
		TerrainLimits_TerrainLimits_List->SetSelection(RestrictionID + 3);
		TerrainLimits_TerrainLimits_List->SetSelection(RestrictionID);
	}
}

void AGE_Frame::OnTerrainRestrictionsTerrainCopy(wxCommandEvent& Event)
{
	gdat::TerrainRestriction * TerrainRestrictionPointer = (gdat::TerrainRestriction*)TerrainLimits_TerrainLimits_List->GetClientData(TerrainLimits_TerrainLimits_List->GetSelection());
	gdat::Terrain * TerrainPointer = (gdat::Terrain*)TerrainLimits_Terrains_List->GetClientData(TerrainLimits_Terrains_List->GetSelection());
	short RestrictionID = TerrainRestrictionPointer - (&GenieFile->TerrainRestrictions[0]);;
	short TerrainID = TerrainPointer - (&GenieFile->Terrains[0]);
	if((RestrictionID != wxNOT_FOUND) && (TerrainID != wxNOT_FOUND))
	{
		TerrainRestrictionSubCopyAccess = GenieFile->TerrainRestrictions[RestrictionID].TerrainAccessible[TerrainID];
		if(GameVersion > 1)	// not AoE nor RoR
		{
			TerrainRestrictionSubCopy = GenieFile->TerrainRestrictions[RestrictionID].TerrainPassGraphics[TerrainID];
		}
	}
}

void AGE_Frame::OnTerrainRestrictionsTerrainPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	gdat::TerrainRestriction * TerrainRestrictionPointer = (gdat::TerrainRestriction*)TerrainLimits_TerrainLimits_List->GetClientData(TerrainLimits_TerrainLimits_List->GetSelection());
	gdat::Terrain * TerrainPointer = (gdat::Terrain*)TerrainLimits_Terrains_List->GetClientData(TerrainLimits_Terrains_List->GetSelection());
	short RestrictionID = TerrainRestrictionPointer - (&GenieFile->TerrainRestrictions[0]);;
	short TerrainID = TerrainPointer - (&GenieFile->Terrains[0]);
	if((RestrictionID != wxNOT_FOUND) && (TerrainID != wxNOT_FOUND))
	{
		GenieFile->TerrainRestrictions[RestrictionID].TerrainAccessible[TerrainID] = TerrainRestrictionSubCopyAccess;
		if(GameVersion > 1)	// not AoE nor RoR
		{
			GenieFile->TerrainRestrictions[RestrictionID].TerrainPassGraphics[TerrainID] = TerrainRestrictionSubCopy;
		}
		wxCommandEvent E;
		OnTerrainRestrictionsTerrainSelect(E);
	}
}

void AGE_Frame::CreateTerrainRestrictionControls()
{

	Tab_TerrainRestrictions = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(-1, 350));
	TerrainLimits_Main = new wxBoxSizer(wxHORIZONTAL);
	TerrainLimits_ListArea = new wxBoxSizer(wxVERTICAL);
	TerrainLimits_TerrainLimits_Buttons = new wxGridSizer(2, 0, 0);
	TerrainLimits_TerrainLimits = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainRestrictions, "Terrain Restriction Slot");
	TerrainLimits_TerrainLimits_Search = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
	TerrainLimits_TerrainLimits_List = new wxListBox(Tab_TerrainRestrictions, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	TerrainLimits_Add = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Add", wxDefaultPosition, wxSize(-1, 20));
	TerrainLimits_Delete = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Delete", wxDefaultPosition, wxSize(-1, 20));
	TerrainLimits_Copy = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	TerrainLimits_Paste = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));

	TerrainLimits_Terrains = new wxBoxSizer(wxVERTICAL);
	TerrainLimits_DataArea = new wxBoxSizer(wxVERTICAL);
	TerrainLimits_Terrains_Search = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
	TerrainLimits_Terrains_List = new wxListBox(Tab_TerrainRestrictions, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	TerrainLimits_Terrains_Buttons = new wxGridSizer(2, 0, 0);
	TerrainLimits_Terrains_Copy = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	TerrainLimits_Terrains_Paste = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));
	TerrainLimits_Holder_Accessible = new wxBoxSizer(wxVERTICAL);
	TerrainLimits_Holder_Accessible2 = new wxBoxSizer(wxHORIZONTAL);
	TerrainLimits_Text_Accessible = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Accessible", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerrainLimits_Accessible = new TextCtrl_Float(Tab_TerrainRestrictions, "0", NULL);
	TerrainLimits_CheckBox_Accessible = new CheckBox_Float(Tab_TerrainRestrictions, "Terrain Is Accessible", TerrainLimits_Accessible);
	TerrainLimits_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	TerrainLimits_Holder_Unknown1Sub = new wxBoxSizer(wxHORIZONTAL);
	TerrainLimits_Text_Unknown1 = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Can Be Built On", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerrainLimits_Unknown1 = new TextCtrl_Long(Tab_TerrainRestrictions, "0", NULL);
	TerrainLimits_CheckBox_Unknown1 = new CheckBox_Long_ZeroIsYes(Tab_TerrainRestrictions, "No", TerrainLimits_Unknown1);
	TerrainLimits_Holder_Graphics = new wxBoxSizer(wxVERTICAL);
	TerrainLimits_Text_Graphics = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Graphics", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerrainLimits_Graphics[0] = new TextCtrl_Long(Tab_TerrainRestrictions, "0", NULL);
	TerrainLimits_Graphics[1] = new TextCtrl_Long(Tab_TerrainRestrictions, "0", NULL);
	TerrainLimits_ComboBox_Graphics[0] = new ComboBox_Long(Tab_TerrainRestrictions, TerrainLimits_Graphics[0]);
	TerrainLimits_ComboBox_Graphics[1] = new ComboBox_Long(Tab_TerrainRestrictions, TerrainLimits_Graphics[1]);
	TerrainLimits_Holder_Amount = new wxBoxSizer(wxVERTICAL);
	TerrainLimits_Text_Amount = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Replication Amount", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerrainLimits_Amount = new TextCtrl_Long(Tab_TerrainRestrictions, "0", NULL);

	TerrainLimits_TerrainLimits_Buttons->Add(TerrainLimits_Add, 1, wxEXPAND);
	TerrainLimits_TerrainLimits_Buttons->Add(TerrainLimits_Delete, 1, wxEXPAND);
	TerrainLimits_TerrainLimits_Buttons->Add(TerrainLimits_Copy, 1, wxEXPAND);
	TerrainLimits_TerrainLimits_Buttons->Add(TerrainLimits_Paste, 1, wxEXPAND);

	TerrainLimits_TerrainLimits->Add(TerrainLimits_TerrainLimits_Search, 0, wxEXPAND);
	TerrainLimits_TerrainLimits->Add(-1, 2);
	TerrainLimits_TerrainLimits->Add(TerrainLimits_TerrainLimits_List, 1, wxEXPAND);
	TerrainLimits_TerrainLimits->Add(-1, 2);
	TerrainLimits_TerrainLimits->Add(TerrainLimits_TerrainLimits_Buttons, 0, wxEXPAND);

	TerrainLimits_ListArea->Add(-1, 10);
	TerrainLimits_ListArea->Add(TerrainLimits_TerrainLimits, 1, wxEXPAND);
	TerrainLimits_ListArea->Add(-1, 10);

	TerrainLimits_Terrains_Buttons->Add(TerrainLimits_Terrains_Copy, 1, wxEXPAND);
	TerrainLimits_Terrains_Buttons->Add(TerrainLimits_Terrains_Paste, 1, wxEXPAND);
	
	TerrainLimits_Terrains->Add(-1, 10);
	TerrainLimits_Terrains->Add(TerrainLimits_Terrains_Search, 0, wxEXPAND);
	TerrainLimits_Terrains->Add(-1, 2);
	TerrainLimits_Terrains->Add(TerrainLimits_Terrains_List, 1, wxEXPAND);
	TerrainLimits_Terrains->Add(-1, 2);
	TerrainLimits_Terrains->Add(TerrainLimits_Terrains_Buttons, 0, wxEXPAND);
	TerrainLimits_Terrains->Add(-1, 10);

	TerrainLimits_Holder_Accessible2->Add(TerrainLimits_Accessible, 1, wxEXPAND);
	TerrainLimits_Holder_Accessible2->Add(2, -1);
	TerrainLimits_Holder_Accessible2->Add(TerrainLimits_CheckBox_Accessible, 2, wxEXPAND);
	TerrainLimits_Holder_Accessible->Add(TerrainLimits_Text_Accessible, 0, wxEXPAND);
	TerrainLimits_Holder_Accessible->Add(-1, 2);
	TerrainLimits_Holder_Accessible->Add(TerrainLimits_Holder_Accessible2, 1, wxEXPAND);

	TerrainLimits_Holder_Unknown1Sub->Add(TerrainLimits_Unknown1, 1, wxEXPAND);
	TerrainLimits_Holder_Unknown1Sub->Add(2, -1);
	TerrainLimits_Holder_Unknown1Sub->Add(TerrainLimits_CheckBox_Unknown1, 1, wxEXPAND);
	TerrainLimits_Holder_Unknown1->Add(TerrainLimits_Text_Unknown1, 0, wxEXPAND);
	TerrainLimits_Holder_Unknown1->Add(-1, 2);
	TerrainLimits_Holder_Unknown1->Add(TerrainLimits_Holder_Unknown1Sub, 1, wxEXPAND);
	TerrainLimits_Holder_Graphics->Add(TerrainLimits_Text_Graphics, 0, wxEXPAND);
	TerrainLimits_Holder_Graphics->Add(-1, 2);
	TerrainLimits_Holder_Graphics->Add(TerrainLimits_Graphics[0], 1, wxEXPAND);
	TerrainLimits_Holder_Graphics->Add(TerrainLimits_ComboBox_Graphics[0], 1, wxEXPAND);
	TerrainLimits_Holder_Graphics->Add(TerrainLimits_Graphics[1], 1, wxEXPAND);
	TerrainLimits_Holder_Graphics->Add(TerrainLimits_ComboBox_Graphics[1], 1, wxEXPAND);
	TerrainLimits_Holder_Amount->Add(TerrainLimits_Text_Amount, 0, wxEXPAND);
	TerrainLimits_Holder_Amount->Add(-1, 2);
	TerrainLimits_Holder_Amount->Add(TerrainLimits_Amount, 1, wxEXPAND);

	TerrainLimits_DataArea->Add(-1, 10);
	TerrainLimits_DataArea->Add(TerrainLimits_Holder_Accessible, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	TerrainLimits_DataArea->Add(-1, 5);
	TerrainLimits_DataArea->Add(TerrainLimits_Holder_Unknown1, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	TerrainLimits_DataArea->Add(-1, 5);
	TerrainLimits_DataArea->Add(TerrainLimits_Holder_Graphics, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	TerrainLimits_DataArea->Add(-1, 5);
	TerrainLimits_DataArea->Add(TerrainLimits_Holder_Amount, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	TerrainLimits_DataArea->Add(-1, 10);

	TerrainLimits_Main->Add(10, -1);
	TerrainLimits_Main->Add(TerrainLimits_ListArea, 1, wxEXPAND);
	TerrainLimits_Main->Add(10, -1);
	TerrainLimits_Main->Add(TerrainLimits_Terrains, 1, wxEXPAND);
	TerrainLimits_Main->Add(10, -1);
	TerrainLimits_Main->Add(TerrainLimits_DataArea, 1, wxEXPAND);
	TerrainLimits_Main->AddStretchSpacer(1);

	Tab_TerrainRestrictions->SetSizer(TerrainLimits_Main);
	
	Connect(TerrainLimits_TerrainLimits_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsSearch));
	Connect(TerrainLimits_TerrainLimits_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainSelect));
	Connect(TerrainLimits_Terrains_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	Connect(TerrainLimits_Terrains_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainSelect));
	Connect(TerrainLimits_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsAdd));
	Connect(TerrainLimits_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsDelete));
	Connect(TerrainLimits_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsCopy));
	Connect(TerrainLimits_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsPaste));
	Connect(TerrainLimits_Terrains_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainCopy));
	Connect(TerrainLimits_Terrains_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainPaste));
}
