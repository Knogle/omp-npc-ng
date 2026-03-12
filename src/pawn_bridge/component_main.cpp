#include "bridge_runtime.hpp"
#include "npc_events.hpp"
#include <Server/Components/Pawn/Impl/pawn_natives.hpp>

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

	void onLoad(ICore* core) override
	{
		ompnpcng::pawn_bridge::setCore(core);
	}

	void onInit(IComponentList* components) override
	{
		if (!components)
		{
			return;
		}

		ompnpcng::pawn_bridge::refreshComponents(*components);
		attachHandlers();
	}

	void onReady() override
	{
		attachHandlers();
	}

	void onFree(IComponent* component) override
	{
		if (!component)
		{
			return;
		}
		if (component == ompnpcng::pawn_bridge::pawn())
		{
			pawnAttached_ = false;
		}
		if (component == ompnpcng::pawn_bridge::npcs())
		{
			npcAttached_ = false;
		}
		ompnpcng::pawn_bridge::forget(*component);
	}

	void free() override
	{
		if (pawnAttached_ && ompnpcng::pawn_bridge::pawn())
		{
			ompnpcng::pawn_bridge::pawn()->getEventDispatcher().removeEventHandler(this);
		}
		if (npcAttached_ && ompnpcng::pawn_bridge::npcs())
		{
			ompnpcng::pawn_bridge::npcs()->getEventDispatcher().removeEventHandler(&npcEvents_);
		}
		ompnpcng::pawn_bridge::clear();
		delete this;
	}

	void reset() override
	{
	}

	void onAmxLoad(IPawnScript& script) override
	{
		pawn_natives::AmxLoad(script.GetAMX());
	}

	void onAmxUnload(IPawnScript& script) override
	{
		(void)script;
	}

private:
	void attachHandlers()
	{
		if (!pawnAttached_ && ompnpcng::pawn_bridge::pawn())
		{
			ompnpcng::pawn_bridge::pawn()->getEventDispatcher().addEventHandler(this);
			pawnAttached_ = true;
		}
		if (!npcAttached_ && ompnpcng::pawn_bridge::npcs())
		{
			ompnpcng::pawn_bridge::npcs()->getEventDispatcher().addEventHandler(&npcEvents_);
			npcAttached_ = true;
		}
	}

	bool pawnAttached_ = false;
	bool npcAttached_ = false;
	ompnpcng::pawn_bridge::NPCEvents npcEvents_;
};

COMPONENT_ENTRY_POINT()
{
	return new OmpNpcNgPawnBridge();
}
