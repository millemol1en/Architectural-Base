#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <iostream>

#include "./SpatialEntities/Particles/Particle.h"
#include "./SpatialEntities/Boids/Boid.h"
#include "../../View/Graphics.h"
#include "../DataStructures/ISpatialDataStructure.h"
#include "../DataStructures/SpatialHashGrid/SpatialHashGrid.h"
#include "../Constants/CONST_SDS_ENTITY_TYPE.h"
#include "../Physics/Forces.h"
#include "../Util/RandGen.h"

// using EntityList = std::vector<ISpatialEntity*>
using ISDS = ISpatialDataStructure;

struct World
{
    // [TODO] :: Needs cleanup and sorting of components:
    int m_itemIDCounter;
	float m_G;

    Vec2f pushForce;

    ISpatialEntity* m_selectedParticle;
    BoundingBox2D m_selectedSDSComponent;

    ISDS* m_SDS;
    ENTITY_TYPE m_entityType;

    BoundingBox2D m_worldBoundingBox;
    Vec2i m_worldSize;
    std::vector<ISpatialEntity*> m_entities;
    std::vector<std::pair<ISpatialEntity*, ISpatialEntity*>> m_collidingParticle;
    std::vector<Vec2f> m_forces;
    std::vector<float> m_torques;


    World(float _gravity = 9.8f, Vec2i _position = { 0, 0 }, Vec2i _size = { Graphics::i_Width(), Graphics::i_Height() });
    ~World();


    // [TODO] :: Clean up is required here! This is a fucking mess
    // Spatial Data Structures:
    SDS_TYPE GetCurrSDSType();
    ISDS* GetCurrSDS();
    ISDS* SetCurrSDS(const SDS_TYPE _sdsType);

    // being tested:
    void SetSDSComponent(const BoundingBox2D _bb);
    BoundingBox2D* GetSDSComponent();

    //////////////////////////
    //   ALL ENTITY TYPES   //
    //////////////////////////
    ENTITY_TYPE GetCurrEntityType();
    int  GetNumParticles();
    Vec2i GetWorldSize();
    std::vector<ISpatialEntity*>& GetEntities();
    ISpatialEntity* GetSelectedEntity();

    void SetSelectedEntity(ISpatialEntity* _particle);

    void AddEntity();
    void Update(float _dt);



    //////////////////
    //   PARTICLE   //
    //////////////////
    // [TODO] Clean this up and divide it into the necessary categories:
    void AddParticle();
    void CheckIfHitBoundary(Particle* _particle);
    void HandleCollision();
    void AddForce(const Vec2f& _force);
    void AddTorque(float _torque);
};

#endif