#include "../AGE_Frame.h"

string AGE_Frame::GetTTAgesName(int index)
{
	return "Age "+lexical_cast<string>(dataset->TechTree.TechTreeAges[index].ID);
}

void AGE_Frame::OnTTAgesSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTAges();
}

void AGE_Frame::ListTTAges()
{
	InitTTAges();
	wxTimerEvent E;
	OnTTAgesTimer(E);
}

void AGE_Frame::InitTTAges()
{
	searchText = TechTrees_MainList_Ages_Search->GetValue().MakeLower();
	excludeText = TechTrees_MainList_Ages_Search_R->GetValue().MakeLower();

	TechTrees_MainList_Ages_ListV->names.clear();
	TechTrees_MainList_Ages_ListV->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.TechTreeAges.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTTAgesName(loop);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_MainList_Ages_ListV->names.Add(Name);
			TechTrees_MainList_Ages_ListV->indexes.push_back(loop);
		}
	}

	virtualListing(TechTrees_MainList_Ages_ListV);
}

void AGE_Frame::OnTTAgesSelect(wxCommandEvent &event)
{
    if(!ttAgeTimer.IsRunning())
        ttAgeTimer.Start(150);
}

void AGE_Frame::OnTTAgesTimer(wxTimerEvent &event)
{
	ttAgeTimer.Stop();
	auto selections = TechTrees_MainList_Ages_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, TechTrees_MainList_Ages_ListV, TTAgeIDs);

	for(auto &box: uiGroupTTAge) box->clear();
	TechTrees_Ages_UnknownItems.UsedItems->clear();
	TechTrees_Ages_UnknownItems.Unknown->clear();
	TechTrees_Ages_Items.UsedItems->clear();

	genie::TechTreeAge * AgePointer;
	for(auto sel = selections; sel--> 0;)
	{
		AgePointer = &dataset->TechTree.TechTreeAges[TTAgeIDs[sel]];

		TechTrees_Ages_ID->prepend(&AgePointer->ID);
		TechTrees_Ages_Unknown2->prepend(&AgePointer->Unknown2);
		TechTrees_Ages_UnknownItems.UsedItems->prepend(&AgePointer->SlotsUsed);
		TechTrees_Ages_UnknownItems.Unknown->prepend(&AgePointer->Unknown6);
		TechTrees_Ages_LineMode->prepend(&AgePointer->LineMode);
		TechTrees_Ages_Items.UsedItems->prepend(&AgePointer->Common.SlotsUsed);
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected age: "+lexical_cast<string>(TTAgeIDs[0]), 0);

	for(auto &box: uiGroupTTAge) box->update();
	TechTrees_Ages_UnknownItems.UsedItems->update();
	TechTrees_Ages_UnknownItems.Unknown->update();
	TechTrees_Ages_Items.UsedItems->update();

	ListTTAgeBuildings();
	ListTTAgeUnits();
	ListTTAgeResearches();
	ListTTAgeItems();
	ListTTAgeUnknownItems();
}

void AGE_Frame::OnTTAgesAdd(wxCommandEvent &event)
{
	if(NULL == dataset) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->TechTree.TechTreeAges);
	ListTTAges();
}

void AGE_Frame::OnTTAgesInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Ages_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->TechTree.TechTreeAges, TTAgeIDs[0]);
	ListTTAges();
}

void AGE_Frame::OnTTAgesDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Ages_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.TechTreeAges, TTAgeIDs);
	ListTTAges();
}

void AGE_Frame::OnTTAgesCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Ages_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.TechTreeAges, TTAgeIDs, copies.TTAge);
	TechTrees_MainList_Ages_ListV->SetFocus();
}

void AGE_Frame::OnTTAgesPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Ages_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTAgeIDs.size(), copies.TTAge.size()))
		{
			PasteToList(dataset->TechTree.TechTreeAges, TTAgeIDs, copies.TTAge);
		}
	}
	else
	{
		PasteToList(dataset->TechTree.TechTreeAges, TTAgeIDs[0], copies.TTAge);
	}
	ListTTAges();
}

void AGE_Frame::OnTTAgesPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Ages_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->TechTree.TechTreeAges, TTAgeIDs[0], copies.TTAge);
	ListTTAges();
}

string AGE_Frame::GetBuildingName(int Building)
{
	string Name = lexical_cast<string>(Building)+" ";
	if(dataset->Civs[0].Units.size() <= Building) return Name + "Nonexistent Building";
	if(!LangDLLstring(dataset->Civs[0].Units[Building].LanguageDLLName, 2).empty())
	{
		return Name + LangDLLstring(dataset->Civs[0].Units[Building].LanguageDLLName, 64);
	}
	if(!dataset->Civs[0].Units[Building].Name.empty())
	{
		return Name + dataset->Civs[0].Units[Building].Name;
	}
	return Name + "New Building";
}

void AGE_Frame::OnTTAgesBuildingSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTAgeBuildings();
}

void AGE_Frame::ListTTAgeBuildings()
{
	searchText = TechTrees_Ages_Buildings.Search->GetValue().MakeLower();
	excludeText = TechTrees_Ages_Buildings.SearchRecursive->GetValue().MakeLower();

	TechTrees_Ages_Buildings.List->names.clear();
	TechTrees_Ages_Buildings.List->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetBuildingName(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_Ages_Buildings.List->names.Add(Name);
			TechTrees_Ages_Buildings.List->indexes.push_back(loop);
		}
	}
	virtualListing(TechTrees_Ages_Buildings.List);

	wxTimerEvent E;
	OnTTAgesBuildingTimer(E);
}

void AGE_Frame::OnTTAgesBuildingSelect(wxCommandEvent &event)
{
    if(!ttAgeBuildingTimer.IsRunning())
        ttAgeBuildingTimer.Start(150);
}

void AGE_Frame::OnTTAgesBuildingTimer(wxTimerEvent &event)
{
    ttAgeBuildingTimer.Stop();
	auto selections = TechTrees_Ages_Buildings.List->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    TechTrees_Ages_Buildings.Item->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, TechTrees_Ages_Buildings.List, TTAgeBuildIDs);
		int32_t * BuildingPointer;
		for(auto loop = selections; loop--> 0;)
		{
			BuildingPointer = &dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings[TTAgeBuildIDs[loop]];
			TechTrees_Ages_Buildings.Item->prepend(BuildingPointer);
		}
	}
    TechTrees_Ages_Buildings.Item->update();
}

void AGE_Frame::OnTTAgesBuildingAdd(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Ages_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings);
	ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs[0]);
	ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs);
	ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs, copies.TTAgeBuild);
	TechTrees_Ages_Buildings.List->SetFocus();
}

void AGE_Frame::OnTTAgesBuildingPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTAgeBuildIDs.size(), copies.TTAgeBuild.size()))
		{
			PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs, copies.TTAgeBuild);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs[0], copies.TTAgeBuild);
	}
	ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings, TTAgeBuildIDs[0], copies.TTAgeBuild);
	ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingCopyToAges(wxCommandEvent &event)
{
	for(short loop=1; loop < TTAgeIDs.size(); ++loop)
	{
		dataset->TechTree.TechTreeAges[TTAgeIDs[loop]].Buildings = dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Buildings;
	}
}

void AGE_Frame::OnTTAgesUnitSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTAgeUnits();
}

void AGE_Frame::ListTTAgeUnits()
{
	searchText = TechTrees_Ages_Units.Search->GetValue().MakeLower();
	excludeText = TechTrees_Ages_Units.SearchRecursive->GetValue().MakeLower();

	TechTrees_Ages_Units.List->names.clear();
	TechTrees_Ages_Units.List->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Units.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Units[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_Ages_Units.List->names.Add(Name);
			TechTrees_Ages_Units.List->indexes.push_back(loop);
		}
	}
	virtualListing(TechTrees_Ages_Units.List);

	wxTimerEvent E;
	OnTTAgesUnitTimer(E);
}

void AGE_Frame::OnTTAgesUnitSelect(wxCommandEvent &event)
{
    if(!ttAgeUnitTimer.IsRunning())
        ttAgeUnitTimer.Start(150);
}

void AGE_Frame::OnTTAgesUnitTimer(wxTimerEvent &event)
{
    ttAgeUnitTimer.Stop();
	auto selections = TechTrees_Ages_Units.List->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    TechTrees_Ages_Units.Item->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, TechTrees_Ages_Units.List, TTAgeUnitIDs);
		int32_t * UnitPointer;
		for(auto loop = selections; loop--> 0;)
		{
			UnitPointer = &dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Units[TTAgeUnitIDs[loop]];
			TechTrees_Ages_Units.Item->prepend(UnitPointer);
		}
	}
    TechTrees_Ages_Units.Item->update();
}

void AGE_Frame::OnTTAgesUnitAdd(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Ages_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Units);
	ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs[0]);
	ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs);
	ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs, copies.TTAgeUnit);
	TechTrees_Ages_Units.List->SetFocus();
}

void AGE_Frame::OnTTAgesUnitPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTAgeUnitIDs.size(), copies.TTAgeUnit.size()))
		{
			PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs, copies.TTAgeUnit);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs[0], copies.TTAgeUnit);
	}
	ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Units, TTAgeUnitIDs[0], copies.TTAgeUnit);
	ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitCopyToAges(wxCommandEvent &event)
{
	for(short loop=1; loop < TTAgeIDs.size(); ++loop)
	{
		dataset->TechTree.TechTreeAges[TTAgeIDs[loop]].Units = dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Units;
	}
}

string AGE_Frame::GetSimpleResearchName(int Research)
{
	string Name = lexical_cast<string>(Research)+" ";
	if(dataset->Researchs.size() <= Research) return Name + "Nonexistent Research";
	if(!LangDLLstring(dataset->Researchs[Research].LanguageDLLName, 2).empty())
	{
		return Name + LangDLLstring(dataset->Researchs[Research].LanguageDLLName, 64);
	}
	if(!dataset->Researchs[Research].Name.empty())
	{
		return Name + dataset->Researchs[Research].Name;
	}
	return Name + "New Research";
}

void AGE_Frame::OnTTAgesResearchSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTAgeResearches();
}

void AGE_Frame::ListTTAgeResearches()
{
	searchText = TechTrees_Ages_Researches.Search->GetValue().MakeLower();
	excludeText = TechTrees_Ages_Researches.SearchRecursive->GetValue().MakeLower();

	TechTrees_Ages_Researches.List->names.clear();
	TechTrees_Ages_Researches.List->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Researches.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetSimpleResearchName(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Researches[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_Ages_Researches.List->names.Add(Name);
			TechTrees_Ages_Researches.List->indexes.push_back(loop);
		}
	}
	virtualListing(TechTrees_Ages_Researches.List);

	wxTimerEvent E;
	OnTTAgesResearchTimer(E);
}

void AGE_Frame::OnTTAgesResearchSelect(wxCommandEvent &event)
{
    if(!ttAgeResearchTimer.IsRunning())
        ttAgeResearchTimer.Start(150);
}

void AGE_Frame::OnTTAgesResearchTimer(wxTimerEvent &event)
{
    ttAgeResearchTimer.Stop();
	auto selections = TechTrees_Ages_Researches.List->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    TechTrees_Ages_Researches.Item->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, TechTrees_Ages_Researches.List, TTAgeResIDs);
		int32_t * ResearchPointer;
		for(auto loop = selections; loop--> 0;)
		{
			ResearchPointer = &dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Researches[TTAgeResIDs[loop]];
			TechTrees_Ages_Researches.Item->prepend(ResearchPointer);
		}
	}
    TechTrees_Ages_Researches.Item->update();
}

void AGE_Frame::OnTTAgesResearchAdd(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Ages_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Researches);
	ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs[0]);
	ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs);
	ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs, copies.TTAgeRes);
	TechTrees_Ages_Researches.List->SetFocus();
}

void AGE_Frame::OnTTAgesResearchPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTAgeResIDs.size(), copies.TTAgeRes.size()))
		{
			PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs, copies.TTAgeRes);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs[0], copies.TTAgeRes);
	}
	ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Researches, TTAgeResIDs[0], copies.TTAgeRes);
	ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchCopyToAges(wxCommandEvent &event)
{
	for(short loop=1; loop < TTAgeIDs.size(); ++loop)
	{
		dataset->TechTree.TechTreeAges[TTAgeIDs[loop]].Researches = dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Researches;
	}
}

