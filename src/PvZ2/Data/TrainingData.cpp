//
//  TrainingData.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-19.
//

#include "SexyAppFramework/Common.h"

#include "TrainingCamp.h"

/////////////// Accessors ///////////////

bool TrainingData::IsEmpty() const
{
	return m_haveNum <= 0 && m_trainNum <= 0;
}
