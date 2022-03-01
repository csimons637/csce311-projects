// Copyright 2022 Charles Simons
// Written for Project 2 - CSCE 311 @ U of SC
// Modified from existing code by J. Lewis
// (instructor for CSCE 311, Spring 2022)

#include <UDS_server.h>

// server for demonstrating IPC using Unix Domain sockets
// receives file name and search term from client
// returns found line(s) to client

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "Usage: ./text-server <socket name>" << endl;
    return 1;
  }

  if (argv[1] != NULL) {        // checks that argument exists
    DomServSock dss(argv[1]);   // builds new server socket
    dss.RunServ();              // runs the server
  }
}
