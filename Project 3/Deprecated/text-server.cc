// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include "./shared_mem_server.h"

const char mem_name_[] = "/shared_memory1";  // name of shared memory file

char path_to_file[1];
char term_to_search[1];
char file_text[1];

static vector<string> thread_vectors[4];

int main(int argc, char** argv) {
    SharedMemServer();
}

// Server controls the semaphore
// Creates semaphore using hardcoded semaphore name
// Then unlocks the semaphore
SharedMemServer::SharedMemServer() : memorySem(mem_sem_) {
    memorySem.Create(0);
    memorySem.Open();
    cout << "Server Started" << endl;
    ToFromClient();
}

SharedMemServer::~SharedMemServer() {
    memorySem.Destroy();
}

// Search the file text for matching strings
void *SharedMemServer::searchFile(void *ptr) {
    // Tentative methodology; feels hacky and underdeveloped
    // Ask Lewis for better direction
    int index = *reinterpret_cast<int*>(ptr);
    vector<string> thread = thread_vectors[index];
    if (index == 0) {
        int i = 0;
        while (i < (sizeof(file_text)/4)) {
            // need substring from file_text
            string search = term_to_search;
            string text = file_text;
            string line = text.substr(i, search.length());  // Get one line
            // if a subline matches, store entire line in vector
            if (line == search) {
                // Add matching line to vector<string> thread and append '\n'
                thread.push_back(text.substr(line.length() - 32,
                                            line.length() + 32) + '\n');
            }
            i += sizeof(line);
        }
    } else if (index == 1) {
        int i = (sizeof(file_text)/4) - 1;
        while (i < (sizeof(file_text)/2)) {
            // need substring from file_text
            string search = term_to_search;
            string text = file_text;
            string line = text.substr(i, search.length());  // Get one line
            // if a subline matches, store entire line in vector
            if (line == search) {
                // Add matching line to vector<string> thread and append '\n'
                thread.push_back(text.substr(line.length() - 32,
                                            line.length() + 32) + '\n');
            }
            i += sizeof(line);
        }
    } else if (index == 2) {
        int i = ((sizeof(file_text)/2)) - 1;
        while (i < ((3/4) * (sizeof(file_text)))) {
            // need substring from file_text
            string search = term_to_search;
            string text = file_text;
            string line = text.substr(i, search.length());  // Get one line
            // if a subline matches, store entire line in vector
            if (line == search) {
                // Add matching line to vector<string> thread and append '\n'
                thread.push_back(text.substr(line.length() - 32,
                                            line.length() + 32) + '\n');
            }
            i += sizeof(line);
        }

    } else if (index == 3) {
        int i = ((3/4) * (sizeof(file_text))) - 1;
        while (i < (sizeof(file_text))) {
            // need substring from file_text
            string search = term_to_search;
            string text = file_text;
            string line = text.substr(i, search.length());  // Get one line
            // if a subline matches, store entire line in vector
            if (line == search) {
                // Add matching line to vector<string> thread and append '\n'
                thread.push_back(text.substr(line.length() - 32,
                                            line.length() + 32) + '\n');
            }
            i += sizeof(line);
        }
    }
}

// Open shared memory and get file descriptor
int SharedMemServer::ToFromClient() {
    // 1. Get file descriptor
    memorySem.Down();
    char search_str[sizeof(storage->search_str)];  // search string buffer
    char file_path[sizeof(storage->file_path)];  // file path buffer
    char buffer[sizeof(storage->buffer)];  // search text buffer
    int mem_fd = ::shm_open(mem_name_.c_str(), O_RDWR, 0);
    if (mem_fd < 0) {
        cerr << strerror(errno) << endl;
        return errno;
    }

    // 2. Get a copy of mapped memory
    SharedMemory* storage = static_cast<SharedMemory*>
    (::mmap(nullptr, sizeof(SharedMemory),
            PROT_READ | PROT_WRITE,
            MAP_SHARED, mem_fd, 0));
    // 2a. Return error state if memory mapping fails
    if (storage == MAP_FAILED) {
        cerr << strerror(errno) << endl;
        return errno;
    }

    // 3. Copy search string from memory into local variable
    strncpy(search_str, storage->search_str, sizeof(storage->search_str));
    strncpy(term_to_search, search_str, sizeof(search_str));

    cout << "Opening: " << storage->file_path << endl;

    // 4. Copy path text file from memory to local variable
    strncpy(file_path, storage->file_path, sizeof(storage->file_path));
    strncpy(path_to_file, file_path, sizeof(file_path));

    // 5. Copy search text from shared memory
    strncpy(buffer, storage->buffer, sizeof(storage->buffer));
    strncpy(file_text, buffer, sizeof(buffer));

    // 6. Search file for search string using four
    // threads for search; each taking 1/4 of file
    pthread_t threads[4];
    int thread_args[4];
    int ret_code;

    for (int i = 0; i < 4; i++) {
        thread_args[i] = i;
        ret_code = pthread_create(&threads[i], nullptr,
                            searchFile, &thread_args[i]);
    }

    for (int i = 0; i < 4; i++) {
        ret_code = pthread_join(threads[i], nullptr);
    }

    cout << "File Closed" << endl;

    // 7. Write results to shared memory
    for (vector<string> v : thread_vectors) {
        // For each vector<string>, strncpy each element to shared memory
        for (int i = 0; i < v.size(); i++) {
            strncpy(storage->buffer, v.at(i).c_str(), v.at(i).size());
        }
    }
    // 7a. Release copy of shared memory
    cout << "Memory Closed" << endl;
    int result = ::munmap(storage, sizeof(storage));
    if (result < 0) {
        cerr << strerror << endl;
        return errno;
    }

    // 8. Release memory semaphore
    memorySem.Up();

    // 9. sem_wait; destroy semaphore when client is done with it
    memorySem.Down();
    exit(0);
}
