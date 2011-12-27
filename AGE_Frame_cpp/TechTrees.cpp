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
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetTTAgesName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTAgesName(loop)).Lower();
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
	/*	UnitLines_ID->ChangeValue(lexical_cast<string>(AgePointer->ID));
		UnitLines_ID->Container = &AgePointer->ID;
		UnitLines_Name->ChangeValue(AgePointer->Name);
		UnitLines_Name->Container = &AgePointer->Name;*/
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
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTAgesBuildingName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Name = lexical_cast<string>(loop);
			Name += " - ";
			Name += GetTTAgesBuildingName(loop, Index);
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
	/*	UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*BuildingPointer));
		UnitLineUnits_Units->Container = BuildingPointer;
		UnitLineUnits_ComboBox_Units->SetSelection(*BuildingPointer + 1);
	*/	Added = false;
	}
	else
	{/*
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	*/}
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
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTAgesUnitName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Name = lexical_cast<string>(loop);
			Name += " - ";
			Name += GetTTAgesUnitName(loop, Index);
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
	/*	UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*UnitPointer));
		UnitLineUnits_Units->Container = UnitPointer;
		UnitLineUnits_ComboBox_Units->SetSelection(*UnitPointer + 1);
	*/	Added = false;
	}
	else
	{/*
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	*/}
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
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTAgesResearchName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Name = lexical_cast<string>(loop);
			Name += " - ";
			Name += GetTTAgesResearchName(loop, Index);
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
	/*	UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*ResearchPointer));
		UnitLineUnits_Units->Container = ResearchPointer;
		UnitLineUnits_ComboBox_Units->SetSelection(*ResearchPointer + 1);
	*/	Added = false;
	}
	else
	{/*
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	*/}
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
	Name = lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].ID)+" ";
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
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetTTBuildingName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTBuildingName(loop)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_MainList_Buildings_List->Append(Name, (void*)&GenieFile->TechTree.BuildingConnections[loop]);
		}
	}
	
	TechTrees_MainList_Buildings_List->SetSelection(0);
	TechTrees_MainList_Buildings_List->SetFirstItem(Selection - 3);
	TechTrees_MainList_Buildings_List->SetSelection(Selection);
	
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
	/*	UnitLines_ID->ChangeValue(lexical_cast<string>(BuildingConnectionPointer->ID));
		UnitLines_ID->Container = &BuildingConnectionPointer->ID;
		UnitLines_Name->ChangeValue(BuildingConnectionPointer->Name);
		UnitLines_Name->Container = &BuildingConnectionPointer->Name;*/
		Added = false;
		ListTTBuildingBuildings(TTBuildingConnectionID);
		ListTTBuildingUnits(TTBuildingConnectionID);
		ListTTBuildingResearches(TTBuildingConnectionID);
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
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTBuildingBuildingName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Name = lexical_cast<string>(loop);
			Name += " - ";
			Name += GetTTBuildingBuildingName(loop, Index);
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
	/*	UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*BuildingPointer));
		UnitLineUnits_Units->Container = BuildingPointer;
		UnitLineUnits_ComboBox_Units->SetSelection(*BuildingPointer + 1);
	*/	Added = false;
	}
	else
	{/*
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	*/}
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
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTBuildingUnitName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Name = lexical_cast<string>(loop);
			Name += " - ";
			Name += GetTTBuildingUnitName(loop, Index);
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
	/*	UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*UnitPointer));
		UnitLineUnits_Units->Container = UnitPointer;
		UnitLineUnits_ComboBox_Units->SetSelection(*UnitPointer + 1);
	*/	Added = false;
	}
	else
	{/*
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	*/}
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
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTBuildingResearchName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Name = lexical_cast<string>(loop);
			Name += " - ";
			Name += GetTTBuildingResearchName(loop, Index);
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
	/*	UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*ResearchPointer));
		UnitLineUnits_Units->Container = ResearchPointer;
		UnitLineUnits_ComboBox_Units->SetSelection(*ResearchPointer + 1);
	*/	Added = false;
	}
	else
	{/*
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	*/}
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
	Name = lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].ID)+" ";
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
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetTTUnitName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTUnitName(loop)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_MainList_Units_List->Append(Name, (void*)&GenieFile->TechTree.UnitConnections[loop]);
		}
	}
	
	TechTrees_MainList_Units_List->SetSelection(0);
	TechTrees_MainList_Units_List->SetFirstItem(Selection - 3);
	TechTrees_MainList_Units_List->SetSelection(Selection);
	
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
	/*	UnitLines_ID->ChangeValue(lexical_cast<string>(UnitConnectionPointer->ID));
		UnitLines_ID->Container = &UnitConnectionPointer->ID;
		UnitLines_Name->ChangeValue(UnitConnectionPointer->Name);
		UnitLines_Name->Container = &UnitConnectionPointer->Name;*/
		Added = false;
		ListTTUnitUnits(TTUnitConnectionID);
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
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTUnitUnitName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Name = lexical_cast<string>(loop);
			Name += " - ";
			Name += GetTTUnitUnitName(loop, Index);
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
	/*	UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*UnitPointer));
		UnitLineUnits_Units->Container = UnitPointer;
		UnitLineUnits_ComboBox_Units->SetSelection(*UnitPointer + 1);
	*/	Added = false;
	}
	else
	{/*
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	*/}
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
	Name = lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].ID)+" ";
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
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetTTResearchName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTResearchName(loop)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			TechTrees_MainList_Researches_List->Append(Name, (void*)&GenieFile->TechTree.ResearchConnections[loop]);
		}
	}
	
	TechTrees_MainList_Researches_List->SetSelection(0);
	TechTrees_MainList_Researches_List->SetFirstItem(Selection - 3);
	TechTrees_MainList_Researches_List->SetSelection(Selection);
	
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
	/*	UnitLines_ID->ChangeValue(lexical_cast<string>(ResearchConnectionPointer->ID));
		UnitLines_ID->Container = &ResearchConnectionPointer->ID;
		UnitLines_Name->ChangeValue(ResearchConnectionPointer->Name);
		UnitLines_Name->Container = &ResearchConnectionPointer->Name;*/
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
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTResearchBuildingName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Name = lexical_cast<string>(loop);
			Name += " - ";
			Name += GetTTResearchBuildingName(loop, Index);
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
	/*	UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*BuildingPointer));
		UnitLineUnits_Units->Container = BuildingPointer;
		UnitLineUnits_ComboBox_Units->SetSelection(*BuildingPointer + 1);
	*/	Added = false;
	}
	else
	{/*
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	*/}
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
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTResearchUnitName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Name = lexical_cast<string>(loop);
			Name += " - ";
			Name += GetTTResearchUnitName(loop, Index);
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
	/*	UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*UnitPointer));
		UnitLineUnits_Units->Container = UnitPointer;
		UnitLineUnits_ComboBox_Units->SetSelection(*UnitPointer + 1);
	*/	Added = false;
	}
	else
	{/*
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	*/}
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
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTTResearchResearchName(loop, Index)).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Name = lexical_cast<string>(loop);
			Name += " - ";
			Name += GetTTResearchResearchName(loop, Index);
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
	/*	UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*ResearchPointer));
		UnitLineUnits_Units->Container = ResearchPointer;
		UnitLineUnits_ComboBox_Units->SetSelection(*ResearchPointer + 1);
	*/	Added = false;
	}
	else
	{/*
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	*/}
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
	TechTrees_MainList_Ages_List = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
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
	
	TechTrees_Data_Ages = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Data_Buildings = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Data_Units = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Data_Researches = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_DataList_Ages_Buildings = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Con. Buildings");
	TechTrees_DataList_Ages_Units = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Con. Units");
	TechTrees_DataList_Ages_Researches = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Con. Researches");
	TechTrees_DataList_Buildings_Buildings = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Con. Buildings");
	TechTrees_DataList_Buildings_Units = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Con. Units");
	TechTrees_DataList_Buildings_Researches = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Con. Researches");
	TechTrees_DataList_Units_Units = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Con. Units");
	TechTrees_DataList_Researches_Buildings = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Con. Buildings");
	TechTrees_DataList_Researches_Units = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Con. Units");
	TechTrees_DataList_Researches_Researches = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Con. Researches");
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
	
