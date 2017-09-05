#include "object.h"

GObject::GObject()
: bIsInitialized(false)
, bIsFinalized(false)
, bIsEnabledTick(false)
, bIsActivated(false)
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
bool GObject::IsActivated() const
{
	return bIsActivated;
}

void GObject::initialize()
{
}

void GObject::finalize()
{
}