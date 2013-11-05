#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetTTAgesName(short Index)
{
	return "Age "+lexical_cast<string>(GenieFile->TechTree.TechTreeAges[Index].ID);
}

void AGE_Frame::OnTTAgesSearch(wxCommandEvent &Event)
{
	ListTTAgess();
}

void AGE_Frame::ListTTAgess()
{
	searchText = TechTrees_MainList_Ages_Search->GetValue().Lower();
	excludeText = TechTrees_MainList_Ages_Search_R->GetValue().Lower();

	auto Selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	TechTrees_MainList_Ages_List->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.TechTreeAges.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetTTAgesName(loop);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_MainList_Ages_List->Append(Name, (void*)&GenieFile->TechTree.TechTreeAges[loop]);
		}
	}

	ListingFix(Selections, TechTrees_MainList_Ages_List);

	wxCommandEvent E;
	OnTTAgesSelect(E);
}

void AGE_Frame::OnTTAgesSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(Selections < 1) return;

	TTAgeIDs.resize(Selections);
	TechTrees_Ages_Unknown1->resize(Selections);
	TechTrees_Ages_ID->resize(Selections);
	TechTrees_Ages_Unknown2->resize(Selections);
	TechTrees_Ages_Unknown3->resize(Selections);
	TechTrees_Ages_Unknown4->resize(Selections);
	for(short loop = 0; loop < 49; ++loop)
	{
		TechTrees_Ages_Zeroes1[loop]->resize(Selections);
	}
	if(GenieVersion >= genie::GV_SWGB)
	for(short loop = 49;loop < 99; ++loop)
	{
		TechTrees_Ages_Zeroes2[loop-49]->resize(Selections);
	}

	genie::TechTreeAge * AgePointer;
	for(auto sel = Selections; sel--> 0;)
	{
		AgePointer = (genie::TechTreeAge*)TechTrees_MainList_Ages_List->GetClientData(Items.Item(sel));
		TTAgeIDs[sel] = (AgePointer - (&GenieFile->TechTree.TechTreeAges[0]));

		TechTrees_Ages_Unknown1->container[sel] = &AgePointer->Unknown1;
		TechTrees_Ages_ID->container[sel] = &AgePointer->ID;
		TechTrees_Ages_Unknown2->container[sel] = &AgePointer->Unknown2;
		TechTrees_Ages_Unknown3->container[sel] = &AgePointer->Unknown3;
		TechTrees_Ages_Unknown4->container[sel] = &AgePointer->Unknown4;
		for(short loop = 0; loop < 49; ++loop)
		{
			TechTrees_Ages_Zeroes1[loop]->container[sel] = &AgePointer->Zeroes[loop];
		}
		if(GenieVersion >= genie::GV_SWGB)
		for(short loop = 49;loop < 99; ++loop)
		{
			TechTrees_Ages_Zeroes2[loop-49]->container[sel] = &AgePointer->Zeroes[loop];
		}
	}

	TechTrees_Ages_Unknown1->ChangeValue(lexical_cast<string>(AgePointer->Unknown1));
	TechTrees_Ages_ID->ChangeValue(lexical_cast<string>(AgePointer->ID));
	TechTrees_Ages_Unknown2->ChangeValue(lexical_cast<string>((short)AgePointer->Unknown2));
	TechTrees_Ages_Unknown3->ChangeValue(lexical_cast<string>(AgePointer->Unknown3));
	TechTrees_Ages_Unknown4->ChangeValue(lexical_cast<string>(AgePointer->Unknown4));
	for(short loop = 0; loop < 49; ++loop)
	{
		TechTrees_Ages_Zeroes1[loop]->ChangeValue(lexical_cast<string>(AgePointer->Zeroes[loop]));
	}
	if(GenieVersion >= genie::GV_SWGB)
	for(short loop = 49;loop < 99; ++loop)
	{
		TechTrees_Ages_Zeroes2[loop-49]->ChangeValue(lexical_cast<string>(AgePointer->Zeroes[loop]));
	}

	ListTTAgesBuildings();
	ListTTAgesUnits();
	ListTTAgesResearches();
}

void AGE_Frame::OnTTAgesAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->TechTree.TechTreeAges);
	ListTTAgess();
}

void AGE_Frame::OnTTAgesInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->TechTree.TechTreeAges, TTAgeIDs[0]);
	ListTTAgess();
}

void AGE_Frame::OnTTAgesDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.TechTreeAges, TTAgeIDs);
	ListTTAgess();
}

void AGE_Frame::OnTTAgesCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.TechTreeAges, TTAgeIDs, copies->TTAge);
}

void AGE_Frame::OnTTAgesPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->TechTree.TechTreeAges, TTAgeIDs[0], copies->TTAge);
	ListTTAgess();
}

void AGE_Frame::OnTTAgesPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->TechTree.TechTreeAges, TTAgeIDs[0], copies->TTAge);
	ListTTAgess();
}

string AGE_Frame::GetBuildingName(short Building)
{
	string Name = lexical_cast<string>(Building)+" ";
	if(GenieFile->Civs[0].Units.size() <= Building) return Name + "Nonexistent Building";
	if(!LangDLLstring(GenieFile->Civs[0].Units[Building].LanguageDLLName, 2).empty())
	{
		return Name + LangDLLstring(GenieFile->Civs[0].Units[Building].LanguageDLLName, 64);
	}
	if(!GenieFile->Civs[0].Units[Building].Name.empty())
	{
		return Name + GenieFile->Civs[0].Units[Building].Name;
	}
	return Name + "New Building";
}

void AGE_Frame::OnTTAgesBuildingSearch(wxCommandEvent &Event)
{
	ListTTAgesBuildings();
}

void AGE_Frame::ListTTAgesBuildings()
{
	searchText = TechTrees_DataList_Ages_Search_Buildings->GetValue().Lower();
	excludeText = TechTrees_DataList_Ages_Search_R_Buildings->GetValue().Lower();

	auto Selections = TechTrees_DataList_Ages_List_Buildings->GetSelections(Items);
	TechTrees_DataList_Ages_List_Buildings->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetBuildingName(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_DataList_Ages_List_Buildings->Append(Name, (void*)&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings[loop]);
		}
	}
	ListingFix(Selections, TechTrees_DataList_Ages_List_Buildings);

	wxCommandEvent E;
	OnTTAgesBuildingSelect(E);
}

void AGE_Frame::OnTTAgesBuildingSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Buildings->GetSelections(Items);
	if(Selections > 0)
	{
		TTAgeBuildIDs.resize(Selections);
		TechTrees_Ages_Building->resize(Selections);

		int32_t * BuildingPointer;
		for(auto loop = Selections; loop--> 0;)
		{
			BuildingPointer = (int32_t*)TechTrees_DataList_Ages_List_Buildings->GetClientData(Items.Item(loop));
			TTAgeBuildIDs[loop] = (BuildingPointer - (&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings[0]));
			TechTrees_Ages_Building->container[loop] = BuildingPointer;
		}

		TechTrees_Ages_Building->ChangeValue(lexical_cast<string>(*BuildingPointer));
		TechTrees_Ages_ComboBox_Building->SetSelection(*BuildingPointer + 1);
	}
	else
	{
		TechTrees_Ages_Building->ChangeValue("0");
		TechTrees_Ages_ComboBox_Building->SetSelection(0);
	}
}

void AGE_Frame::OnTTAgesBuildingAdd(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings);
	ListTTAgesBuildings();
}

void AGE_Frame::OnTTAgesBuildingInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs[0]);
	ListTTAgesBuildings();
}

void AGE_Frame::OnTTAgesBuildingDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs);
	ListTTAgesBuildings();
}

void AGE_Frame::OnTTAgesBuildingCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs, copies->TTAgeBuild);
}

void AGE_Frame::OnTTAgesBuildingPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs[0], copies->TTAgeBuild);
	ListTTAgesBuildings();
}

void AGE_Frame::OnTTAgesBuildingPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs[0], copies->TTAgeBuild);
	ListTTAgesBuildings();
}

void AGE_Frame::OnTTAgesBuildingCopyToAges(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTAgeIDs.size(); ++loop)
	{
		GenieFile->TechTree.TechTreeAges[TTAgeIDs[loop]].Buildings = GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings;
	}
}

void AGE_Frame::OnTTAgesUnitSearch(wxCommandEvent &Event)
{
	ListTTAgesUnits();
}

void AGE_Frame::ListTTAgesUnits()
{
	searchText = TechTrees_DataList_Ages_Search_Units->GetValue().Lower();
	excludeText = TechTrees_DataList_Ages_Search_R_Units->GetValue().Lower();

	auto Selections = TechTrees_DataList_Ages_List_Units->GetSelections(Items);
	TechTrees_DataList_Ages_List_Units->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineUnitName(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_DataList_Ages_List_Units->Append(Name, (void*)&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units[loop]);
		}
	}
	ListingFix(Selections, TechTrees_DataList_Ages_List_Units);

	wxCommandEvent E;
	OnTTAgesUnitSelect(E);
}

void AGE_Frame::OnTTAgesUnitSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Units->GetSelections(Items);
	if(Selections > 0)
	{
		TTAgeUnitIDs.resize(Selections);
		TechTrees_Ages_Unit->resize(Selections);

		int32_t * UnitPointer;
		for(auto loop = Selections; loop--> 0;)
		{
			UnitPointer = (int32_t*)TechTrees_DataList_Ages_List_Units->GetClientData(Items.Item(loop));
			TTAgeUnitIDs[loop] = (UnitPointer - (&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units[0]));
			TechTrees_Ages_Unit->container[loop] = UnitPointer;
		}

		TechTrees_Ages_Unit->ChangeValue(lexical_cast<string>(*UnitPointer));
		TechTrees_Ages_ComboBox_Unit->SetSelection(*UnitPointer + 1);
	}
	else
	{
		TechTrees_Ages_Unit->ChangeValue("0");
		TechTrees_Ages_ComboBox_Unit->SetSelection(0);
	}
}

void AGE_Frame::OnTTAgesUnitAdd(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units);
	ListTTAgesUnits();
}

void AGE_Frame::OnTTAgesUnitInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs[0]);
	ListTTAgesUnits();
}

void AGE_Frame::OnTTAgesUnitDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs);
	ListTTAgesUnits();
}

void AGE_Frame::OnTTAgesUnitCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs, copies->TTAgeUnit);
}

void AGE_Frame::OnTTAgesUnitPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs[0], copies->TTAgeUnit);
	ListTTAgesUnits();
}

void AGE_Frame::OnTTAgesUnitPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs[0], copies->TTAgeUnit);
	ListTTAgesUnits();
}

void AGE_Frame::OnTTAgesUnitCopyToAges(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTAgeIDs.size(); ++loop)
	{
		GenieFile->TechTree.TechTreeAges[TTAgeIDs[loop]].Units = GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units;
	}
}

string AGE_Frame::GetSimpleResearchName(short Research)
{
	string Name = lexical_cast<string>(Research)+" ";
	if(GenieFile->Researchs.size() <= Research) return Name + "Nonexistent Research";
	if(!LangDLLstring(GenieFile->Researchs[Research].LanguageDLLName, 2).empty())
	{
		return Name + LangDLLstring(GenieFile->Researchs[Research].LanguageDLLName, 64);
	}
	if(!GenieFile->Researchs[Research].Name.empty())
	{
		return Name + GenieFile->Researchs[Research].Name;
	}
	return Name + "New Research";
}

void AGE_Frame::OnTTAgesResearchSearch(wxCommandEvent &Event)
{
	ListTTAgesResearches();
}

void AGE_Frame::ListTTAgesResearches()
{
	searchText = TechTrees_DataList_Ages_Search_Researches->GetValue().Lower();
	excludeText = TechTrees_DataList_Ages_Search_R_Researches->GetValue().Lower();

	auto Selections = TechTrees_DataList_Ages_List_Researches->GetSelections(Items);
	TechTrees_DataList_Ages_List_Researches->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetSimpleResearchName(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_DataList_Ages_List_Researches->Append(Name, (void*)&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches[loop]);
		}
	}
	ListingFix(Selections, TechTrees_DataList_Ages_List_Researches);

	wxCommandEvent E;
	OnTTAgesResearchSelect(E);
}

void AGE_Frame::OnTTAgesResearchSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Researches->GetSelections(Items);
	if(Selections > 0)
	{
		TTAgeResIDs.resize(Selections);
		TechTrees_Ages_Research->resize(Selections);

		int32_t * ResearchPointer;
		for(auto loop = Selections; loop--> 0;)
		{
			ResearchPointer = (int32_t*)TechTrees_DataList_Ages_List_Researches->GetClientData(Items.Item(loop));
			TTAgeResIDs[loop] = (ResearchPointer - (&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches[0]));
			TechTrees_Ages_Research->container[loop] = ResearchPointer;
		}

		TechTrees_Ages_Research->ChangeValue(lexical_cast<string>(*ResearchPointer));
		TechTrees_Ages_ComboBox_Research->SetSelection(*ResearchPointer + 1);
	}
	else
	{
		TechTrees_Ages_Research->ChangeValue("0");
		TechTrees_Ages_ComboBox_Research->SetSelection(0);
	}
}

void AGE_Frame::OnTTAgesResearchAdd(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches);
	ListTTAgesResearches();
}

void AGE_Frame::OnTTAgesResearchInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs[0]);
	ListTTAgesResearches();
}

void AGE_Frame::OnTTAgesResearchDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs);
	ListTTAgesResearches();
}

void AGE_Frame::OnTTAgesResearchCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs, copies->TTAgeRes);
}

void AGE_Frame::OnTTAgesResearchPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs[0], copies->TTAgeRes);
	ListTTAgesResearches();
}

void AGE_Frame::OnTTAgesResearchPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Ages_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs[0], copies->TTAgeRes);
	ListTTAgesResearches();
}

void AGE_Frame::OnTTAgesResearchCopyToAges(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTAgeIDs.size(); ++loop)
	{
		GenieFile->TechTree.TechTreeAges[TTAgeIDs[loop]].Researches = GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches;
	}
}

