// Copyright 2022 Charles Simons
// Written for Project 2 - CSCE 311 @ U of SC
// Modified from existing code by J. Lewis
// (instructor for CSCE 311, Spring 2022)

#include "UDS_client.h"

// client for demonstrating IPC using Unix Domain sockets
// sends file name and search term to server socket
// receives found line(s) from server

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  if (argc != 4) {
    cout << "Usage: ./text-client <socket name>"
         << " <text file path> <search string>" << endl;
    return 1;
  }

  DomClntSock dcs(argv[1]);   // builds new client
  dcs.getFile(argv[2]);       // acquires file path for search
  dcs.RunClnt();              // runs the client
}
