#ifndef WS2812Serial_h_
#define WS2812Serial_h_

#include <Arduino.h>
#include "DMAChannel.h"

#define WS2812_RGB      0       // The WS2811 datasheet documents this way
#define WS2812_RBG      1
#define WS2812_GRB      2       // Most LED strips are wired this way
#define WS2812_GBR      3
#define WS2812_BRG      4
#define WS2812_BGR      5

class WS2812Serial {
public:
	constexpr WS2812Serial(uint16_t n, void *f, void *d, HardwareSerial &s, uint8_t c) :
		numled(n), config(c),
		frameBuffer((uint8_t *)f), drawBuffer((uint8_t *)d),
		uart( &s == &Serial1 ? &KINETISK_UART0 : nullptr)
	{
	}
	void begin();
	void setPixel(uint32_t num, int color) {
		if (num >= numled) return;
		num *= 3;
		frameBuffer[num+0] = color;
		frameBuffer[num+1] = color >> 8;
		frameBuffer[num+2] = color >> 16;
	}
	void setPixel(uint32_t num, uint8_t red, uint8_t green, uint8_t blue) {
		if (num >= numled) return;
		num *= 3;
		frameBuffer[num+0] = blue;
		frameBuffer[num+1] = green;
		frameBuffer[num+2] = red;
	}
	void show();
	bool busy();
	uint16_t numPixels() {
		return numled;
	}
private:
	const uint16_t numled;
	const uint8_t config;
	uint8_t *frameBuffer;
	uint8_t *drawBuffer;
	//HardwareSerial &serial;
	KINETISK_UART_t *uart;
	DMAChannel *dma = nullptr;

};

#endif