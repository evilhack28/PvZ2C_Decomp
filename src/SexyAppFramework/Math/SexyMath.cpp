//
//  SexyMath.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-30.
//

#include "SexyAppFramework/Common.h"
#include "SexyMath.h"
#include "Point.h"
#include "Color.h"
#include "SexyVector.h"

namespace Sexy
{

template Point SexyMath::Lerp<Point>(const Point&, const Point&, float);
template FPoint SexyMath::Lerp<FPoint>(const FPoint&, const FPoint&, float);
template SexyVector2 SexyMath::Lerp<SexyVector2>(const SexyVector2&, const SexyVector2&, float);
template SexyVector3 SexyMath::Lerp<SexyVector3>(const SexyVector3&, const SexyVector3&, float);
template Color SexyMath::Lerp<Color>(const Color&, const Color&, float);

}