/*	TechTrees_ListArea = new wxBoxSizer(wxVERTICAL);
	TechTrees_TechTrees_Buttons = new wxGridSizer(2, 0, 0);
	Effects_DataArea = new wxBoxSizer(wxVERTICAL);
	Effects_ListArea = new wxBoxSizer(wxVERTICAL);
	TechTrees_Effects_Buttons = new wxGridSizer(2, 0, 0);
	Effects_DataAreaProperties = new wxBoxSizer(wxVERTICAL);
	TechTrees_Techs = new wxStaticBoxSizer(wxVERTICAL, Tab_Techage, "Technologies");
	TechTrees_TechTrees_Search = new wxTextCtrl(Tab_Techage, wxID_ANY);
	TechTrees_TechTrees_Search_R = new wxTextCtrl(Tab_Techage, wxID_ANY);
	TechTrees_TechTrees_List = new wxListBox(Tab_Techage, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_TechTrees_Add = new wxButton(Tab_Techage, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_TechTrees_Delete = new wxButton(Tab_Techage, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_TechTrees_Copy = new wxButton(Tab_Techage, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_TechTrees_Paste = new wxButton(Tab_Techage, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_TechTrees_Rename = new wxButton(Tab_Techage, wxID_ANY, "Rename Technologies", wxDefaultPosition, wxSize(0, 20));
	TechTrees_TechTrees_Restore = new wxButton(Tab_Techage, wxID_ANY, "Rename for GeniEd 2", wxDefaultPosition, wxSize(0, 20));

	TechTrees_Holder_Name = new wxBoxSizer(wxVERTICAL);
	TechTrees_Text_Name = new wxStaticText(Tab_Techage, wxID_ANY, " Technology Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Name = new TextCtrl_String(Tab_Techage, "0", NULL);

	TechTrees_Effects = new wxStaticBoxSizer(wxVERTICAL, Tab_Techage, "Effects");
	TechTrees_Effects_Search = new wxTextCtrl(Tab_Techage, wxID_ANY);
	TechTrees_Effects_Search_R = new wxTextCtrl(Tab_Techage, wxID_ANY);
	TechTrees_Effects_UseAnd = new wxCheckBox(Tab_Techage, wxID_ANY, "Use AND instead of OR", wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator);
	TechTrees_Effects_List = new wxListBox(Tab_Techage, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	TechTrees_Effects_Add = new wxButton(Tab_Techage, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_Effects_Delete = new wxButton(Tab_Techage, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_Effects_Copy = new wxButton(Tab_Techage, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_Effects_Paste = new wxButton(Tab_Techage, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));

	Effects_Holder_Type = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_Type2 = new wxBoxSizer(wxHORIZONTAL);
	Effects_Text_Type = new wxStaticText(Tab_Techage, wxID_ANY, " Effect Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Type = new TextCtrl_Byte(Tab_Techage, "0", NULL);
	Effects_ComboBox_Type = new ComboBox_Byte_EffectType(Tab_Techage, Effects_Type);
	Effects_Holder_Data = new wxStaticBoxSizer(wxVERTICAL, Tab_Techage, "Effect Attributes");
	Effects_Holder_DataA = new wxBoxSizer(wxHORIZONTAL);
	Effects_Holder_DataB = new wxBoxSizer(wxHORIZONTAL);
	Effects_Holder_DataC = new wxBoxSizer(wxHORIZONTAL);
	Effects_Holder_DataD = new wxBoxSizer(wxHORIZONTAL);
	Effects_Holder_DataE = new wxBoxSizer(wxHORIZONTAL);
	Effects_Holder_DataF = new wxBoxSizer(wxHORIZONTAL);
	Effects_Holder_A = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_B = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_C = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_D = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_E = new wxBoxSizer(wxVERTICAL);
	Effects_Holder_F = new wxBoxSizer(wxVERTICAL);
	Effects_Text_A = new wxStaticText(Tab_Techage, wxID_ANY, "Attribute A ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_A = new TextCtrl_Short(Tab_Techage, "0", NULL);
	Effects_ComboBox_A = new wxBoxSizer(wxHORIZONTAL);
	Effects_ComboBox_UnitsA = new ComboBox_Short(Tab_Techage, Effects_A);
	Effects_ComboBox_ResourcesA = new ComboBox_Short(Tab_Techage, Effects_A);
	Effects_ComboBox_ResearchsA = new ComboBox_Short(Tab_Techage, Effects_A);
	Effects_Info_A = new wxStaticText(Tab_Techage, wxID_ANY, " Info A", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_B = new wxStaticText(Tab_Techage, wxID_ANY, "Attribute B ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_B = new TextCtrl_Short(Tab_Techage, "0", NULL);
	Effects_ComboBox_B = new wxBoxSizer(wxHORIZONTAL);
	Effects_CheckBox_ModeB = new CheckBox_Short(Tab_Techage, "", Effects_B);
	Units_ComboBox_Class[2] = new ComboBox_Short(Tab_Techage, Effects_B);
	Effects_ComboBox_UnitsB = new ComboBox_Short(Tab_Techage, Effects_B);
	Effects_ComboBox_ResourcesB = new ComboBox_Short(Tab_Techage, Effects_B);
	Effects_Info_B = new wxStaticText(Tab_Techage, wxID_ANY, " Info B", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_C = new wxStaticText(Tab_Techage, wxID_ANY, "Attribute C ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_C = new TextCtrl_Short(Tab_Techage, "0", NULL);
	Effects_ComboBox_C = new wxBoxSizer(wxHORIZONTAL);
	Effects_CheckBox_ModeC = new CheckBox_Short(Tab_Techage, "", Effects_C);
	Effects_ComboBox_AttributesC = new ComboBox_Short(Tab_Techage, Effects_C);
	Effects_Info_C = new wxStaticText(Tab_Techage, wxID_ANY, " Info C", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_D = new wxStaticText(Tab_Techage, wxID_ANY, "Attribute D ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_D = new TextCtrl_Float(Tab_Techage, "0", NULL);
	Effects_ComboBox_D = new wxBoxSizer(wxHORIZONTAL);
	Effects_ComboBox_ResearchsD = new ComboBox_Float(Tab_Techage, Effects_D);
	Effects_Info_D = new wxStaticText(Tab_Techage, wxID_ANY, " Info D", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_E = new wxStaticText(Tab_Techage, wxID_ANY, "Amount or % ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_E = new wxTextCtrl(Tab_Techage, wxID_ANY);
	Effects_Info_E = new wxStaticText(Tab_Techage, wxID_ANY, " Attack | Armor", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Text_F = new wxStaticText(Tab_Techage, wxID_ANY, "Class ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Effects_F = new TextCtrl_Short(Tab_Techage, "0", NULL);
	Attacks_ComboBox_Class[2] = new ComboBox_Short_AttackType(Tab_Techage, Effects_F);
	Effects_Info_F = new wxStaticText(Tab_Techage, wxID_ANY, " Attack | Armor", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Effects_Link = new wxHyperlinkCtrl(Tab_Techage, wxID_ANY, "GenieWiki Effect Types", "http://www.digitization.org/wiki/index.php?title=Genie_technology#Effects");
	
	Effects_ComboBox_Type->Append("No Type/Invalid Type");	// Selection 0
	Effects_ComboBox_Type->Append("0 - Attribute Modifier (Set)");	// Selection 1
	Effects_ComboBox_Type->Append("1 - Resource Modifier (Set/+/-)");
	Effects_ComboBox_Type->Append("2 - Enable/Disable Unit");
	Effects_ComboBox_Type->Append("3 - Upgrade Unit");
	Effects_ComboBox_Type->Append("4 - Attribute Modifier (+/-)");
	Effects_ComboBox_Type->Append("5 - Attribute Modifier (Multiply)");
	Effects_ComboBox_Type->Append("6 - Resource Modifier (Multiply)");
	Effects_ComboBox_Type->Append("101 - Research Cost Modifier (Set/+/-)");
	Effects_ComboBox_Type->Append("102 - Disable Research");
	Effects_ComboBox_Type->Append("103 - Research Time Modifier (Set/+/-)");	// Selection 10
	Effects_ComboBox_Type->SetSelection(0);

	TechTrees_TechTrees_Buttons->Add(TechTrees_TechTrees_Add, 1, wxEXPAND);
	TechTrees_TechTrees_Buttons->Add(TechTrees_TechTrees_Delete, 1, wxEXPAND);
	TechTrees_TechTrees_Buttons->Add(TechTrees_TechTrees_Copy, 1, wxEXPAND);
	TechTrees_TechTrees_Buttons->Add(TechTrees_TechTrees_Paste, 1, wxEXPAND);

	TechTrees_Techs->Add(TechTrees_TechTrees_Search, 0, wxEXPAND);
	TechTrees_Techs->Add(TechTrees_TechTrees_Search_R, 0, wxEXPAND);
	TechTrees_Techs->Add(-1, 2);
	TechTrees_Techs->Add(TechTrees_TechTrees_List, 1, wxEXPAND);
	TechTrees_Techs->Add(-1, 2);
	TechTrees_Techs->Add(TechTrees_TechTrees_Buttons, 0, wxEXPAND);

	TechTrees_ListArea->Add(-1, 10);
	TechTrees_ListArea->Add(TechTrees_Techs, 1, wxEXPAND);
	TechTrees_ListArea->Add(-1, 10);

	TechTrees_Effects_Buttons->Add(TechTrees_Effects_Add, 1, wxEXPAND);
	TechTrees_Effects_Buttons->Add(TechTrees_Effects_Delete, 1, wxEXPAND);
	TechTrees_Effects_Buttons->Add(TechTrees_Effects_Copy, 1, wxEXPAND);
	TechTrees_Effects_Buttons->Add(TechTrees_Effects_Paste, 1, wxEXPAND);

	TechTrees_Holder_Name->Add(TechTrees_Text_Name, 0, wxEXPAND);
	TechTrees_Holder_Name->Add(TechTrees_Name, 1, wxEXPAND);
	TechTrees_Holder_Name->Add(TechTrees_TechTrees_Rename, 1, wxEXPAND);
	TechTrees_Holder_Name->Add(TechTrees_TechTrees_Restore, 1, wxEXPAND);

	TechTrees_Effects->Add(TechTrees_Effects_Search, 0, wxEXPAND);
	TechTrees_Effects->Add(TechTrees_Effects_Search_R, 0, wxEXPAND);
	TechTrees_Effects->Add(TechTrees_Effects_UseAnd, 0, wxEXPAND);
	TechTrees_Effects->Add(-1, 2);
	TechTrees_Effects->Add(TechTrees_Effects_List, 1, wxEXPAND);
	TechTrees_Effects->Add(-1, 2);
	TechTrees_Effects->Add(TechTrees_Effects_Buttons, 0, wxEXPAND);

	Effects_ListArea->Add(-1, 10);
	Effects_ListArea->Add(TechTrees_Holder_Name, 0, wxEXPAND);
	Effects_ListArea->Add(-1, 5);
	Effects_ListArea->Add(TechTrees_Effects, 1, wxEXPAND);
	Effects_ListArea->Add(-1, 10);

	Effects_Holder_Type2->Add(Effects_Type, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_Type2->Add(Effects_ComboBox_Type, 2, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_Type->Add(Effects_Text_Type, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_Type->Add(Effects_Holder_Type2, 1, wxEXPAND);
	
	Effects_ComboBox_A->Add(Effects_ComboBox_UnitsA, 1, wxEXPAND);
	Effects_ComboBox_A->Add(Effects_ComboBox_ResourcesA, 1, wxEXPAND);
	Effects_ComboBox_A->Add(Effects_ComboBox_ResearchsA, 1, wxEXPAND);
	Effects_Holder_A->Add(Effects_A, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_A->Add(Effects_ComboBox_A, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Effects_Holder_DataA->Add(Effects_Text_A, 2, wxEXPAND | wxALIGN_CENTRE_VERTICAL);
	Effects_Holder_DataA->Add(Effects_Holder_A, 3, wxEXPAND);
	Effects_Holder_DataA->Add(Effects_Info_A, 3, wxEXPAND);
	
	Effects_ComboBox_B->Add(Effects_CheckBox_ModeB, 1, wxEXPAND);	
	Effects_ComboBox_B->Add(Units_ComboBox_Class[2], 1, wxEXPAND);
	Effects_ComboBox_B->Add(Effects_ComboBox_UnitsB, 1, wxEXPAND);
	Effects_ComboBox_B->Add(Effects_ComboBox_ResourcesB, 1, wxEXPAND);
	Effects_Holder_B->Add(Effects_B, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_B->Add(Effects_ComboBox_B, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Effects_Holder_DataB->Add(Effects_Text_B, 2, wxEXPAND | wxALIGN_CENTRE_VERTICAL);
	Effects_Holder_DataB->Add(Effects_Holder_B, 3, wxEXPAND);
	Effects_Holder_DataB->Add(Effects_Info_B, 3, wxEXPAND);
	
	Effects_ComboBox_C->Add(Effects_CheckBox_ModeC, 1, wxEXPAND);
	Effects_ComboBox_C->Add(Effects_ComboBox_AttributesC, 1, wxEXPAND);
	Effects_Holder_C->Add(Effects_C, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_C->Add(Effects_ComboBox_C, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Effects_Holder_DataC->Add(Effects_Text_C, 2, wxEXPAND | wxALIGN_CENTRE_VERTICAL);
	Effects_Holder_DataC->Add(Effects_Holder_C, 3, wxEXPAND);
	Effects_Holder_DataC->Add(Effects_Info_C, 3, wxEXPAND);
	
	Effects_ComboBox_D->Add(Effects_ComboBox_ResearchsD, 1, wxEXPAND);
	Effects_Holder_D->Add(Effects_D, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_D->Add(Effects_ComboBox_D, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Effects_Holder_DataD->Add(Effects_Text_D, 2, wxEXPAND | wxALIGN_CENTRE_VERTICAL);
	Effects_Holder_DataD->Add(Effects_Holder_D, 3, wxEXPAND);
	Effects_Holder_DataD->Add(Effects_Info_D, 3, wxEXPAND);

	Effects_Holder_E->Add(Effects_E, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Effects_Holder_DataE->Add(Effects_Text_E, 2, wxEXPAND | wxALIGN_CENTRE_VERTICAL);
	Effects_Holder_DataE->Add(Effects_Holder_E, 3, wxEXPAND);
	Effects_Holder_DataE->Add(Effects_Info_E, 3, wxEXPAND);

	Effects_Holder_F->Add(Effects_F, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Effects_Holder_F->Add(Attacks_ComboBox_Class[2], 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Effects_Holder_DataF->Add(Effects_Text_F, 2, wxEXPAND | wxALIGN_CENTRE_VERTICAL);
	Effects_Holder_DataF->Add(Effects_Holder_F, 3, wxEXPAND);
	Effects_Holder_DataF->Add(Effects_Info_F, 3, wxEXPAND);

	Effects_Holder_Data->Add(Effects_Holder_DataA, 0, wxEXPAND);
	Effects_Holder_Data->Add(-1, 5);
	Effects_Holder_Data->Add(Effects_Holder_DataB, 0, wxEXPAND);
	Effects_Holder_Data->Add(-1, 5);
	Effects_Holder_Data->Add(Effects_Holder_DataC, 0, wxEXPAND);
	Effects_Holder_Data->Add(-1, 5);
	Effects_Holder_Data->Add(Effects_Holder_DataD, 0, wxEXPAND);
	Effects_Holder_Data->Add(-1, 5);
	Effects_Holder_Data->Add(Effects_Holder_DataE, 0, wxEXPAND);
	Effects_Holder_Data->Add(Effects_Holder_DataF, 0, wxEXPAND);

	Effects_DataArea->Add(-1, 10);
	Effects_DataArea->Add(Effects_Holder_Type, 0, wxEXPAND);
	Effects_DataArea->Add(-1, 5);
	Effects_DataArea->Add(Effects_Holder_Data, 0, wxEXPAND);
	Effects_DataArea->Add(-1, 5);
	Effects_DataArea->Add(Effects_Link, 0, wxEXPAND);*/

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
	TechTrees_MainList_Buildings->Add(TechTrees_MainList_Buildings_Search, 0, wxEXPAND);
	TechTrees_MainList_Units->Add(TechTrees_MainList_Units_Search, 0, wxEXPAND);
	TechTrees_MainList_Researches->Add(TechTrees_MainList_Researches_Search, 0, wxEXPAND);
	TechTrees_MainList_Ages->Add(TechTrees_MainList_Ages_Search_R, 0, wxEXPAND);
	TechTrees_MainList_Buildings->Add(TechTrees_MainList_Buildings_Search_R, 0, wxEXPAND);
	TechTrees_MainList_Units->Add(TechTrees_MainList_Units_Search_R, 0, wxEXPAND);
	TechTrees_MainList_Researches->Add(TechTrees_MainList_Researches_Search_R, 0, wxEXPAND);
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
	TechTrees_DataList_Ages_Units->Add(TechTrees_DataList_Ages_List_Units, 1, wxEXPAND);
	TechTrees_DataList_Ages_Researches->Add(TechTrees_DataList_Ages_List_Researches, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buildings->Add(TechTrees_DataList_Buildings_List_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Units->Add(TechTrees_DataList_Buildings_List_Units, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Researches->Add(TechTrees_DataList_Buildings_List_Researches, 1, wxEXPAND);
	TechTrees_DataList_Units_Units->Add(TechTrees_DataList_Units_List_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buildings->Add(TechTrees_DataList_Researches_List_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Researches_Units->Add(TechTrees_DataList_Researches_List_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Researches->Add(TechTrees_DataList_Researches_List_Researches, 1, wxEXPAND);
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
	
	TechTrees_Data_Ages->Add(TechTrees_DataList_Ages_Buildings, 1, wxEXPAND);
	TechTrees_Data_Ages->Add(10, -1);
	TechTrees_Data_Ages->Add(TechTrees_DataList_Ages_Units, 1, wxEXPAND);
	TechTrees_Data_Ages->Add(10, -1);
	TechTrees_Data_Ages->Add(TechTrees_DataList_Ages_Researches, 1, wxEXPAND);
	
	TechTrees_Data_Buildings->Add(TechTrees_DataList_Buildings_Buildings, 1, wxEXPAND);
	TechTrees_Data_Buildings->Add(10, -1);
	TechTrees_Data_Buildings->Add(TechTrees_DataList_Buildings_Units, 1, wxEXPAND);
	TechTrees_Data_Buildings->Add(10, -1);
	TechTrees_Data_Buildings->Add(TechTrees_DataList_Buildings_Researches, 1, wxEXPAND);
	
	TechTrees_Data_Units->Add(TechTrees_DataList_Units_Units, 1, wxEXPAND);
	TechTrees_Data_Units->AddStretchSpacer(2);
	
	TechTrees_Data_Researches->Add(TechTrees_DataList_Researches_Buildings, 1, wxEXPAND);
	TechTrees_Data_Researches->Add(10, -1);
	TechTrees_Data_Researches->Add(TechTrees_DataList_Researches_Units, 1, wxEXPAND);
	TechTrees_Data_Researches->Add(10, -1);
	TechTrees_Data_Researches->Add(TechTrees_DataList_Researches_Researches, 1, wxEXPAND);
	
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

	/*Effects_E->Show(false);	// only for attributes 8, 9
	Effects_F->Show(false);	// only for attributes 8, 9
	Effects_ComboBox_A->Show(false);
	Effects_ComboBox_B->Show(false);
	Effects_ComboBox_C->Show(false);
	Effects_ComboBox_D->Show(false);
	Effects_ComboBox_UnitsA->Show(false);	// for Effects 0, 2, 3, 4, 5
	Effects_ComboBox_ResourcesA->Show(false);	// for Effects 1, 6
	Effects_ComboBox_ResearchsA->Show(false);	// for Effects 101, 103
	Effects_CheckBox_ModeB->Show(false);	// for Effects 1, 2
	Units_ComboBox_Class[2]->Show(false);	// for Effects 0, 4, 5
	Effects_ComboBox_UnitsB->Show(false);	// for Effects 3
	Effects_ComboBox_ResourcesB->Show(false);	// for Effects 101
	Effects_CheckBox_ModeC->Show(false);	// for Effects 101, 103
	Effects_ComboBox_AttributesC->Show(false);	// for Effects 0, 4, 5
	Effects_ComboBox_ResearchsD->Show(false);	// for Effects 102
	Attacks_ComboBox_Class[2]->Show(false);	// only for attributes 8, 9
	TechTrees_Effects_UseAnd->Show(false);*/
	
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

/*	TechTrees_Name->Connect(TechTrees_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Effects_Type->Connect(Effects_Type->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxByteEffectType), NULL, this);
	Effects_ComboBox_Type->Connect(Effects_ComboBox_Type->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxByteEffectType), NULL, this);
	Effects_A->Connect(Effects_A->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);
	Effects_B->Connect(Effects_B->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);
	Effects_C->Connect(Effects_C->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Short), NULL, this);
	Effects_D->Connect(Effects_D->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Float), NULL, this);
	Effects_CheckBox_ModeB->Connect(Effects_CheckBox_ModeB->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_CheckBoxShort), NULL, this);
	Effects_CheckBox_ModeC->Connect(Effects_CheckBox_ModeC->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_CheckBoxShort), NULL, this);
	Effects_ComboBox_AttributesC->Connect(Effects_ComboBox_AttributesC->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxShort), NULL, this);
	Attacks_ComboBox_Class[2]->Connect(Attacks_ComboBox_Class[2]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_ComboBoxes), NULL, this);*/

}
