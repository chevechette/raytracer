#include "forward_declaration.h"
#include "structs.h"
#include "object.h"

// This could have been inheritance but I see no logical connection
// and never want to bother with mixing those two nor bother with casting

class ObjectManager {
    private:
        static  ObjectManager   *instance = nullptr;

        ObjectManager(const ObjectManager&) = delete;
        ObjectManager   &operator=(const ObjectManager&) = delete;
        
        ObjectManager() {
        }

        ~ObjectManager() {

        }

    public:
        static  ObjectManager &getInstance() {
            if (ObjectManager::instance == nullptr) {
                ObjectManager::instance == new ObjectManager();
        }
            return *ObjectManager::instance;
        }
};

class GUIManager {
    private:
        static  GUIManager   *instance = nullptr;

        GUIManager(const ObjectManager&) = delete;
        GUIManager   &operator=(const ObjectManager&) = delete;
        
        GUIManager() {
        }

        ~GUIManager() {

        }

    public:
        static  GUIManager &getInstance() {
            if (GUIManager::instance == nullptr) {
                GUIManager::instance == new ObjectManager();
        }
            return *GUIManager::instance;
        }
};