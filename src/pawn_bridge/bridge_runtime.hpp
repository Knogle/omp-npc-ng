#pragma once

#include <Server/Components/Pawn/pawn.hpp>

namespace ompnpcng::pawn_bridge
{
struct State
{
	ICore* core = nullptr;
	IPawnComponent* pawn = nullptr;
	INPCComponent* npcs = nullptr;
	PawnLookup lookup {};
};

State& state();
void setCore(ICore* core);
void refreshComponents(IComponentList& components);
void clear();
void forget(IComponent& component);

inline ICore* core()
{
	return state().core;
}

inline IPawnComponent* pawn()
{
	return state().pawn;
}

inline INPCComponent* npcs()
{
	return state().npcs;
}

inline IObjectsComponent* objects()
{
	return state().lookup.objects;
}

inline IVehiclesComponent* vehicles()
{
	return state().lookup.vehicles;
}

template <typename... T>
cell callAllInEntryFirst(char const* name, DefaultReturnValue defaultRetValue, T... args)
{
	cell ret = static_cast<cell>(defaultRetValue);
	auto* main = pawn() ? pawn()->mainScript() : nullptr;
	if (main)
	{
		ret = main->Call(name, defaultRetValue, args...);
	}
	if (pawn())
	{
		for (IPawnScript* script : pawn()->sideScripts())
		{
			ret = script->Call(name, defaultRetValue, args...);
		}
	}
	return ret;
}

template <typename... T>
cell callInSidesWhile1(char const* name, T... args)
{
	cell ret = 1;
	if (!pawn())
	{
		return ret;
	}
	for (IPawnScript* script : pawn()->sideScripts())
	{
		ret = script->Call(name, DefaultReturnValue_True, args...);
		if (!ret)
		{
			break;
		}
	}
	return ret;
}

template <typename... T>
cell callInEntry(char const* name, DefaultReturnValue defaultRetValue, T... args)
{
	cell ret = static_cast<cell>(defaultRetValue);
	auto* main = pawn() ? pawn()->mainScript() : nullptr;
	if (main)
	{
		ret = main->Call(name, defaultRetValue, args...);
	}
	return ret;
}
} // namespace ompnpcng::pawn_bridge
