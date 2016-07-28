//
//  MyUserHooks.hpp
//  
//  Polarizer oringinally created in Pythia Example main62
//  Class separated and created by James on 6/23/16
//  Adepted here by Ziheng on 6/23/16.
//


#ifndef MyUserHooks_hpp
#define MyUserHooks_hpp

#include <stdio.h>
#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"

using namespace Pythia8;



class MyUserHooks : public UserHooks {
    
public:
    
    MyUserHooks(Info* , bool, double);
    MyUserHooks(Info* , bool, double, int);
    ~MyUserHooks();
    
    bool canVetoProcessLevel();
    bool doVetoProcessLevel(Event& process);
    double selectAngle( double inputSpin, double inputId );
    
private:
    
    Info* infoPtr;
    // bool to define the frame for helicity.
    bool helicityDefinedByMother;
    double _polarization;
    int _spinningparticle;
    
};


#endif /* MyUserHooks_hpp */
