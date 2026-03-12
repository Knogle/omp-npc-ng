# omp-npc-ng

`omp-npc-ng` is a standalone fork workspace for the open.mp NPC component.

The goal is to split NPC work out of the `omp-server` monorepo so it can be:

- built independently
- shipped as a drop-in open.mp component
- extended without upstream coupling
- wrapped with a separate Pawn bridge for `NPC_*` and later `FCNPC_*` compatibility

This repository is intended for future NPC work that does not fit cleanly into the upstream server, while still staying on the open.mp component model instead of falling back to the old SA-MP plugin architecture.

## Status

This repository currently contains the initial scaffold.

Included already:

- standalone top-level CMake setup
- separate `core` and `pawn_bridge` component targets
- bootstrap-only configure mode when vendored dependencies are not present
- CI skeleton
- package metadata skeleton
- initial include/layout/docs structure

Not ported yet:

- the real NPC core from `open.mp/Server/Components/NPCs`
- the Pawn-facing NPC native surface from `open.mp/Server/Components/Pawn/Scripting/NPC`
- FCNPC compatibility includes and callbacks

## Structure

| Path | Content |
| ---- | ------- |
| `src/core/` | Standalone NPC core component (`OMPNPCNG`) |
| `src/pawn_bridge/` | External Pawn bridge component (`OMPNPCNGPawn`) |
| `pawno/include/` | Pawn includes for native and compatibility surfaces |
| `docs/` | Porting and architecture notes |
| `libs/` | Vendored open.mp dependencies |

## Dependency model

The standalone build is designed around vendored open.mp pieces:

- `libs/omp-sdk`
- `libs/omp-network`
- `libs/omp-netcode`

Until those directories exist, CMake configures in bootstrap mode and intentionally skips the real component build.

## Sources

Expected bootstrap flow:

```bash
git clone git@github.com:Knogle/omp-npc-ng.git
cd omp-npc-ng
git submodule update --init --recursive
```

The dependency layout is currently left flexible. It can be implemented with submodules or vendored snapshots, as long as the build sees the required `libs/omp-sdk`, `libs/omp-network` and `libs/omp-netcode` directories.

## Build

Bootstrap-only configure:

```bash
cmake -S . -B build -DOMP_NPC_NG_BOOTSTRAP_ONLY=ON
cmake --build build --parallel
```

Once vendored dependencies are present:

```bash
cmake -S . -B build -DOMP_NPC_NG_BOOTSTRAP_ONLY=OFF
cmake --build build --parallel
```

## Porting plan

1. Port `open.mp/Server/Components/NPCs` into `src/core/`.
2. Replace the placeholder `OMPNPCNG` component with the real forked NPC core.
3. Port the Pawn-facing NPC natives into `src/pawn_bridge/`.
4. Register those natives externally through `IPawnComponent` and `PawnEventHandler`.
5. Add FCNPC compatibility includes and callback/native mapping.

See [`docs/bootstrap-plan.md`](docs/bootstrap-plan.md) for the current bootstrap order.

## Why this exists

The old FCNPC codebase is still tightly bound to the legacy SA-MP plugin model, fixed server addresses and hook-based internals. `omp-npc-ng` deliberately starts from the open.mp component architecture instead:

- stable component entry point
- explicit SDK interfaces
- drop-in `components/*.so` / `*.dll` deployment
- cleaner separation between core logic and Pawn integration

## License

This repository uses the same license family as open.mp: Mozilla Public License 2.0. See [`LICENSE`](LICENSE).
