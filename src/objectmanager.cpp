#include "managers.h"
#include "rtobject.h"
#include <iostream>

// TODO: make it threadsafe
ObjectManager::ObjectManager() {}

ObjectManager::~ObjectManager() {
    this->removeNodes();
    this->removeObjects();
}

ObjectManager &ObjectManager::getInstance() {
    static ObjectManager instance = ObjectManager();
    return instance;
}

void ObjectManager::release() {}
// remove(); // pop
// binary tree structure... later

// cameras map for edition
void ObjectManager::addObject(std::shared_ptr<Object> obj) {
    this->objs.push_back(obj);
}

void ObjectManager::addInfinityObject(std::shared_ptr<Object> obj) {
    this->infinityObjs.push_back(obj);
}

void ObjectManager::addBox(const Box &box) {
    this->boxes.push_back(box);
}

#include <iostream>
void ObjectManager::removeObjects() {

    std::cout << "Cleaning up boxes..." << std::endl;
    this->boxes.clear();
    std::cout << "Cleaning up objects..." << std::endl;
    this->objs.clear();
    std::cout << "Cleaning up planes and infinities..." << std::endl;
    this->infinityObjs.clear();
}

void ObjectManager::removeNodes() {

    std::cout << "Cleaning up nodes..." << std::endl;
    this->nodes.clear();
    std::cout << std::endl;
}

void ObjectManager::buildNodes() {
    this->removeNodes();
    std::cout << "Initialising all nodes" << std::endl;
    for (int i = 0; i < this->boxes.size(); i++) {
        std::cout << "One node" << std::endl; 
        // this->nodes.push_back(std::make_shared<BHV>(this->boxes[i]));
    }
}

std::shared_ptr<BHV> ObjectManager::recursiveTreeBuid(
    std::vector<std::shared_ptr<BHV>> currentNodes) {
    if (currentNodes.size() == 0)
        return nullptr;
    return nullptr;
}

void ObjectManager::buildTree() {
    this->buildNodes();
}

void ObjectManager::createSphere(Coordinates coord, float radius, Color col) {
    auto sphere = std::make_shared<Sphere>(coord, radius, col);
    Box boxedObj = Box(sphere);

    this->addBox(boxedObj);
    this->addObject(sphere);
}

void ObjectManager::createTriangle(Coordinates a, Coordinates b, Coordinates c,
                                   Color col) {
    auto triangle = std::make_shared<Triangle>(a, b, c, col);
    Box boxedObj = Box(triangle);

    this->addBox(boxedObj);
    this->addObject(triangle);
}

void ObjectManager::createPlane(Coordinates o, Coordinates n, Color col) {
    Plane *plane = new Plane(o, n, col);
    std::shared_ptr<Object> ptr = std::shared_ptr<Object>(plane);

    this->addInfinityObject(ptr);
    this->addObject(ptr);
}

Intersection ObjectManager::intersectAllObjects(const Ray &ray) {
    Intersection closest{};

    // This is the basic logic
    // TODO: should be updated with a spatial tree later
    for (auto &objPtr : this->objs) {
        auto intersect = objPtr->intersect(ray);
        if (intersect && intersect < closest) {
            closest = intersect;
        }
    }
    // Throw exception if no match ?
    // TODO: implement intersection with and ifthen logic
    return closest;
    // if intesect exist -> should calculate the next ray or recover this as a
    // color
}
