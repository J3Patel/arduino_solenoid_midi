// Play a file from the SD card in looping mode, from the SD card.
// Example program to demonstrate the use of the MIDFile library
//
// Hardware required:
//  SD card interface - change SD_SELECT for SPI comms
 
#include <SdFat.h>
#include <MD_MIDIFile.h>

#define DEBUGS(s)     Serial.print(s)
#define DEBUG(s, x)   { Serial.print(F(s)); Serial.print(x); }
#define DEBUGX(s, x)  { Serial.print(F(s)); Serial.print(x, HEX); }
#define SERIAL_RATE 57600

#define  SD_SELECT  4

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

const char *loopfile = "blvr6.mid";  // simple and short file

SdFat	SD;
MD_MIDIFile SMF;

int cymbal1Pin = 2;
int cymbal2Pin = 3; //3

int tom1Pin = 4;
int tom2Pin = 5;
int tom3Pin = 6;
int tom4Pin = 7;

int snarePin = 8;

int basePin = 9;

int clapPin = 10;

int hiHatPin = 11;
int hiHatOpenPin = 12;

int ridePin = 1; //13


unsigned long cymbal1PinTime = 0;
unsigned long cymbal2PinTime = 0;

unsigned long tom1PinTime = 0;
unsigned long tom2PinTime = 0;
unsigned long tom3PinTime = 0;
unsigned long tom4PinTime = 0;

unsigned long snarePinTime = 0;

unsigned long basePinTime = 0;

unsigned long clapPinTime = 0;

unsigned long hiHatPinTime = 0;
unsigned long hiHatOpenPinTime = 0;

unsigned long ridePinTime = 0;





boolean cymbal1PinFlag = false;
boolean cymbal2PinFlag = false;

boolean tom1PinFlag = false;
boolean tom2PinFlag = false;
boolean tom3PinFlag = false;
boolean tom4PinFlag = false;

boolean snarePinFlag = false;

boolean basePinFlag = false;

boolean clapPinFlag = false;

boolean hiHatPinFlag = false;
boolean hiHatOpenPinFlag = false;

boolean ridePinFlag = false;


void midiCallback(midi_event *pev)
{
//  DEBUG("\nM T", pev->track);
//  DEBUG(":  Ch ", pev->channel+1);
//  DEBUGS(" Data");
//  
  int note = pev->data[1];
  int velocity = pev->data[2];
  int mDelay = pev->channel;
//
 DEBUG(" ", mDelay);
  DEBUG(" ", note);
  DEBUG(" ", velocity);
  Serial.println("");
//  delay(mDelay);
  switch(note) {
    case 35:
    setBase(velocity != 0);
    break;


    case 41:
    setTom4(velocity != 0);
    break;
    
    case 39:
    setClap(velocity != 0);
    break;

    case 40:
    setSnare(velocity != 0);
    break;

    
    case 47:
    setTom1(velocity != 0);
    break;

    case 45:
    setTom2(velocity != 0);
    break;

    case 43:
    setTom3(velocity != 0);
    break;

    

    case 52:
    setCymbal1(velocity != 0);
    break;

    case 49:
    setCymbal2(velocity != 0);
    break;

    case 33:
    setHiHat(velocity != 0);
    break;
    
    case 31:
    setHiHatOpen(velocity != 0);
    break;

    case 28:
    setRide(velocity != 0);
    break;
    
  }  
}

void setBase(bool on) {
  if (on) {
    basePinTime = millis();
    basePinFlag = true;
    digitalWrite(basePin, LOW);    
  }
}

void setSnare(bool on) {
  if (on) {
    snarePinTime = millis();
    snarePinFlag = true;
    digitalWrite(snarePin, LOW);    
  }
}

void setHiHat(bool on) {
  if (on) {
    hiHatPinFlag = true;
    hiHatPinTime = millis();
    digitalWrite(hiHatPin, LOW);    
  }
}

void setCymbal1(bool on) {
  if (on) {
    cymbal1PinFlag = true;
    cymbal1PinTime = millis();
    digitalWrite(cymbal1Pin, LOW);    
  }
}

void setCymbal2(bool on) {
  if (on) {
    cymbal2PinFlag  = true;
    cymbal2PinTime = millis();
    digitalWrite(cymbal2Pin, LOW);    
  }
}

void setTom1(bool on) {
  if (on) {
    tom1PinFlag = true;
    tom1PinTime = millis();
    digitalWrite(tom1Pin, LOW);    
  }
}

void setTom2(bool on) {
  if (on) {
    tom2PinFlag = true;
    tom2PinTime = millis();
    digitalWrite(tom2Pin, LOW);    
  }
}

void setTom3(bool on) {
  if (on) {
    tom3PinFlag = true;
    tom3PinTime = millis();
    digitalWrite(tom3Pin, LOW);    
  }
}

void setTom4(bool on) {
  if (on) {
    tom4PinFlag = true;
    tom4PinTime = millis();
    digitalWrite(tom4Pin, LOW);    
  }
}


