#include <avr/io.h>

void delay(unsigned long int time) {
    volatile int a = 0;
    for (unsigned long int i = 0; i < time; ++i) {
        a++;
    }
}


int main() {
    DDRB |= (1 << DDB5);
    PORTB &= ~(1 << PORTB5);
    //PINB |= (1 << PINB5);

    while(1) {
        //PINB |= (1 << PINB5); // Writing 1 to PINB5 toggles PORTB5
        PORTB ^= (1 << PORTB5);
        delay(100000);
    }

    return 0;
}