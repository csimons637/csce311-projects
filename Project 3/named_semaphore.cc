// Copyright 2022 Charles Simons
// Written for Project 3 - CSCE 311 @ U of SC
// Based on code written by Dr. Jeremy Lewis
// (instructor for CSCE 311, Spring 2022)

# include "./named_semaphore.h"

void Semaphore::Create(int count) {
    // creates semaphore with name
    sem_ptr_ == sem_open(name.c_str(), O_CREAT,
                        S_IRGRP | S_IRUSR | S_IWGRP | S_IWUSR,
                        count);

    if (sem_ptr_ == SEM_FAILED) {
        cerr << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }

    if (sem_close(sem_ptr_) < 0) {
        cerr << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }

    sem_ptr_ = nullptr;
}

void Semaphore::Open() {
    sem_ptr_ = sem_open(name.c_str(), 0, 0, 0);

    if (sem_ptr_ == SEM_FAILED) {
        cerr << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
}