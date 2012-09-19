//
//  YHMacros.h
//  GameComponents
//
//  Created by duanhouhai on 12-9-19.


#ifndef __YH_Macros_h__
#define __YH_Macros_h__

/** CC_PROPERTY_READONLY is used to declare a protected variable.
 We can use getter to read the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 @warning : The getter is a public virtual function, you should rewrite it first.
 The variables and methods declared after CC_PROPERTY_READONLY are all public.
 If you need protected or private, please declare.
 */
#define CC_DIRECT_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: varType get##funName(void);

#define CC_DIRECT_PROPERTY_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: const varType& get##funName(void);

/** CC_PROPERTY is used to declare a protected variable.
 We can use getter to read the variable, and use the setter to change the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 "set + funName" is the name of the setter.
 @warning : The getter and setter are public virtual functions, you should rewrite them first.
 The variables and methods declared after CC_PROPERTY are all public.
 If you need protected or private, please declare.
 */
#define CC_DIRECT_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: varType get##funName(void);\
public: void set##funName(varType var);

#define CC_DIRECT_PROPERTY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: const varType& get##funName(void);\
public: void set##funName(const varType& var);

/** CC_SYNTHESIZE_READONLY is used to declare a protected variable.
 We can use getter to read the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 @warning : The getter is a public inline function.
 The variables and methods declared after CC_SYNTHESIZE_READONLY are all public.
 If you need protected or private, please declare.
 */
#define CC_DIRECT_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: varType get##funName(void) const { return varName; }

#define CC_DIRECT_SYNTHESIZE_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: const varType& get##funName(void) const { return varName; }

/** CC_SYNTHESIZE is used to declare a protected variable.
 We can use getter to read the variable, and use the setter to change the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 "set + funName" is the name of the setter.
 @warning : The getter and setter are public  inline functions.
 The variables and methods declared after CC_SYNTHESIZE are all public.
 If you need protected or private, please declare.
 */
#define CC_DIRECT_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: varType get##funName(void) const { return varName; }\
public: void set##funName(varType var){ varName = var; }

#define CC_DIRECT_SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: const varType& get##funName(void) const { return varName; }\
public: void set##funName(const varType& var){ varName = var; }

#define CC_DIRECT_SYNTHESIZE_RETAIN(varType, varName, funName)    \
private: varType varName; \
public: varType get##funName(void) const { return varName; } \
public: void set##funName(varType var)   \
{ \
if (varName != var) \
{ \
CC_SAFE_RETAIN(var); \
CC_SAFE_RELEASE(varName); \
varName = var; \
} \
} 



#endif //__YH_Macros_h__
