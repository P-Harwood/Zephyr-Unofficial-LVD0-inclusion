cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lvd0_test)


zephyr_compile_definitions(BSP_CFG_OPTION_SETTING_OFS1_SEC=0xFFFFFDFBU)
zephyr_linker_sources(SECTIONS ofs1_sec.ld)

target_sources(app PRIVATE src/main.c)