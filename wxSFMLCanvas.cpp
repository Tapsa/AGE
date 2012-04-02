

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "wxSFMLCanvas.hpp"

// Platform-specific includes
#ifdef __WXGTK__
    #include <gdk/gdkx.h>
    #include <gtk/gtk.h>
    #include <wx/gtk/win_gtk.h>
#endif


////////////////////////////////////////////////////////////
// Event table
////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(wxSFMLCanvas, wxControl)
    EVT_IDLE(wxSFMLCanvas::OnIdle)
    EVT_PAINT(wxSFMLCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(wxSFMLCanvas::OnEraseBackground)
END_EVENT_TABLE()


////////////////////////////////////////////////////////////
/// Construct the wxSFMLCanvas
////////////////////////////////////////////////////////////
wxSFMLCanvas::wxSFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style) :
wxControl(Parent, Id, Position, Size, Style)
{
    #ifdef __WXGTK__

        // GTK implementation requires to go deeper to find the low-level X11 identifier of the widget
        gtk_widget_realize(m_wxwindow);
        gtk_widget_set_double_buffered(m_wxwindow, false);
        GdkWindow* Win = GTK_PIZZA(m_wxwindow)->bin_window;
        XFlush(GDK_WINDOW_XDISPLAY(Win));
        sf::RenderWindow::Create(GDK_WINDOW_XWINDOW(Win));

    #else

        // Tested under Windows XP only (should work with X11 and other Windows versions - no idea about MacOS)
        sf::RenderWindow::Create(GetHandle());
    
    #endif
}


////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
wxSFMLCanvas::~wxSFMLCanvas()
{
    // Nothing to do...
}


////////////////////////////////////////////////////////////
/// Notification for the derived class that moment is good
/// for doing its update and drawing stuff
////////////////////////////////////////////////////////////
void wxSFMLCanvas::OnUpdate()
{
    // Nothing to do by default...
}


////////////////////////////////////////////////////////////
/// Called when the control is idle - we can refresh our
/// SFML window
////////////////////////////////////////////////////////////
void wxSFMLCanvas::OnIdle(wxIdleEvent&)
{
    // Send a paint message when the control is idle, to ensure maximum framerate
    Refresh();
}


////////////////////////////////////////////////////////////
/// Called when the control is repainted - we can display our
/// SFML window
////////////////////////////////////////////////////////////
void wxSFMLCanvas::OnPaint(wxPaintEvent&)
{
    // Make sure the control is able to be repainted
    wxPaintDC Dc(this);

    // Let the derived class do its specific stuff
    OnUpdate();

    // Display on screen
    Display();
}


////////////////////////////////////////////////////////////
/// Called when the control needs to draw its background
////////////////////////////////////////////////////////////
void wxSFMLCanvas::OnEraseBackground(wxEraseEvent&)
{
    // Don't do anything. We intercept this event in order to prevent the
    // parent class to draw the background before repainting the window,
    // which would cause some flickering
}
