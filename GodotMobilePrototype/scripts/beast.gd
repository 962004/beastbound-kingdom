extends CharacterBody3D

@export var max_health := 30
@export var speed := 2.2
@export var damage := 8
@export var detection_range := 10.0
@export var attack_range := 1.6

var health := 30
var target: Node3D
var attack_timer := 0.0

func _ready():
    add_to_group("beasts")
    health = max_health

func _physics_process(delta):
    attack_timer = maxf(0.0, attack_timer - delta)
    if not is_instance_valid(target):
        target = get_tree().get_first_node_in_group("player")
    if not is_instance_valid(target):
        return
    var distance = global_position.distance_to(target.global_position)
    if distance <= detection_range:
        var direction = (target.global_position - global_position)
        direction.y = 0
        if direction.length() > attack_range:
            direction = direction.normalized()
            velocity.x = direction.x * speed
            velocity.z = direction.z * speed
            look_at(global_position + direction, Vector3.UP)
        else:
            velocity.x = 0
            velocity.z = 0
            if attack_timer <= 0 and target.has_method("take_damage"):
                target.take_damage(damage)
                attack_timer = 1.2
        move_and_slide()

func take_damage(amount: int, attacker = null):
    health -= amount
    if health <= 0:
        if is_instance_valid(attacker) and attacker.has_method("gain_beast_power"):
            attacker.gain_beast_power(1)
        queue_free()
