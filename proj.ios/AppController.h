//
//  sdfsdfsdsdAppController.h
//  sdfsdfsdsd
//
//  Created by duanhouhai on 12-9-13.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end

