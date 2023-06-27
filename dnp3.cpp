/*
Copyright [2022] [roberto64 (roberto64dnp3oss@outlook.com)]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "stdafx.h"
#include "dnp3.hpp"
#include <thread>
#include <chrono>
#include "mframes.hpp"

class LogToList : public opendnp3::ILogHandler
{
public:
    LogToList(MFrame *mframe) : _mframe(mframe) {}
    virtual void log(opendnp3::ModuleId module, const char *id, opendnp3::LogLevel level, char const *location, char const *message);

private:
    MFrame *_mframe;
};

void LogToList::log(opendnp3::ModuleId module, const char *id, opendnp3::LogLevel level, char const *location, char const *message)
{
    _mframe->AddLog(std::string(id) + ", " + message);
}

opendnp3::CommandStatus MCommandHandler::Select(const opendnp3::ControlRelayOutputBlock &arCommand, uint16_t aIndex)
{
    m_slave->AddLog("COMMAND: Select");
    return opendnp3::CommandStatus::SUCCESS;
}

opendnp3::CommandStatus MCommandHandler::Operate(const opendnp3::ControlRelayOutputBlock &arCommand, uint16_t aIndex, opendnp3::IUpdateHandler &handler, opendnp3::OperateType opType)
{
    opendnp3::CommandStatus cs(opendnp3::CommandStatus::NOT_SUPPORTED);
    if (opType == opendnp3::OperateType::DirectOperate)
    {
        m_slave->AddLog(std::string("COMMAND: Operate , LATCH_ON, count=") + std::to_string(arCommand.count));
        cs = opendnp3::CommandStatus::SUCCESS;
    }
    /*    else if(arCommand.functionCode == opendnp3::ControlCode::LATCH_OFF)
        {
            m_slave->AddLog(std::string("COMMAND: Operate , LATCH_OFF, count=") + std::to_string(arCommand.count));
            cs = opendnp3::CommandStatus::SUCCESS;
        }
        else if(arCommand.functionCode == opendnp3::ControlCode::CLOSE_PULSE_ON)
        {
            m_slave->AddLog(std::string("COMMAND: Operate , PULSE_CLOSE, count=") + std::to_string(arCommand.count));
            cs = opendnp3::CommandStatus::SUCCESS;
        }
        else if(arCommand.functionCode == opendnp3::ControlCode::TRIP_PULSE_ON)
        {
            m_slave->AddLog(std::string("COMMAND: Operate , PULSE_TRIP, count=") + std::to_string(arCommand.count));
            cs = opendnp3::CommandStatus::SUCCESS;
        }*/
    return cs;
}

opendnp3::CommandStatus MCommandHandler::Select(const opendnp3::AnalogOutputInt16 &arCommand, uint16_t aIndex)
{
    return opendnp3::CommandStatus::NOT_SUPPORTED;
}

opendnp3::CommandStatus MCommandHandler::Operate(const opendnp3::AnalogOutputInt16 &arCommand, uint16_t aIndex, opendnp3::IUpdateHandler &handler, opendnp3::OperateType opType)
{
    return opendnp3::CommandStatus::NOT_SUPPORTED;
}

opendnp3::CommandStatus MCommandHandler::Select(const opendnp3::AnalogOutputInt32 &arCommand, uint16_t aIndex)
{
    return opendnp3::CommandStatus::NOT_SUPPORTED;
}

opendnp3::CommandStatus MCommandHandler::Operate(const opendnp3::AnalogOutputInt32 &arCommand, uint16_t aIndex, opendnp3::IUpdateHandler &handler, opendnp3::OperateType opType)
{
    return opendnp3::CommandStatus::NOT_SUPPORTED;
}

opendnp3::CommandStatus MCommandHandler::Select(const opendnp3::AnalogOutputFloat32 &arCommand, uint16_t aIndex)
{
    return opendnp3::CommandStatus::NOT_SUPPORTED;
}

opendnp3::CommandStatus MCommandHandler::Operate(const opendnp3::AnalogOutputFloat32 &arCommand, uint16_t aIndex, opendnp3::IUpdateHandler &handler, opendnp3::OperateType opType)
{
    return opendnp3::CommandStatus::NOT_SUPPORTED;
}

opendnp3::CommandStatus MCommandHandler::Select(const opendnp3::AnalogOutputDouble64 &arCommand, uint16_t aIndex)
{
    return opendnp3::CommandStatus::NOT_SUPPORTED;
}

opendnp3::CommandStatus MCommandHandler::Operate(const opendnp3::AnalogOutputDouble64 &arCommand, uint16_t aIndex, opendnp3::IUpdateHandler &handler, opendnp3::OperateType opType)
{
    return opendnp3::CommandStatus::NOT_SUPPORTED;
}

opendnp3::DNPTime MOutstationApplication::Now()
{
    return opendnp3::DNPTime(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
}

bool MOutstationApplication::SupportsWriteAbsoluteTime()
{
    return true;
}

bool MOutstationApplication::WriteAbsoluteTime(const opendnp3::UTCTimestamp &timestamp)
{
    iin.needTime = false;
    time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp.msSinceEpoch)));
    char str[64];
    strftime(str, sizeof(str), "TIME SYNC: %Y-%m-%d %H:%M:%S", gmtime(&t));
    m_slave->AddLog(str);
    return true;
}

opendnp3::ApplicationIIN MOutstationApplication::GetApplicationIIN() const
{
    return iin;
}

