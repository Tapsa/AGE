
#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetSoundName(short &Index)
{
	string Name = "File Count: ";
	Name += lexical_cast<string>(GenieFile->Sounds[Index].Items.size());
	return Name;
}

void AGE_Frame::OnSoundsSearch(wxCommandEvent& Event)
{
	ListSounds(false);
}

void AGE_Frame::ListSounds(bool Sized)
{
	wxString Name, CompareText;
	SearchText = Sounds_Sounds_Search->GetValue().Lower();
	ExcludeText = Sounds_Sounds_Search_R->GetValue().Lower();

	short Selections = Sounds_Sounds_List->GetSelections(Items);
	if(Sounds_Sounds_List->GetCount() > 0) Sounds_Sounds_List->Clear();

	short IDCount = 13, SoundIDs[IDCount];
	if(Sized)
	{
		for(short loop = 0;loop < 2;loop++)
		SoundIDs[loop] = Units_ComboBox_TrainSound[loop]->GetSelection();
		SoundIDs[2] = Units_ComboBox_SelectionSound->GetSelection();
		SoundIDs[3] = Units_ComboBox_DyingSound->GetSelection();
		SoundIDs[4] = Units_ComboBox_AttackSound->GetSelection();
		SoundIDs[5] = Units_ComboBox_MoveSound->GetSelection();
		SoundIDs[6] = Units_ComboBox_StopSound->GetSelection();
		SoundIDs[7] = Units_ComboBox_ConstructionSound->GetSelection();
		SoundIDs[8] = Terrains_ComboBox_SoundID->GetSelection();
		SoundIDs[9] = Graphics_ComboBox_SoundID->GetSelection();
		for(short loop = 0;loop < 3;loop++)
		SoundIDs[loop+10] = Graphics_ComboBox_AttackSoundID[loop]->GetSelection();

		for(short loop = 0;loop < 2;loop++)
		if(Units_ComboBox_TrainSound[loop]->GetCount() > 0)
		{
			Units_ComboBox_TrainSound[loop]->Clear();
		}
		if(Units_ComboBox_SelectionSound->GetCount() > 0)
		{
			Units_ComboBox_SelectionSound->Clear();
		}
		if(Units_ComboBox_DyingSound->GetCount() > 0)
		{
			Units_ComboBox_DyingSound->Clear();
		}
		if(Units_ComboBox_AttackSound->GetCount() > 0)
		{
			Units_ComboBox_AttackSound->Clear();
		}
		if(Units_ComboBox_MoveSound->GetCount() > 0)
		{
			Units_ComboBox_MoveSound->Clear();
		}
		if(Units_ComboBox_StopSound->GetCount() > 0)
		{
			Units_ComboBox_StopSound->Clear();
		}
		if(Units_ComboBox_ConstructionSound->GetCount() > 0)
		{
			Units_ComboBox_ConstructionSound->Clear();
		}
		if(Terrains_ComboBox_SoundID->GetCount() > 0)
		{
			Terrains_ComboBox_SoundID->Clear();
		}
		if(Graphics_ComboBox_SoundID->GetCount() > 0)
		{
			Graphics_ComboBox_SoundID->Clear();
		}
		for(short loop = 0;loop < 3;loop++)
		if(Graphics_ComboBox_AttackSoundID[loop]->GetCount() > 0)
		{
			Graphics_ComboBox_AttackSoundID[loop]->Clear();
		}

		for(short loop = 0;loop < IDCount;loop++)
		{
			if(SoundIDs[loop] == wxNOT_FOUND)
			{
				SoundIDs[loop] = 0;
			}
		}

		for(short loop = 0;loop < 2;loop++)
		Units_ComboBox_TrainSound[loop]->Append("-1 - None");
		Units_ComboBox_SelectionSound->Append("-1 - None");
		Units_ComboBox_DyingSound->Append("-1 - None");
		Units_ComboBox_AttackSound->Append("-1 - None");
		Units_ComboBox_MoveSound->Append("-1 - None");
		Units_ComboBox_StopSound->Append("-1 - None");
		Units_ComboBox_ConstructionSound->Append("-1 - None");
		Terrains_ComboBox_SoundID->Append("-1 - None");
		Graphics_ComboBox_SoundID->Append("-1 - None");
		for(short loop = 0;loop < 3;loop++)
		Graphics_ComboBox_AttackSoundID[loop]->Append("-1 - None");
	}

	for(short loop = 0;loop < GenieFile->Sounds.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetSoundName(loop);
		CompareText = Name.Lower();
		if(SearchMatches(CompareText))
		{
			Sounds_Sounds_List->Append(Name, (void*)&GenieFile->Sounds[loop]);
		}
		if(Sized)
		{
			for(short loop = 0;loop < 2;loop++)
			Units_ComboBox_TrainSound[loop]->Append(Name);
			Units_ComboBox_SelectionSound->Append(Name);
			Units_ComboBox_DyingSound->Append(Name);
			Units_ComboBox_AttackSound->Append(Name);
			Units_ComboBox_MoveSound->Append(Name);
			Units_ComboBox_StopSound->Append(Name);
			Units_ComboBox_ConstructionSound->Append(Name);
			Terrains_ComboBox_SoundID->Append(Name);
			Graphics_ComboBox_SoundID->Append(Name);
			for(short loop = 0;loop < 3;loop++)
			Graphics_ComboBox_AttackSoundID[loop]->Append(Name);
		}
	}

	ListingFix(Selections, Sounds_Sounds_List);
	if(Sized)
	{
		for(short loop = 0;loop < 2;loop++)
		Units_ComboBox_TrainSound[loop]->SetSelection(SoundIDs[loop]);
		Units_ComboBox_SelectionSound->SetSelection(SoundIDs[2]);
		Units_ComboBox_DyingSound->SetSelection(SoundIDs[3]);
		Units_ComboBox_AttackSound->SetSelection(SoundIDs[4]);
		Units_ComboBox_MoveSound->SetSelection(SoundIDs[5]);
		Units_ComboBox_StopSound->SetSelection(SoundIDs[6]);
		Units_ComboBox_ConstructionSound->SetSelection(SoundIDs[7]);
		Terrains_ComboBox_SoundID->SetSelection(SoundIDs[8]);
		Graphics_ComboBox_SoundID->SetSelection(SoundIDs[9]);
		for(short loop = 0;loop < 3;loop++)
		Graphics_ComboBox_AttackSoundID[loop]->SetSelection(SoundIDs[loop+10]);
	}

	wxCommandEvent E;
	OnSoundsSelect(E);
}

