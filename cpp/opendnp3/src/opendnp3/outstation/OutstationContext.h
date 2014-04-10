/**
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
#ifndef __OUTSTATION_CONTEXT_H_
#define __OUTSTATION_CONTEXT_H_

#include <openpal/StaticBuffer.h>
#include <openpal/IExecutor.h>
#include <openpal/LogRoot.h>
#include <openpal/AsyncLayerInterfaces.h>

#include "opendnp3/StaticSizeConfiguration.h"
#include "opendnp3/outstation/Database.h"
#include "opendnp3/outstation/ResponseContext.h"
#include "opendnp3/app/IINField.h"
#include "opendnp3/app/ObjectWriter.h"
#include "opendnp3/app/APDUHeader.h"
#include "opendnp3/outstation/ICommandHandler.h"

namespace opendnp3
{


/// Represent all of the "state" and configuration for an outstation
class OutstationContext
{
	public:

	OutstationContext(	openpal::IExecutor& executor,
						openpal::LogRoot& root, 
						openpal::ILowerLayer& lower,
						ICommandHandler& commandHandler,
						Database& database, 
						EventBufferFacade& buffers);

	// ------ Helper methods for dealing with state ------

	void SetOnline();
	void SetOffline();

	// ------ Dynamic "state" ---------
	
	bool isOnline;
	bool isSending;

	// ------ Unchanged variables and configuration -------

	openpal::Logger logger;
	openpal::IExecutor* pExecutor;
	openpal::ILowerLayer* pLower;
	ICommandHandler* pCommandHandler;
	Database* pDatabase;
	OutstationEventBuffer eventBuffer;
	ResponseContext rspContext;
	openpal::StaticBuffer<sizes::MAX_TX_APDU_SIZE> txBuffer;
};


}



#endif

