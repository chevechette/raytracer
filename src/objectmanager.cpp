#include "fmt/core.h"
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
    std::vector<std::shared_ptr<BHV>> &currentNodes,
    std::vector<std::shared_ptr<BHV>> &savedNodes) {
    size_t i = 0;
    size_t currentNodesSize = currentNodes.size();

    fmt::print(stdout, "Amount of nodes in main list {} secondary {}\n",
               currentNodes.size(), savedNodes.size());

    for (i = 0; i + 3 < currentNodesSize; i += 4) {
        fmt::print(
            stdout,
            "I COUNTER {} Amount of nodes in main list {} secondary {}\n", i,
            currentNodes.size(), savedNodes.size());
        auto node =
            std::make_shared<BHV>(currentNodes[i], currentNodes[i + 1],
                                  currentNodes[i + 2], currentNodes[i + 3]);
        savedNodes.push_back(node);
        fmt::print(
            stdout,
            "I COUNTER {} Amount of nodes in main list {} secondary {}\n", i,
            currentNodes.size(), savedNodes.size());
    }
    while (i-- > 0) {
        currentNodes.pop_back();

        fmt::print(stdout, "Pop pop\n");
    }
    currentNodesSize = currentNodes.size();
    std::cout << "This is the node amount " << currentNodesSize << std::endl;
    if (currentNodesSize > 0 && currentNodesSize <= 4) {
        std::cout << "Getting scraps This is the node amount "
                  << currentNodesSize << std::endl;
        auto node = std::make_shared<BHV>(
            currentNodes[currentNodesSize],
            (currentNodes.size() > 1) ? currentNodes[currentNodesSize - 1]
                                      : nullptr,
            (currentNodes.size() > 2) ? currentNodes[currentNodesSize - 2]
                                      : nullptr,
            (currentNodes.size() > 3) ? currentNodes[currentNodesSize - 3]
                                      : nullptr);
        savedNodes.push_back(node);
        for (int i = 0; i < currentNodesSize; i++) {
            currentNodes.pop_back();
        }
    }
    currentNodesSize = currentNodes.size();
    std::cout << "This is the node amount " << currentNodesSize << std::endl;

    if (currentNodesSize <= 0) { // should always be true
        if (savedNodes.size() <= 0)
            return nullptr;
        if (savedNodes.size() == 1)
            return savedNodes[0];
        return recursiveTreeBuid(savedNodes, currentNodes);
    }

    return recursiveTreeBuid(currentNodes,
                             savedNodes); // should never get there
}

void ObjectManager::buildTree() {
    // this->buildNodes();
    auto workingNodes = this->nodes;
    std::vector<std::shared_ptr<BHV>> emptyTree;

    fmt::print(stdout,
               "Amount of nodes in main list {} secondary {} and empty {}\n",
               this->nodes.size(), workingNodes.size(), emptyTree.size());
    auto mainNode = recursiveTreeBuid(workingNodes, emptyTree);
    fmt::print(stdout,
               "Amount of nodes in main list {} secondary {} and empty {}\n",
               this->nodes.size(), workingNodes.size(), emptyTree.size());
    this->tree = mainNode;
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

Intersection ObjectManager::treeWalk(const Ray &ray) {
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
