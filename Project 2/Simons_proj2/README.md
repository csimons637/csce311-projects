## CSCE 311 Project 2
## Charles Simons - CSCE 311-001

## IPC Demo Using Unix Domain Sockets

# Included Files
    - makefile
    - UDS.h
    - UDS_server.h
    - UDS_client.h
    - text-server.cc
    - text-client.cc
    - ./dat
        - anna_karenina.txt
        - dante.txt
        - lorem_ipsum.txt
    - README.md
    - proj2.pdf
# File Relationships
    - makefile:
        Builds executables (text-server and text-client) and cleans working directory
    - UDS.h: 
        Source header for UDS_server.h and UDS_client.h
        Dictates the system libraries and constructor used by the server and client sockets
    - UDS_server.h:
        Source header file for server socket
        Constructs and modifies socket (sets path, name, read buffer, etc)
        
        Defines:
            + RunServ()
    - UDS_client.h:
        Source header file for client socket
        Constructs and modifies socket (connects to server, sets write buffer, etc)
        Defines the member functions getFileName(const char *) and getSearchTerm(const char *)
        
        Defines:
            + RunClnt()
            + getFileName()
            + getSearchTerm()
    - text-server.cc:
        Source file for text-server executable. Runs the server socket and takes in the socket's path name as a command line argument
    - text-client.cc
        Source file for text-client executable. Runs the client socket and takes in the socket's path name, the file to search, and the search key as command line arguments
        Calls client member functions to set parameters for later use
    - text files:
        Text files to be searched by the server, to find the client's specifed search string
    - proj2.pdf
        Description of project criteria
# File Functionality
    - The .h files provide the constructors and basic logic of the sockets
    - The .cc files provide executability for the client and server
