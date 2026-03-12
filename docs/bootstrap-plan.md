# omp-npc-ng bootstrap plan

Stand: 2026-03-12

## Goal

Turn the open.mp NPC implementation into an independently buildable fork with:

- a standalone NPC core component
- a separate Pawn bridge component
- room for FCNPC compatibility and future fork-only work

## Port order

### 1. Core first

Source basis:

- `open.mp/Server/Components/NPCs/`

Expected destination:

- `src/core/`

First milestone:

- component loads successfully as `OMPNPCNG`
- no extra features yet
- no script surface yet

### 2. Pawn bridge second

Source basis:

- `open.mp/Server/Components/Pawn/Scripting/NPC/Natives.cpp`

Expected destination:

- `src/pawn_bridge/`

Integration path:

- query `IPawnComponent`
- subscribe to `PawnEventHandler`
- register natives during `onAmxLoad`

First milestone:

- a tiny proof native is registered from the external bridge

### 3. FCNPC compatibility layer third

Targets:

- `pawno/include/fcnpc_compat.inc`
- fork-side callback/native mapping

First milestone:

- minimal lifecycle compatibility
- version/introspection helpers

## Dependency policy

This scaffold intentionally expects vendored copies of:

- `omp-sdk`
- `omp-network`
- `omp-netcode`

Keeping those local makes the fork reproducible and removes the need to build against a full `omp-server` tree.
