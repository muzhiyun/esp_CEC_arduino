#include "CEC_Device.h"

// NodeMCU ESP8266 Pins   bootstrap
// D0  GPIO16  DeepSleep  blue LED connected to 3V3
// D1  GPIO5              <high-Z>
// D2  GPIO4              <high-Z>
// D3  GPIO0              pull-up (SPI boot) / pull-down (UART boot)
// D4  GPIO2   TxD1       pull-up, blue LED on ESP12E module
// D5  GPIO14             <weak pull-up>
// D6  GPIO12             <weak pull-up>
// D7  GPIO13             <weak pull-up>
// D8  GPIO15             pull-down
// D9  GPIO3   RxD0
// D10 GPIO1   TxD0
// CLK GPIO6   SD_CLK
// SD0 GPIO7   SD_D0
// SD1 GPIO8   SD_D1
// SD2 GPIO9   SD_D2
// SD3 GPIO10  SD_D3
// CMD GPIO11  SD_CMD

const uint16_t kCecPin =  12;
#define CEC_DEVICE_TYPE CEC_Device::CDT_PLAYBACK_DEVICE
#define CEC_PHYSICAL_ADDRESS 0x2000

CEC_Device cec_device(kCecPin);

void setup()
{
	pinMode(CEC_GPIO, INPUT_PULLUP);

	Serial.begin(115200);
	cec_device.Initialize(CEC_PHYSICAL_ADDRESS, CEC_DEVICE_TYPE, true); // Promiscuous mode
}

void loop()
{
	if (Serial.available()) {
		unsigned char c = Serial.read();
		unsigned char buffer[3];
    
		switch (c) {
		case '1':
			buffer[0] = 0x36;
			cec_device.TransmitFrame(4, buffer, 1);
			break;
		}
	}
	cec_device.Run();
}
