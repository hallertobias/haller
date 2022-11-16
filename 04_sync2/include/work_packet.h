#pragma once

class WorkPacket {
    private: 
        int id = 0;
    public:
        WorkPacket(int id) {
            this->id = id;
        }
        int getID() const {
            return this->id;
        }
};