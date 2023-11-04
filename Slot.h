#ifndef PROJETO_AED_SLOT_H
#define PROJETO_AED_SLOT_H
#include <string>


class Slot {
public:
    Slot();
    Slot(std::string weekDay, double beginTime, double duration, std::string type);


    std::string getWeekDay();
    std::string getType();
    double getStartTime();
    double getEndTime();
    bool overlaps(Slot &other);
    bool operator==(Slot &other);
    bool operator<(Slot &other);

private:
    std::string weekDay;
    double startTime;
    double endTime;
    std::string type;
};


#endif //PROJETO_AED_SLOT_H
