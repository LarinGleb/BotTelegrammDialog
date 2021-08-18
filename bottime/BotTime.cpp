#include <ctime>
#include <stdio.h>
#include "BotTime.h"
#include "tgbot/tgbot.h"


timedifference HandleTime(timedifference timetable)
{
    
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
        struct timedifference diff = {timetable.hoursdiff - ltm->tm_hour,timetable.minutesdiff - ltm->tm_min};


        if (diff.minutesdiff < 0) 
        {
            diff.minutesdiff = diff.minutesdiff + 60;
            diff.hoursdiff = diff.hoursdiff - 1;
        }

        if (diff.hoursdiff < 0)
        {
            diff.hoursdiff = diff.hoursdiff + 24;
        }
        return diff;
        
}