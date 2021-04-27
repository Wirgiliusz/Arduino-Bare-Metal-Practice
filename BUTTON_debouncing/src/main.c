#include <avr/io.h>
#include <avr/interrupt.h>

int debounceSwitch();


int main() {
    DDRD &= ~(1 << DDD2);   // PIN D2 (arduino) INPUT
    PORTD |= (1 << PORTD2); // Pull-up

    DDRB |= (1 << DDB5);        // PIN B13 (arduino) OUTPUT
    PORTB &= ~(1 << PORTB5);    // PIN B13 LOW

    TCCR0A |= (1 << WGM01);     // Timer0 mode CTC
    OCR0A = 62;                 // Count value
    TIMSK0 |= (1 << OCIE0A);    // Interrupt enable
    sei();                      // Enable global interrupts
    TCCR0B |= (1 << CS02);      // Prescaler 256 and START


    while (1) {

    }

    return 0;
}

ISR (TIMER0_COMPA_vect) {
    if (debounceSwitch()) {
        PORTB ^= (1 << PORTB5);
    }
}

/* Debounce algorithm with bit-shifting */
int debounceSwitch() {
    static uint16_t state = 0;

    state = (state << 1) | ((PIND & (1 << PIND2)) >> PIND2) | 0xE000;
    if (state == 0xF000) {
        return 1;
    } else {
        return 0;
    }
} 