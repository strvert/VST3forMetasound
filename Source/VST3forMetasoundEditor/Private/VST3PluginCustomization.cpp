#include "VST3PluginCustomization.h"

#include "DetailLayoutBuilder.h"

TSharedRef<IDetailCustomization> FVST3PluginDetails::MakeInstance()
{
	return MakeShared<FVST3PluginDetails>();
}

void FVST3PluginDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
}
