// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include "./shm_server.h"

int main(int argc, char** argv) {
    Server server = Server();
    server.readMemBuffers();
}


Server::Server() : shm_name_("memory"), shm_semaphore_("semaphore") {
    shm_semaphore_.Open();
    const int kFlags = PROT_READ | PROT_WRITE;
    // Open shared memory and get file descriptor
    int shm_fd = shm_open(shm_name_, O_RDWR, 0);
    if (shm_fd < 0) {
        std::cerr << ::strerror(errno) << std::endl;
        ::exit(errno);
    }

    // Get copy of mapped memory
    storage_ = static_cast<SharedMemory*>(
        ::mmap(nullptr, sizeof(SharedMemory), kFlags,
        MAP_SHARED, shm_fd, 0));
    if (storage_ == MAP_FAILED) {
        std::cerr << ::strerror(errno) << std::endl;
        ::exit(errno);
    }
}

void Server::readMemBuffers() {
    shm_semaphore_.Down();
    std::string search = search_str_;
    std::string grep;
    std::string dante = "dat/dante.txt";
    std::string anna_k = "dat/anna_karenina.txt";
    std::string lorem_ip = "dat/lorem_ipsum.txt";

    if (file_path_ == dante) {
        grep = "grep -f " + search + "dat/dante.txt";
    } else if (file_path_ == anna_k) {
        grep = "grep -f " + search + "dat/anna_karenina.txt";
    } else if (file_path_ == lorem_ip) {
        grep = "grep -f " + search + "dat/lorem_ipsum.txt";
    }
    std::string fromGrep = GetStdoutFromCommand(grep);

    strncpy(storage_->buffer, fromGrep.c_str(), sizeof(fromGrep));

    shm_semaphore_.Up();
}

// This code is not mine. I referenced it from Jeremy Morgan, at their website:
// https://www.jeremymorgan.com/tutorials/c-programming/how-to-capture-the-output-of-a-linux-command-in-c/
// Intent is to call grep and capture its output for use by shared memory server
std::string Server::GetStdoutFromCommand(std::string cmd) {
  std::string data;
  FILE * stream;
  const int kMax_buffer = 256;
  char buffer[kMax_buffer];
  cmd.append(" 2>&1");

  stream = popen(cmd.c_str(), "r");
  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, kMax_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }
  return data;
}
