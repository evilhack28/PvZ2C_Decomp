//
//  LogDBInfo.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "LogCollector/LogDBInfo.h"

#include <sstream>

#include "DNode/DIniFile.h"
#include "logServer/LogServer.h"

LogDBInfo* LogDBInfo::s_pInstance = NULL;

LogDBInfo* LogDBInfo::getInstance()
{
	if (!s_pInstance)
	{
		s_pInstance = new LogDBInfo();
		s_pInstance->loadDB();
	}
	return s_pInstance;
}

bool LogDBInfo::loadDB()
{
	return load("LogServerTable.cfg");
}

bool LogDBInfo::load(const std::string& fileName)
{
	m_tableInfos.clear();

	DIniFile ini;
	DString content("[TabaleColumns]\n        GameStart=Device_ID,User_ID,Character_ID,Client_time,Version_ID,Channel_ID,Session_ID,Project_Code,Behavior_ID,OS_Version,Device_Model,Connect_type,Local_IP,Public_IP,CPU,GPU_Model,Resolution_of_Screen,Memory,Storage\n            GameStart_Funnel=Device_ID,User_ID,Character_ID,Client_time,Version_ID,Channel_ID,Session_ID,Project_Code,Behavior_ID,Duration_Time\n            Register=Device_ID,User_ID,Character_ID,Client_time,Version_ID,Channel_ID,Server_ID,Session_ID,Project_Code,Device_Model,OS_Version\n            Item_Login=Device_ID,User_ID,Character_ID,Client_time,Version_ID,Channel_ID,Server_ID,Session_ID,Project_Code,Item\n        Recharge_Info=Device_ID,User_ID,Character_ID,Client_time,Version_ID,Channel_ID,Server_ID,Session_ID,Project_Code,Pay_SN,Is_success,SKU_ID,Unit_price,Pay_Source,Platform,Return_code,Level,VIP_level_before,VIP_level_after,Result\n        Ingame_Behavior=Device_ID,User_ID,Character_ID,Client_time,Version_ID,Channel_ID,Server_ID,Session_ID,Project_Code,Behavior_ID,D1,D2,D3,D4,Result");
	bool ret = ini.initWithString(content.c_str(), false);
	if (ret)
	{
		DIniField* field = ini.getField("TabaleColumns");
		if (field)
		{
			std::map<std::string, DIniItem> items = field->getItemsList();
			std::map<std::string, DIniItem>::iterator it = items.begin();
			std::map<std::string, DIniItem>::iterator end = items.end();
			for (; it != end; ++it)
			{
				std::pair<const std::string, DIniItem>& item = *it;
				DString value(item.second.getValue().c_str());
				std::vector<DString> cols = value.split(",");
				m_tableInfos[item.first] = cols;
			}
		}
		else
		{
			ret = false;
		}
	}
	return ret;
}

void LogDBInfo::sendMsg(const std::string& tableName, const DValue& value)
{
	if (!value.isDValueMap())
		return;

	TableInfo::iterator it = m_tableInfos.find(tableName);
	if (it != m_tableInfos.end())
	{
		LogServer* logServer = LogServer::Instance();
		logServer->AppendMsg(tableName);

		DValueMap valueMap = value.asDValueMap();

		std::vector<DString>& cols = (*it).second;
		std::vector<DString>::iterator cit = cols.begin();
		std::vector<DString>::iterator cend = cols.end();
		for (; cit != cend; ++cit)
		{
			DValueMap::iterator vit = valueMap.find((*cit).c_str());
			if (vit != valueMap.end())
			{
				const DValue& v = (*vit).second;
				if (v.isDValueVector())
				{
					std::stringstream ss;
					ss.str("");
					DValueVector vec = v.asDValueVector();
					DValueVector::iterator i = vec.begin();
					DValueVector::iterator e = vec.end();
					for (; i != e; ++i)
					{
						DValue item = *i;
						ss << item.asString() << ",";
					}
					ss << ";";
					logServer->AppendMsg(ss.str());
				}
				else if (v.isDValueMap())
				{
					std::stringstream ss;
					ss.str("");
					DValueMap m = v.asDValueMap();
					DValueMap::iterator i = m.begin();
					DValueMap::iterator e = m.end();
					for (; i != e; ++i)
					{
						std::pair<const std::string, DValue> item = *i;
						ss << item.first << "," << item.second.asString() << ";";
					}
					logServer->AppendMsg(ss.str());
				}
				else if (v.isIntKeyMap())
				{
					std::stringstream ss;
					ss.str("");
					DValueMapIntKey m = v.asIntKeyMap();
					DValueMapIntKey::iterator i = m.begin();
					DValueMapIntKey::iterator e = m.end();
					for (; i != e; ++i)
					{
						std::pair<const int, DValue> item = *i;
						ss << item.first << "," << item.second.asString() << ";";
					}
					logServer->AppendMsg(ss.str());
				}
				else
				{
					logServer->AppendMsg(v.asString());
				}
			}
			else
			{
				logServer->AppendMsg("");
			}
		}

		logServer->SendMsg();
	}
}
