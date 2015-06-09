#include "../AGE_Frame.h"

string AGE_Frame::GetResearchName(short Index, bool Filter)
{
	string Name = "";
	if(Filter)
	{
		short Selection[2];
		for(short loop = 0; loop < 2; ++loop)
		Selection[loop] = Research_SearchFilters[loop]->GetSelection();

		if(Selection[0] > 1)
		for(short loop = 0; loop < 2; ++loop)
		{
			switch(Selection[loop])
			{
				case 2: // Required Researches
				{
					bool HasFore = false;
					for(short loop = 0; loop < GenieFile->Researchs[Index].getRequiredTechsSize(); ++loop)
					if(GenieFile->Researchs[Index].RequiredTechs[loop] != -1)
					{
						if(HasFore) Name += ", R"; else {Name += "R"; HasFore = true;}
						Name += lexical_cast<string>(GenieFile->Researchs[Index].RequiredTechs[loop]);
					}
				}	break;
				case 3: // Min. Req. Researches
					Name += "MR "+lexical_cast<string>(GenieFile->Researchs[Index].RequiredTechCount);
					break;
				case 4: // Research Location
					Name += "RL "+lexical_cast<string>(GenieFile->Researchs[Index].ResearchLocation);
					break;
				case 5: // Research Time
					Name += "RT "+lexical_cast<string>(GenieFile->Researchs[Index].ResearchTime);
					break;
				case 6: // Technology
					Name += "Te "+lexical_cast<string>(GenieFile->Researchs[Index].TechageID);
					break;
				case 7: // Type
					Name += "T "+lexical_cast<string>(GenieFile->Researchs[Index].Type);
					break;
				case 8: // Icon
					Name += "I "+lexical_cast<string>(GenieFile->Researchs[Index].IconID);
					break;
				case 9: // Button
					Name += "B "+lexical_cast<string>((short)GenieFile->Researchs[Index].ButtonID);
					break;
				case 10: // Lang DLL Pointer
					Name += "LP "+lexical_cast<string>(GenieFile->Researchs[Index].LanguageDLLHelp);
					break;
				case 11: // Pointer 2
					Name += "P2 "+lexical_cast<string>(GenieFile->Researchs[Index].LanguageDLLName2);
					break;
				case 12: // Pointer 3
					Name += "P3 "+lexical_cast<string>(GenieFile->Researchs[Index].Unknown1);
					break;
				case 13: // Cost Types
				{
					bool HasFore = false;
					for(short loop = 0; loop < 3; ++loop)
					if(GenieFile->Researchs[Index].ResourceCosts[loop].Type != -1)
					{
						if(HasFore) Name += ", CT"; else {Name += "CT"; HasFore = true;}
						Name += lexical_cast<string>(GenieFile->Researchs[Index].ResourceCosts[loop].Type);
					}
				}	break;
				case 14: // Cost Amounts
				{
					bool HasFore = false;
					for(short loop = 0; loop < 3; ++loop)
					{
						if(HasFore) Name += ", CA"; else {Name += "CA"; HasFore = true;}
						Name += lexical_cast<string>(GenieFile->Researchs[Index].ResourceCosts[loop].Amount);
					}
				}	break;
				case 15: // Cost Uses
				{
					bool HasFore = false;
					for(short loop = 0; loop < 3; ++loop)
					{
						if(HasFore) Name += ", CU"; else {Name += "CU"; HasFore = true;}
						Name += lexical_cast<string>((short)GenieFile->Researchs[Index].ResourceCosts[loop].Enabled);
					}
				}	break;
				if(GenieVersion >= genie::GV_AoKB)
				{
				case 16: // Civilization
					Name += "C "+lexical_cast<string>(GenieFile->Researchs[Index].Civ);
					break;
				case 17: // Full Tech. Mode
					Name += "F "+lexical_cast<string>(GenieFile->Researchs[Index].FullTechMode);
					break;
				if(GenieVersion >= genie::GV_SWGB)
				{
				case 18: // Internal Name 2
					if(!GenieFile->Researchs[Index].Name2.empty())
					return Name + GenieFile->Researchs[Index].Name2;
					else goto InternalName;
				}
				}
			}
			Name += ", ";
			if(Selection[loop+1] < 2) break;
		}
		if(Selection[0] == 1) goto InternalName;
	}

	if(!LangDLLstring(GenieFile->Researchs[Index].LanguageDLLName, 2).empty())
	{
		return Name + LangDLLstring(GenieFile->Researchs[Index].LanguageDLLName, 64);
	}
InternalName:
	if(!GenieFile->Researchs[Index].Name.empty())
	{
		return Name + GenieFile->Researchs[Index].Name;
	}
	return Name + "New Research";
}

void AGE_Frame::OnResearchSearch(wxCommandEvent &Event)
{
	FirstVisible = 0;
	ListResearches(false);
}

void AGE_Frame::ListResearches(bool all)
{
	InitResearches(all);
	wxCommandEvent E;
	OnResearchSelect(E);
}