void AGE_Frame::OnTTAgeItemSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTAgeItems();
}

void AGE_Frame::ListTTAgeItems()
{
	ListTTCommonItems(TechTrees_Ages_Items, &dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Common);
	wxTimerEvent E;
	OnTTAgeItemTimer(E);
}

void AGE_Frame::SelectTTCommonItems(AGE_AreaTT84 &area, genie::techtree::Common* dataPointer)
{
    wxBusyCursor WaitCursor;
	auto selections = area.List->GetSelectedItemCount();
    area.Item->clear();
    area.Mode->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, area.List, TTItemIDs);

		int32_t * ItemPointer;
		for(auto loop = selections; loop--> 0;)
		{
			ItemPointer = &dataPointer->Mode[TTItemIDs[loop]];
			area.Mode->prepend(ItemPointer);
			area.Item->prepend(&dataPointer->UnitResearch[TTItemIDs[loop]]);
		}

		area.ModeCombo->SetSelection(*ItemPointer);
		area.FillItemCombo(dataPointer->UnitResearch[TTItemIDs[0]] + 1);
	}
    area.Item->update();
    area.Mode->update();
    area.ModeCombo->Enable(selections);
}

void AGE_Frame::OnTTAgeItemSelect(wxCommandEvent &event)
{
    if(!ttAgeItemTimer.IsRunning())
        ttAgeItemTimer.Start(150);
}

void AGE_Frame::OnTTAgeItemTimer(wxTimerEvent &event)
{
	ttAgeItemTimer.Stop();
	SelectTTCommonItems(TechTrees_Ages_Items, &dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Common);
}

void AGE_Frame::OnTTAgeItemCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Items.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Common.UnitResearch, TTItemIDs, copies.TTItem);
	CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Common.Mode, TTItemIDs, copies.TTMode);
	TechTrees_Ages_Items.List->SetFocus();
}

void AGE_Frame::OnTTAgeItemPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_Items.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTItemIDs.size(), copies.TTItem.size()))
		{
			PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Common.UnitResearch, TTItemIDs, copies.TTItem);
			PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Common.Mode, TTItemIDs, copies.TTMode);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Common.UnitResearch, TTItemIDs[0], copies.TTItem);
		PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Common.Mode, TTItemIDs[0], copies.TTMode);
	}
	ListTTAgeItems();
}

void AGE_Frame::OnTTAgeItemCopyToAges(wxCommandEvent &event)
{
	for(short loop=1; loop < TTAgeIDs.size(); ++loop)
	{
		dataset->TechTree.TechTreeAges[TTAgeIDs[loop]].Common = dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Common;
	}
}

void AGE_Frame::OnTTAgeUnknownItemSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTAgeUnknownItems();
}

void AGE_Frame::ListTTAgeUnknownItems()
{
	searchText = TechTrees_Ages_UnknownItems.Search->GetValue().MakeLower();
	excludeText = TechTrees_Ages_UnknownItems.SearchRecursive->GetValue().MakeLower();

	TechTrees_Ages_UnknownItems.List->names.clear();
	TechTrees_Ages_UnknownItems.List->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.TechTreeAges[TTAgeIDs[0]].getU4Size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>((short)dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown4[loop]);
		Name += " - "+lexical_cast<string>((short)dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown5[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_Ages_UnknownItems.List->names.Add(Name);
			TechTrees_Ages_UnknownItems.List->indexes.push_back(loop);
		}
	}
	virtualListing(TechTrees_Ages_UnknownItems.List);

	wxTimerEvent E;
	OnTTAgeUnknownItemTimer(E);
}

void AGE_Frame::OnTTAgeUnknownItemSelect(wxCommandEvent &event)
{
    if(!ttAgeUnknownTimer.IsRunning())
        ttAgeUnknownTimer.Start(150);
}

void AGE_Frame::OnTTAgeUnknownItemTimer(wxTimerEvent &event)
{
    ttAgeUnknownTimer.Stop();
	auto selections = TechTrees_Ages_UnknownItems.List->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    TechTrees_Ages_UnknownItems.Unknown1->clear();
    TechTrees_Ages_UnknownItems.Unknown2->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, TechTrees_Ages_UnknownItems.List, TTUnknownItemIDs);
		int8_t * unknown4Pointer;
		genie::TechTreeAge* agePointer = &dataset->TechTree.TechTreeAges[TTAgeIDs[0]];
		for(auto loop = selections; loop--> 0;)
		{
			unknown4Pointer = &agePointer->Unknown4[TTUnknownItemIDs[loop]];
			TechTrees_Ages_UnknownItems.Unknown1->prepend(unknown4Pointer);
			TechTrees_Ages_UnknownItems.Unknown2->prepend(&agePointer->Unknown5[TTUnknownItemIDs[loop]]);
		}
	}
    TechTrees_Ages_UnknownItems.Unknown1->update();
    TechTrees_Ages_UnknownItems.Unknown2->update();
}

void AGE_Frame::OnTTAgeUnknownItemCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_UnknownItems.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown4, TTUnknownItemIDs, copies.TTUnknown4);
	CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown5, TTUnknownItemIDs, copies.TTUnknown5);
	TechTrees_Ages_UnknownItems.List->SetFocus();
}

void AGE_Frame::OnTTAgeUnknownItemPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Ages_UnknownItems.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTUnknownItemIDs.size(), copies.TTUnknown4.size()))
		{
			PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown4, TTUnknownItemIDs, copies.TTUnknown4);
			PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown5, TTUnknownItemIDs, copies.TTUnknown5);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown4, TTUnknownItemIDs[0], copies.TTUnknown4);
		PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown5, TTUnknownItemIDs[0], copies.TTUnknown5);
	}
	ListTTAgeUnknownItems();
}

void AGE_Frame::OnTTAgeUnknownItemCopyToAges(wxCommandEvent &event)
{
	for(short loop=1; loop < TTAgeIDs.size(); ++loop)
	{
		dataset->TechTree.TechTreeAges[TTAgeIDs[loop]].Unknown4 = dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown4;
		dataset->TechTree.TechTreeAges[TTAgeIDs[loop]].Unknown5 = dataset->TechTree.TechTreeAges[TTAgeIDs[0]].Unknown5;
	}
}

string AGE_Frame::GetTTBuildingName(int index)
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
				Name += "S "+lexical_cast<string>((short)dataset->TechTree.BuildingConnections[index].Unknown1);
				break;
			case 2: // Required Items
				Name += "I "+lexical_cast<string>(dataset->TechTree.BuildingConnections[index].Common.SlotsUsed);
				break;
			case 3: // Age
				Name += "A "+lexical_cast<string>(dataset->TechTree.BuildingConnections[index].Common.UnitResearch[0]);
				break;
			case 4: // Location in Age
				Name += "LA "+lexical_cast<string>((short)dataset->TechTree.BuildingConnections[index].LocationInAge);
				break;
			case 5: // Units & Techs by Age
				Name += "UT";
				for(short age = 0; age < 5; ++age)
				Name += " "+lexical_cast<string>((short)dataset->TechTree.BuildingConnections[index].UnitsTechsTotal[age]);
				break;
			case 6: // Units & Techs @ 1st by Age
				Name += "UT1";
				for(short age = 0; age < 5; ++age)
				Name += " "+lexical_cast<string>((short)dataset->TechTree.BuildingConnections[index].UnitsTechsFirst[age]);
				break;
			case 7: // Line Mode
				Name += "LM "+lexical_cast<string>(dataset->TechTree.BuildingConnections[index].LineMode);
				break;
			case 8: // Enabling Research
				Name += "E "+lexical_cast<string>(dataset->TechTree.BuildingConnections[index].EnablingResearch);
				break;
		}
		Name += ", ";
		if(Selection[1] < 1) break;
	}

	Name += lexical_cast<string>(dataset->TechTree.BuildingConnections[index].ID)+" ";
	if(dataset->Civs[0].Units.size() <= dataset->TechTree.BuildingConnections[index].ID) return Name;
	if(!LangDLLstring(dataset->Civs[0].Units[dataset->TechTree.BuildingConnections[index].ID].LanguageDLLName, 2).empty())
	{
		Name += LangDLLstring(dataset->Civs[0].Units[dataset->TechTree.BuildingConnections[index].ID].LanguageDLLName, 64);
	}
	else if(!dataset->Civs[0].Units[dataset->TechTree.BuildingConnections[index].ID].Name.empty())
	{
		Name += dataset->Civs[0].Units[dataset->TechTree.BuildingConnections[index].ID].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTBuildingSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTBuildings();
}

void AGE_Frame::ListTTBuildings()
{
	InitTTBuildings();
	wxTimerEvent E;
	OnTTBuildingTimer(E);
}

void AGE_Frame::InitTTBuildings()
{
	searchText = TechTrees_MainList_Buildings_Search->GetValue().MakeLower();
	excludeText = TechTrees_MainList_Buildings_Search_R->GetValue().MakeLower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = TechTrees_MainList_Buildings_UseAnd[loop]->GetValue();

	TechTrees_MainList_Buildings_ListV->names.clear();
	TechTrees_MainList_Buildings_ListV->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.BuildingConnections.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTTBuildingName(loop);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_MainList_Buildings_ListV->names.Add(Name);
			TechTrees_MainList_Buildings_ListV->indexes.push_back(loop);
		}
	}

	virtualListing(TechTrees_MainList_Buildings_ListV);

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;
}

void AGE_Frame::OnTTBuildingSelect(wxCommandEvent &event)
{
    if(!ttBuildingTimer.IsRunning())
        ttBuildingTimer.Start(150);
}

void AGE_Frame::OnTTBuildingTimer(wxTimerEvent &event)
{
	ttBuildingTimer.Stop();
	auto selections = TechTrees_MainList_Buildings_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, TechTrees_MainList_Buildings_ListV, TTBuildConIDs);

	for(auto &box: uiGroupTTBuilding) box->clear();
	TechTrees_Buildings_Items.UsedItems->clear();

	genie::BuildingConnection * BuildingConPointer;
	for(auto sel = selections; sel--> 0;)
	{
		BuildingConPointer = &dataset->TechTree.BuildingConnections[TTBuildConIDs[sel]];

		TechTrees_Buildings_ID->prepend(&BuildingConPointer->ID);
		TechTrees_Buildings_Always2->prepend(&BuildingConPointer->Unknown1);
		TechTrees_Buildings_Items.UsedItems->prepend(&BuildingConPointer->Common.SlotsUsed);
		TechTrees_Buildings_LocationInAge->prepend(&BuildingConPointer->LocationInAge);
		TechTrees_Buildings_LineMode->prepend(&BuildingConPointer->LineMode);
		TechTrees_Buildings_EnablingResearch->prepend(&BuildingConPointer->EnablingResearch);
		for(short loop = 0; loop < 5; ++loop)
		{
			TechTrees_Buildings_TotalUnitsTechs[loop]->prepend(&BuildingConPointer->UnitsTechsTotal[loop]);
			TechTrees_Buildings_TotalUnitsTechs[loop+5]->prepend(&BuildingConPointer->UnitsTechsFirst[loop]);
		}
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected building: "+lexical_cast<string>(TTBuildConIDs[0]), 0);

	for(auto &box: uiGroupTTBuilding) box->update();
	TechTrees_Buildings_Items.UsedItems->update();

	ListTTBuildingBuildings();
	ListTTBuildingUnits();
	ListTTBuildingResearches();
	ListTTBuildingItems();
}

void AGE_Frame::OnTTBuildingAdd(wxCommandEvent &event)
{
	if(NULL == dataset) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->TechTree.BuildingConnections);
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Buildings_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->TechTree.BuildingConnections, TTBuildConIDs[0]);
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Buildings_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.BuildingConnections, TTBuildConIDs);
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Buildings_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.BuildingConnections, TTBuildConIDs, copies.TTBuildCon);
	TechTrees_MainList_Buildings_ListV->SetFocus();
}

