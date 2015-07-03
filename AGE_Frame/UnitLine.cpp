#include "../AGE_Frame.h"

string AGE_Frame::GetUnitLineName(short Index)
{
	if(!GenieFile->UnitLines[Index].Name.empty())
		return GenieFile->UnitLines[Index].Name;
	return "Unitline "+lexical_cast<string>(Index);
}

void AGE_Frame::OnUnitLinesSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListUnitLines();
}

void AGE_Frame::ListUnitLines()
{
	FirstVisible = How2List == SEARCH ? 0 : UnitLines_UnitLines_List->HitTest(wxPoint(0, 0));
	InitUnitLines();
	wxTimerEvent E;
	OnUnitLinesTimer(E);
}

void AGE_Frame::InitUnitLines()
{
	searchText = UnitLines_UnitLines_Search->GetValue().Lower();
	excludeText = UnitLines_UnitLines_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString names, filteredNames;
	names.Alloc(GenieFile->Civs[0].Units.size());

	for(short loop = 0; loop < GenieFile->UnitLines.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineName(loop);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->UnitLines[loop]);
		}
		names.Add(Name);
	}

	Listing(UnitLines_UnitLines_List, filteredNames, dataPointers);

	short selection = Units_Unitline_ComboBox->GetSelection();
	Units_Unitline_ComboBox->Clear();
	Units_Unitline_ComboBox->Append("-1 - None");
	Units_Unitline_ComboBox->Append(names);
	Units_Unitline_ComboBox->SetSelection(selection);
}

void AGE_Frame::OnUnitLinesSelect(wxCommandEvent &event)
{
    if(!unitLineTimer.IsRunning())
        unitLineTimer.Start(150);
}

void AGE_Frame::OnUnitLinesTimer(wxTimerEvent &event)
{
    unitLineTimer.Stop();
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);

	//SwapSelection(event.GetSelection(), Items);
	UnitLineIDs.resize(selections);
	UnitLines_ID->clear();
	UnitLines_Name->clear();

	genie::UnitLine * LinePointer;
	for(auto loop = selections; loop--> 0;)
	{
		LinePointer = (genie::UnitLine*)UnitLines_UnitLines_List->GetClientData(Items.Item(loop));
		UnitLineIDs[loop] = (LinePointer - (&GenieFile->UnitLines[0]));

		UnitLines_ID->prepend(&LinePointer->ID);
		UnitLines_Name->prepend(&LinePointer->Name);
	}
	SetStatusText("Selections: "+lexical_cast<string>(selections)+"    Selected unit line: "+lexical_cast<string>(UnitLineIDs[0]), 0);

	UnitLines_ID->update();
	UnitLines_Name->update();
	ListUnitLineUnits();
}

void AGE_Frame::OnUnitLinesAdd(wxCommandEvent &event)
{
	if(NULL == GenieFile) return;

	wxBusyCursor WaitCursor;
	AddToListIDFix(GenieFile->UnitLines);
	ListUnitLines();
}

void AGE_Frame::OnUnitLinesInsert(wxCommandEvent &event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListIDFix(GenieFile->UnitLines, UnitLineIDs[0]);
	ListUnitLines();
}

void AGE_Frame::OnUnitLinesDelete(wxCommandEvent &event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromListIDFix(GenieFile->UnitLines, UnitLineIDs);
	ListUnitLines();
}

void AGE_Frame::OnUnitLinesCopy(wxCommandEvent &event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->UnitLines, UnitLineIDs, copies.UnitLine);
	UnitLines_UnitLines_List->SetFocus();
}

void AGE_Frame::OnUnitLinesPaste(wxCommandEvent &event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(UnitLineIDs.size(), copies.UnitLine.size()))
		{
			PasteToListIDFix(GenieFile->UnitLines, UnitLineIDs, copies.UnitLine);
		}
	}
	else
	{
		PasteToListIDFix(GenieFile->UnitLines, UnitLineIDs[0], copies.UnitLine);
	}
	ListUnitLines();
}

void AGE_Frame::OnUnitLinesPasteInsert(wxCommandEvent &event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListIDFix(GenieFile->UnitLines, UnitLineIDs[0], copies.UnitLine);
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

void AGE_Frame::OnUnitLineUnitsSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListUnitLineUnits();
}

void AGE_Frame::ListUnitLineUnits()
{
	FirstVisible = How2List == SEARCH ? 0 : UnitLines_UnitLineUnits_List->HitTest(wxPoint(0, 0));
	searchText = UnitLines_UnitLineUnits_Search->GetValue().Lower();
	excludeText = UnitLines_UnitLineUnits_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	for(short loop = 0; loop < GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs.size(); ++loop)
	{
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitLineUnitName(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[loop]);
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[loop]);
		}
	}
	Listing(UnitLines_UnitLineUnits_List, filteredNames, dataPointers);

	wxTimerEvent E;
	OnUnitLineUnitsTimer(E);
}

