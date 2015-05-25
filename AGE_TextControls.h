#include "Common.h"

//	The purpose of these custom text controls is that you get specified error messages
//	when your mouse cursor focus gets off from a data edit box.

#ifndef AGE_TextControls_h
#define AGE_TextControls_h

class AGELinkedBox
{
public:
	virtual void Update(int)=0;
};

class AGETextCtrl: public wxTextCtrl
{
public:
	AGETextCtrl(wxWindow *parent, int window, wxString value, int width):
	wxTextCtrl(parent, wxID_ANY, value, wxDefaultPosition, wxSize(width, 20), wxTE_PROCESS_ENTER){}

	void OnKillFocus(wxFocusEvent &Event){SaveEdits(); Event.Skip();}
	void OnEnter(wxCommandEvent &Event){SaveEdits(true);}
	virtual int SaveEdits(bool forced = false)=0;
	virtual void Update()=0;
	void resize(int size){container.resize(size);}
	bool BatchCheck(string &value, short &batchMode)
	{
		if(value.size() < 3) return false;
		switch((char)value[1])
		{
			case '+': batchMode = 1; value = value.substr(2); return true;
			case '-': batchMode = 2; value = value.substr(2); return true;
			case '*': batchMode = 3; value = value.substr(2); return true;
			case '/': batchMode = 4; value = value.substr(2); return true;
			case '%': batchMode = 5; value = value.substr(2); return true;
			default: return false;
		}
	}

	AGELinkedBox *LinkedBox; // These are for check and combo boxes.
	static const wxString BATCHWARNING, BWTITLE, IETITLE;
	vector<void*> container;
	// Make these window specific
	static vector<bool> hexMode, accurateFloats;
	static vector<int> unSaved, fileLoaded;
	int curFileLoaded, window;
};

class TextCtrl_DLL: public wxTextCtrl
{
public:
	TextCtrl_DLL(wxWindow *parent, wxSize dimensions):
	wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, dimensions, wxTE_MULTILINE | wxTE_PROCESS_ENTER){}

	int index;
};

class TextCtrl_Byte: public AGETextCtrl
{
public:
	TextCtrl_Byte(int window, wxWindow *parent, bool petit = false):
	AGETextCtrl(parent, window, "", petit ? 30 : 50)
	{
		this->window = window;
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(255, 235, 215));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));	// Must-have
		Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_Byte::OnEnter));
	}
	int SaveEdits(bool forced = false);
	void Update();
};

class TextCtrl_UByte: public AGETextCtrl
{
public:
	TextCtrl_UByte(int window, wxWindow *parent):
	AGETextCtrl(parent, window, "", 50)
	{
		this->window = window;
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(255, 235, 215));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_UByte::OnKillFocus));
		Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_UByte::OnEnter));
	}
	int SaveEdits(bool forced = false);
	void Update();
};

class TextCtrl_Float: public AGETextCtrl
{
public:
	TextCtrl_Float(int window, wxWindow *parent, bool petit = false):
	AGETextCtrl(parent, window, "", petit ? 70 : 100)
	{
		this->window = window;
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(255, 225, 255));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
		Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_Float::OnEnter));
	}
	int SaveEdits(bool forced = false);
	void Update();
};

class TextCtrl_Long: public AGETextCtrl
{
public:
	TextCtrl_Long(int window, wxWindow *parent, bool petit = false):
	AGETextCtrl(parent, window, "", petit ? 50 : 100)
	{
		this->window = window;
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(215, 255, 255));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
		Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_Long::OnEnter));
	}
	int SaveEdits(bool forced = false);
	void Update();
};

class TextCtrl_Short: public AGETextCtrl
{
public:
	TextCtrl_Short(int window, wxWindow *parent, bool petit = false):
	AGETextCtrl(parent, window, "", petit ? 50 : 100)
	{
		this->window = window;
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(210, 230, 255));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
		Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_Short::OnEnter));
	}
	int SaveEdits(bool forced = false);
	void Update();
};

class TextCtrl_UShort: public AGETextCtrl
{
public:
	TextCtrl_UShort(int window, wxWindow *parent):
	AGETextCtrl(parent, window, "", 100)
	{
		this->window = window;
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(210, 230, 255));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_UShort::OnKillFocus));
		Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_UShort::OnEnter));
	}
	int SaveEdits(bool forced = false);
	void Update();
};

class TextCtrl_String: public AGETextCtrl
{
public:
	TextCtrl_String(int window, wxWindow *parent, unsigned short CLength = 0):
	AGETextCtrl(parent, window, "", 0)
	{
		this->window = window;
		MaxSize = CLength;
		SetBackgroundColour(wxColour(220, 255, 220));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_String::OnKillFocus));
		Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_String::OnEnter));
	}
	int SaveEdits(bool forced = false);
	void Update();
	void SetMaxSize(unsigned short Size){MaxSize = Size;}
	unsigned short MaxSize;
};

#endif
