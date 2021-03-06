/*
 * Copyright (c) 2009, Vanderbilt University
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the author appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE VANDERBILT UNIVERSITY BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE VANDERBILT
 * UNIVERSITY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE VANDERBILT UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE VANDERBILT UNIVERSITY HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Author: Janos Sallai
 */

module TestBroadcastPolicyC {
  uses {
    interface Boot;
    interface SplitControl as AMControl;
    interface DfrfSend;
    interface DfrfReceive;
    interface Timer<TMilli>;
    interface AMPacket;
    interface Leds;
  }
} implementation {

  uint8_t cnt = 0;

  event void Boot.booted() {
    call AMControl.start();
  }

  event void AMControl.startDone(error_t error_code) {
    if(call AMPacket.address() == 1) {
      dbg("TestBroadcastPolicy","Starting send timer\n");
      call Timer.startPeriodic(768);
    }
  }

  event void AMControl.stopDone(error_t error_code) {}

  task void sendPacket() {
    counter_packet_t packet;

    packet.cnt = cnt;
    packet.src = call AMPacket.address() & 0xff;
    call DfrfSend.send(&packet);
    dbg("TestBroadcastPolicy","Sent packet %d @ %d\n", cnt);

    cnt++;
    if((cnt % 4) != 0)
      post sendPacket();
  }

  event void Timer.fired() {
    post sendPacket();
  }

  event bool DfrfReceive.receive(void* packet_raw) {
    counter_packet_t *packet = packet_raw;

    dbg("TestBroadcastPolicy","Received packet %d @ %d\n", packet->cnt);
    call Leds.set(packet->cnt);
    //return SUCCESS;
    return TRUE;
  }

}
