cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lvd0_test)

target_sources(app PRIVATE src/main.c)

if(CONFIG_BOOTLOADER_MCUBOOT)
  set(signed_hex ${ZEPHYR_BINARY_DIR}/zephyr.signed.hex)
  set(signed_confirmed_hex ${ZEPHYR_BINARY_DIR}/zephyr.signed.confirmed.hex)

  dt_nodelabel(slot0_node NODELABEL "slot0_partition" REQUIRED)
  dt_nodelabel(slot1_node NODELABEL "slot1_partition" REQUIRED)

  dt_reg_addr(slot0_address PATH ${slot0_node})
  dt_reg_addr(slot1_address PATH ${slot1_node})
  
  math(EXPR slot1_offset "${slot1_address} - ${slot0_address}" OUTPUT_FORMAT HEXADECIMAL)

  add_custom_target(bank_images ALL
    COMMAND ${CMAKE_COMMAND} -E copy ${signed_hex} ${ZEPHYR_BINARY_DIR}/app_bank0.hex
    COMMAND ${CMAKE_OBJCOPY} -I ihex -O ihex --change-addresses ${slot1_offset}
            ${signed_hex} ${ZEPHYR_BINARY_DIR}/app_bank1.hex
    COMMAND ${CMAKE_COMMAND} -E copy ${signed_confirmed_hex} ${ZEPHYR_BINARY_DIR}/app_bank0_confirmed.hex
    COMMAND ${CMAKE_OBJCOPY} -I ihex -O ihex --change-addresses ${slot1_offset}
            ${signed_confirmed_hex} ${ZEPHYR_BINARY_DIR}/app_bank1_confirmed.hex
  )
  add_dependencies(bank_images ${logical_target_for_zephyr_elf})
endif()