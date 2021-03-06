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
* Author:Andras Biro
*/
module ActiveMessageGridP{
	provides interface Receive[am_id_t id];
	provides interface Receive as Snoop[am_id_t id];
	
	uses interface Receive as SubReceive[am_id_t id];
	uses interface Receive as SubSnoop[am_id_t id];
	uses interface AMPacket;
}
implementation{

	event message_t * SubReceive.receive[am_id_t id](message_t *msg, void *payload, uint8_t len){
		am_id_t src=call AMPacket.source(msg);
		am_id_t me=call AMPacket.address();
		if((src-me)==1||(me-src)==1||((src^me)&0x0f)==0)
			return signal Receive.receive[id](msg, payload, len);
		else
			return msg;
	}

	event message_t * SubSnoop.receive[am_id_t id](message_t *msg, void *payload, uint8_t len){
		am_id_t src=call AMPacket.source(msg);
		am_id_t me=call AMPacket.address();
		if((src-me)==1||(me-src)==1||((src^me)&0x0f)==0)
			return signal Snoop.receive[id](msg, payload, len);
		else
			return msg;
	}
	
	default event message_t * Receive.receive[am_id_t am_id](message_t *msg, void *payload, uint8_t len){
		return msg;
	};
	
	default event message_t * Snoop.receive[am_id_t am_id](message_t *msg, void *payload, uint8_t len){
		return msg;
	};
}