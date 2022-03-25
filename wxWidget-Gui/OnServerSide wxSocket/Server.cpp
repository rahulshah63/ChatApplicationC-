
#include "wx/wx.h"

#include "wx/socket.h"

// this example is currently written to use only IP or only IPv6 sockets, it
// should be extended to allow using either in the future
#if wxUSE_IPV6
typedef wxIPV6address IPaddress;
#else
typedef wxIPV4address IPaddress;
#endif

class MyApp : public wxApp
{
public:

	virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
	// ctor(s)
	MyFrame(const wxString& title);
	~MyFrame();
	// event handlers (these functions should _not_ be virtual)
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnServerEvent(wxSocketEvent& event);
	void OnSocketEvent(wxSocketEvent& event);
private:

	wxSocketServer* sock;
	wxTextCtrl* txtRx;
	int numClients;
	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();
};

// IDs for the controls and the menu commands
enum
{
	ID_TXTRX = 101,
	SOCKET_ID,
	SERVER_ID,
	// menu items
	Minimal_Quit = wxID_EXIT,

	Minimal_About = wxID_ABOUT
};

// event tables and other macros for wxWidgets
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(Minimal_Quit, MyFrame::OnQuit)
EVT_MENU(Minimal_About, MyFrame::OnAbout)
EVT_SOCKET(SOCKET_ID, MyFrame::OnSocketEvent)
EVT_SOCKET(SERVER_ID, MyFrame::OnServerEvent)
wxEND_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	MyFrame* frame = new MyFrame("wxWidgets TCP Server");
	frame->Show(true);
	return true;
}

// frame constructor
MyFrame::MyFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(390, 280),
		wxDEFAULT_FRAME_STYLE^ wxRESIZE_BORDER)
{
	// create a menu bar
	wxMenu* fileMenu = new wxMenu;

	// the "About" item should be in the help menu
	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(Minimal_About, "&About\tF1", "Show about dialog");

	fileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");

	// now append the freshly created menu to the menu bar...
	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(helpMenu, "&Help");

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);



	// create a status bar just for fun (by default with 1 pane only)
	CreateStatusBar(2);
	SetStatusText("TCP server using wxWidgets");
 // wxUSE_STATUSBAR
	txtRx = new wxTextCtrl(this, ID_TXTRX, wxT(""), wxPoint(5, 5),
		wxSize(365, 125), wxTE_MULTILINE);

	// Create the address - defaults to localhost:0 initially
	IPaddress addr;
	addr.AnyAddress();
	addr.Service(3000);
	txtRx->AppendText(wxString::Format(wxT("Creating server at %s:%u \n")
		, addr.IPAddress(), addr.Service()));

	// Create the socket
	sock = new wxSocketServer(addr);

	// We use IsOk() here to see if the server is really listening
	if (!sock->IsOk()) {
		txtRx->AppendText(wxString::Format(wxT("Could not listen at the specified port !\n")));
		return;
	}

	IPaddress addrReal;
	if (!sock->GetLocal(addrReal)) {
		txtRx->AppendText(wxString::Format(wxT("ERROR: couldn't get the address we bound to. \n")));
	}
	else {
		txtRx->AppendText(wxString::Format(wxT("Server listening at %s:%u \n"),
			addrReal.IPAddress(), addrReal.Service()));
	}

	// Setup the event handler and subscribe to connection events
	sock->SetEventHandler(*this, SERVER_ID);
	sock->SetNotify(wxSOCKET_CONNECTION_FLAG);
	sock->Notify(true);
	numClients = 0;
}

MyFrame::~MyFrame()
{
	// No delayed deletion here, as the frame is dying anyway
	delete sock;
}

// event handlers
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxString::Format
	( "This IS ServerStation\n" ),
		"About wxWidget socket"
		wxOK | wxICON_INFORMATION,
		this);
}

