// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include "./shared_mem_server.h"


// Gets shared memory semaphore name
// *semaphore created and locked by client
SharedMemServer::SharedMemServer(const char mem_name[], const char sem_name[])
                                : mem_name_(mem_name), mem_sem_(sem_name) {
    mem_sem_.Open();
}



const char mem_name[] = "shared_memory1";  // name of shared memory file
