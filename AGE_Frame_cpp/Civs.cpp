/* AGEFrame_cpp/Civs.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetCivName(short Index)
{
	string Name = "";
	Name = GenieFile->Civs[Index].Name+" ("+lexical_cast<string>((short)GenieFile->Civs[Index].GraphicSet)+")";
	return Name;
}

void AGE_Frame::ListCivs()
{
	string Name;
	SearchText = wxString(Civs_Civs_Search->GetValue()).Lower();
	ExcludeText = wxString(Civs_Civs_Search_R->GetValue()).Lower();
	string CompareText;
	
	short Selection = Civs_Civs_List->GetSelection();
	short CivID1 = Research_ComboBox_Civ->GetSelection();
	short CivID2 = Units_Civs_List->GetSelection();
	short CivID3 = SoundItems_ComboBox_Civ->GetSelection();

	if(!Civs_Civs_List->IsEmpty())
	{
		Civs_Civs_List->Clear();
	}
	if(!Research_ComboBox_Civ->IsEmpty())
	{
		Research_ComboBox_Civ->Clear();
	}
	if(!Units_Civs_List->IsEmpty())
	{
		Units_Civs_List->Clear();
	}
	if(!SoundItems_ComboBox_Civ->IsEmpty())
	{
		SoundItems_ComboBox_Civ->Clear();
	}
	
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	if(CivID1 == wxNOT_FOUND)
	{
		CivID1 = 0;
	}
	if(CivID2 == wxNOT_FOUND)
	{
		CivID2 = 0;
	}
	if(CivID3 == wxNOT_FOUND)
	{
		CivID3 = 0;
	}
	
	Research_ComboBox_Civ->Append("-1 - None");
	SoundItems_ComboBox_Civ->Append("-1 - None");
	
	for(short loop = 0;loop < GenieFile->Civs.size();loop++)
	{
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetCivName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetCivName(loop)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Civs_Civs_List->Append(Name, (void*)&GenieFile->Civs[loop]);
		}
		Research_ComboBox_Civ->Append(Name);
		Units_Civs_List->Append(Name);
		SoundItems_ComboBox_Civ->Append(Name);
	}
	
	Civs_Civs_List->SetSelection(0);
	Civs_Civs_List->SetFirstItem(Selection - 3);
	Civs_Civs_List->SetSelection(Selection);
	Research_ComboBox_Civ->SetSelection(CivID1);
	Units_Civs_List->SetSelection(CivID2);
	SoundItems_ComboBox_Civ->SetSelection(CivID3);

	wxCommandEvent E;
	OnCivsSelect(E);
}

void AGE_Frame::OnCivsSearch(wxCommandEvent& Event)
{
	ListCivs();
}

void AGE_Frame::OnCivsSelect(wxCommandEvent& Event)
{
	short Selection = Civs_Civs_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Civs_Civs_List->GetCount() - 1;
			Civs_Civs_List->SetSelection(Selection);
		}
		gdat::Civ * CivPointer = (gdat::Civ*)Civs_Civs_List->GetClientData(Selection);
		CivID = CivPointer - (&GenieFile->Civs[0]);
		Civs_One->ChangeValue(lexical_cast<string>((short)CivPointer->One));
		Civs_One->Container = &CivPointer->One;
		Civs_Name[0]->ChangeValue(CivPointer->Name);
		Civs_Name[0]->Container = &CivPointer->Name;
		if(GameVersion >= 4)
		{
			Civs_Holder_Name[1]->Show(true);
			if(ShowUnknowns) Civs_Holder_SUnknown1->Show(true);
			
			Civs_Name[1]->ChangeValue(CivPointer->Name);
			Civs_Name[1]->Container = &CivPointer->Name;
			for(short loop = 0;loop < 4;loop++)
			Civs_SUnknown1[loop]->ChangeValue(lexical_cast<string>(CivPointer->SUnknown1[loop]));
		}
		else
		{
			Civs_Holder_Name[1]->Show(false);
			Civs_Holder_SUnknown1->Show(false);
		}
		Civs_TechTree->ChangeValue(lexical_cast<string>(CivPointer->TechTreeID));
		Civs_TechTree->Container = &CivPointer->TechTreeID;
		Civs_ComboBox_TechTree->SetSelection(CivPointer->TechTreeID + 1);
		if(GameVersion >= 2)
		{
			Civs_Holder_TeamBonus->Show(true);
			
			Civs_TeamBonus->ChangeValue(lexical_cast<string>(CivPointer->TeamBonusID));
			Civs_TeamBonus->Container = &CivPointer->TeamBonusID;
		}
		else
		{
			Civs_Holder_TeamBonus->Show(false);
		}
		Civs_ComboBox_TeamBonus->SetSelection(CivPointer->TeamBonusID + 1);
		Civs_GraphicSet->ChangeValue(lexical_cast<string>((short)CivPointer->GraphicSet));
		Civs_GraphicSet->Container = &CivPointer->GraphicSet;
		Added = false;
		ListResources(CivID);
	}
}

void AGE_Frame::OnCivsAdd(wxCommandEvent& Event)
{
	gdat::Civ Temp;
	Temp.Resources.resize(GenieFile->Civs[0].Resources.size());
	Temp.Units.resize(GenieFile->Civs[0].Units.size());
	GenieFile->Civs.push_back(Temp);
	Added = true;
	ListCivs();
}

void AGE_Frame::OnCivsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Civs_Civs_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->Civs.erase(GenieFile->Civs.begin() + CivID);
		if(Selection == Civs_Civs_List->GetCount() - 1)
		Civs_Civs_List->SetSelection(Selection - 1);
		ListCivs();
	}
}

void AGE_Frame::OnCivsCopy(wxCommandEvent& Event)
{
	short Selection = Civs_Civs_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		CivCopy = *(gdat::Civ*)Civs_Civs_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnCivsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Civs_Civs_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::Civ*)Civs_Civs_List->GetClientData(Selection) = CivCopy;
		ListCivs();
	}
}

string AGE_Frame::GetResourceName(short Index, short CivID)
{
	string Name = "";
	if(Index == 0)
	{
		Name = "Food Storage";
	}
	else if(Index == 1)
	{
		Name = "Wood Storage";
	}
	else if(Index == 2)
	{
		Name = "Stone Storage";
	}
	else if(Index == 3)
	{
		Name = "Gold Storage ";
	}
	else if(Index == 4)
	{
		Name = "Population Headroom";
	}
	else if(Index == 6)
	{
		Name = "Current Age";
	}
	else if(Index == 7)
	{
		Name = "Captured Relics";
	}
	else if(Index == 9)
	{
		Name = "Goods (Used by Trade Workshops and Docks)";
	}
	else if(Index == 11)
	{
		Name = "Population (Both Current and Headroom)";
	}
	else if(Index == 12)
	{
		Name = "Corpse Decay Time";
	}
	else if(Index == 14)
	{
		Name = "Ruin (Unused)";
	}
	else if(Index == 17)
	{
		Name = "Whale Storage";
	}
	else if(Index == 19)
	{
		Name = "Military Room (Used for counting Losses)";
	}
	else if(Index == 20)
	{
		Name = "Kill";
	}
	else if(Index == 21)
	{
		Name = "Researched Technologies";
	}
	else if(Index == 23)
	{
		Name = "Technology 1?";
	}
	else if(Index == 24)
	{
		Name = "Technology 2?";
	}
	else if(Index == 25)
	{
		Name = "Technology 3?";
	}
	else if(Index == 27)
	{
		Name = "Atonement (Boolean)";
	}
	else if(Index == 28)
	{
		Name = "Redemption (Boolean)";
	}
	else if(Index == 30)
	{
		Name = "(Unknown)";
	}
	else if(Index == 32)
	{
		Name = "Bonus Population";
	}
	else if(Index == 35)
	{
		Name = "Faith Recharging Rate";
	}
	else if(Index == 36)
	{
		Name = "Farm Food Amount";
	}
	else if(Index == 37)
	{
		Name = "Civilian Population";
	}
	else if(Index == 39)
	{
		Name = "Technology 4?";
	}
	else if(Index == 40)
	{
		Name = "Military Population";
	}
	else if(Index == 41)
	{
		Name = "Conversion Made";
	}
	else if(Index == 43)
	{
		Name = "Razing";
	}
	else if(Index == 44)
	{
		Name = "Kill Ratio";
	}
	else if(Index == 45)
	{
		Name = "Survival to Finish (Boolean)";
	}
	else if(Index == 46)
	{
		Name = "Tribute Fee";
	}
	else if(Index == 47)
	{
		Name = "Gold Mining Productivity";
	}
	else if(Index == 50)
	{
		Name = "Reveal Ally (Boolean)";
	}
	else if(Index == 56)
	{
		Name = "Ore Storage? Unit Unload Room?";
	}
	else if(Index == 58)
	{
		Name = "Technology 5?";
	}
	else if(Index == 59)
	{
		Name = "(Boolean)";
	}
	else if(Index == 60)
	{
		Name = "(Boolean)";
	}
	else if(Index == 62)
	{
		Name = "Unknown";
	}
	else if(Index == 65)
	{
		Name = "(Unknown)";
	}
	else if(Index == 66)
	{
		Name = "Dark Age? (Boolean)";
	}
	else if(Index == 67)
	{
		Name = "Conversion (Boolean)";
	}
	else if(Index == 77)
	{
		Name = "Conversion Resistance 1";
	}
	else if(Index == 78)
	{
		Name = "Trade Fee";
	}
	else if(Index == 79)
	{
		Name = "Stone Mining Productivity";
	}
	else if(Index == 80)
	{
		Name = "Achievements, Relic Gold";
	}
	else if(Index == 81)
	{
		Name = "Achievements, Trade Profit";
	}
	else if(Index == 83)
	{
		Name = "(Unknown)";
	}
	else if(Index == 84)
	{
		Name = "Starting Villager";
	}
	else if(Index == 85)
	{
		Name = "Technology Research Cost";
	}
	else if(Index == 87)
	{
		Name = "Boarding (Boolean)";
	}
	else if(Index == 88)
	{
		Name = "Fish Trap Food Amount";
	}
	else if(Index == 89)
	{
		Name = "Bonus Healing Rate";
	}
	else if(Index == 90)
	{
		Name = "Healing Range";
	}
	else if(Index == 91)
	{
		Name = "Bonus Starting Food";
	}
	else if(Index == 92)
	{
		Name = "Bonus Starting Wood";
	}
	else if(Index == 93)
	{
		Name = "Bonus Starting Stone";
	}
	else if(Index == 94)
	{
		Name = "Bonus Starting Gold";
	}
	else if(Index == 95)
	{
		Name = "(Unknown)";
	}
	else if(Index == 96)
	{
		Name = "Berserker Self-Healing Second(s)";
	}
	else if(Index == 97)
	{
		Name = "Sheep/Turkey Dominant LOS (Boolean)";
	}
	else if(Index == 98)
	{
		Name = "(Unknown)";
	}
	else if(Index == 164)
	{
		Name = "(Unknown)";
	}
	else if(Index == 165)
	{
		Name = "(Unknown)";
	}
	else if(Index == 178)
	{
		Name = "Conversion Resistance 2";
	}
	else if(Index == 179)
	{
		Name = "Conversion Resistance 3";
	}
	else if(Index == 180)
	{
		Name = "(Unknown)";
	}
	else if(Index == 181)
	{
		Name = "(Unknown)";
	}
	else if(Index == 182)
	{
		Name = "(Unknown)";
	}
	else if(Index == 183)
	{
		Name = "Reveal Enemy (Boolean)";
	}
	else if(Index == 189)
	{
		Name = "Chopping Productivity";
	}
	else if(Index == 190)
	{
		Name = "Food-gathering Productivity";
	}
	else if(Index == 191)
	{
		Name = "Relic Gold Production";
	}
	else if(Index == 192)
	{
		Name = "Heresy (Boolean)";
	}
	else if(Index == 193)
	{
		Name = "Theocracy (Boolean)";
	}
	else if(Index == 194)
	{
		Name = "Crenellations (Boolean)";
	}
	else if(Index == 195)
	{
		Name = "Building Rate (Except Wonder)";
	}
	else if(Index == 196)
	{
		Name = "Wonder Victory Time?";
	}
	else if(Index == 197)
	{
		Name = "Atheism (Boolean)";
	}
	else
	{
		Name = "Unknown";
	}
	return Name;
}
	
void AGE_Frame::ListResources(short Index)
{
	string Name;
	SearchText = wxString(Civs_Resources_Search->GetValue()).Lower();
	ExcludeText = wxString(Civs_Resources_Search_R->GetValue()).Lower();
	string CompareText;
	
	short Selection = Civs_Resources_List->GetSelection();
	short ResourceID1 = Units_ComboBox_CostType[0]->GetSelection();
	short ResourceID2 = Units_ComboBox_CostType[1]->GetSelection();
	short ResourceID3 = Units_ComboBox_CostType[2]->GetSelection();
	short ResourceID4 = ResourceStorage_ComboBox_Type[0]->GetSelection();
	short ResourceID5 = ResourceStorage_ComboBox_Type[1]->GetSelection();
	short ResourceID6 = ResourceStorage_ComboBox_Type[2]->GetSelection();
	short ResourceID7 = UnitCommands_ComboBox_ResourceIn->GetSelection();
	short ResourceID8 = UnitCommands_ComboBox_ResourceOut->GetSelection();
	short ResourceID9 = Research_ComboBox_Resources[0]->GetSelection();
	short ResourceID10 = Research_ComboBox_Resources[1]->GetSelection();
	short ResourceID11 = Research_ComboBox_Resources[2]->GetSelection();
	short ResourceID12 = Effects_ComboBox_ResourcesA->GetSelection();
	short ResourceID13 = Effects_ComboBox_ResourcesB->GetSelection();

	if(!Civs_Resources_List->IsEmpty())
	{
		Civs_Resources_List->Clear();
	}
	if(!Units_ComboBox_CostType[0]->IsEmpty())
	{
		Units_ComboBox_CostType[0]->Clear();
	}
	if(!Units_ComboBox_CostType[1]->IsEmpty())
	{
		Units_ComboBox_CostType[1]->Clear();
	}
	if(!Units_ComboBox_CostType[2]->IsEmpty())
	{
		Units_ComboBox_CostType[2]->Clear();
	}
	if(!ResourceStorage_ComboBox_Type[0]->IsEmpty())
	{
		ResourceStorage_ComboBox_Type[0]->Clear();
	}
	if(!ResourceStorage_ComboBox_Type[1]->IsEmpty())
	{
		ResourceStorage_ComboBox_Type[1]->Clear();
	}
	if(!ResourceStorage_ComboBox_Type[2]->IsEmpty())
	{
		ResourceStorage_ComboBox_Type[2]->Clear();
	}
	if(!UnitCommands_ComboBox_ResourceIn->IsEmpty())
	{
		UnitCommands_ComboBox_ResourceIn->Clear();
	}
	if(!UnitCommands_ComboBox_ResourceOut->IsEmpty())
	{
		UnitCommands_ComboBox_ResourceOut->Clear();
	}
	if(!Research_ComboBox_Resources[0]->IsEmpty())
	{
		Research_ComboBox_Resources[0]->Clear();
	}
	if(!Research_ComboBox_Resources[1]->IsEmpty())
	{
		Research_ComboBox_Resources[1]->Clear();
	}
	if(!Research_ComboBox_Resources[2]->IsEmpty())
	{
		Research_ComboBox_Resources[2]->Clear();
	}
	if(!Effects_ComboBox_ResourcesA->IsEmpty())
	{
		Effects_ComboBox_ResourcesA->Clear();
	}
	if(!Effects_ComboBox_ResourcesB->IsEmpty())
	{
		Effects_ComboBox_ResourcesB->Clear();
	}
	
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	if(ResourceID1 == wxNOT_FOUND)
	{
		ResourceID1 = 0;
	}
	if(ResourceID2 == wxNOT_FOUND)
	{
		ResourceID2 = 0;
	}
	if(ResourceID3 == wxNOT_FOUND)
	{
		ResourceID3 = 0;
	}
	if(ResourceID4 == wxNOT_FOUND)
	{
		ResourceID4 = 0;
	}
	if(ResourceID5 == wxNOT_FOUND)
	{
		ResourceID5 = 0;
	}
	if(ResourceID6 == wxNOT_FOUND)
	{
		ResourceID6 = 0;
	}
	if(ResourceID7 == wxNOT_FOUND)
	{
		ResourceID7 = 0;
	}
	if(ResourceID8 == wxNOT_FOUND)
	{
		ResourceID8 = 0;
	}
	if(ResourceID9 == wxNOT_FOUND)
	{
		ResourceID9 = 0;
	}
	if(ResourceID10 == wxNOT_FOUND)
	{
		ResourceID10 = 0;
	}
	if(ResourceID11 == wxNOT_FOUND)
	{
		ResourceID11 = 0;
	}
	if(ResourceID12 == wxNOT_FOUND)
	{
		ResourceID12 = 0;
	}
	if(ResourceID13 == wxNOT_FOUND)
	{
		ResourceID13 = 0;
	}
	
	Units_ComboBox_CostType[0]->Append("-1 - None");
	Units_ComboBox_CostType[1]->Append("-1 - None");
	Units_ComboBox_CostType[2]->Append("-1 - None");
	ResourceStorage_ComboBox_Type[0]->Append("-1 - None");
	ResourceStorage_ComboBox_Type[1]->Append("-1 - None");
	ResourceStorage_ComboBox_Type[2]->Append("-1 - None");
	UnitCommands_ComboBox_ResourceIn->Append("-1 - None");
	UnitCommands_ComboBox_ResourceOut->Append("-1 - None");
	Research_ComboBox_Resources[0]->Append("-1 - None");
	Research_ComboBox_Resources[1]->Append("-1 - None");
	Research_ComboBox_Resources[2]->Append("-1 - None");
	Effects_ComboBox_ResourcesA->Append("-1 - None");
	Effects_ComboBox_ResourcesB->Append("-1 - None");
	
	for(short loop = 0;loop < GenieFile->Civs[Index].Resources.size();loop++)
	{
		Name = lexical_cast<string>(loop);
		Name += " - Value: ";
		Name += lexical_cast<string>(GenieFile->Civs[Index].Resources[loop]);
		Name += " - ";
		Name += GetResourceName(loop, Index);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetResourceName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Civs_Resources_List->Append(Name, (void*)&GenieFile->Civs[Index].Resources[loop]);
		}
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetResourceName(loop, 0);
		Units_ComboBox_CostType[0]->Append(Name);
		Units_ComboBox_CostType[1]->Append(Name);
		Units_ComboBox_CostType[2]->Append(Name);
		ResourceStorage_ComboBox_Type[0]->Append(Name);
		ResourceStorage_ComboBox_Type[1]->Append(Name);
		ResourceStorage_ComboBox_Type[2]->Append(Name);
		UnitCommands_ComboBox_ResourceIn->Append(Name);
		UnitCommands_ComboBox_ResourceOut->Append(Name);
		Research_ComboBox_Resources[0]->Append(Name);
		Research_ComboBox_Resources[1]->Append(Name);
		Research_ComboBox_Resources[2]->Append(Name);
		Effects_ComboBox_ResourcesA->Append(Name);
		Effects_ComboBox_ResourcesB->Append(Name);
	}
	
	Civs_Resources_List->SetSelection(0);
	Civs_Resources_List->SetFirstItem(Selection - 3);
	Civs_Resources_List->SetSelection(Selection);
	Units_ComboBox_CostType[0]->SetSelection(ResourceID1);
	Units_ComboBox_CostType[1]->SetSelection(ResourceID2);
	Units_ComboBox_CostType[2]->SetSelection(ResourceID3);
	ResourceStorage_ComboBox_Type[0]->SetSelection(ResourceID4);
	ResourceStorage_ComboBox_Type[1]->SetSelection(ResourceID5);
	ResourceStorage_ComboBox_Type[2]->SetSelection(ResourceID6);
	UnitCommands_ComboBox_ResourceIn->SetSelection(ResourceID7);
	UnitCommands_ComboBox_ResourceOut->SetSelection(ResourceID8);
	Research_ComboBox_Resources[0]->SetSelection(ResourceID9);
	Research_ComboBox_Resources[1]->SetSelection(ResourceID10);
	Research_ComboBox_Resources[2]->SetSelection(ResourceID11);
	Effects_ComboBox_ResourcesA->SetSelection(ResourceID12);
	Effects_ComboBox_ResourcesB->SetSelection(ResourceID13);
	
	wxCommandEvent E;
	OnResourcesSelect(E);
}

void AGE_Frame::OnResourcesSearch(wxCommandEvent& Event)
{
	ListResources(CivID);
}

void AGE_Frame::OnResourcesSelect(wxCommandEvent& Event)
{
	short Selection = Civs_Resources_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Civs_Resources_List->GetCount() - 1;
			Civs_Resources_List->SetSelection(Selection);
		}
		float * CivResourcePointer = (float*)Civs_Resources_List->GetClientData(Selection);
		ResourceID = CivResourcePointer - (&GenieFile->Civs[CivID].Resources[0]);
		Civs_ResourceValue->ChangeValue(lexical_cast<string>(*CivResourcePointer));
		Civs_ResourceValue->Container = CivResourcePointer;
		Added = false;
	}
}

void AGE_Frame::OnResourcesAdd(wxCommandEvent& Event)
{
	float Temp = 0;
	short Selection = Civs_Civs_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->Civs[CivID].Resources.push_back(Temp);
		Added = true;
		ListResources(CivID);
	}
}

void AGE_Frame::OnResourcesDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Civs_Resources_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->Civs[CivID].Resources.erase(GenieFile->Civs[CivID].Resources.begin() + ResourceID);
		if(Selection == Civs_Resources_List->GetCount() - 1)
		Civs_Resources_List->SetSelection(Selection - 1);
		ListResources(CivID);
	}
}

void AGE_Frame::OnResourcesCopy(wxCommandEvent& Event)
{
	short Selection = Civs_Resources_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		ResourceCopy = *(float*)Civs_Resources_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnResourcesPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Civs_Resources_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(float*)Civs_Resources_List->GetClientData(Selection) = ResourceCopy;
		ListResources(CivID);
	}
}

void AGE_Frame::CreateCivControls()
{

	Civs_Main = new wxBoxSizer(wxHORIZONTAL);
	Civs_ListArea = new wxBoxSizer(wxVERTICAL);
	Civs_Civs_Buttons = new wxGridSizer(2, 0, 0);
	Tab_Civs = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(-1, 350));

	Civs_Civs = new wxStaticBoxSizer(wxVERTICAL, Tab_Civs, "Civilization slot");
	Civs_Civs_Search = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Civs_Search_R = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Civs_List = new wxListBox(Tab_Civs, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	Civs_Add = new wxButton(Tab_Civs, wxID_ANY, "Add", wxDefaultPosition, wxSize(-1, 20));
	Civs_Delete = new wxButton(Tab_Civs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(-1, 20));
	Civs_Copy = new wxButton(Tab_Civs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Civs_Paste = new wxButton(Tab_Civs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));

	Civs_DataArea = new wxBoxSizer(wxVERTICAL);
	Civs_DataGrid1 = new wxGridSizer(2, 0, 5);
	Civs_DataGrid2 = new wxGridSizer(2, 0, 5);
	Civs_DataGrid3 = new wxGridSizer(2, 0, 0);
	Civs_Holder_One = new wxBoxSizer(wxVERTICAL);
	Civs_Text_One = new wxStaticText(Tab_Civs, wxID_ANY, " Always One", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_One = new TextCtrl_Byte(Tab_Civs, "0", NULL);
	Civs_Holder_Name[0] = new wxBoxSizer(wxVERTICAL);
	Civs_Text_Name[0] = new wxStaticText(Tab_Civs, wxID_ANY, " Name", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_Name[0] = new TextCtrl_String(Tab_Civs, "0", NULL);
	Civs_Holder_Name[1] = new wxBoxSizer(wxVERTICAL);
	Civs_Text_Name[1] = new wxStaticText(Tab_Civs, wxID_ANY, " Name 2", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_Name[1] = new TextCtrl_String(Tab_Civs, "0", NULL);
	Civs_Holder_TechTree = new wxBoxSizer(wxVERTICAL);
	Civs_Text_TechTree = new wxStaticText(Tab_Civs, wxID_ANY, " Technology Tree", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_TechTree = new TextCtrl_Short(Tab_Civs, "0", NULL);
	Civs_Holder_SUnknown1 = new wxBoxSizer(wxVERTICAL);
	Civs_Text_SUnknown1 = new wxStaticText(Tab_Civs, wxID_ANY, " Unknown 1", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 4;loop++)
	Civs_SUnknown1[loop] = new TextCtrl_Short(Tab_Civs, "0", NULL);
	Civs_ComboBox_TechTree = new ComboBox_Short(Tab_Civs, Civs_TechTree);
	Civs_Holder_TeamBonus = new wxBoxSizer(wxVERTICAL);
	Civs_Text_TeamBonus = new wxStaticText(Tab_Civs, wxID_ANY, " Team Bonus", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_TeamBonus = new TextCtrl_Short(Tab_Civs, "0", NULL);
	Civs_ComboBox_TeamBonus = new ComboBox_Short(Tab_Civs, Civs_TeamBonus);
	Civs_Holder_GraphicSet = new wxBoxSizer(wxVERTICAL);
	Civs_Text_GraphicSet = new wxStaticText(Tab_Civs, wxID_ANY, " Graphic Set", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_GraphicSet = new TextCtrl_Byte(Tab_Civs, "0", NULL);
	
	Civs_Holder_Resources = new wxBoxSizer(wxVERTICAL);
	Civs_Resources = new wxStaticBoxSizer(wxVERTICAL, Tab_Civs, "Initial Resources slot");
	Civs_Resources_Search = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Resources_Search_R = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Resources_List = new wxListBox(Tab_Civs, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	Civs_Resources_Buttons = new wxGridSizer(2, 0, 0);
	Resources_Add = new wxButton(Tab_Civs, wxID_ANY, "Add", wxDefaultPosition, wxSize(-1, 20));
	Resources_Delete = new wxButton(Tab_Civs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(-1, 20));
	Resources_Copy = new wxButton(Tab_Civs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	Resources_Paste = new wxButton(Tab_Civs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));
	Civs_Resources_Data = new wxBoxSizer(wxVERTICAL);
	Civs_Holder_ResourceValue = new wxBoxSizer(wxVERTICAL);
	Civs_Text_ResourceValue = new wxStaticText(Tab_Civs, wxID_ANY, " Resource Value", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_ResourceValue = new TextCtrl_Float(Tab_Civs, "0", NULL);
	Civs_Holder_Resources_Link = new wxHyperlinkCtrl(Tab_Civs, wxID_ANY, "GenieWiki Resource List", "http://www.digitization.org/wiki/index.php?title=Resource");

	Civs_Civs_Buttons->Add(Civs_Add, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Delete, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Copy, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Paste, 1, wxEXPAND);

	Civs_Civs->Add(Civs_Civs_Search, 0, wxEXPAND);
	Civs_Civs->Add(Civs_Civs_Search_R, 0, wxEXPAND);
	Civs_Civs->Add(-1, 2);
	Civs_Civs->Add(Civs_Civs_List, 1, wxEXPAND);
	Civs_Civs->Add(-1, 2);
	Civs_Civs->Add(Civs_Civs_Buttons, 0, wxEXPAND);

	Civs_ListArea->Add(-1, 10);
	Civs_ListArea->Add(Civs_Civs, 1, wxEXPAND);
	Civs_ListArea->Add(-1, 10);

	Civs_Holder_One->Add(Civs_Text_One, 0, wxEXPAND);
	Civs_Holder_One->Add(-1, 2);
	Civs_Holder_One->Add(Civs_One, 1, wxEXPAND);
	for(short loop = 0;loop < 2;loop++){
	Civs_Holder_Name[loop]->Add(Civs_Text_Name[loop], 0, wxEXPAND);
	Civs_Holder_Name[loop]->Add(-1, 2);
	Civs_Holder_Name[loop]->Add(Civs_Name[loop], 1, wxEXPAND);}
	Civs_Holder_SUnknown1->Add(Civs_Text_SUnknown1, 0, wxEXPAND);
	Civs_Holder_SUnknown1->Add(-1, 2);
	Civs_Holder_SUnknown1->Add(Civs_DataGrid3, 1, wxEXPAND);
	for(short loop = 0;loop < 4;loop++)
	Civs_DataGrid3->Add(Civs_SUnknown1[loop], 1, wxEXPAND);
	Civs_Holder_TechTree->Add(Civs_Text_TechTree, 0, wxEXPAND);
	Civs_Holder_TechTree->Add(-1, 2);
	Civs_Holder_TechTree->Add(Civs_TechTree, 1, wxEXPAND);
	Civs_Holder_TechTree->Add(Civs_ComboBox_TechTree, 1, wxEXPAND);
	Civs_Holder_TeamBonus->Add(Civs_Text_TeamBonus, 0, wxEXPAND);
	Civs_Holder_TeamBonus->Add(-1, 2);
	Civs_Holder_TeamBonus->Add(Civs_TeamBonus, 1, wxEXPAND);
	Civs_Holder_TeamBonus->Add(Civs_ComboBox_TeamBonus, 1, wxEXPAND);
	Civs_Holder_GraphicSet->Add(Civs_Text_GraphicSet, 0, wxEXPAND);
	Civs_Holder_GraphicSet->Add(-1, 2);
	Civs_Holder_GraphicSet->Add(Civs_GraphicSet, 1, wxEXPAND);

	Civs_DataGrid1->Add(Civs_Holder_GraphicSet, 1, wxEXPAND);
	Civs_DataGrid1->Add(Civs_Holder_One, 1, wxEXPAND);
	Civs_DataGrid2->Add(Civs_Holder_TechTree, 1, wxEXPAND);
	Civs_DataGrid2->Add(Civs_Holder_TeamBonus, 1, wxEXPAND);
	
	Civs_DataArea->Add(-1, 10);
	Civs_DataArea->Add(Civs_Holder_Name[0], 0, wxEXPAND);
	Civs_DataArea->Add(Civs_Holder_Name[1], 0, wxEXPAND);
	Civs_DataArea->Add(-1, 5);
	Civs_DataArea->Add(Civs_DataGrid1, 0, wxEXPAND);
	Civs_DataArea->Add(-1, 5);
	Civs_DataArea->Add(Civs_DataGrid2, 0, wxEXPAND);
	Civs_DataArea->Add(-1, 5);
	Civs_DataArea->Add(Civs_Holder_SUnknown1, 0, wxEXPAND);

	Civs_Resources_Buttons->Add(Resources_Add, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_Delete, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_Copy, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_Paste, 1, wxEXPAND);

	Civs_Holder_ResourceValue->Add(Civs_Text_ResourceValue, 0, wxEXPAND);
	Civs_Holder_ResourceValue->Add(-1, 2);
	Civs_Holder_ResourceValue->Add(Civs_ResourceValue, 1, wxEXPAND);

	Civs_Resources_Data->Add(Civs_Holder_ResourceValue, 0, wxEXPAND);

	Civs_Resources->Add(Civs_Resources_Search, 0, wxEXPAND);
	Civs_Resources->Add(Civs_Resources_Search_R, 0, wxEXPAND);
	Civs_Resources->Add(Civs_Resources_Data, 0, wxEXPAND);
	Civs_Resources->Add(Civs_Resources_List, 1, wxEXPAND);
	Civs_Resources->Add(Civs_Resources_Buttons, 0, wxEXPAND);
	Civs_Resources->Add(Civs_Holder_Resources_Link, 0, wxEXPAND);

	Civs_Holder_Resources->Add(-1, 10);
	Civs_Holder_Resources->Add(Civs_Resources, 1, wxEXPAND);
	Civs_Holder_Resources->Add(-1, 10);

	Civs_Main->Add(10, -1);
	Civs_Main->Add(Civs_ListArea, 2, wxEXPAND);
	Civs_Main->Add(10, -1);
	Civs_Main->Add(Civs_DataArea, 3, wxEXPAND);
	Civs_Main->Add(10, -1);
	Civs_Main->Add(Civs_Holder_Resources, 3, wxEXPAND);
	Civs_Main->Add(10, -1);

	Tab_Civs->SetSizer(Civs_Main);
	
	Connect(Civs_Civs_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnCivsSearch));
	Connect(Civs_Civs_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnCivsSearch));
	Connect(Civs_Civs_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnCivsSelect));
	Connect(Civs_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsAdd));
	Connect(Civs_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsDelete));
	Connect(Civs_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsCopy));
	Connect(Civs_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsPaste));
	Connect(Civs_Resources_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResourcesSearch));
	Connect(Civs_Resources_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResourcesSearch));
	Connect(Civs_Resources_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnResourcesSelect));
	Connect(Resources_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesCopy));
	Connect(Resources_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesPaste));
	Connect(Resources_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesAdd));
	Connect(Resources_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesDelete));
	
	for(short loop = 0;loop < 2;loop++)
	Civs_Name[loop]->Connect(Civs_Name[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Civs_GraphicSet->Connect(Civs_GraphicSet->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Byte), NULL, this);
	Civs_ResourceValue->Connect(Civs_ResourceValue->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Float), NULL, this);

}
