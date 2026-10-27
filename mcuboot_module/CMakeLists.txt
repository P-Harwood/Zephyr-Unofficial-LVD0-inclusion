zephyr_compile_definitions(BSP_CFG_OPTION_SETTING_OFS1_SEC=0xFFFFFDFBU)
zephyr_linker_sources(SECTIONS ofs1_sec.ld)

if(CONFIG_BOOT_IMAGE_JUMP_HOOKS)
  zephyr_library()
  zephyr_library_link_libraries(MCUBOOT_BOOTUTIL)
endif()