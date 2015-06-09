#include "../AGE_Frame.h"

string AGE_Frame::GetSoundName(short Index)
{
	return "File count: "+lexical_cast<string>(GenieFile->Sounds[Index].Items.size())+" ";
}

void AGE_Frame::OnSoundsSearch(wxCommandEvent &Event)
{
	FirstVisible = 0;
	ListSounds(false);
}

void AGE_Frame::ListSounds(bool all)
{
	InitSounds(all);
	wxCommandEvent E;
	OnSoundsSelect(E);
}

void AGE_Frame::InitSounds(bool all)
{
	searchText = Sounds_Sounds_Search->GetValue().Lower();
	excludeText = Sounds_Sounds_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString names, filteredNames;
	if(all) names.Alloc(GenieFile->Sounds.size());

	for(short loop = 0; loop < GenieFile->Sounds.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetSoundName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->Sounds[loop]);
		}
		if(all) names.Add(Name);
	}

	Listing(Sounds_Sounds_List, filteredNames, dataPointers);
	if(all) FillLists(SoundComboBoxList, names);
}

void AGE_Frame::OnSoundsSelect(wxCommandEvent &Event)
{
	auto selections = Sounds_Sounds_List->GetSelections(Items);
	if(selections < 1) return;

	SwapSelection(Event.GetSelection(), Items);
	SoundIDs.resize(selections);
	Sounds_ID->resize(selections);
	Sounds_Unknown1->resize(selections);
	if(GenieVersion >= genie::GV_TEST)
	Sounds_Unknown2->resize(selections);

	genie::Sound * SoundPointer;
	for(auto loop = selections; loop--> 0;)
	{
		SoundPointer = (genie::Sound*)Sounds_Sounds_List->GetClientData(Items.Item(loop));
		SoundIDs[loop] = (SoundPointer - (&GenieFile->Sounds[0]));

		Sounds_ID->container[loop] = &SoundPointer->ID;
		Sounds_Unknown1->container[loop] = &SoundPointer->Unknown1;
		if(GenieVersion >= genie::GV_TEST)
		Sounds_Unknown2->container[loop] = &SoundPointer->Unknown2;
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected sound: "+lexical_cast<string>(SoundIDs[0]), 0);

	Sounds_ID->Update();
	Sounds_Unknown1->Update();
	if(GenieVersion >= genie::GV_TEST)
	Sounds_Unknown2->Update();
	ListSoundItems();
}

void AGE_Frame::OnSoundsAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToListIDFix(GenieFile->Sounds);
	ListSounds();
}

void AGE_Frame::OnSoundsInsert(wxCommandEvent &Event)
{
	auto selections = Sounds_Sounds_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListIDFix(GenieFile->Sounds, SoundIDs[0]);
	ListSounds();
}

void AGE_Frame::OnSoundsDelete(wxCommandEvent &Event)
{
	auto selections = Sounds_Sounds_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromListIDFix(GenieFile->Sounds, SoundIDs);
	ListSounds();
}

void AGE_Frame::OnSoundsCopy(wxCommandEvent &Event)
{
	auto selections = Sounds_Sounds_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Sounds, SoundIDs, copies->Sound);
}

void AGE_Frame::OnSoundsPaste(wxCommandEvent &Event)
{
	auto selections = Sounds_Sounds_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(SoundIDs.size(), copies->Sound.size()))
		{
			PasteToListIDFix(GenieFile->Sounds, SoundIDs, copies->Sound);
		}
	}
	else
	{
		PasteToListIDFix(GenieFile->Sounds, SoundIDs[0], copies->Sound);
	}
	ListSounds();
}

void AGE_Frame::OnSoundsPasteInsert(wxCommandEvent &Event)
{
	auto selections = Sounds_Sounds_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListIDFix(GenieFile->Sounds, SoundIDs[0], copies->Sound);
	ListSounds();
}

