#include "../Common.hpp"
#include "../Includes.hpp"

class TabColors
{
	public:
	TabColors(wxNotebook* &Parent, bool &IDFix)
	{
		Tab = new wxPanel(Parent, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
		Main = new wxBoxSizer(wxHORIZONTAL);
		ListArea = new wxBoxSizer(wxVERTICAL);

		Colors = new wxStaticBoxSizer(wxVERTICAL, Tab, "Player Colors");
		Search = new wxTextCtrl(Tab, wxID_ANY);
		Search_R = new wxTextCtrl(Tab, wxID_ANY);
		List = new wxListBox(Tab, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, wxLB_EXTENDED);
		Buttons = new wxGridSizer(3, 0, 0);
		Add = new wxButton(Tab, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
		Insert = new wxButton(Tab, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
		Delete = new wxButton(Tab, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
		Copy = new wxButton(Tab, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
		Paste = new wxButton(Tab, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
		PasteInsert = new wxButton(Tab, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

		DataArea = new wxBoxSizer(wxVERTICAL);
		Holder_Name = new wxBoxSizer(wxVERTICAL);
		Holder_ID = new wxBoxSizer(wxVERTICAL);
		Holder_Palette = new wxBoxSizer(wxVERTICAL);
		Holder_Color = new wxBoxSizer(wxVERTICAL);
		Holder_MinimapColor = new wxBoxSizer(wxVERTICAL);
		Holder_UnknownArea = new wxBoxSizer(wxVERTICAL);
		Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
		Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
		Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
		Holder_Unknown4 = new wxBoxSizer(wxVERTICAL);
		Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
		Text_Name = new wxStaticText(Tab, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		Text_ID = new wxStaticText(Tab, wxID_ANY, " ID", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		Text_Palette = new wxStaticText(Tab, wxID_ANY, " Palette", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		Text_Color = new wxStaticText(Tab, wxID_ANY, " Color", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		Text_MinimapColor = new wxStaticText(Tab, wxID_ANY, " Minimap Color", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		Text_Unknown1 = new wxStaticText(Tab, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		Text_Unknown2 = new wxStaticText(Tab, wxID_ANY, " Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		Text_Unknown3 = new wxStaticText(Tab, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		Text_Unknown4 = new wxStaticText(Tab, wxID_ANY, " Unknown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		Text_Unknown5 = new wxStaticText(Tab, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
		Name = new TextCtrl_String(Tab, "0", NULL, 30);
		ID = new TextCtrl_Long(Tab, "0", NULL);
		Palette = new TextCtrl_Long(Tab, "0", NULL);
		ColorL = new TextCtrl_Long(Tab, "0", NULL);
		MinimapColor = new TextCtrl_Long(Tab, "0", NULL);
		Unknown1 = new TextCtrl_Long(Tab, "0", NULL);
		Unknown2 = new TextCtrl_Long(Tab, "0", NULL);
		Unknown3 = new TextCtrl_Long(Tab, "0", NULL);
		Unknown4 = new TextCtrl_Long(Tab, "0", NULL);
		Unknown5 = new TextCtrl_Long(Tab, "0", NULL);

		Buttons->Add(Add, 1, wxEXPAND);
		Buttons->Add(Insert, 1, wxEXPAND);
		Buttons->Add(Delete, 1, wxEXPAND);
		Buttons->Add(Copy, 1, wxEXPAND);
		Buttons->Add(Paste, 1, wxEXPAND);
		Buttons->Add(PasteInsert, 1, wxEXPAND);

		Colors->Add(Search, 0, wxEXPAND);
		Colors->Add(Search_R, 0, wxEXPAND);
		Colors->Add(-1, 2);
		Colors->Add(List, 1, wxEXPAND);
		Colors->Add(-1, 2);
		Colors->Add(Buttons, 0, wxEXPAND);

		ListArea->Add(-1, 10);
		ListArea->Add(Colors, 1, wxEXPAND);
		ListArea->Add(-1, 10);

		Holder_Name->Add(Text_Name, 0, wxEXPAND);
		Holder_Name->Add(Name, 1, wxEXPAND);
		Holder_ID->Add(Text_ID, 0, wxEXPAND);
		Holder_ID->Add(ID, 1, wxEXPAND);
		Holder_Palette->Add(Text_Palette, 0, wxEXPAND);
		Holder_Palette->Add(Palette, 1, wxEXPAND);
		Holder_Color->Add(Text_Color, 0, wxEXPAND);
		Holder_Color->Add(ColorL, 1, wxEXPAND);
		Holder_MinimapColor->Add(Text_MinimapColor, 0, wxEXPAND);
		Holder_MinimapColor->Add(MinimapColor, 1, wxEXPAND);
		Holder_Unknown1->Add(Text_Unknown1, 0, wxEXPAND);
		Holder_Unknown1->Add(Unknown1, 1, wxEXPAND);
		Holder_Unknown2->Add(Text_Unknown2, 0, wxEXPAND);
		Holder_Unknown2->Add(Unknown2, 1, wxEXPAND);
		Holder_Unknown3->Add(Text_Unknown3, 0, wxEXPAND);
		Holder_Unknown3->Add(Unknown3, 1, wxEXPAND);
		Holder_Unknown4->Add(Text_Unknown4, 0, wxEXPAND);
		Holder_Unknown4->Add(Unknown4, 1, wxEXPAND);
		Holder_Unknown5->Add(Text_Unknown5, 0, wxEXPAND);
		Holder_Unknown5->Add(Unknown5, 1, wxEXPAND);

		Holder_UnknownArea->Add(Holder_Unknown1, 0, wxEXPAND);
		Holder_UnknownArea->Add(-1, 5);
		Holder_UnknownArea->Add(Holder_Unknown2, 0, wxEXPAND);
		Holder_UnknownArea->Add(-1, 5);
		Holder_UnknownArea->Add(Holder_Unknown3, 0, wxEXPAND);
		Holder_UnknownArea->Add(-1, 5);
		Holder_UnknownArea->Add(Holder_Unknown4, 0, wxEXPAND);
		Holder_UnknownArea->Add(-1, 5);
		Holder_UnknownArea->Add(Holder_Unknown5, 0, wxEXPAND);

		DataArea->Add(-1, 10);
		DataArea->Add(Holder_Name, 0, wxEXPAND);
		DataArea->Add(-1, 5);
		DataArea->Add(Holder_ID, 0, wxEXPAND);
		DataArea->Add(-1, 5);
		DataArea->Add(Holder_Palette, 0, wxEXPAND);
		DataArea->Add(-1, 5);
		DataArea->Add(Holder_Color, 0, wxEXPAND);
		DataArea->Add(-1, 5);
		DataArea->Add(Holder_MinimapColor, 0, wxEXPAND);
		DataArea->Add(-1, 5);
		DataArea->Add(Holder_UnknownArea, 0, wxEXPAND);

		Main->Add(10, -1);
		Main->Add(ListArea, 1, wxEXPAND);
		Main->Add(10, -1);
	//	Main->Add(-1, -1, 3, wxEXPAND);
		Main->Add(DataArea, 1, wxEXPAND);
		Main->AddStretchSpacer(2);
		Main->Add(10, -1);

		if(IDFix)
		ID->Enable(false);

		Tab->SetSizer(Main);
	}

	~TabColors()
	{
		Tab->Destroy();
	}

	wxPanel * Tab;
	wxBoxSizer * Main;
	wxBoxSizer * ListArea;
	wxStaticBoxSizer * Colors;
	wxTextCtrl * Search;
	wxTextCtrl * Search_R;
	wxListBox * List;
	wxGridSizer * Buttons;
	wxButton * Add;
	wxButton * Insert;
	wxButton * Delete;
	wxButton * Copy;
	wxButton * Paste;
	wxButton * PasteInsert;

	wxBoxSizer * DataArea;
	wxBoxSizer * Holder_Name;
	wxBoxSizer * Holder_ID;
	wxBoxSizer * Holder_Palette;
	wxBoxSizer * Holder_Color;
	wxBoxSizer * Holder_MinimapColor;
	wxBoxSizer * Holder_UnknownArea;
	wxBoxSizer * Holder_Unknown1;
	wxBoxSizer * Holder_Unknown2;
	wxBoxSizer * Holder_Unknown3;
	wxBoxSizer * Holder_Unknown4;
	wxBoxSizer * Holder_Unknown5;
	wxStaticText * Text_Name;
	wxStaticText * Text_ID;
	wxStaticText * Text_Palette;
	wxStaticText * Text_Color;
	wxStaticText * Text_MinimapColor;
	wxStaticText * Text_Unknown1;
	wxStaticText * Text_Unknown2;
	wxStaticText * Text_Unknown3;
	wxStaticText * Text_Unknown4;
	wxStaticText * Text_Unknown5;
	TextCtrl_String * Name;
	TextCtrl_Long * ID;
	TextCtrl_Long * Palette;
	TextCtrl_Long * ColorL;
	TextCtrl_Long * MinimapColor;
	TextCtrl_Long * Unknown1;
	TextCtrl_Long * Unknown2;
	TextCtrl_Long * Unknown3;
	TextCtrl_Long * Unknown4;
	TextCtrl_Long * Unknown5;

};
