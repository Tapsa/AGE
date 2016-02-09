#include "../AGE_Frame.h"

void AGE_Frame::OnCivsSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListCivs(false);
}

string AGE_Frame::GetCivName(int index)
{
    return (GenieVersion < genie::GV_SWGB ? dataset->Civs[index].Name : dataset->Civs[index].Name2) + " (" + lexical_cast<string>((short)dataset->Civs[index].IconSet) + ")";
}

void AGE_Frame::ListCivs(bool all)
{
	InitCivs(all);
	wxTimerEvent E;
	OnCivsTimer(E);
}

void AGE_Frame::InitCivs(bool all)
{
	searchText = Civs_Civs_Search->GetValue().MakeLower();
	excludeText = Civs_Civs_Search_R->GetValue().MakeLower();

	Civs_Civs_ListV->names.clear();
	Civs_Civs_ListV->indexes.clear();
	wxArrayString names;
	if(all) names.Alloc(dataset->Graphics.size());

	for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetCivName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Civs_Civs_ListV->names.Add(Name);
			Civs_Civs_ListV->indexes.push_back(loop);
		}
		if(all) names.Add(Name);
	}

	virtualListing(Civs_Civs_ListV);
	if(all)
	{
		FillLists(CivComboBoxList, names);
        for(auto &box: CivComboBoxListNormal)
        {
            short selection = box->GetSelection();
            box->Clear();
            box->Append(names);
            box->SetSelection(selection < box->GetCount() ? selection : 0);
        }
	}
}

void AGE_Frame::OnCivsSelect(wxCommandEvent &event)
{
    if(!civTimer.IsRunning())
        civTimer.Start(150);
}

void AGE_Frame::OnCivsTimer(wxTimerEvent &event)
{
    civTimer.Stop();
	auto selections = Civs_Civs_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Civs_Civs_ListV, CivIDs);

    for(auto &box: uiGroupCiv) box->clear();

	genie::Civ * CivPointer;
	for(auto sel = selections; sel--> 0;)
	{
		CivPointer = &dataset->Civs[CivIDs[sel]];

		Civs_One->prepend(&CivPointer->Enabled);
		Civs_Name[0]->prepend(&CivPointer->Name);
		if(GenieVersion >= genie::GV_MIK)
		{
			Civs_TechTree->prepend(&CivPointer->TechTreeID);
			if(GenieVersion >= genie::GV_AoKB)
			{
				Civs_TeamBonus->prepend(&CivPointer->TeamBonusID);
				if(GenieVersion >= genie::GV_SWGB)
				{
					Civs_Name[1]->prepend(&CivPointer->Name2);
					for(size_t loop = 0; loop < 4; ++loop)
					Civs_SUnknown1[loop]->prepend(&CivPointer->UniqueUnitsResearches[loop]);
				}
			}
		}
		Civs_GraphicSet->prepend(&CivPointer->IconSet);
	}
    SetStatusText(wxString::Format("Selections: %d    Selected civilization: %d", selections, CivIDs.front()), 0);

    for(auto &box: uiGroupCiv) box->update();
	ListResources();
}

void AGE_Frame::OnCivsAdd(wxCommandEvent &event)
{
	if(!dataset) return;

	wxBusyCursor WaitCursor;
	genie::Civ Temp;
	Temp.setGameVersion(GenieVersion);
	if(dataset->Civs.size() > 0)
	{
		short FillingCiv = (dataset->Civs.size() > 1) ? 1 : 0;
		Temp.Resources = dataset->Civs[FillingCiv].Resources;
		Temp.UnitPointers = dataset->Civs[FillingCiv].UnitPointers;
		Temp.Units = dataset->Civs[FillingCiv].Units;
	}
	dataset->Civs.push_back(Temp);
	How2List = ADD;
	OnCivCountChange();
	ListUnits(UnitCivID, false);
}

