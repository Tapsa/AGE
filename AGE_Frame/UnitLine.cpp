#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetUnitLineName(short Index)
{
	if(!GenieFile->UnitLines[Index].Name.empty())
		return GenieFile->UnitLines[Index].Name;
	return "Unitline "+lexical_cast<string>(Index);
}

void AGE_Frame::OnUnitLinesSearch(wxCommandEvent &Event)
{
	ListUnitLines();
}

void AGE_Frame::ListUnitLines()
{
	searchText = UnitLines_UnitLines_Search->GetValue().Lower();
	excludeText = UnitLines_UnitLines_Search_R->GetValue().Lower();

	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	short UnitIDs = Units_ComboBox_Unitline->GetSelection();

	UnitLines_UnitLines_List->Clear();
	Units_ComboBox_Unitline->Clear();

	if(UnitIDs == wxNOT_FOUND)
	{
		UnitIDs = 0;
	}

	Units_ComboBox_Unitline->Append("-1 - None");

	for(short loop = 0; loop < GenieFile->UnitLines.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineName(loop);
		if(SearchMatches(Name.Lower()))
		{
			UnitLines_UnitLines_List->Append(Name, (void*)&GenieFile->UnitLines[loop]);
		}
		Units_ComboBox_Unitline->Append(Name);
	}

	ListingFix(selections, UnitLines_UnitLines_List);
	Units_ComboBox_Unitline->SetSelection(UnitIDs);

	wxCommandEvent E;
	OnUnitLinesSelect(E);
}

void AGE_Frame::OnUnitLinesSelect(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	UnitLineIDs.resize(selections);
	UnitLines_ID->resize(selections);
	UnitLines_Name->resize(selections);

	genie::UnitLine * LinePointer;
	for(auto loop = selections; loop--> 0;)
	{
		LinePointer = (genie::UnitLine*)UnitLines_UnitLines_List->GetClientData(Items.Item(loop));
		UnitLineIDs[loop] = (LinePointer - (&GenieFile->UnitLines[0]));

		UnitLines_ID->container[loop] = &LinePointer->ID;
		UnitLines_Name->container[loop] = &LinePointer->Name;
	}

	UnitLines_ID->ChangeValue(lexical_cast<string>(LinePointer->ID));
	UnitLines_Name->ChangeValue(LinePointer->Name);
	ListUnitLineUnits();
}

void AGE_Frame::OnUnitLinesAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	AddToListIDFix(GenieFile->UnitLines);
	ListUnitLines();
}

void AGE_Frame::OnUnitLinesInsert(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListIDFix(GenieFile->UnitLines, UnitLineIDs[0]);
	ListUnitLines();
}

void AGE_Frame::OnUnitLinesDelete(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromListIDFix(GenieFile->UnitLines, UnitLineIDs);
	ListUnitLines();
}

void AGE_Frame::OnUnitLinesCopy(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->UnitLines, UnitLineIDs, copies->UnitLine);
}

void AGE_Frame::OnUnitLinesPaste(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListIDFix(GenieFile->UnitLines, UnitLineIDs[0], copies->UnitLine);
	ListUnitLines();
}

void AGE_Frame::OnUnitLinesPasteInsert(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListIDFix(GenieFile->UnitLines, UnitLineIDs[0], copies->UnitLine);
	ListUnitLines();
}

string AGE_Frame::GetUnitLineUnitName(short Unit)
{
	string Name = lexical_cast<string>(Unit)+" ";
	if(GenieFile->Civs[0].Units.size() <= Unit) return Name + "Nonexistent Unit";
	if(!LangDLLstring(GenieFile->Civs[0].Units[Unit].LanguageDLLName, 2).empty())
	{
		return Name + LangDLLstring(GenieFile->Civs[0].Units[Unit].LanguageDLLName, 64);
	}
	if(!GenieFile->Civs[0].Units[Unit].Name.empty())
	{
		return Name + GenieFile->Civs[0].Units[Unit].Name;
	}
	return Name + "New Unit";
}