string AGE_Frame::GetSoundItemName(short Index)
{
	string Name = "";
	short Selection[2];
	for(short loop = 0; loop < 2; ++loop)
	Selection[loop] = Sounds_Items_SearchFilters[loop]->GetSelection();

	if(Selection[0] > 0)
	for(short loop = 0; loop < 2; ++loop)
	{
		switch(Selection[loop])
		{
			case 1: // DRS
				Name += "DRS "+lexical_cast<string>(GenieFile->Sounds[SoundIDs[0]].Items[Index].ResourceID);
				break;
			case 2: // Probability
				Name += "P "+lexical_cast<string>(GenieFile->Sounds[SoundIDs[0]].Items[Index].Probability);
				break;
			if(GenieVersion >= genie::GV_AoKA)
			{
			case 3: // Civilization
				Name += "C "+lexical_cast<string>(GenieFile->Sounds[SoundIDs[0]].Items[Index].Civ);
				break;
			case 4: // Unknown
				Name += "U "+lexical_cast<string>(GenieFile->Sounds[SoundIDs[0]].Items[Index].Unknown1);
				break;
			}
		}
		Name += ", ";
		if(Selection[loop+1] < 1) break;
	}

	if(!GenieFile->Sounds[SoundIDs[0]].Items[Index].FileName.empty())
	{
		Name += GenieFile->Sounds[SoundIDs[0]].Items[Index].FileName;
	}
	else
	{
		Name += "NewFile.wav";
	}
	return Name;
}

void AGE_Frame::OnSoundItemsSearch(wxCommandEvent &Event)
{
	FirstVisible = 0;
	ListSoundItems();
}

void AGE_Frame::ListSoundItems()
{
	searchText = Sounds_Items_Search->GetValue().Lower();
	excludeText = Sounds_Items_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = Sounds_Items_UseAnd[loop]->GetValue();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->Sounds[SoundIDs[0]].Items.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetSoundItemName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->Sounds[SoundIDs[0]].Items[loop]);
		}
	}
	Listing(Sounds_Items_List, filteredNames, dataPointers);

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;

	wxCommandEvent E;
	OnSoundItemsSelect(E);
}

void AGE_Frame::OnSoundItemsSelect(wxCommandEvent &Event)
{
	auto selections = Sounds_Items_List->GetSelections(Items);
	if(selections > 0)
	{
		SwapSelection(Event.GetSelection(), Items);
		SoundItemIDs.resize(selections);
		SoundItems_Name->resize(selections);
		SoundItems_Resource->resize(selections);
		SoundItems_Probability->resize(selections);
		if(GenieVersion >= genie::GV_AoKA)
		{
			SoundItems_Civ->resize(selections);
			SoundItems_Unknown->resize(selections);
		}

		genie::SoundItem * SoundItemPointer;
		for(auto loop = selections; loop--> 0;)
		{
			SoundItemPointer = (genie::SoundItem*)Sounds_Items_List->GetClientData(Items.Item(loop));
			SoundItemIDs[loop] = (SoundItemPointer - (&GenieFile->Sounds[SoundIDs[0]].Items[0]));

			SoundItems_Name->container[loop] = &SoundItemPointer->FileName;
			SoundItems_Resource->container[loop] = &SoundItemPointer->ResourceID;
			SoundItems_Probability->container[loop] = &SoundItemPointer->Probability;
			if(GenieVersion >= genie::GV_AoKA)
			{
				SoundItems_Civ->container[loop] = &SoundItemPointer->Civ;
				SoundItems_Unknown->container[loop] = &SoundItemPointer->Unknown1;
			}
		}

		SoundItems_Name->Update();
		SoundItems_Resource->Update();
		SoundItems_Probability->Update();
		if(GenieVersion >= genie::GV_AoKA)
		{
			SoundItems_Civ->Update();
			SoundItems_Unknown->Update();
		}
	}
	else
	{
		SoundItems_Name->Clear();
		SoundItems_Resource->Clear();
		SoundItems_Probability->Clear();
		SoundItems_Civ->Clear();
		SoundItems_Civ_ComboBox->SetSelection(0);
		SoundItems_Unknown->Clear();
	}
	SoundItems_Name->Enable(selections);
	SoundItems_Resource->Enable(selections);
	SoundItems_Probability->Enable(selections);
	SoundItems_Civ->Enable(selections);
	SoundItems_Civ_ComboBox->Enable(selections);
	SoundItems_Unknown->Enable(selections);
}