void AGE_Frame::InitResearches(bool all)
{
	searchText = Research_Research_Search->GetValue().Lower();
	excludeText = Research_Research_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = Research_Research_UseAnd[loop]->GetValue();

	list<void*> dataPointers;
	wxArrayString filteredNames;
	if(all)
	{
		AGE_AreaTT84::researches.Clear();
		AGE_AreaTT84::researches.Alloc(GenieFile->Researchs.size());
	}

	for(short loop = 0; loop < GenieFile->Researchs.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetResearchName(loop, true);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->Researchs[loop]);
		}
		if(all) AGE_AreaTT84::researches.Add(" "+FormatInt(loop)+" - "+GetResearchName(loop));
	}

	Listing(Research_Research_List, filteredNames, dataPointers);
	if(all)
	{
		FillLists(ResearchComboBoxList, AGE_AreaTT84::researches);
		if(GenieVersion >= genie::GV_AoKA)
		{
			TechTrees_Ages_Items.FillItemCombo(TechTrees_Ages_Items.ItemCombo->GetSelection(), true);
			TechTrees_Buildings_Items.FillItemCombo(TechTrees_Buildings_Items.ItemCombo->GetSelection(), true);
			TechTrees_Units_Items.FillItemCombo(TechTrees_Units_Items.ItemCombo->GetSelection(), true);
			TechTrees_Researches_Items.FillItemCombo(TechTrees_Researches_Items.ItemCombo->GetSelection(), true);
		}
	}

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;
}

void AGE_Frame::OnResearchSelect(wxCommandEvent &Event)
{
	// If trying to select an existing item, don't deselect?
	auto selections = Research_Research_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	// To show contents of last selected item instead of first selection.
	int lastSelection = Event.GetSelection();
	// Look if selections include the last selection.
	int found = FindItem(Items, lastSelection, 0, Items.GetCount() - 1);
	// Swap last selection with the first one.
	if(found != -1)
	{
		int swap = Items.Item(found);
		Items.RemoveAt(found);
		Items.Insert(swap, 0);
	}

	ResearchIDs.resize(selections);
	for(short loop2 = 0; loop2 < GenieFile->Researchs[0].getRequiredTechsSize(); ++loop2)
	{
		Research_RequiredTechs[loop2]->resize(selections);
	}
	Research_RequiredTechCount->resize(selections);
	Research_Resources[0]->resize(selections);
	Research_Resources[1]->resize(selections);
	Research_Resources[2]->resize(selections);
	Research_Amount[0]->resize(selections);
	Research_Amount[1]->resize(selections);
	Research_Amount[2]->resize(selections);
	Research_Used[0]->resize(selections);
	Research_Used[1]->resize(selections);
	Research_Used[2]->resize(selections);
	if(GenieVersion >= genie::GV_AoKB)
	{
		Research_Civ->resize(selections);
		Research_FullTechMode->resize(selections);
		if(GenieVersion >= genie::GV_SWGB)
		Research_Name[1]->resize(selections);
	}
	Research_ResearchLocation->resize(selections);
	if(GenieVersion >= genie::GV_MATT)
	{
		Research_LangDLLName->resize(selections);
		Research_LangDLLDescription->resize(selections);
	}
	Research_ResearchTime->resize(selections);
	Research_TechID->resize(selections);
	Research_Type->resize(selections);
	Research_IconID->resize(selections);
	Research_ButtonID->resize(selections);
	if(GenieVersion >= genie::GV_AoEB)
	{
		Research_LanguageDLLHelp->resize(selections);
		Research_LanguageDLLName2->resize(selections);
		Research_Unknown1->resize(selections);
	}
	Research_Name[0]->resize(selections);

	genie::Research * ResearchPointer;
	for(auto loop = selections; loop--> 0;)
	{
		ResearchPointer = (genie::Research*)Research_Research_List->GetClientData(Items.Item(loop));
		ResearchIDs[loop] = (ResearchPointer - (&GenieFile->Researchs[0]));

		for(short loop2 = 0; loop2 < ResearchPointer->getRequiredTechsSize(); ++loop2)
		{
			Research_RequiredTechs[loop2]->container[loop] = &ResearchPointer->RequiredTechs[loop2];
		}
		Research_RequiredTechCount->container[loop] = &ResearchPointer->RequiredTechCount;
		Research_Resources[0]->container[loop] = &ResearchPointer->ResourceCosts[0].Type;
		Research_Resources[1]->container[loop] = &ResearchPointer->ResourceCosts[1].Type;
		Research_Resources[2]->container[loop] = &ResearchPointer->ResourceCosts[2].Type;
		Research_Amount[0]->container[loop] = &ResearchPointer->ResourceCosts[0].Amount;
		Research_Amount[1]->container[loop] = &ResearchPointer->ResourceCosts[1].Amount;
		Research_Amount[2]->container[loop] = &ResearchPointer->ResourceCosts[2].Amount;
		Research_Used[0]->container[loop] = &ResearchPointer->ResourceCosts[0].Enabled;
		Research_Used[1]->container[loop] = &ResearchPointer->ResourceCosts[1].Enabled;
		Research_Used[2]->container[loop] = &ResearchPointer->ResourceCosts[2].Enabled;
		if(GenieVersion >= genie::GV_AoKB)
		{
			Research_Civ->container[loop] = &ResearchPointer->Civ;
			Research_FullTechMode->container[loop] = &ResearchPointer->FullTechMode;
			if(GenieVersion >= genie::GV_SWGB)
			Research_Name[1]->container[loop] = &ResearchPointer->Name2;
		}
		Research_ResearchLocation->container[loop] = &ResearchPointer->ResearchLocation;
		if(GenieVersion >= genie::GV_MATT)
		{
			Research_LangDLLName->container[loop] = &ResearchPointer->LanguageDLLName;
			Research_LangDLLDescription->container[loop] = &ResearchPointer->LanguageDLLDescription;
		}
		Research_ResearchTime->container[loop] = &ResearchPointer->ResearchTime;
		Research_TechID->container[loop] = &ResearchPointer->TechageID;
		Research_Type->container[loop] = &ResearchPointer->Type;
		Research_IconID->container[loop] = &ResearchPointer->IconID;
		Research_ButtonID->container[loop] = &ResearchPointer->ButtonID;
		if(GenieVersion >= genie::GV_AoEB)
		{
			Research_LanguageDLLHelp->container[loop] = &ResearchPointer->LanguageDLLHelp;
			Research_LanguageDLLName2->container[loop] = &ResearchPointer->LanguageDLLName2;
			Research_Unknown1->container[loop] = &ResearchPointer->Unknown1;
		}
		Research_Name[0]->container[loop] = &ResearchPointer->Name;
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected research: "+lexical_cast<string>(ResearchIDs[0]), 0);

	for(short loop = 0; loop < ResearchPointer->getRequiredTechsSize(); ++loop)
	{
		Research_RequiredTechs[loop]->Update();
	}
	Research_RequiredTechCount->Update();
	Research_Resources[0]->Update();
	Research_Resources[1]->Update();
	Research_Resources[2]->Update();
	Research_Amount[0]->Update();
	Research_Amount[1]->Update();
	Research_Amount[2]->Update();
	Research_Used[0]->Update();
	Research_Used[1]->Update();
	Research_Used[2]->Update();
	if(GenieVersion >= genie::GV_AoKB)
	{
		Research_Civ->Update();
		Research_FullTechMode->Update();
		Research_DLL_LanguageDLLHelp->index = ResearchPointer->LanguageDLLHelp - 79000;
		Research_DLL_LanguageDLLName2->index = ResearchPointer->LanguageDLLName2 - 140000;
		if(GenieVersion >= genie::GV_SWGB)
		Research_Name[1]->Update();
	}
	else
	{
		Research_DLL_LanguageDLLHelp->index = (uint16_t)ResearchPointer->LanguageDLLHelp;
		Research_DLL_LanguageDLLName2->index = (uint16_t)ResearchPointer->LanguageDLLName2;
	}
	Research_ResearchLocation->Update();
	if(GenieVersion >= genie::GV_MATT)
	{
		Research_LangDLLName->Update();
		Research_DLL_LangDLLName->index = ResearchPointer->LanguageDLLName;
		Research_DLL_LangDLLName->SetLabel(LangDLLstring(ResearchPointer->LanguageDLLName, 64));
		Research_LangDLLDescription->Update();
		Research_DLL_LangDLLDescription->index = ResearchPointer->LanguageDLLDescription;
		Research_DLL_LangDLLDescription->SetLabel(LangDLLstring(ResearchPointer->LanguageDLLDescription, 128));
	}
	Research_ResearchTime->Update();
	Research_TechID->Update();
	Research_Type->Update();
	Research_IconID->Update();
	Research_ButtonID->Update();
	if(GenieVersion >= genie::GV_AoEB)
	{
		Research_LanguageDLLHelp->Update();
		Research_DLL_LanguageDLLHelp->SetLabel(LangDLLstring(Research_DLL_LanguageDLLHelp->index, 64));
		Research_LanguageDLLConverter[0]->SetLabel(lexical_cast<string>(Research_DLL_LanguageDLLHelp->index));
		Research_LanguageDLLName2->Update();
		Research_DLL_LanguageDLLName2->SetLabel(LangDLLstring(Research_DLL_LanguageDLLName2->index, 64));
		Research_LanguageDLLConverter[1]->SetLabel(lexical_cast<string>(Research_DLL_LanguageDLLName2->index));
		Research_Unknown1->Update();
	}
	Research_Name[0]->Update();
}

void AGE_Frame::OnResearchAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->Researchs);
	ListResearches();
}