void AGE_Frame::OnSoundsSelect(wxCommandEvent& Event)
{
	short Selections = Sounds_Sounds_List->GetSelections(Items);
	if(Selections != 0)
	{
		SoundIDs.resize(Selections);
		genie::Sound * SoundPointer;
		for(short loop = Selections-1;loop >= 0;loop--)
		{
			SoundPointer = (genie::Sound*)Sounds_Sounds_List->GetClientData(Items.Item(loop));
			SoundIDs[loop] = (SoundPointer - (&GenieFile->Sounds[0]));
		}
		Sounds_ID->ChangeValue(lexical_cast<string>(SoundPointer->ID));
		Sounds_ID->Container = &SoundPointer->ID;
		Sounds_Unknown->ChangeValue(lexical_cast<string>(SoundPointer->Unknown1));
		Sounds_Unknown->Container = &SoundPointer->Unknown1;
		ListSoundItems();
	}
}

void AGE_Frame::OnSoundsAdd(wxCommandEvent& Event)
{
	if(GenieFile != NULL)
	{
		wxBusyCursor WaitCursor;
		genie::Sound Temp;
		GenieFile->Sounds.push_back(Temp);
		if(EnableIDFix)
		GenieFile->Sounds[GenieFile->Sounds.size()-1].ID = (int32_t)(GenieFile->Sounds.size()-1); // ID Fix
		Added = true;
		ListSounds();
	}
}

void AGE_Frame::OnSoundsInsert(wxCommandEvent& Event)
{
	short Selections = Sounds_Sounds_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::Sound Temp;
		GenieFile->Sounds.insert(GenieFile->Sounds.begin() + SoundIDs[0], Temp);
		if(EnableIDFix)
		for(short loop = SoundIDs[0];loop < GenieFile->Sounds.size();loop++) // ID Fix
		GenieFile->Sounds[loop].ID = (int32_t)loop;
		ListSounds();
	}
}

