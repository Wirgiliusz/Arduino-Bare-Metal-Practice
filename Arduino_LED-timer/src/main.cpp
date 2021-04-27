#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000

ISR (TIMER0_COMPA_vect) {
    static volatile int interrupt_count = 0;
    
    if (interrupt_count >= 125) {
        PORTB ^= (1 << PORTB5); // Toggle LED PIN
        interrupt_count = 0;
    }

    interrupt_count++;
}

int main() {
    DDRB |= (1 << DDB5);    //  PB5 as output
    PORTB |= (1 << PORTB5); // Toggle LED PIN

    TCCR0A |= (1 << WGM01); // Timer 0 in CTC mode
    OCR0A = 249;            // Count value

    sei();                      // Enable global interrupts
    TIMSK0 |= (1 << OCIE0A);    // Enable interrupt for timer

    TCCR0B |= (1 << CS02); // clk/256 prescaler + START

    while (1) {
        
    }

    return 0;
}