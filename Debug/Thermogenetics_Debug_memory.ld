/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2025
 * Generated linker script file for MKL02Z32xxx4
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.4.1 [Build 6260] [2021-09-15] on Oct 10, 2025, 4:36:31 PM
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH (rx) : ORIGIN = 0x0, LENGTH = 0x8000 /* 32K bytes (alias Flash) */  
  SRAM (rwx) : ORIGIN = 0x1ffffc00, LENGTH = 0x1000 /* 4K bytes (alias RAM) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x0  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x0 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x0 + 0x8000 ; /* 32K bytes */  
  __top_Flash = 0x0 + 0x8000 ; /* 32K bytes */  
  __base_SRAM = 0x1ffffc00  ; /* SRAM */  
  __base_RAM = 0x1ffffc00 ; /* RAM */  
  __top_SRAM = 0x1ffffc00 + 0x1000 ; /* 4K bytes */  
  __top_RAM = 0x1ffffc00 + 0x1000 ; /* 4K bytes */  
