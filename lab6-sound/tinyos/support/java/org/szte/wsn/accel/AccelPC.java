/** Copyright (c) 2010, University of Szeged
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
* Author: Ali Baharev
*/


package org.szte.wsn.accel;

import java.text.*;
import java.util.*;

import net.tinyos.util.*;
import net.tinyos.message.*;
import net.tinyos.packet.*;

final class Sender {

	private final MoteIF moteIF;
	private final CtrlMsg msg = new CtrlMsg();

	Sender(MoteIF mif) {
		moteIF = mif;
	}

	void command(int moteID, short command) {

		msg.set_cmd(command);
		try {
			moteIF.send(moteID, msg);
		} catch (Exception e) {

			e.printStackTrace();
		}
		System.out.println("Sending to mote "+moteID+", command "+command);
	}

}

final class Receiver implements MessageListener {
	
	private final Sender s;

    private final SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
	
	int counter = 0;
	
	Receiver(Sender s) {
		this.s = s;
	}

	@Override
	public void messageReceived(int to, Message m) {
		
		if (m instanceof ReportMsg) {
			ReportMsg rmsg = (ReportMsg) m;
			System.out.print(sdf.format(new Date()));
			System.out.print(" Report from mote "+rmsg.get_id());
			System.out.println(", state "+rmsg.get_mode());
		}
		if (m instanceof DataMsg) {
			DataMsg dmsg = (DataMsg) m;
			System.out.print("Data from mote "+dmsg.get_node_id());
			System.out.println(", local time "+dmsg.get_local_time());
		}
	}
}

public final class AccelPC {

	private final Sender s;
	
	private final Receiver r;

	private static final short ALTERING      = 0;
	private static final short CONTINUOUS    = 1;
	private static final short FORMAT        = 2;
	private static final short STARTSAMPLING = 5;
	private static final short STOPSAMPLING  = 6;
	private static final short SENDSAMPLES   = 7;
	private static final short RADIOOFF      = 8;

	public AccelPC(MoteIF mif) {
		s = new Sender(mif);
		r = new Receiver(s);
		mif.registerListener(new ReportMsg(), r); // FIXME Escape of this...
		mif.registerListener(new DataMsg(), r);
	}

	private static void exitFailure(String msg) {
		System.err.println("Error: " + msg);
		System.exit(1);		
	}

	public static void main(String[] args) {

		String source = "sf@localhost:9002";

		if (args.length == 2) {
			if (!args[0].equals("-comm")) {
				exitFailure("arguments -comm <source>");
			}
			source = args[1];
		}
		else if (args.length != 0) {
			exitFailure("arguments -comm <source>");
		}

		PhoenixSource phoenix = BuildSource.makePhoenix(source, PrintStreamMessenger.err);

		MoteIF mif = new MoteIF(phoenix);
		//TestSerial serial = new TestSerial(mif);		
		new AccelPC(mif).go();
	}

	private void go() {

		try {
			
			final int MOTE_ID = 5;
			
			s.command(MOTE_ID, CONTINUOUS);
			
			//s.command(MOTE_ID, (short) 12);
			
			s.command(MOTE_ID, FORMAT);

			s.command(MOTE_ID, STARTSAMPLING);
			
			//s.command(MOTE_ID, RADIOOFF);

			s.command(MOTE_ID, STOPSAMPLING);
			
			s.command(MOTE_ID, SENDSAMPLES);
			
			//s.command(MOTE_ID, RADIOOFF);
		
			s.command(MOTE_ID, ALTERING);
			
//			while (true) {
//				//s.switchMode(6, mode);
//				Thread.sleep(5000);
//			}
		}
		catch (Exception e) {

			e.printStackTrace();
		}
	}
}