void setClap(bool on) {
  if (on) {
    clapPinFlag = true;
    clapPinTime = millis();
    digitalWrite(clapPin, LOW);    
  }
}

void setHiHatOpen(bool on) {
  if (on) {
    hiHatOpenPinFlag = true;
    hiHatOpenPinTime = millis();
    digitalWrite(hiHatOpenPin, LOW);    
  }
}

void setRide(bool on) {
  if (on) {
    ridePinFlag = true;
    ridePinTime = millis();
    digitalWrite(ridePin, LOW);    
  }
}


void turnOff(int pin) {
    digitalWrite(pin, HIGH);    
}

void setup(void)
{
  int  err;
  Serial.begin(SERIAL_RATE);
  DEBUGS("\n[MidiFile Looper]");

  // Initialize SD
  if (!SD.begin(SD_SELECT, SPI_FULL_SPEED))
  {
    DEBUGS("\nSD init fail!");
    while (true) ;
  }
 
  // Initialize MIDIFile
  SMF.begin(&SD);
  SMF.setMidiHandler(midiCallback);
//  SMF.looping(true);
//  SMF.setTempoAdjust(50);


  // use the next file name and play it
  DEBUG("\nFile: ", loopfile);
  SMF.setFilename(loopfile);
  err = SMF.load();
  if (err != -1)
  {
    DEBUG("\nSMF load Error ", err);
    while (true);
  }
//   
//  pinMode(2, OUTPUT);
//  pinMode(3, OUTPUT);
//  pinMode(4, OUTPUT);
//  pinMode(5, OUTPUT);
//  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
//  pinMode(8, OUTPUT);
//  pinMode(9, OUTPUT);
//  pinMode(10, OUTPUT);
//  pinMode(11, OUTPUT);
//  pinMode(12, OUTPUT);
//  pinMode(1, OUTPUT);
  
//  digitalWrite(2, HIGH); 
//  digitalWrite(3, HIGH); 
//  digitalWrite(4, HIGH); 
//  digitalWrite(5, HIGH); 
//  digitalWrite(6, HIGH); 
  digitalWrite(7, HIGH); 
//  digitalWrite(8, HIGH); 
//  digitalWrite(9, HIGH); 
//  digitalWrite(10, HIGH); 
//  digitalWrite(11, HIGH); 
//  digitalWrite(12, HIGH); 
//  digitalWrite(1, HIGH); 
  

  
  cymbal1PinTime = millis();
  cymbal2PinTime = millis();

  tom1PinTime = millis();
  tom2PinTime = millis();
  tom3PinTime = millis();
  tom4PinTime = millis();

  snarePinTime = millis();

  basePinTime = millis();

  clapPinTime = millis();

  hiHatPinTime = millis();
  hiHatOpenPinTime = millis();

  ridePinTime = millis();

}



void loop(void)
{
  // play the file
  if (!SMF.isEOF())
  {
    SMF.getNextEvent();
  } 


  if ((millis() - cymbal1PinTime) > 30 && cymbal1PinFlag) {
    turnOff(cymbal1Pin);
    cymbal1PinFlag = false;
  }

  if ((millis() - cymbal2PinTime) > 30 && cymbal2PinFlag) {
    turnOff(cymbal2Pin);
    cymbal2PinFlag = false;
  }

  if ((millis() - tom1PinTime) > 80 && tom1PinFlag) {
    turnOff(tom1Pin);
    tom1PinFlag = false;
  }

  if ((millis() - tom2PinTime) > 80 && tom2PinFlag) {
    turnOff(tom2Pin);
    tom2PinFlag = false;
  }

  if ((millis() - tom3PinTime) > 80 && tom3PinFlag) {
    turnOff(tom3Pin);
    tom3PinFlag = false;
  }

  if ((millis() - tom4PinTime) > 80 && tom4PinFlag) {
    turnOff(tom4Pin);
    tom4PinFlag = false;
  }
  
  if ((millis() - snarePinTime) > 20 && snarePinFlag) {
    turnOff(snarePin);
    snarePinFlag = false;
  }

  if ((millis() - hiHatPinTime) > 40 && hiHatPinFlag) {
    turnOff(hiHatPin);
    hiHatPinFlag = false;
  }

  if ((millis() - basePinTime) > 80 && basePinFlag) {
    turnOff(basePin);
    basePinFlag = false;
  }

  if ((millis() - clapPinTime) > 100 && clapPinFlag) {
    turnOff(clapPin);
    clapPinFlag = false;
  }

  if ((millis() - hiHatOpenPinTime) > 70 && hiHatOpenPinFlag) {
    turnOff(hiHatOpenPin);
    hiHatOpenPinFlag = false;
  }

  if ((millis() - ridePinTime) > 300 && ridePinFlag) {
    turnOff(ridePin);
    ridePinFlag = false;
  }
  
}
