#include <vector>
#include <memory>
#include "rtobject.h"

// TODO : finish the Object Manager
class ObjectManager {

  public: // TMP PUBLIC VARIABLES
    std::vector<std::shared_ptr<Object>>   objs; // shared pointer ? optional ?
  private:
    ObjectManager(const ObjectManager &) = delete;
    ObjectManager &operator=(const ObjectManager &) = delete;

    ObjectManager() {}

    ~ObjectManager() {}

  public:
    static ObjectManager &getInstance() {
        static ObjectManager instance = ObjectManager();
        return instance;
    }

    static void release() {}

    // add(); // push
    // remove(); // pop
    // binary tree structure... later

    // cameras map for edition

    //
};