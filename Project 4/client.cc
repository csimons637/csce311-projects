// Copyright 2022 Charles Simons
// Written for Project 4 - CSCE 311 @ U of SC

#include "./client.h"

int main(int argc, char** argv) {
    ClientSocket client("socket1");
    client.RunClient(argv[2]);
}
