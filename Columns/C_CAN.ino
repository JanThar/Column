///*
// *  CAN-Bus
// */
//
//#include <ACAN2515Tiny.h>
//
//ACAN2515Tiny can (MCP2515_CS, SPI, MCP2515_INT) ;
//static const uint32_t CAN_BIT_RATE = 1000 * 1000 ;
//static const uint32_t QUARTZ_FREQUENCY = 16 * 1000 * 1000 ; // 16 MHz
//
//void start_CAN() {
//  SPI.begin () ;
////--- Configure ACAN2515
//  Serial.println ("Configure ACAN2515") ;
//  ACAN2515TinySettings settings2515 (QUARTZ_FREQUENCY, CAN_BIT_RATE);
//  if (can.begin (settings2515, [] { can.isr () ; }) == 0) Serial.println("CAN initialized!");
//  else Serial.print ("CAN initialisation failed!");
//}
//
//void CAN_Communication() {
//  //Send messages
//  CANMessage frame ;
//  can.tryToSend (frame); 
//  //Receive messsage
//  if (can.available ()) {
//    can.receive (frame);
//  }
//}
//
///*class CANMessage {
//  public : uint32_t id = 0 ;  // Frame identifier
//  public : bool ext = false ; // false -> standard frame, true -> extended frame
//  public : bool rtr = false ; // false -> data frame, true -> remote frame
//  public : uint8_t idx = 0 ;  // This field is used by the driver
//  public : uint8_t len = 0 ;  // Length of data (0 ... 8)
//  public : union {
//    uint64_t data64        ; // Caution: subject to endianness
//    uint32_t data32 [2]    ; // Caution: subject to endianness
//    uint16_t data16 [4]    ; // Caution: subject to endianness
//    float    dataFloat [2] ; // Caution: subject to endianness
//    uint8_t  data   [8] = {0, 0, 0, 0, 0, 0, 0, 0} ;
//  } ;
//} ;
