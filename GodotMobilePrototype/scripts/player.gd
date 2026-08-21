extends CharacterBody3D

@export var speed := 5.0
@export var acceleration := 18.0
@export var gravity := 18.0
@export var attack_damage := 10

var health := 100
var beast_power := 0
var xp := 0
var level := 1
var attack_cooldown := 0.0

func _physics_process(delta):
    if not is_on_floor():
        velocity.y -= gravity * delta
    var input_vec = Input.get_vector("move_left", "move_right", "move_forward", "move_back")
    var direction = Vector3(input_vec.x, 0.0, input_vec.y)
    if direction.length() > 0.05:
        direction = direction.normalized()
        velocity.x = move_toward(velocity.x, direction.x * speed, acceleration * delta)
        velocity.z = move_toward(velocity.z, direction.z * speed, acceleration * delta)
        look_at(global_position + Vector3(direction.x, 0, direction.z), Vector3.UP)
    else:
        velocity.x = move_toward(velocity.x, 0, acceleration * delta)
        velocity.z = move_toward(velocity.z, 0, acceleration * delta)
    attack_cooldown = maxf(0.0, attack_cooldown - delta)
    if Input.is_action_just_pressed("attack"):
        attack()
    move_and_slide()

func attack():
    if attack_cooldown > 0.0:
        return
    attack_cooldown = 0.65
    var forward = -global_transform.basis.z
    for body in get_tree().get_nodes_in_group("beasts"):
        if body is Node3D and global_position.distance_to(body.global_position) < 2.5:
            var to_target = (body.global_position - global_position).normalized()
            if forward.dot(to_target) > 0.25 and body.has_method("take_damage"):
                body.take_damage(attack_damage, self)

func gain_beast_power(amount := 1):
    beast_power += amount
    xp += amount * 10
    while xp >= level * 100:
        xp -= level * 100
        level += 1

func take_damage(amount: int):
    health = max(0, health - amount)
    if health == 0:
        health = 100
        global_position = Vector3(0, 1, 0)
