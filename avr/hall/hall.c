#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdint.h>
#include <inttypes.h>
#include <util/delay.h>

#include <avr/interrupt.h>

#define BAUD 9600
#define MYUBBR F_CPU/16/BAUD/ -1 

#define BUTTON_PORT PORTD
#define BUTTON_PIN PIND
#define BUTTON_BIT PD0

#define LED_PORT PORTB
#define LED_BIT PB0
#define LED_DDR DDRB

#define DEBOUNCE_TIME 10
#define LOCK_INPUT_TIME 100

void delay_ms(uint16_t _ms);
void init_io();
void init_serial();
void init_isr();
int button_is_pressed();
void toggle_led();

char received_char;

void delay_ms(uint16_t _ms){
  while(_ms){
    _delay_ms(1);
    _ms--;
  }
}  

void init_io(){
  LED_DDR = _BV(LED_BIT);
  LED_PORT = _BV(LED_BIT);
  BUTTON_PORT |= _BV(BUTTON_BIT);
  //PORTD |= (1 << PORTD2);
}

void init_isr(){
  //PCMSK |= (1 << PIND2);
  //MCUCR = (1 << ISC01) | (1 << ISC00);
  //GIMSK |= (1 << INT0);
}

void init_serial(){
  //UBRR0H = (MYUBBR >> 8);
  //UBRR0L = MYUBBR;
 
  //UBRR0H = 0;
}

int button_is_pressed(){
  if(bit_is_clear(BUTTON_PIN, BUTTON_BIT)){
    delay_ms(DEBOUNCE_TIME);
    if(bit_is_clear(BUTTON_PIN, BUTTON_BIT)){
      return 1;
    }
  }
  return 0;
}

void toggle_led(){
  LED_PORT ^= _BV(LED_BIT);
}

int main(void){

  init_io(); 
  //init_serial();
  
  UBRR0 = 103;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

  UDR0 = 'a';

  EICRA |= (1 << ISC00);
  EIMSK |= (1 << INT0);

  sei();

  //PORTB = 0xFF;
  
  //while(!(UCSR0A & (1 << UDRE0)))
  //UDR0 = 'a';

  //LED_PORT = 0x01;

  while(1){
    //if(button_is_pressed()){
    //  toggle_led();
    //}
    ;
    //delay_ms(1000);
    //UDR0 = received_char;
  }
}

ISR(USART_RX_vect){
  toggle_led();
  received_char = UDR0;
  UDR0 = received_char;
  delay_ms(50);
  toggle_led();
}

ISR(INT0_vect){
  toggle_led();
  delay_ms(50);
  toggle_led();
}
