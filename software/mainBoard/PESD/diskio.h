/*-----------------------------------------------------------------------
/  Low level disk interface module include file   (C)ChaN, 2010
/-----------------------------------------------------------------------*/

#ifndef _DISKIO

#define _READONLY  _FS_READONLY  /* 1: Remove write functions */
#define _USE_IOCTL  1  /* 1: Use disk_ioctl function */

#include "integer.h"

/* << EST added */
#define CT_SD1   (1<<0) /* LDD_SDHC_SD, Secure Digital memory card */
#define CT_SD2   (1<<1) /* LDD_SDHC_SDIO, Secure Digital IO card */
#define CT_BLOCK (1<<2)
#define CT_MMC   (1<<3) /* LDD_SDHC_MMC, MultiMediaCard memory card */
#define CT_SDC   (1<<4) /* LDD_SDHC_SDCOMBO, Combined Secure Digital memory and IO card */
#define CT_ATA   (1<<5) /* LDD_SDHC_CE_ATA, Consumer Electronics ATA card */

/* Status of Disk Functions */
typedef uint8_t  DSTATUS;

/* Results of Disk Functions */
typedef enum {
  RES_OK = 0,           /* 0: Successful */
  RES_ERROR,    	/* 1: R/W Error */
  RES_WRPRT,            /* 2: Write Protected */
  RES_NOTRDY,           /* 3: Not Ready */
  RES_PARERR,           /* 4: Invalid Parameter */
  RES_NOT_ENOUGH_CORE   /* 5: Not enough heap memory */
} DRESULT;


/*---------------------------------------*/
/* Prototypes for disk control functions */

int assign_drives (int, int);
DSTATUS disk_initialize (uint8_t);
DSTATUS disk_status (uint8_t);
DRESULT disk_read (uint8_t, uint8_t*, uint32_t, uint8_t);
#if  _READONLY == 0
DRESULT disk_write (uint8_t, const uint8_t*, uint32_t, uint8_t);
#endif
DRESULT disk_ioctl (uint8_t, uint8_t, void*);



/* Disk Status Bits (DSTATUS) */

#define STA_NOINIT    0x01  /* Drive not initialized */
#define STA_NODISK    0x02  /* No medium in the drive */
#define STA_PROTECT    0x04  /* Write protected */


/* Command code for disk_ioctrl function */

/* Generic command (defined for FatFs) */
#define CTRL_SYNC      0  /* Flush disk cache (for write functions) */
#define GET_SECTOR_COUNT  1  /* Get media size (for only f_mkfs()) */
#define GET_SECTOR_SIZE    2  /* Get sector size (for multiple sector size (_MAX_SS >= 1024)) */
#define GET_BLOCK_SIZE    3  /* Get erase block size (for only f_mkfs()) */
#define CTRL_ERASE_SECTOR  4  /* Force erased a block of sectors (for only _USE_ERASE) */

/* Generic command */
#define CTRL_POWER    5  /* Get/Set power status */
#define CTRL_LOCK    6  /* Lock/Unlock media removal */
#define CTRL_EJECT    7  /* Eject media */

/* MMC/SDC specific ioctl command */
#define MMC_GET_TYPE    10  /* Get card type */
#define MMC_GET_CSD    11  /* Get CSD */
#define MMC_GET_CID    12  /* Get CID */
#define MMC_GET_OCR    13  /* Get OCR */
#define MMC_GET_SDSTAT    14  /* Get SD status */

/*<< EST added: */
#define MMC_GET_SDC_VERSION     15  /* 1 byte */
#define MMC_GET_READ_BL_LEN     16  /* 2 bytes */
#define MMC_GET_DRIVER_VERSION  17  /* 1 byte: return: 0 SPI driver, 1 LLD SDHC driver */
#define MMC_GET_LLD_INFO        18  /* array: 1 byte subcommand, 1 byte bufSize, bufSize*bytes */
  #define MMC_GET_LLD_CMD_HIGH_CAPACITY  0 /* return 1 byte, 0 for no, 1 for yes */
  #define MMC_GET_LLD_CMD_HIGH_SPEED     1 /* return 1 byte, 0 for no, 1 for yes */
  #define MMC_GET_LLD_CMD_LOW_VOLTAGE    2 /* return 1 byte, 0 for no, 1 for yes */
  #define MMC_GET_LLD_CMD_DATA_WIDTHS    3 /* return 1 byte (bitset), 0x1: 1, 0x2: 4, 0x4: 8 */
  #define MMC_GET_LLD_CMD_OPERATIONS     4 /* return 1 byte (bitset), 0x1: block read, 0x2: block write, 0x4: block erase, 0x8: write protection, 0x10: I/O */

/* ATA/CF specific ioctl command */
#define ATA_GET_REV    20  /* Get F/W revision */
#define ATA_GET_MODEL    21  /* Get model name */
#define ATA_GET_SN    22  /* Get serial number */

/* NAND specific ioctl command */
#define NAND_FORMAT    30  /* Create physical format */


#define _DISKIO
#endif

