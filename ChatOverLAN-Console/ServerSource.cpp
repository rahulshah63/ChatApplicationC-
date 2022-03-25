#include <iostream>
#include <ws2tcpip.h>
#include <sstream>
#include <fstream>
#include <ctime> 
#pragma comment (lib,"ws2_32.lib")

using namespace std;

int main()
{
	// Initialiizing Winsock

	WSADATA wsDATA;

	int wsOK = WSAStartup(MAKEWORD(2, 2), &wsDATA);
	if (wsOK != 0)
	{
		cerr << "Can't Initialize winsock!" << endl;
		return 0;
	}

	//Creating a socket

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Socket Couldn't Be Created." << endl;
		return 0;
	}

	// Binding an ip address and port to the socket

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; //coould also use inet_pton 

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//Tell wisock that the socket is for listening

	listen(listening, SOMAXCONN);

	fd_set master;
	FD_ZERO(&master);

	FD_SET(listening, &master);

	while (true)
	{
		fd_set copy = master;

		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];
			if (sock == listening)
			{
				//Accept a new connection
				SOCKET client = accept(listening, nullptr, nullptr);

				//Add the new connection to the list of connected client
				FD_SET(client, &master);

				//Send a welcome message to the connected client
				std::string welcomeMsg = "\n\n\t\t\t\t\t\tWelcome to the awesome client server\r\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);

			}
			else
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				//Receive Message
				int bytesreceived = recv(sock, buf, 4096, 0);
				cout << buf;
				if (bytesreceived <= 0)
				{
					//Drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					//Send Message to other clients
					for (int i = 0; i < master.fd_count; i++)
					{
						SOCKET outSock = master.fd_array[i];
						if (outSock != listening && outSock != sock)
						{
							ostringstream ss;
							fstream fil;
							fil.open("computer.txt", ios::app);
							time_t my_time = time(NULL);
							char time[2399];
							ctime_s(time, sizeof time, &my_time);
							fil << buf << "\t\t\t" << time << endl;
							fil.close();

							ss << buf << "\r";
							string strOut = ss.str();
							send(outSock, strOut.c_str(), strOut.size() + 1, 0);

						}
					}
				}
			}
		}
	}

	//Cleanup Winsock
	WSACleanup();
	system("pause");
	return 0;
}