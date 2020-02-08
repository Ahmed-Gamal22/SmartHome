/*
 * bit_handle.h
 *
 * Created: 10/12/2019 03:20:34 
 *  Author: cisco126
 */ 


#ifndef BIT_HANDLE_H_
#define BIT_HANDLE_H_

/*individual Bit -> for specific bit number */
#define setBit(REG,BitNumber)	 REG |=  (1<<(BitNumber))		
#define clearBit(REG,BitNumber)	 REG &= ~(1<<(BitNumber))
#define ToggleBit(REG,BitNumber) REG ^=  (1<<(BitNumber))

/*Group of bits -> for specific bit mask(bits) */
#define setMBits(REG,BitMask)		 REG |=  (BitMask)
#define clearMBits(REG,BitMask)		 REG &= ~(BitMask)
#define ToggleMBits(REG,BitMask)	 REG ^=  (BitMask)

/*for all bits */
#define setAllBits(REG)			 REG =   0xFF;
#define clearAllBits(REG)		 REG =   0x00;
#define ToggleAllBits(REG)	     REG ^=  0xFF;

/*get specific bit ->  */
#define getBit(REG,BitNumber)	((REG>>(BitNumber))&0x01)

#endif /* BIT_HANDLE_H_ */