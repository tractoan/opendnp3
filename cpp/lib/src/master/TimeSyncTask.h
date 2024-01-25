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
#ifndef OPENDNP3_TIMESYNCTASK_H
#define OPENDNP3_TIMESYNCTASK_H

#include "master/IMasterTask.h"
#include "master/TaskPriority.h"
#include "opendnp3/master/TimeSyncResultCallbackT.h"

namespace opendnp3
{

// Synchronizes the time on the outstation
class TimeSyncTask : public IMasterTask
{

public:
    TimeSyncTask(const std::shared_ptr<TaskContext>& context, IMasterApplication& app, const TimeSyncResultCallback& callback,
                                                            const Timestamp& startExpiration, uint64_t timeMs, Logger& logger);

    static std::shared_ptr<IMasterTask> CreateTimeSync(const std::shared_ptr<TaskContext>& context,
                                                            IMasterApplication& app,
                                                            const TimeSyncResultCallback& callback,
                                                            const Timestamp& startExpiration,
                                                            uint64_t timeMs,
                                                            Logger logger);

    virtual char const* Name() const override final
    {
        return "time sync";
    }

    virtual int Priority() const override final
    {
        return priority::TIME_SYNC;
    }

    virtual bool BlocksLowerPriority() const override final
    {
        return false;
    }

    virtual bool IsRecurring() const override final
    {
        return false;
    }

    virtual bool BuildRequest(APDURequest& request, uint8_t seq) override final;

private:
    virtual MasterTaskType GetTaskType() const override final
    {
        return MasterTaskType::USER_TASK;
    }

    virtual bool IsEnabled() const override final
    {
        return true;
    }

    virtual ResponseResult ProcessResponse(const APDUResponseHeader& response,
                                           const ser4cpp::rseq_t& objects) override final;

    virtual void OnTaskComplete(TaskCompletion result, Timestamp now) override final;

    ResponseResult OnResponseWriteTime(const APDUResponseHeader& header, const ser4cpp::rseq_t& objects);

    virtual void Initialize() override final;

    // what time we sent the delay meas
    uint64_t timeMs;
    const TimeSyncResultCallback timeSyncCallback;
};

} // namespace opendnp3

#endif
