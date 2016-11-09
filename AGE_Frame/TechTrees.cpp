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
    InitSearch(TechTrees_MainList_Ages_Search->GetValue().MakeLower(), TechTrees_MainList_Ages_Search_R->GetValue().MakeLower());

    TechTrees_MainList_Ages_ListV->names.clear();
    TechTrees_MainList_Ages_ListV->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.TechTreeAges.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetTTAgesName(loop);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_MainList_Ages_ListV->names.Add(Name);
            TechTrees_MainList_Ages_ListV->indexes.push_back(loop);
        }
    }

    RefreshList(TechTrees_MainList_Ages_ListV, &TTAgeIDs);
}

void AGE_Frame::OnTTAgesSelect(wxCommandEvent &event)
{
    if(!ttAgeTimer.IsRunning())
        ttAgeTimer.Start(150);
}

void AGE_Frame::OnTTAgesTimer(wxTimerEvent&)
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
    SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected age: "+lexical_cast<string>(TTAgeIDs.front()), 0);

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
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->TechTree.TechTreeAges);
    ListTTAges();
}

void AGE_Frame::OnTTAgesInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_MainList_Ages_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->TechTree.TechTreeAges, TTAgeIDs.front());
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
    PasteToList(dataset->TechTree.TechTreeAges, TTAgeIDs, copies.TTAge);
    ListTTAges();
}

void AGE_Frame::OnTTAgesPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_MainList_Ages_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->TechTree.TechTreeAges, TTAgeIDs.front(), copies.TTAge);
    ListTTAges();
}

string AGE_Frame::GetBuildingName(int Building)
{
    string Name = lexical_cast<string>(Building)+" ";
    if(dataset->Civs.front().Units.size() <= Building) return Name + "Nonexistent Building";
    if(!LangDLLstring(dataset->Civs.front().Units[Building].LanguageDLLName, 2).empty())
    {
        return Name + string(LangDLLstring(dataset->Civs.front().Units[Building].LanguageDLLName, 64));
    }
    if(!dataset->Civs.front().Units[Building].Name.empty())
    {
        return Name + dataset->Civs.front().Units[Building].Name;
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
    InitSearch(TechTrees_Ages_Buildings.Search->GetValue().MakeLower(), TechTrees_Ages_Buildings.SearchRecursive->GetValue().MakeLower());

    TechTrees_Ages_Buildings.List->names.clear();
    TechTrees_Ages_Buildings.List->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Buildings.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetBuildingName(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Buildings[loop]);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_Ages_Buildings.List->names.Add(Name);
            TechTrees_Ages_Buildings.List->indexes.push_back(loop);
        }
    }
    RefreshList(TechTrees_Ages_Buildings.List, &TTAgeBuildIDs);

    wxTimerEvent E;
    OnTTAgesBuildingTimer(E);
}

void AGE_Frame::OnTTAgesBuildingSelect(wxCommandEvent &event)
{
    if(!ttAgeBuildingTimer.IsRunning())
        ttAgeBuildingTimer.Start(150);
}

void AGE_Frame::OnTTAgesBuildingTimer(wxTimerEvent&)
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
            BuildingPointer = &dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Buildings[TTAgeBuildIDs[loop]];
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
    AddToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Buildings);
    ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Buildings, TTAgeBuildIDs.front());
    ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingDelete(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Buildings, TTAgeBuildIDs);
    ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Buildings, TTAgeBuildIDs, copies.TTAgeBuild);
    TechTrees_Ages_Buildings.List->SetFocus();
}

void AGE_Frame::OnTTAgesBuildingPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Buildings, TTAgeBuildIDs, copies.TTAgeBuild);
    ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Buildings, TTAgeBuildIDs.front(), copies.TTAgeBuild);
    ListTTAgeBuildings();
}

void AGE_Frame::OnTTAgesBuildingCopyToAges(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTAgeIDs.size(); ++loop)
    {
        dataset->TechTree.TechTreeAges[TTAgeIDs[loop]].Buildings = dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Buildings;
    }
}

void AGE_Frame::OnTTAgesUnitSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTAgeUnits();
}

void AGE_Frame::ListTTAgeUnits()
{
    InitSearch(TechTrees_Ages_Units.Search->GetValue().MakeLower(), TechTrees_Ages_Units.SearchRecursive->GetValue().MakeLower());

    TechTrees_Ages_Units.List->names.clear();
    TechTrees_Ages_Units.List->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Units.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Units[loop]);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_Ages_Units.List->names.Add(Name);
            TechTrees_Ages_Units.List->indexes.push_back(loop);
        }
    }
    RefreshList(TechTrees_Ages_Units.List, &TTAgeUnitIDs);

    wxTimerEvent E;
    OnTTAgesUnitTimer(E);
}

void AGE_Frame::OnTTAgesUnitSelect(wxCommandEvent &event)
{
    if(!ttAgeUnitTimer.IsRunning())
        ttAgeUnitTimer.Start(150);
}

void AGE_Frame::OnTTAgesUnitTimer(wxTimerEvent&)
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
            UnitPointer = &dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Units[TTAgeUnitIDs[loop]];
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
    AddToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Units);
    ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Units, TTAgeUnitIDs.front());
    ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitDelete(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Units, TTAgeUnitIDs);
    ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Units, TTAgeUnitIDs, copies.TTAgeUnit);
    TechTrees_Ages_Units.List->SetFocus();
}

void AGE_Frame::OnTTAgesUnitPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Units, TTAgeUnitIDs, copies.TTAgeUnit);
    ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Units, TTAgeUnitIDs.front(), copies.TTAgeUnit);
    ListTTAgeUnits();
}

void AGE_Frame::OnTTAgesUnitCopyToAges(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTAgeIDs.size(); ++loop)
    {
        dataset->TechTree.TechTreeAges[TTAgeIDs[loop]].Units = dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Units;
    }
}

string AGE_Frame::GetSimpleResearchName(int Research)
{
    string Name = lexical_cast<string>(Research)+" ";
    if(dataset->Researchs.size() <= Research) return Name + "Nonexistent Research";
    if(!LangDLLstring(dataset->Researchs[Research].LanguageDLLName, 2).empty())
    {
        return Name + string(LangDLLstring(dataset->Researchs[Research].LanguageDLLName, 64));
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
    InitSearch(TechTrees_Ages_Researches.Search->GetValue().MakeLower(), TechTrees_Ages_Researches.SearchRecursive->GetValue().MakeLower());

    TechTrees_Ages_Researches.List->names.clear();
    TechTrees_Ages_Researches.List->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Researches.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetSimpleResearchName(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Researches[loop]);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_Ages_Researches.List->names.Add(Name);
            TechTrees_Ages_Researches.List->indexes.push_back(loop);
        }
    }
    RefreshList(TechTrees_Ages_Researches.List, &TTAgeResIDs);

    wxTimerEvent E;
    OnTTAgesResearchTimer(E);
}

void AGE_Frame::OnTTAgesResearchSelect(wxCommandEvent &event)
{
    if(!ttAgeResearchTimer.IsRunning())
        ttAgeResearchTimer.Start(150);
}

void AGE_Frame::OnTTAgesResearchTimer(wxTimerEvent&)
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
            ResearchPointer = &dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Researches[TTAgeResIDs[loop]];
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
    AddToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Researches);
    ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Researches, TTAgeResIDs.front());
    ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchDelete(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Researches, TTAgeResIDs);
    ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Researches, TTAgeResIDs, copies.TTAgeRes);
    TechTrees_Ages_Researches.List->SetFocus();
}

void AGE_Frame::OnTTAgesResearchPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Researches, TTAgeResIDs, copies.TTAgeRes);
    ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Researches, TTAgeResIDs.front(), copies.TTAgeRes);
    ListTTAgeResearches();
}

void AGE_Frame::OnTTAgesResearchCopyToAges(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTAgeIDs.size(); ++loop)
    {
        dataset->TechTree.TechTreeAges[TTAgeIDs[loop]].Researches = dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Researches;
    }
}

void AGE_Frame::OnTTAgeItemSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTAgeItems();
}

void AGE_Frame::ListTTAgeItems()
{
    ListTTCommonItems(TechTrees_Ages_Items, &dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Common);
    wxTimerEvent E;
    OnTTAgeItemTimer(E);
}

void AGE_Frame::SelectTTCommonItems(AGE_AreaTT84 &area, genie::techtree::Common *tt_cmn_ptr)
{
    wxBusyCursor WaitCursor;
    auto selections = area.List->GetSelectedItemCount();
    area.Item->clear();
    area.Mode->clear();
    if(selections > 0)
    {
        getSelectedItems(selections, area.List, TTItemIDs);

        int32_t *item_ptr;
        for(auto loop = selections; loop--> 0;)
        {
            item_ptr = &tt_cmn_ptr->Mode[TTItemIDs[loop]];
            area.Mode->prepend(item_ptr);
            area.Item->prepend(&tt_cmn_ptr->UnitResearch[TTItemIDs[loop]]);
        }

        int32_t mode = *item_ptr;
        bool mode_valid = true;
        switch(mode)
        {
            case 0:
                area.ItemCombo->SwapList(&age_names);
                break;
            case 1:
            case 2:
                area.ItemCombo->SwapList(&unit_names);
                break;
            case 3:
                area.ItemCombo->SwapList(&research_names);
                break;
            default:
                mode_valid = false;
                break;
        }
        area.ModeCombo->Show(mode_valid);
        area.ItemCombo->Show(mode_valid);
        area.ModeCombo->SetSelection(mode_valid ? mode : 0);
        area.ItemCombo->Flash();
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

void AGE_Frame::OnTTAgeItemTimer(wxTimerEvent&)
{
    ttAgeItemTimer.Stop();
    SelectTTCommonItems(TechTrees_Ages_Items, &dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Common);
}

void AGE_Frame::OnTTAgeItemCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Items.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Common.UnitResearch, TTItemIDs, copies.TTItem);
    CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Common.Mode, TTItemIDs, copies.TTMode);
    TechTrees_Ages_Items.List->SetFocus();
}

void AGE_Frame::OnTTAgeItemPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_Items.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Common.UnitResearch, TTItemIDs, copies.TTItem);
    PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Common.Mode, TTItemIDs, copies.TTMode);
    ListTTAgeItems();
}

void AGE_Frame::OnTTAgeItemCopyToAges(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTAgeIDs.size(); ++loop)
    {
        dataset->TechTree.TechTreeAges[TTAgeIDs[loop]].Common = dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Common;
    }
}

void AGE_Frame::OnTTAgeUnknownItemSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTAgeUnknownItems();
}

void AGE_Frame::ListTTAgeUnknownItems()
{
    InitSearch(TechTrees_Ages_UnknownItems.Search->GetValue().MakeLower(), TechTrees_Ages_UnknownItems.SearchRecursive->GetValue().MakeLower());

    TechTrees_Ages_UnknownItems.List->names.clear();
    TechTrees_Ages_UnknownItems.List->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.TechTreeAges[TTAgeIDs.front()].getU4Size(); ++loop)
    {
        wxString Name = " "+lexical_cast<string>((short)dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Unknown4[loop]);
        Name += " - "+lexical_cast<string>((short)dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Unknown5[loop]);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_Ages_UnknownItems.List->names.Add(Name);
            TechTrees_Ages_UnknownItems.List->indexes.push_back(loop);
        }
    }
    RefreshList(TechTrees_Ages_UnknownItems.List, &TTUnknownItemIDs);

    wxTimerEvent E;
    OnTTAgeUnknownItemTimer(E);
}

void AGE_Frame::OnTTAgeUnknownItemSelect(wxCommandEvent &event)
{
    if(!ttAgeUnknownTimer.IsRunning())
        ttAgeUnknownTimer.Start(150);
}

void AGE_Frame::OnTTAgeUnknownItemTimer(wxTimerEvent&)
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
        genie::TechTreeAge* agePointer = &dataset->TechTree.TechTreeAges[TTAgeIDs.front()];
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
    CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Unknown4, TTUnknownItemIDs, copies.TTUnknown4);
    CopyFromList(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Unknown5, TTUnknownItemIDs, copies.TTUnknown5);
    TechTrees_Ages_UnknownItems.List->SetFocus();
}

void AGE_Frame::OnTTAgeUnknownItemPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Ages_UnknownItems.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Unknown4, TTUnknownItemIDs, copies.TTUnknown4);
    PasteToListNoGV(dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Unknown5, TTUnknownItemIDs, copies.TTUnknown5);
    ListTTAgeUnknownItems();
}

