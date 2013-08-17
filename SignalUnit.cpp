//
//  SignalUnit.cpp
//  eDrive
//
//  Created by Diego Colombo on 07/07/2013.
//
//


#include "eDrive.h"
#include "OscMessage.h"
#include "SignalUnit.h"

namespace mUBreeze{
    namespace eDrive{
		namespace DSP{
        
        SignalUnit::SignalUnit(){
        }
        
        SignalUnit::~SignalUnit(){
            
        }
        
        void SignalUnit::Initialise( Engine* engine)
        {
            m_engine = engine;
            OnInitialising();
        }
        void SignalUnit::OnInitialising(){}
    
	}
    }
}
