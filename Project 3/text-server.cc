// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include "./shared_mem_server.h"

// Server controls the semaphore


// Gets shared memory semaphore name
// *semaphore created and locked by client
SharedMemServer::SharedMemServer(const char mem_name[], const char sem_name[])
                                : mem_name_(mem_name), mem_sem_(sem_name) {
    mem_sem_.Open();
}

// Opens shared memory and gets file descriptor
int SharedMemServer::readFromClient(const char mem_name[]) {
    string file;    // file to search
    string search;  // for search string

    int sharedMem = ::shm_open(mem_name_.c_str(), O_RDWR, 0);
    if (sharedMem < 0) {  // On failure to open shared memory
        cerr << ::strerror(errno) << endl;
        return errno;
    }

    // Get copy of mapped meory
    SharedMemory* storage = static_cast<SharedMemory*>(
            ::mmap(nullptr, sizeof(SharedMemory),
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED, sharedMem, 0));
    if (storage == MAP_FAILED) {
        cerr << ::strerror(errno) << endl;
        return errno;
    }

    // Get file path and search string from shared memory
}


const char mem_name[] = "shared_memory1";  // name of shared memory file
