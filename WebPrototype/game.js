import * as THREE from 'https://cdn.jsdelivr.net/npm/three@0.179.1/build/three.module.js';

const scene = new THREE.Scene();
scene.background = new THREE.Color(0x8fc7e8);
scene.fog = new THREE.Fog(0x8fc7e8, 25, 130);
const camera = new THREE.PerspectiveCamera(55, innerWidth / innerHeight, 0.1, 300);
const renderer = new THREE.WebGLRenderer({ antialias: true, powerPreference: 'high-performance' });
renderer.setPixelRatio(Math.min(devicePixelRatio, 1.5));
renderer.setSize(innerWidth, innerHeight);
renderer.shadowMap.enabled = true;
renderer.shadowMap.type = THREE.PCFSoftShadowMap;
document.querySelector('#game').appendChild(renderer.domElement);

scene.add(new THREE.HemisphereLight(0xdff3ff, 0x36552f, 2.1));
const sun = new THREE.DirectionalLight(0xffffff, 2.5);
sun.position.set(20, 35, 10); sun.castShadow = true; sun.shadow.mapSize.set(1024, 1024); scene.add(sun);

const mat = (color, roughness=0.9) => new THREE.MeshStandardMaterial({color, roughness});
const ground = new THREE.Mesh(new THREE.PlaneGeometry(180,180), mat(0x3d6b3c));
ground.rotation.x = -Math.PI/2; ground.receiveShadow = true; scene.add(ground);

function addTree(x,z,s=1){
  const g = new THREE.Group();
  const trunk = new THREE.Mesh(new THREE.CylinderGeometry(.22*s,.35*s,2.5*s,7),mat(0x5a3925));
  trunk.position.y=1.25*s;
  const crown = new THREE.Mesh(new THREE.DodecahedronGeometry(1.25*s,0),mat(0x1e542d));
  crown.position.y=3.0*s;
  g.add(trunk,crown); g.position.set(x,0,z); g.traverse(o=>{o.castShadow=true;o.receiveShadow=true}); scene.add(g);
}
for(let i=0;i<55;i++){const a=Math.random()*Math.PI*2,r=12+Math.random()*65;addTree(Math.cos(a)*r,Math.sin(a)*r,.7+Math.random()*.65)}

function makeShelter(){
  const g=new THREE.Group();
  const wood=mat(0x6b4328), roofMat=mat(0x3b2a20);
  for(const x of [-2.1,2.1]) for(const z of [-1.45,1.45]){const p=new THREE.Mesh(new THREE.BoxGeometry(.35,3,.35),wood);p.position.set(x,1.5,z);g.add(p)}
  const back=new THREE.Mesh(new THREE.BoxGeometry(4.5,2.7,.25),wood);back.position.set(0,1.35,1.45);g.add(back);
  const roof=new THREE.Mesh(new THREE.BoxGeometry(5.1,.35,3.6),roofMat);roof.position.y=3;roof.rotation.z=.02;g.add(roof);
  g.position.set(0,0,-3); g.traverse(o=>{o.castShadow=true;o.receiveShadow=true});scene.add(g);return g;
}
const shelter=makeShelter(); let shelterLevel=1;

function makePlayer(){
  const g=new THREE.Group();
  const skin=mat(0xc88e6a), cloth=mat(0x38495a), wood=mat(0x8a5a2f), blade=mat(0x8d8f8f);
  const torso=new THREE.Mesh(new THREE.CapsuleGeometry(.45,.8,5,8),cloth);torso.position.y=1.35;g.add(torso);
  const head=new THREE.Mesh(new THREE.SphereGeometry(.38,12,8),skin);head.position.y=2.45;g.add(head);
  for(const x of [-.22,.22]){const leg=new THREE.Mesh(new THREE.CylinderGeometry(.13,.16,1,8),cloth);leg.position.set(x,0.55,0);g.add(leg);const arm=new THREE.Mesh(new THREE.CylinderGeometry(.11,.13,1.05,8),skin);arm.position.set(x*2.2,1.45,0);arm.rotation.z=x<0?-.25:.25;g.add(arm)}
  const handle=new THREE.Mesh(new THREE.CylinderGeometry(.055,.055,1.2,8),wood);handle.position.set(.65,1.65,-.1);handle.rotation.z=-.55;g.add(handle);
  const axeHead=new THREE.Mesh(new THREE.BoxGeometry(.45,.12,.55),blade);axeHead.position.set(.92,2.05,-.1);axeHead.rotation.z=-.55;g.add(axeHead);
  g.traverse(o=>{o.castShadow=true;o.receiveShadow=true});scene.add(g);return g;
}
const player=makePlayer(); player.position.set(0,0,3);

