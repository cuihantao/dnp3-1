/*
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */
#ifndef ASIODNP3_IOHANDLER_H
#define ASIODNP3_IOHANDLER_H

#include "opendnp3/link/ILinkTx.h"
#include "opendnp3/Route.h"

#include "asiodnp3/IChannelListener.h"

#include "openpal/logging/Logger.h"

#include "asiopal/IO.h"
#include "asiopal/IAsyncChannel.h"

#include <memory>

namespace asiodnp3
{

/**

Manages I/O for a number of link contexts

*/	
class IOHandler : public opendnp3::ILinkTx
{

public:

	IOHandler(
		openpal::Logger logger,
		std::shared_ptr<asiopal::IO> io,
		std::shared_ptr<IChannelListener> listener
	);

	/// --- implement ILinkTx ---
	
	virtual void BeginTransmit(const openpal::RSlice& data, opendnp3::ILinkSession& context) override;


	// Bind a link layer session to the handler
	bool AddContext(opendnp3::ILinkSession& session, const opendnp3::Route& route);
	
	// Begin sending messages to the context	
	bool Enable(opendnp3::ILinkSession& session);
	
	// Stop sending messages to this session
	bool Disable(opendnp3::ILinkSession& session);

	// Remove this session entirely
	bool Remove(opendnp3::ILinkSession& session);

protected:

	virtual void Enable() = 0;

	virtual void Suspend() = 0;

	virtual void StartNewChannel() = 0;

	virtual std::shared_ptr<IOHandler> GetShared() = 0;

	void OnNewChannel(std::shared_ptr<asiopal::IAsyncChannel> channel);

private:	
	
	// Query to see if a route is in use
	bool IsRouteInUse(const opendnp3::Route& route) const;
	bool IsSessionInUse(opendnp3::ILinkSession& session) const;
	bool IsAnySessionEnabled() const;

	struct Session
	{
		Session(opendnp3::ILinkSession& session, const opendnp3::Route& route) :
			session(&session),
			route(route),
			enabled(false)
		{}

		Session() : session(nullptr), enabled(false) {}

		opendnp3::ILinkSession* session;
		opendnp3::Route route;
		bool enabled;
	};

	std::vector<Session> records;

	openpal::Logger logger;
	std::shared_ptr<asiopal::IO> io;
	std::shared_ptr<IChannelListener> listener;
		
	// current value of the channel, may be null
	std::shared_ptr<asiopal::IAsyncChannel> channel;
};

}

#endif

