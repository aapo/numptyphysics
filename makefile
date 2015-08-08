APP := numptyphysics

SOURCES := $(wildcard src/*.cpp)
CXXFLAGS += -std=c++11 -Isrc -Wall -Wno-sign-compare

all: app

include mk/top.mk

TARGET ?= $(APP)

app: $(TARGET)

$(TARGET): $(OBJECTS) $(LOCAL_LIBS)
	$(SILENTMSG) "\tLD\t$@"
	$(SILENTCMD) $(CXX) -o $@ $^ $(LIBS)
	strip $(APP)

clean: $(ADDITIONAL_CLEAN_TARGETS)
	$(SILENTMSG) "\tCLEAN"
	$(SILENTCMD) $(RM) $(CLEAN_FILES)

distclean: clean $(ADDITIONAL_DISTCLEAN_TARGETS)
	$(SILENTMSG) "\tDISTCLEAN"
	$(SILENTCMD) $(RM) $(APP) $(GENERATED_MAKEFILES)
	$(SILENTCMD) $(RM) $(DISTCLEAN_FILES)

.PHONY: all clean distclean
.DEFAULT: all
