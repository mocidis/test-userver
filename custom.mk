CROSS_COMPILE:=2

ARMV7L:=1
LINUX_X86:=2
LINUX_X86_64:=3
MINGW_X86:=4
MACOS_X86_64:=5
ifeq ($(CROSS_COMPILE),$(ARMV7L))
	CROSS_TOOL:=arm-linux-gnueabihf-gcc
	LIBS_DIR:=../libs/linux-armv7l
endif
ifeq ($(CROSS_COMPILE),$(LINUX_X86))
	CROSS_TOOL:=gcc
	LIBS_DIR:=../libs/linux-i686
    LIBS:=-ljson-c -lcrypto
endif
ifeq ($(CROSS_COMPILE),$(LINUX_X86_64))
	CROSS_TOOL:=gcc
	LIBS_DIR:=../libs/linux-x86_64
    LIBS:=-ljson-c -lcrypto
endif
ifeq ($(CROSS_COMPILE),$(MINGW_X86))
	CROSS_TOOL:=gcc
	LIBS_DIR:=../libs/mingw32-i586
endif
ifeq ($(CROSS_COMPILE),$(MACOS_X86_64))
	CROSS_TOOL:=gcc
	LIBS_DIR:=../libs/darwin-x86_64
    LIBS:=../libs/darwin-x86_64/lib/libjson-c.a -lcrypto

endif
PKG_PATH:=`pwd`/$(LIBS_DIR)/lib/pkgconfig
LIBS+=$(shell PKG_CONFIG_PATH=$(PKG_PATH) pkg-config --libs libpjproject)