string AGE_Frame::GetTTBuildingName(short Index)
{
	string Name = "";

	short Selection[2];
	for(short loop = 0; loop < 2; ++loop)
	Selection[loop] = TechTrees_MainList_Buildings_SearchFilters[loop]->GetSelection();

	if(Selection[0] == 0)	// Normal Name
	{
		// Do nothing!
	}
	else for(short loop = 0; loop < 2; ++loop)
	{
		switch(Selection[loop])
		{
			case 1: // Required Researches
				Name += "R "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].RequiredResearches);
				break;
			case 2: // Age
				Name += "A "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Age);
				break;
			case 3: // Unit or Research 1
				Name += "UR1 "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].UnitOrResearch1);
				break;
			case 4: // Unit or Research 2
				Name += "UR2 "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].UnitOrResearch2);
				break;
			case 5: // U/R 1 Mode
				Name += "1M "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Mode1);
				break;
			case 6: // U/R 2 Mode
				Name += "2M "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Mode2);
				break;
			case 7: // Connections
				Name += "C "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Connections);
				break;
			case 8: // Enabling Research
				Name += "E "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].EnablingResearch);
				break;
		}
		Name += ", ";
		if(Selection[loop+1] < 1) break;
	}

	Name += lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].ID)+" ";
	if(!LangDLLstring(GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Index].ID].LanguageDLLName, 2).empty())
	{
		Name += LangDLLstring(GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Index].ID].LanguageDLLName, 64);
	}
	else if(!GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Index].ID].Name.empty())
	{
		Name += GenieFile->Civs[0].Units[GenieFile->TechTree.BuildingConnections[Index].ID].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTBuildingSearch(wxCommandEvent &Event)
{
	ListTTBuildings();
}

void AGE_Frame::ListTTBuildings()
{
	searchText = TechTrees_MainList_Buildings_Search->GetValue().Lower();
	excludeText = TechTrees_MainList_Buildings_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	UseAnd[loop] = TechTrees_MainList_Buildings_UseAnd[loop]->GetValue();

	auto Selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	TechTrees_MainList_Buildings_List->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.BuildingConnections.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetTTBuildingName(loop);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_MainList_Buildings_List->Append(Name, (void*)&GenieFile->TechTree.BuildingConnections[loop]);
		}
	}

	ListingFix(Selections, TechTrees_MainList_Buildings_List);

	for(short loop = 0; loop < 2; ++loop)
	UseAnd[loop] = false;

	wxCommandEvent E;
	OnTTBuildingSelect(E);
}

void AGE_Frame::OnTTBuildingSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(Selections < 1) return;

	TTBuildConIDs.resize(Selections);
	TechTrees_Buildings_ID->resize(Selections);
	TechTrees_Buildings_Always2->resize(Selections);
	TechTrees_Buildings_RequiredResearches->resize(Selections);
	TechTrees_Buildings_Age->resize(Selections);
	TechTrees_Buildings_UnitOrResearch1->resize(Selections);
	TechTrees_Buildings_UnitOrResearch2->resize(Selections);
	for(short loop = 0; loop < 8; ++loop)
	{
		TechTrees_Buildings_Unknown2a1[loop]->resize(Selections);
	}
	for(short loop = 0; loop < 7; ++loop)
	{
		TechTrees_Buildings_Unknown2b1[loop]->resize(Selections);
	}
	if(GenieVersion >= genie::GV_SWGB)
	{
		for(short loop = 8;loop < 18; ++loop)
		{
			TechTrees_Buildings_Unknown2a2[loop-8]->resize(Selections);
		}
		for(short loop = 7;loop < 17; ++loop)
		{
			TechTrees_Buildings_Unknown2b2[loop-7]->resize(Selections);
		}
	}
	TechTrees_Buildings_Mode1->resize(Selections);
	TechTrees_Buildings_Mode2->resize(Selections);
	for(short loop = 0; loop < 11; ++loop)
	{
		TechTrees_Buildings_Unknown3[loop]->resize(Selections);
	}
	TechTrees_Buildings_Connections->resize(Selections);
	TechTrees_Buildings_EnablingResearch->resize(Selections);

	genie::BuildingConnection * BuildingConPointer;
	for(auto sel = Selections; sel--> 0;)
	{
		BuildingConPointer = (genie::BuildingConnection*)TechTrees_MainList_Buildings_List->GetClientData(Items.Item(sel));
		TTBuildConIDs[sel] = (BuildingConPointer - (&GenieFile->TechTree.BuildingConnections[0]));

		TechTrees_Buildings_ID->container[sel] = &BuildingConPointer->ID;
		TechTrees_Buildings_Always2->container[sel] = &BuildingConPointer->Unknown1;
		TechTrees_Buildings_RequiredResearches->container[sel] = &BuildingConPointer->RequiredResearches;
		TechTrees_Buildings_Age->container[sel] = &BuildingConPointer->Age;
		TechTrees_Buildings_UnitOrResearch1->container[sel] = &BuildingConPointer->UnitOrResearch1;
		TechTrees_Buildings_UnitOrResearch2->container[sel] = &BuildingConPointer->UnitOrResearch2;
		for(short loop = 0; loop < 8; ++loop)
		{
			TechTrees_Buildings_Unknown2a1[loop]->container[sel] = &BuildingConPointer->Unknown2a[loop];
		}
		for(short loop = 0; loop < 7; ++loop)
		{
			TechTrees_Buildings_Unknown2b1[loop]->container[sel] = &BuildingConPointer->Unknown2b[loop];
		}
		if(GenieVersion >= genie::GV_SWGB)
		{
			for(short loop = 8;loop < 18; ++loop)
			{
				TechTrees_Buildings_Unknown2a2[loop-8]->container[sel] = &BuildingConPointer->Unknown2a[loop];
			}
			for(short loop = 7;loop < 17; ++loop)
			{
				TechTrees_Buildings_Unknown2b2[loop-7]->container[sel] = &BuildingConPointer->Unknown2b[loop];
			}
		}
		TechTrees_Buildings_Mode1->container[sel] = &BuildingConPointer->Mode1;
		TechTrees_Buildings_Mode2->container[sel] = &BuildingConPointer->Mode2;
		for(short loop = 0; loop < 11; ++loop)
		{
			TechTrees_Buildings_Unknown3[loop]->container[sel] = &BuildingConPointer->Unknown3[loop];
		}
		TechTrees_Buildings_Connections->container[sel] = &BuildingConPointer->Connections;
		TechTrees_Buildings_EnablingResearch->container[sel] = &BuildingConPointer->EnablingResearch;
	}

	TechTrees_Buildings_ID->ChangeValue(lexical_cast<string>(BuildingConPointer->ID));
	TechTrees_Buildings_ComboBox_ID->SetSelection(BuildingConPointer->ID + 1);
	TechTrees_Buildings_Always2->ChangeValue(lexical_cast<string>((short)BuildingConPointer->Unknown1));
	TechTrees_Buildings_RequiredResearches->ChangeValue(lexical_cast<string>(BuildingConPointer->RequiredResearches));
	TechTrees_Buildings_Age->ChangeValue(lexical_cast<string>(BuildingConPointer->Age));
	TechTrees_Buildings_UnitOrResearch1->ChangeValue(lexical_cast<string>(BuildingConPointer->UnitOrResearch1));
	TechTrees_Buildings_UnitOrResearch2->ChangeValue(lexical_cast<string>(BuildingConPointer->UnitOrResearch2));
	if(BuildingConPointer->Mode1 == 1 || BuildingConPointer->Mode1 == 2)
	{
		TechTrees_ComboBox_Unit[0]->Show(true);
		TechTrees_ComboBox_Research[0]->Show(false);
		TechTrees_ComboBox_Unit[0]->SetSelection(BuildingConPointer->UnitOrResearch1 + 1);
		TechTrees_Buildings_Text_UnitOrResearch1->SetLabel("Unit/Building 1");
	}
	else if(BuildingConPointer->Mode1 == 3)
	{
		TechTrees_ComboBox_Unit[0]->Show(false);
		TechTrees_ComboBox_Research[0]->Show(true);
		TechTrees_ComboBox_Research[0]->SetSelection(BuildingConPointer->UnitOrResearch1 + 1);
		TechTrees_Buildings_Text_UnitOrResearch1->SetLabel("Research 1");
	}
	else
	{
		TechTrees_ComboBox_Unit[0]->Show(false);
		TechTrees_ComboBox_Research[0]->Show(false);
		TechTrees_Buildings_Text_UnitOrResearch1->SetLabel("Select Mode 1");
	}
	if(BuildingConPointer->Mode2 == 1 || BuildingConPointer->Mode2 == 2)
	{
		TechTrees_ComboBox_Unit[1]->Show(true);
		TechTrees_ComboBox_Research[1]->Show(false);
		TechTrees_ComboBox_Unit[1]->SetSelection(BuildingConPointer->UnitOrResearch2 + 1);
		TechTrees_Buildings_Text_UnitOrResearch2->SetLabel("Unit/Building 2");
	}
	else if(BuildingConPointer->Mode2 == 3)
	{
		TechTrees_ComboBox_Unit[1]->Show(false);
		TechTrees_ComboBox_Research[1]->Show(true);
		TechTrees_ComboBox_Research[1]->SetSelection(BuildingConPointer->UnitOrResearch2 + 1);
		TechTrees_Buildings_Text_UnitOrResearch2->SetLabel("Research 2");
	}
	else
	{
		TechTrees_ComboBox_Unit[1]->Show(false);
		TechTrees_ComboBox_Research[1]->Show(false);
		TechTrees_Buildings_Text_UnitOrResearch2->SetLabel("Select Mode 2");
	}
	for(short loop = 0; loop < 8; ++loop)
	{
		TechTrees_Buildings_Unknown2a1[loop]->ChangeValue(lexical_cast<string>(BuildingConPointer->Unknown2a[loop]));
	}
	for(short loop = 0; loop < 7; ++loop)
	{
		TechTrees_Buildings_Unknown2b1[loop]->ChangeValue(lexical_cast<string>(BuildingConPointer->Unknown2b[loop]));
	}
	if(GenieVersion >= genie::GV_SWGB)
	{
		for(short loop = 8;loop < 18; ++loop)
		{
			TechTrees_Buildings_Unknown2a2[loop-8]->ChangeValue(lexical_cast<string>(BuildingConPointer->Unknown2a[loop]));
		}
		for(short loop = 7;loop < 17; ++loop)
		{
			TechTrees_Buildings_Unknown2b2[loop-7]->ChangeValue(lexical_cast<string>(BuildingConPointer->Unknown2b[loop]));
		}
	}
	TechTrees_Buildings_Mode1->ChangeValue(lexical_cast<string>(BuildingConPointer->Mode1));
	TechTrees_ComboBox_Modes[0]->SetSelection(0);
	TechTrees_ComboBox_Modes[0]->SetSelection(BuildingConPointer->Mode1);
	TechTrees_Buildings_Mode2->ChangeValue(lexical_cast<string>(BuildingConPointer->Mode2));
	TechTrees_ComboBox_Modes[1]->SetSelection(0);
	TechTrees_ComboBox_Modes[1]->SetSelection(BuildingConPointer->Mode2);
	for(short loop = 0; loop < 11; ++loop)
	{
		TechTrees_Buildings_Unknown3[loop]->ChangeValue(lexical_cast<string>((short)BuildingConPointer->Unknown3[loop]));
	}
	TechTrees_Buildings_Connections->ChangeValue(lexical_cast<string>(BuildingConPointer->Connections));
	TechTrees_Buildings_EnablingResearch->ChangeValue(lexical_cast<string>(BuildingConPointer->EnablingResearch));
	TechTrees_Buildings_ComboBox_EnablingResearch->SetSelection(BuildingConPointer->EnablingResearch + 1);

	ListTTBuildingBuildings();
	ListTTBuildingUnits();
	ListTTBuildingResearches();

	TechTrees_Main->Layout();
	TechTrees_Scroller->GetSizer()->FitInside(TechTrees_Scroller);
}

void AGE_Frame::OnTTBuildingAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->TechTree.BuildingConnections);
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->TechTree.BuildingConnections, TTBuildConIDs[0]);
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.BuildingConnections, TTBuildConIDs);
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.BuildingConnections, TTBuildConIDs, copies->TTBuildCon);
}

void AGE_Frame::OnTTBuildingPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->TechTree.BuildingConnections, TTBuildConIDs[0], copies->TTBuildCon);
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->TechTree.BuildingConnections, TTBuildConIDs[0], copies->TTBuildCon);
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingBuildingSearch(wxCommandEvent &Event)
{
	ListTTBuildingBuildings();
}

void AGE_Frame::ListTTBuildingBuildings()
{
	searchText = TechTrees_DataList_Buildings_Search_Buildings->GetValue().Lower();
	excludeText = TechTrees_DataList_Buildings_Search_R_Buildings->GetValue().Lower();

	auto Selections = TechTrees_DataList_Buildings_List_Buildings->GetSelections(Items);
	TechTrees_DataList_Buildings_List_Buildings->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetBuildingName(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_DataList_Buildings_List_Buildings->Append(Name, (void*)&GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings[loop]);
		}
	}
	ListingFix(Selections, TechTrees_DataList_Buildings_List_Buildings);

	wxCommandEvent E;
	OnTTBuildingBuildingSelect(E);
}

void AGE_Frame::OnTTBuildingBuildingSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Buildings->GetSelections(Items);
	if(Selections > 0)
	{
		TTBuildBuildIDs.resize(Selections);
		TechTrees_Buildings_Building->resize(Selections);

		int32_t * BuildingPointer;
		for(auto loop = Selections; loop--> 0;)
		{
			BuildingPointer = (int32_t*)TechTrees_DataList_Buildings_List_Buildings->GetClientData(Items.Item(loop));
			TTBuildBuildIDs[loop] = (BuildingPointer - (&GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings[0]));
			TechTrees_Buildings_Building->container[loop] = BuildingPointer;
		}

		TechTrees_Buildings_Building->ChangeValue(lexical_cast<string>(*BuildingPointer));
		TechTrees_Buildings_ComboBox_Building->SetSelection(*BuildingPointer + 1);
	}
	else
	{
		TechTrees_Buildings_Building->ChangeValue("0");
		TechTrees_Buildings_ComboBox_Building->SetSelection(0);
	}
}

void AGE_Frame::OnTTBuildingBuildingAdd(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings);
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs[0]);
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs);
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs, copies->TTBuildBuild);
}

void AGE_Frame::OnTTBuildingBuildingPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs[0], copies->TTBuildBuild);
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs[0], copies->TTBuildBuild);
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingCopyToBuildings(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTBuildConIDs.size(); ++loop)
	{
		GenieFile->TechTree.BuildingConnections[TTBuildConIDs[loop]].Buildings = GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings;
	}
}

