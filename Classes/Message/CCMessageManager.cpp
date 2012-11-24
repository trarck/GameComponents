    //
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "CCMessageManager.h"

NS_CC_BEGIN


CCMessageManager::CCMessageManager():
m_messages(NULL),
m_globalObject(NULL)
{
	CCLOG("CCMessageManager create");
}

CCMessageManager::~CCMessageManager()
{
	CCLOG("CCMessageManager destroy begin");
	CC_SAFE_RELEASE(m_messages);
	CC_SAFE_RELEASE(m_globalObject);
	CC_SAFE_RELEASE(m_regiesterMap);
	CCLOG("CCMessageManager destroy end");
}

CCMessageManager* CCMessageManager::s_sharedMessageManagerInstance=NULL;

CCMessageManager* CCMessageManager::defaultManager(void)
{
	if (!s_sharedMessageManagerInstance) {
		s_sharedMessageManagerInstance=new CCMessageManager();
		s_sharedMessageManagerInstance->init();
	}
	return s_sharedMessageManagerInstance;
}

void CCMessageManager::init()
{
	m_messages=new CCDictionary();
	m_globalObject=new CCObject();
	m_regiesterMap=new CCDictionary();
}

bool CCMessageManager::registerReceiver(CCObject* receiver,SEL_MessageHandler handle ,MessageType type ,CCObject* sender ,CCObject*  handleObject)
{
	CCAssert(receiver!=NULL,"MessageManage:registerReceiver:receiver can't be null");
	CCAssert(handle!=NULL,"MessageManage:registerReceiver:handle");
	CCAssert(handleObject!=NULL,"MessageManage:registerReceiver:handleObject");

	//type等于0，则所有消息都会发送
	//register for type
	CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
	if (msgMap==NULL) {
		msgMap=new CCDictionary();
		m_messages->setObject(msgMap,type);
		msgMap->release();
	}
	//register for sender
	//sender 为空，则注册到全局对象上
	sender=sender==NULL?m_globalObject:sender;
	unsigned int senderKey=sender->m_uID;
	CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(senderKey);
	if (!senderMap) {
		senderMap=new CCDictionary();
	    msgMap->setObject(senderMap ,senderKey);
		senderMap->release();
	}
	//register for receiver
	unsigned int receiverKey=receiver->m_uID;
	CCArray *receiverList=(CCArray*)senderMap->objectForKey(receiverKey);
	if (!receiverList) {
		receiverList=new CCArray();
		senderMap->setObject(receiverList,receiverKey);
		receiverList->release();
	}
	
	//检查是否已经注册过
    bool isRegisted=false;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(receiverList,pObject){
        CCMessageHandler* handler=(CCMessageHandler*) pObject;
        if (handler->getHandle()==handle && handler->getTarget()==handleObject) {
			CCAssert(0,"Handle has register");
            isRegisted=true;
            break;
		}
    }

    if(!isRegisted){
        //注册时不需要时间
        //struct timeval now;
        //	gettimeofday(&now,NULL);
        
        //register for handler
        CCMessageHandler *handler=new CCMessageHandler();
        handler->initWithTarget(handleObject,handle);
        receiverList->addObject(handler);
        handler->release();

//		addReceiverMap(receiver,handle,type,sender,handleObject);
    }
	return !isRegisted;
}

//使receiver可以接收sender发送过来的叫type的消息，并用handle来处理
//关注的对象是receiver
bool CCMessageManager::registerReceiver(CCObject* receiver,SEL_MessageHandler handle,MessageType type ,CCObject* sender)
{
	return registerReceiver(receiver ,handle,type ,sender ,receiver);
}


