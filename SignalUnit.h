//
//  SignalUnit.h
//  eDrive
//
//  Created by Diego Colombo on 07/07/2013.
//
//

#ifndef eDrive_SignalUnit_h
#define eDrive_SignalUnit_h

namespace mUBreeze{
    namespace eDrive{
		namespace DSP{
        class Engine;
        
        /*
         Base class to implement
         */
        class SignalUnit{
        public:
            SignalUnit();
            virtual ~SignalUnit();
            
            void Initialise(Engine* engine);
            
        protected:
            /*
             Override for custom initialisation
             */
            void OnInitialising();
        private:
            Engine* m_engine;
            
            
        };
		}
    }
}


#endif
