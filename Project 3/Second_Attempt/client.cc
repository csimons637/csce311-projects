// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include "./shm_client.h"

int main(int argc, char** argv) {
    Client client = Client(argv[1], argv[2]);
    client.writeFileToMem();
    client.readFromMem();
}

Client::Client(const char* search_str, const char* file_path)
    : shm_name_("memory"), shm_semaphore_("semaphore"),
    search_str_(search_str), file_path_(file_path) {
    // Opens shared memory and gets file descriptor
    const int kOFlags = O_CREAT | O_EXCL | O_RDWR;
    int shm_fd = ::shm_open(shm_name_, kOFlags, 0660);
    if (shm_fd < 0) {
        std::cerr << ::strerror(errno) << std::endl;
        ::exit(errno);
    }

    // Set size of shared memory with file descriptor
    struct stat file_attr;
    const size_t kBuffer_size = stat(file_path_, &file_attr) + 256;
    const size_t kSHM_size = sizeof(SharedMemory) + kBuffer_size;
    if (::ftruncate(shm_fd, kSHM_size) < 0) {
        std::cerr << ::strerror(errno) << std::endl;
        ::exit(errno);
    }

    // Write search term to shared memory
    strncpy(storage_->search_str, search_str_, sizeof(search_str_));

    // Get copy of shared memory
    const int kFlags = PROT_READ | PROT_WRITE;
    storage_ = static_cast<SharedMemory*>(::mmap(nullptr,
        sizeof(SharedMemory), kFlags, MAP_SHARED, shm_fd, 0));
    if (storage_ == MAP_FAILED) {
        std::cerr << ::strerror(errno) << std::endl;
        ::exit(errno);
    }

    // Initialize memory mapping
    *storage_ = {};
    storage_->buffer_size = kBuffer_size;

    // Create semaphore to lock memory access
    shm_semaphore_.Create(0);
    shm_semaphore_.Open();
}

Client::~Client() {
    int exit_code = ::munmap(storage_, sizeof(SharedMemory));

    if (exit_code < 0) {
        std::cerr << ::strerror(errno) << std::endl;
    }

    if (::shm_unlink(shm_name_) < 0) {
        std::cerr << ::strerror(errno) << std::endl;
    }

    shm_semaphore_.Destroy();

    ::exit(errno);
}

void Client::writeFileToMem() {
    shm_semaphore_.Down();  // Lock memory semaphore
    std::string line;
    std::ifstream file;
    file.open(file_path_);
    while (file.is_open()) {
        while (getline(file, line)) {
            strncpy(storage_->buffer, line.c_str(), line.length());
        }
        file.close();
    }
    shm_semaphore_.Up();  // Unlock memory semaphore
}

void Client::readFromMem() {
    shm_semaphore_.Down();
    char* from_buff;
    strncpy(from_buff, storage_->buffer, sizeof(storage_->buffer));
    std::cout << from_buff << std::endl;
    shm_unlink(shm_name_);  // Unlink shared memory
    ::exit(0);
}
