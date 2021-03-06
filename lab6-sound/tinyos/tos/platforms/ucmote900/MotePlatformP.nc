/* Copyright (c) 2005 Intel Corporation
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached INTEL-LICENSE     
 * file. If you do not find these files, copies can be found by writing to
 * Intel Research Berkeley, 2150 Shattuck Avenue, Suite 1300, Berkeley, CA, 
 * 94704.  Attention:  Intel License Inquiry.
 */

/*
 * @author David Gay
 */
module MotePlatformP @safe()
{
	provides interface Init as PlatformInit;
	uses interface Init as SubInit;
}
implementation
{
	command error_t PlatformInit.init()
	{
		// Pull C I/O port pins low
		PORTC = 0;
		DDRC = 0xff;

		return call SubInit.init();
	}

	default command error_t SubInit.init()
	{
		return SUCCESS;
	}
}
