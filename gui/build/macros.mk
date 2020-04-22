# Run mkdir if directory does not exists.
# $(call mkdir_if_needed,FILE)
mkdir_if_needed = $(if $(wildcard $(dir $1)),,$(Q)$(MKDIR) $(dir $1))

# Return words which are in one argument but not in the other one.
# $(call diff,A,B)
diff = $(strip $(filter-out $1,$2) $(filter-out $2, $1))
