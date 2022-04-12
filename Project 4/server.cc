// Copyright 2022 Charles Simons
// Written for Project 4 - CSCE 311 @ U of SC

#include "./server.h"

int main(int argc, char** argv) {
    ServerSocket server("socket1");
    server.RunServer();
}
