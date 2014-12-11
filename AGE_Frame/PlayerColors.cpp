#include "../AGE_Frame.h"

void AGE_Frame::OnPlayerColorsSearch(wxCommandEvent &Event)
{
	ListPlayerColors();
}

string AGE_Frame::GetPlayerColorName(short Index)
{
	if(GenieVersion <= genie::GV_RoR)
		return GenieFile->PlayerColours[Index].Name;
	return "Color "+lexical_cast<string>(Index)+" ";
}

void AGE_Frame::ListPlayerColors()
{
	InitPlayerColors();
	wxCommandEvent E;
	OnPlayerColorsSelect(E);
}

void AGE_Frame::InitPlayerColors()
{
	searchText = Colors_Colors_Search->GetValue().Lower();
	excludeText = Colors_Colors_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString names, filteredNames;
	names.Alloc(GenieFile->PlayerColours.size());

	for(short loop = 0; loop < GenieFile->PlayerColours.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetPlayerColorName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->PlayerColours[loop]);
		}
		names.Add(Name);
	}

	Listing(Colors_Colors_List, filteredNames, dataPointers);

	short selection = Graphics_PlayerColor_ComboBox->GetSelection();
	Graphics_PlayerColor_ComboBox->Clear();
	Graphics_PlayerColor_ComboBox->Append("-1 - None");
	Graphics_PlayerColor_ComboBox->Append(names);
	Graphics_PlayerColor_ComboBox->SetSelection(selection);
}

void AGE_Frame::OnPlayerColorsSelect(wxCommandEvent &Event)
{
	auto selections = Colors_Colors_List->GetSelections(Items);
	if(selections < 1) return;

	ColorIDs.resize(selections);
	Colors_ID->resize(selections);
	Colors_ColorL->resize(selections);
	if(GenieVersion <= genie::GV_RoR)	//	AoE and RoR
	{
		Colors_Name->resize(selections);
	}
	else	//	Above AoE and RoR
	{
		Colors_Palette->resize(selections);
		Colors_MinimapColor->resize(selections);
		Colors_Unknown1->resize(selections);
		Colors_Unknown2->resize(selections);
		Colors_Unknown3->resize(selections);
		Colors_Unknown4->resize(selections);
		Colors_Unknown5->resize(selections);
	}

	genie::PlayerColour * PlayerColorPointer;
	for(auto loop = selections; loop--> 0;)
	{
		PlayerColorPointer = (genie::PlayerColour*)Colors_Colors_List->GetClientData(Items.Item(loop));
		ColorIDs[loop] = (PlayerColorPointer - (&GenieFile->PlayerColours[0]));

		Colors_ID->container[loop] = &PlayerColorPointer->ID;
		Colors_ColorL->container[loop] = &PlayerColorPointer->Colour;
		if(GenieVersion <= genie::GV_RoR)	//	AoE and RoR
		{
			Colors_Name->container[loop] = &PlayerColorPointer->Name;
		}
		else	//	Above AoE and RoR
		{
			Colors_Palette->container[loop] = &PlayerColorPointer->Palette;
			Colors_MinimapColor->container[loop] = &PlayerColorPointer->MinimapColour;
			Colors_Unknown1->container[loop] = &PlayerColorPointer->Unknown1;
			Colors_Unknown2->container[loop] = &PlayerColorPointer->Unknown2;
			Colors_Unknown3->container[loop] = &PlayerColorPointer->Unknown3;
			Colors_Unknown4->container[loop] = &PlayerColorPointer->Unknown4;
			Colors_Unknown5->container[loop] = &PlayerColorPointer->StatisticsText;
		}
	}

	Colors_ID->ChangeValue(lexical_cast<string>(PlayerColorPointer->ID));
	Colors_ColorL->ChangeValue(lexical_cast<string>(PlayerColorPointer->Colour));
	if(GenieVersion <= genie::GV_RoR)	//	AoE and RoR
	{
		Colors_Name->ChangeValue(PlayerColorPointer->Name);
	}
	else	//	Above AoE and RoR
	{
		Colors_Palette->ChangeValue(lexical_cast<string>(PlayerColorPointer->Palette));
		Colors_MinimapColor->ChangeValue(lexical_cast<string>(PlayerColorPointer->MinimapColour));
		Colors_Unknown1->ChangeValue(lexical_cast<string>(PlayerColorPointer->Unknown1));
		Colors_Unknown2->ChangeValue(lexical_cast<string>(PlayerColorPointer->Unknown2));
		Colors_Unknown3->ChangeValue(lexical_cast<string>(PlayerColorPointer->Unknown3));
		Colors_Unknown4->ChangeValue(lexical_cast<string>(PlayerColorPointer->Unknown4));
		Colors_Unknown5->ChangeValue(lexical_cast<string>(PlayerColorPointer->StatisticsText));
	}
}