void AGE_Frame::OnResearchInsert(wxCommandEvent &Event)
{
	auto selections = Research_Research_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	FirstVisible = Research_Research_List->HitTest(wxPoint(0, 0));
	InsertToList(GenieFile->Researchs, ResearchIDs[0]);
	ListResearches();
}

void AGE_Frame::OnResearchDelete(wxCommandEvent &Event)
{
	auto selections = Research_Research_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	FirstVisible = Research_Research_List->HitTest(wxPoint(0, 0));
	DeleteFromList(GenieFile->Researchs, ResearchIDs);
	ListResearches();
}

void AGE_Frame::OnResearchCopy(wxCommandEvent &Event)
{
	auto selections = Research_Research_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Researchs, ResearchIDs, copies->Research);
}

void AGE_Frame::OnResearchPaste(wxCommandEvent &Event)
{
	auto selections = Research_Research_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(ResearchIDs.size(), copies->Research.size()))
		{
			PasteToList(GenieFile->Researchs, ResearchIDs, copies->Research);
		}
	}
	else
	{
		PasteToList(GenieFile->Researchs, ResearchIDs[0], copies->Research);
	}
	FirstVisible = Research_Research_List->HitTest(wxPoint(0, 0));
	ListResearches();
}

void AGE_Frame::OnResearchPasteInsert(wxCommandEvent &Event)
{
	auto selections = Research_Research_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	FirstVisible = Research_Research_List->HitTest(wxPoint(0, 0));
	PasteInsertToList(GenieFile->Researchs, ResearchIDs[0], copies->Research);
	ListResearches();
}

void AGE_Frame::ResearchLangDLLConverter(wxCommandEvent &Event)
{
	int32_t DLLValue;
	try
	{
		DLLValue = lexical_cast<int32_t>(((wxTextCtrl*)Event.GetEventObject())->GetValue());
	}
	catch(bad_lexical_cast e)
	{
		wxMessageBox("Incorrect input!");
		return;
	}
	if(Event.GetId() == Research_LanguageDLLConverter[0]->GetId())
	{
		if(GenieVersion < genie::GV_AoKA) DLLValue += 0x10000;
		else DLLValue += 79000;
		GenieFile->Researchs[ResearchIDs[0]].LanguageDLLHelp = DLLValue;
	}
	else
	{
		if(GenieVersion < genie::GV_AoKA) DLLValue += 0x20000;
		else DLLValue += 140000;
		GenieFile->Researchs[ResearchIDs[0]].LanguageDLLName2 = DLLValue;
	}
	wxCommandEvent E;
	OnResearchSelect(E);
}

