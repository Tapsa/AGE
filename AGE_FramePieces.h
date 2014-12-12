#include "Common.h"
#include "AGE_TextControls.h"
#include "AGE_ComboBoxes.h"
#include "AGE_CheckBoxes.h"

class AGE_List32Box
{
private:
	wxGridSizer *Buttons;
public:
	AGE_List32Box() {}
	virtual ~AGE_List32Box() {}

	wxStaticBoxSizer *ItemList;
	wxTextCtrl *Search, *SearchRecursive;
	wxListBox *List;
	TextCtrl_Long *Item;
	ComboBox_Plus1 *ItemCombo;
	wxButton *Add, *Insert, *Delete, *Copy, *Paste, *PasteInsert, *CopyAllToSelected;

	void CreateControls(wxScrolledWindow* &scroller, const wxString &listName, const wxString &itemName)
	{
		ItemList = new wxStaticBoxSizer(wxVERTICAL, scroller, listName);
		Search = new wxTextCtrl(scroller, wxID_ANY);
		SearchRecursive = new wxTextCtrl(scroller, wxID_ANY);
		List = new wxListBox(scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
		Item = new TextCtrl_Long(scroller);
		ItemCombo = new ComboBox_Plus1(scroller, Item);
		Buttons = new wxGridSizer(3, 0, 0);
		Add = new wxButton(scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
		Insert = new wxButton(scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
		Delete = new wxButton(scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
		Copy = new wxButton(scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
		Paste = new wxButton(scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
		PasteInsert = new wxButton(scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
		CopyAllToSelected = new wxButton(scroller, wxID_ANY, "Copy all to selected " + itemName, wxDefaultPosition, wxSize(5, 20));

		Buttons->Add(Add, 1, wxEXPAND);
		Buttons->Add(Delete, 1, wxEXPAND);
		Buttons->Add(Insert, 1, wxEXPAND);
		Buttons->Add(Copy, 1, wxEXPAND);
		Buttons->Add(Paste, 1, wxEXPAND);
		Buttons->Add(PasteInsert, 1, wxEXPAND);

		ItemList->Add(Search, 0, wxEXPAND);
		ItemList->Add(SearchRecursive, 0, wxEXPAND);
		ItemList->Add(-1, 2);
		ItemList->Add(List, 1, wxEXPAND);
		ItemList->Add(-1, 2);
		ItemList->Add(Item, 0, wxEXPAND);
		ItemList->Add(ItemCombo, 0, wxEXPAND);
		ItemList->Add(-1, 2);
		ItemList->Add(Buttons, 0, wxEXPAND);
		ItemList->Add(-1, 2);
		ItemList->Add(CopyAllToSelected, 0, wxEXPAND);
	}
};

class AGE_AreaTT84
{
private:
	wxGridSizer *Buttons;
	wxBoxSizer *ItemList, *UsedItems_H, *Item_H;
	wxStaticText *UsedItems_T;
public:
	AGE_AreaTT84() {}
	virtual ~AGE_AreaTT84() {}

	wxStaticBoxSizer *Area;
	wxTextCtrl *Search, *SearchRecursive;
	wxListBox *List;
	TextCtrl_Long *Item, *Mode, *UsedItems;
	ComboBox_Plus1 *ItemCombo;
	wxOwnerDrawnComboBox *ModeCombo;
	wxButton *Copy, *Paste, *CopyAllToSelected;

	void CreateControls(wxScrolledWindow* &scroller, const wxString &itemName)
	{
		Area = new wxStaticBoxSizer(wxVERTICAL, scroller, "Connected Items");
		ItemList = new wxBoxSizer(wxVERTICAL);
		UsedItems_H = new wxBoxSizer(wxVERTICAL);
		UsedItems_T = new wxStaticText(scroller, wxID_ANY, " Used Ages/Units/Researches", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT);
		UsedItems = new TextCtrl_Long(scroller);

		Search = new wxTextCtrl(scroller, wxID_ANY);
		SearchRecursive = new wxTextCtrl(scroller, wxID_ANY);
		List = new wxListBox(scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
		Item_H = new wxBoxSizer(wxHORIZONTAL);
		Item = new TextCtrl_Long(scroller);
		ItemCombo = new ComboBox_Plus1(scroller, Item);
		Mode = new TextCtrl_Long(scroller);
		ModeCombo = new wxOwnerDrawnComboBox(scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
		Buttons = new wxGridSizer(2, 0, 0);
		Copy = new wxButton(scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
		Paste = new wxButton(scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
		CopyAllToSelected = new wxButton(scroller, wxID_ANY, "Copy all to selected " + itemName, wxDefaultPosition, wxSize(5, 20));

		ModeCombo->Append("Age");
		ModeCombo->Append("Building");
		ModeCombo->Append("Unit");
		ModeCombo->Append("Research");
		ModeCombo->SetSelection(0);

		Buttons->Add(Copy, 1, wxEXPAND);
		Buttons->Add(Paste, 1, wxEXPAND);

		Item_H->Add(Mode, 1, wxEXPAND);
		Item_H->Add(2, -1);
		Item_H->Add(Item, 2, wxEXPAND);

		ItemList->Add(Search, 0, wxEXPAND);
		ItemList->Add(SearchRecursive, 0, wxEXPAND);
		ItemList->Add(-1, 2);
		ItemList->Add(List, 1, wxEXPAND);
		ItemList->Add(-1, 2);
		ItemList->Add(Item_H, 0, wxEXPAND);
		ItemList->Add(ItemCombo, 0, wxEXPAND);
		ItemList->Add(ModeCombo, 0, wxEXPAND);
		ItemList->Add(-1, 2);
		ItemList->Add(Buttons, 0, wxEXPAND);
		ItemList->Add(-1, 2);
		ItemList->Add(CopyAllToSelected, 0, wxEXPAND);

		UsedItems_H->Add(UsedItems_T, 0, wxEXPAND);
		UsedItems_H->Add(UsedItems, 0, wxEXPAND);
		Area->Add(UsedItems_H, 0, wxEXPAND);
		Area->Add(-1, 2);
		Area->Add(ItemList, 0, wxEXPAND);
	}
};

class AGE_AreaTT31020
{
private:
	wxGridSizer *Buttons;
	wxBoxSizer *ItemList, *UsedItems_H, *Unknowns_H, *Unknown_H, *Top;
	wxStaticText *UsedItems_T, *Unknown_T;
public:
	AGE_AreaTT31020() {}
	virtual ~AGE_AreaTT31020() {}

	wxStaticBoxSizer *Area;
	wxTextCtrl *Search, *SearchRecursive;
	wxListBox *List;
	TextCtrl_Byte *Unknown1, *Unknown2, *UsedItems, *Unknown;
	wxButton *Copy, *Paste, *CopyAllToSelected;

	void CreateControls(wxScrolledWindow* &scroller)
	{
		Area = new wxStaticBoxSizer(wxVERTICAL, scroller, "Unknown Items");
		ItemList = new wxBoxSizer(wxVERTICAL);
		Top = new wxBoxSizer(wxHORIZONTAL);
		UsedItems_H = new wxBoxSizer(wxVERTICAL);
		UsedItems_T = new wxStaticText(scroller, wxID_ANY, " Slots Used?", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT);
		UsedItems = new TextCtrl_Byte(scroller);
		Unknown_H = new wxBoxSizer(wxVERTICAL);
		Unknown_T = new wxStaticText(scroller, wxID_ANY, " Unknown 6", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT);
		Unknown = new TextCtrl_Byte(scroller);

		Search = new wxTextCtrl(scroller, wxID_ANY);
		SearchRecursive = new wxTextCtrl(scroller, wxID_ANY);
		List = new wxListBox(scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
		Unknowns_H = new wxBoxSizer(wxHORIZONTAL);
		Unknown1 = new TextCtrl_Byte(scroller);
		Unknown2 = new TextCtrl_Byte(scroller);
		Buttons = new wxGridSizer(2, 0, 0);
		Copy = new wxButton(scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
		Paste = new wxButton(scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
		CopyAllToSelected = new wxButton(scroller, wxID_ANY, "Copy all to selected ages", wxDefaultPosition, wxSize(5, 20));

		Buttons->Add(Copy, 1, wxEXPAND);
		Buttons->Add(Paste, 1, wxEXPAND);

		Unknowns_H->Add(Unknown1, 1, wxEXPAND);
		Unknowns_H->Add(2, -1);
		Unknowns_H->Add(Unknown2, 1, wxEXPAND);

		ItemList->Add(Search, 0, wxEXPAND);
		ItemList->Add(SearchRecursive, 0, wxEXPAND);
		ItemList->Add(-1, 2);
		ItemList->Add(List, 1, wxEXPAND);
		ItemList->Add(-1, 2);
		ItemList->Add(Unknowns_H, 0, wxEXPAND);
		ItemList->Add(-1, 2);
		ItemList->Add(Buttons, 0, wxEXPAND);
		ItemList->Add(-1, 2);
		ItemList->Add(CopyAllToSelected, 0, wxEXPAND);

		UsedItems_H->Add(UsedItems_T, 0, wxEXPAND);
		UsedItems_H->Add(UsedItems, 0, wxEXPAND);
		Unknown_H->Add(Unknown_T, 0, wxEXPAND);
		Unknown_H->Add(Unknown, 0, wxEXPAND);
		Top->Add(UsedItems_H, 1, wxEXPAND);
		Top->Add(5, -1);
		Top->Add(Unknown_H, 1, wxEXPAND);
		Area->Add(Top, 0, wxEXPAND);
		Area->Add(-1, 2);
		Area->Add(ItemList, 0, wxEXPAND);
	}
};
