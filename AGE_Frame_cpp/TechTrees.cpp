/* AGEFrame_cpp/TechTrees.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetTTAgesName(short Index)
{
	string Name = "";
	Name = "Age "+lexical_cast<string>(GenieFile->TechTree.TechTreeAges[Index].ID);
	return Name;
}

void AGE_Frame::OnTTAgesSearch(wxCommandEvent& Event)
{
	ListTTAgess();
}

void AGE_Frame::ListTTAgess()
{
	string Name;
	SearchText = wxString(TechTrees_MainList_Ages_Search->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_MainList_Ages_Search_R->GetValue()).Lower();
	string CompareText;
	
	short Selection = TechTrees_MainList_Ages_List->GetSelection();
	if(TechTrees_MainList_Ages_List->GetCount() > 0)
	{
		TechTrees_MainList_Ages_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	
	for(short loop = 0;loop < GenieFile->TechTree.TechTreeAges.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTAgesName(loop);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_MainList_Ages_List->Append(Name, (void*)&GenieFile->TechTree.TechTreeAges[loop]);
		}
	}
	
	TechTrees_MainList_Ages_List->SetSelection(0);
	TechTrees_MainList_Ages_List->SetFirstItem(Selection - 3);
	TechTrees_MainList_Ages_List->SetSelection(Selection);
	
	wxCommandEvent E;
	OnTTAgesSelect(E);
}

void AGE_Frame::OnTTAgesSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Ages_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_MainList_Ages_List->GetCount() - 1;
			TechTrees_MainList_Ages_List->SetSelection(Selection);
		}
		gdat::TechTreeAge * AgePointer = (gdat::TechTreeAge*)TechTrees_MainList_Ages_List->GetClientData(Selection);
		TTAgeID = AgePointer - (&GenieFile->TechTree.TechTreeAges[0]);
		TechTrees_Ages_Unknown1->ChangeValue(lexical_cast<string>(AgePointer->Unknown1));
		TechTrees_Ages_Unknown1->Container = &AgePointer->Unknown1;
		TechTrees_Ages_ID->ChangeValue(lexical_cast<string>(AgePointer->ID));
		TechTrees_Ages_ID->Container = &AgePointer->ID;
		TechTrees_Ages_Unknown2->ChangeValue(lexical_cast<string>((short)AgePointer->Unknown2));
		TechTrees_Ages_Unknown2->Container = &AgePointer->Unknown2;
		TechTrees_Ages_Unknown3->ChangeValue(lexical_cast<string>(AgePointer->Unknown3));
		TechTrees_Ages_Unknown3->Container = &AgePointer->Unknown3;
		TechTrees_Ages_Unknown4->ChangeValue(lexical_cast<string>(AgePointer->Unknown4));
		TechTrees_Ages_Unknown4->Container = &AgePointer->Unknown4;
		for(short loop = 0;loop < 49;loop++)
		{
			TechTrees_Ages_Zeroes1[loop]->ChangeValue(lexical_cast<string>(AgePointer->Zeroes[loop]));
			TechTrees_Ages_Zeroes1[loop]->Container = &AgePointer->Zeroes[loop];
		}
		if(GameVersion >= 4)
		for(short loop = 49;loop < 99;loop++)
		{
			TechTrees_Ages_Zeroes2[loop-49]->ChangeValue(lexical_cast<string>(AgePointer->Zeroes[loop]));
			TechTrees_Ages_Zeroes2[loop-49]->Container = &AgePointer->Zeroes[loop];
		}

		Added = false;
		ListTTAgesBuildings(TTAgeID);
		ListTTAgesUnits(TTAgeID);
		ListTTAgesResearches(TTAgeID);
	}
}

void AGE_Frame::OnTTAgesAdd(wxCommandEvent& Event)
{
	gdat::TechTreeAge Temp;
	GenieFile->TechTree.TechTreeAges.push_back(Temp);
	Added = true;
	ListTTAgess();
}

void AGE_Frame::OnTTAgesDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_MainList_Ages_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.TechTreeAges.erase(GenieFile->TechTree.TechTreeAges.begin() + TTAgeID);
		if(Selection == TechTrees_MainList_Ages_List->GetCount() - 1)
		TechTrees_MainList_Ages_List->SetSelection(Selection - 1);
		ListTTAgess();
	}
}

void AGE_Frame::OnTTAgesCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Ages_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTAgeCopy = *(gdat::TechTreeAge*)TechTrees_MainList_Ages_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTAgesPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_MainList_Ages_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::TechTreeAge*)TechTrees_MainList_Ages_List->GetClientData(Selection) = TTAgeCopy;
		ListTTAgess();
	}
}

string AGE_Frame::GetTTAgesBuildingName(short Index, short Upper)
{
	string Name = "";
	Name = lexical_cast<string>(GenieFile->TechTree.TechTreeAges[Upper].Buildings[Index])+" ";
	if(LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.TechTreeAges[Upper].Buildings[Index]].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.TechTreeAges[Upper].Buildings[Index]].LanguageDllName);
	}
	else if(GenieFile->Civs[0].Units[GenieFile->TechTree.TechTreeAges[Upper].Buildings[Index]].Name != "")
	{
		Name += GenieFile->Civs[0].Units[GenieFile->TechTree.TechTreeAges[Upper].Buildings[Index]].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTAgesBuildingSearch(wxCommandEvent& Event)
{
	ListTTAgesBuildings(TTAgeID);
}

void AGE_Frame::ListTTAgesBuildings(short Index)
{
	string Name;
	SearchText = wxString(TechTrees_DataList_Ages_Search_Buildings->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_DataList_Ages_Search_R_Buildings->GetValue()).Lower();
	string CompareText;
	short Selection = TechTrees_DataList_Ages_List_Buildings->GetSelection();

	if(TechTrees_DataList_Ages_List_Buildings->GetCount() > 0)
	{
		TechTrees_DataList_Ages_List_Buildings->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->TechTree.TechTreeAges[Index].Buildings.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTAgesBuildingName(loop, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_DataList_Ages_List_Buildings->Append(Name, (void*)&GenieFile->TechTree.TechTreeAges[Index].Buildings[loop]);
		}
	}
	TechTrees_DataList_Ages_List_Buildings->SetSelection(0);
	TechTrees_DataList_Ages_List_Buildings->SetFirstItem(Selection - 3);
	TechTrees_DataList_Ages_List_Buildings->SetSelection(Selection);

	wxCommandEvent E;
	OnTTAgesBuildingSelect(E);
}

void AGE_Frame::OnTTAgesBuildingSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Ages_List_Buildings->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_DataList_Ages_List_Buildings->GetCount() - 1;
			TechTrees_DataList_Ages_List_Buildings->SetSelection(Selection);
		}
		long * BuildingPointer = (long*)TechTrees_DataList_Ages_List_Buildings->GetClientData(Selection);
		TTAgeBuildingID = BuildingPointer - (&GenieFile->TechTree.TechTreeAges[TTAgeID].Buildings[0]);
		TechTrees_Ages_Building->ChangeValue(lexical_cast<string>(*BuildingPointer));
		TechTrees_Ages_Building->Container = BuildingPointer;
		TechTrees_Ages_ComboBox_Building->SetSelection(*BuildingPointer + 1);
		Added = false;
	}
	else
	{
		TechTrees_Ages_Building->ChangeValue("0");
		TechTrees_Ages_ComboBox_Building->SetSelection(0);
	}
}

void AGE_Frame::OnTTAgesBuildingAdd(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Ages_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		long Temp = 0;
		GenieFile->TechTree.TechTreeAges[TTAgeID].Buildings.push_back(Temp);
		Added = true;
		ListTTAgesBuildings(TTAgeID);
	}
}

void AGE_Frame::OnTTAgesBuildingDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Ages_List_Buildings->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.TechTreeAges[TTAgeID].Buildings.erase(GenieFile->TechTree.TechTreeAges[TTAgeID].Buildings.begin() + TTAgeBuildingID);
		if(Selection == TechTrees_DataList_Ages_List_Buildings->GetCount() - 1)
		TechTrees_DataList_Ages_List_Buildings->SetSelection(Selection - 1);
		ListTTAgesBuildings(TTAgeID);
	}
}

void AGE_Frame::OnTTAgesBuildingCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Ages_List_Buildings->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTAgeBuildingCopy = *(long*)TechTrees_DataList_Ages_List_Buildings->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTAgesBuildingPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Ages_List_Buildings->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(long*)TechTrees_DataList_Ages_List_Buildings->GetClientData(Selection) = TTAgeBuildingCopy;
		ListTTAgesBuildings(TTAgeID);
	}
}

string AGE_Frame::GetTTAgesUnitName(short Index, short Upper)
{
	string Name = "";
	Name = lexical_cast<string>(GenieFile->TechTree.TechTreeAges[Upper].Units[Index])+" ";
	if(LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.TechTreeAges[Upper].Units[Index]].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.TechTreeAges[Upper].Units[Index]].LanguageDllName);
	}
	else if(GenieFile->Civs[0].Units[GenieFile->TechTree.TechTreeAges[Upper].Units[Index]].Name != "")
	{
		Name += GenieFile->Civs[0].Units[GenieFile->TechTree.TechTreeAges[Upper].Units[Index]].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTAgesUnitSearch(wxCommandEvent& Event)
{
	ListTTAgesUnits(TTAgeID);
}

void AGE_Frame::ListTTAgesUnits(short Index)
{
	string Name;
	SearchText = wxString(TechTrees_DataList_Ages_Search_Units->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_DataList_Ages_Search_R_Units->GetValue()).Lower();
	string CompareText;
	short Selection = TechTrees_DataList_Ages_List_Units->GetSelection();

	if(TechTrees_DataList_Ages_List_Units->GetCount() > 0)
	{
		TechTrees_DataList_Ages_List_Units->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->TechTree.TechTreeAges[Index].Units.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTAgesUnitName(loop, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_DataList_Ages_List_Units->Append(Name, (void*)&GenieFile->TechTree.TechTreeAges[Index].Units[loop]);
		}
	}
	TechTrees_DataList_Ages_List_Units->SetSelection(0);
	TechTrees_DataList_Ages_List_Units->SetFirstItem(Selection - 3);
	TechTrees_DataList_Ages_List_Units->SetSelection(Selection);

	wxCommandEvent E;
	OnTTAgesUnitSelect(E);
}

void AGE_Frame::OnTTAgesUnitSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Ages_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_DataList_Ages_List_Units->GetCount() - 1;
			TechTrees_DataList_Ages_List_Units->SetSelection(Selection);
		}
		long * UnitPointer = (long*)TechTrees_DataList_Ages_List_Units->GetClientData(Selection);
		TTAgeUnitID = UnitPointer - (&GenieFile->TechTree.TechTreeAges[TTAgeID].Units[0]);
		TechTrees_Ages_Unit->ChangeValue(lexical_cast<string>(*UnitPointer));
		TechTrees_Ages_Unit->Container = UnitPointer;
		TechTrees_Ages_ComboBox_Unit->SetSelection(*UnitPointer + 1);
		Added = false;
	}
	else
	{
		TechTrees_Ages_Unit->ChangeValue("0");
		TechTrees_Ages_ComboBox_Unit->SetSelection(0);
	}
}

void AGE_Frame::OnTTAgesUnitAdd(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Ages_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		long Temp = 0;
		GenieFile->TechTree.TechTreeAges[TTAgeID].Units.push_back(Temp);
		Added = true;
		ListTTAgesUnits(TTAgeID);
	}
}

void AGE_Frame::OnTTAgesUnitDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Ages_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.TechTreeAges[TTAgeID].Units.erase(GenieFile->TechTree.TechTreeAges[TTAgeID].Units.begin() + TTAgeUnitID);
		if(Selection == TechTrees_DataList_Ages_List_Units->GetCount() - 1)
		TechTrees_DataList_Ages_List_Units->SetSelection(Selection - 1);
		ListTTAgesUnits(TTAgeID);
	}
}

void AGE_Frame::OnTTAgesUnitCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Ages_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTAgeUnitCopy = *(long*)TechTrees_DataList_Ages_List_Units->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTAgesUnitPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Ages_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(long*)TechTrees_DataList_Ages_List_Units->GetClientData(Selection) = TTAgeUnitCopy;
		ListTTAgesUnits(TTAgeID);
	}
}

string AGE_Frame::GetTTAgesResearchName(short Index, short Upper)
{
	string Name = "";
	Name = lexical_cast<string>(GenieFile->TechTree.TechTreeAges[TTAgeID].Researches[Index])+" ";
	if(LanguageDllString(GenieFile->Researchs[GenieFile->TechTree.TechTreeAges[TTAgeID].Researches[Index]].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Researchs[GenieFile->TechTree.TechTreeAges[TTAgeID].Researches[Index]].LanguageDllName);
	}
	else if(GenieFile->Researchs[GenieFile->TechTree.TechTreeAges[TTAgeID].Researches[Index]].Name != "")
	{
		Name += GenieFile->Researchs[GenieFile->TechTree.TechTreeAges[TTAgeID].Researches[Index]].Name;
	}
	else
	{
		Name += "New Research";
	}
	return Name;
}

void AGE_Frame::OnTTAgesResearchSearch(wxCommandEvent& Event)
{
	ListTTAgesResearches(TTAgeID);
}

void AGE_Frame::ListTTAgesResearches(short Index)
{
	string Name;
	SearchText = wxString(TechTrees_DataList_Ages_Search_Researches->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_DataList_Ages_Search_R_Researches->GetValue()).Lower();
	string CompareText;
	short Selection = TechTrees_DataList_Ages_List_Researches->GetSelection();

	if(TechTrees_DataList_Ages_List_Researches->GetCount() > 0)
	{
		TechTrees_DataList_Ages_List_Researches->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->TechTree.TechTreeAges[Index].Researches.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTAgesResearchName(loop, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_DataList_Ages_List_Researches->Append(Name, (void*)&GenieFile->TechTree.TechTreeAges[Index].Researches[loop]);
		}
	}
	TechTrees_DataList_Ages_List_Researches->SetSelection(0);
	TechTrees_DataList_Ages_List_Researches->SetFirstItem(Selection - 3);
	TechTrees_DataList_Ages_List_Researches->SetSelection(Selection);

	wxCommandEvent E;
	OnTTAgesResearchSelect(E);
}

void AGE_Frame::OnTTAgesResearchSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Ages_List_Researches->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_DataList_Ages_List_Researches->GetCount() - 1;
			TechTrees_DataList_Ages_List_Researches->SetSelection(Selection);
		}
		long * ResearchPointer = (long*)TechTrees_DataList_Ages_List_Researches->GetClientData(Selection);
		TTAgeResearchID = ResearchPointer - (&GenieFile->TechTree.TechTreeAges[TTAgeID].Researches[0]);
		TechTrees_Ages_Research->ChangeValue(lexical_cast<string>(*ResearchPointer));
		TechTrees_Ages_Research->Container = ResearchPointer;
		TechTrees_Ages_ComboBox_Research->SetSelection(*ResearchPointer + 1);
		Added = false;
	}
	else
	{
		TechTrees_Ages_Research->ChangeValue("0");
		TechTrees_Ages_ComboBox_Research->SetSelection(0);
	}
}

void AGE_Frame::OnTTAgesResearchAdd(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Ages_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		long Temp = 0;
		GenieFile->TechTree.TechTreeAges[TTAgeID].Researches.push_back(Temp);
		Added = true;
		ListTTAgesResearches(TTAgeID);
	}
}

void AGE_Frame::OnTTAgesResearchDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Ages_List_Researches->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.TechTreeAges[TTAgeID].Researches.erase(GenieFile->TechTree.TechTreeAges[TTAgeID].Researches.begin() + TTAgeResearchID);
		if(Selection == TechTrees_DataList_Ages_List_Researches->GetCount() - 1)
		TechTrees_DataList_Ages_List_Researches->SetSelection(Selection - 1);
		ListTTAgesResearches(TTAgeID);
	}
}

void AGE_Frame::OnTTAgesResearchCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Ages_List_Researches->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTAgeResearchCopy = *(long*)TechTrees_DataList_Ages_List_Researches->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTAgesResearchPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Ages_List_Researches->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(long*)TechTrees_DataList_Ages_List_Researches->GetClientData(Selection) = TTAgeResearchCopy;
		ListTTAgesResearches(TTAgeID);
	}
}

string AGE_Frame::GetTTBuildingName(short Index)
{
	string Name = "";
	
	short Selection[2];
	for(short loop = 0;loop < 2;loop++)
	Selection[loop] = TechTrees_MainList_Buildings_SearchFilters[loop]->GetSelection();
	
	if(Selection[0] == 0)	// Normal Name
	{
		// Do nothing!
	}
	else for(short loop = 0;loop < 2;loop++)
	{
		if(Selection[loop] == 1)	// Required Researches
		{
			Name += "R ";
			Name += lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Unknown5);
		}
		else if(Selection[loop] == 2)	// Age
		{
			Name += "A ";
			Name += lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Unknown6);
		}
		else if(Selection[loop] == 3)	// Unit or Research 1
		{
			Name += "UR1 ";
			Name += lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Unknown7);
		}
		else if(Selection[loop] == 4)	// Unit or Research 2
		{
			Name += "UR2 ";
			Name += lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Unknown8);
		}
		else if(Selection[loop] == 5)	// U/R 1 Mode
		{
			Name += "1M ";
			Name += lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Unknown9);
		}
		else if(Selection[loop] == 6)	// U/R 2 Mode
		{
			Name += "2M ";
			Name += lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Unknown10);
		}
		else if(Selection[loop] == 7)	// Connections
		{
			Name += "C ";
			Name += lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Unknown4);
		}
		else if(Selection[loop] == 8)	// Enabling Research
		{
			Name += "E ";
			Name += lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].RequiredResearch);
		}
		Name += ", ";
		if(Selection[loop+1] < 1) break;
	}
	
	Name += lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].ID)+" ";
	if(LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Index].ID].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Index].ID].LanguageDllName);
	}
	else if(GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Index].ID].Name != "")
	{
		Name += GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Index].ID].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTBuildingSearch(wxCommandEvent& Event)
{
	ListTTBuildings();
}

void AGE_Frame::ListTTBuildings()
{
	string Name;
	SearchText = wxString(TechTrees_MainList_Buildings_Search->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_MainList_Buildings_Search_R->GetValue()).Lower();
	string CompareText;
	for(short loop = 0;loop < 2;loop++)
	{
		if(TechTrees_MainList_Buildings_UseAnd[loop]->GetValue() == true)
		UseAnd[loop] = true; else UseAnd[loop] = false;
	}
	
	short Selection = TechTrees_MainList_Buildings_List->GetSelection();
	if(TechTrees_MainList_Buildings_List->GetCount() > 0)
	{
		TechTrees_MainList_Buildings_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	
	for(short loop = 0;loop < GenieFile->TechTree.BuildingConnections.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTBuildingName(loop);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_MainList_Buildings_List->Append(Name, (void*)&GenieFile->TechTree.BuildingConnections[loop]);
		}
	}
	
	TechTrees_MainList_Buildings_List->SetSelection(0);
	TechTrees_MainList_Buildings_List->SetFirstItem(Selection - 3);
	TechTrees_MainList_Buildings_List->SetSelection(Selection);
	
	for(short loop = 0;loop < 2;loop++)
	UseAnd[loop] = false;
	
	wxCommandEvent E;
	OnTTBuildingSelect(E);
}

void AGE_Frame::OnTTBuildingSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Buildings_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_MainList_Buildings_List->GetCount() - 1;
			TechTrees_MainList_Buildings_List->SetSelection(Selection);
		}
		gdat::BuildingConnection * BuildingConnectionPointer = (gdat::BuildingConnection*)TechTrees_MainList_Buildings_List->GetClientData(Selection);
		TTBuildingConnectionID = BuildingConnectionPointer - (&GenieFile->TechTree.BuildingConnections[0]);
		TechTrees_Buildings_ID->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->ID));
		TechTrees_Buildings_ID->Container = &BuildingConnectionPointer->ID;
		TechTrees_Buildings_ComboBox_ID->SetSelection(BuildingConnectionPointer->ID + 1);
		TechTrees_Buildings_Always2->ChangeValue(lexical_cast<string>((short)BuildingConnectionPointer->Unknown1));
		TechTrees_Buildings_Always2->Container = &BuildingConnectionPointer->Unknown1;
		TechTrees_Buildings_RequiredResearches->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->Unknown5));
		TechTrees_Buildings_RequiredResearches->Container = &BuildingConnectionPointer->Unknown5;
		TechTrees_Buildings_Age->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->Unknown6));
		TechTrees_Buildings_Age->Container = &BuildingConnectionPointer->Unknown6;
		TechTrees_Buildings_UnitOrResearch1->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->Unknown7));
		TechTrees_Buildings_UnitOrResearch1->Container = &BuildingConnectionPointer->Unknown7;
		TechTrees_Buildings_UnitOrResearch2->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->Unknown8));
		TechTrees_Buildings_UnitOrResearch2->Container = &BuildingConnectionPointer->Unknown8;
		if(BuildingConnectionPointer->Unknown9 == 1 || BuildingConnectionPointer->Unknown9 == 2)
		{
			TechTrees_ComboBox_Unit[0]->Show(true);
			TechTrees_ComboBox_Research[0]->Show(false);
			TechTrees_ComboBox_Unit[0]->SetSelection(BuildingConnectionPointer->Unknown7 + 1);
			TechTrees_Buildings_Text_UnitOrResearch1->SetLabel("Unit/Building 1");
		}
		else if(BuildingConnectionPointer->Unknown9 == 3)
		{
			TechTrees_ComboBox_Unit[0]->Show(false);
			TechTrees_ComboBox_Research[0]->Show(true);
			TechTrees_ComboBox_Research[0]->SetSelection(BuildingConnectionPointer->Unknown7 + 1);
			TechTrees_Buildings_Text_UnitOrResearch1->SetLabel("Research 1");
		}
		else
		{
			TechTrees_ComboBox_Unit[0]->Show(false);
			TechTrees_ComboBox_Research[0]->Show(false);
			TechTrees_Buildings_Text_UnitOrResearch1->SetLabel("Select Mode 1");
		}
		if(BuildingConnectionPointer->Unknown10 == 1 || BuildingConnectionPointer->Unknown10 == 2)
		{
			TechTrees_ComboBox_Unit[1]->Show(true);
			TechTrees_ComboBox_Research[1]->Show(false);
			TechTrees_ComboBox_Unit[1]->SetSelection(BuildingConnectionPointer->Unknown8 + 1);
			TechTrees_Buildings_Text_UnitOrResearch2->SetLabel("Unit/Building 2");
		}
		else if(BuildingConnectionPointer->Unknown10 == 3)
		{
			TechTrees_ComboBox_Unit[1]->Show(false);
			TechTrees_ComboBox_Research[1]->Show(true);
			TechTrees_ComboBox_Research[1]->SetSelection(BuildingConnectionPointer->Unknown8 + 1);
			TechTrees_Buildings_Text_UnitOrResearch2->SetLabel("Research 2");
		}
		else
		{
			TechTrees_ComboBox_Unit[1]->Show(false);
			TechTrees_ComboBox_Research[1]->Show(false);
			TechTrees_Buildings_Text_UnitOrResearch2->SetLabel("Select Mode 2");
		}
		for(short loop = 0;loop < 8;loop++)
		{
			TechTrees_Buildings_Unknown2a1[loop]->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->Unknown2a[loop]));
			TechTrees_Buildings_Unknown2a1[loop]->Container = &BuildingConnectionPointer->Unknown2a[loop];
		}
		for(short loop = 0;loop < 7;loop++)
		{
			TechTrees_Buildings_Unknown2b1[loop]->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->Unknown2b[loop]));
			TechTrees_Buildings_Unknown2b1[loop]->Container = &BuildingConnectionPointer->Unknown2b[loop];
		}
		if(GameVersion >= 4)
		{
			for(short loop = 8;loop < 18;loop++)
			{
				TechTrees_Buildings_Unknown2a2[loop-8]->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->Unknown2a[loop]));
				TechTrees_Buildings_Unknown2a2[loop-8]->Container = &BuildingConnectionPointer->Unknown2a[loop];
			}
			for(short loop = 7;loop < 17;loop++)
			{
				TechTrees_Buildings_Unknown2b2[loop-7]->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->Unknown2b[loop]));
				TechTrees_Buildings_Unknown2b2[loop-7]->Container = &BuildingConnectionPointer->Unknown2b[loop];
			}
		}
		TechTrees_Buildings_Mode1->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->Unknown9));
		TechTrees_Buildings_Mode1->Container = &BuildingConnectionPointer->Unknown9;
		TechTrees_ComboBox_Modes[0]->SetSelection(0);
		TechTrees_ComboBox_Modes[0]->SetSelection(BuildingConnectionPointer->Unknown9);
		TechTrees_Buildings_Mode2->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->Unknown10));
		TechTrees_Buildings_Mode2->Container = &BuildingConnectionPointer->Unknown10;
		TechTrees_ComboBox_Modes[1]->SetSelection(0);
		TechTrees_ComboBox_Modes[1]->SetSelection(BuildingConnectionPointer->Unknown10);
		for(short loop = 0;loop < 11;loop++)
		{
			TechTrees_Buildings_Unknown3[loop]->ChangeValue(lexical_cast<string>((short)BuildingConnectionPointer->Unknown3[loop]));
			TechTrees_Buildings_Unknown3[loop]->Container = &BuildingConnectionPointer->Unknown3[loop];
		}
		TechTrees_Buildings_Connections->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->Unknown4));
		TechTrees_Buildings_Connections->Container = &BuildingConnectionPointer->Unknown4;
		TechTrees_Buildings_EnablingResearch->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->RequiredResearch));
		TechTrees_Buildings_EnablingResearch->Container = &BuildingConnectionPointer->RequiredResearch;
		TechTrees_Buildings_ComboBox_EnablingResearch->SetSelection(BuildingConnectionPointer->RequiredResearch + 1);
		
		Added = false;
		ListTTBuildingBuildings(TTBuildingConnectionID);
		ListTTBuildingUnits(TTBuildingConnectionID);
		ListTTBuildingResearches(TTBuildingConnectionID);
		
		TechTrees_Main->Layout();
		TechTrees_Scroller->GetSizer()->FitInside(TechTrees_Scroller);
	}
}

void AGE_Frame::OnTTBuildingAdd(wxCommandEvent& Event)
{
	gdat::BuildingConnection Temp;
	GenieFile->TechTree.BuildingConnections.push_back(Temp);
	Added = true;
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_MainList_Buildings_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.BuildingConnections.erase(GenieFile->TechTree.BuildingConnections.begin() + TTBuildingConnectionID);
		if(Selection == TechTrees_MainList_Buildings_List->GetCount() - 1)
		TechTrees_MainList_Buildings_List->SetSelection(Selection - 1);
		ListTTBuildings();
	}
}

void AGE_Frame::OnTTBuildingCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Buildings_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTBuildingConnectionCopy = *(gdat::BuildingConnection*)TechTrees_MainList_Buildings_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTBuildingPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_MainList_Buildings_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::BuildingConnection*)TechTrees_MainList_Buildings_List->GetClientData(Selection) = TTBuildingConnectionCopy;
		ListTTBuildings();
	}
}

string AGE_Frame::GetTTBuildingBuildingName(short Index, short Upper)
{
	string Name = "";
	Name = lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Upper].Buildings[Index])+" ";
	if(LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Upper].Buildings[Index]].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Upper].Buildings[Index]].LanguageDllName);
	}
	else if(GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Upper].Buildings[Index]].Name != "")
	{
		Name += GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Upper].Buildings[Index]].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTBuildingBuildingSearch(wxCommandEvent& Event)
{
	ListTTBuildingBuildings(TTBuildingConnectionID);
}

void AGE_Frame::ListTTBuildingBuildings(short Index)
{
	string Name;
	SearchText = wxString(TechTrees_DataList_Buildings_Search_Buildings->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_DataList_Buildings_Search_R_Buildings->GetValue()).Lower();
	string CompareText;
	short Selection = TechTrees_DataList_Buildings_List_Buildings->GetSelection();

	if(TechTrees_DataList_Buildings_List_Buildings->GetCount() > 0)
	{
		TechTrees_DataList_Buildings_List_Buildings->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->TechTree.BuildingConnections[Index].Buildings.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTBuildingBuildingName(loop, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_DataList_Buildings_List_Buildings->Append(Name, (void*)&GenieFile->TechTree.BuildingConnections[Index].Buildings[loop]);
		}
	}
	TechTrees_DataList_Buildings_List_Buildings->SetSelection(0);
	TechTrees_DataList_Buildings_List_Buildings->SetFirstItem(Selection - 3);
	TechTrees_DataList_Buildings_List_Buildings->SetSelection(Selection);

	wxCommandEvent E;
	OnTTBuildingBuildingSelect(E);
}

void AGE_Frame::OnTTBuildingBuildingSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Buildings_List_Buildings->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_DataList_Buildings_List_Buildings->GetCount() - 1;
			TechTrees_DataList_Buildings_List_Buildings->SetSelection(Selection);
		}
		long * BuildingPointer = (long*)TechTrees_DataList_Buildings_List_Buildings->GetClientData(Selection);
		TTBuildingBuildingID = BuildingPointer - (&GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Buildings[0]);
		TechTrees_Buildings_Building->ChangeValue(lexical_cast<string>(*BuildingPointer));
		TechTrees_Buildings_Building->Container = BuildingPointer;
		TechTrees_Buildings_ComboBox_Building->SetSelection(*BuildingPointer + 1);
		Added = false;
	}
	else
	{
		TechTrees_Buildings_Building->ChangeValue("0");
		TechTrees_Buildings_ComboBox_Building->SetSelection(0);
	}
}

void AGE_Frame::OnTTBuildingBuildingAdd(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Buildings_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		long Temp = 0;
		GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Buildings.push_back(Temp);
		Added = true;
		ListTTBuildingBuildings(TTBuildingConnectionID);
	}
}

void AGE_Frame::OnTTBuildingBuildingDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Buildings_List_Buildings->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Buildings.erase(GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Buildings.begin() + TTBuildingBuildingID);
		if(Selection == TechTrees_DataList_Buildings_List_Buildings->GetCount() - 1)
		TechTrees_DataList_Buildings_List_Buildings->SetSelection(Selection - 1);
		ListTTBuildingBuildings(TTBuildingConnectionID);
	}
}

void AGE_Frame::OnTTBuildingBuildingCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Buildings_List_Buildings->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTBuildingBuildingCopy = *(long*)TechTrees_DataList_Buildings_List_Buildings->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTBuildingBuildingPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Buildings_List_Buildings->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(long*)TechTrees_DataList_Buildings_List_Buildings->GetClientData(Selection) = TTBuildingBuildingCopy;
		ListTTBuildingBuildings(TTBuildingConnectionID);
	}
}

string AGE_Frame::GetTTBuildingUnitName(short Index, short Upper)
{
	string Name = "";
	Name = lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Upper].Units[Index])+" ";
	if(LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Upper].Units[Index]].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Upper].Units[Index]].LanguageDllName);
	}
	else if(GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Upper].Units[Index]].Name != "")
	{
		Name += GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Upper].Units[Index]].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTBuildingUnitSearch(wxCommandEvent& Event)
{
	ListTTBuildingUnits(TTBuildingConnectionID);
}

void AGE_Frame::ListTTBuildingUnits(short Index)
{
	string Name;
	SearchText = wxString(TechTrees_DataList_Buildings_Search_Units->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_DataList_Buildings_Search_R_Units->GetValue()).Lower();
	string CompareText;
	short Selection = TechTrees_DataList_Buildings_List_Units->GetSelection();

	if(TechTrees_DataList_Buildings_List_Units->GetCount() > 0)
	{
		TechTrees_DataList_Buildings_List_Units->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->TechTree.BuildingConnections[Index].Units.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTBuildingUnitName(loop, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_DataList_Buildings_List_Units->Append(Name, (void*)&GenieFile->TechTree.BuildingConnections[Index].Units[loop]);
		}
	}
	TechTrees_DataList_Buildings_List_Units->SetSelection(0);
	TechTrees_DataList_Buildings_List_Units->SetFirstItem(Selection - 3);
	TechTrees_DataList_Buildings_List_Units->SetSelection(Selection);

	wxCommandEvent E;
	OnTTBuildingUnitSelect(E);
}

void AGE_Frame::OnTTBuildingUnitSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Buildings_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_DataList_Buildings_List_Units->GetCount() - 1;
			TechTrees_DataList_Buildings_List_Units->SetSelection(Selection);
		}
		long * UnitPointer = (long*)TechTrees_DataList_Buildings_List_Units->GetClientData(Selection);
		TTBuildingUnitID = UnitPointer - (&GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Units[0]);
		TechTrees_Buildings_Unit->ChangeValue(lexical_cast<string>(*UnitPointer));
		TechTrees_Buildings_Unit->Container = UnitPointer;
		TechTrees_Buildings_ComboBox_Unit->SetSelection(*UnitPointer + 1);
		Added = false;
	}
	else
	{
		TechTrees_Buildings_Unit->ChangeValue("0");
		TechTrees_Buildings_ComboBox_Unit->SetSelection(0);
	}
}

void AGE_Frame::OnTTBuildingUnitAdd(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Buildings_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		long Temp = 0;
		GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Units.push_back(Temp);
		Added = true;
		ListTTBuildingUnits(TTBuildingConnectionID);
	}
}

void AGE_Frame::OnTTBuildingUnitDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Buildings_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Units.erase(GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Units.begin() + TTBuildingUnitID);
		if(Selection == TechTrees_DataList_Buildings_List_Units->GetCount() - 1)
		TechTrees_DataList_Buildings_List_Units->SetSelection(Selection - 1);
		ListTTBuildingUnits(TTBuildingConnectionID);
	}
}

void AGE_Frame::OnTTBuildingUnitCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Buildings_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTBuildingUnitCopy = *(long*)TechTrees_DataList_Buildings_List_Units->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTBuildingUnitPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Buildings_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(long*)TechTrees_DataList_Buildings_List_Units->GetClientData(Selection) = TTBuildingUnitCopy;
		ListTTBuildingUnits(TTBuildingConnectionID);
	}
}

string AGE_Frame::GetTTBuildingResearchName(short Index, short Upper)
{
	string Name = "";
	Name = lexical_cast<string>(GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Researches[Index])+" ";
	if(LanguageDllString(GenieFile->Researchs[GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Researches[Index]].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Researchs[GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Researches[Index]].LanguageDllName);
	}
	else if(GenieFile->Researchs[GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Researches[Index]].Name != "")
	{
		Name += GenieFile->Researchs[GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Researches[Index]].Name;
	}
	else
	{
		Name += "New Research";
	}
	return Name;
}

void AGE_Frame::OnTTBuildingResearchSearch(wxCommandEvent& Event)
{
	ListTTBuildingResearches(TTBuildingConnectionID);
}

void AGE_Frame::ListTTBuildingResearches(short Index)
{
	string Name;
	SearchText = wxString(TechTrees_DataList_Buildings_Search_Researches->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_DataList_Buildings_Search_R_Researches->GetValue()).Lower();
	string CompareText;
	short Selection = TechTrees_DataList_Buildings_List_Researches->GetSelection();

	if(TechTrees_DataList_Buildings_List_Researches->GetCount() > 0)
	{
		TechTrees_DataList_Buildings_List_Researches->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->TechTree.BuildingConnections[Index].Researches.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTBuildingResearchName(loop, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_DataList_Buildings_List_Researches->Append(Name, (void*)&GenieFile->TechTree.BuildingConnections[Index].Researches[loop]);
		}
	}
	TechTrees_DataList_Buildings_List_Researches->SetSelection(0);
	TechTrees_DataList_Buildings_List_Researches->SetFirstItem(Selection - 3);
	TechTrees_DataList_Buildings_List_Researches->SetSelection(Selection);

	wxCommandEvent E;
	OnTTBuildingResearchSelect(E);
}

void AGE_Frame::OnTTBuildingResearchSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Buildings_List_Researches->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_DataList_Buildings_List_Researches->GetCount() - 1;
			TechTrees_DataList_Buildings_List_Researches->SetSelection(Selection);
		}
		long * ResearchPointer = (long*)TechTrees_DataList_Buildings_List_Researches->GetClientData(Selection);
		TTBuildingResearchID = ResearchPointer - (&GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Researches[0]);
		TechTrees_Buildings_Research->ChangeValue(lexical_cast<string>(*ResearchPointer));
		TechTrees_Buildings_Research->Container = ResearchPointer;
		TechTrees_Buildings_ComboBox_Research->SetSelection(*ResearchPointer + 1);
		Added = false;
	}
	else
	{
		TechTrees_Buildings_Research->ChangeValue("0");
		TechTrees_Buildings_ComboBox_Research->SetSelection(0);
	}
}

void AGE_Frame::OnTTBuildingResearchAdd(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Buildings_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		long Temp = 0;
		GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Researches.push_back(Temp);
		Added = true;
		ListTTBuildingResearches(TTBuildingConnectionID);
	}
}

void AGE_Frame::OnTTBuildingResearchDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Buildings_List_Researches->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Researches.erase(GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Researches.begin() + TTBuildingResearchID);
		if(Selection == TechTrees_DataList_Buildings_List_Researches->GetCount() - 1)
		TechTrees_DataList_Buildings_List_Researches->SetSelection(Selection - 1);
		ListTTBuildingResearches(TTBuildingConnectionID);
	}
}

void AGE_Frame::OnTTBuildingResearchCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Buildings_List_Researches->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTBuildingResearchCopy = *(long*)TechTrees_DataList_Buildings_List_Researches->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTBuildingResearchPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Buildings_List_Researches->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(long*)TechTrees_DataList_Buildings_List_Researches->GetClientData(Selection) = TTBuildingResearchCopy;
		ListTTBuildingResearches(TTBuildingConnectionID);
	}
}

string AGE_Frame::GetTTUnitName(short Index)
{
	string Name = "";
	
	short Selection[2];
	for(short loop = 0;loop < 2;loop++)
	Selection[loop] = TechTrees_MainList_Units_SearchFilters[loop]->GetSelection();
	
	if(Selection[0] == 0)	// Normal Name
	{
		// Do nothing!
	}
	else for(short loop = 0;loop < 2;loop++)
	{
		if(Selection[loop] == 1)	// Upper Building
		{
			Name += "U ";
			Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].UpperBuilding);
		}
		else if(Selection[loop] == 2)	// Required Researches
		{
			Name += "C ";
			Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Unknown6);
		}
		else if(Selection[loop] == 3)	// Age
		{
			Name += "A ";
			Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Unknown7);
		}
		else if(Selection[loop] == 4)	// Unit or Research 1
		{
			Name += "UR1 ";
			Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Unknown8);
		}
		else if(Selection[loop] == 5)	// Unit or Research 2
		{
			Name += "UR2 ";
			Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Unknown9);
		}
		else if(Selection[loop] == 6)	// U/R 1 Mode
		{
			Name += "1M ";
			Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Unknown10);
		}
		else if(Selection[loop] == 7)	// U/R 2 Mode
		{
			Name += "2M ";
			Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Unknown11);
		}
		else if(Selection[loop] == 8)	// Vertical Line Number
		{
			Name += "V ";
			Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Unknown12);
		}
		else if(Selection[loop] == 9)	// Space Sharing
		{
			Name += "S ";
			Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Unknown3);
		}
		else if(Selection[loop] == 10)	// Required Research
		{
			Name += "R ";
			Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Unknown4);
		}
		else if(Selection[loop] == 11)	// Placement
		{
			Name += "P ";
			Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Unknown5);
		}
		else if(Selection[loop] == 12)	// Enabling Research
		{
			Name += "E ";
			Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].RequiredResearch);
		}
		Name += ", ";
		if(Selection[loop+1] < 1) break;
	}
	
	Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].ID)+" ";
	if(LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.UnitConnections[Index].ID].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.UnitConnections[Index].ID].LanguageDllName);
	}
	else if(GenieFile->Civs[0].Units[GenieFile->TechTree.UnitConnections[Index].ID].Name != "")
	{
		Name += GenieFile->Civs[0].Units[GenieFile->TechTree.UnitConnections[Index].ID].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTUnitSearch(wxCommandEvent& Event)
{
	ListTTUnits();
}

void AGE_Frame::ListTTUnits()
{
	string Name;
	SearchText = wxString(TechTrees_MainList_Units_Search->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_MainList_Units_Search_R->GetValue()).Lower();
	string CompareText;
	for(short loop = 0;loop < 2;loop++)
	{
		if(TechTrees_MainList_Units_UseAnd[loop]->GetValue() == true)
		UseAnd[loop] = true; else UseAnd[loop] = false;
	}
	
	short Selection = TechTrees_MainList_Units_List->GetSelection();
	if(TechTrees_MainList_Units_List->GetCount() > 0)
	{
		TechTrees_MainList_Units_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	
	for(short loop = 0;loop < GenieFile->TechTree.UnitConnections.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTUnitName(loop);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_MainList_Units_List->Append(Name, (void*)&GenieFile->TechTree.UnitConnections[loop]);
		}
	}
	
	TechTrees_MainList_Units_List->SetSelection(0);
	TechTrees_MainList_Units_List->SetFirstItem(Selection - 3);
	TechTrees_MainList_Units_List->SetSelection(Selection);
	
	for(short loop = 0;loop < 2;loop++)
	UseAnd[loop] = false;
	
	wxCommandEvent E;
	OnTTUnitSelect(E);
}

void AGE_Frame::OnTTUnitSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_MainList_Units_List->GetCount() - 1;
			TechTrees_MainList_Units_List->SetSelection(Selection);
		}
		gdat::UnitConnection * UnitConnectionPointer = (gdat::UnitConnection*)TechTrees_MainList_Units_List->GetClientData(Selection);
		TTUnitConnectionID = UnitConnectionPointer - (&GenieFile->TechTree.UnitConnections[0]);
		TechTrees_Units_ID->ChangeValue(lexical_cast<string>(UnitConnectionPointer->ID));
		TechTrees_Units_ID->Container = &UnitConnectionPointer->ID;
		TechTrees_Units_ComboBox_ID->SetSelection(UnitConnectionPointer->ID + 1);
		TechTrees_Units_Always2->ChangeValue(lexical_cast<string>((short)UnitConnectionPointer->Unknown1));
		TechTrees_Units_Always2->Container = &UnitConnectionPointer->Unknown1;
		TechTrees_Units_UpperBuilding->ChangeValue(lexical_cast<string>(UnitConnectionPointer->UpperBuilding));
		TechTrees_Units_UpperBuilding->Container = &UnitConnectionPointer->UpperBuilding;
		TechTrees_Units_ComboBox_UpperBuilding->SetSelection(UnitConnectionPointer->UpperBuilding + 1);
		TechTrees_Units_RequiredResearches->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown6));
		TechTrees_Units_RequiredResearches->Container = &UnitConnectionPointer->Unknown6;
		TechTrees_Units_Age->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown7));
		TechTrees_Units_Age->Container = &UnitConnectionPointer->Unknown7;
		TechTrees_Units_UnitOrResearch1->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown8));
		TechTrees_Units_UnitOrResearch1->Container = &UnitConnectionPointer->Unknown8;
		TechTrees_Units_UnitOrResearch2->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown9));
		TechTrees_Units_UnitOrResearch2->Container = &UnitConnectionPointer->Unknown9;
		if(UnitConnectionPointer->Unknown10 == 1 || UnitConnectionPointer->Unknown10 == 2)
		{
			TechTrees_ComboBox_Unit[2]->Show(true);
			TechTrees_ComboBox_Research[2]->Show(false);
			TechTrees_ComboBox_Unit[2]->SetSelection(UnitConnectionPointer->Unknown8 + 1);
			TechTrees_Units_Text_UnitOrResearch1->SetLabel("Unit/Building 1");
		}
		else if(UnitConnectionPointer->Unknown10 == 3)
		{
			TechTrees_ComboBox_Unit[2]->Show(false);
			TechTrees_ComboBox_Research[2]->Show(true);
			TechTrees_ComboBox_Research[2]->SetSelection(UnitConnectionPointer->Unknown8 + 1);
			TechTrees_Units_Text_UnitOrResearch1->SetLabel("Research 1");
		}
		else
		{
			TechTrees_ComboBox_Unit[2]->Show(false);
			TechTrees_ComboBox_Research[2]->Show(false);
			TechTrees_Units_Text_UnitOrResearch1->SetLabel("Select Mode 1");
		}
		if(UnitConnectionPointer->Unknown11 == 1 || UnitConnectionPointer->Unknown11 == 2)
		{
			TechTrees_ComboBox_Unit[3]->Show(true);
			TechTrees_ComboBox_Research[3]->Show(false);
			TechTrees_ComboBox_Unit[3]->SetSelection(UnitConnectionPointer->Unknown9 + 1);
			TechTrees_Units_Text_UnitOrResearch2->SetLabel("Unit/Building 2");
		}
		else if(UnitConnectionPointer->Unknown11 == 3)
		{
			TechTrees_ComboBox_Unit[3]->Show(false);
			TechTrees_ComboBox_Research[3]->Show(true);
			TechTrees_ComboBox_Research[3]->SetSelection(UnitConnectionPointer->Unknown9 + 1);
			TechTrees_Units_Text_UnitOrResearch2->SetLabel("Research 2");
		}
		else
		{
			TechTrees_ComboBox_Unit[3]->Show(false);
			TechTrees_ComboBox_Research[3]->Show(false);
			TechTrees_Units_Text_UnitOrResearch2->SetLabel("Select Mode 2");
		}
		TechTrees_Units_Mode1->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown10));
		TechTrees_Units_Mode1->Container = &UnitConnectionPointer->Unknown10;
		TechTrees_ComboBox_Modes[2]->SetSelection(0);
		TechTrees_ComboBox_Modes[2]->SetSelection(UnitConnectionPointer->Unknown10);
		TechTrees_Units_Mode2->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown11));
		TechTrees_Units_Mode2->Container = &UnitConnectionPointer->Unknown11;
		TechTrees_ComboBox_Modes[3]->SetSelection(0);
		TechTrees_ComboBox_Modes[3]->SetSelection(UnitConnectionPointer->Unknown11);
		for(short loop = 0;loop < 8;loop++)
		{
			TechTrees_Units_Unknown2a1[loop]->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown2a[loop]));
			TechTrees_Units_Unknown2a1[loop]->Container = &UnitConnectionPointer->Unknown2a[loop];
		}
		for(short loop = 0;loop < 7;loop++)
		{
			TechTrees_Units_Unknown2b1[loop]->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown2b[loop]));
			TechTrees_Units_Unknown2b1[loop]->Container = &UnitConnectionPointer->Unknown2b[loop];
		}
		if(GameVersion >= 4)
		{
			for(short loop = 8;loop < 18;loop++)
			{
				TechTrees_Units_Unknown2a2[loop-8]->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown2a[loop]));
				TechTrees_Units_Unknown2a2[loop-8]->Container = &UnitConnectionPointer->Unknown2a[loop];
			}
			for(short loop = 7;loop < 17;loop++)
			{
				TechTrees_Units_Unknown2b2[loop-7]->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown2b[loop]));
				TechTrees_Units_Unknown2b2[loop-7]->Container = &UnitConnectionPointer->Unknown2b[loop];
			}
		}
		TechTrees_Units_VerticalLine->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown12));
		TechTrees_Units_VerticalLine->Container = &UnitConnectionPointer->Unknown12;
		TechTrees_Units_Unknown3->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown3));
		TechTrees_Units_Unknown3->Container = &UnitConnectionPointer->Unknown3;
		TechTrees_Units_RequiredResearch->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown4));
		TechTrees_Units_RequiredResearch->Container = &UnitConnectionPointer->Unknown4;
		TechTrees_Units_ComboBox_RequiredResearch->SetSelection(UnitConnectionPointer->Unknown4 + 1);
		TechTrees_Units_LineMode->ChangeValue(lexical_cast<string>(UnitConnectionPointer->Unknown5));
		TechTrees_Units_LineMode->Container = &UnitConnectionPointer->Unknown5;
		TechTrees_Units_EnablingResearch->ChangeValue(lexical_cast<string>(UnitConnectionPointer->RequiredResearch));
		TechTrees_Units_EnablingResearch->Container = &UnitConnectionPointer->RequiredResearch;
		TechTrees_Units_ComboBox_EnablingResearch->SetSelection(UnitConnectionPointer->RequiredResearch + 1);
		
		Added = false;
		ListTTUnitUnits(TTUnitConnectionID);
		
		TechTrees_Main->Layout();
		TechTrees_Scroller->GetSizer()->FitInside(TechTrees_Scroller);
	}
}

void AGE_Frame::OnTTUnitAdd(wxCommandEvent& Event)
{
	gdat::UnitConnection Temp;
	GenieFile->TechTree.UnitConnections.push_back(Temp);
	Added = true;
	ListTTUnits();
}

void AGE_Frame::OnTTUnitDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_MainList_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.UnitConnections.erase(GenieFile->TechTree.UnitConnections.begin() + TTUnitConnectionID);
		if(Selection == TechTrees_MainList_Units_List->GetCount() - 1)
		TechTrees_MainList_Units_List->SetSelection(Selection - 1);
		ListTTUnits();
	}
}

void AGE_Frame::OnTTUnitCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTUnitConnectionCopy = *(gdat::UnitConnection*)TechTrees_MainList_Units_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTUnitPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_MainList_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::UnitConnection*)TechTrees_MainList_Units_List->GetClientData(Selection) = TTUnitConnectionCopy;
		ListTTUnits();
	}
}

string AGE_Frame::GetTTUnitUnitName(short Index, short Upper)
{
	string Name = "";
	Name = lexical_cast<string>(GenieFile->TechTree.UnitConnections[Upper].Units[Index])+" ";
	if(LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.UnitConnections[Upper].Units[Index]].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.UnitConnections[Upper].Units[Index]].LanguageDllName);
	}
	else if(GenieFile->Civs[0].Units[GenieFile->TechTree.UnitConnections[Upper].Units[Index]].Name != "")
	{
		Name += GenieFile->Civs[0].Units[GenieFile->TechTree.UnitConnections[Upper].Units[Index]].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTUnitUnitSearch(wxCommandEvent& Event)
{
	ListTTUnitUnits(TTUnitConnectionID);
}

void AGE_Frame::ListTTUnitUnits(short Index)
{
	string Name;
	SearchText = wxString(TechTrees_DataList_Units_Search_Units->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_DataList_Units_Search_R_Units->GetValue()).Lower();
	string CompareText;
	short Selection = TechTrees_DataList_Units_List_Units->GetSelection();

	if(TechTrees_DataList_Units_List_Units->GetCount() > 0)
	{
		TechTrees_DataList_Units_List_Units->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->TechTree.UnitConnections[Index].Units.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTUnitUnitName(loop, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_DataList_Units_List_Units->Append(Name, (void*)&GenieFile->TechTree.UnitConnections[Index].Units[loop]);
		}
	}
	TechTrees_DataList_Units_List_Units->SetSelection(0);
	TechTrees_DataList_Units_List_Units->SetFirstItem(Selection - 3);
	TechTrees_DataList_Units_List_Units->SetSelection(Selection);

	wxCommandEvent E;
	OnTTUnitUnitSelect(E);
}

void AGE_Frame::OnTTUnitUnitSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Units_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_DataList_Units_List_Units->GetCount() - 1;
			TechTrees_DataList_Units_List_Units->SetSelection(Selection);
		}
		long * UnitPointer = (long*)TechTrees_DataList_Units_List_Units->GetClientData(Selection);
		TTUnitUnitID = UnitPointer - (&GenieFile->TechTree.UnitConnections[TTUnitConnectionID].Units[0]);
		TechTrees_Units_Unit->ChangeValue(lexical_cast<string>(*UnitPointer));
		TechTrees_Units_Unit->Container = UnitPointer;
		TechTrees_Units_ComboBox_Unit->SetSelection(*UnitPointer + 1);
		Added = false;
	}
	else
	{
		TechTrees_Units_Unit->ChangeValue("0");
		TechTrees_Units_ComboBox_Unit->SetSelection(0);
	}
}

void AGE_Frame::OnTTUnitUnitAdd(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		long Temp = 0;
		GenieFile->TechTree.UnitConnections[TTUnitConnectionID].Units.push_back(Temp);
		Added = true;
		ListTTUnitUnits(TTUnitConnectionID);
	}
}

void AGE_Frame::OnTTUnitUnitDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Units_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.UnitConnections[TTUnitConnectionID].Units.erase(GenieFile->TechTree.UnitConnections[TTUnitConnectionID].Units.begin() + TTUnitUnitID);
		if(Selection == TechTrees_DataList_Units_List_Units->GetCount() - 1)
		TechTrees_DataList_Units_List_Units->SetSelection(Selection - 1);
		ListTTUnitUnits(TTUnitConnectionID);
	}
}

void AGE_Frame::OnTTUnitUnitCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Units_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTUnitUnitCopy = *(long*)TechTrees_DataList_Units_List_Units->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTUnitUnitPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Units_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(long*)TechTrees_DataList_Units_List_Units->GetClientData(Selection) = TTUnitUnitCopy;
		ListTTUnitUnits(TTUnitConnectionID);
	}
}

string AGE_Frame::GetTTResearchName(short Index)
{
	string Name = "";
	
	short Selection[2];
	for(short loop = 0;loop < 2;loop++)
	Selection[loop] = TechTrees_MainList_Researches_SearchFilters[loop]->GetSelection();
	
	if(Selection[0] == 0)	// Normal Name
	{
		// Do nothing!
	}
	else for(short loop = 0;loop < 2;loop++)
	{
		if(Selection[loop] == 1)	// Upper Building
		{
			Name += "UB ";
			Name += lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].UpperBuilding);
		}
		else if(Selection[loop] == 2)	// Required Researches
		{
			Name += "RR ";
			Name += lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].Unknown3);
		}
		else if(Selection[loop] == 3)	// Age
		{
			Name += "A ";
			Name += lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].Unknown4);
		}
		else if(Selection[loop] == 4)	// Upper Research
		{
			Name += "UR ";
			Name += lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].UpperResearch);
		}
		else if(Selection[loop] == 5)	// Line Mode
		{
			Name += "LM ";
			Name += lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].Unknown6);
		}
		else if(Selection[loop] == 6)	// Vertical Line Number
		{
			Name += "VL ";
			Name += lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].Unknown7);
		}
		else if(Selection[loop] == 7)	// Location In Age
		{
			Name += "LA ";
			Name += lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].Unknown8);
		}
		else if(Selection[loop] == 8)	// First Age Mode
		{
			Name += "FA ";
			Name += lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].Unknown9);
		}
		Name += ", ";
		if(Selection[loop+1] < 1) break;
	}
	
	Name += lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].ID)+" ";
	if(LanguageDllString(GenieFile->Researchs[GenieFile->TechTree.ResearchConnections[Index].ID].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Researchs[GenieFile->TechTree.ResearchConnections[Index].ID].LanguageDllName);
	}
	else if(GenieFile->Researchs[GenieFile->TechTree.ResearchConnections[Index].ID].Name != "")
	{
		Name += GenieFile->Researchs[GenieFile->TechTree.ResearchConnections[Index].ID].Name;
	}
	else
	{
		Name += "New Research";
	}
	return Name;
}

void AGE_Frame::OnTTResearchSearch(wxCommandEvent& Event)
{
	ListTTResearches();
}

void AGE_Frame::ListTTResearches()
{
	string Name;
	SearchText = wxString(TechTrees_MainList_Researches_Search->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_MainList_Researches_Search_R->GetValue()).Lower();
	string CompareText;
	for(short loop = 0;loop < 2;loop++)
	{
		if(TechTrees_MainList_Researches_UseAnd[loop]->GetValue() == true)
		UseAnd[loop] = true; else UseAnd[loop] = false;
	}
	
	short Selection = TechTrees_MainList_Researches_List->GetSelection();
	if(TechTrees_MainList_Researches_List->GetCount() > 0)
	{
		TechTrees_MainList_Researches_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	
	for(short loop = 0;loop < GenieFile->TechTree.ResearchConnections.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTResearchName(loop);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_MainList_Researches_List->Append(Name, (void*)&GenieFile->TechTree.ResearchConnections[loop]);
		}
	}
	
	TechTrees_MainList_Researches_List->SetSelection(0);
	TechTrees_MainList_Researches_List->SetFirstItem(Selection - 3);
	TechTrees_MainList_Researches_List->SetSelection(Selection);
	
	for(short loop = 0;loop < 2;loop++)
	UseAnd[loop] = false;
	
	wxCommandEvent E;
	OnTTResearchSelect(E);
}

void AGE_Frame::OnTTResearchSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Researches_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_MainList_Researches_List->GetCount() - 1;
			TechTrees_MainList_Researches_List->SetSelection(Selection);
		}
		gdat::ResearchConnection * ResearchConnectionPointer = (gdat::ResearchConnection*)TechTrees_MainList_Researches_List->GetClientData(Selection);
		TTResearchConnectionID = ResearchConnectionPointer - (&GenieFile->TechTree.ResearchConnections[0]);
		TechTrees_Researches_ID->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->ID));
		TechTrees_Researches_ID->Container = &ResearchConnectionPointer->ID;
		TechTrees_Researches_ComboBox_ID->SetSelection(ResearchConnectionPointer->ID + 1);
		TechTrees_Researches_Always2->ChangeValue(lexical_cast<string>((short)ResearchConnectionPointer->Unknown1));
		TechTrees_Researches_Always2->Container = &ResearchConnectionPointer->Unknown1;
		TechTrees_Researches_UpperBuilding->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->UpperBuilding));
		TechTrees_Researches_UpperBuilding->Container = &ResearchConnectionPointer->UpperBuilding;
		TechTrees_Researches_ComboBox_UpperBuilding->SetSelection(ResearchConnectionPointer->UpperBuilding + 1);
		TechTrees_Researches_RequiredResearches->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->Unknown3));
		TechTrees_Researches_RequiredResearches->Container = &ResearchConnectionPointer->Unknown3;
		TechTrees_Researches_Age->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->Unknown4));
		TechTrees_Researches_Age->Container = &ResearchConnectionPointer->Unknown4;
		TechTrees_Researches_UpperResearch->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->UpperResearch));
		TechTrees_Researches_UpperResearch->Container = &ResearchConnectionPointer->UpperResearch;
		TechTrees_Researches_ComboBox_UpperResearch->SetSelection(ResearchConnectionPointer->UpperResearch + 1);
		TechTrees_Researches_LineMode->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->Unknown6));
		TechTrees_Researches_LineMode->Container = &ResearchConnectionPointer->Unknown6;
		for(short loop = 0;loop < 9;loop++)
		{
			TechTrees_Researches_Unknown2a1[loop]->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->Unknown2a[loop]));
			TechTrees_Researches_Unknown2a1[loop]->Container = &ResearchConnectionPointer->Unknown2a[loop];
		}
		for(short loop = 0;loop < 8;loop++)
		{
			TechTrees_Researches_Unknown2b1[loop]->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->Unknown2b[loop]));
			TechTrees_Researches_Unknown2b1[loop]->Container = &ResearchConnectionPointer->Unknown2b[loop];
		}
		if(GameVersion >= 4)
		{
			for(short loop = 9;loop < 19;loop++)
			{
				TechTrees_Researches_Unknown2a2[loop-9]->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->Unknown2a[loop]));
				TechTrees_Researches_Unknown2a2[loop-9]->Container = &ResearchConnectionPointer->Unknown2a[loop];
			}
			for(short loop = 8;loop < 18;loop++)
			{
				TechTrees_Researches_Unknown2b2[loop-8]->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->Unknown2b[loop]));
				TechTrees_Researches_Unknown2b2[loop-8]->Container = &ResearchConnectionPointer->Unknown2b[loop];
			}
		}
		TechTrees_Researches_VerticalLine->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->Unknown7));
		TechTrees_Researches_VerticalLine->Container = &ResearchConnectionPointer->Unknown7;
		TechTrees_Researches_LocationInAge->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->Unknown8));
		TechTrees_Researches_LocationInAge->Container = &ResearchConnectionPointer->Unknown8;
		TechTrees_Researches_Unknown9->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->Unknown9));
		TechTrees_Researches_Unknown9->Container = &ResearchConnectionPointer->Unknown9;
		
		Added = false;
		ListTTResearchBuildings(TTResearchConnectionID);
		ListTTResearchUnits(TTResearchConnectionID);
		ListTTResearchResearches(TTResearchConnectionID);
	}
}

void AGE_Frame::OnTTResearchAdd(wxCommandEvent& Event)
{
	gdat::ResearchConnection Temp;
	GenieFile->TechTree.ResearchConnections.push_back(Temp);
	Added = true;
	ListTTResearches();
}

void AGE_Frame::OnTTResearchDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_MainList_Researches_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.ResearchConnections.erase(GenieFile->TechTree.ResearchConnections.begin() + TTResearchConnectionID);
		if(Selection == TechTrees_MainList_Researches_List->GetCount() - 1)
		TechTrees_MainList_Researches_List->SetSelection(Selection - 1);
		ListTTResearches();
	}
}

void AGE_Frame::OnTTResearchCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Researches_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTResearchConnectionCopy = *(gdat::ResearchConnection*)TechTrees_MainList_Researches_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTResearchPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_MainList_Researches_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::ResearchConnection*)TechTrees_MainList_Researches_List->GetClientData(Selection) = TTResearchConnectionCopy;
		ListTTResearches();
	}
}

string AGE_Frame::GetTTResearchBuildingName(short Index, short Upper)
{
	string Name = "";
	Name = lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Upper].Buildings[Index])+" ";
	if(LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.ResearchConnections[Upper].Buildings[Index]].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.ResearchConnections[Upper].Buildings[Index]].LanguageDllName);
	}
	else if(GenieFile->Civs[0].Units[GenieFile->TechTree.ResearchConnections[Upper].Buildings[Index]].Name != "")
	{
		Name += GenieFile->Civs[0].Units[GenieFile->TechTree.ResearchConnections[Upper].Buildings[Index]].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTResearchBuildingSearch(wxCommandEvent& Event)
{
	ListTTResearchBuildings(TTResearchConnectionID);
}

void AGE_Frame::ListTTResearchBuildings(short Index)
{
	string Name;
	SearchText = wxString(TechTrees_DataList_Researches_Search_Buildings->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_DataList_Researches_Search_R_Buildings->GetValue()).Lower();
	string CompareText;
	short Selection = TechTrees_DataList_Researches_List_Buildings->GetSelection();

	if(TechTrees_DataList_Researches_List_Buildings->GetCount() > 0)
	{
		TechTrees_DataList_Researches_List_Buildings->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->TechTree.ResearchConnections[Index].Buildings.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTResearchBuildingName(loop, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_DataList_Researches_List_Buildings->Append(Name, (void*)&GenieFile->TechTree.ResearchConnections[Index].Buildings[loop]);
		}
	}
	TechTrees_DataList_Researches_List_Buildings->SetSelection(0);
	TechTrees_DataList_Researches_List_Buildings->SetFirstItem(Selection - 3);
	TechTrees_DataList_Researches_List_Buildings->SetSelection(Selection);

	wxCommandEvent E;
	OnTTResearchBuildingSelect(E);
}

void AGE_Frame::OnTTResearchBuildingSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Researches_List_Buildings->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_DataList_Researches_List_Buildings->GetCount() - 1;
			TechTrees_DataList_Researches_List_Buildings->SetSelection(Selection);
		}
		long * BuildingPointer = (long*)TechTrees_DataList_Researches_List_Buildings->GetClientData(Selection);
		TTResearchBuildingID = BuildingPointer - (&GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Buildings[0]);
		TechTrees_Researches_Building->ChangeValue(lexical_cast<string>(*BuildingPointer));
		TechTrees_Researches_Building->Container = BuildingPointer;
		TechTrees_Researches_ComboBox_Building->SetSelection(*BuildingPointer + 1);
		Added = false;
	}
	else
	{
		TechTrees_Researches_Building->ChangeValue("0");
		TechTrees_Researches_ComboBox_Building->SetSelection(0);
	}
}

void AGE_Frame::OnTTResearchBuildingAdd(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Researches_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		long Temp = 0;
		GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Buildings.push_back(Temp);
		Added = true;
		ListTTResearchBuildings(TTResearchConnectionID);
	}
}

void AGE_Frame::OnTTResearchBuildingDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Researches_List_Buildings->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Buildings.erase(GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Buildings.begin() + TTResearchBuildingID);
		if(Selection == TechTrees_DataList_Researches_List_Buildings->GetCount() - 1)
		TechTrees_DataList_Researches_List_Buildings->SetSelection(Selection - 1);
		ListTTResearchBuildings(TTResearchConnectionID);
	}
}

void AGE_Frame::OnTTResearchBuildingCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Researches_List_Buildings->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTResearchBuildingCopy = *(long*)TechTrees_DataList_Researches_List_Buildings->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTResearchBuildingPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Researches_List_Buildings->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(long*)TechTrees_DataList_Researches_List_Buildings->GetClientData(Selection) = TTResearchBuildingCopy;
		ListTTResearchBuildings(TTResearchConnectionID);
	}
}

string AGE_Frame::GetTTResearchUnitName(short Index, short Upper)
{
	string Name = "";
	Name = lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Upper].Units[Index])+" ";
	if(LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.ResearchConnections[Upper].Units[Index]].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Civs[0].Units[GenieFile->TechTree.ResearchConnections[Upper].Units[Index]].LanguageDllName);
	}
	else if(GenieFile->Civs[0].Units[GenieFile->TechTree.ResearchConnections[Upper].Units[Index]].Name != "")
	{
		Name += GenieFile->Civs[0].Units[GenieFile->TechTree.ResearchConnections[Upper].Units[Index]].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTResearchUnitSearch(wxCommandEvent& Event)
{
	ListTTResearchUnits(TTResearchConnectionID);
}

void AGE_Frame::ListTTResearchUnits(short Index)
{
	string Name;
	SearchText = wxString(TechTrees_DataList_Researches_Search_Units->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_DataList_Researches_Search_R_Units->GetValue()).Lower();
	string CompareText;
	short Selection = TechTrees_DataList_Researches_List_Units->GetSelection();

	if(TechTrees_DataList_Researches_List_Units->GetCount() > 0)
	{
		TechTrees_DataList_Researches_List_Units->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->TechTree.ResearchConnections[Index].Units.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTResearchUnitName(loop, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_DataList_Researches_List_Units->Append(Name, (void*)&GenieFile->TechTree.ResearchConnections[Index].Units[loop]);
		}
	}
	TechTrees_DataList_Researches_List_Units->SetSelection(0);
	TechTrees_DataList_Researches_List_Units->SetFirstItem(Selection - 3);
	TechTrees_DataList_Researches_List_Units->SetSelection(Selection);

	wxCommandEvent E;
	OnTTResearchUnitSelect(E);
}

void AGE_Frame::OnTTResearchUnitSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Researches_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_DataList_Researches_List_Units->GetCount() - 1;
			TechTrees_DataList_Researches_List_Units->SetSelection(Selection);
		}
		long * UnitPointer = (long*)TechTrees_DataList_Researches_List_Units->GetClientData(Selection);
		TTResearchUnitID = UnitPointer - (&GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Units[0]);
		TechTrees_Researches_Unit->ChangeValue(lexical_cast<string>(*UnitPointer));
		TechTrees_Researches_Unit->Container = UnitPointer;
		TechTrees_Researches_ComboBox_Unit->SetSelection(*UnitPointer + 1);
		Added = false;
	}
	else
	{
		TechTrees_Researches_Unit->ChangeValue("0");
		TechTrees_Researches_ComboBox_Unit->SetSelection(0);
	}
}

void AGE_Frame::OnTTResearchUnitAdd(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Researches_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		long Temp = 0;
		GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Units.push_back(Temp);
		Added = true;
		ListTTResearchUnits(TTResearchConnectionID);
	}
}

void AGE_Frame::OnTTResearchUnitDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Researches_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Units.erase(GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Units.begin() + TTResearchUnitID);
		if(Selection == TechTrees_DataList_Researches_List_Units->GetCount() - 1)
		TechTrees_DataList_Researches_List_Units->SetSelection(Selection - 1);
		ListTTResearchUnits(TTResearchConnectionID);
	}
}

void AGE_Frame::OnTTResearchUnitCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Researches_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTResearchUnitCopy = *(long*)TechTrees_DataList_Researches_List_Units->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTResearchUnitPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Researches_List_Units->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(long*)TechTrees_DataList_Researches_List_Units->GetClientData(Selection) = TTResearchUnitCopy;
		ListTTResearchUnits(TTResearchConnectionID);
	}
}

string AGE_Frame::GetTTResearchResearchName(short Index, short Upper)
{
	string Name = "";
	Name = lexical_cast<string>(GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Researches[Index])+" ";
	if(LanguageDllString(GenieFile->Researchs[GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Researches[Index]].LanguageDllName) != "")
	{
		Name += LanguageDllString(GenieFile->Researchs[GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Researches[Index]].LanguageDllName);
	}
	else if(GenieFile->Researchs[GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Researches[Index]].Name != "")
	{
		Name += GenieFile->Researchs[GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Researches[Index]].Name;
	}
	else
	{
		Name += "New Research";
	}
	return Name;
}

void AGE_Frame::OnTTResearchResearchSearch(wxCommandEvent& Event)
{
	ListTTResearchResearches(TTResearchConnectionID);
}

void AGE_Frame::ListTTResearchResearches(short Index)
{
	string Name;
	SearchText = wxString(TechTrees_DataList_Researches_Search_Researches->GetValue()).Lower();
	ExcludeText = wxString(TechTrees_DataList_Researches_Search_R_Researches->GetValue()).Lower();
	string CompareText;
	short Selection = TechTrees_DataList_Researches_List_Researches->GetSelection();

	if(TechTrees_DataList_Researches_List_Researches->GetCount() > 0)
	{
		TechTrees_DataList_Researches_List_Researches->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->TechTree.ResearchConnections[Index].Researches.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetTTResearchResearchName(loop, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_DataList_Researches_List_Researches->Append(Name, (void*)&GenieFile->TechTree.ResearchConnections[Index].Researches[loop]);
		}
	}
	TechTrees_DataList_Researches_List_Researches->SetSelection(0);
	TechTrees_DataList_Researches_List_Researches->SetFirstItem(Selection - 3);
	TechTrees_DataList_Researches_List_Researches->SetSelection(Selection);

	wxCommandEvent E;
	OnTTResearchResearchSelect(E);
}

void AGE_Frame::OnTTResearchResearchSelect(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Researches_List_Researches->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TechTrees_DataList_Researches_List_Researches->GetCount() - 1;
			TechTrees_DataList_Researches_List_Researches->SetSelection(Selection);
		}
		long * ResearchPointer = (long*)TechTrees_DataList_Researches_List_Researches->GetClientData(Selection);
		TTResearchResearchID = ResearchPointer - (&GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Researches[0]);
		TechTrees_Researches_Research->ChangeValue(lexical_cast<string>(*ResearchPointer));
		TechTrees_Researches_Research->Container = ResearchPointer;
		TechTrees_Researches_ComboBox_Research->SetSelection(*ResearchPointer + 1);
		Added = false;
	}
	else
	{
		TechTrees_Researches_Research->ChangeValue("0");
		TechTrees_Researches_ComboBox_Research->SetSelection(0);
	}
}

void AGE_Frame::OnTTResearchResearchAdd(wxCommandEvent& Event)
{
	short Selection = TechTrees_MainList_Researches_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		long Temp = 0;
		GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Researches.push_back(Temp);
		Added = true;
		ListTTResearchResearches(TTResearchConnectionID);
	}
}

void AGE_Frame::OnTTResearchResearchDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Researches_List_Researches->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Researches.erase(GenieFile->TechTree.ResearchConnections[TTResearchConnectionID].Researches.begin() + TTResearchResearchID);
		if(Selection == TechTrees_DataList_Researches_List_Researches->GetCount() - 1)
		TechTrees_DataList_Researches_List_Researches->SetSelection(Selection - 1);
		ListTTResearchResearches(TTResearchConnectionID);
	}
}

void AGE_Frame::OnTTResearchResearchCopy(wxCommandEvent& Event)
{
	short Selection = TechTrees_DataList_Researches_List_Researches->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TTResearchResearchCopy = *(long*)TechTrees_DataList_Researches_List_Researches->GetClientData(Selection);
	}
}

void AGE_Frame::OnTTResearchResearchPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TechTrees_DataList_Researches_List_Researches->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(long*)TechTrees_DataList_Researches_List_Researches->GetClientData(Selection) = TTResearchResearchCopy;
		ListTTResearchResearches(TTResearchConnectionID);
	}
}

void AGE_Frame::CreateTechTreeControls()
{
	Tab_TechTrees = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	TechTrees_Main = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_All = new wxBoxSizer(wxVERTICAL);
	TechTrees_Scroller = new wxScrolledWindow(Tab_TechTrees, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	TechTrees_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages = new wxStaticBoxSizer(wxHORIZONTAL, TechTrees_Scroller, "Ages");
	TechTrees_Buildings = new wxStaticBoxSizer(wxHORIZONTAL, TechTrees_Scroller, "Buildings");
	TechTrees_Units = new wxStaticBoxSizer(wxHORIZONTAL, TechTrees_Scroller, "Units");
	TechTrees_Researches = new wxStaticBoxSizer(wxHORIZONTAL, TechTrees_Scroller, "Researches");
	TechTrees_MainList_Ages = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Buildings = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Units = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Researches = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Ages_Search = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Buildings_Search = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Units_Search = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Researches_Search = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Ages_Search_R = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Buildings_Search_R = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Units_Search_R = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Researches_Search_R = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	for(short loop = 0;loop < 2;loop++)
	{
		TechTrees_MainList_Buildings_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		TechTrees_MainList_Units_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		TechTrees_MainList_Researches_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		TechTrees_MainList_Buildings_SearchFilters[loop] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
		TechTrees_MainList_Units_SearchFilters[loop] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
		TechTrees_MainList_Researches_SearchFilters[loop] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
		TechTrees_MainList_Buildings_UseAnd[loop] = new wxCheckBox(TechTrees_Scroller, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20), 0, wxDefaultValidator);
		TechTrees_MainList_Units_UseAnd[loop] = new wxCheckBox(TechTrees_Scroller, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20), 0, wxDefaultValidator);
		TechTrees_MainList_Researches_UseAnd[loop] = new wxCheckBox(TechTrees_Scroller, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20), 0, wxDefaultValidator);
	}
	TechTrees_MainList_Ages_List = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 200));
	TechTrees_MainList_Buildings_List = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_MainList_Units_List = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_MainList_Researches_List = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_MainList_Ages_Buttons = new wxGridSizer(2, 0, 0);
	TechTrees_MainList_Buildings_Buttons = new wxGridSizer(2, 0, 0);
	TechTrees_MainList_Units_Buttons = new wxGridSizer(2, 0, 0);
	TechTrees_MainList_Researches_Buttons = new wxGridSizer(2, 0, 0);
	TechTrees_MainList_Ages_Add = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Add = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Add = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_Add = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Delete = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Delete = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Delete = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_Delete = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Copy = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Copy = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Copy = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_Copy = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Paste = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Paste = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Paste = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_Paste = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	
	TechTrees_Data_Ages = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Ages1 = new wxGridSizer(5, 5, 5);
	TechTrees_Data_Buildings = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Buildings1 = new wxGridSizer(5, 5, 5);
	TechTrees_Data_Units = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Units1 = new wxGridSizer(5, 5, 5);
	TechTrees_Data_Researches = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Researches1 = new wxGridSizer(5, 5, 5);
	TechTrees_DataListHolder_Ages = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_DataListHolder_Buildings = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_DataListHolder_Units = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_DataListHolder_Researches = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_DataList_Ages_Buildings = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Buildings");
	TechTrees_DataList_Ages_Units = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Units");
	TechTrees_DataList_Ages_Researches = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Researches");
	TechTrees_DataList_Buildings_Buildings = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Buildings");
	TechTrees_DataList_Buildings_Units = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Units");
	TechTrees_DataList_Buildings_Researches = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Researches");
	TechTrees_DataList_Units_Units = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Units");
	TechTrees_DataList_Researches_Buildings = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Buildings");
	TechTrees_DataList_Researches_Units = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Units");
	TechTrees_DataList_Researches_Researches = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Researches");
	TechTrees_DataList_Ages_Search_Buildings = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Ages_Search_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Ages_Search_Researches = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Buildings_Search_Buildings = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Buildings_Search_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Buildings_Search_Researches = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Units_Search_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Researches_Search_Buildings = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Researches_Search_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Researches_Search_Researches = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Ages_Search_R_Buildings = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Ages_Search_R_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Ages_Search_R_Researches = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Buildings_Search_R_Buildings = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Buildings_Search_R_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Buildings_Search_R_Researches = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Units_Search_R_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Researches_Search_R_Buildings = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Researches_Search_R_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Researches_Search_R_Researches = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Ages_List_Buildings = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_DataList_Ages_List_Units = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_DataList_Ages_List_Researches = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_DataList_Buildings_List_Buildings = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_DataList_Buildings_List_Units = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_DataList_Buildings_List_Researches = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_DataList_Units_List_Units = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_DataList_Researches_List_Buildings = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_DataList_Researches_List_Units = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_DataList_Researches_List_Researches = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_DataList_Ages_Buttons_Buildings = new wxGridSizer(2, 0, 0);
	TechTrees_DataList_Ages_Buttons_Units = new wxGridSizer(2, 0, 0);
	TechTrees_DataList_Ages_Buttons_Researches = new wxGridSizer(2, 0, 0);
	TechTrees_DataList_Buildings_Buttons_Buildings = new wxGridSizer(2, 0, 0);
	TechTrees_DataList_Buildings_Buttons_Units = new wxGridSizer(2, 0, 0);
	TechTrees_DataList_Buildings_Buttons_Researches = new wxGridSizer(2, 0, 0);
	TechTrees_DataList_Units_Buttons_Units = new wxGridSizer(2, 0, 0);
	TechTrees_DataList_Researches_Buttons_Buildings = new wxGridSizer(2, 0, 0);
	TechTrees_DataList_Researches_Buttons_Units = new wxGridSizer(2, 0, 0);
	TechTrees_DataList_Researches_Buttons_Researches = new wxGridSizer(2, 0, 0);
	TechTrees_DataList_Ages_Add_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Add_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Add_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Add_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Add_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Add_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Units_Add_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Add_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Add_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Add_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Delete_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Delete_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Delete_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Delete_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Delete_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Delete_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Units_Delete_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Delete_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Delete_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Delete_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Copy_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Copy_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Copy_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Copy_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Copy_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Copy_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Units_Copy_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Copy_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Copy_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Copy_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Paste_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Paste_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Paste_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Paste_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Paste_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Paste_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Units_Paste_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Paste_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Paste_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Paste_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	
	TechTrees_Ages_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Text_Unknown1 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_Unknown1 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Ages_Holder_ID = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Text_ID = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Age Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_ID = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Ages_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Text_Unknown2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Always 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_Unknown2 = new TextCtrl_Byte(TechTrees_Scroller, "0", NULL);
	TechTrees_Ages_Holder_Building = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Building = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Ages_ComboBox_Building = new ComboBox_Long(TechTrees_Scroller, TechTrees_Ages_Building);
	TechTrees_Ages_Holder_Unit = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Unit = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Ages_ComboBox_Unit = new ComboBox_Long(TechTrees_Scroller, TechTrees_Ages_Unit);
	TechTrees_Ages_Holder_Research = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Research = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Ages_ComboBox_Research = new ComboBox_Long(TechTrees_Scroller, TechTrees_Ages_Research);
	TechTrees_Ages_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Text_Unknown3 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_Unknown3 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Ages_Holder_Unknown4 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Text_Unknown4 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Second Age Number?", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_Unknown4 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Ages_Holder_Zeroes = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Grid_Zeroes1 = new wxGridSizer(10, 0, 0);
	TechTrees_Ages_Grid_Zeroes2 = new wxGridSizer(10, 0, 0);
	TechTrees_Ages_Text_Zeroes = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 49;loop++)
	TechTrees_Ages_Zeroes1[loop] = new TextCtrl_Short(TechTrees_Scroller, "0", NULL);
	for(short loop = 0;loop < 50;loop++)
	TechTrees_Ages_Zeroes2[loop] = new TextCtrl_Short(TechTrees_Scroller, "0", NULL);
	
	TechTrees_Buildings_Holder_ID = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_ID = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Building Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_ID = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_ComboBox_ID = new ComboBox_Long(TechTrees_Scroller, TechTrees_Buildings_ID);
	TechTrees_Buildings_Holder_Always2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_Always2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Always 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_Always2 = new TextCtrl_Byte(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_Holder_Building = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Building = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_ComboBox_Building = new ComboBox_Long(TechTrees_Scroller, TechTrees_Buildings_Building);
	TechTrees_Buildings_Holder_Unit = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Unit = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_ComboBox_Unit = new ComboBox_Long(TechTrees_Scroller, TechTrees_Buildings_Unit);
	TechTrees_Buildings_Holder_Research = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Research = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_ComboBox_Research = new ComboBox_Long(TechTrees_Scroller, TechTrees_Buildings_Research);
	TechTrees_Buildings_Holder_RequiredResearches = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_RequiredResearches = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Required Researches *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_RequiredResearches = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_RequiredResearches->SetToolTip("Minimum amount of researches that need to be researched for this to be available");
	TechTrees_Buildings_Holder_Age = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_Age = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Age", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_Age = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_Holder_UnitOrResearch1 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_UnitOrResearch1 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unit or Research 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_UnitOrResearch1 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_Holder_UnitOrResearch2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_UnitOrResearch2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unit or Research 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_UnitOrResearch2 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Holder_UnitAndResearch1 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Holder_UnitAndResearch2 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Holder_UnitAndResearch3 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Holder_UnitAndResearch4 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Buildings_Holder_Mode1 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_Mode1 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Mode 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_Mode1 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_Holder_Mode2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_Mode2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Mode 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_Mode2 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_Holder_Unknown2a = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Grid_Unknown2a1 = new wxGridSizer(10, 0, 0);
	TechTrees_Buildings_Grid_Unknown2a2 = new wxGridSizer(10, 0, 0);
	TechTrees_Buildings_Text_Unknown2a = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 8;loop++)
	TechTrees_Buildings_Unknown2a1[loop] = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	for(short loop = 0;loop < 10;loop++)
	TechTrees_Buildings_Unknown2a2[loop] = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_Holder_Unknown2b = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Grid_Unknown2b1 = new wxGridSizer(10, 0, 0);
	TechTrees_Buildings_Grid_Unknown2b2 = new wxGridSizer(10, 0, 0);
	TechTrees_Buildings_Text_Unknown2b = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 7;loop++)
	TechTrees_Buildings_Unknown2b1[loop] = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	for(short loop = 0;loop < 10;loop++)
	TechTrees_Buildings_Unknown2b2[loop] = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Grid_Unknown3 = new wxGridSizer(11, 0, 0);
	TechTrees_Buildings_Text_Unknown3 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Some Sequence", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 11;loop++)
	TechTrees_Buildings_Unknown3[loop] = new TextCtrl_Byte(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_Holder_Connections = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_Connections = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Connections *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_Connections = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_Connections->SetToolTip("5 One or more connections\n6 No connections");
	TechTrees_Buildings_Holder_EnablingResearch = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_EnablingResearch = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Enabling Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_EnablingResearch = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Buildings_EnablingResearch->SetToolTip("Makes available\nUsed by buildings, which need a research to be available");
	TechTrees_Buildings_ComboBox_EnablingResearch = new ComboBox_Long(TechTrees_Scroller, TechTrees_Buildings_EnablingResearch);
	
	TechTrees_Units_Holder_ID = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_ID = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unit Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_ID = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_ComboBox_ID = new ComboBox_Long(TechTrees_Scroller, TechTrees_Units_ID);
	TechTrees_Units_Holder_Always2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_Always2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Always 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_Always2 = new TextCtrl_Byte(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_Holder_UpperBuilding = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_UpperBuilding = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Upper Building", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_UpperBuilding = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_ComboBox_UpperBuilding = new ComboBox_Long(TechTrees_Scroller, TechTrees_Units_UpperBuilding);
	TechTrees_Units_Holder_RequiredResearches = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_RequiredResearches = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Required Researches *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_RequiredResearches = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_RequiredResearches->SetToolTip("Minimum amount of researches that need to be researched for this to be available");
	TechTrees_Units_Holder_Age = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_Age = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Age", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_Age = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_Holder_UnitOrResearch1 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_UnitOrResearch1 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unit or Research 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_UnitOrResearch1 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_Holder_UnitOrResearch2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_UnitOrResearch2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unit or Research 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_UnitOrResearch2 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_ComboBox_Unit[0] = new ComboBox_Long(TechTrees_Scroller, TechTrees_Buildings_UnitOrResearch1);
	TechTrees_ComboBox_Unit[1] = new ComboBox_Long(TechTrees_Scroller, TechTrees_Buildings_UnitOrResearch2);
	TechTrees_ComboBox_Unit[2] = new ComboBox_Long(TechTrees_Scroller, TechTrees_Units_UnitOrResearch1);
	TechTrees_ComboBox_Unit[3] = new ComboBox_Long(TechTrees_Scroller, TechTrees_Units_UnitOrResearch2);
	TechTrees_ComboBox_Research[0] = new ComboBox_Long(TechTrees_Scroller, TechTrees_Buildings_UnitOrResearch1);
	TechTrees_ComboBox_Research[1] = new ComboBox_Long(TechTrees_Scroller, TechTrees_Buildings_UnitOrResearch2);
	TechTrees_ComboBox_Research[2] = new ComboBox_Long(TechTrees_Scroller, TechTrees_Units_UnitOrResearch1);
	TechTrees_ComboBox_Research[3] = new ComboBox_Long(TechTrees_Scroller, TechTrees_Units_UnitOrResearch2);
	TechTrees_Units_Holder_Mode1 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_Mode1 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Mode 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_Mode1 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_Holder_Mode2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_Mode2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Mode 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_Mode2 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_ComboBox_Modes[0] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	TechTrees_ComboBox_Modes[1] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	TechTrees_ComboBox_Modes[2] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	TechTrees_ComboBox_Modes[3] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	TechTrees_Units_Holder_VerticalLine = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_VerticalLine = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Vertical Line Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_VerticalLine = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_Holder_Unknown2a = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Grid_Unknown2a1 = new wxGridSizer(10, 0, 0);
	TechTrees_Units_Grid_Unknown2a2 = new wxGridSizer(10, 0, 0);
	TechTrees_Units_Text_Unknown2a = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 8;loop++)
	TechTrees_Units_Unknown2a1[loop] = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	for(short loop = 0;loop < 10;loop++)
	TechTrees_Units_Unknown2a2[loop] = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_Holder_Unknown2b = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Grid_Unknown2b1 = new wxGridSizer(10, 0, 0);
	TechTrees_Units_Grid_Unknown2b2 = new wxGridSizer(10, 0, 0);
	TechTrees_Units_Text_Unknown2b = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 7;loop++)
	TechTrees_Units_Unknown2b1[loop] = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	for(short loop = 0;loop < 10;loop++)
	TechTrees_Units_Unknown2b2[loop] = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_Holder_Unit = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Unit = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_ComboBox_Unit = new ComboBox_Long(TechTrees_Scroller, TechTrees_Units_Unit);
	TechTrees_Units_Holder_LocationInAge = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_LocationInAge = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Location In Age *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_Unknown3 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_Unknown3->SetToolTip("1 First\n2 Second");
	TechTrees_Units_Holder_RequiredResearch = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_RequiredResearch = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Required Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_RequiredResearch = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_RequiredResearch->SetToolTip("Upgrades unit\nUsed by units, which aren't first in upgrade line");
	TechTrees_Units_ComboBox_RequiredResearch = new ComboBox_Long(TechTrees_Scroller, TechTrees_Units_RequiredResearch);
	TechTrees_Units_Holder_LineMode = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_LineMode = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Line Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_LineMode = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_LineMode->SetToolTip("2 First in vertical line\n3 Not first");
	TechTrees_Units_Holder_EnablingResearch = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_EnablingResearch = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Enabling Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_EnablingResearch = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Units_EnablingResearch->SetToolTip("Makes available\nUsed by units, which need a research to be available");
	TechTrees_Units_ComboBox_EnablingResearch = new ComboBox_Long(TechTrees_Scroller, TechTrees_Units_EnablingResearch);
	
	TechTrees_Researches_Holder_ID = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_ID = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Research Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_ID = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_ComboBox_ID = new ComboBox_Long(TechTrees_Scroller, TechTrees_Researches_ID);
	TechTrees_Researches_Holder_Always2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_Always2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Always 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_Always2 = new TextCtrl_Byte(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_Holder_UpperBuilding = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_UpperBuilding = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Upper Building", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_UpperBuilding = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_ComboBox_UpperBuilding = new ComboBox_Long(TechTrees_Scroller, TechTrees_Researches_UpperBuilding);
	TechTrees_Researches_Holder_UpperResearch = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_UpperResearch = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Upper Research", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_UpperResearch = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_ComboBox_UpperResearch = new ComboBox_Long(TechTrees_Scroller, TechTrees_Researches_UpperResearch);
	TechTrees_Researches_Holder_Building = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Building = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_ComboBox_Building = new ComboBox_Long(TechTrees_Scroller, TechTrees_Researches_Building);
	TechTrees_Researches_Holder_Unit = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Unit = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_ComboBox_Unit = new ComboBox_Long(TechTrees_Scroller, TechTrees_Researches_Unit);
	TechTrees_Researches_Holder_Research = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Research = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_ComboBox_Research = new ComboBox_Long(TechTrees_Scroller, TechTrees_Researches_Research);
	TechTrees_Researches_Holder_RequiredResearches = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_RequiredResearches = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Required Researches *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_RequiredResearches = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_RequiredResearches->SetToolTip("Minimum amount of researches that need to be researched for this to be available");
	TechTrees_Researches_Holder_Age = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_Age = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Age", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_Age = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_Holder_LineMode = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_LineMode = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Line Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_LineMode = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_LineMode->SetToolTip("0 Independent/new in its line\n3 Depends on a previous research in its line");
	TechTrees_Researches_Holder_VerticalLine = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_VerticalLine = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Vertical Line Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_VerticalLine = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_Holder_LocationInAge = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_LocationInAge = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Location In Age *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_LocationInAge = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_LocationInAge->SetToolTip("0 Hidden\n1 First\n2 Second");
	TechTrees_Researches_Holder_Unknown9 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_Unknown9 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " First Age Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_Unknown9 = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_Unknown9->SetToolTip("0 First Age\n4 Others");
	TechTrees_Researches_Holder_Unknown2a = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Grid_Unknown2a1 = new wxGridSizer(10, 0, 0);
	TechTrees_Researches_Grid_Unknown2a2 = new wxGridSizer(10, 0, 0);
	TechTrees_Researches_Text_Unknown2a = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 9;loop++)
	TechTrees_Researches_Unknown2a1[loop] = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	for(short loop = 0;loop < 10;loop++)
	TechTrees_Researches_Unknown2a2[loop] = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	TechTrees_Researches_Holder_Unknown2b = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Grid_Unknown2b1 = new wxGridSizer(10, 0, 0);
	TechTrees_Researches_Grid_Unknown2b2 = new wxGridSizer(10, 0, 0);
	TechTrees_Researches_Text_Unknown2b = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 8;loop++)
	TechTrees_Researches_Unknown2b1[loop] = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	for(short loop = 0;loop < 10;loop++)
	TechTrees_Researches_Unknown2b2[loop] = new TextCtrl_Long(TechTrees_Scroller, "0", NULL);
	
	for(short loop = 0;loop < 2;loop++)
	{
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Normal Name");	// 0
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Upper Building");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Required Researches");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Age");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Unit or Research 1");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Unit or Research 2");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("U/R 1 Mode");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("U/R 2 Mode");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Vertical Line Number");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Location In Age");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Required Research");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Line Mode");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Enabling Research");
		TechTrees_MainList_Units_SearchFilters[loop]->SetSelection(0);
		
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Normal Name");	// 0
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Required Researches");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Age");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Unit or Research 1");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Unit or Research 2");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("U/R 1 Mode");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("U/R 2 Mode");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Connections");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Enabling Research");
		TechTrees_MainList_Buildings_SearchFilters[loop]->SetSelection(0);
		
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Normal Name");	// 0
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Upper Building");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Required Researches");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Age");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Upper Research");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Line Mode");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Vertical Line Number");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Location In Age");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("First Age Mode");
		TechTrees_MainList_Researches_SearchFilters[loop]->SetSelection(0);
	}
	
	for(short loop = 0;loop < 4;loop++)
	{
		TechTrees_ComboBox_Modes[loop]->Append("No unit/research");	// 0
		TechTrees_ComboBox_Modes[loop]->Append("Building");
		TechTrees_ComboBox_Modes[loop]->Append("Unit");
		TechTrees_ComboBox_Modes[loop]->Append("Research");
		TechTrees_ComboBox_Modes[loop]->SetSelection(0);
	}
	
	TechTrees_MainList_Ages_Buttons->Add(TechTrees_MainList_Ages_Add, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Buttons->Add(TechTrees_MainList_Buildings_Add, 1, wxEXPAND);
	TechTrees_MainList_Units_Buttons->Add(TechTrees_MainList_Units_Add, 1, wxEXPAND);
	TechTrees_MainList_Researches_Buttons->Add(TechTrees_MainList_Researches_Add, 1, wxEXPAND);
	TechTrees_MainList_Ages_Buttons->Add(TechTrees_MainList_Ages_Delete, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Buttons->Add(TechTrees_MainList_Buildings_Delete, 1, wxEXPAND);
	TechTrees_MainList_Units_Buttons->Add(TechTrees_MainList_Units_Delete, 1, wxEXPAND);
	TechTrees_MainList_Researches_Buttons->Add(TechTrees_MainList_Researches_Delete, 1, wxEXPAND);
	TechTrees_MainList_Ages_Buttons->Add(TechTrees_MainList_Ages_Copy, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Buttons->Add(TechTrees_MainList_Buildings_Copy, 1, wxEXPAND);
	TechTrees_MainList_Units_Buttons->Add(TechTrees_MainList_Units_Copy, 1, wxEXPAND);
	TechTrees_MainList_Researches_Buttons->Add(TechTrees_MainList_Researches_Copy, 1, wxEXPAND);
	TechTrees_MainList_Ages_Buttons->Add(TechTrees_MainList_Ages_Paste, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Buttons->Add(TechTrees_MainList_Buildings_Paste, 1, wxEXPAND);
	TechTrees_MainList_Units_Buttons->Add(TechTrees_MainList_Units_Paste, 1, wxEXPAND);
	TechTrees_MainList_Researches_Buttons->Add(TechTrees_MainList_Researches_Paste, 1, wxEXPAND);
	
	TechTrees_MainList_Ages->Add(TechTrees_MainList_Ages_Search, 0, wxEXPAND);
	TechTrees_MainList_Ages->Add(TechTrees_MainList_Ages_Search_R, 0, wxEXPAND);
	TechTrees_MainList_Buildings_Searches[0]->Add(TechTrees_MainList_Buildings_Search, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Searches[0]->Add(2, -1);
	TechTrees_MainList_Buildings_Searches[0]->Add(TechTrees_MainList_Buildings_UseAnd[0], 0, wxEXPAND);
	TechTrees_MainList_Buildings_Searches[1]->Add(TechTrees_MainList_Buildings_Search_R, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Searches[1]->Add(2, -1);
	TechTrees_MainList_Buildings_Searches[1]->Add(TechTrees_MainList_Buildings_UseAnd[1], 0, wxEXPAND);
	TechTrees_MainList_Units_Searches[0]->Add(TechTrees_MainList_Units_Search, 1, wxEXPAND);
	TechTrees_MainList_Units_Searches[0]->Add(2, -1);
	TechTrees_MainList_Units_Searches[0]->Add(TechTrees_MainList_Units_UseAnd[0], 0, wxEXPAND);
	TechTrees_MainList_Units_Searches[1]->Add(TechTrees_MainList_Units_Search_R, 1, wxEXPAND);
	TechTrees_MainList_Units_Searches[1]->Add(2, -1);
	TechTrees_MainList_Units_Searches[1]->Add(TechTrees_MainList_Units_UseAnd[1], 0, wxEXPAND);
	TechTrees_MainList_Researches_Searches[0]->Add(TechTrees_MainList_Researches_Search, 1, wxEXPAND);
	TechTrees_MainList_Researches_Searches[0]->Add(2, -1);
	TechTrees_MainList_Researches_Searches[0]->Add(TechTrees_MainList_Researches_UseAnd[0], 0, wxEXPAND);
	TechTrees_MainList_Researches_Searches[1]->Add(TechTrees_MainList_Researches_Search_R, 1, wxEXPAND);
	TechTrees_MainList_Researches_Searches[1]->Add(2, -1);
	TechTrees_MainList_Researches_Searches[1]->Add(TechTrees_MainList_Researches_UseAnd[1], 0, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	{
		TechTrees_MainList_Buildings->Add(TechTrees_MainList_Buildings_Searches[loop], 0, wxEXPAND);
		TechTrees_MainList_Units->Add(TechTrees_MainList_Units_Searches[loop], 0, wxEXPAND);
		TechTrees_MainList_Researches->Add(TechTrees_MainList_Researches_Searches[loop], 0, wxEXPAND);
	}
	for(short loop = 0;loop < 2;loop++)
	{
		TechTrees_MainList_Buildings->Add(TechTrees_MainList_Buildings_SearchFilters[loop], 0, wxEXPAND);
		TechTrees_MainList_Units->Add(TechTrees_MainList_Units_SearchFilters[loop], 0, wxEXPAND);
		TechTrees_MainList_Researches->Add(TechTrees_MainList_Researches_SearchFilters[loop], 0, wxEXPAND);
	}
	TechTrees_MainList_Ages->Add(-1, 2);
	TechTrees_MainList_Buildings->Add(-1, 2);
	TechTrees_MainList_Units->Add(-1, 2);
	TechTrees_MainList_Researches->Add(-1, 2);
	TechTrees_MainList_Ages->Add(TechTrees_MainList_Ages_List, 1, wxEXPAND);
	TechTrees_MainList_Buildings->Add(TechTrees_MainList_Buildings_List, 1, wxEXPAND);
	TechTrees_MainList_Units->Add(TechTrees_MainList_Units_List, 1, wxEXPAND);
	TechTrees_MainList_Researches->Add(TechTrees_MainList_Researches_List, 1, wxEXPAND);
	TechTrees_MainList_Ages->Add(-1, 2);
	TechTrees_MainList_Buildings->Add(-1, 2);
	TechTrees_MainList_Units->Add(-1, 2);
	TechTrees_MainList_Researches->Add(-1, 2);
	TechTrees_MainList_Ages->Add(TechTrees_MainList_Ages_Buttons, 0, wxEXPAND);
	TechTrees_MainList_Buildings->Add(TechTrees_MainList_Buildings_Buttons, 0, wxEXPAND);
	TechTrees_MainList_Units->Add(TechTrees_MainList_Units_Buttons, 0, wxEXPAND);
	TechTrees_MainList_Researches->Add(TechTrees_MainList_Researches_Buttons, 0, wxEXPAND);

	TechTrees_Ages_Holder_Building->Add(TechTrees_Ages_Building, 0, wxEXPAND);
	TechTrees_Ages_Holder_Building->Add(TechTrees_Ages_ComboBox_Building, 0, wxEXPAND);
	TechTrees_Ages_Holder_Unit->Add(TechTrees_Ages_Unit, 0, wxEXPAND);
	TechTrees_Ages_Holder_Unit->Add(TechTrees_Ages_ComboBox_Unit, 0, wxEXPAND);
	TechTrees_Ages_Holder_Research->Add(TechTrees_Ages_Research, 0, wxEXPAND);
	TechTrees_Ages_Holder_Research->Add(TechTrees_Ages_ComboBox_Research, 0, wxEXPAND);
	
	TechTrees_Buildings_Holder_Building->Add(TechTrees_Buildings_Building, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Building->Add(TechTrees_Buildings_ComboBox_Building, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Unit->Add(TechTrees_Buildings_Unit, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Unit->Add(TechTrees_Buildings_ComboBox_Unit, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Research->Add(TechTrees_Buildings_Research, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Research->Add(TechTrees_Buildings_ComboBox_Research, 0, wxEXPAND);
	
	TechTrees_Units_Holder_Unit->Add(TechTrees_Units_Unit, 0, wxEXPAND);
	TechTrees_Units_Holder_Unit->Add(TechTrees_Units_ComboBox_Unit, 0, wxEXPAND);

	TechTrees_Researches_Holder_Building->Add(TechTrees_Researches_Building, 0, wxEXPAND);
	TechTrees_Researches_Holder_Building->Add(TechTrees_Researches_ComboBox_Building, 0, wxEXPAND);
	TechTrees_Researches_Holder_Unit->Add(TechTrees_Researches_Unit, 0, wxEXPAND);
	TechTrees_Researches_Holder_Unit->Add(TechTrees_Researches_ComboBox_Unit, 0, wxEXPAND);
	TechTrees_Researches_Holder_Research->Add(TechTrees_Researches_Research, 0, wxEXPAND);
	TechTrees_Researches_Holder_Research->Add(TechTrees_Researches_ComboBox_Research, 0, wxEXPAND);

	TechTrees_DataList_Ages_Buttons_Buildings->Add(TechTrees_DataList_Ages_Add_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Units->Add(TechTrees_DataList_Ages_Add_Units, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Researches->Add(TechTrees_DataList_Ages_Add_Researches, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Buildings->Add(TechTrees_DataList_Buildings_Add_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Units->Add(TechTrees_DataList_Buildings_Add_Units, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Researches->Add(TechTrees_DataList_Buildings_Add_Researches, 1, wxEXPAND);
	TechTrees_DataList_Units_Buttons_Units->Add(TechTrees_DataList_Units_Add_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Buildings->Add(TechTrees_DataList_Researches_Add_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Units->Add(TechTrees_DataList_Researches_Add_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Researches->Add(TechTrees_DataList_Researches_Add_Researches, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Buildings->Add(TechTrees_DataList_Ages_Delete_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Units->Add(TechTrees_DataList_Ages_Delete_Units, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Researches->Add(TechTrees_DataList_Ages_Delete_Researches, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Buildings->Add(TechTrees_DataList_Buildings_Delete_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Units->Add(TechTrees_DataList_Buildings_Delete_Units, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Researches->Add(TechTrees_DataList_Buildings_Delete_Researches, 1, wxEXPAND);
	TechTrees_DataList_Units_Buttons_Units->Add(TechTrees_DataList_Units_Delete_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Buildings->Add(TechTrees_DataList_Researches_Delete_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Units->Add(TechTrees_DataList_Researches_Delete_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Researches->Add(TechTrees_DataList_Researches_Delete_Researches, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Buildings->Add(TechTrees_DataList_Ages_Copy_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Units->Add(TechTrees_DataList_Ages_Copy_Units, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Researches->Add(TechTrees_DataList_Ages_Copy_Researches, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Buildings->Add(TechTrees_DataList_Buildings_Copy_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Units->Add(TechTrees_DataList_Buildings_Copy_Units, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Researches->Add(TechTrees_DataList_Buildings_Copy_Researches, 1, wxEXPAND);
	TechTrees_DataList_Units_Buttons_Units->Add(TechTrees_DataList_Units_Copy_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Buildings->Add(TechTrees_DataList_Researches_Copy_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Units->Add(TechTrees_DataList_Researches_Copy_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Researches->Add(TechTrees_DataList_Researches_Copy_Researches, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Buildings->Add(TechTrees_DataList_Ages_Paste_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Units->Add(TechTrees_DataList_Ages_Paste_Units, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Researches->Add(TechTrees_DataList_Ages_Paste_Researches, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Buildings->Add(TechTrees_DataList_Buildings_Paste_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Units->Add(TechTrees_DataList_Buildings_Paste_Units, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Researches->Add(TechTrees_DataList_Buildings_Paste_Researches, 1, wxEXPAND);
	TechTrees_DataList_Units_Buttons_Units->Add(TechTrees_DataList_Units_Paste_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Buildings->Add(TechTrees_DataList_Researches_Paste_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Units->Add(TechTrees_DataList_Researches_Paste_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Researches->Add(TechTrees_DataList_Researches_Paste_Researches, 1, wxEXPAND);

	TechTrees_DataList_Ages_Buildings->Add(TechTrees_DataList_Ages_Search_Buildings, 0, wxEXPAND);
	TechTrees_DataList_Ages_Units->Add(TechTrees_DataList_Ages_Search_Units, 0, wxEXPAND);
	TechTrees_DataList_Ages_Researches->Add(TechTrees_DataList_Ages_Search_Researches, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Buildings->Add(TechTrees_DataList_Buildings_Search_Buildings, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Units->Add(TechTrees_DataList_Buildings_Search_Units, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Researches->Add(TechTrees_DataList_Buildings_Search_Researches, 0, wxEXPAND);
	TechTrees_DataList_Units_Units->Add(TechTrees_DataList_Units_Search_Units, 0, wxEXPAND);
	TechTrees_DataList_Researches_Buildings->Add(TechTrees_DataList_Researches_Search_Buildings, 0, wxEXPAND);
	TechTrees_DataList_Researches_Units->Add(TechTrees_DataList_Researches_Search_Units, 0, wxEXPAND);
	TechTrees_DataList_Researches_Researches->Add(TechTrees_DataList_Researches_Search_Researches, 0, wxEXPAND);
	TechTrees_DataList_Ages_Buildings->Add(TechTrees_DataList_Ages_Search_R_Buildings, 0, wxEXPAND);
	TechTrees_DataList_Ages_Units->Add(TechTrees_DataList_Ages_Search_R_Units, 0, wxEXPAND);
	TechTrees_DataList_Ages_Researches->Add(TechTrees_DataList_Ages_Search_R_Researches, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Buildings->Add(TechTrees_DataList_Buildings_Search_R_Buildings, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Units->Add(TechTrees_DataList_Buildings_Search_R_Units, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Researches->Add(TechTrees_DataList_Buildings_Search_R_Researches, 0, wxEXPAND);
	TechTrees_DataList_Units_Units->Add(TechTrees_DataList_Units_Search_R_Units, 0, wxEXPAND);
	TechTrees_DataList_Researches_Buildings->Add(TechTrees_DataList_Researches_Search_R_Buildings, 0, wxEXPAND);
	TechTrees_DataList_Researches_Units->Add(TechTrees_DataList_Researches_Search_R_Units, 0, wxEXPAND);
	TechTrees_DataList_Researches_Researches->Add(TechTrees_DataList_Researches_Search_R_Researches, 0, wxEXPAND);
	TechTrees_DataList_Ages_Buildings->Add(-1, 2);
	TechTrees_DataList_Ages_Units->Add(-1, 2);
	TechTrees_DataList_Ages_Researches->Add(-1, 2);
	TechTrees_DataList_Buildings_Buildings->Add(-1, 2);
	TechTrees_DataList_Buildings_Units->Add(-1, 2);
	TechTrees_DataList_Buildings_Researches->Add(-1, 2);
	TechTrees_DataList_Units_Units->Add(-1, 2);
	TechTrees_DataList_Researches_Buildings->Add(-1, 2);
	TechTrees_DataList_Researches_Units->Add(-1, 2);
	TechTrees_DataList_Researches_Researches->Add(-1, 2);
	TechTrees_DataList_Ages_Buildings->Add(TechTrees_DataList_Ages_List_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buildings->Add(-1, 2);
	TechTrees_DataList_Ages_Buildings->Add(TechTrees_Ages_Holder_Building, 0, wxEXPAND);
	TechTrees_DataList_Ages_Units->Add(TechTrees_DataList_Ages_List_Units, 1, wxEXPAND);
	TechTrees_DataList_Ages_Units->Add(-1, 2);
	TechTrees_DataList_Ages_Units->Add(TechTrees_Ages_Holder_Unit, 0, wxEXPAND);
	TechTrees_DataList_Ages_Researches->Add(TechTrees_DataList_Ages_List_Researches, 1, wxEXPAND);
	TechTrees_DataList_Ages_Researches->Add(-1, 2);
	TechTrees_DataList_Ages_Researches->Add(TechTrees_Ages_Holder_Research, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Buildings->Add(TechTrees_DataList_Buildings_List_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buildings->Add(-1, 2);
	TechTrees_DataList_Buildings_Buildings->Add(TechTrees_Buildings_Holder_Building, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Units->Add(TechTrees_DataList_Buildings_List_Units, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Units->Add(-1, 2);
	TechTrees_DataList_Buildings_Units->Add(TechTrees_Buildings_Holder_Unit, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Researches->Add(TechTrees_DataList_Buildings_List_Researches, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Researches->Add(-1, 2);
	TechTrees_DataList_Buildings_Researches->Add(TechTrees_Buildings_Holder_Research, 0, wxEXPAND);
	TechTrees_DataList_Units_Units->Add(TechTrees_DataList_Units_List_Units, 1, wxEXPAND);
	TechTrees_DataList_Units_Units->Add(-1, 2);
	TechTrees_DataList_Units_Units->Add(TechTrees_Units_Holder_Unit, 0, wxEXPAND);
	TechTrees_DataList_Researches_Buildings->Add(TechTrees_DataList_Researches_List_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buildings->Add(-1, 2);
	TechTrees_DataList_Researches_Buildings->Add(TechTrees_Researches_Holder_Building, 0, wxEXPAND);
	TechTrees_DataList_Researches_Units->Add(TechTrees_DataList_Researches_List_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Units->Add(-1, 2);
	TechTrees_DataList_Researches_Units->Add(TechTrees_Researches_Holder_Unit, 0, wxEXPAND);
	TechTrees_DataList_Researches_Researches->Add(TechTrees_DataList_Researches_List_Researches, 1, wxEXPAND);
	TechTrees_DataList_Researches_Researches->Add(-1, 2);
	TechTrees_DataList_Researches_Researches->Add(TechTrees_Researches_Holder_Research, 0, wxEXPAND);
	TechTrees_DataList_Ages_Buildings->Add(-1, 2);
	TechTrees_DataList_Ages_Units->Add(-1, 2);
	TechTrees_DataList_Ages_Researches->Add(-1, 2);
	TechTrees_DataList_Buildings_Buildings->Add(-1, 2);
	TechTrees_DataList_Buildings_Units->Add(-1, 2);
	TechTrees_DataList_Buildings_Researches->Add(-1, 2);
	TechTrees_DataList_Units_Units->Add(-1, 2);
	TechTrees_DataList_Researches_Buildings->Add(-1, 2);
	TechTrees_DataList_Researches_Units->Add(-1, 2);
	TechTrees_DataList_Researches_Researches->Add(-1, 2);
	TechTrees_DataList_Ages_Buildings->Add(TechTrees_DataList_Ages_Buttons_Buildings, 0, wxEXPAND);
	TechTrees_DataList_Ages_Units->Add(TechTrees_DataList_Ages_Buttons_Units, 0, wxEXPAND);
	TechTrees_DataList_Ages_Researches->Add(TechTrees_DataList_Ages_Buttons_Researches, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Buildings->Add(TechTrees_DataList_Buildings_Buttons_Buildings, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Units->Add(TechTrees_DataList_Buildings_Buttons_Units, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Researches->Add(TechTrees_DataList_Buildings_Buttons_Researches, 0, wxEXPAND);
	TechTrees_DataList_Units_Units->Add(TechTrees_DataList_Units_Buttons_Units, 0, wxEXPAND);
	TechTrees_DataList_Researches_Buildings->Add(TechTrees_DataList_Researches_Buttons_Buildings, 0, wxEXPAND);
	TechTrees_DataList_Researches_Units->Add(TechTrees_DataList_Researches_Buttons_Units, 0, wxEXPAND);
	TechTrees_DataList_Researches_Researches->Add(TechTrees_DataList_Researches_Buttons_Researches, 0, wxEXPAND);
	
	TechTrees_DataListHolder_Ages->Add(TechTrees_DataList_Ages_Buildings, 1, wxEXPAND);
	TechTrees_DataListHolder_Ages->Add(10, -1);
	TechTrees_DataListHolder_Ages->Add(TechTrees_DataList_Ages_Units, 1, wxEXPAND);
	TechTrees_DataListHolder_Ages->Add(10, -1);
	TechTrees_DataListHolder_Ages->Add(TechTrees_DataList_Ages_Researches, 1, wxEXPAND);
	
	TechTrees_Ages_Holder_ID->Add(TechTrees_Ages_Text_ID, 0, wxEXPAND);
	TechTrees_Ages_Holder_ID->Add(TechTrees_Ages_ID, 0, wxEXPAND);
	TechTrees_Ages_Holder_Unknown4->Add(TechTrees_Ages_Text_Unknown4, 0, wxEXPAND);
	TechTrees_Ages_Holder_Unknown4->Add(TechTrees_Ages_Unknown4, 0, wxEXPAND);
	TechTrees_Ages_Holder_Unknown1->Add(TechTrees_Ages_Text_Unknown1, 0, wxEXPAND);
	TechTrees_Ages_Holder_Unknown1->Add(TechTrees_Ages_Unknown1, 0, wxEXPAND);
	TechTrees_Ages_Holder_Unknown3->Add(TechTrees_Ages_Text_Unknown3, 0, wxEXPAND);
	TechTrees_Ages_Holder_Unknown3->Add(TechTrees_Ages_Unknown3, 0, wxEXPAND);
	TechTrees_Ages_Holder_Unknown2->Add(TechTrees_Ages_Text_Unknown2, 0, wxEXPAND);
	TechTrees_Ages_Holder_Unknown2->Add(TechTrees_Ages_Unknown2, 0, wxEXPAND);
	
	TechTrees_Data_Ages1->Add(TechTrees_Ages_Holder_ID, 1, wxEXPAND);
	TechTrees_Data_Ages1->Add(TechTrees_Ages_Holder_Unknown4, 1, wxEXPAND);
	TechTrees_Data_Ages1->Add(TechTrees_Ages_Holder_Unknown1, 1, wxEXPAND);
	TechTrees_Data_Ages1->Add(TechTrees_Ages_Holder_Unknown3, 1, wxEXPAND);
	TechTrees_Data_Ages1->Add(TechTrees_Ages_Holder_Unknown2, 1, wxEXPAND);
	
	for(short loop = 0;loop < 49;loop++)
	TechTrees_Ages_Grid_Zeroes1->Add(TechTrees_Ages_Zeroes1[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 50;loop++)
	TechTrees_Ages_Grid_Zeroes2->Add(TechTrees_Ages_Zeroes2[loop], 1, wxEXPAND);
	TechTrees_Ages_Holder_Zeroes->Add(TechTrees_Ages_Text_Zeroes, 0, wxEXPAND);
	TechTrees_Ages_Holder_Zeroes->Add(TechTrees_Ages_Grid_Zeroes1, 0, wxEXPAND);
	TechTrees_Ages_Holder_Zeroes->Add(TechTrees_Ages_Grid_Zeroes2, 0, wxEXPAND);
	
	TechTrees_Data_Ages->Add(TechTrees_Data_Ages1, 0, wxEXPAND);
	TechTrees_Data_Ages->Add(-1, 5);
	TechTrees_Data_Ages->Add(TechTrees_DataListHolder_Ages, 0, wxEXPAND);
	TechTrees_Data_Ages->Add(-1, 5);
	TechTrees_Data_Ages->Add(TechTrees_Ages_Holder_Zeroes, 0, wxEXPAND);
	
	TechTrees_DataListHolder_Buildings->Add(TechTrees_DataList_Buildings_Buildings, 1, wxEXPAND);
	TechTrees_DataListHolder_Buildings->Add(10, -1);
	TechTrees_DataListHolder_Buildings->Add(TechTrees_DataList_Buildings_Units, 1, wxEXPAND);
	TechTrees_DataListHolder_Buildings->Add(10, -1);
	TechTrees_DataListHolder_Buildings->Add(TechTrees_DataList_Buildings_Researches, 1, wxEXPAND);
	
	TechTrees_Buildings_Holder_ID->Add(TechTrees_Buildings_Text_ID, 0, wxEXPAND);
	TechTrees_Buildings_Holder_ID->Add(TechTrees_Buildings_ID, 0, wxEXPAND);
	TechTrees_Buildings_Holder_ID->Add(TechTrees_Buildings_ComboBox_ID, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Connections->Add(TechTrees_Buildings_Text_Connections, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Connections->Add(TechTrees_Buildings_Connections, 0, wxEXPAND);
	TechTrees_Buildings_Holder_EnablingResearch->Add(TechTrees_Buildings_Text_EnablingResearch, 0, wxEXPAND);
	TechTrees_Buildings_Holder_EnablingResearch->Add(TechTrees_Buildings_EnablingResearch, 0, wxEXPAND);
	TechTrees_Buildings_Holder_EnablingResearch->Add(TechTrees_Buildings_ComboBox_EnablingResearch, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Always2->Add(TechTrees_Buildings_Text_Always2, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Always2->Add(TechTrees_Buildings_Always2, 0, wxEXPAND);
	TechTrees_Buildings_Holder_RequiredResearches->Add(TechTrees_Buildings_Text_RequiredResearches, 0, wxEXPAND);
	TechTrees_Buildings_Holder_RequiredResearches->Add(TechTrees_Buildings_RequiredResearches, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Age->Add(TechTrees_Buildings_Text_Age, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Age->Add(TechTrees_Buildings_Age, 0, wxEXPAND);
	TechTrees_Holder_UnitAndResearch1->Add(TechTrees_ComboBox_Unit[0], 1, wxEXPAND);
	TechTrees_Holder_UnitAndResearch1->Add(TechTrees_ComboBox_Research[0], 1, wxEXPAND);
	TechTrees_Holder_UnitAndResearch2->Add(TechTrees_ComboBox_Unit[1], 1, wxEXPAND);
	TechTrees_Holder_UnitAndResearch2->Add(TechTrees_ComboBox_Research[1], 1, wxEXPAND);
	TechTrees_Buildings_Holder_UnitOrResearch1->Add(TechTrees_Buildings_Text_UnitOrResearch1, 0, wxEXPAND);
	TechTrees_Buildings_Holder_UnitOrResearch1->Add(TechTrees_Buildings_UnitOrResearch1, 0, wxEXPAND);
	TechTrees_Buildings_Holder_UnitOrResearch1->Add(TechTrees_Holder_UnitAndResearch1, 1, wxEXPAND);
	TechTrees_Buildings_Holder_UnitOrResearch2->Add(TechTrees_Buildings_Text_UnitOrResearch2, 0, wxEXPAND);
	TechTrees_Buildings_Holder_UnitOrResearch2->Add(TechTrees_Buildings_UnitOrResearch2, 0, wxEXPAND);
	TechTrees_Buildings_Holder_UnitOrResearch2->Add(TechTrees_Holder_UnitAndResearch2, 1, wxEXPAND);
	TechTrees_Buildings_Holder_Mode1->Add(TechTrees_Buildings_Text_Mode1, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Mode1->Add(TechTrees_Buildings_Mode1, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Mode1->Add(TechTrees_ComboBox_Modes[0], 0, wxEXPAND);
	TechTrees_Buildings_Holder_Mode2->Add(TechTrees_Buildings_Text_Mode2, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Mode2->Add(TechTrees_Buildings_Mode2, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Mode2->Add(TechTrees_ComboBox_Modes[1], 0, wxEXPAND);
	
	for(short loop = 0;loop < 11;loop++)
	TechTrees_Buildings_Grid_Unknown3->Add(TechTrees_Buildings_Unknown3[loop], 1, wxEXPAND);
	TechTrees_Buildings_Holder_Unknown3->Add(TechTrees_Buildings_Text_Unknown3, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Unknown3->Add(TechTrees_Buildings_Grid_Unknown3, 0, wxEXPAND);
	
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_Holder_ID, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_Holder_Age, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_Holder_Connections, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_Holder_EnablingResearch, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_Holder_RequiredResearches, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_Holder_UnitOrResearch1, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_Holder_UnitOrResearch2, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_Holder_Mode1, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_Holder_Mode2, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_Holder_Always2, 1, wxEXPAND);
	
	for(short loop = 0;loop < 8;loop++)
	TechTrees_Buildings_Grid_Unknown2a1->Add(TechTrees_Buildings_Unknown2a1[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 10;loop++)
	TechTrees_Buildings_Grid_Unknown2a2->Add(TechTrees_Buildings_Unknown2a2[loop], 1, wxEXPAND);
	TechTrees_Buildings_Holder_Unknown2a->Add(TechTrees_Buildings_Text_Unknown2a, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Unknown2a->Add(TechTrees_Buildings_Grid_Unknown2a1, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Unknown2a->Add(TechTrees_Buildings_Grid_Unknown2a2, 0, wxEXPAND);
	
	for(short loop = 0;loop < 7;loop++)
	TechTrees_Buildings_Grid_Unknown2b1->Add(TechTrees_Buildings_Unknown2b1[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 10;loop++)
	TechTrees_Buildings_Grid_Unknown2b2->Add(TechTrees_Buildings_Unknown2b2[loop], 1, wxEXPAND);
	TechTrees_Buildings_Holder_Unknown2b->Add(TechTrees_Buildings_Text_Unknown2b, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Unknown2b->Add(TechTrees_Buildings_Grid_Unknown2b1, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Unknown2b->Add(TechTrees_Buildings_Grid_Unknown2b2, 0, wxEXPAND);
	
	TechTrees_Data_Buildings->Add(TechTrees_Data_Buildings1, 0, wxEXPAND);
	TechTrees_Data_Buildings->Add(-1, 5);
	TechTrees_Data_Buildings->Add(TechTrees_Buildings_Holder_Unknown3, 0, wxEXPAND);
	TechTrees_Data_Buildings->Add(-1, 5);
	TechTrees_Data_Buildings->Add(TechTrees_DataListHolder_Buildings, 0, wxEXPAND);
	TechTrees_Data_Buildings->Add(-1, 5);
	TechTrees_Data_Buildings->Add(TechTrees_Buildings_Holder_Unknown2a, 0, wxEXPAND);
	TechTrees_Data_Buildings->Add(-1, 5);
	TechTrees_Data_Buildings->Add(TechTrees_Buildings_Holder_Unknown2b, 0, wxEXPAND);
	
	TechTrees_DataListHolder_Units->Add(TechTrees_DataList_Units_Units, 1, wxEXPAND);
	TechTrees_DataListHolder_Units->AddStretchSpacer(2);
	
	TechTrees_Units_Holder_ID->Add(TechTrees_Units_Text_ID, 0, wxEXPAND);
	TechTrees_Units_Holder_ID->Add(TechTrees_Units_ID, 0, wxEXPAND);
	TechTrees_Units_Holder_ID->Add(TechTrees_Units_ComboBox_ID, 0, wxEXPAND);
	TechTrees_Units_Holder_UpperBuilding->Add(TechTrees_Units_Text_UpperBuilding, 0, wxEXPAND);
	TechTrees_Units_Holder_UpperBuilding->Add(TechTrees_Units_UpperBuilding, 0, wxEXPAND);
	TechTrees_Units_Holder_UpperBuilding->Add(TechTrees_Units_ComboBox_UpperBuilding, 0, wxEXPAND);
	TechTrees_Units_Holder_LocationInAge->Add(TechTrees_Units_Text_LocationInAge, 0, wxEXPAND);
	TechTrees_Units_Holder_LocationInAge->Add(TechTrees_Units_Unknown3, 0, wxEXPAND);
	TechTrees_Units_Holder_RequiredResearch->Add(TechTrees_Units_Text_RequiredResearch, 0, wxEXPAND);
	TechTrees_Units_Holder_RequiredResearch->Add(TechTrees_Units_RequiredResearch, 0, wxEXPAND);
	TechTrees_Units_Holder_RequiredResearch->Add(TechTrees_Units_ComboBox_RequiredResearch, 0, wxEXPAND);
	TechTrees_Units_Holder_LineMode->Add(TechTrees_Units_Text_LineMode, 0, wxEXPAND);
	TechTrees_Units_Holder_LineMode->Add(TechTrees_Units_LineMode, 0, wxEXPAND);
	TechTrees_Units_Holder_EnablingResearch->Add(TechTrees_Units_Text_EnablingResearch, 0, wxEXPAND);
	TechTrees_Units_Holder_EnablingResearch->Add(TechTrees_Units_EnablingResearch, 0, wxEXPAND);
	TechTrees_Units_Holder_EnablingResearch->Add(TechTrees_Units_ComboBox_EnablingResearch, 0, wxEXPAND);
	TechTrees_Units_Holder_Always2->Add(TechTrees_Units_Text_Always2, 0, wxEXPAND);
	TechTrees_Units_Holder_Always2->Add(TechTrees_Units_Always2, 0, wxEXPAND);
	TechTrees_Units_Holder_RequiredResearches->Add(TechTrees_Units_Text_RequiredResearches, 0, wxEXPAND);
	TechTrees_Units_Holder_RequiredResearches->Add(TechTrees_Units_RequiredResearches, 0, wxEXPAND);
	TechTrees_Units_Holder_Age->Add(TechTrees_Units_Text_Age, 0, wxEXPAND);
	TechTrees_Units_Holder_Age->Add(TechTrees_Units_Age, 0, wxEXPAND);
	TechTrees_Holder_UnitAndResearch3->Add(TechTrees_ComboBox_Unit[2], 1, wxEXPAND);
	TechTrees_Holder_UnitAndResearch3->Add(TechTrees_ComboBox_Research[2], 1, wxEXPAND);
	TechTrees_Holder_UnitAndResearch4->Add(TechTrees_ComboBox_Unit[3], 1, wxEXPAND);
	TechTrees_Holder_UnitAndResearch4->Add(TechTrees_ComboBox_Research[3], 1, wxEXPAND);
	TechTrees_Units_Holder_UnitOrResearch1->Add(TechTrees_Units_Text_UnitOrResearch1, 0, wxEXPAND);
	TechTrees_Units_Holder_UnitOrResearch1->Add(TechTrees_Units_UnitOrResearch1, 0, wxEXPAND);
	TechTrees_Units_Holder_UnitOrResearch1->Add(TechTrees_Holder_UnitAndResearch3, 1, wxEXPAND);
	TechTrees_Units_Holder_UnitOrResearch2->Add(TechTrees_Units_Text_UnitOrResearch2, 0, wxEXPAND);
	TechTrees_Units_Holder_UnitOrResearch2->Add(TechTrees_Units_UnitOrResearch2, 0, wxEXPAND);
	TechTrees_Units_Holder_UnitOrResearch2->Add(TechTrees_Holder_UnitAndResearch4, 1, wxEXPAND);
	TechTrees_Units_Holder_Mode1->Add(TechTrees_Units_Text_Mode1, 0, wxEXPAND);
	TechTrees_Units_Holder_Mode1->Add(TechTrees_Units_Mode1, 0, wxEXPAND);
	TechTrees_Units_Holder_Mode1->Add(TechTrees_ComboBox_Modes[2], 0, wxEXPAND);
	TechTrees_Units_Holder_Mode2->Add(TechTrees_Units_Text_Mode2, 0, wxEXPAND);
	TechTrees_Units_Holder_Mode2->Add(TechTrees_Units_Mode2, 0, wxEXPAND);
	TechTrees_Units_Holder_Mode2->Add(TechTrees_ComboBox_Modes[3], 0, wxEXPAND);
	TechTrees_Units_Holder_VerticalLine->Add(TechTrees_Units_Text_VerticalLine, 0, wxEXPAND);
	TechTrees_Units_Holder_VerticalLine->Add(TechTrees_Units_VerticalLine, 0, wxEXPAND);
	
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_ID, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_UpperBuilding, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_Age, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_LocationInAge, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_LineMode, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_UnitOrResearch1, 1, wxEXPAND);	
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_UnitOrResearch2, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_Mode1, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_Mode2, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_VerticalLine, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_RequiredResearches, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_EnablingResearch, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_RequiredResearch, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Holder_Always2, 1, wxEXPAND);
	
	for(short loop = 0;loop < 8;loop++)
	TechTrees_Units_Grid_Unknown2a1->Add(TechTrees_Units_Unknown2a1[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 10;loop++)
	TechTrees_Units_Grid_Unknown2a2->Add(TechTrees_Units_Unknown2a2[loop], 1, wxEXPAND);
	TechTrees_Units_Holder_Unknown2a->Add(TechTrees_Units_Text_Unknown2a, 0, wxEXPAND);
	TechTrees_Units_Holder_Unknown2a->Add(TechTrees_Units_Grid_Unknown2a1, 0, wxEXPAND);
	TechTrees_Units_Holder_Unknown2a->Add(TechTrees_Units_Grid_Unknown2a2, 0, wxEXPAND);
	
	for(short loop = 0;loop < 7;loop++)
	TechTrees_Units_Grid_Unknown2b1->Add(TechTrees_Units_Unknown2b1[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 10;loop++)
	TechTrees_Units_Grid_Unknown2b2->Add(TechTrees_Units_Unknown2b2[loop], 1, wxEXPAND);
	TechTrees_Units_Holder_Unknown2b->Add(TechTrees_Units_Text_Unknown2b, 0, wxEXPAND);
	TechTrees_Units_Holder_Unknown2b->Add(TechTrees_Units_Grid_Unknown2b1, 0, wxEXPAND);
	TechTrees_Units_Holder_Unknown2b->Add(TechTrees_Units_Grid_Unknown2b2, 0, wxEXPAND);
	
	TechTrees_Data_Units->Add(TechTrees_Data_Units1, 0, wxEXPAND);
	TechTrees_Data_Units->Add(-1, 5);
	TechTrees_Data_Units->Add(TechTrees_DataListHolder_Units, 0, wxEXPAND);
	TechTrees_Data_Units->Add(-1, 5);
	TechTrees_Data_Units->Add(TechTrees_Units_Holder_Unknown2a, 0, wxEXPAND);
	TechTrees_Data_Units->Add(-1, 5);
	TechTrees_Data_Units->Add(TechTrees_Units_Holder_Unknown2b, 0, wxEXPAND);
	
	TechTrees_DataListHolder_Researches->Add(TechTrees_DataList_Researches_Buildings, 1, wxEXPAND);
	TechTrees_DataListHolder_Researches->Add(10, -1);
	TechTrees_DataListHolder_Researches->Add(TechTrees_DataList_Researches_Units, 1, wxEXPAND);
	TechTrees_DataListHolder_Researches->Add(10, -1);
	TechTrees_DataListHolder_Researches->Add(TechTrees_DataList_Researches_Researches, 1, wxEXPAND);
	
	TechTrees_Researches_Holder_ID->Add(TechTrees_Researches_Text_ID, 0, wxEXPAND);
	TechTrees_Researches_Holder_ID->Add(TechTrees_Researches_ID, 0, wxEXPAND);
	TechTrees_Researches_Holder_ID->Add(TechTrees_Researches_ComboBox_ID, 0, wxEXPAND);
	TechTrees_Researches_Holder_UpperBuilding->Add(TechTrees_Researches_Text_UpperBuilding, 0, wxEXPAND);
	TechTrees_Researches_Holder_UpperBuilding->Add(TechTrees_Researches_UpperBuilding, 0, wxEXPAND);
	TechTrees_Researches_Holder_UpperBuilding->Add(TechTrees_Researches_ComboBox_UpperBuilding, 0, wxEXPAND);
	TechTrees_Researches_Holder_UpperResearch->Add(TechTrees_Researches_Text_UpperResearch, 0, wxEXPAND);
	TechTrees_Researches_Holder_UpperResearch->Add(TechTrees_Researches_UpperResearch, 0, wxEXPAND);
	TechTrees_Researches_Holder_UpperResearch->Add(TechTrees_Researches_ComboBox_UpperResearch, 0, wxEXPAND);
	TechTrees_Researches_Holder_Always2->Add(TechTrees_Researches_Text_Always2, 0, wxEXPAND);
	TechTrees_Researches_Holder_Always2->Add(TechTrees_Researches_Always2, 0, wxEXPAND);
	TechTrees_Researches_Holder_RequiredResearches->Add(TechTrees_Researches_Text_RequiredResearches, 0, wxEXPAND);
	TechTrees_Researches_Holder_RequiredResearches->Add(TechTrees_Researches_RequiredResearches, 0, wxEXPAND);
	TechTrees_Researches_Holder_Age->Add(TechTrees_Researches_Text_Age, 0, wxEXPAND);
	TechTrees_Researches_Holder_Age->Add(TechTrees_Researches_Age, 0, wxEXPAND);
	TechTrees_Researches_Holder_LineMode->Add(TechTrees_Researches_Text_LineMode, 0, wxEXPAND);
	TechTrees_Researches_Holder_LineMode->Add(TechTrees_Researches_LineMode, 0, wxEXPAND);
	TechTrees_Researches_Holder_VerticalLine->Add(TechTrees_Researches_Text_VerticalLine, 0, wxEXPAND);
	TechTrees_Researches_Holder_VerticalLine->Add(TechTrees_Researches_VerticalLine, 0, wxEXPAND);
	TechTrees_Researches_Holder_LocationInAge->Add(TechTrees_Researches_Text_LocationInAge, 0, wxEXPAND);
	TechTrees_Researches_Holder_LocationInAge->Add(TechTrees_Researches_LocationInAge, 0, wxEXPAND);
	TechTrees_Researches_Holder_Unknown9->Add(TechTrees_Researches_Text_Unknown9, 0, wxEXPAND);
	TechTrees_Researches_Holder_Unknown9->Add(TechTrees_Researches_Unknown9, 0, wxEXPAND);
	
	TechTrees_Data_Researches1->Add(TechTrees_Researches_Holder_ID, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_Holder_UpperResearch, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_Holder_UpperBuilding, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_Holder_Age, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_Holder_LocationInAge, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_Holder_RequiredResearches, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_Holder_LineMode, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_Holder_VerticalLine, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_Holder_Unknown9, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_Holder_Always2, 1, wxEXPAND);
	
	for(short loop = 0;loop < 9;loop++)
	TechTrees_Researches_Grid_Unknown2a1->Add(TechTrees_Researches_Unknown2a1[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 10;loop++)
	TechTrees_Researches_Grid_Unknown2a2->Add(TechTrees_Researches_Unknown2a2[loop], 1, wxEXPAND);
	TechTrees_Researches_Holder_Unknown2a->Add(TechTrees_Researches_Text_Unknown2a, 0, wxEXPAND);
	TechTrees_Researches_Holder_Unknown2a->Add(TechTrees_Researches_Grid_Unknown2a1, 0, wxEXPAND);
	TechTrees_Researches_Holder_Unknown2a->Add(TechTrees_Researches_Grid_Unknown2a2, 0, wxEXPAND);
	
	for(short loop = 0;loop < 8;loop++)
	TechTrees_Researches_Grid_Unknown2b1->Add(TechTrees_Researches_Unknown2b1[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 10;loop++)
	TechTrees_Researches_Grid_Unknown2b2->Add(TechTrees_Researches_Unknown2b2[loop], 1, wxEXPAND);
	TechTrees_Researches_Holder_Unknown2b->Add(TechTrees_Researches_Text_Unknown2b, 0, wxEXPAND);
	TechTrees_Researches_Holder_Unknown2b->Add(TechTrees_Researches_Grid_Unknown2b1, 0, wxEXPAND);
	TechTrees_Researches_Holder_Unknown2b->Add(TechTrees_Researches_Grid_Unknown2b2, 0, wxEXPAND);
	
	TechTrees_Data_Researches->Add(TechTrees_Data_Researches1, 0, wxEXPAND);
	TechTrees_Data_Researches->Add(-1, 5);
	TechTrees_Data_Researches->Add(TechTrees_DataListHolder_Researches, 0, wxEXPAND);
	TechTrees_Data_Researches->Add(-1, 5);
	TechTrees_Data_Researches->Add(TechTrees_Researches_Holder_Unknown2a, 0, wxEXPAND);
	TechTrees_Data_Researches->Add(-1, 5);
	TechTrees_Data_Researches->Add(TechTrees_Researches_Holder_Unknown2b, 0, wxEXPAND);
	
	TechTrees_Ages->Add(TechTrees_MainList_Ages, 1, wxEXPAND);
	TechTrees_Ages->Add(10, -1);
	TechTrees_Ages->Add(TechTrees_Data_Ages, 3, wxEXPAND);
//	TechTrees_Ages->AddStretchSpacer(3);
	
	TechTrees_Buildings->Add(TechTrees_MainList_Buildings, 1, wxEXPAND);
	TechTrees_Buildings->Add(10, -1);
	TechTrees_Buildings->Add(TechTrees_Data_Buildings, 3, wxEXPAND);
//	TechTrees_Buildings->AddStretchSpacer(3);
	
	TechTrees_Units->Add(TechTrees_MainList_Units, 1, wxEXPAND);
	TechTrees_Units->Add(10, -1);
	TechTrees_Units->Add(TechTrees_Data_Units, 3, wxEXPAND);
//	TechTrees_Units->AddStretchSpacer(3);
	
	TechTrees_Researches->Add(TechTrees_MainList_Researches, 1, wxEXPAND);
	TechTrees_Researches->Add(10, -1);
	TechTrees_Researches->Add(TechTrees_Data_Researches, 3, wxEXPAND);
//	TechTrees_Researches->AddStretchSpacer(3);

	TechTrees_ScrollerWindowsSpace->Add(TechTrees_Ages, 0, wxEXPAND);
	TechTrees_ScrollerWindowsSpace->Add(-1, 5);
	TechTrees_ScrollerWindowsSpace->Add(TechTrees_Buildings, 0, wxEXPAND);
	TechTrees_ScrollerWindowsSpace->Add(-1, 5);
	TechTrees_ScrollerWindowsSpace->Add(TechTrees_Units, 0, wxEXPAND);
	TechTrees_ScrollerWindowsSpace->Add(-1, 5);
	TechTrees_ScrollerWindowsSpace->Add(TechTrees_Researches, 0, wxEXPAND);
	
	TechTrees_ScrollerWindows->Add(TechTrees_ScrollerWindowsSpace, 1, wxEXPAND);
	TechTrees_ScrollerWindows->Add(5, -1);

	TechTrees_Scroller->SetSizer(TechTrees_ScrollerWindows);
	TechTrees_Scroller->SetScrollRate(0, 15);

	TechTrees_All->Add(-1, 10);
	TechTrees_All->Add(TechTrees_Scroller, 1, wxEXPAND);
	TechTrees_All->Add(-1, 10);

	TechTrees_Main->Add(10, -1);
	TechTrees_Main->Add(TechTrees_All, 1, wxEXPAND);
	TechTrees_Main->Add(10, -1);
	
	for(short loop = 0;loop < 4;loop++)
	{
		TechTrees_ComboBox_Unit[loop]->Show(false);
		TechTrees_ComboBox_Research[loop]->Show(false);
	}
	
	Tab_TechTrees->SetSizer(TechTrees_Main);
	
	Connect(TechTrees_MainList_Ages_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesSearch));
	Connect(TechTrees_MainList_Ages_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesSearch));
	Connect(TechTrees_MainList_Ages_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesSelect));
	Connect(TechTrees_MainList_Ages_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesAdd));
	Connect(TechTrees_MainList_Ages_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesDelete));
	Connect(TechTrees_MainList_Ages_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesCopy));
	Connect(TechTrees_MainList_Ages_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesPaste));
	Connect(TechTrees_MainList_Buildings_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSearch));
	Connect(TechTrees_MainList_Buildings_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSearch));
	Connect(TechTrees_MainList_Buildings_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSelect));
	Connect(TechTrees_MainList_Buildings_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingAdd));
	Connect(TechTrees_MainList_Buildings_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingDelete));
	Connect(TechTrees_MainList_Buildings_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingCopy));
	Connect(TechTrees_MainList_Buildings_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingPaste));
	Connect(TechTrees_MainList_Units_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTUnitSearch));
	Connect(TechTrees_MainList_Units_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTUnitSearch));
	for(short loop = 0;loop < 2;loop++)
	{
		Connect(TechTrees_MainList_Buildings_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSearch));
		Connect(TechTrees_MainList_Units_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitSearch));
		Connect(TechTrees_MainList_Researches_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchSearch));
		Connect(TechTrees_MainList_Buildings_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_ComboBoxes));
		Connect(TechTrees_MainList_Units_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_ComboBoxes));
		Connect(TechTrees_MainList_Researches_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_ComboBoxes));
	}
	Connect(TechTrees_MainList_Units_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTUnitSelect));
	Connect(TechTrees_MainList_Units_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitAdd));
	Connect(TechTrees_MainList_Units_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitDelete));
	Connect(TechTrees_MainList_Units_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitCopy));
	Connect(TechTrees_MainList_Units_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitPaste));
	Connect(TechTrees_MainList_Researches_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchSearch));
	Connect(TechTrees_MainList_Researches_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchSearch));
	Connect(TechTrees_MainList_Researches_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchSelect));
	Connect(TechTrees_MainList_Researches_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchAdd));
	Connect(TechTrees_MainList_Researches_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchDelete));
	Connect(TechTrees_MainList_Researches_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchCopy));
	Connect(TechTrees_MainList_Researches_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchPaste));
	
	Connect(TechTrees_DataList_Ages_Search_Buildings->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingSearch));
	Connect(TechTrees_DataList_Ages_Search_Units->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitSearch));
	Connect(TechTrees_DataList_Ages_Search_Researches->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchSearch));
	Connect(TechTrees_DataList_Ages_Search_R_Buildings->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingSearch));
	Connect(TechTrees_DataList_Ages_Search_R_Units->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitSearch));
	Connect(TechTrees_DataList_Ages_Search_R_Researches->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchSearch));
	Connect(TechTrees_DataList_Ages_List_Buildings->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingSelect));
	Connect(TechTrees_DataList_Ages_List_Units->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitSelect));
	Connect(TechTrees_DataList_Ages_List_Researches->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchSelect));
	Connect(TechTrees_DataList_Ages_Add_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingAdd));
	Connect(TechTrees_DataList_Ages_Add_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitAdd));
	Connect(TechTrees_DataList_Ages_Add_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchAdd));
	Connect(TechTrees_DataList_Ages_Delete_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingDelete));
	Connect(TechTrees_DataList_Ages_Delete_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitDelete));
	Connect(TechTrees_DataList_Ages_Delete_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchDelete));
	Connect(TechTrees_DataList_Ages_Copy_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingCopy));
	Connect(TechTrees_DataList_Ages_Copy_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitCopy));
	Connect(TechTrees_DataList_Ages_Copy_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchCopy));
	Connect(TechTrees_DataList_Ages_Paste_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingPaste));
	Connect(TechTrees_DataList_Ages_Paste_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitPaste));
	Connect(TechTrees_DataList_Ages_Paste_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchPaste));
	Connect(TechTrees_DataList_Buildings_Search_Buildings->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingSearch));
	Connect(TechTrees_DataList_Buildings_Search_Units->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitSearch));
	Connect(TechTrees_DataList_Buildings_Search_Researches->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchSearch));
	Connect(TechTrees_DataList_Buildings_Search_R_Buildings->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingSearch));
	Connect(TechTrees_DataList_Buildings_Search_R_Units->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitSearch));
	Connect(TechTrees_DataList_Buildings_Search_R_Researches->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchSearch));
	Connect(TechTrees_DataList_Buildings_List_Buildings->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingSelect));
	Connect(TechTrees_DataList_Buildings_List_Units->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitSelect));
	Connect(TechTrees_DataList_Buildings_List_Researches->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchSelect));
	Connect(TechTrees_DataList_Buildings_Add_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingAdd));
	Connect(TechTrees_DataList_Buildings_Add_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitAdd));
	Connect(TechTrees_DataList_Buildings_Add_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchAdd));
	Connect(TechTrees_DataList_Buildings_Delete_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingDelete));
	Connect(TechTrees_DataList_Buildings_Delete_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitDelete));
	Connect(TechTrees_DataList_Buildings_Delete_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchDelete));
	Connect(TechTrees_DataList_Buildings_Copy_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingCopy));
	Connect(TechTrees_DataList_Buildings_Copy_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitCopy));
	Connect(TechTrees_DataList_Buildings_Copy_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchCopy));
	Connect(TechTrees_DataList_Buildings_Paste_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingPaste));
	Connect(TechTrees_DataList_Buildings_Paste_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitPaste));
	Connect(TechTrees_DataList_Buildings_Paste_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchPaste));
	Connect(TechTrees_DataList_Units_Search_Units->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitSearch));
	Connect(TechTrees_DataList_Units_Search_R_Units->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitSearch));
	Connect(TechTrees_DataList_Units_List_Units->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitSelect));
	Connect(TechTrees_DataList_Units_Add_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitAdd));
	Connect(TechTrees_DataList_Units_Delete_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitDelete));
	Connect(TechTrees_DataList_Units_Copy_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitCopy));
	Connect(TechTrees_DataList_Units_Paste_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitPaste));
	Connect(TechTrees_DataList_Researches_Search_Buildings->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingSearch));
	Connect(TechTrees_DataList_Researches_Search_Units->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitSearch));
	Connect(TechTrees_DataList_Researches_Search_Researches->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchSearch));
	Connect(TechTrees_DataList_Researches_Search_R_Buildings->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingSearch));
	Connect(TechTrees_DataList_Researches_Search_R_Units->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitSearch));
	Connect(TechTrees_DataList_Researches_Search_R_Researches->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchSearch));
	Connect(TechTrees_DataList_Researches_List_Buildings->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingSelect));
	Connect(TechTrees_DataList_Researches_List_Units->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitSelect));
	Connect(TechTrees_DataList_Researches_List_Researches->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchSelect));
	Connect(TechTrees_DataList_Researches_Add_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingAdd));
	Connect(TechTrees_DataList_Researches_Add_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitAdd));
	Connect(TechTrees_DataList_Researches_Add_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchAdd));
	Connect(TechTrees_DataList_Researches_Delete_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingDelete));
	Connect(TechTrees_DataList_Researches_Delete_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitDelete));
	Connect(TechTrees_DataList_Researches_Delete_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchDelete));
	Connect(TechTrees_DataList_Researches_Copy_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingCopy));
	Connect(TechTrees_DataList_Researches_Copy_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitCopy));
	Connect(TechTrees_DataList_Researches_Copy_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchCopy));
	Connect(TechTrees_DataList_Researches_Paste_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingPaste));
	Connect(TechTrees_DataList_Researches_Paste_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitPaste));
	Connect(TechTrees_DataList_Researches_Paste_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchPaste));

	TechTrees_Ages_ID->Connect(TechTrees_Ages_ID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Long), NULL, this);
	TechTrees_Ages_Building->Connect(TechTrees_Ages_Building->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Ages_Unit->Connect(TechTrees_Ages_Unit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Ages_Research->Connect(TechTrees_Ages_Research->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Ages_ComboBox_Building->Connect(TechTrees_Ages_ComboBox_Building->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	TechTrees_Ages_ComboBox_Unit->Connect(TechTrees_Ages_ComboBox_Unit->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	TechTrees_Ages_ComboBox_Research->Connect(TechTrees_Ages_ComboBox_Research->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	
	TechTrees_Buildings_ID->Connect(TechTrees_Buildings_ID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Buildings_Building->Connect(TechTrees_Buildings_Building->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Buildings_Unit->Connect(TechTrees_Buildings_Unit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Buildings_Research->Connect(TechTrees_Buildings_Research->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Units_ID->Connect(TechTrees_Units_ID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Units_Unit->Connect(TechTrees_Units_Unit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Researches_ID->Connect(TechTrees_Researches_ID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Researches_Building->Connect(TechTrees_Researches_Building->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Researches_Unit->Connect(TechTrees_Researches_Unit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Researches_Research->Connect(TechTrees_Researches_Research->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Buildings_UnitOrResearch1->Connect(TechTrees_Buildings_UnitOrResearch1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Buildings_UnitOrResearch2->Connect(TechTrees_Buildings_UnitOrResearch2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Units_UnitOrResearch1->Connect(TechTrees_Units_UnitOrResearch1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Units_UnitOrResearch2->Connect(TechTrees_Units_UnitOrResearch2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxLong), NULL, this);
	TechTrees_Buildings_ComboBox_ID->Connect(TechTrees_Buildings_ComboBox_ID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	TechTrees_Buildings_ComboBox_Building->Connect(TechTrees_Buildings_ComboBox_Building->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	TechTrees_Buildings_ComboBox_Unit->Connect(TechTrees_Buildings_ComboBox_Unit->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	TechTrees_Buildings_ComboBox_Research->Connect(TechTrees_Buildings_ComboBox_Research->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	TechTrees_Units_ComboBox_ID->Connect(TechTrees_Units_ComboBox_ID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	TechTrees_Units_ComboBox_Unit->Connect(TechTrees_Units_ComboBox_Unit->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	TechTrees_Researches_ComboBox_ID->Connect(TechTrees_Researches_ComboBox_ID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	TechTrees_Researches_ComboBox_Building->Connect(TechTrees_Researches_ComboBox_Building->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	TechTrees_Researches_ComboBox_Unit->Connect(TechTrees_Researches_ComboBox_Unit->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	TechTrees_Researches_ComboBox_Research->Connect(TechTrees_Researches_ComboBox_Research->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxLong), NULL, this);
	
	TechTrees_Buildings_Mode1->Connect(TechTrees_Buildings_Mode1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Long), NULL, this);
	TechTrees_Buildings_Mode2->Connect(TechTrees_Buildings_Mode2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Long), NULL, this);
	TechTrees_Units_Mode1->Connect(TechTrees_Units_Mode1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Long), NULL, this);
	TechTrees_Units_Mode2->Connect(TechTrees_Units_Mode2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Long), NULL, this);
	for(short loop = 0;loop < 4;loop++)
	Connect(TechTrees_ComboBox_Modes[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_ComboBoxes));

}