void AGE_Frame::OnTTBuildingUnitSearch(wxCommandEvent &Event)
{
	ListTTBuildingUnits();
}

void AGE_Frame::ListTTBuildingUnits()
{
	searchText = TechTrees_DataList_Buildings_Search_Units->GetValue().Lower();
	excludeText = TechTrees_DataList_Buildings_Search_R_Units->GetValue().Lower();

	auto Selections = TechTrees_DataList_Buildings_List_Units->GetSelections(Items);
	TechTrees_DataList_Buildings_List_Units->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineUnitName(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_DataList_Buildings_List_Units->Append(Name, (void*)&GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units[loop]);
		}
	}
	ListingFix(Selections, TechTrees_DataList_Buildings_List_Units);

	wxCommandEvent E;
	OnTTBuildingUnitSelect(E);
}

void AGE_Frame::OnTTBuildingUnitSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Units->GetSelections(Items);
	if(Selections > 0)
	{
		TTBuildUnitIDs.resize(Selections);
		TechTrees_Buildings_Unit->resize(Selections);

		int32_t * UnitPointer;
		for(auto loop = Selections; loop--> 0;)
		{
			UnitPointer = (int32_t*)TechTrees_DataList_Buildings_List_Units->GetClientData(Items.Item(loop));
			TTBuildUnitIDs[loop] = (UnitPointer - (&GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units[0]));
			TechTrees_Buildings_Unit->container[loop] = UnitPointer;
		}

		TechTrees_Buildings_Unit->ChangeValue(lexical_cast<string>(*UnitPointer));
		TechTrees_Buildings_ComboBox_Unit->SetSelection(*UnitPointer + 1);
	}
	else
	{
		TechTrees_Buildings_Unit->ChangeValue("0");
		TechTrees_Buildings_ComboBox_Unit->SetSelection(0);
	}
}

void AGE_Frame::OnTTBuildingUnitAdd(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units);
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs[0]);
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs);
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs, copies->TTBuildUnit);
}

void AGE_Frame::OnTTBuildingUnitPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs[0], copies->TTBuildUnit);
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs[0], copies->TTBuildUnit);
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitCopyToBuildings(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTBuildConIDs.size(); ++loop)
	{
		GenieFile->TechTree.BuildingConnections[TTBuildConIDs[loop]].Units = GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units;
	}
}

void AGE_Frame::OnTTBuildingResearchSearch(wxCommandEvent &Event)
{
	ListTTBuildingResearches();
}

void AGE_Frame::ListTTBuildingResearches()
{
	searchText = TechTrees_DataList_Buildings_Search_Researches->GetValue().Lower();
	excludeText = TechTrees_DataList_Buildings_Search_R_Researches->GetValue().Lower();

	auto Selections = TechTrees_DataList_Buildings_List_Researches->GetSelections(Items);
	TechTrees_DataList_Buildings_List_Researches->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetSimpleResearchName(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_DataList_Buildings_List_Researches->Append(Name, (void*)&GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches[loop]);
		}
	}
	ListingFix(Selections, TechTrees_DataList_Buildings_List_Researches);

	wxCommandEvent E;
	OnTTBuildingResearchSelect(E);
}

void AGE_Frame::OnTTBuildingResearchSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Researches->GetSelections(Items);
	if(Selections > 0)
	{
		TTBuildResIDs.resize(Selections);
		TechTrees_Buildings_Research->resize(Selections);

		int32_t * ResearchPointer;
		for(auto loop = Selections; loop--> 0;)
		{
			ResearchPointer = (int32_t*)TechTrees_DataList_Buildings_List_Researches->GetClientData(Items.Item(loop));
			TTBuildResIDs[loop] = (ResearchPointer - (&GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches[0]));
			TechTrees_Buildings_Research->container[loop] = ResearchPointer;
		}

		TechTrees_Buildings_Research->ChangeValue(lexical_cast<string>(*ResearchPointer));
		TechTrees_Buildings_ComboBox_Research->SetSelection(*ResearchPointer + 1);
	}
	else
	{
		TechTrees_Buildings_Research->ChangeValue("0");
		TechTrees_Buildings_ComboBox_Research->SetSelection(0);
	}
}

void AGE_Frame::OnTTBuildingResearchAdd(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches);
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs[0]);
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs);
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs, copies->TTBuildRes);
}

void AGE_Frame::OnTTBuildingResearchPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs[0], copies->TTBuildRes);
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Buildings_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs[0], copies->TTBuildRes);
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchCopyToBuildings(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTBuildConIDs.size(); ++loop)
	{
		GenieFile->TechTree.BuildingConnections[TTBuildConIDs[loop]].Researches = GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches;
	}
}

string AGE_Frame::GetTTUnitName(short Index)
{
	string Name = "";

	short Selection[2];
	for(short loop = 0; loop < 2; ++loop)
	Selection[loop] = TechTrees_MainList_Units_SearchFilters[loop]->GetSelection();

	if(Selection[0] == 0)	// Normal Name
	{
		// Do nothing!
	}
	else for(short loop = 0; loop < 2; ++loop)
	{
		switch(Selection[loop])
		{
			case 1: // Upper Building
				Name += "U "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].UpperBuilding);
				break;
			case 2: // Required Researches
				Name += "C "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].RequiredResearches);
				break;
			case 3: // Age
				Name += "A "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Age);
				break;
			case 4: // Unit or Research 1
				Name += "UR1 "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].UnitOrResearch1);
				break;
			case 5: // Unit or Research 2
				Name += "UR2 "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].UnitOrResearch2);
				break;
			case 6: // U/R 1 Mode
				Name += "1M "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Mode1);
				break;
			case 7: // U/R 2 Mode
				Name += "2M "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Mode2);
				break;
			case 8: // Vertical Line Number
				Name += "V "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].VerticalLine);
				break;
			case 9: // Space Sharing
				Name += "S "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].LocationInAge);
				break;
			case 10: // Required Research
				Name += "R "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].RequiredResearch);
				break;
			case 11: // Placement
				Name += "P "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].LineMode);
				break;
			case 12: // Enabling Research
				Name += "E "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].EnablingResearch);
				break;
		}
		Name += ", ";
		if(Selection[loop+1] < 1) break;
	}

	Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].ID)+" ";
	if(!LangDLLstring(GenieFile->Civs[0].Units[GenieFile->TechTree.UnitConnections[Index].ID].LanguageDLLName, 2).empty())
	{
		Name += LangDLLstring(GenieFile->Civs[0].Units[GenieFile->TechTree.UnitConnections[Index].ID].LanguageDLLName, 64);
	}
	else if(!GenieFile->Civs[0].Units[GenieFile->TechTree.UnitConnections[Index].ID].Name.empty())
	{
		Name += GenieFile->Civs[0].Units[GenieFile->TechTree.UnitConnections[Index].ID].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTUnitSearch(wxCommandEvent &Event)
{
	ListTTUnits();
}

void AGE_Frame::ListTTUnits()
{
	searchText = TechTrees_MainList_Units_Search->GetValue().Lower();
	excludeText = TechTrees_MainList_Units_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	UseAnd[loop] = TechTrees_MainList_Units_UseAnd[loop]->GetValue();

	auto Selections = TechTrees_MainList_Units_List->GetSelections(Items);
	TechTrees_MainList_Units_List->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.UnitConnections.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetTTUnitName(loop);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_MainList_Units_List->Append(Name, (void*)&GenieFile->TechTree.UnitConnections[loop]);
		}
	}

	ListingFix(Selections, TechTrees_MainList_Units_List);

	for(short loop = 0; loop < 2; ++loop)
	UseAnd[loop] = false;

	wxCommandEvent E;
	OnTTUnitSelect(E);
}

void AGE_Frame::OnTTUnitSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	TTUnitConIDs.resize(Selections);
	TechTrees_Units_ID->resize(Selections);
	TechTrees_Units_Always2->resize(Selections);
	TechTrees_Units_UpperBuilding->resize(Selections);
	TechTrees_Units_RequiredResearches->resize(Selections);
	TechTrees_Units_Age->resize(Selections);
	TechTrees_Units_UnitOrResearch1->resize(Selections);
	TechTrees_Units_UnitOrResearch2->resize(Selections);
	TechTrees_Units_Mode1->resize(Selections);
	TechTrees_Units_Mode2->resize(Selections);
	for(short loop = 0; loop < 8; ++loop)
	{
		TechTrees_Units_Unknown2a1[loop]->resize(Selections);
	}
	for(short loop = 0; loop < 7; ++loop)
	{
		TechTrees_Units_Unknown2b1[loop]->resize(Selections);
	}
	if(GenieVersion >= genie::GV_SWGB)
	{
		for(short loop = 8;loop < 18; ++loop)
		{
			TechTrees_Units_Unknown2a2[loop-8]->resize(Selections);
		}
		for(short loop = 7;loop < 17; ++loop)
		{
			TechTrees_Units_Unknown2b2[loop-7]->resize(Selections);
		}
	}
	TechTrees_Units_VerticalLine->resize(Selections);
	TechTrees_Units_LocationInAge->resize(Selections);
	TechTrees_Units_RequiredResearch->resize(Selections);
	TechTrees_Units_LineMode->resize(Selections);
	TechTrees_Units_EnablingResearch->resize(Selections);

	genie::UnitConnection * UnitConPointer;
	for(auto sel = Selections; sel--> 0;)
	{
		UnitConPointer = (genie::UnitConnection*)TechTrees_MainList_Units_List->GetClientData(Items.Item(sel));
		TTUnitConIDs[sel] = (UnitConPointer - (&GenieFile->TechTree.UnitConnections[0]));

		TechTrees_Units_ID->container[sel] = &UnitConPointer->ID;
		TechTrees_Units_Always2->container[sel] = &UnitConPointer->Unknown1;
		TechTrees_Units_UpperBuilding->container[sel] = &UnitConPointer->UpperBuilding;
		TechTrees_Units_RequiredResearches->container[sel] = &UnitConPointer->RequiredResearches;
		TechTrees_Units_Age->container[sel] = &UnitConPointer->Age;
		TechTrees_Units_UnitOrResearch1->container[sel] = &UnitConPointer->UnitOrResearch1;
		TechTrees_Units_UnitOrResearch2->container[sel] = &UnitConPointer->UnitOrResearch2;
		TechTrees_Units_Mode1->container[sel] = &UnitConPointer->Mode1;
		TechTrees_Units_Mode2->container[sel] = &UnitConPointer->Mode2;
		for(short loop = 0; loop < 8; ++loop)
		{
			TechTrees_Units_Unknown2a1[loop]->container[sel] = &UnitConPointer->Unknown2a[loop];
		}
		for(short loop = 0; loop < 7; ++loop)
		{
			TechTrees_Units_Unknown2b1[loop]->container[sel] = &UnitConPointer->Unknown2b[loop];
		}
		if(GenieVersion >= genie::GV_SWGB)
		{
			for(short loop = 8;loop < 18; ++loop)
			{
				TechTrees_Units_Unknown2a2[loop-8]->container[sel] = &UnitConPointer->Unknown2a[loop];
			}
			for(short loop = 7;loop < 17; ++loop)
			{
				TechTrees_Units_Unknown2b2[loop-7]->container[sel] = &UnitConPointer->Unknown2b[loop];
			}
		}
		TechTrees_Units_VerticalLine->container[sel] = &UnitConPointer->VerticalLine;
		TechTrees_Units_LocationInAge->container[sel] = &UnitConPointer->LocationInAge;
		TechTrees_Units_RequiredResearch->container[sel] = &UnitConPointer->RequiredResearch;
		TechTrees_Units_LineMode->container[sel] = &UnitConPointer->LineMode;
		TechTrees_Units_EnablingResearch->container[sel] = &UnitConPointer->EnablingResearch;
	}

	TechTrees_Units_ID->ChangeValue(lexical_cast<string>(UnitConPointer->ID));
	TechTrees_Units_ComboBox_ID->SetSelection(UnitConPointer->ID + 1);
	TechTrees_Units_Always2->ChangeValue(lexical_cast<string>((short)UnitConPointer->Unknown1));
	TechTrees_Units_UpperBuilding->ChangeValue(lexical_cast<string>(UnitConPointer->UpperBuilding));
	TechTrees_Units_ComboBox_UpperBuilding->SetSelection(UnitConPointer->UpperBuilding + 1);
	TechTrees_Units_RequiredResearches->ChangeValue(lexical_cast<string>(UnitConPointer->RequiredResearches));
	TechTrees_Units_Age->ChangeValue(lexical_cast<string>(UnitConPointer->Age));
	TechTrees_Units_UnitOrResearch1->ChangeValue(lexical_cast<string>(UnitConPointer->UnitOrResearch1));
	TechTrees_Units_UnitOrResearch2->ChangeValue(lexical_cast<string>(UnitConPointer->UnitOrResearch2));
	if(UnitConPointer->Mode1 == 1 || UnitConPointer->Mode1 == 2)
	{
		TechTrees_ComboBox_Unit[2]->Show(true);
		TechTrees_ComboBox_Research[2]->Show(false);
		TechTrees_ComboBox_Unit[2]->SetSelection(UnitConPointer->UnitOrResearch1 + 1);
		TechTrees_Units_Text_UnitOrResearch1->SetLabel("Unit/Building 1");
	}
	else if(UnitConPointer->Mode1 == 3)
	{
		TechTrees_ComboBox_Unit[2]->Show(false);
		TechTrees_ComboBox_Research[2]->Show(true);
		TechTrees_ComboBox_Research[2]->SetSelection(UnitConPointer->UnitOrResearch1 + 1);
		TechTrees_Units_Text_UnitOrResearch1->SetLabel("Research 1");
	}
	else
	{
		TechTrees_ComboBox_Unit[2]->Show(false);
		TechTrees_ComboBox_Research[2]->Show(false);
		TechTrees_Units_Text_UnitOrResearch1->SetLabel("Select Mode 1");
	}
	if(UnitConPointer->Mode2 == 1 || UnitConPointer->Mode2 == 2)
	{
		TechTrees_ComboBox_Unit[3]->Show(true);
		TechTrees_ComboBox_Research[3]->Show(false);
		TechTrees_ComboBox_Unit[3]->SetSelection(UnitConPointer->UnitOrResearch2 + 1);
		TechTrees_Units_Text_UnitOrResearch2->SetLabel("Unit/Building 2");
	}
	else if(UnitConPointer->Mode2 == 3)
	{
		TechTrees_ComboBox_Unit[3]->Show(false);
		TechTrees_ComboBox_Research[3]->Show(true);
		TechTrees_ComboBox_Research[3]->SetSelection(UnitConPointer->UnitOrResearch2 + 1);
		TechTrees_Units_Text_UnitOrResearch2->SetLabel("Research 2");
	}
	else
	{
		TechTrees_ComboBox_Unit[3]->Show(false);
		TechTrees_ComboBox_Research[3]->Show(false);
		TechTrees_Units_Text_UnitOrResearch2->SetLabel("Select Mode 2");
	}
	TechTrees_Units_Mode1->ChangeValue(lexical_cast<string>(UnitConPointer->Mode1));
	TechTrees_ComboBox_Modes[2]->SetSelection(0);
	TechTrees_ComboBox_Modes[2]->SetSelection(UnitConPointer->Mode1);
	TechTrees_Units_Mode2->ChangeValue(lexical_cast<string>(UnitConPointer->Mode2));
	TechTrees_ComboBox_Modes[3]->SetSelection(0);
	TechTrees_ComboBox_Modes[3]->SetSelection(UnitConPointer->Mode2);
	for(short loop = 0; loop < 8; ++loop)
	{
		TechTrees_Units_Unknown2a1[loop]->ChangeValue(lexical_cast<string>(UnitConPointer->Unknown2a[loop]));
	}
	for(short loop = 0; loop < 7; ++loop)
	{
		TechTrees_Units_Unknown2b1[loop]->ChangeValue(lexical_cast<string>(UnitConPointer->Unknown2b[loop]));
	}
	if(GenieVersion >= genie::GV_SWGB)
	{
		for(short loop = 8;loop < 18; ++loop)
		{
			TechTrees_Units_Unknown2a2[loop-8]->ChangeValue(lexical_cast<string>(UnitConPointer->Unknown2a[loop]));
		}
		for(short loop = 7;loop < 17; ++loop)
		{
			TechTrees_Units_Unknown2b2[loop-7]->ChangeValue(lexical_cast<string>(UnitConPointer->Unknown2b[loop]));
		}
	}
	TechTrees_Units_VerticalLine->ChangeValue(lexical_cast<string>(UnitConPointer->VerticalLine));
	TechTrees_Units_LocationInAge->ChangeValue(lexical_cast<string>(UnitConPointer->LocationInAge));
	TechTrees_Units_RequiredResearch->ChangeValue(lexical_cast<string>(UnitConPointer->RequiredResearch));
	TechTrees_Units_ComboBox_RequiredResearch->SetSelection(UnitConPointer->RequiredResearch + 1);
	TechTrees_Units_LineMode->ChangeValue(lexical_cast<string>(UnitConPointer->LineMode));
	TechTrees_Units_EnablingResearch->ChangeValue(lexical_cast<string>(UnitConPointer->EnablingResearch));
	TechTrees_Units_ComboBox_EnablingResearch->SetSelection(UnitConPointer->EnablingResearch + 1);

	ListTTUnitUnits();

	TechTrees_Main->Layout();
	TechTrees_Scroller->GetSizer()->FitInside(TechTrees_Scroller);
}

