#include "../AGE_Frame.h"

string AGE_Frame::GetTTAgesName(short Index)
{
	return "Age "+lexical_cast<string>(GenieFile->TechTree.TechTreeAges[Index].ID);
}

void AGE_Frame::OnTTAgesSearch(wxCommandEvent &Event)
{
	ListTTAges();
}

void AGE_Frame::ListTTAges()
{
	InitTTAges();
	wxCommandEvent E;
	OnTTAgesSelect(E);
}

void AGE_Frame::InitTTAges()
{
	searchText = TechTrees_MainList_Ages_Search->GetValue().Lower();
	excludeText = TechTrees_MainList_Ages_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.TechTreeAges.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTTAgesName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.TechTreeAges[loop]);
		}
	}

	Listing(TechTrees_MainList_Ages_List, filteredNames, dataPointers);
}

void AGE_Frame::OnTTAgesSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(selections < 1) return;

	TTAgeIDs.resize(selections);
	TechTrees_Ages_ID->resize(selections);
	TechTrees_Ages_Unknown2->resize(selections);
	TechTrees_Ages_UnknownItems.UsedItems->resize(selections);
	TechTrees_Ages_UnknownItems.Unknown->resize(selections);
	TechTrees_Ages_LineMode->resize(selections);
	TechTrees_Ages_Items.UsedItems->resize(selections);

	genie::TechTreeAge * AgePointer;
	for(auto sel = selections; sel--> 0;)
	{
		AgePointer = (genie::TechTreeAge*)TechTrees_MainList_Ages_List->GetClientData(Items.Item(sel));
		TTAgeIDs[sel] = (AgePointer - (&GenieFile->TechTree.TechTreeAges[0]));

		TechTrees_Ages_ID->container[sel] = &AgePointer->ID;
		TechTrees_Ages_Unknown2->container[sel] = &AgePointer->Unknown2;
		TechTrees_Ages_UnknownItems.UsedItems->container[sel] = &AgePointer->SlotsUsed;
		TechTrees_Ages_UnknownItems.Unknown->container[sel] = &AgePointer->Unknown6;
		TechTrees_Ages_LineMode->container[sel] = &AgePointer->LineMode;
		TechTrees_Ages_Items.UsedItems->container[sel] = &AgePointer->Common.SlotsUsed;
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected age: "+lexical_cast<string>(TTAgeIDs[0]), 0);

	TechTrees_Ages_ID->Update();
	TechTrees_Ages_Unknown2->Update();
	TechTrees_Ages_Items.UsedItems->Update();
	TechTrees_Ages_UnknownItems.UsedItems->Update();
	TechTrees_Ages_UnknownItems.Unknown->Update();
	TechTrees_Ages_LineMode->Update();

	ListTTAgeBuildings();
	ListTTAgeUnits();
	ListTTAgeResearches();
	ListTTAgeItems();
	ListTTAgeUnknownItems();
}

void AGE_Frame::OnTTAgesAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->TechTree.TechTreeAges);
	ListTTAges();
}

void AGE_Frame::OnTTAgesInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->TechTree.TechTreeAges, TTAgeIDs[0]);
	ListTTAges();
}

void AGE_Frame::OnTTAgesDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.TechTreeAges, TTAgeIDs);
	ListTTAges();
}

void AGE_Frame::OnTTAgesCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.TechTreeAges, TTAgeIDs, copies->TTAge);
}

void AGE_Frame::OnTTAgesPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTAgeIDs.size(), copies->TTAge.size()))
		{
			PasteToList(GenieFile->TechTree.TechTreeAges, TTAgeIDs, copies->TTAge);
		}
	}
	else
	{
		PasteToList(GenieFile->TechTree.TechTreeAges, TTAgeIDs[0], copies->TTAge);
	}
	ListTTAges();
}

void AGE_Frame::OnTTAgesPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->TechTree.TechTreeAges, TTAgeIDs[0], copies->TTAge);
	ListTTAges();
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
	ListTTAgeBuildings();
}

void AGE_Frame::ListTTAgeBuildings()
{
	searchText = TechTrees_Ages_Buildings.Search->GetValue().Lower();
	excludeText = TechTrees_Ages_Buildings.SearchRecursive->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetBuildingName(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings[loop]);
		}
	}
	Listing(TechTrees_Ages_Buildings.List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTTAgesBuildingSelect(E);
}

void AGE_Frame::OnTTAgesBuildingSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Buildings.List->GetSelections(Items);
	if(selections > 0)
	{
		TTAgeBuildIDs.resize(selections);
		TechTrees_Ages_Buildings.Item->resize(selections);

		int32_t * BuildingPointer;
		for(auto loop = selections; loop--> 0;)
		{
			BuildingPointer = (int32_t*)TechTrees_Ages_Buildings.List->GetClientData(Items.Item(loop));
			TTAgeBuildIDs[loop] = (BuildingPointer - (&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings[0]));
			TechTrees_Ages_Buildings.Item->container[loop] = BuildingPointer;
		}

		TechTrees_Ages_Buildings.Item->Update();
	}
	else
	{
		TechTrees_Ages_Buildings.Item->Clear();
		TechTrees_Ages_Buildings.ItemCombo->SetSelection(0);
	}
	TechTrees_Ages_Buildings.Item->Enable(selections);
	TechTrees_Ages_Buildings.ItemCombo->Enable(selections);
}

void AGE_Frame::OnTTAgesBuildingAdd(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings);
	ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs[0]);
	ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs);
	ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs, copies->TTAgeBuild);
}

void AGE_Frame::OnTTAgesBuildingPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTAgeBuildIDs.size(), copies->TTAgeBuild.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs, copies->TTAgeBuild);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs[0], copies->TTAgeBuild);
	}
	ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs[0], copies->TTAgeBuild);
	ListTTAgeBuildings();
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
	ListTTAgeUnits();
}

void AGE_Frame::ListTTAgeUnits()
{
	searchText = TechTrees_Ages_Units.Search->GetValue().Lower();
	excludeText = TechTrees_Ages_Units.SearchRecursive->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units[loop]);
		}
	}
	Listing(TechTrees_Ages_Units.List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTTAgesUnitSelect(E);
}

void AGE_Frame::OnTTAgesUnitSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Units.List->GetSelections(Items);
	if(selections > 0)
	{
		TTAgeUnitIDs.resize(selections);
		TechTrees_Ages_Units.Item->resize(selections);

		int32_t * UnitPointer;
		for(auto loop = selections; loop--> 0;)
		{
			UnitPointer = (int32_t*)TechTrees_Ages_Units.List->GetClientData(Items.Item(loop));
			TTAgeUnitIDs[loop] = (UnitPointer - (&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units[0]));
			TechTrees_Ages_Units.Item->container[loop] = UnitPointer;
		}

		TechTrees_Ages_Units.Item->Update();
	}
	else
	{
		TechTrees_Ages_Units.Item->Clear();
		TechTrees_Ages_Units.ItemCombo->SetSelection(0);
	}
	TechTrees_Ages_Units.Item->Enable(selections);
	TechTrees_Ages_Units.ItemCombo->Enable(selections);
}

void AGE_Frame::OnTTAgesUnitAdd(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units);
	ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs[0]);
	ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs);
	ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs, copies->TTAgeUnit);
}

void AGE_Frame::OnTTAgesUnitPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTAgeUnitIDs.size(), copies->TTAgeUnit.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs, copies->TTAgeUnit);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs[0], copies->TTAgeUnit);
	}
	ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs[0], copies->TTAgeUnit);
	ListTTAgeUnits();
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
	ListTTAgeResearches();
}

void AGE_Frame::ListTTAgeResearches()
{
	searchText = TechTrees_Ages_Researches.Search->GetValue().Lower();
	excludeText = TechTrees_Ages_Researches.SearchRecursive->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetSimpleResearchName(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches[loop]);
		}
	}
	Listing(TechTrees_Ages_Researches.List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTTAgesResearchSelect(E);
}

void AGE_Frame::OnTTAgesResearchSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Researches.List->GetSelections(Items);
	if(selections > 0)
	{
		TTAgeResIDs.resize(selections);
		TechTrees_Ages_Researches.Item->resize(selections);

		int32_t * ResearchPointer;
		for(auto loop = selections; loop--> 0;)
		{
			ResearchPointer = (int32_t*)TechTrees_Ages_Researches.List->GetClientData(Items.Item(loop));
			TTAgeResIDs[loop] = (ResearchPointer - (&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches[0]));
			TechTrees_Ages_Researches.Item->container[loop] = ResearchPointer;
		}

		TechTrees_Ages_Researches.Item->Update();
	}
	else
	{
		TechTrees_Ages_Researches.Item->Clear();
		TechTrees_Ages_Researches.ItemCombo->SetSelection(0);
	}
	TechTrees_Ages_Researches.Item->Enable(selections);
	TechTrees_Ages_Researches.ItemCombo->Enable(selections);
}

void AGE_Frame::OnTTAgesResearchAdd(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Ages_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches);
	ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs[0]);
	ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs);
	ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs, copies->TTAgeRes);
}

void AGE_Frame::OnTTAgesResearchPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTAgeResIDs.size(), copies->TTAgeRes.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs, copies->TTAgeRes);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs[0], copies->TTAgeRes);
	}
	ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs[0], copies->TTAgeRes);
	ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchCopyToAges(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTAgeIDs.size(); ++loop)
	{
		GenieFile->TechTree.TechTreeAges[TTAgeIDs[loop]].Researches = GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Researches;
	}
}

void AGE_Frame::OnTTAgeItemSearch(wxCommandEvent &Event)
{
	ListTTAgeItems();
}

void AGE_Frame::ListTTAgeItems()
{
	ListTTCommonItems(TechTrees_Ages_Items, &GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Common);
	wxCommandEvent E;
	OnTTAgeItemSelect(E);
}

void AGE_Frame::SelectTTCommonItems(AGE_AreaTT84 &area, genie::techtree::Common* dataPointer)
{
	auto selections = area.List->GetSelections(Items);
	if(selections > 0)
	{
		TTItemIDs.resize(selections);
		area.Item->resize(selections);
		area.Mode->resize(selections);

		int32_t * ItemPointer;
		for(auto loop = selections; loop--> 0;)
		{
			ItemPointer = (int32_t*)area.List->GetClientData(Items.Item(loop));
			TTItemIDs[loop] = (ItemPointer - (&dataPointer->Mode[0]));
			area.Mode->container[loop] = ItemPointer;
			area.Item->container[loop] = &dataPointer->UnitResearch[TTItemIDs[loop]];
		}

		area.Mode->Update();
		area.ModeCombo->SetSelection(*ItemPointer);
		area.Item->Update();
		area.FillItemCombo(dataPointer->UnitResearch[TTItemIDs[0]] + 1);
	}
}

void AGE_Frame::OnTTAgeItemSelect(wxCommandEvent &Event)
{
	SelectTTCommonItems(TechTrees_Ages_Items, &GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Common);
}

void AGE_Frame::OnTTAgeItemCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Items.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Common.UnitResearch, TTItemIDs, copies->TTItem);
	CopyFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Common.Mode, TTItemIDs, copies->TTMode);
}

void AGE_Frame::OnTTAgeItemPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_Items.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTItemIDs.size(), copies->TTItem.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Common.UnitResearch, TTItemIDs, copies->TTItem);
			PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Common.Mode, TTItemIDs, copies->TTMode);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Common.UnitResearch, TTItemIDs[0], copies->TTItem);
		PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Common.Mode, TTItemIDs[0], copies->TTMode);
	}
	ListTTAgeItems();
}

void AGE_Frame::OnTTAgeItemCopyToAges(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTAgeIDs.size(); ++loop)
	{
		GenieFile->TechTree.TechTreeAges[TTAgeIDs[loop]].Common = GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Common;
	}
}

void AGE_Frame::OnTTAgeUnknownItemSearch(wxCommandEvent &Event)
{
	ListTTAgeUnknownItems();
}

void AGE_Frame::ListTTAgeUnknownItems()
{
	searchText = TechTrees_Ages_UnknownItems.Search->GetValue().Lower();
	excludeText = TechTrees_Ages_UnknownItems.SearchRecursive->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].getU4Size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>((short)GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown4[loop]);
		Name += " - "+lexical_cast<string>((short)GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown5[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown4[loop]);
		}
	}
	Listing(TechTrees_Ages_UnknownItems.List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTTAgeUnknownItemSelect(E);
}

void AGE_Frame::OnTTAgeUnknownItemSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_UnknownItems.List->GetSelections(Items);
	if(selections > 0)
	{
		TTUnknownItemIDs.resize(selections);
		TechTrees_Ages_UnknownItems.Unknown1->resize(selections);
		TechTrees_Ages_UnknownItems.Unknown2->resize(selections);

		int8_t * unknown4Pointer;
		genie::TechTreeAge* agePointer = &GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]];
		for(auto loop = selections; loop--> 0;)
		{
			unknown4Pointer = (int8_t*)TechTrees_Ages_UnknownItems.List->GetClientData(Items.Item(loop));
			TTUnknownItemIDs[loop] = (unknown4Pointer - (&agePointer->Unknown4[0]));
			TechTrees_Ages_UnknownItems.Unknown1->container[loop] = unknown4Pointer;
			TechTrees_Ages_UnknownItems.Unknown2->container[loop] = &agePointer->Unknown5[TTUnknownItemIDs[loop]];
		}

		TechTrees_Ages_UnknownItems.Unknown1->Update();
		TechTrees_Ages_UnknownItems.Unknown2->Update();
	}
}

void AGE_Frame::OnTTAgeUnknownItemCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_UnknownItems.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown4, TTUnknownItemIDs, copies->TTUnknown4);
	CopyFromList(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown5, TTUnknownItemIDs, copies->TTUnknown5);
}

