#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "IDetailCustomNodeBuilder.h"


class FVST3PluginDetails : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
};


class FVST3PluginNodeBuilder: public IDetailCustomNodeBuilder, public TSharedFromThis<FVST3PluginNodeBuilder>
{
public:
	
};
