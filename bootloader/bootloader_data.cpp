#include "bootloader.h"

// TODO: real jrk names in this file

enum bootloader_type_ids
{
  ID_NONE = 0,
  ID_JRK_2017_BOOTLOADER,
  ID_JRK_2017_APP,
};

const std::vector<bootloader_app_type> bootloader_app_types = {
  {
    /* id */ ID_JRK_2017_APP,
    /* usb_vendor_id */ 0x1FFB,
    /* usb_product_id */ 0x00B7,
    /* name */ "Pololu Jrk 2017",
    /* composite */ true,
    /* interface_number */ 0,
  },
};

const std::vector<bootloader_type> bootloader_types = {
  {
    /* id */ ID_JRK_2017_BOOTLOADER,
    /* usb_vendor_id */ 0x1FFB,
    /* usb_product_id */ 0x00B6,
    /* name */ "Jrk 2017 Bootloader",
    /* short_name */ "2017",
    /* app_address */ 0x2000,
    /* app_size */ 0x6000,
    /* write_block_size */ 0x40,
    /* erasing_flash_affects_eeprom */ true,
    /* supports_plain_flash_writing */ false,
    /* supports_flash_reading */ false,
    /* eeprom_address */ 0,
    /* eeprom_address_hex_file */ 0xF00000,
    /* eeprom_size */ 0x100,
    /* supports_eeprom_access */ true,
    /* device_code */ NULL,
    /* matching_app_types */ { ID_JRK_2017_APP },
  },
};