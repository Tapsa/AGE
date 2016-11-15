#pragma once
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
    ProperList *List;
    AGETextCtrl *Item;
    ComboBox_Plus1 *ItemCombo;
    wxButton *Add, *Insert, *Delete, *Copy, *Paste, *PasteInsert, *CopyAllToSelected;

    void CreateControls(wxFrame* frame, DelayedPopUp *popUp, wxScrolled<APanel>* scroller, const wxString &itemName,
        const wxString &listName, wxArrayString *choices)
    {
        ItemList = new wxStaticBoxSizer(wxVERTICAL, scroller, listName);
        Search = new wxTextCtrl(scroller, wxID_ANY);
        SearchRecursive = new wxTextCtrl(scroller, wxID_ANY);
        List = new ProperList(scroller, wxSize(10, 100));
        Item = AGETextCtrl::init(CLong, NULL, frame, popUp, scroller);
        ItemCombo = new ComboBox_Plus1(scroller, Item, choices);
        Buttons = new wxGridSizer(3, 0, 0);
        Add = new wxButton(scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
        Insert = new wxButton(scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
        Delete = new wxButton(scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
        Copy = new wxButton(scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
        Paste = new wxButton(scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
        PasteInsert = new wxButton(scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
        CopyAllToSelected = new wxButton(scroller, wxID_ANY, "Copy all to selected " + itemName, wxDefaultPosition, wxSize(10, -1));

        Buttons->Add(Add, 1, wxEXPAND);
        Buttons->Add(Delete, 1, wxEXPAND);
        Buttons->Add(Insert, 1, wxEXPAND);
        Buttons->Add(Copy, 1, wxEXPAND);
        Buttons->Add(Paste, 1, wxEXPAND);
        Buttons->Add(PasteInsert, 1, wxEXPAND);

        ItemList->Add(Search, 0, wxEXPAND);
        ItemList->Add(SearchRecursive, 0, wxEXPAND);
        ItemList->Add(List, 1, wxEXPAND | wxTOP | wxBOTTOM, 2);
        ItemList->Add(Item, 0, wxEXPAND);
        ItemList->Add(ItemCombo, 0, wxEXPAND);
        ItemList->Add(Buttons, 0, wxEXPAND | wxTOP | wxBOTTOM, 2);
        ItemList->Add(CopyAllToSelected, 0, wxEXPAND);
    }
};

class AGE_AreaTT84
{
private:
    wxGridSizer *Buttons;
    wxBoxSizer *ItemList, *UsedItems_H, *Item_H;
    SolidText *UsedItems_T;
public:
    AGE_AreaTT84() {}
    virtual ~AGE_AreaTT84() {}

    wxStaticBoxSizer *Area;
    wxTextCtrl *Search, *SearchRecursive;
    ProperList *List;
    AGETextCtrl *Item, *Mode, *UsedItems;
    ComboBox_Plus1 *ItemCombo;
    AGEComboBox *ModeCombo;
    wxButton *Copy, *Paste, *CopyAllToSelected;

    void CreateControls(wxFrame* frame, DelayedPopUp *popUp, wxScrolled<APanel>* scroller, const wxString &itemName,
        wxArrayString *choices)
    {
        Area = new wxStaticBoxSizer(wxVERTICAL, scroller, "Connected Items");
        ItemList = new wxBoxSizer(wxVERTICAL);
        UsedItems_H = new wxBoxSizer(wxVERTICAL);
        UsedItems_T = new SolidText(scroller, " Used Ages/Units/Researches");
        UsedItems = AGETextCtrl::init(CLong, NULL, frame, popUp, scroller);

        Search = new wxTextCtrl(scroller, wxID_ANY);
        SearchRecursive = new wxTextCtrl(scroller, wxID_ANY);
        List = new ProperList(scroller, wxSize(10, 100));
        Item_H = new wxBoxSizer(wxHORIZONTAL);
        Item = AGETextCtrl::init(CLong, NULL, frame, popUp, scroller);
        ItemCombo = new ComboBox_Plus1(scroller, Item, choices);
        Mode = AGETextCtrl::init(CLong, NULL, frame, popUp, scroller, AGETextCtrl::MEDIUM);
        ModeCombo = new AGEComboBox(scroller, choices);
        Buttons = new wxGridSizer(2, 0, 0);
        Copy = new wxButton(scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
        Paste = new wxButton(scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
        CopyAllToSelected = new wxButton(scroller, wxID_ANY, "Copy all to selected " + itemName, wxDefaultPosition, wxSize(10, -1));

        ModeCombo->Flash();

        Buttons->Add(Copy, 1, wxEXPAND);
        Buttons->Add(Paste, 1, wxEXPAND);

        Item_H->Add(Mode);
        Item_H->Add(Item, 2, wxEXPAND | wxLEFT, 2);

        ItemList->Add(Search, 0, wxEXPAND);
        ItemList->Add(SearchRecursive, 0, wxEXPAND);
        ItemList->Add(List, 1, wxEXPAND | wxTOP | wxBOTTOM, 2);
        ItemList->Add(Item_H, 0, wxEXPAND);
        ItemList->Add(ItemCombo, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
        ItemList->Add(ModeCombo, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
        ItemList->Add(Buttons, 0, wxEXPAND | wxTOP | wxBOTTOM, 2);
        ItemList->Add(CopyAllToSelected, 0, wxEXPAND);

        UsedItems_H->Add(UsedItems_T, 0, wxEXPAND);
        UsedItems_H->Add(UsedItems, 0, wxEXPAND);
        Area->Add(UsedItems_H, 0, wxEXPAND);
        Area->Add(ItemList, 0, wxEXPAND | wxTOP, 2);
    }
};

class AGE_AreaTT31020
{
private:
    wxGridSizer *Buttons;
    wxBoxSizer *ItemList, *UsedItems_H, *Unknowns_H, *Unknown_H, *Top;
    SolidText *UsedItems_T, *Unknown_T;
public:
    AGE_AreaTT31020() {}
    virtual ~AGE_AreaTT31020() {}

    wxStaticBoxSizer *Area;
    wxTextCtrl *Search, *SearchRecursive;
    ProperList *List;
    AGETextCtrl *Unknown1, *Unknown2, *UsedItems, *Unknown;
    wxButton *Copy, *Paste, *CopyAllToSelected;

    void CreateControls(wxFrame* frame, DelayedPopUp *popUp, wxScrolled<APanel>* scroller)
    {
        Area = new wxStaticBoxSizer(wxVERTICAL, scroller, "Unknown Items");
        ItemList = new wxBoxSizer(wxVERTICAL);
        Top = new wxBoxSizer(wxHORIZONTAL);
        UsedItems_H = new wxBoxSizer(wxVERTICAL);
        UsedItems_T = new SolidText(scroller, " Slots Used?");
        UsedItems = AGETextCtrl::init(CByte, NULL, frame, popUp, scroller, AGETextCtrl::SMALL);
        Unknown_H = new wxBoxSizer(wxVERTICAL);
        Unknown_T = new SolidText(scroller, " Unknown 6");
        Unknown = AGETextCtrl::init(CByte, NULL, frame, popUp, scroller, AGETextCtrl::SMALL);

        Search = new wxTextCtrl(scroller, wxID_ANY);
        SearchRecursive = new wxTextCtrl(scroller, wxID_ANY);
        List = new ProperList(scroller, wxSize(10, 100));
        Unknowns_H = new wxBoxSizer(wxHORIZONTAL);
        Unknown1 = AGETextCtrl::init(CByte, NULL, frame, popUp, scroller, AGETextCtrl::SMALL);
        Unknown2 = AGETextCtrl::init(CByte, NULL, frame, popUp, scroller, AGETextCtrl::SMALL);
        Buttons = new wxGridSizer(2, 0, 0);
        Copy = new wxButton(scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(10, -1));
        Paste = new wxButton(scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
        CopyAllToSelected = new wxButton(scroller, wxID_ANY, "Copy all to selected ages", wxDefaultPosition, wxSize(10, -1));

        Buttons->Add(Copy, 1, wxEXPAND);
        Buttons->Add(Paste, 1, wxEXPAND);

        Unknowns_H->Add(Unknown1, 1, wxEXPAND);
        Unknowns_H->Add(Unknown2, 1, wxEXPAND | wxLEFT, 2);

        ItemList->Add(Search, 0, wxEXPAND);
        ItemList->Add(SearchRecursive, 0, wxEXPAND);
        ItemList->Add(List, 1, wxEXPAND | wxTOP | wxBOTTOM, 2);
        ItemList->Add(Unknowns_H, 0, wxEXPAND);
        ItemList->Add(Buttons, 0, wxEXPAND | wxTOP | wxBOTTOM, 2);
        ItemList->Add(CopyAllToSelected, 0, wxEXPAND);

        UsedItems_H->Add(UsedItems_T, 0, wxEXPAND);
        UsedItems_H->Add(UsedItems, 0, wxEXPAND);
        Unknown_H->Add(Unknown_T, 0, wxEXPAND);
        Unknown_H->Add(Unknown, 0, wxEXPAND);
        Top->Add(UsedItems_H, 1, wxEXPAND);
        Top->Add(Unknown_H, 1, wxEXPAND | wxLEFT, 5);
        Area->Add(Top, 0, wxEXPAND);
        Area->Add(ItemList, 1, wxEXPAND | wxTOP, 2);
    }
};
