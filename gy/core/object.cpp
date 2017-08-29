#include "object.h"

GObject::GObject()
: bIsInitialized(false)
, bIsFinalized(false)
, bIsEnabledTick(false)
{
}

GObject::~GObject()
{
}

bool GObject::IsEnabledTick() const
{
	return bIsEnabledTick;
}
void GObject::SetEnabledTick(bool bEnabledTick)
{
	bIsEnabledTick = bEnabledTick;
}
