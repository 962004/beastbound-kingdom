# Beastbound Kingdom

A mobile landscape 3D survival-action and kingdom-building game.

## Prototype 0.1

The first vertical slice targets Unreal Engine 5 and mobile landscape play.

### Current prototype goals
- Third-person player foundation
- Axe combat
- Beast enemy with simple AI
- Health and damage
- Beast Power (+1 on beast kill)
- Resource pickup foundation
- Wooden shelter foundation
- Mobile landscape configuration

## Technology
- Unreal Engine 5
- C++ for core gameplay
- Blueprints for content and presentation
- Python for development/procedural tooling
- GitHub for version control

## Folder structure

```text
BeastboundKingdom/
├── Config/
├── Content/
├── Source/
│   └── BeastboundKingdom/
│       ├── BeastboundKingdom.Build.cs
│       ├── BeastboundKingdom.cpp
│       ├── BeastboundGameMode.h/.cpp
│       ├── BeastPlayerCharacter.h/.cpp
│       ├── BeastEnemy.h/.cpp
│       └── BeastShelter.h/.cpp
├── Scripts/
├── Docs/
└── BeastboundKingdom.uproject
```

## Prototype gameplay

Spawn near a small wooden shelter, explore the wilderness, attack a beast with the axe, defeat it, and gain Beast Power. The code is deliberately modular so later systems can add stronger beasts, disasters, followers, construction, events, and kingdom progression.

## Development status

**Prototype 0.1 — foundation created.**

Art, animations, production assets, and device-specific optimization will be added during later milestones.