void AGE_Frame::OnTTUnitAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->TechTree.UnitConnections);
	ListTTUnits();
}

void AGE_Frame::OnTTUnitInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->TechTree.UnitConnections, TTUnitConIDs[0]);
	ListTTUnits();
}

void AGE_Frame::OnTTUnitDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.UnitConnections, TTUnitConIDs);
	ListTTUnits();
}

void AGE_Frame::OnTTUnitCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.UnitConnections, TTUnitConIDs, copies->TTUnitCon);
}

void AGE_Frame::OnTTUnitPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->TechTree.UnitConnections, TTUnitConIDs[0], copies->TTUnitCon);
	ListTTUnits();
}

void AGE_Frame::OnTTUnitPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->TechTree.UnitConnections, TTUnitConIDs[0], copies->TTUnitCon);
	ListTTUnits();
}

void AGE_Frame::OnTTUnitUnitSearch(wxCommandEvent &Event)
{
	ListTTUnitUnits();
}

void AGE_Frame::ListTTUnitUnits()
{
	searchText = TechTrees_DataList_Units_Search_Units->GetValue().Lower();
	excludeText = TechTrees_DataList_Units_Search_R_Units->GetValue().Lower();

	auto Selections = TechTrees_DataList_Units_List_Units->GetSelections(Items);
	TechTrees_DataList_Units_List_Units->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineUnitName(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_DataList_Units_List_Units->Append(Name, (void*)&GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units[loop]);
		}
	}
	ListingFix(Selections, TechTrees_DataList_Units_List_Units);

	wxCommandEvent E;
	OnTTUnitUnitSelect(E);
}

void AGE_Frame::OnTTUnitUnitSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Units_List_Units->GetSelections(Items);
	if(Selections > 0)
	{
		TTUnitUnitIDs.resize(Selections);
		TechTrees_Units_Unit->resize(Selections);

		int32_t * UnitPointer;
		for(auto loop = Selections; loop--> 0;)
		{
			UnitPointer = (int32_t*)TechTrees_DataList_Units_List_Units->GetClientData(Items.Item(loop));
			TTUnitUnitIDs[loop] = (UnitPointer - (&GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units[0]));
			TechTrees_Units_Unit->container[loop] = UnitPointer;
		}

		TechTrees_Units_Unit->ChangeValue(lexical_cast<string>(*UnitPointer));
		TechTrees_Units_ComboBox_Unit->SetSelection(*UnitPointer + 1);
	}
	else
	{
		TechTrees_Units_Unit->ChangeValue("0");
		TechTrees_Units_ComboBox_Unit->SetSelection(0);
	}
}

void AGE_Frame::OnTTUnitUnitAdd(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units);
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Units_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs[0]);
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Units_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs);
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Units_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs, copies->TTUnitUnit);
}

void AGE_Frame::OnTTUnitUnitPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Units_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs[0], copies->TTUnitUnit);
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Units_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs[0], copies->TTUnitUnit);
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitCopyToUnits(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTUnitConIDs.size(); ++loop)
	{
		GenieFile->TechTree.UnitConnections[TTUnitConIDs[loop]].Units = GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units;
	}
}

string AGE_Frame::GetTTResearchName(short Index)
{
	string Name = "";

	short Selection[2];
	for(short loop = 0; loop < 2; ++loop)
	Selection[loop] = TechTrees_MainList_Researches_SearchFilters[loop]->GetSelection();

	if(Selection[0] == 0)	// Normal Name
	{
		// Do nothing!
	}
	else for(short loop = 0; loop < 2; ++loop)
	{
		switch(Selection[loop])
		{
			case 1: // Upper Building
				Name += "UB "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].UpperBuilding);
				break;
			case 2: // Required Researches
				Name += "RR "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].RequiredResearches);
				break;
			case 3: // Age
				Name += "A "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].Age);
				break;
			case 4: // Upper Research
				Name += "UR "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].UpperResearch);
				break;
			case 5: // Line Mode
				Name += "LM "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].LineMode);
				break;
			case 6: // Vertical Line Number
				Name += "VL "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].VerticalLine);
				break;
			case 7: // Location In Age
				Name += "LA "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].LocationInAge);
				break;
			case 8: // First Age Mode
				Name += "FA "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].Unknown9);
				break;
		}
		Name += ", ";
		if(Selection[loop+1] < 1) break;
	}

	Name += lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].ID)+" ";
	if(!LangDLLstring(GenieFile->Researchs[GenieFile->TechTree.ResearchConnections[Index].ID].LanguageDLLName, 2).empty())
	{
		Name += LangDLLstring(GenieFile->Researchs[GenieFile->TechTree.ResearchConnections[Index].ID].LanguageDLLName, 64);
	}
	else if(!GenieFile->Researchs[GenieFile->TechTree.ResearchConnections[Index].ID].Name.empty())
	{
		Name += GenieFile->Researchs[GenieFile->TechTree.ResearchConnections[Index].ID].Name;
	}
	else
	{
		Name += "New Research";
	}
	return Name;
}

void AGE_Frame::OnTTResearchSearch(wxCommandEvent &Event)
{
	ListTTResearches();
}

void AGE_Frame::ListTTResearches()
{
	searchText = TechTrees_MainList_Researches_Search->GetValue().Lower();
	excludeText = TechTrees_MainList_Researches_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	UseAnd[loop] = TechTrees_MainList_Researches_UseAnd[loop]->GetValue();

	auto Selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	TechTrees_MainList_Researches_List->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.ResearchConnections.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetTTResearchName(loop);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_MainList_Researches_List->Append(Name, (void*)&GenieFile->TechTree.ResearchConnections[loop]);
		}
	}

	ListingFix(Selections, TechTrees_MainList_Researches_List);

	for(short loop = 0; loop < 2; ++loop)
	UseAnd[loop] = false;

	wxCommandEvent E;
	OnTTResearchSelect(E);
}

void AGE_Frame::OnTTResearchSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(Selections < 1) return;

	TTResConIDs.resize(Selections);
	TechTrees_Researches_ID->resize(Selections);
	TechTrees_Researches_Always2->resize(Selections);
	TechTrees_Researches_UpperBuilding->resize(Selections);
	TechTrees_Researches_RequiredResearches->resize(Selections);
	TechTrees_Researches_Age->resize(Selections);
	TechTrees_Researches_UpperResearch->resize(Selections);
	TechTrees_Researches_LineMode->resize(Selections);
	for(short loop = 0; loop < 9; ++loop)
	{
		TechTrees_Researches_Unknown2a1[loop]->resize(Selections);
	}
	for(short loop = 0; loop < 8; ++loop)
	{
		TechTrees_Researches_Unknown2b1[loop]->resize(Selections);
	}
	if(GenieVersion >= genie::GV_SWGB)
	{
		for(short loop = 9;loop < 19; ++loop)
		{
			TechTrees_Researches_Unknown2a2[loop-9]->resize(Selections);
		}
		for(short loop = 8;loop < 18; ++loop)
		{
			TechTrees_Researches_Unknown2b2[loop-8]->resize(Selections);
		}
	}
	TechTrees_Researches_VerticalLine->resize(Selections);
	TechTrees_Researches_LocationInAge->resize(Selections);
	TechTrees_Researches_Unknown9->resize(Selections);

	genie::ResearchConnection * ResearchConPointer;
	for(auto sel = Selections; sel--> 0;)
	{
		ResearchConPointer = (genie::ResearchConnection*)TechTrees_MainList_Researches_List->GetClientData(Items.Item(sel));
		TTResConIDs[sel] = (ResearchConPointer - (&GenieFile->TechTree.ResearchConnections[0]));

		TechTrees_Researches_ID->container[sel] = &ResearchConPointer->ID;
		TechTrees_Researches_Always2->container[sel] = &ResearchConPointer->Unknown1;
		TechTrees_Researches_UpperBuilding->container[sel] = &ResearchConPointer->UpperBuilding;
		TechTrees_Researches_RequiredResearches->container[sel] = &ResearchConPointer->RequiredResearches;
		TechTrees_Researches_Age->container[sel] = &ResearchConPointer->Age;
		TechTrees_Researches_UpperResearch->container[sel] = &ResearchConPointer->UpperResearch;
		TechTrees_Researches_LineMode->container[sel] = &ResearchConPointer->LineMode;
		for(short loop = 0; loop < 9; ++loop)
		{
			TechTrees_Researches_Unknown2a1[loop]->container[sel] = &ResearchConPointer->Unknown2a[loop];
		}
		for(short loop = 0; loop < 8; ++loop)
		{
			TechTrees_Researches_Unknown2b1[loop]->container[sel] = &ResearchConPointer->Unknown2b[loop];
		}
		if(GenieVersion >= genie::GV_SWGB)
		{
			for(short loop = 9;loop < 19; ++loop)
			{
				TechTrees_Researches_Unknown2a2[loop-9]->container[sel] = &ResearchConPointer->Unknown2a[loop];
			}
			for(short loop = 8;loop < 18; ++loop)
			{
				TechTrees_Researches_Unknown2b2[loop-8]->container[sel] = &ResearchConPointer->Unknown2b[loop];
			}
		}
		TechTrees_Researches_VerticalLine->container[sel] = &ResearchConPointer->VerticalLine;
		TechTrees_Researches_LocationInAge->container[sel] = &ResearchConPointer->LocationInAge;
		TechTrees_Researches_Unknown9->container[sel] = &ResearchConPointer->Unknown9;
	}

	TechTrees_Researches_ID->ChangeValue(lexical_cast<string>(ResearchConPointer->ID));
	TechTrees_Researches_ComboBox_ID->SetSelection(ResearchConPointer->ID + 1);
	TechTrees_Researches_Always2->ChangeValue(lexical_cast<string>((short)ResearchConPointer->Unknown1));
	TechTrees_Researches_UpperBuilding->ChangeValue(lexical_cast<string>(ResearchConPointer->UpperBuilding));
	TechTrees_Researches_ComboBox_UpperBuilding->SetSelection(ResearchConPointer->UpperBuilding + 1);
	TechTrees_Researches_RequiredResearches->ChangeValue(lexical_cast<string>(ResearchConPointer->RequiredResearches));
	TechTrees_Researches_Age->ChangeValue(lexical_cast<string>(ResearchConPointer->Age));
	TechTrees_Researches_UpperResearch->ChangeValue(lexical_cast<string>(ResearchConPointer->UpperResearch));
	TechTrees_Researches_ComboBox_UpperResearch->SetSelection(ResearchConPointer->UpperResearch + 1);
	TechTrees_Researches_LineMode->ChangeValue(lexical_cast<string>(ResearchConPointer->LineMode));
	for(short loop = 0; loop < 9; ++loop)
	{
		TechTrees_Researches_Unknown2a1[loop]->ChangeValue(lexical_cast<string>(ResearchConPointer->Unknown2a[loop]));
	}
	for(short loop = 0; loop < 8; ++loop)
	{
		TechTrees_Researches_Unknown2b1[loop]->ChangeValue(lexical_cast<string>(ResearchConPointer->Unknown2b[loop]));
	}
	if(GenieVersion >= genie::GV_SWGB)
	{
		for(short loop = 9;loop < 19; ++loop)
		{
			TechTrees_Researches_Unknown2a2[loop-9]->ChangeValue(lexical_cast<string>(ResearchConPointer->Unknown2a[loop]));
		}
		for(short loop = 8;loop < 18; ++loop)
		{
			TechTrees_Researches_Unknown2b2[loop-8]->ChangeValue(lexical_cast<string>(ResearchConPointer->Unknown2b[loop]));
		}
	}
	TechTrees_Researches_VerticalLine->ChangeValue(lexical_cast<string>(ResearchConPointer->VerticalLine));
	TechTrees_Researches_LocationInAge->ChangeValue(lexical_cast<string>(ResearchConPointer->LocationInAge));
	TechTrees_Researches_Unknown9->ChangeValue(lexical_cast<string>(ResearchConPointer->Unknown9));

	ListTTResearchBuildings();
	ListTTResearchUnits();
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->TechTree.ResearchConnections);
	ListTTResearches();
}

