# Copyright 2022 Charles Simons
# Written for Project 2 - CSCE 311 @ U of SC
cc = g++

flags = -std=c++17
flags += -Wall
flags += -g

link = $(cc) $(flags) -o
compile = $(cc) $(flags) -c

# for executables (used in clean)
obj = text-client text-server

# client compilation
text-client : text-client.cc
			$(link) $@ $^

# server compilation
test-server : text-server.cc
			$(link) $@ $^

# directory clean-up
.PHONY : clean
clean :
		$(RM) $(obj)