void AGE_Frame::OnCivsInsert(wxCommandEvent &event)
{
	auto selections = Civs_Civs_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::Civ Temp;
	Temp.setGameVersion(GenieVersion);
	if(dataset->Civs.size() > 0)
	{
		short FillingCiv = (dataset->Civs.size() > 1) ? 1 : 0;
		Temp.Resources = dataset->Civs[FillingCiv].Resources;
		Temp.UnitPointers = dataset->Civs[FillingCiv].UnitPointers;
		Temp.Units = dataset->Civs[FillingCiv].Units;
	}
	dataset->Civs.insert(dataset->Civs.begin() + CivIDs.front(), Temp);
	OnCivCountChange();
	How2List = INSNEW;
	ListUnits(UnitCivID, false);
}

void AGE_Frame::OnCivsDelete(wxCommandEvent &event)
{
	auto selections = Civs_Civs_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(dataset->Civs, CivIDs);
	OnCivCountChange();
	ListUnits(0, false);
}

void AGE_Frame::OnCivsCopy(wxCommandEvent &event)
{
	auto selections = Civs_Civs_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->Civs, CivIDs, copies.Civ);
	Civs_Civs_ListV->SetFocus();
}

void AGE_Frame::OnCivsPaste(wxCommandEvent &event)
{
	auto selections = Civs_Civs_ListV->GetSelectedItemCount();
	if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToList(dataset->Civs, CivIDs, copies.Civ);
    OnCivCountChange();
    ListUnits(UnitCivID, false);
}

void AGE_Frame::OnCivsPasteInsert(wxCommandEvent &event)
{
	auto selections = Civs_Civs_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(dataset->Civs, CivIDs.front(), copies.Civ);
	OnCivCountChange();
	ListUnits(UnitCivID, false);
}

void AGE_Frame::OnCivCountChange()
{
	short CivCount = dataset->Civs.size();
//	Unit copying fixes.
//	This messes copying if more than one window is opened!
//	copies.Dat.Civs.resize(CivCount);

	if(Units_CivBoxes.size() < CivCount)
	{
		Units_CivBoxes.reserve(CivCount);
		for(size_t loop = Units_CivBoxes.size(); loop < CivCount; ++loop)
		{
			Units_CivBoxes.push_back(new wxCheckBox(Tab_Units, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(30, 20)));
			Units_CivBoxes[loop]->SetValue(true);
			Units_TopGrid_Holder->Add(Units_CivBoxes[loop], 0, wxEXPAND);
			Connect(Units_CivBoxes[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
		}
	}
	else if(Units_CivBoxes.size() > CivCount)
	{
		for(size_t loop = Units_CivBoxes.size(); loop--> CivCount;)
		{
			Units_CivBoxes[loop]->Destroy();
		}
		Units_CivBoxes.resize(CivCount);
	}
	for(size_t loop = 0; loop < CivCount; ++loop)
	{
		if(GenieVersion < genie::GV_SWGB)
		Units_CivBoxes[loop]->SetLabel(dataset->Civs[loop].Name.substr(0, 2));
		else
		Units_CivBoxes[loop]->SetLabel(dataset->Civs[loop].Name2.substr(0, 2));
	}
	ListCivs();
	Units_DataArea->Layout();
	Refresh();
}

wxString AGE_Frame::GetResourceName(int index)
{
    if(GenieVersion < genie::GV_AoKA)
    {
        if(index < RoRCivResources.size())
            return RoRCivResources[index];
        else return "Resource";
    }
    else if(GenieVersion < genie::GV_SWGB)
    {
        if(index < AoKCivResources.size())
            return AoKCivResources[index];
        else return "Resource";
    }
    else
    {
        if(index < SWGBCivResources.size())
            return SWGBCivResources[index];
        else return "Resource";
    }
}

void AGE_Frame::OnResourcesSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListResources(false);
}

void AGE_Frame::ListResources(bool all)
{
	searchText = Civs_Resources_Search->GetValue().MakeLower();
	excludeText = Civs_Resources_Search_R->GetValue().MakeLower();

	Civs_Resources_ListV->names.clear();
	Civs_Resources_ListV->indexes.clear();
	wxArrayString names;
	if(all) names.Alloc(dataset->Civs[CivIDs.front()].Resources.size());

	for(size_t loop = 0; loop < dataset->Civs[CivIDs.front()].Resources.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - Value: "+FormatFloat(dataset->Civs[CivIDs.front()].Resources[loop])+" - "+GetResourceName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Civs_Resources_ListV->names.Add(Name);
			Civs_Resources_ListV->indexes.push_back(loop);
		}
		if(all) names.Add(" "+FormatInt(loop)+" - "+GetResourceName(loop));
	}

	virtualListing(Civs_Resources_ListV);
	if(all) FillLists(ResourceComboBoxList, names);

	wxTimerEvent E;
	OnResourcesTimer(E);
}