void AGE_Frame::OnUnitLineUnitsSearch(wxCommandEvent &Event)
{
	ListUnitLineUnits();
}

void AGE_Frame::ListUnitLineUnits()
{
	searchText = UnitLines_UnitLineUnits_Search->GetValue().Lower();
	excludeText = UnitLines_UnitLineUnits_Search_R->GetValue().Lower();

	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	UnitLines_UnitLineUnits_List->Clear();

	for(short loop = 0; loop < GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitLineUnitName(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[loop]);
		if(SearchMatches(Name.Lower()))
		{
			UnitLines_UnitLineUnits_List->Append(Name, (void*)&GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[loop]);
		}
	}
	ListingFix(selections, UnitLines_UnitLineUnits_List);

	wxCommandEvent E;
	OnUnitLineUnitsSelect(E);
}

void AGE_Frame::OnUnitLineUnitsSelect(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(selections > 0)
	{
		UnitLineUnitIDs.resize(selections);
		UnitLineUnits_Units->resize(selections);

		int16_t * UnitPointer;
		for(auto loop = selections; loop--> 0;)
		{
			UnitPointer = (int16_t*)UnitLines_UnitLineUnits_List->GetClientData(Items.Item(loop));
			UnitLineUnitIDs[loop] = (UnitPointer - (&GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[0]));
			UnitLineUnits_Units->container[loop] = UnitPointer;
		}

		UnitLineUnits_Units->ChangeValue(lexical_cast<string>(*UnitPointer));
		UnitLineUnits_ComboBox_Units->SetSelection(*UnitPointer + 1);
	}
	else
	{
		UnitLineUnits_Units->ChangeValue("0");
		UnitLineUnits_ComboBox_Units->SetSelection(0);
	}
}

void AGE_Frame::OnUnitLineUnitsAdd(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs);
	ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsInsert(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs, UnitLineUnitIDs[0]);
	ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsDelete(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs, UnitLineUnitIDs);
	ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsCopy(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs, UnitLineUnitIDs, copies->UnitLineUnit);
}

void AGE_Frame::OnUnitLineUnitsPaste(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs, UnitLineUnitIDs[0], copies->UnitLineUnit);
	ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsPasteInsert(wxCommandEvent &Event)
{
	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs, UnitLineUnitIDs[0], copies->UnitLineUnit);
	ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsCopyToUnitLines(wxCommandEvent &Event)
{
	for(short loop=1; loop < UnitLineIDs.size(); ++loop)
	{
		GenieFile->UnitLines[UnitLineIDs[loop]].UnitIDs = GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs;
	}
}

