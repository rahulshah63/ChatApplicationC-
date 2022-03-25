Title: "Chat System Over a Local Network"

This provided project is very simple to compile and run as there is no need of any additional library to be added in order to run this project successfully.

Inside the source code folder, you will find two files : one ServerSource and another ClientSource

Just create a new visual studios project for console application and add the ServerSource.cpp file in 
its Source Files section and run the project in order to start the server.

Now, for the side of the client, follow similar method as for the server including ClientSource.cpp file.
But here in the ClientSource.cpp file, you will need to make some changes as per your network.

Steps:
1. First be sure to connect the server and the client computer in the same Network.
2. Find the ipAddress string in send() and receive() function in ClientSource.cpp and change it to the ipAddress(Ipv4) of the server computer.
3. If you are running the server and client in the same device then keep the ipAdderss string "127.0.0.1" which signifies the local host.
4. First run the server and then run the clients(you are able to connect as many clients as you want).
5. In the client side you will see a message saying "Welcome to awesome client server.", then you press enter to get an option to enter your username.
   After you enter the username then all the clients connected on the server will see a message saying "(username) has joined the chat".
   Now you can chat in this system.To exit the system simply type "terminate" and press enter.

Thank You!
 