void AGE_Frame::OnSoundsDelete(wxCommandEvent& Event)
{
	short Selections = Sounds_Sounds_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop = Selections-1;loop >= 0;loop--)
		GenieFile->Sounds.erase(GenieFile->Sounds.begin() + SoundIDs[loop]);
		if(EnableIDFix)
		for(short loop = SoundIDs[0];loop < GenieFile->Sounds.size();loop++)	//	ID Fix
		GenieFile->Sounds[loop].ID = (int32_t)loop;
		ListSounds();
	}
}

void AGE_Frame::OnSoundsCopy(wxCommandEvent& Event)
{
	short Selections = Sounds_Sounds_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		SoundCopies.resize(Selections);
		for(short loop = 0;loop < Selections;loop++)
		SoundCopies[loop] = GenieFile->Sounds[SoundIDs[loop]];
	}
}

void AGE_Frame::OnSoundsPaste(wxCommandEvent& Event)
{
	short Selections = Sounds_Sounds_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		if(SoundCopies.size()+SoundIDs[0] > GenieFile->Sounds.size())
		GenieFile->Sounds.resize(SoundCopies.size()+SoundIDs[0]);
		for(short loop = 0;loop < SoundCopies.size();loop++)
		{
			GenieFile->Sounds[SoundIDs[0]+loop] = SoundCopies[loop];
			if(EnableIDFix)
			GenieFile->Sounds[SoundIDs[0]+loop].ID = (int32_t)(SoundIDs[0]+loop); // ID Fix
		}
		ListSounds();
	}
}

void AGE_Frame::OnSoundsPasteInsert(wxCommandEvent& Event)
{
	short Selections = Sounds_Sounds_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::Sound Temp;
		GenieFile->Sounds.insert(GenieFile->Sounds.begin() + SoundIDs[0], SoundCopies.size(), Temp);
		for(short loop = 0;loop < SoundCopies.size();loop++)
		GenieFile->Sounds[SoundIDs[0]+loop] = SoundCopies[loop];
		if(EnableIDFix)
		for(short loop = SoundIDs[0];loop < GenieFile->Sounds.size();loop++) // ID Fix
		GenieFile->Sounds[loop].ID = (int32_t)loop;
		ListSounds();
	}
}

string AGE_Frame::GetSoundItemName(short &Index)
{
	string Name = "";
	short Selection[2];
	for(short loop = 0;loop < 2;loop++)
	Selection[loop] = Sounds_Items_SearchFilters[loop]->GetSelection();

	if(Selection[0] > 0)
	for(short loop = 0;loop < 2;loop++)
	{
		if(Selection[loop] == 1)	// DRS
		{
			Name += "DRS ";
			Name += lexical_cast<string>(GenieFile->Sounds[SoundIDs[0]].Items[Index].ResourceID);
		}
		else if(Selection[loop] == 2)	// Probability
		{
			Name += "P ";
			Name += lexical_cast<string>(GenieFile->Sounds[SoundIDs[0]].Items[Index].Probability);
		}
		else if(GameVersion < 2);
		else if(Selection[loop] == 3)	// Civilization
		{
			Name += "C ";
			Name += lexical_cast<string>(GenieFile->Sounds[SoundIDs[0]].Items[Index].Civ);
		}
		else if(Selection[loop] == 4)	// Unknown
		{
			Name += "U ";
			Name += lexical_cast<string>(GenieFile->Sounds[SoundIDs[0]].Items[Index].Unknown1);
		}
		Name += ", ";
		if(Selection[loop+1] < 1) break;
	}

	if(GenieFile->Sounds[SoundIDs[0]].Items[Index].FileName != "")
	{
		Name += GenieFile->Sounds[SoundIDs[0]].Items[Index].FileName;
	}
	else
	{
		Name += "NewFile.wav";
	}
	return Name;
}

void AGE_Frame::OnSoundItemsSearch(wxCommandEvent& Event)
{
	ListSoundItems();
}

