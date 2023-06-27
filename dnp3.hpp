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
#ifndef __DNP3H__
#define __DNP3H__
#include <bitset>
#include <list>
#include <thread>
#include <opendnp3/DNP3Manager.h>
#include <opendnp3/outstation/UpdateBuilder.h>

class MSlave;

class MCommandHandler : public opendnp3::ICommandHandler
{
public:
    MCommandHandler(MSlave* mw) : m_slave(mw) {}

    opendnp3::CommandStatus Select(const opendnp3::ControlRelayOutputBlock& arCommand, uint16_t aIndex) override;
	opendnp3::CommandStatus Operate(const opendnp3::ControlRelayOutputBlock& arCommand, uint16_t aIndex, opendnp3::IUpdateHandler& handler, opendnp3::OperateType opType)  override;
	opendnp3::CommandStatus Select(const opendnp3::AnalogOutputInt16& arCommand, uint16_t aIndex)  override;
	opendnp3::CommandStatus Operate(const opendnp3::AnalogOutputInt16& arCommand, uint16_t aIndex, opendnp3::IUpdateHandler& handler, opendnp3::OperateType opType)  override;
	opendnp3::CommandStatus Select(const opendnp3::AnalogOutputInt32& arCommand, uint16_t aIndex)  override;
	opendnp3::CommandStatus Operate(const opendnp3::AnalogOutputInt32& arCommand, uint16_t aIndex, opendnp3::IUpdateHandler& handler, opendnp3::OperateType opType)  override;
	opendnp3::CommandStatus Select(const opendnp3::AnalogOutputFloat32& arCommand, uint16_t aIndex)  override;
	opendnp3::CommandStatus Operate(const opendnp3::AnalogOutputFloat32& arCommand, uint16_t aIndex, opendnp3::IUpdateHandler& handler, opendnp3::OperateType opType)  override;
    opendnp3::CommandStatus Select(const opendnp3::AnalogOutputDouble64& arCommand, uint16_t aIndex)  override;
	opendnp3::CommandStatus Operate(const opendnp3::AnalogOutputDouble64& arCommand, uint16_t aIndex, opendnp3::IUpdateHandler& handler, opendnp3::OperateType opType)  override;
	void Begin() override final {}
	void End() override final {}
private:
    MSlave* m_slave;
};

class MOutstationApplication : public opendnp3::IOutstationApplication
{
public:
    MOutstationApplication(MSlave* ms) : m_slave(ms) { iin.needTime = false; }
    opendnp3::DNPTime Now() override;
    bool SupportsWriteAbsoluteTime() override final;
    bool WriteAbsoluteTime(const opendnp3::UTCTimestamp& timestamp) override final;
    opendnp3::ApplicationIIN GetApplicationIIN() const override final;

    void NeedTimeSync() { iin.needTime = true; }
    
private:
    MSlave* m_slave;
    opendnp3::ApplicationIIN iin;

};

class MPanelSlave;

class MSlave
{
public:
	MSlave(MPanelSlave* ps, std::shared_ptr<opendnp3::IChannel> ch,const std::string& name,opendnp3::LogLevels fl,const opendnp3::OutstationStackConfig& cfg);
	~MSlave() { }

    void UpdateBinary(opendnp3::Binary::Type state, opendnp3::BinaryQuality flags, size_t index);
    void UpdateDouble(opendnp3::DoubleBit state, opendnp3::DoubleBitBinaryQuality flags, size_t index);
    void UpdateAnalog(opendnp3::Analog::Type state, opendnp3::AnalogQuality flags, size_t index);
    void UpdateCounter(opendnp3::Counter::Type state, opendnp3::CounterQuality flags, size_t index);
    void FreezeCounter(size_t index);
    void UpdateBinaryOutputStatus(opendnp3::BinaryOutputStatus::Type state, opendnp3::BinaryOutputStatusQuality flags, size_t index);
    void UpdateAnalogOutputStatus(opendnp3::AnalogOutputStatus::Type state, opendnp3::AnalogOutputStatusQuality flags, size_t index);
    void NeedTimeSync();
    void AddLog(const std::string& str);

    void Start();
    void Shutdown();

    void StartRandomize(std::size_t ms);
    void StopRandomize();
    void AddBinaryRandom(std::size_t i) { binary_random.push_back(i); }

    struct AnalogRandom
    {
        AnalogRandom(bool _index, double from, double to) : index(_index), range(std::make_pair(from, to)) {}
        std::size_t index;
        std::pair<double, double> range;
    };

private:
    MPanelSlave* panel_slave;
    opendnp3::OutstationStackConfig stackconfig;
    std::shared_ptr<MOutstationApplication> moa;
    opendnp3::UpdateBuilder builder;
    std::shared_ptr<opendnp3::IOutstation> _outstation;
    bool work_random;
    std::thread randomize_thread;
    std::list<std::size_t> binary_random;
    std::list<std::size_t> dbinary_random;
    std::list<AnalogRandom> analog_random;
    std::list<std::size_t> counter_increment;
};

class MFrame;

class MManager : public opendnp3::DNP3Manager
{
public:
    MManager(MFrame* mf);
    std::shared_ptr<opendnp3::IChannel> AddTCPServer(const std::string& name,const std::string& addr,std::uint16_t port);
    std::shared_ptr<opendnp3::IChannel> AddSerial(const std::string& name,const opendnp3::SerialSettings& settings);
private:
    MFrame *mframe;
    static unsigned int thread_count();
};



#endif
