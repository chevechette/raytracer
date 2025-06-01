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

void ObjectManager::addBox(std::shared_ptr<Box> box) {
    if (!box) {
        std::cerr << "addBox was passed a null box!" << std::endl;
        return;
    }
    this->boxes.push_back(box);
    auto node = std::make_shared<BHV>(box);
    this->nodes.push_back(node);
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
    for (int i = 0; i < this->boxes.size(); i++) {
        this->nodes.push_back(std::make_shared<BHV>(this->boxes[i]));
    }
}

std::shared_ptr<BHV> ObjectManager::recursiveTreeBuid(
    std::vector<std::shared_ptr<BHV>> &currentNodes) {
    if (currentNodes.size() == 0)
        return nullptr;
    if (currentNodes.size() <= 4) {
        return std::make_shared<BHV>(
            currentNodes[0],
            (currentNodes.size() > 1) ? currentNodes[1] : nullptr,
            (currentNodes.size() > 2) ? currentNodes[2] : nullptr,
            (currentNodes.size() > 3) ? currentNodes[3] : nullptr);
    }
    return nullptr;
    // auto node1 =
    //     std::make_shared<BHV>(currentNodes.pop_back(), currentNodes.pop_back(),
    //                           currentNodes.pop_back(), currentNodes.pop_back());
    // auto node2 = recursiveTreeBuid(currentNodes);
    // auto node3 = recursiveTreeBuid(currentNodes);
    // auto node4 = recursiveTreeBuid(currentNodes);
    // if (node2 == nullptr)
    //     return node1;
    // auto bigNode = std::make_shared<BHV>(node1, node2, node3, node4);
    // return bigNode;
}

void ObjectManager::buildTree() {
    this->buildNodes();
}

void ObjectManager::createSphere(Coordinates coord, float radius, Color col) {
    auto sphere = std::make_shared<Sphere>(coord, radius, col);
    auto box = std::make_shared<Box>(sphere);

    this->addBox(box);
    this->addObject(sphere);
}

void ObjectManager::createTriangle(Coordinates a, Coordinates b, Coordinates c,
                                   Color col) {
    auto triangle = std::make_shared<Triangle>(a, b, c, col);
    auto box = std::make_shared<Box>(triangle);

    this->addBox(box);
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