void AGE_Frame::ListSoundItems()
{
	wxString Name, CompareText;
	SearchText = Sounds_Items_Search->GetValue().Lower();
	ExcludeText = Sounds_Items_Search_R->GetValue().Lower();
	for(short loop = 0;loop < 2;loop++)
	{
		if(Sounds_Items_UseAnd[loop]->GetValue() == true)
		UseAnd[loop] = true; else UseAnd[loop] = false;
	}

	short Selections = Sounds_Items_List->GetSelections(Items);
	if(Sounds_Items_List->GetCount() > 0) Sounds_Items_List->Clear();

	for(short loop = 0;loop < GenieFile->Sounds[SoundIDs[0]].Items.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetSoundItemName(loop);
		CompareText = Name.Lower();
		if(SearchMatches(CompareText))
		{
			Sounds_Items_List->Append(Name, (void*)&GenieFile->Sounds[SoundIDs[0]].Items[loop]);
		}
	}
	ListingFix(Selections, Sounds_Items_List);

	for(short loop = 0;loop < 2;loop++)
	UseAnd[loop] = false;

	wxCommandEvent E;
	OnSoundItemsSelect(E);
}

void AGE_Frame::OnSoundItemsSelect(wxCommandEvent& Event)
{
	short Selections = Sounds_Items_List->GetSelections(Items);
	if(Selections != 0)
	{
		SoundItemIDs.resize(Selections);
		genie::SoundItem * SoundItemPointer;
		for(short loop = Selections-1;loop >= 0;loop--)
		{
			SoundItemPointer = (genie::SoundItem*)Sounds_Items_List->GetClientData(Items.Item(loop));
			SoundItemIDs[loop] = (SoundItemPointer - (&GenieFile->Sounds[SoundIDs[0]].Items[0]));
		}
		SoundItems_Name->ChangeValue(SoundItemPointer->FileName);
		SoundItems_Name->Container = &SoundItemPointer->FileName;
		SoundItems_Resource->ChangeValue(lexical_cast<string>(SoundItemPointer->ResourceID));
		SoundItems_Resource->Container = &SoundItemPointer->ResourceID;
		SoundItems_Probability->ChangeValue(lexical_cast<string>(SoundItemPointer->Probability));
		SoundItems_Probability->Container = &SoundItemPointer->Probability;
		if(GameVersion >= 2)
		{
			SoundItems_Civ->ChangeValue(lexical_cast<string>(SoundItemPointer->Civ));
			SoundItems_Civ->Container = &SoundItemPointer->Civ;
			SoundItems_ComboBox_Civ->SetSelection(SoundItemPointer->Civ + 1);
			SoundItems_Unknown->ChangeValue(lexical_cast<string>(SoundItemPointer->Unknown1));
			SoundItems_Unknown->Container = &SoundItemPointer->Unknown1;
		}
		//SoundFile();
		//SoundFile.Play();
	}
	else
	{
		SoundItems_Name->ChangeValue("0");
		SoundItems_Resource->ChangeValue("0");
		SoundItems_Probability->ChangeValue("0");
		SoundItems_Civ->ChangeValue("0");
		SoundItems_ComboBox_Civ->SetSelection(0);
		SoundItems_Unknown->ChangeValue("0");
	}
}

void AGE_Frame::OnSoundItemsAdd(wxCommandEvent& Event)
{
	short Selections = Sounds_Sounds_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::SoundItem Temp;
		GenieFile->Sounds[SoundIDs[0]].Items.push_back(Temp);
		Added = true;
		ListSoundItems();
	}
}

void AGE_Frame::OnSoundItemsInsert(wxCommandEvent& Event)
{
	short Selections = Sounds_Items_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::SoundItem Temp;
		GenieFile->Sounds[SoundIDs[0]].Items.insert(GenieFile->Sounds[SoundIDs[0]].Items.begin() + SoundItemIDs[0], Temp);
		ListSoundItems();
	}
}

void AGE_Frame::OnSoundItemsDelete(wxCommandEvent& Event)
{
	short Selections = Sounds_Items_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop = Selections-1;loop >= 0;loop--)
		GenieFile->Sounds[SoundIDs[0]].Items.erase(GenieFile->Sounds[SoundIDs[0]].Items.begin() + SoundItemIDs[loop]);
		ListSoundItems();
	}
}