void AGE_Frame::OnTTResearchInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->TechTree.ResearchConnections, TTResConIDs[0]);
	ListTTResearches();
}

void AGE_Frame::OnTTResearchDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.ResearchConnections, TTResConIDs);
	ListTTResearches();
}

void AGE_Frame::OnTTResearchCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.ResearchConnections, TTResConIDs, copies->TTResCon);
}

void AGE_Frame::OnTTResearchPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->TechTree.ResearchConnections, TTResConIDs[0], copies->TTResCon);
	ListTTResearches();
}

void AGE_Frame::OnTTResearchPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->TechTree.ResearchConnections, TTResConIDs[0], copies->TTResCon);
	ListTTResearches();
}

void AGE_Frame::OnTTResearchBuildingSearch(wxCommandEvent &Event)
{
	ListTTResearchBuildings();
}

void AGE_Frame::ListTTResearchBuildings()
{
	searchText = TechTrees_DataList_Researches_Search_Buildings->GetValue().Lower();
	excludeText = TechTrees_DataList_Researches_Search_R_Buildings->GetValue().Lower();

	auto Selections = TechTrees_DataList_Researches_List_Buildings->GetSelections(Items);
	TechTrees_DataList_Researches_List_Buildings->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetBuildingName(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_DataList_Researches_List_Buildings->Append(Name, (void*)&GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings[loop]);
		}
	}
	ListingFix(Selections, TechTrees_DataList_Researches_List_Buildings);

	wxCommandEvent E;
	OnTTResearchBuildingSelect(E);
}

void AGE_Frame::OnTTResearchBuildingSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Buildings->GetSelections(Items);
	if(Selections > 0)
	{
		TTResBuildIDs.resize(Selections);
		TechTrees_Researches_Building->resize(Selections);

		int32_t * BuildingPointer;
		for(auto loop = Selections; loop--> 0;)
		{
			BuildingPointer = (int32_t*)TechTrees_DataList_Researches_List_Buildings->GetClientData(Items.Item(loop));
			TTResBuildIDs[loop] = (BuildingPointer - (&GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings[0]));
			TechTrees_Researches_Building->container[loop] = BuildingPointer;
		}

		TechTrees_Researches_Building->ChangeValue(lexical_cast<string>(*BuildingPointer));
		TechTrees_Researches_ComboBox_Building->SetSelection(*BuildingPointer + 1);
	}
	else
	{
		TechTrees_Researches_Building->ChangeValue("0");
		TechTrees_Researches_ComboBox_Building->SetSelection(0);
	}
}

void AGE_Frame::OnTTResearchBuildingAdd(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings);
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs[0]);
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs);
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs, copies->TTResBuild);
}

void AGE_Frame::OnTTResearchBuildingPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs[0], copies->TTResBuild);
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Buildings->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs[0], copies->TTResBuild);
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingCopyToResearches(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTResConIDs.size(); ++loop)
	{
		GenieFile->TechTree.ResearchConnections[TTResConIDs[loop]].Buildings = GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings;
	}
}

void AGE_Frame::OnTTResearchUnitSearch(wxCommandEvent &Event)
{
	ListTTResearchUnits();
}

void AGE_Frame::ListTTResearchUnits()
{
	searchText = TechTrees_DataList_Researches_Search_Units->GetValue().Lower();
	excludeText = TechTrees_DataList_Researches_Search_R_Units->GetValue().Lower();

	auto Selections = TechTrees_DataList_Researches_List_Units->GetSelections(Items);
	TechTrees_DataList_Researches_List_Units->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineUnitName(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_DataList_Researches_List_Units->Append(Name, (void*)&GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units[loop]);
		}
	}
	ListingFix(Selections, TechTrees_DataList_Researches_List_Units);

	wxCommandEvent E;
	OnTTResearchUnitSelect(E);
}

void AGE_Frame::OnTTResearchUnitSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Units->GetSelections(Items);
	if(Selections > 0)
	{
		TTResUnitIDs.resize(Selections);
		TechTrees_Researches_Unit->resize(Selections);

		int32_t * UnitPointer;
		for(auto loop = Selections; loop--> 0;)
		{
			UnitPointer = (int32_t*)TechTrees_DataList_Researches_List_Units->GetClientData(Items.Item(loop));
			TTResUnitIDs[loop] = (UnitPointer - (&GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units[0]));
			TechTrees_Researches_Unit->container[loop] = UnitPointer;
		}

		TechTrees_Researches_Unit->ChangeValue(lexical_cast<string>(*UnitPointer));
		TechTrees_Researches_ComboBox_Unit->SetSelection(*UnitPointer + 1);
	}
	else
	{
		TechTrees_Researches_Unit->ChangeValue("0");
		TechTrees_Researches_ComboBox_Unit->SetSelection(0);
	}
}

void AGE_Frame::OnTTResearchUnitAdd(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units);
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs[0]);
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs);
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs, copies->TTResUnit);
}

void AGE_Frame::OnTTResearchUnitPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs[0], copies->TTResUnit);
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Units->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs[0], copies->TTResUnit);
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitCopyToResearches(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTResConIDs.size(); ++loop)
	{
		GenieFile->TechTree.ResearchConnections[TTResConIDs[loop]].Units = GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units;
	}
}

void AGE_Frame::OnTTResearchResearchSearch(wxCommandEvent &Event)
{
	ListTTResearchResearches();
}

void AGE_Frame::ListTTResearchResearches()
{
	searchText = TechTrees_DataList_Researches_Search_Researches->GetValue().Lower();
	excludeText = TechTrees_DataList_Researches_Search_R_Researches->GetValue().Lower();

	auto Selections = TechTrees_DataList_Researches_List_Researches->GetSelections(Items);
	TechTrees_DataList_Researches_List_Researches->Clear();

	for(short loop = 0; loop < GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetSimpleResearchName(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_DataList_Researches_List_Researches->Append(Name, (void*)&GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches[loop]);
		}
	}
	ListingFix(Selections, TechTrees_DataList_Researches_List_Researches);

	wxCommandEvent E;
	OnTTResearchResearchSelect(E);
}

void AGE_Frame::OnTTResearchResearchSelect(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Researches->GetSelections(Items);
	if(Selections > 0)
	{
		TTResResIDs.resize(Selections);
		TechTrees_Researches_Research->resize(Selections);

		int32_t * ResearchPointer;
		for(auto loop = Selections; loop--> 0;)
		{
			ResearchPointer = (int32_t*)TechTrees_DataList_Researches_List_Researches->GetClientData(Items.Item(loop));
			TTResResIDs[loop] = (ResearchPointer - (&GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches[0]));
			TechTrees_Researches_Research->container[loop] = ResearchPointer;
		}

		TechTrees_Researches_Research->ChangeValue(lexical_cast<string>(*ResearchPointer));
		TechTrees_Researches_ComboBox_Research->SetSelection(*ResearchPointer + 1);
	}
	else
	{
		TechTrees_Researches_Research->ChangeValue("0");
		TechTrees_Researches_ComboBox_Research->SetSelection(0);
	}
}

void AGE_Frame::OnTTResearchResearchAdd(wxCommandEvent &Event)
{
	auto Selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches);
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs[0]);
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchDelete(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs);
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchCopy(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs, copies->TTResRes);
}