void AGE_Frame::CreateResearchControls()
{
	wxString langGlobalAnd, langGlobalAdd, langGlobalInsNew, langGlobalDel,	langGlobalCopy, langGlobalPaste, langGlobalInsCopies, langGlobalName;
	wxString langTabResearch;

	wxFileConfig Translations(wxEmptyString, "Tapsa", "age3trans.txt", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	Translations.Read("Global/And", &langGlobalAnd, "And");
	Translations.Read("Global/Add", &langGlobalAdd, "Add");
	Translations.Read("Global/InsertNew", &langGlobalInsNew, "Insert New");
	Translations.Read("Global/Delete", &langGlobalDel, "Delete");
	Translations.Read("Global/Copy", &langGlobalCopy, "Copy");
	Translations.Read("Global/Paste", &langGlobalPaste, "Paste");
	Translations.Read("Global/InsertCopies", &langGlobalInsCopies, "Ins Copies");
	Translations.Read("Research/Tab", &langTabResearch, "Researches");
	Translations.Read("Global/Name", &langGlobalName, "Name");

	Tab_Research = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Research_Main = new wxBoxSizer(wxHORIZONTAL);
	Research_ListArea = new wxBoxSizer(wxVERTICAL);
	Research_Research = new wxStaticBoxSizer(wxVERTICAL, Tab_Research, langTabResearch);
	Research_Research_Search = new wxTextCtrl(Tab_Research, wxID_ANY);
	Research_Research_UseAnd[0] = new wxCheckBox(Tab_Research, wxID_ANY, langGlobalAnd, wxDefaultPosition, wxSize(40, 20));
	Research_Research_Search_R = new wxTextCtrl(Tab_Research, wxID_ANY);
	Research_Research_UseAnd[1] = new wxCheckBox(Tab_Research, wxID_ANY, langGlobalAnd, wxDefaultPosition, wxSize(40, 20));
	for(short loop = 0; loop < 2; ++loop)
	{
		Research_Research_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Research_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_Research, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	Research_Research_List = new wxListBox(Tab_Research, wxID_ANY, wxDefaultPosition, wxSize(200, 100), 0, NULL, wxLB_EXTENDED);
	Research_Research_Buttons = new wxGridSizer(3, 0, 0);
	Research_Add = new wxButton(Tab_Research, wxID_ANY, langGlobalAdd, wxDefaultPosition, wxSize(5, 20));
	Research_Insert = new wxButton(Tab_Research, wxID_ANY, langGlobalInsNew, wxDefaultPosition, wxSize(5, 20));
	Research_Delete = new wxButton(Tab_Research, wxID_ANY, langGlobalDel, wxDefaultPosition, wxSize(5, 20));
	Research_Copy = new wxButton(Tab_Research, wxID_ANY, langGlobalCopy, wxDefaultPosition, wxSize(5, 20));
	Research_Paste = new wxButton(Tab_Research, wxID_ANY, langGlobalPaste, wxDefaultPosition, wxSize(5, 20));
	Research_PasteInsert = new wxButton(Tab_Research, wxID_ANY, langGlobalInsCopies, wxDefaultPosition, wxSize(5, 20));

	Research_DataArea = new wxBoxSizer(wxVERTICAL);
	Research_Scroller = new wxScrolledWindow(Tab_Research, wxID_ANY, wxDefaultPosition, wxSize(600, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Research_ScrollArea = new wxBoxSizer(wxHORIZONTAL);
	Research_ScrollSpace = new wxBoxSizer(wxVERTICAL);
	Research_Name_Holder[0] = new wxBoxSizer(wxVERTICAL);
	Research_Name_Text[0] = new wxStaticText(Research_Scroller, wxID_ANY, " "+langGlobalName, wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Name[0] = new TextCtrl_String(this, AGEwindow, Research_Scroller, 30);
	Research_Name_Holder[1] = new wxBoxSizer(wxVERTICAL);
	Research_Name_Text[1] = new wxStaticText(Research_Scroller, wxID_ANY, " "+langGlobalName+" 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Name[1] = new TextCtrl_String(this, AGEwindow, Research_Scroller, 30);
	Research_LangDLLName_Holder = new wxBoxSizer(wxVERTICAL);
	Research_LangDLLName_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Language DLL "+langGlobalName+" *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_LangDLLName = new TextCtrl_UShort(this, AGEwindow, Research_Scroller);
	Research_LangDLLName->SetToolTip("Usual Research DLL Pattern for The Conquerors\nName: 7000-7999\nDescription: Name +1000\nPopup: Name +100000, in DLL Name +21000\nHelp: Name +150000, in DLL Name +10000");
	Research_DLL_LangDLLName = new TextCtrl_DLL(Research_Scroller, wxSize(0, 35));
	Research_LangDLLDescription_Holder = new wxBoxSizer(wxVERTICAL);
	Research_LangDLLDescription_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Language DLL Description", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_LangDLLDescription = new TextCtrl_UShort(this, AGEwindow, Research_Scroller);
	Research_DLL_LangDLLDescription = new TextCtrl_DLL(Research_Scroller, wxSize(0, 35));
	Research_RequiredTechArea_Holder = new wxBoxSizer(wxVERTICAL);
	Research_RequiredTechs_Holder = new wxGridSizer(6, 0, 5);
	Research_RequiredTechArea_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Required Researches", wxDefaultPosition, wxSize(630, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_MiscArea1_Grid = new wxGridSizer(5, 0, 5);
	Research_LangDLLArea_Holder = new wxBoxSizer(wxHORIZONTAL);
	Research_Misc2_Holder = new wxGridSizer(5, 0, 5);
	Research_PointerArea_Holder = new wxGridSizer(5, 0, 5);
	Research_Names_Holder = new wxBoxSizer(wxHORIZONTAL);

	for(short loop = 0; loop < 6; ++loop)
	{
		Research_RequiredTechs[loop] = new TextCtrl_Short(this, AGEwindow, Research_Scroller);
		Research_RequiredTechs_ComboBox[loop] = new ComboBox_Plus1(Research_Scroller, Research_RequiredTechs[loop]);
		ResearchComboBoxList.push_back(Research_RequiredTechs_ComboBox[loop]);
	}
	Research_TechID_Holder = new wxBoxSizer(wxVERTICAL);
	Research_TechID_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Technology", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_TechID = new TextCtrl_Short(this, AGEwindow, Research_Scroller);
	Research_TechID_ComboBox = new ComboBox_Plus1(Research_Scroller, Research_TechID);
	TechComboBoxList.push_back(Research_TechID_ComboBox);
	Research_ResearchLocation_Holder = new wxBoxSizer(wxVERTICAL);
	Research_ResearchLocation_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Research Location", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_ResearchLocation = new TextCtrl_Short(this, AGEwindow, Research_Scroller);
	Research_ResearchLocation_ComboBox = new ComboBox_Plus1(Research_Scroller, Research_ResearchLocation);
	UnitComboBoxList.push_back(Research_ResearchLocation_ComboBox);
	Research_Civ_Holder = new wxBoxSizer(wxVERTICAL);
	Research_Civ_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Civilization", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Civ = new TextCtrl_Short(this, AGEwindow, Research_Scroller);
	Research_Civ_ComboBox = new ComboBox_Plus1(Research_Scroller, Research_Civ);
	CivComboBoxList.push_back(Research_Civ_ComboBox);
	Research_FullTechMode_Holder = new wxBoxSizer(wxVERTICAL);
	Research_FullTechMode_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Full Tech. Mode", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_FullTechMode = new TextCtrl_Short(this, AGEwindow, Research_Scroller);
	Research_FullTechMode_CheckBox = new CheckBox_2State(Research_Scroller, "Available", Research_FullTechMode);
	Research_RequiredTechCount_Holder = new wxBoxSizer(wxVERTICAL);
	Research_RequiredTechCount_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Min Req Researches", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_RequiredTechCount = new TextCtrl_Short(this, AGEwindow, Research_Scroller);
	Research_Type_Holder = new wxBoxSizer(wxVERTICAL);
	Research_Type_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Type *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Type = new TextCtrl_Short(this, AGEwindow, Research_Scroller);
	Research_Type->SetToolTip("0 Normal\n2 Show progress in age bar\nAoE/RoR usages:\n1 = dock\n2 = granary\n3 = temple\n4 = market\n5 = government center\n6 = storage pit\n7 = siege workshop\n8 = archery range\n9 = barracks\n10 = stable\n11 = academy\n12 = town center");
	Research_ResearchTime_Holder = new wxBoxSizer(wxVERTICAL);
	Research_ResearchTime_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Research Time", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_ResearchTime = new TextCtrl_Short(this, AGEwindow, Research_Scroller);
	Research_IconID_Holder = new wxBoxSizer(wxVERTICAL);
	Research_IconID_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Icon", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_IconID = new TextCtrl_Short(this, AGEwindow, Research_Scroller);
	Research_ButtonID_Holder = new wxBoxSizer(wxVERTICAL);
	Research_ButtonID_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Button", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_ButtonID = new TextCtrl_Byte(this, AGEwindow, Research_Scroller);

	Research_CostHeader_Holder = new wxStaticBoxSizer(wxVERTICAL, Research_Scroller, "Costs");
	Research_CostType_Holder = new wxBoxSizer(wxHORIZONTAL);
	Research_CostAmount_Holder = new wxBoxSizer(wxHORIZONTAL);
	Research_CostUsed_Holder = new wxBoxSizer(wxHORIZONTAL);
	Research_Resources_Text = new wxStaticText(Research_Scroller, wxID_ANY, "Cost Type ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Research_Amount_Text = new wxStaticText(Research_Scroller, wxID_ANY, "Cost Amount ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Research_Used_Text = new wxStaticText(Research_Scroller, wxID_ANY, "Cost Used ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Research_ResourceGrid1 = new wxGridSizer(3, 0, 5);
	Research_ResourceGrid2 = new wxGridSizer(3, 0, 5);
	for(short loop = 0; loop < 3; ++loop)
	{
		Research_ResourceGrid[loop] = new wxBoxSizer(wxHORIZONTAL);
		Research_Resources[loop] = new TextCtrl_Short(this, AGEwindow, Research_Scroller);
		Research_Resources_ComboBox[loop] = new ComboBox_Plus1(Research_Scroller, Research_Resources[loop]);
		ResourceComboBoxList.push_back(Research_Resources_ComboBox[loop]);
		Research_Amount[loop] = new TextCtrl_Short(this, AGEwindow, Research_Scroller);
		Research_Used[loop] = new TextCtrl_Byte(this, AGEwindow, Research_Scroller);
		Research_Used_CheckBox[loop] = new CheckBox_2State(Research_Scroller, "Used", Research_Used[loop]);
	}

	Research_LanguageDLLHelp_Holder = new wxBoxSizer(wxVERTICAL);
	Research_LanguageDLLName2_Holder = new wxBoxSizer(wxVERTICAL);
	Research_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	Research_LanguageDLLHelp_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Lang DLL Popup *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_LanguageDLLHelp = new TextCtrl_Long(this, AGEwindow, Research_Scroller);
	Research_LanguageDLLHelp->SetToolTip("100000 + Language DLL Name");
	Research_LanguageDLLConverter_Holder[0] = new wxBoxSizer(wxVERTICAL);
	Research_LanguageDLLConverter_Text[0] = new wxStaticText(Research_Scroller, wxID_ANY, " Popup Converter *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_LanguageDLLConverter[0] = new wxTextCtrl(Research_Scroller, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Research_LanguageDLLConverter[0]->SetToolTip("Language popup text in DLL\nHit enter to get the correction into dat file");
	Research_DLL_LanguageDLLHelp = new TextCtrl_DLL(Research_Scroller, wxSize(0, 35));
	Research_LanguageDLLName2_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Lang DLL Help *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_LanguageDLLName2 = new TextCtrl_Long(this, AGEwindow, Research_Scroller);
	Research_LanguageDLLName2->SetToolTip("150000 + Language DLL Name");
	Research_LanguageDLLConverter_Holder[1] = new wxBoxSizer(wxVERTICAL);
	Research_LanguageDLLConverter_Text[1] = new wxStaticText(Research_Scroller, wxID_ANY, " Help Converter *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_LanguageDLLConverter[1] = new wxTextCtrl(Research_Scroller, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Research_LanguageDLLConverter[1]->SetToolTip("Language help text in DLL\nHit enter to get the correction into dat file");
	Research_DLL_LanguageDLLName2 = new TextCtrl_DLL(Research_Scroller, wxSize(0, 20));
	Research_Unknown1_Text = new wxStaticText(Research_Scroller, wxID_ANY, " Pointer 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Unknown1 = new TextCtrl_Long(this, AGEwindow, Research_Scroller);
	
	Translations.Write("Global/And", langGlobalAnd);
	Translations.Write("Global/Add", langGlobalAdd);
	Translations.Write("Global/InsertNew", langGlobalInsNew);
	Translations.Write("Global/Delete", langGlobalDel);
	Translations.Write("Global/Copy", langGlobalCopy);
	Translations.Write("Global/Paste", langGlobalPaste);
	Translations.Write("Global/InsertCopies", langGlobalInsCopies);
	Translations.Write("Research/Tab", langTabResearch);
	Translations.Write("Global/Name", langGlobalName);

	Research_Research_Buttons->Add(Research_Add, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_Delete, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_Insert, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_Copy, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_Paste, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_PasteInsert, 1, wxEXPAND);

	Research_Research_Searches[0]->Add(Research_Research_Search, 1, wxEXPAND);
	Research_Research_Searches[0]->AddSpacer(2);
	Research_Research_Searches[0]->Add(Research_Research_UseAnd[0], 0, wxEXPAND);
	Research_Research_Searches[1]->Add(Research_Research_Search_R, 1, wxEXPAND);
	Research_Research_Searches[1]->AddSpacer(2);
	Research_Research_Searches[1]->Add(Research_Research_UseAnd[1], 0, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Research_Research->Add(Research_Research_Searches[loop], 0, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Research_Research->Add(Research_SearchFilters[loop], 0, wxEXPAND);
	Research_Research->AddSpacer(2);
	Research_Research->Add(Research_Research_List, 1, wxEXPAND);
	Research_Research->AddSpacer(2);
	Research_Research->Add(Research_Research_Buttons, 0, wxEXPAND);

	Research_ListArea->AddSpacer(5);
	Research_ListArea->Add(Research_Research, 1, wxEXPAND);
	Research_ListArea->AddSpacer(5);

	for(short loop = 0; loop < 2; ++loop)
	{
		Research_Name_Holder[loop]->Add(Research_Name_Text[loop], 0, wxEXPAND);
		Research_Name_Holder[loop]->Add(Research_Name[loop], 1, wxEXPAND);
	}

	Research_Names_Holder->Add(Research_Name_Holder[0], 2, wxEXPAND);
	Research_Names_Holder->AddSpacer(5);
	Research_Names_Holder->Add(Research_Name_Holder[1], 2, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Research_LangDLLName_Holder->Add(Research_LangDLLName_Text, 0, wxEXPAND);
	Research_LangDLLName_Holder->Add(Research_LangDLLName, 0, wxEXPAND);
	Research_LangDLLName_Holder->Add(Research_DLL_LangDLLName, 0, wxEXPAND);
	Research_LangDLLDescription_Holder->Add(Research_LangDLLDescription_Text, 0, wxEXPAND);
	Research_LangDLLDescription_Holder->Add(Research_LangDLLDescription, 0, wxEXPAND);
	Research_LangDLLDescription_Holder->Add(Research_DLL_LangDLLDescription, 0, wxEXPAND);

	Research_LangDLLArea_Holder->Add(Research_LangDLLName_Holder, 1, wxEXPAND);
	Research_LangDLLArea_Holder->AddSpacer(5);
	Research_LangDLLArea_Holder->Add(Research_LangDLLDescription_Holder, 1, wxEXPAND);

	Research_CostUsed_Holder->Add(Research_Used_Text, 1, wxEXPAND);
	for(short loop = 0; loop < 3; ++loop)
	{
		Research_ResourceGrid[loop]->Add(Research_Used[loop], 0, wxEXPAND);
		Research_ResourceGrid[loop]->AddSpacer(5);
		Research_ResourceGrid[loop]->Add(Research_Used_CheckBox[loop], 1, wxEXPAND);
		Research_CostUsed_Holder->Add(Research_ResourceGrid[loop], 2, wxEXPAND);
		Research_ResourceGrid1->Add(Research_Resources[loop], 1, wxEXPAND);
	}
	for(short loop = 0; loop < 3; ++loop)
	{
		Research_ResourceGrid1->Add(Research_Resources_ComboBox[loop], 1, wxEXPAND);
		Research_ResourceGrid2->Add(Research_Amount[loop], 2, wxEXPAND);
	}

	Research_CostType_Holder->Add(Research_Resources_Text, 1, wxEXPAND);
	Research_CostType_Holder->Add(Research_ResourceGrid1, 6, wxEXPAND);
	Research_CostAmount_Holder->Add(Research_Amount_Text, 1, wxEXPAND);
	Research_CostAmount_Holder->Add(Research_ResourceGrid2, 6, wxEXPAND);

	Research_CostHeader_Holder->Add(Research_CostType_Holder, 0, wxEXPAND);
	Research_CostHeader_Holder->AddSpacer(5);
	Research_CostHeader_Holder->Add(Research_CostAmount_Holder, 0, wxEXPAND);
	Research_CostHeader_Holder->AddSpacer(5);
	Research_CostHeader_Holder->Add(Research_CostUsed_Holder, 0, wxEXPAND);

	for(short loop = 0; loop < 6; ++loop)
	Research_RequiredTechs_Holder->Add(Research_RequiredTechs[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 6; ++loop)
	Research_RequiredTechs_Holder->Add(Research_RequiredTechs_ComboBox[loop], 1, wxEXPAND);

	Research_RequiredTechArea_Holder->Add(Research_RequiredTechArea_Text, 0, wxEXPAND);
	Research_RequiredTechArea_Holder->Add(Research_RequiredTechs_Holder, 0, wxEXPAND);

	Research_RequiredTechCount_Holder->Add(Research_RequiredTechCount_Text, 0, wxEXPAND);
	Research_RequiredTechCount_Holder->Add(Research_RequiredTechCount, 1, wxEXPAND);

	Research_Civ_Holder->Add(Research_Civ_Text, 0, wxEXPAND);
	Research_Civ_Holder->Add(Research_Civ, 1, wxEXPAND);
	Research_Civ_Holder->Add(Research_Civ_ComboBox, 1, wxEXPAND);

	Research_FullTechMode_Holder->Add(Research_FullTechMode_Text, 0, wxEXPAND);
	Research_FullTechMode_Holder->Add(Research_FullTechMode, 1, wxEXPAND);
	Research_FullTechMode_Holder->Add(Research_FullTechMode_CheckBox, 1, wxEXPAND);

	Research_ResearchLocation_Holder->Add(Research_ResearchLocation_Text, 0, wxEXPAND);
	Research_ResearchLocation_Holder->Add(Research_ResearchLocation, 1, wxEXPAND);
	Research_ResearchLocation_Holder->Add(Research_ResearchLocation_ComboBox, 1, wxEXPAND);

	Research_MiscArea1_Grid->Add(Research_TechID_Holder, 1, wxEXPAND);
	Research_MiscArea1_Grid->Add(Research_ResearchLocation_Holder, 1, wxEXPAND);
	Research_MiscArea1_Grid->Add(Research_Civ_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Research_MiscArea1_Grid->Add(Research_FullTechMode_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Research_ResearchTime_Holder->Add(Research_ResearchTime_Text, 0, wxEXPAND);
	Research_ResearchTime_Holder->Add(Research_ResearchTime, 1, wxEXPAND);

	Research_TechID_Holder->Add(Research_TechID_Text, 0, wxEXPAND);
	Research_TechID_Holder->Add(Research_TechID, 1, wxEXPAND);
	Research_TechID_Holder->Add(Research_TechID_ComboBox, 1, wxEXPAND);

	Research_Type_Holder->Add(Research_Type_Text, 0, wxEXPAND);
	Research_Type_Holder->Add(Research_Type, 1, wxEXPAND);

	Research_IconID_Holder->Add(Research_IconID_Text, 0, wxEXPAND);
	Research_IconID_Holder->Add(Research_IconID, 1, wxEXPAND);

	Research_ButtonID_Holder->Add(Research_ButtonID_Text, 0, wxEXPAND);
	Research_ButtonID_Holder->Add(Research_ButtonID, 1, wxEXPAND);

	Research_Misc2_Holder->Add(Research_RequiredTechCount_Holder, 0, wxEXPAND);
	Research_Misc2_Holder->Add(Research_Type_Holder, 0, wxEXPAND);
	Research_Misc2_Holder->Add(Research_ResearchTime_Holder, 0, wxEXPAND);
	Research_Misc2_Holder->Add(Research_IconID_Holder, 0, wxEXPAND);
	Research_Misc2_Holder->Add(Research_ButtonID_Holder, 0, wxEXPAND);

	Research_LanguageDLLHelp_Holder->Add(Research_LanguageDLLHelp_Text, 0, wxEXPAND);
	Research_LanguageDLLHelp_Holder->Add(Research_LanguageDLLHelp, 0, wxEXPAND);
	Research_LanguageDLLConverter_Holder[0]->Add(Research_LanguageDLLConverter_Text[0], 0, wxEXPAND);
	Research_LanguageDLLConverter_Holder[0]->Add(Research_LanguageDLLConverter[0], 0, wxEXPAND);
	Research_LanguageDLLName2_Holder->Add(Research_LanguageDLLName2_Text, 0, wxEXPAND);
	Research_LanguageDLLName2_Holder->Add(Research_LanguageDLLName2, 0, wxEXPAND);
	Research_LanguageDLLConverter_Holder[1]->Add(Research_LanguageDLLConverter_Text[1], 0, wxEXPAND);
	Research_LanguageDLLConverter_Holder[1]->Add(Research_LanguageDLLConverter[1], 0, wxEXPAND);
	Research_Unknown1_Holder->Add(Research_Unknown1_Text, 0, wxEXPAND);
	Research_Unknown1_Holder->Add(Research_Unknown1, 0, wxEXPAND);

	Research_PointerArea_Holder->Add(Research_LanguageDLLHelp_Holder, 0, wxEXPAND);
	Research_PointerArea_Holder->Add(Research_LanguageDLLConverter_Holder[0], 0, wxEXPAND);
	Research_PointerArea_Holder->Add(Research_LanguageDLLName2_Holder, 0, wxEXPAND);
	Research_PointerArea_Holder->Add(Research_LanguageDLLConverter_Holder[1], 0, wxEXPAND);
	Research_PointerArea_Holder->Add(Research_Unknown1_Holder, 0, wxEXPAND);

	Research_ScrollSpace->Add(Research_Names_Holder, 0, wxEXPAND);
	Research_ScrollSpace->AddSpacer(5);
	Research_ScrollSpace->Add(Research_LangDLLArea_Holder, 0, wxEXPAND);
	Research_ScrollSpace->AddSpacer(5);
	Research_ScrollSpace->Add(Research_RequiredTechArea_Holder, 0, wxEXPAND);
	Research_ScrollSpace->AddSpacer(5);
	Research_ScrollSpace->Add(Research_MiscArea1_Grid, 0, wxEXPAND);
	Research_ScrollSpace->AddSpacer(5);
	Research_ScrollSpace->Add(Research_Misc2_Holder, 0, wxEXPAND);
	Research_ScrollSpace->AddSpacer(5);
	Research_ScrollSpace->Add(Research_CostHeader_Holder, 0, wxEXPAND);
	Research_ScrollSpace->AddSpacer(5);
	Research_ScrollSpace->Add(Research_PointerArea_Holder, 0, wxEXPAND);
	Research_ScrollSpace->AddSpacer(5);
	Research_ScrollSpace->Add(Research_DLL_LanguageDLLHelp, 0, wxEXPAND);
	Research_ScrollSpace->Add(Research_DLL_LanguageDLLName2, 0, wxEXPAND);

	Research_ScrollArea->Add(Research_ScrollSpace, 1, wxEXPAND);
	Research_ScrollArea->AddSpacer(5);

	Research_Scroller->SetSizer(Research_ScrollArea);
	Research_Scroller->SetScrollRate(0, 15);

	Research_DataArea->AddSpacer(5);
	Research_DataArea->Add(Research_Scroller, 1, wxEXPAND);
	Research_DataArea->AddSpacer(5);

	Research_Main->AddSpacer(5);
	Research_Main->Add(Research_ListArea, 21, wxEXPAND);
	Research_Main->AddSpacer(5);
	Research_Main->Add(Research_DataArea, 65, wxEXPAND);
	Research_Main->AddSpacer(5);

	Tab_Research->SetSizer(Research_Main);

	Connect(Research_Research_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResearchSearch));
	Connect(Research_Research_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResearchSearch));
	for(short loop = 0; loop < 2; ++loop)
	{
		Connect(Research_Research_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchSearch));
		Connect(Research_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
	}
	Connect(Research_Research_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnResearchSelect));
	Connect(Research_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchAdd));
	Connect(Research_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchInsert));
	Connect(Research_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchDelete));
	Connect(Research_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchCopy));
	Connect(Research_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchPaste));
	Connect(Research_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchPasteInsert));
	Connect(Research_LanguageDLLConverter[0]->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(AGE_Frame::ResearchLangDLLConverter));
	Connect(Research_LanguageDLLConverter[1]->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(AGE_Frame::ResearchLangDLLConverter));

	Research_LangDLLName->Connect(Research_LangDLLName->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Research), NULL, this);
	Research_LangDLLDescription->Connect(Research_LangDLLDescription->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Research), NULL, this);
	Research_Name[0]->Connect(Research_Name[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Research), NULL, this);
	Research_Name[1]->Connect(Research_Name[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Research), NULL, this);
	Research_LanguageDLLHelp->Connect(Research_LanguageDLLHelp->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Research), NULL, this);
	Research_LanguageDLLName2->Connect(Research_LanguageDLLName2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Research), NULL, this);
	Research_DLL_LangDLLName->Connect(Research_DLL_LangDLLName->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);
	Research_DLL_LangDLLDescription->Connect(Research_DLL_LangDLLDescription->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);
	Research_DLL_LanguageDLLHelp->Connect(Research_DLL_LanguageDLLHelp->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);
	Research_DLL_LanguageDLLName2->Connect(Research_DLL_LanguageDLLName2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);
}

void AGE_Frame::OnKillFocus_Research(wxFocusEvent &Event)
{
	if(((AGETextCtrl*)Event.GetEventObject())->SaveEdits() != 0) return;
	if(Event.GetId() == Research_Name[0]->GetId() || Event.GetId() == Research_LangDLLName->GetId())
	{
		FirstVisible = Research_Research_List->HitTest(wxPoint(0, 0));
		ListResearches();
	}
	else
	{
		wxCommandEvent E;
		OnResearchSelect(E);
	}
	Event.Skip();
}
