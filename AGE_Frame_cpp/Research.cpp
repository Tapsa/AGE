/* AGEFrame_cpp/Research.cpp */

#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetResearchName(short &Index, bool Filter)
{
	string Name = "";
	if(Filter)
	{
		short Selection[2];
		for(short loop = 0;loop < 2;loop++)
		Selection[loop] = Research_Research_SearchFilters[loop]->GetSelection();

		if(Selection[0] > 1)
		for(short loop = 0;loop < 2;loop++)
		{
			if(Selection[loop] == 2)	// Research Location
			{
				Name += "L ";
				Name += lexical_cast<string>(GenieFile->Researchs[Index].ResearchLocation);
			}
			else if(GameVersion < 2);
			else if(Selection[loop] == 3)	// Civilization
			{
				Name += "C ";
				Name += lexical_cast<string>(GenieFile->Researchs[Index].Civ);
			}
			else if(Selection[loop] == 4)	// Full Tech. Mode
			{
				Name += "F ";
				Name += lexical_cast<string>(GenieFile->Researchs[Index].FullTechMode);
			}
			Name += ", ";
			if(Selection[loop+1] < 2) break;
		}

		if(Selection[0] != 1) Filter = false; // Names
	}

	if((LanguageDllString(GenieFile->Researchs[Index].LanguageDllName) != "") && (Filter == false))
	{
		Name += LanguageDllString(GenieFile->Researchs[Index].LanguageDllName);
	}
	else if(GenieFile->Researchs[Index].Name != "")
	{
		Name += GenieFile->Researchs[Index].Name;
	}
	else
	{
		Name += "New Research";
	}
	return Name;
}

void AGE_Frame::OnResearchSearch(wxCommandEvent& Event)
{
	ListResearches(false);
}

