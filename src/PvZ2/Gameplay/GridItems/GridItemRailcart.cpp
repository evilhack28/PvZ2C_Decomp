//
//  GridItemRailcart.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-29.
//

#include "SexyAppFramework/Common.h"

#include "GridItemPropertySheet.h"
#include "GridItemRailcart.h"

GridItemRailcart::GridItemRailcart()
{
	m_owningTouchIdent = 0;
}

GridItemRailcart::~GridItemRailcart()
{
}

GridItemRailcartPropertySheet::~GridItemRailcartPropertySheet()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRailcart);

void GridItemRailcart::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRailcart);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItem);

	REFLECTION_CLASSBUILDER_END(GridItemRailcart);
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(GridItemRailcartPropertySheet);

void GridItemRailcartPropertySheet::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(GridItemRailcartPropertySheet);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GridItemPropertySheet);

		REFLECTION_CLASSBUILDER_FIELD(std::string, ImagePrefix);
	REFLECTION_CLASSBUILDER_END(GridItemRailcartPropertySheet);
}

#include "GridItem.h"
void GridItemRailcart::onGridItemInitialize()
{
	 GridItem::onGridItemInitialize();
}