void AGE_Frame::OnTTAgeUnknownItemCopyToAges(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTAgeIDs.size(); ++loop)
    {
        dataset->TechTree.TechTreeAges[TTAgeIDs[loop]].Unknown4 = dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Unknown4;
        dataset->TechTree.TechTreeAges[TTAgeIDs[loop]].Unknown5 = dataset->TechTree.TechTreeAges[TTAgeIDs.front()].Unknown5;
    }
}

string AGE_Frame::GetTTBuildingName(int index)
{
    string Name = "";

    short Selection[2];
    for(size_t loop = 0; loop < 2; ++loop)
    Selection[loop] = TechTrees_MainList_Buildings_SearchFilters[loop]->GetSelection();

    if(Selection[0] == 0)   // Normal Name
    {
        // Do nothing!
    }
    else for(size_t loop = 0; loop < 2; ++loop)
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
    if(dataset->Civs.front().Units.size() <= dataset->TechTree.BuildingConnections[index].ID) return Name;
    if(!LangDLLstring(dataset->Civs.front().Units[dataset->TechTree.BuildingConnections[index].ID].LanguageDLLName, 2).empty())
    {
        Name += string(LangDLLstring(dataset->Civs.front().Units[dataset->TechTree.BuildingConnections[index].ID].LanguageDLLName, 64));
    }
    else if(!dataset->Civs.front().Units[dataset->TechTree.BuildingConnections[index].ID].Name.empty())
    {
        Name += dataset->Civs.front().Units[dataset->TechTree.BuildingConnections[index].ID].Name;
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
    InitSearch(TechTrees_MainList_Buildings_Search->GetValue().MakeLower(), TechTrees_MainList_Buildings_Search_R->GetValue().MakeLower());
    SearchAnd = TechTrees_MainList_Buildings_UseAnd[0]->GetValue();
    ExcludeAnd = TechTrees_MainList_Buildings_UseAnd[1]->GetValue();

    TechTrees_MainList_Buildings_ListV->names.clear();
    TechTrees_MainList_Buildings_ListV->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.BuildingConnections.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetTTBuildingName(loop);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_MainList_Buildings_ListV->names.Add(Name);
            TechTrees_MainList_Buildings_ListV->indexes.push_back(loop);
        }
    }

    RefreshList(TechTrees_MainList_Buildings_ListV, &TTBuildConIDs);

    SearchAnd = ExcludeAnd = false;
}

void AGE_Frame::OnTTBuildingSelect(wxCommandEvent &event)
{
    if(!ttBuildingTimer.IsRunning())
        ttBuildingTimer.Start(150);
}

void AGE_Frame::OnTTBuildingTimer(wxTimerEvent&)
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
        for(size_t loop = 0; loop < 5; ++loop)
        {
            TechTrees_Buildings_TotalUnitsTechs[loop]->prepend(&BuildingConPointer->UnitsTechsTotal[loop]);
            TechTrees_Buildings_TotalUnitsTechs[loop+5]->prepend(&BuildingConPointer->UnitsTechsFirst[loop]);
        }
    }
    SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected building: "+lexical_cast<string>(TTBuildConIDs.front()), 0);

    for(auto &box: uiGroupTTBuilding) box->update();
    TechTrees_Buildings_Items.UsedItems->update();

    ListTTBuildingBuildings();
    ListTTBuildingUnits();
    ListTTBuildingResearches();
    ListTTBuildingItems();
}

void AGE_Frame::OnTTBuildingAdd(wxCommandEvent &event)
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->TechTree.BuildingConnections);
    ListTTBuildings();
}

void AGE_Frame::OnTTBuildingInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_MainList_Buildings_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->TechTree.BuildingConnections, TTBuildConIDs.front());
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
    PasteToList(dataset->TechTree.BuildingConnections, TTBuildConIDs, copies.TTBuildCon);
    ListTTBuildings();
}

void AGE_Frame::OnTTBuildingPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_MainList_Buildings_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->TechTree.BuildingConnections, TTBuildConIDs.front(), copies.TTBuildCon);
    ListTTBuildings();
}

void AGE_Frame::OnTTBuildingBuildingSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTBuildingBuildings();
}

void AGE_Frame::ListTTBuildingBuildings()
{
    InitSearch(TechTrees_Buildings_Buildings.Search->GetValue().MakeLower(), TechTrees_Buildings_Buildings.SearchRecursive->GetValue().MakeLower());

    TechTrees_Buildings_Buildings.List->names.clear();
    TechTrees_Buildings_Buildings.List->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Buildings.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetBuildingName(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Buildings[loop]);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_Buildings_Buildings.List->names.Add(Name);
            TechTrees_Buildings_Buildings.List->indexes.push_back(loop);
        }
    }
    RefreshList(TechTrees_Buildings_Buildings.List, &TTBuildBuildIDs);

    wxTimerEvent E;
    OnTTBuildingBuildingTimer(E);
}

void AGE_Frame::OnTTBuildingBuildingSelect(wxCommandEvent &event)
{
    if(!ttBuildingBuildingTimer.IsRunning())
        ttBuildingBuildingTimer.Start(150);
}

void AGE_Frame::OnTTBuildingBuildingTimer(wxTimerEvent&)
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
            BuildingPointer = &dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Buildings[TTBuildBuildIDs[loop]];
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
    AddToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Buildings);
    ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Buildings, TTBuildBuildIDs.front());
    ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingDelete(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Buildings, TTBuildBuildIDs);
    ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Buildings, TTBuildBuildIDs, copies.TTBuildBuild);
    TechTrees_Buildings_Buildings.List->SetFocus();
}

void AGE_Frame::OnTTBuildingBuildingPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Buildings, TTBuildBuildIDs, copies.TTBuildBuild);
    ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Buildings, TTBuildBuildIDs.front(), copies.TTBuildBuild);
    ListTTBuildingBuildings();
}

void AGE_Frame::OnTTBuildingBuildingCopyToBuildings(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTBuildConIDs.size(); ++loop)
    {
        dataset->TechTree.BuildingConnections[TTBuildConIDs[loop]].Buildings = dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Buildings;
    }
}

void AGE_Frame::OnTTBuildingUnitSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTBuildingUnits();
}

void AGE_Frame::ListTTBuildingUnits()
{
    InitSearch(TechTrees_Buildings_Units.Search->GetValue().MakeLower(), TechTrees_Buildings_Units.SearchRecursive->GetValue().MakeLower());

    TechTrees_Buildings_Units.List->names.clear();
    TechTrees_Buildings_Units.List->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Units.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Units[loop]);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_Buildings_Units.List->names.Add(Name);
            TechTrees_Buildings_Units.List->indexes.push_back(loop);
        }
    }
    RefreshList(TechTrees_Buildings_Units.List, &TTBuildUnitIDs);

    wxTimerEvent E;
    OnTTBuildingUnitTimer(E);
}

void AGE_Frame::OnTTBuildingUnitSelect(wxCommandEvent &event)
{
    if(!ttBuildingUnitTimer.IsRunning())
        ttBuildingUnitTimer.Start(150);
}

void AGE_Frame::OnTTBuildingUnitTimer(wxTimerEvent&)
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
            UnitPointer = &dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Units[TTBuildUnitIDs[loop]];
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
    AddToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Units);
    ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Units, TTBuildUnitIDs.front());
    ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitDelete(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Units, TTBuildUnitIDs);
    ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Units, TTBuildUnitIDs, copies.TTBuildUnit);
    TechTrees_Buildings_Units.List->SetFocus();
}

void AGE_Frame::OnTTBuildingUnitPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Units, TTBuildUnitIDs, copies.TTBuildUnit);
    ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Units, TTBuildUnitIDs.front(), copies.TTBuildUnit);
    ListTTBuildingUnits();
}

void AGE_Frame::OnTTBuildingUnitCopyToBuildings(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTBuildConIDs.size(); ++loop)
    {
        dataset->TechTree.BuildingConnections[TTBuildConIDs[loop]].Units = dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Units;
    }
}

void AGE_Frame::OnTTBuildingResearchSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTBuildingResearches();
}

void AGE_Frame::ListTTBuildingResearches()
{
    InitSearch(TechTrees_Buildings_Researches.Search->GetValue().MakeLower(), TechTrees_Buildings_Researches.SearchRecursive->GetValue().MakeLower());

    TechTrees_Buildings_Researches.List->names.clear();
    TechTrees_Buildings_Researches.List->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Researches.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetSimpleResearchName(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Researches[loop]);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_Buildings_Researches.List->names.Add(Name);
            TechTrees_Buildings_Researches.List->indexes.push_back(loop);
        }
    }
    RefreshList(TechTrees_Buildings_Researches.List, &TTBuildResIDs);

    wxTimerEvent E;
    OnTTBuildingResearchTimer(E);
}

void AGE_Frame::OnTTBuildingResearchSelect(wxCommandEvent &event)
{
    if(!ttBuildingResearchTimer.IsRunning())
        ttBuildingResearchTimer.Start(150);
}

void AGE_Frame::OnTTBuildingResearchTimer(wxTimerEvent&)
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
            ResearchPointer = &dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Researches[TTBuildResIDs[loop]];
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
    AddToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Researches);
    ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Researches, TTBuildResIDs.front());
    ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchDelete(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Researches, TTBuildResIDs);
    ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Researches, TTBuildResIDs, copies.TTBuildRes);
    TechTrees_Buildings_Researches.List->SetFocus();
}

void AGE_Frame::OnTTBuildingResearchPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Researches, TTBuildResIDs, copies.TTBuildRes);
    ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Researches, TTBuildResIDs.front(), copies.TTBuildRes);
    ListTTBuildingResearches();
}

void AGE_Frame::OnTTBuildingResearchCopyToBuildings(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTBuildConIDs.size(); ++loop)
    {
        dataset->TechTree.BuildingConnections[TTBuildConIDs[loop]].Researches = dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Researches;
    }
}

void AGE_Frame::OnTTBuildingItemSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTBuildingItems();
}

void AGE_Frame::ListTTBuildingItems()
{
    ListTTCommonItems(TechTrees_Buildings_Items, &dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Common);
    wxTimerEvent E;
    OnTTBuildingItemTimer(E);
}

void AGE_Frame::OnTTBuildingItemSelect(wxCommandEvent &event)
{
    if(!ttBuildingItemTimer.IsRunning())
        ttBuildingItemTimer.Start(150);
}

void AGE_Frame::OnTTBuildingItemTimer(wxTimerEvent&)
{
    ttBuildingItemTimer.Stop();
    SelectTTCommonItems(TechTrees_Buildings_Items, &dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Common);
}

void AGE_Frame::OnTTBuildingItemCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Items.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Common.UnitResearch, TTItemIDs, copies.TTItem);
    CopyFromList(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Common.Mode, TTItemIDs, copies.TTMode);
    TechTrees_Buildings_Items.List->SetFocus();
}

void AGE_Frame::OnTTBuildingItemPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Buildings_Items.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Common.UnitResearch, TTItemIDs, copies.TTItem);
    PasteToListNoGV(dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Common.Mode, TTItemIDs, copies.TTMode);
    ListTTBuildingItems();
}

void AGE_Frame::OnTTBuildingItemCopyToBuildings(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTBuildConIDs.size(); ++loop)
    {
        dataset->TechTree.BuildingConnections[TTBuildConIDs[loop]].Common = dataset->TechTree.BuildingConnections[TTBuildConIDs.front()].Common;
    }
}

