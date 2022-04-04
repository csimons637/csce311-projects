## CSCE 311 Project 3 - IPC Using Shared Memory
## Charles Simons - CSCE 311-001


# Included Files
    - makefile
    - shared_memory.h
    - named_semphore.h
    - shared_mem_server.h
    - shared_mem_client.h
    - text-server.cc
    - text-client.cc
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
    - shared_mem_server.h:
        Source header file for server
        Connects to client's shared memory and semaphore
        Defines:
            + readMemBuffers(): void
            + writeResultsToMem(std::string): int
            + searchFoMatches():void
    - shared_mem_client.h:
        Source header file for client
        Constructs and modifies shared memory and semaphore (connects to server, sets write buffer, shared memory size, etc)        
        Defines:
            + writeFileToMem(): void
            + readFromMem(): void
    - shared_memory.h
        Source header file for shared memory struct
        Defines the contents and size of parts of shared memory
    - named_semaphore.h
        Source header file for named semaphore
        Defines functions to lock and unlock the semaphore and create and destroy the semaphore
    - name_semaphore.cc
        Further refines semaphore functionality
    - text-server.cc:
        Source file for text-server executable. Runs the server, but takes no arguments
    - text-client.cc
        Source file for text-client executable. Runs the client semaphore and shared meory and takes in the name of the file to search, and the search key as command line arguments
    - text files:
        Text files to be searched by the server, to find the client's specifed search string
    - proj3.pdf
        Description of project criteria
