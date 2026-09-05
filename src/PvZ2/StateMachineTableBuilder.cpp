// Reconstructed by EvilHack28 on 2026-09-05
#include "StateMachineTableBuilder.h"

StateMachineTableBuilder::StateMachineTableBuilder()
{
}

StateMachineTableBuilder::~StateMachineTableBuilder()
{
	for (size_t i = 0; i < m_stateMachineTableStorage.size(); ++i)
	{
		StateMachineTableBase* table = m_stateMachineTableStorage[i];
		delete table;
	}

	m_stateMachineTableStorage.clear();
	m_stateMachineTables.clear();
}