void AGE_Frame::ListResearches(bool Sized)
{
	string Name, CompareText;
	SearchText = wxString(Research_Research_Search->GetValue()).Lower();
	ExcludeText = wxString(Research_Research_Search_R->GetValue()).Lower();
	for(short loop = 0;loop < 2;loop++)
	{
		if(Research_Research_UseAnd[loop]->GetValue() == true)
		UseAnd[loop] = true; else UseAnd[loop] = false;
	}

	short Selections = Research_Research_List->GetSelections(Items);
	if(Research_Research_List->GetCount() > 0) Research_Research_List->Clear();

	short IDCount = 21, ResearchIDs[IDCount];
	if(Sized)
	{
		ResearchIDs[0] = Effects_ComboBox_ResearchsD->GetSelection();
		ResearchIDs[1] = Effects_ComboBox_ResearchsA->GetSelection();
		ResearchIDs[2] = Units_ComboBox_ResearchID->GetSelection();
		for(short loop = 0;loop < 6;loop++)
		ResearchIDs[loop+3] = Research_ComboBox_RequiredTechs[loop]->GetSelection();
		ResearchIDs[9] = TechTrees_Ages_ComboBox_Research->GetSelection();
		ResearchIDs[10] = TechTrees_Buildings_ComboBox_EnablingResearch->GetSelection();
		ResearchIDs[11] = TechTrees_Buildings_ComboBox_Research->GetSelection();
		ResearchIDs[12] = TechTrees_Units_ComboBox_EnablingResearch->GetSelection();
		ResearchIDs[13] = TechTrees_Researches_ComboBox_ID->GetSelection();
		ResearchIDs[14] = TechTrees_Researches_ComboBox_UpperResearch->GetSelection();
		ResearchIDs[15] = TechTrees_Researches_ComboBox_Research->GetSelection();
		ResearchIDs[16] = TechTrees_Units_ComboBox_RequiredResearch->GetSelection();
		for(short loop = 0;loop < 4;loop++)
		ResearchIDs[loop+17] = TechTrees_ComboBox_Research[loop]->GetSelection();

		if(Effects_ComboBox_ResearchsD->GetCount() > 0)
		{
			Effects_ComboBox_ResearchsD->Clear();
		}
		if(Effects_ComboBox_ResearchsA->GetCount() > 0)
		{
			Effects_ComboBox_ResearchsA->Clear();
		}
		if(Units_ComboBox_ResearchID->GetCount() > 0)
		{
			Units_ComboBox_ResearchID->Clear();
		}
		for(short loop = 0;loop < 6;loop++)
		{
			if(Research_ComboBox_RequiredTechs[loop]->GetCount() > 0)
			{
				Research_ComboBox_RequiredTechs[loop]->Clear();
			}
		}
		if(TechTrees_Ages_ComboBox_Research->GetCount() > 0)
		{
			TechTrees_Ages_ComboBox_Research->Clear();
		}
		if(TechTrees_Buildings_ComboBox_EnablingResearch->GetCount() > 0)
		{
			TechTrees_Buildings_ComboBox_EnablingResearch->Clear();
		}
		if(TechTrees_Buildings_ComboBox_Research->GetCount() > 0)
		{
			TechTrees_Buildings_ComboBox_Research->Clear();
		}
		if(TechTrees_Units_ComboBox_EnablingResearch->GetCount() > 0)
		{
			TechTrees_Units_ComboBox_EnablingResearch->Clear();
		}
		if(TechTrees_Researches_ComboBox_ID->GetCount() > 0)
		{
			TechTrees_Researches_ComboBox_ID->Clear();
		}
		if(TechTrees_Researches_ComboBox_UpperResearch->GetCount() > 0)
		{
			TechTrees_Researches_ComboBox_UpperResearch->Clear();
		}
		if(TechTrees_Researches_ComboBox_Research->GetCount() > 0)
		{
			TechTrees_Researches_ComboBox_Research->Clear();
		}
		if(TechTrees_Units_ComboBox_RequiredResearch->GetCount() > 0)
		{
			TechTrees_Units_ComboBox_RequiredResearch->Clear();
		}
		for(short loop = 0;loop < 4;loop++)
		if(TechTrees_ComboBox_Research[loop]->GetCount() > 0)
		{
			TechTrees_ComboBox_Research[loop]->Clear();
		}

		for(short loop = 0;loop < IDCount;loop++)
		{
			if(ResearchIDs[loop] == wxNOT_FOUND)
			{
				ResearchIDs[loop] = 0;
			}
		}

		Effects_ComboBox_ResearchsD->Append("-1 - None");
		Effects_ComboBox_ResearchsA->Append("-1 - None");
		Units_ComboBox_ResearchID->Append("-1 - None");
		for(short loop = 0;loop < 6;loop++)
		Research_ComboBox_RequiredTechs[loop]->Append("-1 - None");
		TechTrees_Ages_ComboBox_Research->Append("-1 - None");
		TechTrees_Buildings_ComboBox_EnablingResearch->Append("-1 - None");
		TechTrees_Buildings_ComboBox_Research->Append("-1 - None");
		TechTrees_Units_ComboBox_EnablingResearch->Append("-1 - None");
		TechTrees_Researches_ComboBox_ID->Append("-1 - None");
		TechTrees_Researches_ComboBox_UpperResearch->Append("-1 - None");
		TechTrees_Researches_ComboBox_Research->Append("-1 - None");
		TechTrees_Units_ComboBox_RequiredResearch->Append("-1 - None");
		for(short loop = 0;loop < 4;loop++)
		TechTrees_ComboBox_Research[loop]->Append("-1 - None");
	}

	for(short loop = 0;loop < GenieFile->Researchs.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetResearchName(loop, true);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText))
		{
			Research_Research_List->Append(Name, (void*)&GenieFile->Researchs[loop]);
		}
		if(Sized)
		{
			Name = " "+lexical_cast<string>(loop)+" - "+GetResearchName(loop);
			Effects_ComboBox_ResearchsD->Append(Name);
			Effects_ComboBox_ResearchsA->Append(Name);
			Units_ComboBox_ResearchID->Append(Name);
			for(short loop = 0;loop < 6;loop++)
			Research_ComboBox_RequiredTechs[loop]->Append(Name);
			TechTrees_Ages_ComboBox_Research->Append(Name);
			TechTrees_Buildings_ComboBox_EnablingResearch->Append(Name);
			TechTrees_Buildings_ComboBox_Research->Append(Name);
			TechTrees_Units_ComboBox_EnablingResearch->Append(Name);
			TechTrees_Researches_ComboBox_ID->Append(Name);
			TechTrees_Researches_ComboBox_UpperResearch->Append(Name);
			TechTrees_Researches_ComboBox_Research->Append(Name);
			TechTrees_Units_ComboBox_RequiredResearch->Append(Name);
			for(short loop = 0;loop < 4;loop++)
			TechTrees_ComboBox_Research[loop]->Append(Name);
		}
	}

	ListingFix(Selections, Research_Research_List);
	if(Sized)
	{
		Effects_ComboBox_ResearchsD->SetSelection(ResearchIDs[0]);
		Effects_ComboBox_ResearchsA->SetSelection(ResearchIDs[1]);
		Units_ComboBox_ResearchID->SetSelection(ResearchIDs[2]);
		for(short loop = 0;loop < 6;loop++)
		Research_ComboBox_RequiredTechs[loop]->SetSelection(ResearchIDs[loop+3]);
		TechTrees_Ages_ComboBox_Research->SetSelection(ResearchIDs[9]);
		TechTrees_Buildings_ComboBox_EnablingResearch->SetSelection(ResearchIDs[10]);
		TechTrees_Buildings_ComboBox_Research->SetSelection(ResearchIDs[11]);
		TechTrees_Units_ComboBox_EnablingResearch->SetSelection(ResearchIDs[12]);
		TechTrees_Researches_ComboBox_ID->SetSelection(ResearchIDs[13]);
		TechTrees_Researches_ComboBox_UpperResearch->SetSelection(ResearchIDs[14]);
		TechTrees_Researches_ComboBox_Research->SetSelection(ResearchIDs[15]);
		TechTrees_Units_ComboBox_RequiredResearch->SetSelection(ResearchIDs[16]);
		for(short loop = 0;loop < 4;loop++)
		TechTrees_ComboBox_Research[loop]->SetSelection(ResearchIDs[loop+17]);
	}

	for(short loop = 0;loop < 2;loop++)
	UseAnd[loop] = false;

	wxCommandEvent E;
	OnResearchSelect(E);
}

