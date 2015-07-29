#ifndef __CONVERSIONS_H_
#define __CONVERSIONS_H_

#include <string>

#include <openpal/executor/TimeDuration.h>
#include <openpal/container/Buffer.h>

#include <opendnp3/StackStatistics.h>
#include <opendnp3/LogLevels.h>

#include <opendnp3/gen/ChannelState.h>

#include <opendnp3/app/MeasurementTypes.h>
#include <opendnp3/app/TimeAndInterval.h>
#include <opendnp3/app/ControlRelayOutputBlock.h>
#include <opendnp3/app/AnalogOutput.h>
#include <opendnp3/app/OctetString.h>
#include <opendnp3/app/Indexed.h>
#include <opendnp3/app/BinaryCommandEvent.h>
#include <opendnp3/app/AnalogCommandEvent.h>
#include <opendnp3/app/SecurityStat.h>
#include <opendnp3/app/parsing/ICollection.h>
#include <opendnp3/app/GroupVariationID.h>
#include <opendnp3/app/User.h>

#include <opendnp3/master/CommandResponse.h>
#include <opendnp3/master/MasterStackConfig.h>

#include <opendnp3/outstation/OutstationStackConfig.h>
#include <opendnp3/link/LinkChannelStatistics.h>

#include "CollectionAdapter.h"

#include <asiopal/SerialTypes.h>

using namespace System::Collections::Generic;
using namespace Automatak::DNP3::Interface;

namespace Automatak
{
	namespace DNP3
	{
		namespace Adapter
		{

			private class Conversions
			{
			public:

				static openpal::TimeDuration ConvertMilliseconds(System::UInt64 ms);

				static openpal::TimeDuration ConvertTimespan(System::TimeSpan ts);

				static opendnp3::ClassField ConvertClassField(ClassField classField);

				// Convert a .NET string to a C++ string
				static std::string ConvertString(System::String^ s);
				static System::String^ ConvertString(const std::string& s);

				// Converting channel state enumeration
				static ChannelState ConvertChannelState(opendnp3::ChannelState aState);

				static IChannelStatistics^ ConvertChannelStats(const opendnp3::LinkChannelStatistics& statistics);

				static IStackStatistics^ ConvertStackStats(const opendnp3::StackStatistics& statistics);

				// Convert the command status enumeration
				static CommandStatus ConvertCommandStatus(opendnp3::CommandStatus status);
				static opendnp3::CommandStatus ConvertCommandStatus(CommandStatus status);				

				static CommandResponse ConvertCommandResponse(opendnp3::CommandResponse response);

				//functions for Converting binary outputs

				static ControlCode ConvertControlCode(opendnp3::ControlCode code);
				static opendnp3::ControlCode Conversions::ConvertControlCode(ControlCode code);


				static ControlRelayOutputBlock^ ConvertCommand(const opendnp3::ControlRelayOutputBlock& bo);
				static opendnp3::ControlRelayOutputBlock ConvertCommand(ControlRelayOutputBlock^ bo);

				//functions for Converting setpoints

				static opendnp3::AnalogOutputInt32 ConvertCommand(AnalogOutputInt32^ sp);
				static AnalogOutputInt32^ ConvertCommand(const opendnp3::AnalogOutputInt32& sp);

				static opendnp3::AnalogOutputInt16 ConvertCommand(AnalogOutputInt16^ sp);
				static AnalogOutputInt16^ ConvertCommand(const opendnp3::AnalogOutputInt16& sp);

				static opendnp3::AnalogOutputFloat32 ConvertCommand(AnalogOutputFloat32^ sp);
				static AnalogOutputFloat32^ ConvertCommand(const opendnp3::AnalogOutputFloat32& sp);

				static opendnp3::AnalogOutputDouble64 ConvertCommand(AnalogOutputDouble64^ sp);
				static AnalogOutputDouble64^ ConvertCommand(const opendnp3::AnalogOutputDouble64& sp);

