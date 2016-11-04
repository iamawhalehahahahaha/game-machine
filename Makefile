################################################################
#	Makefile magic
#	This makefile compiles all the .cpp files in the directory
#	It then links the .o files produced
#	It names the file $(PROJECT)
################################################################

-include state.mk

SRCFILES := $(wildcard $(SRCDIR)/*.cpp)
OBJFILES := $(subst $(SRCDIR),$(OBJDIR),$(SRCFILES))
OBJFILES := $(subst .cpp,.o,$(OBJFILES))

all: $(PROJPATH)

$(PROJPATH): $(OBJFILES) | $(PROJDIR)
	$(CC) $(COMPFLAGS) -o $@ $^

.SECONDEXPANSION:
$(OBJFILES): %.o: $$(subst $(OBJDIR),$(SRCDIR),%.cpp) | $(OBJDIR)
	$(CC) $(COMPFLAGS) -c -o $@ $^

$(PROJDIR):
	mkdir $(PROJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

#cleans the project
.PHONY: clean destroy
OBJCLEAN = $(wildcard $(OBJDIR)/*.o)
clean:
	-rm -f $(OBJCLEAN)
	-rm -f $(PROJPATH)
	-rmdir $(OBJDIR)
	-rmdir $(PROJDIR)
