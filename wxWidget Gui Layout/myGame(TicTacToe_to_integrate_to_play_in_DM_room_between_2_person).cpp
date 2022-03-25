#include "myGame.h"

myGame::myGame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxPoint(30, 30), wxSize(617, 684))   //Parameter of wxwidget window
{
	SetBackgroundColour(wxColour(0, 0, 0));
	myMenuBar = new wxMenuBar;   //Creating a menubar at top
	file = new wxMenu;           //creating a 'File' as Menuitem
	help = new wxMenu;           //creating 'Help' as Menuitem
	wxFont font(100, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);   //Increasing parameter of X and O
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			button[i][j] = new wxButton(this, 10000 + (j * 3 + i), "", wxPoint(10+a, 10+b), wxSize(180, 180));  //Creating a 3 * 3 matrix of Button
			button[i][j]->SetFont(font);
			a+= 200;
			Connect(10000 + (j * 3 + i), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(myGame::OnMouseClick));  //Binding event on clicking a button
		}
		b += 200;
		a = 0;
	}
	myMenuBar->Append(file, "&FILE");  //Adding 'File' in Menubar
	myMenuBar->Append(help, "&HELP");  //Adiing 'Help' in Menubar

	quit = new wxMenuItem(file, wxID_EXIT, "&Quit...\tCtrl-Q");   
	file->Append(wxID_NEW, wxT("&New Game \tCtrl-N"));             //Adding New game in File tab
	file->AppendSeparator();                                       
	file->Append(quit);                                            //Adding 'Quit' in File tab

	help->Append(wxID_HELP, "&Guide...\tCtrl-G", "How to Play");    //Adding 'Guide' in Help tab

	SetMenuBar(myMenuBar);
	CreateStatusBar(1);   //Creating Statusbar at bottom

	SetStatusText(wxT("\tWelcome to TIC TAC TOE GAME !!!\t\t\tPlayer 1 : X\t\t\tPlayer 2 : O"), 0);
	
	//Binding Various Event
	Connect(wxEVT_PAINT, wxPaintEventHandler(myGame::OnPaint));
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(myGame::OnQuit));
	Connect(wxID_HELP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(myGame::OnGuide));
	Connect(wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(myGame::OnNew));
	Centre();
}

//On Mouse clicking or keyboard inputing, handelling for menubar
void myGame::OnNew(wxCommandEvent& event)             
{
	Close(true);
	myGame* frame = new myGame(wxT("TIC TAC TOE"));    //restarting Game  Ctrl+N
	frame->Show(true);
	event.Skip();
}
void myGame::OnQuit(wxCommandEvent& event)             //Ctrl + Q
{
	Close(true);
	event.Skip();
}

void myGame::OnGuide(wxCommandEvent& event)            //Ctrl + G
{
	//display guide to play
	wxMessageBox(wxT("\n\n\tYou have to match\n\t A. Either one of 3 ROWS  \n\t B. OR  one of 3 COLOUMNS \n\t C. OR one of 2 DIAGONALS."), wxT("GUIDE TO PLAY   :)"));
	event.Skip();
}


// Drawing outline for a board

void myGame::OnPaint(wxPaintEvent& event)  //DC Design event handelling for board
{

	wxPaintDC dc(this);
	wxColour white;
	dc.DrawRectangle(0,0,600,600);   //Setting backround white
	dc.SetPen(wxPen(wxColor(0,0,0), 5));  //for bold black boundary
	wxCoord x1 = 200, y1 = 0;
	wxCoord x2 = 200, y2 = 600;
	for (int i = 0; i < 2; i++)
	{
		dc.DrawLine(x1, y1, x2, y2);   //Drawing lines for border
		dc.DrawLine(y1, x1, y2, x2);
		x1 *= 2;   
		x2 *= 2;
	}
}

