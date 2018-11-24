/******************************************************************************
 * @file pmod_custom_i2c.c
 *
 * IOP code (MicroBlaze) for custom I2C communication
 * returning the number of bytes transferred.
 *****************************************************************************/

#include "circular_buffer.h"
#include "timer.h"
#include "i2c.h"

// Mailbox commands
#define CONFIG_IOP_SWITCH       0x1
#define GET_VALUE            0xD
#define RESET                   0xF

#define INA219_DEFAULT_ADDRESS 0x40

static i2c device;

static uint8_t customAddr;

// Byte operations

void iic_custom_writeByte(uint8_t devAddr)
{
   uint8_t temp[3];
   temp[0] = 0;
   temp[1] = 80;
   temp[2] = 0;
   i2c_write(device, devAddr, temp, 3);
}

int iic_custom_readByte(uint8_t devAddr, uint8_t *data)
{
   uint32_t len = 0xAA;
   len = i2c_read(device, devAddr, data, 2);
   return len;
}

void custom_init() {
   // device setup
   customAddr = INA219_DEFAULT_ADDRESS;
}

void custom_reset()
{	
}

unsigned int custom_getValue()
{
   uint8_t data[2];
   uint32_t len = 0xAA;
   iic_custom_writeByte(customAddr);
   len = iic_custom_readByte(customAddr, &data[0]);
   return len;
}

int main()
{
   int cmd;
   u32 scl, sda;

   // Initialization
   device = i2c_open(3, 7);
   custom_init();

   // Run application
   while(1) {
     // wait and store valid command
      while((MAILBOX_CMD_ADDR & 0x01)==0);
      cmd = MAILBOX_CMD_ADDR;

      switch(cmd) {
         case CONFIG_IOP_SWITCH:
            // read new pin configuration
            scl = MAILBOX_DATA(0);
            sda = MAILBOX_DATA(1);
            device = i2c_open(sda, scl);
            custom_init();
            MAILBOX_CMD_ADDR = 0x0;
            break;
            
         case GET_VALUE:
            MAILBOX_DATA(0) = custom_getValue();
            MAILBOX_CMD_ADDR = 0x0; 
            break;
            
         case RESET:
            //custom_reset();
            MAILBOX_CMD_ADDR = 0x0; 
            break;
            
         default:
            MAILBOX_CMD_ADDR = 0x0;
            break;
      }
   }
   return 0;
}
