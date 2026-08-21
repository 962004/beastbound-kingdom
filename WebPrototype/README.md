# Beastbound Kingdom — 3D Mobile Prototype

This folder contains a playable, browser-based 3D vertical slice used to validate the game's first gameplay loop before the Unreal mobile build.

## Included
- Landscape-first mobile layout
- Third-person 3D camera
- Procedural 3D player, axe, shelter, trees and beasts
- Touch virtual joystick
- Touch axe button
- Beast chase behavior
- Real-time attack and beast defeat
- Beast Power +1 on kill
- XP and level progression
- Shelter upgrade interaction
- Desktop WASD fallback for development

## Run
Serve this folder from a local web server (ES modules are required). Example:

`python -m http.server 8080`

Then open `http://localhost:8080/WebPrototype/` in a browser. On a phone, open the same page from a device reachable server and use landscape orientation.

## Relationship to Unreal
This prototype is intentionally dependency-light and proves the gameplay loop in 3D. The Unreal project remains the production target for Android/iOS packaging, native C++ systems, full animation, authored maps, Blueprints, device optimization, and final assets.
