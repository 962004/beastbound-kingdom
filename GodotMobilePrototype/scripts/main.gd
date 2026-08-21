extends Node3D

@onready var player = $Player
@onready var power_label = $HUD/Power
@onready var level_label = $HUD/Level

func _process(_delta):
    if is_instance_valid(player):
        power_label.text = "BEAST POWER  %d" % player.beast_power
        level_label.text = "LEVEL  %d   XP %d" % [player.level, player.xp]

func _on_attack_pressed():
    if is_instance_valid(player):
        player.attack()

func _on_upgrade_pressed():
    var shelter = get_node_or_null("Shelter")
    if shelter and shelter.has_method("upgrade"):
        shelter.upgrade()