void AGE_Frame::OnTTAgeUnknownItemPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Ages_UnknownItems.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTUnknownItemIDs.size(), copies->TTUnknown4.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown4, TTUnknownItemIDs, copies->TTUnknown4);
			PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown5, TTUnknownItemIDs, copies->TTUnknown5);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown4, TTUnknownItemIDs[0], copies->TTUnknown4);
		PasteToListNoGV(GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown5, TTUnknownItemIDs[0], copies->TTUnknown5);
	}
	ListTTAgeUnknownItems();
}

void AGE_Frame::OnTTAgeUnknownItemCopyToAges(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTAgeIDs.size(); ++loop)
	{
		GenieFile->TechTree.TechTreeAges[TTAgeIDs[loop]].Unknown4 = GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown4;
		GenieFile->TechTree.TechTreeAges[TTAgeIDs[loop]].Unknown5 = GenieFile->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown5;
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
			case 1: // Status
				Name += "S "+lexical_cast<string>((short)GenieFile->TechTree.BuildingConnections[Index].Unknown1);
				break;
			case 2: // Required Items
				Name += "I "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Common.SlotsUsed);
				break;
			case 3: // Age
				Name += "A "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].Common.UnitResearch[0]);
				break;
			case 4: // Location in Age
				Name += "LA "+lexical_cast<string>((short)GenieFile->TechTree.BuildingConnections[Index].LocationInAge);
				break;
			case 5: // Units & Techs by Age
				Name += "UT";
				for(short age = 0; age < 5; ++age)
				Name += " "+lexical_cast<string>((short)GenieFile->TechTree.BuildingConnections[Index].UnitsTechsTotal[age]);
				break;
			case 6: // Units & Techs @ 1st by Age
				Name += "UT1";
				for(short age = 0; age < 5; ++age)
				Name += " "+lexical_cast<string>((short)GenieFile->TechTree.BuildingConnections[Index].UnitsTechsFirst[age]);
				break;
			case 7: // Line Mode
				Name += "LM "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].LineMode);
				break;
			case 8: // Enabling Research
				Name += "E "+lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].EnablingResearch);
				break;
		}
		Name += ", ";
		if(Selection[loop+1] < 1) break;
	}

	Name += lexical_cast<string>(GenieFile->TechTree.BuildingConnections[Index].ID)+" ";
	if(GenieFile->Civs[0].Units.size() <= GenieFile->TechTree.BuildingConnections[Index].ID) return Name;
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
	InitTTBuildings();
	wxCommandEvent E;
	OnTTBuildingSelect(E);
}

void AGE_Frame::InitTTBuildings()
{
	searchText = TechTrees_MainList_Buildings_Search->GetValue().Lower();
	excludeText = TechTrees_MainList_Buildings_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = TechTrees_MainList_Buildings_UseAnd[loop]->GetValue();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.BuildingConnections.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTTBuildingName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.BuildingConnections[loop]);
		}
	}

	Listing(TechTrees_MainList_Buildings_List, filteredNames, dataPointers);

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;
}

void AGE_Frame::OnTTBuildingSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(selections < 1) return;

	TTBuildConIDs.resize(selections);
	TechTrees_Buildings_ID->resize(selections);
	TechTrees_Buildings_Always2->resize(selections);
	TechTrees_Buildings_Items.UsedItems->resize(selections);
	TechTrees_Buildings_LocationInAge->resize(selections);
	TechTrees_Buildings_LineMode->resize(selections);
	TechTrees_Buildings_EnablingResearch->resize(selections);
	for(short loop = 0; loop < 10; ++loop)
	TechTrees_Buildings_TotalUnitsTechs[loop]->resize(selections);

	genie::BuildingConnection * BuildingConPointer;
	for(auto sel = selections; sel--> 0;)
	{
		BuildingConPointer = (genie::BuildingConnection*)TechTrees_MainList_Buildings_List->GetClientData(Items.Item(sel));
		TTBuildConIDs[sel] = (BuildingConPointer - (&GenieFile->TechTree.BuildingConnections[0]));

		TechTrees_Buildings_ID->container[sel] = &BuildingConPointer->ID;
		TechTrees_Buildings_Always2->container[sel] = &BuildingConPointer->Unknown1;
		TechTrees_Buildings_Items.UsedItems->container[sel] = &BuildingConPointer->Common.SlotsUsed;
		TechTrees_Buildings_LocationInAge->container[sel] = &BuildingConPointer->LocationInAge;
		TechTrees_Buildings_LineMode->container[sel] = &BuildingConPointer->LineMode;
		TechTrees_Buildings_EnablingResearch->container[sel] = &BuildingConPointer->EnablingResearch;
		for(short loop = 0; loop < 5; ++loop)
		{
			TechTrees_Buildings_TotalUnitsTechs[loop]->container[sel] = &BuildingConPointer->UnitsTechsTotal[loop];
			TechTrees_Buildings_TotalUnitsTechs[loop+5]->container[sel] = &BuildingConPointer->UnitsTechsFirst[loop];
		}
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected building: "+lexical_cast<string>(TTBuildConIDs[0]), 0);

	TechTrees_Buildings_ID->Update();
	TechTrees_Buildings_Always2->Update();
	TechTrees_Buildings_Items.UsedItems->Update();
	TechTrees_Buildings_LocationInAge->Update();
	for(short loop = 0; loop < 5; ++loop)
	{
		TechTrees_Buildings_TotalUnitsTechs[loop]->Update();
		TechTrees_Buildings_TotalUnitsTechs[loop+5]->Update();
	}
	TechTrees_Buildings_LineMode->Update();
	TechTrees_Buildings_EnablingResearch->Update();

	ListTTBuildingBuildings();
	ListTTBuildingUnits();
	ListTTBuildingResearches();
	ListTTBuildingItems();
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
	auto selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->TechTree.BuildingConnections, TTBuildConIDs[0]);
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.BuildingConnections, TTBuildConIDs);
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.BuildingConnections, TTBuildConIDs, copies->TTBuildCon);
}

void AGE_Frame::OnTTBuildingPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTBuildConIDs.size(), copies->TTBuildCon.size()))
		{
			PasteToList(GenieFile->TechTree.BuildingConnections, TTBuildConIDs, copies->TTBuildCon);
		}
	}
	else
	{
		PasteToList(GenieFile->TechTree.BuildingConnections, TTBuildConIDs[0], copies->TTBuildCon);
	}
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(selections < 1) return;

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
	searchText = TechTrees_Buildings_Buildings.Search->GetValue().Lower();
	excludeText = TechTrees_Buildings_Buildings.SearchRecursive->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetBuildingName(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings[loop]);
		}
	}
	Listing(TechTrees_Buildings_Buildings.List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTTBuildingBuildingSelect(E);
}

void AGE_Frame::OnTTBuildingBuildingSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Buildings.List->GetSelections(Items);
	if(selections > 0)
	{
		TTBuildBuildIDs.resize(selections);
		TechTrees_Buildings_Buildings.Item->resize(selections);

		int32_t * BuildingPointer;
		for(auto loop = selections; loop--> 0;)
		{
			BuildingPointer = (int32_t*)TechTrees_Buildings_Buildings.List->GetClientData(Items.Item(loop));
			TTBuildBuildIDs[loop] = (BuildingPointer - (&GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings[0]));
			TechTrees_Buildings_Buildings.Item->container[loop] = BuildingPointer;
		}

		TechTrees_Buildings_Buildings.Item->Update();
	}
	else
	{
		TechTrees_Buildings_Buildings.Item->Clear();
		TechTrees_Buildings_Buildings.ItemCombo->SetSelection(0);
	}
	TechTrees_Buildings_Buildings.Item->Enable(selections);
	TechTrees_Buildings_Buildings.ItemCombo->Enable(selections);
}

void AGE_Frame::OnTTBuildingBuildingAdd(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings);
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs[0]);
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs);
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs, copies->TTBuildBuild);
}

void AGE_Frame::OnTTBuildingBuildingPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTBuildBuildIDs.size(), copies->TTBuildBuild.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs, copies->TTBuildBuild);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs[0], copies->TTBuildBuild);
	}
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

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
	searchText = TechTrees_Buildings_Units.Search->GetValue().Lower();
	excludeText = TechTrees_Buildings_Units.SearchRecursive->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units[loop]);
		}
	}
	Listing(TechTrees_Buildings_Units.List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTTBuildingUnitSelect(E);
}

void AGE_Frame::OnTTBuildingUnitSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Units.List->GetSelections(Items);
	if(selections > 0)
	{
		TTBuildUnitIDs.resize(selections);
		TechTrees_Buildings_Units.Item->resize(selections);

		int32_t * UnitPointer;
		for(auto loop = selections; loop--> 0;)
		{
			UnitPointer = (int32_t*)TechTrees_Buildings_Units.List->GetClientData(Items.Item(loop));
			TTBuildUnitIDs[loop] = (UnitPointer - (&GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units[0]));
			TechTrees_Buildings_Units.Item->container[loop] = UnitPointer;
		}

		TechTrees_Buildings_Units.Item->Update();
	}
	else
	{
		TechTrees_Buildings_Units.Item->Clear();
		TechTrees_Buildings_Units.ItemCombo->SetSelection(0);
	}
	TechTrees_Buildings_Units.Item->Enable(selections);
	TechTrees_Buildings_Units.ItemCombo->Enable(selections);
}

void AGE_Frame::OnTTBuildingUnitAdd(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units);
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs[0]);
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs);
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs, copies->TTBuildUnit);
}

void AGE_Frame::OnTTBuildingUnitPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTBuildUnitIDs.size(), copies->TTBuildUnit.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs, copies->TTBuildUnit);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs[0], copies->TTBuildUnit);
	}
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Units.List->GetSelections(Items);
	if(selections < 1) return;

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
	searchText = TechTrees_Buildings_Researches.Search->GetValue().Lower();
	excludeText = TechTrees_Buildings_Researches.SearchRecursive->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetSimpleResearchName(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches[loop]);
		}
	}
	Listing(TechTrees_Buildings_Researches.List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTTBuildingResearchSelect(E);
}

void AGE_Frame::OnTTBuildingResearchSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Researches.List->GetSelections(Items);
	if(selections > 0)
	{
		TTBuildResIDs.resize(selections);
		TechTrees_Buildings_Researches.Item->resize(selections);

		int32_t * ResearchPointer;
		for(auto loop = selections; loop--> 0;)
		{
			ResearchPointer = (int32_t*)TechTrees_Buildings_Researches.List->GetClientData(Items.Item(loop));
			TTBuildResIDs[loop] = (ResearchPointer - (&GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches[0]));
			TechTrees_Buildings_Researches.Item->container[loop] = ResearchPointer;
		}

		TechTrees_Buildings_Researches.Item->Update();
	}
	else
	{
		TechTrees_Buildings_Researches.Item->Clear();
		TechTrees_Buildings_Researches.ItemCombo->SetSelection(0);
	}
	TechTrees_Buildings_Researches.Item->Enable(selections);
	TechTrees_Buildings_Researches.ItemCombo->Enable(selections);
}

void AGE_Frame::OnTTBuildingResearchAdd(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Buildings_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches);
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs[0]);
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs);
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs, copies->TTBuildRes);
}

void AGE_Frame::OnTTBuildingResearchPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTBuildResIDs.size(), copies->TTBuildRes.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs, copies->TTBuildRes);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs[0], copies->TTBuildRes);
	}
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Researches.List->GetSelections(Items);
	if(selections < 1) return;

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

void AGE_Frame::OnTTBuildingItemSearch(wxCommandEvent &Event)
{
	ListTTBuildingItems();
}

void AGE_Frame::ListTTBuildingItems()
{
	ListTTCommonItems(TechTrees_Buildings_Items, &GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Common);
	wxCommandEvent E;
	OnTTBuildingItemSelect(E);
}

void AGE_Frame::OnTTBuildingItemSelect(wxCommandEvent &Event)
{
	SelectTTCommonItems(TechTrees_Buildings_Items, &GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Common);
}

void AGE_Frame::OnTTBuildingItemCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Items.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Common.UnitResearch, TTItemIDs, copies->TTItem);
	CopyFromList(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Common.Mode, TTItemIDs, copies->TTMode);
}

void AGE_Frame::OnTTBuildingItemPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Buildings_Items.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTItemIDs.size(), copies->TTItem.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Common.UnitResearch, TTItemIDs, copies->TTItem);
			PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Common.Mode, TTItemIDs, copies->TTMode);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Common.UnitResearch, TTItemIDs[0], copies->TTItem);
		PasteToListNoGV(GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Common.Mode, TTItemIDs[0], copies->TTMode);
	}
	ListTTBuildingItems();
}

void AGE_Frame::OnTTBuildingItemCopyToBuildings(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTBuildConIDs.size(); ++loop)
	{
		GenieFile->TechTree.BuildingConnections[TTBuildConIDs[loop]].Common = GenieFile->TechTree.BuildingConnections[TTBuildConIDs[0]].Common;
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
			case 1: // Status
				Name += "S "+lexical_cast<string>((short)GenieFile->TechTree.UnitConnections[Index].Unknown1);
				break;
			case 2: // Upper Building
				Name += "U "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].UpperBuilding);
				break;
			case 3: // Required Items
				Name += "I "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Common.SlotsUsed);
				break;
			case 4: // Age
				Name += "A "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].Common.UnitResearch[0]);
				break;
			case 5: // Vertical Line Number
				Name += "V "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].VerticalLine);
				break;
			case 6: // Space Sharing
				Name += "LA "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].LocationInAge);
				break;
			case 7: // Required Research
				Name += "R "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].RequiredResearch);
				break;
			case 8: // Placement
				Name += "LM "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].LineMode);
				break;
			case 9: // Enabling Research
				Name += "E "+lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].EnablingResearch);
				break;
		}
		Name += ", ";
		if(Selection[loop+1] < 1) break;
	}

	Name += lexical_cast<string>(GenieFile->TechTree.UnitConnections[Index].ID)+" ";
	if(GenieFile->Civs[0].Units.size() <= GenieFile->TechTree.UnitConnections[Index].ID) return Name;
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
	InitTTUnits();
	wxCommandEvent E;
	OnTTUnitSelect(E);
}

