// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include "./shared_mem_client.h"

const char mem_name_[] = "shared_memory1";  // name of shared memory file
sem_t* memorySem;
// Client creates and named the shared memory

SharedMemClient::SharedMemClient(const char sem_name[], const char file_path[])
        : mem_sem_(sem_name), file_path_(file_path) {
    memorySem = sem_open(mem_sem_.c_str(), O_CREAT, 0);
    sem_wait(memorySem);
}

int SharedMemClient::writeToMem() {
    // 1. Open shared memory
    int shm_fd = shm_open(mem_name_, O_CREAT, O_RDWR);
    // 1a. Retrun error if opening fails
    if (shm_fd < 0) {
        cerr << strerror << endl;
        return errno;
    }

    // 2. Set size of the shared memory
        // How do I use stat to get file size?
        // How do I the use that to size my buffers?

    // 3. Get copy of the mapped memory

    // 4. Write file contents to buffer; then sem_post

    // 5. sem_wait and read out contents of buffer

    // 6. Close and destroy memory; sem_post
}