string AGE_Frame::GetTTUnitName(int index)
{
    string Name = "";

    short Selection[2];
    for(size_t loop = 0; loop < 2; ++loop)
    Selection[loop] = TechTrees_MainList_Units_SearchFilters[loop]->GetSelection();

    if(Selection[0] == 0)   // Normal Name
    {
        // Do nothing!
    }
    else for(size_t loop = 0; loop < 2; ++loop)
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
    if(dataset->Civs.front().Units.size() <= dataset->TechTree.UnitConnections[index].ID) return Name;
    if(!LangDLLstring(dataset->Civs.front().Units[dataset->TechTree.UnitConnections[index].ID].LanguageDLLName, 2).empty())
    {
        Name += string(LangDLLstring(dataset->Civs.front().Units[dataset->TechTree.UnitConnections[index].ID].LanguageDLLName, 64));
    }
    else if(!dataset->Civs.front().Units[dataset->TechTree.UnitConnections[index].ID].Name.empty())
    {
        Name += dataset->Civs.front().Units[dataset->TechTree.UnitConnections[index].ID].Name;
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
    InitSearch(TechTrees_MainList_Units_Search->GetValue().MakeLower(), TechTrees_MainList_Units_Search_R->GetValue().MakeLower());
    SearchAnd = TechTrees_MainList_Units_UseAnd[0]->GetValue();
    ExcludeAnd = TechTrees_MainList_Units_UseAnd[1]->GetValue();

    TechTrees_MainList_Units_ListV->names.clear();
    TechTrees_MainList_Units_ListV->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.UnitConnections.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetTTUnitName(loop);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_MainList_Units_ListV->names.Add(Name);
            TechTrees_MainList_Units_ListV->indexes.push_back(loop);
        }
    }

    RefreshList(TechTrees_MainList_Units_ListV, &TTUnitConIDs);

    SearchAnd = ExcludeAnd = false;
}

void AGE_Frame::OnTTUnitSelect(wxCommandEvent &event)
{
    if(!ttUnitTimer.IsRunning())
        ttUnitTimer.Start(150);
}

void AGE_Frame::OnTTUnitTimer(wxTimerEvent&)
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
    SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected unit: "+lexical_cast<string>(TTUnitConIDs.front()), 0);

    for(auto &box: uiGroupTTUnit) box->update();
    TechTrees_Units_Items.UsedItems->update();

    ListTTUnitUnits();
    ListTTUnitItems();
}

void AGE_Frame::OnTTUnitAdd(wxCommandEvent &event)
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->TechTree.UnitConnections);
    ListTTUnits();
}

void AGE_Frame::OnTTUnitInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_MainList_Units_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->TechTree.UnitConnections, TTUnitConIDs.front());
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
    PasteToList(dataset->TechTree.UnitConnections, TTUnitConIDs, copies.TTUnitCon);
    ListTTUnits();
}

void AGE_Frame::OnTTUnitPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_MainList_Units_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->TechTree.UnitConnections, TTUnitConIDs.front(), copies.TTUnitCon);
    ListTTUnits();
}

void AGE_Frame::OnTTUnitUnitSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTUnitUnits();
}

void AGE_Frame::ListTTUnitUnits()
{
    InitSearch(TechTrees_Units_Units.Search->GetValue().MakeLower(), TechTrees_Units_Units.SearchRecursive->GetValue().MakeLower());

    TechTrees_Units_Units.List->names.clear();
    TechTrees_Units_Units.List->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Units.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Units[loop]);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_Units_Units.List->names.Add(Name);
            TechTrees_Units_Units.List->indexes.push_back(loop);
        }
    }
    RefreshList(TechTrees_Units_Units.List, &TTUnitUnitIDs);

    wxTimerEvent E;
    OnTTUnitUnitTimer(E);
}

void AGE_Frame::OnTTUnitUnitSelect(wxCommandEvent &event)
{
    if(!ttUnitUnitTimer.IsRunning())
        ttUnitUnitTimer.Start(150);
}

void AGE_Frame::OnTTUnitUnitTimer(wxTimerEvent&)
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
            UnitPointer = &dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Units[TTUnitUnitIDs[loop]];
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
    AddToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Units);
    ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Units_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Units, TTUnitUnitIDs.front());
    ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitDelete(wxCommandEvent &event)
{
    auto selections = TechTrees_Units_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Units, TTUnitUnitIDs);
    ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Units_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Units, TTUnitUnitIDs, copies.TTUnitUnit);
    TechTrees_Units_Units.List->SetFocus();
}

void AGE_Frame::OnTTUnitUnitPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Units_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Units, TTUnitUnitIDs, copies.TTUnitUnit);
    ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Units_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Units, TTUnitUnitIDs.front(), copies.TTUnitUnit);
    ListTTUnitUnits();
}

void AGE_Frame::OnTTUnitUnitCopyToUnits(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTUnitConIDs.size(); ++loop)
    {
        dataset->TechTree.UnitConnections[TTUnitConIDs[loop]].Units = dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Units;
    }
}

void AGE_Frame::ListTTCommonItems(AGE_AreaTT84 &area, genie::techtree::Common *tt_cmn_ptr)
{
    InitSearch(area.Search->GetValue().MakeLower(), area.SearchRecursive->GetValue().MakeLower());

    area.List->names.clear();
    area.List->indexes.clear();

    for(size_t loop = 0; loop < tt_cmn_ptr->getSlots(); ++loop)
    {
        wxString Name = " ";
        switch(tt_cmn_ptr->Mode[loop])
        {
            case 0:
                Name += "Age: "+lexical_cast<string>(tt_cmn_ptr->UnitResearch[loop]);
                break;
            case 1:
                Name += "Building: "+GetBuildingName(tt_cmn_ptr->UnitResearch[loop]);
                break;
            case 2:
                Name += "Unit: "+GetBuildingName(tt_cmn_ptr->UnitResearch[loop]);
                break;
            case 3:
                Name += "Research: "+GetSimpleResearchName(tt_cmn_ptr->UnitResearch[loop]);
                break;
            default:
                Name += lexical_cast<string>(tt_cmn_ptr->Mode[loop])+" None: "+lexical_cast<string>(tt_cmn_ptr->UnitResearch[loop]);
        }
        if(SearchMatches(Name.Lower()))
        {
            area.List->names.Add(Name);
            area.List->indexes.push_back(loop);
        }
    }
    RefreshList(area.List, &TTItemIDs);
}

void AGE_Frame::OnTTUnitItemSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTUnitItems();
}

void AGE_Frame::ListTTUnitItems()
{
    ListTTCommonItems(TechTrees_Units_Items, &dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Common);
    wxTimerEvent E;
    OnTTUnitItemTimer(E);
}

void AGE_Frame::OnTTUnitItemSelect(wxCommandEvent &event)
{
    if(!ttUnitItemTimer.IsRunning())
        ttUnitItemTimer.Start(150);
}

void AGE_Frame::OnTTUnitItemTimer(wxTimerEvent&)
{
    ttUnitItemTimer.Stop();
    SelectTTCommonItems(TechTrees_Units_Items, &dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Common);
}

void AGE_Frame::OnTTUnitItemCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Units_Items.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Common.UnitResearch, TTItemIDs, copies.TTItem);
    CopyFromList(dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Common.Mode, TTItemIDs, copies.TTMode);
    TechTrees_Units_Items.List->SetFocus();
}

void AGE_Frame::OnTTUnitItemPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Units_Items.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Common.UnitResearch, TTItemIDs, copies.TTItem);
    PasteToListNoGV(dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Common.Mode, TTItemIDs, copies.TTMode);
    ListTTUnitItems();
}

void AGE_Frame::OnTTUnitItemCopyToUnits(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTUnitConIDs.size(); ++loop)
    {
        dataset->TechTree.UnitConnections[TTUnitConIDs[loop]].Common = dataset->TechTree.UnitConnections[TTUnitConIDs.front()].Common;
    }
}

string AGE_Frame::GetTTResearchName(int index)
{
    string Name = "";

    short Selection[2];
    for(size_t loop = 0; loop < 2; ++loop)
    Selection[loop] = TechTrees_MainList_Researches_SearchFilters[loop]->GetSelection();

    if(Selection[0] == 0)   // Normal Name
    {
        // Do nothing!
    }
    else for(size_t loop = 0; loop < 2; ++loop)
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
        Name += string(LangDLLstring(dataset->Researchs[dataset->TechTree.ResearchConnections[index].ID].LanguageDLLName, 64));
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
    InitSearch(TechTrees_MainList_Researches_Search->GetValue().MakeLower(), TechTrees_MainList_Researches_Search_R->GetValue().MakeLower());
    SearchAnd = TechTrees_MainList_Researches_UseAnd[0]->GetValue();
    ExcludeAnd = TechTrees_MainList_Researches_UseAnd[1]->GetValue();

    TechTrees_MainList_Researches_ListV->names.clear();
    TechTrees_MainList_Researches_ListV->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.ResearchConnections.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetTTResearchName(loop);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_MainList_Researches_ListV->names.Add(Name);
            TechTrees_MainList_Researches_ListV->indexes.push_back(loop);
        }
    }

    RefreshList(TechTrees_MainList_Researches_ListV, &TTResConIDs);

    SearchAnd = ExcludeAnd = false;
}

void AGE_Frame::OnTTResearchSelect(wxCommandEvent &event)
{
    if(!ttResearchTimer.IsRunning())
        ttResearchTimer.Start(150);
}

void AGE_Frame::OnTTResearchTimer(wxTimerEvent&)
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
    SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected research: "+lexical_cast<string>(TTResConIDs.front()), 0);

    for(auto &box: uiGroupTTResearch) box->update();
    TechTrees_Researches_Items.UsedItems->update();

    ListTTResearchBuildings();
    ListTTResearchUnits();
    ListTTResearchResearches();
    ListTTResearchItems();
}

void AGE_Frame::OnTTResearchAdd(wxCommandEvent &event)
{
    if(!dataset) return;

    wxBusyCursor WaitCursor;
    AddToList(dataset->TechTree.ResearchConnections);
    ListTTResearches();
}

void AGE_Frame::OnTTResearchInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_MainList_Researches_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToList(dataset->TechTree.ResearchConnections, TTResConIDs.front());
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
    PasteToList(dataset->TechTree.ResearchConnections, TTResConIDs, copies.TTResCon);
    ListTTResearches();
}

void AGE_Frame::OnTTResearchPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_MainList_Researches_ListV->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToList(dataset->TechTree.ResearchConnections, TTResConIDs.front(), copies.TTResCon);
    ListTTResearches();
}

void AGE_Frame::OnTTResearchBuildingSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTResearchBuildings();
}

void AGE_Frame::ListTTResearchBuildings()
{
    InitSearch(TechTrees_Researches_Buildings.Search->GetValue().MakeLower(), TechTrees_Researches_Buildings.SearchRecursive->GetValue().MakeLower());

    TechTrees_Researches_Buildings.List->names.clear();
    TechTrees_Researches_Buildings.List->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.ResearchConnections[TTResConIDs.front()].Buildings.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetBuildingName(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Buildings[loop]);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_Researches_Buildings.List->names.Add(Name);
            TechTrees_Researches_Buildings.List->indexes.push_back(loop);
        }
    }
    RefreshList(TechTrees_Researches_Buildings.List, &TTResBuildIDs);

    wxTimerEvent E;
    OnTTResearchBuildingTimer(E);
}

void AGE_Frame::OnTTResearchBuildingSelect(wxCommandEvent &event)
{
    if(!ttResearchBuildingTimer.IsRunning())
        ttResearchBuildingTimer.Start(150);
}

void AGE_Frame::OnTTResearchBuildingTimer(wxTimerEvent&)
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
            BuildingPointer = &dataset->TechTree.ResearchConnections[TTResConIDs.front()].Buildings[TTResBuildIDs[loop]];
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
    AddToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Buildings);
    ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Buildings, TTResBuildIDs.front());
    ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingDelete(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Buildings, TTResBuildIDs);
    ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Buildings, TTResBuildIDs, copies.TTResBuild);
    TechTrees_Researches_Buildings.List->SetFocus();
}

void AGE_Frame::OnTTResearchBuildingPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Buildings, TTResBuildIDs, copies.TTResBuild);
    ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Buildings.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Buildings, TTResBuildIDs.front(), copies.TTResBuild);
    ListTTResearchBuildings();
}

void AGE_Frame::OnTTResearchBuildingCopyToResearches(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTResConIDs.size(); ++loop)
    {
        dataset->TechTree.ResearchConnections[TTResConIDs[loop]].Buildings = dataset->TechTree.ResearchConnections[TTResConIDs.front()].Buildings;
    }
}

void AGE_Frame::OnTTResearchUnitSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTResearchUnits();
}

void AGE_Frame::ListTTResearchUnits()
{
    InitSearch(TechTrees_Researches_Units.Search->GetValue().MakeLower(), TechTrees_Researches_Units.SearchRecursive->GetValue().MakeLower());

    TechTrees_Researches_Units.List->names.clear();
    TechTrees_Researches_Units.List->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.ResearchConnections[TTResConIDs.front()].Units.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Units[loop]);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_Researches_Units.List->names.Add(Name);
            TechTrees_Researches_Units.List->indexes.push_back(loop);
        }
    }
    RefreshList(TechTrees_Researches_Units.List, &TTResUnitIDs);

    wxTimerEvent E;
    OnTTResearchUnitTimer(E);
}

