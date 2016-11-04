PROJECT = game-machine

SRCDIR = src
HDRDIR = hdr
OBJDIR = obj
PROJDIR = bin
PROJPATH = $(PROJDIR)/$(PROJECT)

CC = g++
COMPFLAGS = -std=gnu++98 -Wall -Wextra -pedantic -I include
