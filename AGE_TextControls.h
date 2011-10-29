/* AGE_TextControls.h */

#include "wx/wx.h"
#include <string>
using std::string;
#include "boost/lexical_cast.hpp"
using boost::lexical_cast;
using boost::bad_lexical_cast;

//	The purpose of these custom text controls is that you get specified error messages
//	when your mouse cursor focus gets off from a data edit box.

#ifndef TextCtrl_Byte_h
#define TextCtrl_Byte_h

class TextCtrl_Byte : public wxTextCtrl
{
	public:
	
	TextCtrl_Byte(wxWindow*, string, void*);
	
	/* Events */
	
	void OnKillFocus(wxFocusEvent& Event);
	
	/* Member Variables */
	
	void * Container;	// chars and bools (1 byte).
	void * ParentContainer;	//	These are for check and combo boxes.
	bool NoLoadList;
};

#endif

#ifndef TextCtrl_Float_h
#define TextCtrl_Float_h

class TextCtrl_Float : public wxTextCtrl
{
	public:

	TextCtrl_Float(wxWindow*, string, float*);

	/* Events */

	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	float * Container;
	void * ParentContainer;
	bool NoLoadList;
};

#endif

#ifndef TextCtrl_Long_h
#define TextCtrl_Long_h

class TextCtrl_Long : public wxTextCtrl
{
	public:

	TextCtrl_Long(wxWindow*, string, long*);

	/* Events */

	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	long * Container;
	void * ParentContainer;
	bool NoLoadList;
};

#endif

#ifndef TextCtrl_Short_h
#define TextCtrl_Short_h

class TextCtrl_Short : public wxTextCtrl
{
	public:

	TextCtrl_Short(wxWindow*, string, short*);

	/* Events */

	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	short * Container;
	void * ParentContainer;
	bool NoLoadList;
};

#endif

#ifndef TextCtrl_UnShort_h
#define TextCtrl_UnShort_h

class TextCtrl_UnShort : public wxTextCtrl
{
	public:

	TextCtrl_UnShort(wxWindow*, string, unsigned short*);

	/* Events */

	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	unsigned short * Container;
	void * ParentContainer;
	bool NoLoadList;
};

#endif

#ifndef TextCtrl_String_h
#define TextCtrl_String_h

class TextCtrl_String : public wxTextCtrl
{
	public:

	TextCtrl_String(wxWindow*, string, void*, short = -1);

	/* Events */

	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	short Length;
	void * Container;
	bool NoLoadList;
};

#endif
