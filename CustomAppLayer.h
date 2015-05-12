//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef CUSTOMAPPLAYER_H_
#define CUSTOMAPPLAYER_H_

#include "NodeInfo.h"
#include <Vector>
#include <iostream>
using namespace std;

class CustomAppLayer
{
    private:
	
        //Sent packages
        long numSent;
		
        //Received packages
        long numReceived;
		
        //Package ID
        int packageID;
		
        //Distance
        double totalDistance;
		
        //Leader's information
        double localLeaderAcceleration;
        double localLeaderSpeed;

        //Array with info from neighbours
        std::vector<NodeInfo*> nodeInfoVector;

        //Last acceleration calculated with Platoon
        double lastAccelerationPlatoon;

        //Alpha constants to CACC
        double alpha1;
        double alpha2;
        double alpha3;
        double alpha4;
        double alpha5;

        //Lag alpha constant to CACC
        double alphaLag;

        //Parameters to calculate spacing error
        double length_vehicle_front;
        double desiredSpacing;

        //Beacon rate
        double beaconInterval;

        //Platoon rate
        double platoonInterval;

        //Beaconing flag
        bool beaconingEnabled;
		
		 //Speed of current node
		 double mySpeed;
		 
		 //Address of current node
		 double myAddress;

    public:
             CustomAppLayer();
             void handleLowerMsg(NodeInfo* nodeInfo);
             double getAccelerationPlatoon();
			 void setMyAddress(double s);
			 double getMyAddress();
			 void setMySpeed(double s);
			 double getMySpeed();


};

#endif /* CUSTOMAPPLAYER_H_ */