void AGE_Frame::OnSoundItemsCopy(wxCommandEvent& Event)
{
	short Selections = Sounds_Items_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		SoundItemCopies.resize(Selections);
		for(short loop = 0;loop < Selections;loop++)
		SoundItemCopies[loop] = GenieFile->Sounds[SoundIDs[0]].Items[SoundItemIDs[loop]];
	}
}

void AGE_Frame::OnSoundItemsPaste(wxCommandEvent& Event)
{
	short Selections = Sounds_Items_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		if(SoundItemCopies.size()+SoundItemIDs[0] > GenieFile->Sounds[SoundIDs[0]].Items.size())
		GenieFile->Sounds[SoundIDs[0]].Items.resize(SoundItemCopies.size()+SoundItemIDs[0]);
		for(short loop = 0;loop < SoundItemCopies.size();loop++)
		GenieFile->Sounds[SoundIDs[0]].Items[SoundItemIDs[0]+loop] = SoundItemCopies[loop];
		ListSoundItems();
	}
}

void AGE_Frame::OnSoundItemsPasteInsert(wxCommandEvent& Event)
{
	short Selections = Sounds_Items_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::SoundItem Temp;
		GenieFile->Sounds[SoundIDs[0]].Items.insert(GenieFile->Sounds[SoundIDs[0]].Items.begin() + SoundItemIDs[0], SoundItemCopies.size(), Temp);
		for(short loop = 0;loop < SoundItemCopies.size();loop++)
		GenieFile->Sounds[SoundIDs[0]].Items[SoundItemIDs[0]+loop] = SoundItemCopies[loop];
		ListSoundItems();
	}
}

void AGE_Frame::LoadAllSoundFiles(wxCommandEvent& Event)
{
	wxString Name, CompareText;
	SearchText = Sounds_AllItems_Search->GetValue().Lower();
	ExcludeText = Sounds_AllItems_Search_R->GetValue().Lower();
	for(short loop = 0;loop < 2;loop++)
	{
		if(Sounds_AllItems_UseAnd[loop]->GetValue() == true)
		UseAnd[loop] = true; else UseAnd[loop] = false;
	}

	short Selections = Sounds_AllItems_List->GetSelections(Items);
	if(Sounds_AllItems_List->GetCount() > 0) Sounds_AllItems_List->Clear();

	short Store = SoundIDs[0];
	for(short sound = 0;sound < GenieFile->Sounds.size();sound++)
	{
		SoundIDs[0] = sound;
		for(short file = 0;file < GenieFile->Sounds[sound].Items.size();file++)
		{
			Name = " S"+lexical_cast<string>(sound)+" F"+lexical_cast<string>(file)+" - "+GetSoundItemName(file);
			CompareText = Name.Lower();
			if(SearchMatches(CompareText))
			{
				Sounds_AllItems_List->Append(Name);
			}
		}
	}
	SoundIDs[0] = Store;

	Sounds_AllItems_List->SetSelection(Items.Item(0));

	for(short loop = 0;loop < 2;loop++)
	UseAnd[loop] = false;

	wxCommandEvent E;
	OnAllSoundFileSelect(E);
}

void AGE_Frame::OnAllSoundFileSelect(wxCommandEvent& Event)
{
	short Selections = Sounds_AllItems_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxString SoundID, FileName, Line = Sounds_AllItems_List->GetString(Items.Item(0));
		size_t Found;
		Found = Line.find(" ", 3);
		SoundID = Line.substr(2, Found-1); // Cutting the sound number.
		FileName = Line.substr(Found+2, Line.find(" ", Found+3)-Found); // Cutting the filename.
		Sounds_Sounds_Search->SetValue(" "+SoundID+"-");
		Sounds_Items_Search->SetValue(" "+FileName);
	}
}

