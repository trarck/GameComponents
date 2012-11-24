//
//  Message.h
//  Message
//  
//  消息是基于投递的，不存在父子关系。一个消息对应消息的处理函数（一个或多个），不存捕捉和冒泡。可以延迟发关。可以设置优先级。
//  注意和事件的区别，事件要复杂些。消息通常和简单发送执行，所以性能要高一些。
//  当然事件可以定义的很简单或遵循一定模式(dom事件模型)。
//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef __CCMessage_H__
#define __CCMessage_H__

#include "cocos2d.h"

NS_CC_BEGIN

typedef unsigned int MessageType;
//typedef CCObject *MessageObject;
typedef CCObject *MessageParty;
//typedef long int MessageParty;
//typedef NSString *MessageType
//typedef id MessageSender;
//typedef int MessageSender;

class CCMessage : public CCObject {

public:
    CCMessage();
    ~CCMessage(void);
    
	MessageType getType();
	void setType(MessageType type);
	MessageParty getSender();
	void setSender(MessageParty sender);
	MessageParty getReceiver();
	void setReceiver(MessageParty receiver);
    
    
    
    void setData(CCObject* data);
    CCObject* getData();
    
//    void setObjectData(CCObject* data);
//    CCObject* getObjectData();
//    
//    void setData(CCDictionary* data);
    
    void setDictionary(CCDictionary* data);
    CCDictionary* getDictionary();
    
    bool initWithType(MessageType type,MessageParty sender ,MessageParty receiver ,CCObject *data);
    bool initWithType(MessageType type,MessageParty sender ,MessageParty receiver);
    bool initWithType(MessageType type,MessageParty sender);

//    bool initWithType(MessageType type,MessageParty sender ,MessageParty receiver ,CCDictionary *data);
//    bool initWithType(MessageType type,MessageParty sender,CCDictionary *data);
    
    

private:
    MessageType m_type;//消息的类型或ID。
    MessageParty m_sender;//消息的发送者
	MessageParty m_receiver;//消息的接收者
    float m_timeStamp;//发送时间
//	CCDictionary *m_dData;
    CCObject* m_oData;
};

//typedef void (CCObject::*SEL_MessageHandler)(CCMessage*);
//#define message_selector(_SELECTOR) (SEL_MessageHandler)(&_SELECTOR)

NS_CC_END

#endif  // __CCMessage_H__
