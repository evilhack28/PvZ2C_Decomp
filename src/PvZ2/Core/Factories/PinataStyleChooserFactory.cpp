// Reconstructed by EvilHack28 on 2026-09-05
#include "PinataStyleChooserFactory.h"

PinataStyleChooserFactory::PinataStyleChooserFactory()
{
}

PinataStyleChooserFactory& PinataStyleChooserFactory::GetInstance()
{
	static PinataStyleChooserFactory sInstance;
	return sInstance;
}

PinataStyleChooser& PinataStyleChooserFactory::GetChooser()
{
	return m_defaultChooser;
}
