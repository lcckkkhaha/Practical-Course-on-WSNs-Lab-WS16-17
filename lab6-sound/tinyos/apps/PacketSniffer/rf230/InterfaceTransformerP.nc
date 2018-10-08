/*
* Copyright (c) 2010, University of Szeged
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* - Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* - Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following
* disclaimer in the documentation and/or other materials provided
* with the distribution.
* - Neither the name of University of Szeged nor the names of its
* contributors may be used to endorse or promote products derived
* from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Author: Veress Krisztian
*         veresskrisztian@gmail.com
*/

/**
  * This module is a multi-to-multi interface connection. The goal is to provide
  * those interfaces that are needed for the PacketSniffer application, using those
  * that are available on the current platform's radio driver.
  * 
  * @author Veress Krisztian
  * @date   Sept 4 2010
  * 
  */

#include <Tasklet.h>

module InterfaceTransformerP {
  provides {
    interface Packet;
    interface Receive;
  }
  uses {
    interface RadioPacket;
    interface BareReceive;
    interface BareSend;
  }
}

implementation  {

  /** RadioPacket interface to Packet interface */
  command void Packet.clear(message_t* ONE msg) {
    call RadioPacket.clear(msg);
  }
  command uint8_t Packet.payloadLength(message_t* msg) {
    return call RadioPacket.payloadLength(msg);
  }
  command void Packet.setPayloadLength(message_t* msg, uint8_t len) {

  }
  command uint8_t Packet.maxPayloadLength() {
    return call RadioPacket.maxPayloadLength();
  }
  command void* Packet.getPayload(message_t* msg, uint8_t len) {
    if ( len > call RadioPacket.maxPayloadLength() )
      return NULL;
    else
      return ((void*)msg) + call RadioPacket.headerLength(msg);
  }
  /** ---------------------------------------- */
  
  /** BareReceive interface to Receive interface */
  event message_t* BareReceive.receive(message_t* msg){
    message_t* ret = signal Receive.receive(
                             msg,
                             ((void*)msg) + call RadioPacket.headerLength(msg),
                             call RadioPacket.payloadLength(msg)
                     );
    return ret;
  }
  /** ---------------------------------------- */
  
  event void BareSend.sendDone(message_t* msg, error_t error) {}
   
}