void AGE_Frame::OnTTBuildingPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Buildings_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTBuildConIDs.size(), copies.TTBuildCon.size()))
		{
			PasteToList(dataset->TechTree.BuildingConnections, TTBuildConIDs, copies.TTBuildCon);
		}
	}
	else
	{
		PasteToList(dataset->TechTree.BuildingConnections, TTBuildConIDs[0], copies.TTBuildCon);
	}
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Buildings_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->TechTree.BuildingConnections, TTBuildConIDs[0], copies.TTBuildCon);
	ListTTBuildings();
}

void AGE_Frame::OnTTBuildingBuildingSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTBuildingBuildings();
}

void AGE_Frame::ListTTBuildingBuildings()
{
	searchText = TechTrees_Buildings_Buildings.Search->GetValue().MakeLower();
	excludeText = TechTrees_Buildings_Buildings.SearchRecursive->GetValue().MakeLower();

	TechTrees_Buildings_Buildings.List->names.clear();
	TechTrees_Buildings_Buildings.List->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetBuildingName(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_Buildings_Buildings.List->names.Add(Name);
			TechTrees_Buildings_Buildings.List->indexes.push_back(loop);
		}
	}
	virtualListing(TechTrees_Buildings_Buildings.List);

	wxTimerEvent E;
	OnTTBuildingBuildingTimer(E);
}

void AGE_Frame::OnTTBuildingBuildingSelect(wxCommandEvent &event)
{
    if(!ttBuildingBuildingTimer.IsRunning())
        ttBuildingBuildingTimer.Start(150);
}

void AGE_Frame::OnTTBuildingBuildingTimer(wxTimerEvent &event)
{
    ttBuildingBuildingTimer.Stop();
	auto selections = TechTrees_Buildings_Buildings.List->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    TechTrees_Buildings_Buildings.Item->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, TechTrees_Buildings_Buildings.List, TTBuildBuildIDs);
		int32_t * BuildingPointer;
		for(auto loop = selections; loop--> 0;)
		{
			BuildingPointer = &dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings[TTBuildBuildIDs[loop]];
			TechTrees_Buildings_Buildings.Item->prepend(BuildingPointer);
		}
	}
    TechTrees_Buildings_Buildings.Item->update();
}

void AGE_Frame::OnTTBuildingBuildingAdd(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Buildings_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings);
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs[0]);
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs);
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs, copies.TTBuildBuild);
	TechTrees_Buildings_Buildings.List->SetFocus();
}

void AGE_Frame::OnTTBuildingBuildingPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTBuildBuildIDs.size(), copies.TTBuildBuild.size()))
		{
			PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs, copies.TTBuildBuild);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs[0], copies.TTBuildBuild);
	}
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings, TTBuildBuildIDs[0], copies.TTBuildBuild);
	ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingCopyToBuildings(wxCommandEvent &event)
{
	for(short loop=1; loop < TTBuildConIDs.size(); ++loop)
	{
		dataset->TechTree.BuildingConnections[TTBuildConIDs[loop]].Buildings = dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Buildings;
	}
}

void AGE_Frame::OnTTBuildingUnitSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTBuildingUnits();
}

void AGE_Frame::ListTTBuildingUnits()
{
	searchText = TechTrees_Buildings_Units.Search->GetValue().MakeLower();
	excludeText = TechTrees_Buildings_Units.SearchRecursive->GetValue().MakeLower();

	TechTrees_Buildings_Units.List->names.clear();
	TechTrees_Buildings_Units.List->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Units.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Units[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_Buildings_Units.List->names.Add(Name);
			TechTrees_Buildings_Units.List->indexes.push_back(loop);
		}
	}
	virtualListing(TechTrees_Buildings_Units.List);

	wxTimerEvent E;
	OnTTBuildingUnitTimer(E);
}

void AGE_Frame::OnTTBuildingUnitSelect(wxCommandEvent &event)
{
    if(!ttBuildingUnitTimer.IsRunning())
        ttBuildingUnitTimer.Start(150);
}

void AGE_Frame::OnTTBuildingUnitTimer(wxTimerEvent &event)
{
    ttBuildingUnitTimer.Stop();
	auto selections = TechTrees_Buildings_Units.List->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    TechTrees_Buildings_Units.Item->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, TechTrees_Buildings_Units.List, TTBuildUnitIDs);
		int32_t * UnitPointer;
		for(auto loop = selections; loop--> 0;)
		{
			UnitPointer = &dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Units[TTBuildUnitIDs[loop]];
			TechTrees_Buildings_Units.Item->prepend(UnitPointer);
		}
	}
    TechTrees_Buildings_Units.Item->update();
}

void AGE_Frame::OnTTBuildingUnitAdd(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Buildings_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Units);
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs[0]);
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs);
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs, copies.TTBuildUnit);
	TechTrees_Buildings_Units.List->SetFocus();
}

void AGE_Frame::OnTTBuildingUnitPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTBuildUnitIDs.size(), copies.TTBuildUnit.size()))
		{
			PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs, copies.TTBuildUnit);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs[0], copies.TTBuildUnit);
	}
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Units, TTBuildUnitIDs[0], copies.TTBuildUnit);
	ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitCopyToBuildings(wxCommandEvent &event)
{
	for(short loop=1; loop < TTBuildConIDs.size(); ++loop)
	{
		dataset->TechTree.BuildingConnections[TTBuildConIDs[loop]].Units = dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Units;
	}
}

void AGE_Frame::OnTTBuildingResearchSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTBuildingResearches();
}

void AGE_Frame::ListTTBuildingResearches()
{
	searchText = TechTrees_Buildings_Researches.Search->GetValue().MakeLower();
	excludeText = TechTrees_Buildings_Researches.SearchRecursive->GetValue().MakeLower();

	TechTrees_Buildings_Researches.List->names.clear();
	TechTrees_Buildings_Researches.List->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetSimpleResearchName(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_Buildings_Researches.List->names.Add(Name);
			TechTrees_Buildings_Researches.List->indexes.push_back(loop);
		}
	}
	virtualListing(TechTrees_Buildings_Researches.List);

	wxTimerEvent E;
	OnTTBuildingResearchTimer(E);
}

void AGE_Frame::OnTTBuildingResearchSelect(wxCommandEvent &event)
{
    if(!ttBuildingResearchTimer.IsRunning())
        ttBuildingResearchTimer.Start(150);
}

void AGE_Frame::OnTTBuildingResearchTimer(wxTimerEvent &event)
{
    ttBuildingResearchTimer.Stop();
	auto selections = TechTrees_Buildings_Researches.List->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    TechTrees_Buildings_Researches.Item->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, TechTrees_Buildings_Researches.List, TTBuildResIDs);
		int32_t * ResearchPointer;
		for(auto loop = selections; loop--> 0;)
		{
			ResearchPointer = &dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches[TTBuildResIDs[loop]];
			TechTrees_Buildings_Researches.Item->prepend(ResearchPointer);
		}
	}
    TechTrees_Buildings_Researches.Item->update();
}

void AGE_Frame::OnTTBuildingResearchAdd(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Buildings_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches);
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs[0]);
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs);
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs, copies.TTBuildRes);
	TechTrees_Buildings_Researches.List->SetFocus();
}

void AGE_Frame::OnTTBuildingResearchPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTBuildResIDs.size(), copies.TTBuildRes.size()))
		{
			PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs, copies.TTBuildRes);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs[0], copies.TTBuildRes);
	}
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches, TTBuildResIDs[0], copies.TTBuildRes);
	ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchCopyToBuildings(wxCommandEvent &event)
{
	for(short loop=1; loop < TTBuildConIDs.size(); ++loop)
	{
		dataset->TechTree.BuildingConnections[TTBuildConIDs[loop]].Researches = dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Researches;
	}
}

void AGE_Frame::OnTTBuildingItemSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTBuildingItems();
}

void AGE_Frame::ListTTBuildingItems()
{
	ListTTCommonItems(TechTrees_Buildings_Items, &dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Common);
	wxTimerEvent E;
	OnTTBuildingItemTimer(E);
}

void AGE_Frame::OnTTBuildingItemSelect(wxCommandEvent &event)
{
    if(!ttBuildingItemTimer.IsRunning())
        ttBuildingItemTimer.Start(150);
}

void AGE_Frame::OnTTBuildingItemTimer(wxTimerEvent &event)
{
	ttBuildingItemTimer.Stop();
	SelectTTCommonItems(TechTrees_Buildings_Items, &dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Common);
}

void AGE_Frame::OnTTBuildingItemCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Items.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Common.UnitResearch, TTItemIDs, copies.TTItem);
	CopyFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Common.Mode, TTItemIDs, copies.TTMode);
	TechTrees_Buildings_Items.List->SetFocus();
}

void AGE_Frame::OnTTBuildingItemPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Buildings_Items.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTItemIDs.size(), copies.TTItem.size()))
		{
			PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Common.UnitResearch, TTItemIDs, copies.TTItem);
			PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Common.Mode, TTItemIDs, copies.TTMode);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Common.UnitResearch, TTItemIDs[0], copies.TTItem);
		PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Common.Mode, TTItemIDs[0], copies.TTMode);
	}
	ListTTBuildingItems();
}

void AGE_Frame::OnTTBuildingItemCopyToBuildings(wxCommandEvent &event)
{
	for(short loop=1; loop < TTBuildConIDs.size(); ++loop)
	{
		dataset->TechTree.BuildingConnections[TTBuildConIDs[loop]].Common = dataset->TechTree.BuildingConnections[TTBuildConIDs[0]].Common;
	}
}

string AGE_Frame::GetTTUnitName(int index)
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
				Name += "S "+lexical_cast<string>((short)dataset->TechTree.UnitConnections[index].Unknown1);
				break;
			case 2: // Upper Building
				Name += "U "+lexical_cast<string>(dataset->TechTree.UnitConnections[index].UpperBuilding);
				break;
			case 3: // Required Items
				Name += "I "+lexical_cast<string>(dataset->TechTree.UnitConnections[index].Common.SlotsUsed);
				break;
			case 4: // Age
				Name += "A "+lexical_cast<string>(dataset->TechTree.UnitConnections[index].Common.UnitResearch[0]);
				break;
			case 5: // Vertical Line Number
				Name += "V "+lexical_cast<string>(dataset->TechTree.UnitConnections[index].VerticalLine);
				break;
			case 6: // Space Sharing
				Name += "LA "+lexical_cast<string>(dataset->TechTree.UnitConnections[index].LocationInAge);
				break;
			case 7: // Required Research
				Name += "R "+lexical_cast<string>(dataset->TechTree.UnitConnections[index].RequiredResearch);
				break;
			case 8: // Placement
				Name += "LM "+lexical_cast<string>(dataset->TechTree.UnitConnections[index].LineMode);
				break;
			case 9: // Enabling Research
				Name += "E "+lexical_cast<string>(dataset->TechTree.UnitConnections[index].EnablingResearch);
				break;
		}
		Name += ", ";
		if(Selection[1] < 1) break;
	}

	Name += lexical_cast<string>(dataset->TechTree.UnitConnections[index].ID)+" ";
	if(dataset->Civs[0].Units.size() <= dataset->TechTree.UnitConnections[index].ID) return Name;
	if(!LangDLLstring(dataset->Civs[0].Units[dataset->TechTree.UnitConnections[index].ID].LanguageDLLName, 2).empty())
	{
		Name += LangDLLstring(dataset->Civs[0].Units[dataset->TechTree.UnitConnections[index].ID].LanguageDLLName, 64);
	}
	else if(!dataset->Civs[0].Units[dataset->TechTree.UnitConnections[index].ID].Name.empty())
	{
		Name += dataset->Civs[0].Units[dataset->TechTree.UnitConnections[index].ID].Name;
	}
	else
	{
		Name += "New Unit";
	}
	return Name;
}

void AGE_Frame::OnTTUnitSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTUnits();
}

void AGE_Frame::ListTTUnits()
{
	InitTTUnits();
	wxTimerEvent E;
	OnTTUnitTimer(E);
}

