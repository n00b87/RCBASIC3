#ifndef DRAG_FILES_H_INCLUDED
#define DRAG_FILES_H_INCLUDED

#include <wx/wx.h>
#include <wx/dnd.h>

class rc_dragFileTarget : public wxFileDropTarget
{
public:
    rc_dragFileTarget(wxWindowBase *win) : m_win(win) {}

    virtual bool OnDropFiles(wxCoord x, wxCoord y,
                             const wxArrayString& filenames) override
    {
        wxDropFilesEvent event(wxEVT_DROP_FILES,
                               filenames.size(),
                               wxCArrayString(filenames).Release());
        event.SetEventObject(m_win);
        event.m_pos.x = x;
        event.m_pos.y = y;

        return m_win->HandleWindowEvent(event);
    }

private:
    wxWindowBase * const m_win;

    wxDECLARE_NO_COPY_CLASS(rc_dragFileTarget);
};

#endif // DRAG_FILES_H_INCLUDED
