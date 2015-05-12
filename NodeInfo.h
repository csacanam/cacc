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

#ifndef NODEINFO_H_
#define NODEINFO_H_

/**
 * Clase que encapsula la información proveniente de otro nodo
 */
class NodeInfo 
{

private:
    int srcAddress;
    int packageID;
    double distanceToCurrent;
    double speed;
    double acceleration;
    double leaderAcceleration;
    double leaderSpeed;

public:
    NodeInfo( int newSrcAddress, int newPackageID, double newDistanceToCurrent, double newSpeed, double newAcceleration, double newLeaderAcceleration, double newLeaderSpeed);
    void setSrcAddress(int sA);
    void setPackageID(int pI);
    void setDistanceToCurrent(double  dTC);
    void setSpeed(double s);
    void setAcceleration(double a);
    void setLeaderAcceleration(double a);
    void setLeaderSpeed(double s);
    int getSrcAddress();
    int getPackageID();
    double getDistanceToCurrent();
    double getSpeed();
    double getAcceleration();
    double getLeaderAcceleration();
    double getLeaderSpeed();
};

#endif /* NODEINFO_H_ */