void AGE_Frame::OnResourcesSelect(wxCommandEvent &event)
{
    if(!resourceTimer.IsRunning())
        resourceTimer.Start(150);
}

void AGE_Frame::OnResourcesTimer(wxTimerEvent &event)
{
    resourceTimer.Stop();
	auto selections = Civs_Resources_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    getSelectedItems(selections, Civs_Resources_ListV, ResourceIDs);

	Civs_ResourceValue->clear();

	float * CivResourcePointer;
	for(auto loop = selections; loop--> 0;)
	{
		CivResourcePointer = &dataset->Civs[CivIDs.front()].Resources[ResourceIDs[loop]];
		Civs_ResourceValue->prepend(CivResourcePointer);
	}

	Civs_ResourceValue->update();
}

void AGE_Frame::OnResourcesAdd(wxCommandEvent &event)
{
	auto selections = Civs_Civs_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
	dataset->Civs[loop].Resources.push_back(0);
	How2List = ADD;
	ListResources();
}

void AGE_Frame::OnResourcesInsert(wxCommandEvent &event)
{
	auto selections = Civs_Resources_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
	dataset->Civs[loop].Resources.insert(dataset->Civs[loop].Resources.begin() + ResourceIDs.front(), 0);
	How2List = INSNEW;
	ListResources();
}

void AGE_Frame::OnResourcesDelete(wxCommandEvent &event)
{
	auto selections = Civs_Resources_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(size_t loop2 = 0; loop2 < dataset->Civs.size(); ++loop2)
	{
		for(auto loop = selections; loop--> 0;)
		dataset->Civs[loop2].Resources.erase(dataset->Civs[loop2].Resources.begin() + ResourceIDs[loop]);
	}
	How2List = DEL;
	ListResources();
}

void AGE_Frame::OnResourcesCopy(wxCommandEvent &event)
{
	auto selections = Civs_Resources_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(dataset->Civs[CivIDs.front()].Resources, ResourceIDs, copies.Resource);
	Civs_Resources_ListV->SetFocus();
}

void AGE_Frame::OnResourcesPaste(wxCommandEvent &event)
{
	auto selections = Civs_Resources_ListV->GetSelectedItemCount();
	if(selections < 1) return;

    wxBusyCursor WaitCursor;
    PasteToListNoGV(dataset->Civs[CivIDs.front()].Resources, ResourceIDs, copies.Resource, false);
    ListResources();
}

void AGE_Frame::OnResourcesPasteInsert(wxCommandEvent &event)
{
	auto selections = Civs_Resources_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(dataset->Civs[CivIDs.front()].Resources, ResourceIDs.front(), copies.Resource);
	ListResources();
}

void AGE_Frame::OnResourcesCopyToAll(wxCommandEvent &event)
{
	auto selections = Civs_Resources_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(size_t loop = 0; loop < selections; ++loop)
	{
		float Copy = dataset->Civs[CivIDs.front()].Resources[ResourceIDs[loop]];
		for(size_t loop2 = 0; loop2 < dataset->Civs.size(); ++loop2)
		dataset->Civs[loop2].Resources[ResourceIDs[loop]] = Copy;
	}
}