void AGE_Frame::InitTTUnits()
{
	searchText = TechTrees_MainList_Units_Search->GetValue().Lower();
	excludeText = TechTrees_MainList_Units_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = TechTrees_MainList_Units_UseAnd[loop]->GetValue();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.UnitConnections.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTTUnitName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.UnitConnections[loop]);
		}
	}

	Listing(TechTrees_MainList_Units_List, filteredNames, dataPointers);

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;
}

void AGE_Frame::OnTTUnitSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(selections < 1) return;

	TTUnitConIDs.resize(selections);
	TechTrees_Units_ID->resize(selections);
	TechTrees_Units_Always2->resize(selections);
	TechTrees_Units_UpperBuilding->resize(selections);
	TechTrees_Units_Items.UsedItems->resize(selections);
	TechTrees_Units_VerticalLine->resize(selections);
	TechTrees_Units_LocationInAge->resize(selections);
	TechTrees_Units_RequiredResearch->resize(selections);
	TechTrees_Units_LineMode->resize(selections);
	TechTrees_Units_EnablingResearch->resize(selections);

	genie::UnitConnection * UnitConPointer;
	for(auto sel = selections; sel--> 0;)
	{
		UnitConPointer = (genie::UnitConnection*)TechTrees_MainList_Units_List->GetClientData(Items.Item(sel));
		TTUnitConIDs[sel] = (UnitConPointer - (&GenieFile->TechTree.UnitConnections[0]));

		TechTrees_Units_ID->container[sel] = &UnitConPointer->ID;
		TechTrees_Units_Always2->container[sel] = &UnitConPointer->Unknown1;
		TechTrees_Units_UpperBuilding->container[sel] = &UnitConPointer->UpperBuilding;
		TechTrees_Units_Items.UsedItems->container[sel] = &UnitConPointer->Common.SlotsUsed;
		TechTrees_Units_VerticalLine->container[sel] = &UnitConPointer->VerticalLine;
		TechTrees_Units_LocationInAge->container[sel] = &UnitConPointer->LocationInAge;
		TechTrees_Units_RequiredResearch->container[sel] = &UnitConPointer->RequiredResearch;
		TechTrees_Units_LineMode->container[sel] = &UnitConPointer->LineMode;
		TechTrees_Units_EnablingResearch->container[sel] = &UnitConPointer->EnablingResearch;
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected unit: "+lexical_cast<string>(TTUnitConIDs[0]), 0);

	TechTrees_Units_ID->Update();
	TechTrees_Units_Always2->Update();
	TechTrees_Units_UpperBuilding->Update();
	TechTrees_Units_Items.UsedItems->Update();
	TechTrees_Units_VerticalLine->Update();
	TechTrees_Units_LocationInAge->Update();
	TechTrees_Units_RequiredResearch->Update();
	TechTrees_Units_LineMode->Update();
	TechTrees_Units_EnablingResearch->Update();

	ListTTUnitUnits();
	ListTTUnitItems();
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
	auto selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->TechTree.UnitConnections, TTUnitConIDs[0]);
	ListTTUnits();
}

void AGE_Frame::OnTTUnitDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.UnitConnections, TTUnitConIDs);
	ListTTUnits();
}

void AGE_Frame::OnTTUnitCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.UnitConnections, TTUnitConIDs, copies->TTUnitCon);
}

void AGE_Frame::OnTTUnitPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTUnitConIDs.size(), copies->TTUnitCon.size()))
		{
			PasteToList(GenieFile->TechTree.UnitConnections, TTUnitConIDs, copies->TTUnitCon);
		}
	}
	else
	{
		PasteToList(GenieFile->TechTree.UnitConnections, TTUnitConIDs[0], copies->TTUnitCon);
	}
	ListTTUnits();
}

void AGE_Frame::OnTTUnitPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(selections < 1) return;

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
	searchText = TechTrees_Units_Units.Search->GetValue().Lower();
	excludeText = TechTrees_Units_Units.SearchRecursive->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units[loop]);
		}
	}
	Listing(TechTrees_Units_Units.List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTTUnitUnitSelect(E);
}

void AGE_Frame::OnTTUnitUnitSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_Units_Units.List->GetSelections(Items);
	if(selections > 0)
	{
		TTUnitUnitIDs.resize(selections);
		TechTrees_Units_Units.Item->resize(selections);

		int32_t * UnitPointer;
		for(auto loop = selections; loop--> 0;)
		{
			UnitPointer = (int32_t*)TechTrees_Units_Units.List->GetClientData(Items.Item(loop));
			TTUnitUnitIDs[loop] = (UnitPointer - (&GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units[0]));
			TechTrees_Units_Units.Item->container[loop] = UnitPointer;
		}

		TechTrees_Units_Units.Item->Update();
	}
	else
	{
		TechTrees_Units_Units.Item->Clear();
		TechTrees_Units_Units.ItemCombo->SetSelection(0);
	}
	TechTrees_Units_Units.Item->Enable(selections);
	TechTrees_Units_Units.ItemCombo->Enable(selections);
}

void AGE_Frame::OnTTUnitUnitAdd(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units);
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Units_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs[0]);
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_Units_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs);
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Units_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs, copies->TTUnitUnit);
}

void AGE_Frame::OnTTUnitUnitPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Units_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTUnitUnitIDs.size(), copies->TTUnitUnit.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs, copies->TTUnitUnit);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs[0], copies->TTUnitUnit);
	}
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Units_Units.List->GetSelections(Items);
	if(selections < 1) return;

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

void AGE_Frame::ListTTCommonItems(AGE_AreaTT84 &area, genie::techtree::Common* dataPointer)
{
	searchText = area.Search->GetValue().Lower();
	excludeText = area.SearchRecursive->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < dataPointer->getSlots(); ++loop)
	{
		wxString Name = " ";
		switch(dataPointer->Mode[loop])
		{
			case 0:
				Name += "Age: "+lexical_cast<string>(dataPointer->UnitResearch[loop]);
				break;
			case 1:
				Name += "Building: "+GetBuildingName(dataPointer->UnitResearch[loop]);
				break;
			case 2:
				Name += "Unit: "+GetBuildingName(dataPointer->UnitResearch[loop]);
				break;
			case 3:
				Name += "Research: "+GetSimpleResearchName(dataPointer->UnitResearch[loop]);
				break;
			default:
				Name += lexical_cast<string>(dataPointer->Mode[loop])+" None: "+lexical_cast<string>(dataPointer->UnitResearch[loop]);
		}
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&dataPointer->Mode[loop]);
		}
	}
	Listing(area.List, filteredNames, dataPointers);
}

void AGE_Frame::OnTTUnitItemSearch(wxCommandEvent &Event)
{
	ListTTUnitItems();
}

void AGE_Frame::ListTTUnitItems()
{
	ListTTCommonItems(TechTrees_Units_Items, &GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Common);
	wxCommandEvent E;
	OnTTUnitItemSelect(E);
}

void AGE_Frame::OnTTUnitItemSelect(wxCommandEvent &Event)
{
	SelectTTCommonItems(TechTrees_Units_Items, &GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Common);
}

void AGE_Frame::OnTTUnitItemCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Units_Items.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Common.UnitResearch, TTItemIDs, copies->TTItem);
	CopyFromList(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Common.Mode, TTItemIDs, copies->TTMode);
}

void AGE_Frame::OnTTUnitItemPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Units_Items.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTItemIDs.size(), copies->TTItem.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Common.UnitResearch, TTItemIDs, copies->TTItem);
			PasteToListNoGV(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Common.Mode, TTItemIDs, copies->TTMode);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Common.UnitResearch, TTItemIDs[0], copies->TTItem);
		PasteToListNoGV(GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Common.Mode, TTItemIDs[0], copies->TTMode);
	}
	ListTTUnitItems();
}

void AGE_Frame::OnTTUnitItemCopyToUnits(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTUnitConIDs.size(); ++loop)
	{
		GenieFile->TechTree.UnitConnections[TTUnitConIDs[loop]].Common = GenieFile->TechTree.UnitConnections[TTUnitConIDs[0]].Common;
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
			case 1: // Status
				Name += "S "+lexical_cast<string>((short)GenieFile->TechTree.ResearchConnections[Index].Unknown1);
				break;
			case 2: // Upper Building
				Name += "U "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].UpperBuilding);
				break;
			case 3: // Required Items
				Name += "I "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].Common.SlotsUsed);
				break;
			case 4: // Age
				Name += "A "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].Common.UnitResearch[0]);
				break;
			case 5: // Vertical Line Number
				Name += "V "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].VerticalLine);
				break;
			case 6: // Location in Age
				Name += "LA "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].LocationInAge);
				break;
			case 7: // First Age Mode
				Name += "LM "+lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].LineMode);
				break;
		}
		Name += ", ";
		if(Selection[loop+1] < 1) break;
	}

	Name += lexical_cast<string>(GenieFile->TechTree.ResearchConnections[Index].ID)+" ";
	if(GenieFile->Researchs.size() <= GenieFile->TechTree.ResearchConnections[Index].ID) return Name;
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
	InitTTResearches();
	wxCommandEvent E;
	OnTTResearchSelect(E);
}

void AGE_Frame::InitTTResearches()
{
	searchText = TechTrees_MainList_Researches_Search->GetValue().Lower();
	excludeText = TechTrees_MainList_Researches_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = TechTrees_MainList_Researches_UseAnd[loop]->GetValue();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.ResearchConnections.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTTResearchName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.ResearchConnections[loop]);
		}
	}

	Listing(TechTrees_MainList_Researches_List, filteredNames, dataPointers);

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;
}

void AGE_Frame::OnTTResearchSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(selections < 1) return;

	TTResConIDs.resize(selections);
	TechTrees_Researches_ID->resize(selections);
	TechTrees_Researches_Always2->resize(selections);
	TechTrees_Researches_UpperBuilding->resize(selections);
	TechTrees_Researches_Items.UsedItems->resize(selections);
	TechTrees_Researches_VerticalLine->resize(selections);
	TechTrees_Researches_LocationInAge->resize(selections);
	TechTrees_Researches_LineMode->resize(selections);

	genie::ResearchConnection * ResearchConPointer;
	for(auto sel = selections; sel--> 0;)
	{
		ResearchConPointer = (genie::ResearchConnection*)TechTrees_MainList_Researches_List->GetClientData(Items.Item(sel));
		TTResConIDs[sel] = (ResearchConPointer - (&GenieFile->TechTree.ResearchConnections[0]));

		TechTrees_Researches_ID->container[sel] = &ResearchConPointer->ID;
		TechTrees_Researches_Always2->container[sel] = &ResearchConPointer->Unknown1;
		TechTrees_Researches_UpperBuilding->container[sel] = &ResearchConPointer->UpperBuilding;
		TechTrees_Researches_Items.UsedItems->container[sel] = &ResearchConPointer->Common.SlotsUsed;
		TechTrees_Researches_VerticalLine->container[sel] = &ResearchConPointer->VerticalLine;
		TechTrees_Researches_LocationInAge->container[sel] = &ResearchConPointer->LocationInAge;
		TechTrees_Researches_LineMode->container[sel] = &ResearchConPointer->LineMode;
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected research: "+lexical_cast<string>(TTResConIDs[0]), 0);

	TechTrees_Researches_ID->Update();
	TechTrees_Researches_Always2->Update();
	TechTrees_Researches_UpperBuilding->Update();
	TechTrees_Researches_Items.UsedItems->Update();
	TechTrees_Researches_VerticalLine->Update();
	TechTrees_Researches_LocationInAge->Update();
	TechTrees_Researches_LineMode->Update();

	ListTTResearchBuildings();
	ListTTResearchUnits();
	ListTTResearchResearches();
	ListTTResearchItems();
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
	auto selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->TechTree.ResearchConnections, TTResConIDs[0]);
	ListTTResearches();
}

void AGE_Frame::OnTTResearchDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.ResearchConnections, TTResConIDs);
	ListTTResearches();
}

void AGE_Frame::OnTTResearchCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.ResearchConnections, TTResConIDs, copies->TTResCon);
}

void AGE_Frame::OnTTResearchPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTResConIDs.size(), copies->TTResCon.size()))
		{
			PasteToList(GenieFile->TechTree.ResearchConnections, TTResConIDs, copies->TTResCon);
		}
	}
	else
	{
		PasteToList(GenieFile->TechTree.ResearchConnections, TTResConIDs[0], copies->TTResCon);
	}
	ListTTResearches();
}

void AGE_Frame::OnTTResearchPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(selections < 1) return;

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
	searchText = TechTrees_Researches_Buildings.Search->GetValue().Lower();
	excludeText = TechTrees_Researches_Buildings.SearchRecursive->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetBuildingName(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings[loop]);
		}
	}
	Listing(TechTrees_Researches_Buildings.List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTTResearchBuildingSelect(E);
}

void AGE_Frame::OnTTResearchBuildingSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Buildings.List->GetSelections(Items);
	if(selections > 0)
	{
		TTResBuildIDs.resize(selections);
		TechTrees_Researches_Buildings.Item->resize(selections);

		int32_t * BuildingPointer;
		for(auto loop = selections; loop--> 0;)
		{
			BuildingPointer = (int32_t*)TechTrees_Researches_Buildings.List->GetClientData(Items.Item(loop));
			TTResBuildIDs[loop] = (BuildingPointer - (&GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings[0]));
			TechTrees_Researches_Buildings.Item->container[loop] = BuildingPointer;
		}

		TechTrees_Researches_Buildings.Item->Update();
	}
	else
	{
		TechTrees_Researches_Buildings.Item->Clear();
		TechTrees_Researches_Buildings.ItemCombo->SetSelection(0);
	}
	TechTrees_Researches_Buildings.Item->Enable(selections);
	TechTrees_Researches_Buildings.ItemCombo->Enable(selections);
}

