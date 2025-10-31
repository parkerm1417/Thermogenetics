#include "Well.h"

struct Well Wells[2] = {{true,5,0xFFFF,TEMP1_ADDRESS,43,BOARD_INITPINS_GATE1_GPIO,BOARD_INITPINS_GATE1_PIN},{true,5,0xFFFF,TEMP2_ADDRESS,43,BOARD_INITPINS_GATE2_GPIO,BOARD_INITPINS_GATE2_PIN}};


void Well_Heat(struct Well _Well){
	GPIO_PortClear(_Well.GPIOBase, 1 << _Well.GPIOPin);
}

void Well_Cool(struct Well _Well){
	GPIO_PortSet(_Well.GPIOBase, 1 << _Well.GPIOPin);
}
