#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <WS2tcpip.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class framework
{
public:
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	void SetColor(int ForgC)
	{
		WORD wColor;

		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;


		if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
		{

			wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
			SetConsoleTextAttribute(hStdOut, wColor);
		}
		return;
	}
	void gotoxy(int x, int y)
	{
		COORD c;
		c.X = x;
		c.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	}
	void frame(void)
	{

		int i;
		for (i = 0; i < 390; i++)
		{
			if (i == 45)
			{
				gotoxy(53, 4);
				printf("%c", 186);

				for (int j = 0; j < 37; j++)
				{
					gotoxy(i, j + 4);
					printf("%c", 186);

				}
			}
			if (i < 158)
			{
				gotoxy(i, 1);
				printf("%c", 205);
				gotoxy(i, 4);
				printf("%c", 205);

			}
			else if (i == 158)
			{
				gotoxy(i, 1);
				printf("%c", 187);
				gotoxy(i, 4);
				printf("%c", 205);
			}
			else if (i == 159)
			{
				for (int s = 0; s < 10; s++)
				{
					gotoxy(i - 1, s + 2);
					printf("%c", 186);

				}

			}
			else if (i > 158 && i < 190)
			{
				gotoxy(158, i - 149);
				printf("%c", 186);
			}
			else if (i == 190)
			{
				gotoxy(158, i - 150);
				printf("%c", 188);
			}
			else if (i > 190 && i < 349)
			{
				gotoxy(348 - i, 40);
				printf("%c", 205);

			}
			else if (i == 349)
			{
				gotoxy(349 - i, 40);
				printf("%c", 200);
			}
			else if (i > 349 && i < 389)
			{
				gotoxy(0, 389 - i);
				printf("%c", 186);
			}
			else
			{
				gotoxy(0, 1);
				printf("%c", 201);
			}
		}
	}
	void fullscreen(void)
	{
		keybd_event(VK_MENU, 0x38, 0, 0);
		keybd_event(VK_RETURN, 0x1c, 0, 0);
		keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	}
	void fontsize(int a, int b) {
		PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
		lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
		GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
		lpConsoleCurrentFontEx->dwFontSize.X = a;
		lpConsoleCurrentFontEx->dwFontSize.Y = b;
		SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
	}
};

void receive()
{

	string ipAddress = "127.0.0.1";			// IP Address of the server
	int port = 54000;						// Listening port # on the server
	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	char buf[4096];
	while (true)
	{
		// Wait for response
		ZeroMemory(buf, 4096);
		int bytesReceived = recv(sock, buf, 4096, 0);
		if (bytesReceived > 0)
		{
			cout << "\t\t" << string(buf, 0, bytesReceived) << endl;
		}
	}
	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}
void sen()
{
	string ipAddress = "127.0.0.1";			// IP Address of the server
	int port = 54000;						// Listening port # on the server
	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	string user;
	cin.get();
	cout << "\t\t\t\t\t\t\t" << "Enter the username:";
	getline(cin, user);
	ostringstream ss;
	ss << "\t\t\t\t" << user << " has joined the chat.\n";
	string str = ss.str();
	int a = send(sock, str.c_str(), str.size() + 1, 0);
	string userInput;
	do
	{
		time_t my_time = time(NULL);
		char timec[2399];
		ctime_s(timec, sizeof timec, &my_time);

		// Prompt the user for some text
		cout << ">";
		getline(cin, userInput);

		if (userInput.size() > 0)		// Make sure the user has typed in something
		{
			// Send the text
			ostringstream ss;
			ss << "\t\t\t\t" << user << ":" << userInput << "\t\t" << timec;
			string strOut = ss.str();
			int a = send(sock, strOut.c_str(), strOut.size() + 1, 0);
		}

	} while (userInput.compare("terminate") != 0);
	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
	exit(0);
}

int main()
{
	//client c1;
	framework f;
	f.fullscreen();
	f.SetColor(2);
	f.frame();
	f.fontsize(10, 18);
	std::thread rece(receive);
	std::thread se(sen);
	rece.join();
	se.join();
	return 0;
}