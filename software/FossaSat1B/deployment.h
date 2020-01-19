#ifndef DEPLOYMENT_H_INCLUDED
#define DEPLOYMENT_H_INCLUDED

#include "FossaSat1B.h"

/**
 * @file deployment.h
 * 
 * @brief The deployment sequence is outlined in the source deployment.cpp.
 */

/**
 * @brief This function deploys the antenna by powering the MOSFET1/2 for 1200 seconds.
 * 
 * @test (ID DEPLOYMENT_H_T0) (SEV 1) Make sure the antenna deploys using this function.
 * 
 */
void Deployment_Deploy();

#endif