void CCMessageManager::addReceiverMap(CCObject* receiver,SEL_MessageHandler handle ,MessageType type ,CCObject* sender ,CCObject*  handleObject)
{

	CCDictionary *receiverMap=(CCDictionary*) m_regiesterMap->objectForKey(receiver->m_uID);
	if (receiverMap==NULL) {
		receiverMap=new CCDictionary();
		m_regiesterMap->setObject(receiverMap,receiver->m_uID);
		receiverMap->release();
	}

	CCDictionary *msgMap=(CCDictionary*) receiverMap->objectForKey(type);
	if (msgMap==NULL) {
		msgMap=new CCDictionary();
		receiverMap->setObject(msgMap,type);
		msgMap->release();
	}
	
	sender=sender==NULL?m_globalObject:sender;
	unsigned int senderKey=sender->m_uID;
	CCArray *senderList=(CCArray*)msgMap->objectForKey(senderKey);
	if (!senderList) {
		senderList=new CCArray();
		msgMap->setObject(senderList,senderKey);
		senderList->release();
	}
	//不用检查是否已经注册过，在父类中已经检查过了

	//map for handler
	CCMessageHandler *handler=new CCMessageHandler();
	handler->initWithTarget(handleObject,handle);
	senderList->addObject(handler);
	handler->release();
}


void CCMessageManager::removeReceiver(CCObject* receiver,MessageType type ,CCObject* sender,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
    
    
    if(sender==NULL){
        removeReceiver(receiver, type, handle);
    }else if(handle==NULL){
        removeReceiver(receiver,type,sender);
    }else {
        CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

        if(msgMap){
            CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
            removeReceiverMap(receiver, senderMap, handle);
        }
    }
        
    
//	CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
//
//    if(msgMap){
//        
//        if(sender){
//            CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
//            if(senderMap){
//                CCArray *receiverList=(CCArray*)senderMap->objectForKey(receiver->m_uID);
//                if(receiverList){
//                    if(handle){
//                        removeReceiverList(receiverList,handle);
//                    }else{
//                        removeReceiverList(receiverList);
//                    }
//                }
//            }
//        }else{
//            //删除消息type中接收者为ceceiver的注册信息
//            CCDictElement* pElement = NULL;
//            CCDICT_FOREACH(msgMap,pElement){
//                CCDictionary *senderMap=(CCDictionary*)pElement->getObject();
//                
//                CCArray *receiverList=(CCArray*)senderMap->objectForKey(receiver->m_uID);
//                if(receiverList){
//                    if(handle){
//                        removeReceiverList(receiverList,handle);
//                    }else{
//                        removeReceiverList(receiverList);
//                    }
//                }
//            }
//        }
//    }

}

void CCMessageManager::removeReceiver(CCObject* receiver,MessageType type ,CCObject* sender)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
    
    if(sender==NULL){
        removeReceiver(receiver,type);
    }else {
        CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
        if(msgMap){
            CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
            removeReceiverMap(receiver, senderMap);
        }
    }
}

void CCMessageManager::removeReceiver(CCObject* receiver,MessageType type ,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
    
    if(handle==NULL){
        removeReceiver(receiver,type);
    }else {
        CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
        if(msgMap){
            CCDictElement* pElement = NULL;
            CCDICT_FOREACH(msgMap,pElement){
                CCDictionary *senderMap=(CCDictionary*)pElement->getObject();
                removeReceiverMap(receiver, senderMap,handle);
            }
        }
    }
}

void CCMessageManager::removeReceiver(CCObject* receiver,MessageType type)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
	CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
	if(msgMap){
        //删除消息type中接收者为ceceiver的注册信息
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(msgMap,pElement){
            CCDictionary *senderMap=(CCDictionary*)pElement->getObject();
            removeReceiverMap(receiver, senderMap);
        }
    }
}

void CCMessageManager::removeReceiver(CCObject* receiver)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
    
    CCDictElement* msgMapElement = NULL;
    CCDictElement* senderMapElement = NULL;
    
    CCDICT_FOREACH(m_messages,msgMapElement){
        CCDictionary *msgMap=(CCDictionary*) msgMapElement->getObject();
        
        CCDICT_FOREACH(msgMap,senderMapElement){
            CCDictionary *senderMap=(CCDictionary*)senderMapElement->getObject();
            
            removeReceiverMap(receiver, senderMap);
        }
    }
}


void CCMessageManager::removeReceiver(CCObject* receiver,CCObject* sender,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");

    if(sender==NULL){
        removeReceiver(receiver, handle);
    }else if(handle==NULL){
        removeReceiver(receiver,sender);
    }else{
        CCDictElement* msgMapElement = NULL;
        
        CCDICT_FOREACH(m_messages,msgMapElement){
            CCDictionary *msgMap=(CCDictionary*) msgMapElement->getObject();
            CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
            removeReceiverMap(receiver, senderMap,handle);
        }
    }
    
}