void AGE_Frame::OnResearchSelect(wxCommandEvent& Event)
{
	short Selections = Research_Research_List->GetSelections(Items);
	if(Selections != 0)
	{
		ResearchIDs.resize(Selections);
		genie::Research * ResearchPointer;
		for(short loop = Selections-1;loop >= 0;loop--)
		{
			ResearchPointer = (genie::Research*)Research_Research_List->GetClientData(Items.Item(loop));
			ResearchIDs[loop] = (ResearchPointer - (&GenieFile->Researchs[0]));
		}
		short RequiredTechs;
		for(short loop = 4;loop < 6;loop++)
		{
			if(GameVersion >= 2)
			{
				RequiredTechs = 6;
			}
			else
			{
				RequiredTechs = 4;
			}
		}
		for(short loop = 0;loop < RequiredTechs;loop++)
		{
			Research_RequiredTechs[loop]->ChangeValue(lexical_cast<string>(ResearchPointer->RequiredTechs[loop]));
			Research_RequiredTechs[loop]->Container = &ResearchPointer->RequiredTechs[loop];
			Research_ComboBox_RequiredTechs[loop]->SetSelection(ResearchPointer->RequiredTechs[loop] + 1);
		}
		Research_RequiredTechCount->ChangeValue(lexical_cast<string>(ResearchPointer->RequiredTechCount));
		Research_RequiredTechCount->Container = &ResearchPointer->RequiredTechCount;
		Research_Resources[0]->ChangeValue(lexical_cast<string>(ResearchPointer->ResourceCosts[0].Type));
		Research_Resources[0]->Container = &ResearchPointer->ResourceCosts[0].Type;
		Research_Resources[1]->ChangeValue(lexical_cast<string>(ResearchPointer->ResourceCosts[1].Type));
		Research_Resources[1]->Container = &ResearchPointer->ResourceCosts[1].Type;
		Research_Resources[2]->ChangeValue(lexical_cast<string>(ResearchPointer->ResourceCosts[2].Type));
		Research_Resources[2]->Container = &ResearchPointer->ResourceCosts[2].Type;
		Research_ComboBox_Resources[0]->SetSelection(ResearchPointer->ResourceCosts[0].Type + 1);
		Research_ComboBox_Resources[1]->SetSelection(ResearchPointer->ResourceCosts[1].Type + 1);
		Research_ComboBox_Resources[2]->SetSelection(ResearchPointer->ResourceCosts[2].Type + 1);
		Research_Amount[0]->ChangeValue(lexical_cast<string>(ResearchPointer->ResourceCosts[0].Amount));
		Research_Amount[0]->Container = &ResearchPointer->ResourceCosts[0].Amount;
		Research_Amount[1]->ChangeValue(lexical_cast<string>(ResearchPointer->ResourceCosts[1].Amount));
		Research_Amount[1]->Container = &ResearchPointer->ResourceCosts[1].Amount;
		Research_Amount[2]->ChangeValue(lexical_cast<string>(ResearchPointer->ResourceCosts[2].Amount));
		Research_Amount[2]->Container = &ResearchPointer->ResourceCosts[2].Amount;
		Research_Used[0]->ChangeValue(lexical_cast<string>((short)ResearchPointer->ResourceCosts[0].Enabled));
		Research_Used[0]->Container = &ResearchPointer->ResourceCosts[0].Enabled;
		Research_CheckBox_Used[0]->SetValue((bool)ResearchPointer->ResourceCosts[0].Enabled);
		Research_Used[1]->ChangeValue(lexical_cast<string>((short)ResearchPointer->ResourceCosts[1].Enabled));
		Research_Used[1]->Container = &ResearchPointer->ResourceCosts[1].Enabled;
		Research_CheckBox_Used[1]->SetValue((bool)ResearchPointer->ResourceCosts[1].Enabled);
		Research_Used[2]->ChangeValue(lexical_cast<string>((short)ResearchPointer->ResourceCosts[2].Enabled));
		Research_Used[2]->Container = &ResearchPointer->ResourceCosts[2].Enabled;
		Research_CheckBox_Used[2]->SetValue((bool)ResearchPointer->ResourceCosts[2].Enabled);
		if(GameVersion >= 2)
		{
			Research_Civ->ChangeValue(lexical_cast<string>(ResearchPointer->Civ));
			Research_Civ->Container = &ResearchPointer->Civ;
			Research_ComboBox_Civ->SetSelection(ResearchPointer->Civ + 1);
			Research_FullTechMode->ChangeValue(lexical_cast<string>(ResearchPointer->FullTechMode));
			Research_FullTechMode->Container = &ResearchPointer->FullTechMode;
			Research_CheckBox_FullTechMode->SetValue((bool)ResearchPointer->FullTechMode);
		}
		Research_ResearchLocation->ChangeValue(lexical_cast<string>(ResearchPointer->ResearchLocation));
		Research_ResearchLocation->Container = &ResearchPointer->ResearchLocation;
		Research_ComboBox_ResearchLocation->SetSelection(ResearchPointer->ResearchLocation + 1);
		Research_LangDllName->ChangeValue(lexical_cast<string>(ResearchPointer->LanguageDllName));
		Research_LangDllName->Container = &ResearchPointer->LanguageDllName;
		Research_DLL_LangDllName->SetLabel(LanguageDllString(lexical_cast<unsigned short>(Research_LangDllName->GetValue())));
		Research_LangDllDescription->ChangeValue(lexical_cast<string>(ResearchPointer->LanguageDllDescription));
		Research_LangDllDescription->Container = &ResearchPointer->LanguageDllDescription;
		Research_DLL_LangDllDescription->SetLabel(LanguageDllString(lexical_cast<unsigned short>(Research_LangDllDescription->GetValue())));
		Research_ResearchTime->ChangeValue(lexical_cast<string>(ResearchPointer->ResearchTime));
		Research_ResearchTime->Container = &ResearchPointer->ResearchTime;
		Research_TechID->ChangeValue(lexical_cast<string>(ResearchPointer->TechageID));
		Research_TechID->Container = &ResearchPointer->TechageID;
		Research_ComboBox_TechID->SetSelection(ResearchPointer->TechageID + 1);
		Research_Type->ChangeValue(lexical_cast<string>(ResearchPointer->Type));
		Research_Type->Container = &ResearchPointer->Type;
		Research_IconID->ChangeValue(lexical_cast<string>(ResearchPointer->IconID));
		Research_IconID->Container = &ResearchPointer->IconID;
		Research_ButtonID->ChangeValue(lexical_cast<string>((short)ResearchPointer->ButtonID));
		Research_ButtonID->Container = &ResearchPointer->ButtonID;
		Research_Pointers[0]->ChangeValue(lexical_cast<string>(ResearchPointer->Pointers[0]));
		Research_Pointers[0]->Container = &ResearchPointer->Pointers[0];
		Research_Pointers[1]->ChangeValue(lexical_cast<string>(ResearchPointer->Pointers[1]));
		Research_Pointers[1]->Container = &ResearchPointer->Pointers[1];
		Research_Pointers[1]->ChangeValue(lexical_cast<string>(ResearchPointer->Pointers[2]));
		Research_Pointers[2]->Container = &ResearchPointer->Pointers[2];
		Research_Name[0]->ChangeValue(ResearchPointer->Name);
		Research_Name[0]->Container = &ResearchPointer->Name;
		if(GameVersion >= 4)
		{
			Research_Name[1]->ChangeValue(ResearchPointer->Name2);
			Research_Name[1]->Container = &ResearchPointer->Name2;
		}
		Research_DLL_LangDllName->Wrap(Research_DLL_LangDllName->GetSize().GetWidth());
		Research_DLL_LangDllDescription->Wrap(Research_DLL_LangDllDescription->GetSize().GetWidth());
	}
}

