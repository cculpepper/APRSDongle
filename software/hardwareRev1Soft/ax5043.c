/* AX5043 library. 
 * Should provide all initialization and control
 * functionality for the AX5043 radio IC. */ 


int ax5043_power_up(){
	 /* Need to borrow the SPI pins
	  * and select the 5043 until the MISO -> 1*/
	int count;
	int ret;
	count = 0; 
	MISO_PT.pcr[MISO] = MISO_GPIO_SEL;
	MISO_PORT->PDDR |=  (1<<MISO);
	ax5043_sel();
	while(((MISO_PORT->PDIR && (1<<MISO) ) == 0) & (count++ < PWR_UP_TIMEOUT));
	if ((MISO_PORT->PDIR && (1<<MISO)) == 0){
		 /* Then we cant get it to power up. */ 
		ret = 1;
	} else {
		ret = 0;
	}
	ax5043_desel();
	MISO_PT.pcr[MISO] = MISO_SPI_SEL;
}
int spi_send(char[] tx_data, char[] rx_data, int num_bytes);
/* The chenk of data has a header.
 * In this header, there was a byte (first byte)
 * And in that byte, there was a length (upper 3 bits)
 * And in that len, there are invalids (100, 101, and 110)*/ 
CHUNK_HEAD_LEN_SHIFT 5
CHUNK_HEAD_LEN_0 (0x0) << CHUNK_HEAD_LEN_SHIFT
CHUNK_HEAD_LEN_1 (0x1) << CHUNK_HEAD_LEN_SHIFT
CHUNK_HEAD_LEN_2 (0x2) << CHUNK_HEAD_LEN_SHIFT
CHUNK_HEAD_LEN_3 (0x3) << CHUNK_HEAD_LEN_SHIFT
CHUNK_HEAD_LEN_VAR_LEN (0x7) << CHUNK_HEAD_LEN_SHIFT
/* If the length is variable, the next byte is the length, I think.*/ 
CHUNK_HEAD_NOP 0x00 /* A NOP. Receiver will not send NOP. */ 
CHUNK_HEAD_RSSI 0x31  /* Indicates that the next 1 byte will be RSSI.*/ 
CHUNK_HEAD_TXCTRL 0x3C /* Transmit control data*/ 
CHUNK_HEAD_FREQOFFS 0x52 /* Reciever Gen, see TRKFREQ*/ 
CHUNK_HEAD_ANTRSSI2 0x55 /* See RSSI register, includes BGNDNOISE*/ 
CHUNK_HEAD_REPEATDATA 0x62 /* Allows data to be repeated. Constructing preamble*/ 
CHUNK_HEAD_TIMER 0x70  /* Contains a copy of the us register. Freq hopping*/ 
CHUNK_HEAD_RFFREQOFFS 0x73 /* See TRKRFFREQ*/ 
CHUNK_HEAD_DATARATE 0x74  /* Gen by rec. See TRKDATARATE*/ 
CHUNK_HEAD_ANTRSSI3 0x75/* Gen by rec. See RSSI. Encodes ant 0,1,bgnd*/ 
CHUNK_HEAD_DATA 0xE1 /* Actual data. */ 
/* Length is 1st byte after header.  Includes actual data and flag bits
 * Transmit data format:
 * byte after length is the flags. 
 * bit 5: Raw. Set to one to bypas the framing mode
 * bit 4: UNENC: Set to bypass framing and encoder, except for inversion
 * bit 3: NOCRC: Set to bypass the generation of CRC. 
 * bit 2: RESIDUE: Allows for sending less than 8 bits on the last byte
 * bit 1: PKTEND: Allows for data greater than the size of the FIFO 
 * 	to be sent.
 * bit 0: PKTSTART: See bit 1. 
 * 
 * Receive Format:
 * Bit 6: ABORT: indicates if the packet was aborted. 
 * Bit 5: SIZEFAIL: set if the packet does not pass size checks. 
 * Bit 4: ADDR fail: Set if the packet doesnt match the address check. 
 * Bit 3: CRCFAIL
 * Bit 2-0: See bits 2-0 of the tx format. */ 


CHUNK_HEAD_TXPWR 0xFD /* Allows the TX power to be changed on the fly. */ 



