#include"wx/splitter.h"
#include"myGame.h"
#include <wx/statline.h>
#include"wx/socket.h"
#include<string>
class myChatScreen : public wxFrame
{
public:
	myChatScreen(const wxString& title);
	myGame* frame = nullptr;
	//void FunConnect(wxCommandEvent &evt);
	void OnSocketEvent(wxSocketEvent &evt);
private:
	void OnMenuSplit(wxCommandEvent& evt);
	void OnUnsplit(wxSplitterEvent& evt);
	void OnGame(wxCommandEvent& event);
	void OnSend(wxCommandEvent& event);
	void OnGlobalSend(wxCommandEvent& event);
	void OnLogOut(wxCommandEvent& event);
	
private:
	bool sendmsg = false;
	bool Gsendmsg = false;
	bool recmsg = false;
	bool Grecmsg = false;
	char buffer[4096];
	wxSocketClient *Socket;
	//wxSocketServer *m_server;
	wxMenuBar* menuBar;
	wxMenu* viewMenu;
	wxMenuItem* quit; 
	wxSplitterWindow* splitterWindow;
	wxPanel*panel1, *panel2;
	wxStaticText *info, *info2, *send, *sendto;
	wxButton* btn[3];
	wxButton *sendbtn, *btn2;
	wxTextCtrl* textCtrl1, *textCtrl2;
	//wxStaticLine* line;
	wxComboBox* cb;
	wxListBox *lb, *lb1;
	wxBoxSizer *panel1Sizer1, *panel1Sizer2, *panel1Sizer3, *panel1Sizer4, *panel1Sizer5, *panel1Sizer6, *panel2Sizer1, *panel2Sizer2, *panel2Sizer3, *panel2Sizer4, *panel2Sizer5;
	wxDECLARE_EVENT_TABLE();

	enum
	{
		wxID_SEND = 36
	};
};

enum
{
	wxID_GLOBALSEND =63
};



enum
{
	wxID_SOCKET
};


const int SplitMenuID = 1;
const int SplitterWindowID = 2;