void AGE_Frame::InitTTUnits()
{
	searchText = TechTrees_MainList_Units_Search->GetValue().MakeLower();
	excludeText = TechTrees_MainList_Units_Search_R->GetValue().MakeLower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = TechTrees_MainList_Units_UseAnd[loop]->GetValue();

	TechTrees_MainList_Units_ListV->names.clear();
	TechTrees_MainList_Units_ListV->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.UnitConnections.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTTUnitName(loop);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_MainList_Units_ListV->names.Add(Name);
			TechTrees_MainList_Units_ListV->indexes.push_back(loop);
		}
	}

	virtualListing(TechTrees_MainList_Units_ListV);

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;
}

void AGE_Frame::OnTTUnitSelect(wxCommandEvent &event)
{
    if(!ttUnitTimer.IsRunning())
        ttUnitTimer.Start(150);
}

void AGE_Frame::OnTTUnitTimer(wxTimerEvent &event)
{
	ttUnitTimer.Stop();
	auto selections = TechTrees_MainList_Units_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, TechTrees_MainList_Units_ListV, TTUnitConIDs);

	for(auto &box: uiGroupTTUnit) box->clear();
	TechTrees_Units_Items.UsedItems->clear();

	genie::UnitConnection * UnitConPointer;
	for(auto sel = selections; sel--> 0;)
	{
		UnitConPointer = &dataset->TechTree.UnitConnections[TTUnitConIDs[sel]];

		TechTrees_Units_ID->prepend(&UnitConPointer->ID);
		TechTrees_Units_Always2->prepend(&UnitConPointer->Unknown1);
		TechTrees_Units_UpperBuilding->prepend(&UnitConPointer->UpperBuilding);
		TechTrees_Units_Items.UsedItems->prepend(&UnitConPointer->Common.SlotsUsed);
		TechTrees_Units_VerticalLine->prepend(&UnitConPointer->VerticalLine);
		TechTrees_Units_LocationInAge->prepend(&UnitConPointer->LocationInAge);
		TechTrees_Units_RequiredResearch->prepend(&UnitConPointer->RequiredResearch);
		TechTrees_Units_LineMode->prepend(&UnitConPointer->LineMode);
		TechTrees_Units_EnablingResearch->prepend(&UnitConPointer->EnablingResearch);
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected unit: "+lexical_cast<string>(TTUnitConIDs[0]), 0);

	for(auto &box: uiGroupTTUnit) box->update();
	TechTrees_Units_Items.UsedItems->update();

	ListTTUnitUnits();
	ListTTUnitItems();
}

void AGE_Frame::OnTTUnitAdd(wxCommandEvent &event)
{
	if(NULL == dataset) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->TechTree.UnitConnections);
	ListTTUnits();
}

void AGE_Frame::OnTTUnitInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->TechTree.UnitConnections, TTUnitConIDs[0]);
	ListTTUnits();
}

void AGE_Frame::OnTTUnitDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.UnitConnections, TTUnitConIDs);
	ListTTUnits();
}

void AGE_Frame::OnTTUnitCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.UnitConnections, TTUnitConIDs, copies.TTUnitCon);
	TechTrees_MainList_Units_ListV->SetFocus();
}

void AGE_Frame::OnTTUnitPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTUnitConIDs.size(), copies.TTUnitCon.size()))
		{
			PasteToList(dataset->TechTree.UnitConnections, TTUnitConIDs, copies.TTUnitCon);
		}
	}
	else
	{
		PasteToList(dataset->TechTree.UnitConnections, TTUnitConIDs[0], copies.TTUnitCon);
	}
	ListTTUnits();
}

void AGE_Frame::OnTTUnitPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->TechTree.UnitConnections, TTUnitConIDs[0], copies.TTUnitCon);
	ListTTUnits();
}

void AGE_Frame::OnTTUnitUnitSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTUnitUnits();
}

void AGE_Frame::ListTTUnitUnits()
{
	searchText = TechTrees_Units_Units.Search->GetValue().MakeLower();
	excludeText = TechTrees_Units_Units.SearchRecursive->GetValue().MakeLower();

	TechTrees_Units_Units.List->names.clear();
	TechTrees_Units_Units.List->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Units.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Units[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_Units_Units.List->names.Add(Name);
			TechTrees_Units_Units.List->indexes.push_back(loop);
		}
	}
	virtualListing(TechTrees_Units_Units.List);

	wxTimerEvent E;
	OnTTUnitUnitTimer(E);
}

void AGE_Frame::OnTTUnitUnitSelect(wxCommandEvent &event)
{
    if(!ttUnitUnitTimer.IsRunning())
        ttUnitUnitTimer.Start(150);
}

void AGE_Frame::OnTTUnitUnitTimer(wxTimerEvent &event)
{
    ttUnitUnitTimer.Stop();
	auto selections = TechTrees_Units_Units.List->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    TechTrees_Units_Units.Item->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, TechTrees_Units_Units.List, TTUnitUnitIDs);
		int32_t * UnitPointer;
		for(auto loop = selections; loop--> 0;)
		{
			UnitPointer = &dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Units[TTUnitUnitIDs[loop]];
			TechTrees_Units_Units.Item->prepend(UnitPointer);
		}
	}
    TechTrees_Units_Units.Item->update();
}

void AGE_Frame::OnTTUnitUnitAdd(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Units);
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Units_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs[0]);
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_Units_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs);
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Units_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs, copies.TTUnitUnit);
	TechTrees_Units_Units.List->SetFocus();
}

void AGE_Frame::OnTTUnitUnitPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Units_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTUnitUnitIDs.size(), copies.TTUnitUnit.size()))
		{
			PasteToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs, copies.TTUnitUnit);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs[0], copies.TTUnitUnit);
	}
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Units_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Units, TTUnitUnitIDs[0], copies.TTUnitUnit);
	ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitCopyToUnits(wxCommandEvent &event)
{
	for(short loop=1; loop < TTUnitConIDs.size(); ++loop)
	{
		dataset->TechTree.UnitConnections[TTUnitConIDs[loop]].Units = dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Units;
	}
}

void AGE_Frame::ListTTCommonItems(AGE_AreaTT84 &area, genie::techtree::Common* dataPointer)
{
	searchText = area.Search->GetValue().MakeLower();
	excludeText = area.SearchRecursive->GetValue().MakeLower();

	area.List->names.clear();
	area.List->indexes.clear();

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
			area.List->names.Add(Name);
			area.List->indexes.push_back(loop);
		}
	}
	virtualListing(area.List);
}

void AGE_Frame::OnTTUnitItemSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTUnitItems();
}

void AGE_Frame::ListTTUnitItems()
{
	ListTTCommonItems(TechTrees_Units_Items, &dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Common);
	wxTimerEvent E;
	OnTTUnitItemTimer(E);
}

void AGE_Frame::OnTTUnitItemSelect(wxCommandEvent &event)
{
    if(!ttUnitItemTimer.IsRunning())
        ttUnitItemTimer.Start(150);
}

void AGE_Frame::OnTTUnitItemTimer(wxTimerEvent &event)
{
	ttUnitItemTimer.Stop();
	SelectTTCommonItems(TechTrees_Units_Items, &dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Common);
}

void AGE_Frame::OnTTUnitItemCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Units_Items.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Common.UnitResearch, TTItemIDs, copies.TTItem);
	CopyFromList(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Common.Mode, TTItemIDs, copies.TTMode);
	TechTrees_Units_Items.List->SetFocus();
}

void AGE_Frame::OnTTUnitItemPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Units_Items.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTItemIDs.size(), copies.TTItem.size()))
		{
			PasteToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Common.UnitResearch, TTItemIDs, copies.TTItem);
			PasteToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Common.Mode, TTItemIDs, copies.TTMode);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Common.UnitResearch, TTItemIDs[0], copies.TTItem);
		PasteToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Common.Mode, TTItemIDs[0], copies.TTMode);
	}
	ListTTUnitItems();
}

void AGE_Frame::OnTTUnitItemCopyToUnits(wxCommandEvent &event)
{
	for(short loop=1; loop < TTUnitConIDs.size(); ++loop)
	{
		dataset->TechTree.UnitConnections[TTUnitConIDs[loop]].Common = dataset->TechTree.UnitConnections[TTUnitConIDs[0]].Common;
	}
}

string AGE_Frame::GetTTResearchName(int index)
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
				Name += "S "+lexical_cast<string>((short)dataset->TechTree.ResearchConnections[index].Unknown1);
				break;
			case 2: // Upper Building
				Name += "U "+lexical_cast<string>(dataset->TechTree.ResearchConnections[index].UpperBuilding);
				break;
			case 3: // Required Items
				Name += "I "+lexical_cast<string>(dataset->TechTree.ResearchConnections[index].Common.SlotsUsed);
				break;
			case 4: // Age
				Name += "A "+lexical_cast<string>(dataset->TechTree.ResearchConnections[index].Common.UnitResearch[0]);
				break;
			case 5: // Vertical Line Number
				Name += "V "+lexical_cast<string>(dataset->TechTree.ResearchConnections[index].VerticalLine);
				break;
			case 6: // Location in Age
				Name += "LA "+lexical_cast<string>(dataset->TechTree.ResearchConnections[index].LocationInAge);
				break;
			case 7: // First Age Mode
				Name += "LM "+lexical_cast<string>(dataset->TechTree.ResearchConnections[index].LineMode);
				break;
		}
		Name += ", ";
		if(Selection[1] < 1) break;
	}

	Name += lexical_cast<string>(dataset->TechTree.ResearchConnections[index].ID)+" ";
	if(dataset->Researchs.size() <= dataset->TechTree.ResearchConnections[index].ID) return Name;
	if(!LangDLLstring(dataset->Researchs[dataset->TechTree.ResearchConnections[index].ID].LanguageDLLName, 2).empty())
	{
		Name += LangDLLstring(dataset->Researchs[dataset->TechTree.ResearchConnections[index].ID].LanguageDLLName, 64);
	}
	else if(!dataset->Researchs[dataset->TechTree.ResearchConnections[index].ID].Name.empty())
	{
		Name += dataset->Researchs[dataset->TechTree.ResearchConnections[index].ID].Name;
	}
	else
	{
		Name += "New Research";
	}
	return Name;
}

void AGE_Frame::OnTTResearchSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTResearches();
}

void AGE_Frame::ListTTResearches()
{
	InitTTResearches();
	wxTimerEvent E;
	OnTTResearchTimer(E);
}

void AGE_Frame::InitTTResearches()
{
	searchText = TechTrees_MainList_Researches_Search->GetValue().MakeLower();
	excludeText = TechTrees_MainList_Researches_Search_R->GetValue().MakeLower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = TechTrees_MainList_Researches_UseAnd[loop]->GetValue();

	TechTrees_MainList_Researches_ListV->names.clear();
	TechTrees_MainList_Researches_ListV->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.ResearchConnections.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetTTResearchName(loop);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_MainList_Researches_ListV->names.Add(Name);
			TechTrees_MainList_Researches_ListV->indexes.push_back(loop);
		}
	}

	virtualListing(TechTrees_MainList_Researches_ListV);

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;
}

void AGE_Frame::OnTTResearchSelect(wxCommandEvent &event)
{
    if(!ttResearchTimer.IsRunning())
        ttResearchTimer.Start(150);
}

void AGE_Frame::OnTTResearchTimer(wxTimerEvent &event)
{
	ttResearchTimer.Stop();
	auto selections = TechTrees_MainList_Researches_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, TechTrees_MainList_Researches_ListV, TTResConIDs);

	for(auto &box: uiGroupTTResearch) box->clear();
	TechTrees_Researches_Items.UsedItems->clear();

	genie::ResearchConnection * ResearchConPointer;
	for(auto sel = selections; sel--> 0;)
	{
		ResearchConPointer = &dataset->TechTree.ResearchConnections[TTResConIDs[sel]];

		TechTrees_Researches_ID->prepend(&ResearchConPointer->ID);
		TechTrees_Researches_Always2->prepend(&ResearchConPointer->Unknown1);
		TechTrees_Researches_UpperBuilding->prepend(&ResearchConPointer->UpperBuilding);
		TechTrees_Researches_Items.UsedItems->prepend(&ResearchConPointer->Common.SlotsUsed);
		TechTrees_Researches_VerticalLine->prepend(&ResearchConPointer->VerticalLine);
		TechTrees_Researches_LocationInAge->prepend(&ResearchConPointer->LocationInAge);
		TechTrees_Researches_LineMode->prepend(&ResearchConPointer->LineMode);
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected research: "+lexical_cast<string>(TTResConIDs[0]), 0);

	for(auto &box: uiGroupTTResearch) box->update();
	TechTrees_Researches_Items.UsedItems->update();

	ListTTResearchBuildings();
	ListTTResearchUnits();
	ListTTResearchResearches();
	ListTTResearchItems();
}

