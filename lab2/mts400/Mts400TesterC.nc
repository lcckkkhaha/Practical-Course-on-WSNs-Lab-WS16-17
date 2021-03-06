/** Copyright (c) 2009, University of Szeged
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
* Author: Zoltan Kincses
*/

#include "DataMsg.h"

configuration Mts400TesterC {
}
implementation {
	components MainC;
	components LedsC;
	components new Accel202C();
	components new Intersema5534C();
	components new SensirionSht11C();
	components new Taos2550C();
	components ActiveMessageC;
	components new AMSenderC(AM_DATAMSG);
	components Mts400TesterP as App;
	
	App.Boot -> MainC;
	App.Leds -> LedsC;
	App.AMSend -> AMSenderC;
	App.SplitControl -> ActiveMessageC;
	App.X_Axis -> Accel202C.X_Axis;
	App.Y_Axis -> Accel202C.Y_Axis;
	App.Intersema -> Intersema5534C.Intersema;
	App.Temperature -> SensirionSht11C.Temperature;
	App.Humidity -> SensirionSht11C.Humidity;
	App.VisibleLight -> Taos2550C.VisibleLight;
	App.InfraredLight -> Taos2550C.InfraredLight;
  App.Packet -> AMSenderC;
  App.AMPacket -> AMSenderC;
}
