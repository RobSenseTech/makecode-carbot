/*
Copyright (C): 2022, RobSense
*/

#include "pxt.h"
#include <map>
#include <vector>
#include "ReceiverIR.h"
using namespace pxt;

enum class RemoteButton {
      SET = 0x15,
	  UP = 0x40,
	  DOWN = 0x19,
	  LEFT = 0x07,
	  RIGHT = 0x09,
	  A = 0x45,
	  B = 0x46,
	  C = 0x47,
	  D = 0x44,
      E = 0x43,
      F = 0x0D,
	  NUM0 = 0x16,
	  NUM1 = 0x0C,
	  NUM2 = 0x18,
	  NUM3 = 0x5E,
	  NUM4 = 0x08,
	  NUM5 = 0x1C,
	  NUM6 = 0x5A,
	  NUM7 = 0x42,
	  NUM8 = 0x52,
	  NUM9 = 0x4A
};

enum class Pins{
    P0=  3,
    P1=  2,
    P2=  1,
    P3=  4,
    P4=  5,
    P5=  17,
    P6=  12,
    P7=  11,
    P8=  18,
    P9=  10,
    P10= 6,
    P11= 26,
    P12= 20,
    P13= 23,
    P14= 22,
    P15= 21,
    P16= 16,
    P19= 0,
    P20= 30
};

namespace microbit_IR {
  map<RemoteButton, uint32_t> lastact;
  Timer tsb;
  uint8_t buf[32];
  uint32_t now;
  ReceiverIR *rx;
  RemoteIR::Format fmt = RemoteIR::UNKNOWN;

  

  void onReceivable(){
    int x = rx->getData(&fmt, buf, 32);
    //uBit.serial.send(buf, 4);
    now = tsb.read_ms();
    if(now - lastact[(RemoteButton)buf[2]] < 100) return;
    lastact[(RemoteButton)buf[2]] = now;
  }


  void monitorIR(){
    while(1){
      while(rx->getState() != ReceiverIR::Received){
        uBit.sleep(50);
      }
      onReceivable();
    }
  }

  //%
  void init(Pins pin){
    rx = new ReceiverIR((PinName)pin);
    tsb.start(); //interrupt timer for debounce
    create_fiber(monitorIR);
  }

  //%
  void onPressEvent(RemoteButton btn) {

  }

}
