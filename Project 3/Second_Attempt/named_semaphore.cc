// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

#include "./named_semaphore.h"

void NamedSemaphore::Create(int count) {
    sem_ptr_ = ::sem_open(name_.c_str(), O_CREAT,
    S_IRGRP | S_IRUSR | S_IWGRP | S_IWUSR, count);

    if (sem_ptr_ == SEM_FAILED) {
        std::cerr << ::strerror(errno) << std::endl;
        ::exit(errno);
    }

    if (sem_close(sem_ptr_) < 0) {
        std::cerr << ::strerror(errno) << std::endl;
        ::exit(errno);
    }

    sem_ptr_ = nullptr;
}

void NamedSemaphore::Open() {
    sem_ptr_ = ::sem_open(name_.c_str(), 0, 0, 0);

    if (sem_ptr_ == SEM_FAILED) {
        std::cerr << ::strerror(errno) << std::endl;
        ::exit(errno);
    }
}
