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
#ifndef OPENDNP3_BUFFEREDCOLLECTION_H
#define OPENDNP3_BUFFEREDCOLLECTION_H

#include "opendnp3/app/parsing/ICollection.h"

#include <ser4cpp/container/SequenceTypes.h>

namespace opendnp3
{

template<class T, class ReadFunc> class BufferedCollection : public ICollection<T>
{
public:
    BufferedCollection(const ser4cpp::rseq_t& buffer, size_t count, const ReadFunc& readFunc)
        : buffer(buffer), COUNT(count), readFunc(readFunc)
    {
    }

    virtual size_t Count() const override final
    {
        return COUNT;
    }

    virtual void Foreach(IVisitor<T>& visitor) const final
    {
        ser4cpp::rseq_t copy(buffer);

        for (uint32_t pos = 0; pos < COUNT; ++pos)
        {
            visitor.OnValue(readFunc(copy, pos));
        }
    }

private:
    ser4cpp::rseq_t buffer;
    const size_t COUNT;
    ReadFunc readFunc;
};

template<class T, class ReadFunc>
BufferedCollection<T, ReadFunc> CreateBufferedCollection(const ser4cpp::rseq_t& buffer,
                                                         size_t count,
                                                         const ReadFunc& readFunc)
{
    return BufferedCollection<T, ReadFunc>(buffer, count, readFunc);
}

} // namespace opendnp3

#endif
