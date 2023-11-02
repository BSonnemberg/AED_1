#ifndef PROJETO_AED_SLOT_H
#define PROJETO_AED_SLOT_H
#include <string>


class Slot {
public:
    Slot();
    Slot(std::string &weekDay, float &beginTime, float &duration, std::string &type);
    std::string getWeekDay();
    std::string getType();
    float getStartTime();
    float getEndTime();
    bool overlaps(Slot &other);
    bool operator==(Slot &other);
    bool operator<(Slot &other);

private:
    std::string weekDay;
    float startTime;
    float endTime;
    std::string type;
};


#endif //PROJETO_AED_SLOT_H
