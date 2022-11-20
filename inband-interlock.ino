  // QUICK DESIGN FOR INTERLOCKING RUN & INBAND RADIOS AND ANT SWITCHING FOR SHARING SINGLE AMPLIFIER
  // 19th November 2022 by 9A6KX for 9A7DX & 9A5Y team!
  
  // A7 - PTT INPUT RADIO 1
  // A6 - PTT INPUT RADIO 2

static const unsigned int txled1 = 13; // D13 - TX LED RADIO 1
static const unsigned int txled2 = 12; // D12 - TX LED RADIO 2
static const unsigned int relayA = 11; // D11 - RELAY A
static const unsigned int relayB = 10; // D10 - RELAY B
static const unsigned int relayC = 9;  // D9  - RELAY C
static const unsigned int ptt1 = 8;    // D8  - PTT RADIO 1
static const unsigned int ptt2 = 7;    // D7  - PTT RADIO 2
static const unsigned int relayD = 6;  // D6  - RELAY D
static const unsigned int relayE = 5;  // D5  - RELAY E
static const unsigned int ptt_amp = 4; // D4  - PTT AMPLIFIER
static const unsigned int inhibit1= 3; // D3  - INHIBIT RADIO 1
static const unsigned int inhibit2= 2; // D2  - INHIBIT RADIO 2

// SEQUENCER DELAYS - PLEASE READ THIS WITH UNDERSTANDING
unsigned int the_delay = 0;
unsigned int initial_delay = 30;     // 30 ms delay for switching ants / amplifier / radio
/*
You can extend delay if needed - by puting footswitches on both ptt inputs for radio 1 and radio 2 the following way:
1) By pressing PTT input of radio 1 while booting (press footswitch prior than you plug DC power to the board)
   You will add additional 10ms of sequence from relay switchovers to the amplifier and radio PTT - when both TX Leds blink 4 time you can relase footswitch
2) By pressing PTT input of radio 2 while booting (press footswitch prior than you plug DC power to the board)
   You will add additional 20ms of sequence from relay switchovers to the amplifier and radio PTT - when both TX Leds blink 5 time you can relase footswitch
3) By pressing both Radio 1 and Radio 2 PTT intput while booting (press both footswitches prior than you plug DC power to the board)
   You will add additional 20ms of sequence from relay switchovers to the amplifier and radio PTT - when both TX Leds blink 6 time you can relase footswitch
-- You will need to chose delay each time booted as default delay is 30 msec (both TX Leds blink 3 time while booting to indicate 30 ms)

-- The described way allows to adjust delay from 30ms to 40ms, 50ms and even 60ms
-- Tothtsu CX600 12V relay switchover time is 20 msec. Russian REW-14 relay when 27.5V applied also 20msec. Adjust for more if needed.
*/

/*
IMPORTANT NOTES FOR CW:
Set PTT Delay (msec) in N1MM, (DxLog, Win-Test or other) to 47 ms or more - It is used to configure a delay between 
the time the PTT signal is switched and CW sending starts, in order to prevent hot-switching when working CW!
(thats for default delay of 30msec - add more if you extend sequencer delay on the startup!!!)
The default sequence is 30msec for relays and then 15 msec between amp and radio keying, so total of 45 msec.
*/


unsigned int ptt_in_1 = 0;
unsigned int ptt_in_2 = 0;
float voltage1 = 0.0;
float voltage2 = 0.0;

unsigned int radio = 0;

// How much time LED will blink depending on selected delay while "booting" up the mcpu
// 3 - 30ms, 4 - 40ms, 5 - 50ms, 6 - 60ms
void ledBlink(int the_delay){
    for (int i=0; i < (the_delay/10); i++){
      digitalWrite(txled1,HIGH);
      digitalWrite(txled2, HIGH);
      delay(delay);
      digitalWrite(txled1,LOW);
      digitalWrite(txled2,LOW);
    }
}

