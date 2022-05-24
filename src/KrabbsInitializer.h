//
// Created by Tom on 11/05/2022.
//

#ifndef KIROULPA_KIROULPA_INITIALIZER_H
#define KIROULPA_KIROULPA_INITIALIZER_H


#include "base/utility/Initializer.h"
#include "ResistanceReader.h"
#include "MatchManager.h"

class KrabbsInitializer : public Initializer {

public:
    static Configuration * start(bool log = true);
    static void end();

    // ---------- Getters ----------
    static MatchManager * getMatchManager() {return matchManager;}
private:

    static void initMatchManager();
    static inline MatchManager * matchManager;
};


#endif //KIROULPA_KIROULPA_INITIALIZER_H