void AGE_Frame::OnSoundItemsAdd(wxCommandEvent &Event)
{
	auto selections = Sounds_Sounds_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToList(GenieFile->Sounds[SoundIDs[0]].Items);
	ListSoundItems();
}

void AGE_Frame::OnSoundItemsInsert(wxCommandEvent &Event)
{
	auto selections = Sounds_Items_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToList(GenieFile->Sounds[SoundIDs[0]].Items, SoundItemIDs[0]);
	ListSoundItems();
}

void AGE_Frame::OnSoundItemsDelete(wxCommandEvent &Event)
{
	auto selections = Sounds_Items_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Sounds[SoundIDs[0]].Items, SoundItemIDs);
	ListSoundItems();
}

void AGE_Frame::OnSoundItemsCopy(wxCommandEvent &Event)
{
	auto selections = Sounds_Items_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Sounds[SoundIDs[0]].Items, SoundItemIDs, copies->SoundItem);
}

void AGE_Frame::OnSoundItemsPaste(wxCommandEvent &Event)
{
	auto selections = Sounds_Items_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(SoundItemIDs.size(), copies->SoundItem.size()))
		{
			PasteToList(GenieFile->Sounds[SoundIDs[0]].Items, SoundItemIDs, copies->SoundItem);
		}
	}
	else
	{
		PasteToList(GenieFile->Sounds[SoundIDs[0]].Items, SoundItemIDs[0], copies->SoundItem);
	}
	ListSoundItems();
}

void AGE_Frame::OnSoundItemsPasteInsert(wxCommandEvent &Event)
{
	auto selections = Sounds_Items_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->Sounds[SoundIDs[0]].Items, SoundItemIDs[0], copies->SoundItem);
	ListSoundItems();
}

void AGE_Frame::OnSoundItemsCopyToSounds(wxCommandEvent &Event)
{
	for(short loop=1; loop < SoundIDs.size(); ++loop)
	{
		GenieFile->Sounds[SoundIDs[loop]].Items = GenieFile->Sounds[SoundIDs[0]].Items;
	}
}

void AGE_Frame::LoadAllSoundFiles(wxCommandEvent &Event)
{
	wxString Name;
	searchText = Sounds_AllItems_Search->GetValue().Lower();
	excludeText = Sounds_AllItems_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = Sounds_AllItems_UseAnd[loop]->GetValue();

	auto selections = Sounds_AllItems_List->GetSelections(Items);
	Sounds_AllItems_List->Clear();

	short Store = SoundIDs[0];
	for(short sound = 0; sound < GenieFile->Sounds.size(); ++sound)
	{
		SoundIDs[0] = sound;
		for(short file = 0; file < GenieFile->Sounds[sound].Items.size(); ++file)
		{
			Name = " S"+lexical_cast<string>(sound)+" F"+lexical_cast<string>(file)+" - "+GetSoundItemName(file);
			if(SearchMatches(Name.Lower()))
			{
				Sounds_AllItems_List->Append(Name);
			}
		}
	}
	SoundIDs[0] = Store;

	Sounds_AllItems_List->SetSelection(Items.Item(0));

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;

	wxCommandEvent E;
	OnAllSoundFileSelect(E);
}

void AGE_Frame::ClearAllSoundFiles(wxCommandEvent &Event)
{
	Sounds_Sounds_Search->SetValue("");
	Sounds_Items_Search->SetValue("");
}

void AGE_Frame::OnAllSoundFileSelect(wxCommandEvent &Event)
{
	SearchAllSubVectors(Sounds_AllItems_List, Sounds_Sounds_Search, Sounds_Items_Search);
}