void MyFrame::OnServerEvent(wxSocketEvent& event)
{
	txtRx->AppendText(wxT("OnServerEvent: "));
	wxSocketBase* sockBase;

	switch (event.GetSocketEvent())
	{
	case wxSOCKET_CONNECTION: txtRx->AppendText(wxT("wxSOCKET_CONNECTION\n")); break;
	default: txtRx->AppendText(wxT("Unexpected event !\n")); break;
	}

	// Accept new connection if there is one in the pending
	// connections queue, else exit. We use Accept(false) for
	// non-blocking accept (although if we got here, there
	// should ALWAYS be a pending connection).

	sockBase = sock->Accept(false);

	if (sockBase)
	{
		IPaddress addr;
		if (!sockBase->GetPeer(addr))
		{
			txtRx->AppendText(wxT("New connection from unknown client accepted.\n"));
		}
		else
		{
			txtRx->AppendText(wxString::Format(wxT("New client connection from %s:%u accepted \n"),
				addr.IPAddress(), addr.Service()));
		}
	}
	else
	{
		txtRx->AppendText(wxT("Error: couldn't accept a new connection \n"));
		return;
	}

	sockBase->SetEventHandler(*this, SOCKET_ID);
	sockBase->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
	sockBase->Notify(true);

	numClients++;
	SetStatusText(wxString::Format(wxT("%d  clients connected"), numClients), 1);
}

void MyFrame::OnSocketEvent(wxSocketEvent& event)
{
	txtRx->AppendText(wxT("OnSocketEvent: "));
	wxSocketBase* sockBase = event.GetSocket();

	// First, print a message
	switch (event.GetSocketEvent())
	{
	case wxSOCKET_INPUT: txtRx->AppendText(wxT("wxSOCKET_INPUT\n")); break;
	case wxSOCKET_LOST: txtRx->AppendText(wxT("wxSOCKET_LOST\n")); break;
	default: txtRx->AppendText(wxT("Unexpected event !\n")); break;
	}

	// Now we process the event
	switch (event.GetSocketEvent())
	{
	case wxSOCKET_INPUT:
	{
		// We disable input events, so that the test doesn't trigger
		// wxSocketEvent again.
		sockBase->SetNotify(wxSOCKET_LOST_FLAG);

		// Receive data from socket and send it back. We will first
		// get a byte with the buffer size, so we can specify the
		// exact size and use the wxSOCKET_WAITALL flag. Also, we
		// disabled input events so we won't have unwanted reentrance.
		// This way we can avoid the infamous wxSOCKET_BLOCK flag.

		sockBase->SetFlags(wxSOCKET_WAITALL);

		// Read the size @ first byte
		unsigned char len;
		sockBase->Read(&len, 1);
		char buf[256]; 
		// Read the message
		wxUint32 lenRd = sockBase->Read(buf, len).LastCount();
		if (!lenRd) {
			txtRx->AppendText(wxT("Failed to read message.\n"));
			return;
		}
		else {
			txtRx->AppendText(wxString::Format(wxT("Read %d bytes.\n"), lenRd));
		}

		txtRx->AppendText(wxString::Format(wxT("Rx: %s \n"), wxString::FromUTF8(buf, len)));
		ZeroMemory(buf, 256);
		// Write it back
		len = 12;
		wxString msg = "MESSAGE SENT!";

		//sockBase->Write(&len, 1);
		sockBase->Write(msg, sizeof(msg));
		txtRx->AppendText("Tx: " + wxString::From8BitData(buf, len) + "\n");
		// Enable input events again.
		sockBase->SetNotify(wxSOCKET_LOST_FLAG | wxSOCKET_INPUT_FLAG);
		break;
	}
	case wxSOCKET_LOST:
	{
		numClients--;

		// Destroy() should be used instead of delete wherever possible,
		txtRx->AppendText(wxT("Deleting socket.\n"));
		sockBase->Destroy();
		break;
	}
	default:;
	}

	SetStatusText(wxString::Format(wxT("%d  clients connected"), numClients), 1);
}

