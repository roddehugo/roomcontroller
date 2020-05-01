# Project Makefile must specify top-level directory.
ifeq ($(BASE),)
$(error BASE is not defined)
endif

# Check PROGRAM is defined.
ifeq ($(PROGRAM),)
$(error PROGRAM is not defined)
endif

# Check TARGET is defined.
ifeq ($(TARGET),)
$(error TARGET is not defined)
endif

# Check SOURCES are specified.
ifeq ($(SOURCES),)
$(error SOURCES are not specified)
endif

# Be silent per default, but 'make V=1' will show all compiler calls.
ifneq ($(V),1)
Q = @
MAKEFLAGS += --no-print-directory
endif

# Get directory of this Makefile.
BUILD := $(patsubst %/main.mk,%,$(lastword $(MAKEFILE_LIST)))

# Include compiler commands.
include $(BUILD)/gcc.mk

# Include make macros.
include $(BUILD)/macros.mk

# Directory commands.
RM := rm -f
RMDIR := rm -rf
MKDIR := mkdir -p

# Objects directory.
OBJDIR := obj

# User defined compilation flags.
OPT ?= -Og
DEBUG ?= -g3
CSTD ?= -std=c99
CXXSTD ?= -std=c++14

# Include default directories.
INCLUDES = -I. -I$(BASE) -I$(OBJDIR)

# Virtual paths to look for sources.
vpath %.S $(BASE)
vpath %.c $(BASE)
vpath %.cc $(BASE)

# Include target specific flags.
include $(BUILD)/$(TARGET).mk

# Include flags.
include $(BUILD)/flags.mk

# Decline objects from source files.
.SECONDARY: $(OBJS)
OBJS := $(filter %.o,$(SOURCES:%.S=$(OBJDIR)/%.o))
OBJS += $(filter %.o,$(SOURCES:%.c=$(OBJDIR)/%.o))
OBJS += $(filter %.o,$(SOURCES:%.cc=$(OBJDIR)/%.o))

# Main rules.
.PHONY: all
all: build

# Binary rules.
.PHONY: build
build: $(PROGRAM).bin

# Run rule.
.PHONY: run
run: $(PROGRAM).bin
	@echo "PROG  $<"
	$(Q) ./$(PROGRAM).bin

# Size rule.
.PHONY: size
size: $(PROGRAM).bin
	@echo "SIZE  $<"
	$(Q)$(SIZE) $<

# Cleaning rules.
.PHONY: clean
clean:
	@echo "RMDIR $(OBJDIR)"
	$(Q)$(RMDIR) $(OBJDIR)
	@echo "RM    $(PROGRAM).bin"
	$(Q)$(RM) $(PROGRAM).bin

# Making objects directory rule.
$(OBJDIR):
	@echo "MKDIR $@"
	$(Q)$(MKDIR) $@

# Include dependency generation rules.
include $(BUILD)/deps.mk

# Making rules.
$(PROGRAM).bin: $(OBJS) $(LIBDEPS)
	@echo "LD    $@"
	$(Q)$(LD) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(OBJDIR)/%.o: %.S $(OBJDIR)/defs.old | $(OBJDIR)
	@echo "AS    $<"
	$(call mkdir_if_needed,$@)
	$(Q)$(CC) $(ASFLAGS) $(CPPFLAGS) -o $@ -c $<

$(OBJDIR)/%.o: %.c $(OBJDIR)/defs.old | $(OBJDIR)
	@echo "CC    $<"
	$(call mkdir_if_needed,$@)
	$(Q)$(CC) $(CSTD) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(OBJDIR)/%.o: %.cc $(OBJDIR)/defs.old | $(OBJDIR)
	@echo "CXX   $<"
	$(call mkdir_if_needed,$@)
	$(Q)$(CXX) $(CXXSTD) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

# Include help rules.
include $(BUILD)/print.mk

# Include dependency checking rules.
-include $(OBJS:.o=.d)
