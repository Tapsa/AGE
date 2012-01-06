/* AGEFrame_cpp/Sounds.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetSoundName(short Index)
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
	string Name;
	SearchText = wxString(Sounds_Sounds_Search->GetValue()).Lower();
	ExcludeText = wxString(Sounds_Sounds_Search_R->GetValue()).Lower();
	string CompareText;
	
	short Selection = Sounds_Sounds_List->GetSelection();
	if(Sounds_Sounds_List->GetCount() > 0)
	{
		Sounds_Sounds_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	
	short IDsCount = 13, SoundIDs[IDsCount];
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
		
		for(short loop = 0;loop < IDsCount;loop++)
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
		Name = lexical_cast<string>(loop)+" - "+GetSoundName(loop);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
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
	
	Sounds_Sounds_List->SetSelection(0);
	Sounds_Sounds_List->SetFirstItem(Selection - 3);
	Sounds_Sounds_List->SetSelection(Selection);
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
	short Selection = Sounds_Sounds_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Sounds_Sounds_List->GetCount() - 1;
			Sounds_Sounds_List->SetSelection(Selection);
		}
		gdat::Sound * SoundPointer = (gdat::Sound*)Sounds_Sounds_List->GetClientData(Selection);
		SoundID = SoundPointer - (&GenieFile->Sounds[0]);
		Sounds_ID->ChangeValue(lexical_cast<string>(SoundPointer->ID));
		Sounds_ID->Container = &SoundPointer->ID;
		Sounds_Unknown->ChangeValue(lexical_cast<string>(SoundPointer->Unknown1));
		Sounds_Unknown->Container = &SoundPointer->Unknown1;
		Added = false;
		ListSoundItems(SoundID);
	}
}

void AGE_Frame::OnSoundsAdd(wxCommandEvent& Event)
{
	gdat::Sound Temp;
	GenieFile->Sounds.push_back(Temp);
	GenieFile->Sounds[GenieFile->Sounds.size() - 1].ID = lexical_cast<long>(GenieFile->Sounds.size() - 1);	//	ID Fix
	Added = true;
	ListSounds();
}

void AGE_Frame::OnSoundsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Sounds_Sounds_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->Sounds.erase(GenieFile->Sounds.begin() + SoundID);
		for(short loop = SoundID;loop < GenieFile->Sounds.size();loop++)	//	ID Fix
		{
			GenieFile->Sounds[loop].ID = lexical_cast<long>(loop);
		}
		if(Selection == Sounds_Sounds_List->GetCount() - 1)
		Sounds_Sounds_List->SetSelection(Selection - 1);
		ListSounds();
	}
}

void AGE_Frame::OnSoundsCopy(wxCommandEvent& Event)
{
	short Selection = Sounds_Sounds_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		SoundCopy = *(gdat::Sound*)Sounds_Sounds_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnSoundsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Sounds_Sounds_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::Sound*)Sounds_Sounds_List->GetClientData(Selection) = SoundCopy;
		GenieFile->Sounds[SoundID].ID = lexical_cast<long>(SoundID);	//	ID Fix
		ListSounds();
	}
}

string AGE_Frame::GetSoundItemName(short Index, short SoundID)
{
	string Name = "";
	if(GenieFile->Sounds[SoundID].Items[Index].FileName != "")
	{
		Name = GenieFile->Sounds[SoundID].Items[Index].FileName;
	}
	else
	{
		Name = "NewFile.wav";
	}
	return Name;
}

void AGE_Frame::OnSoundItemsSearch(wxCommandEvent& Event)
{
	ListSoundItems(SoundID);
}

void AGE_Frame::ListSoundItems(short Index)
{
	string Name;
	SearchText = wxString(Sounds_SoundItems_Search->GetValue()).Lower();
	ExcludeText = wxString(Sounds_SoundItems_Search_R->GetValue()).Lower();
	string CompareText;
	short Selection = Sounds_SoundItems_List->GetSelection();

	if(Sounds_SoundItems_List->GetCount() > 0)
	{
		Sounds_SoundItems_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->Sounds[Index].Items.size();loop++)
	{
		Name = lexical_cast<string>(loop)+" - "+GetSoundItemName(loop, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Sounds_SoundItems_List->Append(Name, (void*)&GenieFile->Sounds[Index].Items[loop]);
		}
	}
	Sounds_SoundItems_List->SetSelection(0);
	Sounds_SoundItems_List->SetFirstItem(Selection - 3);
	Sounds_SoundItems_List->SetSelection(Selection);

	wxCommandEvent E;
	OnSoundItemsSelect(E);
}

void AGE_Frame::OnSoundItemsSelect(wxCommandEvent& Event)
{
	short Selection = Sounds_SoundItems_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Sounds_SoundItems_List->GetCount() - 1;
			Sounds_SoundItems_List->SetSelection(Selection);
		}
		gdat::SoundItem * SoundItemPointer = (gdat::SoundItem*)Sounds_SoundItems_List->GetClientData(Selection);
		SoundItemID = SoundItemPointer - (&GenieFile->Sounds[SoundID].Items[0]);
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
		Added = false;
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
	short Selection = Sounds_Sounds_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		gdat::SoundItem Temp;
		GenieFile->Sounds[SoundID].Items.push_back(Temp);
		Added = true;
		ListSoundItems(SoundID);
	}
}

void AGE_Frame::OnSoundItemsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Sounds_SoundItems_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->Sounds[SoundID].Items.erase(GenieFile->Sounds[SoundID].Items.begin() + SoundItemID);
		if(Selection == Sounds_SoundItems_List->GetCount() - 1)
		Sounds_SoundItems_List->SetSelection(Selection - 1);
		ListSoundItems(SoundID);
	}
}

void AGE_Frame::OnSoundItemsCopy(wxCommandEvent& Event)
{
	short Selection = Sounds_SoundItems_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		SoundItemCopy = *(gdat::SoundItem*)Sounds_SoundItems_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnSoundItemsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Sounds_SoundItems_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::SoundItem*)Sounds_SoundItems_List->GetClientData(Selection) = SoundItemCopy;
		ListSoundItems(SoundID);
	}
}

void AGE_Frame::CreateSoundControls()
{
	Sounds_Main = new wxBoxSizer(wxHORIZONTAL);
	Sounds_ListArea = new wxBoxSizer(wxVERTICAL);
	Sounds_Sounds_Buttons = new wxGridSizer(2, 0, 0);
	SoundItems_ListArea = new wxBoxSizer(wxVERTICAL);
	Sounds_SoundItems_Buttons = new wxGridSizer(2, 0, 0);
	Sounds_DataArea = new wxBoxSizer(wxVERTICAL);
	
	Tab_Sounds = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	Sounds_Sounds = new wxStaticBoxSizer(wxVERTICAL, Tab_Sounds, "Sounds");
	Sounds_Sounds_Search = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_Sounds_Search_R = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_Sounds_List = new wxListBox(Tab_Sounds, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	Sounds_Add = new wxButton(Tab_Sounds, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Sounds_Delete = new wxButton(Tab_Sounds, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Sounds_Copy = new wxButton(Tab_Sounds, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Sounds_Paste = new wxButton(Tab_Sounds, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));

	Sounds_Holder_ID = new wxBoxSizer(wxVERTICAL);
	Sounds_Text_ID = new wxStaticText(Tab_Sounds, wxID_ANY, " Sound ID", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Sounds_ID = new TextCtrl_Long(Tab_Sounds, "0", NULL);
	Sounds_Holder_Unknown = new wxBoxSizer(wxVERTICAL);
	Sounds_Text_Unknown = new wxStaticText(Tab_Sounds, wxID_ANY, " Sound Unknown", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Sounds_Unknown = new TextCtrl_Long(Tab_Sounds, "0", NULL);

	Sounds_SoundItems = new wxStaticBoxSizer(wxVERTICAL, Tab_Sounds, "Sound Items");
	Sounds_SoundItems_Search = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_SoundItems_Search_R = new wxTextCtrl(Tab_Sounds, wxID_ANY);
	Sounds_SoundItems_List = new wxListBox(Tab_Sounds, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	SoundItems_Add = new wxButton(Tab_Sounds, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	SoundItems_Delete = new wxButton(Tab_Sounds, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	SoundItems_Copy = new wxButton(Tab_Sounds, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	SoundItems_Paste = new wxButton(Tab_Sounds, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));

	SoundItems_Holder_Name = new wxBoxSizer(wxVERTICAL);
	SoundItems_Text_Name = new wxStaticText(Tab_Sounds, wxID_ANY, " Item Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Name = new TextCtrl_String(Tab_Sounds, "0", NULL);
	SoundItems_Holder_Resource = new wxBoxSizer(wxVERTICAL);
	SoundItems_Text_Resource = new wxStaticText(Tab_Sounds, wxID_ANY, " Item Drs Resource", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Resource = new TextCtrl_Long(Tab_Sounds, "0", NULL);
	SoundItems_Holder_Probability = new wxBoxSizer(wxVERTICAL);
	SoundItems_Text_Probability = new wxStaticText(Tab_Sounds, wxID_ANY, " Item Probability", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Probability = new TextCtrl_Short(Tab_Sounds, "0", NULL);
	SoundItems_Holder_Civ = new wxBoxSizer(wxVERTICAL);
	SoundItems_Text_Civ = new wxStaticText(Tab_Sounds, wxID_ANY, " Item Civilization", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Civ = new TextCtrl_Short(Tab_Sounds, "0", NULL);
	SoundItems_ComboBox_Civ = new ComboBox_Short(Tab_Sounds, SoundItems_Civ);
	SoundItems_Holder_Unknown = new wxBoxSizer(wxVERTICAL);
	SoundItems_Text_Unknown = new wxStaticText(Tab_Sounds, wxID_ANY, " Item Unknown", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	SoundItems_Unknown = new TextCtrl_Short(Tab_Sounds, "0", NULL);

	Sounds_Sounds_Buttons->Add(Sounds_Add, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_Delete, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_Copy, 1, wxEXPAND);
	Sounds_Sounds_Buttons->Add(Sounds_Paste, 1, wxEXPAND);

	Sounds_Sounds->Add(Sounds_Sounds_Search, 0, wxEXPAND);
	Sounds_Sounds->Add(Sounds_Sounds_Search_R, 0, wxEXPAND);
	Sounds_Sounds->Add(-1, 2);
	Sounds_Sounds->Add(Sounds_Sounds_List, 1, wxEXPAND);
	Sounds_Sounds->Add(-1, 2);
	Sounds_Sounds->Add(Sounds_Sounds_Buttons, 0, wxEXPAND);

	Sounds_ListArea->Add(-1, 10);
	Sounds_ListArea->Add(Sounds_Sounds, 1, wxEXPAND);
	Sounds_ListArea->Add(-1, 10);

	Sounds_SoundItems_Buttons->Add(SoundItems_Add, 1, wxEXPAND);
	Sounds_SoundItems_Buttons->Add(SoundItems_Delete, 1, wxEXPAND);
	Sounds_SoundItems_Buttons->Add(SoundItems_Copy, 1, wxEXPAND);
	Sounds_SoundItems_Buttons->Add(SoundItems_Paste, 1, wxEXPAND);

	Sounds_SoundItems->Add(Sounds_SoundItems_Search, 0, wxEXPAND);
	Sounds_SoundItems->Add(Sounds_SoundItems_Search_R, 0, wxEXPAND);
	Sounds_SoundItems->Add(-1, 2);
	Sounds_SoundItems->Add(Sounds_SoundItems_List, 1, wxEXPAND);
	Sounds_SoundItems->Add(-1, 2);
	Sounds_SoundItems->Add(Sounds_SoundItems_Buttons, 0, wxEXPAND);

	SoundItems_ListArea->Add(-1, 10);
	SoundItems_ListArea->Add(Sounds_SoundItems, 1, wxEXPAND);
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

	Sounds_Main->Add(10, -1);
	Sounds_Main->Add(Sounds_ListArea, 1, wxEXPAND);
	Sounds_Main->Add(10, -1);
	Sounds_Main->Add(SoundItems_ListArea, 1, wxEXPAND);
	Sounds_Main->Add(10, -1);
	Sounds_Main->Add(Sounds_DataArea, 1, wxEXPAND);
	Sounds_Main->AddStretchSpacer(1);
	
	Sounds_ID->Enable(false);

	Tab_Sounds->SetSizer(Sounds_Main);
	
	Connect(Sounds_Sounds_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSoundsSelect));
	Connect(Sounds_Sounds_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnSoundsSearch));
	Connect(Sounds_Sounds_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnSoundsSearch));
	Connect(Sounds_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundsAdd));
	Connect(Sounds_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundsDelete));
	Connect(Sounds_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundsCopy));
	Connect(Sounds_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundsPaste));
	Connect(Sounds_SoundItems_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSoundItemsSelect));
	Connect(Sounds_SoundItems_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnSoundItemsSearch));
	Connect(Sounds_SoundItems_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnSoundItemsSearch));
	Connect(SoundItems_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsAdd));
	Connect(SoundItems_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsDelete));
	Connect(SoundItems_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsCopy));
	Connect(SoundItems_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnSoundItemsPaste));

	SoundItems_Name->Connect(SoundItems_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);

}
