# Define a helper macro for debugging make errors online
# you can type "make print-CFLAGS" and it will show you
# how that ended up being resolved by all of the included
# makefiles.
print-%:
	@echo $*=$($*)

# Output flags, one per line.
show-flags:
	@echo "CFLAGS"
	@echo $(CFLAGS)
	@echo "ASFLAGS"
	@echo $(ASFLAGS)
	@echo "CXXFLAGS"
	@echo $(CXXFLAGS)
	@echo "CPPFLAGS"
	@echo $(CPPFLAGS)