void AGE_Frame::CreateUnitLineControls()
{
	Tab_UnitLine = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	UnitLines_Main = new wxBoxSizer(wxHORIZONTAL);
	UnitLines_ListArea = new wxBoxSizer(wxVERTICAL);
	UnitLines_UnitLines_Buttons = new wxGridSizer(3, 0, 0);
	UnitLineUnits_ListArea = new wxBoxSizer(wxVERTICAL);
	UnitLines_UnitLineUnits_Buttons = new wxGridSizer(3, 0, 0);
	UnitLines_DataArea = new wxBoxSizer(wxVERTICAL);

	UnitLines_UnitLines = new wxStaticBoxSizer(wxVERTICAL, Tab_UnitLine, "Unitlines (Used by AIs)");
	UnitLines_UnitLines_Search = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLines_Search_R = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLines_List = new wxListBox(Tab_UnitLine, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	UnitLines_Add = new wxButton(Tab_UnitLine, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Insert = new wxButton(Tab_UnitLine, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Delete = new wxButton(Tab_UnitLine, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Copy = new wxButton(Tab_UnitLine, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Paste = new wxButton(Tab_UnitLine, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	UnitLines_PasteInsert = new wxButton(Tab_UnitLine, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	UnitLines_UnitLineUnits = new wxStaticBoxSizer(wxVERTICAL, Tab_UnitLine, "Units");
	UnitLines_UnitLineUnits_Search = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLineUnits_Search_R = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLineUnits_List = new wxListBox(Tab_UnitLine, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	UnitLineUnits_Add = new wxButton(Tab_UnitLine, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Insert = new wxButton(Tab_UnitLine, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Delete = new wxButton(Tab_UnitLine, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Copy = new wxButton(Tab_UnitLine, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Paste = new wxButton(Tab_UnitLine, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_PasteInsert = new wxButton(Tab_UnitLine, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_CopyToUnitLines = new wxButton(Tab_UnitLine, wxID_ANY, "Copy all to selected unitlines", wxDefaultPosition, wxSize(5, 20));

	UnitLines_Holder_ID = new wxBoxSizer(wxVERTICAL);
	UnitLines_Text_ID = new wxStaticText(Tab_UnitLine, wxID_ANY, " Unitline ID", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitLines_ID = new TextCtrl_Short(Tab_UnitLine);
	UnitLines_Holder_Name = new wxBoxSizer(wxVERTICAL);
	UnitLines_Text_Name = new wxStaticText(Tab_UnitLine, wxID_ANY, " Unitline Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitLines_Name = new TextCtrl_String(Tab_UnitLine, 30);

	UnitLineUnits_Holder_Units = new wxBoxSizer(wxVERTICAL);
	UnitLineUnits_Text_Units = new wxStaticText(Tab_UnitLine, wxID_ANY, " Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitLineUnits_Units = new TextCtrl_Short(Tab_UnitLine);
	UnitLineUnits_ComboBox_Units = new ComboBox_Plus1(Tab_UnitLine, UnitLineUnits_Units);
	UnitComboBoxList.push_back(UnitLineUnits_ComboBox_Units);

	UnitLines_UnitLines_Buttons->Add(UnitLines_Add, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Insert, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Delete, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Copy, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Paste, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_PasteInsert, 1, wxEXPAND);

	UnitLines_UnitLines->Add(UnitLines_UnitLines_Search, 0, wxEXPAND);
	UnitLines_UnitLines->Add(UnitLines_UnitLines_Search_R, 0, wxEXPAND);
	UnitLines_UnitLines->Add(-1, 2);
	UnitLines_UnitLines->Add(UnitLines_UnitLines_List, 1, wxEXPAND);
	UnitLines_UnitLines->Add(-1, 2);
	UnitLines_UnitLines->Add(UnitLines_UnitLines_Buttons, 0, wxEXPAND);

	UnitLines_ListArea->Add(-1, 10);
	UnitLines_ListArea->Add(UnitLines_UnitLines, 1, wxEXPAND);
	UnitLines_ListArea->Add(-1, 10);

	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Add, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Insert, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Delete, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Copy, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Paste, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_PasteInsert, 1, wxEXPAND);

	UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_Search, 0, wxEXPAND);
	UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_Search_R, 0, wxEXPAND);
	UnitLines_UnitLineUnits->Add(-1, 2);
	UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_List, 1, wxEXPAND);
	UnitLines_UnitLineUnits->Add(-1, 2);
	UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_Buttons, 0, wxEXPAND);
	UnitLines_UnitLineUnits->Add(-1, 2);
	UnitLines_UnitLineUnits->Add(UnitLineUnits_CopyToUnitLines, 0, wxEXPAND);

	UnitLineUnits_ListArea->Add(-1, 10);
	UnitLineUnits_ListArea->Add(UnitLines_UnitLineUnits, 1, wxEXPAND);
	UnitLineUnits_ListArea->Add(-1, 10);

	UnitLines_Holder_ID->Add(UnitLines_Text_ID, 0, wxEXPAND);
	UnitLines_Holder_ID->Add(UnitLines_ID, 1, wxEXPAND);
	UnitLines_Holder_Name->Add(UnitLines_Text_Name, 0, wxEXPAND);
	UnitLines_Holder_Name->Add(UnitLines_Name, 1, wxEXPAND);
	UnitLineUnits_Holder_Units->Add(UnitLineUnits_Text_Units, 0, wxEXPAND);
	UnitLineUnits_Holder_Units->Add(UnitLineUnits_Units, 1, wxEXPAND);
	UnitLineUnits_Holder_Units->Add(UnitLineUnits_ComboBox_Units, 1, wxEXPAND);

	UnitLines_DataArea->Add(-1, 10);
	UnitLines_DataArea->Add(UnitLines_Holder_ID, 0, wxEXPAND);
	UnitLines_DataArea->Add(-1, 5);
	UnitLines_DataArea->Add(UnitLines_Holder_Name, 0, wxEXPAND);
	UnitLines_DataArea->Add(-1, 5);
	UnitLines_DataArea->Add(UnitLineUnits_Holder_Units, 0, wxEXPAND);

	UnitLines_Main->Add(10, -1);
	UnitLines_Main->Add(UnitLines_ListArea, 1, wxEXPAND);
	UnitLines_Main->Add(10, -1);
	UnitLines_Main->Add(UnitLineUnits_ListArea, 1, wxEXPAND);
	UnitLines_Main->Add(10, -1);
	UnitLines_Main->Add(UnitLines_DataArea, 1, wxEXPAND);
	UnitLines_Main->AddStretchSpacer(1);

	if(EnableIDFix)
	UnitLines_ID->Enable(false);

	Tab_UnitLine->SetSizer(UnitLines_Main);

	Connect(UnitLines_UnitLines_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitLinesSelect));
	Connect(UnitLines_UnitLines_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitLinesSearch));
	Connect(UnitLines_UnitLines_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitLinesSearch));
	Connect(UnitLines_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesAdd));
	Connect(UnitLines_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesInsert));
	Connect(UnitLines_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesDelete));
	Connect(UnitLines_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesCopy));
	Connect(UnitLines_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesPaste));
	Connect(UnitLines_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLinesPasteInsert));
	Connect(UnitLines_UnitLineUnits_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsSelect));
	Connect(UnitLines_UnitLineUnits_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsSearch));
	Connect(UnitLines_UnitLineUnits_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsSearch));
	Connect(UnitLineUnits_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsAdd));
	Connect(UnitLineUnits_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsInsert));
	Connect(UnitLineUnits_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsDelete));
	Connect(UnitLineUnits_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsCopy));
	Connect(UnitLineUnits_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsPaste));
	Connect(UnitLineUnits_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsPasteInsert));
	Connect(UnitLineUnits_CopyToUnitLines->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitLineUnitsCopyToUnitLines));

	UnitLines_Name->Connect(UnitLines_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_UnitLines), NULL, this);
	UnitLineUnits_Units->Connect(UnitLineUnits_Units->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_UnitLines), NULL, this);
	UnitLineUnits_ComboBox_Units->Connect(UnitLineUnits_ComboBox_Units->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_UnitLines), NULL, this);
}

void AGE_Frame::OnKillFocus_UnitLines(wxFocusEvent &Event)
{
	if(!((AGETextCtrl*)Event.GetEventObject())->SaveEdits()) return;
	if(Event.GetId() == UnitLines_Name->GetId())
	{
		ListUnitLines();
	}
	else if(Event.GetId() == UnitLineUnits_Units->GetId())
	{
		ListUnitLineUnits();
	}
	Event.Skip();
}

void AGE_Frame::OnUpdateCombo_UnitLines(wxCommandEvent &Event)
{
	((AGEComboBox*)Event.GetEventObject())->OnUpdate(Event);
	ListUnitLineUnits();
}
