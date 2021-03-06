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
* Author: Mikl�s Mar�ti
* Author: P�ter Ruzicska
*/

#ifndef SERIALLISTENER_H
#define SERIALLISTENER_H

#include <QObject>
#include <QString>

class ActiveMessage
{
public:
	int dest;
	int source;
	int group;
	int type;

	QByteArray payload;

public:
	unsigned char getByte(int index) const;
	unsigned short getShort(int index) const;
	unsigned int getInt(int index) const;
        unsigned int getID() const;

	QString toString() const;
};

class QextSerialPort;

class SerialListener :
	public QObject
{
	Q_OBJECT

public:
	SerialListener();
	virtual ~SerialListener();

signals:
	void receiveMessage(const ActiveMessage & msg);
	void showNotification(const QString & message, int timeout = 0);

public slots:
	void onPortChanged(const QString & portName, int baudRate);

private slots:
	void onReadyRead();
	virtual void timerEvent(QTimerEvent *event);

private:
	QextSerialPort *port;
	void disconnectPort(const char * message);

	bool escaped;
	QByteArray partialPacket;

	int badPacketCount;
	void receiveRawPacket(const QByteArray & packet);
	void receiveTosPacket(const QByteArray & packet);

	int timerId;
	int moteTime;
};

#endif // SERIALLISTENER_H
