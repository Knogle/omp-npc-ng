#pragma once

#include "bridge_runtime.hpp"

namespace ompnpcng::pawn_bridge
{
struct NPCEvents final : public NPCEventHandler
{
	void onNPCFinishMove(INPC& npc) override
	{
		callAllInEntryFirst("OnNPCFinishMove", DefaultReturnValue_True, npc.getID());
	}

	void onNPCCreate(INPC& npc) override
	{
		callAllInEntryFirst("OnNPCCreate", DefaultReturnValue_True, npc.getID());
	}

	void onNPCDestroy(INPC& npc) override
	{
		callAllInEntryFirst("OnNPCDestroy", DefaultReturnValue_True, npc.getID());
	}

	void onNPCWeaponStateChange(INPC& npc, PlayerWeaponState newState, PlayerWeaponState oldState) override
	{
		callAllInEntryFirst("OnNPCWeaponStateChange", DefaultReturnValue_True, npc.getID(), int(newState), int(oldState));
	}

	bool onNPCTakeDamage(INPC& npc, IPlayer& damager, float damage, uint8_t weapon, BodyPart bodyPart) override
	{
		return !!callAllInEntryFirst("OnNPCTakeDamage", DefaultReturnValue_True, npc.getID(), damager.getID(), damage, weapon, int(bodyPart));
	}

	bool onNPCGiveDamage(INPC& npc, IPlayer& damaged, float damage, uint8_t weapon, BodyPart bodyPart) override
	{
		return !!callAllInEntryFirst("OnNPCGiveDamage", DefaultReturnValue_True, npc.getID(), damaged.getID(), damage, weapon, int(bodyPart));
	}

	void onNPCDeath(INPC& npc, IPlayer* killer, int reason) override
	{
		callAllInEntryFirst("OnNPCDeath", DefaultReturnValue_True, npc.getID(), killer ? killer->getID() : INVALID_PLAYER_ID, reason);
	}

	void onNPCSpawn(INPC& npc) override
	{
		callAllInEntryFirst("OnNPCSpawn", DefaultReturnValue_True, npc.getID());
	}

	void onNPCRespawn(INPC& npc) override
	{
		callAllInEntryFirst("OnNPCRespawn", DefaultReturnValue_True, npc.getID());
	}

	void onNPCUpdate(INPC& npc) override
	{
		callAllInEntryFirst("OnNPCUpdate", DefaultReturnValue_True, npc.getID());
	}

	void onNPCStreamIn(INPC& npc, IPlayer& forPlayer) override
	{
		callAllInEntryFirst("OnNPCStreamIn", DefaultReturnValue_True, npc.getID(), forPlayer.getID());
	}

	void onNPCStreamOut(INPC& npc, IPlayer& forPlayer) override
	{
		callAllInEntryFirst("OnNPCStreamOut", DefaultReturnValue_True, npc.getID(), forPlayer.getID());
	}

	void onNPCPlaybackStart(INPC& npc, int recordId) override
	{
		callAllInEntryFirst("OnNPCPlaybackStart", DefaultReturnValue_True, npc.getID(), recordId);
	}

	void onNPCPlaybackEnd(INPC& npc, int recordId) override
	{
		callAllInEntryFirst("OnNPCPlaybackEnd", DefaultReturnValue_True, npc.getID(), recordId);
	}

	void onNPCVehicleEntryComplete(INPC& npc, IVehicle& vehicle, int seatId) override
	{
		callAllInEntryFirst("OnNPCVehicleEntryComplete", DefaultReturnValue_True, npc.getID(), vehicle.getID(), seatId);
	}

	void onNPCVehicleExitComplete(INPC& npc, IVehicle& vehicle) override
	{
		callAllInEntryFirst("OnNPCVehicleExitComplete", DefaultReturnValue_True, npc.getID(), vehicle.getID());
	}

	bool onNPCVehicleTakeDamage(INPC& npc, IPlayer& issuer, IVehicle& vehicle, float damage, uint8_t weapon, const Vector3& hitPos) override
	{
		return !!callAllInEntryFirst("OnNPCVehicleTakeDamage", DefaultReturnValue_True,
			npc.getID(), issuer.getID(), vehicle.getID(), damage, weapon, hitPos.x, hitPos.y, hitPos.z);
	}

	void onNPCChangeHeightPos(INPC& npc, float newZ, float oldZ) override
	{
		callAllInEntryFirst("OnNPCChangeHeightPos", DefaultReturnValue_True, npc.getID(), newZ, oldZ);
	}

	bool onNPCShotMissed(INPC& npc, const PlayerBulletData& bulletData) override
	{
		return callWeaponShot(npc, bulletData);
	}

	bool onNPCShotPlayer(INPC& npc, IPlayer& target, const PlayerBulletData& bulletData) override
	{
		(void)target;
		return callWeaponShot(npc, bulletData);
	}

	bool onNPCShotNPC(INPC& npc, INPC& target, const PlayerBulletData& bulletData) override
	{
		(void)target;
		return callWeaponShot(npc, bulletData);
	}

	bool onNPCShotVehicle(INPC& npc, IVehicle& target, const PlayerBulletData& bulletData) override
	{
		(void)target;
		return callWeaponShot(npc, bulletData);
	}

	bool onNPCShotObject(INPC& npc, IObject& target, const PlayerBulletData& bulletData) override
	{
		(void)target;
		return callWeaponShot(npc, bulletData);
	}

	bool onNPCShotPlayerObject(INPC& npc, IPlayerObject& target, const PlayerBulletData& bulletData) override
	{
		(void)target;
		return callWeaponShot(npc, bulletData);
	}

	void onNPCFinishNodePoint(INPC& npc, int nodeId, uint16_t pointId) override
	{
		callAllInEntryFirst("OnNPCFinishNodePoint", DefaultReturnValue_True, npc.getID(), nodeId, int(pointId));
	}

	void onNPCFinishNode(INPC& npc, int nodeId) override
	{
		callAllInEntryFirst("OnNPCFinishNode", DefaultReturnValue_True, npc.getID(), nodeId);
	}

	bool onNPCChangeNode(INPC& npc, int newNodeId, int oldNodeId) override
	{
		return !!callAllInEntryFirst("OnNPCChangeNode", DefaultReturnValue_True, npc.getID(), newNodeId, oldNodeId);
	}

	void onNPCFinishMovePath(INPC& npc, int pathId) override
	{
		callAllInEntryFirst("OnNPCFinishMovePath", DefaultReturnValue_True, npc.getID(), pathId);
	}

	void onNPCFinishMovePathPoint(INPC& npc, int pathId, int pointId) override
	{
		callAllInEntryFirst("OnNPCFinishMovePathPoint", DefaultReturnValue_True, npc.getID(), pathId, pointId);
	}

private:
	bool callWeaponShot(INPC& npc, const PlayerBulletData& bulletData)
	{
		cell ret = callInSidesWhile1(
			"OnNPCWeaponShot",
			npc.getID(),
			bulletData.weapon, int(bulletData.hitType), bulletData.hitID,
			bulletData.offset.x, bulletData.offset.y, bulletData.offset.z);
		if (ret)
		{
			ret = callInEntry(
				"OnNPCWeaponShot",
				DefaultReturnValue_True,
				npc.getID(),
				bulletData.weapon, int(bulletData.hitType), bulletData.hitID,
				bulletData.offset.x, bulletData.offset.y, bulletData.offset.z);
		}
		return !!ret;
	}
};
} // namespace ompnpcng::pawn_bridge
