//
// Created by Juan Camilo Sacanamboy on 12/05/15.
//

#include "Main.h"
#include <iostream>
#include "NodeInfo.h"
#include "CustomAppLayer.h"
using namespace std;

int main()
{
    //Create nodes
    //NodeInfo *nodeInfo = new NodeInfo(1, 1, 2, 3, 4, 5, 6);
    //NodeInfo *nodeInfoUno = new NodeInfo(1, 1, 2, 3, 4, 5, 6);
    NodeInfo *nodeInfoDos = new NodeInfo(2, 1, 2, 3, 4, 5, 6);
    NodeInfo *nodeInfoTres = new NodeInfo(2, 1, 2, 3, 4, 5, 6);
    NodeInfo *nodeInfoCuatro = new NodeInfo(3, 1, 2, 3, 4, 5, 6);
    NodeInfo *nodeInfoCinco = new NodeInfo(3, 1, 2, 3, 4, 5, 6);
    NodeInfo *nodeInfoSeis = new NodeInfo(4, 1, 2, 3, 4, 5, 6);
    NodeInfo *nodeInfoSiete = new NodeInfo(4, 1, 2, 3, 4, 5, 6);
    NodeInfo *nodeInfoOcho = new NodeInfo(5, 1, 2, 3, 4, 5, 6);
    NodeInfo *nodeInfoNueve = new NodeInfo(5, 1, 2, 3, 4, 5, 6);
    NodeInfo *nodeInfoDiez = new NodeInfo(6, 1, 2, 3, 4, 5, 6);
    NodeInfo *nodeInfoOnce = new NodeInfo(6, 1, 2, 3, 4, 5, 6);

    //Create App Layer
    CustomAppLayer *customAppLayer = new CustomAppLayer();
    customAppLayer->setMyAddress(1);
    customAppLayer->setMySpeed(30);
    customAppLayer->handleLowerMsg(nodeInfoDos);
    customAppLayer->handleLowerMsg(nodeInfoTres);
    customAppLayer->handleLowerMsg(nodeInfoCuatro);
    customAppLayer->handleLowerMsg(nodeInfoCinco);
    customAppLayer->handleLowerMsg(nodeInfoSeis);
    customAppLayer->handleLowerMsg(nodeInfoSiete);
    customAppLayer->handleLowerMsg(nodeInfoOcho);
    customAppLayer->handleLowerMsg(nodeInfoNueve);
    customAppLayer->handleLowerMsg(nodeInfoDiez);
    customAppLayer->handleLowerMsg(nodeInfoOnce);

    //Calculate acceleration with CACC
    double acceleration= customAppLayer->getAccelerationPlatoon();

    //Print desired acceleration
    cout<<"acceleration should be: " << acceleration;

    return 0;
}