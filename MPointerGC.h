#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <vector>
#include <mutex>

class MPointerGC {
private:
    static MPointerGC* instance;
    std::vector<void*> pointers;
    std::mutex mtx;

    MPointerGC() {}

public:
    static MPointerGC* getInstance() {
        if (!instance) {
            instance = new MPointerGC();
        }
        return instance;
    }

    void registerPointer(void* ptr) {
        std::lock_guard<std::mutex> lock(mtx);
        pointers.push_back(ptr);
    }

    void unregisterPointer(void* ptr) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = std::remove(pointers.begin(), pointers.end(), ptr);
        if (it != pointers.end()) {
            pointers.erase(it);
        }
    }

    ~MPointerGC() {
        // for (auto ptr : pointers) {
        //     delete static_cast<int*>(ptr); // Needs to be adapted or removed
        // }
    }
};

MPointerGC* MPointerGC::instance = nullptr;

#endif // MPOINTERGC_H
