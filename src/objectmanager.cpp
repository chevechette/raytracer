#include "rtobject.h"
#include <memory>
#include <vector>

// TODO : finish the Object Manager
class ObjectManager {

  public:                                      // TMP PUBLIC VARIABLES
                                               // would be the full libraries
    std::vector<std::shared_ptr<Object>> objs; // shared pointer ? optional ?

  private:
    ObjectManager(const ObjectManager &) = delete;
    ObjectManager &operator=(const ObjectManager &) = delete;

    ObjectManager();

    ~ObjectManager();

  public:
    static ObjectManager &getInstance();

    static void release();
    // remove(); // pop
    // binary tree structure... later

    // cameras map for edition
    void addObject(std::shared_ptr<Object> obj);

    void removeObjects();

    void createSphere(Coordinates coord, float radius, Color col);
    // TODO: add other objs

    Intersection intersectAllObjects(const Ray &ray);

    // TODO: override some fmt for printability
};

ObjectManager::ObjectManager() {
    this->removeObjects();
}

ObjectManager::~ObjectManager() {}

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

void ObjectManager::removeObjects() {
    this->objs.clear();
}

void ObjectManager::createSphere(Coordinates coord, float radius, Color col) {
    this->addObject(std::shared_ptr<Object>(new Sphere(coord, radius, col)));
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