void AGE_Frame::OnPlayerColorsAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToListIDFix(GenieFile->PlayerColours);
	ListPlayerColors();
}

void AGE_Frame::OnPlayerColorsInsert(wxCommandEvent &Event)
{
	auto selections = Colors_Colors_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListIDFix(GenieFile->PlayerColours, ColorIDs[0]);
	ListPlayerColors();
}

void AGE_Frame::OnPlayerColorsDelete(wxCommandEvent &Event)
{
	auto selections = Colors_Colors_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromListIDFix(GenieFile->PlayerColours, ColorIDs);
	ListPlayerColors();
}

void AGE_Frame::OnPlayerColorsCopy(wxCommandEvent &Event)
{
	auto selections = Colors_Colors_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->PlayerColours, ColorIDs, copies->PlayerColor);
}

void AGE_Frame::OnPlayerColorsPaste(wxCommandEvent &Event)
{
	auto selections = Colors_Colors_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListIDFix(GenieFile->PlayerColours, ColorIDs[0], copies->PlayerColor);
	ListPlayerColors();
}

void AGE_Frame::OnPlayerColorsPasteInsert(wxCommandEvent &Event)
{
	auto selections = Colors_Colors_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListIDFix(GenieFile->PlayerColours, ColorIDs[0], copies->PlayerColor);
	ListPlayerColors();
}

