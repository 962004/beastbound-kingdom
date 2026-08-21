# Beastbound Backend

Planned Python service for player profiles, progression and Top 10 leaderboard synchronization.

## API shape

`POST /v1/profile/session` — submit validated session summary

`GET /v1/leaderboard/top10` — return top ten performance scores

`GET /v1/profile/{player_id}` — retrieve a player's non-sensitive game profile

## Database

PostgreSQL is the planned production database. A local/offline prototype can use Unreal SaveGame first and synchronize when the backend is introduced.

### Player table

```sql
CREATE TABLE player_profiles (
    player_id UUID PRIMARY KEY,
    level INTEGER NOT NULL DEFAULT 1,
    beast_power INTEGER NOT NULL DEFAULT 0,
    xp INTEGER NOT NULL DEFAULT 0,
    performance_score INTEGER NOT NULL DEFAULT 0,
    best_survival_seconds REAL NOT NULL DEFAULT 0,
    best_beast_tier INTEGER NOT NULL DEFAULT 0,
    shelter_level INTEGER NOT NULL DEFAULT 1,
    total_beasts_defeated INTEGER NOT NULL DEFAULT 0,
    total_deaths INTEGER NOT NULL DEFAULT 0,
    last_played_utc TIMESTAMPTZ NOT NULL DEFAULT NOW()
);

CREATE INDEX leaderboard_performance_idx
ON player_profiles (performance_score DESC, last_played_utc ASC);
```

The Top 10 query is simply ordered by `performance_score DESC` with `LIMIT 10`. Server-side validation is required before accepting competitive scores.
