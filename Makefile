.SUFFIXES: .cpp .hpp

#VERSION
VERSION	= 6.3

# Programs
SHELL 	= bash
CC     	= g++
MKDIR	= mkdir
RM 		= rm
CP		= cp
ECHO	= /bin/echo
CAT 	= cat
PRINTF	= printf
######################################
# Project Name (generate executable with this name)
TARGET = music-box-v$(VERSION)

# Project Paths
PROJECT_ROOT=.
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
IMGDIR = $(PROJECT_ROOT)/img

# Compiler and Linker flags
CPPFLAGS =-g 
CPPFLAGS+=-lglut -lGLU -lGL
LDFLAGS+=-lglut -lGLU -lGL

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all setup doc clean distclean

all: setup $(BINDIR)/$(TARGET)

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)
	@$(CP) -r $(IMGDIR) $(BINDIR)
	

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

$(BINDIR)/$(TARGET): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable: $(NO_COLOR) $(FILE_COLOR) %15s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(OBJS) $(LDFLAGS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[DONE]"; \
	fi;
	@$(RM) -f temp.log temp.err

########################################################################
## Documentation and CleanUp

doc:
	@$(ECHO) "Generating Documentation ...  "
	@$(RM) -rf doc/html
	@$(PRINTF) "${OK_COLOR}%50s\n${NO_COLOR}" "[DONE]"

clean:
	@$(PRINTF) "Cleaning up... "
	@$(RM) -rf $(OBJDIR) *~ $(SRCDIR)/*~
	@$(PRINTF) "${OK_COLOR}%53s\n${NO_COLOR}" "[OK]"
	 
distclean: clean
	@$(PRINTF) "Removing compiled files ... "
	@$(RM) -rf $(BINDIR) *.tgz
	@$(PRINTF) "${OK_COLOR}%40s\n${NO_COLOR}" "[OK]"
	
	
