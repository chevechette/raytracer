#include "logger.h"
#include "managers.h"
#include "rtobject.h"
#include "light.h"

// Exception checked
// TODO: make it threadsafe
ObjectManager::ObjectManager() {}

ObjectManager::~ObjectManager() {
    this->removeNodes();
    this->removeLights();
    this->removeObjects();
}

ObjectManager &ObjectManager::getInstance() {
    static ObjectManager instance = ObjectManager();
    return instance;
}

void ObjectManager::release() {}
// remove(); // pop

// cameras map for edition
void ObjectManager::addObject(std::shared_ptr<Object> obj) {
    this->objs.push_back(obj);
}

void ObjectManager::addLight(std::shared_ptr<Light> light) {
    this->lights.push_back(light);
}

void ObjectManager::addInfinityObject(std::shared_ptr<Object> obj) {
    this->infinityObjs.push_back(obj);
}

void ObjectManager::addBox(std::shared_ptr<Box> box) {
    if (!box) {
        spdlog::error(
            "ObjectManager::addBox was passed a null box. Discarding...");
        return;
    }
    if (!box->isValid()) {
        spdlog::error(
            "ObjectManager::addBox was passed an empty box. Discarding...");
        return;
    }
    this->boxes.push_back(box);
    auto node = std::make_shared<BHV>(box);
    this->nodes.push_back(node);
}

void ObjectManager::removeObjects() {
    spdlog::info("Cleaning up boxes...");
    this->boxes.clear();
    spdlog::info("Cleaning up objects...");
    this->objs.clear();
    spdlog::info("Cleaning up planes and infinitiesoxes...");
    this->infinityObjs.clear();
}

void ObjectManager::removeNodes() {

    spdlog::info("Cleaning up nodes...");
    this->nodes.clear();
}

void ObjectManager::removeLights() {
    spdlog::info("Cleaning up lights...");
    this->lights.clear();
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

    for (i = 0; i + 3 < currentNodesSize; i += 4) {
        auto node =
            std::make_shared<BHV>(currentNodes[i], currentNodes[i + 1],
                                  currentNodes[i + 2], currentNodes[i + 3]);
        savedNodes.push_back(node);
    }
    while (i-- > 0) {
        currentNodes.pop_back();
    }
    currentNodesSize = currentNodes.size();
    spdlog::info("This is the node amount {}.", currentNodesSize);
    if (currentNodesSize > 0 && currentNodesSize <= 4) {
        spdlog::info("This is the node amount {}.", currentNodesSize);
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
    spdlog::info("This is the node amount {}.", currentNodesSize);

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
    auto workingNodes = this->nodes;
    std::vector<std::shared_ptr<BHV>> emptyTree;

    auto mainNode = recursiveTreeBuid(workingNodes, emptyTree);
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

void ObjectManager::createDistantLight(Coordinates dir, Color col) {
    DistantLight *sun = new DistantLight(dir, col);

    std::shared_ptr<Light> ptr = std::shared_ptr<Light>(sun);
    this->addLight(ptr);
}

Intersection ObjectManager::treeWalk(const Ray &ray) {
    auto node = this->tree;

    Intersection closest{};
    if (node != nullptr) {
        closest = node->intersectNodeBox(ray);
    }
    for (auto &objPtr : this->infinityObjs) {
        auto intersect = objPtr->intersect(ray);
        if (intersect && intersect < closest) {
            closest = intersect;
        }
    }
    return closest;
    // TODO: if intesect exist -> should calculate the next ray, to get light
    // refraction or recover this as a color
}

Intersection ObjectManager::intersectAllObjects(const Ray &ray) {
    Intersection closest{};

    // This is the basic logic : loop
    for (auto &objPtr : this->objs) {
        auto intersect = objPtr->intersect(ray);
        if (intersect && intersect < closest) {
            closest = intersect;
        }
    }
    return closest;
    // if intesect exist -> should calculate the next ray or recover this as a
    // color
}
