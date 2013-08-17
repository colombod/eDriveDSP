#include "eDrive.h"
#include "..\eDriceOSC\OscMessage.h"
#include "SignalUnit.h"
#include <map>

namespace mUBreeze{
	namespace eDrive{
		namespace DSP{
        namespace SignalUnitFactory{
        
        typedef std::map<const std::string, CreateSingalUnit> Factory;
        Factory s_factoryMap;
        }
        
		// default constructor
		Engine::Engine(){
            m_channelCount = 0;
            ResetBuffers();
		}

		// the destructor is resposible to lcean up
		Engine::~Engine(){
			m_channelCount = 0;
			ResetBuffers();
            FlushInbox();
            FlushOutbox();
            mUBreeze::eDrive::SignalUnitFactory::s_factoryMap.clear();
		}

		void Engine::Initialise(int samplingRate, int channelCount){
			m_samplingRate = samplingRate;
			m_channelCount = channelCount;
			OnInitialising();
		}

		void Engine::OnInitialising(){
	
		}

		void Engine::DoStep(){
			if(m_channelCount > 0)
			{
			}
	
		}
        
        void Engine::FlushInbox(){
            std::queue<OscMessage*> empty;
            std::swap(m_inbox, empty);
        }
        
        void Engine::FlushOutbox(){
            std::queue<OscMessage*> empty;
            std::swap(m_outbox, empty);
        }
        
        float* const Engine::GetIncomingSampleBuffer(){
            return m_ptrIncomingSamples;
        }
        const float* const Engine::GetOutgoingSampleBuffer(){
            return m_ptrOututgoingSamples;
        }
        
		void Engine::ResetBuffers(){
            if(m_ptrIncomingSamples)
            {
                delete (m_ptrIncomingSamples);
            }
            
            if(m_ptrOututgoingSamples)
            {
                delete(m_ptrOututgoingSamples);
            }
			
			if(m_channelCount > 0)
			{
                m_ptrIncomingSamples = new float[m_channelCount];
                m_ptrOututgoingSamples = new float[m_channelCount];
			}
		}
        
        OscMessage* Engine::DequeueFromInbox(){
            return Dequeue(m_inbox);
        }
        
        OscMessage* Engine::DequeueFromOutbox(){
            return Dequeue(m_outbox);
        }
        
        void Engine::EnqueueOnInbox(OscMessage *message){
            Enqueue(message, m_inbox);
        }
        
        void Engine::EnqueueOnOutbox(OscMessage* message)
        {
            Enqueue(message,m_outbox);
        }
        OscMessage* Engine::Dequeue(std::queue<OscMessage *> &storage)  {
            OscMessage* ret = NULL;
            if(!m_inbox.empty()){
                ret = storage.front();
                storage.pop();
            }
            return ret;
        }
        
        void Engine::Enqueue(OscMessage* message, std::queue<OscMessage *>& storage){
            if(message)
            {
             storage.push(message);   
            }
        }
        
        void Engine::RegisterSignalUnit(const std::string id, CreateSingalUnit factoryMethod){
            if(factoryMethod)
            {
                mUBreeze::eDrive::SignalUnitFactory::s_factoryMap[id] = factoryMethod;
            }
        }
        
        SignalUnit* Engine::Create(const std::string id){
            SignalUnit* ret = NULL;
            SignalUnitFactory::Factory::iterator it = mUBreeze::eDrive::SignalUnitFactory::s_factoryMap.find(id);
            if( it != mUBreeze::eDrive::SignalUnitFactory::s_factoryMap.end() )
            {
                ret = it->second();
            }
            return ret;
        	}
		}
	}
}
