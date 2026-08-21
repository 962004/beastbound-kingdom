-- Beastbound Kingdom production leaderboard schema.
CREATE TABLE IF NOT EXISTS player_performance (
    player_id UUID PRIMARY KEY,
    display_name VARCHAR(32) NOT NULL,
    level INTEGER NOT NULL DEFAULT 1 CHECK (level > 0),
    experience BIGINT NOT NULL DEFAULT 0 CHECK (experience >= 0),
    beast_power BIGINT NOT NULL DEFAULT 0 CHECK (beast_power >= 0),
    beasts_defeated BIGINT NOT NULL DEFAULT 0 CHECK (beasts_defeated >= 0),
    strongest_beast_tier INTEGER NOT NULL DEFAULT 0 CHECK (strongest_beast_tier >= 0),
    shelter_level INTEGER NOT NULL DEFAULT 1 CHECK (shelter_level > 0),
    kingdom_population INTEGER NOT NULL DEFAULT 1 CHECK (kingdom_population > 0),
    deaths BIGINT NOT NULL DEFAULT 0 CHECK (deaths >= 0),
    best_survival_seconds DOUBLE PRECISION NOT NULL DEFAULT 0 CHECK (best_survival_seconds >= 0),
    performance_score BIGINT NOT NULL DEFAULT 0 CHECK (performance_score >= 0),
    updated_at TIMESTAMPTZ NOT NULL DEFAULT NOW()
);

CREATE INDEX IF NOT EXISTS idx_player_performance_top10
ON player_performance (performance_score DESC, updated_at ASC);

-- Top 10 query used by the game backend. Never trust a client-supplied score;
-- the server should derive score from validated gameplay events.
CREATE OR REPLACE VIEW top_10_survivors AS
SELECT player_id, display_name, level, beast_power, beasts_defeated,
       strongest_beast_tier, shelter_level, kingdom_population,
       performance_score
FROM player_performance
ORDER BY performance_score DESC, updated_at ASC
LIMIT 10;