void AGE_Frame::OnTTResearchBuildingAdd(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings);
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs[0]);
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs);
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs, copies->TTResBuild);
}

void AGE_Frame::OnTTResearchBuildingPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTResBuildIDs.size(), copies->TTResBuild.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs, copies->TTResBuild);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs[0], copies->TTResBuild);
	}
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Buildings.List->GetSelections(Items);
	if(selections < 1) return;

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
	searchText = TechTrees_Researches_Units.Search->GetValue().Lower();
	excludeText = TechTrees_Researches_Units.SearchRecursive->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units[loop]);
		}
	}
	Listing(TechTrees_Researches_Units.List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTTResearchUnitSelect(E);
}

void AGE_Frame::OnTTResearchUnitSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Units.List->GetSelections(Items);
	if(selections > 0)
	{
		TTResUnitIDs.resize(selections);
		TechTrees_Researches_Units.Item->resize(selections);

		int32_t * UnitPointer;
		for(auto loop = selections; loop--> 0;)
		{
			UnitPointer = (int32_t*)TechTrees_Researches_Units.List->GetClientData(Items.Item(loop));
			TTResUnitIDs[loop] = (UnitPointer - (&GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units[0]));
			TechTrees_Researches_Units.Item->container[loop] = UnitPointer;
		}

		TechTrees_Researches_Units.Item->Update();
	}
	else
	{
		TechTrees_Researches_Units.Item->Clear();
		TechTrees_Researches_Units.ItemCombo->SetSelection(0);
	}
	TechTrees_Researches_Units.Item->Enable(selections);
	TechTrees_Researches_Units.ItemCombo->Enable(selections);
}

void AGE_Frame::OnTTResearchUnitAdd(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units);
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs[0]);
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs);
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs, copies->TTResUnit);
}

void AGE_Frame::OnTTResearchUnitPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Units.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTResUnitIDs.size(), copies->TTResUnit.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs, copies->TTResUnit);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs[0], copies->TTResUnit);
	}
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Units.List->GetSelections(Items);
	if(selections < 1) return;

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
	searchText = TechTrees_Researches_Researches.Search->GetValue().Lower();
	excludeText = TechTrees_Researches_Researches.SearchRecursive->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetSimpleResearchName(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches[loop]);
		}
	}
	Listing(TechTrees_Researches_Researches.List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnTTResearchResearchSelect(E);
}

void AGE_Frame::OnTTResearchResearchSelect(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Researches.List->GetSelections(Items);
	if(selections > 0)
	{
		TTResResIDs.resize(selections);
		TechTrees_Researches_Researches.Item->resize(selections);

		int32_t * ResearchPointer;
		for(auto loop = selections; loop--> 0;)
		{
			ResearchPointer = (int32_t*)TechTrees_Researches_Researches.List->GetClientData(Items.Item(loop));
			TTResResIDs[loop] = (ResearchPointer - (&GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches[0]));
			TechTrees_Researches_Researches.Item->container[loop] = ResearchPointer;
		}

		TechTrees_Researches_Researches.Item->Update();
	}
	else
	{
		TechTrees_Researches_Researches.Item->Clear();
		TechTrees_Researches_Researches.ItemCombo->SetSelection(0);
	}
	TechTrees_Researches_Researches.Item->Enable(selections);
	TechTrees_Researches_Researches.ItemCombo->Enable(selections);
}

void AGE_Frame::OnTTResearchResearchAdd(wxCommandEvent &Event)
{
	auto selections = TechTrees_MainList_Researches_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches);
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs[0]);
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchDelete(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs);
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs, copies->TTResRes);
}

void AGE_Frame::OnTTResearchResearchPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Researches.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTResResIDs.size(), copies->TTResRes.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs, copies->TTResRes);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs[0], copies->TTResRes);
	}
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchPasteInsert(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Researches.List->GetSelections(Items);
	if(selections < 1) return;

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

void AGE_Frame::OnTTResearchItemSearch(wxCommandEvent &Event)
{
	ListTTResearchItems();
}

void AGE_Frame::ListTTResearchItems()
{
	ListTTCommonItems(TechTrees_Researches_Items, &GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Common);
	wxCommandEvent E;
	OnTTResearchItemSelect(E);
}

void AGE_Frame::OnTTResearchItemSelect(wxCommandEvent &Event)
{
	SelectTTCommonItems(TechTrees_Researches_Items, &GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Common);
}

void AGE_Frame::OnTTResearchItemCopy(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Items.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Common.UnitResearch, TTItemIDs, copies->TTItem);
	CopyFromList(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Common.Mode, TTItemIDs, copies->TTMode);
}

void AGE_Frame::OnTTResearchItemPaste(wxCommandEvent &Event)
{
	auto selections = TechTrees_Researches_Items.List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTItemIDs.size(), copies->TTItem.size()))
		{
			PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Common.UnitResearch, TTItemIDs, copies->TTItem);
			PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Common.Mode, TTItemIDs, copies->TTMode);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Common.UnitResearch, TTItemIDs[0], copies->TTItem);
		PasteToListNoGV(GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Common.Mode, TTItemIDs[0], copies->TTMode);
	}
	ListTTResearchItems();
}

void AGE_Frame::OnTTResearchItemCopyToResearches(wxCommandEvent &Event)
{
	for(short loop=1; loop < TTResConIDs.size(); ++loop)
	{
		GenieFile->TechTree.ResearchConnections[TTResConIDs[loop]].Common = GenieFile->TechTree.ResearchConnections[TTResConIDs[0]].Common;
	}
}

