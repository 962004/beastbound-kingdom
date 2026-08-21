# Beastbound Kingdom — Runtime Architecture

## Performance-aware player profile

Each player session records gameplay telemetry needed for progression and personalization:
- player level
- beasts defeated by tier
- damage dealt / received
- survival time
- shelter level
- resources gathered
- deaths
- completed events
- performance score
- last played timestamp

Only gameplay metrics needed by the game are stored. Avoid storing sensitive personal information.

## Player profile schema

```text
PlayerProfile
- PlayerId (opaque generated identifier)
- Level
- BeastPower
- XP
- PerformanceScore
- BestSurvivalTime
- BestBeastTier
- ShelterLevel
- TotalBeastsDefeated
- TotalDeaths
- LastPlayedUtc
```

## Leaderboard / Top 10

On a new game/session, the game can show the player's local/server leaderboard with the top 10 performance scores. Ranking should be server-authoritative for an online leaderboard so clients cannot simply edit their own score.

For an offline-first prototype, store a local Top 10 cache and later synchronize it to the backend.

## Coach / chatbot

The game will include a **Beastbound Coach** system. It should provide short contextual instructions such as:
- "Your shelter is damaged. Return and repair it."
- "This beast is much stronger than you. Consider retreating."
- "You gained +1 Beast Power."
- "A storm is approaching. Upgrade your shelter."

The coach is guidance, not a text-based replacement for gameplay. Actions remain player-controlled.

## Machine language / native code

"Machine language" is not a practical development language for this game. The native low-level layer will be C++ compiled to machine code by the Unreal/Android toolchain. Android's NDK supports native C/C++ and compiles it into native libraries. Unreal's Android workflow handles the SDK/NDK/JDK toolchain and packaging.

Python remains useful for development tools, telemetry analysis, procedural content and offline ML/data pipelines. C++ remains the core runtime language for performance-sensitive gameplay and security-sensitive validation.

## Suggested backend

For an online account/leaderboard later:

```text
Mobile Game
   |
   | HTTPS
   v
Game API (Python)
   |
   +---- PostgreSQL player database
   |
   +---- Leaderboard service
```

Never trust client-submitted scores. The server should validate progression events and calculate authoritative leaderboard values where online competition matters.
