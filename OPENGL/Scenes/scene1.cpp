//
//  scene1.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "scene1.hpp"

scene1::scene1(){
    // Initialise Objects
    // Instantiate Object
    // initModel
    // initTexture
    // loadMat
    // sort any other variables that need set
    double startTime = glfwGetTime(); // So we can see how long it takes for all models to load
    
    
    
    // So for a single object that is not to be instanced, we call its constructor, we initialise its model, texture and load its material.
    // we can also provide a position if we so wish
    
    // Torch
    torchObj = new modelObjectSingle();
    torchObj->initModel("Resources/newTorch.obj","Shaders/vs.glsl","Shaders/fs.glsl");
    torchObj->initTexture("Resources/newTorchCol.ktx");
    torchObj->loadMat("Resources/newTorch.mtl");
//    Objs.push_back(torchObj); //Add objects to vector Objs to be rendered!
                              // This is the most important part, this allows us to just loop through that vector and render each one.
    torchObj->position = playerPosition + posOnSphere(sphereRadius,yawOffset,-pitchOffset);
    
    // Room
    
    // Front of room
    front = new modelObjectSingle();
    front->initModel("Resources/front.obj","Shaders/vs.glsl","Shaders/fs.glsl");
    front->initTexture("Resources/front.ktx");
    front->loadMat("Resources/front.mtl");
    Objs.push_back(front); //Add objects to vector Objs to be rendered!
    
    // Back wall
    back = new modelObjectSingle();
    back->initModel("Resources/back.obj", "Shaders/vs.glsl", "Shaders/fs.glsl");
    back->initTexture("Resources/back.ktx");
    back->loadMat("Resources/back.mtl");
    back->rotation.y = 180.0f;
    back->position = glm::vec3(0.0f,2.0f,3.0f);
    Objs.push_back(back); //Add objects to vector Objs to be rendered!
    
    // Roof
    roof = new modelObjectSingle();
    roof->initModel("Resources/roof.obj", "Shaders/vs.glsl", "Shaders/fs.glsl");
    roof->initTexture("Resources/roof.ktx");
    roof->loadMat("Resources/roof.mtl");
    roof->position.y = 2.5f;
    Objs.push_back(roof); //Add objects to vector Objs to be rendered!
    
    
    // For models to be instanced its a little different, we still use its constructor, init model, texture and load the material
    // but for the position, rotations and scale we need to push back each to create a new instance of the item
    beam = new modelObjectInst();
    beam->initModel("Resources/beam.obj", "Shaders/vs.glsl", "Shaders/fs.glsl");
    beam->initTexture("Resources/beam.ktx");
    beam->loadMat("Resources/beam.mtl");
    
    beam->position.push_back(glm::vec3(0.0f,2.61f,0.0f));
    beam->rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
    beam->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    beam->position.push_back(glm::vec3(0.0f,2.61f,-1.5f));
    beam->rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
    beam->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    beam->position.push_back(glm::vec3(0.0f,2.61f,1.5f));
    beam->rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
    beam->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    Objs.push_back(beam); //Add objects to vector Objs to be rendered!
    
    
    // Plank
    planks = new modelObjectInst();
    planks->initModel("Resources/plank.obj", "Shaders/vs.glsl", "Shaders/fs.glsl");
    planks->initTexture("Resources/plank.ktx");
    planks->loadMat("Resources/plank.mtl");
    
    // Plank 1
    planks->position.push_back(glm::vec3(2.2f,1.5f,-3.0f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,5.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 2
    planks->position.push_back(glm::vec3(2.0f,1.3f,-3.0f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,10.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 3
    planks->position.push_back(glm::vec3(1.65f,1.6f,-3.0f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,2.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 4
    planks->position.push_back(glm::vec3(1.4f,1.5f,-3.0f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,-5.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 5
    planks->position.push_back(glm::vec3(1.1f,1.3f,-3.0f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,1.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 6
    planks->position.push_back(glm::vec3(0.8f,1.55f,-3.0f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,-12.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 7
    planks->position.push_back(glm::vec3(0.5f,1.55f,-3.0f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,-1.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 8
    planks->position.push_back(glm::vec3(0.1f,1.55f,-3.0f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,6.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 9
    planks->position.push_back(glm::vec3(0.6f,1.7f,-2.85f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,80.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 10
    planks->position.push_back(glm::vec3(1.0f,1.15f,-2.85f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,110.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 11
    planks->position.push_back(glm::vec3(1.8f,1.65f,-2.85f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,60.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 12
    planks->position.push_back(glm::vec3(-1.4f,1.85f,-3.2f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,85.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 13
    planks->position.push_back(glm::vec3(-1.4f,1.55f,-3.2f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,95.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 14
    planks->position.push_back(glm::vec3(-1.4f,1.2f,-3.2f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,90.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 15
    planks->position.push_back(glm::vec3(-1.4f,0.85f,-3.2f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,80.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 16
    planks->position.push_back(glm::vec3(-1.4f,0.5f,-3.2f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,100.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Plank 17
    planks->position.push_back(glm::vec3(-1.4f,0.2f,-3.2f));
    planks->rotation.push_back(glm::vec3(90.0f,0.0f,95.0f));
    planks->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    Objs.push_back(planks); //Add objects to vector Objs to be rendered!
    
    
    // Floor
    floor = new modelObjectSingle();
    floor->initModel("Resources/floor.obj", "Shaders/vs.glsl", "Shaders/fs.glsl");
    floor->initTexture("Resources/floor.ktx");
    floor->loadMat("Resources/floor.mtl");
    Objs.push_back(floor); //Add objects to vector Objs to be rendered!
    
    // Wall
    wall = new modelObjectInst();
    wall->initModel("Resources/wall.obj", "Shaders/vs.glsl", "Shaders/fs.glsl");
    wall->initTexture("Resources/wall.ktx");
    wall->loadMat("Resources/wall.mtl");
    
    // Wall 1
    wall->position.push_back(glm::vec3(3.0f,1.25f,0.0f));
    wall->rotation.push_back(glm::vec3(0.0f,180.0f,0.0f));
    wall->scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
    
    // Wall 2
    wall->add(glm::vec3(-3.0f,1.25f,0.0f));              // add is a method for the inst model object, that takes the position, but sets rotation and scale to 0 to speed up the pushing of new objects in vector
    
    Objs.push_back(wall); //Add objects to vector Objs to be rendered!
    
    //Lightbulb
    bulb = new modelObjectSingle();
    bulb->initModel("Resources/bulb.obj", "Shaders/vs_light.glsl", "Shaders/fs_light.glsl");
    bulb->initTexture("Resources/bulb.ktx");
    bulb->loadMat("Resources/bulb.mtl");
    Objs.push_back(bulb); //Add objects to vector Objs to be rendered!
    
    wire = new  modelObjectSingle();
    wire->initModel("Resources/wire.obj", "Shaders/vs.glsl", "Shaders/fs.glsl");
    wire->initTexture("Resources/wire.ktx");
    wire->loadMat("Resources/wire.mtl");
    Objs.push_back(wire); //Add objects to vector Objs to be rendered!
    
    table = new modelObjectSingle();
    table->initModel("Resources/table.obj", "Shaders/vs.glsl", "Shaders/fs.glsl");
    table->initTexture("Resources/table.ktx");
    table->loadMat("Resources/table.mtl");
    table->position = glm::vec3(1.8f,1.0f,1.8f);
    table->rotation.y = 45;
    Objs.push_back(table); //Add objects to vector Objs to be rendered!
    
    lamp = new modelObjectSingle();
    lamp->initModel("Resources/lamp.obj", "Shaders/vs.glsl", "Shaders/fs.glsl");
    lamp->initTexture("Resources/lamp.ktx");
    lamp->loadMat("Resources/lamp.mtl");
    lamp->position = glm::vec3(2.4f,1.025f,1.6f);
    lamp->rotation.y = 120;
    Objs.push_back(lamp); //Add objects to vector Objs to be rendered!
    
    // Add lights to scene, number of lights determined by const int LIGHTSN
    // The ceiling light
    lights[0].type = lightType::point; // So we have an enum for point and spot lights that lets us know which light we are dealing with
    lights[0].position = glm::vec3(0.0f,2.0f,0.0f);
    lights[0].id = glm::vec3(5.0f,5.0f,5.0f);
    lights[0].is = glm::vec3(5.0f,5.0f,5.0f);
    
    // red light by the door
    lights[1].type = lightType::point;
    lights[1].position = glm::vec3(-1.7f,1.5f,-2.8f);
    lights[1].id = glm::vec3(1.5f,0.0f,0.0f);
    lights[1].is = glm::vec3(0.5f,0.0f,0.0f);
    
    // torch light
    lights[2].type = lightType::spot;
    lights[2].position = glm::vec3(0.0f,1.0f,0.0f);
    lights[2].direction = glm::vec3(0.0f,0.0f,1.0f); // its facing the same direction of the player
    lights[2].id = glm::vec3(7.0f,7.0f,7.0f);
    lights[2].is = glm::vec3(5.0f,5.0f,5.0f);
    
    // the lamp light
    lights[3].type = lightType::spot;
    lights[3].position = lamp->position +glm::vec3(0.0f,0.5f,0.0f);
    lights[3].direction = glm::vec3(-0.5f,-0.3f,0.3f);
    lights[3].id = glm::vec3(5.0f,5.0f,5.0f);
    lights[3].is = glm::vec3(1.0f,1.0f,1.0f);
    
    
    cout<<"Time to load "<<glfwGetTime()-startTime<<endl;   // Just a nice thing to know
}




void scene1::update(double currentTime){
    double dt = currentTime - prevTime; // get the change in time between the last frame and the current frame so to accurately calculate any movement
    prevTime = currentTime;
    
    // Swinging light
    double ay = (-9.81/lightRadius)*cos(glm::radians(lightPitch)); // this is the equation for the acceleration acting upon the light
    lightPitch += v*dt + 0.5 * ay * pow(dt,2); // this is the equation for angular motion
    v += ay*dt; // and the new velocity on the pendulum
    
    if(lightPitch>-20){ // we need to cap the height the pendulum reaches, otherwise inaccuracies will cause the pendulum to keep swinging higher and higher
        lightPitch = -20; // by capping the swing between -20 and -160 so that the swing is more natural, could do 0 and -180 but prefer the cone look
                          //        v = 0; // at the peak of its swing the pendulum has zero velocity and max acceleration. whereas at the bottom of its swing it has zero acceleration and a max velocity
    }else if(lightPitch<-160){
        lightPitch = -160;
        //        v = 0;
    }
    lights[0].position = glm::vec3(0.0f,2.49f,0.0f) + posOnSphere(lightRadius, lightYaw, lightPitch); // here we set the position of light source
    bulb->position = lights[0].position; // set the position of the bulb to match
    bulb->rotation.x = -lightPitch-90;   // set the rotation of the bulb to match the angles for the model are weird, so dont ask why its so messed up
                                         // trial and error was used to find the right combination
    
    wire->position = glm::vec3(0.0f,2.49f,0.0f) + posOnSphere(0.125, lightYaw, lightPitch); // need to set the wires position and rotation to match the bulb
    wire->rotation.x = -lightPitch-90;
    
    
    lights[2].position = playerPosition+glm::vec3(0.0f,0.0f,1.0f)/3.0f; // we can update the position of the torch light based on the direction of the camera
}

// Activates the primary action, this case turning the torch on or off
void scene1::usePrimary(){
    if(lights[2].lightOn){ // we need to check if the light is on or off first, if its on we need to switch it off and vice versa
        lights[2].lightOn = false;
    }
    else{
        lights[2].lightOn = true;
    }
}

// Activates the secondary action, this case turning the ceiling light on or off
void scene1::useSecondary(){
    if(lights[0].lightOn){
        lights[0].lightOn = false;
    }
    else{
        lights[0].lightOn = true;
    }
}


// Turns the player to face the direction specified by the spherical coordinates
void scene1::turn(GLfloat yaw, GLfloat pitch){

    torchObj->position = playerPosition + posOnSphere(1, yaw+yawOffset, pitch-pitchOffset) * sphereRadius; // our torchs position is based off the camera position
    // try adding vectors instead of adding yaw and pitch

    torchObj->rotation.x = -pitch;       // Torch seems to be backwards in its model so has to have its pitch rotated the other way
    torchObj->rotation.y = yaw;
    lights[2].direction = posOnSphere(1, yaw, pitch); // the light from the torch just goes where we are looking
}