void AGE_Frame::OnTTResearchAdd(wxCommandEvent &event)
{
	if(NULL == dataset) return;

	wxBusyCursor WaitCursor;
	AddToList(dataset->TechTree.ResearchConnections);
	ListTTResearches();
}

void AGE_Frame::OnTTResearchInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Researches_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(dataset->TechTree.ResearchConnections, TTResConIDs[0]);
	ListTTResearches();
}

void AGE_Frame::OnTTResearchDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Researches_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.ResearchConnections, TTResConIDs);
	ListTTResearches();
}

void AGE_Frame::OnTTResearchCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Researches_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.ResearchConnections, TTResConIDs, copies.TTResCon);
	TechTrees_MainList_Researches_ListV->SetFocus();
}

void AGE_Frame::OnTTResearchPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Researches_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTResConIDs.size(), copies.TTResCon.size()))
		{
			PasteToList(dataset->TechTree.ResearchConnections, TTResConIDs, copies.TTResCon);
		}
	}
	else
	{
		PasteToList(dataset->TechTree.ResearchConnections, TTResConIDs[0], copies.TTResCon);
	}
	ListTTResearches();
}

void AGE_Frame::OnTTResearchPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Researches_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->TechTree.ResearchConnections, TTResConIDs[0], copies.TTResCon);
	ListTTResearches();
}

void AGE_Frame::OnTTResearchBuildingSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTResearchBuildings();
}

void AGE_Frame::ListTTResearchBuildings()
{
	searchText = TechTrees_Researches_Buildings.Search->GetValue().MakeLower();
	excludeText = TechTrees_Researches_Buildings.SearchRecursive->GetValue().MakeLower();

	TechTrees_Researches_Buildings.List->names.clear();
	TechTrees_Researches_Buildings.List->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.ResearchConnections[TTResConIDs[0]].Buildings.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetBuildingName(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Buildings[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_Researches_Buildings.List->names.Add(Name);
			TechTrees_Researches_Buildings.List->indexes.push_back(loop);
		}
	}
	virtualListing(TechTrees_Researches_Buildings.List);

	wxTimerEvent E;
	OnTTResearchBuildingTimer(E);
}

void AGE_Frame::OnTTResearchBuildingSelect(wxCommandEvent &event)
{
    if(!ttResearchBuildingTimer.IsRunning())
        ttResearchBuildingTimer.Start(150);
}

void AGE_Frame::OnTTResearchBuildingTimer(wxTimerEvent &event)
{
    ttResearchBuildingTimer.Stop();
	auto selections = TechTrees_Researches_Buildings.List->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    TechTrees_Researches_Buildings.Item->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, TechTrees_Researches_Buildings.List, TTResBuildIDs);
		int32_t * BuildingPointer;
		for(auto loop = selections; loop--> 0;)
		{
			BuildingPointer = &dataset->TechTree.ResearchConnections[TTResConIDs[0]].Buildings[TTResBuildIDs[loop]];
			TechTrees_Researches_Buildings.Item->prepend(BuildingPointer);
		}
	}
    TechTrees_Researches_Buildings.Item->update();
}

void AGE_Frame::OnTTResearchBuildingAdd(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Researches_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Buildings);
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs[0]);
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs);
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs, copies.TTResBuild);
	TechTrees_Researches_Buildings.List->SetFocus();
}

void AGE_Frame::OnTTResearchBuildingPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTResBuildIDs.size(), copies.TTResBuild.size()))
		{
			PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs, copies.TTResBuild);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs[0], copies.TTResBuild);
	}
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Buildings.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Buildings, TTResBuildIDs[0], copies.TTResBuild);
	ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingCopyToResearches(wxCommandEvent &event)
{
	for(short loop=1; loop < TTResConIDs.size(); ++loop)
	{
		dataset->TechTree.ResearchConnections[TTResConIDs[loop]].Buildings = dataset->TechTree.ResearchConnections[TTResConIDs[0]].Buildings;
	}
}

void AGE_Frame::OnTTResearchUnitSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTResearchUnits();
}

void AGE_Frame::ListTTResearchUnits()
{
	searchText = TechTrees_Researches_Units.Search->GetValue().MakeLower();
	excludeText = TechTrees_Researches_Units.SearchRecursive->GetValue().MakeLower();

	TechTrees_Researches_Units.List->names.clear();
	TechTrees_Researches_Units.List->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.ResearchConnections[TTResConIDs[0]].Units.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Units[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_Researches_Units.List->names.Add(Name);
			TechTrees_Researches_Units.List->indexes.push_back(loop);
		}
	}
	virtualListing(TechTrees_Researches_Units.List);

	wxTimerEvent E;
	OnTTResearchUnitTimer(E);
}

void AGE_Frame::OnTTResearchUnitSelect(wxCommandEvent &event)
{
    if(!ttResearchUnitTimer.IsRunning())
        ttResearchUnitTimer.Start(150);
}

void AGE_Frame::OnTTResearchUnitTimer(wxTimerEvent &event)
{
    ttResearchUnitTimer.Stop();
	auto selections = TechTrees_Researches_Units.List->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    TechTrees_Researches_Units.Item->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, TechTrees_Researches_Units.List, TTResUnitIDs);
		int32_t * UnitPointer;
		for(auto loop = selections; loop--> 0;)
		{
			UnitPointer = &dataset->TechTree.ResearchConnections[TTResConIDs[0]].Units[TTResUnitIDs[loop]];
			TechTrees_Researches_Units.Item->prepend(UnitPointer);
		}
	}
    TechTrees_Researches_Units.Item->update();
}

void AGE_Frame::OnTTResearchUnitAdd(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Researches_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Units);
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs[0]);
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs);
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs, copies.TTResUnit);
	TechTrees_Researches_Units.List->SetFocus();
}

void AGE_Frame::OnTTResearchUnitPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTResUnitIDs.size(), copies.TTResUnit.size()))
		{
			PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs, copies.TTResUnit);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs[0], copies.TTResUnit);
	}
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Units.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Units, TTResUnitIDs[0], copies.TTResUnit);
	ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitCopyToResearches(wxCommandEvent &event)
{
	for(short loop=1; loop < TTResConIDs.size(); ++loop)
	{
		dataset->TechTree.ResearchConnections[TTResConIDs[loop]].Units = dataset->TechTree.ResearchConnections[TTResConIDs[0]].Units;
	}
}

void AGE_Frame::OnTTResearchResearchSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTResearchResearches();
}

void AGE_Frame::ListTTResearchResearches()
{
	searchText = TechTrees_Researches_Researches.Search->GetValue().MakeLower();
	excludeText = TechTrees_Researches_Researches.SearchRecursive->GetValue().MakeLower();

	TechTrees_Researches_Researches.List->names.clear();
	TechTrees_Researches_Researches.List->indexes.clear();

	for(short loop = 0; loop < dataset->TechTree.ResearchConnections[TTResConIDs[0]].Researches.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetSimpleResearchName(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Researches[loop]);
		if(SearchMatches(Name.Lower()))
		{
			TechTrees_Researches_Researches.List->names.Add(Name);
			TechTrees_Researches_Researches.List->indexes.push_back(loop);
		}
	}
	virtualListing(TechTrees_Researches_Researches.List);

	wxTimerEvent E;
	OnTTResearchResearchTimer(E);
}

void AGE_Frame::OnTTResearchResearchSelect(wxCommandEvent &event)
{
    if(!ttResearchResearchTimer.IsRunning())
        ttResearchResearchTimer.Start(150);
}

void AGE_Frame::OnTTResearchResearchTimer(wxTimerEvent &event)
{
    ttResearchResearchTimer.Stop();
	auto selections = TechTrees_Researches_Researches.List->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    TechTrees_Researches_Researches.Item->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, TechTrees_Researches_Researches.List, TTResResIDs);
		int32_t * ResearchPointer;
		for(auto loop = selections; loop--> 0;)
		{
			ResearchPointer = &dataset->TechTree.ResearchConnections[TTResConIDs[0]].Researches[TTResResIDs[loop]];
			TechTrees_Researches_Researches.Item->prepend(ResearchPointer);
		}
    }
    TechTrees_Researches_Researches.Item->update();
}

void AGE_Frame::OnTTResearchResearchAdd(wxCommandEvent &event)
{
	auto selections = TechTrees_MainList_Researches_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Researches);
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs[0]);
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchDelete(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs);
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs, copies.TTResRes);
	TechTrees_Researches_Researches.List->SetFocus();
}

void AGE_Frame::OnTTResearchResearchPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTResResIDs.size(), copies.TTResRes.size()))
		{
			PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs, copies.TTResRes);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs[0], copies.TTResRes);
	}
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchPasteInsert(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Researches.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Researches, TTResResIDs[0], copies.TTResRes);
	ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchCopyToResearches(wxCommandEvent &event)
{
	for(short loop=1; loop < TTResConIDs.size(); ++loop)
	{
		dataset->TechTree.ResearchConnections[TTResConIDs[loop]].Researches = dataset->TechTree.ResearchConnections[TTResConIDs[0]].Researches;
	}
}

void AGE_Frame::OnTTResearchItemSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListTTResearchItems();
}

void AGE_Frame::ListTTResearchItems()
{
	ListTTCommonItems(TechTrees_Researches_Items, &dataset->TechTree.ResearchConnections[TTResConIDs[0]].Common);
	wxTimerEvent E;
	OnTTResearchItemTimer(E);
}

void AGE_Frame::OnTTResearchItemSelect(wxCommandEvent &event)
{
    if(!ttResearchItemTimer.IsRunning())
        ttResearchItemTimer.Start(150);
}

void AGE_Frame::OnTTResearchItemTimer(wxTimerEvent &event)
{
	ttResearchItemTimer.Stop();
	SelectTTCommonItems(TechTrees_Researches_Items, &dataset->TechTree.ResearchConnections[TTResConIDs[0]].Common);
}

void AGE_Frame::OnTTResearchItemCopy(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Items.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Common.UnitResearch, TTItemIDs, copies.TTItem);
	CopyFromList(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Common.Mode, TTItemIDs, copies.TTMode);
	TechTrees_Researches_Items.List->SetFocus();
}

void AGE_Frame::OnTTResearchItemPaste(wxCommandEvent &event)
{
	auto selections = TechTrees_Researches_Items.List->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(TTItemIDs.size(), copies.TTItem.size()))
		{
			PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Common.UnitResearch, TTItemIDs, copies.TTItem);
			PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Common.Mode, TTItemIDs, copies.TTMode);
		}
	}
	else
	{
		PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Common.UnitResearch, TTItemIDs[0], copies.TTItem);
		PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs[0]].Common.Mode, TTItemIDs[0], copies.TTMode);
	}
	ListTTResearchItems();
}

void AGE_Frame::OnTTResearchItemCopyToResearches(wxCommandEvent &event)
{
	for(short loop=1; loop < TTResConIDs.size(); ++loop)
	{
		dataset->TechTree.ResearchConnections[TTResConIDs[loop]].Common = dataset->TechTree.ResearchConnections[TTResConIDs[0]].Common;
	}
}

