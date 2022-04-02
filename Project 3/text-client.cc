// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include "./shared_mem_client.h"

const char mem_name_[] = "shared_memory1";  // name of shared memory file

// Client creates and names the shared memory

int main(int argc, char* argv[]) {
    SharedMemClient(argv[1], argv[2]);
}

SharedMemClient::SharedMemClient(const char sem_name[], const char file_path[])
        : memorySem(mem_sem_), file_path_(file_path) {
    memorySem.Open();
    memorySem.Down();
    writeToMem();
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
    struct stat file_atr;
    const size_t kBuffer_size = stat(file_path_.c_str(), &file_atr) + 256;
    if (ftruncate(shm_fd, sizeof(SharedMemory) + kBuffer_size) < 0) {
        cerr << strerror(errno) << endl;
        return errno;
    }

    // 3. Get copy of the mapped memory
    storage = static_cast<SharedMemory*>(
        mmap(nullptr, kBuffer_size, PROT_READ | PROT_WRITE,
            MAP_SHARED, shm_fd, 0));

    if (storage == MAP_FAILED) {
        cerr << strerror(errno) << endl;
        return errno;
    }

    // 4. Write file contents to buffer; then sem_post
    *storage = {};
    storage->buffer_size = kBuffer_size;  // sets shared mem's buffer size
    string line;  // to store lines from text file

    // 4a. File read stream into buffer
    ifstream reader(file_path_);
    if (!reader.is_open()) {  // error if file not opened/openable
        cerr << strerror(errno) << endl;
        return errno;
    }

    while (getline(reader, line)) {
        strncpy(storage->buffer, line.c_str(), sizeof(line));
    }
    reader.close();
    memorySem.Up();

    // 5. sem_wait and read out contents of buffer
    memorySem.Up();
    char output[sizeof(storage->buffer)];
    strncpy(output, storage->buffer, sizeof(storage->buffer));

    cout << output << endl;

    // 6. Close and destroy memory; sem_post
    // Error messages if unmapping or deletion fail
    // Releases shared memory
    if (munmap(storage, sizeof(SharedMemory)) < 0) {
        cerr << strerror(errno) << endl;
    }
    // Deletes shared memory mapping
    if (shm_unlink(mem_name_) < 0) {
        cerr << strerror(errno) << endl;
    }

    memorySem.Down();
    exit(0);
}

