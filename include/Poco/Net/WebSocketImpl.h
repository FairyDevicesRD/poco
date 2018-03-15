//
// WebSocketImpl.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/WebSocketImpl.h#5 $
//
// Library: Net
// Package: WebSocket
// Module:  WebSocketImpl
//
// Definition of the StreamSocketImpl class.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_WebSocketImpl_INCLUDED
#define Net_WebSocketImpl_INCLUDED


#include "Poco/Net/StreamSocketImpl.h"
#include "Poco/Random.h"
#include <vector>

namespace Poco {
namespace Net {


class Net_API WebSocketImpl: public StreamSocketImpl
	/// This class implements a WebSocket, according
	/// to the WebSocket protocol described in RFC 6455.
{
public:
	WebSocketImpl(StreamSocketImpl* pStreamSocketImpl, bool mustMaskPayload);
		/// Creates a StreamSocketImpl using the given native socket.
	
	// StreamSocketImpl
	virtual int sendBytes(const void* buffer, int length, int flags);
		/// Sends a WebSocket protocol frame.
		
	virtual int receiveBytes(std::vector<char> &buffer, int flags);
	virtual int receiveBytes(void* buffer, int length, int flags);
		/// Receives a WebSocket protocol frame.
		
	virtual SocketImpl* acceptConnection(SocketAddress& clientAddr);
	virtual void connect(const SocketAddress& address);
	virtual void connect(const SocketAddress& address, const Poco::Timespan& timeout);
	virtual void connectNB(const SocketAddress& address);
	virtual void bind(const SocketAddress& address, bool reuseAddress = false);
	virtual void bind6(const SocketAddress& address, bool reuseAddress = false, bool ipV6Only = false);
	virtual void listen(int backlog = 64);
	virtual void close();
	virtual void shutdownReceive();
	virtual void shutdownSend();
	virtual void shutdown();
	virtual int sendTo(const void* buffer, int length, const SocketAddress& address, int flags = 0);
	virtual int receiveFrom(void* buffer, int length, SocketAddress& address, int flags = 0);
	virtual void sendUrgent(unsigned char data);
	virtual bool secure() const;
	virtual void setSendTimeout(const Poco::Timespan& timeout); 
	virtual Poco::Timespan getSendTimeout();
	virtual void setReceiveTimeout(const Poco::Timespan& timeout);
	virtual Poco::Timespan getReceiveTimeout();

	// Internal
	int frameFlags() const;
		/// Returns the frame flags of the most recently received frame.
		
	bool mustMaskPayload() const;
		/// Returns true if the payload must be masked.

protected:
	enum
	{
		FRAME_FLAG_MASK   = 0x80,
		MAX_HEADER_LENGTH = 14
	};
	
	int receiveNBytes(void* buffer, int bytes);
	virtual ~WebSocketImpl();

private:
	WebSocketImpl();
	
	StreamSocketImpl* _pStreamSocketImpl;
	int _frameFlags;
	bool _mustMaskPayload;
	Poco::Random _rnd;
};


//
// inlines
//
inline int WebSocketImpl::frameFlags() const
{
	return _frameFlags;
}


inline bool WebSocketImpl::mustMaskPayload() const
{
	return _mustMaskPayload;
}


} } // namespace Poco::Net


#endif // Net_WebSocketImpl_INCLUDED