void AGE_Frame::CreateTechTreeControls()
{
	Tab_TechTrees = new wxPanel(TabBar_Main);

	TechTrees_Main = new wxBoxSizer(wxVERTICAL);
	TabBar_TechTree = new wxNotebook(Tab_TechTrees, wxID_ANY);
	Tab_TechTreeAges = new wxPanel(TabBar_TechTree);
	Tab_TechTreeBuildings = new wxPanel(TabBar_TechTree);
	Tab_TechTreeUnits = new wxPanel(TabBar_TechTree);
	Tab_TechTreeResearches = new wxPanel(TabBar_TechTree);
	TechTrees_TabAges = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_TabBuildings = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_TabUnits = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_TabResearches = new wxBoxSizer(wxHORIZONTAL);
	TechTrees_ScrollerAges = new wxScrolledWindow(Tab_TechTreeAges, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
	TechTrees_ScrollerBuildings = new wxScrolledWindow(Tab_TechTreeBuildings, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
	TechTrees_ScrollerUnits = new wxScrolledWindow(Tab_TechTreeUnits, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
	TechTrees_ScrollerResearches = new wxScrolledWindow(Tab_TechTreeResearches, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);

	wxString StatusHelp = "0 generic\n1 ?\n2 default\n3 marks this as not available\n4 upgrading or constructing or creating\n5 research completed or building built";
	wxString LocationInAgeHelp = "0 Hidden\n1 First\n2 Second";
	wxString LineModeHelp = "0 research: First age\n1 age: ?\n2 unit: First in vertical line\n3 unit: Not first\n4 research: Others\n5 building: One or more connections\n6 building: No connections";

	General_Variables2_Holder = new wxStaticBoxSizer(wxVERTICAL, Tab_TechTrees, "Technology Tree Related");
	General_Variables2_Grid = new wxGridSizer(8, 5, 5);
	for(short loop = 0; loop < General_TTUnknown.size(); ++loop)
	{
		General_TTUnknown_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		General_TTUnknown_Text[loop] = new wxStaticText(Tab_TechTrees, wxID_ANY, " Unknown "+lexical_cast<string>(loop+1));
		General_TTUnknown[loop] = AGETextCtrl::init(CLong, &uiGroupMaps, this, AGEwindow, Tab_TechTrees);
	}
	General_TTUnknown[7]->SetToolTip("In the file this is between\nage/building/unit/research\ncounts and their data");

	TechTrees_MainList_Ages = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Buildings = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Units = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Researches = new wxBoxSizer(wxVERTICAL);
	TechTrees_MainList_Ages_Search = new wxTextCtrl(Tab_TechTreeAges, wxID_ANY);
	TechTrees_MainList_Ages_Search_R = new wxTextCtrl(Tab_TechTreeAges, wxID_ANY);
	TechTrees_MainList_Ages_ListV = new AGEListView(Tab_TechTreeAges, wxSize(200, 300));
	TechTrees_MainList_Ages_Buttons = new wxGridSizer(3, 0, 0);
	TechTrees_MainList_Ages_Add = new wxButton(Tab_TechTreeAges, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Insert = new wxButton(Tab_TechTreeAges, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Delete = new wxButton(Tab_TechTreeAges, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Copy = new wxButton(Tab_TechTreeAges, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_Paste = new wxButton(Tab_TechTreeAges, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Ages_PasteInsert = new wxButton(Tab_TechTreeAges, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	TechTrees_Ages_ID_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_ID_Text = new wxStaticText(TechTrees_ScrollerAges, wxID_ANY, " Age Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_ID = AGETextCtrl::init(CLong, &uiGroupTTAge, this, AGEwindow, TechTrees_ScrollerAges);
	TechTrees_Ages_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_Unknown2_Text = new wxStaticText(TechTrees_ScrollerAges, wxID_ANY, " Status *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_Unknown2 = AGETextCtrl::init(CByte, &uiGroupTTAge, this, AGEwindow, TechTrees_ScrollerAges);
	TechTrees_Ages_Unknown2->SetToolTip(StatusHelp);

	TechTrees_Ages_LineMode_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Ages_LineMode_Text = new wxStaticText(TechTrees_ScrollerAges, wxID_ANY, " Line Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Ages_LineMode = AGETextCtrl::init(CLong, &uiGroupTTAge, this, AGEwindow, TechTrees_ScrollerAges);
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
	TechTrees_MainList_Buildings_UseAnd[0] = new wxCheckBox(Tab_TechTreeBuildings, wxID_ANY, "And");
	TechTrees_MainList_Buildings_Search_R = new wxTextCtrl(Tab_TechTreeBuildings, wxID_ANY);
	TechTrees_MainList_Buildings_UseAnd[1] = new wxCheckBox(Tab_TechTreeBuildings, wxID_ANY, "And");
	for(short loop = 0; loop < 2; ++loop)
	{
		TechTrees_MainList_Buildings_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		TechTrees_MainList_Buildings_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_TechTreeBuildings, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
		TechTrees_Buildings_TotalUnitsTechs_Grid[loop] = new wxGridSizer(5, 0, 5);
	}
	TechTrees_MainList_Buildings_ListV = new AGEListView(Tab_TechTreeBuildings, wxSize(200, 300));
	TechTrees_MainList_Buildings_Buttons = new wxGridSizer(3, 0, 0);
	TechTrees_MainList_Buildings_Add = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Insert = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Delete = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Copy = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_Paste = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Buildings_PasteInsert = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	TechTrees_Buildings_ID_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_ID_Text = new wxStaticText(TechTrees_ScrollerBuildings, wxID_ANY, " Building Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_ID = AGETextCtrl::init(CLong, &uiGroupTTBuilding, this, AGEwindow, TechTrees_ScrollerBuildings);
	TechTrees_Buildings_ID_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerBuildings, TechTrees_Buildings_ID);
	UnitComboBoxList.push_back(TechTrees_Buildings_ID_ComboBox);
	TechTrees_Buildings_Always2_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_Always2_Text = new wxStaticText(TechTrees_ScrollerBuildings, wxID_ANY, " Status *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_Always2 = AGETextCtrl::init(CByte, &uiGroupTTBuilding, this, AGEwindow, TechTrees_ScrollerBuildings);
	TechTrees_Buildings_Always2->SetToolTip(StatusHelp);
	TechTrees_Buildings_LocationInAge_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_LocationInAge_Text = new wxStaticText(TechTrees_ScrollerBuildings, wxID_ANY, " Location in Age *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_LocationInAge = AGETextCtrl::init(CByte, &uiGroupTTBuilding, this, AGEwindow, TechTrees_ScrollerBuildings);
	TechTrees_Buildings_LocationInAge->SetToolTip(LocationInAgeHelp);
	TechTrees_Buildings_LineMode_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_LineMode_Text = new wxStaticText(TechTrees_ScrollerBuildings, wxID_ANY, " Line Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_LineMode = AGETextCtrl::init(CLong, &uiGroupTTBuilding, this, AGEwindow, TechTrees_ScrollerBuildings);
	TechTrees_Buildings_LineMode->SetToolTip(LineModeHelp);
	TechTrees_Buildings_EnablingResearch_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Buildings_EnablingResearch_Text = new wxStaticText(TechTrees_ScrollerBuildings, wxID_ANY, " Enabling Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Buildings_EnablingResearch = AGETextCtrl::init(CLong, &uiGroupTTBuilding, this, AGEwindow, TechTrees_ScrollerBuildings);
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
	TechTrees_Buildings_TotalUnitsTechs[loop] = AGETextCtrl::init(CByte, &uiGroupTTBuilding, this, AGEwindow, TechTrees_ScrollerBuildings);
	for(short loop = 0; loop < 5; ++loop)
	{
		TechTrees_Buildings_TotalUnitsTechs[loop]->SetToolTip("Age "+lexical_cast<string>(loop+1));
		TechTrees_Buildings_TotalUnitsTechs[loop+5]->SetToolTip("Age "+lexical_cast<string>(loop+1));
	}

	TechTrees_MainList_Units_Search = new wxTextCtrl(Tab_TechTreeUnits, wxID_ANY);
	TechTrees_MainList_Units_UseAnd[0] = new wxCheckBox(Tab_TechTreeUnits, wxID_ANY, "And");
	TechTrees_MainList_Units_Search_R = new wxTextCtrl(Tab_TechTreeUnits, wxID_ANY);
	TechTrees_MainList_Units_UseAnd[1] = new wxCheckBox(Tab_TechTreeUnits, wxID_ANY, "And");
	for(short loop = 0; loop < 2; ++loop)
	{
		TechTrees_MainList_Units_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		TechTrees_MainList_Units_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_TechTreeUnits, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	TechTrees_MainList_Units_ListV = new AGEListView(Tab_TechTreeUnits, wxSize(200, 300));
	TechTrees_MainList_Units_Buttons = new wxGridSizer(3, 0, 0);
	TechTrees_MainList_Units_Add = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Insert = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Delete = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Copy = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_Paste = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	TechTrees_MainList_Units_PasteInsert = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	TechTrees_Units_ID_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_ID_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Unit Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_ID = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_ID_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerUnits, TechTrees_Units_ID);
	UnitComboBoxList.push_back(TechTrees_Units_ID_ComboBox);
	TechTrees_Units_Always2_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_Always2_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Status *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_Always2 = AGETextCtrl::init(CByte, &uiGroupTTUnit, this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_Always2->SetToolTip(StatusHelp);
	TechTrees_Units_UpperBuilding_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_UpperBuilding_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Upper Building", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_UpperBuilding = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_UpperBuilding_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerUnits, TechTrees_Units_UpperBuilding);
	UnitComboBoxList.push_back(TechTrees_Units_UpperBuilding_ComboBox);
	TechTrees_Units_VerticalLine_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_VerticalLine_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Vertical Line Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_VerticalLine = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_LocationInAge_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_LocationInAge_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Location in Age *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_LocationInAge = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_LocationInAge->SetToolTip(LocationInAgeHelp);
	TechTrees_Units_RequiredResearch_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_RequiredResearch_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Required Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_RequiredResearch = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_RequiredResearch->SetToolTip("Upgrades unit\nUsed by units, which aren't first in upgrade line");
	TechTrees_Units_RequiredResearch_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerUnits, TechTrees_Units_RequiredResearch);
	ResearchComboBoxList.push_back(TechTrees_Units_RequiredResearch_ComboBox);
	TechTrees_Units_LineMode_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_LineMode_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Line Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_LineMode = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, AGEwindow, TechTrees_ScrollerUnits);
	TechTrees_Units_LineMode->SetToolTip(LineModeHelp);
	TechTrees_Units_EnablingResearch_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Units_EnablingResearch_Text = new wxStaticText(TechTrees_ScrollerUnits, wxID_ANY, " Enabling Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Units_EnablingResearch = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, AGEwindow, TechTrees_ScrollerUnits);
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
	TechTrees_MainList_Researches_UseAnd[0] = new wxCheckBox(Tab_TechTreeResearches, wxID_ANY, "And");
	TechTrees_MainList_Researches_Search_R = new wxTextCtrl(Tab_TechTreeResearches, wxID_ANY);
	TechTrees_MainList_Researches_UseAnd[1] = new wxCheckBox(Tab_TechTreeResearches, wxID_ANY, "And");
	for(short loop = 0; loop < 2; ++loop)
	{
		TechTrees_MainList_Researches_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		TechTrees_MainList_Researches_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_TechTreeResearches, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	TechTrees_MainList_Researches_ListV = new AGEListView(Tab_TechTreeResearches, wxSize(200, 300));
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
	TechTrees_Researches_ID = AGETextCtrl::init(CLong, &uiGroupTTResearch, this, AGEwindow, TechTrees_ScrollerResearches);
	TechTrees_Researches_ID_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerResearches, TechTrees_Researches_ID);
	ResearchComboBoxList.push_back(TechTrees_Researches_ID_ComboBox);
	TechTrees_Researches_Always2_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_Always2_Text = new wxStaticText(TechTrees_ScrollerResearches, wxID_ANY, " Status *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_Always2 = AGETextCtrl::init(CByte, &uiGroupTTResearch, this, AGEwindow, TechTrees_ScrollerResearches);
	TechTrees_Researches_Always2->SetToolTip(StatusHelp);
	TechTrees_Researches_UpperBuilding_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_UpperBuilding_Text = new wxStaticText(TechTrees_ScrollerResearches, wxID_ANY, " Upper Building", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_UpperBuilding = AGETextCtrl::init(CLong, &uiGroupTTResearch, this, AGEwindow, TechTrees_ScrollerResearches);
	TechTrees_Researches_UpperBuilding_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerResearches, TechTrees_Researches_UpperBuilding);
	UnitComboBoxList.push_back(TechTrees_Researches_UpperBuilding_ComboBox);
	TechTrees_Researches_VerticalLine_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_VerticalLine_Text = new wxStaticText(TechTrees_ScrollerResearches, wxID_ANY, " Vertical Line Number", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_VerticalLine = AGETextCtrl::init(CLong, &uiGroupTTResearch, this, AGEwindow, TechTrees_ScrollerResearches);
	TechTrees_Researches_LocationInAge_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_LocationInAge_Text = new wxStaticText(TechTrees_ScrollerResearches, wxID_ANY, " Location in Age *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_LocationInAge = AGETextCtrl::init(CLong, &uiGroupTTResearch, this, AGEwindow, TechTrees_ScrollerResearches);
	TechTrees_Researches_LocationInAge->SetToolTip(LocationInAgeHelp);
	TechTrees_Researches_LineMode_Holder = new wxBoxSizer(wxVERTICAL);
	TechTrees_Researches_LineMode_Text = new wxStaticText(TechTrees_ScrollerResearches, wxID_ANY, " Line Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TechTrees_Researches_LineMode = AGETextCtrl::init(CLong, &uiGroupTTResearch, this, AGEwindow, TechTrees_ScrollerResearches);
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
		General_TTUnknown_Holder[loop]->Add(General_TTUnknown_Text[loop], 0, wxEXPAND | wxBOTTOM, 2);
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
	TechTrees_MainList_Buildings_Searches[0]->Add(TechTrees_MainList_Buildings_UseAnd[0], 0, wxEXPAND | wxLEFT, 2);
	TechTrees_MainList_Buildings_Searches[1]->Add(TechTrees_MainList_Buildings_Search_R, 1, wxEXPAND);
	TechTrees_MainList_Buildings_Searches[1]->Add(TechTrees_MainList_Buildings_UseAnd[1], 0, wxEXPAND | wxLEFT, 2);
	TechTrees_MainList_Units_Searches[0]->Add(TechTrees_MainList_Units_Search, 1, wxEXPAND);
	TechTrees_MainList_Units_Searches[0]->Add(TechTrees_MainList_Units_UseAnd[0], 0, wxEXPAND | wxLEFT, 2);
	TechTrees_MainList_Units_Searches[1]->Add(TechTrees_MainList_Units_Search_R, 1, wxEXPAND);
	TechTrees_MainList_Units_Searches[1]->Add(TechTrees_MainList_Units_UseAnd[1], 0, wxEXPAND | wxLEFT, 2);
	TechTrees_MainList_Researches_Searches[0]->Add(TechTrees_MainList_Researches_Search, 1, wxEXPAND);
	TechTrees_MainList_Researches_Searches[0]->Add(TechTrees_MainList_Researches_UseAnd[0], 0, wxEXPAND | wxLEFT, 2);
	TechTrees_MainList_Researches_Searches[1]->Add(TechTrees_MainList_Researches_Search_R, 1, wxEXPAND);
	TechTrees_MainList_Researches_Searches[1]->Add(TechTrees_MainList_Researches_UseAnd[1], 0, wxEXPAND | wxLEFT, 2);
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
	TechTrees_MainList_Ages->Add(TechTrees_MainList_Ages_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	TechTrees_MainList_Buildings->Add(TechTrees_MainList_Buildings_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	TechTrees_MainList_Units->Add(TechTrees_MainList_Units_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	TechTrees_MainList_Researches->Add(TechTrees_MainList_Researches_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	TechTrees_MainList_Ages->Add(TechTrees_MainList_Ages_Buttons, 0, wxEXPAND);
	TechTrees_MainList_Buildings->Add(TechTrees_MainList_Buildings_Buttons, 0, wxEXPAND);
	TechTrees_MainList_Units->Add(TechTrees_MainList_Units_Buttons, 0, wxEXPAND);
	TechTrees_MainList_Researches->Add(TechTrees_MainList_Researches_Buttons, 0, wxEXPAND);

	TechTrees_ConnectedHolder_Ages->Add(TechTrees_Ages_Buildings.ItemList, 1, wxEXPAND);
	TechTrees_ConnectedHolder_Ages->Add(TechTrees_Ages_Units.ItemList, 1, wxEXPAND | wxLEFT, 5);
	TechTrees_ConnectedHolder_Ages->Add(TechTrees_Ages_Researches.ItemList, 1, wxEXPAND | wxLEFT, 5);

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
	TechTrees_Data_Ages2->Add(TechTrees_Ages_UnknownItems.Area, 1, wxEXPAND | wxLEFT, 5);
	TechTrees_Data_Ages2->AddStretchSpacer(1);

	TechTrees_Data_Ages->Add(TechTrees_Data_Ages1, 0, wxEXPAND | wxBOTTOM, 5);
	TechTrees_Data_Ages->Add(TechTrees_ConnectedHolder_Ages, 0, wxEXPAND | wxBOTTOM, 5);
	TechTrees_Data_Ages->Add(TechTrees_Data_Ages2, 0, wxEXPAND);

	TechTrees_ConnectedHolder_Buildings->Add(TechTrees_Buildings_Buildings.ItemList, 1, wxEXPAND);
	TechTrees_ConnectedHolder_Buildings->Add(TechTrees_Buildings_Units.ItemList, 1, wxEXPAND | wxLEFT, 5);
	TechTrees_ConnectedHolder_Buildings->Add(TechTrees_Buildings_Researches.ItemList, 1, wxEXPAND | wxLEFT, 5);

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
	TechTrees_Data_Buildings3->Add(TechTrees_Buildings_TotalUnitsTechs_Holder[1], 0, wxEXPAND | wxTOP, 5);
	TechTrees_Data_Buildings2->Add(TechTrees_Buildings_Items.Area, 1, wxEXPAND);
	TechTrees_Data_Buildings2->Add(TechTrees_Data_Buildings3, 2, wxEXPAND | wxLEFT, 5);

	TechTrees_Data_Buildings->Add(TechTrees_Data_Buildings1, 0, wxEXPAND | wxBOTTOM, 5);
	TechTrees_Data_Buildings->Add(TechTrees_ConnectedHolder_Buildings, 0, wxEXPAND | wxBOTTOM, 5);
	TechTrees_Data_Buildings->Add(TechTrees_Data_Buildings2, 0, wxEXPAND);

	TechTrees_ConnectedHolder_Units->Add(TechTrees_Units_Items.Area, 1, wxEXPAND);
	TechTrees_ConnectedHolder_Units->Add(TechTrees_Units_Units.ItemList, 1, wxEXPAND | wxLEFT, 5);
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
	TechTrees_Data_Units1->Add(0, 0);
	TechTrees_Data_Units1->Add(0, 0);
	TechTrees_Data_Units1->Add(TechTrees_Units_VerticalLine_Holder, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_LocationInAge_Holder, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_RequiredResearch_Holder, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_LineMode_Holder, 1, wxEXPAND);
	TechTrees_Data_Units1->Add(TechTrees_Units_EnablingResearch_Holder, 1, wxEXPAND);

	TechTrees_Data_Units->Add(TechTrees_Data_Units1, 0, wxEXPAND | wxBOTTOM, 5);
	TechTrees_Data_Units->Add(TechTrees_ConnectedHolder_Units, 0, wxEXPAND);

	TechTrees_ConnectedHolder_Researches->Add(TechTrees_Researches_Buildings.ItemList, 1, wxEXPAND);
	TechTrees_ConnectedHolder_Researches->Add(TechTrees_Researches_Units.ItemList, 1, wxEXPAND | wxLEFT, 5);
	TechTrees_ConnectedHolder_Researches->Add(TechTrees_Researches_Researches.ItemList, 1, wxEXPAND | wxLEFT, 5);

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
	TechTrees_Data_Researches2->Add(TechTrees_Researches_Items.Area, 1, wxEXPAND | wxLEFT, 5);

	TechTrees_Data_Researches->Add(TechTrees_ConnectedHolder_Researches, 0, wxEXPAND | wxBOTTOM, 5);
	TechTrees_Data_Researches->Add(TechTrees_Data_Researches2, 0, wxEXPAND);

	TechTrees_ScrollerAges->SetSizer(TechTrees_Data_Ages);
	TechTrees_ScrollerAges->SetScrollRate(0, 15);
	TechTrees_TabAges->Add(TechTrees_MainList_Ages, 21, wxEXPAND | wxRIGHT, 5);
	TechTrees_TabAges->Add(TechTrees_ScrollerAges, 65, wxEXPAND | wxTOP, 5);

	TechTrees_ScrollerBuildings->SetSizer(TechTrees_Data_Buildings);
	TechTrees_ScrollerBuildings->SetScrollRate(0, 15);
	TechTrees_TabBuildings->Add(TechTrees_MainList_Buildings, 21, wxEXPAND | wxRIGHT, 5);
	TechTrees_TabBuildings->Add(TechTrees_ScrollerBuildings, 65, wxEXPAND | wxTOP, 5);

	TechTrees_ScrollerUnits->SetSizer(TechTrees_Data_Units);
	TechTrees_ScrollerUnits->SetScrollRate(0, 15);
	TechTrees_TabUnits->Add(TechTrees_MainList_Units, 21, wxEXPAND | wxRIGHT, 5);
	TechTrees_TabUnits->Add(TechTrees_ScrollerUnits, 65, wxEXPAND | wxTOP, 5);

	TechTrees_ScrollerResearches->SetSizer(TechTrees_Data_Researches);
	TechTrees_ScrollerResearches->SetScrollRate(0, 15);
	TechTrees_TabResearches->Add(TechTrees_MainList_Researches, 21, wxEXPAND | wxRIGHT, 5);
	TechTrees_TabResearches->Add(TechTrees_ScrollerResearches, 65, wxEXPAND | wxTOP, 5);

	TechTrees_Main->Add(General_Variables2_Holder, 0, wxEXPAND | wxALL, 5);
	TechTrees_Main->Add(TabBar_TechTree, 1, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 5);

	Tab_TechTreeAges->SetSizer(TechTrees_TabAges);
	Tab_TechTreeBuildings->SetSizer(TechTrees_TabBuildings);
	Tab_TechTreeUnits->SetSizer(TechTrees_TabUnits);
	Tab_TechTreeResearches->SetSizer(TechTrees_TabResearches);
	Tab_TechTrees->SetSizer(TechTrees_Main);

	Connect(TechTrees_MainList_Ages_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesSearch));
	Connect(TechTrees_MainList_Ages_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTAgesSearch));
	Connect(TechTrees_MainList_Ages_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesSelect));
	Connect(TechTrees_MainList_Ages_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesSelect));
	Connect(TechTrees_MainList_Ages_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTAgesSelect));
	Connect(TechTrees_MainList_Ages_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesAdd));
	Connect(TechTrees_MainList_Ages_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesInsert));
	Connect(TechTrees_MainList_Ages_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesDelete));
	Connect(TechTrees_MainList_Ages_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesCopy));
	Connect(TechTrees_MainList_Ages_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesPaste));
	Connect(TechTrees_MainList_Ages_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTAgesPasteInsert));
	Connect(TechTrees_MainList_Buildings_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSearch));
	Connect(TechTrees_MainList_Buildings_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSearch));
	Connect(TechTrees_MainList_Buildings_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSelect));
	Connect(TechTrees_MainList_Buildings_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSelect));
	Connect(TechTrees_MainList_Buildings_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTBuildingSelect));
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
	Connect(TechTrees_MainList_Units_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTUnitSelect));
	Connect(TechTrees_MainList_Units_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTUnitSelect));
	Connect(TechTrees_MainList_Units_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTUnitSelect));
	Connect(TechTrees_MainList_Units_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitAdd));
	Connect(TechTrees_MainList_Units_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitInsert));
	Connect(TechTrees_MainList_Units_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitDelete));
	Connect(TechTrees_MainList_Units_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitCopy));
	Connect(TechTrees_MainList_Units_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitPaste));
	Connect(TechTrees_MainList_Units_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTTUnitPasteInsert));
	Connect(TechTrees_MainList_Researches_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchSearch));
	Connect(TechTrees_MainList_Researches_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTTResearchSearch));
	Connect(TechTrees_MainList_Researches_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchSelect));
	Connect(TechTrees_MainList_Researches_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchSelect));
	Connect(TechTrees_MainList_Researches_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTResearchSelect));
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
	Connect(TechTrees_Ages_Buildings.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingSelect));
	Connect(TechTrees_Ages_Units.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitSelect));
	Connect(TechTrees_Ages_Researches.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchSelect));
	Connect(TechTrees_Ages_Items.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgeItemSelect));
	Connect(TechTrees_Ages_UnknownItems.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgeUnknownItemSelect));
	Connect(TechTrees_Ages_Buildings.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingSelect));
	Connect(TechTrees_Ages_Units.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitSelect));
	Connect(TechTrees_Ages_Researches.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchSelect));
	Connect(TechTrees_Ages_Items.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgeItemSelect));
	Connect(TechTrees_Ages_UnknownItems.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTAgeUnknownItemSelect));
	Connect(TechTrees_Ages_Buildings.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTAgesBuildingSelect));
	Connect(TechTrees_Ages_Units.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTAgesUnitSelect));
	Connect(TechTrees_Ages_Researches.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTAgesResearchSelect));
	Connect(TechTrees_Ages_Items.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTAgeItemSelect));
	Connect(TechTrees_Ages_UnknownItems.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTAgeUnknownItemSelect));
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
	Connect(TechTrees_Buildings_Buildings.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingSelect));
	Connect(TechTrees_Buildings_Units.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitSelect));
	Connect(TechTrees_Buildings_Researches.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchSelect));
	Connect(TechTrees_Buildings_Items.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingItemSelect));
	Connect(TechTrees_Buildings_Buildings.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingSelect));
	Connect(TechTrees_Buildings_Units.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitSelect));
	Connect(TechTrees_Buildings_Researches.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchSelect));
	Connect(TechTrees_Buildings_Items.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTBuildingItemSelect));
	Connect(TechTrees_Buildings_Buildings.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTBuildingBuildingSelect));
	Connect(TechTrees_Buildings_Units.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTBuildingUnitSelect));
	Connect(TechTrees_Buildings_Researches.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTBuildingResearchSelect));
	Connect(TechTrees_Buildings_Items.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTBuildingItemSelect));
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
	Connect(TechTrees_Units_Units.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitSelect));
	Connect(TechTrees_Units_Items.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTUnitItemSelect));
	Connect(TechTrees_Units_Units.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitSelect));
	Connect(TechTrees_Units_Items.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTUnitItemSelect));
	Connect(TechTrees_Units_Units.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTUnitUnitSelect));
	Connect(TechTrees_Units_Items.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTUnitItemSelect));
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
	Connect(TechTrees_Researches_Buildings.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingSelect));
	Connect(TechTrees_Researches_Units.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitSelect));
	Connect(TechTrees_Researches_Researches.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchSelect));
	Connect(TechTrees_Researches_Items.List->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchItemSelect));
	Connect(TechTrees_Researches_Buildings.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingSelect));
	Connect(TechTrees_Researches_Units.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitSelect));
	Connect(TechTrees_Researches_Researches.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchSelect));
	Connect(TechTrees_Researches_Items.List->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnTTResearchItemSelect));
	Connect(TechTrees_Researches_Buildings.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTResearchBuildingSelect));
	Connect(TechTrees_Researches_Units.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTResearchUnitSelect));
	Connect(TechTrees_Researches_Researches.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTResearchResearchSelect));
	Connect(TechTrees_Researches_Items.List->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnTTResearchItemSelect));
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

    ttAgeTimer.Connect(ttAgeTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTAgesTimer), NULL, this);
    ttAgeBuildingTimer.Connect(ttAgeBuildingTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTAgesBuildingTimer), NULL, this);
    ttAgeUnitTimer.Connect(ttAgeUnitTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTAgesUnitTimer), NULL, this);
    ttAgeResearchTimer.Connect(ttAgeResearchTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTAgesResearchTimer), NULL, this);
    ttAgeItemTimer.Connect(ttAgeItemTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTAgeItemTimer), NULL, this);
    ttAgeUnknownTimer.Connect(ttAgeUnknownTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTAgeUnknownItemTimer), NULL, this);
    ttBuildingTimer.Connect(ttBuildingTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTBuildingTimer), NULL, this);
    ttBuildingBuildingTimer.Connect(ttBuildingBuildingTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTBuildingBuildingTimer), NULL, this);
    ttBuildingUnitTimer.Connect(ttBuildingUnitTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTBuildingUnitTimer), NULL, this);
    ttBuildingResearchTimer.Connect(ttBuildingResearchTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTBuildingResearchTimer), NULL, this);
    ttBuildingItemTimer.Connect(ttBuildingItemTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTBuildingItemTimer), NULL, this);
    ttUnitTimer.Connect(ttUnitTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTUnitTimer), NULL, this);
    ttUnitUnitTimer.Connect(ttUnitUnitTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTUnitUnitTimer), NULL, this);
    ttUnitItemTimer.Connect(ttUnitItemTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTUnitItemTimer), NULL, this);
    ttResearchTimer.Connect(ttResearchTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTResearchTimer), NULL, this);
    ttResearchBuildingTimer.Connect(ttResearchBuildingTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTResearchBuildingTimer), NULL, this);
    ttResearchUnitTimer.Connect(ttResearchUnitTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTResearchUnitTimer), NULL, this);
    ttResearchResearchTimer.Connect(ttResearchResearchTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTResearchResearchTimer), NULL, this);
    ttResearchItemTimer.Connect(ttResearchItemTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnTTResearchItemTimer), NULL, this);

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