void AGE_Frame::OnResearchAdd(wxCommandEvent& Event)
{
	if(GenieFile != NULL)
	{
		wxBusyCursor WaitCursor;
		genie::Research Temp;
		GenieFile->Researchs.push_back(Temp);
		Added = true;
		ListResearches();
	}
}

void AGE_Frame::OnResearchInsert(wxCommandEvent& Event)
{
	short Selections = Research_Research_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::Research Temp;
		GenieFile->Researchs.insert(GenieFile->Researchs.begin() + ResearchIDs[0], Temp);
		ListResearches();
	}
}

void AGE_Frame::OnResearchDelete(wxCommandEvent& Event)
{
	short Selections = Research_Research_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop = Selections-1;loop >= 0;loop--)
		GenieFile->Researchs.erase(GenieFile->Researchs.begin() + ResearchIDs[loop]);
		ListResearches();
	}
}

void AGE_Frame::OnResearchCopy(wxCommandEvent& Event)
{
	short Selections = Research_Research_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		ResearchCopies.resize(Selections);
		for(short loop = 0;loop < Selections;loop++)
		ResearchCopies[loop] = GenieFile->Researchs[ResearchIDs[loop]];
	}
}

void AGE_Frame::OnResearchPaste(wxCommandEvent& Event)
{
	short Selections = Research_Research_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		if(ResearchCopies.size()+ResearchIDs[0] > GenieFile->Researchs.size())
		GenieFile->Researchs.resize(ResearchCopies.size()+ResearchIDs[0]);
		for(short loop = 0;loop < ResearchCopies.size();loop++)
		GenieFile->Researchs[ResearchIDs[0]+loop] = ResearchCopies[loop];
		ListResearches();
	}
}

void AGE_Frame::OnResearchPasteInsert(wxCommandEvent& Event)
{
	short Selections = Research_Research_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::Research Temp;
		GenieFile->Researchs.insert(GenieFile->Researchs.begin() + ResearchIDs[0], ResearchCopies.size(), Temp);
		for(short loop = 0;loop < ResearchCopies.size();loop++)
		GenieFile->Researchs[ResearchIDs[0]+loop] = ResearchCopies[loop];
		ListResearches();
	}
}

