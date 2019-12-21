#include "dataBackendMovement.h"
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>

void dataBackendMovement::printAllPlanningSteps() {
    for (unsigned int i = 0; i < planning_pos_.size(); ++i) {
        planning_pos_[i].printData();
    }
}

PosAndAngle dataBackendMovement::getLastPosPlanned() {
    if (internal_step_counter_ == 0) {
        return planning_pos_[0];
    }

    return planning_pos_[internal_step_counter_ - 1];
}

/// *********************** FUNCTION *********************** ///
dataBackendMovement::dataBackendMovement(QQuickView *appViewer, QObject *parent) :
    QObject(parent),
    m_appViewer_(appViewer)
{
    internal_step_counter_ = 0;

    min_map_x_coordinate_ = 0;
    min_map_y_coordinate_ = 0;
    max_map_x_coordinate_ = 0;
    max_map_y_coordinate_ = 0;
}

/// *********************** FUNCTION *********************** ///
void dataBackendMovement::savePosition(const int x, const int y, const int angle) {

    if (internal_step_counter_ < MAX_POSITIONS) {
        planning_pos_[internal_step_counter_].pos_x = x;
        planning_pos_[internal_step_counter_].pos_y = y;
        planning_pos_[internal_step_counter_].angle = angle;
    }

}

/// *********************** FUNCTION *********************** ///
double dataBackendMovement::getPosX(const int step) {

    if (step < MAX_POSITIONS) {
        return planning_pos_[step].pos_x;
    }

    std::cout << "[LOGGER] Step out of range" << std::endl;
    return 0;
}

/// *********************** FUNCTION *********************** ///
double dataBackendMovement::getPosY(const int step) {

    if (step < MAX_POSITIONS) {
        return planning_pos_[step].pos_y;
    }

    std::cout << "[LOGGER] Step out of range" << std::endl;
    return 0;
}

/// *********************** FUNCTION *********************** ///
double dataBackendMovement::getDeltaX(const int step) {

    if (step < MAX_POSITIONS) {
        return planning_pos_[step].delta_x;
    }

    std::cout << "[LOGGER] Step out of range" << std::endl;
    return 0;
}

/// *********************** FUNCTION *********************** ///
double dataBackendMovement::getDeltaY(const int step) {

    if (step < MAX_POSITIONS) {
        return planning_pos_[step].delta_y;
    }

    std::cout << "[LOGGER] Step out of range" << std::endl;
    return 0;
}

/// *********************** FUNCTION *********************** ///
double dataBackendMovement::getPosAngle(const int step) {
    if (step < MAX_POSITIONS) {
        return planning_pos_[step].angle;
    }

    std::cout << "[LOGGER] Step out of range" << std::endl;
    return 0;
}

/// *********************** FUNCTION *********************** ///
double dataBackendMovement::dcheckLimitX(const double x_value) {
    int returnValue = 0;
    if (x_value < max_map_x_coordinate_) {
        if (x_value < min_map_x_coordinate_) {
            returnValue = min_map_x_coordinate_;
        } else {
            returnValue = x_value;
        }
    } else {
        returnValue = max_map_x_coordinate_;
    }

    return returnValue;

}

/// *********************** FUNCTION *********************** ///
double dataBackendMovement::dcheckLimitY(const double y_value) {
    int returnValue = 0;
    if (y_value < max_map_y_coordinate_) {
        if (y_value < min_map_y_coordinate_) {
            returnValue = min_map_y_coordinate_;
        } else {
            returnValue = y_value;
        }
    } else {
        returnValue = max_map_y_coordinate_;
    }

    return returnValue;
}

/// *********************** FUNCTION *********************** ///
bool dataBackendMovement::bcheckLimitX(const double x_value) {
    double value = dcheckLimitX(x_value);
    if (value == 0 || value == max_map_x_coordinate_ || value == min_map_x_coordinate_) {
        std::cout << "[LOGGER] Invalid X position: " << x_value << " - " << value << std::endl;
        return false;
    }
    return true;

}

/// *********************** FUNCTION *********************** ///
bool dataBackendMovement::bcheckLimitY(const double y_value) {
    double value = dcheckLimitY(y_value);
    if (value == 0 || value == max_map_y_coordinate_ || value == min_map_y_coordinate_) {
        std::cout << "[LOGGER] Invalid Y position: " << y_value << " - " << value << std::endl;
        return false;
    }
    return true;
}

