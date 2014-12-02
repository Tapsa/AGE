#include "Common.h"
#include "AGE_TextControls.h"
#include "AGE_ComboBoxes.h"
#include "AGE_CheckBoxes.h"

class AGE_List
{
public:
	AGE_List() {}
	virtual ~AGE_List() {}

	wxStaticBoxSizer *ItemList;
	wxTextCtrl *Search, *SearchRecursive;
	wxListBox *List;
	TextCtrl_Long *Item;
	ComboBox_Plus1 *ItemCombo;
	wxGridSizer *Buttons;
	wxButton *Add, *Insert, *Delete, *Copy, *Paste, *PasteInsert, *CopyAllToSelected;

	void CreateControls(wxScrolledWindow* &scroller, const wxString &listName)
	{
		ItemList = new wxStaticBoxSizer(wxVERTICAL, scroller, listName);
		Search = new wxTextCtrl(scroller, wxID_ANY);
		SearchRecursive = new wxTextCtrl(scroller, wxID_ANY);
		List = new wxListBox(scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
		Item = new TextCtrl_Long(scroller);
		ItemCombo = new ComboBox_Plus1(scroller, Item);
		Buttons = new wxGridSizer(3, 0, 0);
		Add = new wxButton(scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
		Insert = new wxButton(scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
		Delete = new wxButton(scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
		Copy = new wxButton(scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
		Paste = new wxButton(scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
		PasteInsert = new wxButton(scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
		CopyAllToSelected = new wxButton(scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(5, 20));

		Buttons->Add(Add, 1, wxEXPAND);
		Buttons->Add(Insert, 1, wxEXPAND);
		Buttons->Add(Delete, 1, wxEXPAND);
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