void AGE_Frame::OnUnitLineUnitsSelect(wxCommandEvent &event)
{
    if(!unitLineUnitTimer.IsRunning())
        unitLineUnitTimer.Start(150);
}

void AGE_Frame::OnUnitLineUnitsTimer(wxTimerEvent &event)
{
    unitLineUnitTimer.Stop();
	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
    UnitLineUnits_Units->clear();
	if(selections > 0)
	{
		//SwapSelection(event.GetSelection(), Items);
		UnitLineUnitIDs.resize(selections);

		int16_t * UnitPointer;
		for(auto loop = selections; loop--> 0;)
		{
			UnitPointer = (int16_t*)UnitLines_UnitLineUnits_List->GetClientData(Items.Item(loop));
			UnitLineUnitIDs[loop] = (UnitPointer - (&GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs[0]));
			UnitLineUnits_Units->prepend(UnitPointer);
		}
	}
    UnitLineUnits_Units->update();
}

void AGE_Frame::OnUnitLineUnitsAdd(wxCommandEvent &event)
{
	auto selections = UnitLines_UnitLines_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	AddToListNoGV(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs);
	ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsInsert(wxCommandEvent &event)
{
	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	InsertToListNoGV(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs, UnitLineUnitIDs[0]);
	ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsDelete(wxCommandEvent &event)
{
	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs, UnitLineUnitIDs);
	ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsCopy(wxCommandEvent &event)
{
	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs, UnitLineUnitIDs, copies.UnitLineUnit);
	UnitLines_UnitLineUnits_List->SetFocus();
}

void AGE_Frame::OnUnitLineUnitsPaste(wxCommandEvent &event)
{
	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(UnitLineUnitIDs.size(), copies.UnitLineUnit.size()))
		{
			PasteToListNoGV(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs, UnitLineUnitIDs, copies.UnitLineUnit);
		}
	}
	else
	{
		PasteToListNoGV(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs, UnitLineUnitIDs[0], copies.UnitLineUnit);
	}
	ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsPasteInsert(wxCommandEvent &event)
{
	auto selections = UnitLines_UnitLineUnits_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->UnitLines[UnitLineIDs[0]].UnitIDs, UnitLineUnitIDs[0], copies.UnitLineUnit);
	ListUnitLineUnits();
}

