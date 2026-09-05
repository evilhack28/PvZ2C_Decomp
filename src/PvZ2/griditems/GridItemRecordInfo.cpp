// Reconstructed by EvilHack28 on 2026-09-05
#include "BoardEntity.h"
#include "SexyVector.h"

class GridItemRecordInfo
{
public:
	GridItemRecordInfo(Sexy::RtWeakPtr<BoardEntity> i_boardEntity, const Sexy::SexyVector3& i_position);
	GridItemRecordInfo(const GridItemRecordInfo& i_other);
	GridItemRecordInfo(GridItemRecordInfo&& i_other);
	~GridItemRecordInfo();

	GridItemRecordInfo& operator=(const GridItemRecordInfo& i_other);

	Sexy::RtWeakPtr<BoardEntity> m_boardEntity;
	Sexy::SexyVector3 m_position;
};

GridItemRecordInfo::GridItemRecordInfo(Sexy::RtWeakPtr<BoardEntity> i_boardEntity, const Sexy::SexyVector3& i_position)
	: m_boardEntity(i_boardEntity)
	, m_position(i_position)
{
}

GridItemRecordInfo::GridItemRecordInfo(const GridItemRecordInfo& i_other)
	: m_boardEntity(i_other.m_boardEntity)
	, m_position(i_other.m_position)
{
}

GridItemRecordInfo::GridItemRecordInfo(GridItemRecordInfo&& i_other)
	: m_boardEntity(i_other.m_boardEntity)
	, m_position(i_other.m_position)
{
}

GridItemRecordInfo::~GridItemRecordInfo()
{
}

GridItemRecordInfo& GridItemRecordInfo::operator=(const GridItemRecordInfo& i_other)
{
	m_boardEntity = i_other.m_boardEntity;
	m_position = i_other.m_position;
	return *this;
}
