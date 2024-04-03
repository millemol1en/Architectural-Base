#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <iostream>
#include "./Particle.h"
#include "../../View/Graphics.h"
#include "../DataStructures/ISpatialDataStructure.h"
#include "../DataStructures/SpatialHashGrid/SpatialHashGrid.h"
#include "../Constants/CONST_SDS_ENTITY_TYPE.h"
#include "../Physics/Forces.h"

// using EntityList = std::vector<ISpatialEntity*>
using ISDS = ISpatialDataStructure;

struct World
{
    int m_itemIDCounter;
	float m_G;

    Vec2f pushForce;


    Particle* m_selectedParticle;
    BoundingBox2D m_selectedSDSComponent;

    ISDS* m_SDS;
    ENTITY_TYPE m_entityType;


    BoundingBox2D m_worldBoundingBox;
    Vec2i m_worldSize;
    std::vector<Particle*> m_particles;
    std::vector<std::pair<Particle*, Particle*>> m_collidingParticle;
    std::vector<Vec2f> m_forces;
    std::vector<float> m_torques;


    World(float _gravity = 9.8f, Vec2i _position = { 0, 0 }, Vec2i _size = { Graphics::i_Width(), Graphics::i_Height() });
    ~World();


    // [TODO] :: Clean up is required here! This is a fucking mess
    // Spatial Data Structures:
    void SetCurrEntityType();
    ENTITY_TYPE GetCurrEntityType();
    SDS_TYPE GetCurrSDSType();
    ISDS* GetCurrSDS();
    ISDS* SetCurrSDS(const SDS_TYPE _sdsType);

    // being tested:
    void SetSDSComponent(const BoundingBox2D _bb);
    BoundingBox2D* GetSDSComponent();

    // Particles / Entities:
    int  GetNumParticles();
    Vec2i GetWorldSize();
    std::vector<Particle*>& GetParticles();

    // being tested:
    void SetSelectedEntity(Particle* _particle);
    Particle* GetSelectedEntity();

    void AddEntity();
    void AddParticles();
    void HandleCollision();
    void CheckIfHitBoundary(Particle* _particle);
    void AddForce(const Vec2f& _force);
    void AddTorque(float _torque);
    void Update(float _dt);


};

#endif