void AGE_Frame::CreatePlayerColorControls()
{
	Colors_Main = new wxBoxSizer(wxHORIZONTAL);
	Colors_ListArea = new wxBoxSizer(wxVERTICAL);
	Tab_PlayerColors = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Colors_Colors = new wxStaticBoxSizer(wxVERTICAL, Tab_PlayerColors, "Player Colors");
	Colors_Colors_Search = new wxTextCtrl(Tab_PlayerColors, wxID_ANY);
	Colors_Colors_Search_R = new wxTextCtrl(Tab_PlayerColors, wxID_ANY);
	Colors_Colors_List = new wxListBox(Tab_PlayerColors, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	Colors_Colors_Buttons = new wxGridSizer(3, 0, 0);
	Colors_Add = new wxButton(Tab_PlayerColors, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Colors_Insert = new wxButton(Tab_PlayerColors, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Colors_Delete = new wxButton(Tab_PlayerColors, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Colors_Copy = new wxButton(Tab_PlayerColors, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Colors_Paste = new wxButton(Tab_PlayerColors, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Colors_PasteInsert = new wxButton(Tab_PlayerColors, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	Colors_DataArea = new wxBoxSizer(wxVERTICAL);
	Colors_Name_Holder = new wxBoxSizer(wxVERTICAL);
	Colors_ID_Holder = new wxBoxSizer(wxVERTICAL);
	Colors_Palette_Holder = new wxBoxSizer(wxVERTICAL);
	Colors_Color_Holder = new wxBoxSizer(wxVERTICAL);
	Colors_MinimapColor_Holder = new wxBoxSizer(wxVERTICAL);
	Colors_UnknownArea_Holder = new wxBoxSizer(wxVERTICAL);
	Colors_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	Colors_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	Colors_Unknown3_Holder = new wxBoxSizer(wxVERTICAL);
	Colors_Unknown4_Holder = new wxBoxSizer(wxVERTICAL);
	Colors_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
	Colors_Name_Text = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_ID_Text = new wxStaticText(Tab_PlayerColors, wxID_ANY, " ID", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Palette_Text = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Palette *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Color_Text = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Color *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_MinimapColor_Text = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Minimap Color *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Unknown1_Text = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Unknown2_Text = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Unknown3_Text = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Unknown4_Text = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Unknown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Unknown5_Text = new wxStaticText(Tab_PlayerColors, wxID_ANY, " Statistics Text", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Colors_Name = new TextCtrl_String(Tab_PlayerColors, 30);
	Colors_ID = new TextCtrl_Long(Tab_PlayerColors);
	Colors_Palette = new TextCtrl_Long(Tab_PlayerColors);
	Colors_Palette->SetToolTip("Starting index of the main color palette\nfrom where 8 colors are dedicated to this player color");
	Colors_ColorL = new TextCtrl_Long(Tab_PlayerColors);
	Colors_ColorL->SetToolTip("Index of the main color palette");
	Colors_MinimapColor = new TextCtrl_Long(Tab_PlayerColors);
	Colors_MinimapColor->SetToolTip("Index of the main color palette");
	Colors_Unknown1 = new TextCtrl_Long(Tab_PlayerColors);
	Colors_Unknown2 = new TextCtrl_Long(Tab_PlayerColors);
	Colors_Unknown3 = new TextCtrl_Long(Tab_PlayerColors);
	Colors_Unknown4 = new TextCtrl_Long(Tab_PlayerColors);
	Colors_Unknown5 = new TextCtrl_Long(Tab_PlayerColors);

	Colors_Colors_Buttons->Add(Colors_Add, 1, wxEXPAND);
	Colors_Colors_Buttons->Add(Colors_Delete, 1, wxEXPAND);
	Colors_Colors_Buttons->Add(Colors_Insert, 1, wxEXPAND);
	Colors_Colors_Buttons->Add(Colors_Copy, 1, wxEXPAND);
	Colors_Colors_Buttons->Add(Colors_Paste, 1, wxEXPAND);
	Colors_Colors_Buttons->Add(Colors_PasteInsert, 1, wxEXPAND);

	Colors_Colors->Add(Colors_Colors_Search, 0, wxEXPAND);
	Colors_Colors->Add(Colors_Colors_Search_R, 0, wxEXPAND);
	Colors_Colors->Add(-1, 2);
	Colors_Colors->Add(Colors_Colors_List, 1, wxEXPAND);
	Colors_Colors->Add(-1, 2);
	Colors_Colors->Add(Colors_Colors_Buttons, 0, wxEXPAND);

	Colors_ListArea->Add(-1, 10);
	Colors_ListArea->Add(Colors_Colors, 1, wxEXPAND);
	Colors_ListArea->Add(-1, 10);

	Colors_Name_Holder->Add(Colors_Name_Text, 0, wxEXPAND);
	Colors_Name_Holder->Add(Colors_Name, 1, wxEXPAND);
	Colors_ID_Holder->Add(Colors_ID_Text, 0, wxEXPAND);
	Colors_ID_Holder->Add(Colors_ID, 1, wxEXPAND);
	Colors_Palette_Holder->Add(Colors_Palette_Text, 0, wxEXPAND);
	Colors_Palette_Holder->Add(Colors_Palette, 1, wxEXPAND);
	Colors_Color_Holder->Add(Colors_Color_Text, 0, wxEXPAND);
	Colors_Color_Holder->Add(Colors_ColorL, 1, wxEXPAND);
	Colors_MinimapColor_Holder->Add(Colors_MinimapColor_Text, 0, wxEXPAND);
	Colors_MinimapColor_Holder->Add(Colors_MinimapColor, 1, wxEXPAND);
	Colors_Unknown1_Holder->Add(Colors_Unknown1_Text, 0, wxEXPAND);
	Colors_Unknown1_Holder->Add(Colors_Unknown1, 1, wxEXPAND);
	Colors_Unknown2_Holder->Add(Colors_Unknown2_Text, 0, wxEXPAND);
	Colors_Unknown2_Holder->Add(Colors_Unknown2, 1, wxEXPAND);
	Colors_Unknown3_Holder->Add(Colors_Unknown3_Text, 0, wxEXPAND);
	Colors_Unknown3_Holder->Add(Colors_Unknown3, 1, wxEXPAND);
	Colors_Unknown4_Holder->Add(Colors_Unknown4_Text, 0, wxEXPAND);
	Colors_Unknown4_Holder->Add(Colors_Unknown4, 1, wxEXPAND);
	Colors_Unknown5_Holder->Add(Colors_Unknown5_Text, 0, wxEXPAND);
	Colors_Unknown5_Holder->Add(Colors_Unknown5, 1, wxEXPAND);

	Colors_UnknownArea_Holder->Add(Colors_Unknown1_Holder, 0, wxEXPAND);
	Colors_UnknownArea_Holder->Add(-1, 5);
	Colors_UnknownArea_Holder->Add(Colors_Unknown2_Holder, 0, wxEXPAND);
	Colors_UnknownArea_Holder->Add(-1, 5);
	Colors_UnknownArea_Holder->Add(Colors_Unknown3_Holder, 0, wxEXPAND);
	Colors_UnknownArea_Holder->Add(-1, 5);
	Colors_UnknownArea_Holder->Add(Colors_Unknown4_Holder, 0, wxEXPAND);
	Colors_UnknownArea_Holder->Add(-1, 5);
	Colors_UnknownArea_Holder->Add(Colors_Unknown5_Holder, 0, wxEXPAND);

	Colors_DataArea->Add(-1, 10);
	Colors_DataArea->Add(Colors_Name_Holder, 0, wxEXPAND);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_ID_Holder, 0, wxEXPAND);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_Palette_Holder, 0, wxEXPAND);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_Color_Holder, 0, wxEXPAND);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_MinimapColor_Holder, 0, wxEXPAND);
	Colors_DataArea->Add(-1, 5);
	Colors_DataArea->Add(Colors_UnknownArea_Holder, 0, wxEXPAND);

	Colors_Main->Add(10, -1);
	Colors_Main->Add(Colors_ListArea, 1, wxEXPAND);
	Colors_Main->Add(10, -1);
//	Colors_Main->Add(-1, -1, 3, wxEXPAND);
	Colors_Main->Add(Colors_DataArea, 1, wxEXPAND);
	Colors_Main->AddStretchSpacer(2);
	Colors_Main->Add(10, -1);

	if(EnableIDFix)
	Colors_ID->Enable(false);

	Tab_PlayerColors->SetSizer(Colors_Main);

	Connect(Colors_Colors_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsSearch));
	Connect(Colors_Colors_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsSearch));
	Connect(Colors_Colors_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsSelect));
	Connect(Colors_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsAdd));
	Connect(Colors_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsInsert));
	Connect(Colors_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsDelete));
	Connect(Colors_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsCopy));
	Connect(Colors_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsPaste));
	Connect(Colors_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnPlayerColorsPasteInsert));
	Colors_Name->Connect(Colors_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Colors), NULL, this);
}

void AGE_Frame::OnKillFocus_Colors(wxFocusEvent &Event)
{
	if(((AGETextCtrl*)Event.GetEventObject())->SaveEdits() != 0) return;
	ListPlayerColors();
	Event.Skip();
}
