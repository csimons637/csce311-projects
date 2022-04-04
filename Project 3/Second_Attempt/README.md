## CSCE 311 Project 3 - IPC Using Shared Memory
## Charles Simons - CSCE 311-001


# Included Files
    - makefile
    - shared_mem.h
    - named_semphore.h
    - shm_server.h
    - shm_client.h
    - server.cc
    - client.cc
    - named_semaphore.cc
    - ./dat
        - anna_karenina.txt
        - dante.txt
        - lorem_ipsum.txt
    - README.md
    - proj3.pdf
# File Relationships
    - makefile:
        Builds executables (text-server and text-client) and cleans working directory
    - shared_mem.h: 
        Source header for shared memory struct
    - shm_server.h:
        Source header file for server
        Connects to client's shared memory and semaphore
        Defines:
            + readMemBuffers(): void
            + writeResultsToMem(std::string): int
            + searchFoMatches():void
            + GetStdoutFromCommand(std::string): std::string
                - As stated in my code, this function is not my own work. The source URL and author are listed in crediting comments above function declaration
    - shm_client.h:
        Source header file for client
        Constructs and modifies shared memory and semaphore (connects to server, sets write buffer, shared memory size, etc)        
        Defines:
            + writeFileToMem(): void
            + readFromMem(): void
    - server.cc:
        Source file for text-server executable. Runs the server, but takes no arguments
    - client.cc
        Source file for text-client executable. Runs the client semaphore and shared meory and takes in the name of the file to search, and the search key as command line arguments
    - text files:
        Text files to be searched by the server, to find the client's specifed search string
    - proj3.pdf
        Description of project criteria
