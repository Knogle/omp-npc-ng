#include <Server/Components/Pawn/pawn.hpp>
#include <sdk.hpp>

static const UID OMPNPCNG_PAWN_UID = UID(0xa2c309d8b6a94611);

class OmpNpcNgPawnBridge final : public IComponent, public PawnEventHandler
{
public:
	PROVIDE_UID(OMPNPCNG_PAWN_UID);

	StringView componentName() const override
	{
		return "OMPNPCNGPawn";
	}

	SemanticVersion componentVersion() const override
	{
		return SemanticVersion(OMP_VERSION_MAJOR, OMP_VERSION_MINOR, OMP_VERSION_PATCH, BUILD_NUMBER);
	}

	void onLoad(ICore* c) override
	{
		core_ = c;
	}

	void onInit(IComponentList* components) override
	{
		if (!components)
		{
			return;
		}

		pawn_ = components->queryComponent<IPawnComponent>();
		if (pawn_)
		{
			pawn_->getEventDispatcher().addEventHandler(this);
		}
	}

	void onFree(IComponent* component) override
	{
		if (component == pawn_)
		{
			pawn_ = nullptr;
		}
	}

	void free() override
	{
		if (pawn_)
		{
			pawn_->getEventDispatcher().removeEventHandler(this);
			pawn_ = nullptr;
		}

		delete this;
	}

	void reset() override
	{
	}

	void onAmxLoad(IPawnScript& script) override
	{
		(void)script;
		// Native registration moves here once the forked NPC script surface is ported.
	}

	void onAmxUnload(IPawnScript& script) override
	{
		(void)script;
	}

private:
	ICore* core_ = nullptr;
	IPawnComponent* pawn_ = nullptr;
};

COMPONENT_ENTRY_POINT()
{
	return new OmpNpcNgPawnBridge();
}
