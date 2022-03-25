#pragma once
#include"wx/wx.h"
#include"wx/menu.h"
//bool login = false;
//All declaration are done here

class myGame : public wxFrame     //Inheriting wxFrame class in myMain
{
private:
	int draw = 0;
	int a = 0, b = 0,answer;
	char playerTurn = 'X';   //Initializing X to Player First
public:
	myGame(const wxString& title);  //for Creation of Window
	void OnPaint(wxPaintEvent& event);  //For Creating layout
	//void OnPaint2(wxPaintEvent& event);
	void  OnMouseClick(wxCommandEvent& event);  //For Sensing Button Click either left clicl or right click
	bool gameWin(int p);    //TO Check Who Wins 
	bool gameDraw();        //To Check If it is Draw Match or Not

	wxMenuBar* myMenuBar;   //For Creating a Menubar at Top
	wxMenu* file;           //'File' Menu Item
	wxMenu* help;           //'Help; Menu Item
	wxMenuItem* quit;       //'Quit' option under File Menu
	wxButton* button[3][3];  //For creating a 3 * 3 Matrix box

	void OnNew(wxCommandEvent& event);    //Making work of 'New' MenuItem
	void OnQuit(wxCommandEvent& event);    //Making work of 'Quit' MenuItem
	void OnGuide(wxCommandEvent& event);    //Making work of 'Guide' MenuItem


};