void AGE_Frame::CreateResearchControls()
{
	Tab_Research = new wxPanel(TabBar_Data, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Research_Main = new wxBoxSizer(wxHORIZONTAL);
	Research_ListArea = new wxBoxSizer(wxVERTICAL);
	Research_Research = new wxStaticBoxSizer(wxVERTICAL, Tab_Research, "Researchs");
	Research_Research_Search = new wxTextCtrl(Tab_Research, wxID_ANY);
	Research_Research_UseAnd[0] = new wxCheckBox(Tab_Research, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20), 0, wxDefaultValidator);
	Research_Research_Search_R = new wxTextCtrl(Tab_Research, wxID_ANY);
	Research_Research_UseAnd[1] = new wxCheckBox(Tab_Research, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20), 0, wxDefaultValidator);
	for(short loop = 0;loop < 2;loop++)
	{
		Research_Research_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Research_Research_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_Research, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	Research_Research_List = new wxListBox(Tab_Research, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, wxLB_EXTENDED);
	Research_Research_Buttons = new wxGridSizer(3, 0, 0);
	Research_Add = new wxButton(Tab_Research, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Research_Insert = new wxButton(Tab_Research, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Research_Delete = new wxButton(Tab_Research, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Research_Copy = new wxButton(Tab_Research, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Research_Paste = new wxButton(Tab_Research, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Research_PasteInsert = new wxButton(Tab_Research, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	Research_DataArea = new wxBoxSizer(wxVERTICAL);
	Research_Scroller = new wxScrolledWindow(Tab_Research, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Research_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	Research_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	Research_Holder_Name[0] = new wxBoxSizer(wxVERTICAL);
	Research_Text_Name[0] = new wxStaticText(Research_Scroller, wxID_ANY, " Name ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Name[0] = new TextCtrl_String(Research_Scroller, "0", NULL);
	Research_Holder_Name[1] = new wxBoxSizer(wxVERTICAL);
	Research_Text_Name[1] = new wxStaticText(Research_Scroller, wxID_ANY, " Name 2 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Name[1] = new TextCtrl_String(Research_Scroller, "0", NULL);
	Research_Holder_LangDllName = new wxBoxSizer(wxVERTICAL);
	Research_Text_LangDllName = new wxStaticText(Research_Scroller, wxID_ANY, " Language Dll Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_LangDllName = new TextCtrl_UnShort(Research_Scroller, "0", NULL);
	Research_DLL_LangDllName = new wxStaticText(Research_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), wxALIGN_CENTRE | wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);
	Research_Holder_LangDllDescription = new wxBoxSizer(wxVERTICAL);
	Research_Text_LangDllDescription = new wxStaticText(Research_Scroller, wxID_ANY, " Language Dll Description", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_LangDllDescription = new TextCtrl_UnShort(Research_Scroller, "0", NULL);
	Research_DLL_LangDllDescription = new wxStaticText(Research_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), wxALIGN_CENTRE | wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);
	Research_Holder_RequiredTechArea = new wxBoxSizer(wxVERTICAL);
	Research_Holder_RequiredTechs = new wxGridSizer(6, 0, 5);
	Research_Text_RequiredTechArea = new wxStaticText(Research_Scroller, wxID_ANY, " Required Researches", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Grid_MiscArea1 = new wxGridSizer(4, 5, 5);
	Research_Holder_LangDLLArea = new wxBoxSizer(wxHORIZONTAL);
	Research_Holder_Misc2 = new wxBoxSizer(wxHORIZONTAL);
	Research_Holder_PointerArea = new wxBoxSizer(wxHORIZONTAL);
	Research_Holder_Names = new wxBoxSizer(wxHORIZONTAL);

	for(short loop = 0;loop < 6;loop++)
	{
		Research_RequiredTechs[loop] = new TextCtrl_Short(Research_Scroller, "0", NULL);
		Research_ComboBox_RequiredTechs[loop] = new ComboBox_Short(Research_Scroller, Research_RequiredTechs[loop]);
	}
	Research_Holder_TechID = new wxBoxSizer(wxVERTICAL);
	Research_Text_TechID = new wxStaticText(Research_Scroller, wxID_ANY, " Technology", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_TechID = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_ComboBox_TechID = new ComboBox_Short(Research_Scroller, Research_TechID);
	Research_Holder_ResearchLocation = new wxBoxSizer(wxVERTICAL);
	Research_Text_ResearchLocation = new wxStaticText(Research_Scroller, wxID_ANY, " Research Location", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_ResearchLocation = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_ComboBox_ResearchLocation = new ComboBox_Short(Research_Scroller, Research_ResearchLocation);
	Research_Holder_FullTechMode = new wxBoxSizer(wxVERTICAL);
	Research_Text_FullTechMode = new wxStaticText(Research_Scroller, wxID_ANY, " Full Tech. Mode", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_FullTechMode = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_CheckBox_FullTechMode = new CheckBox_Short(Research_Scroller, "Available", Research_FullTechMode);
	Research_Holder_Civ = new wxBoxSizer(wxVERTICAL);
	Research_Text_Civ = new wxStaticText(Research_Scroller, wxID_ANY, " Civilization", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Civ = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_ComboBox_Civ = new ComboBox_Short(Research_Scroller, Research_Civ);
	Research_Holder_RequiredTechCount = new wxBoxSizer(wxVERTICAL);
	Research_Text_RequiredTechCount = new wxStaticText(Research_Scroller, wxID_ANY, " Min. Req. Researches", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_RequiredTechCount = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Holder_Type = new wxBoxSizer(wxVERTICAL);
	Research_Text_Type = new wxStaticText(Research_Scroller, wxID_ANY, " Type *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_Type = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Type->SetToolTip("0 Normal\n2 Age");
	Research_Holder_ResearchTime = new wxBoxSizer(wxVERTICAL);
	Research_Text_ResearchTime = new wxStaticText(Research_Scroller, wxID_ANY, " Research Time", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_ResearchTime = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Holder_IconID = new wxBoxSizer(wxVERTICAL);
	Research_Text_IconID = new wxStaticText(Research_Scroller, wxID_ANY, " Icon", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_IconID = new TextCtrl_Short(Research_Scroller, "0", NULL);
	Research_Holder_ButtonID = new wxBoxSizer(wxVERTICAL);
	Research_Text_ButtonID = new wxStaticText(Research_Scroller, wxID_ANY, " Button", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Research_ButtonID = new TextCtrl_Byte(Research_Scroller, "0", NULL);

	Research_Holder_CostHeader = new wxStaticBoxSizer(wxVERTICAL, Research_Scroller, "Costs");
	Research_Holder_CostType = new wxBoxSizer(wxHORIZONTAL);
	Research_Holder_CostAmount = new wxBoxSizer(wxHORIZONTAL);
	Research_Holder_CostUsed = new wxBoxSizer(wxHORIZONTAL);
	Research_Text_Resources = new wxStaticText(Research_Scroller, wxID_ANY, "Cost Type ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Research_Text_Amount = new wxStaticText(Research_Scroller, wxID_ANY, "Cost Amount ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Research_Text_Used = new wxStaticText(Research_Scroller, wxID_ANY, "Cost Used ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Research_ResourceGrid = new wxGridSizer(3, 0, 5);
	for(short loop = 0;loop < 3;loop++)
	{
		Research_Resources[loop] = new TextCtrl_Short(Research_Scroller, "0", NULL);
		Research_ComboBox_Resources[loop] = new ComboBox_Short(Research_Scroller, Research_Resources[loop]);
		Research_Amount[loop] = new TextCtrl_Short(Research_Scroller, "0", NULL);
		Research_Used[loop] = new TextCtrl_Byte(Research_Scroller, "0", NULL);
		Research_CheckBox_Used[loop] = new CheckBox_Byte(Research_Scroller, "Used", Research_Used[loop]);
	}

	for(short loop = 0;loop < 3;loop++)
	{
		Research_Holder_Pointers[loop] = new wxBoxSizer(wxVERTICAL);
		Research_Text_Pointers[loop] = new wxStaticText(Research_Scroller, wxID_ANY, " Pointer "+lexical_cast<string>(loop+1), wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		Research_Pointers[loop] = new TextCtrl_Long(Research_Scroller, "0", NULL);
	}

	Research_Research_Buttons->Add(Research_Add, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_Insert, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_Delete, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_Copy, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_Paste, 1, wxEXPAND);
	Research_Research_Buttons->Add(Research_PasteInsert, 1, wxEXPAND);

	Research_Research_Searches[0]->Add(Research_Research_Search, 1, wxEXPAND);
	Research_Research_Searches[0]->Add(2, -1);
	Research_Research_Searches[0]->Add(Research_Research_UseAnd[0], 0, wxEXPAND);
	Research_Research_Searches[1]->Add(Research_Research_Search_R, 1, wxEXPAND);
	Research_Research_Searches[1]->Add(2, -1);
	Research_Research_Searches[1]->Add(Research_Research_UseAnd[1], 0, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Research_Research->Add(Research_Research_Searches[loop], 0, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Research_Research->Add(Research_Research_SearchFilters[loop], 0, wxEXPAND);
	Research_Research->Add(-1, 2);
	Research_Research->Add(Research_Research_List, 1, wxEXPAND);
	Research_Research->Add(-1, 2);
	Research_Research->Add(Research_Research_Buttons, 0, wxEXPAND);

	Research_ListArea->Add(-1, 10);
	Research_ListArea->Add(Research_Research, 1, wxEXPAND);
	Research_ListArea->Add(-1, 10);

	for(short loop = 0;loop < 2;loop++)
	{
		Research_Holder_Name[loop]->Add(Research_Text_Name[loop], 0, wxEXPAND);
		Research_Holder_Name[loop]->Add(Research_Name[loop], 1, wxEXPAND);
	}

	Research_Holder_Names->Add(Research_Holder_Name[0], 2, wxEXPAND);
	Research_Holder_Names->Add(5, -1);
	Research_Holder_Names->Add(Research_Holder_Name[1], 2, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Research_Holder_LangDllName->Add(Research_Text_LangDllName, 0, wxEXPAND);
	Research_Holder_LangDllName->Add(Research_LangDllName, 1, wxEXPAND);
	Research_Holder_LangDllName->Add(Research_DLL_LangDllName, 2, wxEXPAND);
	Research_Holder_LangDllDescription->Add(Research_Text_LangDllDescription, 0, wxEXPAND);
	Research_Holder_LangDllDescription->Add(Research_LangDllDescription, 1, wxEXPAND);
	Research_Holder_LangDllDescription->Add(Research_DLL_LangDllDescription, 2, wxEXPAND);

	Research_Holder_LangDLLArea->Add(Research_Holder_LangDllName, 1, wxEXPAND);
	Research_Holder_LangDLLArea->Add(5, -1);
	Research_Holder_LangDLLArea->Add(Research_Holder_LangDllDescription, 1, wxEXPAND);

	for(short loop = 0;loop < 3;loop++)
	Research_ResourceGrid->Add(Research_Resources[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 3;loop++)
	Research_ResourceGrid->Add(Research_ComboBox_Resources[loop], 1, wxEXPAND);

	Research_Holder_CostType->Add(Research_Text_Resources, 1, wxEXPAND);
	Research_Holder_CostType->Add(Research_ResourceGrid, 6, wxEXPAND);

	Research_Holder_CostAmount->Add(Research_Text_Amount, 2, wxEXPAND);
	Research_Holder_CostAmount->Add(Research_Amount[0], 4, wxEXPAND);
	Research_Holder_CostAmount->Add(5, -1);
	Research_Holder_CostAmount->Add(Research_Amount[1], 4, wxEXPAND);
	Research_Holder_CostAmount->Add(5, -1);
	Research_Holder_CostAmount->Add(Research_Amount[2], 4, wxEXPAND);

	Research_Holder_CostUsed->Add(Research_Text_Used, 2, wxEXPAND);
	Research_Holder_CostUsed->Add(Research_Used[0], 3, wxEXPAND);
	Research_Holder_CostUsed->Add(2, -1);
	Research_Holder_CostUsed->Add(Research_CheckBox_Used[0], 1, wxEXPAND);
	Research_Holder_CostUsed->Add(5, -1);
	Research_Holder_CostUsed->Add(Research_Used[1], 3, wxEXPAND);
	Research_Holder_CostUsed->Add(2, -1);
	Research_Holder_CostUsed->Add(Research_CheckBox_Used[1], 1, wxEXPAND);
	Research_Holder_CostUsed->Add(5, -1);
	Research_Holder_CostUsed->Add(Research_Used[2], 3, wxEXPAND);
	Research_Holder_CostUsed->Add(2, -1);
	Research_Holder_CostUsed->Add(Research_CheckBox_Used[2], 1, wxEXPAND);

	Research_Holder_CostHeader->Add(Research_Holder_CostType, 0, wxEXPAND);
	Research_Holder_CostHeader->Add(-1, 5);
	Research_Holder_CostHeader->Add(Research_Holder_CostAmount, 0, wxEXPAND);
	Research_Holder_CostHeader->Add(-1, 5);
	Research_Holder_CostHeader->Add(Research_Holder_CostUsed, 0, wxEXPAND);

	for(short loop = 0;loop < 6;loop++)
	Research_Holder_RequiredTechs->Add(Research_RequiredTechs[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 6;loop++)
	Research_Holder_RequiredTechs->Add(Research_ComboBox_RequiredTechs[loop], 1, wxEXPAND);

	Research_Holder_RequiredTechArea->Add(Research_Text_RequiredTechArea, 0, wxEXPAND);
	Research_Holder_RequiredTechArea->Add(Research_Holder_RequiredTechs, 1, wxEXPAND);

	Research_Holder_RequiredTechCount->Add(Research_Text_RequiredTechCount, 0, wxEXPAND);
	Research_Holder_RequiredTechCount->Add(Research_RequiredTechCount, 1, wxEXPAND);

	Research_Holder_Civ->Add(Research_Text_Civ, 0, wxEXPAND);
	Research_Holder_Civ->Add(Research_Civ, 1, wxEXPAND);
	Research_Holder_Civ->Add(Research_ComboBox_Civ, 1, wxEXPAND);

	Research_Holder_FullTechMode->Add(Research_Text_FullTechMode, 0, wxEXPAND);
	Research_Holder_FullTechMode->Add(Research_FullTechMode, 1, wxEXPAND);
	Research_Holder_FullTechMode->Add(Research_CheckBox_FullTechMode, 1, wxEXPAND);

	Research_Holder_ResearchLocation->Add(Research_Text_ResearchLocation, 0, wxEXPAND);
	Research_Holder_ResearchLocation->Add(Research_ResearchLocation, 1, wxEXPAND);
	Research_Holder_ResearchLocation->Add(Research_ComboBox_ResearchLocation, 1, wxEXPAND);

	Research_Grid_MiscArea1->Add(Research_Holder_TechID, 1, wxEXPAND);
	Research_Grid_MiscArea1->Add(Research_Holder_ResearchLocation, 1, wxEXPAND);
	Research_Grid_MiscArea1->Add(Research_Holder_FullTechMode, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Research_Grid_MiscArea1->Add(Research_Holder_Civ, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Research_Holder_ResearchTime->Add(Research_Text_ResearchTime, 0, wxEXPAND);
	Research_Holder_ResearchTime->Add(Research_ResearchTime, 1, wxEXPAND);

	Research_Holder_TechID->Add(Research_Text_TechID, 0, wxEXPAND);
	Research_Holder_TechID->Add(Research_TechID, 1, wxEXPAND);
	Research_Holder_TechID->Add(Research_ComboBox_TechID, 1, wxEXPAND);

	Research_Holder_Type->Add(Research_Text_Type, 0, wxEXPAND);
	Research_Holder_Type->Add(Research_Type, 1, wxEXPAND);

	Research_Holder_IconID->Add(Research_Text_IconID, 0, wxEXPAND);
	Research_Holder_IconID->Add(Research_IconID, 1, wxEXPAND);

	Research_Holder_ButtonID->Add(Research_Text_ButtonID, 0, wxEXPAND);
	Research_Holder_ButtonID->Add(Research_ButtonID, 1, wxEXPAND);

	Research_Holder_Misc2->Add(Research_Holder_RequiredTechCount, 1, wxEXPAND);
	Research_Holder_Misc2->Add(5, -1);
	Research_Holder_Misc2->Add(Research_Holder_Type, 1, wxEXPAND);
	Research_Holder_Misc2->Add(5, -1);
	Research_Holder_Misc2->Add(Research_Holder_ResearchTime, 1, wxEXPAND);
	Research_Holder_Misc2->Add(5, -1);
	Research_Holder_Misc2->Add(Research_Holder_IconID, 1, wxEXPAND);
	Research_Holder_Misc2->Add(5, -1);
	Research_Holder_Misc2->Add(Research_Holder_ButtonID, 1, wxEXPAND);

	for(short loop = 0;loop < 3;loop++)
	{
		Research_Holder_Pointers[loop]->Add(Research_Text_Pointers[loop], 0, wxEXPAND);
		Research_Holder_Pointers[loop]->Add(Research_Pointers[loop], 1, wxEXPAND);
	}

	Research_Holder_PointerArea->Add(Research_Holder_Pointers[0], 1, wxEXPAND);
	Research_Holder_PointerArea->Add(5, -1);
	Research_Holder_PointerArea->Add(Research_Holder_Pointers[1], 1, wxEXPAND);
	Research_Holder_PointerArea->Add(5, -1);
	Research_Holder_PointerArea->Add(Research_Holder_Pointers[2], 1, wxEXPAND);

	Research_ScrollerWindowsSpace->Add(Research_Holder_Names, 0, wxEXPAND);
	Research_ScrollerWindowsSpace->Add(-1, 5);
	Research_ScrollerWindowsSpace->Add(Research_Holder_LangDLLArea, 0, wxEXPAND);
	Research_ScrollerWindowsSpace->Add(-1, 5);
	Research_ScrollerWindowsSpace->Add(Research_Holder_RequiredTechArea, 0, wxEXPAND);
	Research_ScrollerWindowsSpace->Add(-1, 5);
	Research_ScrollerWindowsSpace->Add(Research_Grid_MiscArea1, 0, wxEXPAND);
	Research_ScrollerWindowsSpace->Add(-1, 5);
	Research_ScrollerWindowsSpace->Add(Research_Holder_Misc2, 0, wxEXPAND);
	Research_ScrollerWindowsSpace->Add(-1, 5);
	Research_ScrollerWindowsSpace->Add(Research_Holder_CostHeader, 0, wxEXPAND);
	Research_ScrollerWindowsSpace->Add(-1, 5);
	Research_ScrollerWindowsSpace->Add(Research_Holder_PointerArea, 0, wxEXPAND);

	Research_ScrollerWindows->Add(Research_ScrollerWindowsSpace, 1, wxEXPAND);
	Research_ScrollerWindows->Add(5, -1);

	Research_Scroller->SetSizer(Research_ScrollerWindows);
	Research_Scroller->SetScrollRate(0, 15);

	Research_DataArea->Add(-1, 10);
	Research_DataArea->Add(Research_Scroller, 1, wxEXPAND);
	Research_DataArea->Add(-1, 10);

	Research_Main->Add(10, -1);
	Research_Main->Add(Research_ListArea, 1, wxEXPAND);
	Research_Main->Add(10, -1);
	Research_Main->Add(Research_DataArea, 3, wxEXPAND);
	Research_Main->Add(10, -1);

	Tab_Research->SetSizer(Research_Main);

	Connect(Research_Research_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResearchSearch));
	Connect(Research_Research_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResearchSearch));
	for(short loop = 0;loop < 2;loop++)
	{
		Connect(Research_Research_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchSearch));
		Connect(Research_Research_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_ComboBoxes));
	}
	Connect(Research_Research_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnResearchSelect));
	Connect(Research_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchAdd));
	Connect(Research_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchInsert));
	Connect(Research_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchDelete));
	Connect(Research_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchCopy));
	Connect(Research_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchPaste));
	Connect(Research_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResearchPasteInsert));

	Research_LangDllName->Connect(Research_LangDllName->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_UnShort), NULL, this);
	Research_LangDllDescription->Connect(Research_LangDllDescription->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_UnShort), NULL, this);
	Research_Name[0]->Connect(Research_Name[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Research_Name[1]->Connect(Research_Name[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);

}
