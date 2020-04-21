# Define a helper macro for debugging make errors online
# you can type "make print-CFLAGS" and it will show you
# how that ended up being resolved by all of the included
# makefiles.
print-%:
	@echo $*=$($*)

# Output compiler version.
print-version:
	@echo "CC  --version"
	$(shell $(CC) --version)
	@echo "CXX --version"
	$(shell $(CXX) --version)

# Output flags, one per line.
print-flags:
	@echo "CFLAGS"
	@echo $(CFLAGS)
	@echo "ASFLAGS"
	@echo $(ASFLAGS)
	@echo "CXXFLAGS"
	@echo $(CXXFLAGS)
	@echo "CPPFLAGS"
	@echo $(CPPFLAGS)
