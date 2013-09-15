include $(TOPDIR)/rules.mk

PKG_NAME:=sysuh3c-cgi
PKG_VERSION:=0.2
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
        SECTION:=utils
        CATEGORY:=Utilities
        DEPENDS:=+libc +libgcc +uhttpd +sysuh3c
        TITLE:=sysuh3c-cgi
        PKGARCH:=ramips
        MAINTAINER:=zonyitoo
endef

define Package/$(PKG_NAME)/description
      	CGI for SYSUH3C.
endef

#非本目录下的源码文件, 拷贝到此相应目录下.
# 如../../xucommon/xucommon.c, 则将 xucommon.c 拷贝到此目录下的源码的 ../../ 
define Build/Prepare
		mkdir -p $(PKG_BUILD_DIR)
		$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

#define Build/Configure
#endef

#define Build/Compile
#	$(MAKE) -C $(PKG_BUILD_DIR) \
#		LIBS="-nodefaultlibs -lgcc -lc -luClibc++" \
#		LDFLAGS="$(EXTRA_LDFLAGS)" \
#		CXXFLAGS="$(TARGET_CFLAGS) $(EXTRA_CPPFLAGS) -nostdinc++" \
#		$(TARGET_CONFIGURE_OPTS) \
#		CROSS="$(TARGET_CROSS)" \
#		ARCH="$(ARCH)" \
#		$(1);
#endef

#define Package/$(PKG_NAME)/conffiles
#[升级时保留文件/备份时备份文件 一个文件一行]
#endef

define Package/$(PKG_NAME)/install
		$(INSTALL_DIR) $(1)/www
		$(CP) $(PKG_BUILD_DIR)/index.html $(1)/www
		$(INSTALL_DIR) $(1)/www/cgi-bin
		$(INSTALL_BIN) $(PKG_BUILD_DIR)/sysuh3c.cgi $(1)/www/cgi-bin
		$(INSTALL_BIN) $(PKG_BUILD_DIR)/sysuh3c-login $(1)/www/cgi-bin
		$(INSTALL_BIN) $(PKG_BUILD_DIR)/sysuh3c-logoff $(1)/www/cgi-bin
		$(INSTALL_DIR) $(1)/www/sysuh3c-cgi
		$(CP) $(PKG_BUILD_DIR)/sysuh3c-cgi/* $(1)/www/sysuh3c-cgi/
endef

define Package/$(PKG_NAME)/preinst
[安装前执行的脚本 记得加上#!/bin/sh 没有就空着]
	#!/bin/sh
	rm -rf /www/sysuh3c-cgi
	exit 0
endef

#define Package/$(PKG_NAME)/postinst
#[安装后执行的脚本 记得加上#!/bin/sh 没有就空着]
#    #!/bin/sh
#     rm -f /tmp/luci-indexcache
#    exit 0
#endef

#define Package/$(PKG_NAME)/prerm
#		#!/bin/sh
#		if [ -f /tmp/sysuh3c.lock ]; then
#			cat /tmp/sysuh3c.lock | while read sysuh3c_LOCK; do kill -int $sysuh3c_LOCK; done
#			rm -f /tmp/sysuh3c.lock
#		fi
#endef

#Package/$(PKG_NAME)/postrm
#[删除后执行的脚本 记得加上#!/bin/sh 没有就空着]
#endef

$(eval $(call BuildPackage,$(PKG_NAME)))