MSlave::MSlave(MPanelSlave *ps, std::shared_ptr<opendnp3::IChannel> ch, const std::string &name, opendnp3::LogLevels fl, const opendnp3::OutstationStackConfig &cfg) : panel_slave(ps), stackconfig(cfg), moa(std::make_shared<MOutstationApplication>(this))
{
    work_random = false;
    _outstation = ch->AddOutstation(name.c_str(), std::make_shared<MCommandHandler>(this), moa, stackconfig);
}

void MSlave::UpdateBinary(opendnp3::Binary::Type state, opendnp3::BinaryQuality flags, size_t index)
{
    opendnp3::Flags f;
    f.Set(flags);
    builder.Update(opendnp3::Binary(state, f, moa->Now()), index);
    _outstation->Apply(builder.Build());
}

void MSlave::UpdateDouble(opendnp3::DoubleBit state, opendnp3::DoubleBitBinaryQuality flags, size_t index)
{
    opendnp3::Flags f;
    f.Set(flags);
    builder.Update(opendnp3::DoubleBitBinary(state, f, moa->Now()), index);
    _outstation->Apply(builder.Build());
}

void MSlave::UpdateAnalog(opendnp3::Analog::Type state, opendnp3::AnalogQuality flags, size_t index)
{
    opendnp3::Flags f;
    f.Set(flags);
    builder.Update(opendnp3::Analog(state, f, moa->Now()), index);
    _outstation->Apply(builder.Build());
}

void MSlave::UpdateCounter(opendnp3::Counter::Type state, opendnp3::CounterQuality flags, size_t index)
{
    opendnp3::Flags f;
    f.Set(flags);
    builder.Update(opendnp3::Counter(state, f, moa->Now()), index);
    _outstation->Apply(builder.Build());
}

void MSlave::FreezeCounter(size_t index)
{
    builder.FreezeCounter(index, false);
    _outstation->Apply(builder.Build());
}

void MSlave::UpdateBinaryOutputStatus(opendnp3::BinaryOutputStatus::Type state, opendnp3::BinaryOutputStatusQuality flags, size_t index)
{
    opendnp3::Flags f;
    f.Set(flags);
    builder.Update(opendnp3::BinaryOutputStatus(state, f, moa->Now()), index);
    _outstation->Apply(builder.Build());
}

void MSlave::UpdateAnalogOutputStatus(opendnp3::AnalogOutputStatus::Type state, opendnp3::AnalogOutputStatusQuality flags, size_t index)
{
    opendnp3::Flags f;
    f.Set(flags);
    builder.Update(opendnp3::AnalogOutputStatus(state, f, moa->Now()), index);
    _outstation->Apply(builder.Build());
}

void MSlave::NeedTimeSync()
{
    moa->NeedTimeSync();
}

void MSlave::AddLog(const std::string &str)
{
    panel_slave->AddLog(str);
}

void MSlave::Start()
{
    _outstation->Enable();
}

void MSlave::Shutdown()
{
    StopRandomize();
    _outstation->Shutdown();
}

void MSlave::StartRandomize(std::size_t ms)
{
    work_random = true;
    randomize_thread = std::thread([this, ms]() {
        std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now();
        while (work_random)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(9));
            if(tp + std::chrono::milliseconds(ms) <= std::chrono::steady_clock::now())
            {
                tp = std::chrono::steady_clock::now();
                for (std::size_t i : binary_random)
                {
                    bool v = rand() % 2;
                    opendnp3::Flags f;
                    f.Set(opendnp3::BinaryQuality::ONLINE);
                    builder.Update(opendnp3::Binary(v, f, moa->Now()), i);
                    _outstation->Apply(builder.Build());
                    panel_slave->UpdateBinaryValueCell(i, v);
                }
            }
        } });
}

void MSlave::StopRandomize()
{
    if(work_random)
    {
        work_random = false;
        randomize_thread.join();
    }
    binary_random.clear();    
}

class MChannelListener final : public opendnp3::IChannelListener, private opendnp3::Uncopyable
{
public:
    MChannelListener(MFrame *mf, const std::string &cn) : mframe(mf), channelname(cn) {}
    void OnStateChange(opendnp3::ChannelState state) override
    {
        mframe->AddLog(channelname + ": " + opendnp3::ChannelStateSpec::to_human_string(state));
    }

public:
    MFrame *mframe;
    std::string channelname;
};

MManager::MManager(MFrame *mf) : opendnp3::DNP3Manager(thread_count(), std::shared_ptr<LogToList>(new LogToList(mf))), mframe(mf)
{
}

std::shared_ptr<opendnp3::IChannel> MManager::AddTCPServer(const std::string &name, const std::string &addr, std::uint16_t port)
{
    auto pChannel = opendnp3::DNP3Manager::AddTCPServer(name, opendnp3::levels::NORMAL, opendnp3::ServerAcceptMode::CloseExisting,
                                                        opendnp3::IPEndpoint(addr, port), std::make_shared<MChannelListener>(mframe, name));
    return pChannel;
}

std::shared_ptr<opendnp3::IChannel> MManager::AddSerial(const std::string &name, const opendnp3::SerialSettings &settings)
{
    auto pChannel = opendnp3::DNP3Manager::AddSerial(name, opendnp3::levels::NORMAL, opendnp3::ChannelRetry::Default(), settings,
                                                     std::make_shared<MChannelListener>(mframe, name));
    return pChannel;
}

unsigned int MManager::thread_count()
{
    unsigned int n = std::thread::hardware_concurrency();
    return n == 0 ? 1 : n;
}
