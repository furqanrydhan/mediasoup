#ifndef MS_RTC_CUSTOM_PARAMETERS_H
#define MS_RTC_CUSTOM_PARAMETERS_H

#include "common.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <json/json.h>

namespace RTC
{
	class CustomParameterValue
	{
		private:
			enum class Type
			{
				BOOLEAN = 1,
				INTEGER,
				DOUBLE,
				STRING
			};

		public:
			CustomParameterValue() {};

			CustomParameterValue(bool booleanValue) :
				type(Type::BOOLEAN),
				booleanValue(booleanValue)
			{}

			CustomParameterValue(int32_t integerValue) :
				type(Type::INTEGER),
				integerValue(integerValue)
			{}

			CustomParameterValue(double doubleValue) :
				type(Type::DOUBLE),
				doubleValue(doubleValue)
			{}

			CustomParameterValue(std::string& stringValue) :
				type(Type::STRING),
				stringValue(stringValue)
			{}

			Json::Value toJson()
			{
				switch (this->type)
				{
					case Type::BOOLEAN:
						return this->booleanValue;
					case Type::INTEGER:
						return (Json::Int)this->integerValue;
					case Type::DOUBLE:
						return this->doubleValue;
					case Type::STRING:
						return this->stringValue;
					default:
						return Json::nullValue;
				}
			}

			bool IsBoolean()
			{
				return this->type == Type::BOOLEAN;
			}

			bool IsInteger()
			{
				return this->type == Type::INTEGER;
			}

			bool IsPositiveInteger()
			{
				return this->type == Type::INTEGER && this->integerValue >= 0;
			}

			bool IsDouble()
			{
				return this->type == Type::DOUBLE;
			}

			bool IsPositiveDouble()
			{
				return this->type == Type::DOUBLE && this->doubleValue >= 0;
			}

			bool IsString()
			{
				return this->type == Type::STRING;
			}

		private:
			Type        type;

		public:
			bool        booleanValue = false;
			int32_t     integerValue = 0;
			double      doubleValue = 0.0;
			std::string stringValue;
	};

	typedef std::unordered_map<std::string, CustomParameterValue> CustomParameters;

	void FillCustomParameters(CustomParameters& parameters, Json::Value& data);
}

#endif