void myGame::OnMouseClick(wxCommandEvent& event)        	// TODO: Implementing OnGameClick
{
	wxButton *b1 = (wxButton *)event.GetEventObject();      //Sensing the Button
	int player1 = 1;                                        //X
	int player2 = 2;                                        //O

	if (b1->GetLabel() == "")   //Checking if the spot is empty or not so as to avoid overwritting
	{

		switch (playerTurn)     //By Default it is 'X'   i.e Player 1
		{
		case 'X':
			b1->SetLabel("X");              //Setting label
			if (gameWin(player1) == true)   //if wins
			{
				//wxSleep(1);
				 answer=wxMessageBox(wxT("Congratulation !!!\n\n\tPlayer 1 has won!!\n\n\tDo You Want To Play Again ???"), wxT("Tic Tac Toe"), wxYES | wxNO, this);
				if (answer==wxYES)           //Asking to replay the Game
				{
					Close(true);
					myGame* frame = new myGame(wxT("TIC TAC TOE"));  //Creation of wxwidget window
					frame->Show(true);
					event.Skip();
				}
				else
					Close(true);
			}
			else
			{
				if(gameDraw() == true)   //Check if is a Draw Match or not
				{
					answer = wxMessageBox(wxT("Match DRAW !!!\n\n\tDo You Want To Play Again ???"), wxT("Tic Tac Toe"), wxYES | wxNO, this);
					if (answer == wxYES)   //Asking to Replay the game
					{
						Close(true);
						myGame* frame = new myGame(wxT("TIC TAC TOE"));  //Creation of wxwidget window
						frame->Show(true);
						event.Skip();
					}
					else
						Close(true);
				}
				else
				{
					playerTurn = 'O';                                   // Updating Player for next turn
					SetStatusText(wxT("\tPlayer 2 (O's) Turn"), 0);
				}
			}
			break;
		case 'O':
			b1->SetLabel("O");

			if (gameWin(player2) == true) 
			{
				answer=wxMessageBox(wxT("Congratulation !!!\n\n\tPlayer 2 has won!!\n\n\tDo You Want To Play Again ???"), wxT("Tic Tac Toe"), wxYES | wxNO, this);
				if (answer==wxYES)
				{
					Close(true);
					myGame* frame = new myGame(wxT("TIC TAC TOE"));  
					frame->Show(true);
					event.Skip();
				}
				else
					Close(true);
					
			}
	
			else
			{
				if(gameDraw() == true)
				{
					answer = wxMessageBox(wxT("Match DRAW !!!\n\n\tDo You Want To Play Again ???"), wxT("Tic Tac Toe"), wxYES | wxNO, this);
					if (answer == wxYES)
					{
						Close(true);
						myGame* frame = new myGame(wxT("TIC TAC TOE"));  //Creation of wxwidget window
						frame->Show(true);
						event.Skip();
					}
					else
						Close(true);
				}
				else
				{
					playerTurn = 'X';
					SetStatusText(wxT("\tPlayer 1 (X's) Turn"), 0);
				}
			}
			break;
		}
	}
	event.Skip();
}

bool myGame::gameWin(int p)    //To Check who wins the Match
{
	char temp;
	if (p == 1) {
		temp = 'X';
	}

	else if (p == 2) {
		temp = 'O';
	}
	//Checking all possible Wins
	while (button[0][0]->GetLabel() == temp && button[0][1]->GetLabel() == temp && button[0][2]->GetLabel() == temp)
	{        
		draw = 1;
		return true;  
	}

	while (button[1][0]->GetLabel() == temp && button[1][1]->GetLabel() == temp && button[1][2]->GetLabel() == temp)
	{
		draw = 2;
		return true;
	}

	while (button[2][0]->GetLabel() == temp && button[2][1]->GetLabel() == temp && button[2][2]->GetLabel() == temp)
	{
		draw = 3; 
		return true;
	}

	while (button[0][0]->GetLabel() == temp && button[1][0]->GetLabel() == temp && button[2][0]->GetLabel() == temp)
	{
		draw = 4; 
		return true;
	}

	while (button[0][1]->GetLabel() == temp && button[1][1]->GetLabel() == temp && button[2][1]->GetLabel() == temp)
	{
		draw = 5; 
		return true;
	}

	while (button[0][2]->GetLabel() == temp && button[1][2]->GetLabel() == temp && button[2][2]->GetLabel() == temp)
	{
		draw = 6; 
		return true;
	}

	while (button[0][0]->GetLabel() == temp && button[1][1]->GetLabel() == temp && button[2][2]->GetLabel() == temp)
	{
		draw = 7; 
		return true;
	}

	while (button[2][0]->GetLabel() == temp && button[1][1]->GetLabel() == temp && button[0][2]->GetLabel() == temp)
	{
		draw = 8; 
		return true;
	}

}

bool myGame::gameDraw()    //To Check if it is a draw Match
{
	while (button[0][0]->GetLabel() != "" && button[0][1]->GetLabel() != "" && button[0][2]->GetLabel() != "" && button[1][0]->GetLabel() != "" && button[1][1]->GetLabel() != "" &&
		button[1][2]->GetLabel() != "" &&button[2][0]->GetLabel() != "" && button[2][1]->GetLabel() != "" && button[2][2]->GetLabel() != "")
		return true;

	return false;
}

/*
void myGame::OnPaint2(wxPaintEvent& event)  //Winning Design 
{
	wxPaintDC dc(this);
	dc.SetPen(wxPen(wxColor(0, 0, 0), 5));
	if(draw=1)
	{
		dc.DrawLine(0,100,600,100);
	}
	if (draw = 2)
	{
		dc.DrawLine(0,300,600,300);
	}
	if (draw = 3)
	{
		dc.DrawLine(0,500,600,500);
	}
	if (draw = 4)
	{
		dc.DrawLine(100,0,100,600);
	}
	if (draw = 5)
	{
		dc.DrawLine(300,0,300,600);
	}
	if (draw = 6)
	{
		dc.DrawLine(500,0,500,600);
	}
	if (draw = 7)
	{
		dc.DrawLine(0,0,600,600);
	}
	if (draw = 8)
	{
		dc.DrawLine(0,600,600,0);
	}
	draw = 0;
	event.Skip();
}

*/