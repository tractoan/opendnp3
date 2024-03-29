/*
 * Copyright 2013-2022 Step Function I/O, LLC
 *
 * Licensed to Green Energy Corp (www.greenenergycorp.com) and Step Function I/O
 * LLC (https://stepfunc.io) under one or more contributor license agreements. 
 * See the NOTICE file distributed with this work for additional information
 * regarding copyright ownership. Green Energy Corp and Step Function I/O LLC license
 * this file to you under the Apache License, Version 2.0 (the "License"); you
 * may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef OPENDNP3CLR_COMMAND_SET_BUILDER_H
#define OPENDNP3CLR_COMMAND_SET_BUILDER_H

#include <opendnp3/master/CommandSet.h>

using namespace Automatak::DNP3::Interface;

using namespace System::Collections::ObjectModel;
using namespace System::Collections::Generic;

namespace Automatak
{
    namespace DNP3
    {
        namespace Adapter
        {

            private ref class CommandSetBuilder : ICommandBuilder
            {
            public:

                CommandSetBuilder(opendnp3::CommandSet& commands);

                virtual void Add(IEnumerable<IndexedValue<ControlRelayOutputBlock^>^>^ commands);
                virtual void Add(IEnumerable<IndexedValue<AnalogOutputInt16^>^>^ commands);
                virtual void Add(IEnumerable<IndexedValue<AnalogOutputInt32^>^>^ commands);
                virtual void Add(IEnumerable<IndexedValue<AnalogOutputFloat32^>^>^ commands);
                virtual void Add(IEnumerable<IndexedValue<AnalogOutputDouble64^>^>^ commands);

            private:

                opendnp3::CommandSet* commands;
            };

        }
    }
}

#endif