void AGE_Frame::OnTTResearchUnitSelect(wxCommandEvent &event)
{
    if(!ttResearchUnitTimer.IsRunning())
        ttResearchUnitTimer.Start(150);
}

void AGE_Frame::OnTTResearchUnitTimer(wxTimerEvent&)
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
            UnitPointer = &dataset->TechTree.ResearchConnections[TTResConIDs.front()].Units[TTResUnitIDs[loop]];
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
    AddToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Units);
    ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Units, TTResUnitIDs.front());
    ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitDelete(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Units, TTResUnitIDs);
    ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Units, TTResUnitIDs, copies.TTResUnit);
    TechTrees_Researches_Units.List->SetFocus();
}

void AGE_Frame::OnTTResearchUnitPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Units, TTResUnitIDs, copies.TTResUnit);
    ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Units.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Units, TTResUnitIDs.front(), copies.TTResUnit);
    ListTTResearchUnits();
}

void AGE_Frame::OnTTResearchUnitCopyToResearches(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTResConIDs.size(); ++loop)
    {
        dataset->TechTree.ResearchConnections[TTResConIDs[loop]].Units = dataset->TechTree.ResearchConnections[TTResConIDs.front()].Units;
    }
}

void AGE_Frame::OnTTResearchResearchSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTResearchResearches();
}

void AGE_Frame::ListTTResearchResearches()
{
    InitSearch(TechTrees_Researches_Researches.Search->GetValue().MakeLower(), TechTrees_Researches_Researches.SearchRecursive->GetValue().MakeLower());

    TechTrees_Researches_Researches.List->names.clear();
    TechTrees_Researches_Researches.List->indexes.clear();

    for(size_t loop = 0; loop < dataset->TechTree.ResearchConnections[TTResConIDs.front()].Researches.size(); ++loop)
    {
        wxString Name = " "+FormatInt(loop)+" - "+GetSimpleResearchName(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Researches[loop]);
        if(SearchMatches(Name.Lower()))
        {
            TechTrees_Researches_Researches.List->names.Add(Name);
            TechTrees_Researches_Researches.List->indexes.push_back(loop);
        }
    }
    RefreshList(TechTrees_Researches_Researches.List, &TTResResIDs);

    wxTimerEvent E;
    OnTTResearchResearchTimer(E);
}

void AGE_Frame::OnTTResearchResearchSelect(wxCommandEvent &event)
{
    if(!ttResearchResearchTimer.IsRunning())
        ttResearchResearchTimer.Start(150);
}

void AGE_Frame::OnTTResearchResearchTimer(wxTimerEvent&)
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
            ResearchPointer = &dataset->TechTree.ResearchConnections[TTResConIDs.front()].Researches[TTResResIDs[loop]];
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
    AddToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Researches);
    ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    InsertToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Researches, TTResResIDs.front());
    ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchDelete(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    DeleteFromList(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Researches, TTResResIDs);
    ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Researches, TTResResIDs, copies.TTResRes);
    TechTrees_Researches_Researches.List->SetFocus();
}

void AGE_Frame::OnTTResearchResearchPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Researches, TTResResIDs, copies.TTResRes);
    ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchPasteInsert(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Researches.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteInsertToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Researches, TTResResIDs.front(), copies.TTResRes);
    ListTTResearchResearches();
}

void AGE_Frame::OnTTResearchResearchCopyToResearches(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTResConIDs.size(); ++loop)
    {
        dataset->TechTree.ResearchConnections[TTResConIDs[loop]].Researches = dataset->TechTree.ResearchConnections[TTResConIDs.front()].Researches;
    }
}

void AGE_Frame::OnTTResearchItemSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListTTResearchItems();
}

void AGE_Frame::ListTTResearchItems()
{
    ListTTCommonItems(TechTrees_Researches_Items, &dataset->TechTree.ResearchConnections[TTResConIDs.front()].Common);
    wxTimerEvent E;
    OnTTResearchItemTimer(E);
}

void AGE_Frame::OnTTResearchItemSelect(wxCommandEvent &event)
{
    if(!ttResearchItemTimer.IsRunning())
        ttResearchItemTimer.Start(150);
}

void AGE_Frame::OnTTResearchItemTimer(wxTimerEvent&)
{
    ttResearchItemTimer.Stop();
    SelectTTCommonItems(TechTrees_Researches_Items, &dataset->TechTree.ResearchConnections[TTResConIDs.front()].Common);
}

void AGE_Frame::OnTTResearchItemCopy(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Items.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    CopyFromList(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Common.UnitResearch, TTItemIDs, copies.TTItem);
    CopyFromList(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Common.Mode, TTItemIDs, copies.TTMode);
    TechTrees_Researches_Items.List->SetFocus();
}

void AGE_Frame::OnTTResearchItemPaste(wxCommandEvent &event)
{
    auto selections = TechTrees_Researches_Items.List->GetSelectedItemCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Common.UnitResearch, TTItemIDs, copies.TTItem);
    PasteToListNoGV(dataset->TechTree.ResearchConnections[TTResConIDs.front()].Common.Mode, TTItemIDs, copies.TTMode);
    ListTTResearchItems();
}

void AGE_Frame::OnTTResearchItemCopyToResearches(wxCommandEvent &event)
{
    for(size_t loop=1; loop < TTResConIDs.size(); ++loop)
    {
        dataset->TechTree.ResearchConnections[TTResConIDs[loop]].Common = dataset->TechTree.ResearchConnections[TTResConIDs.front()].Common;
    }
}

