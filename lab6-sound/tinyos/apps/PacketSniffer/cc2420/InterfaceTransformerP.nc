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
  * @date   July 18 2010
  * 
  */

module InterfaceTransformerP {
  provides {
    interface Packet;
    interface Receive;
  }
  uses {
    interface CC2420Packet;
    interface CC2420PacketBody;
    interface Send;
    interface Receive as BareReceive;
    interface Receive as ActiveReceive;
  }
}

implementation  {

  /** CC2420PacketBody interface to Packet interface */
  command void Packet.clear(message_t* msg) {
    memset(call CC2420PacketBody.getHeader(msg), 0x0, sizeof(cc2420_header_t));
    memset(call CC2420PacketBody.getMetadata(msg), 0x0, sizeof(cc2420_metadata_t));
  }
  
  command uint8_t Packet.payloadLength(message_t* msg) {
    return (call CC2420PacketBody.getHeader(msg))->length - CC2420_SIZE;
  }
  
  command void Packet.setPayloadLength(message_t* msg, uint8_t len) {
    (call CC2420PacketBody.getHeader(msg))->length  = len + CC2420_SIZE;
  }
  
  command uint8_t Packet.maxPayloadLength() {
    return call Send.maxPayloadLength();
  }
  
  command void* Packet.getPayload(message_t* msg, uint8_t len) {
    return call Send.getPayload(msg, len);
  }
  /** ---------------------------------------- */
  
  event void Send.sendDone(message_t* msg, error_t error) {}
  
  /** Two receive interfaces to one Receive interface */
  event message_t* BareReceive.receive(message_t *msg, void *payload, uint8_t len) {
    return signal Receive.receive(msg,payload,len);
  }
  event message_t* ActiveReceive.receive(message_t *msg, void *payload, uint8_t len) {
    return signal Receive.receive(msg,payload,len);
  }
  /** ---------------------------------------- */
}
