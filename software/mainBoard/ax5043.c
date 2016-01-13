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
#define CHUNK_HEAD_LEN_SHIFT 5
#define CHUNK_HEAD_LEN_0 (0x0) << CHUNK_HEAD_LEN_SHIFT
#define CHUNK_HEAD_LEN_1 (0x1) << CHUNK_HEAD_LEN_SHIFT
#define CHUNK_HEAD_LEN_2 (0x2) << CHUNK_HEAD_LEN_SHIFT
#define CHUNK_HEAD_LEN_3 (0x3) << CHUNK_HEAD_LEN_SHIFT
#define CHUNK_HEAD_LEN_VAR_LEN (0x7) << CHUNK_HEAD_LEN_SHIFT
/* If the length is variable, the next byte is the length, I think.*/ 
#define CHUNK_HEAD_NOP 0x00 /* A NOP. Receiver will not send NOP. */ 
#define CHUNK_HEAD_RSSI 0x31  /* Indicates that the next 1 byte will be RSSI.*/ 
#define CHUNK_HEAD_TXCTRL 0x3C /* Transmit control data*/ 
#define CHUNK_HEAD_FREQOFFS 0x52 /* Reciever Gen, see TRKFREQ*/ 
#define CHUNK_HEAD_ANTRSSI2 0x55 /* See RSSI register, includes BGNDNOISE*/ 
#define CHUNK_HEAD_REPEATDATA 0x62 /* Allows data to be repeated. Constructing preamble*/ 
#define CHUNK_HEAD_TIMER 0x70  /* Contains a copy of the us register. Freq hopping*/ 
#define CHUNK_HEAD_RFFREQOFFS 0x73 /* See TRKRFFREQ*/ 
#define CHUNK_HEAD_DATARATE 0x74  /* Gen by rec. See TRKDATARATE*/ 
#define CHUNK_HEAD_ANTRSSI3 0x75/* Gen by rec. See RSSI. Encodes ant 0,1,bgnd*/ 
#define CHUNK_HEAD_DATA 0xE1 /* Actual data. */ 
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


#define CHUNK_HEAD_TXPWR 0xFD /* Allows the TX power to be changed on the fly. */ 



#define PWRMODE_POWERDOWN 0x00 /* All circuits dead. Except the register. */ 
#define PWRMODE_DEEPSLEEP 0x01 /* Now I really mean all circuits are dead. Data loss*/ 
#define PWRMODE_STANDBY 0x05 /* Xtal OSC enabled*/ 
#define PWRMODE_FIFOON 0x07  /* The FIFO and the crystal are enabled*/ 
#define PWRMODE_SYNTHRX 0x08 /* The synth is running, in receive mode*/ 
#define PWRMODE_FULLRX 0x09 /* The receiver is running*/ 
#define PWRMODE_WORRX 0x0B /* Wake on radio mode*/ 
#define PWRMODE_SYNTHTX 0x0C /* The synth is running, transmit mode*/ 
#define PWRMODE_FULLTX 0x0D /* The transmitter is running. */ 

int ax_full_tx(){
	ax5043_sel();
	 /* Need to put into full tx
	  * Need to wait untill SVMODEM is high in the POWSTAT*/ 
}

int ax_autorange(){
	/* This is needed if the frequency is changed more than 1MHz. 
	 * Each frequency must be ranged, FREQA and B. 
	 * Set power mode ta standby, enable TXCO
	 * Wait until the osc is ready
	 * Set RNGSTART of PLLRANGINGA/B
	 * wait until RNGSTART = 0
	 * If RNGERR == 1, error
	 * esle set pwrmode to desired. */ 
}
int ax_send_data(char* tx_data, int len){
	/* Set pwrmode to fulltx
	 * enable tcxo
	 * write pramble
	 * write packet
	 * wait for osc
	 * commit fifo
	 * wat for xmit to complete
	 * set power mode*/ 
}
int ax_read_packet(char* rx_data, int max){
	 /* Assumes a packet is ready and waiting
	  * reads the header
	  * reads the data until max len or data all read
	  * empty the fifo if max is reached. */ 
}
void ax_wr8reg(struct ax_driver_s, uint16_t reg, uint8_t data);
void ax_wr16reg(struct ax_driver_s, uint16_t reg, uint16_t data);