void CCMessageManager::removeReceiver(CCObject* receiver,CCObject* sender)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
    
    if(sender==NULL){
        removeReceiver(receiver);
    }else {
        CCDictElement* msgMapElement = NULL;
        
        CCDICT_FOREACH(m_messages,msgMapElement){
            CCDictionary *msgMap=(CCDictionary*) msgMapElement->getObject();
            CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
            removeReceiverMap(receiver, senderMap);
//            if (senderMap) {
//                CCArray *receiverList=(CCArray*)senderMap->objectForKey(receiver->m_uID);
//                if(receiverList){
//                    removeReceiverList(receiverList);
//                }
//            }
        }
    }
}

void CCMessageManager::removeReceiver(CCObject* receiver,SEL_MessageHandler handle)
{
    
}

void CCMessageManager::removeReceiverList(CCArray* list,SEL_MessageHandler handle){
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(list,pObject){
		CCMessageHandler* handler=(CCMessageHandler*) pObject;
		if (handler->getHandle()==handle) {
			list->removeObject(handler);
		}
	}
}

void CCMessageManager::removeReceiverList(CCArray* list){
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(list,pObject){
		list->removeObject(pObject);
	}
}

void CCMessageManager::removeReceiverMap(CCObject* receiver,CCDictionary* map,SEL_MessageHandler handle){
	if (map) {
        CCArray *receiverList=(CCArray*)map->objectForKey(receiver->m_uID);
        if(receiverList){
            removeReceiverList(receiverList,handle);
        }
    }

}

void CCMessageManager::removeReceiverMap(CCObject* receiver,CCDictionary* map){
	if (map) {
        CCArray *receiverList=(CCArray*)map->objectForKey(receiver->m_uID);
        if(receiverList){
            removeReceiverList(receiverList);
        }
    }
}


void CCMessageManager::execRegisterReceiverList(CCArray* receiverList ,CCMessage* message)
{
	
	CCAssert(receiverList!=NULL,"CCMessageManager:execRegisterReceiverList:receiverList can't be null!");
	CCObject* pObject = NULL;
    CCARRAY_FOREACH(receiverList,pObject){
        CCMessageHandler* handler=(CCMessageHandler*) pObject;
		handler->execute(message);
    }
}


void CCMessageManager::execAllRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message)
{
	CCAssert(senderMap!=NULL,"CCMessageManager:execAllRegisterWithSenderMap:senderMap can't be null!");
	//send to all
	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(senderMap,pElement){
		execRegisterReceiverList((CCArray*)pElement->getObject(),message);
	}
}

void CCMessageManager::execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message)
{
	CCObject* receiver=message->getReceiver();
	if (receiver) {
		//message for receiver
		CCArray* receiverList=(CCArray*)senderMap->objectForKey(receiver->m_uID);
		if(receiverList) execRegisterReceiverList(receiverList,message);
	}else {
		//send to all receiver
		execAllRegisterWithSenderMap(senderMap ,message);
	}
}

void CCMessageManager::execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message,CCObject*  receiver)
{
	CCAssert(senderMap!=NULL,"CCMessageManager:execRegisterWithSenderMap:senderMap can't be null!");
	if (receiver) {
		//message for receiver
		CCArray* receiverList=(CCArray*)senderMap->objectForKey(receiver->m_uID);
		if(receiverList) execRegisterReceiverList(receiverList ,message);
	}else {
		//send to all receiver
		execAllRegisterWithSenderMap(senderMap ,message);
	}
}