void AGE_Frame::CreateSoundControls()
{
	Sounds_Main = new wxBoxSizer(wxHORIZONTAL);
	Sounds_ListArea = new wxBoxSizer(wxVERTICAL);
	Sounds_Sounds_Buttons = new wxGridSizer(3, 0, 0);
	SoundItems_ListArea = new wxBoxSizer(wxVERTICAL);
	Sounds_Items_Buttons = new wxGridSizer(3, 0, 0);
	Sounds_DataArea = new wxBoxSizer(wxVERTICAL);

	Tab_Sounds = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	Sounds_Sounds = new wxStaticBoxSizer(wxVERTICAL, Tab_Sounds, "Sounds");
	Sounds_Sounds_Search = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_Sounds_Search_R = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_Sounds_List = new wxListBox(Tab_Sounds, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, wxLB_EXTENDED);
	Sounds_Add = new wxButton(Tab_Sounds, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Sounds_Insert = new wxButton(Tab_Sounds, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Sounds_Delete = new wxButton(Tab_Sounds, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Sounds_Copy = new wxButton(Tab_Sounds, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Sounds_Paste = new wxButton(Tab_Sounds, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Sounds_PasteInsert = new wxButton(Tab_Sounds, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	Sounds_Items = new wxStaticBoxSizer(wxVERTICAL, Tab_Sounds, "Sound Files");
	for(short loop = 0;loop < 2;loop++)
	{
		Sounds_Items_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Sounds_Items_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_Sounds, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	Sounds_Items_Search = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_Items_UseAnd[0] = new wxCheckBox(Tab_Sounds, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Sounds_Items_Search_R = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_Items_UseAnd[1] = new wxCheckBox(Tab_Sounds, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Sounds_Items_List = new wxListBox(Tab_Sounds, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, wxLB_EXTENDED);
	SoundItems_Add = new wxButton(Tab_Sounds, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	SoundItems_Insert = new wxButton(Tab_Sounds, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	SoundItems_Delete = new wxButton(Tab_Sounds, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	SoundItems_Copy = new wxButton(Tab_Sounds, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	SoundItems_Paste = new wxButton(Tab_Sounds, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	SoundItems_PasteInsert = new wxButton(Tab_Sounds, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	Sounds_Holder_ID = new wxBoxSizer(wxVERTICAL);
	Sounds_Text_ID = new wxStaticText(Tab_Sounds, wxID_ANY, " Sound ID", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Sounds_ID = new TextCtrl_Long(Tab_Sounds, "0", NULL);
	Sounds_Holder_Unknown = new wxBoxSizer(wxVERTICAL);
	Sounds_Text_Unknown = new wxStaticText(Tab_Sounds, wxID_ANY, " Sound Unknown", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Sounds_Unknown = new TextCtrl_Long(Tab_Sounds, "0", NULL);

	SoundItems_Holder_Name = new wxBoxSizer(wxVERTICAL);
	SoundItems_Text_Name = new wxStaticText(Tab_Sounds, wxID_ANY, " Filename", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Name = new TextCtrl_String(Tab_Sounds, "0", NULL);
	SoundItems_Holder_Resource = new wxBoxSizer(wxVERTICAL);
	SoundItems_Text_Resource = new wxStaticText(Tab_Sounds, wxID_ANY, " File DRS Resource", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Resource = new TextCtrl_Long(Tab_Sounds, "0", NULL);
	SoundItems_Holder_Probability = new wxBoxSizer(wxVERTICAL);
	SoundItems_Text_Probability = new wxStaticText(Tab_Sounds, wxID_ANY, " File Probability", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Probability = new TextCtrl_Short(Tab_Sounds, "0", NULL);
	SoundItems_Holder_Civ = new wxBoxSizer(wxVERTICAL);
	SoundItems_Text_Civ = new wxStaticText(Tab_Sounds, wxID_ANY, " File Civilization", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Civ = new TextCtrl_Short(Tab_Sounds, "0", NULL);
	SoundItems_ComboBox_Civ = new ComboBox_Short(Tab_Sounds, SoundItems_Civ);
	SoundItems_Holder_Unknown = new wxBoxSizer(wxVERTICAL);
	SoundItems_Text_Unknown = new wxStaticText(Tab_Sounds, wxID_ANY, " File Unknown", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Unknown = new TextCtrl_Short(Tab_Sounds, "0", NULL);

	Sounds_AllItems = new wxStaticBoxSizer(wxVERTICAL, Tab_Sounds, "Files of all Sounds");
	Sounds_AllItems_Searches[0] = new wxBoxSizer(wxHORIZONTAL);
	Sounds_AllItems_Searches[1] = new wxBoxSizer(wxHORIZONTAL);
	Sounds_AllItems_Search = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_AllItems_UseAnd[0] = new wxCheckBox(Tab_Sounds, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Sounds_AllItems_Search_R = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_AllItems_UseAnd[1] = new wxCheckBox(Tab_Sounds, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Sounds_AllItems_List = new wxListBox(Tab_Sounds, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, wxLB_EXTENDED);
	Sounds_AllItems_Load = new wxButton(Tab_Sounds, wxID_ANY, "Reload", wxDefaultPosition, wxSize(5, 20));

	Sounds_Sounds_Buttons->Add(Sounds_Add, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_Insert, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_Delete, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_Copy, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_Paste, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_PasteInsert, 1, wxEXPAND);

	Sounds_Sounds->Add(Sounds_Sounds_Search, 0, wxEXPAND);
	Sounds_Sounds->Add(Sounds_Sounds_Search_R, 0, wxEXPAND);
	Sounds_Sounds->Add(-1, 2);
	Sounds_Sounds->Add(Sounds_Sounds_List, 1, wxEXPAND);
	Sounds_Sounds->Add(-1, 2);
	Sounds_Sounds->Add(Sounds_Sounds_Buttons, 0, wxEXPAND);

	Sounds_ListArea->Add(-1, 10);
	Sounds_ListArea->Add(Sounds_Sounds, 1, wxEXPAND);
	Sounds_ListArea->Add(-1, 10);

	Sounds_Items_Buttons->Add(SoundItems_Add, 1, wxEXPAND);
	Sounds_Items_Buttons->Add(SoundItems_Insert, 1, wxEXPAND);
	Sounds_Items_Buttons->Add(SoundItems_Delete, 1, wxEXPAND);
	Sounds_Items_Buttons->Add(SoundItems_Copy, 1, wxEXPAND);
	Sounds_Items_Buttons->Add(SoundItems_Paste, 1, wxEXPAND);
	Sounds_Items_Buttons->Add(SoundItems_PasteInsert, 1, wxEXPAND);

	Sounds_Items_Searches[0]->Add(Sounds_Items_Search, 1, wxEXPAND);
	Sounds_Items_Searches[0]->Add(2, -1);
	Sounds_Items_Searches[0]->Add(Sounds_Items_UseAnd[0], 0, wxEXPAND);
	Sounds_Items_Searches[1]->Add(Sounds_Items_Search_R, 1, wxEXPAND);
	Sounds_Items_Searches[1]->Add(2, -1);
	Sounds_Items_Searches[1]->Add(Sounds_Items_UseAnd[1], 0, wxEXPAND);
	Sounds_Items->Add(Sounds_Items_Searches[0], 0, wxEXPAND);
	Sounds_Items->Add(Sounds_Items_Searches[1], 0, wxEXPAND);
	Sounds_Items->Add(Sounds_Items_SearchFilters[0], 0, wxEXPAND);
	Sounds_Items->Add(Sounds_Items_SearchFilters[1], 0, wxEXPAND);
	Sounds_Items->Add(-1, 2);
	Sounds_Items->Add(Sounds_Items_List, 1, wxEXPAND);
	Sounds_Items->Add(-1, 2);
	Sounds_Items->Add(Sounds_Items_Buttons, 0, wxEXPAND);

	SoundItems_ListArea->Add(-1, 10);
	SoundItems_ListArea->Add(Sounds_Items, 1, wxEXPAND);
	SoundItems_ListArea->Add(-1, 10);

	Sounds_Holder_ID->Add(Sounds_Text_ID, 0, wxEXPAND);
	Sounds_Holder_ID->Add(Sounds_ID, 1, wxEXPAND);
	Sounds_Holder_Unknown->Add(Sounds_Text_Unknown, 0, wxEXPAND);
	Sounds_Holder_Unknown->Add(Sounds_Unknown, 1, wxEXPAND);
	SoundItems_Holder_Name->Add(SoundItems_Text_Name, 0, wxEXPAND);
	SoundItems_Holder_Name->Add(SoundItems_Name, 1, wxEXPAND);
	SoundItems_Holder_Resource->Add(SoundItems_Text_Resource, 0, wxEXPAND);
	SoundItems_Holder_Resource->Add(SoundItems_Resource, 1, wxEXPAND);
	SoundItems_Holder_Probability->Add(SoundItems_Text_Probability, 0, wxEXPAND);
	SoundItems_Holder_Probability->Add(SoundItems_Probability, 1, wxEXPAND);
	SoundItems_Holder_Civ->Add(SoundItems_Text_Civ, 0, wxEXPAND);
	SoundItems_Holder_Civ->Add(SoundItems_Civ, 1, wxEXPAND);
	SoundItems_Holder_Civ->Add(SoundItems_ComboBox_Civ, 1, wxEXPAND);
	SoundItems_Holder_Unknown->Add(SoundItems_Text_Unknown, 0, wxEXPAND);
	SoundItems_Holder_Unknown->Add(SoundItems_Unknown, 1, wxEXPAND);

	Sounds_AllItems_Searches[0]->Add(Sounds_AllItems_Search, 1, wxEXPAND);
	Sounds_AllItems_Searches[0]->Add(2, -1);
	Sounds_AllItems_Searches[0]->Add(Sounds_AllItems_UseAnd[0], 0, wxEXPAND);
	Sounds_AllItems_Searches[1]->Add(Sounds_AllItems_Search_R, 1, wxEXPAND);
	Sounds_AllItems_Searches[1]->Add(2, -1);
	Sounds_AllItems_Searches[1]->Add(Sounds_AllItems_UseAnd[1], 0, wxEXPAND);
	Sounds_AllItems->Add(Sounds_AllItems_Searches[0], 0, wxEXPAND);
	Sounds_AllItems->Add(Sounds_AllItems_Searches[1], 0, wxEXPAND);
	Sounds_AllItems->Add(-1, 2);
	Sounds_AllItems->Add(Sounds_AllItems_List, 1, wxEXPAND);
	Sounds_AllItems->Add(-1, 2);
	Sounds_AllItems->Add(Sounds_AllItems_Load, 0, wxEXPAND);

	Sounds_DataArea->Add(-1, 10);
	Sounds_DataArea->Add(Sounds_Holder_ID, 0, wxEXPAND);
	Sounds_DataArea->Add(-1, 5);
	Sounds_DataArea->Add(Sounds_Holder_Unknown, 0, wxEXPAND);
	Sounds_DataArea->Add(-1, 5);
	Sounds_DataArea->Add(SoundItems_Holder_Name, 0, wxEXPAND);
	Sounds_DataArea->Add(-1, 5);
	Sounds_DataArea->Add(SoundItems_Holder_Resource, 0, wxEXPAND);
	Sounds_DataArea->Add(-1, 5);
	Sounds_DataArea->Add(SoundItems_Holder_Probability, 0, wxEXPAND);
	Sounds_DataArea->Add(-1, 5);
	Sounds_DataArea->Add(SoundItems_Holder_Civ, 0, wxEXPAND);
	Sounds_DataArea->Add(-1, 5);
	Sounds_DataArea->Add(SoundItems_Holder_Unknown, 0, wxEXPAND);
	Sounds_DataArea->Add(-1, 5);
	Sounds_DataArea->Add(Sounds_AllItems, 1, wxEXPAND);
	Sounds_DataArea->Add(-1, 10);

	Sounds_Main->Add(10, -1);
	Sounds_Main->Add(Sounds_ListArea, 1, wxEXPAND);
	Sounds_Main->Add(10, -1);
	Sounds_Main->Add(SoundItems_ListArea, 1, wxEXPAND);
	Sounds_Main->Add(10, -1);
	Sounds_Main->Add(Sounds_DataArea, 1, wxEXPAND);
	Sounds_Main->AddStretchSpacer(1);

	if(EnableIDFix)
	Sounds_ID->Enable(false);

	Tab_Sounds->SetSizer(Sounds_Main);

	for(short loop = 0;loop < 2;loop++)
	{
		Connect(Sounds_Items_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsSearch));
		Connect(Sounds_Items_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_ComboBoxes));
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
	Connect(Sounds_AllItems_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::LoadAllSoundFiles));
	Connect(Sounds_AllItems_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::LoadAllSoundFiles));
	Connect(Sounds_AllItems_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnAllSoundFileSelect));
	Connect(Sounds_AllItems_Load->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::LoadAllSoundFiles));

	SoundItems_Name->Connect(SoundItems_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);

}
