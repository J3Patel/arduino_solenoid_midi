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

const char *loopfile = "midi3n.mid";  // simple and short file
//dhol1finalmidi
//const char *loopfile = "j1080.mid";  // simple and short file

SdFat	SD;
MD_MIDIFile SMF;

int basePins[1] = {6};
int snarePins[1] = {8};
int hiHatPins[1] = {4};

int basePins2[1] = {0};
int snarePins2[2] = {0,0};
int hiHatPins2[1] = {0};

unsigned long baseTime = 0;
unsigned long snareTime = 0;
unsigned long hiHatTime = 0;

boolean snareFlag = false;
boolean baseFlag = false;
boolean hiHatFlag = false;


unsigned long baseTime2 = 0;
unsigned long snareTime2 = 0;
unsigned long hiHatTime2 = 0;



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
    case 36:
    setBase(velocity != 64);
    break;

    case 51:
    setHiHat(velocity != 64);
    break;

    case 35:
    setBase(velocity != 64);
    break;

       case 45:
    setBase(velocity != 64);
    break;

       case 43:
    setBase(velocity != 64);
    break;

       case 47:
    setBase(velocity != 64);
    break;
    
    case 38:
    setSnare(velocity != 64);
    break;

    
    case 40:
    setSnare(velocity != 64);
    break;
    
    case 42 :
    setHiHat(velocity != 64);
    break;
    
    case 44:
    setHiHat(velocity != 64);
    break; 
    
    case 46:
    setHiHat(velocity != 64);
    break;
    
    case 49:
    setHiHat(velocity != 64);
    break;
    
    case 33:
    setHiHat(velocity != 64);
    break;
    
    case 39:
    setHiHat(velocity != 64);
    break;
  }  
}

void setBase(bool on) {
  if (on) {
    baseTime = millis();
    baseFlag = true;
    for (int i=0; i< 1; i++) {
      digitalWrite(basePins[i], LOW);    
    }
  }
  
}

void setSnare(bool on) {
  if (on) {
    snareTime = millis();
    snareFlag = true;
    for (int i=0; i< 1; i++) {
      digitalWrite(snarePins[i], LOW);    
    }
  }
}

void setHiHat(bool on) {
  if (on) {
    hiHatFlag = true;
    hiHatTime = millis();
    for (int i=0; i< 1; i++) {
      digitalWrite(hiHatPins[i], LOW);    
    }
  }
}

void setBase2(bool on) {
  
  if (on) {
    baseTime2 = millis();
    for (int i=0; i< 1; i++) {
   //   Serial.print("base on");
      digitalWrite(basePins2[i], LOW);    
    }
  }
  
}

void setSnare2(bool on) {
  if (on) {
    snareTime2 = millis();
    for (int i=0; i< 1; i++) {
    //  Serial.print("base on");
      digitalWrite(snarePins2[i], LOW);    
    }
  }
}

void setHiHat2(bool on) {
  if (on) {
  //  Serial.print("hi hat on");
    hiHatTime2 = millis();
    for (int i=0; i< 1; i++) {
   //   Serial.print("base on");
      digitalWrite(hiHatPins2[i], LOW);    
    }
  }
}

void turnOff(int pins[]) {
  for (int i=0; i< sizeof(pins); i++) {
      digitalWrite(pins[i], HIGH);    
  }
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
//  SMF.setTempo(200);
   
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(4, HIGH); 
  digitalWrite(6, HIGH); 
  digitalWrite(8, HIGH); 
  digitalWrite(3, HIGH); 
  snareTime = millis();
  hiHatTime = millis();
  baseTime = millis();
}



void loop(void)
{
  // play the file
  if (!SMF.isEOF())
  {
    SMF.getNextEvent();
  } 
  
  if ((millis() - snareTime) > 20 && snareFlag) {
    turnOff(snarePins);
    snareFlag = false;
  }

  if ((millis() - hiHatTime) > 50 && hiHatFlag) {
    turnOff(hiHatPins);
    hiHatFlag = false;
  }

if ((millis() - baseTime) > 80 && baseFlag) {
    turnOff(basePins);
    baseFlag = false;
  }
  
//  if (millis() - baseTime2 > 40) {
//    turnOff(basePins2);
//  }
//
//  if (millis() - snareTime2 > 50) {
//    turnOff(snarePins2);
//  }
//
//  if (millis() - hiHatTime2 > 20) {
//    turnOff(hiHatPins2);
//  }
}
