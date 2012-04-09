machine = $(shell uname -m)
uname = $(shell uname)
os = $(strip $(uname))
ifeq ($(os),Darwin)
  platform = -DIH_PLATFORM_DARWIN
endif
ifeq ($(os),Linux)
  platform = -DIH_PLATFORM_LINUX
endif
ifeq ($(os),NetBSD)
  platform = -DIH_PLATFORM_NETBSD
endif

build = -DIH_BUILD_DEVELOPMENT
debugging = -g
optimization = -O0
mode_identifier = +
warnings = -Wall -Werror
ifeq ($(MAKECMDGOALS),release)
  build = -DIH_BUILD_RELEASE
  debugging = -DNDEBUG
  optimization = -O3
  mode_identifier = \#
endif

compiler = gcc
libraries = -ljpeg -lm -lcurses -lpq -lpthread
library_paths = -L. $(IH_LIBRARY_PATHS) -L/usr/lib -L/usr/local/lib
ifeq ($(os),Linux)
  libraries += -luuid
endif
ifeq ($(os),NetBSD)
endif
include_paths = -I$(IH)/.. $(IH_INCLUDE_PATHS)
link_options = -ansi $(build) $(platform) $(debugging) $(optimization) $(warnings) $(include_paths) -D_GNU_SOURCE $(library_paths) $(libraries)
compile_options = -ansi $(build) $(platform) $(debugging) $(optimization) $(warnings) $(include_paths) -D_GNU_SOURCE

clean_files =

include .make-options

object_bases = $(shell find . -name "*.c" | grep -v "\.test\.c" | grep -v "\.impl\." | grep -v "\.bin\.c" | sed 's/\(.*\)\..*/\1/')
object_sources := $(foreach object_base, $(object_bases), $(object_base).c)
objects := $(foreach object_base, $(object_bases), $(object_base).o)
external_objects := $(shell external-objects)
object_tests := $(foreach object_base, $(object_bases), $(object_base).test)
programs = $(shell find . -name "*.bin.c" | sed 's/\(.*\)\..*/\1/')

development: _all

release: clean _all

stats:
	@stats

tags:
	@make-etags

test: _test

tests: _tests

todo:
	@show-todos

clean:
	@find . -name "*~" -exec rm {} \;
	@find . -name ".*~" -exec rm {} \;
	@find . -name "*.a" -exec rm {} \;
	@find . -name "*.o" -exec rm {} \;
	@find . -name "*.test" -exec rm {} \;
	@find . -name "*.bin" -exec rm {} \;
	@find . -name ".make-depend.bak" -exec rm {} \;
	@find . -name ".etags" -exec rm {} \;
	@find . -name ".DS_Store" -exec rm {} \;
	@find . -name ".make-depend" -exec blank-file {} \;
	@rm -f $(clean_files)
	@clean

help:
	@echo "make                                                 ( make objects, programs )"
	@echo "  + test                                              ( make tests, run tests )"
	@echo "  + tests                                                        ( make tests )"
	@echo "  + release                          ( make objects, programs in release mode )"
	@echo "  + tags                                          ( make Emacs tags in .etags )"
	@echo "  + clean                                                             ( clean )"
	@echo "  + stats                                              ( show code statistics )"
	@echo "  + todo                                          ( show todo items from code )"

_all: _init _objects _programs _library

_debug:
#	@echo $(object_bases)
#	@echo $(platform)
#	@echo $(include_paths)
	@echo $(library_paths)

_init:
	@makedepend -f.make-depend $(include_paths) $(object_sources)

_library:
	@make-library "$(mode_identifier)"

_objects: $(objects)

_test: _tests
	@run-tests $(object_tests)

_tests: $(objects) $(object_tests)

_programs: $(programs)

_run_tests:
	@run-tests $(object_tests)

%.o: %.c
	@quiet-execute "$(mode_identifier) $@" "$(compiler) $< -o $@ -c $(compile_options)"

%.test: %.test.c $(objects) $(external_objects)
	@quiet-execute "$(mode_identifier) $@" "$(compiler) $< -o $@ $(objects) $(external_objects) $(compile_options) $(link_options)"

%.bin: %.bin.c $(objects) $(external_objects)
	@quiet-execute "$(mode_identifier) $@" "$(compiler) $< -o $@ $(objects) $(external_objects) $(compile_options) $(link_options)"

include .make-depend
