#include "bridge_runtime.hpp"

namespace ompnpcng::pawn_bridge
{
State& state()
{
	static State runtime;
	return runtime;
}

void setCore(ICore* core)
{
	State& runtime = state();
	runtime.core = core;
	runtime.lookup.core = core;
	runtime.lookup.config = core ? &core->getConfig() : nullptr;
	runtime.lookup.players = core ? &core->getPlayers() : nullptr;
}

void refreshComponents(IComponentList& components)
{
	State& runtime = state();
	runtime.pawn = components.queryComponent<IPawnComponent>();
	runtime.npcs = components.queryComponent<INPCComponent>();
	runtime.lookup.actors = components.queryComponent<IActorsComponent>();
	runtime.lookup.checkpoints = components.queryComponent<ICheckpointsComponent>();
	runtime.lookup.classes = components.queryComponent<IClassesComponent>();
	runtime.lookup.console = components.queryComponent<IConsoleComponent>();
	runtime.lookup.databases = components.queryComponent<IDatabasesComponent>();
	runtime.lookup.dialogs = components.queryComponent<IDialogsComponent>();
	runtime.lookup.fixes = components.queryComponent<IFixesComponent>();
	runtime.lookup.gangzones = components.queryComponent<IGangZonesComponent>();
	runtime.lookup.menus = components.queryComponent<IMenusComponent>();
	runtime.lookup.objects = components.queryComponent<IObjectsComponent>();
	runtime.lookup.pickups = components.queryComponent<IPickupsComponent>();
	runtime.lookup.recordings = components.queryComponent<IRecordingsComponent>();
	runtime.lookup.textdraws = components.queryComponent<ITextDrawsComponent>();
	runtime.lookup.textlabels = components.queryComponent<ITextLabelsComponent>();
	runtime.lookup.timers = components.queryComponent<ITimersComponent>();
	runtime.lookup.vars = components.queryComponent<IVariablesComponent>();
	runtime.lookup.vehicles = components.queryComponent<IVehiclesComponent>();
	runtime.lookup.models = components.queryComponent<ICustomModelsComponent>();
	runtime.lookup.npcs = runtime.npcs;
}

void clear()
{
	State& runtime = state();
	runtime = State {};
}

void forget(IComponent& component)
{
	State& runtime = state();
	if (&component == runtime.pawn)
	{
		runtime.pawn = nullptr;
	}
	if (&component == runtime.npcs)
	{
		runtime.npcs = nullptr;
		runtime.lookup.npcs = nullptr;
	}
	if (&component == runtime.lookup.actors)
	{
		runtime.lookup.actors = nullptr;
	}
	if (&component == runtime.lookup.checkpoints)
	{
		runtime.lookup.checkpoints = nullptr;
	}
	if (&component == runtime.lookup.classes)
	{
		runtime.lookup.classes = nullptr;
	}
	if (&component == runtime.lookup.console)
	{
		runtime.lookup.console = nullptr;
	}
	if (&component == runtime.lookup.databases)
	{
		runtime.lookup.databases = nullptr;
	}
	if (&component == runtime.lookup.dialogs)
	{
		runtime.lookup.dialogs = nullptr;
	}
	if (&component == runtime.lookup.fixes)
	{
		runtime.lookup.fixes = nullptr;
	}
	if (&component == runtime.lookup.gangzones)
	{
		runtime.lookup.gangzones = nullptr;
	}
	if (&component == runtime.lookup.menus)
	{
		runtime.lookup.menus = nullptr;
	}
	if (&component == runtime.lookup.objects)
	{
		runtime.lookup.objects = nullptr;
	}
	if (&component == runtime.lookup.pickups)
	{
		runtime.lookup.pickups = nullptr;
	}
	if (&component == runtime.lookup.recordings)
	{
		runtime.lookup.recordings = nullptr;
	}
	if (&component == runtime.lookup.textdraws)
	{
		runtime.lookup.textdraws = nullptr;
	}
	if (&component == runtime.lookup.textlabels)
	{
		runtime.lookup.textlabels = nullptr;
	}
	if (&component == runtime.lookup.timers)
	{
		runtime.lookup.timers = nullptr;
	}
	if (&component == runtime.lookup.vars)
	{
		runtime.lookup.vars = nullptr;
	}
	if (&component == runtime.lookup.vehicles)
	{
		runtime.lookup.vehicles = nullptr;
	}
	if (&component == runtime.lookup.models)
	{
		runtime.lookup.models = nullptr;
	}
}
} // namespace ompnpcng::pawn_bridge

PawnLookup* getAmxLookups()
{
	return &ompnpcng::pawn_bridge::state().lookup;
}