void AGE_Frame::OnUnitLineUnitsCopyToUnitLines(wxCommandEvent &event)
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
	UnitLines_UnitLines_List = new wxListBox(Tab_UnitLine, wxID_ANY, wxDefaultPosition, wxSize(200, 100), 0, NULL, wxLB_EXTENDED);
	UnitLines_Add = new wxButton(Tab_UnitLine, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Insert = new wxButton(Tab_UnitLine, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Delete = new wxButton(Tab_UnitLine, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Copy = new wxButton(Tab_UnitLine, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnitLines_Paste = new wxButton(Tab_UnitLine, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	UnitLines_PasteInsert = new wxButton(Tab_UnitLine, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));

	UnitLines_UnitLineUnits = new wxStaticBoxSizer(wxVERTICAL, Tab_UnitLine, "Units");
	UnitLines_UnitLineUnits_Search = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLineUnits_Search_R = new wxTextCtrl(Tab_UnitLine, wxID_ANY);
	UnitLines_UnitLineUnits_List = new wxListBox(Tab_UnitLine, wxID_ANY, wxDefaultPosition, wxSize(200, 100), 0, NULL, wxLB_EXTENDED);
	UnitLineUnits_Add = new wxButton(Tab_UnitLine, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Insert = new wxButton(Tab_UnitLine, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Delete = new wxButton(Tab_UnitLine, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Copy = new wxButton(Tab_UnitLine, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_Paste = new wxButton(Tab_UnitLine, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_PasteInsert = new wxButton(Tab_UnitLine, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	UnitLineUnits_CopyToUnitLines = new wxButton(Tab_UnitLine, wxID_ANY, "Copy all to selected unitlines", wxDefaultPosition, wxSize(5, 20));

	UnitLines_ID_Holder = new wxBoxSizer(wxVERTICAL);
	UnitLines_ID_Text = new wxStaticText(Tab_UnitLine, wxID_ANY, " Unitline ID", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitLines_ID = AGETextCtrl::init(CShort, NULL, this, AGEwindow, Tab_UnitLine);
	UnitLines_Name_Holder = new wxBoxSizer(wxVERTICAL);
	UnitLines_Name_Text = new wxStaticText(Tab_UnitLine, wxID_ANY, " Unitline Name", wxDefaultPosition, wxSize(200, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitLines_Name = AGETextCtrl::init(CString, NULL, this, AGEwindow, Tab_UnitLine, 30);

	UnitLineUnits_Holder = new wxBoxSizer(wxVERTICAL);
	UnitLineUnits_Text = new wxStaticText(Tab_UnitLine, wxID_ANY, " Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitLineUnits_Units = AGETextCtrl::init(CShort, NULL, this, AGEwindow, Tab_UnitLine);
	UnitLineUnits_ComboBox = new ComboBox_Plus1(Tab_UnitLine, UnitLineUnits_Units);
	UnitComboBoxList.push_back(UnitLineUnits_ComboBox);

	UnitLines_UnitLines_Buttons->Add(UnitLines_Add, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Delete, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Insert, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Copy, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_Paste, 1, wxEXPAND);
	UnitLines_UnitLines_Buttons->Add(UnitLines_PasteInsert, 1, wxEXPAND);

	UnitLines_UnitLines->Add(UnitLines_UnitLines_Search, 0, wxEXPAND);
	UnitLines_UnitLines->Add(UnitLines_UnitLines_Search_R, 0, wxEXPAND);
	UnitLines_UnitLines->AddSpacer(2);
	UnitLines_UnitLines->Add(UnitLines_UnitLines_List, 1, wxEXPAND);
	UnitLines_UnitLines->AddSpacer(2);
	UnitLines_UnitLines->Add(UnitLines_UnitLines_Buttons, 0, wxEXPAND);

	UnitLines_ListArea->AddSpacer(5);
	UnitLines_ListArea->Add(UnitLines_UnitLines, 1, wxEXPAND);
	UnitLines_ListArea->AddSpacer(5);

	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Add, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Delete, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Insert, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Copy, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_Paste, 1, wxEXPAND);
	UnitLines_UnitLineUnits_Buttons->Add(UnitLineUnits_PasteInsert, 1, wxEXPAND);

	UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_Search, 0, wxEXPAND);
	UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_Search_R, 0, wxEXPAND);
	UnitLines_UnitLineUnits->AddSpacer(2);
	UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_List, 1, wxEXPAND);
	UnitLines_UnitLineUnits->AddSpacer(2);
	UnitLines_UnitLineUnits->Add(UnitLines_UnitLineUnits_Buttons, 0, wxEXPAND);
	UnitLines_UnitLineUnits->AddSpacer(2);
	UnitLines_UnitLineUnits->Add(UnitLineUnits_CopyToUnitLines, 0, wxEXPAND);

	UnitLineUnits_ListArea->AddSpacer(5);
	UnitLineUnits_ListArea->Add(UnitLines_UnitLineUnits, 1, wxEXPAND);
	UnitLineUnits_ListArea->AddSpacer(5);

	UnitLines_ID_Holder->Add(UnitLines_ID_Text, 0, wxEXPAND);
	UnitLines_ID_Holder->Add(UnitLines_ID, 1, wxEXPAND);
	UnitLines_Name_Holder->Add(UnitLines_Name_Text, 0, wxEXPAND);
	UnitLines_Name_Holder->Add(UnitLines_Name, 1, wxEXPAND);
	UnitLineUnits_Holder->Add(UnitLineUnits_Text, 0, wxEXPAND);
	UnitLineUnits_Holder->Add(UnitLineUnits_Units, 1, wxEXPAND);
	UnitLineUnits_Holder->Add(UnitLineUnits_ComboBox, 1, wxEXPAND);

	UnitLines_DataArea->AddSpacer(5);
	UnitLines_DataArea->Add(UnitLines_ID_Holder, 0, wxEXPAND);
	UnitLines_DataArea->AddSpacer(5);
	UnitLines_DataArea->Add(UnitLines_Name_Holder, 0, wxEXPAND);
	UnitLines_DataArea->AddSpacer(5);
	UnitLines_DataArea->Add(UnitLineUnits_Holder, 0, wxEXPAND);

	UnitLines_Main->AddSpacer(5);
	UnitLines_Main->Add(UnitLines_ListArea, 1, wxEXPAND);
	UnitLines_Main->AddSpacer(5);
	UnitLines_Main->Add(UnitLineUnits_ListArea, 1, wxEXPAND);
	UnitLines_Main->AddSpacer(5);
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

    unitLineTimer.Connect(unitLineTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnUnitLinesTimer), NULL, this);
    unitLineUnitTimer.Connect(unitLineUnitTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnUnitLineUnitsTimer), NULL, this);
	UnitLines_Name->Connect(UnitLines_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_UnitLines), NULL, this);
	UnitLineUnits_Units->Connect(UnitLineUnits_Units->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_UnitLines), NULL, this);
	UnitLineUnits_ComboBox->Connect(UnitLineUnits_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_UnitLines), NULL, this);
}

void AGE_Frame::OnKillFocus_UnitLines(wxFocusEvent &event)
{
	event.Skip();
	if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
	if(event.GetId() == UnitLines_Name->GetId())
	{
		ListUnitLines();
	}
	else if(event.GetId() == UnitLineUnits_Units->GetId())
	{
		ListUnitLineUnits();
	}
}

void AGE_Frame::OnUpdateCombo_UnitLines(wxCommandEvent &event)
{
	((AGEComboBox*)event.GetEventObject())->OnUpdate(event);
	ListUnitLineUnits();
}
