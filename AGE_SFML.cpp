/* AGE_SFML.cpp */

#include "AGE_SFML.h"

BEGIN_EVENT_TABLE(wxSFMLCanvas, wxControl)
	EVT_IDLE(wxSFMLCanvas::OnIdle)
	EVT_PAINT(wxSFMLCanvas::OnPaint)
	EVT_ERASE_BACKGROUND(wxSFMLCanvas::OnEraseBackground)
END_EVENT_TABLE()
