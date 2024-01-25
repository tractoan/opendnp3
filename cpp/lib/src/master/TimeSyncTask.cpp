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
#include "TimeSyncTask.h"

#include "app/APDUBuilders.h"
#include "app/parsing/APDUParser.h"
#include "gen/objects/Group50.h"
#include "master/TimeSyncHandler.h"
#include "master/CommandSetOps.h"

#include <ser4cpp/serialization/LittleEndian.h>

namespace opendnp3
{

std::shared_ptr<IMasterTask> TimeSyncTask::CreateTimeSync(const std::shared_ptr<TaskContext>& context,
                                                              IMasterApplication& app,
                                                              const TimeSyncResultCallback& callback,
                                                              const Timestamp& startExpiration,
                                                              uint64_t timeMs,
                                                              Logger logger)
{
    auto task
        = std::make_shared<TimeSyncTask>(context, app, callback, startExpiration, timeMs, logger);
    return task;
}

TimeSyncTask::TimeSyncTask(const std::shared_ptr<TaskContext>& context, 
                            IMasterApplication& app, 
                            const TimeSyncResultCallback& callback,
                            const Timestamp& startExpiration, 
                            uint64_t timeMs, 
                            Logger& logger)
    : IMasterTask(context, app, TaskBehavior::SingleExecutionNoRetry(startExpiration), logger, TaskConfig::Default()), timeMs(timeMs)
{
}

void TimeSyncTask::Initialize()
{
}

bool TimeSyncTask::BuildRequest(APDURequest& request, uint8_t seq)
{
    Group50Var1 time;
    time.time = DNPTime(timeMs);
    request.SetFunction(FunctionCode::WRITE);
    request.SetControl(AppControlField::Request(seq));
    auto writer = request.GetWriter();
    writer.WriteSingleValue<ser4cpp::UInt8, Group50Var1>(QualifierCode::UINT8_CNT, time);
    return true;
}

IMasterTask::ResponseResult TimeSyncTask::ProcessResponse(const APDUResponseHeader& response,
                                                                const ser4cpp::rseq_t& objects)
{
    return OnResponseWriteTime(response, objects);
}

IMasterTask::ResponseResult TimeSyncTask::OnResponseWriteTime(const APDUResponseHeader& header,
                                                                    const ser4cpp::rseq_t& objects)
{
    return ValidateNullResponse(header, objects) ? ResponseResult::OK_FINAL : ResponseResult::ERROR_BAD_RESPONSE;
}

void TimeSyncTask::OnTaskComplete(TaskCompletion result, Timestamp /*now*/)
{
    timeSyncCallback(result);
}

} // namespace opendnp3
