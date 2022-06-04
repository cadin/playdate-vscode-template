HEAP_SIZE      = 8388208
STACK_SIZE     = 61800

PRODUCT = HelloWorld.pdx

# Locate the SDK
SDK = ${PLAYDATE_SDK_PATH}
ifeq ($(SDK),)
	SDK = $(shell egrep '^\s*SDKRoot' ~/.Playdate/config | head -n 1 | cut -c9-)
endif

ifeq ($(SDK),)
$(error SDK path not found; set ENV value PLAYDATE_SDK_PATH)
endif

######
# IMPORTANT: You must add your source folders to VPATH for make to find them
# ex: VPATH += src1:src2
######

VPATH += src

# List C source files here
SRC = src/main.c src/lib/_event_handler_.c src/lib/_state_.c src/lib/_update_.c

# List all user directories here
UINCDIR = 

# List user asm files
UASRC = 

# List all user C define here, like -D_DEBUG=1
UDEFS = 

# Define ASM defines here
UADEFS = 

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS =

include $(SDK)/C_API/buildsupport/common.mk

run: pdc
	open -a $(SDK)/bin/Playdate\ Simulator.app $(PRODUCT)

.temp:
	mkdir .temp

testex: src/lib/*.c src/lib/__tests__/*.c .temp
	gcc -DTARGET_EXTENSION -I/opt/homebrew/include -L/opt/homebrew/lib -lcmocka -I$(SDK)/C_API -DTEST src/lib/__tests__/*.c src/lib/*.c -o ./.temp/test

test: testex
	./.temp/test

watch: test run
	watchman-make -p src/**/* src/lib/__tests__/* src/lib/__tests__/**/* -t test -p  src/* src/lib/* -t run