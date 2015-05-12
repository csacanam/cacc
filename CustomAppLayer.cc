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

#include "CustomAppLayer.h"

using namespace std;

CustomAppLayer::CustomAppLayer()
{
    // 1. General variables
    packageID = 0; // Package ID
    numSent = 0; // Sent packages
    numReceived = 0; // Received packages
    totalDistance = 0; // Total distance
    lastAccelerationPlatoon = 0; // Last acceleration calculated with CACC
    localLeaderAcceleration = 0; // Acceleration of leader
    localLeaderSpeed = 0; // // Speed of leader

    //2 . Platoon's parameters (CACC)
    alpha1 = 0.5;
    alpha2 = 0.5;
    alpha3 = 0.3;
    alpha4 = 0.1;
    alpha5 = 0.04;
    alphaLag = 0.8;
    length_vehicle_front = 2;
    desiredSpacing = 2;
    beaconInterval = 0.1;
    platoonInterval = 1;
    beaconingEnabled = false;

}


double CustomAppLayer::getAccelerationPlatoon()
{
    // 1. PREPARE

    //List without duplicates
    std::vector<NodeInfo*> noDuplicateInfo;
    double distanceBetweenActualAndFront;

    //Add NodeInfo objects to the list without duplicates
    for (int i = 0; i < int(nodeInfoVector.size()); i++)
    {
        NodeInfo* nodeInfo = nodeInfoVector.back();

        bool existeInfo = false;

        //Iterate the list without duplicates
        for (std::vector<NodeInfo*>::iterator it = noDuplicateInfo.begin(); it != noDuplicateInfo.end();
             ++it)
        {
            NodeInfo* n = *it;

            //If exist a package from the same source node, it won't be added to the list without duplicates
            if (n->getSrcAddress() == nodeInfo->getSrcAddress())
            {
                existeInfo = true;
                break;
            }
        }

        //If a package from the same source wasn't found, it will be added to the list without duplicates
        if (existeInfo == false)
        {
            noDuplicateInfo.push_back(nodeInfo);

        }

        //Delete the package from NodeInfoVector
        nodeInfoVector.pop_back();
    }

    // 2. START PLATOON

    //Calculate distance between nodes and current to determine the nearest to the current
    NodeInfo* nearestNode = NULL;
    NodeInfo* leaderNode = NULL;

    cout << "Node[" << getMyAddress() << "]: Running Platoon Update" << endl;

    if (noDuplicateInfo.size() > 0)
    {

        //a. Determine the nearest and the leader nodes
        for (std::vector<NodeInfo*>::iterator it = noDuplicateInfo.begin(); it != noDuplicateInfo.end();
             ++it)
        {
            NodeInfo* nodeInfo = *it;

            //Get distance to current from sending node
            int addr_node = nodeInfo->getSrcAddress();
            double distanceToActual = nodeInfo->getDistanceToCurrent();

            //Asign leader
            if (addr_node == 0)
            {
                leaderNode = *it;
            }

            //If don't exist a nearest node and the distance between the node and the current is more than zero, this is the current nearest node
            if (distanceToActual > 0 && nearestNode == NULL)
            {
                nearestNode = *it;
            }

            //If there is a nearest node, we have to compare the current node and the current nearest node
            if (nearestNode != NULL)
            {
                //Compare with the current nearest node
                double distanceToActual_nearest = nearestNode->getDistanceToCurrent();

                //If distance is below than the current nearest distance, it will be the nearest node
                if (distanceToActual > 0 && distanceToActual < distanceToActual_nearest)
                {
                    nearestNode = *it;
                }
            }
        }

        //b. Get information from the nearest node in the front
        double rel_speed_front;

        double spacing_error;
        double nodeFrontAcceleration;

        if (nearestNode != NULL)
        {
            //Calculate relative speed to the node in front
            rel_speed_front = getMySpeed() - nearestNode->getSpeed();

            //Calculate spacing error
            distanceBetweenActualAndFront = nearestNode->getDistanceToCurrent();
            spacing_error = -distanceBetweenActualAndFront + length_vehicle_front + desiredSpacing;

            nodeFrontAcceleration = nearestNode->getAcceleration();

        }
        else
        {
            rel_speed_front = 0;
            spacing_error = 0;
            nodeFrontAcceleration = 0;
        }

        //c. Get information from leader
        double leaderAcceleration;
        double leaderSpeed;

        if (leaderNode == NULL)
        {
            //We use the data coming with beaconing
            if (nearestNode != NULL && beaconingEnabled == true)
            {
                leaderAcceleration = nearestNode->getLeaderAcceleration();
                leaderSpeed = nearestNode->getLeaderSpeed();
                localLeaderAcceleration = nearestNode->getLeaderAcceleration();
                localLeaderSpeed = nearestNode->getLeaderSpeed();
            }
            else
            {
                leaderAcceleration = 0;
                leaderSpeed = 0;
                localLeaderAcceleration = 0;
                localLeaderSpeed = 0;
            }

        }
        else
        {
            leaderAcceleration = leaderNode->getAcceleration();
            leaderSpeed = leaderNode->getSpeed();
        }

        //Print data for calculation
        cout << "Node[" << getMyAddress() << "]: Platoon parameters" << endl;
        cout << "Distance to Vehicle in Front=" << distanceBetweenActualAndFront << endl;
        cout << "Vehicle in Front Acceleration=" << nodeFrontAcceleration << endl;
        cout << "Leader Acceleration=" << leaderAcceleration << endl;
        cout << "Relative speed vehicule in front=" << rel_speed_front << endl;
        cout << "Leader speed=" << leaderSpeed << endl;
        cout << "My speed=" << getMySpeed() << endl;
        cout << "Spacing Error=" << spacing_error << endl;

        //d. Calculate (Acceleration desired) A_des
        double A_des = alpha1 * nodeFrontAcceleration + alpha2 * leaderAcceleration
                       - alpha3 * rel_speed_front - alpha4 * (getMySpeed() - leaderSpeed)
                       - alpha5 * spacing_error;

        //e. Calculate desired acceleration adding a delay
        double A_des_lag = (alphaLag * A_des) + ((1 - alphaLag) * lastAccelerationPlatoon);

        lastAccelerationPlatoon = A_des_lag;


        return A_des_lag;
    }
    else
    {
        return 0;
    }
}


/**
 * Handle messages coming from outside
 */
void CustomAppLayer::handleLowerMsg(NodeInfo* nodeInfo)
{
    numReceived++;

    //Get information from package to forward to other nodes
    double speed = nodeInfo->getSpeed();
    double acceleration = nodeInfo->getAcceleration();
    int address = nodeInfo->getSrcAddress();

    cout << "Info from: " << address << endl;

    //Save leader acceleration and speed
    if (address == 0)
    {
        localLeaderAcceleration = acceleration;
        localLeaderSpeed = speed;
    }
    else if (beaconingEnabled == true)
    {
        //Package coming with beaconing

    }

    //Save package in NodeInfoVector
    nodeInfoVector.push_back(nodeInfo);

    return;
}


//Getters and setters

void CustomAppLayer::setMyAddress(double newAddress)
{
    myAddress = newAddress;
}

double CustomAppLayer::getMyAddress()
{
    return myAddress;
}

void CustomAppLayer::setMySpeed(double newSpeed)
{
    mySpeed = newSpeed;
}

double CustomAppLayer::getMySpeed()
{
    return mySpeed;
}