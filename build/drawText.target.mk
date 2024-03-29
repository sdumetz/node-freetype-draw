# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := drawText
DEFS_Debug := \
	'-DNODE_GYP_MODULE_NAME=drawText' \
	'-DUSING_UV_SHARED=1' \
	'-DUSING_V8_SHARED=1' \
	'-DV8_DEPRECATION_WARNINGS=1' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_IMMINENT_DEPRECATION_WARNINGS' \
	'-D_GLIBCXX_USE_CXX11_ABI=1' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-D__STDC_FORMAT_MACROS' \
	'-DOPENSSL_NO_PINSHARED' \
	'-DOPENSSL_THREADS' \
	'-DBUILDING_NODE_EXTENSION' \
	'-DDEBUG' \
	'-D_DEBUG' \
	'-DV8_ENABLE_CHECKS'

# Flags passed to all source files.
CFLAGS_Debug := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-g \
	-O0

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-rtti \
	-std=gnu++14

INCS_Debug := \
	-I/home/sebastien/.cache/node-gyp/16.9.1/include/node \
	-I/home/sebastien/.cache/node-gyp/16.9.1/src \
	-I/home/sebastien/.cache/node-gyp/16.9.1/deps/openssl/config \
	-I/home/sebastien/.cache/node-gyp/16.9.1/deps/openssl/openssl/include \
	-I/home/sebastien/.cache/node-gyp/16.9.1/deps/uv/include \
	-I/home/sebastien/.cache/node-gyp/16.9.1/deps/zlib \
	-I/home/sebastien/.cache/node-gyp/16.9.1/deps/v8/include \
	-I/home/sebastien/repositories/node-freetype-draw/node_modules/node-addon-api \
	-I$(srcdir)/vendor/freetype/include

DEFS_Release := \
	'-DNODE_GYP_MODULE_NAME=drawText' \
	'-DUSING_UV_SHARED=1' \
	'-DUSING_V8_SHARED=1' \
	'-DV8_DEPRECATION_WARNINGS=1' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_IMMINENT_DEPRECATION_WARNINGS' \
	'-D_GLIBCXX_USE_CXX11_ABI=1' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-D__STDC_FORMAT_MACROS' \
	'-DOPENSSL_NO_PINSHARED' \
	'-DOPENSSL_THREADS' \
	'-DBUILDING_NODE_EXTENSION'

# Flags passed to all source files.
CFLAGS_Release := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-O3 \
	-fno-omit-frame-pointer

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-fno-rtti \
	-std=gnu++14

INCS_Release := \
	-I/home/sebastien/.cache/node-gyp/16.9.1/include/node \
	-I/home/sebastien/.cache/node-gyp/16.9.1/src \
	-I/home/sebastien/.cache/node-gyp/16.9.1/deps/openssl/config \
	-I/home/sebastien/.cache/node-gyp/16.9.1/deps/openssl/openssl/include \
	-I/home/sebastien/.cache/node-gyp/16.9.1/deps/uv/include \
	-I/home/sebastien/.cache/node-gyp/16.9.1/deps/zlib \
	-I/home/sebastien/.cache/node-gyp/16.9.1/deps/v8/include \
	-I/home/sebastien/repositories/node-freetype-draw/node_modules/node-addon-api \
	-I$(srcdir)/vendor/freetype/include

OBJS := \
	$(obj).target/$(TARGET)/src/init.o \
	$(obj).target/$(TARGET)/src/Renderer.o \
	$(obj).target/$(TARGET)/src/Color.o \
	$(obj).target/$(TARGET)/src/PixFmt.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# Make sure our dependencies are built before any of us.
$(OBJS): | $(builddir)/freetype.a $(obj).target/gyp/freetype.a

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-pthread \
	-rdynamic \
	-m64

LDFLAGS_Release := \
	-pthread \
	-rdynamic \
	-m64

LIBS :=

$(obj).target/drawText.node: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/drawText.node: LIBS := $(LIBS)
$(obj).target/drawText.node: TOOLSET := $(TOOLSET)
$(obj).target/drawText.node: $(OBJS) $(obj).target/gyp/freetype.a FORCE_DO_CMD
	$(call do_cmd,solink_module)

all_deps += $(obj).target/drawText.node
# Add target alias
.PHONY: drawText
drawText: $(builddir)/drawText.node

# Copy this to the executable output path.
$(builddir)/drawText.node: TOOLSET := $(TOOLSET)
$(builddir)/drawText.node: $(obj).target/drawText.node FORCE_DO_CMD
	$(call do_cmd,copy)

all_deps += $(builddir)/drawText.node
# Short alias for building this executable.
.PHONY: drawText.node
drawText.node: $(obj).target/drawText.node $(builddir)/drawText.node

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/drawText.node