				//functions for Converting Measurement types
				static Binary^ ConvertMeas(opendnp3::Binary meas);
				static DoubleBitBinary^ ConvertMeas(opendnp3::DoubleBitBinary meas);
				static Analog^ ConvertMeas(opendnp3::Analog meas);
				static Counter^ ConvertMeas(opendnp3::Counter meas);
				static FrozenCounter^ ConvertMeas(opendnp3::FrozenCounter meas);
				static AnalogOutputStatus^ ConvertMeas(opendnp3::AnalogOutputStatus meas);
				static BinaryOutputStatus^ ConvertMeas(opendnp3::BinaryOutputStatus meas);
				static OctetString^ Conversions::ConvertMeas(const opendnp3::OctetString& meas);
				static TimeAndInterval^ Conversions::ConvertMeas(const opendnp3::TimeAndInterval& meas);
				static BinaryCommandEvent^ Conversions::ConvertMeas(const opendnp3::BinaryCommandEvent& meas);
				static AnalogCommandEvent^ Conversions::ConvertMeas(const opendnp3::AnalogCommandEvent& meas);
				static SecurityStat^ Conversions::ConvertMeas(const opendnp3::SecurityStat& meas);


				static opendnp3::Binary ConvertMeas(Binary^ meas);
				static opendnp3::DoubleBitBinary ConvertMeas(DoubleBitBinary^ meas);
				static opendnp3::Analog ConvertMeas(Analog^ meas);
				static opendnp3::Counter ConvertMeas(Counter^ meas);
				static opendnp3::FrozenCounter ConvertMeas(FrozenCounter^ meas);
				static opendnp3::AnalogOutputStatus ConvertMeas(AnalogOutputStatus^ meas);
				static opendnp3::BinaryOutputStatus ConvertMeas(BinaryOutputStatus^ meas);
				static opendnp3::TimeAndInterval ConvertMeas(TimeAndInterval^ meas);
				static opendnp3::BinaryCommandEvent ConvertMeas(BinaryCommandEvent^ meas);
				static opendnp3::AnalogCommandEvent ConvertMeas(AnalogCommandEvent^ meas);

				//Convert the configuration types
				static asiopal::SerialSettings ConvertSerialSettings(SerialSettings^ settings);
				static opendnp3::EventBufferConfig ConvertConfig(EventBufferConfig^ cm);

				static opendnp3::LinkConfig ConvertConfig(LinkConfig^ config);
				static opendnp3::MasterParams ConvertConfig(MasterConfig^ config);
				static opendnp3::OutstationConfig ConvertConfig(OutstationConfig^ config, opendnp3::IndexMode indexMode);
				static opendnp3::OutstationParams ConvertConfig(OutstationParams^ config, opendnp3::IndexMode indexMode);
				static opendnp3::MasterStackConfig ConvertConfig(MasterStackConfig^ config);
				static opendnp3::OutstationStackConfig ConvertConfig(OutstationStackConfig^ config);

				static opendnp3::DatabaseTemplate ConvertConfig(DatabaseTemplate^ config);

				static opendnp3::GroupVariationID Convert(PointClass clazz);

				static openpal::Buffer Convert(array<System::Byte>^ bytes);

				static User^ Convert(const opendnp3::User& user);


				template <class Target, class Source>
				static IndexedValue<Target>^ ConvertIndexValue(const opendnp3::Indexed<Source>& pair)
				{
					return gcnew IndexedValue<Target>(ConvertMeas(pair.value), pair.index);
				}

				template <class Target, class Source>
				static IEnumerable<IndexedValue<Target>^>^ ToIndexedEnumerable(const opendnp3::ICollection<opendnp3::Indexed<Source>>& values)
				{
					auto convert = [](const opendnp3::Indexed <Source> &value) -> IndexedValue<Target>^ {
						return ConvertIndexValue<Target, Source>(value);
					};

					auto adapter = CreateAdapter<opendnp3::Indexed<Source>, IndexedValue<Target>^>(convert);

					values.Foreach(adapter);
					return adapter.GetValues();
				}

			};

		}
	}
}

#endif
