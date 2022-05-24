//
// Created by Tom on 11/05/2022.
//

#include <wiringPiI2C.h>
#include "KrabbsInitializer.h"
#include "base/ui/UI.h"

Configuration * KrabbsInitializer::start(bool log) {

    Initializer::allowLogging = log;
    Initializer::start(log);

    // Krabbs specific initialization
    initMatchManager();

    UI::logAndRefresh("End of initialization");
    return Initializer::configuration;
}

void KrabbsInitializer::end() {
    Initializer::end();
}

void KrabbsInitializer::initMatchManager() {
    matchManager = new MatchManager();
    UI::logAndRefresh(" -- Match Manager done");
}

