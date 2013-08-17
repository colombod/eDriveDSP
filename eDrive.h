//
//  eDrive.h
//  eDrive.CompileTest
//
//  Created by Diego Colombo on 07/07/2013.
//
//

#ifndef eDrive_h
#define eDrive_h
#include <queue>
#include <string>


namespace  mUBreeze{  
	namespace  eDrive{
		namespace DSP{
        
        
        class OscMessage;
        class SignalUnit;
        
        typedef SignalUnit* (*CreateSingalUnit)(void);
        
		class  Engine{  
			
		private:
			int m_channelCount;
			int m_samplingRate;
			float* m_ptrIncomingSamples;
			float* m_ptrOututgoingSamples;
			
            std::queue<OscMessage*> m_inbox;
            std::queue<OscMessage*> m_outbox;
			void ResetBuffers();
            
            OscMessage* Dequeue(std::queue<OscMessage*>& storage);
            void Enqueue(OscMessage* message, std::queue<OscMessage*>& storage);
           
            
        protected:
            /*
			 Override for sutom initialisation step
             */
			virtual  void  OnInitialising();
            /*
             Flushes and clears all inbox messages
             */
            void FlushInbox();
            
            /*
             Flushes and clears all outbox messages
             */
            void FlushOutbox();

		public:
			Engine();  
			virtual  ~Engine();  
			/*
			 Performs  a  step  
			 */  
			void  DoStep();  
						
			/*
			 Call this at the very beginning
			 */
			
			void  Initialise(int  samplingRate, int channelCount);  
				
			
            int GetBufferSize() { return m_channelCount;}
            
            float* const GetIncomingSampleBuffer();
            
            const float* const GetOutgoingSampleBuffer();
            
            // set the sample value for the channel. channel index is zero based.
            void SetInputSample(float value, int channel);
            
            OscMessage* DequeueFromOutbox();
            
            
            OscMessage* DequeueFromInbox();
            
            void EnqueueOnInbox(OscMessage* message);
            
            void EnqueueOnOutbox(OscMessage* message);
            
            static void RegisterSignalUnit(const std::string id, CreateSingalUnit factoryMethod);
            static SignalUnit* Create(const std::string id);
			};
		}
	}
}
#endif