function makeBeast(pos){
  const g=new THREE.Group(); const fur=mat(0x34383c), eye=mat(0xf4b33e);
  const body=new THREE.Mesh(new THREE.SphereGeometry(.9,12,8),fur);body.scale.set(1.35,.85,.9);body.position.y=.9;g.add(body);
  const head=new THREE.Mesh(new THREE.SphereGeometry(.6,12,8),fur);head.position.set(0,.95,-.95);g.add(head);
  for(const x of [-.5,.5])for(const z of [-.35,.35]){const leg=new THREE.Mesh(new THREE.CylinderGeometry(.13,.18,.9,7),fur);leg.position.set(x,.45,z);g.add(leg)}
  for(const x of [-.2,.2]){const e=new THREE.Mesh(new THREE.ConeGeometry(.16,.35,5),fur);e.position.set(x,1.65,-.95);g.add(e);const eyeM=new THREE.Mesh(new THREE.SphereGeometry(.07,8,6),eye);eyeM.position.set(x*.55,1.05,-1.48);g.add(eyeM)}
  g.position.copy(pos);g.traverse(o=>{o.castShadow=true;o.receiveShadow=true});scene.add(g);return {mesh:g,health:30,maxHealth:30,cooldown:0};
}
const beasts=[makeBeast(new THREE.Vector3(8,0,1)),makeBeast(new THREE.Vector3(-10,0,-12))];

let power=0, level=1, xp=0, attacking=false, time=0;
const keys={}; addEventListener('keydown',e=>keys[e.key.toLowerCase()]=true);addEventListener('keyup',e=>keys[e.key.toLowerCase()]=false);
const joy=document.querySelector('#joystick'),stick=document.querySelector('#stick'); let joyX=0,joyY=0,joyId=null;
function joyMove(e){const r=joy.getBoundingClientRect(),cx=r.left+r.width/2,cy=r.top+r.height/2;let dx=e.clientX-cx,dy=e.clientY-cy;const max=42,len=Math.hypot(dx,dy);if(len>max){dx=dx/len*max;dy=dy/len*max}joyX=dx/max;joyY=dy/max;stick.style.transform=`translate(${dx}px,${dy}px)`}
joy.addEventListener('pointerdown',e=>{joyId=e.pointerId;joy.setPointerCapture(joyId);joyMove(e)});joy.addEventListener('pointermove',e=>{if(e.pointerId===joyId)joyMove(e)});joy.addEventListener('pointerup',e=>{if(e.pointerId===joyId){joyX=joyY=0;stick.style.transform='translate(0,0)';joyId=null}});
const attackBtn=document.querySelector('#attack');attackBtn.addEventListener('pointerdown',()=>{attacking=true});addEventListener('pointerup',()=>attacking=false);
const upgrade=document.querySelector('#upgrade');upgrade.addEventListener('pointerdown',()=>{if(power>=shelterLevel*2){power-=shelterLevel*2;shelterLevel++;shelter.scale.setScalar(1+.08*shelterLevel);message(`Shelter upgraded to level ${shelterLevel}.`)}else message(`Need ${shelterLevel*2} Beast Power to upgrade.`)});
function message(t){document.querySelector('#message').textContent=t}
function updateHUD(){document.querySelector('#power').textContent=power;document.querySelector('#level').textContent=level;document.querySelector('#xp').textContent=`${xp} / 100`}
function gainXP(n){xp+=n;if(xp>=100){xp-=100;level++;message(`Level ${level}! You feel stronger.`)}updateHUD()}
function killBeast(b){scene.remove(b.mesh);power++;gainXP(25);message(`Beast defeated. Beast Power +1.`);}
function distance(a,b){return a.position.distanceTo(b.position)}

const clock=new THREE.Clock();
function animate(){requestAnimationFrame(animate);const dt=Math.min(clock.getDelta(),.033);time+=dt;
  let mx=joyX+(keys.a?-1:0)+(keys.d?1:0), mz=joyY+(keys.w?-1:0)+(keys.s?1:0);const v=new THREE.Vector3(mx,0,mz);if(v.length()>1)v.normalize();
  player.position.x+=v.x*5*dt;player.position.z+=v.z*5*dt;if(v.lengthSq()>0.01){player.rotation.y=Math.atan2(v.x,v.z);}
  if(attacking){for(const b of beasts){if(!b.mesh.parent)continue;if(distance(player,b.mesh)<2.5){b.health-=45*dt;if(b.health<=0){killBeast(b);}}}}
  for(const b of beasts){if(!b.mesh.parent)continue;b.cooldown-=dt;const d=distance(player,b.mesh);if(d<14){const dir=new THREE.Vector3().subVectors(player.position,b.mesh.position).setY(0);if(dir.length()>2.2){dir.normalize();b.mesh.position.addScaledVector(dir,1.5*dt);b.mesh.lookAt(player.position.x,b.mesh.position.y,player.position.z)}else if(b.cooldown<=0){b.cooldown=1.4;message('The beast attacks! Keep moving.')}}}
  camera.position.lerp(new THREE.Vector3(player.position.x,7.5,player.position.z+11),.08);camera.lookAt(player.position.x,1.2,player.position.z);
  renderer.render(scene,camera);
}
addEventListener('resize',()=>{camera.aspect=innerWidth/innerHeight;camera.updateProjectionMatrix();renderer.setSize(innerWidth,innerHeight)});updateHUD();animate();