void AGE_Frame::OnKillFocus_TechTrees(wxFocusEvent &event)
{
	//event.Skip();
	if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
	if(event.GetId() == TechTrees_Ages_ID->GetId())
	{
		ListTTAges();
	}
	else if(event.GetId() == TechTrees_Ages_Buildings.Item->GetId())
	{
		ListTTAgeBuildings();
	}
	else if(event.GetId() == TechTrees_Ages_Units.Item->GetId())
	{
		ListTTAgeUnits();
	}
	else if(event.GetId() == TechTrees_Ages_Researches.Item->GetId())
	{
		ListTTAgeResearches();
	}
	else if(event.GetId() == TechTrees_Ages_Items.Item->GetId() || event.GetId() == TechTrees_Ages_Items.Mode->GetId())
	{
		ListTTAgeItems();
	}
	else if(event.GetId() == TechTrees_Ages_UnknownItems.Unknown1->GetId() || event.GetId() == TechTrees_Ages_UnknownItems.Unknown2->GetId())
	{
		ListTTAgeUnknownItems();
	}
	else if(event.GetId() == TechTrees_Buildings_ID->GetId())
	{
		ListTTBuildings();
	}
	else if(event.GetId() == TechTrees_Buildings_Buildings.Item->GetId())
	{
		ListTTBuildingBuildings();
	}
	else if(event.GetId() == TechTrees_Buildings_Units.Item->GetId())
	{
		ListTTBuildingUnits();
	}
	else if(event.GetId() == TechTrees_Buildings_Researches.Item->GetId())
	{
		ListTTBuildingResearches();
	}
	else if(event.GetId() == TechTrees_Buildings_Items.Item->GetId() || event.GetId() == TechTrees_Buildings_Items.Mode->GetId())
	{
		ListTTBuildingItems();
	}
	else if(event.GetId() == TechTrees_Units_ID->GetId())
	{
		ListTTUnits();
	}
	else if(event.GetId() == TechTrees_Units_Units.Item->GetId())
	{
		ListTTUnitUnits();
	}
	else if(event.GetId() == TechTrees_Units_Items.Item->GetId() || event.GetId() == TechTrees_Units_Items.Mode->GetId())
	{
		ListTTUnitItems();
	}
	else if(event.GetId() == TechTrees_Researches_ID->GetId())
	{
		ListTTResearches();
	}
	else if(event.GetId() == TechTrees_Researches_Buildings.Item->GetId())
	{
		ListTTResearchBuildings();
	}
	else if(event.GetId() == TechTrees_Researches_Units.Item->GetId())
	{
		ListTTResearchUnits();
	}
	else if(event.GetId() == TechTrees_Researches_Researches.Item->GetId())
	{
		ListTTResearchResearches();
	}
	else if(event.GetId() == TechTrees_Researches_Items.Item->GetId() || event.GetId() == TechTrees_Researches_Items.Mode->GetId())
	{
		ListTTResearchItems();
	}
	else if(false)
	{
		wxTimerEvent E;
		OnTTUnitTimer(E);
	}
	else if(false)
	{
		wxTimerEvent E;
		OnTTBuildingTimer(E);
	}
}

