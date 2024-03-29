//
//  _   _         ______    _ _ _   _             _ _ _
// | \ | |       |  ____|  | (_) | (_)           | | | |
// |  \| | ___   | |__   __| |_| |_ _ _ __   __ _| | | |
// | . ` |/ _ \  |  __| / _` | | __| | '_ \ / _` | | | |
// | |\  | (_) | | |___| (_| | | |_| | | | | (_| |_|_|_|
// |_| \_|\___/  |______\__,_|_|\__|_|_| |_|\__, (_|_|_)
//                                           __/ |
//                                          |___/
// 
// This file is auto-generated. Do not edit manually
// 
// Copyright 2013-2022 Step Function I/O, LLC
// 
// Licensed to Green Energy Corp (www.greenenergycorp.com) and Step Function I/O
// LLC (https://stepfunc.io) under one or more contributor license agreements.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership. Green Energy Corp and Step Function I/O LLC license
// this file to you under the Apache License, Version 2.0 (the "License"); you
// may not use this file except in compliance with the License. You may obtain
// a copy of the License at:
// 
//   http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "JNIEventAnalogOutputStatusVariation.h"

namespace jni
{
    namespace cache
    {
        bool EventAnalogOutputStatusVariation::init(JNIEnv* env)
        {
            auto clazzTemp = env->FindClass("Lcom/automatak/dnp3/enums/EventAnalogOutputStatusVariation;");
            if(!clazzTemp) return false;
            this->clazz = (jclass) env->NewGlobalRef(clazzTemp);
            env->DeleteLocalRef(clazzTemp);

            this->method0 = env->GetStaticMethodID(this->clazz, "fromType", "(I)Lcom/automatak/dnp3/enums/EventAnalogOutputStatusVariation;");
            if(!this->method0) return false;

            this->method1 = env->GetMethodID(this->clazz, "toType", "()I");
            if(!this->method1) return false;

            return true;
        }

        void EventAnalogOutputStatusVariation::cleanup(JNIEnv* env)
        {
            env->DeleteGlobalRef(this->clazz);
        }

        LocalRef<JEventAnalogOutputStatusVariation> EventAnalogOutputStatusVariation::fromType(JNIEnv* env, jint arg0)
        {
            return LocalRef<JEventAnalogOutputStatusVariation>(env, env->CallStaticObjectMethod(this->clazz, this->method0, arg0));
        }

        jint EventAnalogOutputStatusVariation::toType(JNIEnv* env, JEventAnalogOutputStatusVariation instance)
        {
            return env->CallIntMethod(instance, this->method1);
        }
    }
}
