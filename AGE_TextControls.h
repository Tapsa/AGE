#include "Common.h"
using std::string;
using std::vector;
using boost::lexical_cast;
using boost::bad_lexical_cast;

//	The purpose of these custom text controls is that you get specified error messages
//	when your mouse cursor focus gets off from a data edit box.

#ifndef AGE_TextControls_h
#define AGE_TextControls_h

class AGELinkedBox
{
	public:
	virtual void Update(long)=0;
};

class AGETextCtrl: public wxTextCtrl
{
	public:
	AGETextCtrl(wxWindow *parent, wxString value):
	wxTextCtrl(parent, wxID_ANY, value, wxDefaultPosition, wxSize(0, 20)){}

	virtual void OnKillFocus(wxFocusEvent&)=0;
	virtual bool SaveEdits()=0;
	bool BatchCheck(wxString &value, short &batchMode)
	{
		if(value.size() < 3) return false;
		switch(value[1])
		{
			case '+': batchMode = 1; value = value.substr(2); return true;
			case '-': batchMode = 2; value = value.substr(2); return true;
			case '*': batchMode = 3; value = value.substr(2); return true;
			case '/': batchMode = 4; value = value.substr(2); return true;
			default: return false;
		}
	}
	template <class C, class V>
	void BatchSave(C &container, short batchMode, V casted)
	{
		for(auto &pointer: container)
		{
			switch(batchMode)
			{
				case 1: *pointer += casted; break;
				case 2: *pointer -= casted; break;
				case 3: *pointer *= casted; break;
				case 4: *pointer /= casted; break;
			}
		}
	}

	AGELinkedBox *LinkedBox; // These are for check and combo boxes.
	static const wxString BATCHWARNING;
};

class TextCtrl_Byte: public AGETextCtrl
{
	public:
	TextCtrl_Byte(wxWindow *parent):
	AGETextCtrl(parent, "0")
	{
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(255, 235, 215));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));	// Must-have
	}

	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();
	void resize(int size){container.resize(size);}

	vector<char*> container;
};

class TextCtrl_UByte: public AGETextCtrl
{
	public:
	TextCtrl_UByte(wxWindow *parent):
	AGETextCtrl(parent, "0")
	{
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(255, 235, 215));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_UByte::OnKillFocus));
	}

	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();
	void resize(int size){container.resize(size);}

	vector<unsigned char*> container;
};

class TextCtrl_Float: public AGETextCtrl
{
	public:
	TextCtrl_Float(wxWindow *parent):
	AGETextCtrl(parent, "0")
	{
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(255, 225, 255));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
	}

	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();
	void resize(int size){container.resize(size);}

	vector<float*> container;
};

class TextCtrl_Long: public AGETextCtrl
{
	public:
	TextCtrl_Long(wxWindow *parent):
	AGETextCtrl(parent, "0")
	{
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(215, 255, 255));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
	}

	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();
	void resize(int size){container.resize(size);}

	vector<int32_t*> container;
};

class TextCtrl_Short: public AGETextCtrl
{
	public:
	TextCtrl_Short(wxWindow *parent):
	AGETextCtrl(parent, "0")
	{
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(210, 230, 255));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
	}

	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();
	void resize(int size){container.resize(size);}

	vector<int16_t*> container;
};

class TextCtrl_UShort: public AGETextCtrl
{
	public:
	TextCtrl_UShort(wxWindow *parent):
	AGETextCtrl(parent, "0")
	{
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(210, 230, 255));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_UShort::OnKillFocus));
	}

	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();
	void resize(int size){container.resize(size);}

	vector<uint16_t*> container;
};

class TextCtrl_String: public AGETextCtrl
{
	public:
	TextCtrl_String(wxWindow *parent, int16_t CLength = -1):
	AGETextCtrl(parent, "")
	{
		MaxSize = CLength;
		SetBackgroundColour(wxColour(220, 255, 220));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_String::OnKillFocus));
	}

	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();
	void resize(int size){container.resize(size);}
	void SetMaxSize(int16_t Size){MaxSize = Size;}

	int16_t MaxSize;
	vector<string*> container;
};

#endif
