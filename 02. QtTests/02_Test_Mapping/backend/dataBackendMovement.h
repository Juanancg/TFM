#ifndef DATABACKENDMOVEMENT_H
#define DATABACKENDMOVEMENT_H
#include <QtCore/QObject>
#include <iostream>
QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

const int MAX_POSITIONS = 10;

struct PosAndAngle {
    double pos_x;
    double delta_x;

    double pos_y;
    double delta_y;

    double angle;

    PosAndAngle() {
        pos_x = 0;
        delta_x = 0;

        pos_y = 0;
        delta_y = 0;

        angle = 0;
    }

    void printData() {
        std::cout << "x = " << pos_x << ", y = " << pos_y << ", angle = " << angle << ", deltaX = " << delta_x << ", deltaY = " << delta_y << std::endl;
    }
};

class dataBackendMovement : public QObject
{
    Q_OBJECT

public:
    explicit dataBackendMovement(QQuickView *appViewer, QObject *parent = nullptr);

public slots:

    void set_map_coordinates(int x_min, int y_min, int x_max, int y_max) {
        min_map_x_coordinate_ = x_min;
        min_map_y_coordinate_ = y_min;
        max_map_x_coordinate_ = x_max;
        max_map_y_coordinate_ = y_max;
        /*std::cout << "Min X: " << min_map_x_coordinate_ << ", "
                  << "Max X: " << max_map_x_coordinate_ << "\t"
                  << "Min Y: " << min_map_y_coordinate_ << ", "
                  << "Max Y: " << max_map_y_coordinate_ << "\t" << std::endl;*/
    }

    void savePosition(const int x, const int y, const int angle);
    double getPosX(const int step);
    double getDeltaX(const int step);
    double getPosY(const int step);
    double getDeltaY(const int step);
    double getPosAngle(const int step);
    unsigned int getTotalSteps() {return internal_step_counter_;}

    bool bplanningMovement(const int x_actual, const int y_actual, const int x_pedida, const int y_pedida);

private:

    QQuickView *m_appViewer_;

    bool bplanningXcoordinate(const int x_pedida, const int x_actual, const int y_actual);
    bool bplanningYcoordinate(const int y_pedida, const int x_actual, const int y_actual);

    double dcheckLimitX(const double x_value);
    double dcheckLimitY(const double y_value);
    bool bcheckLimitX(const double x_value);
    bool bcheckLimitY(const double y_value);
    bool bcheckIfPositionIsPossible(const double x, const double y);

    PosAndAngle getLastPosPlanned();
    void printAllPlanningSteps();

    std::array<PosAndAngle, MAX_POSITIONS> planning_pos_;
    unsigned int internal_step_counter_;

    int min_map_x_coordinate_;
    int min_map_y_coordinate_;
    int max_map_x_coordinate_;
    int max_map_y_coordinate_;


};


#endif // DATABACKENDMOVEMENT_H