void AGE_Frame::CreateTechTreeControls()
{
	Tab_TechTrees = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	TechTrees_Main = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_All = new wxBoxSizer(wxVERTICAL);
	TabBar_TechTree = new wxNotebook(Tab_TechTrees, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	Tab_TechTreeAges = new wxPanel(TabBar_TechTree, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	Tab_TechTreeBuildings = new wxPanel(TabBar_TechTree, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	Tab_TechTreeUnits = new wxPanel(TabBar_TechTree, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	Tab_TechTreeResearches = new wxPanel(TabBar_TechTree, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	TechTrees_TabAges = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_TabBuildings = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_TabUnits = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_TabResearches = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_ScrollerAges = new wxScrolledWindow(Tab_TechTreeAges, wxID_ANY, wxDefaultPosition, wxSize(600, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	TechTrees_ScrollerBuildings = new wxScrolledWindow(Tab_TechTreeBuildings, wxID_ANY, wxDefaultPosition, wxSize(600, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	TechTrees_ScrollerUnits = new wxScrolledWindow(Tab_TechTreeUnits, wxID_ANY, wxDefaultPosition, wxSize(600, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	TechTrees_ScrollerResearches = new wxScrolledWindow(Tab_TechTreeResearches, wxID_ANY, wxDefaultPosition, wxSize(600, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	TechTrees_ScrollArea1 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_ScrollArea2 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_ScrollArea3 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_ScrollArea4 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_ScrollSpace1 = new wxBoxSizer(wxVERTICAL);
	TechTrees_ScrollSpace2 = new wxBoxSizer(wxVERTICAL);
	TechTrees_ScrollSpace3 = new wxBoxSizer(wxVERTICAL);
	TechTrees_ScrollSpace4 = new wxBoxSizer(wxVERTICAL);

	wxString StatusHelp = "3 marks this as not available";
	wxString LocationInAgeHelp = "0 Hidden\n1 First\n2 Second";
	wxString LineModeHelp = "0 research: First age\n1 age: ?\n2 unit: First in vertical line\n3 unit: Not first\n4 research: Others\n5 building: One or more connections\n6 building: No connections";

	General_Variables2_Holder = new wxStaticBoxSizer(wxVERTICAL, Tab_TechTrees, "Technology Tree Related");
	General_Variables2_Grid = new wxGridSizer(8, 5, 5);
	for(short loop = 0; loop < General_TTUnknown.size(); ++loop)
	{
		General_TTUnknown_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		General_TTUnknown_Text[loop] = new wxStaticText(Tab_TechTrees, wxID_ANY, " Unknown "+lexical_cast<string>(loop+1), wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		General_TTUnknown[loop] = new TextCtrl_Long(this, AGEwindow, Tab_TechTrees);
	}
	General_TTUnknown[7]->SetToolTip("In the file this is between\nage/building/unit/research\ncounts and their data");

	TechTrees_MainList_Ages = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Buildings = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Units = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Researches = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Ages_Search = new wxTextCtrl(Tab_TechTreeAges, wxID_ANY);
	TechTrees_MainList_Ages_Search_R = new wxTextCtrl(Tab_TechTreeAges, wxID_ANY);
	TechTrees_MainList_Ages_List = new wxListBox(Tab_TechTreeAges, wxID_ANY, wxDefaultPosition, wxSize(200, 300), 0, NULL, wxLB_EXTENDED);
	TechTrees_MainList_Ages_Buttons = new wxGridSizer(3, 0, 0);
	TechTrees_MainList_Ages_Add = new wxButton(Tab_TechTreeAges, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Insert = new wxButton(Tab_TechTreeAges, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Delete = new wxButton(Tab_TechTreeAges, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Copy = new wxButton(Tab_TechTreeAges, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Paste = new wxButton(Tab_TechTreeAges, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_PasteInsert = new wxButton(Tab_TechTreeAges, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	TechTrees_Ages_ID_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_ID_Text = new wxStaticText(TechTrees_ScrollerAges, wxID_ANY, " Age Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_ID = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerAges);
	TechTrees_Ages_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Unknown2_Text = new wxStaticText(TechTrees_ScrollerAges, wxID_ANY, " Status *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_Unknown2 = new TextCtrl_Byte(this, AGEwindow, TechTrees_ScrollerAges);
	TechTrees_Ages_Unknown2->SetToolTip(StatusHelp);

	TechTrees_Ages_LineMode_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_LineMode_Text = new wxStaticText(TechTrees_ScrollerAges, wxID_ANY, " Line Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_LineMode = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerAges);
	TechTrees_Ages_LineMode->SetToolTip(LineModeHelp);
	TechTrees_Data_Ages = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Ages2 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Data_Ages1 = new wxGridSizer(5, 5, 5);
	TechTrees_ConnectedHolder_Ages = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Ages_Buildings.CreateControls(this, AGEwindow, TechTrees_ScrollerAges, "Connected Buildings", "ages");
	UnitComboBoxList.push_back(TechTrees_Ages_Buildings.ItemCombo);
	TechTrees_Ages_Units.CreateControls(this, AGEwindow, TechTrees_ScrollerAges, "Connected Units", "ages");
	UnitComboBoxList.push_back(TechTrees_Ages_Units.ItemCombo);
	TechTrees_Ages_Researches.CreateControls(this, AGEwindow, TechTrees_ScrollerAges, "Connected Researches", "ages");
	ResearchComboBoxList.push_back(TechTrees_Ages_Researches.ItemCombo);

	TechTrees_Ages_Items.CreateControls(this, AGEwindow, TechTrees_ScrollerAges, "ages");
	TechTrees_Ages_UnknownItems.CreateControls(this, AGEwindow, TechTrees_ScrollerAges);

	TechTrees_MainList_Buildings_Search = new wxTextCtrl(Tab_TechTreeBuildings, wxID_ANY);
	TechTrees_MainList_Buildings_UseAnd[0] = new wxCheckBox(Tab_TechTreeBuildings, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	TechTrees_MainList_Buildings_Search_R = new wxTextCtrl(Tab_TechTreeBuildings, wxID_ANY);
	TechTrees_MainList_Buildings_UseAnd[1] = new wxCheckBox(Tab_TechTreeBuildings, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	for(short loop = 0; loop < 2; ++loop)
	{
		TechTrees_MainList_Buildings_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		TechTrees_MainList_Buildings_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_TechTreeBuildings, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
		TechTrees_Buildings_TotalUnitsTechs_Grid[loop] = new wxGridSizer(5, 0, 5);
	}
	TechTrees_MainList_Buildings_List = new wxListBox(Tab_TechTreeBuildings, wxID_ANY, wxDefaultPosition, wxSize(200, 300), 0, NULL, wxLB_EXTENDED);
	TechTrees_MainList_Buildings_Buttons = new wxGridSizer(3, 0, 0);
	TechTrees_MainList_Buildings_Add = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Insert = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Delete = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Copy = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Paste = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_PasteInsert = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	TechTrees_Buildings_ID_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_ID_Text = new wxStaticText(TechTrees_ScrollerBuildings, wxID_ANY, " Building Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_ID = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerBuildings);
	TechTrees_Buildings_ID_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerBuildings, TechTrees_Buildings_ID);
	UnitComboBoxList.push_back(TechTrees_Buildings_ID_ComboBox);
	TechTrees_Buildings_Always2_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Always2_Text = new wxStaticText(TechTrees_ScrollerBuildings, wxID_ANY, " Status *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_Always2 = new TextCtrl_Byte(this, AGEwindow, TechTrees_ScrollerBuildings);
	TechTrees_Buildings_Always2->SetToolTip(StatusHelp);
	TechTrees_Buildings_LocationInAge_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_LocationInAge_Text = new wxStaticText(TechTrees_ScrollerBuildings, wxID_ANY, " Location in Age *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_LocationInAge = new TextCtrl_Byte(this, AGEwindow, TechTrees_ScrollerBuildings);
	TechTrees_Buildings_LocationInAge->SetToolTip(LocationInAgeHelp);
	TechTrees_Buildings_LineMode_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_LineMode_Text = new wxStaticText(TechTrees_ScrollerBuildings, wxID_ANY, " Line Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_LineMode = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerBuildings);
	TechTrees_Buildings_LineMode->SetToolTip(LineModeHelp);
	TechTrees_Buildings_EnablingResearch_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_EnablingResearch_Text = new wxStaticText(TechTrees_ScrollerBuildings, wxID_ANY, " Enabling Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_EnablingResearch = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerBuildings);
	TechTrees_Buildings_EnablingResearch->SetToolTip("Makes available\nUsed by buildings, which need a research to be available");
	TechTrees_Buildings_EnablingResearch_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerBuildings, TechTrees_Buildings_EnablingResearch);
	ResearchComboBoxList.push_back(TechTrees_Buildings_EnablingResearch_ComboBox);

	//TechTrees_Buildings_Unknown3[2]->SetToolTip("Units+techs in 1st Age?");
	//TechTrees_Buildings_Unknown3[3]->SetToolTip("Units+techs in 2nd Age?");
	//TechTrees_Buildings_Unknown3[4]->SetToolTip("Units+techs in 3rd Age?");
	//TechTrees_Buildings_Unknown3[5]->SetToolTip("Units+techs in 4th Age?");
	//TechTrees_Buildings_Unknown3[7]->SetToolTip("Units+techs on first line in 1st Age?");
	//TechTrees_Buildings_Unknown3[8]->SetToolTip("Units+techs on first line in 2nd Age?");
	//TechTrees_Buildings_Unknown3[9]->SetToolTip("Units+techs on first line in 3rd Age?");
	//TechTrees_Buildings_Unknown3[10]->SetToolTip("Units+techs on first line in 4th Age?");
	TechTrees_Data_Buildings = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Buildings2 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Data_Buildings3 = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Buildings1 = new wxGridSizer(5, 5, 5);
	TechTrees_ConnectedHolder_Buildings = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Buildings_Buildings.CreateControls(this, AGEwindow, TechTrees_ScrollerBuildings, "Connected Buildings", "buildings");
	UnitComboBoxList.push_back(TechTrees_Buildings_Buildings.ItemCombo);
	TechTrees_Buildings_Units.CreateControls(this, AGEwindow, TechTrees_ScrollerBuildings, "Connected Units", "buildings");
	UnitComboBoxList.push_back(TechTrees_Buildings_Units.ItemCombo);
	TechTrees_Buildings_Researches.CreateControls(this, AGEwindow, TechTrees_ScrollerBuildings, "Connected Researches", "buildings");
	ResearchComboBoxList.push_back(TechTrees_Buildings_Researches.ItemCombo);

	TechTrees_Buildings_Items.CreateControls(this, AGEwindow, TechTrees_ScrollerBuildings, "buildings");

	TechTrees_Buildings_TotalUnitsTechs_Holder[0] = new wxStaticBoxSizer(wxVERTICAL, TechTrees_ScrollerBuildings, "Total units and techs by age *");
	TechTrees_Buildings_TotalUnitsTechs_Holder[1] = new wxStaticBoxSizer(wxVERTICAL, TechTrees_ScrollerBuildings, "Total units and techs at first in age *");
	for(short loop = 0; loop < 10; ++loop)
	TechTrees_Buildings_TotalUnitsTechs[loop] = new TextCtrl_Byte(this, AGEwindow, TechTrees_ScrollerBuildings);
	for(short loop = 0; loop < 5; ++loop)
	{
		TechTrees_Buildings_TotalUnitsTechs[loop]->SetToolTip("Age "+lexical_cast<string>(loop+1));
		TechTrees_Buildings_TotalUnitsTechs[loop+5]->SetToolTip("Age "+lexical_cast<string>(loop+1));
	}

	TechTrees_MainList_Units_Search = new wxTextCtrl(Tab_TechTreeUnits, wxID_ANY);
	TechTrees_MainList_Units_UseAnd[0] = new wxCheckBox(Tab_TechTreeUnits, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	TechTrees_MainList_Units_Search_R = new wxTextCtrl(Tab_TechTreeUnits, wxID_ANY);
	TechTrees_MainList_Units_UseAnd[1] = new wxCheckBox(Tab_TechTreeUnits, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	for(short loop = 0; loop < 2; ++loop)
	{
		TechTrees_MainList_Units_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		TechTrees_MainList_Units_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_TechTreeUnits, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	TechTrees_MainList_Units_List = new wxListBox(Tab_TechTreeUnits, wxID_ANY, wxDefaultPosition, wxSize(200, 300), 0, NULL, wxLB_EXTENDED);
	TechTrees_MainList_Units_Buttons = new wxGridSizer(3, 0, 0);
	TechTrees_MainList_Units_Add = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Insert = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Delete = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Copy = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Paste = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_PasteInsert = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	TechTrees_Units_ID_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_ID_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Unit Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_ID = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_ID_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerUnits, TechTrees_Units_ID);
	UnitComboBoxList.push_back(TechTrees_Units_ID_ComboBox);
	TechTrees_Units_Always2_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Always2_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Status *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_Always2 = new TextCtrl_Byte(this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_Always2->SetToolTip(StatusHelp);
	TechTrees_Units_UpperBuilding_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_UpperBuilding_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Upper Building", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_UpperBuilding = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_UpperBuilding_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerUnits, TechTrees_Units_UpperBuilding);
	UnitComboBoxList.push_back(TechTrees_Units_UpperBuilding_ComboBox);
	TechTrees_Units_VerticalLine_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_VerticalLine_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Vertical Line Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_VerticalLine = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_LocationInAge_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_LocationInAge_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Location in Age *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_LocationInAge = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_LocationInAge->SetToolTip(LocationInAgeHelp);
	TechTrees_Units_RequiredResearch_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_RequiredResearch_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Required Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_RequiredResearch = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_RequiredResearch->SetToolTip("Upgrades unit\nUsed by units, which aren't first in upgrade line");
	TechTrees_Units_RequiredResearch_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerUnits, TechTrees_Units_RequiredResearch);
	ResearchComboBoxList.push_back(TechTrees_Units_RequiredResearch_ComboBox);
	TechTrees_Units_LineMode_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_LineMode_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Line Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_LineMode = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_LineMode->SetToolTip(LineModeHelp);
	TechTrees_Units_EnablingResearch_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_EnablingResearch_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Enabling Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_EnablingResearch = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_EnablingResearch->SetToolTip("Makes available\nUsed by units, which need a research to be available");
	TechTrees_Units_EnablingResearch_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerUnits, TechTrees_Units_EnablingResearch);
	ResearchComboBoxList.push_back(TechTrees_Units_EnablingResearch_ComboBox);

	TechTrees_Data_Units = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Units1 = new wxGridSizer(5, 5, 5);
	TechTrees_ConnectedHolder_Units = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Units_Items.CreateControls(this, AGEwindow, TechTrees_ScrollerUnits, "units");
	TechTrees_Units_Units.CreateControls(this, AGEwindow, TechTrees_ScrollerUnits, "Connected Units", "units");
	UnitComboBoxList.push_back(TechTrees_Units_Units.ItemCombo);

	TechTrees_MainList_Researches_Search = new wxTextCtrl(Tab_TechTreeResearches, wxID_ANY);
	TechTrees_MainList_Researches_UseAnd[0] = new wxCheckBox(Tab_TechTreeResearches, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	TechTrees_MainList_Researches_Search_R = new wxTextCtrl(Tab_TechTreeResearches, wxID_ANY);
	TechTrees_MainList_Researches_UseAnd[1] = new wxCheckBox(Tab_TechTreeResearches, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	for(short loop = 0; loop < 2; ++loop)
	{
		TechTrees_MainList_Researches_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		TechTrees_MainList_Researches_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_TechTreeResearches, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	TechTrees_MainList_Researches_List = new wxListBox(Tab_TechTreeResearches, wxID_ANY, wxDefaultPosition, wxSize(200, 300), 0, NULL, wxLB_EXTENDED);
	TechTrees_MainList_Researches_Buttons = new wxGridSizer(3, 0, 0);
	TechTrees_MainList_Researches_Add = new wxButton(Tab_TechTreeResearches, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_Insert = new wxButton(Tab_TechTreeResearches, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_Delete = new wxButton(Tab_TechTreeResearches, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_Copy = new wxButton(Tab_TechTreeResearches, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_Paste = new wxButton(Tab_TechTreeResearches, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Researches_PasteInsert = new wxButton(Tab_TechTreeResearches, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	TechTrees_Data_Researches = new wxBoxSizer(wxVERTICAL);
	TechTrees_Data_Researches2 = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Data_Researches1 = new wxGridSizer(3, 5, 5);
	TechTrees_Data_Researches3 = new wxBoxSizer(wxVERTICAL);
	TechTrees_ConnectedHolder_Researches = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_Researches_Buildings.CreateControls(this, AGEwindow, TechTrees_ScrollerResearches, "Connected Buildings", "researches");
	UnitComboBoxList.push_back(TechTrees_Researches_Buildings.ItemCombo);
	TechTrees_Researches_Units.CreateControls(this, AGEwindow, TechTrees_ScrollerResearches, "Connected Units", "researches");
	UnitComboBoxList.push_back(TechTrees_Researches_Units.ItemCombo);
	TechTrees_Researches_Researches.CreateControls(this, AGEwindow, TechTrees_ScrollerResearches, "Connected Researches", "researches");
	ResearchComboBoxList.push_back(TechTrees_Researches_Researches.ItemCombo);

	TechTrees_Researches_ID_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_ID_Text = new wxStaticText(TechTrees_ScrollerResearches, wxID_ANY, " Research Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_ID = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerResearches);
	TechTrees_Researches_ID_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerResearches, TechTrees_Researches_ID);
	ResearchComboBoxList.push_back(TechTrees_Researches_ID_ComboBox);
	TechTrees_Researches_Always2_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Always2_Text = new wxStaticText(TechTrees_ScrollerResearches, wxID_ANY, " Status *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_Always2 = new TextCtrl_Byte(this, AGEwindow, TechTrees_ScrollerResearches);
	TechTrees_Researches_Always2->SetToolTip(StatusHelp);
	TechTrees_Researches_UpperBuilding_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_UpperBuilding_Text = new wxStaticText(TechTrees_ScrollerResearches, wxID_ANY, " Upper Building", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_UpperBuilding = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerResearches);
	TechTrees_Researches_UpperBuilding_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerResearches, TechTrees_Researches_UpperBuilding);
	UnitComboBoxList.push_back(TechTrees_Researches_UpperBuilding_ComboBox);
	TechTrees_Researches_VerticalLine_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_VerticalLine_Text = new wxStaticText(TechTrees_ScrollerResearches, wxID_ANY, " Vertical Line Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_VerticalLine = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerResearches);
	TechTrees_Researches_LocationInAge_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_LocationInAge_Text = new wxStaticText(TechTrees_ScrollerResearches, wxID_ANY, " Location in Age *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_LocationInAge = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerResearches);
	TechTrees_Researches_LocationInAge->SetToolTip(LocationInAgeHelp);
	TechTrees_Researches_LineMode_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_LineMode_Text = new wxStaticText(TechTrees_ScrollerResearches, wxID_ANY, " Line Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_LineMode = new TextCtrl_Long(this, AGEwindow, TechTrees_ScrollerResearches);
	TechTrees_Researches_LineMode->SetToolTip(LineModeHelp);

	TechTrees_Researches_Items.CreateControls(this, AGEwindow, TechTrees_ScrollerResearches, "researches");

	TabBar_TechTree->AddPage(Tab_TechTreeAges, "Ages");
	TabBar_TechTree->AddPage(Tab_TechTreeBuildings, "Buildings");
	TabBar_TechTree->AddPage(Tab_TechTreeUnits, "Units");
	TabBar_TechTree->AddPage(Tab_TechTreeResearches, "Researches");
	TabBar_TechTree->ChangeSelection(0);

	for(short loop = 0; loop < 2; ++loop)
	{
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Normal Name");	// 0
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Status");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Upper Building");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Required Items");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Age (1st Item)");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Vertical Line Number");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Location in Age");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Required Research");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Line Mode");
		TechTrees_MainList_Units_SearchFilters[loop]->Append("Enabling Research");
		TechTrees_MainList_Units_SearchFilters[loop]->SetSelection(0);

		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Normal Name");	// 0
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Status");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Required Items");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Age (1st Item)");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Location in Age");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Units & Techs by Age");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Units & Techs @ 1st by Age");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Line Mode");
		TechTrees_MainList_Buildings_SearchFilters[loop]->Append("Enabling Research");
		TechTrees_MainList_Buildings_SearchFilters[loop]->SetSelection(0);

		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Normal Name");	// 0
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Status");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Upper Building");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Required Items");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Age (1st Item)");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Vertical Line Number");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Location in Age");
		TechTrees_MainList_Researches_SearchFilters[loop]->Append("Line Mode");
		TechTrees_MainList_Researches_SearchFilters[loop]->SetSelection(0);
	}

	for(short loop = 0; loop < General_TTUnknown.size(); ++loop)
	{
		General_TTUnknown_Holder[loop]->Add(General_TTUnknown_Text[loop], 0, wxEXPAND);
		General_TTUnknown_Holder[loop]->Add(General_TTUnknown[loop], 0, wxEXPAND);
		General_Variables2_Grid->Add(General_TTUnknown_Holder[loop], 1, wxEXPAND);
	}
	General_Variables2_Holder->Add(General_Variables2_Grid, 0, wxEXPAND);

	TechTrees_MainList_Ages_Buttons->Add(TechTrees_MainList_Ages_Add, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Buttons->Add(TechTrees_MainList_Buildings_Add, 1, wxEXPAND);
	TechTrees_MainList_Units_Buttons->Add(TechTrees_MainList_Units_Add, 1, wxEXPAND);
	TechTrees_MainList_Researches_Buttons->Add(TechTrees_MainList_Researches_Add, 1, wxEXPAND);
	TechTrees_MainList_Ages_Buttons->Add(TechTrees_MainList_Ages_Delete, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Buttons->Add(TechTrees_MainList_Buildings_Delete, 1, wxEXPAND);
	TechTrees_MainList_Units_Buttons->Add(TechTrees_MainList_Units_Delete, 1, wxEXPAND);
	TechTrees_MainList_Researches_Buttons->Add(TechTrees_MainList_Researches_Delete, 1, wxEXPAND);
	TechTrees_MainList_Ages_Buttons->Add(TechTrees_MainList_Ages_Insert, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Buttons->Add(TechTrees_MainList_Buildings_Insert, 1, wxEXPAND);
	TechTrees_MainList_Units_Buttons->Add(TechTrees_MainList_Units_Insert, 1, wxEXPAND);
	TechTrees_MainList_Researches_Buttons->Add(TechTrees_MainList_Researches_Insert, 1, wxEXPAND);
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
	TechTrees_MainList_Buildings_Searches[0]->AddSpacer(2);
	TechTrees_MainList_Buildings_Searches[0]->Add(TechTrees_MainList_Buildings_UseAnd[0], 0, wxEXPAND);
	TechTrees_MainList_Buildings_Searches[1]->Add(TechTrees_MainList_Buildings_Search_R, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Searches[1]->AddSpacer(2);
	TechTrees_MainList_Buildings_Searches[1]->Add(TechTrees_MainList_Buildings_UseAnd[1], 0, wxEXPAND);
	TechTrees_MainList_Units_Searches[0]->Add(TechTrees_MainList_Units_Search, 1, wxEXPAND);
	TechTrees_MainList_Units_Searches[0]->AddSpacer(2);
	TechTrees_MainList_Units_Searches[0]->Add(TechTrees_MainList_Units_UseAnd[0], 0, wxEXPAND);
	TechTrees_MainList_Units_Searches[1]->Add(TechTrees_MainList_Units_Search_R, 1, wxEXPAND);
	TechTrees_MainList_Units_Searches[1]->AddSpacer(2);
	TechTrees_MainList_Units_Searches[1]->Add(TechTrees_MainList_Units_UseAnd[1], 0, wxEXPAND);
	TechTrees_MainList_Researches_Searches[0]->Add(TechTrees_MainList_Researches_Search, 1, wxEXPAND);
	TechTrees_MainList_Researches_Searches[0]->AddSpacer(2);
	TechTrees_MainList_Researches_Searches[0]->Add(TechTrees_MainList_Researches_UseAnd[0], 0, wxEXPAND);
	TechTrees_MainList_Researches_Searches[1]->Add(TechTrees_MainList_Researches_Search_R, 1, wxEXPAND);
	TechTrees_MainList_Researches_Searches[1]->AddSpacer(2);
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
	TechTrees_MainList_Ages->AddSpacer(2);
	TechTrees_MainList_Buildings->AddSpacer(2);
	TechTrees_MainList_Units->AddSpacer(2);
	TechTrees_MainList_Researches->AddSpacer(2);
	TechTrees_MainList_Ages->Add(TechTrees_MainList_Ages_List, 1, wxEXPAND);
	TechTrees_MainList_Buildings->Add(TechTrees_MainList_Buildings_List, 1, wxEXPAND);
	TechTrees_MainList_Units->Add(TechTrees_MainList_Units_List, 1, wxEXPAND);
	TechTrees_MainList_Researches->Add(TechTrees_MainList_Researches_List, 1, wxEXPAND);
	TechTrees_MainList_Ages->AddSpacer(2);
	TechTrees_MainList_Buildings->AddSpacer(2);
	TechTrees_MainList_Units->AddSpacer(2);
	TechTrees_MainList_Researches->AddSpacer(2);
	TechTrees_MainList_Ages->Add(TechTrees_MainList_Ages_Buttons, 0, wxEXPAND);
	TechTrees_MainList_Buildings->Add(TechTrees_MainList_Buildings_Buttons, 0, wxEXPAND);
	TechTrees_MainList_Units->Add(TechTrees_MainList_Units_Buttons, 0, wxEXPAND);
	TechTrees_MainList_Researches->Add(TechTrees_MainList_Researches_Buttons, 0, wxEXPAND);

	TechTrees_ConnectedHolder_Ages->Add(TechTrees_Ages_Buildings.ItemList, 1, wxEXPAND);
	TechTrees_ConnectedHolder_Ages->AddSpacer(5);
	TechTrees_ConnectedHolder_Ages->Add(TechTrees_Ages_Units.ItemList, 1, wxEXPAND);
	TechTrees_ConnectedHolder_Ages->AddSpacer(5);
	TechTrees_ConnectedHolder_Ages->Add(TechTrees_Ages_Researches.ItemList, 1, wxEXPAND);

	TechTrees_Ages_ID_Holder->Add(TechTrees_Ages_ID_Text, 0, wxEXPAND);
	TechTrees_Ages_ID_Holder->Add(TechTrees_Ages_ID, 0, wxEXPAND);
	TechTrees_Ages_LineMode_Holder->Add(TechTrees_Ages_LineMode_Text, 0, wxEXPAND);
	TechTrees_Ages_LineMode_Holder->Add(TechTrees_Ages_LineMode, 0, wxEXPAND);
	TechTrees_Ages_Unknown2_Holder->Add(TechTrees_Ages_Unknown2_Text, 0, wxEXPAND);
	TechTrees_Ages_Unknown2_Holder->Add(TechTrees_Ages_Unknown2, 0, wxEXPAND);

	TechTrees_Data_Ages1->Add(TechTrees_Ages_ID_Holder, 1, wxEXPAND);
	TechTrees_Data_Ages1->Add(TechTrees_Ages_Unknown2_Holder, 1, wxEXPAND);
	TechTrees_Data_Ages1->Add(TechTrees_Ages_LineMode_Holder, 1, wxEXPAND);

	TechTrees_Data_Ages2->Add(TechTrees_Ages_Items.Area, 1, wxEXPAND);
	TechTrees_Data_Ages2->AddSpacer(5);
	TechTrees_Data_Ages2->Add(TechTrees_Ages_UnknownItems.Area, 1, wxEXPAND);
	TechTrees_Data_Ages2->AddStretchSpacer(1);

	TechTrees_Data_Ages->Add(TechTrees_Data_Ages1, 0, wxEXPAND);
	TechTrees_Data_Ages->AddSpacer(5);
	TechTrees_Data_Ages->Add(TechTrees_ConnectedHolder_Ages, 0, wxEXPAND);
	TechTrees_Data_Ages->AddSpacer(5);
	TechTrees_Data_Ages->Add(TechTrees_Data_Ages2, 0, wxEXPAND);

	TechTrees_ConnectedHolder_Buildings->Add(TechTrees_Buildings_Buildings.ItemList, 1, wxEXPAND);
	TechTrees_ConnectedHolder_Buildings->AddSpacer(5);
	TechTrees_ConnectedHolder_Buildings->Add(TechTrees_Buildings_Units.ItemList, 1, wxEXPAND);
	TechTrees_ConnectedHolder_Buildings->AddSpacer(5);
	TechTrees_ConnectedHolder_Buildings->Add(TechTrees_Buildings_Researches.ItemList, 1, wxEXPAND);

	TechTrees_Buildings_ID_Holder->Add(TechTrees_Buildings_ID_Text, 0, wxEXPAND);
	TechTrees_Buildings_ID_Holder->Add(TechTrees_Buildings_ID, 0, wxEXPAND);
	TechTrees_Buildings_ID_Holder->Add(TechTrees_Buildings_ID_ComboBox, 0, wxEXPAND);
	TechTrees_Buildings_LocationInAge_Holder->Add(TechTrees_Buildings_LocationInAge_Text, 0, wxEXPAND);
	TechTrees_Buildings_LocationInAge_Holder->Add(TechTrees_Buildings_LocationInAge, 0, wxEXPAND);
	TechTrees_Buildings_LineMode_Holder->Add(TechTrees_Buildings_LineMode_Text, 0, wxEXPAND);
	TechTrees_Buildings_LineMode_Holder->Add(TechTrees_Buildings_LineMode, 0, wxEXPAND);
	TechTrees_Buildings_EnablingResearch_Holder->Add(TechTrees_Buildings_EnablingResearch_Text, 0, wxEXPAND);
	TechTrees_Buildings_EnablingResearch_Holder->Add(TechTrees_Buildings_EnablingResearch, 0, wxEXPAND);
	TechTrees_Buildings_EnablingResearch_Holder->Add(TechTrees_Buildings_EnablingResearch_ComboBox, 0, wxEXPAND);
	TechTrees_Buildings_Always2_Holder->Add(TechTrees_Buildings_Always2_Text, 0, wxEXPAND);
	TechTrees_Buildings_Always2_Holder->Add(TechTrees_Buildings_Always2, 0, wxEXPAND);

	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_ID_Holder, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_Always2_Holder, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_LocationInAge_Holder, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_LineMode_Holder, 1, wxEXPAND);
	TechTrees_Data_Buildings1->Add(TechTrees_Buildings_EnablingResearch_Holder, 1, wxEXPAND);

	for(short loop = 0; loop < 5; ++loop)
	TechTrees_Buildings_TotalUnitsTechs_Grid[0]->Add(TechTrees_Buildings_TotalUnitsTechs[loop], 0, wxEXPAND);
	for(short loop = 5; loop < 10; ++loop)
	TechTrees_Buildings_TotalUnitsTechs_Grid[1]->Add(TechTrees_Buildings_TotalUnitsTechs[loop], 0, wxEXPAND);
	TechTrees_Buildings_TotalUnitsTechs_Holder[0]->Add(TechTrees_Buildings_TotalUnitsTechs_Grid[0], 0, wxEXPAND);
	TechTrees_Buildings_TotalUnitsTechs_Holder[1]->Add(TechTrees_Buildings_TotalUnitsTechs_Grid[1], 0, wxEXPAND);
	TechTrees_Data_Buildings3->Add(TechTrees_Buildings_TotalUnitsTechs_Holder[0], 0, wxEXPAND);
	TechTrees_Data_Buildings3->AddSpacer(5);
	TechTrees_Data_Buildings3->Add(TechTrees_Buildings_TotalUnitsTechs_Holder[1], 0, wxEXPAND);
	TechTrees_Data_Buildings2->Add(TechTrees_Buildings_Items.Area, 1, wxEXPAND);
	TechTrees_Data_Buildings2->AddSpacer(5);
	TechTrees_Data_Buildings2->Add(TechTrees_Data_Buildings3, 2, wxEXPAND);

	TechTrees_Data_Buildings->Add(TechTrees_Data_Buildings1, 0, wxEXPAND);
	TechTrees_Data_Buildings->AddSpacer(5);
	TechTrees_Data_Buildings->Add(TechTrees_ConnectedHolder_Buildings, 0, wxEXPAND);
	TechTrees_Data_Buildings->AddSpacer(5);
	TechTrees_Data_Buildings->Add(TechTrees_Data_Buildings2, 0, wxEXPAND);

	TechTrees_ConnectedHolder_Units->Add(TechTrees_Units_Items.Area, 1, wxEXPAND);
	TechTrees_ConnectedHolder_Units->AddSpacer(5);
	TechTrees_ConnectedHolder_Units->Add(TechTrees_Units_Units.ItemList, 1, wxEXPAND);
	TechTrees_ConnectedHolder_Units->AddStretchSpacer(1);

	TechTrees_Units_ID_Holder->Add(TechTrees_Units_ID_Text, 0, wxEXPAND);
	TechTrees_Units_ID_Holder->Add(TechTrees_Units_ID, 0, wxEXPAND);
	TechTrees_Units_ID_Holder->Add(TechTrees_Units_ID_ComboBox, 0, wxEXPAND);
	TechTrees_Units_UpperBuilding_Holder->Add(TechTrees_Units_UpperBuilding_Text, 0, wxEXPAND);
	TechTrees_Units_UpperBuilding_Holder->Add(TechTrees_Units_UpperBuilding, 0, wxEXPAND);
	TechTrees_Units_UpperBuilding_Holder->Add(TechTrees_Units_UpperBuilding_ComboBox, 0, wxEXPAND);
	TechTrees_Units_LocationInAge_Holder->Add(TechTrees_Units_LocationInAge_Text, 0, wxEXPAND);
	TechTrees_Units_LocationInAge_Holder->Add(TechTrees_Units_LocationInAge, 0, wxEXPAND);
	TechTrees_Units_RequiredResearch_Holder->Add(TechTrees_Units_RequiredResearch_Text, 0, wxEXPAND);
	TechTrees_Units_RequiredResearch_Holder->Add(TechTrees_Units_RequiredResearch, 0, wxEXPAND);
	TechTrees_Units_RequiredResearch_Holder->Add(TechTrees_Units_RequiredResearch_ComboBox, 0, wxEXPAND);
	TechTrees_Units_LineMode_Holder->Add(TechTrees_Units_LineMode_Text, 0, wxEXPAND);
	TechTrees_Units_LineMode_Holder->Add(TechTrees_Units_LineMode, 0, wxEXPAND);
	TechTrees_Units_EnablingResearch_Holder->Add(TechTrees_Units_EnablingResearch_Text, 0, wxEXPAND);
	TechTrees_Units_EnablingResearch_Holder->Add(TechTrees_Units_EnablingResearch, 0, wxEXPAND);
	TechTrees_Units_EnablingResearch_Holder->Add(TechTrees_Units_EnablingResearch_ComboBox, 0, wxEXPAND);
	TechTrees_Units_Always2_Holder->Add(TechTrees_Units_Always2_Text, 0, wxEXPAND);
	TechTrees_Units_Always2_Holder->Add(TechTrees_Units_Always2, 0, wxEXPAND);
	TechTrees_Units_VerticalLine_Holder->Add(TechTrees_Units_VerticalLine_Text, 0, wxEXPAND);
	TechTrees_Units_VerticalLine_Holder->Add(TechTrees_Units_VerticalLine, 0, wxEXPAND);

	TechTrees_Data_Units1->Add(TechTrees_Units_ID_Holder, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_Always2_Holder, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_UpperBuilding_Holder, 1, wxEXPAND);
	TechTrees_Data_Units1->AddStretchSpacer(1);
	TechTrees_Data_Units1->AddStretchSpacer(1);
	TechTrees_Data_Units1->Add(TechTrees_Units_VerticalLine_Holder, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_LocationInAge_Holder, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_RequiredResearch_Holder, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_LineMode_Holder, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_EnablingResearch_Holder, 1, wxEXPAND);

	TechTrees_Data_Units->Add(TechTrees_Data_Units1, 0, wxEXPAND);
	TechTrees_Data_Units->AddSpacer(5);
	TechTrees_Data_Units->Add(TechTrees_ConnectedHolder_Units, 0, wxEXPAND);

	TechTrees_ConnectedHolder_Researches->Add(TechTrees_Researches_Buildings.ItemList, 1, wxEXPAND);
	TechTrees_ConnectedHolder_Researches->AddSpacer(5);
	TechTrees_ConnectedHolder_Researches->Add(TechTrees_Researches_Units.ItemList, 1, wxEXPAND);
	TechTrees_ConnectedHolder_Researches->AddSpacer(5);
	TechTrees_ConnectedHolder_Researches->Add(TechTrees_Researches_Researches.ItemList, 1, wxEXPAND);

	TechTrees_Researches_ID_Holder->Add(TechTrees_Researches_ID_Text, 0, wxEXPAND);
	TechTrees_Researches_ID_Holder->Add(TechTrees_Researches_ID, 0, wxEXPAND);
	TechTrees_Researches_ID_Holder->Add(TechTrees_Researches_ID_ComboBox, 0, wxEXPAND);
	TechTrees_Researches_UpperBuilding_Holder->Add(TechTrees_Researches_UpperBuilding_Text, 0, wxEXPAND);
	TechTrees_Researches_UpperBuilding_Holder->Add(TechTrees_Researches_UpperBuilding, 0, wxEXPAND);
	TechTrees_Researches_UpperBuilding_Holder->Add(TechTrees_Researches_UpperBuilding_ComboBox, 0, wxEXPAND);
	TechTrees_Researches_Always2_Holder->Add(TechTrees_Researches_Always2_Text, 0, wxEXPAND);
	TechTrees_Researches_Always2_Holder->Add(TechTrees_Researches_Always2, 0, wxEXPAND);
	TechTrees_Researches_VerticalLine_Holder->Add(TechTrees_Researches_VerticalLine_Text, 0, wxEXPAND);
	TechTrees_Researches_VerticalLine_Holder->Add(TechTrees_Researches_VerticalLine, 0, wxEXPAND);
	TechTrees_Researches_LocationInAge_Holder->Add(TechTrees_Researches_LocationInAge_Text, 0, wxEXPAND);
	TechTrees_Researches_LocationInAge_Holder->Add(TechTrees_Researches_LocationInAge, 0, wxEXPAND);
	TechTrees_Researches_LineMode_Holder->Add(TechTrees_Researches_LineMode_Text, 0, wxEXPAND);
	TechTrees_Researches_LineMode_Holder->Add(TechTrees_Researches_LineMode, 0, wxEXPAND);

	TechTrees_Data_Researches1->Add(TechTrees_Researches_ID_Holder, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_Always2_Holder, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_UpperBuilding_Holder, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_VerticalLine_Holder, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_LocationInAge_Holder, 1, wxEXPAND);
	TechTrees_Data_Researches1->Add(TechTrees_Researches_LineMode_Holder, 1, wxEXPAND);

	TechTrees_Data_Researches3->Add(TechTrees_Data_Researches1, 0, wxEXPAND);
	TechTrees_Data_Researches2->Add(TechTrees_Data_Researches3, 2, wxEXPAND);
	TechTrees_Data_Researches2->AddSpacer(5);
	TechTrees_Data_Researches2->Add(TechTrees_Researches_Items.Area, 1, wxEXPAND);

	TechTrees_Data_Researches->Add(TechTrees_ConnectedHolder_Researches, 0, wxEXPAND);
	TechTrees_Data_Researches->AddSpacer(5);
	TechTrees_Data_Researches->Add(TechTrees_Data_Researches2, 0, wxEXPAND);

	TechTrees_ScrollSpace1->AddSpacer(5);
	TechTrees_ScrollSpace1->Add(TechTrees_Data_Ages, 0, wxEXPAND);
	TechTrees_ScrollSpace2->AddSpacer(5);
	TechTrees_ScrollSpace2->Add(TechTrees_Data_Buildings, 0, wxEXPAND);
	TechTrees_ScrollSpace3->AddSpacer(5);
	TechTrees_ScrollSpace3->Add(TechTrees_Data_Units, 0, wxEXPAND);
	TechTrees_ScrollSpace4->AddSpacer(5);
	TechTrees_ScrollSpace4->Add(TechTrees_Data_Researches, 0, wxEXPAND);

	TechTrees_ScrollArea1->Add(TechTrees_ScrollSpace1, 1, wxEXPAND);
	TechTrees_ScrollArea1->AddSpacer(5);
	TechTrees_ScrollerAges->SetSizer(TechTrees_ScrollArea1);
	TechTrees_ScrollerAges->SetScrollRate(0, 15);
	TechTrees_TabAges->Add(TechTrees_MainList_Ages, 21, wxEXPAND);
	TechTrees_TabAges->AddSpacer(5);
	TechTrees_TabAges->Add(TechTrees_ScrollerAges, 65, wxEXPAND);

	TechTrees_ScrollArea2->Add(TechTrees_ScrollSpace2, 1, wxEXPAND);
	TechTrees_ScrollArea2->AddSpacer(5);
	TechTrees_ScrollerBuildings->SetSizer(TechTrees_ScrollArea2);
	TechTrees_ScrollerBuildings->SetScrollRate(0, 15);
	TechTrees_TabBuildings->Add(TechTrees_MainList_Buildings, 21, wxEXPAND);
	TechTrees_TabBuildings->AddSpacer(5);
	TechTrees_TabBuildings->Add(TechTrees_ScrollerBuildings, 65, wxEXPAND);

	TechTrees_ScrollArea3->Add(TechTrees_ScrollSpace3, 1, wxEXPAND);
	TechTrees_ScrollArea3->AddSpacer(5);
	TechTrees_ScrollerUnits->SetSizer(TechTrees_ScrollArea3);
	TechTrees_ScrollerUnits->SetScrollRate(0, 15);
	TechTrees_TabUnits->Add(TechTrees_MainList_Units, 21, wxEXPAND);
	TechTrees_TabUnits->AddSpacer(5);
	TechTrees_TabUnits->Add(TechTrees_ScrollerUnits, 65, wxEXPAND);

	TechTrees_ScrollArea4->Add(TechTrees_ScrollSpace4, 1, wxEXPAND);
	TechTrees_ScrollArea4->AddSpacer(5);
	TechTrees_ScrollerResearches->SetSizer(TechTrees_ScrollArea4);
	TechTrees_ScrollerResearches->SetScrollRate(0, 15);
	TechTrees_TabResearches->Add(TechTrees_MainList_Researches, 21, wxEXPAND);
	TechTrees_TabResearches->AddSpacer(5);
	TechTrees_TabResearches->Add(TechTrees_ScrollerResearches, 65, wxEXPAND);

	TechTrees_All->AddSpacer(5);
	TechTrees_All->Add(General_Variables2_Holder, 0, wxEXPAND);
	TechTrees_All->AddSpacer(5);
	TechTrees_All->Add(TabBar_TechTree, 1, wxEXPAND);
	TechTrees_All->AddSpacer(5);

	TechTrees_Main->AddSpacer(5);
	TechTrees_Main->Add(TechTrees_All, 1, wxEXPAND);
	TechTrees_Main->AddSpacer(5);

	/*for(short loop = 4; loop < 4; ++loop)
	{
		TechTrees_Unit_ComboBox[loop]->Show(false);
		TechTrees_Research_ComboBox[loop]->Show(false);
	}*/

	Tab_TechTrees->SetSizer(TechTrees_Main);
	Tab_TechTreeAges->SetSizer(TechTrees_TabAges);
	Tab_TechTreeBuildings->SetSizer(TechTrees_TabBuildings);
	Tab_TechTreeUnits->SetSizer(TechTrees_TabUnits);
	Tab_TechTreeResearches->SetSizer(TechTrees_TabResearches);

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

	Connect(TechTrees_Ages_Buildings.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingSearch));
	Connect(TechTrees_Ages_Units.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitSearch));
	Connect(TechTrees_Ages_Researches.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchSearch));
	Connect(TechTrees_Ages_Items.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgeItemSearch));
	Connect(TechTrees_Ages_UnknownItems.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgeUnknownItemSearch));
	Connect(TechTrees_Ages_Buildings.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingSearch));
	Connect(TechTrees_Ages_Units.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitSearch));
	Connect(TechTrees_Ages_Researches.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchSearch));
	Connect(TechTrees_Ages_Items.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgeItemSearch));
	Connect(TechTrees_Ages_UnknownItems.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgeUnknownItemSearch));
	Connect(TechTrees_Ages_Buildings.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingSelect));
	Connect(TechTrees_Ages_Units.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitSelect));
	Connect(TechTrees_Ages_Researches.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchSelect));
	Connect(TechTrees_Ages_Items.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgeItemSelect));
	Connect(TechTrees_Ages_UnknownItems.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgeUnknownItemSelect));
	Connect(TechTrees_Ages_Buildings.Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingAdd));
	Connect(TechTrees_Ages_Units.Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitAdd));
	Connect(TechTrees_Ages_Researches.Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchAdd));
	Connect(TechTrees_Ages_Buildings.Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingInsert));
	Connect(TechTrees_Ages_Units.Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitInsert));
	Connect(TechTrees_Ages_Researches.Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchInsert));
	Connect(TechTrees_Ages_Buildings.Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingDelete));
	Connect(TechTrees_Ages_Units.Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitDelete));
	Connect(TechTrees_Ages_Researches.Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchDelete));
	Connect(TechTrees_Ages_Buildings.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingCopy));
	Connect(TechTrees_Ages_Units.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitCopy));
	Connect(TechTrees_Ages_Researches.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchCopy));
	Connect(TechTrees_Ages_Items.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgeItemCopy));
	Connect(TechTrees_Ages_UnknownItems.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgeUnknownItemCopy));
	Connect(TechTrees_Ages_Buildings.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingPaste));
	Connect(TechTrees_Ages_Units.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitPaste));
	Connect(TechTrees_Ages_Researches.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchPaste));
	Connect(TechTrees_Ages_Items.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgeItemPaste));
	Connect(TechTrees_Ages_UnknownItems.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgeUnknownItemPaste));
	Connect(TechTrees_Ages_Buildings.PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingPasteInsert));
	Connect(TechTrees_Ages_Units.PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitPasteInsert));
	Connect(TechTrees_Ages_Researches.PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchPasteInsert));
	Connect(TechTrees_Ages_Buildings.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingCopyToAges));
	Connect(TechTrees_Ages_Units.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitCopyToAges));
	Connect(TechTrees_Ages_Researches.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchCopyToAges));
	Connect(TechTrees_Ages_Items.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgeItemCopyToAges));
	Connect(TechTrees_Ages_UnknownItems.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgeUnknownItemCopyToAges));
	Connect(TechTrees_Buildings_Buildings.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingSearch));
	Connect(TechTrees_Buildings_Units.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitSearch));
	Connect(TechTrees_Buildings_Researches.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchSearch));
	Connect(TechTrees_Buildings_Items.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingItemSearch));
	Connect(TechTrees_Buildings_Buildings.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingSearch));
	Connect(TechTrees_Buildings_Units.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitSearch));
	Connect(TechTrees_Buildings_Researches.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchSearch));
	Connect(TechTrees_Buildings_Items.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingItemSearch));
	Connect(TechTrees_Buildings_Buildings.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingSelect));
	Connect(TechTrees_Buildings_Units.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitSelect));
	Connect(TechTrees_Buildings_Researches.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchSelect));
	Connect(TechTrees_Buildings_Items.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingItemSelect));
	Connect(TechTrees_Buildings_Buildings.Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingAdd));
	Connect(TechTrees_Buildings_Units.Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitAdd));
	Connect(TechTrees_Buildings_Researches.Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchAdd));
	Connect(TechTrees_Buildings_Buildings.Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingInsert));
	Connect(TechTrees_Buildings_Units.Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitInsert));
	Connect(TechTrees_Buildings_Researches.Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchInsert));
	Connect(TechTrees_Buildings_Buildings.Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingDelete));
	Connect(TechTrees_Buildings_Units.Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitDelete));
	Connect(TechTrees_Buildings_Researches.Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchDelete));
	Connect(TechTrees_Buildings_Buildings.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingCopy));
	Connect(TechTrees_Buildings_Units.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitCopy));
	Connect(TechTrees_Buildings_Researches.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchCopy));
	Connect(TechTrees_Buildings_Items.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingItemCopy));
	Connect(TechTrees_Buildings_Buildings.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingPaste));
	Connect(TechTrees_Buildings_Units.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitPaste));
	Connect(TechTrees_Buildings_Researches.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchPaste));
	Connect(TechTrees_Buildings_Items.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingItemPaste));
	Connect(TechTrees_Buildings_Buildings.PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingPasteInsert));
	Connect(TechTrees_Buildings_Units.PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitPasteInsert));
	Connect(TechTrees_Buildings_Researches.PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchPasteInsert));
	Connect(TechTrees_Buildings_Buildings.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingCopyToBuildings));
	Connect(TechTrees_Buildings_Units.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitCopyToBuildings));
	Connect(TechTrees_Buildings_Researches.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchCopyToBuildings));
	Connect(TechTrees_Buildings_Items.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTBuildingItemCopyToBuildings));
	Connect(TechTrees_Units_Units.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitSearch));
	Connect(TechTrees_Units_Items.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTUnitItemSearch));
	Connect(TechTrees_Units_Units.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitSearch));
	Connect(TechTrees_Units_Items.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTUnitItemSearch));
	Connect(TechTrees_Units_Units.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitSelect));
	Connect(TechTrees_Units_Items.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTUnitItemSelect));
	Connect(TechTrees_Units_Units.Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitAdd));
	Connect(TechTrees_Units_Units.Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitInsert));
	Connect(TechTrees_Units_Units.Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitDelete));
	Connect(TechTrees_Units_Units.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitCopy));
	Connect(TechTrees_Units_Items.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitItemCopy));
	Connect(TechTrees_Units_Units.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitPaste));
	Connect(TechTrees_Units_Items.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitItemPaste));
	Connect(TechTrees_Units_Units.PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitPasteInsert));
	Connect(TechTrees_Units_Units.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitCopyToUnits));
	Connect(TechTrees_Units_Items.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitItemCopyToUnits));
	Connect(TechTrees_Researches_Buildings.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingSearch));
	Connect(TechTrees_Researches_Units.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitSearch));
	Connect(TechTrees_Researches_Researches.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchSearch));
	Connect(TechTrees_Researches_Items.Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchItemSearch));
	Connect(TechTrees_Researches_Buildings.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingSearch));
	Connect(TechTrees_Researches_Units.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitSearch));
	Connect(TechTrees_Researches_Researches.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchSearch));
	Connect(TechTrees_Researches_Items.SearchRecursive->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchItemSearch));
	Connect(TechTrees_Researches_Buildings.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingSelect));
	Connect(TechTrees_Researches_Units.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitSelect));
	Connect(TechTrees_Researches_Researches.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchSelect));
	Connect(TechTrees_Researches_Items.List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchItemSelect));
	Connect(TechTrees_Researches_Buildings.Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingAdd));
	Connect(TechTrees_Researches_Units.Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitAdd));
	Connect(TechTrees_Researches_Researches.Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchAdd));
	Connect(TechTrees_Researches_Buildings.Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingInsert));
	Connect(TechTrees_Researches_Units.Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitInsert));
	Connect(TechTrees_Researches_Researches.Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchInsert));
	Connect(TechTrees_Researches_Buildings.Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingDelete));
	Connect(TechTrees_Researches_Units.Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitDelete));
	Connect(TechTrees_Researches_Researches.Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchDelete));
	Connect(TechTrees_Researches_Buildings.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingCopy));
	Connect(TechTrees_Researches_Units.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitCopy));
	Connect(TechTrees_Researches_Researches.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchCopy));
	Connect(TechTrees_Researches_Items.Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchItemCopy));
	Connect(TechTrees_Researches_Buildings.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingPaste));
	Connect(TechTrees_Researches_Units.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitPaste));
	Connect(TechTrees_Researches_Researches.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchPaste));
	Connect(TechTrees_Researches_Items.Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchItemPaste));
	Connect(TechTrees_Researches_Buildings.PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingPasteInsert));
	Connect(TechTrees_Researches_Units.PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitPasteInsert));
	Connect(TechTrees_Researches_Researches.PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchPasteInsert));
	Connect(TechTrees_Researches_Buildings.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingCopyToResearches));
	Connect(TechTrees_Researches_Units.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitCopyToResearches));
	Connect(TechTrees_Researches_Researches.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchCopyToResearches));
	Connect(TechTrees_Researches_Items.CopyAllToSelected->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTResearchItemCopyToResearches));

	TechTrees_Ages_ID->Connect(TechTrees_Ages_ID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Ages_Buildings.Item->Connect(TechTrees_Ages_Buildings.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Ages_Units.Item->Connect(TechTrees_Ages_Units.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Ages_Researches.Item->Connect(TechTrees_Ages_Researches.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Ages_Items.Item->Connect(TechTrees_Ages_Items.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Ages_Items.Mode->Connect(TechTrees_Ages_Items.Mode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Ages_UnknownItems.Unknown1->Connect(TechTrees_Ages_UnknownItems.Unknown1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Ages_UnknownItems.Unknown2->Connect(TechTrees_Ages_UnknownItems.Unknown2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Ages_Buildings.ItemCombo->Connect(TechTrees_Ages_Buildings.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Ages_Units.ItemCombo->Connect(TechTrees_Ages_Units.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Ages_Researches.ItemCombo->Connect(TechTrees_Ages_Researches.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Ages_Items.ItemCombo->Connect(TechTrees_Ages_Items.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Ages_Items.ModeCombo->Connect(TechTrees_Ages_Items.ModeCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Buildings_ID->Connect(TechTrees_Buildings_ID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_Buildings.Item->Connect(TechTrees_Buildings_Buildings.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_Units.Item->Connect(TechTrees_Buildings_Units.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_Researches.Item->Connect(TechTrees_Buildings_Researches.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_Items.Item->Connect(TechTrees_Buildings_Items.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_Items.Mode->Connect(TechTrees_Buildings_Items.Mode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Units_ID->Connect(TechTrees_Units_ID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Units_Units.Item->Connect(TechTrees_Units_Units.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Units_Items.Item->Connect(TechTrees_Units_Items.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Units_Items.Mode->Connect(TechTrees_Units_Items.Mode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Researches_ID->Connect(TechTrees_Researches_ID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Researches_Buildings.Item->Connect(TechTrees_Researches_Buildings.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Researches_Units.Item->Connect(TechTrees_Researches_Units.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Researches_Researches.Item->Connect(TechTrees_Researches_Researches.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Researches_Items.Item->Connect(TechTrees_Researches_Items.Item->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Researches_Items.Mode->Connect(TechTrees_Researches_Items.Mode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TechTrees), NULL, this);
	TechTrees_Buildings_ID_ComboBox->Connect(TechTrees_Buildings_ID_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Buildings_Buildings.ItemCombo->Connect(TechTrees_Buildings_Buildings.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Buildings_Units.ItemCombo->Connect(TechTrees_Buildings_Units.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Buildings_Researches.ItemCombo->Connect(TechTrees_Buildings_Researches.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Buildings_Items.ItemCombo->Connect(TechTrees_Buildings_Items.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Buildings_Items.ModeCombo->Connect(TechTrees_Buildings_Items.ModeCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Units_ID_ComboBox->Connect(TechTrees_Units_ID_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Units_Units.ItemCombo->Connect(TechTrees_Units_Units.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Units_Items.ItemCombo->Connect(TechTrees_Units_Items.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Units_Items.ModeCombo->Connect(TechTrees_Units_Items.ModeCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Researches_ID_ComboBox->Connect(TechTrees_Researches_ID_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Researches_Buildings.ItemCombo->Connect(TechTrees_Researches_Buildings.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Researches_Units.ItemCombo->Connect(TechTrees_Researches_Units.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Researches_Researches.ItemCombo->Connect(TechTrees_Researches_Researches.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Researches_Items.ItemCombo->Connect(TechTrees_Researches_Items.ItemCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
	TechTrees_Researches_Items.ModeCombo->Connect(TechTrees_Researches_Items.ModeCombo->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_TechTrees), NULL, this);
}

void AGE_Frame::OnKillFocus_TechTrees(wxFocusEvent &Event)
{
	if(((AGETextCtrl*)Event.GetEventObject())->SaveEdits() != 0) return;
	if(Event.GetId() == TechTrees_Ages_ID->GetId())
	{
		ListTTAges();
	}
	else if(Event.GetId() == TechTrees_Ages_Buildings.Item->GetId())
	{
		ListTTAgeBuildings();
	}
	else if(Event.GetId() == TechTrees_Ages_Units.Item->GetId())
	{
		ListTTAgeUnits();
	}
	else if(Event.GetId() == TechTrees_Ages_Researches.Item->GetId())
	{
		ListTTAgeResearches();
	}
	else if(Event.GetId() == TechTrees_Ages_Items.Item->GetId() || Event.GetId() == TechTrees_Ages_Items.Mode->GetId())
	{
		ListTTAgeItems();
	}
	else if(Event.GetId() == TechTrees_Ages_UnknownItems.Unknown1->GetId() || Event.GetId() == TechTrees_Ages_UnknownItems.Unknown2->GetId())
	{
		ListTTAgeUnknownItems();
	}
	else if(Event.GetId() == TechTrees_Buildings_ID->GetId())
	{
		ListTTBuildings();
	}
	else if(Event.GetId() == TechTrees_Buildings_Buildings.Item->GetId())
	{
		ListTTBuildingBuildings();
	}
	else if(Event.GetId() == TechTrees_Buildings_Units.Item->GetId())
	{
		ListTTBuildingUnits();
	}
	else if(Event.GetId() == TechTrees_Buildings_Researches.Item->GetId())
	{
		ListTTBuildingResearches();
	}
	else if(Event.GetId() == TechTrees_Buildings_Items.Item->GetId() || Event.GetId() == TechTrees_Buildings_Items.Mode->GetId())
	{
		ListTTBuildingItems();
	}
	else if(Event.GetId() == TechTrees_Units_ID->GetId())
	{
		ListTTUnits();
	}
	else if(Event.GetId() == TechTrees_Units_Units.Item->GetId())
	{
		ListTTUnitUnits();
	}
	else if(Event.GetId() == TechTrees_Units_Items.Item->GetId() || Event.GetId() == TechTrees_Units_Items.Mode->GetId())
	{
		ListTTUnitItems();
	}
	else if(Event.GetId() == TechTrees_Researches_ID->GetId())
	{
		ListTTResearches();
	}
	else if(Event.GetId() == TechTrees_Researches_Buildings.Item->GetId())
	{
		ListTTResearchBuildings();
	}
	else if(Event.GetId() == TechTrees_Researches_Units.Item->GetId())
	{
		ListTTResearchUnits();
	}
	else if(Event.GetId() == TechTrees_Researches_Researches.Item->GetId())
	{
		ListTTResearchResearches();
	}
	else if(Event.GetId() == TechTrees_Researches_Items.Item->GetId() || Event.GetId() == TechTrees_Researches_Items.Mode->GetId())
	{
		ListTTResearchItems();
	}
	else if(false)
	{
		wxCommandEvent E;
		OnTTUnitSelect(E);
	}
	else if(false)
	{
		wxCommandEvent E;
		OnTTBuildingSelect(E);
	}
	Event.Skip();
}

void AGE_Frame::OnUpdateCombo_TechTrees(wxCommandEvent &Event)
{
	if(Event.GetId() == TechTrees_Ages_Items.ModeCombo->GetId())
	{
		for(auto &pointer: TechTrees_Ages_Items.Mode->container)
		{
			*(int32_t*)pointer = TechTrees_Ages_Items.ModeCombo->GetSelection();
		}
		ListTTAgeItems();
		return;
	}
	if(Event.GetId() == TechTrees_Buildings_Items.ModeCombo->GetId())
	{
		for(auto &pointer: TechTrees_Buildings_Items.Mode->container)
		{
			*(int32_t*)pointer = TechTrees_Buildings_Items.ModeCombo->GetSelection();
		}
		ListTTBuildingItems();
		return;
	}
	if(Event.GetId() == TechTrees_Units_Items.ModeCombo->GetId())
	{
		for(auto &pointer: TechTrees_Units_Items.Mode->container)
		{
			*(int32_t*)pointer = TechTrees_Units_Items.ModeCombo->GetSelection();
		}
		ListTTUnitItems();
		return;
	}
	if(Event.GetId() == TechTrees_Researches_Items.ModeCombo->GetId())
	{
		for(auto &pointer: TechTrees_Researches_Items.Mode->container)
		{
			*(int32_t*)pointer = TechTrees_Researches_Items.ModeCombo->GetSelection();
		}
		ListTTResearchItems();
		return;
	}
	((AGEComboBox*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == TechTrees_Ages_Buildings.ItemCombo->GetId())
	{
		ListTTAgeBuildings();
	}
	else if(Event.GetId() == TechTrees_Ages_Units.ItemCombo->GetId())
	{
		ListTTAgeUnits();
	}
	else if(Event.GetId() == TechTrees_Ages_Researches.ItemCombo->GetId())
	{
		ListTTAgeResearches();
	}
	else if(Event.GetId() == TechTrees_Ages_Items.ItemCombo->GetId())
	{
		ListTTAgeItems();
	}
	else if(Event.GetId() == TechTrees_Buildings_ID_ComboBox->GetId())
	{
		ListTTBuildings();
	}
	else if(Event.GetId() == TechTrees_Buildings_Buildings.ItemCombo->GetId())
	{
		ListTTBuildingBuildings();
	}
	else if(Event.GetId() == TechTrees_Buildings_Units.ItemCombo->GetId())
	{
		ListTTBuildingUnits();
	}
	else if(Event.GetId() == TechTrees_Buildings_Researches.ItemCombo->GetId())
	{
		ListTTBuildingResearches();
	}
	else if(Event.GetId() == TechTrees_Buildings_Items.ItemCombo->GetId())
	{
		ListTTBuildingItems();
	}
	else if(Event.GetId() == TechTrees_Units_ID_ComboBox->GetId())
	{
		ListTTUnits();
	}
	else if(Event.GetId() == TechTrees_Units_Units.ItemCombo->GetId())
	{
		ListTTUnitUnits();
	}
	else if(Event.GetId() == TechTrees_Units_Items.ItemCombo->GetId())
	{
		ListTTUnitItems();
	}
	else if(Event.GetId() == TechTrees_Researches_ID_ComboBox->GetId())
	{
		ListTTResearches();
	}
	else if(Event.GetId() == TechTrees_Researches_Buildings.ItemCombo->GetId())
	{
		ListTTResearchBuildings();
	}
	else if(Event.GetId() == TechTrees_Researches_Units.ItemCombo->GetId())
	{
		ListTTResearchUnits();
	}
	else if(Event.GetId() == TechTrees_Researches_Researches.ItemCombo->GetId())
	{
		ListTTResearchResearches();
	}
	else if(Event.GetId() == TechTrees_Researches_Items.ItemCombo->GetId())
	{
		ListTTResearchItems();
	}
}
