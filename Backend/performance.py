from dataclasses import dataclass

@dataclass(frozen=True)
class PerformanceInput:
    level: int
    beast_power: int
    beasts_defeated: int
    strongest_beast_tier: int
    shelter_level: int
    kingdom_population: int
    deaths: int
    best_survival_seconds: float


def calculate_performance(s: PerformanceInput) -> int:
    """Deterministic server-side score calculation.

    Clients should send validated gameplay events, not a claimed final score.
    """
    score = (
        max(s.level, 1) * 100
        + max(s.beast_power, 0) * 20
        + max(s.beasts_defeated, 0) * 50
        + max(s.strongest_beast_tier, 0) ** 2 * 100
        + max(s.shelter_level, 1) * 75
        + max(s.kingdom_population, 1) * 10
        + int(max(s.best_survival_seconds, 0) // 60) * 5
        - max(s.deaths, 0) * 100
    )
    return max(0, score)
