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
	return Name;
}

void AGE_Frame::OnTTAgesBuildingSearch(wxCommandEvent& Event)
{
	ListTTAgesBuildings(TTAgeID);
}

void AGE_Frame::ListTTAgesBuildings(short Index)
{

}

void AGE_Frame::OnTTAgesBuildingSelect(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTAgesBuildingAdd(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTAgesBuildingDelete(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTAgesBuildingCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTAgesBuildingPaste(wxCommandEvent& Event)
{

}

string AGE_Frame::GetTTAgesUnitName(short Index, short Upper)
{
	string Name = "";
	return Name;
}

void AGE_Frame::OnTTAgesUnitSearch(wxCommandEvent& Event)
{
	ListTTAgesUnits(TTAgeID);
}

void AGE_Frame::ListTTAgesUnits(short Index)
{

}

void AGE_Frame::OnTTAgesUnitSelect(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTAgesUnitAdd(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTAgesUnitDelete(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTAgesUnitCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTAgesUnitPaste(wxCommandEvent& Event)
{

}

string AGE_Frame::GetTTAgesResearchName(short Index, short Upper)
{
	string Name = "";
	return Name;
}

void AGE_Frame::OnTTAgesResearchSearch(wxCommandEvent& Event)
{
	ListTTAgesResearches(TTAgeID);
}

void AGE_Frame::ListTTAgesResearches(short Index)
{

}

void AGE_Frame::OnTTAgesResearchSelect(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTAgesResearchAdd(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTAgesResearchDelete(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTAgesResearchCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTAgesResearchPaste(wxCommandEvent& Event)
{

}

string AGE_Frame::GetTTBuildingName(short Index)
{
	string Name = "";
	Name = "Building "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].ID);
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
	return Name;
}

void AGE_Frame::OnTTBuildingBuildingSearch(wxCommandEvent& Event)
{
	ListTTBuildingBuildings(TTBuildingConnectionID);
}

void AGE_Frame::ListTTBuildingBuildings(short Index)
{

}

void AGE_Frame::OnTTBuildingBuildingSelect(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTBuildingBuildingAdd(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTBuildingBuildingDelete(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTBuildingBuildingCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTBuildingBuildingPaste(wxCommandEvent& Event)
{

}

string AGE_Frame::GetTTBuildingUnitName(short Index, short Upper)
{
	string Name = "";
	return Name;
}

void AGE_Frame::OnTTBuildingUnitSearch(wxCommandEvent& Event)
{
	ListTTBuildingUnits(TTBuildingConnectionID);
}

void AGE_Frame::ListTTBuildingUnits(short Index)
{

}

void AGE_Frame::OnTTBuildingUnitSelect(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTBuildingUnitAdd(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTBuildingUnitDelete(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTBuildingUnitCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTBuildingUnitPaste(wxCommandEvent& Event)
{

}

string AGE_Frame::GetTTBuildingResearchName(short Index, short Upper)
{
	string Name = "";
	return Name;
}

void AGE_Frame::OnTTBuildingResearchSearch(wxCommandEvent& Event)
{
	ListTTBuildingResearches(TTBuildingConnectionID);
}

void AGE_Frame::ListTTBuildingResearches(short Index)
{

}

void AGE_Frame::OnTTBuildingResearchSelect(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTBuildingResearchAdd(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTBuildingResearchDelete(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTBuildingResearchCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTBuildingResearchPaste(wxCommandEvent& Event)
{

}

string AGE_Frame::GetTTUnitName(short Index)
{
	string Name = "";
	Name = "Unit "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].ID);
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
	return Name;
}

void AGE_Frame::OnTTUnitUnitSearch(wxCommandEvent& Event)
{
	ListTTUnitUnits(TTUnitConnectionID);
}

void AGE_Frame::ListTTUnitUnits(short Index)
{

}

void AGE_Frame::OnTTUnitUnitSelect(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTUnitUnitAdd(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTUnitUnitDelete(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTUnitUnitCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTUnitUnitPaste(wxCommandEvent& Event)
{

}

string AGE_Frame::GetTTResearchName(short Index)
{
	string Name = "";
	Name = "Research "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].ID);
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
	return Name;
}

void AGE_Frame::OnTTResearchBuildingSearch(wxCommandEvent& Event)
{
	ListTTResearchBuildings(TTResearchConnectionID);
}

void AGE_Frame::ListTTResearchBuildings(short Index)
{

}

void AGE_Frame::OnTTResearchBuildingSelect(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTResearchBuildingAdd(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTResearchBuildingDelete(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTResearchBuildingCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTResearchBuildingPaste(wxCommandEvent& Event)
{

}

string AGE_Frame::GetTTResearchUnitName(short Index, short Upper)
{
	string Name = "";
	return Name;
}

void AGE_Frame::OnTTResearchUnitSearch(wxCommandEvent& Event)
{
	ListTTResearchUnits(TTResearchConnectionID);
}

void AGE_Frame::ListTTResearchUnits(short Index)
{

}

void AGE_Frame::OnTTResearchUnitSelect(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTResearchUnitAdd(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTResearchUnitDelete(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTResearchUnitCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTResearchUnitPaste(wxCommandEvent& Event)
{

}

string AGE_Frame::GetTTResearchResearchName(short Index, short Upper)
{
	string Name = "";
	return Name;
}

void AGE_Frame::OnTTResearchResearchSearch(wxCommandEvent& Event)
{
	ListTTResearchResearches(TTResearchConnectionID);
}

void AGE_Frame::ListTTResearchResearches(short Index)
{

}

void AGE_Frame::OnTTResearchResearchSelect(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTResearchResearchAdd(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTResearchResearchDelete(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTResearchResearchCopy(wxCommandEvent& Event)
{

}

void AGE_Frame::OnTTResearchResearchPaste(wxCommandEvent& Event)
{

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
	
	TechTrees_Ages->Add(TechTrees_MainList_Ages, 1, wxEXPAND);
	TechTrees_Ages->Add(10, -1);
	TechTrees_Ages->AddStretchSpacer(3);
	
	TechTrees_Buildings->Add(TechTrees_MainList_Buildings, 1, wxEXPAND);
	TechTrees_Buildings->Add(10, -1);
	TechTrees_Buildings->AddStretchSpacer(3);
	
	TechTrees_Units->Add(TechTrees_MainList_Units, 1, wxEXPAND);
	TechTrees_Units->Add(10, -1);
	TechTrees_Units->AddStretchSpacer(3);
	
	TechTrees_Researches->Add(TechTrees_MainList_Researches, 1, wxEXPAND);
	TechTrees_Researches->Add(10, -1);
	TechTrees_Researches->AddStretchSpacer(3);

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
/*	Connect(TechTrees_TechTrees_Rename->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechageRename));
	Connect(TechTrees_TechTrees_Restore->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTechageRenameGE2));
	Connect(TechTrees_Effects_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnEffectsSelect));
	Connect(TechTrees_Effects_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnEffectsSearch));
	Connect(TechTrees_Effects_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnEffectsSearch));
	Connect(TechTrees_Effects_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsAdd));
	Connect(TechTrees_Effects_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsDelete));
	Connect(TechTrees_Effects_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsCopy));
	Connect(TechTrees_Effects_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnEffectsPaste));
	Effects_E->Connect(Effects_E->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TextControls), NULL, this);
	Effects_F->Connect(Effects_F->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TextControls), NULL, this);

	TechTrees_Name->Connect(TechTrees_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
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