void setup() {
  Serial.begin(9600); // for debuging purposes

pinMode(13, OUTPUT); digitalWrite(13,LOW);
pinMode(12, OUTPUT); digitalWrite(13,LOW);
pinMode(11, OUTPUT); digitalWrite(13,LOW);
pinMode(10, OUTPUT); digitalWrite(13,LOW);
pinMode(9, OUTPUT); digitalWrite(13,LOW);
pinMode(8, OUTPUT); digitalWrite(13,LOW);
pinMode(7, OUTPUT); digitalWrite(13,LOW);
pinMode(6, OUTPUT); digitalWrite(13,LOW);
pinMode(5, OUTPUT); digitalWrite(13,LOW);
pinMode(4, OUTPUT); digitalWrite(13,LOW);
pinMode(13, OUTPUT); digitalWrite(13,LOW);
pinMode(13, OUTPUT); digitalWrite(13,LOW);

// Determine delay for sequencer bellow

ptt_in_1 = analogRead(A7);
voltage1 = float(ptt_in_1) / 1023 * 5.0;

ptt_in_2 = analogRead(A6);
voltage2 = float(ptt_in_1) / 1023 * 5.0;

  if(voltage1 < 0.5 and voltage2 < 0.5) {
    the_delay = initial_delay;
    ledBlink(the_delay);
  }
  if(voltage1 > 3.4 && voltage2 == 0){
    the_delay = initial_delay + 10;
    ledBlink(the_delay);
  }
  if(voltage1 < 0.5 && voltage2 > 3.4){
    the_delay = initial_delay + 20;
    ledBlink(the_delay);
  }
  if(voltage1 > 3.4 && voltage2 > 3.4){
    the_delay = initial_delay + 10 + 20;
    ledBlink(the_delay);
  }
}

void tx (unsigned int radio_on_tx) {
  unsigned int inhibit = 0;
  unsigned int ptt = 0;
  unsigned int txled = 0;

  if(radio_on_tx==1){ // IF RADIO 1 ENTERS PTT
    inhibit = 2; // INHIBIT RADIO 2
    ptt = 8; // KEY RADIO 1
    txled = 13; // TURN ON TX LED 1
  }
   if(radio_on_tx==2){ // IF RADIO 2 ENTERS PTT
    inhibit = 3; // INHIBIT RADIO 1
    ptt = 7; // KEY RADIO 2
    txled = 11; // TURN ON TX LED 2
  }
  // now enter TX in sequence
  
  // CLICK A BUNCH OF RELAYS
  digitalWrite(inhibit, HIGH);
  digitalWrite(relayE, HIGH);
  if(radio_on_tx==2) {
  digitalWrite(relayD, HIGH); // this is the relay that selects drive
  }
  digitalWrite(relayC, HIGH);
  digitalWrite(relayB, HIGH);
  digitalWrite(relayA, HIGH);
  digitalWrite(txled,HIGH);
  
  delay(the_delay); //after switching all relays delay 30-60ms (as set during boot)
  digitalWrite(ptt_amp,HIGH); // PTT for amplifier
  
  delay(15); // delay 15ms before radio keying 
  // this can be edited, but mostly this can be virtually overriden by logger CW delay as without CW no RF going out from radio
  // maybe readjust (add 5-10ms more) for SSB operations if any problems found or intuition tells you so
  digitalWrite(ptt,HIGH); // key the radio
}

void rx(){
  digitalWrite(inhibit1, LOW);
  digitalWrite(inhibit2, LOW);
  digitalWrite(relayE, LOW);
  digitalWrite(relayD, LOW);
  digitalWrite(relayC, LOW);
  digitalWrite(relayB, LOW);
  digitalWrite(relayA, LOW);
  digitalWrite(txled1,LOW);
  digitalWrite(txled2,LOW);
  digitalWrite(ptt_amp,LOW);
  digitalWrite(ptt1,LOW);
  digitalWrite(ptt2,LOW);
  }


void loop() {

  if(analogRead(A7) > 750) { // check if PTT 1 is pressed
    radio = 1;
    while(analogRead(A7 > 750)){ // enter TX sequence and hold while PTT 1 pressed
      tx(radio);
    }
  }
   if(analogRead(A6) > 750) { // check if PTT 2 is pressed
    radio = 2;
    while(analogRead(A7 > 750)){ // enter TX sequence and hold while PTT 1 is pressed
      tx(radio);
    }
  }
  rx();
}