void AGE_Frame::OnUpdateCombo_TechTrees(wxCommandEvent &event)
{
	if(event.GetId() == TechTrees_Ages_Items.ModeCombo->GetId())
	{
		TechTrees_Ages_Items.Mode->ChangeValue(lexical_cast<string>(TechTrees_Ages_Items.ModeCombo->GetSelection()));
		TechTrees_Ages_Items.Mode->SaveEdits(true);
		ListTTAgeItems();
		return;
	}
	if(event.GetId() == TechTrees_Buildings_Items.ModeCombo->GetId())
	{
		TechTrees_Buildings_Items.Mode->ChangeValue(lexical_cast<string>(TechTrees_Buildings_Items.ModeCombo->GetSelection()));
		TechTrees_Buildings_Items.Mode->SaveEdits(true);
		ListTTBuildingItems();
		return;
	}
	if(event.GetId() == TechTrees_Units_Items.ModeCombo->GetId())
	{
		TechTrees_Units_Items.Mode->ChangeValue(lexical_cast<string>(TechTrees_Units_Items.ModeCombo->GetSelection()));
		TechTrees_Units_Items.Mode->SaveEdits(true);
		ListTTUnitItems();
		return;
	}
	if(event.GetId() == TechTrees_Researches_Items.ModeCombo->GetId())
	{
		TechTrees_Researches_Items.Mode->ChangeValue(lexical_cast<string>(TechTrees_Researches_Items.ModeCombo->GetSelection()));
		TechTrees_Researches_Items.Mode->SaveEdits(true);
		ListTTResearchItems();
		return;
	}
	((AGEComboBox*)event.GetEventObject())->OnUpdate(event);
	if(event.GetId() == TechTrees_Ages_Buildings.ItemCombo->GetId())
	{
		ListTTAgeBuildings();
	}
	else if(event.GetId() == TechTrees_Ages_Units.ItemCombo->GetId())
	{
		ListTTAgeUnits();
	}
	else if(event.GetId() == TechTrees_Ages_Researches.ItemCombo->GetId())
	{
		ListTTAgeResearches();
	}
	else if(event.GetId() == TechTrees_Ages_Items.ItemCombo->GetId())
	{
		ListTTAgeItems();
	}
	else if(event.GetId() == TechTrees_Buildings_ID_ComboBox->GetId())
	{
		ListTTBuildings();
	}
	else if(event.GetId() == TechTrees_Buildings_Buildings.ItemCombo->GetId())
	{
		ListTTBuildingBuildings();
	}
	else if(event.GetId() == TechTrees_Buildings_Units.ItemCombo->GetId())
	{
		ListTTBuildingUnits();
	}
	else if(event.GetId() == TechTrees_Buildings_Researches.ItemCombo->GetId())
	{
		ListTTBuildingResearches();
	}
	else if(event.GetId() == TechTrees_Buildings_Items.ItemCombo->GetId())
	{
		ListTTBuildingItems();
	}
	else if(event.GetId() == TechTrees_Units_ID_ComboBox->GetId())
	{
		ListTTUnits();
	}
	else if(event.GetId() == TechTrees_Units_Units.ItemCombo->GetId())
	{
		ListTTUnitUnits();
	}
	else if(event.GetId() == TechTrees_Units_Items.ItemCombo->GetId())
	{
		ListTTUnitItems();
	}
	else if(event.GetId() == TechTrees_Researches_ID_ComboBox->GetId())
	{
		ListTTResearches();
	}
	else if(event.GetId() == TechTrees_Researches_Buildings.ItemCombo->GetId())
	{
		ListTTResearchBuildings();
	}
	else if(event.GetId() == TechTrees_Researches_Units.ItemCombo->GetId())
	{
		ListTTResearchUnits();
	}
	else if(event.GetId() == TechTrees_Researches_Researches.ItemCombo->GetId())
	{
		ListTTResearchResearches();
	}
	else if(event.GetId() == TechTrees_Researches_Items.ItemCombo->GetId())
	{
		ListTTResearchItems();
	}
}