//
void CCMessageManager::dispatchMessage(CCMessage* message)
{
	CCObject* sender;
	//CCAssert(message.type!=0,)
	//如果message的type不为0，则需要执行一个type为global的所有消息
	if (message->getType()!=GlobalMessageType) {
		//message for global
		CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(GlobalMessageType);
		if (msgMap) {
			//parse for sender
			//如果sender不为空，则还要触发一次全局消息。
			sender=message->getSender();
			if (sender) {
				//执行注册到sender的消息的处理方法
				CCDictionary* senderMap=(CCDictionary *)msgMap->objectForKey(sender->m_uID);
				//如果注册则执行
				if (senderMap)  execRegisterWithSenderMap(senderMap ,message);
				//执行注册到global的消息的处理方法
				CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
				//如果注册则执行
				if (globalMap)  execRegisterWithSenderMap(globalMap,message);
			}else {
				//执行注册到global的消息的处理方法
				CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
				//如果注册则执行
				if (globalMap)  execRegisterWithSenderMap(globalMap ,message);
			}
		}
	}
	
	//message for type
	CCDictionary* msgMap= (CCDictionary*)m_messages->objectForKey(message->getType());
	if (msgMap) {
		sender=message->getSender();
		//parse for sender
		//如果sender不为空，则还要触发一次全局消息。
		if (sender) {
			//执行注册到sender的消息的处理方法
			CCDictionary* senderMap=(CCDictionary *)msgMap->objectForKey(sender->m_uID);
			//如果注册则执行
			if (senderMap)  execRegisterWithSenderMap(senderMap,message);
			//执行注册到global的消息的处理方法
			CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
			//如果注册则执行
			if (globalMap)  execRegisterWithSenderMap(globalMap,message);
		}else {
			//执行注册到global的消息的处理方法
			CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
			//如果注册则执行
			if (globalMap)  execRegisterWithSenderMap(globalMap,message);
		}
	}
}


void CCMessageManager::dispatchMessageWithType(MessageType type ,CCObject* sender ,CCObject* receiver,CCObject* data)
{
	CCMessage* message=new CCMessage();
	message->initWithType(type ,sender ,receiver ,data);
	dispatchMessage(message);
	message->release();
}

//void CCMessageManager::dispatchMessageWithType(MessageType type ,CCObject* sender ,CCObject* receiver,CCDictionary* data)
//{
//	CCMessage* message=new CCMessage();
//	message->initWithType(type ,sender ,receiver ,data);
//	dispatchMessage(message);
//	message->release();
//}

void CCMessageManager::dispatchMessageWithType(MessageType type ,CCObject* sender ,CCObject* receiver)
{
	CCMessage* message=new CCMessage();
	message->initWithType(type ,sender ,receiver);
	dispatchMessage(message);
	message->release();
}


//适应message中没有receiver的情况
void CCMessageManager::dispatchMessage(CCMessage* message ,CCObject*  receiver)
{
	if (message->getType()!=GlobalMessageType) {
		//message for global
		CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(m_globalObject->m_uID);
		if (msgMap) {
			//parse for sender
			//如果sender不为空，则还要触发一次全局消息。
			CCObject* sender=message->getSender();
			if (sender) {
				//执行注册到sender的消息的处理方法
				CCDictionary* senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
				//如果注册则执行
				if (senderMap)  execRegisterWithSenderMap(senderMap,message,receiver);
				//执行注册到global的消息的处理方法
				CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
				//如果注册则执行
				if (globalMap)  execRegisterWithSenderMap(globalMap ,message ,receiver);
			}else {
				//执行注册到global的消息的处理方法
				CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
				//如果注册则执行
				if (globalMap)  execRegisterWithSenderMap(globalMap ,message ,receiver);
			}
		}
	}
	//message for type
	CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(message->getType());
	if (msgMap) {
		//parse for sender
		//如果sender不为空，则还要触发一次全局消息。
		CCObject* sender=message->getSender();
		if (sender) {
			//执行注册到sender的消息的处理方法
			CCDictionary* senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
			//如果注册则执行
			if (senderMap)  execRegisterWithSenderMap(senderMap ,message ,receiver);
			//执行注册到global的消息的处理方法
			CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
			//如果注册则执行
			if (globalMap)  execRegisterWithSenderMap(globalMap ,message ,receiver);
		}else {
			//执行注册到global的消息的处理方法
			CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
			//如果注册则执行
			if (globalMap)  execRegisterWithSenderMap(globalMap ,message ,receiver);
		}
	}
}

NS_CC_END
