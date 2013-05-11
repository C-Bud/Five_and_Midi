#include <Metro.h>
#include <Encoder.h>
#include "SPI.h"
#include "Adafruit_WS2801.h"



float Re=0, Gr=0, Bl=0;
float i,j,k,p;
float m[5], time[5], wave[25], wave2[25], j2[25], checker;
long new1, new2, new3, new4, new5;
int maxx;

Encoder knob1(0, 1);
Encoder knob2(2, 3);
Encoder knob3(4, 5);
Encoder knob4(6, 7);
Encoder knob5(10, 11);

Metro timeDec = Metro(500);

int dataPin = 17;
int clockPin = 16;

Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
  for(int n = 0; n < 25; n++) {
    wave[n]    = -1.0;
    wave2[n]   =  0.0;
  }
  for(int n = 0; n < 24; n=n+5) {
    wave[n]    = 1.0;
    wave2[n]   = 0.5;
  }
  maxx=127;
}

long position1 = -999;
long position2 = -999;
long position3 = -999;
long position4 = -999;
long position5 = -999;


void loop() {
  new1 = knob1.read();
  new2 = knob2.read();
  new3 = knob3.read();
  new4 = knob4.read();
  new5 = knob5.read();
  
  if(timeDec.check() == 1) {
    if(new1>0){
      new1 = new1 - 1;
      if(new1<maxx/2) {
        new1 = new1 - 3;
      }
      knob1.write(new1);
    }
    if(new2>0){
      new2 = new2 - 1;
      if(new2<maxx/2) {
        new2 = new2 - 3;
      }
      knob2.write(new2);
    }
    if(new3>0){
      new3 = new3 - 1;
      if(new3<maxx/2) {
        new3 = new3 - 3;
      }
      knob3.write(new3);
    }
    if(new4>0){
      new4 = new4 - 1;
      if(new4<maxx/2) {
        new4 = new4 - 3;
      }
      knob4.write(new4);
    }
    if(new5>0){
      new5 = new5 - 1;
      if(new5<maxx/2) {
        new5 = new5 - 3;
      }
      knob5.write(new5);
    }
  }
  
  if (new1 >= maxx) {
    new1 = maxx;
    knob1.write(maxx);
  }
  if (new1 <= 0) {
    new1 = 0;
    knob1.write(0);
  }
  if (new2 >= maxx) {
    new2 = maxx;
    knob2.write(maxx);
  }
  if (new2 <= 0) {
    new2 = 0;
    knob2.write(0);
  }
  if (new3 >= maxx) {
    new3 = maxx;
    knob3.write(maxx);
  }
  if (new3 <= 0) {
    new3 = 0;
    knob3.write(0);
  }
  if (new4 >= maxx) {
    new4 = maxx;
    knob4.write(maxx);
  }
  if (new4 <= 0) {
    new4 = 0;
    knob4.write(0);
  }
  if (new5 >= maxx) {
    new5 = maxx;
    knob5.write(maxx);
  }
  if (new5 <= 0) {
    new5 = 0;
    knob5.write(0);
  }
  if (new1 != position1) {
    position1 = new1;
    time[0] = millis();
    Serial.print(new1);
    usbMIDI.sendControlChange(1,map(new1,0,maxx,0,127),1);
  }
  if (new2 != position2) {
    position2 = new2;
    time[1] = millis();
    Serial.print(new2);
    usbMIDI.sendControlChange(1,map(new2,0,maxx,0,127),2);
  }
  if (new3 != position3) {
    position3 = new3;
    time[2] = millis();
    Serial.print(new3);
    usbMIDI.sendControlChange(1,map(new3,0,maxx,0,127),3);
  }
  if (new4 != position4) {
    position4 = new4;
    time[3] = millis();
    Serial.print(new4);
    usbMIDI.sendControlChange(1,map(new4,0,maxx,0,127),4);
  }
  if (new5 != position5) {
    position5 = new5;
    time[4] = millis();
    Serial.print(new5);
    usbMIDI.sendControlChange(1,map(new5,0,maxx,0,127),5);
  }
  //j=0.008;
  j=0.015;
  k = 5 * j;
  m[0] = map(knob1.read(),0,maxx,0,1000);
  m[1] = map(knob2.read(),0,maxx,0,1000);
  m[2] = map(knob3.read(),0,maxx,0,1000);
  m[3] = map(knob4.read(),0,maxx,0,1000);
  m[4] = map(knob5.read(),0,maxx,0,1000);
  
  for(int n = 0; n < 25; n++) {
      if(n<5){
        j2[n] = map(knob1.read(),0,maxx,4,25);
      }
      else if(n>=5 && n<10){
        j2[n] = map(knob2.read(),0,maxx,4,25);
      }
      else if(n>=10 && n<15){
        j2[n] = map(knob3.read(),0,maxx,4,25);
      }
      else if(n>=15 && n<20){
        j2[n] = map(knob4.read(),0,maxx,4,25);
      }
      else{
        j2[n] = map(knob5.read(),0,maxx,4,25);
      }
  }

  for(int n = 0; n < 5; n++) {
    m[n] = m[n]/1000;
  }
    
    for(int n = 0; n < 25; n++) {
      if(n<5){
        HSL(i,m[0],wave2[n]);
      }
      else if(n>=5 && n<10){
        HSL(i,m[1],wave2[n]);
      }
      else if(n>=10 && n<15){
        HSL(i,m[2],wave2[n]);
      }
      else if(n>=15 && n<20){
        HSL(i,m[3],wave2[n]);
      }
      else{
        HSL(i,m[4],wave2[n]);
      }

      if(wave[n]==1){
        wave2[n] = wave2[n]+j2[n]/1000;
      }
      else{
        wave2[n] = wave2[n]-j2[n]*0.0005;
      }
      if(wave2[n] >= 0.5) {
        if(n==0 || n==5 || n==10 || n==15 || n==20){
          wave[n+4]=1;
        }
        else {
          wave[n-1] = 1;
        }
        wave[n]=-1;
      }
      if(wave2[n] < 0) {
        wave2[n]=0;
      }
      strip.setPixelColor(n,Re,Gr,Bl);
    }
    i = i + (j/10);
    if(i>=1){
      i=0;
    }
    p = m[0];
    strip.show();
}
 
void HSL(float H, float S, float L)
{
  float var_1;
  float var_2;
  float Hu=H+.33;
  float Hd=H-.33;
  if ( S == 0 )                       //HSL from 0 to 1
  {
     Re = L * 255;                      //RGB results from 0 to 255
     Gr = L * 255;
     Bl = L * 255;
  }
  else
  {
     if ( L < 0.5 ) 
       var_2 = L * ( 1 + S );
     else           
       var_2 = ( L + S ) - ( S * L );
 
     var_1 = 2 * L - var_2;
 
     Re = round(255 * Hue_2_RGB( var_1, var_2, Hu ));
     Gr = round(255 * Hue_2_RGB( var_1, var_2, H ));
     Bl = round(255 * Hue_2_RGB( var_1, var_2, Hd ));
  }
 
}
float Hue_2_RGB( float v1, float v2, float vH )             //Function Hue_2_RGB
{
   if ( vH < 0 ) 
     vH += 1;
   if ( vH > 1 ) 
     vH -= 1;
   if ( ( 6 * vH ) < 1 ) 
     return ( v1 + ( v2 - v1 ) * 6 * vH );
   if ( ( 2 * vH ) < 1 ) 
     return ( v2 );
   if ( ( 3 * vH ) < 2 ) 
     return ( v1 + ( v2 - v1 ) * (.66-vH) * 6 );
   return ( v1 );
}
