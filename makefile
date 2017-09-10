#########################
rwildcard=$(strip $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)))
#########################
TARGET=linker_pc.exe
#########################
CC=g++
CFLAGS=-g -c -m32 -O0 -Wall -std=c++11 -I./src
LFLAGS=-Wl,--image-base,0x400000 -Tsrc/loader/linker_pc.ld
#########################
TARGETDIR=bin
OBJDIR=obj
#########################
SOURCES_C=$(call rwildcard,src/,*.c)
SOURCES_CPP=$(call rwildcard,src/,*.cpp)
OBJECTS_C=$(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SOURCES_C)))
OBJECTS_CPP=$(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SOURCES_CPP)))
#########################
all: notify $(TARGETDIR)/$(TARGET)
	@echo Done

notify:
	@echo Begin

$(TARGETDIR)/$(TARGET): $(OBJECTS_C) $(OBJECTS_CPP)
	@echo   $(CC)  $@
	@$(CC) $(LFLAGS) -o $@ $^

define RULE_C
$(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(1))): $(1)
	@echo   $$(CC)  $$<
	@$$(CC) $$(CFLAGS) -o $$@ $$<
endef
$(foreach src,$(SOURCES_C),$(eval $(call RULE_C,$(src))))

define RULE_CPP
$(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(1))): $(1)
	@echo   $$(CC)  $$<
	@$$(CC) $$(CFLAGS) -o $$@ $$<
endef
$(foreach src,$(SOURCES_CPP),$(eval $(call RULE_CPP,$(src))))

clean:
	@del $(subst /,\,$(OBJECTS_C)) $(subst /,\,$(OBJECTS_CPP)) >nul 2>&1
