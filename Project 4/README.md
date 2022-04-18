## CSCE 311 Project 4 - File-backed Shared Memory
## Charles Simons - CSCE 311-001

# Included Files
    - makefile
    - UDS.h
    - server.h
    - client.h
    - server.cc
    - client.cc
    - ./dat
        - anna_karenina.txt
        - dante.txt
        - lorem_ipsum.txt
    - README.md
    - proj4.pdf
    - file_backed_mmap.c
# File Relationships
    - makefile:
        Builds executables (text-server and text-client) and cleans working directory. Also includes command to build both executables at once
    - UDS.h:
        Serves as the base class for the Unix Domain socket(s) used in _client.h_ and _server.h_
    - server.h:
        Source file for _server.cc_
        Creates Unix Domain socket for receiving a file name from the client
        Defines:
            + void RunServer(): Creates socket and waits for client connection. Then, initiates write of client-specified text file into memory. Once file is mapped to memory, closes the socket
    - client.h:
        Source file for _client.cc_
        Connects to extant socket and sends file name to the server. Also iterates through file and capitalizes all text characters
        Defines:
            + void RunClient(char *file_path): After connecting to socket, send <file_path> to server. After server maps file to memory, opens file and creates 4 threads for file processing
            + static void *caseChange(void *ptr): Reads 1/4 of the file, and changes all lowercase characters to their uppercase counterparts (called by each of four threads)
    - server.cc:
        Source file for _text-server_ executable. Runs the server code and takes no command line arguments
    - client.cc:
        Source file for _text-client_ executable. Runs the client code and take one(1) command line argument (pathname of the text file to be processed)
    - ./dat/*.txt:
        Text files available for processing by client code
    - proj4.pdf
        Project description
    - file_backed_mmap.c:
        Demonstration of file backed memory usage