void AGE_Frame::OnTTResearchResearchPaste(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs[0], copies->TTResRes);
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchPasteInsert(wxCommandEvent &Event)
{
	auto Selections = TechTrees_DataList_Researches_List_Researches->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs[0], copies->TTResRes);
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchCopyToResearches(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTResConIDs.size(); ++loop)
	{
		GenieFile->TechTree.ResearchConnections[TTResConIDs[loop]].Researches = GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches;
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

	General_Holder_Variables2 = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Technology Tree Related?");
	General_Grid_Variables2 = new wxGridSizer(8, 5, 5);
	for(short loop = 0; loop < General_TTUnknown.size(); ++loop)
	{
		General_Holder_TTUnknown[loop] = new wxBoxSizer(wxVERTICAL);
		General_Text_TTUnknown[loop] = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unknown "+lexical_cast<string>(loop+1), wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		General_TTUnknown[loop] = new TextCtrl_Long(TechTrees_Scroller);
	}
	General_TTUnknown[7]->SetToolTip("In the file this is\nright after technology tree ages and\nbefore rest of the tech tree data");

	TechTrees_Ages = new wxStaticBoxSizer(wxHORIZONTAL, TechTrees_Scroller, "Ages");
	TechTrees_Buildings = new wxStaticBoxSizer(wxHORIZONTAL, TechTrees_Scroller, "Buildings");
	TechTrees_Units = new wxStaticBoxSizer(wxHORIZONTAL, TechTrees_Scroller, "Units");
	TechTrees_Researches = new wxStaticBoxSizer(wxHORIZONTAL, TechTrees_Scroller, "Researches");
	TechTrees_MainList_Ages = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Buildings = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Units = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Researches = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Ages_Search = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Ages_Search_R = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Ages_List = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 200), 0, NULL, wxLB_EXTENDED);
	TechTrees_MainList_Ages_Buttons = new wxGridSizer(3, 0, 0);
	TechTrees_MainList_Ages_Add = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Insert = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Delete = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Copy = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Paste = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_PasteInsert = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	TechTrees_Ages_Holder_ID = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Text_ID = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Age Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_ID = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Ages_Holder_Unknown4 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Text_Unknown4 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Second Age Number?", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_Unknown4 = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Ages_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Text_Unknown1 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_Unknown1 = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Ages_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Text_Unknown3 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_Unknown3 = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Ages_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Text_Unknown2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Always 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_Unknown2 = new TextCtrl_Byte(TechTrees_Scroller);
	TechTrees_Data_Ages = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Ages1 = new wxGridSizer(5, 5, 5);
	TechTrees_DataListHolder_Ages = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_DataList_Ages_Buildings = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Buildings");
	TechTrees_DataList_Ages_Search_Buildings = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Ages_Search_R_Buildings = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Ages_List_Buildings = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_Ages_Holder_Building = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Building = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Ages_ComboBox_Building = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Ages_Building);
	TechTrees_DataList_Ages_Buttons_Buildings = new wxGridSizer(3, 0, 0);
	TechTrees_DataList_Ages_Add_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Insert_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Delete_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Copy_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Paste_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_PasteInsert_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_CopyToAges_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy all to selected ages", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Units = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Units");
	TechTrees_DataList_Ages_Search_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Ages_Search_R_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Ages_List_Units = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_Ages_Holder_Unit = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Unit = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Ages_ComboBox_Unit = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Ages_Unit);
	TechTrees_DataList_Ages_Buttons_Units = new wxGridSizer(3, 0, 0);
	TechTrees_DataList_Ages_Add_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Insert_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Delete_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Copy_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Paste_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_PasteInsert_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_CopyToAges_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy all to selected ages", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Researches = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Researches");
	TechTrees_DataList_Ages_Search_Researches = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Ages_Search_R_Researches = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Ages_List_Researches = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_Ages_Holder_Research = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Research = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Ages_ComboBox_Research = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Ages_Research);
	TechTrees_DataList_Ages_Buttons_Researches = new wxGridSizer(3, 0, 0);
	TechTrees_DataList_Ages_Add_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Insert_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Delete_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Copy_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_Paste_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_PasteInsert_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Ages_CopyToAges_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy all to selected ages", wxDefaultPosition, wxSize(5, 20));
	TechTrees_Ages_Holder_Zeroes = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Grid_Zeroes1 = new wxGridSizer(10, 0, 0);
	TechTrees_Ages_Grid_Zeroes2 = new wxGridSizer(10, 0, 0);
	TechTrees_Ages_Text_Zeroes = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 49; ++loop)
	TechTrees_Ages_Zeroes1[loop] = new TextCtrl_Short(TechTrees_Scroller);
	for(short loop = 0; loop < 50; ++loop)
	TechTrees_Ages_Zeroes2[loop] = new TextCtrl_Short(TechTrees_Scroller);

	TechTrees_MainList_Buildings_Search = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Buildings_UseAnd[0] = new wxCheckBox(TechTrees_Scroller, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	TechTrees_MainList_Buildings_Search_R = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Buildings_UseAnd[1] = new wxCheckBox(TechTrees_Scroller, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	for(short loop = 0; loop < 2; ++loop)
	{
		TechTrees_MainList_Buildings_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		TechTrees_MainList_Buildings_SearchFilters[loop] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	TechTrees_MainList_Buildings_List = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_MainList_Buildings_Buttons = new wxGridSizer(3, 0, 0);
	TechTrees_MainList_Buildings_Add = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Insert = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Delete = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Copy = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Paste = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_PasteInsert = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	TechTrees_Buildings_Holder_ID = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_ID = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Building Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_ID = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Buildings_ComboBox_ID = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Buildings_ID);
	TechTrees_Buildings_Holder_Age = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_Age = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Age", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_Age = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Buildings_Holder_Connections = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_Connections = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Connections *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_Connections = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Buildings_Connections->SetToolTip("5 One or more connections\n6 No connections");
	TechTrees_Buildings_Holder_EnablingResearch = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_EnablingResearch = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Enabling Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_EnablingResearch = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Buildings_EnablingResearch->SetToolTip("Makes available\nUsed by buildings, which need a research to be available");
	TechTrees_Buildings_ComboBox_EnablingResearch = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Buildings_EnablingResearch);
	TechTrees_Buildings_Holder_RequiredResearches = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_RequiredResearches = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Required Researches *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_RequiredResearches = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Buildings_RequiredResearches->SetToolTip("Minimum amount of researches that need to be researched for this to be available");
	TechTrees_Holder_UnitAndResearch1 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Holder_UnitAndResearch2 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Holder_UnitAndResearch3 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Holder_UnitAndResearch4 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Buildings_Holder_UnitOrResearch1 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_UnitOrResearch1 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unit or Research 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_UnitOrResearch1 = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_ComboBox_Unit[0] = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Buildings_UnitOrResearch1);
	TechTrees_ComboBox_Research[0] = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Buildings_UnitOrResearch1);
	TechTrees_Buildings_Holder_UnitOrResearch2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_UnitOrResearch2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unit or Research 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_UnitOrResearch2 = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_ComboBox_Unit[1] = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Buildings_UnitOrResearch2);
	TechTrees_ComboBox_Research[1] = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Buildings_UnitOrResearch2);
	TechTrees_Buildings_Holder_Mode1 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_Mode1 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Mode 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_Mode1 = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_ComboBox_Modes[0] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	TechTrees_Buildings_Holder_Mode2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_Mode2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Mode 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_Mode2 = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_ComboBox_Modes[1] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	TechTrees_Buildings_Holder_Always2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Text_Always2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Always 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_Always2 = new TextCtrl_Byte(TechTrees_Scroller);
	TechTrees_Buildings_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Grid_Unknown3 = new wxGridSizer(11, 0, 0);
	TechTrees_Buildings_Text_Unknown3 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Some Sequence *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 11; ++loop)
	TechTrees_Buildings_Unknown3[loop] = new TextCtrl_Byte(TechTrees_Scroller);
	TechTrees_Buildings_Unknown3[2]->SetToolTip("Units+techs in 1st Age?");
	TechTrees_Buildings_Unknown3[3]->SetToolTip("Units+techs in 2nd Age?");
	TechTrees_Buildings_Unknown3[4]->SetToolTip("Units+techs in 3rd Age?");
	TechTrees_Buildings_Unknown3[5]->SetToolTip("Units+techs in 4th Age?");
	TechTrees_Buildings_Unknown3[7]->SetToolTip("Units+techs on first line in 1st Age?");
	TechTrees_Buildings_Unknown3[8]->SetToolTip("Units+techs on first line in 2nd Age?");
	TechTrees_Buildings_Unknown3[9]->SetToolTip("Units+techs on first line in 3rd Age?");
	TechTrees_Buildings_Unknown3[10]->SetToolTip("Units+techs on first line in 4th Age?");
	TechTrees_Data_Buildings = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Buildings1 = new wxGridSizer(5, 5, 5);
	TechTrees_DataListHolder_Buildings = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_DataList_Buildings_Buildings = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Buildings");
	TechTrees_DataList_Buildings_Search_Buildings = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Buildings_Search_R_Buildings = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Buildings_List_Buildings = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_Buildings_Holder_Building = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Building = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Buildings_ComboBox_Building = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Buildings_Building);
	TechTrees_DataList_Buildings_Buttons_Buildings = new wxGridSizer(3, 0, 0);
	TechTrees_DataList_Buildings_Add_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Insert_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Delete_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Copy_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Paste_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_PasteInsert_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_CopyToBuildings_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy all to selected buildings", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Units = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Units");
	TechTrees_DataList_Buildings_Search_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Buildings_Search_R_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Buildings_List_Units = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_Buildings_Holder_Unit = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Unit = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Buildings_ComboBox_Unit = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Buildings_Unit);
	TechTrees_DataList_Buildings_Buttons_Units = new wxGridSizer(3, 0, 0);
	TechTrees_DataList_Buildings_Add_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Insert_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Delete_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Copy_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Paste_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_PasteInsert_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_CopyToBuildings_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy all to selected buildings", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Researches = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Researches");
	TechTrees_DataList_Buildings_Search_Researches = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Buildings_Search_R_Researches = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Buildings_List_Researches = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_Buildings_Holder_Research = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Research = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Buildings_ComboBox_Research = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Buildings_Research);
	TechTrees_DataList_Buildings_Buttons_Researches = new wxGridSizer(3, 0, 0);
	TechTrees_DataList_Buildings_Add_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Insert_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Delete_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Copy_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_Paste_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_PasteInsert_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Buildings_CopyToBuildings_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy all to selected buildings", wxDefaultPosition, wxSize(5, 20));
	TechTrees_Buildings_Holder_Unknown2a = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Grid_Unknown2a1 = new wxGridSizer(10, 0, 0);
	TechTrees_Buildings_Grid_Unknown2a2 = new wxGridSizer(10, 0, 0);
	TechTrees_Buildings_Text_Unknown2a = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 8; ++loop)
	TechTrees_Buildings_Unknown2a1[loop] = new TextCtrl_Long(TechTrees_Scroller);
	for(short loop = 0; loop < 10; ++loop)
	TechTrees_Buildings_Unknown2a2[loop] = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Buildings_Holder_Unknown2b = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Grid_Unknown2b1 = new wxGridSizer(10, 0, 0);
	TechTrees_Buildings_Grid_Unknown2b2 = new wxGridSizer(10, 0, 0);
	TechTrees_Buildings_Text_Unknown2b = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 7; ++loop)
	TechTrees_Buildings_Unknown2b1[loop] = new TextCtrl_Long(TechTrees_Scroller);
	for(short loop = 0; loop < 10; ++loop)
	TechTrees_Buildings_Unknown2b2[loop] = new TextCtrl_Long(TechTrees_Scroller);

	TechTrees_MainList_Units_Search = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Units_UseAnd[0] = new wxCheckBox(TechTrees_Scroller, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	TechTrees_MainList_Units_Search_R = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Units_UseAnd[1] = new wxCheckBox(TechTrees_Scroller, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	for(short loop = 0; loop < 2; ++loop)
	{
		TechTrees_MainList_Units_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		TechTrees_MainList_Units_SearchFilters[loop] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	TechTrees_MainList_Units_List = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_MainList_Units_Buttons = new wxGridSizer(3, 0, 0);
	TechTrees_MainList_Units_Add = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Insert = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Delete = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Copy = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Paste = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_PasteInsert = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	TechTrees_Units_Holder_ID = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_ID = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unit Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_ID = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Units_ComboBox_ID = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Units_ID);
	TechTrees_Units_Holder_UpperBuilding = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_UpperBuilding = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Upper Building", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_UpperBuilding = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Units_ComboBox_UpperBuilding = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Units_UpperBuilding);
	TechTrees_Units_Holder_Age = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_Age = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Age", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_Age = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Units_Holder_LocationInAge = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_LocationInAge = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Location In Age *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_LocationInAge = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Units_LocationInAge->SetToolTip("1 First\n2 Second");
	TechTrees_Units_Holder_LineMode = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_LineMode = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Line Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_LineMode = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Units_LineMode->SetToolTip("2 First in vertical line\n3 Not first");
	TechTrees_Units_Holder_UnitOrResearch1 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_UnitOrResearch1 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unit or Research 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_UnitOrResearch1 = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_ComboBox_Unit[2] = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Units_UnitOrResearch1);
	TechTrees_ComboBox_Research[2] = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Units_UnitOrResearch1);
	TechTrees_Units_Holder_UnitOrResearch2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_UnitOrResearch2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Unit or Research 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_UnitOrResearch2 = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_ComboBox_Unit[3] = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Units_UnitOrResearch2);
	TechTrees_ComboBox_Research[3] = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Units_UnitOrResearch2);
	TechTrees_Units_Holder_Mode1 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_Mode1 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Mode 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_Mode1 = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_ComboBox_Modes[2] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	TechTrees_Units_Holder_Mode2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_Mode2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Mode 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_Mode2 = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_ComboBox_Modes[3] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	TechTrees_Units_Holder_VerticalLine = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_VerticalLine = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Vertical Line Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_VerticalLine = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Units_Holder_RequiredResearches = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_RequiredResearches = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Required Researches *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_RequiredResearches = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Units_RequiredResearches->SetToolTip("Minimum amount of researches that need to be researched for this to be available");
	TechTrees_Units_Holder_EnablingResearch = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_EnablingResearch = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Enabling Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_EnablingResearch = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Units_EnablingResearch->SetToolTip("Makes available\nUsed by units, which need a research to be available");
	TechTrees_Units_ComboBox_EnablingResearch = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Units_EnablingResearch);
	TechTrees_Units_Holder_RequiredResearch = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_RequiredResearch = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Required Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_RequiredResearch = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Units_RequiredResearch->SetToolTip("Upgrades unit\nUsed by units, which aren't first in upgrade line");
	TechTrees_Units_ComboBox_RequiredResearch = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Units_RequiredResearch);
	TechTrees_Units_Holder_Always2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Text_Always2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Always 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_Always2 = new TextCtrl_Byte(TechTrees_Scroller);
	TechTrees_Data_Units = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Units1 = new wxGridSizer(5, 5, 5);
	TechTrees_DataListHolder_Units = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_DataList_Units_Units = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Units");
	TechTrees_DataList_Units_Search_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Units_Search_R_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Units_List_Units = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_Units_Holder_Unit = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Unit = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Units_ComboBox_Unit = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Units_Unit);
	TechTrees_DataList_Units_Buttons_Units = new wxGridSizer(3, 0, 0);
	TechTrees_DataList_Units_Add_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Units_Insert_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Units_Delete_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Units_Copy_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Units_Paste_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Units_PasteInsert_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Units_CopyToUnits_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(5, 20));
	TechTrees_Units_Holder_Unknown2a = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Grid_Unknown2a1 = new wxGridSizer(10, 0, 0);
	TechTrees_Units_Grid_Unknown2a2 = new wxGridSizer(10, 0, 0);
	TechTrees_Units_Text_Unknown2a = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 8; ++loop)
	TechTrees_Units_Unknown2a1[loop] = new TextCtrl_Long(TechTrees_Scroller);
	for(short loop = 0; loop < 10; ++loop)
	TechTrees_Units_Unknown2a2[loop] = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Units_Holder_Unknown2b = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Grid_Unknown2b1 = new wxGridSizer(10, 0, 0);
	TechTrees_Units_Grid_Unknown2b2 = new wxGridSizer(10, 0, 0);
	TechTrees_Units_Text_Unknown2b = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 7; ++loop)
	TechTrees_Units_Unknown2b1[loop] = new TextCtrl_Long(TechTrees_Scroller);
	for(short loop = 0; loop < 10; ++loop)
	TechTrees_Units_Unknown2b2[loop] = new TextCtrl_Long(TechTrees_Scroller);

	TechTrees_MainList_Researches_Search = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Researches_UseAnd[0] = new wxCheckBox(TechTrees_Scroller, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	TechTrees_MainList_Researches_Search_R = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_MainList_Researches_UseAnd[1] = new wxCheckBox(TechTrees_Scroller, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	for(short loop = 0; loop < 2; ++loop)
	{
		TechTrees_MainList_Researches_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		TechTrees_MainList_Researches_SearchFilters[loop] = new wxOwnerDrawnComboBox(TechTrees_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	TechTrees_MainList_Researches_List = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_MainList_Researches_Buttons = new wxGridSizer(3, 0, 0);
	TechTrees_MainList_Researches_Add = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_Insert = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_Delete = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_Copy = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_Paste = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_PasteInsert = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	TechTrees_Researches_Holder_ID = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_ID = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Research Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_ID = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_ComboBox_ID = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Researches_ID);
	TechTrees_Researches_Holder_UpperResearch = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_UpperResearch = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Upper Research", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_UpperResearch = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_ComboBox_UpperResearch = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Researches_UpperResearch);
	TechTrees_Researches_Holder_UpperBuilding = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_UpperBuilding = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Upper Building", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_UpperBuilding = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_ComboBox_UpperBuilding = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Researches_UpperBuilding);
	TechTrees_Researches_Holder_Age = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_Age = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Age", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_Age = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_Holder_LocationInAge = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_LocationInAge = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Location In Age *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_LocationInAge = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_LocationInAge->SetToolTip("0 Hidden\n1 First\n2 Second");
	TechTrees_Researches_Holder_RequiredResearches = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_RequiredResearches = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Required Researches *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_RequiredResearches = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_RequiredResearches->SetToolTip("Minimum amount of researches that need to be researched for this to be available");
	TechTrees_Researches_Holder_LineMode = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_LineMode = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Line Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_LineMode = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_LineMode->SetToolTip("0 Independent/new in its line\n3 Depends on a previous research in its line");
	TechTrees_Researches_Holder_VerticalLine = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_VerticalLine = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Vertical Line Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_VerticalLine = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_Holder_Unknown9 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_Unknown9 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " First Age Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_Unknown9 = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_Unknown9->SetToolTip("0 First Age\n4 Others");
	TechTrees_Researches_Holder_Always2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Text_Always2 = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Always 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_Always2 = new TextCtrl_Byte(TechTrees_Scroller);
	TechTrees_Data_Researches = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Researches1 = new wxGridSizer(5, 5, 5);
	TechTrees_DataListHolder_Researches = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_DataList_Researches_Buildings = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Buildings");
	TechTrees_DataList_Researches_Search_Buildings = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Researches_Search_R_Buildings = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Researches_List_Buildings = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_Researches_Holder_Building = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Building = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_ComboBox_Building = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Researches_Building);
	TechTrees_DataList_Researches_Buttons_Buildings = new wxGridSizer(3, 0, 0);
	TechTrees_DataList_Researches_Add_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Insert_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Delete_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Copy_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Paste_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_PasteInsert_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_CopyToResearches_Buildings = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy all to selected researches", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Units = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Units");
	TechTrees_DataList_Researches_Search_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Researches_Search_R_Units = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Researches_List_Units = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_Researches_Holder_Unit = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Unit = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_ComboBox_Unit = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Researches_Unit);
	TechTrees_DataList_Researches_Buttons_Units = new wxGridSizer(3, 0, 0);
	TechTrees_DataList_Researches_Add_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Insert_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Delete_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Copy_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Paste_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_PasteInsert_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_CopyToResearches_Units = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy all to selected researches", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Researches = new wxStaticBoxSizer(wxVERTICAL, TechTrees_Scroller, "Connected Researches");
	TechTrees_DataList_Researches_Search_Researches = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Researches_Search_R_Researches = new wxTextCtrl(TechTrees_Scroller, wxID_ANY);
	TechTrees_DataList_Researches_List_Researches = new wxListBox(TechTrees_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	TechTrees_Researches_Holder_Research = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Research = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_ComboBox_Research = new ComboBox_Plus1(TechTrees_Scroller, TechTrees_Researches_Research);
	TechTrees_DataList_Researches_Buttons_Researches = new wxGridSizer(3, 0, 0);
	TechTrees_DataList_Researches_Add_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Insert_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Delete_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Copy_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_Paste_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_PasteInsert_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	TechTrees_DataList_Researches_CopyToResearches_Researches = new wxButton(TechTrees_Scroller, wxID_ANY, "Copy all to selected researches", wxDefaultPosition, wxSize(5, 20));
	TechTrees_Researches_Holder_Unknown2a = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Grid_Unknown2a1 = new wxGridSizer(10, 0, 0);
	TechTrees_Researches_Grid_Unknown2a2 = new wxGridSizer(10, 0, 0);
	TechTrees_Researches_Text_Unknown2a = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 9; ++loop)
	TechTrees_Researches_Unknown2a1[loop] = new TextCtrl_Long(TechTrees_Scroller);
	for(short loop = 0; loop < 10; ++loop)
	TechTrees_Researches_Unknown2a2[loop] = new TextCtrl_Long(TechTrees_Scroller);
	TechTrees_Researches_Holder_Unknown2b = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Grid_Unknown2b1 = new wxGridSizer(10, 0, 0);
	TechTrees_Researches_Grid_Unknown2b2 = new wxGridSizer(10, 0, 0);
	TechTrees_Researches_Text_Unknown2b = new wxStaticText(TechTrees_Scroller, wxID_ANY, " Zeroes 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 8; ++loop)
	TechTrees_Researches_Unknown2b1[loop] = new TextCtrl_Long(TechTrees_Scroller);
	for(short loop = 0; loop < 10; ++loop)
	TechTrees_Researches_Unknown2b2[loop] = new TextCtrl_Long(TechTrees_Scroller);

	for(short loop = 0; loop < 2; ++loop)
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

	for(short loop = 0; loop < 4; ++loop)
	{
		TechTrees_ComboBox_Modes[loop]->Append("No unit/research");	// 0
		TechTrees_ComboBox_Modes[loop]->Append("Building");
		TechTrees_ComboBox_Modes[loop]->Append("Unit");
		TechTrees_ComboBox_Modes[loop]->Append("Research");
		TechTrees_ComboBox_Modes[loop]->SetSelection(0);
	}

	for(short loop = 0; loop < General_TTUnknown.size(); ++loop)
	{
		General_Holder_TTUnknown[loop]->Add(General_Text_TTUnknown[loop], 0, wxEXPAND);
		General_Holder_TTUnknown[loop]->Add(General_TTUnknown[loop], 0, wxEXPAND);
		General_Grid_Variables2->Add(General_Holder_TTUnknown[loop], 1, wxEXPAND);
	}
	General_Holder_Variables2->Add(General_Grid_Variables2, 0, wxEXPAND);

	TechTrees_MainList_Ages_Buttons->Add(TechTrees_MainList_Ages_Add, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Buttons->Add(TechTrees_MainList_Buildings_Add, 1, wxEXPAND);
	TechTrees_MainList_Units_Buttons->Add(TechTrees_MainList_Units_Add, 1, wxEXPAND);
	TechTrees_MainList_Researches_Buttons->Add(TechTrees_MainList_Researches_Add, 1, wxEXPAND);
	TechTrees_MainList_Ages_Buttons->Add(TechTrees_MainList_Ages_Insert, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Buttons->Add(TechTrees_MainList_Buildings_Insert, 1, wxEXPAND);
	TechTrees_MainList_Units_Buttons->Add(TechTrees_MainList_Units_Insert, 1, wxEXPAND);
	TechTrees_MainList_Researches_Buttons->Add(TechTrees_MainList_Researches_Insert, 1, wxEXPAND);
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
	TechTrees_MainList_Ages_Buttons->Add(TechTrees_MainList_Ages_PasteInsert, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Buttons->Add(TechTrees_MainList_Buildings_PasteInsert, 1, wxEXPAND);
	TechTrees_MainList_Units_Buttons->Add(TechTrees_MainList_Units_PasteInsert, 1, wxEXPAND);
	TechTrees_MainList_Researches_Buttons->Add(TechTrees_MainList_Researches_PasteInsert, 1, wxEXPAND);

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
	for(short loop = 0; loop < 2; ++loop)
	{
		TechTrees_MainList_Buildings->Add(TechTrees_MainList_Buildings_Searches[loop], 0, wxEXPAND);
		TechTrees_MainList_Units->Add(TechTrees_MainList_Units_Searches[loop], 0, wxEXPAND);
		TechTrees_MainList_Researches->Add(TechTrees_MainList_Researches_Searches[loop], 0, wxEXPAND);
	}
	for(short loop = 0; loop < 2; ++loop)
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
	TechTrees_DataList_Ages_Buttons_Buildings->Add(TechTrees_DataList_Ages_Insert_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Units->Add(TechTrees_DataList_Ages_Insert_Units, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Researches->Add(TechTrees_DataList_Ages_Insert_Researches, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Buildings->Add(TechTrees_DataList_Buildings_Insert_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Units->Add(TechTrees_DataList_Buildings_Insert_Units, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Researches->Add(TechTrees_DataList_Buildings_Insert_Researches, 1, wxEXPAND);
	TechTrees_DataList_Units_Buttons_Units->Add(TechTrees_DataList_Units_Insert_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Buildings->Add(TechTrees_DataList_Researches_Insert_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Units->Add(TechTrees_DataList_Researches_Insert_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Researches->Add(TechTrees_DataList_Researches_Insert_Researches, 1, wxEXPAND);
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
	TechTrees_DataList_Ages_Buttons_Buildings->Add(TechTrees_DataList_Ages_PasteInsert_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Units->Add(TechTrees_DataList_Ages_PasteInsert_Units, 1, wxEXPAND);
	TechTrees_DataList_Ages_Buttons_Researches->Add(TechTrees_DataList_Ages_PasteInsert_Researches, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Buildings->Add(TechTrees_DataList_Buildings_PasteInsert_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Units->Add(TechTrees_DataList_Buildings_PasteInsert_Units, 1, wxEXPAND);
	TechTrees_DataList_Buildings_Buttons_Researches->Add(TechTrees_DataList_Buildings_PasteInsert_Researches, 1, wxEXPAND);
	TechTrees_DataList_Units_Buttons_Units->Add(TechTrees_DataList_Units_PasteInsert_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Buildings->Add(TechTrees_DataList_Researches_PasteInsert_Buildings, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Units->Add(TechTrees_DataList_Researches_PasteInsert_Units, 1, wxEXPAND);
	TechTrees_DataList_Researches_Buttons_Researches->Add(TechTrees_DataList_Researches_PasteInsert_Researches, 1, wxEXPAND);

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
	TechTrees_DataList_Ages_Buildings->Add(TechTrees_DataList_Ages_CopyToAges_Buildings, 0, wxEXPAND);
	TechTrees_DataList_Ages_Units->Add(TechTrees_DataList_Ages_CopyToAges_Units, 0, wxEXPAND);
	TechTrees_DataList_Ages_Researches->Add(TechTrees_DataList_Ages_CopyToAges_Researches, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Buildings->Add(TechTrees_DataList_Buildings_CopyToBuildings_Buildings, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Units->Add(TechTrees_DataList_Buildings_CopyToBuildings_Units, 0, wxEXPAND);
	TechTrees_DataList_Buildings_Researches->Add(TechTrees_DataList_Buildings_CopyToBuildings_Researches, 0, wxEXPAND);
	TechTrees_DataList_Units_Units->Add(TechTrees_DataList_Units_CopyToUnits_Units, 0, wxEXPAND);
	TechTrees_DataList_Researches_Buildings->Add(TechTrees_DataList_Researches_CopyToResearches_Buildings, 0, wxEXPAND);
	TechTrees_DataList_Researches_Units->Add(TechTrees_DataList_Researches_CopyToResearches_Units, 0, wxEXPAND);
	TechTrees_DataList_Researches_Researches->Add(TechTrees_DataList_Researches_CopyToResearches_Researches, 0, wxEXPAND);

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

	for(short loop = 0; loop < 49; ++loop)
	TechTrees_Ages_Grid_Zeroes1->Add(TechTrees_Ages_Zeroes1[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 50; ++loop)
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

	for(short loop = 0; loop < 11; ++loop)
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

	for(short loop = 0; loop < 8; ++loop)
	TechTrees_Buildings_Grid_Unknown2a1->Add(TechTrees_Buildings_Unknown2a1[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 10; ++loop)
	TechTrees_Buildings_Grid_Unknown2a2->Add(TechTrees_Buildings_Unknown2a2[loop], 1, wxEXPAND);
	TechTrees_Buildings_Holder_Unknown2a->Add(TechTrees_Buildings_Text_Unknown2a, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Unknown2a->Add(TechTrees_Buildings_Grid_Unknown2a1, 0, wxEXPAND);
	TechTrees_Buildings_Holder_Unknown2a->Add(TechTrees_Buildings_Grid_Unknown2a2, 0, wxEXPAND);

	for(short loop = 0; loop < 7; ++loop)
	TechTrees_Buildings_Grid_Unknown2b1->Add(TechTrees_Buildings_Unknown2b1[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 10; ++loop)
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
	TechTrees_Units_Holder_LocationInAge->Add(TechTrees_Units_LocationInAge, 0, wxEXPAND);
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

	for(short loop = 0; loop < 8; ++loop)
	TechTrees_Units_Grid_Unknown2a1->Add(TechTrees_Units_Unknown2a1[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 10; ++loop)
	TechTrees_Units_Grid_Unknown2a2->Add(TechTrees_Units_Unknown2a2[loop], 1, wxEXPAND);
	TechTrees_Units_Holder_Unknown2a->Add(TechTrees_Units_Text_Unknown2a, 0, wxEXPAND);
	TechTrees_Units_Holder_Unknown2a->Add(TechTrees_Units_Grid_Unknown2a1, 0, wxEXPAND);
	TechTrees_Units_Holder_Unknown2a->Add(TechTrees_Units_Grid_Unknown2a2, 0, wxEXPAND);

	for(short loop = 0; loop < 7; ++loop)
	TechTrees_Units_Grid_Unknown2b1->Add(TechTrees_Units_Unknown2b1[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 10; ++loop)
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

	for(short loop = 0; loop < 9; ++loop)
	TechTrees_Researches_Grid_Unknown2a1->Add(TechTrees_Researches_Unknown2a1[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 10; ++loop)
	TechTrees_Researches_Grid_Unknown2a2->Add(TechTrees_Researches_Unknown2a2[loop], 1, wxEXPAND);
	TechTrees_Researches_Holder_Unknown2a->Add(TechTrees_Researches_Text_Unknown2a, 0, wxEXPAND);
	TechTrees_Researches_Holder_Unknown2a->Add(TechTrees_Researches_Grid_Unknown2a1, 0, wxEXPAND);
	TechTrees_Researches_Holder_Unknown2a->Add(TechTrees_Researches_Grid_Unknown2a2, 0, wxEXPAND);

	for(short loop = 0; loop < 8; ++loop)
	TechTrees_Researches_Grid_Unknown2b1->Add(TechTrees_Researches_Unknown2b1[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 10; ++loop)
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

	TechTrees_Buildings->Add(TechTrees_MainList_Buildings, 1, wxEXPAND);
	TechTrees_Buildings->Add(10, -1);
	TechTrees_Buildings->Add(TechTrees_Data_Buildings, 3, wxEXPAND);

	TechTrees_Units->Add(TechTrees_MainList_Units, 1, wxEXPAND);
	TechTrees_Units->Add(10, -1);
	TechTrees_Units->Add(TechTrees_Data_Units, 3, wxEXPAND);

	TechTrees_Researches->Add(TechTrees_MainList_Researches, 1, wxEXPAND);
	TechTrees_Researches->Add(10, -1);
	TechTrees_Researches->Add(TechTrees_Data_Researches, 3, wxEXPAND);

	TechTrees_ScrollerWindowsSpace->Add(General_Holder_Variables2, 0, wxEXPAND);
	TechTrees_ScrollerWindowsSpace->Add(-1, 5);
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

	for(short loop = 0; loop < 4; ++loop)
	{
		TechTrees_ComboBox_Unit[loop]->Show(false);
		TechTrees_ComboBox_Research[loop]->Show(false);
	}

	Tab_TechTrees->SetSizer(TechTrees_Main);

	Connect(TechTrees_MainList_Ages_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesSearch));
	Connect(TechTrees_MainList_Ages_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesSearch));
	Connect(TechTrees_MainList_Ages_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesSelect));
	Connect(TechTrees_MainList_Ages_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesAdd));
	Connect(TechTrees_MainList_Ages_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesInsert));
	Connect(TechTrees_MainList_Ages_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesDelete));
	Connect(TechTrees_MainList_Ages_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesCopy));
	Connect(TechTrees_MainList_Ages_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesPaste));
	Connect(TechTrees_MainList_Ages_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesPasteInsert));
	Connect(TechTrees_MainList_Buildings_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSearch));
	Connect(TechTrees_MainList_Buildings_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSearch));
	Connect(TechTrees_MainList_Buildings_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSelect));
	Connect(TechTrees_MainList_Buildings_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingAdd));
	Connect(TechTrees_MainList_Buildings_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingInsert));
	Connect(TechTrees_MainList_Buildings_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingDelete));
	Connect(TechTrees_MainList_Buildings_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingCopy));
	Connect(TechTrees_MainList_Buildings_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingPaste));
	Connect(TechTrees_MainList_Buildings_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingPasteInsert));
	Connect(TechTrees_MainList_Units_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTUnitSearch));
	Connect(TechTrees_MainList_Units_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTUnitSearch));
	for(short loop = 0; loop < 2; ++loop)
	{
		Connect(TechTrees_MainList_Buildings_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSearch));
		Connect(TechTrees_MainList_Units_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitSearch));
		Connect(TechTrees_MainList_Researches_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchSearch));
		Connect(TechTrees_MainList_Buildings_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
		Connect(TechTrees_MainList_Units_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
		Connect(TechTrees_MainList_Researches_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
	}
	Connect(TechTrees_MainList_Units_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTUnitSelect));
	Connect(TechTrees_MainList_Units_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitAdd));
	Connect(TechTrees_MainList_Units_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitInsert));
	Connect(TechTrees_MainList_Units_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitDelete));
	Connect(TechTrees_MainList_Units_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitCopy));
	Connect(TechTrees_MainList_Units_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitPaste));
	Connect(TechTrees_MainList_Units_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitPasteInsert));
	Connect(TechTrees_MainList_Researches_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchSearch));
	Connect(TechTrees_MainList_Researches_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchSearch));
	Connect(TechTrees_MainList_Researches_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchSelect));
	Connect(TechTrees_MainList_Researches_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchAdd));
	Connect(TechTrees_MainList_Researches_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchInsert));
	Connect(TechTrees_MainList_Researches_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchDelete));
	Connect(TechTrees_MainList_Researches_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchCopy));
	Connect(TechTrees_MainList_Researches_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchPaste));
	Connect(TechTrees_MainList_Researches_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchPasteInsert));

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
	Connect(TechTrees_DataList_Ages_Insert_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingInsert));
	Connect(TechTrees_DataList_Ages_Insert_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitInsert));
	Connect(TechTrees_DataList_Ages_Insert_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchInsert));
	Connect(TechTrees_DataList_Ages_Delete_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingDelete));
	Connect(TechTrees_DataList_Ages_Delete_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitDelete));
	Connect(TechTrees_DataList_Ages_Delete_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchDelete));
	Connect(TechTrees_DataList_Ages_Copy_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingCopy));
	Connect(TechTrees_DataList_Ages_Copy_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitCopy));
	Connect(TechTrees_DataList_Ages_Copy_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchCopy));
	Connect(TechTrees_DataList_Ages_Paste_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingPaste));
	Connect(TechTrees_DataList_Ages_Paste_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitPaste));
	Connect(TechTrees_DataList_Ages_Paste_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchPaste));
	Connect(TechTrees_DataList_Ages_PasteInsert_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingPasteInsert));
	Connect(TechTrees_DataList_Ages_PasteInsert_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitPasteInsert));
	Connect(TechTrees_DataList_Ages_PasteInsert_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchPasteInsert));
	Connect(TechTrees_DataList_Ages_CopyToAges_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingCopyToAges));
	Connect(TechTrees_DataList_Ages_CopyToAges_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitCopyToAges));
	Connect(TechTrees_DataList_Ages_CopyToAges_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchCopyToAges));
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
	Connect(TechTrees_DataList_Buildings_Insert_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingInsert));
	Connect(TechTrees_DataList_Buildings_Insert_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitInsert));
	Connect(TechTrees_DataList_Buildings_Insert_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchInsert));
	Connect(TechTrees_DataList_Buildings_Delete_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingDelete));
	Connect(TechTrees_DataList_Buildings_Delete_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitDelete));
	Connect(TechTrees_DataList_Buildings_Delete_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchDelete));
	Connect(TechTrees_DataList_Buildings_Copy_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingCopy));
	Connect(TechTrees_DataList_Buildings_Copy_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitCopy));
	Connect(TechTrees_DataList_Buildings_Copy_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchCopy));
	Connect(TechTrees_DataList_Buildings_Paste_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingPaste));
	Connect(TechTrees_DataList_Buildings_Paste_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitPaste));
	Connect(TechTrees_DataList_Buildings_Paste_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchPaste));
	Connect(TechTrees_DataList_Buildings_PasteInsert_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingPasteInsert));
	Connect(TechTrees_DataList_Buildings_PasteInsert_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitPasteInsert));
	Connect(TechTrees_DataList_Buildings_PasteInsert_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchPasteInsert));
	Connect(TechTrees_DataList_Buildings_CopyToBuildings_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingCopyToBuildings));
	Connect(TechTrees_DataList_Buildings_CopyToBuildings_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitCopyToBuildings));
	Connect(TechTrees_DataList_Buildings_CopyToBuildings_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchCopyToBuildings));
	Connect(TechTrees_DataList_Units_Search_Units->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitSearch));
	Connect(TechTrees_DataList_Units_Search_R_Units->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitSearch));
	Connect(TechTrees_DataList_Units_List_Units->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitSelect));
	Connect(TechTrees_DataList_Units_Add_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitAdd));
	Connect(TechTrees_DataList_Units_Insert_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitInsert));
	Connect(TechTrees_DataList_Units_Delete_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitDelete));
	Connect(TechTrees_DataList_Units_Copy_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitCopy));
	Connect(TechTrees_DataList_Units_Paste_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitPaste));
	Connect(TechTrees_DataList_Units_PasteInsert_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitPasteInsert));
	Connect(TechTrees_DataList_Units_CopyToUnits_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitCopyToUnits));
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
	Connect(TechTrees_DataList_Researches_Insert_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingInsert));
	Connect(TechTrees_DataList_Researches_Insert_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitInsert));
	Connect(TechTrees_DataList_Researches_Insert_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchInsert));
	Connect(TechTrees_DataList_Researches_Delete_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingDelete));
	Connect(TechTrees_DataList_Researches_Delete_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitDelete));
	Connect(TechTrees_DataList_Researches_Delete_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchDelete));
	Connect(TechTrees_DataList_Researches_Copy_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingCopy));
	Connect(TechTrees_DataList_Researches_Copy_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitCopy));
	Connect(TechTrees_DataList_Researches_Copy_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchCopy));
	Connect(TechTrees_DataList_Researches_Paste_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingPaste));
	Connect(TechTrees_DataList_Researches_Paste_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitPaste));
	Connect(TechTrees_DataList_Researches_Paste_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchPaste));
	Connect(TechTrees_DataList_Researches_PasteInsert_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingPasteInsert));
	Connect(TechTrees_DataList_Researches_PasteInsert_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitPasteInsert));
	Connect(TechTrees_DataList_Researches_PasteInsert_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchPasteInsert));
	Connect(TechTrees_DataList_Researches_CopyToResearches_Buildings->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingCopyToResearches));
	Connect(TechTrees_DataList_Researches_CopyToResearches_Units->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitCopyToResearches));
	Connect(TechTrees_DataList_Researches_CopyToResearches_Researches->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchCopyToResearches));

	TechTrees_Ages_ID->Connect(TechTrees_Ages_ID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Ages_Building->Connect(TechTrees_Ages_Building->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Ages_Unit->Connect(TechTrees_Ages_Unit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Ages_Research->Connect(TechTrees_Ages_Research->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Ages_ComboBox_Building->Connect(TechTrees_Ages_ComboBox_Building->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Ages_ComboBox_Unit->Connect(TechTrees_Ages_ComboBox_Unit->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Ages_ComboBox_Research->Connect(TechTrees_Ages_ComboBox_Research->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);

	TechTrees_Buildings_ID->Connect(TechTrees_Buildings_ID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_Building->Connect(TechTrees_Buildings_Building->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_Unit->Connect(TechTrees_Buildings_Unit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_Research->Connect(TechTrees_Buildings_Research->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Units_ID->Connect(TechTrees_Units_ID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Units_Unit->Connect(TechTrees_Units_Unit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Researches_ID->Connect(TechTrees_Researches_ID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Researches_Building->Connect(TechTrees_Researches_Building->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Researches_Unit->Connect(TechTrees_Researches_Unit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Researches_Research->Connect(TechTrees_Researches_Research->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_UnitOrResearch1->Connect(TechTrees_Buildings_UnitOrResearch1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_UnitOrResearch2->Connect(TechTrees_Buildings_UnitOrResearch2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Units_UnitOrResearch1->Connect(TechTrees_Units_UnitOrResearch1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Units_UnitOrResearch2->Connect(TechTrees_Units_UnitOrResearch2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_ComboBox_ID->Connect(TechTrees_Buildings_ComboBox_ID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Buildings_ComboBox_Building->Connect(TechTrees_Buildings_ComboBox_Building->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Buildings_ComboBox_Unit->Connect(TechTrees_Buildings_ComboBox_Unit->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Buildings_ComboBox_Research->Connect(TechTrees_Buildings_ComboBox_Research->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Units_ComboBox_ID->Connect(TechTrees_Units_ComboBox_ID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Units_ComboBox_Unit->Connect(TechTrees_Units_ComboBox_Unit->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Researches_ComboBox_ID->Connect(TechTrees_Researches_ComboBox_ID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Researches_ComboBox_Building->Connect(TechTrees_Researches_ComboBox_Building->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Researches_ComboBox_Unit->Connect(TechTrees_Researches_ComboBox_Unit->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Researches_ComboBox_Research->Connect(TechTrees_Researches_ComboBox_Research->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);

	TechTrees_Buildings_Mode1->Connect(TechTrees_Buildings_Mode1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_Mode2->Connect(TechTrees_Buildings_Mode2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Units_Mode1->Connect(TechTrees_Units_Mode1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Units_Mode2->Connect(TechTrees_Units_Mode2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	for(short loop = 0; loop < 4; ++loop)
	Connect(TechTrees_ComboBox_Modes[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees));
}

void AGE_Frame::OnKillFocus_TechTrees(wxFocusEvent &Event)
{
	if(!((AGETextCtrl*)Event.GetEventObject())->SaveEdits()) return;
	if(Event.GetId() == TechTrees_Ages_ID->GetId())
	{
		ListTTAgess();
	}
	else if(Event.GetId() == TechTrees_Ages_Building->GetId())
	{
		ListTTAgesBuildings();
	}
	else if(Event.GetId() == TechTrees_Ages_Unit->GetId())
	{
		ListTTAgesUnits();
	}
	else if(Event.GetId() == TechTrees_Ages_Research->GetId())
	{
		ListTTAgesResearches();
	}
	else if(Event.GetId() == TechTrees_Buildings_ID->GetId())
	{
		ListTTBuildings();
	}
	else if(Event.GetId() == TechTrees_Buildings_Building->GetId())
	{
		ListTTBuildingBuildings();
	}
	else if(Event.GetId() == TechTrees_Buildings_Unit->GetId())
	{
		ListTTBuildingUnits();
	}
	else if(Event.GetId() == TechTrees_Buildings_Research->GetId())
	{
		ListTTBuildingResearches();
	}
	else if(Event.GetId() == TechTrees_Units_ID->GetId())
	{
		ListTTUnits();
	}
	else if(Event.GetId() == TechTrees_Units_Unit->GetId())
	{
		ListTTUnitUnits();
	}
	else if(Event.GetId() == TechTrees_Researches_ID->GetId())
	{
		ListTTResearches();
	}
	else if(Event.GetId() == TechTrees_Researches_Building->GetId())
	{
		ListTTResearchBuildings();
	}
	else if(Event.GetId() == TechTrees_Researches_Unit->GetId())
	{
		ListTTResearchUnits();
	}
	else if(Event.GetId() == TechTrees_Researches_Research->GetId())
	{
		ListTTResearchResearches();
	}
	else if(Event.GetId() == TechTrees_Units_Mode1->GetId()
	|| Event.GetId() == TechTrees_Units_Mode2->GetId()
	|| Event.GetId() == TechTrees_Units_UnitOrResearch1->GetId()
	|| Event.GetId() == TechTrees_Units_UnitOrResearch2->GetId())
	{
		wxCommandEvent E;
		OnTTUnitSelect(E);
	}
	else if(Event.GetId() == TechTrees_Buildings_Mode1->GetId()
	|| Event.GetId() == TechTrees_Buildings_Mode2->GetId()
	|| Event.GetId() == TechTrees_Buildings_UnitOrResearch1->GetId()
	|| Event.GetId() == TechTrees_Buildings_UnitOrResearch2->GetId())
	{
		wxCommandEvent E;
		OnTTBuildingSelect(E);
	}
	Event.Skip();
}

void AGE_Frame::OnUpdateCombo_TechTrees(wxCommandEvent &Event)
{
	if(Event.GetId() == TechTrees_ComboBox_Modes[2]->GetId())
	{
		GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Mode1 = lexical_cast<long>(TechTrees_ComboBox_Modes[2]->GetSelection());

		wxCommandEvent E;
		OnTTUnitSelect(E);
		return;
	}
	if(Event.GetId() == TechTrees_ComboBox_Modes[3]->GetId())
	{
		GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Mode2 = lexical_cast<long>(TechTrees_ComboBox_Modes[3]->GetSelection());

		wxCommandEvent E;
		OnTTUnitSelect(E);
		return;
	}
	if(Event.GetId() == TechTrees_ComboBox_Modes[0]->GetId())
	{
		GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Mode1 = lexical_cast<long>(TechTrees_ComboBox_Modes[0]->GetSelection());

		wxCommandEvent E;
		OnTTBuildingSelect(E);
		return;
	}
	if(Event.GetId() == TechTrees_ComboBox_Modes[1]->GetId())
	{
		GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Mode2 = lexical_cast<long>(TechTrees_ComboBox_Modes[1]->GetSelection());

		wxCommandEvent E;
		OnTTBuildingSelect(E);
		return;
	}
	((AGEComboBox*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == TechTrees_Ages_ComboBox_Building->GetId())
	{
		ListTTAgesBuildings();
	}
	else if(Event.GetId() == TechTrees_Ages_ComboBox_Unit->GetId())
	{
		ListTTAgesUnits();
	}
	else if(Event.GetId() == TechTrees_Ages_ComboBox_Research->GetId())
	{
		ListTTAgesResearches();
	}
	else if(Event.GetId() == TechTrees_Buildings_ComboBox_ID->GetId())
	{
		ListTTBuildings();
	}
	else if(Event.GetId() == TechTrees_Buildings_ComboBox_Building->GetId())
	{
		ListTTBuildingBuildings();
	}
	else if(Event.GetId() == TechTrees_Buildings_ComboBox_Unit->GetId())
	{
		ListTTBuildingUnits();
	}
	else if(Event.GetId() == TechTrees_Buildings_ComboBox_Research->GetId())
	{
		ListTTBuildingResearches();
	}
	else if(Event.GetId() == TechTrees_Units_ComboBox_ID->GetId())
	{
		ListTTUnits();
	}
	else if(Event.GetId() == TechTrees_Units_ComboBox_Unit->GetId())
	{
		ListTTUnitUnits();
	}
	else if(Event.GetId() == TechTrees_Researches_ComboBox_ID->GetId())
	{
		ListTTResearches();
	}
	else if(Event.GetId() == TechTrees_Researches_ComboBox_Building->GetId())
	{
		ListTTResearchBuildings();
	}
	else if(Event.GetId() == TechTrees_Researches_ComboBox_Unit->GetId())
	{
		ListTTResearchUnits();
	}
	else if(Event.GetId() == TechTrees_Researches_ComboBox_Research->GetId())
	{
		ListTTResearchResearches();
	}
}