void AGE_Frame::CreateSoundControls()
{
	Sounds_Main = new wxBoxSizer(wxHORIZONTAL);
	Sounds_ListArea = new wxBoxSizer(wxVERTICAL);
	Sounds_Sounds_Buttons = new wxGridSizer(3, 0, 0);
	SoundItems_ListArea = new wxBoxSizer(wxVERTICAL);
	Sounds_Items_Buttons = new wxGridSizer(3, 0, 0);
	Sounds_DataArea = new wxBoxSizer(wxVERTICAL);
	Sounds_AllArea = new wxBoxSizer(wxVERTICAL);

	Tab_Sounds = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	Sounds_Sounds = new wxStaticBoxSizer(wxVERTICAL, Tab_Sounds, "Sounds");
	Sounds_Sounds_Search = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_Sounds_Search_R = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_Sounds_List = new wxListBox(Tab_Sounds, wxID_ANY, wxDefaultPosition, wxSize(200, 100), 0, NULL, wxLB_EXTENDED);
	Sounds_Add = new wxButton(Tab_Sounds, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Sounds_Insert = new wxButton(Tab_Sounds, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Sounds_Delete = new wxButton(Tab_Sounds, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Sounds_Copy = new wxButton(Tab_Sounds, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Sounds_Paste = new wxButton(Tab_Sounds, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Sounds_PasteInsert = new wxButton(Tab_Sounds, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	Sounds_Items = new wxStaticBoxSizer(wxVERTICAL, Tab_Sounds, "Sound Files");
	for(short loop = 0; loop < 2; ++loop)
	{
		Sounds_Items_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Sounds_Items_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_Sounds, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	Sounds_Items_Search = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_Items_UseAnd[0] = new wxCheckBox(Tab_Sounds, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Sounds_Items_Search_R = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_Items_UseAnd[1] = new wxCheckBox(Tab_Sounds, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Sounds_Items_List = new wxListBox(Tab_Sounds, wxID_ANY, wxDefaultPosition, wxSize(200, 100), 0, NULL, wxLB_EXTENDED);
	SoundItems_Add = new wxButton(Tab_Sounds, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	SoundItems_Insert = new wxButton(Tab_Sounds, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	SoundItems_Delete = new wxButton(Tab_Sounds, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	SoundItems_Copy = new wxButton(Tab_Sounds, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	SoundItems_Paste = new wxButton(Tab_Sounds, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	SoundItems_PasteInsert = new wxButton(Tab_Sounds, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	SoundItems_CopyToSounds = new wxButton(Tab_Sounds, wxID_ANY, "Copy all to selected sounds", wxDefaultPosition, wxSize(5, 20));

	Sounds_ID_Holder = new wxBoxSizer(wxVERTICAL);
	Sounds_ID_Text = new wxStaticText(Tab_Sounds, wxID_ANY, " Sound ID", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Sounds_ID = new TextCtrl_Short(this, AGEwindow, Tab_Sounds);
	Sounds_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	Sounds_Unknown1_Text = new wxStaticText(Tab_Sounds, wxID_ANY, " Sound Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Sounds_Unknown1 = new TextCtrl_Short(this, AGEwindow, Tab_Sounds);
	Sounds_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	Sounds_Unknown2_Text = new wxStaticText(Tab_Sounds, wxID_ANY, " Sound Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Sounds_Unknown2 = new TextCtrl_Long(this, AGEwindow, Tab_Sounds);

	SoundItems_Name_Holder = new wxBoxSizer(wxVERTICAL);
	SoundItems_Name_Text = new wxStaticText(Tab_Sounds, wxID_ANY, " Filename", wxDefaultPosition, wxSize(200, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Name = new TextCtrl_String(this, AGEwindow, Tab_Sounds);
	SoundItems_Resource_Holder = new wxBoxSizer(wxVERTICAL);
	SoundItems_Resource_Text = new wxStaticText(Tab_Sounds, wxID_ANY, " File DRS Resource", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Resource = new TextCtrl_Long(this, AGEwindow, Tab_Sounds);
	SoundItems_Probability_Holder = new wxBoxSizer(wxVERTICAL);
	SoundItems_Probability_Text = new wxStaticText(Tab_Sounds, wxID_ANY, " File Probability", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Probability = new TextCtrl_Short(this, AGEwindow, Tab_Sounds);
	SoundItems_Civ_Holder = new wxBoxSizer(wxVERTICAL);
	SoundItems_Civ_Text = new wxStaticText(Tab_Sounds, wxID_ANY, " File Civilization", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Civ = new TextCtrl_Short(this, AGEwindow, Tab_Sounds);
	SoundItems_Civ_ComboBox = new ComboBox_Plus1(Tab_Sounds, SoundItems_Civ);
	CivComboBoxList.push_back(SoundItems_Civ_ComboBox);
	SoundItems_Unknown_Holder = new wxBoxSizer(wxVERTICAL);
	SoundItems_Unknown_Text = new wxStaticText(Tab_Sounds, wxID_ANY, " File Unknown", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Unknown = new TextCtrl_Short(this, AGEwindow, Tab_Sounds);

	Sounds_AllItems = new wxStaticBoxSizer(wxVERTICAL, Tab_Sounds, "Files of all Sounds");
	Sounds_AllItems_Searches[0] = new wxBoxSizer(wxHORIZONTAL);
	Sounds_AllItems_Searches[1] = new wxBoxSizer(wxHORIZONTAL);
	Sounds_AllItems_Search = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_AllItems_UseAnd[0] = new wxCheckBox(Tab_Sounds, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Sounds_AllItems_Search_R = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_AllItems_UseAnd[1] = new wxCheckBox(Tab_Sounds, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Sounds_AllItems_List = new wxListBox(Tab_Sounds, wxID_ANY, wxDefaultPosition, wxSize(200, 100), 0, NULL, wxLB_EXTENDED);
	Sounds_AllItems_Buttons = new wxBoxSizer(wxHORIZONTAL);
	Sounds_AllItems_Load = new wxButton(Tab_Sounds, wxID_ANY, "Reload", wxDefaultPosition, wxSize(5, 20));
	Sounds_AllItems_Clear = new wxButton(Tab_Sounds, wxID_ANY, "Clear *", wxDefaultPosition, wxSize(5, 20));
	Sounds_AllItems_Clear->SetToolTip("Clear the modified search texts");

	Sounds_Sounds_Buttons->Add(Sounds_Add, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_Delete, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_Insert, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_Copy, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_Paste, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_PasteInsert, 1, wxEXPAND);

	Sounds_Sounds->Add(Sounds_Sounds_Search, 0, wxEXPAND);
	Sounds_Sounds->Add(Sounds_Sounds_Search_R, 0, wxEXPAND);
	Sounds_Sounds->AddSpacer(2);
	Sounds_Sounds->Add(Sounds_Sounds_List, 1, wxEXPAND);
	Sounds_Sounds->AddSpacer(2);
	Sounds_Sounds->Add(Sounds_Sounds_Buttons, 0, wxEXPAND);

	Sounds_ListArea->AddSpacer(5);
	Sounds_ListArea->Add(Sounds_Sounds, 1, wxEXPAND);
	Sounds_ListArea->AddSpacer(5);

	Sounds_Items_Buttons->Add(SoundItems_Add, 1, wxEXPAND);
	Sounds_Items_Buttons->Add(SoundItems_Delete, 1, wxEXPAND);
	Sounds_Items_Buttons->Add(SoundItems_Insert, 1, wxEXPAND);
	Sounds_Items_Buttons->Add(SoundItems_Copy, 1, wxEXPAND);
	Sounds_Items_Buttons->Add(SoundItems_Paste, 1, wxEXPAND);
	Sounds_Items_Buttons->Add(SoundItems_PasteInsert, 1, wxEXPAND);

	Sounds_Items_Searches[0]->Add(Sounds_Items_Search, 1, wxEXPAND);
	Sounds_Items_Searches[0]->AddSpacer(2);
	Sounds_Items_Searches[0]->Add(Sounds_Items_UseAnd[0], 0, wxEXPAND);
	Sounds_Items_Searches[1]->Add(Sounds_Items_Search_R, 1, wxEXPAND);
	Sounds_Items_Searches[1]->AddSpacer(2);
	Sounds_Items_Searches[1]->Add(Sounds_Items_UseAnd[1], 0, wxEXPAND);
	Sounds_Items->Add(Sounds_Items_Searches[0], 0, wxEXPAND);
	Sounds_Items->Add(Sounds_Items_Searches[1], 0, wxEXPAND);
	Sounds_Items->Add(Sounds_Items_SearchFilters[0], 0, wxEXPAND);
	Sounds_Items->Add(Sounds_Items_SearchFilters[1], 0, wxEXPAND);
	Sounds_Items->AddSpacer(2);
	Sounds_Items->Add(Sounds_Items_List, 1, wxEXPAND);
	Sounds_Items->AddSpacer(2);
	Sounds_Items->Add(Sounds_Items_Buttons, 0, wxEXPAND);
	Sounds_Items->AddSpacer(2);
	Sounds_Items->Add(SoundItems_CopyToSounds, 0, wxEXPAND);

	SoundItems_ListArea->AddSpacer(5);
	SoundItems_ListArea->Add(Sounds_Items, 1, wxEXPAND);
	SoundItems_ListArea->AddSpacer(5);

	Sounds_ID_Holder->Add(Sounds_ID_Text, 0, wxEXPAND);
	Sounds_ID_Holder->Add(Sounds_ID, 1, wxEXPAND);
	Sounds_Unknown1_Holder->Add(Sounds_Unknown1_Text, 0, wxEXPAND);
	Sounds_Unknown1_Holder->Add(Sounds_Unknown1, 1, wxEXPAND);
	Sounds_Unknown2_Holder->Add(Sounds_Unknown2_Text, 0, wxEXPAND);
	Sounds_Unknown2_Holder->Add(Sounds_Unknown2, 1, wxEXPAND);
	SoundItems_Name_Holder->Add(SoundItems_Name_Text, 0, wxEXPAND);
	SoundItems_Name_Holder->Add(SoundItems_Name, 1, wxEXPAND);
	SoundItems_Resource_Holder->Add(SoundItems_Resource_Text, 0, wxEXPAND);
	SoundItems_Resource_Holder->Add(SoundItems_Resource, 1, wxEXPAND);
	SoundItems_Probability_Holder->Add(SoundItems_Probability_Text, 0, wxEXPAND);
	SoundItems_Probability_Holder->Add(SoundItems_Probability, 1, wxEXPAND);
	SoundItems_Civ_Holder->Add(SoundItems_Civ_Text, 0, wxEXPAND);
	SoundItems_Civ_Holder->Add(SoundItems_Civ, 1, wxEXPAND);
	SoundItems_Civ_Holder->Add(SoundItems_Civ_ComboBox, 1, wxEXPAND);
	SoundItems_Unknown_Holder->Add(SoundItems_Unknown_Text, 0, wxEXPAND);
	SoundItems_Unknown_Holder->Add(SoundItems_Unknown, 1, wxEXPAND);

	Sounds_AllItems_Searches[0]->Add(Sounds_AllItems_Search, 1, wxEXPAND);
	Sounds_AllItems_Searches[0]->AddSpacer(2);
	Sounds_AllItems_Searches[0]->Add(Sounds_AllItems_UseAnd[0], 0, wxEXPAND);
	Sounds_AllItems_Searches[1]->Add(Sounds_AllItems_Search_R, 1, wxEXPAND);
	Sounds_AllItems_Searches[1]->AddSpacer(2);
	Sounds_AllItems_Searches[1]->Add(Sounds_AllItems_UseAnd[1], 0, wxEXPAND);
	Sounds_AllItems->Add(Sounds_AllItems_Searches[0], 0, wxEXPAND);
	Sounds_AllItems->Add(Sounds_AllItems_Searches[1], 0, wxEXPAND);
	Sounds_AllItems->AddSpacer(2);
	Sounds_AllItems->Add(Sounds_AllItems_List, 1, wxEXPAND);
	Sounds_AllItems->AddSpacer(2);
	Sounds_AllItems_Buttons->Add(Sounds_AllItems_Load, 2, wxEXPAND);
	Sounds_AllItems_Buttons->AddSpacer(2);
	Sounds_AllItems_Buttons->Add(Sounds_AllItems_Clear, 1, wxEXPAND);
	Sounds_AllItems->Add(Sounds_AllItems_Buttons, 0, wxEXPAND);
	Sounds_AllArea->AddSpacer(5);
	Sounds_AllArea->Add(Sounds_AllItems, 1, wxEXPAND);
	Sounds_AllArea->AddSpacer(5);

	Sounds_DataArea->AddSpacer(5);
	Sounds_DataArea->Add(Sounds_ID_Holder, 0, wxEXPAND);
	Sounds_DataArea->AddSpacer(5);
	Sounds_DataArea->Add(Sounds_Unknown1_Holder, 0, wxEXPAND);
	Sounds_DataArea->AddSpacer(5);
	Sounds_DataArea->Add(Sounds_Unknown2_Holder, 0, wxEXPAND);
	Sounds_DataArea->AddSpacer(5);
	Sounds_DataArea->Add(SoundItems_Name_Holder, 0, wxEXPAND);
	Sounds_DataArea->AddSpacer(5);
	Sounds_DataArea->Add(SoundItems_Resource_Holder, 0, wxEXPAND);
	Sounds_DataArea->AddSpacer(5);
	Sounds_DataArea->Add(SoundItems_Probability_Holder, 0, wxEXPAND);
	Sounds_DataArea->AddSpacer(5);
	Sounds_DataArea->Add(SoundItems_Civ_Holder, 0, wxEXPAND);
	Sounds_DataArea->AddSpacer(5);
	Sounds_DataArea->Add(SoundItems_Unknown_Holder, 0, wxEXPAND);

	Sounds_Main->AddSpacer(5);
	Sounds_Main->Add(Sounds_ListArea, 1, wxEXPAND);
	Sounds_Main->AddSpacer(5);
	Sounds_Main->Add(SoundItems_ListArea, 1, wxEXPAND);
	Sounds_Main->AddSpacer(5);
	Sounds_Main->Add(Sounds_DataArea, 1, wxEXPAND);
	Sounds_Main->AddSpacer(5);
	Sounds_Main->Add(Sounds_AllArea, 1, wxEXPAND);
	Sounds_Main->AddSpacer(5);

	if(EnableIDFix)
	Sounds_ID->Enable(false);

	Tab_Sounds->SetSizer(Sounds_Main);

	for(short loop = 0; loop < 2; ++loop)
	{
		Connect(Sounds_Items_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsSearch));
		Connect(Sounds_Items_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
		Connect(Sounds_AllItems_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::LoadAllSoundFiles));
	}
	Connect(Sounds_Sounds_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSoundsSelect));
	Connect(Sounds_Sounds_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnSoundsSearch));
	Connect(Sounds_Sounds_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnSoundsSearch));
	Connect(Sounds_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundsAdd));
	Connect(Sounds_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundsInsert));
	Connect(Sounds_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundsDelete));
	Connect(Sounds_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundsCopy));
	Connect(Sounds_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundsPaste));
	Connect(Sounds_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundsPasteInsert));
	Connect(Sounds_Items_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSoundItemsSelect));
	Connect(Sounds_Items_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnSoundItemsSearch));
	Connect(Sounds_Items_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnSoundItemsSearch));
	Connect(SoundItems_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsAdd));
	Connect(SoundItems_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsInsert));
	Connect(SoundItems_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsDelete));
	Connect(SoundItems_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsCopy));
	Connect(SoundItems_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsPaste));
	Connect(SoundItems_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsPasteInsert));
	Connect(SoundItems_CopyToSounds->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsCopyToSounds));
	Connect(Sounds_AllItems_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::LoadAllSoundFiles));
	Connect(Sounds_AllItems_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::LoadAllSoundFiles));
	Connect(Sounds_AllItems_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnAllSoundFileSelect));
	Connect(Sounds_AllItems_Load->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::LoadAllSoundFiles));
	Connect(Sounds_AllItems_Clear->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::ClearAllSoundFiles));

	SoundItems_Name->Connect(SoundItems_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Sounds), NULL, this);
}

void AGE_Frame::OnKillFocus_Sounds(wxFocusEvent &Event)
{
	if(((AGETextCtrl*)Event.GetEventObject())->SaveEdits() != 0) return;
	ListSoundItems();
	Event.Skip();
}
