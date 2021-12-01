include $(TOPDIR)/rules.mk

PKG_NAME:=ibm_program
PKG_RELEASE:=1
PKG_VERSION:=1.0.0

include $(INCLUDE_DIR)/package.mk

define Package/ibm_program
	CATEGORY:=Base system
	TITLE:=ibm_program
	DEPENDS:=+libubus +libubox +libblobmsg-json +libibm +luci-app-ibm
endef

define Package/ibm_program/description
	This is a ibm app package
endef

define Package/ibm_program/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ibm_program $(1)/usr/bin
	$(INSTALL_BIN) ./files/ibm_conf.init $(1)/etc/init.d/ibm_conf
	$(INSTALL_CONF) ./files/ibm_conf.config $(1)/etc/config/ibm_conf
endef

$(eval $(call BuildPackage,ibm_program))