void AGE_Frame::CreateCivControls()
{
	Civs_Main = new wxBoxSizer(wxHORIZONTAL);
	Civs_Civs_Buttons = new wxGridSizer(3, 0, 0);
	Tab_Civs = new wxPanel(TabBar_Main);

	Civs_Civs = new wxStaticBoxSizer(wxVERTICAL, Tab_Civs, "Civilizations");
	Civs_Civs_Search = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Civs_Search_R = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Civs_ListV = new AGEListView(Tab_Civs, wxSize(200, 100));
	Civs_Add = new wxButton(Tab_Civs, wxID_ANY, "Add *", wxDefaultPosition, wxSize(5, 20));
	Civs_Add->SetToolTip("I highly recommend you to download UserPatch\nfrom xOmicron, if you play The Conquerors.\nWith it you can use added civilizations.\nStar Wars versions can already have more civilizations.");
	Civs_Insert = new wxButton(Tab_Civs, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Civs_Delete = new wxButton(Tab_Civs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Civs_Copy = new wxButton(Tab_Civs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Civs_Paste = new wxButton(Tab_Civs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Civs_PasteInsert = new wxButton(Tab_Civs, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	Civs_DataArea = new wxBoxSizer(wxVERTICAL);
	Civs_DataGrid1 = new wxGridSizer(2, 0, 5);
	Civs_DataGrid2 = new wxGridSizer(2, 0, 5);
	Civs_DataGrid3 = new wxGridSizer(2, 0, 0);
	Civs_Name_Holder[0] = new wxBoxSizer(wxVERTICAL);
	Civs_Name_Text[0] = new wxStaticText(Tab_Civs, wxID_ANY, " Name");
	Civs_Name[0] = AGETextCtrl::init(CString, &uiGroupCiv, this, &popUp, Tab_Civs, 20);
	Civs_Name_Holder[1] = new wxBoxSizer(wxVERTICAL);
	Civs_Name_Text[1] = new wxStaticText(Tab_Civs, wxID_ANY, " Name 2");
	Civs_Name[1] = AGETextCtrl::init(CString, &uiGroupCiv, this, &popUp, Tab_Civs, 20);
	Civs_GraphicSet_Holder = new wxBoxSizer(wxVERTICAL);
	Civs_GraphicSet_Text = new wxStaticText(Tab_Civs, wxID_ANY, " Icon Set *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_GraphicSet = AGETextCtrl::init(CByte, &uiGroupCiv, this, &popUp, Tab_Civs);
	Civs_GraphicSet->SetToolTip("Building icon set (and trade cart graphics?)\nThis is actually an offset used to look up SLPs inside the DRS file\nAoE 1: also determines the interface graphics used\nStar Wars: also determines unit and tech icons");
	Civs_One_Holder = new wxBoxSizer(wxVERTICAL);
	Civs_One_Text = new wxStaticText(Tab_Civs, wxID_ANY, " Enabled", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_One = AGETextCtrl::init(CByte, &uiGroupCiv, this, &popUp, Tab_Civs);
	Civs_TechTree_Holder = new wxBoxSizer(wxVERTICAL);
	Civs_TechTree_Text = new wxStaticText(Tab_Civs, wxID_ANY, " Technology Tree", wxDefaultPosition, wxSize(150, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_TechTree = AGETextCtrl::init(CShort, &uiGroupCiv, this, &popUp, Tab_Civs);
	Civs_TechTree_ComboBox = new ComboBox_Plus1(Tab_Civs, Civs_TechTree);
	TechComboBoxList.push_back(Civs_TechTree_ComboBox);
	Civs_TeamBonus_Holder = new wxBoxSizer(wxVERTICAL);
	Civs_TeamBonus_Text = new wxStaticText(Tab_Civs, wxID_ANY, " Team Bonus", wxDefaultPosition, wxSize(150, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_TeamBonus = AGETextCtrl::init(CShort, &uiGroupCiv, this, &popUp, Tab_Civs);
	Civs_TeamBonus_ComboBox = new ComboBox_Plus1(Tab_Civs, Civs_TeamBonus);
	TechComboBoxList.push_back(Civs_TeamBonus_ComboBox);
	Civs_SUnknown1_Holder = new wxBoxSizer(wxVERTICAL);
	Civs_SUnknown1_Text = new wxStaticText(Tab_Civs, wxID_ANY, " Unique Units / Researches", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(size_t loop = 0; loop < 4; ++loop)
	Civs_SUnknown1[loop] = AGETextCtrl::init(CShort, &uiGroupCiv, this, &popUp, Tab_Civs);

	Civs_Resources = new wxStaticBoxSizer(wxVERTICAL, Tab_Civs, "Initial Resources");
	Civs_Resources_Search = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Resources_Search_R = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_ResourceValue_Holder = new wxBoxSizer(wxVERTICAL);
	Civs_ResourceValue_Text = new wxStaticText(Tab_Civs, wxID_ANY, " Resource Value", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_ResourceValue = AGETextCtrl::init(CFloat, NULL, this, &popUp, Tab_Civs);
	Civs_Resources_ListV = new AGEListView(Tab_Civs, wxSize(200, 100));
	Civs_Resources_Buttons = new wxGridSizer(3, 0, 0);
	Resources_Add = new wxButton(Tab_Civs, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Resources_Insert = new wxButton(Tab_Civs, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Resources_Delete = new wxButton(Tab_Civs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Resources_Copy = new wxButton(Tab_Civs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Resources_Paste = new wxButton(Tab_Civs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Resources_PasteInsert = new wxButton(Tab_Civs, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	Resources_CopyToAll = new wxButton(Tab_Civs, wxID_ANY, "Copy to all civs", wxDefaultPosition, wxSize(5, 20));
	Civs_Resources_Data = new wxBoxSizer(wxVERTICAL);

	Civs_Civs_Buttons->Add(Civs_Add, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Delete, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Insert, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Copy, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Paste, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_PasteInsert, 1, wxEXPAND);

	Civs_Civs->Add(Civs_Civs_Search, 0, wxEXPAND);
	Civs_Civs->Add(Civs_Civs_Search_R, 0, wxEXPAND);
	Civs_Civs->Add(Civs_Civs_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Civs_Civs->Add(Civs_Civs_Buttons, 0, wxEXPAND);

	Civs_One_Holder->Add(Civs_One_Text, 0, wxEXPAND);
	Civs_One_Holder->Add(Civs_One, 1, wxEXPAND);
	for(size_t loop = 0; loop < 2; ++loop){
	Civs_Name_Holder[loop]->Add(Civs_Name_Text[loop], 0, wxEXPAND | wxBOTTOM, 2);
	Civs_Name_Holder[loop]->Add(Civs_Name[loop], 1, wxEXPAND);}
	Civs_SUnknown1_Holder->Add(Civs_SUnknown1_Text, 0, wxEXPAND);
	Civs_SUnknown1_Holder->Add(Civs_DataGrid3, 1, wxEXPAND);
	for(size_t loop = 0; loop < 4; ++loop)
	Civs_DataGrid3->Add(Civs_SUnknown1[loop], 1, wxEXPAND);
	Civs_TechTree_Holder->Add(Civs_TechTree_Text, 0, wxEXPAND);
	Civs_TechTree_Holder->Add(Civs_TechTree, 1, wxEXPAND);
	Civs_TechTree_Holder->Add(Civs_TechTree_ComboBox, 1, wxEXPAND);
	Civs_TeamBonus_Holder->Add(Civs_TeamBonus_Text, 0, wxEXPAND);
	Civs_TeamBonus_Holder->Add(Civs_TeamBonus, 1, wxEXPAND);
	Civs_TeamBonus_Holder->Add(Civs_TeamBonus_ComboBox, 1, wxEXPAND);
	Civs_GraphicSet_Holder->Add(Civs_GraphicSet_Text, 0, wxEXPAND);
	Civs_GraphicSet_Holder->Add(Civs_GraphicSet, 1, wxEXPAND);

	Civs_DataGrid1->Add(Civs_GraphicSet_Holder, 1, wxEXPAND);
	Civs_DataGrid1->Add(Civs_One_Holder, 1, wxEXPAND);
	Civs_DataGrid2->Add(Civs_TechTree_Holder, 1, wxEXPAND);
	Civs_DataGrid2->Add(Civs_TeamBonus_Holder, 1, wxEXPAND);

	Civs_DataArea->Add(Civs_Name_Holder[0], 0, wxEXPAND | wxTOP, 5);
	Civs_DataArea->Add(Civs_Name_Holder[1], 0, wxEXPAND);
	Civs_DataArea->Add(Civs_DataGrid1, 0, wxEXPAND | wxTOP, 5);
	Civs_DataArea->Add(Civs_DataGrid2, 0, wxEXPAND | wxTOP, 5);
	Civs_DataArea->Add(Civs_SUnknown1_Holder, 0, wxEXPAND | wxTOP, 5);

	Civs_Resources_Buttons->Add(Resources_Add, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_Delete, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_Insert, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_Copy, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_Paste, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_PasteInsert, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_CopyToAll, 1, wxEXPAND);

	Civs_ResourceValue_Holder->Add(Civs_ResourceValue_Text, 0, wxEXPAND);
	Civs_ResourceValue_Holder->Add(Civs_ResourceValue, 1, wxEXPAND);

	Civs_Resources_Data->Add(Civs_ResourceValue_Holder, 0, wxEXPAND);

	Civs_Resources->Add(Civs_Resources_Search, 0, wxEXPAND);
	Civs_Resources->Add(Civs_Resources_Search_R, 0, wxEXPAND);
	Civs_Resources->Add(Civs_Resources_Data, 0, wxEXPAND);
	Civs_Resources->Add(Civs_Resources_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Civs_Resources->Add(Civs_Resources_Buttons, 0, wxEXPAND);

	Civs_Main->Add(Civs_Civs, 21, wxEXPAND | wxALL, 5);
	Civs_Main->Add(Civs_DataArea, 30, wxEXPAND);
	Civs_Main->Add(Civs_Resources, 30, wxEXPAND | wxALL, 5);

	Tab_Civs->SetSizer(Civs_Main);

	Connect(Civs_Civs_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnCivsSearch));
	Connect(Civs_Civs_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnCivsSearch));
	Connect(Civs_Civs_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnCivsSelect));
	Connect(Civs_Civs_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnCivsSelect));
	Connect(Civs_Civs_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnCivsSelect));
	Connect(Civs_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsAdd));
	Connect(Civs_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsInsert));
	Connect(Civs_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsDelete));
	Connect(Civs_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsCopy));
	Connect(Civs_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsPaste));
	Connect(Civs_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsPasteInsert));
	Connect(Civs_Resources_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResourcesSearch));
	Connect(Civs_Resources_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResourcesSearch));
	Connect(Civs_Resources_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnResourcesSelect));
	Connect(Civs_Resources_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnResourcesSelect));
	Connect(Civs_Resources_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnResourcesSelect));
	Connect(Resources_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesCopy));
	Connect(Resources_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesPaste));
	Connect(Resources_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesPasteInsert));
	Connect(Resources_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesAdd));
	Connect(Resources_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesInsert));
	Connect(Resources_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesDelete));
	Connect(Resources_CopyToAll->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesCopyToAll));

    civTimer.Connect(civTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnCivsTimer), NULL, this);
    resourceTimer.Connect(resourceTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnResourcesTimer), NULL, this);
	for(size_t loop = 0; loop < 2; ++loop)
	Civs_Name[loop]->Connect(Civs_Name[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Civs), NULL, this);
	Civs_GraphicSet->Connect(Civs_GraphicSet->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Civs), NULL, this);
	Civs_ResourceValue->Connect(Civs_ResourceValue->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Civs), NULL, this);
}

void AGE_Frame::OnKillFocus_Civs(wxFocusEvent &event)
{
	event.Skip();
	if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
	if(event.GetId() == Civs_Name[0]->GetId()
	|| event.GetId() == Civs_Name[1]->GetId())
	{
		for(auto const &ID: CivIDs)
		{
			if(GenieVersion < genie::GV_SWGB)
			Units_CivBoxes[ID]->SetLabel(dataset->Civs[ID].Name.substr(0, 2));
			else
			Units_CivBoxes[ID]->SetLabel(dataset->Civs[ID].Name2.substr(0, 2));
		}
		ListCivs();
	}
	else if(event.GetId() == Civs_GraphicSet->GetId())
	{
		ListCivs();
	}
	else if(event.GetId() == Civs_ResourceValue->GetId())
	{
		ListResources();
	}
}