void AGE_Frame::CreateTechTreeControls()
{
    Tab_TechTrees = new APanel(TabBar_Main);

    TechTrees_Main = new wxBoxSizer(wxVERTICAL);
    TabBar_TechTree = new wxNotebook(Tab_TechTrees, wxID_ANY);
    Tab_TechTreeAges = new APanel(TabBar_TechTree);
    Tab_TechTreeBuildings = new APanel(TabBar_TechTree);
    Tab_TechTreeUnits = new APanel(TabBar_TechTree);
    Tab_TechTreeResearches = new APanel(TabBar_TechTree);
    TechTrees_TabAges = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_TabBuildings = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_TabUnits = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_TabResearches = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_ScrollerAges = new wxScrolled<APanel>(Tab_TechTreeAges, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
    TechTrees_ScrollerBuildings = new wxScrolled<APanel>(Tab_TechTreeBuildings, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
    TechTrees_ScrollerUnits = new wxScrolled<APanel>(Tab_TechTreeUnits, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
    TechTrees_ScrollerResearches = new wxScrolled<APanel>(Tab_TechTreeResearches, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);

    mode_names.Add("Age");
    mode_names.Add("Building");
    mode_names.Add("Unit");
    mode_names.Add("Research");

    wxString StatusHelp = "0 generic\n1 ?\n2 default\n3 marks this as not available\n4 upgrading or constructing or creating\n5 research completed or building built";
    wxString LocationInAgeHelp = "0 Hidden\n1 First\n2 Second";
    wxString LineModeHelp = "0 research: First age\n1 age: ?\n2 unit: First in vertical line\n3 unit: Not first\n4 research: Others\n5 building: One or more connections\n6 building: No connections";

    General_Variables2_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Tab_TechTrees, "Technology Tree Related");
    for(size_t loop = 0; loop < General_TTUnknown.size(); ++loop)
    {
        General_TTUnknown_Holder[loop] = new wxBoxSizer(wxVERTICAL);
        General_TTUnknown_Text[loop] = new SolidText(Tab_TechTrees, " Unknown "+lexical_cast<string>(loop+1));
        General_TTUnknown[loop] = AGETextCtrl::init(CLong, &uiGroupMaps, this, &popUp, Tab_TechTrees);
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
    TechTrees_MainList_Ages_Add = new wxButton(Tab_TechTreeAges, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Ages_Insert = new wxButton(Tab_TechTreeAges, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Ages_Delete = new wxButton(Tab_TechTreeAges, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Ages_Copy = new wxButton(Tab_TechTreeAges, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Ages_Paste = new wxButton(Tab_TechTreeAges, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Ages_PasteInsert = new wxButton(Tab_TechTreeAges, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));

    TechTrees_Ages_ID_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Ages_ID_Text = new SolidText(TechTrees_ScrollerAges, " Age Number");
    TechTrees_Ages_ID = AGETextCtrl::init(CLong, &uiGroupTTAge, this, &popUp, TechTrees_ScrollerAges);
    TechTrees_Ages_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Ages_Unknown2_Text = new SolidText(TechTrees_ScrollerAges, " Status *");
    TechTrees_Ages_Unknown2 = AGETextCtrl::init(CByte, &uiGroupTTAge, this, &popUp, TechTrees_ScrollerAges);
    TechTrees_Ages_Unknown2->SetToolTip(StatusHelp);

    TechTrees_Ages_LineMode_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Ages_LineMode_Text = new SolidText(TechTrees_ScrollerAges, " Line Mode *");
    TechTrees_Ages_LineMode = AGETextCtrl::init(CLong, &uiGroupTTAge, this, &popUp, TechTrees_ScrollerAges);
    TechTrees_Ages_LineMode->SetToolTip(LineModeHelp);
    TechTrees_Data_Ages = new wxBoxSizer(wxVERTICAL);
    TechTrees_Data_Ages2 = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_Data_Ages1 = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_ConnectedHolder_Ages = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_Ages_Buildings.CreateControls(this, &popUp, TechTrees_ScrollerAges, "ages", "Connected Buildings", &unit_names);
    UnitComboBoxList.push_back(TechTrees_Ages_Buildings.ItemCombo);
    TechTrees_Ages_Units.CreateControls(this, &popUp, TechTrees_ScrollerAges, "ages", "Connected Units", &unit_names);
    UnitComboBoxList.push_back(TechTrees_Ages_Units.ItemCombo);
    TechTrees_Ages_Researches.CreateControls(this, &popUp, TechTrees_ScrollerAges, "ages", "Connected Researches", &research_names);
    ResearchComboBoxList.push_back(TechTrees_Ages_Researches.ItemCombo);

    TechTrees_Ages_Items.CreateControls(this, &popUp, TechTrees_ScrollerAges, "ages", &mode_names);
    TechTrees_Ages_UnknownItems.CreateControls(this, &popUp, TechTrees_ScrollerAges);

    TechTrees_MainList_Buildings_Search = new wxTextCtrl(Tab_TechTreeBuildings, wxID_ANY);
    TechTrees_MainList_Buildings_UseAnd[0] = new wxCheckBox(Tab_TechTreeBuildings, wxID_ANY, "And");
    TechTrees_MainList_Buildings_Search_R = new wxTextCtrl(Tab_TechTreeBuildings, wxID_ANY);
    TechTrees_MainList_Buildings_UseAnd[1] = new wxCheckBox(Tab_TechTreeBuildings, wxID_ANY, "And");
    for(size_t loop = 0; loop < 2; ++loop)
    {
        TechTrees_MainList_Buildings_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
        TechTrees_MainList_Buildings_SearchFilters[loop] = new AGEComboBox(Tab_TechTreeBuildings, &tt_building_filters);
    }
    TechTrees_MainList_Buildings_ListV = new AGEListView(Tab_TechTreeBuildings, wxSize(200, 300));
    TechTrees_MainList_Buildings_Buttons = new wxGridSizer(3, 0, 0);
    TechTrees_MainList_Buildings_Add = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Buildings_Insert = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Buildings_Delete = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Buildings_Copy = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Buildings_Paste = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Buildings_PasteInsert = new wxButton(Tab_TechTreeBuildings, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));

    TechTrees_Buildings_ID_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Buildings_ID_Text = new SolidText(TechTrees_ScrollerBuildings, " Building Number");
    TechTrees_Buildings_ID = AGETextCtrl::init(CLong, &uiGroupTTBuilding, this, &popUp, TechTrees_ScrollerBuildings);
    TechTrees_Buildings_ID_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerBuildings, TechTrees_Buildings_ID, &unit_names);
    UnitComboBoxList.push_back(TechTrees_Buildings_ID_ComboBox);
    TechTrees_Buildings_Always2_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Buildings_Always2_Text = new SolidText(TechTrees_ScrollerBuildings, " Status *");
    TechTrees_Buildings_Always2 = AGETextCtrl::init(CByte, &uiGroupTTBuilding, this, &popUp, TechTrees_ScrollerBuildings);
    TechTrees_Buildings_Always2->SetToolTip(StatusHelp);
    TechTrees_Buildings_LocationInAge_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Buildings_LocationInAge_Text = new SolidText(TechTrees_ScrollerBuildings, " Location in Age *");
    TechTrees_Buildings_LocationInAge = AGETextCtrl::init(CByte, &uiGroupTTBuilding, this, &popUp, TechTrees_ScrollerBuildings);
    TechTrees_Buildings_LocationInAge->SetToolTip(LocationInAgeHelp);
    TechTrees_Buildings_LineMode_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Buildings_LineMode_Text = new SolidText(TechTrees_ScrollerBuildings, " Line Mode *");
    TechTrees_Buildings_LineMode = AGETextCtrl::init(CLong, &uiGroupTTBuilding, this, &popUp, TechTrees_ScrollerBuildings);
    TechTrees_Buildings_LineMode->SetToolTip(LineModeHelp);
    TechTrees_Buildings_EnablingResearch_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Buildings_EnablingResearch_Text = new SolidText(TechTrees_ScrollerBuildings, " Enabling Research *");
    TechTrees_Buildings_EnablingResearch = AGETextCtrl::init(CLong, &uiGroupTTBuilding, this, &popUp, TechTrees_ScrollerBuildings);
    TechTrees_Buildings_EnablingResearch->SetToolTip("Makes available\nUsed by buildings, which need a research to be available");
    TechTrees_Buildings_EnablingResearch_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerBuildings, TechTrees_Buildings_EnablingResearch, &research_names);
    ResearchComboBoxList.push_back(TechTrees_Buildings_EnablingResearch_ComboBox);

    TechTrees_Data_Buildings = new wxBoxSizer(wxVERTICAL);
    TechTrees_Data_Buildings2 = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_Data_Buildings3 = new wxBoxSizer(wxVERTICAL);
    TechTrees_Data_Buildings1 = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_ConnectedHolder_Buildings = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_Buildings_Buildings.CreateControls(this, &popUp, TechTrees_ScrollerBuildings, "buildings", "Connected Buildings", &unit_names);
    UnitComboBoxList.push_back(TechTrees_Buildings_Buildings.ItemCombo);
    TechTrees_Buildings_Units.CreateControls(this, &popUp, TechTrees_ScrollerBuildings, "buildings", "Connected Units", &unit_names);
    UnitComboBoxList.push_back(TechTrees_Buildings_Units.ItemCombo);
    TechTrees_Buildings_Researches.CreateControls(this, &popUp, TechTrees_ScrollerBuildings, "buildings", "Connected Researches", &research_names);
    ResearchComboBoxList.push_back(TechTrees_Buildings_Researches.ItemCombo);

    TechTrees_Buildings_Items.CreateControls(this, &popUp, TechTrees_ScrollerBuildings, "buildings", &mode_names);

    TechTrees_Buildings_TotalUnitsTechs_Holder[0] = new wxStaticBoxSizer(wxHORIZONTAL, TechTrees_ScrollerBuildings, "Total units and techs by age *");
    TechTrees_Buildings_TotalUnitsTechs_Holder[1] = new wxStaticBoxSizer(wxHORIZONTAL, TechTrees_ScrollerBuildings, "Total units and techs at first in age *");
    for(size_t loop = 0; loop < 10; ++loop)
    TechTrees_Buildings_TotalUnitsTechs[loop] = AGETextCtrl::init(CByte, &uiGroupTTBuilding, this, &popUp, TechTrees_ScrollerBuildings, AGETextCtrl::SMALL);
    for(size_t loop = 0; loop < 5; ++loop)
    {
        TechTrees_Buildings_TotalUnitsTechs[loop]->SetToolTip("Age "+lexical_cast<string>(loop+1));
        TechTrees_Buildings_TotalUnitsTechs[loop+5]->SetToolTip("Age "+lexical_cast<string>(loop+1));
    }

    TechTrees_MainList_Units_Search = new wxTextCtrl(Tab_TechTreeUnits, wxID_ANY);
    TechTrees_MainList_Units_UseAnd[0] = new wxCheckBox(Tab_TechTreeUnits, wxID_ANY, "And");
    TechTrees_MainList_Units_Search_R = new wxTextCtrl(Tab_TechTreeUnits, wxID_ANY);
    TechTrees_MainList_Units_UseAnd[1] = new wxCheckBox(Tab_TechTreeUnits, wxID_ANY, "And");
    for(size_t loop = 0; loop < 2; ++loop)
    {
        TechTrees_MainList_Units_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
        TechTrees_MainList_Units_SearchFilters[loop] = new AGEComboBox(Tab_TechTreeUnits, &tt_unit_filters);
    }
    TechTrees_MainList_Units_ListV = new AGEListView(Tab_TechTreeUnits, wxSize(200, 300));
    TechTrees_MainList_Units_Buttons = new wxGridSizer(3, 0, 0);
    TechTrees_MainList_Units_Add = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Units_Insert = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Units_Delete = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Units_Copy = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Units_Paste = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Units_PasteInsert = new wxButton(Tab_TechTreeUnits, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));

    TechTrees_Units_ID_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Units_ID_Text = new SolidText(TechTrees_ScrollerUnits, " Unit Number");
    TechTrees_Units_ID = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, &popUp, TechTrees_ScrollerUnits);
    TechTrees_Units_ID_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerUnits, TechTrees_Units_ID, &unit_names);
    UnitComboBoxList.push_back(TechTrees_Units_ID_ComboBox);
    TechTrees_Units_Always2_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Units_Always2_Text = new SolidText(TechTrees_ScrollerUnits, " Status *");
    TechTrees_Units_Always2 = AGETextCtrl::init(CByte, &uiGroupTTUnit, this, &popUp, TechTrees_ScrollerUnits);
    TechTrees_Units_Always2->SetToolTip(StatusHelp);
    TechTrees_Units_UpperBuilding_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Units_UpperBuilding_Text = new SolidText(TechTrees_ScrollerUnits, " Upper Building");
    TechTrees_Units_UpperBuilding = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, &popUp, TechTrees_ScrollerUnits);
    TechTrees_Units_UpperBuilding_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerUnits, TechTrees_Units_UpperBuilding, &unit_names);
    UnitComboBoxList.push_back(TechTrees_Units_UpperBuilding_ComboBox);
    TechTrees_Units_VerticalLine_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Units_VerticalLine_Text = new SolidText(TechTrees_ScrollerUnits, " Vertical Line Number");
    TechTrees_Units_VerticalLine = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, &popUp, TechTrees_ScrollerUnits);
    TechTrees_Units_LocationInAge_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Units_LocationInAge_Text = new SolidText(TechTrees_ScrollerUnits, " Location in Age *");
    TechTrees_Units_LocationInAge = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, &popUp, TechTrees_ScrollerUnits);
    TechTrees_Units_LocationInAge->SetToolTip(LocationInAgeHelp);
    TechTrees_Units_RequiredResearch_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Units_RequiredResearch_Text = new SolidText(TechTrees_ScrollerUnits, " Required Research *");
    TechTrees_Units_RequiredResearch = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, &popUp, TechTrees_ScrollerUnits);
    TechTrees_Units_RequiredResearch->SetToolTip("Upgrades unit\nUsed by units, which aren't first in upgrade line");
    TechTrees_Units_RequiredResearch_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerUnits, TechTrees_Units_RequiredResearch, &research_names);
    ResearchComboBoxList.push_back(TechTrees_Units_RequiredResearch_ComboBox);
    TechTrees_Units_LineMode_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Units_LineMode_Text = new SolidText(TechTrees_ScrollerUnits, " Line Mode *");
    TechTrees_Units_LineMode = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, &popUp, TechTrees_ScrollerUnits);
    TechTrees_Units_LineMode->SetToolTip(LineModeHelp);
    TechTrees_Units_EnablingResearch_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Units_EnablingResearch_Text = new SolidText(TechTrees_ScrollerUnits, " Enabling Research *");
    TechTrees_Units_EnablingResearch = AGETextCtrl::init(CLong, &uiGroupTTUnit, this, &popUp, TechTrees_ScrollerUnits);
    TechTrees_Units_EnablingResearch->SetToolTip("Makes available\nUsed by units, which need a research to be available");
    TechTrees_Units_EnablingResearch_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerUnits, TechTrees_Units_EnablingResearch, &research_names);
    ResearchComboBoxList.push_back(TechTrees_Units_EnablingResearch_ComboBox);

    TechTrees_Data_Units = new wxBoxSizer(wxVERTICAL);
    TechTrees_Data_Units1 = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_Data_Units2 = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_ConnectedHolder_Units = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_Units_Items.CreateControls(this, &popUp, TechTrees_ScrollerUnits, "units", &mode_names);
    TechTrees_Units_Units.CreateControls(this, &popUp, TechTrees_ScrollerUnits, "units", "Connected Units", &unit_names);
    UnitComboBoxList.push_back(TechTrees_Units_Units.ItemCombo);

    TechTrees_MainList_Researches_Search = new wxTextCtrl(Tab_TechTreeResearches, wxID_ANY);
    TechTrees_MainList_Researches_UseAnd[0] = new wxCheckBox(Tab_TechTreeResearches, wxID_ANY, "And");
    TechTrees_MainList_Researches_Search_R = new wxTextCtrl(Tab_TechTreeResearches, wxID_ANY);
    TechTrees_MainList_Researches_UseAnd[1] = new wxCheckBox(Tab_TechTreeResearches, wxID_ANY, "And");
    for(size_t loop = 0; loop < 2; ++loop)
    {
        TechTrees_MainList_Researches_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
        TechTrees_MainList_Researches_SearchFilters[loop] = new AGEComboBox(Tab_TechTreeResearches, &tt_research_filters);
    }
    TechTrees_MainList_Researches_ListV = new AGEListView(Tab_TechTreeResearches, wxSize(200, 300));
    TechTrees_MainList_Researches_Buttons = new wxGridSizer(3, 0, 0);
    TechTrees_MainList_Researches_Add = new wxButton(Tab_TechTreeResearches, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Researches_Insert = new wxButton(Tab_TechTreeResearches, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Researches_Delete = new wxButton(Tab_TechTreeResearches, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Researches_Copy = new wxButton(Tab_TechTreeResearches, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Researches_Paste = new wxButton(Tab_TechTreeResearches, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    TechTrees_MainList_Researches_PasteInsert = new wxButton(Tab_TechTreeResearches, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));

    TechTrees_Data_Researches = new wxBoxSizer(wxVERTICAL);
    TechTrees_Data_Researches2 = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_Data_Researches1 = new wxBoxSizer(wxVERTICAL);
    TechTrees_Data_Researches3 = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_Data_Researches4 = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_ConnectedHolder_Researches = new wxBoxSizer(wxHORIZONTAL);
    TechTrees_Researches_Buildings.CreateControls(this, &popUp, TechTrees_ScrollerResearches, "researches", "Connected Buildings", &unit_names);
    UnitComboBoxList.push_back(TechTrees_Researches_Buildings.ItemCombo);
    TechTrees_Researches_Units.CreateControls(this, &popUp, TechTrees_ScrollerResearches, "researches", "Connected Units", &unit_names);
    UnitComboBoxList.push_back(TechTrees_Researches_Units.ItemCombo);
    TechTrees_Researches_Researches.CreateControls(this, &popUp, TechTrees_ScrollerResearches, "researches", "Connected Researches", &research_names);
    ResearchComboBoxList.push_back(TechTrees_Researches_Researches.ItemCombo);

    TechTrees_Researches_ID_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Researches_ID_Text = new SolidText(TechTrees_ScrollerResearches, " Research Number");
    TechTrees_Researches_ID = AGETextCtrl::init(CLong, &uiGroupTTResearch, this, &popUp, TechTrees_ScrollerResearches);
    TechTrees_Researches_ID_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerResearches, TechTrees_Researches_ID, &research_names);
    ResearchComboBoxList.push_back(TechTrees_Researches_ID_ComboBox);
    TechTrees_Researches_Always2_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Researches_Always2_Text = new SolidText(TechTrees_ScrollerResearches, " Status *");
    TechTrees_Researches_Always2 = AGETextCtrl::init(CByte, &uiGroupTTResearch, this, &popUp, TechTrees_ScrollerResearches);
    TechTrees_Researches_Always2->SetToolTip(StatusHelp);
    TechTrees_Researches_UpperBuilding_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Researches_UpperBuilding_Text = new SolidText(TechTrees_ScrollerResearches, " Upper Building");
    TechTrees_Researches_UpperBuilding = AGETextCtrl::init(CLong, &uiGroupTTResearch, this, &popUp, TechTrees_ScrollerResearches);
    TechTrees_Researches_UpperBuilding_ComboBox = new ComboBox_Plus1(TechTrees_ScrollerResearches, TechTrees_Researches_UpperBuilding, &unit_names);
    UnitComboBoxList.push_back(TechTrees_Researches_UpperBuilding_ComboBox);
    TechTrees_Researches_VerticalLine_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Researches_VerticalLine_Text = new SolidText(TechTrees_ScrollerResearches, " Vertical Line Number");
    TechTrees_Researches_VerticalLine = AGETextCtrl::init(CLong, &uiGroupTTResearch, this, &popUp, TechTrees_ScrollerResearches);
    TechTrees_Researches_LocationInAge_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Researches_LocationInAge_Text = new SolidText(TechTrees_ScrollerResearches, " Location in Age *");
    TechTrees_Researches_LocationInAge = AGETextCtrl::init(CLong, &uiGroupTTResearch, this, &popUp, TechTrees_ScrollerResearches);
    TechTrees_Researches_LocationInAge->SetToolTip(LocationInAgeHelp);
    TechTrees_Researches_LineMode_Holder = new wxBoxSizer(wxVERTICAL);
    TechTrees_Researches_LineMode_Text = new SolidText(TechTrees_ScrollerResearches, " Line Mode *");
    TechTrees_Researches_LineMode = AGETextCtrl::init(CLong, &uiGroupTTResearch, this, &popUp, TechTrees_ScrollerResearches);
    TechTrees_Researches_LineMode->SetToolTip(LineModeHelp);

    TechTrees_Researches_Items.CreateControls(this, &popUp, TechTrees_ScrollerResearches, "researches", &mode_names);

    TabBar_TechTree->AddPage(Tab_TechTreeAges, "Ages");
    TabBar_TechTree->AddPage(Tab_TechTreeBuildings, "Buildings");
    TabBar_TechTree->AddPage(Tab_TechTreeUnits, "Units");
    TabBar_TechTree->AddPage(Tab_TechTreeResearches, "Researches");
    TabBar_TechTree->ChangeSelection(0);

    tt_unit_filters.Add("Normal Name");    // 0
    tt_unit_filters.Add("Status");
    tt_unit_filters.Add("Upper Building");
    tt_unit_filters.Add("Required Items");
    tt_unit_filters.Add("Age (1st Item)");
    tt_unit_filters.Add("Vertical Line Number");
    tt_unit_filters.Add("Location in Age");
    tt_unit_filters.Add("Required Research");
    tt_unit_filters.Add("Line Mode");
    tt_unit_filters.Add("Enabling Research");
    tt_building_filters.Add("Normal Name");    // 0
    tt_building_filters.Add("Status");
    tt_building_filters.Add("Required Items");
    tt_building_filters.Add("Age (1st Item)");
    tt_building_filters.Add("Location in Age");
    tt_building_filters.Add("Units & Techs by Age");
    tt_building_filters.Add("Units & Techs @ 1st by Age");
    tt_building_filters.Add("Line Mode");
    tt_building_filters.Add("Enabling Research");
    tt_research_filters.Add("Normal Name");   // 0
    tt_research_filters.Add("Status");
    tt_research_filters.Add("Upper Building");
    tt_research_filters.Add("Required Items");
    tt_research_filters.Add("Age (1st Item)");
    tt_research_filters.Add("Vertical Line Number");
    tt_research_filters.Add("Location in Age");
    tt_research_filters.Add("Line Mode");
    for(size_t loop = 0; loop < 2; ++loop)
    {
        TechTrees_MainList_Units_SearchFilters[loop]->Flash();
        TechTrees_MainList_Buildings_SearchFilters[loop]->Flash();
        TechTrees_MainList_Researches_SearchFilters[loop]->Flash();
    }

    for(size_t loop = 0; loop < General_TTUnknown.size(); ++loop)
    {
        General_TTUnknown_Holder[loop]->Add(General_TTUnknown_Text[loop]);
        General_TTUnknown_Holder[loop]->Add(General_TTUnknown[loop], 0, wxEXPAND);
        General_Variables2_Holder->Add(General_TTUnknown_Holder[loop], 0, wxRIGHT, 5);
    }

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
    for(size_t loop = 0; loop < 2; ++loop)
    {
        TechTrees_MainList_Buildings->Add(TechTrees_MainList_Buildings_Searches[loop], 0, wxEXPAND);
        TechTrees_MainList_Units->Add(TechTrees_MainList_Units_Searches[loop], 0, wxEXPAND);
        TechTrees_MainList_Researches->Add(TechTrees_MainList_Researches_Searches[loop], 0, wxEXPAND);
    }
    for(size_t loop = 0; loop < 2; ++loop)
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

    TechTrees_Ages_ID_Holder->Add(TechTrees_Ages_ID_Text);
    TechTrees_Ages_ID_Holder->Add(TechTrees_Ages_ID, 0, wxEXPAND);
    TechTrees_Ages_LineMode_Holder->Add(TechTrees_Ages_LineMode_Text);
    TechTrees_Ages_LineMode_Holder->Add(TechTrees_Ages_LineMode, 0, wxEXPAND);
    TechTrees_Ages_Unknown2_Holder->Add(TechTrees_Ages_Unknown2_Text);
    TechTrees_Ages_Unknown2_Holder->Add(TechTrees_Ages_Unknown2, 0, wxEXPAND);

    TechTrees_Data_Ages1->Add(TechTrees_Ages_ID_Holder);
    TechTrees_Data_Ages1->Add(TechTrees_Ages_Unknown2_Holder, 0, wxLEFT, 5);
    TechTrees_Data_Ages1->Add(TechTrees_Ages_LineMode_Holder, 0, wxLEFT, 5);

    TechTrees_Data_Ages2->Add(TechTrees_Ages_Items.Area, 1, wxEXPAND);
    TechTrees_Data_Ages2->Add(TechTrees_Ages_UnknownItems.Area, 1, wxEXPAND | wxLEFT, 5);
    TechTrees_Data_Ages2->AddStretchSpacer(1);

    TechTrees_Data_Ages->Add(TechTrees_Data_Ages1, 0, wxBOTTOM, 5);
    TechTrees_Data_Ages->Add(TechTrees_ConnectedHolder_Ages, 0, wxEXPAND | wxBOTTOM, 5);
    TechTrees_Data_Ages->Add(TechTrees_Data_Ages2, 0, wxEXPAND);

    TechTrees_ConnectedHolder_Buildings->Add(TechTrees_Buildings_Buildings.ItemList, 1, wxEXPAND);
    TechTrees_ConnectedHolder_Buildings->Add(TechTrees_Buildings_Units.ItemList, 1, wxEXPAND | wxLEFT, 5);
    TechTrees_ConnectedHolder_Buildings->Add(TechTrees_Buildings_Researches.ItemList, 1, wxEXPAND | wxLEFT, 5);

    TechTrees_Buildings_ID_Holder->Add(TechTrees_Buildings_ID_Text);
    TechTrees_Buildings_ID_Holder->Add(TechTrees_Buildings_ID, 0, wxEXPAND);
    TechTrees_Buildings_ID_Holder->Add(TechTrees_Buildings_ID_ComboBox);
    TechTrees_Buildings_LocationInAge_Holder->Add(TechTrees_Buildings_LocationInAge_Text);
    TechTrees_Buildings_LocationInAge_Holder->Add(TechTrees_Buildings_LocationInAge, 0, wxEXPAND);
    TechTrees_Buildings_LineMode_Holder->Add(TechTrees_Buildings_LineMode_Text);
    TechTrees_Buildings_LineMode_Holder->Add(TechTrees_Buildings_LineMode, 0, wxEXPAND);
    TechTrees_Buildings_EnablingResearch_Holder->Add(TechTrees_Buildings_EnablingResearch_Text);
    TechTrees_Buildings_EnablingResearch_Holder->Add(TechTrees_Buildings_EnablingResearch, 0, wxEXPAND);
    TechTrees_Buildings_EnablingResearch_Holder->Add(TechTrees_Buildings_EnablingResearch_ComboBox);
    TechTrees_Buildings_Always2_Holder->Add(TechTrees_Buildings_Always2_Text);
    TechTrees_Buildings_Always2_Holder->Add(TechTrees_Buildings_Always2, 0, wxEXPAND);

    TechTrees_Data_Buildings1->Add(TechTrees_Buildings_ID_Holder);
    TechTrees_Data_Buildings1->Add(TechTrees_Buildings_Always2_Holder, 0, wxLEFT, 5);
    TechTrees_Data_Buildings1->Add(TechTrees_Buildings_LocationInAge_Holder, 0, wxLEFT, 5);
    TechTrees_Data_Buildings1->Add(TechTrees_Buildings_LineMode_Holder, 0, wxLEFT, 5);
    TechTrees_Data_Buildings1->Add(TechTrees_Buildings_EnablingResearch_Holder, 0, wxLEFT, 5);

    for(size_t loop = 0; loop < 5; ++loop)
    TechTrees_Buildings_TotalUnitsTechs_Holder[0]->Add(TechTrees_Buildings_TotalUnitsTechs[loop], 0, wxRIGHT, 5);
    for(size_t loop = 5; loop < 10; ++loop)
    TechTrees_Buildings_TotalUnitsTechs_Holder[1]->Add(TechTrees_Buildings_TotalUnitsTechs[loop], 0, wxRIGHT, 5);
    TechTrees_Data_Buildings3->Add(TechTrees_Buildings_TotalUnitsTechs_Holder[0]);
    TechTrees_Data_Buildings3->Add(TechTrees_Buildings_TotalUnitsTechs_Holder[1], 0, wxTOP, 5);
    TechTrees_Data_Buildings2->Add(TechTrees_Buildings_Items.Area, 1, wxEXPAND);
    TechTrees_Data_Buildings2->Add(TechTrees_Data_Buildings3, 2, wxEXPAND | wxLEFT, 5);

    TechTrees_Data_Buildings->Add(TechTrees_Data_Buildings1, 0, wxBOTTOM, 5);
    TechTrees_Data_Buildings->Add(TechTrees_ConnectedHolder_Buildings, 0, wxEXPAND | wxBOTTOM, 5);
    TechTrees_Data_Buildings->Add(TechTrees_Data_Buildings2, 0, wxEXPAND);

    TechTrees_ConnectedHolder_Units->Add(TechTrees_Units_Items.Area, 1, wxEXPAND);
    TechTrees_ConnectedHolder_Units->Add(TechTrees_Units_Units.ItemList, 1, wxEXPAND | wxLEFT, 5);
    TechTrees_ConnectedHolder_Units->AddStretchSpacer(1);

    TechTrees_Units_ID_Holder->Add(TechTrees_Units_ID_Text);
    TechTrees_Units_ID_Holder->Add(TechTrees_Units_ID, 0, wxEXPAND);
    TechTrees_Units_ID_Holder->Add(TechTrees_Units_ID_ComboBox);
    TechTrees_Units_UpperBuilding_Holder->Add(TechTrees_Units_UpperBuilding_Text);
    TechTrees_Units_UpperBuilding_Holder->Add(TechTrees_Units_UpperBuilding, 0, wxEXPAND);
    TechTrees_Units_UpperBuilding_Holder->Add(TechTrees_Units_UpperBuilding_ComboBox);
    TechTrees_Units_LocationInAge_Holder->Add(TechTrees_Units_LocationInAge_Text);
    TechTrees_Units_LocationInAge_Holder->Add(TechTrees_Units_LocationInAge, 0, wxEXPAND);
    TechTrees_Units_RequiredResearch_Holder->Add(TechTrees_Units_RequiredResearch_Text);
    TechTrees_Units_RequiredResearch_Holder->Add(TechTrees_Units_RequiredResearch, 0, wxEXPAND);
    TechTrees_Units_RequiredResearch_Holder->Add(TechTrees_Units_RequiredResearch_ComboBox);
    TechTrees_Units_LineMode_Holder->Add(TechTrees_Units_LineMode_Text);
    TechTrees_Units_LineMode_Holder->Add(TechTrees_Units_LineMode, 0, wxEXPAND);
    TechTrees_Units_EnablingResearch_Holder->Add(TechTrees_Units_EnablingResearch_Text);
    TechTrees_Units_EnablingResearch_Holder->Add(TechTrees_Units_EnablingResearch, 0, wxEXPAND);
    TechTrees_Units_EnablingResearch_Holder->Add(TechTrees_Units_EnablingResearch_ComboBox);
    TechTrees_Units_Always2_Holder->Add(TechTrees_Units_Always2_Text);
    TechTrees_Units_Always2_Holder->Add(TechTrees_Units_Always2, 0, wxEXPAND);
    TechTrees_Units_VerticalLine_Holder->Add(TechTrees_Units_VerticalLine_Text);
    TechTrees_Units_VerticalLine_Holder->Add(TechTrees_Units_VerticalLine, 0, wxEXPAND);

    TechTrees_Data_Units1->Add(TechTrees_Units_ID_Holder);
    TechTrees_Data_Units1->Add(TechTrees_Units_Always2_Holder, 0, wxLEFT, 5);
    TechTrees_Data_Units1->Add(TechTrees_Units_UpperBuilding_Holder, 0, wxLEFT, 5);
    TechTrees_Data_Units2->Add(TechTrees_Units_VerticalLine_Holder);
    TechTrees_Data_Units2->Add(TechTrees_Units_LocationInAge_Holder, 0, wxLEFT, 5);
    TechTrees_Data_Units2->Add(TechTrees_Units_RequiredResearch_Holder, 0, wxLEFT, 5);
    TechTrees_Data_Units2->Add(TechTrees_Units_LineMode_Holder, 0, wxLEFT, 5);
    TechTrees_Data_Units2->Add(TechTrees_Units_EnablingResearch_Holder, 0, wxLEFT, 5);

    TechTrees_Data_Units->Add(TechTrees_Data_Units1, 0, wxBOTTOM, 5);
    TechTrees_Data_Units->Add(TechTrees_Data_Units2, 0, wxBOTTOM, 5);
    TechTrees_Data_Units->Add(TechTrees_ConnectedHolder_Units, 0, wxEXPAND);

    TechTrees_ConnectedHolder_Researches->Add(TechTrees_Researches_Buildings.ItemList, 1, wxEXPAND);
    TechTrees_ConnectedHolder_Researches->Add(TechTrees_Researches_Units.ItemList, 1, wxEXPAND | wxLEFT, 5);
    TechTrees_ConnectedHolder_Researches->Add(TechTrees_Researches_Researches.ItemList, 1, wxEXPAND | wxLEFT, 5);

    TechTrees_Researches_ID_Holder->Add(TechTrees_Researches_ID_Text);
    TechTrees_Researches_ID_Holder->Add(TechTrees_Researches_ID, 0, wxEXPAND);
    TechTrees_Researches_ID_Holder->Add(TechTrees_Researches_ID_ComboBox);
    TechTrees_Researches_UpperBuilding_Holder->Add(TechTrees_Researches_UpperBuilding_Text);
    TechTrees_Researches_UpperBuilding_Holder->Add(TechTrees_Researches_UpperBuilding, 0, wxEXPAND);
    TechTrees_Researches_UpperBuilding_Holder->Add(TechTrees_Researches_UpperBuilding_ComboBox);
    TechTrees_Researches_Always2_Holder->Add(TechTrees_Researches_Always2_Text);
    TechTrees_Researches_Always2_Holder->Add(TechTrees_Researches_Always2, 0, wxEXPAND);
    TechTrees_Researches_VerticalLine_Holder->Add(TechTrees_Researches_VerticalLine_Text);
    TechTrees_Researches_VerticalLine_Holder->Add(TechTrees_Researches_VerticalLine, 0, wxEXPAND);
    TechTrees_Researches_LocationInAge_Holder->Add(TechTrees_Researches_LocationInAge_Text);
    TechTrees_Researches_LocationInAge_Holder->Add(TechTrees_Researches_LocationInAge, 0, wxEXPAND);
    TechTrees_Researches_LineMode_Holder->Add(TechTrees_Researches_LineMode_Text);
    TechTrees_Researches_LineMode_Holder->Add(TechTrees_Researches_LineMode, 0, wxEXPAND);

    TechTrees_Data_Researches3->Add(TechTrees_Researches_ID_Holder);
    TechTrees_Data_Researches3->Add(TechTrees_Researches_Always2_Holder, 0, wxLEFT, 5);
    TechTrees_Data_Researches3->Add(TechTrees_Researches_UpperBuilding_Holder, 0, wxLEFT, 5);
    TechTrees_Data_Researches4->Add(TechTrees_Researches_VerticalLine_Holder);
    TechTrees_Data_Researches4->Add(TechTrees_Researches_LocationInAge_Holder, 0, wxLEFT, 5);
    TechTrees_Data_Researches4->Add(TechTrees_Researches_LineMode_Holder, 0, wxLEFT, 5);

    TechTrees_Data_Researches1->Add(TechTrees_Data_Researches3, 0, wxBOTTOM, 5);
    TechTrees_Data_Researches1->Add(TechTrees_Data_Researches4);
    TechTrees_Data_Researches2->Add(TechTrees_Data_Researches1, 2, wxEXPAND);
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

    TechTrees_Main->Add(General_Variables2_Holder, 0, wxALL, 5);
    TechTrees_Main->Add(TabBar_TechTree, 1, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 5);

    Tab_TechTreeAges->SetSizer(TechTrees_TabAges);
    Tab_TechTreeBuildings->SetSizer(TechTrees_TabBuildings);
    Tab_TechTreeUnits->SetSizer(TechTrees_TabUnits);
    Tab_TechTreeResearches->SetSizer(TechTrees_TabResearches);
    Tab_TechTrees->SetSizer(TechTrees_Main);

    TechTrees_MainList_Ages_Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTAgesSearch, this);
    TechTrees_MainList_Ages_Search_R->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTAgesSearch, this);
    TechTrees_MainList_Ages_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTAgesSelect, this);
    TechTrees_MainList_Ages_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTAgesSelect, this);
    TechTrees_MainList_Ages_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTAgesSelect, this);
    TechTrees_MainList_Ages_Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesAdd, this);
    TechTrees_MainList_Ages_Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesInsert, this);
    TechTrees_MainList_Ages_Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesDelete, this);
    TechTrees_MainList_Ages_Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesCopy, this);
    TechTrees_MainList_Ages_Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesPaste, this);
    TechTrees_MainList_Ages_PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesPasteInsert, this);
    TechTrees_MainList_Buildings_Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTBuildingSearch, this);
    TechTrees_MainList_Buildings_Search_R->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTBuildingSearch, this);
    TechTrees_MainList_Buildings_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTBuildingSelect, this);
    TechTrees_MainList_Buildings_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTBuildingSelect, this);
    TechTrees_MainList_Buildings_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTBuildingSelect, this);
    TechTrees_MainList_Buildings_Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingAdd, this);
    TechTrees_MainList_Buildings_Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingInsert, this);
    TechTrees_MainList_Buildings_Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingDelete, this);
    TechTrees_MainList_Buildings_Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingCopy, this);
    TechTrees_MainList_Buildings_Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingPaste, this);
    TechTrees_MainList_Buildings_PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingPasteInsert, this);
    TechTrees_MainList_Units_Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTUnitSearch, this);
    TechTrees_MainList_Units_Search_R->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTUnitSearch, this);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        TechTrees_MainList_Buildings_UseAnd[loop]->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &AGE_Frame::OnTTBuildingSearch, this);
        TechTrees_MainList_Units_UseAnd[loop]->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &AGE_Frame::OnTTUnitSearch, this);
        TechTrees_MainList_Researches_UseAnd[loop]->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &AGE_Frame::OnTTResearchSearch, this);
        TechTrees_MainList_Buildings_SearchFilters[loop]->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnSelection_SearchFilters, this);
        TechTrees_MainList_Units_SearchFilters[loop]->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnSelection_SearchFilters, this);
        TechTrees_MainList_Researches_SearchFilters[loop]->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnSelection_SearchFilters, this);
    }
    TechTrees_MainList_Units_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTUnitSelect, this);
    TechTrees_MainList_Units_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTUnitSelect, this);
    TechTrees_MainList_Units_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTUnitSelect, this);
    TechTrees_MainList_Units_Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitAdd, this);
    TechTrees_MainList_Units_Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitInsert, this);
    TechTrees_MainList_Units_Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitDelete, this);
    TechTrees_MainList_Units_Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitCopy, this);
    TechTrees_MainList_Units_Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitPaste, this);
    TechTrees_MainList_Units_PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitPasteInsert, this);
    TechTrees_MainList_Researches_Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTResearchSearch, this);
    TechTrees_MainList_Researches_Search_R->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTResearchSearch, this);
    TechTrees_MainList_Researches_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTResearchSelect, this);
    TechTrees_MainList_Researches_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTResearchSelect, this);
    TechTrees_MainList_Researches_ListV->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTResearchSelect, this);
    TechTrees_MainList_Researches_Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchAdd, this);
    TechTrees_MainList_Researches_Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchInsert, this);
    TechTrees_MainList_Researches_Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchDelete, this);
    TechTrees_MainList_Researches_Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchCopy, this);
    TechTrees_MainList_Researches_Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchPaste, this);
    TechTrees_MainList_Researches_PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchPasteInsert, this);

    TechTrees_Ages_Buildings.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTAgesBuildingSearch, this);
    TechTrees_Ages_Units.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTAgesUnitSearch, this);
    TechTrees_Ages_Researches.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTAgesResearchSearch, this);
    TechTrees_Ages_Items.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTAgeItemSearch, this);
    TechTrees_Ages_UnknownItems.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTAgeUnknownItemSearch, this);
    TechTrees_Ages_Buildings.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTAgesBuildingSearch, this);
    TechTrees_Ages_Units.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTAgesUnitSearch, this);
    TechTrees_Ages_Researches.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTAgesResearchSearch, this);
    TechTrees_Ages_Items.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTAgeItemSearch, this);
    TechTrees_Ages_UnknownItems.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTAgeUnknownItemSearch, this);
    TechTrees_Ages_Buildings.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTAgesBuildingSelect, this);
    TechTrees_Ages_Units.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTAgesUnitSelect, this);
    TechTrees_Ages_Researches.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTAgesResearchSelect, this);
    TechTrees_Ages_Items.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTAgeItemSelect, this);
    TechTrees_Ages_UnknownItems.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTAgeUnknownItemSelect, this);
    TechTrees_Ages_Buildings.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTAgesBuildingSelect, this);
    TechTrees_Ages_Units.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTAgesUnitSelect, this);
    TechTrees_Ages_Researches.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTAgesResearchSelect, this);
    TechTrees_Ages_Items.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTAgeItemSelect, this);
    TechTrees_Ages_UnknownItems.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTAgeUnknownItemSelect, this);
    TechTrees_Ages_Buildings.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTAgesBuildingSelect, this);
    TechTrees_Ages_Units.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTAgesUnitSelect, this);
    TechTrees_Ages_Researches.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTAgesResearchSelect, this);
    TechTrees_Ages_Items.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTAgeItemSelect, this);
    TechTrees_Ages_UnknownItems.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTAgeUnknownItemSelect, this);
    TechTrees_Ages_Buildings.Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesBuildingAdd, this);
    TechTrees_Ages_Units.Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesUnitAdd, this);
    TechTrees_Ages_Researches.Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesResearchAdd, this);
    TechTrees_Ages_Buildings.Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesBuildingInsert, this);
    TechTrees_Ages_Units.Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesUnitInsert, this);
    TechTrees_Ages_Researches.Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesResearchInsert, this);
    TechTrees_Ages_Buildings.Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesBuildingDelete, this);
    TechTrees_Ages_Units.Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesUnitDelete, this);
    TechTrees_Ages_Researches.Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesResearchDelete, this);
    TechTrees_Ages_Buildings.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesBuildingCopy, this);
    TechTrees_Ages_Units.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesUnitCopy, this);
    TechTrees_Ages_Researches.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesResearchCopy, this);
    TechTrees_Ages_Items.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgeItemCopy, this);
    TechTrees_Ages_UnknownItems.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgeUnknownItemCopy, this);
    TechTrees_Ages_Buildings.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesBuildingPaste, this);
    TechTrees_Ages_Units.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesUnitPaste, this);
    TechTrees_Ages_Researches.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesResearchPaste, this);
    TechTrees_Ages_Items.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgeItemPaste, this);
    TechTrees_Ages_UnknownItems.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgeUnknownItemPaste, this);
    TechTrees_Ages_Buildings.PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesBuildingPasteInsert, this);
    TechTrees_Ages_Units.PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesUnitPasteInsert, this);
    TechTrees_Ages_Researches.PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesResearchPasteInsert, this);
    TechTrees_Ages_Buildings.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesBuildingCopyToAges, this);
    TechTrees_Ages_Units.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesUnitCopyToAges, this);
    TechTrees_Ages_Researches.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgesResearchCopyToAges, this);
    TechTrees_Ages_Items.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgeItemCopyToAges, this);
    TechTrees_Ages_UnknownItems.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTAgeUnknownItemCopyToAges, this);
    TechTrees_Buildings_Buildings.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTBuildingBuildingSearch, this);
    TechTrees_Buildings_Units.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTBuildingUnitSearch, this);
    TechTrees_Buildings_Researches.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTBuildingResearchSearch, this);
    TechTrees_Buildings_Items.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTBuildingItemSearch, this);
    TechTrees_Buildings_Buildings.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTBuildingBuildingSearch, this);
    TechTrees_Buildings_Units.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTBuildingUnitSearch, this);
    TechTrees_Buildings_Researches.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTBuildingResearchSearch, this);
    TechTrees_Buildings_Items.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTBuildingItemSearch, this);
    TechTrees_Buildings_Buildings.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTBuildingBuildingSelect, this);
    TechTrees_Buildings_Units.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTBuildingUnitSelect, this);
    TechTrees_Buildings_Researches.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTBuildingResearchSelect, this);
    TechTrees_Buildings_Items.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTBuildingItemSelect, this);
    TechTrees_Buildings_Buildings.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTBuildingBuildingSelect, this);
    TechTrees_Buildings_Units.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTBuildingUnitSelect, this);
    TechTrees_Buildings_Researches.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTBuildingResearchSelect, this);
    TechTrees_Buildings_Items.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTBuildingItemSelect, this);
    TechTrees_Buildings_Buildings.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTBuildingBuildingSelect, this);
    TechTrees_Buildings_Units.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTBuildingUnitSelect, this);
    TechTrees_Buildings_Researches.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTBuildingResearchSelect, this);
    TechTrees_Buildings_Items.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTBuildingItemSelect, this);
    TechTrees_Buildings_Buildings.Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingBuildingAdd, this);
    TechTrees_Buildings_Units.Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingUnitAdd, this);
    TechTrees_Buildings_Researches.Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingResearchAdd, this);
    TechTrees_Buildings_Buildings.Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingBuildingInsert, this);
    TechTrees_Buildings_Units.Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingUnitInsert, this);
    TechTrees_Buildings_Researches.Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingResearchInsert, this);
    TechTrees_Buildings_Buildings.Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingBuildingDelete, this);
    TechTrees_Buildings_Units.Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingUnitDelete, this);
    TechTrees_Buildings_Researches.Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingResearchDelete, this);
    TechTrees_Buildings_Buildings.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingBuildingCopy, this);
    TechTrees_Buildings_Units.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingUnitCopy, this);
    TechTrees_Buildings_Researches.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingResearchCopy, this);
    TechTrees_Buildings_Items.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingItemCopy, this);
    TechTrees_Buildings_Buildings.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingBuildingPaste, this);
    TechTrees_Buildings_Units.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingUnitPaste, this);
    TechTrees_Buildings_Researches.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingResearchPaste, this);
    TechTrees_Buildings_Items.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingItemPaste, this);
    TechTrees_Buildings_Buildings.PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingBuildingPasteInsert, this);
    TechTrees_Buildings_Units.PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingUnitPasteInsert, this);
    TechTrees_Buildings_Researches.PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingResearchPasteInsert, this);
    TechTrees_Buildings_Buildings.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingBuildingCopyToBuildings, this);
    TechTrees_Buildings_Units.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingUnitCopyToBuildings, this);
    TechTrees_Buildings_Researches.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingResearchCopyToBuildings, this);
    TechTrees_Buildings_Items.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTBuildingItemCopyToBuildings, this);
    TechTrees_Units_Units.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTUnitUnitSearch, this);
    TechTrees_Units_Items.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTUnitItemSearch, this);
    TechTrees_Units_Units.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTUnitUnitSearch, this);
    TechTrees_Units_Items.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTUnitItemSearch, this);
    TechTrees_Units_Units.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTUnitUnitSelect, this);
    TechTrees_Units_Items.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTUnitItemSelect, this);
    TechTrees_Units_Units.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTUnitUnitSelect, this);
    TechTrees_Units_Items.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTUnitItemSelect, this);
    TechTrees_Units_Units.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTUnitUnitSelect, this);
    TechTrees_Units_Items.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTUnitItemSelect, this);
    TechTrees_Units_Units.Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitUnitAdd, this);
    TechTrees_Units_Units.Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitUnitInsert, this);
    TechTrees_Units_Units.Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitUnitDelete, this);
    TechTrees_Units_Units.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitUnitCopy, this);
    TechTrees_Units_Items.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitItemCopy, this);
    TechTrees_Units_Units.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitUnitPaste, this);
    TechTrees_Units_Items.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitItemPaste, this);
    TechTrees_Units_Units.PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitUnitPasteInsert, this);
    TechTrees_Units_Units.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitUnitCopyToUnits, this);
    TechTrees_Units_Items.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTUnitItemCopyToUnits, this);
    TechTrees_Researches_Buildings.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTResearchBuildingSearch, this);
    TechTrees_Researches_Units.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTResearchUnitSearch, this);
    TechTrees_Researches_Researches.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTResearchResearchSearch, this);
    TechTrees_Researches_Items.Search->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTResearchItemSearch, this);
    TechTrees_Researches_Buildings.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTResearchBuildingSearch, this);
    TechTrees_Researches_Units.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTResearchUnitSearch, this);
    TechTrees_Researches_Researches.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTResearchResearchSearch, this);
    TechTrees_Researches_Items.SearchRecursive->Bind(wxEVT_COMMAND_TEXT_UPDATED, &AGE_Frame::OnTTResearchItemSearch, this);
    TechTrees_Researches_Buildings.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTResearchBuildingSelect, this);
    TechTrees_Researches_Units.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTResearchUnitSelect, this);
    TechTrees_Researches_Researches.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTResearchResearchSelect, this);
    TechTrees_Researches_Items.List->Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED, &AGE_Frame::OnTTResearchItemSelect, this);
    TechTrees_Researches_Buildings.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTResearchBuildingSelect, this);
    TechTrees_Researches_Units.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTResearchUnitSelect, this);
    TechTrees_Researches_Researches.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTResearchResearchSelect, this);
    TechTrees_Researches_Items.List->Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED, &AGE_Frame::OnTTResearchItemSelect, this);
    TechTrees_Researches_Buildings.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTResearchBuildingSelect, this);
    TechTrees_Researches_Units.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTResearchUnitSelect, this);
    TechTrees_Researches_Researches.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTResearchResearchSelect, this);
    TechTrees_Researches_Items.List->Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED, &AGE_Frame::OnTTResearchItemSelect, this);
    TechTrees_Researches_Buildings.Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchBuildingAdd, this);
    TechTrees_Researches_Units.Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchUnitAdd, this);
    TechTrees_Researches_Researches.Add->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchResearchAdd, this);
    TechTrees_Researches_Buildings.Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchBuildingInsert, this);
    TechTrees_Researches_Units.Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchUnitInsert, this);
    TechTrees_Researches_Researches.Insert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchResearchInsert, this);
    TechTrees_Researches_Buildings.Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchBuildingDelete, this);
    TechTrees_Researches_Units.Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchUnitDelete, this);
    TechTrees_Researches_Researches.Delete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchResearchDelete, this);
    TechTrees_Researches_Buildings.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchBuildingCopy, this);
    TechTrees_Researches_Units.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchUnitCopy, this);
    TechTrees_Researches_Researches.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchResearchCopy, this);
    TechTrees_Researches_Items.Copy->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchItemCopy, this);
    TechTrees_Researches_Buildings.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchBuildingPaste, this);
    TechTrees_Researches_Units.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchUnitPaste, this);
    TechTrees_Researches_Researches.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchResearchPaste, this);
    TechTrees_Researches_Items.Paste->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchItemPaste, this);
    TechTrees_Researches_Buildings.PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchBuildingPasteInsert, this);
    TechTrees_Researches_Units.PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchUnitPasteInsert, this);
    TechTrees_Researches_Researches.PasteInsert->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchResearchPasteInsert, this);
    TechTrees_Researches_Buildings.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchBuildingCopyToResearches, this);
    TechTrees_Researches_Units.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchUnitCopyToResearches, this);
    TechTrees_Researches_Researches.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchResearchCopyToResearches, this);
    TechTrees_Researches_Items.CopyAllToSelected->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_Frame::OnTTResearchItemCopyToResearches, this);

    ttAgeTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTAgesTimer, this);
    ttAgeBuildingTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTAgesBuildingTimer, this);
    ttAgeUnitTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTAgesUnitTimer, this);
    ttAgeResearchTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTAgesResearchTimer, this);
    ttAgeItemTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTAgeItemTimer, this);
    ttAgeUnknownTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTAgeUnknownItemTimer, this);
    ttBuildingTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTBuildingTimer, this);
    ttBuildingBuildingTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTBuildingBuildingTimer, this);
    ttBuildingUnitTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTBuildingUnitTimer, this);
    ttBuildingResearchTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTBuildingResearchTimer, this);
    ttBuildingItemTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTBuildingItemTimer, this);
    ttUnitTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTUnitTimer, this);
    ttUnitUnitTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTUnitUnitTimer, this);
    ttUnitItemTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTUnitItemTimer, this);
    ttResearchTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTResearchTimer, this);
    ttResearchBuildingTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTResearchBuildingTimer, this);
    ttResearchUnitTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTResearchUnitTimer, this);
    ttResearchResearchTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTResearchResearchTimer, this);
    ttResearchItemTimer.Bind(wxEVT_TIMER, &AGE_Frame::OnTTResearchItemTimer, this);

    TechTrees_Ages_ID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Ages_Buildings.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Ages_Units.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Ages_Researches.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Ages_Items.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Ages_Items.Mode->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Ages_UnknownItems.Unknown1->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Ages_UnknownItems.Unknown2->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Ages_Buildings.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Ages_Units.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Ages_Researches.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Ages_Items.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Ages_Items.ModeCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTreeMode, this);
    TechTrees_Buildings_ID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Buildings_Buildings.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Buildings_Units.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Buildings_Researches.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Buildings_Items.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Buildings_Items.Mode->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Units_ID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Units_Units.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Units_Items.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Units_Items.Mode->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Researches_ID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Researches_Buildings.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Researches_Units.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Researches_Researches.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Researches_Items.Item->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Researches_Items.Mode->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_TechTrees, this);
    TechTrees_Buildings_ID_ComboBox->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Buildings_Buildings.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Buildings_Units.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Buildings_Researches.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Buildings_Items.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Buildings_Items.ModeCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTreeMode, this);
    TechTrees_Units_ID_ComboBox->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Units_Units.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Units_Items.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Units_Items.ModeCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTreeMode, this);
    TechTrees_Researches_ID_ComboBox->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Researches_Buildings.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Researches_Units.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Researches_Researches.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Researches_Items.ItemCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTrees, this);
    TechTrees_Researches_Items.ModeCombo->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_Frame::OnUpdateCombo_TechTreeMode, this);
}

void AGE_Frame::OnKillFocus_TechTrees(wxFocusEvent &event)
{
    event.Skip();
    if(static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() != 0) return;
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

void AGE_Frame::OnUpdateCombo_TechTreeMode(wxCommandEvent &event)
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
}

void AGE_Frame::OnUpdateCombo_TechTrees(wxCommandEvent &event)
{
    static_cast<ComboBox_Plus1*>(event.GetEventObject())->OnChoose(event);
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