/// *********************** FUNCTION *********************** ///
bool dataBackendMovement::bcheckIfPositionIsPossible(const double x, const double y) {
    bool returnValue = true;
    returnValue = bcheckLimitX(x);
    if (returnValue == true) {
        returnValue = bcheckLimitY(y);
    }
    return returnValue;
}

bool dataBackendMovement::bplanningXcoordinate(const int x_pedida, const int x_actual, const int y_actual) {

    // Checkear si es posible llegar hasta la x_pedida en la y_actual
    if (bcheckIfPositionIsPossible(x_pedida, y_actual)) {

        planning_pos_[internal_step_counter_].pos_x = x_pedida;
        planning_pos_[internal_step_counter_].pos_y = y_actual;
        planning_pos_[internal_step_counter_].delta_x  = x_pedida - x_actual;
        planning_pos_[internal_step_counter_].delta_y = 0;

        if (planning_pos_[internal_step_counter_].delta_x < 0) {
            planning_pos_[internal_step_counter_].angle = 180;

        } else if (0 <= planning_pos_[internal_step_counter_].delta_x) {
            planning_pos_[internal_step_counter_].angle = 0;

        }
        internal_step_counter_++;
        return true;

    } else {

        // TODO:
        std::cout << "[LOGGER] Position isn't posible" << std::endl;
        return false;
    }

}

bool dataBackendMovement::bplanningYcoordinate(const int y_pedida, const int x_actual, const int y_actual) {

    // Checkear si es posible llegar hasta la y_pedida en la x_actual
    if (bcheckIfPositionIsPossible(x_actual, y_pedida)) {

        planning_pos_[internal_step_counter_].pos_x = x_actual;
        planning_pos_[internal_step_counter_].pos_y = y_pedida;
        planning_pos_[internal_step_counter_].delta_y = y_pedida - y_actual;
        planning_pos_[internal_step_counter_].delta_x = 0;

        if (planning_pos_[internal_step_counter_].delta_y < 0) {
            planning_pos_[internal_step_counter_].angle = 270;

        } else if (0 <= planning_pos_[internal_step_counter_].delta_y) {
            planning_pos_[internal_step_counter_].angle = 90;

        }
        internal_step_counter_++;
        return true;
    } else {

        // TODO:
        std::cout << "[LOGGER] Position isn't posible" << std::endl;
        return false;
    }

}


bool dataBackendMovement::bplanningMovement(const int x_actual, const int y_actual, const int x_pedida, const int y_pedida) {

    if (x_actual == x_pedida && y_actual == y_pedida) return false;

    /*if (internal_step_counter_ == 0) {
        planning_pos_[internal_step_counter_].pos_x = x_actual;
        planning_pos_[internal_step_counter_].pos_y = y_actual;
        internal_step_counter_++;
    }*/
    bool result = true;



    while (getLastPosPlanned().pos_x != x_pedida || getLastPosPlanned().pos_y != y_pedida) {

        if (internal_step_counter_ == 0) {

            // 1º Movement
            if (x_actual != x_pedida) {
                result &= bplanningXcoordinate(x_pedida, x_actual, y_actual);
                std::cout << "[LOGGER] Planning first X coordinate" << std::endl;

            } else if (y_actual != y_pedida) {
                result &= bplanningYcoordinate(y_pedida, x_actual, y_actual);
                std::cout << "[LOGGER] Planning first Y coordinate" << std::endl;
            }

        } else {

            if (getLastPosPlanned().pos_x != x_pedida) {
                result &= bplanningXcoordinate(x_pedida, getLastPosPlanned().pos_x, getLastPosPlanned().pos_y);
                std::cout << "[LOGGER] Planning X coordinate" << std::endl;
            }

            if (getLastPosPlanned().pos_y != y_pedida) {
                result &= bplanningYcoordinate(y_pedida, getLastPosPlanned().pos_x, getLastPosPlanned().pos_y);
                std::cout << "[LOGGER] Planning Y coordinate" << std::endl;
            }
        }

    }

    printAllPlanningSteps();
    return result;
}
