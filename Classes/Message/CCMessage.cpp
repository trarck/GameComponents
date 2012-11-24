//
//  Message.m
//  Message

//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "CCMessage.h"

using namespace std;

NS_CC_BEGIN

CCMessage::CCMessage(void)
:m_type(0)
,m_sender(NULL)
,m_receiver(NULL)
//,m_dData(NULL)
,m_oData(NULL)
,m_timeStamp(0.0f)
{
    CCLog("Message create");
}

CCMessage::~CCMessage(void)
{
    CCLog("Message destroy begin");
    CC_SAFE_RELEASE(m_sender);
    CC_SAFE_RELEASE(m_receiver);
//    CC_SAFE_RELEASE(m_dData);
    CC_SAFE_RELEASE(m_oData);
    CCLog("Message destroy end");
}

MessageType CCMessage::getType()
{
    return m_type;
}

void CCMessage::setType(MessageType type)
{
    m_type=type;
}

MessageParty CCMessage::getSender()
{
    return m_sender;
}
void CCMessage::setSender(MessageParty sender)
{
    CC_SAFE_RETAIN(sender);
    CC_SAFE_RELEASE(m_sender);
    m_sender=sender;
}

MessageParty CCMessage::getReceiver()
{
    return m_receiver;
}

void CCMessage::setReceiver(MessageParty receiver)
{
    CC_SAFE_RETAIN(receiver);
    CC_SAFE_RELEASE(m_receiver);
    m_receiver=receiver;
}


void CCMessage::setData(CCObject* data)
{
    CC_SAFE_RETAIN(data);
    CC_SAFE_RELEASE(m_oData);
    m_oData=data;
    
}


CCObject* CCMessage::getData()
{
    return m_oData;
}

//void CCMessage::setObjectData(CCObject* data)
//{
//    CC_SAFE_RETAIN(data);
//    CC_SAFE_RELEASE(m_oData);
//    m_oData=data;
//    
//}
//
//CCObject* CCMessage::getObjectData()
//{
//    return m_oData;
//}
//
//
//void CCMessage::setData(CCDictionary* data)
//{
//    CC_SAFE_RETAIN(data);
//    CC_SAFE_RELEASE(m_dData);
//    m_dData=data;
//}

//void CCMessage::setDictionary(CCDictionary* data)
//{
//    CC_SAFE_RETAIN(data);
//    CC_SAFE_RELEASE(m_dData);
//    m_dData=data;
//}


CCDictionary* CCMessage::getDictionary()
{
    return (CCDictionary*) m_oData;
}


bool CCMessage::initWithType(MessageType type,MessageParty sender ,MessageParty receiver ,CCObject *data)
{
    m_type=type;
    setSender(sender);
    setReceiver(receiver);
    setData(data);
    
    return true;
}

bool CCMessage::initWithType(MessageType type,MessageParty sender ,MessageParty receiver)
{
    m_type=type;
    setSender(sender);
    setReceiver(receiver);
    
    return true;

}

bool CCMessage::initWithType(MessageType type,MessageParty sender)
{
    m_type=type;
    setSender(sender);
  
    return true;

}


//bool CCMessage::initWithType(MessageType type,MessageParty sender ,MessageParty receiver ,CCDictionary *data)
//{
//
//    m_type=type;
//    setSender(sender);
//    setReceiver(receiver);
//    setData(data);
//    
//    return true;
//}
//
//
//bool CCMessage::initWithType(MessageType type,MessageParty sender,CCDictionary *data)
//{
//    return initWithType(type,sender,NULL,data);
//}



NS_CC_END
