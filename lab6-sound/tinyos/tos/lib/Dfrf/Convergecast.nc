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
* Author: Miklos Maroti
*/

#include "Convergecast.h"

interface Convergecast
{
	/**
	 * Write a convergecast header that declares this node to be the 
	 * root. This message should be broadcasted to all other nodes.
	 */
	command void writeHeader(convergecast_t *header);

	/**
	 * Should be called when the beacon message is received.
	 */
	command bool readHeader(convergecast_t *header);

	/**
	 * Returns the node ID of current root of the network, or
	 * <code>0xFFFF</code> if no root was detected.
	 */
	command am_addr_t root();

	/**
	 * Returns the node ID of the parent of this node.
	 */
	command am_addr_t parent();

	/**
	 * Returns the node ID of the grand parent of this node.
	 */
	command am_addr_t grandParent();
	
	/**
	 * Returns the node ID of the great-grand parent of this node.
	 */
	command am_addr_t greatGrandParent();

	/**
	 * Returns the node ID of the great-great-grand parent of this node.
	 */
	command am_addr_t greatGreatGrandParent();
	
	/**
	 * Returns the hopcount from this node to the root. The
	 * root has hopcount zero.
	 */
	command uint8_t hopCount();
}
