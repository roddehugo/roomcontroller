# Assembler flags.
ASFLAGS += $(DEBUG)
ASFLAGS += -x assembler-with-cpp

# C flags.
CFLAGS += $(OPT) $(DEBUG)
CFLAGS += -Wall # Enable all warnings.
CFLAGS += -Wextra # Enable extra warnings.
CFLAGS += -Werror # Turn warnings into errors.

# Extra warnings and optimization flags sorted lexically.
CFLAGS += -Wdouble-promotion # Warn for float implicitly promoted to double.
CFLAGS += -Wformat=2 # Enable '-Wformat' plus additional format checks.
CFLAGS += -Wmissing-prototypes # Warn functions defined without prototype.
CFLAGS += -Wno-unused-parameter # Do not warn for unused parameter.
CFLAGS += -Wshadow # Warn for any global shadowing.
CFLAGS += -Wstrict-prototypes # Warn functions defined without argument types.
CFLAGS += -Wundef # Warn undefined identifier evaluated in #if directive.
CFLAGS += -fdata-sections # Place each data into its own section.
CFLAGS += -ffunction-sections # Place each function into its own section.
CFLAGS += -fno-common # Emit duplicate symbol warning at link time.

# C++ flags.
CXXFLAGS += $(CFLAGS)
CXXFLAGS += -Weffc++ # Warn about violations of the Scott Meyers's guidelines.
CXXFLAGS += -fno-exceptions # Disable C++ exceptions. Most of the std namespace
# is off-limits, including STL containers, except <algorithm>, which is mostly OK.
CXXFLAGS += -fno-rtti # Disable generation of information about every class with
# virtual functions for use by the C++ run-time type identification features.
CXXFLAGS += -fno-threadsafe-statics # Do not emit the extra code to use the
# routines specified in the C++ ABI for thread-safe initialization of local statics.

# C & C++ preprocessor flags.
CPPFLAGS += $(DEFS)
CPPFLAGS += $(INCLUDES)
CPPFLAGS += -MP # Emit dummy dependency rules.
CPPFLAGS += -MMD # List only user header files.

# Linker flags.
LDFLAGS += $(DEBUG)
ifeq ($(shell uname -s),Darwin) # On macOS 'gcc' is actually 'clang'.
LDFLAGS += -Wl,-dead_strip # Enable garbage collection of unused input sections.
else
LDFLAGS += -Wl,--gc-sections # Enable garbage collection of unused input sections.
endif
