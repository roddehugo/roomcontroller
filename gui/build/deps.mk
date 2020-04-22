# Handle command line changes.
# The given variable is saved in savefile, which should be included as target
# dependencies.  If variable content is not the same as in previous build, the
# savefile is made phony and the target is rebuilt.
# $(call cmddep,VAR,savefile)
define cmddep
-include $2
.PHONY: $$(if $$(call diff,$$($1_OLD),$$($1)),$2)
$2:
	@echo "DEP   $$@"
	$$(call mkdir_if_needed,$$@)
	$$(Q)echo "$1_OLD = $$($1)" > $$@
endef

# Make sure to rebuild sources if defines change.
$(eval $(call cmddep,DEFS,$(OBJDIR)/defs.old))
