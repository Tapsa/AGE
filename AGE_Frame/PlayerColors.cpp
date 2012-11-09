
#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetPlayerColorName(short &Index)
{
	if(GameVersion <= 1)
		return GenieFile->PlayerColours[Index].Name;
	return "Color "+lexical_cast<string>(Index)+" ";
}

void AGE_Frame::ListPlayerColors()
{
	wxString Name, CompareText;
	SearchText = PlayerColors->Search->GetValue().Lower();
	ExcludeText = PlayerColors->Search_R->GetValue().Lower();

	auto Selections = PlayerColors->List->GetSelections(Items);
	if(PlayerColors->List->GetCount() > 0) PlayerColors->List->Clear();

	for(short loop=0; loop < GenieFile->PlayerColours.size(); loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetPlayerColorName(loop);
		CompareText = Name.Lower();
		if(SearchMatches(CompareText))
		{
			PlayerColors->List->Append(Name, (void*)&GenieFile->PlayerColours[loop]);
		}
	}

	ListingFix(Selections, PlayerColors->List);

	wxCommandEvent E;
	OnPlayerColorsSelect(E);
}

void AGE_Frame::OnPlayerColorsSearch(wxCommandEvent& Event)
{
	ListPlayerColors();
}

void AGE_Frame::OnPlayerColorsSelect(wxCommandEvent& Event)
{
	auto Selections = PlayerColors->List->GetSelections(Items);
	if(Selections != 0)
	{
		ColorIDs.resize(Selections);
		genie::PlayerColour * PlayerColor;
		for(short loop = Selections; loop--> 0;)
		{
			PlayerColor = (genie::PlayerColour*)PlayerColors->List->GetClientData(Items.Item(loop));
			ColorIDs[loop] = (PlayerColor - (&GenieFile->PlayerColours[0]));
		}
		PlayerColors->ID->ChangeValue(lexical_cast<string>(PlayerColor->ID));
		PlayerColors->ID->Container = &PlayerColor->ID;
		PlayerColors->ColorL->ChangeValue(lexical_cast<string>(PlayerColor->Colour));
		PlayerColors->ColorL->Container = &PlayerColor->Colour;
		if(GameVersion < 2)	//	AoE and RoR
		{
			PlayerColors->ColorL->SetBackgroundColour(wxColour(210, 230, 255));
			PlayerColors->Name->ChangeValue(PlayerColor->Name);
			PlayerColors->Name->Container = &PlayerColor->Name;
		}
		else	//	Above AoE and RoR
		{
			PlayerColors->ColorL->SetBackgroundColour(wxColour(215, 255, 255));
			PlayerColors->Palette->ChangeValue(lexical_cast<string>(PlayerColor->Palette));
			PlayerColors->Palette->Container = &PlayerColor->Palette;
			PlayerColors->MinimapColor->ChangeValue(lexical_cast<string>(PlayerColor->MinimapColour));
			PlayerColors->MinimapColor->Container = &PlayerColor->MinimapColour;
			PlayerColors->Unknown1->ChangeValue(lexical_cast<string>(PlayerColor->Unknown1));
			PlayerColors->Unknown1->Container = &PlayerColor->Unknown1;
			PlayerColors->Unknown2->ChangeValue(lexical_cast<string>(PlayerColor->Unknown2));
			PlayerColors->Unknown2->Container = &PlayerColor->Unknown2;
			PlayerColors->Unknown3->ChangeValue(lexical_cast<string>(PlayerColor->Unknown3));
			PlayerColors->Unknown3->Container = &PlayerColor->Unknown3;
			PlayerColors->Unknown4->ChangeValue(lexical_cast<string>(PlayerColor->Unknown4));
			PlayerColors->Unknown4->Container = &PlayerColor->Unknown4;
			PlayerColors->Unknown5->ChangeValue(lexical_cast<string>(PlayerColor->Unknown5));
			PlayerColors->Unknown5->Container = &PlayerColor->Unknown5;
		}
	}
}

void AGE_Frame::OnPlayerColorsAdd(wxCommandEvent& Event)
{
	if(GenieFile != NULL)
	{
		wxBusyCursor WaitCursor;
		genie::PlayerColour Temp;
		GenieFile->PlayerColours.push_back(Temp);
		Added = true;
		ListPlayerColors();
	}
}

void AGE_Frame::OnPlayerColorsInsert(wxCommandEvent& Event)
{
	auto Selections = PlayerColors->List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::PlayerColour Temp;
		GenieFile->PlayerColours.insert(GenieFile->PlayerColours.begin() + ColorIDs[0], Temp);
		ListPlayerColors();
	}
}

void AGE_Frame::OnPlayerColorsDelete(wxCommandEvent& Event)
{
	auto Selections = PlayerColors->List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop = Selections; loop--> 0;)
		GenieFile->PlayerColours.erase(GenieFile->PlayerColours.begin() + ColorIDs[loop]);
		ListPlayerColors();
	}
}

void AGE_Frame::OnPlayerColorsCopy(wxCommandEvent& Event)
{
	auto Selections = PlayerColors->List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		PlayerColorCopies.resize(Selections);
		for(short loop=0; loop < Selections; loop++)
		PlayerColorCopies[loop] = GenieFile->PlayerColours[ColorIDs[loop]];
	}
}

void AGE_Frame::OnPlayerColorsPaste(wxCommandEvent& Event)
{
	auto Selections = PlayerColors->List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		if(PlayerColorCopies.size()+ColorIDs[0] > GenieFile->PlayerColours.size())
		GenieFile->PlayerColours.resize(PlayerColorCopies.size()+ColorIDs[0]);
		for(short loop=0; loop < PlayerColorCopies.size(); loop++)
		GenieFile->PlayerColours[ColorIDs[0]+loop] = PlayerColorCopies[loop];
		ListPlayerColors();
	}
}

void AGE_Frame::OnPlayerColorsPasteInsert(wxCommandEvent& Event)
{
	auto Selections = PlayerColors->List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::PlayerColour Temp;
		GenieFile->PlayerColours.insert(GenieFile->PlayerColours.begin() + ColorIDs[0], PlayerColorCopies.size(), Temp);
		for(short loop=0; loop < PlayerColorCopies.size(); loop++)
		GenieFile->PlayerColours[ColorIDs[0]+loop] = PlayerColorCopies[loop];
		ListPlayerColors();
	}
}

void AGE_Frame::ConnectPlayerColors()
{
	Connect(PlayerColors->Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsSearch));
	Connect(PlayerColors->Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsSearch));
	Connect(PlayerColors->List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsSelect));
	Connect(PlayerColors->Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsAdd));
	Connect(PlayerColors->Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsInsert));
	Connect(PlayerColors->Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsDelete));
	Connect(PlayerColors->Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsCopy));
	Connect(PlayerColors->Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsPaste));
	Connect(PlayerColors->PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsPasteInsert));
	PlayerColors->Name->Connect(PlayerColors->Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
}
