#ifndef __MMOUSE_H__
#define __MMOUSE_H__

typedef enum mouseOrientation {
    North, East, South, West
    } orientation;

class mMouse {
    private:
        // original sensor readings
        int origLeftSensor;
        int origRightSensor;
        int origFrontSensor;
        
        // saved sensor readings
        int lastLeftSensor;
        int lastRightSensor;
        int lastFrontSensor;
        
        // location and direction
        unsigned cellX;
        unsigned cellY;
        orientation direction;
    public:
        mMouse();
       
        void initCalibrate();
        void repositionMouse();
        
        // gets the reading of sensor
        int getLeftSensor();
        int getRightSensor();
        int getFrontSensor();
        
        // gets the average reading of sensor (count <= 500)
        int avgLeftSensor(unsigned count);
        int avgRightSensor(unsigned count);
        int avgFrontSensor(unsigned count);
        
        void calcAverageSensors(unsigned count);
        
        // do we even need this?
        int getLeftEncoder();
        int getRightEncoder();
        
        // used in mMap
        void setMouseLocation(unsigned x, unsigned y);
        unsigned getCellX();
        unsigned getCellY();
        
        void stopMouse(unsigned ms);
        void moveForward(double leftMotor, double rightMotor);
        void centerMouse();
        void turnRight();
        void turnLeft();
        void turnAround();
        
        bool checkLeftWall(unsigned offset);
        bool checkRightWall(unsigned offset);
        bool checkFrontWall(unsigned offset);
};

#endif
