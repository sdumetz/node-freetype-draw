# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := libfreetype
DEFS_Debug := \
	'-DNODE_GYP_MODULE_NAME=libfreetype' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DOPENSSL_NO_PINSHARED' \
	'-DFT2_BUILD_LIBRARY' \
	'-DFT_CONFIG_OPTION_ERROR_STRINGS' \
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
	-fno-exceptions \
	-std=gnu++1y

INCS_Debug := \
	-I/home/sebastien/.node-gyp/10.20.1/include/node \
	-I/home/sebastien/.node-gyp/10.20.1/src \
	-I/home/sebastien/.node-gyp/10.20.1/deps/uv/include \
	-I/home/sebastien/.node-gyp/10.20.1/deps/v8/include \
	-I$(srcdir)/vendor/freetype/include

DEFS_Release := \
	'-DNODE_GYP_MODULE_NAME=libfreetype' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DOPENSSL_NO_PINSHARED' \
	'-DFT2_BUILD_LIBRARY' \
	'-DFT_CONFIG_OPTION_ERROR_STRINGS'

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
	-fno-exceptions \
	-std=gnu++1y

INCS_Release := \
	-I/home/sebastien/.node-gyp/10.20.1/include/node \
	-I/home/sebastien/.node-gyp/10.20.1/src \
	-I/home/sebastien/.node-gyp/10.20.1/deps/uv/include \
	-I/home/sebastien/.node-gyp/10.20.1/deps/v8/include \
	-I$(srcdir)/vendor/freetype/include

OBJS := \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftsystem.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftinit.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftdebug.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftbase.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftbbox.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftglyph.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftbdf.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftbitmap.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftcid.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftfstype.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftgasp.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftgxval.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftlcdfil.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftmm.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftotval.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftpatent.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftpfr.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftstroke.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftsynth.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/fttype1.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/base/ftwinfnt.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/bdf/bdf.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/cff/cff.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/cid/type1cid.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/pcf/pcf.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/pfr/pfr.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/sfnt/sfnt.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/truetype/truetype.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/type1/type1.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/type42/type42.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/winfonts/winfnt.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/raster/raster.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/smooth/smooth.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/autofit/autofit.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/cache/ftcache.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/gzip/ftgzip.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/lzw/ftlzw.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/bzip2/ftbzip2.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/gxvalid/gxvalid.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/otvalid/otvalid.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/psaux/psaux.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/pshinter/pshinter.o \
	$(obj).target/$(TARGET)/vendor/freetype/src/psnames/psnames.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

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

$(obj).target/gyp/freetype.a: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/gyp/freetype.a: LIBS := $(LIBS)
$(obj).target/gyp/freetype.a: TOOLSET := $(TOOLSET)
$(obj).target/gyp/freetype.a: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,alink)

all_deps += $(obj).target/gyp/freetype.a
# Add target alias
.PHONY: libfreetype
libfreetype: $(obj).target/gyp/freetype.a

# Add target alias to "all" target.
.PHONY: all
all: libfreetype

# Add target alias
.PHONY: libfreetype
libfreetype: $(builddir)/freetype.a

# Copy this to the static library output path.
$(builddir)/freetype.a: TOOLSET := $(TOOLSET)
$(builddir)/freetype.a: $(obj).target/gyp/freetype.a FORCE_DO_CMD
	$(call do_cmd,copy)

all_deps += $(builddir)/freetype.a
# Short alias for building this static library.
.PHONY: freetype.a
freetype.a: $(obj).target/gyp/freetype.a $(builddir)/freetype.a

# Add static library to "all" target.
.PHONY: all
all: $(builddir)/freetype.a

