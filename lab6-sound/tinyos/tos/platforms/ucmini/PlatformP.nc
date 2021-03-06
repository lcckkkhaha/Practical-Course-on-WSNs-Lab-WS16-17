/// $Id: PlatformP.nc,v 1.4 2010/11/12 19:37:01 szabomeister Exp $

/*
 * Copyright (c) 2004-2005 Crossbow Technology, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of Crossbow Technology nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * Internal platform boot code.
 *
 * @author Martin Turon <mturon@xbow.com>
 */

#include "hardware.h"

module PlatformP @safe()
{
  provides interface Init;
  uses interface Init as MoteInit;
  uses interface Init as MeasureClock;

}
implementation
{
  void power_init() {
      atomic {
	MCUCR = _BV(SE);      // Internal RAM, IDLE, rupt vector at 0x0002,
			      // enable sleep instruction!
	DDRB &= ~(_BV(PB7));    // set it as input
	//PORTB |= _BV(7);  // enable usb-rs232 chip
        DDRE &= ~(_BV(PE4)); // set it as input
       
        //DDRF |= _BV(PF2);
        //PORTF |= _BV(PF2); //empowering i2c sensors for testing purposes
	
       // DDRD |= _BV(PD0);
       // DDRD |= _BV(PD1);
       // PORTD |= _BV(PD0) | _BV(PD1);
      }
  }

  command error_t Init.init()
  {
    error_t ok;

    // set the clock prescaler
    atomic {
      // enable changing the prescaler
      CLKPR = 0x80;

#if MHZ == 8
      CLKPR = 0x00;
#elif MHZ == 4
      CLKPR = 0x01;
#elif MHZ == 2
      CLKPR = 0x02;
#elif MHZ == 1
      CLKPR = 0x03;
#else
	#error "Unsupported MHZ"
#endif
    }

    /* First thing is to measure the clock frequency */
    ok = call MeasureClock.init();
    ok = ecombine(ok, call MoteInit.init());

    if (ok != SUCCESS)
      return ok;

    power_init();

    return SUCCESS;
  }
}
