VALID_TOOLCHAINS := pnacl

TARGET = MoonlightTizenOld

# Include library makefiles
include common-c.mk
include opus.mk
include h264bitstream.mk
include libgamestream.mk
include ports.mk

EXTRA_INC_PATHS := $(EXTRA_INC_PATHS) $(COMMON_C_INCLUDE) $(OPUS_INCLUDE) $(H264BS_INCLUDE) $(LIBGS_C_INCLUDE) $(PORTS_INCLUDE)
EXTRA_LIB_PATHS := $(EXTRA_LIB_PATHS) $(PORTS_LIB_ROOT)

include $(NACL_SDK_ROOT)/tools/common.mk

# Dirty hack to allow 'make serve' to work in this directory
HTTPD_PY := $(HTTPD_PY) --no-dir-check

CHROME_ARGS += --allow-nacl-socket-api=localhost

LIBS = ppapi_gles2 ppapi ppapi_cpp pthread curl z ssl crypto nacl_io

CFLAGS += -Wall $(COMMON_C_C_FLAGS) $(OPUS_C_FLAGS)
CXXFLAGS += -Wall

SOURCES = \
    $(OPUS_SOURCE)           \
    $(H264BS_SOURCE)         \
    $(COMMON_C_SOURCE)       \
    $(LIBGS_C_SOURCE)        \
    src/libchelper.c             \
    src/main.cpp                 \
    src/input.cpp                \
    src/gamepad.cpp              \
    src/connectionlistener.cpp   \
    src/viddec.cpp               \
    src/auddec.cpp               \
    src/http.cpp                 \
    src/profiling.cpp            \

# Build rules generated by macros from common.mk:

$(foreach src,$(SOURCES),$(eval $(call COMPILE_RULE,$(src),$(CFLAGS))))

# The PNaCl workflow uses both an unstripped and finalized/stripped binary.
# On NaCl, only produce a stripped binary for Release configs (not Debug).
ifneq (,$(or $(findstring pnacl,$(TOOLCHAIN)),$(findstring Release,$(CONFIG))))
$(eval $(call LINK_RULE,$(TARGET)_unstripped,$(SOURCES),$(LIBS),$(DEPS)))
$(eval $(call STRIP_RULE,$(TARGET),$(TARGET)_unstripped))
else
$(eval $(call LINK_RULE,$(TARGET),$(SOURCES),$(LIBS),$(DEPS)))
endif

$(eval $(call NMF_RULE,$(TARGET),))

#use $(OUTDIR) which is defined by common.mk and make extra folder afterwards in which we copy
#the relevant data to have smaller footprint compared to current >100Mb
package:
	@echo 'Invoking: NaCl Translator'
	$(NACL_SDK_ROOT)/toolchain/linux_pnacl/bin/pnacl-translate --allow-llvm-bitcode-input -arch armv7 -o pnacl/Release/MoonlightTizenOld_armv7.nexe pnacl/Release/MoonlightTizenOld.pexe
	python "$(NACL_SDK_ROOT)/tools/create_nmf.py" -s ./  -o "pnacl/Release/MoonlightTizenOld.nmf" "pnacl/Release/MoonlightTizenOld_armv7.nexe"
	@echo 'Finished translation'
