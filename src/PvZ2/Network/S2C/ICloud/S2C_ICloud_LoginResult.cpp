//
//  S2C_ICloud_LoginResult.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-12.
//

#include "SexyAppFramework/Common.h"

#include "NetworkData.h"
#include "ReflectionBuilder.h"

/////////////// Reflection ///////////////

RT_CLASS_IMPLEMENT(S2C_ICloud_LoginResult);

void S2C_ICloud_LoginResult::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(S2C_ICloud_LoginResult);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(INetworkData);

		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_UserId, ui);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int64, m_serverTime, st);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_sk, sk);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_signature, s);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_OldKey, ok);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_NewKey, nk);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, m_encrypt, uk);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(pvztime_t, m_saveInterval, upis);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_createdTime, rt);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int32, m_idEncryptIndex, i);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, m_isNewUser, in);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(int, m_PlayerReturnDays, day);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, m_bindUniqueID, bui);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(bool, m_newAccountBind, nab);
		REFLECTION_CLASSBUILDER_FIELD_RENAME(std::string, m_stageURL, stage);
	REFLECTION_CLASSBUILDER_END(S2C_ICloud_LoginResult);
}
