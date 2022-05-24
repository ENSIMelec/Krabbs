//
// Created by Tom on 20/05/2022.
//

#include "MatchManager.h"
#include "base/utility/Initializer.h"
#include "base/ui/UI.h"
#include "KrabbsInitializer.h"

MatchManager::MatchManager() {
    strategyIndex = 0;
    strategy_0 = new Strategy("../res/strategies/Purple/Resistances/", "strategy0");
    strategy_1 = new Strategy("../res/strategies/Purple/Resistances/", "strategy1");
    strategy_2 = new Strategy("../res/strategies/Purple/Resistances/", "strategy2");
    strategy_3 = new Strategy("../res/strategies/Purple/Resistances/", "strategy3");
    undefined = new Strategy("../res/strategies/Purple/Resistances/", "undefined");
//    undefined = new Strategy("../res/strategies/", "None");

    startingStrategy = new Strategy("../res/strategies/", "Purple");
    Initializer::setStrategy(startingStrategy);

    // Setting the first point
    controller = Initializer::getController();
    currentPoint = startingStrategy->getNextPoint();
    controller->setNextPoint(currentPoint);

    actionManager = Initializer::getActionManager();

    Configuration * configuration = Initializer::getConfiguration();
    matchTime = configuration->getInt("global.match_time");

    timer.restart();
}

bool MatchManager::isMatchDone() {
    return matchIsDone;

//    int totalTime = (int) timer.elapsed_s();
//    if(totalTime >= matchTime) {
//        return true;
//    }

    return false;
}

void MatchManager::next() {
    UI::logAndRefresh("Point reached !");

    // Stop the motors
    controller->stopMotors();

    // Execute the action (if there is one)
    if(currentPoint->isActionAfterMovement()) {
        string actionFile = currentPoint->getAction();
        UI::logAndRefresh(actionFile.c_str());
        if(actionFile != "null") actionManager->action(actionFile + ".as");
    }

    // Strategy is done is updated when asking for next point
    gettingCurrentPoint();

    // Check if all strategies are done
    if(currentPoint != nullptr) {
        UI::log("Going to next point");
        controller->setNextPoint(currentPoint);
    } else {
        UI::log("End of the match (maybe?)");
        matchIsDone = true;
    }
}

void MatchManager::gettingCurrentPoint() {
    if(!firstPartIsDone) {
        currentPoint = startingStrategy->getNextPoint();
        if(currentPoint == nullptr) {
            UI::log("Going to part 2 of the match :)");
            firstPartIsDone = true;

            // Reading the resistance value
            resistanceReader->getValues();
            strategyIndex = resistanceReader->getStrategyIndexFromValues();

            UI::log("Strategy Index :");
            UI::log(to_string(strategyIndex).c_str());

            // Getting the first point of the next strategy
            switch (strategyIndex) {
                case 0:
                    currentPoint = strategy_0->getNextPoint();
                    break;
                case 1:
                    currentPoint = strategy_1->getNextPoint();
                    break;
                case 2:
                    currentPoint = strategy_2->getNextPoint();
                    break;
                case 3:
                    currentPoint = strategy_3->getNextPoint();
                    break;
                default:
                    currentPoint =  undefined->getNextPoint();
            }

            if(currentPoint == nullptr) {
                UI::logAndRefresh("Point is null :(");
            }
        }
    } else {
        switch (strategyIndex) {
            case 0:
                currentPoint = strategy_0->getNextPoint();
                break;
            case 1:
                currentPoint = strategy_1->getNextPoint();
                break;
            case 2:
                currentPoint = strategy_2->getNextPoint();
                break;
            case 3:
                currentPoint = strategy_3->getNextPoint();
                break;
            default:
                currentPoint = undefined->getNextPoint();
        }
    }
}

Point *MatchManager::getNextMatchPoint() {
    return nullptr;
}
